//
//  INNoteContent.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INNoteContent is deprecated. Please adopt the Notes or Reminders AppSchema domain instead.", ios(11.0, 27.0), watchos(4.0, 27.0))
API_UNAVAILABLE(macos, tvos)
@interface INNoteContent : NSObject <NSSecureCoding, NSCopying>

@end
NS_ASSUME_NONNULL_END
