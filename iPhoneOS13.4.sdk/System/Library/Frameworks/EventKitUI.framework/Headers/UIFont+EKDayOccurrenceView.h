//
//  UIFont+EKDayOccurrenceView.h
//  EventKit
//
//  Copyright 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIFont (EKDayOccurrenceView)

@property (nonatomic, readonly, class) UIFont *ek_defaultOccurrenceSecondaryTextFont
API_DEPRECATED("No replacement. This is not intended for third party use and will return nil.", ios(13.0, 13.4))
API_UNAVAILABLE(macos, macCatalyst, watchos);

+ (UIFont *)ek_defaultOccurrencePrimaryTextFontForSizeClass:(UIUserInterfaceSizeClass)sizeClass
API_DEPRECATED("No replacement. This is not intended for third party use and will return nil.", ios(13.0, 13.4))
API_UNAVAILABLE(macos, macCatalyst, watchos);

+ (UIFont *)ek_defaultOccurrenceSmallPrimaryTextFontForSizeClass:(UIUserInterfaceSizeClass)sizeClass
API_DEPRECATED("No replacement. This is not intended for third party use and will return nil.", ios(13.0, 13.4))
API_UNAVAILABLE(macos, macCatalyst, watchos);

@end

NS_ASSUME_NONNULL_END
