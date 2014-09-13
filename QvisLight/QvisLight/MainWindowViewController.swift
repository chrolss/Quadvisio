//
//  MainWindowViewController.swift
//  QvisLight
//
//  Created by Toni Axelsson on 2014-09-01.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

import UIKit
import AudioToolbox
import MapKit

class MainWindowViewController: UIViewController, JoystickDelegate, tcpProtocol {
    
    @IBOutlet weak var rightJoystickView: Joystick!
    @IBOutlet weak var leftJoystickView: Joystick!
    
    @IBOutlet weak var cameraView: UIImageView!
    
    @IBOutlet weak var rightView: UIView!
    @IBOutlet weak var middleView: UIView!
    @IBOutlet weak var leftView: UIView!
    @IBOutlet weak var topView: UIView!
    @IBOutlet weak var videoControlView: UIView!
    @IBOutlet weak var motorControlView: UIView!
    @IBOutlet weak var rightMiddleView: UIView!
    @IBOutlet weak var leftMiddleView: UIView!
    @IBOutlet weak var backgroundView: UIView!
    
    @IBOutlet weak var disconnectButton: UIButton!
    @IBOutlet weak var videoButton: UIButton!
    @IBOutlet weak var photoButton: UIButton!
    @IBOutlet weak var motorButton: UIButton!
    @IBOutlet weak var landButton: UIButton!
    @IBOutlet weak var takeoffButon: UIButton!
    @IBOutlet weak var lockAltitudeButon: UIButton!
    @IBOutlet weak var darkModeButton: UIButton!
    @IBOutlet weak var colorButton: UIButton!
    
    @IBOutlet weak var rollLabel: UILabel!
    @IBOutlet weak var pitchLabel: UILabel!
    @IBOutlet weak var yawLabel: UILabel!
    
    @IBOutlet weak var fpsSlider: UISlider!
    
    @IBOutlet weak var mapView: MKMapView!
    @IBOutlet weak var videoIndicator: UIActivityIndicatorView!
    
    var videoOn: Bool = false
    var motorOn: Bool = false
    var darkMode: Bool = false
    var colorVideo: Bool = true
    
    var soundID: SystemSoundID = 0
    
