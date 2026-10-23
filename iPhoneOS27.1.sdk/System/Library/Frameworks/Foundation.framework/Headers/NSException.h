/*	NSException.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <stdarg.h>
#if !0
#import <setjmp.h>
#endif

@class NSString, NSDictionary, NSArray<ObjectType>, NSNumber;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* **************	Generic Exception names		***************/

/// Name of a generic exception for general purpose use.
FOUNDATION_EXPORT NSExceptionName const NSGenericException;
/// Name of an exception that occurs when you access outside the bounds of some data, such as beyond the end of a string or array.
FOUNDATION_EXPORT NSExceptionName const NSRangeException;
/// Name of an exception that occurs when you pass an invalid argument to a method, such as a `nil` pointer where a non-`nil` object is required.
FOUNDATION_EXPORT NSExceptionName const NSInvalidArgumentException;
/// Name of an exception that occurs when an internal assertion fails and implies an unexpected condition within the called code.
FOUNDATION_EXPORT NSExceptionName const NSInternalInconsistencyException;

/// Name of an exception that occurs when the system fails to allocate required memory.
FOUNDATION_EXPORT NSExceptionName const NSMallocException;

/// Name of an exception that occurs when a remote object is accessed from a thread that should not access it.
FOUNDATION_EXPORT NSExceptionName const NSObjectInaccessibleException;
/// Name of an exception that occurs when the remote side of the object is no longer available.
FOUNDATION_EXPORT NSExceptionName const NSObjectNotAvailableException;
/// Name of an exception that occurs when an internal assertion fails for a destination.
FOUNDATION_EXPORT NSExceptionName const NSDestinationInvalidException;

/// Name of an exception that occurs when a port operation times out.
FOUNDATION_EXPORT NSExceptionName const NSPortTimeoutException;
/// Name of an exception that occurs when the send port of a connection has become invalid.
FOUNDATION_EXPORT NSExceptionName const NSInvalidSendPortException;
/// Name of an exception that occurs when the receive port of a connection has become invalid.
FOUNDATION_EXPORT NSExceptionName const NSInvalidReceivePortException;
/// Name of an exception that occurs when an error occurs while sending a message through a port.
FOUNDATION_EXPORT NSExceptionName const NSPortSendException;
/// Name of an exception that occurs when an error occurs while receiving a message through a port.
FOUNDATION_EXPORT NSExceptionName const NSPortReceiveException;

/// Name of an obsolete exception.
FOUNDATION_EXPORT NSExceptionName const NSOldStyleException;

/// Name of an exception that occurs when there is an inconsistency in an archive.
FOUNDATION_EXPORT NSExceptionName const NSInconsistentArchiveException;

/* **************	Exception object	***************/

#if __OBJC2__
__attribute__((__objc_exception__))
#endif

/// An object that represents a special condition that interrupts the normal flow of program execution.
@interface NSException : NSObject <NSCopying, NSSecureCoding> {
    @private
    NSString		*name;
    NSString		*reason;
    NSDictionary	*userInfo;
    id			reserved;
}

/// Creates and returns an exception object with the specified name, reason, and user info dictionary.
+ (NSException *)exceptionWithName:(NSExceptionName)name reason:(nullable NSString *)reason userInfo:(nullable NSDictionary *)userInfo;

/// Initializes and returns a newly allocated exception object.
- (instancetype)initWithName:(NSExceptionName)aName reason:(nullable NSString *)aReason userInfo:(nullable NSDictionary *)aUserInfo NS_DESIGNATED_INITIALIZER;

/// A string used to uniquely identify the receiver.
@property (readonly, copy) NSExceptionName name;

/// A human-readable message string summarizing the reason for the exception.
@property (nullable, readonly, copy) NSString *reason;

/// A dictionary containing application-specific data pertaining to the receiver.
@property (nullable, readonly, copy) NSDictionary *userInfo;

/// An array of return addresses from the call stack when the exception was first raised.
@property (readonly, copy) NSArray<NSNumber *> *callStackReturnAddresses API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// An array of strings describing the call stack backtrace at the point the exception was first raised.
@property (readonly, copy) NSArray<NSString *> *callStackSymbols API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Raises the receiver, causing program flow to jump to the local exception handler.
- (void)raise;

