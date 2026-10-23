/*	NSTextCheckingResult.h
	Copyright (c) 2008-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSDate.h>

@class NSString, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSDate, NSTimeZone, NSOrthography, NSURL, NSRegularExpression;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// These constants specify the type of checking the methods should do.
///
/// They are returned by ``NSTextCheckingResult/resultType``.
/* NSTextCheckingResult is a class used to describe items located by text checking.  Each of these objects represents something that has been found during checking--a misspelled word, a sentence with grammatical issues, a detected URL, a straight quote to be replaced with curly quotes, and so forth. */

typedef NS_OPTIONS(uint64_t, NSTextCheckingType) {    // a single type
    /// Language identification.
    NSTextCheckingTypeOrthography           = 1ULL << 0,            // language identification
    /// Spell checking.
    NSTextCheckingTypeSpelling              = 1ULL << 1,            // spell checking
    /// Grammar checking.
    NSTextCheckingTypeGrammar               = 1ULL << 2,            // grammar checking
    /// Date and time detection.
    NSTextCheckingTypeDate                  = 1ULL << 3,            // date/time detection
    /// Address detection.
    NSTextCheckingTypeAddress               = 1ULL << 4,            // address detection
    /// Link detection.
    NSTextCheckingTypeLink                  = 1ULL << 5,            // link detection
    /// Smart quotes.
    NSTextCheckingTypeQuote                 = 1ULL << 6,            // smart quotes
    /// Smart dashes.
    NSTextCheckingTypeDash                  = 1ULL << 7,            // smart dashes
    /// Fixed replacements, such as copyright symbol for (c).
    NSTextCheckingTypeReplacement           = 1ULL << 8,            // fixed replacements, such as copyright symbol for (c)
    /// Autocorrection.
    NSTextCheckingTypeCorrection            = 1ULL << 9,            // autocorrection
    /// Regular expression matches.
    NSTextCheckingTypeRegularExpression API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0))  = 1ULL << 10,           // regular expression matches
    /// Phone number detection.
    NSTextCheckingTypePhoneNumber API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0))        = 1ULL << 11,           // phone number detection
    /// Transit (e.g. flight) info detection.
    NSTextCheckingTypeTransitInformation API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0)) = 1ULL << 12            // transit (e.g. flight) info detection
};

typedef uint64_t NSTextCheckingTypes;   // a combination of types
NS_ENUM(NSTextCheckingTypes) {
    /// All system checking types; the first 32 types are reserved.
    NSTextCheckingAllSystemTypes    = 0xffffffffULL,
    /// All custom checking types; clients may use the remainder for their own purposes.
    NSTextCheckingAllCustomTypes    = 0xffffffffULL << 32,
    /// All possible checking types, both system- and user-supported.
    NSTextCheckingAllTypes          = (NSTextCheckingAllSystemTypes | NSTextCheckingAllCustomTypes)
};

typedef NSString *NSTextCheckingKey NS_TYPED_EXTENSIBLE_ENUM;

/// An occurrence of textual content found during the analysis of a block of text, such as when matching a regular expression.
///
/// On both iOS and macOS, instances of ``NSTextCheckingResult`` are returned by the ``NSRegularExpression`` class and the ``NSDataDetector`` class to indicate the discovery of content. In those cases, what is found may be a match for a regular expression or a date, address, phone number, and so on. In macOS, instances of `NSTextCheckingResult` are returned by the <doc://com.apple.documentation/documentation/appkit/nsspellchecker> object to describe the results of spelling, grammar, or text-substitution actions.
API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0))
@interface NSTextCheckingResult : NSObject <NSCopying, NSSecureCoding>

/* Mandatory properties, used with all types of results. */
/// Returns the text checking result type that the receiver represents.
@property (readonly) NSTextCheckingType resultType;
/// Returns the range of the result that the receiver represents.
@property (readonly) NSRange range;

@end

@interface NSTextCheckingResult (NSTextCheckingResultOptional)

/* Optional properties, used with certain types of results. */
/// The detected orthography of a type checking result.
@property (nullable, readonly, copy) NSOrthography *orthography;
/// The details of a grammar checking result.
@property (nullable, readonly, copy) NSArray<NSDictionary<NSString *, id> *> *grammarDetails;
/// The date component of a type checking result.
@property (nullable, readonly, copy) NSDate *date;
/// The time zone component of a type checking result.
@property (nullable, readonly, copy) NSTimeZone *timeZone;
/// The duration component of a type checking result.
@property (readonly) NSTimeInterval duration;
/// The components of a type checking result.
@property (nullable, readonly, copy) NSDictionary<NSTextCheckingKey, NSString *> *components API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
/// The URL component of a type checking result.
@property (nullable, readonly, copy) NSURL *URL;
/// The replacement string of a type checking result.
@property (nullable, readonly, copy) NSString *replacementString;
@property (nullable, readonly, copy) NSArray<NSString *> *alternativeStrings API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
/// The regular expression of a type checking result.
@property (nullable, readonly, copy) NSRegularExpression *regularExpression API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
/// The phone number of a type checking result.
@property (nullable, readonly, copy) NSString *phoneNumber API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));


