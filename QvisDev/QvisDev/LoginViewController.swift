//
//  ViewController.swift
//  QvisDev
//
//  Created by Toni Axelsson on 2014-09-11.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

import UIKit

class LoginViewController: UIViewController, UITextFieldDelegate, connectionProtocol {

    @IBOutlet weak var ipTextField: UITextField!
    @IBOutlet weak var connectButton: UIButton!
    
    @IBAction func connectButtonPushed(sender: AnyObject) {
        
        tcp = TCPHandler(ipAdress: "10.0.1.6" ,portNumber: 3490, delegate: self)
        tcp!.initTCPConnection()
        
        //self.performSegueWithIdentifier("toHomeView", sender: self)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        connectButton.layer.borderWidth = 2.0
        connectButton.layer.borderColor = UIColor.whiteColor().CGColor
        connectButton.layer.cornerRadius = 10.0
        
        ipTextField.delegate = self
        ipTextField.keyboardType = UIKeyboardType.NumbersAndPunctuation

    }
    
    func connectedSucess() {
        self.performSegueWithIdentifier("toHomeView", sender: self)
    }
    
    func errorConnecting() {
        var errorView = UIAlertController(title: "Error During Connection", message: "Something went wrong", preferredStyle: UIAlertControllerStyle.Alert)
        errorView.addAction(UIAlertAction(title: "OK", style: UIAlertActionStyle.Default, handler: nil))
        self.presentViewController(errorView, animated: true, completion: nil)
        
    }
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        self.ipTextField.resignFirstResponder()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
}

