//
//  HKSourceRevision.h
//  HealthKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

@class HKSource;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKSourceRevision
 @abstract      Represents a specific revision of an HKSource.
 */

HK_CLASS_AVAILABLE_IOS_WATCHOS(9_0, 2_0)
@interface HKSourceRevision : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      source
 @abstract      The HKSource of the receiver.
 */
@property (readonly) HKSource *source;

/*!
 @property      version
 @abstract      The version of the source property.
 @discussion    This value is taken from the CFBundleVersion of the source. May be nil for older data.
 */
@property (readonly, nullable) NSString *version;

/*!
 @method        initWithSource:version:
 @abstract      Initializes a new HKSourceRevision with the given source and version.
 */
- (instancetype)initWithSource:(HKSource *)source version:(nullable NSString *)version;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
