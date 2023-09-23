//
//  SFTranscriptionResultAttributeOptions_Private.h
//  Speech
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_SWIFT_SENDABLE
typedef NS_OPTIONS(NSUInteger, _SFTranscriptionResultAttributeOptions) {
    _SFTranscriptionResultAttributeOptionsConfidence = 1UL << 0,
    _SFTranscriptionResultAttributeOptionsCmTime = 1UL << 1,
} API_AVAILABLE(macos(14), ios(17));
