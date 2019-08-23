//
//  INAmountType.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INAmountType_h
#define INAmountType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INAmountType) {
    INAmountTypeUnknown = 0,
    INAmountTypeMinimumDue,
    INAmountTypeAmountDue,
    INAmountTypeCurrentBalance,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INAmountType_h
