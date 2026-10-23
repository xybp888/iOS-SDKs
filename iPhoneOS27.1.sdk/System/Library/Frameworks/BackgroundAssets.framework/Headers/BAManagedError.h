//
//  BAManagedError.h
//  Background Assets
//
//  Created by Gabriel Jacoby-Cooper on 4/14/25.
//

#import <BackgroundAssets/BackgroundAssets.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The error domain for managed asset packs.
BA_EXPORT NSErrorDomain const BAManagedErrorDomain
API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT;

/// The `-[NSError userInfo]` key for an asset pack’s identifier.
///
/// This key is relevant when the error code is ``BAManagedErrorCode/BAManagedErrorCodeAssetPackNotFound``. Its value should be an `NSString` object.
BA_EXPORT NSErrorUserInfoKey const BAAssetPackIdentifierErrorKey
API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT;

/// The `-[NSError userInfo]` key for the set of asset packs the local availability of which the system successfully ensured.
///
/// This key is relevant when the error code is ``BAManagedErrorCode/BAManagedErrorCodeLocalAvailabilityFailure``. Its value should be an `NSSet<BAAssetPack*>` object.
BA_EXPORT NSErrorUserInfoKey const BASuccessesErrorKey
API_AVAILABLE(ios(27), macos(27), tvos(27), visionos(27))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT;

/// The `-[NSError userInfo]` key for the set of asset packs the local availability of which the system couldn’t ensure and their respective associated underlying errors.
///
/// This key is relevant when the error code is ``BAManagedErrorCode/BAManagedErrorCodeLocalAvailabilityFailure``. Its value should be an `NSDictionary<BAAssetPack*, NSError*>` object.
BA_EXPORT NSErrorUserInfoKey const BAFailuresErrorKey
API_AVAILABLE(ios(27), macos(27), tvos(27), visionos(27))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT;

/// An error code for a managed asset pack.
typedef NS_ENUM(NSInteger, BAManagedErrorCode) {
    
    /// An error code that indicates the system couldn’t find an asset pack with the given identifier.
    ///
    /// Refer to the value in `-[NSError userInfo]` for the key ``BAAssetPackIdentifierErrorKey`` for the asset pack’s identifier.
    BAManagedErrorCodeAssetPackNotFound,
    
    /// An error code that indicates the system couldn’t find a file at the specified path.
    ///
    /// Refer to the value in `-[NSError userInfo]` for the key `NSFilePathErrorKey` for the file path.
    BAManagedErrorCodeFileNotFound,
    
    /// An error code that indicates that the system couldn’t ensure the local availability of some or all of the requested asset packs.
    ///
    /// Refer to the values in `-[NSError userInfo]` for the keys ``BASuccessesErrorKey`` and ``BAFailuresErrorKey`` for, respectively, the asset packs the local availability of which the system ensured successfully and the asset packs the local availability of which the system couldn’t ensure with associated underlying errors for the latter.
    BAManagedErrorCodeLocalAvailabilityFailure
    
} API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

NS_HEADER_AUDIT_END(nullability, sendability)
