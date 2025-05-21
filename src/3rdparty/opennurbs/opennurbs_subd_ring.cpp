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

#include "opennurbs_subd_data.h"

unsigned int ON_SubD::GetQuadSectorPointRing(
  bool bPermitNoSubdivisions,
  bool bObsoleteAndIgnoredParameter,
  const ON_SubDVertex* obsolete_and_ignored_parameter,
  const ON_SubDComponentPtr* component_ring,
  size_t component_ring_count,
  double* point_ring,
  size_t point_ring_stride
)
{
  unsigned int subdivision_count = 0;
  return ON_SubD::GetQuadSectorPointRing(
    bPermitNoSubdivisions,
    component_ring,
    component_ring_count,
    subdivision_count,
    point_ring,
    point_ring_stride
  );
}

unsigned int ON_SubD::GetQuadSectorPointRing(
  bool bPermitNoSubdivisions,
  const class ON_SubDComponentPtr* component_ring,
  size_t component_ring_count,
  unsigned int& subdivision_count,
  double* point_ring,
  size_t point_ring_stride
)
{
  // MINIMAL VALIDATION CHECKS TO PREVENT CRASHES
  // CALLER MUST INSURE INPUT IS CORRECT
  subdivision_count = 0;

  const ON_SubDVertex* vertex0 = (nullptr != component_ring) ? ON_SUBD_VERTEX_POINTER(component_ring[0].m_ptr) : nullptr;
  if (nullptr == vertex0)
    return ON_SUBD_RETURN_ERROR(0);

  const ON_SubDVertexTag center_vertex_tag = vertex0->m_vertex_tag;
  const bool bCreaseOrCornerSector = (ON_SubDVertexTag::Crease == center_vertex_tag || ON_SubDVertexTag::Corner == center_vertex_tag);
  const bool bDartOrCreaseOrCornerSector = bCreaseOrCornerSector || ON_SubDVertexTag::Dart == center_vertex_tag;
  if (false == bDartOrCreaseOrCornerSector && ON_SubDVertexTag::Smooth != center_vertex_tag)
    return ON_SUBD_RETURN_ERROR(0);

  const unsigned N = ON_SubD::ComponentRingEdgeCount(component_ring_count);
  const unsigned F = ON_SubD::ComponentRingFaceCount(component_ring_count);
  if (N < 2U)
    return ON_SUBD_RETURN_ERROR(0);
  if (F + (bCreaseOrCornerSector ? 1u : 0u) != N)
    return ON_SUBD_RETURN_ERROR(0);

  const unsigned point_ring_count = 1u + N + F;
  if ((size_t)point_ring_count != component_ring_count)
    return ON_SUBD_RETURN_ERROR(0);

  // If the final value of target_subdivision_count = 0, then no subdivision is needed.
  // If the final value of target_subdivision_count = 1, then exactly 1 subdivision is needed.
  // If the final value of target_subdivision_count = 2, then at least two subdivisions are needed.
  unsigned target_subdivision_count = bPermitNoSubdivisions ?0u : 1u;

  for (unsigned eptr_dex = 1u; eptr_dex < point_ring_count; eptr_dex += 2u)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(component_ring[eptr_dex].m_ptr);
    if (nullptr == e)
      return ON_SUBD_RETURN_ERROR(0);
    const unsigned end0 = e->VertexArrayIndex(vertex0);
    if (end0 > 1u)
      return ON_SUBD_RETURN_ERROR(0);

    const ON_SubDEdgeTag etag = e->m_edge_tag;
    if (ON_SubDEdgeTag::Crease == etag)
      continue;

    const ON_SubDEdgeSharpness s0 = e->Sharpness(false);
    const double x0 = s0.MaximumEndSharpness();
    if (x0 > 0.0)
    {
      if (target_subdivision_count < 1u)
      {
        // at least one subdivision is required to remove sharpness
        target_subdivision_count = 1u;
      }
      const double x1 = s0.Subdivided(end0).MaximumEndSharpness();
      if (x1 > 0.0)
      {
        // at least two subdivisions are required to remove sharpness.
        target_subdivision_count = 2u;
        break;
      }
    }

    if (target_subdivision_count >= 1u)
      continue;

    if (ON_SubDEdgeTag::SmoothX == etag)
    {
      // one subdivision is required to handle SmoothX edges
      target_subdivision_count = 1u;
    }
    else
    {
      const ON_SubDVertex* v1 = e->m_vertex[1u - end0];
      if (nullptr == v1 || v1 == vertex0)
        return ON_SUBD_RETURN_ERROR(0);
      if (v1->IsDartOrCreaseOrCorner() && 0.5 != e->m_sector_coefficient[1u - end0])
      {
        // one subdivision is required to handle extraordinary sector coefficient at v1.
        target_subdivision_count = 1u;
      }
    }
  }

  double vertex0_sharpness;
  if (
    ON_SubDVertexTag::Crease == center_vertex_tag
    && vertex0->m_edge_count == vertex0->m_face_count
    && F < (unsigned)(vertex0->m_face_count)
    )
  {
    // Dale Lear 14 Dec 2023 RH-76871
    // When a crease vertex has more than one sector the tagging rules imply
    // it must have exactly two crease edges and exactly two sectors separated by
    // those edges. Call the two sectors sector A and sector B.
    // Set a = maximum ens sharpness at vertex0 of sector A
    // and set b = maximum ens sharpness at vertex0 of sector B.
    // If (a != b) and there is an integer n so that max(a,b) >= n and min(a,b) <= n,
    // then we need to sudivide the sector with the smallest sharpness 
    // enough times to insure the vertex has no sharpness in either sector.
    // Since the code below only has access to the edges from the current sector,
    // we need the overall vertex sharpness here.
    // This situation cannot occur with smooth or dart vertices because they
    // always have a single sector. It doesn't matter with corner vertices
    // because their subdivision points and limit point are simple the
    // level 0 control net point.
    vertex0_sharpness = vertex0->VertexSharpness();
    if (vertex0_sharpness > 1.0)
    {
      if (target_subdivision_count < 2u)
        target_subdivision_count = 2u; // put a breakpoint here to see when this test matters (use files from RH-76871).
    }
    else if (vertex0_sharpness > 0.0)
    {
      if (target_subdivision_count < 1u)
        target_subdivision_count = 1u; // put a breakpoint here to see when this test matters (use files from RH-76871 with constant edge sharpness = 1).
    }
  }
  else
  {
    // Setting vertex0_sharpness = nan indicates
    // it is not set and the actual value doesn't matter
    // in the rest of this calculation.
    vertex0_sharpness = ON_DBL_QNAN;
  }

  if (target_subdivision_count > 1u)
  {
    // we need to subdivide at least twice to get the point ring

    ON_SubDVertexQuadSector vqs;
    if (false == vqs.InitializeFromSubdividedSectorComponents(vertex0_sharpness, component_ring, component_ring_count))
      return ON_SUBD_RETURN_ERROR(0);
    if (N != vqs.CenterVertexEdgeCount())
      return ON_SUBD_RETURN_ERROR(0);
    if (F != vqs.SectorFaceCount())
      return ON_SUBD_RETURN_ERROR(0);
    if (point_ring_count != vqs.SectorVertexCount())
      return ON_SUBD_RETURN_ERROR(0);
    unsigned int sharp_subdivision_count = 0;
    if (false == vqs.SubdivideUntilSharpnessIsZero(sharp_subdivision_count))
      return ON_SUBD_RETURN_ERROR(0);

    // harvest the ring points from vqs.
    for (unsigned i = 0; i < point_ring_count; ++i)
    {
      const ON_3dPoint P = vqs.m_v[i].ControlNetPoint();
      point_ring[0] = P.x;
      point_ring[1] = P.y;
      point_ring[2] = P.z;
      point_ring += point_ring_stride;
    }
    // subdivision_count = total number of subdivisions to get point_ring[]
    subdivision_count = sharp_subdivision_count + 1;
    return point_ring_count;
  }

  if (0u == target_subdivision_count)
  {
    for (unsigned fptr_dex = 2u; fptr_dex < point_ring_count; fptr_dex += 2u)
    {
      const ON_SubDFace* f = ON_SUBD_FACE_POINTER(component_ring[fptr_dex].m_ptr);
      if (nullptr == f)
        return ON_SUBD_RETURN_ERROR(0);
      if (4 == f->m_edge_count)
        continue;

      // a subdivision is required to handle non-quad faces
      target_subdivision_count = 1u;
      break;
    }
  }

  // get ring points with 0 or 1 subdivision
  double subP[3];
  const double* Q = nullptr;
  if (0 == target_subdivision_count)
    Q = vertex0->m_P;
  else
  {
    if (false == vertex0->GetSubdivisionPoint(subP))
      return ON_SUBD_RETURN_ERROR(0);
    Q = subP;
    subdivision_count = 1;
  }

  double* P = point_ring;
  P[0] = Q[0];
  P[1] = Q[1];
  P[2] = Q[2];
  P += point_ring_stride;

  for (unsigned eptr_dex = 1u; eptr_dex < point_ring_count; eptr_dex += 2u)
  {
    // Get edge point
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(component_ring[eptr_dex].m_ptr);
    if (nullptr == e)
      return ON_SUBD_RETURN_ERROR(0);

    if (0u == target_subdivision_count)
    {
      const ON_SubDVertex* vertexQ = e->OtherEndVertex(vertex0);
      if (nullptr == vertexQ)
        return ON_SUBD_RETURN_ERROR(0);
      Q = vertexQ->m_P;
    }
    else
    {
      if (false == e->GetSubdivisionPoint(subP))
        return ON_SUBD_RETURN_ERROR(0);
      // Q = subP set above when vertex0 was subdivided.
    }
    P[0] = Q[0];
    P[1] = Q[1];
    P[2] = Q[2];
    P += point_ring_stride;
      
    if (eptr_dex + 1u < point_ring_count)
    {
      const ON_SubDFace* f = ON_SUBD_FACE_POINTER(component_ring[eptr_dex+1u].m_ptr);
      if (nullptr == f)
        return ON_SUBD_RETURN_ERROR(0);
      if (0u == target_subdivision_count)
      {
        const ON_SubDVertex* vertexQ = f->QuadOppositeVertex(vertex0);
        if (nullptr == vertexQ)
          return ON_SUBD_RETURN_ERROR(0);
        Q = vertexQ->m_P;
      }
      else
      {
        if (false == f->GetSubdivisionPoint(subP))
          return ON_SUBD_RETURN_ERROR(0);
        // Q = subP set above when vertex0 was subdivided.
      }
      P[0] = Q[0];
      P[1] = Q[1];
      P[2] = Q[2];
      P += point_ring_stride;
    }
  }

  return point_ring_count;
}

