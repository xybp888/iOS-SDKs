/*
 File:  AVPlaybackUserInterfaceControllable.h
 
 Framework:  AVKit
 
 Copyright © 2026 Apple Inc. All rights reserved.
 
 To report bugs, go to:  http://developer.apple.com/bugreporter/
 
 */

#import <AVFoundation/AVMediaFormat.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <Foundation/Foundation.h>
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

#if TARGET_OS_MACCATALYST
#import <AVKitCore/AVKitDefines.h>
#else
#import <AVKit/AVKitDefines.h>
#endif // TARGET_OS_MACCATALYST


// MARK: - Typedefs

/*!
 Describes possible transport states of the playback source.
 */
typedef NS_ENUM(NSInteger, AVPlaybackUserInterfacePlaybackState) {
	/// Indicates the source is in a normal state.
	AVPlaybackUserInterfacePlaybackStateNormal = 0,
	/// Indicates the source is scanning forward or backward at an accelerated rate.
	AVPlaybackUserInterfacePlaybackStateScanning,
	/// Indicates the source is being scrubbed by user interaction with the timeline.
	AVPlaybackUserInterfacePlaybackStateScrubbing,
} API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos);

/*!
 Describes navigation capabilities of the media source.
 
 This option set defines timeline navigation operations. Different content types and sources may have varying
 levels of navigation support based on technical limitations, licensing restrictions, or content type.
 */
typedef NS_OPTIONS(NSUInteger, AVPlaybackUserInterfaceSeekCapabilities) {
	/// The source does not support any scanning or seeking operations.
	AVPlaybackUserInterfaceSeekCapabilitiesNone			= 0,
	/// The source supports forward scanning at accelerated rates for fast-forward operations. Enables rapid progression through content at speeds greater than normal playback.
	AVPlaybackUserInterfaceSeekCapabilitiesScanForward	= 1 << 0,
	/// The source supports backward scanning at accelerated rates for rewind operations. Enables rapid reverse progression through content at speeds greater than normal playback.
	AVPlaybackUserInterfaceSeekCapabilitiesScanBackward	= 1 << 1,
	/// The source supports seeking to specific time positions for precise navigation. Enables jumping directly to any arbitrary point within the seekable time ranges.
	AVPlaybackUserInterfaceSeekCapabilitiesSeek			= 1 << 2,
} API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos);

/*!
 Describes the type of content within a timeline segment.
 */
typedef NS_ENUM(NSInteger, AVPlaybackUserInterfaceTimelineSegmentType) {
	/// The segment contains primary program content.
	AVPlaybackUserInterfaceTimelineSegmentTypePrimary = 0,
	/// The segment contains an advertisement.
	AVPlaybackUserInterfaceTimelineSegmentTypeAdvertisement,
	/// The segment contains bonus content, such as a post-credits scene or supplemental material.
	AVPlaybackUserInterfaceTimelineSegmentTypeBonus,
	/// The segment contains end credits.
	AVPlaybackUserInterfaceTimelineSegmentTypeCredits,
	/// The segment contains an opening title sequence.
	AVPlaybackUserInterfaceTimelineSegmentTypeIntro,
	/// The segment contains a recap of previous content.
	AVPlaybackUserInterfaceTimelineSegmentTypeRecap,
	/// The segment contains a trailer or preview for other content.
	AVPlaybackUserInterfaceTimelineSegmentTypeTrailer,
	/// The segment contains auxiliary content of an unspecified type.
	AVPlaybackUserInterfaceTimelineSegmentTypeOther,
} API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos);


// MARK: -

NS_ASSUME_NONNULL_BEGIN

