//
//  UITraitCollection.h
//  UIKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDevice.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UITouch.h>

/*! A trait collection encapsulates the system traits of an interface's environment. */
NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(8_0) @interface UITraitCollection : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (BOOL)containsTraitsInCollection:(nullable UITraitCollection *)trait;

/*! Returns a trait collection by merging the traits in `traitCollections`. The last trait along any given
 axis (e.g. interface usage) will supercede any others. */
+ (UITraitCollection *)traitCollectionWithTraitsFromCollections:(NSArray<UITraitCollection *> *)traitCollections;


+ (UITraitCollection *)traitCollectionWithUserInterfaceIdiom:(UIUserInterfaceIdiom)idiom;
@property (nonatomic, readonly) UIUserInterfaceIdiom userInterfaceIdiom; // unspecified: UIUserInterfaceIdiomUnspecified

+ (UITraitCollection *)traitCollectionWithDisplayScale:(CGFloat)scale;
@property (nonatomic, readonly) CGFloat displayScale; // unspecified: 0.0

+ (UITraitCollection *)traitCollectionWithHorizontalSizeClass:(UIUserInterfaceSizeClass)horizontalSizeClass;
@property (nonatomic, readonly) UIUserInterfaceSizeClass horizontalSizeClass; // unspecified: UIUserInterfaceSizeClassUnspecified

+ (UITraitCollection *)traitCollectionWithVerticalSizeClass:(UIUserInterfaceSizeClass)verticalSizeClass;
@property (nonatomic, readonly) UIUserInterfaceSizeClass verticalSizeClass; // unspecified: UIUserInterfaceSizeClassUnspecified

+ (UITraitCollection *)traitCollectionWithForceTouchCapability:(UIForceTouchCapability)capability NS_AVAILABLE_IOS(9_0);
@property (nonatomic, readonly) UIForceTouchCapability forceTouchCapability NS_AVAILABLE_IOS(9_0); // unspecified: UIForceTouchCapabilityUnknown

@end

/*! Trait environments expose a trait collection that describes their environment. */
@protocol UITraitEnvironment <NSObject>
@property (nonatomic, readonly) UITraitCollection *traitCollection NS_AVAILABLE_IOS(8_0);

/*! To be overridden as needed to provide custom behavior when the environment's traits change. */
- (void)traitCollectionDidChange:(nullable UITraitCollection *)previousTraitCollection NS_AVAILABLE_IOS(8_0);
@end

NS_ASSUME_NONNULL_END
