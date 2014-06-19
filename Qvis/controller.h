//
//  controller.h
//  layout_test
//
//  Created by Toni Axelsson on 2014-05-27.
//
//

#ifndef __layout_test__controller__
#define __layout_test__controller__

#include <iostream>
#include <QtGui>
#include <QObject>
#include <QDialog>
#include <QTcpSocket>
#include <string.h>
#include <unistd.h>


#include "layout.h"
#include "model.h"

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
class QNetworkSession;

class QvisController : public QDialog
{
    Q_OBJECT
    
public:
    QvisController();
    void showUI();
    
private slots:
    void createTCPThread();
    void closeTCP();
    void readTCP();
    void displayError(QAbstractSocket::SocketError socketError);
    
private:
    void setTCPButton();
    
    QvisLayout *ui;
    QvisModel *model;
    
    // Networking
    pthread_t t;
    QTcpSocket *tcpSocket;
    QByteArray data;
    QString qs;
    quint16 blockSize;
    QNetworkSession *networkSession;
    int numb=0;
};

#endif /* defined(__layout_test__controller__) */
