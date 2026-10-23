/*    NSMorphology.h
      Copyright (c) 2021, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSError.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A representation of grammatical gender, used for inflecting strings.
typedef NS_ENUM(NSInteger, NSGrammaticalGender) {
    /// The grammatical gender is not set.
    NSGrammaticalGenderNotSet = 0,
    /// The feminine grammatical gender.
    NSGrammaticalGenderFeminine,
    /// The masculine grammatical gender.
    NSGrammaticalGenderMasculine,
    /// The neuter grammatical gender.
    NSGrammaticalGenderNeuter,
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// A representation of grammatical parts of speech, used for inflecting strings.
typedef NS_ENUM(NSInteger, NSGrammaticalPartOfSpeech) {
    /// The part of speech is not set.
    NSGrammaticalPartOfSpeechNotSet = 0,
    /// A word that introduces a noun.
    NSGrammaticalPartOfSpeechDeterminer,
    /// A word that substitutes for a noun.
    NSGrammaticalPartOfSpeechPronoun,
    /// A letter of an alphabet.
    NSGrammaticalPartOfSpeechLetter,
    /// A word that modifies a verb, an adjective, or another adverb.
    NSGrammaticalPartOfSpeechAdverb,
    /// A function word associated with another word or phrase to express a grammatical or semantic relation.
    NSGrammaticalPartOfSpeechParticle,
    /// A word that modifies a noun.
    NSGrammaticalPartOfSpeechAdjective,
    /// A word governing, and usually preceding, a noun or pronoun to express a relation.
    NSGrammaticalPartOfSpeechAdposition,
    /// A word that describes an action.
    NSGrammaticalPartOfSpeechVerb,
    /// A word that represents a person, place, or thing.
    NSGrammaticalPartOfSpeechNoun,
    /// A word that connects words, phrases, or clauses.
    NSGrammaticalPartOfSpeechConjunction,
    /// A word that represents a number.
    NSGrammaticalPartOfSpeechNumeral,
    /// A word that expresses a strong emotion.
    NSGrammaticalPartOfSpeechInterjection,
    /// A word governing, and usually preceding, a noun or pronoun to express a relation to another word.
    NSGrammaticalPartOfSpeechPreposition,
    /// An abbreviation.
    NSGrammaticalPartOfSpeechAbbreviation,
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// A representation of grammatical number, used for inflecting strings.
typedef NS_ENUM(NSInteger, NSGrammaticalNumber) {
    /// The grammatical number is not set.
    NSGrammaticalNumberNotSet = 0,
    /// The singular form.
    NSGrammaticalNumberSingular,
    /// The zero form.
    NSGrammaticalNumberZero,
    /// The plural form.
    NSGrammaticalNumberPlural,
    /// The dual plural form.
    NSGrammaticalNumberPluralTwo,
    /// The paucal (few) plural form.
    NSGrammaticalNumberPluralFew,
    /// The plural form for many.
    NSGrammaticalNumberPluralMany,
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

typedef NS_ENUM(NSInteger, NSGrammaticalCase) {
    NSGrammaticalCaseNotSet = 0,
    NSGrammaticalCaseNominative,
    NSGrammaticalCaseAccusative,
    NSGrammaticalCaseDative,
    NSGrammaticalCaseGenitive,
    NSGrammaticalCasePrepositional,
    NSGrammaticalCaseAblative,
    NSGrammaticalCaseAdessive,
    NSGrammaticalCaseAllative,
    NSGrammaticalCaseElative,
    NSGrammaticalCaseIllative,
    NSGrammaticalCaseEssive,
    NSGrammaticalCaseInessive,
    NSGrammaticalCaseLocative,
    NSGrammaticalCaseTranslative
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

typedef NS_ENUM(NSInteger, NSGrammaticalPronounType) {
    NSGrammaticalPronounTypeNotSet = 0,
    NSGrammaticalPronounTypePersonal,
    NSGrammaticalPronounTypeReflexive,
    NSGrammaticalPronounTypePossessive
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

typedef NS_ENUM(NSInteger, NSGrammaticalPerson) {
    NSGrammaticalPersonNotSet = 0,
    NSGrammaticalPersonFirst,
    NSGrammaticalPersonSecond,
    NSGrammaticalPersonThird
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

typedef NS_ENUM(NSInteger, NSGrammaticalDetermination) {
    NSGrammaticalDeterminationNotSet = 0,
    NSGrammaticalDeterminationIndependent,
    NSGrammaticalDeterminationDependent
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

typedef NS_ENUM(NSInteger, NSGrammaticalDefiniteness) {
    NSGrammaticalDefinitenessNotSet = 0,
    NSGrammaticalDefinitenessIndefinite,
    NSGrammaticalDefinitenessDefinite
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// A description of the grammatical properties of a string.
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
NS_REFINED_FOR_SWIFT
@interface NSMorphology: NSObject <NSCopying, NSSecureCoding>

/// The grammatical gender used for inflecting strings.
@property (nonatomic) NSGrammaticalGender grammaticalGender;

/// The grammatical part of speech used for inflecting strings.
@property (nonatomic) NSGrammaticalPartOfSpeech partOfSpeech;

/// The grammatical number used for inflecting strings.
@property (nonatomic) NSGrammaticalNumber number;
@property (nonatomic) NSGrammaticalCase grammaticalCase API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));
@property (nonatomic) NSGrammaticalDetermination determination API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));
@property (nonatomic) NSGrammaticalPerson grammaticalPerson API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));
@property (nonatomic) NSGrammaticalPronounType pronounType API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));
@property (nonatomic) NSGrammaticalDefiniteness definiteness API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

@end

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
@interface NSMorphologyPronoun : NSObject <NSCopying, NSSecureCoding>
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithPronoun:(NSString*)pronoun
                     morphology:(NSMorphology*)morphology
            dependentMorphology:(nullable NSMorphology*)dependentMorphology;

@property (readonly, copy) NSString* pronoun;
@property (readonly, copy) NSMorphology* morphology;
@property (readonly, copy, nullable) NSMorphology* dependentMorphology;
@end

// Per-language attribute support:

@class NSMorphologyCustomPronoun;

API_DEPRECATED("Use NSTermOfAddress instead", macos(12.0,14.0), ios(15.0,17.0), tvos(15.0,17.0), watchos(8.0,10.0))
@interface NSMorphology (NSCustomPronouns)

/// Returns the custom pronoun behavior for the specified language.
- (nullable NSMorphologyCustomPronoun *)customPronounForLanguage:(NSString *)language
API_DEPRECATED("Use NSTermOfAddress instead", macos(12.0,14.0), ios(15.0,17.0), tvos(15.0,17.0), watchos(8.0,10.0));

/// Sets the custom pronoun behavior for the specified language.
- (BOOL)setCustomPronoun:(nullable NSMorphologyCustomPronoun *)features forLanguage:(NSString *)language error:(NSError **)error
API_DEPRECATED("Use NSTermOfAddress instead", macos(12.0,14.0), ios(15.0,17.0), tvos(15.0,17.0), watchos(8.0,10.0));

@end

/// A custom pronoun behavior for use in a specific language.
API_DEPRECATED("Use NSTermOfAddress instead", macos(12.0,14.0), ios(15.0,17.0), tvos(15.0,17.0), watchos(8.0,10.0))
NS_REFINED_FOR_SWIFT
@interface NSMorphologyCustomPronoun: NSObject <NSCopying, NSSecureCoding>

/// Returns a Boolean value that indicates whether custom pronouns are supported for the specified language.
+ (BOOL)isSupportedForLanguage:(NSString *)language;

/// Returns the list of pronoun form keys required for the specified language.
+ (NSArray<NSString *> *)requiredKeysForLanguage:(NSString *)language;

/// The subject pronoun form.
@property(nullable, copy, nonatomic) NSString *subjectForm;

/// The object pronoun form.
@property(nullable, copy, nonatomic) NSString *objectForm;

/// The possessive pronoun form.
@property(nullable, copy, nonatomic) NSString *possessiveForm;

/// The possessive adjective form.
@property(nullable, copy, nonatomic) NSString *possessiveAdjectiveForm;

/// The reflexive pronoun form.
@property(nullable, copy, nonatomic) NSString *reflexiveForm;

@end


// User settings access:

@interface NSMorphology (NSMorphologyUserSettings)

/// A Boolean value that indicates whether the morphology has no specific settings.
@property (readonly, getter=isUnspecified) BOOL unspecified
 API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// The current user's morphology.
@property (class, readonly) NSMorphology *userMorphology
 API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
