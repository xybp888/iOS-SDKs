//
//  NSFileProviderError.h
//  FileProvider
//
//  Copyright (c) 2014-2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const NSFileProviderErrorDomain FILEPROVIDER_API_AVAILABILITY_V2;

FOUNDATION_EXPORT NSString * const NSFileProviderErrorCollidingItemKey API_DEPRECATED("NSFileProviderErrorItemKey", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);
FOUNDATION_EXPORT NSString * const NSFileProviderErrorItemKey FILEPROVIDER_API_AVAILABILITY_V3;
FOUNDATION_EXPORT NSString * const NSFileProviderErrorNonExistentItemIdentifierKey FILEPROVIDER_API_AVAILABILITY_V2;

typedef NS_ERROR_ENUM(NSFileProviderErrorDomain, NSFileProviderErrorCode) {
    /** The user credentials cannot be verified */
    NSFileProviderErrorNotAuthenticated  = -1000,

    /** An item already exists with the same parentItemIdentifier and filename (or with a filename differing only in case.)

     \note Please use -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:] to build an error with this code.
     \see -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:]
     */
    NSFileProviderErrorFilenameCollision = -1001,

    /** The value of the sync anchor is too old, and the system must re-sync from scratch */
    NSFileProviderErrorSyncAnchorExpired = -1002,

    /** The value of the page token is too old, and the system must re-sync from scratch */
    NSFileProviderErrorPageExpired        = NSFileProviderErrorSyncAnchorExpired,

    /** The item has not been uploaded because it would push the account over quota */
    NSFileProviderErrorInsufficientQuota = -1003,

    /** Connecting to the servers failed */
    NSFileProviderErrorServerUnreachable = -1004,

    /** The requested item doesn't exist

     \note Please use -[NSError (NSFileProviderError) fileProviderErrorForNonExistentItemWithIdentifier:] to build an error with this code.
     \see -[NSError (NSFileProviderError) fileProviderErrorForNonExistentItemWithIdentifier:]
     */
    NSFileProviderErrorNoSuchItem        = -1005,

    /** The requested version is not the latest version of the file.

     \note Please use -[NSError (NSFileProviderError) fileProviderErrorForOutOfDateItem:] to build an error with this code.
     \see -[NSError (NSFileProviderError) fileProviderErrorForOutOfDateItem:]
     */
    NSFileProviderErrorVersionOutOfDate FILEPROVIDER_API_AVAILABILITY_V3 = -1006,

    /** We're trying to non-recursively delete a non-empty directory
     */
    NSFileProviderErrorDirectoryNotEmpty FILEPROVIDER_API_AVAILABILITY_V3 = -1007,

} FILEPROVIDER_API_AVAILABILITY_V2;

@interface NSError (NSFileProviderError)
+ (instancetype)fileProviderErrorForCollisionWithItem:(NSFileProviderItem)existingItem FILEPROVIDER_API_AVAILABILITY_V2;
+ (instancetype)fileProviderErrorForNonExistentItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier FILEPROVIDER_API_AVAILABILITY_V2;
+ (instancetype)fileProviderErrorForOutOfDateItem:(NSFileProviderItem)updatedVersion NS_SWIFT_NAME(fileProviderErrorForOutOfDateItem(_:)) FILEPROVIDER_API_AVAILABILITY_V3;

@end

NS_ASSUME_NONNULL_END
