//
//  CKServerChangeToken.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An opaque token that represents a specific point in a database's history.
///
/// CloudKit uses server change tokens to record significant events in a database's history, such as record creation, modification, and deletion. Using change tokens helps reduce the cost of a fetch operation — both the time to execute the fetch and the overall number of records it returns.
///
/// You don't create change tokens. Instead, ``CKFetchDatabaseChangesOperation`` and ``CKFetchRecordZoneChangesOperation`` provide them during their execution and when they complete. Cache each token as you receive it, overwriting any previous token for the database or record zone you're fetching from. Then, pass the cached token with your next fetch and CloudKit returns only the changes that occur after that point. Don't infer any behavior or order from a token's contents.
///
/// The change tokens that ``CKFetchDatabaseChangesOperation`` provides aren't compatible with ``CKFetchRecordZoneChangesOperation`` and vice versa, so segregate them in your cache.
///
/// Change tokens conform to <doc://com.apple.documentation/documentation/foundation/nssecurecoding> and are safe to cache on-disk, as the following example shows:
///
/// ```swift
/// func writeToken(_ token: CKServerChangeToken, to url: URL) throws {
///     // Use a keyed archiver to securely encode the provided token.
///     let coder = NSKeyedArchiver(requiringSecureCoding: true)
///     coder.encode(token, forKey: "token")
///
///     // Write the encoded data to disk. The caller provides the
///     // location as a file URL.
///     let data = coder.encodedData
///     try data.write(to: url)
/// }
///
/// func readToken(at url: URL) throws -> CKServerChangeToken? {
///     // Create a Data instance with the contents of the file at
///     // the provided URL.
///     let data = try Data(contentsOf: url)
///
///     // Use a keyed unarchiver to decode the token and return
///     // it to the caller.
///     let coder = try NSKeyedUnarchiver(forReadingFrom: data)
///     return coder.decodeObject(of: CKServerChangeToken.self, forKey: "token")
/// }
/// ```
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
NS_SWIFT_SENDABLE
@interface CKServerChangeToken : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
