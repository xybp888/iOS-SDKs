//
//  INPerson+SiriAdditions.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INPerson.h>

#import <Intents/INSpeakable.h>

NS_ASSUME_NONNULL_BEGIN

@interface INPerson (SiriAdditions) <INSpeakable>

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *siriMatches API_AVAILABLE(ios(10.3), watchos(3.2));

@end

NS_ASSUME_NONNULL_END
