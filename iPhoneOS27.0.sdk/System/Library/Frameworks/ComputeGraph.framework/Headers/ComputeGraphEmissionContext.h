#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>
#include <ComputeGraph/ComputeGraphContext.h>
#include <ComputeGraph/ComputeGraphRandom.h>

#include <metal_types>

namespace emitter
{
struct context_t;

namespace api
{
PS_API void spawn(thread emitter::context_t &, int count);
PS_API thread graph_context_t &graph_context(thread emitter::context_t &);
PS_API float lifetime(thread emitter::context_t &);
}
}

namespace computegraph
{
/// Context for emitting new particles.
///
/// @discussion Adding a ``emission_context`` parameter to a function designates it as
/// an emission module.
///
/// @see ``ParticleEmitterInfo`` for read-only information about the current emitter.
struct emission_context
{
    PS_ALWAYS_INLINE emission_context(thread emitter::context_t &_context)
    : data(_context)
    {
    }

    PS_ALWAYS_INLINE emission_context(const thread emission_context &other)
    : data(other.data)
    {
    }

    PS_ALWAYS_INLINE float delta_time() const
    {
        return graph::api::delta_time(emitter::api::graph_context(data));
    }

    PS_ALWAYS_INLINE float age() const
    {
        return graph::api::age(emitter::api::graph_context(data));
    }

    PS_ALWAYS_INLINE float lifetime() const thread
    {
        return emitter::api::lifetime(data);
    }

    /// Adds ``count`` elements to the current spawn request.
    PS_ALWAYS_INLINE void spawn(uint count)
    {
        emitter::api::spawn(data, count);
    }

    PS_ALWAYS_INLINE computegraph::debug_draw debug_draw() const
    {
        return computegraph::debug_draw(emitter::api::graph_context(data));
    }

    PS_ALWAYS_INLINE computegraph::random_generator random() thread
    {
        return api::random(emitter::api::graph_context(data));
    }

    PS_ALWAYS_INLINE graph_context graph() thread
    {
        return graph_context(emitter::api::graph_context(data));
    }

    thread emitter::context_t &data;
};

} // namespace computegraph

#endif

