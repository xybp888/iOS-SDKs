#pragma once

#if defined(__METAL_VERSION__)

#include <ComputeGraph/ComputeGraphTypes.h>

#include <metal_types>

struct group_context_t;

namespace group
{
struct context_t;

namespace api
{
PS_API uint group_index_in_system(thread group_context_t &);
PS_API uint group_maximum_in_system(thread group_context_t &);

PS_API uint simdgroup_index_in_group(thread group_context_t &);
PS_API uint simdgroups_per_group(thread group_context_t &);

PS_API uint element_index_in_group(thread group_context_t &);
PS_API uint element_active_count_in_group(thread group_context_t &);
PS_API uint element_maximum_in_group(thread group_context_t &);
}
}

namespace computegraph
{
/// A context for elements that are grouped together, either as a strip
/// (like a ribbon) or as an unstructured group.
struct group_context
{
    PS_ALWAYS_INLINE group_context(thread group_context_t &ctx)
    : _context(ctx)
    {}

    /// Index of the current group within the system overall
    PS_ALWAYS_INLINE ushort group_index_in_system() const
    {
        return group::api::group_index_in_system(_context);
    }

    /// The current simdgroup's index within the element group or ribbon
    PS_ALWAYS_INLINE ushort simdgroup_index_in_group() const
    {
        return group::api::simdgroup_index_in_group(_context);
    }

    /// Returns the number of simdgroups that execute per element group or ribbon.
    PS_ALWAYS_INLINE ushort simdgroups_per_group() const
    {
        return group::api::simdgroups_per_group(_context);
    }

    /// Returns the index of the current element within the current group.
    PS_ALWAYS_INLINE uint element_index_in_group() const
    {
        return group::api::element_index_in_group(_context);
    }

    /// Number of elements active in the current group or ribbon.
    PS_ALWAYS_INLINE uint active_element_count() const
    {
        return group::api::element_active_count_in_group(_context);
    }

    /// Maximum number of elements that can be active within a group.
    ///
    /// This value is configured in the simulation and is constant for the lifetime of the graph.
    PS_ALWAYS_INLINE uint element_maximum_in_group() const
    {
        return group::api::element_maximum_in_group(_context);
    }

    /// Maximum number of groups that can exist in the system.
    ///
    /// The number of active groups will always be less than or equal to this number
    PS_ALWAYS_INLINE uint maximum_groups_in_system() const
    {
        return group::api::group_maximum_in_system(_context);
    }
private:
    thread group_context_t &_context;
};
} // namespace computegraph

#endif
