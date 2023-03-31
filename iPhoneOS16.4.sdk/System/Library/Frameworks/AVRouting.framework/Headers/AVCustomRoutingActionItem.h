/*
    File:  AVCustomRoutingActionItem.h
    
    Framework:  AVRouting
    
    Copyright © 2022 Apple Inc. All rights reserved.
    
 */

#import <Foundation/Foundation.h>

@class UTType;

NS_ASSUME_NONNULL_BEGIN

/*!
    @class      AVCustomRoutingActionItem
    @abstract   AVCustomRoutingActionItem objects can be created by 3rd parties to inject custom action items into the route picker.
    @discussion An item can be any action the app wants to provide as menu items besides the discovered routes.
    Tapping on the custom items dismisses the picker and invokes a callback to the app telling it which item was tapped. (See -[AVCustomRoutingController customRoutingController:didSelectItem:])
 */
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)
@interface AVCustomRoutingActionItem : NSObject

/*!
    @property   type
    @abstract   A UTType with an identifier which matches a UTType in the info.plist.
    @discussion Provide a UTTypeSymbolName and description in the info.plist.
 */
@property (nonatomic, copy) UTType *type API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
    @property   overrideTitle
    @abstract   A title which overrides the title of the UTType.
    @discussion Use this to dynamically override the title of the custom item.
 */
@property (nonatomic, copy, nullable) NSString *overrideTitle API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
