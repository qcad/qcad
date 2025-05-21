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

const size_t ON_SubDHeap::g_sizeof_fragment[ON_SubDDisplayParameters::MaximumDensity + 1] =
{
  // All densities >= 0 and <= ON_SubDDisplayParameters::MaximumDensity
  // must be in the following list. The sizes must include room for
  // textures, colors, and curvatures, even though those properties are
  // often not set.
  ON_SubDMeshFragment::SizeofFragment(0),
  ON_SubDMeshFragment::SizeofFragment(1),
  ON_SubDMeshFragment::SizeofFragment(2),
  ON_SubDMeshFragment::SizeofFragment(3),
  ON_SubDMeshFragment::SizeofFragment(4),
  ON_SubDMeshFragment::SizeofFragment(5),
  ON_SubDMeshFragment::SizeofFragment(ON_SubDDisplayParameters::MaximumDensity)
};

static void* ON_SubD__Allocate(size_t sz)
{
  if (0 == sz)
    return nullptr;

  // double array allocation is used to insure the memory
  // returned by new is properly aligned for any type.
  double* a;
  size_t sz1 = sz % sizeof(a[0]);
  if (sz1 > 0)
    sz += (sizeof(a[0]) - sz1);
  a = new(std::nothrow) double[sz];

  if (nullptr == a)
    return ON_SUBD_RETURN_ERROR(nullptr);

  return a;
}

static void ON_SubD__Free(void* p)
{
  if (nullptr != p)
  {
    double* a = (double*)p;
    delete[] a;
  }
}



//////////////////////////////////////////////////////////////////////////
//
// ON_SubD_FixedSizeHeap
//

unsigned int ON_SubD_FixedSizeHeap::m__sn_factory = 0;

ON_SubD_FixedSizeHeap::~ON_SubD_FixedSizeHeap()
{
  Destroy();
}


void ON_SubD_FixedSizeHeap::Destroy()
{
  Reset();
  m_v_capacity = 0;
  m_e_capacity = 0;
  m_f_capacity = 0;
  m_p_capacity = 0;
  m_h_capacity = 0;
  m_h_count = 0;
  void* p[6] = { m_v, m_e, m_f, m_p, m_hash_table, m_hash_elements };
  m_v = nullptr;
  m_e = nullptr;
  m_f = nullptr;
  m_p = nullptr;
  m_hash_table = nullptr;
  m_hash_elements = nullptr;
  ON_SubD__Free(p[0]);
  ON_SubD__Free(p[1]);
  ON_SubD__Free(p[2]);
  ON_SubD__Free(p[3]);
  ON_SubD__Free(p[4]);
  ON_SubD__Free(p[5]);
}

void ON_SubD_FixedSizeHeap::Reset()
{
  if (m_h_capacity > 0)
    memset(m_hash_table, 0, m_h_capacity * sizeof(*m_hash_table));
  m_v_index = 0;
  m_e_index = 0;
  m_f_index = 0;
  m_p_index = 0;
  m_h_count = 0;
}

bool ON_SubD_FixedSizeHeap::InUse() const
{
  return (m_v_index > 0 || m_e_index > 0 || m_f_index>0 || m_p_index>0);
}

class ON_SubD_FixedSizeHeap_ComponentPairHashElement
{
public:
  //static const ON_SubD_FixedSizeHeap_ComponentPairHashElement Empty;
  ON_SubDComponentPtrPair m_pair;
  ON_SubD_FixedSizeHeap_ComponentPairHashElement* m_next;

};

bool ON_SubD_FixedSizeHeap::Internal_ReserveSubDWorkspace_HashTable()
{
  const unsigned int hash_capacity = (m_v_capacity > 0) ? (m_v_capacity / 4 + 1) : 0;
  m_h_count = 0;
  if (hash_capacity > m_h_capacity)
  {
    m_h_capacity = 0;
    if (nullptr != m_hash_elements)
    {
      ON_SubD__Free(m_hash_elements);
      m_hash_elements = nullptr;
    }
    if (nullptr != m_hash_table)
    {
      ON_SubD__Free(m_hash_table);
      m_hash_table = nullptr;
    }
    m_hash_table = (ON_SubD_FixedSizeHeap_ComponentPairHashElement**)ON_SubD__Allocate(hash_capacity * sizeof(*m_hash_table));
    if (nullptr == m_hash_table)
      return false;
    m_hash_elements = (ON_SubD_FixedSizeHeap_ComponentPairHashElement*)ON_SubD__Allocate(m_v_capacity * sizeof(*m_hash_elements));
    if (nullptr == m_hash_elements)
    {
      ON_SubD__Free(m_hash_table);
      m_hash_table = nullptr;
      return false;
    }
    m_h_capacity = hash_capacity;
  }
  if ( m_h_capacity > 0 && nullptr != m_hash_table)
    memset(m_hash_table, 0, m_h_capacity * sizeof(*m_hash_table));
  return true;
}

