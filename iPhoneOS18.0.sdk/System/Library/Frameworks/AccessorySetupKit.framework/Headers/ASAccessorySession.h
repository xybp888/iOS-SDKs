/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#import <AccessorySetupKit/ASCommon.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class ASAccessory;
@class ASAccessorySettings;
@class ASDiscoveryDescriptor;
@class ASAccessoryEvent;
@class ASAccessorySession;
@class ASMigrationDisplayItem;
@class ASPickerDisplayItem;

//===========================================================================================================================
/// Manages accessories.
AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
@interface ASAccessorySession : NSObject

/// Previously selected accessories for this application. To monitor changes listen for `eventHandler`.
@property (readonly, copy, nonatomic) NSArray<ASAccessory *> *accessories;

/// Activate the session with dispatch queue and event handler.
- (void) activateWithQueue:(dispatch_queue_t) queue eventHandler:(void(^)(ASAccessoryEvent *event)) eventHandler
NS_SWIFT_NAME(activate(on:eventHandler:));

/// Stops any operations and breaks retain cycles. The object cannot be used after calling this.
- (void) invalidate;

/// Discover display items in App Extension.
- (void) showPickerWithCompletionHandler:(void(^)(NSError * _Nullable error)) completionHandler
NS_SWIFT_NAME(showPicker(completionHandler:));

/// Discover display items in picker.
- (void) showPickerForDisplayItems:(NSArray<ASPickerDisplayItem *> *) displayItems
				  completionHandler:(void(^)(NSError * _Nullable error)) completionHandler
NS_SWIFT_NAME(showPicker(for:completionHandler:));

/// Finish accessory setup awaiting authorization.
- (void) finishAuthorization:(ASAccessory *) accessory
                    settings:(ASAccessorySettings *) settings
           completionHandler:(void(^)(NSError * _Nullable error)) completionHandler
NS_SWIFT_NAME(finishAuthorization(for:settings:completionHandler:));

/// Fail accessory setup awaiting authorization.
- (void) failAuthorization:(ASAccessory *) accessory
         completionHandler:(void(^)(NSError * _Nullable error)) completionHandler
NS_SWIFT_NAME(failAuthorization(for:completionHandler:));

/// Remove accessory.
- (void) removeAccessory:(ASAccessory *) accessory
       completionHandler:(void(^)(NSError * _Nullable error)) completionHandler
NS_SWIFT_NAME(removeAccessory(_:completionHandler:));

/// Rename accessory.
- (void) renameAccessory:(ASAccessory *) accessory
                 options:(ASAccessoryRenameOptions) renameOptions
       completionHandler:(void(^)(NSError * _Nullable error)) completionHandler
NS_SWIFT_NAME(renameAccessory(_:options:completionHandler:));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
