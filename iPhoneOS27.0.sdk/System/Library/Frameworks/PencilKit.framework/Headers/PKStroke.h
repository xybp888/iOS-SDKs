//
//  PKStroke.h
//  PencilKit
//
//  Copyright © 2020-2026 Apple Inc. All rights reserved.
//

#import <PencilKit/PKContentVersion.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

@class PKInk, PKStrokePath, PKFloatRange, PKStrokeRenderState;

NS_ASSUME_NONNULL_BEGIN

/// The data model value representing a stroke in a `PKDrawing`.
API_AVAILABLE(ios(14.0), macos(11.0))
NS_SWIFT_SENDABLE
@interface PKStroke : NSObject <NSCopying>

/// Creates a stroke with the specified ink, path, transform, and mask.
///
/// @param ink The ink for the stroke.
/// @param strokePath The B-spline stroke path for the stroke.
/// @param transform The affine transform of the stroke.
/// @param mask The mask for the stroke.
#if TARGET_OS_IPHONE
- (instancetype)initWithInk:(PKInk *)ink
                 strokePath:(PKStrokePath *)strokePath
                  transform:(CGAffineTransform)transform
                       mask:(nullable UIBezierPath *)mask;
#else
- (instancetype)initWithInk:(PKInk *)ink
                 strokePath:(PKStrokePath *)strokePath
                  transform:(CGAffineTransform)transform
                       mask:(nullable NSBezierPath *)mask;
#endif

/// Creates a stroke with the specified ink, path, transform, mask, and random seed.
///
/// @param ink The ink for the stroke.
/// @param strokePath The B-spline stroke path for the stroke.
/// @param transform The affine transform of the stroke.
/// @param mask The mask for the stroke.
/// @param randomSeed The random seed for the stroke.
#if TARGET_OS_IPHONE
- (instancetype)initWithInk:(PKInk *)ink
                 strokePath:(PKStrokePath *)strokePath
                  transform:(CGAffineTransform)transform
                       mask:(nullable UIBezierPath *)mask
                 randomSeed:(uint32_t)randomSeed API_AVAILABLE(ios(16.0), macos(13.0));
#else
- (instancetype)initWithInk:(PKInk *)ink
                 strokePath:(PKStrokePath *)strokePath
                  transform:(CGAffineTransform)transform
                       mask:(nullable NSBezierPath *)mask
                 randomSeed:(uint32_t)randomSeed API_AVAILABLE(ios(16.0), macos(13.0));
#endif

/// Creates a stroke with the specified ink, path, transform, mask, random seed, ID, render group, and render state.
///
/// @param ink The ink for the stroke.
/// @param strokePath The B-spline stroke path for the stroke.
/// @param transform The affine transform of the stroke.
/// @param mask The mask for the stroke.
/// @param randomSeed The random seed for the stroke.
/// @param strokeID The unique identity of the stroke.
/// @param renderGroupID See this property for more information.
/// @param renderState See this property for more information.
#if TARGET_OS_IPHONE
- (instancetype)initWithInk:(PKInk *)ink
                 strokePath:(PKStrokePath *)strokePath
                  transform:(CGAffineTransform)transform
                       mask:(nullable UIBezierPath *)mask
                 randomSeed:(uint32_t)randomSeed
                   strokeID:(NSUUID *)strokeID
              renderGroupID:(nullable NSUUID *)renderGroupID
                renderState:(nullable PKStrokeRenderState *)renderState
    NS_SWIFT_NAME(init(ink:strokePath:transform:mask:randomSeed:strokeID:renderGroupID:renderState:))
    API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));
#else
- (instancetype)initWithInk:(PKInk *)ink
                 strokePath:(PKStrokePath *)strokePath
                  transform:(CGAffineTransform)transform
                       mask:(nullable NSBezierPath *)mask
                 randomSeed:(uint32_t)randomSeed
                   strokeID:(NSUUID *)strokeID
              renderGroupID:(nullable NSUUID *)renderGroupID
                renderState:(nullable PKStrokeRenderState *)renderState
    NS_SWIFT_NAME(init(ink:strokePath:transform:mask:randomSeed:strokeID:renderGroupID:renderState:))
    API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));
#endif

/// The PencilKit version required to use this stroke.
@property (nonatomic, readonly) PKContentVersion requiredContentVersion API_AVAILABLE(ios(17.0), macos(14.0));

/// The ink used to render this stroke.
@property (nonatomic, readonly) PKInk *ink;

/// The unique identity of the stroke.
@property (nonatomic, readonly) NSUUID *strokeID API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));

/// The affine transform of the stroke when rendered.
@property (nonatomic, readonly) CGAffineTransform transform;

/// The B-spline path that describes this stroke.
@property (nonatomic, readonly) PKStrokePath *path;

/// The pre-transform mask that clips the stroke rendering, set by tools such as the bitmap eraser or ruler.
#if TARGET_OS_IPHONE
@property (nonatomic, readonly, nullable) UIBezierPath *mask;
#else
@property (nonatomic, readonly, nullable) NSBezierPath *mask;
#endif

/// The bounds of the rendered stroke, including its width and ink after the transform is applied.
@property (nonatomic, readonly) CGRect renderBounds;

/// The parametric ranges of points in the stroke path that intersect the mask.
@property (nonatomic, readonly) NSArray<PKFloatRange *> *maskedPathRanges;

/// The random seed for drawing strokes that use randomized effects.
@property (nonatomic, readonly) uint32_t randomSeed API_AVAILABLE(ios(16.0), macos(13.0));

/// A UUID that groups strokes for wet-ink compositing with compatible inks such as marker.
///
/// Set this to the same value for a run of strokes to render them as if drawn while the previous
/// stroke with the same ink was still wet.
@property (nonatomic, readonly, nullable) NSUUID *renderGroupID API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));

/// The render details of the stroke, such as particle positioning. Uses default rendering when nil.
///
/// This may be set on substrokes returned by `-substrokeWithRange:`.
@property (nonatomic, readonly, nullable) PKStrokeRenderState *renderState API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));

/// Returns a copy of the stroke containing the control points in the specified range.
///
/// Maintains rendering information so the returned substroke renders the same as the corresponding
/// portion of the receiver. The returned stroke may have a `renderState` set to maintain this information.
///
/// @param range The range of control points in the receiver to copy to the returned stroke.
/// @returns A new stroke containing only the control points within the specified range.
- (PKStroke *)substrokeWithRange:(PKFloatRange *)range API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0));

@end

NS_ASSUME_NONNULL_END
