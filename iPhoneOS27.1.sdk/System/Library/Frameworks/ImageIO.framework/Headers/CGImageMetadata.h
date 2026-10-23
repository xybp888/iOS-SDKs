/*
 * ImageIO - CGImageMetadata.h
 * Copyright (c) 2004-2016 Apple Inc. All rights reserved.
 *
 */

#ifndef CGIMAGEMETADATA_H_
#define CGIMAGEMETADATA_H_

#include <ImageIO/ImageIOBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/*!
 * @header CGImageMetadata.h
 * @abstract Implements access to image metadata
 * @description CGImageMetadata APIs allow clients to view and modify metadata
 * for popular image formats. ImageIO supports the EXIF, IPTC, and XMP
 * metadata specifications. Please refer to CGImageSource.h for functions to 
 * read metadata from a CGImageSource, and CGImageDestination.h for functions to
 * write metadata to a CGImageDestination. CGImageDestinationCopyImageSource can
 * be used to modify metadata without recompressing the image.
 *
 * Developers can enable additional debugging information by setting the
 * environment variable IIO_DEBUG_METADATA=1.
 * @related CGImageSource.h
 * @related CGImageDestination.h
 * @ignorefuncmacro IMAGEIO_AVAILABLE_STARTING
 * @ignore IMAGEIO_EXTERN
 * @unsorted
 */

/**
 * An immutable object that contains the XMP metadata associated with an image.
 *
 * A ``CGImageMetadata`` object stores the metadata associated with an image. Create this object from your image's associated XMP data, and use it to fetch individual metadata tags. You can search for specific tags, or enumerate all of the tags present for the image.
 */
typedef const struct IIO_BRIDGED_TYPE(id) CGImageMetadata *CGImageMetadataRef;

///*! @functiongroup Creating and identifying CGImageMetadata containers */

/**
 * Returns the type identifier for metadata objects.
 *
 * - Returns: The type identifier for ``CGImageMetadata`` and ``CGMutableImageMetadata`` objects.
 */
IMAGEIO_EXTERN CFTypeID CGImageMetadataGetTypeID(void);

/**
 * An opaque type for adding or modifying image metadata.
 *
 * Create a ``CGMutableImageMetadata`` opaque type when you want to modify the metadata in an image. You may pass this type  to any functions that take a ``CGImageMetadata`` type as a parameter. This object stores the tag information as XMP data, which  you can write back to the image.
 *
 * When you access or modify EXIF or IPTC properties, the metadata functions automatically bridge those properties to appropriate XMP  properties. This bridging behavior fills in any fields that are present only in the XMP data. For example, it fills in the namespace, prefix,  and XMP type information in the corresponding ``CGImageMetadataTag`` object.
 */
typedef struct IIO_BRIDGED_TYPE(id) CGImageMetadata *CGMutableImageMetadataRef;

/**
 * Creates an empty, mutable image metdata opaque type.
 *
 * - Returns: A ``CGMutableImageMetadata`` object that contains no metadata information, or `NULL` if an error occurs. You are responsible for releasing the returned object.
 */
IMAGEIO_EXTERN CGMutableImageMetadataRef _iio_Nonnull CGImageMetadataCreateMutable(void) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Creates a deep, mutable copy of the specified metadata information.
 *
 * - Parameters:
 *   - metadata: The metadata information to copy. This function makes a deep copy of all ``CGImageMetadataTag`` structures in this parameter, including the values for the tags.
 *
 * - Returns: A new ``CGMutableImageMetadata`` type that contains a deep copy of the tags in the metadata parameter.
 *
 * Typically, you call this function before modifying the metadata information for an image. Use it to create a copy of the image's existing metadata information, and then add or modify that metadata before saving it with the image.
 */
IMAGEIO_EXTERN CGMutableImageMetadataRef _iio_Nullable CGImageMetadataCreateMutableCopy(CGImageMetadataRef _iio_Nonnull metadata) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

// ****************************************************************************
// CGImageMetadataTag - an individual metadata tag, encapsulating an EXIF tag, 
// IPTC tag, or XMP property.
// ****************************************************************************

/**
 * An immutable type that contains information about a single piece of image metadata.
 *
 * Each ``CGImageMetadataTag`` opaque type contains a single EXIF, IPTC, or XMP property. The namespace, prefix, name, type, and value of the tag identify different portions of the tag's content. For example, the namespace specifies whether the tag is part of the EXIF metadata or a different set of metadata.
 *
 * You retrieve existing metadata tags from an ``CGImageMetadata`` opaque type. You may also create new tags and add them to a ``CGMutableImageMetadata`` type, before you assign the updated metadata to an image.
 */
typedef struct IIO_BRIDGED_TYPE(id) CGImageMetadataTag *CGImageMetadataTagRef;

///*! @functiongroup Creating and identifying CGImageMetadataTags */

