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
    createGridBox();
    createConnectBox();
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(connectGroupBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Qvis v0.1 (alpha)"));
    setFixedSize(300, 350);
}

void QvisLayout::saveData()
{
    
}

// Create the connect Acceleration data UI section
void QvisLayout::createGridBox()
{
    gridGroupBox = new QGroupBox(tr("Acceleration"));
    QGridLayout *layout = new QGridLayout;
    
    labels[0] = new QLabel(tr("X"));
    lineEdits[0] = new QLineEdit;
    layout->addWidget(labels[0], 1, 0);
    layout->addWidget(lineEdits[0], 1, 1);
    labels[1] = new QLabel(tr("Y"));
    lineEdits[1] = new QLineEdit;
    layout->addWidget(labels[1], 2, 0);
    layout->addWidget(lineEdits[1], 2, 1);
    labels[2] = new QLabel(tr("Z"));
    lineEdits[2] = new QLineEdit;
    layout->addWidget(labels[2], 3, 0);
    layout->addWidget(lineEdits[2], 3, 1);
    
    gridGroupBox->setLayout(layout);
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

void QvisLayout::setDataFields(QString str)
{
    lineEdits[0]->setText(str);
}

int QvisLayout::getPort()
{
    return portField->text().toInt();
}

QString QvisLayout::getIp()
{
    return ipField->text();
}


