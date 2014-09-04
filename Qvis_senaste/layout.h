//
//  layout.h
//  layout_test
//
//  Created by Toni Axelsson on 2014-05-25.
//
//

#ifndef __layout_test__layout__
#define __layout_test__layout__

#include <iostream>
#include <QtGui>
#include <QObject>
#include <QDialog>
#include <QtWebKit/QtWebKit>

class GLWidget;

class QvisLayout : public QDialog
{
    Q_OBJECT
    
public:
    QvisLayout();
    
    void createPIDWindow();
    void openPIDWindow();
    void closePIDWindow();
    
    void updateImg(QImage img);
    
    // Setters
    void setConnectionStatus(bool state);
    void setConnected();
    void setDataFields(QStringList strList);
    void setInfoText(QString s);
    
    // Getters
    int getPort();
    QString getIp();
    int getThrustValue();
    int getFPSValue();
    QString getPIDString();
    
    // Objects
    QPushButton *connectButton, *closeButton;
    QLabel *videoLabel;
    
    //Control Objects
    QPushButton *takeOfButton, *landButton, *videoButton, *motorButton, *altitudeLock, *pidButton;
    QSpinBox *verticalThrustSpin;
    
    // PID window objects
    QLabel *pRollLabel, *iRollLabel, *dRollLabel, *pPitchLabel, *iPitchLabel, *dPitchLabel, *pYawLabel, *iYawLabel, *dYawLabel;
    QLineEdit *pRollField, *iRollField, *dRollField, *pPitchField, *iPitchField, *dPitchField,*pYawField, *iYawField, *dYawField;
    QPushButton *setPIDButton;
    
signals:
    void valueChanged(int value);
    
private slots:
    void saveData();
    void createAccBox();
    void createAngBox();
    void createPowerBox();
    void createConnectBox();
    void createVideoBox();
    void createMovementBox();
    void createControls();
    
private:
    enum { NumGridRows = 3};
    QLabel *labelsAcc[NumGridRows], *labelsAng[NumGridRows];
    QLabel *valAcc[NumGridRows], *valAng[NumGridRows];
    QLabel *voltageHeaderLabel;
    QDoubleSpinBox *desiredAlt;
    QGroupBox *connectGroupBox, *gridAccBox, *gridAngBox, *gridVideoBox, *gridOrientationBox, *gridControls;
    QGroupBox *batteryBox, *mapBox, *altitudeBox, *speedBox;
    QGridLayout *connectLayout;
    QLineEdit *ipField, *portField;
    QLabel *connectLabel, *ipLabel, *portLabel, *infoLabel;
    
    // Control objects
    QSlider *verticalThrustSlider, *videoFPSSlider;
    
    GLWidget *glwidget;
    
    QDialog *pidWindow;
    
};

#endif /* defined(__layout_test__layout__) */