unsigned int ON_SubD::ComponentRingEdgeCount(size_t component_ring_count)
{
  const unsigned int N 
    = (component_ring_count < 4)
    ? 0
    : (unsigned int)(component_ring_count/2);
  return N;
}

unsigned int ON_SubD::ComponentRingFaceCount(size_t component_ring_count)
{
  const unsigned int N = ComponentRingEdgeCount(component_ring_count);
  const unsigned int F
    = (N < 2)
    ? 0 
    : (unsigned int)(component_ring_count - N - 1);
  return F;
}

bool ON_SubD::ComponentRingIsValid(
  const ON_SubDComponentPtr* component_ring,
  size_t component_ring_count
  )
{
  if (nullptr == component_ring || component_ring_count < 4)
    return ON_SUBD_RETURN_ERROR(false);
  
  const unsigned int N = ON_SubD::ComponentRingEdgeCount(component_ring_count);
  const unsigned int F = ON_SubD::ComponentRingFaceCount(component_ring_count);

  const ON_SubDVertex* vertex = component_ring[0].Vertex();
  if ( nullptr == vertex )
    return ON_SUBD_RETURN_ERROR(false);
  if ( vertex->m_edge_count < N || nullptr == vertex->m_edges)
    return ON_SUBD_RETURN_ERROR(false);
  if ( vertex->m_face_count < F || nullptr == vertex->m_faces)
    return ON_SUBD_RETURN_ERROR(false);

  const ON_SubDEdgeTag edge0_tag 
    = (F+1 == N || (F == N && ON_SubDVertexTag::Dart == vertex->m_vertex_tag))
    ? ON_SubDEdgeTag::Crease
    : ON_SubDEdgeTag::Smooth;
  const ON_SubDEdgeTag edge1_tag 
    = (F+1 == N)
    ? ON_SubDEdgeTag::Crease
    : ON_SubDEdgeTag::Smooth;

  unsigned int component_ring_index = 1;
  for (unsigned int i = 0; i < N; i++, component_ring_index++)
  {
    const ON_SubDEdge* edge = component_ring[component_ring_index].Edge();
    if ( nullptr == edge)
      return ON_SUBD_RETURN_ERROR(false);
    if (vertex != edge->m_vertex[component_ring[component_ring_index].ComponentDirection()])
      return ON_SUBD_RETURN_ERROR(false);

    if (0 == i)
    {
      if (edge0_tag != edge->m_edge_tag)
      {
        if (  ON_SubDEdgeTag::Smooth != edge0_tag || ON_SubDEdgeTag::SmoothX != edge->m_edge_tag )
          return ON_SUBD_RETURN_ERROR(false);
      }
    }
    else if (i+1 == N)
    {
      if (edge1_tag != edge->m_edge_tag)
      {
        if (  ON_SubDEdgeTag::Smooth != edge1_tag || ON_SubDEdgeTag::SmoothX != edge->m_edge_tag )
          return ON_SUBD_RETURN_ERROR(false);
      }
      if ( ON_SubDEdgeTag::Crease == edge1_tag)
        continue;
    }
    else
    {
      if (2 != edge->m_face_count || false == edge->IsSmooth())
        return ON_SUBD_RETURN_ERROR(false);
    }

    component_ring_index++;
    if ( component_ring_index >= component_ring_count)
      return ON_SUBD_RETURN_ERROR(false);

    const ON_SubDFace* face = component_ring[component_ring_index].Face();
    if ( nullptr == face)
      return ON_SUBD_RETURN_ERROR(false);
  }

  if (component_ring_index == component_ring_count)
    return true;

  return ON_SUBD_RETURN_ERROR(false);
}

