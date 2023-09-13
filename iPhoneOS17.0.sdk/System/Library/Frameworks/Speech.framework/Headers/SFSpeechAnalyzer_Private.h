//
//  SFSpeechAnalyzer_Private.h
//  Speech
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>
#import <Speech/SFCommandRecognizerArgumentPresence_Private.h>
#import <Speech/SFEARResultType_Private.h>
#import <Speech/SFSpeechAnalyzerOutputWrapper_Private.h>
#import <Speech/SFSpeechRecognitionTaskHint.h>
#import <Speech/SFTranscriptionOptions_Private.h>
#import <Speech/SFTranscriptionResultAttributeOptions_Private.h>

NS_ASSUME_NONNULL_BEGIN

@class EARVoiceCommandActiveSet;
@class _SFAnalysisContext;
@class _SFContextualNamedEntity;
@class _SFAnalyzerTranscriptionSegment;
@class _SFCommandRecognizerArgument;
@class _SFCommandRecognizerInterpretation;
@class _STCommandRecognizerResult;
@class _SFEndpointingResult;
@class _SFInputSequencer;
@class _SFModelDownloadRequest;
@class _SFSpeechAnalyzerCommandRecognizerOptions;
@class _SFSpeechAnalyzerOptions;
@class _SFSpeechAnalyzerOptionsLoggingInfo;
@class _SFSpeechAnalyzerOptionsPowerContext;
@class _SFSpeechAnalyzerTranscriberOptions;
@class _SFTranscriberModelOptions;
@class _STTranscriberMultisegmentResult;
@class _SFTranscriberResult;
@class _SFToken;
@protocol _SFSpeechAnalyzerTranscriberResultDelegate;
@protocol _SFSpeechAnalyzerEndpointingResultDelegate;


API_AVAILABLE(macos(14), ios(17))
@interface _SFSpeechAnalyzer : NSObject

+ (nullable _SFModelDownloadRequest *)modelDownloadRequestForClientIdentifier:(NSString *)clientIdentifier
        transcriberOptions:(_SFSpeechAnalyzerTranscriberOptions *)transcriberOptions;

/**
    @param transcriberOptions `transcriptionOptions` should not contain
    `_SFTranscriptionOptionsNormalizedTranscription` or `_SFTranscriptionOptionsContextualizedTranscription`.
    Both types of output will be provided.
 */
- (instancetype)initWithClientIdentifier:(NSString *)clientIdentifier
        inputSequence:(_SFInputSequencer *)inputSequence
        audioFormat:(AVAudioFormat *)audioFormat
        transcriberResultDelegate:(id<_SFSpeechAnalyzerTranscriberResultDelegate>)transcriberResultDelegate
        endpointingResultDelegate:(id<_SFSpeechAnalyzerEndpointingResultDelegate>)endpointingResultDelegate
        queue:(NSOperationQueue *)queue
        transcriberOptions:(_SFSpeechAnalyzerTranscriberOptions *)transcriberOptions
        commandRecognizerOptions:(_SFSpeechAnalyzerCommandRecognizerOptions *)commandRecognizerOptions
        options:(_SFSpeechAnalyzerOptions *_Nullable)options
        restrictedLogging:(BOOL)restrictedLogging
        geoLMRegionID:(NSString *_Nullable)geoLMRegionID
        contextualNamedEntities:(NSArray <_SFContextualNamedEntity *> *_Nullable)contextualNamedEntities
        didChangeVolatileRange:(void (^ _Nullable)(CMTimeRange, BOOL, BOOL))didChangeVolatileRange;

- (instancetype)init NS_UNAVAILABLE;

// The input sequence cannot be changed after the analyzer is created.

@property (readonly) _SFInputSequencer *inputSequence;

// Does not include bestAudioFormat and bestAvailableAudioFormat, because ESConnection
// expects to be able to use 8k and 16k sampling rates.

// No getter for volatileRange.

// TODO: inputAudioFormat getter?


/// This just returns the end of the volatile range. The time value will be invalid if there is no start time. Use `CMTIME_IS_INVALID` to check.
- (void)getNextBufferStartTimeWithCompletion:(void (^)(CMTime))completion;

