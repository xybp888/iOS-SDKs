//
//  CNSpatialAudio.h
//  Cinematic
//
//  Copyright © 2024-2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
  @enum		CNSpatialAudioRenderingStyle
  @abstract	Standard rendering styles for Audio Mix type effects
 */
typedef NS_ENUM(NSInteger, CNSpatialAudioRenderingStyle) {
	/// Isolates background and foreground sounds and places them in separate stems.
	CNSpatialAudioRenderingStyleCinematic = 0,
	/// Isolates background and foreground in separate stems. Adds a proximity effect to foreground sounds.
	CNSpatialAudioRenderingStyleStudio = 1,
	/// Isolates background from foreground sounds in the camera field of view and places them in separate stems.
	CNSpatialAudioRenderingStyleInFrame = 2,
	/// Isolates background sounds in a stem.
	CNSpatialAudioRenderingStyleCinematicBackgroundStem = 3,
	/// Isolates foreground sounds in a stem.
	CNSpatialAudioRenderingStyleCinematicForegroundStem = 4,
	/// Isolates foreground sounds in a stem, and adds a proximity effect.
	CNSpatialAudioRenderingStyleStudioForegroundStem = 5,
	/// Isolates foreground sounds within the camera field of view in a stem.
	CNSpatialAudioRenderingStyleInFrameForegroundStem = 6,
	/// Produces an unprocessed spatial stem of the original recording. This is the default rendering style.
	CNSpatialAudioRenderingStyleStandard = 7,
	/// Isolates background sounds in a stem.
	CNSpatialAudioRenderingStyleStudioBackgroundStem = 8,
	/// Isolates background plus foreground sounds outside the camera field of view in a stem.
	CNSpatialAudioRenderingStyleInFrameBackgroundStem = 9,
}
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos);

/*!
  @enum		CNSpatialAudioContentType
  @abstract	Enum used to generate settings dictionary for export using AssetReader and AssetWriter with Spatial Audio effects burned in
 */
typedef NS_ENUM(NSInteger, CNSpatialAudioContentType) {
	/// Export settings to generate an asset with stereo audio and effect burned in
	CNSpatialAudioContentTypeStereo,
	/// Export settings to generate an asset with spatial audio and effect burned in
	CNSpatialAudioContentTypeSpatial,
}
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos);

/*!
 @class CNAssetSpatialAudioInfo
 
 @abstract A helper class to inspect recordings made when Spatial Audio setting is turned on. An instance of this class contains the default audio track with Spatial Audio, metadata read from the file that can be applied
	during to enhance the playback experience. This class also provides tunable parameters to change the intensity & mode of the playback experience.
 
 @discussion The goal of this class is to assist users operate on assets in which audio has been captured in multiple formats like Spatial Audio and Stereo to allow more audio customization.
	Users can audition playback of this asset with an immersive audio rendering effect applied by fetching an AVAudioMix containing the necessary metadata serialized in the file as well as any user supplied changes.
	Once the results of the audition are satisfactory, clients can create a copy of the asset with the audio effect burned in.
 */

NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos)
@interface CNAssetSpatialAudioInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new  NS_UNAVAILABLE;

/*!
@property		isSupported
@abstract		Indicates whether the current device supports Audio Mix.
*/
@property (class, readonly) BOOL isSupported;

/*!
 @method		checkIfContainsSpatialAudio:
 @abstract		Check if asset meets all the requirements to operate with Spatial Audio and its accompanying effects
 @param			asset
	An instance of AVAsset.
 @param			completionHandler
	Completion handler to return the result */
+ (void)checkIfContainsSpatialAudio:(AVAsset *)asset completionHandler:(void (^)(BOOL result))completionHandler;

/*!
 @method		loadFromAsset:
 @abstract		Returns an instance of CNAssetAudioInfo for an AVAsset object asynchronously.
 @param		asset
	An instance of AVAsset
 @param		completionHandler
	Completion handler to return the result
 */
+ (void)loadFromAsset:(AVAsset *)asset
		completionHandler:(void (^)(CNAssetSpatialAudioInfo * _Nullable assetInfo,
									NSError * _Nullable error))completionHandler;

@end

@interface CNAssetSpatialAudioInfo (Properties)

/*!
 @property		defaulSpatialAudioTrack
 @abstract		default `AVAssetTrack` containing Spatial Audio
 */
@property (nonatomic, readonly) AVAssetTrack * defaultSpatialAudioTrack;

/*!
 @property		defaultEffectIntensity
 @abstract		default effect intensity value as provided by the system. Supported range is [0.0-1.0]
 */
@property (nonatomic, readonly) float defaultEffectIntensity;

/*!
 @property		defaultRenderingStyle
 @abstract		default rendering style as provided by the system
 */
@property (nonatomic, readonly) CNSpatialAudioRenderingStyle defaultRenderingStyle;

/*!
 @property		spatialAudioMixMetadata
 @abstract		The result of audio analysis during recording which contains metadata necessary to properly configure the Audio Mix feature during playback or editing..
				Can be used with `AUAudioUnit` instances that support AudioUnitPropertyID `kProperty_SpatialAudioMixMetadata`
 */
@property (nonatomic, readonly) NSData *spatialAudioMixMetadata;

@end

@interface CNAssetSpatialAudioInfo (SynthesizeAVFoundationObjects)

/*!
 @method		audioMixWithEffectIntensity:renderingStyle:
 @abstract		returns an instance of `AVAudioMix` encapsulating all spatial audio related data with specified effect intensity and rendering style.
 @discussion    Returns an `AVAudioMix` containing all the necessary state to operate on the asset with Spatial Audio effects enabled
 */
- (AVAudioMix *) audioMixWithEffectIntensity:(float)effectIntensity renderingStyle:(CNSpatialAudioRenderingStyle)renderingStyle;

/*!
 @method		assetReaderOutputSettingsForContentType
 @abstract		Returns a dictionary of settings and the source track that should be used to fetch LPCM samples from this track with the effect applied
 @discussion    Use the returned NSDictionary with the `defaulSpatialAudioTrack` to initialize an instance of `AVAssetReaderAudioMixOutput`
 */
- (NSDictionary<NSString *, id> *) assetReaderOutputSettingsForContentType:(CNSpatialAudioContentType)contentType;

/*!
 @method		assetWriterInputSettingsForContentType
 @abstract		Returns a dictionary of settings that should be used to encode LPCM samples using `AVAssetWriterInput`
 */
- (NSDictionary<NSString *, id> *) assetWriterInputSettingsForContentType:(CNSpatialAudioContentType)contentType;

@end

NS_ASSUME_NONNULL_END
