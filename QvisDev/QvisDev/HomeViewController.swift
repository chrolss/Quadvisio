//
//  File.swift
//  QvisDev
//
//  Created by Toni Axelsson on 2014-09-11.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

import Foundation

import UIKit
import MapKit

class HomeViewController: UIViewController, JoystickDelegate, tcpProtocol {
    
    @IBOutlet weak var rightJoystickView: Joystick!
    @IBOutlet weak var leftJoystickView: Joystick!
    
    @IBOutlet weak var bottomView: UIView!
    @IBOutlet weak var bottomRightView: UIView!
    @IBOutlet weak var bottomLeftView: UIView!
    
    @IBOutlet weak var middleRightView: UIView!
    @IBOutlet weak var angleView: UIView!
    @IBOutlet weak var levelView: UIView!
    @IBOutlet weak var headingView: UIView!
    @IBOutlet weak var directionImage: UIImageView!
    @IBOutlet weak var directionRefImage: UIImageView!
    @IBOutlet weak var levelImage: UIImageView!
    @IBOutlet weak var levelRefImage: UIImageView!
    
    @IBOutlet weak var middleLeftView: UIView!
    @IBOutlet weak var gpsView: UIView!
    @IBOutlet weak var mapView: MKMapView!
    
    @IBOutlet weak var topLeftView: UIView!
    @IBOutlet weak var cameraView: UIImageView!
    @IBOutlet weak var cameraControlView: UIView!
    
    @IBOutlet weak var topRightView: UIView!
    @IBOutlet weak var messageView: UITextView!
    @IBOutlet weak var atlasView: UIView!
    
    @IBOutlet weak var topView: UIView!
    
    @IBOutlet weak var colorButton: UIButton!
    @IBOutlet weak var videoButton: UIButton!
    @IBOutlet weak var photoButton: UIButton!
    @IBOutlet weak var disconnectButton: UIButton!
    @IBOutlet weak var motorButton: UIButton!
    
    @IBOutlet weak var atlasFreqLabel: UILabel!
    @IBOutlet weak var videoLabel: UILabel!
    @IBOutlet weak var LFLabel: UILabel!
    @IBOutlet weak var RFLabel: UILabel!
    @IBOutlet weak var RRLabel: UILabel!
    @IBOutlet weak var LRLabel: UILabel!
    @IBOutlet weak var altLabel: UILabel!
    @IBOutlet weak var rollLabel: UILabel!
    @IBOutlet weak var pitchLabel: UILabel!
    @IBOutlet weak var yawLabel: UILabel!
    @IBOutlet weak var rollRefLabel: UILabel!
    @IBOutlet weak var pitchRefLabel: UILabel!
    @IBOutlet weak var yawRefLabel: UILabel!
    @IBOutlet weak var tcpFreqLabel: UILabel!
    
    @IBOutlet weak var fpsSlider: UISlider!
    
    let blueColor: UIColor = UIColor(red: 0.0/255.0, green: 80.0/255.0, blue: 200.0/255.0, alpha: 1.0)
    
    let blueColorLight: UIColor = UIColor(red: 120.0/255.0, green: 190.0/255.0, blue: 255.0/255.0, alpha: 1.0)
    
    var videoOn: Bool = false
    var colorVideo: Bool = true
    var motorOn: Bool = false
    
    var start: NSDate = NSDate()
    var end: NSDate = NSDate()
    var tcpFreqArray = [Double](count: 20, repeatedValue: 0.0)
    var tcpCount: Int = 0
    
    @IBAction func fpsSliderChanged(sender: AnyObject) {
        var newStep: Float = roundf(fpsSlider.value/1.0)
        fpsSlider.setValue(newStep*1.0, animated: false)
    }
    
    @IBAction func motorButtonPushed(sender: AnyObject) {
        if(motorOn) {
            motorOn = false
            motorButton.layer.backgroundColor = UIColor.whiteColor().CGColor
        }
        else {
            motorOn = true
            motorButton.layer.backgroundColor = blueColorLight.CGColor
        }
    }
    
