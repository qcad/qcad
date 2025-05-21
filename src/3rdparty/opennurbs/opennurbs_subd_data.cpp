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

const ON_SubDLevel ON_SubDLevel::Empty;

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDimple
//


ON_SubDimple::ON_SubDimple()
  : RuntimeSerialNumber(++ON_SubDimple::Internal_RuntimeSerialNumberGenerator)
{}

ON_SubDimple::~ON_SubDimple()
{
  Destroy();
}

ON_SubDHeap& ON_SubDimple::Heap()
{
  return m_heap;
}

void ON_SubDimple::Clear()
{
  m_subd_appearance = ON_SubD::DefaultSubDAppearance;
  m_texture_coordinate_type = ON_SubDTextureCoordinateType::Unset;
  m_texture_mapping_tag = ON_MappingTag::Unset;
  m_colors_mapping_tag = ON_MappingTag::Unset;

  m_fragment_texture_settings_hash = ON_SHA1_Hash::EmptyContentHash;
  m_fragment_colors_settings_hash = ON_SHA1_Hash::EmptyContentHash;

  for (unsigned i = 0; i < m_levels.UnsignedCount(); ++i)
  {
    ON_SubDLevel* level = m_levels[i];
    if (nullptr != level)
    {
      m_levels[i] = nullptr;
      delete level;
    }
  }
  m_levels.SetCount(0);
  m_active_level = nullptr;
  m_heap.Clear();
  m_face_packing_id = ON_nil_uuid;
  m_face_packing_topology_hash = ON_SubDHash::Empty;
  m_symmetry = ON_Symmetry::Unset;
}

void  ON_SubDimple::ClearLevelContents(
  ON_SubDLevel* level
)
{
  if (nullptr == level)
    return;

  if (level == m_active_level)
    ChangeGeometryContentSerialNumber(false);

  level->ResetFaceArray();
  level->ResetEdgeArray();
  level->ResetVertexArray();

  ON_SubDVertex* next_vertex = level->m_vertex[0];
  level->m_vertex[0] = nullptr;
  level->m_vertex[1] = nullptr;

  ON_SubDEdge* next_edge = level->m_edge[0];
  level->m_edge[0] = nullptr;
  level->m_edge[1] = nullptr;

  ON_SubDFace* next_face = level->m_face[0];
  level->m_face[0] = nullptr;
  level->m_face[1] = nullptr;

  for (ON_SubDVertex* vertex = next_vertex; nullptr != vertex; vertex = next_vertex)
  {
    next_vertex = const_cast<ON_SubDVertex*>(vertex->m_next_vertex);
    ReturnVertex(vertex);
  }

  for (ON_SubDEdge* edge = next_edge; nullptr != edge; edge = next_edge)
  {
    next_edge = const_cast<ON_SubDEdge*>(edge->m_next_edge);
    ReturnEdge(edge);
  }

  for (ON_SubDFace* face = next_face; nullptr != face; face = next_face)
  {
    next_face = const_cast<ON_SubDFace*>(face->m_next_face);
    ReturnFace(face);
  }

}

unsigned int ON_SubDimple::ClearHigherSubdivisionLevels(
  unsigned int max_level_index
  )
{
  const unsigned int original_level_count = m_levels.UnsignedCount();

  if (max_level_index+1 < m_levels.UnsignedCount())
  {
    unsigned int level_count = m_levels.UnsignedCount();
    if (nullptr != m_active_level && m_active_level->m_level_index > max_level_index)
    {
      if ( level_count > max_level_index )
      {
        m_active_level = m_levels[max_level_index];
        ChangeGeometryContentSerialNumber(false);
      }
    }

    while (level_count > max_level_index+1)
    {
      const unsigned int level_index = (level_count-1);
      ON_SubDLevel* level = m_levels[level_index];
      m_levels[level_index] = nullptr;
      m_levels.Remove();
      level_count--;
      if (level_count != m_levels.UnsignedCount())
      {
        Clear();
        break;
      }

      if ( nullptr == level )
        continue;

      ClearLevelContents(level);

      delete level;
    }
  }

  return original_level_count - m_levels.UnsignedCount();
}


unsigned int ON_SubDimple::ClearLowerSubdivisionLevels(
  unsigned int min_level_index
  )
{
  const unsigned int original_level_count = m_levels.UnsignedCount();

  if (min_level_index > 0 && min_level_index < original_level_count)
  {
    if (nullptr != m_active_level && m_active_level->m_level_index < min_level_index)
    {
      m_active_level = m_levels[min_level_index];
      ChangeGeometryContentSerialNumber(false);
    }

    for ( unsigned int level_index = 0; level_index < min_level_index; level_index++)
    {
      ON_SubDLevel* level = m_levels[level_index];
      m_levels[level_index] = nullptr;
      if ( nullptr == level )
        continue;
      ClearLevelContents(level);
      delete level;
    }
    
    unsigned short new_level_index = 0;
    for (unsigned int level_index = min_level_index; level_index < original_level_count; level_index++, new_level_index++)
    {
      ON_SubDLevel* level = m_levels[level_index];
      m_levels[level_index] = nullptr;
      if ( nullptr == level )
        continue;
      level->m_level_index = new_level_index;

      for (ON_SubDVertex* vertex = level->m_vertex[0]; nullptr != vertex; vertex = const_cast<ON_SubDVertex*>(vertex->m_next_vertex))
      {
        vertex->SetSubdivisionLevel(new_level_index);
      }

      for (ON_SubDEdge* edge = level->m_edge[0]; nullptr != edge; edge = const_cast<ON_SubDEdge*>(edge->m_next_edge))
      {
        edge->SetSubdivisionLevel(new_level_index);
      }

      for (ON_SubDFace* face = level->m_face[0]; nullptr != face; face = const_cast<ON_SubDFace*>(face->m_next_face))
      {
        face->SetSubdivisionLevel(new_level_index);
        face->m_level_zero_face_id = face->m_id;
      }

      m_levels[new_level_index] = level;
    }
    m_levels.SetCount(new_level_index);
  }

  return original_level_count - m_levels.UnsignedCount();
}

unsigned int ON_SubDimple::ClearInactiveLevels()
{
  const unsigned active_level_index = this->ActiveLevelIndex();
  unsigned c1 = ClearHigherSubdivisionLevels(active_level_index);
  unsigned c0 = ClearLowerSubdivisionLevels(active_level_index);
  return c0 + c1;
}

void ON_SubDimple::Destroy()
{
  const unsigned int level_count = m_levels.Count();
  for (unsigned int level_index = 0; level_index < level_count; level_index++)
  {
    ON_SubDLevel* level = m_levels[level_index];
    if ( nullptr == level )
      continue;
    m_levels[level_index] = nullptr;
    delete level;
  }
  m_levels.Destroy();
  m_heap.Destroy();
  m_subd_geometry_content_serial_number = 0;
  m_subd_render_content_serial_number = 0;
}

ON_SubDLevel* ON_SubDimple::ActiveLevel(
  bool bCreateIfNeeded)
{
  if (nullptr == m_active_level)
  {
    unsigned int level_index = (m_levels.UnsignedCount() > 0) ? (m_levels.UnsignedCount()-1) : 0U;
    m_active_level = SubDLevel(level_index,bCreateIfNeeded && 0 == m_levels.UnsignedCount());    
    ChangeGeometryContentSerialNumber(false);
  }
  return m_active_level;
}