/**
 * Returns the type identifier for the image metadata tag opaque type
 *
 * - Returns: The type identifier for the ``CGImageMetadataTag`` opaque type.
 */
IMAGEIO_EXTERN CFTypeID CGImageMetadataTagGetTypeID(void) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);


// ****************************************************************************
// Constants for use in a CGImageMetadataTag
// ****************************************************************************

// All metadata tags must contain a namespace. Clients may use one of the
// public namespaces defined below or create their own namespace. If a caller
// defines their own namespace, it should comply with the guidelines set forth
// by Adobe in their XMP specification at:
// http://www.adobe.com/devnet/xmp.html.
// For example: "http://ns.adobe.com/exif/1.0/". 
// The caller must also register a custom namespace using 
// CGImageMetadataRegisterNamespaceForPrefix.

// Public, common namespaces.
/**
 * The namespace for the Exchangeable Image File (EXIF) format.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceExif IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The namespace for EXIF auxiliary keys.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceExifAux IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The namespace for the exifEX format.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceExifEX IMAGEIO_AVAILABLE_STARTING(10.9, 7.0);
/**
 * The namespace for the Dublin Core Metadata Element Set.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceDublinCore IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The namespace for the IPTC format.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceIPTCCore IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceIPTCExtension IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
/**
 * The namespace for Photoshop image metadata.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespacePhotoshop IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The namespace for TIFF image metadata.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceTIFF IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The namespace for the Extensible Metadata Platform (XMP) format.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceXMPBasic IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The namespace for XMP metadata that conveys legal restrictions associated with a resource.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceXMPRights IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

// All metadata tags must contain a prefix. For the public namespaces defined
// above, no prefix is required - ImageIO will use appropriate defaults.  For 
// other namespaces a prefix is required. For example, while the exif namespace 
// is rather long ("http://ns.adobe.com/exif/1.0/"), when exported the shorter 
// string "exif" will be used to prefix all properties in the exif namespace 
// (example - "exif:Flash").

// Public, common prefixes.
/**
 * The prefix string for tags in the Exchangeable Image File (EXIF) metadata.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixExif IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The prefix string for tags in the EXIF auxiliary metadata collection.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixExifAux IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The prefix string for tags in the exifEX metadata.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixExifEX IMAGEIO_AVAILABLE_STARTING(10.9, 7.0);
/**
 * The prefix string for tags in the Dublin Core Metadata Element Set.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixDublinCore IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The prefix string for tags in the IPTC metadata.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixIPTCCore IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixIPTCExtension IMAGEIO_AVAILABLE_STARTING(10.13.4, 11.3);
/**
 * The prefix string for tags in the Photoshop image metadata.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixPhotoshop IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The prefix string for tags in the TIFF image metadata.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixTIFF IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The prefix string for tags in the XMP metadata.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixXMPBasic IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
/**
 * The prefix string for tags in the XMP metadata that convey legal restrictions for the resource.
 */
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixXMPRights IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

// Metadata value type constants.
/**
 * Constants that indicate the XMP type for a metadata tag.
 *
 * Use these constants to identify the type of metadata in a ``CGImageMetadataTag`` opaque type. The type tells you how to interpret the value of the metadata tag. When creating a new ``CGImageMetadataTag``, specify a type so the system knows how to serialize the data to the XMP format.
 */
typedef CF_ENUM(int32_t, CGImageMetadataType) {
    /**
     * An invalid metadata type.
     */
    kCGImageMetadataTypeInvalid = -1,
    /**
     * The default type for new tags.
     *
     * When you create new tags, the system assigns this value initially. The system uses the Core Foundation type of the metadata tag's value to determine an appropriate type. During the serialization process, the system converts the type automatically to a nondefault value.
     */
    kCGImageMetadataTypeDefault = 0,
    /**
     * A string value.
     *
     * The string type also represents number and Boolean values.
     */
    kCGImageMetadataTypeString = 1,
    /**
     * An array that doesn't preserve the order of items.
     *
     * During serialization, this type becomes `<rdf:Bag>` in the XMP format.
     */
    kCGImageMetadataTypeArrayUnordered = 2,
    /**
     * An array that preserves the order of items.
     *
     * During serialization, this type becomes `<rdf:Seq>` in the XMP format.
     */
    kCGImageMetadataTypeArrayOrdered = 3,
    /**
     * An ordered array, in which all elements are alternates for the same value.
     *
     * During serialization, this type becomes `<rdf:Alt>` in the XMP format.
     */
    kCGImageMetadataTypeAlternateArray = 4,
    /**
     * An alternate array, in which all elements are localized strings for the same value.
     *
     * During serialization, this type becomes an alternate array of strings with `xml:lang` qualifiers in the XMP format.
     */
    kCGImageMetadataTypeAlternateText = 5,
    /**
     * A collection of keys and values.
     *
     * Unlike array elements, fields of a structure may belong to different namespaces.
     */
    kCGImageMetadataTypeStructure = 6
};

