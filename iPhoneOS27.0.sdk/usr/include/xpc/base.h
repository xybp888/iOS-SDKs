// Copyright (c) 2009-2011 Apple Inc. All rights reserved.

#ifndef __XPC_BASE_H__
#define __XPC_BASE_H__

#include <sys/cdefs.h>

#if !defined(__has_include)
#define __has_include(x) 0
#endif // !defined(__has_include)

#if !defined(__has_attribute)
#define __has_attribute(x) 0
#endif // !defined(__has_attribute)

#if !defined(__has_feature)
#define __has_feature(x) 0
#endif // !defined(__has_feature)

#if !defined(__has_extension)
#define __has_extension(x) 0
#endif // !defined(__has_extension)

#if __has_include(<xpc/availability.h>)
#include <xpc/availability.h>
#else // __has_include(<xpc/availability.h>)
#include <Availability.h>
#endif // __has_include(<xpc/availability.h>)

#include <os/availability.h>

#ifndef __XPC_INDIRECT__
#error "Please #include <xpc/xpc.h> instead of this file directly."
#endif // __XPC_INDIRECT__ 

__BEGIN_DECLS

#ifndef __XPC_TEST__
#define __XPC_TEST__ 0
#endif

#ifndef XPC_CONCAT
#define XPC_CONCAT(_A, _B) XPC_CONCAT_(_A, _B)
#define XPC_CONCAT_(_A, _B) _A ## _B
#endif

#pragma mark Attribute Shims
// We use __has_attribute to check for attribute existance. The macros are set
// up to always use __ before and after attributes to guard against
// similarly-named mactos since these go in public headers. We also use
// __attribute__ for best compatibility with older C/C++ versions. Attributes
// should be optimized for use by Clang (i.e. use Clang's preferred form over a
// supported GCC form if it's preferred by the compiler). Attributes are
// defined in the order that they appear in Clang's doccumentation

#if !defined(__has_attribute)
#define __has_attribute(_X) 0
#endif // !defined(__has_attribute)

#define _XPC_CHOOSE_0(...)
#define _XPC_CHOOSE_1(...) __VA_ARGS__

#define XPC_ATTRIBUTE(_X, ...) XPC_CONCAT(_XPC_CHOOSE_, __has_attribute(_X))(__attribute__((__##_X##__(__VA_ARGS__))))

