#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>
#include <ComputeGraph/ComputeGraphDebugDraw.h>
#include <ComputeGraph/ComputeGraphRandom.h>
#include <ComputeGraph/ComputeGraphTextures.h>

#include <metal_types>

struct graph_context_t;

namespace graph
{
struct context_t;

namespace api
{
PS_API float age(thread graph_context_t &);
PS_API float delta_time(thread graph_context_t &);

PS_API metal::float4x4 local_to_world(thread graph_context_t &);
PS_API metal::float4x4 world_to_local(thread graph_context_t &);
}
} // namepsace graph

namespace api
{
PS_API thread random_context_t &random(thread graph_context_t &base);
}

namespace computegraph
{
struct graph_context
{
    PS_ALWAYS_INLINE graph_context(thread graph_context_t &ctx)
    : context(ctx)
    {}

    PS_ALWAYS_INLINE computegraph::random_generator random() thread
    {
        return api::random(context);
    }

    PS_ALWAYS_INLINE computegraph::debug_draw debug_draw() const
    {
        return computegraph::debug_draw(context);
    }

    PS_ALWAYS_INLINE computegraph::global_textures textures() const
    {
        return computegraph::global_textures(context);
    }

    PS_ALWAYS_INLINE float age() const
    {
        return graph::api::age(context);
    }

    PS_ALWAYS_INLINE float delta_time() const
    {
        return graph::api::delta_time(context);
    }

    PS_ALWAYS_INLINE metal::float4x4 local_to_world() const
    {
        return graph::api::local_to_world(context);
    }

    PS_ALWAYS_INLINE metal::float4x4 world_to_local() const
    {
        return graph::api::world_to_local(context);
    }

private:
    thread graph_context_t &context;
};

} // namespace computegraph

#endif
