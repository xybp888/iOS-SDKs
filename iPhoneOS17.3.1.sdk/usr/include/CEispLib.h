/**
 * \file CEispLib.h
 *
 * \brief Include file for \ref CEispLib class.
 *
 * This file includes the definition for the \ref CEispLib class.
 *
 * - Copyright(c) 2011 Apple Inc. All rights reserved.
 *
 */

#ifndef CEISPLIB_H_
#define CEISPLIB_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "CEispLibDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t  eispMemObjId_t;
#define eispMemObjId_Invalid  (0)
typedef   int64_t           EISPHandle;
#define   EISPHandleInvalid (-1)

#define EISPLIB_DUMPBUFF_SIZE       (1*1024*1024)
#define EISPLIB_TRACEBUFF_SIZE      (288*1024)
#define EISPLIB_NON_AR_MEMORY_SIZE  (EISPLIB_DUMPBUFF_SIZE + EISPLIB_TRACEBUFF_SIZE) //dumpBufSize + traceBufferSize

#ifdef EISP_EXTRA_STACK
#define STACK_PER_THREAD            (128*1024)
#else
#define STACK_PER_THREAD            (64*1024)
#endif
#define IMPLICIT_LIBRARY_MARGIN     (5)
#define EISPLIB_AR_MEMORY_SIZE      (STACK_PER_THREAD + PAGESIZE*(1+IMPLICIT_LIBRARY_MARGIN)) //dumpBufSize + traceBufferSize

typedef struct _sEISPLibConfigOption{
  uint32_t  tbd;
} __attribute__((packed))sEISPLibConfigOption;

typedef struct _sEISPLibParam{
  uint32_t  heapSize;  /*heap size requirement for the lib, in bytes */
  uint32_t  refImageSize; /*the size of each uncompression ref image size in bytes*/
} __attribute__((packed))sEISPLibParam;

enum eEISPLibFDRRegType
{
  eEISPLibFDRRegType_SPARSE = 0,
  eEISPLibFDRRegType_DENSE,
  eEISPLibFDRRegType_MAX
};

typedef struct  _sEISPLibFDRData
{
  uint8_t    *pPceCalib;
  uint32_t   calibSize;

  uint8_t     *pPceRegs[eEISPLibFDRRegType_MAX];
  uint32_t     pceRegsSize[eEISPLibFDRRegType_MAX];
} __attribute__((packed))sEISPLibFDRData;

typedef struct  _sEISPLibSpotDbData
{
  uint64_t pceSportDB;
} __attribute__((packed))sEISPLibSpotDbData;

typedef enum _eEISPLibCalibrationDataTypes
{
  eEISPLibCalibrationDataType_PCIC = 0,
  eEISPLibCalibrationDataType_PCVC,
  eEISPLibCalibrationDataType_PCII,
  eEISPLibCalibrationDataType_PCVI,
  eEISPLibCalibrationDataType_PCVE,
  eEISPLibCalibrationDataType_PBAS,
  eEISPLibCalibrationDataType_PMPC,
  eEISPLibCalibrationDataType_PDCL,
  eEISPLibCalibrationDataType_PREG,
  eEISPLibCalibrationDataType_PRF1,
  eEISPLibCalibrationDataType_PRF2,
  eEISPLibCalibrationDataType_PSD1,
  eEISPLibCalibrationDataType_PSD2,
  eEISPLibCalibrationDataType_PWCL,
  eEISPLibCalibrationDataType_PFCL,
  eEISPLibCalibrationDataType_PSNV,
  eEISPLibCalibrationDataType_PSPC,
  eEISPLibCalibrationDataType_Nbr,
} eEISPLibCalibrationDataTypes;

typedef struct  _sEISPLibFDRRawData
{
  eispMemObjId_t  fdrRawDataDartObj[eEISPLibCalibrationDataType_Nbr];
} __attribute__((packed))sEISPLibFDRRawData;

typedef struct  _sEISPLibInitParameter
{
  void      *pHeap;   /*Aligned to size_t*/
  uint32_t  heapSize; /*in bytes*/
  uint32_t  maxUserNbr; /*Maximum User support for the verifier*/
  uint32_t  maxEnrollmentNbr; /*Maximum enrollment for one user*/
} sEISPLibInitParameter;

typedef enum  _eEISPLibEnrollStatus{
    eEISPLibEnrollStatus_KeepGoing = 0,
    eEISPLibEnrollStatus_Completed = 1,

} eEISPLibEnrollStatus;

