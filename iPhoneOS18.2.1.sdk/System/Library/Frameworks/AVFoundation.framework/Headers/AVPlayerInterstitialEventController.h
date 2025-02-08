#if !__has_include(<AVFCore/AVPlayerInterstitialEventController.h>)
/*
	File:  AVPlayerInterstitialEventController.h

	Framework:  AVFoundation
 
   Copyright:  2020-2024 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <AVFoundation/AVPlayer.h>
#import <AVFoundation/AVPlayerItem.h>

NS_ASSUME_NONNULL_BEGIN

/*!
  @enum         AVPlayerInterstitialEventRestrictions
  @abstract     These constants can be specified when creating AVPlayerInterstitialEvents in order to configure their behavior.
 
  @constant     AVPlayerInterstitialEventRestrictionNone
	Indicates that the user may freely employ playback controls, as available, both within the primary content and in the interstitial content specified for the event.
  @constant     AVPlayerInterstitialEventRestrictionConstrainsSeekingForwardInPrimaryContent
	Indicates that seeking within the primary content from a date prior to the date of the event to a date subsequent to the date of the event is not permitted.
  @constant     AVPlayerInterstitialEventRestrictionRequiresPlaybackAtPreferredRateForAdvancement
	Indicates that advancing the currentTime within an interstitial item, either by seeking ahead or by setting the playback rate to a value greater than the item's asset's preferredRate, is not permitted.
*/
typedef NS_OPTIONS(NSUInteger, AVPlayerInterstitialEventRestrictions) {
	AVPlayerInterstitialEventRestrictionNone = 0UL,
	AVPlayerInterstitialEventRestrictionConstrainsSeekingForwardInPrimaryContent = (1UL << 0),
	AVPlayerInterstitialEventRestrictionRequiresPlaybackAtPreferredRateForAdvancement = (1UL << 2),
	
	AVPlayerInterstitialEventRestrictionDefaultPolicy = AVPlayerInterstitialEventRestrictionNone
} NS_SWIFT_NAME(AVPlayerInterstitialEvent.Restrictions) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
  @enum         AVPlayerInterstitialEventCue
  @abstract     A particular cue can be specified when creating AVPlayerInterstitialEvents to override the start time/date to a predefined position.
 
  @constant     AVPlayerInterstitialEventNoCue
	No cue specified; event playback should start at event time (or date).
  @constant     AVPlayerInterstitialEventJoinCue
	Event playback should occur before starting primary playback, regardless of initial primary playback position.
  @constant     AVPlayerInterstitialEventLeaveCue
	Event playback should occur after primary playback ends without error, either at the end of the primary asset or at the client-specified forward playback end time.
*/
typedef NSString * AVPlayerInterstitialEventCue NS_TYPED_ENUM NS_SWIFT_NAME(AVPlayerInterstitialEvent.Cue) API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
AVF_EXPORT AVPlayerInterstitialEventCue const AVPlayerInterstitialEventNoCue                                   API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
AVF_EXPORT AVPlayerInterstitialEventCue const AVPlayerInterstitialEventJoinCue                                 API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
AVF_EXPORT AVPlayerInterstitialEventCue const AVPlayerInterstitialEventLeaveCue                                API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/*!
  @enum         AVPlayerInterstitialEventTimelineOccupancy
  @abstract     These constants specify how an event occupies time on AVPlayerItemIntegratedTimeline.

  @constant     AVPlayerInterstitialEventTimelineOccupancySinglePoint
	Indicates this interstitial event occupies a single point on AVPlayerItemIntegratedTimeline.
  @constant     AVPlayerInterstitialEventTimelineOccupancyFill
	Indicates this interstitial event fills AVPlayerItemIntegratedTimeline with the duration of this event.
*/
typedef NS_ENUM(NSInteger, AVPlayerInterstitialEventTimelineOccupancy) {
	AVPlayerInterstitialEventTimelineOccupancySinglePoint = 0,
	AVPlayerInterstitialEventTimelineOccupancyFill = 1,
} NS_SWIFT_NAME(AVPlayerInterstitialEvent.TimelineOccupancy) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/*!
  @class        AVPlayerInterstitialEvent

  @abstract
    An AVPlayerInterstitialEvent provides instructions for temporarily suspending the playback of primary content in order to play alternative interstitial content instead, resuming playback of the primary content when playback of the interstitial content is complete or is canceled.
    
  @discussion
    The primary content is specified as an instance of AVPlayerItem, designated as the primary item of the interstitial event.

    The timing of interstitial playback is specified as a date within the date range of the primary item. Interstitial events are currently possible only for items with an intrinsic mapping from their timeline to real-time dates.

    The alternative interstitial content is specified as an array of one or more AVPlayerItems that will be used as templates for the creation of items for interstitial playback. In other words, these template items are not the actual items that will be played during interstitial playback; instead they are used to generate the items that are to be played, with property values that match the configuration of your template items.

    If you wish to observe the scheduling and progress of interstitial events, use an AVPlayerInterstitialEventMonitor. If you wish to specify your own schedule of interstitial events, use an AVPlayerInterstitialEventController.

	Note that while previously AVPlayerInterstitialEvent was an immutable object, it is now mutable. This allows it to be created and customized before being set on an AVPlayerInterstitialEventController.
*/
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVPlayerInterstitialEvent : NSObject <NSCopying>