// ****************************************************************************
// Creating a CGImageMetadataTag
// ****************************************************************************
/**
 * Creates a new image metadata tag, and fills it with the specified information.
 *
 * - Parameters:
 *   - xmlns: The namespace for the tag. Specify a common XMP namespace, such as ``kCGImageMetadataNamespaceExif``, or a string with a custom namespace URI. A custom namespace must be a valid XML namespace. By convention, namespaces end with either the `/` or `#` character.
 *   - prefix: An abbreviation for the XML namespace. You must specify a valid string for custom namespace. For standard namespaces such as ``kCGImageMetadataNamespaceExif``, you may specify `NULL`.
 *   - name: The name of the metadata tag. This string must correspond to a valid XMP name.
 *   - type: The type of data in the `value` parameter. For a list of possible values, see ``CGImageMetadataType``.
 *   - value: The value of the tag. The value's type must match the information in the `type` parameter. Supported types for this parameter are <doc://com.apple.documentation/documentation/corefoundation/cfstring>, <doc://com.apple.documentation/documentation/corefoundation/cfnumber>, <doc://com.apple.documentation/documentation/corefoundation/cfboolean>, <doc://com.apple.documentation/documentation/corefoundation/cfarray>, and <doc://com.apple.documentation/documentation/corefoundation/cfdictionary>. The keys of a dictionary must be <doc://com.apple.documentation/documentation/corefoundation/cfstring> types with XMP names. The values of a dictionary must be either <doc://com.apple.documentation/documentation/corefoundation/cfstring> or ``CGImageMetadataTag`` types.
 *
 *     The newly created tag stores only a shallow copy of the original value. As a result, modifying the original value doesn't affect the value in the new ``CGImageMetadataTag``.
 *
 * - Returns: A new ``CGImageMetadataTag`` type, or `NULL` if an error occurred.
 */
IMAGEIO_EXTERN CGImageMetadataTagRef _iio_Nullable CGImageMetadataTagCreate (CFStringRef _iio_Nonnull xmlns, CFStringRef _iio_Nullable prefix, CFStringRef _iio_Nonnull name, CGImageMetadataType type, CFTypeRef _iio_Nonnull value) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

// ****************************************************************************
// Getting attributes of a CGImageMetadataTag
// ****************************************************************************
///*! @functiongroup Getting attributes of a CGImageMetadataTag */

/**
 * Returns an immutable copy of the tag's XMP namespace.
 *
 * - Parameters:
 *   - tag: The metadata tag from which to fetch the namespace information.
 *
 * - Returns: An immutable string that contains the tag's namespace. For a list of public namespaces, see <doc:xmp-namespaces-and-prefixes>. You are responsible for releasing this string.
 *
 * By convention, namespaces end with either a `/` or `#` character. For example, EXIF metadata uses the namespace `http://ns.adobe.com/exif/1.0/`. Custom namespaces must be a valid XML namespace.
 */
IMAGEIO_EXTERN CFStringRef _iio_Nullable CGImageMetadataTagCopyNamespace(CGImageMetadataTagRef _iio_Nonnull tag) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Returns an immutable copy of the tag's prefix.
 *
 * - Parameters:
 *   - tag: The metadata tag from which to fetch the namespace information.
 *
 * - Returns: An immutable string that contains the tag's prefix. For example, EXIF metadata uses the prefix `exif`. You are responsible for releasing this string.
 */
IMAGEIO_EXTERN CFStringRef _iio_Nullable CGImageMetadataTagCopyPrefix(CGImageMetadataTagRef _iio_Nonnull tag) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Returns an immutable copy of the tag's name.
 *
 * - Parameters:
 *   - tag: The metadata tag from which to fetch the namespace information.
 *
 * - Returns: A string that contains the tag's name. You are responsible for releasing this string.
 */
IMAGEIO_EXTERN CFStringRef _iio_Nullable CGImageMetadataTagCopyName(CGImageMetadataTagRef _iio_Nonnull tag) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Returns a shallow copy of the tag's value, which is suitable only for reading.
 *
 * - Parameters:
 *   - tag: The metadata tag from which to fetch the namespace information.
 *
 * - Returns: A copy of the tag's value. Possible return types are <doc://com.apple.documentation/documentation/corefoundation/cfstring>, <doc://com.apple.documentation/documentation/corefoundation/cfnumber>, <doc://com.apple.documentation/documentation/corefoundation/cfboolean>, <doc://com.apple.documentation/documentation/corefoundation/cfarray>, and <doc://com.apple.documentation/documentation/corefoundation/cfdictionary>.
 *
 * Use this method to obtain the value when you want to use or display that value elsewhere. Any changes you make to the returned value don't change the contents of the metadata tag. To change the value, call ``CGImageMetadataSetValueWithPath(_:_:_:_:)`` or ``CGImageMetadataSetTagWithPath(_:_:_:_:)`` instead.
 */
