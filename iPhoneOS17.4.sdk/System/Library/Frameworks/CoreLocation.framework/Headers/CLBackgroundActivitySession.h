//
//  CLBackgroundActivitySession.h
//  CoreLocation
//
//  Created by Siraj Abidi on 02/20/23.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

CL_EXTERN
API_AVAILABLE(ios(17.0), watchos(10.0)) API_UNAVAILABLE(macos) NS_REFINED_FOR_SWIFT
@interface CLBackgroundActivitySession : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*
*  invalidate
*
*  Discussion:
*     	Ends the session immediately. Any UI giving visual attestation
*     	to this background session will also be terminated. Once the
*     	session is invalidated it cannot become active again.
*/
- (void)invalidate API_AVAILABLE(ios(17.0), watchos(10.0)
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
, visionos(1.0)
#endif
) API_UNAVAILABLE(macos);

/* backgroundActivitySession
 *  Discussion:
 *      Starts a background activity session allowing a When-In-Use
 *      authorized app to receive location updates or monitoring events. Provides
 *      user visibility about the background activity by displaying the Blue
 *      StatusBar/Pill and allowing the navigation back to this app by tapping
 *      the displayed UI.
 *
 *      Session creation will always yield a session object but it may or may
 *      not be active based on the following circumstances:
 *
 *      - A session may only be active for an app which has effective authorization.
 *      - A session may only be active for an app which includes Location in its
 *        UIBackgroundModes.
 *      - A new session may only become active while the app is foregrounded and
 *        in direct use.
 *      - An active session may continue when the app enters the background even
 *        if the app stops running.
 *      - An active session may be resumed immediately with this method when the
 *        app is next run, even in the background.
 *      - However, such a session which is not resumed immediately on next run
 *        will end and will need to qualify to become active again if still desired.
 *
 *      When a session is active, the app remains in-use, so When-In-Use
 *      authorization will remain effective, and both Updater and Monitor
 *      APIs will be available.

 *      Note: the app is responsible for resuming an active session with this
 *      method immediately upon background launch if it wishes the session
 *      to remain active.
 *
 *      Calling invalidate on the session will terminate it and render it
 *      immediately inactive.
 */
+ (instancetype)backgroundActivitySession API_AVAILABLE(ios(17.0), watchos(10.0)
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
, visionos(1.0)
#endif
) API_UNAVAILABLE(macos);

@end
NS_ASSUME_NONNULL_END