AV_INIT_UNAVAILABLE
/*!
  @method       interstitialEventWithPrimaryItem:time:templateItems:restrictions:resumptionOffset:
  @abstract     Returns an instance of AVPlayerInterstitialEvent for use in scheduling interstitial playback.
  @param        primaryItem
                An AVPlayerItem representing the primary content during the playback of which the interstitial event should occur. The primaryItem must have an AVAsset that provides an intrinsic mapping from its timeline to real-time dates.
  @param        identifier
                An external identifier for the event.
  @param        time
                The time within the duration of the primary item at which playback of the primary content should be temporarily suspended and the interstitial items played.
  @param        templateItems
                An array of AVPlayerItems with configurations that will be reproduced for the playback of interstitial content. An NSInvalidArgumentException will be raised if any of the template items employs an AVAsset that lacks a URL, such as an AVComposition.
  @param        restrictions
                Indicates restrictions on the use of end user playback controls that are imposed by the event.
  @param        resumptionOffset
                Specifies the offset in time at which playback of the primary item should resume after interstitial playback has finished. Definite numeric values are supported. The value kCMTimeIndefinite can also be used, in order to specify that the effective resumption time offset should accord with the wallclock time elapsed during interstitial playback.
  @param        playoutLimit
                Specifies the offset from the beginning of the interstitial at which interstitial playback should end, if the interstitial asset(s) are longer. Pass a positive numeric value, or kCMTimeInvalid to indicate no playout limit.
  @param        userDefinedAttributes
			    Storage for attributes defined by the client or the content vendor. Attribute names should begin with X- for uniformity with server insertion.
  @result       An instance of AVPlayerInterstitialEvent.
*/
+ (instancetype)interstitialEventWithPrimaryItem:(AVPlayerItem *)primaryItem identifier:(nullable NSString *)identifier time:(CMTime)time templateItems:(NSArray<AVPlayerItem *> *)templateItems restrictions:(AVPlayerInterstitialEventRestrictions)restrictions resumptionOffset:(CMTime)resumptionOffset playoutLimit:(CMTime)playoutLimit userDefinedAttributes:(nullable NSDictionary*)userDefinedAttributes NS_REFINED_FOR_SWIFT API_DEPRECATED("Use interstitialEventWithPrimaryItem:time: instead", macos(12.0, 15.0), ios(15.0, 18.0), tvos(15.0, 18.0), watchos(8.0, 11.0)) API_UNAVAILABLE(visionos);

