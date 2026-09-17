//
//  PHAssetExtendedMetadata.h
//  Photos
//
//  Copyright (c) 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PHAsset.h>

NS_ASSUME_NONNULL_BEGIN

/// Represents other asset attributes that are not included when fetching `PHAsset` directly.
/// 
/// When ``/Photos/PHAsset/extendedMetadata`` is called, these properties are fetched. They can be
/// prefetched by toggling ``/Photos/PHFetchOptions/prefetchAssetExtendedMetadata`` when fetching ``/Photos/PHAsset``.
API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27))
OS_EXPORT
NS_SWIFT_SENDABLE
@interface PHAssetExtendedMetadata : NSObject

/// The compact description for this asset.
@property (copy, readonly, nullable) NSString *caption;

/// The original file name of this asset.
@property (copy, readonly, nullable) NSString *originalFilename;

/// The keywords associated with this asset
@property (copy, readonly) NSArray<NSString *> *keywords;

@end

NS_ASSUME_NONNULL_END
