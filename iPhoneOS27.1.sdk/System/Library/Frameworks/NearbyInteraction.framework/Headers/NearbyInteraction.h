//
//  NearbyInteraction.h
//  NearbyInteraction
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#if __has_include(<AppleFeatures/AppleFeatures.h>)
#import <AppleFeatures/AppleFeatures.h>
#endif

#import <NearbyInteraction/NIError.h>

#import <NearbyInteraction/NIAlgorithmConvergenceStatusReason.h>
#if APPLE_FEATURE_NIBODY
#import <NearbyInteraction/NIBody.h>
#endif // APPLE_FEATURE_NIBODY
#import <NearbyInteraction/NIConfiguration.h>
#import <NearbyInteraction/NIDeviceCapability.h>
#import <NearbyInteraction/NINearbyObject.h>
#import <NearbyInteraction/NISession.h>
#import <NearbyInteraction/NIDLTDOAMeasurement.h>
#import <NearbyInteraction/NIExport.h>
