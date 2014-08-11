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

class QvisModel
{
public:
    QvisModel();
    
    void setPIDParameters(double p, double i, double d);
    
private:
    double p;
    double i;
    double d;
};

#endif /* defined(__layout_test__model__) */