- (void)setDidChangeVolatileRange:(void (^ _Nullable)(CMTimeRange, BOOL, BOOL))handler completion:(void (^)(void))completion;

- (void)cancelPendingResultsAndPauseWithCompletion:(void (^)(NSError *_Nullable))completion;

- (void)resumeWithCompletion:(void (^)(NSError *_Nullable))completion;

- (void)finalizeWithCompletion:(void (^)(NSError *_Nullable))completion;

/// @param time If invalid, it's the same as omitting it.
- (void)finalizeThrough:(CMTime)time completion:(void (^)(NSError *_Nullable))completion;

- (void)finalizeAndFinishWithCompletion:(void (^)(NSError *_Nullable))completion;

/// @param time If invalid, it's the same as omitting it.
- (void)finalizeAndFinishThrough:(CMTime)time completion:(void (^)(NSError *_Nullable))completion;

- (void)finalizeAndFinishThroughEndOfInputWithCompletion:(void (^)(NSError *_Nullable))completion;

/// @param times An array of CMTime values.
- (void)requestResultAtEndpointTimes:(NSArray<NSValue *> *)times;

- (void)getModelInfoTasksWithCompletion:(void (^)(NSSet<NSString *> *))completion;
- (void)getModelInfoLanguageWithCompletion:(void (^)(NSString *))completion;
- (void)getRecognitionStatisticsWithCompletion:(void (^)(NSDictionary *))completion;
- (void)getRecognitionUtterenceStatisticsWithCompletion:(void (^)(NSDictionary *))completion;

/**
    Each time this is called, a new object is returned. However, different `_SFAnalysisContext` objects
    may or may not refer to the same `AnalysisContext` object, and there's no way to tell. This will be fixed later.
*/
- (void)getContextWithCompletion:(void (^)(_SFAnalysisContext *))completion;

- (void)prepareToAnalyzeReportingInto:(NSProgress *_Nullable)progress
        completion:(void (^)(NSError *_Nullable))completion;

@end


API_AVAILABLE(macos(14), ios(17))
NS_SWIFT_SENDABLE
@protocol _SFSpeechAnalyzerTranscriberResultDelegate
- (void)speechAnalyzer:(_SFSpeechAnalyzer *)speechAnalyzer
        didProduceTranscriberResult:(_SFTranscriberResult *)transcriberResult;
- (void)speechAnalyzer:(_SFSpeechAnalyzer *)speechAnalyzer
        didStopTranscriptionWithError:(NSError *)error;
// TODO: Can remove @optional once Core Speech updated to implement delegate.
@optional
- (void)speechAnalyzerDidProduceAllTranscriberResults:(_SFSpeechAnalyzer *)speechAnalyzer;
@end


API_AVAILABLE(macos(14), ios(17))
NS_SWIFT_SENDABLE
@protocol _SFSpeechAnalyzerEndpointingResultDelegate
- (void)speechAnalyzer:(_SFSpeechAnalyzer *)speechAnalyzer
        didProduceEndpointingResult:(_SFEndpointingResult *)endpointingResult;
- (void)speechAnalyzer:(_SFSpeechAnalyzer *)speechAnalyzer
        didStopEndpointingWithError:(NSError *)error;
@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFModelDownloadRequest : NSObject
// Wrapper for ModelDownloadRequest.

@property (nonatomic, readonly) NSProgress *progress;

- (void)downloadWithCompletion:(void (^)(NSError *_Nullable))completion;

@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFSpeechAnalyzerTranscriberOptions : NSObject

@property (nonatomic, copy) NSLocale *locale;
@property (nonatomic) SFSpeechRecognitionTaskHint taskHint;
@property (nonatomic, copy, nullable) _SFTranscriberModelOptions *modelOptions;
@property (nonatomic) _SFTranscriptionOptions transcriptionOptions;
@property (nonatomic) _SFTranscriptionResultAttributeOptions attributeOptions;

// TODO: add reportingOptions?

- (instancetype)init;

@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFSpeechAnalyzerCommandRecognizerOptions : NSObject

@property (nonatomic, copy) EARVoiceCommandActiveSet *voiceCommandActiveSet;

- (instancetype)initWithVoiceCommandActiveSet:(EARVoiceCommandActiveSet *)voiceCommandActiveSet;

