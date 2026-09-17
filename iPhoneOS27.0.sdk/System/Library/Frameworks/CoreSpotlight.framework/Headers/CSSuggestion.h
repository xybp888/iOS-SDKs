//
//  CSSuggestion.h
//  CoreSpotlight
//
//  Copyright © 2021–2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(suggestionHighlight)
extern NSAttributedStringKey const CSSuggestionHighlightAttributeName API_AVAILABLE(macos(13.0), ios(16.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

API_AVAILABLE(macos(13.0), ios(16.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
typedef NS_ENUM(NSInteger, CSSuggestionKind) {
    CSSuggestionKindNone,
    CSSuggestionKindCustom,
    CSSuggestionKindDefault,
} NS_SWIFT_NAME(CSSuggestion.SuggestionKind);

API_AVAILABLE(macos(13.0), ios(16.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSSuggestion : NSObject <NSSecureCoding, NSCopying>

@property (nonnull, nonatomic, readonly) NSAttributedString *localizedAttributedSuggestion NS_REFINED_FOR_SWIFT;
@property (nonatomic, readonly) CSSuggestionKind suggestionKind;

// For suggestions that have been ranked by the query
- (NSComparisonResult)compareByRank:(CSSuggestion *)other;

- (NSComparisonResult)compare:(CSSuggestion *)other;

@end

NS_ASSUME_NONNULL_END
