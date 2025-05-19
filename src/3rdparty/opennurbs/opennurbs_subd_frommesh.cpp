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

class ON_MeshNGonEdge
{
public:
  // In ON_Mesh to ON_SubD, there is a ON_MeshNGonEdge for each mesh ngon edge.
  // So, for an interior edge, there will be 2 ON_MeshNGonEdge values, one
  // for each attached ngon.
  // Sorting ON_MeshNGonEdge by m_u.mesh_edge_id will group the these
  // edges together.
  static const ON_MeshNGonEdge Unset;
  static const ON_MeshNGonEdge Create(
    unsigned candidate_subd_face_id,
    unsigned mesh_Vi, 
    unsigned mesh_Vj,
    const unsigned int* mesh_point_id
  );

  const ON_MeshNGonEdge Reversed() const
  {
    if (IsSet())
    {
      ON_MeshNGonEdge e = *this;

      e.m_mesh_Vi = m_mesh_Vj;
      e.m_mesh_Vj = m_mesh_Vi;

      if (2 == m_u_status)
      {
        e.m_u.subd_edgeptr = m_u.subd_edgeptr.Reversed();
      }

      return e;
    }
    return ON_MeshNGonEdge::Unset;
  }

  static int CompareMeshEdgeTopologyId(const void* lhs, const void* rhs);

  /*
  Returns:
    True if a and b reference the same topological edge and the normals
    at both ends of the edge are different
  */
  static bool TagEdgeAsCrease(
    const ON_MeshNGonEdge& a,
    const ON_MeshNGonEdge& b,
    const unsigned int* mesh_point_id
  );

  const ON_2udex PointIds(
    const unsigned int* mesh_point_id
  ) const
  {
    return (nullptr != mesh_point_id) ? ON_2udex(mesh_point_id[m_mesh_Vi], mesh_point_id[m_mesh_Vj]) : ON_2udex::Zero;
  }


  unsigned int m_sud_face_id; // likely ON_SubDFace.m_id value (unless invalid input causes some to be skipped)
  unsigned int m_mesh_Vi; // ON_Mesh vertex index
  unsigned int m_mesh_Vj; // ON_Mesh vertex index

private:
  unsigned char m_u_status; // 0 = u is unset, 1 = m_u.mesh_edge_topology_id is set, 2 = m_u.subd_edgeptr is set
  union
  {
    ON_2udex mesh_edge_topology_id; // uniquely identifies mesh edge topologically - independent of vertex order
    ON_SubDEdgePtr subd_edgeptr;
  } m_u;

public:

  const ON_2udex EdgeTopologyId() const
  {
    return 1 == m_u_status ? m_u.mesh_edge_topology_id : ON_2udex::Zero;
  }

  const ON_SubDEdgePtr EdgePtr() const
  {
    return 2 == m_u_status ? m_u.subd_edgeptr : ON_SubDEdgePtr::Null;
  }

  bool SetEdgePtr(ON_SubDEdgePtr eptr)
  {
    if (1 == m_u_status)
    {
      m_u_status = eptr.IsNull() ? 0 : 2;
      m_u.subd_edgeptr = eptr;
      return true;
    }
    return ON_SUBD_RETURN_ERROR(false);
  }

  bool IsSet() const
  {
    return 0 != m_u_status;
  }

};

static ON_MeshNGonEdge Internal_CreateUnsetMeshNGonEdge()
{
  ON_MeshNGonEdge unset;
  memset(&unset, 0, sizeof(unset));
  return unset;
}

const ON_MeshNGonEdge ON_MeshNGonEdge::Unset = Internal_CreateUnsetMeshNGonEdge();

const ON_MeshNGonEdge ON_MeshNGonEdge::Create(
  unsigned candidate_sud_face_id,
  unsigned mesh_Vi,
  unsigned mesh_Vj,
  const unsigned int* mesh_point_id
)
{
  for(;;)
  {
    if (candidate_sud_face_id <= 0)
      break;
    if (mesh_Vi == mesh_Vj)
      break;
    ON_MeshNGonEdge e = ON_MeshNGonEdge::Unset;
    const unsigned a = mesh_point_id[mesh_Vi];
    const unsigned b = mesh_point_id[mesh_Vj];
    if (a < b)
    {
      e.m_u.mesh_edge_topology_id.i = a;
      e.m_u.mesh_edge_topology_id.j = b;
      e.m_u_status = 1;
    }
    else if (a > b)
    {
      e.m_u.mesh_edge_topology_id.i = b;
      e.m_u.mesh_edge_topology_id.j = a;
      e.m_u_status = 1;
    }
    else
      break;
    e.m_mesh_Vi = mesh_Vi;
    e.m_mesh_Vj = mesh_Vj;
    e.m_sud_face_id = candidate_sud_face_id;
    return e;
  }
  return ON_SUBD_RETURN_ERROR(ON_MeshNGonEdge::Unset);
}



int ON_MeshNGonEdge::CompareMeshEdgeTopologyId(const void* lhs, const void* rhs)
{
  // compare location ids
  const ON_2udex lhs_edge_topology_id = ((const ON_MeshNGonEdge*)lhs)->EdgeTopologyId();
  const ON_2udex rhs_edge_topology_id = ((const ON_MeshNGonEdge*)rhs)->EdgeTopologyId();

  if (lhs_edge_topology_id.i < rhs_edge_topology_id.i)
    return -1;
  if (lhs_edge_topology_id.i > rhs_edge_topology_id.i)
    return 1;

  if (lhs_edge_topology_id.j < rhs_edge_topology_id.j)
    return -1;
  if (lhs_edge_topology_id.j > rhs_edge_topology_id.j)
    return 1;

  return 0;
}

bool ON_MeshNGonEdge::TagEdgeAsCrease(
  const ON_MeshNGonEdge& a,
  const ON_MeshNGonEdge& b,
  const unsigned int* mesh_point_id
  )
{
  if (1 != a.m_u_status || 1 != b.m_u_status 
    || a.m_u.mesh_edge_topology_id.i != b.m_u.mesh_edge_topology_id.i 
    || a.m_u.mesh_edge_topology_id.j != b.m_u.mesh_edge_topology_id.j
    )
  {
    // a and b should currently have equal topology ids
    return ON_SUBD_RETURN_ERROR(false);
  }

  const bool bFlipA = (a.m_u.mesh_edge_topology_id.i != mesh_point_id[a.m_mesh_Vi]) ? true : false;
  const bool bFlipB = (b.m_u.mesh_edge_topology_id.i != mesh_point_id[b.m_mesh_Vi]) ? true : false;

  if (bFlipA == bFlipB)
  {
    // a and b have the same direction
    if (a.m_mesh_Vi != b.m_mesh_Vi && a.m_mesh_Vj != b.m_mesh_Vj)
      return true; // ON_Mesh vertex indices are different at both ends
  }
  else
  {
    // a and b have opposite directions
    if (a.m_mesh_Vi != b.m_mesh_Vj && a.m_mesh_Vj != b.m_mesh_Vi)
      return true; // ON_Mesh vertex indices are different at both ends
  }

  return false;
}

static bool Internal_CandidateTagIsBetterCreaseEnd(
  ON_SubDVertexTag current_tag,
  const ON_SubDVertex* candidate
)
{
  if (nullptr == candidate)
    return false;
  switch(current_tag)
  {
  case ON_SubDVertexTag::Unset:
    if (ON_SubDVertexTag::Unset != candidate->m_vertex_tag )
      return true;
    break;
  case ON_SubDVertexTag::Smooth:
    if (candidate->IsDartOrCreaseOrCorner())
      return true;
    break;
  case ON_SubDVertexTag::Dart:
    if (candidate->IsCreaseOrCorner())
      return true;
    break;
  case ON_SubDVertexTag::Crease:
    if (candidate->IsCorner())
      return true;
    break;
  case ON_SubDVertexTag::Corner:
    break;
  default:
    break;
  }
  return false;
}

static bool Internal_CreateFromMesh_ValidateNonmanifoldVertexSector(
  const ON_SubDVertex* v,
  const ON_SubDEdge* e,
  ON_SubDSectorIterator& sit
)
{
  // e is non manifold edge
  // v = nonmanifold corner vertex on e
  // sit is a sector of v with e as a starting boundary
  if (nullptr == v || v != sit.CenterVertex() || e != sit.CurrentEdge(0))
    return false;

  // k is used to protect against infinite looping if the topology
  // around v is invalid.
  const ON_SubDEdge* other_crease = nullptr;
  const ON_SubDEdge* best_candidate_edge = nullptr;
  const ON_SubDVertex* best_canditate_v1 = nullptr;
  const ON_3dVector dir = -e->ControlNetDirectionFrom(v);
  double best_dot = ON_DBL_QNAN;
  for (unsigned short k = 0; k <= v->m_face_count; ++k)
  {
    const ON_SubDEdge* e1 = sit.CurrentEdge(1);
    if (e1->IsCrease())
    {
      other_crease = e1;
      break;
    }
    const ON_SubDVertex* v1 = e1->OtherEndVertex(v);
    if (nullptr == v1)
    {
      ON_SUBD_ERROR("invalid SubD topology.");
      return false; // invalid topology
    }
    const double d = dir * e1->ControlNetDirectionFrom(v);
    if (
      nullptr == best_candidate_edge
      || Internal_CandidateTagIsBetterCreaseEnd(best_canditate_v1->m_vertex_tag,v1)
      || (nullptr != best_candidate_edge && best_canditate_v1->m_vertex_tag == v1->m_vertex_tag && d > best_dot)
      )
    {
      best_candidate_edge = e1;
      best_dot = d;
      best_canditate_v1 = v1;
    }
    if (nullptr == sit.NextFace(ON_SubDSectorIterator::StopAt::AnyCrease))
      break;
  }

  if (nullptr == other_crease)
  {
    ON_SUBD_ERROR("bug in nonmanifold mesh to SubD code.");
    return false;
  }
  if (other_crease != e)
    return true; // this sector is a valid corner vertex sector.

  if (nullptr == best_candidate_edge)
  {
    ON_SUBD_ERROR("bug in nonmanifold mesh to SubD code.");
    return false;
  }

  // make  best_candidate_edge a crease so corner sector is valid
  const_cast<ON_SubDEdge*>(best_candidate_edge)->m_edge_tag = ON_SubDEdgeTag::Crease;
  const ON_SubDVertexEdgeProperties best_ep = best_canditate_v1->EdgeProperties();

  ON_SubDVertexTag vtag;
  if ( 1 == best_ep.m_crease_edge_count && 2 == best_ep.m_min_edge_face_count && 2 == best_ep.m_max_edge_face_count)
    vtag = ON_SubDVertexTag::Dart;
  else if ( 2 == best_ep.m_crease_edge_count && best_ep.m_max_edge_face_count <= 2 )
    vtag = ON_SubDVertexTag::Crease;
  else
    vtag = ON_SubDVertexTag::Corner;

  if (false == Internal_CandidateTagIsBetterCreaseEnd(vtag, best_canditate_v1))
    const_cast<ON_SubDVertex*>(best_canditate_v1)->m_vertex_tag = vtag;

  return true;
}

