/*	NSLinguisticTagger.h
	Copyright (c) 2009-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

@class NSArray<ObjectType>, NSOrthography, NSValue;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* NSLinguisticTagger is a class used to automatically segment natural-language text and tag the tokens with information such as language, script, lemma, and part of speech.  An instance of this class is assigned a string to tag, and clients can then obtain tags and ranges for tokens in that string appropriate to a given tag scheme and unit.
*/

/* Tag schemes */
/// Constants for the tag schemes specified when initializing a linguistic tagger.
///
/// ## Discussion
///
/// When initializing a linguistic tagger with ``NSLinguisticTagger/init(tagSchemes:options:)``, you specify one or more tag schemes that correspond to the kind of information you're interested in for a selection of natural language text. To ensure optimal performance, avoid specifying tag schemes that you won't use.
///
/// Some tag schemes are only available for certain units and languages. Use the ``NSLinguisticTagger/availableTagSchemes(for:language:)`` or ``NSLinguisticTagger/availableTagSchemes(forLanguage:)`` methods to determine the possible values for a specified language and linguistic unit.
///
/// When working with linguistic tags using the methods described in Getting Linguistic Tags and Enumerating Linguistic Tags, the returned tag value depends on the specified scheme. For example, given the token "Überraschung", the returned tag is ``NSLinguisticTag/noun`` when using the ``lexicalClass`` tag scheme, "de" (German language) when using the ``language`` tag scheme, and "Latn" (Latin script) when using the ``script`` tag scheme, as shown in the following code.
///
/// ```swift
/// let tagger = NSLinguisticTagger(tagSchemes: [.lexicalClass, .language, .script], options: 0)
/// tagger.string = "Überraschung"
///
/// tagger.tag(at: 0, unit: .word, scheme: .lexicalClass, tokenRange: nil) // Noun
/// tagger.tag(at: 0, unit: .word, scheme: .language, tokenRange: nil) // de
/// tagger.tag(at: 0, unit: .word, scheme: .script, tokenRange: nil) // Latn
/// ```
///
///
/// The following table lists the available tag schemes, their applicable linguistic units, and possible tag values.
///
///
/// | Linguistic tag scheme | Applicable linguistic units | Possible tag values |
/// |---|---|---|
/// | ``tokenType`` | ``NSLinguisticTaggerUnit/word`` | See Token Types |
/// | ``lexicalClass`` | ``NSLinguisticTaggerUnit/word`` | See Lexical Classes |
/// | ``nameType`` | ``NSLinguisticTaggerUnit/word`` | See Name Types |
/// | ``nameTypeOrLexicalClass`` | ``NSLinguisticTaggerUnit/word`` | See Name Types and Lexical Classes |
/// | ``lemma`` | ``NSLinguisticTaggerUnit/word`` | A stem of the word |
/// | ``language`` | ``NSLinguisticTaggerUnit/word``, ``NSLinguisticTaggerUnit/sentence``, ``NSLinguisticTaggerUnit/paragraph``, ``NSLinguisticTaggerUnit/document`` | A BCP-47 language tag |
/// | ``script`` | ``NSLinguisticTaggerUnit/word``, ``NSLinguisticTaggerUnit/sentence``, ``NSLinguisticTaggerUnit/paragraph``, ``NSLinguisticTaggerUnit/document`` | An ISO 15924 script code |
typedef NSString *NSLinguisticTagScheme NS_TYPED_EXTENSIBLE_ENUM;

