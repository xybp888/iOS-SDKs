//  
//  GCEventInteraction.h
//  GameController
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, GCUIEventTypes) {
    GCUIEventTypeNone           = (0U),
    GCUIEventTypeGamepad        = (1U << 0),
};

/**
 *  An interaction that indicates your views's intent to receive game controller
 *  events through the GameController framework.
 *
 *  @discussion
 *  On some platforms controllers can be used to control the general UIKit user
 *  interface and for many views that is the default behavior.  By attaching a
 *  \c GCEventInteraction to one or more of your app's views you get fine
 *  grained control over whether the controller events go through the UIEvent &
 *  UIResponder chain, or if they are decoupled from the UI and all incoming
 *  data is served via Game Controller framework.
 *
 *  On visionOS, while the user is gazing a view with the \c GCEventInteraction,
 *  or one of its subviews, the interaction's \c handledEventTypes property
 *  determines whether the system will deliver game controller events through
 *  the Game Controller framework instead of through the UIEvent & UIResponder
 *  chain.
 */
API_AVAILABLE(macCatalyst(18.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos)
@interface GCEventInteraction : NSObject <UIInteraction>

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 *  The types of game controller events that should be delivered through
 *  the Game Controller framework.
 */
@property (nonatomic, readwrite) GCUIEventTypes handledEventTypes;

@end

NS_ASSUME_NONNULL_END