bool ON_SubD_FixedSizeHeap::Internal_ReserveSubDWorkspace(
  size_t vertex_capacity,
  size_t face_capacity,
  size_t array_capacity,
  bool bEnableHash
  )
{
  if ( vertex_capacity <= 0 || face_capacity <= 0 || array_capacity <= 0)
  {
    Destroy();
    return ON_SUBD_RETURN_ERROR(false);
  }
  const size_t edge_capacity = vertex_capacity + face_capacity - 1; // Euler formula
  if (m_v_capacity >= vertex_capacity
    && m_e_capacity >= edge_capacity
    && m_f_capacity >= face_capacity
    && m_p_capacity >= array_capacity
    )
  {
    Reset();
    if (bEnableHash)
      Internal_ReserveSubDWorkspace_HashTable();
    else
      m_h_count = ON_SubD_FixedSizeHeap::DisabledHashCount;
    return true;
  }

  Destroy();

  size_t max_capacity = 0xFFFFFFU;
  if (vertex_capacity > max_capacity || edge_capacity > max_capacity || face_capacity > max_capacity || array_capacity > max_capacity)
    return ON_SUBD_RETURN_ERROR(false);

  for (;;)
  {
    m_v = (ON_SubDVertex*)ON_SubD__Allocate(vertex_capacity*sizeof(m_v[0]));
    if (nullptr == m_v && vertex_capacity > 0)
      break;
    m_e = (ON_SubDEdge*)ON_SubD__Allocate(edge_capacity*sizeof(m_e[0]));
    if (nullptr == m_e && edge_capacity > 0)
      break;
    m_f = (ON_SubDFace*)ON_SubD__Allocate(face_capacity*sizeof(m_f[0]));
    if (nullptr == m_f && face_capacity > 0)
      break;
    m_p = (ON__UINT_PTR*)ON_SubD__Allocate(array_capacity*sizeof(m_p[0]));
    if (nullptr == m_p && array_capacity > 0)
      break;

    m_v_capacity = (unsigned int)vertex_capacity;
    m_e_capacity = (unsigned int)edge_capacity;
    m_f_capacity = (unsigned int)face_capacity;
    m_p_capacity = (unsigned int)array_capacity;

    if (bEnableHash)
      Internal_ReserveSubDWorkspace_HashTable();
    else
      m_h_count = ON_SubD_FixedSizeHeap::DisabledHashCount;
    return true;
  }

  Destroy();

  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubD_FixedSizeHeap::ReserveSubDWorkspace(
  unsigned int sector_edge_count
  )
{
  if (0 == sector_edge_count)
  {
    Destroy();
    return true;
  }

  const unsigned int k = (sector_edge_count <= 4) ? 0 : (sector_edge_count - 4);
  const unsigned int v_capacity = 16 + 2 * k;
  const unsigned int f_capacity = 9 + k;
  const unsigned int p_capacity = 8*v_capacity + 2 * k;

  return Internal_ReserveSubDWorkspace(v_capacity, f_capacity, p_capacity, false);
}

static unsigned int Internal_AtLeast4(unsigned int n)
{
  return (n > 4U) ? n : 4U;
}

bool ON_SubD_FixedSizeHeap::ReserveSubDWorkspace(
  const ON_SubDFace* center_face0
  )
{
  unsigned int v_capacity =  0;
  unsigned int f_capacity =  0;
  unsigned int a_capacity =  0;

  for (;;)
  {
    if (nullptr == center_face0)
      break;

    const unsigned int N = center_face0->m_edge_count;
    if (N <= 2)
      break;

    unsigned int S = 0;  // Set S = sum of the number of edges attached to each vertex of center_face0.
    unsigned int T = Internal_AtLeast4(N);  // Set T = capacity required for vertex edge arrays on face subdivision vertices
    unsigned int X = 0;
    bool bValenceTwoVertices = false; // bValenceTwoVertices = true if center_face0 has a valence 2 vertex and we need the hash table
    {
      const ON_SubDEdgePtr* edges = center_face0->m_edge4;
      ON__UINT_PTR edge_ptr;
      const ON_SubDEdge* edge;
      const ON_SubDVertex* vertex;
      const ON_SubDFace* vertex_face;
      unsigned int fei;
      edge = center_face0->Edge(N - 1);
      if (nullptr == edge)
        break;
      bool bEdgeIsHardCrease[2] = { false, edge->IsHardCrease() };
      for (fei = 0; fei < N; fei++, edges++)
      {
        if (4 == fei)
        {
          edges = center_face0->m_edgex;
          if (nullptr == edges)
            break;
        }
        edge_ptr = edges->m_ptr;
        edge = ON_SUBD_EDGE_POINTER(edge_ptr);
        if (nullptr == edge)
          break;
        bEdgeIsHardCrease[0] = bEdgeIsHardCrease[1];
        bEdgeIsHardCrease[1] = edge->IsHardCrease();
        vertex = edge->m_vertex[ON_SUBD_EDGE_DIRECTION(edge_ptr)];
        if (nullptr == vertex)
          break;
        if (vertex->m_edge_count < 2)
          break;
        if (vertex->m_edge_count < vertex->m_face_count)
          break;
        S += vertex->m_edge_count;
        X += Internal_AtLeast4(vertex->m_edge_count);
        if ( bEdgeIsHardCrease[0] && bEdgeIsHardCrease[1] && vertex->IsCreaseOrCorner() )
        {
          // If this vertex has multiple sectors, the other sectors are isolated from center_face0 by hard creases.
          continue;
        }
        if (2 == vertex->m_edge_count)
        {
          // ring face has valence 2 vertex and the subdivision point for vertex_face
          // may be reference by 2 different edges from center_face0
          bValenceTwoVertices = true;
        }
        for (unsigned short vfi = 0; vfi < vertex->m_face_count; ++vfi)
        {
          vertex_face = vertex->m_faces[vfi];
          if (nullptr == vertex_face || center_face0 == vertex_face)
            continue;
          T += Internal_AtLeast4(vertex_face->m_edge_count);
        }
      }
      if (fei != N)
        break;
    }

    // NOTE: S >= 2*N
    v_capacity =  2*(S - N) + 1; // maximum possible and occurs when all face0 edges are distinct and smooth
    f_capacity =  S;  // maximum possible and occurs when all face0 edges are distinct and smooth

    // T = capacity required for vertex edge arrays on face subdivision vertices
    // 4*(S-N) = capacity required for vertex edge arrays on edge subdivision vertices
    // X = capacity required for vertex edge arrays on vertex subdivision vertices
    //
    a_capacity = 2*( X + T + 4 * (S - N) ); // Twice the number of edges from all subdivision vertices.

    return Internal_ReserveSubDWorkspace(
      v_capacity,
      f_capacity,
      a_capacity,
      (0U == center_face0->SubdivisionLevel()) || bValenceTwoVertices
    );
  }

  Destroy();
  if (nullptr == center_face0 )
    return true;

  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubD_FixedSizeHeap::Internal_HashEnabled() const
{
  return (ON_SubD_FixedSizeHeap::DisabledHashCount != m_h_count && m_h_capacity > 0);
}

unsigned int ON_SubD_FixedSizeHeap::Internal_Hash(ON_SubDComponentPtr component0)
{
  return Internal_HashEnabled() ? (((unsigned int)component0.Hash16FromTypeAndId()) % m_h_capacity) : 0U;
}

ON_SubDVertex* ON_SubD_FixedSizeHeap::Internal_HashFindVertex1(unsigned int hash, ON_SubDComponentPtr component0)
{
  if (Internal_HashEnabled())
  {
    for (ON_SubD_FixedSizeHeap_ComponentPairHashElement* e = m_hash_table[hash]; nullptr != e; e = e->m_next)
    {
      if (component0.m_ptr == e->m_pair.m_pair[0].m_ptr)
        return e->m_pair.m_pair[1].Vertex();
    }
  }
  return nullptr;
}

void ON_SubD_FixedSizeHeap::Internal_HashAddPair(unsigned int hash, ON_SubDComponentPtr component0, class ON_SubDVertex* vertex1)
{
  if (Internal_HashEnabled())
  {
    if (vertex1->m_id == m_v_index)
    {
      ON_SubD_FixedSizeHeap_ComponentPairHashElement* e = &m_hash_elements[vertex1->m_id - 1];
      e->m_pair.m_pair[0] = component0;
      e->m_pair.m_pair[1] = ON_SubDComponentPtr::Create(vertex1);
      e->m_next = m_hash_table[hash];
      m_hash_table[hash] = e;
      ++m_h_count;
    }
    else
    {
      ON_SUBD_ERROR("unexpected has table state");
    }
  }
}

ON_SubDVertex* ON_SubD_FixedSizeHeap::AllocateVertex(
  const double vertexP[3],
  unsigned int edge_capacity
  )
{
  if (nullptr == m_v || m_v_index >= m_v_capacity)
    return ON_SUBD_RETURN_ERROR(nullptr);

  const unsigned int face_capacity = edge_capacity;

  if (edge_capacity + face_capacity + m_p_index > m_p_capacity )
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON__UINT_PTR* a = nullptr;
  if (0 != edge_capacity || 0 != face_capacity)
  {
    if ( edge_capacity > 0xFFFFu)
      return ON_SUBD_RETURN_ERROR(nullptr);
    if ( face_capacity > 0xFFFFu)
      return ON_SUBD_RETURN_ERROR(nullptr);
    a = AllocatePtrArray(edge_capacity + face_capacity, true);
    if (nullptr == a)
      return ON_SUBD_RETURN_ERROR(nullptr);
  }

  ON_SubDVertex* v = m_v + m_v_index;
  memset(v, 0, sizeof(*v));
  if (m_v_index > 0)
  {
    // code in ON_SubDFaceNeighborhood.Subdivide() relies on
    // m_next_vertex being set this way.
    m_v[m_v_index - 1].m_next_vertex = v;
    v->m_prev_vertex = &m_v[m_v_index - 1];
  }
  v->m_id = ++m_v_index;

  if (nullptr != vertexP)
  {
    v->m_P[0] = vertexP[0];
    v->m_P[1] = vertexP[1];
    v->m_P[2] = vertexP[2];
  }

  if (edge_capacity > 0)
  {
    v->m_edge_capacity = (unsigned short)edge_capacity;
    v->m_edges = (ON_SubDEdgePtr*)a;
    a += edge_capacity;
  }
  if (face_capacity > 0)
  {
    v->m_face_capacity = (unsigned short)face_capacity;
    v->m_faces = (const ON_SubDFace**)a;
  }
  a = 0;

  return v;
}

ON_SubDVertex* ON_SubD_FixedSizeHeap::AllocateVertex(
  const ON_SubDVertex* vertex0,
  unsigned int edge_capacity
  )
{
  if ( nullptr == vertex0)
    return ON_SUBD_RETURN_ERROR(nullptr);

  double subdP[3];
  if (false == vertex0->GetSubdivisionPoint(subdP))
    return ON_SUBD_RETURN_ERROR(nullptr);
  ON_SubDVertex* v1 = AllocateVertex(subdP, edge_capacity);

  if (nullptr == v1)
    return ON_SUBD_RETURN_ERROR(nullptr);

  v1->SetSubdivisionLevel( vertex0->SubdivisionLevel() + 1 );

  v1->m_vertex_tag = vertex0->m_vertex_tag;

  const double crease_sector_vertex_sharpness0 = vertex0->Internal_InteriorCreaseVertexSharpnessForExperts();
  if (crease_sector_vertex_sharpness0 > 1.0)
  {
    // subdivide this value
    const double crease_sector_vertex_sharpness1 = ON_SubDEdgeSharpness::Sanitize(crease_sector_vertex_sharpness0 - 1.0);
    // The 2nd parameter is true because we have not attached the edges and faces yet.
    v1->Internal_SetInteriorCreaseVertexSharpnessForExperts(crease_sector_vertex_sharpness1, true);
  }

  if (vertex0->SurfacePointIsSet())
  {
    // copy any cached limit point from vertex0 to v1.
    ON_SubDSectorSurfacePoint limit_point;
    if (vertex0->GetSurfacePoint(vertex0->m_faces[0], limit_point))
    {
      if (nullptr == limit_point.m_sector_face)
      {
        limit_point.m_next_sector_limit_point = (const ON_SubDSectorSurfacePoint*)1;
        v1->SetSavedSurfacePoint(true, limit_point);
      }
    }
  }

  return v1;
}

ON_SubDVertex* ON_SubD_FixedSizeHeap::AllocateEdgeSubdivisionVertex(bool bUseFindOrAllocate, const ON_SubDEdge* edge0)
{
  return bUseFindOrAllocate ? FindOrAllocateVertex(edge0) : AllocateVertex(edge0);
}

ON_SubDVertex * ON_SubD_FixedSizeHeap::FindOrAllocateVertex(const ON_SubDEdge * edge0)
{
  if ( nullptr == edge0)
    return ON_SUBD_RETURN_ERROR(nullptr);

  const ON_SubDComponentPtr component0 = ON_SubDComponentPtr::Create(edge0);
  const unsigned int hash = Internal_Hash(component0);
  ON_SubDVertex* v1 = Internal_HashFindVertex1(hash, component0);

  if (nullptr != v1)
  {
    // found the previously allocated vertex
    if (((unsigned int)v1->m_edge_capacity) < 4)
    {
      ON_SUBD_ERROR("edge capacity was too small when vertex was created.");
    }
    return v1;
  }

  v1 = AllocateVertex(edge0);
  if (nullptr == v1)
    return ON_SUBD_RETURN_ERROR(nullptr);
  Internal_HashAddPair(hash, component0, v1);

  return v1;
}

ON_SubDVertex* ON_SubD_FixedSizeHeap::AllocateVertex(
  const ON_SubDEdge* edge0
  )
{
  if ( nullptr == edge0)
    return ON_SUBD_RETURN_ERROR(nullptr);

  double subdP[3];
  if (false == edge0->GetSubdivisionPoint(subdP))
    return ON_SUBD_RETURN_ERROR(nullptr);

  const unsigned int edge_capacity = 4;
  ON_SubDVertex* v1 = AllocateVertex(subdP, edge_capacity);
  if (nullptr == v1)
    return ON_SUBD_RETURN_ERROR(nullptr);

  v1->SetSubdivisionLevel( edge0->SubdivisionLevel() + 1 );

  if (ON_SubDEdgeTag::Smooth == edge0->m_edge_tag || ON_SubDEdgeTag::SmoothX == edge0->m_edge_tag)
    v1->m_vertex_tag = ON_SubDVertexTag::Smooth;
  else if (ON_SubDEdgeTag::Crease == edge0->m_edge_tag)
    v1->m_vertex_tag = ON_SubDVertexTag::Crease;

  return v1;
}

ON_SubDVertex * ON_SubD_FixedSizeHeap::FindOrAllocateVertex(const ON_SubDFace * face0)
{
  const unsigned int face0_edge_count = (nullptr != face0) ? ((unsigned int)face0->m_edge_count) : 0U;
  if (face0_edge_count < 3)
    return ON_SUBD_RETURN_ERROR(nullptr);

  const ON_SubDComponentPtr component0 = ON_SubDComponentPtr::Create(face0);
  const unsigned int hash = Internal_Hash(component0);
  ON_SubDVertex* v1 = Internal_HashFindVertex1(hash, component0);

  if (nullptr != v1)
  {
    // found the previously allocated vertex
    if (((unsigned int)v1->m_edge_capacity) < face0->m_edge_count)
    {
      ON_SUBD_ERROR("edge capacity was too small when vertex was created.");
    }
    return v1;
  }

  double subdP[3];
  if (false == face0->GetSubdivisionPoint(subdP))
    return ON_SUBD_RETURN_ERROR(nullptr);

  v1 = AllocateVertex(subdP, face0_edge_count );
  if (nullptr == v1)
    return ON_SUBD_RETURN_ERROR(nullptr);

  v1->SetSubdivisionLevel( face0->SubdivisionLevel() + 1 );
  v1->m_vertex_tag = ON_SubDVertexTag::Smooth;

  Internal_HashAddPair(hash, component0, v1);

  return v1;
}


ON_SubDVertex * ON_SubD_FixedSizeHeap::AllocateSectorFaceVertex(const ON_SubDFace * sector_face0)
{
  if (nullptr == sector_face0)
    return ON_SUBD_RETURN_ERROR(nullptr);
  double subdP[3];
  if (false == sector_face0->GetSubdivisionPoint(subdP))
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON_SubDVertex* v1 = AllocateVertex(subdP, 3 );
  if (nullptr == v1)
    return ON_SUBD_RETURN_ERROR(nullptr);

  v1->SetSubdivisionLevel( sector_face0->SubdivisionLevel() + 1 );
  v1->m_vertex_tag = ON_SubDVertexTag::Smooth;
  return v1;
}

const ON_SubDEdgePtr ON_SubD_FixedSizeHeap::AllocateEdge(
  bool bUseFindOrAllocatEdge,
  ON_SubDVertex* v0,
  double v0_sector_coefficient,
  ON_SubDVertex* v1,
  double v1_sector_coefficient
)
{
  return bUseFindOrAllocatEdge 
    ? FindOrAllocateEdge(v0, v0_sector_coefficient, v1, v1_sector_coefficient) 
    : AllocateEdge(v0, v0_sector_coefficient, v1, v1_sector_coefficient);
}

const ON_SubDEdgePtr ON_SubD_FixedSizeHeap::FindOrAllocateEdge(
  ON_SubDVertex * v0,
  double v0_sector_coefficient,
  ON_SubDVertex * v1,
  double v1_sector_coefficient
)
{
  if ( nullptr == v0 || nullptr == v0->m_edges)
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  if ( nullptr == v1 || nullptr == v1->m_edges)
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  for (unsigned short v0ei = 0; v0ei < v0->m_edge_count; ++v0ei)
  {
    const ON_SubDEdgePtr ep = v0->m_edges[v0ei];
    if (v0 == ep.RelativeVertex(0))
    {
      if (v1 == ep.RelativeVertex(1))
        return ep;
    }
    else if (v0 == ep.RelativeVertex(1))
    {
      if (v1 == ep.RelativeVertex(0))
        return ep.Reversed();
    }
    else
    {
      ON_SUBD_RETURN_ERROR("Invalid ON_SubDEdgePtr in vertex->m_edge[] array");
    }
  }

  return AllocateEdge(v0, v0_sector_coefficient, v1, v1_sector_coefficient);
}

const ON_SubDEdgePtr ON_SubD_FixedSizeHeap::AllocateEdge(
  ON_SubDVertex* v0,
  double v0_sector_coefficient,
  ON_SubDVertex* v1,
  double v1_sector_coefficient
  )
{
  if ( nullptr != v0 && nullptr == v0->m_edges)
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  if ( nullptr != v1 && nullptr == v1->m_edges)
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  if (nullptr == m_e || m_e_index >= m_e_capacity)
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);

  bool bTaggedVertex[2];
  if (nullptr != v0)
  {
    if (nullptr == v0->m_edges || v0->m_edge_count >= v0->m_edge_capacity)
      return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
    if (ON_SubDVertexTag::Smooth == v0->m_vertex_tag)
    {
      bTaggedVertex[0] = false;
      v0_sector_coefficient = ON_SubDSectorType::IgnoredSectorCoefficient;
    }
    else
    {
      bTaggedVertex[0] = (ON_SubDVertexTag::Unset != v0->m_vertex_tag);
    }
  }
  else
    bTaggedVertex[0] = false;

  if (nullptr != v1)
  {
    if (nullptr == v1->m_edges || v1->m_edge_count >= v1->m_edge_capacity)
      return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
    if (ON_SubDVertexTag::Smooth == v1->m_vertex_tag)
    {
      bTaggedVertex[1] = false;
      v1_sector_coefficient = ON_SubDSectorType::IgnoredSectorCoefficient;
    }
    else
    {
      bTaggedVertex[1] = (ON_SubDVertexTag::Unset != v0->m_vertex_tag);
      if (bTaggedVertex[0] && bTaggedVertex[1])
      {
        // crease edge - no weights
        v0_sector_coefficient = ON_SubDSectorType::IgnoredSectorCoefficient;
        v1_sector_coefficient = ON_SubDSectorType::IgnoredSectorCoefficient;
      }
    }
  }
  else
    bTaggedVertex[1] = false;

  if ( false == ON_SubDSectorType::IsValidSectorCoefficientValue(v0_sector_coefficient, true))
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);

  if ( false == ON_SubDSectorType::IsValidSectorCoefficientValue(v1_sector_coefficient, true))
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);

  ON_SubDEdge* e = m_e + m_e_index;
  memset(e, 0, sizeof(*e));
  if (m_e_index > 0)
  {
    // code in ON_SubDFaceNeighborhood.Subdivide() relies on m_next_edge being set this way.
    m_e[m_e_index - 1].m_next_edge = e;
    e->m_prev_edge = &m_e[m_e_index - 1];
  }

  e->m_id = ++m_e_index;

  if (nullptr != v0)
  {
    e->m_vertex[0] = v0;
    v0->m_edges[v0->m_edge_count++] = ON_SubDEdgePtr::Create(e,0);
    //v0->m_vertex_edge_order = ON_SubD::VertexEdgeOrder::unset;
    e->SetSubdivisionLevel(v0->SubdivisionLevel());
  }

  if (nullptr != v1)
  {
    e->m_vertex[1] = v1;
    v1->m_edges[v1->m_edge_count++] = ON_SubDEdgePtr::Create(e,1);
    //v1->m_vertex_edge_order = ON_SubD::VertexEdgeOrder::unset;
    if ( e->SubdivisionLevel() < v1->SubdivisionLevel())
      e->SetSubdivisionLevel(v1->SubdivisionLevel());
  }

  e->m_sector_coefficient[0] = v0_sector_coefficient;
  e->m_sector_coefficient[1] = v1_sector_coefficient;
  e->m_edge_tag = (bTaggedVertex[0] && bTaggedVertex[1]) ? ON_SubDEdgeTag::Crease : ON_SubDEdgeTag::Smooth;

  return ON_SubDEdgePtr::Create(e,0);
}

