//
//  Joystick.swift
//  JoystickSwift
//
//  Created by Toni Axelsson on 2014-08-26.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

import UIKit
import QuartzCore

protocol JoystickDelegate {
    func updateView(x: CGFloat, y: CGFloat)
}

enum startingPoint {
    case middle
    case top
    case bottom
}

class Joystick: UIView {
    var bgImageView: UIImageView?
    var thumbImageView: UIImageView?
    var handle: UIView?
    var defaultPoint: CGPoint?
    var selfCenter: CGPoint = CGPoint(x: 0.0, y: 0.0)
    var selfRadius: CGFloat = 0.0
    var joystickHandleLimit: CGFloat = 0.0
    
    var verticalDeadZone: CGFloat = 0.0
    var horizontalDeadZone: CGFloat = 0.0
    
    var isTouching: Bool = false
    var horizontalReturn: Bool = false
    var verticalReturn: Bool = false
    var longLayout: Bool = false
    
    var start: startingPoint = .middle
    
    var delegate: JoystickDelegate?
    
    let moveViscosity: CGFloat = 4
    let smallestPossible: CGFloat = 0.09
    
    required init(coder aDecoder: (NSCoder!)) {
        super.init(coder: aDecoder)
    }
    
    func initialize(horizontalReturn: Bool, verticalReturn: Bool, longLayout: Bool, start: startingPoint, verticalDeadZone: CGFloat, horizontalDeadZone: CGFloat) {
        self.horizontalReturn = horizontalReturn
        self.verticalReturn = verticalReturn
        self.longLayout = longLayout
        self.start = start
        self.verticalDeadZone = verticalDeadZone
        self.horizontalDeadZone = horizontalDeadZone
        
        self.bgImageView = UIImageView(frame: CGRect(x: 0, y: 0, width: self.bounds.size.width, height: self.bounds.size.height))
        self.bgImageView!.layer.cornerRadius = bgImageView!.bounds.width/2.0

        if(longLayout) {
            bgImageView?.image = UIImage(named: "long_joystick_bg")
        }
        else {
            bgImageView?.image = UIImage(named: "regular_joystick_bg")
        }
        
        self.addSubview(self.bgImageView!)
        
        self.makeJoystickHandle()
        
        thumbImageView?.image = UIImage(named: "joystick_handle")
        
        self.selfCenter = CGPointMake(self.bounds.origin.x + self.bounds.size.width/2.0, self.bounds.origin.y + self.bounds.size.height/2.0)
        
        self.selfRadius = self.bounds.size.width/2.0
        joystickHandleLimit = selfRadius - self.handle!.bounds.width/2.0
    }
    
    func makeJoystickHandle() {
        self.handle = UIView(frame: CGRectMake(0, 0, 55, 55))
        
        switch start {
        case .top:
            println("top")
            
        case .middle:
            self.handle?.center = CGPointMake(self.bounds.size.width/2.0, self.bounds.size.height/2.0)
            
        case .bottom:
            self.handle?.center = CGPointMake(self.bounds.size.width/2.0, self.bounds.size.height - 27.5)

        }
        
        self.defaultPoint = self.handle!.center
        
        self.addSubview(self.handle!)
        
        self.thumbImageView = UIImageView(frame: self.handle!.frame)
        self.addSubview(self.thumbImageView!)
    }
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        UIView.animateWithDuration(0.2, animations: {self.alpha = 1})
        
        self.touchesMoved(touches, withEvent: event)
    }
    
    override func touchesMoved(touches: NSSet, withEvent event: UIEvent) {
        var myTouch: UITouch = touches.allObjects[0] as UITouch
        var touchPos: CGPoint = myTouch.locationInView(self)
        
        if(self.DistanceBetweenTwoPoints(touchPos, point2: selfCenter) > joystickHandleLimit) {
            var vX: CGFloat = touchPos.x - selfCenter.x
            var vY: CGFloat = touchPos.y - selfCenter.y
            var magV: CGFloat = sqrt(vX*vX + vY*vY)
            touchPos.x = selfCenter.x + vX * joystickHandleLimit / magV
            touchPos.y = selfCenter.y + vY * joystickHandleLimit / magV
        }
        
        if(touchPos.x > selfRadius - horizontalDeadZone && touchPos.x < selfRadius + horizontalDeadZone) {
            println("setting pos x to zero")
            touchPos.x = self.defaultPoint!.x
        }
        
        self.handle!.center = touchPos
        UIView.animateWithDuration(0.1, animations: {self.thumbImageView!.center = touchPos})
        
        self.isTouching = true
    }
    
    override func touchesEnded(touches: NSSet, withEvent event: UIEvent) {        
        if(self.verticalReturn) {
            UIView.animateWithDuration(0.1, animations: {self.thumbImageView!.center.x = self.defaultPoint!.x})
            self.handle!.center.x = defaultPoint!.x
        }
        if(self.horizontalReturn) {
            UIView.animateWithDuration(0.1, animations: {self.thumbImageView!.center.y = self.defaultPoint!.y})
            self.handle!.center.y = defaultPoint!.y
        }
    }
    
    func setImages(bgImage: UIImage, thumbImage: UIImage) {
        self.bgImageView?.image = bgImage
        self.thumbImageView?.image = thumbImage
    }
    
    func setOptions(horizontalReturn: Bool, verticalReturn: Bool) {
        self.horizontalReturn = horizontalReturn
        self.verticalReturn = verticalReturn
    }
    
    func calcValuesAndNotifyDelegate() {
        var dx = (self.defaultPoint!.x - handle!.center.x)/(self.selfRadius)
        var dy = (handle!.center.y - self.defaultPoint!.y)/(self.selfRadius)
    }
    
    func getJoystickPosition() -> (dx: CGFloat, dy: CGFloat) {
        
        var dx: CGFloat = 0.0
        var dy: CGFloat = 0.0
        
        if( handle!.center.x - self.defaultPoint!.x > horizontalDeadZone ) {
            dx = (handle!.center.x - self.defaultPoint!.x - horizontalDeadZone)/(self.joystickHandleLimit - horizontalDeadZone)
        }
        else if(self.defaultPoint!.x - handle!.center.x > horizontalDeadZone) {
            dx = (handle!.center.x - self.defaultPoint!.x + horizontalDeadZone)/(self.joystickHandleLimit - horizontalDeadZone)
        }
        else {
            dx = 0
        }
        
        if( handle!.center.y - self.defaultPoint!.y > verticalDeadZone) {
            dy = (handle!.center.y - self.defaultPoint!.y - verticalDeadZone)/(self.joystickHandleLimit - verticalDeadZone)
        }
        else if(self.defaultPoint!.y - handle!.center.y > verticalDeadZone) {
            dy = (handle!.center.y - self.defaultPoint!.y + verticalDeadZone)/(self.joystickHandleLimit - verticalDeadZone)
        }
        else {
            dy = 0
        }
        return (dx, -dy/2.0)
    }
    
    func DistanceBetweenTwoPoints(point1: CGPoint, point2: CGPoint) -> CGFloat {
        var dx: CGFloat = point2.x - point1.x
        var dy: CGFloat = point2.y - point1.y
        return sqrt(dx*dx + dy*dy)
    }
    
}