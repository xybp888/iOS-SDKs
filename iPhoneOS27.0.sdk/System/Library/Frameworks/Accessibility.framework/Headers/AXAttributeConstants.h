//
//  AXAttributeConstants.h
//  Accessibility
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Accessibility/AXFoundation.h>

#if defined(__OBJC__)

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Annotate a range of an accessibility NSAttributedString with a
 Speech Synthesis Markup Language (SSML) fragment that describes how that range
 should be spoken.

 @discussion
 The value is an NSString containing an SSML fragment, as defined by the W3C
 Speech Synthesis Markup Language (SSML) Version 1.1 specification. Assistive
 technologies that produce speech, such as VoiceOver and Spoken Content, use the
 fragment to determine how to pronounce the annotated range, enabling control
 over pronunciation, inline language switching, pacing, emphasis, and say-as
 interpretations.

 The SSML fragment is scoped to the attribute's range; you do not need to wrap
 it in a top-level <speak> element. The text spoken for the range is derived
 from the SSML fragment, not from the underlying characters, so the visible and
 Braille-rendered text remain unchanged. Assistive technologies that do not
 produce speech ignore this attribute and use the underlying string.

 If the value is not well-formed SSML, the attribute is ignored for that range
 and the underlying string is spoken normally.

 This attribute can be applied to any accessibility attributed-string field,
 including accessibilityAttributedLabel, accessibilityAttributedValue,
 accessibilityAttributedHint, and attributed announcement strings.

 When AXSpeechAttributeSSML is present on a range, it takes precedence over
 the older, single-purpose speech attributes (IPA notation, spell out, pitch,
 punctuation, language) for that range.

 Use an NSString containing an SSML fragment.
*/
AX_EXTERN NSAttributedStringKey const AXSpeechAttributeSSML API_AVAILABLE(anyappleos(27.0));

NS_ASSUME_NONNULL_END

#endif
