/*
    NSFilePresenter.h
    Copyright (c) 2010-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURL.h>

@class NSError, NSFileVersion, NSOperationQueue, NSSet<ObjectType>;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The interface a file coordinator uses to inform an object presenting a file about changes to that file made elsewhere in the system.
///
/// Objects that allow the user to view or edit the content of files or directories should adopt the ``NSFilePresenter`` protocol. You use file presenters in conjunction with an ``NSFileCoordinator`` object to coordinate access to a file or directory among the objects of your application and between your application and other processes. When changes to an item occur, the system notifies objects that adopt this protocol and gives them a chance to respond appropriately.
///
/// Use the methods of this protocol to respond to actions about to be taken on the presented file or directory. When another object or process uses a file coordinator to begin reading or writing a file or directory, the file coordinator notifies all presented objects interested in the item first. It notifies the presenter objects by invoking one of the methods defined by this protocol on that object. The actual invocation of that method occurs on the operation queue in the ``presentedItemOperationQueue`` property. Your file presenter must provide this queue. If your queue supports the concurrent execution of operations, the methods of your presenter object must be thread-safe and able to run in multiple queues simultaneously.
///
/// You can use file presenters to coordinate access to a file or directory among your application's objects. If another process uses a file coordinator for the same file or directory, your presenter objects are similarly notified whenever the other process makes its changes. Your presenter objects are not notified about changes made directly using low-level read and write calls to the file. Only changes that go through a file coordinator result in notifications.
///
/// For information about how to use file presenters with a file coordinator object, see ``NSFileCoordinator``.
///
/// ### File Presenters and iOS
///
/// If your app enters the background with an active file presenter, any other processes that perform a coordinated read or write on the presented file can deadlock. To prevent this situation, call the coordinator's ``NSFileCoordinator/removeFilePresenter(_:)`` type method to remove the file presenter in the <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/applicationdidenterbackground(_:)> method or in response to a <doc://com.apple.documentation/documentation/uikit/uiapplication/didenterbackgroundnotification> notification. Call ``NSFileCoordinator/addFilePresenter(_:)`` to add the file presenter again in the <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/applicationwillenterforeground(_:)> method or in response to a <doc://com.apple.documentation/documentation/uikit/uiapplication/willenterforegroundnotification> notification.
///
/// > Note:
/// > The <doc://com.apple.documentation/documentation/uikit/uidocument> class automatically removes itself when your app goes to the background. It automatically adds itself again when your app returns to the foreground.
@protocol NSFilePresenter<NSObject>

@required

/// The URL of the presented file or directory.
///
/// File presenters must implement this property and use it to return the file or directory of interest. If this object presents a group of related files that all reside in the same directory, specify the URL of the directory instead of creating separate presenter objects for each file.
///
/// The URL associated with your item may be requested by objects not associated with your presenter. Therefore, your implementation of the accessor method for this property must be thread safe and capable of running in multiple dispatch or operation queues simultaneously.
///
/// A nil value is valid and means that the presented item does not exist yet. An NSFilePresenter with a nil presentedItemURL will be asked for its presentedItemURL again when coordinated file access on behalf of that NSFilePresenter completes, in case the presented item was just created.
@property (nullable, readonly, copy) NSURL *presentedItemURL;

/// The operation queue in which to execute presenter-related messages.
///
/// As other objects and processes interact with the presented item, the system queues relevant messages for this presenter object on the operation queue in this property. Requests for an object's presented URL are not processed on this queue.
///
/// Implementations of this method must be prepared to be invoked by Cocoa in any queue, at any time, including from within invocations of NSFileCoordinator methods. A nil value is not valid.
@property (readonly, retain) NSOperationQueue *presentedItemOperationQueue;

@optional

/// The URL of the primary presented item for a secondary item.
///
/// This property supports App Sandbox on OS X. Some applications, given a user-selected file, require access to additional files or directories with related names. The system will grant access to an appropriate secondary item after an NSFilePresenter is registered for it. Each NSFilePresenter of a secondary item must return an NSURL to the primary item, for which it already has access, on request.
@property (nullable, readonly, copy) NSURL *primaryPresentedItemURL API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, watchos, tvos);

/// Notifies your object that another object or process wants to read the presented file or directory.
///
/// You use this method to provide an appropriate response when another object wants to read from your presented URL. For example, when this method is called, you might temporarily stop making changes to the file or directory. After taking any appropriate steps, you must execute the block in the reader parameter to let the waiting object know that it may now proceed with its task. If you want to be notified when the reader has completed its task, pass your own block to the reader and use that block to reacquire the file or URL for your own uses.
///
/// If you implement this method, you must execute the block in the reader parameter as part of your implementation. The system waits for you to execute that block before allowing the reader to operate on the file. Therefore, failure to execute the block could stall threads in your application or other processes. Depending on the reader's options, this message may be followed up with other messages like -savePresentedItemChangesWithCompletionHandler:.
- (void)relinquishPresentedItemToReader:(void (NS_SWIFT_SENDABLE ^)(void (NS_SWIFT_SENDABLE ^ _Nullable reacquirer)(void)))reader;

/// Notifies your object that another object or process wants to write to the presented file or directory.
///
/// You use this method to provide an appropriate response when another object wants to write to your presented URL. Implementations of this method must always invoke the passed-in writer block because other parts of the system will wait until it is invoked or until the user loses patience and cancels the waiting.
///
/// If you implement this method, you must execute the block in the writer parameter as part of your implementation. The system waits for you to execute that block before allowing the writer to operate on the file. Depending on the writer's options, this message may be followed up with other messages like -accommodatePresentedItemDeletionWithCompletionHandler: or -savePresentedItemChangesWithCompletionHandler:.
- (void)relinquishPresentedItemToWriter:(void (NS_SWIFT_SENDABLE ^)(void (NS_SWIFT_SENDABLE ^ _Nullable reacquirer)(void)))writer;

/// Given that something in the system is waiting to read from the presented file or directory, do whatever it takes to ensure that the contents of the presented file or directory is completely up to date, and then invoke the completion handler.
///
/// If successful pass nil to the completion handler, or if not successful pass an NSError that encapsulates the reason why saving failed. Implementations of this method must always invoke the completion handler because other parts of the system will wait until it is invoked or the user loses patience and cancels the waiting.
- (void)savePresentedItemChangesWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable errorOrNil))completionHandler;

/// Tells your object that its presented item is about to be deleted.
///
/// A file coordinator calls this method when your object's presented item is about to be deleted. You can use this method to perform any actions that are needed to prepare for the deletion. For example, document objects typically use this method to close the document.
///
/// If you implement this method, you must execute the block in the completionHandler parameter at the end of your implementation. The system waits for you to execute that block before allowing the other object to delete the file or directory. Therefore, failure to execute the block could stall threads in your application or other processes.
- (void)accommodatePresentedItemDeletionWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable errorOrNil))completionHandler;

/// Given that something in the system is waiting to evict the presented file or directory, do whatever it takes to ensure that the eviction will succeed and that the receiver's application will behave properly when the eviction has happened, and then invoke the completion handler. This must include calling +[NSFileCoordinator removeFilePresenter:]. You may instead prevent eviction by passing the completion handler a meaningful error.
///
/// If this method is not implemented, eviction will fail.
- (void)accommodatePresentedItemEvictionWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable errorOrNil))completionHandler API_AVAILABLE(macos(14.4), ios(17.4)) API_UNAVAILABLE(watchos, tvos);

/// Be notified that the file or directory has been moved or renamed, or a directory containing it has been moved or renamed.
///
/// A typical implementation of this method will cause subsequent invocations of -presentedItemURL to return the new URL. The new URL may have a different file name extension than the current value of the presentedItemURL property.
///
/// Not all programs use file coordination. Your NSFilePresenter may be sent this message without being sent -relinquishPresentedItemToWriter: first. Make your application do the best it can in that case.
- (void)presentedItemDidMoveToURL:(NSURL *)newURL;

#pragma mark *** Files and File Packages ***

/// Tells your object that the presented item's contents or attributes changed.
///
/// You can use this method to update your internal data structures to reflect the changes to the presented item. This method reports both changes to the file's contents and changes to the attributes of the item.
///
/// Because this method notifies you of both attribute and content changes, you might want to check the modification date before needlessly rereading the contents of a file. To do that, you must store the date when your object last made changes to the file and compare that date with the item's current modification date. Use a file coordinator to ensure exclusive access to the file when reading the current modification date.
///
/// Not all programs use file coordination. Your NSFilePresenter may be sent this message without being sent -relinquishPresentedItemToWriter: first.
- (void)presentedItemDidChange;

/// Be notified that the presented file or file package's ubiquity attributes have changed.
///
/// The possible attributes that can appear in the given set include only those specified by the receiver's value for observedPresentedItemUbiquityAttributes, or those in the default set if that property is not implemented. Note that changes to these attributes do not normally align with -presentedItemDidChange notifications.
- (void)presentedItemDidChangeUbiquityAttributes:(NSSet<NSURLResourceKey> *)attributes API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/// The set of ubiquity attributes which the receiver wishes to be notified about when they change for presentedItemURL.
///
/// Valid attributes include only NSURLIsUbiquitousItemKey and any other attributes whose names start with "NSURLUbiquitousItem" or "NSURLUbiquitousSharedItem". The default set, in case this property is not implemented, includes all such attributes.
///
/// This property will normally be checked only at the time +[NSFileCoordinator addFilePresenter:] is called. However, if presentedItemURL is nil at that time, it will instead be checked only at the end of a coordinated write where presentedItemURL became non-nil.
@property (readonly, strong) NSSet<NSURLResourceKey> *observedPresentedItemUbiquityAttributes API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/// Be notified that something in the system has added a version of the file or file package.
- (void)presentedItemDidGainVersion:(NSFileVersion *)version;

/// Be notified that something in the system has removed a version of the file or file package.
- (void)presentedItemDidLoseVersion:(NSFileVersion *)version;

/// Be notified that something in the system has resolved a version conflict for the file or file package.
- (void)presentedItemDidResolveConflictVersion:(NSFileVersion *)version;

#pragma mark *** Directories ***

/* These methods are sent by the file coordination machinery only when the presented item is a directory. "Contained by the directory" in these comments means contained by the directory, a directory contained by the directory, and so on.
 
 Not all programs use file coordination. Your NSFileProvider may be sent these messages without being sent -relinquishPresentedItemToWriter: first. Make your application do the best it can in that case.
*/

