#if !__has_include(<AVFCore/AVAssetVariant.h>)
/*
	File:           AVAssetVariant.h

	Framework:      AVFoundation

	Copyright © 2021-2024 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVVideoSettings.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>
#import <CoreGraphics/CGGeometry.h>
#import <CoreMedia/CMTag.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMediaSelectionOption;
@class AVAssetVariantVideoAttributes;
@class AVAssetVariantVideoLayoutAttributes;
@class AVAssetVariantAudioAttributes;
@class AVAssetVariantAudioRenditionSpecificAttributes;

/*!
  @class		AVAssetVariant
  @abstract		An AVAssetVariant represents a bit rate variant.
				Each asset contains a collection of variants that represent a combination of audio, video, text, closed captions, and subtitles for a particular bit rate.
				Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVAssetVariant : NSObject

AV_INIT_UNAVAILABLE

/*!
 @property		peakBitRate
 @abstract		If it is not declared, the value will be negative.
 */
@property (nonatomic, readonly) double peakBitRate;

/*!
 @property		averageBitRate
 @abstract		If it is not declared, the value will be negative.
 */
@property (nonatomic, readonly) double averageBitRate;

/*!
 @property		videoAttributes
 @abstract		Provides  variant's video rendition attributes. If no video attributes are declared, it will be nil.
 */
@property (nonatomic, readonly, nullable) AVAssetVariantVideoAttributes *videoAttributes;

/*!
 @property		audioAttributes
 @abstract		Provides  variant's audio rendition attributes. If no audio attributes are declared, it will be nil.
 */
@property (nonatomic, readonly, nullable) AVAssetVariantAudioAttributes *audioAttributes;

@end

/*!
 @class			AVAssetVariantVideoAttributes
 @abstract		Video attributes for an asset variant.
 @discussion	Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVAssetVariantVideoAttributes : NSObject

AV_INIT_UNAVAILABLE

/*!
 @property		videoRange
 @abstract		Provides the video range of the variant. If it is not declared, it will be AVVideoRangeSDR.
 */
@property (nonatomic, readonly) AVVideoRange videoRange;

/*!
 @property		codecTypes
 @abstract		Provides an array of video sample codec types present in the variant's renditions if any are declared. Each value in the array is a NSNumber representation of CMVideoCodecType.
 */
@property (nonatomic, readonly) NSArray <NSNumber *> *codecTypes;

/*!
 @property		presentationSize
 @abstract		If it is not declared, it will be CGSizeZero.
 */
@property (nonatomic, readonly) CGSize presentationSize;

/*!
 @property		nominalFrameRate
 @abstract		If it is not declared, the value will be negative.
 */
@property (nonatomic, readonly) double nominalFrameRate;

/*!
	@property	videoLayoutAttributes
	@abstract	Describes the video layout attributes.
	@discussion	videoLayoutAttributes' count may be greater than one if this variant contains a collection of differing video layout media attributes over time.
*/
@property (nonatomic, readonly) NSArray <AVAssetVariantVideoLayoutAttributes *> *videoLayoutAttributes API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

@end

/*!
 @class			AVAssetVariantVideoLayoutAttributes
 @discussion	Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0))
@interface AVAssetVariantVideoLayoutAttributes : NSObject

AV_INIT_UNAVAILABLE

/*!
	@property	stereoViewComponents
	@abstract	Describes the stereo components. If not declared, the value will be `kCMStereoViewComponent_None`. 
				In case of monoscopic content, the value will be `kCMStereoViewComponent_None` and incase of stereoscopic content, the value will be `(kCMStereoViewComponent_LeftEye | kCMStereoViewComponent_RightEye)`.
*/
@property (nonatomic, readonly) CMStereoViewComponents stereoViewComponents;

@end

/*!
 @class         AVAssetVariantAudioAttributes
 @abstract      Audio attributes for an asset variant.
 @discussion    Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVAssetVariantAudioAttributes : NSObject

AV_INIT_UNAVAILABLE

/*!
 @property		formatIDs
 @abstract		Provides an array of audio formats present in the variant's renditions if any are declared. Each value in the array is a NSNumber representation of AudioFormatID.
 */
