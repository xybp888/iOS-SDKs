#if !__has_include(<AVFCore/AVCaptionGrouper.h>)
/*
	File:  AVCaptionGrouper.h
 
	Framework:  AVFoundation
 
	Copyright 2015-2023 Apple Inc. All rights reserved.
 
*/

#import <AVFoundation/AVBase.h>
#if TARGET_OS_OSX

#import <Foundation/Foundation.h>
#import <AVFoundation/AVCaption.h>
#import <AVFoundation/AVCaptionGroup.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, tvos, watchos)
@interface AVCaptionGrouper : NSObject
{
@private
	NSMutableArray<AVCaption *> *_captionCollector;
	CMTime _captionGroupStartTime;
}

- (void)addCaption:(AVCaption *)input;
- (NSArray<AVCaptionGroup *> *)flushAddedCaptionsIntoGroupsUpToTime:(CMTime)upToTime;
@end

NS_ASSUME_NONNULL_END

#endif //TARGET_OS_OSX

#else
#import <AVFCore/AVCaptionGrouper.h>
#endif
