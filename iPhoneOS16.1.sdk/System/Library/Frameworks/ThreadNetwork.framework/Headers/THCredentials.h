//
//  THCredentials.h
//  ThreadNetwork
//
//  Copyright © 2021 Apple. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern __attribute__((visibility ("default")))

API_AVAILABLE(ios(15.0)) @interface THCredentials : NSObject<NSSecureCoding>

/*
 * @description:
 *
 * All the fields represents Credentials field.
 *
 * Note :
 * If activeOperationalDataSet is nil after retrieving the credentials,
 * use rest of the parameter to join the Thread Network
 */

/// networkName : Thread Network name
@property (nonatomic, nullable, readonly) NSString *networkName;
/// extendedPANID : Thread Network extended PAN ID
@property (nonatomic, nullable, readonly) NSData *extendedPANID;
/// extendedPANID : Active Thread Network Border Agent Identifier
@property (nonatomic, nullable, readonly) NSData *borderAgentID;
/// Active Operational Data Set in Bytes.
@property (nonatomic, nullable, readonly) NSData *activeOperationalDataSet;
/// networkKey : A 16 byte value. e.g. 7dd5b9bffe1285f27e78898658aa88f4
@property (nonatomic, nullable, readonly) NSData *networkKey;
/// PSKc : A 16 byte value. e.g. 0eec92e950c4cbc6966d32613f08efe0
@property (nonatomic, nullable, readonly) NSData *PSKC;
/// channel : Thread network channel
@property (nonatomic) uint8_t channel;
/// PANID : A 2 byte value. e.g. 308f
@property (nonatomic, nullable, readonly) NSData *panID;

/// Metadata
@property (nonatomic, nullable, readonly) NSDate *creationDate;
@property (nonatomic, nullable, readonly) NSDate *lastModificationDate;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

