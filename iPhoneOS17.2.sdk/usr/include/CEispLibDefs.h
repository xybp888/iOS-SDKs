/**
 * \file CEispLibDefs.h
 *
 * \brief Include file for \ref CEispLib class.
 *
 * This file includes the definition for the \ref CEispLib class.
 *
 * - Copyright(c) 2011 Apple Inc. All rights reserved.
 *
 */

#ifndef CEISPLIBDEFS_H_
#define CEISPLIBDEFS_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Structure and union packing.  All structures in this file are meant to be
 * transferred, and need to be packed to be 32-bit compatible.
 */
#pragma pack(push,4)

#define   EISPLIBVERS   "Eisp-81.0.21.1"
/**
 * Debug Info Definition version number
  */

#define CEISPLIB_DEBUG_INFO_VERSION (0x00000069)

/**
 * FW Common Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_COMMON_VERSION (0x00000019)


/**
 * FW Common Sensitive Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_COMMONSENSITIVE_VERSION (0x00000019)


/**
 * FW FeatureGen Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_FEAGEN_VERSION (0x00000007)


/**
 * FW SHA Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_SHA_VERSION (0x00000001)


/**
 * FW CropFrame Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_CROPFRAME_VERSION (0x00000004)


/**
 * FW DepthFrame Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_DEPTHFRAME_VERSION (0x00000003)


/**
 * Vispipe Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_VISPIPE_VERSION (0x00000001)

/**
 * PDE Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_PDE_VERSION (0x00000009)

/**
 * Algorithm Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_ALG_VERSION (0x00000012)

/**
 * PDE Probe Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_PDE_PROBE_VERSION (0x00000002)

/**
 * FW Template Info Definition version number
 */

#define CEISPLIB_FW_TEMPLATE_VERSION (0x0000000C)

/**
 * HostMeta HostMeta Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_HOSTMETA_VERSION (0x00000001)

/**
 * HostMeta HostMeta Debug Info Definition version number
 */

#define CEISPLIB_DEBUG_INFO_FW_FLOWDBG_VERSION (0x00000003)


/**
 * Debug info data structure enumeration, used to retrieve the correct structure
 * offset within the \ref sCEIspLibDebugInfo structure.
 * \note The name of this enum must not be changed in any case. Otherwise it
 * will break the header parsing. Moreover each element in the
 * enum must have an associated comment with the format "text \ref myStruct
 * structure text" where myStruct refers to the structure name describing the
 * meta-data at that index.
 * A new section should be inserted at the end !!!
 */
enum eCEISPLibDebugInfoField
{
    CEISPLIB_DEBUG_INFO_FW_COMMON             = 0,  /*!< ID for \ref sEispLibDbgInfoFwCommon structure */
    CEISPLIB_DEBUG_INFO_FW_COMMONSENSITIVE    = 1,  /*!< ID for \ref sEispLibDbgInfoFwCommonSensitive structure */
    CEISPLIB_DEBUG_INFO_FW_FEAGEN             = 2,  /*!< ID for \ref sEispLibDbgInfoFwFeaGen structure */
    CEISPLIB_DEBUG_INFO_FW_SHA                = 3,  /*!< ID for \ref sEispLibDbgInfoFwSha structure */
    CEISPLIB_DEBUG_INFO_FW_CROPFRAME          = 4,  /*!< ID for \ref sEispLibDbgInfoFwCropFrame structure */
    CEISPLIB_DEBUG_INFO_FW_DEPTHFRAME         = 5,  /*!< ID for \ref sEispLibDbgInfoFwDepthFrame structure. */
    CEISPLIB_DEBUG_INFO_FW_VISPIPE            = 6,  /*!< ID for \ref sEispLibDbgInfoFwVisPipe structure */
    CEISPLIB_DEBUG_INFO_FW_PDE                = 7,  /*!< ID for \ref sEispLibDbgInfoFwPde structure */
    CEISPLIB_DEBUG_INFO_ALG                   = 8,  /*!< ID for \ref sEispLibDbgInfoAlg structure */
    CEISPLIB_DEBUG_INFO_FW_PDE_PROBE          = 9,  /*!< ID for \ref sEispLibDbgInfoFwPdeProbe structure */
    CEISPLIB_DEBUG_INFO_FW_HOST_META          = 10, /*!< ID for \ref sEispLibDbgInfoFwHostMeta structure */
    CEISPLIB_DEBUG_INFO_FW_FLOW_DBG           = 11, /*!< ID for \ref sEispLibDbgInfoFwFlowDBG structure */
    CEISPLIB_DEBUG_INFO_TOT /*!< Total number of debug info shared structures. */
};

typedef struct _sEispLibDbgInfoShared
{
    uint32_t version; /*!< Debug info version. */
    uint32_t frameCount; /*!< Frame's s progressive count */
    uint32_t sectionCtrl; /*!< Bitmask for which sections are enabled */
    uint32_t totDescriptors; /*!< Total number of debug info structures. */
    uint32_t totSize;
    uint32_t resv;
    uint64_t timeStamp; /*!< Image capture time-stamp. */
    uint32_t offsets[0]; /*!< Variable length array of debug info structures.
    This array length is given by the 'totDescriptors' field.  If not 0,
    the n-th offset value represents the byte offset of the n-th structure
    relative to the start address of this structure.  If 0, the n-th structure
    is not present.  The type of the n-th structure is implicitly defined by
    the n index.  e.g the offset at \ref CEISPLIB_DEBUG_INFO_ALG index refers to the
    algorithm debug structure (\ref sEispLibDbgInfoAlg). */
} sEispLibDbgInfoShared;


/**
 * Return indexed debug info block.
 */

#define CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH 32
#define CEISPLIB_DCN_BUILD_COMMIT_MAX_LENGTH 32

#define CEISPLIB_FID_NUM_FEATURES_IN_ENROLL_MAX    (9)
#define CEISPLIB_FID_NUM_FEATURES_IN_ONLINE_MAX    (41)
#define CEISPLIB_FID_NUM_FEATURES_IN_SHORTTERM_MAX (20)
#define CEISPLIB_FID_NUM_FEATURES_IN_MULTIUSER_SHORTTERM_MAX (20)
#define CEISPLIB_FID_FEATURE_LEN_MAX               (128)
#define CEISPLIB_FID_ANTISPOOF_FEATURE_LEN_MAX     (2)
#define CEISPLIB_FID_ASDEPTH_FEATURE_LEN_MAX       (2)
#define CEISPLIB_FID_SCENEMATCHER_FEATURE_LEN_MAX  (2)

#define CEISPLIB_FID_STRIDE(s,type)   (((s)*sizeof(type) + 63)>>6<<6)

#define CEISPLIB_FID_RESIZEOUTPUT_SIZE_WIDTH          (128)
#define CEISPLIB_FID_RESIZEOUTPUT_SIZE_HEIGHT         (128)
#define CEISPLIB_FID_RESIZEOUTPUT_SIZE                (CEISPLIB_FID_RESIZEOUTPUT_SIZE_HEIGHT * CEISPLIB_FID_STRIDE(CEISPLIB_FID_RESIZEOUTPUT_SIZE_WIDTH, uint16_t))


#define CEISPLIB_FID_NORMOUTPUT_SIZE_WIDTH            (120)
#define CEISPLIB_FID_NORMOUTPUT_SIZE_HEIGHT           (120)
#define CEISPLIB_FID_NORMOUTPUT_SIZE                  (CEISPLIB_FID_NORMOUTPUT_SIZE_HEIGHT * CEISPLIB_FID_STRIDE(CEISPLIB_FID_NORMOUTPUT_SIZE_WIDTH, uint16_t))

#define CEISPLIB_AS_RESIZEOUTPUT_SIZE_WIDTH           (136)
#define CEISPLIB_AS_RESIZEOUTPUT_SIZE_HEIGHT          (136)
#define CEISPLIB_AS_RESIZEOUTPUT_SIZE                 (CEISPLIB_AS_RESIZEOUTPUT_SIZE_HEIGHT * CEISPLIB_FID_STRIDE(CEISPLIB_AS_RESIZEOUTPUT_SIZE_WIDTH, uint16_t))

#define CEISPLIB_AS_NORMOUTPUT_SIZE_WIDTH             (128)
#define CEISPLIB_AS_NORMOUTPUT_SIZE_HEIGHT            (128)
#define CEISPLIB_AS_NORMOUTPUT_SIZE                   (CEISPLIB_AS_NORMOUTPUT_SIZE_HEIGHT * CEISPLIB_FID_STRIDE(CEISPLIB_AS_NORMOUTPUT_SIZE_WIDTH, uint16_t))

#define CEISPLIB_ASDEPTH_RESIZEOUTPUT_SIZE_WIDTH      (128)
#define CEISPLIB_ASDEPTH_RESIZEOUTPUT_SIZE_HEIGHT     (128)
#define CEISPLIB_ASDEPTH_RESIZEOUTPUT_SIZE            (CEISPLIB_ASDEPTH_RESIZEOUTPUT_SIZE_HEIGHT * CEISPLIB_FID_STRIDE(CEISPLIB_ASDEPTH_RESIZEOUTPUT_SIZE_WIDTH, uint16_t))

#define CEISPLIB_ASDEPTH_NORMOUTPUT_SIZE_WIDTH        (128)
#define CEISPLIB_ASDEPTH_NORMOUTPUT_SIZE_HEIGHT       (128)
#define CEISPLIB_ASDEPTH_NORMOUTPUT_SIZE              (CEISPLIB_ASDEPTH_NORMOUTPUT_SIZE_HEIGHT * CEISPLIB_FID_STRIDE(CEISPLIB_ASDEPTH_NORMOUTPUT_SIZE_WIDTH, uint16_t))

#define CEISPLIB_SCENEMAT_RESIZEOUTPUT_SIZE_WIDTH      (256)
#define CEISPLIB_SCENEMAT_RESIZEOUTPUT_SIZE_HEIGHT     (128)
#define CEISPLIB_SCENEMAT_RESIZEOUTPUT_SIZE            (CEISPLIB_SCENEMAT_RESIZEOUTPUT_SIZE_HEIGHT * CEISPLIB_FID_STRIDE(CEISPLIB_SCENEMAT_RESIZEOUTPUT_SIZE_WIDTH, uint16_t))

#define CEISPLIB_SCENEMAT_NORMOUTPUT_SIZE_WIDTH        (256)
#define CEISPLIB_SCENEMAT_NORMOUTPUT_SIZE_HEIGHT       (128)
#define CEISPLIB_SCENEMAT_NORMOUTPUT_SIZE              (CEISPLIB_SCENEMAT_NORMOUTPUT_SIZE_HEIGHT * CEISPLIB_FID_STRIDE(CEISPLIB_SCENEMAT_NORMOUTPUT_SIZE_WIDTH, uint16_t))

