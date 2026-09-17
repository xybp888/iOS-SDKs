/*
 * ColorSync - ColorSyncHeadroomAdaptiveGainCurve.h
 * Copyright (c)  2026 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNCHEADROOMADAPTIVEGAINCURVE__
#define __COLORSYNCHEADROOMADAPTIVEGAINCURVE__

#ifdef __cplusplus
extern "C" {
#endif

#include <ColorSync/ColorSyncBase.h>
#include <ColorSync/ColorSyncProfile.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

API_AVAILABLE_BEGIN(macos(27.0), ios(27.0), tvos(27.0), watchos(27.0), visionos(27.0))

/// Returns a copy of a profile with the supplied Headroom Adaptive Gain Curve
/// data embedded as an HAGC tag.
///
/// - Parameters:
///   - profile: A profile whose CICP tag indicates a PQ, HLG, or linear transfer
///     function. (Use linear for extended-range data.) Passing an SDR profile
///     returns `NULL`.
///   - data: The raw Headroom Adaptive Gain Curve data to embed. Must be non-`NULL`.
///   - options: Reserved for future use. Pass `NULL`.
/// - Returns: A new profile that the caller must release with `CFRelease`, or
///   `NULL` on failure.
CSEXTERN ColorSyncProfileRef __nullable ColorSyncProfileCreateCopyWithHeadroomAdaptiveGainCurveMetadata(ColorSyncProfileRef profile, CFDataRef data, __nullable CFDictionaryRef options) CF_REFINED_FOR_SWIFT CF_RETURNS_RETAINED;

/// Returns a copy of the raw Headroom Adaptive Gain Curve data embedded in a profile.
///
/// - Parameter profile: The profile to read the HAGC tag from.
/// - Returns: A copy of the raw HAGC data that the caller must release with
///   `CFRelease`, or `NULL` if the profile contains no HAGC tag.
CSEXTERN CFDataRef __nullable ColorSyncProfileCopyHeadroomAdaptiveGainCurveMetadata(ColorSyncProfileRef profile) CF_REFINED_FOR_SWIFT CF_RETURNS_RETAINED;

/// Returns a copy of a profile with an HAGC tag synthesized from an info dictionary.
///
/// - Parameters:
///   - profile: A profile whose CICP tag indicates a PQ, HLG, or linear transfer
///     function. (Use linear for extended-range data.) Passing an SDR profile
///     returns `NULL`.
///   - info: A dictionary describing the gain curve. See the key constants
///     declared below for its structure.
/// - Returns: A new profile that the caller must release with `CFRelease`, or
///   `NULL` on failure.
CSEXTERN ColorSyncProfileRef __nullable ColorSyncProfileCreateCopyWithHeadroomAdaptiveGainCurveInfoDictionary(ColorSyncProfileRef profile, CFDictionaryRef info) CF_REFINED_FOR_SWIFT CF_RETURNS_RETAINED;

/// Returns a dictionary describing the Headroom Adaptive Gain Curve decoded from a profile.
///
/// - Parameter profile: The profile to decode the HAGC tag from.
/// - Returns: A dictionary describing the gain curve, which the caller must
///   release with `CFRelease`, or `NULL` if the profile carries no HAGC tag.
///   See the key constants declared below for the dictionary's contents.
CSEXTERN CFDictionaryRef __nullable ColorSyncProfileCopyHeadroomAdaptiveGainCurveInfoDictionary(ColorSyncProfileRef profile) CF_REFINED_FOR_SWIFT CF_RETURNS_RETAINED;

/// Returns whether a profile contains a Headroom Adaptive Gain Curve tag.
///
/// - Parameter profile: The profile to test.
/// - Returns: `true` if the profile contains an HAGC tag; otherwise, `false`.
CSEXTERN bool ColorSyncProfileContainsHeadroomAdaptiveGainCurve(ColorSyncProfileRef profile);

/*
Dictionary structure returned by `ColorSyncProfileCopyHeadroomAdaptiveGainCurveInfoDictionary`.
Indentation reflects nesting; entries marked (1) or (2) share the value from array index 0
when the indicated flag is true.


| Key                                                       | Type               | Condition |
| --------------------------------------------------------- | ------------------ | --------- |
| `kColorSyncHeadroomAdaptiveGainCurveApplicationVersion`   | `CFNumberRef (u8)` | always    |
| `kColorSyncHeadroomAdaptiveGainCurveColorVolumeTransform` | `CFDictionaryRef`  | if Custom Reference White or Headroom-Adaptive tone map |
| `├─ kColorSyncCustomHDRReferenceWhite`                    | `CFNumberRef (f)`  | if Custom Reference White |
| `└─ kColorSyncHeadroomAdaptiveToneMappingInfo`            | `CFDictionaryRef`  | if Headroom-Adaptive tone map (`kCFBooleanFalse` otherwise) |
| `  ├─ kColorSyncBaselineHeadroomStops`                    | `CFNumberRef (f)`  | always    |
| `  └─ kColorSyncHeadroomAdaptiveGainCurveInfo`            | `CFDictionaryRef`  | if `RWTMO == false` (`kCFBooleanFalse` otherwise) |
| `    ├─ kColorSyncAlternateCurveCount`                    | `CFNumberRef (u8)` | always    |
| `    ├─ kColorSyncCommonComponentMixing`                  | `CFBooleanRef`     | always    |
| `    ├─ kColorSyncCommonCurveParameters`                  | `CFBooleanRef`     | always    |
| `    ├─ kColorSyncGainCurveChromaticities`                | `CFNumberRef (u8)`<br> or `CFArrayRef (f)` | always; CFNumberRef for standard primaries enum,<br>or CFArray of 8 floats for custom primaries |
| `    └─ kColorSyncAlternateGainCurveInfo`                 | `CFArrayRef`       | if `alternate curve count > 0` |
| `      └─ [each of alternate_curve_count elements]`       | `CFDictionaryRef`  |           |
| `        ├─ kColorSyncAlternateCurveHeadroomStops`        | `CFNumberRef (f)`  | always    |
| `        ├─ kColorSyncComponentMix`                       | `CFNumberRef (u8)` | always (1)|
| `        ├─ kColorSyncComponentCoefficients`              | `CFDictionaryRef`  | if `kColorSyncComponentMix == 3` (1) |
| `        │ ├─ kColorSyncCoefficientRed`                   | `CFNumberRef (f)`  | if present in bitstream |
| `        │ ├─ kColorSyncCoefficientGreen`                 | `CFNumberRef (f)`  | if present in bitstream |
| `        │ ├─ kColorSyncCoefficientBlue`                  | `CFNumberRef (f)`  | if present in bitstream |
| `        │ ├─ kColorSyncCoefficientMaxRGB`                | `CFNumberRef (f)`  | if present in bitstream |
| `        │ ├─ kColorSyncCoefficientMinRGB`                | `CFNumberRef (f)`  | if present in bitstream |
| `        │ └─ kColorSyncCoefficientComponent`             | `CFNumberRef (f)`  | if present in bitstream |
| `        ├─ kColorSyncMaxControlPointIndex`               | `CFNumberRef (u8)` | always (2) |
| `        ├─ kColorSyncInterpolateSlopes`                  | `CFBooleanRef`     | always (2) |
| `        ├─ kColorSyncControlPointsX`                     | `CFArrayRef (f)`   | always (2) × number of points |
| `        ├─ kColorSyncControlPointsY`                     | `CFArrayRef (f)`   | always (2) × number of points |
| `        └─ kColorSyncControlPointSlopes`                 | `CFArrayRef (f)`   | if `kColorSyncInterpolateSlopes == false` (2) × number of points |

    (1) Shared across all array entries from index 0 when `kColorSyncCommonComponentMixing` is true.
    (2) Shared across all array entries from index 0 when `kColorSyncCommonCurveParameters` is true.
*/

