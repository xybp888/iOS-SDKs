/*
    NSFetchedResultsController.h
    Core Data
    Copyright (c) 2009-2015, Apple Inc.
    All rights reserved.

Class Overview
==============

This class is intended to efficiently manage the results returned from a Core Data fetch request.

You configure an instance of this class using a fetch request that specifies the entity, optionally a filter predicate, and an array containing at least one sort ordering. When you execute the fetch, the instance efficiently collects information about the results without the need to bring all the result objects into memory at the same time. As you access the results, objects are automatically faulted into memory in batches to match likely access patterns, and objects from previous accessed disposed of. This behavior further serves to keep memory requirements low, so even if you traverse a collection containing tens of thousands of objects, you should never have more than tens of them in memory at the same time.

This class is tailored to work in conjunction with UITableView, however you are free to use it with your own views. UITableView expects its data source to present the results as an array of sections made up of rows. NSFetchedResultsController can efficiently analyze the result of the fetch request and pre-compute all the information about sections in the result set. Moreover, the controller can cache the results of this computation so that if the same data is subsequently re-displayed, the work does not have to be repeated. In addition:
* The controller monitors changes to objects in its associated managed object context, and updates the results accordingly. It reports changes in the results set to its delegate.
* The controller automatically purges unneeded objects if it receives an application low memory notification.
* The controller maintains a persistent cache of the section information across application launches if the cacheName is not nil.  If caching is enabled, you must not mutate the fetch request, its predicate, or its sort descriptor without first calling +deleteCacheWithName:

Typical use
===========

	Developers create an instance of NSFetchedResultsController and configure it with a fetchRequest.  It is expected that the sort descriptor used in the request groups the results into sections. This allows for section information to be pre-computed.
	After creating an instance, the performFetch: method should be called to actually perform the fetching. 
	Once configured, this class can be a helper class when implementing the following methods from the UITableViewDataSource protocol

- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section;
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView; 
- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section; 
- (NSArray *)sectionIndexTitlesForTableView:(UITableView *)tableView;   
- (NSInteger)tableView:(UITableView *)tableView sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)index; 

	The instance of NSFetchedResultsController also registers to receive change notifications on the managed object context that holds the fetched objects. Any change in the context that affects the result set or section information is properly processed. A delegate can be set on the class so that it's also notified when the result objects have changed. This would typically be used to update the display of the table view.  
	WARNING: The controller only performs change tracking if a delegate is set and responds to any of the change tracking notification methods.  See the NSFetchedResultsControllerDelegate protocol for which delegate methods are change tracking.

Handling of Invalidated Objects
===============================
	
		When a managed object context notifies the NSFetchedResultsController of individual objects being invalidated (NSInvalidatedObjectsKey), the controller treats these as deleted objects and sends the proper delegate calls.
		It's possible for all the objects in a managed object context to be invalidated simultaneously. This can happen as a result of calling -reset on NSManagedObjectContext, or if a store is removed from the the NSPersistentStoreCoordinator. When this happens, NSFetchedResultsController currently does not invalidate all objects, nor does it send individual notifications for object deletions. Instead, developers must call performFetch: again to reset the state of the controller if all the objects in a context have been invalidated. They should also reload all their data in the UITableView.
		
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSError.h>
#import <Foundation/NSIndexPath.h>
#import <CoreData/NSManagedObjectContext.h>
#import <CoreData/NSManagedObject.h>
#import <CoreData/NSFetchRequest.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NSFetchedResultsControllerDelegate;
@protocol NSFetchedResultsSectionInfo;

NS_CLASS_AVAILABLE(NA,3_0)
@interface NSFetchedResultsController : NSObject {
@private
	NSFetchRequest *_fetchRequest;
	NSManagedObjectContext *_managedObjectContext;
	NSString *_sectionNameKeyPath;
	NSString *_sectionNameKey;
	NSString *_cacheName;
	void	  *_cache;
	struct _fetchResultsControllerFlags {
	  unsigned int _sendObjectChangeNotifications:1;
	  unsigned int _sendSectionChangeNotifications:1;
	  unsigned int _sendDidChangeContentNotifications:1;
	  unsigned int _sendWillChangeContentNotifications:1;
	  unsigned int _sendSectionIndexTitleForSectionName:1;
	  unsigned int _changedResultsSinceLastSave:1;
	  unsigned int _hasMutableFetchedResults:1;
	  unsigned int _hasBatchedArrayResults:1;
	  unsigned int _hasSections:1;
	  unsigned int _usesNonpersistedProperties:1;
	  unsigned int _includesSubentities:1;
	  unsigned int _reservedFlags:21;
	} _flags;
	id _delegate;
	id _sortKeys;
	id _fetchedObjects;
	id _sections;
	id _sectionsByName;
	id _sectionIndexTitles;
	id _sectionIndexTitlesSections;
	
}

/* ========================================================*/
/* ========================= INITIALIZERS ====================*/
/* ========================================================*/

