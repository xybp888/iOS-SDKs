//
//  PTChannelDescriptor.h
//  PushToTalk
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PushToTalk/PTBase.h>

@class UIImage;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_SENDABLE // Immutable with no mutable subclasses

PT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos)
@interface PTChannelDescriptor : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithName:(NSString *)name image:(UIImage *_Nullable)image NS_DESIGNATED_INITIALIZER;

/// The channel's "group name" shown in system user interface. (This is shown while nobody else is speaking.)
@property (nonatomic, copy, readonly) NSString *name;

/// The channel's "group photo" presented in the system user interface. This image is shown while nobody else is speaking.
@property (nonatomic, copy, readonly, nullable) UIImage *image;

@end

NS_ASSUME_NONNULL_END

