//
// ----------------------------------------
//
// File : UPOSPrinterController.h
// Date : 11/07/2019
//
// ========================================
        

#import "UPOSDeviceController.h"
#import <UIKit/UIKit.h> // for swift (UIImage*)

NS_ASSUME_NONNULL_BEGIN


@interface UPOSPrinterController : UPOSDeviceController

@property (readonly)    BOOL                CapRecPapercut;
@property (readonly)    NSInteger           RecLineWidth;
@property (nonatomic)   NSInteger           RecLineChars;
@property (readonly)    NSString* _Nullable RecLineCharsList;

/**
 * @brief output complete delegate
 */
@property (nonatomic)   BOOL        AsyncMode;


// Text Encoding Setting
-(NSInteger)setCharacterSet:(NSInteger)characterSet;
    
// Text Encoding Setting
-(NSInteger)setTextEncoding:(NSStringEncoding)textEncoding;

// print text
-(NSInteger)printNormal:(NSInteger)station data:(NSString*)data;

/**
 * @brief paper cutting
 * @param percentage 100 is full Cut, 0~99 is patical Cut
 */
-(NSInteger)cutPaper:(NSInteger)percentage;

/**
 * @brief paper cutting
 * @param percentage 100 is full Cut, 0~99 is patical Cut
 * @param feedCut YES: automatically feeds to the cutting postion and then cuts paper. No: no feeds and then cuts paper.
 */
- (NSInteger)cutPaper:(NSInteger)percentage feedCut:(BOOL)feedCut;

/**
* @brief returns a current printer status
*/
-(NSInteger)getPrinterStatus;
    
/**
 * @brief Print Barcode
 * @param station PTR_S_RECEIPT only
 * @param data barcode data
 * @param symbology barcode type
 * @param height barcode height
 * @param barWidth barcode width(1,2,3~...)
 * @param alignment barcode alignment
 * @param textPosition barcode HRI
 */
-(NSInteger) printBarcode:(NSInteger)station data:(NSString*)data
                symbology:(NSInteger)symbology
                   height:(NSInteger)height
                 barWidth:(NSInteger)barWidth
                alignment:(NSInteger)alignment
              textPostion:(NSInteger)textPosition;

/**
* @brief Direct IO (byte array value)
* @param command Not Using
* @param data Write Data to Printer
*/
- (NSInteger) directIO: (NSInteger)command data:(NSData*)data;
    
/**
 * @brief Direct IO (byte array value)
 * @param command Not Using
 * @param data Write Data to Printer
 * @param object Not Using, param is nil only
 */
-(NSInteger) directIO : (NSInteger)command
                 data : (void*)data
               object : (void* _Nullable)object;

/**
 * @brief formfeed
 * @param type Not Using
*/
-(NSInteger)markFeed:(NSInteger)type;


/**
 * @brief Direct IO ( NSData value )
 * @param station PTR_S_RECEIPT only
 * @param data Write Data to Printer
 */
-(NSInteger) printRawData : (NSInteger) station
                     data : (NSData*) data;


/**
 * @brief print Image
 * @param station PTR_S_RECEIPT only
 * @param fileName file full path info
 */
-(NSInteger) printBitmap : (NSInteger) station
                fileName : (NSString*) fileName
                   width : (NSInteger) width
               alignment : (NSInteger) alignment;

/**
 * @brief print Image
 * @param station PTR_S_RECEIPT only
 * @param image UIImage Data
 * @param width Print Width
 * @param alignment Print alignment
 */
-(NSInteger) printBitmap : (NSInteger) station
                   image : (UIImage*) image
                   width : (NSInteger) width
               alignment : (NSInteger) alignment;

/**
 * @brief print Image
 * @param station PTR_S_RECEIPT only
 * @param fileName file full path info
 * @param width Print Width
 * @param alignment Print alignment
 * @param brightness print brightness
 */
