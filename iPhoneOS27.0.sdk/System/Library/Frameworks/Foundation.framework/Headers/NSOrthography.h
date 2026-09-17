/*	NSOrthography.h
	Copyright (c) 2008-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A description of the linguistic content of natural language text, typically used for spelling and grammar checking.
///
/// Use ``NSOrthography`` objects to describe the linguistic content of a piece of text, including which scripts the text contains, a dominant language (and possibly other languages) for each script, and a dominant script and language for the text as a whole.
///
/// Scripts are uniformly described by four-letter ISO 15924 script codes, such as `"Latn"`, `"Grek"`, and `"Cyrl"`. The supertags `"Jpan"` and `"Kore"` are typically used for Japanese and Korean text, and `"Hans"` and `"Hant"` are typically used for Chinese text. The tag `"Zyyy"` is used if a specific script cannot be identified. See [Internationalization and Localization Guide](https://developer.apple.com/library/archive/documentation/MacOSX/Conceptual/BPInternational/Introduction/Introduction.html#//apple_ref/doc/uid/10000171i) for more information.
///
/// Languages are uniformly described by BCP-47 tags (preferably in canonical form). The tag `"und"` is used if a specific language cannot be determined.
///
/// You typically work with orthography objects returned from methods and properties for classes like ``NSLinguisticTagger`` and <doc://com.apple.documentation/documentation/appkit/nsspellchecker>.
///
/// ### Subclassing Notes
///
/// Subclasses must override the ``dominantScript`` and ``languageMap`` properties. These properties are set using ``init(dominantScript:languageMap:)`` or ``orthographyWithDominantScript:languageMap:`` in Objective-C.
API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0))
@interface NSOrthography : NSObject <NSCopying, NSSecureCoding>

/// The dominant script for the text.
///
/// The value of this property is an ISO 15924 script code, such as `"Latn"` or `"Cyrl"`, that identifies the dominant script.
@property (readonly, copy) NSString *dominantScript;
/// A dictionary that maps script tags to arrays of language tags.
///
/// The dictionary's keys are ISO 15924 script codes (such as `"Latn"` or `"Cyrl"`) and its values are arrays of BCP-47 language tags (such as `"en"`, `"fr"`, or `"de"`).
@property (readonly, copy) NSDictionary<NSString *, NSArray<NSString *> *> *languageMap;
/// Creates an orthography object with the specified dominant script and language map.
///
/// You typically use the `defaultOrthographyForLanguage:` method to create orthography objects with automatic language mapping. Use this initializer only if you need to override the script associated with one or more languages.
///
/// - Parameter script: The dominant script.
/// - Parameter map: A dictionary mapping ISO 15924 script codes to arrays of BCP-47 language tags.
- (instancetype)initWithDominantScript:(NSString *)script languageMap:(NSDictionary<NSString *, NSArray<NSString *> *> *)map API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSOrthography (NSOrthographyExtended)

/// Returns the list of languages for the specified script.
///
/// - Parameter script: The specified script.
- (nullable NSArray<NSString *> *)languagesForScript:(NSString *)script API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns the dominant language for the specified script.
///
/// - Parameter script: The specified script.
- (nullable NSString *)dominantLanguageForScript:(NSString *)script API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The first language in the list of languages for the dominant script.
@property (readonly, copy) NSString *dominantLanguage API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The scripts appearing as keys in the language map.
@property (readonly, copy) NSArray<NSString *> *allScripts API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The languages appearing in values of the language map.
@property (readonly, copy) NSArray<NSString *> *allLanguages API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Creates and returns an orthography object with the default language map for the specified language.
///
/// This method automatically determines the script for the specified language.
///
/// - Parameter language: A BCP-47 tag identifying the language.
+ (instancetype)defaultOrthographyForLanguage:(NSString *)language API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0), tvos(11.0));

@end

@interface NSOrthography (NSOrthographyCreation)

/// Creates and returns an orthography object with the specified dominant script and language map.
///
/// - Parameter script: The dominant script.
/// - Parameter map: A dictionary mapping ISO 15924 script codes to arrays of BCP-47 language tags.
+ (instancetype)orthographyWithDominantScript:(NSString *)script languageMap:(NSDictionary<NSString *, NSArray<NSString *> *> *)map API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
