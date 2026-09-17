#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>
#import <SharedWithYouCore/SWCollaborationMetadata.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWCollaborationMetadata (NSItemProvider) <NSItemProviderReading, NSItemProviderWriting>

@end

NS_ASSUME_NONNULL_END

SW_EXTERN NSString * const SWCollaborationMetadataTypeIdentifier API_AVAILABLE(ios(16.0), macos(13.0));

/*!
    @abstract Type identifier for copy representation that signals the system to use the app's local document version.

    @discussion Register this as the first open-in-place type identifier on an NSItemProvider when you want
                the system to load the document's file URL directly from your app rather than from the file provider.
                This ensures that users share the most current version of their document, including any unsynced
                local edits.

                When this type identifier is registered first, also register a "public.file-url" representation
                that provides the local file URL.

    @code
    NSItemProvider *provider = [[NSItemProvider alloc] init];
    NSURL *localDocumentURL = [self currentDocumentFileURL]; // Obtain from your document management code

    // Step 1: Register SWCopyRepresentationTypeIdentifier as an open-in-place file
    [provider registerFileRepresentationForTypeIdentifier:SWCopyRepresentationTypeIdentifier
                                              fileOptions:NSItemProviderFileOptionOpenInPlace
                                               visibility:NSItemProviderRepresentationVisibilityAll
                                              loadHandler:^NSProgress * _Nullable(void (^completionHandler)(NSURL * _Nullable, BOOL, NSError * _Nullable)) {
        completionHandler(localDocumentURL, YES, nil);
        return nil;
    }];

    // Step 2: Register the public.file-url representation
    [provider registerObject:localDocumentURL
                  visibility:NSItemProviderRepresentationVisibilityAll];
    @endcode

    @note In a UIDocument subclass, use self.fileURL. In an NSDocument subclass, use self.fileURL.
          For custom document handling, use whatever property or method provides access to the current file location.
 */
SW_EXTERN NSString * const SWCopyRepresentationTypeIdentifier API_AVAILABLE(ios(27.0), macos(27.0));

#endif // !TARGET_OS_TV
