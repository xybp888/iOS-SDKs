/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class ASDiscoveryDescriptor;

//---------------------------------------------------------------------------------------------------------------------------
/*!    @brief        Accessory Setup Options
*/
typedef NS_OPTIONS( NSUInteger, ASPickerDisplayItemSetupOptions )
{
    ASPickerDisplayItemSetupRename                          = ( 1U << 0 ),   // Ask user to rename accessory.
    ASPickerDisplayItemSetupConfirmAuthorization            = ( 1U << 1 ),   // App session finishes accessory authorization.
    ASPickerDisplayItemSetupFinishInApp                     = ( 1U << 2 ),   // Display instruction to finish setup in app after accessory is authorized to use.
} NS_SWIFT_NAME(ASPickerDisplayItem.SetupOptions);

AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASPickerDisplayItem : NSObject

/// NOTE:-  `name` and `productImage` is ignored if display item matched with an already authorized accessory for another app

/// Accessory's display name on picker as title.
@property (readonly, copy, nonatomic) NSString *name;

/// Accessory's product image.
@property (readonly, copy, nonatomic) UIImage *productImage;

/// Accessory discovery parameters.
@property (readonly, copy, nonatomic) ASDiscoveryDescriptor *descriptor;

/// Accessory rename option. `allowsRename` needs to be allowed to update options.
@property (readwrite, assign, nonatomic) ASAccessoryRenameOptions renameOptions;

/// Accessory custom setup options.
@property (readwrite, assign, nonatomic) ASPickerDisplayItemSetupOptions setupOptions;

- (instancetype)initWithName:(NSString *) name productImage:(UIImage *) productImage
        descriptor:(ASDiscoveryDescriptor *) descriptor NS_DESIGNATED_INITIALIZER;

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) new NS_UNAVAILABLE;

@end

// MARK: -
//===========================================================================================================================

AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASMigrationDisplayItem : ASPickerDisplayItem

@property (readwrite, copy, nullable, nonatomic) NSUUID *peripheralIdentifier;

@property (readwrite, copy, nullable, nonatomic) NSString *hotspotSSID;

@end

NS_ASSUME_NONNULL_END
