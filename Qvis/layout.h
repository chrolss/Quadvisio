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
    void setDataFields(QString str);
    
    QPushButton *connectButton, *closeButton;
    
private slots:
    void saveData();
    void createGridBox();
    void createConnectBox();
    
private:
    enum { NumGridRows = 3};
    QLabel *labels[NumGridRows];
    QGroupBox *gridGroupBox;
    QGroupBox *connectGroupBox;
    QVBoxLayout *connectLayout;
    QLineEdit *lineEdits[NumGridRows], *ipField, *portField;
    QLabel *connectLabel;
    
};

#endif /* defined(__layout_test__layout__) */
