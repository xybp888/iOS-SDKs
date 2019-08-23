//
//  INMessageAttribute.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INMessageAttribute_h
#define INMessageAttribute_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INMessageAttribute) {
    INMessageAttributeUnknown = 0,
    INMessageAttributeRead,
    INMessageAttributeUnread,
    INMessageAttributeFlagged,
    INMessageAttributeUnflagged,
} API_AVAILABLE(ios(10.0), watchos(3.2));

#endif // INMessageAttribute_h
