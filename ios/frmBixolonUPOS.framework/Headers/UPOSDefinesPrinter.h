//
// ----------------------------------------
//
// File : UPOSDefinesPrinter.h
// Date : 08/08/2019
//
// ========================================
        

#ifndef UPOSDefinesPrinter_h
#define UPOSDefinesPrinter_h


typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_STATION) {
    PTR_S_JOURNAL        DEPRECATED_MSG_ATTRIBUTE("not USE") = 1,
    PTR_S_RECEIPT        = 2,
    PTR_S_SLIP           DEPRECATED_MSG_ATTRIBUTE("not USE") = 4,
    
    PTR_S_JOURNAL_RECEIPT    DEPRECATED_MSG_ATTRIBUTE("not USE") = 0x0003,
    PTR_S_JOURNAL_SLIP       DEPRECATED_MSG_ATTRIBUTE("not USE") = 0x0005,
    PTR_S_RECEIPT_SLIP       DEPRECATED_MSG_ATTRIBUTE("not USE") = 0x0006,
    
    PTR_TWO_RECEIPT_JOURNAL  DEPRECATED_MSG_ATTRIBUTE("not USE") = 0x8003,
    PTR_TWO_SLIP_JOURNAL     DEPRECATED_MSG_ATTRIBUTE("not USE") = 0x8005,
    PTR_TWO_SLIP_RECEIPT     DEPRECATED_MSG_ATTRIBUTE("not USE") = 0x8006
};

/**
 * "Alignment" Parameter
 */
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_BARCODE_ALIGNMENT) {
    PTR_BC_LEFT          = -1,
    PTR_BC_CENTER        = -2,
    PTR_BC_RIGHT         = -3
};

/**
 * "Width" Parameter
 */
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_BITMAP_WIDTH) {
    PTR_BM_ASIS          = -11,
};

/**
 * "TextPosition" Parameter
 */
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_BARCODE_TEXT_POSITION) {
    PTR_BC_TEXT_NONE     = -11,
    PTR_BC_TEXT_ABOVE    = -12,
    PTR_BC_TEXT_BELOW    = -13
};


/**
 * "Symbology" Parameter:
 */
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_BARCODE_SYMBOLOGIES) {
    PTR_BCS_UPCA         = 101,
    PTR_BCS_UPCE         = 102,
    PTR_BCS_JAN8         = 103,
    PTR_BCS_EAN8         = PTR_BCS_JAN8,
    PTR_BCS_JAN13        = 104,
    PTR_BCS_EAN13        = PTR_BCS_JAN13,
    PTR_BCS_TF           DEPRECATED_MSG_ATTRIBUTE("not USE") = 105,
    PTR_BCS_ITF          = 106,
    PTR_BCS_Codabar      = 107,
    PTR_BCS_Code39       = 108,
    PTR_BCS_Code93       = 109,
    PTR_BCS_Code128      = 110,
    PTR_BCS_UPCA_S       DEPRECATED_MSG_ATTRIBUTE("not USE") = 111,
    PTR_BCS_UPCE_S       DEPRECATED_MSG_ATTRIBUTE("not USE") = 112,
    PTR_BCS_UPCD1        DEPRECATED_MSG_ATTRIBUTE("not USE") = 113,
    PTR_BCS_UPCD2        DEPRECATED_MSG_ATTRIBUTE("not USE") = 114,
    PTR_BCS_UPCD3        DEPRECATED_MSG_ATTRIBUTE("not USE") = 115,
    PTR_BCS_UPCD4        DEPRECATED_MSG_ATTRIBUTE("not USE") = 116,
    PTR_BCS_UPCD5        DEPRECATED_MSG_ATTRIBUTE("not USE") = 117,
    PTR_BCS_EAN8_S       DEPRECATED_MSG_ATTRIBUTE("not USE") = 118,
    PTR_BCS_EAN13_S      DEPRECATED_MSG_ATTRIBUTE("not USE") = 119,
    PTR_BCS_EAN128       DEPRECATED_MSG_ATTRIBUTE("not USE") = 120,
    PTR_BCS_OCRA         DEPRECATED_MSG_ATTRIBUTE("not USE") = 121,
    PTR_BCS_OCRB         DEPRECATED_MSG_ATTRIBUTE("not USE") = 122,
    PTR_BCS_Code128_Parsed  DEPRECATED_MSG_ATTRIBUTE("not USE") = 123,
    PTR_BCS_RSS14        DEPRECATED_MSG_ATTRIBUTE("not USE") = 131,
    PTR_BCS_RSS_EXPANDED DEPRECATED_MSG_ATTRIBUTE("not USE") = 132,
    PTR_BCS_GS1DATABAR    DEPRECATED_MSG_ATTRIBUTE("not USE") = 131,
    PTR_BCS_GS1DATABAR_E  DEPRECATED_MSG_ATTRIBUTE("not USE") = 132,
    PTR_BCS_GS1DATABAR_S  DEPRECATED_MSG_ATTRIBUTE("not USE") = 133,
    PTR_BCS_GS1DATABAR_E_S  DEPRECATED_MSG_ATTRIBUTE("not USE") = 134,
    PTR_BCS_PDF417       = 201,
    PTR_BCS_MAXICODE     DEPRECATED_MSG_ATTRIBUTE("not USE") = 202,
    PTR_BCS_DATAMATRIX   = 203,
    PTR_BCS_QRCODE       = 204,
    PTR_BCS_UQRCODE      DEPRECATED_MSG_ATTRIBUTE("not USE") = 205,  // Micro QR Code
    PTR_BCS_AZTEC        DEPRECATED_MSG_ATTRIBUTE("not USE") = 206,  // Aztec
    PTR_BCS_UPDF417      DEPRECATED_MSG_ATTRIBUTE("not USE") = 207,  // Micro PDF 417
    PTR_BCS_OTHER        DEPRECATED_MSG_ATTRIBUTE("QRCode Same type") = 501
};


