//
//  PKStrokePath.h
//  PencilKit
//
//  Copyright © 2020-2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@class PKStrokePoint;

/// Information about a B-spline control point converted from a Bézier path.
///
/// Provided to the `pointProvider` closure of ``PKStrokePath-class/initWithBezierPath:creationDate:pointProvider:``
/// to initialize each ``PKStrokePoint-class`` of the resulting path.
API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0))
NS_SWIFT_NAME(PKConvertedBezierPointReference)
@interface PKConvertedBezierPoint : NSObject

/// The index of the point along the path.
@property (nonatomic, readonly, assign) NSInteger index;

/// The total number of B-Spline control points in the path.
@property (nonatomic, readonly, assign) NSInteger pointCount;

/// The location of the cubic uniform B-Spline control point.
@property (nonatomic, readonly, assign) CGPoint location;

/// The index of the Bézier segment the point originates from, not including `move to` elements.
@property (nonatomic, readonly, assign) NSInteger bezierSegmentIndex;

- (instancetype)init NS_UNAVAILABLE;

@end

/// A uniform cubic B-spline representing the point data of a `PKStroke`.
API_AVAILABLE(ios(14.0), macos(11.0))
NS_SWIFT_SENDABLE
@interface PKStrokePath : NSObject <NSCopying>

/// Creates a stroke path with the specified cubic B-spline control points.
///
/// @param controlPoints An array of control points for a cubic B-spline.
/// @param creationDate The start time of this path.
- (instancetype)initWithControlPoints:(NSArray<PKStrokePoint *> *)controlPoints creationDate:(NSDate *)creationDate NS_DESIGNATED_INITIALIZER;

/// Creates a stroke path with the specified control points and a unique identifier.
///
/// @param controlPoints An array of control points for a cubic B-spline.
/// @param creationDate The start time of this path.
/// @param strokePathID The unique identity of the stroke path.
///
/// > Warning: Using multiple stroke paths with identical IDs but different control points
/// will result in undefined rendering behavior. Ensure each stroke path has a unique identifier.
- (instancetype)initWithControlPoints:(NSArray<PKStrokePoint *> *)controlPoints creationDate:(NSDate *)creationDate strokePathID:(NSUUID *)strokePathID API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));

/// Creates a stroke path recreating the specified Bézier path as a cubic uniform B-Spline.
///
/// @param bezierPath The Bézier path to convert to a cubic uniform B-Spline.
/// @param creationDate The start time of this path.
/// @param pointProvider Block to initialize the `PKStrokePoint`s of the path. A single `PKConvertedBezierPoint` instance is shared across all converted points.
///
/// The count of control points of the generated spline is not guaranteed to be a specific value
/// except when the provided path is the output of ``bezierRepresentation->CGPathRef``, where it will match the original curve.
///
/// The output B-Spline will have continuous curvature and 0 curvature at the endpoints. In cases where the B-Spline
/// cannot fully recreate the Bézier path, it will be an approximation. For example, if the given Bézier path includes
/// `line to` elements, these will produce straight line segments in the resulting B-Spline, but if a `line to` element
/// is adjacent to a `curve to` element, the resulting curve may not match the original.
///
/// > Warning: For a Bézier path with multiple subpaths, only the first will be converted.
- (instancetype)initWithBezierPath:(CGPathRef)bezierPath creationDate:(NSDate *)creationDate pointProvider:(PKStrokePoint *(NS_NOESCAPE ^)(PKConvertedBezierPoint *convertedPoint))pointProvider API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));

/// The unique identity of the stroke path.
///
/// > Warning: Using multiple stroke paths with identical IDs but different control points
/// will result in undefined rendering behavior. Ensure each stroke path has a unique identifier.
@property (nonatomic, readonly) NSUUID *strokePathID API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));

/// The number of control points in the stroke path.
@property (nonatomic, readonly) NSUInteger count;

/// The time at which the stroke path started.
///
/// The `timeOffset` of each contained `PKStrokePoint` is relative to this date.
@property (nonatomic, readonly) NSDate *creationDate;

/// A Bézier path representation of the path's curve, computed in linear time.
@property (nonatomic, readonly) CGPathRef bezierRepresentation API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));

