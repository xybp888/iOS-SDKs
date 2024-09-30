//
//  SHCustomCatalog.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>
#import <ShazamKit/SHSignature.h>
#import <ShazamKit/SHMediaItem.h>
#import <ShazamKit/SHCatalog.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// @brief Configure a custom catalog of @c SHSignature objects to match against
/// @discussion Use a custom catalog if you intend to search against reference signatures that you have provided yourself. All matches will be performed locally on the device against the signatures added to this Catalog.
/// @c SHMediaItem can be built using custom data that will be returned when a match is made.
/// Once this catalog has been built it can be written to disk and loaded again at a later date.
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHCustomCatalog : SHCatalog

/// The data representation of this file, it can be written to disk
@property (NS_NONATOMIC_IOSONLY, strong, readonly) NSData *dataRepresentation API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));
 
/// Add a reference @c SHSignature and its associated @c SHMediaItem for matching
/// @param signature The reference to match against
/// @param mediaItems The metadata associated with the @c SHSignature
/// @discussion Once the @c SHCatalog had been added to a @c SHSession further calls to this method will be ignored
/// @return YES if the data was successfully added, NO on failure with a populated error parameter
- (BOOL)addReferenceSignature:(SHSignature *)signature representingMediaItems:(NSArray<SHMediaItem *> *)mediaItems error:(NSError **)error;

/// Load a `shazamcatalog` file from a file path URL
/// @param customCatalogURL The path to the `shazamcatalog` file.
/// @param error An error if the catalog could not be loaded
/// @return YES if the data was successfully added, NO on failure with a populated error parameter
- (BOOL)addCustomCatalogFromURL:(NSURL *)customCatalogURL error:(NSError **)error;

/// Write this Catalog to a URL
/// @discussion A Catalog can safely be shared among devices
/// @note If the `destinationURL` is a directory, a file named Signatures.shazamcatalog will be created
/// @param destinationURL The location to write to
/// @param error populated on error, otherwise nil
/// @return YES on success, NO on failure with a populated error parameter
- (BOOL)writeToURL:(NSURL *)destinationURL error:(NSError **)error API_DEPRECATED("Use dataRepresentation", macos(12.0, 15.0), ios(15.0, 18.0), tvos(15.0, 18.0), watchos(8.0, 11.0));

+ (instancetype)new API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_SWIFT_UNAVAILABLE("Use init in Swift");
- (instancetype)init API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// Load a @c SHCustomCatalog from data
/// @param dataRepresentation The data representation of the @c SHCustomCatalog
/// @param error Error populated if not a valid data representation
- (nullable instancetype)initWithDataRepresentation:(NSData *)dataRepresentation error:(NSError **)error API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
