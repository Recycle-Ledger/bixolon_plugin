import 'dart:io';

import 'package:bixolon_plugin/bixolon_plugin.dart';
import 'package:bixolon_plugin/bluetooth_device.dart';
import 'package:bixolon_plugin/escape_sequence.dart';
import 'package:bixolon_plugin/common_symbol.dart';
import 'package:file_picker/file_picker.dart';
import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'package:path_provider/path_provider.dart';
import 'package:pdf/pdf.dart';
import 'package:pdf/widgets.dart' as pw;
import 'dart:async';
import 'dart:ui' as ui;

import 'package:flutter/services.dart';
import 'package:pdf_render/pdf_render_widgets.dart';
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
  String pdfPath = '';

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
                      try {
                        BixolonPlugin().init();
                      } catch (error, stackTrace) {}
                    },
                    child: const Text('init'),
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
                      /*BixolonPlugin().printText('${es.normal}\n');
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
                      BixolonPlugin().printText('${es.normal}\n\n');*/

                      BixolonPlugin().printText('${es.normal}\n\n');
                      BixolonPlugin().printText('${es.doubleHighAndWide}${es.bold}${es.center}영수증\n\n\n');
                      BixolonPlugin().printText('${es.normal}${es.bold}[구 매 처]\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('상ㅤㅤ호 :', '삼보식당')}\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('담 당 자 :', '페드로')}\n');
                      BixolonPlugin().printText('${es.normal}${CommonSymbol.dash}\n');
                      BixolonPlugin().printText('${es.normal}${es.bold}[공 급 처]\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('상ㅤㅤ호 :', '다둥유통')}\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('담 당 자 :', '황미남')}\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('사업자등록번호 : ', '686-74-00386')}\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('주ㅤㅤ소 :', '충청남도 아산시 배방읍 모산로 52')}\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('업태 : 도소매', '종목 : 식용유')}\n');
                      BixolonPlugin().printText('${es.normal}\n');
                      BixolonPlugin().printText('${es.normal}${CommonSymbol.stroke}\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('품목    수량    단가', '공급대가')}\n');
                      BixolonPlugin().printText('${es.normal}${CommonSymbol.stroke}\n');
                      BixolonPlugin().printText('${es.normal}${es.autoLineBreak(rawString: '식용유', limitByte: 8)} ${'3'.padLeft(3)}${'58,000'.padLeft(8)}${'174,000'.padLeft(12)}\n');
                      BixolonPlugin().printText('${es.normal}${es.autoLineBreak(rawString: '폐식용용용용유', limitByte: 8)} ${'5'.padLeft(3)}${'-4,000'.padLeft(8)}${'-20,000'.padLeft(12)}\n');
                      BixolonPlugin().printText('${es.normal}\n');
                      BixolonPlugin().printText('${es.normal}${CommonSymbol.dash}\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('금일합계 :', '154,000')}\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('미 수 금 :', '333,000')}\n');
                      BixolonPlugin().printText('${es.normal}\n');
                      BixolonPlugin().printText('${es.doubleHigh}${es.spaceBetween('총 합 계 :', '487,000')}\n');
                      BixolonPlugin().printText('${es.normal}\n');
                      BixolonPlugin().printText('${es.normal}${es.center}위 금액을 정히 영수(청구)함\n');
                      BixolonPlugin().printText('${es.normal}${es.center}2023년 12월 12일\n');
                      BixolonPlugin().printText('${es.normal}\n');
                      BixolonPlugin().printText('${es.normal}${CommonSymbol.doubleDash}\n');
                      BixolonPlugin().printText('${es.normal}${es.bold}[계좌번호]\n');
                      BixolonPlugin().printText('${es.normal}${es.spaceBetween('농협은행', '356-0711-2177-73 황미남')}\n');
                      BixolonPlugin().printText('${es.normal}\n\n\n');

                      // BixolonPlugin().printText('${es.normal}${es.center}상기 폐식용유를 수집하였음\n');
                      // BixolonPlugin().printText('${es.normal}${es.center}2023년 5월 3일\n\n');
                      // BixolonPlugin().printText('${es.normal}\n\n');
                      // BixolonPlugin().printText('${es.normal}${es.doubleWide}서명\n\n');
                      // BixolonPlugin().printImage(await widgetToByteArray());
                      // BixolonPlugin().printText('${es.normal}\n\n');
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
                      final List<List<String>> dataTable = [
                        ['1', 'abc', '30'],
                        ['2', '개발자', '10'],
                        ['3', '테스트', '20'],
                      ];
                      final pdf = pw.Document();
                      final fontBase = await rootBundle.load('assets/fonts/PretendardVariable.ttf');
                      pdf.addPage(
                        pw.Page(
                          pageTheme: pw.PageTheme(
                              pageFormat: PdfPageFormat(
                              57 * PdfPageFormat.mm,
                              double.infinity,
                              marginAll: 2.5 * PdfPageFormat.mm,
                            ),
                              theme: pw.ThemeData.withFont(
                                base: pw.Font.ttf(fontBase),
                              )),
                          build: (pw.Context context) {
                            return pw.TableHelper.fromTextArray(
                              border: pw.TableBorder.all(
                                width: 0.1,
                              ),
                              headers: ['번호', '이름', '나이'],
                              data: List<List<dynamic>>.generate(
                                dataTable.length,
                                (index) => <dynamic>[
                                  dataTable[index][0],
                                  dataTable[index][1],
                                  dataTable[index][2],
                                ],
                              ),
                              headerDecoration: const pw.BoxDecoration(
                                color: PdfColors.white,
                              ),
                              rowDecoration: const pw.BoxDecoration(
                                border: pw.Border(
                                  bottom: pw.BorderSide(
                                    color: PdfColors.black,
                                    width: .5,
                                  ),
                                ),
                              ),
                              cellAlignment: pw.Alignment.centerRight,
                              cellAlignments: {0: pw.Alignment.centerLeft},
                            );
                          },
                        ),
                      ); // Page

                      final output = await getTemporaryDirectory();
                      final file = File('${output.path}/example.pdf');
                      await file.writeAsBytes(await pdf.save());
                      print("@@@ path : ${file.path}");
                      setState(() {

                      });

                      BixolonPlugin().printPDF(file.path);
                    },
                    child: const Text('pdf print'),
                  ),
                  FilledButton(
                    onPressed: () async {
                      final result = await FilePicker.platform.pickFiles(allowedExtensions: ['pdf'],type: FileType.custom);
                      if (result == null) {
                        return;
                      }
                      BixolonPlugin().printPDF(result.paths[0]!);
                    },
                    child: const Text('pdf picker'),
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
              SizedBox(
                height: 200,
                child: PdfViewer.openFile(
                  '/var/mobile/Containers/Data/Application/D6EFBE0E-4268-4735-91BE-B6EEBE7B9B9B/Library/Caches/example.pdf',
                ),
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
                          if (Platform.isAndroid) {
                            BixolonPlugin().selectPrinter(pairedDeviceList[index].macAddress);
                          } else {
                            BixolonPlugin().selectPrinter(pairedDeviceList[index].logicalName);
                          }
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
