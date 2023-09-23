//
//  PlaygroundTransformRuntime.h
//  LiveExecutionResultsRuntime
//
//  Copyright © 2016-2020 Apple Inc. All rights reserved.
//

#import <LiveExecutionResultsRuntime/PlaygroundRuntimeDefines.h>
#import <Foundation/Foundation.h>

#ifdef __OBJC2__

typedef void(*_ler_send_log_data_t)(_Nonnull id);

LER_EXPORT _ler_send_log_data_t _Nullable _ler_send_log_data;

// !!! NOTE: This type must be kept in sync with the version in PlaygroundLogger.framework.

typedef bool (* _Nullable _playground_logger_should_capture_t)(_Nullable id /*instance*/,  NSString * _Nullable  /*name*/, NSInteger /*startLine*/, NSInteger /*endLine*/, NSInteger /*startColumn*/, NSInteger /*endColumn*/, NSInteger /*module_id*/, NSInteger /*file_id*/);

LER_EXPORT _playground_logger_should_capture_t _Nullable _playground_logger_should_capture;

#endif
