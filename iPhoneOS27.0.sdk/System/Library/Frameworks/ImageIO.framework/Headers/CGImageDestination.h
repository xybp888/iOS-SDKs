/*
 * ImageIO - CGImageDestination.h
 * Copyright (c) 2004-2016 Apple Inc. All rights reserved.
 *
 */

#ifndef CGIMAGEDESTINATION_H_
#define CGIMAGEDESTINATION_H_

#include <ImageIO/ImageIOBase.h>

/**
 * An opaque type that you use to write image data to a URL, data object, or data consumer.
 *
 * A ``CGImageDestination`` object provides an abstract interface for saving image data. Use an image destination to represent a single image, or multiple images packaged together. For example, you might create an image that also contains a thumbnail. You can also use the image destination to add metadata to your images.
 *
 * An image destination outputs data to a URL, a `CFData` object, or a <doc://com.apple.documentation/documentation/coregraphics/cgdataconsumer> object, which you specify at creation time. After you create the image destination, add the image data and properties. When you are done, call ``CGImageDestinationFinalize(_:)`` to finalize the image data and write it to the output location.
 *
 * For more information, see [Image I/O Programming Guide](https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/ImageIOGuide/imageio_intro/ikpg_intro.html#//apple_ref/doc/uid/TP40005462).
 */
typedef struct IIO_BRIDGED_TYPE(id) CGImageDestination * CGImageDestinationRef;

#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/CGImageSource.h>
#include <ImageIO/CGImageMetadata.h>

CF_IMPLICIT_BRIDGING_ENABLED

/** Properties which may be passed to "CGImageDestinationAddImage"
 ** or "CGImageDestinationAddImageFromSource" to effect the output.
 ** The values apply to a single image of an image destination. **/

CF_ASSUME_NONNULL_BEGIN

/* The desired compression quality to use when writing to an image 
 * destination. If present, the value of this key is a CFNumberRef 
 * in the range 0.0 to 1.0. A value of 1.0 implies lossless
 * compression is desired if destination format supports it. 
 * A value of 0.0 implies that that maximum compression is 
 * desired. */

/**
 * The desired compression quality to use when writing the image data.
 *
 * If present, the value associated with this key must be a `CFNumberRef` data type in the range `0.0` to `1.0`. A value of `1.0` specifies to use lossless compression if destination format supports it. A value of 0.0 implies to use maximum compression.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationLossyCompressionQuality  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);


/* The desired background color to composite against when writing 
 * an image with alpha to a destination format that does not support 
 * alpha. If present, the value of this key is a CGColorRef without
 * any alpha component of its own.  If not present a white color
 * will be used if needed. */

/**
 * The background color to use when the image has an alpha component, but the destination format doesn't support alpha.
 *
 * If present, the value associated with this key must be a <doc://com.apple.documentation/documentation/coregraphics/cgcolor> data type without an alpha component of its own. If not present, and if a background color is needed, a white color is used.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationBackgroundColor  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Rescale the image to the maximum width and height in pixels.
 * If present, this value of this key must be a CFNumberRef. */

/**
 * The maximum width and height of the image, in pixels.
 *
 * The value of this key must be a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>. If present, the destination rescales the image as needed to fit within the maximum width and height. If this key isn't present, the destination retains the native image size.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationImageMaxPixelSize  IMAGEIO_AVAILABLE_STARTING(10.10, 8.0);

/* Enable or disable thumbnail embedding for JPEG and HEIF.
 * The value should be kCFBooleanTrue or kCFBooleanFalse. Defaults to kCFBooleanFalse */

/**
 * A Boolean value that indicates whether to embed a thumbnail for JPEG and HEIF images.
 *
 * The value of this key must be a <doc://com.apple.documentation/documentation/corefoundation/cfboolean> value. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEmbedThumbnail  IMAGEIO_AVAILABLE_STARTING(10.10, 8.0);


/* Create an image using a colorspace, that has is compatible with older devices
 * The value should be kCFBooleanTrue or kCFBooleanFalse
 * Defaults to kCFBooleanFalse = don't do any color conversion
 */