typedef enum  _eEISPLibEnrollFeedback{
    eEISPLibEnrollFeedback_OK               = 0,
    eEISPLibEnrollFeedback_MoreFrames       = 1,
    eEISPLibEnrollFeedback_NoFaceDetected   = 0x2,
    eEISPLibEnrollFeedback_MultipleFaces    = 0x4,
    eEISPLibEnrollFeedback_FaceOutFov       = 0x8,
    eEISPLibEnrollFeedback_FaceTooClose     = 0x10,
    eEISPLibEnrollFeedback_FaceTooFar       = 0x20,
    eEISPLibEnrollFeedback_PoseOutRange     = 0x40,
    eEISPLibEnrollFeedback_BinCovered       = 0x80,
    eEISPLibEnrollFeedback_Occluded         = 0x100,
    eEISPLibEnrollFeedback_NotCompleted     = 0x200,
    eEISPLibEnrollFeedback_Finalized        = 0x400,
    eEISPLibEnrollFeedback_OutOfMemory      = 0x800,
    eEISPLibEnrollFeedback_HwError          = 0x1000,
    eEISPLibEnrollFeedback_Internal         = 0x2000,
    eEISPLibEnrollFeedback_TooManyFeatures  = 0x4000,
    eEISPLibEnrollFeedback_NotInitialized   = 0x8000,
    eEISPLibEnrollFeedback_NO_ATTN          = 0x10000,
    eEISPLibEnrollFeedback_Invalid          = 0x20000,
    eEISPLibEnrollFeedback_InvalidAtt       = 0x40000,
    eEISPLibEnrollFeedback_InvalidLandMark  = 0x80000,
    eEISPLibEnrollFeedback_InvalidOccul     = 0x100000,
    eEISPLibEnrollFeedback_UpperFaceOccl    = 0x200000,
    eEISPLibEnrollFeedback_LowerFaceOccl    = 0x400000,
    eEISPLibEnrollFeedback_ANTISPOOF_NOT_PASSED     = 0x800000,
    eEISPLibEnrollFeedback_IDENTITY_CHANGE          = 0x1000000,
    eEISPLibEnrollFeedback_TWO_IDENTIIES_SUSPICIOUS = 0x2000000,
    eEISPLibEnrollFeedback_INCORRECT_VERSION        = 0x4000000,
    eEISPLibEnrollFeedback_DEPTHHOLES               = 0x8000000,
    eEISPLibEnrollFeedback_INVALID_PLATFORM         = 0x10000000,
    eEISPLibEnrollFeedback_DUPLICATE_ENROLL_ID      = 0x20000000,
    eEISPLibEnrollFeedback_MISMATCH_SESSION_TYPE    = 0x40000000,
} eEISPLibEnrollFeedback;

typedef enum  _eEISPLibMigrateTemplateFeedback{
  eEISPLibMigrateTemplateFeedback_NotChanged = 0,
  eEISPLibMigrateTemplateFeedback_Success,
  eEISPLibMigrateTemplateFeedback_Fail,
} eEISPLibMigrateTemplateFeedback;


typedef struct  _sEISPLibFIDTemplateList{
    uint32_t  templateCount;
    sEISPLibFIDTemplate *templates;
} __attribute__((packed)) sEISPLibFIDTemplateList;

typedef struct _sEISPLibMatchParameters {
    bool overrideAntispoofing;
    bool overrideAttention;
} __attribute__((packed)) sEISPLibMatchParameters;

typedef struct _sEISPLibAlgorithmParameters {
    uint32_t overrideAntispoofing:1;
    uint32_t overrideAttention:1;
    uint32_t	rsvd;
} __attribute__((packed)) sEISPLibAlgorithmParameters;

typedef struct _sEISPLibGenericMetaInfo
{
    uint64_t       groupId;
    uint32_t       isFlood;
    uint32_t       isBioCapture;
    uint32_t       isSparse; //This only has valid value when isFlood is false.
} __attribute__((packed)) EISPLibGenericMetaInfo;

typedef struct _sEISPLibEnrollMetaInfo
{
    uint64_t       groupId;
    uint32_t       isFlood;
    uint32_t       isBioCapture;
    uint16_t       triggerCapture; // 0/1
    uint16_t       resvd;
    uint32_t       feedback; // See eEISPLibEnrollFeedback.
    uint32_t       isSparse; //This only has valid value when isFlood is false.
    float          pitch;
    float          yaw;
    float          roll;
} __attribute__((packed))sEISPLibEnrollMetaInfo;

typedef struct _sEISPLibVerifyMetaInfo
{
    uint64_t       groupId;
    uint32_t       isFlood;
    uint32_t       isBioCapture;
    uint32_t       isFullFace;
    uint32_t       isSparse; //This only has valid value when isFlood is false.
    //uint16_t       triggerCapture; // 0/1
    float          pitch;
    float          yaw;
    float          roll;
} __attribute__((packed)) sEISPLibVerifyMetaInfo;

typedef struct _sEISPLibRefData
{
    double       temperature;    // temperature of the reference image
} __attribute__((packed)) sEISPLibRefData;



//typedef void (*EISPLibFrameDoneCallback)(void *context, const sFrameOutputMeta *result);
typedef enum  _eEISPLibCallbackType{
  eEISPLibCallbackType_SHAComplete = 0,
  eEISPLibCallbackType_FeatureResult = 1,
} eEISPLibCallbackType;

typedef void (*EISPLibFrameDoneCallbackObj)(void *context, eispMemObjId_t resultId);

typedef void (*EISPLibFrameDoneCallbackObj3)(void *context, uint64_t  userData, eispMemObjId_t resultId);

typedef void (*EISPLibFrameDoneCallbackObj4)(void *context, uint64_t  userData, uint32_t  type, eispMemObjId_t resultId); //type should be eEISPLibCallbackType

#define CEISP_FID_TEMPLATE_INDEX_MAX_NBR  (1)

/**
 * Get the Configuration of  the EISPLib.
 *
 * \param[in]  cfgOptions       some configuration parameter of the EISP Library.
 * \param[out] outputParameter  returned parameter to the user according the input configuation, such as memory size.
 *
 * \return, Handle of the EISP Library object.
 */

eEISPLibErrorCode EISPLibGetParameter(const sEISPLibConfigOption *cfgOptions, sEISPLibParam *outputParameter);

/**
 * Delete the Library
 */
eEISPLibErrorCode EISPLibDelete(EISPHandle libHandle);

/**
 * Library Init
 * \param[In] pLibHandle  library handle
 * \param[in] pFdr        factory data information
 * \param[in] pInitParam  init parameter.
 */
eEISPLibErrorCode EISPLibCreate(EISPHandle *pLibHandle,
                                const sEISPLibFDRData *pFdr,
                                const sEISPLibInitParameter *pInitParam);

