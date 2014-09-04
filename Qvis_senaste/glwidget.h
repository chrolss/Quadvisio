//
//  glwidget.h
//  Qvis
//
//  Created by Toni Axelsson on 2014-07-08.
//
//

#ifndef __Qvis__glwidget__
#define __Qvis__glwidget__

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
    
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    
    public slots:
    void setXrot(int angle);
    void setYrot(int angle);
    void setZrot(int angle);
    
signals:
    void xRotChanged(int angle);
    void yRotChanged(int angle);
    void zRotChanged(int angle);
    
protected:
    void initializeGL();
    void paintGL();
    
private:
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;
};


#endif /* defined(__Qvis__glwidget__) */