unsigned int ON_SubD::GetSectorPointRing(
  bool bSubdivideIfNeeded,
  size_t component_ring_count,
  const ON_SubDComponentPtr* component_ring,
  ON_SimpleArray<ON_3dPoint>& point_ring
  )
{
  point_ring.SetCount(0);
  if ( component_ring_count <= 0 || nullptr == component_ring )
    return ON_SUBD_RETURN_ERROR(0);
  const ON_SubDVertex* center_vertex = component_ring[0].Vertex();
  if ( nullptr == center_vertex )
    return ON_SUBD_RETURN_ERROR(0);
  const unsigned int point_ring_capacity = (unsigned int)component_ring_count;
  ON_3dPoint* point_ring_array = point_ring.Reserve(point_ring_capacity);
  if ( nullptr == point_ring_array)
    return ON_SUBD_RETURN_ERROR(0);
  unsigned int point_ring_count = GetSectorPointRing( bSubdivideIfNeeded, component_ring, component_ring_count, &point_ring_array[0].x, point_ring_capacity, 3);
  if (point_ring_count > 0)
  {
    point_ring.SetCount(point_ring_count);
    return point_ring_count;
  }
  return ON_SUBD_RETURN_ERROR(0);
}


unsigned int ON_SubD::GetSectorSubdivsionPointRing(
  const ON_SubDComponentPtr* component_ring,
  size_t component_ring_count,
  double* subd_point_ring,
  size_t subd_point_ring_capacity,
  size_t subd_point_ring_stride
  )
{
  if (false == ComponentRingIsValid(component_ring,component_ring_count))
    return ON_SUBD_RETURN_ERROR(0);


  const unsigned int N = ON_SubD::ComponentRingEdgeCount(component_ring_count);
  const unsigned int F = ON_SubD::ComponentRingFaceCount(component_ring_count);
  const unsigned int point_ring_count = N + F;
  if ( point_ring_count > subd_point_ring_capacity || nullptr == subd_point_ring)
    return ON_SUBD_RETURN_ERROR(0);

  const bool bObsoleteAndIgnoredParameter = false;
  unsigned int rc = GetQuadSectorPointRing(
    false, 
    bObsoleteAndIgnoredParameter, 
    nullptr,
    component_ring,
    component_ring_count, 
    subd_point_ring, 
    subd_point_ring_stride);

  if (0 == rc)
    return ON_SUBD_RETURN_ERROR(0);

  return rc;

}

