//
//  SCVideoEffectOutput.h
//  ScreenCaptureKit
//
//  Created by Angelina Ilijevski on 4/24/26.
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#ifndef SCVideoEffectOutput_h
#define SCVideoEffectOutput_h

#import <Foundation/Foundation.h>

@class AVCaptureDevice;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract SCVideoEffectOutput
 @discussion SCVideoEffectOutput represents a camera video effect session on a SCStream. Create an instance and add it to a stream using addVideoEffectOutput:error: to start the camera video effect. The camera preview is framework-managed and automatically added to the application's key window. Callbacks for video effect lifecycle events are delivered through the SCStreamDelegate protocol.
*/
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, macCatalyst, visionos, tvos)
@interface SCVideoEffectOutput : NSObject

/*!
 @abstract initWithCameraDevice:
 @param device The AVCaptureDevice to use for the camera video effect.
 @discussion Creates an SCVideoEffectOutput configured to use the specified camera device for the video effect preview.
*/
- (instancetype)initWithCameraDevice:(AVCaptureDevice *)device;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @abstract cameraDevice
 @discussion The camera device used for the video effect. Can be changed while the video effect is active to switch cameras.
*/
@property (nonatomic, strong) AVCaptureDevice *cameraDevice;

@end

NS_ASSUME_NONNULL_END

#endif /* SCVideoEffectOutput_h */