eEISPLibErrorCode EISPLibCreate_v2(EISPHandle *pLibHandle,
                                const sEISPLibFDRData *pFdr,
                                const sEISPLibInitParameter *pInitParam,
                                sEispLibFidFwDetectorRect *fovRect);

eEISPLibErrorCode EISPLibSetFDR(EISPHandle *pLibHandle,
                                const sEISPLibFDRData *pFdr);

eEISPLibErrorCode EISPLibSetSpotDb(EISPHandle *pLibHandle,
                                const sEISPLibSpotDbData *pFdr);


/**
 * Set the Raw FDR Data so the EispLibrary and EIspApp will generate its Calibration Data
 * \param[In]   pLibHandle    library handle
 * \param[In]   pFdr          Raw FDR
 * \param[Out]  pceCalibData  the memory object for the calib data.
 */
eEISPLibErrorCode EISPLibSetRawFDR(EISPHandle *pLibHandle,
                                  const sEISPLibFDRRawData *pFdr,
                                  eispMemObjId_t  		*pceCalibData);


/**
 * Call this API to signal one phase is about to start. This is intended for EISPLib to keep information within a session
 * \param[In] libHandle   library handle
 * \param[in] type        type
 * \return    error code
 */
eEISPLibErrorCode EISPLibPhaseStart(EISPHandle libHandle, eFIDPhaseID type);


eEISPLibErrorCode EISPLibPhaseStart_v2(EISPHandle libHandle, eFIDPhaseID type,
    bool disableAntispoof, bool disableAttention);


eEISPLibErrorCode EISPLibPhaseStart_v3(EISPHandle libHandle, eFIDPhaseID type, uint32_t token,
    bool disableAntispoof, bool disableAttention);

eEISPLibErrorCode EISPLibPhaseStart_v4(EISPHandle libHandle, eFIDPhaseID type, uint32_t token,
    bool disableAntispoof, bool disableAttention, uint32_t minAttentionCount);

eEISPLibErrorCode EISPLibPhaseStart_v5(EISPHandle libHandle, eFIDPhaseID type, uint32_t token,
    bool disableAntispoof, bool disableAttention, uint32_t minAttentionCount, uint32_t userID, uuid_t enrollmentID);

eEISPLibErrorCode EISPLibIsPeriocularSupported(EISPHandle libHandle, bool* isPeriocularSupported);

eEISPLibErrorCode EISPLibIsMultiUserSupported(EISPHandle libHandle, bool* isMultiUserSupported);

eEISPLibErrorCode EISPLibPhaseStart_v6(EISPHandle libHandle, eFIDPhaseID type, uint32_t token,
    bool disableAntispoof, bool disableAttention, uint32_t minAttentionCount, uint32_t userID, uuid_t enrollmentID, bool isPeriocular);

eEISPLibErrorCode EISPLibPhaseStart_v7(EISPHandle libHandle, eFIDPhaseID type, uint32_t token,
    bool disableAntispoof, bool disableAttention, uint32_t minAttentionCount, uint32_t userID, uuid_t enrollmentID, bool isPeriocular, uint32_t templateID);

eEISPLibErrorCode EISPLibPhaseStart_v8(EISPHandle libHandle, eFIDPhaseID type, uint32_t token,
    bool disableAntispoof, bool disableAttention, uint32_t minAttentionCount, uint32_t userID, uuid_t enrollmentID, eFIDEnrollmentType enrollType, uint32_t templateID);

eEISPLibErrorCode EISPLibPhaseStart_v9(EISPHandle libHandle, eFIDPhaseID type, uint32_t token,
    bool disableAntispoof, bool disableAttention, uint32_t minAttentionCount, uint32_t userID, uuid_t enrollmentID, bool isPeriocular, uint32_t templateID, eEispLibFidGlassesMode glassesRequirement);

eEISPLibErrorCode EISPLibPhaseStart_v10(EISPHandle libHandle, sEISPLibSessionSetting *pSessionSetting);

void  EISPLibSetSessionID(EISPHandle libHandle, uint64_t sessionId);


/**
 * Call this API to signal one phase is about to stop. This is intended for EISPLib to keep information within a session
 * \param[In] libHandle   library handle
 * \return    error code
 */
eEISPLibErrorCode EISPLibPhaseStop(EISPHandle libHandle);


/**
 * Utility Function to get the ref Image from FDR data indexed by the temperature.
 * \param[In] libHandle       library handle
 * \param[in] fdrDataIn       factory data information
 * \param[in] fdrDataInSize   size,
 * \param[in] temperature     temperature
 * \param[in] refImage        pointer of reference image which contains the result
 * \param[in,out] refImageSize  size of the refImage buffer.
 * \return    error code
 */
eEISPLibErrorCode EISPLibFDRDataGetRefImage(EISPHandle libHandle,
                                              const void *fdrDataIn,
                                              size_t  fdrDataInSize,
                                              float   temperature, /*In unit of F degree */
                                              void    *refImage,
                                              size_t  *refImageSize);

/**
 * Utility Function to get number of reference sets
 * \param[In]   libHandle   library handle
 * \param[in]   prf1        raw factory data AP dart memory object
 * \param[out]  pNbrOfSet  Nbr of reference sets.
 * \return      error code
 */
eEISPLibErrorCode EISPLibFDRDataGetNbrOfRefSets(EISPHandle libHandle,
                                                const eispMemObjId_t  prf1,
                                                uint32_t  *pNbrOfSet);
