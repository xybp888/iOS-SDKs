//
//  INImageNoteContent.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INNoteContent.h>

@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INImageNoteContent is deprecated. Please adopt the Notes or Reminders AppSchema domain instead.", ios(11.0, 27.0), watchos(4.0, 27.0)) API_UNAVAILABLE(macos, tvos)
@interface INImageNoteContent : INNoteContent <NSSecureCoding, NSCopying>

- (instancetype)initWithImage:(INImage *)image;

// The image that comprises the note content
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *image;

@end
NS_ASSUME_NONNULL_END
