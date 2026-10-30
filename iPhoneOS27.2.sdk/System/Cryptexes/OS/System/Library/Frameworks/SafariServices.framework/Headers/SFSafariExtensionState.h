// Copyright © 2025 Apple Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_SWIFT_SENDABLE
SF_EXTERN API_AVAILABLE(ios(26.2), visionos(26.2)) API_UNAVAILABLE(tvos, watchos)
@interface SFSafariExtensionState : NSObject

/// A Boolean value that indicates whether the web extension is enabled.
@property (nonatomic, readonly, getter=isEnabled) BOOL enabled;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

