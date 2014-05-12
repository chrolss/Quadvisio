#include <GUI.h>

GUI::GUI()
{
    QDesktopWidget *desktop = QApplication::desktop();
    
    WIDTH = 640;
    HEIGHT = 480;
    
    screenWidth = desktop->width();
    screenHeight = desktop->height();
    
    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;
    
    
    window.resize(WIDTH, HEIGHT);
    window.move(x,y);
    window.setWindowTitle("Qvis v0.1 (alpha)");
    window.show();
}