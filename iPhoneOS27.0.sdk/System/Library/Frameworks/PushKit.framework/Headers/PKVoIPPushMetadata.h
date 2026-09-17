//
//  PKVoIPPushMetadata.h
//  PushKit
//
//  Created by Kevin Ferrell on 12/8/25.
//  Copyright © 2025 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/// An object that contains metadata about a received PushKit VoIP notification.
///
/// ### Metadata
///
/// - ``PushKit/PKVoIPPushMetadata/mustReport``
///
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(26.4), macCatalyst(26.4), ios(26.4), watchos(26.4))
@interface PKVoIPPushMetadata : NSObject

/// A boolean indicating whether a VoIP app must report a call or live conversation in response to receiving this VoIP notification.
@property (readonly) BOOL mustReport;

@end

NS_ASSUME_NONNULL_END
