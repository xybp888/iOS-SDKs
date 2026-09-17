/*
 * ColorSync - ColorSyncProfile.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNCPROFILE__
#define __COLORSYNCPROFILE__

#ifdef __cplusplus
extern "C" {
#endif

#include <ColorSync/ColorSyncBase.h>

/// A reference to an immutable International Color Consortium (ICC) color profile.
typedef const struct CF_BRIDGED_TYPE(id) ColorSyncProfile* ColorSyncProfileRef;

/// A reference to a mutable ICC color profile.
typedef struct CF_BRIDGED_TYPE(id) ColorSyncProfile* ColorSyncMutableProfileRef;

#if !defined(__swift__)

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN
    
#endif

#define icVersion4Number       0x04000000L /* 4.0.0, BCD */
#define icVersion4Point4Number 0x04400000L /* 4.4.0, BCD */

/// The generic gray color profile.
CSEXTERN CFStringRef kColorSyncGenericGrayProfile CS_AVAILABLE_STARTING(10.4, 16.0);          /* com.apple.ColorSync.GenericGray  */
/// The generic gray color profile with a gamma of 2.2.
CSEXTERN CFStringRef kColorSyncGenericGrayGamma22Profile CS_AVAILABLE_STARTING(10.4, 16.0);   /* com.apple.ColorSync.GenericGrayGamma2.2  */
/// The generic RGB color profile.
CSEXTERN CFStringRef kColorSyncGenericRGBProfile CS_AVAILABLE_STARTING(10.4, 16.0);           /* com.apple.ColorSync.GenericRGB   */
/// The generic CMYK color profile.
CSEXTERN CFStringRef kColorSyncGenericCMYKProfile CS_AVAILABLE_STARTING(10.4, 16.0);          /* com.apple.ColorSync.GenericCMYK  */
/// The Display P3 color profile.
CSEXTERN CFStringRef kColorSyncDisplayP3Profile CS_AVAILABLE_STARTING(10.4, 16.0);            /* com.apple.ColorSync.DisplayP3 */
/// The sRGB color profile.
CSEXTERN CFStringRef kColorSyncSRGBProfile CS_AVAILABLE_STARTING(10.4, 16.0);                 /* com.apple.ColorSync.sRGB         */
/// The Adobe RGB (1998) color profile.
CSEXTERN CFStringRef kColorSyncAdobeRGB1998Profile CS_AVAILABLE_STARTING(10.4, 16.0);         /* com.apple.ColorSync.AdobeRGB1998 */
/// The generic CIELAB color profile.
CSEXTERN CFStringRef kColorSyncGenericLabProfile CS_AVAILABLE_STARTING(10.4, 16.0);           /* com.apple.ColorSync.GenericLab */
/// The generic CIEXYZ color profile.
CSEXTERN CFStringRef kColorSyncGenericXYZProfile CS_AVAILABLE_STARTING(10.4, 16.0);           /* com.apple.ColorSync.GenericXYZ */

/// The ACEScg linear color profile.
CSEXTERN CFStringRef kColorSyncACESCGLinearProfile CS_AVAILABLE_STARTING(10.4, 16.0);         /* com.apple.ColorSync.ACESCGLinear */
/// The DCI-P3 color profile.
CSEXTERN CFStringRef kColorSyncDCIP3Profile CS_AVAILABLE_STARTING(10.4, 16.0);                /* com.apple.ColorSync.DCIP3 */
/// The ITU-R BT.709 color profile.
CSEXTERN CFStringRef kColorSyncITUR709Profile CS_AVAILABLE_STARTING(10.4, 16.0);              /* com.apple.ColorSync.ITUR709 */
/// The ITU-R BT.2020 color profile.
CSEXTERN CFStringRef kColorSyncITUR2020Profile CS_AVAILABLE_STARTING(10.4, 16.0);             /* com.apple.ColorSync.ITUR2020 */

/// The ROMM RGB (ProPhoto RGB) color profile.
CSEXTERN CFStringRef kColorSyncROMMRGBProfile CS_AVAILABLE_STARTING(10.4, 16.0);              /* com.apple.ColorSync.ROMMRGB */

