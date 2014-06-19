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
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(gridAccBox, 0, 0);
    mainLayout->addWidget(gridAngBox, 0, 1);
    mainLayout->addWidget(connectGroupBox, 1, 0, 1, 2);
    setLayout(mainLayout);
    setWindowTitle(tr("Qvis v0.1 (alpha)"));
    setFixedSize(400, 400);
}

void QvisLayout::saveData()
{
    
}

// Create the connect Acceleration data UI section
void QvisLayout::createAccBox()
{
    gridAccBox = new QGroupBox(tr("Acceleration"));
    QGridLayout *layout = new QGridLayout;
    
    labelsAcc[0] = new QLabel(tr("X"));
    lineEditsAcc[0] = new QLineEdit;
    layout->addWidget(labelsAcc[0], 1, 0);
    layout->addWidget(lineEditsAcc[0], 1, 1);
    labelsAcc[1] = new QLabel(tr("Y"));
    lineEditsAcc[1] = new QLineEdit;
    layout->addWidget(labelsAcc[1], 2, 0);
    layout->addWidget(lineEditsAcc[1], 2, 1);
    labelsAcc[2] = new QLabel(tr("Z"));
    lineEditsAcc[2] = new QLineEdit;
    layout->addWidget(labelsAcc[2], 3, 0);
    layout->addWidget(lineEditsAcc[2], 3, 1);
    
    gridAccBox->setLayout(layout);
}

void QvisLayout::createAngBox()
{
    gridAngBox =new QGroupBox(tr("Angles"));
    QGridLayout *layout = new QGridLayout;
    
    labelsAng[0] = new QLabel(tr("Roll"));
    lineEditsAng[0] = new QLineEdit;
    layout->addWidget(labelsAng[0], 1, 0);
    layout->addWidget(lineEditsAng[0], 1, 1);
    labelsAng[1] = new QLabel(tr("Pitch"));
    lineEditsAng[1] = new QLineEdit;
    layout->addWidget(labelsAng[1], 2, 0);
    layout->addWidget(lineEditsAng[1], 2, 1);
    labelsAng[2] = new QLabel(tr("Yaw"));
    lineEditsAng[2] = new QLineEdit;
    layout->addWidget(labelsAng[2], 3, 0);
    layout->addWidget(lineEditsAng[2], 3, 1);
    
    gridAngBox->setLayout(layout);
    
}

// Create the connect UI section
void QvisLayout::createConnectBox()
{
    connectGroupBox = new QGroupBox(tr("TCP Connection"));
    connectLayout = new QVBoxLayout;
    connectLabel = new QLabel(tr("Not connected"));
    connectLabel->setStyleSheet("QLabel { color : red; }");
    connectLabel->setAlignment(Qt::AlignCenter);
    ipField = new QLineEdit;
    ipField->setText("10.0.1.4");
    portField = new QLineEdit;
    portField->setText("3490");
    connectButton = new QPushButton(tr("Connect to Pi"));
        
    connectLayout->addWidget(connectLabel);
    connectLayout->addWidget(ipField);
    connectLayout->addWidget(portField);
    connectLayout->addWidget(connectButton);
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
    lineEditsAcc[0]->setText(strList.value(0));
    lineEditsAcc[1]->setText(strList.value(1));
    lineEditsAcc[2]->setText(strList.value(2));
    lineEditsAng[2]->setText(strList.value(3));
    lineEditsAng[1]->setText(strList.value(4));
    lineEditsAng[0]->setText(strList.value(5));
}

int QvisLayout::getPort()
{
    return portField->text().toInt();
}

QString QvisLayout::getIp()
{
    return ipField->text();
}


