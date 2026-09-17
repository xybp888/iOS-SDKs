#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>
#include <ComputeGraph/ComputeGraphContext.h>
#include <ComputeGraph/ComputeGraphDebugDraw.h>
#include <ComputeGraph/ComputeGraphElement.h>
#include <ComputeGraph/ComputeGraphElementContext.h>
#include <ComputeGraph/ComputeGraphRandom.h>

#include <metal_types>

namespace initialize
{
struct context_t;

namespace api
{
PS_API thread graph_context_t &graph_context(thread initialize::context_t &);
PS_API thread system_element_context_t &system_element_context(thread initialize::context_t &);

PS_API uint source_element_index(thread initialize::context_t &);
PS_API uint spawn_index(thread initialize::context_t &);
}
}

namespace computegraph
{
struct initialization_context
{
    PS_ALWAYS_INLINE initialization_context(thread initialize::context_t &_data)
    : data(_data)
    {}

    PS_ALWAYS_INLINE initialization_context(const thread initialization_context &_context)
    : data(_context.data)
    {}

    PS_ALWAYS_INLINE computegraph::element_info element() const
    {
        return computegraph::element_info(system_element::api::element_data(initialize::api::system_element_context(data)));
    }

    PS_ALWAYS_INLINE uint element_index() const
    {
        return system_element::api::element_index(initialize::api::system_element_context(data));
    }

    /// For a derived element spawned with EventSource, returns the index of the source
    /// element. If this element was not spawned from an event source, 0 is returned.
    PS_ALWAYS_INLINE uint source_element_index() const
    {
        return initialize::api::source_element_index(data);
    }

    /// For a derived element spawned from an emitter, returns the sequential index of
    /// the spawn from that emitter. If this was spawned from an EventSource or from the CPU,
    /// this value is the index within the current spawn request.
    PS_ALWAYS_INLINE uint spawn_index() const
    {
        return initialize::api::spawn_index(data);
    }

    PS_ALWAYS_INLINE computegraph::random_generator random() thread
    {
        return graph().random();
    }

    PS_ALWAYS_INLINE computegraph::graph_context graph() const
    {
        return computegraph::graph_context(initialize::api::graph_context(data));
    }

    PS_ALWAYS_INLINE computegraph::debug_draw debug_draw() const
    {
        return graph().debug_draw();
    }

    // TODO: private
    thread initialize::context_t &data;
};
} // namespace computegraph

#endif