/* Initializes an instance of NSFetchedResultsController
	fetchRequest - the fetch request used to get the objects. It's expected that the sort descriptor used in the request groups the objects into sections.
	context - the context that will hold the fetched objects
	sectionNameKeyPath - keypath on resulting objects that returns the section name. This will be used to pre-compute the section information.
	cacheName - Section info is cached persistently to a private file under this name. Cached sections are checked to see if the time stamp matches the store, but not if you have illegally mutated the readonly fetch request, predicate, or sort descriptor.
*/
- (instancetype)initWithFetchRequest:(NSFetchRequest *)fetchRequest managedObjectContext: (NSManagedObjectContext *)context sectionNameKeyPath:(nullable NSString *)sectionNameKeyPath cacheName:(nullable NSString *)name;

/* Executes the fetch request on the store to get objects.
    Returns YES if successful or NO (and an error) if a problem occurred. 
    An error is returned if the fetch request specified doesn't include a sort descriptor that uses sectionNameKeyPath.
    After executing this method, the fetched objects can be accessed with the property 'fetchedObjects'
*/
- (BOOL)performFetch:(NSError **)error;

/* ========================================================*/
/* ====================== CONFIGURATION ===================*/
/* ========================================================*/

/* NSFetchRequest instance used to do the fetching. You must not change it, its predicate, or its sort descriptor after initialization without disabling caching or calling +deleteCacheWithName.  The sort descriptor used in the request groups objects into sections. 
*/
@property (nonatomic, readonly) NSFetchRequest *fetchRequest;

/* Managed Object Context used to fetch objects. The controller registers to listen to change notifications on this context and properly update its result set and section information. 
*/
@property (nonatomic, readonly) NSManagedObjectContext *managedObjectContext;

/* The keyPath on the fetched objects used to determine the section they belong to. 
*/
@property (nullable, nonatomic, readonly) NSString *sectionNameKeyPath;

/* Name of the persistent cached section information. Use nil to disable persistent caching, or +deleteCacheWithName to clear a cache.
*/
@property (nullable, nonatomic, readonly) NSString *cacheName;

/* Delegate that is notified when the result set changes.
*/
@property(nullable, nonatomic, assign) id< NSFetchedResultsControllerDelegate > delegate;

/* Deletes the cached section information with the given name.
    If name is nil, then all caches are deleted.
*/
+ (void)deleteCacheWithName:(nullable NSString *)name;

/* ========================================================*/
/* ============= ACCESSING OBJECT RESULTS =================*/
/* ========================================================*/

/* Returns the results of the fetch.
    Returns nil if the performFetch: hasn't been called.
*/
@property  (nullable, nonatomic, readonly) NSArray *fetchedObjects;

/* Returns the fetched object at a given indexPath.
*/
- (id)objectAtIndexPath:(NSIndexPath *)indexPath;

/* Returns the indexPath of a given object.
*/
-(nullable NSIndexPath *)indexPathForObject:(id)object;

/* ========================================================*/
/* =========== CONFIGURING SECTION INFORMATION ============*/
/* ========================================================*/
/*	These are meant to be optionally overridden by developers.
*/

/* Returns the corresponding section index entry for a given section name.	
    Default implementation returns the capitalized first letter of the section name.
    Developers that need different behavior can implement the delegate method -(NSString*)controller:(NSFetchedResultsController *)controller sectionIndexTitleForSectionName
    Only needed if a section index is used.
*/
- (nullable NSString *)sectionIndexTitleForSectionName:(NSString *)sectionName;

/* Returns the array of section index titles.
    It's expected that developers call this method when implementing UITableViewDataSource's
	- (NSArray *)sectionIndexTitlesForTableView:(UITableView *)tableView
	
    The default implementation returns the array created by calling sectionIndexTitleForSectionName: on all the known sections.
    Developers should override this method if they wish to return a different array for the section index.
    Only needed if a section index is used.
*/
@property (nonatomic, readonly) NSArray<NSString *> *sectionIndexTitles;

