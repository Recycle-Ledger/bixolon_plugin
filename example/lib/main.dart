import 'dart:io';

import 'package:bixolon_plugin/bixolon_plugin.dart';
import 'package:bixolon_plugin/bluetooth_device.dart';
import 'package:bixolon_plugin/escape_sequence.dart';
import 'package:bixolon_plugin/common_symbol.dart';
import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'dart:async';
import 'dart:ui' as ui;

import 'package:flutter/services.dart';
import 'package:permission_handler/permission_handler.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  List<BluetoothDevice> pairedDeviceList = [];
  String stateText = 'ready';

  @override
  void initState() {
    super.initState();
    checkPermission();
  }

  @override
  Widget build(BuildContext context) {
    final key = GlobalKey();

    Future<Uint8List> widgetToByteArray() async {
      try {
        final boundary = key.currentContext?.findRenderObject() as RenderRepaintBoundary?;
        if (boundary == null) {
          return Future.error('key error');
        }
        ui.Image image = await boundary.toImage();
        ByteData? byteData = await image.toByteData(format: ui.ImageByteFormat.png);
        if (byteData == null) {
          return Future.error('byteData error');
        }
        Uint8List pngBytes = byteData.buffer.asUint8List();

        return pngBytes;
      } catch (e) {
        return Future.error(e.toString());
      }
    }

    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('bixolon plugin example'),
        ),
        body: Container(
          alignment: Alignment.center,
          width: double.infinity,
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Text(
                stateText,
                style: const TextStyle(
                  fontSize: 18.0,
                ),
              ),
              const SizedBox(height: 20),
              Wrap(
                spacing: 10,
                runSpacing: 10,
                crossAxisAlignment: WrapCrossAlignment.center,
                direction: Axis.horizontal,
                children: [
                  FilledButton(
                    onPressed: () async {
                      BixolonPlugin().init();
                    },
                    child: const Text('init'),
                  ),
                  FilledButton(
                    onPressed: () async {
                      bool needDevice = await BixolonPlugin().checkConnection();
                      if (needDevice) {
                      } else {
                        setState(() {
                          stateText = '등록된 기기가 없습니다. 기기 스캔이 필요합니다.';
                        });
                      }
                    },
                    child: const Text('search'),
                  ),
                  FilledButton(
                    onPressed: () async {
                      try {
                        await BixolonPlugin().deviceEnableSetting();
                        setState(() {
                          stateText = '프린트 준비가 완료되었습니다.';
                        });
                      } catch (error, stackTrace) {
                        setState(() {
                          stateText = '등록된 기기와의 연결에 실패했습니다. 기기 확인 후 다시 연결해주세요. error : ${error.toString()}';
                        });
                      }
                    },
                    child: const Text('connect'),
                  ),
                  FilledButton(
                    onPressed: () async {
                      List<BluetoothDevice> deviceList = await BixolonPlugin().getPairedDevices();
                      setState(() {
                        pairedDeviceList = deviceList;
                      });
                    },
                    child: const Text('scan'),
                  ),
                  FilledButton(
                    onPressed: () async {
                      final es = EscapeSequence();
                        BixolonPlugin().printText('${es.normal}\n');
                        BixolonPlugin().printText('${es.doubleHighAndWide}${es.bold}${es.center}수집 확인서\n\n\n');
                        BixolonPlugin().printText('${es.normal}${es.spaceBetween('대    상 :', '폐식용유')}\n');
                        BixolonPlugin().printText('${es.normal}${es.spaceBetween('수    량 :', '20 캔')}\n');
                        BixolonPlugin().printText('${es.normal}${es.spaceBetween('금    액 :', '675,000 원')}\n\n\n');
                        BixolonPlugin().printText('${es.normal}${es.center}상기 폐식용유를 수집하였음\n');
                        BixolonPlugin().printText('${es.normal}${es.center}2023년 5월 3일\n\n');
                        BixolonPlugin().printText('${es.normal}${CommonSymbol.stroke}\n\n');
                        BixolonPlugin().printText('${es.normal}${es.doubleWide}배출처\n');
                        BixolonPlugin().printText('${es.normal}${es.spaceBetween('상    호 :', '까치울초')}\n');
                        BixolonPlugin().printText('${es.normal}${es.spaceBetween('담 당 자 :', '김까치')}\n\n');
                        BixolonPlugin().printText('${es.normal}${es.doubleWide}수집처\n');
                        BixolonPlugin().printText('${es.normal}${es.spaceBetween('상    호 :', '(주) 에코그린')}\n');
                        BixolonPlugin().printText('${es.normal}${es.spaceBetween('대표이사 :', '서 성 희')}\n');
                        BixolonPlugin().printText('${es.normal}${es.spaceBetween('주    소 :', '군포시 당정로 83')}\n');
                        BixolonPlugin().printText('${es.normal}${es.spaceBetween('담 당 자 :', '정 재 우')}\n');
                        BixolonPlugin().printText('${es.normal}\n\n');
                        BixolonPlugin().printText('${es.normal}${es.doubleWide}서명\n\n');
                        BixolonPlugin().printImage(await widgetToByteArray());
                        BixolonPlugin().printText('${es.normal}\n\n');
                    },
                    child: const Text('text print'),
                  ),
                  FilledButton(
                    onPressed: () async {
                      BixolonPlugin().printImage(await widgetToByteArray());
                    },
                    child: const Text('png print'),
                  ),
                  FilledButton(
                    onPressed: () async {
                      BixolonPlugin().dispose();
                    },
                    child: const Text('dispose'),
                  ),
                ],
              ),
              const SizedBox(height: 10),
               RepaintBoundary(
                key: key,
                child: Container(
                  color: Colors.white,
                  child: Image.asset(
                    'assets/test.png',
                    height: 300,
                    fit: BoxFit.cover,
                  ),
                ),
              ),
              if (pairedDeviceList.isNotEmpty)
                Expanded(
                  child: ListView.builder(
                    itemCount: pairedDeviceList.length,
                    itemBuilder: (context, index) {
                      return ListTile(
                        title: Text(
                          pairedDeviceList[index].logicalName,
                          style: const TextStyle(
                            fontSize: 18,
                          ),
                        ),
                        subtitle: Text(
                          pairedDeviceList[index].macAddress,
                          style: const TextStyle(
                            fontSize: 18,
                          ),
                        ),
                        onTap: () async {
                          BixolonPlugin().selectPrinter(pairedDeviceList[index].macAddress);
                        },
                      );
                    },
                  ),
                )
            ],
          ),
        ),
      ),
    );
  }

  void checkPermission() async {
    await Permission.bluetooth.request();
    await Permission.bluetoothScan.request();
    await Permission.bluetoothConnect.request();
    await Permission.location.request();
  }
}
