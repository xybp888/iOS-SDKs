//
//  PHCloudIdentifier.h
//  Photos
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <Photos/PHPhotoLibrary.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE_BEGIN(macos(10.13), ios(15), tvos(15))


OS_EXPORT
NS_SWIFT_SENDABLE
/*!
 A representation of a globally unique identifier for a PHAsset or PHCollection that can be used to identify the same asset or collection across different devices and photo libraries.

 Cloud identifiers are designed to work best when used with an account that has iCloud Photos enabled, but they also work on libraries that are not synced via iCloud Photos, including on devices that have never been signed in to an iCloud account. Use ``PHPhotoLibrary/cloudIdentifierMappingsForLocalIdentifiers:`` and ``PHPhotoLibrary/localIdentifierMappingsForCloudIdentifiers:`` to map between cloud identifiers and local identifiers.

 When resolving a cloud identifier to a local identifier, ``PHPhotoLibrary/localIdentifierMappingsForCloudIdentifiers:`` first looks for a record synced through iCloud Photos. If no synced record is found — for example, when resolving cloud identifiers between libraries on devices that do not have iCloud Photos enabled — it falls back to matching on media content, which may return more than one local identifier for a single cloud identifier (see `PHPhotosErrorMultipleLocalIdentifiersFound`). To skip the media-content fallback and only resolve identifiers backed by iCloud Photos synced records, use ``PHPhotoLibrary/localIdentifierMappingsForSyncedCloudIdentifiers:``.
 */
@interface PHCloudIdentifier : NSObject <NSSecureCoding>

/// DEPRECATED: If there is a failure to determine the global identifier for a local identifier, the notFoundIdentifier is provided in that array slot.
@property (class, nonatomic, readonly) PHCloudIdentifier *notFoundIdentifier

API_DEPRECATED("Check for PHPhotosErrorIdentifierNotFound in PHCloudIdentifierMapping.error", macos(10.13, 12)) API_UNAVAILABLE(ios, macCatalyst, tvos);


/// Archival string can be used to serialize and deserialize the PHCloudIdentifier
/// (Note the archival format is compatible with strings archived via the deprecated API `stringValue`)
- (nullable instancetype)initWithArchivalStringValue:(NSString *)archivalString API_AVAILABLE(macos(15.2), ios(18.2), tvos(18.2), visionos(2.2));
@property (nonatomic, readonly) NSString *archivalStringValue API_AVAILABLE(macos(15.2), ios(18.2), tvos(18.2), visionos(2.2));


- (instancetype)initWithStringValue:(NSString *)stringValue API_DEPRECATED("Use initWithArchivalStringValue: instead", macos(10.13, 27), ios(13, 27), tvos(13, 27), visionos(1, 27));
@property (nonatomic, readonly) NSString *stringValue API_DEPRECATED_WITH_REPLACEMENT("archivalStringValue", macos(10.13, 27), ios(13, 27), tvos(13, 27), visionos(1, 27));



@end

API_AVAILABLE_END
API_AVAILABLE_BEGIN(macos(12), ios(15), tvos(15))
/// Contains the cloud identifier result from looking up a local identifier via `cloudIdentifierMappingsForLocalIdentifiers`, or an `error` indicating why the lookup failed
OS_EXPORT NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface PHCloudIdentifierMapping : NSObject
/// The cloud identifier of the record found for this local identifier
@property (nonatomic, readonly, nullable) PHCloudIdentifier *cloudIdentifier;
/// An error indicating why the `cloudIdentifier` is `nil`. `PHPhotosErrorIdentifierNotFound` if no record could be found for the provided local identifier.
@property (nonatomic, readonly, nullable) NSError *error;
@end

/// Contains the local identifier result from looking up a cloud identifier via `localIdentifierMappingsForCloudIdentifiers`, or an `error` indicating why the lookup failed
OS_EXPORT NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface PHLocalIdentifierMapping : NSObject
/// The `NSString` representing the local identifier of the record found for this cloud identifier, or nil if the match was not found.
@property (nonatomic, readonly, nullable) NSString *localIdentifier;
/// An error indicating why the `localIdentifier` is `nil`. `PHPhotosErrorIdentifierNotFound` if no record could be found for the provided cloud identifier. `PHPhotosErrorMultipleLocalIdentifiersFound` if the cloud identifier matched more than one photo library record, so there were multiple local identifiers found. The array of matching local identifiers can be retrieved from the error's user info via the `PHLocalIdentifiersErrorKey`
@property (nonatomic, readonly, nullable) NSError *error;
@end

@interface PHCloudIdentifier () <NSCopying>
@end
API_AVAILABLE_END



#pragma mark - CloudIdentifiers


API_AVAILABLE_BEGIN(macos(10.13), ios(15), tvos(15))

