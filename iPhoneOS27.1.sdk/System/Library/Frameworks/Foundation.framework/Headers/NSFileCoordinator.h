/*
    NSFileCoordinator.h
    Copyright (c) 2010-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURL.h>

@class NSArray<ObjectType>, NSError, NSMutableDictionary, NSOperationQueue, NSSet<ObjectType>;

@protocol NSFilePresenter;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Options to use when reading the contents or attributes of a file or directory.
typedef NS_OPTIONS(NSUInteger, NSFileCoordinatorReadingOptions) {

    /// Whether reading does _not_ trigger sending of -savePresentedItemChangesWithCompletionHandler: to certain NSFilePresenters in the system and waiting for those NSFilePresenters to respond. The default behavior during coordinated reading is to send -savePresentedItemChangesWithCompletionHandler: to NSFilePresenters.
    ///
    /// Specify this constant if your code does not need other objects to save changes first. If you do _not_ specify this constant, the -savePresentedItemChangesWithCompletionHandler: method of relevant file presenters is called before your code reads the item.
    NSFileCoordinatorReadingWithoutChanges = 1 << 0,

    /// Whether reading of an item that might be a symbolic link file causes the resolution of the link if it is. This affects the URL passed to the block passed to an invocation of one of the -coordinateReadingItemAtURL:... methods.
    ///
    /// Specify this constant if you want an item that might be a symbolic link to resolve to the file pointed to by that link (instead of to the link itself). When you use this option, the system provides the resolved URL to the accessor block in place of the original URL.
    ///
    /// This is not a valid option to use with -prepareForReadingItemsAtURLs:options:writingItemsAtURLs:options:error:byAccessor:.
    NSFileCoordinatorReadingResolvesSymbolicLink = 1 << 1,

    /// Whether the reading to be done will only attempt to get an item's metadata that is immediately available (name, modification date, tags, and other attributes), and not its contents.
    ///
    /// For ubiquitous items, specifying this option causes coordinated reads to be granted immediately (barring other coordinated readers or writers or file presenters on the same system preventing this) instead of waiting for any downloading of contents or additional metadata like conflicting versions or thumbnails. Attempting to read the item's contents during such a coordinated read may give unexpected results or fail.
    NSFileCoordinatorReadingImmediatelyAvailableMetadataOnly API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 1 << 2,

    /// Whether reading of an item is being done for the purpose of uploading.
    ///
    /// When using this option, NSFileCoordinator will create a temporary snapshot of the item being read and will relinquish its claim on the file once that snapshot is made to avoid blocking other coordinated writes during a potentially long upload. If the item at the URL being read is a directory (such as a document package), then the snapshot will be a new file that contains the zipped contents of that directory, and the URL passed to the accessor block will locate that file.
    ///
    /// When using this option, you may upload the document outside of the accessor block. However, you should open a file descriptor to the file or relocate the file within the accessor block before you do so, because NSFileCoordinator will unlink the file after the block returns, rendering it inaccessible via the URL.
    NSFileCoordinatorReadingForUploading API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 1 << 3,

};

/// Options to use when changing the contents or attributes of a file or directory.
///
/// You must specify only one constant at a time for a given write operation.
typedef NS_OPTIONS(NSUInteger, NSFileCoordinatorWritingOptions) {

    /* You can use only one of these writing options at a time. Using none of them indicates that the writing will simply update the item.
    */

    /// Whether the writing to be done is actually the deletion of the item.
    ///
    /// This affects how the writing waits for previously scheduled coordinated reading and writing, how the writing causes subsequently scheduled reading and writing to wait, and what NSFilePresenter messaging is done. When this constant is specified, the file coordinator calls the -accommodatePresentedItemDeletionWithCompletionHandler: or -accommodatePresentedSubitemDeletionAtURL:completionHandler: method of relevant file presenters to give them a chance to make adjustments before the item is deleted.
    ///
    /// For example, Finder uses this when it's emptying the trash to give NSFilePresenters a chance to close documents before their files disappear, or would disappear if the files weren't still open.
    NSFileCoordinatorWritingForDeleting = 1 << 0,

    /// Whether the writing to be done is actually the moving or renaming of the item.
    ///
    /// This affects how the writing waits for previously scheduled coordinated reading and writing, how the writing causes subsequently scheduled reading and writing to wait, and what NSFilePresenter messaging is done. When specified for a directory item, the file coordinator waits for already running read and write operations of the directory's contents, which were themselves initiated through a file coordinator, to finish before moving the directory. Queued, but not executing, read and write operations on the directory's contents wait until the move operation finishes.
    ///
    /// This option has no effect when what's being moved is a plain file so you can use it in code that moves file system items without checking whether the items are files or directories. Any such check would invite a race condition anyway.
    NSFileCoordinatorWritingForMoving = 1 << 1,

    /// Whether coordinated writing triggers sending of -savePresentedItemChangesWithCompletionHandler: to certain NSFilePresenters in the system and waiting for those NSFilePresenters to respond.
    ///
    /// When this constant is specified, the file coordinator calls the -savePresentedItemChangesWithCompletionHandler: method of relevant file presenters to give them a chance to save their changes before your code makes its changes.
    NSFileCoordinatorWritingForMerging = 1 << 2,

    /// Whether the writing to be done is actually the replacement of the item with a different item.
    ///
    /// It causes the same behavior as NSFileCoordinatorWritingForDeleting except that when the item being written to is renamed or moved while the writer is being made to wait the item is considered to have been a different item, so the writer is not passed an updated URL to reflect the renaming or moving. Use this when the moving or creation of an item will replace any item that gets in its way. To avoid a race condition use it regardless of whether there is actually an item in the way before the writing begins. Don't use this when simply updating the contents of a file, even if the way you do that is writing the contents to another file and renaming it into place. This is not a valid option to use with -prepareForReadingItemsAtURLs:options:writingItemsAtURLs:options:error:byAccessor:.
    ///
    /// For example, NSDocument uses this for NSSaveAsOperation and NSSaveToOperation to announce that it is possibly overwriting an item with a brand new file or file package. This gives any NSFilePresenter of the overwritten item, including perhaps a different instance of NSDocument, perhaps in the same application, a chance to close itself before the item is overwritten.
    ///
    /// For another example, the most accurate and safe way to coordinate a move is to invoke -coordinateWritingItemAtURL:options:writingItemAtURL:options:error:byAccessor: using the NSFileCoordinatorWritingForMoving option with the source URL and NSFileCoordinatorWritingForReplacing with the destination URL.
    NSFileCoordinatorWritingForReplacing = 1 << 3,

    /// Whether the writing to be done will change the item's metadata only and not its contents.
    ///
    /// If the item being written to is ubiquitous, then changes to the item's contents during this coordinated write may not be preserved or fail. When using this option, changing metadata that is related to the item's contents is not supported for ubiquitous items and such changes may not be preserved. For example, changing the value of NSURLTagNamesKey is supported, but changing the value of NSURLContentModificationDateKey is not.
    NSFileCoordinatorWritingContentIndependentMetadataOnly API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 1 << 4

};

