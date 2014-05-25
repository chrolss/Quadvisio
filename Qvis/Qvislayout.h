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

class Qvislayout : public QDialog
{
    Q_OBJECT
    
public:
    Qvislayout();
    
private slots:
    void saveData();
    void createGridBox();
    void createConnectBox();
    void connectTCP();
    
private:
    enum { NumGridRows = 3};
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QGroupBox *gridGroupBox;
    QGroupBox *connectGroupBox;
    QLabel *connectLabel;
    QPushButton *connectButton, *closeButton;
    QVBoxLayout *connectLayout;
};

#endif /* defined(__layout_test__layout__) */