    @IBAction func changeColorMode(sender: AnyObject) {
        
        if(darkMode) {
            darkModeButton.setTitle("Dark Mode", forState: UIControlState.Normal)
            videoControlView.layer.borderColor = UIColor.whiteColor().CGColor
            videoControlView.layer.backgroundColor = design.lightViewColor.CGColor
            
            motorControlView.layer.borderColor = UIColor.whiteColor().CGColor
            motorControlView.layer.backgroundColor = design.lightViewColor.CGColor
            
            leftMiddleView.layer.borderColor = UIColor.whiteColor().CGColor
            leftMiddleView.layer.backgroundColor = design.lightViewColor.CGColor
            
            rightMiddleView.layer.borderColor = UIColor.whiteColor().CGColor
            rightMiddleView.layer.backgroundColor = design.lightViewColor.CGColor
            
            leftView.layer.backgroundColor = design.lightViewColor.CGColor
            rightView.layer.backgroundColor = design.lightViewColor.CGColor
            middleView.layer.backgroundColor = design.lightViewColor.CGColor
            topView.layer.backgroundColor = design.lightViewColor.CGColor
            backgroundView.layer.backgroundColor = UIColor.whiteColor().CGColor
            cameraView.alpha = 1.0
            
            leftJoystickView.layer.backgroundColor = UIColor.whiteColor().CGColor
            rightJoystickView.layer.backgroundColor = UIColor.whiteColor().CGColor
            
            leftJoystickView.bgImageView?.image = UIImage(named: "regular_joystick_bg")
            rightJoystickView.bgImageView?.image = UIImage(named: "regular_joystick_bg")
            
            if(videoOn) {
                videoButton.layer.backgroundColor = design.buttonPushedColorLight.CGColor
                videoButton.layer.borderColor = design.buttonPushedColorLight.CGColor
            }
            
            darkMode = false
        }
        else {
            darkModeButton.setTitle("Light Mode", forState: UIControlState.Normal)

            videoControlView.layer.borderColor = UIColor.lightGrayColor().CGColor
            videoControlView.layer.backgroundColor = design.darkViewColor.CGColor

            motorControlView.layer.borderColor = UIColor.lightGrayColor().CGColor
            motorControlView.layer.backgroundColor = design.darkViewColor.CGColor

            leftMiddleView.layer.borderColor = UIColor.lightGrayColor().CGColor
            leftMiddleView.layer.backgroundColor = design.darkViewColor.CGColor

            rightMiddleView.layer.borderColor = UIColor.lightGrayColor().CGColor
            rightMiddleView.layer.backgroundColor = design.darkViewColor.CGColor

            leftView.layer.backgroundColor = design.darkViewColor.CGColor
            rightView.layer.backgroundColor = design.darkViewColor.CGColor
            middleView.layer.backgroundColor = design.darkViewColor.CGColor
            topView.layer.backgroundColor = design.darkViewColor.CGColor
            backgroundView.layer.backgroundColor = design.darkBackgroundColor.CGColor
            
            leftJoystickView.layer.backgroundColor = design.darkBackgroundColor.CGColor
            rightJoystickView.layer.backgroundColor = design.darkBackgroundColor.CGColor
            leftJoystickView.bgImageView?.image = UIImage(named: "regular_joystick_bg_dark")
            rightJoystickView.bgImageView?.image = UIImage(named: "regular_joystick_bg_dark")
            
            if(videoOn) {
                videoButton.layer.backgroundColor = design.buttonPushedColorDark.CGColor
                videoButton.layer.borderColor = design.buttonPushedColorDark.CGColor
            }
            else {
                cameraView.alpha = 0.1
            }
            
            darkMode = true
        }
    }
    @IBAction func photoButtonPushed(sender: AnyObject) {
        AudioServicesPlaySystemSound(soundID)
    }
    
    @IBAction func disconnect(sender: AnyObject) {
        
        
        while(!tcp!.canClose()) {
            
        }
        
        tcp!.closeConnection()

        self.performSegueWithIdentifier("toLoginView", sender: self)
    }
    
    @IBAction func videoButtonPushed(sender: AnyObject) {
        if(videoOn) {
            design.designButton(&videoButton)
            videoButton.setTitle("Video Off", forState: UIControlState.Normal)
            videoOn = false
            cameraView.image = UIImage(named: "ios_logo_opeque_center")
            if(darkMode) {
                cameraView.alpha = 0.1
            }
        }
        else {
            if(darkMode) {
                videoButton.layer.backgroundColor = design.buttonPushedColorDark.CGColor
                videoButton.layer.borderColor = design.buttonPushedColorDark.CGColor
                cameraView.alpha = 1.0
            }
            else {
                videoButton.layer.backgroundColor = design.buttonPushedColorLight.CGColor
                videoButton.layer.borderColor = design.buttonPushedColorLight.CGColor
            }
            
            videoButton.setTitle("Video On", forState: UIControlState.Normal)
            videoOn = true
            videoIndicator.hidden = false
            videoIndicator.startAnimating()
        }
    }
    
    @IBAction func motorButtonPushed(sender: AnyObject) {
        if(motorOn) {
            design.designButton(&motorButton)
            motorButton.setTitle("Motor Off", forState: UIControlState.Normal)
            motorOn = false
        }
        else {
            motorButton.layer.backgroundColor = design.buttonPushedColorLight.CGColor
            motorButton.layer.borderColor = design.buttonPushedColorLight.CGColor
            motorButton.setTitle("Motor On", forState: UIControlState.Normal)
            motorOn = true
        }
    }
    
    @IBAction func colorButtonPushed(sender: AnyObject) {
        if(colorVideo) {
            colorVideo = false
            colorButton.setImage(UIImage(named: "bw_icon"), forState: UIControlState.Normal)
        }
        else {
            colorVideo = true
            colorButton.setImage(UIImage(named: "color_icon"), forState: UIControlState.Normal)
        }
    }
    
