#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocusDefines.h>)
#if __FOCUSENGINE_BUILDING_FOCUSENGINE__
#import <FocusEngine/UIFocusDefines.h>
#else
//
//  UIFocusDefines.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Availability.h>
#import <UIUtilities/UIDefines.h>
#endif // else __FOCUSENGINE_BUILDING_FOCUSENGINE__

#else
#import <UIKitCore/UIFocusDefines.h>
#endif