/// Classifies tokens according to their broad type:  word, punctuation, or whitespace.
///
/// For possible values, see Token Types.
///
/// To classify tokens by a more specific type, for example, distinguishing words between nouns and verbs, use the `NSLinguisticTagSchemeLexicalClass` scheme.
FOUNDATION_EXPORT NSLinguisticTagScheme const NSLinguisticTagSchemeTokenType API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Classifies tokens according to class: part of speech for words, type of punctuation or whitespace, etc.
FOUNDATION_EXPORT NSLinguisticTagScheme const NSLinguisticTagSchemeLexicalClass API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Classifies tokens as to whether they are part of named entities of various types or not.
FOUNDATION_EXPORT NSLinguisticTagScheme const NSLinguisticTagSchemeNameType API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Follows `NSLinguisticTagSchemeNameType` for names, `NSLinguisticTagSchemeLexicalClass` for all other tokens.
FOUNDATION_EXPORT NSLinguisticTagScheme const NSLinguisticTagSchemeNameTypeOrLexicalClass API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Supplies a stem form for each word token (if known).
FOUNDATION_EXPORT NSLinguisticTagScheme const NSLinguisticTagSchemeLemma API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Tags tokens according to their most likely language (if known).
FOUNDATION_EXPORT NSLinguisticTagScheme const NSLinguisticTagSchemeLanguage API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Tags tokens according to their script.
FOUNDATION_EXPORT NSLinguisticTagScheme const NSLinguisticTagSchemeScript API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// A token, lexical class, name, lemma, language, or script returned by a linguistic tagger for natural language text.
typedef NSString *NSLinguisticTag NS_TYPED_EXTENSIBLE_ENUM;

/* Tags for NSLinguisticTagSchemeTokenType */
/// Tokens considered to be words or word-like linguistic items.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagWord API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token indicates punctuation.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagPunctuation API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Tokens made up of whitespace of all sorts.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagWhitespace API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Other tokens, including non-linguistic items such as symbols.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagOther API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/* Tags for NSLinguisticTagSchemeLexicalClass */
/// The token is a noun.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagNoun API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a verb.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagVerb API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is an adjective.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagAdjective API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is an adverb.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagAdverb API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a pronoun.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagPronoun API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a determiner.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagDeterminer API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a particle.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagParticle API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a preposition.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagPreposition API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a number.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagNumber API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a conjunction.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagConjunction API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is an interjection.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagInterjection API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a classifier.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagClassifier API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is an idiom.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagIdiom API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a word that doesn't fall into any other category.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagOtherWord API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a sentence terminator.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagSentenceTerminator API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is an open quote.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagOpenQuote API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a close quote.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagCloseQuote API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is an open parenthesis.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagOpenParenthesis API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a close parenthesis.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagCloseParenthesis API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a word joiner.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagWordJoiner API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a dash.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagDash API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is punctuation that doesn't fall into any other category.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagOtherPunctuation API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a paragraph break.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagParagraphBreak API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is whitespace that doesn't fall into any other category.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagOtherWhitespace API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/* Tags for NSLinguisticTagSchemeNameType */
/// The token is a personal name.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagPersonalName API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is a place name.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagPlaceName API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The token is an organization name.
FOUNDATION_EXPORT NSLinguisticTag const NSLinguisticTagOrganizationName API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/* For NSLinguisticTagSchemeTokenType, NSLinguisticTagSchemeLexicalClass, NSLinguisticTagSchemeNameType, and NSLinguisticTagSchemeNameTypeOrLexicalClass, tags will be taken from the lists above (clients may use == comparison).  Tags for NSLinguisticTagSchemeLemma are lemmas from the language.  Tags for NSLinguisticTagSchemeLanguage are standard language abbreviations.  Tags for NSLinguisticTagSchemeScript are standard script abbreviations.
*/

/* NSLinguisticTaggerUnit specifes the size of units in a string to which tagging applies.  The tagging unit may be word, sentence, paragraph, or document.  Methods that do not specify a unit act at the word level.  Not all combinations of scheme and unit are supported; clients can use +availableTagSchemesForUnit:language: to determine which ones are.
*/
/// Constants representing linguistic units.
///
/// You use these constants with the ``NSLinguisticTagger/availableTagSchemes(for:language:)`` method as well as the ``NSLinguisticTagger/tag(for:at:unit:scheme:orthography:tokenRange:)``,  ``NSLinguisticTagger/tags(in:unit:scheme:options:tokenRanges:)``, and ``NSLinguisticTagger/enumerateTags(in:unit:scheme:options:using:)`` methods.
typedef NS_ENUM(NSInteger, NSLinguisticTaggerUnit) {
    /// An individual word.
    NSLinguisticTaggerUnitWord,
    /// A sentence.
    NSLinguisticTaggerUnitSentence,
    /// A paragraph.
    NSLinguisticTaggerUnitParagraph,
    /// The document in its entirety.
    NSLinguisticTaggerUnitDocument
};