/// The web-safe colors profile.
CSEXTERN CFStringRef kColorSyncWebSafeColorsProfile CS_AVAILABLE_STARTING(13.0, 16.1);        /* com.apple.ColorSync.WebSafeColors */

/// A key for the profile's header data.
CSEXTERN CFStringRef kColorSyncProfileHeader CS_AVAILABLE_STARTING(10.4, 16.0);      /* com.apple.ColorSync.ProfileHeader */
/// A key for the profile's class.
CSEXTERN CFStringRef kColorSyncProfileClass CS_AVAILABLE_STARTING(10.4, 16.0);       /* com.apple.ColorSync.ProfileClass */
/// A key for the profile's color space.
CSEXTERN CFStringRef kColorSyncProfileColorSpace CS_AVAILABLE_STARTING(10.4, 16.0);  /* com.apple.ColorSync.ProfileColorSpace */
/// A key for the profile's connection space (PCS).
CSEXTERN CFStringRef kColorSyncProfilePCS CS_AVAILABLE_STARTING(10.4, 16.0);         /* com.apple.ColorSync.PCS */
/// A key for the profile's URL.
CSEXTERN CFStringRef kColorSyncProfileURL CS_AVAILABLE_STARTING(10.4, 16.0);         /* com.apple.ColorSync.ProfileURL */
/// A key for the profile's localized description.
CSEXTERN CFStringRef kColorSyncProfileDescription CS_AVAILABLE_STARTING(10.4, 16.0); /* com.apple.ColorSync.ProfileDescription */
/// A key for the profile's MD5 digest.
CSEXTERN CFStringRef kColorSyncProfileMD5Digest CS_AVAILABLE_STARTING(10.4, 16.0);   /* com.apple.ColorSync.ProfileMD5Digest */
/// A key indicating whether the profile is valid.
CSEXTERN CFStringRef kColorSyncProfileIsValid   CS_AVAILABLE_STARTING(13.0, 16.0);   /* com.apple.ColorSync.ProfileIsValid */

