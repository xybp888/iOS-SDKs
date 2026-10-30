#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>

#include <metal_types>
#include <metal_array>

struct graph_context_t;

namespace debugdraw
{
namespace api
{
PS_API void lines(thread debug_draw_context_t &, metal::array_ref<thread float3> points, half4 color);
PS_API void line_strip(thread debug_draw_context_t &, metal::array_ref<thread float3> points, half4 color);
PS_API bool enabled(thread debug_draw_context_t &);

PS_API thread debug_draw_context_t &graph_debug_draw_context(thread graph_context_t &);
}
}

namespace computegraph
{

struct debug_draw
{
    PS_ALWAYS_INLINE debug_draw(thread graph_context_t & _context)
    : context(debugdraw::api::graph_debug_draw_context(_context))
    {}

    PS_ALWAYS_INLINE debug_draw(thread debug_draw_context_t & _context)
    : context(_context)
    {}

    PS_ALWAYS_INLINE void line(float3 from, float3 to, half4 color)
    {
        float3 points[2] = {from, to};
        debugdraw::api::lines(context, points, color);
    }

    PS_ALWAYS_INLINE void lines(metal::array_ref<thread float3> points, half4 color)
    {
        debugdraw::api::lines(context, points, color);
    }

    PS_ALWAYS_INLINE void line_strip(metal::array_ref<thread float3> points, half4 color)
    {
        debugdraw::api::line_strip(context, points, color);
    }

    PS_ALWAYS_INLINE bool enabled() const
    {
        return debugdraw::api::enabled(context);
    }
private:
    thread debug_draw_context_t &context;
};

}

#endif
