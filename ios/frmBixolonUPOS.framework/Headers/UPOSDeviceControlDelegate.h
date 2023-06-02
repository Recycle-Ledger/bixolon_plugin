//
// ----------------------------------------
//
// File : UPOSDeviceControlDelegate.h
// Date : 12/07/2019
//
// ========================================
        

#ifndef UPOSDeviceControlDelegate_h
#define UPOSDeviceControlDelegate_h


@protocol UPOSDeviceControlDelegate <NSObject>
@optional
-(void)DataEvent:(NSNumber*) status;
-(void)DataEvent:(NSNumber*) status data:(NSData*) data;

/**
 * @brief AsyncMode On
 * @param outputID not use value is only 0
 */
-(void)OutputCompleteEvent:(NSNumber*)outputID;

-(void)DisconnectedEvent;

-(void)StatusUpdateEvent:(NSNumber*) status;

-(void)DirectIOEvent:(NSNumber*) eventNumber
                Data:(NSNumber*) data
                 Obj:(id) obj
__deprecated_msg("It is unnecessary to call this delegate");

-(void)ErrorEvent:(NSNumber*) errorCode
errorCodeExtended:(NSNumber*) errorCodeExtended
       errorLocus:(NSNumber*) errorLocus
    errorResponse:(NSNumber*) errorResponse
__deprecated_msg("It is unnecessary to call this delegate");




@end



#endif /* UPOSDeviceControlDelegate_h */
