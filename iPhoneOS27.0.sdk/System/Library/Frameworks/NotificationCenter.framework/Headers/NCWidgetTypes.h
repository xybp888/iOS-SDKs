//
//  NCWidgetTypes.h
//  NotificationCenter
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, NCWidgetDisplayMode) {
    NCWidgetDisplayModeCompact, // Fixed height
    NCWidgetDisplayModeExpanded, // Variable height
} API_DEPRECATED("Use WidgetKit instead. Today View extensions have been deprecated.", ios(10.0, 14.0));
