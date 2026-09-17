#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>
#include <ComputeGraph/ComputeGraphContext.h>
#include <ComputeGraph/ComputeGraphDebugDraw.h>

#include <metal_types>

namespace compute
{
struct context_t;

namespace api
{
PS_API thread graph_context_t &graph_context(thread compute::context_t &);

// TODO: deprecate these APIs
PS_API ushort thread_index_in_simdgroup(thread compute::context_t &);
PS_API ushort thread_position_in_threadgroup(thread compute::context_t &);
PS_API uint thread_position_in_grid(thread compute::context_t &);

PS_API ushort threads_per_simdgroup(thread compute::context_t &);
PS_API uint threads_per_threadgroup(thread compute::context_t &);

PS_API uint simdgroup_index_in_threadgroup(thread compute::context_t &);
}
}

namespace computegraph
{
struct compute_context
{
    PS_ALWAYS_INLINE compute_context(thread compute::context_t &_data)
    : data(_data)
    {}

    PS_ALWAYS_INLINE compute_context(const thread compute_context &_other)
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

    // TODO: private
    thread compute::context_t &data;
private:
    PS_ALWAYS_INLINE thread graph_context_t &graph_context() const { return compute::api::graph_context(data); }
};
} // namespace computegraph

#endif
