//
//  PKPushPayload.h
//  PushKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_CLASS_AVAILABLE_IOS(8_0)
@interface PKPushPayload : NSObject

@property (readonly,copy) NSString *type;
@property (readonly,copy) NSDictionary *dictionaryPayload;

@end
