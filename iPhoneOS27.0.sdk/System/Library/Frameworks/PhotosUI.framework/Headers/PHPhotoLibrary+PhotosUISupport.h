//
//  PHPhotoLibrary+PhotosUISupport.h
//  PhotosUI
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Photos/Photos.h>

#if TARGET_OS_IPHONE || TARGET_OS_MACCATALYST
@class UIWindowScene;
@class UIViewController;
#else
@class NSWindow;
#endif

NS_ASSUME_NONNULL_BEGIN

#if TARGET_OS_IPHONE || TARGET_OS_MACCATALYST

API_AVAILABLE_BEGIN(ios(14))
API_UNAVAILABLE_BEGIN(macos, tvos, watchos)

@interface PHPhotoLibrary (PhotosUISupport_LimitedLibraryPicker)

#pragma mark - Limited library picker

/**
 @abstract Prompt the user to update their limited library selection by presenting the limited library image picker when the user has opted into limited library access mode (see \c PHAuthorizationStatusLimited )
 @param controller The view controller that is used to present the limited library picker.
 @discussion Use this API when the user has enabled limited photo library access to present the limited library picker and give the user a way to update their selection. If the user has not enabled limited library access mode for this application, then this method will do nothing. This should be used when disabling the automatic limited library alert prompt (by adding \c PHPhotoLibraryPreventAutomaticLimitedAccessAlert = \c YES to the application's Info.plist).  
 
 Any changes applied to the limited library selection by the user will trigger a \c PHPhotoLibraryChangeObserver update that can be used to observe the changes to the selection.
 */
- (void)presentLimitedLibraryPickerFromViewController:(UIViewController *)controller;

/**
 @abstract Prompt the user to update their limited library selection by presenting the limited library image picker when the user has opted into limited library access mode (see \c PHAuthorizationStatusLimited )
 @param controller The view controller that is used to present the limited library picker.
 @param completionHandler The block that will be called upon the user finishing their selection. Only newly selected assets will be provided to the block.
 @discussion Use this API when the user has enabled limited photo library access to present the limited library picker and give the user a way to update their selection. If the user has not enabled limited library access mode for this application, then this method will do nothing. This should be used when disabling the automatic limited library alert prompt (by adding \c PHPhotoLibraryPreventAutomaticLimitedAccessAlert = \c YES to the application's Info.plist).
 
 In addition to being provided the new asset local identifiers in the callback any changes applied to the limited library selection by the user will trigger a \c PHPhotoLibraryChangeObserver update that can be used to observe the changes to the selection.
 */
- (void)presentLimitedLibraryPickerFromViewController:(UIViewController *)controller completionHandler:(void(^)(NSArray<NSString *>*))completionHandler API_AVAILABLE(ios(15));

@end

API_UNAVAILABLE_END // (macos, tvos, watchos)
API_AVAILABLE_END // (ios(14))

#endif // TARGET_OS_IPHONE || TARGET_OS_MACCATALYST



NS_ASSUME_NONNULL_END
