/*
 * ImageIO - CGImageProperties.h
 * Copyright (c) 2004-2016 Apple Inc. All rights reserved.
 *
 */

#ifndef __CGIMAGEPROPERTIES__
#define __CGIMAGEPROPERTIES__

#include <CoreGraphics/CGBase.h>
#include <ImageIO/ImageIOBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Properties that, if returned by CGImageSourceCopyProperties or 
 * CGImageSourceCopyPropertiesAtIndex, contain a dictionary of file-format 
 * or metadata-format specific key-values. */

/**
 * A dictionary of key-value pairs for an image that uses Tagged Image File Format (TIFF).
 *
 * For more information about the available metadata keys, see <doc:tiff-image-properties>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFDictionary  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A dictionary of key-value pairs for an image that uses Graphics Interchange Format (GIF).
 *
 * For more information about the available metadata keys, see <doc:gif-image-properties>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFDictionary  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A dictionary of key-value pairs for an image that uses JPEG File Interchange Format (JFIF).
 *
 * For more information about the available metadata keys, see <doc:jfif-image-properties>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFDictionary  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHEIFDictionary  IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
/**
 * A dictionary of properties related to an HEIC container.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHEICSDictionary  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * A dictionary of key-value pairs for an image that uses Exchangeable Image File Format (EXIF).
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifDictionary  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A dictionary of key-value pairs for an image that uses Portable Network Graphics (PNG) format.
 *
 * For more information about the available metadata keys, see <doc:png-image-properties>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGDictionary  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A dictionary of key-value pairs for an image that uses International Press Telecommunications Council (IPTC) metadata.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCDictionary  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A dictionary of key-value pairs for an image that has Global Positioning System (GPS) information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDictionary  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A dictionary of key-value pairs for an image that contains minimally processed, or raw, data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyRawDictionary  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A dictionary of key-value pairs for an image that uses Camera Image File Format (CIFF).
 *
 * For more information about the available metadata keys, see <doc:ciff-image-properties>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyCIFFDictionary  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A dictionary of key-value pairs for an image from a Canon camera.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerCanonDictionary  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * A dictionary of key-value pairs for an image from a Nikon camera.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerNikonDictionary  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * A dictionary of key-value pairs for an image from a Minolta camera.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerMinoltaDictionary  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * A dictionary of key-value pairs for an image from a Fuji camera.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerFujiDictionary  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * A dictionary of key-value pairs for an image from a Olympus camera.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerOlympusDictionary  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * A dictionary of key-value pairs for an image from a Pentax camera.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerPentaxDictionary  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * A dictionary of key-value pairs for an Adobe Photoshop image.
 *
 * For more information about the available metadata keys, see <doc:8bim-image-properties>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageProperty8BIMDictionary  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A dictionary of key-value pairs for an image that uses the Digital Negative (DNG) archival format.
 *
 * For more information about the available metadata keys, see <doc:dng-image-properties>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGDictionary  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * An auxiliary dictionary of key-value pairs for an image that uses Exchangeable Image File Format (EXIF).
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxDictionary  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * A dictionary of properties specific to the OpenEXR metadata standard.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyOpenEXRDictionary  IMAGEIO_AVAILABLE_STARTING(10.9, 11.3);
/**
 * A dictionary of key-value pairs for an image from an Apple camera.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyMakerAppleDictionary  IMAGEIO_AVAILABLE_STARTING(10.10, 7.0);
/**
 * A dictionary of properties related to the image's on-disk file.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfdictionary>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyFileContentsDictionary IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * A dictionary of properties related to a WebP container.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyWebPDictionary  IMAGEIO_AVAILABLE_STARTING(11.0, 14.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAVISDictionary  IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTGADictionary  IMAGEIO_AVAILABLE_STARTING(11.0, 14.0);


/** Properties which may be returned by "CGImageSourceCopyProperties".  The
 ** values apply to the container in general but not necessarily to any
 ** individual image that it contains. **/

/* The size of the image file in bytes, if known. If present, the value of
 * this key is a CFNumberRef. */

/**
 * The size of the image file in bytes, if known.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyFileSize  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);


/** Properties which may be returned by "CGImageSourceCopyPropertiesAtIndex".
 ** The values apply to a single image of an image source file. **/

/* The number of pixels in the x- and y-dimensions. The value of these keys 
 * is a CFNumberRef. */

/**
 * The number of pixels along the y-axis of the image.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPixelHeight  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The number of pixels along the x-axis of the image.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPixelWidth  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* The DPI in the x- and y-dimensions, if known. If present, the value of
 * these keys is a CFNumberRef. */

/**
 * The resolution, in dots per inch, in the y dimension.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDPIHeight  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The resolution, in dots per inch, in the x dimension.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDPIWidth  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* The number of bits in each color sample of each pixel. The value of this 
 * key is a CFNumberRef. */

/**
 * The number of bits in the color sample of a pixel.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDepth  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* The intended display orientation of the image. If present, the value 
 * of this key is a CFNumberRef with the same value as defined by the 
 * TIFF and Exif specifications.  That is:
 *   1  =  0th row is at the top, and 0th column is on the left.  
 *   2  =  0th row is at the top, and 0th column is on the right.  
 *   3  =  0th row is at the bottom, and 0th column is on the right.  
 *   4  =  0th row is at the bottom, and 0th column is on the left.  
 *   5  =  0th row is on the left, and 0th column is the top.  
 *   6  =  0th row is on the right, and 0th column is the top.  
 *   7  =  0th row is on the right, and 0th column is the bottom.  
 *   8  =  0th row is on the left, and 0th column is the bottom.  
 * If not present, a value of 1 is assumed. */ 
 
/**
 * The intended display orientation of the image.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>. The value encodes the intended display orientation for the image according to the TIFF and EXIF specifications. See the ``CGImagePropertyOrientation`` type for possible values and their meanings.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyOrientation  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* The value of this key is kCFBooleanTrue if the image contains floating- 
 * point pixel samples */ 
 
/**
 * A Boolean value that indicates whether the image contains floating-point pixel samples.
 *
 * The value of this property is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleantrue> if the image contains floating-point pixel samples.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIsFloat  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* The value of this key is kCFBooleanTrue if the image contains indexed 
 * (a.k.a. paletted) pixel samples */ 
 
/**
 * A Boolean value that indicates whether the image contains indexed pixel samples.
 *
 * Indexed pixel samples are also known as paletted samples. The value of this property is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleantrue> if the image contains indexed pixel samples.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIsIndexed  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* The value of this key is kCFBooleanTrue if the image contains an alpha 
 * (a.k.a. coverage) channel */ 
 
/**
 * A Boolean value that indicates whether the image has an alpha channel.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfboolean>. The value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleantrue> when the image contains an alpha channel.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHasAlpha  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* The color model of the image such as "RGB", "CMYK", "Gray", or "Lab".
 * The value of this key is CFStringRef. */ 

/**
 * The color model of the image, such as RGB, CMYK, grayscale, or Lab.
 *
 * The value of this key is of type <doc://com.apple.documentation/documentation/corefoundation/cfstring>. Typically, the value corresponds to the ``kCGImagePropertyColorModelRGB``, ``kCGImagePropertyColorModelCMYK``, ``kCGImagePropertyColorModelGray``, or ``kCGImagePropertyColorModelLab`` constant.
 *
 * A color model describes how color values are represented mathematically. A color space is a color model combined with a definition of how to interpret values within the model.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyColorModel  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* The name of the optional ICC profile embedded in the image, if known.  
 * If present, the value of this key is a CFStringRef. */

/**
 * The name of the optional International Color Consortium (ICC) profile embedded in the image, if known.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfstring>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyProfileName  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* For HEIF images: the value of this key is kCFBooleanTrue if the image at the given index is the primary image.
 */
/**
 * The index of the primary image in the file.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPrimaryImage     IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);

/* Possible values for kCGImagePropertyColorModel property */