/// Options arguments of type `NSLinguisticTaggerOptions` may include the following flags, which allow clients interested only in certain general types of tokens to specify that tokens of other types should be omitted from the returned results.
typedef NS_OPTIONS(NSUInteger, NSLinguisticTaggerOptions) {
    /// Omit tokens of type `NSLinguisticTagWord` (items considered to be words).
    NSLinguisticTaggerOmitWords         = 1 << 0,
    /// Omit tokens of type `NSLinguisticTagPunctuation` (all punctuation).
    NSLinguisticTaggerOmitPunctuation   = 1 << 1,
    /// Omit tokens of type `NSLinguisticTagWhitespace` (whitespace of all sorts).
    NSLinguisticTaggerOmitWhitespace    = 1 << 2,
    /// Omit tokens of type `NSLinguisticTagOther` (non-linguistic items, such as symbols).
    NSLinguisticTaggerOmitOther         = 1 << 3,
    /// Typically, multiple-word names will be returned as multiple tokens, following the standard tokenization practice of the tagger. If this option is set, then multiple-word names will be joined together and returned as a single token.
    NSLinguisticTaggerJoinNames         = 1 << 4
};


/// Analyze natural language text to tag part of speech and lexical class, identify names, perform lemmatization, and determine the language and script.
///
/// @DeprecationSummary {
/// Use the <doc://com.apple.documentation/documentation/naturallanguage> framework instead.
/// }
///
/// ``NSLinguisticTagger`` provides a uniform interface to a variety of natural language processing functionality with support for many different languages and scripts. You can use this class to segment natural language text into paragraphs, sentences, or words, and tag information about those segments, such as part of speech, lexical class, lemma, script, and language.
///
/// When you create a linguistic tagger, you specify what kind of information you're interested in by passing one or more ``NSLinguisticTagScheme`` values. Set the ``string`` property to the natural language text you want to analyze, and the linguistic tagger processes it according to the specified tag schemes. You can then enumerate over the tags in a specified range, using the methods described in Enumerating Linguistic Tags, to get the information requested for a given scheme and unit.
///
/// ### Thread Safety
///
/// A single instance of ``NSLinguisticTagger`` should not be used simultaneously from multiple threads.
API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED))
@interface NSLinguisticTagger : NSObject {
@private
    NSArray *_schemes;
    NSUInteger _options;
    NSString *_string;
    id _orthographyArray;
    id _tokenArray;
    void *_reserved;
}

/// Creates a linguistic tagger instance using the specified tag schemes and options.
///
/// - Parameters:
///   - tagSchemes: An array of tag schemes to be used. See `NSLinguisticTagScheme` for the possible values.
///   - opts: Reserved for future use. Specify `0` for this parameter.
///
/// Pass any tag schemes to `tagSchemes` that you intend to use with the methods described in Enumerating Linguistic Tags and Getting Linguistic Tags.
///
/// > Tip: Avoid specifying tag schemes that you won't use to ensure optimal performance.
- (instancetype)initWithTagSchemes:(NSArray<NSLinguisticTagScheme> *)tagSchemes options:(NSUInteger)opts NS_DESIGNATED_INITIALIZER API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Returns the tag schemes configured for this linguistic tagger.
@property (readonly, copy) NSArray<NSLinguisticTagScheme> *tagSchemes API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// The string being analyzed by the linguistic tagger.
@property (nullable, retain) NSString *string API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Returns the tag schemes available for a particular unit and language on the current device.
///
/// - Parameters:
///   - unit: The linguistic unit. For possible values, see `NSLinguisticTaggerUnit`.
///   - language: A BCP-47 tag identifying the language. For example, "en" for English or "zh-Hans" for Chinese written using the Simplified Chinese script.
/// - Returns: The supported tag schemes. For possible values, see `NSLinguisticTagScheme`.
+ (NSArray<NSLinguisticTagScheme> *)availableTagSchemesForUnit:(NSLinguisticTaggerUnit)unit language:(NSString *)language API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));