/// The details of a coordinated-read or coordinated-write operation.
///
/// Use this class when performing asynchronous operations with a file coordinator using the coordinator's ``NSFileCoordinator/coordinate(with:queue:byAccessor:)`` method.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface NSFileAccessIntent : NSObject
/// Returns a file access intent object for reading the given URL with the provided options.
///
/// When calling a file coordinator's ``NSFileCoordinator/coordinate(with:queue:byAccessor:)`` method, you pass an array of file access intent objects. Each intent object represents a specific read or write operation on a single document or directory. Use this method to create an intent object suitable for reading.
///
/// - Parameters:
///   - url: The URL of the document you intend to read from.
///   - options: The coordinated reading options. For a list of valid values, see ``NSFileCoordinator/ReadingOptions`` in the ``NSFileCoordinator``.
/// - Returns: A newly instantiated and configured file access intent object.
+ (instancetype)readingIntentWithURL:(NSURL *)url options:(NSFileCoordinatorReadingOptions)options;
/// Returns a file access intent object for writing to the given URL with the provided options.
///
/// When calling a file coordinator's ``NSFileCoordinator/coordinate(with:queue:byAccessor:)`` method, you pass an array of file access intent objects. Each intent object represents a specific read or write operation on a single document or directory. Use this method to create an intent object suitable for writing.
///
/// - Parameters:
///   - url: The URL of the document you intend to write to.
///   - options: The coordinated writing options. For a list of valid values, see ``NSFileCoordinator/WritingOptions`` in the ``NSFileCoordinator``.
/// - Returns: A newly instantiated and configured file access intent object.
+ (instancetype)writingIntentWithURL:(NSURL *)url options:(NSFileCoordinatorWritingOptions)options;
/// The URL of the item. Use this URL within the accessor block. This property may change from its original value in response to actions from other writers.
@property (readonly, copy) NSURL *URL;
@end


