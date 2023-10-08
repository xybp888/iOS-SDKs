#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISelectionFeedbackGenerator.h>)
//
//  UISelectionFeedbackGenerator.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIFeedbackGenerator.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// UISelectionFeedbackGenerator is used to give user feedback when a selection changes
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UISelectionFeedbackGenerator : UIFeedbackGenerator

/// call when the selection changes (not on initial selection)
- (void)selectionChanged;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISelectionFeedbackGenerator.h>
#endif