@end

@interface NSException (NSExceptionRaisingConveniences)

/// Creates and raises an exception with the specified name, reason format string, and arguments.
+ (void)raise:(NSExceptionName)name format:(NSString *)format, ... NS_FORMAT_FUNCTION(2,3);

/// Creates and raises an exception with the specified name, reason format string, and `va_list` of arguments.
+ (void)raise:(NSExceptionName)name format:(NSString *)format arguments:(va_list)argList NS_FORMAT_FUNCTION(2,0);

@end


/// Marks the start of the exception-handling domain.
///
/// The `NS_DURING` macro marks the start of the exception-handling domain for a section of code.
/// The ``NS_HANDLER`` macro marks the end of the domain. Within the exception-handling domain you
/// can raise an exception, giving the local exception handler (or lower exception handlers) a chance
/// to handle it.
#define NS_DURING		@try {
/// Marks the end of the exception-handling domain and the start of the local exception handler.
///
/// The `NS_HANDLER` macro marks end of a section of code that is an exception-handling domain while at the
/// same time marking the beginning of a section of code that is a local exception handler for that domain.
/// The ``NS_DURING`` macro marks the beginning of the exception-handling domain; the ``NS_ENDHANDLER``
/// marks the end of the local exception handler. If an exception is raised in the exception-handling domain,
/// the local exception handler is first given the chance to handle the exception before lower-level handlers
/// are given a chance.
#define NS_HANDLER		} @catch (NSException *localException) {
/// Marks the end of the local exception handler.
///
/// The `NS_ENDHANDLER` marks the end of a section of code that is a local exception handler. The
/// ``NS_HANDLER`` macro marks the beginning of this section. If an exception is raised in the exception
/// handling domain marked off by the ``NS_DURING`` and ``NS_HANDLER``, the local exception handler
/// (if specified) is given a chance to handle the exception.
#define NS_ENDHANDLER		}
/// Permits program control to exit from an exception-handling domain with a value of a specified type.
///
/// The `NS_VALUERETURN` macro returns program control to the caller out of the exception-handling
/// domain---that is, a section of code between the ``NS_DURING`` and ``NS_HANDLER`` macros that might
/// raise an exception. The specified value (of the specified type) is returned to the caller. The
/// standard `return` statement does not work as expected in the exception-handling domain.
///
/// - Parameters:
///   - v: A value to preserve beyond the exception-handling domain.
///   - t: The type of the value specified in `v`.
#define NS_VALUERETURN(v,t)	return (v)
/// Permits program control to exit from an exception-handling domain.
///
/// The `NS_VOIDRETURN` macro returns program control to the caller out of the exception-handling
/// domain---that is, a section of code between the ``NS_DURING`` and ``NS_HANDLER`` macros that might
/// raise an exception. The standard `return` statement does not work as expected in the exception-handling
/// domain.
#define NS_VOIDRETURN		return


/// The type for uncaught exception handler functions.
typedef void NSUncaughtExceptionHandler(NSException *exception);

/// Returns the top-level error handler.
FOUNDATION_EXPORT NSUncaughtExceptionHandler * _Nullable NSGetUncaughtExceptionHandler(void);
/// Changes the top-level error handler.
FOUNDATION_EXPORT void NSSetUncaughtExceptionHandler(NSUncaughtExceptionHandler * _Nullable);


#if __clang__
#define __PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wformat-extra-args\"")

#define __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS _Pragma("clang diagnostic pop")
#else
#define __PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS
#define __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS
#endif

@class NSAssertionHandler;

#if (defined(__STDC_VERSION__) && (199901L <= __STDC_VERSION__)) || (defined(__cplusplus) && (201103L <= __cplusplus))

#if !defined(NS_BLOCK_ASSERTIONS)

