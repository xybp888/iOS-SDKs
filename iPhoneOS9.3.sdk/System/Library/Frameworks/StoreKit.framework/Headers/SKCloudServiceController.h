//
//  SKCloudServiceController.h
//  StoreKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKCloudServiceAuthorizationStatus) {
    SKCloudServiceAuthorizationStatusNotDetermined,
    SKCloudServiceAuthorizationStatusDenied,
    SKCloudServiceAuthorizationStatusRestricted,
    SKCloudServiceAuthorizationStatusAuthorized,
} NS_ENUM_AVAILABLE_IOS(9_3);

typedef NS_OPTIONS(NSUInteger, SKCloudServiceCapability) {
    SKCloudServiceCapabilityNone                           = 0,
    SKCloudServiceCapabilityMusicCatalogPlayback           = 1 << 0,
    SKCloudServiceCapabilityAddToCloudMusicLibrary         = 1 << 8,
} NS_AVAILABLE_IOS(9_3);

SK_EXTERN_CLASS_AVAILABLE(9_3) @interface SKCloudServiceController : NSObject

+ (SKCloudServiceAuthorizationStatus)authorizationStatus;
+ (void)requestAuthorization:(void(^)(SKCloudServiceAuthorizationStatus status))handler;

- (void)requestStorefrontIdentifierWithCompletionHandler:(void(^)(NSString * __nullable storefrontIdentifier, NSError * __nullable error))completionHandler;
- (void)requestCapabilitiesWithCompletionHandler:(void(^)(SKCloudServiceCapability capabilities, NSError * __nullable error))completionHandler;

@end

SK_EXTERN NSString * const SKStorefrontIdentifierDidChangeNotification NS_AVAILABLE_IOS(9_3);
SK_EXTERN NSString * const SKCloudServiceCapabilitiesDidChangeNotification NS_AVAILABLE_IOS(9_3);

NS_ASSUME_NONNULL_END