/* ---------------------------------------------------------
    Keys for Headroom Adaptive Gain Curve Info Dictionary
   --------------------------------------------------------  */

/*  ................................. */
/*  ........ Baseline Curve ......... */
/*  ................................. */

/// Application version (uint8_t). 3-bit field from ST 2094-50 Table C.1.
/// Must be `0`; the framework rejects any other value.
CSEXTERN CFStringRef kColorSyncHeadroomAdaptiveGainCurveApplicationVersion;

/// Top-level container (CFDictionaryRef) for the color volume transform.
///
/// It may contain parameters for Headroom-Adaptive tone mapping or indicate
/// usage of the Reference-White Tone Mapping Method. It allows for specifying
/// a custom HDR Reference White luminance.
CSEXTERN CFStringRef kColorSyncHeadroomAdaptiveGainCurveColorVolumeTransform;

/// Custom reference white luminance in nits (float), overriding the standard
/// 203-nit reference white.
///
/// Must be greater than `0`. The encoding has a resolution of 0.2 nits and a
/// maximum of 10000 nits; the framework clamps values to that range.
CSEXTERN CFStringRef kColorSyncCustomHDRReferenceWhite;

/// Container (CFDictionaryRef) for Headroom-Adaptive tone mapping parameters.
///
/// Present when Headroom-Adaptive tone mapping is encoded. Contains
/// ``kColorSyncBaselineHeadroomStops`` and either
/// ``kColorSyncHeadroomAdaptiveGainCurveInfo`` or, when set to `kCFBooleanFalse`,
/// indicates the Reference-White Tone Mapping Operator (RWTMO) method.
CSEXTERN CFStringRef kColorSyncHeadroomAdaptiveToneMappingInfo;
    /// Headroom of the source (baseline) curve in stops (log2) above reference
    /// white (float in the range [0.0, 6.0]).
    CSEXTERN CFStringRef kColorSyncBaselineHeadroomStops;

    /// Container (CFDictionaryRef) for the adaptive gain curve data.
    ///
    /// Contains the alternate curve count, sharing flags, chromaticities, and
    /// the per-alternate curve info array. When set to `kCFBooleanFalse` instead
    /// of a CFDictionary, indicates the Reference-White Tone Mapping Operator (RWTMO) method.
    CSEXTERN CFStringRef kColorSyncHeadroomAdaptiveGainCurveInfo;

    /// Number of alternate (tone-mapped) curves encoded in the metadata
    /// (uint8_t in the range [0, 4]). Each alternate targets a different
    /// display headroom.
    CSEXTERN CFStringRef kColorSyncAlternateCurveCount;

    /// CFArrayRef of per-alternate dictionaries.
    ///
    /// Count equals ``kColorSyncAlternateCurveCount``. Only present when the
    /// alternate curve count is greater than 0. See the alternate curve keys below.
    CSEXTERN CFStringRef kColorSyncAlternateGainCurveInfo;

    /// Chromaticity primaries used to compute the driving signal for the gain curve.
    ///
    /// For standard primaries, pass a `CFNumberRef` (`uint8_t`): 0 = BT.709,
    /// 1 = Display P3, 2 = BT.2020. For custom primaries, pass a `CFArrayRef`
    /// of 8 `float` values encoding four xy chromaticity pairs in order R, G, B,
    /// white point; each component in [0, 1] with x + y ≤ 1. The framework rejects
    /// any numeric value other than 0, 1, or 2.
    CSEXTERN CFStringRef kColorSyncGainCurveChromaticities;

    /// CFBooleanRef indicating whether alternate curves share one component-mixing configuration.
    ///
    /// When true, all alternate curves share the component mixing configuration
    /// from array index 0, reducing bitstream size.
    CSEXTERN CFStringRef kColorSyncCommonComponentMixing;

    /// CFBooleanRef indicating whether alternate curves share common gain-curve parameters.
    ///
    /// When true, all alternate curves share the gain curve x control points and
    /// slope interpolate flag from array index 0, reducing bitstream size.
    CSEXTERN CFStringRef kColorSyncCommonCurveParameters;