#define CEISPLIB_FID_NUM_PITCH_BINS                   (3)
#define CEISPLIB_FID_NUM_YAW_BINS                     (3)

#define CEISPLIB_DEPTHFRAME_WIDTH                     (128)
#define CEISPLIB_DEPTHFRAME_HEIGHT                    (128)
#define CEISPLIB_DEPTHFRAME_SIZE                      (CEISPLIB_DEPTHFRAME_HEIGHT * CEISPLIB_FID_STRIDE(CEISPLIB_DEPTHFRAME_WIDTH, uint16_t))

#define CEISPLIB_VISPIPEOUT_WIDTH                     (136)
#define CEISPLIB_VISPIPEOUT_HEIGHT                    (136)

#define CEISPLIB_PDE_DEPTH_WIDTH                      (136)
#define CEISPLIB_PDE_DEPTH_HEIGHT                     (136)

#define CEISPLIB_NUMBER_OF_TRACE_PER_FRAME            (256)
#define CEISPLIB_MAX_TRACE_BUFFER_ITEM_SIZE           (128)

#define CEISPLIB_SPARSE_DXY_WIDTH                     (488)
#define CEISPLIB_SPARSE_DXY_HEIGHT                    (528)
#define CEISPLIB_DENSE_DXY_WIDTH                      (608)
#define CEISPLIB_DENSE_DXY_HEIGHT                     (656)
#define CEISPLIB_DXY_STRIDE                           (1216)
#define CEISPLIB_SPARSE_DXY_SIZE                      (CEISPLIB_SPARSE_DXY_HEIGHT*CEISPLIB_DXY_STRIDE)
#define CEISPLIB_DENSE_DXY_SIZE                       (CEISPLIB_DENSE_DXY_HEIGHT*CEISPLIB_DXY_STRIDE)
#define CEISPLIB_DXY_BUFFER_SIZE                      (CEISPLIB_DENSE_DXY_SIZE>CEISPLIB_SPARSE_DXY_SIZE)?CEISPLIB_DENSE_DXY_SIZE:CEISPLIB_SPARSE_DXY_SIZE

#define CEISPLIB_NUM_AS_PERCENTILES                   (8)
#define CEISPLIB_NUM_AS_TEMPLATEIMPL                  (1)

#define CEISPLIB_PPD_HISTORY_BUFFER_SIZE              (8020)

#define   CEISPLIB_UUID_SIZE 16
#ifndef UUID_DEFINED
    typedef uint8_t uuid_t[CEISPLIB_UUID_SIZE];
#define UUID_DEFINED
#endif

#define CEISPLIB_HOSTMETA_MAX_SIZE                    (32*1024)

#define CEISPLIB_MAX_VERIFICATION_FRAMES              (5)

#define CEISPLIB_MAX_ENROLLMENT_NUMBER                (2)
#define CEISPLIB_MAX_FULLFACE_TEMPLATEID              (1)
#define CEISPLIB_MAX_FULLFACE_USERID_NUMBER           (6)
#define CEISPLIB_MAX_PERIOCULAR_TEMPLATEID            (1)
#define CEISPLIB_MAX_PERIOCULAR_GLASSES_TEMPLATEID    (4)
#define CEISPLIB_MAX_FULLFACE_TEMPLATE_NUMBER         (CEISPLIB_MAX_ENROLLMENT_NUMBER*CEISPLIB_MAX_FULLFACE_TEMPLATEID*CEISPLIB_MAX_FULLFACE_USERID_NUMBER)
#define CEISPLIB_MAX_PERIOCULAR_TEMPLATE_NUMBER       (CEISPLIB_MAX_ENROLLMENT_NUMBER*CEISPLIB_MAX_PERIOCULAR_TEMPLATEID + CEISPLIB_MAX_PERIOCULAR_GLASSES_TEMPLATEID)
#define CEISPLIB_MAX_TEMPLATE_NUMBER                  (CEISPLIB_MAX_PERIOCULAR_TEMPLATE_NUMBER)

typedef enum  _eEISPLibErrorCode{
  eEISPLibErrorCode_None                              = 0,
  eEISPLibErrorCode_START_BIO_CAPTURE                 = 1,
  eEISPLibErrorCode_ERROR_NO_FACE_DETECTED            = 0x2,
  eEISPLibErrorCode_ERROR_MULTIPLE_FACES              = 0x4,
  eEISPLibErrorCode_ERROR_FACE_OUT_FOV                = 0x8,
  eEISPLibErrorCode_ERROR_FACE_TOO_CLOSE              = 0x10,
  eEISPLibErrorCode_ERROR_FACE_TOO_FAR                = 0x20,
  eEISPLibErrorCode_ERROR_POSE_OUT_RANGE              = 0x40,
  eEISPLibErrorCode_ERROR_POSE_BIN_COVERED            = 0x80,
  eEISPLibErrorCode_ERROR_FACE_OCCLUDED               = 0x100,
  eEISPLibErrorCode_ERROR_ENROLLMENT_NOT_COMPLETED    = 0x200,
  eEISPLibErrorCode_ERROR_ENROLLMENT_NOT_FINALIZED    = 0x400,
  eEISPLibErrorCode_ERROR_OUT_OF_MEMORY               = 0x800,
  eEISPLibErrorCode_ERROR_HW_ERROR                    = 0x1000,
  eEISPLibErrorCode_ERROR_INTERNAL                    = 0x2000,
  eEISPLibErrorCode_ERROR_TOO_MANY_FEATURES           = 0x4000,
  eEISPLibErrorCode_ERROR_NOT_INITIALIZED             = 0x8000,
  eEISPLibErrorCode_ERROR_NOT_ATTENDING               = 0x10000,
  eEISPLibErrorCode_ERROR_INVALID                     = 0x20000,
  eEISPLibErrorCode_ERROR_INVALID_ATTENTION           = 0x40000,
  eEISPLibErrorCode_ERROR_INVALID_LANDMARKS           = 0x80000,
  eEISPLibErrorCode_ERROR_INVALID_OCCLUSION           = 0x100000,
  eEISPLibErrorCode_ERROR_UPPER_FACE_OCCLUDED         = 0x200000,
  eEISPLibErrorCode_ERROR_LOWER_FACE_OCCLUDED         = 0x400000,
  eEISPLibErrorCode_ERROR_ANTISPOOF_NOT_PASSED        = 0x800000,
  eEISPLibErrorCode_ERROR_ENROLL_IDENTITY_CHANGE      = 0x1000000,
  eEISPLibErrorCode_ERROR_TWO_IDENTIIES_SUSPICIOUS    = 0x2000000,
  eEISPLibErrorCode_ERROR_INCORRECT_VERSION           = 0x4000000,
  eEISPLibErrorCode_ERROR_DEPTHHOLES                  = 0x8000000,
  eEISPLibErrorCode_ERROR_INVALID_PLATFORM            = 0x10000000,
  eEISPLibErrorCode_ERROR_DUPLICATE_ENROLL_ID         = 0x20000000,
  eEISPLibErrorCode_ERROR_MISMATCH_SESSION_TYPE       = 0x40000000,
  eEISPLibErrorCode_Reserved                          = 0x80000000,
  eEISPLibErrorCode_Parameter_Error                   = 0x80000001,
  eEISPLibErrorCode_OUT_OF_MEMORY                     = 0x80000002,
  eEISPLibErrorCode_NO_CALLBACK                       = 0x80000003,
  eEISPLibErrorCode_NOT_INITIALIZED                   = 0x80000004,
  eEISPLibErrorCode_NOT_SUPPORTED                     = 0x80000005,
  eEISPLibErrorCode_GeneralError                      = 0x80000006,
  eEISPLibErrorCode_memObjectMap_Error                = 0x80000007,
  eEISPLibErrorCode_Parameter_Error_InvalidMemObj     = 0x80000008,
  eEISPLibErrorCode_Parameter_Error_NullLibHandle     = 0x80000009,
  eEISPLibErrorCode_Parameter_Error_HostMetaDescrip   = 0x8000000A,
  eEISPLibErrorCode_Parameter_Error_HostMetaOffsets   = 0x8000000B,
  eEISPLibErrorCode_Parameter_Error_HostMetaCRC       = 0x8000000C,
  eEISPLibErrorCode_Parameter_Error_FDNull            = 0x8000000D,
  eEISPLibErrorCode_Parameter_Error_FDInvalidData     = 0x8000000E,
  eEISPLibErrorCode_Parameter_Error_FDTooManyResults  = 0x80000010,
  eEISPLibErrorCode_Parameter_Error_SharedInputNull   = 0x80000011,
  eEISPLibErrorCode_Parameter_Error_AENull            = 0x80000012,
  eEISPLibErrorCode_Parameter_Error_ProjectorNull     = 0x80000013,
  eEISPLibErrorCode_Parameter_Error_AttnNull          = 0x80000014,
  eEISPLibErrorCode_Parameter_Error_AttnInvalidData   = 0x80000015,
  eEISPLibErrorCode_Parameter_Error_PdeNull           = 0x80000016,
  eEISPLibErrorCode_Parameter_Error_FDTooManyChosenResults  = 0x80000017,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaLibHandle    = 0x80000020,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaDstMemObj    = 0x80000021,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaSrcMemObj    = 0x80000022,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaDstDartObj   = 0x80000023,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaSrcDartObj   = 0x80000024,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaSize         = 0x80000025,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaDstObjNull   = 0x80000026,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaSrcObjNull   = 0x80000027,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaDstObjSize   = 0x80000028,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaSrcObjSize   = 0x80000029,
  eEISPLibErrorCode_Parameter_Error_InvalidMetaRetried      = 0x8000002A,
  eEISPLibErrorCode_Parameter_Error_InvalidMeta2nd          = 0x8000002B,
  eEISPLibErrorCode_OUT_OF_RESOURCE                         = 0x8000002C,
  eEISPLibErrorCode_Parameter_Error_NoIrAsFeature           = 0x8000002D,
  eEISPLibErrorCode_Parameter_Error_NoDepthAsFeature        = 0x8000002E,
  eEISPLibErrorCode_Parameter_Error_FrameOutCountNotOne     = 0x8000002F,
  eEISPLibErrorCode_ERROR_InvalidPhaseFeatureGeneration     = 0x80000100,
  eEISPLibErrorCode_ANEPowerLockFailed                      = 0x80000200,
  eEISPLibErrorCode_ANEPowerUnlockFailed                    = 0x80000201,
  eEISPLibErrorCode_NonSecureToSecureHang                   = 0x80000202,
  eEISPLibErrorCode_SecureNetworkHang                       = 0x80000203,
  eEISPLibErrorCode_SecureToNonSecureHang                   = 0x80000204,
  eEISPLibErrorCode_ReservedEnd,
  eEISPLibErrorCode_ReservedNonFatal                  = 0x80010000,
  eEISPLibErrorCode_CachedRequestRelease              = 0x80010001,
  eEISPLibErrorCode_ReservedNonFatalEnd
} eEISPLibErrorCode;