@property (nonatomic, readonly) NSArray <NSNumber *> *formatIDs;

/*!
 @method		renditionSpecificAttributesForMediaOption:
 @abstract		Provides attributes for a specific audio media selection option. If no rendition specific attributes are declared, it will be nil.
 @param			mediaSelectionOption
				The option to return rendition specific information for.
 */
- (nullable AVAssetVariantAudioRenditionSpecificAttributes *)renditionSpecificAttributesForMediaOption:(AVMediaSelectionOption *)mediaSelectionOption;

@end

/*!
 @class         AVAssetVariantAudioRenditionSpecificAttributes
 @abstract      Audio rendition attributes for an asset variant.
 @discussion    Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVAssetVariantAudioRenditionSpecificAttributes : NSObject

/*!
 @property		channelCount
 @abstract		If it is not declared, the value will be negative.
 @discussion	A channel count greater than two indicates that the variant offers a rich multichannel authoring.
 */
@property (nonatomic, readonly) NSInteger channelCount;

/*!
 @property		binaural
 @abstract		Indicates that the variant is best suited for delivery to headphones.
 @discussion 	A binaural variant may originate from a direct binaural recording or from the processing of a multichannel audio source.
*/
@property (nonatomic, readonly, getter=isBinaural) BOOL binaural API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/*!
 @property		immersive
 @abstract		Indicates that this variant contains virtualized or otherwise pre-processed audio content that is suitable for a variety of purposes.
 @discussion 	If a variant audio redition is immersive it is eligible for rendering either to headphones or speakers.
*/
@property (nonatomic, readonly, getter=isImmersive) BOOL immersive API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @property		downmix
 @abstract		Indicates that this variant is declared as a downmix derivative of other media of greater channel count.
 @discussion	If one or more multichannel variants are also provided, the dowmix is assumed to be compatible in its internal timing and other attributes with those variants. Typically this is because it has been derived from the same source. A downmix can be used as a suitable substitute for a multichannel variant under some conditions.
*/
@property (nonatomic, readonly, getter=isDownmix) BOOL downmix API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

@end

/*!
 @class         AVAssetVariantQualifier
 @abstract      The qualifier of an asset variant.
 @discussion    Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(10.0), visionos(1.0))
@interface AVAssetVariantQualifier : NSObject <NSCopying>

AV_INIT_UNAVAILABLE

/*!
 @method 		assetVariantQualifierWithPredicate:
 @abstract		Returns a qualifer for a predicate.
 @param			predicate
				The variant predicate. Must be a valid, non-nil NSPredicate.
 */
+ (instancetype)assetVariantQualifierWithPredicate:(nonnull NSPredicate *)predicate;

/*!
 @method 		assetVariantQualifierWithVariant:
 @abstract		Returns a qualifer for a particular asset variant.
 @param			variant
				A variant obtained from the -[AVAsset variants] or -[AVAssetDownloadConfiguration playableVariants]. Must be a valid, non-nil AVAssetVariant.
 */
+ (instancetype)assetVariantQualifierWithVariant:(nonnull AVAssetVariant *)variant;

/*!
 @method 		assetVariantQualifierForMinimumValueInKeyPath:
 @abstract		Returns a qualifer for finding variant with minimum value in the input key path.
 @param			keyPath
				AVAssetVariant keyPath. Allowed keyPath values are peakBitRate, averageBitRate, videoAttributes.presentationSize. Must be a valid, non-nil NSString.
 */

+ (instancetype)assetVariantQualifierForMinimumValueInKeyPath:(nonnull NSString *)keyPath API_UNAVAILABLE(macos, ios, tvos, watchos, visionos);

/*!
 @method 		assetVariantQualifierForMaximumValueInKeyPath:
 @abstract		Returns a qualifer for finding variant with maximum value in the input key path
 @param			keyPath
				AVAssetVariant keyPath. Allowed keyPath values are peakBitRate, averageBitRate, videoAttributes.presentationSize. Must be a valid, non-nil NSString.
 */