IMAGEIO_EXTERN CFTypeRef _iio_Nullable CGImageMetadataTagCopyValue(CGImageMetadataTagRef _iio_Nonnull tag) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Returns the type of the metadata tag's value.
 *
 * - Parameters:
 *   - tag: The metadata tag from which to fetch the namespace information.
 *
 * - Returns: A constant that indicates the type of the value. For a list of possible return values, see ``CGImageMetadataType``.
 *
 * To get the value itself, call ``CGImageMetadataTagCopyValue(_:)``. Metadata tags store string, number, and Boolean values using the ``CGImageMetadataType/string`` type.
 */
IMAGEIO_EXTERN CGImageMetadataType CGImageMetadataTagGetType(CGImageMetadataTagRef _iio_Nonnull tag) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Returns a shallow copy of the metadata tags that act as qualifiers for the current tag.
 *
 * - Parameters:
 *   - tag: The metadata tag from which to fetch the namespace information.
 *
 * - Returns: An array of ``CGImageMetadataTag`` types that represent the current tag's qualifiers, or `NULL` if the tag has no qualifiers.
 *
 * XMP allows a metadata tag to contain supplemental tags that act as qualifiers on the content. For example, the `xml:lang` qualifier provides alternate text entries for the current tag. Each qualifier is a ``CGImageMetadataTag`` with its own namespace, prefix, name, and value.
 */
IMAGEIO_EXTERN CFArrayRef _iio_Nullable CGImageMetadataTagCopyQualifiers(CGImageMetadataTagRef _iio_Nonnull tag) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);


// ****************************************************************************
// Functions for copying CGImageMetadataTagRefs from a CGImageMetadataRef. 
// These functions make it easier for the caller to traverse complex nested 
// structures of metadata, similar to KVC-compliant Objective-C classes.
// ****************************************************************************
///*! @functiongroup Retrieving CGImageMetadataTagRefs from a CGImageMetadataRef */

/**
 * Returns an array of root-level metadata tags from the specified metadata object.
 *
 * - Parameters:
 *   - metadata: The metadata object that contains the tags.
 *
 * - Returns: An array that contains a shallow copy of all root-level ``CGImageMetadataTag`` objects. This array contains only the root-level tags. It doesn't contain any nested tags.
 */
IMAGEIO_EXTERN CFArrayRef _iio_Nullable CGImageMetadataCopyTags(CGImageMetadataRef _iio_Nonnull metadata) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Searches for a specific metadata tag within a metadata collection.
 *
 * - Parameters:
 *   - metadata: The metadata object that contains the tags.
 *   - parent: The parent tag, if any. Specify `NULL` to start the search in the top-level tags of the metadata object. If this parameter is `NULL`, you must include a valid prefix string in the `path` parameter.
 *   - path: A string that represents the path to the tag. A path consists of the tag's name, plus optional prefix and parent information. Separate prefix information from other path information using a colon (`:`) character. Separate parent and child tags using the period (`.`) character. For example, the string `“exif:Flash.RedEyeMode”` represents the path to the `RedEyeMode` field of the `Flash` parent structure in the EXIF metadata.
 *
 *     When a tag contains an ordered or unordered array, specify elements using a `0`-based index inside square brackets. For example, use the string `“dc.subject[2]”` to access the third element in the `subject` array.
 *
 *     When the tag contains an alternate-text array, access elements using an RFC 3066 language code inside square brackets. For example, use the string `“dc.description[de]”` to access the German description information.
 *
 *     Use the ? character to delimit qualifiers for tags with string values. You may not use this character for arrays and structures.
 *
 * - Returns: A copy of the ``CGImageMetadataTag`` object at the specified path, or `NULL` if the tag wasn't found.
 *
 * If you specify a valid tag in the `parent` parameter, you may omit the parent's path information from the `path` parameter. For example, to access the `RedEyeMode` field, specify the ``CGImageMetadataTag`` object for the `Flash` parent property, and specify `“RedEyeMode”` for the path string.
 *
 * If a tag contains a custom prefix that is not already present in the metadata object, call ``CGImageMetadataRegisterNamespaceForPrefix(_:_:_:_:)`` to register that prefix before you search for it with this function.
 */
