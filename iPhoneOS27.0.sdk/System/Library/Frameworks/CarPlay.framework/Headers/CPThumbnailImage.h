//
//  CPThumbnail.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <CarPlay/CPImageOverlay.h>
#import <CarPlay/CPSportsOverlay.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPThumbnailImage : NSObject <NSSecureCoding>

/**
 Initialize a thumbnail with an image.

 @param image The image to display in the thumbnail.
 */
- (instancetype)initWithImage:(UIImage *)image API_AVAILABLE(ios(26.4));

/**
 Initialize a thumbnail with a combination of properties.
 
 @param image The image to display in the thumbnail.
 @param imageOverlay The image overlay for the thumbnail.
 @param sportsOverlay The sports overlay for the thumbnail.
 */
- (instancetype)initWithImage:(UIImage *)image
                 imageOverlay:(nullable CPImageOverlay *)imageOverlay
                sportsOverlay:(nullable CPSportsOverlay *)sportsOverlay API_AVAILABLE(ios(26.4));

- (instancetype)init NS_UNAVAILABLE;

/**
 The image displayed in the thumbnail.
 */
@property (nonatomic, strong) UIImage *image API_AVAILABLE(ios(26.4));

/**
 An optional overlay for the thumbnail.
 */
@property (nonatomic, strong, nullable) CPImageOverlay *imageOverlay API_AVAILABLE(ios(26.4));

/**
 An optional sports overlay for the thumbnail.
 */
@property (nonatomic, strong, nullable) CPSportsOverlay *sportsOverlay API_AVAILABLE(ios(26.4));

/**
 Returns the recommended maximum image size for a @c CPThumbnailImage with the given aspect ratio.

 @discussion Use this method to determine the correct size for images before providing them to
 @c CPThumbnailImage. Supplying a correctly-sized image avoids unnecessary memory use from
 oversized images being held in the thumbnail pipeline.

 @param aspectRatio The width-to-height ratio of the image.
 @return The recommended @c CGSize at which to size the image.
 */
+ (CGSize)maximumImageSizeForAspectRatio:(CGFloat)aspectRatio API_AVAILABLE(ios(27.0));

@end

NS_ASSUME_NONNULL_END