// Swift attributes
#define XPC_SWIFT_SENDABLE XPC_ATTRIBUTE(swift_attr, "@Sendable")
#define XPC_SWIFT_NAME(_Name) XPC_ATTRIBUTE(swift_name, _Name)
#define XPC_SWIFT_UNAVAILABLE(msg) __swift_unavailable(msg)
#define XPC_SWIFT_NOEXPORT XPC_SWIFT_UNAVAILABLE("Unavailable in Swift from the XPC C Module")
// Declaration attributes
#define XPC_DEPRECATED(_M) XPC_ATTRIBUTE(deprecated, _M)
#define XPC_TRANSPARENT_UNION XPC_ATTRIBUTE(transparent_union)
// Function attributes
#define XPC_NORETURN XPC_ATTRIBUTE(noreturn)
#define XPC_ALLOC_SIZE(...) XPC_MALLOC XPC_ATTRIBUTE(alloc_size, __VA_ARGS__)
#define XPC_INLINE static inline XPC_ATTRIBUTE(always_inline)
#define XPC_RETURNS_ALIGNED(_N) XPC_ATTRIBUTE(assume_aligned, _N)
#define XPC_CONSTRUCTOR XPC_ATTRIBUTE(constructor)
#define XPC_PRINTF(_M, _N) XPC_ATTRIBUTE(format, printf, _M, _N)
#define XPC_MALLOC XPC_ATTRIBUTE(malloc)
#define XPC_WARN_RESULT XPC_ATTRIBUTE(warn_unused_result)
#define XPC_NOINLINE XPC_ATTRIBUTE(noinline)
#define XPC_NOTHROW XPC_ATTRIBUTE(nothrow)
#define XPC_USED XPC_ATTRIBUTE(used)
// Nullibility attributes
#define XPC_NONNULL1 XPC_ATTRIBUTE(nonnull, 1)
#define XPC_NONNULL2 XPC_ATTRIBUTE(nonnull, 2)
#define XPC_NONNULL3 XPC_ATTRIBUTE(nonnull, 3)
#define XPC_NONNULL4 XPC_ATTRIBUTE(nonnull, 4)
#define XPC_NONNULL5 XPC_ATTRIBUTE(nonnull, 5)
#define XPC_NONNULL6 XPC_ATTRIBUTE(nonnull, 6)
#define XPC_NONNULL7 XPC_ATTRIBUTE(nonnull, 7)
#define XPC_NONNULL8 XPC_ATTRIBUTE(nonnull, 8)
#define XPC_NONNULL9 XPC_ATTRIBUTE(nonnull, 9)
#define XPC_NONNULL10 XPC_ATTRIBUTE(nonnull, 10)
#define XPC_NONNULL11 XPC_ATTRIBUTE(nonnull, 11)
#define XPC_NONNULL_ALL XPC_ATTRIBUTE(nonnull)
#define XPC_RETURNS_NONNULL XPC_ATTRIBUTE(returns_nonnull)
// Variable attributes
#define XPC_UNUSED XPC_ATTRIBUTE(unused)
#define XPC_NOESCAPE XPC_ATTRIBUTE(noescape)
// Other attributes
#define XPC_READ_NONE XPC_ATTRIBUTE(const) // const attribute adds memory(none)
#define XPC_PACKED XPC_ATTRIBUTE(packed)
#define XPC_PURE XPC_ATTRIBUTE(pure) // pure attribute adds memory(read)
#define XPC_NOIMPL XPC_ATTRIBUTE(unavailable)

// diagnose_as_builtin
#if !defined(__has_builtin)
#define __has_builtin(_X) 0
#endif
#define XPC_DIAGNOSE_AS(_Builtin, ...) XPC_CONCAT(_XPC_CHOOSE_, __has_builtin(__builtin_ ## _Builtin))(XPC_ATTRIBTUE(diagnose_as_builtin, __builtin_ ## _Builtin)(__VA_ARGS__))

// __abortlike
#ifdef __abortlike
#define XPC_ABORTLIKE __abortlike
#else
#define XPC_ABORTLIKE
#endif

// unavailable(message)
#if __has_extension(attribute_unavailable_with_message)
#define XPC_UNAVAILABLE(m) XPC_ATTRIBUTE(unavailable, m)
#else
#define XPC_UNAVAILABLE(m) XPC_NOIMPL
#endif

// _xpc_unreachable
#if __has_builtin(__builtin_unreachable)
#define _xpc_unreachable() __builtin_unreachable()
#else
#define _xpc_unreachable()
#endif

#pragma mark Import/Export
#define XPC_CONST const
#define XPC_NOCONST
#define XPC_EXPORT extern XPC_ATTRIBUTE(visibility, "default")
#define XPC_NOEXPORT XPC_ATTRIBUTE(visibility, "hidden")
#define XPC_DEBUGGER_EXCL XPC_NOEXPORT XPC_USED
#define XPC_WEAKIMPORT extern XPC_ATTRIBUTE(weak_import)

// XPC_TESTEXPORT
#ifndef XPC_TESTEXPORT
#define XPC_TESTEXPORT XPC_NOEXPORT
#endif // XPC_TESTEXPORT

// XPC_TESTCONST
#ifndef XPC_TESTCONST
#define XPC_TESTCONST XPC_CONST
#endif // XPC_TESTCONST

#if __XPC_TEST__
#define XPC_TESTSTATIC
#define XPC_TESTEXTERN extern
#define XPC_TESTNORETURN
#else // __XPC_TEST__
#define XPC_TESTSTATIC static
#define XPC_TESTNORETURN XPC_NORETURN
#endif // __XPC_TEST__