-(NSInteger) printBitmap : (NSInteger) station
                fileName : (NSString*) fileName
                   width : (NSInteger) width
               alignment : (NSInteger) alignment
              brightness : (NSInteger) brightness;


/**
* @brief print Image
* @param station PTR_S_RECEIPT only
* @param fileName file full path info
* @param width Print Width
* @param alignment Print alignment
* @param brightness print brightness
* @param compressType  CompressType : None, RLE, LZMA
* @param dithering  image dithering
*/
-(NSInteger) printBitmap : (NSInteger)station
                fileName : (NSString*)fileName
                   width : (NSInteger)width
               alignment : (NSInteger)alignment
              brightness : (NSInteger)brightness
            compressType : (NSInteger)compressType
                dithering: (BOOL)dithering;

/**
 * @brief print Image
 * @param station PTR_S_RECEIPT only
 * @param image UIImage Data
 * @param width Print Width
 * @param alignment Print alignment
 * @param brightness Print brightness
 */
-(NSInteger) printBitmap : (NSInteger)station
                   image : (UIImage*)image
                   width : (NSInteger)width
               alignment : (NSInteger)alignment
              brightness : (NSInteger)brightness;

/**
* @brief print Image
* @param station PTR_S_RECEIPT only
* @param image UIImage Data
* @param width Print Width
* @param alignment Print alignment
* @param brightness Print brightness
* @param compressType  CompressType : None, RLE, LZMA
* @param dithering  image dithering
*/
-(NSInteger) printBitmap: (NSInteger)station
                   image: (UIImage*)image
                   width: (NSInteger)width
               alignment: (NSInteger)alignment
              brightness: (NSInteger)brightness
            compressType: (NSInteger)compressType
               dithering: (BOOL)dithering;
/**
 * @brief print PDF
 * @param station PTR_S_RECEIPT only
 * @param fileName pdf file full path
 * @param page setting to pdf page number
 */
-(NSInteger) printPDF: (NSInteger)station
             fileName: (NSString*)fileName
                 page: (NSInteger)page;

/**
 * @brief print PDF
 * @param station PTR_S_RECEIPT only
 * @param fileName pdf file full path
 * @param width print Width
 * @param alignment print alignment
 * @param page setting to pdf page number
 * @param brightness print brightness
 */
-(NSInteger) printPDF: (NSInteger)station
             fileName: (NSString*)fileName
                width: (NSInteger)width
            alignment: (NSInteger)alignment
                 page: (NSInteger)page
           brightness: (NSInteger)brightness;

/**
* @brief print PDF
* @param station PTR_S_RECEIPT only
* @param fileName pdf file full path
* @param width print Width
* @param alignment print alignment
* @param page setting to pdf page number
* @param brightness print brightness
* @param compressType  CompressType : None, RLE, LZMA
* @param dithering  image dithering
*/
-(NSInteger) printPDF: (NSInteger)station
             fileName: (NSString*)fileName
                width: (NSInteger)width
            alignment: (NSInteger)alignment
                 page: (NSInteger)page
           brightness: (NSInteger)brightness
         compressType: (NSInteger)compressType
            dithering: (BOOL)dithering;

/**
 * @brief transaction mode
 * @param station PTR_S_RECEIPT only
 * @param control transaction mode on/off param
 */
-(NSInteger)transactionPrint:(NSInteger)station
                     control:(NSInteger)control;

/**
 * @brief getBatteryState
 */
-(NSInteger) getBatteryState;

/**
 * @brief alarm rings n times
 * @param count n of n times
 */
-(NSInteger) setAlarm:(NSInteger)count
NS_SWIFT_NAME(setAlarm(count:));


@end

/*------------------------------------------------------------------------------------*/
//MARK: - about Page mode
@interface UPOSPrinterController(BXLPagemode)

/**
 * @brief Setting Pagemode direction
 * @param direction PAGE_MODE_DIRECTION enum using
 */
- (NSInteger)setPageModeDirection:(PAGE_MODE_DIRECTION)direction;

