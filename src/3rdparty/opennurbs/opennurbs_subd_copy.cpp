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

unsigned int ON_SubDArchiveIdMap::ArchiveIdFromComponentPtr(ON__UINT_PTR ptr)
{
  return (unsigned int)(ptr/(ON_SUBD_COMPONENT_FLAGS_MASK+1));
}

const ON_SubDComponentPtr ON_SubDArchiveIdMap::FromVertex(
  const ON_SubDVertex* vertex
  )
{
  ON__UINT_PTR archive_id = (nullptr == vertex) ? 0 : vertex->ArchiveId();
  return ON_SubDComponentPtr::Create((const ON_SubDVertex*)(archive_id*(ON_SUBD_COMPONENT_FLAGS_MASK+1)));
}

const ON_SubDComponentPtr ON_SubDArchiveIdMap::FromEdge(
  const ON_SubDEdge* edge
  )
{
  ON__UINT_PTR archive_id = (nullptr == edge) ? 0 : edge->ArchiveId();
  return ON_SubDComponentPtr::Create((const ON_SubDEdge*)(archive_id*(ON_SUBD_COMPONENT_FLAGS_MASK+1)));
}

const ON_SubDComponentPtr ON_SubDArchiveIdMap::FromFace(
  const ON_SubDFace* face
  )
{
  ON__UINT_PTR archive_id = (nullptr == face) ? 0 : face->ArchiveId();
  return ON_SubDComponentPtr::Create((const ON_SubDFace*)(archive_id*(ON_SUBD_COMPONENT_FLAGS_MASK+1)));
}

const ON_SubDComponentPtr ON_SubDArchiveIdMap::FromVertex(
  ON_SubDVertexPtr vertex_ptr
  )
{
  ON_SubDComponentPtr ptr = FromVertex(vertex_ptr.Vertex());
  ptr.m_ptr |= vertex_ptr.VertexDirection();
  return ptr;
}

const ON_SubDComponentPtr ON_SubDArchiveIdMap::FromEdge(
  ON_SubDEdgePtr edge_ptr
  )
{
  ON_SubDComponentPtr ptr = FromEdge(edge_ptr.Edge());
  ptr.m_ptr |= edge_ptr.EdgeDirection();
  return ptr;
}

const ON_SubDComponentPtr ON_SubDArchiveIdMap::FromFace(
  ON_SubDFacePtr face_ptr
  )
{
  ON_SubDComponentPtr ptr = FromFace(face_ptr.Face());
  ptr.m_ptr |= face_ptr.FaceDirection();
  return ptr;
}

const ON_SubDComponentPtr ON_SubDArchiveIdMap::FromSymmetrySetNext(
  ON_SubDComponentPtr::Type component_type,
  const ON_SubDComponentBase* component
)
{
  if (nullptr == component)
    return ON_SubDComponentPtr::Null;

  ON_SubDComponentPtr cptr;
  switch (component_type)
  {
  case ON_SubDComponentPtr::Type::Vertex:
    cptr = ON_SubDArchiveIdMap::FromVertex(component->m_symmetry_set_next.Vertex());
    break;
  case ON_SubDComponentPtr::Type::Edge:
    cptr = ON_SubDArchiveIdMap::FromEdge(component->m_symmetry_set_next.Edge());
    break;
  case ON_SubDComponentPtr::Type::Face:
    cptr = ON_SubDArchiveIdMap::FromFace(component->m_symmetry_set_next.Face());
    break;
  case ON_SubDComponentPtr::Type::Unset:
  default:
    return ON_SubDComponentPtr::Null;
    break;
  }
  return (1 == component->m_symmetry_set_next.ComponentDirection() && component->m_symmetry_set_next.IsNotNull()) ? cptr.SetComponentDirection() : cptr;
}

ON_SubDVertex* ON_SubDArchiveIdMap::CopyVertex(
  const ON_SubDVertex* source_vertex,
  class ON_SubDimple& subdimple
  )
{
  if ( nullptr == source_vertex )
    return ON_SUBD_RETURN_ERROR(nullptr);
  ON_SubDVertex* vertex = subdimple.AllocateVertex(
    source_vertex->m_id,
    source_vertex->m_vertex_tag,
    source_vertex->m_level,
    source_vertex->m_P,
    source_vertex->m_edge_count,
    source_vertex->m_face_count
    );
  if ( nullptr == vertex )
    return ON_SUBD_RETURN_ERROR(nullptr);
  
  const bool bCopyEdgeArray = true;
  const bool bCopyFaceArray = true;
  const bool bCopyLimitPointList = true;
  const bool bCopySymmetrySetNext = true;
  vertex->CopyFrom(source_vertex,bCopyEdgeArray,bCopyFaceArray,bCopyLimitPointList, bCopySymmetrySetNext);

  // convert vertex->m_edges[] pointers to archive_id values
  ON_SubDComponentPtr ptr;
  for (unsigned int vei = 0; vei < vertex->m_edge_count; vei++)
  {
    ptr = ON_SubDArchiveIdMap::FromEdge(vertex->m_edges[vei]);
    vertex->m_edges[vei].m_ptr = ptr.m_ptr;
  }

  // convert vertex->m_faces[] pointers to archive_id values
  for (unsigned int vfi = 0; vfi < vertex->m_face_count; vfi++)
  {
    ptr = ON_SubDArchiveIdMap::FromFace(vertex->m_faces[vfi]);
    vertex->m_faces[vfi] = (const ON_SubDFace*)ptr.m_ptr;
  }

  // convert vertex->m_limit_point[].m_sector_face pointers to archive_id values
  for (const ON_SubDSectorSurfacePoint* p = &vertex->m_limit_point; nullptr != p; p = p->m_next_sector_limit_point)
  {
    ptr = ON_SubDArchiveIdMap::FromFace(p->m_sector_face);
    const_cast<ON_SubDSectorSurfacePoint*>(p)->m_sector_face = (const ON_SubDFace*)ptr.m_ptr;
  }

  // convert symmetry set next pointers to archive_id values
  vertex->m_symmetry_set_next = ON_SubDArchiveIdMap::FromSymmetrySetNext(ON_SubDComponentPtr::Type::Vertex, vertex);
  
  return vertex;
}

