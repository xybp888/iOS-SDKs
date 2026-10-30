//
//  ARParticipantAnchor.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKitCore/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 An anchor for another user in multiuser augmented reality experiences.

 When you set ``ARWorldTrackingConfiguration/isCollaborationEnabled`` to true, ARKit calls ``ARSessionDelegate/session(_:didAdd:)`` with an
 ``ARParticipantAnchor`` for every user it detects in your physical environment, providing you with their world position. Identify the participant by
 the anchor's ``ARAnchor/sessionIdentifier`` property.
*/
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARParticipantAnchor : ARAnchor

/**
 Unavailable.

 - Parameter transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;

/**
 Unavailable.

 - Parameters:
   - name: The anchor name.
   - transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