/// The signature of the device-to-PCS transform tag for the perceptual rendering intent.
CSEXTERN CFStringRef kColorSyncSigAToB0Tag CS_AVAILABLE_STARTING(10.4, 16.0);                       /* 0x41324230L => CFSTR("A2B0")*/
/// The signature of the device-to-PCS transform tag for the media-relative colorimetric rendering intent.
CSEXTERN CFStringRef kColorSyncSigAToB1Tag CS_AVAILABLE_STARTING(10.4, 16.0);                       /* 0x41324231L => CFSTR("A2B1")*/
/// The signature of the device-to-PCS transform tag for the saturation rendering intent.
CSEXTERN CFStringRef kColorSyncSigAToB2Tag CS_AVAILABLE_STARTING(10.4, 16.0);                       /* 0x41324232L => CFSTR("A2B2")*/
/// The signature of the PCS-to-device transform tag for the perceptual rendering intent.
CSEXTERN CFStringRef kColorSyncSigBToA0Tag CS_AVAILABLE_STARTING(10.4, 16.0);                       /* 0x42324130L => CFSTR("B2A0")*/
/// The signature of the PCS-to-device transform tag for the media-relative colorimetric rendering intent.
CSEXTERN CFStringRef kColorSyncSigBToA1Tag CS_AVAILABLE_STARTING(10.4, 16.0);                       /* 0x42324131L => CFSTR("B2A1")*/
/// The signature of the PCS-to-device transform tag for the saturation rendering intent.
CSEXTERN CFStringRef kColorSyncSigBToA2Tag CS_AVAILABLE_STARTING(10.4, 16.0);                       /* 0x42324132L => CFSTR("B2A2")*/
/// The signature identifying the CMYK data color space.
CSEXTERN CFStringRef kColorSyncSigCmykData CS_AVAILABLE_STARTING(10.4, 16.0);                       /* 0x434D594BL => CFSTR("CMYK")*/
/// The signature identifying the grayscale data color space.
CSEXTERN CFStringRef kColorSyncSigGrayData CS_AVAILABLE_STARTING(10.4, 16.0);                       /* 0x47524159L => CFSTR("GRAY")*/
/// The signature identifying the CIELAB data color space.
CSEXTERN CFStringRef kColorSyncSigLabData CS_AVAILABLE_STARTING(10.4, 16.0);                        /* 0x4C616220L => CFSTR("Lab ")*/
/// The signature identifying the RGB data color space.
CSEXTERN CFStringRef kColorSyncSigRgbData CS_AVAILABLE_STARTING(10.4, 16.0);                        /* 0x52474220L => CFSTR("RGB ")*/
/// The signature identifying the CIEXYZ data color space.
CSEXTERN CFStringRef kColorSyncSigXYZData CS_AVAILABLE_STARTING(10.4, 16.0);                        /* 0x58595A20L => CFSTR("XYZ ")*/
/// The signature identifying an abstract profile class.
CSEXTERN CFStringRef kColorSyncSigAbstractClass CS_AVAILABLE_STARTING(10.4, 16.0);                  /* 0x61627374L => CFSTR("abst")*/
/// The signature of the blue channel's tone reproduction curve (TRC) tag.
CSEXTERN CFStringRef kColorSyncSigBlueTRCTag CS_AVAILABLE_STARTING(10.4, 16.0);                     /* 0x62545243L => CFSTR("bTRC")*/
/// The signature of the blue colorant tag, giving the blue channel's PCSXYZ values.
CSEXTERN CFStringRef kColorSyncSigBlueColorantTag CS_AVAILABLE_STARTING(10.4, 16.0);                /* 0x6258595AL => CFSTR("bXYZ")*/
/// The signature of the media black point tag.
CSEXTERN CFStringRef kColorSyncSigMediaBlackPointTag CS_AVAILABLE_STARTING(10.4, 16.0);             /* 0x626B7074L => CFSTR("bkpt")*/
/// The signature of the profile copyright tag.
CSEXTERN CFStringRef kColorSyncSigCopyrightTag CS_AVAILABLE_STARTING(10.4, 16.0);                   /* 0x63707274L => CFSTR("cprt")*/
/// The signature of the profile description tag.
CSEXTERN CFStringRef kColorSyncSigProfileDescriptionTag CS_AVAILABLE_STARTING(10.4, 16.0);          /* 0x64657363L => CFSTR("desc")*/
/// The signature of the device model description tag.
CSEXTERN CFStringRef kColorSyncSigDeviceModelDescTag CS_AVAILABLE_STARTING(10.4, 16.0);             /* 0x646D6464L => CFSTR("dmdd")*/
/// The signature of the device manufacturer description tag.
CSEXTERN CFStringRef kColorSyncSigDeviceMfgDescTag CS_AVAILABLE_STARTING(10.4, 16.0);               /* 0x646D6E64L => CFSTR("dmnd")*/
/// The signature of the green channel's tone reproduction curve (TRC) tag.
CSEXTERN CFStringRef kColorSyncSigGreenTRCTag CS_AVAILABLE_STARTING(10.4, 16.0);                    /* 0x67545243L => CFSTR("gTRC")*/
/// The signature of the green colorant tag, giving the green channel's PCSXYZ values.
CSEXTERN CFStringRef kColorSyncSigGreenColorantTag CS_AVAILABLE_STARTING(10.4, 16.0);               /* 0x6758595AL => CFSTR("gXYZ")*/
/// The signature of the gamut tag, marking which PCS colors fall outside the device gamut.
CSEXTERN CFStringRef kColorSyncSigGamutTag CS_AVAILABLE_STARTING(10.4, 16.0);                       /* 0x67616D74L => CFSTR("gamt")*/
/// The signature of the grayscale tone reproduction curve (TRC) tag.
CSEXTERN CFStringRef kColorSyncSigGrayTRCTag CS_AVAILABLE_STARTING(10.4, 16.0);                     /* 0x6B545243L => CFSTR("kTRC")*/
/// The signature identifying a device-link profile class.
CSEXTERN CFStringRef kColorSyncSigLinkClass CS_AVAILABLE_STARTING(10.4, 16.0);                      /* 0x6C696E6BL => CFSTR("link")*/
/// The signature identifying a display device profile class.
CSEXTERN CFStringRef kColorSyncSigDisplayClass CS_AVAILABLE_STARTING(10.4, 16.0);                   /* 0x6D6E7472L => CFSTR("mntr")*/
/// The signature of the named color (version 2) tag.
CSEXTERN CFStringRef kColorSyncSigNamedColor2Tag CS_AVAILABLE_STARTING(10.4, 16.0);                 /* 0x6E636C32L => CFSTR("ncl2")*/
/// The signature identifying a named color profile class.
CSEXTERN CFStringRef kColorSyncSigNamedColorClass CS_AVAILABLE_STARTING(10.4, 16.0);                /* 0x6E6D636CL => CFSTR("nmcl")*/
/// The signature of the preview tag for the perceptual rendering intent.
CSEXTERN CFStringRef kColorSyncSigPreview0Tag CS_AVAILABLE_STARTING(10.4, 16.0);                    /* 0x70726530L => CFSTR("pre0")*/
/// The signature of the preview tag for the media-relative colorimetric rendering intent.
CSEXTERN CFStringRef kColorSyncSigPreview1Tag CS_AVAILABLE_STARTING(10.4, 16.0);                    /* 0x70726531L => CFSTR("pre1")*/
/// The signature of the preview tag for the saturation rendering intent.
CSEXTERN CFStringRef kColorSyncSigPreview2Tag CS_AVAILABLE_STARTING(10.4, 16.0);                    /* 0x70726532L => CFSTR("pre2")*/
/// The signature identifying an output (printer) device profile class.
CSEXTERN CFStringRef kColorSyncSigOutputClass CS_AVAILABLE_STARTING(10.4, 16.0);                    /* 0x70727472L => CFSTR("prtr")*/
/// The signature of the profile sequence description tag.
CSEXTERN CFStringRef kColorSyncSigProfileSequenceDescTag CS_AVAILABLE_STARTING(10.4, 16.0);         /* 0x70736571L => CFSTR("pseq")*/
/// The signature of the red channel's tone reproduction curve (TRC) tag.
CSEXTERN CFStringRef kColorSyncSigRedTRCTag CS_AVAILABLE_STARTING(10.4, 16.0);                      /* 0x72545243L => CFSTR("rTRC")*/
/// The signature of the red colorant tag, giving the red channel's PCSXYZ values.
CSEXTERN CFStringRef kColorSyncSigRedColorantTag CS_AVAILABLE_STARTING(10.4, 16.0);                 /* 0x7258595AL => CFSTR("rXYZ")*/
/// The signature identifying an input (scanner or camera) device profile class.
CSEXTERN CFStringRef kColorSyncSigInputClass CS_AVAILABLE_STARTING(10.4, 16.0);                     /* 0x73636E72L => CFSTR("scnr")*/
/// The signature identifying a color-space conversion profile class.
CSEXTERN CFStringRef kColorSyncSigColorSpaceClass CS_AVAILABLE_STARTING(10.4, 16.0);                /* 0x73706163L => CFSTR("spac")*/
/// The signature of the technology tag, identifying the device technology.
CSEXTERN CFStringRef kColorSyncSigTechnologyTag CS_AVAILABLE_STARTING(10.4, 16.0);                  /* 0x74656368L => CFSTR("tech")*/
/// The signature of the viewing conditions tag.
CSEXTERN CFStringRef kColorSyncSigViewingConditionsTag CS_AVAILABLE_STARTING(10.4, 16.0);           /* 0x76696577L => CFSTR("view")*/
/// The signature of the viewing conditions description tag.
CSEXTERN CFStringRef kColorSyncSigViewingCondDescTag CS_AVAILABLE_STARTING(10.4, 16.0);             /* 0x76756564L => CFSTR("vued")*/
/// The signature of the media white point tag.
CSEXTERN CFStringRef kColorSyncSigMediaWhitePointTag CS_AVAILABLE_STARTING(10.4, 16.0);             /* 0x77747074L => CFSTR("wtpt")*/