/// Generates an assertion if a given condition is false.
///
/// The `NSAssert` macro evaluates the condition and serves as a front end to the assertion handler.
///
/// Each thread has its own assertion handler, which is an object of class `NSAssertionHandler`.
/// When invoked, an assertion handler prints an error message that includes the method and class
/// names (or the function name). It then raises an `NSInternalInconsistencyException` exception.
/// If `condition` evaluates to false, the macro invokes
/// ``NSAssertionHandler/handleFailureInMethod:object:file:lineNumber:description:`` on the
/// assertion handler for the current thread, passing `desc` as the description string.
///
/// This macro should be used only within Objective-C methods.
///
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined or the
/// `ENABLE_NS_ASSERTIONS` Xcode build setting is disabled.
///
/// > Important: Do not call functions with side effects in the `condition` parameter of this macro.
/// > The `condition` parameter is not evaluated when assertions are disabled, so if you call
/// > functions with side effects, those functions may never get called when you build the project
/// > in a non-debug configuration.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: An `NSString` object that contains a `printf`-style string containing an error
///     message describing the failure condition and placeholders for the arguments.
///   - ...: A comma-separated list of arguments to substitute into `desc`.
#if !defined(_NSAssertBody)
#define NSAssert(condition, desc, ...)	\
    do {				\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
	if (__builtin_expect(!(condition), 0)) {		\
	    [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd \
		object:self file:@(__FILE_NAME__) \
	    	lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
	}				\
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
    } while(0)
#endif

/// Generates an assertion if the given condition is false.
///
/// The `NSCAssert` macro evaluates the condition and serves as a front end to the assertion handler.
/// This macro should be used only within C functions.
///
/// Each thread has its own assertion handler, which is an object of class `NSAssertionHandler`.
/// When invoked, an assertion handler prints an error message that includes method and class names
/// (or the function name). It then raises an `NSInternalInconsistencyException` exception.
///
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// > Important: Do not call functions with side effects in the `condition` parameter of this macro.
/// > The `condition` parameter is not evaluated when assertions are disabled, so if you call
/// > functions with side effects, those functions may never get called when you build the project
/// > in a non-debug configuration.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: A `printf`-style format string that describes the failure condition.
///   - ...: A comma-separated list of arguments to substitute into `desc`.
#if !defined(_NSCAssertBody)
#define NSCAssert(condition, desc, ...) \
    do {				\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
	if (__builtin_expect(!(condition), 0)) {		\
	    [[NSAssertionHandler currentHandler] handleFailureInFunction:(NSString * _Nonnull)@(__PRETTY_FUNCTION__) \
		file:@(__FILE_NAME__) \
	    	lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
	}				\
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
    } while(0)
#endif

#else // NS_BLOCK_ASSERTIONS defined

/// Generates an assertion if a given condition is false.
#if !defined(_NSAssertBody)
#define NSAssert(condition, desc, ...) do {} while (0)
#endif

/// Generates an assertion if the given condition is false.
#if !defined(_NSCAssertBody)
#define NSCAssert(condition, desc, ...) do {} while (0)
#endif

#endif

#if !defined(_NSAssertBody)
/// Generates an assertion if a given condition is false, with one format argument.
///
/// This macro is a legacy variant of ``NSAssert`` that accepts exactly one substitution argument.
/// Prefer using ``NSAssert`` with variadic arguments instead.
///
/// This macro should be used only within Objective-C methods.
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: An `NSString` object that contains a `printf`-style string with a placeholder for one argument.
///   - arg1: An argument to be inserted, in place, into `desc`.
#define NSAssert1(condition, desc, arg1) NSAssert((condition), (desc), (arg1))
/// Generates an assertion if a given condition is false, with two format arguments.
///
/// This macro is a legacy variant of ``NSAssert`` that accepts exactly two substitution arguments.
/// Prefer using ``NSAssert`` with variadic arguments instead.
///
/// This macro should be used only within Objective-C methods.
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: An `NSString` object that contains a `printf`-style string with placeholders for two arguments.
///   - arg1: An argument to be inserted, in place, into `desc`.
///   - arg2: An argument to be inserted, in place, into `desc`.
#define NSAssert2(condition, desc, arg1, arg2) NSAssert((condition), (desc), (arg1), (arg2))
/// Generates an assertion if a given condition is false, with three format arguments.
///
/// This macro is a legacy variant of ``NSAssert`` that accepts exactly three substitution arguments.
/// Prefer using ``NSAssert`` with variadic arguments instead.
///
/// This macro should be used only within Objective-C methods.
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: An `NSString` object that contains a `printf`-style string with placeholders for three arguments.
///   - arg1: An argument to be inserted, in place, into `desc`.
///   - arg2: An argument to be inserted, in place, into `desc`.
///   - arg3: An argument to be inserted, in place, into `desc`.
#define NSAssert3(condition, desc, arg1, arg2, arg3) NSAssert((condition), (desc), (arg1), (arg2), (arg3))
/// Generates an assertion if a given condition is false, with four format arguments.
///
/// This macro is a legacy variant of ``NSAssert`` that accepts exactly four substitution arguments.
/// Prefer using ``NSAssert`` with variadic arguments instead.
///
/// This macro should be used only within Objective-C methods.
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: An `NSString` object that contains a `printf`-style string with placeholders for four arguments.
///   - arg1: An argument to be inserted, in place, into `desc`.
///   - arg2: An argument to be inserted, in place, into `desc`.
///   - arg3: An argument to be inserted, in place, into `desc`.
///   - arg4: An argument to be inserted, in place, into `desc`.
#define NSAssert4(condition, desc, arg1, arg2, arg3, arg4) NSAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4))
/// Generates an assertion if a given condition is false, with five format arguments.
///
/// This macro is a legacy variant of ``NSAssert`` that accepts exactly five substitution arguments.
/// Prefer using ``NSAssert`` with variadic arguments instead.
///
/// This macro should be used only within Objective-C methods.
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: An `NSString` object that contains a `printf`-style string with placeholders for five arguments.
///   - arg1: An argument to be inserted, in place, into `desc`.
///   - arg2: An argument to be inserted, in place, into `desc`.
///   - arg3: An argument to be inserted, in place, into `desc`.
///   - arg4: An argument to be inserted, in place, into `desc`.
///   - arg5: An argument to be inserted, in place, into `desc`.
#define NSAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5) NSAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5))
/// Validates the specified parameter in an Objective-C method.
///
/// This macro validates a parameter for an Objective-C method. Simply provide the parameter as
/// the `condition` argument. The macro evaluates the parameter and, if it is false, it logs an
/// error message that includes the parameter and then raises an
/// `NSInternalInconsistencyException` exception.
///
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// > Important: Do not call functions with side effects in the `condition` parameter of this macro.
/// > The `condition` parameter is not evaluated when assertions are disabled, so if you call
/// > functions with side effects, those functions may never get called when you build the project
/// > in a non-debug configuration.
///
/// - Parameter condition: An expression that evaluates to true or false.
#define NSParameterAssert(condition) NSAssert((condition), @"Invalid parameter not satisfying: %@", @#condition)
#endif

#if !defined(_NSCAssertBody)
/// Generates an assertion if a given condition is false, with one format argument.
///
/// This macro is a legacy variant of ``NSCAssert`` that accepts exactly one substitution argument.
/// Prefer using ``NSCAssert`` with variadic arguments instead.
///
/// This macro should be used only within C functions.
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: A `printf`-style format string that describes the failure condition.
///   - arg1: An argument to be inserted, in place, into `desc`.
#define NSCAssert1(condition, desc, arg1) NSCAssert((condition), (desc), (arg1))
/// Generates an assertion if a given condition is false, with two format arguments.
///
/// This macro is a legacy variant of ``NSCAssert`` that accepts exactly two substitution arguments.
/// Prefer using ``NSCAssert`` with variadic arguments instead.
///
/// This macro should be used only within C functions.
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: A `printf`-style format string that describes the failure condition.
///   - arg1: An argument to be inserted, in place, into `desc`.
///   - arg2: An argument to be inserted, in place, into `desc`.
#define NSCAssert2(condition, desc, arg1, arg2) NSCAssert((condition), (desc), (arg1), (arg2))
/// Generates an assertion if a given condition is false, with three format arguments.
///
/// This macro is a legacy variant of ``NSCAssert`` that accepts exactly three substitution arguments.
/// Prefer using ``NSCAssert`` with variadic arguments instead.
///
/// This macro should be used only within C functions.
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: A `printf`-style format string that describes the failure condition.
///   - arg1: An argument to be inserted, in place, into `desc`.
///   - arg2: An argument to be inserted, in place, into `desc`.
///   - arg3: An argument to be inserted, in place, into `desc`.
#define NSCAssert3(condition, desc, arg1, arg2, arg3) NSCAssert((condition), (desc), (arg1), (arg2), (arg3))
/// Generates an assertion if a given condition is false, with four format arguments.
///
/// This macro is a legacy variant of ``NSCAssert`` that accepts exactly four substitution arguments.
/// Prefer using ``NSCAssert`` with variadic arguments instead.
///
/// This macro should be used only within C functions.
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: A `printf`-style format string that describes the failure condition.
///   - arg1: An argument to be inserted, in place, into `desc`.
///   - arg2: An argument to be inserted, in place, into `desc`.
///   - arg3: An argument to be inserted, in place, into `desc`.
///   - arg4: An argument to be inserted, in place, into `desc`.
#define NSCAssert4(condition, desc, arg1, arg2, arg3, arg4) NSCAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4))
/// Generates an assertion if a given condition is false, with five format arguments.
///
/// This macro is a legacy variant of ``NSCAssert`` that accepts exactly five substitution arguments.
/// Prefer using ``NSCAssert`` with variadic arguments instead.
///
/// This macro should be used only within C functions.
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// - Parameters:
///   - condition: An expression that evaluates to true or false.
///   - desc: A `printf`-style format string that describes the failure condition.
///   - arg1: An argument to be inserted, in place, into `desc`.
///   - arg2: An argument to be inserted, in place, into `desc`.
///   - arg3: An argument to be inserted, in place, into `desc`.
///   - arg4: An argument to be inserted, in place, into `desc`.
///   - arg5: An argument to be inserted, in place, into `desc`.
#define NSCAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5) NSCAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5))
/// Evaluates the specified parameter in a C function.
///
/// This macro validates a parameter for a C function. Simply provide the parameter as the
/// `condition` argument. The macro evaluates the parameter and, if the parameter evaluates to
/// false, logs an error message that includes the parameter and then raises an
/// `NSInternalInconsistencyException` exception.
///
/// Assertions are disabled if the preprocessor macro `NS_BLOCK_ASSERTIONS` is defined.
///
/// > Important: Do not call functions with side effects in the `condition` parameter of this macro.
/// > The `condition` parameter is not evaluated when assertions are disabled, so if you call
/// > functions with side effects, those functions may never get called when you build the project
/// > in a non-debug configuration.
///
/// - Parameter condition: An expression that evaluates to true or false.
#define NSCParameterAssert(condition) NSCAssert((condition), @"Invalid parameter not satisfying: %@", @#condition)
#endif

#endif


/* Non-vararg implementation of asserts (ignore) */
#if !defined(NS_BLOCK_ASSERTIONS)
#if !defined(_NSAssertBody)
#define _NSAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    do {						\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
	if (!(condition)) {				\
            NSString *__assert_file__ = [NSString stringWithUTF8String:__FILE__]; \
            __assert_file__ = __assert_file__ ? __assert_file__ : @"<Unknown File>"; \
	    [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd object:self file:__assert_file__ \
	    	lineNumber:__LINE__ description:(desc), (arg1), (arg2), (arg3), (arg4), (arg5)];	\
	}						\
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
    } while(0)
#endif
#if !defined(_NSCAssertBody)
#define _NSCAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    do {						\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
	if (!(condition)) {				\
            NSString *__assert_fn__ = [NSString stringWithUTF8String:__PRETTY_FUNCTION__]; \
            __assert_fn__ = __assert_fn__ ? __assert_fn__ : @"<Unknown Function>"; \
            NSString *__assert_file__ = [NSString stringWithUTF8String:__FILE__]; \
            __assert_file__ = __assert_file__ ? __assert_file__ : @"<Unknown File>"; \
	    [[NSAssertionHandler currentHandler] handleFailureInFunction:__assert_fn__ file:__assert_file__ \
	    	lineNumber:__LINE__ description:(desc), (arg1), (arg2), (arg3), (arg4), (arg5)];	\
	}						\
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
    } while(0)