class ON_SubDLevel* ON_SubDimple::SubDLevel(
  unsigned int level_index,
  bool bCreateIfNeeded
  )
{
  ON_SubDLevel* level = nullptr;
  if (level_index < m_levels.UnsignedCount())
    level = m_levels[level_index];
  else if (bCreateIfNeeded && level_index == m_levels.UnsignedCount())
  {
    level = new ON_SubDLevel();
    level->m_level_index = level_index;
    m_levels.Append(level);
    if (nullptr == m_active_level)
    {
      m_active_level = level;
      ChangeGeometryContentSerialNumber(false);
    }
  }

  return level;
}

class ON_SubDLevel const * ON_SubDimple::SubDLevel(
  unsigned int level_index
  ) const
{
  if (level_index < m_levels.UnsignedCount())
    return m_levels[level_index];
  return nullptr;
}

void ON_SubDAggregates::UpdateBoundingBox(
  const ON_SubDLevel* level
  )
{
  ON_BoundingBox bbox = ON_BoundingBox::EmptyBoundingBox;
  if (nullptr != level)
  {
    double x;
    for (const ON_SubDVertex* v = level->m_vertex[0]; nullptr != v; v = v->m_next_vertex)
    {
      if (v->m_P[0] == v->m_P[0] && v->m_P[1] == v->m_P[1] && v->m_P[2] == v->m_P[2])
      {
        bbox.m_min.x = v->m_P[0];
        bbox.m_min.y = v->m_P[1];
        bbox.m_min.z = v->m_P[2];
        bbox.m_max.x = bbox.m_min.x;
        bbox.m_max.y = bbox.m_min.y;
        bbox.m_max.z = bbox.m_min.z;
        for (v = v->m_next_vertex; nullptr != v; v = v->m_next_vertex)
        {
          x = v->m_P[0];
          if (x < bbox.m_min.x) bbox.m_min.x = x; else if (x > bbox.m_max.x) bbox.m_max.x = x;
          x = v->m_P[1];
          if (x < bbox.m_min.y) bbox.m_min.y = x; else if (x > bbox.m_max.y) bbox.m_max.y = x;
          x = v->m_P[2];
          if (x < bbox.m_min.z) bbox.m_min.z = x; else if (x > bbox.m_max.z) bbox.m_max.z = x;
        }
        break;
      }
    }
  }
  m_controlnet_bbox = bbox;
  m_bDirtyBoundingBox = false;
}

ON_BoundingBox ON_SubDLevel::ControlNetBoundingBox() const
{
  if ( m_aggregates.m_bDirtyBoundingBox )
    m_aggregates.UpdateBoundingBox(this);
  return m_aggregates.m_controlnet_bbox;
}

void  ON_SubDAggregates::UpdateTopologicalAttributes(
  const ON_SubDLevel* level
)
{
  m_topological_attributes = 0;
  if (nullptr == level)
    return;

  if (m_bDirtyBoundingBox)
  {
    UpdateBoundingBox(level);
    if (m_bDirtyBoundingBox)
      return;
  }

  bool bIsManifold = level->m_edge_count >= 3 && level->m_face_count >= 1;
  bool bIsOriented = bIsManifold;
  bool bHasBoundary = false;

  for (const ON_SubDEdge* e = level->m_edge[0]; nullptr != e; e = e->m_next_edge)
  {
    if (1 == e->m_face_count)
    {
      bHasBoundary = true;
      if (false == bIsManifold && false == bIsOriented)
        break;
    }
    else if (2 == e->m_face_count)
    {
      if (ON_SUBD_FACE_DIRECTION(e->m_face2[0].m_ptr) == ON_SUBD_FACE_DIRECTION(e->m_face2[1].m_ptr))
      {
        bIsOriented = false;
        if (bHasBoundary && false == bIsManifold)
          break;
      }
    }
    else
    {
      bIsManifold = false;
      bIsOriented = false;
      if (bHasBoundary)
        break;
    }
  }

  double vol = 0.0;
  if (bIsManifold && bIsOriented && false == bHasBoundary)
  {
    const ON_3dVector B(m_controlnet_bbox.IsValid() ? ON_3dVector(m_controlnet_bbox.Center()) : ON_3dVector::ZeroVector);
    ON_3dVector P, Q, R;
    for (const ON_SubDFace* f = level->m_face[0]; nullptr != f && vol == vol; f = f->m_next_face)
    {
      if (false == f->GetSubdivisionPoint( &P.x))
      {
        vol = ON_DBL_QNAN;
        break;
      }
      P -= B;
      const unsigned count = f->EdgeCount();
      if (count < 3)
      {
        vol = ON_DBL_QNAN;
        break;
      }
      const ON_SubDVertex* v = f->Vertex(count - 1);
      if (nullptr == v || false == v->GetSubdivisionPoint( &R.x))
      {
        vol = ON_DBL_QNAN;
        break;
      }
      R -= B;
      for (unsigned fvi = 0; fvi < count; fvi++)
      {
        Q = R;
        v = f->Vertex(fvi);
        if (nullptr == v || false == v->GetSubdivisionPoint( &R.x))
        {
          vol = ON_DBL_QNAN;
          break;
        }
        R -= B;
        // ON_TripleProduct(P, Q, R) = 6x signed volume of tetrahedron with triangle base (P,Q,R) and apex B.
        vol += ON_TripleProduct(P, Q, R);
      }
    }
  }

  // bit 1 indicates m_topological_attributes is set.
  m_topological_attributes = 1;

  if (bIsManifold)
    m_topological_attributes |= 2;
  if (bIsOriented)
    m_topological_attributes |= 4;
  if (bHasBoundary)
    m_topological_attributes |= 8;
  
  if (vol > 0.0)
    m_topological_attributes |= 16;
  else if (vol < 0.0)
    m_topological_attributes |= 32;
}

bool ON_SubDAggregates::GetTopologicalAttributes(bool & bIsManifold, bool & bIsOriented, bool & bHasBoundary, int & solid_orientation) const
{
  // if m_bDirtyBoundingBox is true, then m_topological_attributes is dirty as well.
  const unsigned int topological_attributes = m_bDirtyBoundingBox ? 0U : m_topological_attributes;

  bIsManifold = 0 != (2 & topological_attributes);
  bIsOriented = 0 != (4 & topological_attributes);
  bHasBoundary = 0 != (8 & topological_attributes);
  if (bIsManifold && bIsOriented && false == bHasBoundary)
  {
    if (0 != (16 & topological_attributes))
      solid_orientation = 1;
    else if (0 != (32 & topological_attributes))
      solid_orientation = -1;
    else
      solid_orientation = 2;
  }
  else
    solid_orientation = 0;

  return (0 != topological_attributes);
}

bool ON_SubDAggregates::GetTopologicalAttributes(const ON_SubDLevel * level, bool &bIsManifold, bool & bIsOriented, bool & bHasBoundary, int & solid_orientation)
{
  if ( (m_bDirtyBoundingBox || 0 == m_topological_attributes) && nullptr != level)
    UpdateTopologicalAttributes(level);
  return GetTopologicalAttributes(bIsManifold, bIsOriented, bHasBoundary, solid_orientation);
}

const ON_AggregateComponentStatusEx ON_SubDLevel::AggregateComponentStatus() const
{
  if (false == m_aggregates.m_aggregate_status.IsCurrent())
    m_aggregates.UpdateAggregateComponentStatus(this);
  return m_aggregates.m_aggregate_status;
}

ON__UINT64 ON_SubDLevel::ComponentStatusSerialNumber() const
{
  return m_aggregates.m_aggregate_status.ComponentStatusSerialNumber();
}