    @IBAction func fpsSliderChanged(sender: AnyObject) {
        var newStep: Float = roundf(fpsSlider.value/1.0)
        fpsSlider.setValue(newStep*1.0, animated: false)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        var soundURL: NSURL = NSURL(fileURLWithPath: NSBundle.mainBundle().pathForResource("camera_shutter", ofType: "mp3")!)
        AudioServicesCreateSystemSoundID(soundURL as CFURLRef, &soundID)
        
        leftView.layer.cornerRadius = 20
        rightView.layer.cornerRadius = 20
        middleView.layer.cornerRadius = 20
        topView.layer.cornerRadius = 20
        
        videoControlView.layer.borderColor = UIColor.whiteColor().CGColor
        videoControlView.layer.borderWidth = 1.0
        videoControlView.layer.cornerRadius = 20
        motorControlView.layer.borderColor = UIColor.whiteColor().CGColor
        motorControlView.layer.borderWidth = 1.0
        motorControlView.layer.cornerRadius = 20
        leftMiddleView.layer.borderColor = UIColor.whiteColor().CGColor
        leftMiddleView.layer.borderWidth = 1.0
        leftMiddleView.layer.cornerRadius = 20
        rightMiddleView.layer.borderColor = UIColor.whiteColor().CGColor
        rightMiddleView.layer.borderWidth = 1.0
        rightMiddleView.layer.cornerRadius = 20
        
        design.designButton(&videoButton)
        design.designButton(&photoButton)
        design.designButton(&motorButton)
        design.designButton(&landButton)
        design.designButton(&takeoffButon)
        design.designButton(&lockAltitudeButon)
        design.designButton(&disconnectButton)
        
        cameraView.layer.borderWidth = 1.0
        cameraView.layer.borderColor = design.qvisColor.CGColor
        
        mapView.layer.cornerRadius = 20
        
        videoIndicator.hidden = true
                        
        leftJoystickView.delegate = self
        rightJoystickView.delegate = self
        
        leftJoystickView.initialize(false, verticalReturn: true, longLayout: false, start: .bottom, verticalDeadZone: 0, horizontalDeadZone: 20.0)
        rightJoystickView.initialize(true, verticalReturn: true, longLayout: false, start: .middle, verticalDeadZone: 0, horizontalDeadZone: 0.0)
        
        cameraView.layer.cornerRadius = 10.0
        
        tcp!.tcpDelegate = self
        
        fpsSlider.maximumValue = 3.0
        fpsSlider.minimumValue = 0.0
        fpsSlider.setValue(2.0, animated: false)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    func updateView(x: CGFloat, y: CGFloat) {
        
    }
    
    func setRecivedImage(image: UIImage) {
        if(videoOn){
            if(videoIndicator.hidden == false){
                videoIndicator.hidden = true
                videoIndicator.stopAnimating()
            }
            println("Setting image")
            cameraView.image = image
        }
    }
    
    func setRecivedData(data: [Double]) {
        rollLabel.text = NSString(format: "%.02f", data[0])
        pitchLabel.text = NSString(format: "%.02f", data[1])
        yawLabel.text = NSString(format: "%.02f", data[2])

    }
    
    func getSendData() -> String {
        var rightJoystickValues = rightJoystickView.getJoystickPosition()
        var leftJoystickValues = leftJoystickView.getJoystickPosition()
        
        var msg: String = ""
        
        msg = "<\(Float(rightJoystickValues.dx)):\(rightJoystickValues.dy):\(leftJoystickValues.dx):\(leftJoystickValues.dy):"
        
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
            msg += "1>"
        }
        else {
            msg += "0>"
        }
        
        return msg

    }
    
    func getIdentityMsg() -> String {
        
        var identity = ":2:\(UIDevice.currentDevice().name)"
        
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
    
    override func prefersStatusBarHidden() -> Bool {
        return true
    }
}