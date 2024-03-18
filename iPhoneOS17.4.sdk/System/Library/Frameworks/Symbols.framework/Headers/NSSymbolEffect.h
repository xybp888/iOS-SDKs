//
//  NSSymbolEffect.h
//  Symbols
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef NSSymbolEffect_h
#define NSSymbolEffect_h

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark - Options

/// Options configuring how symbol effects apply to symbol views.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolEffectOptions : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The default options.
+ (instancetype)options;

/// Convenience initializer that prefers to repeat indefinitely.
+ (instancetype)optionsWithRepeating;

/// Return a copy of the options that prefers to repeat indefinitely.
- (instancetype)optionsWithRepeating;

/// Convenience initializer that prefers not to repeat.
+ (instancetype)optionsWithNonRepeating;

/// Return a copy of the options that prefers not to repeat.
- (instancetype)optionsWithNonRepeating;

/// Convenience initializer setting a preferred repeat count.
///
/// - Parameter count: The preferred number of times to play the
///   effect. Very large or small values may be clamped.
///
/// - Returns: A new options object with the preferred repeat count.
+ (instancetype)optionsWithRepeatCount:(NSInteger)count;

/// Return a copy of the options setting a preferred repeat count.
///
/// - Parameter count: The preferred number of times to play the
///   effect. Very large or small values may be clamped.
///
/// - Returns: A new options object with the preferred repeat count.
- (instancetype)optionsWithRepeatCount:(NSInteger)count;

/// Convenience initializer setting the preferred speed multiplier.
///
/// - Parameter speed: the preferred speed multiplier to play the effect with.
/// The default multiplier is `1.0`. Very large or small values may
/// be clamped.
///
/// - Returns: A new instance with the preferred speed multiplier.
+ (instancetype)optionsWithSpeed:(double)speed;

/// Return a copy of the options setting the preferred speed multiplier.
///
/// - Parameter speed: The preferred speed multiplier to play the effect with.
/// The default multiplier is `1.0`. Very large or small values may
/// be clamped.
///
/// - Returns: A new instance with the preferred speed multiplier.
- (instancetype)optionsWithSpeed:(double)speed;

@end

#pragma mark - Base Effect

/// An abstract base class for effects that can be applied to both NSImageViews and UIImageViews that have symbol-based images.
///
/// Don't use this class directly, instead use any of the concrete subclasses.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolEffect : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - Pulse Effect

/// A symbol effect that applies the Pulse animation to
/// symbol images.
///
/// The Pulse animation fades the opacity of either all layers in
/// the symbol, or of a subset of the layers in the symbol.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolPulseEffect : NSSymbolEffect

/// The default pulse effect, determined by the system.
+ (instancetype)effect;

/// Returns a copy of the effect that only animates annotated pulse layers.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Bounce Effect

/// A symbol effect that applies the Bounce animation to
/// symbol images.
///
/// The Bounce animation applies a transitory scaling effect to the symbol.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolBounceEffect : NSSymbolEffect

/// The default bounce effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer for a bounce effect that bounces up.
+ (instancetype)bounceUpEffect;

/// Convenience initializer for a bounce effect that bounces down.
+ (instancetype)bounceDownEffect;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Variable Color Effect

/// A symbol effect that applies the Variable Color
/// animation to symbol images.
///
/// The Variable Color animation replaces the opacity of variable
/// layers in the symbol by a possibly repeating pattern that moves
/// up and possibly back down the variable layers. It has no effect
/// for non-variable color symbol images.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolVariableColorEffect : NSSymbolEffect

/// The default variable color effect, determined by the system.
+ (instancetype)effect;

/// Returns a copy of the effect that activates one layer at a time. This cancels the cumulative variant.
- (instancetype)effectWithIterative;

/// Returns a copy of the effect that activates each layer until all layers are active. This cancels the iterative variant.
- (instancetype)effectWithCumulative;

/// Returns a copy of the effect that animates in reverse after fully executing. This cancels the nonReversing variant.
- (instancetype)effectWithReversing;

/// Returns a copy of the effect that only animates forwards before restarting. This cancels the reversing variant.
- (instancetype)effectWithNonReversing;

/// Returns a copy of the effect that hides layers when they are inactive.
- (instancetype)effectWithHideInactiveLayers;

/// Returns a copy of the effect that draws layers with reduced (but non-zero)
/// opacity when they are inactive.
- (instancetype)effectWithDimInactiveLayers;

@end

#pragma mark - Scale Effect

/// A symbol effect that scales symbol images.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolScaleEffect : NSSymbolEffect

/// The default scaling effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer to create a scale effect with a scale up level.
+ (instancetype)scaleUpEffect;

/// Convenience initializer to create a scale effect with a scale down level.
+ (instancetype)scaleDownEffect;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Appear Effect

/// A symbol effect that applies the Appear animation to
/// symbol images.
///
/// The Appear animation makes the symbol visible either as a whole,
/// or one motion group at a time.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolAppearEffect : NSSymbolEffect

/// The default appear effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer for an appear effect that appears scaling up.
+ (instancetype)appearUpEffect;

/// Convenience initializer for an appear effect that appears scaling down.
+ (instancetype)appearDownEffect;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Disappear Effect

/// A symbol effect that applies the Disappear animation to
/// symbol images.
///
/// The Disappear animation makes the symbol visible either as a whole,
/// or one motion group at a time.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolDisappearEffect : NSSymbolEffect

/// The default disappear effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer for a disappear effect that disappears scaling up.
+ (instancetype)disappearUpEffect;

/// Convenience initializer for a disappear effect that disappears scaling down.
+ (instancetype)disappearDownEffect;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Base Content Transitions

/// An abstract base class for transitions that can be applied to both NSImageViews and
/// UIImageViews that have symbol-based images.
///
/// Don't use this class directly, instead use any of the concrete subclasses.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolContentTransition : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - Replace Content Transition

/// A symbol effect that animates the replacement of one symbol image
/// with another.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolReplaceContentTransition : NSSymbolContentTransition

/// The default replace transition, determined by the system.
+ (instancetype)transition;

/// Convenience initializer for a replace content transition where the initial symbol
/// scales down as it is removed, and the new symbol scales up as it is added.
+ (instancetype)replaceDownUpTransition;

/// Convenience initializer for a replace content transition where the initial symbol
/// scales up as it is removed, and the new symbol scales up as it is added.
+ (instancetype)replaceUpUpTransition;

/// Convenience initializer for a replace content transition where the initial symbol
/// is removed with no animation, and the new symbol scales up as it is added.
+ (instancetype)replaceOffUpTransition;

/// Returns a copy of the content transition that animates incrementally, by layer.
- (instancetype)transitionWithByLayer;

/// Returns a copy of the content transition that animates all layers of the symbol simultaneously.
- (instancetype)transitionWithWholeSymbol;

@end

#pragma mark - Automatic Content Transition

/// The default symbol transition, resolves to a particular transition in a
/// context-sensitive manner.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolAutomaticContentTransition : NSSymbolContentTransition

/// The default automatic transition, determined by the system.
+ (instancetype)transition;

@end


NS_HEADER_AUDIT_END(nullability, sendability)

#endif /* NSSymbolEffect_h */
