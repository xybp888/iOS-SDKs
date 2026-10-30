//
//  CPPanel.h
//  CarPlay
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A type that provides the common behaviors for panels you display on top of your app’s content.

 The `CPPanel` type defines the default behaviors for panels you display in your app. You don’t create or present
 this type directly. Instead, instantiate one of the defined subclasses and present that type from your app’s interface.
 For example, create a ``CPMapPanel`` and configure it with navigation-related data, and present it from a ``CPMapTemplate``
 to overlay that information on top of your custom map.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPPanel : NSObject <NSSecureCoding>

/**
 The maximum number of items the panel is able to display.

 Each panel subtype configures this property with the maximum number of items it’s able to display. When assembling content
 for your panel, check the value of this property to determine precisely how many items the current type of panel supports.
 */
@property (nonatomic, class, readonly) NSInteger maximumPanelItemsCount;

/**
 A Boolean value that indicates whether the panel displays a close button.

 When the value of this property is `true`, the panel displays a close button that the driver can use to dismiss the panel.
 When the value of this property is `false`, you need to dismiss the panel programmatically from your app.
 The default value of this property is `true`.
 */
@property (nonatomic, assign) BOOL showsCloseButton;

@end

NS_ASSUME_NONNULL_END
