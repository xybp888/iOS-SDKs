//
//  PKDrawing.h
//  PencilKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <PencilKit/PKContentVersion.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif


NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif
/// The UTType identifier for PencilKit drawing data.
extern const CFStringRef PKAppleDrawingTypeIdentifier API_AVAILABLE(ios(13.0), macos(10.15));

#ifdef __cplusplus
}
#endif

@class PKStroke, PKStrokePath;

/// The data model for a drawing that a `PKCanvasView` displays.
API_AVAILABLE(ios(13.0), macos(10.15))
NS_SWIFT_SENDABLE
@interface PKDrawing : NSObject <NSCopying, NSSecureCoding>

/// Creates a blank drawing.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates a drawing with the specified strokes.
///
/// When setting strokes, duplicate IDs are automatically resolved by generating
/// new UUIDs for conflicting strokes. The first occurrence keeps its original ID.
- (instancetype)initWithStrokes:(NSArray<PKStroke *> *)strokes API_AVAILABLE(ios(14.0), macos(11.0));

/// Creates a drawing from the specified encoded data.
///
/// @param data The data containing the encoded drawing.
/// @param error If an error occurs, upon return the `NSError` object describes the error.
///   Pass `NULL` to ignore errors.
/// @return An initialized `PKDrawing` object on success, or `nil` if the data is invalid.
- (nullable instancetype)initWithData:(NSData *)data error:(NSError * _Nullable *)error NS_DESIGNATED_INITIALIZER;

/// Returns a data representation of the drawing.
///
/// @return An `NSData` object containing the drawing data.
- (NSData *)dataRepresentation;

/// The strokes the drawing contains.
@property (nonatomic, readonly) NSArray<PKStroke *> *strokes API_AVAILABLE(ios(14.0), macos(11.0));

/// The bounds of the drawing's contents, accounting for the rendered width of all strokes.
///
/// Passing these bounds to `imageFromRect:scale:` produces an image that includes all content without cropping.
@property (nonatomic, readonly) CGRect bounds;

/// The PencilKit version required to use this drawing.
@property (nonatomic, readonly) PKContentVersion requiredContentVersion API_AVAILABLE(ios(17.0), macos(14.0));

/// Returns a non-opaque image of the drawing rendered from the specified rectangle at the given scale.
///
/// @param rect The rect in the drawing to render.
/// @param scale The scale of image to render. Specify `0.0` to use the scale factor of the device’s main screen.
/// @return A non-opaque image of this drawing with pixel dimensions `rect.size * scale`.
#if TARGET_OS_IPHONE
- (UIImage *)imageFromRect:(CGRect)rect scale:(CGFloat)scale;
#else
- (NSImage *)imageFromRect:(CGRect)rect scale:(CGFloat)scale;
#endif

/// Returns a new drawing with the specified transform applied.
///
/// @param transform The transform to apply to this drawing.
/// @return A new copy of this drawing with `transform` applied.
- (PKDrawing *)drawingByApplyingTransform:(CGAffineTransform)transform;

/// Returns a new drawing by appending the contents of the specified drawing on top of the receiver's contents.
///
/// @param drawing The drawing to append.
/// @return A new copy of this drawing with `drawing` appended.
///
/// The combined array of strokes is uniqued by `strokeID`.
- (PKDrawing *)drawingByAppendingDrawing:(PKDrawing *)drawing;

/// Returns a new drawing with the specified strokes appended.
///
/// @param strokes The strokes to append.
/// @return A new copy of this drawing with `strokes` appended.
///
/// The combined array of strokes is uniqued by `strokeID`.
- (PKDrawing *)drawingByAppendingStrokes:(NSArray<PKStroke *> *)strokes API_AVAILABLE(ios(14.0), macos(11.0));

/// Returns a new drawing with strokes erased along the specified stroke path.
///
/// @param eraserPath The path to erase through this drawing.
/// @param mask An optional mask to constrain the eraser’s effect to a specific region.
/// @param transform The transform to apply to the path being erased.
/// @return A new copy of this drawing with strokes erased by the path.
#if TARGET_OS_IPHONE
- (PKDrawing *)drawingByErasingStrokePath:(PKStrokePath *)eraserPath mask:(nullable UIBezierPath *)mask transform:(CGAffineTransform)transform API_AVAILABLE(ios(27.0), visionos(27.0));
#else
- (PKDrawing *)drawingByErasingStrokePath:(PKStrokePath *)eraserPath mask:(nullable NSBezierPath *)mask transform:(CGAffineTransform)transform API_AVAILABLE(macos(27.0));
#endif

@end

NS_ASSUME_NONNULL_END