    @IBAction func videoButtonPushed(sender: AnyObject) {
        if(videoOn) {
            videoOn = false
            videoLabel.hidden = false
            cameraView.image = nil
            videoButton.layer.backgroundColor = UIColor.whiteColor().CGColor
        }
        else {
            videoOn = true
            videoLabel.hidden = true
            videoButton.layer.backgroundColor = blueColorLight.CGColor
        }
    }
    @IBAction func colorButtonPushed(sender: AnyObject) {
        if(colorVideo) {
            colorVideo = false
            colorButton.layer.backgroundColor = UIColor.whiteColor().CGColor
        }
        else {
            colorButton.layer.backgroundColor = blueColorLight.CGColor
            colorVideo = true
        }
    }
    @IBAction func disconnectButtonPushed(sender: AnyObject) {
        tcp!.closeConnection()
        //self.performSegueWithIdentifier("toLoginView", sender: self)
        self.dismissViewControllerAnimated(true, completion: nil)

    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        tcp?.tcpDelegate = self
        
        bottomLeftView.layer.borderColor = blueColor.CGColor
        bottomLeftView.layer.borderWidth = 2.0
        bottomLeftView.layer.cornerRadius = 10.0
        
        bottomRightView.layer.borderColor = blueColor.CGColor
        bottomRightView.layer.borderWidth = 2.0
        bottomRightView.layer.cornerRadius = 10.0
        
        angleView.layer.borderColor = blueColor.CGColor
        angleView.layer.borderWidth = 2.0
        angleView.layer.cornerRadius = 10.0
        
        levelView.layer.borderColor = blueColor.CGColor
        levelView.layer.borderWidth = 2.0
        levelView.layer.cornerRadius = 10.0
        
        headingView.layer.borderColor = blueColor.CGColor
        headingView.layer.borderWidth = 2.0
        headingView.layer.cornerRadius = 10.0
        
        gpsView.layer.borderColor = blueColor.CGColor
        gpsView.layer.borderWidth = 2.0
        gpsView.layer.cornerRadius = 10.0
        
        cameraView.layer.borderColor = blueColor.CGColor
        cameraView.layer.borderWidth = 2.0
        cameraView.layer.cornerRadius = 10.0
        
        cameraControlView.layer.borderColor = blueColor.CGColor
        cameraControlView.layer.borderWidth = 2.0
        cameraControlView.layer.cornerRadius = 10.0
        
        mapView.layer.borderColor = blueColor.CGColor
        mapView.layer.cornerRadius = 10.0
        mapView.layer.borderWidth = 1.0
        
        atlasView.layer.borderColor = blueColor.CGColor
        atlasView.layer.borderWidth = 2.0
        atlasView.layer.cornerRadius = 10.0
        
        messageView.layer.borderColor = blueColor.CGColor
        messageView.layer.borderWidth = 2.0
        messageView.layer.cornerRadius = 10.0
        
        bottomView.layer.cornerRadius = 20.0
        bottomView.layer.backgroundColor = UIColor.whiteColor().CGColor
        
        middleRightView.layer.cornerRadius = 20.0
        middleRightView.layer.backgroundColor = UIColor.whiteColor().CGColor
        
        middleLeftView.layer.cornerRadius = 20.0
        middleLeftView.layer.backgroundColor = UIColor.whiteColor().CGColor
        
        topLeftView.layer.cornerRadius = 20.0
        topLeftView.layer.backgroundColor = UIColor.whiteColor().CGColor
        
        topRightView.layer.cornerRadius = 20.0
        topRightView.layer.backgroundColor = UIColor.whiteColor().CGColor
        
        topView.layer.cornerRadius = 20.0
        topView.layer.backgroundColor = UIColor.whiteColor().CGColor
    
        videoButton.layer.borderColor = blueColor.CGColor
        videoButton.layer.borderWidth = 1.0
        videoButton.layer.cornerRadius = 10.0
        
        colorButton.layer.borderColor = blueColor.CGColor
        colorButton.layer.borderWidth = 1.0
        colorButton.layer.cornerRadius = 10.0
        colorButton.layer.backgroundColor = blueColorLight.CGColor
        
        photoButton.layer.borderColor = blueColor.CGColor
        photoButton.layer.borderWidth = 1.0
        photoButton.layer.cornerRadius = 10.0
        
        disconnectButton.layer.borderColor = blueColor.CGColor
        disconnectButton.layer.borderWidth = 1.0
        disconnectButton.layer.cornerRadius = 10.0
        
        motorButton.layer.borderColor = blueColor.CGColor
        motorButton.layer.borderWidth = 1.0
        motorButton.layer.cornerRadius = 10.0
        
        leftJoystickView.delegate = self
        rightJoystickView.delegate = self
        
        leftJoystickView.initialize(false, verticalReturn: true, longLayout: false, start: .bottom, verticalDeadZone: 0, horizontalDeadZone: 20.0)
        rightJoystickView.initialize(true, verticalReturn: true, longLayout: false, start: .middle, verticalDeadZone: 0, horizontalDeadZone: 0.0)
        
        leftJoystickView.layer.backgroundColor = UIColor.clearColor().CGColor
        
        rightJoystickView.layer.backgroundColor = UIColor.clearColor().CGColor
        
        fpsSlider.maximumValue = 3.0
        fpsSlider.minimumValue = 0.0
        fpsSlider.setValue(2.0, animated: false)

    }
    