ON_SubDFace* ON_SubD_FixedSizeHeap::Internal_AllocateFace(
  unsigned int level_zero_face_id,
  unsigned int parent_face_id
  )
{
  if (nullptr == m_f || m_f_index >= m_f_capacity)
    return ON_SUBD_RETURN_ERROR(nullptr);
  ON_SubDFace* f = m_f + m_f_index;
  memset(f, 0, sizeof(*f));
  if (m_f_index > 0)
  {
    // code in ON_SubDFaceNeighborhood.Subdivide() relies on
    // m_next_face being set this way.
    m_f[m_f_index-1].m_next_face = f;
    f->m_prev_face = &m_f[m_f_index-1];
  }

  f->m_id = ++m_f_index;
  f->ClearPerFaceColor();
  f->m_level_zero_face_id = (0 == level_zero_face_id) ? parent_face_id : level_zero_face_id;

  return f;
}


ON_SubDFace* ON_SubD_FixedSizeHeap::AllocateQuad(
  unsigned int zero_face_id,
  unsigned int parent_face_id,
  ON_SubDEdgePtr e0,
  ON_SubDEdgePtr e1,
  ON_SubDEdgePtr e2,
  ON_SubDEdgePtr e3
)
{
  const ON_SubDEdgePtr eptrs[4] = { e0,e1,e2,e3 };
  return AllocateQuad(zero_face_id, parent_face_id, eptrs);
}

ON_SubDFace* ON_SubD_FixedSizeHeap::AllocateQuad(
  unsigned int zero_face_id,
  unsigned int parent_face_id,
  const ON_SubDEdgePtr eptrs[4]
  )
{
  if (nullptr == eptrs)
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON_SubDEdge* edges[4] = {
    ON_SUBD_EDGE_POINTER(eptrs[0].m_ptr),
    ON_SUBD_EDGE_POINTER(eptrs[1].m_ptr),
    ON_SUBD_EDGE_POINTER(eptrs[2].m_ptr),
    ON_SUBD_EDGE_POINTER(eptrs[3].m_ptr)};

  if (nullptr == edges[0] || edges[0]->m_face_count > 1)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (nullptr == edges[1] || edges[1]->m_face_count > 1)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (nullptr == edges[2] || edges[2]->m_face_count > 1)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (nullptr == edges[3] || edges[3]->m_face_count > 1)
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON__UINT_PTR edgedirs[4] = {
    ON_SUBD_EDGE_DIRECTION(eptrs[0].m_ptr),
    ON_SUBD_EDGE_DIRECTION(eptrs[1].m_ptr),
    ON_SUBD_EDGE_DIRECTION(eptrs[2].m_ptr),
    ON_SUBD_EDGE_DIRECTION(eptrs[3].m_ptr)};

  ON_SubDVertex* vertices[4] = {
    const_cast<ON_SubDVertex*>(edges[0]->m_vertex[edgedirs[0]]),
    const_cast<ON_SubDVertex*>(edges[1]->m_vertex[edgedirs[1]]),
    const_cast<ON_SubDVertex*>(edges[2]->m_vertex[edgedirs[2]]),
    const_cast<ON_SubDVertex*>(edges[3]->m_vertex[edgedirs[3]]) };

  if (nullptr == vertices[0] || nullptr == vertices[0]->m_faces || vertices[0]->m_face_count >= vertices[0]->m_face_capacity || vertices[0] != edges[3]->m_vertex[1-edgedirs[3]])
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (nullptr == vertices[1] || nullptr == vertices[1]->m_faces || vertices[1]->m_face_count >= vertices[1]->m_face_capacity || vertices[1] != edges[0]->m_vertex[1-edgedirs[0]])
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (nullptr == vertices[2] || nullptr == vertices[2]->m_faces || vertices[2]->m_face_count >= vertices[2]->m_face_capacity || vertices[2] != edges[1]->m_vertex[1-edgedirs[1]])
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (nullptr == vertices[3] || nullptr == vertices[3]->m_faces || vertices[3]->m_face_count >= vertices[3]->m_face_capacity || vertices[3] != edges[2]->m_vertex[1-edgedirs[2]])
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON_SubDFace* f = Internal_AllocateFace(zero_face_id,parent_face_id);
  if (nullptr == f)
    return ON_SUBD_RETURN_ERROR(nullptr);

  f->m_edge_count = 4;
  f->m_edge4[0] = eptrs[0];
  f->m_edge4[1] = eptrs[1];
  f->m_edge4[2] = eptrs[2];
  f->m_edge4[3] = eptrs[3];

  edges[0]->m_face2[edges[0]->m_face_count++] = ON_SubDFacePtr::Create(f,edgedirs[0]);
  edges[1]->m_face2[edges[1]->m_face_count++] = ON_SubDFacePtr::Create(f,edgedirs[1]);
  edges[2]->m_face2[edges[2]->m_face_count++] = ON_SubDFacePtr::Create(f,edgedirs[2]);
  edges[3]->m_face2[edges[3]->m_face_count++] = ON_SubDFacePtr::Create(f,edgedirs[3]);

  vertices[0]->m_faces[vertices[0]->m_face_count++] = f;
  //vertices[0]->m_vertex_edge_order = ON_SubD::VertexEdgeOrder::unset;
  vertices[1]->m_faces[vertices[1]->m_face_count++] = f;
  //vertices[1]->m_vertex_edge_order = ON_SubD::VertexEdgeOrder::unset;
  vertices[2]->m_faces[vertices[2]->m_face_count++] = f;
  //vertices[2]->m_vertex_edge_order = ON_SubD::VertexEdgeOrder::unset;
  vertices[3]->m_faces[vertices[3]->m_face_count++] = f;
  //vertices[3]->m_vertex_edge_order = ON_SubD::VertexEdgeOrder::unset;

  f->SetSubdivisionLevel( edges[0]->SubdivisionLevel() );

  return f;
}

