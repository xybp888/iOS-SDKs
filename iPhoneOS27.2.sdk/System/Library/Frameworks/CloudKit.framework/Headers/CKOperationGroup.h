//
//  CKOperationGroup.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKOperationConfiguration;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that represent possible data transfer sizes.
typedef NS_ENUM(NSInteger, CKOperationGroupTransferSize) {
    /// An unknown transfer size.
    CKOperationGroupTransferSizeUnknown,

    /// A transfer size that represents 1 or more kilobytes.
    CKOperationGroupTransferSizeKilobytes,

    /// A transfer size that represents 1 or more megabytes.
    CKOperationGroupTransferSizeMegabytes,

    /// A transfer size that represents tens of megabytes.
    CKOperationGroupTransferSizeTensOfMegabytes,

    /// A transfer size that represents hundreds of megabytes.
    CKOperationGroupTransferSizeHundredsOfMegabytes,

    /// A transfer size that represents 1 or more gigabytes.
    CKOperationGroupTransferSizeGigabytes,

    /// A transfer size that represents tens of gigabytes.
    CKOperationGroupTransferSizeTensOfGigabytes,

    /// A transfer size that represents hundreds of gigabytes.
    CKOperationGroupTransferSizeHundredsOfGigabytes,
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/// An explicit association between two or more operations.
///
/// In certain situations, you might want to perform several CloudKit operations together. Grouping operations in CloudKit doesn't ensure atomicity.
///
/// For example, when building a Calendar app, you group the following actions:
///
/// - Fetch records from CloudKit, which consists of numerous queries that fetch both new records and records with changes.
/// - Perform incremental fetches of records in response to a push notification.
/// - Update several records when the user saves a calendar event.
///
/// Associate operation groups with operations by setting their ``CKOperation/group`` property. Create a new operation group for each distinct user interaction.
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKOperationGroup : NSObject <NSSecureCoding, NSCopying>

/// Creates an operation group.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation group from a serialized instance.
///
/// - Parameters:
///   - aDecoder: The coder to use when deserializing the group.
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/// The operation group's unique identifier.
///
/// The framework generates this value and it's unique to this operation group. The system sends this identifier to CloudKit, which can use it to identify server-side logs for ``CKOperationGroup``.
@property (readonly, copy, nonatomic) NSString *operationGroupID;
 
/// The default configuration for operations in the group.
///
/// If an operation in the group has its own configuration, that configuration's values override the default configuration's values. For more information, see ``CKOperation/Configuration``.
@property (null_resettable, copy) CKOperationConfiguration *defaultConfiguration;

/// The operation group's name.
///
/// The system sends the name of the operation group to CloudKit to provide aggregate reporting for ``CKOperationGroup``. The name must not include any personal data.
@property (nullable, copy) NSString *name;

/// The number of operations in the operation group.
///
/// This property shows the number of operations that you expect to be in this operation group. It's the developer's responsibility to set this value.
@property (assign) NSUInteger quantity;

/// The estimated size of traffic to upload to CloudKit.
///
/// This property informs the system about the amount of data your app can transfer. An order-of-magnitude estimate is better than no estimate, and accuracy helps performance. The system checks this value when it schedules discretionary network requests.
@property (assign) CKOperationGroupTransferSize expectedSendSize;

/// The estimated size of traffic to download from CloudKit.
///
/// This property informs the system about the amount of data your app can transfer. An order-of-magnitude estimate is better than no estimate, and accuracy helps performance. The system checks this value when it schedules discretionary network requests.
@property (assign) CKOperationGroupTransferSize expectedReceiveSize;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
