import 'dart:convert';

class EscapeSequence {
  final String prefix = utf8.decode([0x1b, 0x7c]);
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
  String get scale1TimeHorizontally => '${prefix}1hC';
  String get scale2TimesHorizontally => '${prefix}2hC';
  String get scale3TimesHorizontally => '${prefix}3hC';
  String get scale4TimesHorizontally => '${prefix}4hC';
  String get scale5TimesHorizontally => '${prefix}5hC';
  String get scale6TimesHorizontally => '${prefix}6hC';
  String get scale7TimesHorizontally => '${prefix}7hC';
  String get scale8TimesHorizontally => '${prefix}8hC';
  String get scale1TimeVertically => '${prefix}1vC';
  String get scale2TimesVertically => '${prefix}2vC';
  String get scale3TimesVertically => '${prefix}3vC';
  String get scale4TimesVertically => '${prefix}4vC';
  String get scale5TimesVertically => '${prefix}5vC';
  String get scale6TimesVertically => '${prefix}6vC';
  String get scale7TimesVertically => '${prefix}7vC';
  String get scale8TimesVertically => '${prefix}8vC';
}