#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPhotoSearchSuggestion.h>)
//
//  UIPhotoSearchSuggestion.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInputSuggestion.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A class you use to handle a photo search suggestion
///
/// When the system detects text that could be used to search a user's photo library,
/// it provides a `UIPhotoSearchSuggestion` through the input suggestion system.
/// Your app can use the filter metadata (who, what, where, when) to construct queries
/// using the Photos framework.
///
/// You receive photo search suggestions through the
/// ``UITextFieldDelegate/textField(_:insertInputSuggestion:)`` or
/// ``UITextViewDelegate/textView(_:insertInputSuggestion:)`` delegate methods.
///
/// ## Example
///
/// ```swift
/// func textField(_ textField: UITextField,
///                insertInputSuggestion inputSuggestion: UIInputSuggestion) {
///     if let photoSuggestion = inputSuggestion as? UIPhotoSearchSuggestion {
///         performPhotoSearch(photoSuggestion)
///     }
/// }
/// ```
UIKIT_EXTERN API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(tvos, watchos, visionos)
@interface UIPhotoSearchSuggestion : UIInputSuggestion

- (instancetype)init NS_UNAVAILABLE;

/// People mentioned in the text that can be used to filter photos.
///
/// For example, if the user types "photos with John," this array might contain `@[@"John"]`.
@property (nonatomic, copy, readonly) NSArray<NSString *> *whoValues;

/// Subjects or topics mentioned in the text that can be used to filter photos.
///
/// For example, if the user types "photos of food," this array might contain `@[@"food"]`.
@property (nonatomic, copy, readonly) NSArray<NSString *> *whatValues;

/// Locations mentioned in the text that can be used to filter photos.
///
/// For example, if the user types "pictures from Paris," this array might contain `@[@"Paris"]`.
@property (nonatomic, copy, readonly) NSArray<NSString *> *whereValues;

/// Time periods mentioned in the text that can be used to filter photos.
///
/// For example, if the user types "photos from last summer," this array might
/// contain `@[@"last summer"]`.
@property (nonatomic, copy, readonly) NSArray<NSString *> *whenValues;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIPhotoSearchSuggestion.h>
#endif
