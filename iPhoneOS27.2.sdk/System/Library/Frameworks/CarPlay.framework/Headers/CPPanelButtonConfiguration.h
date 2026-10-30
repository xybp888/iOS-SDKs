//
//  CPPanelButtonConfiguration.h
//  CarPlay
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CPTextButton;
@class CPButton;

NS_ASSUME_NONNULL_BEGIN

/**
 A type that provides the common behaviors for a button layout in a panel.

 The `CPPanelButtonConfiguration` type defines the default behaviors for button configurations in a panel. You don’t
 create this type directly or use it to configure your panel. Instead, instantiate one of the defined subclasses based on the type
 of panel you’re configuring. For example, create a ``CPMapPanelButtonConfiguration`` object when configuring
 content for a ``CPMapPanel`` type.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPPanelButtonConfiguration : NSObject <NSSecureCoding>

/**
 Initializes the button configuration object with the specified buttons.

 - Parameters:
     - primaryAction: The primary button for the panel. Use this button to specify the default or primary action someone
        might want to perform. The initializer makes a copy of the provided button.
     - secondaryAction: The secondary button for the panel. Use this to specify an additional action someone might want
        to perform. The initializer makes a copy of the provided button, if any.
 - Returns: An initialized panel button configuration object.
 */
- (instancetype)initWithPrimaryAction:(CPTextButton *)primaryAction
                      secondaryAction:(nullable CPTextButton *)secondaryAction NS_DESIGNATED_INITIALIZER;

/**
 The primary action button for the panel.

 Specify the button at initialization time and use this property to retrieve it later.
 */
@property (nonatomic, copy, readonly) CPTextButton *primaryAction;

/**
 An optional action button to display in the panel.

 Specify this button at initialization time and use this property to retrieve it later.
*/
@property (nonatomic, copy, readonly, nullable) CPTextButton *secondaryAction;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
