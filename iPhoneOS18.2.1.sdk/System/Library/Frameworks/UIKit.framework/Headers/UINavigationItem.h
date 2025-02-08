#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UINavigationItem.h>)
//
//  UINavigationItem.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIBarButtonItem.h>

@class UISearchController, UINavigationBarAppearance, UIDocumentProperties, UIDeferredMenuElement;
@class UINavigationItem;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UINavigationItemLargeTitleDisplayMode) {
    /// Automatically use the large out-of-line title based on the state of the previous item in the navigation bar. An item with largeTitleDisplayMode=Automatic will show or hide the large title based on the request of the previous navigation item. If the first item pushed is set to Automatic, then it will show the large title if the navigation bar has prefersLargeTitles=YES.
    UINavigationItemLargeTitleDisplayModeAutomatic,
    /// Always use a larger title when this item is topmost.
    UINavigationItemLargeTitleDisplayModeAlways,
    /// Never use a larger title when this item is topmost.
    UINavigationItemLargeTitleDisplayModeNever,
    /// Always use a large title when this item is topmost. If there is a back button present, this will revert to `Always`. Leading & center items will move to the overflow menu if present.
    UINavigationItemLargeTitleDisplayModeInline API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos),
} NS_SWIFT_NAME(UINavigationItem.LargeTitleDisplayMode) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UINavigationItemBackButtonDisplayMode) {
    /// Default mode, uses an appropriate title, followed by a generic title (typically 'Back'), then no title.
    UINavigationItemBackButtonDisplayModeDefault = 0,
    /// Generic titles only. Ignores .title and .backButtonTitle (but *not* .backBarButtonItem.title).
    UINavigationItemBackButtonDisplayModeGeneric = 1,
    /// Don't use a title, just the back button indicator image.
    UINavigationItemBackButtonDisplayModeMinimal = 2,
} NS_SWIFT_NAME(UINavigationItem.BackButtonDisplayMode) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UINavigationItemSearchBarPlacement) {
    /// The navigation bar will choose a placement for the search bar that is appropriate for the current layout
    UINavigationItemSearchBarPlacementAutomatic,
    /// The navigation bar will place the search bar inline with other content, on the trailing edge.
    UINavigationItemSearchBarPlacementInline,
    /// The navigation bar will place the search bar vertically stacked with other content.
    UINavigationItemSearchBarPlacementStacked,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

typedef NS_ENUM(NSInteger, UINavigationItemStyle) {
    /// Traditional navigation bar behavior. Center items are placed in the overflow menu.
    UINavigationItemStyleNavigator,
    /// A style designed for use as a browser. Title is leading aligned, center items are displayed. Typically used with history-based navigation.
    UINavigationItemStyleBrowser,
    /// A style designed for use as an editor. The back button will always present as chevron-only, title is leading aligned, center items are displayed. Typically used without navigation.
    UINavigationItemStyleEditor,
} NS_SWIFT_NAME(UINavigationItem.ItemStyle) API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UINavigationItemRenameDelegate <NSObject>

/// This method is called when renaming has ended. The title on the navigation item has already been changed when this method is called but
/// clients can make further adjustments to it when necessary.
- (void)navigationItem:(UINavigationItem *)navigationItem didEndRenamingWithTitle:(NSString *)title;

@optional

/// Controls whether the rename action is supported for the given navigation item. For example this method is called when the navigation bar's
/// document menu is shown to validate if the rename action should be part of that menu.
- (BOOL)navigationItemShouldBeginRenaming:(UINavigationItem *)navigationItem;

/// Called when we begin renaming. Implementing this method allows for customizing the initial text that will show up in the text field as well as the
/// selected range of that text.
- (NSString *)navigationItem:(UINavigationItem *)navigationItem willBeginRenamingWithSuggestedTitle:(NSString *)title selectedRange:(inout NSRange *)selectedRange;

/// This method can be used to prevent renaming from happening. However there are cases (e.g. when a new navigation item is pushed on the navigation
/// bar) where this method will not be called and instead navigationItem:didEndRenamingWithTitle: is called right away. Clients are therefore expected to
/// handle titles in navigationItem:didEndRenamingWithTitle: for which they would return NO from navigationItem:shouldEndRenamingWithTitle:.
- (BOOL)navigationItem:(UINavigationItem *)navigationItem shouldEndRenamingWithTitle:(NSString *)title;

@end


UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UINavigationItem : NSObject <NSCoding>

- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Title when topmost on the stack. default is nil
@property (nonatomic, readwrite, copy, nullable) NSString *title;
/// Custom view to use in lieu of a title. May be sized horizontally. Only used when item is topmost on the stack.
@property (nonatomic, readwrite, strong, nullable) UIView *titleView;
/// Explanatory text to display above the navigation bar buttons.
@property (nonatomic, readwrite, copy, nullable) NSString *prompt API_UNAVAILABLE(tvos);

/// Bar button item to use for the back button when this item is the navigation bar's backItem.
@property (nonatomic, readwrite, strong, nullable) UIBarButtonItem *backBarButtonItem API_UNAVAILABLE(tvos);
/// Title to use when this item is the navigation bar's backItem. Default is nil. backBarButtonItem takes precedence if both are specified.
@property (nonatomic, readwrite, copy, nullable) NSString *backButtonTitle API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos);
/// If YES, this navigation item will hide the back button when it's on top of the stack.
@property (nonatomic, readwrite, assign) BOOL hidesBackButton API_UNAVAILABLE(tvos);
- (void)setHidesBackButton:(BOOL)hidesBackButton animated:(BOOL)animated API_UNAVAILABLE(tvos);
/// Controls how the back button sources its title.
@property (nonatomic, readwrite, assign) UINavigationItemBackButtonDisplayMode backButtonDisplayMode API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/// Replaces the back action for the navigation bar. if a back button is naturally present, this replaces only its action, otherwise a back button will be synthesized with the image or title from the action.
@property (nonatomic, readwrite, copy, nullable) UIAction *backAction API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// When non-nil, UIKit will generate suggestedActions and call this block to generate a menu that is displayed from the title.
@property (nonatomic, readwrite, copy, nullable) UIMenu *_Nullable (^titleMenuProvider)(NSArray<UIMenuElement *> *suggestedActions) API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// When non-nil, enables the UINavigationBar to respond to the rename: action by providing an inline UI.
/// Setting this property to nil while a rename operation is in progress will cancel the operation immediately.
@property (nonatomic, readwrite, weak) id<UINavigationItemRenameDelegate> renameDelegate API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// When non-nil, UIKit will use the metadata provided to generate additional controls displayed from the title.
@property (nonatomic, readwrite, strong, nullable) UIDocumentProperties *documentProperties API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/* Use these properties to set multiple items in a navigation bar.
 The older single properties (leftBarButtonItem and rightBarButtonItem) now refer to
 the first item in the respective array of items.
 
 NOTE: You'll achieve the best results if you use either the singular properties or
 the plural properties consistently and don't try to mix them.
 
 leftBarButtonItems are placed in the navigation bar left to right with the first
 item in the list at the left outside edge and left aligned.
 rightBarButtonItems are placed right to left with the first item in the list at
 the right outside edge and right aligned.
 */