ON_SubDEdge* ON_SubDArchiveIdMap::CopyEdge(
  const ON_SubDEdge* source_edge,
  class ON_SubDimple& subdimple
  )
{
  if ( nullptr == source_edge )
    return ON_SUBD_RETURN_ERROR(nullptr);
  ON_SubDEdge* edge = subdimple.AllocateEdge(
    source_edge->m_id,
    source_edge->m_edge_tag,
    source_edge->m_level,
    source_edge->m_face_count);
  if ( nullptr == edge )
    return ON_SUBD_RETURN_ERROR(nullptr);
  
  const bool bReverseEdge = false;
  const bool bCopyVertexArray = true;
  const bool bCopyEdgeArray = true;
  const bool bCopySymmetryLoop = true;
  edge->CopyFrom(source_edge,bReverseEdge,bCopyVertexArray,bCopyEdgeArray, bCopySymmetryLoop);

  // convert edge->m_vertex[] pointers to archive_id values
  ON_SubDComponentPtr ptr;
  for (unsigned int evi = 0; evi < 2; evi++)
  {
    ptr = ON_SubDArchiveIdMap::FromVertex(edge->m_vertex[evi]);
    edge->m_vertex[evi] = (const ON_SubDVertex*)ptr.m_ptr;
  }

  // convert edge->m_faces[] pointers to archive_id values
  ON_SubDFacePtr* fptr = edge->m_face2;
  for (unsigned int efi = 0; efi < edge->m_face_count; efi++, fptr++)
  {
    if (2 == efi)
      fptr = edge->m_facex;
    fptr->m_ptr = ON_SubDArchiveIdMap::FromFace(*fptr).m_ptr;
  }

  // convert symmetry set next pointers to archive_id values
  edge->m_symmetry_set_next = ON_SubDArchiveIdMap::FromSymmetrySetNext(ON_SubDComponentPtr::Type::Edge, edge);

  return edge;
}

ON_SubDFace* ON_SubDArchiveIdMap::CopyFace(
  const ON_SubDFace* source_face,
  class ON_SubDimple& subdimple
  )
{
  if ( nullptr == source_face )
    return ON_SUBD_RETURN_ERROR(nullptr);
  ON_SubDFace* face = subdimple.AllocateFace( source_face->m_id, source_face->m_level,source_face->m_edge_count, source_face->TexturePointsAreSet());
  if ( nullptr == face )
    return ON_SUBD_RETURN_ERROR(nullptr);
  
  const bool bCopyEdgeArray = true;
  const bool bCopySymmetryLoop = true;
  face->CopyFrom(source_face,bCopyEdgeArray, bCopySymmetryLoop);

  // convert face->m_edges[] pointers to archive_id values
  ON_SubDEdgePtr* eptr = face->m_edge4;
  for (unsigned int fei = 0; fei < face->m_edge_count; fei++, eptr++)
  {
    if (4 == fei)
      eptr = face->m_edgex;
    eptr->m_ptr = ON_SubDArchiveIdMap::FromEdge(*eptr).m_ptr;
  }

  // convert symmetry set next pointers to archive_id values
  face->m_symmetry_set_next = ON_SubDArchiveIdMap::FromSymmetrySetNext(ON_SubDComponentPtr::Type::Face, face);

  return face;
}
  
bool ON_SubDArchiveIdMap::ConvertArchiveIdToRuntimeVertexPtr(
  unsigned int vertex_count,
  size_t vertex_capacity,
  ON_SubDVertex** vertex
  )
{
  if ( 0 == vertex_count )
    return true;
  if ( 0 == vertex_capacity || nullptr == vertex )
    return ON_SUBD_RETURN_ERROR(false);
  if ( vertex_count > vertex_capacity )
    return ON_SUBD_RETURN_ERROR(false);
  for (unsigned int i = 0; i < vertex_count; i++)
  {
    ON__UINT_PTR vptr = (ON__UINT_PTR)(vertex[i]);
    vertex[i] = nullptr;
    const unsigned int archive_id = ON_SubDArchiveIdMap::ArchiveIdFromComponentPtr(vptr);
    // future use // ON__UINT_PTR flags = ON_SUBD_COMPONENT_FLAGS(vptr);
    if (0 == archive_id || archive_id < m_archive_id_partition[0] || archive_id >= m_archive_id_partition[1])
    {
      ON_ERROR("Invalid vertex archive id.");
      continue;
    }
    const ON_SubDComponentPtr* eleptr = ComponentPtrFromArchiveId(archive_id);
    if (nullptr == eleptr)
    {
      ON_ERROR("null element pointer.");
      continue;
    }
    ON_SubDVertex* v = eleptr->Vertex();
    if (nullptr == v)
    {
      ON_ERROR("null vertex pointer.");
      continue;
    }
    if (archive_id != v->ArchiveId())
    {
      ON_ERROR("archive_id != v->ArchiveId().");
      continue;
    }
    vertex[i] = v;
  }
  return true;
}


