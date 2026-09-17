/*    NSListFormatter.h
      Copyright (c) 2018-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/NSFormatter.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that provides locale-correct formatting of a list of items using the appropriate separator and conjunction.
///
/// The list formatter isn't aware of the context where the formatted string will be used and doesn't provide capitalization customization of the list items. The formatted result may not be grammatically correct if placed in a sentence, and it should only be used in a standalone manner.
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
@interface NSListFormatter : NSFormatter
#if !__OBJC2__
{
@private
    void * _listFormatter;
    NSLocale *_locale;
    NSFormatter *_itemFormatter;
}
#endif // !__OBJC2__

/// Specifies the locale to format the items.
///
/// Defaults to `autoupdatingCurrentLocale`. Also resets to `autoupdatingCurrentLocale` on assignment of `nil`.
@property (null_resettable, copy) NSLocale *locale;

/// Specifies how each object should be formatted.
///
/// If not set, the object is formatted using its instance method in the following order: `descriptionWithLocale:`, `localizedDescription`, and `description`.
@property (nullable, copy) NSFormatter *itemFormatter;

/// Returns a string constructed from an array of strings using the list format specific to the current locale.
///
/// It is recommended to join only disjointed strings that are ready to display in a bullet-point list. Sentences, phrases with punctuations, and appositions may not work well when joined together.
+ (NSString *)localizedStringByJoiningStrings:(NSArray<NSString *> *)strings;

/// Returns a string constructed from an array using the locale-aware format.
///
/// Each item is formatted using the `itemFormatter`. If the `itemFormatter` does not apply to a particular item,
/// the method will fall back to the item's `descriptionWithLocale:` or `localizedDescription` if implemented, or `description` if not.
///
/// Returns `nil` if `items` is `nil` or if the list formatter cannot generate a string representation for all items in the array.
- (nullable NSString *)stringFromItems:(NSArray *)items;

/// Creates a formatted string for an array of items.
///
/// The list formatter uses `itemFormatter` to format each item in the array. If `itemFormatter` doesn't apply to a particular item, the list formatter falls back to the item's `description(withLocale:)` or `localizedDescription` if implemented. If those methods aren't implemented, the formatter uses `description` instead.
///
/// - Parameters:
///   - obj: An array of objects to format as a list.
/// - Returns: A formatted string representing the list of objects in an array. Returns `nil` if the formatter can't generate a description for all objects in the array, or if `obj` is `nil`.
- (nullable NSString *)stringForObjectValue:(nullable id)obj;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
