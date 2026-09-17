#pragma once

#if defined(__METAL_VERSION__)

#include <metal_stdlib>
#include <metal_types>

#include <ComputeGraph/ComputeGraphTypes.h>

namespace random
{
namespace api
{
PS_API uint16_t random_uint16(uint16_t seed);
PS_API uint32_t random_uint32(uint32_t seed);

PS_API half random01_half(uint16_t seed);
PS_API float random01_float(uint32_t seed);

PS_API uint32_t increment_seed(thread random_context_t &rng, uint32_t count);

/// Returns the current seed without incrementing it
PS_API uint32_t seed(const thread random_context_t &rng);
}
}
namespace computegraph
{
struct random_generator
{
    PS_ALWAYS_INLINE random_generator(thread random_context_t &_context)
    : context(_context)
    {}
    
    PS_ALWAYS_INLINE uint16_t uint16()
    {
        return random::api::random_uint16(uint16_t(next_seed()));
    }
    
    PS_ALWAYS_INLINE uint32_t uint32()
    {
        return random::api::random_uint32(next_seed());
    }
    
    PS_ALWAYS_INLINE float float_01()
    {
        return random::api::random01_float(next_seed());
    }
    
    PS_ALWAYS_INLINE float2 float2_01()
    {
        uint32_t seed = next_seed(2);
        
        return {
            random::api::random01_float(seed),
            random::api::random01_float(seed+1)
        };
    }
    
    PS_ALWAYS_INLINE float3 float3_01()
    {
        uint32_t seed = next_seed(3);
        
        return {
            random::api::random01_float(seed),
            random::api::random01_float(seed+1),
            random::api::random01_float(seed+2)
        };
    }
    
    PS_ALWAYS_INLINE float4 float4_01()
    {
        uint32_t seed = next_seed(4);
        
        return {
            random::api::random01_float(seed),
            random::api::random01_float(seed+1),
            random::api::random01_float(seed+2),
            random::api::random01_float(seed+3)
        };
    }
    
    PS_ALWAYS_INLINE half half_01()
    {
        uint32_t seed = next_seed(1);
        
        return random::api::random01_half(seed);
    }
    
    PS_ALWAYS_INLINE half2 half2_01()
    {
        uint32_t seed = next_seed(2);
        
        return {
            random::api::random01_half(seed),
            random::api::random01_half(seed+1),
        };
    }
    
    PS_ALWAYS_INLINE half3 half3_01()
    {
        uint32_t seed = next_seed(3);
        
        return {
            random::api::random01_half(seed),
            random::api::random01_half(seed+1),
            random::api::random01_half(seed+2),
        };
    }
    
    PS_ALWAYS_INLINE half4 half4_01()
    {
        uint32_t seed = next_seed(4);
        
        return {
            random::api::random01_half(seed),
            random::api::random01_half(seed+1),
            random::api::random01_half(seed+2),
            random::api::random01_half(seed+3)
        };
    }
    
    /// Returns the current seed and increments it `count` times.
    PS_ALWAYS_INLINE uint32_t next_seed(uint32_t count = 1)
    {
        return random::api::increment_seed(context, count);
    }
    
    /// Returns the current seed without incrementing it
    PS_ALWAYS_INLINE uint32_t seed() const
    {
        return random::api::seed(context);
    }
private:
    thread random_context_t &context;
};

} // namespace computegraph

#endif // __METAL_VERSION__