/// Returns the unique identifier for the ColorSync profile opaque type.
///
/// - Returns: The `CFTypeID` for `ColorSyncProfile` objects.
CSEXTERN CFTypeID ColorSyncProfileGetTypeID(void) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Creates a profile from ICC profile data.
///
/// - Parameters:
///   - data: The ICC profile data.
///   - error: On failure, a pointer to an error describing the problem. Optional.
/// - Returns: A new profile, or `NULL` in case of failure.
CSEXTERN ColorSyncProfileRef __nullable ColorSyncProfileCreate(CFDataRef data, CFErrorRef* __nullable error) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Creates a profile from ICC profile data at a URL.
///
/// - Parameters:
///   - url: The URL to the profile data.
///   - error: On failure, a pointer to an error describing the problem. Optional.
/// - Returns: A new profile, or `NULL` in case of failure.
CSEXTERN ColorSyncProfileRef __nullable ColorSyncProfileCreateWithURL(CFURLRef url, CFErrorRef* __nullable error) CS_AVAILABLE_STARTING(10.4, 16.0);

/// An option that, when set to `kCFBooleanTrue`, skips substituting a matching system-provided profile.
CSEXTERN CFStringRef kColorSyncDoNotSubstituteProfiles CS_AVAILABLE_STARTING(26.1, 26.1);
/// Creates a profile from ICC profile data at a URL, using the given options.
///
/// - Parameters:
///   - url: The URL to the profile data.
///   - options: A dictionary with creation options, for example ``kColorSyncDoNotSubstituteProfiles``.
///   - error: On failure, a pointer to an error describing the problem. Optional.
/// - Returns: A new profile, or `NULL` in case of failure.
CSEXTERN ColorSyncProfileRef __nullable ColorSyncProfileCreateWithURLAndOptions(CFURLRef url, CFDictionaryRef __nullable options, CFErrorRef* __nullable error) CS_AVAILABLE_STARTING(26.1, 26.1);