unsigned int ON_SubD::GetSectorSubdivisionPointRing(
  const ON_SubDComponentPtr* component_ring,
  size_t component_ring_count,
  ON_SimpleArray<ON_3dPoint>& subd_point_ring
  )
{
  subd_point_ring.SetCount(0);
  if ( component_ring_count <= 0 || nullptr == component_ring )
    return ON_SUBD_RETURN_ERROR(0);
  const ON_SubDVertex* center_vertex = component_ring[0].Vertex();
  if ( nullptr == center_vertex )
    return ON_SUBD_RETURN_ERROR(0);
  const unsigned int subd_point_ring_capacity = (unsigned int)component_ring_count;
  ON_3dPoint* subd_point_ring_array = subd_point_ring.Reserve(subd_point_ring_capacity);
  if ( nullptr == subd_point_ring_array)
    return ON_SUBD_RETURN_ERROR(0);
  unsigned int subd_point_ring_count = GetSectorSubdivsionPointRing(component_ring, component_ring_count, &subd_point_ring_array[0].x, subd_point_ring_capacity, 3);
  if (subd_point_ring_count > 0)
  {
    subd_point_ring.SetCount(subd_point_ring_count);
    return subd_point_ring_count;
  }
  return ON_SUBD_RETURN_ERROR(0);
}

unsigned int ON_SubD::GetSectorPointRing(
  bool bSubdivideIfNeeded,
  const ON_SubDComponentPtr* component_ring,
  size_t component_ring_count,
  double* point_ring,
  size_t point_ring_capacity,
  size_t point_ring_stride
  )
{
  if (false == ComponentRingIsValid(component_ring,component_ring_count))
    return ON_SUBD_RETURN_ERROR(0);

  const unsigned int N = ON_SubD::ComponentRingEdgeCount(component_ring_count);
  const unsigned int F = ON_SubD::ComponentRingFaceCount(component_ring_count);
  const unsigned int point_ring_count = N + F;
  if ( point_ring_count > point_ring_capacity || nullptr == point_ring)
    return ON_SUBD_RETURN_ERROR(0);

  // Except for internal testing functions, bSubdivideIfNeeded is always true.
  const bool bObsoleteAndIgnoredParameter = false;
  unsigned int rc = GetQuadSectorPointRing(
    bSubdivideIfNeeded ? false : true, 
    bObsoleteAndIgnoredParameter,
    nullptr,
    component_ring,
    component_ring_count, 
    point_ring,point_ring_stride
  );

  if (0 == rc)
    return ON_SUBD_RETURN_ERROR(0);

  return rc;
}


