/*	NSByteOrder.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#import <CoreFoundation/CFByteOrder.h>

NS_HEADER_AUDIT_BEGIN(sendability)

/// Constants that indicate the byte order of the current architecture.
enum {
    /// The byte order is unknown.
    NS_UnknownByteOrder = CFByteOrderUnknown,
    /// The byte order is little-endian.
    NS_LittleEndian = CFByteOrderLittleEndian,
    /// The byte order is big-endian.
    NS_BigEndian = CFByteOrderBigEndian
};

/// Returns the endian format.
///
/// - Returns: The endian format, either `NS_LittleEndian` or `NS_BigEndian`.
NS_INLINE long NSHostByteOrder(void) {
    return CFByteOrderGetCurrent();
}

/// Swaps the bytes of a number.
///
/// Swaps the low-order and high-order bytes of `inv` and returns the resulting value.
///
/// - Parameter inv: The value whose bytes you want to swap.
/// - Returns: The byte-swapped value.
NS_INLINE unsigned short NSSwapShort(unsigned short inv) {
    return CFSwapInt16(inv);
}

/// Swaps the bytes of a number.
///
/// Swaps the bytes of `inv` and returns the resulting value. Bytes are swapped from each
/// low-order position to the corresponding high-order position and vice versa. For example,
/// if the bytes of `inv` are numbered from 1 to 4, this function swaps bytes 1 and 4, and
/// bytes 2 and 3.
///
/// - Parameter inv: The value whose bytes you want to swap.
/// - Returns: The byte-swapped value.
NS_INLINE unsigned int NSSwapInt(unsigned int inv) {
    return CFSwapInt32(inv);
}

/// Swaps the bytes of a number.
///
/// Swaps the bytes of `inv` and returns the resulting value. Bytes are swapped from each
/// low-order position to the corresponding high-order position and vice versa. For example,
/// if the bytes of `inv` are numbered from 1 to 4, this function swaps bytes 1 and 4, and
/// bytes 2 and 3.
///
/// - Parameter inv: The value whose bytes you want to swap.
/// - Returns: The byte-swapped value.
NS_INLINE unsigned long NSSwapLong(unsigned long inv) {
#if __LP64__
    return CFSwapInt64(inv);
#else
    return CFSwapInt32(inv);
#endif
}

/// Swaps the bytes of a number.
///
/// Swaps the bytes of `inv` and returns the resulting value. Bytes are swapped from each
/// low-order position to the corresponding high-order position and vice versa. For example,
/// if the bytes of `inv` are numbered from 1 to 8, this function swaps bytes 1 and 8, bytes
/// 2 and 7, bytes 3 and 6, and bytes 4 and 5.
///
/// - Parameter inv: The value whose bytes you want to swap.
/// - Returns: The byte-swapped value.
NS_INLINE unsigned long long NSSwapLongLong(unsigned long long inv) {
    return CFSwapInt64(inv);
}

/// Converts a big-endian `unsigned short` to the host's native byte order.
///
/// Converts the big-endian value in `x` to the current endian format and returns the
/// resulting value. If it is necessary to swap the bytes of `x`, this function calls
/// ``NSSwapShort(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned short NSSwapBigShortToHost(unsigned short x) {
    return CFSwapInt16BigToHost(x);
}

/// Converts a big-endian `unsigned int` to the host's native byte order.
///
/// Converts the big-endian value in `x` to the current endian format and returns the
/// resulting value. If it is necessary to swap the bytes of `x`, this function calls
/// ``NSSwapInt(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned int NSSwapBigIntToHost(unsigned int x) {
    return CFSwapInt32BigToHost(x);
}

/// Converts a big-endian `unsigned long` to the host's native byte order.
///
/// Converts the big-endian value in `x` to the current endian format and returns the
/// resulting value. If it is necessary to swap the bytes of `x`, this function calls
/// ``NSSwapLong(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned long NSSwapBigLongToHost(unsigned long x) {
#if __LP64__
    return CFSwapInt64BigToHost(x);
#else
    return CFSwapInt32BigToHost(x);
#endif
}

/// Converts a big-endian `unsigned long long` to the host's native byte order.
///
/// Converts the big-endian value in `x` to the current endian format and returns the
/// resulting value. If it is necessary to swap the bytes of `x`, this function calls
/// ``NSSwapLongLong(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned long long NSSwapBigLongLongToHost(unsigned long long x) {
    return CFSwapInt64BigToHost(x);
}

/// Converts an `unsigned short` from the host's native byte order to big-endian.
///
/// Converts the value in `x`, specified in the current endian format, to big-endian format
/// and returns the resulting value. If it is necessary to swap the bytes, this function calls
/// ``NSSwapShort(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned short NSSwapHostShortToBig(unsigned short x) {
    return CFSwapInt16HostToBig(x);
}

/// Converts an `unsigned int` from the host's native byte order to big-endian.
///
/// Converts the value in `x`, specified in the current endian format, to big-endian format
/// and returns the resulting value. If it is necessary to swap the bytes, this function calls
/// ``NSSwapInt(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned int NSSwapHostIntToBig(unsigned int x) {
    return CFSwapInt32HostToBig(x);
}

/// Converts an `unsigned long` from the host's native byte order to big-endian.
///
/// Converts the value in `x`, specified in the current endian format, to big-endian format
/// and returns the resulting value. If it is necessary to swap the bytes, this function calls
/// ``NSSwapLong(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned long NSSwapHostLongToBig(unsigned long x) {
#if __LP64__
    return CFSwapInt64HostToBig(x);
#else
    return CFSwapInt32HostToBig(x);
#endif
}

/// Converts an `unsigned long long` from the host's native byte order to big-endian.
///
/// Converts the value in `x`, specified in the current endian format, to big-endian format
/// and returns the resulting value. If it is necessary to swap the bytes, this function calls
/// ``NSSwapLongLong(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned long long NSSwapHostLongLongToBig(unsigned long long x) {
    return CFSwapInt64HostToBig(x);
}

/// Converts a little-endian `unsigned short` to the host's native byte order.
///
/// Converts the little-endian formatted value in `x` to the current endian format and
/// returns the resulting value. If it is necessary to swap the bytes of `x`, this function
/// calls ``NSSwapShort(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned short NSSwapLittleShortToHost(unsigned short x) {
    return CFSwapInt16LittleToHost(x);
}

/// Converts a little-endian `unsigned int` to the host's native byte order.
///
/// Converts the little-endian formatted value in `x` to the current endian format and
/// returns the resulting value. If it is necessary to swap the bytes, this function calls
/// ``NSSwapInt(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned int NSSwapLittleIntToHost(unsigned int x) {
    return CFSwapInt32LittleToHost(x);
}

/// Converts a little-endian `unsigned long` to the host's native byte order.
///
/// Converts the little-endian formatted value in `x` to the current endian format and
/// returns the resulting value. If it is necessary to swap the bytes of `x`, this function
/// calls ``NSSwapLong(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned long NSSwapLittleLongToHost(unsigned long x) {
#if __LP64__
    return CFSwapInt64LittleToHost(x);
#else
    return CFSwapInt32LittleToHost(x);
#endif
}

/// Converts a little-endian `unsigned long long` to the host's native byte order.
///
/// Converts the little-endian formatted value in `x` to the current endian format and
/// returns the resulting value. If it is necessary to swap the bytes, this function calls
/// ``NSSwapLongLong(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned long long NSSwapLittleLongLongToHost(unsigned long long x) {
    return CFSwapInt64LittleToHost(x);
}

/// Converts an `unsigned short` from the host's native byte order to little-endian.
///
/// Converts the value in `x`, specified in the current endian format, to little-endian
/// format and returns the resulting value. If it is necessary to swap the bytes, this
/// function calls ``NSSwapShort(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned short NSSwapHostShortToLittle(unsigned short x) {
    return CFSwapInt16HostToLittle(x);
}

/// Converts an `unsigned int` from the host's native byte order to little-endian.
///
/// Converts the value in `x`, specified in the current endian format, to little-endian
/// format and returns the resulting value. If it is necessary to swap the bytes, this
/// function calls ``NSSwapInt(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned int NSSwapHostIntToLittle(unsigned int x) {
    return CFSwapInt32HostToLittle(x);
}

/// Converts an `unsigned long` from the host's native byte order to little-endian.
///
/// Converts the value in `x`, specified in the current endian format, to little-endian
/// format and returns the resulting value. If it is necessary to swap the bytes, this
/// function calls ``NSSwapLong(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned long NSSwapHostLongToLittle(unsigned long x) {
#if __LP64__
    return CFSwapInt64HostToLittle(x);
#else
    return CFSwapInt32HostToLittle(x);
#endif
}

/// Converts an `unsigned long long` from the host's native byte order to little-endian.
///
/// Converts the value in `x`, specified in the current endian format, to little-endian
/// format and returns the resulting value. If it is necessary to swap the bytes, this
/// function calls ``NSSwapLongLong(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE unsigned long long NSSwapHostLongLongToLittle(unsigned long long x) {
    return CFSwapInt64HostToLittle(x);
}


/// A structure holding a swapped `float` value.
typedef struct NS_SWIFT_SENDABLE {unsigned int v;} NSSwappedFloat;
/// A structure holding a swapped `double` value.
typedef struct NS_SWIFT_SENDABLE {unsigned long long v;} NSSwappedDouble;

/// Performs a type conversion.
///
/// Converts the float value in `x` to a value whose bytes can be swapped. This function
/// does not actually swap the bytes of `x`. You should not need to call this function
/// directly.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE NSSwappedFloat NSConvertHostFloatToSwapped(float x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->sf;
}

/// Performs a type conversion.
///
/// Converts the value in `x` to a float value. This function does not actually swap the
/// bytes of `x`. You should not need to call this function directly.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE float NSConvertSwappedFloatToHost(NSSwappedFloat x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->number;
}

/// Performs a type conversion.
///
/// Converts the double value in `x` to a value whose bytes can be swapped. This function
/// does not actually swap the bytes of `x`. You should not need to call this function
/// directly.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE NSSwappedDouble NSConvertHostDoubleToSwapped(double x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->sd;
}

/// Performs a type conversion.
///
/// Converts the value in `x` to a double value. This function does not actually swap the
/// bytes of `x`. You should not need to call this function directly.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE double NSConvertSwappedDoubleToHost(NSSwappedDouble x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->number;
}

/// Swaps the bytes of a number.
///
/// Swaps the bytes of `x` and returns the resulting value. Bytes are swapped from each
/// low-order position to the corresponding high-order position and vice versa. For example,
/// if the bytes of `x` are numbered from 1 to 4, this function swaps bytes 1 and 4, and
/// bytes 2 and 3.
///
/// - Parameter x: The value whose bytes you want to swap.
/// - Returns: The byte-swapped value.
NS_INLINE NSSwappedFloat NSSwapFloat(NSSwappedFloat x) {
    x.v = NSSwapInt(x.v);
    return x;
}

/// Swaps the bytes of a number.
///
/// Swaps the bytes of `x` and returns the resulting value. Bytes are swapped from each
/// low-order position to the corresponding high-order position and vice versa. For example,
/// if the bytes of `x` are numbered from 1 to 8, this function swaps bytes 1 and 8, bytes
/// 2 and 7, bytes 3 and 6, and bytes 4 and 5.
///
/// - Parameter x: The value whose bytes you want to swap.
/// - Returns: The byte-swapped value.
NS_INLINE NSSwappedDouble NSSwapDouble(NSSwappedDouble x) {
    x.v = NSSwapLongLong(x.v);
    return x;
}

#if defined(__BIG_ENDIAN__)

/// Swaps the bytes of a number.
///
/// Converts the big-endian value in `x` to the current endian format and returns the
/// resulting value. If it is necessary to swap the bytes of `x`, this function calls
/// ``NSSwapDouble(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

/// Swaps the bytes of a number.
///
/// Converts the big-endian value in `x` to the current endian format and returns the
/// resulting value. If it is necessary to swap the bytes of `x`, this function calls
/// ``NSSwapFloat(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

/// Swaps the bytes of a number.
///
/// Converts the value in `x`, specified in the current endian format, to big-endian format
/// and returns the resulting value. If it is necessary to swap the bytes, this function calls
/// ``NSSwapDouble(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSConvertHostDoubleToSwapped(x);
}

/// Swaps the bytes of a number.
///
/// Converts the value in `x`, specified in the current endian format, to big-endian format
/// and returns the resulting value. If it is necessary to swap the bytes, this function calls
/// ``NSSwapFloat(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSConvertHostFloatToSwapped(x);
}

/// Swaps the bytes of a number.
///
/// Converts the little-endian formatted value in `x` to the current endian format and
/// returns the resulting value. If it is necessary to swap the bytes of `x`, this function
/// calls ``NSSwapDouble(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

/// Swaps the bytes of a number.
///
/// Converts the little-endian formatted value in `x` to the current endian format and
/// returns the resulting value. If it is necessary to swap the bytes of `x`, this function
/// calls ``NSSwapFloat(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}

/// Swaps the bytes of a number.
///
/// Converts the value in `x`, specified in the current endian format, to little-endian
/// format and returns the resulting value. If it is necessary to swap the bytes, this
/// function calls ``NSSwapDouble(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}

/// Swaps the bytes of a number.
///
/// Converts the value in `x`, specified in the current endian format, to little-endian
/// format and returns the resulting value. If it is necessary to swap the bytes, this
/// function calls ``NSSwapFloat(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

#elif defined(__LITTLE_ENDIAN__)

/// Swaps the bytes of a number.
///
/// Converts the big-endian value in `x` to the current endian format and returns the
/// resulting value. If it is necessary to swap the bytes of `x`, this function calls
/// ``NSSwapDouble(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

/// Swaps the bytes of a number.
///
/// Converts the big-endian value in `x` to the current endian format and returns the
/// resulting value. If it is necessary to swap the bytes of `x`, this function calls
/// ``NSSwapFloat(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}

/// Swaps the bytes of a number.
///
/// Converts the value in `x`, specified in the current endian format, to big-endian format
/// and returns the resulting value. If it is necessary to swap the bytes, this function calls
/// ``NSSwapDouble(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}

/// Swaps the bytes of a number.
///
/// Converts the value in `x`, specified in the current endian format, to big-endian format
/// and returns the resulting value. If it is necessary to swap the bytes, this function calls
/// ``NSSwapFloat(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

/// Swaps the bytes of a number.
///
/// Converts the little-endian formatted value in `x` to the current endian format and
/// returns the resulting value. If it is necessary to swap the bytes of `x`, this function
/// calls ``NSSwapDouble(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

/// Swaps the bytes of a number.
///
/// Converts the little-endian formatted value in `x` to the current endian format and
/// returns the resulting value. If it is necessary to swap the bytes of `x`, this function
/// calls ``NSSwapFloat(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

/// Swaps the bytes of a number.
///
/// Converts the value in `x`, specified in the current endian format, to little-endian
/// format and returns the resulting value. If it is necessary to swap the bytes, this
/// function calls ``NSSwapDouble(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSConvertHostDoubleToSwapped(x);
}

/// Swaps the bytes of a number.
///
/// Converts the value in `x`, specified in the current endian format, to little-endian
/// format and returns the resulting value. If it is necessary to swap the bytes, this
/// function calls ``NSSwapFloat(_:)`` to perform the swap.
///
/// - Parameter x: The value you want to convert.
/// - Returns: The converted value.
NS_INLINE NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSConvertHostFloatToSwapped(x);
}

#else
#error Do not know the endianess of this architecture
#endif

NS_HEADER_AUDIT_END(sendability)
