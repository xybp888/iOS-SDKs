//
//  MLModelCollectionEntry.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLModelCollectionEntry
 * Information about a model in a model collection.
 */
API_DEPRECATED("Use Background Assets or NSURLSession instead.", macos(11.0, 14.4), ios(14.0, 17.4))
API_UNAVAILABLE(tvos, watchos)
ML_EXPORT
@interface MLModelCollectionEntry : NSObject

@property (readonly, nonatomic) NSString *modelIdentifier API_DEPRECATED("Use Background Assets or NSURLSession instead.", macos(11.0, 14.4), ios(14.0, 17.4));

@property (readonly, nonatomic) NSURL *modelURL API_DEPRECATED("Use Background Assets or NSURLSession instead.", macos(11.0, 14.4), ios(14.0, 17.4));

- (BOOL)isEqualToModelCollectionEntry:(MLModelCollectionEntry *)entry API_DEPRECATED("Use Background Assets or NSURLSession instead.", macos(11.0, 14.4), ios(14.0, 17.4));

- (instancetype)init NS_UNAVAILABLE;

+ (id)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
