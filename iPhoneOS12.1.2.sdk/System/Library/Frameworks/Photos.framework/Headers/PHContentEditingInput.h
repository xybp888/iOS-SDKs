//
//  PHContentEditingInput.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#if !TARGET_OS_OSX
#import <UIKit/UIImage.h>
#endif
#import <Photos/PhotosTypes.h>
#import <Photos/PhotosDefines.h>

@class PHAdjustmentData;
@class AVAsset, AVAudioMix, AVVideoComposition;
@class CLLocation;
@class PHLivePhoto;

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS_OSX(8_0, 10_0, 10_12) @interface PHContentEditingInput : NSObject

@property (readonly, assign) PHAssetMediaType mediaType;
@property (readonly, assign) PHAssetMediaSubtype mediaSubtypes;
@property (readonly, copy, nullable) NSDate *creationDate;
@property (readonly, copy, nullable) CLLocation *location;
@property (readonly, copy, nullable) NSString *uniformTypeIdentifier;

// Playback style describes how the content should be presented to the user.  Use this value to choose the type of view and the appropriate APIs on the content editing input to display this content.
// When editing a live photo with a PHAssetPlaybackStyleLoopingVideo, you should provide an updated video that includes the looping video metadata on the PHContentEditingOutput's renderedContentURL.
@property (nonatomic, assign, readonly) PHAssetPlaybackStyle playbackStyle PHOTOS_AVAILABLE_IOS_TVOS(11_0, 11_0);

// Adjustments to be applied onto the provided input image or video.
@property (readonly, strong, nullable) PHAdjustmentData *adjustmentData;

// Input image:
#if TARGET_OS_OSX
@property (readonly, strong, nullable) NSImage *displaySizeImage;
#else
@property (readonly, strong, nullable) UIImage *displaySizeImage;
#endif
@property (readonly, copy, nullable) NSURL *fullSizeImageURL;
@property (readonly, assign) int fullSizeImageOrientation; // EXIF value

// Input video:
@property (readonly, strong, nullable) AVAsset *avAsset NS_DEPRECATED_IOS(8_0, 9_0);
@property (readonly, strong, nullable) AVAsset *audiovisualAsset PHOTOS_AVAILABLE_IOS_TVOS_OSX(9_0, 10_0, 10_13);

// Input Live Photo:
@property (readonly, strong, nullable) PHLivePhoto *livePhoto PHOTOS_AVAILABLE_IOS_TVOS_OSX(10_0, 10_0, 10_12);

@end

NS_ASSUME_NONNULL_END
