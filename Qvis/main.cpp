
#include <iostream>
#include "layout.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    
    Qvislayout qvis;
    qvis.show();
    
    return app.exec();
}

