/*
 * ImageIO - CGImageSource.h
 * Copyright (c) 2004-2016 Apple Inc. All rights reserved.
 *
 */

#ifndef CGIMAGESOURCE_H_
#define CGIMAGESOURCE_H_

#include <ImageIO/ImageIOBase.h>

/**
 * An opaque type that you use to read image data from a URL, data object, or data consumer.
 *
 * Use a ``CGImageSource`` type to read data efficiently for most image file formats. The image source object manages the data buffers needed to load the image data and performs any operations on that data to turn it into a usable image. For example, it decompresses data stored in a compressed format. You can also use an image source to fetch or create thumbnail images and access metadata stored with the image.
 *
 * Create an image source object from a <doc://com.apple.documentation/documentation/corefoundation/cfurl>, <doc://com.apple.documentation/documentation/corefoundation/cfdata>, or <doc://com.apple.documentation/documentation/coregraphics/cgdataprovider> data type. The image source object reads data from the specified type and extracts the image information for you.
 *
 * For more information, see [Image I/O Programming Guide](https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/ImageIOGuide/imageio_intro/ikpg_intro.html#//apple_ref/doc/uid/TP40005462).
 */
typedef struct IIO_BRIDGED_TYPE(id) CGImageSource * CGImageSourceRef;

#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/CGImageMetadata.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/**
 * The set of status values for images and image sources.
 *
 * The ``CGImageSourceGetStatus(_:)`` and ``CGImageSourceGetStatusAtIndex(_:_:)`` functions return these values.
 */
typedef CF_ENUM(int32_t, CGImageSourceStatus) {
    /**
     * The end of the file occurred unexpectedly.
     */
    kCGImageStatusUnexpectedEOF = -5,
    /**
     * The data is not valid.
     */
    kCGImageStatusInvalidData = -4,
    /**
     * The image is an unknown type.
     */
    kCGImageStatusUnknownType = -3,
    /**
     * The image source is reading the header.
     */
    kCGImageStatusReadingHeader = -2,
    /**
     * The operation is not complete
     */
    kCGImageStatusIncomplete = -1,
    /**
     * The operation is complete.
     */
    kCGImageStatusComplete = 0
};

/** Keys for the options dictionary when creating a CGImageSourceRef. **/

/* Specifies the "best guess" of the type identifier for the format of the
 * image source file. If specified, the value of this key must be a
 * CFStringRef. For more information about type identifiers, see "UTType.h"
 * in the Application Services framework. */

/**
 * The uniform type identifier that represents your best guess for the image's type.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfstring> object. Add this key to the options dictionary when you create a ``CGImageSource`` object.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceTypeIdentifierHint  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/**
 * Option key for restricting which image formats can be decoded.
 *
 * The value is a <doc://com.apple.documentation/documentation/corefoundation/cfarray> containing <doc://com.apple.documentation/documentation/corefoundation/cfstring> Uniform Type Identifiers (UTIs)
 * of allowed image formats. When specified, ImageIO will only decode images
 * whose format matches one of the entries in the allow list. If no matching reader
 * is found, decoding fails.
 *
 * Unknown format identifiers are ignored.
 * If not specified, all supported ImageIO formats are allowed (default behavior).
 * If process-wide format restrictions were set via ``CGImageSourceSetAllowableTypes``,
 * only formats allowed by both mechanisms are permitted.
 *
 * See also <doc://com.apple.documentation/documentation/uniformtypeidentifiers/system-declared-uniform-type-identifiers>.
 *
 * ## Example
 * @TabNavigator {
 *   @Tab("Swift") {
 *     ```swift
 *     let allowedTypes = ["public.jpeg" as CFString, "public.png" as CFString]
 *     let options = [
 *         kCGImageSourceAllowableTypes: allowedTypes
 *     ] as CFDictionary
 *     ```
 *   }
 *   @Tab("Objective-C") {
 *     ```objc
 *     NSArray *allowedTypes = @[@"public.jpeg", @"public.png"];
 *     NSDictionary *options = @{
 *         (id)kCGImageSourceAllowableTypes: allowedTypes
 *     };
 *     ```
 *   }
 * }
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceAllowableTypes  IMAGEIO_AVAILABLE_STARTING(27.0, 27.0, 27.0, 27.0);

/** Keys for the options dictionary of "CGImageSourceCopyPropertiesAtIndex"
 ** and "CGImageSourceCreateImageAtIndex". **/

