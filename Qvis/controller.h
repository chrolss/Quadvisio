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
#include <opencv2/highgui/highgui.hpp>

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
    void videoButtonPushed();
    void pidButtonClicked();
    void setPIDButtonClicked();
    void closeTCP();
    void readTCP();
    void displayError(QAbstractSocket::SocketError socketError);    
    
private:
    void setButtons();
    
    QvisLayout *ui;
    QvisModel *model;
    
    // Network communication
    QByteArray getSendData();
    
    QTcpSocket *tcpSocket;
    QByteArray data;
    QString qs;
    QStringList pieces;
    QNetworkSession *networkSession;
    int numbytes=0;
    int imgSize = 230400; // 320x240 resolution
    cv::Mat bufFrame;
    bool recvImg=false;
    bool readData=false;
    int imgChar;
    const uchar *qImageBuffer;
    
    bool videoStream=false;
    
    //
    double pid[9];
    
};

#endif /* defined(__layout_test__controller__) */
