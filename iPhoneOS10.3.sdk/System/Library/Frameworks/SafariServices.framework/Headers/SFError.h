//
//  SFError.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#import <Foundation/Foundation.h>

SF_EXTERN NSString * const SFErrorDomain NS_AVAILABLE_IOS(10_0);

typedef NS_ENUM(NSInteger, SFErrorCode) {
    SFErrorNoExtensionFound = 1,
    SFErrorNoAttachmentFound = 2,
    SFErrorLoadingInterrupted = 3,
} NS_ENUM_AVAILABLE_IOS(10_0);
