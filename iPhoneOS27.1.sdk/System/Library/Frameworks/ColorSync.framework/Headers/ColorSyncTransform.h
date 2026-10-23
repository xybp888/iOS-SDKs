/*
 * ColorSync - ColorSyncTransform.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNCTRANSFORM__
#define __COLORSYNCTRANSFORM__

#ifdef __cplusplus
extern "C" {
#endif

#include <ColorSync/ColorSyncBase.h>

/// A reference to a color transform that converts color data between profiles.
typedef struct CF_BRIDGED_TYPE(id) ColorSyncTransform* ColorSyncTransformRef;

#if !defined(__swift__)

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

#endif

/// Returns the type identifier for the `ColorSyncTransform` opaque type.
///
/// - Returns: The `CFTypeID` for `ColorSyncTransform` objects.
CSEXTERN CFTypeID ColorSyncTransformGetTypeID(void) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Creates a color transform from a sequence of profiles.
///
/// Each dictionary in `profileSequence` contains a profile object and information on the
/// usage of the profile in the transform.
///
/// Required keys:
///
/// - ``kColorSyncProfile``: A ``ColorSyncProfileRef``.
/// - ``kColorSyncRenderingIntent``: A `CFStringRef` defining the rendering intent.
/// - ``kColorSyncTransformTag``: A `CFStringRef` defining which tags to use.
///
/// Optional key:
///
/// - ``kColorSyncBlackPointCompensation``: A `CFBooleanRef` to enable or disable black point compensation.
///
/// - Parameters:
///   - profileSequence: An array of dictionaries, each one containing a profile object and the information on the usage of the profile in the transform.
///   - options: A dictionary with additional public global options (for example, preferred CMM, quality, and so on). It can also contain custom options that are CMM specific.
/// - Returns: A new ``ColorSyncTransformRef``, or `NULL` in case of failure.
CSEXTERN ColorSyncTransformRef __nullable ColorSyncTransformCreate (CFArrayRef __nullable profileSequence, CFDictionaryRef __nullable options) CS_AVAILABLE_STARTING(10.4, 16.0);


/// Copies a property from a color transform.
///
/// - Parameters:
///   - transform: The transform from which to copy the property.
///   - key: A `CFTypeRef` used as a key to identify the property.
///   - options: A dictionary with additional options.
CSEXTERN CFTypeRef __nullable ColorSyncTransformCopyProperty(ColorSyncTransformRef transform, CFTypeRef key, CFDictionaryRef __nullable options) CS_AVAILABLE_STARTING(10.4, 16.0);


/// Sets a property on a color transform.
///
/// - Parameters:
///   - transform: The transform in which to set the property.
///   - key: A `CFTypeRef` used as a key to identify the property.
///   - property: The `CFTypeRef` to set as the property.
CSEXTERN void ColorSyncTransformSetProperty(ColorSyncTransformRef transform, CFTypeRef key, __nullable CFTypeRef property) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Returns the profile sequence used to create a color transform.
///
/// - Parameter transform: The transform from which to get the profile sequence used to create the transform.
CSEXTERN CFArrayRef __nullable ColorSyncTransformGetProfileSequence(ColorSyncTransformRef transform) CS_AVAILABLE_STARTING(11.0, 16.0);

/// The bit depth and numeric type of a color component in a pixel.
enum ColorSyncDataDepth {
    /// One-bit values, used for gamut-check results.
    kColorSync1BitGamut             = 1,
    /// 8-bit integer components.
    kColorSync8BitInteger           = 2,
    /// 16-bit integer components.
    kColorSync16BitInteger          = 3,
    /// 16-bit floating-point (half-float) components.
    kColorSync16BitFloat            = 4,
    /// 32-bit integer components.
    kColorSync32BitInteger          = 5,
    /// 32-bit named-color index values.
    kColorSync32BitNamedColorIndex  = 6,
    /// 32-bit floating-point components.
    kColorSync32BitFloat            = 7,
    /// 10-bit integer components.
    kColorSync10BitInteger          = 8
};

typedef enum ColorSyncDataDepth ColorSyncDataDepth;

/// The location of the alpha component in a pixel, and whether it's premultiplied.
enum ColorSyncAlphaInfo {
    /// There is no alpha channel. For example, RGB.
    kColorSyncAlphaNone,
    /// The alpha component is stored last and the color components are premultiplied by it. For example, premultiplied RGBA.
    kColorSyncAlphaPremultipliedLast,
    /// The alpha component is stored first and the color components are premultiplied by it. For example, premultiplied ARGB.
    kColorSyncAlphaPremultipliedFirst,
    /// The alpha component is stored last and is not premultiplied. For example, non-premultiplied RGBA.
    kColorSyncAlphaLast,
    /// The alpha component is stored first and is not premultiplied. For example, non-premultiplied ARGB.
    kColorSyncAlphaFirst,
    /// There is no alpha channel; the least significant bits are ignored. For example, RGBX.
    kColorSyncAlphaNoneSkipLast,
    /// There is no alpha channel; the most significant bits are ignored. For example, XRGB.
    kColorSyncAlphaNoneSkipFirst,
};

typedef enum ColorSyncAlphaInfo ColorSyncAlphaInfo;

enum {
    /// The mask for extracting the ``ColorSyncAlphaInfo`` value from a ``ColorSyncDataLayout``.
    kColorSyncAlphaInfoMask = 0x1F,
    
    /// The mask for extracting the byte-order value from a ``ColorSyncDataLayout``.
    kColorSyncByteOrderMask = 0x7000,
    /// The default (host) byte order.
    kColorSyncByteOrderDefault = (0 << 12),
    /// 16-bit, little-endian byte order.
    kColorSyncByteOrder16Little = (1 << 12),
    /// 32-bit, little-endian byte order.
    kColorSyncByteOrder32Little = (2 << 12),
    /// 16-bit, big-endian byte order.
    kColorSyncByteOrder16Big = (3 << 12),
    /// 32-bit, big-endian byte order.
    kColorSyncByteOrder32Big = (4 << 12)
};


/// A bit field describing the alpha information and byte order of a pixel layout.
///
/// Combine a ``ColorSyncAlphaInfo`` value (within ``kColorSyncAlphaInfoMask``) with a byte-order
/// value (within ``kColorSyncByteOrderMask``) to describe how color components are packed.
typedef uint32_t ColorSyncDataLayout;

/// Converts color data from a source layout to a destination layout using a color transform.
///
/// Use this function with care for performance reasons. Color conversions are computationally
/// intensive and the recommended way to perform these is by using the vImage converter with a
/// ColorSync code fragment. vImage employs vectorized code which is not only faster but also more
/// battery efficient. Please visit the following link to see a sample application of vImage used in
/// conjunction with ColorSync:
/// <https://developer.apple.com/library/prerelease/content/samplecode/convertImage/Listings/convertImage_main_c.html>
/// More details regarding ColorSync code fragments are included below, as well.
///
/// - Parameters:
///   - transform: The transform to use for converting color.
///   - width: The width of the image in pixels.
///   - height: The height of the image in pixels.
///   - dst: A pointer to the destination where the function writes the results.
///   - dstDepth: Describes the bit depth and type of the destination color components.
///   - dstLayout: Describes the format and byte packing of the destination pixels.
///   - dstBytesPerRow: The number of bytes in the row of data.
///   - src: A pointer to the data to convert.
///   - srcDepth: Describes the bit depth and type of the source color components.
///   - srcLayout: Describes the format and byte packing of the source pixels.
///   - srcBytesPerRow: The number of bytes in the row of data.
///   - options: A dictionary with additional options.
/// - Returns: `true` if the conversion succeeds, or `false` otherwise.
CSEXTERN bool ColorSyncTransformConvert (ColorSyncTransformRef transform, size_t width, size_t height,
                                         void* dst, ColorSyncDataDepth dstDepth,
                                         ColorSyncDataLayout dstLayout, size_t dstBytesPerRow,
                                         const void* src, ColorSyncDataDepth srcDepth,
                                         ColorSyncDataLayout srcLayout, size_t srcBytesPerRow,
                                         __nullable CFDictionaryRef options) CS_AVAILABLE_STARTING(10.4, 16.0);

/* Keys and values for profile specific info and options */
/// A key for the profile object in a profile-sequence dictionary passed to ``ColorSyncTransformCreate``.
CSEXTERN CFStringRef kColorSyncProfile CS_AVAILABLE_STARTING(10.4, 16.0);
/// A key for the rendering intent to use for the profile in a profile-sequence dictionary.
CSEXTERN CFStringRef kColorSyncRenderingIntent CS_AVAILABLE_STARTING(10.4, 16.0);

    /* Legal values for kColorSyncRenderingIntent */
        /// A ``kColorSyncRenderingIntent`` value selecting the perceptual rendering intent.
        CSEXTERN CFStringRef kColorSyncRenderingIntentPerceptual CS_AVAILABLE_STARTING(10.4, 16.0);
        /// A ``kColorSyncRenderingIntent`` value selecting the media-relative colorimetric rendering intent.
        CSEXTERN CFStringRef kColorSyncRenderingIntentRelative CS_AVAILABLE_STARTING(10.4, 16.0);
        /// A ``kColorSyncRenderingIntent`` value selecting the saturation rendering intent.
        CSEXTERN CFStringRef kColorSyncRenderingIntentSaturation CS_AVAILABLE_STARTING(10.4, 16.0);
        /// A ``kColorSyncRenderingIntent`` value selecting the ICC-absolute colorimetric rendering intent.
        CSEXTERN CFStringRef kColorSyncRenderingIntentAbsolute CS_AVAILABLE_STARTING(10.4, 16.0);
        /// A ``kColorSyncRenderingIntent`` value selecting the rendering intent stored in the profile header.
        CSEXTERN CFStringRef kColorSyncRenderingIntentUseProfileHeader CS_AVAILABLE_STARTING(10.4, 16.0);

