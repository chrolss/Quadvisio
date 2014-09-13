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
    
    let blueColor: UIColor = UIColor(red: 0.0/255.0, green: 80.0/255.0, blue: 200.0/255.0, alpha: 1.0)
    
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
        videoButton.layer.borderWidth = 2.0
        videoButton.layer.cornerRadius = 10.0
        
        colorButton.layer.borderColor = blueColor.CGColor
        colorButton.layer.borderWidth = 2.0
        colorButton.layer.cornerRadius = 10.0
        
        photoButton.layer.borderColor = blueColor.CGColor
        photoButton.layer.borderWidth = 2.0
        photoButton.layer.cornerRadius = 10.0
        
        disconnectButton.layer.borderColor = blueColor.CGColor
        disconnectButton.layer.borderWidth = 2.0
        disconnectButton.layer.cornerRadius = 10.0
        
        
        leftJoystickView.delegate = self
        rightJoystickView.delegate = self
        
        leftJoystickView.initialize(false, verticalReturn: true, longLayout: false, start: .bottom, verticalDeadZone: 0, horizontalDeadZone: 20.0)
        rightJoystickView.initialize(true, verticalReturn: true, longLayout: false, start: .middle, verticalDeadZone: 0, horizontalDeadZone: 0.0)
        
        leftJoystickView.layer.backgroundColor = UIColor.clearColor().CGColor
        
        rightJoystickView.layer.backgroundColor = UIColor.clearColor().CGColor

    }
    
    func updateView(x: CGFloat, y: CGFloat) {
        
    }
    
    func setRecivedData(data: [Double]) {
        
    }
    
    func setRecivedImage(image: UIImage) {
    
    }
    
    func getSendData() -> String {
        
        return "<0:0:0:0:0:0:0:0>"
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
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
}