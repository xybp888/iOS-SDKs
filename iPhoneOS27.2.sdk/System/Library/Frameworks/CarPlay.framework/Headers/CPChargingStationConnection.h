
//
//  CPChargingStationConnection.h
//  CarPlay
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CPChargingStationConnectionConnector) {
    CPChargingStationConnectionConnectorCCS1     NS_SWIFT_NAME(ccs1),
    CPChargingStationConnectionConnectorCCS2     NS_SWIFT_NAME(ccs2),
    CPChargingStationConnectionConnectorJ1772    NS_SWIFT_NAME(j1772),
    CPChargingStationConnectionConnectorCHAdeMO  NS_SWIFT_NAME(chaDeMo),
    CPChargingStationConnectionConnectorMennekes NS_SWIFT_NAME(mennekes),
    CPChargingStationConnectionConnectorGBTDC    NS_SWIFT_NAME(gbtDC),
    CPChargingStationConnectionConnectorGBTAC    NS_SWIFT_NAME(gbtAC),
    CPChargingStationConnectionConnectorNACSDC   NS_SWIFT_NAME(nacsDC),
    CPChargingStationConnectionConnectorNACSAC   NS_SWIFT_NAME(nacsAC),
} NS_SWIFT_NAME(CPChargingStationConnection.Connector);

API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPChargingStationConnection : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithConnector:(CPChargingStationConnectionConnector)connector
                          voltage:(NSMeasurement<NSUnitElectricPotentialDifference *> *)voltage
                            power:(NSMeasurement<NSUnitPower *> *)power;

@property (nonatomic, assign, readonly) CPChargingStationConnectionConnector connector;
@property (nonatomic, strong, readonly) NSMeasurement<NSUnitElectricPotentialDifference *> *voltage;
@property (nonatomic, strong, readonly) NSMeasurement<NSUnitPower *> *power;

@end

NS_ASSUME_NONNULL_END