static void Internal_CreateFromMesh_ValidateNonmanifoldVertex(
  const ON_SubDVertex* v
)
{
  if (
    nullptr == v
    || ON_SubDVertexTag::Corner != v->m_vertex_tag
    )
    return;

  for (unsigned short vei = 0; vei < v->m_edge_count; ++vei)
  {
    const ON_SubDEdge* e = v->Edge(vei);
    if (
      nullptr == e
      || ON_SubDEdgeTag::Crease != e->m_edge_tag
      || e->m_face_count <= 2
      )
      continue;
    // e is non manifold - verify every attached face has a valid corner sector
    for (unsigned short efi = 0; efi < e->m_face_count; ++efi)
    {
      const ON_SubDFace* f = e->Face(efi);
      if (nullptr == f)
        continue;
      ON_SubDSectorIterator sit;
      sit.Initialize(f, 0, v);
      if (e != sit.CurrentEdge(0))
      {
        sit.Initialize(f, 1, v);
        if (e != sit.CurrentEdge(0))
        {
          ON_SUBD_ERROR("bug in nonmanifold mesh to SubD code.");
          continue;
        }
      }
      Internal_CreateFromMesh_ValidateNonmanifoldVertexSector(v,e,sit);
      // convert best_candidate to a crease to make this a valid corner sector;
    }
  }

  return;
}

class ON_NgonBoundaryChecker
{
public:
  /*
  Parameters:
    ngon  - [in]
      ngon to test
    mesh [in]
      mesh that ngon is a part of
    bMustBeOriented - [in]
      If true, the faces in the ngon must be compatibly oriented
  */
  bool IsSimpleNgon(
    const class ON_MeshNgon* ngon,
    const class ON_Mesh* mesh,
    bool bMustBeOriented
  );

  enum : unsigned int
  {
    HashTableSize = 256
  };

private:
  void Internal_Reset();
  class ON_NgonBoundaryComponent* Internal_AddVertex(unsigned int vertex_index);
  class ON_NgonBoundaryComponent* Internal_AddEdge(unsigned int vertex_index0, unsigned int vertex_index1, bool bMustBeOriented);
  static unsigned int Internal_VertexHashIndex(unsigned int vertex_index);
  static unsigned int Internal_EdgeHashIndex(unsigned int vertex_index0, unsigned int vertex_index1);
  void Internal_InitialzeFixedSizePool();

  void Internal_ReturnIsNotSimple();

  // m_fsp manages the memory used for boundary components.
  ON_FixedSizePool m_fsp;
  class ON_NgonBoundaryComponent* m_hash_table[ON_NgonBoundaryChecker::HashTableSize] = {};
  unsigned m_vertex_count = 0;
  unsigned m_edge_count = 0;
  bool m_bIsSimple = false;
  bool m_bIsNotSimple = false;
};

ON_SubD* ON_SubD::CreateFromMesh(
  const class ON_Mesh* level_zero_mesh,
  const class ON_SubDFromMeshParameters* from_mesh_options,
  ON_SubD* subd
)
{
  ON_Mesh* local_copy = nullptr;
  if (nullptr != level_zero_mesh)
  {
    // remove ngons with holes and other damaged ngons so the underlying faces get used.

    ON_NgonBoundaryChecker bc;
    const bool bMustBeOrientedNgon = false;

    const unsigned ngon_count = level_zero_mesh->NgonUnsignedCount();
    ON_SimpleArray<unsigned> ngons_with_holes(ngon_count);
    for (unsigned ni = 0; ni < ngon_count; ++ni)
    {
      const class ON_MeshNgon* ngon = level_zero_mesh->Ngon(ni);
      if ( nullptr == ngon)
        continue;
      if (ngon->m_Vcount < 3 || ngon->m_Fcount <= 1)
        continue;
      if ( false == bc.IsSimpleNgon(ngon, level_zero_mesh,bMustBeOrientedNgon) )
        ngons_with_holes.Append(ni);
    }

    for (;;)
    {
      if (0 == ngons_with_holes.UnsignedCount())
        break;
      local_copy = new ON_Mesh(*level_zero_mesh);
      if (nullptr == local_copy)
        break;
      if (ngon_count != local_copy->NgonUnsignedCount())
        break;
      const unsigned removed_count = local_copy->RemoveNgons(ngons_with_holes.UnsignedCount(), ngons_with_holes.Array());
      if (removed_count > 0)
        level_zero_mesh = local_copy;
      break;
    }
  }

  ON_SubD* subd_from_mesh = Internal_CreateFromMeshWithValidNgons(level_zero_mesh, from_mesh_options, subd);
  if (nullptr != local_copy)
    delete local_copy;
  return subd_from_mesh;
}

static double Internal_FaceCornerAngleRadians(const ON_SubDVertex* v, const ON_SubDFace* f)
{
  for (;;)
  {
    if (nullptr == f)
      break;

    if (false == f->IsConvex())
      break;

    // We could remove the f->IsConvex() test, but it might make make a bad situation worse.
    // As of May 2020, nobody has complained about this approach.
    // the code below assumes the face is convex

    const unsigned fvi = f->VertexIndex(v);
    const ON_SubDComponentPtrPair pair = f->VertexEdgePair(fvi);
    if (false == pair.BothAreNotNull())
      break;
    const double a = ON_SubDSectorType::CornerSectorAngleRadiansFromEdges(pair.First().EdgePtr().Reversed(), pair.Second().EdgePtr());
    if (false == (a > 0.0 && a < ON_PI))
      break;
    return a;
  }
  return ON_DBL_QNAN;
}