/// Given that something in the system is waiting to delete a file or directory contained by the presented directory, do whatever it takes to ensure that the deleting will succeed and that the receiver's application will behave properly when the deleting has happened, and then invoke the completion handler.
///
/// Implementations of this method must always invoke the completion handler because other parts of the system will wait until it is invoked or until the user loses patience and cancels the waiting.
- (void)accommodatePresentedSubitemDeletionAtURL:(NSURL *)url completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable errorOrNil))completionHandler;

/// Be notified that a file or directory contained by the presented directory has been added.
///
/// If this method is not implemented but -presentedItemDidChange is, and the directory is actually a file package, then the file coordination machinery will invoke -presentedItemDidChange instead.
- (void)presentedSubitemDidAppearAtURL:(NSURL *)url;

/// Be notified that a file or directory contained by the presented directory has been moved or renamed.
///
/// If this method is not implemented but -presentedItemDidChange is, and the directory is actually a file package, then the file coordination machinery will invoke -presentedItemDidChange instead.
- (void)presentedSubitemAtURL:(NSURL *)oldURL didMoveToURL:(NSURL *)newURL;

/// Be notified that the contents or attributes of a file or directory contained by the presented directory have been written to.
///
/// If this method is not implemented but -presentedItemDidChange is, and the directory is actually a file package, then the file coordination machinery will invoke -presentedItemDidChange instead.
- (void)presentedSubitemDidChangeAtURL:(NSURL *)url;

/// Be notified that something in the system has added a version of a file or directory contained by the presented directory.
- (void)presentedSubitemAtURL:(NSURL *)url didGainVersion:(NSFileVersion *)version;

/// Be notified that something in the system has removed a version of a file or directory contained by the presented directory.
- (void)presentedSubitemAtURL:(NSURL *)url didLoseVersion:(NSFileVersion *)version;

/// Be notified that something in the system has resolved a version conflict for a file or directory contained by the presented directory.
- (void)presentedSubitemAtURL:(NSURL *)url didResolveConflictVersion:(NSFileVersion *)version;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
