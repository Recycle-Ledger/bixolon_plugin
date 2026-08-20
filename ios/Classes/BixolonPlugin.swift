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

    // pairedDevices 요청 응답 대기열. refreshBTLookup()의 결과는
    // BT_FOUND_PRINTER/BT_LOOKUP_COMPLETE 알림으로만 전달되므로,
    // LOOKUP_COMPLETE(또는 타임아웃) 시점에 모아서 한꺼번에 응답한다.
    private var pendingLookupResults: [FlutterResult] = []
    private var lookupTimeoutWork: DispatchWorkItem?
    private var didRegisterLookupObservers = false
    private static let lookupTimeoutSeconds: TimeInterval = 5

    // COMPLETE 알림이 아직 도착하지 않은 refreshBTLookup 호출 수.
    // init 직후처럼 이전 lookup이 진행 중일 때 새 조회가 시작되면, 이전
    // lookup의 COMPLETE가 새 조회의 결과를 조기 응답하지 않도록
    // 카운트가 0이 되는 마지막 COMPLETE에서만 응답한다.
    private var outstandingLookups = 0

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
            startLookup()
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
    
    /// 페어링(연결)된 프린터 목록을 조회한다.
    ///
    /// 기존에는 init 시점에 채워진 btList 캐시를 그대로 반환해, 앱 실행 후
    /// 새로 페어링한 프린터가 재조회에도 나타나지 않았다. 이제 요청마다
    /// lookup을 새로 돌리고 완료 알림(또는 타임아웃) 시점의 목록을 반환한다.
    private func scanPairedDevices(result: @escaping FlutterResult) {
        guard printerController != nil else {
            // init 전이라 lookup을 돌릴 수단이 없으면 현재(빈) 목록을 반환한다.
            result(encodedBtList())
            return
        }

        pendingLookupResults.append(result)
        // 이미 진행 중인 lookup이 있으면 새로 시작하지 않고 그 완료에 함께 응답한다.
        if pendingLookupResults.count == 1 {
            let work = DispatchWorkItem { [weak self] in
                self?.flushPendingLookupResults()
            }
            lookupTimeoutWork = work
            DispatchQueue.main.asyncAfter(
                deadline: .now() + Self.lookupTimeoutSeconds,
                execute: work
            )
            startLookup()
        }
    }

    /// 목록을 비우고 lookup을 새로 시작한다. 결과는 알림 옵저버가 채운다.
    private func startLookup() {
        btList.removeAll()
        printerList = UPOSPrinters()
        refreshLookup()
    }

    private func refreshLookup() {
        outstandingLookups += 1
        printerController?.refreshBTLookup()
    }

    private func flushPendingLookupResults() {
        lookupTimeoutWork?.cancel()
        lookupTimeoutWork = nil
        // 타임아웃으로 응답하는 경우 COMPLETE가 유실된 것이므로 카운트를 초기화해
        // 이후 조회가 계속 타임아웃에만 의존하지 않게 한다.
        outstandingLookups = 0
        guard !pendingLookupResults.isEmpty else { return }

        let results = pendingLookupResults
        pendingLookupResults = []
        let payload = encodedBtList()
        for result in results {
            result(payload)
        }
    }

    private func encodedBtList() -> Any {
        do {
            let jsonData = try JSONEncoder().encode(btList)
            return String(data: jsonData, encoding: .utf8)!
        } catch let error {
            return FlutterError(
                code: "ENCODE_FAILED",
                message: error.localizedDescription,
                details: nil
            )
        }
    }

    private func connectPrinter(deviceName: String, result: FlutterResult) {
        refreshLookup()
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
        // printerInit은 앱 세션 중 여러 번 불릴 수 있다(dispose 후 재-init).
        // 옵저버가 중복 등록되면 같은 기기가 목록에 여러 번 쌓이므로 한 번만 등록한다.
        if didRegisterLookupObservers { return }
        didRegisterLookupObservers = true

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
                    // connectPrinter 등 목록을 비우지 않는 lookup에서도 같은 기기가
                    // 중복으로 쌓이지 않도록 주소 기준으로 걸러 넣는다.
                    if !strongSelf.btList.contains(where: { $0.macAddress == lookupDevice.address }) {
                        strongSelf.btList.append(
                            BluetoothData(logicalName: lookupDevice.modelName, macAddress: lookupDevice.address)
                        )
                        strongSelf.printerList?.addDevice(lookupDevice)
                    }
                }
            }
        }
        
        notiCenter.addObserver(forName: NSNotification.Name(rawValue: __NOTIFICATION_NAME_BT_LOOKUP_COMPLETE_),
                               object: nil,
                               queue: OperationQueue.current)
        {
            [weak self] n in
            guard let strongSelf = self else { return }
            strongSelf.outstandingLookups = max(0, strongSelf.outstandingLookups - 1)
            if strongSelf.outstandingLookups == 0 {
                strongSelf.flushPendingLookupResults()
            }
        }
    }
}
