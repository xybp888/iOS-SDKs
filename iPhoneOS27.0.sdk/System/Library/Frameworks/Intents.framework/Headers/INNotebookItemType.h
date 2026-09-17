//
//  INNotebookItemType.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#ifndef INNotebookItemType_h
#define INNotebookItemType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INNotebookItemType) {
    INNotebookItemTypeUnknown = 0,
    INNotebookItemTypeNote,
    INNotebookItemTypeTaskList,
    INNotebookItemTypeTask,
} API_DEPRECATED("INNotebookItemType is deprecated. Please adopt the Notes or Reminders AppSchema domain instead.", ios(11.0, 27.0), watchos(4.0, 27.0)) API_UNAVAILABLE(macos, tvos);

#endif // INNotebookItemType_h
