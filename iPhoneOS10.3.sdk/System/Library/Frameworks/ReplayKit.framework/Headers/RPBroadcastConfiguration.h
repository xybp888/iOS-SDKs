//
//  RPBroadcastConfiguration.h
//  ReplayKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_CLASS_AVAILABLE_IOS(10_0)

NS_ASSUME_NONNULL_BEGIN
@interface RPBroadcastConfiguration : NSObject <NSCoding, NSSecureCoding>

/* @abstract Specify the duration of a movie clip before it is delivered to the movie clip handler extension. Default is 5 seconds. */
@property (nonatomic, assign) NSTimeInterval clipDuration;

/* @abstract Override the video compression properties used to encode movie clips. See AVVideoCompressionPropertiesKey in <AVFoundation/AVVideoSettings.h> for available properties. */
@property (nonatomic, strong, nullable) NSDictionary <NSString *, NSObject <NSCoding, NSSecureCoding> *> *videoCompressionProperties;

@end
NS_ASSUME_NONNULL_END
