//
//  CPPanelListSection.h
//  CarPlay
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CarPlay/CPMapPanelItem.h>

@class CPMapPanelSection;

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPPanelListSection describes a section within a map template overlay page.
 Each section contains a title, a collection of content items, and an optional item selection handler.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPMapPanelSection : NSObject <NSSecureCoding>

/**
 Initializes a section with items conforming to @c CPMapPanelItem.
 Only items that adopt @c CPMapPanelItem are supported when displaying
 panel sections on a @c CPMapTemplate.

 @param title An optional title for the section.
 @param items An array of @c CPMapPanelItem conforming objects to display in the section.
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                        items:(NSArray<CPMapPanelItem *> *)items NS_DESIGNATED_INITIALIZER;

/**
 The title of the section.
 */
@property (nonatomic, copy, nullable) NSString *title;

/**
 The items displayed in this section, or @c nil if the section does not contain items.
 */
@property (nonatomic, copy) NSArray<CPMapPanelItem *> *items;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
