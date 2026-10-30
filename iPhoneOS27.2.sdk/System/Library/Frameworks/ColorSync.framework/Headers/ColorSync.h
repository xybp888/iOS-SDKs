/*
 * ColorSync - ColorSync.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNC_MAIN_HEADER__
#define __COLORSYNC_MAIN_HEADER__

#include <ColorSync/ColorSyncBase.h>
#include <ColorSync/ColorSyncHeadroomAdaptiveGainCurve.h>
#include <ColorSync/ColorSyncProfile.h>
#include <ColorSync/ColorSyncTransform.h>

#define COLORSYNC_API_VERSION 0x1B000000L
// 27.0.0.0 BCD; uint32_t BCD = ((uint32_t)majorOS (=  << 24) | (minorOS << 16) | (dotOS << 8) | (API version & 0xFF);

/// Returns the version of the ColorSync API.
///
/// - Returns: The API version as a binary-coded decimal `uint32_t`. From most to least
///   significant byte, the value encodes the major OS version, minor OS version, patch
///   version, and API version — that is, `(major << 24) | (minor << 16) | (dot << 8) | (apiVersion & 0xFF)`.
CSEXTERN uint32_t ColorSyncAPIVersion(void);

#endif /* __COLORSYNC_MAIN_HEADER__ */

