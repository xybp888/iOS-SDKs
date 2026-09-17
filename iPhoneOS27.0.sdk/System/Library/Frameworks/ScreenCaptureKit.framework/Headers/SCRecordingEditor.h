//
//  SCRecordingEditor.h
//  ScreenCaptureKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 @typedef SCRecordingEditorMode
 @constant SCRecordingEditorModePreview Preview screen displayed when editing a recording.
 @constant SCRecordingEditorModeShare Share/AirDrop screen displayed when editing a recording.
 */
typedef NS_ENUM(NSInteger, SCRecordingEditorMode) {
    SCRecordingEditorModePreview,  // Preview UI (default)
    SCRecordingEditorModeShare     // Skip to share UI directly
} NS_SWIFT_NAME(SCRecordingEditor.Mode)
    API_AVAILABLE(tvos(27.0)) API_UNAVAILABLE(ios, visionos, macos, macCatalyst);

@class SCRecordingEditor;

API_AVAILABLE(ios(27.0), visionos(27.0), tvos(27.0), macCatalyst(27.0), macos(27.0))
@protocol SCRecordingEditorDelegate <NSObject>
@optional
/*!
 @abstract recordingEditorDidDismiss:
 @discussion Called when the recording editor is dismissed.
 */
- (void)recordingEditorDidDismiss:(SCRecordingEditor *)editor;

/*!
 @abstract recordingEditor:didFailWithError:
 @discussion Called when the recording editor encounters an error.
 */
- (void)recordingEditor:(SCRecordingEditor *)editor didFailWithError:(NSError *)error;
@end

/*!
 @class SCRecordingEditor
 @abstract Presents a system-owned preview UI for a completed recording via SCStream.
 @discussion SCRecordingEditor owns the full presentation lifecycle of the preview UI.
 Callers provide an optional anchor window (macOS) or scene; if none is provided, the foreground
 window/scene is discovered automatically.
 */
API_AVAILABLE(ios(27.0), visionos(27.0), tvos(27.0), macCatalyst(27.0), macos(27.0))
@interface SCRecordingEditor : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @method initWithURL:
 @abstract Initialize an SCRecordingEditor with the file URL of a completed recording.
 @param url The file URL of the completed recording, from SCRecordingOutput or SCClipBufferingOutput.
 @result An initialized SCRecordingEditor.
 */
- (instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

/*!
 @abstract delegate The delegate for the recording preview.
 */
@property (nonatomic, weak, nullable) id<SCRecordingEditorDelegate> delegate;

#if TARGET_OS_OSX

/*!
 @method presentFromWindow:completionHandler:
 @abstract Present the recording editor from the specified window.
 @param window The window to present from.
 @param completionHandler Called when presentation completes. error is nil on success.
 */
- (void)presentFromWindow:(NSWindow *)window
        completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    API_AVAILABLE(macos(27.0));

- (void)presentFromWindow:(NSWindow *)window
                     mode:(SCRecordingEditorMode)mode
        completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    NS_UNAVAILABLE;

#else

/*!
 @method presentFromWindowScene:completionHandler:
 @abstract Present the recording editor from the specified window scene.
 @param windowScene The window scene to present from.
 @param completionHandler Called when presentation completes. error is nil on success.
 */
- (void)presentFromWindowScene:(UIWindowScene *)windowScene
             completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    API_AVAILABLE(ios(27.0), visionos(27.0), macCatalyst(27.0), tvos(27.0));

- (void)presentFromWindowScene:(UIWindowScene *)windowScene
                          mode:(SCRecordingEditorMode)mode
             completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    API_AVAILABLE(tvos(27.0)) API_UNAVAILABLE(macos, ios, visionos);

#endif

@end

NS_ASSUME_NONNULL_END
