//
//  CKAsset.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An external file that belongs to a record.
///
/// Use assets to incorporate external files into your app's records, such as photos, videos, and binary files. Alternatively, use assets when a field's value is more than a few kilobytes in size. To associate an instance of ``CKAsset`` with a record, assign it to one of its fields.
///
/// - Note: CloudKit stores only an asset's data. If you require its filename, or any other file-system metadata, use one or more separate fields on the record to store it.
///
/// CloudKit stores an asset's data separately from a record that references it, but maintains an association with that record. When you save a record that has an asset, CloudKit saves both the record and the asset to the server. Similarly, when you fetch the record, the server returns the record and the asset.
///
/// When you fetch a record that contains an asset, CloudKit stores the asset's data in a staging area accessible to your app. Use the asset's ``fileURL`` property to access its staged location. The system regularly deletes files in the staging area to reclaim disk space. To avoid this behavior, move the data into your app's container as soon as you fetch it.
///
/// If you don't require the asset when retrieving records, use the operation's `desiredKeys` property to exclude the field. For more information, see ``CKFetchRecordsOperation``, ``CKQueryOperation``, and ``CKFetchRecordZoneChangesOperation``.
///
/// If you no longer require an asset that's on the server, you don't delete it. Instead, orphan the asset by setting any fields that contain the asset to `nil` and then saving the record. CloudKit periodically deletes orphaned assets from the server.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKAsset : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates an asset that references a file.
///
/// - Parameters:
///   - fileURL: The URL of the file that you want to store in CloudKit. You must provide a file URL, and it must not be `nil`.
///
/// - Returns: An asset object that represents the specified file.
///
/// Use this method to initialize new file-based assets that you want to transfer to iCloud. After saving an asset to the server, CloudKit doesn't delete the file at the specified URL. If you no longer need the file, you must delete it yourself. When you subsequently download a record that contains an asset, CloudKit downloads its own copy of the asset data to the local device and provides you with a URL to that file.
///
/// You can assign only one record to the asset that this method returns. If you want multiple records to point to the same file, you must create separate assets for each one.
///
/// - Important: CloudKit saves only the contents of the file and doesn't save the filename or any file-related metadata. To preserve the filename or any file-related metadata, save that data separately in the record.
- (instancetype)initWithFileURL:(NSURL *)fileURL;

/// The URL for accessing the asset.
///
/// After you create an asset, use the URL in this property to access the asset's contents. The URL in this property is different from the one you specify when creating the asset.
///
/// - Note: If a modify operation fails with a ``CKError/serverRecordChanged`` error, CloudKit doesn't download assets for the copy of the server's record that's accessible using the error's ``CKError/serverRecord`` property. In this scenario, ``CKAsset/fileURL`` is `nil` for all of that record's asset fields.
@property (nullable, readonly, copy) NSURL *fileURL;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
