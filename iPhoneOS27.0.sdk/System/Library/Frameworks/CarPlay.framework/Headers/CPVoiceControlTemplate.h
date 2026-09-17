//
//  CPVoiceControlTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <CarPlay/CPBarButtonProviding.h>
#import <CarPlay/CPButton.h>
#import <CarPlay/CPTemplate.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPVoiceControlState encapsulates the title variants and image(s) for a single voice control
 state, like listening, loading, or recognized.

 Your app may initialize the voice control template with one or more states, and
 you may call @c activateVoiceControlState: to switch between states you've defined.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPVoiceControlState : NSObject <NSSecureCoding>

/**
 Initialize a voice control state with a title and image.

 @param identifier A custom identifier you can use to identify this voice control state. You'll also
 switch to this state by specifying this identifier.
 @param titleVariants An array of title variants. The Voice Control template will select the longest
 variant that fits your specified content.
 @param image An image to be animated while this template is visible. The system
 enforces a minimum cycle duration of 0.3 seconds and a maximum cycle duration of 5 seconds.
 Voice Control state images may be a maximum of 150 by 150 points.
 @param repeats For an animated image, YES if the animation should repeat indefinitely, NO
 to run the animation only once.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                     titleVariants:(nullable NSArray <NSString *> *)titleVariants
                             image:(nullable UIImage *)image
                           repeats:(BOOL)repeats;

/**
 Initialize a voice control state with a title and image.

 @param identifier A custom identifier you can use to identify this voice control state. You'll also
 switch to this state by specifying this identifier.
 @param titleVariants An array of title variants. The Voice Control template will select the longest
 variant that fits your specified content.
 @param image An image to be animated while this template is visible. The system
 enforces a minimum cycle duration of 0.3 seconds and a maximum cycle duration of 5 seconds.
 Voice Control state images may be a maximum of 150 by 150 points.
 @param backgroundImage A custom background image to be displayed behind the voice control template content.
 The background image fills the entire template view and appears behind all voice control
 state content, including the state image, title variants, and action buttons.
 @param repeats For an animated image, YES if the animation should repeat indefinitely, NO
 to run the animation only once.

 @discussion When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide light and dark styles by using an asset from your asset catalog, prepared with light and dark styles or by using @c UIImageAsset to combine two @c UIImage instances into a single image with both styles.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                     titleVariants:(nullable NSArray <NSString *> *)titleVariants
                             image:(nullable UIImage *)image
                   backgroundImage:(nullable UIImage *)backgroundImage
                           repeats:(BOOL)repeats API_AVAILABLE(ios(27.0));

@property (nullable, nonatomic, readonly, copy) NSArray <NSString *> *titleVariants;

@property (nullable, nonatomic, readonly, strong) UIImage *image;

@property (nonatomic, readonly, copy) NSString *identifier;

@property (nonatomic, readonly) BOOL repeats;

/**
 * An array of action buttons displayed in the template.
 *
 * These buttons provide user interaction capabilities such as play/pause,
 * favorite/unfavorite, share, or other content-specific actions. The buttons
 * are displayed horizontally and are limited by maximumActionButtonCount.
 *
 * @discussion Buttons should have clear, concise titles or recognizable icons.
 *             The order of buttons in the array determines their display order
 *             from leading to trailing in the interface.
 */
@property (nonatomic, copy) NSArray <CPButton *> *actionButtons API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos);

/**
 * The maximum number of action buttons that can be displayed in the CPVoiceControlTemplate.
 *
 * This class property defines the upper limit for action buttons to ensure
 * proper layout and usability within the CarPlay interface constraints.
 * Any buttons beyond this limit in the actionButtons array will be ignored.
 *
 * @return The maximum number of action buttons supported by this template.
 */
@property (nonatomic, readonly, class) NSInteger maximumActionButtonCount API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos);

/**
 A custom background image to be displayed behind the voice control template content.

 The background image fills the entire template view and appears behind all voice control
 state content, including the state image, title variants, and action buttons.
 */
@property (nullable, nonatomic, readonly, strong) UIImage *backgroundImage API_AVAILABLE(ios(27.0));

@end

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR

#if __IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_26_4
@interface CPVoiceControlTemplate : CPTemplate <CPBarButtonProviding>
#else
@interface CPVoiceControlTemplate : CPTemplate
#endif


/**
 Initialize a voice control template with a list of voice control states.

 @param voiceControlStates An array of voice control states for this template. Your app can switch between these states after the template is presented.

 @note By default, the Voice Control template will begin on the first state specified.

 @warning You may specify a maximum of 5 voice control states. If you specify more than 5, only the first 5 will be available.
 */
- (instancetype)initWithVoiceControlStates:(NSArray <CPVoiceControlState *> *)voiceControlStates;

@property (nonatomic, readonly, copy) NSArray <CPVoiceControlState *> *voiceControlStates;

/**
 Switch the voice control template to the state corresponding with a particular identifier.

 @param identifier An identifier corresponding to one of the voice control states used to initialize this template.

 @note The Voice Control template applies a rate-limit for voice control states; the template will
 ignore voice control state changes that occur too rapidly or frequently in a short period of time.

 @warning You must first present this voice control template through your @c CPInterfaceController before
 activating a voice control state, otherwise this method will have no effect.
 When the Voice Control template is first presented, the first state you specify in
 @c initWithVoiceControlStates: will be visible.
 */
- (void)activateVoiceControlStateWithIdentifier:(NSString *)identifier;

/**
 The currently-active voice control state identifier.
 */
@property (nonatomic, readonly, copy, nullable) NSString *activeStateIdentifier;

/**
 An array of bar buttons to be displayed on the leading side of the navigation bar.

 @note The navigation bar may display a maximum of 2 buttons in the leading space.
 Setting more than 2 buttons to this property will only display the first 2 buttons.
 */
@property (nonatomic, strong) NSArray<CPBarButton *> *leadingNavigationBarButtons API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos, visionos);

/**
 An array of bar buttons to be displayed on the trailing side of the navigation bar.

 @note The navigation bar may display a maximum of 2 buttons in the trailing space.
 Setting more than 2 buttons to this property will only display the first 2 buttons.
 */
@property (nonatomic, strong) NSArray<CPBarButton *> *trailingNavigationBarButtons API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos, visionos);

@property (nonatomic, strong, nullable) CPBarButton *backButton API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos, visionos);

@end

NS_ASSUME_NONNULL_END
