//
//  SFContentBlockerState.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_CLASS_AVAILABLE_IOS(10_0)
@interface SFContentBlockerState : NSObject

@property (nonatomic, readonly, getter=isEnabled) BOOL enabled;

@end
