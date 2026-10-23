#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>

#include <metal_types>

struct element_context_t;

namespace element
{
namespace api
{
PS_API float age(thread element_context_t &element);
PS_API void set_age(thread element_context_t &element, float age);

PS_API float lifetime(thread element_context_t &element);
PS_API void set_lifetime(thread element_context_t &element, float lifetime);

PS_API float3 position(thread element_context_t &element);
PS_API void set_position(thread element_context_t &element, float3 position);

PS_API float2 size(thread element_context_t &element);
PS_API void set_size(thread element_context_t &element, float2 size);

PS_API half4 color(thread element_context_t &element);
PS_API void set_color(thread element_context_t &element, half4 color);

PS_API float3 velocity(thread element_context_t &element);
PS_API void set_velocity(thread element_context_t &element, float3 velocity);

PS_API bool is_alive(thread element_context_t &element);
}
}

namespace computegraph
{
/// Information about a single element, usable in multiple stages, such as
/// initialization and simulation.
struct element_info
{
    PS_ALWAYS_INLINE element_info(thread element_context_t &_element)
    : element(_element)
    {}

    PS_ALWAYS_INLINE float age()
    {
        return element::api::age(element);
    }

    PS_ALWAYS_INLINE void set_age(float value)
    {
        element::api::set_age(element, value);
    }

    PS_ALWAYS_INLINE float lifetime()
    {
        return element::api::lifetime(element);
    }

    PS_ALWAYS_INLINE void set_lifetime(float value)
    {
        return element::api::set_lifetime(element, value);
    }

    PS_ALWAYS_INLINE float3 position()
    {
        return element::api::position(element);
    }

    PS_ALWAYS_INLINE void set_position(float3 value)
    {
        return element::api::set_position(element, value);
    }

    PS_ALWAYS_INLINE float2 size()
    {
        return element::api::size(element);
    }

    PS_ALWAYS_INLINE void set_size(float2 value)
    {
        return element::api::set_size(element, value);
    }

    PS_ALWAYS_INLINE half4 color() const
    {
        return element::api::color(element);
    }

    PS_ALWAYS_INLINE void set_color(half3 value)
    {
        set_color(half4(value, color().a));
    }

    PS_ALWAYS_INLINE half alpha() const
    {
        return element::api::color(element).a;
    }

    PS_ALWAYS_INLINE void set_alpha(half value)
    {
        set_color(half4(color().rgb, value));
    }

    PS_ALWAYS_INLINE void set_color(half4 color)
    {
        element::api::set_color(element, color);
    }

    PS_ALWAYS_INLINE float3 velocity() const
    {
        return element::api::velocity(element);
    }

    PS_ALWAYS_INLINE void set_velocity(float3 velocity)
    {
        element::api::set_velocity(element, velocity);
    }

    PS_ALWAYS_INLINE void add_velocity(float3 delta)
    {
        set_velocity(velocity() + delta);
    }

    PS_ALWAYS_INLINE bool is_alive() const
    {
        return element::api::is_alive(element);
    }
private:
    thread element_context_t &element;
};
} // namespace computegraph

#endif
