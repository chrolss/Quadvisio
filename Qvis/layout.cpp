//
//  layout.cpp
//  layout_test
//
//  Created by Toni Axelsson on 2014-05-25.
//
//

#include "layout.h"
#include "glwidget.h"

QvisLayout::QvisLayout()
{
    std::cout << "This comes from the GUI" << std::endl;
    createAccBox();
    createAngBox();
    createAltBox();
    createConnectBox();
    createVideoBox();
    createOrientationBox();
    createControls();
    
    createPIDWindow();
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(gridVideoBox, 0, 0, 1, 2);
    mainLayout->addWidget(gridOrientationBox, 0, 2, 1, 2);
    mainLayout->addWidget(gridControls,1,2,3,2);
    mainLayout->addWidget(gridAccBox, 1, 0, 1, 1);
    mainLayout->addWidget(gridAngBox, 1, 1, 1, 1);
    mainLayout->addWidget(gridAltBox,2,0,1,2);
    mainLayout->addWidget(connectGroupBox, 3, 0, 1, 2);
    setLayout(mainLayout);
    setWindowTitle(tr("Qvis v0.3 (alpha)"));
    setFixedSize(700, 650);
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

void QvisLayout::createAltBox() {
    gridAltBox = new QGroupBox(tr("Altitude"));
    QGridLayout *layout = new QGridLayout;
    
    altLabel = new QLabel(tr("Current Altitude"));
    desiredAlt = new QDoubleSpinBox;
    desiredAlt->setRange(0.0, 2.0);
    desiredAlt->setSingleStep(0.1);
    desiredAlt->setValue(0.0);
    
    QLabel *desiredAltLabel = new QLabel(tr("Desired Altitude"));
    QLabel *currentAlt = new QLabel(tr("0"));
                                         
    layout->addWidget(altLabel,0,0);
    layout->addWidget(currentAlt,1,0);
    layout->addWidget(desiredAltLabel,0,1);
    layout->addWidget(desiredAlt,1,1);
    
    gridAltBox->setLayout(layout);
    
}

void QvisLayout::createVideoBox() {
    
    gridVideoBox = new QGroupBox(tr("Camera"));
    gridVideoBox->setFixedSize(320, 240);
    videoLabel = new QLabel(tr("No Video Stream Available"));
    videoLabel->setAlignment(Qt::AlignCenter);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(videoLabel);
    gridVideoBox->setLayout(layout);
}

void QvisLayout::createOrientationBox(){
    
    gridOrientationBox = new QGroupBox(tr("Orientation"));
    gridOrientationBox->setFixedSize(320, 240);
}

void QvisLayout::createControls() {
    gridControls = new QGroupBox(tr("Controls"));
    QGridLayout *layout = new QGridLayout;
    
    QGroupBox *movementBox = new QGroupBox(tr("Vertical Thrust"));
    QGroupBox *videoBox = new QGroupBox(tr("Video"));
    QGroupBox *commandsBox = new QGroupBox(tr("Commands"));
    
    QVBoxLayout *videoLayout = new QVBoxLayout;
    QVBoxLayout *thrustLayout = new QVBoxLayout;
    QVBoxLayout *commandsLayout = new QVBoxLayout;

    
    // Labels
    QLabel *fpsLabel = new QLabel(tr("Set FPS"));
    fpsLabel->setAlignment(Qt::AlignBottom);
    
    // Slider
    verticalThrustSlider = new QSlider(Qt::Vertical,0);
    verticalThrustSlider->setRange(0.0, 100.0);
    
    videoFPSSlider = new QSlider(Qt::Horizontal,0);
    videoFPSSlider->setRange(1, 5);
    videoFPSSlider->setTickInterval(1);
    
    // Spinbox
    verticalThrustSpin = new QSpinBox;
    verticalThrustSpin->setRange(0, 100);
    verticalThrustSpin->setSingleStep(1);
    verticalThrustSpin->setValue(0);
    
    // Buttons
    takeOfButton = new QPushButton(tr("Take Off"));
    landButton = new QPushButton(tr("Land"));
    videoButton = new QPushButton(tr("Video On"));
    stopButton = new QPushButton(tr("STOP"));
    stopButton->setStyleSheet("QPushButton { color : red; }");
    altitudeLock = new QPushButton(tr("Lock Altitude"));
    pidButton = new QPushButton(tr("PID Parameters"));
    
    connect(verticalThrustSpin, SIGNAL(valueChanged(int)),verticalThrustSlider,SLOT(setValue(int)) );
    connect(verticalThrustSlider,SIGNAL(valueChanged(int)),verticalThrustSpin,SLOT(setValue(int)) );
    
    thrustLayout->addWidget(verticalThrustSlider);
    thrustLayout->addWidget(verticalThrustSpin);
    
    videoLayout->addWidget(fpsLabel);
    videoLayout->addWidget(videoFPSSlider);
    videoLayout->addWidget(videoButton);
    
    commandsLayout->addWidget(pidButton);
    commandsLayout->addWidget(altitudeLock);
    commandsLayout->addWidget(takeOfButton);
    commandsLayout->addWidget(landButton);
    commandsLayout->addWidget(stopButton);
    
    movementBox->setLayout(thrustLayout);
    videoBox->setLayout(videoLayout);
    commandsBox->setLayout(commandsLayout);
    
    videoBox->setFixedHeight(110);
    
    layout->addWidget(videoBox,0,0);
    layout->addWidget(commandsBox,1,0);
    layout->addWidget(movementBox,0,1,2,1);
    
    gridControls->setLayout(layout);
}

void QvisLayout::createConnectBox()
{
    connectGroupBox = new QGroupBox(tr("TCP Connection"));
    connectLayout = new QGridLayout;
    connectLabel = new QLabel(tr("Not connected"));
    connectLabel->setStyleSheet("QLabel { color : red; }");
    connectLabel->setAlignment(Qt::AlignCenter);
    
    infoLabel = new QLabel(tr("Enter IP and Port and click connect"));
    infoLabel->setAlignment(Qt::AlignCenter);
    QFont font;
	font.setPointSize(9);
    infoLabel->setFont(font);
    
    ipLabel = new QLabel(tr("Ip:"));
    portLabel = new QLabel(tr("Port:"));
    ipLabel->setAlignment(Qt::AlignRight);
    portLabel->setAlignment(Qt::AlignRight);
    
    ipField = new QLineEdit;
    ipField->setText("10.0.1.8");
    portField = new QLineEdit;
    portField->setText("3490");
    connectButton = new QPushButton(tr("Connect to Atlas"));
        
    connectLayout->addWidget(connectLabel, 0, 0, 1, 3);
    connectLayout->addWidget(infoLabel, 1, 0, 1, 3);
    connectLayout->addWidget(ipLabel, 2, 0, 1, 1);
    connectLayout->addWidget(ipField, 2, 1, 1, 1);
    connectLayout->addWidget(portLabel, 3, 0, 1, 1);
    connectLayout->addWidget(portField, 3, 1, 1, 1);
    connectLayout->addWidget(connectButton, 4, 0, 1, 3);
    
    connectGroupBox->setLayout(connectLayout);
}

void QvisLayout::createPIDWindow() {
    pidWindow = new QDialog;
    QGridLayout *layout = new QGridLayout;
    setPIDButton = new QPushButton(tr("Set Parameters"));
    pLabel = new QLabel(tr("P:"));
    iLabel = new QLabel(tr("I:"));
    dLabel = new QLabel(tr("D:"));
    
    pField = new QLineEdit();
    iField = new QLineEdit();
    dField = new QLineEdit();
    
    pField->setText("0.0");
    iField->setText("0.0");
    dField->setText("0.0");
    
    layout->addWidget(pLabel,0,0);
    layout->addWidget(iLabel,1,0);
    layout->addWidget(dLabel,2,0);
    layout->addWidget(pField,0,1);
    layout->addWidget(iField,1,1);
    layout->addWidget(dField,2,1);
    layout->addWidget(setPIDButton,3,0,1,2);
    
    pidWindow->setLayout(layout);
}

void QvisLayout::openPIDWindow() {
    pidWindow->show();
}

void QvisLayout::closePIDWindow() {
    pidWindow->close();
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
    connectLabel->setText("Connected to: " + ipField->text());
    ipField->setDisabled(true);
    portField->setDisabled(true);
}

void QvisLayout::setDataFields(QStringList strList)
{
    valAcc[0]->setText(strList.value(0).left(5));
    valAcc[1]->setText(strList.value(1).left(5));
    valAcc[2]->setText(strList.value(2).left(5));
    valAng[0]->setText(strList.value(3).left(5));
    valAng[1]->setText(strList.value(4).left(5));
    valAng[2]->setText(strList.value(5).left(5));
}

void QvisLayout::setInfoText(QString s) {
    infoLabel->setText(s);
}

void QvisLayout::updateImg(QImage img) {
    videoLabel->setPixmap(QPixmap::fromImage(img));
}

int QvisLayout::getPort()
{
    return portField->text().toInt();
}

QString QvisLayout::getIp()
{
    return ipField->text();
}

int QvisLayout::getThrustValue() {
    return verticalThrustSlider->value();
}

int QvisLayout::getFPSValue() {
    return videoFPSSlider->value();
}

void QvisLayout::getPIDValues(double *pid) {
    pid[0] = 0.0;
    pid[1] = 0.0;
    pid[2] = 0.0;
}