@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFSpeechAnalyzerOptions : NSObject<NSCopying>
// corresponds to AnalysisOptions

// This is similar to _SFAnalysisOptions, but that's used for XPC, and is not a part of the API.

@property (nonatomic, readonly) BOOL highPriority;
@property (nonatomic, readonly, copy, nullable) _SFSpeechAnalyzerOptionsLoggingInfo *loggingInfo;
@property (nonatomic, readonly, copy, nullable) _SFSpeechAnalyzerOptionsPowerContext *powerContext;

- (instancetype)initWithHighPriority:(BOOL)highPriority
        loggingInfo:(_SFSpeechAnalyzerOptionsLoggingInfo *_Nullable)loggingInfo
        powerContext:(_SFSpeechAnalyzerOptionsPowerContext *_Nullable)powerContext;

@end

API_AVAILABLE(macos(14), ios(17))
@interface _SFSpeechAnalyzerOptionsLoggingInfo : NSObject<NSCopying>

@property (nonatomic, readonly, copy) NSUUID *asrID;
@property (nonatomic, readonly, copy) NSUUID *requestID;

- (instancetype)initWithAsrID:(NSUUID *)asrID
        requestID:(NSUUID *)requestID;

@end

API_AVAILABLE(macos(14), ios(17))
@interface _SFSpeechAnalyzerOptionsPowerContext : NSObject<NSCopying>

@property (nonatomic, readonly, copy) NSString *ane;
@property (nonatomic, readonly, copy) NSString *cpu;
@property (nonatomic, readonly, copy) NSString *gpu;

- (instancetype)initWithAne:(NSString *)ane
        cpu:(NSString *)cpu
        gpu:(NSString *)gpu;

@end


@interface _SFTranscriberModelOptions : NSObject<NSCopying>
// corresponds to Transcriber.ModelOptions

@property (nonatomic, readonly, copy, nullable) NSURL *supplementalModelURL;
@property (nonatomic, readonly) BOOL farField;
@property (nonatomic, readonly, copy, nullable) NSURL *modelOverrideURL;
@property (nonatomic, readonly, copy, nullable) NSString *taskForMemoryLock;
@property (nonatomic, readonly, copy) NSArray<NSURL *> *speechProfileURLs;

- (instancetype)initWithSupplementalModelURL:(NSURL *_Nullable)supplementalModelURL
        farField:(BOOL)farField
        modelOverrideURL:(NSURL *_Nullable)modelOverrideURL
        speechProfileURLs:(NSArray<NSURL *> *)speechProfileURLs
        taskForMemoryLock:(NSString *_Nullable)taskForMemoryLock;

@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFTranscriberResult : NSObject
@property (nonatomic, readonly) CMTimeRange range;
@property (nonatomic, readonly, copy) _STTranscriberMultisegmentResult *normalizedTranscriberMultisegmentResult;
@property (nonatomic, readonly, copy, nullable) _STCommandRecognizerResult *normalizedCommandRecognizerResult;
@property (nonatomic, readonly, copy) _STTranscriberMultisegmentResult *contextualizedTranscriberMultisegmentResult;
@property (nonatomic, readonly, copy, nullable) _STCommandRecognizerResult *contextualizedCommandRecognizerResult;

- (instancetype)initWithRange:(CMTimeRange)range
        normalizedTranscriberMultisegmentResult:(_STTranscriberMultisegmentResult *)normalizedTranscriberMultisegmentResult
        normalizedCommandRecognizerResult:(nullable _STCommandRecognizerResult *)normalizedCommandRecognizerResult
        contextualizedTranscriberMultisegmentResult:(_STTranscriberMultisegmentResult *)contextualizedTranscriberMultisegmentResult
        contextualizedCommandRecognizerResult:(nullable _STCommandRecognizerResult *)contextualizedCommandRecognizerResult;
@end


API_AVAILABLE(macos(14), ios(17))
@interface _STTranscriberMultisegmentResult : NSObject<NSCopying>
// corresponds to Transcriber.MultisegmentResult, except for the range property.

