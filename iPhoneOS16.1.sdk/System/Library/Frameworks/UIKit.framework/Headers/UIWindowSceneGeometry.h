#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneGeometry.h>)
//
//  UIWindowSceneGeometry.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIApplication.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(16.0))
@interface UIWindowSceneGeometry : NSObject <NSCopying>

/// Geometry objects are readonly and should only be created by the framework. To set a window scene's geometry, see UIWindowSceneGeometryPreferences and -[UIWindowScene requestGeometryUpdateWithPreferences:].
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) CGRect systemFrame API_AVAILABLE(macCatalyst(16.0)) API_UNAVAILABLE(ios, watchos, tvos);
@property (nonatomic, readonly) UIInterfaceOrientation interfaceOrientation API_UNAVAILABLE(tvos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneGeometry.h>
#endif