bool ON_SubDArchiveIdMap::ConvertArchiveIdToRuntimeEdgePtr(
  unsigned int edge_count,
  size_t edgeN_capacity,
  ON_SubDEdgePtr* edgeN,
  unsigned int edgeX_capacity,
  ON_SubDEdgePtr* edgeX
  )
{
  if ( 0 == edge_count )
    return true;
  if ( 0 == edgeN_capacity || nullptr == edgeN )
    return ON_SUBD_RETURN_ERROR(false);
  if ( 0 != edgeX_capacity && nullptr == edgeX )
    return ON_SUBD_RETURN_ERROR(false);
  if ( edge_count > edgeN_capacity + edgeX_capacity )
    return ON_SUBD_RETURN_ERROR(false);
  ON_SubDEdgePtr* eptr = edgeN;
  for (unsigned int i = 0; i < edge_count; i++, eptr++)
  {
    if ( i == edgeN_capacity )
      eptr = edgeX;
    const unsigned int archive_id = ON_SubDArchiveIdMap::ArchiveIdFromComponentPtr(eptr->m_ptr);
    ON__UINT_PTR flags = ON_SUBD_COMPONENT_FLAGS(eptr->m_ptr);
    eptr->m_ptr = 0;
    if (0 == archive_id || archive_id < m_archive_id_partition[1] || archive_id >= m_archive_id_partition[2])
    {
      ON_ERROR("Invalid edge archive id.");
      continue;
    }
    const ON_SubDComponentPtr* eleptr = ComponentPtrFromArchiveId(archive_id);
    if (nullptr == eleptr)
    {
      ON_ERROR("null element pointer.");
      continue;
    }
    ON_SubDEdge* edge = eleptr->Edge();
    if (nullptr == edge)
    {
      ON_ERROR("null edge pointer.");
      continue;
    }
    if (archive_id != edge->ArchiveId())
    {
      ON_ERROR("archive_id != edge->ArchiveId().");
      continue;
    }
    *eptr = ON_SubDEdgePtr::Create(edge,ON_SUBD_COMPONENT_DIRECTION(flags));
  }
  return true;
}

bool ON_SubDArchiveIdMap::ConvertArchiveIdToRuntimeFacePtr(
  unsigned int face_count,
  size_t faceN_capacity,
  ON_SubDFacePtr* faceN,
  unsigned int faceX_capacity,
  ON_SubDFacePtr* faceX
  )
{
  if ( 0 == face_count )
    return true;
  if ( 0 == faceN_capacity || nullptr == faceN )
    return ON_SUBD_RETURN_ERROR(false);
  if ( 0 != faceX_capacity && nullptr == faceX )
    return ON_SUBD_RETURN_ERROR(false);
  if ( face_count > faceN_capacity + faceX_capacity )
    return ON_SUBD_RETURN_ERROR(false);
  ON_SubDFacePtr* fptr = faceN;
  for (unsigned int i = 0; i < face_count; i++, fptr++)
  {
    if ( i == faceN_capacity )
      fptr = faceX;
    const unsigned int archive_id = ON_SubDArchiveIdMap::ArchiveIdFromComponentPtr(fptr->m_ptr);
    ON__UINT_PTR flags = ON_SUBD_COMPONENT_FLAGS(fptr->m_ptr);
    fptr->m_ptr = 0;
    if (0 == archive_id || archive_id < m_archive_id_partition[2] || archive_id >= m_archive_id_partition[3])
    {
      ON_ERROR("Invalid face archive id.");
      continue;
    }
    const ON_SubDComponentPtr* eleptr = ComponentPtrFromArchiveId(archive_id);
    if (nullptr == eleptr)
    {
      ON_ERROR("null element pointer.");
      continue;
    }
    ON_SubDFace* face = eleptr->Face();
    if (nullptr == face)
    {
      ON_ERROR("null face pointer.");
      continue;
    }
    if (archive_id != face->ArchiveId())
    {
      ON_ERROR("archive_id != face->ArchiveId().");
      continue;
    }
    *fptr = ON_SubDFacePtr::Create(face,ON_SUBD_COMPONENT_DIRECTION(flags));
  }
  return true;
}

bool ON_SubDArchiveIdMap::ConvertArchiveIdToRuntimeSymmetrySetNextPtr(
  ON_SubDComponentPtr::Type component_type,
  ON_SubDComponentBase* component
)
{
  if (nullptr == component)
    return false;
  const ON_SubDComponentPtr symmetry_set_next = component->m_symmetry_set_next; // symmetry_set_next stores archive id
  component->m_symmetry_set_next = ON_SubDComponentPtr::Null;
  if (symmetry_set_next.IsNull())
    return true;
  if (component_type != symmetry_set_next.ComponentType())
    return ON_SUBD_RETURN_ERROR(false);
  const unsigned archive_id = ON_SubDArchiveIdMap::ArchiveIdFromComponentPtr(symmetry_set_next.m_ptr);
  if (archive_id < 1)
    return ON_SUBD_RETURN_ERROR(false);
  unsigned parition0 = 0;
  switch (component_type)
  {
  case ON_SubDComponentPtr::Type::Unset:
    return ON_SUBD_RETURN_ERROR(false);
    break;
  case ON_SubDComponentPtr::Type::Vertex:
    parition0 = 0;
    break;
  case ON_SubDComponentPtr::Type::Edge:
    parition0 = 1;
    break;
  case ON_SubDComponentPtr::Type::Face:
    parition0 = 2;
    break;
  default:
    return ON_SUBD_RETURN_ERROR(false);
    break;
  }
  if(archive_id < m_archive_id_partition[parition0] || archive_id >= m_archive_id_partition[parition0+1])
    return ON_SUBD_RETURN_ERROR(false);
  const ON_SubDComponentPtr* eleptr = ComponentPtrFromArchiveId(archive_id);
  if ( nullptr == eleptr || eleptr->ComponentType() != component_type)
    return ON_SUBD_RETURN_ERROR(false);
  component->m_symmetry_set_next = (1 == symmetry_set_next.ComponentDirection()) ? eleptr->SetComponentDirection() : eleptr->ClearComponentDirection();
  return true;
}

void ON_SubDArchiveIdMap::ValidateArrayCounts(
  unsigned short& array_count,
  size_t arrayN_capacity,
  const void* arrayN,
  unsigned short arrayX_capacity,
  const void* arrayX
  )
{
  if (arrayN_capacity >= 0xFFFFU)
  {
    ON_ERROR("Invalid arrayN_capacity.");
    arrayN_capacity = 0xFFFFU;
  }

  unsigned short arrayN_cap = (unsigned short)arrayN_capacity;
  if ( array_count > arrayN_cap + arrayX_capacity 
    || (0 == arrayN_cap && 0 != arrayX_capacity)
    || (0 != arrayN_cap && nullptr == arrayN)
    || (0 != arrayX_capacity && nullptr == arrayX)
    )
  {
    ON_ERROR("Invalid array counts.");
    if ( nullptr == arrayN )
      arrayN_cap = 0;
    if ( 0 == arrayN_cap || nullptr == arrayX )
      arrayX_capacity = 0;
    if (array_count > arrayN_cap + arrayX_capacity )
      array_count = arrayN_cap + arrayX_capacity;
  }
}

