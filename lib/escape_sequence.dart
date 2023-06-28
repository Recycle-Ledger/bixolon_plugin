import 'dart:convert';

class EscapeSequence {
  final String prefix = utf8.decode([0x1b, 0x7c]);
  final int oneLineByte = 32;

  String spaceBetween(String prefix, String suffix) {
    int spaceByte = oneLineByte - _getByteSize(prefix + suffix);
    String space = '';
    if (spaceByte <= 0 && !prefix.endsWith(' ')) {
      space = ' ';
    }
    for (int i = 0; i < spaceByte; i++) {
      space += ' ';
    }
    return prefix + space + suffix;
  }

  // 입력받은 문자열을 리미트바이트를 기준으로 자동개행을 해준다. (영문 숫자 1바이트 한글 2바이트)
  // ex) rawString : 123123456, limitByte : 4
  // 1231
  // 2345
  // 6
  String autoLineBreak({required String rawString, required int limitByte}) {
    final int rawByte = _getByteSize(rawString);
    if (rawByte <= limitByte) {
      // 리미트만큼 마지막 글자 끝에 공백을 채워준다.
      return rawString + (' ' * (limitByte - rawByte));
    } else {
      final splitWords = _splitStringByByte(rawString, limitByte);
      // 한줄 개행을 하기 위해 첫번째 글자에 한줄이 채워질 만큼 공백을 더해준다.
      String word1 = splitWords.word1 + (' ' * (oneLineByte - limitByte));
      // 리미트 바이트 만큼 앞의 문자열을 잘라내고 남은 문자열을 다시 재귀함수를 돌려서 자동개행이 불가능할때까지 잘라준다.
      return word1 + autoLineBreak(rawString: splitWords.word2, limitByte: limitByte);
    }
  }

  // 입력받은 문자열을 입력한 바이트길이를 기준으로 2개의 단어로 분리해준다.
  ({String word1, String word2}) _splitStringByByte(String rawString, int byte) {
    final Runes inputRunes = rawString.runes;
    int currentByte = 0;

    for (int i = 0; i < inputRunes.length; i++) {
      final int element = inputRunes.elementAt(i);
      if (element <= 0x7F) {
        // ASCII 문자인 경우 1바이트로 계산
        currentByte += 1;
      } else if (element <= 0xFFFF) {
        // BMP 평면의 문자인 경우 2바이트로 계산
        currentByte += 2;
      } else {
        // 서로게이트 쌍을 포함한 문자인 경우 4바이트로 계산
        currentByte += 4;
      }

      if (currentByte == byte) {
        return (word1: rawString.substring(0, i + 1), word2: rawString.substring(i + 1));
      }
      if (currentByte > byte) {
        return (word1: rawString.substring(0, i), word2: rawString.substring(i));
      }
    }
    return (word1: rawString, word2: '');
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