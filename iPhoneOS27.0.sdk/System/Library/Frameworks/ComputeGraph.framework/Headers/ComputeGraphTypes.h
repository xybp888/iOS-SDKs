#pragma once

#include <simd/simd.h>

#if defined(__METAL_VERSION__)
#   include <metal_types>
#   include <metal_logging>
#   define PS_CONSTANT constant
#   define PS_THREAD thread
#   define PS_THREADGROUP threadgroup
#   define PS_DEVICE device
#   define ps_binding_type int32_t
#else
#   include <sys/types.h>
#   include <stdbool.h>
#   include <stddef.h>
#   define PS_CONSTANT
#   define PS_THREAD
#   define PS_THREADGROUP
#   define PS_DEVICE
#   define ps_binding_type intptr_t
#endif

#define PS_AVAILABILE(X) __attribute__((availability(x)))
#define PS_DEPRECATED(M...) __attribute__((deprecated(M)))
#define PS_ALWAYS_INLINE inline __attribute__ ((always_inline))
#define PS_ENUM(type) enum __attribute__((enum_extensibility(closed))) : type

// Explicit annotation for public/exported
#define PS_API [[visible]]

// Explicit annotation of internal functions
#define PS_INTERNAL

// MARK: - Element structures

#if defined(__METAL_VERSION__)

struct graph_context_t;
struct system_context_t;
struct debug_draw_context_t;
struct random_context_t;

namespace emitter
{
struct context_t;
}

namespace initialize
{
struct context_t;
}

namespace simulate
{
struct context_t;
}

namespace output
{
struct context_t;
}

namespace compute
{
struct context_t;
}

namespace texture
{
struct context_t;
}

// TODO: shorter name. "access" would be ideal, but it conflicts with metal::access.
enum class value_access
{
    read,
    write,
    read_write
};

constexpr bool is_read_only(value_access access)
{
    return access == value_access::read;
}

constexpr bool is_writable(value_access access)
{
    return access == value_access::write || access == value_access::read_write;
}

/// A uniform value which is global to *all nodes* binding a value of the same type.
///
/// @discussion Globals are matched by *type only* and are intended for use with
/// compound structure types.
template<typename T>
struct shared_uniform
{
    constant T &value;

    constant T *operator->() thread {
        return &value;
    }

    operator T() const thread {
        return value;
    }
};

/// Per-emitter state which is read+write from the emitter phase and unavailable from later phases.
///
/// @discussion System State variables are matched by both type and name, so multiple
/// attributes with the same type may be specified by using different names.
template<typename T>
struct emitter_state
{
    device T &value;

    device T *operator->() thread {
        return &value;
    }

    operator T() const thread {
        return value;
    }
};

/// Per-group state which is read+write during the simulation state.
///
/// @discussion Group State variables are matched by both type and name, so multiple
/// attributes with the same type may be specified by using different names.
template<typename T>
struct group_state
{
    device T &value;

    device T *operator->() thread {
        return &value;
    }

    operator T() const thread {
        return value;
    }
};

/// Threadgroup memory binding with type and size parameters. Use ``group_temporary`` for a
/// more convenient alternative.
template<typename T, size_t N>
struct threadgroup_memory
{
    threadgroup T &data;

    operator threadgroup T &() {
        return data;
    }
};

template<typename T>
using group_temporary = threadgroup_memory<T, sizeof(T)>;

/// A per-vertex attribute which can be written from the output stage.
///
/// The ``output_attribute`` attribute allows accessing the entire buffer's contents.
/// Use the OutputContext's``context.range`` to index into this attribute.
///
/// @discussion In order for the attribute to be usable from a Vertex shader,
/// its name must match an existing semantic. See ``LowLevelMesh.VertexSemantic``.
template<typename T, bool required = true>
struct output_attribute
{
    struct attribute_ref
    {
        const bool has_value;
        device T* value;

        T operator=(T newValue) thread {
            if (has_value) {
                *value = newValue;
            }
            return newValue;
        }

        operator T() const thread {
            if (has_value) {
                return *value;
            } else {
                return {};
            }
        }
    };

    const bool _has_value;
    const int _stride;
    const int _count;
    device T* value;

    bool has_value() const thread {
        return _has_value;
    }

    attribute_ref operator [](size_t index) {
        if (_has_value) {
            device uint8_t *bytes = (device uint8_t *)value;

            return attribute_ref {
                .has_value = true,
                .value = (device T *)(bytes + _stride * index)
            };
        } else {
            return {
                .has_value = false,
            };
        }
    }
};

/// A per-element attribute which can be read/written.
///
/// @discussion Attributes are matched by both type and name, so multiple attributes
/// of the same type may be specified by using different names.
///
/// "Built-in" attributes can also be accessed using attribute, for example
/// `element_state<float3> velocity`.
template<typename T, value_access a = value_access::read, bool required = true, typename _Enable = void>
struct element_state
{
    bool _has_value;
    const size_t _offset;
    thread T* value;
};