#pragma mark ARC
#if __has_feature(objc_arc)
#define XPC_GIVES_REFERENCE __strong
#define XPC_UNRETAINED __unsafe_unretained
#define XPC_BRIDGE(xo) ((__bridge void *)(xo))
#define XPC_BRIDGEREF_BEGIN(xo) ((__bridge_retained void *)(xo))
#define XPC_BRIDGEREF_BEGIN_WITH_REF(xo) ((__bridge void *)(xo))
#define XPC_BRIDGEREF_MIDDLE(xo) ((__bridge id)(xo))
#define XPC_BRIDGEREF_END(xo) ((__bridge_transfer id)(xo))
#else // __has_feature(objc_arc)
#define XPC_GIVES_REFERENCE
#define XPC_UNRETAINED
#define XPC_BRIDGE(xo) (xo)
#define XPC_BRIDGEREF_BEGIN(xo) (xo)
#define XPC_BRIDGEREF_BEGIN_WITH_REF(xo) (xo)
#define XPC_BRIDGEREF_MIDDLE(xo) (xo)
#define XPC_BRIDGEREF_END(xo) (xo)
#endif // __has_feature(objc_arc)


#pragma mark Nullability
#if __has_feature(assume_nonnull)
#define XPC_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define XPC_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
#else
#define XPC_ASSUME_NONNULL_BEGIN
#define XPC_ASSUME_NONNULL_END
#endif

#if __has_feature(nullability_on_arrays)
#define XPC_NONNULL_ARRAY _Nonnull
#else
#define XPC_NONNULL_ARRAY
#endif

#pragma mark Bounds safety attributes
#if defined(__has_ptrcheck) && __has_ptrcheck
#define XPC_PTR_ASSUMES_SINGLE __ptrcheck_abi_assume_single()
#define XPC_SINGLE __single
#define XPC_UNSAFE_INDEXABLE __unsafe_indexable
// This should be __null_terminated but because it was originally defined this
// way, it will cause build failures to fix
#define XPC_CSTRING XPC_UNSAFE_INDEXABLE
#define XPC_SIZEDBY(N) __sized_by(N)
#define XPC_COUNTEDBY(N) __counted_by(N)
#define XPC_UNSAFE_FORGE_SIZED_BY(_type, _ptr, _size) \
		__unsafe_forge_bidi_indexable(_type, _ptr, _size)
#define XPC_UNSAFE_FORGE_SINGLE(_type, _ptr) \
		__unsafe_forge_single(_type, _ptr)
#else // defined(__has_ptrcheck) ** __has_ptrcheck
#define XPC_PTR_ASSUMES_SINGLE
#define XPC_SINGLE
#define XPC_UNSAFE_INDEXABLE
#define XPC_CSTRING
#define XPC_SIZEDBY(N)
#define XPC_COUNTEDBY(N)
#define XPC_UNSAFE_FORGE_SIZED_BY(_type, _ptr, _size) ((_type)(_ptr))
#define XPC_UNSAFE_FORGE_SINGLE(_type, _ptr) ((_type)(_ptr))
#endif // defined(__has_ptrcheck) ** __has_ptrcheck

#pragma mark Enums
// XPC_FLAGS_ENUM
#ifdef OS_CLOSED_OPTIONS
#define XPC_FLAGS_ENUM(_name, _type, ...) \
		OS_CLOSED_OPTIONS(_name, _type, __VA_ARGS__)
#else
#define XPC_FLAGS_ENUM(_name, _type, ...) \
		OS_ENUM(_name, _type, __VA_ARGS__)
#endif

// XPC_ENUM
#ifdef OS_CLOSED_ENUM
#define XPC_ENUM(_name, _type, ...) \
		OS_CLOSED_ENUM(_name, _type, __VA_ARGS__)
#else
#define XPC_ENUM(_name, _type, ...) \
		OS_ENUM(_name, _type, __VA_ARGS__)
#endif

__END_DECLS

#endif // __XPC_BASE_H__ 
