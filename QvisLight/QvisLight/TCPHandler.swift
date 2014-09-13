//
//  TCPHandler.swift
//  TCPHandler
//
//  Created by Toni Axelsson on 2014-08-28.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

import Foundation
import UIKit

protocol connectionProtocol {
    func connectedSucess()
    func errorConnecting()
}

protocol tcpProtocol {
    func setRecivedImage(image: UIImage)
    func setRecivedData(data: [Double])
    func getSendData() -> String
    func getIdentityMsg() -> String
}

var tcp: TCPHandler?

class TCPHandler: NSObject, NSStreamDelegate {
    
    var inputStream: NSInputStream?
    var outputStream: NSOutputStream?
    
    var ipAdress: String
    var portNumber: Int

    var outputStr:String = ""
    var inputStr: String = ""
    var buffer = [UInt8](count: 4096, repeatedValue: 0)
    var msgStorage = [UInt8]()
    var imgBytes = [UInt8]()
    var bytesWritten: NSInteger = 0
    var msgSize: Int = 0
    var totalSize: Int = -1
    
    let colorSpace: CGColorSpaceRef = CGColorSpaceCreateDeviceRGB()
    let bwSpace: CGColorSpaceRef = CGColorSpaceCreateDeviceGray()
    var imgSize: Int = -1
    var imgHeight: Int = 0
    var imgWidth: Int = 0
    var imgChannels: Int = 3
    var imgData: NSData = NSData()
    var imageRef: CGImageRef?
    var provider: CGDataProviderRef?
    var image: UIImage?
    
    var stateData = [Double](count: 3, repeatedValue: 0)
    
    var send: Bool = true
    var imgComing: Bool = false
    var outputStreamReady: Bool = false
    var inputstreamOpened: Bool = false
    var outputStreamOpened: Bool = false
    
    var identityTold: Bool = false
    
    var connectionDelegate:connectionProtocol
    var tcpDelegate:tcpProtocol?
    
    init(ipAdress: String, portNumber: Int, delegate: connectionProtocol) {
        self.ipAdress = ipAdress
        self.portNumber = portNumber
        self.connectionDelegate = delegate
    }
    
    func initTCPConnection() {
        println("Connecting...")
    
        NSStream.getStreamsToHostWithName(self.ipAdress, port: 3490, inputStream: &inputStream, outputStream: &outputStream)
        
        self.inputStream!.delegate = self
        self.outputStream!.delegate = self
        
        self.inputStream!.scheduleInRunLoop(NSRunLoop.currentRunLoop(), forMode: NSDefaultRunLoopMode)
        self.outputStream!.scheduleInRunLoop(NSRunLoop.currentRunLoop(), forMode: NSDefaultRunLoopMode)
        
        self.inputStream!.open()
        self.outputStream!.open()
    }
    
    func stream(aStream: NSStream!, handleEvent eventCode: NSStreamEvent) {
        
        switch eventCode {
        case NSStreamEvent.ErrorOccurred:
            println("Error during connection")
            if(aStream==self.inputStream || aStream==self.outputStream) {
                connectionDelegate.errorConnecting()
                self.closeConnection()
            }
            
        case NSStreamEvent.OpenCompleted:
            println("Stream Opened!")
            
            if(aStream==self.inputStream) {
                self.inputstreamOpened = true
            }
            
            else if(aStream==self.outputStream) {
                self.outputStreamOpened = true
            }
            if(self.outputStreamOpened && self.inputstreamOpened) {
                    connectionDelegate.connectedSucess()
                    tcpDelegate?.setRecivedImage(UIImage(named: "ios_logo_opeque_center"))
            }
            
        case NSStreamEvent.HasBytesAvailable:
            println("Stream has bytes available")
            
            if(aStream==self.inputStream && !self.send) {
                
                while(self.inputStream!.hasBytesAvailable) {
                    var bytesRead = self.inputStream!.read(&buffer, maxLength: buffer.count)
                    if(bytesRead == -1) {
                        println("Server closed connection")
                        closeConnection()
                        break
                    }
                    msgStorage += buffer[0..<bytesRead]
                    println(msgStorage.count)
                    
                    if(msgSize==0 && msgStorage.count>4) {
                        let data = NSData(bytes: msgStorage, length: 4)
                        self.inputStr = NSString(data: data, encoding: NSUTF8StringEncoding)
                        msgSize = inputStr.toInt()!
                        println(msgSize)
                    }
                    
                    if(msgSize != 0 && msgStorage.count >= msgSize+4 && imgSize<0) {
                        let data = NSData(bytes: msgStorage, length: msgSize+4)
                        self.inputStr = NSString(data: data, encoding: NSUTF8StringEncoding)
                        println(self.inputStr)
                        self.decodeMsg(self.inputStr)
                    }
                    
                    if (msgStorage.count == totalSize && imgSize>0){
                        println("Excracting image")
                        self.extractImage()
                        msgStorage.removeAll()
                        msgSize = 0
                        imgSize = -1
                        totalSize = -1
                        self.send = true
                        if(self.outputStreamReady) {
                            self.sendMsg()
                        }
                        
                    }
                    if(msgStorage.count == totalSize && imgSize==0) {
                        println("No image")
                        msgStorage.removeAll()
                        inputStr = ""
                        msgSize = 0
                        imgSize = -1
                        totalSize = -1
                        self.send = true
                        if(self.outputStreamReady) {
                            self.sendMsg()
                        }
                    }
                }
            }
            println("Leaving bytes available")
            
            
        case NSStreamEvent.HasSpaceAvailable:
            println("Has space available")
            
            if(!identityTold) {
                
                var identity = tcpDelegate!.getIdentityMsg()
                
                self.bytesWritten = outputStream!.write(identity, maxLength: countElements(identity))
                identityTold = true
            }

            else if(aStream==self.outputStream && send) {
                self.sendMsg()
            }
            else if(aStream==self.outputStream && !send) {
                outputStreamReady = true
            }
            
        case NSStreamEvent.EndEncountered:
            println("End of Stream")
            
        case NSStreamEvent.None:
            println("None Event Occured")
            
        case NSStreamEvent.allZeros:
            println("All zeros")

        default:
            println("Unknown Error")
        }
    }
    
