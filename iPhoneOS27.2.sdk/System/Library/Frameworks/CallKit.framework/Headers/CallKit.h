//
//  CallKit.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CallKit/CXBase.h>
#import <CallKit/CXError.h>
#import <CallKit/CXAction.h>
#import <CallKit/CXTransaction.h>
#import <CallKit/CXCallUpdate.h>
#import <CallKit/CXHandle.h>
#import <CallKit/CXCallAction.h>
#import <CallKit/CXStartCallAction.h>
#import <CallKit/CXAnswerCallAction.h>
#import <CallKit/CXEndCallAction.h>
#import <CallKit/CXSetHeldCallAction.h>
#import <CallKit/CXSetMutedCallAction.h>
#import <CallKit/CXSetGroupCallAction.h>
#import <CallKit/CXPlayDTMFCallAction.h>
#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST && !TARGET_OS_VISION
#import <CallKit/CXSetTranslatingCallAction.h>
#endif
#import <CallKit/CXProvider.h>
#import <CallKit/CXProviderConfiguration.h>
#if APPLE_FEATURE_CALLNOTES && TARGET_OS_IOS && !TARGET_OS_MACCATALYST && !TARGET_OS_VISION
#import <CallKit/CXCallNotesStatus.h>
#import <CallKit/CXSetCallNotesAction.h>
#endif
#import <CallKit/CXCall.h>
#import <CallKit/CXCallObserver.h>
#import <CallKit/CXCallController.h>
#import <CallKit/CXCallDirectory.h>
#import <CallKit/CXCallDirectoryManager.h>
#import <CallKit/CXCallDirectoryProvider.h>
#import <CallKit/CXCallDirectoryExtensionContext.h>
