//
//  SKAdTestPostback.h
//  StoreKitTest
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * SKAdTestPostbackVersion NS_TYPED_ENUM API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,tvos);

SK_EXTERN SKAdTestPostbackVersion const SKAdTestPostbackVersion2_1 API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,tvos);
SK_EXTERN SKAdTestPostbackVersion const SKAdTestPostbackVersion2_2 API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,tvos);
SK_EXTERN SKAdTestPostbackVersion const SKAdTestPostbackVersion3_0 API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,tvos);
SK_EXTERN SKAdTestPostbackVersion const SKAdTestPostbackVersion4_0 API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(macos,watchos,tvos);

SK_EXTERN_CLASS API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,tvos) @interface SKAdTestPostback : NSObject

/// Use this initializer to create a postback with the specified version and parameters.
/// Parameters that are not applicable to the specified version will be ignored.
/// Parameters that are mandatory for the specified version and not provided will result
/// in failure to create the postback.
- (nullable instancetype)initWithVersion:(SKAdTestPostbackVersion)version
                     adNetworkIdentifier:(NSString *)adNetworkIdentifier
                    adCampaignIdentifier:(NSInteger)adCampaignIdentifier
                  appStoreItemIdentifier:(NSInteger)appStoreItemIdentifier
            sourceAppStoreItemIdentifier:(NSInteger)sourceAppStoreItemIdentifier
                         conversionValue:(NSInteger)conversionValue
                            fidelityType:(NSInteger)fidelityType
                            isRedownload:(BOOL)isRedownload
                                  didWin:(BOOL)didWin
                             postbackURL:(NSString *)postbackURL API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,tvos);

/// Use this initializer to create a postback with the specified version and parameters.
/// Parameters that are not applicable to the specified version will be ignored.
/// Parameters that are mandatory for the specified version and not provided will result
/// in failure to create the postback.
- (nullable instancetype)initWithVersion:(SKAdTestPostbackVersion)version
                     adNetworkIdentifier:(NSString *)adNetworkIdentifier
                        sourceIdentifier:(NSString *)sourceIdentifier
                  appStoreItemIdentifier:(NSInteger)appStoreItemIdentifier
            sourceAppStoreItemIdentifier:(NSInteger)sourceAppStoreItemIdentifier
                            sourceDomain:(nullable NSString *)sourceDomain
                            fidelityType:(NSInteger)fidelityType
                            isRedownload:(BOOL)isRedownload
                                  didWin:(BOOL)didWin
                             postbackURL:(NSString *)postbackURL API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(macos,watchos,tvos);

/// Use this initializer to create an array of 3 winning postbacks with the specified version and parameters.
/// Parameters that are not applicable to the specified version will be ignored.
/// Parameters that are mandatory for the specified version and not provided will result
/// in failure to create the postback.
+ (nullable NSArray <SKAdTestPostback *> *)winningPostbacksWithVersion:(SKAdTestPostbackVersion)version
                                                       adNetworkIdentifier:(NSString *)adNetworkIdentifier
                                                          sourceIdentifier:(NSString *)sourceIdentifier
                                                    appStoreItemIdentifier:(NSInteger)appStoreItemIdentifier
                                              sourceAppStoreItemIdentifier:(NSInteger)sourceAppStoreItemIdentifier
                                                              sourceDomain:(nullable NSString *)sourceDomain
                                                              fidelityType:(NSInteger)fidelityType
                                                              isRedownload:(BOOL)isRedownload
                                                               postbackURL:(NSString *)postbackURL API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(macos,watchos,tvos);

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The version of SKAdNetwork being used.
@property (nonatomic, strong, readonly) SKAdTestPostbackVersion version;

/// The identifier for the ad network.
@property (nonatomic, strong, readonly) NSString *adNetworkIdentifier;

/// The ad campaign identifier.
@property (nonatomic, assign, readonly) NSInteger adCampaignIdentifier;

/// The source identifier.
@property (nonatomic, strong, readonly, nullable) NSString *sourceIdentifier API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(macos,watchos,tvos);

/// The App Store item identifier for the app.
@property (nonatomic, assign, readonly) NSInteger appStoreItemIdentifier;

/// The App Store item identifier for the source app.
@property (nonatomic, assign, readonly) NSInteger sourceAppStoreItemIdentifier;

/// The eTLD+1 representation of the source web page.
@property (nonatomic, strong, readonly, nullable) NSString *sourceDomain API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(macos,watchos,tvos);

/// The conversion value for this conversion.
@property (nonatomic, assign, readonly) NSInteger conversionValue;

/// The fine conversion value for this postback.
@property (nonatomic, assign, readonly) NSInteger fineConversionValue API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(macos,watchos,tvos);

/// The coarse conversion value for this postback.
@property (nonatomic, strong, readonly, nullable) SKAdNetworkCoarseConversionValue coarseConversionValue API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(macos,watchos,tvos);

/// A flag indicating whether this postback is registered or not.
@property (nonatomic, assign, readonly) BOOL isRegistered;

/// The transaction identifier for this postback.
@property (nonatomic, strong, readonly) NSString *transactionIdentifier;

/// The fidelity-type for this conversion.
@property (nonatomic, assign) NSInteger fidelityType;

/// Indication as to whether this conversion was for a redownload.
@property (nonatomic, assign, readonly) BOOL isRedownload;

/// Indication as to whether this was the winning conversion.
@property (nonatomic, assign, readonly) BOOL didWin;

/// The sequence index of the postback.
@property (nonatomic, assign, readonly) NSInteger postbackSequenceIndex API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(macos,watchos,tvos);

/// The URL to which the postback is to be sent.
@property (nonatomic, strong, readonly) NSString *postbackURL;

@end

SK_EXTERN_CLASS API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,tvos) __TVOS_PROHIBITED @interface SKAdTestPostbackResponse : NSObject

/// The error encountered, if any, while attempting to send this postback.
@property (nonatomic, strong, nullable) NSError *error;

/// A boolean flag indicating if this postback was sent successfully.
@property (nonatomic, assign) BOOL didSucceed;

/// The HTTP response received, if any, as a result of sending the postback.
@property (nonatomic, strong, nullable) NSHTTPURLResponse *httpResponse;

@end

NS_ASSUME_NONNULL_END