/**
 * Utility Function to get information for each set of referene.
 * \param[In]   libHandle     library handle
 * \param[in]   prf1          raw factory data AP dart memory object
 * \param[in]   refSetIndex   index of the set,
 * \param[out]  pNbrOfRef     Number of reference in the set
 * \param[out]  pSizeForOneRef  size of each reference in the set.
 * \return      error code
 */
eEISPLibErrorCode EISPLibFDRDataGetRefImageSetInfo(EISPHandle libHandle,
                                                   const eispMemObjId_t  prf1,
                                                   uint32_t  refSetIndex,
                                                   eEISPLibPrf1EntryType *pRrefType,
                                                   uint32_t  *pNbrOfRef,
                                                   uint32_t  *pSizeForOneRef
                                                   );
/**
 * Utility Function to decompression the compression reference image
 * \param[In]   libHandle     library handle
 * \param[in]   prf1Ap        raw factory data AP dart memory object
 * \param[in]   refSetIndex   index of the set.
 * \param[out]  decompressRefSet  output memory object, size has to be more than NbrOfRef times SizeForOneRef for that set
 * \param[out]  refData       output memory object, Array of sEISPLibRefData. Size has to be more than NbrOfRef times sEISPLibRefData for that set
 * \return      error code
 */
eEISPLibErrorCode EISPLibFDRDataDecompressRefImageSet(EISPHandle libHandle,
                                                      const eispMemObjId_t  prf1Ap,
                                                      uint32_t  refSetIndex,
                                                      eispMemObjId_t  decompressRefSet,
                                                      eispMemObjId_t  refData
                                                      );
/**
 * Utility Function to compress a single reference image
 * \param[in]   source        	memory object holding multiple reference images
 * \param[in]   sourceOffset	offset to the beginning of the specific reference in the memory object
 * \param[in]	sourceSize		size of the specific reference
 * \param[out]  dest  			output memory object, to hold the compress reference image
 * \param[in]   destMaxSize     size of the output memory object
 * \param[out]	compressedSize	size used to compress the reference image
 * \return      error code
 */
eEISPLibErrorCode EISPLibFDRCompressRef(const eispMemObjId_t source,
 										uint32_t sourceOffset,
 										uint32_t sourceSize,
 										eispMemObjId_t dest,
 										uint32_t destMaxSize,
										uint32_t* compressedSize);


/**
 * Call this API to after each reboot to update the PPD algo with the buffer from the previous run
 * \param[In]   libHandle          library handle
 * \param[in]   ppdHistoryBuffer   data From the persistent memory
 * \return      error code
 */
eEISPLibErrorCode EISPLibPPDHistoryBufferSet(EISPHandle libHandle,
                                                      const eispMemObjId_t  ppdHistoryBuffer
                                                      );


/**
 * Function to start frame process request.
 * This is an Async function call, which means once this function return, the process
 * may not be done yet.
 *  The API should be called for B0 chip only.
 * \param[In] libHandle   library handle
 * \param[in] meta        meta data mem obj
 * \param[in] rawSensor   raw image mem obj
 * \param[in] refImage    ref Image mem obj
 * \return    error code
 */
eEISPLibErrorCode EISPLibFeatureGeneration(EISPHandle libHandle,
                                           eispMemObjId_t  meta,
                                           eispMemObjId_t  rawSensor,
                                           eispMemObjId_t  refImage,
                                           eispMemObjId_t  result);

/**
 * The callback function will be called once the frame processing is done
 * This is an Async function call.
 * Once this function is called, the related
 * Resource could be freed. It is the callers responsibility to do the memory clean up  (DART unmapped, for example)
 * \param[In] libHandle     library handle
 * \param[in] callbackObj   call back.
 * \param[in] context       call back context.
 * \return    error code
 */

/*eEISPLibErrorCode EISPLibInstallFrameDoneCallBackFunc(EISPHandle libHandle,
                                                        EISPLibFrameDoneCallback callback,
                                                        void *context);
*/

eEISPLibErrorCode EISPLibInstallFrameDoneCallBackFuncObj( EISPHandle libHandle,
                                                          EISPLibFrameDoneCallbackObj callbackObj,
                                                          void *context);

eEISPLibErrorCode EISPLibInstallFrameDoneCallBackFuncObj3( EISPHandle libHandle,
                                                          EISPLibFrameDoneCallbackObj3 callbackObj,
                                                          void *context);

eEISPLibErrorCode EISPLibInstallFrameDoneCallBackFuncObj4( EISPHandle libHandle,
                                                           EISPLibFrameDoneCallbackObj4 callbackObj,
                                                           void *context);

/**
 * Set up the template feature vectors for future matching.
 * \param[In] libHandle     library handle
 * \param[in] templateList  template index (less than CEISP_FID_TEMPLATE_INDEX_MAX_NBR)
 * \return    error code
 */
eEISPLibErrorCode EISPLibMatchSetTemplate(EISPHandle libHandle,
                                          const sEISPLibFIDTemplateList *templateList);

/**
 * Set up the template feature vectors for future matching.
 * \param[In] libHandle     library handle
 * \param[in] templateList  template index (less than CEISP_FID_TEMPLATE_INDEX_MAX_NBR)
 *                          Only templates for the corresponding Fullface or Periocular sessions
 * \return    error code
 */
eEISPLibErrorCode EISPLibMatchSetTemplate_v2(EISPHandle libHandle,
                                            const sEISPLibFIDTemplateList *templateList,
                                            uint32_t numEnrollments);

eEISPLibErrorCode EISPLibMatchSetTemplate_v3(EISPHandle libHandle,
                                            const sEISPLibFIDTemplateList *templateList,
                                            sEISPLibFIDSimilarityTag *similarityTag);


