//
//  INUIAddVoiceShortcutButton
//  IntentsUI
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, INUIAddVoiceShortcutButtonStyle) {
    INUIAddVoiceShortcutButtonStyleWhite = 0,
    INUIAddVoiceShortcutButtonStyleWhiteOutline,
    INUIAddVoiceShortcutButtonStyleBlack,
    INUIAddVoiceShortcutButtonStyleBlackOutline
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos, macosx, tvos);

@class INShortcut, INUIAddVoiceShortcutButton, INUIAddVoiceShortcutViewController, INUIEditVoiceShortcutViewController;

API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, macosx, tvos)
@protocol INUIAddVoiceShortcutButtonDelegate <NSObject>

- (void)presentAddVoiceShortcutViewController:(INUIAddVoiceShortcutViewController *)addVoiceShortcutViewController forAddVoiceShortcutButton:(INUIAddVoiceShortcutButton *)addVoiceShortcutButton;
- (void)presentEditVoiceShortcutViewController:(INUIEditVoiceShortcutViewController *)editVoiceShortcutViewController forAddVoiceShortcutButton:(INUIAddVoiceShortcutButton *)addVoiceShortcutButton;

@end

API_AVAILABLE(ios(12.0))
API_UNAVAILABLE(watchos, macosx, tvos)
@interface INUIAddVoiceShortcutButton : UIButton

- (instancetype)initWithStyle:(INUIAddVoiceShortcutButtonStyle)style;

@property (nonatomic, readonly) INUIAddVoiceShortcutButtonStyle style;

@property (nonatomic, weak) id<INUIAddVoiceShortcutButtonDelegate> delegate;
@property (nonatomic, strong, nullable) INShortcut *shortcut;

@end

NS_ASSUME_NONNULL_END
