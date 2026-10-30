//
//  NSPredicateValidating.h
//  Foundation
//
//  Copyright (c) 2026, Apple Inc.
//  All rights reserved.
//

#import <Foundation/NSComparisonPredicate.h>
#import <Foundation/NSError.h>
#import <Foundation/NSExpression.h>
#import <Foundation/NSPredicate.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(26.4), ios(26.4), watchos(26.4), tvos(26.4))
@protocol NSPredicateValidating <NSObject>

@optional
- (BOOL)visitPredicate:(NSPredicate *)predicate
                 error:(NSError **)error;
- (BOOL)visitExpression:(NSExpression *)expression
                  error:(NSError **)error;
- (BOOL)visitOperatorType:(NSPredicateOperatorType)operatorType
                    error:(NSError **)error;
- (BOOL)visitExpressionKeyPath:(NSExpression *)expression
                         scope:(NSString * _Nullable)scope
                           key:(NSString * _Nullable)key
                         error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