/**
 * @brief Page Mode Setting
 * @param startingX x pos
 * @param startingY y pos
 * @param width page width
 * @param height page height
 */
- (NSInteger)setPageArea:(NSInteger)startingX
               startingY:(NSInteger)startingY
                   width:(NSInteger)width
                  height:(NSInteger)height;

/**
 * @brief Setting left position
 * @param positionX positionX
 */
- (NSInteger)setLeftPosition:(NSInteger)positionX;

/**
 * @brief Setting vertical position
 * @param positionY positionY
 */
- (NSInteger)setVerticalPosition:(NSInteger)positionY;

/**
 * @brief page mode printing
 */
- (NSInteger)printDataInPageMode;


/**
 * @brief page mode box draw
 * @param startPosX (0~832)
 * @param startPosY (0~65535)
 * @param endPosX (0~832)
 * @param endPosY (0~65535)
 * @param thickness (0~16)
 */
- (NSInteger)drawBoxInPageMode:(NSUInteger)startPosX
                     startPosY:(NSUInteger)startPosY
                       endPosX:(NSUInteger)endPosX
                       endPosY:(NSUInteger)endPosY
                     thickness:(NSUInteger)thickness;

/**
* @brief page mode box line
* @param startPosX (0~832)
* @param startPosY (0~65535)
* @param endPosX (0~832)
* @param endPosY (0~65535)
* @param thickness (0~16)
*/
- (NSInteger)drawLineInPageMode:(NSUInteger)startPosX
                      startPosY:(NSUInteger)startPosY
                        endPosX:(NSUInteger)endPosX
                        endPosY:(NSUInteger)endPosY
                      thickness:(NSUInteger)thickness;

@end
/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/
//MARK: - about BCD3000 API for SRP-Q300 Only
@interface UPOSPrinterController(BXLBCD3000)

/**
 * @brief display text to BCD3000
 * @param string display text
 */
-(NSInteger) displayString:(NSString*)string;

/**
 * @brief display text to BCD3000
 * @param line setting display text Line, value 1~2
 * @param data display data
 */
-(NSInteger) displayStringAtLine:(NSInteger)line
                            data:(NSString*)data;



/**
 * @brief display clear
 */
-(NSInteger) clearScreen;

/**
 * @brief bcd codepage setting
 * @param characterSet codepage value setting, 0~51
 */
-(NSInteger) setDisplayCharacterSet:(NSInteger)characterSet;

/**
 * @brief bcd International Character setting
 * @param internationalCharset internationalCharacter value setting, 0~15
 */
-(NSInteger) setInternationalCharacterset:(NSInteger)internationalCharset;

/**
 * @brief bcd image store
 * @param image save image Data
 * @param width image width
 * @param imageNumber save image address, 1~5
 */
-(NSInteger) storeImage:(UIImage*)image
                  width:(NSInteger)width
            imageNumber:(NSInteger)imageNumber;

/**
 * @brief bcd image store
 * @param filename save image file path
 * @param width image width
 * @param imageNumber save image address, 1~5
 */
-(NSInteger) storeImageFile:(NSString*)filename
                      width:(NSInteger)width
                imageNumber:(NSInteger)imageNumber;


/**
 * @brief display image to BCD3000
 * @param imageNumber imageNumber, 1~5
 * @param xPos xPos
 * @param yPos yPos
 */
-(NSInteger) displayImage:(NSInteger)imageNumber
                     xPos:(NSInteger)xPos
                     yPos:(NSInteger)yPos;

/**
 * @brief clear Image
 * @param isAll total clear flag
 * @param imageNumber clear image index
 */
-(NSInteger) clearImage:(BOOL)isAll
            imageNumber:(NSInteger)imageNumber;

@end

/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/
//MARK: - deprecated API and property Extension
@interface UPOSPrinterController(BXLDeprecated)


-(NSInteger)printImmediate:(NSInteger)station
                      data:(NSString*)data
__deprecated_msg("It is unnecessary to call this API");

