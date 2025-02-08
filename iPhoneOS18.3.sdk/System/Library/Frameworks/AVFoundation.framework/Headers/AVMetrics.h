#if !__has_include(<AVFCore/AVMetrics.h>)
/*
 File: AVMetrics.h
 
 Copyright (c) 2024. Apple Inc. All rights reserved.
 */
#ifndef AVMETRICS_H
#define AVMETRICS_H

#import <Foundation/Foundation.h>
#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVContentKeySession.h>
#import <AVFoundation/AVAssetVariant.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMetricEvent;

/*!
 @protocol AVMetricEventStreamPublisher
 @abstract This protocol needs to be implemented by interfaces intending to publish metric events to the event stream.
 */
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@protocol AVMetricEventStreamPublisher
@end

/*!
 @protocol AVMetricEventStreamSubscriber
 @abstract This protocol needs to be implemented by the subscriber delegate to receive subscribed metric events.
 */
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@protocol AVMetricEventStreamSubscriber

/*!
 @method publisher:didReceiveEvent:
 @abstract Delegate callback to receive metric events.
 @param event The metric event.
 @param publisher The publisher which generated the current event.
 */
- (void)publisher:(id<AVMetricEventStreamPublisher>)publisher didReceiveEvent:(AVMetricEvent *)event;
@end

/*!
 @class AVMetricEventStream
 @abstract AVMetricEventStream allows clients to add publishers and then subscribe to specific metric event classes from those publishers. Publishers are AVFoundation instances implementing AVMetricEventStreamPublisher. The interface allows clients to receive metric events via a subscriber delegate which implements AVMetricEventStreamSubscriber.
 */
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricEventStream : NSObject 

AV_INIT_UNAVAILABLE

/*!
 @method eventStream
 @abstract Returns an autoreleased instance.
 */
+ (instancetype)eventStream;

/*!
 @method addPublisher:
 @abstract The publisher should be an AVFoundation instance conforming to AVMetricEventStreamPublisher.
 */
- (BOOL)addPublisher:(id<AVMetricEventStreamPublisher>)publisher;

/*!
 @method setSubscriber:queue:
 @abstract Set a subscriber delegate.
 @param subscriber A subscriber delegate object conforming to AVMetricEventStreamSubscriber.
 @param queue Dispatch queue for the delegate callbacks.
 */
- (BOOL)setSubscriber:(id<AVMetricEventStreamSubscriber>)subscriber queue:(nullable dispatch_queue_t)queue;

/*!
 @method subscribeToMetricEvent:
 @abstract Subscribe to a specific metric event class.
 @param metricEventClass Type of metric event class to subscribe to.
 */
- (void)subscribeToMetricEvent:(Class)metricEventClass;

/*!
 @method subscribeToMetricEvents:
 @abstract Subscribe to set of metric event classes.
 @param metricEventClasses Set of metric event classes to subscribe to.
 */
- (void)subscribeToMetricEvents:(NSArray<Class> *)metricEventClasses;

/*!
 @method subscribeToAllMetricEvents:
 @abstract Subscribe to all metric event classes.
 */
- (void)subscribeToAllMetricEvents;

@end

#pragma mark - Base class -

/*!
 @class AVMetricEvent
 @abstract An abstract base class representing metric events.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricEvent : NSObject <NSSecureCoding>
AV_INIT_UNAVAILABLE

/*!
 @property date
 @abstract Returns the date when the event occurred.
 */
@property (readonly) NSDate *date;

/*!
 @property mediaTime
 @abstract Returns the time in the media timeline when the event occured.
 */
@property (readonly) CMTime mediaTime;

/*!
 @property sessionID
 @abstract A GUID that identifies the media session. If not available, value is nil.
 */
@property (readonly, nullable) NSString *sessionID;

@end

#pragma mark - Error Event -

/*!
 @class AVMetricErrorEvent
 @abstract Represents a metric event when an error occurred.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricErrorEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/*!
 @property didRecover
 @abstract Returns whether the error was recoverable.
 */
@property (readonly) BOOL didRecover;

/*!
 @property error
 @abstract Returns the error encountered.
 */
@property (readonly) NSError *error;
@end

#pragma mark - Resource Request Event -

