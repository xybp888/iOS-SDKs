
// -*- Metal -*-
//===-- MetalTensorOpsTraits ------------------------------------------------------===//
// Copyright (c) 2025 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __MetalTensorOpsTraits__
#define __MetalTensorOpsTraits__

#if defined(__METAL_VERSION__) && defined(__HAVE_TENSOR__)

#include <__exec/units.h>
#include <metal_cooperative_tensor>
#include <metal_tensor>
#include <metal_type_traits>

#pragma METAL internals : enable

namespace mpp
{
namespace tensor_ops
{

namespace __tensor_ops_detail
{

template <bool B, typename T = void>
using __enable_if_t = metal::enable_if_t<B, T>;

template <typename T>
using __remove_addrspace_t = metal::remove_addrspace_t<T>;

template <typename T>
using __remove_pointer_t = metal::remove_pointer_t<T>;

template <typename T>
using __remove_reference_t = metal::remove_reference_t<T>;

template <typename U, typename V>
constant auto __is_same_v = metal::is_same_v<U, V>;

template <typename T>
constant auto __is_integral_v = metal::is_integral_v<T>;

using __false_type = metal::false_type;

using __true_type = metal::true_type;

template <typename T>
using __remove_cv_t = metal::remove_cv_t<T>;

template <typename T>
using __remove_coherent_t = metal::remove_coherent_t<T>;

template <typename T>
using __remove_ref_ptr_t = __remove_reference_t<__remove_pointer_t<T>>;

template <typename T>
constant auto __is_ui8_v = __is_same_v<T, uint8_t> || __is_same_v<T, unsigned char>;

template <typename T>
constant auto __is_i8_v = __is_same_v<T, int8_t> || __is_same_v<T, char> || __is_same_v<T, signed char>;

template <typename T>
constant auto __is_i32_v = __is_integral_v<T> && sizeof(T) == 4;

template <typename T>
constant auto __is_fp16_v = __is_same_v<T, half>;

#if __HAVE_BFLOAT__
template <typename T>
constant auto __is_bf16_v = __is_same_v<T, bfloat>;
#endif

template <typename T>
constant auto __is_fp32_v = __is_same_v<T, float>;

template <typename T>
constant auto __is_device_addrspace_v = metal::__tensor_detail::__is_device_addrspace_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant auto __is_threadgroup_addrspace_v = metal::__tensor_detail::__is_threadgroup_addrspace_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant auto __is_constant_addrspace_v = metal::__tensor_detail::__is_constant_addrspace_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant auto __is_thread_addrspace_v = metal::__tensor_detail::__is_thread_addrspace_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant auto __is_unqualified_v = __is_same_v<T, __remove_cv_t<__remove_coherent_t<__remove_addrspace_t<__remove_ref_ptr_t<T>>>>>;

template <typename T>
struct __assert_false : __false_type
{
};

template <typename T>
constexpr constant bool __assert_false_v = __assert_false<T>::value;

template <class T>
struct __is_cooperative_tensor_type : __false_type
{
};

template <class ElementType, class Extents, class Layout>
struct __is_cooperative_tensor_type<metal::cooperative_tensor<ElementType, Extents, Layout>> : __true_type
{
};

template <class T>
constant auto __is_cooperative_tensor_type_v = __is_cooperative_tensor_type<__remove_cv_t<__remove_ref_ptr_t<T>>>::value;

template <typename T>
constant bool __is_tensor_handle_v = metal::is_tensor_handle_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant bool __is_tensor_offset_v = metal::has_tensor_offset_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant bool __is_tensor_inline_v = metal::is_tensor_inline_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant bool __is_tensor_type_v = __is_tensor_handle_v<T> || __is_tensor_offset_v<T> || __is_tensor_inline_v<T>;

template <typename T>
constexpr constant bool __is_tensorops_execution_scope_v = metal::is_execution_thread_v<__remove_cv_t<__remove_ref_ptr_t<T>>> ||
                                                           metal::is_execution_simdgroups_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
using __remove_cvref_t = __remove_cv_t<__remove_reference_t<T>>;

#if defined(__HAVE_TENSOR_MULTIPLANE__)
template<typename T>
struct is_tensor_blockwise : metal::false_type {};

template<class PlaneTag, class ElementType, size_t... BlockSizes>
struct is_tensor_blockwise<metal::tensor_blockwise<PlaneTag, ElementType, BlockSizes...>> : metal::true_type {};

template<typename T>
inline constant constexpr bool is_tensor_blockwise_v = is_tensor_blockwise<T>::value;

template<typename T>
struct tensor_plane_tag {};

template<class PlaneTag, class ElementType, size_t... BlockSizes>
struct tensor_plane_tag<metal::tensor_blockwise<PlaneTag, ElementType, BlockSizes...>> : metal::__type_traits_detail::type_identity<PlaneTag> {};

template<class PlaneTag, typename Tag, bool = is_tensor_blockwise_v<Tag>>
struct tag_matches_plane : metal::false_type {};

template<class PlaneTag, typename Tag>
struct tag_matches_plane<PlaneTag, Tag, true>
    : metal::bool_constant<metal::is_same_v<typename tensor_plane_tag<Tag>::type, PlaneTag>>
{};

template<class PlaneTag, typename... Tags>
struct find_tensor_blockwise_tag;

template<class PlaneTag>
struct find_tensor_blockwise_tag<PlaneTag> {};

template<class PlaneTag, typename Head, typename... Tail>
struct find_tensor_blockwise_tag<PlaneTag, Head, Tail...>
    : metal::conditional_t<tag_matches_plane<PlaneTag, Head>::value,
                           metal::__type_traits_detail::type_identity<Head>,
                           find_tensor_blockwise_tag<PlaneTag, Tail...>>
{};

template<class PlaneTag, typename T>
struct tensor_blockwise_tag {};

template<class PlaneTag, class ElementType, class Extents, class... Tags>
struct tensor_blockwise_tag<PlaneTag, metal::tensor<ElementType, Extents, Tags...>>
    : find_tensor_blockwise_tag<PlaneTag, Tags...>
{};

template<class PlaneTag, typename T>
struct has_tensor_blockwise : metal::false_type {};

template<class PlaneTag, class ElementType, class Extents, class... Tags>
struct has_tensor_blockwise<PlaneTag, metal::tensor<ElementType, Extents, Tags...>>
    : metal::bool_constant<(tag_matches_plane<PlaneTag, Tags>::value || ...)>
{};

template<class PlaneTag, typename T>
inline constant constexpr bool has_tensor_blockwise_v = has_tensor_blockwise<PlaneTag, T>::value;
#endif

} // namespace __tensor_ops_detail
} // namespace tensor_ops
} // namespace mpp

#pragma METAL internals : disable

#endif

#endif // __TensorOpsTraits__