/**
 * Return is non-zero when the EISPLibErrorCode is fatal.
 */
#define CEISPLIB_ERROR_CODE_IS_FATAL(err) \
      ((err & eEISPLibErrorCode_ERROR_OUT_OF_MEMORY) || \
       (err & eEISPLibErrorCode_ERROR_HW_ERROR) || \
       (err & eEISPLibErrorCode_ERROR_INTERNAL) || \
       (err & eEISPLibErrorCode_ERROR_NOT_INITIALIZED) || \
       (err & eEISPLibErrorCode_ERROR_ENROLL_IDENTITY_CHANGE) || \
       ((err > eEISPLibErrorCode_Reserved) && (err < eEISPLibErrorCode_ReservedEnd)))

typedef enum _eFIDPhaseID
{
  eFIDSessionIDFID_None = 0,
  eFIDSessionIDFID_Enrollment = 1,
  eFIDSessionIDFID_FaceMatching = 2,  // doublet biometric face matching
  eFIDSessionIDFID_Secret = 3,
  eFIDSessionIDFID_PasscodeChanllenge = 4,
  eFIDSessionIDFID_TemplateMigration = 5,
  eFIDSessionIDFID_FasterPath = 6,
} eFIDPhaseID;

typedef enum _eEispLibMatchSubtype
{
  eEispLibMatchSubtype_Insession = 0,
  eEispLibMatchSubtype_PreEnrollment = 1,
  eEispLibMatchSubtype_MultiUser = 2,
} eEispLibMatchSubtype;

typedef enum _eFIDEnrollmentType
{
  eFIDEnrollmentType_Fullface = 0,
  eFIDEnrollmentType_Periocular = 1,
  eFIDEnrollmentType_Fullface_Periocular = 2,
} eFIDEnrollmentType;

typedef enum _eEispLibFidGlassesMode
{
   eEispLibFidGlasses_Allowed = 0,
   eEispLibFidGlasses_Required,
   eEispLibFidGlasses_Prohibited,
   eEispLibFidGlasses_Modes_ToT
} eEispLibFidGlassesMode;

typedef struct _sEISPLibSessionSetting
{
  eFIDPhaseID             type;
  eEispLibMatchSubtype    matchSubType;
  uint32_t                userID;
  uuid_t                  enrollmentID;
  uint32_t                token;
  bool                    disableAntispoof;
  bool                    disableAttention;
  uint32_t                minAttentionCount;
  bool                    isPeriocular;
  uint32_t                templateID;
  eEispLibFidGlassesMode  glassesRequirement;
} sEISPLibSessionSetting;

typedef enum _eEispLibFidFwTraceType
{
  eEispLibFidFwFuncActionType_Enter = 0x0,
  eEispLibFidFwFuncActionType_Exit,
  eEispLibFidFwFuncActionType_Proc,
  eEispLibFidFwFuncActionType_Error,
  eEispLibFidFwFuncActionType_MAX,
} eEispLibFidFwTraceType;

typedef enum _eEISPLibPrf1EntryType
{
  eEISPLibPRF1TYPE_SPARSE = 0,
  eEISPLibPRF1TYPE_SPARSE_LOW_POWER,
  eEISPLibPRF1TYPE_DENSE,
  eEISPLibPRF1TYPE_DENSE_LOW_POWER,
  eEISPLibPRF1TYPE_NBR
} eEISPLibPrf1EntryType;

typedef struct _sEispLibFidFwTraceInfo
{
  uint32_t type;    //eEispLibFidFwTraceType
  uint64_t timeStamp;
  uint8_t  buf[CEISPLIB_MAX_TRACE_BUFFER_ITEM_SIZE];
} sEispLibFidFwTraceInfo;

typedef struct _sEispLibFidFwDetectorRect
{
  int32_t x;
  int32_t y;
  uint32_t width;
  uint32_t height;
} sEispLibFidFwDetectorRect;

typedef enum _eEispLibFidFwPrimitiveOrientation {
  EispLibFidFw_kPortrait,
  EispLibFidFw_kLandscapeLeft,
  EispLibFidFw_kLandscapeRight,
  EispLibFidFw_kUpsideDownPortrait,
} eEispLibFidFwPrimitiveOrientation;

typedef struct _sEispLibFidFwPrimitiveMetaData {
  uint64_t groupId;
  uint64_t frameId;
  uint16_t captureMode;
  uint16_t frameType;
  int32_t faceBoxX;
  int32_t faceBoxY;
  uint32_t faceBoxWidth;
  uint32_t faceBoxHeight;
  uint32_t frameWidth;
  uint32_t frameHeight;
  float yaw;
  float pitch;
  float roll;
  uint32_t distance;
  uint32_t numFaces;
  uint16_t attention;
  float occlusionMap[12][12];
  uint32_t errorCode;
  uint32_t probingPattern;
  eEispLibFidFwPrimitiveOrientation orientation;
  uint32_t hasOcclusion;
  uint32_t occlusionAreas;
  uint32_t hasGlasses;
  uint32_t hasEyeOcclusion;
  uint32_t hasNoGlasses;
  uint32_t hasTransparentGlasses;
  uint32_t hasUnsupportedGlassesForLearning;
  uint32_t hasRelaxedOcclusion;
  uint32_t hasUnsupportedGlassesForUnlock;
  uint16_t realAttention;
} sEispLibFidFwPrimitiveMetaData;

typedef struct _sEispLibFidFwVerifyScore {
  float irScore;
  float depthScore;
  float irOnlineScore;
  float depthOnlineScore;
  float irShortTermScore;
  float depthShortTermScore;
  float overallScore;
  float overallOnlineScore;
  float overallShortTermScore;
  float antispoofDottedIrScore;
  float antispoofFloodIrScore;
  float antispoofDepthScore;
  float sceneMatcherScore;
  float antispoofOverallScore;
  float antispoofFusedScoreMinusThresh;
} sEispLibFidFwVerifyScore;

typedef enum _eEispLibFidFwFeatureSource {
  EispLibFidFw_kFeatureSourceEnrollment,
  EispLibFidFw_kFeatureSourceSafeUpdate,
  EispLibFidFw_kFeatureSourceShortTermMemory,
}eEispLibFidFwFeatureSource;


typedef struct _sEISPLibMatcherFeature {
    float     feat[CEISPLIB_FID_FEATURE_LEN_MAX];
    uint64_t  frameId;
    eEispLibFidFwFeatureSource source;
    uint16_t  unlockCount;
    uint16_t  uniqueUnlockCount;
    uint16_t  lifetime;
    uint8_t   valid;
} sEISPLibMatcherFeature;

typedef struct _sEISPLibFwPrimitiveShortTermFeature {
    float irFeat[CEISPLIB_FID_FEATURE_LEN_MAX];
    float depthFeat[CEISPLIB_FID_FEATURE_LEN_MAX];
    uint64_t frameIdIR;
    uint64_t frameIdDepth;
    uint16_t unlockCount;
    uint16_t uniqueUnlockCount;
    uint16_t lifetime;
    uint8_t valid;
} sEISPLibFwPrimitiveShortTermFeature;

typedef struct _sEISPLibFwPrimitiveShortTermMemory {
  sEISPLibFwPrimitiveShortTermFeature memory[CEISPLIB_FID_NUM_FEATURES_IN_SHORTTERM_MAX];
  uint32_t userId;
} sEISPLibFwPrimitiveShortTermMemory;

typedef struct _sEISPLibFwPrimitiveMultiUserShortTermMemory {
  sEISPLibFwPrimitiveShortTermFeature memory[CEISPLIB_FID_NUM_FEATURES_IN_MULTIUSER_SHORTTERM_MAX];
} sEISPLibFwPrimitiveMultiUserShortTermMemory;

typedef struct _sEispLibFidFwThreshold {
    float matchThreshold;
    float onlineThreshold;
    float shortTermThreshold;
    float antispoofThreshold;
    float safeUpdateThreshold;
    float onlineUpdateThreshold;
    float passCodeThreshold;
    float onlinePassCodeThreshold;
    float passCodeAntispoofThreshold;
    float maxIRScore;
    float maxDepthScore;
    float maxDepthUnlockScore;
    float minIRScore;
    float minDepthScore;
} sEispLibFidFwThreshold;

typedef struct _sEISPLibAsTemplateBuf {
  float p_ext[CEISPLIB_NUM_AS_PERCENTILES];
  float q_ext[CEISPLIB_NUM_AS_PERCENTILES];
  float n_ext[CEISPLIB_NUM_AS_PERCENTILES];
} sEISPLibAsTemplateBuf;

typedef struct _sEISPLibMarginFunction {
  uint32_t timeElapsed;
  float base;
  float margin;
} sEISPLibMarginFunction;

typedef struct _sEISPLibAsTemplateImpl {
  sEISPLibAsTemplateBuf all;
  sEISPLibAsTemplateBuf pass;
  sEISPLibMarginFunction enrollMargin;
  sEISPLibMarginFunction passcodeMargin;
  float threshold;
} sEISPLibAsTemplateImpl;

typedef struct _sEISPLibAsTemplate {
  sEISPLibAsTemplateImpl tempImpl[CEISPLIB_NUM_AS_TEMPLATEIMPL];
  uint32_t len;
} sEISPLibAsTemplate;


typedef struct _sEISPLibFwDetectorOcStorage {
  uint64_t version;
  float attentionScoreThreshScale;
  float irDistScale;
  float irDistOffset;
  uint32_t count; ///< meta data; number of processed frames
  uint32_t attnCount; ///< meta data; number of frames hasAttention is true
  uint32_t fdPairCount; ///< meta data; number of frames both face detectors have results
  uint8_t reserved[96];
} sEISPLibFwDetectorOcStorage;


