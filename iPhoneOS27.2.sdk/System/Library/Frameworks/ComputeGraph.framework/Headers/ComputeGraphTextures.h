#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>

#include <metal_types>
#include <metal_texture>

struct graph_context_t;

namespace textures
{
namespace api
{
PS_API metal::texture1d<float> noise1d(thread graph_context_t &);
PS_API metal::texture2d<float> noise2d(thread graph_context_t &);
PS_API metal::texture3d<float> noise3d(thread graph_context_t &);
} // namespace api
} // namespace textures

namespace computegraph
{

// TODO: replace me with shared_uniform texture bindings
struct global_textures
{
    PS_ALWAYS_INLINE global_textures(thread graph_context_t &_data)
        : data(_data)
    {
    }

    PS_ALWAYS_INLINE global_textures(const thread global_textures &other)
        : data(other.data)
    {
    }

    PS_ALWAYS_INLINE metal::texture1d<float> noise1d() const thread
    {
        return textures::api::noise1d(data);
    }

    PS_ALWAYS_INLINE metal::texture2d<float> noise2d() const thread
    {
        return textures::api::noise2d(data);
    }

    PS_ALWAYS_INLINE metal::texture3d<float> noise3d() const thread
    {
        return textures::api::noise3d(data);
    }
private:
    thread graph_context_t &data;
};
} // namespace computegraph


#endif
