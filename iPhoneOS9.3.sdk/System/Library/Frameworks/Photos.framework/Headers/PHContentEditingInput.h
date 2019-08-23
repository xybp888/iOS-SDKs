//
//  PHContentEditingInput.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>
#import <Photos/PhotosTypes.h>

@class PHAdjustmentData;
@class AVAsset, AVAudioMix, AVVideoComposition;
@class CLLocation;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(8_0) @interface PHContentEditingInput : NSObject

@property (readonly, assign) PHAssetMediaType mediaType;
@property (readonly, assign) PHAssetMediaSubtype mediaSubtypes;
@property (readonly, copy, nullable) NSDate *creationDate;
@property (readonly, copy, nullable) CLLocation *location;
@property (readonly, copy, nullable) NSString *uniformTypeIdentifier;

// Adjustments to be applied onto the provided input image or video.
@property (readonly, strong) PHAdjustmentData *adjustmentData;

// Input image:
@property (readonly, strong, nullable) UIImage *displaySizeImage;
@property (readonly, copy, nullable) NSURL *fullSizeImageURL;
@property (readonly, assign) int fullSizeImageOrientation; // EXIF value

// Input video:
@property (readonly, strong, nullable) AVAsset *avAsset NS_DEPRECATED_IOS(8_0, 9_0);
@property (readonly, strong, nullable) AVAsset *audiovisualAsset NS_AVAILABLE(NA, 9_0);

@end

NS_ASSUME_NONNULL_END