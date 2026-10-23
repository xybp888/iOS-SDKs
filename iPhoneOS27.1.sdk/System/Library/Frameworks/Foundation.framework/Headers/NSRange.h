/*	NSRange.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSValue.h>
#import <Foundation/NSObjCRuntime.h>

@class NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A structure used to describe a portion of a series, such as characters in a string or objects in an array.
typedef struct NS_SWIFT_SENDABLE _NSRange {
    NSUInteger location;
    NSUInteger length;
} NSRange;

typedef NSRange *NSRangePointer;

/// Creates a new `NSRange` from the specified values.
///
/// - Parameters:
///   - loc: The starting location of the range.
///   - len: The length of the range.
/// - Returns: An `NSRange` with location `loc` and length `len`.
NS_INLINE NSRange NSMakeRange(NSUInteger loc, NSUInteger len) {
    NSRange r;
    r.location = loc;
    r.length = len;
    return r;
}

/// Returns the sum of the location and length of the range.
///
/// - Parameter range: The range to evaluate.
/// - Returns: The sum of the location and length of the range—that is, `range.location` + `range.length`.
NS_INLINE NSUInteger NSMaxRange(NSRange range) {
    return (range.location + range.length);
}

/// Returns a Boolean value that indicates whether a specified position is in a given range.
///
/// - Parameters:
///   - loc: The position to test.
///   - range: The range to test against.
/// - Returns: `YES` if `loc` lies within `range`—that is, if it's greater than or equal to `range.location` and less than `range.location` plus `range.length`.
NS_INLINE BOOL NSLocationInRange(NSUInteger loc, NSRange range) {
    return (!(loc < range.location) && (loc - range.location) < range.length) ? YES : NO;
}

/// Returns a Boolean value that indicates whether two given ranges are equal.
///
/// - Parameters:
///   - range1: The first range to compare.
///   - range2: The second range to compare.
/// - Returns: `YES` if `range1` and `range2` have the same locations and lengths.
NS_INLINE BOOL NSEqualRanges(NSRange range1, NSRange range2) {
    return (range1.location == range2.location && range1.length == range2.length);
}

/// Returns the union of the specified ranges.
FOUNDATION_EXPORT NSRange NSUnionRange(NSRange range1, NSRange range2);
/// Returns the intersection of the specified ranges.
FOUNDATION_EXPORT NSRange NSIntersectionRange(NSRange range1, NSRange range2);
/// Returns a string representation of a range.
FOUNDATION_EXPORT NSString *NSStringFromRange(NSRange range);
/// Returns a range from a textual representation.
FOUNDATION_EXPORT NSRange NSRangeFromString(NSString *aString);

@interface NSValue (NSValueRangeExtensions)

/// Creates a new value object containing the specified Foundation range structure.
///
/// - Parameters:
///   - range: The value for the new object.
/// - Returns: A new value object that contains the range information.
+ (NSValue *)valueWithRange:(NSRange)range;
/// The Foundation range structure representation of the value.
@property (readonly) NSRange rangeValue;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
