#if !__has_include(<AVFCore/AVDisplayCriteria.h>)
/*
	File:  AVDisplayCriteria.h

	Framework:  AVFoundation

	Copyright 2017-2018 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMFormatDescription.h>

NS_ASSUME_NONNULL_BEGIN

@class AVDisplayCriteriaInternal;

/*
 @class			AVDisplayCriteria
 @abstract		AVDisplayCriteria is an abstract set of properties that is used to guide the selection of a display mode.
 @discussion	Certain display modes are more suitable for certain types of content.

				Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(tvos(11.2), visionos(1.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(macos, watchos)
@interface AVDisplayCriteria : NSObject <NSCopying>
{
@private
	AVDisplayCriteriaInternal *_displayCriteria;
}
AV_INIT_UNAVAILABLE

/*!
	@method			initWithRefreshRate:formatDescription:
	@abstract		Initializes an AVDisplayCriteria with the specified refresh rate and format description.
	@param			refreshRate - Desired screen refresh rate.
	@param			formatDescription - Format description describing the video format.
	@result			An instance of AVDisplayCriteria.
*/
- (instancetype)initWithRefreshRate:(float)refreshRate formatDescription:(CMFormatDescriptionRef)formatDescription API_AVAILABLE(tvos(17.0), visionos(1.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(macos, watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVDisplayCriteria.h>
#endif