/*!
 Represents a contiguous segment of timeline content with specific playback characteristics.
 
 Timeline segments divide media content into distinct regions, each with its own classification
 and behavior rules. Segments are typically used to distinguish between primary content and
 auxiliary content such as advertisements or bonus material, and to control whether users can
 seek or skip through specific portions of the timeline.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
@interface AVPlaybackUserInterfaceTimelineSegment : NSObject <NSCopying, NSSecureCoding>

AVKIT_INIT_UNAVAILABLE

/// The time range defining the segment's position and duration within the overall timeline.
@property (nonatomic, readonly) CMTimeRange timeRange;

/// The type of content within this segment, indicating whether it is primary program content or a specific category of auxiliary content.
@property (nonatomic, readonly) AVPlaybackUserInterfaceTimelineSegmentType segmentType;

/// Indicates whether this segment should be visually highlighted or marked in the timeline UI.
@property (nonatomic, readonly, getter = isMarked) BOOL marked;

/// Indicates whether this segment must be played sequentially without seeking or skipping. Typically used for advertisements or important announcements.
@property (nonatomic, readonly) BOOL requiresLinearPlayback;

/// Optional external identifier for tracking or analytics purposes. May correspond to advertisement IDs, chapter markers, or other external systems.
@property (nonatomic, readonly, copy, nullable) NSString *identifier;

/*!
 Initializes a new timeline segment with the specified characteristics.
 
 - Parameter timeRange: The time range defining the segment's position and duration within the timeline.
 - Parameter segmentType: The type of content this segment represents.
 - Parameter marked: Whether the segment should be visually highlighted in the timeline UI.
 - Parameter requiresLinearPlayback: Whether the segment must be played sequentially without seeking or skipping.
 - Parameter identifier: External identifier for tracking or analytics purposes.
 */
- (instancetype)initWithTimeRange:(CMTimeRange)timeRange
					  segmentType:(AVPlaybackUserInterfaceTimelineSegmentType)segmentType
						   marked:(BOOL)marked
		   requiresLinearPlayback:(BOOL)requiresLinearPlayback
					   identifier:(nullable NSString *)identifier NS_DESIGNATED_INITIALIZER;

@end

/*!
 Represents a media selection option for audio tracks or subtitle tracks.
 
 This class represents individual media options (such as audio tracks or subtitle tracks)
 that can be selected by the user in media playback interfaces. Each option provides
 display information and metadata for user selection.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
@interface AVPlaybackUserInterfaceMediaSelectionOption : NSObject <NSCopying, NSSecureCoding>

AVKIT_INIT_UNAVAILABLE

/// Human-readable name for this media option displayed in user interfaces (e.g., "English", "Spanish (Latin America)", "Director's Commentary").
@property (nonatomic, readonly, copy) NSString *displayName;

/// Unique system identifier for this media option, used for programmatic selection and persistence across sessions.
@property (nonatomic, readonly, copy) NSString *identifier;

/// IETF BCP 47 language identifier (e.g., "en-US", "es-419", "zh-Hans-CN") indicating the primary language and locale of this option.
/// This standardized tag provides detailed language information including region, script, and variants. May be empty for language-neutral content such as music-only audio tracks, sound effects, or visual-only subtitles without spoken content.
@property (nonatomic, readonly, copy, nullable) NSString *extendedLanguageTag NS_REFINED_FOR_SWIFT;

/// The media characteristics describing accessibility features and content properties of this option.
/// Common values include `AVMediaCharacteristicContainsOnlyForcedSubtitles`, `AVMediaCharacteristicTranscribesSpokenDialogForAccessibility`, and `AVMediaCharacteristicDescribesMusicAndSoundForAccessibility`. May be empty if no characteristics apply.
@property (nonatomic, readonly, copy) NSArray<AVMediaCharacteristic> *mediaCharacteristics;

/*!
 Initializes a new media selection option with the specified attributes.
 
 - Parameter displayName: Human-readable name displayed in user interfaces.
 - Parameter identifier: Unique system identifier for programmatic selection.
 - Parameter extendedLanguageTag: IETF BCP 47 language identifier, or `nil` for language-neutral content.
 - Parameter mediaCharacteristics: The media characteristics describing accessibility features and content properties of this option.
 */
- (instancetype)initWithDisplayName:(NSString *)displayName
						 identifier:(NSString *)identifier
                extendedLanguageTag:(nullable NSString *)extendedLanguageTag
               mediaCharacteristics:(NSArray<AVMediaCharacteristic> *)mediaCharacteristics NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@end

@class AVPlaybackUserInterfaceContentURLArtwork;

/*!
 Base class representing artwork or cover art for media content.
 
 Use a concrete subclass such as ``AVPlaybackUserInterfaceContentURLArtwork`` to create artwork instances.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
@interface AVPlaybackUserInterfaceContentArtwork : NSObject <NSCopying, NSSecureCoding>

AVKIT_INIT_UNAVAILABLE

/// The pixel dimensions of the artwork image.
@property (nonatomic, readonly) CGSize size;

/*!
 Creates an artwork instance that references an image at the given URL.
 
 - Parameter url: URL pointing to the artwork image resource.
 - Parameter type: The uniform type identifier for the image data.
 - Parameter size: The pixel dimensions of the artwork image.
 */
