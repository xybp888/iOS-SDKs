//
//  CTCellularPlanProperties.h
//  CFTelephony
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

API_AVAILABLE_BEGIN(ios(26.0), watchos(26.0))

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CTCellularPlanProperties.Capability)
typedef NS_ENUM(NSInteger, CTCellularPlanCapability) {
	CTCellularPlanCapabilityDataOnly,
	CTCellularPlanCapabilityDataAndVoice
};

CORETELEPHONY_EXTERN_CLASS
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(macos, tvos)
NS_SWIFT_NAME(CTCellularPlanProperties.lifecycle)
@interface CTCellularPlanLifecycleProperties : NSObject<NSSecureCoding>
@property (nonatomic, readwrite, nonnull) NSDateComponents* expirationDate API_UNAVAILABLE(macos, tvos);
@end

CORETELEPHONY_EXTERN_CLASS
API_UNAVAILABLE(macos, tvos)
@interface CTCellularPlanProperties : NSObject<NSSecureCoding>

@property (nonatomic, readwrite, nullable) NSString*                associatedIccid               API_UNAVAILABLE(macos, tvos);
@property (nonatomic, readwrite)           CTCellularPlanCapability simCapability                 API_UNAVAILABLE(macos, tvos);
@property (nonatomic, readwrite, nonnull)  NSArray<NSString*>*      supportedRegionCodes          API_UNAVAILABLE(macos, tvos) NS_REFINED_FOR_SWIFT;
@property (nonatomic, readwrite, nullable) CTCellularPlanLifecycleProperties* lifecycleProperties API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(macos, tvos);

@end

NS_ASSUME_NONNULL_END

API_AVAILABLE_END

#endif // __OBJC__
