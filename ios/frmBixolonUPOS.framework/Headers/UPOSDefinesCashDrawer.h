//
// ----------------------------------------
//
// File : UPOSDefinesCashDrawer.h
// Date : 20/09/2019
//
// ========================================
        

#ifndef UPOSDefinesCashDrawer_h
#define UPOSDefinesCashDrawer_h

#include "UPOSDefines.h"

typedef NS_OPTIONS(NSUInteger, __UPOS_CASHDRAWER_STATES) {
    
    CASH_SUE_DRAWERCLOSED = 0,
    CASH_SUE_DRAWEROPEN   = 1
}__deprecated_msg("It is unnecessary to call this NS_OPTIONS");

#endif /* UPOSDefinesCashDrawer_h */
