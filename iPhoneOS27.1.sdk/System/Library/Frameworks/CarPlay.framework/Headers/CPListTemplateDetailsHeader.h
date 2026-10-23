//
//  CPListTemplateDetailsHeader.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <CarPlay/CPButton.h>
#import <CarPlay/CPPlaybackConfiguration.h>
#import <CarPlay/CPTemplate.h>
#import <CarPlay/CPThumbnailImage.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A header for list templates that displays rich media content with action buttons.
 * 
 * CPListTemplateDetailsHeader provides a prominent header section for list templates
 * that includes a thumbnail image, title, subtitle, and configurable action buttons.
 * This component is ideal for displaying media items, content details, or featured
 * items at the top of a list template in CarPlay applications.
 *
 * The header supports:
 * - A thumbnail image with overlay and progress indicators
 * - Primary title and subtitle text
 * - Up to a maximum number of action buttons for user interaction
 * - Automatic layout and styling appropriate for CarPlay interfaces
 *
 * @discussion This class is designed specifically for CarPlay templates and follows
 *             CarPlay design guidelines for typography, spacing, and interaction patterns.
 *             The header automatically adapts to different screen sizes and orientations
 *             while maintaining optimal readability and touch target sizes.
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPListTemplateDetailsHeader: NSObject <NSSecureCoding, CPPlayableItem>

/**
 * Creates a new details header with the specified content and action buttons.
 *
 * @param thumbnail The thumbnail image to display in the header. This image may include
 *                  overlays, progress indicators, or other visual enhancements.
 * @param title The primary title text to display. Pass nil to hide the title.
 * @param subtitle The secondary subtitle text to display below the title. Pass nil to hide the subtitle.
 * @param actionButton An array of CPButton objects representing user actions. The number of buttons
 *                     is limited by maximumActionButtonCount. Additional buttons beyond the limit
 *                     will be ignored.
 *
 * @return A newly initialized CPListTemplateDetailsHeader instance.
 *
 * @discussion The thumbnail parameter is required and should not be nil. The title and subtitle
 *             are optional but at least one should be provided for meaningful content display.
 *             Action buttons will be displayed in the order provided in the array.
 */
- (instancetype)initWithThumbnail:(CPThumbnailImage *)thumbnail
                            title:(nullable NSString *)title
                         subtitle:(nullable NSString *)subtitle
                    actionButtons:(NSArray <CPButton *> *)actionButton API_AVAILABLE(ios(26.4));

/**
 * Creates a new details header with the specified content and action buttons.
 *
 * @param thumbnail The thumbnail image to display in the header. This image may include
 *                  overlays, progress indicators, or other visual enhancements.
 * @param title The primary title text to display. Pass nil to hide the title.
 * @param subtitle The secondary subtitle text to display below the title. Pass nil to hide the subtitle.
 * @param bodyVariants The multiline metadata text to display below the subtitle. Pass nil to hide the metadata.
 * @param actionButton An array of CPButton objects representing user actions. The number of buttons
 *                     is limited by maximumActionButtonCount. Additional buttons beyond the limit
 *                     will be ignored.
 *
 * @return A newly initialized CPListTemplateDetailsHeader instance.
 *
 * @discussion The thumbnail parameter is required and should not be nil. The title and subtitle
 *             are optional but at least one should be provided for meaningful content display.
 *             Action buttons will be displayed in the order provided in the array.
 */
- (instancetype)initWithThumbnail:(CPThumbnailImage *)thumbnail
                            title:(nullable NSString *)title
                         subtitle:(nullable NSString *)subtitle
                     bodyVariants:(NSArray<NSAttributedString *> *)bodyVariants
                    actionButtons:(NSArray<CPButton *> *)actionButtons API_AVAILABLE(ios(26.4));

/**
 * The thumbnail image displayed in the header.
 *
 * This property represents the primary visual content of the header. The thumbnail
 * may include image overlays, playback progress indicators, or sports overlays
 * depending on the content type.
 */
@property (nonatomic, strong) CPThumbnailImage *thumbnail API_AVAILABLE(ios(26.4));

/**
 * The primary title text displayed in the header.
 *
 * The title appears prominently below or alongside the thumbnail image.
 * Use this property for the main content identifier such as song titles,
 * show names, or primary content descriptions.
 */
@property (nonatomic, copy, nullable) NSString *title API_AVAILABLE(ios(26.4));

/**
 * The secondary subtitle text displayed below the title.
 *
 * The subtitle provides additional context or metadata about the content,
 * such as artist names, episode descriptions, or secondary information.
 * This text is displayed with reduced visual prominence compared to the title.
 */
@property (nonatomic, copy, nullable) NSString *subtitle API_AVAILABLE(ios(26.4));

/**
 * An optional array of strings, ordered from most to least preferred.
 *
 * The variant strings should be provided as localized, displayable content.
 * The system will select the first variant that fits the available space.
 */
@property (nonatomic, copy) NSArray<NSAttributedString *> *bodyVariants API_AVAILABLE(ios(26.4));

/**
 * An array of action buttons displayed in the header.
 *
 * These buttons provide user interaction capabilities such as play/pause,
 * favorite/unfavorite, share, or other content-specific actions. The buttons
 * are displayed horizontally and are limited by maximumActionButtonCount.
 *
 * @discussion Buttons should have clear, concise titles or recognizable icons.
 *             The order of buttons in the array determines their display order
 *             from leading to trailing in the interface.
 */
@property (nonatomic, copy) NSArray <CPButton *> *actionButtons API_AVAILABLE(ios(26.4));

/**
 * A Boolean value that determines whether to use a custom background style.
 *
 * When set to YES, the header will use a custom background style derived from
 * the thumbnail image. This creates an adaptive background that automatically
 * generates light and dark mode variants.
 *
 * When set to NO (default), the header uses the standard CarPlay background.
 *
 * @discussion The custom background style uses perceptually-aware color transformation
 *             to create visually harmonious backgrounds that adapt to the user's
 *             interface style preference.
 */
@property (nonatomic, assign, getter=wantsAdaptiveBackgroundStyle) BOOL adaptiveBackgroundStyle API_AVAILABLE(ios(26.4));

/**
 * The maximum number of action buttons that can be displayed in the header.
 *
 * This class property defines the upper limit for action buttons to ensure
 * proper layout and usability within the CarPlay interface constraints.
 * Any buttons beyond this limit in the actionButtons array will be ignored.
 *
 * @return The maximum number of action buttons supported by this header type.
 */
@property (nonatomic, readonly, class) NSInteger maximumActionButtonCount API_AVAILABLE(ios(26.4));


@property (nonatomic, readonly, class) CGSize maximumActionButtonSize API_AVAILABLE(ios(26.4));

@end


NS_ASSUME_NONNULL_END
