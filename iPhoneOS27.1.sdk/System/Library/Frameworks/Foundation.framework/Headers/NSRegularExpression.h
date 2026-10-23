/*	NSRegularExpression.h
	Copyright (c) 2009-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSTextCheckingResult.h>

@class NSArray<ObjectType>;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An immutable representation of a compiled regular expression that you apply to Unicode strings.
///
/// The pattern syntax currently supported is that specified by ICU.

/// These constants define the regular expression options. These constants are used by the property `options`, `regularExpressionWithPattern:options:error:`, and `initWithPattern:options:error:`.
typedef NS_OPTIONS(NSUInteger, NSRegularExpressionOptions) {
   /// Match letters in the pattern independent of case.
   NSRegularExpressionCaseInsensitive             = 1 << 0,
   /// Ignore whitespace and #-prefixed comments in the pattern.
   NSRegularExpressionAllowCommentsAndWhitespace  = 1 << 1,
   /// Treat the entire pattern as a literal string.
   NSRegularExpressionIgnoreMetacharacters        = 1 << 2,
   /// Allow `.` to match any character, including line separators.
   NSRegularExpressionDotMatchesLineSeparators    = 1 << 3,
   /// Allow `^` and `$` to match the start and end of lines.
   NSRegularExpressionAnchorsMatchLines           = 1 << 4,
   /// Treat only `\n` as a line separator (otherwise, all standard line separators are used).
   NSRegularExpressionUseUnixLineSeparators       = 1 << 5,
   /// Use Unicode TR#29 to specify word boundaries (otherwise, traditional regular expression word boundaries are used).
   NSRegularExpressionUseUnicodeWordBoundaries    = 1 << 6
};

/// An immutable representation of a compiled regular expression that you apply to Unicode strings.
///
/// The fundamental matching method for ``NSRegularExpression`` is a Block iterator method that allows clients to supply a Block object which will be invoked each time the regular expression matches a portion of the target string.  There are additional convenience methods for returning all the matches as an array, the total number of matches, the first match, and the range of the first match.
///
/// An individual match is represented by an instance of the ``NSTextCheckingResult`` class, which carries information about the overall matched range (via its ``NSTextCheckingResult/range`` property), and the range of each individual capture group (via the ``NSTextCheckingResult/range(at:)`` method).  For basic ``NSRegularExpression`` objects, these match results will be of type ``NSTextCheckingResult/CheckingType/regularExpression``, but subclasses may use other types.
///
/// > Note:
/// > ``NSRegularExpression`` conforms to the International Components for Unicode ([ICU](https://unicode-org.github.io/icu/)) specification for [regular expressions](https://unicode-org.github.io/icu/userguide/strings/regexp.html).
///
/// ### Examples Using NSRegularExpression
///
/// What follows are a set of graduated examples for using the `NSRegularExpression` class. All these examples use the regular expression `\\b(a|b)(c|d)\\b` as their regular expression.
///
/// This snippet creates a regular expression to match two-letter words, in which the first letter is "a" or "b" and the second letter is "c" or "d". Specifying ``Options/caseInsensitive`` means that matches will be case-insensitive, so this will match "BC", "aD", and so forth, as well as their lower-case equivalents.
///
///
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// do {
/// let regex = try NSRegularExpression(pattern: "\\b(a|b)(c|d)\\b", options: .caseInsensitive)
/// } catch let error as NSError {
/// print("Error creating NSRegularExpression: \(error)")
/// }
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSError *error = NULL;
/// NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:@"\\b(a|b)(c|d)\\b"
/// options:NSRegularExpressionCaseInsensitive
/// error:&error];
/// ```
/// }
/// }
///
///
/// The ``numberOfMatches(in:options:range:)`` method provides a simple mechanism for counting the number of matches in a given range of a string.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let numberOfMatches = regex.numberOfMatches(in: string, options: [], range: NSRange(location: 0, length: string.utf16.count))
///
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSUInteger numberOfMatches = [regex numberOfMatchesInString:string
/// options:0
/// range:NSMakeRange(0, [string length])];
/// ```
/// }
/// }
///
///
/// If you are interested only in the overall range of the first match, the ``rangeOfFirstMatch(in:options:range:)`` method provides it for you.  Some regular expressions (though not the example pattern) can successfully match a zero-length range, so the comparison of the resulting range with `{NSNotFound, 0}` is the most reliable way to determine whether there was a match or not.
///
/// The example regular expression contains two capture groups, corresponding to the two sets of parentheses, one for the first letter, and one for the second.  If you are interested in more than just the overall matched range, you want to obtain an ``NSTextCheckingResult`` object corresponding to a given match.  This object provides information about the overall matched range, via its ``NSTextCheckingResult/range`` property, and also supplies the capture group ranges, via the ``NSTextCheckingResult/range(at:)`` method.  The first capture group range is given by `[result rangeAtIndex:1]`, the second by `[result rangeAtIndex:2]`.  Sending a result the  ``NSTextCheckingResult/range(at:)`` message and passing `0` is equivalent to `[result range]`.
///
/// If the result returned is non-`nil`, then `[result range]` will always be a valid range, so it is not necessary to compare it against `{NSNotFound, 0}`.  However, for some regular expressions (though not the example pattern) some capture groups may or may not participate in a given match.  If a given capture group does not participate in a given match, then `[result rangeAtIndex:idx]` will return `{NSNotFound, 0}`.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let rangeOfFirstMatch = regex.rangeOfFirstMatch(in: string, options: [], range: NSRange(location: 0, length: string.utf16.count))
/// if rangeOfFirstMatch.location != NSNotFound {
/// let substringForFirstMatch = (string as NSString).substring(with: rangeOfFirstMatch)
/// }
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSRange rangeOfFirstMatch = [regex rangeOfFirstMatchInString:string options:0 range:NSMakeRange(0, [string length])];
/// if (!NSEqualRanges(rangeOfFirstMatch, NSMakeRange(NSNotFound, 0))) {
/// NSString *substringForFirstMatch = [string substringWithRange:rangeOfFirstMatch];
/// }
/// ```
/// }
/// }
///
///
/// The ``matches(in:options:range:)`` returns all the matching results.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let matches = regex.matches(in: string, options: [], range: NSRange(location: 0, length: string.utf16.count))
/// for match in matches {
/// let matchRange = match.range
/// let firstHalfRange = match.range(at: 1)
/// let secondHalfRange = match.range(at: 2)
/// }
///
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSArray *matches = [regex matchesInString:string
/// options:0
/// range:NSMakeRange(0, [string length])];
/// for (NSTextCheckingResult *match in matches) {
/// NSRange matchRange = [match range];
/// NSRange firstHalfRange = [match rangeAtIndex:1];
/// NSRange secondHalfRange = [match rangeAtIndex:2];
/// }
/// ```
/// }
/// }
///
///
///
///
/// The ``firstMatch(in:options:range:)`` method is similar to ``matches(in:options:range:)`` but it returns only the first match.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// if let match = regex.firstMatch(in: string, options: [], range: NSRange(location: 0, length: string.utf16.count)) {
/// let matchRange = match.range
/// let firstHalfRange = match.range(at: 1)
/// let secondHalfRange = match.range(at: 2)
/// }
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSTextCheckingResult *match = [regex firstMatchInString:string
/// options:0
/// range:NSMakeRange(0, [string length])];
/// if (match) {
/// NSRange matchRange = [match range];
/// NSRange firstHalfRange = [match rangeAtIndex:1];
/// NSRange secondHalfRange = [match rangeAtIndex:2];
/// }
///
/// ```
/// }
/// }
///
///
/// The Block enumeration method ``enumerateMatches(in:options:range:using:)`` is the most general and flexible of the matching methods of `NSRegularExpression`.  It allows you to iterate through matches in a string, performing arbitrary actions on each as specified by the code in the Block and to stop partway through if desired.  In the following example case, the iteration is stopped after a certain number of matches have been found.
///
/// If neither of the special options ``MatchingOptions/reportProgress`` or ``MatchingOptions/reportCompletion`` is specified, then the result argument to the Block is guaranteed to be non-`nil`, and as mentioned before, it is guaranteed to have a valid overall range.  See ``MatchingOptions`` for the significance of ``MatchingOptions/reportProgress`` or ``MatchingOptions/reportCompletion``.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// var count = 0
/// regex.enumerateMatches(in: string, options: [], range: NSRange(location: 0, length: string.utf16.count)) { match, flags, stop in
/// guard let match = match else { return }
///
/// let matchRange = match.range
/// let firstHalfRange = match.range(at: 1)
/// let secondHalfRange = match.range(at: 2)
/// count += 1
/// if count >= 100 {
/// stop = true
/// }
/// }
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// __block NSUInteger count = 0;
/// [regex enumerateMatchesInString:string options:0 range:NSMakeRange(0, [string length]) usingBlock:^(NSTextCheckingResult *match, NSMatchingFlags flags, BOOL *stop){
/// NSRange matchRange = [match range];
/// NSRange firstHalfRange = [match rangeAtIndex:1];
/// NSRange secondHalfRange = [match rangeAtIndex:2];
/// if (++count >= 100) *stop = YES;
/// }];
/// ```
/// }
/// }
///
///
///
///
/// `NSRegularExpression` also provides simple methods for performing find-and-replace operations on a string.  The following example returns a modified copy, but there is a corresponding method for modifying a mutable string in place.  The template specifies what is to be used to replace each match, with `$0` representing the contents of the overall matched range, `$1` representing the contents of the first capture group, and so on.  In this case, the template reverses the two letters of the word.
///
///
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let modifiedString = regex.stringByReplacingMatches(in: string, options: [], range: NSRange(location: 0, length: string.utf16.count), withTemplate: "$2$1")
///
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSString *modifiedString = [regex stringByReplacingMatchesInString:string
/// options:0
/// range:NSMakeRange(0, [string length])
/// withTemplate:@"$2$1"];
/// ```
/// }
/// }
///
///
/// ### Concurrency and Thread Safety
///
/// `NSRegularExpression` is designed to be immutable and thread safe, so that a single instance can be used in matching operations on multiple threads at once.  However, the string on which it is operating should not be mutated during the course of a matching operation, whether from another thread or from within the Block used in the iteration.
///
/// ### Regular Expression Syntax
///
/// The following tables describe the character expressions used by the regular expression to match patterns within a string, the pattern operators that specify how many times a pattern is matched and additional matching restrictions, and the last table specifies flags that can be included in the regular expression pattern that specify search behavior over multiple lines (these flags can also be specified using the ``Options`` option flags.
///
/// #### Regular Expression Metacharacters
///
/// Table 1: Character sequences used to match characters within a string.
///
/// | Character Expression | Description |
/// |---|---|
/// | `\a` | Match a BELL, `\u0007` |
/// | `\A` | Match at the beginning of the input. Differs from `^` in that `\A` will not match after a new line within the input. |
/// | `\b, outside of a [Set]` | Match if the current position is a word boundary. Boundaries occur at the transitions between word (`\w`) and non-word (`\W`) characters, with combining marks ignored. For better word boundaries, see ``Options/useUnicodeWordBoundaries``. |
/// | `\b, within a [Set]` | Match a BACKSPACE, `\u0008`. |
/// | `\B` | Match if the current position is not a word boundary. |
/// | `\cX` | Match a `control-X` character |
/// | `\d` | Match any character with the Unicode General Category of Nd (Number, Decimal Digit.) |
/// | `\D` | Match any character that is not a decimal digit. |
/// | `\e` | Match an `ESCAPE`, `\u001B`. |
/// | `\E` | Terminates a `\Q ... \E` quoted sequence. |
/// | `\f` | Match a FORM FEED, `\u000C`. |
/// | `\G` | Match if the current position is at the end of the previous match. |
/// | `\n` | Match a `LINE FEED`, `\u000A`. |
/// | `\N{`_UNICODE CHARACTER NAME_`}` | Match the named character. |
/// | `\p{`_UNICODE PROPERTY NAME_`}` | Match any character with the specified Unicode Property. |
/// | `\P{`_UNICODE PROPERTY NAME_`}` | Match any character not having the specified Unicode Property. |
/// | `\Q` | Quotes all following characters until `\E`. |
/// | `\r` | Match a CARRIAGE RETURN, \u000D. |
/// | `\s` | Match a white space character. White space is defined as [\t\n\f\r\p{Z}]. |
/// | `\S` | Match a non-white space character. |
/// | `\t` | Match a HORIZONTAL TABULATION, `\u0009`. |
/// | `\u`_hhhh_ | Match the character with the hex value _hhhh_. |
/// | `\U`_hhhhhhhh_ | Match the character with the hex value _hhhhhhhh_. Exactly eight hex digits must be provided, even though the largest Unicode code point is `\U0010ffff`. |
/// | `\w` | Match a word character. Word characters are [\p{Ll}\p{Lu}\p{Lt}\p{Lo}\p{Nd}]. |
/// | `\W` | Match a non-word character. |
/// | `\x{`_hhhh_`}` | Match the character with hex value _hhhh_. From one to six hex digits may be supplied. |
/// | `\x`_hh_ | Match the character with two digit hex value _hh_. |
/// | `\X` | Match a Grapheme Cluster. |
/// | `\Z` | Match if the current position is at the end of input, but before the final line terminator, if one exists. |
/// | `\z` | Match if the current position is at the end of input. |
/// | `\`_n_ | Back Reference. Match whatever the _n_th capturing group matched. _n_ must be a number `≥ 1` and `≤` total number of capture groups in the pattern. |
/// | `\0`_ooo_ | Match an Octal character.  _ooo_ is from one to three octal digits.  `0377` is the largest allowed Octal character.  The leading zero is required; it distinguishes Octal constants from back references. |
/// | `[`_pattern_`]` | Match any one character from the pattern. |
/// | `.` | Match any character. See ``Options/dotMatchesLineSeparators`` and the `s` character expression in Table 4. |
/// | `^` | Match at the beginning of a line. See ``Options/anchorsMatchLines`` and the `\m` character expression in Table 4. |
/// | `$` | Match at the end of a line. See ``Options/anchorsMatchLines`` and the `m` character expression in Table 4. |
/// | `\` | Quotes the following character. Characters that must be quoted to be treated as literals are `* ? + [ ( ) { } ^ $ | \ . /` |
///
///
/// #### Regular Expression Operators
///
/// Table 2: Regular expression operators.
///
/// | Operator | Description |
/// |---|---|
/// | `|` | Alternation. _A_`|`_B_ matches either _A_ or _B_. |
/// | `*` | Match `0` or more times. Match as many times as possible. |
/// | `+` | Match `1` or more times. Match as many times as possible. |
/// | `?` | Match zero or one times. Prefer one. |
/// | `{`_n_`}` | Match exactly _n_ times. |
/// | `{`_n_`,}` | Match at least _n_ times. Match as many times as possible. |
/// | `{`_n_`,`_m_`}` | Match between _n_ and _m_ times. Match as many times as possible, but not more than _m_. |
/// | `*?` | Match `0` or more times. Match as few times as possible. |
/// | `+?` | Match 1 or more times. Match as few times as possible. |
/// | `??` | Match zero or one times. Prefer zero. |
/// | `{`_n_`}?` | Match exactly n times. |
/// | `{`_n_`,}?` | Match at least n times, but no more than required for an overall pattern match. |
/// | `{`_n_`,`_m_`}?` | Match between n and m times. Match as few times as possible, but not less than n. |
/// | `*+` | Match 0 or more times. Match as many times as possible when first encountered. Do not retry with fewer, even if overall match fails (possessive match). |
/// | `++` | Match 1 or more times (possessive match). |
/// | `?+` | Match zero or one times (possessive match). |
/// | `{`_n_`}+` | Match exactly _n_ times. |
/// | `{`_n_`,}+` | Match at least _n_ times (possessive match). |
/// | `{`_n_`,`_m_`}+` | Match between _n_ and _m_ times (possessive match). |
/// | `(`_..._`)` | Capturing parentheses. Range of input that matched the parenthesized subexpression is available after the match. |
/// | `(?:`_..._`)` | Non-capturing parentheses. Groups the included pattern, but does not provide capturing of matching text. Somewhat more efficient than capturing parentheses. |
/// | `(?>`_..._`)` | Atomic-match parentheses. First match of the parenthesized subexpression is the only one tried; if it does not lead to an overall pattern match, back up the search for a match to a position before the "`(?>`" |
/// | `(?# ... )` | Free-format comment `(?# comment )`. |
/// | `(?= ... )` | Look-ahead assertion. True if the parenthesized pattern matches at the current input position, but does not advance the input position. |
/// | `(?! ... )` | Negative look-ahead assertion. True if the parenthesized pattern does not match at the current input position. Does not advance the input position. |
/// | `(?<= ... )` | Look-behind assertion. True if the parenthesized pattern matches text preceding the current input position, with the last character of the match being the input character just before the current position. Does not alter the input position. The length of possible strings matched by the look-behind pattern must not be unbounded (no \* or + operators.) |
/// | `(?<! ... )` | Negative Look-behind assertion. True if the parenthesized pattern does not match text preceding the current input position, with the last character of the match being the input character just before the current position. Does not alter the input position. The length of possible strings matched by the look-behind pattern must not be unbounded (no \* or + operators.) |
/// | `(?ismwx-ismwx:` `...` `)` | Flag settings. Evaluate the parenthesized expression with the specified flags enabled or -disabled. The flags are defined in <doc:#Flag-Options>. |
/// | `(?ismwx-ismwx)` | Flag settings. Change the flag settings. Changes apply to the portion of the pattern following the setting. For example, (?i) changes to a case insensitive match.The flags are defined in <doc:#Flag-Options>. |
///
///
/// #### Template Matching Format
///
/// The `NSRegularExpression` class provides find-and-replace methods for both immutable and mutable strings using the technique of template matching.
///
/// Table 3: Find-and-replace syntax.
///
/// | Character | Descriptions |
/// |---|---|
/// | `$`_n_ | The text of capture group n will be substituted for $_n_. _n_ must be `>= 0` and not greater than the number of capture groups. A `$` not followed by a digit has no special meaning, and will appear in the substitution text as itself, a `$`. |
/// | `\` | Treat the following character as a literal, suppressing any special meaning. Backslash escaping in substitution text is only required for '$' and '\', but may be used on any other character without bad effects. |
///
///
/// The replacement string is treated as a template, with `$0` being replaced by the contents of the matched range, `$1` by the contents of the first capture group, and so on.  Additional digits beyond the maximum required to represent the number of capture groups will be treated as ordinary characters, as will a `$` not followed by digits.  Backslash will escape both `$` and `\`.
///
/// #### Flag Options
///
/// The following flags control various aspects of regular expression matching. These flag values may be specified within the pattern using the `(?ismx-ismx)` pattern options.  Equivalent behaviors can be specified for the entire pattern when an `NSRegularExpression` is initialized, using the ``Options`` option flags.
///
/// Table 4: Regular expression matching flags.
///
/// | Flag (Pattern) | Description |
/// |---|---|
/// | i | If set, matching will take place in a case-insensitive manner. |
/// | x | If set, allow use of white space and #comments within patterns |
/// | s | If set, a "`.`" in a pattern will match a line terminator in the input text. By default, it will not. Note that a `carriage-return / line-feed pair` in text behave as a single line terminator, and will match a single "`.`" in a regular expression pattern |
/// | m | Control the behavior of "`^`" and "`$`" in a pattern. By default these will only match at the start and end, respectively, of the input text. If this flag is set, "`^`" and "`$`" will also match at the start and end of each line within the input text. |
/// | w | Controls the behavior of `\b` in a pattern. If set, word boundaries are found according to the definitions of word found in Unicode UAX 29, Text Boundaries. By default, word boundaries are identified by means of a simple classification of characters as either "word" or "non-word", which approximates traditional regular expression behavior. The results obtained with the two options can be quite different in runs of spaces and other non-word characters. |
///
///
/// ### Performance
///
/// `NSRegularExpression` implements a nondeterministic finite automaton matching engine. As such, complex regular expression patterns containing multiple `*` or `+` operators may result in poor performance when attempting to perform matches — particularly failing to match a given input. For more information, see the [“Performance Tips” section of the ICU User Guide](http://userguide.icu-project.org/strings/regexp#TOC-Performance-Tips).
///
/// ### ICU License
///
/// Tables 1, 2, 3, and 4 are reproduced from the ICU User Guide, Copyright (c) 2000 - 2009 IBM and Others, which are licensed under the following terms:
///
/// COPYRIGHT AND PERMISSION NOTICE
///
/// Copyright (c) 1995-2009 International Business Machines Corporation and others. All rights reserved.
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, provided that the above copyright notice(s) and this permission notice appear in all copies of the Software and that both the above copyright notice(s) and this permission notice appear in supporting documentation.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
///
/// Except as contained in this notice, the name of a copyright holder shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization of the copyright holder.
///
/// All trademarks and registered trademarks mentioned herein are the property of their respective owners.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0))
@interface NSRegularExpression : NSObject <NSCopying, NSSecureCoding> {
    @protected   // all instance variables are private
    NSString *_pattern;
    NSUInteger _options;
    void *_internal;
    int32_t _checkout;
}

/// Creates an NSRegularExpression instance with the specified regular expression pattern and options.
///
/// - Parameter pattern: The regular expression pattern to compile.
/// - Parameter options: The matching options. See `NSRegularExpressionOptions` for possible values. The values can be combined using the C-bitwise `OR` operator.
/// - Parameter error: An out value that returns any error encountered during initialization. Returns an `NSError` object if the regular expression pattern is invalid; otherwise returns `nil`.
/// - Returns: An instance of `NSRegularExpression` for the specified regular expression and options.
+ (nullable NSRegularExpression *)regularExpressionWithPattern:(NSString *)pattern options:(NSRegularExpressionOptions)options error:(NSError **)error;
/// Returns an initialized NSRegularExpression instance with the specified regular expression pattern and options.
///
/// - Parameter pattern: The regular expression pattern to compile.
/// - Parameter options: The regular expression options that are applied to the expression during matching. See `NSRegularExpressionOptions` for possible values.
/// - Parameter error: An out value that returns any error encountered during initialization. Returns an `NSError` object if the regular expression pattern is invalid; otherwise returns `nil`.
/// - Returns: An instance of `NSRegularExpression` for the specified regular expression and options.
- (nullable instancetype)initWithPattern:(NSString *)pattern options:(NSRegularExpressionOptions)options error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/// Returns the regular expression pattern.
@property (readonly, copy) NSString *pattern;
/// Returns the options used when the regular expression option was created.
///
/// The options property specifies aspects of the regular expression matching that are always used when matching the regular expression. For example, if the expression is case sensitive, allows comments, ignores metacharacters, etc.
@property (readonly) NSRegularExpressionOptions options;
/// Returns the number of capture groups in the regular expression.
///
/// A capture group consists of each possible match within a regular expression. Each capture group can then be used in a replacement template to insert that value into a replacement string.
///
/// This value puts a limit on the values of `n` for `$n` in templates, and it determines the number of ranges in the returned `NSTextCheckingResult` instances returned in the match methods.
@property (readonly) NSUInteger numberOfCaptureGroups;

/// Returns a string by adding backslash escapes as necessary to protect any characters that would match as pattern metacharacters.
///
/// - Parameter string: The string.
/// - Returns: The escaped string.
///
/// Returns a string by adding backslash escapes as necessary to the given string, to escape any characters that would otherwise be treated as pattern metacharacters. You typically use this method to match on a particular string within a larger pattern.
+ (NSString *)escapedPatternForString:(NSString *)string;

@end


/// The matching options constants specify the reporting, completion and matching rules to the expression matching methods.
typedef NS_OPTIONS(NSUInteger, NSMatchingOptions) {
   /// Call the Block periodically during long-running match operations. This option has no effect for methods other than `enumerateMatchesInString:options:range:usingBlock:`.
   NSMatchingReportProgress         = 1 << 0,
   /// Call the Block once after the completion of any matching. This option has no effect for methods other than `enumerateMatchesInString:options:range:usingBlock:`.
   NSMatchingReportCompletion       = 1 << 1,
   /// Specifies that matches are limited to those at the start of the search range.
   NSMatchingAnchored               = 1 << 2,
   /// Specifies that matching may examine parts of the string beyond the bounds of the search range, for purposes such as word boundary detection, lookahead, etc. This constant has no effect if the search range contains the entire string.
   NSMatchingWithTransparentBounds  = 1 << 3,
   /// Specifies that `^` and `$` will not automatically match the beginning and end of the search range, but will still match the beginning and end of the entire string. This constant has no effect if the search range contains the entire string.
   NSMatchingWithoutAnchoringBounds = 1 << 4
};

/// Set by the Block as the matching progresses, completes, or fails. Used by the method `enumerateMatchesInString:options:range:usingBlock:`.
typedef NS_OPTIONS(NSUInteger, NSMatchingFlags) {
   /// Set when the Block is called to report progress during a long-running match operation.
   NSMatchingProgress               = 1 << 0,
   /// Set when the Block is called after matching has completed.
   NSMatchingCompleted              = 1 << 1,
   /// Set when the current match operation reached the end of the search range.
   NSMatchingHitEnd                 = 1 << 2,
   /// Set when the current match depended on the location of the end of the search range.
   NSMatchingRequiredEnd            = 1 << 3,
   /// Set when matching failed due to an internal error.
   NSMatchingInternalError          = 1 << 4
};

@interface NSRegularExpression (NSMatching)

/// Enumerates the string allowing the Block to handle each regular expression match.
///
/// - Parameter string: The string.
/// - Parameter options: The matching options to report. See `NSMatchingOptions` for the supported values.
/// - Parameter range: The range of the string to test.
/// - Parameter block: The Block enumerates the matches of the regular expression in the string. The block takes three arguments: `result` (an `NSTextCheckingResult` specifying the match), `flags` (the current state of matching progress), and `stop` (a reference to a Boolean value that the Block can set to `YES` to stop further processing).
///
/// This method is the fundamental matching method for regular expressions and is suitable for overriding by subclassers. There are additional convenience methods for returning all the matches as an array, the total number of matches, the first match, and the range of the first match.

- (void)enumerateMatchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range usingBlock:(void (NS_NOESCAPE ^)(NSTextCheckingResult * _Nullable result, NSMatchingFlags flags, BOOL *stop))block;

/// Returns an array containing all the matches of the regular expression in the string.
///
/// - Parameter string: The string to search.
/// - Parameter options: The matching options to use. See `NSMatchingOptions` for possible values.
/// - Parameter range: The range of the string to search.
/// - Returns: An array of `NSTextCheckingResult` objects. Each result gives the overall matched range via its `range` property, and the range of each individual capture group via its `rangeAtIndex:` method. The range {`NSNotFound`, 0} is returned if one of the capture groups did not participate in this particular match.
- (NSArray<NSTextCheckingResult *> *)matchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;
/// Returns the number of matches of the regular expression within the specified range of the string.
///
/// - Parameter string: The string to search.
/// - Parameter options: The matching options to use. See `NSMatchingOptions` for possible values.
/// - Parameter range: The range of the string to search.
/// - Returns: The number of matches of the regular expression.
- (NSUInteger)numberOfMatchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;
/// Returns the first match of the regular expression within the specified range of the string.
///
/// - Parameter string: The string to search.
/// - Parameter options: The matching options to use. See `NSMatchingOptions` for possible values.
/// - Parameter range: The range of the string to search.
/// - Returns: An `NSTextCheckingResult` object. This result gives the overall matched range via its `range` property, and the range of each individual capture group via its `rangeAtIndex:` method. The range {`NSNotFound`, 0} is returned if one of the capture groups did not participate in this particular match.
- (nullable NSTextCheckingResult *)firstMatchInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;
/// Returns the range of the first match of the regular expression within the specified range of the string.
///
/// - Parameter string: The string to search.
/// - Parameter options: The matching options to use. See `NSMatchingOptions` for possible values.
/// - Parameter range: The range of the string to search.
/// - Returns: The range of the first match. Returns `{NSNotFound, 0}` if no match is found.
- (NSRange)rangeOfFirstMatchInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;

@end


@interface NSRegularExpression (NSReplacement)

/// Returns a new string containing matching regular expressions replaced with the template string.
///
/// - Parameter string: The string to search for values within.
/// - Parameter options: The matching options to use. See `NSMatchingOptions` for possible values.
/// - Parameter range: The range of the string to search.
/// - Parameter templ: The substitution template used when replacing matching instances.
/// - Returns: A string with matching regular expressions replaced by the template string.
///
/// The replacement is treated as a template, with `$0` being replaced by the contents of the matched range, `$1` by the contents of the first capture group, and so on. Additional digits beyond the maximum required to represent the number of capture groups will be treated as ordinary characters, as will a `$` not followed by digits. Backslash will escape both `$` and itself.
- (NSString *)stringByReplacingMatchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range withTemplate:(NSString *)templ;
/// Replaces regular expression matches within the mutable string using the template string.
///
/// - Parameter string: The mutable string to search and replace values within.
/// - Parameter options: The matching options to use. See `NSMatchingOptions` for possible values.
/// - Parameter range: The range of the string to search.
/// - Parameter templ: The substitution template used when replacing matching instances.
/// - Returns: The number of matches.
- (NSUInteger)replaceMatchesInString:(NSMutableString *)string options:(NSMatchingOptions)options range:(NSRange)range withTemplate:(NSString *)templ;

/// Used to perform template substitution for a single result for clients implementing their own replace functionality.
///
/// - Parameter result: The result of the single match.
/// - Parameter string: The string from which the result was matched.
/// - Parameter offset: The offset to be added to the location of the result in the string.
/// - Parameter templ: The replacement template.
/// - Returns: A replacement string.
///
/// For clients implementing their own replace functionality, this is a method to perform the template substitution for a single result, given the string from which the result was matched, an offset to be added to the location of the result in the string (for example, in cases that modifications to the string moved the result since it was matched), and a replacement template.
- (NSString *)replacementStringForResult:(NSTextCheckingResult *)result inString:(NSString *)string offset:(NSInteger)offset template:(NSString *)templ;

/// Returns a template string by adding backslash escapes as necessary to protect any characters that would match as pattern metacharacters.
///
/// - Parameter string: The template string.
/// - Returns: The escaped template string.
///
/// Returns a string by adding backslash escapes as necessary to the given string, to escape any characters that would otherwise be treated as template metacharacters.
+ (NSString *)escapedTemplateForString:(NSString *)string;

@end

API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0))
/// A specialized regular expression object that matches natural language text for predefined data patterns.
///
/// Find dates, addresses, links, phone numbers, and transit information in natural language text with `NSDataDetector`.
///
/// `NSDataDetector` returns the results of matching content in ``NSTextCheckingResult`` objects. The ``NSTextCheckingResult`` objects that `NSDataDetector` returns are different from those that ``NSRegularExpression`` returns. The results are one of the data detector's types and contain the corresponding properties. For example, results of type ``NSTextCheckingResult/CheckingType/date`` have a ``NSTextCheckingResult/date``, ``NSTextCheckingResult/timeZone``, and ``NSTextCheckingResult/duration``; and results of type ``NSTextCheckingResult/CheckingType/link`` have a ``NSTextCheckingResult/url``.
///
/// > Important:
/// > Don't use `NSDataDetector` to validate data. `NSDataDetector` discards potential matches in case of uncertainty. Use a class specific to the type of data for validation instead. For example, attempt to instantiate a ``URL`` object using ``URL/init(string:)`` to validate a URL string. A valid URL string returns an instance of ``URL``, while an invalid URL string returns <doc://com.apple.documentation/documentation/objectivec/nil-227m0>.
///
/// ### Examples
///
/// The following shows several graduated examples of using the `NSDataDetector` class.
///
/// This code fragment creates a data detector that finds URL links and phone numbers. If an error occurs, it returns in `error`.
///
/// ```objc
/// NSError *error = nil;
/// NSDataDetector *detector = [NSDataDetector dataDetectorWithTypes:NSTextCheckingTypeLink|NSTextCheckingTypePhoneNumber
/// error:&error];
/// ```
///
///
/// After creating the data detector instance, you can determine the number of matches within a range of a string using the `NSRegularExpression` method ``NSRegularExpression/numberOfMatches(in:options:range:)``.
///
/// ```objc
/// NSUInteger numberOfMatches = [detector numberOfMatchesInString:string
/// options:0
/// range:NSMakeRange(0, [string length])];
/// ```
///
///
/// If you're interested only in the overall range of the first match, the ``NSRegularExpression/numberOfMatches(in:options:range:)`` method provides it.  However, with data detectors, this is less likely than with regular expressions because clients are usually interested in additional information as well.
///
/// The additional information available depends on the type of the result.  For results of type ``NSTextCheckingResult/CheckingType/link``, it's the `URL` property that's significant.  For results of type `NSTextCheckingTypePhoneNumber` , it's the `phoneNumber` property instead.
///
/// The ``NSRegularExpression/matches(in:options:range:)`` method is similar to ``NSRegularExpression/firstMatch(in:options:range:)``, except that it returns all matches rather than only the first. The following code fragment finds all the matches for links and phone numbers in a string:
///
/// ```objc
/// NSArray *matches = [detector matchesInString:string
/// options:0
/// range:NSMakeRange(0, [string length])];
/// for (NSTextCheckingResult *match in matches) {
/// NSRange matchRange = [match range];
/// if ([match resultType] == NSTextCheckingTypeLink) {
/// NSURL *url = [match URL];
/// } else if ([match resultType] == NSTextCheckingTypePhoneNumber) {
/// NSString *phoneNumber = [match phoneNumber];
/// }
/// }
/// ```
///
///
/// The `NSRegularExpression` block object enumerator is the most general and flexible of the matching methods.  It allows you to iterate through matches in a string, performing arbitrary actions on each as specified by the code in the block, and to stop partway through if desired. In the following code fragment, the iteration stops after finding a certain number of matches:
///
/// ```objc
/// __block NSUInteger count = 0;
/// [detector enumerateMatchesInString:string
/// options:0
/// range:NSMakeRange(0, [string length])
/// usingBlock:^(NSTextCheckingResult *match, NSMatchingFlags flags, BOOL *stop){
/// NSRange matchRange = [match range];
/// if ([match resultType] == NSTextCheckingTypeLink) {
/// NSURL *url = [match URL];
/// } else if ([match resultType] == NSTextCheckingTypePhoneNumber) {
/// NSString *phoneNumber = [match phoneNumber];
/// }
/// if (++count >= 100) *stop = YES;
/// }];
/// ```
///
///
/// > Note:
/// > Only use `NSDataDetector` on natural language text.
/// >
/// > If you expect text to be in a particular format, use an ``Formatter`` or ``ValueTransformer`` subclass instead. For instance, if you're expecting a date field to be an ISO 8601 timestamp, use ``DateFormatter`` to parse that into an ``NSDate`` object.
/// >
/// > If the text is in a machine-readable format, such as XML or JSON, extract the natural language text, such as by using ``XMLParser`` or ``JSONSerialization``, and match on that rather than attempt to match on the entire document.
@interface NSDataDetector : NSRegularExpression {
    @protected   // all instance variables are private
    NSTextCheckingTypes _types;
}

/// NSDataDetector is a specialized subclass of NSRegularExpression. Instead of finding matches to regular expression patterns, it matches items identified by Data Detectors, such as dates, addresses, and URLs. The checkingTypes argument should contain one or more of the types NSTextCheckingTypeDate, NSTextCheckingTypeAddress, NSTextCheckingTypeLink, NSTextCheckingTypePhoneNumber, and NSTextCheckingTypeTransitInformation.
+ (nullable NSDataDetector *)dataDetectorWithTypes:(NSTextCheckingTypes)checkingTypes error:(NSError **)error;
/// Initializes and returns a data detector instance.
///
/// - Parameters:
///   - checkingTypes: The checking types. The supported checking types are a subset of the types ``NSTextCheckingResult/CheckingType``.
///     Those constants can be combined using the C-bitwise OR operator. Currently, the supported data detector checking types are:
///     ``NSTextCheckingResult/CheckingType/date``, ``NSTextCheckingResult/CheckingType/address``,
///     ``NSTextCheckingResult/CheckingType/link``, phone number, and transit information.
///   - error: An out parameter that if an error occurs during initialization contains the encountered error.
/// - Returns: Returns the newly initialized data detector. If an error was encountered returns `nil`, and `error` contains the error.
- (nullable instancetype)initWithTypes:(NSTextCheckingTypes)checkingTypes error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/// The checking types for the data detector.
///
/// The supported subset of checking types are specified in ``NSTextCheckingResult/CheckingType``. Those constants can be combined using the C-bitwise OR operator. Currently, the supported data detector checking types are: ``NSTextCheckingResult/CheckingType/date``, ``NSTextCheckingResult/CheckingType/address``, ``NSTextCheckingResult/CheckingType/link``, phone number, and transit information.
@property (readonly) NSTextCheckingTypes checkingTypes;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