/*!
  @method       interstitialEventWithPrimaryItem:date:templateItems:restrictions:resumptionOffset:
  @abstract     Returns an instance of AVPlayerInterstitialEvent for use in scheduling interstitial playback.
  @param        primaryItem
                An AVPlayerItem representing the primary content during the playback of which the interstitial event should occur. The primaryItem must have an AVAsset that provides an intrinsic mapping from its timeline to real-time dates.
  @param        identifier
                An external identifier for the event.
  @param        date
                The date within the date range of the primary item at which playback of the primary content should be temporarily suspended and the interstitial items played.
  @param        templateItems
                An array of AVPlayerItems with configurations that will be reproduced for the playback of interstitial content. An NSInvalidArgumentException will be raised if any of the template items employs an AVAsset that lacks a URL, such as an AVComposition.
  @param        restrictions
                Indicates restrictions on the use of end user playback controls that are imposed by the event.
  @param        resumptionOffset
                Specifies the offset in time at which playback of the primary item should resume after interstitial playback has finished. Definite numeric values are supported. The value kCMTimeIndefinite can also be used, in order to specify that the effective resumption time offset should accord with the wallclock time elapsed during interstitial playback.
  @param        playoutLimit
                Specifies the offset from the beginning of the interstitial at which interstitial playback should end, if the interstitial asset(s) are longer. Pass a positive numeric value, or kCMTimeInvalid to indicate no playout limit.
  @param        userDefinedAttributes
			    Storage for attributes defined by the client or the content vendor. Attribute names should begin with X- for uniformity with server insertion.
  @result       An instance of AVPlayerInterstitialEvent.
*/
+ (instancetype)interstitialEventWithPrimaryItem:(AVPlayerItem *)primaryItem identifier:(nullable NSString *)identifier date:(NSDate *)date templateItems:(NSArray<AVPlayerItem *> *)templateItems restrictions:(AVPlayerInterstitialEventRestrictions)restrictions resumptionOffset:(CMTime)resumptionOffset playoutLimit:(CMTime)playoutLimit userDefinedAttributes:(nullable NSDictionary*)userDefinedAttributes NS_REFINED_FOR_SWIFT API_DEPRECATED("Use interstitialEventWithPrimaryItem:date: instead", macos(12.0, 15.0), ios(15.0, 18.0), tvos(15.0, 18.0), watchos(8.0, 11.0)) API_UNAVAILABLE(visionos);

/*!
  @method       interstitialEventWithPrimaryItem:time:
  @abstract     Returns an instance of AVPlayerInterstitialEvent for use in scheduling interstitial playback.
  @param        primaryItem
                An AVPlayerItem representing the primary content during the playback of which the interstitial event should occur. The primaryItem must have an AVAsset that provides an intrinsic mapping from its timeline to real-time dates.
  @param        time
                The time within the duration of the primary item at which playback of the primary content should be temporarily suspended and the interstitial items played.
  @result       An instance of AVPlayerInterstitialEvent.
*/
+ (instancetype)interstitialEventWithPrimaryItem:(AVPlayerItem *)primaryItem time:(CMTime)time API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/*!
  @method       interstitialEventWithPrimaryItem:date:
  @abstract     Returns an instance of AVPlayerInterstitialEvent for use in scheduling interstitial playback.
  @param        primaryItem
                An AVPlayerItem representing the primary content during the playback of which the interstitial event should occur. The primaryItem must have an AVAsset that provides an intrinsic mapping from its timeline to real-time dates.
  @param        date
                The date within the date range of the primary item at which playback of the primary content should be temporarily suspended and the interstitial items played.
  @result       An instance of AVPlayerInterstitialEvent.
*/
+ (instancetype)interstitialEventWithPrimaryItem:(AVPlayerItem *)primaryItem date:(NSDate *)date API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/*!
  @property     primaryItem
  @abstract     An AVPlayerItem representing the primary content during the playback of which the interstitial event should occur. The primaryItem must have an AVAsset that provides an intrinsic mapping from its timeline to real-time dates.
*/
@property (nonatomic, readonly, weak) AVPlayerItem *primaryItem;

/*!
  @property     identifier
  @abstract     An external identifier for the event. 
  @discussion	If an event is set on an AVPlayerInterstitialEventController that already has an event with the same identifier, the old event will be replaced by the new one.
*/
@property (nonatomic, readonly) NSString *identifier;

