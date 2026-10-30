//
//  SRStateReporter.h
//  StateReporting
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

API_AVAILABLE(ios(27.0), macos(27.0), watchos(27.0), tvos(27.0), visionos(27.0))
NS_REFINED_FOR_SWIFT
/// An object unique per domain that records state transitions and volatile metadata updates.
///
/// `SRStateReporter` is the central object for recording your feature's or subsystem's current
/// state. Obtain an instance through the ``reporterForDomain:`` method, which guarantees
/// that every caller using the same domain string receives the same object.
///
/// A state is uniquely identified by its label and stable metadata. A transition to a new
/// state occurs when the label or stable metadata changes; reporting the same label and
/// stable metadata as the current state is a no-op. *Volatile metadata* provides additional context
/// within an ongoing state and is discarded when the next transition begins. Context
/// dictionaries must contain only `NSNumber`, `NSString`, or `NSDate` values.
///
/// Call ``reportTransitionToStateLabel:stableMetadata:volatileMetadata:`` whenever your feature
/// transitions to a new state. Pass `nil` as the label to signal that no state is active. Call
/// ``reportVolatileMetadataUpdate:`` to update volatile metadata without beginning a new state
/// transition. Calling either method more frequently than user interaction timescales can trigger
/// rate limiting, causing state updates to go unlogged.
///
/// ```objc
/// SRStateReporter *reporter =
///     [SRStateReporter reporterForDomain:@"com.example.myapp.checkout"];
///
/// [reporter reportTransitionToStateLabel:@"paymentSheet"
///                  stableMetadata:@{@"userTier": @"premium"}
///                 volatileMetadata:@{@"cartTotal": @(49.99)}];
/// ```
///
/// For Swift, use ``StateReporter``.
@interface SRStateReporter : NSObject

/// The reverse DNS-style domain name that identifies this reporter.
@property (strong, nonatomic, readonly, nonnull) NSString* domain;

/// Reports a transition to a new state.
///
/// A transition occurs only when `stateLabel` or `stableMetadata` changes from the current
/// state. If both are equal to the current values, this call is a no-op. Pass `nil` for
/// `stateLabel` to indicate that no state is currently active, clearing any previously
/// reported state. Any volatile metadata from the previous state is discarded when a new
/// transition begins. Calling this method more frequently than user interaction timescales
/// can trigger rate limiting, causing state updates to go unlogged.
///
/// - Parameters:
///   - stateLabel: A descriptive label for the new state, which must not be empty, or `nil` to clear the active state.
///   - stableMetadata: An optional dictionary with `NSString` keys that identifies the state
///     together with `stateLabel`. Dictionary values must be `NSNumber`, `NSString`, or `NSDate`.
///     Passing values of any other type is a programmer error and will raise an exception.
///   - volatileMetadata: An optional dictionary with `NSString` keys providing context likely to
///     change within this state. Dictionary values must be `NSNumber`, `NSString`, or
///     `NSDate`. Passing values of any other type is a programmer error and will raise an
///     exception.
- (void)reportTransitionToStateLabel:(nullable NSString*)stateLabel
					  stableMetadata:(nullable NSDictionary<NSString*, NSObject*>*)stableMetadata
					volatileMetadata:(nullable NSDictionary<NSString*, NSObject*>*)volatileMetadata;

/// Updates the volatile metadata within the current state without beginning a new transition.
///
/// Use this method to update rapidly-changing data — such as a progress value or a running
/// count — while staying within the same state. If no state is currently active, this call
/// is a no-op. Calling this method more frequently than user interaction timescales can
/// trigger rate limiting, causing updates to go unlogged.
///
/// - Parameter updatedMetadata: The updated volatile context, or `nil` to clear volatile metadata
///   without ending the current state. Dictionary values must be `NSNumber`,
///   `NSString`, or `NSDate`. Passing values of any other type is a programmer error and will
///   raise an exception.
- (void)reportVolatileMetadataUpdate:(nullable NSDictionary<NSString*, NSObject*>*)updatedMetadata;



/// Returns the reporter instance unique to the given domain name.
///
/// This method is the only way to obtain an `SRStateReporter`. Calling it multiple times with
/// the same domain string always returns the same object.
///
/// - Parameter domain: The reverse DNS-style name of the domain whose state you are reporting.
/// - Returns: The reporter instance for the specified domain.
+ (nonnull instancetype)reporterForDomain:(nonnull NSString*)domain;

- (nonnull instancetype)init NS_UNAVAILABLE;
@end
