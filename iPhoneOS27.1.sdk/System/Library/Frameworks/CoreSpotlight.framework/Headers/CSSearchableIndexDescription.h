//
//  CSSearchableIndexDescription.h
//  CoreSpotlight
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSSearchableIndexDescription : NSObject <NSSecureCoding, NSCopying>

@property (nonatomic, readonly, nullable) NSFileProtectionType protectionClass;
@end

NS_ASSUME_NONNULL_END
