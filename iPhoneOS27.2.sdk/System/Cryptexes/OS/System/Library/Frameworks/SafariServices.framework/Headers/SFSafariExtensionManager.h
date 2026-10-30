//  Copyright © 2025 Apple Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

@class SFSafariExtensionState;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_SWIFT_SENDABLE
SF_EXTERN API_AVAILABLE(ios(26.2), visionos(26.2)) API_UNAVAILABLE(tvos, watchos)
@interface SFSafariExtensionManager : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Returns information about the state of a Safari web extension contained within your app.
/// - Parameters:
///   - identifier: The bundle identifier for the Safari web extension to check.
///   - completionHandler: The completion handler the system calls with either the state of the extension or an error.
///     - term state: An object that describes the current state of the Safari web extension, or `nil` if the system can't find the extension.
///     - term error: An error object indicating the reason for the failure, or `nil` if no failure occurs.
+ (void)getStateOfExtensionWithIdentifier:(NSString *)identifier completionHandler:(void (^)(SFSafariExtensionState * _Nullable state, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(stateOfExtension(withIdentifier:));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
