
#ifndef UPOSDefinesScr_h
#define UPOSDefinesScr_h

#include "UPOSDefines.h"

typedef NS_OPTIONS(NSUInteger, __UPOS_SCR_READ_DATA_ACTION) {
    SC_READ_DATA        =  11,
};

typedef NS_OPTIONS(NSUInteger, __UPOS_SCR_CAP_ISO_EMV_MODE) {
    SC_CMODE_ISO         =   1,
    SC_CMODE_EMV         =   2
};

typedef NS_OPTIONS(NSUInteger, __UPOS_SCR_RESPONSE) {
    _UPOS_SCR_RESPONSE_SUCCESSFUL                       = 0x00,
    _UPOS_SCR_RESPONSE_WRONG_COMMAND_LENGTH             = 0x01,
    _UPOS_SCR_RESPONSE_EXCESSIVE_CURRENT_POWEROFF       = 0x02,
    _UPOS_SCR_RESPONSE_DEFECTIVE_VOLTAGE_POWEROFF       = 0x03,
    _UPOS_SCR_RESPONSE_INVALID_07                       = 0x07,
    _UPOS_SCR_RESPONSE_INVALID_08                       = 0x08,
    _UPOS_SCR_RESPONSE_INVALID_09                       = 0x09,
    _UPOS_SCR_RESPONSE_INVALID_0A                       = 0x0A,
    _UPOS_SCR_RESPONSE_INVALID_15                       = 0x15,
    _UPOS_SCR_RESPONSE_SHORT_CIRCUITING                 = 0xA2,
    _UPOS_SCR_RESPONSE_ATR_TOO_LONG                     = 0xA3,
    _UPOS_SCR_RESPONSE_CARD_IS_TOO_LONG                 = 0xB0,
    _UPOS_SCR_RESPONSE_PROTOCOL_ERROR_IN_EMV            = 0xBB,
    _UPOS_SCR_RESPONSE_PROTOCOL_ERROR_DURING_T1EXCHANGE = 0xBD,
    _UPOS_SCR_RESPONSE_APDU_LENGTH_WRONG                = 0xBE,
    _UPOS_SCR_RESPONSE_INVALID_TCK_OF_ATR               = 0xF7,
    _UPOS_SCR_RESPONSE_INVALID_TS_OF_ATR                = 0xF8,
    _UPOS_SCR_RESPONSE_PARITY_ERROR                     = 0xFD,
    _UPOS_SCR_RESPONSE_CARD_IS_NOT_PRESENT_OR_MUTE      = 0xFE,
    _UPOS_SCR_RESPONSE_NO_USED                          = 0xFF,
    
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


#endif /* UPOSDefinesScr_h */