/* Specifies whether the image should be cached in a decoded form. The
 * value of this key must be a CFBooleanRef.
 * kCFBooleanFalse indicates no caching, kCFBooleanTrue indicates caching.
 * For 64-bit architectures, the default is kCFBooleanTrue, for 32-bit the default is kCFBooleanFalse.
 */

/**
 * A Boolean value that indicates whether to cache the decoded image.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfboolean>. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleantrue> for 64-bit architectures, and <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse> for 32-bit architectures.
 *
 * Include this key in the options dictionary you pass to the functions ``CGImageSourceCopyPropertiesAtIndex(_:_:_:)`` and ``CGImageSourceCreateImageAtIndex(_:_:_:)``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceShouldCache  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Specifies whether image decoding and caching should happen at image creation time.
 * The value of this key must be a CFBooleanRef. The default value is kCFBooleanFalse (image decoding will
 * happen at rendering time).
 */
/**
 * A Boolean value that indicates whether image decoding and caching happens at image creation time.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfboolean>. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>, which causes decoding and caching to happen only when you render the image.
 *
 * Include this key in the options dictionary you pass to the functions ``CGImageSourceCopyPropertiesAtIndex(_:_:_:)`` and ``CGImageSourceCreateImageAtIndex(_:_:_:)``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceShouldCacheImmediately  IMAGEIO_AVAILABLE_STARTING(10.9, 7.0);

/* Specifies whether the image should be returned as a floating
 * point CGImageRef if supported by the file format. Extended
 * range floating point CGImageRef may require additional
 * processing  to render pleasingly.  The value of this key must
 * be a CFBooleanRef; the default value is kCFBooleanFalse. */

/**
 * A Boolean that indicates whether to use floating-point values in returned images.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfboolean>. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>, which tells the image source not to use floating-point values.
 *
 * If the image format supports floating-point values, this key tells the image source to format <doc://com.apple.documentation/documentation/coregraphics/cgimage> types using those values. The use of extended-range floating-point values may require additional processing to render in a pleasing manner.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceShouldAllowFloat  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* A Boolean value that indicates whether to prioritize image quality over
 * decode speed. Currently, image sources support this option only for camera
 * RAW images. The value of this key must be a CFBooleanRef; the default value
 * is kCFBooleanFalse. */

/**
 * A Boolean value that indicates whether to prioritize image quality over decode speed.
 *
 * When you set this key to <doc://com.apple.documentation/documentation/corefoundation/kcfbooleantrue>, the image source decodes the full-size image using the highest-quality decode method available for the file. The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfboolean>. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>.
 *
 * Currently, image sources support this option only for camera RAW images. This key is a no-op when it is absent or <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>, when the image isn't a camera RAW format, or when no higher-quality decode method is available, so it is always safe to set.
 *
 * Include this key in the options dictionary you pass to the functions ``CGImageSourceCopyPropertiesAtIndex(_:_:_:)`` and ``CGImageSourceCreateImageAtIndex(_:_:_:)``.
 *
 * ## Example
 * @TabNavigator {
 *   @Tab("Swift") {
 *     ```swift
 *     let options = [
 *         kCGImageSourcePrioritizeQuality: true
 *     ] as CFDictionary
 *     let image = CGImageSourceCreateImageAtIndex(source, 0, options)
 *     ```
 *   }
 *   @Tab("Objective-C") {
 *     ```objc
 *     NSDictionary *options = @{
 *         (id)kCGImageSourcePrioritizeQuality: @YES
 *     };
 *     CGImageRef image = CGImageSourceCreateImageAtIndex(source, 0, (CFDictionaryRef)options);
 *     ```
 *   }
 * }
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourcePrioritizeQuality  IMAGEIO_AVAILABLE_STARTING(27.0, 27.0, 27.0, 27.0);

/** Keys for the options dictionary of
 ** "CGImageSourceCreateThumbnailAtIndex". **/

