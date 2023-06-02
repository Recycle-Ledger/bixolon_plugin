//
// ----------------------------------------
//
// File : UPOSCDController.h
// Date : 12/07/2019
//
// ========================================


#import "UPOSPrinterController.h"
#import "UPOSDefinesCashDrawer.h"

NS_ASSUME_NONNULL_BEGIN

@interface UPOSCDController : UPOSDeviceController

@property (readonly)    BOOL    DrawerOpened;
@property (readonly)    BOOL    IsHighSignal;

-(NSInteger) open:(NSString*)logicalDeviceName connectionPrinterID:(NSNumber*)connectionPrinterID;
-(NSInteger) OpenDrawer;


@end

@interface UPOSCDController(BXLDeprecated)
-(NSInteger) waitForDrawerClose:(NSInteger)beepTimeout
                  beepFrequency:(NSInteger)beepFrequency
                   beepDuration:(NSInteger)beepDuration
                      beepDelay:(NSInteger)beepDelay
__deprecated_msg("It is unnecessary to call this API");
@end

NS_ASSUME_NONNULL_END