/**
 * A Red Green Blue (RGB) color model.
 *
 * Use this value with the ``kCGImagePropertyColorModel`` key.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyColorModelRGB  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A grayscale color model.
 *
 * Use this value with the ``kCGImagePropertyColorModel`` key.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyColorModelGray  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A Cyan Magenta Yellow Black (CMYK) color model.
 *
 * Use this value with the ``kCGImagePropertyColorModel`` key.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyColorModelCMYK  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A Lab color model, where color values contain the amount of light and the amounts of four human-perceivable colors.
 *
 * Use this value with the ``kCGImagePropertyColorModel`` key.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyColorModelLab  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);


/* Possible keys for kCGImagePropertyTIFFDictionary */

/**
 * The compression scheme used on the image data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFCompression  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The color space of the image data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFPhotometricInterpretation  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The document name.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFDocumentName  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The image description.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFImageDescription  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The name of the manufacturer of the camera or input device.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFMake  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The camera or input device model.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFModel  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The image orientation.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFOrientation  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The number of pixels per resolution unit in the image width direction.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFXResolution  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The number of pixels per resolution unit in the image height direction.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFYResolution  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFXPosition  IMAGEIO_AVAILABLE_STARTING(14.4, 17.4);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFYPosition  IMAGEIO_AVAILABLE_STARTING(14.4, 17.4);
/**
 * The units of resolution.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFResolutionUnit  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The name and version of the software used for image creation.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFSoftware  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The transfer function, in tabular format, used to map pixel components from a nonlinear form into a linear form.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFTransferFunction  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The date and time that the image was created.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFDateTime  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The artist who created the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFArtist  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The computer or operating system used when the image was created.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFHostComputer  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * Copyright information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFCopyright  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The white point of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFWhitePoint  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The chromaticities of the primaries of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFPrimaryChromaticities  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFTileWidth  IMAGEIO_AVAILABLE_STARTING(10.11, 9.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyTIFFTileLength  IMAGEIO_AVAILABLE_STARTING(10.11, 9.0);

/* Possible keys for kCGImagePropertyJFIFDictionary */

/**
 * The version of JFIF.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFVersion  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The x pixel density.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFXDensity  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The y pixel density.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFYDensity  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The units for the x and y density fields.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFDensityUnit  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * Whether there are versions of the image of increasing quality.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyJFIFIsProgressive  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Possible keys for kCGImagePropertyHEICSDictionary */

/**
 * The number of times to play the sequence.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHEICSLoopCount  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The number of seconds to wait before displaying the next image in the sequence, clamped to a minimum of `0.1` seconds.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber> with a floating-point value. The value of this key is never less than 100 millseconds, and the system adjusts values less than that amount to 100 milliseconds, as needed. See ``kCGImagePropertyHEICSUnclampedDelayTime``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHEICSDelayTime  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The unclamped number of seconds to wait before displaying the next image in the sequence.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber> with a floating-point value.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHEICSUnclampedDelayTime  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The width of the main image, in pixels.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHEICSCanvasPixelWidth IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The height of the main image, in pixels.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHEICSCanvasPixelHeight IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * An array of dictionaries that contain timing information for the image sequence.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfarray>. Each <doc://com.apple.documentation/documentation/corefoundation/cfdictionary> in the array contains timing information about an image in the sequence.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHEICSFrameInfoArray  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);

/* Possible keys for kCGImagePropertyExifDictionary */

/**
 * The exposure time.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifExposureTime  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The F-number.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFNumber  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The exposure program.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifExposureProgram  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The spectral sensitivity of each channel.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSpectralSensitivity  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The ISO speed ratings.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifISOSpeedRatings  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The opto-electric conversion function (OECF) that defines the relationship between the optical input of the camera and the resulting image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifOECF  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The type of sensitivity data stored for the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSensitivityType  IMAGEIO_AVAILABLE_STARTING(10.9, 7.0);
/**
 * The sensitivity data for the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifStandardOutputSensitivity  IMAGEIO_AVAILABLE_STARTING(10.9, 7.0);
/**
 * The recommended exposure index.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifRecommendedExposureIndex  IMAGEIO_AVAILABLE_STARTING(10.9, 7.0);
/**
 * The ISO speed setting used to capture the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifISOSpeed  IMAGEIO_AVAILABLE_STARTING(10.9, 7.0);
/**
 * The ISO speed latitude yyy value.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifISOSpeedLatitudeyyy  IMAGEIO_AVAILABLE_STARTING(10.9, 7.0);
/**
 * The ISO speed latitude zzz value.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifISOSpeedLatitudezzz  IMAGEIO_AVAILABLE_STARTING(10.9, 7.0);
/**
 * The EXIF version.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifVersion  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The original date and time.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifDateTimeOriginal  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The digitized date and time.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifDateTimeDigitized  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifOffsetTime  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifOffsetTimeOriginal  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifOffsetTimeDigitized  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The components configuration for compressed data.
 *
 * For compressed data, specifies that the channels of each component are arranged in increasing numeric order (from first component to the fourth).
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifComponentsConfiguration  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The bits per pixel of the compression mode.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifCompressedBitsPerPixel  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The shutter speed value.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifShutterSpeedValue  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The aperture value.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifApertureValue  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The brightness value.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifBrightnessValue  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The exposure bias value.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifExposureBiasValue  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The maximum aperture value.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifMaxApertureValue  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The distance to the subject, in meters.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubjectDistance  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The metering mode.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifMeteringMode  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The light source.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifLightSource  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The flash status when the image was shot.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFlash  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The focal length.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFocalLength  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The subject area.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubjectArea  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * Information specified by the camera manufacturer.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifMakerNote  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A user comment.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifUserComment  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The fraction of seconds for the date and time tag.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubsecTime  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The fraction of seconds for the original date and time tag.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubsecTimeOriginal  IMAGEIO_AVAILABLE_STARTING(10.11, 10.0);
/**
 * The fraction of seconds for the digitized date and time tag.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubsecTimeDigitized  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The FlashPix version supported by an FPXR file.
 *
 * FlashPix is a format for multiresolution tiled images that facilitates fast onscreen viewing.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFlashPixVersion  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The color space.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifColorSpace  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The x dimension of a pixel.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifPixelXDimension  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The y dimension of a pixel.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifPixelYDimension  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A sound file related to the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifRelatedSoundFile  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The strobe energy when the image was captured, in beam candle power seconds.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFlashEnergy  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The spatial frequency table and spatial frequency response values in the width, height, and diagonal directions.
 *
 * For more information, see ISO 12233.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSpatialFrequencyResponse  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The number of image-width pixels (x-axis) per focal plane resolution unit.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneXResolution  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The number of image-height pixels (y-axis) per focal plane resolution unit.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneYResolution  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The unit of measurement for the focal plane x and y resolutions.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneResolutionUnit  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The location of the image's primary subject.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubjectLocation  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The selected exposure index.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifExposureIndex  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The sensor type of the camera or input device.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSensingMethod  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The image source.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFileSource  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The scene type.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSceneType  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The color filter array (CFA) pattern, which is the geometric pattern of the image sensor for a 1-chip color sensor area.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifCFAPattern  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * Special  rendering performed on the image data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifCustomRendered  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The exposure mode setting.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifExposureMode  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The white balance mode.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifWhiteBalance  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The digital zoom ratio.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifDigitalZoomRatio  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The equivalent focal length in 35 mm film.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifFocalLenIn35mmFilm  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The scene capture type; for example, standard, landscape, portrait, or night.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSceneCaptureType  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The gain adjustment setting.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifGainControl  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The contrast setting.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifContrast  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The saturation setting.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSaturation  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The sharpness setting.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSharpness  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * For a particular camera mode, indicates the conditions for taking the picture.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifDeviceSettingDescription  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The distance to the subject.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubjectDistRange  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The unique ID of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifImageUniqueID  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A string with the name of the camera's owner.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifCameraOwnerName  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * A string with the serial number of the camera.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifBodySerialNumber  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * The specification information for the camera lens.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifLensSpecification  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * A string with the name of the lens manufacturer.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifLensMake  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * A string with the lens model information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifLensModel  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * A string with the lens's serial number.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifLensSerialNumber  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * The gamma setting.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifGamma  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifCompositeImage  IMAGEIO_AVAILABLE_STARTING(10.15.1, 13.1);
/**
 * The number of images that make up a composite image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSourceImageNumberOfCompositeImage  IMAGEIO_AVAILABLE_STARTING(10.15.1, 13.1);
/**
 * The exposure times for composite images.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSourceExposureTimesOfCompositeImage  IMAGEIO_AVAILABLE_STARTING(10.15.1, 13.1);

/* Deprecated. See kCGImagePropertyExifSubsecTimeOriginal */
/**
 * The fraction of seconds for the original date and time tag.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifSubsecTimeOrginal IMAGEIO_AVAILABLE_BUT_DEPRECATED(10.4, 10.11, 4.0, 10.0);

/* Possible keys for kCGImagePropertyExifAuxDictionary */
/**
 * Lens information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxLensInfo  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The lens model.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxLensModel  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The serial number.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxSerialNumber  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The lens ID.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxLensID  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The lens serial number.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxLensSerialNumber  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The image number.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxImageNumber IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * Flash compensation.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxFlashCompensation  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The owner name.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxOwnerName  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * Firmware information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyExifAuxFirmware  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);

/* Possible keys for kCGImagePropertyGIFDictionary */

