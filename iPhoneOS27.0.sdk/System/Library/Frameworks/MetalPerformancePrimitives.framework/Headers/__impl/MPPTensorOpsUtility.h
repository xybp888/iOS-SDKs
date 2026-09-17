
// -*- Metal -*-
//===-- MetalTensorOpsUtility ------------------------------------------------------===//
// Copyright (c) 2025 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __MetalTensorOpsUtility__
#define __MetalTensorOpsUtility__

#if defined(__METAL_VERSION__) && defined(__HAVE_TENSOR__)

#include "MPPTensorOpsTypes.h"

namespace mpp
{
namespace tensor_ops
{

namespace __tensor_ops_detail
{

template <typename T>
T __MIN(T x, T y)
{
  return ((x) < (y) ? (x) : (y));
}
template <typename T>
T __MAX(T x, T y)
{
  return ((x) > (y) ? (x) : (y));
}

template <typename T>
struct __type_to_tensor_ops_datatype
{
    static_assert(__tensor_ops_detail::__assert_false_v<T>,
                  "unsupported data type");
};
template <>
struct __type_to_tensor_ops_datatype<float>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_float32;
};
template <>
struct __type_to_tensor_ops_datatype<half>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_float16;
};
#if __HAVE_BFLOAT__
template <>
struct __type_to_tensor_ops_datatype<bfloat>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_bfloat16;
};
#endif
template <>
struct __type_to_tensor_ops_datatype<int8_t>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_int8;
};
template <>
struct __type_to_tensor_ops_datatype<uint8_t>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_uint8;
};
#if __HAVE_INT2B_FORMAT_TYPE__
template <>
struct __type_to_tensor_ops_datatype<metal::int2b_format>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_int2;
};
template <>
struct __type_to_tensor_ops_datatype<metal::uint2b_format>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_uint2;
};
#endif
#if __HAVE_INT4B_FORMAT_TYPE__
template <>
struct __type_to_tensor_ops_datatype<metal::int4b_format>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_int4;
};
template <>
struct __type_to_tensor_ops_datatype<metal::uint4b_format>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_uint4;
};
#endif
#if __HAVE_METAL_FP4_E2M1_FORMAT_TYPE__
template <>
struct __type_to_tensor_ops_datatype<metal::metal_fp4_e2m1_format>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_fp4_e2m1;
};
#endif
#if __HAVE_METAL_FP8_E4M3_FORMAT_TYPE__
template <>
struct __type_to_tensor_ops_datatype<metal::metal_fp8_e4m3_format>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_fp8_e4m3;
};
#endif
#if __HAVE_METAL_FP8_E5M2_FORMAT_TYPE__
template <>
struct __type_to_tensor_ops_datatype<metal::metal_fp8_e5m2_format>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_fp8_e5m2;
};
#endif
template <>
struct __type_to_tensor_ops_datatype<int16_t>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_int16;
};
template <>
struct __type_to_tensor_ops_datatype<uint16_t>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_uint16;
};
template <>
struct __type_to_tensor_ops_datatype<int>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_int32;
};
template <>
struct __type_to_tensor_ops_datatype<uint>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_uint32;
};

} // namespace __tensor_ops_detail

} // namespace tensor_ops
} // namespace mpp

#endif

#endif // __TensorOpsUtility__
