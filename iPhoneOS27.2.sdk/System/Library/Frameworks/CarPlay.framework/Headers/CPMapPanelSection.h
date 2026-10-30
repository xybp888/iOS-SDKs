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
 A single section of a map panel that you fill with a title and one or more items.

 The `CPMapPanelSection` class organizes a single section of content in a ``CPMapPanel`` interface. In a navigation app,
 you use map panels to display relevant information such as route options or the location of charging stations on top of your
 custom map. Section objects manage one or more related items you want to display. For example, you might use one section
 to display upcoming charging stations and a different section to display route choices.

 Create a `CPMapPanelSection` object and configure it with the section title and a ``CPMapPanelItem`` object for each
 item you want to display. Add the section to your ``CPMapPanel`` object before showing the panel from your map template.
 If you modify a section after the panel is visible, the system updates the section’s contents in your CarPlay interface.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPMapPanelSection : NSObject <NSSecureCoding>

/**
 Initializes the section with the specified title and items.

 - Parameters:
     - title: The localized title of the section. The system displays this string at the top of the section’s content. The section
        object stores a copy of the provided string. Specify `nil` if you don’t want to display a title for the section.
     - items: The array of items to display in the section. Specify at least one item in this array. The section object stores a
        copy of the provided array.
 - Returns: An initialized section object.
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                        items:(NSArray<CPMapPanelItem *> *)items NS_DESIGNATED_INITIALIZER;

/**
 The localized string to display for the section title.

 Set this property to `nil` if you don’t want to display a title for the section.
 */
@property (nonatomic, copy, nullable) NSString *title;

/**
 The items to display in the section.

 You specify the set of items at initialization time, but can change the items at any time. If you change the value of this property
 while the panel is visible, the system updates your CarPlay interface to reflect the changes. 
 */
@property (nonatomic, copy) NSArray<CPMapPanelItem *> *items;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
