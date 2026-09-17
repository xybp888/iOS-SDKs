//
//  PKContentVersion.h
//  PencilKit
//
//  Copyright © 2023-2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/// A version that specifies which PencilKit features a drawing uses or requires.
API_AVAILABLE(ios(17.0), macos(14.0))
NS_SWIFT_SENDABLE
typedef NS_ENUM(NSInteger, PKContentVersion) {

    /// The version for inks introduced in iOS 14, including Pen, Pencil, and Marker.
    PKContentVersion1 NS_SWIFT_NAME(version1) = 1,

    /// The version for inks introduced in iOS 17, adding Monoline, Fountain Pen, Watercolor, and Crayon.
    PKContentVersion2 NS_SWIFT_NAME(version2),

    /// The version that includes the updated Fountain Pen ink.
    PKContentVersion3 NS_SWIFT_NAME(version3) API_AVAILABLE(ios(17.5), macos(14.5)),

    /// The version that adds the Reed Pen ink.
    PKContentVersion4 NS_SWIFT_NAME(version4) API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0)),

    /// The version that adds stroke render state support.
    PKContentVersion5 NS_SWIFT_NAME(version5) API_AVAILABLE(ios(27.0), macos(27.0), visionos(27.0)),

    /// The latest version, which includes all available PencilKit features.
    PKContentVersionLatest = 5
};
