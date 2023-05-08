import 'dart:async';

import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';

class MainController {
  final flutterReactiveBle = FlutterReactiveBle();
  StreamSubscription? _subscription;

  void startScan() {
    _subscription = flutterReactiveBle.scanForDevices(withServices: [], scanMode: ScanMode.lowLatency).listen((event) {
      print("@@@ device name : ${event.name}");
      print("@@@ device name : ${event.id}");
    });
  }
}