IMAGEIO_EXTERN CGImageMetadataTagRef _iio_Nullable CGImageMetadataCopyTagWithPath(CGImageMetadataRef _iio_Nonnull metadata, CGImageMetadataTagRef _iio_Nullable parent, CFStringRef _iio_Nonnull path) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Searches the metadata for the specified tag, and returns its string value if it exists.
 *
 * - Parameters:
 *   - metadata: The metadata object to search.
 *   - parent: The parent tag, if any. Specify `NULL` to start the search in the top-level tags of the metadata object. If this parameter is `NULL`, you must include a valid prefix string in the `path` parameter.
 *   - path: A string that represents the path to the tag. A path consists of the tag's name, plus optional prefix and parent information. Separate prefix information from other path information using a colon (`:`) character. Separate parent and child tags using the period (`.`) character. For example, the string `“exif:Flash.RedEyeMode”` represents the path to the `RedEyeMode` field of the `Flash` parent structure in the EXIF metadata.
 *
 *     When a tag contains an ordered or unordered array, specify elements using a `0`-based index inside square brackets. For example, use the string `“dc.subject[2]”` to access the third element in the `subject` array.
 *
 *     When the tag contains an alternate-text array, access elements using an RFC 3066 language code inside square brackets. For example, use the string `“dc.description[de]”` to access the German description information.
 *
 *     Use the ? character to delimit qualifiers for tags with string values. You may not use this character for arrays and structures.
 *
 * - Returns: The string value for the specified tag, or `NULL` if the tag wasn't found or doesn't contain a string value.
 *
 * The XMP type of the property at the specified path must be ``CGImageMetadataType/string`` or ``CGImageMetadataType/alternateText``. If the property contains alternate text, this function returns the element with the `x-default` language qualifier.
 */
IMAGEIO_EXTERN CFStringRef _iio_Nullable CGImageMetadataCopyStringValueWithPath(CGImageMetadataRef _iio_Nonnull metadata, CGImageMetadataTagRef _iio_Nullable parent, CFStringRef _iio_Nonnull path) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

// ****************************************************************************
// Functions for modifying a CGMutableImageMetadataRef
// ****************************************************************************
///*! @functiongroup Modifying a CGMutableImageMetadataRef */

/**
 * Registers the specified namespace and prefix with the metadata object.
 *
 * - Parameters:
 *   - metadata: The metadata object in which to register the namespace.
 *   - xmlns: The namespace to register. Specify a string with a custom namespace URI. A custom namespace must be a valid XML namespace. By convention, namespaces end with either the `/` or `#` character.
 *   - prefix: An abbreviation for the XML namespace. You must specify a valid string for custom namespace.
 *   - err: A pointer to an error object. If an error occurs, this function assigns an error object to this parameter.
 *
 * - Returns: `true` if registration of the namespace was successful, or `false` if it wasn't.
 *
 * All tags you add to a ``CGMutableImageMetadata`` object must belong to known namespaces. When you encounter an unrecognized prefix in a metadata path, call this function to register the prefix before you add the corresponding tag.
 *
 * You don't need to register the standard metadata spaces, or any metadata spaces that are already present in the image's metadata. Register only the namespaces you need to support additional metadata tags.
 *
 * If the namespace already exists and the `prefix` parameter conflicts with the already registered prefix, this function returns `false` and places an error object in the `err` parameter. However, if the prefix matches what's registered, this method returns `true`.
 */
IMAGEIO_EXTERN bool CGImageMetadataRegisterNamespaceForPrefix(CGMutableImageMetadataRef _iio_Nonnull metadata, CFStringRef _iio_Nonnull xmlns, CFStringRef _iio_Nonnull prefix, _iio_Nullable CFErrorRef * _iio_Nullable err) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Sets the tag at the specified path in the metadata object.
 *
 * - Parameters:
 *   - metadata: The metadata object that contains the tag. If the tag doesn't exist in this metadata object, this function creates a new tag.
 *   - parent: The parent tag, if any. Specify `NULL` to add or update a tag starting at the top-level of the metadata object. If this parameter is `NULL`, you must include a valid prefix string in the `path` parameter.
 *
 *     If you specify a value for this parameter, this function modifies the children its children, which might create different references for those children. To fix the references, commit this object back to the metadata object using this function. Pass the parent's full path string; don't specify the parent using a parent object and relative path.
 *   - path: A string that represents the path to the tag. A path consists of the tag's name, plus optional prefix and parent information. Separate prefix information from other path information using a colon (`:`) character. Separate parent and child tags using the period (`.`) character. For example, the string `“exif:Flash.RedEyeMode”` represents the path to the `RedEyeMode` field of the `Flash` parent structure in the EXIF metadata.
 *
 *     When a tag contains an ordered or unordered array, specify elements using a `0`-based index inside square brackets. For example, use the string `“dc.subject[2]”` to access the third element in the `subject` array.
 *
 *     When the tag contains an alternate-text array, access elements using an RFC 3066 language code inside square brackets. For example, use the string `“dc.description[de]”` to access the German description information.
 *
 *     Use the ? character to delimit qualifiers for tags with string values. You may not use this character for arrays and structures.
 *   - tag: The tag object to add to the metadata. This function retains the tag object.
 *
 * - Returns: `true` if the function saved the tag successfully, or `false` if it encountered a problem.
 */
