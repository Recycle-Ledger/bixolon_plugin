        
#import "UPOSDeviceController.h"

@interface UPOSSCRController : UPOSDeviceController

-(NSInteger)open:(NSString*_Nullable)logicalDeviceName connectionPrinterID:(NSNumber*_Nullable)connectionPrinterID;

-(void)setSCSlot:(NSInteger)slot;
-(void)setIsoEmvMode:(NSInteger)isoEmvMode;
-(void)beginInsertion:(NSInteger)timeout;
-(void)endInsertion;
-(void)beginRemoval:(NSInteger)timeout;
-(void)endRemoval;
-(void)readData:(NSInteger)action data:(NSData*_Nullable*_Nullable)data;

@end

