//
//  NIDLTDOAMeasurement.h
//  NearbyInteraction
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIExport.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The coordinate types of DL-TDOA measurement updates that Nearby Interaction supports.
 */

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst)
typedef NS_ENUM(NSInteger, NIDLTDOACoordinatesType) {
    NIDLTDOACoordinatesTypeGeodetic = 0,
    NIDLTDOACoordinatesTypeRelative = 1,
};

/**
 The measurement types of DL-TDOA measurement updates that Nearby Interaction supports.
 */

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst)
typedef NS_ENUM(NSInteger, NIDLTDOAMeasurementType) {
    NIDLTDOAMeasurementTypePoll     = 0,
    NIDLTDOAMeasurementTypeResponse = 1,
    NIDLTDOAMeasurementTypeFinal    = 2,
};

/**
 Represents floor elevation info of a DL-TDOA anchor.
*/
NS_SWIFT_SENDABLE
NS_SWIFT_NAME(NIDLTDOAMeasurement.FloorElevation)
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst)
NI_EXPORT
@interface NIDLTDOAMeasurementFloorElevation : NSObject <NSCopying>
/**
 Indicates the floor number relative to ground level.  Negative values indicate floors below ground level; positive values indicate floors above.
*/
@property (nonatomic, assign, readonly) NSInteger floorNumber;

/**
 Indicates the anchor's height above the floor in meters.
*/
@property (nonatomic, assign, readonly) double height;

/** Unavailable  */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Represents a single measurement relative to a DL-TDOA anchor.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst)
NI_EXPORT
@interface NIDLTDOAMeasurement : NSObject <NSCopying, NSSecureCoding>
/**
 Indicates the address of anchor of this measurement.
*/
@property (nonatomic, assign, readonly) NSUInteger address;

/**
 Indicates the address of initator anchor from the same cluster.
*/
@property (nonatomic, assign, readonly) NSUInteger clusterInitiatorAddress API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst);

/**
 Indicates the type of this measurement.
*/
@property (nonatomic, assign, readonly) NIDLTDOAMeasurementType measurementType;

/**
 Indicates the transmission timestamp (in seconds).
*/
@property (nonatomic, assign, readonly) double transmitTime;

/**
 Indicates the raw transmission timestamp (in units of 15.65 picoseconds).
*/
@property (nonatomic, assign, readonly) uint64_t rawTransmitTime API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst);

/**
 Indicates the reception timestamp (in seconds).
*/
@property (nonatomic, assign, readonly) double receiveTime;

/**
 Indicates the raw reception timestamp (in units of 15.65 picoseconds).
*/
@property (nonatomic, assign, readonly) uint64_t rawReceiveTime API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst);

/**
 Indicates the signal strength in dBm.
*/
@property (nonatomic, assign, readonly) double signalStrength;

/**
 Indicates the estimated carrier frequency offset (dimensionless).
*/
@property (nonatomic, assign, readonly) double carrierFrequencyOffset;

/**
 Indicates the clock frequency offset (CFO) fraction of the responder anchor relative to the initiator anchor (dimensionless).
 For example, a positive value means for every 1 clock cycle, the responder runs fewer cycles than initiator.
 Returns nil when measurementType is not NIDLTDOAMeasurementTypeResponse, or when the value is not available.
*/
@property (nonatomic, strong, readonly, nullable) NSNumber* responderClockFrequencyOffset NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst);

/**
 Inidicates the type of coordinates of this anchor.
*/
@property (nonatomic, assign, readonly) NIDLTDOACoordinatesType coordinatesType;

/**
 Indicates the anchor's coordinates:

 When coordinatesType == NIDLTDOACoordinatesTypeGeodetic:
    coordinates represent geodetic position in 3D space with format {latitude, longitude, altitude}.
    If `NIDLTDOAMeasurementFloorElevation` is non-nil, the altitude component is replaced by the floor elevation.

 When coordinatesType == NIDLTDOACoordinatesTypeRelative:
    coordinates represent distances from anchor(s) along the 3 axes in 3D space with format {x, y, z}.
    If `NIDLTDOAMeasurementFloorElevation` is non-nil, the z component is replaced by the floor elevation.
 */
@property (nonatomic, assign, readonly) simd_double3 coordinates;

/**
   The floor elevation of the anchor, if available.
                                                                                                                                                                                                                                              
   When non-nil, this value overrides the altitude component of `coordinates` for `NIDLTDOACoordinatesTypeGeodetic`, and the z component for `NIDLTDOACoordinatesTypeRelative`.

   A nil value indicates that no floor elevation information is available for this anchor.
 */
@property (nonatomic, copy, readonly, nullable) NIDLTDOAMeasurementFloorElevation* floorElevation API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst);

/** Unavailable  */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