IMAGEIO_EXTERN bool CGImageMetadataSetTagWithPath(CGMutableImageMetadataRef _iio_Nonnull metadata, CGImageMetadataTagRef _iio_Nullable parent, CFStringRef _iio_Nonnull path, CGImageMetadataTagRef _iio_Nonnull tag) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Update the value of an existing metadata tag, or create a new tag using the specified information.
 *
 * - Parameters:
 *   - metadata: The metadata object that contains the tag. If the tag doesn't exist in this metadata object, this function creates a new tag.
 *   - parent: The parent tag, if any. Specify `NULL` to add or update a tag starting at the top-level of the metadata object. If this parameter is `NULL`, you must include a valid prefix string in the `path` parameter.
 *   - path: A string that represents the path to the tag. A path consists of the tag's name, plus optional prefix and parent information. Separate prefix information from other path information using a colon (`:`) character. Separate parent and child tags using the period (`.`) character. For example, the string `“exif:Flash.RedEyeMode”` represents the path to the `RedEyeMode` field of the `Flash` parent structure in the EXIF metadata.
 *
 *     When a tag contains an ordered or unordered array, specify elements using a `0`-based index inside square brackets. For example, use the string `“dc.subject[2]”` to access the third element in the `subject` array.
 *
 *     When the tag contains an alternate-text array, access elements using an RFC 3066 language code inside square brackets. For example, use the string `“dc.description[de]”` to access the German description information.
 *
 *     Use the ? character to delimit qualifiers for tags with string values. You may not use this character for arrays and structures.
 *   - value: The new value for the property. The new value's type must match the expected XMP type of the property at the specified `path`.
 *
 * - Returns: `true` if this function set the tag successfully, or `false` if a problem occurred.
 *
 * As needed, this function creates any intermediate tags that are required to create the tag at the specified path. This function creates each tag with default types. Tag creation fails if the path includes an unregistered prefix.
 *
 * If you specify a tag object in the `parent` parameter, this function modifies the children of that tag, which might create different references for those children. To fix the references, commit the changed parent back to the metadata object using the ``CGImageMetadataSetTagWithPath(_:_:_:_:)`` function. Pass the parent's full path string when calling that function; don't specify the parent using a parent object and relative path.
 */
IMAGEIO_EXTERN bool CGImageMetadataSetValueWithPath(CGMutableImageMetadataRef _iio_Nonnull metadata, CGImageMetadataTagRef _iio_Nullable parent, CFStringRef _iio_Nonnull path, CFTypeRef _iio_Nonnull value) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Removes the tag at the specified path from the metadata object.
 *
 * - Parameters:
 *   - metadata: The metadata object that contains the tag. If the tag doesn't exist in this metadata object, this function creates a new tag.
 *   - parent: The parent tag, if any. Specify `NULL` to add or update a tag starting at the top-level of the metadata object. If this parameter is `NULL`, you must include a valid prefix string in the `path` parameter.
 *
 *     If you specify a value for this parameter, this function modifies the children its children, which might create different references for those children. To fix the references, commit this object back to the metadata object using this function. Pass the parent's full path string; don't specify the parent using a parent object and relative path.
 *   - path: A string that represents the path to the tag. A path consists of the tag's name, plus optional prefix and parent information. Separate prefix information from other path information using a colon (`:`) character. Separate parent and child tags using the period (`.`) character. For example, the string `“exif:Flash.RedEyeMode”` represents the path to the `RedEyeMode` field of the `Flash` parent structure in the EXIF metadata.
 *
 *     When a tag contains an ordered or unordered array, specify elements using a `0`-based index inside square brackets. For example, use the string `“dc.subject[2]”` to access the third element in the `subject` array.
 *
 *     When the tag contains an alternate-text array, access elements using an RFC 3066 language code inside square brackets. For example, use the string `“dc.description[de]”` to access the German description information.
 *
 *     Use the ? character to delimit qualifiers for tags with string values. You may not use this character for arrays and structures.
 *
 * - Returns: true if this function removed the tag, or false if it encountered a problem.
 */
IMAGEIO_EXTERN bool CGImageMetadataRemoveTagWithPath(CGMutableImageMetadataRef _iio_Nonnull metadata,  CGImageMetadataTagRef _iio_Nullable parent, CFStringRef _iio_Nonnull path) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);


#ifdef __BLOCKS__
/*  Iterating through tags of CGImageMetadataRef */
/**
 * The block to execute when enumerating the tags of a metadata object.
 *
 * - Parameters:
 *   - path: The full path to the tag in the metadata container.
 *   - tag: The ``CGImageMetadataTag`` object that contains the tag information. Never modify this object from your block. If you want to change the tag, save a reference to it and make your changes later.
 *
 * - Returns: `true` to continue enumerating the tags, or `false` to stop.
 */
typedef bool(^CGImageMetadataTagBlock)(CFStringRef _iio_Nonnull path, CGImageMetadataTagRef _iio_Nonnull tag);

// Enumerates the children of the tag located at 'path'.
// If 'rootPath' is nil, all top-level tags in 'metadata' will be enumerated.
// Executes a CGImageMetadataTagBlock, 'block', for each CGImageMetadataTag.
// The block should return true to continue enumeration, or false to stop.
// Behavior is undefined if 'metadata' is modified during enumeration.

