//
//  SFTranscriptionOptions_Private.h
//  Speech
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_SWIFT_SENDABLE
typedef NS_OPTIONS(NSUInteger, _SFTranscriptionOptions) {
    _SFTranscriptionOptionsNormalizedTranscription = 1UL << 0,
    _SFTranscriptionOptionsContextualizedTranscription = 1UL << 1,
    _SFTranscriptionOptionsPunctuation = 1UL << 2,
    _SFTranscriptionOptionsEmoji = 1UL << 3,
    _SFTranscriptionOptionsEtiquetteReplacements = 1UL << 4,
} API_AVAILABLE(macos(14), ios(17));