/// Returns the tag schemes available for a particular language on the current device.
///
/// - Parameters:
///   - language: A BCP-47 tag identifying the language. For example, "en" for English or "zh-Hans" for Chinese written using the Simplified Chinese script.
/// - Returns: The available tag schemes. For possible values, see `NSLinguisticTagScheme`.
///
/// This is a convenience method for calling `availableTagSchemesForUnit:language:`, passing `NSLinguisticTaggerUnitWord` as the linguistic unit.
+ (NSArray<NSLinguisticTagScheme> *)availableTagSchemesForLanguage:(NSString *)language API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Sets the orthography for the specified range.
///
/// - Parameters:
///   - orthography: The orthography.
///   - range: The range.
///
/// If the orthography of the linguistic tagger is not set, it will determine it automatically from the contents of the text.  You should call this method only if you know the orthography of the text by some other means.
- (void)setOrthography:(nullable NSOrthography *)orthography range:(NSRange)range API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Returns the orthography at the index and also returns the effective range.
///
/// - Parameters:
///   - charIndex: The character index to begin examination.
///   - effectiveRange: An NSRangePointer that, upon completion, contains the range of the orthography containing `charIndex`.
/// - Returns: The orthography for the location.
- (nullable NSOrthography *)orthographyAtIndex:(NSUInteger)charIndex effectiveRange:(nullable NSRangePointer)effectiveRange API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Notifies the linguistic tagger that the string (if mutable) has changed as specified by the parameters.
///
/// - Parameters:
///   - newRange: The range in the final string that was edited.
///   - delta: The change in length.
- (void)stringEditedInRange:(NSRange)newRange changeInLength:(NSInteger)delta API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Returns the range of the linguistic unit containing the specified character index.
///
/// - Parameters:
///   - charIndex: The character index to begin examination.
///   - unit: The linguistic unit. For possible values, see `NSLinguisticTaggerUnit`.
/// - Returns: The range of the substring for the linguistic unit.
- (NSRange)tokenRangeAtIndex:(NSUInteger)charIndex unit:(NSLinguisticTaggerUnit)unit API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));

