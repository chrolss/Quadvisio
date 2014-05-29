//
//  model.cpp
//  layout_test
//
//  Created by Toni Axelsson on 2014-05-27.
//
//

#include "model.h"

QvisModel::QvisModel()
{

}

void QvisModel::connectToServer()
{
    tcpH = new tcpHandler;
    std::cout << "And this comes from the Model" << std::endl;

}