/*!
 @class AVMetricMediaResourceRequestEvent
 @abstract Represents a metric event associated with media resource requests.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricMediaResourceRequestEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/*!
 @property url
 @abstract Returns the URL of the resource request. If no value is available, returns nil.
 */
@property (readonly, nullable) NSURL *url;

/*!
 @property serverAddress
 @abstract The IP address of the server. If not available, the value is nil. 
 */
@property (readonly, nullable) NSString *serverAddress;

/*!
 @property requestStartTime
 @abstract Returns the start time of the resource request.
 */
@property (readonly) NSDate *requestStartTime;

/*!
 @property requestEndTime
 @abstract Returns the end time of the resource request.
 */
@property (readonly) NSDate *requestEndTime;

/*!
 @property responseStartTime
 @abstract Returns the start time of the resource request response.
 */
@property (readonly) NSDate *responseStartTime;

/*!
 @property responseEndTime
 @abstract Returns the end time of the resource request response.
 */
@property (readonly) NSDate *responseEndTime;

/*!
 @property byteRange
 @abstract Returns the byte range downloaded for the resource request. If not available, the range start and end will be 0.
 */
@property (readonly) NSRange byteRange;

/*!
 @property readFromCache
 @abstract Returns true if the resource was read from the cache.
 */
@property (readonly, getter=wasReadFromCache) BOOL readFromCache;

/*!
 @property errorEvent
 @abstract Returns the error event, if any, encountered during the resource request. If no value is present, returns nil.
 */
@property (readonly, nullable) AVMetricErrorEvent *errorEvent;

/*!
 @property networkTransactionMetrics
 @abstract Returns the NSURLSessionTaskMetrics associated with the resource request. If no value is present, returns nil
 */
@property (readonly, nullable) NSURLSessionTaskMetrics *networkTransactionMetrics;
@end

/*!
 @class AVMetricHLSPlaylistRequestEvent
 @abstract Represents a metric event associated with a HLS playlist resource request.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricHLSPlaylistRequestEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/*!
 @property url
 @abstract Returns the URL of the playlist. If no value is available, returns nil.
 */
@property (readonly, nullable) NSURL *url;

/*!
 @property isMultivariantPlaylist
 @abstract Returns true if the playlist request is for a multivariant playlist.
 */
@property (readonly) BOOL isMultivariantPlaylist;

/*!
 @property mediaType
 @abstract Returns the media type.  If the value cannot be determined, returns AVMediaTypeMuxed.
 */
@property (readonly) AVMediaType mediaType;

/*!
 @property mediaResourceRequestEvent
 @abstract Returns the media resource request event which was used to satisfy the playlist.
 */
@property (readonly, nullable) AVMetricMediaResourceRequestEvent *mediaResourceRequestEvent;
@end

/*!
 @class AVMetricHLSMediaSegmentRequestEvent
 @abstract Represents a metric event associated with a HLS media segment resource request.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricHLSMediaSegmentRequestEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/*!
 @property url
 @abstract Returns the URL of the media segment. If no value is available, returns nil.
 */
@property (readonly, nullable) NSURL *url;

/*!
 @property isMapSegment
 @abstract Returns true if the media segment request is for a map segment.
 */
@property (readonly) BOOL isMapSegment;

/*!
 @property mediaType
 @abstract Returns the media type.  If the value cannot be determined, returns AVMediaTypeMuxed.
 */
@property (readonly) AVMediaType mediaType;

/*!
 @property byteRange
 @abstract Returns the byte range for the media segment. If not available, the range start and end will be 0.
 */
@property (readonly) NSRange byteRange;

/*!
 @property indexFileURL
 @abstract Returns the URL of the index file in which this segment was declared. If not available, returns nil.
 */
@property (readonly) NSURL *indexFileURL;

/*!
 @property mediaResourceRequestEvent
 @abstract Returns the media resource request event which was used to satisfy the media segment.
 */
@property (readonly, nullable) AVMetricMediaResourceRequestEvent *mediaResourceRequestEvent;
@end

/*!
 @class AVMetricContentKeyRequestEvent
 @abstract Represents a metric event associated with a HLS content key resource request.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricContentKeyRequestEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/*!
 @property contentKeySpecifier
 @abstract Returns the content key specifier for the request.
 */
