//
//  AEAssessmentBinaryExecutableConfiguration.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// The configuration applied to an ``AEAssessmentBinaryExecutable`` participant.
///
/// A non-bundled executable (such as a launchd daemon) is headless, so it supports only the subset of
/// participant policies that apply to a process without UI: network access and whether the assessment
/// requires it. The UI-oriented policies of ``AEAssessmentParticipantConfiguration`` (allowed menu items,
/// graceful termination) do not apply.
///
/// - SeeAlso: ``AEAssessmentBinaryExecutable``, ``AEAssessmentParticipantConfiguration``.
API_AVAILABLE(macCatalyst(27.0), macos(27.0))
API_UNAVAILABLE(ios)
@interface AEAssessmentBinaryExecutableConfiguration : NSObject <NSCopying>

/// Whether the executable may access the network during an assessment. Defaults to `YES`.
@property (nonatomic, assign) BOOL allowsNetworkAccess API_AVAILABLE(macCatalyst(27.0), macos(27.0))
    API_UNAVAILABLE(ios);

/// Whether the assessment requires this executable. Defaults to `NO`.
@property (nonatomic, assign, getter=isRequired) BOOL required API_AVAILABLE(macCatalyst(27.0), macos(27.0))
    API_UNAVAILABLE(ios);

- (instancetype)init API_AVAILABLE(macCatalyst(27.0), macos(27.0))API_UNAVAILABLE(ios);
+ (instancetype)new API_AVAILABLE(macCatalyst(27.0), macos(27.0))API_UNAVAILABLE(ios);

@end

NS_ASSUME_NONNULL_END