/// An object that coordinates the reading and writing of files and directories among file presenters.
///
/// The ``NSFileCoordinator`` class coordinates the reading and writing of files and directories among multiple processes and objects in the same process. You use instances of this class as is to read from, write to, modify the attributes of, change the location of, or delete a file or directory, but before your code to perform those actions executes, the file coordinator lets registered file presenter objects perform any tasks that they might require to ensure their own integrity. For example, if you want to change the location of a file, other objects interested in that file need to know where you intend to move it so that they can update their references.
///
/// Objects that adopt the ``NSFilePresenter`` protocol must register themselves with the ``NSFileCoordinator`` class to be notified of any pending changes. They do this by calling the ``addFilePresenter(_:)`` class method. A file presenter must balance calls to ``addFilePresenter(_:)`` with a call to ``removeFilePresenter(_:)`` before being released, even in a garbage-collected application. The file presenter class maintains a list of active file presenter objects in the current application and uses that list, plus the file coordinator classes in other processes, to deliver notifications to all of the objects interested in a particular item.
///
/// Instances of ``NSFileCoordinator`` are meant to be used on a per-file-operation basis, where a file operation is something like opening and reading the contents of a file or moving a batch of files and directories to a new location. There is no benefit to keeping a file coordinator object past the length of the planned operation. In fact, because file coordinators retain file presenter objects, keeping one around could prevent the file presenter objects from being released in a timely manner.
///
/// For information about implementing a file presenter object to receive file-related notifications, see ``NSFilePresenter``.
///
/// ### File Presenters and iOS
///
/// If your app or extension enters the background with an active file presenter, it may be terminated by the system in order to prevent deadlock on that file. To prevent this situation, call ``removeFilePresenter(_:)`` to remove the file presenter in the <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/applicationdidenterbackground(_:)> method or in response to a <doc://com.apple.documentation/documentation/uikit/uiapplication/didenterbackgroundnotification> notification. Call ``addFilePresenter(_:)`` to add the file presenter again in the <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/applicationwillenterforeground(_:)> method or in response to a <doc://com.apple.documentation/documentation/uikit/uiapplication/willenterforegroundnotification> notification.
///
/// > Note:
/// > The <doc://com.apple.documentation/documentation/uikit/uidocument> class automatically removes itself when your app goes to the background. It automatically adds itself again when your app returns to the foreground.
///
/// ### File Coordinators and iOS
///
/// A coordinated read or write will automatically begin a background task when granted, similar to one created with the <doc://com.apple.documentation/documentation/uikit/uiapplication/beginbackgroundtask(expirationhandler:)> method. This helps ensure that your app or extension has sufficient time to finish the read or write operation if it's suspended, without creating a deadlock on access to that file by other processes. If a process is suspended while waiting for a coordinated read or write to be granted, the request is canceled, and an `NSError` object with the code ``NSUserCancelledError-var`` is produced. If the background task expires, the process is terminated.
///
/// > Note:
/// > The <doc://com.apple.documentation/documentation/uikit/uidocument> class automatically requests additional background time and safely performs coordinated reads and writes when loading and saving the document.
///
/// ### Threading Considerations
///
/// Each file coordinator object you create should be used on a single thread only. If you need to coordinate file operations across multiple objects in different threads, each object should create its own file coordinator.
API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0))
@interface NSFileCoordinator : NSObject {
    @private
    id _accessArbiter;
    id _fileReactor;
    id _purposeID;
    NSURL *_recentFilePresenterURL;
    id _accessClaimIDOrIDs;
    NSMutableDictionary *_movedItems;
    BOOL _isCancelled;
}

