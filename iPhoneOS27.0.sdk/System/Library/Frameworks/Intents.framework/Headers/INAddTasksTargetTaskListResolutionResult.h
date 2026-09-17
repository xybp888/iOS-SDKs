//
//  INAddTasksTargetTaskListResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#import <Intents/INTaskListResolutionResult.h>

typedef NS_ENUM(NSInteger, INAddTasksTargetTaskListConfirmationReason) {
    INAddTasksTargetTaskListConfirmationReasonListShouldBeCreated = 1,
} API_DEPRECATED("", ios(13.0, 27.0), watchos(6.0, 27.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("", ios(13.0, 27.0), watchos(6.0, 27.0))
API_UNAVAILABLE(macos, tvos)
@interface INAddTasksTargetTaskListResolutionResult : INTaskListResolutionResult

+ (instancetype)confirmationRequiredWithTaskListToConfirm:(nullable INTaskList *)taskListToConfirm forReason:(INAddTasksTargetTaskListConfirmationReason)reason NS_SWIFT_NAME(confirmationRequired(with:forReason:));

- (instancetype)initWithTaskListResolutionResult:(INTaskListResolutionResult *)taskListResolutionResult;

@end

NS_ASSUME_NONNULL_END