/// Returns a range covering all sentences intersecting the given range.
///
/// - Parameters:
///   - range: The character range.
/// - Returns: Returns the range of the sentence.
///
/// This is a convenience method for calling `tokenRangeAtIndex:unit:`, passing `NSLinguisticTaggerUnitSentence` as the unit and the first position of the provided range.
- (NSRange)sentenceRangeForRange:(NSRange)range API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Enumerates over a given range of the string for a particular unit and calls the specified block for each tag.
///
/// - Parameters:
///   - range: The range to analyze.
///   - unit: The linguistic unit. For possible values, see `NSLinguisticTaggerUnit`.
///   - scheme: The tag scheme. For possible values, see `NSLinguisticTagScheme`.
///   - options: The linguistic tagger options to use.
///   - block: The block to apply to ranges of the string. The block takes a tag, a token range, and a stop pointer as arguments.
///
/// This method's block is called for all tokens intersecting a given range, supplying tags and ranges.
- (void)enumerateTagsInRange:(NSRange)range unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options usingBlock:(void (NS_NOESCAPE ^)(NSLinguisticTag _Nullable tag, NSRange tokenRange, BOOL *stop))block API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));
/// Returns a tag for a single scheme, for a given linguistic unit, at the specified character position.
///
/// - Parameters:
///   - charIndex: The position of the initial character.
///   - unit: The linguistic unit. See `NSLinguisticTaggerUnit` for possible values.
///   - scheme: The tag scheme. See `NSLinguisticTagScheme` for possible values.
///   - tokenRange: A pointer to the token range.
/// - Returns: Returns the tag for the requested tag scheme and linguistic unit, or `nil`. If a tag is returned, this function returns by reference the range of the token to `tokenRange`.
- (nullable NSLinguisticTag)tagAtIndex:(NSUInteger)charIndex unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme tokenRange:(nullable NSRangePointer)tokenRange API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));
/// Returns an array of linguistic tags and token ranges for a given string range and linguistic unit.
///
/// - Parameters:
///   - range: The range from which to return tags.
///   - unit: The linguistic unit. See `NSLinguisticTaggerUnit` for possible values.
///   - scheme: The tag scheme. See `NSLinguisticTagScheme` for possible values.
///   - options: The linguistic tagger options to use.
///   - tokenRanges: Returns by reference an array of token ranges.
/// - Returns: An array of the tags in the requested range.
- (NSArray<NSLinguisticTag> *)tagsInRange:(NSRange)range unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options tokenRanges:(NSArray<NSValue *> * _Nullable * _Nullable)tokenRanges API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));

/// Enumerates over a given range of the string and calls the specified block for each tag.
///
/// - Parameters:
///   - range: The range to analyze.
///   - tagScheme: The tag scheme. For possible values, see `NSLinguisticTagScheme`.
///   - opts: The linguistic tagger options to use.
///   - block: The block to apply to ranges of the string. The block takes a tag, a token range, a sentence range, and a stop pointer as arguments.
///
/// This is a convenience method for calling `enumerateTagsInRange:unit:scheme:options:usingBlock:`, passing `NSLinguisticTaggerUnitWord` as the linguistic unit.
- (void)enumerateTagsInRange:(NSRange)range scheme:(NSLinguisticTagScheme)tagScheme options:(NSLinguisticTaggerOptions)opts usingBlock:(void (NS_NOESCAPE ^)(NSLinguisticTag _Nullable tag, NSRange tokenRange, NSRange sentenceRange, BOOL *stop))block API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Returns a tag for a single scheme at the specified character position.
///
/// - Parameters:
///   - charIndex: The position of the initial character.
///   - scheme: The tag scheme. See `NSLinguisticTagScheme` for the possible values.
///   - tokenRange: A pointer to the token range.
///   - sentenceRange: A pointer to the range of the sentence.
/// - Returns: Returns the tag for the requested tag scheme, or `nil`. If a tag is returned, this function returns by reference the range of the token to `tokenRange`, and the range of the enclosing sentence to `sentenceRange`, if applicable.
///
/// This is a convenience method for calling `tagAtIndex:unit:scheme:tokenRange:` and passing `NSLinguisticTaggerUnitWord` as the linguistic unit.
- (nullable NSLinguisticTag)tagAtIndex:(NSUInteger)charIndex scheme:(NSLinguisticTagScheme)scheme tokenRange:(nullable NSRangePointer)tokenRange sentenceRange:(nullable NSRangePointer)sentenceRange API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Returns an array of linguistic tags and token ranges for a given string range.
///
/// - Parameters:
///   - range: The range from which to return tags.
///   - tagScheme: The tag scheme. See `NSLinguisticTagScheme` for possible values.
///   - opts: The linguistic tagger options to use.
///   - tokenRanges: Returns by reference an array of token ranges.
/// - Returns: An array of the tags in the requested range.
///
/// This is a convenience method for calling `tagsInRange:unit:scheme:options:tokenRanges:` and passing `NSLinguisticTaggerUnitWord` as the linguistic unit.
- (NSArray<NSString *> *)tagsInRange:(NSRange)range scheme:(NSString *)tagScheme options:(NSLinguisticTaggerOptions)opts tokenRanges:(NSArray<NSValue *> * _Nullable * _Nullable)tokenRanges API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Returns the dominant language of the string set for the linguistic tagger.
///
/// Returns the BCP-47 tag identifying the dominant language of the string, or the tag "und" if a specific language cannot be determined.
@property (nullable, readonly, copy) NSString *dominantLanguage API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));