#pragma mark *** File Presenters ***

/// Registers the specified file presenter object so that it can receive notifications.
///
/// This method registers the file presenter object process wide. Thus, any file coordinator objects you create later automatically know about the file presenter object and know to message it when its file or directory is affected.
///
/// Be sure to balance calls to this method with a corresponding call to +removeFilePresenter: before the file presenter is deallocated, even in a garbage-collected application.
///
/// If you call this method while coordinated file operations are already under way in another process, your file presenter may not receive notifications for that operation. To prevent missing such notifications, create a file coordinator, call its -coordinateReadingItemAtURL:options:error:byAccessor: method, and register your file presenter object there. If you are going to read a file and then create a file presenter for that file, both actions should occur in the same coordinated read block. Synchronizing on the presented file or directory guarantees that when your block executes, all other objects have completed any tasks and you have sole access to the item.
+ (void)addFilePresenter:(id<NSFilePresenter>)filePresenter;

/// Unregisters the specified file presenter object.
///
/// Call this method to unregister file presenters before those objects are deallocated.
+ (void)removeFilePresenter:(id<NSFilePresenter>)filePresenter;

/// Returns an array containing the process's currently registered file presenter objects.
@property (class, readonly, copy) NSArray<id<NSFilePresenter>> *filePresenters;

/// Initializes and returns a file coordinator object using the specified file presenter.
///
/// Specifying a file presenter at initialization time is strongly recommended if the file presenter is initiating the file operation. Otherwise, the file presenter itself would receive notifications when it made changes to the file and would have to compensate for that fact. Receiving such notifications could also deadlock if the file presenter's code and its notifications run on the same thread. There is one exception: Messages about versions of the presented item being added, removed, or resolved during coordinated writing are sent to every relevant file presenter.
///
/// NSFileCoordinator is meant to be instantiated on a per-file-operation basis, where a file operation is something like the opening or saving of a document, or the copying or moving of a batch of folders and files. There is no benefit to keeping an instance of it alive in your application for much more time than it takes to actually perform the file operation. Doing so can be harmful, or at least wasteful of memory, because NSFileCoordinators may retain NSFilePresenters.
///
/// Aside from disabling most self-initiated NSFilePresenter notifications, associating an NSFileCoordinator with an NSFilePresenter accomplishes the following:
/// - Prevents deadlocks that could occur when the file presenter performs a coordinated write operation in response to a -savePresentedItemChangesWithCompletionHandler: message. This is done by giving this coordinated write priority over the coordinated read that initiated the -savePresentedItemChangesWithCompletionHandler: message.
/// - Prevents race conditions that could occur when the file presenter is sent a -presentedItemDidMoveToURL: message and at the same time the file presenter enqueues an operation using the old URL on a different queue. For this to be effective, the coordinator must be initialized on the same operation queue that the file presenter uses to receive its messages.
/// - Allows the file coordination mechanism to gracefully handle file presenters that initially contain nil in the presentedItemURL property, but that can later contain a non-nil value after creating the item using a coordinated write operation.
- (instancetype)initWithFilePresenter:(nullable id<NSFilePresenter>)filePresenterOrNil NS_DESIGNATED_INITIALIZER;

#pragma mark *** Purpose Identifier ***

