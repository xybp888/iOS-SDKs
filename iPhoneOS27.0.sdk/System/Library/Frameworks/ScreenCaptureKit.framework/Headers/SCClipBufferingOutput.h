//
//  SCClipBufferingOutput.h
//  ScreenCaptureKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef SCClipBufferingOutput_h
#define SCClipBufferingOutput_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCClipBufferingOutput;

/*!
 @protocol SCClipBufferingOutputDelegate
 @abstract
    Defines an interface for delegates of SCClipBufferingOutput to respond to events that occur during clip buffering.
 */
API_AVAILABLE(macos(27.0), macCatalyst(27.0), ios(27.0), visionos(27.0), tvos(27.0))
@protocol SCClipBufferingOutputDelegate <NSObject>

@optional
/*!
 @abstract clipBufferingOutputDidStartBuffering:
 @param clipBufferingOutput the SCClipBufferingOutput object
 @discussion Notifies the delegate that clip buffering has successfully started.
*/
- (void)clipBufferingOutputDidStartBuffering:(SCClipBufferingOutput *)clipBufferingOutput;

/*!
 @abstract clipBufferingOutput:didFailWithError:
 @param clipBufferingOutput the SCClipBufferingOutput object
 @param error error describing why clip buffering failed
 @discussion Notifies the delegate that clip buffering has failed with an associated error.
*/
- (void)clipBufferingOutput:(SCClipBufferingOutput *)clipBufferingOutput didFailWithError:(NSError *)error;

/*!
 @abstract clipBufferingOutputDidStopBuffering:
 @param clipBufferingOutput the SCClipBufferingOutput object
 @discussion Notifies the delegate that clip buffering has finished successfully.
*/
- (void)clipBufferingOutputDidStopBuffering:(SCClipBufferingOutput *)clipBufferingOutput;

@end

/*!
 @abstract SCClipBufferingOutput
 @discussion SCClipBufferingOutput represents a clip buffering session on a SCStream.
*/
API_AVAILABLE(macos(27.0), macCatalyst(27.0), ios(27.0), visionos(27.0), tvos(27.0))
@interface SCClipBufferingOutput : NSObject

/*!
 @method initWithDelegate:
 @abstract Initialize SCClipBufferingOutput object with SCClipBufferingOutputDelegate
 @param delegate object conforming to SCClipBufferingOutputDelegate protocol. Clients may specify a delegate to receive notifications about clip buffering events.
 @discussion Client can create a SCClipBufferingOutput with this initializer and add it to SCStream to start clip buffering.
*/
- (instancetype)initWithDelegate:(nullable id<SCClipBufferingOutputDelegate>)delegate;

/*!
 @method exportClipToURL:duration:completionHandler:
 @abstract Export buffered content as a clip to the specified URL
 @param url URL containing absolute path for where to save the clip. Must be a file URL. The file will be created; if it already exists, it will be overwritten.
 @param duration Length of time in seconds for clip export. The clip will contain the most recent samples from the buffer for this duration. Maximum duration is 15 seconds. If the requested duration exceeds available buffered content, the clip will contain all available buffered content.
 @param completionHandler handler called after clip export completes or fails. Will be passed an optional NSError in the SCStreamErrorDomain domain if there was an issue exporting the clip.
 @discussion This method exports the most recent buffered samples as a video file. The export happens asynchronously and does not interrupt ongoing buffering - new samples continue to be buffered during export. The clip buffering output must be added to a stream before exports can be requested.
*/
- (void)exportClipToURL:(NSURL *)url duration:(NSTimeInterval)duration completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif /* SCClipBufferingOutput_h */
