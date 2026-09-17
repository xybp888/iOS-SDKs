//
//  BEAccessibility.h
//  BrowserEngineKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <CoreVideo/CoreVideo.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BEAccessibilityPressedState) {
    BEAccessibilityPressedStateUndefined = 0,
    BEAccessibilityPressedStateFalse,
    BEAccessibilityPressedStateTrue,
    BEAccessibilityPressedStateMixed,
} BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

typedef NS_OPTIONS(NSUInteger, BEAccessibilityContainerType) {
    BEAccessibilityContainerTypeNone             = 0,
    BEAccessibilityContainerTypeLandmark         = 1 << 0,
    BEAccessibilityContainerTypeTable            = 1 << 1,
    BEAccessibilityContainerTypeList             = 1 << 2,
    BEAccessibilityContainerTypeFieldset         = 1 << 3,
    BEAccessibilityContainerTypeDialog           = 1 << 4,
    BEAccessibilityContainerTypeTree             = 1 << 5,
    BEAccessibilityContainerTypeFrame            = 1 << 6,
    BEAccessibilityContainerTypeArticle          = 1 << 7,
    BEAccessibilityContainerTypeSemanticGroup    = 1 << 8,
    BEAccessibilityContainerTypeScrollArea       = 1 << 9,
    BEAccessibilityContainerTypeAlert            = 1 << 10,
    BEAccessibilityContainerTypeDescriptionList  = 1 << 11,
} BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

typedef NS_ENUM(NSInteger, BEAccessibilityOrientation) {
    BEAccessibilityOrientationUnknown = 0,
    BEAccessibilityOrientationVertical,
    BEAccessibilityOrientationHorizontal
} BROWSERENGINE_ACCESSIBILITY_AVAILABILITY_27;

@interface NSObject (BEAccessibility)

/**
 * Represents the value of aria-current.
 * default: nil
 */
@property (nonatomic, strong, nullable) NSString *browserAccessibilityCurrentStatus BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * Represents the value of aria-sort.
 * default: nil
 */
@property (nonatomic, strong, nullable) NSString *browserAccessibilitySortDirection BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * Represents the value of aria-roledescription.
 * default: nil
 */
@property (nonatomic, strong, nullable) NSString *browserAccessibilityRoleDescription BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * Represents the value of aria-required.
 * default: false
 */
@property (nonatomic, assign) BOOL browserAccessibilityIsRequired BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * Represents the value of aria-pressed.
 * default: BEAccessibilityPressedStateUndefined
 */
@property (nonatomic, assign) BEAccessibilityPressedState browserAccessibilityPressedState BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * Represents whether the current element has native DOM focus.
 * default: false
 */
@property (nonatomic, assign) BOOL browserAccessibilityHasDOMFocus BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * An option set of the types that contain this element. For example, an object within a table cell
 * will return the Table container type.
 * default: BEAccessibilityContainerTypeNone
 */
@property (nonatomic, assign) BEAccessibilityContainerType browserAccessibilityContainerType BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Returns an range representing the selected text on the page.
 default: { NSNotFound, 0 }
 */
- (NSRange)browserAccessibilitySelectedTextRange BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Set the selected text range.
 @param range The range to make selected.
 */
- (void)browserAccessibilitySetSelectedTextRange:(NSRange)range BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Returns the value of this element in the given range.
 @param range The range of this element's value to return.
 */
- (NSString *)browserAccessibilityValueInRange:(NSRange)range BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Returns the attributed value of this element in the given range.
 @param range The range of this element's value to return.
 */
- (NSAttributedString *)browserAccessibilityAttributedValueInRange:(NSRange)range BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Insert text at the current cursor position.
 @param text The text to insert.
 */
- (void)browserAccessibilityInsertTextAtCursor:(NSString *)text NS_SWIFT_NAME(browserAccessibilityInsertTextAtCursor(text:)) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Delete text at the current cursor position.
 @param numberOfCharacters Number of characters to delete.
 */
- (void)browserAccessibilityDeleteTextAtCursor:(NSInteger)numberOfCharacters NS_SWIFT_NAME(browserAccessibilityDeleteTextAtCursor(numberOfCharacters:)) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract The text cursor position of the soft line end should be returned, starting from the current selection (or beginning if no selection).
 */
- (NSInteger)accessibilityLineEndPositionFromCurrentSelection BROWSERENGINE_ACCESSIBILITY_MARKER_AVAILABILITY;

/**
 @abstract The text cursor position of the soft line start should be returned, starting from the current selection (or beginning if no selection).
 */
- (NSInteger)accessibilityLineStartPositionFromCurrentSelection BROWSERENGINE_ACCESSIBILITY_MARKER_AVAILABILITY;

/**
 @abstract The text cursor range of the soft line should be returned depending on the position.
 @param position A text cursor position within a line of text.
 */
- (NSRange)accessibilityLineRangeForPosition:(NSInteger)position BROWSERENGINE_ACCESSIBILITY_MARKER_AVAILABILITY;

/**
 @abstract Represents the value of aria-keyshortcuts.
 default: nil
 */
@property (nonatomic, strong, nullable) NSString *browserAccessibilityKeyboardShortcuts BROWSERENGINE_ACCESSIBILITY_AVAILABILITY_27;

/**
 @abstract Represents the value of aria-details. Returns an array of objects.
 default: []
 */
@property (nonatomic, strong) NSArray<NSObject *> *browserAccessibilityDetailsElements BROWSERENGINE_ACCESSIBILITY_AVAILABILITY_27;

/**
 @abstract Represents the value of aria-orientation.
 default: BEAccessibilityOrientationUnknown
 */
@property (nonatomic, assign) BEAccessibilityOrientation browserAccessibilityOrientation BROWSERENGINE_ACCESSIBILITY_AVAILABILITY_27;

/**
 @abstract Returns the native pixel dimensions of the image represented by this element.
 @result An NSValue wrapping a CGSize, or nil if this element does not represent an image.
 */
- (nullable NSValue *)browserAccessibilityImageDataSize NS_REFINED_FOR_SWIFT BROWSERENGINE_ACCESSIBILITY_AVAILABILITY_27;

/**
 @abstract Returns image pixel data for this element as a CVPixelBuffer.

 @param attributes A dictionary of CVPixelBuffer attributes specifying the desired format and size.

   Supported keys:
     kCVPixelBufferPixelFormatTypeKey (NSNumber / OSType) — The desired pixel format,
       e.g. kCVPixelFormatType_32RGBA. Required.
     kCVPixelBufferWidthKey  (NSNumber) — Target image width in pixels. Absent means native width.
     kCVPixelBufferHeightKey (NSNumber) — Target image height in pixels. Absent means native height.

 @result A CVPixelBuffer containing the image pixel data, or NULL if this element does not
 represent an image or the requested pixel format is unsupported. The caller is responsible
 for releasing the returned pixel buffer.
 */
- (nullable CVPixelBufferRef)browserAccessibilityImageData:(NSDictionary *)attributes CF_RETURNS_RETAINED BROWSERENGINE_ACCESSIBILITY_AVAILABILITY_27;

@end

NS_ASSUME_NONNULL_END
