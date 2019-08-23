//
//  MPMediaPickerController.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaItemCollection.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MPMediaPickerControllerDelegate;

// MPMediaPickerController is a UIViewController for visually selecting media items.
// To display it, present it modally on an existing view controller.

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(3.0, 10.12.2, 3.0)
@interface MPMediaPickerController : UIViewController

- (instancetype)initWithMediaTypes:(MPMediaType)mediaTypes NS_DESIGNATED_INITIALIZER;
@property (nonatomic, readonly) MPMediaType mediaTypes;

@property (nonatomic, weak, nullable) id<MPMediaPickerControllerDelegate> delegate;

@property (nonatomic) BOOL allowsPickingMultipleItems; // default is NO

@property (nonatomic) BOOL showsCloudItems NS_AVAILABLE_IOS(6_0); // default is YES

@property (nonatomic) BOOL showsItemsWithProtectedAssets NS_AVAILABLE_IOS(9_2); // default is YES

@property (nonatomic, copy, nullable) NSString *prompt; // displays a prompt for the user above the navigation bar buttons

@end

__TVOS_PROHIBITED
@protocol MPMediaPickerControllerDelegate<NSObject>
@optional

// It is the delegate's responsibility to dismiss the modal view controller on the parent view controller.

- (void)mediaPicker:(MPMediaPickerController *)mediaPicker didPickMediaItems:(MPMediaItemCollection *)mediaItemCollection;
- (void)mediaPickerDidCancel:(MPMediaPickerController *)mediaPicker;

@end

NS_ASSUME_NONNULL_END