unsigned int ON_SubD::GetSectorPointRing(
  bool bSubdivideIfNeeded,
  const class ON_SubDSectorIterator& sit,
  double* point_ring,
  size_t point_ring_capacity,
  size_t point_ring_stride
  )
{
  const ON_SubDVertex* center_vertex = sit.CenterVertex();
  if ( nullptr == center_vertex )
    return ON_SUBD_RETURN_ERROR(0);
  const unsigned int center_vertex_element_count = center_vertex->m_edge_count + center_vertex->m_face_count + 1;

  ON_SubDComponentPtr stack_component_ring[41];
  unsigned int component_ring_capacity = sizeof(stack_component_ring) / sizeof(stack_component_ring[0]);
  ON_SubDComponentPtr* component_ring = stack_component_ring;
  if (component_ring_capacity < point_ring_capacity && component_ring_capacity < center_vertex_element_count)
  {
    component_ring_capacity = (unsigned int)((center_vertex_element_count < point_ring_capacity) ? center_vertex_element_count : point_ring_capacity);
    component_ring = new(std::nothrow) ON_SubDComponentPtr[component_ring_capacity];
    if ( nullptr == component_ring)
      return ON_SUBD_RETURN_ERROR(0);
  }

  unsigned int point_ring_count = 0;
  unsigned int component_ring_count = ON_SubD::GetSectorComponentRing(sit, component_ring,component_ring_capacity);
  if (component_ring_count > 0)
  {
    const bool bObsoleteAndIgnoredParameter = false;
    point_ring_count = ON_SubD::GetQuadSectorPointRing(
      bSubdivideIfNeeded ? false : true, 
      bObsoleteAndIgnoredParameter, 
      nullptr, 
      component_ring, 
      component_ring_count, 
      point_ring, point_ring_stride
    );
  }
  
  if ( component_ring != stack_component_ring)
    delete[] component_ring;

  return point_ring_count;
}

unsigned int ON_SubD::GetSectorPointRing(
  bool bSubdivideIfNeeded,
  const class ON_SubDSectorIterator& sit,
  ON_SimpleArray<ON_3dPoint>& point_ring
  )
{
  point_ring.SetCount(0);
  const ON_SubDVertex* center_vertex = sit.CenterVertex();
  if ( nullptr == center_vertex )
    return ON_SUBD_RETURN_ERROR(0);
  const unsigned int point_ring_capacity = (center_vertex->m_edge_count + center_vertex->m_face_count);
  ON_3dPoint* point_ring_array = point_ring.Reserve(point_ring_capacity);
  if ( nullptr == point_ring_array)
    return ON_SUBD_RETURN_ERROR(0);
  unsigned int point_ring_count = GetSectorPointRing( bSubdivideIfNeeded, sit, &point_ring_array[0].x, point_ring_capacity, 3);
  if (point_ring_count > 0)
  {
    point_ring.SetCount(point_ring_count);
    return point_ring_count;
  }
  return ON_SUBD_RETURN_ERROR(0);
}


unsigned int ON_SubD::GetSectorPointRing(
  const class ON_SubDSectorIterator& sit,
  unsigned& subdivision_count,
  double* point_ring,
  size_t point_ring_capacity,
  size_t point_ring_stride
)
{
  subdivision_count = 0;
  const ON_SubDVertex* center_vertex = sit.CenterVertex();
  if (nullptr == center_vertex)
    return ON_SUBD_RETURN_ERROR(0);
  const unsigned int center_vertex_element_count = center_vertex->m_edge_count + center_vertex->m_face_count + 1;

  ON_SubDComponentPtr stack_component_ring[41];
  unsigned int component_ring_capacity = sizeof(stack_component_ring) / sizeof(stack_component_ring[0]);
  ON_SubDComponentPtr* component_ring = stack_component_ring;
  if (component_ring_capacity < point_ring_capacity && component_ring_capacity < center_vertex_element_count)
  {
    component_ring_capacity = (unsigned int)((center_vertex_element_count < point_ring_capacity) ? center_vertex_element_count : point_ring_capacity);
    component_ring = new(std::nothrow) ON_SubDComponentPtr[component_ring_capacity];
    if (nullptr == component_ring)
      return ON_SUBD_RETURN_ERROR(0);
  }

  unsigned int point_ring_count = 0;
  unsigned int component_ring_count = ON_SubD::GetSectorComponentRing(sit, component_ring, component_ring_capacity);
  if (component_ring_count > 0)
  {
    point_ring_count = ON_SubD::GetQuadSectorPointRing(
      false, // false means subdivisions are permitted
      component_ring,
      component_ring_count,
      subdivision_count,
      point_ring,
      point_ring_stride
    );
  }

  if (component_ring != stack_component_ring)
    delete[] component_ring;

  return point_ring_count;
}


