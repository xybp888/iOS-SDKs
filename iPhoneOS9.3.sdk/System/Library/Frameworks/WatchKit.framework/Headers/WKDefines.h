//
//  WKDefines.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define WKI_EXTERN  extern "C" __attribute__((visibility ("default")))
#else
#define WKI_EXTERN  extern __attribute__((visibility ("default")))
#endif

#define WK_CLASS_AVAILABLE_IOS(_iOSIntro)   NS_CLASS_AVAILABLE_IOS(_iOSIntro)
#define WK_AVAILABLE_WATCHOS_ONLY(_watchOSIntro) __WATCHOS_AVAILABLE(_watchOSIntro) __IOS_UNAVAILABLE
#define WK_AVAILABLE_IOS_ONLY(_iOSIntro) __IOS_AVAILABLE(_iOSIntro) __WATCHOS_UNAVAILABLE
#define WK_AVAILABLE_WATCHOS_IOS(_watchOSIntro,_iOSIntro) __WATCHOS_AVAILABLE(_watchOSIntro) __IOS_AVAILABLE(_iOSIntro)
