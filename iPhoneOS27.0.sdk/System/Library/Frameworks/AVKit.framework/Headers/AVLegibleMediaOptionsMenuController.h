/*
	File:  AVLegibleMediaOptionsMenuController.h
	
	Framework:  AVKit
	
	Copyright © 2025 Apple Inc. All rights reserved.
	
 */

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

#if TARGET_OS_OSX && !TARGET_OS_MACCATALYST
#import <AppKit/AppKit.h>
#import <AVKitCore/AVKitDefines.h>
#else
#import <AVKit/AVKitDefines.h>
#import <UIKit/UIKit.h>
#endif // TARGET_OS_OSX && !TARGET_OS_MACCATALYST


NS_ASSUME_NONNULL_BEGIN


// MARK: - Enums (API)

/*!
	@enum		AVLegibleMediaOptionsMenuStateChangeReason
				An enum set, describing the different reasons for changing the menu state.
	@constant	AVLegibleMediaOptionsMenuStateChangeReasonNone
				Describes a non specified menu state change reason.
	@constant 	AVLegibleMediaOptionsMenuStateChangeReasonLanguageMismatch
				Describes a menu state change reason due language mismatch.
 */
typedef NS_ENUM(NSInteger, AVLegibleMediaOptionsMenuStateChangeReason) {
	 AVLegibleMediaOptionsMenuStateChangeReasonNone,
	 AVLegibleMediaOptionsMenuStateChangeReasonLanguageMismatch,
} API_AVAILABLE(ios(26.4), macos(26.4), visionos(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(AVLegibleMediaOptionsMenuController.StateChangeReason);

/*!
	@struct		AVLegibleMediaOptionsMenuState
	@abstract 	A struct describing the state of the legible options menu.
 */
NS_SWIFT_NAME(AVLegibleMediaOptionsMenuController.MenuState)
API_AVAILABLE(ios(26.4), macos(26.4), visionos(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
typedef struct AVLegibleMediaOptionsMenuState {
	
	/// Whether or not the legible options menu is
	BOOL enabled;
	
	/// The reason for changing the menu state
	AVLegibleMediaOptionsMenuStateChangeReason reason;
} AVLegibleMediaOptionsMenuState;

/*!
	@enum		AVLegibleMediaOptionsMenuContents
				An option set, describing the different contents of legible option menus.
	@constant	AVLegibleMediaOptionsMenuContentsLegible
				Describes the legible contents of a legible options menu
	@constant 	AVLegibleMediaOptionsMenuContentsCaptionAppearance
				Describes the caption appearance contents of a legible options menu.
	@constant	AVLegibleMediaOptionsMenuContentsAll
				Describes all the contents of a legible options menu.
 */
typedef NS_OPTIONS(NSInteger, AVLegibleMediaOptionsMenuContents) {
	AVLegibleMediaOptionsMenuContentsLegible = 1 << 0,
	AVLegibleMediaOptionsMenuContentsCaptionAppearance = 1 << 1,
	AVLegibleMediaOptionsMenuContentsAll = (AVLegibleMediaOptionsMenuContentsLegible | AVLegibleMediaOptionsMenuContentsCaptionAppearance)
} API_AVAILABLE(ios(26.4), macos(26.4), visionos(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(AVLegibleMediaOptionsMenuController.MenuContents);


@protocol AVMediaOptionsControllerDelegate;
@protocol AVLegibleMediaOptionsMenuControllerDelegate;


// MARK: - AVLegibleMediaOptionsMenuController

/*!
	@class			AVLegibleMediaOptionsMenuController
	@abstract		A menu controller for legible media options (subtitles/captions)
	@discussion		Supports both media track selection and caption appearance customization. When initialized without a player, only caption appearance options are available. When initialized with a player, both media tracks and caption appearance are available.
 */
API_AVAILABLE(ios(26.4), macos(26.4), visionos(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(AVLegibleMediaOptionsMenuController)
@interface AVLegibleMediaOptionsMenuController : NSObject

/*!
	@method			init
	@abstract		Creates an AVLegibleMediaOptionsMenuController without a player
	@discussion		When initialized without a player, only non-track-specific options are available (e.g., appearance styles). Media track selection requires initialization with a player.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
	@method			initWithPlayer:
	@param			player
					The AVPlayer to build menus from, or nil for non-track-specific options only
	@abstract		Creates an AVLegibleMediaOptionsMenuController with an optional player
	@discussion		When player is non-nil, both media tracks and caption appearance options will be included, otherwise, only caption appearance options.
 */
- (instancetype)initWithPlayer:(nullable AVPlayer *)player NS_DESIGNATED_INITIALIZER;

#if TARGET_OS_OSX && !TARGET_OS_MACCATALYST
/*!
	@method			menuWithContents:
	@param			contents
					A set of values from the AVLegibleMediaOptionsMenuContents
	@abstract		Builds a legible options menu using the specified contents.
	@return			A NSMenu ready to be presented by the client, or nil if the menu cannot be built
	@discussion		Returns nil if the requested menu type cannot be built due to missing content (e.g., requesting track selection without a player).
 */
- (nullable NSMenu *)menuWithContents:(AVLegibleMediaOptionsMenuContents)contents;
#else
/*!
	@method			menuWithContents:
	@param			contents
					A set of values from the AVLegibleMediaOptionsMenuContents
	@abstract		Builds a legible options menu using the specified contents.
	@return			A UIMenu ready to be presented by the client, or nil if the menu cannot be built
	@discussion		Returns nil if the requested menu type cannot be built due to missing content (e.g., requesting track selection without a player).
 */
- (nullable UIMenu *)menuWithContents:(AVLegibleMediaOptionsMenuContents)contents;
#endif // TARGET_OS_OSX && !TARGET_OS_MACCATALYST

/*!
	@property		player
	@abstract		The player associated with the menu controller.
 */
@property (nonatomic, readwrite) AVPlayer *player;

/**
	@property		delegate
	@abstract		The delegate for receiving caption preview and state change notifications.
 */
@property (nonatomic, weak) id<AVLegibleMediaOptionsMenuControllerDelegate> delegate;


/*!
	@property		menuState
	@abstract		The current of the legible media options menu.
	@discussion		Use this to check the legible options menu state.
 */
@property (nonatomic, readonly) AVLegibleMediaOptionsMenuState menuState;

@end


// MARK: - AVLegibleMediaOptionsMenuControllerDelegate

/*!
	@protocol		AVLegibleMediaOptionsMenuControllerDelegate
	@abstract		Delegate protocol for AVLegibleMediaOptionsMenuController
	@discussion		Provides callbacks for caption preview display and enablement state changes.
*/
API_AVAILABLE(ios(26.4), macos(26.4), visionos(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(AVLegibleMediaOptionsMenuController.Delegate)
@protocol AVLegibleMediaOptionsMenuControllerDelegate <NSObject>
@optional

/*!
	@method			legibleMenuController:didChangeMenuState:
	@param			menuController
					The legible options menu controller.
	@param			state
					The new menu state.
	@abstract		Tells the delegate, when legible media options menu state changes.
 */
- (void)legibleMenuController:(AVLegibleMediaOptionsMenuController *)menuController didChangeMenuState:(AVLegibleMediaOptionsMenuState)state;

/*!
	@method			legibleMenuController:didRequestCaptionPreviewForProfileID:
	@param			menuController
					The legible options menu controller.
	@param			profileID
					MACaptionAppearance profile ID as an NSString for the caption style to preview
	@abstract		Called when a caption preview should be displayed
	@discussion		The client should display a caption preview using the MACaptionAppearance profile ID provided. The client is responsible for rendering and positioning the preview.
 */
- (void)legibleMenuController:(AVLegibleMediaOptionsMenuController *)menuController didRequestCaptionPreviewForProfileID:(NSString *)profileID;


/*!
	@method			legibleMenuControllerDidRequestStoppingSubtitleCaptionPreview:
	@param			menuController
					The legible options menu controller.
	@abstract		Called when the caption preview should be hidden
	@discussion		The client should hide any active caption preview.
 */
- (void)legibleMenuControllerDidRequestStoppingSubtitleCaptionPreview:(AVLegibleMediaOptionsMenuController *)menuController;

@end

NS_ASSUME_NONNULL_END