eEISPLibErrorCode EISPLibMatchResetTemplate(EISPHandle libHandle,
                                            const sEISPLibFIDTemplateList *templateList);

/**
 * Set up the template feature vectors and match them to feature vectors from current frames.
 * \param[In]   libHandle     library handle
 * \param[in]   featureCount  template index (less than CEISP_FID_TEMPLATE_INDEX_MAX_NBR)
 * \param[in]   IRFeatures    IRFeatures
 *  param[in]   DepthFeatures DepthFeatures
 * \param[out]  matchInfo     matchInfo;
 * \return      error code
 */

eEISPLibErrorCode EISPLibMatchFeatureVectors(EISPHandle libHandle,
                                             eispMemObjId_t  meta,
                                             size_t   featureCount,
                                             sEISPLibFeatureVector *IRFeatures,
                                             sEISPLibFeatureVector *DepthFeatures,
                                             sEISPLibMatchInfo *matchInfo);

eEISPLibErrorCode EISPLibMatchFeatureVectors2(EISPHandle libHandle,
                                              eispMemObjId_t  metaIrIn,
                                              eispMemObjId_t  metaDepthIn,
                                              size_t   featureCount,
                                              sEISPLibFeatureVector *IRFeatures,
                                              sEISPLibFeatureVector *DepthFeatures,
                                              sEISPLibMatchInfo *matchInfo);

eEISPLibErrorCode EISPLibMatchFeatureVectors_v2(EISPHandle libHandle,
                                                eispMemObjId_t  metaIrIn,
                                                eispMemObjId_t  metaDepthIn,
                                                uint32_t isFullFace,
                                                size_t   featureCount,
                                                sEISPLibFeatureVector *IRFeatures,
                                                sEISPLibFeatureVector *DepthFeatures,
                                                sEISPLibMatchInfo *matchInfo,
                                                eispMemObjId_t  irDbgData,
                                                eispMemObjId_t  depthDbgData);

eEISPLibErrorCode EISPLibMatchFeatureVectors_v3(EISPHandle libHandle,
                                                eispMemObjId_t  metaIrIn,
                                                eispMemObjId_t  metaDepthIn,
                                                uint32_t isFullFace,
                                                size_t   frameOutCount,
                                                sFrameOutputMeta *pIrFrameOut,
                                                sFrameOutputMeta *pDepthFrameOut,
                                                sEISPLibMatchInfo *matchInfo,
                                                eispMemObjId_t  irDbgData,
                                                eispMemObjId_t  depthDbgData);

eEISPLibErrorCode EISPLibMatchFinalize(EISPHandle libHandle,
                                       sEISPLibMatchInfo *matchInfo,
                                       uint32_t isAfterBioDone,
                                       eispMemObjId_t  irDbgData,
                                       eispMemObjId_t  depthDbgData);

/**
 * Control the Algorithm Match Parameter.
 * This API should only be called at most ONCE every time user switch the to new phase.
 * \param[In] libHandle   Library handle
 * \param[In] parameter   Control parameter
 */
eEISPLibErrorCode EISPLibAlgorithmConfig(EISPHandle libHandle,
                                        sEISPLibAlgorithmParameters *parameter);

/**
 * Call this API to enroll one frame of feature vectors; need multiple calls to complete enrollment
 * \param[In]   libHandle         library handle
 * \param[in]   meta              meta data mem obj
 * \param[in]   enrolledTemplate  enrolledTemplate
 * \param[in]   pIRFeatures       IRFeatures
 * \param[in]   IRFeatureCount    nbr of the IRFeatures
 *  param[in]   pDepthFeatures    DepthFeatures
 * \param[in]   DepthFeatureCount nbr of the DepthFeatures
 * \param[out]  enrollInfo        enrollment status
 * \return      error code
 */

eEISPLibErrorCode EISPLibEnrollFeatureVectors(
                                                EISPHandle libHandle,
                                                eispMemObjId_t  meta,
                                                sEISPLibFIDTemplate *enrolledTemplate,
                                                sEISPLibFeatureVector *pIRFeatures,
                                                size_t IRFeatureCount,
                                                sEISPLibFeatureVector *pDepthFeatures,
                                                size_t DepthFeatureCount,
                                                sEISPLibEnrollInfo *enrollInfo);


eEISPLibErrorCode EISPLibEnrollFeatureVectors2(
                                                EISPHandle libHandle,
                                                eispMemObjId_t  metaIrIn,
                                                eispMemObjId_t  metaDepthIn,
                                                sEISPLibFIDTemplate *enrolledTemplate,
                                                sEISPLibFeatureVector *pIRFeatures,
                                                size_t IRFeatureCount,
                                                sEISPLibFeatureVector *pDepthFeatures,
                                                size_t DepthFeatureCount,
                                                sEISPLibEnrollInfo *enrollInfo);
                                 
eEISPLibErrorCode EISPLibEnrollFeatureVectors_v2(EISPHandle libHandle,
                                                 eispMemObjId_t  metaIrIn,
                                                 eispMemObjId_t  metaDepthIn,
                                                 sEISPLibFIDTemplate *enrolledTemplate,
                                                 sEISPLibFeatureVector *pIRFeatures,
                                                 size_t IRFeatureCount,
                                                 sEISPLibFeatureVector *pDepthFeatures,
                                                 size_t DepthFeatureCount,
                                                 sEISPLibFeatureVector *pPeriocularIRFeatures,
                                                 size_t PeriocularIRFeatureCount,
                                                 sEISPLibFeatureVector *pPeriocularDepthFeatures,
                                                 size_t PeriocularDepthFeatureCount,
                                                 sEISPLibEnrollInfo *enrollInfo,
                                                 eispMemObjId_t  irDbgData,
                                                 eispMemObjId_t  depthDbgData);


