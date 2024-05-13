//
//  SKProductsRequest.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <StoreKit/SKRequest.h>

@class SKProduct, SKProductsRequest, SKProductsResponse;

NS_ASSUME_NONNULL_BEGIN

@protocol SKProductsRequestDelegate <SKRequestDelegate>

@required
// Sent immediately before -requestDidFinish:
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0));

@end


// request information about products for your application
SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0)) NS_SWIFT_NONSENDABLE @interface SKProductsRequest : SKRequest {
@private
    id _productsRequestInternal;
}

// Set of string product identifiers
- (instancetype)initWithProductIdentifiers:(NSSet<NSString *> *)productIdentifiers API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0));

@property(nonatomic, weak, nullable) id <SKProductsRequestDelegate> delegate API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0));

@end


SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0)) NS_SWIFT_SENDABLE @interface SKProductsResponse : NSObject {
@private
    id _internal;
}

// Array of SKProduct instances.
@property(nonatomic, readonly) NSArray<SKProduct *> *products API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0));

// Array of invalid product identifiers.
@property(nonatomic, readonly) NSArray<NSString *> *invalidProductIdentifiers API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0));

@end

NS_ASSUME_NONNULL_END
