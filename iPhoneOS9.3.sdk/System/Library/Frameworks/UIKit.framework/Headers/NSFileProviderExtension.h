//
//  NSFileProviderExtension.h
//  UIKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED @interface NSFileProviderExtension : NSObject
// You don't want to override these

// metadata contains NSURLNameKey, NSURLFileSizeKey, NSURLIsPackageKey
+ (BOOL)writePlaceholderAtURL:(NSURL *)placeholderURL withMetadata:(NSDictionary *)metadata error:(NSError **)error;
+ (NSURL *)placeholderURLForURL:(NSURL *)url;

// An identifier unique to this provider.
// When modifying the files stored in the directory returned by documentStorageURL, you should pass this identifier
// to your file coordinator's setPurposeIdentifier: method.
// By default, this returns the bundle identifier of the application containing your extension. You need to make sure to use the same identifier in your containing app.
- (NSString *)providerIdentifier;

// The root URL for provided documents. This URL must be writable from your app extension, and must only be used for the extension's files or their placeholders.
- (NSURL *)documentStorageURL;

// You may want to override these.

// Should return the URL corresponding to a specific identifier. Fail if it's not a subpath of documentStorageURL.
// This is a static mapping; each identifier must always return a path corresponding to the same file.
// By default, this returns the path relative to the path returned by documentStorageURL.
- (nullable NSURL *)URLForItemWithPersistentIdentifier:(NSString *)identifier;
- (nullable NSString *)persistentIdentifierForItemAtURL:(NSURL *)url;

// These need to be overridden. None of them should call super.

// Should call + writePlaceholderAtURL: with the placeholder URL, then call the completion handler with that URL.
- (void)providePlaceholderAtURL:(NSURL *)url completionHandler:(void (^)(NSError * __nullable error))completionHandler;

// Should ensure that the actual file is in the position returned by URLForItemWithIdentifier:, then call the completion handler
- (void)startProvidingItemAtURL:(NSURL *)url completionHandler:(void (^)(NSError * __nullable error))completionHandler;

// Called at some point after the file has changed; the provider may then trigger an upload
- (void)itemChangedAtURL:(NSURL *)url;

// Called after the last claim to the file has been released. At this point, it is safe for the file provider to remove the content file.
// Care should be taken that the corresponding placeholder file stays behind after the content file has been deleted.
- (void)stopProvidingItemAtURL:(NSURL *)url;
@end

NS_ASSUME_NONNULL_END
