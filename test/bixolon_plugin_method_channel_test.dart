import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:bixolon_plugin/bixolon_plugin_method_channel.dart';

void main() {
  MethodChannelBixolonPlugin platform = MethodChannelBixolonPlugin();
  const MethodChannel channel = MethodChannel('bixolon_plugin');

  TestWidgetsFlutterBinding.ensureInitialized();

  setUp(() {
    channel.setMockMethodCallHandler((MethodCall methodCall) async {
      return '42';
    });
  });

  tearDown(() {
    channel.setMockMethodCallHandler(null);
  });

  test('getPlatformVersion', () async {
    expect(await platform.getPlatformVersion(), '42');
  });
}