+ (AVPlaybackUserInterfaceContentURLArtwork *)artworkWithURL:(NSURL *)url
												 contentType:(UTType *)type
														size:(CGSize)size NS_SWIFT_NAME(artwork(url:contentType:size:));

@end

/*!
 An artwork subclass that references artwork via a URL and content type.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
@interface AVPlaybackUserInterfaceContentURLArtwork : AVPlaybackUserInterfaceContentArtwork

/// URL pointing to the artwork image resource.
@property (nonatomic, readonly, copy) NSURL *url;

/// The uniform type identifier for the artwork image data.
@property (nonatomic, readonly, copy) UTType *contentType;

AVKIT_INIT_UNAVAILABLE

@end

/*!
 Properties specific to video content.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
NS_REFINED_FOR_SWIFT
@interface AVPlaybackUserInterfaceContentVideoProperties : NSObject <NSCopying, NSSecureCoding>

AVKIT_INIT_UNAVAILABLE

/// The natural pixel dimensions of the video content for layout and aspect ratio calculations.
@property (nonatomic, readonly) CGSize presentationSize;

/*!
 Initializes a new video properties instance.

 - Parameter presentationSize: The natural pixel dimensions of the video content.
 */
- (instancetype)initWithPresentationSize:(CGSize)presentationSize NS_DESIGNATED_INITIALIZER;

@end

/*!
 A mutable template for configuring media metadata before creating immutable metadata objects.
 
 Use this class to build and configure metadata for media content with full control over all properties.
 Once configured, create an immutable ``AVPlaybackUserInterfaceContentMetadata`` object using `initWithTemplate:` to provide
 stable metadata for playback interfaces.
 
 This template provides a convenient way to incrementally build metadata information, allowing you to
 set properties individually before finalizing the metadata. All properties are mutable (readwrite),
 making it ideal for scenarios where metadata is constructed from multiple sources or updated over time.
 
 Example usage:
 
 AVPlaybackUserInterfaceContentMetadataTemplate *template = [[AVPlaybackUserInterfaceContentMetadataTemplate alloc] init];
 template.videoProperties = [[AVPlaybackUserInterfaceContentVideoProperties alloc] initWithPresentationSize:CGSizeMake(1920, 1080)];
 template.title = @"Episode 5: The Journey Continues";
 template.subtitle = @"Season 2";
 template.artworkRepresentations = @[artwork1, artwork2];

 AVPlaybackUserInterfaceContentMetadata *metadata = [[AVPlaybackUserInterfaceContentMetadata alloc] initWithTemplate:template];
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_REFINED_FOR_SWIFT
@interface AVPlaybackUserInterfaceContentMetadataTemplate : NSObject <NSCopying, NSSecureCoding>

/// Properties describing the video content. `nil` if the content contains no video.
@property (nonatomic, readwrite, copy, nullable) AVPlaybackUserInterfaceContentVideoProperties *videoProperties;

/// Primary title or name of the media content for display in player UI and system interfaces.
/// This should be the main identifying text for the content, such as a song title, episode name, or movie title.
@property (nonatomic, readwrite, copy, nullable) NSString *title;

/// Secondary descriptive text such as artist name, episode description, or additional context for the content.
/// This provides supplementary information to help users identify and understand the content being played.
@property (nonatomic, readwrite, copy, nullable) NSString *subtitle;

/// Array of available artwork representations in various formats and sizes for this media content.
/// Multiple representations allow the system to choose the most appropriate artwork for different display contexts (thumbnails, full-screen, high-DPI displays).
/// Each representation specifies its dimensions, format, and URL for optimal loading and display performance.
@property (nonatomic, readwrite, copy) NSArray<AVPlaybackUserInterfaceContentArtwork *> *artworkRepresentations;

@end

/*!
 Provides metadata information about media content including title, artwork, and content type.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
NS_REFINED_FOR_SWIFT
@interface AVPlaybackUserInterfaceContentMetadata : NSObject <NSCopying, NSSecureCoding>

AVKIT_INIT_UNAVAILABLE

/// Properties describing the video content. `nil` if the content contains no video.
@property (nonatomic, readonly, copy, nullable) AVPlaybackUserInterfaceContentVideoProperties *videoProperties;

/// Primary title or name of the media content for display in player UI and system interfaces.
/// This should be the main identifying text for the content, such as a song title, episode name, or movie title.
@property (nonatomic, readonly, copy, nullable) NSString *title;

/// Secondary descriptive text such as artist name, episode description, or additional context for the content.
/// This provides supplementary information to help users identify and understand the content being played.
@property (nonatomic, readonly, copy, nullable) NSString *subtitle;

/// Array of available artwork representations in various formats and sizes for this media content.
/// Multiple representations allow the system to choose the most appropriate artwork for different display contexts (thumbnails, full-screen, high-DPI displays).
/// Each representation specifies its dimensions, format, and URL for optimal loading and display performance.
@property (nonatomic, readonly, copy) NSArray<AVPlaybackUserInterfaceContentArtwork *> *artworkRepresentations;

/*!
 Initializes a new metadata object with the specified properties.

 - Parameter videoProperties: Properties describing the video content, or `nil` for content without video.
 - Parameter title: Primary title or name of the media content.
 - Parameter subtitle: Secondary descriptive text such as artist name or episode description.
 - Parameter artworkRepresentations: Array of available artwork representations in various formats and sizes.
 */
