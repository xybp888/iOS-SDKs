//
//  SCContentSharingPicker.h
//  ScreenCaptureKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ScreenCaptureKit/ScreenCaptureKit.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @typedef SCContentSharingPickerMode
 @abstract SCContentSharingPickerModeSingleWindow picker mode for single window selection
 @constant SCContentSharingPickerModeMultipleWindows picker mode for multiple window selection
 @constant SCContentSharingPickerModeSingleApplication picker mode for application selection
 @constant SCContentSharingPickerModeSingleDisplay picker mode for full display selection
*/
typedef NS_OPTIONS(NSUInteger, SCContentSharingPickerMode) {
    SCContentSharingPickerModeSingleWindow          = 1 << 0,
    SCContentSharingPickerModeMultipleWindows       = 1 << 1,
    SCContentSharingPickerModeSingleApplication     = 1 << 2,
    SCContentSharingPickerModeMultipleApplications  = 1 << 3,
    SCContentSharingPickerModeSingleDisplay         = 1 << 4
} API_AVAILABLE(macos(14.0), macCatalyst(18.2)) API_UNAVAILABLE(ios, visionos, tvos);

@protocol SCContentSharingPickerObserver;

/*!
 @abstract SCContentSharingPickerConfiguration
 @discussion SCContentSharingPickerConfiguration is an object which can optionally be set on the SCContentSharingPicker for customized configuration.
*/
API_AVAILABLE(macos(14.0), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0))
NS_REFINED_FOR_SWIFT
@interface SCContentSharingPickerConfiguration <NSCopying>: NSObject
/*!
 @abstract allowedPickerModes Limits the type of selections available to the user when the picker is presented. Default is 0, no excluded picking modes
 */
@property (nonatomic, assign) SCContentSharingPickerMode allowedPickerModes API_AVAILABLE(macos(14.0), macCatalyst(18.2)) API_UNAVAILABLE(ios, visionos, tvos);

/*!
 @abstract excludedWindowIDs Excludes CGWindowIDs for picking
 */
@property (nonatomic, strong) NSArray<NSNumber *> *excludedWindowIDs API_AVAILABLE(macos(14.0), macCatalyst(18.2)) API_UNAVAILABLE(ios, visionos, tvos);

/*!
 @abstract excludedBundleIDs Excludes bundle IDs for picking
 */
@property (nonatomic, strong) NSArray<NSString *> *excludedBundleIDs API_AVAILABLE(macos(14.0), macCatalyst(18.2)) API_UNAVAILABLE(ios, visionos, tvos);

/*!
 @abstract allowsChangingSelectedContent Controls if the user can make updates to the content filter after the initial selection. Defaults is YES.
 */
@property (nonatomic, assign) BOOL allowsChangingSelectedContent API_AVAILABLE(macos(14.0), macCatalyst(18.2)) API_UNAVAILABLE(ios, visionos, tvos);

/*!
 @abstract showsMicrophoneControl Indicates whether the system picker view will show microphone control for user. Default is NO.
 */
@property (nonatomic, assign) BOOL showsMicrophoneControl API_AVAILABLE(ios(27.0), visionos(27.0)) API_UNAVAILABLE(macos, macCatalyst, tvos);

/*!
 @abstract showsCameraControl Indicates whether the system picker will show camera control for user. Default is NO. Only applies when presenting the picker for the current application
 */
@property (nonatomic, assign) BOOL showsCameraControl API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos);

@end

/*!
 @abstract SCContentSharingPicker
 @discussion SCContentSharingPicker is an object created by client applications to opt-in to Control Center's content picker
*/
API_AVAILABLE(macos(14.0), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0))
@interface SCContentSharingPicker : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @abstract sharedPicker the singleton shared picker for the application
 */
@property (class, readonly) SCContentSharingPicker *sharedPicker;

/*!
 @abstract defaultConfiguration for the content sharing picker. If a stream does not have a configuration, the default configuration will be used.
 */
@property (nonatomic, copy) SCContentSharingPickerConfiguration *defaultConfiguration NS_REFINED_FOR_SWIFT;

/*!
 @abstract maximumStreamCount An integer value that, if set, limits when Control Center will show the UI to present a picker with no associated stream. If set to 0, Control Center will never ever show UI to present a picker without an associated stream.
 */
@property (nonatomic, nullable, strong) NSNumber *maximumStreamCount API_AVAILABLE(macos(14.0), macCatalyst(18.2)) API_UNAVAILABLE(ios, visionos, tvos) NS_REFINED_FOR_SWIFT;

