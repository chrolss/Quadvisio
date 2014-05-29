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
    void setTCPButton();
    void showUI();
    
    /* For the TCP connection */
    void connectTCP();
    static void* threadHelper(void *pThisArg)
    {
        QvisController *pThis = static_cast<QvisController*>(pThisArg);
        pThis->connectTCP();
        return NULL;
    }
    
private slots:
    void createTCPThread();
    void readTCP();
    void displayError(QAbstractSocket::SocketError socketError);
    
private:
    QvisLayout *ui;
    QvisModel *model;
    
    // Networking
    pthread_t t;
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;
    QNetworkSession *networkSession;
    
};

#endif /* defined(__layout_test__controller__) */
