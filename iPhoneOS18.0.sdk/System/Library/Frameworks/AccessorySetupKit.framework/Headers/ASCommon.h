/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#pragma once

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

/// Marks an API as exported.
#ifndef AS_EXTERN
#ifdef __cplusplus
#define AS_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define AS_EXTERN extern __attribute__((visibility("default")))
#endif
#endif

/// Work around some projects disabling OS_OBJECT_USE_OBJC by mapping to strong/assign as needed.
#if defined( OS_OBJECT_USE_OBJC ) && OS_OBJECT_USE_OBJC
    #define as_os_ownership        strong
#else
    #define as_os_ownership        assign
#endif

// MARK: == Constants and Types ==

typedef uint16_t ASBluetoothCompanyIdentifier NS_TYPED_EXTENSIBLE_ENUM;

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
