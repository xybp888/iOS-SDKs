//
//  INImage.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NSData;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INImage : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)imageNamed:(NSString *)name;
+ (instancetype)imageWithImageData:(NSData *)imageData;

// This method will throw NSInvalidArgumentException for invalid URLs
+ (instancetype)imageWithURL:(NSURL *)URL;

@end

NS_ASSUME_NONNULL_END
