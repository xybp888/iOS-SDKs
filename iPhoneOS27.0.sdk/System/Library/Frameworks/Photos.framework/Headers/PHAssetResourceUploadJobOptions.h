//
//  PHAssetResourceUploadJobOptions.h
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Options that affect the service behavior when processing Asset Resource Upload Jobs.
API_AVAILABLE(ios(27.0), macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(tvos, visionos, watchos)
@interface PHAssetResourceUploadJobOptions : NSObject <NSCopying>

/// Prevents expensive network access, such as cellular, for the service.
///
/// When `true`, the service only performs work for the associated configuration while the
/// device has a non-expensive network connection (such as Wi-Fi or Ethernet); cellular
/// connectivity is not used. Defaults to `false`.
@property (nonatomic, assign) BOOL preventsExpensiveNetworkAccess;

@end

NS_ASSUME_NONNULL_END