typedef struct  _sEISPLibFIDTemplate{
  uint32_t                version;

  uint32_t                userID;
  uuid_t                  identityUUID;

  //static
  sEISPLibMatcherFeature  irTemplateBuf[CEISPLIB_FID_NUM_FEATURES_IN_ENROLL_MAX];
  uint32_t                irTemplateLen;
  sEISPLibMatcherFeature  depthTemplateBuf[CEISPLIB_FID_NUM_FEATURES_IN_ENROLL_MAX];
  uint32_t                depthTemplateLen;
  sEispLibFidFwThreshold  threshFullFace;
  float                   antispoofThreshold;  //deprecated

  sEISPLibAsTemplate      asTemplateFullFace;
  sEISPLibFwDetectorOcStorage   detectorOcStorage; //deprecated

  //online
  sEISPLibMatcherFeature  onlineIrTemplateBuf[CEISPLIB_FID_NUM_FEATURES_IN_ONLINE_MAX];
  uint32_t                onlineIrTemplateLen;
  sEISPLibMatcherFeature  onlineDepthTemplateBuf[CEISPLIB_FID_NUM_FEATURES_IN_ONLINE_MAX];
  uint32_t                onlineDepthTemplateLen;
  sEispLibFidFwThreshold  onlineThreshFullFace;

  sEISPLibAsTemplate      onlineAsTemplateFullFace;
  sEISPLibFwDetectorOcStorage   onlineDetectorOcStorage; //deprecated

  //short-term
  sEISPLibFwPrimitiveShortTermMemory shortTermMem;

  uint32_t                isOnlineValid;
  uint32_t                isStaticAsTemplateValid;
  uint32_t                isOnlineAsTemplateValid;

  float                   depthAntispoofThreshold;
  float                   sceneMatcherThreshold;

  uint32_t                enrollmentType;
  uint32_t                enrollmentHasGlasses;

  uint32_t                templateID;

  float                   onlineThresholdDepth;
  float                   shortTermThresholdDepth;

  //multi-user short-term
  sEISPLibFwPrimitiveMultiUserShortTermMemory multiUserShortTermMem;
} sEISPLibFIDTemplate;


typedef struct  _sEISPLibFIDEnrollmentIdentifier {
  uint32_t                userID;
  uuid_t                  identityUUID;
  uint32_t                templateID;
  uint32_t                enrollmentType;
} sEISPLibFIDEnrollmentIdentifier;


typedef struct  _sEISPLibFIDSimilarityTag {
  uint32_t                version;
  uint8_t                 isSimilar[CEISPLIB_MAX_FULLFACE_TEMPLATE_NUMBER][CEISPLIB_MAX_FULLFACE_TEMPLATE_NUMBER];

  sEISPLibFIDEnrollmentIdentifier enrollIdentifier[CEISPLIB_MAX_FULLFACE_TEMPLATE_NUMBER];
} sEISPLibFIDSimilarityTag;

typedef struct  _sEISPLibFIDGroupedEnrollmentIdentifier {
  uint32_t                count;
  sEISPLibFIDEnrollmentIdentifier enrollIdentifier[CEISPLIB_MAX_FULLFACE_TEMPLATE_NUMBER];
} sEISPLibFIDGroupedEnrollmentIdentifier;

typedef struct  _sEISPLibFIDMatchedEnrollmentGroup {
  sEISPLibFIDGroupedEnrollmentIdentifier matchedEnrollments;
  sEISPLibFIDGroupedEnrollmentIdentifier similarEnrollments;
} sEISPLibFIDMatchedEnrollmentGroup;


typedef struct _sEISPLibEnrollInfo
{
    uint16_t    status; // See eEISPLibEnrollStatus.
    uint16_t    resvd;
    uint32_t    feedback; // See eEISPLibEnrollFeedback.
    int32_t     poseBinStatus[CEISPLIB_FID_NUM_PITCH_BINS][CEISPLIB_FID_NUM_YAW_BINS];
    int32_t     poseBinCount[CEISPLIB_FID_NUM_PITCH_BINS][CEISPLIB_FID_NUM_YAW_BINS];
    float       pitch;
    float       yaw;
    float       roll;
} sEISPLibEnrollInfo;

typedef struct _sEISPEnrollmentInfo {
    uuid_t enrollmentId;
    int8_t unlockStatus;
} sEISPEnrollmentInfo;


typedef enum _eEispLibFidMatchStatus {
  eEispLibFidMatchStatus_unmatched = 0,
  eEispLibFidMatchStatus_matched = 1,
  eEispLibFidMatchStatus_ambiguous = 2,
} eEispLibFidMatchStatus;

typedef enum _eEispLibFidBioStatus {
  eEispLibFidBioStatus_unmatched = 0,
  eEispLibFidBioStatus_matched = 1,
  eEispLibFidBioStatus_ambiguous = 2,
} eEispLibFidBioStatus;

typedef enum _eEispLibFidAsStatus {
  eEispLibFidAsStatus_unmatched = 0,
  eEispLibFidAsStatus_matched = 1,
  eEispLibFidAsStatus_ambiguous = 2,
} eEispLibFidAsStatus;

typedef struct  _sEISPLibFIDGroupedToken {
  uint32_t                count;
  uint32_t                userID[CEISPLIB_MAX_FULLFACE_USERID_NUMBER];
  uint32_t                token[CEISPLIB_MAX_FULLFACE_USERID_NUMBER];
} sEISPLibFIDGroupedToken;

typedef struct _sEISPLibMatchInfo
{
    uint32_t  matched;        // eEispLibFidMatchStatus: 0/1/2
    float     overallScore;   //deprecated, for backward compatibility
    float     asScore;        //deprecated, for backward compatibility
    uint32_t  bioOK;          // eEispLibFidBioStatus: 0/1/2
    uint32_t  asOK;           // eEispLibFidAsStatus: 0/1/2
    uint32_t  attentionOK;    // 0/1
    uint32_t  contWithPasscode;
    uint32_t  token;
    uint32_t  isIrOverThreshold;        //deprecated, for backward compatibility
    uint32_t  isDepthOverThreshold;     //deprecated, for backward compatibility
    uint32_t  isFloodASOverThreshold;   //deprecated, for backward compatibility
    uint32_t  isDottedASOverThreshold;  //deprecated, for backward compatibility
    float     probeScore;
    uint32_t  earlyExit;

    //DecisionInfo
    uint32_t  isDecisionInfoValid;
    uint32_t  isStaticUnlock;
    uint32_t  isOnlineUnlock;
    uint32_t  isShortTermUnlock;
    int32_t   lifetimeOnline;
    int32_t   lifetimeShortTerm;
    int32_t   pitchBin;
    int32_t   yawBin;
    int32_t   distanceBin;
    uint8_t   hasAttention;

    uint8_t   asFusedIrPass;
    uint8_t   asFloodIrPass;
    uint8_t   asDotIrPass;
    int8_t    isTightStaticUnlock;
    int8_t    isTighterStaticUnlock;
    int8_t    isOnlineStaticUnlock;
    int8_t    isOnlineShortTermUnlock;
    int8_t    isOnlineOutofAnchor;
    int8_t    isPasscodeUpdate;
    int8_t    isPasscodeUpdateTight;
    int8_t    isPasscodeUpdateTighter;
    int8_t    isProbingPatternPass;
    int8_t    isMatcherFailStaticClose;
    int8_t    isMatcherFailStaticFar;
    int8_t    isMatcherFailStaticFarther;

    float     pitchVals[CEISPLIB_MAX_VERIFICATION_FRAMES];
    float     rollVals[CEISPLIB_MAX_VERIFICATION_FRAMES];
    float     yawVals[CEISPLIB_MAX_VERIFICATION_FRAMES];
    uint32_t  distanceVals[CEISPLIB_MAX_VERIFICATION_FRAMES];
    int32_t   fbX[CEISPLIB_MAX_VERIFICATION_FRAMES];
    int32_t   fbY[CEISPLIB_MAX_VERIFICATION_FRAMES];

    //matched enrollmentID
    uuid_t    matchedEnrollmentID;
    uint32_t  userID;
    uint32_t  numEnrollments;
    float     overallScores[CEISPLIB_MAX_TEMPLATE_NUMBER];
    float     asScores[CEISPLIB_MAX_TEMPLATE_NUMBER];
    uint8_t   isIrOverThresholds[CEISPLIB_MAX_TEMPLATE_NUMBER];
    uint8_t   isDepthOverThresholds[CEISPLIB_MAX_TEMPLATE_NUMBER];
    uint8_t   isFloodASOverThresholds[CEISPLIB_MAX_TEMPLATE_NUMBER];
    uint8_t   isDottedASOverThresholds[CEISPLIB_MAX_TEMPLATE_NUMBER];
    sEISPEnrollmentInfo enrollmentInfo[CEISPLIB_MAX_TEMPLATE_NUMBER];
    uint8_t   isDepthASOverThresholds[CEISPLIB_MAX_TEMPLATE_NUMBER];
    uint8_t   isSceneMatcherOverThresholds[CEISPLIB_MAX_TEMPLATE_NUMBER];

    uint32_t  enrollmentHasGlasses;
    uint32_t  verificationHasGlasses;
    uint32_t  bestFrameHasGlasses;

    uint32_t  matchedTemplateID;
    uint32_t  bestFrameHasOcclusion;

    sEISPLibFIDMatchedEnrollmentGroup matchedEnrollmentGroup;
    sEISPLibFIDGroupedToken tokenGroup;
} sEISPLibMatchInfo;

typedef struct _sEISPLibFaceInfo{
  uint32_t  hasFace;
  int16_t  x;
  int16_t  y;
  uint16_t  w;
  uint16_t  h;

  float yaw;
  float pitch;
  float roll;
  uint32_t distance;

  uint32_t  tbd;
} sEISPLibFaceInfo;

typedef  enum _eEISPLibProjectorType
{
    eEISPLibProjectType_None = 0,
    eEISPLibProjectType_Flood = 1,
    eEISPLibProjectType_Sparse = 2,
    eEISPLibProjectType_Dense = 3,
    eEISPLibProjectType_SparseLowerPower = 4,
    eEISPLibProjectType_DenseLowPower = 5,

    eEISPLibProjectType_secret1 = 6,
    eEISPLibProjectType_secret2 = 7,

} eEISPLibProjectorType;

typedef enum  _eEISPLibProjectorProbeMode {
    eEISPLibProjectorProbeMode_NONE = 0,
    eEISPLibProjectorProbeMode_A,  /*!< Curr3 */
    eEISPLibProjectorProbeMode_B,  /*!< Curr4 */
    eEISPLibProjectorProbeMode_AB, /*!< Curr3+4 */
} eEISPLibProjectorProbeMode;

typedef enum _eEISPLibPowerMode
{
  eEISPLibSecretPattern_TBD = 1,
} eEISPLibPowerMode;

typedef enum _eEISPLibFeaGenErrorState
{
  eEISPLibFeaGenErrorState_NONE = 0,
  eEISPLibFeaGenErrorState_CROP,
  eEISPLibFeaGenErrorState_PCE_RESIZE,
  eEISPLibFeaGenErrorState_VISPIPE_RESIZE,
  eEISPLibFeaGenErrorState_PRE,
  eEISPLibFeaGenErrorState_DCN,
  eEISPLibFeaGenErrorState_POST,
  eEISPLibFeaGenErrorState_FDCHECK,
} eEISPLibFeaGenErrorState;

