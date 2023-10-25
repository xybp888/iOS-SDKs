//
//  SFAnalysisContext_Private.h
//  Speech
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AnalysisContext;

extern NSString *const _SFAnalysisContextTagLeftContext;
extern NSString *const _SFAnalysisContextTagRightContext;
extern NSString *const _SFAnalysisContextTagSelectedText;
extern NSString *const _SFAnalysisContextTagGeoLMRegionID;
extern NSString *const _SFAnalysisContextTagContextualNamedEntities;

// TODO: Remove these after Core Speech updated. rdar://110343916
extern NSString *const SFAnalysisContextTagLeftContext;
extern NSString *const SFAnalysisContextTagRightContext;
extern NSString *const SFAnalysisContextTagSelectedText;
/*
 */

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14), ios(17))
@interface _SFContextualNamedEntity : NSObject
// Wrapper around ContextualNamedEntity.

- (instancetype)initWithPersonalizationPortraitName:(NSString *)name
                                              score:(double)score
                                           category:(NSUInteger)category
                                           language:(NSString *)language;

- (instancetype)initWithPeopleSuggesterRecipientDisplayName:(NSString *)displayName;

- (instancetype)init NS_UNAVAILABLE;
@end


API_AVAILABLE(macos(14), ios(17))
@interface _SFAnalysisContext : NSObject
// Wrapper around AnalysisContext.

- (instancetype)initWithAnalysisContext:(AnalysisContext *)analysisContext;

- (instancetype)init NS_UNAVAILABLE;

/// Returns nil if the key is not found.
- (NSArray<NSString *> *_Nullable)contextualStringsForKey:(NSString *)key;
/// @param contextualStrings Pass nil to remove the key and associated value.
- (void)setContextualStrings:(NSArray<NSString *>*_Nullable)contextualStrings forKey:(NSString *)key;

/// Returns nil if the key is not found.
- (id _Nullable)userDataForKey:(NSString *)key;
/**
    The user data should be `Sendable`. In particular, it should be a property list type, that is,
    a type returned by `StringProtocol.propertyList()`.
    @param userData Pass nil to remove the key and associated value.
 */
///
- (void)setUserData:(id _Nullable)userData forKey:(NSString *)key;

@property (nonatomic, copy, nullable) NSString *geoLMRegionID;
@property (nonatomic, copy, nullable) NSArray<_SFContextualNamedEntity *> *contextualNamedEntities;

@end

NS_ASSUME_NONNULL_END
