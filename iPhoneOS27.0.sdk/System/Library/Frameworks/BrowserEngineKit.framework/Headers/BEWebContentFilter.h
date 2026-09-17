//
//  BEWebContentFilter.h
//  BrowserEngineKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>

#if BROWSERENGINEKIT_HAS_UIKIT
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

/*! @enum BEWebContentFilterPermissionDecision
 @abstract The outcome of a Permission Request to add URL to allow-list
 @constant BEWebContentFilterPermissionDecisionError  Default value, returned if there is failure to retrieve decision.
 @constant BEWebContentFilterPermissionDecisionAllowed  Request to permit URL is allowed. URL is added to filter allow-list.
 @constant BEWebContentFilterPermissionDecisionDenied  Request to permit URL access is denied.
 @constant BEWebContentFilterPermissionDecisionPending  Request to permit URL is pending.
 */
typedef NS_ENUM(NSInteger, BEWebContentFilterPermissionDecision) {
    BEWebContentFilterPermissionDecisionError,
    BEWebContentFilterPermissionDecisionAllowed,
    BEWebContentFilterPermissionDecisionDenied,
    BEWebContentFilterPermissionDecisionPending,
} NS_SWIFT_NAME(BEWebContentFilter.PermissionDecision) API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, watchos, tvos, visionos);

/// An object that represents a web content filter
API_AVAILABLE(ios(26.2))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BEWebContentFilter : NSObject
/**
 @abstract Determines whether the built-in web content filter is active.
 @returns YES if the built-in web content filter is active, and NO if it isn't.
 */
@property (class, readonly) BOOL shouldEvaluateURLs;

/**
 @abstract Evaluates whether a URL should be blocked and if so, provides a
 response body representing the HTML of a blocking page.
 @param url The URL to be evaluated.
 @param completionHandler The completion block to be invoked with result when
 evaluation is complete. Result is YES if the url should be blocked, and NO if it isn't.
 @discussion This method performs a lazy initialization of some objects, so the
 first call could take longer than subsequent calls.
 */
- (void)evaluateURL:(NSURL *)url completionHandler:(void (^)(BOOL shouldBlock,  NSData * _Nullable blockPageRepresentation))completionHandler;

/**
 @abstract Evaluates whether a URL should be blocked and if yes, provides a
 response body representing the HTML of the blocking content that will be displayed
 in either the blocked main document or blocked subframe. 
 @param url The URL to be evaluated, either a main frame or subframe URL. 
 @param mainFrameURL The URL of the main document and root of the transitive trust
 policy. This may match the evaluated `url` param for main frame navigations.
 @param isMainFrame Whether the evaluated URL is a main frame or subframe navigation.
 YES if main frame navigation and NO otherwise.
 @param completionHandler The completion block to be invoked when evaluation is 
 complete.
 */
- (void)evaluateURL:(NSURL *)url mainFrameURL:(NSURL *)mainFrameURL isMainFrame:(BOOL)isMainFrame completionHandler:(void (^)(BOOL shouldBlock, NSData * _Nullable blockPageRepresentation))completionHandler API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, watchos, tvos, visionos);

/**
 @abstract Adds blocked URL to built-in web content filter's allowlist.
 @param url The URL to be added.
 @param completionHandler The completion block to be called when the add
 operation is complete, with result of the operation. Result is YES if the url is added
 successfully, and NO if it isn't.
 */
- (void)allowURL:(NSURL *)url completionHandler:(void (^)(BOOL didAllow, NSError * _Nullable error))completionHandler;

#if BROWSERENGINEKIT_HAS_UIVIEW
/**
 @abstract Request a blocked URL to be added to built-in web content filter's allowlist
 @param url The URL to be added.
 @param referrerURL The URL that initiated the permission request. This determines whether or not parent approval is done remotely or on-device.
 @param presentingView The view to present permission UI from.
 @param completionHandler The completion block to be called when the add
 operation is complete, with result of the operation. Result is BEWebContentFilterPermissionDecision that holds
 the outcome of the request for access.
 */
- (void)requestPermissionForURL:(NSURL *)url referrerURL:(NSURL * _Nullable)referrerURL presentingView:(UIView * _Nullable)presentingView completionHandler:(void (^)(BEWebContentFilterPermissionDecision result, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macos, watchos, tvos, visionos);
#endif
@end

NS_ASSUME_NONNULL_END