/// Creates a profile from a predefined profile name.
///
/// - Parameter name: The predefined profile name.
/// - Returns: A new profile, or `NULL` in case of failure.
CSEXTERN ColorSyncProfileRef __nullable ColorSyncProfileCreateWithName(CFStringRef name) CS_AVAILABLE_STARTING(10.4, 16.0);


/// Creates an empty mutable profile.
///
/// - Returns: An empty mutable profile, or `NULL` in case of failure.
CSEXTERN ColorSyncMutableProfileRef __nullable ColorSyncProfileCreateMutable(void) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Creates a mutable copy of a profile.
///
/// - Parameter prof: The profile whose data the function copies into the new mutable profile.
/// - Returns: A new mutable profile, or `NULL` in case of failure.
CSEXTERN ColorSyncMutableProfileRef __nullable ColorSyncProfileCreateMutableCopy(ColorSyncProfileRef prof) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Creates a device link profile from an array of profiles.
///
/// Each dictionary in `profileInfo` contains a profile object and information on the usage of the
/// profile in the transform.
///
/// Required keys:
/// - ``kColorSyncProfile``: A ``ColorSyncProfileRef``.
/// - ``kColorSyncRenderingIntent``: A `CFStringRef` defining the rendering intent.
/// - ``kColorSyncTransformTag``: A `CFStringRef` defining which tags to use.
///
/// Optional key:
/// - ``kColorSyncBlackPointCompensation``: A `CFBooleanRef` to enable or disable black point compensation.
///
/// - Parameters:
///   - profileInfo: An array of dictionaries, each containing a profile object and the information on the usage of the profile in the transform.
///   - options: A dictionary with additional public global options (for example, preferred CMM, quality, and so on). It can also contain custom options that are CMM specific.
/// - Returns: A new profile, or `NULL` in case of failure.
CSEXTERN ColorSyncProfileRef __nullable ColorSyncProfileCreateLink (CFArrayRef profileInfo, CFDictionaryRef __nullable options) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Verifies whether a profile can be used.
///
/// - Parameters:
///   - prof: The profile to verify.
///   - errors: Returns error strings in case problems are found that would prevent use of the profile.
///   - warnings: Returns warning strings indicating problems due to lack of conformance with the ICC specification, but not preventing use of the profile.
/// - Returns: `true` if the profile can be used; otherwise, `false`.
CSEXTERN bool ColorSyncProfileVerify (ColorSyncProfileRef prof, CFErrorRef* __nullable errors, CFErrorRef* __nullable warnings) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Returns a Boolean value indicating whether the display profile describes a wide-gamut color space.
CSEXTERN bool ColorSyncProfileIsWideGamut (ColorSyncProfileRef) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Returns a Boolean value indicating whether the profile is matrix-based.
CSEXTERN bool ColorSyncProfileIsMatrixBased (ColorSyncProfileRef) CS_AVAILABLE_STARTING(11.0, 16.0);

