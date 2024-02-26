//
//  MKMapItemRequest.h
//  MapKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MKMapFeatureAnnotation;
@class MKMapItem;

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MKMapItemRequest : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithMapFeatureAnnotation:(MKMapFeatureAnnotation *)mapFeatureAnnotation NS_DESIGNATED_INITIALIZER;

- (void)getMapItemWithCompletionHandler:(void (^)(MKMapItem * _Nullable mapItem, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:mapItem());
- (void)cancel;

@property (nonatomic, readonly) MKMapFeatureAnnotation *featureAnnotation;
@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;
@property (nonatomic, readonly, getter=isLoading) BOOL loading;

@end

NS_ASSUME_NONNULL_END
