//
//  INImage+IntentsUI.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INImage.h>

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

@class INIntentResponse;

@interface INImage (IntentsUI)

+ (instancetype)imageWithCGImage:(CGImageRef)imageRef API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);
+ (instancetype)imageWithUIImage:(UIImage *)image API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

/*!
 @abstract Returns the image size at which the image for an INIntentResponse will be displayed
 */
+ (CGSize)imageSizeForIntentResponse:(INIntentResponse *)response API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

@end