ON_SubDArchiveIdMap::ON_SubDArchiveIdMap()
{
  m_fsp.Create(sizeof(ON_SubDComponentPtr),0,0);
  m_archive_id_partition[0] = 0;
  m_archive_id_partition[1] = 0;
  m_archive_id_partition[2] = 0;
  m_archive_id_partition[3] = 0;
}

bool ON_SubDArchiveIdMap::Reset()
{
  m_fsp.ReturnAll();
  m_element_index = ON_UNSET_UINT_INDEX;
  m_element_count = 0;
  m_archive_id_partition[0] = 0;
  m_archive_id_partition[1] = 0;
  m_archive_id_partition[2] = 0;
  m_archive_id_partition[3] = 0;
  return AddComponentPtr(ON_SubDComponentPtr::Null,0);
}

unsigned int ON_SubDArchiveIdMap::Count()
{
  return m_element_count;
}

const ON_SubDComponentPtr* ON_SubDArchiveIdMap::First()
{
  m_fsp_it.Create(&m_fsp);
  m_element_index = 0;
  const ON_SubDComponentPtr* p = (const ON_SubDComponentPtr*)m_fsp_it.FirstElement();
  if (nullptr != p)
    m_element_index++;
  return p;
}

const ON_SubDComponentPtr* ON_SubDArchiveIdMap::Next()
{
  if ( ON_UNSET_UINT_INDEX == m_element_index)
    return First();
  const ON_SubDComponentPtr* p = (const ON_SubDComponentPtr*)m_fsp_it.NextElement();
  if (nullptr != p)
    m_element_index++;
  return p;
}

bool ON_SubDArchiveIdMap::Add(const ON_SubDVertex* vertex)
{
  return AddComponentPtr(ON_SubDComponentPtr::Create(vertex,0),vertex ? vertex->ArchiveId() : 0);
}

bool ON_SubDArchiveIdMap::Add(const ON_SubDEdge* edge)
{
  return AddComponentPtr(ON_SubDComponentPtr::Create(edge,0),edge ? edge->ArchiveId() : 0);
}

bool ON_SubDArchiveIdMap::Add(const ON_SubDFace* face)
{
  return AddComponentPtr(ON_SubDComponentPtr::Create(face,0),face ? face->ArchiveId() : 0);
}


class ON_SubDVertex* ON_SubDArchiveIdMap::AddCopy(const class ON_SubDVertex* source_vertex, class ON_SubDimple& subdimple)
{
  ON_SubDVertex* vertex = ON_SubDArchiveIdMap::CopyVertex(source_vertex,subdimple);
  vertex->SetArchiveId(source_vertex->ArchiveId());
  Add(vertex);
  return vertex;
}

class ON_SubDEdge* ON_SubDArchiveIdMap::AddCopy(const class ON_SubDEdge* source_edge, class ON_SubDimple& subdimple)
{
  ON_SubDEdge* edge = ON_SubDArchiveIdMap::CopyEdge(source_edge,subdimple);
  edge->SetArchiveId(source_edge->ArchiveId());
  Add(edge);
  return edge;
}

class ON_SubDFace* ON_SubDArchiveIdMap::AddCopy(const class ON_SubDFace* source_face, class ON_SubDimple& subdimple)
{
  ON_SubDFace* face = ON_SubDArchiveIdMap::CopyFace(source_face,subdimple);
  face->SetArchiveId(source_face->ArchiveId());
  Add(face);
  return face;
}

const ON_SubDComponentPtr* ON_SubDArchiveIdMap::ComponentPtrFromArchiveId(
  unsigned int archive_id
  ) const
{
  return (const ON_SubDComponentPtr*)m_fsp.Element(archive_id);
}


bool ON_SubDArchiveIdMap::AddComponentPtr(ON_SubDComponentPtr eptr, unsigned int archive_id)
{
  if (m_element_count != archive_id)
  {
    ON_ERROR("Archive id is not valid and ON_SubD::Read will fail.");
    return false;
  }
  ON_SubDComponentPtr* p = (ON_SubDComponentPtr*)m_fsp.AllocateElement();
  *p = eptr;

////#if defined(ON_DEBUG)
////  if (0 != archive_id)
////  {
////    const ON_SubDComponentPtr* p1 = (const ON_SubDComponentPtr*)m_fsp.Element(archive_id);
////    unsigned int archive_id1 = 0;
////    if (p1 == p)
////    {
////      switch (p1->ComponentType())
////      {
////      case ON_SubDComponentPtr::Type::Vertex:
////        archive_id1 = p1->Vertex()->ArchiveId();
////        break;
////      case ON_SubDComponentPtr::Type::Edge:
////        archive_id1 = p1->Edge()->ArchiveId();
////        break;
////      case ON_SubDComponentPtr::Type::Face:
////        archive_id1 = p1->Face()->ArchiveId();
////        break;
////      default:
////        ON_ERROR("invalid element type");
////        break;
////      }
////    }
////    if (archive_id1 != archive_id)
////    {
////      // break here and then see what went wrong
////      ON_SubDIncrementErrorCount();
////      m_fsp.Element(archive_id);
////      m_fsp.Element(archive_id);
////    }
////  }
////#endif

  m_element_count++;
  return true;
}