/// A string that uniquely identifies the file access that was performed by this file coordinator.
///
/// Every NSFileCoordinator has a unique purpose identifier that is created during initialization. Coordinated reads and writes performed by NSFileCoordinators with the same purpose identifier never block each other, even if they exist in different processes. If you are coordinating file access on behalf of a file presenter, use -initWithFilePresenter: and do not attempt to set a custom purpose identifier. Every file coordinator instance initialized with the same file presenter has the same purpose identifier.
///
/// You may need to set a custom purpose identifier for the following reasons:
/// - Your application has a File Provider extension. Any file coordination done on behalf of the File Provider needs to be done using the File Provider's purpose identifier.
/// - You have two separate subsystems that need to work together to perform a single high-level operation, and both subsystems perform their own coordinated reads or writes. Using the same purpose identifier in both subsystems prevents possible deadlocks between the two subsystems.
///
/// When creating custom purpose identifiers, you can use a reverse DNS style string, such as "com.mycompany.myapplication.mypurpose", or a UUID string. Nil and zero-length strings are not allowed.
///
/// Purpose identifiers can be set only once. If you attempt to set the purpose identifier of an NSFileCoordinator that you initialized with -initWithFilePresenter: or that you already assigned a purpose identifier, an exception will be thrown.
@property (copy) NSString *purposeIdentifier API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

#pragma mark *** Asynchronous File Coordination ***

/* You can consider "item" in method names and comments in this header file to be an abbreviation of "fileOrDirectory." As always, a directory might actually be a file package.

 The term "reader" refers to an invocation of -coordinateAccessWithIntents:queue:byAccessor: with at least one NSFileAccessIntent created with +readingIntentWithURL:options: or an invocation of one of the synchronous methods mentioning "reading". Similarly, the term "writer" refers to an invocation of -coordinateAccessWithIntents:queue:byAccessor: with at least one NSFileAccessIntent created with +writingIntentWithURL:optiosn: or an invocation of one of the synchronous methods metioning "writing".
 
 A coordinated reader of a directory that is not a file package does not wait for coordinated writers of contained items, or cause such writers to wait. With one exception, a coordinated writer of a directory that is not a file package does not wait for coordinated readers and writers of contained items, or cause such readers and writers to wait. The exception is when you use NSFileCoordinatorWritingForDeleting, NSFileCoordinatorWritingForMoving, or NSFileCoordinatorWritingForReplacing. They make your coordinated writer wait for previously scheduled coordinated readers and writers of contained items, and causes subsequently scheduled coordinated readers and writers of contained items to wait.
 
 In addition to waiting for other readers or writers, coordinated reads and writes also wait for messages to be sent to NSFilePresenters registered for relevant URLs, and for their responses to those messages. The specific message sent are as follows:
 
 Coordinated reading of an item triggers the sending of messages to other NSFilePresenters that implement the corresponding optional methods, even those in other processes:
 - -relinquishPresentedItemToReader: is sent to NSFilePresenters of the item and, if the item is in a file package, NSFilePresenters of the file package. If there are nested file packages then the message is sent to NSFilePresenters of all of them.
 - If NSFileCoordinatorReadingWithoutChanges is not used then -savePresentedItemChangesWithCompletionHandler: is also sent to the same NSFilePresenters.
  
 Coordinated writing of an item triggers the sending of messages to NSFilePresenters that implement the corresponding optional methods, even those in other processes, except the one specified when -initWithFilePresenter: was invoked:
 - -relinquishPresentedItemToWriter: is sent to NSFilePresenters of the item and, if the item is in a file package, NSFilePresenters of the file package. If there are nested file packages then the message is sent to NSFilePresenters of all of them.
 - If NSFileCoordinatorWritingForDeleting, NSFileCoordinatorWritingForMoving, or NSFileCoordinatorWritingForReplacing is used and the item is a directory then -relinquishPresentedItemToWriter: is also sent to NSFilePresenters of each item contained by it.
 - If NSFileCoordinatorWritingForDeleting or NSFileCoordinatorWritingForReplacing is used then -accommodatePresentedItemDeletionWithCompletionHandler: is sent to NSFilePresenters of the item and, if the item is a directory, NSFilePresenters of each item contained by it. -accommodatePresentedSubitemDeletionAtURL:completionHandler: is sent to NSFilePresenters of each file package that contains the item.
 - When NSFileCoordinatorWritingForReplacing is used the the definition of "the item" depends on what happened while waiting for other writers. See the description of it above.
 - If NSFileCoordinatorWritingForMerging is used then -savePresentedItemChangesWithCompletionHandler: is sent to NSFilePresenters of the item and, if the item is in a file package, NSFilePresenters of the file package. If there are nested file packages then the message is sent to NSFilePresenters of all of them.
  
 For both coordinated reading and writing, if there are multiple NSFilePresenters involved then the order in which they are messaged is undefined. If an NSFilePresenter signals failure then waiting will fail and *outError will be set to an NSError describing the failure.
 
 None of those rules apply to coordinated readers and writers that are using the exact same instance of NSFileCoordinator or different instances instantiated with the same NSFilePresenter.
*/

