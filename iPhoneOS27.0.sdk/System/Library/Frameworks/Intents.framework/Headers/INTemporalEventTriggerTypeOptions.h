//
//  INTemporalEventTriggerTypeOptions.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#ifndef INTemporalEventTriggerTypeOptions_h
#define INTemporalEventTriggerTypeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INTemporalEventTriggerTypeOptions) {
    INTemporalEventTriggerTypeOptionNotScheduled = (1UL << 0),
    INTemporalEventTriggerTypeOptionScheduledNonRecurring = (1UL << 1),
    INTemporalEventTriggerTypeOptionScheduledRecurring = (1UL << 2),
} API_DEPRECATED("INTemporalEventTriggerTypeOptions is deprecated. Please adopt the Notes or Reminders AppSchema domain instead.", ios(13.0, 27.0), watchos(6.0, 27.0)) API_UNAVAILABLE(macos, tvos);

#endif // INTemporalEventTriggerTypeOptions_h
