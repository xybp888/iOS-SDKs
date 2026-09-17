#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextViewportRenderingSurface.h>)
//
//  NSTextViewportRenderingSurface.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <UIKit/UIKitDefines.h>

#pragma mark - NSTextViewportRenderingSurface
/// A protocol that identifies a view or layer as a drawable element for a text layout fragment.
///
/// Typically an `NSView`, `UIView`, or `CALayer`.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0))
@protocol NSTextViewportRenderingSurface <NSObject>

@end

#pragma mark - NSTextViewportRenderingSurfaceKey
/// A protocol that lets you use an object to identify a rendering surface when storing or retrieving it.
///
/// `NSString` and ``NSTextLayoutFragment`` conform to this protocol.
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0), watchos(11.0))
@protocol NSTextViewportRenderingSurfaceKey <NSObject>
@end
#else
#import <UIFoundation/NSTextViewportRenderingSurface.h>
#endif
