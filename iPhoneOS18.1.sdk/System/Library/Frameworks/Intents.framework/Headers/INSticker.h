//
//  INSticker.h
//  Intents
//
//  Copyright (c) 2016-2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INStickerType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(18.0), macos(15.0), watchos(11.0))
API_UNAVAILABLE(tvos)
@interface INSticker : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithType:(INStickerType)type
                       emoji:(nullable NSString *)emoji NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INStickerType type;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *emoji;

@end

NS_ASSUME_NONNULL_END