ON_SubD* ON_SubD::Internal_CreateFromMeshWithValidNgons(
  const class ON_Mesh* mesh,
  const class ON_SubDFromMeshParameters* from_mesh_options,
  ON_SubD* subd
  )
{
  if (nullptr != subd)
  {
    ON_SubDimple* subdimple = subd->SubDimple(false);
    if (nullptr != subdimple)
      subdimple->Clear();
  }

  if (nullptr == mesh)
    return nullptr;

  ON_Workspace ws;

  if (nullptr == from_mesh_options)
    from_mesh_options = &ON_SubDFromMeshParameters::Smooth;

  ON_3dPointListRef mesh_points(mesh);
  const unsigned mesh_point_count = mesh_points.PointCount();
  if (mesh_point_count < 3)
    return nullptr;

  const ON_MeshFaceList mesh_face_list(mesh);
  const unsigned int mesh_face_count = mesh_face_list.FaceCount();
  if ( mesh_face_count < 1 )
    return nullptr;

  const_cast<ON_Mesh*>(mesh)->NgonMap(true);
  ON_MeshNgonIterator ngonit(mesh);
  if (nullptr == ngonit.FirstNgon())
    return nullptr;
  
  ////////////////////////////////////////////////////////////////////////////////////////
  //
  // Conceptually sort the vertices of mesh into groups that are at the same 3d location.
  // For each group of mesh vertices at a particular spot, there will typically be
  // one SubD vertex. However, mesh vertices that are not referenced by mesh faces
  // are ignored so it is possible that some mesh vertices will not have a corresponding 
  // SubD vertex.
  //
  // mesh_point_count = mesh->MeshVertexCount();
  // mesh_point_id[]
  //   mesh_point_id[] has mesh_point_count values.
  //   mesh_point_id[i] = mesh_point_id[j] if and only if mesh->m_V[i] and mesh->m_V[j] are coincident.
  //   Values in mesh_point_id[] run from 0 to mesh_point_id_count-1.
  //   There are mesh_point_id_count unique locations.
  // mesh_point_map[] is a permutation of (0, ..., mesh_point_count-1).
  //   mesh_point_map[] sorts mesh->m_V[] into groups of vertices with the same mesh_id / location.
  //   0 == mesh_point_id[mesh_point_map[0]] <= ... <= mesh_point_id[mesh_point_map[mesh_point_count-1]] = mesh_point_id_count-1.
  // mesh_vertex_status[] mesh_point_id_count char values.
  //   mesh_vertex_status[mesh_vi] = 1 if that mesh vertex id/location has a corresponding SubD vertex. 0 if the mesh vertex will be ignored.
  unsigned int* buffer1 = (unsigned int*)ws.GetIntMemory(mesh_point_count);
  const unsigned int* mesh_point_id = mesh->GetVertexLocationIds(0, (unsigned int*)ws.GetIntMemory(mesh_point_count), buffer1);
  if (nullptr == mesh_point_id)
    return nullptr;
  const unsigned int* mesh_point_map = buffer1;

  // mesh_point_id_count = number of unique vertex locations in mesh->m_V[] array.
  const unsigned mesh_point_id_count = mesh_point_id[mesh_point_map[mesh_point_count - 1]] + 1;

  unsigned char* mesh_vertex_status = (unsigned char*)ws.GetMemory(mesh_point_id_count*sizeof(mesh_vertex_status[0]));
  memset(mesh_vertex_status, 0, mesh_point_id_count*sizeof(mesh_vertex_status[0]));

  ON_SubDFromMeshParameters::InteriorCreaseOption crease_test 
    = (nullptr != from_mesh_options)
    ? from_mesh_options->GetInteriorCreaseOption()
    : ON_SubDFromMeshParameters::InteriorCreaseOption::None;

  if (ON_SubDFromMeshParameters::InteriorCreaseOption::AtMeshDoubleEdge != crease_test)
  {
    crease_test = ON_SubDFromMeshParameters::InteriorCreaseOption::None;
  }
    
  ////////////////////////////////////////////////////////////////////////////////////////
  //
  // Get mesh edge list
  // 
  unsigned int subd_vertex_count = 0;
  unsigned int mesh_edge_count = 0;
  unsigned int max_subd_face_edge_count = 0;
  ON_SimpleArray<ON_MeshNGonEdge> mesh_edges(4 * mesh->m_F.UnsignedCount());

  unsigned int quad_vi[4];
  ON_MeshNGonEdge quad_edges[4] = {};

  bool bMergeColinearEdges = false;

  unsigned int subd_face_count = 0;
  unsigned int mesh_Vi;
  unsigned int mesh_Vj;
  for (const ON_MeshNgon* ngon = ngonit.FirstNgon(); nullptr != ngon; ngon = ngonit.NextNgon())
  {
    if (ngon->m_Vcount < 3 || ngon->m_Fcount < 1)
      continue;

    const int ngon_orientation = ngon->Orientation(mesh_face_list, false);

    if (0 != ngon_orientation)
    {
      unsigned int ngon_edge_count = 0;
      mesh_Vj = ngon->m_vi[0];
      for (unsigned int nvi = 1; nvi <= ngon->m_Vcount; nvi++)
      {
        mesh_Vi = mesh_Vj;
        mesh_Vj = ngon->m_vi[nvi % ngon->m_Vcount];
        if (mesh_point_id[mesh_Vi] == mesh_point_id[mesh_Vj])
          continue; // coincident vertex locations
        ON_MeshNGonEdge& mesh_edge = mesh_edges.AppendNew();
        mesh_edge = ON_MeshNGonEdge::Create(subd_face_count+1, mesh_Vi, mesh_Vj, mesh_point_id);
        if (mesh_edge.IsSet())
        {

          ngon_edge_count++;
          continue;
        }
        ngon_edge_count = 0;
        break;
      }
      if (ngon_edge_count < 3)
      {
        mesh_edges.SetCount(mesh_edge_count);
        continue;
      }

      if (ngon_orientation < 0)
      {
        // ngon and mesh have opposite orientations - mesh orientation wins
        // reverese edges
        unsigned int i0 = mesh_edge_count;
        unsigned int i1 = mesh_edge_count + ngon_edge_count - 1;
        while (i0 < i1)
        {
          const ON_MeshNGonEdge mesh_edge = mesh_edges[i0];
          mesh_edges[i0] = mesh_edges[i1].Reversed();
          mesh_edges[i1] = mesh_edge.Reversed();
          i0++;
          i1--;
        }
        // Flip middle edge if odd number of edges
        if (i0 == i1)
          mesh_edges[i0] = mesh_edges[i0].Reversed();
      }

      // the ngon created a single subd face
      ++subd_face_count;

      if (ngon_edge_count >= 4)
        bMergeColinearEdges = true;

      if (mesh_edges.UnsignedCount() - mesh_edge_count > max_subd_face_edge_count)
        max_subd_face_edge_count = mesh_edges.UnsignedCount() - mesh_edge_count;
    }
    else if ( ngon->m_Fcount >= 1 )
    {
      // This generally happens when the "ngon" has holes and it cannot be used as a subd control net polygon.
      //
      // Each tri or quad in the ngon will get added as a subd face.
      for (unsigned int nfi = 0; nfi < ngon->m_Fcount; nfi++)
      {
        if ( nullptr == mesh_face_list.QuadFvi(ngon->m_fi[nfi],quad_vi))
          continue;

        unsigned int quad_edge_count = 0;        
        mesh_Vj = quad_vi[0];
        for (unsigned int fvi = 1; fvi <= 4; fvi++)
        {
          mesh_Vi = mesh_Vj;
          mesh_Vj = quad_vi[fvi % 4];
          if (mesh_point_id[mesh_Vi] == mesh_point_id[mesh_Vj])
            continue; // coincident vertex locations (always happens on a tri face and can happen on invalid faces)
          quad_edges[quad_edge_count] = ON_MeshNGonEdge::Create(subd_face_count+1, mesh_Vi, mesh_Vj, mesh_point_id);
          if (quad_edges[quad_edge_count].IsSet())
          {
            ++quad_edge_count;
            continue;
          }
          quad_edge_count = 0;
          break;
        }
        if (quad_edge_count >= 3)
        {
          // each quad/triangle in the ON_Mesh ngon created a subd face
          mesh_edges.Append(quad_edge_count,quad_edges);
          ++subd_face_count;
          if( quad_edge_count > max_subd_face_edge_count)
            max_subd_face_edge_count = quad_edge_count;
        }
      }

      if ( mesh_edge_count == mesh_edges.UnsignedCount() )
        continue;
    }


    for (/*empty init*/; mesh_edge_count < mesh_edges.UnsignedCount(); mesh_edge_count++)
    {
      const ON_MeshNGonEdge& mesh_edge = mesh_edges[mesh_edge_count];
      if (0 == mesh_vertex_status[mesh_point_id[mesh_edge.m_mesh_Vi]])
      {
        mesh_vertex_status[mesh_point_id[mesh_edge.m_mesh_Vi]] = 1;
        subd_vertex_count++;
      }
      if (0 == mesh_vertex_status[mesh_point_id[mesh_edge.m_mesh_Vj]])
      {
        mesh_vertex_status[mesh_point_id[mesh_edge.m_mesh_Vj]] = 1;
        subd_vertex_count++;
      }
    }
  }

  if (subd_vertex_count < 3 || mesh_edge_count < 3 || subd_face_count < 1)
    return nullptr;
    
  std::unique_ptr<ON_SubD> uptr;
  ON_SubD* new_subd = nullptr;
  if (subd)
  {
    new_subd = subd;
  }
  else
  {
    uptr = std::make_unique<ON_SubD>();
    new_subd = uptr.get();
  }

  // Make sure the subdimple is created before adding components.
  if (nullptr == new_subd->SubDimple(true))
    return nullptr;

  bool bHasTaggedVertices = false;
  bool bHasNonmanifoldCornerVertices = false;

  //////////////////////////////////////////////////////////////////////
  //
  // create subd vertices
  //
  // subd_V[mesh_vi] = subd vertex that corresponds to mesh->m_V[].
  // Note that when mesh-m_V[i] and mesh->m_V[j] are the same point, 
  // then subd_V[i] = subd_V[j]. 
  // This is common and it happens when mesh_point_id_count < mesh_point_count
  // (some distinct mesh points in the mesh->m_V[] array have the same location).
  ON_SubDVertex** subd_V = (ON_SubDVertex**)ws.GetMemory(mesh_point_count * sizeof(subd_V[0]));
  memset(subd_V, 0, mesh_point_count * sizeof(subd_V[0]));
  for (unsigned int i = 0; i < mesh_point_count;/*empty iterator*/)
  {
    const unsigned int vid0 = mesh_point_id[mesh_point_map[i]];
    if (0 == mesh_vertex_status[vid0])
    {
      // no edges reference this vertex.
      ++i;
      continue;
    }

    unsigned int j;
    for (j = i + 1; j < mesh_point_count; j++)
    {
      if (vid0 != mesh_point_id[mesh_point_map[j]])
        break;
    }

    const ON_3dPoint P = mesh_points[mesh_point_map[i]];
    ON_SubDVertex* subd_vertex = new_subd->AddVertex(ON_SubDVertexTag::Smooth, &P.x);
    while (i < j)
      subd_V[mesh_point_map[i++]] = subd_vertex;
  }


  ////////////////////////////////////////////////////////////////////////
  //
  // If we are adding interior crease, set the mesh_edge_ref.m_mesh_Ni / m_mesh_Nj values used to detect creases.
  //
  if ( ON_SubDFromMeshParameters::InteriorCreaseOption::AtMeshDoubleEdge != crease_test )
  {
    crease_test = ON_SubDFromMeshParameters::InteriorCreaseOption::None;
  }

  //////////////////////////////////////////////////////////////////////
  //
  // Create SubD edges.
  // 
  // An subd interior edge will have 2 consecutive element in mesh_edges[].
  // A subd non-manifold edge with k faces with have k consecutive element in mesh_edges[].
  // A subd boundary edge will have 1 element in mesh_edges[].
  // A subd wire edge will have 1 element in mesh_edges[].
  //

  // mesh_edge_map[] is used to sort the sort mesh_edges[] into groups that correspond to the same SubD edge.
  // The order of mesh_edges[] cannot be changed because the current order is needed to efficiently create the SubD faces.
  unsigned int* mesh_edge_map = (unsigned int*)ws.GetMemory(mesh_edges.UnsignedCount() * sizeof(mesh_edge_map[0]));
  ON_Sort(
    ON::sort_algorithm::quick_sort,
    mesh_edge_map, mesh_edges.Array(),
    mesh_edges.UnsignedCount(),
    sizeof(ON_MeshNGonEdge),
    ON_MeshNGonEdge::CompareMeshEdgeTopologyId
  );

  for (unsigned int i = 0; i < mesh_edges.UnsignedCount(); /*empty iterator*/)
  {
    const ON_MeshNGonEdge& mesh_edge0 = mesh_edges[mesh_edge_map[i]];
    const ON_2udex topology_id0 = mesh_edge0.EdgeTopologyId();

    // get the group of mesh_edges[] that will use the same SubD edge.
    // and determine if that edge should be tagged as a crease.
    ON_SubDEdgeTag edge_tag = ON_SubDEdgeTag::Smooth;
    unsigned j = i + 1;
    for (/*empty init*/; j < mesh_edges.UnsignedCount(); ++j)
    {
      ON_MeshNGonEdge& mesh_edge1 = mesh_edges[mesh_edge_map[j]];
      const ON_2udex topology_id1 = mesh_edge1.EdgeTopologyId();
      if (topology_id0.i != topology_id1.i || topology_id0.j != topology_id1.j)
        break;
      if (ON_SubDFromMeshParameters::InteriorCreaseOption::None != crease_test)
      {
        if (ON_MeshNGonEdge::TagEdgeAsCrease(mesh_edge0, mesh_edge1, mesh_point_id))
          edge_tag = ON_SubDEdgeTag::Crease;
      }
    }
    if ( j-i != 2 )
      edge_tag = ON_SubDEdgeTag::Crease; // wire, boundary, or non-manifold edge

    // create the SubD edge.
    ON_SubDVertex* v0[2] = { subd_V[mesh_edge0.m_mesh_Vi],  subd_V[mesh_edge0.m_mesh_Vj] };
    ON_SubDEdge* e
      = (nullptr != v0[0] && nullptr != v0[1] && v0[0]->m_id != v0[1]->m_id)
      ? new_subd->AddEdgeWithSectorCoefficients(edge_tag, v0[0], ON_SubDSectorType::IgnoredSectorCoefficient, v0[1], ON_SubDSectorType::IgnoredSectorCoefficient)
      : nullptr;

    // Change the mesh_edges[].m_u from the topology id to an ON_SubDEdgePtr.
    // We need the ON_SubDEdgePtr below to create SubD faces.
    ON_SubDEdgePtr eptr = ON_SubDEdgePtr::Null;
    for (/*empty init*/; i < j; ++i)
    {
      ON_MeshNGonEdge& mesh_edge = mesh_edges[mesh_edge_map[i]];
      if (nullptr != e)
      {
        const ON_SubDVertex* v[2] = { subd_V[mesh_edge.m_mesh_Vi],  subd_V[mesh_edge.m_mesh_Vj] };
        if (v0[0] == v[0] && v0[1] == v[1])
          eptr = ON_SubDEdgePtr::Create(e, 0);
        else if (v0[0] == v[1] && v0[1] == v[0])
          eptr = ON_SubDEdgePtr::Create(e, 1);
        else
        {
          ON_SUBD_ERROR("There is a bug in the code above. This should not happen.");
          eptr = ON_SubDEdgePtr::Null;
        }
      }
      else
      {
        eptr = ON_SubDEdgePtr::Null;
      }
      mesh_edge.SetEdgePtr(eptr);
    }
  }

  //////////////////////////////////////////////////////////////////////
  //
  // Create the SubD faces.
  //
  //  mesh_edges[] is ordered in groups that form the boundary of each SubD face.
  //  All the edges that form a boundary of a face have the same m_sud_face_id value.
  //  If the input mesh is completely valid, this will also be ON_SubDFace m_id value.
  //  If the input mesh is damaged, some boundaries will not generate a corresponding SubD face.
  // 
  const ON_SubDFromMeshParameters::TextureCoordinatesOption texture_coordinates_option
    = nullptr != from_mesh_options
    ? from_mesh_options->GetTextureCoordinatesOption()
    : ON_SubDFromMeshParameters::TextureCoordinatesOption::None;
  const bool bAutomaticTextureCoordinates = ON_SubDFromMeshParameters::TextureCoordinatesOption::Automatic == texture_coordinates_option;
  

  // At most one of bCopyMeshMappingTag, bCopyMeshTextureCoordinates, or bPackedTextureCoordinates is true.
  const bool bCopyMeshMappingTag
    = (bAutomaticTextureCoordinates || ON_SubDFromMeshParameters::TextureCoordinatesOption::CopyMapping == texture_coordinates_option)
    && mesh->m_Ttag.IsSet()
    ;
  const bool bCopyMeshTextureCoordinates
    = false == bCopyMeshMappingTag
    && (bAutomaticTextureCoordinates || ON_SubDFromMeshParameters::TextureCoordinatesOption::CopyCoordinates == texture_coordinates_option)
    && mesh->HasTextureCoordinates()
    ;
  const bool bPackedTextureCoordinates
    = false == bCopyMeshMappingTag
    && false == bCopyMeshTextureCoordinates
    && (bAutomaticTextureCoordinates || ON_SubDFromMeshParameters::TextureCoordinatesOption::Packed == texture_coordinates_option)
    && mesh->HasTextureCoordinates()
    ;

  ON_SimpleArray< ON_SubDEdgePtr > EP(max_subd_face_edge_count);
  ON_SimpleArray< ON_3dPoint > face_texture_points(bCopyMeshTextureCoordinates ? max_subd_face_edge_count : 0);
  for (unsigned i = 0; i < mesh_edges.UnsignedCount(); /*empty iterator*/)
  {
    EP.SetCount(0);
    face_texture_points.SetCount(0);
    const unsigned candidate_sud_face_id = mesh_edges[i].m_sud_face_id;
    unsigned j = i;
    for (/*empty init*/; j < mesh_edges.UnsignedCount(); ++j)
    {
      const ON_MeshNGonEdge& mesh_edge = mesh_edges[j];
      if (candidate_sud_face_id != mesh_edge.m_sud_face_id)
        break;
      const ON_SubDEdgePtr eptr = mesh_edge.EdgePtr();
      if (eptr.IsNotNull())
      {
        EP.Append(eptr);
        const ON_SubDVertex* debug_eptr_v[2] = { eptr.RelativeVertex(0), eptr.RelativeVertex(1) };
        const ON_SubDVertex* debug_mesh_v[2] = { subd_V[mesh_edge.m_mesh_Vi], subd_V[mesh_edge.m_mesh_Vj] };
        const bool bOK = debug_eptr_v[0] == debug_mesh_v[0] && debug_eptr_v[1] == debug_mesh_v[1];
        if (false == bOK) ON_SUBD_ERROR("XXX");
        if (bCopyMeshTextureCoordinates)
          face_texture_points.Append(ON_3dPoint(mesh->m_T[mesh_edge.m_mesh_Vi]));
      }
    }
    const unsigned edge_count = EP.UnsignedCount();
    ON_SubDFace* f 
      = (edge_count >= 3 && j - i == edge_count)
      ?  new_subd->AddFace(EP.Array(), EP.UnsignedCount())
      : nullptr;
    if (nullptr != f)
    {
      if (bCopyMeshTextureCoordinates)
        new_subd->AddFaceTexturePoints(f, face_texture_points.Array(), face_texture_points.UnsignedCount() );
    }
    const unsigned actual_subd_face_id = (nullptr != f) ? f->m_id : 0;
    for ( /*empty init*/; i < j; ++i)
      mesh_edges[i].m_sud_face_id = actual_subd_face_id;
  }

  // Apply "ON_SubDEdgeTag::Crease" tag to boundary and non-manifold edges and their vertices.
  unsigned int interior_crease_count = 0;
  for (const ON_SubDEdge* edge = new_subd->FirstEdge(); nullptr != edge; edge = edge->m_next_edge)
  {
    // Note: edges are created before faces and we set the edge tag when the edges are created
    // assuming that face creation will go as expected. If the mesh is damaged, the face may not 
    // be created. So, we need to check both edge->m_face_count and edge->m_edge_tag.
    if (2 == edge->m_face_count && ON_SubDEdgeTag::Smooth == edge->m_edge_tag)
      continue;

    const_cast<ON_SubDEdge*>(edge)->m_edge_tag = ON_SubDEdgeTag::Crease;

    bHasTaggedVertices = true;
    const ON_SubDVertexTag vtag
      = (1 == edge->m_face_count || 2 == edge->m_face_count)
      ? ON_SubDVertexTag::Crease
      : ON_SubDVertexTag::Corner; // wire edge or non-manifold edge


    // Depending on the number of creased edges, a vertex on an interior crease here that
    // is tagged as ON_SubDVertexTag::Crease  here may get changed 
    // to ON_SubDVertexTag::Dart or ON_SubDVertexTag::Corner below.

    for (unsigned int j = 0; j < 2; j++)
    {
      const ON_SubDVertex* vertex = edge->m_vertex[j];
      if (ON_SubDVertexTag::Smooth == vertex->m_vertex_tag)
      {
        const_cast<ON_SubDVertex*>(vertex)->m_vertex_tag = vtag;
        if (ON_SubDVertexTag::Corner == vtag && edge->m_face_count > 2)
          bHasNonmanifoldCornerVertices = true;
      }
    }

    if ( 2 == edge->m_face_count )
      interior_crease_count++;
  }

  if (bHasNonmanifoldCornerVertices)
  {
    // may need to crease more edges to get valid corners RH-49843
    for (const ON_SubDVertex* v = new_subd->FirstVertex(); nullptr != v; v = v->m_next_vertex)
      Internal_CreateFromMesh_ValidateNonmanifoldVertex(v);
  }

  if (interior_crease_count > 0)
  {
    // Any interior vertex that has exactly one creased edge must be tagged as a dart.
    // Any interior vertex that has more than two creased edges must be tagged as a corner.
    unsigned int k = 0; // k = number of interior creases we've tested
    for (const ON_SubDEdge* edge = new_subd->FirstEdge(); nullptr != edge && k < interior_crease_count; edge = edge->m_next_edge)
    {
      if (2 != edge->m_face_count || ON_SubDEdgeTag::Crease != edge->m_edge_tag)
        continue;

      k++; // processing another interior crease.

      if ( ON_SubDVertexTag::Crease != edge->m_vertex[0]->m_vertex_tag
          && ON_SubDVertexTag::Crease != edge->m_vertex[1]->m_vertex_tag)
        continue;

      for (unsigned int j = 0; j < 2; j++)
      {
        const ON_SubDVertex* vertex = edge->m_vertex[j];
        if (ON_SubDVertexTag::Crease != vertex->m_vertex_tag)
          continue; // this vertex has already been processed.

        const ON_SubDVertexEdgeProperties ep = vertex->EdgeProperties();
        if ( 0 == ep.m_null_edge_count && 0 == ep.m_unset_edge_count )
        {
          if (ep.m_crease_edge_count >= 3)
          {
            const_cast<ON_SubDVertex*>(edge->m_vertex[j])->m_vertex_tag = ON_SubDVertexTag::Corner;
          }
          else if (1 == ep.m_crease_edge_count && ep.m_smooth_edge_count >= 1 && 2 == ep.m_min_edge_face_count && 2 == ep.m_max_edge_face_count)
          {
            const_cast<ON_SubDVertex*>(edge->m_vertex[j])->m_vertex_tag = ON_SubDVertexTag::Dart;
          }
        }
      }
    }
  }

  if (bHasTaggedVertices)
  {
    for (const ON_SubDEdge* edge = new_subd->FirstEdge(); nullptr != edge; edge = edge->m_next_edge)
    {
      if (ON_SubDEdgeTag::Smooth != edge->m_edge_tag)
        continue;
      const unsigned int tagged_end_index = edge->TaggedEndIndex();
      if (tagged_end_index < 2)
      {
        // sector weight will be calculated when facet type is set
        const_cast<ON_SubDEdge*>(edge)->m_sector_coefficient[tagged_end_index] = ON_SubDSectorType::UnsetSectorCoefficient;
      }
      else if (2 == tagged_end_index)
      {
        // both ends are tagged
        if (2 == edge->m_face_count)
        {
          // first subdivision will convert edge to smooth
          const_cast<ON_SubDEdge*>(edge)->m_edge_tag = ON_SubDEdgeTag::SmoothX;
          // sector weights will be calculated when facet type is set
          const_cast<ON_SubDEdge*>(edge)->m_sector_coefficient[0] = ON_SubDSectorType::UnsetSectorCoefficient;
          const_cast<ON_SubDEdge*>(edge)->m_sector_coefficient[1] = ON_SubDSectorType::UnsetSectorCoefficient;
        }
        else
        {
          const_cast<ON_SubDEdge*>(edge)->m_edge_tag = ON_SubDEdgeTag::Crease;
        }
      }
    }

    for (const ON_SubDVertex* vertex = new_subd->FirstVertex(); nullptr != vertex; vertex = vertex->m_next_vertex)
    {
      if (ON_SubDVertexTag::Crease != vertex->m_vertex_tag)
        continue;
      unsigned int vertex_creased_edge_count = 0;
      const unsigned int vertex_edge_count = vertex->m_edge_count;
      for (unsigned int j = 0; j < vertex_edge_count; j++)
      {
        const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(vertex->m_edges[j].m_ptr);
        if (ON_SubDEdgeTag::Crease == edge->m_edge_tag)
        {
          if (vertex_creased_edge_count >= 2)
          {
            // Three or more creased edges end at this vertex.
            // It must be subdivided as a corner vertex.
            const_cast<ON_SubDVertex*>(vertex)->m_vertex_tag = ON_SubDVertexTag::Corner;
            break;
          }
          vertex_creased_edge_count++;
        }
      }
    }
  }

  if (bMergeColinearEdges)
  {
    const bool bMergeBoundaryEdges = from_mesh_options->MergeColinearBoundaryEdges();
    const bool bMergeInteriorCreaseEdges = from_mesh_options->MergeColinearInteriorEdges();
    const bool bMergeInteriorSmoothEdges = from_mesh_options->MergeColinearInteriorEdges();
    new_subd->MergeColinearEdges(bMergeBoundaryEdges, bMergeInteriorCreaseEdges, bMergeInteriorSmoothEdges, 1e-6, 0.01, sin(0.25*ON_PI));
  }

  // All interior vertices must have at least 2 faces and three edges

  // If the ON_SubD was allocated in this function, do not delete it.
  uptr.release();

  // If the input mesh is not oriented, fix the subd so it is.
  if ( false == new_subd->IsOriented() )
    new_subd->Orient();

  const double max_convex_angle_radians = from_mesh_options->MaximumConvexCornerAngleRadians();
  const bool bLookForConvexCorners 
    = ON_SubDFromMeshParameters::ConvexCornerOption::AtMeshCorner == from_mesh_options->GetConvexCornerOption() 
    && max_convex_angle_radians > 0.0
    && max_convex_angle_radians < ON_PI
    ;
  const double min_concave_angle_radians = from_mesh_options->MinimumConcaveCornerAngleRadians();
  const bool bLookForConcaveCorners
    = ON_SubDFromMeshParameters::ConcaveCornerOption::AtMeshCorner == from_mesh_options->GetConcaveCornerOption()
    && min_concave_angle_radians > ON_PI
    && min_concave_angle_radians < ON_2PI
    ;
  if (bLookForConvexCorners || bLookForConcaveCorners)
  {
    // Add corners
    ON_SubDVertexIterator vit(*new_subd);
    for (ON_SubDVertex* vertex = const_cast<ON_SubDVertex*>(vit.FirstVertex()); nullptr != vertex; vertex = const_cast<ON_SubDVertex*>(vit.NextVertex()))
    {
      if (ON_SubDVertexTag::Crease != vertex->m_vertex_tag)
        continue;
      if ( 1 + vertex->m_face_count != vertex->m_edge_count )
        continue;

      ON_SubDComponentPtrPair boundary_pair = vertex->BoundaryEdgePair();
      if (false == boundary_pair.BothAreNotNull())
        continue;

      bool bConvexCorner
        = bLookForConvexCorners
        && vertex->m_edge_count <= from_mesh_options->MaximumConvexCornerEdgeCount()
        ;
      bool bConcaveCorner
        = bLookForConcaveCorners
        && vertex->m_edge_count >= from_mesh_options->MinimumConcaveCornerEdgeCount()
        ;

      if (false == bConvexCorner && false == bConcaveCorner)
        continue;

      // add up angles of faces at this vertex
      // If the faces are not coplanar, this sum can exceed 2pi.
      double vertex_angle_radians = 0.0;
      for (unsigned short vei = 0; vei < vertex->m_face_count; ++vei)
      {
        const double a = Internal_FaceCornerAngleRadians(vertex, vertex->m_faces[vei]);
        if (false == (a > 0.0 && a < ON_PI) )
        {
          vertex_angle_radians = ON_DBL_QNAN;
          break;
        }
        vertex_angle_radians += a;
      }
      if (false == (vertex_angle_radians > 0.0))
        continue;

      bConvexCorner = bConvexCorner && vertex_angle_radians <= max_convex_angle_radians;
      bConcaveCorner = bConcaveCorner && vertex_angle_radians >= min_concave_angle_radians;
      if (bConvexCorner ? 0 : 1 == bConcaveCorner ? 0 : 1)
        continue;

      // Finally, test the angle between the boundary edges. That angle must also pass the min/max tests.
      // This test cannot be done earlier, because we need to know if we are making a concave or convex corner
      // to do this test correctly.
      const double boundary_angle_radians = ON_SubDSectorType::CornerSectorAngleRadiansFromEdges(boundary_pair.First().EdgePtr(), boundary_pair.Second().EdgePtr());
      if (false == boundary_angle_radians > 0.0 && boundary_angle_radians < ON_PI)
        continue; // the angle is always acute because it does not look at the active side
      if (bConvexCorner)
      {
        if (false == (boundary_angle_radians <= max_convex_angle_radians))
          continue;
      }
      else if (bConcaveCorner)
      {
        if (false == ((ON_2PI - boundary_angle_radians) >= min_concave_angle_radians))
          continue;
      }
      else
        continue; // should never get here


      vertex->m_vertex_tag = ON_SubDVertexTag::Corner;        
    }
  }

  new_subd->UpdateEdgeSectorCoefficients(false);



  if (bCopyMeshMappingTag)
  {
    new_subd->SetTextureMappingTag(mesh->m_Ttag);
    new_subd->SetTextureCoordinateType(ON_SubDTextureCoordinateType::FromMapping);
  }
  else if (bCopyMeshTextureCoordinates)
  {
    new_subd->SetTextureMappingTag(ON_MappingTag::Unset);
    new_subd->SetTextureCoordinateType(ON_SubDTextureCoordinateType::FromFaceTexturePoints);
  }
  else if (bPackedTextureCoordinates)
  {
    new_subd->SetTextureMappingTag(ON_MappingTag::Unset);
    new_subd->SetTextureCoordinateType(ON_SubDTextureCoordinateType::Packed);
  }
  else
  {
    new_subd->SetTextureMappingTag(ON_MappingTag::Unset);
    new_subd->SetTextureCoordinateType(ON_SubDTextureCoordinateType::Unset);
  }

  return new_subd;
}


