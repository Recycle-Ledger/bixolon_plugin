//
// ----------------------------------------
//
// File : UPOSDefines.h
// Date : 16/07/2019
//
// ========================================
        

#ifndef UPOSDefines_h
#define UPOSDefines_h

/**
 * @breif about refresh API notification Key name
 */
#define __NOTIFICATION_NAME_WIFI_WILL_LOOKUP_           @"__NotificationName_WifiLookupWillStart"
#define __NOTIFICATION_NAME_WIFI_FOUND_PRINTER_         @"__NotificationName_WifiPrinterFound"
#define __NOTIFICATION_NAME_WIFI_LOOKUP_COMPLETE_       @"__NotificationName_WifiLookupComplete"

#define __NOTIFICATION_NAME_ETHERNET_WILL_LOOKUP_       @"__NotificationName_EthernetLookupWillStart"
#define __NOTIFICATION_NAME_ETHERNET_FOUND_PRINTER_     @"__NotificationName_EthernetPrinterFound"
#define __NOTIFICATION_NAME_ETHERNET_LOOKUP_COMPLETE_   @"__NotificationName_EthernetLookupComplete"

#define __NOTIFICATION_NAME_BT_WILL_LOOKUP_             @"__NotificationName_BTLookupWillStart"
#define __NOTIFICATION_NAME_BT_FOUND_PRINTER_           @"__NotificationName_BTPrinterFound"
#define __NOTIFICATION_NAME_BT_LOOKUP_COMPLETE_         @"__NotificationName_BTLookupComplete"

#define __NOTIFICATION_NAME_BLE_WILL_LOOKUP_            @"__NotificationName_BLELookupWillStart"
#define __NOTIFICATION_NAME_BLE_FOUND_PRINTER_          @"__NotificationName_BLEPrinterFound"
#define __NOTIFICATION_NAME_BLE_LOOKUP_COMPLETE_        @"__NotificationName_BLELookupComplete"


/**
 * @brief about setLogLevel API
 */
#define LOG_SHOW_NEVER  0x00
#define LOG_SHOW_ALL    0xff



/**
 * @breif API Result Codes
 */
typedef NS_OPTIONS(NSUInteger, __UPOS_RESULT_CODE) {
    UPOS_SUCCESS        = 0,
    
    UPOS_E_CLOSED       DEPRECATED_MSG_ATTRIBUTE("case in, close status") = 101,
    UPOS_E_CLAIMED      DEPRECATED_MSG_ATTRIBUTE("already claimed") = 102,
    UPOS_E_NOTCLAIMED   DEPRECATED_MSG_ATTRIBUTE("case in, not claim status") = 103,
    UPOS_E_NOSERVICE    DEPRECATED_MSG_ATTRIBUTE("not use") = 104,
    UPOS_E_DISABLED     DEPRECATED_MSG_ATTRIBUTE("case in, disabled status") = 105,
    UPOS_E_ILLEGAL      DEPRECATED_MSG_ATTRIBUTE("case in. write fail or call a function that is not supported") = 106,
    UPOS_E_NOHARDWARE   DEPRECATED_MSG_ATTRIBUTE("not USE") = 107,
    UPOS_E_OFFLINE      DEPRECATED_MSG_ATTRIBUTE("not USE") = 108,
    UPOS_E_NOEXIST      DEPRECATED_MSG_ATTRIBUTE("not USE") = 109,
    UPOS_E_EXISTS       DEPRECATED_MSG_ATTRIBUTE("not USE") = 110,
    UPOS_E_FAILURE      DEPRECATED_MSG_ATTRIBUTE("case in. open fail") = 111,
    UPOS_E_TIMEOUT      DEPRECATED_MSG_ATTRIBUTE("not USE") = 112,
    UPOS_E_BUSY         DEPRECATED_MSG_ATTRIBUTE("not USE") = 113,
    UPOS_E_EXTENDED     DEPRECATED_MSG_ATTRIBUTE("not USE") = 114,
    UPOS_E_DEPRECATED   DEPRECATED_MSG_ATTRIBUTE("not USE") = 115,
    
    UPOS_E_ENCODING     = 116,  // case in. text encoding error
    
    UPOSERR             DEPRECATED_MSG_ATTRIBUTE("not USE") = 100,
    UPOSERREXT          DEPRECATED_MSG_ATTRIBUTE("not USE") = 200
};


