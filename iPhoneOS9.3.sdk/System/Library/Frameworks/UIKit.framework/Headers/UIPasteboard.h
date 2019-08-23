//
//  UIPasteboard.h
//  UIKit
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN NSString *const UIPasteboardNameGeneral __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIPasteboardNameFind __TVOS_PROHIBITED;

@class UIColor, UIImage;

NS_CLASS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED @interface UIPasteboard : NSObject
{
  @private
    NSString * __nullable _name;
}

+ (UIPasteboard *)generalPasteboard;
+ (nullable UIPasteboard *)pasteboardWithName:(NSString *)pasteboardName create:(BOOL)create;
+ (UIPasteboard *)pasteboardWithUniqueName;

@property(readonly,nonatomic) NSString *name;

+ (void)removePasteboardWithName:(NSString *)pasteboardName;

@property(getter=isPersistent,nonatomic) BOOL persistent;
@property(readonly,nonatomic) NSInteger changeCount;

// First item

- (NSArray<NSString *> *)pasteboardTypes;
- (BOOL)containsPasteboardTypes:(NSArray<NSString *> *)pasteboardTypes;
- (nullable NSData *)dataForPasteboardType:(NSString *)pasteboardType;

- (nullable id)valueForPasteboardType:(NSString *)pasteboardType;

- (void)setValue:(id)value forPasteboardType:(NSString *)pasteboardType;
- (void)setData:(NSData *)data forPasteboardType:(NSString *)pasteboardType;

// Multiple items

@property(readonly,nonatomic) NSInteger numberOfItems;
- (nullable NSArray *)pasteboardTypesForItemSet:(nullable NSIndexSet*)itemSet;

- (BOOL)containsPasteboardTypes:(NSArray<NSString *> *)pasteboardTypes inItemSet:(nullable NSIndexSet *)itemSet;
- (nullable NSIndexSet *)itemSetWithPasteboardTypes:(NSArray *)pasteboardTypes;
- (nullable NSArray *)valuesForPasteboardType:(NSString *)pasteboardType inItemSet:(nullable NSIndexSet *)itemSet;
- (nullable NSArray *)dataForPasteboardType:(NSString *)pasteboardType inItemSet:(nullable NSIndexSet *)itemSet;

// Direct access

@property(nonatomic,copy) NSArray *items;
- (void)addItems:(NSArray<NSDictionary<NSString *, id> *> *)items;

@end

// Notification

UIKIT_EXTERN NSString *const UIPasteboardChangedNotification __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIPasteboardChangedTypesAddedKey __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIPasteboardChangedTypesRemovedKey __TVOS_PROHIBITED;

UIKIT_EXTERN NSString *const UIPasteboardRemovedNotification __TVOS_PROHIBITED;

// Extensions

UIKIT_EXTERN NSArray<NSString *> *UIPasteboardTypeListString __TVOS_PROHIBITED;
UIKIT_EXTERN NSArray<NSString *> *UIPasteboardTypeListURL __TVOS_PROHIBITED;
UIKIT_EXTERN NSArray<NSString *> *UIPasteboardTypeListImage __TVOS_PROHIBITED;
UIKIT_EXTERN NSArray<NSString *> *UIPasteboardTypeListColor __TVOS_PROHIBITED;

@interface UIPasteboard(UIPasteboardDataExtensions)

@property(nullable,nonatomic,copy) NSString *string __TVOS_PROHIBITED;
@property(nullable,nonatomic,copy) NSArray<NSString *> *strings __TVOS_PROHIBITED;

@property(nullable,nonatomic,copy) NSURL *URL __TVOS_PROHIBITED;
@property(nullable,nonatomic,copy) NSArray<NSURL *> *URLs __TVOS_PROHIBITED;

@property(nullable,nonatomic,copy) UIImage *image __TVOS_PROHIBITED;
@property(nullable,nonatomic,copy) NSArray<UIImage *> *images __TVOS_PROHIBITED;

@property(nullable,nonatomic,copy) UIColor *color __TVOS_PROHIBITED;
@property(nullable,nonatomic,copy) NSArray<UIColor *> *colors __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
    