/// A key for the tag identifying which tags of the profile to use in a profile-sequence dictionary.
CSEXTERN CFStringRef kColorSyncTransformTag CS_AVAILABLE_STARTING(10.4, 16.0);

    /* Legal values for kColorSyncTransformTag */
        /// A ``kColorSyncTransformTag`` value selecting the device-to-PCS conversion direction.
        CSEXTERN CFStringRef kColorSyncTransformDeviceToPCS CS_AVAILABLE_STARTING(10.4, 16.0);
        /// A ``kColorSyncTransformTag`` value selecting the PCS-to-PCS conversion direction.
        CSEXTERN CFStringRef kColorSyncTransformPCSToPCS CS_AVAILABLE_STARTING(10.4, 16.0);
        /// A ``kColorSyncTransformTag`` value selecting the PCS-to-device conversion direction.
        CSEXTERN CFStringRef kColorSyncTransformPCSToDevice CS_AVAILABLE_STARTING(10.4, 16.0);
        /// A ``kColorSyncTransformTag`` value selecting the device-to-device conversion direction.
        CSEXTERN CFStringRef kColorSyncTransformDeviceToDevice CS_AVAILABLE_STARTING(10.4, 16.0);
        /// A ``kColorSyncTransformTag`` value that checks whether colors fall outside the destination gamut.
        CSEXTERN CFStringRef kColorSyncTransformGamutCheck CS_AVAILABLE_STARTING(10.4, 16.0);