/**
 * @typedef __INTERFACE_TYPE
 * @breif interface type define
 * @constant for about refresh APIs or about connect APIs
 */
typedef NS_OPTIONS(NSUInteger, __INTERFACE_TYPE) {
    _INTERFACETYPE_WIFI                    = 1,
    _INTERFACETYPE_ETHERNET                = 2,
    _INTERFACETYPE_BLUETOOTH               = 4,
    _INTERFACETYPE_BLE                     = 6,
    
    _INTERFACETYPE_BLUETOOTH_NON_EXCLUSIVE DEPRECATED_MSG_ATTRIBUTE("not USE") = 0x10+_INTERFACETYPE_BLUETOOTH,
    _INTERFACETYPE_BROADCAST               DEPRECATED_MSG_ATTRIBUTE("not USE") = 8,
};


/**
 * getBatteryState API
 */
typedef NS_OPTIONS(NSUInteger, __BATTERY_VALUE) {
    __BATTERY_VALUE_FULL    = 0,
    __BATTERY_VALUE_HIGH,
    __BATTERY_VALUE_MIDDLE,
    __BATTERY_VALUE_LOW

};





//MARK: - Deprecated #define or NS_OPTIONS

/**
 * @brief not Using Define
 */
#define LOG_SHOW_LEVEL1             (0x1 << 0) // not USE
#define LOG_SHOW_LEVEL2             (0x1 << 1) // not USE
#define LOG_SHOW_LEVEL3             (0x1 << 2) // not USE
#define LOG_SHOW_LEVEL4             (0x1 << 3) // not USE
#define LOG_SHOW_LEVEL5             (0x1 << 4) // not USE
#define LOG_SHOW_LEVEL6             (0x1 << 5) // not USE
#define LOG_SHOW_LEVEL7             (0x1 << 6) // not USE
#define LOG_SHOW_LEVEL8             (0x1 << 7) // not USE
#define LOG_SHOW_FUNCTION_IN        (0x1 << 0) // not USE
#define LOG_SHOW_FUNCTION_OUT       (0x1 << 1) // not USE
#define LOG_SHOW_ERROR              (0x1 << 2) // not USE
#define LOG_SHOW_NORMAL             (0x1 << 3) // not USE
#define LOG_SHOW_INTERFACE          (0x1 << 4) // not USE
#define LOG_SHOW_TX                 (0x1 << 5) // not USE
#define LOG_SHOW_RX                 (0x1 << 6) // not USE
#define LOG_SHOW_THREAD             (0x1 << 7) // not USE
#define LOG_SHOW_HALF               0x0f  // not USE


/**
 * @typedef __SHOW_BLUETOOTH_SETTINGS_OPTIONS
 * @constant for about -(NSArray*)getPairedDevices:(NSError**) errorCode APIs
 */