- (instancetype)initWithVideoProperties:(nullable AVPlaybackUserInterfaceContentVideoProperties *)videoProperties
								  title:(nullable NSString *)title
							   subtitle:(nullable NSString *)subtitle
				 artworkRepresentations:(NSArray<AVPlaybackUserInterfaceContentArtwork *> *)artworkRepresentations NS_DESIGNATED_INITIALIZER;

/*!
 Initializes a new metadata object by copying values from a metadata template.
 
 This initializer creates an immutable ``AVPlaybackUserInterfaceContentMetadata`` instance from a mutable
 ``AVPlaybackUserInterfaceContentMetadataTemplate``, providing a convenient way to convert configured template
 data into stable metadata for playback interfaces.
 
 All properties from the template are copied into the new metadata object, creating an
 independent immutable snapshot of the template's current state. Subsequent changes to
 the template will not affect the created metadata object.
 
 - Parameter metadataTemplate: The metadata template to copy values from. If `nil`, returns a metadata object with default values.
 */
- (instancetype)initWithTemplate:(nullable AVPlaybackUserInterfaceContentMetadataTemplate *)metadataTemplate;

@end

/*!
 A snapshot comprising a playback position recorded at a known host time and the rate of position
 advancement.

 All three fields must be captured atomically by the conformer.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
@interface AVPlaybackUserInterfacePlaybackPosition : NSObject <NSCopying, NSSecureCoding>

AVKIT_INIT_UNAVAILABLE

/// The playback position at the time of the snapshot.
@property (nonatomic, readonly) CMTime position;

/// The mach host time at which `position` was accurate.
@property (nonatomic, readonly) CMTime hostTime;

/// The rate of position advancement at the time of the snapshot. Zero when paused; negative during reverse scan.
@property (nonatomic, readonly) float rate;

/// Creates a new playback position snapshot.
///
/// - Parameters:
///   - position: The playback position at `hostTime`.
///   - hostTime: The mach host time at which `position` was accurate.
///   - rate: The rate of position advancement at the time of the snapshot.
/// - Returns: A new playback position snapshot.
- (instancetype)initWithPosition:(CMTime)position hostTime:(CMTime)hostTime rate:(float)rate NS_DESIGNATED_INITIALIZER;

@end

// MARK: - Protocols

/*!
 Provides playback control and state management for media content.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVPlaybackUserInterfacePlaybackControllable <NSObject>

/// Indicates whether the media source is ready to begin playback.
/// This property should transition from NO to YES once the source has loaded enough data to start playback, and should not revert. Use `isBuffering` to track temporary stalls that may occur after this point. Must be key-value observable.
@property (nonatomic, readonly, getter = isReady) BOOL ready;

/// Indicates whether playback is active. Setting this property to YES starts playback; setting it to NO pauses it.
/// This property reflects playback intent — it should remain YES while `isBuffering` is YES, indicating that playback should resume automatically once sufficient data is available. Must be key-value observable.
@property (nonatomic, readwrite, getter = isPlaying) BOOL playing;

/// Indicates whether the media source is currently stalled waiting for data. Returns YES when the source cannot immediately sustain continuous playback.
/// This may occur both before `isReady` becomes YES during initial loading, and after `isReady` is YES during mid-playback stalls. When YES, `isPlaying` may still be YES, indicating that playback should resume automatically once sufficient data is available. Must be key-value observable.
@property (nonatomic, readonly, getter = isBuffering) BOOL buffering;

/// The user's preferred playback speed multiplier.
/// This value is preserved across scanning operations. Must be key-value observable.
@property (nonatomic, readwrite) float playbackSpeed;

/// The speed multiplier used during scanning (fast-forward or rewind).
/// This is a transient override that is active only while `state` is scanning. It does not affect `playbackSpeed`. When scanning ends, playback resumes at `playbackSpeed`. Must be key-value observable.
@property (nonatomic, readwrite) float scanSpeed;

/// The current transport state of the playback source. Must be key-value observable.
@property (nonatomic, readwrite) AVPlaybackUserInterfacePlaybackState state;

/// An option set indicating which timeline navigation operations are supported by this media source.
/// This property defines the available navigation capabilities, including precise seeking to specific time positions and accelerated scanning for fast-forward/rewind operations.
/// The supported modes may vary based on content type, licensing restrictions, or technical limitations of the underlying media format. Must be key-value observable.
@property (nonatomic, readonly) AVPlaybackUserInterfaceSeekCapabilities supportedSeekCapabilities;

/// Indicates whether the content is a live stream. Returns YES for live streams and NO for on-demand content. Must be key-value observable.
@property (nonatomic, readonly) BOOL containsLiveStreamingContent;

/// Error information when the source encounters a playback failure. Nil when playback is functioning normally. Must be key-value observable.
@property (nonatomic, readonly, strong, nullable) NSError *error;


#if TARGET_OS_TV
/// The default playback speed to use when playback begins.
/// This value is used to set the initial playback rate when starting playback.
/// A value of 1.0 represents normal speed. Must be key-value observable.
@property (nonatomic, readwrite) float defaultPlaybackSpeed API_UNAVAILABLE(tvos) API_UNAVAILABLE(ios, macCatalyst, macos, visionos, watchos);
#endif // TARGET_OS_TV

@end

/*!
 Provides time control and navigation capabilities for media content.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVPlaybackUserInterfaceTimeControllable <NSObject>

/// The time range representing the total duration and bounds of the media content.
/// This defines the overall playable timeline, with all segments and seekable ranges falling within this range.
/// For on-demand content, `start` is typically zero and `duration` is the total length of the content.
/// For live content without DVR, set ``timeRange`` to a zero-duration range at the current live edge and advance it as the edge moves; ``seekableTimeRanges`` must be nil or empty.
/// For live content with DVR, set ``timeRange`` to the available DVR window and advance both `start` and `end` as the window rolls. Use ``seekableTimeRanges`` to indicate which portion is seekable.
/// The duration is always a finite, non-negative value. Must be key-value observable.
@property (nonatomic, readonly) CMTimeRange timeRange;

/// A snapshot of the current playback position. Must be updated — with a fresh `hostTime` — on
/// play, pause, seek, scan, and buffering state changes. Must be key-value observable.
@property (nonatomic, readonly, copy) AVPlaybackUserInterfacePlaybackPosition *playbackPosition;

/*!
 Requests a seek to the specified position.

 - Parameter position: The position to seek to.
 - Parameter tolerance: How close to `position` the actual seek must land. Pass `kCMTimeZero` for exact frame-accurate seeking or `kCMTimePositiveInfinity` for fast approximate seeking.
 */