@property (nonatomic, readwrite, copy, nullable) NSArray<UIBarButtonItem *> *leftBarButtonItems API_AVAILABLE(ios(5.0));
@property (nonatomic, readwrite, copy, nullable) NSArray<UIBarButtonItem *> *rightBarButtonItems API_AVAILABLE(ios(5.0));
- (void)setLeftBarButtonItems:(nullable NSArray<UIBarButtonItem *> *)items animated:(BOOL)animated API_AVAILABLE(ios(5.0));
- (void)setRightBarButtonItems:(nullable NSArray<UIBarButtonItem *> *)items animated:(BOOL)animated API_AVAILABLE(ios(5.0));

/* By default, the leftItemsSupplementBackButton property is NO. In this case,
 the back button is not drawn and the left item or items replace it. If you
 would like the left items to appear in addition to the back button (as opposed to instead of it)
 set leftItemsSupplementBackButton to YES.
 */
@property (nonatomic, readwrite, assign) BOOL leftItemsSupplementBackButton API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);

/// Some navigation items want to display a custom left or right item when they're on top of the stack. A custom left item replaces the regular back button unless you set leftItemsSupplementBackButton to YES
@property(nonatomic, readwrite, strong, nullable) UIBarButtonItem *leftBarButtonItem;
@property(nonatomic, readwrite, strong, nullable) UIBarButtonItem *rightBarButtonItem;
- (void)setLeftBarButtonItem:(nullable UIBarButtonItem *)item animated:(BOOL)animated;
- (void)setRightBarButtonItem:(nullable UIBarButtonItem *)item animated:(BOOL)animated;

