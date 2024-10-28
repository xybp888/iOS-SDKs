/* CoreGraphics - CGToneMapping.h
   Copyright (c) 2000-2012 Apple Inc.
   All rights reserved. */

#ifndef CGTONEMAPPING_H_
#define CGTONEMAPPING_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>


#include <CoreGraphics/CGBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

typedef CF_ENUM (uint32_t, CGToneMapping) {
  kCGToneMappingDefault = 0,              /* A system default method will be used */
  kCGToneMappingImageSpecificLumaScaling, /* Implements tone mapping of HDR content associated with the CGImage gain map */
  kCGToneMappingReferenceWhiteBased,      /* Implements a tone curve that preserves SDR contrast and rolls off HDR highlights */
  kCGToneMappingITURecommended,           /* Implements tone mapping based on ITU-R specifications for HDR-to-SDR and SDR-to-HDR conversions assuming mastering peak of 1000 nits */
  kCGToneMappingEXRGamma,                 /* Implements Open EXR tone mapping gamma suitable for tone mapping images in extended linear sRGB color space to SDR */
  kCGToneMappingNone                      /* Does not apply any tone mapping. Color converted values in extended color spaces will be clipped to SDR ([0.0-1.0]) range */
} API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

/* kCGUse100nitsHLGOOTF allows for using HLG OOTF targeting 100 nits when converting HLG to SDR when applying kCGColorITURecommended tone mapping method */
CG_EXTERN const CFStringRef kCGUse100nitsHLGOOTF API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));     /* The expected value is a CFBooleanRef (kCFBooleanTrue) */

/* kCGUseBT1886ForCoreVideoGamma allows for choosing BT1886 recommended gamma in lieu of CoreVideo Gamma. */
CG_EXTERN const CFStringRef kCGUseBT1886ForCoreVideoGamma API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));     /* The expected value is a CFBooleanRef (kCFBooleanTrue) */

/* kCGSkipBoostToHDR allows for skipping linear boost when converting non-HDR content (either SDR or extended range) to HDR when applying kCGColorITURecommended tone mapping method */
CG_EXTERN const CFStringRef kCGSkipBoostToHDR API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));     /* The expected value is a CFBooleanRef (kCFBooleanTrue) */

/* kCGUseLegacyHDREcosystem allows for choosing legacy HDR conversion functions implemented in previous versions of the OS when applying kCGColorITURecommended tone mapping method */
CG_EXTERN const CFStringRef kCGUseLegacyHDREcosystem API_AVAILABLE(macos(15.1), ios(18.1), tvos(18.1), watchos(11.1));     /* The expected value is a CFBooleanRef (kCFBooleanTrue) */

/* kCGEXRToneMappingGammaDefog allows for specifying custom defog value to override system defaults when applying kCGToneMappingEXRGamma tone mapping method */
CG_EXTERN const CFStringRef kCGEXRToneMappingGammaDefog    API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0)); /* default value: 0.0f range [0.0f, 0.01f]   */

/* kCGEXRToneMappingGammaExposure allows for specifying custom exposure value to override system defaults when applying kCGToneMappingEXRGamma tone mapping method */
CG_EXTERN const CFStringRef kCGEXRToneMappingGammaExposure API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0)); /* default value: 0.0f range [-10.0f, 10.0f] */

/* kCGEXRToneMappingGammaKneeLow allows for specifying custom "knee low" value to override system defaults when applying kCGToneMappingEXRGamma tone mapping method */
CG_EXTERN const CFStringRef kCGEXRToneMappingGammaKneeLow  API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0)); /* default value: 0.0f range [-2.85f, 3.0f]  */

/* kCGEXRToneMappingGammaKneeHigh allows for specifying custom "knee high" value to override system defaults when applying kCGToneMappingEXRGamma tone mapping method */
CG_EXTERN const CFStringRef kCGEXRToneMappingGammaKneeHigh API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0)); /* default value: 5.0f range [3.5f, 7.5f]    */


CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGTONEMAPPING_H_ */