eEISPLibErrorCode EISPLibEnrollFeatureVectors_v3(EISPHandle libHandle,
                                                 eispMemObjId_t  metaIrIn,
                                                 eispMemObjId_t  metaDepthIn,
                                                 sEISPLibFIDTemplate *enrolledTemplate,
                                                 sFrameOutputMeta *pIrFrameOut,
                                                 size_t IrFrameOutCount,
                                                 sFrameOutputMeta *pDepthFrameOut,
                                                 size_t DepthFrameOutCount,
                                                 sEISPLibEnrollInfo *enrollInfo,
                                                 eispMemObjId_t  irDbgData,
                                                 eispMemObjId_t  depthDbgData);


eEISPLibErrorCode EISPLibEnrollFeatureVectors_v4(EISPHandle libHandle,
                                                 eispMemObjId_t  metaIrIn,
                                                 eispMemObjId_t  metaDepthIn,
                                                 sEISPLibFIDTemplate *enrolledTemplate,
                                                 sFrameOutputMeta *pIrFrameOut,
                                                 size_t IrFrameOutCount,
                                                 sFrameOutputMeta *pDepthFrameOut,
                                                 size_t DepthFrameOutCount,
                                                 sEISPLibEnrollInfo *enrollInfo,
                                                 eispMemObjId_t  irDbgData,
                                                 eispMemObjId_t  depthDbgData,
                                                 bool isPeriocular);


eEISPLibErrorCode EISPLibEnrollFinalize(EISPHandle libHandle,
                                        sEISPLibFIDTemplate *enrolledTemplate,
                                        eispMemObjId_t  irDbgData,
                                        eispMemObjId_t  depthDbgData);


eEISPLibErrorCode EISPLibEnrollPrepareTemplateRemoval(EISPHandle libHandle,
                                                      sEISPLibFIDTemplateList *templateList,
                                                      const uuid_t enrollmentID);



eEISPLibErrorCode EISPLibEnrollFeatureVectors_Pause(EISPHandle libHandle,
                                                    bool       on);


eEISPLibErrorCode EISPLibFeatureGeneration3(EISPHandle libHandle,
                                           eispMemObjId_t  rawSensorDartIn,
                                           eispMemObjId_t  refImageDartIn,

                                           eispMemObjId_t  meta,
                                           eispMemObjId_t  rawSensor,
                                           eispMemObjId_t  refImage,

                                           eispMemObjId_t  result,
                                           eispMemObjId_t  dbgData,
                                           eispMemObjId_t  depth);

eEISPLibErrorCode EISPLibFeatureGeneration4(EISPHandle libHandle,
                                           uint64_t        userData,
                                           eispMemObjId_t  rawSensorDartIn,
                                           eispMemObjId_t  refImageDartIn,

                                           eispMemObjId_t  meta,
                                           eispMemObjId_t  rawSensor,
                                           eispMemObjId_t  refImage,

                                           eispMemObjId_t  result,
                                           eispMemObjId_t  dbgData,
                                           eispMemObjId_t  depth);

eEISPLibErrorCode EISPLibFeatureGeneration5(EISPHandle libHandle,
                                           uint64_t        userData,

                                           eispMemObjId_t  meta,
                                           eispMemObjId_t  rawSensor,
                                           eispMemObjId_t  refImage,

                                           eispMemObjId_t  result,
                                           eispMemObjId_t  dbgData,
                                           eispMemObjId_t  depth);

eEISPLibErrorCode EISPLibFeatureGeneration6(EISPHandle libHandle,
                                           uint64_t        userData,

                                           eispMemObjId_t  meta,
                                           eispMemObjId_t  rawSensor,
                                           eispMemObjId_t  refImage,

                                           eispMemObjId_t  result,
                                           eispMemObjId_t  dbgData,
                                           eispMemObjId_t  depth,
                                           eispMemObjId_t  ppdHistory);

eEISPLibErrorCode EISPLibFeatureGeneration7(EISPHandle libHandle,
                                           uint64_t        userData,

                                           eispMemObjId_t  meta,
                                           eispMemObjId_t  rawSensor,
                                           eispMemObjId_t  refImage,

                                           eispMemObjId_t  result,
                                           eispMemObjId_t  dbgData,
                                           eispMemObjId_t  depth,
                                           eispMemObjId_t  ppdHistory,
                                           bool            isPeriocular);


#define SEISPSHAIOUT_EDL_LEN    (1408*2)
typedef struct  _sEISPShaInOut{
  uint32_t  shaGenerated;
  uint32_t  key[4];
  uint32_t  hash[8];
  uint32_t  signature[8];
  uint64_t  NonceSigStatus;
  uint32_t  SensorTimeStatus;
  uint16_t  FrameCountStatus;
  uint16_t  EXT_Clock_Status;
  uint32_t  pdpCrcValue;
  uint8_t   edl[SEISPSHAIOUT_EDL_LEN];
} sEISPShaInOut;
/**
 * This API is used to copy Raw
 */
eEISPLibErrorCode EISPLibCheckRaw(EISPHandle libHandle,
                                  eispMemObjId_t  meta,
                                  uint64_t        userData,
                                  eispMemObjId_t  rawSensorDartIn,

                                  eispMemObjId_t  rawSensor,
                                  eispMemObjId_t  shaInOut,

                                  eispMemObjId_t  dbgData);

eEISPLibErrorCode EISPLibGeneralMeta(EISPHandle libHandle,
                                     eispMemObjId_t  meta,
                                     EISPLibGenericMetaInfo *metaInfo);

