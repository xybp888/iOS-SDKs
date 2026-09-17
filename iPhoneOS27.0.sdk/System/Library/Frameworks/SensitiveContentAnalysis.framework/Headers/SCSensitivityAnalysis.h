//
//  SCSensitivityAnalysis.h
//  SensitiveContentAnalysis
//
//  Copyright (c).2024, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
  @enum         SCSensitiveContentType
  @abstract     Identifies the specific types of sensitive content that can be detected during media analysis.
  @discussion   These content types are used to categorize potentially sensitive material found in images,
                videos, or other media. Use these constants to determine what kind of sensitive content
                was detected and to implement appropriate handling or filtering logic in your application.
 
  @constant     SCSensitiveContentTypeSexuallyExplicit
                Content that contains nudity or sexually explicit material.
 
  @constant     SCSensitiveContentTypeGoreOrViolence
                Content that depicts graphic violence, gore, or disturbing imagery.
*/
typedef NSString *SCSensitiveContentType NS_TYPED_ENUM NS_SWIFT_NAME(SCSensitivityAnalysis.ContentType) API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(watchos, tvos);
extern const SCSensitiveContentType SCSensitiveContentTypeSexuallyExplicit API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(watchos, tvos);
extern const SCSensitiveContentType SCSensitiveContentTypeGoreOrViolence API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(watchos, tvos);

/// Sensitive Analysis Results object is returned after sensitivity analysis is performed on media
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.0), ios(17.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface SCSensitivityAnalysis : NSObject

/// Set to YES if analyzed media contains sensitive content
// … skipped existing API ...
@property(readonly, getter=isSensitive) BOOL sensitive;

/// Type of sensitive content the analyzed media contains
@property (nonnull, nonatomic, copy, readonly) NSSet<SCSensitiveContentType> *detectedTypes API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