/*!
  @property     time
  @abstract     The time within the duration of the primary item at which playback of the primary content should be temporarily suspended and the interstitial items played.
  @discussion	Will have a value equal to kCMTimeInvalid if the event was initialized with a date instead of a time.
*/
@property (nonatomic, readonly) CMTime time;

/*!
  @property     date
  @abstract     The date within the date range of the primary item at which playback of the primary content should be temporarily suspended and the interstitial items played.
  @discussion	Will have a value of nil if the event was initialized with a time instead of a date.
*/
@property (nonatomic, readonly, nullable) NSDate *date;

/*!
  @property     templateItems
  @abstract     An array of AVPlayerItems with configurations that will be reproduced for the playback of interstitial content.
  @discussion
    If you want the instances of AVURLAsset used during interstitial playback to be identical to the ones you specify for templateItems in AVPlayerInterstitialEvents that you set on an AVPlayerInterstitialEventController, rather than equivalent AVURLAssets with the same URL, you must create them with a value for the key AVURLAssetPrimarySessionIdentifierKey that's equal to the httpSessionIdentifier of the primary AVPlayerItem's asset. See AVAsset.h. This is especially useful if you require the use of a custom AVAssetResourceLoader delegate for interstitial assets.

    An NSInvalidArgumentException will be raised if any of the template items employs an AVAsset that lacks a URL, such as an AVComposition.
*/
@property (nonatomic, readonly) NSArray<AVPlayerItem *> *templateItems;

/*!
  @property     restrictions
  @abstract     Indicates restrictions on the use of end user playback controls that are imposed by the event.
*/
@property (nonatomic, readonly) AVPlayerInterstitialEventRestrictions restrictions;

/*!
  @property     resumptionOffset
  @abstract     Specifies the offset in time at which playback of the primary item should resume after interstitial playback has finished.
  @discussion
    Definite numeric values are supported. The value kCMTimeIndefinite can also be used, in order to specify that the effective resumption time offset should accord with the wallclock time elapsed during interstitial playback; this value is typically suitable for live broadcasts. The default value is kCMTimeZero.
*/
@property (nonatomic, readonly) CMTime resumptionOffset;

/*!
  @property     playoutLimit
  @abstract     Specifies the offset in time at which playback of the interstitial event should end.
  @discussion
    Can be any positive numeric value, or invalid. The default value is kCMTimeInvalid, which means there is no limit.
*/
@property (nonatomic, readonly) CMTime playoutLimit;

/*!
  @property     alignsStartWithPrimarySegmentBoundary
  @abstract     Specifies that the start time of interstitial playback should be snapped to a segment boundary of the primary asset
  @discussion
    If true, the start time or date of the interstitial will be adjusted to the nearest segment boundary when the primary player is playing an HTTP Live Streaming asset.
*/
@property (nonatomic, readonly) BOOL alignsStartWithPrimarySegmentBoundary API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/*!
  @property     alignsResumptionWithPrimarySegmentBoundary
  @abstract     Specifies that the resumption time of primary playback should be snapped to a segment boundary of the primary asset
  @discussion
    If true, the resumption time of primary playback following an interstitial will be adjusted to the nearest segment boundary when the primary player is playing an HTTP Live Streaming asset.
*/
@property (nonatomic, readonly) BOOL alignsResumptionWithPrimarySegmentBoundary API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/*!
  @property     cue
  @abstract     The cue property is used to schedule event playback at a predefined position of primary playback.
*/
@property (nonatomic, readonly) AVPlayerInterstitialEventCue cue API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/*!
  @property     willPlayOnce
  @abstract     Specifies that the interstitial should be scheduled for playback once only, and suppressed for subsequent replay.
  @discussion
    The "once" provision takes effect at the start of interstitial playback. The interstitial will not be scheduled again even if the first playback is canceled before completion.
*/
@property (nonatomic, readonly) BOOL willPlayOnce API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/*!
  @property     userDefinedAttributes
  @abstract     Attributes of the event defined by the content vendor or the client.
  @discussion
    Dictionary keys are attribute names. Dictionary values are attribute values.
*/
@property (nonatomic, readonly) NSDictionary * NS_SWIFT_SENDABLE userDefinedAttributes;

