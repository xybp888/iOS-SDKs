/*	NSNull.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A singleton object used to represent null values in collection objects that don't allow `nil` values.
///
/// ``NSNull`` is "toll-free bridged" with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfnull>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
NS_SWIFT_SENDABLE
@interface NSNull : NSObject <NSCopying, NSSecureCoding>

/// Returns the singleton instance of `NSNull`.
+ (NSNull *)null;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
