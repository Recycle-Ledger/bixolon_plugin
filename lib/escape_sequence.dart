import 'dart:convert';

class EscapeSequence {
  final String prefix = utf8.decode([0x1b, 0x7c]);

  String spaceBetween(String prefix, String suffix) {
    int spaceByte = 32 - _getByteSize(prefix + suffix);
    String space = '';
    if (spaceByte <= 0) {
      space = ' ';
    }
    for (int i = 0; i < spaceByte; i++) {
      space += ' ';
    }
    return prefix + space + suffix;
  }

  int _getByteSize(String str) {
    int byteSize = str.runes.fold(0, (previousValue, element) {
      if (element <= 0x7F) {
        // ASCII 문자인 경우 1바이트로 계산
        return previousValue + 1;
      } else if (element <= 0xFFFF) {
        // BMP 평면의 문자인 경우 2바이트로 계산
        return previousValue + 2;
      } else {
        // 서로게이트 쌍을 포함한 문자인 경우 4바이트로 계산
        return previousValue + 4;
      }
    });
    return byteSize;
  }
}

extension Suffix on EscapeSequence {
  String get normal => '${prefix}N';
  String get fontA => '${prefix}aM';
  String get fontB => '${prefix}bM';
  String get fontC => '${prefix}cM';
  String get leftJustify => '${prefix}lA';
  String get center => '${prefix}cA';
  String get rightJustify => '${prefix}rA';
  String get bold => '${prefix}bC';
  String get disabledBold => '$prefix!bC';
  String get underline => '${prefix}uC';
  String get disabledUnderline => '$prefix!uC';
  String get reverseVideo => '${prefix}rvC';
  String get disabledReverseVideo => '$prefix!rvC';
  String get singleHighAndWide => '${prefix}1C';
  String get doubleWide => '${prefix}2C';
  String get doubleHigh => '${prefix}3C';
  String get doubleHighAndWide => '${prefix}4C';
  String get scale1Horizontally => '${prefix}1hC';
  String get scale2Horizontally => '${prefix}2hC';
  String get scale3Horizontally => '${prefix}3hC';
  String get scale4Horizontally => '${prefix}4hC';
  String get scale5Horizontally => '${prefix}5hC';
  String get scale6Horizontally => '${prefix}6hC';
  String get scale7Horizontally => '${prefix}7hC';
  String get scale8Horizontally => '${prefix}8hC';
  String get scale1Vertically => '${prefix}1vC';
  String get scale2Vertically => '${prefix}2vC';
  String get scale3Vertically => '${prefix}3vC';
  String get scale4Vertically => '${prefix}4vC';
  String get scale5Vertically => '${prefix}5vC';
  String get scale6Vertically => '${prefix}6vC';
  String get scale7Vertically => '${prefix}7vC';
  String get scale8Vertically => '${prefix}8vC';
}