/*!
  @property     assetListResponse
  @abstract     The asset list JSON response as a dictionary, or nil if no asset list response has been loaded for the event.
  @discussion   If the AVPlayerInterstitialEvent's templateItems is empty and the assetListResponse is nil, then an asset list read is expected. If the AVPlayerInterstitialEvent's templateItems is not empty and the assetListResponse is nil, then an asset list read is not expected.
*/
@property (readonly, nullable) NSDictionary * NS_SWIFT_SENDABLE assetListResponse API_AVAILABLE(macos(13.3), ios(16.4), tvos(16.4), watchos(9.4), visionos(1.0));

/*!
  @enum AVPlayerInterstitialEventAssetListResponseStatus
  @abstract These constants describe the status of the asset list response for an AVPlayerInterstitialEvent.

  @constant	 AVPlayerInterstitialEventAssetListResponseStatusAvailable
	Indicates that the asset list response is now available and non-nil, meaning the asset list read was successful.
  @constant	 AVPlayerInterstitialEventAssetListResponseStatusCleared
	Indicates that asset list response has been cleared and reverted to its original state of nil.
  @constant	 AVPlayerInterstitialEventAssetListResponseStatusUnavailable
	Indicates that the asset list response is unavailable, meaning the asset list read failed.
*/
typedef NS_ENUM(NSInteger, AVPlayerInterstitialEventAssetListResponseStatus) {
	AVPlayerInterstitialEventAssetListResponseStatusAvailable = 0,
	AVPlayerInterstitialEventAssetListResponseStatusCleared = 1,
	AVPlayerInterstitialEventAssetListResponseStatusUnavailable = 2
} API_AVAILABLE(macos(13.3), ios(16.4), tvos(16.4), watchos(9.4), visionos(1.0));

/*!
  @property     timelineOccupancy
  @abstract     Indicates this event's occupancy on AVPlayerItemIntegratedTimeline. The default value is AVPlayerInterstitialEventTimelineSinglePointOccupancy.
*/
@property (nonatomic, readonly) AVPlayerInterstitialEventTimelineOccupancy timelineOccupancy API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/*!
  @property     supplementsPrimaryContent
  @abstract     Indicates this event will supplement the primary content and should be presented unified with the primary item. The default value is NO.
*/
@property (nonatomic, readonly) BOOL supplementsPrimaryContent API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/*!
  @property     contentMayVary
  @abstract     Indicates this event's content is dynamic and server may respond with different interstitial assets for other particpants in coordinated playback.
  @discussion   Indicates this event's content is dynamic and server may respond with different interstitial assets for other particpants in coordinated playback. If this value is set to NO and the primary asset is particpating in coordinated playback, this event will participate in coordinated playback as well. The default value is YES.
*/
@property (nonatomic, readonly) BOOL contentMayVary API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));
@end

@interface AVPlayerInterstitialEvent (MutableEvents)
@property (nonatomic, readwrite, weak) AVPlayerItem *primaryItem API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite, copy) NSString *identifier API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite) CMTime time API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite, copy, nullable) NSDate *date API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite, copy) NSArray<AVPlayerItem *> *templateItems API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite) AVPlayerInterstitialEventRestrictions restrictions API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite) CMTime resumptionOffset API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite) CMTime playoutLimit API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite) BOOL alignsStartWithPrimarySegmentBoundary API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite) BOOL alignsResumptionWithPrimarySegmentBoundary API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite, retain) AVPlayerInterstitialEventCue cue API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite) BOOL willPlayOnce API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite, copy) NSDictionary * NS_SWIFT_SENDABLE userDefinedAttributes API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
@property (nonatomic, readwrite) AVPlayerInterstitialEventTimelineOccupancy timelineOccupancy API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));
@property (nonatomic, readwrite) BOOL supplementsPrimaryContent API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));
@property (nonatomic, readwrite) BOOL contentMayVary API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/*!
  @property     plannedDuration
  @abstract     Indicates the event's planned duration. The default value is kCMTimeInvalid.
*/
@property (nonatomic, readwrite) CMTime plannedDuration API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));
@end

