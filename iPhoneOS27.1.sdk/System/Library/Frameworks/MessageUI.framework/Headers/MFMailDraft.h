//
//  MFMailDraft.h
//  MessageUI
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MFMailDraft: NSObject

@property (nonatomic, nullable, readonly) NSString *from;
@property (nonatomic, nonnull, readonly) NSString *subject;
@property (nonatomic, nonnull, readonly) NSAttributedString *body;
@property (nonatomic, nonnull, readonly) NSArray<NSString *> *to;
@property (nonatomic, nonnull, readonly) NSArray<NSString *> *cc;

- (instancetype)initWithSubject:(NSString *)subject body:(NSAttributedString *)body from:(NSString *)from to:(NSArray<NSString *> *)to cc:(NSArray<NSString *> *)cc;

@end

NS_ASSUME_NONNULL_END