+ (instancetype)assetVariantQualifierForMaximumValueInKeyPath:(nonnull NSString *)keyPath API_UNAVAILABLE(macos, ios, tvos, watchos, visionos);

/*!
 @method		predicateForChannelCount:mediaSelectionOption:operatorType:
 @abstract		Creates a NSPredicate for audio channel count which can be used with other NSPredicates to express variant preferences.
 @param			channelCount
				The RHS value for the channel count in the predicate equation.
 @param			mediaSelectionOption
				The audio media selection option under consideration.
 @param			operatorType
				The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
 */
+ (NSPredicate *)predicateForChannelCount:(NSInteger)channelCount mediaSelectionOption:(AVMediaSelectionOption *)mediaSelectionOption operatorType:(NSPredicateOperatorType)operatorType;

/*!
 @method		predicateForBinauralAudio:mediaSelectionOption:
 @abstract		Creates a NSPredicate for binaural which can be used with other NSPredicates to express variant preferences.
 @param			isBinaural
				The RHS value for the value of isBinauralAudio in the predicate equation.
 @param			mediaSelectionOption
				The audio media selection option under consideration.
 */
+ (NSPredicate *)predicateForBinauralAudio:(BOOL)isBinauralAudio mediaSelectionOption:(AVMediaSelectionOption *)mediaSelectionOption API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @method		predicateForImmersiveAudio:mediaSelectionOption:
 @abstract		Creates a NSPredicate for immersive audio which can be used with other NSPredicates to express variant preferences.
 @param			isImmersiveAudio
				The RHS value for the value of isImmersiveAudio in the predicate equation.
 @param			mediaSelectionOption
				The audio media selection option under consideration.
 */
+ (NSPredicate *)predicateForImmersiveAudio:(BOOL)isImmersiveAudio mediaSelectionOption:(AVMediaSelectionOption *)mediaSelectionOption API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @method		predicateForDownmixAudio:mediaSelectionOption:
 @abstract		Creates a NSPredicate for immersive audio which can be used with other NSPredicates to express variant preferences.
 @param			isDownmixAudio
				The RHS value for the value of isDownmixAudio in the predicate equation.
 @param			mediaSelectionOption
				The audio media selection option under consideration.
 */
+ (NSPredicate *)predicateForDownmixAudio:(BOOL)isDownmixAudio mediaSelectionOption:(AVMediaSelectionOption *)mediaSelectionOption API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @method		predicateForPresentationWidth:operatorType:
 @abstract		Creates a NSPredicate for presentation size width which can be used with other NSPredicates to express variant preferences.
 @param			width
				The RHS value for the presentation size width in the predicate equation.
 @param			operatorType
				The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
 */
+ (NSPredicate *)predicateForPresentationWidth:(CGFloat)width operatorType:(NSPredicateOperatorType)operatorType;

/*!
 @method		predicateForPresentationHeight:operatorType:
 @abstract		Creates a NSPredicate for presentation size height which can be used with other NSPredicates to express variant preferences.
 @param			height
				The RHS value for the presentation size height in the predicate equation.
 @param			operatorType
				The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
 */
+ (NSPredicate *)predicateForPresentationHeight:(CGFloat)height operatorType:(NSPredicateOperatorType)operatorType;

/*!
 @method		predicateForAudioSampleRate:mediaSelectionOption:operatorType:
 @abstract		Creates a NSPredicate for audio sample rate which can be used with other NSPredicates to express variant preferences.
 @param			sampleRate
				The RHS value for the sample rate in the predicate equation.
 @param			mediaSelectionOption
				The audio media selection option under consideration.
 @param			operatorType
				The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
 */
+ (NSPredicate *)predicateForAudioSampleRate:(double)sampleRate mediaSelectionOption:(AVMediaSelectionOption *)mediaSelectionOption operatorType:(NSPredicateOperatorType)operatorType API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetVariant.h>
#endif
