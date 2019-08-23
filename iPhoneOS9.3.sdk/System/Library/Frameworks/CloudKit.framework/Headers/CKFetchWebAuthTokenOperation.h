//
//  CKFetchWebAuthTokenOperation.h
//  CloudKit
//
//  Copyright © 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_11, 9_2)
@interface CKFetchWebAuthTokenOperation : CKDatabaseOperation

/* This operation will fetch a web auth token given an API token obtained
 * from the CloudKit Dashboard for your container
 */
- (instancetype)initWithAPIToken:(NSString *)APIToken NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSString *APIToken;

@property (nonatomic, copy, nullable) void (^fetchWebAuthTokenCompletionBlock)(NSString *webAuthToken, NSError *operationError);

@end
NS_ASSUME_NONNULL_END