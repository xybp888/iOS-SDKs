//
//  CXCallDirectoryExtensionContext.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>
#import <CallKit/CXCallDirectory.h>

NS_ASSUME_NONNULL_BEGIN

@class CXCallDirectoryExtensionContext;

@protocol CXCallDirectoryExtensionContextDelegate <NSObject>

- (void)requestFailedForExtensionContext:(CXCallDirectoryExtensionContext *)extensionContext withError:(NSError *)error;

@end

CX_CLASS_AVAILABLE(ios(10.0))
@interface CXCallDirectoryExtensionContext : NSExtensionContext

@property (nonatomic, weak, nullable) id<CXCallDirectoryExtensionContextDelegate> delegate;

- (void)addBlockingEntryWithNextSequentialPhoneNumber:(CXCallDirectoryPhoneNumber)phoneNumber;

- (void)addIdentificationEntryWithNextSequentialPhoneNumber:(CXCallDirectoryPhoneNumber)phoneNumber label:(NSString *)label;

- (void)completeRequestWithCompletionHandler:(nullable void (^)(BOOL expired))completion;

// Use -completeRequestWithCompletionHandler: instead
- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void (^__nullable)(BOOL expired))completionHandler NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