/* Specifies whether a thumbnail should be automatically created for an
 * image if a thumbnail isn't present in the image source file.  The
 * thumbnail will be created from the full image, subject to the limit
 * specified by kCGImageSourceThumbnailMaxPixelSize---if a maximum pixel
 * size isn't specified, then the thumbnail will be the size of the full
 * image, which probably isn't what you want. The value of this key must be
 * a CFBooleanRef; the default value of this key is kCFBooleanFalse. */

/**
 * A Boolean value that indicates whether to create a thumbnail image automatically if the data source doesn't contain one.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfboolean>. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>.
 *
 * If you set the value of this key to <doc://com.apple.documentation/documentation/corefoundation/kcfbooleantrue>, the image source creates the thumbnail from the full image, subject to the limit specified by ``kCGImageSourceThumbnailMaxPixelSize``. If you don't specify a maximum pixel size, the image soucre creates the thumbnail using the image's full size, which in most cases is not desirable.
 *
 * Include this key in the options dictionary you pass to the function ``CGImageSourceCreateThumbnailAtIndex(_:_:_:)``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceCreateThumbnailFromImageIfAbsent  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Specifies whether a thumbnail should be created from the full image even
 * if a thumbnail is present in the image source file. The thumbnail will
 * be created from the full image, subject to the limit specified by
 * kCGImageSourceThumbnailMaxPixelSize---if a maximum pixel size isn't
 * specified, then the thumbnail will be the size of the full image, which
 * probably isn't what you want. The value of this key must be a
 * CFBooleanRef; the default value of this key is kCFBooleanFalse. */

/**
 * A Boolean value that indicates whether to always create a thumbnail image.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfboolean>. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>.
 *
 * If you set the value of this key to <doc://com.apple.documentation/documentation/corefoundation/kcfbooleantrue>, the image source creates the thumbnail from the full image, subject to the limit specified by ``kCGImageSourceThumbnailMaxPixelSize``. If you don't specify a maximum pixel size, the image source creates the thumbnail using the image's full size, which in most cases is not desirable.
 *
 * Include this key in the options dictionary you pass to the function ``CGImageSourceCreateThumbnailAtIndex(_:_:_:)``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceCreateThumbnailFromImageAlways  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Specifies the maximum width and height in pixels of a thumbnail.  If
 * this this key is not specified, the width and height of a thumbnail is
 * not limited and thumbnails may be as big as the image itself.  If
 * present, this value of this key must be a CFNumberRef. */

/**
 * The maximum width and height of a thumbnail image, specified in pixels.
 *
 * If this key is not specified, the width and height of a thumbnail is not limited and thumbnails may be as big as the image itself. If present, this key must be a CFNumber value. This key can be provided in the options dictionary that you pass to the function ``CGImageSourceCreateThumbnailAtIndex(_:_:_:)``.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceThumbnailMaxPixelSize  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Specifies whether the thumbnail should be rotated and scaled according
 * to the orientation and pixel aspect ratio of the full image. The value
 * of this key must be a CFBooleanRef; the default value of this key is 
 * kCFBooleanFalse. */

/**
 * A Boolean value that indicates whether to rotate and scale the thumbnail image to match the image's orientation and aspect ratio.
 *
 * The value of this key must be a CFBoolean value. The default value is <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse>.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceCreateThumbnailWithTransform  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Specifies that, if possible, an image should be returned as scaled down (in height and width) by a specified factor.
 * The resulting image will be smaller and have reduced spatial quality but will otherwise have the same characteristics
 * as the full size normal image.
 * If the specified scaling factor is not supported, a larger or full size normal image will be returned.
 * Supported file formats are JPEG, HEIF, TIFF, and PNG.
 * The value of this key must be an integer CFNumberRef (allowed values: 2, 4, and 8).
 */