void ON_SubDAggregates::UpdateAggregateEdgeAttributes(
  const ON_SubDLevel* level
  )
{
  if (nullptr != level)
  {
    unsigned int bits = 0;
    for (const ON_SubDEdge* e = level->m_edge[0]; nullptr != e; e = e->m_next_edge)
      bits |= e->EdgeAttributes();
    m_aggregate_edge_attributes = bits;
  }
  m_bDirtyEdgeAttributes = false;
}

unsigned int ON_SubDLevel::EdgeFlags() const
{
  if (m_aggregates.m_bDirtyEdgeAttributes)
    m_aggregates.UpdateAggregateEdgeAttributes(this);
  return m_aggregates.m_aggregate_edge_attributes;
}

unsigned int ON_SubD::AggregateEdgeAttributes() const
{
  return ActiveLevel().EdgeFlags();
}

void ON_SubDAggregates::UpdateAggregateComponentStatus(
  const ON_SubDLevel* level
  )
{
  m_aggregate_status = ON_AggregateComponentStatus::Empty;
  if (nullptr != level)
  {
    for (const ON_SubDVertex* v = level->m_vertex[0]; nullptr != v; v = v->m_next_vertex)
      m_aggregate_status.Add(v->m_status);
    for (const ON_SubDEdge* e = level->m_edge[0]; nullptr != e; e = e->m_next_edge)
      m_aggregate_status.Add(e->m_status);
    for (const ON_SubDFace* f = level->m_face[0]; nullptr != f; f = f->m_next_face)
      m_aggregate_status.Add(f->m_status);
  }
}


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDLevel
//

std::shared_ptr<const ON_SubDVertex*> ON_SubDLevel::VertexArray() const
{
  if (m_vertex_count != m_vertex_array_count || nullptr == m_vertex_array.get())
  {
    ON_SubDVertex const** a = new ON_SubDVertex const*[m_vertex_count];
    ON_SubDVertex const** a1 = a + m_vertex_count;
    const_cast<ON_SubDLevel*>(this)->m_vertex_array = std::shared_ptr<const ON_SubDVertex*>(a);
    for (const ON_SubDVertex* v = m_vertex[0]; nullptr != v && a < a1; v = v->m_next_vertex)
      *a++ = v;
    while (a < a1)
      *a++ = nullptr;
    const_cast<ON_SubDLevel*>(this)->m_vertex_array_count = m_vertex_count;
  }
  return m_vertex_array;
}

std::shared_ptr<const ON_SubDEdge*> ON_SubDLevel::EdgeArray() const
{
  if (m_edge_count != m_edge_array_count || nullptr == m_edge_array.get())
  {
    ON_SubDEdge const** a = new ON_SubDEdge const*[m_edge_count];
    ON_SubDEdge const** a1 = a + m_edge_count;
    const_cast<ON_SubDLevel*>(this)->m_edge_array = std::shared_ptr<const ON_SubDEdge*>(a);
    for (const ON_SubDEdge* v = m_edge[0]; nullptr != v && a < a1; v = v->m_next_edge)
      *a++ = v;
    while (a < a1)
      *a++ = nullptr;
    const_cast<ON_SubDLevel*>(this)->m_edge_array_count = m_edge_count;
  }
  return m_edge_array;
}

