//
//  MSMessageError.h
//  Messages
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Messages/MessagesDefines.h>

MESSAGES_EXTERN NSString * const MSStickersErrorDomain NS_AVAILABLE_IOS(10_0);

MESSAGES_EXTERN NSString * const MSMessagesErrorDomain NS_AVAILABLE_IOS(10_0);

typedef NS_ENUM(NSInteger, MSMessageErrorCode) {
    MSMessageErrorCodeFileNotFound = 1,
    MSMessageErrorCodeFileUnreadable,
    MSMessageErrorCodeImproperFileType,
    MSMessageErrorCodeImproperFileURL,
    MSMessageErrorCodeStickerFileImproperFileAttributes,
    MSMessageErrorCodeStickerFileImproperFileSize,
    MSMessageErrorCodeStickerFileImproperFileFormat,
    MSMessageErrorCodeURLExceedsMaxSize,
} NS_ENUM_AVAILABLE_IOS(10_0);
