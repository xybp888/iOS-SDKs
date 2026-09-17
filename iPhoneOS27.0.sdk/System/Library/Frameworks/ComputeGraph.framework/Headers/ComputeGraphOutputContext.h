#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>
#include <ComputeGraph/ComputeGraphRandom.h>
#include <ComputeGraph/ComputeGraphElementContext.h>

#include <metal_types>

namespace output
{
struct context_t;

namespace api
{
PS_API uint output_index(thread output::context_t &);
PS_API thread graph_context_t &graph_context(thread output::context_t &);
PS_API thread system_element_context_t &system_element_context(thread output::context_t &);

PS_API float3 position(thread output::context_t &);
PS_API void set_position(thread output::context_t &, float3);

PS_API float2 size(thread output::context_t &);
PS_API void set_size(thread output::context_t &, float2);

PS_API float2 scale(thread output::context_t &);
PS_API void set_scale(thread output::context_t &, float2);

PS_API half4 color(thread output::context_t &);
PS_API void set_color(thread output::context_t &, half4);

PS_API float2 uv_offset(thread output::context_t &);
PS_API void set_uv_offset(thread output::context_t &, float2);

PS_API float2 uv_scale(thread output::context_t &);
PS_API void set_uv_scale(thread output::context_t &, float2);

} // namespace api
} // namespace update


namespace computegraph
{
struct output_context
{
    PS_ALWAYS_INLINE output_context(thread output::context_t &_context)
    : context(_context)
    {}

    PS_ALWAYS_INLINE uint element_id() const
    {
        return system_element::api::element_index(output::api::system_element_context(context));
    }

    /// Returns true if the current context has a valid element to read.
    PS_ALWAYS_INLINE bool is_reader() const
    {
        return system_element::api::is_reader_thread(output::api::system_element_context(context));
    }

    /// Returns true if the current context is the authority for its current element.
    PS_ALWAYS_INLINE bool is_authority() const
    {
        return system_element::api::is_authority_thread(output::api::system_element_context(context));
    }

    /// Returns true if the current context is expected to write to its output, regardless of
    /// whether it has an active element.
    PS_ALWAYS_INLINE bool is_output() const
    {
        return system_element::api::is_output_thread(output::api::system_element_context(context));
    }

    // Returns the output index ordering.
    //
    // This may be different from elementId() in cases where particles are sorted.
    PS_ALWAYS_INLINE uint output_index() const
    {
        return output::api::output_index(context);
    }

    PS_ALWAYS_INLINE float3 output_position() const
    {
        return output::api::position(context);
    }
    PS_ALWAYS_INLINE void set_output_position(float3 value)
    {
        output::api::set_position(context, value);
    }

    /// Returns the current output size.
    ///
    /// This begin's with the element's current value, and can be customized during
    /// the output stage without affecting the element.
    PS_ALWAYS_INLINE float2 output_size() const
    {
        return output::api::size(context);
    }
    PS_ALWAYS_INLINE void set_output_size(float2 value)
    {
        output::api::set_size(context, value);
    }

    /// Returns the current output scale.
    ///
    /// This begin's with the element's current value, and can be customized during
    /// the output stage without affecting the element.
    PS_ALWAYS_INLINE float2 output_scale() const
    {
        return output::api::scale(context);
    }
    PS_ALWAYS_INLINE void set_output_scale(float2 value)
    {
        output::api::set_scale(context, value);
    }

    /// Returns the current output color.
    ///
    /// This begin's with the element's current value, and can be customized during
    /// the output stage without affecting the element.
    PS_ALWAYS_INLINE half4 output_color() const
    {
        return output::api::color(context);
    }
    PS_ALWAYS_INLINE void set_output_color(half3 value)
    {
        output::api::set_color(context, half4(value, output_color().a));
    }

    /// Returns the current output alpha.
    ///
    /// This begin's with the element's current value, and can be customized during
    /// the output stage without affecting the element.
    PS_ALWAYS_INLINE half output_alpha() const
    {
        return output::api::color(context).a;
    }
    PS_ALWAYS_INLINE void set_output_alpha(half value)
    {
        output::api::set_color(context, half4(output_color().rgb, value));
    }


    /// Returns the current output uv offset.
    ///
    /// This begin's with the (0, 0), and can be customized during
    /// the output stage without affecting the element.
    PS_ALWAYS_INLINE float2 uv_offset() const
    {
        return output::api::uv_offset(context);
    }
    PS_ALWAYS_INLINE void set_uv_offset(float2 value)
    {
        output::api::set_uv_offset(context, value);
    }

    /// Returns the current output uv scale.
    ///
    /// This begin's with (1, 1), and can be customized during
    /// the output stage without affecting the element.
    PS_ALWAYS_INLINE float2 uv_scale() const
    {
        return output::api::uv_scale(context);
    }

    PS_ALWAYS_INLINE void set_uv_scale(float2 value)
    {
        output::api::set_uv_scale(context, value);
    }

    PS_ALWAYS_INLINE computegraph::graph_context graph() const
    {
        return computegraph::graph_context(output::api::graph_context(context));
    }

    PS_ALWAYS_INLINE computegraph::element_info element() const
    {
        return computegraph::element_info(system_element::api::element_data(output::api::system_element_context(context)));
    }

    PS_ALWAYS_INLINE computegraph::random_generator random() thread
    {
        return base().random();
    }

    PS_ALWAYS_INLINE computegraph::element_context base() const
    {
        return computegraph::element_context(output::api::system_element_context(context));
    }

    PS_ALWAYS_INLINE computegraph::debug_draw debug_draw() const
    {
        return base().debug_draw();
    }

    // TODO: private
    thread output::context_t &context;
};

} // namespace computegraph

#endif
