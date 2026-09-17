//
//  CSSearchableItemAttributeSet_Messaging.h
//  CoreSpotlight
//
//  Copyright © 2015–2026 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>
#import <CoreSpotlight/CSPerson.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

//Well-known mailbox identifiers
extern NSString * const CSMailboxInbox API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
extern NSString * const CSMailboxDrafts API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
extern NSString * const CSMailboxSent API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
extern NSString * const CSMailboxJunk API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
extern NSString * const CSMailboxTrash API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
extern NSString * const CSMailboxArchive API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSSearchableItemAttributeSet (CSMessaging)

//Unique identifier for the account the item is associated with, if any
@property(nullable, copy) NSString *accountIdentifier;

//Array of the canonical handles of the account the item is associated with
//(IM handle, e-mail address, phone number...).
//E.g. in Mail's case, all the email addresses the account receives email on.
@property(nullable, copy) NSArray<NSString*> *accountHandles;

//Contains the HTML content of the document encoded as NSData of UTF-8 encoded string.
@property(nullable, copy) NSData *HTMLContentData;

//Contains the text content of the document.
@property(nullable, copy) NSString *textContent;

//An array of CSPerson objects representing the content of the From: field in an email
@property(nullable, copy) NSArray<CSPerson*> *authors;

//An array of CSPerson objects representing the content of the To: field in an email
@property(nullable, copy) NSArray<CSPerson*> *primaryRecipients;

//An array of CSPerson objects representing the content of the Cc: field in an email
@property(nullable, copy) NSArray<CSPerson*> *additionalRecipients;

//An array of CSPerson objects representing the content of the Bcc: field in an email
@property(nullable, copy) NSArray<CSPerson*> *hiddenAdditionalRecipients;

//Dictionary with all the headers of the message
//Keys are header names and values arrays of strings (because a header might be present multiple times in an email)
@property(nullable, copy) NSDictionary<NSString*,NSArray*> *emailHeaders;

//Array of Mailbox identifiers associated with the item. e.g. CSMailboxInbox, CSMailboxDrafts, CSMailboxSent, or a custom identifier etc.
@property(nullable, copy) NSArray<NSString*> *mailboxIdentifiers;

//The list of author/authors that have worked on this item.
//There could be 0 or more authors of a particular item.
//The order of the authors in the array is preserved, but is not intended to represent
//the main author or relative importance of the authors.
@property(nullable, copy) NSArray<NSString*> *authorNames;

//This attribute indicates the recipients of this item.
@property(nullable, copy) NSArray<NSString*> *recipientNames;

//This attribute indicates the author of the emails message addresses.
//(This is always the email address, and not the human readable version)
@property(nullable, copy) NSArray<NSString*> *authorEmailAddresses;

//This attribute indicates the recipients email addresses.
//(This is always the email address,  and not the human readable version).
@property(nullable, copy) NSArray<NSString*> *recipientEmailAddresses;

//This attribute indicates the author addresses of the document.
@property(nullable, copy) NSArray<NSString*> *authorAddresses;

//This attribute indicates the recipient addresses of the document.
@property(nullable, copy) NSArray<NSString*> *recipientAddresses;

//Phone numbers for this item.
@property(nullable, copy) NSArray<NSString*> *phoneNumbers;

//Email addresses for this item.
@property(nullable, copy) NSArray<NSString*> *emailAddresses;

//Instant message addresses for this item.
@property(nullable, copy) NSArray<NSString*> *instantMessageAddresses;

//This attribute indicates if the document is likely to be considered junk.  Should be 1 if true, 0 otherwise
@property(nonatomic, strong, getter=isLikelyJunk) NSNumber *likelyJunk;

@property(nonatomic, nullable, strong, readonly) NSNumber *isPriority API_AVAILABLE(macos(15.4), ios(18.4), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
