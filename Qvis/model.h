//
//  model.h
//  layout_test
//
//  Created by Toni Axelsson on 2014-05-27.
//
//

#ifndef __layout_test__model__
#define __layout_test__model__

#include <iostream>
#include "tcpHandler.h"

class QvisModel
{
public:
    QvisModel();
    void connectToServer();
    
private:
    tcpHandler *tcpH;
};

#endif /* defined(__layout_test__model__) */
