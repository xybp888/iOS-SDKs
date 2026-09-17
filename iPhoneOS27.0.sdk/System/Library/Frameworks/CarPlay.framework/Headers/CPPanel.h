//
//  CPPanel.h
//  CarPlay
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPPanel : NSObject <NSSecureCoding>

/**
 The maximum panel items count.
 */
@property (nonatomic, class, readonly) NSInteger maximumPanelItemsCount;

/**
 A Boolean value indicating whether the close button is allowed to appear.

 @discussion Set the value of this property to @c NO to hide the close button.

 Defaults to YES.
 */
@property (nonatomic, assign) BOOL showsCloseButton;

@end

NS_ASSUME_NONNULL_END
