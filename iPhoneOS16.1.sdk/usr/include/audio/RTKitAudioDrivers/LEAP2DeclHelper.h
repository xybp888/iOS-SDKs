//
//  LEAP2DeclHelper.h
//  RTKitAudioDrivers
//
//  Created by Rashmi on 3/14/20.
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

// Use header guards instead of #pragma once because LEAP2DeclHelper.h can potentially be
// included from multiple paths and #pragma won't prevent that
#ifndef LEAP2_DECL_HELPER_H
#define LEAP2_DECL_HELPER_H

namespace RTKitAudioDrivers
{
    namespace LEAP2
    {
        typedef uint8_t CoreNum;
        typedef uint8_t ThreadNum;
        typedef uint8_t ClusterId;
        typedef uint8_t ComponentIndex;
        typedef uint8_t ComponentCount;

        enum : ClusterId
        {
            kAON  = 0,
            kAUD0 = 1,
            kAUD1 = 2,
            kAUD2 = 3,
            kAUD3 = 4,
            kAUD4 = 5,
            kAUD5 = 6,
            kSelf = 255, // Relative conotation
        };

        constexpr uint8_t kCoreMaxCount = 5;

        enum ThreadMask
        {
            kThread0Mask   = 0x1 << 0,
            kThread1Mask   = 0x1 << 1,
            kThread2Mask   = 0x1 << 2,
            kThread3Mask   = 0x1 << 3,
            kThreadAllMask = kThread0Mask | kThread1Mask | kThread2Mask | kThread3Mask,
        };

        enum class PowerGroup : uint8_t
        {
            kPowerGroup0   = 0x1,
            kPowerGroup1   = 0x2,
            kPowerGroupAll = 0x3,
        };

        enum CoreMask
        {
            kCoreMaskInvalid = 0,
            kCoreMask0       = 0x1 << 0,
            kCoreMask1       = 0x1 << 1,
            kCoreMask2       = 0x1 << 2,
            kCoreMask3       = 0x1 << 3,
            kCoreMask4       = 0x1 << 4,
            kCoreMask5       = 0x1 << 5,
            kCoreMaskCommon  = 0x1 << 6,
            kCoreMaskAll     = ((1UL << sizeof(uint8_t) * 8) - 1),
        };

        constexpr uint8_t kCoreMaxT2016 = 5;
        constexpr uint8_t kCoreMaxT6500 = 5;

        /*!
         @struct CoreConfiguration
         @abstract Core configuration description
         @field instMemSizeInWords Size of instruction mem (words)
         @field dataMemSizeInWords Size of data mem (words)
         @field fEx flag to indicate floating-point execution
         @field trns flag to indicate if transcendentals are present in the core
         @field wfir flag to indicate if WFIRs are present in the core
         @field powerGroup flag to indicate which powerGroup is this core associated with
         */
        struct CoreConfiguration
        {
            uint32_t   instMemSizeInWords;
            uint32_t   dataMemSizeInWords;
            bool       fEx;
            bool       trns;
            uint8_t    WFIR;
            PowerGroup powerGroup;
            uint64_t   baseAddress;
            size_t     blockSize;
        };
    } // namespace LEAP2
} // namespace RTKitAudioDrivers

#endif
