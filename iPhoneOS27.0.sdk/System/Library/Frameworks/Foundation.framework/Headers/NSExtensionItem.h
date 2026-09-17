/*	NSExtensionItem.h
        Copyright (c) 2013-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <Foundation/NSItemProvider.h>

#if __OBJC2__
/// An immutable collection of values representing different aspects of an item for the extension to act upon.
NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An immutable collection of values representing different aspects of an item for an extension to act upon.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface NSExtensionItem : NSObject<NSCopying, NSSecureCoding>

/// An optional title for the item.
@property(nullable, copy, NS_NONATOMIC_IOSONLY) NSAttributedString *attributedTitle;

/// Optional content text.
@property(nullable, copy, NS_NONATOMIC_IOSONLY) NSAttributedString *attributedContentText;

/// Optional array of media data associated with the extension item, including images, videos, and URLs.
///
/// This is not meant to be an array of alternate data formats/types, but instead a collection
/// to include in a social media post for example.
@property(nullable, copy, NS_NONATOMIC_IOSONLY) NSArray<NSItemProvider *> *attachments;

/// Optional dictionary of key-value data.
///
/// The key/value pairs accepted by the service are expected to be specified in the extension's @c Info.plist.
/// The values of @c NSExtensionItem's properties will be reflected into the dictionary.
@property(nullable, copy, NS_NONATOMIC_IOSONLY) NSDictionary *userInfo;

@end

/// Keys corresponding to properties exposed on the NSExtensionItem interface.
FOUNDATION_EXTERN NSString * _Null_unspecified const NSExtensionItemAttributedTitleKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// The key for the attributed content text property.
FOUNDATION_EXTERN NSString * _Null_unspecified const NSExtensionItemAttributedContentTextKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// The key for the attachments property.
FOUNDATION_EXTERN NSString * _Null_unspecified const NSExtensionItemAttachmentsKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

NS_HEADER_AUDIT_END(nullability, sendability)
#endif
