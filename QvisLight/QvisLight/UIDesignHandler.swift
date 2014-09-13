//
//  designHandler.swift
//  QvisLight
//
//  Created by Toni Axelsson on 2014-09-01.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

import Foundation
import UIKit

var design: UIDesignHandler = UIDesignHandler()

class UIDesignHandler {
    
    let qvisColor = UIColor(red: 0.0/255.0, green: 199.0/255.0, blue: 199.0/255.0, alpha: 1.0)
    let cornerRadius: CGFloat = 10.0
    
    let buttonPushedColorLight = UIColor(red: 187.0/255.0, green: 232.0/255.0, blue: 231.0/255.0, alpha: 1.0)
    let buttonPushedColorDark = UIColor(red: 0.0/255.0, green: 110.0/255.0, blue: 110.0/255.0, alpha: 1.0)
    
    let darkViewColor = UIColor(red: 31.0/255.0, green: 33.0/255.0, blue: 36.0/255.0, alpha: 1.0)
    let darkBackgroundColor = UIColor(red: 39.0/255.0, green: 42.0/255.0, blue: 46.0/255.0, alpha: 1.0)
    let lightViewColor = UIColor(red: 245.0/255.0, green: 245.0/255.0, blue: 245.0/255.0, alpha: 1.0)
    
    init() {
    }
    
    func designButton(inout button: UIButton!) {
        
        button.layer.borderWidth = 1.0
        button.layer.borderColor = qvisColor.CGColor
        button.layer.cornerRadius = cornerRadius
        button.layer.backgroundColor = UIColor.clearColor().CGColor
    }
    
    func makePopUpView() -> UIVisualEffectView {
        
        var popUpView = UIVisualEffectView()
        
        return popUpView
    }
}