@property (nonatomic, readonly, copy) NSArray<_SFAnalyzerTranscriptionSegment *> *segments;
@property (nonatomic, readonly, copy) NSArray<NSArray<_SFToken *> *> *transcriptions;
@property (nonatomic, readonly) _SFEARResultType earResultType;
@property (nonatomic, readonly, copy) NSArray<NSIndexPath *> *nBestChoices;
@property (nonatomic, readonly) CMTimeRange recognitionAudioRange;

- (instancetype)initWithSegments:(NSArray<_SFAnalyzerTranscriptionSegment *> *)segments
        transcriptions:(NSArray<NSArray<_SFToken *> *> *)transcriptions
        earResultType:(_SFEARResultType)earResultType
        nBestChoices:(NSArray<NSIndexPath *> *)nBestChoices
        recognitionAudioRange:(CMTimeRange)recognitionAudioRange;

@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFAnalyzerTranscriptionSegment : NSObject
// corresponds to TranscriptionSegment
// Similar to _SFTranscriptionSegment, but in a different format.

@property (nonatomic, readonly, copy) NSArray<_SFToken *> *text;
@property (nonatomic, readonly, copy) NSArray<NSArray<_SFToken *> *> *alternatives;

- (instancetype)initWithText:(NSArray<_SFToken *> *)text
        alternatives:(NSArray<NSArray<_SFToken *> *> *)alternatives;

@end


API_AVAILABLE(macos(14), ios(17))
@interface _STCommandRecognizerResult : NSObject<NSCopying>
// Corresponds to CommandRecognizer.Result, except for the range property.

- (instancetype)initWithTranscriptionCommands:(NSArray<NSArray<_SFCommandRecognizerInterpretation *> *> *)transcriptionCommands;

@property (nonatomic, readonly) NSArray<NSArray<_SFCommandRecognizerInterpretation *> *> *transcriptionCommands;

@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFCommandRecognizerInterpretation : NSObject
// corresponds to CommandRecognizer.Interpretation

@property (nonatomic, readonly, copy) NSString *commandIdentifier;
@property (nonatomic, readonly, copy) NSSet<NSString *> *suiteIdentifiers;
@property (nonatomic, readonly) NSRange range;
@property (nonatomic, readonly, copy) NSIndexSet *verbIndexes;
@property (nonatomic, readonly, copy) NSArray<_SFCommandRecognizerArgument *> *arguments;

- (instancetype)initWithCommandIdentifier:(NSString *)commandIdentifier
        suiteIdentifiers:(NSSet<NSString *> *)suiteIdentifiers
        range:(NSRange)range
        verbIndexes:(NSIndexSet *)verbIndexes
        arguments:(NSArray<_SFCommandRecognizerArgument *> *)arguments;

@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFCommandRecognizerArgument : NSObject
// corresponds to CommandRecognizer.Argument

@property (nonatomic, readonly) _SFCommandRecognizerArgumentPresence presence;
@property (nonatomic, readonly, copy) NSIndexSet *indexes;
@property (nonatomic, readonly, copy) NSIndexSet *adpositionIndexes;

- (instancetype)initWithPresence:(_SFCommandRecognizerArgumentPresence)presence
        indexes:(NSIndexSet *)indexes
        adpositionIndexes:(NSIndexSet *)adpositionIndexes;

@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFEndpointingResult : NSObject
// corresponds to EndpointDetector.ModuleOutput

@property (nonatomic, readonly) CMTimeRange range;
@property (nonatomic, readonly) NSInteger wordCount;
@property (nonatomic, readonly) double eosLikelihood;
@property (nonatomic, readonly, copy) NSArray<NSNumber *> *pauseCounts;
@property (nonatomic, readonly) double silencePosterior;

- (instancetype)initWithRange:(CMTimeRange)range
        wordCount:(NSInteger)wordCount
        eosLikelihood:(double)eosLikelihood
        pauseCounts:(NSArray<NSNumber *> *)pauseCounts
        silencePosterior:(double)silencePosterior;

@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFToken : NSObject<NSCopying>

@property(nonatomic, readonly, copy) NSString *text;
@property(nonatomic, readonly) double confidence;
@property(nonatomic, readonly) double startTime;
@property(nonatomic, readonly) double duration;

- (instancetype)initWithText:(NSString *)text
                    confidence:(double)confidence
                    startTime:(double)startTime
                    duration:(double)duration;

@end

NS_ASSUME_NONNULL_END