unsigned int ON_SubD::GetSectorPointRing(
  const class ON_SubDSectorIterator& sit,
  unsigned& subdivision_count,
  ON_SimpleArray<ON_3dPoint>& point_ring
)
{
  subdivision_count = 0;
  point_ring.SetCount(0);
  const ON_SubDVertex* center_vertex = sit.CenterVertex();
  if (nullptr == center_vertex)
    return ON_SUBD_RETURN_ERROR(0);
  const unsigned int point_ring_capacity = (center_vertex->m_edge_count + center_vertex->m_face_count);
  ON_3dPoint* point_ring_array = point_ring.Reserve(point_ring_capacity);
  if (nullptr == point_ring_array)
    return ON_SUBD_RETURN_ERROR(0);
  unsigned int point_ring_count = GetSectorPointRing(sit, subdivision_count , &point_ring_array[0].x, point_ring_capacity, 3);
  if (point_ring_count > 0)
  {
    point_ring.SetCount(point_ring_count);
    return point_ring_count;
  }
  return ON_SUBD_RETURN_ERROR(0);}

const ON_SubDVertex* ON_SubD::SubdivideSector(
  const ON_SubDVertex* center_vertex,
  const ON_SubDComponentPtr* component_ring,
  size_t component_ring_count,
  ON_SubD_FixedSizeHeap& fsh
  )
{
  const unsigned int N = (nullptr != center_vertex) ? center_vertex->m_edge_count : ON_SubD::ComponentRingEdgeCount(component_ring_count);
  const unsigned int F = (nullptr != center_vertex) ? center_vertex->m_face_count : ON_SubD::ComponentRingFaceCount(component_ring_count);
  if ( N < 2 )
    return ON_SUBD_RETURN_ERROR(nullptr);
  if ( F != N && F+1 != N )
    return ON_SUBD_RETURN_ERROR(nullptr);

  size_t element_stride;
  const ON_SubDEdgePtr* edges;
  const ON_SubDFacePtr* faces;

  if (nullptr == center_vertex)
  {
    if (nullptr == component_ring || component_ring_count < 4)
      return ON_SUBD_RETURN_ERROR(nullptr);
    edges = (const ON_SubDEdgePtr*)(component_ring + 1);
    faces = (const ON_SubDFacePtr*)(component_ring + 2);
    element_stride = 2;
    center_vertex = component_ring[0].Vertex();
    if ( nullptr == center_vertex)
      return ON_SUBD_RETURN_ERROR(nullptr);
  }
  else
  {
    edges = center_vertex->m_edges;
    faces = (const ON_SubDFacePtr*)(center_vertex->m_faces);
    element_stride = 1;
  }

  // smooth and dart sectors have F = N
  // crease and corner have F = N-1
  if (F != (center_vertex->IsCreaseOrCorner() ? (N-1) : N) )
  {
    return ON_SUBD_RETURN_ERROR(nullptr);
  }
  
  const ON_SubDEdgeTag edge0_tag = (F+1 == N) ? ON_SubDEdgeTag::Crease : ON_SubDEdgeTag::Smooth;

  //const unsigned int face_edge_count = 4;
  const unsigned int K = 3;
  
  const ON_SubDEdge* edge0 = edges->Edge();
  if ( nullptr == edge0)
    return ON_SUBD_RETURN_ERROR(nullptr);
  edges += element_stride;

  if (ON_SubDEdgeTag::Smooth == edge0_tag)
  {
    if (false == edge0->IsSmooth() )
      return ON_SUBD_RETURN_ERROR(nullptr);
  }
  else 
  {
    if (edge0_tag != edge0->m_edge_tag)
      return ON_SUBD_RETURN_ERROR(nullptr);
  }
  
  const ON_SubDFace* face0 = faces->Face();
  if ( nullptr == face0)
    return ON_SUBD_RETURN_ERROR(nullptr);
  edges += element_stride;

  if ( false == fsh.ReserveSubDWorkspace(N) )
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON_SubDVertex* v1[4] = {};
  ON_SubDEdgePtr e1[4] = {};
  ON_SubDEdgePtr f1epts[4] = {};

  const ON_SubDVertex* vertex0 = center_vertex;

  v1[0] = fsh.AllocateVertex(vertex0,N);
  if ( nullptr == v1[0])
    return ON_SUBD_RETURN_ERROR(nullptr);
  //v1[0]->m_vertex_edge_order = ON_SubD::VertexEdgeOrder::radial;

  ON_SubDVertex* vertex1 = fsh.AllocateVertex(edge0);
  if ( nullptr == vertex1)
    return ON_SUBD_RETURN_ERROR(nullptr);

  // at_crease weight is used when the corresponding vertex is a crease.
  // Otherwise, fsh.AllocateEdge() ignores at_crease_weight.
  ON_SubDEdgeTag edge1_tag = (ON_SubDEdgeTag::SmoothX == edge0_tag) ? ON_SubDEdgeTag::Smooth : edge0_tag;
  const double at_crease_weight 
    = ON_SubDEdgeTag::Crease == edge1_tag
    ? ON_SubDSectorType::CreaseSectorCoefficient(5-K)
    : ON_SubDSectorType::IgnoredSectorCoefficient;
  ON_SubDEdgePtr edge1 = fsh.AllocateEdge(v1[0], ON_SubDSectorType::CopyEdgeSectorCoefficient(edge0,vertex0,ON_UNSET_VALUE), vertex1, ON_SubDSectorType::IgnoredSectorCoefficient );
  if (edge1.IsNull())
    return ON_SUBD_RETURN_ERROR(nullptr);
  edge1.Edge()->m_edge_tag = edge1_tag;
  
  v1[1] = vertex1;
  e1[0] = edge1;
  f1epts[0] = e1[0];
  edge1_tag = ON_SubDEdgeTag::Smooth;
    
  for (unsigned int i = 1; i < N; i++, edges += element_stride, faces += element_stride)
  {
    edge0 = edges->Edge();
    if ( nullptr == edge0)
      return ON_SUBD_RETURN_ERROR(nullptr);
    if (vertex0 != edge0->m_vertex[0] && vertex0 != edge0->m_vertex[1])
      return ON_SUBD_RETURN_ERROR(nullptr);

    if (i + 1 == N)
    {
      edge1_tag = edge0_tag;
      if ( edge1_tag != edge0->m_edge_tag)
        return ON_SUBD_RETURN_ERROR(nullptr);
      if (ON_SubDEdgeTag::Smooth == edge1_tag)
      {
        v1[K] = vertex1;
        e1[K] = edge1;
      }
    }

    if (nullptr == v1[K])
    {
      v1[K] = fsh.AllocateVertex(edge0);
      if (nullptr == v1[K])
        return ON_SUBD_RETURN_ERROR(nullptr);
      e1[K] = fsh.AllocateEdge(v1[0], ON_SubDSectorType::CopyEdgeSectorCoefficient(edge0, vertex0, ON_UNSET_VALUE), v1[K], ON_SubDSectorType::IgnoredSectorCoefficient);
      if (e1[K].IsNull())
        return ON_SUBD_RETURN_ERROR(nullptr);
      e1[K].Edge()->m_edge_tag = edge1_tag;
    }

    f1epts[K] = e1[K].Reversed();

    // quads
    v1[2] = fsh.AllocateSectorFaceVertex(face0 );
    e1[1] = fsh.AllocateEdge(v1[1], at_crease_weight, v1[2], ON_SubDSectorType::IgnoredSectorCoefficient);
    e1[2] = fsh.AllocateEdge(v1[2], ON_SubDSectorType::IgnoredSectorCoefficient, v1[3], at_crease_weight);
    f1epts[1] = e1[1];
    f1epts[2] = e1[2];
    if (nullptr == fsh.AllocateQuad(face0->m_level_zero_face_id, face0->m_id, f1epts) )
      return ON_SUBD_RETURN_ERROR(nullptr);
      
    if (i + 1 == N)
    {
      if (i + 1 == N && edge0_tag == edge1_tag)
        return v1[0];

      return ON_SUBD_RETURN_ERROR(nullptr);
    }

    face0 = faces->Face();
    if ( nullptr == face0)
      return ON_SUBD_RETURN_ERROR(nullptr);

    v1[1] = v1[K];
    e1[0] = e1[K];
    f1epts[0] = f1epts[K].Reversed();
    v1[K] = nullptr;
    e1[K] = ON_SubDEdgePtr::Null;
  }

  return ON_SUBD_RETURN_ERROR(nullptr);
}

