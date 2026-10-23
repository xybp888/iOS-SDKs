//
//  CTCellularPlanStatus.h
//  CFTelephony
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CTCellularPlanStatus.Availability)
typedef NS_ENUM(NSInteger, CTCellularPlanStatusAvailability) {
    CTCellularPlanStatusAvailabilityUnavailable = 0,
    CTCellularPlanStatusAvailabilityAvailable,
} __API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, tvos, watchos);

NS_SWIFT_NAME(CTCellularPlanStatus.AvailabilityConfidence)
typedef NS_ENUM(NSInteger, CTCellularPlanStatusAvailabilityConfidence) {
    CTCellularPlanStatusAvailabilityConfidenceLow = 0,
    CTCellularPlanStatusAvailabilityConfidenceHigh,
} __API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, tvos, watchos);

NS_SWIFT_NAME(CTCellularPlanStatus.Authorization)
typedef NS_ENUM(NSInteger, CTCellularPlanStatusAuthorization) {
    CTCellularPlanStatusAuthorizationNotAuthorized,
    CTCellularPlanStatusAuthorizationAuthorized,
    CTCellularPlanStatusAuthorizationRestricted,
    CTCellularPlanStatusAuthorizationNotSupported,
} __API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, tvos, watchos);

CORETELEPHONY_CLASS_AVAILABLE(19_0)
@interface CTCellularPlanStatus : NSObject

+ (void)getTokenWithCompletion:(void (^)(NSString * _Nullable token, NSError * _Nullable error))completionHandler __API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, tvos, watchos);
+ (void)checkValidityOfToken:(NSString *)token completionHandler:(void (^)(BOOL isValid, NSError * _Nullable error))completionHandler __API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, tvos, watchos);

+ (void)requestAuthorizationForPhoneNumber:(NSString *)phoneNumber
    completion:(void (^)(CTCellularPlanStatusAuthorization status, NSError * _Nullable error))completionHandler
    __API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, tvos, watchos);

+ (void)getAuthorizationStatusForPhoneNumber:(NSString *)phoneNumber
    completion:(void (^)(CTCellularPlanStatusAuthorization status, NSError * _Nullable error))completionHandler
    __API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, tvos, watchos);

+ (void)getStatusHintForPhoneNumber:(NSString *)phoneNumber
    completion:(void (^)(CTCellularPlanStatusAvailability, CTCellularPlanStatusAvailabilityConfidence, NSError * _Nullable error))completionHandler
    __API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC__
