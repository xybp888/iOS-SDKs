// Copyright © 2024 Apple Inc. All rights reserved.

#import <SafariServices/SFFoundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class BEWebAppManifest;

SF_EXTERN API_AVAILABLE(ios(18.2))
@interface SFAddToHomeScreenInfo : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;

- (SFAddToHomeScreenInfo *)initWithManifest:(BEWebAppManifest *)manifest NS_DESIGNATED_INITIALIZER;

/*! @abstract A property for the web app manifest.
 This is only available to apps that can use BrowserEngineKit.
*/
@property (nonatomic, readonly, copy) BEWebAppManifest *manifest;

/*! @abstract An optional item for providing the website's cookies.
 These will be copied to the Home Screen web app's data store. This will
 only be used if the manifest is non-nil and a Home Screen
 web app is created, not a Home Screen Bookmark.
 */
@property (nonatomic, copy) NSArray<NSHTTPCookie *> *websiteCookies;

@end

NS_ASSUME_NONNULL_END
