//
//  UIGraphicsImageRenderer.h
//  UIKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <UIKit/UIGraphicsRenderer.h>
#import <UIKit/UIImage.h>

NS_ASSUME_NONNULL_BEGIN

@class UIGraphicsImageRendererContext;

typedef void (^UIGraphicsImageDrawingActions)(UIGraphicsImageRendererContext *rendererContext) NS_AVAILABLE_IOS(10_0);


NS_CLASS_AVAILABLE_IOS(10_0) @interface UIGraphicsImageRendererFormat : UIGraphicsRendererFormat
@property (nonatomic) CGFloat scale; // display scale of the context. defaults to mainScreen scale.
@property (nonatomic) BOOL opaque; // indicates the bitmap context will draw fully opaque. defaults to NO.
@property (nonatomic) BOOL prefersExtendedRange; // indicates the bitmap context should draw into a context capable of rendering extended color images. Defaults to NO on hardware that does not support deep color, YES on hardware that does.
@end

NS_CLASS_AVAILABLE_IOS(10_0) @interface UIGraphicsImageRendererContext : UIGraphicsRendererContext
@property (nonatomic, readonly) UIImage *currentImage; // Returns a UIImage representing the current state of the renderer's CGContext
@end

NS_CLASS_AVAILABLE_IOS(10_0) @interface UIGraphicsImageRenderer : UIGraphicsRenderer
- (instancetype)initWithSize:(CGSize)size;
- (instancetype)initWithSize:(CGSize)size format:(UIGraphicsImageRendererFormat *)format NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithBounds:(CGRect)bounds format:(UIGraphicsImageRendererFormat *)format NS_DESIGNATED_INITIALIZER;

// Returns a UIImage rendered with the contents of the CGContext after the imageRenderBlock executes.
// If the options provided to the renderer contain a rect with a zero width or height size, this will return an empty UIImage.
- (UIImage *)imageWithActions:(NS_NOESCAPE UIGraphicsImageDrawingActions)actions;

// These return compressed image data with the contents of the image drawn in the renderer block.
- (NSData *)PNGDataWithActions:(NS_NOESCAPE UIGraphicsImageDrawingActions)actions;
- (NSData *)JPEGDataWithCompressionQuality:(CGFloat)compressionQuality actions:(NS_NOESCAPE UIGraphicsImageDrawingActions)actions;
@end

NS_ASSUME_NONNULL_END
