#ifndef Spatial_Base_h
#define Spatial_Base_h

#define SPDefaultTolerance sqrt(__DBL_EPSILON__)

// Returns `true` if `x` and `y` are equal within `SPDefaultTolerance`
#define _sp_almost_equal(x, y) (fabs((x) - (y)) < SPDefaultTolerance)

// Returns `true` if the square matrix `x` is orthogonal.
#define _sp_is_orthogonal(x, identity) simd_almost_equal_elements(simd_mul((x), simd_transpose((x))), (identity), SPDefaultTolerance)

#if __has_attribute(swift_name)
# define SPATIAL_SWIFT_NAME(_name) __attribute__((swift_name(#_name)))
#else
# define SPATIAL_SWIFT_NAME(_name)
#endif

#if __has_attribute(swift_private)
# define SPATIAL_REFINED_FOR_SWIFT __attribute__((swift_private))
#else
# define SPATIAL_REFINED_FOR_SWIFT
#endif

#if __has_extension(attribute_overloadable)
#define SPATIAL_OVERLOADABLE __attribute__((__overloadable__))
#else
#define SPATIAL_OVERLOADABLE
#endif

#define SPATIAL_INLINE static inline

#ifdef __cplusplus
#define _sp_simd_isnan ::__tg_isnan
#else
#define _sp_simd_isnan isnan
#endif

#ifdef __cplusplus
#define _sp_simd_isfinite ::__tg_isfinite
#else
#define _sp_simd_isfinite isfinite
#endif

#ifdef __cplusplus
#define _sp_simd_floor ::__tg_floor
#else
#define _sp_simd_floor floor
#endif

#ifdef __cplusplus
#define _sp_simd_ceil ::__tg_ceil
#else
#define _sp_simd_ceil ceil
#endif

#ifdef __cplusplus
#define _sp_simd_cos ::__tg_cos
#else
#define _sp_simd_cos cos
#endif

#ifdef __cplusplus
#define _sp_simd_sin ::__tg_sin
#else
#define _sp_simd_sin sin
#endif

#endif /* Spatial_Base_h */
