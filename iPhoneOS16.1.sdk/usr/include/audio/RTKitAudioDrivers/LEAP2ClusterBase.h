//
//  LEAP2ClusterBase.h
//  RTKitAudioDrivers
//
//  Created by Rashmi on 6/5/20.
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

// Use header guards instead of #pragma once because LEAP2ClusterBase.h can potentially be
// included from multiple paths and #pragma can't avoid that
#ifndef LEAP2_CLUSTER_BASE_H
#define LEAP2_CLUSTER_BASE_H

#include "LEAP2DeclHelper.h"

#if defined(TARGET_TYPE) && \
    ((TARGET_TYPE == TARGET_TYPE_ASTRIS) || (TARGET_TYPE == TARGET_TYPE_UNIT_TESTS))
#include "RTKCpuFake.hpp"
#else
#include <RTK_rtbuddy_cpu.h>
#include <RTK_rtbuddy_mapper.h>
#endif

namespace RTKitAudioDrivers
{
    namespace LEAP2
    {
        /*!
         @class ClusterBase
         @abstract Represents leap2 cluster for enabling power, loading firmware
         @discussion Extends the RTK_rtbuddy_cpu to be able to load firmware either from the
         filesystem or the buffer
         */
        class ClusterBase : public RTK_rtbuddy_cpu
        {
            using super = RTK_rtbuddy_cpu;

        protected:
            ClusterBase(SegmentMapper&                      inMapper,
                        RTKitAudioDrivers::LEAP2::ClusterId inClusterId,
                        bool                                inIsLoadFirmwareFromFileSupported,
                        bool                                inIsLoadFirmwareFromBufferSupported,
                        bool                                inIsMemoryRetentionSupported)
              : RTK_rtbuddy_cpu(inMapper, nullptr, PMGR_DEVICE_NONE), mClusterId(inClusterId),
                mIsLoadFirmwareFromFileSupported(inIsLoadFirmwareFromFileSupported),
                mIsLoadFirmwareFromBufferSupported(inIsLoadFirmwareFromBufferSupported),
                mIsMemoryRetentionSupported(inIsMemoryRetentionSupported)
            {
            }

            virtual ~ClusterBase() = default;

        public:
            /*! For loading firmware from filesystem which is typical for RTKitOSPlatform product.
             LEAP firmware comes in rtkbin file format. RTK_rtbudy_cpu helps load this firmware file
             onto the cluster.
             https://confluence.sd.apple.com/pages/viewpage.action?pageId=521642301
             But, leap firmware has a specific requirement that it needs to setup some core
             registers before the firmware is loaded into the memory and after the firmware load is
             completed. These pre and post segments are register value pairs. These are handled 2
             different ways. For RTKOS platform product, the repre needs to be split into 1-n number
             of files.
             @param inCoreFileName  4cc code filename for the core file
             @param inRegPreFileNames an array of reg pre file names
             @param inRegPreFileCount count of reg pre files
             @param inRegPostFileNames an array of reg post file names
             @param inRegPostFileCount count of reg post
             @result RTK_ST_OK                 firmware loaded successfully
                     RTK_ST_INVALID_PARAMETER  file not found
                     RTK_ST_NOT_IMPLEMENTED   if not implemented
                     RTK_ST_DEVICE_ERROR any other error
                     RTK_ST_OUT_OF_RESOURCES out of resources
             */
            virtual RTK_status loadFirmwareImageFromFile(uint32_t        inCoreFileName,
                                                         const uint32_t* inRegPreFileNames,
                                                         uint8_t         inRegPreFileCount,
                                                         uint32_t*       inRegPostFileNames,
                                                         uint8_t         inRegPostFileCount) = 0;

            /*! loadFirmwareImage using  RAM buffer
             @param *inBuffer pointer to the firmware in RAM
             @param inBufferSizeInBytes size of the firmware buffer in bytes
             @result RTK_ST_OK                 firmware loaded successfully
                     RTK_ST_NOT_IMPLEMENTED   if not implemented
                     RTK_ST_DEVICE_ERROR any other error
                     RTK_ST_OUT_OF_RESOURCES out of resources
             */
            virtual RTK_status loadFirmwareImage(void* inBuffer, size_t inBufferSizeInBytes) = 0;

            /*! getId returns cluster Id
              @result RTKitAudioDrivers::LEAP2::ClusterId  return the clusterId
             */
            RTKitAudioDrivers::LEAP2::ClusterId getId() const { return mClusterId; }

            /*! isFirmwareLoadFromFileSupported returns true if firmware from file is supported
             @result true if loading firmware from  file is supported
                     false if loading firmware from  file is unsupported
             */
            bool isFirmwareLoadFromFileSupported() const
            {
                return mIsLoadFirmwareFromFileSupported;
            }

            /*! isFirmwareLoadFromFileSupported returns true if firmware from buffer is supported
             @result true return if loading firmware from buffer is supported
                     false if loading firmware from  file is unsupported
             */
            bool isFirmwareLoadFromBufferSupported() const
            {
                return mIsLoadFirmwareFromBufferSupported;
            }

            bool isMemoryRetentionSupported() const { return mIsMemoryRetentionSupported; }

            bool isClusterComposite() const { return mIsClusterComposite; }

        protected:
            const RTKitAudioDrivers::LEAP2::ClusterId mClusterId;
            bool                                      mIsLoadFirmwareFromFileSupported;
            bool                                      mIsLoadFirmwareFromBufferSupported;
            bool                                      mIsMemoryRetentionSupported;
            bool                                      mIsClusterComposite;
        };
    } // namespace LEAP2
} // namespace RTKitAudioDrivers

#endif // LEAP2_CLUSTER_BASE_H
