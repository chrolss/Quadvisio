//
//  test.swift
//  SwiftGame
//
//  Created by Toni Axelsson on 2014-08-20.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

import Foundation
import UIKit

var com = Communicate()

class Communicate: NSObject, NSStreamDelegate {
    
    var inputStream: NSInputStream?
    var outputStream: NSOutputStream?
    
    func initConnection() {
        println("connecting...")
        
        NSStream.getStreamsToHostWithName("10.0.1.6", port: 3490, inputStream: &inputStream, outputStream: &outputStream)
        
        self.inputStream!.delegate = self
        self.outputStream!.delegate = self
        
        self.inputStream!.scheduleInRunLoop(NSRunLoop.currentRunLoop(), forMode: NSDefaultRunLoopMode)
        self.outputStream!.scheduleInRunLoop(NSRunLoop.currentRunLoop(), forMode: NSDefaultRunLoopMode)
        
        self.inputStream!.open()
        self.outputStream!.open()
        
    }
    
    func stream(aStream: NSStream!, handleEvent eventCode: NSStreamEvent){
        
        switch eventCode {
        case NSStreamEvent.ErrorOccurred:
            println("Error during connection")
            
        case NSStreamEvent.OpenCompleted:
            println("Stream opened")
            
        case NSStreamEvent.HasBytesAvailable:
            println("Bytes available")
            
        default:
            println("Unkown error")
        }
    }
}