/**
 * The number of times to repeat an animated sequence.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFLoopCount  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The number of seconds to wait before displaying the next image in an animated sequence, clamped to a minimum of 100 milliseconds.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber> with a floating-point value. The value of this key is never less than 100 millseconds, and the system adjusts values less than that amount to 100 milliseconds, as needed. See ``kCGImagePropertyGIFUnclampedDelayTime``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFDelayTime  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The image color map.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFImageColorMap  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A Boolean value that indicates whether the GIF has a global color map.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfboolean>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFHasGlobalColorMap  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The number of seconds to wait before displaying the next image in an animated sequence.
 *
 * This value may be `0` milliseconds or higher. Unlike the ``kCGImagePropertyGIFDelayTime`` property, this value is not clamped at the low end of the range.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFUnclampedDelayTime  IMAGEIO_AVAILABLE_STARTING(10.7, 4.0);
/**
 * The width of the main image, in pixels.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFCanvasPixelWidth  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The height of the main image, in pixels.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFCanvasPixelHeight  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * An array of dictionaries that contain timing information for the image sequence.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfarray>. Each <doc://com.apple.documentation/documentation/corefoundation/cfdictionary> in the array contains timing information about an image in the sequence.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGIFFrameInfoArray  IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);

/* Possible keys for kCGImagePropertyPNGDictionary */

/**
 * A string that identifies the author of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGAuthor  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * The chromaticities.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGChromaticities  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A string that contains image comments.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGComment  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A string that identifies the copyright of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGCopyright  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * A string that identifies the date and time the image was created.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGCreationTime  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * A string that describes the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGDescription  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * A disclaimer string.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGDisclaimer  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The gamma value.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGGamma  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The interlace type.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGInterlaceType  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A string that identifies the last date and time the image was modified.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGModificationTime  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * A string that identifies the software used to create the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGSoftware  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGSource  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The sRGB intent.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGsRGBIntent  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A string that holds the image's title.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGTitle  IMAGEIO_AVAILABLE_STARTING(10.7, 5.0);
/**
 * A warning string.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGWarning  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The number of x pixels per meter.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGXPixelsPerMeter  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The number of y pixels per meter.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGYPixelsPerMeter  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGPixelsAspectRatio  IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);

/**
 * The number of times that an animated PNG should play through its frames before stopping.
 *
 * A value of `0` means the PNG repeats forever.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAPNGLoopCount  IMAGEIO_AVAILABLE_STARTING(10.10, 8.0);
/**
 * The number of seconds to wait before displaying the next image in an animated sequence.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber> with a floating-point value. The value of this key is never less than 50 millseconds, and the system adjusts values less than that amount to 50 milliseconds, as needed. See ``kCGImagePropertyAPNGUnclampedDelayTime``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAPNGDelayTime  IMAGEIO_AVAILABLE_STARTING(10.10, 8.0);
/**
 * The number of seconds to wait before displaying the next image in an animated sequence.
 *
 * This value may be `0` milliseconds or higher. Unlike the ``kCGImagePropertyAPNGDelayTime`` property, this value is not clamped at the low end of the range.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAPNGUnclampedDelayTime  IMAGEIO_AVAILABLE_STARTING(10.10, 8.0);
/**
 * An array of dictionaries that contain timing information for the image sequence.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfarray>. Each <doc://com.apple.documentation/documentation/corefoundation/cfdictionary> in the array contains timing information about an image in the sequence.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAPNGFrameInfoArray IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The width of the main image, in pixels.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAPNGCanvasPixelWidth IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The height of the main image, in pixels.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAPNGCanvasPixelHeight IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);

/* Possible keys for kCGImagePropertyWebPDictionary */

/**
 * The number of times to play the sequence.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyWebPLoopCount  IMAGEIO_AVAILABLE_STARTING(11.0, 14.0);
/**
 * The number of seconds to wait before displaying the next image in the sequence.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber> with a floating-point value. The value of this key is never less than 100 millseconds, and the system adjusts values less than that amount to 100 milliseconds, as needed. See ``kCGImagePropertyGIFUnclampedDelayTime``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyWebPDelayTime  IMAGEIO_AVAILABLE_STARTING(11.0, 14.0);
/**
 * The unadjusted number of seconds to wait before displaying the next image in the sequence.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber> with a floating-point value.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyWebPUnclampedDelayTime  IMAGEIO_AVAILABLE_STARTING(11.0, 14.0);
/**
 * An array of dictionaries that contain timing information for the image sequence.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfarray>. Each <doc://com.apple.documentation/documentation/corefoundation/cfdictionary> in the array contains timing information about an image in the sequence.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyWebPFrameInfoArray IMAGEIO_AVAILABLE_STARTING(11.0, 14.0);
/**
 * The width of the main image, in pixels.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyWebPCanvasPixelWidth IMAGEIO_AVAILABLE_STARTING(11.0, 14.0);
/**
 * The height of the main image, in pixels.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyWebPCanvasPixelHeight IMAGEIO_AVAILABLE_STARTING(11.0, 14.0);

/* Possible keys for kCGImagePropertyGPSDictionary */

/**
 * The GPS version information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSVersion  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * An indication of whether the latitude is north or south.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSLatitudeRef  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The latitude.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSLatitude  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * An indication of whether the longitude is east or west.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSLongitudeRef  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The longitude.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSLongitude  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The altitude point of reference.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSAltitudeRef  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The altitude.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSAltitude  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The time in UTC (Coordinated Universal Time).
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSTimeStamp  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The satellites used for GPS measurements.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSSatellites  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The status of the GPS receiver.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSStatus  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The measurement mode.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSMeasureMode  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The degree of precision (DOP) of the data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDOP  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The unit for expressing the GPS receiver's speed of movement.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSSpeedRef  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The GPS receiver's speed of movement.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSSpeed  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The reference for the direction of GPS receiver's movement.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSTrackRef  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The direction of GPS receiver's movement.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSTrack  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The reference for the direction of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSImgDirectionRef  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The direction of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSImgDirection  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The geodetic survey data used by the GPS receiver.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSMapDatum  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * An indication of whether the latitude of the destination point is northern or southern.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestLatitudeRef  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The latitude of the destination point.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestLatitude  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * An indication of whether the longitude of the destination point is east or west.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestLongitudeRef  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The longitude of the destination point.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestLongitude  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The reference for giving the bearing to the destination point.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestBearingRef  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The bearing to the destination point.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestBearing  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The units for expressing the distance to the destination point.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestDistanceRef  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The distance to the destination point.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDestDistance  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The name of the method used to find a location.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSProcessingMethod  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The name of the GPS area.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSAreaInformation  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The date and time information relative to Coordinated Universal Time (UTC).
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDateStamp  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * An indication of whether differential correction is applied to the GPS receiver.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSDifferental  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The horizontal error in the GPS position.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGPSHPositioningError  IMAGEIO_AVAILABLE_STARTING(10.10, 8.0);

/* Possible keys for kCGImagePropertyIPTCDictionary */