unsigned int ON_SubDArchiveIdMap::ConvertArchiveIdsToRuntimePointers()
{
  // Convert archive_id references to runtime pointers.

  // The first element is ON_SubDComponentPtr::Null.  This is done so the index of the elements
  // in element_list[] is equal to the element's archive_id.
  const ON_SubDComponentPtr* element = First();
  if (nullptr == element || ON_SubDComponentPtr::Type::Unset != element->ComponentType())
    return ON_SUBD_RETURN_ERROR(0);
  
  element = Next();

  unsigned int archive_id;

  for (archive_id = m_archive_id_partition[0]; nullptr != element && archive_id < m_archive_id_partition[1]; archive_id++, element = Next())
  {
    ON_SubDVertex* v = element->Vertex();
    if (nullptr == v)
      break;
    if (archive_id != v->ArchiveId())
      break;
    // convert ON_SubDVertex.m_edges[]
    ConvertArchiveIdToRuntimeEdgePtr(v->m_edge_count,v->m_edge_capacity,v->m_edges,0,nullptr);
    // convert ON_SubDVertex.m_faces[]
    ConvertArchiveIdToRuntimeFacePtr(v->m_face_count,v->m_face_capacity,(ON_SubDFacePtr*)v->m_faces,0,nullptr);

    for (const ON_SubDSectorSurfacePoint* p = &v->m_limit_point; nullptr != p; p = p->m_next_sector_limit_point)
    {
      if ( 0 != p->m_sector_face )
        ConvertArchiveIdToRuntimeFacePtr(1,1,(ON_SubDFacePtr*)&p->m_sector_face,0,nullptr);
    }

    // convert v->m_symmetry_set_next to runtime pointer.
    ConvertArchiveIdToRuntimeSymmetrySetNextPtr(ON_SubDComponentPtr::Type::Vertex, v);
  }
  if ( archive_id != m_archive_id_partition[1] )
    return ON_SUBD_RETURN_ERROR(0);

  for (archive_id = m_archive_id_partition[1]; nullptr != element && archive_id < m_archive_id_partition[2]; archive_id++, element = Next())
  {
    ON_SubDEdge* e = element->Edge();
    if (nullptr == e)
      break;
    if (archive_id != e->ArchiveId())
      break;
    // convert ON_SubDEdge.m_vertex[2]
    ConvertArchiveIdToRuntimeVertexPtr(2,2,(ON_SubDVertex**)(e->m_vertex));
    // convert ON_SubDEdge.m_face2[] and ON_SubDEdge.m_facex[]
    ConvertArchiveIdToRuntimeFacePtr(e->m_face_count,sizeof(e->m_face2)/sizeof(e->m_face2[0]),e->m_face2,e->m_facex_capacity,e->m_facex);

    // convert e->m_symmetry_set_next to runtime pointer.
    ConvertArchiveIdToRuntimeSymmetrySetNextPtr(ON_SubDComponentPtr::Type::Edge, e);
  }
  if ( archive_id != m_archive_id_partition[2] )
    return ON_SUBD_RETURN_ERROR(0);

  for (archive_id = m_archive_id_partition[2]; nullptr != element && archive_id < m_archive_id_partition[3]; archive_id++, element = Next())
  {
    ON_SubDFace* f = element->Face();
    if (nullptr == f)
      break;
    if (archive_id != f->ArchiveId())
      break;
    // convert ON_SubDFace.m_edge4[] and ON_SubDFace.m_edgex[]
    ON_SubDArchiveIdMap::ConvertArchiveIdToRuntimeEdgePtr(f->m_edge_count,sizeof(f->m_edge4)/sizeof(f->m_edge4[0]),f->m_edge4,f->m_edgex_capacity,f->m_edgex);

    // convert f->m_symmetry_set_next to runtime pointer.
    ConvertArchiveIdToRuntimeSymmetrySetNextPtr(ON_SubDComponentPtr::Type::Face, f);
  }
  if ( archive_id != m_archive_id_partition[3] )
    return ON_SUBD_RETURN_ERROR(0);

  return archive_id;
}

void ON_SubD::ShareContentsFrom(ON_SubD& src_subd)
{
  if (this == &ON_SubD::Empty || &src_subd == &ON_SubD::Empty)
  {
    ON_SubDIncrementErrorCount();
  }
  else if (m_subdimple_sp.get() != src_subd.m_subdimple_sp.get())
  {
    m_subdimple_sp = src_subd.m_subdimple_sp;
  }
}

void ON_SubD::SwapContents(
  ON_SubD& a,
  ON_SubD& b
  )
{
  if (&a == &ON_SubD::Empty || &b == &ON_SubD::Empty)
  {
    ON_SubDIncrementErrorCount();
  }
  else
  {
    std::swap(a.m_subdimple_sp, b.m_subdimple_sp);
  }
}


ON_SubD::ON_SubD(const ON_SubD& src)
  : ON_Geometry(src)
{
  this->CopyHelper(src);
}

ON_SubD& ON_SubD::operator=(const ON_SubD& src)
{
  if ( this != &src )
  {
    this->Destroy();
    this->CopyHelper(src);
    // The next line copies user data
    ON_Geometry::operator=(src);
  }
  return *this;
}

void ON_SubD::CopyHelper(const ON_SubD& src)
{
  ON_SubDimple* subdimple = nullptr;
  const ON_SubDimple* src_subdimple = src.SubDimple();
  if (nullptr != src_subdimple)
  {
    subdimple = new ON_SubDimple(*src_subdimple);
  }
  m_subdimple_sp = std::shared_ptr<ON_SubDimple>(subdimple);
  if (nullptr != subdimple)
    subdimple->SetManagedMeshSubDWeakPointers(m_subdimple_sp);
}

ON__UINT64 ON_SubDimple::GeometryContentSerialNumber() const
{
  return m_subd_geometry_content_serial_number;
}

ON__UINT64 ON_SubDimple::RenderContentSerialNumber() const
{
  return m_subd_render_content_serial_number;
}

ON__UINT64 ON_SubDimple::ComponentStatusSerialNumber() const
{
  return ActiveLevel().ComponentStatusSerialNumber();
}

const ON_AggregateComponentStatusEx ON_SubDimple::AggregateComponentStatus() const
{
  return ActiveLevel().AggregateComponentStatus();
}