template<typename T, value_access a>
struct element_state<T, a, true, typename metal::enable_if_t<is_read_only(a)> >
{
    const bool _has_value = true;
    const size_t _offset;
    const thread T* value;

    bool has_value() const thread {
        return true;
    }

    const thread T &operator->() thread {
        return value;
    }

    operator T() const thread {
        return *value;
    }

    /// Conversion operator from a required to optional attribute
    operator element_state<T, a, false, typename metal::enable_if_t<is_read_only(a)> > () const thread {
        return {true, value};
    }
};

template<typename T, value_access a>
struct element_state<T, a, true, typename metal::enable_if_t<is_writable(a)> >
{
    const bool _has_value = true;
    const size_t _offset;
    thread T* value;

    constexpr bool has_value() const thread {
        return true;
    }

    thread T &operator->() thread {
        return value;
    }

    void operator=(T newValue) thread {
        *value = newValue;
    }

    operator T() const thread {
        return *value;
    }
};

template<typename T, value_access a>
struct element_state<T, a, false, typename metal::enable_if_t<is_read_only(a)> >
{
    const bool _has_value;
    const size_t _offset;
    const thread T* value;

    bool has_value() const thread {
        return _has_value;
    }

    T operator->() thread {
        if (_has_value) {
            return *value;
        } else {
            return {};
        }
    }

    operator T() const thread {
        if (_has_value) {
            return *value;
        } else {
            return {};
        }
    }
};

template<typename T, value_access a>
struct element_state<T, a, false, typename metal::enable_if_t<is_writable(a)> >
{
    const bool _has_value;
    const size_t _offset;
    thread T* value;

    bool has_value() const thread {
        return _has_value;
    }

    void operator=(T newValue) thread {
        if (_has_value) {
            *value = newValue;
        }
    }

    operator T() const thread {
        if (_has_value) {
            return *value;
        } else {
            return {};
        }
    }
};

/// A typed buffer of unknown size
template<typename T>
struct pointer
{
    device T *value;
    uint3 __unused;

    device T *operator->() thread {
        return value;
    }
};

template<typename T>
struct buffer1d
{
    device T *values;
    uint3 count;

    T read(uint x) thread {
        if (x < count.x) {
            return values[x];
        } else {
            return {};
        }
    }
};

template<typename T>
struct buffer2d
{
    device T *values;
    uint3 count;

    T read(uint2 pos) thread {
        return read(pos.x, pos.y);
    }

    T read(uint x, uint y) thread {
        if (x < count.x && y < count.y) {
            return values[x + y * count.x];
        } else {
            return {};
        }
    }
};

template<typename T>
struct buffer3d
{
    device T *values;
    uint3 count;

    T read(uint3 pos) thread {
        return read(pos.x, pos.y, pos.z);
    }

    T read(uint x, uint y, uint z) thread {
        if (x < count.x && y < count.y && z < count.z) {
            return values[x + y * count.x + z * (count.x * count.y)];
        } else {
            return {};
        }
    }
};

/// Optional buffer with stride and count. Used internally during compilation.
template<typename T>
struct strided_buffer
{
    const bool _has_value;
    const int _stride;
    const int count;
    device T* value;

    struct value_ref
    {
        const bool has_value;
        device T* value;

        PS_ALWAYS_INLINE T operator=(const thread value_ref &newValue) thread {
            return (*this) = (T)newValue;
        }

        PS_ALWAYS_INLINE T operator=(T newValue) thread {
            if (has_value) {
                *value = newValue;
            }
            return newValue;
        }

        PS_ALWAYS_INLINE operator T() const thread {
            if (has_value) {
                return *value;
            } else {
                return {};
            }
        }
    };

    PS_ALWAYS_INLINE value_ref operator [] (size_t index) const {
        if (_has_value && index < (size_t)count) {
            device uint8_t *bytes = (device uint8_t *)value;

            return value_ref {
                .has_value = true,
                .value = (device T *)(bytes + _stride * index)
            };
        } else {
            return {
                .has_value = false,
            };
        }
    }

    explicit operator bool () const { return _has_value; }
};

// Mark - Built-ins

struct thread_position_in_grid {
    uint3 value;

    operator uint() const { return value.x; }
    operator uint2() const { return value.xy; }
    operator uint3() const { return value; }
};

struct threads_per_grid {
    uint3 value;

    operator uint() const { return value.x; }
    operator uint2() const { return value.xy; }
    operator uint3() const { return value; }
};

struct threads_per_threadgroup {
    uint3 value;

    operator uint() const { return value.x; }
    operator uint2() const { return value.xy; }
    operator uint3() const { return value; }
};

#endif // defined(__METAL_VERSION__)

