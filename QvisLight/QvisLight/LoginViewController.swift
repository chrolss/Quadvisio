//
//  ViewController.swift
//  QvisLight
//
//  Created by Toni Axelsson on 2014-08-27.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

import UIKit

class LoginViewController: UIViewController, UITextFieldDelegate, connectionProtocol {
                            
    @IBOutlet weak var connectButton: UIButton!
    @IBOutlet weak var connectIndicator: UIActivityIndicatorView!
    @IBOutlet weak var ipTextField: UITextField!
    
    @IBAction func connectButtonPushed(sender: AnyObject) {
        
        connectButton.hidden = true
        connectIndicator.hidden = false;
        connectIndicator.startAnimating()
        tcp = TCPHandler(ipAdress: ipTextField.text ,portNumber: 3490, delegate: self)
        
        tcp!.initTCPConnection()
        self.performSegueWithIdentifier("toHomeView", sender: self)

    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        design.designButton(&connectButton)
        connectButton.layer.backgroundColor = UIColor.whiteColor().CGColor
        ipTextField.delegate = self
        ipTextField.keyboardType = UIKeyboardType.NumbersAndPunctuation
        
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        self.ipTextField.resignFirstResponder()
    }
    
    func connectedSucess() {
        connectIndicator.hidden = true;
        connectIndicator.stopAnimating()
        self.performSegueWithIdentifier("toHomeView", sender: self)
    }
    
    func errorConnecting() {
        var errorView = UIAlertController(title: "Error During Connection", message: "Something went wrong", preferredStyle: UIAlertControllerStyle.Alert)
        errorView.addAction(UIAlertAction(title: "OK", style: UIAlertActionStyle.Default, handler: nil))
        self.presentViewController(errorView, animated: true, completion: nil)
        connectButton.hidden = false
        connectIndicator.stopAnimating()
        connectIndicator.hidden = true
        
    }

}