/// Returns the dominant language for the specified string.
///
/// - Parameters:
///   - string: The string for which the dominant language is determined.
/// - Returns: The BCP-47 tag identifying the dominant language of the string, or the tag "und" if a specific language cannot be determined.
///
/// This is a convenience method for creating a new linguistic tagger, setting the `string` property, and getting the `dominantLanguage` property.
+ (nullable NSString *)dominantLanguageForString:(NSString *)string API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));
/// Returns a tag for a single scheme, for a given linguistic unit, at the specified character position in a string.
///
/// - Parameters:
///   - string: The string to analyze.
///   - charIndex: The position of the initial character.
///   - unit: The linguistic unit. See `NSLinguisticTaggerUnit` for possible values.
///   - scheme: The tag scheme. See `NSLinguisticTagScheme` for possible values.
///   - orthography: The orthography of the string. If unspecified, the orthography is automatically detected.
///   - tokenRange: A pointer to the token range.
/// - Returns: Returns the tag for the requested tag scheme and linguistic unit, or `nil`.
///
/// This is a convenience method for initializing a linguistic tagger, setting the `string` property, and calling `tagAtIndex:unit:scheme:tokenRange:`. If you analyze the same string more than once, you should create a linguistic tagger object instead of calling this method.
+ (nullable NSLinguisticTag)tagForString:(NSString *)string atIndex:(NSUInteger)charIndex unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme orthography:(nullable NSOrthography *)orthography tokenRange:(nullable NSRangePointer)tokenRange API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));
/// Returns an array of linguistic tags and token ranges for a given string and linguistic unit.
///
/// - Parameters:
///   - string: The string to analyze.
///   - range: The range from which to return tags.
///   - unit: The linguistic unit. See `NSLinguisticTaggerUnit` for possible values.
///   - scheme: The tag scheme. See `NSLinguisticTagScheme` for possible values.
///   - options: The linguistic tagger options to use.
///   - orthography: The orthography of the string. If unspecified, the orthography is automatically detected.
///   - tokenRanges: Returns by reference an array of token ranges.
/// - Returns: An array of the tags in the requested range.
///
/// This is a convenience method for initializing a linguistic tagger, setting the `string` property, and calling `tagsInRange:unit:scheme:options:tokenRanges:`. If you analyze the same string more than once, you should create a linguistic tagger object instead of calling this method.
+ (NSArray<NSLinguisticTag> *)tagsForString:(NSString *)string range:(NSRange)range unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options orthography:(nullable NSOrthography *)orthography tokenRanges:(NSArray<NSValue *> * _Nullable * _Nullable)tokenRanges API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));
/// Enumerates over a given string and calls the specified block for each tag.
///
/// - Parameters:
///   - string: The string to enumerate over.
///   - range: The range to analyze.
///   - unit: The linguistic unit. For possible values, see `NSLinguisticTaggerUnit`.
///   - scheme: The tag scheme. For possible values, see `NSLinguisticTagScheme`.
///   - options: The linguistic tagger options to use.
///   - orthography: The orthography of the string. If unspecified, the orthography is automatically detected.
///   - block: The block to apply to ranges of the string. The block takes a tag, a token range, and a stop pointer as arguments.
///
/// This is a convenience method for initializing a linguistic tagger, setting the `string` property, and calling `enumerateTagsInRange:unit:scheme:options:usingBlock:`. If you analyze the same string more than once, you should create a linguistic tagger object instead of calling this method.
+ (void)enumerateTagsForString:(NSString *)string range:(NSRange)range unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options orthography:(nullable NSOrthography *)orthography usingBlock:(void (NS_NOESCAPE ^)(NSLinguisticTag _Nullable tag, NSRange tokenRange, BOOL *stop))block API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), watchos(4.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));