/*!
  @class        AVPlayerInterstitialEventMonitor

  @abstract
    An AVPlayerInterstitialEventMonitor allows you to observe the scheduling and progress of interstitial events, specified either intrinsically within the content of primary items, such as via use of directives carried by HLS media playlists, or via use of an AVPlayerInterstitialEventController.
    
  @discussion
    The schedule of interstitial events is provided as an array of AVPlayerInterstitialEvents. For each AVPlayerInterstitialEvent, when the primary player's current item is the primary item of the interstitial event and its currentDate reaches the date of the event, playback of the primary item by the primary player is temporarily suspended, i.e. its timeControlStatus changes to AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate and its reasonForWaitingToPlay will change to AVPlayerWaitingDuringInterstitialEventReason. During this suspension, playback of items that replicate the interstitial template items of the event are played by the interstitial player, which temporarily assumes the output configuration of the primary player; for example, its visual content will be routed to AVPlayerLayers that reference the primary player. Once the interstitial player has advanced through playback of the interstitial items specified by the event or its current item otherwise becomes nil, playback of the primary content will resume, at an offset from the time at which it was suspended as specified by the event.
  
    Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVPlayerInterstitialEventMonitor : NSObject

/*!
  @method       interstitialEventMonitorWithPrimaryPlayer:
  @abstract     Returns an instance of AVPlayerInterstitialEvent for use in observing and scheduling interstitial playback.
  @param        primaryPlayer
                The AVPlayer that will play the primaryItems of the receiver's interstitial events.
  @result       An instance of AVPlayerInterstitialEventMonitor.
*/
+ (instancetype)interstitialEventMonitorWithPrimaryPlayer:(AVPlayer *)primaryPlayer;

- (instancetype)initWithPrimaryPlayer:(AVPlayer *)primaryPlayer  NS_DESIGNATED_INITIALIZER;

/*!
  @property     primaryPlayer
  @abstract     The AVPlayer that will play the primaryItems of the receiver's interstitial events.
*/
@property (nonatomic, readonly, weak) AVPlayer *primaryPlayer;

/*!
  @property     interstitialPlayer
  @abstract     The AVQueuePlayer that will play interstitial items during suspension of playback of primary items.
*/
@property (nonatomic, readonly) AVQueuePlayer *interstitialPlayer;

/*!
  @property     events
  @abstract     Provides the current schedule of interstitial events, specified either intrinsically within the content of primary items, such as via use of directives carried by HLS media playlists, or via use of an AVPlayerInterstitialEventController.
  @discussion
    When interstitial events follow a schedule specified intrinsically within the content of primary items, the value of this property will typically change whenever the currentItem of the primaryPlayer changes. For HLS content that specifies interstitials via the use of DATERANGE tags, the value of this property may also change whenever the set of DATERANGE tags in the currentItem's media playlist changes.
    When interstitial events follow a schedule specified via use of an AVPlayerInterstitialEventController, the value of this property changes only when a new schedule is set on the AVPlayerInterstitialEventController.
    The events returned in this array are immutable. Attempting to mutate them will trigger an exception. To alter an event, make a copy and mutate the copy.
*/
@property (readonly, copy) NSArray<AVPlayerInterstitialEvent *> *events;

/*!
  @property     currentEvent
  @abstract     The current interstitial event. Has a value of nil during playback of primary content by the primary player.
*/
@property (readonly, nullable) AVPlayerInterstitialEvent *currentEvent;

@end

/*!
  @constant     AVPlayerInterstitialEventMonitorEventsDidChangeNotification
  @abstract     A notification that's posted whenever the value of events of an AVPlayerInterstitialEventMonitor is changed.
*/
AVF_EXPORT NSNotificationName const AVPlayerInterstitialEventMonitorEventsDidChangeNotification API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
  @constant     AVPlayerInterstitialEventMonitorCurrentEventDidChangeNotification
  @abstract     A notification that's posted whenever the currentEvent of an AVPlayerInterstitialEventMonitor changes.
