//
//  CPNavigationAlert.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPAlertAction.h>
#import <CarPlay/CPImageSet.h>
#import <CarPlay/CPTemplate.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Reasons why your navigation alert was dismissed.
 */
typedef NS_ENUM(NSUInteger, CPNavigationAlertDismissalContext) {
    CPNavigationAlertDismissalContextTimeout = 0,    // The banner was visible long enough to reach its timeout.
    CPNavigationAlertDismissalContextUserDismissed,  // The banner was dismissed in response to a user button press.
    CPNavigationAlertDismissalContextSystemDismissed // The banner was dismissed because of a request by the app.
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

/**
 Your @c CPNavigationAlert may specify a duration for which the alert will be visible onscreen,
 or 0 for an alert that is visible indefinitely.

 For non-indefinite alerts, this is the minimum duration the alert will be visible.
 */
static NSTimeInterval const CPNavigationAlertMinimumDuration = 5;

/**
 @c CPNavigationAlert is a banner alert that can display map or navigation-related information to the user.
*/
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPNavigationAlert : NSObject <NSSecureCoding>

/**
 Fully specify a @c CPNavigationAlert with a title, image, primary and secondary action,
 and duration.

 @param titleVariants An array of titles. The system will select a title that fits in the available space. The variant strings should be provided as localized, displayable content.

 @param subtitleVariants An array of subtitles. The system will select a subtitle that fits in the available space. The variant strings should be provided as localized, displayable content.

 @param imageSet An optional @c CPImageSet to display in this navigation alert. Animated images are not supported.
 If an animated image is provided, only the first image from each image set will be used.

 @param primaryAction The alert must include at least one action button.

 @param secondaryAction An optional secondary button to display on the trailing edge of this alert.

 @param duration The duration for which this alert should be visible. Specify 0 for an alert
 that displays indefinitely.

 @return an initialized @c CPNavigationAlert.
 */
- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants
                     subtitleVariants:(nullable NSArray <NSString *> *)subtitleVariants
                             imageSet:(nullable CPImageSet *)imageSet
                        primaryAction:(CPAlertAction *)primaryAction
                      secondaryAction:(nullable CPAlertAction *)secondaryAction
                             duration:(NSTimeInterval)duration API_DEPRECATED_WITH_REPLACEMENT("initWithTitleVariants:subtitleVariants:image:primaryAction:secondaryAction:duration", ios(12.0, 13.0)) API_UNAVAILABLE(macos, watchos, tvos);

- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants
                     subtitleVariants:(nullable NSArray <NSString *> *)subtitleVariants
                                image:(nullable UIImage *)image
                        primaryAction:(CPAlertAction *)primaryAction
                      secondaryAction:(nullable CPAlertAction *)secondaryAction
                             duration:(NSTimeInterval)duration;

/**
 Initialize a @c CPNavigationAlert with a title, image, an array of actions, and duration.

 @param titleVariants An array of titles. The system will select a title that fits in the available space. The variant strings should be provided as localized, displayable content.

 @param subtitleVariants An array of subtitles. The system will select a subtitle that fits in the available space. The variant strings should be provided as localized, displayable content.

 @param avatarImage An optional @c UIImage to display in this navigation alert. Animated images are not supported. It will be displayed in the top leading corner.

 @param alertImage An optional @c UIImage to display in this navigation alert. Animated images are not supported. It will be displayed above the action buttons. Note that this image may be hidden by the system if the available screen space is too small.

 @param actions An array of @c CPAlertAction objects. The number of actions will be clamped to @c maximumActionsCount.

 @param duration The duration for which this alert should be visible. Specify 0 for an alert
 that displays indefinitely.

 @return an initialized @c CPNavigationAlert.
 */
- (instancetype)initWithTitleVariants:(NSArray <NSString *> *)titleVariants
                     subtitleVariants:(NSArray <NSString *> *)subtitleVariants
                          avatarImage:(nullable UIImage *)avatarImage
                           alertImage:(nullable UIImage *)alertImage
                              actions:(NSArray<CPAlertAction *> *)actions
                             duration:(NSTimeInterval)duration API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos);

/**
 The navigation alert may be updated with new title and subtitle variants, either
 after it has already been displayed on screen, or before its initial presentation on screen.

 Updating an alert that has been already been dismissed has no effect.

 @param newTitleVariants an updated array of title variants
 @param newSubtitleVariants an updated array of subtitle variants
 */
- (void)updateTitleVariants:(NSArray <NSString *> *)newTitleVariants
           subtitleVariants:(NSArray <NSString *> *)newSubtitleVariants;


/**
 Update the navigation alert with new title variants, subtitle variants, image, actions, and duration.

 Updating an alert that has already been dismissed has no effect.

 @param newTitleVariants An updated array of title variants.
 @param newSubtitleVariants An updated array of subtitle variants.
 @param avatarImage An optional updated @c UIImage to display.
 @param alertImage An optional updated @c UIImage to display. Note that this image may be hidden by the system if the available screen space is too small.
 @param actions An updated array of @c CPAlertAction objects. The number of actions will be clamped to @c maximumActionsCount.
 @param duration The updated duration for which this alert should be visible. Specify -1 to keep duration unaltered. Specify 0 for an alert that displays indefinitely.
 
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
  light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
  or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
  both styles.

  UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 */
- (void)updateTitleVariants:(NSArray <NSString *> *)newTitleVariants
          subtitleVariants:(NSArray <NSString *> *)newSubtitleVariants
               avatarImage:(nullable UIImage *)avatarImage
                alertImage:(nullable UIImage *)alertImage
                    actions:(NSArray<CPAlertAction *> *)actions
                   duration:(NSTimeInterval)duration API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos);

@property (nonatomic, readonly, copy) NSArray <NSString *> *titleVariants;
@property (nonatomic, readonly, copy) NSArray <NSString *> *subtitleVariants;
@property (nullable, nonatomic, readonly, copy) CPImageSet *imageSet;
@property (nullable, nonatomic, readonly, copy) UIImage *image;
@property (nullable, nonatomic, readonly, copy) UIImage *avatarImage API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos);
@property (nullable, nonatomic, readonly, copy) UIImage *alertImage API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos);
@property (nonatomic, readonly, strong) CPAlertAction *primaryAction;
@property (nullable, nonatomic, readonly, strong) CPAlertAction *secondaryAction;
@property (nonatomic, readonly) NSTimeInterval duration;

/**
 The array of actions associated with this navigation alert.

 If the alert was created with the older @c primaryAction / @c secondaryAction initializer,
 this property returns those actions as an array for backward compatibility.
 */
@property (nonatomic, readonly, copy) NSArray<CPAlertAction *> *actions API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos);

/**
 The maximum number of actions that a @c CPNavigationAlert can display.
 */
@property (nonatomic, readonly, class) NSInteger maximumActionsCount API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos);

/**
 The maximum image size for the alert image that a @c CPNavigationAlert can display.
 */
@property (nonatomic, readonly, class) CGSize maximumAlertImageSize API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos);

/**
 The maximum image size for the avatar image that a @c CPNavigationAlert can display.
 */
@property (nonatomic, readonly, class) CGSize maximumAvatarImageSize API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos);

/**
 A Boolean value indicating whether the close button is allowed to appear.

 @discussion Set the value of this property to @c NO to hide the close button.

 Defaults to @c YES.
 */
@property (nonatomic, assign) BOOL showsCloseButton API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END
