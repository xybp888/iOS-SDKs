//
//  MPSFColorConversion.h
//  MPSFunctions
//
//  Created on 3/23/26.
//  Copyright © 2017 Apple. All rights reserved.

//  This library allows the fast just in time construction of a
//  inlinable metal shading language function to convert from one
//  colorspace to another.  This will allow your application to
//  avoid making a separate pass for color conversion.
//
//  Here is a sample compute kernel showing its usage:
//
//        #include <MPSFunctions/MPSFColorConversionKernel.h>
//
//        MHDR_DECLARE_CONVERSION( ColorConvert );
//        typedef half DataType;
//
//        kernel void DoConversion( texture2d<DataType, access::sample>   srcImage        [[texture(0)]],
//                                  texture2d<DataType, access::write>    destImage       [[texture(1)]],
//                                  uint2 gid                                             [[thread_position_in_grid]],
//
//                                  // ColorConvert data is contained in these resources
//                                  texture1d<float, access::sample>  table1d_1           [[texture(2)]],
//                                  texture3d<float, access::sample>  table3d_1           [[texture(3)]],
//                                  texture3d<float, access::sample>  table3d_2           [[texture(4)]] )
//        {
//            typedef DataType __attribute__((__ext_vector_type__(4))) type4;
//
//            // avoid writing off the edge of destImage
//            if( any(gid >= (uint2){destImage.get_width(), destImage.get_height()}))
//                return;
//
//            // load the source data
//            constexpr sampler s(coord::pixel, address::clamp_to_zero, filter::nearest);
//            type4 p = srcImage.sample(s, float2(gid));
//
//            // convert it to the new colorspace
//            mhdr_conversion_data_t  cData = {table1d_1, table3d_1, table3d_2};
//            p = ColorConvert(p, cData);
//
//            // obviously at this point you could go do whatever else you want to do with the converted pixel
//
//            // write out the result
//            destImage.write(p, gid);
//        }
//
//  The id <MTLFunction> representation of "ColorConvert" (you can pick any function name) is created
//  using MPSFunctionsConversion.function, based on the CGColorConversionInfoRef provided
//  when the MPSFunctionsConversion object is created.
//
//  You can link this function with your shader to make a MTLComputePipelineState as follows:
//
//        static __nullable id <MTLComputePipelineState> NewComputePipelineStateWithConversion( __nonnull id <MTLFunction> myFunction,
//                                                                                              MPSFunctionsConversion * __nonnull c,
//                                                                                              NSError * __nullable __autoreleasing * err) NS_RETURNS_RETAINED
//        {
//            assert( [myFunction.device isEqual: c.device]);
//
//            MTLComputePipelineDescriptor *descriptor = [MTLComputePipelineDescriptor new];
//            MTLLinkedFunctions * linkedFunctions = [MTLLinkedFunctions new];
//            id <MTLFunction> convertFunction = c.function;
//            if( nil == convertFunction)
//            {
//                if(err)
//                {
//                    err[0] = [[c.error retain] autorelease];
//                    NSLog( @"Error getting convert function:\n%@\n", err[0].debugDescription);
//                }
//                [descriptor release];
//                [linkedFunctions release];
//                return nil;
//            }
//            linkedFunctions.functions = @[convertFunction];
//            descriptor.computeFunction = myFunction;
//            descriptor.linkedFunctions = linkedFunctions;
//            [linkedFunctions release];
//
//            id <MTLComputePipelineState> result =  [myFunction.device newComputePipelineStateWithDescriptor: descriptor
//                                                                                                    options: MTLPipelineOptionNone
//                                                                                                 reflection: nil
//                                                                                                      error: err ];
//            [descriptor release];
//            return result;
//        }
//
//  A similar method for MTLRenderPipelineState is under investigation.
//
//  Depending on the conversion, not all of the channels in the float4 will necessarily be modified.
//  The converter will attempt to follow texture unit conventions for mapping texels with fewer
//  than 4 color channels to a float4 value.  Alpha, if present and there is room for it, will
//  be stored in the .w component.  If there are less than 3 color components in the result, the
//  unused channels will be zeroed. If the input pixel has 4 color channels, the image will be assumed
//  to be opaque and an alpha value of 1 will be used if there is room for it. See also
//  MPSFColorConversionOptionsReturnGrayscaleAsRGB.
//

#include <MPSFunctions/MPSFunction.h>
#include <CoreGraphics/CoreGraphics.h>

#ifndef CGCOLORCONVERSIONINFO_H_
    typedef const struct CF_BRIDGED_TYPE(id) CGColorConversionInfo* CGColorConversionInfoRef;