/**
 * A Boolean value that indicates whether to create the image using a colorspace.
 *
 * The value of this key must be a <doc://com.apple.documentation/documentation/corefoundation/cfboolean> value. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>. Include this key and set it to <doc://com.apple.documentation/documentation/corefoundation/kcfbooleantrue> to color convert the image using its colorspace, which provides better compatibility with older devices.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationOptimizeColorForSharing  IMAGEIO_AVAILABLE_STARTING(10.12, 9.3);


/* Return the CFTypeID for CGImageDestinations. */

/**
 * Returns the unique type identifier of an image destination opaque type.
 *
 * - Returns: Returns the Core Foundation type ID for an image destination.
 *
 * A type identifier is an integer that identifies the opaque type to which a Core Foundation object belongs. You use type IDs in various contexts, such as when you are operating on heterogeneous collections.
 */
IMAGEIO_EXTERN CFTypeID CGImageDestinationGetTypeID(void)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Return an array of supported type identifiers. */

/**
 * Returns an array of the uniform type identifiers that are supported for image destinations.
 *
 * - Returns: Returns an array of the uniform type identifiers that image destinations support. For a list of system-declared and third-party identifiers, see <doc://com.apple.documentation/documentation/uniformtypeidentifiers>.
 */
IMAGEIO_EXTERN CFArrayRef _iio_Nonnull CGImageDestinationCopyTypeIdentifiers(void)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Create an image destination writing to the data consumer `consumer'.
 * The parameter `type' specifies the type identifier of the resulting
 * image file.  Constants for `type' are found in the LaunchServices framework
 * header UTCoreTypes.h.  The parameter `count' specifies number of images
 * (not including thumbnails) that the image file will contain. The `options'
 * dictionary is reserved for future use; currently, you should pass NULL for
 * this parameter. */

/**
 * Creates an image destination that writes to the specified data consumer.
 *
 * - Parameters:
 *   - consumer: A data consumer object to store the image data.
 *   - type: The uniform type identifier of the resulting image file. For a list of system-declared and third-party identifiers, see <doc://com.apple.documentation/documentation/uniformtypeidentifiers>.
 *   - count: The number of images (not including thumbnail images) you want to include in the image file.
 *   - options: Future options. Specify `NULL` for this parameter.
 *
 * - Returns: An image destination, or `NULL` if an error occurs. You are responsible for releasing this object using <doc://com.apple.documentation/documentation/corefoundation/cfrelease>.
 */
IMAGEIO_EXTERN CGImageDestinationRef _iio_Nullable CGImageDestinationCreateWithDataConsumer(CGDataConsumerRef _iio_Nonnull consumer, CFStringRef _iio_Nonnull type, size_t count, CFDictionaryRef _iio_Nullable options)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Create an image destination writing to `data'. The parameter `type'
 * specifies the type identifier of the resulting image file.  Constants for
 * `type' are found in the LaunchServices framework header UTCoreTypes.h.  The
 * parameter `count' specifies number of images (not including thumbnails)
 * that the image file will contain. The `options' dictionary is reserved
 * for future use; currently, you should pass NULL for this parameter. */

/**
 * Creates an image destination that writes to a Core Foundation mutable data object.
 *
 * - Parameters:
 *   - data: The data object in which to store the image data.
 *   - type: The uniform type identifier of the resulting image file. For a list of system-declared and third-party identifiers, see <doc://com.apple.documentation/documentation/uniformtypeidentifiers>.
 *   - count: The number of images (not including thumbnail images) you want to include in the image file.
 *   - options: Future options. Specify `NULL` for this parameter.
 *
 * - Returns: An image destination, or `NULL` if an error occurs. You are responsible for releasing this object using <doc://com.apple.documentation/documentation/corefoundation/cfrelease>.
 */
IMAGEIO_EXTERN CGImageDestinationRef _iio_Nullable CGImageDestinationCreateWithData(CFMutableDataRef _iio_Nonnull data, CFStringRef _iio_Nonnull type, size_t count, CFDictionaryRef _iio_Nullable options)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Create an image destination writing to `url'. The parameter `type'
 * specifies the type identifier of the resulting image file.  Constants for
 * `type' are found in the LaunchServices framework header UTCoreTypes.h.  The
 * parameter `count' specifies number of images (not including thumbnails)
 * that the image file will contain. The `options' dictionary is reserved
 * for future use; currently, you should pass NULL for this parameter.
 * Note that if `url' already exists, it will be overwritten. */