/**
 * The factor by which to scale down any returned images.
 *
 * When you specify this key, the image source scales down the image data by the specified numerical factor. The value of this key must be a <doc://com.apple.documentation/documentation/corefoundation/cfnumber> containing the integer value 2, 4, or 8. If the image doesn't support the specified scale factor, the image source provides a larger or full-size normal image.
 *
 * Image sources support this option only for JPEG, HEIF, TIFF, and PNG images.
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceSubsampleFactor  IMAGEIO_AVAILABLE_STARTING(10.11, 9.0);


/* Return the CFTypeID for CGImageSources. */

/**
 * Returns the unique type identifier of an image source opaque type.
 *
 * - Returns: Returns the Core Foundation type ID for an image source.
 *
 * A type identifier is an integer that identifies the opaque type to which a Core Foundation object belongs. You use type IDs in various contexts, such as when you are operating on heterogeneous collections. Note that a Core Foundation type ID is different from a uniform type identifier.
 */
IMAGEIO_EXTERN CFTypeID CGImageSourceGetTypeID (void)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Return an array of supported type identifiers. */

/**
 * Returns an array of uniform type identifiers that are supported for image sources.
 *
 * - Returns: Returns an array of the uniform type identifiers that are supported for image sources.
 *
 * For a list of system-declared and third-party identifiers, see <doc://com.apple.documentation/documentation/uniformtypeidentifiers>.
 */
IMAGEIO_EXTERN CFArrayRef _iio_Nonnull CGImageSourceCopyTypeIdentifiers(void)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Create an image source reading from the data provider `provider'. The
 * `options' dictionary may be used to request additional creation options;
 * see the list of keys above for more information. */

/**
 * Creates an image source that reads data from the specified data provider.
 *
 * - Parameters:
 *   - provider: The data provider to read from. For more information on data providers, see <doc://com.apple.documentation/documentation/coregraphics/cgdataprovider> and [Quartz 2D Programming Guide](https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Introduction/Introduction.html#//apple_ref/doc/uid/TP30001066).
 *   - options: A dictionary that specifies additional creation options. For a list of possible values, see <doc:CGImageSource#Specifying-the-Read-Options>.
 *
 * - Returns: An image source. You're responsible for releasing this type using <doc://com.apple.documentation/documentation/corefoundation/cfrelease>.
 */
IMAGEIO_EXTERN CGImageSourceRef _iio_Nullable CGImageSourceCreateWithDataProvider(CGDataProviderRef _iio_Nonnull provider, CFDictionaryRef _iio_Nullable options) IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Create an image source reading from `data'.  The `options' dictionary
 * may be used to request additional creation options; see the list of keys
 * above for more information. */

/**
 * Creates an image source that reads from a Core Foundation data object.
 *
 * - Parameters:
 *
 *   - data: The data object from which to read. For more information on data objects, see <doc://com.apple.documentation/documentation/corefoundation/cfdata> and [Data Objects](https://developer.apple.com/library/archive/documentation/CoreFoundation/Conceptual/CFBinaryData/DataObjects.html#//apple_ref/doc/uid/20000171).
 *
 *
 *   - options: A dictionary that specifies additional creation options. For a list of possible values, see <doc:CGImageSource#Specifying-the-Read-Options>.
 *
 * - Returns: An image source. You're responsible for releasing this type using <doc://com.apple.documentation/documentation/corefoundation/cfrelease>.
 */
IMAGEIO_EXTERN CGImageSourceRef _iio_Nullable CGImageSourceCreateWithData(CFDataRef _iio_Nonnull data, CFDictionaryRef _iio_Nullable options) IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Create an image source reading from `url'. The `options' dictionary may
 * be used to request additional creation options; see the list of keys
 * above for more information. */

/**
 * Creates an image source that reads from a location specified by a URL.
 *
 * - Parameters:
 *   - url: The URL of the image.
 *   - options: A dictionary that specifies additional creation options. For a list of possible values, see <doc:CGImageSource#Specifying-the-Read-Options>.
 *
 * - Returns: An image source. You're responsible for releasing this type using <doc://com.apple.documentation/documentation/corefoundation/cfrelease>.
 */
