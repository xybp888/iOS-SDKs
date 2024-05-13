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

#endif
