//
//  ILCallCommunication.h
//  IdentityLookup
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <IdentityLookup/ILCommunication.h>

NS_ASSUME_NONNULL_BEGIN

IL_EXTERN API_AVAILABLE(ios(12.0))
@interface ILCallCommunication : ILCommunication

- (BOOL)isEqualToCallCommunication:(ILCallCommunication *)communication NS_SWIFT_UNAVAILABLE("Use == operator instead");;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
