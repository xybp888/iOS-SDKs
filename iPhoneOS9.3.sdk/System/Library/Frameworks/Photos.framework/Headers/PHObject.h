//
//  PHObject.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PHPhotoLibrary;


NS_CLASS_AVAILABLE_IOS(8_0) @interface PHObject : NSObject <NSCopying>

// Returns an identifier which persistently identifies the object on a given device
@property (nonatomic, copy, readonly) NSString *localIdentifier;

@end

// PHObjectPlaceholder represents a model object future , vended by change requests when creating a model object.  PHObjectPlaceholder is a read-only object and may be used as a proxy for the real object that will be created both inside and outside of the change block.  Will compare isEqual: to the fetched model object after the change block is performed.
NS_CLASS_AVAILABLE_IOS(8_0) @interface PHObjectPlaceholder : PHObject
@end

NS_ASSUME_NONNULL_END