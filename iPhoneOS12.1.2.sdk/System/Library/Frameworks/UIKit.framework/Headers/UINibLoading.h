#if USE_UIKIT_PUBLIC_HEADERS || !__has_include(<UIKitCore/UINibLoading.h>)
//
//  UINibLoading.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * UINibOptionsKey NS_TYPED_ENUM;

UIKIT_EXTERN UINibOptionsKey const UINibExternalObjects NS_AVAILABLE_IOS(3_0);

@interface NSBundle(UINibLoadingAdditions)
- (nullable NSArray *)loadNibNamed:(NSString *)name owner:(nullable id)owner options:(nullable NSDictionary<UINibOptionsKey, id> *)options;
@end

@interface NSObject(UINibLoadingAdditions)
- (void)awakeFromNib NS_REQUIRES_SUPER;
- (void)prepareForInterfaceBuilder NS_AVAILABLE_IOS(8_0);
@end

UIKIT_EXTERN NSString * const UINibProxiedObjectsKey NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UINibLoading.h>
#endif
