//
//  AEAssessmentParticipantConfiguration.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0), macCatalyst(15.0), macos(12.0))
API_UNAVAILABLE(visionos)
@interface AEAssessmentParticipantConfiguration : NSObject <NSCopying>

/// Returns the set of allowed menu item titles for the given language
/// identifier, or @c nil if no items have been configured for that
/// identifier.
///
/// Menu item titles are matched against the participant application's
/// localized menu items at the time the assessment session begins.
/// The system resolves each language identifier to the best-matching
/// localization the application bundle provides, so an exact locale
/// match is not required.
///
/// @param languageIdentifier A BCP 47 language identifier
///   (for example, @c en or @c zh-Hans ).
///
- (nullable NSSet<NSString *> *)allowedMenuItemsForLanguageIdentifier:(NSString *)languageIdentifier API_AVAILABLE(macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(ios) NS_REFINED_FOR_SWIFT;

/// Sets the allowed menu item titles for the given language identifier.
///
/// Titles must match the participant application's localized menu item
/// strings for the corresponding language.
///
/// If multiple language identifiers resolve to the same application
/// localization, the system combines their sets of allowed menu items.
///
/// @param menuItems The set of menu item titles to allow, or @c nil to
///   remove the entry for @c languageIdentifier.
/// @param languageIdentifier A BCP 47 language identifier
///   (for example, @c en or @c zh-Hans ).
///
- (void)setAllowedMenuItems:(nullable NSSet<NSString *> *)menuItems forLanguageIdentifier:(NSString *)languageIdentifier API_AVAILABLE(macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(ios) NS_REFINED_FOR_SWIFT;

/// The set of language identifiers for which allowed menu items have
/// been configured.
///
/// Contains only identifiers explicitly added via
/// @c setAllowedMenuItems:forLanguageIdentifier: . Does not include
/// identifiers inferred through localization resolution.
///
@property (copy, nonatomic, readonly) NSSet<NSString *> *allowedMenuItemLanguageIdentifiers API_AVAILABLE(macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(ios) NS_REFINED_FOR_SWIFT;

@property (nonatomic, assign) BOOL allowsNetworkAccess API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));
@property (nonatomic, assign, getter=isRequired) BOOL required API_AVAILABLE(ios(26.0), macCatalyst(26.0), macos(26.0)) API_UNAVAILABLE(visionos);

@property (nonatomic, copy) NSDictionary<NSString *, id> *configurationInfo API_AVAILABLE(ios(18.0), macCatalyst(18.0), macos(15.0));

- (instancetype)init API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));
+ (instancetype)new API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));

@end

NS_ASSUME_NONNULL_END
