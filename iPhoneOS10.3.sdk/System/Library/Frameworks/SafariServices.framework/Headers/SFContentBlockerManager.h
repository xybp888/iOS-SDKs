//
//  SFContentBlockerManager.h
//  SafariServices
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#import <Foundation/Foundation.h>
#import <SafariServices/SFError.h>

NS_ASSUME_NONNULL_BEGIN

@class SFContentBlockerState;

SF_EXTERN NSString * const SFContentBlockerErrorDomain NS_DEPRECATED_IOS(9_0, 10_0, "Please use SFErrorDomain.");

typedef NS_ENUM(NSInteger, SFContentBlockerErrorCode) {
    SFContentBlockerNoExtensionFound NS_ENUM_DEPRECATED_IOS(9_0, 10_0, "Please use SFErrorNoExtensionFound.") = SFErrorNoExtensionFound,
    SFContentBlockerNoAttachmentFound NS_ENUM_DEPRECATED_IOS(9_0, 10_0, "Please use SFErrorNoAttachmentFound.") = SFErrorNoAttachmentFound,
    SFContentBlockerLoadingInterrupted NS_ENUM_DEPRECATED_IOS(9_0, 10_0, "Please use SFErrorLoadingInterrupted.") = SFErrorLoadingInterrupted,
} NS_ENUM_DEPRECATED_IOS(9_0, 10_0, "Please use SFErrorCode.");

NS_CLASS_AVAILABLE_IOS(9_0)
@interface SFContentBlockerManager : NSObject

+ (void)reloadContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(void (^_Nullable)(NSError *_Nullable error))completionHandler;
+ (void)getStateOfContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(void (^)(SFContentBlockerState *_Nullable state, NSError *_Nullable error))completionHandler NS_AVAILABLE_IOS(10_0);

@end

NS_ASSUME_NONNULL_END
