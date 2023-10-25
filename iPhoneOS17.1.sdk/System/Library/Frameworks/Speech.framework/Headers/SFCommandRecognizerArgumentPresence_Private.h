//
//  SFCommandRecognizerArgumentPresence_Private.h
//  Speech
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <stdint.h>

NS_SWIFT_SENDABLE
typedef NS_ENUM(int8_t, _SFCommandRecognizerArgumentPresence) {
    _SFCommandRecognizerArgumentPresencePresentAndDelimited = 0,
    _SFCommandRecognizerArgumentPresencePresentMaybeIncomplete = 1,
    _SFCommandRecognizerArgumentPresenceMissingMaybeExpected = 2,
    _SFCommandRecognizerArgumentPresenceMissing = 3,
    
    // TODO: Remove once Core Speech no longer uses these symbols. rdar://110343916
    SFCommandRecognizerArgumentPresencePresentAndDelimited = 0,
    SFCommandRecognizerArgumentPresencePresentMaybeIncomplete = 1,
    SFCommandRecognizerArgumentPresenceMissingMaybeExpected = 2,
    SFCommandRecognizerArgumentPresenceMissing = 3,
} API_AVAILABLE(macos(14), ios(17));
