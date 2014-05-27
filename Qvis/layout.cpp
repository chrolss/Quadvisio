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
    setFixedSize(200, 300);
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
    connectButton = new QPushButton(tr("Connect to Pi"));
        
    connectLayout->addWidget(connectLabel);
    connectLayout->addWidget(connectButton);
    connectGroupBox->setLayout(connectLayout);
}


