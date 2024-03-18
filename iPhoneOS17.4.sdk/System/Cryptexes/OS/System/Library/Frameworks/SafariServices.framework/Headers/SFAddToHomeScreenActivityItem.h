// Copyright © 2023 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! 
 @protocol SFAddToHomeScreenActivityItem
 An activity item for adding "Add to Home Screen" activity type into activity view (share sheet) list.
 */
API_AVAILABLE(ios(17.4))
@protocol SFAddToHomeScreenActivityItem <NSObject>

/*! @abstract The URL for the home screen bookmark item.
 The URL scheme should be HTTP or HTTPS.
 This URL will be shown to user in the confirmation sheet.
 */
@property (nonatomic, readonly) NSURL *URL;

/*! @abstract The title for the home screen bookmark item.
 This URL will be shown to user in the confirmation sheet.
 */
@property (nonatomic, readonly) NSString *title;

/*! @abstract An optional item provider for providing website icons.
 This provider should register and provide an item with the UIImage type.
 A default icon for the website will be shown to user if an icon is not provided.
 */
@optional
@property (nonatomic, nullable, readonly) NSItemProvider *iconItemProvider;

@end

NS_ASSUME_NONNULL_END

