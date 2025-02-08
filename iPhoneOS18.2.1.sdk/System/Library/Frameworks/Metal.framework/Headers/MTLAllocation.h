//
//  MTLAllocation.h
//  Metal
//
//  Copyright (c) 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>


API_AVAILABLE(macos(15.0), ios(18.0))
@protocol MTLAllocation <NSObject>
@property (readonly) NSUInteger allocatedSize API_AVAILABLE(macos(15.0), ios(18.0));
@end