/// Returns a copy of the path containing the control points in the specified parametric range.
///
/// @param range The parametric range to copy. Values must be within [0, count-1].
/// @return A new stroke path containing the portion within the specified parametric range.
- (PKStrokePath *)subpathWithRange:(PKFloatRange *)range API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));

/// Returns the B-spline control point at the specified index.
- (PKStrokePoint *)pointAtIndex:(NSUInteger)i;

/// Returns the B-spline control point at the specified index.
- (PKStrokePoint *)objectAtIndexedSubscript:(NSUInteger)i;

/// Returns the on-curve location for the specified parametric value.
///
/// The floating-point `parametricValue` must be in the range [0, count-1].
///
/// This has better performance than `[self interpolatedPointAt: parametricValue].location`
/// when only the location is required.
- (CGPoint)interpolatedLocationAt:(CGFloat)parametricValue;

/// Returns the on-curve stroke point for the specified parametric value.
- (PKStrokePoint *)interpolatedPointAt:(CGFloat)parametricValue;

/// Executes a block for each interpolated point in the specified range, stepping by distance.
///
/// @param range The parametric range to enumerate points in.
/// @param distanceStep The distance to step between points.
/// @param block The block to execute for each point. The block receives the interpolated point
///        and a stop flag; set the flag to `YES` to stop enumeration.
- (void)enumerateInterpolatedPointsInRange:(PKFloatRange *)range strideByDistance:(CGFloat)distanceStep usingBlock:(void (^)(PKStrokePoint *point, BOOL *stop))block
#if __swift__
API_DEPRECATED("Use `PKStrokePath.interpolatedPoints(in:by:)`", ios(14.0, API_TO_BE_DEPRECATED), macos(11.0, API_TO_BE_DEPRECATED))
#endif
;

/// Executes a block for each interpolated point in the specified range, stepping by time interval.
///
/// @param range The parametric range to enumerate points in.
/// @param timeStep The time interval to step between points.
/// @param block The block to execute for each point. The block receives the interpolated point
///        and a stop flag; set the flag to `YES` to stop enumeration.
- (void)enumerateInterpolatedPointsInRange:(PKFloatRange *)range strideByTime:(NSTimeInterval)timeStep usingBlock:(void (^)(PKStrokePoint *point, BOOL *stop))block
#if __swift__
API_DEPRECATED("Use `PKStrokePath.interpolatedPoints(in:by:)`", ios(14.0, API_TO_BE_DEPRECATED), macos(11.0, API_TO_BE_DEPRECATED))
#endif
;

/// Executes a block for each interpolated point in the specified range, stepping by a parametric step.
///
/// @param range The parametric range to enumerate points in.
/// @param parametricStep The parametric step between points.
/// @param block The block to execute for each point. The block receives the interpolated point
///        and a stop flag; set the flag to `YES` to stop enumeration.
- (void)enumerateInterpolatedPointsInRange:(PKFloatRange *)range strideByParametricStep:(CGFloat)parametricStep usingBlock:(void (^)(PKStrokePoint *point, BOOL *stop))block
#if __swift__
API_DEPRECATED("Use `PKStrokePath.interpolatedPoints(in:by:)`", ios(14.0, API_TO_BE_DEPRECATED), macos(11.0, API_TO_BE_DEPRECATED))
#endif
;

/// Returns a parametric value on the B-spline that is a specified distance from the given parametric value.
///
/// @param parametricValue The floating point [0, count-1] parametric value.
/// @param distanceStep The distance to offset `parametricValue`. Can be positive or negative.
/// @return A parametric value offset by `distanceStep` from `parametricValue`.
- (CGFloat)parametricValue:(CGFloat)parametricValue offsetByDistance:(CGFloat)distanceStep;

/// Returns a parametric value on the B-spline that is a specified time from the given parametric value.
///
/// @param parametricValue The floating point [0, count-1] parametric value.
/// @param timeStep The time to offset `parametricValue`. Can be positive or negative.
/// @return A parametric value offset by `timeStep` from `parametricValue`.
- (CGFloat)parametricValue:(CGFloat)parametricValue offsetByTime:(NSTimeInterval)timeStep;

@end

NS_ASSUME_NONNULL_END
