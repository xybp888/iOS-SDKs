//
//  CGPDFStructureElement.h
//  CoreGraphics
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef CGPDFStructureElement_h
#define CGPDFStructureElement_h

#include <CoreFoundation/CFBase.h>
#include <CoreGraphics/CGPDFContext.h>

typedef struct CF_BRIDGED_TYPE(id) CGPDFStructureElement* CGPDFStructureElementRef
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

#include <CoreFoundation/CFString.h>
#include <CoreGraphics/CGPDFMarkedContentItem.h>

CF_ASSUME_NONNULL_BEGIN

CG_EXTERN CGPDFStructureElementRef CGPDFStructureElementCreate(CGPDFTagType type) CF_RETURNS_RETAINED
    CF_SWIFT_NAME(CGPDFStructureElement.init(tagType:))
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

/* Standard CoreFoundation-style retain/release for C clients, balanced against the
   +1 references returned by CGPDFStructureElementCreate and the CGPDFContext
   marked-content functions. NULL-safe. Refined away in Swift, where ARC manages
   lifetimes. */

CG_EXTERN CGPDFStructureElementRef cg_nullable CGPDFStructureElementRetain(CGPDFStructureElementRef cg_nullable structureElemnt)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

CG_EXTERN void CGPDFStructureElementRelease(CGPDFStructureElementRef cg_nullable structureElemnt)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

/* Structure Element Attributes */

/* The attribute setters are refined out of the Swift surface; the overlay
   applies them from a `CGPDFStructureElement.Attributes` value at creation. */

CG_EXTERN void CGPDFStructureElementSetTitle(CGPDFStructureElementRef structureElement, CFStringRef title)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

CG_EXTERN void CGPDFStructureElementSetLanguageIdentifier(CGPDFStructureElementRef structureElement, CFStringRef languageID)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

CG_EXTERN void CGPDFStructureElementSetAlternativeText(CGPDFStructureElementRef structureElement, CFStringRef alternativeText)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

CG_EXTERN void CGPDFStructureElementSetExpansionText(CGPDFStructureElementRef structureElement, CFStringRef expansionText)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

CG_EXTERN void CGPDFStructureElementSetActualText(CGPDFStructureElementRef structureElement, CFStringRef actualText)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

/* Children */

CG_EXTERN OSStatus CGPDFStructureElementAddStructureElement(CGPDFStructureElementRef structureElement, CGPDFStructureElementRef childStructureElement)
    CF_SWIFT_NAME(CGPDFStructureElement.addChild(self:_:))
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

CG_EXTERN OSStatus CGPDFStructureElementAddMarkedContentItem(CGPDFStructureElementRef structureElement, CGPDFMarkedContentItemRef markedContentItem)
    CF_SWIFT_NAME(CGPDFStructureElement.addMarkedContentItem(self:_:))
    API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
    API_UNAVAILABLE(watchos, tvos);

CF_ASSUME_NONNULL_END

#endif /* CGPDFStructureElement_h */
