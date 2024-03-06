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
    return BluetoothDevice(
      logicalName: map['logicalName'] as String,
      macAddress: map['macAddress'] as String,
    );
  }
}