*/
AVF_EXPORT NSNotificationName const AVPlayerInterstitialEventMonitorCurrentEventDidChangeNotification API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
  @constant     AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeNotification
  @abstract     A notification that is posted whenever an AVPlayerInterstitialEvent's asset list response status changes.
  @discussion   Carries a userInfo dictionary that can contain the following keys and values:
                    1. AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeEventKey, with a value that indicates the AVPlayerInterstitialEvent for which the asset response status has changed.
                    2. AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeStatusKey, with a value of type AVPlayerInterstitialEventAssetListResponseStatus, indicating the changed asset response status.
                    3. AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeErrorKey, with a value of type NSError that carries additional information about the failure to read the asset list. This key is only present when the new AVPlayerInterstitialEventAssetListResponseStatus is AVPlayerInterstitialEventAssetListResponseStatusUnavailable.
*/
AVF_EXPORT NSNotificationName const AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeNotification API_AVAILABLE(macos(13.3), ios(16.4), tvos(16.4), watchos(9.4), visionos(1.0));

/*!
  @constant     AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeEventKey
  @abstract     The dictionary key for the AVPlayerInterstitial event that had its asset list response status changed in the payload of the AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeNotification.
  @discussion   The value corresponding to this key is of type AVPlayerInterstitialEvent.
*/
AVF_EXPORT NSString *const AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeEventKey API_AVAILABLE(macos(13.3), ios(16.4), tvos(16.4), watchos(9.4), visionos(1.0));

/*!
  @constant     AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeStatusKey
  @abstract     The dictionary key for the asset list response status in the payload of the AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeNotification.
  @discussion   The value corresponding to this key is of type AVPlayerInterstitialEventAssetListResponseStatus.
*/
AVF_EXPORT NSString *const AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeStatusKey API_AVAILABLE(macos(13.3), ios(16.4), tvos(16.4), watchos(9.4), visionos(1.0));

/*!
  @constant     AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeErrorKey
  @abstract     The dictionary key for the NSError in the payload of the AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeNotification.
  @discussion   The value corresponding to this key is of type NSError. This key only exists in the payload of AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeNotification if AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeStatusKey in the same payload points to a value of AVPlayerInterstitialEventAssetListResponseStatusUnavailable.
*/
AVF_EXPORT NSString *const AVPlayerInterstitialEventMonitorAssetListResponseStatusDidChangeErrorKey API_AVAILABLE(macos(13.3), ios(16.4), tvos(16.4), watchos(9.4), visionos(1.0));

/*!
  @class        AVPlayerInterstitialEventController

  @abstract
    An AVPlayerInterstitialEventController allows you to specify a schedule of interstitial events for items played by a primary player.
    By creating an instance of AVPlayerInterstitialEventController and setting a schedule of interstitial events, you pre-empt directives the are intrinsic to the items played by the primary player, if any exist, causing them to be ignored.
    
  @discussion
    The schedule of interstitial events is specified as an array of AVPlayerInterstitialEvents. For each AVPlayerInterstitialEvent, when the primary player's current item is the primary item of the interstitial event and its currentDate reaches the date of the event, playback of the primary item by the primary player is temporarily suspended, i.e. its timeControlStatus changes to AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate and its reasonForWaitingToPlay will change to AVPlayerWaitingDuringInterstitialEventReason. During this suspension, playback of items that replicate the interstitial template items of the event are played by the interstitial player, which temporarily assumes the output configuration of the primary player; for example, its visual content will be routed to AVPlayerLayers that reference the primary player. Once the interstitial player has advanced through playback of the interstitial items specified by the event or its current item otherwise becomes nil, playback of the primary content will resume, at an offset from the time at which it was suspended as specified by the event.

    Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVPlayerInterstitialEventController : AVPlayerInterstitialEventMonitor

/*!
  @method       interstitialEventControllerWithPrimaryPlayer
  @abstract     Returns an instance of AVPlayerInterstitialEvent for use in observing and scheduling interstitial playback.
  @param        primaryPlayer
                The AVPlayer that will play the primaryItems of the receiver's interstitial events.
  @result       An instance of AVPlayerInterstitialEventController.
  @discussion   This method throws an exception if the primary player is an interstitial player.
*/
+ (instancetype)interstitialEventControllerWithPrimaryPlayer:(AVPlayer *)primaryPlayer;

