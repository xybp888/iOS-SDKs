//
//  CPListImageRowItemCardElement.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//


#import <CarPlay/CPListImageRowItemElement.h>
#import <CarPlay/CPThumbnailImage.h>
#import <CarPlay/CPTemplate.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN


API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPListImageRowItemCardElement: CPListImageRowItemElement <NSSecureCoding>

/**
 Initialize a card element with an image.
 
 @param image The image to display in the card.
 @param showsImageFullHeight Whether the image should fill the full height of the card.
 @param title The title text for the card.
 @param subtitle The subtitle text for the card.
 @param tintColor The tint color for the card.
 */
- (instancetype)initWithImage:(UIImage *)image
         showsImageFullHeight:(BOOL)showsImageFullHeight
                        title:(nullable NSString *)title
                     subtitle:(nullable NSString *)subtitle
                    tintColor:(nullable UIColor *)tintColor;

/**
 Initialize an element with a thumbnail, title, subtitle, and tint color.
 
 This initializer uses a CPThumbnailImage which encapsulates the image, aspect ratio,
 image, and sports overlay information.

 @param thumbnail The thumbnail containing image, aspect ratio, image, and sports overlay information.
 @param title The title of the element.
 @param subtitle The subtitle of the element.
 @param tintColor The color used for styling the element.
 */
- (instancetype)initWithThumbnail:(CPThumbnailImage *)thumbnail
                            title:(nullable NSString *)title
                         subtitle:(nullable NSString *)subtitle
                        tintColor:(nullable UIColor *)tintColor API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos);

/**
 The thumbnail associated with this element.
 */
@property (nonatomic, strong, nullable) CPThumbnailImage *thumbnail API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos);

/**
 The title associated with this element.
 */
@property (nonatomic, copy) NSString *title;

/**
 The subtitle associated with this element.
 */
@property (nonatomic, copy, nullable) NSString *subtitle;

/**
 A Boolean value indicating whether the element should be fill with the image.
 
 @discussion Set the value of this property to @c YES to fill the element with the image or @c NO to use a rounded square image that does not fill the card.
 */
@property (nonatomic, assign, readonly) BOOL showsImageFullHeight;

/**
 A UIColor used to tint the element. When @c showsImageFullHeight is true, the tint color is applied behind the labels at the bottom of the card. Otherwise, this color is part of the gradient color at the bottom of the card.

 If this value is nil, iOS will use secondarySystemBackground color.
 */
@property (nonatomic, copy, nullable) UIColor *tintColor;

/**
 The expected image size for the image in your @c CPListImageRowItemCardElement when @c showsImageFullHeight is false. Images provided
 will be resized to this size.

 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, class, readonly) CGSize maximumImageSize;

/**
 The expected image size for the image in your @c CPListImageRowItemCardElement when @c showsImageFullHeight is  true. Images provided
 will be resized to this size.
 
 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, class, readonly) CGSize maximumFullHeightImageSize;

@end

NS_ASSUME_NONNULL_END