/**
 * Enumerates the tags of a metadata object and executes the specified block on each tag.
 *
 * - Parameters:
 *   - metadata: The metadata object that contains the tags to enumerate.
 *   - rootPath: A string that contains the path to the root tag. Specify `NULL` to enumerate the top-level tags in the metadata object.
 *
 *     A path consists of the tag's name, plus optional prefix and parent information. Separate prefix information from other path information using a colon (`:`) character. Separate parent and child tags using the period (`.`) character. For example, the string `“exif:Flash.RedEyeMode”` represents the path to the `RedEyeMode` field of the `Flash` parent structure in the EXIF metadata.
 *
 *     When a tag contains an ordered or unordered array, specify elements using a `0`-based index inside square brackets. For example, use the string `“dc.subject[2]”` to access the third element in the `subject` array.
 *
 *     When the tag contains an alternate-text array, access elements using an RFC 3066 language code inside square brackets. For example, use the string `“dc.description[de]”` to access the German description information.
 *
 *     Use the ? character to delimit qualifiers for tags with string values. You may not use this character for arrays and structures.
 *   - options: A dictionary of additional options. Currently, the only supported option is ``kCGImageMetadataEnumerateRecursively``.
 *   - block: The block to execute for each tag. For more information, see ``CGImageMetadataTagBlock``.
 *
 * This function iterates over the tags in the specified metadata object. By default, it iterates over only the top-level tags. Include the ``kCGImageMetadataEnumerateRecursively`` constant in the `options` parameter to iterate over all tags recursively.
 *
 * You must not modify the tag information from your block. Instead, use your block only to read information from the tags. If you need to modify any tags, add those tags to a collection object and modify them after this function finishes its enumeration.
 */
IMAGEIO_EXTERN void CGImageMetadataEnumerateTagsUsingBlock(CGImageMetadataRef _iio_Nonnull metadata, CFStringRef _iio_Nullable rootPath, CFDictionaryRef _iio_Nullable options, CGImageMetadataTagBlock _iio_Nonnull block) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);
#endif

// A key for the 'options' of CGImageMetadataEnumerateTagsUsingBlock. If present,
// the value should be a CFBoolean. If true, tags will be enumerated recursively,
// if false, only the direct children of 'rootPath' will be enumerated. 
// The default is non-recursive.
/**
 * An option to enumerate recursively through a set of metadata tags.
 *
 * The value of this key is a <doc://com.apple.documentation/documentation/corefoundation/cfboolean>. Set the value to <doc://com.apple.documentation/documentation/driverkit/kosbooleantrue> to enumerate all tags recursively. Set the value to <doc://com.apple.documentation/documentation/corefoundation/kcfbooleanfalse> to enumerate only the direct children of the root path you specify.
 *
 * When you call ``CGImageMetadataEnumerateTagsUsingBlock(_:_:_:_:)``, include this option if you want the enumeration behavior to search recursively through the available tags. If you don't specify this key, the function behaves as if the value is false.
 */
IMAGEIO_EXTERN const CFStringRef _iio_Nonnull kCGImageMetadataEnumerateRecursively IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);


// ****************************************************************************
// Functions for working with constants defined in CGImageProperties.h
// Provides a bridge for values from CGImageCopyPropertiesAtIndex().
// Simplifies metadata access for properties defined EXIF and IPTC standards, 
// which have no notion of namespaces, prefixes, or XMP property types.
// Metadata Working Group guidance is factored into the mapping of 
// CGImageProperties to XMP. For example, setting Exif DateTimeOriginal will
// set the value of the corresponding XMP tag, which is photoshop:DateCreated
// ****************************************************************************

///*! @functiongroup Working with CGImageProperties */

/**
 * Searches for the specified image property and, if found, returns the corresponding tag object.
 *
 * - Parameters:
 *   - metadata: The metadata object to search.
 *   - dictionaryName: The metadata subdictionary to which the image property belongs. For example, specify ``kCGImagePropertyExifDictionary`` for image properties that are part of the image's EXIF metadata.
 *   - propertyName: The name of the property. For example, specify ``kCGImagePropertyTIFFOrientation``, ``kCGImagePropertyExifDateTimeOriginal``, or ``kCGImagePropertyIPTCKeywords``. If the specified property is unsupported by the metadata object, this function logs a warning.
 *
 * - Returns: The ``CGImageMetadataTag`` object that corresponds to the specified property, or `NULL` if the property wasn't found.
 *
 * Use this function to quickly search the different metadata dictionaries for a specific tag. The returned tag object contains appropriate values for all fields, including the namespace, prefix, and XMP type.
 *
 * When you request an EXIF or IPTC property, this function fills in the namespace, prefix, and XMP type information by copying information from an appropriate XMP type. For example, when you request the ``kCGImagePropertyExifDateTimeOriginal`` property, the function fills in the information using the `photoshop:DateTime` XMP tag. When this bridging occurs, property fields retain their XMP format, rather than the EXIF or IPTC format.
 */