ON__UINT64 ON_SubDimple::ChangeGeometryContentSerialNumber(
  bool bChangePreservesSymmetry
) const
{
  // For efficiency, must calculate bUpdateSymmetricObjectGeometry before changing m_subd_geometry_content_serial_number
  const bool bUpdateSymmetricObjectGeometry = bChangePreservesSymmetry && m_symmetry.SameSymmetricObjectGeometry(this);

  m_subd_geometry_content_serial_number = ON_NextContentSerialNumber();
  m_subd_render_content_serial_number = m_subd_geometry_content_serial_number; // changing content automatically changes render content.

  if (m_symmetry.IsSet())
  {
    if (bUpdateSymmetricObjectGeometry)
      m_symmetry.SetSymmetricObject(this);
    else if (false == m_symmetry.SameSymmetricObjectTopology(this))
      m_symmetry.ClearSymmetricObject();
  }

  return m_subd_geometry_content_serial_number;
}

ON__UINT64 ON_SubDimple::ChangeRenderContentSerialNumber() const
{
  m_subd_render_content_serial_number = ON_NextContentSerialNumber();
  return m_subd_render_content_serial_number;
}

void ON_SubDimple::SetManagedMeshSubDWeakPointers(
  std::shared_ptr<class ON_SubDimple>& subdimple_sp
  )
{
  // update weak ptrs on limit mesh
  const unsigned int level_count = m_levels.UnsignedCount();
  for (unsigned level_index = 0; level_index < level_count; level_index++)
  {
    ON_SubDLevel* level = m_levels[level_index];
    if (nullptr == level)
      continue;
    ON_SubDMeshImpl* surface_mesh_imple = level->m_surface_mesh.SubLimple();
    if (nullptr != surface_mesh_imple)
      surface_mesh_imple->SetSubDWeakPointer(level->m_face[0], subdimple_sp);
    ON_SubDMeshImpl* control_net_mesh_imple = level->m_control_net_mesh.SubLimple();
    if (nullptr != control_net_mesh_imple)
      control_net_mesh_imple->SetSubDWeakPointer(level->m_face[0], subdimple_sp);
  }
}

void ON_SubDMeshImpl::SetSubDWeakPointer(
  const ON_SubDFace* subd_first_face,
  std::shared_ptr<class ON_SubDimple>& subdimple_sp
)
{
  for (;;)
  {
    const ON_SubDimple* subdimple = subdimple_sp.get();
    if (nullptr == subdimple)
      break;
    if (nullptr == subd_first_face)
      break;
    if (nullptr == m_first_fragment)
      break;
    if (m_first_fragment->m_face != subd_first_face)
      break;
    m_subdimple_wp = subdimple_sp;
    return;
  }

  // It's no longer clear that the subd used to create this limit mesh exist.
  ClearFragmentFacePointers(true);
}


ON_SubDimple::ON_SubDimple(const ON_SubDimple& src)
  : RuntimeSerialNumber(++ON_SubDimple::Internal_RuntimeSerialNumberGenerator)
{
  const bool bCopyComponentStatus = true;

  unsigned level_count = src.m_levels.UnsignedCount();
  for (/*empty init*/; level_count > 0; level_count--)
  {
    const ON_SubDLevel* src_level = src.m_levels[level_count - 1];
    if (nullptr == src_level)
      continue;
    if (nullptr == src_level->m_vertex[0])
      continue;
    if (nullptr == src_level->m_edge[0])
      continue;
    // it's ok to have subd with just vertices and edges.
    //NO//if (nullptr == src_level->m_face[0])
    //NO//  continue;
    break;
  }

  ON_SubDArchiveIdMap eptrlist;
  m_levels.Reserve(level_count);
  for (unsigned int level_index = 0; level_index < level_count; level_index++)
  {
    const ON_SubDLevel* src_level = src.m_levels[level_index];
    ON_SubDLevel* level = SubDLevel(level_index,true);
    if (nullptr == level)
      break;
    if (false == level->CopyHelper(src, *src_level, eptrlist, *this, bCopyComponentStatus))
      break;
    if ( src.m_active_level == src_level )
      m_active_level = level;
  }

  // this ON_SubDimple is an exact copy of src, so they have identical geometry 
  // and render content.
  m_subd_geometry_content_serial_number = src.m_subd_geometry_content_serial_number;
  m_subd_render_content_serial_number = src.m_subd_render_content_serial_number;

  m_subd_appearance = src.m_subd_appearance;
  m_texture_coordinate_type = src.m_texture_coordinate_type;
  m_texture_mapping_tag = src.m_texture_mapping_tag;
  m_colors_mapping_tag = src.m_colors_mapping_tag;

  // NOTE WELL: (Dale Lear Aug 2023)
  // Fragment settings like the two m_fragment_... values 
  // should be copied only if the mesh fragments are copied
  // and that happens conditionally and happens later
  // if ON_SubDimple::CopyEvaluationCacheForExperts() is called.
  // NO // m_fragment_texture_settings_hash = src.m_fragment_texture_settings_hash;
  // NO // m_fragment_colors_settings_hash = src.m_fragment_colors_settings_hash;

  m_face_packing_id = src.m_face_packing_id;
  m_face_packing_topology_hash = src.m_face_packing_topology_hash;
  m_face_packing_topology_hash.m_subd_runtime_serial_number
    = (src.RuntimeSerialNumber == src.m_face_packing_topology_hash.SubDRuntimeSerialNumber())
    ? this->RuntimeSerialNumber
    : 0;
  if (0 == m_face_packing_topology_hash.m_subd_runtime_serial_number)
    m_face_packing_topology_hash.m_subd_geometry_content_serial_number = 0;

  m_symmetry = src.m_symmetry;

  if (
    src.RuntimeSerialNumber == src.m_subd_toplology_hash.SubDRuntimeSerialNumber()
    && m_subd_geometry_content_serial_number == src.m_subd_toplology_hash.SubDGeometryContentSerialNumber()
    )
  {
    // src.m_subd_toplology_hash is valid - copy it to this
    m_subd_toplology_hash = src.m_subd_toplology_hash;
    m_subd_toplology_hash.m_subd_runtime_serial_number = this->RuntimeSerialNumber;
  }

  if (
    src.RuntimeSerialNumber == src.m_subd_toplology_and_edge_creases_hash.SubDRuntimeSerialNumber()
    && m_subd_geometry_content_serial_number == src.m_subd_toplology_and_edge_creases_hash.SubDGeometryContentSerialNumber()
    )
  {
    // src.m_subd_toplology_and_edge_crease_hash is valid - copy it to this
    m_subd_toplology_and_edge_creases_hash = src.m_subd_toplology_and_edge_creases_hash;
    m_subd_toplology_and_edge_creases_hash.m_subd_runtime_serial_number = this->RuntimeSerialNumber;
  }

  if (
    src.RuntimeSerialNumber == src.m_subd_geometry_hash.SubDRuntimeSerialNumber()
    && m_subd_geometry_content_serial_number == src.m_subd_geometry_hash.SubDGeometryContentSerialNumber()
    )
  {
    // src.m_subd_geometry_hash is valid - copy it to this.
    m_subd_geometry_hash = src.m_subd_geometry_hash;
    m_subd_geometry_hash.m_subd_runtime_serial_number = this->RuntimeSerialNumber;
  }
}

