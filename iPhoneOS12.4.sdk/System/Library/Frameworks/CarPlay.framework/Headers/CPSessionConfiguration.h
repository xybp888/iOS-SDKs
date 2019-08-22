//
//  CPSessionConfiguration.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, CPLimitableUserInterface) {
    CPLimitableUserInterfaceKeyboard        = 1 << 0,
    CPLimitableUserInterfaceLists           = 1 << 1,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

@protocol CPSessionConfigurationDelegate;

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPSessionConfiguration : NSObject

- (instancetype)initWithDelegate:(id <CPSessionConfigurationDelegate>)delegate NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// A bitmask of what type of user interfaces are limited
@property (nonatomic, readonly) CPLimitableUserInterface limitedUserInterfaces;
@property (nonatomic, weak) id<CPSessionConfigurationDelegate> delegate;

@end

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPSessionConfigurationDelegate <NSObject>

// This delegate is called whenever the types of limited user interfaces have changed.
- (void)sessionConfiguration:(CPSessionConfiguration *)sessionConfiguration limitedUserInterfacesChanged:(CPLimitableUserInterface)limitedUserInterfaces;

@end

NS_ASSUME_NONNULL_END