/// Setting a non-nil customizationIdentifier enables customization and UIKit will automatically save & restore customizations based on this identifier. The identifier must be unique within the scope of the application.
@property (nonatomic, readwrite, copy  , nullable) NSString *customizationIdentifier API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// UIBarButtonItemGroups to be displayed in the leading section of the navigation bar. Items set via this method will replace items set via .leftBarButtonItem or .leftBarButtonItems.
@property (nonatomic, readwrite, copy) NSArray<UIBarButtonItemGroup *> *leadingItemGroups API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// Customizable UIBarButtonItemGroups that will be placed in the center region when the navigation bar is the browser or editor modes. In navigation mode, these items will be placed in the overflow.
@property (nonatomic, readwrite, copy) NSArray<UIBarButtonItemGroup *> *centerItemGroups API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// UIBarButtonItemGroups to be displayed in the trailing section of the navigation bar. Items set via this method will replace items set via .rightBarButtonItem or .rightBarButtonItems.
@property (nonatomic, readwrite, copy) NSArray<UIBarButtonItemGroup *> *trailingItemGroups API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);
/// Set a group of items to be placed on the trailing edge of the bar, past the overflow & search items (if present). If you wish to have more than 1 item, it is HIGHLY recommended to assign a representative item to the group to avoid overflowing the bar as this group cannot move to the overflow.
@property (nonatomic, readwrite, strong, nullable) UIBarButtonItemGroup *pinnedTrailingGroup API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// Additional items to add to the overflow menu. Setting this property to a non-nil value will force the overflow button to appear, regardless of if you provide any content in the element's callback. Items returned are displayed directly in the presented menu.
@property (nonatomic, readwrite, strong, nullable) UIDeferredMenuElement *additionalOverflowItems API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);
/// If the overflow button for this item is currently present, then this will return a non-nil item that can be used as a presentation source (e.g. for popovers). Otherwise it will return nil.
@property (nonatomic, readonly, strong, nullable) id<UIPopoverPresentationControllerSourceItem> overflowPresentationSource API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// When UINavigationBar.prefersLargeTitles=YES, this property controls when the larger out-of-line title is displayed. If prefersLargeTitles=NO, this property has no effect. The default value is Automatic.
@property (nonatomic, readwrite, assign) UINavigationItemLargeTitleDisplayMode largeTitleDisplayMode API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

/// Controls how content defined by this item is laid out in the navigation bar.
@property (nonatomic, readwrite, assign) UINavigationItemStyle style API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// A view controller that will be shown inside of a navigation controller can assign a UISearchController to this property to display the search controller’s search bar in its containing navigation controller’s navigation bar.
@property (nonatomic, readwrite, strong, nullable) UISearchController *searchController API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

/// If this property is true (the default), the searchController’s search bar will hide as the user scrolls in the top view controller’s scroll view. If false, the search bar will remain visible and pinned underneath the navigation bar.
/// Not appicable and ignored for UINavigationItemSearchBarPlacementInline
@property (nonatomic, readwrite, assign) BOOL hidesSearchBarWhenScrolling API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

/// The preferred search bar placement, when a search controller is assigned to this item.
@property (nonatomic, readwrite, assign) UINavigationItemSearchBarPlacement preferredSearchBarPlacement API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// The realized placement. Only valid if a search controller has been assigned to this item.
@property (nonatomic, readonly, assign)  UINavigationItemSearchBarPlacement searchBarPlacement API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

///  When set and this item is topmost, overrides the hosting navigation bar's standardAppearance. See UINavigationBar.standardAppearance for further details.
@property (nonatomic, readwrite, copy, nullable) UINavigationBarAppearance *standardAppearance API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
///  When set and this item is topmost, overrides the hosting navigation bar's compactAppearance. See UINavigationBar.compactAppearance for further details.
@property (nonatomic, readwrite, copy, nullable) UINavigationBarAppearance *compactAppearance API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);
///  When set and this item is topmost, overrides the hosting navigation bar's scrollEdgeAppearance. See UINavigationBar.scrollEdgeAppearance for further details.
@property (nonatomic, readwrite, copy, nullable) UINavigationBarAppearance *scrollEdgeAppearance API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);
///  When set and this item is topmost, overrides the hosting navigation bar's compactScrollEdgeAppearance. See UINavigationBar.h for further details.
@property (nonatomic, readwrite, copy, nullable) UINavigationBarAppearance *compactScrollEdgeAppearance API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UINavigationItem.h>
#endif
