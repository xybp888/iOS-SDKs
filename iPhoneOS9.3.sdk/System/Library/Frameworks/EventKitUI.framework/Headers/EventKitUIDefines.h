/*
 *  EventKitUIDefines.h
 *  EventKitUI
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#ifdef __cplusplus
#define EVENTKITUI_EXTERN               extern "C" __attribute__((visibility ("default")))
#else
#define EVENTKITUI_EXTERN               extern __attribute__((visibility ("default")))
#endif

#define EVENTKITUI_CLASS_AVAILABLE(_iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, _iphoneIntro)