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
 @c CPPanelButtonConfiguration describes the button configuration for
 a panel list section. It contains a primary and secondary action button.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPPanelButtonConfiguration : NSObject <NSSecureCoding>

/**
 Initializes a button configuration with a primary action and an optional secondary action.

 @param primaryAction The primary text button for the panel.
 @param secondaryAction An optional secondary @c CPTextButton.
 @return A new @c CPPanelButtonConfiguration instance
 */
- (instancetype)initWithPrimaryAction:(CPTextButton *)primaryAction
                      secondaryAction:(nullable CPTextButton *)secondaryAction NS_DESIGNATED_INITIALIZER;

/**
 The primary action button.
 */
@property (nonatomic, copy, readonly) CPTextButton *primaryAction;

/**
 The secondary action button, or @c nil if excluded.
 */
@property (nonatomic, copy, readonly, nullable) CPTextButton *secondaryAction;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
