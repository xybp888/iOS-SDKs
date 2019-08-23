//
//  SSReadingList.h
//  SafariServices
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @class SSReadingList
    Provides an interface for adding to a user's Reading List.
*/
NS_CLASS_AVAILABLE_IOS(7_0)
@interface SSReadingList : NSObject

/*!
    @method defaultReadingList
    @result Returns a pointer to a shared instance of SSReadingList, or nil if access to Reading List is not permitted.
    @discussion This class method to obtain the instance of SSReadingList should used instead of direct alloc and init.  
*/
+ (nullable SSReadingList *)defaultReadingList;

- (instancetype)init NS_UNAVAILABLE;

/*!
    @method supportsURL:
    @abstract Determines if the provided URL can be added to Reading List.
    @param URL The URL to be tested for Reading List support.
    @result Returns YES if the URL is supported by Reading List, NO if not.
*/
+ (BOOL)supportsURL:(NSURL *)URL;

/*!
    @method addReadingListItemWithURL:title:previewText:error:
    @abstract Adds an item to the Reading List.
    @param URL The URL of the item.
    @param title The title string of the item, or nil.
    @param previewText A string shown as detail text for the item, or nil.
    @param error Describes the error that occurred.
    @result Returns YES if the item was added, otherwise returns NO and error param is set.
    @discussion Only URLs with http:// or https:// schemes are supported by Reading List.
*/
- (BOOL)addReadingListItemWithURL:(NSURL *)URL title:(nullable NSString *)title previewText:(nullable NSString *)previewText error:(NSError **)error NS_AVAILABLE_IOS(7_0);

@end

// domain for NSError
SF_EXTERN NSString *const SSReadingListErrorDomain NS_AVAILABLE_IOS(7_0);

typedef NS_ENUM(NSInteger, SSReadingListErrorCode) {
    SSReadingListErrorURLSchemeNotAllowed = 1,
} NS_ENUM_AVAILABLE_IOS(7_0);

NS_ASSUME_NONNULL_END
