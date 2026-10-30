#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>
#include <ComputeGraph/ComputeGraphContext.h>
#include <ComputeGraph/ComputeGraphDebugDraw.h>

#include <metal_types>

namespace texture
{
struct context_t;

namespace api
{
PS_API metal::texture2d<float, metal::access::read_write> texture(thread texture::context_t &);
PS_API thread graph_context_t &graph_context(thread texture::context_t &);
}
}

namespace computegraph
{

/// A context for creating a texture.
struct texture_context
{
    PS_ALWAYS_INLINE texture_context(thread texture::context_t &_data)
    : data(_data)
    {}

    PS_ALWAYS_INLINE texture_context(const thread texture_context &_other)
    : data(_other.data)
    {}

    PS_ALWAYS_INLINE computegraph::graph_context graph() const
    {
        return computegraph::graph_context(graph_context());
    }

    PS_ALWAYS_INLINE computegraph::debug_draw debug_draw() const
    {
        return computegraph::debug_draw(graph_context());
    }

    PS_ALWAYS_INLINE metal::texture2d<float, metal::access::read_write> texture() const
    {
        return texture::api::texture(data);
    }

    // TODO: private
    thread texture::context_t &data;
private:
    PS_ALWAYS_INLINE thread graph_context_t &graph_context() const { return texture::api::graph_context(data); }
};
} // namespace computegraph

#endif

