//
//  INUIHostedViewControlling.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INInteraction;

typedef NS_ENUM(NSUInteger, INUIHostedViewContext) {
    INUIHostedViewContextSiriSnippet,
    INUIHostedViewContextMapsCard,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

@protocol INUIHostedViewControlling <NSObject>

/*!
 @abstract Perform configuration of UI based on the provided INInteraction object.
 @discussion When configuration is complete for the given interaction, the hosted view controller should call the completion block with its view's desired size. This size will be constrained between hostedViewMinimumAllowedSize and hostedViewMaximumAllowedSize of the extension context.
 
 @param  interaction The input interaction
 @param  context The hosting context for this interaction. The hosted view will be displayed alongside this context -- for instance, a Siri result snippet, or a place card within Maps.
 @param  completion The response handling block takes one parameter corresponding the optional desiredSize property of the INUIHostedViewControlling protocol
 
 @see  INInteraction
 */
- (void)configureWithInteraction:(INInteraction *)interaction context:(INUIHostedViewContext)context completion:(void (^)(CGSize desiredSize))completion;

@end

@interface NSExtensionContext (INUIHostedViewControlling)

@property (nonatomic, assign, readonly) CGSize hostedViewMinimumAllowedSize API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);
@property (nonatomic, assign, readonly) CGSize hostedViewMaximumAllowedSize API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

@end
