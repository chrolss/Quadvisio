
#include <iostream>
#include "controller.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    
    std::cout << "Qvis started" << std::endl;
    
    QvisController controller;
    controller.showUI();
    
    return app.exec();
}

