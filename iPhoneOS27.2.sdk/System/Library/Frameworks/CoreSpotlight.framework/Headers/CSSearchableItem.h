//
//  CSSearchableItem.h
//  CoreSpotlight
//
//  Copyright © 2015–2026 Apple Inc. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// When opening a document from Spotlight, the application's application:willContinueUserActivityWithType:
// method will get called with CSSearchableItemActionType, followed by  application:continueUserActivity:restorationHandler:
// with an NSUserActivity where the userInfo dictionary has a key value pair where CSSearchableItemActivityIdentifier is the key
// and the value is the uniqueIdentifier used when creating the item.
extern NSString * const CSSearchableItemActionType API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
extern NSString * const CSSearchableItemActivityIdentifier API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

// For custom actions on iOS, the userInfo dictionary also has another key value pair where CSActionIdentifier is the key
// and the value is the action tapped in the UI based on what was indexed by the app.
extern NSString * const CSActionIdentifier API_AVAILABLE(ios(15.0), visionos(1.0)) API_UNAVAILABLE(macos, tvos, watchos);

// When continuing a query from Spotlight, the application's -application:willContinueUserActivityWithType:
// method will get called with CSQueryContinuationActionType, followed by -application:continueUserActivity:restorationHandler:
// with an NSUserActivity where the userInfo dictionary has a key value pair with CSSearchQueryString as the key
// and the value is the string the application should use when performing its query.
// The application should declare that it supports the query continuation by adding the CoreSpotlightContinuation key to its Info.plist:
//
//    <key>CoreSpotlightContinuation</key>
//    <true/>
//
extern NSString * const CSQueryContinuationActionType API_AVAILABLE(macos(10.12), ios(10.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
extern NSString * const CSSearchQueryString API_AVAILABLE(macos(10.12), ios(10.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

typedef NS_OPTIONS(NSUInteger, CSSearchableItemUpdateListenerOptions) {
    CSSearchableItemUpdateListenerOptionDefault        = 0,
    CSSearchableItemUpdateListenerOptionSummarization  = 1 << 1, // textContentSummary
    CSSearchableItemUpdateListenerOptionPriority       = 1 << 2, // isPriority
} NS_SWIFT_NAME(CSSearchableItem.UpdateListenerOptions) API_AVAILABLE(macos(15.4), ios(18.4), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSSearchableItem : NSObject <NSSecureCoding, NSCopying>

// uniqueIdentifier can be null, in which case one will be generated.
// If passing in null, you must retrieve and store the generated identifier in persistent storage, so that you can open the appropriate item when recalled in a query
- (instancetype)initWithUniqueIdentifier:(nullable NSString *)uniqueIdentifier
                        domainIdentifier:(nullable NSString *)domainIdentifier
                            attributeSet:(CSSearchableItemAttributeSet *)attributeSet;

// For comparison of items ranked by the query
- (NSComparisonResult)compareByRank:(CSSearchableItem *)other API_AVAILABLE(macos(13.0), ios(16.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

// Should be unique to your application group.
// REQUIRED since this is the way you will refer to the item to update the index / delete it from the index
// Starts with an UUID for ease of use, but you can replace it with an UID of your own before the item is first indexed if you wish.
@property (copy) NSString *uniqueIdentifier;

// An optional identifier that represents the "domain" or owner of this item.
// This might be an identifier for a mailbox in an account whose indexed data you may want to remove when the account is deleted.
// In that case the domainIdentifier should be of the form <account-id>.<mailbox-id> where <account-id> and <mailbox-id> should not contains periods.
// Calling deleteSearchableItemsWithDomainIdentifiers with <account-id>.<mailbox-id> will delete all items with that domain identifier.
// Calling deleteSearchableItemsWithDomainIdentifiers with <account-id> will delete all items with <account-id> and any <mailbox-id>.
@property (copy, nullable) NSString *domainIdentifier;

// Searchable items have an expiration date or time to live.  By default it's set to 1 month.
@property (copy, null_resettable) NSDate * expirationDate;

// Set of attributes containing meta data for the item
@property (strong) CSSearchableItemAttributeSet *attributeSet;

// A flag to specify whether or not this item should be treated as an update
// By default index insertions are treated as a full delete of any existing item, followed by an insert, and the client needs to specify whether or not this should be treated as an update.
// If an item is marked as an update, but does not already exist in the index, it will be dropped during the attempted indexing.
// In update mode, attributes can be marked as deleted by setting their value to nil.
@property (assign) BOOL isUpdate;

// An option flag to specify whether to listen for specific attribute updates that Spotlight can provide.
// A developer may be notified by a call of searchableItemsDidUpdate to its delegate, where specific properties will be available on the item.
@property (assign) CSSearchableItemUpdateListenerOptions updateListenerOptions API_AVAILABLE(macos(15.4), ios(18.4), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
