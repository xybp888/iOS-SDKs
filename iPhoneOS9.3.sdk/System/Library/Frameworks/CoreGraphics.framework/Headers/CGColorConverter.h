/* CoreGraphics - CGColorConverter.h
   Copyright (c) 2015 Apple Inc.
   All rights reserved. */

#ifndef CGCOLORCONVERTER_H_
#define CGCOLORCONVERTER_H_

#include <CoreFoundation/CFAvailability.h>
#include <CoreGraphics/CGColorSpace.h>

typedef const struct CGColorConverter* CGColorConverterRef;

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

CG_EXTERN CFTypeID CGColorConverterGetTypeID(void);

typedef CF_ENUM (uint32_t, CGColorConverterTransformType) {
  kCGColorConverterTransformFromSpace = 0,
  kCGColorConverterTransformToSpace,
  kCGColorConverterTransformApplySpace
};


/* Create CGColorConverterRef from a list of CG color spaces, transform types and rendering intents.
 * ColorSpaces are iterated from first to last. The list of triples:
 * {CGColorSpaceRef, CGColorConverterTransformType, CGColorRenderingIntent} needs to be terminated with NULL
 * Requirements: CG color spaces must be calibrated (no Device{Gray,RGB,CMYK}, Indexed or DeviceN).
 */
CG_EXTERN CGColorConverterRef __nullable CGColorConverterCreate
  (CFDictionaryRef __nullable options, __nullable CGColorSpaceRef, CGColorConverterTransformType, CGColorRenderingIntent, ...);

CG_EXTERN CGColorConverterRef __nullable CGColorConverterCreateSimple(__nullable CGColorSpaceRef from, __nullable CGColorSpaceRef to);

CG_EXTERN void CGColorConverterRelease(CGColorConverterRef __nullable);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCOLORCONVERTER_H_ */