/**
 * The object type.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCObjectTypeReference  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The object attribute.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCObjectAttributeReference  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The object name.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCObjectName  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The edit status.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCEditStatus  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * An editorial update.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCEditorialUpdate  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The urgency level.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCUrgency  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The subject.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCSubjectReference  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The category.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCategory  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A supplemental category.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCSupplementalCategory  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A fixture identifier.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCFixtureIdentifier  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * Keywords relevant to the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCKeywords  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The content location code.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContentLocationCode  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The content location name.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContentLocationName  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The earliest day on which you can use the image, in the form CCYYMMDD.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCReleaseDate  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The earliest time at which you can use the image, in the form HHMMSS.
 *
 * This time is valid on the release date, which is available in the ``kCGImagePropertyIPTCReleaseDate`` property.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCReleaseTime  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The latest date you can use the image, in the form CCYYMMDD.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExpirationDate  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The latest time on the expiration date you can use the image, in the form HHMMSS.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExpirationTime  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * Special instructions about the use of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCSpecialInstructions  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The advised action.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCActionAdvised  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The reference service.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceService  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The reference date.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceDate  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The reference number.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceNumber  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The creation date.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCDateCreated  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The creation time.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCTimeCreated  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The digital creation date.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCDigitalCreationDate  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The digital creation time.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCDigitalCreationTime  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The originating application.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCOriginatingProgram  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The application version.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCProgramVersion  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The editorial cycle (morning, evening, or both) of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCObjectCycle  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The name of the person who created the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCByline  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The title of the person who created the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCBylineTitle  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The city where the image was created.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCity  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The location within the city where the image was created.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCSubLocation  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The province or state.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCProvinceState  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The primary country code, a three-letter code defined by ISO 3166-1.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCountryPrimaryLocationCode  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The primary country name.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCountryPrimaryLocationName  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The call letter or number combination associated with the originating point of an image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCOriginalTransmissionReference  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * A summary of the contents of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCHeadline  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The name of the service that provided the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCredit  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The original owner of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCSource  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The copyright notice.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCopyrightNotice  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The contact information for getting details about the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContact  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The description of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCaptionAbstract  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The name of the person who wrote or edited the description of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCWriterEditor  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The image type.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCImageType  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The image orientation (portrait, landscape, or square).
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCImageOrientation  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The language identifier, a two-letter code defined by ISO 639:1988.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCLanguageIdentifier  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The star rating.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCStarRating  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The creator's contact info.
 *
 * For a list of keys to include in the contact dictionary, see <doc:iptc-creator-contact-info-dictionary-keys>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCCreatorContactInfo  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);  // IPTC Core
/**
 * The usage rights for the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCRightsUsageTerms  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);    // IPTC Core
/**
 * The scene codes for the image; a scene code is a six-digit string.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCScene  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);               // IPTC Core

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtAboutCvTerm  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtAboutCvTermCvId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtAboutCvTermId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtAboutCvTermName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtAboutCvTermRefinedAbout  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtAddlModelInfo  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkOrObject  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkCircaDateCreated  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkContentDescription  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkContributionDescription  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkCopyrightNotice  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkCreator  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkCreatorID  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkCopyrightOwnerID  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkCopyrightOwnerName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkLicensorID  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkLicensorName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkDateCreated  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkPhysicalDescription  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkSource  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkSourceInventoryNo  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkSourceInvURL  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkStylePeriod  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtArtworkTitle  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtAudioBitrate  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtAudioBitrateMode  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtAudioChannelCount  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtCircaDateCreated  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtContainerFormat  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtContainerFormatIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtContainerFormatName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtContributor  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtContributorIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtContributorName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtContributorRole  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtCopyrightYear  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtCreator  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtCreatorIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtCreatorName     IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtCreatorRole  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtControlledVocabularyTerm  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDataOnScreen  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDataOnScreenRegion  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDataOnScreenRegionD  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDataOnScreenRegionH  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDataOnScreenRegionText  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDataOnScreenRegionUnit  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDataOnScreenRegionW  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDataOnScreenRegionX  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDataOnScreenRegionY  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDigitalImageGUID  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDigitalSourceFileType  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDigitalSourceType  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDopesheet  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDopesheetLink  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDopesheetLinkLink  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtDopesheetLinkLinkQualifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtEmbdEncRightsExpr  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtEmbeddedEncodedRightsExpr  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtEmbeddedEncodedRightsExprType  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtEmbeddedEncodedRightsExprLangID  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtEpisode  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtEpisodeIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtEpisodeName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtEpisodeNumber  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtEvent  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtShownEvent  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtShownEventIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtShownEventName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtExternalMetadataLink  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtFeedIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtGenre  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtGenreCvId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtGenreCvTermId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtGenreCvTermName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtGenreCvTermRefinedAbout  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtHeadline  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtIPTCLastEdited  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLinkedEncRightsExpr  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLinkedEncodedRightsExpr  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLinkedEncodedRightsExprType  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLinkedEncodedRightsExprLangID  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationCreated  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationCity  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationCountryCode  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationCountryName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationGPSAltitude  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationGPSLatitude  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationGPSLongitude  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationLocationId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationLocationName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationProvinceState  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationSublocation  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationWorldRegion  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtLocationShown  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtMaxAvailHeight  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtMaxAvailWidth  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtModelAge  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtOrganisationInImageCode  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtOrganisationInImageName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonHeard  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonHeardIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonHeardName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonInImage  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonInImageWDetails  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonInImageCharacteristic  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonInImageCvTermCvId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonInImageCvTermId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonInImageCvTermName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonInImageCvTermRefinedAbout  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonInImageDescription  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonInImageId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPersonInImageName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtProductInImage  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtProductInImageDescription  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtProductInImageGTIN  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtProductInImageName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPublicationEvent  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPublicationEventDate  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPublicationEventIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtPublicationEventName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRating  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRatingRegion  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionCity  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionCountryCode  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionCountryName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionGPSAltitude  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionGPSLatitude  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionGPSLongitude  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionLocationId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionLocationName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionProvinceState  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionSublocation  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingRegionWorldRegion  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingScaleMaxValue  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingScaleMinValue  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingSourceLink  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingValue  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRatingValueLogoLink  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRegistryID  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRegistryEntryRole  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRegistryItemID  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtRegistryOrganisationID  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtReleaseReady  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtSeason  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtSeasonIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtSeasonName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtSeasonNumber  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtSeries  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtSeriesIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtSeriesName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtStorylineIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtStreamReady  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtStylePeriod  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtSupplyChainSource  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtSupplyChainSourceIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtSupplyChainSourceName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtTemporalCoverage  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtTemporalCoverageFrom  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtTemporalCoverageTo  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtTranscript  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtTranscriptLink  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtTranscriptLinkLink  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtTranscriptLinkLinkQualifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtVideoBitrate  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtVideoBitrateMode  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtVideoDisplayAspectRatio  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtVideoEncodingProfile  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtVideoShotType  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtVideoShotTypeIdentifier  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtVideoShotTypeName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtVideoStreamsCount  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtVisualColor  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtWorkflowTag  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtWorkflowTagCvId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtWorkflowTagCvTermId  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtWorkflowTagCvTermName  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCExtWorkflowTagCvTermRefinedAbout  IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);


/* Possible keys for kCGImagePropertyIPTCCreatorContactInfo dictionary (part of IPTC Core - above) */

/**
 * The city portion of the contact information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoCity  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);
/**
 * The country or region portion of the contact information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoCountry  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);
/**
 * The address portion of the contact information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoAddress  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);
/**
 * The postal code portion of the contact.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoPostalCode  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);
/**
 * The state or province of the contact.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoStateProvince  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);
/**
 * Email addresses for the contact.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoEmails  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);
/**
 * Phone numbers for the contact.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoPhones  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);
/**
 * Web addresses for the contact.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoWebURLs  IMAGEIO_AVAILABLE_STARTING(10.6, 4.0);

/* Possible keys for kCGImageProperty8BIMDictionary */

