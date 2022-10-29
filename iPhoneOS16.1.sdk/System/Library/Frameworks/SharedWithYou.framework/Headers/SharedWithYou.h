//
//  SharedWithYou.h
//  SharedWithYou
//
//  Copyright (c) 2021 Apple. All rights reserved.
//

#import <SharedWithYouCore/SharedWithYouCore.h>

#import <SharedWithYou/SWErrors.h>
#import <SharedWithYou/SWCollaborationHighlight.h>
#import <SharedWithYou/SWHighlight.h>
#import <SharedWithYou/SWHighlightCenter.h>
#import <SharedWithYou/SWHighlightChangeEvent.h>
#import <SharedWithYou/SWHighlightEvent.h>
#import <SharedWithYou/SWHighlightMembershipEvent.h>
#import <SharedWithYou/SWHighlightMentionEvent.h>
#import <SharedWithYou/SWHighlightPersistenceEvent.h>
#import <SharedWithYou/SWAttributionView.h>
#import <SharedWithYou/SWCollaborationView.h>
#import <SharedWithYou/NSItemProvider+SWCollaborationMetadata.h>

#if TARGET_OS_IPHONE
#import <SharedWithYou/SWRemoveParticipantAlertController.h>
#else
#import <SharedWithYou/SWRemoveParticipantAlert.h>
#endif

#if TARGET_OS_OSX
#import <SharedWithYou/NSPasteboardItem+SWCollaborationMetadata.h>
#endif
