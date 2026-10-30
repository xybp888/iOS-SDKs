//  
//  GCDeviceType.h
//  GameController
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  A class representing a type of spatial accessory.
 */

API_AVAILABLE(visionos(27.0)) API_UNAVAILABLE(macos, ios, tvos)

@interface GCDeviceType : NSObject <NSCopying>

/**
 *  Create a device type for an identifier.
 *
 *  This initializer returns nil if the system doesn’t know the device type for
 *  \a identifier.
 */
+ (nullable instancetype)deviceTypeWithIdentifier:(NSString *)identifier;

- (instancetype)init NS_UNAVAILABLE;

/**
 *  A localized description of the device type.
 */
@property (readonly, nullable) NSString *localizedDescription;

@end


@interface GCDeviceType (CommonTypes)

/**
 *  A device type that represents any spatial accessory.
 */
@property (readonly, class) GCDeviceType *spatialAccessoryType API_AVAILABLE(visionos(27.0)) API_UNAVAILABLE(macos, ios, tvos);

@end

NS_ASSUME_NONNULL_END
