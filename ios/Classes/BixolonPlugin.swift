import Flutter
import UIKit
import frmBixolonUPOS
import CoreBluetooth
import CoreLocation

public class BixolonPlugin: NSObject, FlutterPlugin, UPOSDeviceControlDelegate {
    let CHANNEL: String = "bixolon_plugin"
    var btList = Array<BluetoothData>()
  
    // SDK Variable
    let msr: UPOSMSR = UPOSMSR()
    var printerController: UPOSPrinterController?
    var printerList: UPOSPrinters?
    
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "bixolon_plugin", binaryMessenger: registrar.messenger())
    let instance = BixolonPlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    result("iOS " + UIDevice.current.systemVersion)
      switch (call.method) {
      case "init":
          printerInit()
          result(true)
          break
      case "checkConnection":
          result(true)
          break
      case "deviceEnableSetting":
          result(true)
          break
      case "dispose":
          dispose()
          result(true)
          break
      case "pairedDevices":
          scanPairedDevices(result: result)
          break
      case "connectPrinter":
          connectPrinter(deviceName: call.arguments as! String)
          break
      case "currentPrinter":
          result(true)
          break
      case "printText":
          printText(text: call.arguments as! String, result: result)
          break
      case "printImage":
          printImage(byteArray: call.arguments as! FlutterStandardTypedData, result: result)
          break
      case "printPDF":
          printPDF(filePath: call.arguments as! String, result: result)
          break
      default:
          return
      }
  }
    
    private func printerInit() {
        print("@@@@ 1")
        let printerController = UPOSPrinterController()
        
        print("@@@@ 2")
        printerList = UPOSPrinters()
        
//        if let printerCon = printerController {
//            print("@@@@ 3")
//            registerNotiLookupBT()
//            printerCon.setLogLevel(UInt8(LOG_SHOW_ALL))
//            printerCon.setCharacterSet(5601)
//            printerCon.delegate = self
//            printerCon.refreshBTLookup()
//            print("@@@@ 4")
//        }
//        
//        if let rawList = printerList?.getList() as? [Any] {
//            let device = rawList.compactMap{ $0 as? UPOSPrinter }.first
//            printerController?.open(device?.modelName)
//        } else {
//
//        }
//        print("@@@@ 5")
//        printerController?.claim(5000)
//        printerController?.deviceEnabled = true
    }
    
    private func dispose() {
        printerController?.releaseDevice()
        printerController?.close()
        printerController?.deviceEnabled = false
    }
    
    private func scanPairedDevices(result: FlutterResult) {
        do {
            let jsonData = try JSONEncoder().encode(btList)
            let jsonString = String(data: jsonData, encoding: .utf8)
            result(String(jsonString!))
        } catch let error {
            result(error)
        }
    }

    private func connectPrinter(deviceName: String) {
        printerController?.refreshBTLookup()
        if let rawList = printerList?.getList() as? [Any] {
            let deviceList = rawList.compactMap{ $0 as? UPOSPrinter }
            if let device = deviceList.first(where: {$0.modelName == deviceName}) {
                printerController?.open(deviceName)
            } else {

            }
        } else {

        }
        printerController?.claim(5000)
        printerController?.deviceEnabled = true
    }
    
    private func printText(text: String, result: FlutterResult) {
        printerController?.printNormal(Int(__UPOS_PRINTER_STATION.PTR_S_RECEIPT.rawValue), data: text)
    }
    
    private func printImage(byteArray: FlutterStandardTypedData, result: FlutterResult) {
        do {
            let byte = [UInt8](byteArray.data)
            let data = Data(byte)
            print("byte : \(byte)")
            let image = UIImage(data: data)!
            printerController?.printBitmap(Int(__UPOS_PRINTER_STATION.PTR_S_RECEIPT.rawValue), image: image, width: printerController!.recLineWidth, alignment: -3)
            result(true)
        } catch let error {
            result(error)
        }
    }
    
    private func printPDF(filePath: String, result: FlutterResult) {
        printerController?.printPDF(Int(__UPOS_PRINTER_STATION.PTR_S_RECEIPT.rawValue), fileName: filePath, page: 1)
    }
     
    func registerNotiLookupBT(){
        let notiCenter = NotificationCenter.default
        notiCenter.addObserver(forName: NSNotification.Name(rawValue: __NOTIFICATION_NAME_BT_WILL_LOOKUP_),
                               object: nil,
                               queue: OperationQueue.current)
        {
            n in
        }
        
        notiCenter.addObserver(forName: NSNotification.Name(rawValue: __NOTIFICATION_NAME_BT_FOUND_PRINTER_),
                               object: nil,
                               queue: OperationQueue.current)
        {
            [weak self] n in
            print("__NOTIFICATION_NAME_BT_FOUND_PRINTER_")
            guard let strongSelf = self else { return }
            if let userinfo = n.userInfo {
                if let lookupDevice:UPOSPrinter = userinfo[__NOTIFICATION_NAME_BT_FOUND_PRINTER_] as? UPOSPrinter  {
                    strongSelf.btList.append(
                        BluetoothData(logicalName: lookupDevice.modelName, macAddress: lookupDevice.address)
                    )
                    strongSelf.printerList?.addDevice(lookupDevice)
                }
            }
        }
        
        notiCenter.addObserver(forName: NSNotification.Name(rawValue: __NOTIFICATION_NAME_BT_LOOKUP_COMPLETE_),
                               object: nil,
                               queue: OperationQueue.current)
        {
            [weak self] n in
            guard let strongSelf = self else { return }
        }
    }
}
