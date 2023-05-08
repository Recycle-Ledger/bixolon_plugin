//
// ----------------------------------------
//
// File : UPOSDevices.h
// Date : 12/07/2019
//
// ========================================


NS_ASSUME_NONNULL_BEGIN

@protocol UPOSDevicesDelegate <NSObject>
@required
@optional
-(void)didFinish_ShowBluetoothAccessory:(NSError*) error
__deprecated_msg("It is unnecessary to call this Delegate");
@end


@interface UPOSDevice : NSObject<NSCoding, NSCopying>
@property NSString        *modelName;
@property NSString        *ldn;
@property NSNumber        *interfaceType;
@property NSString        *address;
@property NSString        *serialNumber;
@property NSString        *port;
@property NSString        *bluetoothDeviceName;

- (instancetype)initWithModelName:(NSString*)modelName
                    interfaceType:(NSNumber*)interfaceType
                          address:(NSString*)address
                             port:(NSString*)port;

- (instancetype)initWithModelName:(NSString*)modelName
                     serialNumber:(NSString*)serialNumber;

- (instancetype)initWithDevice:(UPOSDevice*)device;

//MARK: - @protected Method
- (instancetype)initWithCoder:(NSCoder *)coder;
//MARK: - @protected Method
- (void)encodeWithCoder:(NSCoder *)coder;

@end

@interface UPOSDevices : NSObject {
    @protected NSMutableArray* bxlDevices;
}
@property id<UPOSDevicesDelegate> delegate;



/**
* @brief Register Printer info return
*/
-(NSArray*)getList;

-(NSArray*)getList:(id)deviceType;

/**
 * @brief Registers a device
 * @param device device type is [UPOSPrinter/UPOSMSR/UPOSSCR/UPOSCD]
 * @discussion Registered device information is permanently stored.
 * @returns Only return NO, Not Used
 */
-(BOOL) addDevice:(id)device;

/**
 * @brief Removes the registered device from the list
 * @param device device type is [UPOSPrinter/UPOSMSR/UPOSSCR/UPOSCD]
 * @returns Remove Success is return YES, Fail is NO return
 */
-(BOOL) removeDevice:(id)device;


/**
 * @brief Removes all the registered device from the list
 */
-(void) removeAllDevices;
    
/**
 * @brief not Use
 * @returns Only return YES, Not Used
 */
-(BOOL) save
__deprecated_msg("It is unnecessary to call this API");


/**
 * @brief not Use
 * @returns Only return YES, Not Used
 */
-(NSString*)getDeviceIdentity
__deprecated_msg("It is unnecessary to call this API");

/**
 * @brief Get paired Device List
 * @returns paired Device List
 */
-(NSArray*)getPairedDevices
__deprecated_msg("It is unnecessary to call this API");

/**
 * @brief Get paired Device List
 * @param errorCode is not use
 * @param action if value is
 _SHOW_BLUETOOTH_SETTINGS_NEVER get paired Device List return
 _SHOW_BLUETOOTH_SETTINGS_IF_NO_DEVICE, _SHOW_BLUETOOTH_SETTINGS_ALWAYS show bluetooth paired list return nil
 * @returns paired Device List or nil return
 */
-(NSArray*)getPairedDevices:(NSError**) errorCode
                     action:(NSInteger) action
__deprecated_msg("It is unnecessary to call this API");
@end



@interface UPOSPrinter:UPOSDevice   @end
@interface UPOSPrinters:UPOSDevices @end


@interface UPOSMSR:UPOSDevice
@property NSString  *selectedPrinterName
__deprecated_msg("It is unnecessary to call this API");
@end
@interface UPOSMSRs:UPOSDevices @end


@interface UPOSSCR:UPOSDevice   @end
@interface UPOSSCRs:UPOSDevices @end


@interface UPOSCashDrawer : UPOSDevice

/**
 * @brief pinNumber value is 2 or 5
 */
@property NSNumber        *pinNumber;

/**
 * @brief pinLevel value is 0 or 1
 */
@property NSNumber        *pinLevel;

/**
 * @brief pulseOnTime default value is 50
 */
@property NSNumber        *pulseOnTime;

/**
 * @brief pulseOffTime default value is 200
 */
@property NSNumber        *pulseOffTime;

// Not Use
// default value is @""
@property NSString *selectedPrinterName
__deprecated_msg("It is unnecessary to call this API");
@end

@interface UPOSCashDrawers:UPOSDevices  @end



NS_ASSUME_NONNULL_END
