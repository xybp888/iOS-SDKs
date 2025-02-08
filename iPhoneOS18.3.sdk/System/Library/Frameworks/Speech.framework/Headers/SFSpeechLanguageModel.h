//
//  SFSpeechLanguageModel.h
//  Speech
//
//  Created by Ethan Peters on 8/1/22.
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(17), macos(14), tvos(18))
NS_SWIFT_SENDABLE
NS_SWIFT_NAME(SFSpeechLanguageModel.Configuration)
@interface SFSpeechLanguageModelConfiguration : NSObject <NSCopying>

@property (nonatomic, readonly, copy) NSURL *languageModel;
@property (nonatomic, readonly, nullable, copy) NSURL *vocabulary;

- (instancetype)initWithLanguageModel:(NSURL *)languageModel;
- (instancetype)initWithLanguageModel:(NSURL *)languageModel vocabulary:(NSURL * __nullable)vocabulary;

@end

API_AVAILABLE(ios(17), macos(14), tvos(18))
@interface SFSpeechLanguageModel : NSObject
  
+ (void)prepareCustomLanguageModelForUrl:(NSURL *)asset clientIdentifier:(NSString *)clientIdentifier configuration:(SFSpeechLanguageModelConfiguration *)configuration completion:(void(^)(NSError * __nullable error))completion;

+ (void)prepareCustomLanguageModelForUrl:(NSURL *)asset clientIdentifier:(NSString *)clientIdentifier configuration:(SFSpeechLanguageModelConfiguration *)configuration ignoresCache:(BOOL)ignoresCache completion:(void(^)(NSError * __nullable error))completion;

@end

NS_ASSUME_NONNULL_END
