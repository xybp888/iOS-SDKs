// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#if TARGET_OS_OSX
#ifndef GKDialogController_h
#define GKDialogController_h

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@protocol GKViewController
@end

@interface GKDialogController : NSResponder

@property (weak, nullable) IBOutlet NSWindow *parentWindow;

- (BOOL)presentViewController:(NSViewController<GKViewController>  *)viewController;
- (IBAction)dismiss:(id)sender;

@end

@interface GKDialogController (SharedDialogController)
+ (GKDialogController *)sharedDialogController;
@end

NS_ASSUME_NONNULL_END

#endif
#endif
