/* CoreAnimation - CAMetalDisplayLink.h

   Copyright (c) 2023, Apple Inc.
   All rights reserved. */

#ifdef __OBJC__

#import <QuartzCore/CABase.h>
#import <QuartzCore/CAFrameRateRange.h>
#import <QuartzCore/CAMetalLayer.h>
#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

@class CAMetalDisplayLink;

API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
CF_SWIFT_NAME(CAMetalDisplayLink.Update)
@interface CAMetalDisplayLinkUpdate : NSObject
@property(readonly, nonatomic) id<CAMetalDrawable> drawable;
@property(readonly, nonatomic) CFTimeInterval targetTimestamp;
@property(readonly, nonatomic) CFTimeInterval targetPresentationTimestamp;
@end

API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
@protocol CAMetalDisplayLinkDelegate
- (void)metalDisplayLink:(CAMetalDisplayLink *)link needsUpdate:(CAMetalDisplayLinkUpdate *)update;
@end

API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
@interface CAMetalDisplayLink : NSObject

- (instancetype)initWithMetalLayer:(CAMetalLayer *)layer;

- (void)addToRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

- (void)removeFromRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

- (void)invalidate;

@property(nonatomic, weak, nullable) id<CAMetalDisplayLinkDelegate> delegate;

@property(nonatomic) float preferredFrameLatency;

@property(nonatomic) CAFrameRateRange preferredFrameRateRange;

@property(getter=isPaused, nonatomic) BOOL paused;

@end

NS_ASSUME_NONNULL_END

#endif