@interface PHPhotoLibrary (CloudIdentifiers)
/*!
 Returns a dictionary that maps each cloud identifier from the provided array to a `PHLocalIdentifierMapping` result containing the local identifier found for that cloud identifier.
 
 This method can be very expensive so they should be used sparingly for batch lookup of all needed identifiers. Clients should work in terms of local identifiers and call these methods only once after loading from and before saving to persistent storage.  If the attempt to lookup a local identifier for a given cloud identifier fails, the error parameter will indicate the reason.
 
 Note that cloud identifiers are designed to lookup local identifiers for records that are synced through iCloud Photo Library, but also support lookup in the following situations:
 - looking up local identifiers with cloud identifiers generated from the same library, even if that library is not synced via iCloud Photo Library
 - looking up PHAsset local identifiers based on media content matching if the cloud identifier hasn't synced to the device library, note that this can potentially map a cloud identifier to more than one local identifier if the cloud identifier hasn't synced and there are multiple PHAsset records with the same media content (see `PHPhotosErrorMultipleLocalIdentifiersFound`). To avoid using media matching as part of the mapping lookup strategy, use `localIdentifierMappingsForSyncedCloudIdentifiers:` instead.
 
 - Parameters:
 - cloudIdentifiers The array of `PHCloudIdentifier` instances whose local identifiers are being requested.
 */
- (NSDictionary <PHCloudIdentifier *, PHLocalIdentifierMapping *> *)localIdentifierMappingsForCloudIdentifiers:(NSArray<PHCloudIdentifier *> *)cloudIdentifiers API_AVAILABLE(macos(12), ios(15), tvos(15)) NS_REFINED_FOR_SWIFT;

/*!
 Returns a dictionary that maps each cloud identifier from the provided array to a `PHLocalIdentifierMapping` result containing the local identifier found for that cloud identifier if that cloud identifier is a known synced identifier.

 This method can be very expensive so they should be used sparingly for batch lookup of all needed identifiers. Clients should work in terms of local identifiers and call these methods only once after loading from and before saving to persistent storage.  If the attempt to lookup a local identifier for a given cloud identifier fails, the error parameter will indicate the reason.
 
 Use this method instead of `localIdentifierMappingsForCloudIdentifiers:` to avoid looking up PHAsset local identifiers based on the media content matching
 
 - Parameters:
 - cloudIdentifiers The array of `PHCloudIdentifier` instances whose local identifiers are being requested.
 */
- (NSDictionary <PHCloudIdentifier *, PHLocalIdentifierMapping *> *)localIdentifierMappingsForSyncedCloudIdentifiers:(NSArray<PHCloudIdentifier *> *)cloudIdentifiers API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27)) NS_REFINED_FOR_SWIFT;

/*!
 Returns a dictionary that maps each local identifier from the provided array to a `PHCloudIdentifierMapping` result containing the cloud identifier found for that local identifier
 
 This method can be very expensive so they should be used sparingly for batch lookup of all needed identifiers. Clients should work in terms of local identifiers and call these methods only once after loading from and before saving to persistent storage.  If the attempt to lookup a cloud identifier for a given local identifier fails, the error parameter will indicate the reason.
 - Parameters:
 - localIdentifiers The array of `NSString` instances whose cloud identifiers are being requested.
 */
- (NSDictionary <NSString *, PHCloudIdentifierMapping *> *)cloudIdentifierMappingsForLocalIdentifiers:(NSArray<NSString *> *)localIdentifiers API_AVAILABLE(macos(12), ios(15), tvos(15)) NS_REFINED_FOR_SWIFT;

/// DEPRECATED: These two methods can be very expensive so they should be used sparingly for batch lookup of all needed identifiers. Clients should work in terms of local identifiers and call these methods only once after loading from and before saving to persistent storage.
- (NSArray<NSString *> *)localIdentifiersForCloudIdentifiers:(NSArray<PHCloudIdentifier *> *)cloudIdentifiers

API_DEPRECATED("Use localIdentifierMappingsForCloudIdentifiers: instead", macos(10.13, 12)) API_UNAVAILABLE(ios, macCatalyst, tvos);

- (NSArray<PHCloudIdentifier *> *)cloudIdentifiersForLocalIdentifiers:(NSArray<NSString *> *)localIdentifiers

API_DEPRECATED("Use cloudIdentifierMappingsForLocalIdentifiers: instead", macos(10.13, 12)) API_UNAVAILABLE(ios, macCatalyst, tvos);


@end

/// DEPRECATED: If the local object cannot be resolved from a global identifier, `PHLocalIdentifierNotFound` is provided in that array slot.
extern NSString * const PHLocalIdentifierNotFound

API_DEPRECATED("Check for PHPhotosErrorIdentifierNotFound in PHLocalIdentifierMapping.error", macos(10.13, 12)) API_UNAVAILABLE(ios, macCatalyst, tvos);


API_AVAILABLE_END
NS_ASSUME_NONNULL_END
