//
//  CSSearchableItemAttributeSet_Events.h
//  CoreSpotlight
//
//  Copyright © 2015–2026 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

#import <Foundation/Foundation.h>

API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSSearchableItemAttributeSet (CSEvents)

//Date this item is due.
@property(nullable, strong) NSDate *dueDate;

//Date the item was completed
@property(nullable, strong) NSDate *completionDate;

//Start date of this item.
@property(nullable, strong) NSDate *startDate;

//End date for this item.
@property(nullable, strong) NSDate *endDate;

//Important dates associated with this item
@property(nullable, copy) NSArray<NSDate *> *importantDates;

//Whether this event covers complete days
@property(nullable, strong) NSNumber *allDay;

@end
