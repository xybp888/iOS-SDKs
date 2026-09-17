#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>
#include <ComputeGraph/ComputeGraphDebugDraw.h>
#include <ComputeGraph/ComputeGraphRandom.h>
#include <ComputeGraph/ComputeGraphElement.h>
#include <ComputeGraph/ComputeGraphContext.h>

#include <metal_types>

struct system_element_context_t;

namespace system_element
{
namespace api
{
PS_API void terminate(thread system_element_context_t &base);
PS_API thread graph_context_t &graph_context(const thread system_element_context_t &base);

PS_API uint element_index(thread system_element_context_t &);

PS_API bool is_reader_thread(thread system_element_context_t &);
PS_API bool is_authority_thread(thread system_element_context_t &);
PS_API bool is_output_thread(thread system_element_context_t &);

PS_API thread element_context_t &element_data(thread system_element_context_t &);

PS_API uint element_capacity(thread system_element_context_t &);
}
}

namespace computegraph
{
struct element_context
{
    PS_ALWAYS_INLINE element_context(thread system_element_context_t &data)
    : context(data)
    {}

    PS_ALWAYS_INLINE uint element_index() const thread
    {
        return system_element::api::element_index(context);
    }

    /// Returns true if the thread executing had an element to read.
    ///
    /// @discussion This can be true for output threads that need to write null elements to their output.
    PS_ALWAYS_INLINE bool is_reader() const thread
    {
        return system_element::api::is_reader_thread(context);
    }

    /// Returns true if the thread executing is the authority on its element
    ///
    /// @discussion This can be false for 'helper threads', when simulating strips. These threads
    /// will calculate values, but not write data. This concept is similar to Metal's helper threads,
    /// however Metal uses helper threads exclusively for render pipelines.
    PS_ALWAYS_INLINE bool is_authority() const thread
    {
        return system_element::api::is_authority_thread(context);
    }

    PS_ALWAYS_INLINE computegraph::element_info element() const thread
    {
        return computegraph::element_info(system_element::api::element_data(context));
    }

    PS_ALWAYS_INLINE computegraph::random_generator random() thread
    {
        return api::random(system_element::api::graph_context(context));
    }

    PS_ALWAYS_INLINE computegraph::debug_draw debug_draw() const
    {
        return computegraph::debug_draw(system_element::api::graph_context(context));
    }
private:
    thread system_element_context_t &context;
};

} // namespace computegraph

#endif
