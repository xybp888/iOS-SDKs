// Copyright © 2025 Apple Inc. All rights reserved.


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const BEBrowserDataExchangeErrorDomain;

typedef NS_ERROR_ENUM(BEBrowserDataExchangeErrorDomain, BEBrowserDataExchangeError) {
    BEBrowserDataDataExchangeErrorUnknown NS_SWIFT_NAME(unknown) = 0,
    BEBrowserDataDataExchangeErrorExport NS_SWIFT_NAME(export),
    BEBrowserDataDataExchangeErrorImport NS_SWIFT_NAME(import),
}
API_AVAILABLE(ios(26.4))
API_UNAVAILABLE(tvos, watchos, macCatalyst, macos, visionos);

NS_ASSUME_NONNULL_END

