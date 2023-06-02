//
// ----------------------------------------
//
// File : UPOSMSRController.h
// Date : 12/07/2019
//
// ========================================
        
#import "UPOSDeviceController.h"
#import "UPOSDefinesCashDrawer.h"

NS_ASSUME_NONNULL_BEGIN

@interface UPOSMSRController : UPOSDeviceController

@property (readonly)    NSString*   Track1Data;
@property (readonly)    NSString*   Track2Data;
@property (readonly)    NSString*   Track3Data;


/**
* @brief for multi Connection
* @param connectionPrinterID to connect printer ID
*/
-(NSInteger)open:(NSString*)logicalDeviceName connectionPrinterID:(NSNumber*)connectionPrinterID;

@end


@interface UPOSMSRController(BXLDeprecated)

@property (readonly)    NSData*     Track1EncryptedData
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   Track1EncryptedDataLength
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSData*     Track2EncryptedData
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   Track2EncryptedDataLength
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSData*     Track3EncryptedData
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   Track3EncryptedDataLength
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSString*   Track4Data
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              AccountNumber
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              AdditionalSecurityInformation
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              CardAuthenticationData
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger              CardAuthenticationDataLength
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              CardPropertyList
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              CardType
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              CardTypeList
__deprecated_msg("It is unnecessary to call this property");

@property (readwrite)             NSInteger              DataEncryptionAlgorithm
__deprecated_msg("It is unnecessary to call this property");

@property (readwrite)             BOOL                   DecodeData
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              BOOL                   DeviceAuthenticated
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger              DeviceAuthenticationProtocol
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger              EncodingMaxLength
__deprecated_msg("It is unnecessary to call this property");

@property (readwrite)             NSInteger              ErrorReportingType
__deprecated_msg("It is unnecessary to call this property");



@property (strong, readonly)      NSString*              FirstName
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              MiddleInitial
__deprecated_msg("It is unnecessary to call this property");

@property (readwrite)             BOOL                   ParseDecodeData
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              ServiceCode
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              Suffix
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              Surname
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString*              Title
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSData*              Track4EncryptedData
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)              NSInteger              Track4EncryptedDataLength
__deprecated_msg("It is unnecessary to call this property");

@property (readwrite)             NSInteger              TracksToRead
__deprecated_msg("It is unnecessary to call this property");

@property (readwrite)             NSInteger              TracksToWrite
__deprecated_msg("It is unnecessary to call this property");

@property (readwrite)             BOOL                   TransmitSentinels
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readwrite)     NSString*              WriteCardType
__deprecated_msg("It is unnecessary to call this property");

@end



NS_ASSUME_NONNULL_END
