//
//  CSIndexExtensionRequestHandler.h
//  CoreSpotlight
//
//  Copyright © 2015–2026 Apple Inc. All rights reserved.
//

#import <CoreSpotlight/CSSearchableIndex.h>

#import <Foundation/Foundation.h>

__attribute__((visibility("default")))
API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSIndexExtensionRequestHandler : NSObject <NSExtensionRequestHandling,CSSearchableIndexDelegate>

@end