static ON_SubDVertex* IndexVertex(
  ON_SimpleArray< ON_SubDVertex* >& vertex,
  ON_ClassArray< ON_ClassArray< ON_SimpleArray < int > > >& vert_index,
  int x, int y, int z
  )
{
  int vi = vert_index[x][y][z];
  if (vi < 0)
    return nullptr;
  if (vi >= vertex.Count())
    return nullptr;
  return vertex[vi];
}


ON_SubD* ON_SubD::CreateSubDBox(
  const ON_3dPoint corners[8],
  ON_SubDEdgeTag edge_tag,
  unsigned int facecount_x,
  unsigned int facecount_y,
  unsigned int facecount_z,
  ON_SubD* destination_subd)
{
  double edge_sharpness
    = ON_SubDEdgeTag::Crease == edge_tag
    ? ON_SubDEdgeSharpness::CreaseValue
    : ON_SubDEdgeSharpness::SmoothValue
    ;

  return ON_SubD::CreateSubDBox(
    corners,
    edge_sharpness,
    facecount_x,
    facecount_y,
    facecount_z,
    destination_subd
  );
}

ON_SubD* ON_SubD::CreateSubDBox(
  const ON_3dPoint corners[8],
  double edge_sharpness,
  unsigned int facecount_x,
  unsigned int facecount_y,
  unsigned int facecount_z,
  ON_SubD* destination_subd
)
{
  if (nullptr == corners)
    return nullptr;
  if (facecount_x <= 0)
    return nullptr;
  if (facecount_y <= 0)
    return nullptr;
  if (facecount_z <= 0)
    return nullptr;
    
  const ON_SubDEdgeTag edge_tag
    = (ON_SubDEdgeSharpness::CreaseValue == edge_sharpness)
    ? ON_SubDEdgeTag::Crease
    : ON_SubDEdgeTag::Smooth;

  ON_SubD* subd
    = (nullptr != destination_subd)
    ? destination_subd
    : new ON_SubD;

  ON_3dVector xdir = corners[1] - corners[0];
  ON_3dVector ydir = corners[3] - corners[0];
  ON_3dVector zdir = corners[4] - corners[0];

  double x_len = xdir.LengthAndUnitize();
  double y_len = ydir.LengthAndUnitize();
  double z_len = zdir.LengthAndUnitize();

  double dx = x_len / (double)facecount_x;
  double dy = y_len / (double)facecount_y;
  double dz = z_len / (double)facecount_z;

  ON_ClassArray< ON_ClassArray< ON_SimpleArray < int > > > vert_index;
  ON_SimpleArray< ON_SubDVertex* > vertex;
  // Allocate index arrays
  vert_index.Reserve(facecount_x + 1);
  vert_index.SetCount(facecount_x + 1);
  for (unsigned int ix = 0; ix <= facecount_x; ix++)
  {
    vert_index[ix].Reserve(facecount_y + 1);
    vert_index[ix].SetCount(facecount_y + 1);
    for (unsigned int iy = 0; iy <= facecount_y; iy++)
    {
      vert_index[ix][iy].Reserve(facecount_z + 1);
      vert_index[ix][iy].SetCount(facecount_z + 1);
      for (unsigned int iz = 0; iz <= facecount_z; iz++)
      {
        vert_index[ix][iy][iz] = -1;
      }
    }
  }

  // Make interior vertexes and store 3d indexes
  for (unsigned int ix = 0; ix <= facecount_x; ix++)
  {
    for (unsigned int iy = 0; iy <= facecount_y; iy++)
    {
      for (unsigned int iz = 0; iz <= facecount_z; iz++)
      {
        int ccnt = 0;
        if (ix == 0 || ix == facecount_x)
          ccnt++;
        if (iy == 0 || iy == facecount_y)
          ccnt++;
        if (iz == 0 || iz == facecount_z)
          ccnt++;
        if (ccnt > 0) // On some face
        {
          ON_SubDVertexTag vtag = ON_SubDVertexTag::Smooth;
          if (edge_tag == ON_SubDEdgeTag::Crease)
          {
            if(ccnt == 2)  // On some edge
              vtag = ON_SubDVertexTag::Crease;
            else if(ccnt == 3)  // On some corner
              vtag = ON_SubDVertexTag::Corner;
          }
          ON_3dPoint P(corners[0] + (xdir * (dx * ix)) + (ydir * (dy * iy)) + (zdir * (dz * iz)));
          vert_index[ix][iy][iz] = vertex.Count();
          vertex.AppendNew() = subd->AddVertex(vtag, &P.x);
          if (nullptr == vertex.Last())
            return nullptr;
        }
      }
    }
  }

  ON_ClassArray< ON_SubDEdgePtr > box_edges[12];
  ON_SubDEdge* e = nullptr;

  // 4 edge chains parallel to x
  for (unsigned int ix = 0; ix < facecount_x; ix++)
  {
    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, ix, 0, 0), IndexVertex(vertex, vert_index, ix + 1, 0, 0));
    box_edges[0].Append(ON_SubDEdgePtr::Create(e, 0));

    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, ix, facecount_y, 0), IndexVertex(vertex, vert_index, ix + 1, facecount_y, 0));
    box_edges[2].Append(ON_SubDEdgePtr::Create(e, 0));

    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, ix, 0, facecount_z), IndexVertex(vertex, vert_index, ix + 1, 0, facecount_z));
    box_edges[8].Append(ON_SubDEdgePtr::Create(e, 0));

    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, ix, facecount_y, facecount_z), IndexVertex(vertex, vert_index, ix + 1, facecount_y, facecount_z));
    box_edges[10].Append(ON_SubDEdgePtr::Create(e, 0));
  }

  // 4 edge chains parallel to y
  for (unsigned int iy = 0; iy < facecount_y; iy++)
  {
    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, 0, iy, 0), IndexVertex(vertex, vert_index, 0, iy + 1, 0));
    box_edges[3].Append(ON_SubDEdgePtr::Create(e, 0));

    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, facecount_x, iy, 0), IndexVertex(vertex, vert_index, facecount_x, iy + 1, 0));
    box_edges[1].Append(ON_SubDEdgePtr::Create(e, 0));

    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, facecount_x, iy, facecount_z), IndexVertex(vertex, vert_index, facecount_x, iy + 1, facecount_z));
    box_edges[9].Append(ON_SubDEdgePtr::Create(e, 0));

    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, 0, iy, facecount_z), IndexVertex(vertex, vert_index, 0, iy + 1, facecount_z));
    box_edges[11].Append(ON_SubDEdgePtr::Create(e, 0));
  }

  // 4 edge chains parallel to z
  for (unsigned int iz = 0; iz < facecount_z; iz++)
  {
    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, 0, 0, iz), IndexVertex(vertex, vert_index, 0, 0, iz + 1));
    box_edges[4].Append(ON_SubDEdgePtr::Create(e, 0));

    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, facecount_x, 0, iz), IndexVertex(vertex, vert_index, facecount_x, 0, iz + 1));
    box_edges[5].Append(ON_SubDEdgePtr::Create(e, 0));

    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, facecount_x, facecount_y, iz), IndexVertex(vertex, vert_index, facecount_x, facecount_y, iz + 1));
    box_edges[6].Append(ON_SubDEdgePtr::Create(e, 0));

    e = subd->AddEdge(edge_tag, IndexVertex(vertex, vert_index, 0, facecount_y, iz), IndexVertex(vertex, vert_index, 0, facecount_y, iz + 1));
    box_edges[7].Append(ON_SubDEdgePtr::Create(e, 0));
  }

  if (edge_sharpness > ON_SubDEdgeSharpness::Tolerance && edge_sharpness <= ON_SubDEdgeSharpness::MaximumValue)
  {
    const ON_SubDEdgeSharpness sharpness = ON_SubDEdgeSharpness::FromConstant(edge_sharpness);
    if (sharpness.IsSharp())
    {
      for (int i = 0; i < 12; ++i)
      {
        ON_ClassArray< ON_SubDEdgePtr >& sharp_edges = box_edges[i];
        const int c = sharp_edges.Count();
        for (int j = 0; j < c; ++j)
          sharp_edges[j].SetRelativeSharpness(sharpness);
      }
    }
  }

  ON_ClassArray< ON_ClassArray< ON_SubDEdgePtr > > face_edges[2];

  // Bottom face
  {
    for (unsigned int iy = 0; iy <= facecount_y; iy++)
    {
      if (iy == 0)
        face_edges[0].Append(box_edges[0]);
      else if (iy == facecount_y)
        face_edges[0].Append(box_edges[2]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& row = face_edges[0].AppendNew();
        for (unsigned int ix = 0; ix < facecount_x; ix++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, ix, iy, 0), IndexVertex(vertex, vert_index, ix + 1, iy, 0));
          row.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int ix = 0; ix <= facecount_x; ix++)
    {
      if (ix == 0)
        face_edges[1].Append(box_edges[3]);
      else if (ix == facecount_x)
        face_edges[1].Append(box_edges[1]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& col = face_edges[1].AppendNew();
        for (unsigned int iy = 0; iy < facecount_y; iy++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, ix, iy, 0), IndexVertex(vertex, vert_index, ix, iy + 1, 0));
          col.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int iy = 0; iy < facecount_y; iy++)
    {
      for (unsigned int ix = 0; ix < facecount_x; ix++)
      {
        ON_SubDEdgePtr edge_ptrs[4];
        edge_ptrs[0] = face_edges[1][ix][iy];
        edge_ptrs[1] = face_edges[0][iy + 1][ix];
        edge_ptrs[2] = face_edges[1][ix + 1][iy].Reversed();
        edge_ptrs[3] = face_edges[0][iy][ix].Reversed();
        ON_SubDFace* f0 = subd->AddFace(edge_ptrs, 4);
        if (nullptr == f0)
          return nullptr;
      }
    }
  }

  // Top face
  {
    face_edges[0].Empty();
    face_edges[1].Empty();

    for (unsigned int iy = 0; iy <= facecount_y; iy++)
    {
      if (iy == 0)
        face_edges[0].Append(box_edges[8]);
      else if (iy == facecount_y)
        face_edges[0].Append(box_edges[10]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& row = face_edges[0].AppendNew();
        for (unsigned int ix = 0; ix < facecount_x; ix++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, ix, iy, facecount_z), IndexVertex(vertex, vert_index, ix + 1, iy, facecount_z));
          row.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int ix = 0; ix <= facecount_x; ix++)
    {
      if (ix == 0)
        face_edges[1].Append(box_edges[11]);
      else if (ix == facecount_x)
        face_edges[1].Append(box_edges[9]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& col = face_edges[1].AppendNew();
        for (unsigned int iy = 0; iy < facecount_y; iy++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, ix, iy, facecount_z), IndexVertex(vertex, vert_index, ix, iy + 1, facecount_z));
          col.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int iy = 0; iy < facecount_y; iy++)
    {
      for (unsigned int ix = 0; ix < facecount_x; ix++)
      {
        ON_SubDEdgePtr edge_ptrs[4];
        edge_ptrs[0] = face_edges[0][iy][ix];
        edge_ptrs[1] = face_edges[1][ix + 1][iy];
        edge_ptrs[2] = face_edges[0][iy + 1][ix].Reversed();
        edge_ptrs[3] = face_edges[1][ix][iy].Reversed();
        ON_SubDFace* f0 = subd->AddFace(edge_ptrs, 4);
        if (nullptr == f0)
          return nullptr;
      }
    }
  }

  // Front face
  {
    face_edges[0].Empty();
    face_edges[1].Empty();

    for (unsigned int iz = 0; iz <= facecount_z; iz++)
    {
      if (iz == 0)
        face_edges[0].Append(box_edges[0]);
      else if (iz == facecount_z)
        face_edges[0].Append(box_edges[8]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& row = face_edges[0].AppendNew();
        for (unsigned int ix = 0; ix < facecount_x; ix++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, ix, 0, iz), IndexVertex(vertex, vert_index, ix + 1, 0, iz));
          row.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int ix = 0; ix <= facecount_x; ix++)
    {
      if (ix == 0)
        face_edges[1].Append(box_edges[4]);
      else if (ix == facecount_x)
        face_edges[1].Append(box_edges[5]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& col = face_edges[1].AppendNew();
        for (unsigned int iz = 0; iz < facecount_z; iz++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, ix, 0, iz), IndexVertex(vertex, vert_index, ix, 0, iz + 1));
          col.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int iz = 0; iz < facecount_z; iz++)
    {
      for (unsigned int ix = 0; ix < facecount_x; ix++)
      {
        ON_SubDEdgePtr edge_ptrs[4];
        edge_ptrs[0] = face_edges[0][iz][ix];
        edge_ptrs[1] = face_edges[1][ix + 1][iz];
        edge_ptrs[2] = face_edges[0][iz + 1][ix].Reversed();
        edge_ptrs[3] = face_edges[1][ix][iz].Reversed();
        ON_SubDFace* f0 = subd->AddFace(edge_ptrs, 4);
        if (nullptr == f0)
          return nullptr;
      }
    }
  }

  // Back face
  {
    face_edges[0].Empty();
    face_edges[1].Empty();

    for (unsigned int iz = 0; iz <= facecount_z; iz++)
    {
      if (iz == 0)
        face_edges[0].Append(box_edges[2]);
      else if (iz == facecount_z)
        face_edges[0].Append(box_edges[10]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& row = face_edges[0].AppendNew();
        for (unsigned int ix = 0; ix < facecount_x; ix++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, ix, facecount_y, iz), IndexVertex(vertex, vert_index, ix + 1, facecount_y, iz));
          row.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int ix = 0; ix <= facecount_x; ix++)
    {
      if (ix == 0)
        face_edges[1].Append(box_edges[7]);
      else if (ix == facecount_x)
        face_edges[1].Append(box_edges[6]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& col = face_edges[1].AppendNew();
        for (unsigned int iz = 0; iz < facecount_z; iz++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, ix, facecount_y, iz), IndexVertex(vertex, vert_index, ix, facecount_y, iz + 1));
          col.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int iz = 0; iz < facecount_z; iz++)
    {
      for (unsigned int ix = 0; ix < facecount_x; ix++)
      {
        ON_SubDEdgePtr edge_ptrs[4];
        edge_ptrs[0] = face_edges[1][ix][iz];
        edge_ptrs[1] = face_edges[0][iz + 1][ix];
        edge_ptrs[2] = face_edges[1][ix + 1][iz].Reversed();
        edge_ptrs[3] = face_edges[0][iz][ix].Reversed();
        ON_SubDFace* f0 = subd->AddFace(edge_ptrs, 4);
        if (nullptr == f0)
          return nullptr;
      }
    }
  }

  // Left face
  {
    face_edges[0].Empty();
    face_edges[1].Empty();

    for (unsigned int iz = 0; iz <= facecount_z; iz++)
    {
      if (iz == 0)
        face_edges[0].Append(box_edges[3]);
      else if (iz == facecount_z)
        face_edges[0].Append(box_edges[11]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& row = face_edges[0].AppendNew();
        for (unsigned int iy = 0; iy < facecount_y; iy++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, 0, iy, iz), IndexVertex(vertex, vert_index, 0, iy + 1, iz));
          row.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int iy = 0; iy <= facecount_y; iy++)
    {
      if (iy == 0)
        face_edges[1].Append(box_edges[4]);
      else if (iy == facecount_y)
        face_edges[1].Append(box_edges[7]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& col = face_edges[1].AppendNew();
        for (unsigned int iz = 0; iz < facecount_z; iz++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, 0, iy, iz), IndexVertex(vertex, vert_index, 0, iy, iz + 1));
          col.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int iz = 0; iz < facecount_z; iz++)
    {
      for (unsigned int iy = 0; iy < facecount_y; iy++)
      {
        ON_SubDEdgePtr edge_ptrs[4];
        edge_ptrs[0] = face_edges[1][iy][iz];
        edge_ptrs[1] = face_edges[0][iz + 1][iy];
        edge_ptrs[2] = face_edges[1][iy + 1][iz].Reversed();
        edge_ptrs[3] = face_edges[0][iz][iy].Reversed();
        ON_SubDFace* f0 = subd->AddFace(edge_ptrs, 4);
        if (nullptr == f0)
          return nullptr;
      }
    }
  }

  // Right face
  {
    face_edges[0].Empty();
    face_edges[1].Empty();

    for (unsigned int iz = 0; iz <= facecount_z; iz++)
    {
      if (iz == 0)
        face_edges[0].Append(box_edges[1]);
      else if (iz == facecount_z)
        face_edges[0].Append(box_edges[9]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& row = face_edges[0].AppendNew();
        for (unsigned int iy = 0; iy < facecount_y; iy++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, facecount_x, iy, iz), IndexVertex(vertex, vert_index, facecount_x, iy + 1, iz));
          row.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int iy = 0; iy <= facecount_y; iy++)
    {
      if (iy == 0)
        face_edges[1].Append(box_edges[5]);
      else if (iy == facecount_y)
        face_edges[1].Append(box_edges[6]);
      else
      {
        ON_ClassArray< ON_SubDEdgePtr >& col = face_edges[1].AppendNew();
        for (unsigned int iz = 0; iz < facecount_z; iz++)
        {
          e = subd->AddEdge(ON_SubDEdgeTag::Smooth, IndexVertex(vertex, vert_index, facecount_x, iy, iz), IndexVertex(vertex, vert_index, facecount_x, iy, iz + 1));
          col.Append(ON_SubDEdgePtr::Create(e, 0));
        }
      }
    }

    for (unsigned int iz = 0; iz < facecount_z; iz++)
    {
      for (unsigned int iy = 0; iy < facecount_y; iy++)
      {
        ON_SubDEdgePtr edge_ptrs[4];
        edge_ptrs[0] = face_edges[0][iz][iy];
        edge_ptrs[1] = face_edges[1][iy + 1][iz];
        edge_ptrs[2] = face_edges[0][iz + 1][iy].Reversed();
        edge_ptrs[3] = face_edges[1][iy][iz].Reversed();
        ON_SubDFace* f0 = subd->AddFace(edge_ptrs, 4);
        if (nullptr == f0)
          return nullptr;
      }
    }
  }

  if (subd == destination_subd)
    subd->SubDModifiedNofification();
  else
    subd->UpdateAllTagsAndSectorCoefficients(true);

 return subd;
}