    func sendMsg() {
        self.outputStr = self.composeMsg()
        println("Sending message: " + self.outputStr)
        let data: NSData = outputStr.dataUsingEncoding(NSUTF8StringEncoding, allowLossyConversion: true)!
        self.bytesWritten = outputStream!.write(UnsafePointer<UInt8>(data.bytes), maxLength: data.length)
        self.send = false
        println("Message sent")
    }
    
    func decodeMsg(str: NSString) {
        println("Final message: " + str)

        var strValues = str.componentsSeparatedByString(":") as [String]
        stateData.removeAll()
        
        for value in 1..<(strValues.count-3) {
            stateData.append((strValues[value] as NSString).doubleValue)
            println(stateData[value-1])
        }
        
        imgChannels = strValues[strValues.count-1].toInt()!
        imgSize = strValues[strValues.count-2].toInt()!
        imgHeight = strValues[strValues.count-3].toInt()!
        imgWidth = strValues[strValues.count-4].toInt()!
        
        totalSize = msgSize + imgSize + 4
        
        println("Width: \(imgWidth) Height: \(imgHeight) ImageSize: \(imgSize) TotalSize: \(totalSize)")

        
        //Set recived data
        tcpDelegate!.setRecivedData(stateData)
    }
    
    func composeMsg() -> String {
        
        return tcpDelegate!.getSendData()
    }
    
    func extractImage() {
        imgBytes = Array(msgStorage[(msgSize+4)..<totalSize])
        
        imgData = NSData(bytes: imgBytes, length: imgSize)
        provider = CGDataProviderCreateWithCFData((imgData as CFDataRef))
        
        if(imgChannels==3){
        imageRef = CGImageCreate(UInt(imgWidth), UInt(imgHeight), 8, 24, UInt(imgWidth*3), colorSpace, CGBitmapInfo.ByteOrderDefault, provider, nil, false, kCGRenderingIntentDefault)
        }
        else {
            imageRef = CGImageCreate(UInt(imgWidth), UInt(imgHeight), 8, 8, UInt(imgWidth), bwSpace, CGBitmapInfo.ByteOrderDefault, provider, nil, false, kCGRenderingIntentDefault)
        }
        image = UIImage(CGImage: imageRef)
        
        tcpDelegate!.setRecivedImage(image!)
    }
    
    func canClose() -> Bool {
        if(self.outputStream!.streamStatus.toRaw() != 3 && self.inputStream!.streamStatus.toRaw() != 4) {
            return true
        }
        return false
    }
    
    func closeConnection() {
        
        while(!canClose()) {
            
        }
        
        outputStream!.close()
        inputStream!.close()
        outputStream!.removeFromRunLoop(NSRunLoop.currentRunLoop(), forMode: NSDefaultRunLoopMode)
        inputStream!.removeFromRunLoop(NSRunLoop.currentRunLoop(), forMode: NSDefaultRunLoopMode)
    }
}