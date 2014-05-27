//
//  controller.cpp
//  layout_test
//
//  Created by Toni Axelsson on 2014-05-27.
//
//

#include "controller.h"

QvisController::QvisController() {
    
    ui = new QvisLayout;
    model = new QvisModel;
    
    setTCPButton();
}


void QvisController::connectTCP()
{
    std::cout << "This comes from the controller" << std::endl;
    model->connectToServer();
}

void QvisController::showUI()
{
    ui->show();
}

void QvisController::setTCPButton()
{
    QObject::connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectTCP()));
}