typedef struct _sEISPFIDMetaData
{
    uint8_t     control_pceTestMode;  //0: normal flow, 1: using the face window in the meta as the crop/scale
    uint8_t     control_fidTestMode;  //0: normal flow. others.
    uint8_t     ppdIsDone;
    uint8_t     ppdIsOnGoing;
    uint32_t    fidIsDone;

    uint32_t    serverResId;  //This is used for the resource Id.

    uint32_t    frameNbr;
    uint32_t    width;
    uint32_t    height;
    uint32_t    rowSize;
    uint32_t    bitdepth;
    uint32_t    packFormat;
    uint32_t    doubletSeqNumber;
    float       temperature;
    uint16_t    projectorType; // See eEISPLibProjectorType.
    uint16_t    probeMode; /*!< projector probe mode, eEISPLibProjectorProbeMode */
    uint32_t    power; // See eEISPLibPowerMode.
    uint64_t    userData;
    sEISPLibFaceInfo faceInfo;
    sEISPLibFaceInfo asFaceInfo;
    uint16_t    pceCalibUpdateGMS; /* Apply GMS results */
    int16_t     gmcResult; /*!< GMC result: 0=Pass, For errors (negative values) see GmcStatus in CISPControllerDepthEngine.h */
    double      irIntrinsicsEFL; /*!< IR Intrinsics EFL (irCameraOp/GMC) */
    double      projectorExtrinsicsRotation[3][3]; /*!< Projector Extrinsics Rotation (projectorOp/GMC) */
    double      projectorExtrinsicsLocation[3]; /*!< Projector Extrinsics Location X,Y,Z (projectorOp) */
    uint16_t    PdeRgsW;
    uint16_t    PdeRgsH;
    uint16_t    FPDPass; /*!< 1=FPD Check Passed, 0=FPD Check Failed*/
    uint16_t    PPDValid; /*!< set to true if the output of PPD is valid. */
    uint16_t    PPDPass; /*!< 1=PPD Check Passed, 0=PPD Check Failed */
    int16_t     PPDErrors; /*!< Number of PPD errors */
    uint32_t    PCERefIdx;
    uint8_t     DepthConfig[512];
    uint8_t     faceIsCopied;
    uint16_t    feaGenErrorState; //See eEISPLibFeaGenErrorState
    uint32_t    PCERfcDataType;
    uint16_t    needFIDFeature;
    uint8_t     needASFloodFeature;
    uint8_t     needASDottedFeature;
    uint16_t    bypassPCE;
    uint16_t    bypassPPD;
    uint8_t     orientation;
    uint8_t     isFullFace;
    uint8_t     needASDepthFeature;
    uint8_t     needSceneMatcherFeature;
    uint8_t     pceFrameDoneCount;
    uint8_t     syncCallback;
    uint8_t     isIR;
    uint8_t     extra[491];
} sEISPFIDMetaData;

typedef struct  _sEISPLibFeatureVector{
  uint32_t  asLen;
  uint32_t  featureLen;
  uint8_t  isIr;
  uint8_t  hasFeature;
  uint8_t  hasAsFeature;
  uint8_t  isFullFace;

  float     feature[CEISPLIB_FID_FEATURE_LEN_MAX];
  float     as[CEISPLIB_FID_ANTISPOOF_FEATURE_LEN_MAX];

  uint8_t   asDepthLen;
  uint8_t   sceneMatcherFeatureLen;
  uint8_t   hasAsDepthFeature;
  uint8_t   hasSceneMatcherFeature;

  float     asDepth[CEISPLIB_FID_ASDEPTH_FEATURE_LEN_MAX];
  float     sceneMatcher[CEISPLIB_FID_SCENEMATCHER_FEATURE_LEN_MAX];
} sEISPLibFeatureVector;

typedef struct _sFrameOutputMeta
{
  uint32_t  frameNbr;
  uint32_t  hasFPD;

  uint16_t  FPDPass; /*!< 1=FPD Check Passed, 0=FPD Check Failed*/
  uint16_t  PPDValid; /*!< set to true if the output of PPD is valid. */
  uint16_t  PPDPass; /*!< 1=PPD Check Passed, 0=PPD Check Failed */
  int16_t   PPDErrors; /*!< Number of PPD errors */

  uint32_t  probeMode; /*!< projector probe mode, eEISPLibProjectorProbeMode */

  eEISPLibErrorCode errorCode;
  sEISPLibFeatureVector vector; //This is for full face or periocular vector
} sFrameOutputMeta;

#define   EISPAPPVERINFOSIZE   (32)
typedef struct  _sEispLibDbgInfoFwCommon{
  uint32_t  version;
  char  dcnVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  gitRevision[CEISPLIB_DCN_BUILD_COMMIT_MAX_LENGTH];

  uint32_t numOfTraceInfo;
  sEispLibFidFwTraceInfo traceInfo[CEISPLIB_NUMBER_OF_TRACE_PER_FRAME];

  uint32_t type;  //eFIDPhaseID
  uint64_t groupId;
  uint64_t frameNbr;
  uint32_t isIr;
  uint32_t isFidTemplateUpdated;

  //FeatureGen
  //FeatureGen input
  sEISPFIDMetaData eispMeta;
  //FeatureGen output
  sFrameOutputMeta eispOutMeta;

  //Enrollment
  uint32_t  enroll_choseFd;
  uint32_t  enroll_numFaces;
  sEispLibFidFwPrimitiveMetaData enrollMeta;

  //Verification
  uint32_t verify_choseFd;
  uint32_t verify_numFaces;
  sEispLibFidFwPrimitiveMetaData verifyMeta;
  uint8_t  appVer[EISPAPPVERINFOSIZE];
  uint64_t sessionId; /*!< Session ID for the E-File */

  char  irMatcherVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  depthMatcherVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  asFloodVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  asDottedVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  asDepthVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  sceneMatcherVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];

  char  irMatcherAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  depthMatcherAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  asFloodAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  asDottedAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  asDepthAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  sceneMatcherAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];

  char  periocularIrMatcherVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  periocularDepthMatcherVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  periocularAsFloodVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  periocularAsDottedVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  periocularAsDepthVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];

  char  periocularIrMatcherAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  periocularDepthMatcherAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  periocularAsFloodAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  periocularAsDottedAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];
  char  periocularAsDepthAneCompilerVersion[CEISPLIB_DCN_VERSION_INFO_MAX_LENGTH];

  sEISPLibSessionSetting sessionSetting;
} sEispLibDbgInfoFwCommon;


typedef struct _sEispLibDbgInfoFwCommonSensitive {
  uint32_t  version;

  //Enrollment & Verification
  sEISPLibFIDTemplate fidTemplate;  //deprecated, for backward compatibility

  //Enrollment
  sEISPLibEnrollInfo enrollInfo;

  //Verification
  sEispLibFidFwVerifyScore verifyScore; //deprecated, for backward compatibility
  sEISPLibMatchInfo matchInfo;
  uint32_t isOnlineTemplateUpdated; //deprecated, for backward compatibility
  uint32_t isShortTermMemoryUpdated;//deprecated, for backward compatibility
  uint32_t isSafeUpdate;            //deprecated, for backward compatibility
  uint32_t isPasscodeUpdate;        //deprecated, for backward compatibility
  uint32_t isShortTermMoved;        //deprecated, for backward compatibility

  uint32_t numEnrollments;
  sEISPLibFIDTemplate fidTemplates[CEISPLIB_MAX_TEMPLATE_NUMBER];
  sEispLibFidFwVerifyScore verifyScores[CEISPLIB_MAX_TEMPLATE_NUMBER];
  uint8_t isTemplateUpdated;
  uint8_t isSafeUpdatesSts[CEISPLIB_MAX_TEMPLATE_NUMBER];
  uint8_t isPasscodeUpdateSts[CEISPLIB_MAX_TEMPLATE_NUMBER];
  uint8_t isShortTermMovedSts[CEISPLIB_MAX_TEMPLATE_NUMBER];
  float antispoofFusedScoreMinusThresh[CEISPLIB_MAX_TEMPLATE_NUMBER];

  uint32_t isSimilarityTagUpdated;
  sEISPLibFIDSimilarityTag similarityTag;
} sEispLibDbgInfoFwCommonSensitive;


typedef struct _sEispLibDbgInfoFwSha {
  uint32_t  version;

  //SHA debug blob - TBD
  uint32_t shaDebugInfo[4096];
} sEispLibDbgInfoFwSha;


typedef struct  _sFidFeatureGenDebug {
  /*Following are intenral debugging purpose */
  /* This is used to contain the normalization input for FID feature generation.
   * 1> Could be the FD window crop/scacled version of the flood RAW,
   * 2> Or FD window crop/scalced Depth Image,
   */
  uint32_t  isFullFace;
  uint32_t  hasValidData;

  uint32_t  fidResizeOutputWidth;
  uint32_t  fidResizeOutputHeight;
  uint32_t  fidResizeOutputStride;

  uint32_t  fidNormOutputWidth;
  uint32_t  fidNormOutputHeight;
  uint32_t  fidNormOutputStride;

  uint8_t   fidResizedData[CEISPLIB_FID_RESIZEOUTPUT_SIZE];
  uint8_t   fidNormalizedData[CEISPLIB_FID_NORMOUTPUT_SIZE];
  uint16_t  fidDcnOutput[CEISPLIB_FID_FEATURE_LEN_MAX];

  /* This is used to contain the normalization input for Anti spoofing.
   * FD window cropped/scaled DOT image.
   */
  uint32_t  asResizeOutputWidth;
  uint32_t  asResizeOutputHeight;
  uint32_t  asResizeOutputStride;

  uint32_t  asNormOutputWidth;
  uint32_t  asNormOutputHeight;
  uint32_t  asNormOutputStride;

  uint8_t   asResizedData[CEISPLIB_AS_RESIZEOUTPUT_SIZE];
  uint8_t   asNormalizedData[CEISPLIB_AS_NORMOUTPUT_SIZE];
  uint16_t  asDcnOutput[CEISPLIB_FID_ANTISPOOF_FEATURE_LEN_MAX];

  /* This is used to contain the normalization input for AS depth.
   * FD window cropped/scaled Depth Image.
   */
  uint32_t  asDepResizeOutputWidth;
  uint32_t  asDepResizeOutputHeight;
  uint32_t  asDepResizeOutputStride;

  uint32_t  asDepNormOutputWidth;
  uint32_t  asDepNormOutputHeight;
  uint32_t  asDepNormOutputStride;

  uint8_t   asDepResizedData[CEISPLIB_ASDEPTH_RESIZEOUTPUT_SIZE];
  uint8_t   asDepNormalizedData[CEISPLIB_ASDEPTH_NORMOUTPUT_SIZE];
  uint16_t  asDepDcnOutput[CEISPLIB_FID_ASDEPTH_FEATURE_LEN_MAX];

  /* This is used to contain the normalization input for SceneMatcher.
   * FD window cropped/scaled image.
   */
  uint32_t  sceneMatResizeOutputWidth;
  uint32_t  sceneMatResizeOutputHeight;
  uint32_t  sceneMatResizeOutputStride;

  uint32_t  sceneMatNormOutputWidth;
  uint32_t  sceneMatNormOutputHeight;
  uint32_t  sceneMatNormOutputStride;

  uint8_t   sceneMatResizedData[CEISPLIB_SCENEMAT_RESIZEOUTPUT_SIZE];
  uint8_t   sceneMatNormalizedData[CEISPLIB_SCENEMAT_NORMOUTPUT_SIZE];
  uint16_t  sceneMatDcnOutput[CEISPLIB_FID_SCENEMATCHER_FEATURE_LEN_MAX];
} sFidFeatureGenDebug;


