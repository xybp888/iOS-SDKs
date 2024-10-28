//
//  SHMediaItem.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>
#import <ShazamKit/SHRange.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
typedef NSString * SHMediaItemProperty NS_TYPED_EXTENSIBLE_ENUM;

/// The Shazam media ID
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemShazamID;

/// Title
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemTitle;

/// Subtitle
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemSubtitle;

/// Artist
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemArtist;

/// A web URL representing this result
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemWebURL;

/// The AppleMusic ID
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemAppleMusicID;

/// A link to this media on Apple Music
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemAppleMusicURL;

/// A URL to the artwork
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemArtworkURL;

/// A URL for a Video associated with the media
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemVideoURL;

/// Is this content explicit
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemExplicitContent;

/// An array of strings representing the genres of the media item
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemGenres;

/// The International Standard Recording Code
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
SH_EXPORT SHMediaItemProperty const SHMediaItemISRC;

/// The time ranges in the represented media that are described by this @c SHMediaItem
SH_EXPORT SHMediaItemProperty const SHMediaItemTimeRanges API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_REFINED_FOR_SWIFT;

/// The frequency skew ranges that are described by this @c SHMediaItem
SH_EXPORT SHMediaItemProperty const SHMediaItemFrequencySkewRanges API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_REFINED_FOR_SWIFT;

/// The date when the media item was created
SH_EXPORT SHMediaItemProperty const SHMediaItemCreationDate API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// @brief @c SHMediaItem represents metadata associated with a @c SHSignature
/// @discussion A @c SHMediaItem is used in two distinct ways
///     1. As the base class of a @c SHMatchedMediaItem, and therefore as the result of a match
///     2. As a way of associating metadata with reference signatures in a @c SHCustomCatalog
///
/// A SHMediaItem contains no required fields and may be entirely blank, they can also contain custom data set with custom keys when making a @c SHCustomCatalog.
/// 
/// @note @c SHMediaItem  is not intended to be subclassed further.
SH_EXPORT NS_SWIFT_SENDABLE API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHMediaItem : NSObject <NSSecureCoding, NSCopying>

/// The Shazam Media ID
/// @note This may be fetched using the key @c SHMediaItemShazamID
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *shazamID;

/// The Title
/// @note This may be fetched using the key @c SHMediaItemTitle
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *title;

/// The Subtitle
/// @note This may be fetched using the key @c SHMediaItemSubtitle
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *subtitle;

/// The Artist
/// @note This may be fetched using the key @c SHMediaItemArtist
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *artist;

/// The Genre Names
/// @note This may be fetched using the key @c SHMediaItemGenres
/// @discussion An array of strings representing the genres of the media item. Will return an empty array if there are no genres.
@property (NS_NONATOMIC_IOSONLY, strong, readonly) NSArray<NSString *> *genres;

/// The Apple Music ID
/// @note This may be fetched using the key @c SHMediaItemAppleMusicID
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *appleMusicID;

/// The Apple Music URL
/// @note This may be fetched using the key @c SHMediaItemAppleMusicURL
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *appleMusicURL;

/// The Web URL
/// @discussion The URL will point to a page that displays the current object in its entirety
/// @note This may be fetched using the key @c SHMediaItemWebURL
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *webURL;

/// The Artwork URL
/// @note This may be fetched using the key @c SHMediaItemArtworkURL
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *artworkURL;

/// The VideoURL
/// @note This may be fetched using the key @c SHMediaItemVideoURL
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSURL *videoURL;

/// @brief Whether this object represents explicit material
/// @note This may be fetched using the key @c SHMediaItemExplicitContent
@property (NS_NONATOMIC_IOSONLY, assign, readonly) BOOL explicitContent;

/// @brief The International Standard Recording Code
/// @note This may be fetched using the key @c SHMediaItemISRC
@property (NS_NONATOMIC_IOSONLY, copy, readonly, nullable) NSString *isrc;

/// @brief An array of @c SHRange that indicate the offsets within the reference signature that this media item describes
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nonnull) NSArray<SHRange *> *timeRanges API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_REFINED_FOR_SWIFT;

/// @brief An array of @c SHRange that indicate the frequency skews in the reference signature that this media item describes
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nonnull) NSArray<SHRange *> *frequencySkewRanges API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_REFINED_FOR_SWIFT;

/// @brief The date when the @c SHMediaItem was created
/// @note This may be fetched using the key @c SHMediaItemCreationDate
@property (NS_NONATOMIC_IOSONLY, strong, readonly, nullable) NSDate *creationDate API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// Construct a new instance with the provided dictionary
/// @param properties A dictionary of @c SHMediaItemProperty and their values
/// @discussion You may add your own keys here to return custom data, custom data should conform to NSCoding
+ (instancetype)mediaItemWithProperties:(NSDictionary<SHMediaItemProperty, id> *)properties NS_REFINED_FOR_SWIFT;

#if !0
/// @brief Fetch a @c SHMediaItem by Shazam ID
/// @discussion The completionHandler will contain a @c SHMediaItem if the ShazamID is valid, otherwise nil and an error
+ (void)fetchMediaItemWithShazamID:(NSString *)shazamID completionHandler:(void (NS_SWIFT_SENDABLE ^)(SHMediaItem * __nullable mediaItem, NSError * __nullable error))completionHandler NS_SWIFT_NAME(fetch(shazamID:completionHandler:));
#endif

/// Retrieve a value using a known key
/// @param property The `SHMediaItemProperty` for a value
- (id)valueForProperty:(SHMediaItemProperty)property NS_SWIFT_UNAVAILABLE("Use subscripting in Swift");

/// Use subscripting to retrieve values
/// @param key The `SHMediaItemProperty` or custom key for a value
- (id)objectForKeyedSubscript:(SHMediaItemProperty)key;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
