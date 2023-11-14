//
//  SHMatch.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>
#import <ShazamKit/SHSignature.h>
#import <ShazamKit/SHMatchedMediaItem.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// @brief A @c SHMatch indicates that a Signature matched a reference Signature in the target @c SHCatalog
/// @discussion A @c SHSignature can match many reference Signatures in a catalog and in turn a Signature can map to
/// many @c SHMediaItem. Therefore a match encapsulates the query Signature and all of the various @c SHMediaItem it matched
///
/// @note @c SHMatch is not intended to be subclassed
SH_EXPORT NS_SWIFT_SENDABLE API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHMatch : NSObject <NSSecureCoding>

/// @brief The @c SHMatchedMediaItem belonging to the instance of @c SHSignature that we matched
///
/// @discussion One Signature may match multiple @c SHMediaItem, especially in the case of audio that uses samples. The array of @c SHMatchedMediaItem
/// is ordered by the quality of the match. Use the first @c SHMatchedMediaItem if you intend to only show one result
@property (NS_NONATOMIC_IOSONLY, strong, readonly) NSArray<SHMatchedMediaItem *> *mediaItems;

/// The @c SHSignature used to query the @c SHCatalog
/// @note This Signature is the query Signature, not the reference Signature contained in the @c SHCatalog
@property (NS_NONATOMIC_IOSONLY, strong, readonly) SHSignature *querySignature;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