/*!
 @abstract active A picker needs to be marked as active to enable user interaction with system UI (displayed picker, video menu bar, directly from a window). If the picker is not marked as active, when present is called, the displayed picker UI will not appear, and user will not be able to share content from system UI to your application.
 */
@property (nonatomic, assign, getter=isActive) BOOL active;

/*!
 @abstract available Indicates whether screen recording is available on this device.
 @discussion Returns YES if screen recording is supported and allowed on this device.
 */
@property (nonatomic, readonly, getter=isAvailable) BOOL available API_AVAILABLE(macos(27.0), macCatalyst(27.0), ios(27.0), visionos(27.0), tvos(27.0));

/*!
 @abstract addObserver:
 @param observer the observer object that adheres to SCContentSharingPickerObserver protocol
 @discussion Adds an observer object that will receive the results of user interaction with a displayed picker
*/
- (void)addObserver:(id<SCContentSharingPickerObserver>)observer;

/*!
 @abstract removeObserver:
 @param observer the observer object that adheres to SCContentSharingPickerObserver protocol
 @discussion Removes an observer object that will receive the results of user interaction with a displayed picker
*/
- (void)removeObserver:(id<SCContentSharingPickerObserver>)observer;

/*!
 @abstract setConfiguration:forStream:
 @param pickerConfig configuration for the picker
 @param stream stream for optional picking configuration
 @discussion Sets optional configuration for the picker for a specific stream. If this is not set, the stream will use the defaultConfiguration instead
*/
- (void)setConfiguration:(nullable SCContentSharingPickerConfiguration *)pickerConfig forStream:(SCStream *)stream NS_REFINED_FOR_SWIFT;

/*!
 @abstract present
 @discussion show content sharing picker to get content for updating a new stream
*/
- (void)present API_AVAILABLE(macos(14.0), macCatalyst(18.2), ios(27.0), visionos(27.0)) API_UNAVAILABLE(tvos);

/*!
 @abstract presentPickerUsingContentStyle:
 @param contentStyle the mode in which picking should start
 @discussion Takes a person straight into picking particular windows or displays
*/
- (void)presentPickerUsingContentStyle:(SCShareableContentStyle)contentStyle API_AVAILABLE(macos(14.0), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0));

/*!
 @abstract presentPickerForStream:
 @param stream the stream to update
 @discussion show content sharing picker with an existing stream
*/
- (void)presentPickerForStream:(SCStream *)stream API_AVAILABLE(macos(14.0), macCatalyst(18.2)) API_UNAVAILABLE(ios, visionos, tvos);

/*!
 @abstract presentPickerForStream:usingContentStyle:
 @param stream the stream that the picker will display
 @param contentStyle the mode in which picking should start
 @discussion Takes a person straight into picking particular windows or displays
*/
- (void)presentPickerForStream:(SCStream *)stream usingContentStyle:(SCShareableContentStyle)contentStyle API_AVAILABLE(macos(14.0), macCatalyst(18.2)) API_UNAVAILABLE(ios, visionos, tvos);

/*!
 @abstract presentPickerForCurrentApplication
 @discussion Shows the content sharing picker for capturing the current application only.
*/
- (void)presentPickerForCurrentApplication API_AVAILABLE(ios(27.0), visionos(27.0), tvos(27.0)) API_UNAVAILABLE(macos, macCatalyst);
@end

/*!
 @abstract SCContentSharingPickerObserver
 @discussion SCContentSharingPickerObserver the protocol that is used to inform client when the picker did make selection or cancel
*/
API_AVAILABLE(macos(14.0), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0))
@protocol SCContentSharingPickerObserver <NSObject>
/*!
 @abstract contentSharingPicker:didCancelforStream:
 @param picker the SCContentSharingPicker object
 @param stream the optional associated stream for this picker
 @discussion the observer callback method when the picker has been canceled with no selection.
*/
- (void)contentSharingPicker:(SCContentSharingPicker *)picker didCancelForStream:(nullable SCStream *)stream;

/*!
 @abstract contentSharingPicker:didUpdateWithFilter:forStream:
 @param picker the SCContentSharingPicker object
 @param filter the updated filter
 @param stream the updated stream
 @discussion the observer callback method when the user has finished updating content for a stream
*/
- (void)contentSharingPicker:(SCContentSharingPicker *)picker didUpdateWithFilter:(SCContentFilter *)filter forStream:(nullable SCStream *)stream;

/*!
 @abstract contentSharingPickerStartDidFailWithError:
 @param error the error denoted for the failure to start picker
 @discussion the observer callback method when the picker was asked to start but failed to do so.
*/
- (void)contentSharingPickerStartDidFailWithError:(NSError *)error;
@end

NS_ASSUME_NONNULL_END
