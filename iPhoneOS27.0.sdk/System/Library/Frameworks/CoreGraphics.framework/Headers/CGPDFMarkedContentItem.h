//
//  CGPDFMarkedContentItem.h
//  CoreGraphics
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef CGPDFMarkedContentItem_h
#define CGPDFMarkedContentItem_h

#include <CoreFoundation/CFBase.h>

/* CGPDFMarkedContentItemRef represents the link between a piece of drawn content and
   its place in the PDF structure tree. */

typedef struct CF_BRIDGED_TYPE(id) CGPDFMarkedContentItem* CGPDFMarkedContentItemRef
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

#include <CoreGraphics/CGBase.h>

CF_ASSUME_NONNULL_BEGIN

CG_EXTERN CGPDFMarkedContentItemRef cg_nullable CGPDFMarkedContentItemRetain(CGPDFMarkedContentItemRef cg_nullable markedContentItem)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

CG_EXTERN void CGPDFMarkedContentItemRelease(CGPDFMarkedContentItemRef cg_nullable markedContentItem)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

CF_ASSUME_NONNULL_END


#endif /* CGPDFMarkedContentItem_h */