/**
 * The layer names for an Adobe Photoshop file.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageProperty8BIMLayerNames  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);
/**
 * The Adobe Photoshop file version.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageProperty8BIMVersion  IMAGEIO_AVAILABLE_STARTING(10.10, 8.0);

/* Possible keys for kCGImagePropertyDNGDictionary */

/**
 * An encoding of the four-tier version number.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGVersion  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The oldest version for which a file is compatible.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGBackwardVersion  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * A unique, nonlocalized name for the camera model.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGUniqueCameraModel  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The localized camera model name.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGLocalizedCameraModel  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The camera serial number.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGCameraSerialNumber  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * Information about the lens used for the image.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGLensInfo  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The zero light encoding level, specified as a repeating pattern.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGBlackLevel  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * The saturated encoding level for the raw sample values.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGWhiteLevel  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * The illuminant for the first set of color calibration tags.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGCalibrationIlluminant1  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * The illuminant for an optional second set of color calibration tags.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGCalibrationIlluminant2  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * A transformation matrix that converts XYZ values to reference camera native color spaces, under the first calibration illuminant.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGColorMatrix1  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * A transformation matrix that converts XYZ values to reference camera native color spaces, under the second calibration illuminant.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGColorMatrix2  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * A matrix that transforms reference camera native space values to camera-native space values under the first calibration illuminant.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGCameraCalibration1  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * A matrix that transforms reference camera native space values to camera-native space values under the second calibration illuminant.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGCameraCalibration2  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * The selected white balance at the time of capture, encoded as the coordinates of a neutral color in linear reference space values.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGAsShotNeutral  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * The selected white balance at the time of capture, encoded as x-y chromaticity coordinates.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGAsShotWhiteXY  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * The amount by which to adjust the zero point of the exposure, specified in EV units.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGBaselineExposure  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * The relative noise level of the camera model at an ISO of 100.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGBaselineNoise  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * The amount of sharpening required for this camera model.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGBaselineSharpness  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * Private data that manufacturers may store with an image and use in their own converters.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGPrivateData  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * A string to match against the profile calibration signature for the selected camera profile.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGCameraCalibrationSignature  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * A string that describes the calibration for the current profile.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGProfileCalibrationSignature  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * The amount of noise in the raw image.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGNoiseProfile  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * An opcode to apply a warp to an image to correct for geometric distortion and lateral chromatic aberration for rectilinear lenses.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGWarpRectilinear  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * An opcode to unwrap an image captued with a fisheye lens and map it to a perspective projection.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGWarpFisheye  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
/**
 * An opcode to apply a gain function to an image to correct vignetting.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyDNGFixVignetteRadial  IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);

/**
 * The rectangle that defines the non-masked pixels of the sensor.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGActiveArea  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The analog or digital gain that applies to the stored raw values.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGAnalogBalance  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A hint to the DNG reader about how strong the camera's antialias filter is.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGAntiAliasStrength  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A profile that specifies default color rendering from camera color-space coordinates into the ICC profile space.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGAsShotICCProfile  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A matrix to apply to the camera color-space coordinates before processing values through the ICC profile.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGAsShotPreProfileMatrix  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A string containing the name of the "as shot" camera profile, if any.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGAsShotProfileName  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The amount of EV units to add to the baseline exposure during image rendering.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGBaselineExposureOffset  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A value that specifies how closely green pixels in the blue/green rows track the green pixels in red/green rows.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGBayerGreenSplit  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The scale factor to apply to the default scale to achieve the best quality image size.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGBestQualityScale  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The difference between the zero-light encoding level for each column and the baseline zero-light encoding level.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGBlackLevelDeltaH  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The difference between the zero-light encodoing level for each row and the baseline zero-light encoding level.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGBlackLevelDeltaV  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The repeat pattern size for the black level tag.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGBlackLevelRepeatDim  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The spatial layout of the CFA.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGCFALayout  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A mapping between the values in the CFA pattern tag and the plane numbers in linear raw space.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGCFAPlaneColor  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A hint to the DNG reader about how much chroma blur to apply to the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGChromaBlurRadius  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The colorimetric reference for the CIE XYZ values.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGColorimetricReference  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A profile that specifies default color rendering from camera color-space coordinates into the ICC profile space.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGCurrentICCProfile  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A matrix to apply to the current camera color-space coordinates before processing values through the ICC profile.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGCurrentPreProfileMatrix  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A hint to the raw converter about how to handle the black point during rendering.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGDefaultBlackRender  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The origin of the final image area, relative to the top-left corner of the active area rectangle.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGDefaultCropOrigin  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The size of the final image area, in raw image coordinates.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGDefaultCropSize  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The default scale factors for each direction to convert the image to square pixels.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGDefaultScale  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A default user-crop rectangle in relative coordinates.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGDefaultUserCrop  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A list of file offsets to extra camera profiles.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGExtraCameraProfiles  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A matrix that maps white balanced camera colors to XYZ D50 colors.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGForwardMatrix1  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A matrix that maps white balanced camera colors to XYZ D50 colors.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGForwardMatrix2  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A lookup table that maps stored values into linear values.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGLinearizationTable  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The fraction of the encoding range, above which the response may become significantly non-linear.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGLinearResponseLimit  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A Boolean value that tells the DNG reader whether the EXIF MakerNote tag is safe to preserve.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGMakerNoteSafety  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A list of non-overlapping rectangles that contain fully masked pixels in the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGMaskedAreas  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * An MD5 digest of the raw image data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGNewRawImageDigest  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The amount of noise reduction applied to the raw data on a scale of 0.0 to 1.0.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGNoiseReductionApplied  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The list of opcodes to apply to the raw image, as read directly from the file.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGOpcodeList1  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * THe list of opcodes to apply to the raw image, after mapping it to linear reference values.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGOpcodeList2  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The list of opcodes to apply to the raw image, after demosaicing it.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGOpcodeList3  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The best-quality final size of the larger original file that was the source of this proxy.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGOriginalBestQualityFinalSize  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The default crop size of the larger original file that was the source of this proxy.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGOriginalDefaultCropSize  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * THe default final size of the larger original file that was the source of this proxy.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGOriginalDefaultFinalSize  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The compressed contents of the original raw file.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGOriginalRawFileData  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * An MD5 digest of the data stored for the original raw file data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGOriginalRawFileDigest  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The file name of the original raw file.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGOriginalRawFileName  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The name of the app that created the preview stored in the IFD.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGPreviewApplicationName  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The version number of the app that created the preview stored in the IFD.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGPreviewApplicationVersion  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The color space associated with the rendered preview.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGPreviewColorSpace  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The date and time for the render of the preview.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGPreviewDateTime  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A unique ID of the conversion settings used to render the preview.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGPreviewSettingsDigest  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The name of the conversion settings for the preview.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGPreviewSettingsName  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The copyright information for the camera profile.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileCopyright  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The usage rules for the camera profile.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileEmbedPolicy  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The data for the first hue/saturation/value mapping table.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileHueSatMapData1  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The data for the second hue/saturation/value mapping table.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileHueSatMapData2  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The number of input samples in each dimension of the hue/saturation/value mapping tables.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileHueSatMapDims  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The encoding option to use when indexing into a 3D look table during raw conversion.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileHueSatMapEncoding  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The default "look" table to apply when processing the image as a starting point for user adjustment.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileLookTableData  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The number of input samples in each dimentsion of a default "look" table.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileLookTableDims  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The encoding option to use when indexing into a 3D look table during raw conversion.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileLookTableEncoding  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A string containing the name of the camera profile.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileName  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The default tone curve to apply when processing the image as a starting point for user adjustments.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGProfileToneCurve  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A 16-byte unique identifier for the raw image data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGRawDataUniqueID  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A modified MD5 digest of the raw image data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGRawImageDigest  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The gain between the main raw IFD and the preview IFD that contains this tag.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGRawToPreviewGain  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A reduction matrix that converts color camera-native space values to XYZ values, under the first calibration illuminant.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGReductionMatrix1  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A reduction matrix that converts color camera-native space values to XYZ values, under the second calibration illuminant.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGReductionMatrix2  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The number of interleaved fields for the rows of the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGRowInterleaveFactor  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * A tag that Adobe Camera Raw uses to control the sensitivity of its Shadows slider.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGShadowScale  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);
/**
 * The size of rectangular blocks that tiles use to group pixels.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyDNGSubTileBlockSize  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);



/* Possible keys for kCGImagePropertyCIFFDictionary */