/**
 * Creates an image destination that writes image data to the specified URL.
 *
 * - Parameters:
 *   - url: The URL at which to write the image data. This object overwrites any data at the specified URL.
 *   - type: The uniform type identifier of the resulting image file. For a list of system-declared and third-party identifiers, see <doc://com.apple.documentation/documentation/uniformtypeidentifiers>.
 *   - count: The number of images (not including thumbnail images) you want to include in the image file.
 *   - options: Future options. Specify `NULL` for this parameter.
 *
 * - Returns: An image destination, or `NULL` if an error occurs. You are responsible for releasing this object using <doc://com.apple.documentation/documentation/corefoundation/cfrelease>.
 */
IMAGEIO_EXTERN CGImageDestinationRef _iio_Nullable CGImageDestinationCreateWithURL(CFURLRef _iio_Nonnull url, CFStringRef _iio_Nonnull type, size_t count, CFDictionaryRef _iio_Nullable options)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Specify the dictionary `properties' of properties which apply to all
 * images in the image destination `idst'. */

/**
 * Applies one or more properties to all images in an image destination.
 *
 * - Parameters:
 *   - idst: The image destination to modify
 *   - properties: A dictionary that contains the properties to apply. For a list of possible values, see <doc:image-properties> and <doc:CGImageDestination/Configuring-the-Image-Behaviors>.
 */
IMAGEIO_EXTERN void CGImageDestinationSetProperties(CGImageDestinationRef _iio_Nonnull idst, CFDictionaryRef _iio_Nullable properties)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Set the next image in the image destination `idst' to be `image' with
 * optional properties specified in `properties'.  An error is logged if
 * more images are added than specified in the original count of the image
 * destination. */

/**
 * Adds an image to an image destination.
 *
 * - Parameters:
 *   - idst: The image destination to modify.
 *   - image: The image to add.
 *   - properties: An optional dictionary that specifies the properties of the added image. Specify `NULL` to omit any additional properties. For a list of possible values, see <doc:image-properties> and <doc:CGImageDestination/Configuring-the-Image-Behaviors>.
 *
 * The function logs an error if you add more images than what you specified when you created the image destination.
 */
IMAGEIO_EXTERN void CGImageDestinationAddImage(CGImageDestinationRef _iio_Nonnull idst, CGImageRef _iio_Nonnull image, CFDictionaryRef _iio_Nullable properties)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Set the next image in the image destination `idst' to be the image at
 * `index' in the image source `isrc'.  The index is zero-based. The
 * properties of the source image can be added to or overriden by supplying
 * additional keys/values in `properties'.  If a key in `properties' has
 * the value kCFNull, the corresponding property in the destination will be
 * removed. */

/**
 * Adds an image from an image source to an image destination.
 *
 * - Parameters:
 *   - idst: The image destination to modify.
 *   - isrc: An image source that contains the image.
 *   - index: The index of the image in the image source. Specify a valid, zero-based index into the images of the image source. If the index is invalid, this method returns `NULL`.
 *   - properties: An optional dictionary that specifies additional image property information. The added image automatically inherits the properties found in the image source. Use this dictionary to add properties to the image, or to modify one of the inherited properties. To remove an inherited property altogether, specify `NULL` for the property's value. For a list of possible values, see <doc:image-properties> and <doc:CGImageDestination/Configuring-the-Image-Behaviors>.
 */
