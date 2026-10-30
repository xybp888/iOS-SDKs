//
//  CXCall.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <CallKit/CXBase.h>
#if APPLE_FEATURE_CALLNOTES && TARGET_OS_IOS && !TARGET_OS_MACCATALYST && !TARGET_OS_VISION
#import <CallKit/CXCallNotesStatus.h>
#endif

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), watchos(9.0))  API_UNAVAILABLE(macos, tvos)
@interface CXCall : NSObject

@property (nonatomic, readonly, copy) NSUUID *UUID;

@property (nonatomic, readonly, assign, getter=isOutgoing) BOOL outgoing;
@property (nonatomic, readonly, assign, getter=isOnHold) BOOL onHold;
@property (nonatomic, readonly, assign) BOOL hasConnected;
@property (nonatomic, readonly, assign) BOOL hasEnded;

#if APPLE_FEATURE_CALLNOTES && TARGET_OS_IOS && !TARGET_OS_MACCATALYST && !TARGET_OS_VISION
/// Whether notes are currently being gathered for this call.
@property (nonatomic, readonly, assign) CXCallNotesStatus callNotesStatus API_AVAILABLE(ios(27.0));
#endif

- (instancetype)init NS_UNAVAILABLE;

- (BOOL)isEqualToCall:(CXCall *)call;

@end

NS_ASSUME_NONNULL_END
