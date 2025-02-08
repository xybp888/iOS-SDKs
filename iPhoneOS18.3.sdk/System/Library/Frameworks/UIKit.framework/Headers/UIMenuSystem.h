#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMenuSystem.h>)
//
//  UIMenuSystem.h
//  UIKit
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The command system to build or rebuild.
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIMenuSystem : NSObject

/// The main command system.
@property (class, nonatomic, readonly) UIMenuSystem *mainSystem;

/// The context command system.
@property (class, nonatomic, readonly) UIMenuSystem *contextSystem;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Trigger a rebuild of this system at a suitable time.
- (void)setNeedsRebuild;

/// Trigger a revalidate of this system at a suitable time.
- (void)setNeedsRevalidate;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMenuSystem.h>
#endif
