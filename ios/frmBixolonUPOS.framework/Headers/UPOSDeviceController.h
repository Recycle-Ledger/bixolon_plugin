//
// ----------------------------------------
//
// File : UPOSDeviceController.h
// Date : 11/07/2019
//
// ========================================
        

#import "UPOSDefines.h"
#import "UPOSDefinesPrinter.h"
#import "UPOSDeviceControlDelegate.h"
#import "UPOSDevices.h"

@interface UPOSDeviceController : NSObject {
    // ADD Device List
    UPOSDevices *_listOfDevices     __deprecated_msg("not use");
    NSInteger   _controlLevel       __deprecated_msg("not use");
    NSInteger   _ResultCodeExtended __deprecated_msg("not use");
    NSInteger   _State              __deprecated_msg("not use");
    NSInteger   _OpenResult         __deprecated_msg("is Instead 'isOpen;'");
    NSInteger   _ResultCode         __deprecated_msg("not use");
};

@property (nonatomic) id<UPOSDeviceControlDelegate> delegate;
@property (atomic, readonly) UPOSDevice* targetDevice;
@property (readonly) float DeviceControlVersion;
@property (readonly) NSString* DeviceControlDescription;
@property (readwrite) BOOL DeviceEnabled;    // Device Enabled is return YES, Device Disabled is return NO
@property (readonly) NSNumber* objID;        // for multiconnection ID


+(void) setEnableLog:(BOOL)printLog saveFile:(BOOL)saveFile saveToHex:(BOOL)saveToHex;

+(NSString* __nonnull) getVersionDescription;


/**
 * @brief Log Enable/Disable
 * @discussion Provides Debug Log function of SDK.
 * @param level log level setting
 LOG_SHOW_NEVER is disable
 LOG_SHOW_ALL is enable
 *
 */
-(void)setLogLevel:(Byte)level;


- (NSInteger) directIO: (NSInteger)command data:(NSData*)data;

- (NSInteger) directIO : (NSInteger)command
                 data : (void*)data
               object : (void*)object;


-(NSMutableArray*) getSupportDeviceStrings;


//MARK: - Delete API
/**
 * @brief setting UPOSDeviceControlDelegate
 * @param obj delegate Object
 */
// Delete, use 'property delegate value' instead
//-(void) setDelegate:(id<UPOSDeviceControlDelegate>)obj;
@end

/*------------------------------------------------------------------------------------*/
//MARK: - About printer search API
@interface UPOSDeviceController(BXLLookup)
/**
 * @brief Wifi interface printer search API
 * @discussion To use this function, you need to register the following functions:
 *
 * __NOTIFICATION_NAME_WIFI_WILL_LOOKUP_
 * __NOTIFICATION_NAME_WIFI_FOUND_PRINTER_
 * __NOTIFICATION_NAME_WIFI_LOOKUP_COMPLETE_
 */
-(void)refreshWifiLookup;

/**
 * @brief Bluetooth interface printer search API
 * @discussion To use this function, you need to register the following functions:
 *
 * __NOTIFICATION_NAME_BT_WILL_LOOKUP_
 * __NOTIFICATION_NAME_BT_FOUND_PRINTER_
 * __NOTIFICATION_NAME_BT_LOOKUP_COMPLETE_
 */
-(void)refreshBTLookup;

/**
 * @brief Ethernet interface printer search API
 * @discussion To use this function, you need to register the following functions:
 *
 * __NOTIFICATION_NAME_ETHERNET_WILL_LOOKUP_
 * __NOTIFICATION_NAME_ETHERNET_FOUND_PRINTER_
 * __NOTIFICATION_NAME_ETHERNET_LOOKUP_COMPLETE_
 */
-(void)refreshEthernetLookup;


/**
 * @brief BLE(Bluetooth Low Energy) interface printer search API
 * @discussion To use this function, you need to register the following functions:
 
 * __NOTIFICATION_NAME_BLE_WILL_LOOKUP_
 * __NOTIFICATION_NAME_BLE_FOUND_PRINTER_
 * __NOTIFICATION_NAME_BLE_LOOKUP_COMPLETE_
 */
-(void)refreshBLELookup;
@end
/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/
//MARK: - Device Manager
@interface UPOSDeviceController(BXLDeviceManager)
-(UPOSDevices*)getRegisteredDevice;
@end
/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/
//MARK: - About Connect
@interface UPOSDeviceController(BXLConnection)