/// A key whose `CFBooleanRef` value enables or disables black point compensation.
CSEXTERN CFStringRef kColorSyncBlackPointCompensation CS_AVAILABLE_STARTING(10.4, 16.0);
/// A key whose `CFBooleanRef` value enables or disables extended range.
CSEXTERN CFStringRef kColorSyncExtendedRange CS_AVAILABLE_STARTING(10.16, 16.0);
/// A key for the HDR derivative to apply to the profile in a profile-sequence dictionary.
CSEXTERN CFStringRef kColorSyncHDRDerivative CS_AVAILABLE_STARTING(14.0, 17.0);
        /// A ``kColorSyncHDRDerivative`` value selecting the PQ HDR derivative.
        CSEXTERN CFStringRef kColorSyncPQDerivative CS_AVAILABLE_STARTING(14.0, 17.0);
        /// A ``kColorSyncHDRDerivative`` value selecting the HLG HDR derivative.
        CSEXTERN CFStringRef kColorSyncHLGDerivative CS_AVAILABLE_STARTING(14.0, 17.0);

/* Global transform options */
/// A key whose value is the ``ColorSyncCMMRef`` of the preferred CMM.
CSEXTERN CFStringRef kColorSyncPreferredCMM CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED; /* ColorSyncCMMRef of the preferred CMM */
/// A key for the quality of the conversion performed by the transform.
CSEXTERN CFStringRef kColorSyncConvertQuality CS_AVAILABLE_STARTING(10.4, 16.0);

    /* Legal values for kColorSyncConvertQuality */
        /// A ``kColorSyncConvertQuality`` value that does not coalesce profile transforms; the default.
        CSEXTERN CFStringRef kColorSyncBestQuality CS_AVAILABLE_STARTING(10.4, 16.0);      /* do not coalesce profile transforms (default) */
        /// A ``kColorSyncConvertQuality`` value that coalesces all transforms.
        CSEXTERN CFStringRef kColorSyncNormalQuality CS_AVAILABLE_STARTING(10.4, 16.0);    /* coalesce all transforms */
        /// A ``kColorSyncConvertQuality`` value that coalesces all transforms and does not interpolate.
        CSEXTERN CFStringRef kColorSyncDraftQuality CS_AVAILABLE_STARTING(10.4, 16.0);     /* coalesce all transforms, do not interpolate */