IMAGEIO_EXTERN CGImageMetadataTagRef _iio_Nullable CGImageMetadataCopyTagMatchingImageProperty(CGImageMetadataRef _iio_Nonnull metadata, CFStringRef _iio_Nonnull dictionaryName, CFStringRef _iio_Nonnull propertyName) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Updates the value of the metadata tag assigned to the specified image property.
 *
 * - Parameters:
 *   - metadata: The metadata object that contains the tag.
 *   - dictionaryName: The metadata subdictionary to which the image property belongs. For example, specify ``kCGImagePropertyExifDictionary`` for image properties that are part of the image's EXIF metadata. This function doesn't support all dictionaries.
 *   - propertyName: The name of the property. For example, specify ``kCGImagePropertyTIFFOrientation``, ``kCGImagePropertyExifDateTimeOriginal``, or ``kCGImagePropertyIPTCKeywords``. If the specified property is unsupported by the metadata object, this function logs a warning.
 *   - value: The new value for the property. The new value's type must match the XMP type of the metadata tag.
 *
 * - Returns: `true` if this function set the tag successfully, or `false` if a problem occurred.
 *
 * Use this function to update the value of a property in the specified metadata collection. If you try to set the value of an EXIF or IPTC property, this function matches it to an appropriate XMP tag. For example, when you set the value of the ``kCGImagePropertyExifDateTimeOriginal`` property, this function sets the value of the `photoshop:DateTime` XMP tag.
 *
 * If the metdata object doesn't contain the tag, this function creates it and populates it with appropriate XMP information.
 */
IMAGEIO_EXTERN bool CGImageMetadataSetValueMatchingImageProperty(CGMutableImageMetadataRef _iio_Nonnull metadata, CFStringRef _iio_Nonnull dictionaryName, CFStringRef _iio_Nonnull propertyName, CFTypeRef _iio_Nonnull value) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);


// ****************************************************************************
// Functions for converting metadata to and from XMP packets
// ****************************************************************************
///*! @functiongroup Reading and Writing XMP */

/**
 * Returns a data object that contains the metadata object's contents serialized into the XMP format.
 *
 * - Parameters:
 *   - metadata: The metadata object to serialize. The function converts all tags in this object to XMP data.
 *   - options: Additional options for the serialization process. Options aren't currently supported, so specify `NULL`.
 *
 * - Returns: A <doc://com.apple.documentation/documentation/corefoundation/cfdata> object with an XMP representation of the metadata, or `NULL` if an error occurs.
 *
 * Use this function to create sidecar files with metadata for image formats that don't support embedded XMP, or that you cannot edit due to other format restrictions. For example, use this function to create the data for proprietary RAW camera formats.
 */
IMAGEIO_EXTERN CFDataRef _iio_Nullable CGImageMetadataCreateXMPData (CGImageMetadataRef _iio_Nonnull metadata, CFDictionaryRef _iio_Nullable options) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * Creates a collection of metadata tags from the specified XMP data.
 *
 * - Parameters:
 *   - data: An object containin XMP data. The contents of this object must represent a complete XMP tree. The XMP data may include packet headers.
 *
 * - Returns: A ``CGImageMetadata`` object that contains the parsed metadata information, or `NULL` if an error occurs. You are responsible for releasing the returned object.
 *
 * Use this function to parse the raw XMP data from an image and build a parseable set of metadata tags. Use the returned object to enumerate the tags or search for individual tags within the collection.
 */
IMAGEIO_EXTERN CGImageMetadataRef _iio_Nullable CGImageMetadataCreateFromXMPData (CFDataRef _iio_Nonnull data) IMAGEIO_AVAILABLE_STARTING(10.8, 7.0);

/**
 * The domain for metadata-related errors that originate in the Image I/O framework.
 */
IMAGEIO_EXTERN const CFStringRef _iio_Nonnull kCFErrorDomainCGImageMetadata;

/**
 * Constants for errors that occur when getting or setting metadata information.
 */
typedef CF_ENUM(int32_t, CGImageMetadataErrors) {
    /**
     * An error that indicates an unknown condition occurred.
     */
    kCGImageMetadataErrorUnknown = 0,
    /**
     * An error that indicates the metadata was in an unsupported format.
     */
    kCGImageMetadataErrorUnsupportedFormat = 1,
    /**
     * An error that indicates a parameter was malformed or contained invalid data.
     */
    kCGImageMetadataErrorBadArgument = 2,
    /**
     * An error that indicates an attempt to save conflicting metadata values.
     */
    kCGImageMetadataErrorConflictingArguments = 3,
    /**
     * An error that indicates an attempt to register a namespace with a prefix that is different than the namespace's existing prefix.
     */
    kCGImageMetadataErrorPrefixConflict = 4,
};

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif // CGIMAGEMETADATA_H_
