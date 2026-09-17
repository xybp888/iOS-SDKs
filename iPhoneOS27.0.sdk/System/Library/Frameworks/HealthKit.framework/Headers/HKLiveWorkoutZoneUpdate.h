//
//  HKLiveWorkoutZoneUpdate.h
//  HealthKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(27.0), watchos(27.0)) API_UNAVAILABLE(visionos)
@interface HKLiveWorkoutZoneUpdate : NSObject

/// The timestamp of the most recent processed sample at the time of the update.
@property(nonatomic, readonly, nullable, copy) NSDate *lastSampleProcessedDate;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
