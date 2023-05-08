import Flutter
import UIKit
import frmBixolonUPOS

public class BixolonPlugin: NSObject, FlutterPlugin, UPOSDeviceControlDelegate {
    let CHANNEL: String = "bixolon_plugin"
    
    // SDK Variable
    let msr: UPOSMSR = UPOSMSR()
    var printerController: UPOSPrinterController?
    
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "bixolon_plugin", binaryMessenger: registrar.messenger())
    let instance = BixolonPlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    result("iOS " + UIDevice.current.systemVersion)
      switch (call.method) {
      case "init":
          break
      case "checkConnection":
          break
      case "deviceEnableSetting":
          break
      case "dispose":
          break
      case "pairedDevices":
          break
      case "connectPrinter":
          break
      case "currentPrinter":
          break
      case "unregisterPrinter":
          break
      case "printText":
          break
      default:
          return
      }
  }
    private func printerInit() {
        printerController = UPOSPrinterController()
        
        if let printerCon = printerController {
            printerCon.releaseDevice()
            printerCon.close()
            printerCon.setLogLevel(UInt8(LOG_SHOW_NEVER))
            printerCon.delegate = self
        }
    }
    
    private func registerNotiLookupBT() {
        let notiCenter = NotificationCenter.default
    }
    
    private func dispose() {
        
    }
    
    private func printText() {
    
        printerController?.printNormal(, data: "test print")
    }
}
