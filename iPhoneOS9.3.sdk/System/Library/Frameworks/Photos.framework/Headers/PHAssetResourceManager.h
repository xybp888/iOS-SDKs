//
//  PHAssetResourceManager.h
//  Photos
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>


// Uniquely identify a resource data request
typedef int32_t PHAssetResourceDataRequestID NS_AVAILABLE_IOS(9_0);
static const PHAssetResourceDataRequestID PHInvalidAssetResourceDataRequestID = 0;

// Progress handler, called in an arbitrary serial queue.
typedef void (^PHAssetResourceProgressHandler)(double progress) NS_AVAILABLE_IOS(9_0);

@class PHAssetResource;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(9_0) @interface PHAssetResourceRequestOptions : NSObject <NSCopying>

@property (nonatomic, assign, getter=isNetworkAccessAllowed) BOOL networkAccessAllowed;
@property (nonatomic, copy, nullable) PHAssetResourceProgressHandler progressHandler;

@end

NS_CLASS_AVAILABLE_IOS(9_0) @interface PHAssetResourceManager : NSObject

+ (PHAssetResourceManager *)defaultManager;

// Handlers are called on an arbitrary serial queue. The lifetime of the data is not guaranteed beyond that of the handler.
- (PHAssetResourceDataRequestID)requestDataForAssetResource:(PHAssetResource *)resource
                                                    options:(nullable PHAssetResourceRequestOptions *)options
                                        dataReceivedHandler:(void (^)(NSData *data))handler
                                          completionHandler:(void(^)(NSError *__nullable error))completionHandler;

// Handlers are called on an arbitrary serial queue.
- (void)writeDataForAssetResource:(PHAssetResource *)resource
                           toFile:(NSURL *)fileURL
                          options:(nullable PHAssetResourceRequestOptions *)options
                completionHandler:(void(^)(NSError *__nullable error))completionHandler;

- (void)cancelDataRequest:(PHAssetResourceDataRequestID)requestID;

@end

NS_ASSUME_NONNULL_END