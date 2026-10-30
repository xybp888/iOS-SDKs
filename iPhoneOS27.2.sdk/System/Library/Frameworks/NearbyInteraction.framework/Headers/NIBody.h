//
//  NIBody.h
//  NearbyInteraction
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#if __has_include(<AppleFeatures/AppleFeatures.h>)
#import <AppleFeatures/AppleFeatures.h>
#endif

#if APPLE_FEATURE_NIBODY
#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIExport.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A protocol for objects that represent an identifiable physical body.

 @discussion Conform to this protocol to provide an object that can be set as the
             origin body of an NISession. The origin body identifies the physical
             body associated with the local device running the session.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)
NI_EXPORT
@protocol NIBodyIdentifiable <NSObject>

@end

NS_ASSUME_NONNULL_END
#endif // APPLE_FEATURE_NIBODY