bool ON_SubDLevel::IsEmpty() const
{
  return (
    nullptr == m_vertex[0] 
    || 0U == m_vertex_count 
    || this == &ON_SubDLevel::Empty 
    );
}

int ON_SubDComponentBaseLink::CompareId(ON_SubDComponentBaseLink const*const* lhs, ON_SubDComponentBaseLink const*const* rhs)
{
  unsigned int lhs_id = (*lhs)->m_id;
  unsigned int rhs_id = (*rhs)->m_id;
  if (lhs_id < rhs_id)
    return -1;
  if (lhs_id > rhs_id)
    return 1;
  return 0;
}

void ON_SubDLevelComponentIdIterator::Initialize(
  bool bLevelLinkedListIncreasingId,
  ON_SubDComponentPtr::Type ctype,
  const ON_SubDimple& subdimple,
  const ON_SubDLevel& level
)
{
  m_bLevelLinkedListIncreasingId = false;
  m_ctype = ctype;
  m_level_index = (unsigned short)level.m_level_index;
  m_count = 0;
  m_prev_id = 0;
  m_first = nullptr;
  m_current = nullptr;

  switch (ctype)
  {
  case ON_SubDComponentPtr::Type::Vertex:
      m_first = (const ON_SubDComponentBaseLink*)level.m_vertex[0];
      break;
  case ON_SubDComponentPtr::Type::Edge:
      m_first = (const ON_SubDComponentBaseLink*)level.m_edge[0];
      break;
  case ON_SubDComponentPtr::Type::Face:
      m_first = (const ON_SubDComponentBaseLink*)level.m_face[0];
      break;
  default:
    m_first = nullptr;
    break;
  }

  if (nullptr == m_first)
    return;

  m_bLevelLinkedListIncreasingId = bLevelLinkedListIncreasingId;

  if (false == m_bLevelLinkedListIncreasingId)
  {
    subdimple.InitializeComponentIdIterator(ctype, m_cidit);
  }
}

const ON_SubDVertex* ON_SubDLevelComponentIdIterator::FirstVertex()
{
  return (ON_SubDComponentPtr::Type::Vertex == m_ctype) ? (const ON_SubDVertex*)InternalFirst() : nullptr;
}

const ON_SubDVertex* ON_SubDLevelComponentIdIterator::NextVertex()
{
  return (ON_SubDComponentPtr::Type::Vertex == m_ctype) ? (const ON_SubDVertex*)InternalNext() : nullptr;
}

const ON_SubDEdge* ON_SubDLevelComponentIdIterator::FirstEdge()
{
  return (ON_SubDComponentPtr::Type::Edge == m_ctype) ? (const ON_SubDEdge*)InternalFirst() : nullptr;
}

const ON_SubDEdge* ON_SubDLevelComponentIdIterator::NextEdge()
{
  return (ON_SubDComponentPtr::Type::Edge == m_ctype) ? (const ON_SubDEdge*)InternalNext() : nullptr;
}

const ON_SubDFace* ON_SubDLevelComponentIdIterator::FirstFace()
{
  return (ON_SubDComponentPtr::Type::Face == m_ctype) ? (const ON_SubDFace*)InternalFirst() : nullptr;
}

const ON_SubDFace* ON_SubDLevelComponentIdIterator::NextFace()
{
  return (ON_SubDComponentPtr::Type::Face == m_ctype) ? (const ON_SubDFace*)InternalNext() : nullptr;
}    

const ON_SubDComponentBase* ON_SubDLevelComponentIdIterator::InternalFirst()
{
  m_prev_id = 0;
  if (nullptr == m_first)
    return nullptr;
  m_current = nullptr;
  if (m_bLevelLinkedListIncreasingId)
  {
    m_current = m_first;
  }
  else
  {
    for (const ON_SubDComponentBase* c = m_cidit.FirstComponent(); nullptr != c; c = m_cidit.NextComponent())
    {
      if (m_level_index != c->SubdivisionLevel())
        continue;
      m_current = (const ON_SubDComponentBaseLink*)c;
      break;
    }
  }
  if (nullptr != m_current)
  {
    if (m_current->m_id <= m_prev_id)
    {
      // When this happens, searching by component id will be broken in the destination of the SubD copy.
      // It is a very serious bug, but we continue so something will get saved to the archive or be created in the copy.
      ON_SUBD_ERROR("Iterator is not in order of increasing id.");
    }
    else
      m_prev_id = m_current->m_id;
    m_count = 1;
  }
  return m_current;
}


const ON_SubDComponentBase* ON_SubDLevelComponentIdIterator::InternalNext()
{
  if (nullptr == m_first || nullptr == m_current)
    return nullptr;
  if (m_bLevelLinkedListIncreasingId)
  {
    m_current = m_current->m_next;
  }
  else
  {
    m_current = nullptr;
    for (const ON_SubDComponentBase* c = m_cidit.NextComponent(); nullptr != c; c = m_cidit.NextComponent())
    {
      if (m_level_index != c->SubdivisionLevel())
        continue;
      m_current = (const ON_SubDComponentBaseLink*)c;
      break;
    }
  }
  if (nullptr != m_current)
  {
    if (m_current->m_id <= m_prev_id)
    {
      // When this happens, searching by component id will be broken in the destination of the SubD copy.
      // It is a very serious bug, but we continue so something will get saved to the archive or be created in the copy.
      ON_SUBD_ERROR("Iterator is not in order of increasing id.");
    }
    else
      m_prev_id = m_current->m_id;
    ++m_count;
  }
  return m_current;
}



