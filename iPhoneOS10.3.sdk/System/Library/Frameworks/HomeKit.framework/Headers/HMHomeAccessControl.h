// HMHomeAccessControl.h
// HomeKit
//
// Copyright (c) 2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief Represents the access control of a user associated with a home.
 */
NS_CLASS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(2_0) __TVOS_AVAILABLE(10_0)
@interface HMHomeAccessControl : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Specifies if the user has administrative privileges for the home.
 */
@property(readonly, getter=isAdministrator, nonatomic) BOOL administrator;

@end

NS_ASSUME_NONNULL_END
