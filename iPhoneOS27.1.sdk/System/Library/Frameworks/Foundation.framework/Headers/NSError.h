/*	NSError.h
	Copyright (c) 2003-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDictionary<KeyType, ObjectType>, NSArray<ObjectType>, NSString;

typedef NSString *NSErrorDomain;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The error domain for Cocoa errors.
FOUNDATION_EXPORT NSErrorDomain const NSCocoaErrorDomain;

/// The error domain for POSIX errors.
FOUNDATION_EXPORT NSErrorDomain const NSPOSIXErrorDomain;
/// The error domain for Mac OS 9/Carbon errors.
FOUNDATION_EXPORT NSErrorDomain const NSOSStatusErrorDomain;
/// The error domain for Mach errors.
FOUNDATION_EXPORT NSErrorDomain const NSMachErrorDomain;

/// These keys may exist in the user info dictionary.
typedef NSString *NSErrorUserInfoKey;

/// The underlying error that caused this error.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSUnderlyingErrorKey;

// Key in userInfo. A recommended standard way to embed a list of several NSErrors from underlying calls. The value of this key should be an NSArray of NSError. This value is independent from the value of `NSUnderlyingErrorKey` - neither, one, or both may be set.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSMultipleUnderlyingErrorsKey API_AVAILABLE(macos(11.3), ios(14.5), watchos(7.4), tvos(14.5));

/// A human-readable description of the error.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSLocalizedDescriptionKey;             // NSString, a complete sentence (or more) describing ideally both what failed and why it failed.
/// A human-readable reason for the failure.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSLocalizedFailureReasonErrorKey;      // NSString, a complete sentence (or more) describing why the operation failed.
/// A human-readable suggestion for recovering from the error.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSLocalizedRecoverySuggestionErrorKey; // NSString, a complete sentence (or more) describing what the user can do to fix the problem.
/// An array of localized titles for buttons appropriate for displaying in an alert panel.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSLocalizedRecoveryOptionsErrorKey;    // NSArray of NSStrings corresponding to button titles.
/// An object that conforms to the `NSErrorRecoveryAttempting` protocol.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSRecoveryAttempterErrorKey;           // Instance of a subclass of NSObject that conforms to the NSErrorRecoveryAttempting informal protocol
/// A string to display in response to an attempt to show help related to an error.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSHelpAnchorErrorKey;                  // NSString containing a help anchor
FOUNDATION_EXPORT NSErrorUserInfoKey const NSDebugDescriptionErrorKey API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));     // NSString. This provides a string which will be shown when constructing the debugDescription of the NSError, to be used when debugging or when formatting the error with %@.  This string will never be used in localizedDescription, so will not be shown to the user.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSLocalizedFailureErrorKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));  // NSString, a complete sentence (or more) describing what failed.  Setting a value for this key in userInfo dictionary of errors received from framework APIs is a good way to customize and fine tune the localizedDescription of an NSError.  As an example, for Foundation error code NSFileWriteOutOfSpaceError, setting the value of this key to "The image library could not be saved." will allow the localizedDescription of the error to come out as "The image library could not be saved. The volume Macintosh HD is out of space." rather than the default (say) “You can't save the file ImgDatabaseV2 because the volume Macintosh HD is out of space."

// Other standard keys in userInfo, for various error codes
/// The corresponding value is an `NSNumber` object containing the `NSStringEncoding` value.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSStringEncodingErrorKey ;
/// The URL which caused the error.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSURLErrorKey;              // NSURL
/// The file path of the error.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSFilePathErrorKey;         // NSString

/// Information about an error condition including a domain, a domain-specific error code, and application-specific information.
///
/// Objective-C methods can signal an error condition by returning an ``NSError`` object by reference, which provides additional information about the kind of error and any underlying cause, if one can be determined. An ``NSError`` object may also provide localized error descriptions suitable for display to the user in its user info dictionary. See [Error Handling Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ErrorHandlingCocoa/ErrorHandling/ErrorHandling.html#//apple_ref/doc/uid/TP40001806) for more information.
///
/// Methods in Foundation and other Cocoa frameworks most often produce errors in the Cocoa error domain (``NSCocoaErrorDomain``); error codes for the Cocoa Error Domain are documented in the <doc:foundation-constants>. There are also predefined domains corresponding to Mach (``NSMachErrorDomain``), POSIX (``NSPOSIXErrorDomain``), and Carbon (``NSOSStatusErrorDomain``) errors.
///
/// ``NSError`` is "toll-free bridged" with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cferror>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information.
///
/// ### Subclassing Notes
///
/// Applications may choose to create subclasses of `NSError`, for example, to provide better localized error strings by overriding ``localizedDescription``.
NS_SWIFT_SENDABLE
@interface NSError : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new API_DEPRECATED("Use +[NSError errorWithDomain:code:userInfo:] to specify an error domain and code instead", macos(10.0, 27.0), ios(2.0, 27.0), watchos(2.0, 27.0), tvos(9.0, 27.0), visionos(1.0, 27.0));

- (instancetype)init 
#ifdef __swift__
API_DEPRECATED("Use init(domain:code:userInfo:) to specify an error domain and code instead.", macos(10.0, 27.0), ios(2.0, 27.0), watchos(2.0, 27.0), tvos(9.0, 27.0), visionos(1.0, 27.0))
#else
API_DEPRECATED("Use -[NSError initWithDomain:code:userInfo:] to specify an error domain and code instead.", macos(10.0, 27.0), ios(2.0, 27.0), watchos(2.0, 27.0), tvos(9.0, 27.0), visionos(1.0, 27.0))
#endif
;

/// Returns an `NSError` object initialized for a given domain and code with a given @c userInfo dictionary.
///
/// This is the designated initializer for @c NSError. @c domain must not be @c nil.
/// @param domain The error domain---this can be one of the predefined @c NSError domains, or an arbitrary string describing a custom domain.
/// @param code The error code for the error.
/// @param dict The @c userInfo dictionary for the error. May be @c nil.
/// @return An @c NSError object initialized for @c domain with the specified error @c code and the dictionary of arbitrary data @c userInfo.
- (instancetype)initWithDomain:(NSErrorDomain)domain code:(NSInteger)code userInfo:(nullable NSDictionary<NSErrorUserInfoKey, id> *)dict NS_DESIGNATED_INITIALIZER;

/// Creates and initializes an @c NSError object for a given domain and code with a given @c userInfo dictionary.
///
/// @param domain The error domain---this can be one of the predefined @c NSError domains, or an arbitrary string describing a custom domain.
/// @param code The error code for the error.
/// @param dict The @c userInfo dictionary for the error. May be @c nil.
/// @return An @c NSError object for @c domain with the specified error @c code and the dictionary of arbitrary data @c userInfo.
+ (instancetype)errorWithDomain:(NSErrorDomain)domain code:(NSInteger)code userInfo:(nullable NSDictionary<NSErrorUserInfoKey, id> *)dict;

/// A string containing the error domain.
///
/// Domains are described by names that are arbitrary strings used to differentiate groups of codes;
/// for custom domains, using reverse-DNS naming will help avoid conflicts.
@property (readonly, copy) NSErrorDomain domain;

/// The error code.
///
/// Codes are domain-specific.
@property (readonly) NSInteger code;

/// The user info dictionary.
///
/// Contains application-specific data related to the error. Examples of keys that might be included are
/// @c NSLocalizedDescriptionKey, @c NSFilePathErrorKey, and @c NSUnderlyingErrorKey.
@property (readonly, copy) NSDictionary<NSErrorUserInfoKey, id> *userInfo;

/// A string containing the localized description of the error.
///
/// For instance, for `NSFileReadNoPermissionError`: "The file "File Name" couldn't be opened because you don't have permission to view it.". This message should ideally indicate what failed and why it failed. This value either comes from `NSLocalizedDescriptionKey`, or `NSLocalizedFailureErrorKey` + `NSLocalizedFailureReasonErrorKey`, or `NSLocalizedFailureErrorKey`. The steps this takes to construct the description include:
/// 1. Look for NSLocalizedDescriptionKey in userInfo, use value as-is if present.
/// 2. Look for NSLocalizedFailureErrorKey in userInfo. If present, use, combining with value for NSLocalizedFailureReasonErrorKey if available.
/// 3. Fetch NSLocalizedDescriptionKey from userInfoValueProvider, use value as-is if present.
/// 4. Fetch NSLocalizedFailureErrorKey from userInfoValueProvider. If present, use, combining with value for NSLocalizedFailureReasonErrorKey if available.
/// 5. Look for NSLocalizedFailureReasonErrorKey in userInfo or from userInfoValueProvider; combine with generic "Operation failed" message.
/// 6. Last resort localized but barely-presentable string manufactured from domain and code. The result is never nil.
/// This value either comes from @c NSLocalizedDescriptionKey, or @c NSLocalizedFailureErrorKey combined with
/// @c NSLocalizedFailureReasonErrorKey, or a last-resort string manufactured from the domain and code.
@property (readonly, copy) NSString *localizedDescription;

/// A string containing the localized explanation of the reason for the error.
///
/// Return a complete sentence which describes why the operation failed.
///
/// For instance, for `NSFileReadNoPermissionError`: "You don't have permission.". In many cases this will be just the "because" part of the error message (but as a complete sentence, which makes localization easier).  Default implementation of this picks up the value of `NSLocalizedFailureReasonErrorKey` from the userInfo dictionary. If not present, it consults the `userInfoValueProvider` for the domain, and if that returns `nil`, this also returns `nil`.
/// The object in the user info dictionary for the key @c NSLocalizedFailureReasonErrorKey.
/// If not present, consults the @c userInfoValueProvider for the domain. Returns @c nil if unavailable.
@property (nullable, readonly, copy) NSString *localizedFailureReason;

/// A string containing the localized recovery suggestion for the error.
///
/// For instance, for `NSFileReadNoPermissionError`: "To view or change permissions, select the item in the Finder and choose File > Get Info.". The default implementation of this picks up the value of `NSLocalizedRecoverySuggestionErrorKey` from the `userInfo` dictionary. If not present, it consults the `userInfoValueProvider` for the domain, and if that returns `nil`, this also returns `nil`.
///
/// The object in the user info dictionary for the key @c NSLocalizedRecoverySuggestionErrorKey.
/// The returned string is suitable for displaying as the secondary message in an alert panel.
/// Returns @c nil if unavailable.
@property (nullable, readonly, copy) NSString *localizedRecoverySuggestion;

/// An array containing the localized titles of buttons appropriate for displaying in an alert panel.
///
/// The object in the user info dictionary for the key @c NSLocalizedRecoveryOptionsErrorKey.
///
/// These should match the string provided as a part of `localizedRecoverySuggestion`.  The first string would be the title of the right-most and default button, the second one next to it, and so on. If used in an alert the corresponding default return values are `NSAlertFirstButtonReturn` + `n`. Default implementation of this picks up the value of `NSLocalizedRecoveryOptionsErrorKey` from the `userInfo` dictionary. If not present, it consults the `userInfoValueProvider` for the domain, and if that returns `nil`, this also returns `nil`. `nil` return usually implies no special suggestion, which would imply a single "OK" button.
///
/// Returns @c nil if no recovery options are available, which typically implies a single "OK" button.
@property (nullable, readonly, copy) NSArray<NSString *> *localizedRecoveryOptions;

/// The object in the user info dictionary corresponding to the @c NSRecoveryAttempterErrorKey key.
///
/// The recovery attempter must be an object that conforms to the @c NSErrorRecoveryAttempting informal protocol.
/// It must be able to correctly interpret an index into the @c localizedRecoveryOptions array.
/// The default implementation of this picks up the value of `NSRecoveryAttempterErrorKey` from the `userInfo` dictionary. If not present, it consults the `userInfoValueProvider` for the domain. If that returns `nil`, this also returns `nil`.
/// Returns @c nil if not present in the user info or from the @c userInfoValueProvider.
@property (nullable, readonly, strong) id recoveryAttempter;

/// A string to display in response to an alert panel help anchor button being pressed.
///
/// The object in the user info dictionary for the key @c NSHelpAnchorErrorKey.
/// Returns @c nil if not present.
@property (nullable, readonly, copy) NSString *helpAnchor;

/* Return a list of underlying errors, if any. It includes the values of both NSUnderlyingErrorKey and NSMultipleUnderlyingErrorsKey. If there are no underlying errors, returns an empty array.
*/
@property (readonly, copy) NSArray<NSError *> *underlyingErrors API_AVAILABLE(macos(11.3), ios(14.5), watchos(7.4), tvos(14.5));