typedef struct  _sEispLibDbgInfoFwFeaGen {
  uint32_t  version;

  uint16_t  chosenDump[2];
  sEispLibFidFwDetectorRect origWindow[2];
  sEispLibFidFwDetectorRect adjustWindow[2];
  sEispLibFidFwDetectorRect cropWindow[2];
  sEispLibFidFwDetectorRect resizeWindow[2];

  sFidFeatureGenDebug fidFeaGen;
} sEispLibDbgInfoFwFeaGen;


typedef struct  _sEispLibDbgInfoFwCropFrame {
  uint32_t  version;
  uint32_t  hasValidData;

  uint32_t  fidNormOutputWidth;
  uint32_t  fidNormOutputHeight;

  uint32_t  asNormOutputWidth;
  uint32_t  asNormOutputHeight;

  uint8_t  fidNormalizedData[CEISPLIB_FID_NORMOUTPUT_SIZE];
  uint8_t  asNormalizedData[CEISPLIB_AS_NORMOUTPUT_SIZE];
} sEispLibDbgInfoFwCropFrame;


typedef struct  _sEispLibDbgInfoFwDepthFrame {
  uint32_t version;
  uint32_t  hasValidData;

  uint32_t size;
  uint8_t  depthFrame[CEISPLIB_DEPTHFRAME_SIZE];
} sEispLibDbgInfoFwDepthFrame;


typedef struct _sEispLibDbgInfoFwVisPipe {
  uint32_t  version;

  uint16_t visOut[CEISPLIB_VISPIPEOUT_WIDTH][CEISPLIB_VISPIPEOUT_HEIGHT];
} sEispLibDbgInfoFwVisPipe;

typedef struct _sEispLibDbgInfoFwPde {
#if 0
//#ifdef PEARL_REG_DUMP
#if defined(EISP_CRETE) 
#define PEARL_MAX_REG_ADDR 0x1f3d0 //(PEARL_PEARLPROCPOSTDMADSTUNPACKER_LAST + 0x4)
#else
#define PEARL_MAX_REG_ADDR 0x1f398 //(PEARL_PEARLPROCPOSTDMADSTUNPACKER_LAST + 0x4)
#endif

	uint32_t reg_dump[(PEARL_MAX_REG_ADDR/4 + 1)];
  uint32_t version;
#else
  uint32_t  version;
  
  uint16_t depth[CEISPLIB_PDE_DEPTH_WIDTH][CEISPLIB_PDE_DEPTH_HEIGHT];
  uint16_t probeDepth[CEISPLIB_PDE_DEPTH_WIDTH][CEISPLIB_PDE_DEPTH_HEIGHT];

  sEispLibFidFwDetectorRect cropWindow;
  sEispLibFidFwDetectorRect origWindow;
  //calibration blob - placeholder
  uint8_t calib[16*1024];
  uint32_t calibSize;
  //regDump blob - placeholder
  uint8_t regDump[24*1024];

  //in SMP emitter count is 20, in pearl1  10
  double  ppdEmittersScores[20];
  uint32_t numOfValidScores;
  double  ppdSoftScores[32];
  uint32_t numOfValidSoftScores;
  uint32_t fpd_psb;
  uint8_t ppdHistoryBuffer[10*1024];
  uint32_t irCrC;
#endif
} sEispLibDbgInfoFwPde;


typedef struct _sEispLibDbgInfoFwPdeProbe {
  uint32_t  version;

  uint16_t Dx[CEISPLIB_DXY_BUFFER_SIZE];
  uint16_t Dy[CEISPLIB_DXY_BUFFER_SIZE];

  //calibration blob - placeholder
  uint8_t calib[16*1024];

}sEispLibDbgInfoFwPdeProbe;


typedef struct _sEispLibDbgInfoAlgItem {
  uint16_t version;
  uint16_t isEnrollment;
  uint16_t isIr;
  uint16_t isMetaDataCopied;

  uint64_t groupId;
  uint64_t frameId;
  uint32_t errorCode;

  uint32_t asFeatureLen;
  uint32_t fidFeatureLen;

  float asFeature[CEISPLIB_FID_ANTISPOOF_FEATURE_LEN_MAX];
  float fidFeature[CEISPLIB_FID_FEATURE_LEN_MAX];

  //Scores for each verify feature
  float currFrameOverallScore;
  float currFrameAsScore;
  float currFrameStaticScore;
  float currOnlineSafeUpdateScore;
  float currOnlinePasscodeScore;
  float probePatternMatchingScore;
  int32_t bestMatchTemplateIdxStatic;
  int32_t bestMatchTemplateIdxSafeUpdate;
  int32_t bestMatchTemplateIdxPasscode;

  float bestIRScore;
  float bestDepthScore;
  float bestFusedScore;
  float bestIROnlineScore;
  float bestDepthOnlineScore;
  float bestFusedOnlineScore;
  float bestIRShortTermScore;
  float bestDepthShortTermScore;
  float bestFusedShortTermScore;

  uint32_t isBestScoreOnline;
  uint32_t isBestScoreShortTerm;
  int32_t bestScoreTemplateIdxIR;
  int32_t bestScoreTemplateIdxIROnline;
  int32_t bestScoreTemplateIdxIRShortTerm;
  int32_t bestScoreTemplateIdxDepth;
  int32_t bestScoreTemplateIdxDepthOnline;
  int32_t bestScoreTemplateIdxDepthShortTerm;

  int32_t onlineInsertionIdx;
  int32_t shortTermOnlineInsertionIdx;

  uint64_t bestIRScoreFrameId;
  uint64_t bestIROnlineScoreFrameId;
  uint64_t bestIRShortTermScoreFrameId;
  uint64_t bestDepthScoreFrameId;
  uint64_t bestDepthOnlineScoreFrameId;
  uint64_t bestDepthShortTermScoreFrameId;

  uint32_t isStaticUnlock;
  uint32_t isOnlineUnlock;
  uint32_t isShortTermUnlock;

  uint32_t isSafeUpdate;
  uint32_t isPasscodeUpdate;
  uint32_t isShortTermMoved;

  uint32_t passcodeStatus;

  uint32_t isBackgroundUpdateEligible;
  uint32_t isPasscodeUpdateEligible;

  uuid_t enrollmentId;
  uint32_t userId;

  uint32_t doesFramePassMatcher;
  float antispoofFusedScoreMinusThresh;

  float currFrameSceneMatcherScore;
  float sceneMatcherFeature[CEISPLIB_FID_SCENEMATCHER_FEATURE_LEN_MAX];
  uint32_t sceneMatcherLen;

  uint32_t enrollmentHasGlasses;
  uint32_t verificationHasGlasses;
  uint32_t bestFrameHasGlasses;
  uint32_t currFrameHasGlasses;
  uint32_t templateId;

  uint8_t rsvd1[1820];
} sEispLibDbgInfoAlgItem;



typedef struct _sEispLibDbgInfoAlg {
  uint16_t version;

  //Deprecated, for backward compatibility
  uint16_t isEnrollment;
  uint16_t isIr;
  uint16_t isMetaDataCopied;

  uint64_t groupId;
  uint64_t frameId;
  uint32_t errorCode;

  uint32_t asFeatureLen;
  uint32_t fidFeatureLen;

  float asFeature[CEISPLIB_FID_ANTISPOOF_FEATURE_LEN_MAX];
  float fidFeature[CEISPLIB_FID_FEATURE_LEN_MAX];

  //Scores for each verify feature
  float currFrameOverallScore;
  float currFrameAsScore;
  float currFrameStaticScore;
  float currOnlineSafeUpdateScore;
  float currOnlinePasscodeScore;
  float probePatternMatchingScore;
  int32_t bestMatchTemplateIdxStatic;
  int32_t bestMatchTemplateIdxSafeUpdate;
  int32_t bestMatchTemplateIdxPasscode;

  float bestIRScore;
  float bestDepthScore;
  float bestFusedScore;
  float bestIROnlineScore;
  float bestDepthOnlineScore;
  float bestFusedOnlineScore;
  float bestIRShortTermScore;
  float bestDepthShortTermScore;
  float bestFusedShortTermScore;

  uint32_t isBestScoreOnline;
  uint32_t isBestScoreShortTerm;
  int32_t bestScoreTemplateIdxIR;
  int32_t bestScoreTemplateIdxIROnline;
  int32_t bestScoreTemplateIdxIRShortTerm;
  int32_t bestScoreTemplateIdxDepth;
  int32_t bestScoreTemplateIdxDepthOnline;
  int32_t bestScoreTemplateIdxDepthShortTerm;

  int32_t onlineInsertionIdx;
  int32_t shortTermOnlineInsertionIdx;

  uint64_t bestIRScoreFrameId;
  uint64_t bestIROnlineScoreFrameId;
  uint64_t bestIRShortTermScoreFrameId;
  uint64_t bestDepthScoreFrameId;
  uint64_t bestDepthOnlineScoreFrameId;
  uint64_t bestDepthShortTermScoreFrameId;

  uint32_t isStaticUnlock;
  uint32_t isOnlineUnlock;
  uint32_t isShortTermUnlock;

  uint32_t isSafeUpdate;
  uint32_t isPasscodeUpdate;
  uint32_t isShortTermMoved;

  uint32_t passcodeStatus;

  uint32_t isBackgroundUpdateEligible;
  uint32_t isPasscodeUpdateEligible;

  uint32_t numEnrollments;
  sEispLibDbgInfoAlgItem algoDbgInfo[CEISPLIB_MAX_TEMPLATE_NUMBER];
} sEispLibDbgInfoAlg;