/**
 * The camera description.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFDescription  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The firmware version of the camera.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFFirmware  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The name of the camera's owner.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFOwnerName  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The image name.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFImageName  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The image file name.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFImageFileName  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The method of shutter release—single-shot or continuous.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFReleaseMethod  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The priority for shutter release timing—shutter or focus.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFReleaseTiming  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The number of images taken since the camera shipped.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFRecordID  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The time in milliseconds until shutter release when using the self-timer.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFSelfTimingTime  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The camera serial number.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFCameraSerialNumber  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The image serial number.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFImageSerialNumber  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The continuous drive mode.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFContinuousDrive  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The focus mode.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFFocusMode  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The metering mode.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFMeteringMode  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The shooting mode.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFShootingMode  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The lens model.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFLensModel  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The maximum lens length in millimeters.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFLensMaxMM  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The minimum lens length in millimeters.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFLensMinMM  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The white balance index.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFWhiteBalanceIndex  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The flash exposure compensation.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFFlashExposureComp  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The measured exposure value.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyCIFFMeasuredEV  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);


/* Possible keys for kCGImagePropertyMakerNikonDictionary */

/**
 * The ISO setting.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonISOSetting  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The color mode.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonColorMode  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The quality setting.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonQuality  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The white balance mode.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonWhiteBalanceMode  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The sharpening mode.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonSharpenMode  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The focus mode.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFocusMode  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The flash setting.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFlashSetting  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The ISO selection.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonISOSelection  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The flash exposure compensation.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFlashExposureComp  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The image adjustment setting.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonImageAdjustment  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The lens adapter.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonLensAdapter  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The lens type.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonLensType  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * Lens information.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonLensInfo  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The focus distance.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFocusDistance  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The digital zoom setting.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonDigitalZoom  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The shooting mode.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonShootingMode  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The camera serial number.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonCameraSerialNumber  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The number of times the shutter has been actuated.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerNikonShutterCount  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);

/* Possible keys for kCGImagePropertyMakerCanonDictionary */

/**
 * The name of the camera's owner.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonOwnerName  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The camera serial number.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonCameraSerialNumber  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The image serial number.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonImageSerialNumber  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The flash exposure compensation setting.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonFlashExposureComp  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The presence of a continuous drive.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonContinuousDrive  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The lens model.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonLensModel  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The firmware version.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonFirmware  IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);
/**
 * The image aspect ratio.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyMakerCanonAspectRatioInfo IMAGEIO_AVAILABLE_STARTING(10.5, 4.0);

/*  For EXR files:
 *  The value (CFNumberRef) specifies the EXR compression method. See AppleEXR.h for possible values.
 *  Default value if not specified is 'axr_compression_piz'
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyOpenEXRCompression    IMAGEIO_AVAILABLE_STARTING(13.0, 16.1);

/* Possible keys for kCGImagePropertyOpenEXRDictionary */
/**
 * The aspect ratio of the image.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyOpenEXRAspectRatio  IMAGEIO_AVAILABLE_STARTING(10.9, 11.3);


/* Possible int values for kCGImagePropertyTIFFOrientation */
/**
 * A value describing the intended display orientation for an image.
 *
 * Values of this type define the position of the pixel coordinate origin point (`0,0`) and the directions of the coordinate axes relative to the intended display orientation of the image. Orientation values are commonly found in image metadata, and specifying image orientation correctly can be important both for displaying the image and for certain image processing tasks such as face recognition.
 *
 * For example, the pixel data for an image captured by an iOS device camera is encoded in the camera sensor's native landscape orientation. When the user captures a photo while holding the device in portrait orientation, iOS writes an orientation value of ``right`` in the resulting image file. Software displaying the image can then, after reading that value from the file's metadata, apply a 90° clockwise rotation to the image data so that the image appears in the photographer's intended orientation.
 *
 * ![To correct an image with right orientation for display, rotate it 90° clockwise.](media-2948298)
 *
 * ### Compatibility with UIImageOrientation
 *
 * The ``CGImagePropertyOrientation`` type covers the same set of orientation names available in from the <doc://com.apple.documentation/documentation/uikit/uiimage/orientation> type, but the underlying numeric values of each type do not match. (For example, the "left mirrored" orientation has an underlying value of 5 in ``CGImagePropertyOrientation``, but an underlying value of 7 in <doc://com.apple.documentation/documentation/uikit/uiimage/orientation>.) If you have an orientation value in one type and need a semantically equivalent value in the other, use a function such as those below to produce the same-named value in the other type:
 *
 * @TabNavigator {
 *     @Tab("Swift") {
 *         ```swift
 *         extension CGImagePropertyOrientation {
 *             init(_ uiOrientation: UIImage.Orientation) {
 *                 switch uiOrientation {
 *                     case .up: self = .up
 *                     case .upMirrored: self = .upMirrored
 *                     case .down: self = .down
 *                     case .downMirrored: self = .downMirrored
 *                     case .left: self = .left
 *                     case .leftMirrored: self = .leftMirrored
 *                     case .right: self = .right
 *                     case .rightMirrored: self = .rightMirrored
 *                 @unknown default:
 *                     fatalError()
 *                 }
 *             }
 *         }
 *         extension UIImage.Orientation {
 *             init(_ cgOrientation: CGImagePropertyOrientation) {
 *                 switch cgOrientation {
 *                     case .up: self = .up
 *                     case .upMirrored: self = .upMirrored
 *                     case .down: self = .down
 *                     case .downMirrored: self = .downMirrored
 *                     case .left: self = .left
 *                     case .leftMirrored: self = .leftMirrored
 *                     case .right: self = .right
 *                     case .rightMirrored: self = .rightMirrored
 *                 @unknown default:
 *                     fatalError()
 *                 }
 *             }
 *         }
 *         ```
 *     }
 *     @Tab("Objective-C") {
 *         ```objc
 *         CGImagePropertyOrientation CGImagePropertyOrientationForUIImageOrientation(UIImageOrientation uiOrientation) {
 *             switch (uiOrientation) {
 *                 case UIImageOrientationUp: return kCGImagePropertyOrientationUp;
 *                 case UIImageOrientationDown: return kCGImagePropertyOrientationDown;
 *                 case UIImageOrientationLeft: return kCGImagePropertyOrientationLeft;
 *                 case UIImageOrientationRight: return kCGImagePropertyOrientationRight;
 *                 case UIImageOrientationUpMirrored: return kCGImagePropertyOrientationUpMirrored;
 *                 case UIImageOrientationDownMirrored: return kCGImagePropertyOrientationDownMirrored;
 *                 case UIImageOrientationLeftMirrored: return kCGImagePropertyOrientationLeftMirrored;
 *                 case UIImageOrientationRightMirrored: return kCGImagePropertyOrientationRightMirrored;
 *             }
 *         }
 *         UIImageOrientation UIImageOrientationForCGImagePropertyOrientation(CGImagePropertyOrientation cgOrientation) {
 *             switch (cgOrientation) {
 *                 case kCGImagePropertyOrientationUp: return UIImageOrientationUp;
 *                 case kCGImagePropertyOrientationDown: return UIImageOrientationDown;
 *                 case kCGImagePropertyOrientationLeft: return UIImageOrientationLeft;
 *                 case kCGImagePropertyOrientationRight: return UIImageOrientationRight;
 *                 case kCGImagePropertyOrientationUpMirrored: return UIImageOrientationUpMirrored;
 *                 case kCGImagePropertyOrientationDownMirrored: return UIImageOrientationDownMirrored;
 *                 case kCGImagePropertyOrientationLeftMirrored: return UIImageOrientationLeftMirrored;
 *                 case kCGImagePropertyOrientationRightMirrored: return UIImageOrientationRightMirrored;
 *             }
 *         }
 *         ```
 *     }
 * }
 *
 * ### Working with Raw TIFF/Exif Numeric Values
 *
 * Some APIs describe image orientation with basic integer values, intended for interpretation according to the TIFF and Exif specifications. The ``CGImagePropertyOrientation`` type simply defines symbolic names for those values, so you can convert to and from the raw numeric type with C type-cast syntax or the inherited <doc://com.apple.documentation/documentation/swift/rawrepresentable/init(rawvalue:)> initializer and <doc://com.apple.documentation/documentation/swift/rawrepresentable/rawvalue-swift.property> property in Swift.
 */
