//
//  NIDeviceCapability.h
//  NearbyInteraction
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIExport.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT
@protocol NIDeviceCapability

/**
 Whether or not this device is capable of participating in a nearby interaction session with precise ranging
 */
@property (nonatomic, readonly) BOOL supportsPreciseDistanceMeasurement;

/**
 Whether or not this device is capable of participating in a nearby interaction session with instantaneous direction
 */
@property (nonatomic, readonly) BOOL supportsDirectionMeasurement;

/**
 Whether or not this device is capable of participating in a nearby interaction session with camera assistance
 */
@property (nonatomic, readonly) BOOL supportsCameraAssistance;

@end

NS_ASSUME_NONNULL_END
