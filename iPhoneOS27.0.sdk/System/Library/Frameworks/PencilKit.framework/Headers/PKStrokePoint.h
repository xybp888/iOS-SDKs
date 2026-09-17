//
//  PKStrokePoint.h
//  PencilKit
//
//  Copyright © 2020-2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// A value that stores all attributes of a stroke at a specific point.
///
/// Properties are stored in a compressed format, so the value you read back may not exactly equal the value you set.
API_AVAILABLE(ios(14.0), macos(11.0))
NS_SWIFT_SENDABLE
@interface PKStrokePoint : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/// Creates a stroke point with the specified properties.
- (instancetype)initWithLocation:(CGPoint)location
                      timeOffset:(NSTimeInterval)timeOffset
                            size:(CGSize)size
                         opacity:(CGFloat)opacity
                           force:(CGFloat)force
                         azimuth:(CGFloat)azimuth
                        altitude:(CGFloat)altitude NS_DESIGNATED_INITIALIZER;

/// Creates a stroke point with the specified properties, including secondary scale.
- (instancetype)initWithLocation:(CGPoint)location
                      timeOffset:(NSTimeInterval)timeOffset
                            size:(CGSize)size
                         opacity:(CGFloat)opacity
                           force:(CGFloat)force
                         azimuth:(CGFloat)azimuth
                        altitude:(CGFloat)altitude
                  secondaryScale:(CGFloat)secondaryScale API_AVAILABLE(ios(17.0), macos(14.0)) NS_DESIGNATED_INITIALIZER;

/// Creates a stroke point with the specified properties, including a rendering threshold.
- (instancetype)initWithLocation:(CGPoint)location
                      timeOffset:(NSTimeInterval)timeOffset
                            size:(CGSize)size
                         opacity:(CGFloat)opacity
                           force:(CGFloat)force
                         azimuth:(CGFloat)azimuth
                        altitude:(CGFloat)altitude
                  secondaryScale:(CGFloat)secondaryScale
                       threshold:(CGFloat)threshold API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0)) NS_DESIGNATED_INITIALIZER;

/// Creates a stroke point with the specified properties, including lateral jitter.
- (instancetype)initWithLocation:(CGPoint)location
                      timeOffset:(NSTimeInterval)timeOffset
                            size:(CGSize)size
                         opacity:(CGFloat)opacity
                           force:(CGFloat)force
                         azimuth:(CGFloat)azimuth
                        altitude:(CGFloat)altitude
                  secondaryScale:(CGFloat)secondaryScale
                       threshold:(CGFloat)threshold
                   lateralJitter:(CGFloat)lateralJitter API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0)) NS_DESIGNATED_INITIALIZER;

/// The location of the point.
@property (nonatomic, readonly) CGPoint location;

/// The time offset in seconds from the start of the stroke path.
@property (nonatomic, readonly) NSTimeInterval timeOffset;

/// The size of the point.
@property (nonatomic, readonly) CGSize size;

/// The opacity of the point, in the range 0 to 2.
@property (nonatomic, readonly) CGFloat opacity;

/// The force used to create the point.
@property (nonatomic, readonly) CGFloat force;

/// The azimuth of the point in radians, in the range 0.0 to 2π.
@property (nonatomic, readonly) CGFloat azimuth;

/// The altitude used to create the point in radians, in the range 0.0 to π/2.
@property (nonatomic, readonly) CGFloat altitude;

/// The scale factor for secondary rendering effects at this point.
///
/// For example, this controls the pigment spread in watercolor ink.
@property (nonatomic, readonly) CGFloat secondaryScale API_AVAILABLE(ios(17.0), macos(14.0));

/// The alpha threshold for clipping the stroke rendering for supported inks.
///
/// Only pixels with an alpha greater than the threshold are drawn. A threshold of `0` has no effect
/// on rendering; a threshold of `1` draws nothing. Thresholds apply only to some inks, such as `PKInkIdentifierReed`.
@property (nonatomic, readonly) CGFloat threshold API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0));

/// The amount of lateral particle jitter at the stroke edge for supported inks.
///
/// Lateral jitter applies only to some inks, such as `PKInkIdentifierPencil`.
@property (nonatomic, readonly) CGFloat lateralJitter API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));

@end

NS_ASSUME_NONNULL_END
