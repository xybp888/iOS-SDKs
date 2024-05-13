//
//  MLModelAsset.h
//  CoreML
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

ML_EXPORT
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0))
@interface MLModelAsset : NSObject

/*!
 * Construct an optimized model asset from the contents of specification data.
 *
 * @param specificationData Contents of .mlmodel as a data blob.
 * @param error When the model asset creation fails error is populated with the reason for failure.
 *
 */
+ (nullable instancetype)modelAssetWithSpecificationData:(NSData *)specificationData
                                                   error:(NSError * _Nullable __autoreleasing *)error API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(init(specification:));

// cannot construct MLModelAsset without model specification data.
- (instancetype)init NS_UNAVAILABLE;

// cannot construct MLModelAsset without model specification data.
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