typedef NS_OPTIONS(NSUInteger, __SHOW_BLUETOOTH_SETTINGS_OPTIONS) {
    _SHOW_BLUETOOTH_SETTINGS_NEVER         = 0,
    _SHOW_BLUETOOTH_SETTINGS_IF_NO_DEVICE DEPRECATED_MSG_ATTRIBUTE("not USE"),
    _SHOW_BLUETOOTH_SETTINGS_ALWAYS
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");

/**
 * Open API Result Code
 */
typedef NS_OPTIONS(NSUInteger, __UPOS_OPEN_RESULT) {
    UPOS_OR_ALREADYOPEN     = 301,
    UPOS_OR_REGBADNAME      = 302,
    UPOS_OR_REGPROGID       = 303,
    UPOS_OR_CREATE          = 304,
    UPOS_OR_BADIF           = 305,
    UPOS_OR_FAILEDOPEN      = 306,
    UPOS_OR_BADVERSION      = 307,
    UPOS_ORS_NOPORT         = 401,
    UPOS_ORS_NOTSUPPORTED   = 402,
    UPOS_ORS_CONFIG         = 403,
    UPOS_ORS_SPECIFIC       = 450
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");

typedef NS_OPTIONS(NSUInteger, __UPOS_STATES) {
    UPOS_S_CLOSED        = 1,
    UPOS_S_IDLE          = 2,
    UPOS_S_BUSY          = 3,
    UPOS_S_ERROR         = 4
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");

typedef NS_OPTIONS(NSUInteger, __UPOS_RESULT_CODE_EXTENDED) {

    // The following applies to ResetStatistics and UpdateStatistics.
    UPOS_ESTATS_ERROR       = 280,
    UPOS_ESTATS_DEPENDENCY  = 282,
    // The following applies to CompareFirmwareVersion and UpdateFirmware.
    UPOS_EFIRMWARE_BAD_FILE = 281

}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");

typedef NS_OPTIONS(NSUInteger, __UPOS_BINARY_CONVERSION) {
    UPOS_BC_NONE         = 0,
    UPOS_BC_NIBBLE       = 1,
    UPOS_BC_DECIMAL      = 2
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


typedef NS_OPTIONS(NSUInteger, __UPOS_CHECK_HEALTH_LEVEL) {
    UPOS_CH_INTERNAL     = 1,
    UPOS_CH_EXTERNAL     = 2,
    UPOS_CH_INTERACTIVE  = 3
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


typedef NS_OPTIONS(NSUInteger, __UPOS_POWER_REPORTING_LEVEL) {
    UPOS_PR_NONE         = 0,
    UPOS_PR_STANDARD     = 1,
    UPOS_PR_ADVANCED     = 2
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


typedef NS_OPTIONS(NSUInteger, __UPOS_POWER_STATUS) {
    UPOS_PN_DISABLED     = 0,
    UPOS_PN_ENABLED      = 1
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


typedef NS_OPTIONS(NSUInteger, __UPOS_POWER_NOTIFY) {
    UPOS_PS_UNKNOWN      = 2000,
    UPOS_PS_ONLINE       = 2001,
    PowerState          = 2002,
    UPOS_PS_OFFLINE      = 2003,
    UPOS_PS_OFF_OFFLINE  = 2004
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


typedef NS_OPTIONS(NSUInteger, __UPOS_COMPARE_FIRMWARE_VERSION) {
    UPOS_CFV_FIRMWARE_OLDER      = 1,
    UPOS_CFV_FIRMWARE_SAME       = 2,
    UPOS_CFV_FIRMWARE_NEWER      = 3,
    UPOS_CFV_FIRMWARE_DIFFERENT  = 4,
    UPOS_CFV_FIRMWARE_UNKNOWN    = 5
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


typedef NS_OPTIONS(NSUInteger, __UPOS_ERROR_LOCUS) {
    UPOS_EL_OUTPUT       = 1,
    UPOS_EL_INPUT        = 2,
    UPOS_EL_INPUT_DATA   = 3
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


typedef NS_OPTIONS(NSUInteger, __UPOS_ERROR_RESPONSE) {
    UPOS_ER_RETRY        = 11,
    UPOS_ER_CLEAR        = 12,
    UPOS_ER_CONTINUEINPUT= 13
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


typedef NS_OPTIONS(NSUInteger, __UPOS_STATUS) {
    UPOS_SUE_POWER_ONLINE                    = 2001,
    UPOS_SUE_POWER_OFF                       = 2002,
    UPOS_SUE_POWER_OFFLINE                   = 2003,
    UPOS_SUE_POWER_OFF_OFFLINE               = 2004,

    UPOS_SUE_UF_PROGRESS                     = 2100,
    UPOS_SUE_UF_COMPLETE                     = 2200,
    UPOS_SUE_UF_COMPLETE_DEV_NOT_RESTORED    = 2205,
    UPOS_SUE_UF_FAILED_DEV_OK                = 2201,
    UPOS_SUE_UF_FAILED_DEV_UNRECOVERABLE     = 2202,
    UPOS_SUE_UF_FAILED_DEV_NEEDS_FIRMWARE    = 2203,
    UPOS_SUE_UF_FAILED_DEV_UNKNOWN           = 2204
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");


#endif /* UPOSDefines_h */
