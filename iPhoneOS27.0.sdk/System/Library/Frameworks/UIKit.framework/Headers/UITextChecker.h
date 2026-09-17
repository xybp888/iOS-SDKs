#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextChecker.h>)
//
//  UITextChecker.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>

/* A UITextChecker object is used by a client (e.g. a document in an application) to check a given NSString. Generally one UITextChecker instance should be created per document.  Multiple related pieces of text may share a single UITextChecker instance, if they are intended to share ignored words and other similar state.
*/

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextChecker : NSObject 

/* Initiates a spell-check of a string.  Returns the range of the first misspelled word, or {NSNotFound, 0} if none is found.  Checking is limited to the range specified, and starts at the specified offset (which should lie within the range), but if wrapFlag is YES then it will check from the beginning of the range if no misspelling is found between startingOffset and the end of the range. */
- (NSRange)rangeOfMisspelledWordInString:(NSString *)stringToCheck range:(NSRange)range startingAt:(NSInteger)startingOffset wrap:(BOOL)wrapFlag language:(NSString *)language;

/* Returns an array of strings, in the order in which they should be presented, representing guesses for words that might have been intended in place of the misspelled word at the given range in the given string. */
- (nullable NSArray<NSString *> *)guessesForWordRange:(NSRange)range inString:(NSString *)string language:(NSString *)language;

/* Returns an array of strings, in the order in which they should be presented, representing complete words that the user might be trying to type when starting by typing the partial word at the given range in the given string. */
- (nullable NSArray<NSString *> *)completionsForPartialWordRange:(NSRange)range inString:(NSString *)string language:(NSString *)language;

/* Methods for dealing with ignored words. */
- (void)ignoreWord:(NSString *)wordToIgnore;
@property(nonatomic, strong, nullable) NSArray<NSString *> *ignoredWords;

/* These allow clients to programmatically instruct the checker to learn and unlearn words, and to determine whether a word has been learned (and hence can potentially be unlearned). */
+ (void)learnWord:(NSString *)word;
+ (BOOL)hasLearnedWord:(NSString *)word;
+ (void)unlearnWord:(NSString *)word;

/* Entries in the availableLanguages list are all available spellchecking languages in user preference order, usually language abbreviations such as en_US. */
@property(class, nonatomic, readonly) NSArray<NSString *> *availableLanguages;

/* Requests grammar checking in the background. The completion handler will be called when results are available, with an array of NSTextCheckingResult objects describing particular items found during checking and their individual ranges, sorted by range origin, then range end, then result type. The result type may be either NSTextCheckingTypeGrammar or NSTextCheckingTypeCorrection. If waitForAllResults is true, this will not return until all grammar analysis has been performed; otherwise, the request will include those grammar results that are available quickly. */
- (void)requestGrammarCheckingOfString:(NSString *)stringToCheck range:(NSRange)range waitForAllResults:(BOOL)waitForAllResults completionHandler:(void (^ _Nullable)(NSArray<NSTextCheckingResult *> *results))completionHandler API_AVAILABLE(ios(27.0), tvos(27.0), macos(27.0), visionos(27.0));

/* This method should be called to ignore a particular grammar issue. The sentence should be the portion of the text corresponding to the range of an NSTextCheckingResult of grammar type. The grammarRange should be the range within that sentence of an individual issue, taken from the NSGrammarRange entry of one of the grammarDetails of the same NSTextCheckingResult. */
- (void)ignoreGrammarRange:(NSRange)grammarRange inSentence:(NSString *)sentence API_AVAILABLE(ios(27.0), tvos(27.0), macos(27.0), visionos(27.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextChecker.h>
#endif