/*
The ONLY use for this class is in a calculation to determine if an ngon has a single simple outer boundary.
*/
class ON_NgonBoundaryComponent
{
public:
  enum class Type : unsigned char
  {
    Unset = 0,
    Vertex = 1,
    Edge = 2
  };

  static const ON_NgonBoundaryComponent Unset;

  unsigned int IsBoundaryVertex() const;

  unsigned int IsBoundaryEdge() const;

  ON_NgonBoundaryComponent::Type m_type = ON_NgonBoundaryComponent::Type::Unset;
  mutable unsigned char m_mark = 0;
  unsigned char m_face_count = 0; // 0, 1, 2, or 3 = number of faces attached to this edge. 3 means 3 or more
  unsigned char m_attached_count = 0; // 0, 1, or 2 = number of values set in m_attached_to[]

  unsigned int m_index = 0;

  // If this component is a vertex, these will be the first two edges attached to the vertex.
  // If this component is an edge, these will be the vertices at the start and end.
  ON_NgonBoundaryComponent* m_attached_to[2] = {};

private:
  bool Internal_IsAttachedToTwo(ON_NgonBoundaryComponent::Type attached_type) const;
  friend class ON_NgonBoundaryChecker;
  // hash table pointer
  // m_next is a list in a ON_NgonBoundaryChecker.m_vertex_hash_table[] element.
  ON_NgonBoundaryComponent* m_next = nullptr;
};

