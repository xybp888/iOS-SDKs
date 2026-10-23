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
 @c CPPanelItem is the base class for all items that can be displayed within a panel section.
 Subclasses represent items specific to a particular template context (e.g., @c CPMapPanelItem for map templates).
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPPanelItem : NSObject <NSSecureCoding>

/**
 Whether the item is interactable. Defaults to @c YES.
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 When @c NO, the bottom separator line below this item is not drawn. Defaults to @c YES.
 */
@property (nonatomic) BOOL showsBottomSeparator;

/**
 Any custom user info related to this item.
 */
@property (nullable, nonatomic, strong) id userInfo;

/**
 Initializes a panel item wrapping a @c CPListItem.
 */
- (instancetype)initWithListItem:(CPListItem *)listItem;

/**
 Initializes a panel item wrapping an array of @c CPGridButton objects.
 */
- (instancetype)initWithGridButtons:(NSArray<CPGridButton *> *)gridButtons;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
