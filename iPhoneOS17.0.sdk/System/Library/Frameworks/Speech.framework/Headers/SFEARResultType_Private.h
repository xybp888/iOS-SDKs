//
//  SFEARResultType_Private.h
//  Speech
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_SWIFT_SENDABLE
typedef NS_ENUM(NSUInteger, _SFEARResultType) {
    /// An EAR partial (or preliminary) result, without alternatives or confidences.
    _SFEARResultTypePartial = 0,

    /// A result candidate for an incomplete utterance.
    _SFEARResultTypeCandidate = 1,

    /// The final (generally non-volatile) result for a span of audio or utterance, but not the final (terminal) result of the recognition. Accompanied by a change to the transcriber's volatile range. (The EAR package's `isFinal` flag is false.)
    _SFEARResultTypeFinal = 2,

    /// The final, non-volatile and terminal, result for the recognition. Accompanied by a change to the transcriber's volatile range. (The EAR package's `isFinal` flag is true.)
    _SFEARResultTypeFinalAndTerminal = 3,
    
    /// An otherwise-empty result indicating that recognition has paused.
    _SFEARResultTypePauseConfirmation = 4

} API_AVAILABLE(macos(14), ios(17));
