// Copyright © 2025 Apple Inc. All rights reserved.


#import "BEBrowserData.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
extern NSString * const BEBrowserDataExchangeImportActivity
NS_SWIFT_NAME(BEBrowserDataImportManager.userActivityType);

API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
extern NSString * const BEBrowserDataExchangeImportToken
NS_SWIFT_NAME(BEBrowserDataImportManager.importTokenUserInfoKey);

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEImportOptions : NSObject <NSSecureCoding>

@property (nonatomic, readonly) BOOL importFromFiles;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithImportFromFiles:(BOOL)importFromFiles;

@end

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEImportMetadata : NSObject <NSSecureCoding>

@property (nonatomic, readonly) BOOL supportImportFromFiles;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithSupportForImportFromFiles:(BOOL)supportImportFromFiles;

@end

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEBrowserDataImportManager : NSObject

- (instancetype)init;
- (instancetype)initWithScene:(UIWindowScene * _Nullable)scene NS_SWIFT_UI_ACTOR;

- (void)importBrowserDataWithToken:(NSUUID *)token importBlock:(void (^)(BEBrowserData * _Nullable, BOOL, NSError * _Nullable))importBlock NS_REFINED_FOR_SWIFT;
- (void)requestImportForMetadata:(BEImportMetadata *)metadata completionHandler:(void (^)(BEImportOptions * _Nullable, NSError * _Nullable))completionHandler;

@end

NS_ASSUME_NONNULL_END

