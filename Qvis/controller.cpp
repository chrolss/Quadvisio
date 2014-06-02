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
    
    setTCPButton();
}

void QvisController::showUI()
{
    ui->show();
}

void QvisController::setTCPButton()
{
    QObject::connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(createTCPThread()));
}

// Create and start thread for TCP connection
void QvisController::createTCPThread()
{
    
    ui->setConnectionStatus(true);

    tcpSocket = new QTcpSocket(this);
    std::cout << "This comes from the controller" << std::endl;
    
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readTCP()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    blockSize = 0;
    tcpSocket->connectToHost(ui->getIp(),ui->getPort());
    
    //QObject::connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(closeTCP()));
    ui->setConnected();
}

void QvisController::closeTCP()
{
    tcpSocket->abort();
    tcpSocket->deleteLater();
    ui->setConnectionStatus(false);
}

void QvisController::readTCP()
{
    std::cout << "hej" << std::endl;

    QByteArray data = tcpSocket->readAll();
    QString qs = data;
    // Either this if you use UTF-8 anywhere
    std::string utf8_text = qs.toUtf8().constData();
    std::cout << utf8_text << std::endl;

    ui->setDataFields(qs);
}

void QvisController::displayError(QAbstractSocket::SocketError socketError)
{
    std::cout << "In Error function" << std::endl;

    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
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
            QMessageBox::information(this, tr("Fortune Client"),
                                     tr("The following error occurred: %1.")
                                     .arg(tcpSocket->errorString()));
    }
    
    ui->setConnectionStatus(false);
}