#endif

#ifndef MPSFColorConversion_h
#define MPSFColorConversion_h  1

#if defined( __cplusplus)
    extern "C" {
#endif

#   define MHDR_AVAILABILITY_v1       __API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0))

#if defined(DOXYGEN)
    typedef enum MPSFColorConversionOptions
#else
typedef NS_OPTIONS( uint64_t, MPSFColorConversionOptions)
#endif
{
    MPSFColorConversionOptionsNone                   MHDR_AVAILABILITY_v1    = 0,
    
    // Specify the minimum bits precision in the intermediate stages
    // used to calculate the result, or 0 for default precision for the type (half vs. float)
    MPSFColorConversionOptionsPrecisionDefault = MPSFColorConversionOptionsNone,
    
    // some suggested values, though other values are valid
    MPSFConverisonOptionsPrecisionSnorm8             MHDR_AVAILABILITY_v1    = 7,
    MPSFConverisonOptionsPrecisionUnorm8             MHDR_AVAILABILITY_v1    = 8,
    MPSFConverisonOptionsPrecisionSnorm16            MHDR_AVAILABILITY_v1    = 15,
    MPSFConverisonOptionsPrecisionUnorm16            MHDR_AVAILABILITY_v1    = 16,
    MPSFConverisonOptionsPrecisionFloat16            MHDR_AVAILABILITY_v1    = 11,
    MPSFConverisonOptionsPrecisionFloat32            MHDR_AVAILABILITY_v1    = 24,
    
    MPSFColorConversionOptionsPrecisionMask          MHDR_AVAILABILITY_v1    = 0x3f,
    
    // Return monochrome output as {Y, Y, Y, A} instead. Has no effect if there is more than one color channel.
    // Note that if the conversion parameter is NULL, then MPSFunctions has no information about the number of
    // color channels in the output and will be forced to assume that the output is grayscale.
    MPSFColorConversionOptionsReturnGrayscaleAsRGB   MHDR_AVAILABILITY_v1  = 0x100,
    MPSFColorConversionOptionsVerboseLogging         MHDR_AVAILABILITY_v1  = 0x200
};

static const MPSFunctions_AABB MPSFunctions_AABB_Unbounded = { .max = INFINITY, .min = -INFINITY };
static const MPSFunctions_AABB MPSFunctions_AABB_SDR = { .max = 1, .min = 0 };
    
MHDR_AVAILABILITY_v1
@interface MPSFColorConversion : MPSFunction 

/*! @abstract initialize a new MPSFunctionsConversion object
 *  @discussion  Builds a MPSFunctionsConverison object from a starting and ending colorspace.
 *               Kicks off an asynchronous compilation task to build a MTLFunction appropriate
 *               for the device. Calling the .function or .error propertywill stop and wait for it.
 *               Since the compilation task may take a few milliseconds, your application should
 *               create the MPSFunctionsConversion object as soon as it knows the conversion will
 *               be needed.
 *  @param       device  A valid MTLDevice where the conversion will be used
 *  @param       start  The CGColorSpaceRef for the input data to the conversion
 *
 *               If you would like to make use of  sRGB, PQ and HLG, MTLPixelFormat
 *               variants to take advantage of hardware features to produce linear color
 *               from these colorspaces, use the result of CGColorSpaceCreateLinearized(start)
 *               here instead and configure your MTLTexture to the appropriate variant MTLPixelFormat,
 *               using a texture view or new base pixel format.
 *
 *  @param       end    The CGColorSpaceRef for the output data from the conversion
 *  @param       name  The name of the Metal Shading Language function to build.
 *  @param       sourceRange    If not NULL, the range limit guarantees that the input
 *               texels to the MTLFunction will not appear outside the given axis aligned
 *               bounding box. This, in combination with precision limits (see options), may
 *               allow for a faster conversion calculation.  If a rangeLimit is provided, the
 *               result of the conversion involving out of range inputs is undefined.
 *  @param       options Options to use when building the conversion
 *  @param       error   On failure, the address of a NSError may be written to error[0]
 *  @return      On success, a valid MPSFunctionsConversion object. If the conversion can't be done,
 *               for example because it consumes or produces more than four channels, nil will be
 *               returned, and an appropriate error code created. */
-(nullable instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        startColorSpace: (__nonnull CGColorSpaceRef) start
                          endColorSpace: (__nonnull CGColorSpaceRef) end
                           functionName: (NSString * __nonnull) name
                            sourceRange: (const MPSFunctions_AABB * __nullable) sourceRange
                                options: (MPSFColorConversionOptions) options
                                  error: (NSError * __nullable __autoreleasing * __nullable) error;

/*! @abstract initialize a new MPSFunctionsConversion object
 *  @discussion  Reads the CGColorConversionInfoRef and creates an internal representation
 *               Kicks off an asynchronous compilation task to build a MTLFunction appropriate
 *               for the device.  Calling the .function or .error properties will stop and wait for it.
 *               Since the compilation task may take a few milliseconds, your application should
 *               create the MPSFunctionsConversion object as soon as it knows the conversion will
 *               be needed.
 *
 *  @param       device  A valid MTLDevice where the conversion will be used
 *  @param       conversion A CGColorConversionInfoRef to represent the conversion.
 *               If NULL, a conversion function that returns its argument will be returned.
 *  @param       name  The name of the Metal Shading Language function to build.
 *  @param       sourceRange    If not NULL, the range limit guarantees that the input
 *               texels to the MTLFunction will not appear outside the given axis aligned
 *               bounding box. This, in combination with precision limits (see options), may
 *               allow for a faster conversion calculation.  If a rangeLimit is provided, the
 *               result of the conversion involving out of range inputs is undefined.
 *  @param       options Options to use when building the conversion
 *               CAUTION: when conversion is NULL, MPSFunctions has no information about the
 *               number of channels in the result texel, and so can not intelligently handle
 *               MPSFColorConversionOptionsReturnGrayscaleAsRGB.  In this case, it will assume the
 *               output content is grayscale and remap it to {Y,Y,Y,A} as requested.  Your application
 *               should either intelligently set the option only for grayscale content, or call the other
 *               -init method that consumes two colorspaces which can manage this detail itself.
 *  @param       error   On failure, the address of a NSError may be written to error[0]
 *  @return      On success, a valid MPSFunctionsConversion object. If the conversion can't be done,
 *               for example because it consumes or produces more than four channels, nil will be
 *               returned, and an appropriate error code created. */
-(nullable instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                             conversion: (__nullable CGColorConversionInfoRef) conversion
                           functionName: (NSString * __nonnull) name
                            sourceRange: (const MPSFunctions_AABB * __nullable) sourceRange
                                options: (MPSFColorConversionOptions) options
                                  error: (NSError * __nullable __autoreleasing * __nullable) error NS_DESIGNATED_INITIALIZER;

/*! @abstract The options used when creating the object */
@property (readonly, nonatomic)  MPSFColorConversionOptions options;

/*! @abstract The number of color channels used by the conversion in the float4 texel
    @discussion When the conversion is initialized with a NULL CGColorConversionInfoRef this value will be 0 */
@property (readonly, nonatomic)  NSUInteger inputColorChannels;

/*! @abstract The number of color channels produced by the conversion in the float4 texel
    @discussion When the conversion is initialized with a NULL CGColorConversionInfoRef this value will be 0 */
@property (readonly, nonatomic)  NSUInteger outputColorChannels;

/*! @abstract Estimate the gamut produced by the function based on a range of inputs */
-(MPSFunctions_AABB) effectiveRange: (MPSFunctions_AABB) inputRange;


// Resources:
//  The MPSFunctionsConversion function may need some resources to do its work.
//  See mhdr_conversion_data_t in MPSFunctionsKernel.h.
//  Find the buffer size or MTLTextureDescriptor for the MTLResource. Allocate
//  the resource on your MTLHeap or regular memory, then call the ensuing methods
//  to initialize the contents of the resource. These will need to be passed in
//  to your shader and passed on to your conversion function.
//
/*! @abstract A descriptor for mhdr_conversion_data_t.tex1d_1 */
-(MTLTextureDescriptor * __nullable) descriptorFor1DTexture1;

/*! @abstract A descriptor for mhdr_conversion_data_t.tex3d_1 */
-(MTLTextureDescriptor * __nullable) descriptorFor3DTexture1;

/*! @abstract A descriptor for mhdr_conversion_data_t.tex3d_2 */
-(MTLTextureDescriptor * __nullable) descriptorFor3DTexture2;

/*! @abstract overwrite tex1d_1 will the LUT data needed for the conversion */
-(void) initialize1DTexture1: (__nullable id <MTLTexture>) tex;

/*! @abstract overwrite tex3d_1 will the LUT data needed for the conversion */
-(void) initialize3DTexture1: (__nullable id <MTLTexture>) tex;

/*! @abstract overwrite tex3d_2 will the LUT data needed for the conversion */
-(void) initialize3DTexture2: (__nullable id <MTLTexture>) tex;

@end

#if defined( __cplusplus)
    }   // extern "C"
#endif

#endif /* MPSFColorConversion_h */
