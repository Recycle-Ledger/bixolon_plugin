import 'package:flutter_test/flutter_test.dart';
import 'package:bixolon_plugin/src/bixolon_plugin.dart';
import 'package:bixolon_plugin/bixolon_plugin_platform_interface.dart';
import 'package:bixolon_plugin/bixolon_plugin_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockBixolonPluginPlatform
    with MockPlatformInterfaceMixin
    implements BixolonPluginPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final BixolonPluginPlatform initialPlatform = BixolonPluginPlatform.instance;

  test('$MethodChannelBixolonPlugin is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelBixolonPlugin>());
  });

  test('getPlatformVersion', () async {
    BixolonPlugin bixolonPlugin = BixolonPlugin();
    MockBixolonPluginPlatform fakePlatform = MockBixolonPluginPlatform();
    BixolonPluginPlatform.instance = fakePlatform;

    expect(await bixolonPlugin.getPlatformVersion(), '42');
  });
}