bool ON_NgonBoundaryComponent::Internal_IsAttachedToTwo(ON_NgonBoundaryComponent::Type attached_type) const
{
  return
    2 == m_attached_count
    && nullptr != m_attached_to[0]
    && nullptr != m_attached_to[1]
    && m_attached_to[0] != m_attached_to[1]
    && attached_type == m_attached_to[0]->m_type
    && attached_type == m_attached_to[1]->m_type
    ;
}

unsigned int ON_NgonBoundaryComponent::IsBoundaryVertex() const
{
  return
    ON_NgonBoundaryComponent::Type::Vertex == m_type
    && 0 == m_face_count
    && Internal_IsAttachedToTwo(ON_NgonBoundaryComponent::Type::Edge)
    && 1 == m_attached_to[0]->m_face_count
    && 1 == m_attached_to[1]->m_face_count
    ;
}

unsigned int ON_NgonBoundaryComponent::IsBoundaryEdge() const
{
  return
    ON_NgonBoundaryComponent::Type::Edge == m_type
    && 1 == m_face_count
    && Internal_IsAttachedToTwo(ON_NgonBoundaryComponent::Type::Vertex)
    && 0 == m_attached_to[0]->m_face_count
    && 0 == m_attached_to[1]->m_face_count
    ;
}

