//  HMEvent.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a generic HomeKit event.
 */
NS_CLASS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(2_0) __TVOS_AVAILABLE(10_0)
@interface HMEvent : NSObject

/*!
 * @brief A unique identifier for the event.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier;

@end

NS_ASSUME_NONNULL_END