@property (readonly) AVContentKeySpecifier *contentKeySpecifier;

/*!
 @property mediaType
 @abstract Returns the media type.  If the value cannot be determined, returns AVMediaTypeMuxed.
 */
@property (readonly) AVMediaType mediaType;

/*!
 @property isClientInitiated
 @abstract Returns whether the content key resource request was initiated by the client.
 */
@property (readonly) BOOL isClientInitiated;

/*!
 @property mediaResourceRequestEvent
 @abstract Returns the media resource request event which was used to satisfy the content key.
 */
@property (readonly, nullable) AVMetricMediaResourceRequestEvent *mediaResourceRequestEvent;
@end

#pragma mark - Likely To Keep Up Events -

/*!
 @class AVMetricPlayerItemLikelyToKeepUpEvent
 @abstract Represents a metric event when playback was likely to play through without stalling.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemLikelyToKeepUpEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/*!
 @property variant
 @abstract Returns the variant selected at the time likely to keep up is achieved. If no value is present, returns nil.
 */
@property (readonly, nullable) AVAssetVariant *variant;

/*!
 @property timeTaken
 @abstract Returns the total time taken to reach likely to keep up.
 */
@property (readonly) NSTimeInterval timeTaken;

/*!
 @property loadedTimeRanges
 @abstract This property provides a collection of time ranges for which the player has the media data readily available. The ranges provided might be discontinuous.
 @discussion Returns an NSArray of NSValues containing CMTimeRanges.
 */
@property (readonly) NSArray<NSValue *> *loadedTimeRanges NS_REFINED_FOR_SWIFT;

@end

/*!
 @class AVMetricPlayerItemInitialLikelyToKeepUpEvent
 @abstract Represents a metric event when playback was first likely to play through without stalling.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemInitialLikelyToKeepUpEvent : AVMetricPlayerItemLikelyToKeepUpEvent
AV_INIT_UNAVAILABLE

/*!
 @property playlistRequestEvents
 @abstract Returns the playlist request events required to reach likely to keep up.
 */
@property (readonly) NSArray <AVMetricHLSPlaylistRequestEvent *> *playlistRequestEvents;

/*!
 @property mediaSegmentRequestEvents
 @abstract Returns the media segment request events required to reach likely to keep up.
 */
@property (readonly) NSArray <AVMetricHLSMediaSegmentRequestEvent *> *mediaSegmentRequestEvents;

/*!
 @property contentKeyRequestEvents
 @abstract Returns the content key request required to reach likely to keep up.
 */
@property (readonly) NSArray <AVMetricContentKeyRequestEvent *> *contentKeyRequestEvents;

@end

#pragma mark - Rate Change Events -

/*!
 @class AVMetricPlayerItemRateChangeEvent
 @abstract Represents a metric event when playback rate change occurred.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemRateChangeEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/*!
 @property rate
 @abstract Returns the playback rate after the rate change event.
 */
@property (readonly) double rate;

/*!
 @property previousRate
 @abstract Returns the playback rate before the rate change event.
 */
@property (readonly) double previousRate;

/*!
 @property variant
 @abstract Returns the variant being played at the time of rate change. If no value is present, returns nil.
 */
@property (readonly, nullable) AVAssetVariant *variant;

@end

/*!
 @class AVMetricPlayerItemStallEvent
 @abstract Represents a metric event when playback stalled.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemStallEvent : AVMetricPlayerItemRateChangeEvent
AV_INIT_UNAVAILABLE

@end

/*!
 @class AVMetricPlayerItemSeekEvent
 @abstract Represents a metric event when playback seeked.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemSeekEvent : AVMetricPlayerItemRateChangeEvent
AV_INIT_UNAVAILABLE

@end

/*!
 @class AVMetricPlayerItemSeekDidCompleteEvent
 @abstract Represents a metric event when playback seek completed.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemSeekDidCompleteEvent : AVMetricPlayerItemRateChangeEvent
AV_INIT_UNAVAILABLE

/*!
 @property didSeekInBuffer
 @abstract Returns whether the seek was performed within the available buffer.
 */
@property (readonly) BOOL didSeekInBuffer;

@end

#pragma mark - Variant Change Event -

