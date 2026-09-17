// Copyright © 2025 Apple Inc. All rights reserved.


NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEBrowserData : NSObject <NSSecureCoding>

@property (nonatomic, nullable, readonly, copy) NSString *sourceApplicationBundleIdentifier;
@property (nonatomic, nullable, readonly, copy) NSString *sourceApplicationLocalizedName;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithSourceApplicationBundleIdentifier:(nullable NSString *)sourceApplicationBundleIdentifier sourceApplicationLocalizedName:(nullable NSString *)sourceApplicationLocalizedName;

@end

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEBrowserDataBookmark : BEBrowserData

@property (nonatomic, readonly) BOOL isFolder;
@property (nonatomic, readonly, copy) NSString *title;
@property (nonatomic, readonly, copy) NSString *identifier;
@property (nonatomic, nullable, readonly) NSURL *url;
@property (nonatomic, nullable, readonly, copy) NSString *parentIdentifier;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initAsFolder:(BOOL)isFolder title:(NSString *)title identifier:(NSString *)identifier url:(nullable NSURL *)url parentIdentifier:(nullable NSString *)parentIdentifier NS_SWIFT_NAME(init(isFolder:title:identifier:url:parentIdentifier:));

@end

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEBrowserDataReadingListItem : BEBrowserData

@property (nonatomic, readonly, copy) NSString *title;
@property (nonatomic, readonly) NSURL *url;
@property (nonatomic, nullable, readonly) NSDate *dateOfLastVisit;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithTitle:(NSString *)title url:(NSURL *)url dateOfLastVisit:(nullable NSDate *)dateOfLastVisit;

@end

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEBrowserDataHistoryVisit : BEBrowserData

@property (nonatomic, readonly) NSURL *url;
@property (nonatomic, readonly) NSDate *dateOfLastVisit;
@property (nonatomic, nullable, readonly, copy) NSString *title;
@property (nonatomic, readonly) BOOL loadedSuccessfully;
@property (nonatomic, readonly) BOOL httpGet;
@property (nonatomic, nullable, readonly) NSURL *redirectSourceURL;
@property (nonatomic, nullable, readonly) NSDate *redirectSourceDateOfVisit;
@property (nonatomic, nullable, readonly) NSURL *redirectDestinationURL;
@property (nonatomic, nullable, readonly) NSDate *redirectDestinationDateOfVisit;
@property (nonatomic, readonly) NSUInteger visitCount;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithURL:(NSURL *)url dateOfLastVisit:(NSDate *)dateOfLastVisit title:(nullable NSString *)title loadedSuccessfully:(BOOL)loadedSuccessfully httpGet:(BOOL)httpGet redirectSourceURL:(nullable NSURL *)redirectSourceURL redirectSourceDateOfVisit:(nullable NSDate *)redirectSourceDateOfVisit redirectDestinationURL:(nullable NSURL *)redirectDestinationURL redirectDestinationDateOfVisit:(nullable NSDate *)redirectDestinationDateOfVisit visitCount:(NSUInteger)visitCount;

@end

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEBrowserDataExtension : BEBrowserData

@property (nonatomic, readonly, copy) NSString *displayName;
@property (nonatomic, readonly, copy) NSString *developerName;
@property (nonatomic, readonly, copy) NSString *identifier;
@property (nonatomic, readonly, copy) NSString *storeIdentifier;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithDisplayName:(NSString *)displayName developerName:(NSString *)developerName identifier:(NSString *)identifier storeIdentifier:(NSString *)storeIdentifier;

@end

NS_ASSUME_NONNULL_END