/* Conversion options */
/// A key whose `CFBooleanRef` value allows float data to exceed the `[0.0, 1.0]` range.
CSEXTERN CFStringRef kColorSyncConvertUseExtendedRange CS_AVAILABLE_STARTING(11.0, 16.0); /* allow float data to exceed [0.0 .. 1.0] range */

/* Public keys for copying transform properties */

/// A key for a dictionary of information about the transform.
CSEXTERN CFStringRef kColorSyncTransformInfo CS_AVAILABLE_STARTING(10.4, 16.0);        /* dictionary with the following keys */
    /// A key for the name of the CMM that created the transform.
    CSEXTERN CFStringRef kColorSyncTransformCreator CS_AVAILABLE_STARTING(10.4, 16.0); /* name of the CMM that created the transform */
    /// A key for the transform's source color space.
    CSEXTERN CFStringRef kColorSyncTransformSrcSpace CS_AVAILABLE_STARTING(10.4, 16.0);
    /// A key for the transform's destination color space.
    CSEXTERN CFStringRef kColorSyncTransformDstSpace CS_AVAILABLE_STARTING(10.4, 16.0);

/*
 * =============================
 *
 *  Code Fragment Support
 *
 * =============================
 *
 * ColorSync can return parameters for standard components of color conversion,
 * i.e. tone rendering curves (TRCs), 3x4 matrices (3x3 + 3x1), multi-dimensional
 * interpolation tables and Black Point Compensation.
 * The parameters are wrapped in CFArray or CFData objects specific to the
 * component type and placed in a CFDictionary under a key that identifies the 
 * type of the component. The complete code fragment is a CFArray of component
 * dictionaries that are placed in the in the order they have to be executed.
 * 
 * A code fragment is created by calling ColorSyncTransformCopyProperty with the key 
 * specifying the type of the code fragment to be created. NULL pointer will be
 * returnde if the requested code fragment cannot be created.
 */

/*
 * Types of Code Fragments:
 *
 * 1. Full conversion: all non-NULL components based on all the tags from the
 *                     sequence of profiles passed to create the ColorSyncTransform with
 *                     an exception of adjacent matrices that can be collapsed to
 *                     one matrix.
 * 2. Parametric:      same as above, except that the returned code fragment consists
 *                     only of parametric curves, matrices and BPC components.
 * 3. Simplified:      Full conversion is collapsed to one
 *                     multi-dimensional table with N inputs and M outputs.
 */
 
    
/// A key for the type of code fragment to create, or that the framework created.
CSEXTERN CFStringRef kColorSyncTransformCodeFragmentType CS_AVAILABLE_STARTING(10.4, 16.0);           /* CFSTR("com.apple.cmm.CodeFragmentType")  */
/// A key for the MD5 checksum of the code fragment.
CSEXTERN CFStringRef kColorSyncTransformCodeFragmentMD5 CS_AVAILABLE_STARTING(10.4, 16.0);            /* CFSTR("com.apple.cmm.CodeFragmentMD5")  */
/// A key for the full-conversion code fragment, containing all non-`NULL` components from the profile sequence.
CSEXTERN CFStringRef kColorSyncTransformFullConversionData CS_AVAILABLE_STARTING(10.4, 16.0);         /* CFSTR("com.apple.cmm.FullConversion") */
/// A key for the simplified code fragment, collapsing the full conversion into one multi-dimensional table.
CSEXTERN CFStringRef kColorSyncTransformSimplifiedConversionData CS_AVAILABLE_STARTING(10.4, 16.0);   /* CFSTR("com.apple.cmm.SimplifiedConversion") */
/// A key for the parametric code fragment, consisting only of parametric curves, matrices, and BPC components.
CSEXTERN CFStringRef kColorSyncTransformParametricConversionData CS_AVAILABLE_STARTING(10.4, 16.0);   /* CFSTR("com.apple.cmm.ParametricConversion") */
/// A key for the profile sequence used to create the transform.
CSEXTERN CFStringRef kColorSyncTransformProfileSequnce CS_AVAILABLE_STARTING(11.0, 16.0);             /* CFSTR("com.apple.cmm.ProfileSequnce") */