/**
 * "Alignment" Parameter:
 * using PrintBitmap or PrintPDF parameter
 */
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_BITMAP_ALIGNMENT) {
    PTR_BM_LEFT          = -1,
    PTR_BM_CENTER        = -2,
    PTR_BM_RIGHT         = -3
};


/**
 * "TransactionPrint" Method
 * PTR_TP_TRANSACTION is transaction mode on
 * PTR_TP_NORMAL is transaction mode off
 */
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_TRANSACTION) {
    PTR_TP_TRANSACTION   = 11,
    PTR_TP_NORMAL        = 12
};


/**
 * "setPagemodeDirection" Method
 */
typedef NS_ENUM(NSUInteger, PAGE_MODE_DIRECTION) {
    LEFT_TO_RIGHT = 0,
    BOTTOM_TO_TOP,
    RIGHT_TO_LEFT,
    TOP_TO_BOTTOM
};

typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_PAGE_MODE_DIRECTION) {
    PTR_PD_LEFT_TO_RIGHT DEPRECATED_MSG_ATTRIBUTE("not USE") = 1,
    PTR_PD_BOTTOM_TO_TOP DEPRECATED_MSG_ATTRIBUTE("not USE"),
    PTR_PD_RIGHT_TO_LEFT DEPRECATED_MSG_ATTRIBUTE("not USE"),
    PTR_PD_TOP_TO_BOTTOM DEPRECATED_MSG_ATTRIBUTE("not USE")
};


/**
 * "statusUpdateEvent" Event
 */
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_STATUS) {
    PTR_SUE_COVER_OPEN              = 11,
    PTR_SUE_COVER_OK                = 12,
    PTR_SUE_OFF_LINE                = 53,
    PTR_SUE_REC_EMPTY               = 24,
    PTR_SUE_REC_NEAREMPTY           = 25,
    PTR_SUE_REC_PAPEROK             = 26,
    PTR_SUE_REC_BATTERY_NORMAL      = 60,
    PTR_SUE_REC_BATTERY_LOW         = 61,
    PTR_SUE_BAT_OK                  = 55,
    PTR_SUE_BAT_LOW                 = 56,
};



