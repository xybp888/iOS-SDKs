/*
 * Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#ifndef __OS_TRACE_BASE_H__
#define __OS_TRACE_BASE_H__

/*
 * Some of these Darwin or POSIX header files aren't available in all SDKs,
 * e.g., RTKit, so don't include them if not available.
 */
#if __has_include(<mach-o/loader.h>)
#include <mach-o/loader.h>
#endif
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#if __has_include(<sys/time.h>)
#include <sys/time.h>
#endif
#if __has_include(<sys/types.h>)
#include <sys/types.h>
#endif
#include <unistd.h>
/*
 * Each of these header files has a standalone implementation for SDKs
 * (e.g. RTKit) where the headers aren't available.  Switch to using
 * those, if made available.
 */
#if __has_include(<os/availability.h>)
#include <os/availability.h>
#else
#include <os/log_availability.h>
#endif
#if __has_include(<os/base.h>)
#include <os/base.h>
#else
#include <os/log_base.h>
#endif
#if __has_include(<os/object.h>)
#include <os/object.h>
#else
#include <os/log_object.h>
#endif

/*
 * The os/log_trace_base.h header, if existing, contains sensitive
 * values used to configure logging API behaviour.  Prior to including
 * it, undefine all of those sensitive values to prevent external
 * callers from injecting their own overrides, intentionally or not.
 */
#undef OS_LOG_STRING_SECTION
#if __has_include(<os/log_trace_base.h>)
#include <os/log_trace_base.h>
#endif

#define OS_LOG_FORMATLIKE(x, y)  __attribute__((format(os_log, x, y)))

#define __OS_LOG_OS_FEATURES_AT_LEAST(macos, ios, tvos, watchos) \
        (  (defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_##macos) \
        || (defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_##ios) \
        || (defined(__TV_OS_VERSION_MIN_REQUIRED) && __TV_OS_VERSION_MIN_REQUIRED >= __TVOS_##tvos) \
        || (defined(__WATCH_OS_VERSION_MIN_REQUIRED) && __WATCH_OS_VERSION_MIN_REQUIRED >= __WATCHOS_##watchos) \
        || (defined(__RTKIT__)) \
        )

#if __OS_LOG_OS_FEATURES_AT_LEAST(10_15, 13_0, 13_0, 6_0)
#define OS_LOG_TARGET_HAS_10_15_FEATURES 1
#else
#define OS_LOG_TARGET_HAS_10_15_FEATURES 0
#endif

#if __OS_LOG_OS_FEATURES_AT_LEAST(10_14, 12_0, 12_0, 5_0)
#define OS_LOG_TARGET_HAS_10_14_FEATURES 1
#else
#define OS_LOG_TARGET_HAS_10_14_FEATURES 0
#endif

#if __OS_LOG_OS_FEATURES_AT_LEAST(10_13, 11_0, 11_0, 4_0)
#define OS_LOG_TARGET_HAS_10_13_FEATURES 1
#else
#define OS_LOG_TARGET_HAS_10_13_FEATURES 0
#endif

#if __OS_LOG_OS_FEATURES_AT_LEAST(10_12, 10_0, 10_0, 3_0)
#define OS_LOG_TARGET_HAS_10_12_FEATURES 1
#else
#define OS_LOG_TARGET_HAS_10_12_FEATURES 0
#endif

#ifndef OS_COUNT_ARGS
#define OS_COUNT_ARGS(...) OS_COUNT_ARGS1(, ##__VA_ARGS__, _8, _7, _6, _5, _4, _3, _2, _1, _0)
#define OS_COUNT_ARGS1(z, a, b, c, d, e, f, g, h, cnt, ...) cnt
#endif

#ifdef OS_LOG_FORMAT_WARNINGS
#define OS_LOG_FORMAT_ERRORS _Pragma("clang diagnostic warning \"-Wformat\"")
#else
#define OS_LOG_FORMAT_ERRORS _Pragma("clang diagnostic error \"-Wformat\"")
#endif

#define OS_LOG_PRAGMA_PUSH \
        _Pragma("clang diagnostic push") \
        _Pragma("clang diagnostic ignored \"-Wvla\"") \
        OS_LOG_FORMAT_ERRORS

#define OS_LOG_PRAGMA_POP  _Pragma("clang diagnostic pop")

#if __has_attribute(uninitialized)
#define OS_LOG_UNINITIALIZED __attribute__((uninitialized))
#else
#define OS_LOG_UNINITIALIZED
#endif

#ifndef OS_LOG_STRING_SECTION
#define OS_LOG_STRING_SECTION "__TEXT,__oslogstring,cstring_literals"
#endif

#define OS_LOG_STRING(_ns, _var, _str) \
        _Static_assert(__builtin_constant_p(_str), \
                "format/label/description argument must be a string constant"); \
        __attribute__((section(OS_LOG_STRING_SECTION),internal_linkage)) \
        static const char _var[] __asm(OS_STRINGIFY(OS_CONCAT(LOS_##_ns, __COUNTER__))) = _str


#define OS_LOG_REMOVE_PARENS(...) __VA_ARGS__

#define OS_LOG_CALL_WITH_FORMAT(fun, fun_args, fmt, ...) __extension__({ \
        OS_LOG_PRAGMA_PUSH OS_LOG_STRING(LOG, _os_fmt_str, fmt); \
        __attribute__((stack_protector_ignore)) \
        uint8_t _Alignas(16) OS_LOG_UNINITIALIZED _os_fmt_buf[__builtin_os_log_format_buffer_size(fmt, ##__VA_ARGS__)]; \
        fun(OS_LOG_REMOVE_PARENS fun_args, _os_fmt_str, \
                (uint8_t *)__builtin_os_log_format(_os_fmt_buf, fmt, ##__VA_ARGS__), \
                (uint32_t)sizeof(_os_fmt_buf)) OS_LOG_PRAGMA_POP; \
})

#define OS_LOG_CALL_WITH_FORMAT_NAME(fun, fun_args, name, fmt, ...) __extension__({ \
        OS_LOG_PRAGMA_PUSH OS_LOG_STRING(LOG, _os_fmt_str, fmt); \
        OS_LOG_STRING(LOG, _os_name_str, name); \
        __attribute__((stack_protector_ignore)) \
        uint8_t _Alignas(16) OS_LOG_UNINITIALIZED _os_fmt_buf[__builtin_os_log_format_buffer_size(fmt, ##__VA_ARGS__)]; \
        fun(OS_LOG_REMOVE_PARENS fun_args, _os_name_str, _os_fmt_str, \
                (uint8_t *)__builtin_os_log_format(_os_fmt_buf, fmt, ##__VA_ARGS__), \
                (uint32_t)sizeof(_os_fmt_buf)) OS_LOG_PRAGMA_POP; \
})

/*
 * If not building Swift and without Objective C, allow for annotating
 * types for Swift.  This is currently only useful for RTKit, which
 * doesn't have Objective C yet wants Swift (embedded) support.  It
 * should be ignored by other platforms and cause no effects.
 */
#if !OS_OBJECT_SWIFT3 && !OS_OBJECT_USE_OBJC
#define LOG_SWIFT_NEWTYPE(_type) __attribute__((__swift_newtype__(_type)))
#define LOG_SWIFT_NAME(_type) OS_SWIFT_NAME(_type)
#else
#define LOG_SWIFT_NEWTYPE(_type)
#define LOG_SWIFT_NAME(_type)
#endif

__BEGIN_DECLS

extern struct mach_header __dso_handle;

__END_DECLS

#endif // !__OS_TRACE_BASE_H__
