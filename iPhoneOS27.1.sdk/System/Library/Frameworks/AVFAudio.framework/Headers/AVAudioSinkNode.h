//
//  AVAudioSinkNode.h
//  AVFAudio
//
//  Copyright © 2018 Apple. All rights reserved.
//

#if __OBJC2__

#import <AVFAudio/AVAudioNode.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAudioFormat;

/*! @typedef AVAudioSinkNodeReceiverBlock
    @abstract Block to receive audio data from AVAudioSinkNode
    @param timestamp
        The time at which the input data will be rendered.
    @param frameCount
        The number of sample frames of input provided.
    @param inputData
        The input audio data.

        The engine will supply valid buffers in inputData's mBuffers' mData and mDataByteSize.
        mDataByteSize will be consistent with frameCount.

        The pointer to the AudioBufferList is only valid within the scope of this block.
    @return
        An OSStatus result code. If an error is returned, the input data should be assumed to be
        invalid.
 */
typedef OSStatus (^ NS_SWIFT_NONSENDABLE AVAudioSinkNodeReceiverBlock)(const AudioTimeStamp *timestamp, AVAudioFrameCount frameCount, const AudioBufferList *inputData) API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0)) ;

/*! @typedef AVAudioSinkNodeReceiverBlockRealtimeSafe
    @abstract
        Identical to AVAudioSinkNodeReceiverBlock, with the addition of a realtime-safety
        guarantee.
*/
typedef OSStatus (^AVAudioSinkNodeReceiverBlockRealtimeSafe)(const AudioTimeStamp *timestamp, AVAudioFrameCount frameCount, const AudioBufferList *inputData) CA_REALTIME_API API_AVAILABLE(macos(27.0), ios(27.0), watchos(27.0), tvos(27.0), visionos(27.0))  __SWIFT_UNAVAILABLE_MSG("Swift is not supported for use with audio realtime threads");

/*! @class AVAudioSinkNode
    @abstract AVAudioSinkNode wraps a client provided block to receive input audio on the audio IO thread.
    @discussion
        AVAudioSinkNode is restricted to be used in the input chain and does not support format
        conversion. Hence when connecting to an AVAudioSinkNode node, the format for the connection
        should be the output scope format of the input node (essentialy the format should match the input hardware
 		sample rate).

		The voice processing IO unit is an exception to the above as it supports sample rate conversion. 
        The input scope format (HW format) and output scope format (client format) of the input node can differ 
        in that case.
        
        This node is only supported when the engine is rendering to the audio device and not in
        manual rendering mode.

        AVAudioSinkNode does not have an output bus and therefore it does not support tapping.
 */
NS_SWIFT_SENDABLE API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0)) 
@interface AVAudioSinkNode : AVAudioNode

- (instancetype)init NS_UNAVAILABLE;

/*! @method initWithReceiverBlock:
    @abstract Create a node with a receiver block.
    @param block
        The block that receives audio data from the input.
    @discussion
        The preferred initializer is initWithRealtimeSafeReceiverBlock: and should be used instead.
 
        The receiver block is called when the input data is available.

        The block will be called on the realtime thread and it is the client's responsibility to
        handle it in a thread-safe manner and to not make any blocking calls.

        The audio format for the input bus will be set from the connection format when connecting
        to another node.

        The audio format for the data received by the block will be set to the node's input format.
 */
- (instancetype)initWithReceiverBlock:(AVAudioSinkNodeReceiverBlock)block NS_DESIGNATED_INITIALIZER;

/*! @method initWithRealtimeSafeReceiverBlock:
    @abstract
        Identical to initWithReceiverBlock:, but requires a realtime-safe block and is the preferred initializer.
*/
- (instancetype)initWithRealtimeSafeReceiverBlock:(AVAudioSinkNodeReceiverBlockRealtimeSafe)block NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(27.0), ios(27.0), watchos(27.0), tvos(27.0), visionos(27.0)) __SWIFT_UNAVAILABLE_MSG("Swift is not supported for use with audio realtime threads");

@end

NS_ASSUME_NONNULL_END

#endif
