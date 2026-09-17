//
//  NSItemProvider+CKSharingSupport.h
//  CloudKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class CKShare, CKContainer, CKAllowedSharingOptions;

typedef void (^CKSharePreparationCompletionHandler)(CKShare * _Nullable, NSError * _Nullable) NS_SWIFT_UNAVAILABLE("Use the async throwing preparationHandler instead.");
typedef void (^CKSharePreparationHandler)(CKSharePreparationCompletionHandler) NS_SWIFT_UNAVAILABLE("Use the async throwing preparationHandler instead.");

@interface NSItemProvider (CKSharingSupport)

/// Creates and registers a new collaboration object using a collection of records to share.
///
/// - Parameters:
///   - container: A ``CKContainer`` the system uses to coordinate all the interactions between your app and the server.
///   - allowedOptions: The ``CKAllowedSharingOptions``. The standard option is the default.
///   - preparationHandler: The handler the system calls in your app to create a new ``CKShare``.
///
/// Use this method to share a collection of ``CKRecord`` objects that aren’t assigned to an existing ``CKShare``. When the system calls the `preparationHandler`, your app creates a new ``CKShare`` with the appropriate root ``CKRecord`` or ``CKRecordZoneID``.
///
/// After the server successfully saves the share, invoke the ``CKSharePreparationCompletionHandler`` with either the resulting `CKShare` or an `NSError`, if the save failed.
///
/// When the system invokes the share sheet with a `CKShare` registered with this method, it prompts the user to start sharing.
- (void)registerCKShareWithContainer:(CKContainer *)container allowedSharingOptions:(CKAllowedSharingOptions *)allowedOptions preparationHandler:(CKSharePreparationHandler)preparationHandler API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(tvos, watchos) NS_REFINED_FOR_SWIFT;

/// Registers an existing collaboration object on a server.
///
/// - Parameters:
///   - share: An existing ``CKShare`` on the server.
///   - container: A ``CKContainer`` the system uses to coordinate all the interactions between your app and the server.
///   - allowedOptions: The ``CKAllowedSharingOptions``. The standard option is the default.
///
/// Use this method when a ``CKShare`` currently exists on the server. When the system invokes the share sheet with a `CKShare` that you register with this method, it allows the owner to make modifications to the share settings, and allows a participant to view the share settings.
- (void)registerCKShare:(CKShare *)share container:(CKContainer *)container allowedSharingOptions:(CKAllowedSharingOptions *)allowedOptions API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(tvos, watchos) NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