/* ========================================================*/
/* =========== QUERYING SECTION INFORMATION ===============*/
/* ========================================================*/

/* Returns an array of objects that implement the NSFetchedResultsSectionInfo protocol.
   It's expected that developers use the returned array when implementing the following methods of the UITableViewDataSource protocol

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView; 
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section;
- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section; 

*/
@property (nullable, nonatomic, readonly) NSArray<id<NSFetchedResultsSectionInfo>> *sections;

/* Returns the section number for a given section title and index in the section index.
    It's expected that developers call this method when executing UITableViewDataSource's
	- (NSInteger)tableView:(UITableView *)tableView sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)index;
*/
- (NSInteger)sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)sectionIndex;

@end

// ================== PROTOCOLS ==================

@protocol NSFetchedResultsSectionInfo

/* Name of the section
*/
@property (nonatomic, readonly) NSString *name;

/* Title of the section (used when displaying the index)
*/
@property (nullable, nonatomic, readonly) NSString *indexTitle;

/* Number of objects in section
*/
@property (nonatomic, readonly) NSUInteger numberOfObjects;

/* Returns the array of objects in the section.
*/
@property (nullable, nonatomic, readonly) NSArray *objects;

@end // NSFetchedResultsSectionInfo



@protocol NSFetchedResultsControllerDelegate <NSObject>

typedef NS_ENUM(NSUInteger, NSFetchedResultsChangeType) {
	NSFetchedResultsChangeInsert = 1,
	NSFetchedResultsChangeDelete = 2,
	NSFetchedResultsChangeMove = 3,
	NSFetchedResultsChangeUpdate = 4
} NS_ENUM_AVAILABLE(NA,  3_0);

/* Notifies the delegate that a fetched object has been changed due to an add, remove, move, or update. Enables NSFetchedResultsController change tracking.
	controller - controller instance that noticed the change on its fetched objects
	anObject - changed object
	indexPath - indexPath of changed object (nil for inserts)
	type - indicates if the change was an insert, delete, move, or update
	newIndexPath - the destination path for inserted or moved objects, nil otherwise
	
	Changes are reported with the following heuristics:

	On Adds and Removes, only the Added/Removed object is reported. It's assumed that all objects that come after the affected object are also moved, but these moves are not reported. 
	The Move object is reported when the changed attribute on the object is one of the sort descriptors used in the fetch request.  An update of the object is assumed in this case, but no separate update message is sent to the delegate.
	The Update object is reported when an object's state changes, and the changed attributes aren't part of the sort keys. 
*/
@optional
- (void)controller:(NSFetchedResultsController *)controller didChangeObject:(id)anObject atIndexPath:(nullable NSIndexPath *)indexPath forChangeType:(NSFetchedResultsChangeType)type newIndexPath:(nullable NSIndexPath *)newIndexPath;

/* Notifies the delegate of added or removed sections.  Enables NSFetchedResultsController change tracking.

	controller - controller instance that noticed the change on its sections
	sectionInfo - changed section
	index - index of changed section
	type - indicates if the change was an insert or delete

	Changes on section info are reported before changes on fetchedObjects. 
*/
@optional
- (void)controller:(NSFetchedResultsController *)controller didChangeSection:(id <NSFetchedResultsSectionInfo>)sectionInfo atIndex:(NSUInteger)sectionIndex forChangeType:(NSFetchedResultsChangeType)type;

/* Notifies the delegate that section and object changes are about to be processed and notifications will be sent.  Enables NSFetchedResultsController change tracking.
   Clients utilizing a UITableView may prepare for a batch of updates by responding to this method with -beginUpdates
*/
@optional
- (void)controllerWillChangeContent:(NSFetchedResultsController *)controller;

/* Notifies the delegate that all section and object changes have been sent. Enables NSFetchedResultsController change tracking.
   Providing an empty implementation will enable change tracking if you do not care about the individual callbacks.
*/
@optional
- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller;

/* Asks the delegate to return the corresponding section index entry for a given section name.	Does not enable NSFetchedResultsController change tracking.
    If this method isn't implemented by the delegate, the default implementation returns the capitalized first letter of the section name (seee NSFetchedResultsController sectionIndexTitleForSectionName:)
    Only needed if a section index is used.
*/
@optional
- (nullable NSString *)controller:(NSFetchedResultsController *)controller sectionIndexTitleForSectionName:(NSString *)sectionName __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@end

NS_ASSUME_NONNULL_END
