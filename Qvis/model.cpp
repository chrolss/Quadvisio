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

void QvisModel::setPIDParameters(double p_, double i_, double d_) {
    p = p_;
    i = i_;
    d = d_;
}



