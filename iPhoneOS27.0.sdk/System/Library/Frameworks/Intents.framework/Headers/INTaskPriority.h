//
//  INTaskPriority.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#ifndef INTaskPriority_h
#define INTaskPriority_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INTaskPriority) {
    INTaskPriorityUnknown = 0,
    INTaskPriorityNotFlagged,
    INTaskPriorityFlagged,
} API_DEPRECATED("INTaskPriority is deprecated. Please adopt the Notes or Reminders AppSchema domain instead.", ios(13.0, 27.0), watchos(6.0, 27.0)) API_UNAVAILABLE(macos, tvos);

#endif // INTaskPriority_h
