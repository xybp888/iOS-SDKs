//
//  INIntentHandlerProviding.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INIntent;

NS_ASSUME_NONNULL_BEGIN

@protocol INIntentHandlerProviding <NSObject>

// Override this function to provide classes other than the extension's principal class to handle a given intent
- (nullable id)handlerForIntent:(INIntent *)intent;

@end

NS_ASSUME_NONNULL_END
