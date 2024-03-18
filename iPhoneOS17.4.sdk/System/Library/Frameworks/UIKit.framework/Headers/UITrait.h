#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITrait.h>)
//
//  UITrait.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)


API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0)) NS_SWIFT_UI_ACTOR
@protocol UITraitDefinition

@optional

/// A unique identifier string for the trait (reverse-DNS format recommended).
/// Allows the trait to be encoded/decoded, and to map both a Swift and Objective-C trait to the same data.
@property (nonatomic, class, readonly) NSString *identifier;

/// A short human-readable name for the trait, e.g. for printing and debugging output.
/// By default, the trait's class name is used when not implemented.
@property (nonatomic, class, readonly) NSString *name;

/// Whether the trait is used to resolve dynamic colors (or images), and changes to the trait should
/// automatically trigger views using dynamic colors/images to update their appearance. Default is NO.
@property (nonatomic, class, readonly) BOOL affectsColorAppearance;

@end
typedef Class<UITraitDefinition> UITrait API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0));

API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0)) NS_SWIFT_UI_ACTOR
@protocol UICGFloatTraitDefinition <UITraitDefinition>
/// The default value for this trait in a trait collection when no value has been set.
@property (nonatomic, class, readonly) CGFloat defaultValue;
@end
typedef Class<UICGFloatTraitDefinition> UICGFloatTrait API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0));

API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0)) NS_SWIFT_UI_ACTOR
@protocol UINSIntegerTraitDefinition <UITraitDefinition>
/// The default value for this trait in a trait collection when no value has been set.
@property (nonatomic, class, readonly) NSInteger defaultValue;
@end
typedef Class<UINSIntegerTraitDefinition> UINSIntegerTrait API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0));

API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0)) NS_SWIFT_UI_ACTOR
@protocol UIObjectTraitDefinition <UITraitDefinition>
/// The default value for this trait in a trait collection when no value has been set.
@property (nonatomic, class, readonly, nullable) __kindof id<NSObject> defaultValue;
@end
typedef Class<UIObjectTraitDefinition> UIObjectTrait API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0));


UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitUserInterfaceIdiom : NSObject <UINSIntegerTraitDefinition> // UIUserInterfaceIdiom
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitUserInterfaceStyle : NSObject <UINSIntegerTraitDefinition> // UIUserInterfaceStyle
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitLayoutDirection : NSObject <UINSIntegerTraitDefinition> // UITraitEnvironmentLayoutDirection
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitDisplayScale : NSObject <UICGFloatTraitDefinition> // CGFloat
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitHorizontalSizeClass : NSObject <UINSIntegerTraitDefinition> // UIUserInterfaceSizeClass
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitVerticalSizeClass : NSObject <UINSIntegerTraitDefinition> // UIUserInterfaceSizeClass
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitForceTouchCapability : NSObject <UINSIntegerTraitDefinition> // UIForceTouchCapability
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitPreferredContentSizeCategory : NSObject <UIObjectTraitDefinition> // UIContentSizeCategory (NSString *)
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitDisplayGamut : NSObject <UINSIntegerTraitDefinition> // UIDisplayGamut
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface UITraitAccessibilityContrast : NSObject <UINSIntegerTraitDefinition> // UIAccessibilityContrast
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface UITraitUserInterfaceLevel : NSObject <UINSIntegerTraitDefinition> // UIUserInterfaceLevel
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitLegibilityWeight : NSObject <UINSIntegerTraitDefinition> // UILegibilityWeight
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitActiveAppearance : NSObject <UINSIntegerTraitDefinition> // UIUserInterfaceActiveAppearance
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitToolbarItemPresentationSize : NSObject <UINSIntegerTraitDefinition> // UINSToolbarItemPresentationSize
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitImageDynamicRange : NSObject <UINSIntegerTraitDefinition> // UIImageDynamicRange
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0))
@interface UITraitTypesettingLanguage : NSObject <UIObjectTraitDefinition> // NSString
@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface UITraitSceneCaptureState : NSObject <UINSIntegerTraitDefinition> // UISceneCaptureState
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITrait.h>
#endif
