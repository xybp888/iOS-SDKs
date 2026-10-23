//
//  CPRerouteReason.h
//  CarPlayFrameworks
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

/**
 Reasons why a reroute was triggered during navigation.
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos) NS_SWIFT_SENDABLE
typedef NS_ENUM(NSInteger, CPRerouteReason)
{
    /** The reason for rerouting is unknown or not specified. */
    CPRerouteReasonUnknown = 0,
    
    /** The user missed a turn or maneuver along the planned route. */
    CPRerouteReasonMissedTurn,
    
    /** The device lost connectivity and needs to recalculate using offline data. */
    CPRerouteReasonOffline,
    
    /** An alternative route was found that may be faster or more efficient. */
    CPRerouteReasonAlternateRoute,
    
    /** An existing waypoint was modified or updated. */
    CPRerouteReasonWaypointModified,
    
    /** A reroute was required due to external circumstances, such as a road closure. */
    CPRerouteReasonMandated,
};
