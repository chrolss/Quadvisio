//
//  controller.cpp
//  layout_test
//
//  Created by Toni Axelsson on 2014-05-27.
//
//

#include <QtNetwork>
#include "controller.h"

QvisController::QvisController() {
    
    ui = new QvisLayout;
    model = new QvisModel;
    
    setButtons();
    bufFrame = cv::Mat::zeros(240, 320, CV_8UC3);
}

void QvisController::showUI()
{
    ui->show();
}

void QvisController::setButtons()
{
    QObject::connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(createTCPThread()));
    QObject::connect(ui->videoButton, SIGNAL(clicked()), this, SLOT(videoButtonPushed()));
    QObject::connect(ui->pidButton, SIGNAL(clicked()), this, SLOT(pidButtonClicked()));
    QObject::connect(ui->setPIDButton, SIGNAL(clicked()), this, SLOT(setPIDButtonClicked()));
}

void QvisController::createTCPThread()
{
    if (ui->getPort() != 3490) {
        ui->setInfoText("Atlas is on port 3940");
        return;
    }
    
    ui->setConnectionStatus(true);

    tcpSocket = new QTcpSocket(this);
    
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readTCP()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    tcpSocket->connectToHost(ui->getIp(),ui->getPort());
    
    QObject::connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(closeTCP()));
    std::cout << "Connection button set to close" << std::endl;
    tcpSocket->write(getSendData(), 5);
    ui->setConnected();
}

void QvisController::closeTCP()
{
    tcpSocket->disconnect();
    tcpSocket->abort();
    tcpSocket->deleteLater();
    ui->setConnectionStatus(false);
    QObject::connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(createTCPThread()));
    std::cout << "Connection button set to connect" << std::endl;

}

void QvisController::readTCP()
{
    while (tcpSocket->bytesAvailable()>0) {

        if (numbytes==0 && tcpSocket->bytesAvailable()>5) {
            
            data = tcpSocket->read(5);
            qs = data;
            numbytes = qs.mid(0,2).toInt();
            imgChar = qs.mid(3,1).toInt();
            
            if (imgChar==1) {
                recvImg=true;
            }
            else {
                recvImg=false;
            }
        }
        
        if (!recvImg && tcpSocket->bytesAvailable()>=numbytes) {
            
            data = tcpSocket->read(numbytes);
            qs = data;

            pieces = qs.split(" ");
            ui->setDataFields(pieces);
            numbytes = 0;

            // When done reading send back the input data
            tcpSocket->write(getSendData(), 5);
        }
        
        if (recvImg && tcpSocket->bytesAvailable()>=(numbytes+230400)) {
            std::cout << "Reading data and image" << std::endl;

            data = tcpSocket->read(numbytes);
            qs = data;
            pieces = qs.split(" ");
            ui->setDataFields(pieces);
            numbytes = 0;
            
            data = tcpSocket->read(imgSize);
            int ptr=0;
            for (int i = 0;  i < bufFrame.rows; i++) {
                for (int j = 0; j < bufFrame.cols; j++) {
                    bufFrame.at<cv::Vec3b>(i,j) = cv::Vec3b(data[ptr+ 0],data[ptr+1],data[ptr+2]);
                    ptr=ptr+3;
                }
            }
            
            qImageBuffer = (const uchar*)bufFrame.data;
            QImage img(qImageBuffer, bufFrame.cols, bufFrame.rows, bufFrame.step, QImage::Format_RGB888);
            img = img.rgbSwapped();
            if (videoStream) {
                ui->updateImg(img);
            }
            
            // When done reading, send back the input data
            tcpSocket->write(getSendData(), 5);
        }
        
        else {
            return;
        }
    }
}

QByteArray QvisController::getSendData() {
    QByteArray data;
    int thrust = ui->getThrustValue();
    int fps = ui->getFPSValue();
    
    if (thrust<100 && thrust>=10) {
        data.append("0");
        data.append(QString::number(thrust));
    }
    
    else if (thrust<10) {
        data.append("00");
        data.append(QString::number(thrust));
    }
    else {
        data.append(QString::number(thrust));
    }
    
    if (videoStream) {
        data.append("1");
    }
    
    else {
        data.append("0");
    }
    
    data.append(QString::number(fps));
    
    
    
    return data;
}

void QvisController::videoButtonPushed() {
    if (videoStream==false) {
        videoStream=true;
        ui->videoButton->setText("Video Off");
    }
    else {
        videoStream=false;
        ui->videoButton->setText("Video On");
        ui->videoLabel->setText("Video Off");
    }
}

void QvisController::pidButtonClicked() {
    ui->openPIDWindow();
}

void QvisController::setPIDButtonClicked() {
    ui->getPIDValues(pid);
    ui->closePIDWindow();
    std::cout << pid[0] << std::endl;
}

void QvisController::displayError(QAbstractSocket::SocketError socketError)
{
    std::cout << "In Error function" << std::endl;

    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            ui->setInfoText(tr("Host not found, check Port and IP"));
            QMessageBox::information(this, tr("Fortune Client"),
                                     tr("The host was not found. Please check the "
                                        "host name and port settings."));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, tr("Fortune Client"),
                                     tr("The connection was refused by the peer. "
                                        "Make sure the fortune server is running, "
                                        "and check that the host name and port "
                                        "settings are correct."));
            break;
        default:
            ui->setInfoText(tr("The following error occurred: %1.").arg(tcpSocket->errorString()));
            //closeTCP();
    }
    
    ui->setConnectionStatus(false);
}