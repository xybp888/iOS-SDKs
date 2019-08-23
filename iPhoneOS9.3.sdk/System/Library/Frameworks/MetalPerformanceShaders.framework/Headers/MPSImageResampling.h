/*!
 *  @header MPSImageResampling.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract  Resampling filters for Metal Image
 */

#ifndef MPS_MPSImageResampling_h
#define MPS_MPSImageResampling_h

#include <MetalPerformanceShaders/MPSImageKernel.h>


/*!
 *  @class      MPSImageLanczosScale
 *  @abstract   Resize an image and / or change its aspect ratio
 *  @discussion The MPSImageLanczosScale filter can be used to resample an existing image
 *              using a different sampling frequency in each dimension. This can be
 *              used to enlarge or reduce the size of an image, or change the aspect
 *              ratio of an image.  The filter uses a Lanczos resampling algorithm
 *              which typically produces better quality for photographs, but is slower
 *              than linear sampling using the GPU texture units. Lanczos downsampling 
 *              does not require a low pass filter to be applied before it is used. 
 *              Because the resampling function has negative lobes, Lanczos can result 
 *              in ringing near sharp edges, making it less suitable for vector art.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageLanczosScale : MPSUnaryImageKernel

/*! @property   scaleTransform
 *  @abstract   An optional transform that describes how to scale and translate the source image
 *  @discussion If the scaleTransform is NULL, then the MPSImageLanczosScale filter will 
 *              rescale the image so that the source image fits exactly into the destination 
 *              texture.  If the transform is not NULL, then the transform is used for determining
 *              how to map the source image to the destination. Default: NULL
 *              
 *              When the scaleTransform is set to non-NULL, the values pointed to by the new 
 *              scaleTransform are copied to object storage, and the pointer is updated to point 
 *              to internal storage. Do not attempt to free it.  You may free your copy of 
 *              the MPSScaleTransform as soon as the property set operation is complete.
 */
@property (readwrite, nonatomic, nullable) const MPSScaleTransform *scaleTransform;



@end

#endif /* MPS_MSImageResampling_h */