IMAGEIO_EXTERN CGImageSourceRef _iio_Nullable CGImageSourceCreateWithURL(CFURLRef _iio_Nonnull url, CFDictionaryRef _iio_Nullable options) IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Return the type identifier of the image source `isrc'.  This type is the
 * type of the source "container", which is not necessarily the type of the
 * image(s) in the container.  For example, the .icns format supports
 * embedded JPEG2000 but the source type will be "com.apple.icns". */

/**
 * Returns the uniform type identifier of the source container.
 *
 * - Parameters:
 *   - isrc: The image source that contains the image data.
 *
 * - Returns: The uniform type identifier of the image source container.
 *
 * The uniform type identifier of the source container can be different from the type of the images in the container. For example, the `.icns` format supports embedded `JPEG2000`. The type of the source container is `"com.apple.icns"`, but type of the images is `JPEG2000`.
 *
 * For a list of system-declared and third-party identifiers, see <doc://com.apple.documentation/documentation/uniformtypeidentifiers>.
 */
IMAGEIO_EXTERN CFStringRef _iio_Nullable CGImageSourceGetType(CGImageSourceRef _iio_Nonnull isrc)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Return the number of images (not including thumbnails) in the image
 * source `isrc'. */

/**
 * Returns the number of images (not including thumbnails) in the image source.
 *
 * - Parameters:
 *   - isrc: The image source that contains the image data.
 *
 * - Returns: The number of images. If the image source is a multilayered Photoshop (PSD) file, the function returns `1`.
 *
 * This function does not extract the layers of a PSD file.
 */
IMAGEIO_EXTERN size_t CGImageSourceGetCount(CGImageSourceRef _iio_Nonnull isrc)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Return the properties of the image source `isrc'.  These properties
 * apply to the container in general but not necessarily to any individual
 * image that it contains. */

/**
 * Returns the properties of the image source.
 *
 * - Parameters:
 *   - isrc: The image source that contains the image data.
 *   - options: A dictionary you can use to request additional options. For a list of possible values, see <doc:CGImageSource#Specifying-the-Read-Options>.
 *
 * - Returns: A dictionary that contains the properties associated with the image source container. See `CGImageProperties` for a list of properties that can be in the dictionary.
 *
 * These properties apply to the container in general but not necessarily to any individual image contained in the image source.
 */
IMAGEIO_EXTERN CFDictionaryRef _iio_Nullable CGImageSourceCopyProperties(CGImageSourceRef _iio_Nonnull isrc, CFDictionaryRef _iio_Nullable options)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Return the properties of the image at `index' in the image source
 * `isrc'.  The index is zero-based. The `options' dictionary may be used
 * to request additional options; see the list of keys above for more
 * information. */

/**
 * Returns the properties of the image at a specified location in an image source.
 *
 * - Parameters:
 *   - isrc: The image source that contains the image data.
 *   - index: The zero-based index into the images of the image source. If the index is invalid, this method returns `NULL`.
 *   - options: A dictionary you can use to request additional options. For a list of possible values, see <doc:CGImageSource#Specifying-the-Read-Options>.
 *
 * - Returns: A dictionary that contains the properties associated with the image. See `CGImageProperties` for a list of properties that allowed in the dictionary.
 */
IMAGEIO_EXTERN CFDictionaryRef _iio_Nullable CGImageSourceCopyPropertiesAtIndex(CGImageSourceRef _iio_Nonnull isrc, size_t index, CFDictionaryRef _iio_Nullable options)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Return the metadata of the image at `index' in the image source
 * `isrc'. The index is zero-based. The `options' dictionary may be used
 * to request additional options; see the list of keys above for more
 * information. Please refer to CGImageMetadata.h for usage of metadata. */
IMAGEIO_EXTERN CGImageMetadataRef _iio_Nullable CGImageSourceCopyMetadataAtIndex (CGImageSourceRef _iio_Nonnull isrc, size_t index, CFDictionaryRef _iio_Nullable options) IMAGEIO_AVAILABLE_STARTING(10.8,7.0);

/* Return the image at `index' in the image source `isrc'.  The index is
 * zero-based. The `options' dictionary may be used to request additional
 * creation options; see the list of keys above for more information. */

