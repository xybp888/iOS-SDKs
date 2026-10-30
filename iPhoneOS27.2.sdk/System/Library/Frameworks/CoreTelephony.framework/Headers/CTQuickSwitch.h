//
//  CTQuickSwitch.h
//  CFTelephony
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class CTQuickSwitchManager;

NS_SWIFT_NAME(CTQuickSwitchManager.State)
typedef NS_ENUM(NSInteger, CTQuickSwitchState) {
    CTQuickSwitchStateFailed,
    CTQuickSwitchStateNotEnrolled,
    CTQuickSwitchStateActive,
    CTQuickSwitchStatePassive
} __API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, tvos, watchos);

CORETELEPHONY_CLASS_AVAILABLE(27_0)
API_UNAVAILABLE(macos, tvos, watchos)
NS_SWIFT_NAME(CTQuickSwitchManager.Delegate)
@protocol CTQuickSwitchManagerDelegate <NSObject>
@optional
- (void)quickSwitchManager:(CTQuickSwitchManager *)quickSwitchManager didChangeToState:(CTQuickSwitchState)state;
@end

CORETELEPHONY_CLASS_AVAILABLE(27_0)
API_UNAVAILABLE(macos, tvos, watchos)
@interface CTQuickSwitchManager : NSObject

@property (weak, nonatomic, nullable) id<CTQuickSwitchManagerDelegate> delegate;

- (void)getPhoneNumberStateForSuffix:(NSString *)phoneNumberSuffix
                 completion:(void (^)(CTQuickSwitchState state, NSError * _Nullable error))completionHandler;

- (void)getDeviceState:(void (^)(CTQuickSwitchState state, NSError * _Nullable error))completionHandler
    NS_SWIFT_ASYNC_NAME(getter:deviceState());

+ (void)registerForLaunchOnQuickSwitchStateEvents:(void (^)(NSError * _Nullable error))completionHandler;

+ (void)unregisterForLaunchOnQuickSwitchStateEvents:(void (^)(NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC__
