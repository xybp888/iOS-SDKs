/*
    File:  AVCaptureAudioPreviewOutput.h
 	
 	Framework:  AVFoundation
 
	Copyright 2010-2016 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureOutput.h>


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

#pragma mark - AVCaptureAudioPreviewOutput

@class AVCaptureAudioPreviewOutputInternal;

/*!
 @class AVCaptureAudioPreviewOutput
 @abstract
    AVCaptureAudioPreviewOutput is a concrete subclass of AVCaptureOutput that can be used to preview the audio being captured.
 
 @discussion
    Instances of AVCaptureAudioPreviewOutput have an associated Core Audio output device that can be used to play audio being captured by the capture session. The unique ID of a Core Audio device can be obtained from its kAudioDevicePropertyDeviceUID property.
 */
NS_CLASS_AVAILABLE(10_7, NA) __TVOS_PROHIBITED
@interface AVCaptureAudioPreviewOutput : AVCaptureOutput 
{
@private
	AVCaptureAudioPreviewOutputInternal *_internal;
}

/*!
 @property outputDeviceUniqueID
 @abstract
    Specifies the unique ID of the Core Audio output device being used to play preview audio.

 @discussion
    The value of this property is an NSString containing the unique ID of the Core Audio device to be used for output, or nil if the default system output should be used.
 */
@property(nonatomic, copy) NSString *outputDeviceUniqueID;

/*!
 @property volume
 @abstract
    Specifies the preview volume of the output.

 @discussion
    The value of this property is the preview volume of the receiver, where 1.0 is the maximum volume and 0.0 is muted. 
 */
@property(nonatomic) float volume;

@end

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