#endif
#else
#if !defined(_NSAssertBody)
#define _NSAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)
#endif
#if !defined(_NSCAssertBody)
#define _NSCAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)
#endif
#endif


/*
 * Asserts to use in Objective-C method bodies
 */

#if !defined(NSAssert)
/// Generates an assertion if a given condition is false, with five format arguments.
#define NSAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5)) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

/// Generates an assertion if a given condition is false, with four format arguments.
#define NSAssert4(condition, desc, arg1, arg2, arg3, arg4)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

/// Generates an assertion if a given condition is false, with three format arguments.
#define NSAssert3(condition, desc, arg1, arg2, arg3)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

/// Generates an assertion if a given condition is false, with two format arguments.
#define NSAssert2(condition, desc, arg1, arg2)		\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), (arg1), (arg2), 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

/// Generates an assertion if a given condition is false, with one format argument.
#define NSAssert1(condition, desc, arg1)		\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), (arg1), 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

/// Generates an assertion if a given condition is false.
#define NSAssert(condition, desc)			\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), (desc), 0, 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS
#endif

/// Validates the specified parameter in an Objective-C method.
#if !defined(NSParameterAssert)
#define NSParameterAssert(condition)			\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSAssertBody((condition), @"Invalid parameter not satisfying: %s", #condition, 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS
#endif