/**
 * Creates an image object from the data at the specified index in an image source.
 *
 * - Parameters:
 *   - isrc: The image source that contains the image data.
 *   - index: The zero-based index of the image you want. If the index is invalid, this method returns `NULL`.
 *   - options: A dictionary that specifies additional creation options. For a list of possible values, see <doc:CGImageSource#Specifying-the-Read-Options>.
 *
 * - Returns: The image at the specified index, or `NULL` if an error occurs. You're responsible for releasing the returned object using <doc://com.apple.documentation/documentation/coregraphics/cgimagerelease>.
 */
IMAGEIO_EXTERN CGImageRef _iio_Nullable CGImageSourceCreateImageAtIndex(CGImageSourceRef _iio_Nonnull isrc, size_t index, CFDictionaryRef _iio_Nullable options)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Remove the cached decoded image data for the image at `index' in the image source `isrc'.
 * The index is zero-based.
 */
IMAGEIO_EXTERN void CGImageSourceRemoveCacheAtIndex(CGImageSourceRef _iio_Nonnull isrc, size_t index) IMAGEIO_AVAILABLE_STARTING(10.9, 7.0);

/* Return the thumbnail of the image at `index' in the image source `isrc'.
 * The index is zero-based. The `options' dictionary may be used to request
 * additional thumbnail creation options; see the list of keys above for
 * more information. */

/**
 * Creates a thumbnail version of the image at the specified index in an image source.
 *
 * - Parameters:
 *   - isrc: The image source that contains the image data.
 *   - index: The zero-based index of the image you want. If the index is invalid, this method returns `NULL`.
 *   - options: A dictionary that specifies additional creation options. For a list of possible values, see <doc:CGImageSource#Specifying-the-Read-Options>.
 *
 * - Returns: The image at the specified index, or `NULL` if an error occurs. You are responsible for releasing the returned object using <doc://com.apple.documentation/documentation/coregraphics/cgimagerelease>.
 *
 * If the image source is a PDF, this function creates a 72 dpi image of the PDF page specified by the index that you pass. You must, however, pass an options dictionary that contains either the ``kCGImageSourceCreateThumbnailFromImageIfAbsent`` or ``kCGImageSourceCreateThumbnailFromImageAlways`` keys, with the value of the key set to `true`.
 */
IMAGEIO_EXTERN CGImageRef _iio_Nullable CGImageSourceCreateThumbnailAtIndex(CGImageSourceRef _iio_Nonnull isrc, size_t index, CFDictionaryRef _iio_Nullable options)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Create an incremental image source. No data is provided at creation
 * time; it is assumed that data will eventually be provided using
 * "CGImageSourceUpdateDataProvider" or "CGImageSourceUpdateData".  The
 * `options' dictionary may be used to request additional creation options;
 * see the list of keys above for more information. */

/**
 * Creates an empty image source that you can use to accumulate incremental image data.
 *
 * - Parameters:
 *   - options: A dictionary that specifies additional creation options. For a list of possible values, see <doc:CGImageSource#Specifying-the-Read-Options>.
 *
 * - Returns: An empty image source object. You're responsible for releasing this type using <doc://com.apple.documentation/documentation/corefoundation/cfrelease>.
 *
 * This function creates an empty image source container, which you use to accumulate data downloaded in chunks from the network. To add new chunks of data to the image source, call the ``CGImageSourceUpdateDataProvider(_:_:_:)`` or ``CGImageSourceUpdateData(_:_:_:)`` functions.
 */
IMAGEIO_EXTERN CGImageSourceRef _iio_Nonnull CGImageSourceCreateIncremental(CFDictionaryRef _iio_Nullable options)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Update the incremental image source `isrc' with new data.  The new data
 * must include all the previous data plus any additional new data. The
 * `final' parameter should be true when the final set of data is provided;
 * false otherwise. */

/**
 * Updates the data in an incremental image source.
 *
 * - Parameters:
 *   - isrc: The image source to modify.
 *   - data: The updated data for the image source. Each time you call this function, specify all of the accumulated image data so far.
 *   - final: A Boolean value that indicates whether the `data` parameter represents the complete data set. Specify `true` if the data is complete or `false` if it isn't.
 *
 * This method updates the state of the image source and its contained images. Call this method one or more times to update the contents of an incremental data source. Each time you call the method, you must specify all of the accumulated image data, not just the new data you received.
 */
IMAGEIO_EXTERN void CGImageSourceUpdateData(CGImageSourceRef _iio_Nonnull isrc, CFDataRef _iio_Nonnull data, bool final)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Update the incremental image source `isrc' with a new data provider.
 * The new data provider must provide all the previous data plus any
 * additional new data. The `final' parameter should be true when the final
 * set of data is provided; false otherwise. */

/**
 * Updates an incremental image source with a new data provider.
 *
 * - Parameters:
 *   - isrc: The image source to modify.
 *   - provider: The new data provider. The new data provider must provide all the previous data supplied to the image source and any additional new data.
 *   - final: A Boolean value that indicates whether the `provider` parameter provides the complete data set. Specify `true` if the data is complete or `false` if it isn't.
 */
IMAGEIO_EXTERN void CGImageSourceUpdateDataProvider(CGImageSourceRef _iio_Nonnull isrc, CGDataProviderRef _iio_Nonnull provider, bool final)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Return the overall status of the image source `isrc'.  The status is
 * particularly informative for incremental image sources, but may be used
 * by clients providing non-incremental data as well. */

