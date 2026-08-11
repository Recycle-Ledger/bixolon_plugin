class BluetoothDevice {
  final String logicalName;
  final String macAddress;

  const BluetoothDevice({
    required this.logicalName,
    required this.macAddress,
  });

  @override
  bool operator ==(Object other) =>
      identical(this, other) ||
      (other is BluetoothDevice &&
          runtimeType == other.runtimeType &&
          logicalName == other.logicalName &&
          macAddress == other.macAddress);

  @override
  int get hashCode => logicalName.hashCode ^ macAddress.hashCode;

  @override
  String toString() {
    return 'BluetoothDevice{ logicalName: $logicalName, macAddress: $macAddress,}';
  }

  BluetoothDevice copyWith({
    String? logicalName,
    String? macAddress,
  }) {
    return BluetoothDevice(
      logicalName: logicalName ?? this.logicalName,
      macAddress: macAddress ?? this.macAddress,
    );
  }

  Map<String, dynamic> toMap() {
    return {
      'logicalName': logicalName,
      'macAddress': macAddress,
    };
  }

  factory BluetoothDevice.fromMap(Map<String, dynamic> map) {
    final macAddress = map['macAddress'] as String? ?? '';
    return BluetoothDevice(
      // 일부 기기는 캐시된 이름이 없어 네이티브 쪽에서 logicalName이 null로 올 수 있다.
      // 화면이 깨지지 않도록 주소를 대체 표시 이름으로 사용한다.
      logicalName: map['logicalName'] as String? ?? macAddress,
      macAddress: macAddress,
    );
  }
}