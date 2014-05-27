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

#include "layout.h"
#include "model.h"

class QvisController : public QDialog
{
    Q_OBJECT
    
public:
    QvisController();
    void setTCPButton();
    void showUI();
    
private slots:
    void connectTCP();
    
private:
    QvisLayout *ui;
    QvisModel *model;
    
};

#endif /* defined(__layout_test__controller__) */
