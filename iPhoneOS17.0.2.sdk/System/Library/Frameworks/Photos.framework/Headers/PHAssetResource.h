//
//  PHAssetResource.h
//  Photos
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>

@class PHAsset;
@class PHLivePhoto;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(9), tvos(10))

OS_EXPORT
@interface PHAssetResource : NSObject

@property (nonatomic, assign, readonly) PHAssetResourceType type;
@property (nonatomic, copy, readonly) NSString *assetLocalIdentifier;
@property (nonatomic, copy, readonly) NSString *uniformTypeIdentifier;
@property (nonatomic, copy, readonly) NSString *originalFilename;

@property (nonatomic, assign, readonly) NSInteger pixelWidth API_AVAILABLE(macos(13), ios(16), tvos(16));
@property (nonatomic, assign, readonly) NSInteger pixelHeight API_AVAILABLE(macos(13), ios(16), tvos(16));

#pragma mark - Getting resources

+ (NSArray<PHAssetResource *> *)assetResourcesForAsset:(PHAsset *)asset;
+ (NSArray<PHAssetResource *> *)assetResourcesForLivePhoto:(PHLivePhoto *)livePhoto API_AVAILABLE(ios(9.1));

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