/// Performs a number of coordinated-read or -write operations asynchronously.
///
/// This method lets you asynchronously perform coordinated read or writes. You can specify any combination of individual read or write operations. The file coordinator waits asynchronously to get access to the files and then invokes the accessor block on the specified queue.
///
/// If an error occurs while waiting for access, an error message is passed to the block. You must check the block's error parameter before accessing any of the files. If the error parameter is set to nil, you can freely perform the read and write operations described by your intents. Otherwise, you may not access the files.
///
/// Additionally, always use the URL property on the NSFileAccessIntent objects when accessing the files inside the accessor block. The system updates this property to account for any changes to the underlying files. Your file coordinator has access to the files only until the accessor block returns. Do not dispatch tasks that continue to access these files onto other threads or queues.
///
/// In general a coordinated reader waits for a coordinated writer of the same item, and a coordinated writer waits for coordinated readers and other coordinated writers of the same item. Coordinated readers do not wait for each other. Coordinated reading or writing of items in a file package is treated as coordinated reading or writing of the file package as a whole. Coordinated reads and writes from the same file coordinator instance never block each other. However, if you make multiple, concurrent calls to this method, you risk deadlocking with another process that is similarly making multiple concurrent calls. Wherever possible, invoke this method once with multiple file access intent objects.
- (void)coordinateAccessWithIntents:(NSArray<NSFileAccessIntent *> *)intents queue:(NSOperationQueue *)queue byAccessor:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))accessor API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

#pragma mark *** Synchronous File Coordination ***

/// Initiates a read operation on a single file or directory using the specified options.
///
/// This method executes synchronously, blocking the current thread until the reader block finishes executing. Before executing that block, the file coordinator waits until other relevant file presenter objects finish in-progress actions.
///
/// When invoking these methods, declare a __block variable before the accessor block and initialize it to a value that signals failure, and then inside the accessor block set it to a value that indicates success. If the coordinated operation fails, then the accessor block never runs and the NSError out parameter contains a reference that describes the error.
///
/// This method calls the -relinquishPresentedItemToReader: method of any relevant file presenters. Depending on the options you specify, other methods of the file presenters may also be called. All of the called methods must return successfully before the file coordinator executes your block. If multiple file presenters are operating on the item, the order in which those presenters are notified is undefined.
///
/// If the device has not yet downloaded the file at the given URL, this method blocks (potentially for a long time) while the file is downloaded.
- (void)coordinateReadingItemAtURL:(NSURL *)url options:(NSFileCoordinatorReadingOptions)options error:(NSError **)outError byAccessor:(void (NS_NOESCAPE ^)(NSURL *newURL))reader;

