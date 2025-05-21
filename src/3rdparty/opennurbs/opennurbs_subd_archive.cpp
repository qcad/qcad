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

static bool Internal_WriteDouble3(
  const double x[3],
  ON_BinaryArchive& archive
  )
{
  for (;;)
  {
    if (!archive.WriteDouble(3, x))
      break;
    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}

static bool Internal_ReadDouble3(
  ON_BinaryArchive& archive,
  double x[3]
  )
{
  for (;;)
  {
    if (!archive.ReadDouble(3, x))
      break;
    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}

enum : unsigned char
{
  ON_SubDComponentArchiveAnonymousChunkMark = 254U,
  ON_SubDComponentArchiveAdditionEndMark = 255U
};

static bool Internal_ReadComponentAdditionSize(ON_BinaryArchive& archive, unsigned char valid_sz, unsigned char* sz)
{
  if (archive.Archive3dmVersion() < 70)
  {
    return ON_SUBD_RETURN_ERROR(false);
  }

  if (0 == valid_sz)
    return ON_SUBD_RETURN_ERROR(false);
  if (false == archive.ReadChar(sz))
    return ON_SUBD_RETURN_ERROR(false);
  if ( 0 != *sz && valid_sz != *sz && ON_SubDComponentArchiveAdditionEndMark != *sz )
    return ON_SUBD_RETURN_ERROR(false);
  return true;
}

static bool Internal_WriteComponentAdditionSize(bool bHaveAddition, ON_BinaryArchive& archive, unsigned char sz)
{
  if (archive.Archive3dmVersion() < 70)
  {
    return ON_SUBD_RETURN_ERROR(false);
  }

  if (0 == sz)
    return ON_SUBD_RETURN_ERROR(false);
  if (false == bHaveAddition)
    sz = 0;
  if (false == archive.WriteChar(sz))
    return ON_SUBD_RETURN_ERROR(false);
  return true;
}

static bool Internal_FinishReadingComponentAdditions(ON_BinaryArchive& archive)
{
  if (archive.Archive3dmVersion() < 70)
  {
    return ON_SUBD_RETURN_ERROR(false);
  }

  unsigned char sz = 1;
  if ( false == archive.ReadChar(&sz))
    return ON_SUBD_RETURN_ERROR(false);

  for (;;)
  {
    if (ON_SubDComponentArchiveAdditionEndMark == sz)
      return true;
    if (ON_SubDComponentArchiveAnonymousChunkMark == sz)
    {
      // skip an addition a future version added as an anonymous chunk
      int v = 0;
      if (false == archive.BeginRead3dmAnonymousChunk(&v))
        break;
      if (false == archive.EndRead3dmChunk())
        break;
    }
    else if ( sz > 0 )
    {
      // skip an addition a future version added as a fixed number of bytes
      // use archive.ReadByte(sz,buffer) instead of archive.SeekForward(sz) so CRC is properly calculated.
      char buffer[256];
      if (false == archive.ReadByte(sz,buffer))
        break;
    }
    sz = 0;
    if (false == archive.ReadChar(&sz))
      break;
  }
  return ON_SUBD_RETURN_ERROR(false);
}

static bool Internal_FinishWritingComponentAdditions(ON_BinaryArchive& archive)
{
  if (archive.Archive3dmVersion() < 70)
    return ON_SUBD_RETURN_ERROR(false);
  const unsigned char sz = ON_SubDComponentArchiveAdditionEndMark;
  return archive.WriteChar(sz);
}


static bool Internal_WriteArchiveIdAndFlags(
  unsigned int archive_id,
  ON__UINT_PTR ptr_flags,
  ON_BinaryArchive& archive
)
{
  if (!archive.WriteInt(archive_id))
    return ON_SUBD_RETURN_ERROR(false);
  unsigned char flags = (unsigned char)ON_SUBD_COMPONENT_FLAGS(ptr_flags);
  if (!archive.WriteChar(flags))
    return ON_SUBD_RETURN_ERROR(false);
  return true;
}

static bool Internal_ReadArchiveIdAndFlagsIntoComponentPtr(
  ON_BinaryArchive& archive,
  ON__UINT_PTR& element_ptr
)
{
  element_ptr = 0;
  unsigned int archive_id = 0;
  if (!archive.ReadInt(&archive_id))
    return ON_SUBD_RETURN_ERROR(false);
  unsigned char flags = 0;
  if (!archive.ReadChar(&flags))
    return ON_SUBD_RETURN_ERROR(false);
  element_ptr = archive_id;
  element_ptr *= (ON_SUBD_COMPONENT_FLAGS_MASK + 1);
  element_ptr += (flags & ON_SUBD_COMPONENT_FLAGS_MASK);
  return true;
}

static bool Internal_WritesSymmetrySetNext(
  const ON_SubDComponentBase& c,
  ON_BinaryArchive& archive
)
{
  const ON_SubDComponentPtr symmetry_set_next = ON_SubDArchiveIdMap::SymmetrySetNextForExperts(c);
  const ON_SubDComponentBase* next_c = symmetry_set_next.ComponentBase();
  const unsigned archive_id = (nullptr != next_c) ? next_c->ArchiveId() : 0;
  return Internal_WriteArchiveIdAndFlags(archive_id, symmetry_set_next.m_ptr, archive);
}


static bool Internal_ReadSymmetrySetNext(
  ON_BinaryArchive& archive,
  const ON_SubDComponentBase& c
)
{
  return Internal_ReadArchiveIdAndFlagsIntoComponentPtr(archive, ON_SubDArchiveIdMap::SymmetrySetNextForExperts(c).m_ptr);
}

static bool WriteBase(
  const ON_SubDComponentBase* base,
  ON_BinaryArchive& archive
  )
{
  for (;;)
  {
    unsigned int archive_id = base->ArchiveId();
    unsigned int id = base->m_id;
    unsigned short level = (unsigned short)base->SubdivisionLevel();
    if (!archive.WriteInt(archive_id))
      break;
    if (!archive.WriteInt(id))
      break;
    if (!archive.WriteShort(level))
      break;

    if (archive.Archive3dmVersion() < 70)
    {
      // version 6 3dm files
      double P[3];
      const bool bHaveP = base->GetSavedSubdivisionPoint(P);

      unsigned char cP = bHaveP ? 4U : 0U;
      if (!archive.WriteChar(cP))
        break;
      if (0 != cP)
      {
        if (!Internal_WriteDouble3(P, archive))
          break;
      }

      unsigned char deprecated_and_never_used_zero = 0U;
      if (!archive.WriteChar(deprecated_and_never_used_zero))
        break;
      return true;
    }
    
    // version 7 3dm files and later

    // never used displacement
    if ( false == Internal_WriteComponentAdditionSize(false,archive,24) )
      break;

    // 4 byte group id addition
    const bool bWriteGroupId = base->m_group_id > 0;
    if (false == Internal_WriteComponentAdditionSize(bWriteGroupId, archive, 4))
      break;
    if (bWriteGroupId)
    {
      if (!archive.WriteInt(base->m_group_id))
        break;
    }

    // 5 byte symmetry set next addition Dec 2020 Rhino 7.2 and later
    // 5 bytes = unsigned archive id + char flags
    const bool bWriteSymmetrySetNext = base->InSymmetrySet();
    if (false == Internal_WriteComponentAdditionSize(bWriteSymmetrySetNext, archive, 5))
      break;
    if (bWriteSymmetrySetNext)
    {
      if (!Internal_WritesSymmetrySetNext(*base,archive))
        break;
    }

    return Internal_FinishWritingComponentAdditions(archive);
  }
  return ON_SUBD_RETURN_ERROR(false);
}


static bool ReadBase(
  ON_BinaryArchive& archive,
  ON_SubDComponentBase& base
  )
{
  unsigned int archive_id = 0;
  unsigned int id = 0;
  unsigned short level = 0;
  for (;;)
  {
    if (!archive.ReadInt(&archive_id))
      break;
    if (!archive.ReadInt(&id))
      break;
    if (!archive.ReadShort(&level))
      break;

    base.m_id = id;
    base.SetArchiveId(archive_id);
    base.SetSubdivisionLevel(level);

    if (archive.Archive3dmVersion() < 70)
    {
      unsigned char cP = 0U;
      unsigned char deprecated_and_never_used_char = 0U;
      double P[3];

      if (!archive.ReadChar(&cP))
        break;
      if (0 != cP)
      {
        if (!Internal_ReadDouble3(archive, P))
          break;
      }

      if (!archive.ReadChar(&deprecated_and_never_used_char))
        break;
      if (0 != deprecated_and_never_used_char)
      {
        double deprecated_and_never_used_V[3];
        if (!Internal_ReadDouble3(archive, deprecated_and_never_used_V))
          break;
      }
      if (4 == cP)
        base.SetSavedSubdivisionPoint(P);
      return true;
    }

    // read additions
    unsigned char sz;

    // 24 byte displacement addition
    // This addition was a deprecated prototype that was never used in commercial Rhino.
    sz = 0;
    if (false == Internal_ReadComponentAdditionSize(archive, 24, &sz))
      break;
    if (ON_SubDComponentArchiveAdditionEndMark == sz)
      return true; // end of additions
    if (0 != sz)
    {
      double deprecated_and_never_used_V[3] = {};
      if (!archive.ReadDouble(3, deprecated_and_never_used_V))
        break;
    }

    // 4 byte group id addition
    sz = 0;
    if (false == Internal_ReadComponentAdditionSize(archive, 4, &sz))
      break;
    if (ON_SubDComponentArchiveAdditionEndMark == sz)
      return true; // end of additions
    if (0 != sz)
    {
      if (!archive.ReadInt(&base.m_group_id))
        break;
    }

    // 5 bytes symmetry set next addition Dec 2020 Rhino 7.2 and later
    // 5 bytes = unsigned archive id + char flags
    sz = 0;
    if (false == Internal_ReadComponentAdditionSize(archive, 5, &sz))
      break;
    if (ON_SubDComponentArchiveAdditionEndMark == sz)
      return true; // end of additions
    if (0 != sz)
    {
      if (!Internal_ReadSymmetrySetNext(archive,base))
        break;
    }

    
    return Internal_FinishReadingComponentAdditions(archive);
  }

  return ON_SUBD_RETURN_ERROR(false);
}

// Dale Lear 2024-12-18 Rhino 8.x
// Due to a bug in v7, the saved limit points were read but nuever used.
// So I'm simply not writing the limit points anymore.
//static bool Internal_WriteSavedLimitPointList(
//  unsigned int vertex_face_count,
//  bool bHaveLimitPoint,
//  const ON_SubDSectorSurfacePoint& limit_point,
//  ON_BinaryArchive& archive
//  )
//{
//  unsigned int limit_point_count = 0;
//  const ON_SubDSectorSurfacePoint* p;
//
//  if (bHaveLimitPoint)
//  {
//    for (p = &limit_point; nullptr != p && limit_point_count <= vertex_face_count; p = p->m_next_sector_limit_point)
//    {
//      if (!ON_IsValid(p->m_limitP[0]))
//        break;
//      if (limit_point_count > 0 && nullptr == p->m_sector_face)
//        break;
//      limit_point_count++;
//    }
//    if (limit_point_count > vertex_face_count || nullptr != p)
//      limit_point_count = 0;
//
//    if (limit_point_count > vertex_face_count)
//      limit_point_count = 0;
//  }
//  if (0 == limit_point_count)
//    bHaveLimitPoint = false;
//
//  for (;;)
//  {
//    unsigned char c = bHaveLimitPoint ? 4 : 0;
//    if (!archive.WriteChar(c))
//      break;
//
//    if (0 == c)
//      return true;
//
//    if (!archive.WriteInt(limit_point_count))
//      break;
//    
//    p = &limit_point;
//    for (unsigned int i = 0; i < limit_point_count; i++, p = p->m_next_sector_limit_point )
//    {
//      if (!Internal_WriteDouble3(limit_point.m_limitP, archive))
//        break;
//      if (!Internal_WriteDouble3(limit_point.m_limitT1, archive))
//        break;
//      if (!Internal_WriteDouble3(limit_point.m_limitT2, archive))
//        break;
//      if (!Internal_WriteDouble3(limit_point.m_limitN, archive))
//        break;
//      if (!Internal_WriteArchiveIdAndFlags(limit_point.m_sector_face ? limit_point.m_sector_face->ArchiveId() : 0, 0, archive))
//        break;
//    }
//    return true;
//  }
//  return ON_SUBD_RETURN_ERROR(false);
//}

// Dale Lear 2024-12-18 Rhino 8.x
// Due to a bug (missing & limit_points so the array was by value rather than by reference)
// on that's been in this code since v7, the saved
// limit points were read but never used.
// This function reads and discards the information that was never used
// but which exists in millions of older 3dm files.
// It appears recalculating the limit point information has been fast enough
// for many years, so I'm making it clear that this is legacy code.
static bool Internal_IgnoreSavedLimitPointList(
  ON_BinaryArchive& archive,
  unsigned int vertex_face_count
  //ON_SimpleArray< ON_SubDSectorSurfacePoint > limit_points // NOTE MISSING & means this array was by value and not by reference
  )
{
  //limit_points.SetCount(0);

  for (;;)
  {
    unsigned char c = 0;
    if (!archive.ReadChar(&c))
      break;

    if ( 0 == c)
      return true;

    unsigned int limit_point_count = 0;
    if (!archive.ReadInt(&limit_point_count))
      break;

    if ( 0 == limit_point_count )
      break;

    if (limit_point_count > vertex_face_count)
      break;

    //limit_points.Reserve(limit_point_count);
    unsigned int i = 0;
    for ( /*empty init*/; i < limit_point_count; i++)
    {
      ON_SubDSectorSurfacePoint limit_point = ON_SubDSectorSurfacePoint::Unset;
      if (!Internal_ReadDouble3(archive,limit_point.m_limitP))
        break;
      if (!Internal_ReadDouble3(archive,limit_point.m_limitT1))
        break;
      if (!Internal_ReadDouble3(archive,limit_point.m_limitT2))
        break;
      if (!Internal_ReadDouble3(archive,limit_point.m_limitN))
        break;
      ON_SubDFacePtr fptr = ON_SubDFacePtr::Null;
      if (!Internal_ReadArchiveIdAndFlagsIntoComponentPtr(archive,fptr.m_ptr))
        break;
      //limit_points.Append(limit_point);
    }

    if (limit_point_count != i )
      break;

    //if (4 != c)
    //  limit_points.SetCount(0);

    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}

static bool Internal_WriteVertexList(
  unsigned short vertex_count,
  const ON_SubDVertex*const* vertex,
  ON_BinaryArchive& archive
  )
{
  for (;;)
  {
    ON_SubDArchiveIdMap::ValidateArrayCounts(vertex_count,vertex_count,vertex,0,nullptr);

    if (!archive.WriteShort(vertex_count))
      break;

    if ( 0 == vertex_count )
      return true;
    
    const ON__UINT_PTR ptr_flags = 0; // for future use
    unsigned short i = 0;
    for (i = 0; i < vertex_count; i++)
    {
      const ON_SubDVertex* v = vertex[i];
      if (!Internal_WriteArchiveIdAndFlags((nullptr != v) ? v->ArchiveId() : 0, ptr_flags, archive))
        break;
    }
    if ( i < vertex_count )
      break;

    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}


static bool Internal_ReadVertexList(
  ON_BinaryArchive& archive,
  unsigned short& vertex_count,
  unsigned short vertex_capacity,
  ON_SubDVertex* vertex[]
  )
{
  for (;;)
  {
    unsigned short archive_vertex_count = 0;
    if (!archive.ReadShort(&archive_vertex_count))
      break;

    if (archive_vertex_count != vertex_count)
    {
      ON_ERROR("Archive vertex count != expected vertex count.");
      if ( archive_vertex_count < vertex_count)
        vertex_count = archive_vertex_count;
    }

    ON_SubDArchiveIdMap::ValidateArrayCounts(vertex_count,vertex_capacity,vertex,0,nullptr);

    unsigned short i = 0;
    for (i = 0; i < vertex_count; i++)
    {
      ON__UINT_PTR vptr = 0;
      if (!Internal_ReadArchiveIdAndFlagsIntoComponentPtr(archive,vptr))
        break;
      vertex[i] = (ON_SubDVertex*)vptr;
    }
    if ( i < vertex_count )
      break;

    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}


static bool Internal_WriteEdgePtrList(
  unsigned short edge_count,
  unsigned short edgeN_capacity,
  const ON_SubDEdgePtr* edgeN,
  unsigned short edgeX_capacity,
  const ON_SubDEdgePtr* edgeX,
  ON_BinaryArchive& archive
  )
{
  for (;;)
  {
    ON_SubDArchiveIdMap::ValidateArrayCounts(edge_count,edgeN_capacity,edgeN,edgeX_capacity,edgeX);

    if (!archive.WriteShort(edge_count))
      break;

    if ( 0 == edge_count )
      return true;

    const ON_SubDEdgePtr* eptr = edgeN;
    unsigned short i = 0;
    for (i = 0; i < edge_count; i++, eptr++)
    {
      if ( i == edgeN_capacity)
        eptr = edgeX;
      const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
      if (!Internal_WriteArchiveIdAndFlags((nullptr != edge) ? edge->ArchiveId() : 0,eptr->m_ptr,archive))
        break;
    }
    if ( i < edge_count )
      break;

    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}


static bool Internal_ReadEdgePtrList(
  ON_BinaryArchive& archive,
  unsigned short& edge_count,
  unsigned short edgeN_capacity,
  ON_SubDEdgePtr* edgeN,
  unsigned short edgeX_capacity,
  ON_SubDEdgePtr* edgeX
  )
{
  for (;;)
  {
    unsigned short archive_edge_count = 0;
    if (!archive.ReadShort(&archive_edge_count))
      break;

    if (archive_edge_count != edge_count)
    {
      ON_ERROR("Archive edge count != expected edge count.");
      if ( archive_edge_count < edge_count)
        edge_count = archive_edge_count;
    }

    ON_SubDArchiveIdMap::ValidateArrayCounts(edge_count,edgeN_capacity,edgeN,edgeX_capacity,edgeX);


    ON_SubDEdgePtr* eptr = edgeN;
    unsigned short i = 0;
    for (i = 0; i < edge_count; i++, eptr++)
    {
      if ( i == edgeN_capacity)
        eptr = edgeX;
      if (!Internal_ReadArchiveIdAndFlagsIntoComponentPtr(archive,eptr->m_ptr))
        break;
    }
    if ( i < edge_count )
      break;

    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}


static bool Internal_WriteFacePtrList(
  unsigned short face_count,
  size_t faceN_capacity,
  const ON_SubDFacePtr* faceN,
  unsigned short faceX_capacity,
  const ON_SubDFacePtr* faceX,
  ON_BinaryArchive& archive
  )
{
  for (;;)
  {
    ON_SubDArchiveIdMap::ValidateArrayCounts(face_count,faceN_capacity,faceN,faceX_capacity,faceX);

    if (!archive.WriteShort(face_count))
      break;

    if ( 0 == face_count )
      return true;

    const ON_SubDFacePtr* fptr = faceN;
    unsigned short i = 0;
    for (i = 0; i < face_count; i++, fptr++)
    {
      if ( i == faceN_capacity)
        fptr = faceX;
      const ON_SubDFace* face = ON_SUBD_FACE_POINTER(fptr->m_ptr);
      if (!Internal_WriteArchiveIdAndFlags((nullptr != face) ? face->ArchiveId() : 0,fptr->m_ptr,archive))
        break;
    }
    if ( i < face_count )
      break;

    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}


static bool Internal_ReadFacePtrList(
  ON_BinaryArchive& archive,
  unsigned short& face_count,
  unsigned short faceN_capacity,
  ON_SubDFacePtr* faceN,
  unsigned short faceX_capacity,
  ON_SubDFacePtr* faceX
  )
{
  for (;;)
  {
    unsigned short archive_face_count = 0;
    if (!archive.ReadShort(&archive_face_count))
      break;

    if (archive_face_count != face_count)
    {
      ON_ERROR("Archive face count != expected face count.");
      if ( archive_face_count < face_count)
        face_count = archive_face_count;
    }

    ON_SubDArchiveIdMap::ValidateArrayCounts(face_count,faceN_capacity,faceN,faceX_capacity,faceX);

    ON_SubDFacePtr* fptr = faceN;
    unsigned short i = 0;
    for (i = 0; i < face_count; i++, fptr++)
    {
      if ( i == faceN_capacity)
        fptr = faceX;
      if (!Internal_ReadArchiveIdAndFlagsIntoComponentPtr(archive,fptr->m_ptr))
        break;
    }
    if ( i < face_count )
      break;

    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}

ON_SubDComponentPtr& ON_SubDArchiveIdMap::SymmetrySetNextForExperts(const ON_SubDComponentBase& c)
{
  return const_cast<ON_SubDComponentPtr&>(c.m_symmetry_set_next);
}

bool ON_SubDVertex::Write(
  ON_BinaryArchive& archive
  ) const
{
  for (;;)
  {
    if (!WriteBase(this,archive))
      break;
    if (!archive.WriteChar((unsigned char)m_vertex_tag))
      break;
    if (!Internal_WriteDouble3(m_P,archive))
      break;
    if (!archive.WriteShort(m_edge_count))
      break;
    if (!archive.WriteShort(m_face_count))
      break;
    
    // Dale Lear 2024-12-18
    // Due to a bug in ON_SubDVertex::Read(), the limit points written
    // by Internal_WriteSavedLimitPointList() were read but never used.
    // It appears that recalculating the limit points every time the
    // file is read is working out just fine. So writing a zero byte
    // here means that old code will be able to read new files and
    // we wont' waste time and disk space saving limit points.
    if (!archive.WriteChar((unsigned char)0))
      break;
    //if (!Internal_WriteSavedLimitPointList(m_face_count, this->SurfacePointIsSet(), m_limit_point, archive))
    //  break;

    if (!Internal_WriteEdgePtrList(m_edge_count,m_edge_capacity,m_edges,0,nullptr, archive))
      break;
    if (!Internal_WriteFacePtrList(m_face_count,m_face_capacity,(const ON_SubDFacePtr*)m_faces,0,nullptr, archive))
      break;

    if (archive.Archive3dmVersion() < 70)
    {
      // mark end with a 0 byte
      if (!archive.WriteChar((unsigned char)0U))
        break;
      return true;
    }


    return Internal_FinishWritingComponentAdditions(archive);
  }
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubDVertex::Read(
  class ON_BinaryArchive& archive,
  class ON_SubD& subd,
  class ON_SubDVertex*& vertex
  )
{
  vertex = nullptr;

  for (;;)
  {
    ON_SubDimple* subdimple = const_cast<ON_SubDimple*>(subd.SubDimple());
    if ( nullptr == subdimple)
      break;

    ON_SubDComponentBase base = ON_SubDComponentBase::Unset;
    unsigned char vertex_tag = 0;
    //unsigned char vertex_edge_order = 0;
    //unsigned char vertex_facet_type = 0;
    double P[3];
    unsigned short edge_count = 0;
    unsigned short face_count = 0;

    //ON_SimpleArray<ON_SubDSectorSurfacePoint> limit_points;

    if (!ReadBase(archive,base))
      break;
    if (!archive.ReadChar(&vertex_tag))
      break;
    if (!Internal_ReadDouble3(archive,P))
      break;
    if (!archive.ReadShort(&edge_count))
      break;
    if (!archive.ReadShort(&face_count))
      break;

    if (!Internal_IgnoreSavedLimitPointList(archive, face_count))
      break;

    ON_SubDVertex* v = subdimple->AllocateVertex(
      base.m_id, // serialization must preserve ON_SubDVertex.m_id
      ON_SubD::VertexTagFromUnsigned(vertex_tag),
      base.SubdivisionLevel(),
      P,
      edge_count,
      face_count
      );

    if ( nullptr == v )
      break;

    v->ON_SubDComponentBase::operator=(base);

    if (!Internal_ReadEdgePtrList(archive,edge_count,v->m_edge_capacity,v->m_edges,0,nullptr))
      break;
    v->m_edge_count = edge_count;

    if (!Internal_ReadFacePtrList(archive,face_count,v->m_face_capacity,(ON_SubDFacePtr*)v->m_faces,0,nullptr))
      break;
    v->m_face_count = face_count;

    //for (unsigned int i = 0; i < limit_points.UnsignedCount(); i++)
    //{
    //  ON_SubDSectorSurfacePoint limit_point = limit_points[i];
    //  limit_point.m_next_sector_limit_point = (const ON_SubDSectorSurfacePoint*)1U; // skips checks
    //  if (false == v->SetSavedSurfacePoint( true, limit_point))
    //  {
    //    v->ClearSavedSurfacePoints();
    //    break;
    //  }
    //}

    vertex = v;

    if (archive.Archive3dmVersion() < 70)
    {
      unsigned char sz = 1;
      if (!archive.ReadChar(&sz) || 0 != sz)
        break;
      return true;
    }

    // read additions
    return Internal_FinishReadingComponentAdditions(archive);
  }
  return ON_SUBD_RETURN_ERROR(false);
}


bool ON_SubDEdge::Write(
  ON_BinaryArchive& archive
  ) const
{
  for (;;)
  {
    if (!WriteBase(this,archive))
      break;
    if (!archive.WriteChar((unsigned char)m_edge_tag))
      break;
    if (!archive.WriteShort(m_face_count))
      break;
    if (!archive.WriteDouble(2,m_sector_coefficient))
      break;
    if (!archive.WriteDouble(this->m_sharpness[0]))
      break;
    if (!Internal_WriteVertexList(2, m_vertex, archive))
      break;
    if (!Internal_WriteFacePtrList(m_face_count,sizeof(m_face2)/sizeof(m_face2[0]),m_face2,m_facex_capacity,m_facex, archive))
      break;

    if (archive.Archive3dmVersion() < 70)
    {
      // mark end with a 0 byte
      if (!archive.WriteChar((unsigned char)0U))
        break;
      return true;
    }

    if (archive.Archive3dmVersion() >= 80)
    {
      // 2nd sharpness added Jan 2023 to v8 files.
      if (!archive.WriteChar((unsigned char)8U))
        break;
      if (!archive.WriteDouble(this->m_sharpness[1]))
        break;
    }

    return Internal_FinishWritingComponentAdditions(archive);
  }
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubDEdge::Read(
  class ON_BinaryArchive& archive,
  class ON_SubD& subd,
  class ON_SubDEdge*& edge
  )
{
  edge = nullptr;

  for (;;)
  {
    ON_SubDimple* subdimple = const_cast<ON_SubDimple*>(subd.SubDimple());
    if ( nullptr == subdimple)
      break;

    ON_SubDComponentBase base = ON_SubDComponentBase::Unset;
    unsigned char edge_tag = 0;
    unsigned short face_count = 0;
    double sector_coefficient[2] = { 0 };
    double sharpness0 = 0.0;

    if (!ReadBase(archive,base))
      break;
    if (!archive.ReadChar(&edge_tag))
      break;
    if (!archive.ReadShort(&face_count))
      break;
    if (!archive.ReadDouble(2,sector_coefficient))
      break;
    if (!archive.ReadDouble(&sharpness0))
      break;

    ON_SubDVertex* v[2] = { 0 };
    unsigned short vertex_count = 2;
    if (!Internal_ReadVertexList(archive, vertex_count, 2, v))
      break;

    ON_SubDEdge* e = subdimple->AllocateEdge(
      base.m_id, // serialization must preserve ON_SubDEdge.m_id
      ON_SubD::EdgeTagFromUnsigned(edge_tag),
      base.SubdivisionLevel(),
      face_count
      );

    if ( nullptr == e )
      break;

    e->ON_SubDComponentBase::operator=(base);

    for ( unsigned short evi = 0; evi < 2 && evi < vertex_count; evi++ )
      e->m_vertex[evi] = v[evi];

    e->m_sector_coefficient[0] = sector_coefficient[0];
    e->m_sector_coefficient[1] = sector_coefficient[1];

    if (!Internal_ReadFacePtrList(archive,face_count,sizeof(e->m_face2)/sizeof(e->m_face2[0]),e->m_face2,e->m_facex_capacity,e->m_facex))
      break;
    e->m_face_count = face_count;
   
    edge = e;

    if (archive.Archive3dmVersion() < 70)
    {
      unsigned char sz;
      if (false == archive.ReadChar(&sz) || 0 != sz)
        break;
      return true;
    }

    if (archive.Archive3dmVersion() >= 80)
    {
      unsigned char sz;
      if (false == archive.ReadChar(&sz))
        break;
      if (ON_SubDComponentArchiveAdditionEndMark == sz)
        return true;
      if (8 != sz)
        break; // error

      // 2nd sharpness added Jan 2023 to v8 files.
      double sharpness1 = 0.0;
      if (false == archive.ReadDouble(&sharpness1))
        break;
      if (e->IsSmooth())
        e->SetSharpnessForExperts(ON_SubDEdgeSharpness::FromInterval(sharpness0,sharpness1));
    }

    return Internal_FinishReadingComponentAdditions(archive);
  }
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubDFace::Write(
  ON_BinaryArchive& archive
  ) const
{
  for (;;)
  {
    if (!WriteBase(this,archive))
      break;
    if (!archive.WriteInt(m_level_zero_face_id))
      break;

    // OBSOLETE parent face id
    const int obsolete_parent_face_id = 0;
    if (!archive.WriteInt(obsolete_parent_face_id))
      break;

    if (!archive.WriteShort(m_edge_count))
      break;
    if (!Internal_WriteEdgePtrList(m_edge_count,sizeof(m_edge4)/sizeof(m_edge4[0]),m_edge4,m_edgex_capacity,m_edgex, archive))
      break;

    if (archive.Archive3dmVersion() < 70)
    {
      unsigned char sz = 0;
      if (!archive.WriteChar(sz))
        break;
      return true;
    }

    // write 34 byte texture domain
    const bool bWritePackRect = PackRectIsSet();
    if (false == Internal_WriteComponentAdditionSize(bWritePackRect, archive, 34))
      break;
    if (bWritePackRect)
    {
      const unsigned char obsolete_per_face_texture_coordinate_type = ON_SubD::ObsoleteTextureDomainTypeFromTextureCoordinateType(ON_SubDTextureCoordinateType::Packed);
      if (!archive.WriteChar(obsolete_per_face_texture_coordinate_type))
        break;

      const unsigned packing_rot = PackRectRotationDegrees();
      const unsigned char packing_rot_dex = (unsigned char)(packing_rot/90U);
      if (!archive.WriteChar(packing_rot_dex))
        break;
      const ON_2dPoint pack_rect_origin = PackRectOrigin();
      if (!archive.WriteDouble(2, &pack_rect_origin.x))
        break;
      const ON_2dVector pack_rect_size = PackRectSize();
      if (!archive.WriteDouble(2, &pack_rect_size.x))
        break;
    }

    // 4 byte render material channel index
    const int material_channel_index = MaterialChannelIndex();
    const bool bWriteMaterialChannelIndex = (material_channel_index > 0 && material_channel_index <= ON_Material::MaximumMaterialChannelIndex);
    if (false == Internal_WriteComponentAdditionSize(bWriteMaterialChannelIndex, archive, 4))
      break;
    if (bWriteMaterialChannelIndex)
    {
      if (!archive.WriteInt(material_channel_index))
        break;
    }

    // 4 byte per face color
    const ON_Color per_face_color = PerFaceColor();
    const bool bWritePerFaceColor = (ON_Color::UnsetColor != per_face_color);
    if (false == Internal_WriteComponentAdditionSize(bWritePerFaceColor, archive, 4))
      break;
    if (bWritePerFaceColor)
    {
      if (!archive.WriteColor(per_face_color))
        break;
    }

    // PackId
    const unsigned pack_id = PackId();
    const bool bPackId = (pack_id > 0U);
    if (false == Internal_WriteComponentAdditionSize(bPackId, archive, 4))
      break;
    if (bPackId)
    {
      if (!archive.WriteInt(pack_id))
        break;
    }

    // Custom texture coordinates
    const bool bTexturePoints = this->TexturePointsAreSet();
    if (false == Internal_WriteComponentAdditionSize(bTexturePoints, archive, 4))
      break;
    if (bTexturePoints)
    {
      // The number of texture points varies from face to face (EdgeCount()).
      // The maximum size that can be saved in a single component addition is 253 bytes.
      // So, texture points are saved in 10 point chunks ( 10*sizeof(ON_3dPoint) = 240 <= 243.
      const unsigned texture_point_count = this->EdgeCount();
      const unsigned ten_point_chunk_count = texture_point_count / 10;
      const unsigned left_over_points_count = texture_point_count % 10;
      const ON_3dPoint* a = this->m_texture_points;
      const unsigned char sizeof_ten_points = (unsigned char)(10 * sizeof(ON_3dPoint)); // sizeof_ten_points = 240 <= 243
      bool bContinue = archive.WriteInt(ten_point_chunk_count);
      if ( false == bContinue)
        break;

      // write the 10 point chunks
      for (unsigned i = 0; bContinue && i < ten_point_chunk_count; ++i)
      {
        bContinue = Internal_WriteComponentAdditionSize(true, archive, sizeof_ten_points);
        bContinue = bContinue && archive.WriteDouble(30, (const double*)a);
        a += 10;
      }

      // write the "left over" points
      if (bContinue && left_over_points_count > 0)
      {
        const unsigned char sizeof_left_over_points = (unsigned char)(left_over_points_count * sizeof(ON_3dPoint)); // sizeof_left_over_points < 240
        bContinue = Internal_WriteComponentAdditionSize(true, archive, sizeof_left_over_points);
        bContinue = bContinue && archive.WriteDouble(3* left_over_points_count, (const double*)a);
      }
      if (false == bContinue)
        break;
    }

    return Internal_FinishWritingComponentAdditions(archive);
  }
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubDFace::Read(
  class ON_BinaryArchive& archive,
  class ON_SubD& subd,
  class ON_SubDFace*& face
)
{
  face = nullptr;

  for (;;)
  {
    ON_SubDimple* subdimple = const_cast<ON_SubDimple*>(subd.SubDimple());
    if (nullptr == subdimple)
      break;

    ON_SubDComponentBase base = ON_SubDComponentBase::Unset;
    unsigned int level_zero_face_id = 0;
    unsigned int obsolete_parent_face_id = 0;
    unsigned short edge_count = 0;

    if (!ReadBase(archive, base))
      break;
    if (!archive.ReadInt(&level_zero_face_id))
      break;
    if (!archive.ReadInt(&obsolete_parent_face_id))
      break;
    if (!archive.ReadShort(&edge_count))
      break;

    ON_SubDFace* f = subdimple->AllocateFace(
      base.m_id, // serialization must preserve ON_SubDFace.m_id
      base.SubdivisionLevel(),
      edge_count
    );

    if (nullptr == f)
      break;

    f->ON_SubDComponentBase::operator=(base);

    f->m_level_zero_face_id = level_zero_face_id;

    if (!Internal_ReadEdgePtrList(archive, edge_count, sizeof(f->m_edge4) / sizeof(f->m_edge4[0]), f->m_edge4, f->m_edgex_capacity, f->m_edgex))
      break;
    f->m_edge_count = edge_count;

    face = f;

    if (archive.Archive3dmVersion() < 70)
    {
      unsigned char sz;
      if (false == archive.ReadChar(&sz) || 0 != sz)
        break;
      return true;
    }

    // read additions
    unsigned char sz;

    sz = 0;
    if (false == Internal_ReadComponentAdditionSize(archive, 34, &sz))
      break;
    if (ON_SubDComponentArchiveAdditionEndMark == sz)
      return true; // end of additions
    if (0 != sz)
    {
      // 34 bytes of texture domain information
      unsigned char obsolete_per_face_texture_coordinate_type = 0;
      if (!archive.ReadChar(&obsolete_per_face_texture_coordinate_type))
        break;
      unsigned char packing_rot_dex = 0;
      if (!archive.ReadChar(&packing_rot_dex))
        break;
      const unsigned packing_rot = ((unsigned int)packing_rot_dex) * 90U;
      ON_2dPoint pack_rect_origin(ON_2dPoint::Origin);
      if (!archive.ReadDouble(2, &pack_rect_origin.x))
        break;
      ON_2dVector pack_rect_delta(ON_2dVector::ZeroVector);
      if (!archive.ReadDouble(2, &pack_rect_delta.x))
        break;

      if (ON_SubDFace::IsValidPackRect(pack_rect_origin, pack_rect_delta, packing_rot) )
        f->SetPackRectForExperts(pack_rect_origin, pack_rect_delta, packing_rot);
    }

    sz = 0;
    if (false == Internal_ReadComponentAdditionSize(archive, 4, &sz))
      break;
    if (ON_SubDComponentArchiveAdditionEndMark == sz)
      return true; // end of additions
    if (0 != sz)
    {
      // 4 bytes of material channel index
      int material_channel_index = 0;
      if (false == archive.ReadInt(&material_channel_index))
        break;
      f->SetMaterialChannelIndex(material_channel_index);
    }

    sz = 0;
    if (false == Internal_ReadComponentAdditionSize(archive, 4, &sz))
      break;
    if (ON_SubDComponentArchiveAdditionEndMark == sz)
      return true; // end of additions
    if (0 != sz)
    {
      // 4 bytes of per face color
      ON_Color per_face_color = ON_Color::UnsetColor;
      if (false == archive.ReadColor(per_face_color))
        break;
      f->SetPerFaceColor(per_face_color);
    }


    // PackId
    sz = 0;
    if (false == Internal_ReadComponentAdditionSize(archive, 4, &sz))
      break;
    if (ON_SubDComponentArchiveAdditionEndMark == sz)
      return true; // end of additions
    if (0 != sz)
    {
      // 4 bytes of pack id
      unsigned pack_id = 0U;
      if (false == archive.ReadInt(&pack_id))
        break;
      f->m_pack_id = pack_id;
    }


    // Custom texture coordinates
    sz = 0;
    if (false == Internal_ReadComponentAdditionSize(archive, 4, &sz))
      break;
    if (ON_SubDComponentArchiveAdditionEndMark == sz)
      return true; // end of additions
    if (0 != sz)
    {
      // The number of texture points varies from face to face (EdgeCount()).
      // The maximum size that can be saved in a single component addition is 253 bytes.
      // So, texture points are saved in 10 point chunks ( 10*sizeof(ON_3dPoint) = 240 <= 243.
      const unsigned texture_point_count = f->EdgeCount();
      unsigned ten_point_chunk_count = 0xFFFFFFFFU;
      if (false == archive.ReadInt(&ten_point_chunk_count))
        break;
      if (ten_point_chunk_count != texture_point_count / 10)
        break;
      const unsigned left_over_points_count = texture_point_count % 10;
      const unsigned char sizeof_ten_points = (unsigned char)(10 * sizeof(ON_3dPoint)); // sizeof_ten_points = 240 <= 243
      ON_3dPoint a[10];
      bool bContinue = true;

      // Even if allocation fails, we need to read the points so we can get get
      // future information that is after the points out of the archive.
      subdimple->AllocateFaceTexturePoints(f);
      ON_3dPoint* tp = f->m_texture_points;

      // read the 10 point chunks
      for (unsigned i = 0; bContinue && i < ten_point_chunk_count; ++i)
      {
        sz = 0;
        bContinue = Internal_ReadComponentAdditionSize(archive, sizeof_ten_points, &sz);
        bContinue = bContinue && (sizeof_ten_points == sz);
        bContinue = bContinue && archive.ReadDouble(30, (double*)a);
        if (bContinue && nullptr != tp)
        {
          for (unsigned j = 0; j < 10; ++j)
            *tp++ = a[j];
        }
      }

      // read the "left over" points.
      if (bContinue && left_over_points_count > 0)
      {
        const unsigned char sizeof_left_over_points = (unsigned char)(left_over_points_count * sizeof(ON_3dPoint)); // sizeof_left_over_points < 240
        sz = 0;
        bContinue = Internal_ReadComponentAdditionSize(archive, sizeof_left_over_points, &sz);
        bContinue = bContinue && (sizeof_left_over_points == sz);
        bContinue = bContinue && archive.ReadDouble(3 * left_over_points_count, (double*)a);
        if (bContinue && nullptr != tp)
        {
          for (unsigned j = 0; j < left_over_points_count; ++j)
            *tp++ = a[j];
        }
      }
      if (false == bContinue)
        break;
      if ( nullptr != tp)
        f->m_texture_status_bits |= ON_SubDFace::TextureStatusBits::TexturePointsSet;
    }


    return Internal_FinishReadingComponentAdditions(archive);
  }
  return ON_SUBD_RETURN_ERROR(false);
}

unsigned int ON_SubDLevel::SetArchiveId(
  const ON_SubDimple& subdimple,
  unsigned int archive_id_partition[4],
  bool bLevelLinkedListIncreasingId[3]
  ) const
{
  unsigned int archive_id = 1;
  //archive_id_partition[0] = 0;
  //archive_id_partition[1] = 0;
  //archive_id_partition[2] = 0;
  //archive_id_partition[3] = 0;

  const ON_SubDComponentPtr::Type component_type[3] = {
    ON_SubDComponentPtr::Type::Vertex,
    ON_SubDComponentPtr::Type::Edge,
    ON_SubDComponentPtr::Type::Face
  };

  const ON_SubDComponentBaseLink* first_link[3] = {
    (const ON_SubDComponentBaseLink*)m_vertex[0],
    (const ON_SubDComponentBaseLink*)m_edge[0],
    (const ON_SubDComponentBaseLink*)m_face[0]
  };


  for (unsigned int listdex = 0; listdex < 3; listdex++)
  {
    bLevelLinkedListIncreasingId[listdex] 
      = nullptr != first_link[listdex] 
      && first_link[listdex]->m_id > 0U;
    unsigned int prev_id = 0;
    archive_id_partition[listdex] = archive_id;
    unsigned int linked_list_count = 0;
    for (const ON_SubDComponentBaseLink* clink = first_link[listdex]; nullptr != clink; clink = clink->m_next)
    {
      ++linked_list_count;
      if (prev_id < clink->m_id)
      {
        prev_id = clink->m_id;
        clink->SetArchiveId(archive_id++);
        continue;
      }

      // the for(..) scope we are currently in is exited below.
      bLevelLinkedListIncreasingId[listdex] = false;

      // m_id values are not increasing in the linked list. 
      // This happens when the subd is edited  and components are deleted 
      // and then added back later. 
      // Finish counting components in the linked list.
      for (clink = clink->m_next; nullptr != clink; clink = clink->m_next)
        ++linked_list_count;

      // Now iterate the fixed size pool (which always iterates in increasing id order),
      // skip components not on this level, and set archive id of the ones on this level.
      unsigned int cidit_level_count = 0;
      archive_id = archive_id_partition[listdex];
      ON_SubDComponentIdIterator cidit;
      subdimple.InitializeComponentIdIterator(component_type[listdex],cidit);
      const unsigned level_index = this->m_level_index;
      prev_id = 0;
      for (const ON_SubDComponentBase* c = cidit.FirstComponent(); nullptr != c; c = cidit.NextComponent())
      {
        if (prev_id >= c->m_id)
        {
          // This is a serious error!
          // Continue because this allows us to save something do the disk in these bad cases.
          ON_SUBD_ERROR("The m_id values of the active components in the fixed size pool are corrupt.");
        }
        else
        {
          prev_id = c->m_id;
        }
        if (level_index != c->SubdivisionLevel())
          continue;
        ++cidit_level_count;
        c->SetArchiveId(archive_id++);
      }
      if (cidit_level_count != linked_list_count)
      {
        // This is a serious error!
        // Continue because this allows us to save something do the disk in these bad cases.
        ON_SUBD_ERROR("The m_level values of the active components in the fixed size pool are corrupt.");
      }
      break;
    }
  }

  archive_id_partition[3] = archive_id;

  return archive_id-1;
}


void ON_SubDLevel::ClearArchiveId() const
{
  // archive ids can be cleared in any order.
  for (const ON_SubDVertex* v = m_vertex[0]; nullptr != v; v = v->m_next_vertex)
    v->SetArchiveId(0);
  for (const ON_SubDEdge* e = m_edge[0]; nullptr != e; e = e->m_next_edge)
    e->SetArchiveId(0);
  for (const ON_SubDFace* f = m_face[0]; nullptr != f; f = f->m_next_face)
    f->SetArchiveId(0);
}

bool ON_SubDLevel::Write(
  const ON_SubDimple& subdimple,
  ON_BinaryArchive& archive
  ) const
{
  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,1))
    return ON_SUBD_RETURN_ERROR(false);

  bool rc = false;
  for (;;)
  {
    if (!archive.WriteShort((unsigned short)m_level_index))
      break;

    // from early days when there was a possibility of different types of subdivision algorithm
    // 4,4,4 means catmull clark quad
    if (!archive.WriteChar((unsigned char)4))
      break;
    if (!archive.WriteChar((unsigned char)4))
      break;
    if (!archive.WriteChar((unsigned char)4))
      break;   

    ON_BoundingBox bbox = m_aggregates.m_bDirtyBoundingBox ? ON_BoundingBox::EmptyBoundingBox : m_aggregates.m_controlnet_bbox;
    if (!archive.WriteDouble(3,bbox[0]))
      break;
    if (!archive.WriteDouble(3,bbox[1]))
      break;


    unsigned int archive_id_partition[4] = {};
    bool bLevelLinkedListIncreasingId[3] = {};
    SetArchiveId(subdimple, archive_id_partition, bLevelLinkedListIncreasingId);

    if (!archive.WriteInt(4,archive_id_partition))
      break;

    const ON_SubDVertex* v = nullptr;
    const ON_SubDEdge* e = nullptr;
    const ON_SubDFace* f = nullptr;

    // Have to use idit because subd editing (deleting and then adding) can leave the level's linked lists
    // with components in an order that is not increasing in id and it is critical that the next three for
    // loops iterate the level's components in order of increasing id.
    ON_SubDLevelComponentIdIterator idit;

    // must iterate vertices in order of increasing id
    idit.Initialize(bLevelLinkedListIncreasingId[0], ON_SubDComponentPtr::Type::Vertex, subdimple, *this);
    for (v = idit.FirstVertex(); nullptr != v; v = idit.NextVertex())
    {
      if( !v->Write(archive) )
        break;
    }
    if ( nullptr != v )
      break;

    // must iterate edges in order of increasing id
    idit.Initialize(bLevelLinkedListIncreasingId[1], ON_SubDComponentPtr::Type::Edge, subdimple, *this);
    for (e = idit.FirstEdge(); nullptr != e; e = idit.NextEdge())
    {
      if( !e->Write(archive) )
        break;
    }
    if ( nullptr != e )
      break;

    // must iterate faces in order of increasing id
    idit.Initialize(bLevelLinkedListIncreasingId[2], ON_SubDComponentPtr::Type::Face, subdimple, *this);
    for (f = idit.FirstFace(); nullptr != f; f = idit.NextFace())
    {
      if( !f->Write(archive) )
        break;
    }
    if ( nullptr != f )
      break;

    // chunk 1.1 has meshes
    unsigned char c = 0;
    if (archive.Save3dmRenderMesh(ON::object_type::subd_object) || archive.Save3dmAnalysisMesh(ON::object_type::subd_object))
    {
      // no reason to save the m_control_net_mesh
      if (false == m_surface_mesh.IsEmpty())
      {
        c = 0;
        // c = 1; TODO change to c = 1 when ON_SubDMesh::Write()/Read() actually work
      }
    }
    
    if (!archive.WriteChar(c))
      break;

    if (1 == c)
    {
      //if (!m_limit_mesh.Write(archive))
      //  break;
    }

    rc = true;
    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;
  ClearArchiveId();

  if (rc)
    return rc;
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubDLevel::Read(
  ON_BinaryArchive& archive,
  class ON_SubDArchiveIdMap& element_list,
  ON_SubD& subd
  )
{
  if ( false == element_list.Reset())
    return ON_SUBD_RETURN_ERROR(false);

  int major_version = 1;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version))
    return ON_SUBD_RETURN_ERROR(false);

  bool rc = false;
  for (;;)
  {
    if ( 1 != major_version)
      break;

    unsigned short level_index = 0;
    if (!archive.ReadShort(&level_index))
      break;
    m_level_index = level_index;

    // from early days when there was a possibility of different types of subdivision algorithm
    unsigned char ignored_c[3] = {};
    if (!archive.ReadChar(&ignored_c[0]))
      break;
    if (!archive.ReadChar(&ignored_c[1]))
      break;
    if (!archive.ReadChar(&ignored_c[2]))
      break;   

    ON_BoundingBox controlnet_bbox;
    if (!archive.ReadDouble(3, controlnet_bbox[0]))
      break;
    if (!archive.ReadDouble(3, controlnet_bbox[1]))
      break;
    if (controlnet_bbox.IsValid())
    {
      m_aggregates.m_bDirtyBoundingBox = false;
      m_aggregates.m_controlnet_bbox = controlnet_bbox;
    }
    else
    {
      m_aggregates.m_bDirtyBoundingBox = true;
    }

    if (!archive.ReadInt(4,element_list.m_archive_id_partition))
      break;

    unsigned int archive_id = 0;

    for (archive_id = element_list.m_archive_id_partition[0]; archive_id < element_list.m_archive_id_partition[1]; archive_id++ )
    {
      ON_SubDVertex* v = nullptr;
      if ( false == ON_SubDVertex::Read(archive, subd, v) )
        break;
      if ( nullptr == v )
        break;
      if (archive_id != v->ArchiveId())
        break;
      if ( !element_list.Add(v) )
        break;
      AddVertex(v);      
    }
    if ( archive_id != element_list.m_archive_id_partition[1] )
      break;    

    for (archive_id = element_list.m_archive_id_partition[1]; archive_id < element_list.m_archive_id_partition[2]; archive_id++ )
    {
      ON_SubDEdge* e = nullptr;
      if ( false == ON_SubDEdge::Read(archive, subd, e) )
        break;
      if ( nullptr == e )
        break;
      if (archive_id != e->ArchiveId())
        break;
      if ( !element_list.Add(e) )
        break;
      AddEdge(e);

#if !defined(OPENNURBS_IN_RHINO) && !defined(OPENNURBS_7_17_SUBD_SKIP_CHECK_CORNER_SECTOR_COEFFICIENTS)
      // Versions <= 7.16 saved incorrect sector coefficient values, for smooth edges to corner vertices.
      // Rhino updates all sector coefficient values when adding the SubD to the document so has no need for this check.
      if (
        archive.ArchiveOpenNURBSVersion() <= ON_VersionNumberConstruct(7, 16, 2099, 12, 31, 6)
        && (e->m_edge_tag == ON_SubDEdgeTag::Smooth || e->m_edge_tag == ON_SubDEdgeTag::SmoothX)
        )
      {
        static const ON_String format{
          L"The value of m_sector_coefficient[% i] for edge with m_id %u in SubD %u "
          "is incorrect. Recompute it before using it.\n"
          "Recompile OpenNURBS with the OPENNURBS_7_17_SUBD_SKIP_CHECK_CORNER_SECTOR_COEFFICIENTS "
          "flag to skip this check and silence this warning, or update and save your file in "
          "OpenNURBS >= 7.17.\n"
        };
        for (unsigned short evi = 0; evi < 2; evi++)
        {
          ON_SubDVertex* vp{ const_cast<ON_SubDVertex*>(e->m_vertex[evi]) };
          if (!element_list.ConvertArchiveIdToRuntimeVertexPtr(1, 1, &vp)) continue;
          if (vp->m_vertex_tag == ON_SubDVertexTag::Corner)
          {
            ON_String msg{};
            msg.Format(format, evi, e->m_id, subd.ModelObjectId());
            ON_WARNING(msg);
          }
        }
      }
#endif

    }
    if ( archive_id != element_list.m_archive_id_partition[2] )
      break;

    for (archive_id = element_list.m_archive_id_partition[2]; archive_id < element_list.m_archive_id_partition[3]; archive_id++ )
    {
      ON_SubDFace* f = nullptr;
      if ( false == ON_SubDFace::Read(archive, subd, f) )
        break;
      if ( nullptr == f )
        break;
      if (archive_id != f->ArchiveId())
        break;
      if ( !element_list.Add(f) )
        break;
      AddFace(f);
    }
    if ( archive_id != element_list.m_archive_id_partition[3] )
      break;

    if (archive_id != element_list.Count())
      break;

    // Convert archive_id references to runtime pointers.
    archive_id = element_list.ConvertArchiveIdsToRuntimePointers();
    if ( archive_id <= 0 )
      break;    

    if (0 == minor_version )
      break;

    unsigned char c = 0;
    if (!archive.ReadChar(&c))
      break;

    if (1 == c)
    {
      //if (!m_limit_mesh.Read(archive))
      //  break; 
    }

    rc = true;
    break;
  }

  ClearArchiveId();

  if (!archive.EndRead3dmChunk())
    rc = false;

  if (rc)
    return rc;
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubDimple::Write(
  ON_BinaryArchive& archive
  ) const
{
  const_cast< ON_SubDHeap* >(&m_heap)->ClearArchiveId();

  const int minor_version = (archive.Archive3dmVersion() < 70) ? 0 : 4;
  if ( !archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, 1, minor_version) )
    return ON_SUBD_RETURN_ERROR(false);
  bool rc = false;
  for (;;)
  {
    unsigned int level_count = m_levels.UnsignedCount();
    unsigned int level_index;
    for (level_index = 0; level_index < level_count; level_index++)
    {
      if (nullptr == m_levels[level_index])
      {
        level_count = level_index;
        break;
      }
    }
    if (!archive.WriteInt(level_count))
      break;

    if (!archive.WriteInt(MaximumVertexId()))
      break;
    if (!archive.WriteInt(MaximumEdgeId()))
      break;
    if (!archive.WriteInt(MaximumFaceId()))
      break;

    // a global bounding box was saved before May 2015.
    // Something has to be here so file IO is not broken.
    if (!archive.WriteBoundingBox(ON_BoundingBox::EmptyBoundingBox))
      break;

    for (level_index = 0; level_index < level_count; level_index++)
    {
      if ( !m_levels[level_index]->Write(*this,archive) )
        break;
    }
    if (level_index < level_count)
      break;


    if (minor_version <= 0)
    {
      rc = true;
      break;
    }

    // minor version = 1 additions
    const unsigned char obsolete_texture_domain_type = ON_SubD::ObsoleteTextureDomainTypeFromTextureCoordinateType(TextureCoordinateType());
    if (false == archive.WriteChar(obsolete_texture_domain_type))
      break;

    if (false == m_texture_mapping_tag.Write(archive))
      break;

    // minor version = 2 additions
    if (false == m_symmetry.Write(archive))
      break;

    // minor version = 3 additions
    // runtime content number used to compare with the one from the saved on m_symmetry
    // Dale Lear Sep 2020 - Turns out saving the runtime GeometryContentSerialNumber()
    // was a bad idea. Doing it the way I came up with today while adding
    // m_face_packing_topology_hash is much better because all decisions get
    // made at save time when we have the most reliable information.
    // I've added bSyncSymmetricContentSerialNumber below, but saving gsn has to stay
    // so pre-today Rhino can read files saved from post today Rhino.
    const ON__UINT64 gsn = GeometryContentSerialNumber();
    if (false == archive.WriteBigInt(gsn))
      break;

    // minor version = 4 additions
    // bSubDIsSymmetric = true if this subd currently has the symmetry specified by m_symmetry.
    const bool bSubDIsSymmetric = m_symmetry.SameSymmetricObjectGeometry(this);

    if (false == archive.WriteBool(bSubDIsSymmetric))
      break;

    if (false == archive.WriteUuid(m_face_packing_id))
      break;

    const bool bSyncFacePackingHashSerialNumbers
      = m_face_packing_topology_hash.IsNotEmpty()
      && this->RuntimeSerialNumber == m_face_packing_topology_hash.SubDRuntimeSerialNumber()
      && gsn > 0 && gsn == m_face_packing_topology_hash.SubDGeometryContentSerialNumber()
      ;
    if (false == archive.WriteBool(bSyncFacePackingHashSerialNumbers))
      break;

    if (false == m_face_packing_topology_hash.Write(archive))
      break;

    rc = true;
    break;
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;
  if (rc)
    return true;
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubDimple::Read(
  ON_BinaryArchive& archive,
  class ON_SubD& subd
  )
{
  m_heap.Clear();
  int major_version = 0;
  int minor_version = 0;
  if ( !archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version) )
    return ON_SUBD_RETURN_ERROR(false);
  bool rc = false;


  // Code before Feb 10, 2020 cared about these values
  unsigned int obsolete_archive_max_vertex_id = 0;
  unsigned int obsolete_archive_max_edge_id = 0;
  unsigned int obsolete_archive_max_face_id = 0;

  bool bSubDIsSymmetric = false;
  bool bSyncFacePackingHashSerialNumbers = false;

  for (;;)
  {
    if (1 != major_version)
      break;

    unsigned int i;
    if (!archive.ReadInt(&i))
      break;
    const unsigned int level_count = i;

    if (!archive.ReadInt(&obsolete_archive_max_vertex_id))
      break;
    if (!archive.ReadInt(&obsolete_archive_max_edge_id))
      break;
    if (!archive.ReadInt(&obsolete_archive_max_face_id))
      break;


    ON_BoundingBox bbox_unsued_after_May_2015;
    if (!archive.ReadBoundingBox(bbox_unsued_after_May_2015))
      break;

    ON_SubDArchiveIdMap element_list;

    unsigned int level_index;
    for (level_index = 0; level_index < level_count; level_index++)
    {
      ON_SubDLevel* level = SubDLevel(level_index,true);
      if ( nullptr == level )
        break;
      if (false == level->Read(archive, element_list, subd ) )
        break;
      m_active_level = level;
    }

    if ( level_index != level_count)
      break;

    if (minor_version >= 1)
    {
      unsigned char obsolete_texture_domain_type = 0;
      if (false == archive.ReadChar(&obsolete_texture_domain_type))
        break;      
      m_texture_coordinate_type = ON_SubD::TextureCoordinateTypeFromObsoleteTextureDomainType(obsolete_texture_domain_type);

      if (false == m_texture_mapping_tag.Read(archive))
        break;

      if (minor_version >= 2)
      {
        if (false == m_symmetry.Read(archive))
          break;

        if (minor_version >= 3)
        {
          // 
          ON__UINT64 legacy_gsn_at_save_time = 0;
          if (false == archive.ReadBigInt(&legacy_gsn_at_save_time))
            break;

          if (minor_version >= 4)
          {
            // minor version = 4 additions
            if (false == archive.ReadBool(&bSubDIsSymmetric))
              break;
            if (false == archive.ReadUuid(m_face_packing_id))
              break;
            if (false == archive.ReadBool(&bSyncFacePackingHashSerialNumbers))
              break;
            if (false == m_face_packing_topology_hash.Read(archive))
              break;
          }
        }
      }
    }

    rc = true;
    break;
  }
  if (!archive.EndRead3dmChunk())
    rc = false;

  // Heap id validation. Always an error if max_heap_..._id > m_max_..._id.
  if (false == m_heap.IsValid(false,nullptr))
  {
    ON_SUBD_ERROR("m_heap.IsValid() is false.");
    m_heap.ResetIds(); // breaks component id references, but this is a serious error.
  }

  if (archive.ArchiveOpenNURBSVersion() < 2382394661)
  {
    // try to get texture information set correctly when it comes from old files
    const ON_MappingTag file_tag = this->TextureMappingTag(true);
    ON_MappingTag new_tag = file_tag;
    
    const ON_SubDTextureCoordinateType file_type = this->TextureCoordinateType();
    ON_SubDTextureCoordinateType new_type = file_type;

    if (ON_TextureMapping::TYPE::srfp_mapping == file_tag.m_mapping_type)
    {
      new_tag = ON_MappingTag::SurfaceParameterMapping;
      if (ON_SubDTextureCoordinateType::FromMapping == file_type || ON_SubDTextureCoordinateType::Unset == file_type)
        new_type = ON_SubDTextureCoordinateType::Packed;
    }
    else
    {
      const bool bTagIsSet
        = ON_TextureMapping::TYPE::srfp_mapping != file_tag.m_mapping_type
        && ON_TextureMapping::TYPE::no_mapping != file_tag.m_mapping_type
        && file_tag.IsSet()
        ;
      if (ON_SubDTextureCoordinateType::Unset == file_type)
      {
        if (bTagIsSet)
          new_type = ON_SubDTextureCoordinateType::FromMapping;
        else
          new_tag = ON_MappingTag::Unset;
      }
      else if (ON_SubDTextureCoordinateType::FromMapping == file_type)
      {
        if (false == bTagIsSet)
        {
          new_tag = ON_MappingTag::Unset;
          new_type = ON_SubDTextureCoordinateType::Packed;
        }
      }
    }

    if (0 != ON_MappingTag::CompareAll(file_tag, new_tag))
      this->SetTextureMappingTag(new_tag);
    if (file_type != new_type)
      this->SetTextureCoordinateType(new_type);
  }

  ChangeGeometryContentSerialNumber(false);


  ///////////////////////////////////////////
  //
  // No changes to "this SubD" below here.
  // 
  // The rest is updating information that is used to determine if this SubD
  // is the same SubD that existed when symmetry and texture information
  // was saved. It's ok if this is not the same subd. If and when appropriate
  // something downstream will update either the SubD or the symmetry/texture 
  // information.
  // It most certainly is NOT appropriate to update any of that here.
  //

  if (bSubDIsSymmetric)
    m_symmetry.SetSymmetricObject(this);
  else
    m_symmetry.ClearSymmetricObject();

  if (bSyncFacePackingHashSerialNumbers)
  {
    // When the file was saved, the values of subd.GeometryContentSerialNumber() and
    // and m_face_packing_topology_hash.SubDGeometryContentSerialNumber() were the same.
    m_face_packing_topology_hash.m_subd_runtime_serial_number = this->RuntimeSerialNumber;
    m_face_packing_topology_hash.m_subd_geometry_content_serial_number = this->GeometryContentSerialNumber();
  }
  else
  {
    m_face_packing_topology_hash.m_subd_runtime_serial_number = 0;
    m_face_packing_topology_hash.m_subd_geometry_content_serial_number = 0;
  }

  if (rc)
    return true;
  return ON_SUBD_RETURN_ERROR(false);
}

//virtual
bool ON_SubD::Write(
  ON_BinaryArchive& archive
  ) const // override
{
  for (;;)
  {
    const ON_SubDimple* subdimple = SubDimple();
    unsigned char c = (nullptr == subdimple) ? 0 : 1;
    if (!archive.WriteChar(c))
      break;
    if (nullptr != subdimple)
    {
      if (!subdimple->Write(archive))
        break;
    }
    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}

//virtual
bool ON_SubD::Read(
  ON_BinaryArchive& archive
  ) // override
{
  Destroy();
  for (;;)
  {
    unsigned char c = 0;
    if (!archive.ReadChar(&c))
      break;
    if (1 == c)
    {
      ON_SubDimple* subdimple = SubDimple(true);
      if ( nullptr == subdimple)
        break;
      if (false == subdimple->Read(archive,*this))
      {
        Destroy();
        break;
      }
    }
    else if ( 0 != c )
      break;

    return true;
  }
  return ON_SUBD_RETURN_ERROR(false);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
// ON_SubDMeshProxyUserData
//

ON_OBJECT_IMPLEMENT(ON_SubDMeshProxyUserData,ON_UserData,"2868B9CD-28AE-4EA7-8073-BD390B3E97C8");

const bool ON_SubDMeshProxyUserData::Internal_MeshHasFaces(const ON_Mesh* mesh)
{
  for (;;)
  {
    if (nullptr == mesh)
      break;
    if (mesh->m_F.UnsignedCount() <= 0)
      break;
    if (mesh->m_V.UnsignedCount() <= 2)
      break;
    return true;
  }
  return false;
}

const ON_SHA1_Hash ON_SubDMeshProxyUserData::Internal_FaceSHA1(const ON_Mesh* mesh)
{
  if (false == ON_SubDMeshProxyUserData::Internal_MeshHasFaces(mesh))
    return ON_SHA1_Hash::EmptyContentHash;

  ON_SHA1 sha1;
  const ON_MeshFace* f = mesh->m_F.Array();
  sha1.AccumulateBytes(f, mesh->m_F.UnsignedCount() * sizeof(*f));
  return sha1.Hash();
}

const ON_SHA1_Hash ON_SubDMeshProxyUserData::Internal_VertexSHA1(const ON_Mesh* mesh)
{
  if (false == ON_SubDMeshProxyUserData::Internal_MeshHasFaces(mesh))
    return ON_SHA1_Hash::EmptyContentHash;

  ON_SHA1 sha1;
  const ON_3fPoint* v = mesh->m_V.Array();
  sha1.AccumulateBytes(v, mesh->m_V.UnsignedCount() * sizeof(*v));
  return sha1.Hash();
}


void ON_SubDMeshProxyUserData::Internal_CopyFrom(const ON_SubDMeshProxyUserData& src)
{
  if ( src.IsValid() )
  {
    m_subd = new ON_SubD(*src.m_subd);
    m_mesh_face_count = src.m_mesh_face_count;
    m_mesh_vertex_count = src.m_mesh_vertex_count;
    m_mesh_face_array_sha1 = src.m_mesh_face_array_sha1;
    m_mesh_vertex_array_sha1 = src.m_mesh_vertex_array_sha1;
  }
}

void ON_SubDMeshProxyUserData::Internal_Destroy()
{
  if (nullptr != m_subd)
  {
    delete m_subd;
    m_subd = nullptr;
  }
  m_mesh_face_count = 0;
  m_mesh_vertex_count = 0;
  m_mesh_face_array_sha1 = ON_SHA1_Hash::EmptyContentHash;
  m_mesh_vertex_array_sha1 = ON_SHA1_Hash::EmptyContentHash;
}


const ON_SubDDisplayParameters ON_SubDMeshProxyUserData::MeshProxyDisplayParameters()
{
  return ON_SubDDisplayParameters::CreateFromDisplayDensity(4);

}

ON_Mesh* ON_SubDMeshProxyUserData::MeshProxyFromSubD(
  const ON_SubD* subd
)
{
  ON_Mesh* mesh = nullptr;
  ON_SubD* subd_copy = nullptr;

  for (;;)
  {
    if (nullptr == subd)
      break;
    subd_copy = new ON_SubD(*subd);
    if (nullptr == subd_copy)
      break;
    mesh = subd_copy->GetControlNetMesh(nullptr, ON_SubDGetControlNetMeshPriority::Geometry);
    if (false == ON_SubDMeshProxyUserData::Internal_MeshHasFaces(mesh))
      break;
    ON_SubDMeshProxyUserData* ud = new ON_SubDMeshProxyUserData();
    ud->m_subd = subd_copy;
    ud->m_mesh_face_count = mesh->FaceUnsignedCount();
    ud->m_mesh_vertex_count = mesh->VertexUnsignedCount();
    ud->m_mesh_face_array_sha1 = ON_SubDMeshProxyUserData::Internal_FaceSHA1(mesh);
    ud->m_mesh_vertex_array_sha1 = ON_SubDMeshProxyUserData::Internal_VertexSHA1(mesh);
    if (false == mesh->AttachUserData(ud))
    {
      ud->m_subd = nullptr;
      delete ud;
      break;
    }
    return mesh;
  }
  
  if (nullptr != mesh)
    delete mesh;
  
  if (nullptr != subd_copy)
    delete subd_copy;

  return nullptr;
}


ON_SubD* ON_SubDMeshProxyUserData::SubDFromMeshProxy(
  const ON_Mesh* mesh
)
{
  ON_SubD* subd = nullptr;
  ON_SubDMeshProxyUserData* ud = nullptr;
  
  for (;;)
  {
    if (nullptr == mesh)
      break;
    const ON_UUID udid = ON_CLASS_ID(ON_SubDMeshProxyUserData);
    ud = ON_SubDMeshProxyUserData::Cast(mesh->GetUserData(udid));
    if (nullptr == ud)
      break;
    if (false == ud->IsValid())
      break;
    if (false == ud->ParentMeshValid())
      break;
    subd = ud->m_subd;
    ud->m_subd = nullptr;
  }
  
  if (nullptr != ud)
    delete ud;

  return subd;
}


bool ON_SubDMeshProxyUserData::IsSubDMeshProxy(
  const ON_Mesh* mesh
)
{
  return false;
}


ON_SubDMeshProxyUserData::ON_SubDMeshProxyUserData()
{
  m_userdata_uuid = ON_CLASS_ID(ON_SubDMeshProxyUserData);
  m_application_uuid = ON_opennurbs6_id; // opennurbs.dll reads/writes this userdata
                                         // The id must be the version 4 id because
                                         // V5 SaveAs V4 needs to work.
  m_userdata_copycount = 1;
}


ON_SubDMeshProxyUserData::~ON_SubDMeshProxyUserData()
{
  Internal_Destroy();
}


ON_SubDMeshProxyUserData::ON_SubDMeshProxyUserData(const ON_SubDMeshProxyUserData& src)
  : ON_UserData(src)
{
  Internal_CopyFrom(src);
}


ON_SubDMeshProxyUserData& ON_SubDMeshProxyUserData::operator=(const ON_SubDMeshProxyUserData& src)
{
  if (this != &src)
  {
    Internal_Destroy();
    Internal_CopyFrom(src);
  }
  return *this;
}
 
bool ON_SubDMeshProxyUserData::Write(ON_BinaryArchive& archive) const
{
  const int chunk_version = 1;
  if ( false == archive.BeginWrite3dmAnonymousChunk(chunk_version) )
    return false;

  bool rc = false;

  for (;;)
  {
    const bool bIsValid = IsValid();
    if (!archive.WriteBool(bIsValid))
      break;

    if (false == bIsValid)
    {
      rc = true;
      break;
    }

    if (!m_subd->Write(archive))
      break;
    if (!archive.WriteInt(m_mesh_face_count))
      break;
    if (!archive.WriteInt(m_mesh_vertex_count))
      break;
    if (!m_mesh_face_array_sha1.Write(archive))
      break;
    if (!m_mesh_vertex_array_sha1.Write(archive))
      break;

    rc = true;
    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_SubDMeshProxyUserData::Read(ON_BinaryArchive& archive)
{
  Internal_Destroy();

  int chunk_version = 0;
  if ( false == archive.BeginRead3dmAnonymousChunk(&chunk_version) )
    return false;

  bool rc = false;

  for (;;)
  {
    if (chunk_version <= 0)
      break;
    bool bIsValid = false;

    if (!archive.ReadBool(&bIsValid))
      break;

    if (false == bIsValid)
    {
      rc = true;
      break;
    }

    m_subd = new ON_SubD();
    if (!m_subd->Read(archive))
      break;
    if (!archive.ReadInt(&m_mesh_face_count))
      break;
    if (!archive.ReadInt(&m_mesh_vertex_count))
      break;
    if (!m_mesh_face_array_sha1.Read(archive))
      break;
    if (!m_mesh_vertex_array_sha1.Read(archive))
      break;

    rc = true;
    break;
  }

  if (!archive.EndRead3dmChunk())
    rc = false;
  
  if (!rc || !IsValid())
    Internal_Destroy();

  return rc;
}


bool ON_SubDMeshProxyUserData::ParentMeshValid() const
{
  for (;;)
  {
    if (!IsValid())
      break;

    const ON_Mesh* mesh = ON_Mesh::Cast(Owner());
    if (false == ON_SubDMeshProxyUserData::Internal_MeshHasFaces(mesh))
      break;

    if (m_mesh_face_count != mesh->m_F.UnsignedCount())
      break;

    if (m_mesh_vertex_count != mesh->m_V.UnsignedCount())
      break;

    const ON_SHA1_Hash f_sha1 = ON_SubDMeshProxyUserData::Internal_FaceSHA1(mesh);
    if (f_sha1 != m_mesh_face_array_sha1)
      break;
    
    const ON_SHA1_Hash v_sha1 = ON_SubDMeshProxyUserData::Internal_VertexSHA1(mesh);
    if (v_sha1 != m_mesh_vertex_array_sha1)
      break;

    return true;
  }

  m_mesh_face_count = 0;
  m_mesh_vertex_count = 0;
  m_mesh_face_array_sha1 = ON_SHA1_Hash::EmptyContentHash;
  m_mesh_vertex_array_sha1 = ON_SHA1_Hash::EmptyContentHash;

  return false;
}

bool ON_SubDMeshProxyUserData::IsValid(
  class ON_TextLog* text_log
) const
{
  for (;;)
  {
    if (nullptr == m_subd)
      break;
    if (m_mesh_face_count <= 0 )
      break;
    if (m_mesh_vertex_count <= 2 )
      break;
    if (ON_SHA1_Hash::EmptyContentHash == m_mesh_face_array_sha1)
      break;
    if (ON_SHA1_Hash::EmptyContentHash == m_mesh_vertex_array_sha1)
      break;
    if (false == m_userdata_xform.IsIdentity())
      break;

    return true;
  }

  return false;
}


bool ON_SubDMeshProxyUserData::GetDescription(ON_wString& description)
{
  if (IsValid())
    description = L"SubD attached to a valid proxy mesh.";
  else
    description = L"SubD attached to an invalid proxy mesh.";
  return true;
}


bool ON_SubDMeshProxyUserData::WriteToArchive(
  const class ON_BinaryArchive& archive,
  const class ON_Object* parent_object
) const
{
  for (;;)
  {
    if (archive.Archive3dmVersion() < 60)
      break;
    if (false == IsValid())
      return false;
    if (false == ParentMeshValid())
      return false;
    return true;
  }

  return false;
}
 
