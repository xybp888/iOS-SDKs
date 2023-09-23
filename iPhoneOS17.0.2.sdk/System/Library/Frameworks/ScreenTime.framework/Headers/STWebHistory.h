//
//  STWebHistory.h
//  ScreenTime
//
//  Copyright © 2019–2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// The object you use to delete web-usage data.
///
/// This class provides an easy way for you to delete web history, including:
///
/// - All history
/// - History associated to a specific URL
/// - History during a specific time interval
API_AVAILABLE(macos(11.0), ios(14.0))
@interface STWebHistory : NSObject

/// Creates a web history instance to delete web-usage data associated to the
/// bundle identifier you specify.
///
/// The default value for `bundleIdentifier` is `Bundle.main.bundleIdentifier`.
/// This is the recommended identifier to use, except for example, if a helper
/// process is presenting web UI and you want to group that web-usage under the
/// main app’s bundle identifier.
///
/// - Parameters:
///   - bundleIdentifier: The bundle identifier.
///   - error: Any error that occurred while changing the bundle identifier.
- (nullable instancetype)initWithBundleIdentifier:(NSString *)bundleIdentifier error:(NSError **)error;
// -init uses NSBundle.mainBundle.bundleIdentifier as the bundle identifier.

/// Deletes all the web history for the URL you specify.
///
/// The framework references the entire URL to determine which web-usage data to
/// delete.
///
/// - Parameters:
///   - url: The URL associated with the web history to delete.
- (void)deleteHistoryForURL:(NSURL *)url NS_SWIFT_NAME(deleteHistory(for:));

/// Deletes web history that occurred during the date interval you specify.
///
/// - Parameters:
///   - interval: The date interval of web history you want to delete.
- (void)deleteHistoryDuringInterval:(NSDateInterval *)interval NS_SWIFT_NAME(deleteHistory(during:));

/// Deletes all web history associated with the bundle identifier you specified
/// during initialization.
- (void)deleteAllHistory;

@end

NS_ASSUME_NONNULL_END
