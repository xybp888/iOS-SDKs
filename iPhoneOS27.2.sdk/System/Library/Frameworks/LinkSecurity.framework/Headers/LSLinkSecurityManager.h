/*!
 @header     LSLinkSecurityManager
 @copyright  Copyright (c) 2026 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         LSLinkSecurityManager
 @abstract      Store and check links to be handled with additional security
 */
API_AVAILABLE(ios(27.0), macCatalyst(27.0), visionos(27.0), macos(27.0), watchos(27.0), tvos(27.0))
@interface LSLinkSecurityManager: NSObject

/*!
 @property   sharedManager
 @abstract   Shared instance of LSLinkSecurityManager
*/
@property (class, nonatomic, strong, readonly) LSLinkSecurityManager *sharedManager;

/*!
 @property   hasFlaggedURLs
 @abstract   Whether there are any URLs that currently flagged
*/
@property (nonatomic, assign, readonly) BOOL hasFlaggedURLs;

/*!
@method     addFlaggedURL:
@abstract   Flags a given URL for additional security considerations
@param      url  The URL to flag
*/
- (void)addFlaggedURL:(NSURL *)url;

/*!
@method     addFlaggedURLs:
@abstract   Marks Flags a given URLs for additional security considerations
@param      urls  A list of URLs to flag
*/
- (void)addFlaggedURLs:(NSArray<NSURL *> *)urls;

/*!
@method     checkIsFlaggedURL:completion:
@abstract   Check if a given URL is flagged
@param      url  The URL to check
@param      completion  A completion handler with an argument indicating if the URL is flagged
*/
- (void)checkIsFlaggedURL:(NSURL *)url completion:(void (^)(BOOL))completion NS_SWIFT_ASYNC_NAME(isFlaggedURL(_:));

@end

NS_ASSUME_NONNULL_END
