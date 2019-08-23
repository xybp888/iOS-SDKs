//
//  CXProviderConfiguration.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

CX_CLASS_AVAILABLE(ios(10.0))
@interface CXProviderConfiguration : NSObject <NSCopying>

/// Localized name of the provider
@property (nonatomic, readonly, copy) NSString *localizedName;

/// Name of resource in app's bundle to play as ringtone for incoming call
@property (nonatomic, strong, nullable) NSString *ringtoneSound;

@property (nonatomic, copy, nullable) NSData *iconTemplateImageData; // Image should be a square with side length of 40 points
@property (nonatomic) NSUInteger maximumCallGroups; // Default 2
@property (nonatomic) NSUInteger maximumCallsPerCallGroup; // Default 5

@property (nonatomic) BOOL supportsVideo; // Default NO

// Numbers are of type CXHandleType
@property (nonatomic, copy) NSSet<NSNumber *> *supportedHandleTypes;

- (instancetype)initWithLocalizedName:(NSString *)localizedName;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
