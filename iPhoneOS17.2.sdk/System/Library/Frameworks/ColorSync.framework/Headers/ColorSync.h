/*
 * ColorSync - ColorSync.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNC_MAIN_HEADER__
#define __COLORSYNC_MAIN_HEADER__

#include <ColorSync/ColorSyncBase.h>
#include <ColorSync/ColorSyncProfile.h>
#include <ColorSync/ColorSyncTransform.h>

#define COLORSYNC_API_VERSION 0x00010000L // 1.0.0 BCD; uint32_t BCD = ((uint32_t)major << 16) | (minor << 8) | (dot & 0xFF);

CSEXTERN uint32_t ColorSyncAPIVersion(void);

#endif /* __COLORSYNC_MAIN_HEADER__ */