typedef NS_OPTIONS(NSUInteger, __UPOS_CHARACTER_SET) {
    PTR_CC_ALPHA        =   1,
    PTR_CC_KANA         =  10,
    PTR_CC_KANJI        =  11,
    PTR_CC_ASCII        = 998,
    PTR_CC_UNICODE      = 997,
    PTR_CS_ANSI          = 999,
    PTR_CS_WINDOWS       = PTR_CS_ANSI
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");

typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_ERROR_LEVEL) {
    PTR_EL_NONE          = 1,
    PTR_EL_RECOVERABLE   = 2,
    PTR_EL_FATAL         = 3
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");

typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_MAP_MODE) {
    PTR_MM_DOTS          = 1,
    PTR_MM_TWIPS         = 2,
    PTR_MM_ENGLISH       = 3,
    PTR_MM_METRIC        = 4
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_COLOR) {
    PTR_COLOR_PRIMARY      = 0x00000001,
    PTR_COLOR_CUSTOM1      = 0x00000002,
    PTR_COLOR_CUSTOM2      = 0x00000004,
    PTR_COLOR_CUSTOM3      = 0x00000008,
    PTR_COLOR_CUSTOM4      = 0x00000010,
    PTR_COLOR_CUSTOM5      = 0x00000020,
    PTR_COLOR_CUSTOM6      = 0x00000040,
    PTR_COLOR_CYAN         = 0x00000100,
    PTR_COLOR_MAGENTA      = 0x00000200,
    PTR_COLOR_YELLOW       = 0x00000400,
    PTR_COLOR_FULL         = 0x80000000
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_CARTRIDGE_SENSOR) {
    PTR_CART_UNKNOWN         = 0x10000000,
    PTR_CART_OK              = 0x00000000,
    PTR_CART_REMOVED         = 0x00000001,
    PTR_CART_EMPTY           = 0x00000002,
    PTR_CART_NEAREND         = 0x00000004,
    PTR_CART_CLEANING        = 0x00000008
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_CARTRIDGE_NOTIFY) {
    PTR_CN_DISABLED        = 0x00000000,
    PTR_CN_ENABLED         = 0x00000001
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_CUT_PAPER_LEVEL) {
    PTR_CP_FULLCUT       = 100
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_PAGE_MODE_PRINT) {
    PTR_PM_PAGE_MODE      = 1,
    PTR_PM_PRINT_SAVE     = 2,
    PTR_PM_NORMAL         = 3,
    PTR_PM_CANCEL         = 4
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_ROTATE) {
    PTR_RP_NORMAL        = 0x0001,
    PTR_RP_RIGHT90       = 0x0101,
    PTR_RP_LEFT90        = 0x0102,
    PTR_RP_ROTATE180     = 0x0103,
    
    // For "RotatePrint", one or both of the following values may be
    // ORed with one of the above values.
    PTR_RP_BARCODE       = 0x1000,
    PTR_RP_BITMAP        = 0x2000,
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_LOGO) {
    PTR_L_TOP            = 1,
    PTR_L_BOTTOM         = 2
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_MARK_FEED_TYPE) {
    PTR_MF_TO_TAKEUP     = 1,
    PTR_MF_TO_CUTTER     = 2,
    PTR_MF_TO_CURRENT_TOF= 4,
    PTR_MF_TO_NEXT_TOF   = 8
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_SIDE) {
    PTR_PS_UNKNOWN       = 0,
    PTR_PS_SIDE1         = 1,
    PTR_PS_SIDE2         = 2,
    PTR_PS_OPPOSITE      = 3
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSUInteger, __UPOS_PRINTER_RESULTCODE_EXTENDED) {
    UPOS_EPTR_COVER_OPEN            = 201, // (Several)
    UPOS_EPTR_JRN_EMPTY             = 202, // (Several)
    UPOS_EPTR_REC_EMPTY             = 203, // (Several)
    UPOS_EPTR_SLP_EMPTY             = 204, // (Several)
    UPOS_EPTR_SLP_FORM              = 205, // EndRemoval
    UPOS_EPTR_TOOBIG                = 206, // PrintBitmap
    UPOS_EPTR_BADFORMAT             = 207, // PrintBitmap
    UPOS_EPTR_JRN_CARTRIDGE_REMOVED = 208, // (Several)
    UPOS_EPTR_JRN_CARTRIDGE_EMPTY   = 209, // (Several)
    UPOS_EPTR_JRN_HEAD_CLEANING     = 210, // (Several)
    UPOS_EPTR_REC_CARTRIDGE_REMOVED = 211, // (Several)
    UPOS_EPTR_REC_CARTRIDGE_EMPTY   = 212, // (Several)
    UPOS_EPTR_REC_HEAD_CLEANING     = 213, // (Several)
    UPOS_EPTR_SLP_CARTRIDGE_REMOVED = 214, // (Several)
    UPOS_EPTR_SLP_CARTRIDGE_EMPTY   = 215, // (Several)
    UPOS_EPTR_SLP_HEAD_CLEANING     = 216 // (Several)
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");
typedef NS_OPTIONS(NSStringEncoding, __UPOS_ENCODING_OPTIONS) {
    _UPOS_ENCODING_OPTION_ASCII          = 0x00000001,
    _UPOS_ENCODING_OPTION_KSC5601        = 0x80000422,
    _UPOS_ENCODING_OPTION_SHIFT_JIS      = 0x00000008,
    _UPOS_ENCODING_OPTION_BIG5           = 0x80000a03,
    _UPOS_ENCODING_OPTION_GB2312         = 0x80000421,
    _UPOS_ENCODING_OPTION_GB18030        = 0x80000632,
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


#endif /* UPOSDefinesPrinter_h */
