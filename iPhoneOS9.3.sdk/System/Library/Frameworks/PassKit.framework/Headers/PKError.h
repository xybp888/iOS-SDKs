//
//  PKError.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#ifndef __PKERROR_H
#define __PKERROR_H

// Domain for NSError
extern NSString * const PKPassKitErrorDomain NS_AVAILABLE_IOS(6_0);

typedef NS_ENUM(NSInteger, PKPassKitErrorCode) {
    PKUnknownError = -1,
    PKInvalidDataError = 1,
    PKUnsupportedVersionError,
    PKInvalidSignature,
    PKNotEntitledError
} NS_ENUM_AVAILABLE_IOS(6_0);

#endif