/// A key whose `CFBooleanRef` value uses the ITU-R BT.709 opto-electronic transfer function.
CSEXTERN CFStringRef kColorSyncTransformUseITU709OETF CS_AVAILABLE_STARTING(15.0, 18.0);              /* CFSTR("com.apple.cmm.TransformUseITU709OETF") */
/*
 * Matrix: represented as a CFArray of three CFArrays of four CFNumbers (Float32)
 *         each, performin the following matrix operation
 *         y[3] = 3x3 matrix *x[3] + 3x1 vector (last column)
 */
/// A key for a conversion matrix component, represented as a `CFArray` of three `CFArray`s of four `Float32` `CFNumber`s.
CSEXTERN CFStringRef kColorSyncConversionMatrix CS_AVAILABLE_STARTING(10.4, 16.0);        /* CFSTR("com.apple.cmm.Matrix") */

/*
 * Tone Rendering Curves:
 *
 * 1. Parametric curves: represented as a CFArray of seven CFNumbers (Float32)
 *                       [gamma a b c d e f]
 *  Curve Type 0  Y = X^gamma
 *  Curve Type 1  Y = (aX+b)^gamma     [X >= -b/a],  Y = 0  [X < -b/a]
 *  Curve Type 2  Y = (aX+b)^gamma + c [X >= -b/a],  Y = c  [X < -b/a]
 *  Curve Type 3  Y = (aX+b)^gamma     [X >= d],     Y = cX [X < d]
 *  Curve Type 4  Y = (aX+b)^gamma + e [X >= d],     Y = cX + f [X < d]
 *
 * 2. 1-dimensional lookup with interpolation:
 *                  represented as CFData containing a Float32 table[gridPoints]
 */
 
/// A key for a parametric tone rendering curve of type 0, represented as a `CFArray` of seven `Float32` `CFNumber`s.
CSEXTERN CFStringRef kColorSyncConversionParamCurve0 CS_AVAILABLE_STARTING(10.4, 16.0);      /* CFSTR("com.apple.cmm.ParamCurve0") */
/// A key for a parametric tone rendering curve of type 1, represented as a `CFArray` of seven `Float32` `CFNumber`s.
CSEXTERN CFStringRef kColorSyncConversionParamCurve1 CS_AVAILABLE_STARTING(10.4, 16.0);      /* CFSTR("com.apple.cmm.ParamCurve1") */
/// A key for a parametric tone rendering curve of type 2, represented as a `CFArray` of seven `Float32` `CFNumber`s.
CSEXTERN CFStringRef kColorSyncConversionParamCurve2 CS_AVAILABLE_STARTING(10.4, 16.0);      /* CFSTR("com.apple.cmm.ParamCurve2") */
/// A key for a parametric tone rendering curve of type 3, represented as a `CFArray` of seven `Float32` `CFNumber`s.
CSEXTERN CFStringRef kColorSyncConversionParamCurve3 CS_AVAILABLE_STARTING(10.4, 16.0);      /* CFSTR("com.apple.cmm.ParamCurve3") */
/// A key for a parametric tone rendering curve of type 4, represented as a `CFArray` of seven `Float32` `CFNumber`s.
CSEXTERN CFStringRef kColorSyncConversionParamCurve4 CS_AVAILABLE_STARTING(10.4, 16.0);      /* CFSTR("com.apple.cmm.ParamCurve4") */
/// A key for a one-dimensional lookup table with interpolation, represented as `CFData` containing a `Float32` table.
CSEXTERN CFStringRef kColorSyncConversion1DLut CS_AVAILABLE_STARTING(10.4, 16.0);            /* CFSTR("com.apple.cmm.1D-LUT") */
/// A key for the number of grid points in a lookup table.
CSEXTERN CFStringRef kColorSyncConversionGridPoints CS_AVAILABLE_STARTING(10.4, 16.0);       /* CFSTR("com.apple.cmm.GridPointCount") */
/// A key for the identifier of the channel a conversion component applies to.
CSEXTERN CFStringRef kColorSyncConversionChannelID CS_AVAILABLE_STARTING(10.4, 16.0);        /* CFSTR("com.apple.cmm.ChannelID") */

