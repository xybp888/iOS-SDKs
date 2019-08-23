//
//  CXError.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN NSString *const CXErrorDomain API_AVAILABLE(ios(10.0));
CX_EXTERN NSString *const CXErrorDomainIncomingCall API_AVAILABLE(ios(10.0));
CX_EXTERN NSString *const CXErrorDomainRequestTransaction API_AVAILABLE(ios(10.0));
CX_EXTERN NSString *const CXErrorDomainCallDirectoryManager API_AVAILABLE(ios(10.0));

typedef NS_ENUM(NSInteger, CXErrorCode) {
    CXErrorCodeUnknownError = 0,
} API_AVAILABLE(ios(10.0));

typedef NS_ENUM(NSInteger, CXErrorCodeIncomingCallError) {
    CXErrorCodeIncomingCallErrorUnknown = 0,
    CXErrorCodeIncomingCallErrorUnentitled = 1,
    CXErrorCodeIncomingCallErrorCallUUIDAlreadyExists = 2,
    CXErrorCodeIncomingCallErrorFilteredByDoNotDisturb = 3,
    CXErrorCodeIncomingCallErrorFilteredByBlockList = 4,
} API_AVAILABLE(ios(10.0));

typedef NS_ENUM(NSInteger, CXErrorCodeRequestTransactionError) {
    CXErrorCodeRequestTransactionErrorUnknown = 0,
    CXErrorCodeRequestTransactionErrorUnentitled = 1,
    CXErrorCodeRequestTransactionErrorUnknownCallProvider = 2,
    CXErrorCodeRequestTransactionErrorEmptyTransaction = 3,
    CXErrorCodeRequestTransactionErrorUnknownCallUUID = 4,
    CXErrorCodeRequestTransactionErrorCallUUIDAlreadyExists = 5,
    CXErrorCodeRequestTransactionErrorInvalidAction = 6,
    CXErrorCodeRequestTransactionErrorMaximumCallGroupsReached = 7,
} API_AVAILABLE(ios(10.0));

typedef NS_ENUM(NSInteger, CXErrorCodeCallDirectoryManagerError) {
    CXErrorCodeCallDirectoryManagerErrorUnknown = 0,
    CXErrorCodeCallDirectoryManagerErrorNoExtensionFound = 1,
    CXErrorCodeCallDirectoryManagerErrorLoadingInterrupted = 2,
    CXErrorCodeCallDirectoryManagerErrorEntriesOutOfOrder = 3,
    CXErrorCodeCallDirectoryManagerErrorDuplicateEntries = 4,
    CXErrorCodeCallDirectoryManagerErrorMaximumEntriesExceeded = 5,
    CXErrorCodeCallDirectoryManagerErrorExtensionDisabled = 6,
    CXErrorCodeCallDirectoryManagerErrorCurrentlyLoading = 7,
} API_AVAILABLE(ios(10.0));

NS_ASSUME_NONNULL_END
