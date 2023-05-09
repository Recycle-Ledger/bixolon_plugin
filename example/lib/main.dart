import 'dart:io';

import 'package:bixolon_plugin/bixolon_plugin.dart';
import 'package:bixolon_plugin/bluetooth_device.dart';
import 'package:bixolon_plugin/escape_sequence.dart';
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
                        print("@@@ catch error : ${error.toString()}");
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
                      BixolonPlugin().printText('${es.center}=================\n${es.doubleHighAndWide}${es.scale2TimesHorizontally}서울 강남구\n${es.normal}(역삼동, 한국지식재산센터)\n02-1566-5701');
                    },
                    child: const Text('text print'),
                  ),
                  FilledButton(
                    onPressed: () async {
                      BixolonPlugin().printImage(await widgetToByteArray());
                    },
                    child: const Text('png print'),
                  ),
                ],
              ),
              const SizedBox(height: 10),
              RepaintBoundary(
                key: key,
                child: Container(
                  color: Colors.white,
                  child: Text(
                    'text print\n서울 강남구 테헤란로 131, 15층\n(역삼동, 한국지식재산센터)\n02-1566-5701',
                    style: TextStyle(
                      fontSize: 24,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),
              ),
              /* RepaintBoundary(
                key: key,
                child: Container(
                  color: Colors.white,
                  child: Image.asset(
                    'assets/test.png',
                    height: 300,
                    fit: BoxFit.cover,
                  ),
                ),
              ),*/
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
