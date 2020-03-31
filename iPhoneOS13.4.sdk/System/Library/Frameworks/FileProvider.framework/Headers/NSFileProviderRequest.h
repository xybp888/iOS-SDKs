//
//  NSFileProviderRequest.h
//  FileProvider
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderManager.h>

NS_ASSUME_NONNULL_BEGIN

FILEPROVIDER_API_AVAILABILITY_V3
@interface NSFileProviderRequest : NSObject
/**
 An identifier for the application. The identifier is system-specific and may
 change between different installations of the application.
 */
@property (nonatomic, readonly, strong) NSUUID *requestingApplicationIdentifier;

@end

@interface NSFileProviderExtension (Request)
- (nullable NSFileProviderRequest *)currentRequest FILEPROVIDER_API_AVAILABILITY_V3;
@end



NS_ASSUME_NONNULL_END