/*
 * Multi-dimensional lookup with interpolation:
 *
 *       represented as CFData containing a table for N inputs, M outputs 
 *       and P gridPoints in each direction. The dimension corresponding to the
 *       first input channel varies least rapidly, and the dimension corresponding
 *       to the last input channel varies most rapidly. Each grid point value contains
 *       M uint16_t numbers, one for each of output channels (M is the number of outputs).
 */
 

/// A key for a three-dimensional lookup table with interpolation, represented as `CFData`.
CSEXTERN CFStringRef kColorSyncConversion3DLut CS_AVAILABLE_STARTING(10.4, 16.0);      /* CFSTR("com.apple.cmm.3D-LUT") */
/// A key for a multi-dimensional lookup table with interpolation, represented as `CFData` for N inputs and M outputs.
CSEXTERN CFStringRef kColorSyncConversionNDLut CS_AVAILABLE_STARTING(10.4, 16.0);      /* CFSTR("com.apple.cmm.ND-LUT") */
/// A key for the number of input channels of a lookup table.
CSEXTERN CFStringRef kColorSyncConversionInpChan CS_AVAILABLE_STARTING(10.4, 16.0);    /* CFSTR("com.apple.cmm.InputChannels") */
/// A key for the number of output channels of a lookup table.
CSEXTERN CFStringRef kColorSyncConversionOutChan CS_AVAILABLE_STARTING(10.4, 16.0);    /* CFSTR("com.apple.cmm.OutputChannels") */

/*
 * Black Point Compensation: represented as an CFArray of CFNumbers (Float32)
 *
 * 1. Scaling in Luminance: CFArray containing two numbers.
 * 2. Scaling in XYZ: CFArray containing six numbers.
 */
 
/// A key for a black point compensation component, represented as a `CFArray` of `Float32` `CFNumber`s.
CSEXTERN CFStringRef kColorSyncConversionBPC CS_AVAILABLE_STARTING(10.4, 16.0);   /* CFSTR("com.apple.cmm.BPC") */

/// A key for the fixed-point range of the conversion data.
CSEXTERN CFStringRef kColorSyncFixedPointRange CS_AVAILABLE_STARTING(10.4, 16.0); /* CFSTR("com.apple.cmm.FixedPointRange") */

/// Creates a code fragment from a sequence of profiles.
///
/// Each dictionary in `profileSequence` contains a profile object and information on the
/// usage of the profile in the code fragment.
///
/// Required keys:
///
/// - ``kColorSyncProfile``: A ``ColorSyncProfileRef``.
/// - ``kColorSyncRenderingIntent``: A `CFStringRef` defining the rendering intent.
/// - ``kColorSyncTransformTag``: A `CFStringRef` defining which tags to use.
///
/// Optional key:
///
/// - ``kColorSyncBlackPointCompensation``: A `CFBooleanRef` to enable or disable black point compensation.
/// - ``kColorSyncExtendedRange``: A `CFBooleanRef` to enable or disable extended range; disabling implies floating point conversions.
///
/// - Parameters:
///   - profileSequence: An array of dictionaries, each one containing a profile object and the information on the usage of the profile in the code fragment.
///   - options: A dictionary with additional options as in the case of creating a `ColorSyncTransform`.
/// - Returns: A `CFTypeRef` representing a ColorSync code fragment, or `NULL` in case of failure.
CSEXTERN CFTypeRef ColorSyncCreateCodeFragment(CFArrayRef profileSequence, CFDictionaryRef options) CS_AVAILABLE_STARTING(10.4, 16.0);
    
#if !defined(__swift__)

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif

#ifdef __cplusplus
}
#endif

#endif /* __COLORSYNCTRANSFORM__ */