/**
 * Return the status of an image source.
 *
 * - Parameters:
 *   - isrc: The image source that contains the image data.
 *
 * - Returns: Returns the current status of the image source. See ``CGImageSourceStatus`` for a list of possible values.
 *
 * Status information is particularly informative for incremental image sources, but it may also be useful on image sources that contain non-incremental data.
 */
IMAGEIO_EXTERN CGImageSourceStatus CGImageSourceGetStatus(CGImageSourceRef _iio_Nonnull isrc)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Return the current status of the image at `index' in the image source
 * `isrc'. The index is zero-based. The returned status is particularly
 * informative for incremental image sources but may used by clients
 * providing non-incremental data as well. */

/**
 * Returns the current status of an image at the specified location in the image source.
 *
 * - Parameters:
 *   - isrc: The image source that contains the image data.
 *   - index: The zero-based index into the images of the image source. If the index is invalid, this method returns `NULL`.
 *
 * - Returns: Returns the current status of the image. See ``CGImageSourceStatus`` for a list of possible values.
 *
 * Status information is particularly informative for incremental image sources, but you may also use it on image sources that contain non-incremental data.
 */
IMAGEIO_EXTERN CGImageSourceStatus CGImageSourceGetStatusAtIndex(CGImageSourceRef _iio_Nonnull isrc, size_t index)  IMAGEIO_AVAILABLE_STARTING(10.4, 4.0);

/* Return the primary image index for HEIF images.
 * Zero for all other formats.
 */
/**
 * Returns the index of the primary image for an High Efficiency Image File Format (HEIF) image.
 *
 * - Parameters:
 *   - isrc: The image source that contains the image data.
 *
 * - Returns: The index of the primary image, or `0` for image formats other than the HEIF format.
 */
IMAGEIO_EXTERN size_t CGImageSourceGetPrimaryImageIndex(CGImageSourceRef _iio_Nonnull isrc)  IMAGEIO_AVAILABLE_STARTING(10.14, 12.0);

/* Auxiliary data support for JPEG, HEIF, and DNG images (kCGImageAuxiliaryDataTypeDepth, ...)
 * The returned CFDictionary contains:
 *   - the depth data (CFDataRef) - (kCGImageAuxiliaryDataInfoData),
 *   - the depth data description (CFDictionary) - (kCGImageAuxiliaryDataInfoDataDescription)
 *   - metadata (CGImageMetadataRef) - (kCGImageAuxiliaryDataInfoMetadata)
 *   - optional color space (CGColorSpaceRef) - (kCGImageAuxiliaryDataInfoColorSpace)
 * CGImageSourceCopyAuxiliaryDataInfoAtIndex returns nil if the image did not contain ‘auxiliaryImageDataType’ data.
 */
