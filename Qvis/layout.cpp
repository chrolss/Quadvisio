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
    createPowerBox();
    createConnectBox();
    createVideoBox();
    createMovementBox();
    createControls();
    
    createPIDWindow();
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(gridVideoBox, 0, 2, 2, 2);
    mainLayout->addWidget(gridAccBox, 2, 0, 1, 1);
    mainLayout->addWidget(gridAngBox, 2, 1, 1, 1);
    mainLayout->addWidget(batteryBox,3,0,1,2);
    mainLayout->addWidget(connectGroupBox, 4, 0, 1, 2);
    
    mainLayout->addWidget(gridOrientationBox, 0, 0, 2, 2);
    mainLayout->addWidget(mapBox,0,4,2,2);
    //mainLayout->addWidget(altitudeBox,1,2,1,1);
    //mainLayout->addWidget(speedBox,1,3,1,1);
    mainLayout->addWidget(gridControls,2,2,3,2);
    setLayout(mainLayout);
    setWindowTitle(tr("Qvis v0.4 (alpha)"));
    setFixedSize(1030, 660);
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

void QvisLayout::createPowerBox() {
    batteryBox = new QGroupBox(tr("Power"));
    QGridLayout *layout = new QGridLayout;
    
    voltageHeaderLabel = new QLabel(tr("Voltage"));
    QLabel *currentHeaderLabel = new QLabel(tr("Current"));
    QLabel *consumeHeaderLabel = new QLabel(tr("Consumption"));
    
    QLabel *currentValueLabel = new QLabel(tr("0.0 A"));
    QLabel *voltageValueLabel = new QLabel(tr("0.0 V"));
    QLabel *consumeValueLabel = new QLabel(tr("0.0 mAh"));
    
    currentHeaderLabel->setAlignment(Qt::AlignCenter);
    voltageValueLabel->setAlignment(Qt::AlignCenter);
    voltageHeaderLabel->setAlignment(Qt::AlignCenter);
    currentValueLabel->setAlignment(Qt::AlignCenter);
    consumeValueLabel->setAlignment(Qt::AlignCenter);
    consumeHeaderLabel->setAlignment(Qt::AlignCenter);
                                         
    layout->addWidget(voltageHeaderLabel,0,0);
    layout->addWidget(voltageValueLabel,1,0);
    layout->addWidget(currentHeaderLabel,0,1);
    layout->addWidget(currentValueLabel,1,1);
    layout->addWidget(consumeHeaderLabel,0,2);
    layout->addWidget(consumeValueLabel,1,2);
    
    batteryBox->setLayout(layout);
    
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

void QvisLayout::createMovementBox(){
    
    gridOrientationBox = new QGroupBox(tr("Orientation"));
    gridOrientationBox->setFixedSize(320, 240);
    mapBox = new QGroupBox(tr("Map"));
    mapBox->setFixedSize(320, 240);
    altitudeBox = new QGroupBox(tr("Altitude"));
    speedBox = new QGroupBox(tr("Speed"));
    
    QWebView *gView = new QWebView(this);
    gView->settings()->setAttribute( QWebSettings::JavascriptEnabled, true );
    QString fileName = "/Users/toniaxelsson/Documents/Kod/Qt/Qvis/data/map.html";
    
    QVBoxLayout *mapLayout = new QVBoxLayout(this);
    
    QUrl url = QUrl::fromLocalFile(fileName);
    gView->load(url);
    mapLayout->addWidget(gView);
    mapBox->setLayout(mapLayout);
}

void QvisLayout::createControls() {
    gridControls = new QGroupBox(tr("Controls"));
    QGridLayout *layout = new QGridLayout;
    
    QGroupBox *movementBox = new QGroupBox(tr("Vertical Thrust"));
    QGroupBox *videoBox = new QGroupBox(tr("Video"));
    QGroupBox *commandsBox = new QGroupBox(tr("Commands"));
    QGroupBox *parametersBox = new QGroupBox(tr("Parameters"));
    
    QVBoxLayout *videoLayout = new QVBoxLayout;
    QVBoxLayout *thrustLayout = new QVBoxLayout;
    QVBoxLayout *commandsLayout = new QVBoxLayout;
    QVBoxLayout *paramLayout = new QVBoxLayout;

    
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
    motorButton = new QPushButton(tr("Motor On"));
    altitudeLock = new QPushButton(tr("Lock Altitude"));
    pidButton = new QPushButton(tr("PID Parameters"));
    
    connect(verticalThrustSpin, SIGNAL(valueChanged(int)),verticalThrustSlider,SLOT(setValue(int)) );
    connect(verticalThrustSlider,SIGNAL(valueChanged(int)),verticalThrustSpin,SLOT(setValue(int)) );
    
    thrustLayout->addWidget(verticalThrustSlider);
    thrustLayout->addWidget(verticalThrustSpin);
    
    videoLayout->addWidget(fpsLabel);
    videoLayout->addWidget(videoFPSSlider);
    videoLayout->addWidget(videoButton);
    
    commandsLayout->addWidget(altitudeLock);
    commandsLayout->addWidget(takeOfButton);
    commandsLayout->addWidget(landButton);
    commandsLayout->addWidget(motorButton);
    
    paramLayout->addWidget(pidButton);
    
    parametersBox->setLayout(paramLayout);
    movementBox->setLayout(thrustLayout);
    videoBox->setLayout(videoLayout);
    commandsBox->setLayout(commandsLayout);
    
    //videoBox->setFixedHeight(110);
    
    layout->addWidget(videoBox,0,0);
    layout->addWidget(commandsBox,1,0);
    layout->addWidget(parametersBox,2,0);
    layout->addWidget(movementBox,0,1,3,1);
    
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
    ipField->setText("10.0.1.12");
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
    
    QGroupBox *rollBox = new QGroupBox(tr("Roll"));
    QGroupBox *pitchBox = new QGroupBox(tr("Pitch"));
    QGroupBox *yawBox = new QGroupBox(tr("Yaw"));
    
    QGridLayout *layout = new QGridLayout;
    QGridLayout *rollLayout = new QGridLayout;
    QGridLayout *pitchLayout = new QGridLayout;
    QGridLayout *yawLayout = new QGridLayout;
    
    setPIDButton = new QPushButton(tr("Set Parameters"));
    pRollLabel = new QLabel(tr("P:"));
    iRollLabel = new QLabel(tr("I:"));
    dRollLabel = new QLabel(tr("D:"));
    pPitchLabel = new QLabel(tr("P:"));
    iPitchLabel = new QLabel(tr("I:"));
    dPitchLabel = new QLabel(tr("D:"));
    pYawLabel = new QLabel(tr("P:"));
    iYawLabel = new QLabel(tr("I:"));
    dYawLabel = new QLabel(tr("D:"));
    
    pRollField = new QLineEdit(tr("0.17"));
    iRollField = new QLineEdit(tr("0.04"));
    dRollField = new QLineEdit(tr("0.11"));
    
    pPitchField = new QLineEdit(tr("0.17"));
    iPitchField = new QLineEdit(tr("0.04"));
    dPitchField = new QLineEdit(tr("0.11"));
    
    pYawField = new QLineEdit(tr("0.0"));
    iYawField = new QLineEdit(tr("0.0"));
    dYawField = new QLineEdit(tr("0.0"));
    
    rollLayout->addWidget(pRollLabel,0,0);
    rollLayout->addWidget(iRollLabel,1,0);
    rollLayout->addWidget(dRollLabel,2,0);
    rollLayout->addWidget(pRollField,0,1);
    rollLayout->addWidget(iRollField,1,1);
    rollLayout->addWidget(dRollField,2,1);
    
    pitchLayout->addWidget(pPitchLabel,0,0);
    pitchLayout->addWidget(iPitchLabel,1,0);
    pitchLayout->addWidget(dPitchLabel,2,0);
    pitchLayout->addWidget(pPitchField,0,1);
    pitchLayout->addWidget(iPitchField,1,1);
    pitchLayout->addWidget(dPitchField,2,1);
    
    yawLayout->addWidget(pYawLabel,0,0);
    yawLayout->addWidget(iYawLabel,1,0);
    yawLayout->addWidget(dYawLabel,2,0);
    yawLayout->addWidget(pYawField,0,1);
    yawLayout->addWidget(iYawField,1,1);
    yawLayout->addWidget(dYawField,2,1);
    
    rollBox->setLayout(rollLayout);
    pitchBox->setLayout(pitchLayout);
    yawBox->setLayout(yawLayout);
    
    layout->addWidget(rollBox,0,0);
    layout->addWidget(pitchBox,0,1);
    layout->addWidget(yawBox,0,2);
    layout->addWidget(setPIDButton,4,1,1,1);
    
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

QString QvisLayout::getPIDString() {
    
    return pRollField->text() + ":" + iRollField->text() + ":" + dRollField->text() + ":" + pPitchField->text() + ":" + iPitchField->text() + ":" +
    dPitchField->text() + ":" + pYawField->text() + ":" + iYawField->text() + ":" + dYawField->text();
}

