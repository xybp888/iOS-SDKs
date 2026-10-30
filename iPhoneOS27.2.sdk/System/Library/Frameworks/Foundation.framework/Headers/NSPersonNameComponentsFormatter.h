/*	NSPersonNameComponentsFormatter.h
	Copyright (c) 2015-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/NSPersonNameComponents.h>
#import <Foundation/NSFormatter.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The formatting styles for person name components.
typedef NS_ENUM(NSInteger, NSPersonNameComponentsFormatterStyle) {
    /// The default style, determined by the formatter.
    NSPersonNameComponentsFormatterStyleDefault = 0,

    /// Relies on user preferences and language defaults to display shortened form appropriate
    /// for display in space-constrained settings, e.g. C Darwin.
    NSPersonNameComponentsFormatterStyleShort,

    /// The minimally necessary features for differentiation in a casual setting, e.g. Charles Darwin.
    NSPersonNameComponentsFormatterStyleMedium,

    /// The fully-qualified name complete with all known components, e.g. Charles Robert Darwin, FRS.
    NSPersonNameComponentsFormatterStyleLong,

    /// The maximally-abbreviated form of a name suitable for monograms, e.g. CRD.
    NSPersonNameComponentsFormatterStyleAbbreviated
} API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Options for formatting person name components.
typedef NS_OPTIONS (NSUInteger, NSPersonNameComponentsFormatterOptions) {
    /// Indicates that the formatter should format the component object's phoneticRepresentation components instead of its own components.
    NSPersonNameComponentsFormatterPhonetic = (1UL << 1)
} API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// A formatter that provides localized representations of the components of a person's name.
///
/// Each locale has its own set of rules and conventions for how personal names are structured and represented. These rules vary widely across different locales in a several ways, including the sort and display order of given and family names, the use of salutations and honorifics, and other concerns related to the grammar, spelling, punctuation, and formatting. About the only thing that _is_ consistent across all locales is that personal names are significant and meaningful. For this reason, names deserve careful and respectful treatment—perhaps more than any other kind of information your app interacts with.
///
/// Formatters can be configured to represent names in a variety of styles, which are described in detail below.
///
/// - Default (``Style/default``)
/// - Short (``Style/short``)
/// - Long (``Style/long``)
/// - Abbreviated (``Style/abbreviated``)
///
/// When determining how to represent a name in a particular style, a formatter takes a number of factors into consideration, in order of priority:
///
/// 1. **Script derived behaviors** Scripts may specify a strict sort or display order of given and family names, and the availability of styles.
/// 2. **User specified preferences** Users can enable and configure the display of short names, as well as whether or not to display nicknames when available. Users can also override the default sort and display order of given and family names for their current locale.
/// 3. **Locale derived defaults** Locales specify a default sort and display order for given and family names.
/// 4. **Developer specified configuration** The style property value set for the `NSPersonNameComponentsFormatter` object.
///
///
/// When the behavior specified in one factor conflicts with any other factors, the behavior specified by the factor with the most precedence is used. For example, the U.S. English (`en-US`) locale specifies that names be displayed in "given name followed by the family name" (for example,"John Appleseed"). This behavior would be overridden if the user changed their system preferences to have names displayed as family name followed by given name (for example, "Appleseed, John"), because user-specified preferences take precedence over locale-derived defaults. Furthermore, if the name to be formatted were Japanese (for example, given name: "泰夫", family name: "木田"), the behavior derived for the name's script (CJK, for Chinese, Japanese, and Korean languages) would take precedence over any locale-derived defaults or user-specified preferences to have the name displayed as family name followed by given name (for example, "木田 泰夫").
///
/// These considerations extend to the availability of certain formatter styles as well. Because developer-specified configurations have the lowest precedence in determining behavior, the value set for the formatter's style property can be invalidated if it's not supported for the locale, user preferences, or script. If the specified style is not available, the next longest valid style is used. For example, a name in Arabic script (for example, "أحمد الراجحي") does not support the Abbreviated style, so the Short style is used instead. A name that contains more than one script (for example, given name: "John", family name: "王") is detected to have "Unknown" script, which has its own set of behaviors and characteristics.
///
/// > Tip:
/// > In Swift, you can use ``PersonNameComponents/FormatStyle`` rather than ``PersonNameComponentsFormatter``. The ``FormatStyle`` API offers a declarative idiom for customizing the formatting of various types. Also, Foundation caches identical ``FormatStyle`` instances, so you don't need to pass them around your app, or risk wasting memory with duplicate formatters.
///
///
///
/// ### Styles
///
/// `NSPersonNameComponentsFormatter` can be configured to format names in the following styles:
///
/// - term ``Style/default``: The minimally necessary features for differentiation in a casual setting. Equivalent to ``Style/medium``.
/// - term ``Style/short``: Relies on user preferences and language defaults to display shortened form appropriate for display in space-constrained settings.
/// - term ``Style/long``: The fully qualified name complete with all known components.
/// - term ``Style/abbreviated``: The maximally abbreviated form of a name.
///
///
/// |  | `namePrefix` | `givenName` | `middleName` | `familyName` | `nameSuffix` | `nickname` |
/// |---|---|---|---|---|---|---|
/// | Arabic ![](spacer) `(ar-SA)` | .د | أحمد |  | محمدالمصري |  |  |
/// | Chinese ![](spacer) `(zh-Hans)` | 物理学博士 | 振宁 |  | 杨 | 先生 |  |
/// | English ![](spacer) `(en-US)` | Dr. | Jonathan | Maple | Appleseed | Esq. | Johnny |
/// | French ![](spacer) `(fr-FR)` | Père | Jean-Philippe |  | de Zélicourt |  | JP |
/// | German ![](spacer) `(de-DE)` | Dr. med. | Max |  | Mustermann | junior, M.A. |  |
/// | Hindi ![](spacer) `(hi-IN)` | डॉ. | रिय |  | साहिल |  |  |
/// | Japanese ![](spacer) `(ja-JP)` |  | 泰夫 |  | 木田 | 先生 |  |
/// | Spanish ![](spacer) `(es-ES)` | Dr. | José Ramiro |  | Martín González de Rivera | júnior, PhD | Ramiro |
/// | Thai ![](spacer) `(th-TH)` | ฯพณฯ | สมชาย | ปีเตอร์ | รัตนเรืองรองบวรทิพย์ |  |  |
///
///
/// #### Default
///
/// The Default, or Medium, style presents names in a way that is suitable for most contexts. It uses the given and family names, as well as a nickname, if provided and enabled by the user in System Preferences.
///
///
/// |  | Default style |
/// |---|---|
/// | Arabic (ar-SA) | أحمد محمﺩﺍلمصﺭﻱ |
/// | Chinese (zh-Hans) | 杨振宁 |
/// | English (en-US) | Jonathan Appleseed |
/// | French (fr-FR) | Jean-Philippe de Zélicourt |
/// | German (de-DE) | Max Mustermann |
/// | Hindi (hi-IN) | रिय साहिल |
/// | Japanese (ja-JP) | 木田泰夫 |
/// | Spanish (es-ES) | José Ramiro Martín González de Rivera |
/// | Thai (th-TH) | สมชาย รัตนเรืองรอง บวรทิพย์ |
///
///
/// #### Short
///
/// The Short style offers an alternative display method for names whose default representation may exceed a certain length constraint. It is only available if the user has enabled "Short Names" in System Preferences, and only for names with a script that supports Short style. Otherwise, a formatter configured to display with Short style is displayed with Medium style instead.
///
/// If a user has enabled the use of short names, the user can choose from one of four variations:
///
/// - Given Name - Family Initial
/// - Family Name - Given Initial
/// - Given Name Only
/// - Family Name Only
///
/// Short style is not available for names in CJK script and is restricted to Given Name Only or Family Name Only for names in Arabic or Devanagari script. If the specified Short style is unavailable, the Medium style is used instead.
///
///
/// |  | Given Name - Family Initial | Family Name - Given Initial | Given Name Only | Family Name Only |
/// |---|---|---|---|---|
/// | Arabic (ar-SA) | _N/A_ | _N/A_ | أحمد | محمﺩﺍلمصﺭﻱ |
/// | Chinese (zh-Hans) | _N/A_ | _N/A_ | _N/A_ | _N/A_ |
/// | English (en-US) | Jonathan A | J Appleseed | Jonathan | Appleseed |
/// | French (fr-FR) | Jean-Philippe d | J de Zélicourt | Jean-Philippe | de Zélicourt |
/// | German (de-DE) | Max M | M Mustermann | Max | Mustermann |
/// | Hindi (hi-IN) | _N/A_ | _N/A_ | रिय | साहिल |
/// | Japanese (ja-JP) | _N/A_ | _N/A_ | _N/A_ | _N/A_ |
/// | Spanish (es-ES) | José Ramiro M | J Martín González de Rivera | José Ramiro | Martín González de Rivera |
/// | Thai (th-TH) | สมชาย ร | ส รัตนเรืองรองบวรทิพย์ | สมชาย | รัตนเรืองรองบวรทิพย์ |
///
///
/// > Important:
/// > `NSPersonNameComponentsFormatter` does not currently account for prepositional particles. Representations using the Short style that specify a family name initial naively use the first letter unit of the particle as the initial.
///
/// #### Long
///
/// The Long style provides the most explicit representation of names. It uses all available name components, with the exception of nickname.
///
///
/// |  | Long style |
/// |---|---|
/// | Arabic (ar-SA) | ﺩ. أحمد محمﺩﺍلمصﺭﻱ |
/// | Chinese (zh-Hans) | 物理学博士杨振宁先生 |
/// | English (en-US) | Dr. Jonathan Maple Appleseed Esq. |
/// | French (fr-FR) | Père Jean-Philippe de Zélicourt |
/// | German (de-DE) | Dr. med. Max Mustermann junior, M.A. |
/// | Hindi (hi-IN) | डॉ. रिय साहिल |
/// | Japanese (ja-JP) | 木田泰夫先生 |
/// | Spanish (es-ES) | Dr. José Ramiro Martín González de Rivera júnior, PhD |
/// | Thai (th-TH) | ฯพณฯ สมชาย ปีเตอร์ รัตนเรืองรอง บวรทิพย์ |
///
///
/// #### Abbreviated
///
/// The Abbreviated style offers the most compact representation of names, similar to a monogram.
///
/// Abbreviated style is supported for names in several scripts, with the following general characteristics:
///
/// - For names in Cyrillic, Greek, or Latin script, the first characters of `givenName`, `middleName`, and `familyName` may be used.
/// - For names in Chinese or Japanese script, `familyName` may be used. If `familyName` is too long, or if the family name is `nil`, the Short or Medium style may be used instead.
/// - For names in Korean script, `givenName` may be used. If `givenName` is too long, the first character of `givenName` may be used. If `givenName` is `nil`, the `familyName` may be used instead.
/// - For names in Bengali, Devanagari, Gujarati, Gurmukhi, Kannada, Malayalam, Oriya, Sinhala, Tamil, Telugu, Tibetan, or Thai script, the first character of `givenName` may be used. If `givenName` is `nil`, the first character of `familyName` may be used instead.
/// - For names that contain more than one script, the abbreviated style may use the `familyName`, `givenName`, or the first characters of `givenName` and/or `familyName`.
///
/// If the Abbreviated style is unavailable, the Short style is used instead—unless that too is unsupported, in which case the Medium style is used instead.
///
///
/// |  | Abbreviated style |
/// |---|---|
/// | Arabic (ar-SA) | _N/A_ |
/// | Chinese (zh-Hans) | 杨 |
/// | English (en-US) | JMA |
/// | French (fr-FR) | Jd |
/// | German (de-DE) | MM |
/// | Hindi (hi-IN) | मि |
/// | Japanese (ja-JP) | 木田 |
/// | Spanish (es-ES) | JM |
/// | Thai (th-TH) | ส |
///
///
/// > Important:
/// > `NSPersonNameComponentsFormatter` doesn't currently account for prepositional particles or compound names. Representations using the Abbreviated style uses the first letter unit of each name component, regardless.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface NSPersonNameComponentsFormatter : NSFormatter {
@private
    id _private;
}

/// The formatting style for the formatted string on an instance.
///
/// `ShortStyle` will fall back to user preferences and language-specific defaults.
@property NSPersonNameComponentsFormatterStyle style;

/// Specify that the formatter should only format the components object's phoneticRepresentation.
@property (getter=isPhonetic) BOOL phonetic;


/// Specifies the locale to format names.
///
/// Defaults to `autoupdatingCurrentLocale`. Also resets to `autoupdatingCurrentLocale` on assignment of `nil`.
@property (null_resettable, copy) NSLocale *locale API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// Returns a formatted string from the given person name components using the specified style and options.
///
/// Shortcut for converting an `NSPersonNameComponents` object into a string without explicitly creating an instance. Create an instance for greater customizability.
+ (NSString *)localizedStringFromPersonNameComponents:(NSPersonNameComponents *)components
                                                style:(NSPersonNameComponentsFormatterStyle)nameFormatStyle
                                              options:(NSPersonNameComponentsFormatterOptions)nameOptions;

/// Returns a string containing the formatted value of the provided components object.
- (NSString *)stringFromPersonNameComponents:(NSPersonNameComponents *)components;

/// Returns an attributed string with annotations for each component.
///
/// For each range, attributes can be obtained by querying dictionary key `NSPersonNameComponentKey`, using `NSPersonNameComponent` constant values.
- (NSAttributedString *)annotatedStringFromPersonNameComponents:(NSPersonNameComponents *)components;


/// Returns an `NSPersonNameComponents` object representing the name components found in the provided string.
- (nullable NSPersonNameComponents *)personNameComponentsFromString:(nonnull NSString *)string API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// Returns by reference an object after creating it from a string.
- (BOOL)getObjectValue:(out id _Nullable * _Nullable)obj forString:(NSString *)string errorDescription:(out NSString * _Nullable * _Nullable)error;

@end

/// The attributed string key used to identify person name components.
FOUNDATION_EXPORT NSString * const NSPersonNameComponentKey API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// The given name component of a person's name.
FOUNDATION_EXPORT NSString * const NSPersonNameComponentGivenName API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// The family name component of a person's name.
FOUNDATION_EXPORT NSString * const NSPersonNameComponentFamilyName API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// The middle name component of a person's name.
FOUNDATION_EXPORT NSString * const NSPersonNameComponentMiddleName API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// The name prefix component of a person's name.
FOUNDATION_EXPORT NSString * const NSPersonNameComponentPrefix API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// The name suffix component of a person's name.
FOUNDATION_EXPORT NSString * const NSPersonNameComponentSuffix API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// The nickname component of a person's name.
FOUNDATION_EXPORT NSString * const NSPersonNameComponentNickname API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// The delimiter is the character or characters used to separate name components.
///
/// For CJK languages there is no delimiter.
FOUNDATION_EXPORT NSString * const NSPersonNameComponentDelimiter API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

NS_HEADER_AUDIT_END(nullability, sendability)
