//
//  ARAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

@class ARAnchor;
/**
 An anchor object that can be copied from values of an existing anchor.
 */
API_AVAILABLE(ios(12.0))
@protocol ARAnchorCopying <NSCopying>

/**
 Initializes a new anchor object copying values from an existing anchor.

 This initializer will be called any time copy is called on anchor of this class.
 This method must be implemented for any ARAnchor subclasses that adds properties.

 - Parameter anchor: The anchor from which to copy values.

 - Returns: An initialized anchor object.
*/
- (instancetype)initWithAnchor:(ARAnchor *)anchor;

@end

/**
 A real world object or location in the scene that is being tracked.
 */
API_AVAILABLE(ios(11.0))
@protocol ARTrackable <NSObject>

/**
 Tracking state of the anchor.

 The `isTracked` value is used to determine the anchor transform's validity. When the object being tracked is no longer detected in the
 camera image, its anchor will return `NO` for `isTracked`.
*/
@property (nonatomic, readonly) BOOL isTracked;

@end

/**
 Object representing a physical location and orientation in 3D space.
 */
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARAnchor : NSObject <ARAnchorCopying,
                                NSSecureCoding
                                >

/**
 Unique identifier of the anchor.
 */
@property (nonatomic, readonly) NSUUID *identifier;

/**
 An optional name used to associate with the anchor.
 */
@property (nonatomic, nullable, readonly) NSString *name API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(visionos);

/**
 Identifier of the session that owns the anchor.

 The session identifier will be assigned to anchor when added to the session.
*/
@property (nonatomic, nullable, readonly) NSUUID *sessionIdentifier API_AVAILABLE(ios(13.0));

/**
 The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 */
@property (nonatomic, readonly) simd_float4x4 transform;

/**
 Initializes a new anchor object.

 - Parameter transform: The transformation matrix that defines the anchor's rotation, translation and scale in world coordinates.

 - Returns: An initialized anchor object.
*/
- (instancetype)initWithTransform:(simd_float4x4)transform;

/**
 Initializes a new anchor object with the provided identifier and name.

 - Parameters:
   - name: A name to associate with the anchor.
   - transform: The transformation matrix that defines the anchor's rotation, translation and scale in world coordinates.

 - Returns: An initialized anchor object.
*/
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform API_AVAILABLE(ios(12.0))API_UNAVAILABLE(visionos);

/**
 Unavailable.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
