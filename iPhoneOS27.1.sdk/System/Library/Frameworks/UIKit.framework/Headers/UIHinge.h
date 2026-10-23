#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIHinge.h>)
//
//  UIHinge.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The status of an individual hinge
typedef NS_ENUM(NSInteger, UIHingeStatus) {

    /// The status of the hinge is unknown
    UIHingeStatusUnknown = 0,

    /// The hinge is closed
    UIHingeStatusClosed = 1,

    /// The hinge is partially open
    UIHingeStatusPartiallyOpen = 2,

    /// The hinge is open as far as the device allows
    UIHingeStatusFullyOpen = 3,

} NS_SWIFT_NAME(UIHinge.Status) API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos);

/// An object encapsulating the state of a single hinge.
///
/// You observe hinge state by adding a `UIHingeInteraction` to a view and reading it from the update delivered to its handler.
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
@interface UIHinge : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The current status of the hinge
@property (nonatomic, readonly) UIHingeStatus status;

/// The current angle of the hinge, in radians.
///
/// The rate and granularity of angle updates are system policy and can change based on system state, so don't depend on a particular update frequency or
/// precision. If you only need to know whether the hinge is closed, partially open, or fully open, prefer `status` over the angle.
@property (nonatomic, readonly) CGFloat angle;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIHinge.h>
#endif
