#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>
#include <ComputeGraph/ComputeGraphRandom.h>
#include <ComputeGraph/ComputeGraphDebugDraw.h>
#include <ComputeGraph/ComputeGraphElement.h>
#include <ComputeGraph/ComputeGraphElementContext.h>
#include <ComputeGraph/ComputeGraphContext.h>

#include <metal_types>

namespace simulate
{
struct context_t;

namespace api
{
PS_API thread float3 &force(thread simulate::context_t &);
PS_API thread graph_context_t &graph_context(thread simulate::context_t &);
PS_API thread system_element_context_t &system_element_context(thread simulate::context_t &);
} // namespace api
} // namespace update

namespace computegraph
{
struct simulation_context
{
    PS_ALWAYS_INLINE simulation_context(thread simulate::context_t &_data)
    : data(_data)
    {}

    PS_ALWAYS_INLINE simulation_context(const thread simulation_context &_other)
    : data(_other.data)
    {}

    PS_ALWAYS_INLINE uint element_index() const
    {
        return system_element::api::element_index(system_element_context());
    }

    PS_ALWAYS_INLINE computegraph::element_info element() const
    {
        return computegraph::element_info(system_element::api::element_data(system_element_context()));
    }

    PS_ALWAYS_INLINE computegraph::random_generator random() thread
    {
        return graph().random();
    }

    PS_ALWAYS_INLINE computegraph::global_textures textures() const
    {
        return computegraph::global_textures(graph_context());
    }

    PS_ALWAYS_INLINE computegraph::graph_context graph() const
    {
        return computegraph::graph_context(graph_context());
    }

    PS_ALWAYS_INLINE computegraph::element_context base() const
    {
        return computegraph::element_context(system_element_context());
    }

    PS_ALWAYS_INLINE computegraph::debug_draw debug_draw() const
    {
        return graph().debug_draw();
    }

    PS_ALWAYS_INLINE void terminate()
    {
        system_element::api::terminate(system_element_context());
    }

    PS_ALWAYS_INLINE float delta_time() const
    {
        return graph::api::delta_time(graph_context());
    }

    PS_ALWAYS_INLINE float3 force() const
    {
        return simulate::api::force(data);
    }

    PS_ALWAYS_INLINE void set_force(float3 force)
    {
        simulate::api::force(data) = force;
    }

    // TODO: make me private
    thread simulate::context_t &data;
private:
    PS_ALWAYS_INLINE thread graph_context_t &graph_context() const { return simulate::api::graph_context(data); }
    PS_ALWAYS_INLINE thread system_element_context_t &system_element_context() const { return simulate::api::system_element_context(data); }
};

} // namespace computegraph

#endif
