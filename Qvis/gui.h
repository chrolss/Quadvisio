#ifndef GUI_H
#define GUI_H

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>

class GUI : public QWidget
{
    Q_OBJECT
    
    public:
        GUI();

    private:
        int WIDTH;
        int HEIGHT;
    
        int screenWidth;
        int screenHeight;

        int x,y;
    
        QWidget window;

};

#endif