-(NSInteger) validateData : (NSInteger) station
                     data : (NSString*) data
__deprecated_msg("It is unnecessary to call this API");

-(NSInteger) rotatePrint : (NSInteger)station
                rotation : (NSInteger)rotation
__deprecated_msg("It is unnecessary to call this API");

-(NSInteger) printTwoNormal : (NSInteger)station
                      data1 : (NSString*)data1
                      data2 : (NSString*)data2
__deprecated_msg("It is unnecessary to call this API");

-(NSInteger) printNormal : (NSInteger)station
                byteData : (void*)byteData
              byteLength : (int)byteLength
__deprecated_msg("It is unnecessary to call this API");

-(NSInteger) setLogo : (NSInteger) location
                data : (NSString*) data
__deprecated_msg("It is unnecessary to call this API");

-(NSInteger) setBitmap : (NSInteger) bitmapNumber
               station : (NSInteger) station
              fileName : (NSString*) fileName
                 width : (NSInteger) width
             alignment : (NSInteger) alignment
__deprecated_msg("It is unnecessary to call this API");


/**
 * @brief Print Barcode
 * @param station PTR_S_RECEIPT only
 * @param data barcode data
 * @param symbology barcode type
 * @param height barcode height
 * @param width barcode width
 * @param alignment barcode alignment
 * @param textPosition barcode HRI
 */
-(NSInteger) printBarcode:(NSInteger)station
                     data:(NSString*)data
                symbology:(NSInteger)symbology
                   height:(NSInteger)height
                    width:(NSInteger)width
                alignment:(NSInteger)alignment
              textPostion:(NSInteger)textPosition
__deprecated_msg("ㅣIt is unnecessary to call this API");

-(NSInteger) printBitmap : (NSInteger) station
                   image : (UIImage*) image
                   width : (NSInteger) width
               alignment : (NSInteger) alignment
              brightness : (NSInteger) brightness
         imageCorrection : (NSInteger) imageCorrection
__deprecated_msg("imageCorrection param is Not Use, It is unnecessary to call this API");

-(NSInteger) printPDF:(NSInteger)station
             fileName:(NSString*)fileName
                width:(NSInteger)width
            alignment:(NSInteger)alignment
                 page:(NSInteger)page
           brightness:(NSInteger)brightness
      imageCorrection:(NSInteger)imageCorrection
__deprecated_msg("imageCorrection param is Not Use, It is unnecessary to call this API");

-(BOOL) _private_GetPrinterID
__deprecated_msg("It is unnecessary to call this API");

-(BOOL) _private_SetLabelConfig:(Byte)data
__deprecated_msg("It is unnecessary to call this API");

-(BOOL) _private_SetFontConfig:(Byte)data
__deprecated_msg("It is unnecessary to call this API");

-(BOOL) _private_InitPrinter
__deprecated_msg("It is unnecessary to call this API");

// width value area is 0~7
// height value area is 0~7
-(BOOL) _private_SetFontSize:(Byte)width
                      height:(Byte)height
__deprecated_msg("It is unnecessary to call this API");

@property (readonly)    NSInteger   CapCharacterSet
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapConcurrentJrnRec
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapConcurrentJrnSlp
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapConcurrentPageMode
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapConcurrentRecSlp
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapMapCharacterSet
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapTransaction
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapJrnPresent
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapJrn2Color
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapJrnBold
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapJrnDhigh
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapJrnDwide
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapJrnDwideDhigh
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapJrnEmptySensor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapJrnItalic
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapJrnNearEndSensor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapJrnUnderline
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   CapJrnCartridgeSensor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   CapJrnColor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecPresent
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecBarCode
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecBitmap
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecBold
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecDhigh
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecDwide
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecDwideDhigh
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecEmptySensor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecItalic
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecLeft90
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecNearEndSensor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecRight90
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecRotate180
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecStamp
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecUnderline
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   CapRecCartridgeSensor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   CapRecColor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   CapRecMarkFeed
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRecPageMode
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   CapRecRuledLine
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpPresent
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpFullslip
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlp2Color
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpBarCode
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpBitmap
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpBold
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpDhigh
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpDwide
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpDwideDhigh
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpEmptySensor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpItalic
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpLeft90
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpNearEndSensor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpRight90
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpUnderline
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpBothSidesPrint
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   CapSlpCartridgeSensor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   CapSlpColor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapSlpPageMode
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   CapSlpRuledLine
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   CartridgeNotify
__deprecated_msg("It is unnecessary to call this property");

