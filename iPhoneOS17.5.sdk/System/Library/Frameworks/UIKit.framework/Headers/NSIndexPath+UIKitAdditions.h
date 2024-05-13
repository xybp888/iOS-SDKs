#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSIndexPath+UIKitAdditions.h>)
//
//  NSIndexPath+UIKitAdditions.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// This category provides convenience methods to make it easier to use an NSIndexPath to represent a section and row/item, for use with UITableView and UICollectionView.
@interface NSIndexPath (UIKitAdditions)

+ (instancetype)indexPathForRow:(NSInteger)row inSection:(NSInteger)section;
+ (instancetype)indexPathForItem:(NSInteger)item inSection:(NSInteger)section API_AVAILABLE(ios(6.0));

// Returns the index at position 0.
@property (nonatomic, readonly) NSInteger section;

// Returns the index at position 1.
@property (nonatomic, readonly) NSInteger row;
// Returns the index at position 1 if it exists, otherwise returns NSNotFound.
@property (nonatomic, readonly) NSInteger item API_AVAILABLE(ios(6.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/NSIndexPath+UIKitAdditions.h>
#endif