/*!
  @method       initWithPrimaryPlayer:
  @discussion	This method throws an exception if the primary player is an interstitial player.
 */
- (instancetype)initWithPrimaryPlayer:(AVPlayer *)primaryPlayer;

/*!
  @property     events
  @abstract     Specifies the current schedule of interstitial events.
  @discussion
    Setting this property to a non-nil value cancels and overrides all previously scheduled future interstitial events, including those that are intrinsically specified by the content of primary items, such as directives carried by HLS media playlists. Setting it to nil causes its value to be reset in accordance with the content of the current primary item.

    If you change the value of events during an interstitial event and the current event is not included in the new value of events, the current event is nevertheless allowed to continue until completion. If you wish to cancel the current event, use -cancelCurrentEventWithResumptionOffset:.

    If interstitial events are scheduled with dates that coincide either with the date of another scheduled interstitial event or with the date range of the primary content that's omitted according to the resumption offset of another scheduled interstitial event, the primary content will remain suspended until all coinciding interstitial events have been completed. The effective resumption offset will be the sum of the resumption offsets of the coinciding interstitial events. (Note that the sum of a numeric CMTime and kCMTimeIndefinite is kCMTimeIndefinite.)

    If interstitial events are scheduled for the same date, they are ordered according to their position in the events array.

    The receiver will make a copy of the events that are set on it. Subsequent mutations on the original events will have no effect on the copy.
    
    An NSInvalidArgumentException will be raised if an under-specified AVPlayerInterstitialEvent is set, such as one with a nil primaryItem, or with neither a time nor a date.
*/
@property (copy, null_resettable) NSArray<AVPlayerInterstitialEvent *> *events;

/*!
  @method       cancelCurrentEventWithResumptionOffset:
  @abstract     Causes the playback of any and all interstitial content currently in progress to be abandoned and the playback of primary content to be resumed.
  @param        resumptionOffset
                Specifies the offset in time at which playback of the primary player's current item should resume after interstitial playback has finished. To specify that the effective resumption time offset should accord with the wallclock time elapsed during interstitial playback, pass a value of kCMTimeIndefinite.
  @discussion
    If invoked during the handling of coinciding interstitial events, they will all be canceled.           
    When you cancel interstitial events via the use of this method, the value of resumptionOffset that you pass overrides the events' resumptionOffset.
    Has no effect while currentEvent is nil.
*/
- (void)cancelCurrentEventWithResumptionOffset:(CMTime)resumptionOffset;

@end

@interface AVPlayer (AVPlayerInterstitialSupport)

/*!
 @constant AVPlayerWaitingDuringInterstitialEventReason
 @abstract Indicates that the player is waiting for the completion of an interstitial event.
 @discussion
    The player is waiting for playback because an interstitial event is currently in progress. Interstitial events can be monitored via use of an AVPlayerInterstitialEventMonitor.
 */
AVF_EXPORT AVPlayerWaitingReason const AVPlayerWaitingDuringInterstitialEventReason API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

@end

@interface AVPlayerItem (AVPlayerInterstitialSupport)

/*!
  @property     automaticallyHandlesInterstitialEvents
  @abstract     Allows interstitials to be played according to a schedule that's specified by server-side directives. The default value is YES. A value of NO prevents automatic scheduling of future server-side interstitial events. Events specified by an AVPlayerInterstitialEventController override server-side events, regardless of the value of this property.
  @discussion	Before macOS 13, iOS 16, tvOS 16, and watchOS 9, this property must be accessed on the main thread/queue.
 */
@property (nonatomic) BOOL automaticallyHandlesInterstitialEvents
#if AVF_DEPLOYING_TO_2022_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
  @property     templatePlayerItem
  @abstract     If the item was created automatically according to a template item for looping, for interstitial playback, or for other purposes, indicates the AVPlayerItem that was used as the template.
*/
@property (nonatomic, readonly, nullable) AVPlayerItem *templatePlayerItem NS_SWIFT_NONISOLATED API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlayerInterstitialEventController.h>
#endif
