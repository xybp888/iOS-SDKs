//
//  PTParticipant.h
//  PushToTalk
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <PushToTalk/PTBase.h>

@class UIImage;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_SENDABLE // Immutable with no mutable subclasses

PT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos)
@interface PTParticipant : NSObject

@property (nonatomic, readonly, copy) NSString *name;
@property (nonatomic, readonly, copy, nullable) UIImage *image;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The name length must be greater than 0. 
- (instancetype)initWithName:(NSString *)name image:(UIImage *_Nullable)image NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
