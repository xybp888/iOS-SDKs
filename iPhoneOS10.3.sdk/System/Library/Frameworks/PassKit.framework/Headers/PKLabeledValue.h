//
//  PKLabeledValue.h
//  PassKit
//
//  Copyright © 2016 Apple, Inc. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(10_1) @interface PKLabeledValue : NSObject

- (instancetype)initWithLabel:(NSString *)label
                        value:(NSString *)value NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, readonly) NSString *label;
@property (nonatomic, copy, readonly) NSString *value;

@end

NS_ASSUME_NONNULL_END