- (void)seekToPosition:(CMTime)position tolerance:(CMTime)tolerance;

/// Segments representing different content types within the timeline. All segments should be contiguous and collectively cover the entire timeline duration without gaps or overlaps.
/// Each segment defines a specific portion of content (such as main program, advertisements, or bonus material) with its own playback characteristics. Must be key-value observable.
@property (nonatomic, readonly, copy) NSArray<AVPlaybackUserInterfaceTimelineSegment *> *segments;

/// The segment containing the current playback position. This property automatically updates as playback progresses through different timeline segments.
/// Use this to determine the current content type (primary vs. secondary) and any special playback characteristics that apply to the current position. Must be key-value observable.
@property (nonatomic, readonly, copy) AVPlaybackUserInterfaceTimelineSegment *currentSegment;

/// An array of time ranges within the timeline where seeking operations are permitted.
/// Each range is represented as an NSValue wrapping a CMTimeRange structure, defining portions of the timeline where users can jump to specific time positions during playback.
/// If `nil`, the entire content defined by timeRange is considered seekable. When provided, each range must be a subset of the overall timeRange and should not overlap with other seekable ranges.
/// An empty array means the entire content defined by timeRange is not seekable.
/// Seekable ranges typically exclude segments where requiresLinearPlayback is YES, such as advertisements, mandatory content, or licensing-restricted portions.
/// The array should contain ranges in chronological order for optimal performance. Must be key-value observable.
@property (nonatomic, readonly, copy, nullable) NSArray<NSValue *> *seekableTimeRanges;

