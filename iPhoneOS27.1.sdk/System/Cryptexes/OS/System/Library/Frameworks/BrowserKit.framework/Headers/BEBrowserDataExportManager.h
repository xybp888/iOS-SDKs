// Copyright © 2025 Apple Inc. All rights reserved.


#import "BEBrowserData.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
extern NSString * const BEBrowserDataExchangeExportActivity NS_SWIFT_NAME(BEBrowserDataExportManager.userActivityType);

API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
extern NSString * const BEBrowserDataExchangeExportToken NS_SWIFT_NAME(BEBrowserDataExportManager.exportTokenUserInfoKey);

typedef NS_OPTIONS(NSUInteger, BEExportDataTypes) {
    BEExportDataTypesNone NS_SWIFT_NAME(none) = 0,
    BEExportDataTypesBookmarks NS_SWIFT_NAME(bookmarks) = 1 << 0,
    BEExportDataTypesReadingList NS_SWIFT_NAME(readingList) = 1 << 1,
    BEExportDataTypesHistory NS_SWIFT_NAME(history) = 1 << 2,
    BEExportDataTypesExtensions NS_SWIFT_NAME(extensions) = 1 << 3,
}
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
NS_SWIFT_NAME(BEExportOptions.DataTypes);

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEExportOptions : NSObject <NSSecureCoding>

@property (nonatomic, readonly) BOOL exportToFiles;
@property (nonatomic, readonly) BEExportDataTypes dataTypes;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithExportToFiles:(BOOL)exportToFiles dataTypes:(BEExportDataTypes)dataTypes;

@end

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEExportMetadata : NSObject <NSSecureCoding>

@property (nonatomic, readonly) BOOL supportExportToFiles;
@property (nonatomic, readonly) NSInteger bookmarksCount;
@property (nonatomic, readonly) NSInteger readingListCount;
@property (nonatomic, readonly) NSInteger historyCount;
@property (nonatomic, readonly) NSInteger extensionsCount;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithSupportForExportToFiles:(BOOL)supportExportToFiles bookmarksCount:(NSInteger)bookmarksCount readingListCount:(NSInteger)readingListCount historyCount:(NSInteger)historyCount extensionsCount:(NSInteger)extensionsCount;

@end

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos)
@interface BEBrowserDataExportManager : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithScene:(UIWindowScene *)scene NS_SWIFT_UI_ACTOR;

- (void)requestExportForMetadata:(BEExportMetadata *)metadata token:(NSUUID * _Nullable)token completionHandler:(void (^)(BEExportOptions * _Nullable, NSError * _Nullable))completionHandler;
- (void)exportBrowserData:(BEBrowserData *)browserData completionHandler:(void (^)(NSError * _Nullable))completionHandler NS_REFINED_FOR_SWIFT;
- (void)exportFinishedWithCompletionHandler:(void (^)(NSError * _Nullable))completionHandler NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

