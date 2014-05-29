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
    
    QPushButton *connectButton, *closeButton;
    
private slots:
    void saveData();
    void createGridBox();
    void createConnectBox();
    
private:
    enum { NumGridRows = 3};
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows], *ipField;
    QGroupBox *gridGroupBox;
    QGroupBox *connectGroupBox;
    QLabel *connectLabel;

    QVBoxLayout *connectLayout;
    
};

#endif /* defined(__layout_test__layout__) */
