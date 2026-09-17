//
//  INLocationSearchType.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#ifndef INLocationSearchType_h
#define INLocationSearchType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INLocationSearchType) {
    INLocationSearchTypeUnknown = 0,
    INLocationSearchTypeByLocationTrigger,
} API_DEPRECATED("INLocationSearchType is deprecated. Please adopt the Notes or Reminders AppSchema domain instead.", ios(11.0, 27.0), watchos(4.0, 27.0)) API_UNAVAILABLE(macos, tvos);

#endif // INLocationSearchType_h
