#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextViewportLayoutController.h>)
//
//  NSTextViewportLayoutController.h
//  Text Kit
//
//  Copyright (c) 2017-2025, Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <CoreGraphics/CGGeometry.h>
#import <UIKit/NSTextViewportRenderingSurface.h>

@class NSTextRange;
@class NSTextLayoutManager;
@class NSTextContainer;
@class NSTextViewportLayoutController;
@class NSTextLayoutFragment;
@protocol NSTextLocation;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Manages the layout process inside the viewport interacting with its delegate.
///
/// A viewport is a rectangular area within a flipped coordinate system expanding
/// along the y-axis. With text contents, lines advance along the expanding
/// direction typically. It defines the active area where text layout fragments
/// are laid out. The area corresponds to the user visible area with additional
/// over-scroll region in most cases.

#pragma mark NSTextViewportLayoutControllerDelegate
/// The protocol that viewport layout controller delegates implement to manage layout and rendering surfaces.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol NSTextViewportLayoutControllerDelegate <NSObject>
#pragma mark Properties
/// Returns the current viewport bounds, typically the view visible bounds with overdraw.
///
/// - Parameters:
///   - textViewportLayoutController: The viewport layout controller requesting the bounds.
///
/// - Returns: The viewport bounds rect.
- (CGRect)viewportBoundsForTextViewportLayoutController:(NSTextViewportLayoutController *)textViewportLayoutController;

#pragma mark Viewport layout
/// Called when the viewport layout controller lays out a given text layout fragment.
///
/// The delegate should arrange to present the text layout fragment in the UI,
/// e.g. a sublayer or subview. Layout information such as `viewportBounds` on
/// `textViewportLayoutController` is not up-to-date at the point of this call.
///
/// - Parameters:
///   - textViewportLayoutController: The viewport layout controller.
///   - textLayoutFragment: The layout fragment to configure a rendering surface for.
- (void)textViewportLayoutController:(NSTextViewportLayoutController *)textViewportLayoutController configureRenderingSurfaceForTextLayoutFragment:(NSTextLayoutFragment *)textLayoutFragment;

@optional

#pragma mark Layout Process Observation
/// Called when the viewport layout controller is about to layout.
///
/// Layout information on `textViewportLayoutController` is up-to-date at the
/// point of this call.
///
/// - Parameters:
///   - textViewportLayoutController: The viewport layout controller about to layout.
- (void)textViewportLayoutControllerWillLayout:(NSTextViewportLayoutController *)textViewportLayoutController;

/// Called when the viewport layout controller has finished layout.
///
/// Layout information on `textViewportLayoutController` is up-to-date at the
/// point of this call.
///
/// - Parameters:
///   - textViewportLayoutController: The viewport layout controller that finished layout.
- (void)textViewportLayoutControllerDidLayout:(NSTextViewportLayoutController *)textViewportLayoutController;

/// Asks the delegate to cache a rendering surface for later retrieval.
///
/// - Parameters:
///   - textViewportLayoutController: The viewport layout controller.
///   - renderingSurface: The rendering surface to cache.
///   - renderingSurfaceKey: The key identifying the rendering surface.
- (void)textViewportLayoutController:(NSTextViewportLayoutController *)textViewportLayoutController cacheRenderingSurface:(id<NSTextViewportRenderingSurface>)renderingSurface forKey:(id<NSTextViewportRenderingSurfaceKey>)renderingSurfaceKey;

/// Asks the delegate to return a previously cached rendering surface.
///
/// - Parameters:
///   - textViewportLayoutController: The viewport layout controller.
///   - renderingSurfaceKey: The key identifying the rendering surface.
///
/// - Returns: The cached rendering surface, or `nil`.
- (id<NSTextViewportRenderingSurface>)textViewportLayoutController:(NSTextViewportLayoutController *)textViewportLayoutController retrieveCachedRenderingSurfaceForKey:(id<NSTextViewportRenderingSurfaceKey>)renderingSurfaceKey;