    func updateView(x: CGFloat, y: CGFloat) {
        
    }
    
    func setRecivedData(data: [Double], errorMsg: String) {
        
        end = NSDate()
        let timeInterval: Double = end.timeIntervalSinceDate(start)
        
        tcpFreqLabel.text = NSString(format: "%.01f", calcTCPAverageValue(timeInterval))
        
        rollLabel.text = NSString(format: "%.02f", data[0])
        pitchLabel.text = NSString(format: "%.02f", data[1])
        yawLabel.text = NSString(format: "%.01f", data[2])
        rollRefLabel.text = NSString(format: "%.01f", data[3])
        pitchRefLabel.text = NSString(format: "%.01f", data[4])
        yawRefLabel.text = NSString(format: "%.01f", data[5])
        
        // Set direction
        directionImage.transform = CGAffineTransformMakeRotation(CGFloat(data[2]*M_PI/180.0))
        directionRefImage.transform = CGAffineTransformMakeRotation(CGFloat(data[5]*M_PI/180.0))
        
        levelImage.transform = CGAffineTransformMakeRotation(CGFloat(data[0]*M_PI/180.0))
        
        LFLabel.text = NSString(format: "%.01f", data[6])
        RFLabel.text = NSString(format: "%.01f", data[7])
        RRLabel.text = NSString(format: "%.01f", data[8])
        LRLabel.text = NSString(format: "%.01f", data[9])
        
        altLabel.text = NSString(format: "%.01f", data[12])

        atlasFreqLabel.text = NSString(format: "%.01f", data[13]) + "Hz"
        
        messageView.text = messageView.text.stringByAppendingString(errorMsg)
        
        start = NSDate()
    }
    
    func setRecivedImage(image: UIImage) {
        if(videoOn){
            println("Setting image")
            cameraView.image = image
        }
        else {
            cameraView.image = nil
        }

    }
    
    func getSendData() -> String {
        
        var rightJoystickValues = rightJoystickView.getJoystickPosition()
        var leftJoystickValues = leftJoystickView.getJoystickPosition()
        
        var msg: String = ""
        
        msg = ":\(Float(rightJoystickValues.dx)):\(rightJoystickValues.dy):\(leftJoystickValues.dx):\(leftJoystickValues.dy):"
        
        if(videoOn) {
            msg += "1:"
        }
            
        else {
            msg += "0:"
        }
        
        if(colorVideo) {
            msg += "1:"
        }
        else {
            msg += "0:"
        }
        
        msg += "\(fpsSlider.value):"
        
        if(motorOn) {
            msg += "1"
        }
        else {
            msg += "0"
        }
        
        if(countElements(msg)>=10 && countElements(msg)<100) {
            return "0\(countElements(msg))" + msg
        }
        else if(countElements(msg)>=100) {
            return "\(countElements(msg))" + msg
        }
        else {
            return "00\(countElements(msg))" + msg
        }

    }
    
    func getIdentityMsg() -> String {
        
        var identity = ":3:\(UIDevice.currentDevice().name)"
        
        if(countElements(identity)>=10 && countElements(identity)<100) {
            return "0\(countElements(identity))" + identity
        }
        else if(countElements(identity)>=100) {
            return "\(countElements(identity))" + identity
        }
        else {
            return "00\(countElements(identity))" + identity
        }
    }
    
    func calcTCPAverageValue(time: Double) -> Double {
        
        if(tcpCount==20) {
            tcpCount = 0
        }
        tcpFreqArray[tcpCount] = time
        
        var sum: Double = 0.0
        
        for element in tcpFreqArray {
            sum += element
        }
        tcpCount++
        return Double(tcpFreqArray.count) / sum
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
}