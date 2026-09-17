//
//  CPImageOverlay.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Alignment options for positioning.
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
typedef NS_ENUM(NSInteger, CPImageOverlayAlignment) {
    CPImageOverlayAlignmentLeading,
    CPImageOverlayAlignmentCenter,
    CPImageOverlayAlignmentTrailing
} NS_SWIFT_NAME(CPImageOverlay.Alignment);

/**
 An overlay that displays information over an image.
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPImageOverlay : NSObject <NSSecureCoding>

/**
 Initialize an overlay with a UIImage.

 @param image The image to display in the overlay.
 @param alignment The alignment for positioning the overlay.
 */
- (instancetype)initWithImage:(UIImage *)image alignment:(CPImageOverlayAlignment)alignment API_AVAILABLE(ios(26.4));

/**
 Initialize an overlay with properties that control the overlay's appearance and text contents.

 @param text The text to display in the overlay.
 @param textColor The color of the overlay text.
 @param backgroundColor The background color of the overlay.
 @param alignment The alignment for positioning the overlay.
 */
- (instancetype)initWithText:(NSString *)text
                   textColor:(UIColor *)textColor
             backgroundColor:(UIColor *)backgroundColor
                   alignment:(CPImageOverlayAlignment)alignment API_AVAILABLE(ios(26.4));

- (instancetype)init NS_UNAVAILABLE;

/**
 The text displayed in the overlay.
 */
@property (nonatomic, copy, nullable, readonly) NSString *text API_AVAILABLE(ios(26.4));

/**
 The color of the overlay text.
 */
@property (nonatomic, strong, nullable, readonly) UIColor *textColor API_AVAILABLE(ios(26.4));

/**
 The background color of the overlay.
 */
@property (nonatomic, strong, nullable, readonly) UIColor *backgroundColor API_AVAILABLE(ios(26.4));

/**
 An optional image to display in the overlay.
 */
@property (nonatomic, strong, nullable, readonly) UIImage *image API_AVAILABLE(ios(26.4));

/**
 The alignment for positioning the overlay.
 */
@property (nonatomic, assign, readonly) CPImageOverlayAlignment alignment API_AVAILABLE(ios(26.4));

@end

NS_ASSUME_NONNULL_END