/*!
 @class AVMetricPlayerItemVariantSwitchEvent
 @abstract Represents a metric event when variant switch was completed.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemVariantSwitchEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/*!
 @property fromVariant
 @abstract Returns the variant before the switch. If no value is available, returns nil
 */
@property (readonly, nullable) AVAssetVariant *fromVariant;

/*!
 @property toVariant
 @abstract Returns the variant after the switch.
 */
@property (readonly) AVAssetVariant *toVariant;

/*!
 @property loadedTimeRanges
 @abstract This property provides a collection of time ranges for which the player has the media data readily available. The ranges provided might be discontinuous.
 @discussion Returns an NSArray of NSValues containing CMTimeRanges.
 */
@property (readonly) NSArray<NSValue *> *loadedTimeRanges NS_REFINED_FOR_SWIFT;

/*!
 @property didSucceed
 @abstract Returns if the switch did succeed.
 */
@property (readonly) BOOL didSucceed;
@end

#pragma mark - Variant Switch Start Event -

/*!
 @class AVMetricPlayerItemVariantSwitchStartEvent
 @abstract Represents a metric event when variant switch was attempted.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemVariantSwitchStartEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/*!
 @property fromVariant
 @abstract Returns the variant from which the switch is attempted. If no value is available, returns nil
 */
@property (readonly, nullable) AVAssetVariant *fromVariant;

/*!
 @property toVariant
 @abstract Returns the variant to which the switch is attempted.
 */
@property (readonly) AVAssetVariant *toVariant;

/*!
 @property loadedTimeRanges
 @abstract This property provides a collection of time ranges for which the player has the media data readily available. The ranges provided might be discontinuous.
 @discussion Returns an NSArray of NSValues containing CMTimeRanges.
 */
@property (readonly) NSArray<NSValue *> *loadedTimeRanges NS_REFINED_FOR_SWIFT;
@end

#pragma mark - Summary Event -

/*!
 @class AVMetricPlayerItemPlaybackSummaryEvent
 @abstract Represents a summary metric event with aggregated metrics for the entire playback session.
 @discussion Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15), ios(18), tvos(18), watchos(11), visionos(2))
@interface AVMetricPlayerItemPlaybackSummaryEvent : AVMetricEvent
AV_INIT_UNAVAILABLE

/*!
 @property errorEvent
 @abstract Returns the error event if any. If no value is available, returns nil.
 */
@property (readonly, nullable) AVMetricErrorEvent *errorEvent;

/*!
 @property recoverableErrorCount
 @abstract Returns the total count of recoverable errors encountered during playback. If no errors were encountered, returns 0.
 */
@property (readonly) NSInteger recoverableErrorCount;

/*!
 @property stallCount
 @abstract Returns the total count of stalls encountered during playback. If no stalls were encountered, returns 0.
 */
@property (readonly) NSInteger stallCount;

/*!
 @property variantSwitchCount
 @abstract Returns the total count of variant switch encountered during playback.
 */
@property (readonly) NSInteger variantSwitchCount;

/*!
 @property playbackDuration
 @abstract Returns the total duration of playback in seconds.
 */
@property (readonly) NSInteger playbackDuration;

/*!
 @property mediaResourceRequestCount
 @abstract Returns the total number of media requests performed by the player.
 */
@property (readonly) NSInteger mediaResourceRequestCount;

/*!
 @property timeSpentRecoveringFromStall
 @abstract Returns the total time spent recovering from a stall event.
 */
@property (readonly) NSTimeInterval timeSpentRecoveringFromStall;

/*!
 @property timeSpentInInitialStartup
 @abstract Returns the total time spent in initial startup of playback.
 */
@property (readonly) NSTimeInterval timeSpentInInitialStartup;

/*!
 @property timeWeightedAverageBitrate
 @abstract Returns the playtime weighted average bitrate played in bits / second.
 */
@property (readonly) NSInteger timeWeightedAverageBitrate;

/*!
 @property timeWeightedPeakBitrate
 @abstract Returns the playtime weighted peak bitrate played in bits / second.
 */
@property (readonly) NSInteger timeWeightedPeakBitrate;

@end

NS_ASSUME_NONNULL_END

#endif /* AVMETRICS_H */

#else
#import <AVFCore/AVMetrics.h>
#endif