typedef struct _sEispLibDbgInfoFwHostMeta
{
  uint8_t version;

  uint8_t isValid;
  uint16_t size;
  uint8_t hostMeta[CEISPLIB_HOSTMETA_MAX_SIZE];
} sEispLibDbgInfoFwHostMeta;


typedef struct _sEispLibDbgInfoFwFlowDBG_Item
{
  uint8_t    valid;
  uint8_t    rsvd[3];
  uint32_t   traceCode; //Need to be unique
  uint64_t   timeStamp;
  uint64_t   userData;
} sEispLibDbgInfoFwFlowDBG_Item;


typedef struct _sEispLibDbgInfoFwFlowDBG_CheckEnrollMeta
{
  sEispLibDbgInfoFwFlowDBG_Item hdr;
  uint8_t data[64];

} sEispLibDbgInfoFwFlowDBG_CheckEnrollMeta;

typedef struct _sEispLibDbgInfoFwFlowDBG_CheckVerifyMeta
{
  sEispLibDbgInfoFwFlowDBG_Item hdr;
  uint8_t data[64];

} sEispLibDbgInfoFwFlowDBG_CheckVerifyMeta;

typedef struct _sEispLibDbgInfoFwFlowDBG_CheckRaw
{
  sEispLibDbgInfoFwFlowDBG_Item hdr;
  uint8_t data[160];
} sEispLibDbgInfoFwFlowDBG_CheckRaw;

typedef struct _sEispLibDbgInfoFwFlowDBG_FGClient
{
  sEispLibDbgInfoFwFlowDBG_Item fg5;
  sEispLibDbgInfoFwFlowDBG_Item fg6Cache;
  sEispLibDbgInfoFwFlowDBG_Item fg6;
  sEispLibDbgInfoFwFlowDBG_Item fg52;
  sEispLibDbgInfoFwFlowDBG_Item fg2;
  sEispLibDbgInfoFwFlowDBG_Item fgclientSend;
  sEispLibDbgInfoFwFlowDBG_Item fgclientRecv;
  //uint8_t data[1024];
} sEispLibDbgInfoFwFlowDBG_FGClient;



typedef struct _sEispLibDbgInfoFwFlowDBG_FGServer
{
  sEispLibDbgInfoFwFlowDBG_Item pce;
  sEispLibDbgInfoFwFlowDBG_Item pcePpd;

  sEispLibDbgInfoFwFlowDBG_Item AsPre;
  sEispLibDbgInfoFwFlowDBG_Item FidPre;

  sEispLibDbgInfoFwFlowDBG_Item AsPost;
  sEispLibDbgInfoFwFlowDBG_Item FidPost;

  sEispLibDbgInfoFwFlowDBG_Item AsDcn;
  sEispLibDbgInfoFwFlowDBG_Item FidDcn;

  sEispLibDbgInfoFwFlowDBG_Item ppdAlg;

} sEispLibDbgInfoFwFlowDBG_FeatureGenServer;

typedef struct _sEispLibDbgInfoFwFlowDBG_Enrollment
{
  sEispLibDbgInfoFwFlowDBG_Item hdr;

} sEispLibDbgInfoFwFlowDBG_Enrollment;

typedef struct _sEispLibDbgInfoFwFlowDBG_EnrollmentFinalize
{
  sEispLibDbgInfoFwFlowDBG_Item hdr;

} sEispLibDbgInfoFwFlowDBG_EnrollmentFinalize;

typedef struct _sEispLibDbgInfoFwFlowDBG_Match
{
  sEispLibDbgInfoFwFlowDBG_Item hdr;

} sEispLibDbgInfoFwFlowDBG_Match;

typedef struct _sEispLibDbgInfoFwFlowDBG_MatchFinalize
{
  sEispLibDbgInfoFwFlowDBG_Item hdr;

} sEispLibDbgInfoFwFlowDBG_MatchFinalize;

typedef struct _sEispLibDbgInfoFwFlowDBG_MatchUpdateTemplate
{
  sEispLibDbgInfoFwFlowDBG_Item hdr;

} sEispLibDbgInfoFwFlowDBG_MatchUpdateTemplate;


typedef struct _sEispLibDbgInfoFwFlowDBG
{
  uint8_t  version;
  uint8_t  rsvd[3];
  sEispLibDbgInfoFwFlowDBG_CheckEnrollMeta  checkEnrollMeta;
  sEispLibDbgInfoFwFlowDBG_CheckVerifyMeta  checkVerifyMeta;
  sEispLibDbgInfoFwFlowDBG_CheckRaw checkRaw;
  sEispLibDbgInfoFwFlowDBG_FGClient fgClient;
  sEispLibDbgInfoFwFlowDBG_FeatureGenServer fgServer;
  sEispLibDbgInfoFwFlowDBG_Enrollment enroll;
  sEispLibDbgInfoFwFlowDBG_EnrollmentFinalize enrollFinal;
  sEispLibDbgInfoFwFlowDBG_Match  match;
  sEispLibDbgInfoFwFlowDBG_MatchFinalize  matchFinal;
  sEispLibDbgInfoFwFlowDBG_MatchUpdateTemplate  matchUpdateTemplate;
} sEispLibDbgInfoFwFlowDBG;

typedef enum  _eEispLibDbgInfoFwFlowDBG_TraceCode{
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkRaw_NO_ERROR = 0x01000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkRaw_LIBHANLDE_ERR = 0x01000001,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkRaw_SHAINOUT_ERR  = 0x01000002,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkRaw_META_ERR  = 0x01000002,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkRaw_SHARESULT_ERR  = 0x01000002,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkRaw_NO_SHA_DMA_ERR  = 0x01000002,


  eEispLibDbgInfoFwFlowDBG_TraceCode_checkEnrollMeta_NO_ERROR = 0x02000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkEnrollMeta_PARAMETER_ERROR = 0x02000001,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkEnrollMeta_META_ERROR = 0x02000002,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkEnrollMeta_FIDMeta_ERROR = 0x02000003,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkEnrollMeta_IRMETA_ERROR = 0x02000004,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkEnrollMeta_IRFIDMeta_ERROR = 0x02000005,


  eEispLibDbgInfoFwFlowDBG_TraceCode_checkVerifyMeta_NO_ERROR = 0x03000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkVerifyMeta_PARAMETER_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkVerifyMeta_META_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkVerifyMeta_FIDMeta_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkVerifyMeta_IRMETA_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_checkVerifyMeta_IRFIDMeta_ERROR,

  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_5_NO_ERROR = 0x04000000,

  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_6Cache_NO_ERROR = 0x05000000,


  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_6_NO_ERROR = 0x06000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_6_PARAM_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_6_META_ERROR,


  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_NO_ERROR = 0x07000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_PARAM_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_META_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_FIDMETA_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_IRMETA_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_IRFIDMETA_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_DEPTH_RES_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_PMETA_RES_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_BIOCAPTURE_CHECK_ERROR,

  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_2_NO_ERROR = 0x08000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_2_PAMA_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_2_SEND_FAIL,


  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Send_NO_ERROR = 0x09000000,


  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_NO_ERROR = 0x0a000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_CACHED_FAILUR_PUSHOUT,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_CACHED_FAILUR_GROUPID,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_CACHED_FAILUR_FRAMENBR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_CACHED_FAILUR_IR_FAILURE,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_CACHED_FAILUR_2nd_DEPTH,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_PMETA_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_CALLBACK_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_NO_RESULT_ERROR,


  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_NO_ERROR = 0x0b000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_PARAMETER_v2,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_PARAMETER_v3,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_IR_META_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_DEPTH_META_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_IR_FIDMETA_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_DEPTH_FIDMETA_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_IDENTITY_CHANGE,


  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_FINALIZE_NO_ERROR = 0x0c000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_FINALIZE_PARAMETER,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_FINALIZE_FAILED,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_FINALIZE_GETTEMPLATE_SIZE_FAILED,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_FINALIZE_WRONG_TEMPLATE_SIZE,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ENROLL_FINALIZE_GETTEMPLATE_FAILED,


  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_NO_ERROR = 0x0d000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_PARAMETER_v2,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_PARAMETER_v3,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_IR_META_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_DEPTH_META_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_IR_FIDMETA_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_DEPTH_FIDMETA_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_PUSH_ERROR,


  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_FINALIZE_NO_ERROR = 0x0e000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_FINALIZE_PARAMETER,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_FINALIZE_FAILED,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_FINALIZE_MODALITY_FAILED,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_FINALIZE_DECISIONINFO_FAILED,

  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_UPDATETEMPLATE_NO_ERROR = 0x0f000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_UPDATETEMPLATE_PARAMETER,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_UPDATETEMPLATE_FINALIZE_FAILED,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_UPDATETEMPLATE_GETTEMPLATE_SIZE_FAILED,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_UPDATETEMPLATE_WRONG_TEMPLATE_SIZE,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_UPDATETEMPLATE_GETTEMPLATE_FAILED,
  eEispLibDbgInfoFwFlowDBG_TraceCode_MATCH_UPDATETEMPLATE_GETSHORTTERM_FAILED,


  eEispLibDbgInfoFwFlowDBG_TraceCode_PCE_NO_ERROR = 0x10000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_PCE_NOCLIBRATION,
  eEispLibDbgInfoFwFlowDBG_TraceCode_PCE_META_INVALID,
  eEispLibDbgInfoFwFlowDBG_TraceCode_PCE_BUFFER_INVALID,
  eEispLibDbgInfoFwFlowDBG_TraceCode_PCE_CONF_INVALID,
  eEispLibDbgInfoFwFlowDBG_TraceCode_PCE_SETSCALECROP_FAILED,
  eEispLibDbgInfoFwFlowDBG_TraceCode_PCE_EXECUTION_ERROR,


  eEispLibDbgInfoFwFlowDBG_TraceCode_PCEPPD_NO_ERROR = 0x11000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_PCEPPD_EXECUTION_ERROR,


  eEispLibDbgInfoFwFlowDBG_TraceCode_ASPRE_NO_ERROR = 0x12000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ASPRE_PREPROCESS_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ASPRE_RESIZE_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ASPRE_NORMALIZE_ERROR,


  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_NO_ERROR = 0x13000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_PREPROCESS_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_RESIZE_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_NORMALIZE_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_NULL_PDATA,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_NULL_PMETA,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_INVALID_META_MEMOBJ,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_INVALID_RAW_MEMOBJ,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_NOT_INITIALIZED,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_NO_FD,


  eEispLibDbgInfoFwFlowDBG_TraceCode_ASPOST_NO_ERROR = 0x14000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_ASPOST_NORMALIZE_ERROR,


  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPOST_NO_ERROR = 0x15000000,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPOST_NORMALIZE_ERROR,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPOST_NULL_PMETA,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPOST_NULL_PRESULT,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPOST_INVALID_META_MEMOBJ,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPOST_INVALID_RESULT_MEMOBJ,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPOST_NOT_INITIALIZED,
  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPOST_NO_FD,


  eEispLibDbgInfoFwFlowDBG_TraceCode_ASDCN_NO_ERROR = 0x16000000,


  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDDCN_NO_ERROR = 0x17000000,


  eEispLibDbgInfoFwFlowDBG_TraceCode_PPDALG_NO_ERROR = 0x18000000,

} eEispLibDbgInfoFwFlowDBG_TraceCode;