eEISPLibErrorCode EISPLibGeneralMeta_v2(EISPHandle libHandle,
                                     eispMemObjId_t  meta,
                                     EISPLibGenericMetaInfo *metaInfo,
                                     eispMemObjId_t dbgData);

eEISPLibErrorCode EISPLibEnrollMeta(EISPHandle libHandle,
                                    eispMemObjId_t  meta,
                                    eispMemObjId_t  irMeta,
                                    sEISPLibFIDTemplate *enrolledTemplate, // if necessary for algorithms
                                    sEISPLibEnrollMetaInfo *metaInfo);

eEISPLibErrorCode EISPLibEnrollMeta_v2(EISPHandle libHandle,
                                       eispMemObjId_t  meta,
                                       eispMemObjId_t  irMeta,
                                       sEISPLibFIDTemplate *enrolledTemplate, // if necessary for algorithms
                                       sEISPLibEnrollMetaInfo *enrollInfo,
                                       eispMemObjId_t dbgData);

eEISPLibErrorCode EISPLibVerifyMeta(EISPHandle libHandle,
                                    eispMemObjId_t  meta,
                                    eispMemObjId_t  irMeta,
                                    sEISPLibFIDTemplate *enrolledTemplate, // if necessary for algorithms
                                    sEISPLibVerifyMetaInfo *metaInfo);

eEISPLibErrorCode EISPLibVerifyMeta_v2(EISPHandle libHandle,
                                       eispMemObjId_t  meta,
                                       eispMemObjId_t  irMeta,
                                       sEISPLibFIDTemplate *enrolledTemplate, // if necessary for algorithms
                                       sEISPLibVerifyMetaInfo *metaInfo,
                                       eispMemObjId_t  dbgData);


typedef  uint64_t  eispMemObjPerm_t;
#define CEISPLIB_MEMVMPERM_RD (1 << 2) /* L4_Readable   */
#define CEISPLIB_MEMVMPERM_WR (1 << 1) /* L4_Writable   */
#define CEISPLIB_MEMVMPERM_EX (1 << 0) /* L4_eXecutable */
#define CEISPLIB_MEMVMPERM_NONE 0      /* L4_NoAccess */
#define CEISPLIB_MEMVMPERM_RW (CEISPLIB_MEMVMPERM_RD | CEISPLIB_MEMVMPERM_WR)
#define CEISPLIB_MEMVMPERM_ALL (CEISPLIB_MEMVMPERM_RW | CEISPLIB_MEMVMPERM_EX)

eispMemObjId_t  EISPLibMemObjectCreate(size_t size);
eispMemObjId_t  EISPLibMemObjectCreateWithTag(size_t size, uint32_t tag);
void *EISPLibMemObjectMap(eispMemObjId_t handle, eispMemObjPerm_t perms, uintptr_t *size);
eispMemObjId_t  EISPLibMemObjectCreateWithTag2(size_t size, uint32_t tag, uint32_t useTZ1);
eispMemObjId_t  EISPLibMemObjectCreateWithTag3(size_t size, uint32_t tag, uint32_t useTZ1, eEISPLibTZ1MemPoolType tz1MemPoolType);

eispMemObjId_t  EISPLibMemDartObjectCreate(uint64_t  dartAddr, size_t size);
#if defined(DART_64BIT)
uint64_t  EISPLibMemObjectGetDartMap(eispMemObjId_t handle, uintptr_t *size);
#else
uint32_t  EISPLibMemObjectGetDartMap(eispMemObjId_t handle, uintptr_t *size);
#endif
uint32_t  EISPLibDmaCopy(EISPHandle libHandle,
                        eispMemObjId_t  dstObj,
                        eispMemObjId_t  srcObj,
                        size_t          size);

uint32_t  EISPLibMetaDmaCopy(EISPHandle libHandle,
                        eispMemObjId_t  dstObj,
                        eispMemObjId_t  srcObj,
                        size_t          size,
                        eispMemObjId_t  dbgData);

uint32_t  EISPLibEfileDmaCopy(EISPHandle libHandle,
                        eispMemObjId_t  dstObj,
                        eispMemObjId_t  srcObj,
                        size_t          size);

uint32_t  EISPLibDcnKernelDmaCopy(EISPHandle libHandle,
                        eispMemObjId_t  dstObj,
                        eispMemObjId_t  srcObj,
                        size_t          size);

uint32_t  EISPLibRefDmaCopy(EISPHandle libHandle,
                        eispMemObjId_t  dstObj,
                        eispMemObjId_t  srcObj,
                        size_t          size);

eEISPLibErrorCode EISPLibGetFeatureMode(EISPHandle libHandle,
                                        eispMemObjId_t  irMeta,
                                        uint32_t *isFullFace);

/**
 * This API is used to set the DCN Data to the FID Algorithm
 */
eEISPLibErrorCode EISPLibSetDCNData(EISPHandle libHandle,
                                    eispMemObjId_t  dcnData);

/**
 * This API is used to test runProgram in FIDSNE
 */
eEISPLibErrorCode EISPLibRunSNEProgram(EISPHandle libHandle,
                                       eispMemObjId_t  programIn,
                                       eispMemObjId_t programOut,
                                       uint32_t programId);

/**
 * This API is used to control the Eisp Hardware
 *
 */
eEISPLibErrorCode EISPLibPowerControlEisp(EISPHandle libHandle,
                                          bool       on);

/**
 * Version2 of EISPLibPowerControlEisp() supports the secureANE
 *
 */
eEISPLibErrorCode EISPLibPowerControlEisp_v2(EISPHandle libHandle,
                                             bool       on,
                                             bool       withANE);

