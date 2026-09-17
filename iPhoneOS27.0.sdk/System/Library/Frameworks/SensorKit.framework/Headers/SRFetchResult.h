//
//  SRFetchResult.h
//  SensorKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <SensorKit/SRAbsoluteTime.h>
#import <Foundation/Foundation.h>
#import <SensorKit/SRSourceDevice.h>

NS_ASSUME_NONNULL_BEGIN

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos)
@interface SRFetchResult <SampleType> : NSObject <NSCopying>
/**
 * @brief Retrieves the resultant sample
 * @discussion The caller is expected to know what the result type should be
 * @note This may thrown an exception if the sample could not be constructed from
 * the data in the datastore
 */
@property (readonly, copy) SampleType sample;

/**
 * @brief the timestamp the sample was written to the data store
 */
@property (readonly, assign) SRAbsoluteTime timestamp;

/**
 * @brief the source of the sample data
 *
 * @discussion Represents the peripheral supplying data. Useful for distinguishing
 *             multiple source peripherals using a common device. Is nullable
 *             when no source information is available when providing sample data.
 */
@property (readonly, nonatomic, nullable, strong) SRSourceDevice *sourceDevice API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
