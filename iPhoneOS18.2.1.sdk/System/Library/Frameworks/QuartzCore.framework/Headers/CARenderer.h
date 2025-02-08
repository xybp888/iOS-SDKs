/* CoreAnimation - CARenderer.h

   Copyright (c) 2007-2022, Apple Inc.
   All rights reserved. */





























#ifdef __OBJC__

#import <QuartzCore/CABase.h>
#import <CoreVideo/CVBase.h>
#import <Foundation/NSObject.h>

@class NSDictionary, CALayer;
@protocol MTLTexture;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(10.5), ios(2.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface CARenderer : NSObject
{
@private
  struct CARendererPriv *_priv;
}















/* Create a new renderer object. Its render target is the specified
 * texture. 'dict' is an optional dictionary of parameters.  */

+ (CARenderer *)rendererWithMTLTexture:(id<MTLTexture>)tex
    options:(nullable NSDictionary *)dict
    API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/* The root layer associated with the renderer. */

@property(nullable, strong) CALayer *layer;

/* The bounds rect of the render target. */

@property CGRect bounds;

/* Begin rendering a frame at time 't'. If 'ts' is non-null it defines
 * the host time and update frequency of the target device. */

- (void)beginFrameAtTime:(CFTimeInterval)t timeStamp:(nullable CVTimeStamp *)ts;

/* Returns the bounds of the update region - the area that contains all
 * pixels that will be rendered by the current frame. Initially this
 * will include all differences between the current frame and the
 * previously rendered frame. */

- (CGRect)updateBounds;

/* Add rectangle 'r' to the update region of the current frame. */

- (void)addUpdateRect:(CGRect)r;

/* Render the update region of the current frame to the target context. */

- (void)render;

/* Returns the time at which the next update should happen. If infinite
 * no update needs to be scheduled yet. If the current frame time, a
 * continuous animation is running and an update should be scheduled
 * after a "natural" delay. */

- (CFTimeInterval)nextFrameTime;

/* Release any data associated with the current frame. */

- (void)endFrame;

/* Change the renderer's destination Metal texture. */

- (void)setDestination:(id<MTLTexture>)tex;
@end

/** Options for the renderer options dictionary. **/

/* The CGColorSpaceRef object defining the output color space. */

CA_EXTERN NSString * const kCARendererColorSpace
    API_AVAILABLE(macos(10.6), ios(2.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* The Metal Command Queue object against which to submit work.
 *
 * If the client provides a queue, then we will only commit our
 * command buffer and let the client handle it's own synchronization
 * and/or resource synchronization blits.
 *
 * If none is provided, then we will use an internal queue which
 * automatically commits and waitUntilScheduled. */

CA_EXTERN NSString * const kCARendererMetalCommandQueue
    API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0)) API_UNAVAILABLE(watchos);

NS_HEADER_AUDIT_END(nullability, sendability)

#endif