std::shared_ptr<const ON_SubDFace*> ON_SubDLevel::FaceArray() const
{
  if (m_face_count != m_face_array_count || nullptr == m_face_array.get())
  {
    ON_SubDFace const** a = new ON_SubDFace const*[m_face_count];
    ON_SubDFace const** a1 = a + m_face_count;
    const_cast<ON_SubDLevel*>(this)->m_face_array = std::shared_ptr<const ON_SubDFace*>(a);
    for (const ON_SubDFace* v = m_face[0]; nullptr != v && a < a1; v = v->m_next_face)
      *a++ = v;
    while (a < a1)
      *a++ = nullptr;
    const_cast<ON_SubDLevel*>(this)->m_face_array_count = m_face_count;
  }
  return m_face_array;
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubD::Transform
// ON_SubDimple::Transform
// ON_SubDLevel::Transform
// ON_SubDVertex::Transform
// ON_SubDEdge::Transform
// ON_SubDFace::Transform
//

static void TransformPoint(
  const double* xform,
  double P[3]
  )
{
  const double x = xform[0] * P[0] + xform[1] * P[1] + xform[2] * P[2] + xform[3];
  const double y = xform[4] * P[0] + xform[5] * P[1] + xform[6] * P[2] + xform[7];
  const double z = xform[8] * P[0] + xform[9] * P[1] + xform[10] * P[2] + xform[11];
  const double w = xform[12] * P[0] + xform[13] * P[1] + xform[14] * P[2] + xform[15];
  if (1.0 == w)
  {
    P[0] = x;
    P[1] = y;
    P[2] = z;
  }
  else
  {
    P[0] = x / w;
    P[1] = y / w;
    P[2] = z / w;
  }
}

static void TransformVector(
  const double* xform,
  double V[3]
  )
{
  const double x = xform[0] * V[0] + xform[1] * V[1] + xform[2] * V[2];
  const double y = xform[4] * V[0] + xform[5] * V[1] + xform[6] * V[2];
  const double z = xform[8] * V[0] + xform[9] * V[1] + xform[10] * V[2];
  V[0] = x;
  V[1] = y;
  V[2] = z;
}

bool ON_SubDSectorSurfacePoint::Transform(
  const ON_Xform& xform
  )
{
  TransformPoint(&xform.m_xform[0][0],m_limitP);
  TransformVector(&xform.m_xform[0][0],m_limitT1);
  TransformVector(&xform.m_xform[0][0],m_limitT2);
  ON_3dVector N = ON_CrossProduct(m_limitT1,m_limitT2);
  bool rc = N.Unitize();
  m_limitN[0] = N.x;
  m_limitN[1] = N.y;
  m_limitN[2] = N.z;
  return rc;
}

bool ON_SubDSectorSurfacePoint::Transform(
  const ON_Xform& xform,
  const ON_Xform& xformNormals
)
{
  TransformPoint(&xform.m_xform[0][0], m_limitP);
  TransformVector(&xform.m_xform[0][0], m_limitT1);
  TransformVector(&xform.m_xform[0][0], m_limitT2);
  TransformVector(&xformNormals.m_xform[0][0], m_limitN);
  return true;
}


bool ON_SubDVertex::Transform(
  bool bTransformationSavedSubdivisionPoint,
  const class ON_Xform& xform
  )
{
  TransformPoint(&xform.m_xform[0][0],m_P);

  if (bTransformationSavedSubdivisionPoint)
  {
    // Transform saved subdivision point
    Internal_TransformComponentBase(bTransformationSavedSubdivisionPoint, xform);

    // NOTE WELL:
    //   If the vertex 
    //     is tagged as ON_SubDVertexTag::Corner
    //     and bTransformationSavedSubdivisionPoint is true, 
    //     and the corner sector(s) contains interior smooth edges,
    //     and the transformation changes the angle between a corner sector's crease boundary, 
    //   then the sector's interior smooth edge's m_sector_coefficient[] could change
    //   and invalidate the subdivision points and limit points.
    //   This is only possible for uncommon (in practice) transformations
    //   and corner sectors and will require a fair bit of testing for 
    //   now it's easier to simply set bTransformationSavedSubdivisionPoint to false
    //   at a higher level when these types of transformations are encountered.
    if (bTransformationSavedSubdivisionPoint && Internal_SurfacePointFlag())
    {
      for (const ON_SubDSectorSurfacePoint* lp = &m_limit_point; nullptr != lp; lp = lp->m_next_sector_limit_point)
        const_cast<ON_SubDSectorSurfacePoint*>(lp)->Transform(xform);
    }
    else
      Internal_ClearSurfacePointFlag();
  }
  else
    this->ClearSavedSubdivisionPoints();

  return true;
}


bool ON_SubDVertex::Transform(
  bool bTransformationSavedSubdivisionPoint,
  const class ON_Xform& xform,
  const class ON_Xform& xformNormals
  )
{
  TransformPoint(&xform.m_xform[0][0],m_P);

  if (bTransformationSavedSubdivisionPoint)
  {
    // Transform saved subdivision point
    Internal_TransformComponentBase(bTransformationSavedSubdivisionPoint, xform);

    // NOTE WELL:
    //   If the vertex 
    //     is tagged as ON_SubDVertexTag::Corner
    //     and bTransformationSavedSubdivisionPoint is true, 
    //     and the corner sector(s) contains interior smooth edges,
    //     and the transformation changes the angle between a corner sector's crease boundary, 
    //   then the sector's interior smooth edge's m_sector_coefficient[] could change
    //   and invalidate the subdivision points and limit points.
    //   This is only possible for uncommon (in practice) transformations
    //   and corner sectors and will require a fair bit of testing for 
    //   now it's easier to simply set bTransformationSavedSubdivisionPoint to false
    //   at a higher level when these types of transformations are encountered.
    if (bTransformationSavedSubdivisionPoint && Internal_SurfacePointFlag())
    {
      for (const ON_SubDSectorSurfacePoint* lp = &m_limit_point; nullptr != lp; lp = lp->m_next_sector_limit_point)
        const_cast<ON_SubDSectorSurfacePoint*>(lp)->Transform(xform, xformNormals);
    }
    else
      Internal_ClearSurfacePointFlag();
  }
  else
    this->ClearSavedSubdivisionPoints();

  return true;
}

void ON_SubDVertex::UnsetControlNetPoint()
{
  m_P[0] = ON_DBL_QNAN;
  m_P[1] = ON_DBL_QNAN;
  m_P[2] = ON_DBL_QNAN;
  ClearSavedSubdivisionPoints();
  // With a nan control net point, there is no need for an expensive unset 
  // of the neighborhood because the caller will either later pass
  // bClearNeighborhoodCache=true to ON_SubDVertex::SetControlNetPoint(...,bClearNeighborhoodCache) 
  // or deal with cleaning up the cached evaluations in some other way.
}

bool ON_SubDVertex::SetControlNetPoint(
  ON_3dPoint control_net_point,
  bool bClearNeighborhoodCache
)
{
  if (false == control_net_point.IsValid())
    return false;

  if (false == (m_P[0] == control_net_point.x && m_P[1] == control_net_point.y && m_P[2] == control_net_point.z))
  {
    m_P[0] = control_net_point.x;
    m_P[1] = control_net_point.y;
    m_P[2] = control_net_point.z;
    ClearSavedSubdivisionPoints();

    for(;;)
    {
      if (false == bClearNeighborhoodCache)
        break;

      if (this->m_edge_count <= 0 || nullptr == this->m_edges)
        break;

      // need to clear 2 rings of faces around "this" vertex.

      const bool bThisVertexIsACorner = ON_SubDVertexTag::Corner == this->m_vertex_tag;
      for (unsigned short vei = 0; vei < this->m_edge_count; vei++)
      {
        const ON__UINT_PTR edgeptr = this->m_edges[vei].m_ptr;
        const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(edgeptr);
        if (nullptr == edge)
          continue;
        edge->ON_SubDComponentBase::Internal_ClearSubdivisionPointAndSurfacePointFlags();
        // v1 = vertex opposite this on edge
        const ON_SubDVertex* v1 = edge->m_vertex[1 - ON_SUBD_EDGE_DIRECTION(edgeptr)];
        if (nullptr == v1)
          continue;

        v1->ClearSavedSubdivisionPoints();

        if (ON_SubDVertexTag::Smooth != v1->m_vertex_tag)
          continue;
        if (false == bThisVertexIsACorner)
          continue;
        if (false == edge->IsSmooth())
          continue;
        // When a corner vertex is moved, the sector coefficients
        // for smooth edges can change because the corner sector
        // coefficient depends on the angle between the creases that
        // bound the sector. For any other tag, the sector
        // coefficients depend only on the topology and tags and
        // moving a control net point does not change those.
        edge->UnsetSectorCoefficientsForExperts();
      }

      if (this->m_face_count <= 0 || nullptr == this->m_faces)
        break;

      //const ON_SubDFace* face = this->m_faces[m_face_count - 1];
      for(unsigned short vfi = 0; vfi < m_face_count; vfi++)
      {
        //const ON_SubDFace* prevface = face;
        const ON_SubDFace* face = this->m_faces[vfi];
        if (nullptr == face)
          continue;

        // face->ON_SubDComponentBase::Internal_ClearSubdivisionPointAndSurfacePointFlags() is fast
        face->ON_SubDComponentBase::Internal_ClearSubdivisionPointAndSurfacePointFlags();

        const ON_SubDEdgePtr* face_eptr = face->m_edge4;
        for (unsigned short fei = 0; fei < face->m_edge_count; fei++, face_eptr++)
        {
          if (4 == fei)
          {
            face_eptr = face->m_edgex;
            if (nullptr == face_eptr)
              break;          
          }
          const ON__UINT_PTR e1ptr = face_eptr->m_ptr;
          ON_SubDEdge* e1 = ON_SUBD_EDGE_POINTER(e1ptr);
          if (nullptr == e1)
            continue;

          // e1->ON_SubDComponentBase::Internal_ClearSubdivisionPointAndSurfacePointFlags() is fast.
          // There is no need to unset e1 sector coefficients.
          e1->ON_SubDComponentBase::Internal_ClearSubdivisionPointAndSurfacePointFlags();
          const ON_SubDVertex* v1 = e1->m_vertex[ON_SUBD_EDGE_DIRECTION(e1ptr)];
          if (this == v1 || nullptr == v1)
            continue;
          v1->ClearSavedSubdivisionPoints();

          if (v1->m_edge_count <= 0 || nullptr == v1->m_edges)
            continue;
          for (unsigned short v1ei = 0; v1ei < v1->m_edge_count; v1ei++)
          {
            // e2 is sometime in ring 1, sometimes between ring 1 and 2, 
            // and sometimes in ring 2, but this is enough to clear the
            // ring 2 edges that can be modified by moving "this" vertex.
            const ON_SubDEdge* e2 = ON_SUBD_EDGE_POINTER(v1->m_edges[v1ei].m_ptr);
            if (nullptr != e2)
              e2->ON_SubDComponentBase::Internal_ClearSubdivisionPointAndSurfacePointFlags();
          }          
          
          if (v1->m_face_count <= 0 || nullptr == v1->m_faces)
            continue;
          for (unsigned short v1fi = 0; v1fi < v1->m_face_count; v1fi++)
          {
            // f2 is sometimes in ring 1 and sometimes in ring 2, but this
            // is enough to clear the ring 2 faces that can be modified by
            // moving "this" vertex.
            const ON_SubDFace* f2 = v1->m_faces[v1fi];
            if (nullptr != f2)
              f2->ON_SubDComponentBase::Internal_ClearSubdivisionPointAndSurfacePointFlags();
          }
        }
      }
      break;
    }
  }

  return true;
}

void ON_SubDComponentBase::Internal_TransformComponentBase(
  bool bTransformationSavedSubdivisionPoint,
  const class ON_Xform& xform
  )
{
  if ( SavedSubdivisionPointIsSet() )
  {
    if (bTransformationSavedSubdivisionPoint)
      TransformPoint(&xform.m_xform[0][0], m_saved_subd_point1);
    else
      ON_SUBD_CACHE_CLEAR_POINT_FLAG(m_saved_points_flags);
  }
}

bool ON_SubDEdge::Transform(
  bool bTransformationSavedSubdivisionPoint,
  const class ON_Xform& xform
  )
{
  Internal_TransformComponentBase(bTransformationSavedSubdivisionPoint, xform);

    Internal_ClearSurfacePointFlag();

  return true;
}

bool ON_SubDFace::Transform(
  bool bTransformationSavedSubdivisionPoint,
  const class ON_Xform& xform
  )
{
  ON_Xform xformNormals{ ON_Xform::IdentityTransformation };
  const double det{ xform.GetSurfaceNormalXformKeepLengthAndOrientation(xformNormals) };
  ON_Xform xformCurvatures{ ON_Xform::IdentityTransformation };
  if (abs(det) > 0) {
    if (abs(abs(det) - 1) > ON_SQRT_EPSILON)
    {
      xformCurvatures = ON_Xform::DiagonalTransformation(pow(det, -1. / 3.));
    }
  }
  else {
    return ON_SUBD_RETURN_ERROR(false);
  }
  const bool bKeepCurvatures{ xform.IsSimilarity() != 0 };
  const bool bKeepTextures{ true };
  const bool bKeepColors{ xform.IsRigid() != 0 };


  // bTransformationSavedSubdivisionPoint = true should mean that
  // xform is a similarity.
  // If it's more complicated than this, the calling code should
  // reset or adjust colors as needed based on information in the
  // SubD's texture coordinate mapping tag and color mapping tag.
  // Note that both of those tags have their transformation updated
  // so intelligent decisions can be made at a higher level where
  // there is enough context to make the correct decision.
  return Transform(bTransformationSavedSubdivisionPoint, bKeepCurvatures, bKeepTextures, bKeepColors, xform, xformNormals, xformCurvatures, ON_Xform::IdentityTransformation, ON_Xform::IdentityTransformation);
}

bool ON_SubDFace::Transform(
  bool bTransformationSavedSubdivisionPoint,
  bool bKeepCurvatures,
  bool bKeepTextures,
  bool bKeepColors,
  const ON_Xform& xform,
  const ON_Xform& xformNormals,
  const ON_Xform& xformCurvatures,
  const ON_Xform& xformTextures,
  const ON_Xform& xformColors
  )
{
  if (bTransformationSavedSubdivisionPoint)
  {
    Internal_TransformComponentBase(true, xform);

    if (Internal_SurfacePointFlag())
    {
      for (ON_SubDMeshFragment* f = m_mesh_fragments; nullptr != f; f = f->m_next_fragment)
        f->Transform(bKeepCurvatures, bKeepTextures, bKeepColors, xform, xformNormals, xformCurvatures, xformTextures, xformColors);
    }
    else
      Internal_ClearSurfacePointFlag();
  }
  else
    this->ClearSavedSubdivisionPoints();

  return true;
}

bool ON_SubDLevel::Transform(
  bool bTransformationSavedSubdivisionPoint,
  const class ON_Xform& xform
  )    
{
  bool rc = true;
  ON_Xform xformNormals{ ON_Xform::IdentityTransformation };
  const double det{ xform.GetSurfaceNormalXformKeepLengthAndOrientation(xformNormals) };
  ON_Xform xformCurvatures{ ON_Xform::IdentityTransformation };
  if (abs(det) > 0) {
    if (abs(abs(det) - 1) > ON_SQRT_EPSILON)
    {
      xformCurvatures = ON_Xform::DiagonalTransformation(pow(det, -1. / 3.));
    }
  }
  else {
    rc = false;
  }
  const bool bKeepCurvatures{ xform.IsSimilarity() != 0 };
  const bool bKeepTextures{ true };
  const bool bKeepColors{ xform.IsRigid() != 0 };

  m_aggregates.m_bDirtyBoundingBox = true;

  for (const ON_SubDVertex* vertex = m_vertex[0]; nullptr != vertex; vertex = vertex->m_next_vertex)
  {
    if (false == const_cast<ON_SubDVertex*>(vertex)->Transform(bTransformationSavedSubdivisionPoint, xform, xformNormals))
      rc = false;
  }
  
  for (const ON_SubDEdge* edge = m_edge[0]; nullptr != edge; edge = edge->m_next_edge)
  {
    if (false == const_cast<ON_SubDEdge*>(edge)->Transform(bTransformationSavedSubdivisionPoint, xform))
      rc = false;
  }
  
  for (const ON_SubDFace* face = m_face[0]; nullptr != face; face = face->m_next_face)
  {
    if (false == const_cast<ON_SubDFace*>(face)->Transform(
      bTransformationSavedSubdivisionPoint, bKeepCurvatures, bKeepTextures, bKeepColors,
      xform, xformNormals, xformCurvatures, ON_Xform::IdentityTransformation, ON_Xform::IdentityTransformation
    ))
      rc = false;
  }

  if (false == m_surface_mesh.Transform(
    bKeepCurvatures, bKeepTextures, bKeepColors,
    xform, xformNormals, xformCurvatures, ON_Xform::IdentityTransformation, ON_Xform::IdentityTransformation
  ))
    rc = false;
  
  if (false == m_control_net_mesh.Transform(
    bKeepCurvatures, bKeepTextures, bKeepColors,
    xform, xformNormals, xformCurvatures, ON_Xform::IdentityTransformation, ON_Xform::IdentityTransformation
  ))
    rc = false;

  if (rc)
    return true;

  return ON_SUBD_RETURN_ERROR(false);
}


bool ON_SubDMesh::Transform(
  const ON_Xform& xform
  )
{
  if (false == xform.IsValid())
    return false;
  if (xform.IsIdentity())
    return true;
  if (xform.IsZero())
    return false;
  ON_SubDMeshImpl* impl = m_impl_sp.get();
  if ( nullptr == impl )
    return true; // transform applied to empty mesh is true on purpose.  Changing to false will break other code.
  return impl->Transform(xform);
}


bool ON_SubDMesh::Transform(
  bool bKeepCurvatures,
  bool bKeepTextures,
  bool bKeepColors,
  const ON_Xform& xform,
  const ON_Xform& xformNormals,
  const ON_Xform& xformCurvatures,
  const ON_Xform& xformTextures,
  const ON_Xform& xformColors
  )
{
  if (false == xform.IsValid())
    return false;
  if (xform.IsIdentity())
    return true;
  if (xform.IsZero())
    return false;
  ON_SubDMeshImpl* impl = m_impl_sp.get();
  if ( nullptr == impl )
    return true; // transform applied to empty mesh is true on purpose.  Changing to false will break other code.
  return impl->Transform(bKeepCurvatures, bKeepTextures, bKeepColors, xform, xformNormals, xformCurvatures, xformTextures, xformColors);
}

bool ON_SubDimple::Transform(
  const ON_Xform& xform
  )
{
  const bool bSymmetricInput = m_symmetry.SameSymmetricObjectGeometry(this);
  const ON_Symmetry symmetry0 = m_symmetry;
  const ON__UINT64 gsn0 = this->GeometryContentSerialNumber();

  const bool bUpdateFacePackingHash
    = m_face_packing_topology_hash.m_subd_geometry_content_serial_number == gsn0
    && m_face_packing_topology_hash.IsNotEmpty()
    && m_face_packing_topology_hash.SubDHash() == this->SubDHash(ON_SubDHashType::TopologyAndEdgeCreases, false).SubDHash()
    ;


  if (false == xform.IsValid())
    return false;
  if (xform.IsZero())
    return true;
  if (xform.IsIdentity())
    return true;

  const unsigned int level_count = m_levels.UnsignedCount();
  if ( level_count <= 0 )
    return true; // transform applied to empty subd is true on purpose.

  bool rc = true;

  // If 
  // 1) The transformation is being applied to every vertex, edge and 
  //    face in every level of a subdivision object, and
  // 2) the transformation is an isometry (rotation, translation, mirror, ...),
  //   a uniform scale, or a composition of these types, 
  // then set bTransformationSavedSubdivisionPoint = true to apply the
  // transformation to saved subdivision and saved limit point information.
  // In all other cases, set bTransformationSavedSubdivisionPoint = false
  // and any saved subdivision points or saved limit points will be
  // deleted.
  const bool bTransformationSavedSubdivisionPoint = (0 != xform.IsSimilarity());

  bool bHasTextures = false;
  bool bHasColors = false;

  for (unsigned int level_index = 0; level_index < level_count; level_index++)
  {
    ON_SubDLevel* level = m_levels[level_index];
    if (nullptr == level)
    {
      ON_SubDIncrementErrorCount();
      continue;
    }

    if (false == level->Transform(bTransformationSavedSubdivisionPoint, xform))
    {
      rc = false;
      break;
    }

    if (level->m_face_count > 0 && level->m_face[0])
    {
      const ON_SubDMeshFragment* frag = level->m_face[0]->MeshFragments();
      if (nullptr != frag)
      {
        if (frag->TextureCoordinateCount() > 0)
          bHasTextures = true;
        if (frag->ColorCount() > 0)
          bHasColors = true;
      }
    }
  }

  if (bHasTextures)
    this->m_texture_mapping_tag.Transform(xform);
  if (bHasColors)
    this->m_colors_mapping_tag.Transform(xform);

  // SubD has been moved - geometry changed and we need to bump the geometry content serial number.
  this->ChangeGeometryContentSerialNumber(false);

  // GeometryContentSerial number trackers need to be updated
  // so the SubD knows its status with respect to the 
  // newly transformed geometry.

  if (bUpdateFacePackingHash)
    m_face_packing_topology_hash = this->SubDHash(ON_SubDHashType::TopologyAndEdgeCreases, false);

  if (m_symmetry.IsSet())
  {
    m_symmetry = m_symmetry.TransformConditionally(xform);
    bool bSymmetricOutput = false;
    if (bSymmetricInput)
    {
      // see if the transformed object will still be symmetric.
      if (ON_Symmetry::Coordinates::Object == m_symmetry.SymmetryCoordinates())
      {
        // object is still symmetric.
        bSymmetricOutput = true;
      }
      else if (ON_Symmetry::Coordinates::World == m_symmetry.SymmetryCoordinates())
      {
        // if transform didn't move the symmetry
        if ( 0 == ON_Symmetry::CompareSymmetryTransformation(&symmetry0, &m_symmetry, ON_UNSET_VALUE) )
          bSymmetricOutput = true;
      }
    }
    if (bSymmetricOutput)
    {
      if (ON_Symmetry::Coordinates::Object == m_symmetry.SymmetryCoordinates())
      {
        // symmetry constraints transformed with object
        m_symmetry.SetSymmetricObject(this);
      }
      else
      {
        // object moved with respect to symmetry constraints
        // DO NOTHING HERE - the serial number and hashes on m_symmetry will inform downstream processes
        // that the object no longer has the symmetry property specified by m_symmetry.
        // It will get updated when appropriate - typically in replace object.
        // EXAMPLE: Make a SubD plane - reflect it across the world Y axis. 
        // Then rotate the plane a bit. The rotated plane gets fixed in replace object.
      }
    }
    else
    {
      // input was already dirty - remove all object settings from m_symmetry.
      m_symmetry.ClearSymmetricObject();
    }
  }
  else
  {
    m_symmetry = ON_Symmetry::Unset;
  }

  return rc;
}

bool ON_SubDMeshFragment::Transform(
  const ON_Xform& xform
)
{
  const bool bKeepCurvatures{ xform.IsSimilarity() != 0 };
  const bool bKeepTextures{ true };
  const bool bKeepColors{ xform.IsRigid() != 0 };
  return this->Transform(bKeepCurvatures, bKeepTextures, bKeepColors, xform);
}

bool ON_SubDMeshFragment::Transform(
  bool bKeepCurvatures,
  bool bKeepTextures,
  bool bKeepColors,
  const ON_Xform& xform
)
{
  ON_Xform xformNormals{ON_Xform::IdentityTransformation};
  const double det{ xform.GetSurfaceNormalXformKeepLengthAndOrientation(xformNormals) };
  ON_Xform xformCurvatures{ON_Xform::IdentityTransformation};
  if (abs(det) > 0) {
    if (abs(abs(det) - 1) > ON_SQRT_EPSILON)
    {
      xformCurvatures = ON_Xform::DiagonalTransformation(pow(det, -1. / 3.));
    }
  }
  else {
    return ON_SUBD_RETURN_ERROR(false);
  }

  return this->Transform(
    bKeepCurvatures, bKeepTextures, bKeepColors,
    xform, xformNormals, xformCurvatures, ON_Xform::IdentityTransformation, ON_Xform::IdentityTransformation
  );
}

bool ON_SubDMeshFragment::Transform(
  bool bKeepCurvatures,
  bool bKeepTextures,
  bool bKeepColors,
  const ON_Xform& xform,
  const ON_Xform& xformNormals,
  const ON_Xform& xformCurvatures,
  const ON_Xform& xformTextures,
  const ON_Xform& xformColors

)
{
  const unsigned count = PointCount();
  if (0 == count)
  {
    m_surface_bbox = ON_BoundingBox::EmptyBoundingBox;
    return true;
  }
  if ( false == ON_TransformPointList(3,false, count,(int)m_P_stride,m_P,xform) )
    return ON_SUBD_RETURN_ERROR(false);
  if (count == NormalCount())
  {
    if (false == ON_TransformVectorList(3, count, (int)m_N_stride, m_N, xformNormals))
      return ON_SUBD_RETURN_ERROR(false);
  }
  if (0 != (ON_SubDMeshFragment::EtcControlNetQuadBit & m_vertex_count_etc))
  {
    for (int i = 0; i < 4; i++)
    {
      const ON_3dPoint A(m_ctrlnetP[i]);
      if (A.IsValid())
      {
        const ON_3dPoint B = xform * A;
        m_ctrlnetP[i][0] = B.x;
        m_ctrlnetP[i][1] = B.y;
        m_ctrlnetP[i][2] = B.z;
      }
    }
  }
  // Pierre, 2023-04-13: This was wrongly looking at ON_SubDMeshFragment::EtcControlNetQuadBit & m_vertex_capacity_etc)
  // That is actually already defined for the EtcManagedArraysBit
  if (0 != (ON_SubDMeshFragment::EtcControlNetQuadBit & m_vertex_count_etc))
  {
    const ON_3dVector A(m_ctrlnetN);
    if (A.IsNotZero())
    {
      ON_3dVector B = xformNormals * A;
      m_ctrlnetN[0] = B.x;
      m_ctrlnetN[1] = B.y;
      m_ctrlnetN[2] = B.z;
    }
  }
  ON_GetPointListBoundingBox(3,0,count,(int)m_P_stride,m_P,&m_surface_bbox.m_min.x,&m_surface_bbox.m_max.x,false);

  if (TextureCoordinatesExistForExperts()) {
    this->SetTextureCoordinatesExistForExperts(bKeepTextures);
    if (bKeepTextures) {
      if (xformTextures.IsNotIdentity()) {
        double* p = &this->m_ctrlnetT[0][0];
        constexpr unsigned dim = sizeof(this->m_ctrlnetT[0]) / sizeof(this->m_ctrlnetT[0][0]);
        constexpr unsigned tcount = sizeof(this->m_ctrlnetT) / sizeof(this->m_ctrlnetT[0]);
        if (false == ON_TransformPointList(dim, false, tcount, dim, p, xformTextures))
          return ON_SUBD_RETURN_ERROR(false);
      }
    }
    else {
      double* p = &this->m_ctrlnetT[0][0];
      const double* p1 = p + sizeof(this->m_ctrlnetT) / sizeof(this->m_ctrlnetT[0][0]);
      while (p < p1)
        *p++ = ON_DBL_QNAN;
    }
  }

  if (CurvaturesExistForExperts()) {
    this->SetCurvaturesExistForExperts(bKeepCurvatures);
    if (bKeepCurvatures) {
      if (xformCurvatures.IsNotIdentity()) {
        constexpr unsigned dim{sizeof(ON_SurfaceCurvature) / sizeof(double)};
        constexpr unsigned ccount{sizeof(m_ctrlnetK) / sizeof(m_ctrlnetK[0])};
        if (false == ON_TransformVectorList(dim, ccount, dim, (double*)m_ctrlnetK, xformCurvatures))
          return ON_SUBD_RETURN_ERROR(false);
      }
    }
    else {
      this->m_ctrlnetK[0] = ON_SurfaceCurvature::Nan;
      this->m_ctrlnetK[1] = ON_SurfaceCurvature::Nan;
      this->m_ctrlnetK[2] = ON_SurfaceCurvature::Nan;
      this->m_ctrlnetK[3] = ON_SurfaceCurvature::Nan;
    }
  }

  if (ColorsExistForExperts()) {
    this->SetColorsExistForExperts(bKeepColors);
    if (bKeepColors) {
      if (xformColors.IsNotIdentity()) {
        for (int i = 0; i < 4; ++i) {
          ON_Color& color{ m_ctrlnetC[i] };
          ON_4dPoint rgba{ (double)color.Red(), (double)color.Green(), (double)color.Blue(), (double)color.Alpha() };
          rgba.Transform(xformColors);
          m_ctrlnetC->SetRGBA((int)rgba[0], (int)rgba[1], (int)rgba[2], (int)rgba[3]);
        }
      }
    }
    else {
      this->m_ctrlnetC[0] = ON_Color::UnsetColor;
      this->m_ctrlnetC[1] = ON_Color::UnsetColor;
      this->m_ctrlnetC[2] = ON_Color::UnsetColor;
      this->m_ctrlnetC[3] = ON_Color::UnsetColor;
    }
  }

  return true;
}

bool ON_SubDMeshImpl::Transform(
  const ON_Xform& xform
  )
{
  m_bbox = ON_BoundingBox::EmptyBoundingBox;
  ON_BoundingBox bbox = ON_BoundingBox::EmptyBoundingBox;
  for (const ON_SubDMeshFragment* fragment = m_first_fragment; nullptr != fragment; fragment = fragment->m_next_fragment)
  {
    if (false == const_cast<ON_SubDMeshFragment*>(fragment)->Transform(xform))
      return ON_SUBD_RETURN_ERROR(false);
    if (fragment == m_first_fragment)
      bbox = fragment->m_surface_bbox;
    else
      bbox.Union(fragment->m_surface_bbox);
  }
  m_bbox = bbox;
  ChangeContentSerialNumber();
  return true;
}

bool ON_SubDMeshImpl::Transform(
  bool bKeepCurvatures,
  bool bKeepTextures,
  bool bKeepColors,
  const ON_Xform& xform,
  const ON_Xform& xformNormals,
  const ON_Xform& xformCurvatures,
  const ON_Xform& xformTextures,
  const ON_Xform& xformColors
  )
{
  //const bool bIsometry = (1 == xform.IsRigid()); // silence unused variable warning
  m_bbox = ON_BoundingBox::EmptyBoundingBox;
  ON_BoundingBox bbox = ON_BoundingBox::EmptyBoundingBox;
  for ( const ON_SubDMeshFragment* fragment = m_first_fragment; nullptr != fragment; fragment = fragment->m_next_fragment)
  {
    if ( false == const_cast<ON_SubDMeshFragment*>(fragment)->Transform(
      bKeepCurvatures, bKeepTextures, bKeepColors,
      xform, xformNormals, xformCurvatures, xformTextures, xformColors
    ) )
      return ON_SUBD_RETURN_ERROR(false);
    if ( fragment == m_first_fragment )
      bbox = fragment->m_surface_bbox;
    else
      bbox.Union(fragment->m_surface_bbox);
  }
  m_bbox = bbox;
  ChangeContentSerialNumber();
  return true;
}

//////////////////////////////////////////////////////////////////////////
//
//
//
//

ON_BoundingBox ON_SubDVertex::ControlNetBoundingBox() const
{
  ON_BoundingBox bbox;
  bbox.m_min = m_P;
  bbox.m_max = bbox.m_min;
  return bbox;
}



const ON_BoundingBox ON_SubDEdge::ControlNetBoundingBox() const
{
  ON_BoundingBox bbox;
  if (nullptr != m_vertex[0] && nullptr != m_vertex[1])
  {
    ON_3dPoint P[2];
    P[0] = m_vertex[0]->m_P;
    P[1] = m_vertex[1]->m_P;
    ON_GetPointListBoundingBox(3, 0, 2, 3, &P[0].x, &bbox.m_min.x, &bbox.m_max.x,false);
  }
  return bbox;
}

const ON_BoundingBox ON_SubDFace::ControlNetBoundingBox() const
{
  ON_BoundingBox bbox;
  ON_3dPoint P[16];
  unsigned int P_count = 0;
  const unsigned int P_capacity = (unsigned int)(sizeof(P) / sizeof(P[0]));
  bool bGrowBox = false;

  const unsigned int count = m_edge_count;
  for (unsigned int i = 0; i < count; i++)
  {
    const ON_SubDVertex* vertex = Vertex(i);
    if (nullptr == vertex)
      continue;
    P[P_count++] = vertex->m_P;
    if (P_count == P_capacity)
    {
      ON_GetPointListBoundingBox(3, 0, P_count, 3, &P[0].x, &bbox.m_min.x, &bbox.m_max.x, bGrowBox);
      P_count = 0;
      bGrowBox = true;
    }
  }

  if ( P_count > 0)
    ON_GetPointListBoundingBox(3, 0, P_count, 3, &P[0].x, &bbox.m_min.x, &bbox.m_max.x, bGrowBox);

  return bbox;
}

const ON_SHA1_Hash ON_SubDVertex::TopologyHash(bool bIncludeSubdivisionProperties) const
{
  ON_SHA1 sha1;
  sha1.AccumulateInteger32(m_id);
  if (bIncludeSubdivisionProperties)
  {
    sha1.AccumulateBytes(&this->m_vertex_tag, sizeof(this->m_vertex_tag));
    sha1.AccumulateDoubleArray(3, this->m_P);
  }

  if (this->IsCreaseOrCorner())
    bIncludeSubdivisionProperties = false;

  if (nullptr != this->m_edges)
  {
    sha1.AccumulateInteger16(m_edge_count);
    for (unsigned short vei = 0; vei < m_edge_count; ++vei)
    {
      const ON_SubDEdgePtr eptr = this->m_edges[vei];
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
      if (nullptr == e)
      {
        sha1.AccumulateInteger32(ON_UNSET_UINT_INDEX);
      }
      else
      {
        sha1.AccumulateInteger32(e->m_id);
        sha1.AccumulateInteger32((ON__UINT32)ON_SUBD_EDGE_DIRECTION(eptr.m_ptr));
        if (bIncludeSubdivisionProperties)
        {
          // passing true here includes the edge tag in the hash.
          const ON_SubDEdgeSharpness s = eptr.RelativeSharpness(true);
          sha1.AccumulateDouble(s[0]);
          sha1.AccumulateDouble(s[1]);
        }
      }
    }
  }

  if (nullptr != this->m_faces)
  {
    sha1.AccumulateInteger16(m_face_count);
    for (unsigned short vfi = 0; vfi < m_face_count; ++vfi)
    {
      const ON_SubDFace* f = this->m_faces[vfi];
      sha1.AccumulateInteger32(nullptr == f ? ON_UNSET_UINT_INDEX : f->m_id);
    }
  }

  return sha1.Hash();
}

ON__UINT32 ON_SubDVertex::TopologyCRC32(bool bIncludeSubdivisionProperties) const
{
  return this->TopologyHash(bIncludeSubdivisionProperties).CRC32(0);
}

const ON_SHA1_Hash ON_SubDEdge::TopologyHash(bool bIncludeSubdivisionProperties) const
{
  ON_SHA1 sha1;
  sha1.AccumulateInteger32(m_id);
  if (bIncludeSubdivisionProperties)
  {
    // passing true here includes the edge tag in the hash.
    const ON_SubDEdgeSharpness s = this->Sharpness(true);
    sha1.AccumulateDouble(s[0]);
    sha1.AccumulateDouble(s[1]);
  }
  for (unsigned evi = 0; evi < 2; ++evi)
  {
    const ON_SubDVertex* v = this->m_vertex[evi];    
    if (nullptr == v)
      sha1.AccumulateInteger32(ON_UNSET_UINT_INDEX);
    else
    {
      sha1.AccumulateInteger32(v->m_id);
      if (bIncludeSubdivisionProperties)
      {
        sha1.AccumulateDoubleArray(3, v->m_P);
        if (v->IsDartOrCreaseOrCorner())
          sha1.AccumulateDouble(this->m_sector_coefficient[evi]);
      }
    }
  }

  sha1.AccumulateInteger16(this->m_face_count);
  const ON_SubDFacePtr* ef = this->m_face2;
  for (unsigned short efi = 0; efi < this->m_face_count; ++efi)
  {
    if (2 == efi)
    {
      ef = this->m_facex;
      if (nullptr == ef)
      {
        while (efi < this->m_face_count)
        {
          sha1.AccumulateInteger32(ON_UNSET_UINT_INDEX);
          ++efi;
        }
        break;
      }
    }
    const ON_SubDFacePtr fptr = *ef++;
    const ON_SubDFace* f = ON_SUBD_FACE_POINTER(fptr.m_ptr);
    if (nullptr == f)
    {
      sha1.AccumulateInteger32(ON_UNSET_UINT_INDEX);
    }
    else
    {
      sha1.AccumulateInteger32(f->m_id);
      sha1.AccumulateInteger32((ON__UINT32)ON_SUBD_FACE_DIRECTION(fptr.m_ptr));
    }
  }

  return sha1.Hash();
}

ON__UINT32 ON_SubDEdge::TopologyCRC32(bool bIncludeSubdivisionProperties) const
{
  return this->TopologyHash(bIncludeSubdivisionProperties).CRC32(0);
}

const ON_SHA1_Hash ON_SubDFace::TopologyHash(bool bIncludeSubdivisionProperties) const
{
  ON_SHA1 sha1;
  sha1.AccumulateInteger32(m_id);

  const ON_SubDEdgePtr* fe = m_edge4;
  for (unsigned short fei = 0; fei < m_edge_count; ++fei)
  {
    if (4 == fei)
    {
      fe = m_edgex;
      if (nullptr == fe)
      {
        while (fei < this->m_edge_count)
        {
          sha1.AccumulateInteger32(ON_UNSET_UINT_INDEX);
          ++fei;
        }
        break;
      }
    }

    const ON_SubDEdgePtr eptr = *fe++;
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
    if (nullptr == e)
    {
      sha1.AccumulateInteger32(ON_UNSET_UINT_INDEX);
    }
    else
    {
      sha1.AccumulateInteger32(e->m_id);
      const unsigned evi = (unsigned)ON_SUBD_EDGE_DIRECTION(eptr.m_ptr);
      sha1.AccumulateInteger32(evi);
      const ON_SubDVertex* v = e->m_vertex[evi];
      if (nullptr == v)
        sha1.AccumulateInteger32(ON_UNSET_UINT_INDEX);
      else
      {
        sha1.AccumulateInteger32(v->m_id);
        if (bIncludeSubdivisionProperties)
          sha1.AccumulateDoubleArray(3, v->m_P);
      }
    }
  }

  return sha1.Hash();
}

ON__UINT32 ON_SubDFace::TopologyCRC32(bool bIncludeSubdivisionProperties) const
{
  return this->TopologyHash(bIncludeSubdivisionProperties).CRC32(0);
}

bool ON_Symmetry::SameSymmetricObjectGeometry(const class ON_SubD* subd) const
{
  const ON_SubDimple* subdimple = (nullptr != subd) ? subd->SubDimple() : nullptr;
  return SameSymmetricObjectGeometry(subdimple);
}

bool ON_Symmetry::SameSymmetricObjectTopology(const class ON_SubD* subd) const
{
  const ON_SubDimple* subdimple = (nullptr != subd) ? subd->SubDimple() : nullptr;
  return SameSymmetricObjectTopology(subdimple);
}

bool ON_Symmetry::SameSymmetricObjectGeometry(const class ON_SubDimple* subdimple) const
{
  if (this->IsSet() && m_symmetric_object_content_serial_number != 0 && nullptr != subdimple)
  {
    const ON__UINT64 subd_gsn = subdimple->GeometryContentSerialNumber();
    if (m_symmetric_object_content_serial_number == subd_gsn)
      return true; // speedy check worked
    if (m_symmetric_object_geometry_hash.IsSet() && m_symmetric_object_geometry_hash == subdimple->SubDHash(ON_SubDHashType::Geometry, false).SubDHash())
      return true;
  }
  return false;
}

bool ON_Symmetry::SameSymmetricObjectTopology(const class ON_SubDimple* subdimple) const
{
  if (this->IsSet() && m_symmetric_object_content_serial_number != 0 && nullptr != subdimple)
  {
    const ON__UINT64 subd_gsn = subdimple->GeometryContentSerialNumber();
    if (m_symmetric_object_content_serial_number == subd_gsn)
      return true; // speedy check worked (same geometry in fact!)
    if (m_symmetric_object_topology_hash.IsSet() && m_symmetric_object_topology_hash == subdimple->SubDHash(ON_SubDHashType::Topology, false).SubDHash())
      return true;
  }
  return false;
}