ON__UINT_PTR* ON_SubD_FixedSizeHeap::AllocatePtrArray(
  unsigned int capacity,
  bool bZeroMemory
  )
{
  if (0 == capacity)
    return nullptr;

  if (nullptr == m_p || capacity + m_p_index > m_p_capacity)
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON__UINT_PTR* p = m_p + m_p_index;
  m_p_index += capacity;

  if (bZeroMemory)
  {
    ON__UINT_PTR* p1 = p + capacity;
    while (p1 > p)
    {
      *(--p1) = 0;
    }
  }

  return p;
}

bool ON_SubD_FixedSizeHeap::ReturnPtrArray(
  void* p,
  unsigned int capacity
  )
{
  if (nullptr != m_p && capacity <= m_p_index && p == m_p + (m_p_index - capacity))
  {
    m_p_index -= capacity;
    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDHeap
//

size_t ON_SubDHeap::m_offset_vertex_id = 0;
size_t ON_SubDHeap::m_offset_edge_id = 0;
size_t ON_SubDHeap::m_offset_face_id = 0;

ON_SubDHeap::ON_SubDHeap()
{
  m_fspv.Create(sizeof(class ON_SubDVertex), 0, 0);
  m_fspe.Create(sizeof(class ON_SubDEdge), 0, 0);
  m_fspf.Create(sizeof(class ON_SubDFace), 0, 0);
  m_fsp5.Create(5 * sizeof(ON__UINT_PTR), 0, 0);
  m_fsp9.Create(9 * sizeof(ON__UINT_PTR), 0, 0);
  m_fsp17.Create(17 * sizeof(ON__UINT_PTR), 0, 0);

  if (0 == ON_SubDHeap::m_offset_vertex_id)
  {
    ON_SubDVertex v;
    ON_SubDHeap::m_offset_vertex_id = ((const char*)(&v.m_id)) - ((const char*)&v);
    ON_SubDEdge e;
    ON_SubDHeap::m_offset_edge_id = ((const char*)(&e.m_id)) - ((const char*)&e);
    ON_SubDFace f;
    ON_SubDHeap::m_offset_face_id = ((const char*)(&f.m_id)) - ((const char*)&f);
  }
}

ON_SubDHeap::~ON_SubDHeap()
{
  Destroy();
}

class ON_SubDComponentBase* ON_SubDHeap::Internal_AllocateComponentAndSetId(
  ON_FixedSizePool& fspc,
  ON_SubDComponentBase*& unused_list,
  unsigned int& max_id,
  unsigned int candidate_id
)
{
  // fspc is a m_fspv / m_fspe / m_fspf fixed size pool on an ON_SubDHeap.
  // unused_list is the corresponding m_unused_vertex / m_unused_edge / m_unused_face list on that ON_SubDHeap.
  

  // In order for m_fspv.ElementFromId(), m_fspe.ElementFromId() , m_fspf.ElementFromId() 
  // to work, it is critical that once a vertex/edge/face is allocated from m_fspv/mfspe/mfspf
  // the value of m_id never changes.  This is important because the value of m_id must persist
  // in binary archives in order for ON_COMPONENT_INDEX values to persist in binary archives.

  ON_SubDComponentBaseLink* c;
  if (candidate_id >3000000000U)
  {
    // Requests for a candidate_id value above 3 billion are ignored to insure
    // there is plenty of room for ids. 
    // It's almost certainly a bug if candidate_id > several million or so.
    candidate_id = 0; 
  }

  if (nullptr != unused_list && candidate_id <= max_id)
  {
    ON_SubDComponentBaseLink* prev = nullptr;

    if (candidate_id > 0 && candidate_id != unused_list->m_id)
    {
      // Caller wants a specific id. If it's found here, the context is probably
      // some editing code where the caller deleted the component and now wants it back
      // to preserve the id structure.

      for (prev = static_cast<ON_SubDComponentBaseLink*>(unused_list); nullptr != prev; prev = const_cast<ON_SubDComponentBaseLink*>(prev->m_next))
      {
        // If candidate_id is somewhere in the unused list after the first element, return it.
        if (nullptr != prev->m_next && candidate_id == prev->m_next->m_id)
          break;
      }
    }

    if (nullptr != prev)
    {
      // The candidate was found somewhere in the unused_list after the first element.
      c = const_cast<ON_SubDComponentBaseLink*>(prev->m_next);
      prev->m_next = c->m_next;
    }
    else
    {
      // Return element at the head of the unused list.
      c = static_cast<ON_SubDComponentBaseLink*>(unused_list);
      unused_list = const_cast<ON_SubDComponentBaseLink*>(c->m_next);
    }
    const unsigned int id = c->m_id;
    if (ON_UNSET_UINT_INDEX == (&c->m_id)[1] && c->m_status.IsDeleted() )
    {
      // When a vertex/edge/face is put on the unused list, m_archive_id is set to ON_UNSET_UINT_INDEX and m_status = ON_ComponentStatus::Deleted.
      memset(c, 0, fspc.SizeofElement());
      c->m_id = id;
    }
    else
    {
      // Something is modifying returned elements. This is a serious bug.
      ON_SubDIncrementErrorCount();
      memset(c, 0, fspc.SizeofElement());
      c->m_id = ++max_id;
    }
  }
  else
  {
    if (candidate_id > max_id)
    {
      // Caller wants a specific id. This is common when copying subds
      // and some of the components of the original subd were deleted.
      max_id = candidate_id;
    }
    else
    {
      ////#if defined(ON_DEBUG)
      ////      // TEMPORARY ERROR CHECK added Feb 2020 to test new code. Can be removed in April 2020 or earlier if needed.
      ////      // Ask Dale Lear if confused.
      ////      if (0 != candidate_id)
      ////      {
      ////        ON_SUBD_ERROR("Unable to assign candidate_id");
      ////      }
      ////#endif
      // otherwise assign the next id to this component.
      candidate_id = ++max_id;
    }

    // allocate a new vertex.
    c = (ON_SubDComponentBaseLink*)fspc.AllocateElement();
    c->m_id = candidate_id;
  }
  return c;
}


class ON_SubDVertex* ON_SubDHeap::AllocateVertexAndSetId(unsigned int candidate_vertex_id)
{
  ON_SubDComponentBase* unused_list = m_unused_vertex;
  ON_SubDComponentBase* c = ON_SubDHeap::Internal_AllocateComponentAndSetId(
    m_fspv,
    unused_list,
    m_max_vertex_id,
    candidate_vertex_id
  );
  m_unused_vertex = static_cast<ON_SubDVertex*>(unused_list);
  return static_cast<ON_SubDVertex*>(c);
}

void ON_SubDHeap::ReturnVertex(class ON_SubDVertex* v)
{
  if (nullptr != v)
  {
    ReturnVertexEdgeAndFaceArrays(v);
    (&v->m_id)[1] = ON_UNSET_UINT_INDEX; // m_archive_id == ON_UNSET_UINT_INDEX marks the fixed size pool element as unused
    v->m_status = ON_ComponentStatus::Deleted;
    v->m_next_vertex = m_unused_vertex;
    m_unused_vertex = v;
    // It is critical that v->m_symmetry_set_next remains set
    // so deleted elements of symmetric SubDs can be found.

    // NO! // m_fspv.ReturnElement(v);
    // See comments in AllocateVertexAndSetId();
  }
}

class ON_SubDEdge* ON_SubDHeap::AllocateEdgeAndSetId(
  unsigned int candidate_edge_id
  )
{
  ON_SubDComponentBase* unused_list = m_unused_edge;
  ON_SubDComponentBase* c = ON_SubDHeap::Internal_AllocateComponentAndSetId(
    m_fspe,
    unused_list,
    m_max_edge_id,
    candidate_edge_id
  );
  m_unused_edge = static_cast<ON_SubDEdge*>(unused_list);
  return static_cast<ON_SubDEdge*>(c);
}

void ON_SubDHeap::ReturnEdge(class ON_SubDEdge* e)
{
  if (nullptr != e)
  {
    if (nullptr != e->m_facex)
      ReturnArray(e->m_facex_capacity,(ON__UINT_PTR*)e->m_facex);
    (&e->m_id)[1] = ON_UNSET_UINT_INDEX; // m_archive_id == ON_UNSET_UINT_INDEX marks the fixed size pool element as unused
    e->m_status = ON_ComponentStatus::Deleted;
    e->m_next_edge = m_unused_edge;
    m_unused_edge = e;
    // It is critical that e->m_symmetry_set_next remains set
    // so deleted elements of symmetric SubDs can be found.

    // NO! // m_fspe.ReturnElement(e);
    // See comments in AllocateVertexAndSetId();
  }
}

class ON_SubDFace* ON_SubDHeap::AllocateFaceAndSetId(
  unsigned int candidate_face_id
)
{
  ON_SubDComponentBase* unused_list = m_unused_face;
  ON_SubDFace* f = static_cast<ON_SubDFace*>( ON_SubDHeap::Internal_AllocateComponentAndSetId(
    m_fspf,
    unused_list,
    m_max_face_id,
    candidate_face_id
  ) );
  m_unused_face = static_cast<ON_SubDFace*>(unused_list);
  if (nullptr != f)
    f->ClearPerFaceColor();
  return f;
}

void ON_SubDHeap::ReturnFace(class ON_SubDFace* f)
{
  if (nullptr != f)
  {
    if (f->m_texture_points)
    {
      this->Return3dPointArray(f->m_texture_points);
      f->m_texture_points = nullptr;
      f->m_texture_status_bits = 0;
    }
    ReturnArray(f->m_edgex_capacity,(ON__UINT_PTR*)f->m_edgex);
    (&f->m_id)[1] = ON_UNSET_UINT_INDEX; // m_archive_id == ON_UNSET_UINT_INDEX marks the fixed size pool element as unused
    f->m_status = ON_ComponentStatus::Deleted;
    f->m_next_face = m_unused_face;
    m_unused_face = f;
    // It is critical that f->m_symmetry_set_next remains set
    // so deleted elements of symmetric SubDs can be found.

    // NO! // m_fspf.ReturnElement(f);
    // See comments in AllocateVertexAndSetId();
  }
}

void ON_SubDHeap::Clear()
{
  class tagWSItem* p = m_ws;
  m_ws = 0;
  while (p)
  {
    class tagWSItem* next = p->m_next;
    onfree(p);
    p = next;
  }

  m_fspv.ReturnAll();
  m_fspe.ReturnAll();
  m_fspf.ReturnAll();

  m_fsp5.ReturnAll();
  m_fsp9.ReturnAll();
  m_fsp17.ReturnAll();

  m_full_fragment_display_density = 0;
  m_full_fragment_count_estimate = 0;
  m_part_fragment_count_estimate = 0;

  m_fsp_full_fragments.ReturnAll();
  m_fsp_part_fragments.ReturnAll();
  m_fsp_oddball_fragments.ReturnAll();
  m_fsp_limit_curves.ReturnAll();

  const size_t frag_size_count = sizeof(m_unused_fragments) / sizeof(m_unused_fragments[0]);
  for (size_t i = 0; i < frag_size_count; ++i)
    m_unused_fragments[i] = nullptr;

  m_unused_vertex = nullptr;
  m_unused_edge = nullptr;
  m_unused_face = nullptr;

  m_max_vertex_id = 0;
  m_max_edge_id = 0;
  m_max_face_id = 0;
}

void ON_SubDHeap::Destroy()
{
  Clear();
  m_fspv.Destroy();
  m_fspe.Destroy();
  m_fspf.Destroy();
  m_fsp5.Destroy();
  m_fsp9.Destroy();
  m_fsp17.Destroy();
}

void ON_SubDHeap::ClearArchiveId()
{
  ON_FixedSizePoolIterator fit;
  fit.Create(&m_fspv);
  for (ON_SubDVertex* v = (ON_SubDVertex*)fit.FirstElement(); nullptr != v; v = (ON_SubDVertex*)fit.NextElement())
  {
    if ( ON_UNSET_UINT_INDEX != v->ArchiveId())
      v->SetArchiveId(0);
  }
  fit.Create(&m_fspe);
  for (ON_SubDEdge* e = (ON_SubDEdge*)fit.FirstElement(); nullptr != e; e = (ON_SubDEdge*)fit.NextElement())
  {
    if ( ON_UNSET_UINT_INDEX != e->ArchiveId())
      e->SetArchiveId(0);
  }
  fit.Create(&m_fspf);
  for (ON_SubDFace* f = (ON_SubDFace*)fit.FirstElement(); nullptr != f; f = (ON_SubDFace*)fit.NextElement())
  {
    if ( ON_UNSET_UINT_INDEX != f->ArchiveId())
      f->SetArchiveId(0);
  }
}

const class ON_SubDVertex* ON_SubDHeap::VertexFromId(
  unsigned int vertex_id
  ) const
{
  if ( 0 == vertex_id || ON_UNSET_UINT_INDEX == vertex_id)
    return ON_SUBD_RETURN_ERROR(nullptr);
  const class ON_SubDVertex* vertex = (const class ON_SubDVertex*)m_fspv.ElementFromId(ON_SubDHeap::m_offset_vertex_id,vertex_id);
  if ( nullptr == vertex || vertex_id != vertex->m_id)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if ( ON_UNSET_UINT_INDEX == vertex->ArchiveId() )
    return ON_SUBD_RETURN_ERROR(nullptr);
  return vertex;
}

const class ON_SubDEdge* ON_SubDHeap::EdgeFromId(
  unsigned int edge_id
  ) const
{
  if ( 0 == edge_id || ON_UNSET_UINT_INDEX == edge_id)
    return ON_SUBD_RETURN_ERROR(nullptr);
  const class ON_SubDEdge* edge = (const class ON_SubDEdge*)m_fspe.ElementFromId(ON_SubDHeap::m_offset_edge_id,edge_id);
  if ( nullptr == edge || edge_id != edge->m_id)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if ( ON_UNSET_UINT_INDEX == edge->ArchiveId() )
    return ON_SUBD_RETURN_ERROR(nullptr);
  return edge;
}

const class ON_SubDFace* ON_SubDHeap::FaceFromId(
  unsigned int face_id
  ) const
{
  if ( 0 == face_id || ON_UNSET_UINT_INDEX == face_id)
    return ON_SUBD_RETURN_ERROR(nullptr);
  const class ON_SubDFace* face = (const class ON_SubDFace*)m_fspf.ElementFromId(ON_SubDHeap::m_offset_face_id,face_id);
  if ( nullptr == face || face_id != face->m_id)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if ( ON_UNSET_UINT_INDEX == face->ArchiveId() )
    return ON_SUBD_RETURN_ERROR(nullptr);
  return face;
}

static bool ON_SubDHeapIsNotValid(bool bSilentError)
{
  ON_SubDIncrementErrorCount();
  return bSilentError ? false : ON_IsNotValid();
}

bool ON_SubDHeap::IsValid(
  bool bSilentError,
  ON_TextLog* text_log
) const
{
  if (false == m_fspv.ElementIdIsIncreasing(ON_SubDHeap::m_offset_vertex_id))
  {
    if (nullptr != text_log)
      text_log->Print("m_fspv.ElementIdIsIncreasing() is false.");
    return ON_SubDHeapIsNotValid(bSilentError);
  }

  if (false == m_fspe.ElementIdIsIncreasing(ON_SubDHeap::m_offset_edge_id))
  {
    if (nullptr != text_log)
      text_log->Print("m_fspe.ElementIdIsIncreasing() is false.");
    return ON_SubDHeapIsNotValid(bSilentError);
  }

  if (false == m_fspf.ElementIdIsIncreasing(ON_SubDHeap::m_offset_face_id))
  {
    if (nullptr != text_log)
      text_log->Print("m_fspf.ElementIdIsIncreasing() is false.");
    return ON_SubDHeapIsNotValid(bSilentError);
  }

  const unsigned max_fspv_max_id = m_fspv.MaximumElementId(ON_SubDHeap::m_offset_vertex_id);
  if (m_max_vertex_id != max_fspv_max_id)
  {
    if (nullptr != text_log)
      text_log->Print("m_max_vertex_id = %u != %u = m_fspv.MaximumElementId()\n", m_max_vertex_id, max_fspv_max_id);
    return ON_SubDHeapIsNotValid(bSilentError);
  }

  const unsigned max_fspe_max_id = m_fspe.MaximumElementId(ON_SubDHeap::m_offset_edge_id);
  if (m_max_edge_id != max_fspe_max_id)
  {
    if (nullptr != text_log)
      text_log->Print("m_max_edge_id = %u != %u = m_fspe.MaximumElementId()\n", m_max_edge_id, max_fspe_max_id);
    return ON_SubDHeapIsNotValid(bSilentError);
  }

  const unsigned max_fspf_max_id = m_fspf.MaximumElementId(ON_SubDHeap::m_offset_face_id);
  if (m_max_face_id != max_fspf_max_id)
  {
    if (nullptr != text_log)
      text_log->Print("m_max_face_id = %u != %u = m_fspf.MaximumElementId()\n", m_max_face_id, max_fspf_max_id);
    return ON_SubDHeapIsNotValid(bSilentError);
  }

  return true;
}

void ON_SubDHeap::ResetIds()
{
  const unsigned int first_id = 1;
  const unsigned int next_vertex_id = m_fspv.ResetElementId(ON_SubDHeap::m_offset_vertex_id,first_id);
  const unsigned int next_edge_id = m_fspe.ResetElementId(ON_SubDHeap::m_offset_edge_id,first_id);
  const unsigned int next_face_id = m_fspf.ResetElementId(ON_SubDHeap::m_offset_face_id,first_id);

  // m_max_..._id  =  maximum assigned id = m_next_..._id - 1
  m_max_vertex_id = (next_vertex_id > first_id) ? (next_vertex_id - 1U) : 0U;
  m_max_edge_id = (next_edge_id > first_id) ? (next_edge_id - 1U) : 0U;
  m_max_face_id = (next_face_id > first_id) ? (next_face_id - 1U) : 0U;
}

ON_FixedSizePool* ON_SubDHeap::Internal_ComponentFixedSizePool(
  ON_SubDComponentPtr::Type component_type
)
{
  switch (component_type)
  {
  case ON_SubDComponentPtr::Type::Unset:
    break;
  case ON_SubDComponentPtr::Type::Vertex:
    return &m_fspv;
    break;
  case ON_SubDComponentPtr::Type::Edge:
    return &m_fspe;
    break;
  case ON_SubDComponentPtr::Type::Face:
    return &m_fspf;
    break;
  default:
    break;
  }
  return nullptr;
}

const ON_FixedSizePool* ON_SubDHeap::Internal_ComponentFixedSizePool(
  ON_SubDComponentPtr::Type component_type
) const
{
  switch (component_type)
  {
  case ON_SubDComponentPtr::Type::Unset:
    break;
  case ON_SubDComponentPtr::Type::Vertex:
    return &m_fspv;
    break;
  case ON_SubDComponentPtr::Type::Edge:
    return &m_fspe;
    break;
  case ON_SubDComponentPtr::Type::Face:
    return &m_fspf;
    break;
  default:
    break;
  }
  return nullptr;
}


size_t ON_SubDHeap::OversizedElementCapacity(size_t count)
{
  size_t capacity = 32 * (count / 32);
  if (count % 32 > 0 || 0 == count)
    capacity += 32;
  return capacity;
}

ON__UINT_PTR* ON_SubDHeap::AllocateOversizedElement(size_t* capacity)
{
  class tagWSItem* p;
  size_t actual_capacity = ON_SubDHeap::OversizedElementCapacity(*capacity);
  size_t sz = (actual_capacity + 1)*sizeof(ON__UINT_PTR);
  sz += sizeof(*p);
  p = (class tagWSItem*)onmalloc(sz);
  p->m_next = m_ws;
  if (p->m_next)
    p->m_next->m_prev = p;
  p->m_prev = 0;
  m_ws = p;
  ON__UINT_PTR* a = (ON__UINT_PTR*)(p + 1);
  *a++ = actual_capacity;
  *capacity = actual_capacity;
  return a;
}

void ON_SubDHeap::ReturnOversizedElement(
  size_t capacity,
  ON__UINT_PTR* a
  )
{
  if (0 != a && capacity > 0)
  {
    class tagWSItem* p = ((class tagWSItem*)(a - 1)) - 1;
    if (p == m_ws)
    {
      if (nullptr != p->m_next)
      {
        m_ws = p->m_next;
        p->m_next->m_prev = 0;
      }
      else
        m_ws = nullptr;
    }
    else
    {
      if (p->m_next)
        p->m_next->m_prev = p->m_prev;
      p->m_prev->m_next = p->m_next;
    }
    onfree(p);
  }
}

ON__UINT_PTR* ON_SubDHeap::ResizeArray(
  size_t current_count,
  size_t current_capacity,
  ON__UINT_PTR* current_a,
  size_t* new_capacity
  )
{
  ON__UINT_PTR capacity = ON_SubDHeap::ArrayCapacity(current_capacity,current_a);
  if (capacity <= 0)
  {
    return (ON__UINT_PTR*)AllocateArray(new_capacity);
  }

  if (*new_capacity <= 0)
  {
    ReturnArray(current_capacity,current_a);
    *new_capacity = 0;
    return nullptr;
  }

  if (*new_capacity <= capacity)
  {
    return current_a;
  }

  ON__UINT_PTR* new_a = AllocateArray(new_capacity);
  ON__UINT_PTR* a1 = new_a + current_count;
  while (new_a < a1)
  {
    *new_a++ = *current_a++;
  }
  ReturnArray(current_capacity,current_a - current_count);
  return (a1 - current_count);
}

bool ON_SubDHeap::GrowVertexEdgeArray(
  ON_SubDVertex* v,
  size_t capacity
  )
{
  if ( nullptr == v)
    return ON_SUBD_RETURN_ERROR(false);
  if ( 0 == capacity )
    capacity = v->m_edge_count+1;
  if ( capacity <= v->m_edge_capacity)
    return true;
  ON__UINT_PTR* a = ResizeArray(v->m_edge_count,v->m_edge_capacity,(ON__UINT_PTR*)v->m_edges,&capacity);
  if ( nullptr == a )
  {
    v->m_edge_count = 0;
    v->m_edge_capacity = 0;
    v->m_edges = 0;
    return ON_SUBD_RETURN_ERROR(false);
  }
  v->m_edges = (ON_SubDEdgePtr*)a;
  v->m_edge_capacity = (unsigned short)capacity;
  return true;
}

bool ON_SubDHeap::GrowVertexFaceArray(
  ON_SubDVertex* v,
  size_t capacity
  )
{
  if ( nullptr == v)
    return ON_SUBD_RETURN_ERROR(false);
  if ( 0 == capacity )
    capacity = v->m_face_count+1;
  if ( capacity <= v->m_face_capacity)
    return true;
  ON__UINT_PTR* a = ResizeArray(v->m_face_count,v->m_face_capacity,(ON__UINT_PTR*)v->m_faces,&capacity);
  if (nullptr == a)
  {
    v->m_face_count = 0;
    v->m_face_capacity = 0;
    v->m_faces = nullptr;
    return ON_SUBD_RETURN_ERROR(false);
  }
  v->m_faces = (const ON_SubDFace**)a;
  v->m_face_capacity = (unsigned short)capacity;
  return true;
}

bool ON_SubDHeap::GrowEdgeFaceArray(
  ON_SubDEdge* e,
  size_t capacity
  )
{
  if ( nullptr == e)
    return ON_SUBD_RETURN_ERROR(false);
  if ( 0 == capacity )
    capacity = e->m_face_count+1;
  if ( capacity <= (size_t)(2 + e->m_facex_capacity))
    return true;
  size_t xcapacity = capacity-2;
  ON__UINT_PTR* a = ResizeArray((e->m_face_count>2) ? (e->m_face_count-2) : 0,e->m_facex_capacity,(ON__UINT_PTR*)e->m_facex,&xcapacity);
  if ( nullptr == a )
  {
    e->m_face_count = 0;
    e->m_facex_capacity = 0;
    e->m_facex = nullptr;
    return ON_SUBD_RETURN_ERROR(false);
  }
  e->m_facex = (ON_SubDFacePtr*)a;
  e->m_facex_capacity = (unsigned short)xcapacity;
  return true;
}

bool ON_SubDHeap::GrowFaceEdgeArray(
  ON_SubDFace* f,
  size_t capacity
  )
{
  if ( nullptr == f)
    return ON_SUBD_RETURN_ERROR(false);

  // The capacity of f->m_texture_points[] must always be 4 + f->m_edgex_capacity
  const size_t texture_point_capacity0 = f->TexturePointsCapacity();

  if ( 0 == capacity )
    capacity = f->m_edge_count+1;
  if ( capacity <= (size_t)(4 + f->m_edgex_capacity))
    return true;
  size_t xcapacity = capacity-4;
  ON__UINT_PTR* a = ResizeArray((f->m_edge_count>4) ? (f->m_edge_count-4) : 0,f->m_edgex_capacity,(ON__UINT_PTR*)f->m_edgex,&xcapacity);
  if ( nullptr == a )
  {
    f->m_edge_count = 0;
    f->m_edgex_capacity = 0;
    f->m_edgex = nullptr;
    // also remove texture points
    f->m_texture_status_bits &= ON_SubDFace::TextureStatusBits::NotTexturePointsBitsMask;
    f->m_texture_points = nullptr;
    return ON_SUBD_RETURN_ERROR(false);
  }
  f->m_edgex = (ON_SubDEdgePtr*)a;
  f->m_edgex_capacity = (unsigned short)xcapacity;
  if (texture_point_capacity0 > 0)
  {
    const size_t texture_point_capacity1 = 4 + xcapacity;
    if (texture_point_capacity0 < texture_point_capacity1)
    {
      ON_3dPoint* texture_points0 = f->m_texture_points;
      ON_3dPoint* texture_points1 = this->Allocate3dPointArray(texture_point_capacity1);
      for (size_t i = 0; i < texture_point_capacity0; ++i)
        texture_points1[i] = texture_points0[i];
      for (size_t i = texture_point_capacity0; i < texture_point_capacity1; ++i)
        texture_points1[i] = ON_3dPoint::NanPoint;
      f->m_texture_points = texture_points1;
      this->Return3dPointArray(texture_points0);
    }
  }
  return true;
}

unsigned int ON_SubDHeap::Managed3dPointArrayCapacity(class ON_3dPoint* point_array)
{
  const unsigned int point_capacity =
    (nullptr != point_array)
    ? *((unsigned int*)(((const double*)point_array)-1))
    : 0;
  return (point_capacity >= 3 && point_capacity <= ON_SubDFace::MaximumEdgeCount) ? point_capacity : 0;
}

ON_3dPoint* ON_SubDHeap::Allocate3dPointArray(size_t point_capacity)
{
  if (point_capacity <= 0 || point_capacity > ON_SubDFace::MaximumEdgeCount)
    return nullptr;
#if defined(ON_64BIT_RUNTIME)
  if (point_capacity < 5)
    point_capacity = 5; // maximize use of m_fsp17 chunks.
#endif
  const size_t a_capacity = 3 * point_capacity + 1;
  double* a = 
#if defined(ON_64BIT_RUNTIME)
    // when sizeof(void*) = sizeof(double) we can use the fast fixed size pool for faces with 5 or fewer edges.
    ( a_capacity*sizeof(a[0]) <= m_fsp17.SizeofElement() ) 
    ? (double*)this->m_fsp17.AllocateDirtyElement()
    :
#endif
    a = (double*)onmalloc(a_capacity * sizeof(a[0]));

  if (nullptr != a)
  {
    *((unsigned int*)a) = ((unsigned int)point_capacity);
    ++a;
  }
  return ((ON_3dPoint*)a);
}

void ON_SubDHeap::Return3dPointArray(class ON_3dPoint* point_array)
{
  const size_t point_capacity = ON_SubDHeap::Managed3dPointArrayCapacity(point_array);
  if (0 == point_capacity)
  {
    ON_SUBD_ERROR("point_array is not valid");
    return;
  }
  double* a = ((double*)point_array) - 1;
#if defined(ON_64BIT_RUNTIME)
  // when sizeof(void*) = sizeof(double) we can use the fast fixed size pool for faces with 5 or fewer edges.
  const size_t a_capacity = 3 * point_capacity + 1;
  if ( a_capacity * sizeof(a[0]) <= m_fsp17.SizeofElement() )
    this->m_fsp17.ReturnElement(a);
  else
#endif
    onfree(a);

  return;
}

bool ON_SubDHeap::GrowVertexEdgeArrayByOne(
  ON_SubDVertex* v
  )
{
  return GrowVertexEdgeArray(v,0);
}

bool ON_SubDHeap::GrowVertexFaceArrayByOne(
  ON_SubDVertex* v
  )
{
  return GrowVertexFaceArray(v,0);
}

bool ON_SubDHeap::GrowEdgeFaceArrayByOne(
  ON_SubDEdge* e
  )
{
  return GrowEdgeFaceArray(e,0);
}

bool ON_SubDHeap::GrowFaceEdgeArrayByOne(
  ON_SubDFace* f
  )
{
  return GrowFaceEdgeArray(f,0);
}

bool ON_SubDimple::GrowVertexEdgeArray(
  ON_SubDVertex* v,
  size_t capacity
  )
{
  return m_heap.GrowVertexEdgeArray(v,capacity);
}

bool ON_SubDimple::GrowVertexFaceArray(
  ON_SubDVertex* v,
  size_t capacity
  )
{
  return m_heap.GrowVertexFaceArray(v,capacity);
}

bool ON_SubDimple::GrowEdgeFaceArray(
  ON_SubDEdge* e,
  size_t capacity
  )
{
  return m_heap.GrowEdgeFaceArray(e,capacity);
}

bool ON_SubDimple::GrowFaceEdgeArray(
  ON_SubDFace* f,
  size_t capacity
  )
{
  return m_heap.GrowFaceEdgeArray(f,capacity);
}

bool ON_SubD::GrowVertexEdgeArray(
  ON_SubDVertex* v,
  size_t capacity
  )
{
  ON_SubDimple* subdimple = SubDimple(false);
  if ( nullptr == subdimple )
    return ON_SUBD_RETURN_ERROR(false);
  return subdimple->GrowVertexEdgeArray(v,capacity);
}

bool ON_SubD::GrowVertexFaceArray(
  ON_SubDVertex* v,
  size_t capacity
  )
{
  ON_SubDimple* subdimple = SubDimple(false);
  if ( nullptr == subdimple )
    return ON_SUBD_RETURN_ERROR(false);
  return subdimple->GrowVertexFaceArray(v,capacity);
}

bool ON_SubD::GrowEdgeFaceArray(
  ON_SubDEdge* e,
  size_t capacity
  )
{
  ON_SubDimple* subdimple = SubDimple(false);
  if ( nullptr == subdimple )
    return ON_SUBD_RETURN_ERROR(false);
  return subdimple->GrowEdgeFaceArray(e,capacity);
}

bool ON_SubD::GrowFaceEdgeArray(
  ON_SubDFace* f,
  size_t capacity
  )
{
  ON_SubDimple* subdimple = SubDimple(false);
  if ( nullptr == subdimple )
    return ON_SUBD_RETURN_ERROR(false);
  return subdimple->GrowFaceEdgeArray(f,capacity);
}

ON__UINT_PTR ON_SubDHeap::ArrayCapacity(
  size_t capacity,
  ON__UINT_PTR* a
  )
{
#if defined(ON_DEBUG)
  size_t acapacity = (nullptr == a) ? 0 : a[-1];
  if (capacity != acapacity)
  {
    ON_SubDIncrementErrorCount();
  }
#endif
  return (nullptr == a) ? 0 : a[-1];
}

bool ON_SubDHeap::ReturnVertexEdgeAndFaceArrays(
  ON_SubDVertex* v
  )
{
  if ( nullptr == v )
    return ON_SUBD_RETURN_ERROR(false);
  if (nullptr != v->m_edges || v->m_edge_capacity > 0 || v->m_edge_count > 0)
  {
    ReturnArray(v->m_edge_capacity,(ON__UINT_PTR*)v->m_edges);
    v->m_edges = nullptr;
    v->m_edge_capacity = 0;
    v->m_edge_count = 0;
  }
  if (nullptr != v->m_faces || v->m_face_capacity > 0 || v->m_face_count > 0)
  {
    ReturnArray(v->m_face_capacity,(ON__UINT_PTR*)v->m_faces);
    v->m_faces = nullptr;
    v->m_face_capacity = 0;
    v->m_face_count = 0;
  }
  return true;

}

bool ON_SubDHeap::ReturnEdgeExtraArray(
  ON_SubDEdge* e
  )
{
  if ( nullptr == e )
    return ON_SUBD_RETURN_ERROR(false);
  if (nullptr != e->m_facex || e->m_facex_capacity > 0)
  {
    ReturnArray(e->m_facex_capacity,(ON__UINT_PTR*)e->m_facex);
    e->m_facex = nullptr;
    e->m_facex_capacity = 0;
  }
  if (e->m_face_count > 2)
    e->m_face_count = 2;
  return true;
}

bool ON_SubDHeap::ReturnFaceExtraArray(
  ON_SubDFace* f
  )
{
  if ( nullptr == f )
    return ON_SUBD_RETURN_ERROR(false);
  if (nullptr != f->m_edgex || f->m_edgex_capacity > 0)
  {
    ReturnArray(f->m_edgex_capacity,(ON__UINT_PTR*)f->m_edgex);
    f->m_edgex = nullptr;
    f->m_edgex_capacity = 0;
  }
  if (f->m_edge_count > 4)
    f->m_edge_count = 4;
  return true;
}

ON__UINT_PTR* ON_SubDHeap::AllocateArray(size_t* capacity)
{
  ON__UINT_PTR* a;
  size_t requested_capacity = *capacity;
  if (requested_capacity <= 0)
    return nullptr;

  if (requested_capacity <= 4)
  {
    a = (ON__UINT_PTR*)m_fsp5.AllocateElement();
    *a++ = 4;
    *capacity = 4;
    return a;
  }

  if (requested_capacity <= 8)
  {
    a = (ON__UINT_PTR*)m_fsp9.AllocateElement();
    *a++ = 8;
    *capacity = 8;
    return a;
  }

  if (requested_capacity <= 16)
  {
    a = (ON__UINT_PTR*)m_fsp17.AllocateElement();
    *a++ = 16;
    *capacity = 16;
    return a;
  }

  return  AllocateOversizedElement(capacity);
}

void ON_SubDHeap::ReturnArray(
  size_t capacity,
  ON__UINT_PTR* a
  )
{
  if (nullptr != a && 0 == capacity)
  {
    ON_SubDIncrementErrorCount();
  }

  switch (ON_SubDHeap::ArrayCapacity(capacity,a))
  {
  case 0:
    break;
  case 4:
    m_fsp5.ReturnElement(a - 1);
    break;
  case 8:
    m_fsp9.ReturnElement(a - 1);
    break;
  case 16:
    m_fsp17.ReturnElement(a - 1);
    break;
  default:
    ReturnOversizedElement(capacity,a);
    break;
  }
  return;
}

bool ON_SubDHeap::Internal_InitializeLimitCurvesPool()
{
  if (0 == m_fsp_limit_curves.SizeofElement())
  {
    unsigned subd_edge_count = 0;
    // count edge and face to get an estimate of haow many mesh fragments we need to managed.
    ON_FixedSizePoolIterator fspeit(m_fspe);
    for (const void* p = fspeit.FirstElement(); nullptr != p; p = fspeit.NextElement())
    {
      const ON_SubDEdge* e = (const ON_SubDEdge*)p;
      if (false == e->IsActive())
        continue;
      ++subd_edge_count;
    }

    //const size_t sizeof_element = sizeof(ON_SubDEdgeSurfaceCurve);

    Internal_InitializeMeshFragmentPool(
      sizeof(ON_SubDEdgeSurfaceCurve),
      subd_edge_count,
      32,
      m_fsp_limit_curves
    );
  }
  return (m_fsp_limit_curves.SizeofElement() > 0);
}

bool ON_SubDHeap::Internal_InitializeFragmentCountEstimates(
  unsigned subd_display_density
)
{
  if (0 == m_full_fragment_display_density)
  {
    m_full_fragment_display_density 
      = subd_display_density > 0 
      ? (subd_display_density <= ON_SubDDisplayParameters::MaximumDensity ? subd_display_density : ON_SubDDisplayParameters::MaximumDensity)
      : 1U
      ;

    // Count the number of active faces and fragments needed to mesh them
    unsigned subd_face_count = 0;
    unsigned full_frag_count = 0;
    unsigned part_frag_count = 0;

    ON_FixedSizePoolIterator fspfit(m_fspf);
    for (const void* p = fspfit.FirstElement(); nullptr != p; p = fspfit.NextElement())
    {
      const ON_SubDFace* f = (const ON_SubDFace*)p;
      if (false == f->IsActive())
        continue;
      ++subd_face_count;
      if (4 == f->m_edge_count)
        ++full_frag_count; // one full fragment per quad
      else
        part_frag_count += f->m_edge_count; // n partial fragments per n-gon when n != 4
    }

    if (full_frag_count > 0 || part_frag_count > 0)
    {
      m_full_fragment_count_estimate = full_frag_count;
      m_part_fragment_count_estimate = part_frag_count;
    }
    else
    {
      m_full_fragment_count_estimate = 0;
      m_part_fragment_count_estimate = 0;
    }
  }

  return (m_full_fragment_display_density > 0 && m_full_fragment_display_density <= ON_SubDDisplayParameters::MaximumDensity);
}

bool ON_SubDHeap::Internal_InitializeMeshFragmentPool(
  size_t sizeof_element,
  size_t element_count_estimate,
  size_t min_fsp_2nd_block_element_count,
  ON_FixedSizePool& fsp // fsp references either m_fsp_*_fragments or m_fsp_limit_curves.
)
{
  if (0 == fsp.SizeofElement() && sizeof_element > 0)
  {
    ON_SleepLockGuard guard(fsp);
    fsp.CreateForExperts(sizeof_element, element_count_estimate, min_fsp_2nd_block_element_count);
    // check size again in case another thread beat this call
    if (0 == fsp.SizeofElement())
      fsp.CreateForExperts(sizeof_element, element_count_estimate, min_fsp_2nd_block_element_count);
  }
  return (fsp.SizeofElement() > 0);
}

ON_SubDMeshFragment* ON_SubDHeap::AllocateMeshFragment(
  unsigned subd_display_density,
  const ON_SubDMeshFragment& src_fragment
)
{
  if (subd_display_density > ON_SubDDisplayParameters::MaximumDensity)
    return ON_SUBD_RETURN_ERROR(nullptr);

  // When 4 == ON_SubDDisplayParameters::DefaultDensity (setting used in February 2019)
  // quads get a single fragment with a 16x16 face grid
  // N-gons with N != 4 get N 8x8 grids.

  // density = density of src_fragment
  const unsigned int density = (src_fragment.m_face_fragment_count > 1)
    ? ((subd_display_density > 0) ? (subd_display_density -1) : ON_UNSET_UINT_INDEX)
    : ((1==src_fragment.m_face_fragment_count) ? subd_display_density : ON_UNSET_UINT_INDEX)
    ;
  if (ON_UNSET_UINT_INDEX == density)
    return ON_SUBD_RETURN_ERROR(nullptr);
  const unsigned count = (unsigned)(sizeof(m_unused_fragments) / sizeof(m_unused_fragments[0]));
  if (density >= count)
    return ON_SUBD_RETURN_ERROR(nullptr);

  const unsigned short side_seg_count = (unsigned short)ON_SubDMeshFragment::SideSegmentCountFromDisplayDensity(density);
  const unsigned short vertex_capacity = (side_seg_count + 1)*(side_seg_count + 1);
  if ( src_fragment.VertexCount() > 0 && src_fragment.VertexCount() < ((unsigned)vertex_capacity) )
    return ON_SUBD_RETURN_ERROR(nullptr);

  if (0 == m_full_fragment_display_density)
  {
    // Lazy initialization of m_full_fragment_display_density is done because
    // we don't know the display density when SubDs are being constructed.
    if (false == Internal_InitializeFragmentCountEstimates(subd_display_density))
      return ON_SUBD_RETURN_ERROR(nullptr);
  }
  if (m_full_fragment_display_density <= 0 || m_full_fragment_display_density >= ON_SubDDisplayParameters::MaximumDensity)
    return ON_SUBD_RETURN_ERROR(nullptr);

  // In all common situations, bUseFullFragmentFSP or bUsePartFragmentFSP is true.
  const bool bUseFullFragmentFSP = (density == this->m_full_fragment_display_density);
  const bool bUsePartFragmentFSP = (density+1 == this->m_full_fragment_display_density);

  ON_FixedSizePool& fsp 
    = bUseFullFragmentFSP
    ? m_fsp_full_fragments
    : bUsePartFragmentFSP ? m_fsp_part_fragments : m_fsp_oddball_fragments;

  if (0 == fsp.SizeofElement())
  {
    // Lazy initialization of the fragment fixed size pools
    // is done so that we don't reserve pool memory that never gets used.

    const size_t sizeof_fragment
      = bUseFullFragmentFSP
      ? ON_SubDHeap::g_sizeof_fragment[m_full_fragment_display_density]
      : (bUsePartFragmentFSP ? ON_SubDHeap::g_sizeof_fragment[m_full_fragment_display_density - 1U] : ON_SubDHeap::g_sizeof_fragment[ON_SubDDisplayParameters::MaximumDensity])
      ;

    const size_t fragment_count_estimate
      = bUseFullFragmentFSP
      ? m_full_fragment_count_estimate
      : (bUsePartFragmentFSP ? m_part_fragment_count_estimate : ((unsigned)4U))
      ;

    const size_t min_fsp_2nd_block_element_count = (bUseFullFragmentFSP || bUsePartFragmentFSP) ? 32 : 1;

    if (false == this->Internal_InitializeMeshFragmentPool(
      sizeof_fragment,
      fragment_count_estimate,
      min_fsp_2nd_block_element_count,
      fsp
    ))
    {
      return ON_SUBD_RETURN_ERROR(nullptr);
    }
  }

  ON_SubDMeshFragment* fragment;
  {
    char* p = nullptr;
    char* p1 = nullptr;
    ON_SleepLockGuard guard(fsp);
    if (nullptr == m_unused_fragments[density])
    {
      p = (char*)fsp.AllocateDirtyElement();
      if (nullptr == p)
        return ON_SUBD_RETURN_ERROR(nullptr);
      p1 = p + fsp.SizeofElement();
      m_unused_fragments[density] = (ON_FixedSizePoolElement*)p;
      m_unused_fragments[density]->m_next = nullptr;
      const size_t sizeof_fragment = ON_SubDHeap::g_sizeof_fragment[density];
      for (p += sizeof_fragment; p + sizeof_fragment <= p1; p += sizeof_fragment)
      {
        // This loop is rarely executed.
        // It is used when an unusual small fragment is allocated from a pool
        // providing large fragments (fsp.SizeofElement() > sizeof_fragment).
        // If fsp.SizeofElement() is not an even multiple of sizeof_fragment,
        // then some memory is wasted. Because this situation is uncommon,
        // the waste doesn't matter in the big scheme of things.
        ON_FixedSizePoolElement* ele = (ON_FixedSizePoolElement*)p;
        ele->m_next = m_unused_fragments[density];
        m_unused_fragments[density] = ele;          
      }
    }
    fragment = (ON_SubDMeshFragment*)m_unused_fragments[density];
    m_unused_fragments[density] = m_unused_fragments[density]->m_next;
  }

  // NO // *fragment = src_fragment;
  *fragment = ON_SubDMeshFragment::Empty;
  fragment->m_prev_fragment = nullptr;
  fragment->m_next_fragment = nullptr;

  // NOTE WELL:
  //   fragment and fragment array memory are from a single fixed size pool allocation.
  fragment->Internal_LayoutArrays(vertex_capacity, (double*)(fragment + 1) );

  if (src_fragment.VertexCount() > 0)
    fragment->CopyFrom(src_fragment,density);

  return fragment;
}


ON_SubDMeshFragment* ON_SubDHeap::CopyMeshFragments(
  const ON_SubDFace* source_face,
  unsigned destination_subd_display_density,
  const ON_SubDFace* destination_face
)
{
  if (nullptr == source_face || nullptr == destination_face || nullptr != destination_face->m_mesh_fragments)
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON_SubDMeshFragment* prev_dst_fragment = nullptr;
  for (const ON_SubDMeshFragment* src_fragment = source_face->MeshFragments(); nullptr != src_fragment; src_fragment = src_fragment->m_next_fragment)
  {
    ON_SubDMeshFragment* dst_fragment = this->AllocateMeshFragment(destination_subd_display_density ,*src_fragment);
    dst_fragment->m_face = destination_face;
    if (prev_dst_fragment)
      prev_dst_fragment->m_next_fragment = dst_fragment;
    else
    {
      destination_face->m_mesh_fragments = dst_fragment;
      destination_face->Internal_SetSavedSurfacePointFlag(true);
    }
    prev_dst_fragment = dst_fragment;
  }
  return destination_face->m_mesh_fragments;
}


bool ON_SubDHeap::ReturnMeshFragment(ON_SubDMeshFragment * fragment)
{
  if (nullptr == fragment)
    return false;

  const size_t count = sizeof(m_unused_fragments) / sizeof(m_unused_fragments[0]);
  size_t i;
  switch (fragment->VertexCapacity())
  {
  case 2 * 2: // 1x1 mesh quad fragment
    i = 0;
    break;
  case 3 * 3: // 2x2 mesh quad fragment
    i = 1;
    break;
  case 5 * 5: // 4x4 mesh quad fragment
    i = 2;
    break;
  case 9 * 9: // 8x8 mesh quad fragment
    i = 3;
    break;
  case 17 * 17: // 16x16 mesh quad fragment
    i = 4;
    break;
  case 33 * 33: // 32x32 mesh quad fragment
    i = 5;
    break;
  case 65 * 65: // 64x64 mesh quad fragment
    i = 6;
    break;
  default:
    i = count;
    break;
  }
  if (i >= count)
    return ON_SUBD_RETURN_ERROR(false);

  ON_FixedSizePool& fsp 
    = (i == m_full_fragment_display_density) ? m_fsp_full_fragments
    : (i+1 == m_full_fragment_display_density) ? m_fsp_part_fragments : m_fsp_oddball_fragments;

  ON_FixedSizePoolElement* ele = (ON_FixedSizePoolElement*)fragment;
  ON_SleepLockGuard guard(fsp);
  ((unsigned int*)ele)[5] = 0; // zero m_vertex_count_etc and m_vertex_capacity_etc
  ele->m_next = m_unused_fragments[i];
  m_unused_fragments[i] = ele;

  return true;
}

bool ON_SubDHeap::ReturnMeshFragments(const ON_SubDFace * face)
{
  if (nullptr != face)
  {
    face->Internal_ClearSurfacePointFlag();
    ON_SubDMeshFragment* fragment = face->m_mesh_fragments;
    face->m_mesh_fragments = nullptr;
    while (nullptr != fragment)
    {
      if (face != fragment->m_face)
        return ON_SUBD_RETURN_ERROR(false);
      ON_SubDMeshFragment* next_fragment = fragment->m_next_fragment;
      if (false == ReturnMeshFragment(fragment))
        return false;
      fragment = next_fragment;
    }
  }
  return true;
}

class ON_SubDEdgeSurfaceCurve* ON_SubDHeap::AllocateEdgeSurfaceCurve(
  unsigned int cv_capacity
)
{
  if (cv_capacity < 1 || cv_capacity > ON_SubDEdgeSurfaceCurve::MaximumControlPointCapacity)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (0 == this->m_fsp_limit_curves.SizeofElement())
  {
    if( false == this->Internal_InitializeLimitCurvesPool())
      return ON_SUBD_RETURN_ERROR(nullptr);
  }

  ON_SubDEdgeSurfaceCurve* limit_curve = nullptr;
  double* cvx = nullptr;
  {
    ON_SleepLockGuard guard(m_fsp_limit_curves);
    limit_curve = (ON_SubDEdgeSurfaceCurve*)m_fsp_limit_curves.AllocateDirtyElement();
    if (cv_capacity > ON_SubDEdgeSurfaceCurve::MinimumControlPointCapacity)
      cvx = (double*)m_fsp_limit_curves.AllocateDirtyElement();
  }

  if (nullptr != limit_curve)
  {
    memset(limit_curve, 0, sizeof(*limit_curve));
    limit_curve->m_cv_capacity = ON_SubDEdgeSurfaceCurve::MinimumControlPointCapacity;
    if (nullptr != cvx)
    {
      // increase capacity
      limit_curve->m_cv_capacity = ON_SubDEdgeSurfaceCurve::MaximumControlPointCapacity;
      limit_curve->m_cvx = cvx;
      double* p1 = cvx + 3 * (ON_SubDEdgeSurfaceCurve::MaximumControlPointCapacity - ON_SubDEdgeSurfaceCurve::MinimumControlPointCapacity);
      while (cvx < p1)
        *cvx++ = ON_DBL_QNAN;
    }
  }

  return limit_curve;
}

ON_SubDEdgeSurfaceCurve* ON_SubDHeap::CopyEdgeSurfaceCurve(const ON_SubDEdge* source_edge, const ON_SubDEdge* desination_edge)
{
  if ( nullptr == desination_edge || source_edge == desination_edge)
    return ON_SUBD_RETURN_ERROR(nullptr);

  desination_edge->Internal_ClearSurfacePointFlag();
  if (source_edge->m_limit_curve == desination_edge->m_limit_curve)
    desination_edge->m_limit_curve = nullptr;
  else if (nullptr != desination_edge->m_limit_curve)
    desination_edge->m_limit_curve->m_cv_count = 0;

  if (nullptr == source_edge)
  {
    ReturnEdgeSurfaceCurve(desination_edge);
    return ON_SUBD_RETURN_ERROR(nullptr);
  }

  const ON_SubDEdgeSurfaceCurve* source_curve = source_edge->Internal_SurfacePointFlag() ? source_edge->m_limit_curve : nullptr;
  const unsigned char cv_count = (nullptr != source_curve) ? source_curve->m_cv_count : 0;
  if (0 == cv_count)
  {
    source_edge->Internal_ClearSurfacePointFlag();
    ReturnEdgeSurfaceCurve(desination_edge);
    return nullptr;
  }

  if (cv_count < 2 || cv_count > ON_SubDEdgeSurfaceCurve::MaximumControlPointCapacity || (cv_count > ON_SubDEdgeSurfaceCurve::MinimumControlPointCapacity && nullptr == source_curve->m_cvx))
  {
    source_edge->Internal_ClearSurfacePointFlag();
    ReturnEdgeSurfaceCurve(desination_edge);
    return ON_SUBD_RETURN_ERROR(nullptr);
  }

  ON_SubDEdgeSurfaceCurve* desination_curve = desination_edge->m_limit_curve;
  if (nullptr != desination_curve && desination_curve->m_cv_capacity < cv_count)
  {
    ReturnEdgeSurfaceCurve(desination_edge);
    desination_curve = nullptr;
  }
  if (nullptr == desination_curve)
  {
    desination_curve = this->AllocateEdgeSurfaceCurve(cv_count);
    if (nullptr == desination_curve)
      return ON_SUBD_RETURN_ERROR(nullptr);
    if (desination_curve->m_cv_capacity < cv_count)
    {
      ReturnEdgeSurfaceCurve(desination_curve);
      return ON_SUBD_RETURN_ERROR(nullptr);
    }
  }
  const size_t sz9 = sizeof(desination_curve->m_cv9);
  memcpy(desination_curve->m_cv9, source_curve->m_cv9, sz9);
  if (cv_count > ON_SubDEdgeSurfaceCurve::MinimumControlPointCapacity && nullptr != desination_curve->m_cvx && nullptr != source_curve->m_cvx)
  {
    const size_t szx = ((size_t)(cv_count - ON_SubDEdgeSurfaceCurve::MinimumControlPointCapacity)) * 24;
    memcpy(desination_curve->m_cvx, source_curve->m_cvx, szx);
  }
  desination_curve->m_cv_count = cv_count;
  desination_edge->m_limit_curve = desination_curve;
  desination_edge->Internal_SetSavedSurfacePointFlag(true);
  return desination_curve;
}

bool ON_SubDHeap::ReturnEdgeSurfaceCurve(
  ON_SubDEdgeSurfaceCurve* limit_curve
)
{
  if (nullptr != limit_curve)
  {
    // zero cv_count and cv_capacity - to limit crashes caused by rogue references
    limit_curve->m_cv_count = 0;
    limit_curve->m_cv_capacity = 0;
    ON_FixedSizePoolElement* ele0 = (ON_FixedSizePoolElement*)limit_curve;
    ON_FixedSizePoolElement* ele1 = (ON_FixedSizePoolElement*)limit_curve->m_cvx;
    if (nullptr != ele1)
    {
      // zero cv_count and cv_capacity - to limit crashes caused by rogue references
      ((ON_SubDEdgeSurfaceCurve*)ele1)->m_cv_count = 0;
      ((ON_SubDEdgeSurfaceCurve*)ele1)->m_cv_capacity = 0;
    }
    ON_SleepLockGuard guard(m_fsp_limit_curves);
    m_fsp_limit_curves.ReturnElement(ele0);
    if (nullptr != ele1)
      m_fsp_limit_curves.ReturnElement(ele1);
  }
  return true;
}

bool ON_SubDHeap::ReturnEdgeSurfaceCurve(
  const class ON_SubDEdge* edge
)
{
  bool rc = true;
  ON_SubDEdgeSurfaceCurve* limit_curve = (nullptr != edge) ? edge->m_limit_curve : nullptr;
  if (nullptr != limit_curve)
  {
    edge->Internal_ClearSurfacePointFlag();
    edge->m_limit_curve = nullptr;
    rc = ReturnEdgeSurfaceCurve(limit_curve);
  }
  return rc;
}
