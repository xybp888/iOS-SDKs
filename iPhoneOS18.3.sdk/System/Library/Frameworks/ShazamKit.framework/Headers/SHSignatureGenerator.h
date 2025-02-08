//
//  SHSignatureGenerator.h
//  ShazamKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#if __has_include(<AVFoundation/AVFoundation.h>)
#import <AVFoundation/AVFoundation.h>
#else
#import <AVFAudio/AVFAudio.h>
#endif

#import <ShazamKit/SHSignature.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// @brief @c SHSignatureGenerator provides a way to convert audio data into instances of @c SHSignature
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHSignatureGenerator : NSObject

#if __has_include(<AVFoundation/AVFoundation.h>)
/// Create a `SHSignature` from an @c AVAsset.
/// @param asset An AVAsset that contains audio you would like to convert to a Signature
/// @discussion The asset can be any type of media that has audio tracks. If the asset has multiple tracks, they
/// will be mixed into one @c SHSignature
/// @param completionHandler A block called with the created @c SHSignature or nil and a populated error parameter if a signature could not be created.
+ (void)generateSignatureFromAsset:(AVAsset *)asset completionHandler:(void (^)(SHSignature * __nullable signature, NSError * __nullable error))completionHandler API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_SWIFT_ASYNC_NAME(signature(from:));
#endif

/// @brief Add audio to the generator
/// @discussion Audio passed to the generator should be contiguous, passing non contiguous data will affect the quality of the @c SHSignature
/// produced. Passing the @c AVAudioTime is not required but recommended, it allows the generator to detect when the audio is not contiguous.
/// This method only accepts PCM audio formats. The following sample rates are recommended but not required: 48000, 44100, 32000, 16000.
/// @param time Where in the stream the audio represents
/// @param buffer The audio data to be appended to the signature
/// @param error An error if there was an issue appending the buffer
- (BOOL)appendBuffer:(AVAudioPCMBuffer *)buffer atTime:(nullable AVAudioTime *)time error:(NSError **)error;

/// @brief Convert the current audio data into a @c SHSignature
/// @discussion Signature may be called as many times as needed, each time producing a @c SHSignature from
/// the audio data
- (SHSignature *)signature;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