/**
 * Returns auxiliary data, such as mattes and depth information, that accompany the image.
 *
 * - Parameters:
 *   - isrc: The image source that contains the image data.
 *   - index: The zero-based index into the images of the image source. If the index is invalid, this method returns `NULL`.
 *   - auxiliaryImageDataType: The auxiliary data to retrieve. For a list of possible values, see <doc:individual-image-properties#Auxiliary-Image-Data> and <doc:individual-image-properties#Auxiliary-Data-Types>.
 *
 * - Returns: A dictionary that contains the auxiliary data, or `NULL` if an error occurs.
 */
IMAGEIO_EXTERN CFDictionaryRef _iio_Nullable CGImageSourceCopyAuxiliaryDataInfoAtIndex(CGImageSourceRef _iio_Nonnull isrc, size_t index, CFStringRef _iio_Nonnull auxiliaryImageDataType ) IMAGEIO_AVAILABLE_STARTING(10.13, 11.0);


/* HDR-related */

/* kCGImageSourceDecodeRequest - value is one of the predefined keys (kCGImageSourceDecodeToHDR, kCGImageSourceDecodeToSDR, ...)
 */
/**
 * ## Overview
 *
 * For more information, see [Image I/O Programming Guide](https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/ImageIOGuide/imageio_intro/ikpg_intro.html#//apple_ref/doc/uid/TP40005462).
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceDecodeRequest    IMAGEIO_AVAILABLE_STARTING(14.0, 17.0, 17.0, 10.0);

IMAGEIO_EXTERN const CFStringRef kCGImageSourceDecodeToHDR      IMAGEIO_AVAILABLE_STARTING(14.0, 17.0, 17.0, 10.0);
IMAGEIO_EXTERN const CFStringRef kCGImageSourceDecodeToSDR      IMAGEIO_AVAILABLE_STARTING(14.0, 17.0, 17.0, 10.0);

/* kCGImageSourceGenerateImageSpecificLumaScaling - generate a global tone mapping function based on the gain map. Dafault value is "YES" (kCFBooleanTrue)
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceGenerateImageSpecificLumaScaling      IMAGEIO_AVAILABLE_STARTING(15.0, 18.0, 18.0, 11.0);

/* kCGImageSourceDecodeRequestOptions - CFDictionaryRef to specify additional options
 */
IMAGEIO_EXTERN const CFStringRef kCGImageSourceDecodeRequestOptions     IMAGEIO_AVAILABLE_STARTING(14.0, 17.0, 17.0, 10.0);

// HDR statistics
IMAGEIO_EXTERN const CFStringRef kCGComputeHDRStats                     IMAGEIO_AVAILABLE_STARTING(16.0, 19.0, 19.0, 12.0);

/* To limit the image formats that ImageIO can decode, you can call 'CGImageSourceSetAllowableTypes' with
 * an array of type identifiers.
 * The 'allowableTypes' array should contain valid type identifiers.
 * CGImageSourceSetAllowableTypes can only be called once.
 */

/**
 * Restricts which image formats can be decoded in the current process.
 *
 * When this method has been called, ImageIO will only decode images whose format matches one of the entries in the allow list for the remaining lifetime of the process.
 *
 * If per-asset format restrictions are set via ``kCGImageSourceAllowableTypes``,
 * only formats allowed by both mechanisms are permitted.
 * If `allowableTypes` is empty, all image parsing is disabled.
 * Unknown format identifiers are ignored.
 * Can only be called once per process; subsequent calls are ignored.
 *
 * See also <doc://com.apple.documentation/documentation/uniformtypeidentifiers/system-declared-uniform-type-identifiers>.
 *
 * - Parameters:
 *   - allowableTypes: A <doc://com.apple.documentation/documentation/corefoundation/cfarray> containing <doc://com.apple.documentation/documentation/corefoundation/cfstring> Uniform Type Identifiers (UTIs) of allowed image formats.
 */
IMAGEIO_EXTERN OSStatus CGImageSourceSetAllowableTypes(CFArrayRef allowableTypes) IMAGEIO_AVAILABLE_STARTING(14.2, 17.2, 17.2, 10.2);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED


#endif  /* CGIMAGESOURCE_H_ */
