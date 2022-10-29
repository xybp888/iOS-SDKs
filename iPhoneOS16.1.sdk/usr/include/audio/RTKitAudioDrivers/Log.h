//
//  Log.h
//  RTKitAudioDrivers
//
//  Created by Virag Doshi on 8/9/18.
//  Copyright © 2018 Apple, Inc. All rights reserved.
//

#pragma once

//-----------------------------------------------------------------------------------
#pragma mark -
#pragma mark Log Levels
//-----------------------------------------------------------------------------------

#define MINUTIAE_LOG_LEVEL 6
#define DEBUG_LOG_LEVEL    5
#define INFO_LOG_LEVEL     4
#define NOTICE_LOG_LEVEL   3
#define WARNING_LOG_LEVEL  2
#define ERROR_LOG_LEVEL    1

#define MINUTIAE_LOG_DELIM  "Minutiae"
#define DEBUG_LOG_DELIM     "Debug"
#define INFO_LOG_DELIM      "Info"
#define NOTICE_LOG_DELIM    "Notice"
#define WARNING_LOG_DELIM   "Warning"
#define ERROR_LOG_DELIM     "Error"

//-----------------------------------------------------------------------------------
#pragma mark -
#pragma mark Static Logging
//-----------------------------------------------------------------------------------

/*
 * LOG_LEVEL - This should remain statically defined in a runtime envrionment with limited resources
 */
#if defined DEBUG
    #define LOG_LEVEL   DEBUG_LOG_LEVEL
#else
    #define LOG_LEVEL   NOTICE_LOG_LEVEL
#endif


/*
 * __LOG__ - for internal use only
 */
#ifndef __LOG__
    #if LOGGING_TYPE == LOGGING_TYPE_SYSLOG
        #define __LOG__(delim, ...)                         \
            do {                                            \
                syslog(LOG_ALWAYS, __VA_ARGS__);            \
            } while (0)
    #elif LOGGING_TYPE == LOGGING_TYPE_OSLOG
        #define __LOG__(delim, ...)                                                     \
            do {                                                                        \
                os_log(RTKitAudioFramework::System::getOSLogChannel(), __VA_ARGS__);    \
            } while (0)
    #elif LOGGING_TYPE == LOGGING_TYPE_PRINTF
        #define __LOG__(delim, ...)                         \
            do {                                            \
                printf("[%s] ", delim);                     \
                printf(__VA_ARGS__);                        \
                printf("\n");                               \
            } while (0)
    #else
        #error "LOGGING_TYPE not defined"
    #endif
#endif

/*
 *  LogMinutiae()
 */
#ifndef LogMinutiae
    #if (LOG_LEVEL) >= (MINUTIAE_LOG_LEVEL)
        #define LogMinutiae(...) __LOG__( MINUTIAE_LOG_DELIM, __VA_ARGS__)
    #else
        #define LogMinutiae(...)
    #endif
#endif

/*
 *  LogDebug()
 */
#ifndef LogDebug
    #if (LOG_LEVEL) >= (DEBUG_LOG_LEVEL)
        #define LogDebug(...) __LOG__( DEBUG_LOG_DELIM, __VA_ARGS__)
    #else
        #define LogDebug(...)
    #endif
#endif

/*
 * LogInfo()
 */
#ifndef LogInfo
    #if (LOG_LEVEL) >= (INFO_LOG_LEVEL)
        #define LogInfo(...) __LOG__( INFO_LOG_DELIM , __VA_ARGS__)
    #else
        #define LogInfo(...)
    #endif
#endif

/*
 * LogNotice()
 */
#ifndef LogNotice
    #if (LOG_LEVEL) >= (NOTICE_LOG_LEVEL)
        #define LogNotice(...) __LOG__( NOTICE_LOG_DELIM , __VA_ARGS__)
    #else
        #define LogNotice(...)
    #endif
#endif

/*
 * LogWarning()
 */
#ifndef LogWarning
    #if (LOG_LEVEL) >= (WARNING_LOG_LEVEL)
        #define LogWarning(...) __LOG__( WARNING_LOG_DELIM , __VA_ARGS__)
    #else
        #define LogWarning(...)
    #endif
#endif

/*
 * LogError()
 */
