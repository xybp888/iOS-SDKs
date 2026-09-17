/*	NSUUID.h
        Copyright (c) 2011-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#if !0
#include <CoreFoundation/CFUUID.h>
#endif
#include <uuid/uuid.h>

/* Note: NSUUID is not toll-free bridged with CFUUID. Use UUID strings to convert between CFUUID and NSUUID, if needed. NSUUIDs are not guaranteed to be comparable by pointer value (as CFUUIDRef is); use isEqual: to compare two NSUUIDs. */

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A universally unique value that can be used to identify types, interfaces, and other items.
///
/// In Swift, this object bridges to ``UUID``; use ``NSUUID`` when you need reference semantics or other Foundation-specific behavior.
///
/// UUIDs (Universally Unique Identifiers), also known as GUIDs (Globally Unique Identifiers) or IIDs (Interface Identifiers), are 128-bit values. UUIDs created by `NSUUID` conform to RFC 4122 version 4 and are created with random bytes.
///
/// The standard format for UUIDs represented in ASCII is a string punctuated by hyphens, for example `68753A44-4D6F-1226-9C60-0050E4C00067`. The hex representation looks, as you might expect, like a list of numerical values preceded by 0x. For example, `0xD7`, `0x36`, `0x95`, `0x0A`, `0x4D`, `0x6E`, `0x12`, `0x26`, `0x80`, `0x3A`, `0x00`, `0x50`, `0xE4`, `0xC0`, `0x00`, `0x67`. Because a UUID is expressed simply as an array of bytes, there are no endianness considerations for different platforms.
///
/// The `NSUUID` class is _not_ toll-free bridged with CoreFoundation's <doc://com.apple.documentation/documentation/corefoundation/cfuuid>. Use UUID strings to convert between `CFUUIDRef` and `NSUUID`, if needed. Two `NSUUID` objects are not guaranteed to be comparable by pointer value (as <doc://com.apple.documentation/documentation/corefoundation/cfuuid> is); use <doc://com.apple.documentation/documentation/objectivec/nsobjectprotocol/isequal(_:)> to compare two `NSUUID` instances.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``UUID`` structure, which bridges to the ``NSUUID`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0))
@interface NSUUID : NSObject <NSCopying, NSSecureCoding>

/// Creates a new autoreleased NSUUID with RFC 4122 version 4 random bytes.
+ (instancetype)UUID;

/// Creates a new NSUUID with RFC 4122 version 4 random bytes.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an NSUUID from a string such as "E621E1F8-C36C-495A-93FC-0C247A3E6E5F". Returns nil for invalid strings.
- (nullable instancetype)initWithUUIDString:(NSString *)string;

/// Creates an NSUUID with the given bytes.
- (instancetype)initWithUUIDBytes:(const uuid_t _Nullable)bytes;

/// Gets the individual bytes of the receiver.
- (void)getUUIDBytes:(uuid_t _Nonnull)uuid;

/// Compares the receiver to another NSUUID in constant time.
- (NSComparisonResult)compare:(NSUUID *)otherUUID API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// The UUID as a string.
///
/// A string containing a formatted UUID for example `E621E1F8-C36C-495A-93FC-0C247A3E6E5F`.
@property (readonly, copy) NSString *UUIDString;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
