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

void QvisController::createTCPThread()
{
    ui->connectButton->setEnabled(false);

    tcpSocket = new QTcpSocket(this);
    std::cout << "This comes from the controller" << std::endl;
    int rc = pthread_create(&t, NULL, threadHelper, static_cast<void*>(this));
    if ( rc != 0 )
    {
        std::cerr << "Error in thread creation..." << std::endl;
        std::cerr << strerror(rc) << std::endl;
        exit(EXIT_FAILURE);
    }
}

void QvisController::connectTCP()
{
    std::cout << "This comes from the thread" << std::endl;
    
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readTCP()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    
    ui->connectButton->setText("Connecting");
    blockSize = 0;
    tcpSocket->connectToHost(ui->ipField->text(),ui->portField->text().toInt());
    
    tcpSocket->abort();
    tcpSocket->deleteLater();
    ui->lineEdits[0]->setText("Hej");
}

void QvisController::readTCP()
{
    
}

void QvisController::displayError(QAbstractSocket::SocketError socketError)
{
    
}