/// Specifies a block to call when the corresponding property is not present in the user info dictionary.
///
/// The provider is called synchronously from the implementations of @c localizedDescription, @c localizedFailureReason,
/// @c localizedRecoverySuggestion, @c localizedRecoveryOptions, @c recoveryAttempter, @c helpAnchor, and @c debugDescription
/// when the underlying value is not present in the @c userInfo dictionary of NSError instances with the specified domain.
/// The provider should return @c nil for any keys it is not able to provide and any keys it does not recognize.
/// The results are not cached. It is expected that only the “owner” of an NSError domain specifies the provider, and this is done once. This facility is not meant for consumers of errors to customize the userInfo entries.  This facility should not be used to customize the behaviors of error domains provided by the system.
/// If an appropriate result for the requested key cannot be provided, return nil rather than choosing to manufacture a generic fallback response such as "Operation could not be completed, error 42." `NSError` will take care of the fallback cases.
/// @param errorDomain The error domain of the provider.
/// @param provider A block to be executed synchronously at the time a corresponding property is accessed.
+ (void)setUserInfoValueProviderForDomain:(NSErrorDomain)errorDomain provider:(id _Nullable (NS_SWIFT_SENDABLE ^ _Nullable)(NSError *err, NSErrorUserInfoKey userInfoKey))provider API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Returns any user info provider specified for a given error domain.
///
/// @param errorDomain The error domain of the user info provider.
/// @return The user info provider of the error domain, or @c nil if none is specified.
+ (id _Nullable (NS_SWIFT_SENDABLE ^ _Nullable)(NSError *err, NSErrorUserInfoKey userInfoKey))userInfoValueProviderForDomain:(NSErrorDomain)errorDomain API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

@end


@interface NSObject(NSErrorRecoveryAttempting)

/* Given that an error alert has been presented document-modally to the user, and the user has chosen one of the error's recovery options, attempt recovery from the error, and send the selected message to the specified delegate. The option index is an index into the error's array of localized recovery options. The method selected by didRecoverSelector must have the same signature as:

    - (void)didPresentErrorWithRecovery:(BOOL)didRecover contextInfo:(void *)contextInfo;

The value passed for didRecover must be YES if error recovery was completely successful, NO otherwise.
*/
- (void)attemptRecoveryFromError:(NSError *)error optionIndex:(NSUInteger)recoveryOptionIndex delegate:(nullable id)delegate didRecoverSelector:(nullable SEL)didRecoverSelector contextInfo:(nullable void *)contextInfo;

/* Given that an error alert has been presented applicaton-modally to the user, and the user has chosen one of the error's recovery options, attempt recovery from the error, and return YES if error recovery was completely successful, NO otherwise. The recovery option index is an index into the error's array of localized recovery options.
*/
- (BOOL)attemptRecoveryFromError:(NSError *)error optionIndex:(NSUInteger)recoveryOptionIndex;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