/// Initiates a write operation on a single file or directory using the specified options.
///
/// This method executes synchronously, blocking the current thread until the writer block finishes executing. Before executing the block, the file coordinator waits until other relevant file presenter objects finish in-progress actions.
///
/// When invoking this method, declare a __block variable before the accessor block and initialize it to a value that signals failure, and then inside the accessor block set it to a value that indicates success. If the coordinated operation fails, then the accessor block never runs and the NSError out parameter contains a reference that describes the error.
///
/// This method calls the -relinquishPresentedItemToWriter: method of any relevant file presenters. Depending on the options you specify, other methods of the file presenters may also be called. All of the called methods must return successfully before the file coordinator executes your block.
///
/// With one exception, do not nest calls to file coordinator methods inside the block you pass to this method. You may call -coordinateReadingItemAtURL:options:error:byAccessor: to read the file if you discover through modification-date checking that the contents of the file have changed. However, if you call this method from inside your block, the file coordinator object throws an exception.
- (void)coordinateWritingItemAtURL:(NSURL *)url options:(NSFileCoordinatorWritingOptions)options error:(NSError **)outError byAccessor:(void (NS_NOESCAPE ^)(NSURL *newURL))writer;

/// Initiates a read operation that contains a follow-up write operation.
///
/// You use this method to perform a read operation that might also contain a write operation that needs to be coordinated. This method executes synchronously, blocking the current thread until the readerWriter block finishes executing. When performing the write operation, you may call -coordinateWritingItemAtURL:options:error:byAccessor: from your readerWriter block. This method does the canonical lock ordering that is required to prevent a potential deadlock of the file operations.
///
/// When invoking this method, declare a __block variable before the accessor block and initialize it to a value that signals failure, and then inside the accessor block set it to a value that indicates success. If the coordinated operation fails, then the accessor block never runs and the NSError out parameter contains a reference that describes the error.
///
/// This method makes the same calls to file presenters, and has the same general wait behavior, as the -coordinateReadingItemAtURL:options:error:byAccessor: and -coordinateWritingItemAtURL:options:error:byAccessor: methods.
- (void)coordinateReadingItemAtURL:(NSURL *)readingURL options:(NSFileCoordinatorReadingOptions)readingOptions writingItemAtURL:(NSURL *)writingURL options:(NSFileCoordinatorWritingOptions)writingOptions error:(NSError **)outError byAccessor:(void (NS_NOESCAPE ^)(NSURL *newReadingURL, NSURL *newWritingURL))readerWriter;

/// Initiates a write operation that involves a secondary write operation.
///
/// You use this method to perform two write operations without the risk of those operations creating a deadlock. This method executes synchronously, blocking the current thread until the writer block finishes executing. You may call -coordinateWritingItemAtURL:options:error:byAccessor: from your writer block. This method does the canonical lock ordering that is required to prevent a potential deadlock of the file operations.
///
/// When invoking this method, declare a __block variable before the accessor block and initialize it to a value that signals failure, and then inside the accessor block set it to a value that indicates success. If the coordinated operation fails, then the accessor block never runs and the NSError out parameter contains a reference that describes the error.
///
/// This method makes the same calls to file presenters, and has the same general wait behavior, as the -coordinateWritingItemAtURL:options:error:byAccessor: method.
- (void)coordinateWritingItemAtURL:(NSURL *)url1 options:(NSFileCoordinatorWritingOptions)options1 writingItemAtURL:(NSURL *)url2 options:(NSFileCoordinatorWritingOptions)options2 error:(NSError **)outError byAccessor:(void (NS_NOESCAPE ^)(NSURL *newURL1, NSURL *newURL2))writer;

#pragma mark *** Batched File Coordination ***

