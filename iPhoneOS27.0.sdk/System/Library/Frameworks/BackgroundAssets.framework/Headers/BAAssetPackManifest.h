//
//  BAAssetPackManifest.h
//  Background Assets
//
//  Created by Gabriel Jacoby-Cooper on 3/10/25.
//

#import <BackgroundAssets/BAAssetPack.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A manifest of asset packs that are available to download.
API_AVAILABLE(ios(26), macos(26), tvos(26), visionos(26))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface BAAssetPackManifest : NSObject

/// The asset packs in this manifest that are available to download.
@property (readonly, copy) NSSet<BAAssetPack*>* assetPacks;

/// The application’s primary language, represented as a BCP-47 identifier, as configured in App Store Connect.
///
/// If no available localized asset packs match the current preferred languages, the system falls back on the application’s primary language.
@property (nullable, readonly, copy) NSString* primaryLanguage
API_AVAILABLE(ios(27), macos(27), tvos(27), visionos(27))
NS_SWIFT_NAME(primaryLanguageID);

/// The languages, represented as their respective BCP-47 identifiers, for which asset packs in this manifest are localized.
@property (readonly, copy) NSArray<NSString*>* availableLanguages
API_AVAILABLE(ios(27), macos(27), tvos(27), visionos(27))
NS_SWIFT_NAME(availableLanguageIDs);

/// The language, represented as a BCP-47 identifier, asset packs in this manifest that are localized for which the system automatically makes available locally.
///
/// The user’s preferred languages inform the choice of resolved language, respecting any language that your application sets manually by setting ``BAAssetPackManager/resolvedLanguage``. This property may be `nil` if no localized asset packs are available. If the user recently changed their preferred language or if this manifest is outdated, this property’s value may be out of sync with the set of asset packs available locally.
@property (nullable, readonly, copy) NSString* resolvedLanguage
API_AVAILABLE(ios(27), macos(27), tvos(27), visionos(27))
NS_SWIFT_NAME(resolvedLanguageID);

/// The subset of asset packs in this manifest that best match the current preferred languages.
@property (readonly, copy) NSSet<BAAssetPack*>* localizedAssetPacks
API_AVAILABLE(ios(27), macos(27), tvos(27), visionos(27));

- (null_unspecified instancetype)init NS_UNAVAILABLE;

/// Initializes a representation of a manifest in memory given a URL to the manifest’s representation as a JSON file on disk.
/// - Parameters:
///   - URL: A URL to a local JSON file.
///   - applicationGroupIdentifier: The identifier of the application group in which to store unmanaged asset packs that are downloaded from the manifest.
///   - error: A pointer to an error that will be set if an error occurs.
- (nullable instancetype)initWithContentsOfURL:(NSURL*)URL
                    applicationGroupIdentifier:(NSString*)applicationGroupIdentifier
                                         error:(NSError* _Nullable * _Nullable)error
NS_SWIFT_NAME(init(contentsOf:appGroupID:));

/// Initializes a representation of a manifest in memory from JSON-encoded data.
/// - Parameters:
///   - data: JSON-encoded data.
///   - applicationGroupIdentifier: The identifier of the application group in which to store unmanaged asset packs that are downloaded from the manifest.
///   - error: A pointer to an error that will be set if an error occurs.
- (nullable instancetype)initFromData:(NSData*)data
           applicationGroupIdentifier:(NSString*)applicationGroupIdentifier
                                error:(NSError* _Nullable * _Nullable)error
NS_SWIFT_NAME(init(from:appGroupID:));

+ (null_unspecified instancetype)new NS_UNAVAILABLE;

/// Returns the asset pack in this manifest with the given identifier.
/// - Parameter assetPackIdentifier: The asset pack’s identifier.
/// - Returns: The asset pack, if it could be found in this manifest; otherwise, `nil`.
- (nullable BAAssetPack*)assetPackWithIdentifier:(NSString*)assetPackIdentifier
API_AVAILABLE(ios(27), macos(27), tvos(27), visionos(27))
NS_SWIFT_NAME(assetPack(withID:));

/// Returns the subset of asset packs in this manifest that are available to download and that best match the specified language.
///
/// Depending on which languages are available, the returned asset packs’ respective languages may not exactly match the specified language.
/// - Parameter languageIdentifier: The language’s BCP-47 identifier.
/// - Returns: The localized asset packs.
- (NSSet<BAAssetPack*>*)localizedAssetPacksForLanguage:(NSString*)languageIdentifier
API_AVAILABLE(ios(27), macos(27), tvos(27), visionos(27))
NS_SWIFT_NAME(localizedAssetPacks(forLanguageWithID:));

/// Creates download objects for every asset pack in this manifest.
///
/// The returned download objects can be scheduled with the download manager.
/// - Returns: A collection of download objects.
/// - Remark: Use this method in your main application; use ``allDownloadsForContentRequest:`` in your downloader extension.
- (NSSet<BADownload*>*)allDownloads;

/// Creates download objects for every asset pack in this manifest.
///
/// The returned download objects can be scheduled with the download manager.
/// - Parameter contentRequest: The content request for the current extension invocation.
/// - Returns: A collection of download objects.
/// - Remark: Use this method in your downloader extension; use ``allDownloads`` instead in your main application.
- (NSSet<BADownload*>*)allDownloadsForContentRequest:(BAContentRequest)contentRequest;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
