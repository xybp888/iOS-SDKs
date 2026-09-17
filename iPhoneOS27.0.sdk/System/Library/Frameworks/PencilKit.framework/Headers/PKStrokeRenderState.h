//
//  PKStrokeRenderState.h
//  PencilKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// The render details of a stroke, including particle positioning and grain texture offset.
///
/// Some state is exposed, but other state is opaque. Use `NSSecureCoding` to persist all stored information.
API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0))
NS_SWIFT_NAME(PKStrokeRenderStateReference)
@interface PKStrokeRenderState : NSObject <NSCopying, NSSecureCoding>

/// The pre-transform position of the grain texture for strokes with a backing grain texture such as crayon.
@property (nonatomic, assign) CGPoint grainOffset;

@end

NS_ASSUME_NONNULL_END
