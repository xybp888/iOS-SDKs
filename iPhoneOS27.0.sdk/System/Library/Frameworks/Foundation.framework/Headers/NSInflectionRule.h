/*    NSMorphology.h
      Copyright (c) 2021, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>

@class NSMorphology;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A rule that affects how an attributed string performs automatic grammatical agreement.
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
NS_REFINED_FOR_SWIFT
@interface NSInflectionRule: NSObject <NSCopying, NSSecureCoding>

- (id)init NS_UNAVAILABLE; // This class is abstract. Use +automaticRule, or instantiate a subclass instead.

/// Returns a rule that performs automatic grammar agreement based on the system's current locale and language settings.
@property (class, readonly) NSInflectionRule *automaticRule;

@end

/// An inflection rule that uses a morphology instance to determine how to inflect attributed strings.
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
NS_REFINED_FOR_SWIFT
@interface NSInflectionRuleExplicit: NSInflectionRule

/// Initializes the inflection rule with the specified morphology.
- (instancetype)initWithMorphology:(NSMorphology *)morphology NS_DESIGNATED_INITIALIZER;

/// The morphology used by the receiver.
@property (readonly, copy) NSMorphology *morphology;

@end

// -----

@interface NSInflectionRule (NSInflectionAvailability)

/// Returns a Boolean value that indicates whether inflection will work in the specified language code.
+ (BOOL)canInflectLanguage:(NSString *)language
 API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// A Boolean value that indicates whether inflection will work in the language of the main bundle's first preferred localization.
@property (class, readonly) BOOL canInflectPreferredLocalization
 API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));
 
@end

NS_HEADER_AUDIT_END(nullability, sendability)
