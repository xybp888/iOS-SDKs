//
//  CSUserQuery.h
//  CoreSpotlight
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <CoreSpotlight/CSBase.h>
#import <CoreSpotlight/CoreSpotlight.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.13), ios(16.0)) CS_TVOS_UNAVAILABLE
@interface CSUserQueryContext : CSSearchQueryContext

+ (CSUserQueryContext *)userQueryContext;
+ (CSUserQueryContext *)userQueryContextWithCurrentSuggestion:(CSSuggestion * _Nullable)currentSuggestion;

@property (nonatomic, assign) BOOL enableRankedResults;

// maxResultCount is maximum number of search results to retrieve. (defaults to 0)
// If maxResultCount == 0, Spotlight will retrieve all results related to query. (committed search)
@property (nonatomic, assign) NSInteger maxResultCount;
// maxSuggestionCount is maximum number of suggestion results to retrieve. (defaults to 0)
@property (nonatomic, assign) NSInteger maxSuggestionCount;

@end

API_AVAILABLE(macos(10.13), ios(16.0)) CS_TVOS_UNAVAILABLE
@interface CSUserQuery : CSSearchQuery

- (instancetype)initWithUserQueryString:(NSString * _Nullable)userQueryString userQueryContext:(CSUserQueryContext * _Nullable)userQueryContext NS_DESIGNATED_INITIALIZER;

// The query will update the count before each foundSuggestionsHandler invocation to reflect
// the number of suggestions found so far; if foundSuggestionsHandler is nil then the count will be zero.
@property (readonly) NSInteger foundSuggestionCount;

// The foundSuggestionsHandler may be invoked additional times as new suggestions are generated,
// but the value will always be a complete, ordered list. The query serializes all the foundSuggestionsHandler invocations. If no handler is set, suggestions will not be generated.
@property (nullable, copy) void (^foundSuggestionsHandler)(NSArray<CSSuggestion *> *suggestions);

- (void)start;
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
