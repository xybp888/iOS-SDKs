#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIHingeInteraction.h>)
//
//  UIHingeInteraction.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <UIKit/UIInteraction.h>
#import <UIKit/UIHinge.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An update for a `UIHingeInteraction`
UIKIT_EXTERN NS_SWIFT_NAME(UIHingeInteraction.Update) NS_SWIFT_UI_ACTOR API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos)
@interface UIHingeInteractionUpdate : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The current hinge state for the interaction, or `nil` when the interaction leaves a hierarchy that provides hinge updates.
@property (nonatomic, readonly, copy, nullable) UIHinge *hinge;

@end

/// An interaction for observing the hinge state associated with the view's hierarchy.
///
/// Add a `UIHingeInteraction` to a view to receive hinge state updates. The interaction's handler is called when the hinge state changes, or when the interaction
/// moves between hierarchies. When the interaction moves out of a hierarchy that provides hinge updates, the update's `hinge` is nil.
///
///     override func viewDidLoad() {
///         super.viewDidLoad()
///
///         let interaction = UIHingeInteraction { [weak self] _, update in
///             guard let self else { return }
///             // A nil `hinge` indicates the interaction has left a
///             // hierarchy that provides hinge updates.
///             guard let hinge = update.hinge else {
///                 handleHingeUnavailable()
///                 return
///             }
///
///             updateAngleDisplay(with: hinge.angle)
///             updateStatusDisplay(with: hinge.status)
///         }
///
///         view.addInteraction(interaction)
///     }
///
/// In the example above, the current angle and status of the hinge are displayed as the user interacts with the hinge.
UIKIT_EXTERN NS_SWIFT_UI_ACTOR API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos)
@interface UIHingeInteraction : NSObject <UIInteraction>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Creates a new hinge interaction with the provided update handler.
///
/// The handler is invoked with the initial hinge state, and again whenever there is an update. An update can occur due to the hinge changing, or when the interaction
/// moves between hierarchies. The handler is stored and escapes, so take care to avoid retain cycles.
///
/// - Parameter updateHandler: Called with the initial hinge state and on each subsequent update for the interaction.
- (instancetype)initWithUpdateHandler:(void(^)(UIHingeInteraction *, UIHingeInteractionUpdate *))updateHandler NS_DESIGNATED_INITIALIZER;

/// Whether the interaction is enabled.
///
/// While disabled, the interaction's handler is not called for hinge updates, and any updates that occur are not queued. When re-enabled, the handler is called with
/// the current hinge state if one is available.
@property (nonatomic, getter=isEnabled) BOOL enabled;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIHingeInteraction.h>
#endif