/// Returns a Boolean value indicating whether the profile uses ITU BT.2100 PQ transfer functions.
CSEXTERN bool ColorSyncProfileIsPQBased (ColorSyncProfileRef) CS_AVAILABLE_STARTING(11.0, 16.0);

/// Returns a Boolean value indicating whether the profile uses ITU BT.2100 HLG transfer functions.
CSEXTERN bool ColorSyncProfileIsHLGBased (ColorSyncProfileRef) CS_AVAILABLE_STARTING(11.0, 16.0);


/// Estimates the gamma of a profile.
///
/// - Parameters:
///   - prof: The profile to perform estimation on.
///   - error: On failure, a pointer to an error describing the problem. Optional.
/// - Returns: A non-zero value on success, or `0.0` in case of error.
CSEXTERN float ColorSyncProfileEstimateGamma (ColorSyncProfileRef prof, CFErrorRef* __nullable error) CS_AVAILABLE_STARTING(10.4, 26.1);
    
#define COLORSYNC_MD5_LENGTH  16

/// An MD5 digest that uniquely identifies a profile, as defined by the ICC specification.
typedef struct { uint8_t digest[COLORSYNC_MD5_LENGTH]; } ColorSyncMD5;

/// Returns the MD5 digest for a profile.
///
/// - Parameter prof: The profile to compute the digest for.
/// - Returns: The MD5 digest for the profile, calculated as defined by the ICC specification, or a "zero" signature (filled with zeros) in case of failure.
CSEXTERN ColorSyncMD5 ColorSyncProfileGetMD5(ColorSyncProfileRef prof) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Copies the flattened data from a profile.
///
/// - Parameters:
///   - prof: The profile to copy the flattened data from.
///   - error: On failure, a pointer to an error describing the problem. Optional.
/// - Returns: The profile data on success, or `NULL` in case of failure.
CSEXTERN CFDataRef ColorSyncProfileCopyData (ColorSyncProfileRef prof, CFErrorRef* __nullable error) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Returns the URL of a profile.
///
/// - Parameters:
///   - prof: The profile to get the URL from.
///   - error: On failure, a pointer to an error describing the problem. Optional.
/// - Returns: The profile's URL on success, or `NULL` in case of failure.
CSEXTERN CFURLRef ColorSyncProfileGetURL (ColorSyncProfileRef prof, CFErrorRef* __nullable error) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Copies the header from a profile.
///
/// - Parameter prof: The profile to copy the header from.
/// - Returns: The profile header (in host endianness), or `NULL` in case of failure.
CSEXTERN CFDataRef ColorSyncProfileCopyHeader (ColorSyncProfileRef prof) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Sets the header of a mutable profile.
///
/// - Parameters:
///   - prof: The profile in which to set the header.
///   - header: The header data (must be in host endianness).
CSEXTERN void ColorSyncProfileSetHeader (ColorSyncMutableProfileRef prof, CFDataRef header) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Copies the localized description string of a profile.
///
/// - Parameter prof: The profile to copy the description string from.
/// - Returns: The profile description, localized to the current locale.
CSEXTERN CFStringRef __nullable ColorSyncProfileCopyDescriptionString (ColorSyncProfileRef prof) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Copies the tag signatures of a profile.
///
/// - Parameter prof: The profile to copy tag signatures from.
/// - Returns: An array with the signatures (`CFStringRef`) of the tags in the profile.
CSEXTERN CFArrayRef __nullable ColorSyncProfileCopyTagSignatures (ColorSyncProfileRef prof) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Returns a Boolean value indicating whether a profile contains a given tag.
///
/// - Parameters:
///   - prof: The profile in which to search for the tag.
///   - signature: The signature of the tag to search for.
/// - Returns: `true` if the tag exists; otherwise, `false`.
CSEXTERN bool ColorSyncProfileContainsTag (ColorSyncProfileRef prof, CFStringRef signature) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Copies a tag from a profile.
///
/// - Parameters:
///   - prof: The profile to copy the tag from.
///   - signature: The signature of the tag to copy.
/// - Returns: The tag data, or `NULL` in case of failure.
CSEXTERN CFDataRef __nullable ColorSyncProfileCopyTag (ColorSyncProfileRef prof, CFStringRef signature) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Sets a tag in a mutable profile.
///
/// - Parameters:
///   - prof: The profile in which to set the tag.
///   - signature: The signature of the tag to set in the profile.
///   - data: The tag data.
CSEXTERN void ColorSyncProfileSetTag (ColorSyncMutableProfileRef prof, CFStringRef signature, CFDataRef data) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Removes a tag from a mutable profile.
///
/// - Parameters:
///   - prof: The profile to remove the tag from.
///   - signature: The signature of the tag to remove.
CSEXTERN void ColorSyncProfileRemoveTag (ColorSyncMutableProfileRef prof, CFStringRef signature) CS_AVAILABLE_STARTING(10.4, 16.0);


