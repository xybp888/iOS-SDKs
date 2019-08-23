/*
	File:  AVError.h
	
	Framework:  AVKit
	
	Copyright © 2015-2016 Apple Inc. All rights reserved.
	
 */

#import <Foundation/Foundation.h>

#import <AVKit/AVKitDefines.h>

/*!
	@constant	AVKitErrorDomain
	@abstract	Domain for errors from AVKit APIs.
 */
AVKIT_EXTERN NSString * const AVKitErrorDomain NS_AVAILABLE_IOS(9_0);


/*!
	@constant	AVKitErrorUnknown
	@abstract	Unknown error.
	@constant	AVKitErrorPictureInPictureStartFailed
	@abstract	Failed to start Picture in Picture.
 */
typedef NS_ENUM(NSInteger, AVKitError) {
	AVKitErrorUnknown						= -1000,
	AVKitErrorPictureInPictureStartFailed	= -1001
} NS_ENUM_AVAILABLE_IOS(9_0);
