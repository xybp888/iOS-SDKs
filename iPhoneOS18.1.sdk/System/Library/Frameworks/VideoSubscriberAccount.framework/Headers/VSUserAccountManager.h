//
//  VSUserAccountManager.h
//  VideoSubscriberAccountFramework
//
//  Created by Nik Harris on 1/30/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

#import <Foundation/Foundation.h>


@class VSUserAccount;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSInteger, VSUserAccountQueryOptions) {
    VSUserAccountQueryNone = 0,  // default
    VSUserAccountQueryAllDevices // return VSUserAccounts also registered on other devices in the users iCloud account
} NS_SWIFT_NAME(VSUserAccountManager.QueryOptions) API_AVAILABLE(ios(16.4), tvos(16.4), macos(13.3)) API_UNAVAILABLE(watchos, macCatalyst);

VS_EXPORT API_AVAILABLE(ios(16.4), tvos(16.4), macos(13.3)) API_UNAVAILABLE(watchos, macCatalyst)
@interface VSUserAccountManager : NSObject

@property (nonatomic, readonly, class) VSUserAccountManager *sharedUserAccountManager;

// Register a new VSUserAccount.
- (void)updateUserAccount:(VSUserAccount *)account completion:(void (^ _Nullable)(NSError * _Nullable error))completion NS_REFINED_FOR_SWIFT;

// Query the registered VSUserAccounts for your application.
// By default, this will return VSUserAccounts registered by your application on the current
// device only. To query the VSUserAccounts registered on all of the devices signed into the
// users iCloud account, use the query flag VSUserAccountQueryAllDevices.
- (void)queryUserAccountsWithOptions:(VSUserAccountQueryOptions)options completion:(void (^)(NSArray<VSUserAccount *> * _Nullable accounts, NSError * _Nullable error))completion NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
