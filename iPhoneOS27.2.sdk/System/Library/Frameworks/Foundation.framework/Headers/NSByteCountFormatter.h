/*	NSByteCountFormatter.h
	Copyright (c) 2012-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#import <Foundation/NSMeasurement.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Specifies the units appropriate for the formatter to display. Specifying any units explicitly causes just those units to be used in showing the number.
typedef NS_OPTIONS(NSUInteger, NSByteCountFormatterUnits) {
    /// This causes default units appropriate for the platform to be used. This is the default.
    NSByteCountFormatterUseDefault      = 0,
    /// Displays bytes in the formatter content.
    NSByteCountFormatterUseBytes        = 1UL << 0,
    /// Displays kilobytes in the formatter content.
    NSByteCountFormatterUseKB           = 1UL << 1,
    /// Displays megabytes in the formatter content.
    NSByteCountFormatterUseMB           = 1UL << 2,
    /// Displays gigabytes in the formatter content.
    NSByteCountFormatterUseGB           = 1UL << 3,
    /// Displays terabytes in the formatter content.
    NSByteCountFormatterUseTB           = 1UL << 4,
    /// Displays petabytes in the formatter content.
    NSByteCountFormatterUsePB           = 1UL << 5,
    /// Displays exabytes in the formatter content.
    NSByteCountFormatterUseEB           = 1UL << 6,
    /// Displays zettabytes in the formatter content.
    NSByteCountFormatterUseZB           = 1UL << 7,
    /// Displays yottabytes in the formatter content.
    NSByteCountFormatterUseYBOrHigher   = 0x0FFUL << 8,
    /// Can use any unit in the formatter content.
    NSByteCountFormatterUseAll          = 0x0FFFFUL
};

/// Specifies display of file or storage byte counts. The display style is platform specific.
typedef NS_ENUM(NSInteger, NSByteCountFormatterCountStyle) {
    /// Specifies display of file byte counts. The actual behavior for this is platform-specific; in macOS 10.8, this uses the decimal style, but that may change over time.
    NSByteCountFormatterCountStyleFile   = 0,
    /// Specifies display of memory byte counts. The actual behavior for this is platform-specific; in macOS 10.8, this uses the binary style, but that may change over time.
    NSByteCountFormatterCountStyleMemory = 1,
    /// Causes 1000 bytes to be shown as 1 KB. It is better to use `NSByteCountFormatterCountStyleFile` or `NSByteCountFormatterCountStyleMemory` in most cases.
    NSByteCountFormatterCountStyleDecimal = 2,
    /// Causes 1024 bytes to be shown as 1 KB. It is better to use `NSByteCountFormatterCountStyleFile` or `NSByteCountFormatterCountStyleMemory` in most cases.
    NSByteCountFormatterCountStyleBinary  = 3
};


/// A formatter that converts a byte count value into a localized description that is formatted with the appropriate byte modifier (KB, MB, GB and so on).
///
/// > Tip:
/// > In Swift, you can use ``ByteCountFormatStyle`` or ``Measurement/FormatStyle/ByteCount`` rather than ``ByteCountFormatter``. The ``FormatStyle`` API offers a declarative idiom for customizing the formatting of various types. Also, Foundation caches identical ``FormatStyle`` instances, so you don't need to pass them around your app, or risk wasting memory with duplicate formatters.
API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0))
@interface NSByteCountFormatter : NSFormatter

/// Converts a byte count into the specified string format without creating an `NSNumber` object.
///
/// If you need to specify options other than `countStyle`, create an instance of `NSByteCountFormatter` first.
///
/// @param byteCount The byte count.
/// @param countStyle The formatter style. See `NSByteCountFormatterCountStyle` for possible values.
/// @return A string containing the formatted `byteCount` value.
+ (NSString *)stringFromByteCount:(long long)byteCount countStyle:(NSByteCountFormatterCountStyle)countStyle;

/// Converts a byte count into a string without creating an `NSNumber` object.
///
/// This is a convenience method on `stringForObjectValue:`.
///
/// @param byteCount The byte count.
/// @return A string containing the formatted `byteCount` value.
- (NSString *)stringFromByteCount:(long long)byteCount;

/// Formats the value of the given measurement using the given `countStyle`.
///
/// Throws an exception if the given measurement's unit does not belong to the `NSUnitInformationStorage` dimension.
+ (NSString *)stringFromMeasurement:(NSMeasurement<NSUnitInformationStorage *> *)measurement countStyle:(NSByteCountFormatterCountStyle)countStyle API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/// Formats the value of the given measurement using the receiver's `countStyle`.
///
/// Converts the measurement to the units allowed by the receiver's `allowedUnits` before formatting; depending on the value of the measurement, this may result in a string which implies an approximate value (e.g. if the measurement is too large to represent in `allowedUnits`, like `1e20 YB` expressed in `NSByteCountFormatterUseBytes`).
///
/// Throws an exception if the given measurement's unit does not belong to the `NSUnitInformationStorage` dimension.
- (NSString *)stringFromMeasurement:(NSMeasurement<NSUnitInformationStorage *> *)measurement API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/// Formats `obj` as a byte count (if `obj` is an `NSNumber`) or specific byte measurement (if `obj` is an `NSMeasurement`) using the receiver's settings.
///
/// Returns `nil` if `obj` is not of the correct class (`NSNumber` or `NSMeasurement`).
/// Throws an exception if `obj` is an `NSMeasurement` whose unit does not belong to the `NSUnitInformationStorage` dimension.
- (nullable NSString *)stringForObjectValue:(nullable id)obj;

/// Specify the units that can be used in the output.
///
/// If the value is `NSByteCountFormatterUseDefault`, the formatter uses platform-appropriate settings; otherwise only the specified units are used.
///
/// > Note: ZB and YB cannot be covered by the range of possible values, but you can still choose to use these units to get fractional display ("0.0035 ZB" for instance).
@property NSByteCountFormatterUnits allowedUnits;

/// Specify the number of bytes to be used for kilobytes.
///
/// The default setting is `NSByteCountFormatterCountStyleFile`, which is the system specific value for file and storage sizes.
@property NSByteCountFormatterCountStyle countStyle;

/// Determines whether to allow more natural display of some values.
///
/// Displays a more natural display of some values, such as zero, where it may be displayed as "Zero KB", ignoring all other flags or options (with the exception of `NSByteCountFormatterUseBytes`, which would generate "Zero bytes"). The result is appropriate for standalone output.
///
/// Special handling of certain values such as zero is especially important in some languages, so it's highly recommended that this property be left in its default state.
///
/// Default value is `YES`.
@property BOOL allowsNonnumericFormatting;

/// Determines whether to include the units in the resulting formatted string.
///
/// If set to `YES` and `includesCount` is set to `NO`, no count is displayed. For example, a value of 723 KB is formatted as "KB".
///
/// You can set this property and `includesCount` individually to get both parts, separately. Note that putting them together yourself via string concatenation may be incorrect for some locales.
///
/// The default value is `YES`.
@property BOOL includesUnit;

/// Determines whether to include the count in the resulting formatted string.
///
/// If set to `YES` and `includesUnit` is set to `NO`, no unit is displayed. For example, a value of 723 KB is formatted as "723".
///
/// You can set this property and `includesUnit` individually to get both parts, separately. Note that putting them together yourself via string concatenation may be incorrect for some locales.
///
/// The default value is `YES`.
@property BOOL includesCount;

/// Determines whether to include the number of bytes after the formatted string.
///
/// Setting this value to `YES` causes the byte count to be displayed parenthetically (localized as appropriate), for instance "723 KB (722,842 bytes)". This will happen only if needed, that is, the first part is already not showing the exact byte count.
///
/// If `includesUnit` or `includesCount` are `NO`, then this setting has no effect.
///
/// Default value is `NO`.
@property BOOL includesActualByteCount;

/// Determines the display style of the size representation.
///
/// The "adaptive" algorithm is platform specific and uses a different number of fraction digits based on the magnitude (in OS X v10.8: 0 fraction digits for bytes and KB; 1 fraction digits for MB; 2 for GB and above). Otherwise the result always tries to show at least three significant digits, introducing fraction digits as necessary.
///
/// Default is `YES`.
@property (getter=isAdaptive) BOOL adaptive;

/// Determines whether to zero pad fraction digits so a consistent number of characters is displayed in a representation.
///
/// Displaying values using zero pad fraction digits causes a consistent number of fraction digits to be displayed, causing updating displays to remain more stable. For instance, if the adaptive algorithm is used, this option formats 1.19 and 1.2 GB as "1.19 GB" and "1.20 GB", respectively, while without the option the latter would be displayed as "1.2 GB".
///
/// Default value is `NO`.
@property BOOL zeroPadsFractionDigits;

/// Specify the formatting context for the formatted string.
///
/// The default value is `NSFormattingContextUnknown`.
@property NSFormattingContext formattingContext API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
