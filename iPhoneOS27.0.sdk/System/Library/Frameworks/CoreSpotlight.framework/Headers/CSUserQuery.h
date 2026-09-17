//
//  CSUserQuery.h
//  CoreSpotlight
//
//  Copyright © 2021–2026 Apple Inc. All rights reserved.
//

#import <CoreSpotlight/CSSearchQuery.h>
#import <CoreSpotlight/CSSuggestion.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0))
API_UNAVAILABLE(tvos, watchos)
typedef NS_ENUM(NSInteger, CSUserInteraction) {
    CSUserInteractionSelect,
    CSUserInteractionDefault=CSUserInteractionSelect,
    CSUserInteractionFocus,
} NS_SWIFT_NAME(CSUserQuery.UserInteractionKind);

API_AVAILABLE(macos(13.0), ios(16.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSUserQueryContext : CSSearchQueryContext

+ (CSUserQueryContext *)userQueryContext;
+ (CSUserQueryContext *)userQueryContextWithCurrentSuggestion:(CSSuggestion * _Nullable)currentSuggestion;

@property (nonatomic, assign) BOOL enableRankedResults;
@property (nonatomic, assign) BOOL disableSemanticSearch API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

// maxResultCount is maximum number of search results to retrieve. (defaults to 0)
// If maxResultCount == 0, Spotlight will retrieve all results related to query. (committed search)
@property (nonatomic, assign) NSInteger maxResultCount;

// maxSuggestionCount is maximum number of suggestion results to retrieve. (defaults to 0)
@property (nonatomic, assign) NSInteger maxSuggestionCount;

// maxRankedResultCount is maximum number of ranked search results to retrieve. (defaults to 100)
// If maxRankedResultCount > maxResultCount, Spotlight will rank maxResultCount results related to query.
@property (nonatomic, assign) NSInteger maxRankedResultCount API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

@end

API_AVAILABLE(macos(13.0), ios(16.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSUserQuery : CSSearchQuery

+ (void)prepare API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

+ (void)prepareProtectionClasses:(NSArray<NSFileProtectionType> *)protectionClasses API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

- (instancetype)initWithUserQueryString:(NSString * _Nullable)userQueryString userQueryContext:(CSUserQueryContext * _Nullable)userQueryContext NS_DESIGNATED_INITIALIZER;

// The query will update the count before each foundSuggestionsHandler invocation to reflect
// the number of suggestions found so far; if foundSuggestionsHandler is nil then the count will be zero.
@property (readonly) NSInteger foundSuggestionCount;

// The foundSuggestionsHandler may be invoked additional times as new suggestions are generated,
// but the value will always be a complete, ordered list. The query serializes all the foundSuggestionsHandler invocations. If no handler is set, suggestions will not be generated.
@property (nullable, copy) void (^foundSuggestionsHandler)(NSArray<CSSuggestion *> *suggestions);

- (void)userEngagedWithItem:(CSSearchableItem *)item visibleItems:(NSArray<CSSearchableItem *> *)visibleItems userInteractionType:(CSUserInteraction)userInteractionType NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

- (void)userEngagedWithSuggestion:(CSSuggestion *)suggestion visibleSuggestions:(NSArray<CSSuggestion *> *)visibleSuggestions userInteractionType:(CSUserInteraction)userInteractionType NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

- (void)start;
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