bool ON_SubDLevel::CopyHelper(
  const class ON_SubDimple& src_subdimple,
  const ON_SubDLevel& src_level,
  class ON_SubDArchiveIdMap& archive_id_map,
  class ON_SubDimple& dest_subdimple,
  bool bCopyComponentStatus
  )
{
  bool rc = false;

  archive_id_map.Reset();

  m_surface_mesh.Clear();
  m_control_net_mesh.Clear();

  for (;;)
  {
    bool bLevelLinkedListIncreasingId[3] = {};
    if ( 0 == src_level.SetArchiveId(src_subdimple, archive_id_map.m_archive_id_partition, bLevelLinkedListIncreasingId) )
      break;

    unsigned int archive_id = 1;
    if ( archive_id != archive_id_map.m_archive_id_partition[0])
      break;

    // Have to use idit because subd editing (deleting and then adding) can leave the level's linked lists
    // with components in an order that is not increasing in id and it is critical that the next three for
    // loops iterate the level's components in order of increasing id.
    ON_SubDLevelComponentIdIterator src_idit;

    // must iterate source vertices in order of increasing id
    src_idit.Initialize(bLevelLinkedListIncreasingId[0], ON_SubDComponentPtr::Type::Vertex, src_subdimple, src_level);
    for (const ON_SubDVertex* source_vertex = src_idit.FirstVertex(); nullptr != source_vertex; source_vertex = src_idit.NextVertex(), archive_id++)
    {
      if (archive_id != source_vertex->ArchiveId())
        break;
      ON_SubDVertex* vertex = archive_id_map.AddCopy(source_vertex,dest_subdimple);
      if (nullptr == vertex )
        break;
      if (archive_id != vertex->ArchiveId())
        break;
      this->AddVertex(vertex);
      if ( bCopyComponentStatus )
        vertex->m_status = source_vertex->m_status;
    }
    if ( archive_id != archive_id_map.m_archive_id_partition[1])
      break;

    // must iterate source edges in order of increasing id
    src_idit.Initialize(bLevelLinkedListIncreasingId[1], ON_SubDComponentPtr::Type::Edge, src_subdimple, src_level);
    for (const ON_SubDEdge* source_edge = src_idit.FirstEdge(); nullptr != source_edge; source_edge = src_idit.NextEdge(), archive_id++)
    {
      if (archive_id != source_edge->ArchiveId())
        break;
      ON_SubDEdge* edge = archive_id_map.AddCopy(source_edge,dest_subdimple);
      if (nullptr == edge )
        break;
      if (archive_id != edge->ArchiveId())
        break;
      this->AddEdge(edge);
      if ( bCopyComponentStatus )
        edge->m_status = source_edge->m_status;
    }
    if ( archive_id != archive_id_map.m_archive_id_partition[2])
      break;

    // must iterate source faces in order of increasing id
    src_idit.Initialize(bLevelLinkedListIncreasingId[2], ON_SubDComponentPtr::Type::Face, src_subdimple, src_level);
    for (const ON_SubDFace* source_face = src_idit.FirstFace(); nullptr != source_face; source_face = src_idit.NextFace(), archive_id++)
    {
      if (archive_id != source_face->ArchiveId())
        break;
      ON_SubDFace* face = archive_id_map.AddCopy(source_face,dest_subdimple);
      if (nullptr == face )
        break;
      if (archive_id != face->ArchiveId())
        break;
      this->AddFace(face);
      if ( bCopyComponentStatus )
        face->m_status = source_face->m_status;
    }
    if ( archive_id != archive_id_map.m_archive_id_partition[3])
      break;

    if (0 == archive_id_map.ConvertArchiveIdsToRuntimePointers())
      break;

    for (int meshdex = 0; meshdex < 2; meshdex++)
    {
      ON_SubDMesh* src_mesh = (0==meshdex) ? (&src_level.m_surface_mesh) : (&src_level.m_control_net_mesh);
      ON_SubDMesh* this_mesh = (0 == meshdex) ? (&m_surface_mesh) : (&m_control_net_mesh);
      if (false == src_mesh->IsEmpty())
      {
        ON_SubDMesh local_subd_mesh;
        local_subd_mesh.CopyFrom(*src_mesh);
        for (const ON_SubDMeshFragment* fragment = local_subd_mesh.FirstFragment(); nullptr != fragment; fragment = fragment->m_next_fragment)
        {
          if (nullptr != fragment->m_face)
          {
            archive_id = fragment->m_face->ArchiveId();
            ON_SubDComponentPtr cptr = ON_SubDArchiveIdMap::FromFace(fragment->m_face);
            ON_SubDFacePtr fptr = cptr.FacePtr();
            const_cast<ON_SubDMeshFragment*>(fragment)->m_face = nullptr;
            if (0 != archive_id)
            {
              if (archive_id_map.ConvertArchiveIdToRuntimeFacePtr(1, 1, &fptr, 0, nullptr))
              {
                const_cast<ON_SubDMeshFragment*>(fragment)->m_face = fptr.Face();
                if (nullptr != fragment->m_face)
                  continue;
              }
            }
          }
          local_subd_mesh = ON_SubDMesh::Empty;
          break;
        }
        if (false == local_subd_mesh.IsEmpty())
          ON_SubDMesh::Swap(*this_mesh, local_subd_mesh);
      }
    }

    this->ClearArchiveId();

    this->m_level_index = src_level.m_level_index;
    this->m_aggregates = src_level.m_aggregates;
    this->m_aggregates.MarkAllAsNotCurrent();

    rc = true;
    break;
  }

  archive_id_map.Reset();
  src_level.ClearArchiveId();

  if ( false == rc )
    return ON_SUBD_RETURN_ERROR(false);

  return rc;
} // archive_id_map
