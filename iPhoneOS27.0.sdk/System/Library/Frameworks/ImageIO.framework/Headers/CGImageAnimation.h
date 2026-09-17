/*
 * ImageIO - CGImageAnimation.h
 * Copyright (c) 2018 Apple Inc. All rights reserved.
 *
 */

#ifndef CGIMAGEANIMATION_H_
#define CGIMAGEANIMATION_H_

#include <ImageIO/ImageIOBase.h>

#include <CoreGraphics/CoreGraphics.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN


/**
 * Constants that indicate the result of animating an image sequence.
 */
typedef CF_ENUM(OSStatus, CGImageAnimationStatus) {
    kCGImageAnimationStatus_ParameterError          = -22140,      /* NULL or invalid parameter passed to API */
    kCGImageAnimationStatus_CorruptInputImage       = -22141,      /* An image cannot be read from the given source */
    kCGImageAnimationStatus_UnsupportedFormat       = -22142,      /* The image format is not applicable to animation */
    kCGImageAnimationStatus_IncompleteInputImage    = -22143,      /* An image can be read from the given source, but it is incomplete */
    kCGImageAnimationStatus_AllocationFailure       = -22144       /* A required resource could not be created */
};

/* Starts the animation at the given index. Defaults to 0
 * Value is a CFNumber
 */
/**
 * A property that specifies the index of the first frame of an animation.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber> that contains an unsigned integer. To override the start index value in the image file, include this property in the options dictionary when animating an image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAnimationStartIndex  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);

/* The value of this key overrides the `delay time` specified by the image
 * Value is a CFNumber of kCFNumberDoubleType.
 */
/**
 * The number of seconds to wait before displaying the next image in an animated sequence.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber> with a floating-point value. To override the delay time value in the image file, include this property in the options dictionary when animating an image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAnimationDelayTime  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);

/* The value of this key overrides the `loop count` specified by the image
 * Value is a CFNumber; kCFNumberPositiveInfinity may be used.
 */
/**
 * The number of times to repeat the animated sequence.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber> that contains an unsigned integer. To override the loop count value in the image file, include this property in the options dictionary when animating an image.
 *
 * You may specify <doc://com.apple.documentation/documentation/corefoundation/kcfnumberpositiveinfinity> for this property to animate the images continuously.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAnimationLoopCount  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);


/**
 * The block to execute for each frame of an image animation.
 *
 * - Parameters:
 *   - index: The index of the image in the file.
 *   - image: The image to display.
 *   - stop: A Boolean flag set to `false` on input. To stop the animation, set the value of this parameter to `true`.
 *
 * During the animation of an image, the system calls this block for each successive frame of the animation. Use this block to display the new image in your app's interface, and to update any additional details.
 */
typedef void (^CGImageSourceAnimationBlock)(size_t index, CGImageRef image, bool* stop);

/**
 * Animate the sequence of images in the Graphics Interchange Format (GIF) or Animated Portable Network Graphics (APNG) file at the specified URL.
 *
 * - Parameters:
 *   - url: The URL of the image file.
 *   - options: Additional playback options. Include the ``kCGImageAnimationDelayTime`` or ``kCGImageAnimationLoopCount`` keys to override the timing information in the image file. Include the ``kCGImageAnimationStartIndex`` key to specify the index of the first image in the animation.
 *   - block: The animation block to execute for each image frame. The system executes this block on the main queue, and at the intervals indicated by the image's delay time metadata. Use this block to display the provided image in your interface.
 *
 * - Returns: A status code indicating the success or failure of the animation.
 *
 * The function executes the provided `block` for each frame of the animation. By default, the function uses the timing information contained in the image's metadata. This information includes the number of seconds between individual frames, and the number of times to loop the animation. For example, the function uses the ``kCGImagePropertyGIFDelayTime`` and ``kCGImagePropertyGIFLoopCount`` tags from a GIF file's metadata. To override the default timing information, provide the appropriate keys in the `options` dictionary.
 */
IMAGEIO_EXTERN OSStatus CGAnimateImageAtURLWithBlock(CFURLRef url, CFDictionaryRef _iio_Nullable options, CGImageSourceAnimationBlock block) IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);

/**
 * Animate the sequence of images using data from a Graphics Interchange Format (GIF) or Animated Portable Network Graphics (APNG) file file.
 *
 * - Parameters:
 *   - data: The image data to animate.
 *   - options: Additional playback options. Include the ``kCGImageAnimationDelayTime`` or ``kCGImageAnimationLoopCount`` keys to override the timing information in the image file. Include the ``kCGImageAnimationStartIndex`` key to specify the index of the first image in the animation.
 *   - block: The animation block to execute for each image frame. The system executes this block on the main queue, and at the intervals indicated by the image's delay time metadata. Use this block to display the provided image in your interface.
 *
 * - Returns: A status code indicating the success or failure of the animation.
 *
 * The function executes the provided `block` for each frame of the animation. By default, the function uses the timing information contained in the image's metadata. This information includes the number of seconds between individual frames, and the number of times to loop the animation. For example, the function uses the ``kCGImagePropertyGIFDelayTime`` and ``kCGImagePropertyGIFLoopCount`` tags from a GIF image's metadata. To override the default timing information, provide the appropriate keys in the `options` dictionary.
 */
IMAGEIO_EXTERN OSStatus CGAnimateImageDataWithBlock(CFDataRef data, CFDictionaryRef _iio_Nullable options, CGImageSourceAnimationBlock block) IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGIMAGEANIMATION_H_ */