/// A callback that the framework invokes for each installed profile during iteration.
///
/// The framework passes only validated profiles to the callback. Return `false` to stop the iteration.
///
/// - Parameters:
///   - profileInfo: A dictionary describing the profile.
///   - userInfo: The user info passed to the iteration function.
typedef bool (*ColorSyncProfileIterateCallback)(CFDictionaryRef profileInfo, void* userInfo);

#define COLORSYNC_ITERATE_ASYNC

/// The current profile-cache seed (uint32_t), sent with ``kColorSyncProfileRepositoryChangeNotification``.
CSEXTERN CFStringRef kColorSyncProfileCacheSeed;

/// Iterates over the installed profiles.
///
/// When called for the first time, this function returns only system profiles, because profile
/// iteration is a slow process requiring multiple accesses to the file system. Clients are advised
/// to register for ``kColorSyncProfileRepositoryChangeNotification`` using `CFNotificationCenter` or
/// `NSNotificationCenter` to obtain all installed profiles. The notification callback receives, if
/// possible, a `CFDictionary` containing a new seed value of the profile cache (key
/// ``kColorSyncProfileCacheSeed`` / value `kCFNumberSInt32Type`). Comparing old and new seed values
/// may prevent unnecessary calls to iterate installed profiles. Alternatively, call
/// ``ColorSyncIterateInstalledProfilesWithOptions`` with the ``kColorSyncWaitForCacheReply``
/// option set to `kCFBooleanTrue` to obtain all installed profiles in one call.
///
/// - Parameters:
///   - callBack: A pointer to a client-provided function (can be `NULL`).
///   - seed: A pointer to a cache seed owned by the client (can be `NULL`).
///   - userInfo: User-defined data passed to the callback.
///   - error: On failure, a pointer to an error describing the problem. Optional.
CSEXTERN void ColorSyncIterateInstalledProfiles (ColorSyncProfileIterateCallback __nullable callBack,
                                                 uint32_t*                       __nullable seed,
                                                 void*                           __nullable userInfo,
                                                 CFErrorRef*                     __nullable error) CS_AVAILABLE_STARTING(10.4, 16.0);


    /********************************************************************************************
    *                                                                                           *
    *   For further information on ICC profiles refer to ICC profile specification published    *
    *   by International Color Consortium at www.color.org                                      *
    *                                                                                           *
    *   ICC header file (ICC.h) containing programmatic definitions of ICC data types can be    *
    *   downloaded from the Technical Notes web page of ICC website at                          *
    *   www.color.org/technotes.xalter                                                          *
    *                                                                                           *
    ********************************************************************************************/

#ifdef __cplusplus
}
#endif

#if !defined(__swift__)

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif

#endif /* __COLORSYNCPROFILE__ */
