//
//  CPMultiStopCardConfiguration.h
//  CarPlay
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CarPlay/CPTextButton.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)

@interface CPMultiStopCardConfiguration : NSObject <NSSecureCoding>

/**
 Initializes a MultiStopCardConfiguration with an optional title and an array of text buttons
 */
- (instancetype)initWithTitle:(nullable NSString *)title
             buttons:(NSArray<CPTextButton *> *)buttons;

/**
 Initializes a MultiStopCardConfiguration with an optional title, an array of text buttons, and an optional image
 
 Your app should provide a @c UIImage that is display-ready, containing
 two @c UIImageAssets, corresponding to night and day mode.

 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 */
- (instancetype)initWithTitle:(nullable NSString *)title
             buttons:(NSArray<CPTextButton *> *)buttons
                        image:(nullable UIImage *)image;


/**
 Title of panel presented to configure waypoints along a route. If no panel is provided, the panel title will default to "Add Stop".
 */
@property (nonatomic, copy, readonly, nullable) NSString *title;

/**
 An optional image displayed alongside the @c title in the options panel, serving as an entry point to the multi-stop panel.
 */
@property (nonatomic, copy, readonly, nullable) UIImage *image;

/**
 An array of text buttons to be displayed at the bottom of the card presented to configure waypoints along a route.
 @note The multi-stop card may display a maximum of 2 buttons. Setting more than 2 buttons to this
 property will only display the first 2 buttons.
 */
@property (nonatomic, copy, readonly) NSArray<CPTextButton *> *buttons;

@end

NS_ASSUME_NONNULL_END