#ifndef LogError
    #if (LOG_LEVEL) >= (ERROR_LOG_LEVEL)
        #define LogError(...) __LOG__( ERROR_LOG_DELIM, __VA_ARGS__)
    #else
        #define LogError(...)
    #endif
#endif


/**
 @name          DTLog
 @abstract      Dynamic Threshold Logging
 
 @discussion:       The logging macros above (LogDebug, LogNotice, etc.) only allow users to choose the log level at  compile time.
 DTLog macros allow the user to change the logging level based on a variable passed to the macro. This allows controlling the logging
 level at run-time at a scale desired to the user (at the smallest scope, each call within the same block can have a different threshold,
 or at the broadest, this level can be set for the whole platform).
 
 In general, if the passed threshold value is higher than (or equal to) the message's logging level, it will get logged.
 
 @example       Here's an example of how this can be used to control the logging level for each object of a class:
 
 Foo.hpp:
 
 @code
 class Foo
 {
    ...
     enum LogLevel : uint8_t
     {
         kMinutiae   = 6,
         kDebug      = 5,
         kInfo       = 4,
         kNotice     = 3,
         kWarning    = 2,
         kError      = 1
     };
    ...
    LogLevel mLogLevel;
    ...
    void      setLogLevel(LogLevel inLvl) { mLogLevel = inLvl }
    LogLevel  getLogLevel() const { return mLogLevel; }
    ...
    void bar();
    ...
 };
 @endcode
 
 Foo.cpp:
 
 @code
 
 #include "Foo.hpp"
 #include "Log.h"
 
 // macros to make DTLogging a little less verbose:
 #define __FOO_DT_LOG_THRESHOLD__    getLogLevel()

 #define FooDTLogMinutiae(...)       DTLogMinutiae(__FOO_DT_LOG_THRESHOLD__, __VA_ARGS__)
 #define FooDTLogDebug(...)          DTLogDebug(__FOO_DT_LOG_THRESHOLD__, __VA_ARGS__)
 ...
 void Foo::bar();
 {
     ...
     FooDTLogInfo("Bar called at %lld", Time::get_time_us());
     ...
 }
 ...
 @endcode
*/

/*
 __DT_LOG__ - for internal use only
 */
#ifndef  __DT_LOG__
    #define __DT_LOG__(threshold, inLogLevel, delim, ...)       \
        do {                                                    \
            if (threshold >= inLogLevel)                        \
            {                                                   \
                __LOG__(delim, __VA_ARGS__);                    \
            }                                                   \
        } while (0)
#endif

/*
 DTLogMinutiae - logs if the threshold is greater than or equal to MINUTIAE_LOG_LEVEL
 */
#ifndef DTLogMinutiae
    #define DTLogMinutiae(threshold, ...)                       \
        __DT_LOG__(threshold, MINUTIAE_LOG_LEVEL, MINUTIAE_LOG_DELIM, __VA_ARGS__)
#endif

/*
 DTLogDebug - logs if the threshold is greater than or equal to DEBUG_LOG_LEVEL
 */
#ifndef DTLogDebug
    #define DTLogDebug(threshold, ...)                          \
        __DT_LOG__(threshold, DEBUG_LOG_LEVEL, DEBUG_LOG_DELIM, __VA_ARGS__)
#endif

/*
 DTLogInfo - logs if the threshold is greater than or equal to INFO_LOG_LEVEL
 */
#ifndef DTLogInfo
    #define DTLogInfo(threshold, ...)                           \
        __DT_LOG__(threshold, INFO_LOG_LEVEL, INFO_LOG_DELIM, __VA_ARGS__)
#endif

/*
 DTLogWarning - logs if the threshold is greater than or equal to WARNING_LOG_LEVEL
 */
#ifndef DTLogWarning
    #define DTLogWarning(threshold, ...)                        \
        __DT_LOG__(threshold, WARNING_LOG_LEVEL, WARNING_LOG_DELIM, __VA_ARGS__)
#endif

/*
 DTLogError - logs if the threshold is greater than or equal to ERROR_LOG_LEVEL
 */
#ifndef DTLogError
    #define DTLogError(threshold, ...)                          \
        __DT_LOG__(threshold, ERROR_LOG_LEVEL, ERROR_LOG_DELIM, __VA_ARGS__)
#endif
