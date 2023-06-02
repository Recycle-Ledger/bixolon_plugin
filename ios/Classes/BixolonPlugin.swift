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
      switch (call.method) {
      case "init":
          printerInit(result: result)
          break
      case "checkConnection":
          result(nil)
          break
      case "deviceEnableSetting":
          result(nil)
          break
      case "dispose":
          dispose()
          result(nil)
          break
      case "pairedDevices":
          scanPairedDevices(result: result)
          break
      case "connectPrinter":
          connectPrinter(deviceName: call.arguments as! String, result: result)
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
          result(FlutterMethodNotImplemented)
          return
      }
  }
    
    private func printerInit(result: @escaping FlutterResult) {
        printerController = UPOSPrinterController()
        printerList = UPOSPrinters()
        
        if let printerCon = printerController {
            registerNotiLookupBT()
            printerCon.setLogLevel(UInt8(LOG_SHOW_NORMAL))
            printerCon.setCharacterSet(5601)
            printerCon.delegate = self
            printerCon.refreshBTLookup()
        }
        result(nil)

//        if let rawList = printerList?.getList() as? [Any] {
//            print("list : \(rawList.count)")
//            if (rawList.isEmpty) {
//                result(FlutterError())
//                return
//            }
//            let device = rawList.compactMap{ $0 as? UPOSPrinter }.first
//            printerController?.open(device?.modelName)
//        } else {
//            print("else")
//            result(FlutterError())
//            return
//        }
//        printerController?.claim(5000)
//        printerController?.deviceEnabled = true
//        result(nil)
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

    private func connectPrinter(deviceName: String, result: FlutterResult) {
        printerController?.refreshBTLookup()
        if let rawList = printerList?.getList() as? [Any] {
            let deviceList = rawList.compactMap{ $0 as? UPOSPrinter }
            if let device = deviceList.first(where: {$0.modelName == deviceName}) {
                printerController?.open(deviceName)
            } else {
                result(FlutterError())
            }
        } else {
            result(FlutterError())
        }
        printerController?.claim(5000)
        printerController?.deviceEnabled = true
        result(nil)
    }
    
    private func printText(text: String, result: FlutterResult) {
        printerController?.printNormal(Int(__UPOS_PRINTER_STATION.PTR_S_RECEIPT.rawValue), data: text)
        result(nil)
    }
    
    private func printImage(byteArray: FlutterStandardTypedData, result: FlutterResult) {
        let byte = [UInt8](byteArray.data)
        let data = Data(byte)
        print("byte : \(byte)")
        let image = UIImage(data: data)!
        printerController?.printBitmap(Int(__UPOS_PRINTER_STATION.PTR_S_RECEIPT.rawValue), image: image, width: printerController!.recLineWidth, alignment: -3)
        result(nil)
    }
    
    private func printPDF(filePath: String, result: FlutterResult) {
        printerController?.printPDF(Int(__UPOS_PRINTER_STATION.PTR_S_RECEIPT.rawValue), fileName: filePath, page: 1)
        result(nil)
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