#if !defined(NSCAssert)
/// Generates an assertion if the given condition is false, with five format arguments.
#define NSCAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5)) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

/// Generates an assertion if the given condition is false, with four format arguments.
#define NSCAssert4(condition, desc, arg1, arg2, arg3, arg4)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

/// Generates an assertion if the given condition is false, with three format arguments.
#define NSCAssert3(condition, desc, arg1, arg2, arg3)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

/// Generates an assertion if the given condition is false, with two format arguments.
#define NSCAssert2(condition, desc, arg1, arg2)	\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), (arg1), (arg2), 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

/// Generates an assertion if the given condition is false, with one format argument.
#define NSCAssert1(condition, desc, arg1)		\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), (arg1), 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS

/// Generates an assertion if the given condition is false.
#define NSCAssert(condition, desc)			\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), (desc), 0, 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS
#endif

/// Evaluates the specified parameter in a C function.
#if !defined(NSCParameterAssert)
#define NSCParameterAssert(condition)			\
	__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
    _NSCAssertBody((condition), @"Invalid parameter not satisfying: %s", #condition, 0, 0, 0, 0) \
        __PRAGMA_POP_NO_EXTRA_ARG_WARNINGS
#endif


FOUNDATION_EXPORT NSString * const NSAssertionHandlerKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// An object that logs an assertion to the console.
///
/// `NSAssertionHandler` objects are automatically created to handle false assertions. Assertion macros, such as `NSAssert` and `NSCAssert`, are used to evaluate a condition, and if the condition evaluates to false, the macros pass a string to an `NSAssertionHandler` object describing the failure. Each thread has its own `NSAssertionHandler` object. When invoked, an assertion handler prints an error message that includes the method and class (or function) containing the assertion and raises an `NSInternalInconsistencyException`.
///
/// You create assertions only using the assertion macros—you rarely need to invoke `NSAssertionHandler` methods directly. The macros for use inside methods and functions send ``handleFailureInMethod:object:file:lineNumber:description:`` and ``handleFailureInFunction:file:lineNumber:description:`` messages respectively to the current assertion handler. The assertion handler for the current thread is obtained using the ``current`` class method. See <doc:nsassertionhandlerkey> if you need to customize the behavior of ``NSAssertionHandler``.
@interface NSAssertionHandler : NSObject

/// Returns the `NSAssertionHandler` object associated with the current thread.
///
/// If no assertion handler is associated with the current thread, this method creates one and assigns it to the thread.
@property (class, readonly, strong) NSAssertionHandler *currentHandler;

- (void)handleFailureInMethod:(SEL)selector object:(id)object file:(NSString *)fileName lineNumber:(NSInteger)line description:(nullable NSString *)format,... NS_FORMAT_FUNCTION(5,6);

- (void)handleFailureInFunction:(NSString *)functionName file:(NSString *)fileName lineNumber:(NSInteger)line description:(nullable NSString *)format,... NS_FORMAT_FUNCTION(4,5);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