// 2.0.0 or later added property
// opened is return YES, closed is return NO
@property(readonly)     BOOL Opened;

// claimed is return YES, releaseDeviced is return NO
@property(readonly)     BOOL Claimed;



-(NSInteger)open:(NSString*)logicalDeviceName;
-(NSInteger)open:(NSString*)logicalDeviceName address:(NSString*)address ;
-(NSInteger)open:(NSString*)logicalDeviceName serialNumber:(NSString*)serialNumber;
-(NSInteger)open:(NSString*)logicalDeviceName connectionPrinterID:(NSNumber*)connectionPrinterID;

-(NSInteger)claim:(NSInteger)timeout;

-(NSInteger)releaseDevice;
-(NSInteger)close;

// open -> clam -> setDeviceEnalbe:YES
-(NSInteger)connect:(NSString*)logicalDeviceName;


@end
/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/
//MARK: - deprecated API Extension
@interface UPOSDeviceController(BXLDeprecated)

-(NSString*) getAvailableNewModelString:(NSString*)newModel
__deprecated_msg("It is unnecessary to call this API");

-(NSMutableArray*) getRegisteredPrinterStrings
__deprecated_msg("It is unnecessary to call this API");

/**
 * @brief not support
 * @returns return 106(UPOS_E_ILLEGAL) only
 */
-(NSInteger)compareFirmwareVersion:(NSString*)firmwareFileName
                            result:(NSInteger)result
__deprecated_msg("It is unnecessary to call this API");


/**
 * @brief not support
 * @returns return 106(UPOS_E_ILLEGAL) only
 */
-(NSInteger) resetStatistics : (NSString*)statisticsBuffer
__deprecated_msg("It is unnecessary to call this API");


/**
 * @brief not support
 * @returns return 106(UPOS_E_ILLEGAL) only
 */
-(NSInteger) retrieveStatistics : (NSString*)statisticsBuffer
__deprecated_msg("It is unnecessary to call this API");


/**
 * @brief not support
 * @returns return 106(UPOS_E_ILLEGAL) only
 */
-(NSInteger) updateFirmware : (NSString*)firmwareFileName
__deprecated_msg("It is unnecessary to call this API");


/**
 * @brief not support
 * @returns return 106(UPOS_E_ILLEGAL) only
 */
-(NSInteger) updateStatistics : (NSString*)statisticsBuffer
__deprecated_msg("It is unnecessary to call this API");

/**
 * @brief not support
 */
-(void) setDeviceMode:(BOOL)isHub
__deprecated_msg("It is unnecessary to call this API");

/**
 * @brief not support
 */
-(NSInteger) clearInput
__deprecated_msg("It is unnecessary to call this API");

/**
 * @brief not support
 */
-(NSInteger) clearInputProperties
__deprecated_msg("It is unnecessary to call this API");

/**
 * @brief not support
 */
-(NSInteger) clearOutput
__deprecated_msg("It is unnecessary to call this API");

/**
 * @brief not support
 */
-(NSInteger) checkHealth : (NSInteger) level
__deprecated_msg("It is unnecessary to call this API");

@property                         BOOL        AutoDisable
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              BOOL        CapCompareFirmwareVersion
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              BOOL        CapPowerReporting
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              BOOL        CapStatisticsReporting
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              BOOL        CapUpdateFirmware
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              BOOL        CapUpdateStatistics
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*   CheckHealthText
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger   DataCount
__deprecated_msg("It is unnecessary to call this property");

@property                         BOOL        DataEventEnabled
__deprecated_msg("It is unnecessary to call this property");

@property                         BOOL        FreezeEvents
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger   OpenResult
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger   ResultCode
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger   ResultCodeExtended
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger   OutputID
__deprecated_msg("It is unnecessary to call this property");

@property                         NSInteger   PowerNotify
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger   PowerState
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger   State
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*   DeviceServiceDescription
__deprecated_msg("It is unnecessary to call this property");

@property                         float       DeviceServiceVersion
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*   PhysicalDeviceDescription
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*   PhysicalDeviceName
__deprecated_msg("It is unnecessary to call this property");

@property (assign)    unsigned short            portSrc
__deprecated_msg("It is unnecessary to call this property");

@property (assign)    unsigned short            portDest
__deprecated_msg("It is unnecessary to call this property");

@end
/*------------------------------------------------------------------------------------*/