typedef CF_CLOSED_ENUM(uint32_t, CGImagePropertyOrientation) {
    /**
     * The encoded image data matches the image's intended display orientation.
     *
     * The (x,y) pixel coordinates of the origin point (0,0) represent the leftmost column and top row, respectively. Pixel (x,y) positions increase left-to-right, top-to-bottom.
     *
     * If an image is encoded with this orientation, then displayed by software unaware of orientation metadata, the image appears correctly "right side up". That is, this orientation is an identity value.
     *
     * ![An image in up orientation can be presented for display without rotating or flipping.](media-2948288)
     */
    kCGImagePropertyOrientationUp = 1,        // 0th row at top,    0th column on left   - default orientation
    /**
     * The encoded image data is horizontally flipped from the image's intended display orientation.
     *
     * The (x,y) pixel coordinates of the origin point (0,0) represent the rightmost column and top row, respectively. Pixel (x,y) positions increase right-to-left, top-to-bottom.
     *
     * If an image is encoded with this orientation, then displayed by software unaware of orientation metadata, the image appears horizontally mirrored.
     *
     * ![To correct an image with upMirrored orientation for display, flip it horizontally.](media-2948289)
     */
    kCGImagePropertyOrientationUpMirrored,    // 0th row at top,    0th column on right  - horizontal flip
    /**
     * The encoded image data is rotated 180° from the image's intended display orientation.
     *
     * The (x,y) pixel coordinates of the origin point (0,0) represent the rightmost column and bottom row, respectively. Pixel (x,y) positions increase right-to-left, bottom-to-top.
     *
     * If an image is encoded with this orientation, then displayed by software unaware of orientation metadata, the image appears rotated 180°.
     *
     * ![To correct an image with down orientation for display, rotate it 180°.](media-2948290)
     */
    kCGImagePropertyOrientationDown,          // 0th row at bottom, 0th column on right  - 180 deg rotation
    /**
     * The encoded image data is vertically flipped from the image's intended display orientation.
     *
     * The (x,y) pixel coordinates of the origin point (0,0) represent the leftmost column and bottom row, respectively. Pixel (x,y) positions increase left-to-right, bottom-to-top.
     *
     * If an image is encoded with this orientation, then displayed by software unaware of orientation metadata, the image appears vertically flipped. (Alternatively, the image is rotated 180° and then flipped horizontally.)
     *
     * ![To correct an image with downMirrored orientation for display, flip it vertically.](media-2948294)
     */
    kCGImagePropertyOrientationDownMirrored,  // 0th row at bottom, 0th column on left   - vertical flip
    /**
     * The encoded image data is horizontally flipped and rotated 90° counter-clockwise from the image's intended display orientation.
     *
     * The (x,y) pixel coordinates of the origin point (0,0) represent the top row and leftmost column, respectively. Pixel (x,y) positions increase top-to-bottom, left-to-right.
     *
     * If an image is encoded with this orientation, then displayed by software unaware of orientation metadata, the image appears to be horizontally mirrored, then rotated 90° counter-clockwise. (That is, to present the image in its intended orientation, you can rotate it 90° clockwise, then flip horizontally.)
     *
     * ![To correct an image with leftMirrored orientation for display, rotate it 90° clockwise then flip it horizontally.](media-2948297)
     */
    kCGImagePropertyOrientationLeftMirrored,  // 0th row on left,   0th column at top
    /**
     * The encoded image data is rotated 90° counter-clockwise from the image's intended display orientation.
     *
     * The (x,y) pixel coordinates of the origin point (0,0) represent the top row and rightmost column, respectively. Pixel (x,y) positions increase top-to-bottom, right-to-left.
     *
     * If an image is encoded with this orientation, then displayed by software unaware of orientation metadata, the image appears to be rotated 90° counter-clockwise. (That is, to present the image in its intended orientation, you must rotate it 90° clockwise.)
     *
     * ![To correct an image with right orientation for display, rotate it 90° clockwise.](media-2948299)
     */
    kCGImagePropertyOrientationRight,         // 0th row on right,  0th column at top    - 90 deg CW
    /**
     * The encoded image data is horizontally flipped and rotated 90° clockwise from the image's intended display orientation.
     *
     * The (x,y) pixel coordinates of the origin point (0,0) represent the bottom row and rightmost column, respectively. Pixel (x,y) positions increase bottom-to-top, right-to-left.
     *
     * If an image is encoded with this orientation, then displayed by software unaware of orientation metadata, the image appears to be horizontally mirrored, then rotated 90° clockwise. (That is, to present the image in its intended orientation, you can rotate  90° counter-clockwise, then flip horizontally.)
     *
     * ![To correct an image with rightMirrored orientation for display, rotate it 90° counterclockwise then flip it horizontally.](media-2948300)
     */
    kCGImagePropertyOrientationRightMirrored, // 0th row on right,  0th column on bottom
    /**
     * The encoded image data is rotated 90° clockwise from the image's intended display orientation.
     *
     * The (x,y) pixel coordinates of the origin point (0,0) represent the bottom row and leftmost column, respectively. Pixel (x,y) positions increase bottom-to-top, left-to-right.
     *
     * If an image is encoded with this orientation, then displayed by software unaware of orientation metadata, the image appears to be rotated 90° clockwise. (That is, to present the image in its intended orientation, you must rotate 90° counter-clockwise.)
     *
     * ![To correct an image with left orientation for display, rotate it 90° counterclockwise.](media-2948296)
     */
    kCGImagePropertyOrientationLeft           // 0th row on left,   0th column at bottom - 90 deg CCW
};


/* Possible keys for kCGImagePropertyTGADictionary */
IMAGEIO_EXTERN const CFStringRef  kCGImagePropertyTGACompression IMAGEIO_AVAILABLE_STARTING(11.0, 14.0);

/* Possible int values for kCGImagePropertyTGACompression */
/**
 * Possible values for ``kCGImagePropertyTGACompression``.
 */
typedef CF_CLOSED_ENUM(uint32_t, CGImagePropertyTGACompression) {
    kCGImageTGACompressionNone = 0,
    kCGImageTGACompressionRLE,
};

/*
 * Allows client to choose the filters applied before PNG compression
 * http://www.libpng.org/pub/png/book/chapter09.html#png.ch09.div.1
 * The value should be a CFNumber, of type long, containing a bitwise OR of the desired filters
 * The filters are defined below, IMAGEIO_PNG_NO_FILTERS, IMAGEIO_PNG_FILTER_NONE, etc
 * This value has no effect when compressing to any format other than PNG
 */