/*  ................................. */
/* ....... Alternate Curves ....... */
/*  ................................. */

/// Target headroom of this alternate curve in stops (log2) above reference white
/// (float in the range [0.0, 6.0]).
/// The renderer selects the closest alternate to the actual display headroom.
CSEXTERN CFStringRef kColorSyncAlternateCurveHeadroomStops;

/// Component mixing type (uint8_t) matching `component_mixing_value` in ST 2094-50.
///
/// Determines how the framework derives the scalar driving signal from the RGB pixel:
///   - 0 = MAX(R, G, B)
///   - 1 = single component (the framework applies the gain curve to individual components)
///   - 2 = luma_A (sum of 1/6 of each color channel and 1/2 of MAX(R, G, B))
///   - 3 = free-style (custom linear combination via ``kColorSyncComponentCoefficients``)
///
/// Shared across all alternates from index 0 when ``kColorSyncCommonComponentMixing`` is true.
CSEXTERN CFStringRef kColorSyncComponentMix;

/// Sub-dictionary of custom linear-combination coefficients for free-style
/// component mixing.
///
/// Each present key contributes its value as a weight in:
/// `signal = R*red + G*green + B*blue + MAX*maxRGB + MIN*minRGB + C*component`.
/// Only present when `kColorSyncComponentMix == 3`.
CSEXTERN CFStringRef kColorSyncComponentCoefficients;
    /// Weight for the red channel in the free-style component mixing sum.
    CSEXTERN CFStringRef kColorSyncCoefficientRed;
    /// Weight for the green channel in the free-style component mixing sum.
    CSEXTERN CFStringRef kColorSyncCoefficientGreen;
    /// Weight for the blue channel in the free-style component mixing sum.
    CSEXTERN CFStringRef kColorSyncCoefficientBlue;
    /// Weight for the MAX(R,G,B) term in the free-style component mixing sum.
    CSEXTERN CFStringRef kColorSyncCoefficientMaxRGB;
    /// Weight for the MIN(R,G,B) term in the free-style component mixing sum.
    CSEXTERN CFStringRef kColorSyncCoefficientMinRGB;
    /// Weight for the 'component' term in the free-style component mixing sum.
    CSEXTERN CFStringRef kColorSyncCoefficientComponent;

