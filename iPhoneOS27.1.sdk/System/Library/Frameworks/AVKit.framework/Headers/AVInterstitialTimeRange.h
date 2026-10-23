/*
	File:  AVInterstitialTimeRange.h
	
	Framework:  AVKit
	
	Copyright © 2015-2023 Apple Inc. All rights reserved.
	
 */

#import <Foundation/Foundation.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

/*!
	@class		AVInterstitialTimeRange
	@abstract	AVInterstitialTimeRange represents the time range of an interstitial.
	@discussion	An AVInterstitialTimeRange identifies a portion of an asset as an interstitial. When the asset is presented, the time range of this interstitial content will be collapsed in the user interface timeline to a single dot, scrubbing will skip over this range, and the duration will be subtracted from the time remaining in the video as displayed to the user.
 */

API_AVAILABLE(tvos(9.0), ios(16.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos)
@interface AVInterstitialTimeRange : NSObject <NSCopying, NSSecureCoding>

/*!
	@method		initWithTimeRange:
	@param		timeRange
				The time range of the interstitial.
	@abstract	Designated initializer.
*/
 - (instancetype)initWithTimeRange:(CMTimeRange)timeRange API_AVAILABLE(tvos(9.0)) API_UNAVAILABLE(ios, visionos) API_UNAVAILABLE(macos, watchos) NS_DESIGNATED_INITIALIZER;
/*!
	@property	timeRange
	@abstract	The time range of the interstitial.
*/
@property (readonly) CMTimeRange timeRange;

@end

NS_ASSUME_NONNULL_END
