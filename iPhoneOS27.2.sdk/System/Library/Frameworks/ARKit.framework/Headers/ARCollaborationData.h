#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARCollaborationData.h>)
//
//  ARCollaborationData.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARSession.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Options that help you choose the appropriate network protocol or settings for a given data instance.

 When you send an `ARCollaborationData` instance over the network by using a protocol that allows you to specify varying reliability, this
 enumeration lists the priority options that hint at which reliability setting to use for a given collaboration data instance. Depending on its
 priority, you may also choose to send a given collaboration data instance using different protocols.
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARCollaborationDataPriority) {
    /**
     A priority that indicates that collaboration depends on this data.

     ARKit sets the data priority to critical when the data is important for establishing or continuing a collaborative session. For best results,
     use network transmission mechanisms that ensure delivery, such as MCSessionSendDataModeReliable.
     */
    ARCollaborationDataPriorityCritical,

    /**
     A priority that indicates that collaboration can continue without this data.

     ARKit sets the data priority to optional when the data is time-sensitive but not important to collaborative session quality. Timely
     synchronization of this data between participants produces a smoother shared session, but the session can continue if the data is not received.
     For best results, use network transmission mechanisms that prioritize speed over delivery guarantees, such as MCSessionSendDataModeUnreliable.
     */
    ARCollaborationDataPriorityOptional,
} NS_SWIFT_NAME(ARCollaborationData.Priority);

/**
 An object that holds information that a user has collected about the physical environment.

 To create a multiuser AR experience, you enable collaboration on a world tracking session. ARKit regularly outputs `ARCollaborationData`
 that users share with each other, which enables everyone to view the same virtual content from their own perspective. This data needs to be
 sent to each participant in the collaborative session. For more information, see
 <doc://com.apple.documentation/documentation/arkit/arworldtrackingconfiguration/iscollaborationenabled>.
*/
API_AVAILABLE(ios(13.0))
NS_SWIFT_NAME(ARSession.CollaborationData)
NS_SWIFT_SENDABLE
@interface ARCollaborationData : NSObject <NSSecureCoding>

/**
 A property that gives you a hint about how to send a given data instance over the network.

 If you have reliability options in the network protocol you choose to transport `ARCollaborationData` among peers, the priority property gives
 you a hint about which reliability option to choose for a given collaboration data instance. For example, if you use MultipeerConnectivity to
 send collaboration data over the network, choose <doc://com.apple.documentation/documentation/multipeerconnectivity/mcsessionsenddatamode/reliable>
 when calling <doc://com.apple.documentation/documentation/multipeerconnectivity/mcsession/send(_:topeers:with:)> after ARKit gives you a
 collaboration data instance with priority ARCollaborationDataPriorityCritical.
*/
@property (nonatomic, readonly) ARCollaborationDataPriority priority;

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
#else
#import <ARKitCore/ARCollaborationData.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARCollaborationData.h>)