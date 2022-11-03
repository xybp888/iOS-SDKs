//
//  DCError.h
//  DeviceCheck
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <DeviceCheck/DeviceCheck.h>

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const DCErrorDomain API_AVAILABLE(ios(11.0), macos(10.15), tvos(11.0), watchos(9.0));

typedef NS_ERROR_ENUM(DCErrorDomain, DCError) {
    DCErrorUnknownSystemFailure,
    DCErrorFeatureUnsupported,
    DCErrorInvalidInput,
    DCErrorInvalidKey,
    DCErrorServerUnavailable,
} API_AVAILABLE(ios(11.0), macos(10.15), tvos(11.0), watchos(9.0));

NS_ASSUME_NONNULL_END

