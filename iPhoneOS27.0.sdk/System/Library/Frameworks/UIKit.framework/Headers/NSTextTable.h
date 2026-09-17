#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextTable.h>)
//
//  NSTextTable.h
//  Text Kit
//
//  Copyright (c) 2004-2025, Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UIKit/NSText.h>
#import <CoreFoundation/CFCGTypes.h>

@class NSTextTable;
@class NSLayoutManager;
@class NSTextContainer;
@class UIColor;


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* Values for NSTextBlockValueType */
typedef NS_ENUM(NSInteger, NSTextBlockValueType) {
    NSTextBlockValueTypeAbsolute = 0,    // Absolute value in points
    NSTextBlockValueTypePercentage = 1, // Percentage value (out of 100)
    
} API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0)) NS_SWIFT_NAME(NSTextBlock.ValueType);

/* Values for NSTextBlockDimension */
typedef NS_ENUM(NSInteger, NSTextBlockDimension) {
    NSTextBlockDimensionWidth = 0,
    NSTextBlockDimensionMinimumWidth = 1,
    NSTextBlockDimensionMaximumWidth = 2,
    NSTextBlockDimensionHeight = 4,
    NSTextBlockDimensionMinimumHeight = 5,
    NSTextBlockDimensionMaximumHeight = 6,
    
    
} API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0)) NS_SWIFT_NAME(NSTextBlock.Dimension);

/* Values for NSTextBlockLayer */
typedef NS_ENUM(NSInteger, NSTextBlockLayer) {
    NSTextBlockLayerPadding = -1,
    NSTextBlockLayerBorder  =  0,
    NSTextBlockLayerMargin  =  1,
    
} API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0)) NS_SWIFT_NAME(NSTextBlock.Layer);

/* Values for NSTextBlockVerticalAlignment */
typedef NS_ENUM(NSInteger, NSTextBlockVerticalAlignment) {
    NSTextBlockVerticalAlignmentTop = 0,
    NSTextBlockVerticalAlignmentMiddle = 1,
    NSTextBlockVerticalAlignmentBottom = 2,
    NSTextBlockVerticalAlignmentBaseline = 3,

} API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0)) NS_SWIFT_NAME(NSTextBlock.VerticalAlignment);

/* Values for NSTextTableLayoutAlgorithm */
typedef NS_ENUM(NSInteger, NSTextTableLayoutAlgorithm) {
    NSTextTableLayoutAlgorithmAutomatic = 0,
    NSTextTableLayoutAlgorithmFixed = 1,
    
} API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0))  NS_SWIFT_NAME(NSTextTable.LayoutAlgorithm);

/// An object that defines the size, spacing, and appearance of a block of text in an attributed string.
UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0))
@interface NSTextBlock : NSObject <NSSecureCoding, NSCopying>
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/* Content size */
- (void)setValue:(CGFloat)value type:(NSTextBlockValueType)type forDimension:(NSTextBlockDimension)dimension;
- (CGFloat)valueForDimension:(NSTextBlockDimension)dimension;
- (NSTextBlockValueType)valueTypeForDimension:(NSTextBlockDimension)dimension;

/* Convenience methods for content width in particular, using the above methods with dimension == NSTextBlockWidth */
- (void)setContentWidth:(CGFloat)contentWidth type:(NSTextBlockValueType)type;
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat contentWidth;
@property (readonly, NS_NONATOMIC_IOSONLY) NSTextBlockValueType contentWidthValueType;

/* Margin, border, and padding */
- (void)setWidth:(CGFloat)width type:(NSTextBlockValueType)type forLayer:(NSTextBlockLayer)layer;     // Convenience method sets all edges at once
- (void)setWidth:(CGFloat)width type:(NSTextBlockValueType)type forLayer:(NSTextBlockLayer)layer rectEdge:(CGRectEdge)rectEdge API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0));
- (CGFloat)widthForLayer:(NSTextBlockLayer)layer rectEdge:(CGRectEdge)rectEdge API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0));
- (NSTextBlockValueType)widthValueTypeForLayer:(NSTextBlockLayer)layer rectEdge:(CGRectEdge)rectEdge API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0));

/* Alignment */
@property (NS_NONATOMIC_IOSONLY) NSTextBlockVerticalAlignment verticalAlignment;

/* Colors */
@property (nullable, copy, NS_NONATOMIC_IOSONLY) UIColor *backgroundColor;
- (void)setBorderColor:(nullable UIColor *)color;        // Convenience method sets all edges at once
- (void)setBorderColor:(nullable UIColor *)borderColor rectEdge:(CGRectEdge)rectEdge API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0));
- (nullable UIColor *)borderColorForRectEdge:(CGRectEdge)rectEdge API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0));
@end

/// An object that represents a single cell in a text table.
UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0))
@interface NSTextTableBlock : NSTextBlock
- (instancetype)initWithTable:(NSTextTable *)table startingRow:(NSInteger)row rowSpan:(NSInteger)rowSpan startingColumn:(NSInteger)column columnSpan:(NSInteger)columnSpan NS_DESIGNATED_INITIALIZER;     // Designated initializer
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/* These methods determine the block's role in its enclosing table. */
@property (readonly, strong, NS_NONATOMIC_IOSONLY) NSTextTable * table;
@property (readonly, NS_NONATOMIC_IOSONLY) NSInteger startingRow;
@property (readonly, NS_NONATOMIC_IOSONLY) NSInteger rowSpan;
@property (readonly, NS_NONATOMIC_IOSONLY) NSInteger startingColumn;
@property (readonly, NS_NONATOMIC_IOSONLY) NSInteger columnSpan;

@end

/// An object that represents a table of rows and columns in an attributed string.
UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0))
@interface NSTextTable : NSTextBlock
/* These methods control the basic parameters of the table. */
@property (NS_NONATOMIC_IOSONLY) NSInteger numberOfColumns;
@property (NS_NONATOMIC_IOSONLY) NSTextTableLayoutAlgorithm layoutAlgorithm;
@property (NS_NONATOMIC_IOSONLY) BOOL collapsesBorders;
@property (NS_NONATOMIC_IOSONLY) BOOL hidesEmptyCells;
@end
NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextTable.h>
#endif
