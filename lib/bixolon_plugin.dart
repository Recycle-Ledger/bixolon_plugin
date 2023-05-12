

import 'dart:convert';

import 'package:bixolon_plugin/bluetooth_device.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class BixolonPlugin {
  static const tag = 'bixolon_plugin';
  final platform = const MethodChannel('bixolon_plugin');

  Future<void> init() async {
    debugPrint('$tag - init');
    try {
      await platform.invokeMethod('init');
      return;
    } catch (error, stackTrace) {
      return Future.error(error, stackTrace);
    }
  }

  Future<void> dispose() async {
    debugPrint('$tag - dispose');
    try {
      await platform.invokeMethod('dispose');
      return;
    } catch (error, stackTrace) {
      return Future.error(error, stackTrace);
    }
  }
  
  /// 사전에 등록된 디바이스가 있는지 체크함. 등록된 디바이스가 없을 경우 스캔목록을 가져와서 최초 등록을 해주어야 한다.
  Future<bool> checkConnection() async {
      bool exist = await platform.invokeMethod('checkConnection');
    return exist;
  }
  
  /// 페어링된 디바이스를 사용할 수 있도록 사전 설정을 준비한다.
  Future<void> deviceEnableSetting() async {
    try {
      await platform.invokeMethod('deviceEnableSetting');
    } on PlatformException catch (error, stackTrace) {
      return Future.error(error.message.toString(), stackTrace);
    }
  }

  /// 페어링 되어있는 기기목록을 가져옴
  Future<List<BluetoothDevice>> getPairedDevices() async {
    debugPrint('$tag - getPairedDevices');
    String devicesJson = await platform.invokeMethod('pairedDevices');
    List jsonList = jsonDecode(devicesJson) as List;
    return jsonList.map((e) => BluetoothDevice.fromMap(e)).toList();
  }

  void unregisterPrinter() {
    platform.invokeMethod('unregisterPrinter');
  }

  /// 스캔한 프린터를 사용하도록 설정
  Future<void> selectPrinter(String macAddress) async {
    debugPrint('$tag - selectPrinter : $macAddress');
    try {
      await platform.invokeMethod('connectPrinter', macAddress);
    } on PlatformException catch (error, stackTrace) {
      return Future.error(error, stackTrace);
    }
  }

  /// 현재 연결된 프린터의 정보
  Future<BluetoothDevice?> getCurrentPrinter() async {
    debugPrint('$tag - getCurrentPrinter');
    String? deviceJson = await platform.invokeMethod('currentPrinter');
    if (deviceJson == null) {
       return null;
    } else {
      return BluetoothDevice.fromMap(jsonDecode(deviceJson));
    }
  }

  Future<void> printText(String text) async {
    debugPrint('$tag - printText');
    try {
      await platform.invokeMethod('printText', '$text');
    } on PlatformException catch (error, stackTrace) {
      return Future.error(error, stackTrace);
    }
  }

  Future<void> printImage(Uint8List byteArray) async {
    debugPrint('$tag - printImage');
    try {
      await platform.invokeMethod('printImage', byteArray);
    } on PlatformException catch (error, stackTrace) {
      return Future.error(error, stackTrace);
    }
  }

  Future<void> printPDF(String filePath) async {
    debugPrint('$tag - printPDF');
    try {
      await platform.invokeMethod('printPDF', filePath);
    } on PlatformException catch (error, stackTrace) {
      return Future.error(error, stackTrace);
    }
  }

  // Singleton patten
  factory BixolonPlugin() {
    return _bixolonPlugin;
  }

  static final BixolonPlugin _bixolonPlugin = BixolonPlugin._internal();

  BixolonPlugin._internal();
}