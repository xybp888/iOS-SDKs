//
//  SFContentBlockerManager.h
//  SafariServices
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

SF_EXTERN NSString * const SFContentBlockerErrorDomain NS_AVAILABLE_IOS(9_0);

typedef NS_ENUM(NSInteger, SFContentBlockerErrorCode) {
    SFContentBlockerNoExtensionFound = 1,
    SFContentBlockerNoAttachmentFound = 2,
    SFContentBlockerLoadingInterrupted = 3,
} NS_ENUM_AVAILABLE_IOS(9_0);

NS_CLASS_AVAILABLE_IOS(9_0)
@interface SFContentBlockerManager : NSObject

+ (void)reloadContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(void (^__nullable)(NSError *__nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
