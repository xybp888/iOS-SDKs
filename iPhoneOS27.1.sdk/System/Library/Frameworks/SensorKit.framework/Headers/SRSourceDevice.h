//
//  SRSourceDevice.h
//  SensorKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos)
@interface SRSourceDevice : NSObject <NSSecureCoding, NSCopying>

/*!
 * @property localIdentifier
 *
 * @brief A unique identifier for the data source. This property is available to clients for
 *        a local identifier. The local identifier distinguishes different peripheral
 *        sources used by a common device.
 */
@property (nonatomic, readonly, copy) NSString *localIdentifier;

/*!
 * @property manufacturer
 *
 * @brief A nil value means a manufacter was not provided.
 */
@property (nonatomic, readonly, copy, nullable) NSString *manufacturer;

/*!
 * @property model
 *
 * @brief Model of the source. A nil value means a model name was not provided.
 */
@property (nonatomic, readonly, copy, nullable) NSString *model;

/*!
 * @property hardwareVersion
 *
 * @brief Hardware version of the source. A nil value means a hardware version was not provided.
 */
@property (nonatomic, readonly, copy, nullable) NSString *hardwareVersion;

/*!
 * @property firmwareVersion
 *
 * @brief Firmware version of the source. A nil value means a firmware version was not provided.
 */
@property (nonatomic, readonly, copy, nullable) NSString *firmwareVersion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