/// Index of the last control point (uint8_t, 0–31), i.e. the number of control
/// points minus 1. Shared across all alternates from index 0 when
/// ``kColorSyncCommonCurveParameters`` is true.
CSEXTERN CFStringRef kColorSyncMaxControlPointIndex;

/// CFBooleanRef controlling how the framework determines control-point slopes.
///
/// When true, the framework computes slopes at control points by Piecewise Cubic Hermite
/// Interpolating Polynomial from the X,Y control point coordinates, and you must omit
/// ``kColorSyncControlPointSlopes``. When false, you must supply explicit slopes
/// in ``kColorSyncControlPointSlopes`` (see below). Shared across
/// all alternates from index 0 when ``kColorSyncCommonCurveParameters`` is true.
CSEXTERN CFStringRef kColorSyncInterpolateSlopes;

/// CFArrayRef of floats — the X-axis coordinates of the gain-curve control points.
///
/// The coordinates are normalized by the reference white, so a value of `1.0`
/// corresponds to the signal value at reference white. Shared across all
/// alternates from index 0 when ``kColorSyncCommonCurveParameters`` is true.
CSEXTERN CFStringRef kColorSyncControlPointsX;

/// CFArrayRef of floats — the Y-axis gain offsets at the control points.
///
/// Values are in stops (float in the range [0.0, 6.0]) and must be non-negative;
/// the framework infers the gain direction (expand vs. compress) from the relationship
/// between this alternate's headroom and the baseline headroom.
CSEXTERN CFStringRef kColorSyncControlPointsY;

/// CFArrayRef of floats — explicit tangent slopes at each control point, expressed
/// as tan(slope_angle). Only present when ``kColorSyncInterpolateSlopes`` is false.
CSEXTERN CFStringRef kColorSyncControlPointSlopes;

API_AVAILABLE_END

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#ifdef __cplusplus
}
#endif

#endif /* __COLORSYNCHEADROOMADAPTIVEGAINCURVE__ */