/// Prepare to read or write from multiple files in a single batch operation.
///
/// Use this method to prepare the file coordinator for multiple read and write operations. Because file coordination requires interprocess communication, it is much more efficient to batch changes to large numbers of files and directories than to change each item individually. The file coordinator uses the values in the readingURLs and writingURLs parameters, together with reading and writing options, to prepare any relevant file presenters for the upcoming operations.
///
/// This method executes synchronously, blocking the current thread until the batchAccessor block finishes executing. The batchAccessor block you provide does not have exclusive access to the given items when it is invoked. Instead, you must call coordinated read and write methods for each individual item from inside the batchAccessor block. You must then call the completion handler after all the coordinated reads and writes have completed. You can call the completion handler from any thread.
///
/// Don't simply pass this method all the URLs that are passed into the nested coordinate methods. Instead pass only the top-level files and directories involved in the operation. This method triggers messages to the file presenters of those items and to the file presenters of any items contained by those items.
///
/// In most cases, passing the same reading and writing options to both this method and the contained coordination operations is redundant.
- (void)prepareForReadingItemsAtURLs:(NSArray<NSURL *> *)readingURLs options:(NSFileCoordinatorReadingOptions)readingOptions writingItemsAtURLs:(NSArray<NSURL *> *)writingURLs options:(NSFileCoordinatorWritingOptions)writingOptions error:(NSError **)outError byAccessor:(void (NS_NOESCAPE NS_SWIFT_NONSENDABLE ^)(void (NS_SWIFT_SENDABLE ^completionHandler)(void)))batchAccessor;

#pragma mark *** Renaming and Moving Notification ***

/// Announces that your app is moving a file to a new URL.
///
/// This method is intended for apps that adopt App Sandbox. Some apps need to rename files while saving them. For example, when a user adds an attachment to a rich text document, TextEdit changes the document's filename extension from .rtf to .rtfd. In such a case, in a sandboxed app, you must call this method to declare your intent to rename a file without user approval.
///
/// After the renaming process succeeds, call -itemAtURL:didMoveToURL: with the same arguments to provide your app with continued access to the file under its new name, while also giving up access to any file that appears with the old name.
///
/// If your macOS app is not sandboxed, this method serves no purpose. This method is nonfunctional in iOS.
- (void)itemAtURL:(NSURL *)oldURL willMoveToURL:(NSURL *)newURL API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// Notifies relevant file presenters that the location of a file or directory changed.
///
/// If you move or rename a file or directory as part of a write operation, call this method to notify relevant file presenters that the change occurred. This method calls -presentedItemDidMoveToURL: for any of the item's file presenters. If the item is a directory, this method calls -presentedItemDidMoveToURL: on the file presenters for the item's contents. Finally, it calls -presentedSubitemAtURL:didMoveToURL: on the file presenter of any directory containing the item.
///
/// You must call this method from a coordinated write block. Calling this method with the same URL in the oldURL and newURL parameters is harmless. This call must balance a call to -itemAtURL:willMoveToURL:.
- (void)itemAtURL:(NSURL *)oldURL didMoveToURL:(NSURL *)newURL;

#pragma mark *** Ubiquity Attribute Change Notification ***

/// Tells observing file providers that the item's ubiquity attributes have changed.
///
/// This triggers the -presentedItemDidChangeUbiquityAttributes: method on any file presenters that are observing the item, even if they are running in different processes. See NSFilePresenter's observedPresentedItemUbiquityAttributes property for an explanation of valid attributes.
- (void)itemAtURL:(NSURL *)url didChangeUbiquityAttributes:(NSSet <NSURLResourceKey> *)attributes API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

#pragma mark *** Cancellation ***

/// Cancels any active file coordination calls.
///
/// Use this method to cancel any active calls to coordinate the reading or writing of a file. If the block passed to the file coordination call has not yet been executed — perhaps because the file coordinator is still waiting for a response from other file presenters — the file coordinator method stops waiting for a response, does not execute its block, and returns an error object with the error code NSUserCancelledError. However, if the block is already being executed, the file coordinator method does not return until the block finishes executing.
///
/// You can call this method from any thread of your application and it returns immediately without waiting for the file coordinator object to respond. Thus, when this method returns, you cannot assume that the read or write operation occurred or did not occur. If you want to know whether the operation actually occurred, you must track it yourself by setting a flag when the block starts executing or by using some other means.
- (void)cancel;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