const ON_NgonBoundaryComponent ON_NgonBoundaryComponent::Unset;

void ON_NgonBoundaryChecker::Internal_ReturnIsNotSimple()
{
  m_bIsSimple = false;
  m_bIsNotSimple = true;
}

void ON_NgonBoundaryChecker::Internal_Reset()
{
  m_fsp.ReturnAll();
  for (unsigned i = 0; i < ON_NgonBoundaryChecker::HashTableSize; ++i)
    m_hash_table[i] = nullptr;
  m_vertex_count = 0;
  m_edge_count = 0;
  m_bIsSimple = false;
  m_bIsNotSimple = false;
}

unsigned int ON_NgonBoundaryChecker::Internal_VertexHashIndex(unsigned int vertex_index)
{
  return ON_CRC32(0, sizeof(vertex_index), &vertex_index) % ON_NgonBoundaryChecker::HashTableSize;
}


unsigned int ON_NgonBoundaryChecker::Internal_EdgeHashIndex(unsigned int vertex_index0, unsigned int vertex_index1)
{
  return (vertex_index0 < vertex_index1)
    ? (ON_CRC32(vertex_index0, sizeof(vertex_index1), &vertex_index1) % ON_NgonBoundaryChecker::HashTableSize)
    : (ON_CRC32(vertex_index1, sizeof(vertex_index0), &vertex_index0) % ON_NgonBoundaryChecker::HashTableSize)
    ;
}

void ON_NgonBoundaryChecker::Internal_InitialzeFixedSizePool()
{
  if (0 == m_fsp.SizeofElement())
    m_fsp.Create(sizeof(ON_NgonBoundaryComponent), 0, 0);
}

ON_NgonBoundaryComponent* ON_NgonBoundaryChecker::Internal_AddVertex(unsigned int vertex_index)
{
  if (m_bIsNotSimple)
    return nullptr;

  const unsigned hash_index = ON_NgonBoundaryChecker::Internal_VertexHashIndex(vertex_index);
  ON_NgonBoundaryComponent* v;
  for (
    v = m_hash_table[hash_index];
    nullptr != v;
    v = v->m_next
    )
  {
    if (ON_NgonBoundaryComponent::Type::Vertex == v->m_type && vertex_index == v->m_index)
      return v;
  }
  if (nullptr == v)
  {
    Internal_InitialzeFixedSizePool();
    v = (ON_NgonBoundaryComponent*)m_fsp.AllocateElement();
    v->m_type = ON_NgonBoundaryComponent::Type::Vertex;
    v->m_index = vertex_index;
    v->m_next = m_hash_table[hash_index];
    m_hash_table[hash_index] = v;
    ++m_vertex_count;
  }
  return v;
}