/// Triggers relayout of the view.
///
/// - Parameters:
///   - textViewportLayoutController: The viewport layout controller requesting a relayout.
- (void)textViewportLayoutControllerReceivedSetNeedsLayout:(NSTextViewportLayoutController *)textViewportLayoutController;

#pragma mark NSTextViewportRenderingSurface support
/// Returns a rendering surface for the specified text layout fragment.
///
/// Invoked right before
/// `textViewportLayoutController:configureRenderingSurfaceForTextLayoutFragment:`.
/// The returned rendering surface is registered and mapped by
/// ``renderingSurfaceForKey:``.
///
/// - Parameters:
///   - textViewportLayoutController: The viewport layout controller.
///   - textLayoutFragment: The layout fragment needing a rendering surface.
///
/// - Returns: A rendering surface, or `nil`.
- (nullable id <NSTextViewportRenderingSurface>)textViewportLayoutController:(NSTextViewportLayoutController *)textViewportLayoutController renderingSurfaceForTextLayoutFragment:(NSTextLayoutFragment *)textLayoutFragment API_UNAVAILABLE(macos, ios, tvos, visionos, watchos);

@end

#pragma mark NSTextViewportLayoutController
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextViewportLayoutController : NSObject
#pragma mark Initialization
/// Creates a new viewport layout controller with the specified text layout manager.
///
/// - Parameters:
///   - textLayoutManager: The text layout manager providing layout fragments.
- (instancetype)initWithTextLayoutManager:(NSTextLayoutManager *)textLayoutManager NS_DESIGNATED_INITIALIZER;


+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

#pragma mark Properties
/// The viewport layout delegate.
@property (nullable, weak) id <NSTextViewportLayoutControllerDelegate> delegate;

/// The text layout manager for this viewport layout controller.
@property (weak, readonly) NSTextLayoutManager *textLayoutManager;


#pragma mark Viewport layout state
/// The visible bounds of the view, plus the overdraw area.
///
/// Not KVO-compliant.
@property (readonly) CGRect viewportBounds;

/// The text range of the current viewport layout.
///
/// Not KVO-compliant.
@property (nullable, readonly) NSTextRange *viewportRange;

#pragma mark Viewport layout
/// Performs layout in the viewport.
- (void)layoutViewport;

/// Relocates the viewport to start with the specified location.
///
/// This is used to programmatically scroll to the specified location.
///
/// - Parameters:
///   - textLocation: The document location to scroll to.
///
/// - Returns: The suggested viewport anchor point.
- (CGFloat)relocateViewportToTextLocation:(id <NSTextLocation>)textLocation;

/// Adjusts the viewport rect by the specified offset if needed.
///
/// This is used to artificially move the viewport without affecting viewport
/// content. The offset can be both positive and negative.
///
/// - Parameters:
///   - verticalOffset: The vertical offset to adjust by.
- (void)adjustViewportByVerticalOffset:(CGFloat)verticalOffset;

#pragma mark NSTextViewportRenderingSurface support
/// Returns a rendering surface corresponding to the specified key.
///
/// The mapping is registered via the returned rendering surfaces from
/// `textViewportLayoutController:renderingSurfaceForTextLayoutFragment:`. In
/// addition, it can return auxiliary rendering surfaces registered through
/// `addRenderingSurface:key:group:placement:`. The mappings are cleared at the
/// beginning of each ``layoutViewport``.
///
/// - Parameters:
///   - key: The key identifying the rendering surface.
///
/// - Returns: The rendering surface, or `nil`.
- (nullable id <NSTextViewportRenderingSurface>)renderingSurfaceForKey:(id <NSTextViewportRenderingSurfaceKey>)key API_UNAVAILABLE(macos, ios, tvos, visionos, watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextViewportLayoutController.h>
#endif