/**
 * The PNG filter to apply prior to compression.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>. The number contains a bitwise-OR of one or more filter constants, such as ``IMAGEIO_PNG_FILTER_AVG`` or ``IMAGEIO_PNG_FILTER_SUB``. The value has no effect on formats other than PNG.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGCompressionFilter IMAGEIO_AVAILABLE_STARTING(10.11, 9.0);

/** No PNG filters. */
#define IMAGEIO_PNG_NO_FILTERS     0x00
/** A filter in which each byte is unchanged. */
#define IMAGEIO_PNG_FILTER_NONE    0x08
/** A filter in which each byte is replaced with the difference between it and the corresponding byte to its left. */
#define IMAGEIO_PNG_FILTER_SUB     0x10
/** A filter in which each byte is replaced with the difference between it and the byte above it. */
#define IMAGEIO_PNG_FILTER_UP      0x20
/** A filter in which each byte is replaced with the difference between it and the average of the bytes above it and to its left. */
#define IMAGEIO_PNG_FILTER_AVG     0x40
/** A filter in which each byte is replaced with the difference between it and the Paeth predictor of the bytes to its left, above, and upper left. */
#define IMAGEIO_PNG_FILTER_PAETH   0x80
/** All PNG filters. */
#define IMAGEIO_PNG_ALL_FILTERS (IMAGEIO_PNG_FILTER_NONE | IMAGEIO_PNG_FILTER_SUB | IMAGEIO_PNG_FILTER_UP | IMAGEIO_PNG_FILTER_AVG | IMAGEIO_PNG_FILTER_PAETH)

/*
 * For PNG files:
 * When writing indexed color PNGs, the data for the transparity chunk 'tRNS' can be passed in with this key.
 * The value (CFDataRef) should contain one byte transparency info for each entry in the indexed color map.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPNGTransparency     IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);


/* For use with CGImageSourceCopyAuxiliaryDataInfoAtIndex and CGImageDestinationAddAuxiliaryDataInfo:
 * These strings specify the 'auxiliaryImageDataType':
 */
/**
 * The type for depth map information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeDepth IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * The type for image disparity information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeDisparity IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * The type for portrait effects matte information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypePortraitEffectsMatte IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);

/**
 * The type for skin matte informaton.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeSemanticSegmentationSkinMatte IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The type for hair matte information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeSemanticSegmentationHairMatte IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The type for teeth matte information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeSemanticSegmentationTeethMatte IMAGEIO_AVAILABLE_STARTING(10.15, 13.0);
/**
 * The type for glasses matte informaton.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeSemanticSegmentationGlassesMatte IMAGEIO_AVAILABLE_STARTING(11.0, 14.1);
/**
 * The type for sky matte information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeSemanticSegmentationSkyMatte IMAGEIO_AVAILABLE_STARTING(11.0, 14.1);
/**
 * The type for High Dynamic Range (HDR) gain map information.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeHDRGainMap   IMAGEIO_AVAILABLE_STARTING(11.0, 14.1);
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataTypeISOGainMap   IMAGEIO_AVAILABLE_STARTING(15.0, 18);


/* Depth/Disparity data support for JPEG, HEIF, and DNG images:
 * CGImageSourceCopyAuxiliaryDataInfoAtIndex and CGImageDestinationAddAuxiliaryDataInfo will use these keys in the dictionary:
 * kCGImageAuxiliaryDataInfoData - the depth data (CFDataRef)
 * kCGImageAuxiliaryDataInfoDataDescription - the depth data description (CFDictionary)
 * kCGImageAuxiliaryDataInfoMetadata - metadata (CGImageMetadataRef)
 * kCGImageAuxiliaryDataInfoColorSpace - the color space associated with the aux image (CGColorSpaceRef)
 */
/**
 * The auxiliary data for the image.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfdata>. Use the ``kCGImagePropertyAuxiliaryDataType`` property to determine the format of this data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataInfoData IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * A dictionary of keys that describe the auxiliary data.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfdictionary>. The keys in this dictionary may include ``kCGImagePropertyWidth``, ``kCGImagePropertyHeight``, and ``kCGImagePropertyBytesPerRow``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataInfoDataDescription IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * The metadata for any auxiliary data.
 *
 * The value of this property is a ``CGImageMetadata`` type. Use it to obtain any metadata associated with the auxiliary data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataInfoMetadata IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
IMAGEIO_EXTERN const CFStringRef kCGImageAuxiliaryDataInfoColorSpace IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);

/**
 * The number of images in the file.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyImageCount IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * The width of the image, in the image's coordinate space.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyWidth IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * The height of the image, in the image's coordinate space.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyHeight IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * The total number of bytes in each row of the image.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyBytesPerRow IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * The name of the image's color space.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfstring>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyNamedColorSpace IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * The format of the image's individual pixels.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>. For information about how to interpret this value, see the `PixelFormat` tag in the EXIF specification.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPixelFormat IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * An array of dictionaries, each of which contains metadata for one of the images in the file.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfarray>. Each element in the array is a <doc://com.apple.documentation/documentation/corefoundation/cfdictionary> that contains metadata for one of the images. For example, the dictionary might contain the width and height of the image, the image's color space name, thumbnail image information, and any auxiliary data.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyImages IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyThumbnailImages IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * An array of dictionaries that contain auxiliary data for the images.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfarray>. Each <doc://com.apple.documentation/documentation/corefoundation/cfdictionary> in the array contains auxiliary data for one of the images in the file. Use the ``kCGImagePropertyAuxiliaryDataType`` key to determine the type of data associated with the image.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAuxiliaryData IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
/**
 * The type of the auxiliary data.
 *
 * The value of this property is a <doc://com.apple.documentation/documentation/corefoundation/cfstring>. The value of this key might be ``kCGImageAuxiliaryDataTypeDisparity``, ``kCGImageAuxiliaryDataTypeDepth``, or another auxiliary data type.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyAuxiliaryDataType IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyImageIndex IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroups IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupIndex IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupType IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupTypeStereoPair IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupTypeAlternate IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImagesAlternate IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImageIndexLeft IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImageIndexRight IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImageIndexMonoscopic IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImageIsLeftImage IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImageIsRightImage IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImageIsMonoscopicImage IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImageIsAlternateImage IMAGEIO_AVAILABLE_STARTING(12.0, 15.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImageBaseline IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImageDisparityAdjustment IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupImageStereoAggressors IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);

IMAGEIO_EXTERN const CFStringRef kIIOStereoAggressors_Type IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);
IMAGEIO_EXTERN const CFStringRef kIIOStereoAggressors_SubTypeURI IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);
IMAGEIO_EXTERN const CFStringRef kIIOStereoAggressors_Severity IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);

IMAGEIO_EXTERN const CFStringRef kCGImagePropertyGroupMonoscopicImageLocation IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);
IMAGEIO_EXTERN const CFStringRef kIIOMonoscopicImageLocation_Unspecified IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);
IMAGEIO_EXTERN const CFStringRef kIIOMonoscopicImageLocation_Left IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);
IMAGEIO_EXTERN const CFStringRef kIIOMonoscopicImageLocation_Right IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);
IMAGEIO_EXTERN const CFStringRef kIIOMonoscopicImageLocation_Center IMAGEIO_AVAILABLE_STARTING(15.0, 18.0);

IMAGEIO_EXTERN const CFStringRef kIIOMetadata_CameraExtrinsicsKey  IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
IMAGEIO_EXTERN const CFStringRef kIIOCameraExtrinsics_CoordinateSystemID IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
IMAGEIO_EXTERN const CFStringRef kIIOCameraExtrinsics_Position IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
IMAGEIO_EXTERN const CFStringRef kIIOCameraExtrinsics_Rotation IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);

IMAGEIO_EXTERN const CFStringRef kIIOMetadata_CameraModelKey IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
IMAGEIO_EXTERN const CFStringRef kIIOCameraModel_ModelType IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
IMAGEIO_EXTERN const CFStringRef kIIOCameraModelType_SimplifiedPinhole IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
IMAGEIO_EXTERN const CFStringRef kIIOCameraModelType_GenericPinhole IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);
IMAGEIO_EXTERN const CFStringRef kIIOCameraModel_Intrinsics IMAGEIO_AVAILABLE_STARTING(13.0, 16.0);

IMAGEIO_EXTERN const CFStringRef kCGImageProviderPreferredTileWidth IMAGEIO_AVAILABLE_STARTING(16.0, 19.0);
IMAGEIO_EXTERN const CFStringRef kCGImageProviderPreferredTileHeight IMAGEIO_AVAILABLE_STARTING(16.0, 19.0);
CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif  /* __CGIMAGEPROPERTIES__ */