@end

/*!
 Provides audio and subtitle selection capabilities for media content.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVPlaybackUserInterfaceMediaSelectionControllable <NSObject>

/// The currently selected audio track. Should be one of the options in `audioOptions`. Must be key-value observable.
@property (nonatomic, readwrite, copy, nullable) AVPlaybackUserInterfaceMediaSelectionOption *currentAudioOption;

/// The currently selected audio description track. Should be one of the options in `audioDescriptionOptions`. Must be key-value observable.
@property (nonatomic, readwrite, copy, nullable) AVPlaybackUserInterfaceMediaSelectionOption *currentAudioDescriptionOption;

/// The currently selected subtitle or caption track. Should be one of the options in `legibleOptions`. Must be key-value observable.
@property (nonatomic, readwrite, copy, nullable) AVPlaybackUserInterfaceMediaSelectionOption *currentLegibleOption;

/// Array of available audio track options. This includes all audio streams provided by the media source such as different languages, director's commentary, and alternative audio mixes.
/// Options are ordered by preference with the primary language or default audio track typically appearing first. May be empty for content without selectable audio options. Must be key-value observable.
@property (nonatomic, readonly, copy) NSArray<AVPlaybackUserInterfaceMediaSelectionOption *> *audioOptions;

/// Array of available audio description track options. Audio description tracks provide narrated descriptions of visual content for visually impaired viewers.
/// Audio description options are distinct from those in `audioOptions` — they provide a narration layer played alongside the primary audio rather than replacing it.
/// Options are ordered by preference with the primary language or default audio description track typically appearing first. May be empty for content without audio description tracks. Must be key-value observable.
@property (nonatomic, readonly, copy) NSArray<AVPlaybackUserInterfaceMediaSelectionOption *> *audioDescriptionOptions;

/// Array of available subtitle and caption track options. This includes text overlays in different languages, closed captions for accessibility, forced narrative subtitles, and sign language interpretation tracks.
/// May be empty for content without text tracks. Must be key-value observable.
@property (nonatomic, readonly, copy) NSArray<AVPlaybackUserInterfaceMediaSelectionOption *> *legibleOptions;

@end

/*!
 Provides volume and audio muting control for media content.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVPlaybackUserInterfaceVolumeControllable <NSObject>

/// Indicates whether the media contains audio tracks and can produce sound output. Returns NO for video-only content, silent content, or when audio tracks are unavailable. Must be key-value observable.
@property (nonatomic, readonly) BOOL hasAudio;

/// Controls whether audio output is temporarily silenced. When YES, audio is muted regardless of the volume level setting. Must be key-value observable.
@property (nonatomic, readwrite, getter = isMuted) BOOL muted;

/// The audio output volume as a normalized value between 0.0 and 1.0. Must be key-value observable.
@property (nonatomic, readwrite) float volume;

@end

/*!
 Provides metadata information about media content including title, artwork, and content type.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVPlaybackUserInterfaceMetadataProviding <NSObject>

/// The metadata object containing information about the media content. Must be key-value observable.
@property (nonatomic, readonly, copy) AVPlaybackUserInterfaceContentMetadata *metadata;

@end

/*!
 A comprehensive protocol that provides complete media control and information for playback, timeline navigation, audio/subtitle selection, volume control, and metadata access.
 
 This protocol consolidates all media source capabilities into a single interface, enabling rich media experiences with full control over playback state, timeline interactions, and content metadata. Implementations should provide key-value observable properties where specified to ensure proper integration with media player controls and UI frameworks.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVPlaybackUserInterfaceControllable <	AVPlaybackUserInterfaceTimeControllable,
												AVPlaybackUserInterfacePlaybackControllable,
												AVPlaybackUserInterfaceMediaSelectionControllable,
												AVPlaybackUserInterfaceVolumeControllable,
												AVPlaybackUserInterfaceMetadataProviding	>

@end

NS_ASSUME_NONNULL_END
