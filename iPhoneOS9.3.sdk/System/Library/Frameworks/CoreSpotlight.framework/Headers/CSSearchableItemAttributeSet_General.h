//
//  CSSearchableItemAttributeSet_General.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

@interface CSSearchableItemAttributeSet (CSGeneral)

//A localized string to be displayed in the UI for this item.
@property(nullable, copy) NSString *displayName;

//An array of localized strings of alternate display names for this item.
@property(nullable, copy) NSArray<NSString*> *alternateNames;

//This is the complete path to the item.
@property(nullable, copy) NSString *path;

//Optional file URL representing the content to be indexed
@property(nullable, strong) NSURL *contentURL;

//Optional file URL pointing to a thumbnail image for this item
@property(nullable, strong) NSURL *thumbnailURL;

//Optional image data for thumbnail for this item
@property(nullable, copy) NSData *thumbnailData;

//For activities, this is the unique identifier for the item this activity is related to
@property(nullable, copy) NSString *relatedUniqueIdentifier;

//This is the date that the last metadata attribute was changed.
@property(nullable, strong) NSDate *metadataModificationDate;

//UTI Type pedigree for an item.  Common types can be found in UTCoreTypes.h
@property(nullable, copy) NSString *contentType;

@property(nullable, copy) NSArray<NSString*> *contentTypeTree;

//Represents keywords associated with this particular item.
//Example Keywords might be Birthday,Important etc.
@property(nullable, copy) NSArray<NSString*> *keywords;

//The title of this particular item.
//Title of the document, or it could be the title of this mp3 or a subject of a mail message.
@property(nullable, copy) NSString *title;

@end

@interface CSSearchableItemAttributeSet (CSActionExtras)
// If supportsPhoneCall is 1 and the item has the phoneNumbers property, then the phone number may be used to initiate phone calls. This should be used to indicate that using the phone number is appropriate, and a primary action for the user. For example, supportsPhoneCall would be set on a business, but not an academic paper that happens to have phone numbers for the authors or the institution.
@property (nullable, copy) NSNumber *supportsPhoneCall;

// If supportsNavigation is set to 1, and the item has the latitude and longitude properties set, then the latitude and longitude may be used for navigation. For example, supportsNavigation would be set on a restaurant review, but not on a photo.
@property (nullable, copy) NSNumber *supportsNavigation;
@end

@interface CSSearchableItemAttributeSet(CSContainment)
@property(nullable, copy) NSString *containerTitle;
@property(nullable, copy) NSString *containerDisplayName;
@property(nullable, copy) NSString *containerIdentifier;
@property(nullable, copy) NSNumber *containerOrder;
@end