unsigned int ON_SubD::GetSectorComponentRing(
  const class ON_SubDSectorIterator& sit,
  ON_SubDComponentPtr* component_ring,
  size_t component_ring_capacity
  )
{
  if ( component_ring_capacity < 4 || nullptr == component_ring)
    return ON_SUBD_RETURN_ERROR(0);

  const ON_SubDVertex* vertex = sit.CenterVertex();
  if ( nullptr == vertex || vertex->m_edge_count < 2 || vertex->m_face_count < 1)
    return ON_SUBD_RETURN_ERROR(0);

  const ON_SubDVertexTag center_vertex_tag = vertex->m_vertex_tag;

  ON_SubDSectorIterator localsit(sit);
  const bool bCreases = (nullptr != localsit.IncrementToCrease(-1));
  
  ON_SubDEdgePtr edgeptr = localsit.CurrentEdgePtr(0);
  ON_SubDFacePtr faceptr = localsit.CurrentFacePtr();

  const ON_SubDEdge* edge0 = edgeptr.Edge();
  if ( nullptr == edge0 )
    return ON_SUBD_RETURN_ERROR(0);
  const ON_SubDFace* face0 = faceptr.Face();
  if ( nullptr == face0 )
    return ON_SUBD_RETURN_ERROR(0);
  const ON_SubDVertex* ring_vertex0 = localsit.CurrentEdgeRingVertex(0);
  if ( nullptr == ring_vertex0 || vertex == ring_vertex0)
    return ON_SUBD_RETURN_ERROR(0);

  if (bCreases && ON_SubDEdgeTag::Crease != edge0->m_edge_tag)
    return ON_SUBD_RETURN_ERROR(0);

  unsigned int component_ring_count = 0;
  component_ring[component_ring_count++] = ON_SubDComponentPtr::Create(vertex);
  component_ring[component_ring_count++] = ON_SubDComponentPtr::Create(edgeptr);
  component_ring[component_ring_count++] = ON_SubDComponentPtr::Create(faceptr);
  const unsigned int N = vertex->m_edge_count; // for () used to prevent infinite recursion when vertex is not valid
  for (unsigned int i = 0; i < N; i++)
  {
    const ON_SubDFace* face = localsit.NextFace(ON_SubDSectorIterator::StopAt::AnyCrease);

    edgeptr = localsit.CurrentEdgePtr(0);
    const ON_SubDEdge* edge = edgeptr.Edge();
    if ( nullptr == edge)
      return ON_SUBD_RETURN_ERROR(0);
    const ON_SubDVertex* ring_vertex = localsit.CurrentEdgeRingVertex(0);
    if ( nullptr == ring_vertex || vertex == ring_vertex)
      return ON_SUBD_RETURN_ERROR(0);

    if (face == face0 || edge == edge0 || ring_vertex == ring_vertex0)
    {
      // back to start?
      if (edge == edge0 && ring_vertex == ring_vertex0)
      {
        if (ON_SubDVertexTag::Smooth == center_vertex_tag)
        {
          if (face == face0 && ON_SubDEdgeTag::Smooth == edge0->m_edge_tag)
            return component_ring_count; // back to start smooth case.
        }
        if (ON_SubDVertexTag::Dart == center_vertex_tag)
        {
          if (nullptr == face && ON_SubDEdgeTag::Crease == edge0->m_edge_tag)
            return component_ring_count; // back to start dart case.
        }
        if (ON_SubDVertexTag::Corner == center_vertex_tag)
        {
          // occurs in nonmanifold cases like the one in RH-49843
          if (nullptr == face && ON_SubDEdgeTag::Crease == edge0->m_edge_tag)
            return component_ring_count; // back to start corner case.
        }
      }

      return ON_SUBD_RETURN_ERROR(false); // damaged topology information
    }

    if ( component_ring_count >= component_ring_capacity)
      return ON_SUBD_RETURN_ERROR(false);

    component_ring[component_ring_count++] = ON_SubDComponentPtr::Create(edgeptr);
    
    if (nullptr == face)
    {
      if (bCreases && ON_SubDEdgeTag::Crease == edge->m_edge_tag)
        return component_ring_count;
      return ON_SUBD_RETURN_ERROR(0);
    }

    if ( false == edge->IsSmooth() || 2 != edge->m_face_count )
      return ON_SUBD_RETURN_ERROR(false);

    if ( component_ring_count >= component_ring_capacity)
      return ON_SUBD_RETURN_ERROR(false);

    faceptr = localsit.CurrentFacePtr();
    component_ring[component_ring_count++] = ON_SubDComponentPtr::Create(faceptr);
  }

  return ON_SUBD_RETURN_ERROR(false); // damaged topology information
}


unsigned int ON_SubD::GetSectorComponentRing(
  const class ON_SubDSectorIterator& sit,
  ON_SimpleArray<ON_SubDComponentPtr>& elements
  )
{
  elements.SetCount(0);
  const ON_SubDVertex* vertex = sit.CenterVertex();
  if ( nullptr == vertex || vertex->m_edge_count < 2 || vertex->m_face_count < 1)
    return ON_SUBD_RETURN_ERROR(0);

  const unsigned int component_ring_capacity = 1 + vertex->m_edge_count + vertex->m_face_count;
  unsigned int component_ring_count = ON_SubD::GetSectorComponentRing(sit, elements.Reserve(component_ring_capacity), component_ring_capacity);
  if (component_ring_count >= 4 && component_ring_count <= component_ring_capacity)
    elements.SetCount(component_ring_count);

  return elements.UnsignedCount();
}