ON_NgonBoundaryComponent* ON_NgonBoundaryChecker::Internal_AddEdge(unsigned int vertex_index0, unsigned int vertex_index1, bool bMustBeOriented)
{
  if (m_bIsNotSimple)
    return nullptr;

  if (vertex_index0 == vertex_index1)
  {
    Internal_ReturnIsNotSimple();
    return nullptr;
  }

  ON_NgonBoundaryComponent* v[2] = { Internal_AddVertex(vertex_index0), Internal_AddVertex(vertex_index1) };
  if (nullptr == v[0] || nullptr == v[1])
  {
    Internal_ReturnIsNotSimple();
    return nullptr;
  }

  const unsigned hash_index = ON_NgonBoundaryChecker::Internal_EdgeHashIndex(vertex_index0, vertex_index1);
  ON_NgonBoundaryComponent* e;
  for (
    e = m_hash_table[hash_index];
    nullptr != e;
    e = e->m_next
    )
  {
    if (
      ON_NgonBoundaryComponent::Type::Edge == e->m_type
      &&
      ((e->m_attached_to[0] == v[0] && e->m_attached_to[1] == v[1]) || (e->m_attached_to[0] == v[1] && e->m_attached_to[1] == v[0]))
      )
    {
      if (1 == e->m_face_count)
      {
        if (bMustBeOriented)
        {
          if (e->m_attached_to[0] != v[1] || e->m_attached_to[1] != v[0])
          {
            // The 2 faces attached to this edge are not compatibly oriented.
            Internal_ReturnIsNotSimple();
            return nullptr;
          }
        }
        // this is an interior edge
        e->m_face_count = 2;
        return e;
      }
      // nonmanifold edge
      Internal_ReturnIsNotSimple();
      return nullptr;
    }
  }

  e = (ON_NgonBoundaryComponent*)m_fsp.AllocateElement();
  e->m_type = ON_NgonBoundaryComponent::Type::Edge;
  e->m_face_count = 1;
  e->m_attached_count = 2;
  e->m_attached_to[0] = v[0];
  e->m_attached_to[1] = v[1];
  e->m_next = m_hash_table[hash_index];
  m_hash_table[hash_index] = e;
  ++m_edge_count;
  return e;
}


bool ON_NgonBoundaryChecker::IsSimpleNgon(
  const class ON_MeshNgon* ngon,
  const class ON_Mesh* mesh,
  bool bMustBeOriented
)
{
  Internal_Reset();

  if (nullptr == ngon || nullptr == mesh)
  {
    Internal_ReturnIsNotSimple();
    return false;
  }
  
  const unsigned ngon_face_count = ngon->m_Fcount;
  if (ngon_face_count < 1 || nullptr == ngon->m_fi)
  {
    Internal_ReturnIsNotSimple();
    return false;
  }

  const int mesh_vertex_count = mesh->VertexCount();
  const unsigned mesh_face_count = mesh->m_F.UnsignedCount();
  if (mesh_vertex_count < 3 || mesh_face_count < 1)
  {
    Internal_ReturnIsNotSimple();
    return false;
  }

  const ON_MeshFace* a = mesh->m_F.Array();
  for (unsigned i = 0; i < ngon_face_count; ++i)
  {
    const unsigned fi = ngon->m_fi[i];
    if (fi >= mesh_face_count)
    {
      Internal_ReturnIsNotSimple();
      return false; // invalid face index in this ngon
    }
    const int* fvi = a[fi].vi;
    if (fvi[0] < 0 || fvi[0] >= mesh_vertex_count)
    {
      Internal_ReturnIsNotSimple();
      return false; // invalid face in this ngon
    }
    if (fvi[1] < 0 || fvi[1] >= mesh_vertex_count)
    {
      Internal_ReturnIsNotSimple();
      return false; // invalid face in this ngon
    }
    if (fvi[2] < 0 || fvi[2] >= mesh_vertex_count)
    {
      Internal_ReturnIsNotSimple();
      return false; // invalid face in this ngon
    }
    if (fvi[3] < 0 || fvi[3] >= mesh_vertex_count)
    {
      Internal_ReturnIsNotSimple();
      return false; // invalid face in this ngon
    }
    if (nullptr == this->Internal_AddEdge(fvi[0], fvi[1], bMustBeOriented))
    {
      Internal_ReturnIsNotSimple();
      return false;
    }
    if (nullptr == this->Internal_AddEdge(fvi[1], fvi[2], bMustBeOriented))
    {
      Internal_ReturnIsNotSimple();
      return false;
    }
    if (fvi[2] != fvi[3])
    {
      if (nullptr == this->Internal_AddEdge(fvi[2], fvi[3], bMustBeOriented))
      {
        Internal_ReturnIsNotSimple();
        return false;
      }
    }
    if (nullptr == this->Internal_AddEdge(fvi[3], fvi[0], bMustBeOriented))
    {
      Internal_ReturnIsNotSimple();
      return false;
    }
  }

  if (m_edge_count < 3 || m_vertex_count < 3)
  {
    Internal_ReturnIsNotSimple();
    return false;
  }

  // A simple ngon has Euler number = ( V - E + F) = 1.
  if (m_vertex_count + ngon_face_count != m_edge_count + 1)
  {
    Internal_ReturnIsNotSimple();
    return false; // wrong Euler number
  }
  
  // set vertex attachments
  for (unsigned hash_index = 0; hash_index < ON_NgonBoundaryChecker::HashTableSize; ++hash_index)
  {
    for (ON_NgonBoundaryComponent* e = m_hash_table[hash_index]; nullptr != e; e = e->m_next)
    {
      if (1 != e->m_face_count)
        continue;
      for (unsigned evi = 0; evi < 2; ++evi)
      {
        ON_NgonBoundaryComponent* v = e->m_attached_to[evi];
        if (v->m_attached_count >= 2)
        {
          Internal_ReturnIsNotSimple();
          return false; // vertex is attached to 3 or more boundary edges
        }
        v->m_attached_to[v->m_attached_count++] = e;
      }
    }
  }

  bool bBoundaryIsMarked = false;
  ON_FixedSizePoolIterator fspit(m_fsp);
  for (ON_NgonBoundaryComponent* e = (ON_NgonBoundaryComponent * )fspit.FirstElement(); nullptr != e; e = (ON_NgonBoundaryComponent * )fspit.NextElement())
  {
    if (1 != e->m_face_count)
      continue; // vertex components always have m_face_count = 0;

    // e is a boundary edge
    if (bBoundaryIsMarked)
    {
      if (0 == e->m_mark)
      {
        // this is a boundary edge that part of the boundary we marked. The ngon is not simple.
        Internal_ReturnIsNotSimple();
        return false;
      }
    }
    else
    {
      if (false == e->IsBoundaryEdge())
      {
        Internal_ReturnIsNotSimple();
        return false;
      }
      // e is the first boundary edge in the pool
      if (0 != e->m_mark)
      {
        ON_ERROR("Bug in this code - all edges should have m_mark = 0 at this point.");
        Internal_ReturnIsNotSimple();
        return false;
      }

      // Walk along the boundary beginning at e0 and mark every edge in the boundary.
      ON_NgonBoundaryComponent* e0 = e;
      ON_NgonBoundaryComponent* v0 = e0->m_attached_to[0];
      if ( nullptr == v0 || 0 != v0->m_mark)
      {
        ON_ERROR("Bug in this code - vertices should have m_mark = 0 at this point.");
        Internal_ReturnIsNotSimple();
        return false;
      }
      if (false == v0->IsBoundaryVertex())
      {
        Internal_ReturnIsNotSimple();
        return false;
      }
      ON_NgonBoundaryComponent* e1 = e0;
      ON_NgonBoundaryComponent* v1 = v0;
      for (unsigned i = 0; i < m_edge_count; ++i) // counter limits infinite loop if there is a bug
      {
        if (0 != v1->m_mark)
        {
          Internal_ReturnIsNotSimple();
          return false;
        }
        if (0 != e1->m_mark)
        {
          Internal_ReturnIsNotSimple();
          return false;
        }

        // mark v1 and e1 as part of the boundary.
        v1->m_mark = 1;
        e1->m_mark = 1;

        // set v1 = "next" vertex in the boundary
        if ( v1 == e1->m_attached_to[0])
          v1 = e1->m_attached_to[1];
        else if (v1 == e1->m_attached_to[1])
        {
          if (bMustBeOriented)
          {
            Internal_ReturnIsNotSimple();
            return false;
          }
          v1 = e1->m_attached_to[0];
        }
        else
        {
          Internal_ReturnIsNotSimple();
          return false;
        }

        if (nullptr == v1)
        {
          Internal_ReturnIsNotSimple();
          return false;
        }

        // set e1 = "next" edge in the boundary
        if (e1 == v1->m_attached_to[0])
          e1 = v1->m_attached_to[1];
        else if (e1 == v1->m_attached_to[1])
          e1 = v1->m_attached_to[0];
        else
        {
          Internal_ReturnIsNotSimple();
          return false;
        }

        if (nullptr == e1)
        {
          Internal_ReturnIsNotSimple();
          return false;
        }

        if (e0 == e1 || v0 == v1)
        {
          if (e0 == e1 && v0 == v1)
          {
            // all edges and vertices in this boundary are marked. There should be no unmarked boundary edges.
            bBoundaryIsMarked = true;
            break;
          }
          Internal_ReturnIsNotSimple();
          return false;
        }

        if (false == v1->IsBoundaryVertex())
        {
          Internal_ReturnIsNotSimple();
          return false;
        }
        if (false == e1->IsBoundaryEdge())
        {
          Internal_ReturnIsNotSimple();
          return false;
        }
      }
      if (false == bBoundaryIsMarked)
      {
        Internal_ReturnIsNotSimple();
        return false; // for loop finished without marking a boundary
      }
    }
  }

  m_bIsSimple = (bBoundaryIsMarked && false == m_bIsNotSimple);
  return m_bIsSimple;
}