/// Returns an array of possible tags for the given scheme at the specified range, supplying matching scores.
///
/// - Parameters:
///   - charIndex: The position of the initial character.
///   - tagScheme: The tag scheme. See `NSLinguisticTagScheme` for possible values.
///   - tokenRange: The token range.
///   - sentenceRange: The range of the sentence.
///   - scores: Returns by reference an array of numeric scores indicating the likelihood that the range matches the tag scheme.
/// - Returns: Returns an array of possible tags for the tag scheme at the specified location, starting with the most likely tag scheme.
///
/// Calling this method is not recommended; for most use cases, this information is not as useful as what is provided by the methods described in Enumerating Linguistic Tags and Getting Linguistic Tags.
- (nullable NSArray<NSString *> *)possibleTagsAtIndex:(NSUInteger)charIndex scheme:(NSString *)tagScheme tokenRange:(nullable NSRangePointer)tokenRange sentenceRange:(nullable NSRangePointer)sentenceRange scores:(NSArray<NSValue *> * _Nullable * _Nullable)scores API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

@end

@interface NSString (NSLinguisticAnalysis)

/// Returns an array of linguistic tags for the specified range and requested tags within the receiving string.
///
/// This is a convenience method. It is the equivalent of creating an instance of ``NSLinguisticTagger``, specifying the receiver as the string to be analyzed, and the orthography (or `nil`) and then invoking the ``NSLinguisticTagger`` method ``NSLinguisticTagger/tags(in:scheme:options:tokenRanges:)``.
///
/// - Parameters:
///   - range: The range of the string to analyze.
///   - scheme: The tag scheme to use. See Linguistic Tag Schemes for supported values.
///   - options: The linguistic tagger options to use. See ``NSLinguisticTagger/Options`` for the constants. These constants can be combined using the C-Bitwise OR operator.
///   - orthography: The orthography of the string. If `nil`, the linguistic tagger will attempt to determine the orthography from the string content.
///   - tokenRanges: An array returned by-reference containing the token ranges of the linguistic tags wrapped in `NSValue` objects.
/// - Returns: An array containing the linguistic tags for the `tokenRanges` within the receiving string.
- (NSArray<NSLinguisticTag> *)linguisticTagsInRange:(NSRange)range scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options orthography:(nullable NSOrthography *)orthography tokenRanges:(NSArray<NSValue *> * _Nullable * _Nullable)tokenRanges API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Performs linguistic analysis on the specified string by enumerating the specific range of the string, providing the block with the located tags.
///
/// This is a convenience method. It is the equivalent of creating an instance of ``NSLinguisticTagger``, specifying the receiver as the string to be analyzed, and the orthography (or `nil`) and then invoking ``NSLinguisticTagger/enumerateTags(in:scheme:options:using:)``.
///
/// - Parameters:
///   - range: The range of the string to analyze.
///   - scheme: The tag scheme to use. See Linguistic Tag Schemes for supported values.
///   - options: The linguistic tagger options to use. See ``NSLinguisticTagger/Options`` for the constants. These constants can be combined using the C-Bitwise OR operator.
///   - orthography: The orthography of the string. If `nil`, the linguistic tagger will attempt to determine the orthography from the string content.
///   - block: The block to apply to the string. The block takes four arguments: the tag for the token, the token range, the sentence range, and a stop pointer.
- (void)enumerateLinguisticTagsInRange:(NSRange)range scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options orthography:(nullable NSOrthography *)orthography usingBlock:(void (NS_NOESCAPE ^)(NSLinguisticTag _Nullable tag, NSRange tokenRange, NSRange sentenceRange, BOOL *stop))block API_DEPRECATED("All NSLinguisticTagger API should be replaced with NaturalLanguage.framework API", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