/**
 * Debugging level enumeration, the debugging level is compared
 * to these enumerations to decide if the log will be processed:
 * an entry will be logged only if the passed level is equal of
 * greater than the current threshold.
 */
typedef enum {

    eEISPLib_DBG_LVL_CRIT = 0, /*!< Critical messages, always logged. */
    eEISPLib_DBG_LVL_ERR = 10, /*!< Error message threshold. */
    eEISPLib_DBG_LVL_CHECKPOINT = 30, /*!< Checking Point */
    eEISPLib_DBG_LVL_MSG = 50, /*!< Normal message threshold. */

    eEISPLib_DBG_LVL_TRACE = 200,
    eEISPLib_DBG_LVL_TRACE_ENTER = 210, /*!< Debugging tracing threshold including function entering logs. */
    eEISPLib_DBG_LVL_TRACE_EXIT = 220, /*!< Debugging tracing threshold including function entering and exiting logs. */
    eEISPLib_DBG_LVL_VERBOSE = 255 /*!< Log everything. */

} eEISPLib_DBG_LVL;

/**
 * This API is used to set the Console Logging Debug Level
 */
eEISPLibErrorCode	EISPLibSetConsoleDebugLevel( EISPHandle libHandle,
																							 uint32_t		dbgLevel);



/**
 * This API is used to get total size of per-frame debug data given the input of sectionCtrl bit mask
 *
 */
eEISPLibErrorCode EISPLibGetDebugInfoTotalSize(EISPHandle libHandle, uint32_t sectionCtrl, uint32_t* size);

/**
 * This API is used to initialize per-frame debug data given the input of sectionCtrl bit mask
 *
 */
eEISPLibErrorCode EISPLibInitDebugInfo(EISPHandle libHandle, uint32_t sectionCtrl, eispMemObjId_t dbgData);

/**
 * This API is used to get online Template
 *
 */
eEISPLibErrorCode EISPLibGetOnlineTemplate(EISPHandle libHandle,
                                           uint32_t *isOnlineTemplateUpdated,
                                           sEISPLibFIDTemplate *onlineTemplate);


eEISPLibErrorCode EISPLibGetOnlineTemplate_v2(EISPHandle libHandle,
                                              uint32_t *isOnlineTemplateUpdated,
                                              sEISPLibFIDTemplate *onlineTemplate,
                                              eispMemObjId_t  irDbgData,
                                              eispMemObjId_t  depthDbgData);

eEISPLibErrorCode EISPLibGetUpdatedTemplates(EISPHandle libHandle,
                                             uint32_t *isOnlineTemplateUpdated,
                                             uint32_t *isShortTermTemplateUpdated,
                                             sEISPLibFIDTemplate *updatedTemplate,
                                             eispMemObjId_t  irDbgData,
                                             eispMemObjId_t  depthDbgData);

eEISPLibErrorCode EISPLibGetUpdatedTemplates_v2(EISPHandle libHandle,
                                                uint32_t *isOnlineTemplateUpdated,
                                                uint32_t *isShortTermTemplateUpdated,
                                                uint32_t *isSafeUpdate,
                                                uint32_t *isPasscodeUpdate,
                                                uint32_t *isShortTermMoved,
                                                sEISPLibFIDTemplate *updatedTemplate,
                                                eispMemObjId_t  irDbgData,
                                                eispMemObjId_t  depthDbgData);

/**
 * Get Updated Templates for multi-enrollment
 * isTemplateUpdated
 * isShortTermTemplateUpdated, array of uint8_t[numEnrollments]
 * isSafeUpdate, array of uint8_t[numEnrollments]
 * isPasscodeUpdate, array of uint8_t[numEnrollments]
 * isShortTermMoved, array of uint8_t[numEnrollments]
 * templateCount in sEISPLibFIDTemplateList should match with input in EISPLibMatchSetTemplate()
 * numEnrollments should match with input in EISPLibMatchSetTemplate call
 */
eEISPLibErrorCode EISPLibGetUpdatedTemplates_v3(EISPHandle libHandle,
                                                uint8_t *isTemplateUpdated,
                                                uint8_t *isSafeUpdate,
                                                uint8_t *isPasscodeUpdate,
                                                uint8_t *isShortTermMoved,
                                                sEISPLibFIDTemplateList *sEISPLibFIDTemplateList,
                                                eispMemObjId_t  irDbgData,
                                                eispMemObjId_t  depthDbgData,
                                                uint32_t numEnrollments);

eEISPLibErrorCode EISPLibGetUpdatedSimilarityTag(EISPHandle libHandle,
                                                 uint8_t *isSimilarityTagUpdated,
                                                 sEISPLibFIDSimilarityTag *similarityTag,
                                                 eispMemObjId_t  irDbgData,
                                                 eispMemObjId_t  depthDbgData);

eEISPLibErrorCode EISPLibGetTraceObject(EISPHandle libHandle,
                                        eispMemObjId_t  *pTraceObj);

eEISPLibErrorCode EISPLibMigrateTemplate(EISPHandle libHandle,
                                         void *inTemplate,
                                         uint32_t inTemplateSize,
                                         void *outTemplate,
                                         uint32_t outTemplateSize,
                                         eEISPLibMigrateTemplateFeedback *feedback,
                                         eispMemObjId_t  inDbgData,
                                         eispMemObjId_t  outDbgData);

#define MAX_TRACE_OBJ_SIZE  (2048*2*144)
uint32_t EISPLibGetTraceObjectSize(void);

#ifdef __cplusplus
};
#endif
#endif /* CEISPLIB_H_ */