/* A result must have at least one range, but may optionally have more (for example, to represent regular expression capture groups).  The range at index 0 always matches the range property.  Additional ranges, if any, will have indexes from 1 to numberOfRanges-1. rangeWithName: can be used with named regular expression capture groups. */
/// Returns the number of ranges.
///
/// A result must have at least one range, but may optionally have more (for example, to represent regular expression capture groups).
@property (readonly) NSUInteger numberOfRanges API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns the range at the specified index.
///
/// Passing a value of `0` always returns the value of the `range` property. Additional ranges, if any, will have indexes from `1` to `numberOfRanges-1`.
- (NSRange)rangeAtIndex:(NSUInteger)idx API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
- (NSRange)rangeWithName:(NSString *)name API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0), tvos(11.0));
/// Returns a new text checking result after adjusting the ranges as specified by the offset.
- (NSTextCheckingResult *)resultByAdjustingRangesWithOffset:(NSInteger)offset API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// The address dictionary of a type checking result.
@property (nullable, readonly, copy) NSDictionary<NSTextCheckingKey, NSString *> *addressComponents;    // Deprecated in favor of components

@end


/* Keys for address components. */
/// A key for the name component of a text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingNameKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A key for the job title component of a text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingJobTitleKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A key for the organization component of a text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingOrganizationKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A key for the street component of a text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingStreetKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A key for the city component of a text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingCityKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A key for the state component of a text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingStateKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A key for the ZIP code component of a text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingZIPKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A key for the country component of a text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingCountryKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A key for the phone number component of a text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingPhoneKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A key for the airline component of a transit information text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingAirlineKey API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
/// A key for the flight number component of a transit information text checking result.
FOUNDATION_EXPORT NSTextCheckingKey const NSTextCheckingFlightKey API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));


@interface NSTextCheckingResult (NSTextCheckingResultCreation)

/* Methods for creating instances of the various types of results. */
/// Creates and returns a text checking result with the specified orthography.
+ (NSTextCheckingResult *)orthographyCheckingResultWithRange:(NSRange)range orthography:(NSOrthography *)orthography;
/// Creates and returns a text checking result with the range of a misspelled word.
+ (NSTextCheckingResult *)spellCheckingResultWithRange:(NSRange)range;
/// Creates and returns a text checking result with the specified grammar details.
+ (NSTextCheckingResult *)grammarCheckingResultWithRange:(NSRange)range details:(NSArray<NSDictionary<NSString *, id> *> *)details;
/// Creates and returns a text checking result with the specified date.
+ (NSTextCheckingResult *)dateCheckingResultWithRange:(NSRange)range date:(NSDate *)date;
/// Creates and returns a text checking result with the specified date, time zone, and duration.
+ (NSTextCheckingResult *)dateCheckingResultWithRange:(NSRange)range date:(NSDate *)date timeZone:(NSTimeZone *)timeZone duration:(NSTimeInterval)duration;
/// Creates and returns a text checking result with the specified address components.
+ (NSTextCheckingResult *)addressCheckingResultWithRange:(NSRange)range components:(NSDictionary<NSTextCheckingKey, NSString *> *)components;
/// Creates and returns a text checking result with the specified URL.
+ (NSTextCheckingResult *)linkCheckingResultWithRange:(NSRange)range URL:(NSURL *)url;
/// Creates and returns a text checking result with the specified quote replacement string.
+ (NSTextCheckingResult *)quoteCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
/// Creates and returns a text checking result with the specified dash replacement string.
+ (NSTextCheckingResult *)dashCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
/// Creates and returns a text checking result with the specified replacement string.
+ (NSTextCheckingResult *)replacementCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
/// Creates and returns a text checking result with the specified correction replacement string.
+ (NSTextCheckingResult *)correctionCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
+ (NSTextCheckingResult *)correctionCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString alternativeStrings:(NSArray<NSString *> *)alternativeStrings     API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
/// Creates and returns a text checking result with the specified regular expression data.
+ (NSTextCheckingResult *)regularExpressionCheckingResultWithRanges:(NSRangePointer)ranges count:(NSUInteger)count regularExpression:(NSRegularExpression *)regularExpression   API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
/// Creates and returns a text checking result with the specified phone number.
+ (NSTextCheckingResult *)phoneNumberCheckingResultWithRange:(NSRange)range phoneNumber:(NSString *)phoneNumber             API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
/// Creates and returns a text checking result with the specified transit information.
+ (NSTextCheckingResult *)transitInformationCheckingResultWithRange:(NSRange)range components:(NSDictionary<NSTextCheckingKey, NSString *> *)components    API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