typedef enum  _eEispLibDbgInfoFwFlowDBG_FGClient_Index{
  eEispLibDbgInfoFwFlowDBG_FGClientIndex_5= 0,
  eEispLibDbgInfoFwFlowDBG_FGClientIndex_6Cache = 1,
  eEispLibDbgInfoFwFlowDBG_FGClientIndex_6 = 2,
  eEispLibDbgInfoFwFlowDBG_FGClientIndex_52 = 3,
  eEispLibDbgInfoFwFlowDBG_FGClientIndex_2 = 4,
  eEispLibDbgInfoFwFlowDBG_FGClientIndex_Send = 5,
  eEispLibDbgInfoFwFlowDBG_FGClientIndex_Recv = 6,
  eEispLibDbgInfoFwFlowDBG_FGClientIndex_ToT,
  eEispLibDbgInfoFwFlowDBG_FGClientIndex_Invalid
} eEispLibDbgInfoFwFlowDBG_FGClient_Index;

inline  eEispLibDbgInfoFwFlowDBG_FGClient_Index getFGClientIndexByTraceCode(uint32_t  traceCode)
{
  traceCode = traceCode & 0xff000000;
  switch(traceCode)
  {
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_5_NO_ERROR:
      return eEispLibDbgInfoFwFlowDBG_FGClientIndex_5;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_6Cache_NO_ERROR:
      return eEispLibDbgInfoFwFlowDBG_FGClientIndex_6Cache;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_6_NO_ERROR:
      return eEispLibDbgInfoFwFlowDBG_FGClientIndex_6;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_NO_ERROR:
      return eEispLibDbgInfoFwFlowDBG_FGClientIndex_52;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_2_NO_ERROR:
      return eEispLibDbgInfoFwFlowDBG_FGClientIndex_2;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Send_NO_ERROR:
      return eEispLibDbgInfoFwFlowDBG_FGClientIndex_Send;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_NO_ERROR:
      return eEispLibDbgInfoFwFlowDBG_FGClientIndex_Recv;
    default:
      return eEispLibDbgInfoFwFlowDBG_FGClientIndex_Invalid;
      break;
  }
}

inline  sEispLibDbgInfoFwFlowDBG_Item* getFGServerItemByTraceCode(uint32_t  traceCode, sEispLibDbgInfoFwFlowDBG_FeatureGenServer *pFg)
{
  if(!pFg)
  {
    return (sEispLibDbgInfoFwFlowDBG_Item*)NULL;
  }
  traceCode = traceCode & 0xff000000;
  switch(traceCode)
  {
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_PCE_NO_ERROR:
      return &pFg->pce;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_PCEPPD_NO_ERROR:
      return &pFg->pcePpd;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_ASPRE_NO_ERROR:
      return &pFg->AsPre;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPRE_NO_ERROR:
      return &pFg->FidPre;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_ASPOST_NO_ERROR:
      return &pFg->AsPost;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDPOST_NO_ERROR:
      return &pFg->FidPost;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_ASDCN_NO_ERROR:
      return &pFg->AsDcn;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FIDDCN_NO_ERROR:
      return &pFg->FidDcn;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_PPDALG_NO_ERROR:
      return &pFg->ppdAlg;
    default:
      return (sEispLibDbgInfoFwFlowDBG_Item*)NULL;
      break;
  }
}


inline  sEispLibDbgInfoFwFlowDBG_Item* getFGClientItemByTraceCode(uint32_t  traceCode, sEispLibDbgInfoFwFlowDBG_FGClient *pFg)
{
  if(!pFg)
  {
    return (sEispLibDbgInfoFwFlowDBG_Item*)NULL;
  }
  traceCode = traceCode & 0xff000000;
  switch(traceCode)
  {
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_5_NO_ERROR:
      return &pFg->fg5;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_6Cache_NO_ERROR:
      return &pFg->fg6Cache;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_6_NO_ERROR:
      return &pFg->fg6;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_52_NO_ERROR:
      return &pFg->fg52;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_2_NO_ERROR:
      return &pFg->fg2;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Send_NO_ERROR:
      return &pFg->fgclientSend;
    case  eEispLibDbgInfoFwFlowDBG_TraceCode_FG_Client_Recv_NO_ERROR:
      return &pFg->fgclientRecv;
    default:
      return (sEispLibDbgInfoFwFlowDBG_Item*)NULL;
      break;
  }
}




typedef enum  _eEispLibDbgInfoFwFlowDBG_SubModuleIndex{
  eEispLibDbgInfoFwFlowDBG_SubModuleIndex_checkEnroll = 0,
  eEispLibDbgInfoFwFlowDBG_SubModuleIndex_checkRaw = 1,
  eEispLibDbgInfoFwFlowDBG_SubModuleIndex_fgClient = 2,
  eEispLibDbgInfoFwFlowDBG_SubModuleIndex_fgServer = 3,
  eEispLibDbgInfoFwFlowDBG_SubModuleIndex_enroll = 4,
  eEispLibDbgInfoFwFlowDBG_SubModuleIndex_match = 5,
  eEispLibDbgInfoFwFlowDBG_SubModuleIndex_ToT
} eEispLibDbgInfoFwFlowDBG_SubModuleIndex;
// Used by SPRL to extract the SN
typedef struct _pwclSN
{
    char padding[101];
    char serialNumberBase34[11];
    char padding2[17];
    uint8_t otpVer;
    char padding3[45];
    char serialNumberNVMv2Base34[11];
} pwclSN;

#define DCNLoaderFileMaxKernelNbr (32)
typedef struct  _sDCNLoaderFileHdr{
  uint32_t  version;
  uint32_t  totalSize;
  uint32_t  kernelNbr;
  uint32_t  kernelOffset[DCNLoaderFileMaxKernelNbr];
  uint32_t  kernelSize[DCNLoaderFileMaxKernelNbr];
  uint16_t  kernelCrc[DCNLoaderFileMaxKernelNbr];

} sDCNLoaderFileHdr;

#define MAX_EFILE_SIZE (sizeof(sEispLibDbgInfoShared) + CEISPLIB_DEBUG_INFO_TOT * sizeof(uint32_t)\
                        + sizeof(sEispLibDbgInfoFwCommon)\
                        + sizeof(sEispLibDbgInfoFwCommonSensitive)\
                        + sizeof(sEispLibDbgInfoFwFeaGen)\
                        + sizeof(sEispLibDbgInfoFwSha)\
                        + sizeof(sEispLibDbgInfoFwCropFrame)\
                        + sizeof(sEispLibDbgInfoFwDepthFrame)\
                        + sizeof(sEispLibDbgInfoFwVisPipe)\
                        + sizeof(sEispLibDbgInfoFwPde)\
                        + sizeof(sEispLibDbgInfoAlg)\
                        + sizeof(sEispLibDbgInfoFwPdeProbe)\
                        + sizeof(sEispLibDbgInfoFwHostMeta)\
                        + sizeof(sEispLibDbgInfoFwFlowDBG))

static  uint32_t  EispLibItemSize[CEISPLIB_DEBUG_INFO_TOT] =
{
     [CEISPLIB_DEBUG_INFO_FW_COMMON]             = sizeof(sEispLibDbgInfoFwCommon),  /*!< ID for \ref sEispLibDbgInfoFwCommon structure */
     [CEISPLIB_DEBUG_INFO_FW_COMMONSENSITIVE]    = sizeof(sEispLibDbgInfoFwCommonSensitive),  /*!< ID for \ref sEispLibDbgInfoFwCommonSensitive structure */
     [CEISPLIB_DEBUG_INFO_FW_FEAGEN]             = sizeof(sEispLibDbgInfoFwFeaGen),  /*!< ID for \ref sEispLibDbgInfoFwFeaGen structure */
     [CEISPLIB_DEBUG_INFO_FW_SHA]                = sizeof(sEispLibDbgInfoFwSha),  /*!< ID for \ref sEispLibDbgInfoFwSha structure */
     [CEISPLIB_DEBUG_INFO_FW_CROPFRAME]          = sizeof(sEispLibDbgInfoFwCropFrame),  /*!< ID for \ref sEispLibDbgInfoFwCropFrame structure */
     [CEISPLIB_DEBUG_INFO_FW_DEPTHFRAME]         = sizeof(sEispLibDbgInfoFwDepthFrame),  /*!< ID for \ref sEispLibDbgInfoFwDepthFrame structure. */
     [CEISPLIB_DEBUG_INFO_FW_VISPIPE]            = sizeof(sEispLibDbgInfoFwVisPipe),  /*!< ID for \ref sEispLibDbgInfoFwVisPipe structure */
     [CEISPLIB_DEBUG_INFO_FW_PDE]                = sizeof(sEispLibDbgInfoFwPde),  /*!< ID for \ref sEispLibDbgInfoFwPde structure */
     [CEISPLIB_DEBUG_INFO_ALG]                   = sizeof(sEispLibDbgInfoAlg),  /*!< ID for \ref sEispLibDbgInfoAlg structure */
     [CEISPLIB_DEBUG_INFO_FW_PDE_PROBE]          = sizeof(sEispLibDbgInfoFwPdeProbe),  /*!< ID for \ref sEispLibDbgInfoFwPdeProbe structure */
     [CEISPLIB_DEBUG_INFO_FW_HOST_META]          = sizeof(sEispLibDbgInfoFwHostMeta), /*!< ID for \ref sEispLibDbgInfoFwHostMeta structure */
     [CEISPLIB_DEBUG_INFO_FW_FLOW_DBG]          = sizeof(sEispLibDbgInfoFwFlowDBG), /*!< ID for \ref sEispLibDbgInfoFwFlowDBG structure */
};

typedef enum  _eEISPLibTZ1MemPoolType{
  eEISPLibTZ1MemPoolType_Perm = 0,
  eEISPLibTZ1MemPoolType_Temp = 1,
} eEISPLibTZ1MemPoolType;

/**
 * Reset packing
 */
#pragma pack(pop)

#ifdef __cplusplus
};
#endif
#endif /* CEISPLIBDEFS_H_ */
