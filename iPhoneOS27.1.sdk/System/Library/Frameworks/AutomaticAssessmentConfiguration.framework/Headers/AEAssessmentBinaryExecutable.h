//
//  AEAssessmentBinaryExecutable.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// A non-bundled, non-UI executable (e.g. a launchd daemon) designated as an assessment participant
/// by its on-disk path.
///
/// Use this for a participant that has no bundle identifier and so cannot be expressed as an
/// ``AEAssessmentApplication``. It feeds only the app-launch allowlist under
/// ``AEAssessmentConfiguration/allowOnlyParticipantsToRun`` and, when its configuration permits,
/// network access; UI policies (frontmost app, window server, media, menu bar) do not apply.
///
/// Matching is by exact on-disk path. At runtime the executable must also satisfy
/// ``requiresSignatureValidation`` (and the team identifier, if set), so a swapped or re-signed
/// binary is not silently trusted. Leave ``requiresSignatureValidation`` enabled (the default)
/// unless the executable is unsigned.
///
/// - SeeAlso: ``AEAssessmentApplication`` for bundled participants.
API_AVAILABLE(macCatalyst(27.0), macos(27.0))
API_UNAVAILABLE(ios)
@interface AEAssessmentBinaryExecutable : NSObject <NSCopying>

/// On-disk path of the executable.
@property (nonatomic, copy, readonly) NSURL *binaryExecutableURL API_AVAILABLE(macCatalyst(27.0), macos(27.0))
    API_UNAVAILABLE(ios);

/// Team identifier the running executable's signature must match, or `nil` to skip the team check.
@property (nonatomic, copy, readonly, nullable) NSString *teamIdentifier API_AVAILABLE(macCatalyst(27.0), macos(27.0))
    API_UNAVAILABLE(ios);

/// Whether the running executable's code signature is validated. Defaults to `YES`.
@property (nonatomic, assign) BOOL requiresSignatureValidation API_AVAILABLE(macCatalyst(27.0), macos(27.0))
    API_UNAVAILABLE(ios);

- (instancetype)initWithBinaryExecutableURL:(NSURL *)binaryExecutableURL API_AVAILABLE(macCatalyst(27.0), macos(27.0))
                                                API_UNAVAILABLE(ios);
- (instancetype)initWithBinaryExecutableURL:(NSURL *)binaryExecutableURL
                             teamIdentifier:(nullable NSString *)teamIdentifier
    API_AVAILABLE(macCatalyst(27.0), macos(27.0))API_UNAVAILABLE(ios);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
