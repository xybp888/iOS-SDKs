//
//  AEAssessmentSessionDelegate.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.4), macos(10.15.4))
API_UNAVAILABLE(macCatalyst)
@protocol AEAssessmentSessionDelegate <NSObject>
@optional

- (void)assessmentSessionDidBegin:(AEAssessmentSession *)session;

- (void)assessmentSession:(AEAssessmentSession *)session failedToBeginWithError:(NSError *)error;

- (void)assessmentSession:(AEAssessmentSession *)session wasInterruptedWithError:(NSError *)error;

- (void)assessmentSessionDidEnd:(AEAssessmentSession *)session;

@end

NS_ASSUME_NONNULL_END
