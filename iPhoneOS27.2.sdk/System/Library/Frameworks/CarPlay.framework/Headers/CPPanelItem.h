//
//  CPPanelItem.h
//  CarPlay
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CPListItem;
@class CPGridButton;

NS_ASSUME_NONNULL_BEGIN

/**
 A type that provides the common behaviors for items you display in a section of a panel.

 The `CPPanelItem` type defines the default behaviors for content you display in a panel. You don’t create
 this type directly or use it to configure the contents of your panel. Instead, instantiate one of the defined subclasses
 based on the type of panel you’re configuring. For example, create ``CPMapPanelItem`` objects when configuring
 the content for a ``CPMapPanel`` type.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPPanelItem : NSObject <NSSecureCoding>

/**
 A Boolean value that indicates whether the item supports interactions.

 When the value of this property is `true`, the item is enabled and supports interactions. Set the value to
 `false` to disable interactions. The default value of this property is `true`.
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 A Boolean value that indicates whether a separator line appears at the bottom edge of the item.

 When the value of this property is `true`, CarPlay draws a line along the bottom edge of the item to separate it
 from the next item. Set this property to `false` if you don't want to draw the separator. The default value of this
 property is `true`.
 
 When drawing the last section in the map panel, the system doesn't draw a separator line, even if this property
 is `true`. 
 */
@property (nonatomic) BOOL showsBottomSeparator;

/**
 Custom information you want to store with the item.

 Store any app-specific data for the item in this property. For example, you might store a dictionary of keys and values.
 The item maintains a strong reference to the object you specify.
 */
@property (nullable, nonatomic, strong) id userInfo;

/**
 Initialize the item using a list item.

 - Parameters:
     - listItem: The list item with the information to display. The ``CPListItem`` type supports primary and
        secondary text and images.
 - Returns: A panel item configured with the specified list item.
 */
- (instancetype)initWithListItem:(CPListItem *)listItem;

/**
 Initialize the item using one or more grid buttons.

 - Parameters:
     - gridButtons: The grid buttons to display in the item. Specify the buttons in the order you want them to appear.
    Include no more than four grid buttons in the array.
 - Returns: A panel item configured with the specified grid buttons.
 */
- (instancetype)initWithGridButtons:(NSArray<CPGridButton *> *)gridButtons;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