//@property (nonatomic)   NSInteger   CharacterSet
//__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   ErrorLevel
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   ErrorStation
__deprecated_msg("It is unnecessary to call this property");

@property (nonatomic)   BOOL        MapCharacterSet
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   MapMode
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   PageModeDescriptor
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   PageModeHorizontalPosition
__deprecated_msg("It is unnecessary to call this property");

@property (strong)      NSString*   PageModePrintArea
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   PageModePrintDirection
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   PageModeStation
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   PageModeVerticalPosition
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   RotateSpecial
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   JrnLineChars
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   JrnLineHeight
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   JrnLineSpacing
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   JrnLineWidth
__deprecated_msg("It is unnecessary to call this property");

@property               BOOL        JrnLetterQuality
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        JrnEmpty
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        JrnNearEnd
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   JrnCartridgeState
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   JrnCurrentCartidge
__deprecated_msg("It is unnecessary to call this property");

@property               BOOL        RecLetterQuality
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   RecSidewaysMaxLines
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   RecSidewaysMaxChars
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   RecLinesToPaperCut
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   RecCartridgeState
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   RecCurrentCartridge
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   SlpLineChars
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   SlpLineHeight
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   SlpLineSpacing
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   SlpLineWidth
__deprecated_msg("It is unnecessary to call this property");

@property               BOOL        SlpLetterQuality
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        SlpEmpty
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        SlpNearEnd
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   SlpSidewaysMaxLines
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   SlpSidewaysMaxChars
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   SlpLinesToPaperCut
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    NSInteger   SlpCartridgeState
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   SlpCurrentCartridge
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapCoverSensor
__deprecated_msg("It is unnecessary to call this property");

@property (nonatomic)   BOOL        FlagWhenIdle
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        CapRec2Color
__deprecated_msg("It is unnecessary to call this property");

@property               BOOL        CoverOpen
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   RecLineSpacing
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        RecEmpty
__deprecated_msg("It is unnecessary to call this property");

@property (readonly)    BOOL        RecNearEnd
__deprecated_msg("It is unnecessary to call this property");

@property               NSInteger   RecLineHeight
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString* CharacterSetList
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString* ErrorString
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString* FontTypefaceList
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString* PageModeArea
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString* JrnLineCharsList
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString* RecBarCodeRotationList
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString* RecBitmapRotationList
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString* SlpLineCharsList
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString* SlpBarCodeRotationList
__deprecated_msg("It is unnecessary to call this property");

@property (strong, readonly)      NSString* SlpBitmapRotationList
__deprecated_msg("It is unnecessary to call this property");




@end
/*------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------*/
//MARK: - delete API Extension
//-(NSInteger) getVMSM;
//-(NSInteger) getVMSM:(NSInteger)index;
//-(NSInteger) setVMSMStart;
//-(NSInteger) setVMSM:(int)pinNum
//             pinInfo:(NSData*)pinInfo;
//-(NSInteger) setVMSMEnd;
//
//-(NSInteger) getNVImageList;
//-(NSInteger) nvPrint:(NSInteger)address;
//-(NSInteger) nvDownload:(NSInteger)address
//                  image:(UIImage *)image;
//-(NSInteger) nvRemove:(NSInteger)address;
//-(NSInteger) nvRemoveAll;
/*------------------------------------------------------------------------------------*/

NS_ASSUME_NONNULL_END
