//
//  INUIHostedViewSiriProviding.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

@protocol INUIHostedViewSiriProviding <NSObject>

@optional

@property (nonatomic, assign, readonly) BOOL displaysMap;
@property (nonatomic, assign, readonly) BOOL displaysMessage;
@property (nonatomic, assign, readonly) BOOL displaysPaymentTransaction;

@end
