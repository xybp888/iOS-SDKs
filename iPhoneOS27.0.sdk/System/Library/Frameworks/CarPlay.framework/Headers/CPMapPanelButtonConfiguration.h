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

API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPMapPanelButtonConfiguration : CPPanelButtonConfiguration

/**
 Initializes a map panel button configuration with a primary action, optional travel estimates,
 and an optional secondary button.

 @param primaryAction The primary text button for the panel.
 @param secondaryButton An optional secondary button. Note: only the image property of this button is used. Any title provided will be dropped.
 @param travelEstimates The travel estimates to display alongside the primary button.
 @return A new @c CPMapPanelButtonConfiguration instance.
 */
- (instancetype)initWithPrimaryAction:(CPTextButton *)primaryAction
                      secondaryButton:(nullable CPButton *)secondaryButton
                      travelEstimates:(CPTravelEstimates *)travelEstimates;

/**
 Optional travel estimates displayed alongside the primary action.
 */
@property (nonatomic, copy, nullable) CPTravelEstimates *travelEstimates;

/**
 An optional secondary button shown with this configuration. Note: only the image property of this button is used.
 */
@property (nonatomic, copy, readonly, nullable) CPButton *secondaryButton;

@end

NS_ASSUME_NONNULL_END
