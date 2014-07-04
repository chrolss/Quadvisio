//
//  layout.h
//  layout_test
//
//  Created by Toni Axelsson on 2014-05-25.
//
//

#ifndef __layout_test__layout__
#define __layout_test__layout__

#include <iostream>
#include <QtGui>
#include <QObject>
#include <QDialog>

class QvisLayout : public QDialog
{
    Q_OBJECT
    
public:
    QvisLayout();
    void setConnectionStatus(bool state);
    void setConnected();
    int getPort();
    QString getIp();
    void setDataFields(QStringList strList);
    
    QPushButton *connectButton, *closeButton;
    
private slots:
    void saveData();
    void createAccBox();
    void createConnectBox();
    void createAngBox();
    void createVideoBox();
    void createOrientationBox();
    
private:
    enum { NumGridRows = 3};
    QLabel *labelsAcc[NumGridRows], *labelsAng[NumGridRows];
    QLabel *valAcc[NumGridRows], *valAng[NumGridRows];
    QGroupBox *connectGroupBox, *gridAccBox, *gridAngBox, *gridVideoBox, *gridOrientationBox;
    QGridLayout *connectLayout;
    QLineEdit *ipField, *portField;
    QLabel *connectLabel, *ipLabel, *portLabel;
    
};

#endif /* defined(__layout_test__layout__) */
