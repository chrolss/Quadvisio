//
//  layout.cpp
//  layout_test
//
//  Created by Toni Axelsson on 2014-05-25.
//
//

#include "layout.h"

QvisLayout::QvisLayout()
{
    std::cout << "This comes from the GUI" << std::endl;
    createAccBox();
    createAngBox();
    createConnectBox();
    createVideoBox();
    createOrientationBox();
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(gridVideoBox, 0, 0, 1, 2);
    mainLayout->addWidget(gridOrientationBox, 0, 2, 1, 2);
    mainLayout->addWidget(gridAccBox, 1, 1, 1, 1);
    mainLayout->addWidget(gridAngBox, 1, 2, 1, 1);
    mainLayout->addWidget(connectGroupBox, 2, 1, 1, 2);
    setLayout(mainLayout);
    setWindowTitle(tr("Qvis v0.2 (alpha)"));
    setFixedSize(400, 400);
}

void QvisLayout::saveData()
{
    
}

// Create acceleration box
void QvisLayout::createAccBox()
{
    gridAccBox = new QGroupBox(tr("Acceleration"));
    QGridLayout *layout = new QGridLayout;
    
    labelsAcc[0] = new QLabel(tr("X: "));
    valAcc[0] = new QLabel(tr("0"));
    layout->addWidget(labelsAcc[0], 0, 0);
    layout->addWidget(valAcc[0], 0, 1);
    labelsAcc[1] = new QLabel(tr("Y: "));
    valAcc[1] = new QLabel(tr("0"));
    layout->addWidget(labelsAcc[1], 1, 0);
    layout->addWidget(valAcc[1], 1, 1);
    labelsAcc[2] = new QLabel(tr("Z: "));
    valAcc[2] = new QLabel(tr("0"));
    layout->addWidget(labelsAcc[2], 2, 0);
    layout->addWidget(valAcc[2], 2, 1);
    
    gridAccBox->setLayout(layout);
}

void QvisLayout::createAngBox()
{
    gridAngBox = new QGroupBox(tr("Angles"));
    QGridLayout *layout = new QGridLayout;
    
    labelsAng[0] = new QLabel(tr("Roll :"));
    valAng[0] = new QLabel(tr("0"));
    layout->addWidget(labelsAng[0], 0, 0);
    layout->addWidget(valAng[0], 0, 1);
    labelsAng[1] = new QLabel(tr("Pitch: "));
    valAng[1] = new QLabel(tr("0"));
    layout->addWidget(labelsAng[1], 1, 0);
    layout->addWidget(valAng[1], 1, 1);
    labelsAng[2] = new QLabel(tr("Yaw: "));
    valAng[2] = new QLabel(tr("0"));
    layout->addWidget(labelsAng[2], 2, 0);
    layout->addWidget(valAng[2], 2, 1);
    
    gridAngBox->setLayout(layout);
    
}

void QvisLayout::createVideoBox() {
    
    gridVideoBox = new QGroupBox(tr("Camera"));
}

void QvisLayout::createOrientationBox(){
    
    gridOrientationBox = new QGroupBox(tr("Orientation"));
}

// Create the connect UI section
void QvisLayout::createConnectBox()
{
    connectGroupBox = new QGroupBox(tr("TCP Connection"));
    connectLayout = new QGridLayout;
    connectLabel = new QLabel(tr("Not connected"));
    connectLabel->setStyleSheet("QLabel { color : red; }");
    connectLabel->setAlignment(Qt::AlignCenter);
    
    ipLabel = new QLabel(tr("Ip:"));
    portLabel = new QLabel(tr("Port:"));
    
    ipField = new QLineEdit;
    ipField->setText("10.0.1.8");
    portField = new QLineEdit;
    portField->setText("3490");
    connectButton = new QPushButton(tr("Connect to Atlas"));
        
    connectLayout->addWidget(connectLabel, 0, 0, 1, 3);
    connectLayout->addWidget(ipLabel, 1, 0, 1, 1);
    connectLayout->addWidget(ipField, 1, 1, 1, 2);
    connectLayout->addWidget(portLabel, 2, 0, 1, 1);
    connectLayout->addWidget(portField, 2, 1, 1, 2);
    connectLayout->addWidget(connectButton, 3, 0, 1, 3);
    connectGroupBox->setLayout(connectLayout);
}

void QvisLayout::setConnectionStatus(bool state)
{
    if (state) {
        connectButton->setEnabled(false);
        ipField->setEnabled(false);
        portField->setEnabled(false);
        connectButton->setText("Connecting");
        connectLabel->setStyleSheet("QLabel { color : black; }");
        connectLabel->setText("Connecting...");
    }
    else {
        connectButton->setEnabled(true);
        ipField->setEnabled(true);
        portField->setEnabled(true);
        connectButton->setText("Connect");
        connectLabel->setStyleSheet("QLabel { color : red; }");
        connectLabel->setText("Not Connected");
    }
}

void QvisLayout::setConnected()
{
    connectButton->setEnabled(true);
    connectButton->setText("Disconnect");
    connectLabel->setStyleSheet("QLabel { color : green; }");
    connectLabel->setText("Not connected to: " + ipField->text());
}

void QvisLayout::setDataFields(QStringList strList)
{
    valAcc[0]->setText(strList.value(0));
    valAcc[1]->setText(strList.value(1));
    valAcc[2]->setText(strList.value(2));
    valAng[2]->setText(strList.value(3));
    valAng[1]->setText(strList.value(4));
    valAng[0]->setText(strList.value(5));
}

int QvisLayout::getPort()
{
    return portField->text().toInt();
}

QString QvisLayout::getIp()
{
    return ipField->text();
}


