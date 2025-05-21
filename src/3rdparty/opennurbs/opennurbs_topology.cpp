//
// Copyright (c) 1993-2022 Robert McNeel & Associates. All rights reserved.
// OpenNURBS, Rhinoceros, and Rhino3D are registered trademarks of Robert
// McNeel & Associates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

bool ON_ComponentAttributes::EdgeIsEligible(
  unsigned int edge_attributes_filter,
  const class ON_SubDEdge* edge
)
{
  return ON_ComponentAttributes::EdgeIsEligible(edge_attributes_filter, (nullptr != edge) ? edge->EdgeAttributes() : 0U);
}

bool ON_ComponentAttributes::EdgeIsEligible(
  unsigned int edge_attributes_filter,
  unsigned int edge_attributes
)
{
  if (0U == edge_attributes_filter)
    return true; // no restrictions

  if (0U == edge_attributes)
    return false; // edge has no properties - it's null or unset  

  if (0 != (edge_attributes_filter & ON_ComponentAttributes::Damaged))
  {
    if (0 == (edge_attributes & ON_ComponentAttributes::Damaged))
      return false; // edge_flags_filter specifies damaged edges and this edge is not damaged.
  }

  unsigned filter;

  // Test subsets of mutually exclusive properties
  const unsigned int masks[] =
  {
    // open/closed test
    // open = edge has distinct start/end vertices (they might be located at the same location)
    // closed = edge has identical start/end vertices.
    ON_ComponentAttributes::EdgeAttributes::Open
    | ON_ComponentAttributes::EdgeAttributes::Closed,

    // wire/boundary/interior/nonmanifold
    // wire = 0 faces, boundary = 1 face, interior = 2 faces, nonmanifold = 3 or more faces
    ON_ComponentAttributes::EdgeAttributes::Wire
    | ON_ComponentAttributes::EdgeAttributes::Boundary
    | ON_ComponentAttributes::EdgeAttributes::Interior
    | ON_ComponentAttributes::EdgeAttributes::Nonmanifold,

    // length test,
    // ZeroLength locations for start/end are equal and the curve connecting them has zero length.
    // NonzeroLength the curve connecting the start/end has nonzero length.
    ON_ComponentAttributes::EdgeAttributes::ZeroLength
    | ON_ComponentAttributes::EdgeAttributes::NonzeroLength,
  };

  for (size_t i = 0; i < sizeof(masks) / sizeof(masks[0]); ++i)
  {
    filter = masks[i] & edge_attributes_filter;
    // Each masks[i] is a set of mutually exclusive edge properties.
    //
    // Example:
    // masks[0] = ON_ComponentAttributes::EdgeAttributes::Open | ON_ComponentAttributes::EdgeAttributes::Closed.
    // if (0 == (masks[0] & edge_flags_filter)), neither is set, so don't check the filter.
    // if (masks[0] == (masks[0] & edge_flags_filter)), both are set, so don't check the filter.
    // Note that if and edge is damaged or has unset vertex information, 
    // then 0 = (edge &  masks[0]).
    if (0 == filter)
      continue; // nothing to check for this set of properties.

    if (0 == (filter & edge_attributes))
      return false; // edge does not have desired properties
  }

  if (0 != (ON_ComponentAttributes::EdgeAttributes::Interior & edge_attributes))
  {
    // tests that apply to interior edges

    // Mutually exclusive attributes for interior edges
    const unsigned int interior_edge_masks[] =
    {
      // smooth/crease test
      ON_ComponentAttributes::EdgeAttributes::InteriorSmooth
      | ON_ComponentAttributes::EdgeAttributes::InteriorCrease,

      // oriented/not oriented
      ON_ComponentAttributes::EdgeAttributes::InteriorOriented
      | ON_ComponentAttributes::EdgeAttributes::InteriorNotOriented,

      // seam/slit
      ON_ComponentAttributes::EdgeAttributes::InteriorTwoFaced
      | ON_ComponentAttributes::EdgeAttributes::InteriorSeam
      | ON_ComponentAttributes::EdgeAttributes::InteriorSlit,
    };

    for (size_t i = 0; i < sizeof(interior_edge_masks) / sizeof(interior_edge_masks[0]); ++i)
    {
      filter = interior_edge_masks[i] & edge_attributes_filter;
      if (0 == filter)
        continue; // nothing to check

      if (0 == (filter & edge_attributes))
        return false; // edge does not have desired properties
    }
  }

  return true; // edge passed filter tests  
}

bool ON_ComponentAttributes::IsSolid(
  unsigned int aggregate_edge_component_attributes
  )
{
  const unsigned int required_bits 
    = ON_ComponentAttributes::EdgeAttributes::InteriorOriented
    ;
  if ( required_bits != (required_bits & aggregate_edge_component_attributes) )
    return false;

  const unsigned int forbidden_bits
    = ON_ComponentAttributes::EdgeAttributes::Wire
    | ON_ComponentAttributes::EdgeAttributes::Boundary
    | ON_ComponentAttributes::EdgeAttributes::Nonmanifold
    | ON_ComponentAttributes::EdgeAttributes::InteriorNotOriented
    | ON_ComponentAttributes::Damaged
    ;
  if ( 0 != (forbidden_bits & aggregate_edge_component_attributes) )
    return false;

  return true;
}

bool ON_ComponentAttributes::HasBoundary(
  unsigned int aggregate_edge_component_attributes
  )
{
  const unsigned int required_bits
    = ON_ComponentAttributes::EdgeAttributes::Boundary
    ;
  if ( required_bits != (required_bits & aggregate_edge_component_attributes) )
    return false;

  return true;}


bool ON_ComponentAttributes::IsOriented(
  unsigned int aggregate_edge_component_attributes
  )
{
  const unsigned int required_bits
    = ON_ComponentAttributes::EdgeAttributes::InteriorOriented
    ;
  if ( required_bits != (required_bits & aggregate_edge_component_attributes) )
    return false;

  const unsigned int forbidden_bits
    = ON_ComponentAttributes::EdgeAttributes::InteriorNotOriented
    ;
  if ( 0 != (forbidden_bits & aggregate_edge_component_attributes) )
    return false;

  return true;
}

bool ON_ComponentAttributes::IsNotOriented(
  unsigned int aggregate_edge_component_attributes
  )
{
  const unsigned int required_bits
    = ON_ComponentAttributes::EdgeAttributes::InteriorNotOriented
    ;
  if ( required_bits != (required_bits & aggregate_edge_component_attributes) )
    return false;

  return true;
}


bool ON_ComponentAttributes::IsManifold(
  unsigned int aggregate_edge_component_attributes
  )
{
  const unsigned int require_at_least_one_bit
    = ON_ComponentAttributes::EdgeAttributes::Boundary
    | ON_ComponentAttributes::EdgeAttributes::Interior
    ;
  if ( 0 == (require_at_least_one_bit & aggregate_edge_component_attributes) )
    return false;

  const unsigned int forbidden_bits
    = ON_ComponentAttributes::EdgeAttributes::Wire
    | ON_ComponentAttributes::EdgeAttributes::Nonmanifold
    ;
  if ( 0 != (forbidden_bits & aggregate_edge_component_attributes) )
    return false;

  return true;
}

bool ON_ComponentAttributes::IsNotManifold(
  unsigned int aggregate_edge_component_attributes
  )
{
  const unsigned int require_at_least_one_bit
    = ON_ComponentAttributes::EdgeAttributes::Wire
    | ON_ComponentAttributes::EdgeAttributes::Nonmanifold
    ;
  if ( 0 == (require_at_least_one_bit & aggregate_edge_component_attributes) )
    return false;

  return true;
}

