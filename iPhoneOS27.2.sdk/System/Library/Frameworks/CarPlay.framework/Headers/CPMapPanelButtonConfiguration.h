//
//  CPMapPanelButtonConfiguration.h
//  CarPlay
//
//  Created by Rico Bowman on 5/6/26.
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <CarPlay/CPPanelButtonConfiguration.h>
#import <CarPlay/CPTravelEstimates.h>

@class CPTextButton;
@class CPButton;
@class CPTravelEstimates;

NS_ASSUME_NONNULL_BEGIN

/**
 A type that manages the action buttons and travel estimates in a map panel.

 A `CPMapPanelbuttonConfiguration` object specifies the controls and details to display at the bottom of a ``CPMapPanel``.
 Create this type when to add a primary action button and an optional secondary action button to the bottom of the panel. These
 buttons are separate from your map panel’s section content and remain pinned to the bottom of the panel during scrolling. You can
 also use this type to specify travel estimates you want to keep pinned to the bottom of the panel.

 Instantiate this type and specify it with the rest of the panel content when initializing your ``CPMapPanel`` object. You can’t
 change the button configuration details after you create your map panel.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPMapPanelButtonConfiguration : CPPanelButtonConfiguration

/**
 Initializes the map panel button configuration with the specified action buttons and travel estimates.

 - Parameters:
     - primaryAction: The text button for the primary action.
     - secondaryButton: An optional button you can use to handle a secondary action. The configuration object stores a copy
        of the provided button in the ``CPMapPanelButtonConfiguration/secondaryButton`` property.
     - travelEstimates: The travel estimates to display with the buttons. The configuration object stores a copy of the
        provided travel estimates.
 - Returns: A new map panel button configuration object.
 */
- (instancetype)initWithPrimaryAction:(CPTextButton *)primaryAction
                      secondaryButton:(nullable CPButton *)secondaryButton
                      travelEstimates:(CPTravelEstimates *)travelEstimates;

/**
 The travel estimates to display alongside the action buttons.

 Specify this information at initialization time and access it using this property. 
*/
@property (nonatomic, copy, nullable) CPTravelEstimates *travelEstimates;

/**
 The optional button you use to perform a secondary action.

 Specify this button at initialization time and access it using this property. The value of this property can be `nil`.
*/
@property (nonatomic, copy, readonly, nullable) CPButton *secondaryButton;

@end

NS_ASSUME_NONNULL_END
