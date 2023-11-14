//
//  SKAdTestSession.h
//  StoreKitTest
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <StoreKit/StoreKit.h>

@class SKAdTestPostback;
@class SKAdTestPostbackResponse;

NS_ASSUME_NONNULL_BEGIN

typedef void (^SKANTestPostbackResponseHandler)(NSDictionary <NSString *, SKAdTestPostbackResponse *> * __nullable responseDict, NSError * __nullable error) API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,visionos) __TVOS_PROHIBITED;

SK_EXTERN_CLASS API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,tvos,watchos,visionos)
@interface SKAdTestSession : NSObject

#pragma mark - Methods

- (instancetype)init;

/// Use this method to validate an impression against the requirements that SKAdNetwork impressions
/// are expected to satisfy. This method is to be used for StoreKit rendered ads.
- (BOOL)validateImpressionWithParameters:(NSDictionary <NSString *, id> *)parameters publicKey:(NSString *)publicKey error:(NSError *__autoreleasing  _Nullable *)error NS_SWIFT_NAME(validateImpression(parameters:publicKey:)) API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,visionos) __TVOS_PROHIBITED;

/// Use this method to validate an impression against the requirements that SKAdNetwork impressions
/// are expected to satisfy. This method is to be used for ViewThrough ads.
- (BOOL)validateImpression:(SKAdImpression *)impression publicKey:(NSString *)publicKey error:(NSError *__autoreleasing  _Nullable *)error API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,visionos) __TVOS_PROHIBITED;

/// Use this method to validate an impression against the requirements that SKAdNetwork impressions
/// are expected to satisfy. This method is to be used for Web ads.
- (BOOL)validateWebAdImpressionPayload:(NSData *)impressionData publicKey:(NSString *)publicKey error:(NSError *__autoreleasing  _Nullable *)error API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(macos,watchos,visionos) __TVOS_PROHIBITED;

/// Use this method to set postbacks to interact with later.
- (BOOL)setPostbacks:(NSArray <SKAdTestPostback *> *)postbacks error:(NSError *__autoreleasing  _Nullable *)error NS_SWIFT_NAME(setPostbacks(_:)) API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,visionos) __TVOS_PROHIBITED;

@property (nonatomic, strong, readonly) NSArray <SKAdTestPostback *> * postbacks;

@property (nonatomic, strong, readonly, nullable) NSURL *developerPostbackURL;

/// Use this method to send the test postbacks.
- (void)flushPostbacksWithResponses:(SKANTestPostbackResponseHandler)responses NS_SWIFT_ASYNC(1) API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,visionos) __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
