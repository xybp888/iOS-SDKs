/* CoreGraphics - CGColorConversionInfo.h
   Copyright (c) 2016 Apple Inc.
   All rights reserved. */

#ifndef CGCOLORCONVERSIONINFO_H_
#define CGCOLORCONVERSIONINFO_H_

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <CoreGraphics/CGColorSpace.h>

typedef const struct CF_BRIDGED_TYPE(id) CGColorConversionInfo* CGColorConversionInfoRef;

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

CG_EXTERN CFTypeID CGColorConversionInfoGetTypeID(void);

typedef CF_ENUM (uint32_t, CGColorConversionInfoTransformType) {
  kCGColorConversionTransformFromSpace = 0,
  kCGColorConversionTransformToSpace,
  kCGColorConversionTransformApplySpace
};

/* Create CGColorConversionInfoRef for converting color from `src' color space to `dst' color space
 * using kCGRenderingIntentDefault rendering intent.
 * Requirements: CG color spaces must be calibrated (no Device{Gray,RGB,CMYK}, Indexed or DeviceN are allowed).
 */

CG_EXTERN CGColorConversionInfoRef __nullable CGColorConversionInfoCreate(cg_nullable CGColorSpaceRef src, cg_nullable CGColorSpaceRef dst)
    API_AVAILABLE(macos(10.12), ios(10.0));

CG_EXTERN CGColorConversionInfoRef __nullable CGColorConversionInfoCreateWithOptions(__nonnull CGColorSpaceRef src, __nonnull CGColorSpaceRef dst, CFDictionaryRef __nullable options)
API_AVAILABLE(macos(10.14.6), ios(13));

/* Create CGColorConversionInfoRef from a list of CG color spaces, transform types and rendering intents.
 * ColorSpaces are iterated from first to last. The list of triples:
 * {CGColorSpaceRef, CGColorConversionInfoTransformType, CGColorRenderingIntent} must be terminated with NULL
 * Requirements: CG color spaces must be calibrated (no Device{Gray,RGB,CMYK}, Indexed or DeviceN are allowed).
 */

CG_EXTERN CGColorConversionInfoRef __nullable CGColorConversionInfoCreateFromList
  (CFDictionaryRef __nullable options, cg_nullable CGColorSpaceRef, CGColorConversionInfoTransformType, CGColorRenderingIntent, ...)
  API_AVAILABLE(macos(10.12), ios(10.0));

CG_EXTERN CGColorConversionInfoRef __nullable CGColorConversionInfoCreateFromListWithArguments
  (CFDictionaryRef __nullable options, cg_nullable CGColorSpaceRef, CGColorConversionInfoTransformType, CGColorRenderingIntent, va_list)
  API_AVAILABLE(macos(10.13), ios(11.0));

/* CFBooleanRef's which can be used as options to create CGColorConversionInfoRef */
CG_EXTERN const CFStringRef kCGColorConversionBlackPointCompensation API_AVAILABLE(macos(10.12), ios(10.0));

CG_EXTERN const CFStringRef kCGColorConversionTRCSize API_AVAILABLE(macos(10.13), ios(11.0));

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCOLORCONVERSIONINFO_H_ */
