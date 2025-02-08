//
//  SFErrors.h
//  SpeechRecognition
//
//  Created by Donovan Voss on 10/25/22.
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const SFSpeechErrorDomain
API_AVAILABLE(macos(14), ios(17), tvos(18));

typedef NS_ERROR_ENUM (SFSpeechErrorDomain, SFSpeechErrorCode) {
    /** Error may include `NSUnderlyingErrorKey` in `userInfo`.*/
    SFSpeechErrorCodeInternalServiceError = 1,
    /** Failed to read audio file */
    SFSpeechErrorCodeAudioReadFailed = 2,

    // MARK: CustomLM data related errors
    
    /** Templates were malformed */
    SFSpeechErrorCodeUndefinedTemplateClassName = 7,
    
    /** A custom language model file was malformed */
    SFSpeechErrorCodeMalformedSupplementalModel = 8,
    
    /** Operation timed out */
    SFSpeechErrorCodeTimeout = 10,
} API_AVAILABLE(macos(14), ios(17), tvos(18));

NS_ASSUME_NONNULL_END