IMAGEIO_EXTERN void CGImageDestinationAddImageFromSource(CGImageDestinationRef _iio_Nonnull idst, CGImageSourceRef _iio_Nonnull isrc, size_t index, CFDictionaryRef _iio_Nullable properties)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Write everything to the destination data, url or consumer of the image
 * destination `idst'.  You must call this function or the image
 * destination will not be valid.  After this function is called, no
 * additional data will be written to the image destination.  Return true
 * if the image was successfully written; false otherwise. */

/**
 * Writes image data and properties to the data, URL, or data consumer associated with the image destination.
 *
 * - Parameters:
 *   - idst: An image destination.
 *
 * - Returns: `true` if the image destination successfully finalized the images, or `false` if an error occurred.
 *
 * Call this method as the final step in saving your images. The output of the image destination isn't valid until you call this method. After calling this function, you can't add any more data to the image destination.
 */
IMAGEIO_EXTERN bool CGImageDestinationFinalize(CGImageDestinationRef _iio_Nonnull idst)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);


/* Set the next image in the image destination `idst' to be `image' with
 * metadata properties specified in `metadata'. An error is logged if more
 * images are added than specified in the original count of the image
 * destination. */
IMAGEIO_EXTERN void CGImageDestinationAddImageAndMetadata(CGImageDestinationRef _iio_Nonnull idst, CGImageRef _iio_Nonnull image, CGImageMetadataRef _iio_Nullable metadata, CFDictionaryRef _iio_Nullable options)  IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/* For CGImageDestinationAddImageFromSource: when set to kCFBooleanTrue, a HEIF-embedded GainMap will be preserved.
 * If the destination image is scaled (using kCGImageDestinationImageMaxPixelSize), the GainMap will be scaled accordingly.
 * The value should be kCFBooleanTrue or kCFBooleanFalse
 * Defaults to kCFBooleanFalse
 */
/**
 * A Boolean value that indicates whether to include a HEIF-embedded gain map in the image data.
 *
 * The value of this key must be a <doc://com.apple.documentation/documentation/corefoundation/cfboolean> value. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>. If you scale the destination image using the ``kCGImageDestinationImageMaxPixelSize`` key, the destination also scales the gain map.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationPreserveGainMap IMAGEIO_AVAILABLE_STARTING(11.0, 14.1);

/**
 ** Keys which may be used in the 'options' dictionary of
 ** "CGImageDestinationCopyImageSource" to effect the output.
 **/

/* Set the metadata tags for the image destination. If present, the value of
 * this key is a CGImageMetadataRef. By default, all EXIF, IPTC, and XMP tags
 * will be replaced. Use kCGImageDestinationMergeMetadata to merge the tags
 * with the existing tags in the image source.
 */
/**
 * The metadata tags to include with the image.
 *
 * The value of this key is a ``CGImageMetadata`` type. When you specify this key, the image destination ovewrites all EXIF, IPTC, and XMP metadata. If you want to merge the new tags with the existing metadata, include the ``kCGImageDestinationMergeMetadata`` key in addition to this key.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationMetadata IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/* If true, The metadata will be copied from the source and merged with the tags
 * specified in kCGImageDestinationMetadata. If a tag does not exist in the 
 * source, it will be added. If the tag exists in the source, it will be 
 * updated. A metadata tag can be removed by setting the tag's value to 
 * kCFNull. If present, the value of this key is a CFBoooleanRef. The default
 * is kCFBooleanFalse.
 */ 
/**
 * A Boolean value that indicates whether to merge new metadata with the image's existing metadata.
 *
 * The value of this key must be a <doc://com.apple.documentation/documentation/corefoundation/cfboolean> value. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>.
 *
 * If you set this key to <doc://com.apple.documentation/documentation/corefoundation/kcfbooleantrue>, the image destination merges the information in the ``kCGImageDestinationMetadata`` key with the image's existing metadata. Specifically, if a tag doesn't exist in the source, the destination adds it. If the tag exists in the source, the destination updates its value. To remove a tag, set the value of the appropriate key to <doc://com.apple.documentation/documentation/corefoundation/kcfnull>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationMergeMetadata IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/* XMP data will not be written to the destination. If used in conjunction with 
 * kCGImageDestinationMetadata, EXIF tags will be preserved, but
 * an XMP packet will not be written to the file. IPTC tags, that are stored in XMP, will not be preserved.
 * If present, the value for this key is a CFBooleanRef. The default is kCFBooleanFalse.
 */
/**
 * A Boolean value that indicates whether to exclude XMP data from the destination.
 *
 * The value of this key must be a <doc://com.apple.documentation/documentation/corefoundation/cfboolean> value. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>, which causes the destination to include XMP metadata. If you use this flag in conjunction with the ``kCGImageDestinationMetadata`` flag, the image destination preserves EXIF and IPTC tags but doesn't write XMP packets to the file.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageMetadataShouldExcludeXMP IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/* If true, GPS metadata will not be written to EXIF data or the corresponding
 * EXIF tags in XMP. This flag cannot filter any proprietary location data that
 * could be stored in a manufacturer's EXIF MakerNote or custom XMP properties.
 * If present, the value for this key is a CFBooleanRef. The default is 
 * kCFBooleanFalse.
 */
/**
 * A Boolean value that indicates whether to exclude GPS metadata from EXIF data or the corresponding XMP tags.
 *
 * The value of this key must be a <doc://com.apple.documentation/documentation/corefoundation/cfboolean> value. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>, which includes GPS information in the metadata. This flag doesn't filter any proprietary location data in the manufacturer's EXIF MakerNote or in custom XMP properties.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageMetadataShouldExcludeGPS IMAGEIO_AVAILABLE_STARTING(10.10, 8.0);

/* Updates the DateTime parameters of the image metadata. Only values
 * present in the original image will updated. If present, the value should
 * be a CFStringRef or a CFDateRef. If CFString, the value must be in 
 * Exif DateTime or ISO 8601 DateTime format. This option is mutually
 * exclusive with kCGImageDestinationMetadata.
 */
/**
 * The date and time information to associate with the image.
 *
 * This property puts the specified date and time information into the DateTime parameters of the image's metadata. Specify the value of this key using a <doc://com.apple.documentation/documentation/corefoundation/cfstring> or <doc://com.apple.documentation/documentation/corefoundation/cfdata>. For strings, the value must be in EXIF DateTime or ISO 8601 DateTime format.
 *
 * This option is mutually exclusive with ``kCGImageDestinationMetadata``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationDateTime IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/* Updates the orientation in the image metadata. The image data itself will
 * not be rotated. If present, the value should be a CFNumberRef from 1 to 8. 
 * This option is mutually exclusive with kCGImageDestinationMetadata.
 */
/**
 * The orientation of the image, specified as an EXIF value in the range 1 to 8.
 *
 * The value of this key must be a <doc://com.apple.documentation/documentation/corefoundation/cfnumber>, and the number must be an integer in the range `1`–`8`. For more information about the meaning of each number, see the orientation field in the EXIF specification.
 *
 * This option is mutually exclusive with ``kCGImageDestinationMetadata``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationOrientation IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/*  For KTX files:
 *  The key 'kCGImagePropertyEncoder' can be used with CGImageDestinationAddImage...() to specify the encoder to be used.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyEncoder        IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyASTCEncoder    IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyPVREncoder     IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyBCEncoder      IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);

/* For BC / KTX(BC) / DDS files:
 * Specifies the specific pixel format to be encoded.
 * The value of this key must be an integer CFNumberRef, containing a OpenGL format enum.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyBCFormat          IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);

/* For ASTC / KTX(ASTC) files:
 * Specifies ASTC block size.
 * The value of this key must be either kCGImagePropertyASTCBlockSize4x4 or kCGImagePropertyASTCBlockSize8x8.
 */
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyASTCBlockSize          IMAGEIO_AVAILABLE_STARTING(10.12, 10.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyASTCBlockSize4x4       IMAGEIO_AVAILABLE_STARTING(16, 19.0, 19.0, 12.0);
IMAGEIO_EXTERN const CFStringRef kCGImagePropertyASTCBlockSize8x8       IMAGEIO_AVAILABLE_STARTING(16, 19.0, 19.0, 12.0);

/* Losslessly copies the contents of the image source, 'isrc', to the
 * destination, 'idst'. The image data will not be modified. The image's 
 * metadata can be modified by adding the keys and values defined above to 
 * 'options'. No other images should be added to the image destination. 
 * CGImageDestinationFinalize() should not be called afterward -
 * the result is saved to the destination when this function returns. 
 * The image type of the destination must match the image source. Returns true
 * if the operation was successful. If an error occurs, false will be returned 
 * and 'err' will be set to a CFErrorRef. Not all image formats are supported 
 * for this operation. */
IMAGEIO_EXTERN bool CGImageDestinationCopyImageSource(CGImageDestinationRef _iio_Nonnull idst, CGImageSourceRef _iio_Nonnull isrc, CFDictionaryRef _iio_Nullable options, _iio_Nullable CFErrorRef * _iio_Nullable err) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/* Auxiliary data support for JPEG, HEIF, and DNG images.
 * The auxiliaryDataInfoDictionary should contain:
 *   - the auxiliary data (CFDataRef) - (kCGImageAuxiliaryDataInfoData),
 *   - the auxiliary data description (CFDictionary) - (kCGImageAuxiliaryDataInfoDataDescription)
 *   - metadata (CGImageMetadataRef) - (kCGImageAuxiliaryDataInfoMetadata)
 * To add auxiliary data to an image, call CGImageDestinationAddAuxiliaryDataInfo() after adding the CGImage to the CGImageDestinationRef.
 */
/**
 * Sets the auxiliary data, such as mattes and depth information, that accompany the image.
 *
 * - Parameters:
 *   - idst: The image destination to modify.
 *   - auxiliaryImageDataType: The type of auxiliary information you want to add. For a list of possible values, see <doc:individual-image-properties#Auxiliary-Data-Types>.
 *   - auxiliaryDataInfoDictionary: A dictionary that contains the ``kCGImageAuxiliaryDataInfoData``, ``kCGImageAuxiliaryDataInfoDataDescription``, and ``kCGImageAuxiliaryDataInfoMetadata`` keys. Use those keys to describe the depth or matte information.
 *
 * Call this method after you add an image to the image destination. This method adds the specified depth or matte information to the most recently added image.
 */
IMAGEIO_EXTERN void CGImageDestinationAddAuxiliaryDataInfo(CGImageDestinationRef _iio_Nonnull idst, CFStringRef _iio_Nonnull auxiliaryImageDataType, CFDictionaryRef _iio_Nonnull auxiliaryDataInfoDictionary ) IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);


/* HDR-support */

IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeRequest         IMAGEIO_AVAILABLE_STARTING(15, 18.0, 18.0, 11.0);

IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeToSDR           IMAGEIO_AVAILABLE_STARTING(15, 18.0, 18.0, 11.0);
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeToISOHDR        IMAGEIO_AVAILABLE_STARTING(15, 18.0, 18.0, 11.0);
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeToISOGainmap    IMAGEIO_AVAILABLE_STARTING(15, 18.0, 18.0, 11.0);

/* kCGImageSourceEncodeRequestOptions - CFDictionaryRef to specify additional options
 */
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeRequestOptions                IMAGEIO_AVAILABLE_STARTING(15, 18.0, 18.0, 11.0);
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeBaseIsSDR                     IMAGEIO_AVAILABLE_STARTING(15, 18.0, 18.0, 11.0);
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeTonemapMode                   IMAGEIO_AVAILABLE_STARTING(15, 18.0, 18.0, 11.0);

IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeIsBaseImage                   IMAGEIO_AVAILABLE_STARTING(16, 19.0, 19.0, 12.0);
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeBaseColorSpace                IMAGEIO_AVAILABLE_STARTING(16, 19.0, 19.0, 12.0);
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeBasePixelFormatRequest        IMAGEIO_AVAILABLE_STARTING(16, 19.0, 19.0, 12.0);

IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeGenerateGainMapWithBaseImage  IMAGEIO_AVAILABLE_STARTING(16, 19.0, 19.0, 12.0);
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeGainMapPixelFormatRequest     IMAGEIO_AVAILABLE_STARTING(16, 19.0, 19.0, 12.0);
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeGainMapSubsampleFactor        IMAGEIO_AVAILABLE_STARTING(16, 19.0, 19.0, 12.0);
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEncodeAlternateColorSpace           IMAGEIO_AVAILABLE_STARTING(16, 19.0, 19.0, 12.0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGIMAGEDESTINATION_H_ */
