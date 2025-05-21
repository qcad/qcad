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


ON_SubDToBrepParameters::VertexProcess ON_SubDToBrepParameters::VertexProcessFromUnsigned(
  unsigned int vertex_process_as_unsigned
)
{
  switch (vertex_process_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDToBrepParameters::VertexProcess::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDToBrepParameters::VertexProcess::LocalG1);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDToBrepParameters::VertexProcess::LocalG2);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDToBrepParameters::VertexProcess::LocalG1x);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDToBrepParameters::VertexProcess::LocalG1xx);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDToBrepParameters::VertexProcess::None);
}

const ON_wString ON_SubDToBrepParameters::VertexProcessToString(
  ON_SubDToBrepParameters::VertexProcess vertex_process
)
{
  const wchar_t* s;
  switch (vertex_process)
  {
  case ON_SubDToBrepParameters::VertexProcess::None:
    s = L"None";
    break;
  case ON_SubDToBrepParameters::VertexProcess::LocalG1:
    s = L"G1";
    break;
  case ON_SubDToBrepParameters::VertexProcess::LocalG2:
    s = L"G2";
    break;
  case ON_SubDToBrepParameters::VertexProcess::LocalG1x:
    s = L"G1x";
    break;
  case ON_SubDToBrepParameters::VertexProcess::LocalG1xx:
    s = L"G1xx";
    break;
  default:
    s = L"INVALID";
    break;
  }
  return ON_wString(s);
}

ON_SubDToBrepParameters::VertexProcess ON_SubDToBrepParameters::ExtraordinaryVertexProcess() const
{
  return m_extraordinary_vertex_process;
}


int ON_SubDToBrepParameters::Compare(
  const ON_SubDToBrepParameters& lhs,
  const ON_SubDToBrepParameters& rhs
)
{
  unsigned int a = lhs.m_bPackFaces ? 1 : 0;
  unsigned int b = rhs.m_bPackFaces ? 1 : 0;
  if (a < b)
    return -1;
  if (a > b)
    return 1;

  a = static_cast<unsigned char>(lhs.m_extraordinary_vertex_process);
  b = static_cast<unsigned char>(rhs.m_extraordinary_vertex_process);
  if (a < b)
    return -1;
  if (a > b)
    return 1;

  return 0;
}

int ON_SubDToBrepParameters::CompareFromPointers(
  const ON_SubDToBrepParameters* lhs,
  const ON_SubDToBrepParameters* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  return ON_SubDToBrepParameters::Compare(*lhs, *rhs);
}

bool operator==(const ON_SubDToBrepParameters& lhs, const ON_SubDToBrepParameters& rhs)
{
  return 0 == ON_SubDToBrepParameters::Compare(lhs, rhs);
}

bool operator!=(const ON_SubDToBrepParameters& lhs, const ON_SubDToBrepParameters& rhs)
{
  return (0 != ON_SubDToBrepParameters::Compare(lhs, rhs));
}

void ON_SubDToBrepParameters::SetExtraordinaryVertexProcess(
  ON_SubDToBrepParameters::VertexProcess ev_process
)
{
  m_extraordinary_vertex_process = ev_process;
}

bool ON_SubDToBrepParameters::PackFaces() const
{
  return m_bPackFaces;
}

void ON_SubDToBrepParameters::SetPackFaces(
  bool bPackFaces
)
{
  m_bPackFaces = bPackFaces ? true : false;
}

const ON_wString ON_SubDToBrepParameters::ToString( bool bVerbose ) const
{
  const ON_wString exvtx(ON_SubDToBrepParameters::VertexProcessToString(ExtraordinaryVertexProcess()));
  const ON_wString faces(PackFaces() ? L"Packed" : L"Unpacked");

  const ON_wString s = ON_wString::FormatToString(L"Faces = %ls ExtraordinaryVertex = %ls",
    static_cast<const wchar_t*>(faces),
    static_cast<const wchar_t*>(exvtx)
    );

  return bVerbose ? (ON_wString(L"ON_SubDToBrepParameters: ") + s) : s;
}

bool ON_SubDToBrepParameters::Read(ON_BinaryArchive& archive)
{
  *this = ON_SubDToBrepParameters::Default;
  int version = 0;
  if (false == archive.BeginRead3dmAnonymousChunk(&version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (version < 1)
      break;

    bool bPackFaces = this->PackFaces();
    if (false == archive.ReadBool(&bPackFaces))
      break;
    this->SetPackFaces(bPackFaces);

    unsigned u = static_cast<unsigned char>(this->ExtraordinaryVertexProcess());
    if (false == archive.ReadInt(&u))
      break;
    ON_SubDToBrepParameters::VertexProcess exvtx = ON_SubDToBrepParameters::VertexProcessFromUnsigned(u);
    this->SetExtraordinaryVertexProcess(exvtx);

    rc = true;
    break;
  }

  if (false == archive.EndRead3dmChunk())
    rc = false;
  return rc;
}

bool ON_SubDToBrepParameters::Write(ON_BinaryArchive& archive) const
{
  if (false == archive.BeginWrite3dmAnonymousChunk(1))
    return false;

  bool rc = false;
  for (;;)
  {
    if (false == archive.WriteBool(PackFaces()))
      break;
    const unsigned u = static_cast<unsigned char>(this->ExtraordinaryVertexProcess());
    if (false == archive.WriteInt(u))
      break;
    rc = true;
    break;
  }

  if (false == archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

ON_SubDComponentPtr::Type ON_SubDComponentPtr::ComponentPtrTypeFromUnsigned(
  unsigned int element_pointer_type_as_unsigned
  )
{
  switch (element_pointer_type_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDComponentPtr::Type::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDComponentPtr::Type::Vertex);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDComponentPtr::Type::Edge);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDComponentPtr::Type::Face);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDComponentPtr::Type::Unset);
}

ON_SubDVertexTag ON_SubD::VertexTagFromUnsigned(
  unsigned int vertex_tag_as_unsigned
  )
{
  switch (vertex_tag_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDVertexTag::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDVertexTag::Smooth);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDVertexTag::Crease);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDVertexTag::Corner);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDVertexTag::Dart);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDVertexTag::Unset);
}

const ON_wString ON_SubD::VertexTagToString(
  ON_SubDVertexTag vertex_tag,
  bool bVerbose
)
{
  const wchar_t* tag_name;
  switch (vertex_tag)
  {
  case ON_SubDVertexTag::Unset:
    tag_name = L"Unset";
    break;
  case ON_SubDVertexTag::Smooth:
    tag_name = L"Smooth";
    break;
  case ON_SubDVertexTag::Crease:
    tag_name = L"Crease";
    break;
  case ON_SubDVertexTag::Corner:
    tag_name = L"Corner";
    break;
  case ON_SubDVertexTag::Dart:
    tag_name = L"Dart";
    break;
  default:
    tag_name = L"invalid";
    break;
  }
  return bVerbose ? ON_wString::FormatToString(L"ON_SubDVertexTag::%ls", tag_name) : ON_wString(tag_name);
}

const ON_wString ON_SubDVertex::ToString(
  bool bIncludeControlNetPoint,
  bool bIncludeTopology
) const
{
  const ON_wString vtag = ON_SubD::VertexTagToString(m_vertex_tag,false);
  ON_wString v
    = bIncludeControlNetPoint
    ? ON_wString::FormatToString(L"v%u %ls (%g,%g,%g)", m_id, static_cast<const wchar_t*>(vtag), m_P[0], m_P[1], m_P[2])
    : ON_wString::FormatToString(L"v%u %ls", m_id, static_cast<const wchar_t*>(vtag))
    ;
  if (bIncludeTopology)
  {
    ON_wString elist = ON_wString::FormatToString(L" Edges[%u]", EdgeCount());
    if (nullptr != m_edges && m_edge_count > 0)
    {
      elist += L"={";
      for (unsigned short vei = 0; vei < m_edge_count; ++vei)
      {
        const ON_SubDEdgePtr eptr = m_edges[vei];
        const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
        if (vei > 0)
          elist += L", ";
        if (nullptr == e)
          elist += L"Null";
        else
        {
          elist += (0 == ON_SUBD_EDGE_DIRECTION(eptr.m_ptr)) ? ON_wString::FormatToString(L"+e%u", e->m_id) : ON_wString::FormatToString(L"-e%u", e->m_id);
        }
      }
      elist += L"}";
    }
    v += elist;

    ON_wString flist = ON_wString::FormatToString(L" Faces[%u]", FaceCount());
    if (nullptr != m_faces && m_face_count > 0)
    {
      flist += L"={";
      for (unsigned short vfi = 0; vfi < m_face_count; ++vfi)
      {
        const ON_SubDFace* f = m_faces[vfi];
        if (vfi > 0)
          flist += L", ";
        if (nullptr == f)
          flist += L"Null";
        else
        {
          flist += ON_wString::FormatToString(L"f%u", f->m_id);
        }
      }
      flist += L"}";
    }
    v += flist;
  }
  return v;
}


bool ON_SubD::VertexTagIsSet(
  ON_SubDVertexTag vertex_tag
)
{
  return (
    ON_SubDVertexTag::Smooth == vertex_tag
    || ON_SubDVertexTag::Crease == vertex_tag
    || ON_SubDVertexTag::Corner == vertex_tag
    || ON_SubDVertexTag::Dart == vertex_tag
    );
}


ON_SubDEdgeTag ON_SubD::EdgeTagFromUnsigned(
  unsigned int edge_tag_as_unsigned
  )
{
  switch (edge_tag_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDEdgeTag::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDEdgeTag::Smooth);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDEdgeTag::Crease);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDEdgeTag::SmoothX);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDEdgeTag::Unset);
}


const ON_wString ON_SubD::EdgeTagToString(
  ON_SubDEdgeTag edge_tag,
  bool bVerbose
)
{
  const wchar_t* tag_name;
  switch (edge_tag)
  {
  case ON_SubDEdgeTag::Unset:
    tag_name = L"Unset";
    break;
  case ON_SubDEdgeTag::Smooth:
    tag_name = L"Smooth";
    break;
  case ON_SubDEdgeTag::Crease:
    tag_name = L"Crease";
    break;
  case ON_SubDEdgeTag::SmoothX:
    tag_name = L"SmoothX";
    break;
  default:
    tag_name = L"invalid";
    break;
  }
  return bVerbose ? ON_wString::FormatToString(L"ON_SubDEdgeTag::%ls", tag_name) : ON_wString(tag_name);
}


bool ON_SubD::EdgeTagIsSet(
  ON_SubDEdgeTag edge_tag
)
{
  return (
    ON_SubDEdgeTag::Smooth == edge_tag
    || ON_SubDEdgeTag::Crease == edge_tag
    || ON_SubDEdgeTag::SmoothX == edge_tag
    );
}

ON_SubD::VertexFacetType ON_SubD::VertexFacetTypeFromUnsigned(
  unsigned int vertex_facet_type_as_unsigned
  )
{
  switch (vertex_facet_type_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubD::VertexFacetType::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubD::VertexFacetType::Tri);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubD::VertexFacetType::Quad);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubD::VertexFacetType::Ngon);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_SubD::VertexFacetType::Mixed);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubD::VertexFacetType::Unset);
}

unsigned int ON_SubDSectorType::SectorPointRingCountFromEdgeCount(
  ON_SubDVertexTag vertex_tag,
  unsigned int sector_edge_count
  )
{
  if (sector_edge_count >= ON_SubDSectorType::MinimumSectorEdgeCount(vertex_tag) && sector_edge_count <= ON_SubDVertex::MaximumEdgeCount)
  {
    if (ON_SubDVertexTag::Smooth == vertex_tag || ON_SubDVertexTag::Dart == vertex_tag)
    {
      // interior vertex
      return (2 * sector_edge_count + 1);
    }

    if (ON_SubDVertexTag::Crease == vertex_tag || ON_SubDVertexTag::Corner == vertex_tag)
    {
      // boundary vertex
      return (2 * sector_edge_count);
    }
  }
  return ON_SUBD_RETURN_ERROR(0);
}

unsigned int ON_SubDSectorType::SectorPointRingCountFromFaceCount(
  ON_SubDVertexTag vertex_tag,
  unsigned int sector_face_count
  )
{
  unsigned int sector_edge_count = ON_SubDSectorType::SectorEdgeCountFromFaceCount(vertex_tag,sector_face_count);
  return (sector_edge_count > 0)
    ? ON_SubDSectorType::SectorPointRingCountFromEdgeCount(vertex_tag,sector_edge_count)
    : ON_SUBD_RETURN_ERROR(0);
}

unsigned int ON_SubDSectorType::SectorFaceCountFromEdgeCount(
  ON_SubDVertexTag vertex_tag,
  unsigned int sector_edge_count
  )
{
  if (sector_edge_count >= 2 && sector_edge_count <= ON_SubDVertex::MaximumEdgeCount)
  {
    unsigned int sector_face_count
      = (ON_SubDVertexTag::Crease == vertex_tag || ON_SubDVertexTag::Corner == vertex_tag)
      ? sector_edge_count-1
      : sector_edge_count;
    return sector_face_count;
  }
  return ON_SUBD_RETURN_ERROR(0);
}

unsigned int ON_SubDSectorType::SectorEdgeCountFromFaceCount(
  ON_SubDVertexTag vertex_tag,
  unsigned int sector_face_count
  )
{
  if (sector_face_count > 0 && sector_face_count <= ON_SubDVertex::MaximumFaceCount)
  {
    unsigned int sector_edge_count
      = (ON_SubDVertexTag::Crease == vertex_tag || ON_SubDVertexTag::Corner == vertex_tag)
      ? sector_face_count+1
      : sector_face_count;
    return sector_edge_count;
  }
  return ON_SUBD_RETURN_ERROR(0);
}

unsigned int ON_SubDSectorType::MinimumSectorEdgeCount(
  ON_SubDVertexTag vertex_tag
  )
{
  if (ON_SubDVertexTag::Smooth == vertex_tag || ON_SubDVertexTag::Dart == vertex_tag)
    return ON_SubDSectorType::MinimumSectorFaceCount(vertex_tag);
  if (ON_SubDVertexTag::Corner == vertex_tag || ON_SubDVertexTag::Crease == vertex_tag)
    return ON_SubDSectorType::MinimumSectorFaceCount(vertex_tag)+1;
  return ON_UNSET_UINT_INDEX;
}

unsigned int ON_SubDSectorType::MinimumSectorFaceCount(
  ON_SubDVertexTag vertex_tag
  )
{
  unsigned int minimum_sector_face_count;
  switch (vertex_tag)
  {
  case ON_SubDVertexTag::Unset:
    ON_SUBD_ERROR("Unset tag.");
    minimum_sector_face_count = ON_UNSET_UINT_INDEX;
    break;

  case ON_SubDVertexTag::Smooth:
    // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Smooth
    // See comments in ON_SubDSectorType::GetSurfaceEvaluationCoefficients()
    // for more details on how this case is handled.
    minimum_sector_face_count = 2; // 3 without special case handling
    break;

  case ON_SubDVertexTag::Crease:
    // A "wire" crease can have zero faces - this is the minimum when faces exist
    minimum_sector_face_count = 1;
    break;

  case ON_SubDVertexTag::Corner:
    // A "wire" corner can have zero faces - this is the minimum when faces exist
    minimum_sector_face_count = 1;
    break;

  case ON_SubDVertexTag::Dart:
    // April 2019 Dale Lear - Catmull Clark Valence 2 Evaluation: Dart
    // See comments in ON_SubDSectorType::GetSurfaceEvaluationCoefficients()
    // for more details on how this case is handled.
    minimum_sector_face_count = 2; // 3 without special case handling
    break;

  default:
    ON_SUBD_ERROR("Invalid tag.");
    minimum_sector_face_count = ON_UNSET_UINT_INDEX;
    break;
  }

  return minimum_sector_face_count;
}

bool ON_SubD::IsValidSectorEdgeCount(
  ON_SubDVertexTag vertex_tag,
  unsigned int sector_edge_count
  )
{
  return (sector_edge_count >= ON_SubDSectorType::MinimumSectorEdgeCount(vertex_tag) && sector_edge_count <= ON_SubDVertex::MaximumEdgeCount);
}

bool ON_SubD::IsValidSectorFaceCount(
  ON_SubDVertexTag vertex_tag,
  unsigned int sector_face_count
  )
{
  return (sector_face_count >= ON_SubDSectorType::MinimumSectorFaceCount(vertex_tag) && sector_face_count <= ON_SubDVertex::MaximumFaceCount);
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDVertexPtr
//
//
bool operator==(ON_SubDVertexPtr lhs, ON_SubDVertexPtr rhs)
{
  return lhs.m_ptr == rhs.m_ptr;
}

bool operator!=(ON_SubDVertexPtr lhs, ON_SubDVertexPtr rhs)
{
  return lhs.m_ptr != rhs.m_ptr;
}

bool ON_SubDVertexPtr::IsNull() const
{
  return (nullptr == ON_SUBD_VERTEX_POINTER(m_ptr));
}

bool ON_SubDVertexPtr::IsNotNull() const
{
  return (nullptr != ON_SUBD_VERTEX_POINTER(m_ptr));
}

unsigned int ON_SubDVertexPtr::VertexId() const
{
  const ON_SubDVertex* v = ON_SUBD_VERTEX_POINTER(m_ptr);
  return (nullptr != v) ? v->m_id : 0U;
}

class ON_SubDVertex* ON_SubDVertexPtr::Vertex() const
{
  return ON_SUBD_VERTEX_POINTER(m_ptr);
}

ON__UINT_PTR ON_SubDVertexPtr::VertexDirection() const
{
  return ON_SUBD_VERTEX_DIRECTION(m_ptr);
}

void ON_SubDVertexPtr::ClearSavedSubdivisionPoints() const
{
  const ON_SubDVertex* v = ON_SUBD_VERTEX_POINTER(m_ptr);
  if (nullptr != v)
    v->ClearSavedSubdivisionPoints();
}

void ON_SubDVertexPtr::ClearSavedSubdivisionPoints(
  bool bClearNeighborhood
) const
{
  const ON_SubDVertex* v = ON_SUBD_VERTEX_POINTER(m_ptr);
  if (nullptr != v)
    v->ClearSavedSubdivisionPoints(bClearNeighborhood);
}

const ON_ComponentStatus ON_SubDVertexPtr::Status() const
{
  const ON_SubDVertex* vertex = ON_SUBD_VERTEX_POINTER(m_ptr);
  return (nullptr == vertex) ? ON_ComponentStatus::NoneSet : vertex->m_status;
}

const ON_SubDVertexPtr ON_SubDVertexPtr::Create(
  const class ON_SubDVertex* vertex
  )
{
  return ON_SubDVertexPtr::Create(vertex,0);
}

const ON_SubDVertexPtr ON_SubDVertexPtr::Create(
  const class ON_SubDVertex* vertex,
  ON__UINT_PTR vertex_mark
  )
{
  ON_SubDVertexPtr vptr = { (ON__UINT_PTR)vertex | (vertex_mark & ON_SUBD_COMPONENT_DIRECTION_MASK) };
  return vptr;
}

const ON_SubDVertexPtr ON_SubDVertexPtr::Create(
  const class ON_SubDComponentPtr& vertex_element
  )
{
  return ON_SubDVertexPtr::Create(vertex_element.Vertex(), vertex_element.ComponentDirection());
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDEdgePtr
//
bool operator==(ON_SubDEdgePtr lhs, ON_SubDEdgePtr rhs)
{
  return lhs.m_ptr == rhs.m_ptr;
}

bool operator!=(ON_SubDEdgePtr lhs, ON_SubDEdgePtr rhs)
{
  return lhs.m_ptr != rhs.m_ptr;
}

bool ON_SubDEdgePtr::IsNull() const
{
  return (nullptr == ON_SUBD_EDGE_POINTER(m_ptr));
}

bool ON_SubDEdgePtr::IsNotNull() const
{
  return (nullptr != ON_SUBD_EDGE_POINTER(m_ptr));
}

bool ON_SubDEdgePtr::IsNotNullAndVerticesAreNotNull() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e && nullptr != e->m_vertex[0] && nullptr != e->m_vertex[1]);
}


class ON_SubDEdge* ON_SubDEdgePtr::Edge() const
{
  return ON_SUBD_EDGE_POINTER(m_ptr);
}

unsigned int ON_SubDEdgePtr::EdgeId() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->m_id : 0U;
}

unsigned int ON_SubDEdgePtr::EdgeFaceCount() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? ((unsigned int)e->m_face_count) : 0U;
}

ON_SubDEdgeTag ON_SubDEdgePtr::EdgeTag() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->m_edge_tag : ON_SubDEdgeTag::Unset;
}

bool ON_SubDEdgePtr::EdgeIsSmooth() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->IsSmooth() : false;
}   

bool ON_SubDEdgePtr::EdgeIsSmoothNotSharp() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->IsSmoothNotSharp() : false;
}

bool ON_SubDEdgePtr::EdgeIsSharp() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->IsSharp() : false;
}

bool ON_SubDEdgePtr::EdgeIsCreaseOrSharp() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->IsCreaseOrSharp() : false;
}

bool ON_SubDEdgePtr::EdgeIsCrease() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->IsCrease() : false;
}   

bool ON_SubDEdgePtr::EdgeIsHardCrease() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->IsHardCrease() : false;
}   

bool ON_SubDEdgePtr::EdgeIsDartCrease() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->IsDartCrease() : false;
}

bool ON_SubDEdgePtr::HasInteriorEdgeTopology(
  bool bRequireOppositeFaceDirections
) const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->HasInteriorEdgeTopology(bRequireOppositeFaceDirections) : false;
}

ON__UINT_PTR ON_SubDEdgePtr::EdgeDirection() const
{
  return ON_SUBD_EDGE_DIRECTION(m_ptr);
}

const ON_3dPoint ON_SubDEdgePtr::SubdivisionPoint() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->SubdivisionPoint() : ON_3dPoint::NanPoint;
}

void ON_SubDEdgePtr::ClearSavedSubdivisionPoints() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  if (nullptr != e)
    e->ClearSavedSubdivisionPoints();
}

void ON_SubDEdgePtr::ClearSavedSubdivisionPoints(
  bool bClearNeighborhood
) const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  if (nullptr != e)
    e->ClearSavedSubdivisionPoints(bClearNeighborhood);
}

const class ON_SubDVertex* ON_SubDEdgePtr::RelativeVertex(
  int relative_vertex_index
  ) const
{
  for (;;)
  {
    if (relative_vertex_index < 0 || relative_vertex_index>1)
      break;
    const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(m_ptr);
    if (nullptr == edge)
      break;
    if (0 != ON_SUBD_EDGE_DIRECTION(m_ptr))
      relative_vertex_index = 1 - relative_vertex_index;
    return edge->m_vertex[relative_vertex_index];
  }
  return nullptr;
}

ON_SubDVertexTag ON_SubDEdgePtr::RelativeVertexTag(
  int relative_vertex_index
) const
{
  const ON_SubDVertex* v = this->RelativeVertex(relative_vertex_index);
  return (nullptr != v) ? v->m_vertex_tag : ON_SubDVertexTag::Unset;
}

const ON_3dPoint ON_SubDEdgePtr::RelativeVertexPoint(
  int relative_vertex_index,
  ON_SubDComponentLocation point_location
) const
{
  const ON_SubDVertex* v = this->RelativeVertex(relative_vertex_index);
  return (nullptr != v) ? v->Point(point_location) : ON_3dPoint::NanPoint;
}


const ON_3dPoint ON_SubDEdgePtr::RelativeVertexSurfacePoint(
  int relative_vertex_index
) const
{
  const ON_SubDVertex* v = this->RelativeVertex(relative_vertex_index);
  return (nullptr != v) ? v->SurfacePoint() : ON_3dPoint::NanPoint;
}


unsigned ON_SubDEdgePtr::RelativeVertexId(int relative_vertex_index) const
{
  const ON_SubDVertex* v = this->RelativeVertex(relative_vertex_index);
  return (nullptr != v) ? v->m_id : 0U;
}

bool ON_SubDEdgePtr::RelativeVertexMark(
  int relative_vertex_index,
  bool missing_vertex_return_value
) const
{
  const ON_SubDVertex* v = this->RelativeVertex(relative_vertex_index);
  return (nullptr != v) ? v->Mark() : missing_vertex_return_value;
}

ON__UINT8 ON_SubDEdgePtr::RelativeVertexMarkBits(
  int relative_vertex_index,
  ON__UINT8 missing_vertex_return_value
) const
{
  const ON_SubDVertex* v = this->RelativeVertex(relative_vertex_index);
  return (nullptr != v) ? v->MarkBits() : missing_vertex_return_value;
}


const ON_3dPoint ON_SubDEdgePtr::RelativeControlNetPoint(
  int relative_vertex_index
) const
{
  const ON_SubDVertex* v = RelativeVertex(relative_vertex_index);
  return (nullptr != v) ? v->ControlNetPoint() : ON_3dPoint::NanPoint;
}

const ON_Line ON_SubDEdgePtr::RelativeControlNetLine() const
{
  return ON_Line(RelativeControlNetPoint(0), RelativeControlNetPoint(1));
}

const ON_3dVector ON_SubDEdgePtr::RelativeControlNetDirection() const
{
  return RelativeControlNetLine().Direction();
}

double ON_SubDEdgePtr::RelativeSectorCoefficient(
  int relative_vertex_index
) const
{
  for (;;)
  {
    if (relative_vertex_index < 0 || relative_vertex_index>1)
      break;
    const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(m_ptr);
    if (nullptr == edge)
      break;
    if (0 != ON_SUBD_EDGE_DIRECTION(m_ptr))
      relative_vertex_index = 1 - relative_vertex_index;
    return edge->m_sector_coefficient[relative_vertex_index];
  }
  return ON_SubDSectorType::ErrorSectorCoefficient;
}

void  ON_SubDEdgePtr::SetRelativeSectorCoefficientForExperts(
  int relative_vertex_index,
  double relative_sector_coefficient
) const
{
  for (;;)
  {
    if (relative_vertex_index < 0 || relative_vertex_index>1)
      break;
    const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(m_ptr);
    if (nullptr == edge)
      break;
    if (0 != ON_SUBD_EDGE_DIRECTION(m_ptr))
      relative_vertex_index = 1 - relative_vertex_index;
    edge->m_sector_coefficient[relative_vertex_index] = relative_sector_coefficient;
    break;
  }
}


const ON_SubDEdgeSharpness ON_SubDEdgePtr::RelativeSharpness(bool bUseCreaseSharpness) const
{
  const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(m_ptr);
  if (nullptr != edge)
  {
    const ON_SubDEdgeSharpness s = edge->Sharpness(bUseCreaseSharpness);
    return (0 == ON_SUBD_EDGE_DIRECTION(m_ptr)) ? s : s.Reversed();
  }
  return ON_SubDEdgeSharpness::Nan;
}

void ON_SubDEdgePtr::SetRelativeSharpness(ON_SubDEdgeSharpness relative_sharpness) const
{
  ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(m_ptr);
  if (nullptr != edge)
    edge->SetSharpnessForExperts(
      (0 == ON_SUBD_EDGE_DIRECTION(m_ptr))
      ? relative_sharpness 
      : relative_sharpness.Reversed()
    );
}

const ON_3dVector ON_SubDEdgePtr::RelativeDirection() const
{
  for (;;)
  {
    const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(m_ptr);
    if (nullptr == edge)
      break;
    if (nullptr == edge->m_vertex[0] || nullptr == edge->m_vertex[1])
      break;
    const int i0 = (0 != ON_SUBD_EDGE_DIRECTION(m_ptr)) ? 1 : 0;
    const ON_3dPoint P0(edge->m_vertex[i0]->m_P);
    const ON_3dPoint P1(edge->m_vertex[1-i0]->m_P);
    return (P1 - P0);
  }
  return ON_3dVector::NanVector;
}

const class ON_SubDFace* ON_SubDEdgePtr::EdgeFace(
  int edge_face_index
) const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  if (nullptr == e)
    return nullptr; // null input
  return (edge_face_index >= 0 && edge_face_index < (int)(e->m_face_count)) ? e->Face((unsigned)edge_face_index) : nullptr;
}

const class ON_SubDFace* ON_SubDEdgePtr::RelativeFace(
  int relative_face_index
) const
{
  if (relative_face_index < 0 || relative_face_index > 1)
    return nullptr; // invalid input
  
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  if (nullptr == e )
    return nullptr; // null input

  if (nullptr == e || e->m_face_count > 2)
    return nullptr; // nonmanifold edge

  const ON_SubDFace* LR[2] = {};
  for (unsigned short efi = 0; efi < e->m_face_count; ++efi)
  {
    const ON__UINT_PTR ptr = e->m_face2[efi].m_ptr;
    const ON_SubDFace* f = ON_SUBD_FACE_POINTER(ptr);
    if (nullptr == f)
      continue;
    if (0 == ON_SUBD_FACE_DIRECTION(ptr))
    {
      if (nullptr != LR[0])
        return nullptr; // not an oriented manifold interior edge
      LR[0] = f;
    }
    else
    {
      if (nullptr != LR[1])
        return nullptr; // not an oriented manifold interior edge
      LR[1] = f;
    }
  }

  if (0 != ON_SUBD_EDGE_DIRECTION(m_ptr))
    relative_face_index = 1 - relative_face_index;
  return LR[relative_face_index];
}

bool ON_SubDEdgePtr::RelativeFaceMark(
  int relative_face_index,
  bool missing_face_return_value
) const
{
  const ON_SubDFace* f = this->RelativeFace(relative_face_index);
  return (nullptr != f) ? f->Mark() : missing_face_return_value;
}

ON__UINT8 ON_SubDEdgePtr::RelativeFaceMarkBits(
  int relative_face_index,
  ON__UINT8 missing_face_return_value
) const
{
  const ON_SubDFace* f = this->RelativeFace(relative_face_index);
  return (nullptr != f) ? f->MarkBits() : missing_face_return_value;
}

const ON_ComponentStatus ON_SubDEdgePtr::Status() const
{
  const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr == edge) ? ON_ComponentStatus::NoneSet : edge->m_status;
}

const ON_SubDEdgePtr ON_SubDEdgePtr::Reversed() const
{
  return ON_SubDEdgePtr::Create(ON_SUBD_EDGE_POINTER(m_ptr), 1 - (m_ptr & 1));
}

const ON_SubDEdgePtr ON_SubDEdgePtr::Create(
  const class ON_SubDEdge* edge
  )
{
  ON_SubDEdgePtr eptr = { (ON__UINT_PTR)edge };
  return eptr;
}

const ON_SubDEdgePtr ON_SubDEdgePtr::Create(
  const class ON_SubDEdge* edge,
  ON__UINT_PTR direction
  )
{
  ON_SubDEdgePtr eptr = { (ON__UINT_PTR)edge | (direction & ON_SUBD_COMPONENT_DIRECTION_MASK) };
  return eptr;
}

const ON_SubDEdgePtr ON_SubDEdgePtr::Create(
  const class ON_SubDVertex* v0,
  const class ON_SubDVertex* v1
)
{
  return ON_SubDEdge::FromVertices(v0,v1);
}

const ON_SubDEdgePtr ON_SubDEdgePtr::Create(
  const class ON_SubDComponentPtr& edge_element
  )
{
  return ON_SubDEdgePtr::Create(edge_element.Edge(), edge_element.ComponentDirection());
}

const ON_SubDEdgePtr ON_SubDEdgePtr::CreateFromStartVertex(
  const class ON_SubDEdge* edge,
  const ON_SubDVertex* start_vertex
)
{
  for (;;)
  {
    if (nullptr == edge || nullptr == start_vertex)
      break;
    if (edge->m_vertex[0] == edge->m_vertex[1])
      break;
    
    ON__UINT_PTR dir;
    if (start_vertex == edge->m_vertex[0])
      dir = 0;
    else if (start_vertex == edge->m_vertex[1])
      dir = 1;
    else
      break;
    return ON_SubDEdgePtr::Create(edge, dir);
  }
  return ON_SubDEdgePtr::Null;
}

const ON_SubDEdgePtr ON_SubDEdgePtr::CreateFromEndVertex(
  const class ON_SubDEdge* edge,
  const ON_SubDVertex* end_vertex
)
{
  return CreateFromStartVertex(edge,end_vertex).Reversed();
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFacePtr
//

bool operator==(ON_SubDFacePtr lhs, ON_SubDFacePtr rhs)
{
  return lhs.m_ptr == rhs.m_ptr;
}

bool operator!=(ON_SubDFacePtr lhs, ON_SubDFacePtr rhs)
{
  return lhs.m_ptr != rhs.m_ptr;
}

bool ON_SubDFacePtr::IsNull() const
{
  return (nullptr == ON_SUBD_FACE_POINTER(m_ptr));
}

bool ON_SubDFacePtr::IsNotNull() const
{
  return (nullptr != ON_SUBD_FACE_POINTER(m_ptr));
}

ON_SubDFace* ON_SubDFacePtr::Face() const
{
  return ON_SUBD_FACE_POINTER(m_ptr);
}

void ON_SubDFacePtr::ClearSavedSubdivisionPoints() const
{
  const ON_SubDFace* f = ON_SUBD_FACE_POINTER(m_ptr);
  if (nullptr != f)
    f->ClearSavedSubdivisionPoints();
}

void ON_SubDFacePtr::ClearSavedSubdivisionPoints(
  bool bClearNeighborhood
) const
{
  const ON_SubDFace* f = ON_SUBD_FACE_POINTER(m_ptr);
  if (nullptr != f)
    f->ClearSavedSubdivisionPoints(bClearNeighborhood);
}


unsigned int ON_SubDFacePtr::FaceId() const
{
  const ON_SubDFace* f = ON_SUBD_FACE_POINTER(m_ptr);
  return (nullptr != f) ? f->m_id : 0U;
}

unsigned int ON_SubDFacePtr::FaceEdgeCount() const
{
  const ON_SubDFace* f = ON_SUBD_FACE_POINTER(m_ptr);
  return (nullptr != f) ? ((unsigned int)f->m_edge_count) : 0U;
}

ON__UINT_PTR ON_SubDFacePtr::FaceDirection() const
{
  return ON_SUBD_FACE_DIRECTION(m_ptr);
}

const ON_ComponentStatus ON_SubDFacePtr::Status() const
{
  const ON_SubDFace* face = ON_SUBD_FACE_POINTER(m_ptr);
  return (nullptr == face) ? ON_ComponentStatus::NoneSet : face->m_status;
}

const ON_SubDFacePtr ON_SubDFacePtr::Reversed() const
{
  return ON_SubDFacePtr::Create(ON_SUBD_FACE_POINTER(m_ptr), 1 - (m_ptr & 1));
}

const ON_SubDFacePtr ON_SubDFacePtr::Create(
  const class ON_SubDFace* face,
  ON__UINT_PTR direction
  )
{
  ON_SubDFacePtr fptr = { (ON__UINT_PTR)face | (direction & ON_SUBD_COMPONENT_DIRECTION_MASK) };
  return fptr;
}

const ON_SubDFacePtr ON_SubDFacePtr::Create(
  const class ON_SubDComponentPtr& face_element
  )
{
  return ON_SubDFacePtr::Create(face_element.Face(), face_element.ComponentDirection());
}


int ON_SubDFacePtr::Compare(
  const ON_SubDFacePtr* lhs,
  const ON_SubDFacePtr* rhs
)
{
  if ( nullptr == lhs )
    return 1;
  if ( nullptr == rhs )
    return -1;

  if (lhs->m_ptr < rhs->m_ptr)
    return -1;
  if (lhs->m_ptr > rhs->m_ptr)
    return 1;

  return 0;
}

int ON_SubDFacePtr::CompareFacePointer(
  const ON_SubDFacePtr* lhs,
  const ON_SubDFacePtr* rhs
)
{
  if (lhs == rhs)
    return 0;
  if ( nullptr == lhs )
    return 1;
  if ( nullptr == rhs )
    return -1;

  const ON__UINT_PTR lhs_ptr = (lhs->m_ptr & ON_SUBD_COMPONENT_POINTER_MASK);
  const ON__UINT_PTR rhs_ptr = (rhs->m_ptr & ON_SUBD_COMPONENT_POINTER_MASK);
  if (lhs_ptr < rhs_ptr)
    return -1;
  if (lhs_ptr > rhs_ptr)
    return 1;
  return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentPtr
//

bool operator==(ON_SubDComponentPtr lhs, ON_SubDComponentPtr rhs)
{
  // MUST compare entire m_ptr (type, pointer, and direction)
  return lhs.m_ptr == rhs.m_ptr;
}

bool operator!=(ON_SubDComponentPtr lhs, ON_SubDComponentPtr rhs)
{
  // MUST compare entire m_ptr (type, pointer, and direction)
  return lhs.m_ptr != rhs.m_ptr;
}

bool ON_SubDComponentPtr::IsNull() const
{
  return nullptr == ComponentBase();
}

bool ON_SubDComponentPtr::IsNotNull() const
{
  return nullptr != ComponentBase();
}

unsigned int ON_SubDComponentPtr::ComponentId() const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->m_id : 0U;
}

unsigned int ON_SubDComponentPtr::VertexId() const
{
  const ON_SubDVertex* v = this->Vertex();
  return (nullptr != v) ? v->m_id : 0;
}

unsigned int ON_SubDComponentPtr::EdgeId() const
{
  const ON_SubDEdge* e = this->Edge();
  return (nullptr != e) ? e->m_id : 0;
}

unsigned int ON_SubDComponentPtr::FaceId() const
{
  const ON_SubDFace* f = this->Face();
  return (nullptr != f) ? f->m_id : 0;
}

ON_SubDVertexTag ON_SubDComponentPtr::VertexTag() const
{
  const ON_SubDVertex* v = this->Vertex();
  return (nullptr != v) ? v->m_vertex_tag : ON_SubDVertexTag::Unset;
}

ON_SubDEdgeTag ON_SubDComponentPtr::EdgeTag() const
{
  const ON_SubDEdge* e = this->Edge();
  return (nullptr != e) ? e->m_edge_tag : ON_SubDEdgeTag::Unset;
}

double ON_SubDComponentPtr::VertexSharpness() const
{
  const ON_SubDVertex* v = this->Vertex();
  return (nullptr != v) ? v->VertexSharpness() : ON_DBL_QNAN;
}

const ON_SubDEdgeSharpness ON_SubDComponentPtr::EdgeSharpness(bool bUseCreaseSharpness) const
{
  const ON_SubDEdgePtr eptr = this->EdgePtr();
  return
    eptr.IsNotNull()
    ? eptr.RelativeSharpness(bUseCreaseSharpness)
    : ON_SubDEdgeSharpness::Nan;
}

void ON_SubDComponentPtr::ClearSavedSubdivisionPoints() const
{
  switch (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr)
  {
  case ON_SUBD_COMPONENT_TYPE_VERTEX:
  {
    const ON_SubDVertex* v = Vertex();
    if (nullptr != v)
      v->ClearSavedSubdivisionPoints();
  }
  break;
  case ON_SUBD_COMPONENT_TYPE_EDGE:
  {
    const ON_SubDEdge* e = Edge();
    if (nullptr != e)
      e->ClearSavedSubdivisionPoints();
  }
  break;
  case ON_SUBD_COMPONENT_TYPE_FACE:
  {
    const ON_SubDFace* f = Face();
    if (nullptr != f)
      f->ClearSavedSubdivisionPoints();
  }
  break;
  }
}

void ON_SubDComponentPtr::ClearSavedSubdivisionPoints(
  bool bClearNeighborhood
) const
{
  switch (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr)
  {
  case ON_SUBD_COMPONENT_TYPE_VERTEX:
  {
    const ON_SubDVertex* v = Vertex();
    if (nullptr != v)
      v->ClearSavedSubdivisionPoints(bClearNeighborhood);
  }
  break;
  case ON_SUBD_COMPONENT_TYPE_EDGE:
  {
    const ON_SubDEdge* e = Edge();
    if (nullptr != e)
      e->ClearSavedSubdivisionPoints(bClearNeighborhood);
  }
  break;
  case ON_SUBD_COMPONENT_TYPE_FACE:
  {
    const ON_SubDFace* f = Face();
    if (nullptr != f)
      f->ClearSavedSubdivisionPoints(bClearNeighborhood);
  }
  break;
  }
}

const ON_3dPoint ON_SubDComponentPtr::ControlNetCenterPoint() const
{
  switch (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr)
  {
  case ON_SUBD_COMPONENT_TYPE_VERTEX:
  {
    const ON_SubDVertex* v = Vertex();
    if (nullptr != v)
      return v->ControlNetPoint();
  }
  break;
  case ON_SUBD_COMPONENT_TYPE_EDGE:
  {
    const ON_SubDEdge* e = Edge();
    if (nullptr != e)
      return e->ControlNetCenterPoint();
  }
  break;
  case ON_SUBD_COMPONENT_TYPE_FACE:
  {
    const ON_SubDFace* f = Face();
    if (nullptr != f)
      return f->ControlNetCenterPoint();
  }
  break;
  }
  return ON_3dPoint::NanPoint;
}

const ON_3dPoint ON_SubDComponentPtr::SubdivisionPoint() const
{
  switch (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr)
  {
  case ON_SUBD_COMPONENT_TYPE_VERTEX:
  {
    const ON_SubDVertex* v = Vertex();
    if (nullptr != v)
      return v->SubdivisionPoint();
  }
  break;
  case ON_SUBD_COMPONENT_TYPE_EDGE:
  {
    const ON_SubDEdge* e = Edge();
    if (nullptr != e)
      return e->SubdivisionPoint();
  }
  break;
  case ON_SUBD_COMPONENT_TYPE_FACE:
  {
    const ON_SubDFace* f = Face();
    if (nullptr != f)
      return f->SubdivisionPoint();
  }
  break;
  }
  return ON_3dPoint::NanPoint;
}



const ON_BoundingBox ON_SubDComponentPtr::ControlNetBoundingBox() const
{
  switch (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr)
  {
  case ON_SUBD_COMPONENT_TYPE_VERTEX:
  {
    const ON_SubDVertex* v = Vertex();
    if (nullptr != v)
      return v->ControlNetBoundingBox();
  }
  break;
  case ON_SUBD_COMPONENT_TYPE_EDGE:
  {
    const ON_SubDEdge* e = Edge();
    if (nullptr != e)
      return e->ControlNetBoundingBox();
  }
  break;
  case ON_SUBD_COMPONENT_TYPE_FACE:
  {
    const ON_SubDFace* f = Face();
    if (nullptr != f)
      return f->ControlNetBoundingBox();
  }
  break;
  }
  return ON_BoundingBox::NanBoundingBox;
}



ON__UINT16 ON_SubDComponentPtr::Hash16FromTypeAndId() const
{
  const ON_SubDComponentBase* c = ComponentBase();
  return (0 != c)
    ? ON_CRC16((ON__UINT16)(ON_SUBD_COMPONENT_TYPE_MASK & m_ptr), sizeof(c->m_id), &(c->m_id))
    : ((ON__UINT16)0U)
    ;
}

ON__UINT32 ON_SubDComponentPtr::Hash32FromPointer() const
{
  const ON__UINT_PTR ptr = (ON__UINT_PTR)ComponentBase();
  return ON_CRC32((ON__UINT32)(ON_SUBD_COMPONENT_TYPE_MASK & m_ptr), sizeof(ptr), &ptr);
}


ON_SubDComponentPtr::Type ON_SubDComponentPtr::ComponentType() const
{
  switch (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr)
  {
  case ON_SUBD_COMPONENT_TYPE_VERTEX:
    return ON_SubDComponentPtr::Type::Vertex;
  case ON_SUBD_COMPONENT_TYPE_EDGE:
    return ON_SubDComponentPtr::Type::Edge;
  case ON_SUBD_COMPONENT_TYPE_FACE:
    return ON_SubDComponentPtr::Type::Face;
  }
  return ON_SubDComponentPtr::Type::Unset;
}


const ON_ComponentStatus ON_SubDComponentPtr::Status() const
{
  switch (ComponentType())
  {
  case ON_SubDComponentPtr::Type::Vertex:
    {
      const ON_SubDVertex* vertex = Vertex();
      if ( nullptr != vertex )
        return vertex->m_status;
    }
    break;
  case ON_SubDComponentPtr::Type::Edge:
    {
      const ON_SubDEdge* edge = Edge();
      if ( nullptr != edge )
        return edge->m_status;
    }
    break;
  case ON_SubDComponentPtr::Type::Face:
    {
      const ON_SubDFace* face = Face();
      if ( nullptr != face )
        return face->m_status;
    }
    break;
  case ON_SubDComponentPtr::Type::Unset:
    break;
  }
  return ON_ComponentStatus::NoneSet;
}

unsigned int ON_SubDComponentPtr::SetStatus(
  ON_ComponentStatus status
  )
{
  switch (ComponentType())
  {
  case ON_SubDComponentPtr::Type::Vertex:
    {
      const ON_SubDVertex* vertex = Vertex();
      if (nullptr != vertex)
        return vertex->m_status.SetStatus(status);
    }
    break;
  case ON_SubDComponentPtr::Type::Edge:
    {
      const ON_SubDEdge* edge = Edge();
      if (nullptr != edge)
        return edge->m_status.SetStatus(status);
    }
    break;
  case ON_SubDComponentPtr::Type::Face:
    {
      const ON_SubDFace* face = Face();
      if (nullptr != face)
        return face->m_status.SetStatus(status);
    }
    break;
  case ON_SubDComponentPtr::Type::Unset:
    break;
  }
  return ON_SUBD_RETURN_ERROR(0);
}


unsigned int ON_SubDComponentPtr::SetStates(
  ON_ComponentStatus states_to_set
  )
{
  switch (ComponentType())
  {
  case ON_SubDComponentPtr::Type::Vertex:
    {
      const ON_SubDVertex* vertex = Vertex();
      if (nullptr != vertex)
        return vertex->m_status.SetStates(states_to_set);
    }
    break;
  case ON_SubDComponentPtr::Type::Edge:
    {
      const ON_SubDEdge* edge = Edge();
      if (nullptr != edge)
        return edge->m_status.SetStates(states_to_set);
    }
    break;
  case ON_SubDComponentPtr::Type::Face:
    {
      const ON_SubDFace* face = Face();
      if (nullptr != face)
        return face->m_status.SetStates(states_to_set);
    }
    break;
  case ON_SubDComponentPtr::Type::Unset:
    break;
  }
  return ON_SUBD_RETURN_ERROR(0);
}


unsigned int ON_SubDComponentPtr::ClearStates(
  ON_ComponentStatus states_to_clear
  )
{
  switch (ComponentType())
  {
  case ON_SubDComponentPtr::Type::Vertex:
    {
      const ON_SubDVertex* vertex = Vertex();
      if (nullptr != vertex)
        return vertex->m_status.ClearStates(states_to_clear);
    }
    break;
  case ON_SubDComponentPtr::Type::Edge:
    {
      const ON_SubDEdge* edge = Edge();
      if (nullptr != edge)
        return edge->m_status.ClearStates(states_to_clear);
    }
    break;
  case ON_SubDComponentPtr::Type::Face:
    {
      const ON_SubDFace* face = Face();
      if (nullptr != face)
        return face->m_status.ClearStates(states_to_clear);
    }
    break;
  case ON_SubDComponentPtr::Type::Unset:
    break;
  }
  return ON_SUBD_RETURN_ERROR(0);
}

ON_SubDComponentTest::ON_SubDComponentTest(ON__UINT_PTR ptr)
: m_ptr(ptr)
{}

ON_SubDComponentTest::~ON_SubDComponentTest()
{}

bool ON_SubDComponentTest::Passes(const ON_SubDComponentPtr cptr) const
{
  // Default implementation of a virtual function that is typically overridden
  return cptr.IsNotNull() && 0 != m_ptr;
}

bool ON_SubDComponentTest::Passes(const class ON_SubDVertex* v) const
{
  return Passes((nullptr != v) ? v->ComponentPtr() : ON_SubDComponentPtr::Null);
}

bool ON_SubDComponentTest::Passes(const class ON_SubDEdge* e) const
{
  return Passes((nullptr != e) ? e->ComponentPtr() : ON_SubDComponentPtr::Null);
}

bool ON_SubDComponentTest::Passes(const ON_SubDFace* f) const
{
  return Passes((nullptr != f) ? f->ComponentPtr() : ON_SubDComponentPtr::Null);
}

ON_SubDComponentId::ON_SubDComponentId(ON_SubDComponentPtr::Type component_type, unsigned int component_id)
  : m_id(component_id)
  , m_type_and_dir((unsigned char)component_type)
{}

ON_SubDComponentId::ON_SubDComponentId(ON_SubDComponentPtr::Type component_type, unsigned int component_id, ON__UINT_PTR dir)
  : m_id(component_id)
  , m_type_and_dir(((unsigned char)component_type) | ((unsigned char)(dir%2)))
{}

ON_SubDComponentId::ON_SubDComponentId(ON_SubDComponentPtr cptr)
{
  const ON_SubDComponentBase* b = cptr.ComponentBase();
  if (nullptr != b)
  {
    m_id = b->m_id;
    Internal_SetType(cptr.ComponentType());
    Internal_SetDir(0 == cptr.ComponentDirection() ? 0u : 1u);
  }
}

ON_SubDComponentId::ON_SubDComponentId(const class ON_SubDVertex* v)
{
  if (nullptr != v)
  {
    m_id = v->m_id;
    Internal_SetType(ON_SubDComponentPtr::Type::Vertex);
  }
}

ON_SubDComponentId::ON_SubDComponentId(const class ON_SubDVertexPtr vptr)
{
  const ON_SubDVertex* v = vptr.Vertex();
  if (nullptr != v)
  {
    m_id = v->m_id;
    Internal_SetType(ON_SubDComponentPtr::Type::Vertex);
    Internal_SetDir(0 == vptr.VertexDirection() ? 0u : 1u);
  }
}

ON_SubDComponentId::ON_SubDComponentId(const class ON_SubDEdge* e)
{
  if (nullptr != e)
  {
    m_id = e->m_id;
    Internal_SetType(ON_SubDComponentPtr::Type::Edge);
  }
}

ON_SubDComponentId::ON_SubDComponentId(ON_SubDEdgePtr eptr)
{
  const ON_SubDEdge* e = eptr.Edge();
  if (nullptr != e)
  {
    m_id = e->m_id;
    Internal_SetType(ON_SubDComponentPtr::Type::Edge);
    Internal_SetDir(0 == eptr.EdgeDirection() ? 0u : 1u);
  }
}

ON_SubDComponentId::ON_SubDComponentId(const class ON_SubDFace* f)
{
  if (nullptr != f)
  {
    m_id = f->m_id;
    Internal_SetType(ON_SubDComponentPtr::Type::Face);
  }
}

ON_SubDComponentId::ON_SubDComponentId(ON_SubDFacePtr fptr)
{
  const ON_SubDFace* f = fptr.Face();
  if (nullptr != f)
  {
    m_id = f->m_id;
    Internal_SetType(ON_SubDComponentPtr::Type::Face);
    Internal_SetDir(0 == fptr.FaceDirection() ? 0u : 1u);
  }
}

ON_SubDComponentId::ON_SubDComponentId(const class ON_SubDFace* f, unsigned face_corner_index)
{
  if (nullptr != f)
  {
    m_id = f->m_id;
    Internal_SetType(ON_SubDComponentPtr::Type::Face);
    if (face_corner_index < (unsigned)f->m_edge_count && (unsigned)f->m_edge_count < 4096u)
    {
      Internal_SetValueA(face_corner_index);
      Internal_SetValueB(f->m_edge_count);
    }
  }
}

ON_SubDComponentId::ON_SubDComponentId(ON_SubDFacePtr fptr, unsigned face_corner_index)
{
  const ON_SubDFace* f = fptr.Face();
  if (nullptr != f)
  {
    m_id = f->m_id;
    Internal_SetType(ON_SubDComponentPtr::Type::Face);
    Internal_SetDir(0 == fptr.FaceDirection() ? 0u : 1u);
    if (face_corner_index < (unsigned)f->m_edge_count && (unsigned)f->m_edge_count < 4096u)
    {
      Internal_SetValueA(face_corner_index);
      Internal_SetValueB(f->m_edge_count);
    }
  }
}

ON_SubDComponentId::ON_SubDComponentId(unsigned face_id, ON__UINT_PTR face_dir, ON_SubDFaceCornerDex face_cdex)
{
  if (face_id > 0)
  {
    m_id = face_id;
    Internal_SetType(ON_SubDComponentPtr::Type::Face);
    Internal_SetDir(0 == face_dir ? 0u : 1u);
    if (face_cdex.IsSet() && face_cdex.EdgeCount() < 4096u)
    {
      Internal_SetValueA(face_cdex.CornerIndex());
      Internal_SetValueB(face_cdex.EdgeCount());
    }
  }
}


int ON_SubDComponentId::CompareTypeAndId(const ON_SubDComponentId& lhs, const ON_SubDComponentId& rhs)
{
  const unsigned char lhs_type = (lhs.m_type_and_dir & ON_SubDComponentId::bits_type_mask);
  const unsigned char rhs_type = (rhs.m_type_and_dir & ON_SubDComponentId::bits_type_mask);
  if (lhs_type < rhs_type)
    return -1;
  if (lhs_type > rhs_type)
    return 1;
  if (lhs.m_id < rhs.m_id)
    return -1;
  if (lhs.m_id > rhs.m_id)
    return 1;
  return 0;
}

int ON_SubDComponentId::CompareTypeAndIdAndDirection(const ON_SubDComponentId& lhs, const ON_SubDComponentId& rhs)
{
  const int rc = CompareTypeAndId(lhs, rhs);
  if (0 != rc)
    return rc;

  // compare dir
  const unsigned char lhs_dir = (lhs.m_type_and_dir & ON_SubDComponentId::bits_dir_mask);
  const unsigned char rhs_dir = (rhs.m_type_and_dir & ON_SubDComponentId::bits_dir_mask);
  if (lhs_dir < rhs_dir)
    return -1;
  if (lhs_dir > rhs_dir)
    return 1;
  return 0;
}

int ON_SubDComponentId::CompareTypeAndIdFromPointer(const ON_SubDComponentId* lhs, const ON_SubDComponentId* rhs)
{
  if (lhs == rhs)
    return 0;

  // nullptr sorts to end of list
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;

  // compare type
  const unsigned char lhs_type = (lhs->m_type_and_dir & ON_SubDComponentId::bits_type_mask);
  const unsigned char rhs_type = (rhs->m_type_and_dir & ON_SubDComponentId::bits_type_mask);
  if (lhs_type < rhs_type)
    return -1;
  if (lhs_type > rhs_type)
    return 1;

  // compare id
  if (lhs->m_id < rhs->m_id)
    return -1;
  if (lhs->m_id > rhs->m_id)
    return 1;

  return 0;
}

unsigned int ON_SubDComponentId::ComponentId() const
{
  return m_id;
}

void ON_SubDComponentId::Internal_SetType(ON_SubDComponentPtr::Type type)
{
  m_type_and_dir &= ~((unsigned char)ON_SubDComponentId::bits_type_mask);
  m_type_and_dir |= (((unsigned char)type) & ON_SubDComponentId::bits_type_mask);
}

void ON_SubDComponentId::Internal_SetDir(unsigned dir)
{
  // invalid dir is treated as 0
  if (1 == dir)
    m_type_and_dir |= ((unsigned char)ON_SubDComponentId::bits_dir_mask);
  else
    m_type_and_dir &= ~((unsigned char)ON_SubDComponentId::bits_dir_mask);
}

void ON_SubDComponentId::Internal_SetValueA(unsigned a)
{
  if (a < 0x0FFFu)
  {
    m_valueAB[0] = (unsigned char)(a & 0x00FFu);
    const unsigned char ahigh = (unsigned char)((a & 0x0F00u) >> 8);
    m_valueAB[2] = (m_valueAB[2] & 0xF0u) | ahigh;
  }
}

void ON_SubDComponentId::Internal_SetValueB(unsigned b)
{
  if (b < 0x0FFFu)
  {
    m_valueAB[1] = (unsigned char)(b & 0x00FFu);
    const unsigned char bhigh = (unsigned char)((b & 0x0F00u) >> 4);
    m_valueAB[2] = (m_valueAB[2] & 0x0Fu) | bhigh;
  }
}

unsigned ON_SubDComponentId::Internal_ValueA() const
{
  const unsigned alow = m_valueAB[0];
  const unsigned ahigh = ((unsigned)(m_valueAB[2] & 0x0Fu)) << 8;
  return alow | ahigh;
}

unsigned ON_SubDComponentId::Internal_ValueB() const
{
  const unsigned blow = m_valueAB[0];
  const unsigned bhigh = ((unsigned)(m_valueAB[2] & 0xF0u)) << 4;
  return blow | bhigh;
}

unsigned ON_SubDComponentId::ComponentDirection() const
{
  return (m_type_and_dir & ON_SubDComponentId::bits_dir_mask);
}

const ON_wString ON_SubDComponentId::ToString(bool bUnsetIsEmptyString, bool bDirectionPrefix) const
{
  ON_wString str;
  const unsigned id = this->ComponentId();
  if (id > 0)
  {
    const char prefix = bDirectionPrefix ? (1 == this->ComponentDirection() ? '-' : '+') : 0;
    switch (this->ComponentType())
    {
    case ON_SubDComponentPtr::Type::Vertex:
      str = (0 == prefix) ? ON_wString::FormatToString(L"v%u", id) : ON_wString::FormatToString(L"%cv%u", prefix, id);
      break;

    case ON_SubDComponentPtr::Type::Edge:
      str = (0 == prefix) ? ON_wString::FormatToString(L"e%u", id) : ON_wString::FormatToString(L"%ce%u", prefix, id);
      break;

    case ON_SubDComponentPtr::Type::Face:
    {
      const ON_SubDFaceCornerDex cdex = this->FaceCornerDex();
      if (cdex.IsSet())
        str = (0 == prefix) ? ON_wString::FormatToString(L"f%u.%u", id, cdex.CornerIndex()) : ON_wString::FormatToString(L"%cf%u.%u", prefix, id, cdex.CornerIndex());
      else
        str = (0 == prefix) ? ON_wString::FormatToString(L"f%u", id) : ON_wString::FormatToString(L"%cf%u", prefix, id);
    }
    break;

    case ON_SubDComponentPtr::Type::Unset:
      break;
    }
  }
  return (str.IsNotEmpty() || bUnsetIsEmptyString) ? str : ON_wString("unset");
}

ON_SubDComponentPtr::Type ON_SubDComponentId::ComponentType() const
{
  return ON_SubDComponentPtr::ComponentPtrTypeFromUnsigned(m_type_and_dir & ON_SubDComponentId::bits_type_mask);
}

bool ON_SubDComponentId::IsSet() const
{
  return 0 != m_id && ON_SubDComponentPtr::Type::Unset != ComponentType();
}

bool ON_SubDComponentId::IsNotSet() const
{
  return 0 == m_id || ON_SubDComponentPtr::Type::Unset == ComponentType();
}

bool ON_SubDComponentId::IsVertexId() const
{
  return m_id > 0 && ON_SubDComponentPtr::Type::Vertex == this->ComponentType();
}

bool ON_SubDComponentId::IsEdgeId() const
{
  return m_id > 0 && ON_SubDComponentPtr::Type::Edge == this->ComponentType();
}

bool ON_SubDComponentId::IsFaceId() const
{
  return m_id > 0 && ON_SubDComponentPtr::Type::Face == this->ComponentType();
}

const ON_SubDComponentId ON_SubDComponentId::Reversed() const
{
  ON_SubDComponentId c = *this;
  c.Internal_SetDir(1u - this->ComponentDirection());
  return c;
}

const ON_SubDComponentPtr ON_SubDComponentId::ComponentPtr(const class ON_SubD* subd) const
{
  return nullptr != subd ? this->ComponentPtr(*subd) : ON_SubDComponentPtr::Null;
}

const ON_SubDComponentPtr ON_SubDComponentId::ComponentPtr(const class ON_SubD& subd) const
{
  if (0 != m_id)
  {
    ON_SubDComponentPtr cptr;
    switch (this->ComponentType())
    {
    case ON_SubDComponentPtr::Type::Vertex:
      cptr = ON_SubDComponentPtr::Create(subd.VertexFromId(m_id));
      break;
    case ON_SubDComponentPtr::Type::Edge:
      cptr = ON_SubDComponentPtr::Create(subd.EdgeFromId(m_id));
      break;
    case ON_SubDComponentPtr::Type::Face:
      cptr = ON_SubDComponentPtr::Create(subd.FaceFromId(m_id));
      break;
    default:
      cptr = ON_SubDComponentPtr::Null;
      break;
    }
    if (cptr.IsNotNull() && 0 != (m_type_and_dir & ON_SubDComponentId::bits_dir_mask))
      cptr.SetComponentDirection(1);
    return cptr;
  }
  return ON_SubDComponentPtr::Null;
}

unsigned ON_SubDComponentId::VertexId() const
{
  return this->IsVertexId() ? this->ComponentId() : 0u;
}

const ON_SubDVertex* ON_SubDComponentId::Vertex(const class ON_SubD& subd) const
{
  return this->ComponentPtr(subd).Vertex();
}

const ON_SubDVertexPtr ON_SubDComponentId::VertexPtr(const class ON_SubD& subd) const
{
  return this->ComponentPtr(subd).VertexPtr();
}

const ON_SubDVertex* ON_SubDComponentId::Vertex(const class ON_SubD* subd) const
{
  return (nullptr != subd) ? this->ComponentPtr(*subd).Vertex() : nullptr;
}

const ON_SubDVertexPtr ON_SubDComponentId::VertexPtr(const class ON_SubD* subd) const
{
  return (nullptr != subd) ? this->ComponentPtr(*subd).VertexPtr() : ON_SubDVertexPtr::Null;
}

unsigned ON_SubDComponentId::EdgeId() const
{
  return this->IsEdgeId() ? this->ComponentId() : 0u;
}

const ON_SubDEdge* ON_SubDComponentId::Edge(const class ON_SubD& subd) const
{
  return this->ComponentPtr(subd).Edge();
}

const ON_SubDEdgePtr ON_SubDComponentId::EdgePtr(const class ON_SubD& subd) const
{
  return this->ComponentPtr(subd).EdgePtr();
}

const ON_SubDEdge* ON_SubDComponentId::Edge(const class ON_SubD* subd) const
{
  return (nullptr != subd) ? this->ComponentPtr(*subd).Edge() : nullptr;
}

const ON_SubDEdgePtr ON_SubDComponentId::EdgePtr(const class ON_SubD* subd) const
{
  return (nullptr != subd) ? this->ComponentPtr(*subd).EdgePtr() : ON_SubDEdgePtr::Null;
}

unsigned ON_SubDComponentId::FaceId() const
{
  return this->IsFaceId() ? this->ComponentId() : 0u;
}

const ON_SubDFace* ON_SubDComponentId::Face(const class ON_SubD& subd) const
{
  return this->ComponentPtr(subd).Face();
}

const ON_SubDFacePtr ON_SubDComponentId::FacePtr(const class ON_SubD& subd) const
{
  return this->ComponentPtr(subd).FacePtr();
}

const ON_SubDFace* ON_SubDComponentId::Face(const class ON_SubD* subd) const
{
  return (nullptr != subd) ? this->ComponentPtr(*subd).Face() : nullptr;
}

const ON_SubDFacePtr ON_SubDComponentId::FacePtr(const class ON_SubD* subd) const
{
  return (nullptr != subd) ? this->ComponentPtr(*subd).FacePtr() : ON_SubDFacePtr::Null;
}

const ON_SubDFaceCornerDex ON_SubDComponentId::FaceCornerDex() const
{
  if (IsFaceId())
  {
    const ON_SubDFaceCornerDex cid(this->Internal_ValueA(), this->Internal_ValueB());
    if (cid.IsSet())
      return cid;
  }
  return ON_SubDFaceCornerDex::Unset;
}

bool ON_SubDComponentIdList::Passes(const ON_SubDComponentPtr cptr) const
{
  return InList(cptr) ? m_bInListPassesResult : !m_bInListPassesResult;
}

void ON_SubDComponentIdList::AddId(ON_SubDComponentId cid)
{
  if (cid.IsSet())
  {
    m_bSorted = false;
    m_id_list.Append(cid);
  }
}

void ON_SubDComponentIdList::AddId(ON_SubDComponentPtr cptr)
{
  AddId(ON_SubDComponentId(cptr));
}

void ON_SubDComponentIdList::AddIdList(const ON_SubDComponentIdList& list)
{
  const unsigned cnt{ list.UnsignedCount() };
  m_bSorted = false;
  for (unsigned i = 0; i < cnt; ++i)
  {
    m_id_list.Append(list[i]);
  }
}

unsigned int ON_SubDComponentIdList::UnsignedCount() const
{
  return m_id_list.UnsignedCount();
}

ON_SubDComponentId ON_SubDComponentIdList::operator[](unsigned int i) const
{
  return m_id_list[i];
}

void ON_SubDComponentIdList::SetInListPassesResult(bool bInListPassesResult)
{
  m_bInListPassesResult = bInListPassesResult ? true : false;
}

bool ON_SubDComponentIdList::InListPassesResult() const
{
  return m_bInListPassesResult;
}

bool ON_SubDComponentIdList::InList(ON_SubDComponentId cid) const
{
  if (false == m_bSorted)
  {
    m_bSorted = true;
    m_id_list.QuickSortAndRemoveDuplicates(ON_SubDComponentId::CompareTypeAndIdFromPointer);
  }
  const bool bInList = m_id_list.BinarySearch(&cid, ON_SubDComponentId::CompareTypeAndIdFromPointer) >= 0;

  return bInList;
}

bool ON_SubDComponentIdList::InList(ON_SubDComponentPtr cptr) const
{
  return InList(ON_SubDComponentId(cptr));
}


bool ON_SubDComponentPtr::Mark() const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->m_status.RuntimeMark() : false;
}

bool ON_SubDComponentPtr::ClearMark() const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->m_status.ClearRuntimeMark() : false;
}

bool ON_SubDComponentPtr::SetMark() const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->m_status.SetRuntimeMark() : false;
}

bool ON_SubDComponentPtr::SetMark(
  bool bMark
) const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->m_status.SetRuntimeMark(bMark) : false;
}

ON__UINT8 ON_SubDComponentPtr::MarkBits() const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->m_status.MarkBits() : 0U;
}

ON__UINT8 ON_SubDComponentPtr::SetMarkBits(ON__UINT8 mark_bits) const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->m_status.SetMarkBits(mark_bits) : false;
}

ON__UINT8 ON_SubDComponentPtr::ClearMarkBits() const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->m_status.SetMarkBits(0) : false;
}

unsigned int ON_SubDComponentPtr::GroupId(unsigned int null_component_value) const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->m_group_id : null_component_value;
}

bool ON_SubDComponentPtr::SetGroupId(
  unsigned int group_id
)
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  if (nullptr != c)
  {
    c->m_group_id = group_id;
    return true;
  }
  return false;
}


bool ON_SubDVertexPtr::Mark() const
{
  const ON_SubDVertex* c = this->Vertex();
  return (nullptr != c) ? c->m_status.RuntimeMark() : false;
}

bool ON_SubDVertexPtr::ClearMark() const
{
  const ON_SubDVertex* c = this->Vertex();
  return (nullptr != c) ? c->m_status.ClearRuntimeMark() : false;
}

bool ON_SubDVertexPtr::SetMark() const
{
  const ON_SubDVertex* c = this->Vertex();
  return (nullptr != c) ? c->m_status.SetRuntimeMark() : false;
}

bool ON_SubDVertexPtr::SetMark(
  bool bMark
) const
{
  const ON_SubDVertex* c = this->Vertex();
  return (nullptr != c) ? c->m_status.SetRuntimeMark(bMark) : false;
}

ON__UINT8 ON_SubDVertexPtr::MarkBits() const
{
  const ON_SubDVertex* c = this->Vertex();
  return (nullptr != c) ? c->m_status.MarkBits() : 0U;
}

ON__UINT8 ON_SubDVertexPtr::SetMarkBits(ON__UINT8 mark_bits) const
{
  const ON_SubDVertex* c = this->Vertex();
  return (nullptr != c) ? c->m_status.SetMarkBits(mark_bits) : false;
}

ON__UINT8 ON_SubDVertexPtr::ClearMarkBits() const
{
  const ON_SubDVertex* c = this->Vertex();
  return (nullptr != c) ? c->m_status.SetMarkBits(0) : false;
}

bool ON_SubDEdgePtr::Mark() const
{
  const ON_SubDEdge* c = this->Edge();
  return (nullptr != c) ? c->m_status.RuntimeMark() : false;
}

bool ON_SubDEdgePtr::ClearMark() const
{
  const ON_SubDEdge* c = this->Edge();
  return (nullptr != c) ? c->m_status.ClearRuntimeMark() : false;
}

bool ON_SubDEdgePtr::SetMark() const
{
  const ON_SubDEdge* c = this->Edge();
  return (nullptr != c) ? c->m_status.SetRuntimeMark() : false;
}

bool ON_SubDEdgePtr::SetMark(
  bool bMark
) const
{
  const ON_SubDEdge* c = this->Edge();
  return (nullptr != c) ? c->m_status.SetRuntimeMark(bMark) : false;
}

ON__UINT8 ON_SubDEdgePtr::MarkBits() const
{
  const ON_SubDEdge* c = this->Edge();
  return (nullptr != c) ? c->m_status.MarkBits() : 0U;
}

ON__UINT8 ON_SubDEdgePtr::SetMarkBits(ON__UINT8 mark_bits) const
{
  const ON_SubDEdge* c = this->Edge();
  return (nullptr != c) ? c->m_status.SetMarkBits(mark_bits) : false;
}

ON__UINT8 ON_SubDEdgePtr::ClearMarkBits() const
{
  const ON_SubDEdge* c = this->Edge();
  return (nullptr != c) ? c->m_status.SetMarkBits(0) : false;
}

bool ON_SubDFacePtr::Mark() const
{
  const ON_SubDFace* c = this->Face();
  return (nullptr != c) ? c->m_status.RuntimeMark() : false;
}

bool ON_SubDFacePtr::ClearMark() const
{
  const ON_SubDFace* c = this->Face();
  return (nullptr != c) ? c->m_status.ClearRuntimeMark() : false;
}

bool ON_SubDFacePtr::SetMark() const
{
  const ON_SubDFace* c = this->Face();
  return (nullptr != c) ? c->m_status.SetRuntimeMark() : false;
}

bool ON_SubDFacePtr::SetMark(
  bool bMark
) const
{
  const ON_SubDFace* c = this->Face();
  return (nullptr != c) ? c->m_status.SetRuntimeMark(bMark) : false;
}

ON__UINT8 ON_SubDFacePtr::MarkBits() const
{
  const ON_SubDFace* c = this->Face();
  return (nullptr != c) ? c->m_status.MarkBits() : 0U;
}

ON__UINT8 ON_SubDFacePtr::SetMarkBits(ON__UINT8 mark_bits) const
{
  const ON_SubDFace* c = this->Face();
  return (nullptr != c) ? c->m_status.SetMarkBits(mark_bits) : false;
}

ON__UINT8 ON_SubDFacePtr::ClearMarkBits() const
{
  const ON_SubDFace* c = this->Face();
  return (nullptr != c) ? c->m_status.SetMarkBits(0) : false;
}

ON__UINT_PTR ON_SubDComponentPtr::ComponentDirection() const
{
  return ON_SUBD_COMPONENT_DIRECTION(m_ptr);
}

const ON_SubDComponentPtr ON_SubDComponentPtr::ClearComponentDirection() const
{
  ON_SubDComponentPtr component_ptr = *this;
  component_ptr.m_ptr &= (ON_SUBD_COMPONENT_POINTER_MASK | ON_SUBD_COMPONENT_TYPE_MASK);
  return component_ptr;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::SetComponentDirection() const
{
  ON_SubDComponentPtr component_ptr = *this;
  component_ptr.m_ptr |= ON_SUBD_COMPONENT_DIRECTION_MASK;
  return component_ptr;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::SetComponentDirection(ON__UINT_PTR dir) const
{
  ON_SubDComponentPtr component_ptr = *this;
  if (0 == dir)
    component_ptr.m_ptr &= ~((ON__UINT_PTR)ON_SUBD_COMPONENT_DIRECTION_MASK);
  else if (1 == dir)
    component_ptr.m_ptr |= ON_SUBD_COMPONENT_DIRECTION_MASK;
  else
    ON_SUBD_ERROR("Invalid dir parameter");
  return component_ptr;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::Reversed() const
{
  return (0 != (m_ptr & ON_SUBD_COMPONENT_DIRECTION_MASK)) ? ClearComponentDirection() : SetComponentDirection();
}

const ON_SubDComponentPtr ON_SubDComponentPtr::CreateNull(
  ON_SubDComponentPtr::Type component_type,
  ON__UINT_PTR component_direction
)
{
  ON_SubDComponentPtr component_ptr;
  switch (component_type)
  {
  case ON_SubDComponentPtr::Type::Unset:
    component_ptr.m_ptr = 0;
    break;
  case ON_SubDComponentPtr::Type::Vertex:
    component_ptr.m_ptr = ON_SUBD_COMPONENT_TYPE_VERTEX;
    break;
  case ON_SubDComponentPtr::Type::Edge:
    component_ptr.m_ptr = ON_SUBD_COMPONENT_TYPE_EDGE;
    break;
  case ON_SubDComponentPtr::Type::Face:
    component_ptr.m_ptr = ON_SUBD_COMPONENT_TYPE_FACE;
    break;
  default:
    component_ptr.m_ptr = 0;
    break;
  }
  if (1 == component_direction)
    component_ptr.m_ptr |= ON_SUBD_COMPONENT_DIRECTION_MASK;
  return component_ptr;
}


class ON_SubDComponentBase* ON_SubDComponentPtr::ComponentBase() const
{
  switch ((ON_SUBD_COMPONENT_TYPE_MASK & m_ptr))
  {
  case ON_SUBD_COMPONENT_TYPE_VERTEX:
  case ON_SUBD_COMPONENT_TYPE_EDGE:
  case ON_SUBD_COMPONENT_TYPE_FACE:
    // During archive id mapping, the returned value can be an archive id and not a true pointer.
    // This is in a controlled setting inside functions like ON_SubDArchiveIdMap::ConvertArchiveIdToRuntimeSymmetrySetNextPtr().
    // All public level SDK code can safely assume the returned value is a true pointer.
    // It does mean that you cannot "validate" the value returned here
    // using some constraint on what you feel is a reasonable true pointer value.
    return ((class ON_SubDComponentBase*)ON_SUBD_COMPONENT_POINTER(m_ptr));
    break;
  }
  return nullptr;
}


class ON_SubDComponentBase* ON_SubDComponentPtr::ComponentBase(ON_SubDComponentPtr::Type type_filter) const
{
  const ON_SubDComponentPtr::Type ptr_type = static_cast<ON_SubDComponentPtr::Type>((unsigned char)(ON_SUBD_COMPONENT_TYPE_MASK & m_ptr));
  switch (ptr_type)
  {
  case ON_SubDComponentPtr::Type::Vertex:
  case ON_SubDComponentPtr::Type::Edge:
  case ON_SubDComponentPtr::Type::Face:
    return (ptr_type == type_filter || ON_SubDComponentPtr::Type::Unset == type_filter) ? ((class ON_SubDComponentBase*)ON_SUBD_COMPONENT_POINTER(m_ptr)) : nullptr;
  case ON_SubDComponentPtr::Type::Unset:
    break;
  }
  return nullptr;
}

class ON_SubDVertex* ON_SubDComponentPtr::Vertex() const
{
  if (ON_SUBD_COMPONENT_TYPE_VERTEX == (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr))
    return ON_SUBD_VERTEX_POINTER(m_ptr);
  return nullptr;
}

class ON_SubDEdge* ON_SubDComponentPtr::Edge() const
{
  if (ON_SUBD_COMPONENT_TYPE_EDGE == (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr))
    return ON_SUBD_EDGE_POINTER(m_ptr);
  return nullptr;
}

class ON_SubDFace* ON_SubDComponentPtr::Face() const
{
  if (ON_SUBD_COMPONENT_TYPE_FACE == (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr))
    return ON_SUBD_FACE_POINTER(m_ptr);
  return nullptr;
}

const ON_SubDVertexPtr ON_SubDComponentPtr::VertexPtr() const
{
  ON__UINT_PTR element_type = ON_SUBD_COMPONENT_TYPE(m_ptr);
  if ( ON_SUBD_COMPONENT_TYPE_VERTEX == element_type)
    return ON_SubDVertexPtr::Create(Vertex(), ComponentDirection());
  return ON_SubDVertexPtr::Null;
}

const ON_SubDEdgePtr ON_SubDComponentPtr::EdgePtr() const
{
  ON__UINT_PTR element_type = ON_SUBD_COMPONENT_TYPE(m_ptr);
  if ( ON_SUBD_COMPONENT_TYPE_EDGE == element_type)
    return ON_SubDEdgePtr::Create(Edge(), ComponentDirection());
  return ON_SubDEdgePtr::Null;
}

const ON_SubDFacePtr ON_SubDComponentPtr::FacePtr() const
{
  ON__UINT_PTR element_type = ON_SUBD_COMPONENT_TYPE(m_ptr);
  if ( ON_SUBD_COMPONENT_TYPE_FACE == element_type)
    return ON_SubDFacePtr::Create(Face(), ComponentDirection());
  return ON_SubDFacePtr::Null;
}

const bool ON_SubDComponentPtr::IsVertex() const
{
  return (ON_SUBD_COMPONENT_TYPE_VERTEX == (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr));
}

const bool ON_SubDComponentPtr::IsEdge() const
{
  return (ON_SUBD_COMPONENT_TYPE_EDGE == (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr));
}

const bool ON_SubDComponentPtr::IsFace() const
{
  return (ON_SUBD_COMPONENT_TYPE_FACE == (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr));
}

const ON_SubDComponentPtr ON_SubDComponentPtr::Create(
  const class ON_SubDVertex* vertex
  )
{
  if (nullptr != vertex)
  {
    ON_SubDComponentPtr vptr = { (ON__UINT_PTR)vertex | ON_SUBD_COMPONENT_TYPE_VERTEX };
    return vptr;
  }
  return ON_SubDComponentPtr::Null;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::Create(
  const class ON_SubDEdge* edge
  )
{
  if (nullptr != edge)
  {
    ON_SubDComponentPtr eptr = { (ON__UINT_PTR)edge | ON_SUBD_COMPONENT_TYPE_EDGE };
    return eptr;
  }
  return ON_SubDComponentPtr::Null;
}


const ON_SubDComponentPtr ON_SubDComponentPtr::Create(
  const class ON_SubDFace* face
  )
{
  if (nullptr != face)
  {
    ON_SubDComponentPtr fptr = { (ON__UINT_PTR)face | ON_SUBD_COMPONENT_TYPE_FACE };
    return fptr;
  }
  return ON_SubDComponentPtr::Null;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::Create(
  const class ON_SubDVertex* vertex,
  ON__UINT_PTR vertex_direction
  )
{
  if (nullptr != vertex)
  {
    ON_SubDComponentPtr vptr = { (ON__UINT_PTR)vertex | ON_SUBD_COMPONENT_TYPE_VERTEX | (vertex_direction & ON_SUBD_COMPONENT_DIRECTION_MASK) };
    return vptr;
  }
  return ON_SubDComponentPtr::Null;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::Create(
  const class ON_SubDEdge* edge,
  ON__UINT_PTR edge_direction
  )
{
  if (nullptr != edge)
  {    
    ON_SubDComponentPtr eptr = { (ON__UINT_PTR)edge | (ON_SUBD_COMPONENT_TYPE_EDGE | (edge_direction & ON_SUBD_COMPONENT_DIRECTION_MASK)) };
    return eptr;
  }
  return ON_SubDComponentPtr::Null;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::Create(
  const class ON_SubDFace* face,
  ON__UINT_PTR face_direction
  )
{
  if (nullptr != face)
  {
    ON_SubDComponentPtr fptr = { (ON__UINT_PTR)face | (ON_SUBD_COMPONENT_TYPE_FACE | (face_direction & ON_SUBD_COMPONENT_DIRECTION_MASK)) };
    return fptr;
  }
  return ON_SubDComponentPtr::Null;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::Create(
  ON_SubDVertexPtr vertexptr
  )
{
  return Create(vertexptr.Vertex(), vertexptr.VertexDirection());
}

const ON_SubDComponentPtr ON_SubDComponentPtr::Create(
  ON_SubDEdgePtr edgeptr
  )
{
  return Create(edgeptr.Edge(), edgeptr.EdgeDirection());
}

const ON_SubDComponentPtr ON_SubDComponentPtr::Create(
  ON_SubDFacePtr faceptr
  )
{
  return Create(faceptr.Face(), faceptr.FaceDirection());
}

int ON_SubDComponentPtr::CompareComponentPtrType(
  ON_SubDComponentPtr::Type a,
  ON_SubDComponentPtr::Type b
  )
{
  if ( a == b )
    return 0;
  switch (a)
  {
  case ON_SubDComponentPtr::Type::Vertex:
    return -1;
    break;
  case ON_SubDComponentPtr::Type::Edge:
    return (ON_SubDComponentPtr::Type::Vertex == b) ? 1 : -1;
    break;
  case ON_SubDComponentPtr::Type::Face:
    return (ON_SubDComponentPtr::Type::Vertex == b || ON_SubDComponentPtr::Type::Edge == b) ? 1 : -1;
    break;
  default:
    break;
  }
  return (((unsigned char)a) < ((unsigned char)b)) ? -1 : 1;
}

int ON_SubDComponentPtr::CompareType(
  const ON_SubDComponentPtr* a,
  const ON_SubDComponentPtr* b
  )
{
  if ( a == b )
    return 0;
    // sort nullptrs to ends of arrays
  if ( nullptr == a )
    return 1; // nonzero b < nullptr a
  if ( nullptr == b )
    return -1; // nonzero a < nullptr b
  return ON_SubDComponentPtr::CompareComponentPtrType(a->ComponentType(), b->ComponentType());
}


int ON_SubDComponentPtr::CompareComponent(
  const ON_SubDComponentPtr* a,
  const ON_SubDComponentPtr* b
)
{
  const int rc = ON_SubDComponentPtr::CompareType(a, b);
  if (0 == rc && a != b)
  {
    // 0 == ON_SubDComponentPtr::CompareType(a, b) and a != b insures both pointers are not nullptr.
    const ON__UINT_PTR x = (a->m_ptr & ON_SUBD_COMPONENT_POINTER_MASK);
    const ON__UINT_PTR y = (b->m_ptr & ON_SUBD_COMPONENT_POINTER_MASK);
    if (x < y)
      return -1;
    if (x > y)
      return 1;
  }
  return rc;
}


int ON_SubDComponentPtr::CompareComponentId(
  const ON_SubDComponentPtr* a,
  const ON_SubDComponentPtr* b
)
{
  const int rc = ON_SubDComponentPtr::CompareType(a, b);
  if (0 == rc && a != b)
  {
    // 0 == ON_SubDComponentPtr::CompareType(a, b) and a != b insures both pointers are not nullptr.
    const unsigned x = a->ComponentId();
    const unsigned y = b->ComponentId();
    if (x < y)
      return -1;
    if (x > y)
      return 1;
  }
  return rc;
}

int ON_SubDComponentPtr::CompareComponentAndDirection(
  const ON_SubDComponentPtr* a,
  const ON_SubDComponentPtr* b
)
{
  const int rc = ON_SubDComponentPtr::CompareComponent(a, b);
  if (0 == rc && a != b)
  {
    // 0 == ON_SubDComponentPtr::CompareComponent(a, b) and a != b insures both pointers are not nullptr.
    const ON__UINT_PTR x = (a->m_ptr & ON_SUBD_COMPONENT_DIRECTION_MASK);
    const ON__UINT_PTR y = (b->m_ptr & ON_SUBD_COMPONENT_DIRECTION_MASK);
    if (x < y)
      return -1;
    if (x > y)
      return 1;
  }
  return rc;
}

const ON_SubDComponentAndNumber ON_SubDComponentAndNumber::Create(
  ON_SubDComponentPtr cptr,
  double x
)
{
  ON_SubDComponentAndNumber cx;
  cx.m_cptr = cptr;
  cx.m_x = x;
  return cx;
}

const ON_SubDComponentAndNumber ON_SubDComponentAndNumber::Create(
  const ON_SubDVertex* v,
  double x
)
{
  return ON_SubDComponentAndNumber::Create(ON_SubDComponentPtr::Create(v), x);
}

const ON_SubDComponentAndNumber ON_SubDComponentAndNumber::Create(
  const ON_SubDEdge* e,
  double x
)
{
  return ON_SubDComponentAndNumber::Create(ON_SubDComponentPtr::Create(e), x);
}

const ON_SubDComponentAndNumber ON_SubDComponentAndNumber::Create(
  const ON_SubDFace* f,
  double x
)
{
  return ON_SubDComponentAndNumber::Create(ON_SubDComponentPtr::Create(f), x);
}

const ON_SubDComponentAndNumber ON_SubDComponentAndNumber::Create(
  const ON_SubDVertexPtr vptr,
  double x
)
{
  return ON_SubDComponentAndNumber::Create(ON_SubDComponentPtr::Create(vptr), x);
}

const ON_SubDComponentAndNumber ON_SubDComponentAndNumber::Create(
  const ON_SubDEdgePtr eptr,
  double x
)
{
  return ON_SubDComponentAndNumber::Create(ON_SubDComponentPtr::Create(eptr), x);
}

const ON_SubDComponentAndNumber ON_SubDComponentAndNumber::Create(
  const ON_SubDFacePtr fptr,
  double x
)
{
  return ON_SubDComponentAndNumber::Create(ON_SubDComponentPtr::Create(fptr), x);
}


const ON_SubDComponentPtr ON_SubDComponentAndNumber::Component() const
{
  return m_cptr;
}

void ON_SubDComponentAndNumber::SetComponent(ON_SubDComponentPtr cptr)
{
  m_cptr = cptr;
}

double ON_SubDComponentAndNumber::Number() const
{
  return m_x;
}

void ON_SubDComponentAndNumber::SetNumber(double x)
{
  m_x = x;
}

int ON_SubDComponentAndNumber::CompareComponent(
  const ON_SubDComponentAndNumber* a,
  const ON_SubDComponentAndNumber* b
)
{
  if (a == b)
    return 0;
  if (nullptr == a)
    return -1;
  if (nullptr == b)
    return 1;
  return ON_SubDComponentPtr::CompareComponent(&a->m_cptr, &b->m_cptr);
}

// 
int ON_SubDComponentAndNumber::CompareComponentAndDirection(
  const ON_SubDComponentAndNumber* a,
  const ON_SubDComponentAndNumber* b
)
{
  if (a == b)
    return 0;
  if (nullptr == a)
    return -1;
  if (nullptr == b)
    return 1;
  return ON_SubDComponentPtr::CompareComponentAndDirection(&a->m_cptr, &b->m_cptr);
}

int ON_SubDComponentAndNumber::CompareNumber(
  const ON_SubDComponentAndNumber* a,
  const ON_SubDComponentAndNumber* b
)
{
  if (a == b)
    return 0;
  if (nullptr == a)
    return -1;
  if (nullptr == b)
    return 1;
  return ON_CompareDouble(a->m_x, b->m_x);
}

int ON_SubDComponentAndNumber::CompareComponentAndNumber(
  const ON_SubDComponentAndNumber* a,
  const ON_SubDComponentAndNumber* b
)
{
  const int rc = ON_SubDComponentAndNumber::CompareComponent(a, b);
  return (0 != rc) ? rc : ON_SubDComponentAndNumber::CompareNumber(a, b);
}

int ON_SubDComponentAndNumber::CompareComponentAndDirectionAndNumber(
  const ON_SubDComponentAndNumber* a,
  const ON_SubDComponentAndNumber* b
)
{
  const int rc = ON_SubDComponentAndNumber::CompareComponentAndDirection(a, b);
  return (0 != rc) ? rc : ON_SubDComponentAndNumber::CompareNumber(a, b);
}



const ON_SubDComponentAndPoint ON_SubDComponentAndPoint::Create(
  ON_SubDComponentPtr cptr,
  ON_3dPoint P
)
{
  ON_SubDComponentAndPoint cx;
  cx.m_cptr = cptr;
  cx.m_P = P;
  return cx;
}

const ON_SubDComponentAndPoint ON_SubDComponentAndPoint::Create(
  const ON_SubDVertex* v,
  ON_3dPoint P
)
{
  return ON_SubDComponentAndPoint::Create(ON_SubDComponentPtr::Create(v), P);
}

const ON_SubDComponentAndPoint ON_SubDComponentAndPoint::Create(
  const ON_SubDEdge* e,
  ON_3dPoint P
)
{
  return ON_SubDComponentAndPoint::Create(ON_SubDComponentPtr::Create(e), P);
}

const ON_SubDComponentAndPoint ON_SubDComponentAndPoint::Create(
  const ON_SubDFace* f,
  ON_3dPoint P
)
{
  return ON_SubDComponentAndPoint::Create(ON_SubDComponentPtr::Create(f), P);
}

const ON_SubDComponentAndPoint ON_SubDComponentAndPoint::Create(
  const ON_SubDVertexPtr vptr,
  ON_3dPoint P
)
{
  return ON_SubDComponentAndPoint::Create(ON_SubDComponentPtr::Create(vptr), P);
}

const ON_SubDComponentAndPoint ON_SubDComponentAndPoint::Create(
  const ON_SubDEdgePtr eptr,
  ON_3dPoint P
)
{
  return ON_SubDComponentAndPoint::Create(ON_SubDComponentPtr::Create(eptr), P);
}

const ON_SubDComponentAndPoint ON_SubDComponentAndPoint::Create(
  const ON_SubDFacePtr fptr,
  ON_3dPoint P
)
{
  return ON_SubDComponentAndPoint::Create(ON_SubDComponentPtr::Create(fptr), P);
}


const ON_SubDComponentPtr ON_SubDComponentAndPoint::Component() const
{
  return m_cptr;
}

void ON_SubDComponentAndPoint::SetComponent(ON_SubDComponentPtr cptr)
{
  m_cptr = cptr;
}

const ON_3dPoint ON_SubDComponentAndPoint::Point() const
{
  return m_P;
}

void ON_SubDComponentAndPoint::SetPoint(ON_3dPoint P)
{
  m_P = P;
}

int ON_SubDComponentAndPoint::CompareComponent(
  const ON_SubDComponentAndPoint* lhs,
  const ON_SubDComponentAndPoint* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return -1;
  if (nullptr == rhs)
    return 1;
  return ON_SubDComponentPtr::CompareComponent(&lhs->m_cptr, &rhs->m_cptr);
}

// 
int ON_SubDComponentAndPoint::CompareComponentAndDirection(
  const ON_SubDComponentAndPoint* lhs,
  const ON_SubDComponentAndPoint* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return -1;
  if (nullptr == rhs)
    return 1;
  return ON_SubDComponentPtr::CompareComponentAndDirection(&lhs->m_cptr, &rhs->m_cptr);
}

int ON_SubDComponentAndPoint::ComparePoint(
  const ON_SubDComponentAndPoint* lhs,
  const ON_SubDComponentAndPoint* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return -1;
  if (nullptr == rhs)
    return 1;
  return ON_3dPoint::Compare(lhs->m_P, rhs->m_P);
}

int ON_SubDComponentAndPoint::CompareComponentAndPoint(
  const ON_SubDComponentAndPoint* lhs,
  const ON_SubDComponentAndPoint* rhs
)
{
  const int rc = ON_SubDComponentAndPoint::CompareComponent(lhs, rhs);
  return (0 != rc) ? rc : ON_SubDComponentAndPoint::ComparePoint(lhs, rhs);
}

int ON_SubDComponentAndPoint::CompareComponentAndDirectionAndPoint(
  const ON_SubDComponentAndPoint* lhs,
  const ON_SubDComponentAndPoint* rhs
)
{
  const int rc = ON_SubDComponentAndPoint::CompareComponentAndDirection(lhs, rhs);
  return (0 != rc) ? rc : ON_SubDComponentAndPoint::ComparePoint(lhs, rhs);
}


static const bool Internal_FirstIsPartOfSecond(
  const ON_SubDComponentPoint& first,
  const ON_SubDComponentPoint& second
)
{
  // returns true if first is topologically part of second (vertex on edge, vertex on face, or edge on face).
  const ON_SubDComponentPtr::Type first_type = first.m_component_ptr.ComponentType();
  const ON_SubDComponentPtr::Type second_type = second.m_component_ptr.ComponentType();
  if (first_type != second_type)
  {
    if (ON_SubDComponentPtr::Type::Vertex == first_type)
    {
      const ON_SubDVertex* v = first.m_component_ptr.Vertex();
      if (nullptr != v)
      {
        if (ON_SubDComponentPtr::Type::Edge == second_type)
        {
          const ON_SubDEdge* e = second.m_component_ptr.Edge();
          if (nullptr != e && (v == e->m_vertex[0] || v == e->m_vertex[1]))
            return true;
        }
        else if (ON_SubDComponentPtr::Type::Face == second_type)
        {
          const ON_SubDFace* f = second.m_component_ptr.Face();
          if (nullptr != f && f->VertexIndex(v) < ON_UNSET_UINT_INDEX)
            return true;
        }
      }
    }
    else if (ON_SubDComponentPtr::Type::Edge == first_type)
    {
      if (ON_SubDComponentPtr::Type::Face == second_type)
      {
        const ON_SubDEdge* e = first.m_component_ptr.Edge();
        const ON_SubDFace* f = second.m_component_ptr.Face();
        if (nullptr != e && nullptr != f && e->FaceArrayIndex(f) < ON_UNSET_UINT_INDEX)
          return true;
      }
    }
  }
  return false;
}

const ON_SubDComponentPoint ON_SubDComponentPoint::BestPickPoint(
  ON_PickType pick_type,
  double vertex_depth_bias,
  double edge_depth_bias,
  const ON_SubDComponentPoint& A,
  const ON_SubDComponentPoint& B
)
{
  // If you're working on a bug where somebody isn't able to pick the SubD component
  // they thought they clicked on, then you're in the right place.
  // Mikko has done lots of work in this area and be sure to retest RH-52172 and RH-52173 (fixed 3 May 2019).
  // Also, retest RH-59666 (fixed August 2020).
  //
  // This function will be a work in progress for many years.

  // unbiased_compare ignores SubD component types and relative topological relationships.
  // If unbiased_compare == 1, then A is "best" from this "unbiased" point of views.
  const int unbiased_compare = (ON_PickPoint::Compare(A.m_pick_point, B.m_pick_point)>=0) ? 1 : -1;
  
  const ON_SubDComponentPtr::Type A_component_type = A.m_component_ptr.ComponentType();
  const ON_SubDComponentPtr::Type B_component_type = B.m_component_ptr.ComponentType();
  if (A_component_type == B_component_type)
  {
    // A and B are the same type of component
    return (unbiased_compare >= 0) ? A : B;
  }
  if (ON_SubDComponentPtr::Type::Unset == A_component_type)
    return B;
  if (ON_SubDComponentPtr::Type::Unset == B_component_type)
    return A;

  // If we get this far, then A and B are pick events on different types of SubD components.

  // type_bias = 1 if A is a vertex and B is an edge/face or A is an edge and B is a face.
  // type_bias = -1 if B is a vertex and A is an edge/face or B is an edge and A is a face.
  const int type_bias = (ON_SubDComponentPtr::CompareComponentPtrType(A_component_type, B_component_type)) <= 0 ? 1 : -1;

  // 17 Dec 2024, Mikko, RH-85024:
  // Skip the following section if either component is a face. 
  // In that case it gives the wrong answer if you click on an opaque shaded SubD face, 
  // and at the same time hit an edge/vertex of the same face behind the shaded part.
  if (
    ON_PickType::PointPick == pick_type
    && ((type_bias >= 0) ? Internal_FirstIsPartOfSecond(A, B) : Internal_FirstIsPartOfSecond(B, A))
    && ON_SubDComponentPtr::Type::Face != A_component_type
    && ON_SubDComponentPtr::Type::Face != B_component_type
    )
  {
    // A point pick is occurring and best is a vertex on an edge/face or best is an edge on a face.
    // Bias towards the vertex/edge.
    // Users can pick the middle of an edge/face if they want the "bigger" component.
    ON_SubDComponentPoint best = (type_bias >= 0) ? A : B;
    best.m_pick_point.m_distance = ON_Min(A.m_pick_point.m_distance, B.m_pick_point.m_distance);
    best.m_pick_point.m_depth = ON_Max(A.m_pick_point.m_depth, B.m_pick_point.m_depth);
    return best;
  }

  ON_PickPoint biased_A(A.m_pick_point);
  ON_PickPoint biased_B(B.m_pick_point);

  // distance bias applied to point picks on vertices and edges
  // Events with smaller distances are "better" because they are visually are closer to the picked point.
  if (ON_PickType::PointPick == pick_type)
  {
    // 18 Aug 2020 Dale Lear:
    //   The pick distance for a point pick is normalized so 1.0 = pick frustum radius. 
    //   Reasonable values for distance_tol are 0.25 to 1.0.
    //   0.5 fixes RH-52172
    //   1.0 seems to fix bugs like RH-59666 (0.5 is too small to fix RH-59666).
    const double distance_tol = 1.0;

    if ( type_bias > 0 && biased_A.m_distance > 0.0 && biased_A.m_distance <= distance_tol)
      biased_A.m_distance = 0.0; // consider pick A to be on the vertex/edge

    if ( type_bias < 0 && biased_B.m_distance > 0.0 && biased_B.m_distance <= distance_tol )
      biased_B.m_distance = 0.0; // consider pick B to be on the vertex/edge
  }

  // Apply a depth bias when we have a relative topological relationship between the components
  // (vertex on edge, vertex on face, or edge on face).
  // Events with larger depths are "better" because they are in front of smaller depths.
  double depth_bias = 0.0;
  const bool bHaveVertex = ON_SubDComponentPtr::Type::Vertex == A_component_type || ON_SubDComponentPtr::Type::Vertex == B_component_type;
  const bool bHaveEdge = ON_SubDComponentPtr::Type::Edge == A_component_type || ON_SubDComponentPtr::Type::Edge == B_component_type;
  const bool bHaveFace = ON_SubDComponentPtr::Type::Face == A_component_type || ON_SubDComponentPtr::Type::Face == B_component_type;
  if ( bHaveVertex && vertex_depth_bias > 0.0 && vertex_depth_bias < ON_UNSET_POSITIVE_VALUE  )
  {
    // One event is a vertex, the other event is an edge or face, and a vertex bias was supplied.
    // Test to see if the vertex is on the edge or face.
    if (Internal_FirstIsPartOfSecond(A,B))
    {
      // B is an edge/face and A is a vertex on the edge/face
      depth_bias = vertex_depth_bias;
      biased_A.m_depth += depth_bias; // bias vertex closer
    }
    else if (Internal_FirstIsPartOfSecond(B, A))
    {
      // A is an edge/face and B is a vertex on the edge/face
      depth_bias = vertex_depth_bias;
      biased_B.m_depth += depth_bias; // bias vertex closer
    }
  }
  else if ( bHaveEdge && bHaveFace && edge_depth_bias > 0.0  && edge_depth_bias < ON_UNSET_POSITIVE_VALUE )
  {
    // One event is an edge, the other event is a face, and an edge bias was supplied.
    // Test to see if the edge is on the face.
    if (Internal_FirstIsPartOfSecond(A, B))
    {
      // B is a face and A is an edge on the face
      depth_bias = edge_depth_bias;
      biased_A.m_depth += depth_bias; // bias edge closer
    }
    else if (Internal_FirstIsPartOfSecond(B, A))
    {
      // A is a face and B is an edge on the face
      depth_bias = edge_depth_bias;
      biased_B.m_depth += depth_bias; // bias edge closer
    }
  }

  // biased_compare adds a bias towards vertices and edges based on SubD component types and relative topological relationships.
  // If biased_compare >= 0, then A is "best" from this biased point of views.
  const int biased_compare = (ON_PickPoint::Compare(biased_A, biased_B)>=0) ? 1 : -1;

  ON_SubDComponentPoint best = (biased_compare >= 0) ? A : B;

  const ON_SubDComponentPtr::Type best_type = best.m_component_ptr.ComponentType();
  if ( ON_SubDComponentPtr::Type::Vertex == best_type || (ON_SubDComponentPtr::Type::Edge == best_type && bHaveFace) )
  {
    // Either a vertex was better than an edge/face or an edge was better than a face.
    if (fabs(A.m_pick_point.m_depth - B.m_pick_point.m_depth) <= depth_bias)
    {
      // The two pick points were "close" in depth.
      // In these cases, strengthen "best" by using the "best" depth and distance values from A and B.
      best.m_pick_point.m_distance = ON_Min(A.m_pick_point.m_distance, B.m_pick_point.m_distance);
      best.m_pick_point.m_depth = ON_Max(A.m_pick_point.m_depth, B.m_pick_point.m_depth);
    }
  }

  return best;
}

int ON_SubDComponentPoint::CompareComponentAndDirection(
  const ON_SubDComponentPoint* a,
  const ON_SubDComponentPoint* b
  )
{
  if ( a == b)
    return 0;  
  if ( nullptr == a)
    return 1; // nullptr > non-null pointer.
  if ( nullptr == b)
    return -1; // nullptr > non-null pointer.

  // 1st: compare component type
  // unset < vertex < edge < face
  ON__UINT_PTR x = (ON_SUBD_COMPONENT_TYPE_MASK & a->m_component_ptr.m_ptr);
  ON__UINT_PTR y = (ON_SUBD_COMPONENT_TYPE_MASK & b->m_component_ptr.m_ptr);
  if ( x < y )
    return -1;
  if ( x > y )
    return 1;

  // 2nd: compare component pointer
  x = (a->m_component_ptr.m_ptr & ON_SUBD_COMPONENT_POINTER_MASK);
  y = (b->m_component_ptr.m_ptr & ON_SUBD_COMPONENT_POINTER_MASK);
  if (x < y)
    return -1;
  if (x > y)
    return 1;

  // 3rd: compare component direction flag
  x = (a->m_component_ptr.m_ptr & ON_SUBD_COMPONENT_DIRECTION_MASK);
  y = (b->m_component_ptr.m_ptr & ON_SUBD_COMPONENT_DIRECTION_MASK);
  if (x < y)
    return -1;
  if (x > y)
    return 1;

  return 0;
}


const ON_SubDComponentPtrPair ON_SubDComponentPtrPair::Create(ON_SubDComponentPtr first_ptr, ON_SubDComponentPtr second_ptr)
{
  ON_SubDComponentPtrPair p;
  p.m_pair[0] = first_ptr;
  p.m_pair[1] = second_ptr;
  return p;
}

int ON_SubDComponentPtrPair::CompareComponent(
  const ON_SubDComponentPtrPair* lhs,
  const ON_SubDComponentPtrPair* rhs
)
{
  if (lhs == rhs)
    return 0;
  // nulls sort to end.
  if (nullptr == rhs)
    return -1;
  if (nullptr == lhs)
    return 1;
  int rc = ON_SubDComponentPtr::CompareComponent(&lhs->m_pair[0], &rhs->m_pair[0]);
  if (0 == rc)
    rc = ON_SubDComponentPtr::CompareComponent(&lhs->m_pair[1], &rhs->m_pair[1]);
  return rc;
}

int ON_SubDComponentPtrPair::CompareComponentAndDirection(
  const ON_SubDComponentPtrPair* lhs,
  const ON_SubDComponentPtrPair* rhs
)
{
  if (lhs == rhs)
    return 0;
  // nulls sort to end.
  if (nullptr == rhs)
    return -1;
  if (nullptr == lhs)
    return 1;
  int rc = ON_SubDComponentPtr::CompareComponentAndDirection(&lhs->m_pair[0], &rhs->m_pair[0]);
  if (0 == rc)
    rc = ON_SubDComponentPtr::CompareComponentAndDirection(&lhs->m_pair[1], &rhs->m_pair[1]);
  return rc;
}


int ON_SubDComponentPtrPair::CompareFirstPointer(
  const ON_SubDComponentPtrPair* lhs,
  const ON_SubDComponentPtrPair* rhs
)
{
  if (lhs == rhs)
    return 0;
  // nulls sort to end.
  if (nullptr == rhs)
    return -1;
  if (nullptr == lhs)
    return 1;
  const ON__UINT_PTR lhs_ptr = (ON_SUBD_COMPONENT_POINTER_MASK & lhs->m_pair[0].m_ptr);
  const ON__UINT_PTR rhs_ptr = (ON_SUBD_COMPONENT_POINTER_MASK & rhs->m_pair[0].m_ptr);
  if (lhs_ptr < rhs_ptr)
    return -1;
  if (lhs_ptr > rhs_ptr)
    return 1;
  return 0;
}

ON_SubDComponentPtr::Type ON_SubDComponentPtrPair::ComponentType() const
{
  const ON_SubDComponentPtr::Type type = m_pair[0].ComponentType();
  return (type == m_pair[1].ComponentType()) ? type : ON_SubDComponentPtr::Type::Unset;
}

const ON_SubDComponentPtrPair ON_SubDComponentPtrPair::SwapPair() const
{
  return ON_SubDComponentPtrPair::Create(m_pair[1], m_pair[0]);
}

const ON_SubDComponentPtrPair ON_SubDComponentPtrPair::ReversedPair() const
{
  return ON_SubDComponentPtrPair::Create(m_pair[0].Reversed(), m_pair[1].Reversed());
}

const ON_SubDComponentPtr ON_SubDComponentPtrPair::First() const
{
  return m_pair[0];
}

const ON_SubDComponentPtr ON_SubDComponentPtrPair::Second() const
{
  return m_pair[1];
}

bool ON_SubDComponentPtrPair::FirstIsNull() const
{
  return (0 == (ON_SUBD_COMPONENT_POINTER_MASK & m_pair[0].m_ptr));
}

bool ON_SubDComponentPtrPair::SecondIsNull() const
{
  return (0 == (ON_SUBD_COMPONENT_POINTER_MASK & m_pair[1].m_ptr));
}

bool ON_SubDComponentPtrPair::BothAreNull() const
{
  return (0 == (ON_SUBD_COMPONENT_POINTER_MASK & m_pair[0].m_ptr)) && 0 == (ON_SUBD_COMPONENT_POINTER_MASK & m_pair[1].m_ptr);
}

bool ON_SubDComponentPtrPair::FirstIsNotNull() const
{
  return m_pair[0].IsNotNull();
}

bool ON_SubDComponentPtrPair::SecondIsNotNull() const
{
  return m_pair[1].IsNotNull();
}

bool ON_SubDComponentPtrPair::BothAreNotNull() const
{
  return m_pair[0].IsNotNull() && m_pair[1].IsNotNull();
}


/////////////////////////////////////////////////////////////////////////
//
// ON_SubD_ComponentIdTypeAndTag
//

const ON_wString ON_SubD_ComponentIdTypeAndTag::ToString() const
{
  switch (m_type)
  {
  case ON_SubDComponentPtr::Type::Unset:
    break;
  case ON_SubDComponentPtr::Type::Vertex:
    return ON_wString::FormatToString(L"Vertex id=%u tag=",m_id) + ON_SubD::VertexTagToString(VertexTag(),false);
    break;
  case ON_SubDComponentPtr::Type::Edge:
    return ON_wString::FormatToString(L"Edge id=%u tag=",m_id) + ON_SubD::EdgeTagToString(EdgeTag(), false);
    break;
  case ON_SubDComponentPtr::Type::Face:
    return ON_wString::FormatToString(L"Face id=%u tag=%u", m_id, (unsigned)FaceTag());
    break;
  default:
    break;
  }
  return ON_wString(L"Unset");
}

const ON_SubD_ComponentIdTypeAndTag ON_SubD_ComponentIdTypeAndTag::CreateFromVertex(const ON_SubDVertex* v)
{
  ON_SubD_ComponentIdTypeAndTag itt
    = (nullptr != v)
    ? ON_SubD_ComponentIdTypeAndTag::CreateFromVertexId(v->m_id, v->m_vertex_tag)
    : ON_SubD_ComponentIdTypeAndTag::Unset;
  //if (itt.m_id > 0)
  //  itt.m_cptr = ON_SubDComponentPtr::Create(v);
  return itt;
}

const ON_SubD_ComponentIdTypeAndTag ON_SubD_ComponentIdTypeAndTag::CreateFromVertexId(unsigned vertex_id, ON_SubDVertexTag vtag)
{
  ON_SubD_ComponentIdTypeAndTag itt;
  if (vertex_id > 0)
  {
    itt.m_id = vertex_id;
    itt.m_type = ON_SubDComponentPtr::Type::Vertex;
    itt.Internal_SetTag(static_cast<unsigned char>(vtag));
  }
  return itt;
}

const ON_SubD_ComponentIdTypeAndTag ON_SubD_ComponentIdTypeAndTag::CreateFromEdge(const ON_SubDEdge * e)
{
  ON_SubD_ComponentIdTypeAndTag itt
    = (nullptr != e) 
    ? ON_SubD_ComponentIdTypeAndTag::CreateFromEdgeId(e->m_id, e->m_edge_tag, e->Sharpness(false)) 
    : ON_SubD_ComponentIdTypeAndTag::Unset;
  //if (itt.m_id > 0)
  //  itt.m_cptr = ON_SubDComponentPtr::Create(e);
  return itt;
}

const ON_SubD_ComponentIdTypeAndTag ON_SubD_ComponentIdTypeAndTag::CreateFromEdge(const class ON_SubDEdgePtr eptr)
{
  ON_SubD_ComponentIdTypeAndTag itt = ON_SubD_ComponentIdTypeAndTag::CreateFromEdge(eptr.Edge());
  if (ON_SubDEdgeTag::Unset != itt.EdgeTag())
    itt.Internal_SetDir(0 == eptr.EdgeDirection() ? 0 : 1);
  return itt;
}


const ON_SubD_ComponentIdTypeAndTag ON_SubD_ComponentIdTypeAndTag::CreateFromEdgeId(unsigned edge_id, ON_SubDEdgeTag etag)
{
  ON_SubD_ComponentIdTypeAndTag itt;
  if (edge_id > 0)
  {
    itt.m_sharpness = ON_SubDEdgeSharpness::Smooth;
    itt.m_id = edge_id;
    itt.m_type = ON_SubDComponentPtr::Type::Edge;
    itt.Internal_SetTag(static_cast<unsigned char>(ON_SubDEdgeTag::SmoothX == etag ? ON_SubDEdgeTag::Smooth : etag));
  }
  return itt;
}

const ON_SubD_ComponentIdTypeAndTag ON_SubD_ComponentIdTypeAndTag::CreateFromEdgeId(unsigned edge_id, ON_SubDEdgeTag etag, ON_SubDEdgeSharpness sharpness)
{
  ON_SubD_ComponentIdTypeAndTag itt = CreateFromEdgeId(edge_id, etag);
  if (ON_SubDComponentPtr::Type::Edge == itt.m_type)
  {
    switch (itt.EdgeTag())
    {
    case ON_SubDEdgeTag::Smooth:
    case ON_SubDEdgeTag::SmoothX:
      if (sharpness.IsSharp())
        itt.m_sharpness = sharpness;
      break;
    default:
      break;
    }
  }
  return itt;
}

const ON_SubD_ComponentIdTypeAndTag ON_SubD_ComponentIdTypeAndTag::CreateFromFace(const ON_SubDFace* f, unsigned char ftag)
{
  ON_SubD_ComponentIdTypeAndTag itt
    = (nullptr != f)
    ? ON_SubD_ComponentIdTypeAndTag::CreateFromFaceId(f->m_id, ftag)
    : ON_SubD_ComponentIdTypeAndTag::Unset;
  //if (itt.m_id > 0)
  //  itt.m_cptr = ON_SubDComponentPtr::Create(f);
  return itt;
}

const ON_SubD_ComponentIdTypeAndTag ON_SubD_ComponentIdTypeAndTag::CreateFromFaceId(unsigned face_id, unsigned char ftag)
{
  ON_SubD_ComponentIdTypeAndTag itt;
  if (face_id > 0)
  {
    itt.m_id = face_id;
    itt.m_type = ON_SubDComponentPtr::Type::Vertex;
    itt.Internal_SetTag(ftag);
  }
  return itt;
}

int ON_SubD_ComponentIdTypeAndTag::CompareTypeAndId(const ON_SubD_ComponentIdTypeAndTag * lhs, const ON_SubD_ComponentIdTypeAndTag * rhs)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  if (lhs->m_type < rhs->m_type)
    return -1;
  if (lhs->m_type > rhs->m_type)
    return 1;
  if (lhs->m_id < rhs->m_id)
    return -1;
  if (lhs->m_id > rhs->m_id)
    return 1;
  return 0;
}

int ON_SubD_ComponentIdTypeAndTag::CompareTypeAndIdAndTag(const ON_SubD_ComponentIdTypeAndTag* lhs, const ON_SubD_ComponentIdTypeAndTag* rhs)
{
  int rc = ON_SubD_ComponentIdTypeAndTag::CompareTypeAndId(lhs, rhs);
  if (0 != rc)
    return rc;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  const unsigned char lhs_tag = lhs->Internal_Tag();
  const unsigned char rhs_tag = rhs->Internal_Tag();
  if (lhs_tag < rhs_tag)
    return -1;
  if (lhs_tag > rhs_tag)
    return 1;
  return 0;
}

const ON_SubD_ComponentIdTypeAndTag ON_SubD_ComponentIdTypeAndTag::FindFromTypeAndId(ON_SubDComponentPtr::Type type, unsigned id, const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags)
{
  if (0 == id || ON_SubDComponentPtr::Type::Unset == type)
    return ON_SubD_ComponentIdTypeAndTag::Unset;
  ON_SubD_ComponentIdTypeAndTag itt;
  itt.m_id = id;
  itt.m_type = type;
  const int i = sorted_tags.BinarySearch(&itt, ON_SubD_ComponentIdTypeAndTag::CompareTypeAndId);
  return (i >= 0) ? sorted_tags[i] : ON_SubD_ComponentIdTypeAndTag::Unset;
}

ON_SubDVertexTag ON_SubD_ComponentIdTypeAndTag::OriginalVertexTag(unsigned vertex_id, const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags)
{
  if (0 == vertex_id)
    return ON_SubDVertexTag::Unset;
  const ON_SubD_ComponentIdTypeAndTag itt = ON_SubD_ComponentIdTypeAndTag::FindFromTypeAndId(ON_SubDComponentPtr::Type::Vertex, vertex_id, sorted_tags);
  return itt.VertexTag();
}

ON_SubDVertexTag ON_SubD_ComponentIdTypeAndTag::OriginalVertexTag(const ON_SubDVertex* v, const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags)
{
  if (nullptr == v)
    return ON_SubD_ComponentIdTypeAndTag::OriginalVertexTag((unsigned)0, sorted_tags);
  const ON_SubD_ComponentIdTypeAndTag itt = ON_SubD_ComponentIdTypeAndTag::FindFromTypeAndId(ON_SubDComponentPtr::Type::Vertex, v->m_id, sorted_tags);
  return (ON_SubDComponentPtr::Type::Vertex == itt.m_type && v->m_id == itt.m_id) ? itt.VertexTag() : v->m_vertex_tag;
}

ON_SubDEdgeTag ON_SubD_ComponentIdTypeAndTag::OriginalEdgeTag(unsigned edge_id, const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags)
{
  if (0 == edge_id)
    return ON_SubDEdgeTag::Unset;
  const ON_SubD_ComponentIdTypeAndTag itt = ON_SubD_ComponentIdTypeAndTag::FindFromTypeAndId(ON_SubDComponentPtr::Type::Edge, edge_id, sorted_tags);
  return itt.EdgeTag();
}

ON_SubDEdgeTag ON_SubD_ComponentIdTypeAndTag::OriginalEdgeTag(const ON_SubDEdge * e, const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>&sorted_tags)
{
  if (nullptr == e)
    return ON_SubD_ComponentIdTypeAndTag::OriginalEdgeTag((unsigned)0,sorted_tags);
  const ON_SubD_ComponentIdTypeAndTag itt = ON_SubD_ComponentIdTypeAndTag::FindFromTypeAndId(ON_SubDComponentPtr::Type::Edge, e->m_id, sorted_tags);
  return (ON_SubDComponentPtr::Type::Edge == itt.m_type && e->m_id == itt.m_id) ? itt.EdgeTag() : e->m_edge_tag;
}

unsigned char ON_SubD_ComponentIdTypeAndTag::OriginalFaceTag(unsigned face_id, const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags)
{
  if (0 == face_id)
    return 0;
  const ON_SubD_ComponentIdTypeAndTag itt = ON_SubD_ComponentIdTypeAndTag::FindFromTypeAndId(ON_SubDComponentPtr::Type::Face, face_id, sorted_tags);
  return itt.FaceTag();
}


unsigned char ON_SubD_ComponentIdTypeAndTag::OriginalFaceTag(const ON_SubDFace* f, const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags)
{
  if (nullptr == f)
    return ON_SubD_ComponentIdTypeAndTag::OriginalFaceTag((unsigned)0, sorted_tags);
  const ON_SubD_ComponentIdTypeAndTag itt = ON_SubD_ComponentIdTypeAndTag::FindFromTypeAndId(ON_SubDComponentPtr::Type::Face, f->m_id, sorted_tags);
  return (ON_SubDComponentPtr::Type::Face == itt.m_type && f->m_id == itt.m_id) ? itt.FaceTag() : 0;
}

ON_SubDComponentPtr::Type ON_SubD_ComponentIdTypeAndTag::ComponentType() const
{
  return m_type;
}

unsigned char ON_SubD_ComponentIdTypeAndTag::Internal_Tag() const
{
  return (0x07 & m_tag_and_dirx);
}

void ON_SubD_ComponentIdTypeAndTag::Internal_SetTag(unsigned char tag)
{
  const unsigned char dir = 0x80 & m_tag_and_dirx;
  m_tag_and_dirx = (dir | (0x07 & tag));
}

// returns (0x80 & m_tag_and_dir) != 0 ? 1 : 0;
unsigned char ON_SubD_ComponentIdTypeAndTag::Internal_Dir() const
{
  return (0 == (0x80 & m_tag_and_dirx)) ? 0 : 1;
}

void ON_SubD_ComponentIdTypeAndTag::Internal_SetDir(unsigned char dir)
{
  if (dir <= 1)
  {

    const unsigned char tag = 0x07 & m_tag_and_dirx;
    m_tag_and_dirx = (tag | ((dir != 0) ? 0x70 : 0x00));
  }
}

unsigned ON_SubD_ComponentIdTypeAndTag::VertexId() const
{
  return (ON_SubDComponentPtr::Type::Vertex == m_type) ? m_id : 0;
}

unsigned ON_SubD_ComponentIdTypeAndTag::EdgeId() const
{
  return (ON_SubDComponentPtr::Type::Edge == m_type) ? m_id : 0;
}

const ON_SubDEdgeSharpness ON_SubD_ComponentIdTypeAndTag::EdgeSharpness(bool bUseCreaseSharpness) const
{
  switch (EdgeTag())
  {
  case ON_SubDEdgeTag::Smooth:
  case ON_SubDEdgeTag::SmoothX:
    return m_sharpness;
    break;
  case ON_SubDEdgeTag::Crease:
    if (bUseCreaseSharpness)
      return ON_SubDEdgeSharpness::Crease;
    break;
  default:
    break;
  }
  return ON_SubDEdgeSharpness::Nan;
}

const double ON_SubD_ComponentIdTypeAndTag::VertexSharpness() const
{
  return
    (ON_SubDComponentPtr::Type::Vertex == m_type && m_sharpness.IsConstant()) 
    ? m_sharpness[0] 
    : 0.0;
}

void ON_SubD_ComponentIdTypeAndTag::SetVertexSharpness(double s)
{
  m_sharpness = ON_SubDEdgeSharpness::FromConstant(ON_SubDEdgeSharpness::IsValidValue(s, false) ? s : 0.0);
}


unsigned ON_SubD_ComponentIdTypeAndTag::FaceId() const
{
  return (ON_SubDComponentPtr::Type::Face == m_type) ? m_id : 0;
}

ON_SubDVertexTag ON_SubD_ComponentIdTypeAndTag::VertexTag() const
{
  return (ON_SubDComponentPtr::Type::Vertex == m_type) ? ON_SubD::VertexTagFromUnsigned(this->Internal_Tag()) : ON_SubDVertexTag::Unset;
}

ON_SubDEdgeTag ON_SubD_ComponentIdTypeAndTag::EdgeTag() const
{
  return (ON_SubDComponentPtr::Type::Edge == m_type) ? ON_SubD::EdgeTagFromUnsigned(this->Internal_Tag()) : ON_SubDEdgeTag::Unset;
}

unsigned char ON_SubD_ComponentIdTypeAndTag::FaceTag() const
{
  return (ON_SubDComponentPtr::Type::Face == m_type) ? this->Internal_Tag() : 0;
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFromMeshParameters
//

// Convex corner options

ON_SubDFromMeshParameters::ConvexCornerOption ON_SubDFromMeshParameters::ConvexCornerOptionFromUnsigned(
  unsigned int convex_corner_option_as_unsigned
)
{
  switch (convex_corner_option_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::ConvexCornerOption::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::ConvexCornerOption::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::ConvexCornerOption::AtMeshCorner);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDFromMeshParameters::ConvexCornerOption::Unset);
}

void ON_SubDFromMeshParameters::SetConvexCornerOption(
  ON_SubDFromMeshParameters::ConvexCornerOption convex_corner_option
  )
{
  m_convex_corner_option = ON_SubDFromMeshParameters::ConvexCornerOptionFromUnsigned((unsigned int)convex_corner_option);
}

ON_SubDFromMeshParameters::ConvexCornerOption ON_SubDFromMeshParameters::GetConvexCornerOption() const
{
  switch (m_convex_corner_option)
  {
  case ON_SubDFromMeshParameters::ConvexCornerOption::Unset:
  case ON_SubDFromMeshParameters::ConvexCornerOption::None:
    return m_convex_corner_option;

  case ON_SubDFromMeshParameters::ConvexCornerOption::AtMeshCorner:
    if ( m_maximum_convex_corner_edge_count >= 2 
         && m_maximum_convex_corner_edge_count <= ON_SubDVertex::MaximumEdgeCount
         && m_maximum_convex_corner_angle_radians >= 0.0
         && m_maximum_convex_corner_angle_radians < ON_PI
         )
         return m_convex_corner_option;
    break;
  }

  return ON_SubDFromMeshParameters::ConvexCornerOption::Unset;
}

void ON_SubDFromMeshParameters::SetMaximumConvexCornerEdgeCount(
  unsigned int maximum_convex_corner_edge_count
  )
{
  if ( maximum_convex_corner_edge_count >= 2 && maximum_convex_corner_edge_count <= ON_SubDVertex::MaximumEdgeCount)
    m_maximum_convex_corner_edge_count = (unsigned short)maximum_convex_corner_edge_count;
}

unsigned int ON_SubDFromMeshParameters::MaximumConvexCornerEdgeCount() const
{
  return m_maximum_convex_corner_edge_count;
}

void ON_SubDFromMeshParameters::SetMaximumConvexCornerAngleRadians(
  double maximum_convex_corner_angle_radians
  )
{
  if (maximum_convex_corner_angle_radians > 0.0 && maximum_convex_corner_angle_radians < ON_PI)
    m_maximum_convex_corner_angle_radians = maximum_convex_corner_angle_radians;
}

double ON_SubDFromMeshParameters::MaximumConvexCornerAngleRadians() const
{
  return m_maximum_convex_corner_angle_radians;
}

ON_SubDFromMeshParameters::ConvexCornerOption ON_SubDFromMeshParameters::CopyConvexCornerTest(
  ON_SubDFromMeshParameters source_parameters
  )
{
  SetConvexCornerOption(source_parameters.GetConvexCornerOption());
  SetMaximumConvexCornerEdgeCount(source_parameters.MaximumConvexCornerEdgeCount());
  SetMaximumConvexCornerAngleRadians(source_parameters.MaximumConvexCornerAngleRadians());
  return GetConvexCornerOption();
}

// concave corner options

ON_SubDFromMeshParameters::ConcaveCornerOption ON_SubDFromMeshParameters::ConcaveCornerOptionFromUnsigned(
  unsigned int concave_corner_option_as_unsigned
)
{
  switch (concave_corner_option_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::ConcaveCornerOption::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::ConcaveCornerOption::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::ConcaveCornerOption::AtMeshCorner);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDFromMeshParameters::ConcaveCornerOption::Unset);
}

void ON_SubDFromMeshParameters::SetConcaveCornerOption(
  ON_SubDFromMeshParameters::ConcaveCornerOption concave_corner_option
)
{
  m_concave_corner_option = ON_SubDFromMeshParameters::ConcaveCornerOptionFromUnsigned((unsigned int)concave_corner_option);
}

ON_SubDFromMeshParameters::ConcaveCornerOption ON_SubDFromMeshParameters::GetConcaveCornerOption() const
{
  switch (m_concave_corner_option)
  {
  case ON_SubDFromMeshParameters::ConcaveCornerOption::Unset:
  case ON_SubDFromMeshParameters::ConcaveCornerOption::None:
    return m_concave_corner_option;

  case ON_SubDFromMeshParameters::ConcaveCornerOption::AtMeshCorner:
    if (m_minimum_concave_corner_edge_count >= 2
      && m_minimum_concave_corner_edge_count <= ON_SubDVertex::MaximumEdgeCount
      && m_minimum_concave_corner_angle_radians > ON_PI
      && m_minimum_concave_corner_angle_radians <= ON_2PI
      )
      return m_concave_corner_option;
    break;
  }

  return ON_SubDFromMeshParameters::ConcaveCornerOption::Unset;
}

void ON_SubDFromMeshParameters::SetMinimumConcaveCornerEdgeCount(
  unsigned int minimum_concave_corner_edge_count
)
{
  if (minimum_concave_corner_edge_count >= 2 && minimum_concave_corner_edge_count <= ON_SubDVertex::MaximumEdgeCount)
    m_minimum_concave_corner_edge_count = (unsigned short)minimum_concave_corner_edge_count;
}

unsigned int ON_SubDFromMeshParameters::MinimumConcaveCornerEdgeCount() const
{
  return m_minimum_concave_corner_edge_count;
}

void ON_SubDFromMeshParameters::SetMinimumConcaveCornerAngleRadians(
  double minimum_concave_corner_angle_radians
)
{
  if (minimum_concave_corner_angle_radians > ON_PI && minimum_concave_corner_angle_radians <= ON_2PI)
    m_minimum_concave_corner_angle_radians = minimum_concave_corner_angle_radians;
}

double ON_SubDFromMeshParameters::MinimumConcaveCornerAngleRadians() const
{
  return m_minimum_concave_corner_angle_radians;
}

ON_SubDFromMeshParameters::ConcaveCornerOption ON_SubDFromMeshParameters::CopyConcaveCornerTest(
  ON_SubDFromMeshParameters source_parameters
)
{
  SetConcaveCornerOption(source_parameters.GetConcaveCornerOption());
  SetMinimumConcaveCornerEdgeCount(source_parameters.MinimumConcaveCornerEdgeCount());
  SetMinimumConcaveCornerAngleRadians(source_parameters.MinimumConcaveCornerAngleRadians());
  return GetConcaveCornerOption();
}


bool ON_SubDFromMeshParameters::InterpolateMeshVertices() const
{
  return m_bInterpolateMeshVertices;
}

void ON_SubDFromMeshParameters::SetInterpolateMeshVertices(
  bool bInterpolateMeshVertices
)
{
  // Not supported in free opennurbs
  m_bInterpolateMeshVertices = false;
}

ON_SubDFromMeshParameters::TextureCoordinatesOption ON_SubDFromMeshParameters::TextureCoordinatesOptionFromUnsigned(
  unsigned int texture_coordinate_option_as_unsigned
)
{
  switch (texture_coordinate_option_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::TextureCoordinatesOption::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::TextureCoordinatesOption::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::TextureCoordinatesOption::Automatic);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::TextureCoordinatesOption::Packed);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::TextureCoordinatesOption::CopyMapping);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::TextureCoordinatesOption::CopyCoordinates);
  default:
    break;
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDFromMeshParameters::TextureCoordinatesOption::Unset);
}


void ON_SubDFromMeshParameters::SetTextureCoordinatesOption(
  ON_SubDFromMeshParameters::TextureCoordinatesOption texture_coorindates_option
)
{
  // use TextureCoordinatesOptionFromUnsigned to trap invalid input.
  m_texture_coordinates_option = ON_SubDFromMeshParameters::TextureCoordinatesOptionFromUnsigned(static_cast<unsigned char>(texture_coorindates_option));
}

ON_SubDFromMeshParameters::TextureCoordinatesOption ON_SubDFromMeshParameters::GetTextureCoordinatesOption() const
{
  return m_texture_coordinates_option;
}

bool ON_SubDFromMeshParameters::MergeColinearBoundaryEdges() const
{
  // clear bit means true, set bit means false
  return (0 == (ON_SubDFromMeshParameters::MergeColinearBoundaryEdgesMask & m_merge_edges_bits));
}

void ON_SubDFromMeshParameters::SetMergeColinearBoundaryEdges(
  bool bAllowColinearBoundaryEdges
)
{
  const unsigned char mask = ON_SubDFromMeshParameters::MergeColinearBoundaryEdgesMask;
  if (false == bAllowColinearBoundaryEdges)
    m_merge_edges_bits |= mask; // set bit
  else
    m_merge_edges_bits &= ~mask; // clear bit
}

bool ON_SubDFromMeshParameters::MergeColinearInteriorEdges() const
{
  // clear bit means true, set bit means false
  return (0 == (ON_SubDFromMeshParameters::MergeColinearInteriorEdgesMask & m_merge_edges_bits));
}

void ON_SubDFromMeshParameters::SetMergeColinearInteriorEdges(
  bool bAllowColinearInteriorEdges
)
{
  const unsigned char mask = ON_SubDFromMeshParameters::MergeColinearInteriorEdgesMask;
  if (false == bAllowColinearInteriorEdges)
    m_merge_edges_bits |= mask; // set bit
  else
    m_merge_edges_bits &= ~mask; // clear bit
}


void ON_SubDFromMeshParameters::SetInteriorCreaseOption(
  ON_SubDFromMeshParameters::InteriorCreaseOption interior_crease_option
  )
{
  m_interior_crease_option = ON_SubDFromMeshParameters::InteriorCreaseOptionFromUnsigned((unsigned int)interior_crease_option);
}

ON_SubDFromMeshParameters::InteriorCreaseOption ON_SubDFromMeshParameters::GetInteriorCreaseOption() const
{
  return m_interior_crease_option;
}

ON_SubDFromMeshParameters::InteriorCreaseOption ON_SubDFromMeshParameters::CopyInteriorCreaseTest(
  ON_SubDFromMeshParameters source_parameters
  )
{
  SetInteriorCreaseOption(source_parameters.GetInteriorCreaseOption());
  return GetInteriorCreaseOption();
}

ON_SubDFromMeshParameters::InteriorCreaseOption ON_SubDFromMeshParameters::InteriorCreaseOptionFromUnsigned(
  unsigned int interior_crease_option_as_unsigned
  )
{
  switch (interior_crease_option_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::InteriorCreaseOption::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::InteriorCreaseOption::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDFromMeshParameters::InteriorCreaseOption::AtMeshDoubleEdge);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDFromMeshParameters::InteriorCreaseOption::Unset);
}


ON_SubDFromSurfaceParameters::Methods ON_SubDFromSurfaceParameters::Method() const
{
  return m_method;
}

void ON_SubDFromSurfaceParameters::SetMethod(
  ON_SubDFromSurfaceParameters::Methods method
  )
{
  m_method = method;
}

bool ON_SubDFromSurfaceParameters::Corners() const
{
  return m_bCorners;
}

void ON_SubDFromSurfaceParameters::SetCorners(
  bool bCorners
  )
{
  m_bCorners = bCorners ? true : false;
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDVertex
//

const ON_SubDEdgePtr ON_SubDVertex::EdgePtr(
  unsigned int i
) const
{
  return (i < m_edge_count) ? m_edges[i] : ON_SubDEdgePtr::Null;
}


const class ON_SubDEdge* ON_SubDVertex::Edge(
  unsigned int i
  ) const
{
  return (i < m_edge_count) ? ON_SUBD_EDGE_POINTER(m_edges[i].m_ptr) : nullptr;
}

ON__UINT_PTR ON_SubDVertex::EdgeDirection(
  unsigned int i
  ) const
{
  return (i < m_edge_count) ? ON_SUBD_EDGE_DIRECTION(m_edges[i].m_ptr) : 0;
}

unsigned int ON_SubDVertex::EdgeCount() const
{
  return m_edge_count;
}

unsigned int ON_SubDVertex::EdgeCount(
  ON_SubDEdgeTag edge_tag
  ) const
{
  if (nullptr != m_edges)
  {
    unsigned int matching_edge_count = 0;
    const unsigned int edge_count = m_edge_count;
    for (unsigned int vei = 0; vei < edge_count; vei++)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
      if (nullptr != e && edge_tag == e->m_edge_tag)
        matching_edge_count++;
    }
    return matching_edge_count;
  }
  return 0;
}

unsigned int ON_SubDVertex::EdgeArrayIndex(
  const ON_SubDEdge* edge
  ) const
{
  if ( nullptr == edge )
    return ON_UNSET_UINT_INDEX;
  const unsigned int edge_count = m_edge_count;
  if ( 0 == edge_count)
    return ON_UNSET_UINT_INDEX;
  const ON_SubDEdgePtr* eptr = m_edges;
  if ( nullptr == eptr)
    return ON_SUBD_RETURN_ERROR(ON_UNSET_UINT_INDEX);

  for ( unsigned int i = 0; i < edge_count; i++, eptr++)
  {
    if (edge == ON_SUBD_EDGE_POINTER(eptr->m_ptr))
      return i;
  }

  return ON_UNSET_UINT_INDEX;
}

unsigned int ON_SubDVertex::ReplaceEdgeInArray(
  const ON_SubDEdge* old_edge,
  const ON_SubDEdgePtr new_edge
  )
{
  if (m_edges == nullptr || m_edge_count == 0)
    return ON_SUBD_RETURN_ERROR(ON_UNSET_UINT_INDEX);
  unsigned vei = old_edge != nullptr ? EdgeArrayIndex(old_edge) : ON_UNSET_UINT_INDEX;
  if (ON_UNSET_UINT_INDEX == vei || m_edges[vei].m_ptr == new_edge.m_ptr)
    return ON_UNSET_UINT_INDEX;
  if (new_edge.IsNotNull())
  {
    m_edges[vei] = new_edge;
  }
  else
  {
    const unsigned c = (unsigned)(m_edge_count--);
    while (++vei < c)
      m_edges[vei - 1] = m_edges[vei];
  }
  return vei;
}

unsigned int ON_SubDVertex::MarkedEdgeCount() const
{
  unsigned int mark_count = 0;
  for (unsigned short vei = 0; vei < m_edge_count; ++vei)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
    if (nullptr != e && e->m_status.RuntimeMark())
      ++mark_count;
  }
  return mark_count;
}

bool ON_SubDVertex::ClearEdgeMarks() const
{
  bool rc = true;
  for (unsigned short vei = 0; vei < m_edge_count; ++vei)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
    if (nullptr == e)
      rc = false;
    else
      e->m_status.ClearRuntimeMark();
  }
  return rc;
}

unsigned int ON_SubDVertex::MarkedFaceCount() const
{
  unsigned int mark_count = 0;
  for (unsigned short vfi = 0; vfi < m_face_count; ++vfi)
  {
    const ON_SubDFace* f = m_faces[vfi];
    if (nullptr != f && f->m_status.RuntimeMark())
      ++mark_count;
  }
  return mark_count;
}

bool ON_SubDVertex::ClearFaceMarks() const
{
  bool rc = true;
  for (unsigned short vfi = 0; vfi < m_face_count; ++vfi)
  {
    const ON_SubDFace* f = m_faces[vfi];
    if (nullptr == f)
      rc = false;
    else
      f->m_status.ClearRuntimeMark();
  }
  return rc;
}


unsigned int ON_SubDVertex::MinimumFaceEdgeCount() const
{
  unsigned short min_count = 0xFFFFU;
  for (unsigned short vfi = 0; vfi < m_face_count; ++vfi)
  {
    const ON_SubDFace* f = m_faces[vfi];
    if (nullptr != f && f->m_edge_count < min_count)
      min_count = f->m_edge_count;
  }
  return min_count < 0xFFFFU ? min_count : 0;
}

unsigned int ON_SubDVertex::MaximumFaceEdgeCount() const
{
  unsigned short max_count = 0;
  for (unsigned short vfi = 0; vfi < m_face_count; ++vfi)
  {
    const ON_SubDFace* f = m_faces[vfi];
    if (nullptr != f && f->m_edge_count < max_count)
      max_count = f->m_edge_count;
  }
  return max_count;
}


unsigned int ON_SubDVertex::MinimumEdgeFaceCount() const
{
  unsigned short min_count = 0xFFFFU;
  for (unsigned short vei = 0; vei < m_edge_count; ++vei)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
    if (nullptr != e && e->m_face_count < min_count)
      min_count = e->m_face_count;
  }
  return min_count < 0xFFFFU ? min_count : 0;
}

unsigned int ON_SubDVertex::MaximumEdgeFaceCount() const
{
  unsigned short max_count = 0;
  for (unsigned short vei = 0; vei < m_edge_count; ++vei)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
    if (nullptr != e && e->m_face_count > max_count)
    max_count = e->m_face_count;
  }
  return max_count;
}

unsigned int ON_SubDEdge::MarkedVertexCount() const
{
  unsigned int mark_count = 0;
  for (unsigned evi = 0; evi < 2; ++evi)
  {
    const ON_SubDVertex* v = m_vertex[evi];
    if (nullptr != v && v->m_status.RuntimeMark())
      ++mark_count;
  }
  return mark_count;
}

unsigned int ON_SubDEdge::MarkedFaceCount() const
{
  unsigned int mark_count = 0;
  const ON_SubDFacePtr* fptr = m_face2;
  for (unsigned short efi = 0; efi < m_face_count; ++efi, ++fptr)
  {
    if (2 == efi)
    {
      fptr = m_facex;
      if (nullptr == fptr)
        break;
    }
    const ON_SubDFace* f = ON_SUBD_FACE_POINTER(fptr->m_ptr);
    if (nullptr != f && f->m_status.RuntimeMark())
      ++mark_count;
  }
  return mark_count;
}

unsigned int ON_SubDVertex::FaceCount() const
{
  return m_face_count;
}

const class ON_SubDFace* ON_SubDVertex::Face(
  unsigned int i
  ) const
{
  //return (i < m_face_count) ? ON_SUBD_FACE_POINTER(m_faces[i].m_ptr) : nullptr;
  return (i < m_face_count) ? m_faces[i] : nullptr;
}


unsigned int ON_SubDVertex::FaceArrayIndex(
  const ON_SubDFace* face
  ) const
{
  if ( nullptr == face )
    return ON_UNSET_UINT_INDEX;
  const unsigned int face_count = m_face_count;
  if ( 0 == face_count)
    return ON_UNSET_UINT_INDEX;
  if ( nullptr == m_faces)
    return ON_SUBD_RETURN_ERROR(ON_UNSET_UINT_INDEX);

  for ( unsigned int i = 0; i < face_count; i++)
  {
    if (face == m_faces[i] )
      return i;
  }

  return ON_UNSET_UINT_INDEX;
}

unsigned int ON_SubDVertex::ReplaceFaceInArray(const ON_SubDFace * old_face, const ON_SubDFace * new_face)
{
  unsigned vfi = (nullptr != old_face && old_face != new_face) ? FaceArrayIndex(old_face) : ON_UNSET_UINT_INDEX;
  if (ON_UNSET_UINT_INDEX == vfi)
    return ON_UNSET_UINT_INDEX;
  if (nullptr != new_face)
  {
    m_faces[vfi] = new_face;
  }
  else
  {
    const unsigned c = (unsigned)(m_face_count--);
    while (++vfi < c)
      m_faces[vfi - 1] = m_faces[vfi];
  }
  return vfi;
}

const ON_3dPoint ON_SubDVertex::ControlNetPoint() const
{
  return ON_3dPoint(m_P);
}

bool ON_SubDVertex::IsSmooth() const
{
  return (ON_SubDVertexTag::Smooth == m_vertex_tag);
}

bool ON_SubDVertex::IsCrease() const
{
  return (ON_SubDVertexTag::Crease == m_vertex_tag);
}

bool ON_SubDVertex::IsOneSectorCrease() const
{
  return (ON_SubDVertexTag::Crease == m_vertex_tag && m_edge_count == m_face_count+1 && m_face_count >= 1);
}

bool ON_SubDVertex::IsTwoSectorCrease() const
{
  return (ON_SubDVertexTag::Crease == m_vertex_tag && m_edge_count == m_face_count && m_face_count >= 2);
}

bool ON_SubDVertex::IsCorner() const
{
  return (ON_SubDVertexTag::Corner == m_vertex_tag);
}

bool ON_SubDVertex::IsDart() const
{
  return (ON_SubDVertexTag::Dart == m_vertex_tag);
}

bool ON_SubDVertex::IsCreaseOrCorner() const
{
  return (ON_SubDVertexTag::Crease == m_vertex_tag || ON_SubDVertexTag::Corner == m_vertex_tag);
}

bool ON_SubDVertex::IsDartOrCreaseOrCorner() const
{
  return (
    ON_SubDVertexTag::Dart == m_vertex_tag
    || ON_SubDVertexTag::Crease == m_vertex_tag
    || ON_SubDVertexTag::Corner == m_vertex_tag
    );
}


bool ON_SubDVertex::IsDartOrCrease() const
{
  return (
    ON_SubDVertexTag::Dart == m_vertex_tag
    || ON_SubDVertexTag::Crease == m_vertex_tag
    );
}

bool ON_SubDVertex::IsDartOrCorner() const
{
  return (
    ON_SubDVertexTag::Dart == m_vertex_tag
    || ON_SubDVertexTag::Corner == m_vertex_tag
    );
}


bool ON_SubDVertex::IsSmoothOrDart() const
{
  return (ON_SubDVertexTag::Smooth == m_vertex_tag || ON_SubDVertexTag::Dart == m_vertex_tag);
}

bool ON_SubDVertex::IsSmoothOrDartOrCrease() const
{
  return (ON_SubDVertexTag::Smooth == m_vertex_tag || ON_SubDVertexTag::Dart == m_vertex_tag || ON_SubDVertexTag::Crease == m_vertex_tag);
}

bool ON_SubDVertex::IsSmoothOrCrease() const
{
  return (ON_SubDVertexTag::Smooth == m_vertex_tag || ON_SubDVertexTag::Crease == m_vertex_tag);
}

bool ON_SubDVertex::GetBoundaryVertexEdges(
  ON_SubDEdgePtr* eptr0,
  ON_SubDEdgePtr* eptr1
) const
{
  unsigned int vbi[2] = {};
  const bool rc = GetBoundaryVertexEdgeIndices(&vbi[0], &vbi[1]);
  if (rc)
  {
    if (nullptr != eptr0)
      *eptr0 = m_edges[vbi[0]];
    if (nullptr != eptr1)
      *eptr1 = m_edges[vbi[1]];
  }
  else
  {
    if (nullptr != eptr0)
      *eptr0 = ON_SubDEdgePtr::Null;
    if (nullptr != eptr1)
      *eptr1 = ON_SubDEdgePtr::Null;
  }
  return rc;
}

bool ON_SubDVertex::GetBoundaryVertexEdgeIndices(
  unsigned* vei0,
  unsigned* vei1
) const
{
  unsigned int vbi_count = 0;
  unsigned int vbi[2] = {};
  for (unsigned short vei = 0; vei < m_edge_count; vei++)
  {
    const ON_SubDEdge* e = m_edges[vei].Edge();
    if (1 == e->m_face_count)
    {
      if (vbi_count < 2)
        vbi[vbi_count++] = vei;
      else
      {
        vbi_count = 0;
        break;
      }
    }
  }
  if (2 != vbi_count)
    vbi[0] = vbi[1] = ON_UNSET_UINT_INDEX;
  if (nullptr != vei0)
    *vei0 = vbi[0];
  if (nullptr != vei1)
    *vei1 = vbi[1];
  return (2 == vbi_count);
}

const ON_SubDVertexEdgeProperties ON_SubDVertex::EdgeProperties() const
{
  ON_SubDVertexEdgeProperties ep;

  ep.m_edge_count = m_edge_count;
  ep.m_face_count = m_face_count;

  bool bFirstEdge = true;
  for (unsigned short vei = 0; vei < ep.m_edge_count; vei++)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
    if (nullptr == e)
    {
      ep.m_null_edge_count++;
      continue;
    }

    if (e->IsCrease())
      ep.m_crease_edge_count++;
    else if (e->IsSmooth())
      ep.m_smooth_edge_count++;
    else
      ep.m_unset_edge_count++;

    const unsigned short edge_face_count = e->m_face_count;
    if (bFirstEdge)
    {
      bFirstEdge = false;
      ep.m_min_edge_face_count = edge_face_count;
      ep.m_max_edge_face_count = edge_face_count;
    }
    else if (edge_face_count < ep.m_min_edge_face_count)
      ep.m_min_edge_face_count = edge_face_count;
    else if (edge_face_count > ep.m_max_edge_face_count)
      ep.m_max_edge_face_count = edge_face_count;

    if (0 == edge_face_count)
      ep.m_wire_edge_count++;
    else if (1 == edge_face_count)
      ep.m_boundary_edge_count++;
    else if (2 == edge_face_count)
      ep.m_interior_edge_count++;
    else
      ep.m_nonmanifold_edge_count++;

  }
  return ep;
}


bool ON_SubDEdge::IsCrease() const
{
  return (ON_SubDEdgeTag::Crease == m_edge_tag) ? true : false;
}


bool ON_SubDEdge::IsHardCrease() const
{
  return
    (
      ON_SubDEdgeTag::Crease == m_edge_tag
      && nullptr != m_vertex[0]
      && nullptr != m_vertex[1]
      && m_vertex[0]->IsCreaseOrCorner()
      && m_vertex[1]->IsCreaseOrCorner()
      )
    ? true
    : false;
}

bool ON_SubDEdge::IsDartCrease() const
{
  return
    (ON_SubDEdgeTag::Crease == m_edge_tag && DartCount() > 0 )
    ? true
    : false;
}

unsigned int ON_SubDEdge::DartCount() const
{
  unsigned int dart_count = 0;
  if (nullptr != m_vertex[0] && ON_SubDVertexTag::Dart == m_vertex[0]->m_vertex_tag)
    dart_count++;
  if (nullptr != m_vertex[1] && ON_SubDVertexTag::Dart == m_vertex[1]->m_vertex_tag)
    dart_count++;
  return dart_count;
}

bool ON_SubDEdge::IsSmooth() const
{
  return (ON_SubDEdgeTag::Smooth == m_edge_tag || ON_SubDEdgeTag::SmoothX == m_edge_tag) ? true : false;
}

bool ON_SubDEdge::IsSmoothNotX() const
{
  return (ON_SubDEdgeTag::Smooth == m_edge_tag) ? true : false;
}

bool ON_SubDEdge::IsSmoothX() const
{
  return (ON_SubDEdgeTag::SmoothX == m_edge_tag) ? true : false;
}

const ON_SubDEdgeSharpness ON_SubDEdge::Sharpness(bool bUseCreaseSharpness) const
{
  return IsSmooth() 
    ? (m_sharpness.IsValid() ? m_sharpness : ON_SubDEdgeSharpness::Smooth)
    : ((bUseCreaseSharpness && IsCrease()) ? ON_SubDEdgeSharpness ::Crease : ON_SubDEdgeSharpness::Smooth);
}

double ON_SubDEdge::EndSharpness(
  unsigned evi
) const
{
  return EndSharpness(evi, false);
}

double ON_SubDEdge::EndSharpness(
  unsigned evi,
  bool bUseCreaseSharpness
) const
{
  return (IsSmooth() && evi >= 0 && evi <= 1)
    ? m_sharpness[evi]
    : ((bUseCreaseSharpness && IsCrease()) ? ON_SubDEdgeSharpness::CreaseValue : ON_SubDEdgeSharpness::SmoothValue);
}

double ON_SubDEdge::EndSharpness(
  const ON_SubDVertex* v
) const
{
  if (nullptr != v)
  {
    if (v == m_vertex[0])
      return EndSharpness(0U);
    if (v == m_vertex[1])
      return EndSharpness(1U);
  }
  return 0.0;
}

const ON_SubDEdgeSharpness ON_SubDEdge::SubdivideSharpness(
  unsigned evi,
  bool bReverse
) const
{
  const ON_SubDEdgeSharpness s = Sharpness(false).Subdivided(evi);
  return bReverse ? s.Reversed() : s;
}

const ON_SubDEdgeSharpness ON_SubDEdge::SubdivideSharpness(
  const class ON_SubDVertex* end_vertex,
  bool bReverse
) const
{
  if (nullptr != end_vertex)
  {
    if (end_vertex == this->m_vertex[0])
      return this->SubdivideSharpness(0U, bReverse);
    if (end_vertex == this->m_vertex[1])
      return this->SubdivideSharpness(1U, bReverse);
  }
  return ON_SubDEdgeSharpness::Smooth;
}

bool ON_SubDEdge::ClearSharpnessForExperts()
{
  const bool bChanged = IsSmooth() && (m_sharpness != ON_SubDEdgeSharpness::Smooth);
  m_sharpness = ON_SubDEdgeSharpness::Smooth;
  return bChanged;
}

void ON_SubDEdge::SetSharpnessForExperts(ON_SubDEdgeSharpness sharpness)
{
  m_sharpness 
    = IsSmooth() && sharpness.IsValid() 
    ? sharpness 
    : ON_SubDEdgeSharpness::Smooth;
}

double ON_SubDEdgeSharpness::ToPercentage(double sharpness, double crease_percentage)
{
  if (0.0 <= sharpness && sharpness <= ON_SubDEdgeSharpness::MaximumValue)
    return 100.0 * (sharpness / ON_SubDEdgeSharpness::MaximumValue);
  if (ON_SubDEdgeSharpness::CreaseValue == sharpness)
    return crease_percentage;
  return ON_DBL_QNAN;
}

const ON_wString ON_SubDEdgeSharpness::ToPercentageText(double sharpness)
{
  if ( ON_SubDEdgeSharpness::IsValidValue(sharpness,false) )
  {
    const double s = sharpness / ON_SubDEdgeSharpness::MaximumValue;
    double m = 1.0; 
    unsigned max_decimal_places = 4;
    for (unsigned decimal_places = 0; decimal_places <= max_decimal_places; ++decimal_places, m *= 10.0 )
    {
      double p = 100.0 * m * s;
      double f = floor(p);
      if (p - f > 0.5)
        f = f + 1.0;
      f /= m;
      if (fabs(f - 100.0*s) <= 0.00005)
      {
        double minf = 1.0 / m;
        if (f < minf && sharpness > 0.0)
        {
          if (decimal_places < max_decimal_places)
            continue;          
          f = minf;
        }
        else if (f > 100.0 - minf && sharpness < ON_SubDEdgeSharpness::MaximumValue)
        {
          if (decimal_places < max_decimal_places)
            continue;
          f = 100.0 - minf;
        }
        if (0 == decimal_places)
          return ON_wString::FormatToString(L"%g%%", f);
        const ON_wString format = ON_wString::FormatToString(L"%%.%df%%%%", decimal_places);
        return ON_wString::FormatToString(format, f);
      }
    }
    return ON_wString::FormatToString(L"%g%%", s*100.0);
  }

  if (ON_SubDEdgeSharpness::CreaseValue == sharpness)
    return ON_wString(L"crease");

  return ON_wString(ON_wString::WarningSign);
}

const ON_wString ON_SubDEdgeSharpness::ToPercentageText(bool bOrderMinToMax) const
{
  if (IsValid())
  {
    if ( IsConstant() )
      return ON_SubDEdgeSharpness::ToPercentageText(EndSharpness(0));
    const int i0 = (bOrderMinToMax && (EndSharpness(0) > EndSharpness(1))) ? 1 : 0;
    const double s0 = EndSharpness(i0);
    const double s1 = EndSharpness(1-i0);
    return
      ON_SubDEdgeSharpness::ToPercentageText(s0)
      + ON_wString("-")
      + ON_SubDEdgeSharpness::ToPercentageText(s1);
  }

  if (IsCrease())
    return ON_SubDEdgeSharpness::ToPercentageText(ON_SubDEdgeSharpness::CreaseValue);

  // invalid sharpness
  return ON_SubDEdgeSharpness::ToPercentageText(ON_DBL_QNAN);
}

bool ON_SubDEdgeSharpness::IsConstant() const
{
  // NOTE WELL:
  // ON_SubDEdgeSharpness::Crease::IsConstant() and ON_SubDEdgeSharpness::Nan::IsConstant()
  // must be false.
  return m_edge_sharpness[0] == m_edge_sharpness[1] && 0.0f <= m_edge_sharpness[0] && m_edge_sharpness[0] <= ((float)ON_SubDEdgeSharpness::MaximumValue);
}

bool ON_SubDEdgeSharpness::IsConstant(bool bCreaseResult) const
{
  return 
    (m_edge_sharpness[0] == m_edge_sharpness[1])
    && 
    (
      (0.0f <= m_edge_sharpness[0] && m_edge_sharpness[0] <= ((float)ON_SubDEdgeSharpness::MaximumValue))
      ||
      (bCreaseResult && m_edge_sharpness[0] == ((float)ON_SubDEdgeSharpness::CreaseValue))
    );
}

bool ON_SubDEdgeSharpness::IsConstant(
  const ON_SimpleArray<ON_SubDEdgePtr>& edges,
  bool bCreaseResult
)
{
  return ON_SubDEdgeSharpness::IsConstant(
    edges.Count(),
    edges.Array(),
    bCreaseResult
  );
}

bool ON_SubDEdgeSharpness::IsConstant(
  size_t edge_count,
  const ON_SubDEdgePtr* edges,
  bool bCreaseResult
)
{
  if (edge_count < 1 || nullptr == edges)
    return false;
  
  ON_SubDEdgeSharpness s = edges[0].RelativeSharpness(true);
  if (false == s.IsConstant(bCreaseResult))
    return false;
  const double c = s[0];
  if (nullptr == edges[0].RelativeVertex(0))
    return false; // not an edge chain
  for (size_t i = 0; i < edge_count; ++i)
  {
    s = edges[i].RelativeSharpness(true);
    if ( false == (c == s.EndSharpness(0) && c == s.EndSharpness(1)))
      return false;
  }

  return true;
}


bool ON_SubDEdgeSharpness::IsIncreasing() const
{
  return (m_edge_sharpness[0] < m_edge_sharpness[1]);
}

bool ON_SubDEdgeSharpness::IsDecreasing() const
{
  return (m_edge_sharpness[0] > m_edge_sharpness[1]);
}

int ON_SubDEdgeSharpness::Trend() const
{

  if (m_edge_sharpness[0] < m_edge_sharpness[1])
    return 1;
  if (m_edge_sharpness[0] > m_edge_sharpness[1])
    return -1;
  if (m_edge_sharpness[0] == m_edge_sharpness[1])
    return 0;
  return ON_UNSET_INT_INDEX;
}


double ON_SubDEdgeSharpness::Delta() const
{

  if (m_edge_sharpness[0] != m_edge_sharpness[1])
    return ((double)m_edge_sharpness[1]) - ((double)m_edge_sharpness[0]);
  if (m_edge_sharpness[0] == m_edge_sharpness[1])
    return 0.0;
  return ON_DBL_QNAN;
}

bool ON_SubDEdgeSharpness::EqualEndSharpness(
  ON_SubDEdgeSharpness s0,
  ON_SubDEdgeSharpness s1
)
{
  return (s0.m_edge_sharpness[1] == s1.m_edge_sharpness[0]);
}

bool ON_SubDEdgeSharpness::EqualTrend(
  ON_SubDEdgeSharpness s0,
  ON_SubDEdgeSharpness s1
)
{
  if (false == (s0.m_edge_sharpness[1] == s1.m_edge_sharpness[0]))
    return false;
  return (s0.Trend() == s1.Trend());
}


bool ON_SubDEdgeSharpness::EqualDelta(
  ON_SubDEdgeSharpness s0,
  ON_SubDEdgeSharpness s1
)
{
  if (false == (s0.m_edge_sharpness[1] == s1.m_edge_sharpness[0]))
    return false;
  
  const double delta0 = s0.Delta();
  const double delta1 = s1.Delta();

  if (0.0 != delta0 && 0.0 != delta1)
  {
    // fuzzy compare for nonzero deltas
    const double d = fabs(delta0 - delta1);
    return (d <= ON_SubDEdgeSharpness::Tolerance);
  }

  // strict compare for zero deltas.
  return 0.0 == delta0 && 0.0 == delta1;
}

bool ON_SubDEdgeSharpness::EqualEndSharpness(
  const class ON_SubDEdgePtr& eptr0,
  const class ON_SubDEdgePtr& eptr1
)
{
  const ON_SubDEdge* e[2] = { eptr0.Edge(), eptr1.Edge() };
  if (nullptr == e[0] || nullptr == e[1] || e[0] == e[1])
    return false;

  if (e[0]->m_edge_tag != e[1]->m_edge_tag)
    return false;

  const ON_SubDVertex* v = eptr0.RelativeVertex(1);
  if (nullptr == v)
    return false;
  if (v != eptr1.RelativeVertex(0))
    return false;

  return ON_SubDEdgeSharpness::EqualEndSharpness(eptr0.RelativeSharpness(true), eptr1.RelativeSharpness(true));
}

bool ON_SubDEdgeSharpness::EqualTrend(
  const ON_SubDEdgePtr& eptr0,
  const ON_SubDEdgePtr& eptr1
)
{
  const ON_SubDEdge* e[2] = { eptr0.Edge(), eptr1.Edge() };
  if (nullptr == e[0] || nullptr == e[1] || e[0] == e[1])
    return false;

  if (e[0]->m_edge_tag != e[1]->m_edge_tag)
    return false;

  const ON_SubDVertex* v = eptr0.RelativeVertex(1);
  if (nullptr == v)
    return false;
  if (v != eptr1.RelativeVertex(0))
    return false;

  return ON_SubDEdgeSharpness::EqualTrend(eptr0.RelativeSharpness(true), eptr1.RelativeSharpness(true));
}

bool ON_SubDEdgeSharpness::EqualDelta(
  const ON_SubDEdgePtr& eptr0,
  const ON_SubDEdgePtr& eptr1
)
{
  const ON_SubDEdge* e[2] = { eptr0.Edge(), eptr1.Edge() };
  if (nullptr == e[0] || nullptr == e[1] || e[0] == e[1])
    return false;

  if (e[0]->m_edge_tag != e[1]->m_edge_tag)
    return false;

  const ON_SubDVertex* v = eptr0.RelativeVertex(1);
  if (nullptr == v)
    return false;
  if (v != eptr1.RelativeVertex(0))
    return false;

  return ON_SubDEdgeSharpness::EqualDelta(eptr0.RelativeSharpness(true), eptr1.RelativeSharpness(true));
}


bool ON_SubDEdgeSharpness::IsVariable() const
{
  return m_edge_sharpness[0] != m_edge_sharpness[1] && IsValid();
}

bool ON_SubDEdgeSharpness::IsZero() const
{
  // NOTE WELL:
  // ON_SubDEdgeSharpness::Crease::IsZero() and ON_SubDEdgeSharpness::Nan::IsZero()
  // must be false.
  return (0.0f == m_edge_sharpness[0] && 0.0f == m_edge_sharpness[1]);
}

bool ON_SubDEdgeSharpness::IsCrease() const
{
  const float x = (float)ON_SubDEdgeSharpness::CreaseValue;
  return (x == m_edge_sharpness[0] && x == m_edge_sharpness[1]);
}

bool ON_SubDEdgeSharpness::IsSharp() const
{
  return (m_edge_sharpness[0] > 0.0f || m_edge_sharpness[1] > 0.0f) && IsValid();
}


bool ON_SubDEdgeSharpness::IsCreaseOrSharp() const
{
  return (m_edge_sharpness[0] > 0.0f || m_edge_sharpness[1] > 0.0f) && IsValid(true);
}

bool ON_SubDEdgeSharpness::IsValidValue(
  double candidate_value,
  bool bCreaseResult
)
{
  if (candidate_value >= 0.0 && candidate_value <= ON_SubDEdgeSharpness::MaximumValue)
    return true;
  if ( ON_SubDEdgeSharpness::CreaseValue == candidate_value)
    return bCreaseResult;
  return false;
}

bool ON_SubDEdgeSharpness::IsValid() const
{
  // NOTE WELL:
  // ON_SubDEdgeSharpness::Crease::IsValid() and ON_SubDEdgeSharpness::Nan::IsValid()
  // must be false.
  return
    m_edge_sharpness[0] >= 0.0f
    && m_edge_sharpness[0] <= ((float)ON_SubDEdgeSharpness::MaximumValue)
    && m_edge_sharpness[1] >= 0.0f
    && m_edge_sharpness[1] <= ((float)ON_SubDEdgeSharpness::MaximumValue)
    ;
}

bool ON_SubDEdgeSharpness::IsNotValid() const
{
  return (false == IsValid());
}


bool ON_SubDEdgeSharpness::IsValid(bool bCreaseResult) const
{
  // The logic (bCreaseResult && IsCrease()) avoids a useless
  // call to IsCrease() in the most common case.
  return (bCreaseResult && IsCrease()) ? true : IsValid();
}

bool ON_SubDEdgeSharpness::IsNotValid(bool bCreaseResult) const
{
  return IsCrease() ? bCreaseResult : (false == IsValid());
}

const ON_SubDEdgeSharpness ON_SubDEdgeSharpness::FromConstant(
  double sharpness
)
{
  ON_SubDEdgeSharpness s;
  s.m_edge_sharpness[0] 
    = (sharpness >= 0.0 && sharpness  <= ON_SubDEdgeSharpness::MaximumValue) 
    ? ((float)ON_SubDEdgeSharpness::Sanitize(sharpness, 0.0)) 
    : (ON_SubDEdgeSharpness::CreaseValue == sharpness ? ((float)ON_SubDEdgeSharpness::CreaseValue) : ON_FLT_QNAN);
  s.m_edge_sharpness[1] = s.m_edge_sharpness[0];
  return s;
}

const ON_SubDEdgeSharpness ON_SubDEdgeSharpness::FromInterval(
  double sharpness0,
  double sharpness1
)
{
  if (sharpness0 >= 0.0 && sharpness0 <= ON_SubDEdgeSharpness::MaximumValue 
    && sharpness1 >= 0.0 && sharpness1 <= ON_SubDEdgeSharpness::MaximumValue)
  {
    ON_SubDEdgeSharpness s;
    s.m_edge_sharpness[0] = (float)ON_SubDEdgeSharpness::Sanitize(sharpness0, 0.0);
    s.m_edge_sharpness[1] = (float)ON_SubDEdgeSharpness::Sanitize(sharpness1, 0.0);
    return s;
  }
  
  if (ON_SubDEdgeSharpness::CreaseValue == sharpness0 && ON_SubDEdgeSharpness::CreaseValue == sharpness1)
  {
    return ON_SubDEdgeSharpness::Crease;
  }

  return ON_SubDEdgeSharpness::Nan;
}

const ON_SubDEdgeSharpness ON_SubDEdgeSharpness::FromInterval(const class ON_Interval& sharpness_interval)
{
  return ON_SubDEdgeSharpness::FromInterval(sharpness_interval[0], sharpness_interval[1]);
}

const ON_SubDEdgeSharpness ON_SubDEdgeSharpness::Union(
  const ON_SubDEdgeSharpness& a,
  const ON_SubDEdgeSharpness& b
)
{
  float s[4] = {};
  int count = 0;

  if (a.IsSharp())
  {
    s[0] = a.m_edge_sharpness[0];
    s[1] = a.m_edge_sharpness[1];
    count = 2;
  }
  if (b.IsSharp())
  {
    s[count] = b.m_edge_sharpness[0];
    s[count+1] = b.m_edge_sharpness[1];
    count += 2;
  }
  ON_SubDEdgeSharpness u = ON_SubDEdgeSharpness::FromConstant(s[0]);
  for ( int i = 1; i < count; ++i)
  { 
    float x = s[i];
    if (x < u.m_edge_sharpness[0])
      u.m_edge_sharpness[0] = x;
    else if (x > u.m_edge_sharpness[1])
      u.m_edge_sharpness[1] = x;
  }
  return u;
}

double ON_SubDEdgeSharpness::Sanitize(
  double sharpness, 
  double invalid_input_result
)
{
  // When sharpness is withing ON_SubDEdgeSharpness::Tolerance of an integer value,
  // snap to that integer value.

  if (false == (sharpness >= 0.0 && sharpness <= ON_SubDEdgeSharpness::MaximumValue))
    return invalid_input_result; // when sharpness is nan, invalid_input_result is returned here. 

  // When sharpness is close to an integer value, snap to the integer value.
  // This results in cleaner looking limit surfaces and faster evaluation.
  const double f = floor(sharpness);
  if (f >= 0.0 && f <= ON_SubDEdgeSharpness::MaximumValue)
  {
    if (sharpness - f <= ON_SubDEdgeSharpness::Tolerance)
      sharpness = f;
    else if (f + 1.0 - sharpness <= ON_SubDEdgeSharpness::Tolerance && f + 1.0 <= ON_SubDEdgeSharpness::MaximumValue)
      sharpness = f + 1.0;
  }

  return sharpness;
}

double ON_SubDEdgeSharpness::Sanitize(
  double sharpness
)
{
  // When edges are subdivided, the call ON_SubDEdgeSharpness::Sanitize(current_sharpness-1.0).
  // These critical calls assume this function returns 0.0 when the input is not valid, for example
  // negative when 0 <= current_sharpness < 1.
  return ON_SubDEdgeSharpness::Sanitize(sharpness, 0.0);
}

const ON_SubDEdgeSharpness ON_SubDEdgeSharpness::Subdivided(int end_index) const
{
  if (this->IsCrease())
    return ON_SubDEdgeSharpness::Crease;

  if (end_index >= 0 && end_index <= 1)
  {
    const double s[2] = { 
      ON_SubDEdgeSharpness::Sanitize(((double)(this->m_edge_sharpness[0])) - 1.0),
      ON_SubDEdgeSharpness::Sanitize(((double)(this->m_edge_sharpness[1])) - 1.0)
    };
    const double mids = (s[0] == s[1]) ? s[0] : ON_SubDEdgeSharpness::Sanitize(0.5 * (s[0] + s[1]));
    return (0 == end_index) ? ON_SubDEdgeSharpness::FromInterval(s[0], mids) : ON_SubDEdgeSharpness::FromInterval(mids, s[1]);
  }
  return ON_SubDEdgeSharpness::Smooth;
}

const ON_SubDEdgeSharpness ON_SubDEdgeSharpness::Reversed() const
{
  ON_SubDEdgeSharpness r;
  r.m_edge_sharpness[0] = this->m_edge_sharpness[1];
  r.m_edge_sharpness[1] = this->m_edge_sharpness[0];
  return r;
}

double ON_SubDEdgeSharpness::operator[](int end_index) const
{
  return this->EndSharpness(end_index);
}

bool operator!=(const ON_SubDEdgeSharpness& lhs, const ON_SubDEdgeSharpness& rhs)
{
  const float* l = (const float*)(&lhs);
  const float* r = (const float*)(&rhs);

  // The compare must be done this way so
  // any nan results in false being returned.
  // (Note: x==x and x!=x are both false when x = nan.)
  if (l[0] != r[0])
    return (l[1] == l[1] && r[1] == r[1]);
  if (l[1] != r[1])
    return (l[0] == l[0] && r[0] == r[0]);
  return false;
}

bool operator==(const ON_SubDEdgeSharpness& lhs, const ON_SubDEdgeSharpness& rhs)
{
  const float* l = (const float*)(&lhs);
  const float* r = (const float*)(&rhs);
  return l[0] == r[0] && l[1] == r[1];
}

double ON_SubDEdgeSharpness::Average() const
{
  return
    (m_edge_sharpness[0] == m_edge_sharpness[1]) 
    ? ((double)m_edge_sharpness[0]) 
    : ON_SubDEdgeSharpness::Sanitize(0.5 * ( ((double)m_edge_sharpness[0]) + ((double)m_edge_sharpness[1]) ));
}

double ON_SubDEdgeSharpness::MinimumEndSharpness() const
{
  return (double)((m_edge_sharpness[0] <= m_edge_sharpness[1]) ? m_edge_sharpness[0] : m_edge_sharpness[1]);
}

double ON_SubDEdgeSharpness::MaximumEndSharpness() const
{
  return (double)((m_edge_sharpness[0] >= m_edge_sharpness[1]) ? m_edge_sharpness[0] : m_edge_sharpness[1]);
}


double ON_SubDEdgeSharpness::EndSharpness(int end_index) const
{
  return (end_index >= 0 && end_index <= 1) ? ((double)m_edge_sharpness[end_index]) : ON_DBL_QNAN;
}


double ON_SubDEdgeSharpness::VertexSharpness(
  ON_SubDVertexTag vertex_tag,
  unsigned sharp_edge_end_count,
  double maximum_edge_end_sharpness
)
{
  return ON_SubDEdgeSharpness::VertexSharpness(vertex_tag, 0.0, sharp_edge_end_count, maximum_edge_end_sharpness);
}

double ON_SubDEdgeSharpness::VertexSharpness(
  ON_SubDVertexTag vertex_tag,
  double interior_crease_vertex_sharpness,
  unsigned sharp_edge_end_count,
  double maximum_edge_sharpness_at_vertex
)
{
  // NOTE WELL:
  // For edge chains with a constant sharpness, this agrees with DKT SIGGRAPH 1998.
  // For edge chains with variable sharpness, having a sharpness interval on the
  // edge with end values matching at shared vertices gives nicer looking results
  // than assigning a constant sharpness to edges and Chaikin's subdivision rule
  // (averaging) at vertices.

  if (ON_SubDVertexTag::Corner == vertex_tag)
  {
    // No sharpness bias for corner vertex subdivision.
    // At a corner vertex, all subdivision points and the limit point are equal to the level 0 control net point.
    // Thus, applying a sharp bias doesn't modify the subdivision point or limit point.
    return 0.0;
  }

  unsigned crease_edge_count;
  if (ON_SubDVertexTag::Smooth == vertex_tag)
  {
    crease_edge_count = 0;
  }
  else if (ON_SubDVertexTag::Crease == vertex_tag)
  {
    if (interior_crease_vertex_sharpness > 0.0 && interior_crease_vertex_sharpness <= ON_SubDEdgeSharpness::MaximumValue)
    {
      // In the comments below,
      // VSS = vertex sector sharpness = maximum edges sharpness 
      //       at the vertex's end of all smooth edges in the sector.
      if (sharp_edge_end_count <= 0)
      {
        // No edges have nonzero end sharpness at this vertex
        // It should be the case that the origin of this vertex
        // is an interior crease vertex where:
        // 1) One sector (A) had sharp edges and VSS > 0.
        // 2) The other sector (B) had no sharp edges and VSS = 0.
        // 3) This vertex is part of a single sector B copy (or a subdivision of such a copy).
        return interior_crease_vertex_sharpness;
      }

      if (interior_crease_vertex_sharpness > maximum_edge_sharpness_at_vertex)
      {
        // It should be the case that the origin of this vertex
        // is an interior crease vertex where:
        // 1) Both sectors had sharp edges and the VSS of the sectors was different (one could be zero).
        // 2) This vertex is part of a single sector copy of the sector with 
        //    the smaller VSS (or a subdivision of such a copy).
        return interior_crease_vertex_sharpness;
      }
    }

    crease_edge_count = 2;
  }
  else if (ON_SubDVertexTag::Dart == vertex_tag)
  {
    crease_edge_count = 1;
  }
  else
  {
    ON_SUBD_ERROR("vertex_tag parameter is invalid or unset.");
    return 0.0;
  }

  if (sharp_edge_end_count + crease_edge_count < 2U)
  {
    // No sharp bias for the vertex subdivision point.
    return 0.0;
  }

  return maximum_edge_sharpness_at_vertex;
}

double ON_SubDEdgeSharpness::SharpnessFromNormalizedValue(
  double normalized_slider_value
)
{
  return SharpnessFromSliderValue(
    ON_Interval::ZeroToOne,
    normalized_slider_value,
    ON_DBL_QNAN
  );
}

double ON_SubDEdgeSharpness::SharpnessFromSliderValue(
  ON_Interval slider_domain,
  double slider_value,
  double invalid_input_result
)
{
  if (slider_domain.IsInterval() && slider_value >= slider_domain.Min() && slider_value <= slider_domain.Max())
  {
    if (0.0 == slider_domain[0] && ON_SubDEdgeSharpness::MaximumValue == slider_domain[1])
      return slider_value;
    const double s = (0.0 == slider_domain[0] && 1.0 == slider_domain[1]) ? slider_value : slider_domain.NormalizedParameterAt(slider_value);
    if (s >= 0.0 && s <= 1.0)
    {
      const ON_Interval ZeroToMaximumSharpness(0.0, ON_SubDEdgeSharpness::MaximumValue);
      double sharpness = ON_SubDEdgeSharpness::Sanitize(ZeroToMaximumSharpness.ParameterAt(s), invalid_input_result);
      if (sharpness >= 0.0 && sharpness <= ON_SubDEdgeSharpness::MaximumValue)
        return sharpness;
    }
  }
  return invalid_input_result;
}

unsigned ON_SubDEdgeSharpness::SetEdgeChainSharpness(
  ON_Interval chain_sharpness_range,
  unsigned edge_count,
  ON_SimpleArray<ON_SubDEdgeSharpness>& chain_edge_sharpness
)
{
  if (edge_count <= 0 || edge_count >= ON_UNSET_UINT_INDEX)
    return 0;
  chain_edge_sharpness.Reserve(edge_count);
  chain_edge_sharpness.SetCount(edge_count);
  const unsigned rc = ON_SubDEdgeSharpness::SetEdgeChainSharpness(chain_sharpness_range, edge_count, chain_edge_sharpness.Array());
  if (rc <= 0)
    chain_edge_sharpness.SetCount(0);
  return rc;
}


unsigned ON_SubDEdgeSharpness::SetEdgeChainSharpness(
  ON_Interval chain_sharpness_range,
  unsigned edge_count,
  ON_SubDEdgeSharpness* chain_edge_sharpness
)
{
  if (edge_count <= 0 || edge_count >= ON_UNSET_UINT_INDEX || nullptr == chain_edge_sharpness)
    return 0;

  if (chain_sharpness_range[0] == chain_sharpness_range[1])
  {
    const ON_SubDEdgeSharpness c = ON_SubDEdgeSharpness::FromConstant(chain_sharpness_range[0]);
    if (false == c.IsValid(true))
      return 0;
    for (unsigned i = 0; i < edge_count; ++i)
      chain_edge_sharpness[i] = c;
    return 1;
  }

  if (false == ON_SubDEdgeSharpness::IsValidValue(chain_sharpness_range[0], false))
    return false;
  if (false == ON_SubDEdgeSharpness::IsValidValue(chain_sharpness_range[1], false))
    return false;

  const double d = (double)edge_count;
  ON_Interval r(ON_DBL_QNAN, chain_sharpness_range[0]);
  for (unsigned i = 1; i <= edge_count; ++i)
  {
    r.m_t[0] = r.m_t[1];
    r.m_t[1]
      = (i < edge_count)
      ? chain_sharpness_range.ParameterAt(((double)i / d))
      : chain_sharpness_range[1];
    const ON_SubDEdgeSharpness v = ON_SubDEdgeSharpness::FromInterval(r);
    if (v.IsValid())
    {
      chain_edge_sharpness[i - 1] = v;
      continue;
    }
    return 0;
  }

  return
    (chain_edge_sharpness[0].EndSharpness(0) != chain_edge_sharpness[edge_count - 1].EndSharpness(1))
    ? edge_count
    : 1;
}

bool ON_SubD::HasSharpEdges() const
{
  bool bHasSharpEdges = 0 != (ON_ComponentAttributes::EdgeAttributes::InteriorSharp & this->AggregateEdgeAttributes());
  return bHasSharpEdges;

  //ON_SubDEdgeIterator eit = this->EdgeIterator();
  //for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
  //{
  //  if (e->IsSharp())
  //    return true;
  //}
  //return false;
}

unsigned int ON_SubD::SharpEdgeCount(ON_SubDEdgeSharpness& sharpness_range) const
{
  sharpness_range = ON_SubDEdgeSharpness::Smooth;
  unsigned int sharp_edge_count = 0;
  ON_SubDEdgeIterator eit = this->EdgeIterator();
  for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
  {
    if (e->IsSharp())
    {
      sharpness_range = ON_SubDEdgeSharpness::Union(sharpness_range, e->Sharpness(false));
      ++sharp_edge_count;      
    }
  }
  return sharp_edge_count;
}

unsigned int ON_SubD::SharpEdgeCount() const
{
  ON_SubDEdgeSharpness sharpness_range = ON_SubDEdgeSharpness::Smooth;
  return SharpEdgeCount(sharpness_range);
}

bool ON_SubDVertex::IsSharp( bool bEndCheck ) const
{
  // This definition of vertex sharpness is from DeRose, Kass, Truong 1998
  // If there are exactly two sharp edges adjacent to the vertex, then
  // the vertex sharpness is the average of the edge sharpnesses.
  if (IsSmoothOrDartOrCrease() && nullptr != m_edges)
  {
    for (unsigned short vei = 0; vei < m_edge_count; ++vei)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
      if (nullptr != e && e->IsSharp() )
        return true;
    }
  }
  return false;
}

unsigned int ON_SubD::ClearEdgeSharpness()
{
  unsigned int sharp_edge_count = 0;
  ON_SubDEdgeIterator eit = this->EdgeIterator();
  for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
  {
    if (const_cast<ON_SubDEdge*>(e)->ClearSharpnessForExperts())
    {
      e->ClearSavedSubdivisionPoints(true);
      ++sharp_edge_count;
    }
  }
  
  if (sharp_edge_count != 0)
    this->ChangeGeometryContentSerialNumberForExperts(true);

  return sharp_edge_count;
}


double ON_SubDVertex::Internal_InteriorCreaseVertexSharpnessForExperts() const
{
  // This function cannot check that this->IsInteriorCrease() is true because
  // this function is used on partial subsets of a SubD in low level evaluation code.
  // When a vertex is an interior crease in the complete SubD, these partial
  // SubD include only one of the sectors. Thus, all that can be checked is the
  // crease tag settings
  return (ON_SubDVertexTag::Crease == m_vertex_tag) ? m_interior_crease_vertex_sharpness : 0.0;
}

void ON_SubDVertex::Internal_SetInteriorCreaseVertexSharpnessForExperts(
  double interior_crease_vertex_sharpness,
  bool bSkipEdgeCountTest
) const
{
  // NOTE WELL:
  // This function is used to set m_crease_sector_vertex_sharpness when the vertex is part
  // of a complete SubD.
  if (ON_SubDVertexTag::Crease == m_vertex_tag
    && interior_crease_vertex_sharpness > 0.0
    && ON_SubDEdgeSharpness::IsValidValue(interior_crease_vertex_sharpness, false)
    )
  {
    // nonzero vertex sharpness on a crease vertex.
    // Because, even with the bSingleSectorSubset parameter, it's impossible to know the context 
    // when ON_SubDVertex.VertexSharpness() is called (complete SubD or singel sector subset)
    // we test for a change to the value before setting it so debugger breakpoints can
    // be set and triggered at useful times.
    const float f = (float)interior_crease_vertex_sharpness;
    if (m_edge_count == m_face_count && m_face_count >= 2)
    {
      // This is a 2 sector crease vertex and is exactly
      // the case where m_crease_sector_vertex_sharpness is useful.
      // If the sectors have different maximum edge end sharpnesses at this
      // vertex, then this value is critical. The sector with the smaller
      // maximum edge end sharpness must use this value when the
      // vertex subdivision point is calculated so the subdivision
      // and limit surface point are correct when calculated from
      // either sector.
      this->m_interior_crease_vertex_sharpness = f;
    }
    else
    {
      const bool bOneSector = m_edge_count == m_face_count + 1 && m_face_count >= 1;
      if (bOneSector && m_level > 0)
      {
        // The situation should be that the calling code knows for sure
        // this is a 1 sector crease vertex and that sector is a 
        // subset taken from a 2 sector crease vertex (in low level evaluation code)
        // and interior_crease_vertex_sharpness was calculated using both sectors
        // (or is a subdivision of a value calculated using both sectors).
        // One place this happens is in ON_SubDVertexQuadSector::Subdivide().
        // This is a good location for a breakpoint.
        this->m_interior_crease_vertex_sharpness = f;
      }
      else if (bSkipEdgeCountTest)
      {
        // When bSkipEdgeCountTest = true, the expert caller is stating
        // this is some type of special case when the vertex isn't completely
        // connected the the entire SubD. It is typically at some stage of subdivision
        // where either a the subdivided SubD is under construction or
        // during low level evaluation where a copy of 1 side of a 2 sector crease
        // is being created so limit surface information can be calculated.
        // 
        // Each case is separated out so it's possible to surgically debug with simple breakpoints.
        if (bOneSector)
        {
          // One sector of a level 0 vertex is being copied and the expert caller
          // set bSkipEdgeCountTest=true to inform us this is a special case.
          // One place this happens is in
          // ON_SubDVertexQuadSector::Initialize(ON_SubDVertexTag center_vertex_tag, double center_vertex_sharpness, ...).
          this->m_interior_crease_vertex_sharpness = f;
        }
        else if (0 == m_edge_count && 0 == m_face_count)
        {
          // A vertex is being copied, the edges and faces have not been attached yet,
          // and the expert caller set bSkipEdgeCountTest=true to inform us this is a
          // special case.
          // One place this happens is in
          // ON_SubD_FixedSizeHeap::AllocateVertex(ON_SubDVertex* vertex0,unsigned int edge_capacity)
          // where the subdivision vertex of vertex0 is being created and the edges and faces
          // have not been allocated (and hence not attached) yet.
          // Good place for a breakpoint.
          this->m_interior_crease_vertex_sharpness = f;
        }
        else
        {
          // If you end up here and it's a valid state, add a comment.
          // If it's confusing, please ask Dale Lear for some help.
          ON_ERROR("This probably should not be happening.");
          // Nothing is accomplished by setting this value and 
          // having it set can cause errors when sharpnesses are edited.      
          // Good place for a breakpoint.
          this->Internal_ClearInteriorCreaseVertexSharpnessForExperts();
        }
      }
    }
  }
  else
    this->Internal_ClearInteriorCreaseVertexSharpnessForExperts();
}

void ON_SubDVertex::Internal_ClearInteriorCreaseVertexSharpnessForExperts() const
{
  // NO tests - set m_interior_crease_vertex_sharpness = 0 unconditionally 
  this->m_interior_crease_vertex_sharpness = 0.0f;
}

static double Internal_VertexSharpnessCalculationHelper(
  const ON_SubDVertex* v, // caller insures v is not nullptr
  unsigned int sharp_edge_count, // caller insures sharp_edge_count is valid 
  double max_end_sharpeness // caller insures max_end_sharpness is valid
)
{
  // In low level evaluation code, interior crease vertices
  // only have information from one sector and we need the value
  // calculated from both sectors. In all other cases, the
  // value of max_end_sharpness calculated above is the
  // correct value to use.
  const bool bIsOneSectorCrease = v->IsOneSectorCrease();
  const double two_sector_crease_vertex_sharpness
    = bIsOneSectorCrease
    ? v->Internal_InteriorCreaseVertexSharpnessForExperts()
    : 0.0;
  const double vertex_sharpness = ON_SubDEdgeSharpness::VertexSharpness(v->m_vertex_tag, two_sector_crease_vertex_sharpness, sharp_edge_count, max_end_sharpeness);
  if (false == bIsOneSectorCrease)
  {
    if (vertex_sharpness > 0.0 && v->IsTwoSectorCrease())
    {
      // This interior crease vertex has both sectors present and the value
      // of vertex_sharpness can be saved for future situations where
      // single sector copies are used in low level evaluation code.
      v->Internal_SetInteriorCreaseVertexSharpnessForExperts(vertex_sharpness, false);
    }
    else
      v->Internal_ClearInteriorCreaseVertexSharpnessForExperts();
  }
  // else DO NOTHING - THIS IS IMPORTANT
  // The 1 sector case might be low level code passing in copy of just one of two sectors
  // and, at this point, there is not enough information to determine the correct action.
  return vertex_sharpness;
}

double ON_SubDVertex::VertexSharpness() const
{
  // NOTE WELL:

  // For performance reasons in calculating limit surface meshes,
  // the code in this function does the same calculation and
  // returns the same value as
  //
  //  ON_3dPoint sharp_subdivision_point;
  //  return GetSharpSubdivisionPoint(sharp_subdivision_point);
  //
  //  ALWAYS CHANGE THE CODE IN ON_SubDVertex::GetSharpSubdivisionPoint() first
  //  and then update this function as needed.


  double vertex_sharpness;
  if (this->IsSmoothOrDartOrCrease() && nullptr != m_edges)
  {
    unsigned int sharp_edge_count = 0;
    double max_end_sharpeness = 0.0;

    for (unsigned short vei = 0; vei < m_edge_count; ++vei)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
      if (nullptr == e)
        continue;
      // The edge is has a smooth tag and at leas one end has sharpness > 0.
      // For variable edge sharpness, s can be zero at an end.
      const double s = e->EndSharpness(this);
      if (s > 0.0)
      {
        if (s > max_end_sharpeness)
          max_end_sharpeness = s;
        ++sharp_edge_count;
      }
    }

    vertex_sharpness = Internal_VertexSharpnessCalculationHelper(
      this,
      sharp_edge_count,
      max_end_sharpeness
    );
  }
  else
  {
    vertex_sharpness = 0.0;
  }
  

  // DEBUG TEST to make sure the condition descried in the comment above is satisfied.
  // DO NOT COMMIT THIS CODE - IT IS FOR TESTING WHILE DEVELOPING
  //  ON_3dPoint sharp_subdivision_point;
  //  const double check = GetSharpSubdivisionPoint(sharp_subdivision_point);
  //  if (false == (check == vertex_sharpness))
  //  {
  //#if !defined(ON_DEBUG)
  //#error Read comment above - do not commit this code uncommented.
  //#endif
  //    ON_SUBD_ERROR("The code in \"double ON_SubDVertex::VertexSharpness() const\" is wrong.");
  //  }

  return vertex_sharpness;
}

double ON_SubDVertex::GetSharpSubdivisionPoint(ON_3dPoint& sharp_subdivision_point) const
{
  unsigned count = 0;
  const ON_SubDVertex* v[3] = {};
  double c[3] = {};
  double vs = this->GetSharpSubdivisionPoint(count,v,c);
  if (vs > 0.0 && count > 0U && nullptr != v[0])
  {
    switch (count)
    {
    case 1:
      sharp_subdivision_point = c[0] * v[0]->ControlNetPoint();
      break;
    case 2:
      sharp_subdivision_point 
        = c[0] * v[0]->ControlNetPoint() 
        + c[1] * v[1]->ControlNetPoint();
      break;
    case 3:
      sharp_subdivision_point 
        = c[0] * v[0]->ControlNetPoint() 
        + c[1] * v[1]->ControlNetPoint() 
        + c[2] * v[2]->ControlNetPoint();
      break;
    default:
      vs = 0.0;
      sharp_subdivision_point = ON_3dPoint::NanPoint;
      break;
    }
  }
  else
  {
    vs = 0.0;
    sharp_subdivision_point = ON_3dPoint::NanPoint;
  }
  return vs;
}

double ON_SubDVertex::GetSharpSubdivisionPoint(
  unsigned& count,
  const ON_SubDVertex* v[3],
  double c[3]
) const
{
  // Below "sharp edge" means an edge attached to this vertex that has a smooth tag
  // and a nonzero sharpness at the end attached to this vertex.
  // This definition of vertex sharpness is from DeRose, Kass, Truong 1998.
  // - If the vertex is smooth and adjacent to zero or one sharp edges, 
  //   then the ordinary vertex subdivision rule is used,
  //   sharp_subdivision_point is set to NanPoint,
  //   and 0.0 is returned.
  // - If the vertex is adjacent to 3 or more sharp edges and crease edges, 
  //   then the corner vertex subdivision rule is used,
  //   sharp_subdivision_point = vertex control net point,
  //   and the maximum edge sharpness at the vertex is returned.
  // - If the vertex is adjacent to 2 sharp edges and crease edges, 
  //   then sharp_subdivision_point = crease vertex subdivision point, 
  //   and the average of the edge sharpnesses is returned.
  // 
  // The returned vertex sharpens is always >= 0.
  // When the returned vertex sharpness is > 0, the vertex subdivision point
  // (1-s)*(ordinary subdivision point) + s*sharp_subdivision_point,
  // where s = min(returned vertex sharpness, 1).
  //

  // NOTE WELL:
  // The double returned by ON_SubDVertex::VertexSharpness() must
  // always be identical to the double returned by this function.
  //
  //  ALWAYS CHANGE THE CODE IN ON_SubDVertex::GetSharpSubdivisionPoint() first
  //  and then update ON_SubDVertex::VertexSharpness() as needed.

  count = 0;
  v[0] = v[1] = v[2] = nullptr;
  c[0] = c[1] = c[2] = 0.0;
  if (this->IsSmoothOrDartOrCrease() && nullptr != m_edges)
  {
    unsigned int sharp_edge_count = 0;
    unsigned other_v_count = 0;
    double max_end_sharpeness = 0.0;
    const ON_SubDVertex* other_v[2] = {};

    // NOTE WELL:
    // In low level evaluation code, the edges are only those in the sector
    // being evaluated. See RH-76871 for an example
    for (unsigned short vei = 0; vei < m_edge_count; ++vei)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
      if (nullptr == e)
        continue;
      if (e->IsCrease())
      {
        if (other_v_count < 2)
          other_v[other_v_count] = e->OtherEndVertex(this);
        ++other_v_count;
      }
      else if ( e->IsSharp() )
      {
        // The edge is has a smooth tag and at leas one end has sharpness > 0.
        // For variable edge sharpness, s can be zero at an end.
        const double s = e->EndSharpness(this);
        if (s > 0.0)
        {
          if (other_v_count < 2)
            other_v[other_v_count] = e->OtherEndVertex(this);
          ++other_v_count;
          if (s > max_end_sharpeness)
            max_end_sharpeness = s;
          ++sharp_edge_count;
        }
      }
    }

    const double vertex_sharpness = Internal_VertexSharpnessCalculationHelper(
      this,
      sharp_edge_count,
      max_end_sharpeness
    );


    if (vertex_sharpness > 0.0)
    {      
      if (sharp_edge_count > 0 && 2 == other_v_count && nullptr != other_v[0] && nullptr != other_v[1])
      {
        // 2 creases and sharps - "crease" subdivision point
        c[0] = 0.75; 
        c[1] = 0.125;
        c[2] = 0.125;
        v[0] = this;
        v[1] = other_v[0];
        v[2] = other_v[1];
        count = 3;
      }
      else
      {
        // Use "corner" subdivision point as the sharp contribution.
        // There are two possibilities:
        // 
        // A) (sharp_edge_count > 0 and other_v_count >= 3)
        // At least one sharp edge and a total of 3 or more creases and sharps.
        // 
        // B) (sharp_edge_count = 0, other_v_count = 2, tag = ON_SubDVertexTag::Crease)
        // Two creases an no sharps at an interior crease vertex has sharp edges in one
        // sector and no sharp edges in the other sector and this vertex
        // is the sector center in low level evaluation code that stores only the
        // sector components. See RH-76871 for an example.
        c[0] = 1.0;
        v[0] = this;
        count = 1;
      }
      return vertex_sharpness;
    }
  }
  return 0.0;
}

unsigned int ON_SubDVertex::SharpEdgeCount( 
  bool bCountCreasesAsSharp,
  bool bEndCheck 
) const
{
  ON_Interval sharpness_range;
  return SharpEdgeCount(bCountCreasesAsSharp, bEndCheck, sharpness_range);
}

unsigned int ON_SubDVertex::SharpEdgeCount(
  bool bCountCreasesAsSharp,
  bool bEndCheck,
  ON_Interval& sharpness_range
) const
{
  unsigned int sharp_edge_count = 0;
  double mins = 0.0;
  double maxs = 0.0;
  if (nullptr != m_edges)
  {
    for (unsigned short vei = 0; vei < m_edge_count; ++vei)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
      if (nullptr == e || 2 != e->m_face_count)
        continue;
      if (false == e->IsSharp())
      {
        if (false == bCountCreasesAsSharp || false == e->IsCrease())
          continue;
      }
      const double s = e->IsCrease() ? ON_SubDEdgeSharpness::CreaseValue : e->EndSharpness(this);
      if (false == bEndCheck || s > 0.0)
      {
        if (0 == sharp_edge_count)
        {
          mins = s;
          maxs = s;
        }
        else if (s < mins)
          mins = s;
        else if (s > maxs)
          maxs = s;
        ++sharp_edge_count;
      }
    }
  }
  sharpness_range.Set(mins, maxs);
  return sharp_edge_count;
}

bool ON_SubDEdge::IsSharp() const
{
  return 
    (ON_SubDEdgeTag::Smooth == m_edge_tag || ON_SubDEdgeTag::SmoothX == m_edge_tag)
    && m_sharpness.IsSharp();
}

bool ON_SubDEdge::IsCreaseOrSharp() const
{
  return (ON_SubDEdgeTag::Crease == m_edge_tag || this->IsSharp());
}

bool ON_SubDEdge::IsSmoothNotSharp() const
{
  return
    (ON_SubDEdgeTag::Smooth == m_edge_tag || ON_SubDEdgeTag::SmoothX == m_edge_tag)
    && (false == m_sharpness.IsSharp());
}

bool ON_SubDEdge::IsSmoothNotXNotSharp() const
{
  return ON_SubDEdgeTag::Smooth == m_edge_tag && (false == m_sharpness.IsSharp());
}

double ON_SubDEdge::GetSharpSubdivisionPoint(ON_3dPoint& sharp_subdivision_point) const
{
  if (IsSharp())
  {
    const double s = Sharpness(false).Average();
    sharp_subdivision_point = this->ControlNetCenterPoint();
    return s;
  }

  sharp_subdivision_point = ON_3dPoint::NanPoint;
  return 0.0;
}

bool ON_SubDVertex::IsSingleSectorVertex() const
{
  const bool bIsCreaseOrCorner = IsCreaseOrCorner();
  if (bIsCreaseOrCorner)
  {
    if (m_face_count < 1 || m_face_count + 1 != m_edge_count)
      return false;
  }
  else if (IsSmoothOrDart())
  {
    if (m_face_count < 2 || m_edge_count!= m_face_count)
      return false;
  }
  else
    return false;


  unsigned short boundary_crease_count = 0;
  unsigned short interior_crease_count = 0;
  unsigned short interior_smooth_count = 0;
  for (unsigned short vei = 0; vei < m_edge_count; ++vei)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(this->m_edges[vei].m_ptr);
    if (nullptr == e)
      return false;

    if (e->IsSmooth())
    {
      if (2 == e->m_face_count)
      {
        ++interior_smooth_count;
        continue;
      }
    }
    else if (ON_SubDEdgeTag::Crease == e->m_edge_tag)
    {
      if (2 == e->m_face_count)
      {
        ++interior_crease_count;
        if (ON_SubDVertexTag::Dart == m_vertex_tag && 1 == interior_crease_count)
          continue;
      }
      else if (1 == e->m_face_count)
      {
        ++boundary_crease_count;
        if (bIsCreaseOrCorner && boundary_crease_count <= 2)
          continue;
      }
    }

    return false;
  }

  if (bIsCreaseOrCorner)
  {
    if (2 == boundary_crease_count && 2+interior_smooth_count == m_edge_count)
      return true;
  }
  else if (ON_SubDVertexTag::Dart == m_vertex_tag)
  {
    if (1 == interior_crease_count && 1+interior_smooth_count == m_edge_count)
      return true;
  }
  else if (ON_SubDVertexTag::Smooth == m_vertex_tag)
  {
    if (interior_smooth_count == m_edge_count)
      return true;
  }

  return false;
}

bool ON_SubDVertex::IsManifoldBoundaryVertex() const
{
  return IsCreaseOrCorner() && IsSingleSectorVertex();
}


bool ON_SubDVertex::HasInteriorVertexTopology() const
{
  if (m_edge_count >= 2 && m_edge_count == m_face_count && nullptr != m_edges && nullptr != m_faces)
  {
    for (unsigned short vei = 0; vei < m_edge_count; ++vei)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
      if (nullptr == e || 2 != e->m_face_count)
        return false;
    }
    return true;
  }    
  return false;
}

bool ON_SubDVertex::HasBoundaryVertexTopology() const
{
  if (m_edge_count >= 2 && m_edge_count == m_face_count+1 && nullptr != m_edges && nullptr != m_faces)
  {
    unsigned boundary_count = 0;
    for (unsigned short vei = 0; vei < m_edge_count; ++vei)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
      if (nullptr == e || 0 == e->m_face_count || e->m_face_count > 2)
        return false;
      if (1 == e->m_face_count)
        ++boundary_count;
    }
    if (2 == boundary_count)
      return true;
  }    
  return false;
}

const ON_SubDComponentPtrPair ON_SubDVertex::BoundaryEdgePair() const
{
  ON_SubDComponentPtrPair epair = ON_SubDComponentPtrPair::Null;
  if (nullptr != m_edges && m_edge_count >= 2)
  {
    for (unsigned short vei = 0; vei < m_edge_count; ++vei)
    {
      ON_SubDEdgePtr eptr = m_edges[vei];
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
      if (nullptr == e)
        continue;
      if (false == e->HasBoundaryEdgeTopology())
        continue;
      const ON__UINT_PTR edir = ON_SUBD_EDGE_DIRECTION(eptr.m_ptr);
      if (this != e->m_vertex[edir])
      {
        // m_edges[vei] is corrupt ...
        ON_SUBD_ERROR("m_edges[vei] has incorrect edge orientation flag.");
        if (this == e->m_vertex[1 - edir])
          eptr = eptr.Reversed(); // we can still return the requested information.
        else
          return ON_SubDComponentPtrPair::Null;
      }
      if (epair.m_pair[0].IsNull())
        epair.m_pair[0] = ON_SubDComponentPtr::Create(eptr);
      else if (epair.m_pair[1].IsNull())
        epair.m_pair[1] = ON_SubDComponentPtr::Create(eptr);
      else
        return ON_SubDComponentPtrPair::Null; // 3 or more boundary edges
    }
  }
  return (epair.m_pair[1].IsNotNull()) ? epair : ON_SubDComponentPtrPair::Null;
}

const ON_SubDComponentPtrPair ON_SubDVertex::CreasedEdgePair(bool bInteriorEdgesOnly) const
{
  ON_SubDComponentPtrPair creased_eptr_pair = ON_SubDComponentPtrPair::Null;
  if (nullptr != m_edges && m_edge_count >= 2)
  {
    for (unsigned short vei = 0; vei < m_edge_count; ++vei)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
      if (nullptr == e)
        continue;
      if (bInteriorEdgesOnly && false == e->HasInteriorEdgeTopology(false))
        continue;
      if (ON_SubDEdgeTag::Crease == e->m_edge_tag)
      {
        if (e == ON_SUBD_EDGE_POINTER(creased_eptr_pair.m_pair[0].m_ptr) || e == ON_SUBD_EDGE_POINTER(creased_eptr_pair.m_pair[1].m_ptr))
        {
          ON_SUBD_ERROR("Duplicate entries in m_edges[] list.");
          continue;
        }
        if (creased_eptr_pair.FirstIsNull())
          creased_eptr_pair.m_pair[0] = ON_SubDComponentPtr::Create(m_edges[vei]);
        else if (creased_eptr_pair.SecondIsNull())
          creased_eptr_pair.m_pair[1] = ON_SubDComponentPtr::Create(m_edges[vei]);
        else
          return ON_SubDComponentPtrPair::Null; // 3 or more creases
      }
    }
  }
  return creased_eptr_pair.SecondIsNull() ? ON_SubDComponentPtrPair::Null : creased_eptr_pair;
}

const ON_SubDEdgePtr ON_SubDVertex::CreasedEdge(bool bInteriorEdgesOnly) const
{
  ON_SubDEdgePtr creased_eptr = ON_SubDEdgePtr::Null;
  if (nullptr != m_edges)
  {
    for (unsigned short vei = 0; vei < m_edge_count; ++vei)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
      if (nullptr == e)
        continue;
      if (bInteriorEdgesOnly && false == e->HasInteriorEdgeTopology(false))
        continue;
      if (ON_SubDEdgeTag::Crease == e->m_edge_tag)
      {
        if (creased_eptr.IsNull())
          creased_eptr = m_edges[vei];
        else
          return ON_SubDEdgePtr::Null; // 2 or more creases.
      }
    }
  }
  return creased_eptr;
}

const unsigned int ON_SubDVertex::CreasedEdgeCount() const
{
  return  CreasedEdgeCount(true, true, true, true);
}

const unsigned int ON_SubDVertex::CreasedEdgeCount(
  bool bCountInteriorCreases, 
  bool bCountBoundaryCreases, 
  bool bCountNonmanifoldCreases,
  bool bCountWireCreases
) const
{
  unsigned creased_edge_count = 0;
  for (unsigned short vei = 0; vei < m_edge_count; ++vei)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
    if (nullptr == e)
      continue;
    if (ON_SubDEdgeTag::Crease != e->m_edge_tag)
      continue;
    switch (e->m_face_count)
    {
    case 0:
      if (bCountWireCreases)
        ++creased_edge_count;
      break;
    case 1:
      if (bCountBoundaryCreases)
        ++creased_edge_count;
      break;
    case 2:
      if (bCountInteriorCreases)
        ++creased_edge_count;
      break;
    default:
      if (bCountNonmanifoldCreases)
        ++creased_edge_count;
      break;
    }
  }
  return creased_edge_count;
}

bool ON_SubDVertexEdgeProperties::HasInteriorVertexTopology() const
{
  return 
    m_null_edge_count == 0
    && m_edge_count == m_face_count
    && m_boundary_edge_count == 0
    && m_interior_edge_count >= 2
    && m_nonmanifold_edge_count == 0
    ;
}

bool ON_SubDVertexEdgeProperties::HasBoundaryVertexTopology() const
{
  return
    m_null_edge_count == 0
    && m_edge_count == m_face_count+1
    && m_boundary_edge_count == 2
    && m_nonmanifold_edge_count == 0
    ;
}

bool ON_SubDVertexEdgeProperties::HasManifoldVertexTopology() const
{
  return HasInteriorVertexTopology() || HasBoundaryVertexTopology();
}

bool ON_SubDVertexEdgeProperties::HasNonmanifoldVertexTopology() const
{
  return  
    (m_null_edge_count == 0)
    && (m_wire_edge_count > 0 || m_nonmanifold_edge_count > 0)
    ;
}

bool ON_SubDVertex::IsStandard() const
{
  if (nullptr == m_edges)
    return false;

  if (nullptr == m_faces)
    return false;

  const unsigned int edge_count = m_edge_count;
  if (!ON_SubD::IsValidSectorEdgeCount(m_vertex_tag,edge_count))
    return false;

  const unsigned int face_count = m_face_count;
  if (face_count != ON_SubDSectorType::SectorFaceCountFromEdgeCount(m_vertex_tag, edge_count))
    return false;

  const unsigned short f_edge_count = 4;

  unsigned int crease_edge_face_count = ON_UNSET_UINT_INDEX;
  bool bTaggedVertex = false;
  switch (m_vertex_tag)
  {
  case ON_SubDVertexTag::Unset:
    return false;
    break;

  case ON_SubDVertexTag::Smooth:
    if (edge_count != face_count)
      return false;
    break;

  case ON_SubDVertexTag::Crease:
    if (edge_count != face_count+1)
      return false;
    crease_edge_face_count = 1;
    bTaggedVertex = true;
    break;

  case ON_SubDVertexTag::Corner:
    if (edge_count != face_count+1)
      return false;
    crease_edge_face_count = 1;
    bTaggedVertex = true;
    break;

  case ON_SubDVertexTag::Dart:
    if (edge_count != face_count)
      return false;
    crease_edge_face_count = 2;
    bTaggedVertex = true;
    break;

  default:
    return false;
    break;
  }
  

  for (unsigned int vfi = 0; vfi < face_count; vfi++)
  {
    const ON_SubDFace* f = m_faces[vfi];
    if (nullptr == f)
      return false;
    if (f_edge_count != f->m_edge_count)
      return false;
  }

  unsigned int creased_edge_count = 0;
  double sector_coefficient = 0.0;
  for (unsigned int vei = 0; vei < edge_count; vei++)
  {
    const ON_SubDEdge* e = m_edges[vei].Edge();
    if (nullptr == e)
      return false;

    unsigned int evi;
    if (this == e->m_vertex[0])
      evi = 0;
    else if (this == e->m_vertex[1])
      evi = 1;
    else
      return false;

    const ON_SubDVertex* other_vertex = e->m_vertex[1-evi];

    if (nullptr == other_vertex)
      return false;

    if (ON_SubDEdgeTag::Smooth == e->m_edge_tag)
    {
      if (2 != e->m_face_count)
        return false;

      if (bTaggedVertex && 0 == vei)
      {
        sector_coefficient = e->m_sector_coefficient[evi];
        if (!(0.0 <= sector_coefficient && sector_coefficient <= 1.0))
          return false;
      }
      
      if (!(sector_coefficient == e->m_sector_coefficient[evi]))
        return false;

      if (ON_SubDVertexTag::Smooth == other_vertex->m_vertex_tag)
      {
        if ( !(0.0 == e->m_sector_coefficient[1-evi]) )
          return false;
      }
      else
      {
        if ( bTaggedVertex )
          return false;
        if ( !(0.5 == e->m_sector_coefficient[1-evi]) )
          return false;
      }
    }
    else if (ON_SubDEdgeTag::Crease == e->m_edge_tag)
    {
      if (crease_edge_face_count != e->m_face_count)
        return false;
      creased_edge_count++;
      if (creased_edge_count > 2)
        return false;
      if (false == other_vertex->IsDartOrCreaseOrCorner())
        return false;
    }
    else
    {
      return false;
    }
  }

  switch (creased_edge_count)
  {
  case 0:
    if (false == IsSmooth())
      return false;
    break;
  case 1:
    if (false == IsDart())
      return false;
    break;
  case 2:
    if (false == IsCreaseOrCorner())
      return false;
    break;
  default:
    return false;
  }

  // The standard subdivision matrix will correctly calculate
  // the subdivision location for this vertex.
  return true;
}


unsigned int ON_SubDEdge::EdgeAttributes() const
{
  unsigned int edge_topology_attributes = 0U;

  if (nullptr == m_vertex[0] || nullptr == m_vertex[1])
  {
    edge_topology_attributes |= ON_ComponentAttributes::Damaged;
  }
  else
  {
    const double* P[2] = { m_vertex[0]->m_P, m_vertex[1]->m_P };
    if (
      fabs(P[0][0]) < ON_UNSET_POSITIVE_VALUE
      && fabs(P[0][1]) < ON_UNSET_POSITIVE_VALUE
      && fabs(P[0][2]) < ON_UNSET_POSITIVE_VALUE
      && fabs(P[1][0]) < ON_UNSET_POSITIVE_VALUE
      && fabs(P[1][1]) < ON_UNSET_POSITIVE_VALUE
      && fabs(P[1][2]) < ON_UNSET_POSITIVE_VALUE
      )
    {
      if (P[0][0] == P[1][0] && P[0][1] == P[1][1] && P[0][2] == P[1][2])
        edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::ZeroLength;
      else
        edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::NonzeroLength;
    }
    if (m_vertex[0] != m_vertex[1])
      edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::Open;
    else
      edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::Closed;
  }
  
  const ON_SubDFace* f[2] = { ON_SUBD_FACE_POINTER(m_face2[0].m_ptr),ON_SUBD_FACE_POINTER(m_face2[1].m_ptr) };
  switch (m_face_count)
  {
  case 0:
    edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::Wire;
    break;

  case 1:
    edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::Boundary;
    if ( nullptr == f[0])
      edge_topology_attributes |= ON_ComponentAttributes::Damaged;
    break;

  case 2:
    edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::Interior;

    if (IsSmooth())
    {
      edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::InteriorSmooth;
      if ( IsSharp() )
        edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::InteriorSharp;
    }
    else if (IsCrease())
      edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::InteriorCrease;

    if (nullptr != f[0] && nullptr != f[1])
    {
      if (ON_SUBD_FACE_DIRECTION(m_face2[0].m_ptr) == ON_SUBD_FACE_DIRECTION(m_face2[1].m_ptr))
        edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::InteriorNotOriented;
      else
        edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::InteriorOriented;
      if (f[0] != f[1])
      {
        edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::InteriorTwoFaced;
      }
      else
      {
        const unsigned int fecount = f[0]->EdgeCount();
        const unsigned int fei0 = f[0]->EdgeArrayIndex(this);
        if (fecount > 2 && fei0 < fecount)
        {
          for (unsigned int fei1 = fei0 + 1; fei1 < fecount; ++fei1)
          {
            if (this == f[0]->Edge(fei1))
            {
              if (f[0]->EdgeDirection(fei0) != f[0]->EdgeDirection(fei1))
              {
                if ( fei1+1 == fei0 || (0 == fei0 && fei1+1 == fecount))
                  edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::InteriorSlit;
                else
                  edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::InteriorSeam;
              }
              break;
            }
          }
        }
      }
    }
    else
    {
      edge_topology_attributes |= ON_ComponentAttributes::Damaged;
    }
    break;

  default:
    edge_topology_attributes |= ON_ComponentAttributes::EdgeAttributes::Nonmanifold;
    if ( nullptr == f[0] || nullptr == f[1] || nullptr == m_facex )
      edge_topology_attributes |= ON_ComponentAttributes::Damaged;
    break;
  }

  return edge_topology_attributes;
}

static int Compare_ON__UINT_PTR(const void* a, const void* b)
{
  ON__UINT_PTR ai = *((const unsigned int*)a);
  ON__UINT_PTR bi = *((const unsigned int*)b);
  if (ai < bi)
    return -1;
  if (ai > bi)
    return 1;
  return 0;
}

static int ComparePointerArrays(
  size_t count,
  const ON__UINT_PTR* a,
  const ON__UINT_PTR* b
  )
{
  if (count <= 0)
    return 0;
  if (nullptr == a)
    return ((nullptr == b) ? 0 : -1);
  if (nullptr == b)
    return 1;
  if (1 == count)
    return Compare_ON__UINT_PTR(a, b);

  unsigned int stack_buffer[128];
  unsigned int* adex
    = (2 * count <= sizeof(stack_buffer) / sizeof(stack_buffer[0]))
    ? stack_buffer
    : new (std::nothrow) unsigned int[2 * count];  
  if (nullptr == adex)
    return 0;
  
  unsigned int* bdex = adex + count;
  ON_Sort(ON::sort_algorithm::quick_sort, adex, a, count, sizeof(a[0]), Compare_ON__UINT_PTR);
  ON_Sort(ON::sort_algorithm::quick_sort, bdex, b, count, sizeof(b[0]), Compare_ON__UINT_PTR);
  
  int rc = 0;
  for (unsigned int i = 0; 0 == rc && i < count; i++)
  {
    rc = Compare_ON__UINT_PTR(a + adex[i], b + bdex[i]);
  }

  if (adex != stack_buffer)
    delete[] adex;

  return rc;
}

int ON_SubDVertex::CompareUnorderedEdges(
  const ON_SubDVertex* a,
  const ON_SubDVertex* b
  )
{
  if (nullptr == a)
    return ((nullptr == b) ? 0 : -1);
  if (nullptr == b)
    return 1;

  if (a->m_edge_count < b->m_edge_count)
    return -1;
  if (a->m_edge_count > b->m_edge_count)
    return 1;
  return ComparePointerArrays(a->m_edge_count, (const ON__UINT_PTR*)a->m_edges, (const ON__UINT_PTR*)b->m_edges);
}

int ON_SubDVertex::CompareUnorderedFaces(
  const ON_SubDVertex* a,
  const ON_SubDVertex* b
  )
{
  if (nullptr == a)
    return ((nullptr == b) ? 0 : -1);
  if (nullptr == b)
    return 1;

  if (a->m_face_count < b->m_face_count)
    return -1;
  if (a->m_face_count > b->m_face_count)
    return 1;
  return ComparePointerArrays(a->m_face_count, (const ON__UINT_PTR*)a->m_faces, (const ON__UINT_PTR*)b->m_faces);
}

int ON_SubDVertex::CompareUnorderedEdgesAndFaces(
  const ON_SubDVertex* a,
  const ON_SubDVertex* b
  )
{
  int rc = CompareUnorderedEdges(a, b);
  if (0 == rc)
    rc = CompareUnorderedFaces(a, b);
  return rc;
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDEdge
//

void ON_SubDComponentBase::CopyBaseFrom(
  const ON_SubDComponentBase* src,
  bool bCopySymmetrySetNext
  )
{
  if ( nullptr == src )
    src = &ON_SubDComponentBase::Unset;

  *this = *src;
  m_subd_point1 = nullptr;
  Internal_ClearSurfacePointFlag();
  if (bCopySymmetrySetNext)
    m_symmetry_set_next = src->m_symmetry_set_next;
}

void ON_SubDEdge::CopyFrom(
  const ON_SubDEdge* src,
  bool bReverseEdge,
  bool bCopyVertexArray,
  bool bCopyFaceArray,
  bool bCopySymmetrySetNext
)
{
  if (nullptr == src)
    src = &ON_SubDEdge::Empty;

  CopyBaseFrom(src, bCopySymmetrySetNext);

  m_next_edge = nullptr;
  
  m_edge_tag = src->m_edge_tag;

  m_sharpness = src->m_sharpness;

  unsigned int end0 = bReverseEdge ? 1 : 0;

  if (bCopyVertexArray)
  {
    m_vertex[0] = src->m_vertex[end0];
    m_vertex[1] = src->m_vertex[1 - end0];
  }

  m_sector_coefficient[0] = src->m_sector_coefficient[end0];
  m_sector_coefficient[1] = src->m_sector_coefficient[1 - end0];

  if (bCopyFaceArray)
  {
    if (src->m_face_count > 0 && (src->m_face_count <= 2 || (nullptr != src->m_facex && nullptr != m_facex)))
    {
      m_face2[0] = src->m_face2[0];
      m_face2[1] = src->m_face2[1];
      unsigned int face_count = src->m_face_count;
      if (face_count > 2)
      {
        face_count -= 2;
        for (unsigned int efi = 0; efi < face_count; efi++)
          m_facex[efi] = src->m_facex[efi];
      }
      m_face_count = src->m_face_count;
    }
    else
      m_face_count = 0;
  }
}

unsigned int ON_SubDEdge::TaggedEndIndex() const
{
  unsigned int tagged_end_index = 3;
  for (unsigned int evi = 0; evi < 2; evi++)
  {
    const ON_SubDVertex* v = m_vertex[evi];
    if (nullptr == v || false == v->IsDartOrCreaseOrCorner())
      continue;
    tagged_end_index = (3 == tagged_end_index) ? evi : 2;
  }
  return tagged_end_index;
}

const ON_SubDFacePtr ON_SubDEdge::FacePtr(
  unsigned int i
  ) const
{
  return (i < 2) ? m_face2[i] : ((i < m_face_count) ? m_facex[i - 2] : ON_SubDFacePtr::Null);
  //return (i < m_face_count) ? ((i < 2) ? m_face2[i] : m_facex[i - 2]) : ON_SubDFacePtr::Null;
}

unsigned ON_SubDEdge::VertexCount() const
{
  return 
    (nullptr != m_vertex[0]) 
    ? ((nullptr != m_vertex[1] && m_vertex[0] != m_vertex[1]) ? 2U : 1U)
    : ((nullptr != m_vertex[1] ? 1U : 0U))
    ;
}

unsigned int ON_SubDEdge::VertexId(
  unsigned evi
) const
{
  const ON_SubDVertex* v = Vertex(evi);
  return (nullptr != v) ? v->m_id : 0U;
}

const ON_SubDVertex* ON_SubDEdge::Vertex(
  unsigned evi
) const
{
  return (evi >= 0 && evi <= 1) ? m_vertex[evi] : nullptr;
}


unsigned int ON_SubDEdge::FaceCount() const
{
  return m_face_count;
}

ON_SubDEdgeType ON_SubDEdge::EdgeType() const
{
  if (0 == m_face_count)
  {
    if (ON_SubDEdgeTag::Crease == m_edge_tag)
      return ON_SubDEdgeType::Wire;
  }
  else if (1 == m_face_count)
  {
    if (ON_SubDEdgeTag::Crease == m_edge_tag)
      return ON_SubDEdgeType::Boundary;
  }
  else if (2 == m_face_count)
  {
    if (ON_SubDEdgeTag::Crease == m_edge_tag)
      return ON_SubDEdgeType::InteriorCrease;
    
    if (ON_SubDEdgeTag::Smooth == m_edge_tag || ON_SubDEdgeTag::SmoothX == m_edge_tag)
    {
      if (this->m_sharpness.IsZero())
        return ON_SubDEdgeType::InteriorSmooth;
      if (this->m_sharpness.IsSharp())
        return ON_SubDEdgeType::InteriorSharp;
    }
  }
  else if (m_face_count <= ON_SubDEdge::MaximumFaceCount)
  {
    if (ON_SubDEdgeTag::Crease == m_edge_tag)
      return ON_SubDEdgeType::Nonmanifold;
  }

  return ON_SubDEdgeType::Invalid;
};

ON_SubDEdgeType ON_SubDEdgePtr::EdgeType() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->EdgeType() : ON_SubDEdgeType::Unset;
}

bool ON_SubDEdge::HasBoundaryEdgeTopology() const
{
  for (;;)
  {
    if (1 != m_face_count)
      break;
    const ON_SubDFace* f = ON_SUBD_FACE_POINTER(m_face2[0].m_ptr);
    if (nullptr == f)
      break;
    const ON_SubDEdgePtr feptr = f->EdgePtrFromEdge(this);
    if (this != ON_SUBD_EDGE_POINTER(feptr.m_ptr))
    {
      ON_SUBD_ERROR("m_face2[0] does not reference this edge.");
      break;
    }
    if (ON_SUBD_FACE_DIRECTION(m_face2[0].m_ptr) != ON_SUBD_FACE_DIRECTION(feptr.m_ptr))
    {
      ON_SUBD_ERROR("m_face2[0] has inconsistent direction flags.");
      break;
    }
    if (nullptr == m_vertex[0] || nullptr == m_vertex[1] || m_vertex[0] == m_vertex[1])
    {
      ON_SUBD_ERROR("m_vertex[] has null or invalid pointers.");
      break;
    }
    return true;
  }
  return false;
}

bool ON_SubDEdge::HasInteriorEdgeTopology(bool bRequireOppositeFaceDirections) const
{
  for (;;)
  {
    if (2 != m_face_count)
      break;
    if (bRequireOppositeFaceDirections && ON_SUBD_FACE_DIRECTION(m_face2[0].m_ptr) == ON_SUBD_FACE_DIRECTION(m_face2[1].m_ptr))
      break;
    const ON_SubDFace* f[2] = { ON_SUBD_FACE_POINTER(m_face2[0].m_ptr), ON_SUBD_FACE_POINTER(m_face2[1].m_ptr) };
    if ( nullptr == f[0] || nullptr == f[1] || f[0] == f[1])
      break;
    const ON_SubDEdgePtr feptr[2] = { f[0]->EdgePtrFromEdge(this), f[1]->EdgePtrFromEdge(this) };
    if (this != ON_SUBD_EDGE_POINTER(feptr[0].m_ptr))
    {
      ON_SUBD_ERROR("m_face2[0] does not reference this edge.");
      break;
    }
    if (ON_SUBD_FACE_DIRECTION(feptr[0].m_ptr) != ON_SUBD_FACE_DIRECTION(m_face2[0].m_ptr))
    {
      ON_SUBD_ERROR("m_face2[0] has inconsistent direction flags.");
      break;
    }
    if (this != ON_SUBD_EDGE_POINTER(feptr[1].m_ptr))
    {
      ON_SUBD_ERROR("m_face2[1] does not reference this edge.");
      break;
    }
    if (ON_SUBD_FACE_DIRECTION(feptr[1].m_ptr) != ON_SUBD_FACE_DIRECTION(m_face2[1].m_ptr))
    {
      ON_SUBD_ERROR("m_face2[1] has inconsistent direction flags.");
      break;
    }
    if (nullptr == m_vertex[0] || nullptr == m_vertex[1] || m_vertex[0] == m_vertex[1])
    {
      ON_SUBD_ERROR("m_vertex[] has null or invalid pointers.");
      break;
    }
    return true;
  }
  return false;
}

const class ON_SubDFace* ON_SubDEdge::Face(
  unsigned int i
  ) const
{
  return (i < 2) ? ON_SUBD_FACE_POINTER(m_face2[i].m_ptr) : ((i < m_face_count) ? ON_SUBD_FACE_POINTER(m_facex[i - 2].m_ptr) : nullptr);
}

ON__UINT_PTR ON_SubDEdge::FaceDirection(
  unsigned int i
  ) const
{
  return (i < 2) ? ON_SUBD_FACE_DIRECTION(m_face2[i].m_ptr) : ((i < m_face_count) ? ON_SUBD_FACE_DIRECTION(m_facex[i - 2].m_ptr) : 0);
}

const ON_SubDFacePtr ON_SubDEdge::FacePtrFromFace(
  const class ON_SubDFace* f
) const
{
  if (nullptr != f)
  {
    const ON_SubDFacePtr* fptr = m_face2;
    const unsigned int edge_face_count = m_face_count;
    for (unsigned int efi = 0; efi < edge_face_count; efi++, fptr++)
    {
      if (2 == efi)
      {
        fptr = m_facex;
        if (nullptr == fptr)
          break;
      }
      if (fptr->Face() == f)
        return *fptr;
    }
  }
  return ON_SubDFacePtr::Null;
}


unsigned int ON_SubDEdge::FaceArrayIndex(
  const ON_SubDFace* f
  ) const
{
  if (nullptr == f)
    return ON_UNSET_UINT_INDEX;
  const unsigned int face_count = m_face_count;
  if (face_count > 0)
  {
    if (f == ON_SUBD_FACE_POINTER(m_face2[0].m_ptr))
      return 0;
    if (face_count > 1)
    {
      if (f == ON_SUBD_FACE_POINTER(m_face2[1].m_ptr))
        return 1;
      if (face_count > 2 && nullptr != m_facex)
      {
        const ON_SubDFacePtr* fptr = m_facex - 2;
        for (unsigned int efi = 2; efi < face_count; efi++)
        {
          if (f == ON_SUBD_FACE_POINTER(fptr[efi].m_ptr))
            return efi;
        }
      }
    }
  }
  return ON_UNSET_UINT_INDEX;
}

unsigned int ON_SubDEdge::ReplaceFaceInArray(const ON_SubDFace * old_face, const ON_SubDFace * new_face)
{
  unsigned efi = (nullptr != old_face && old_face != new_face) ? FaceArrayIndex(old_face) : ON_UNSET_UINT_INDEX;
  if (ON_UNSET_UINT_INDEX == efi)
    return ON_UNSET_UINT_INDEX;
  ON_SubDFacePtr* fptr = (efi < 2) ? &m_face2[efi] : &m_facex[efi - 2];
  if (nullptr != new_face)
  {
    *fptr = ON_SubDFacePtr::Create(new_face, fptr->FaceDirection());
  }
  else
  {    
    unsigned efi1 = efi + 1;
    ON_SubDFacePtr* fptr1 = (efi1 < 2) ? &m_face2[efi1] : &m_facex[efi1 - 2];
    for (const unsigned c = (unsigned)(m_face_count--); efi1 < c; ++efi, ++efi1)
    {
      if (2 == efi)
        fptr = m_facex;
      else if (2 == efi1)
        fptr1 = m_facex;
      *fptr++ = *fptr1++;
    }
  }
  return efi;
}



unsigned int ON_SubDEdge::VertexArrayIndex(const ON_SubDVertex * v) const
{
  if (nullptr == v || m_vertex[0] == m_vertex[1])
    return ON_UNSET_UINT_INDEX;
  if (v == m_vertex[0])
    return 0;
  if (v == m_vertex[1])
    return 1;
  return ON_UNSET_UINT_INDEX;
}

const ON_SubDFace* ON_SubDEdgePtr::NeighborFace(
  const ON_SubDFace* face,
  bool bStopAtCrease
) const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->NeighborFace(face, bStopAtCrease) : nullptr;
}

const ON_SubDFace* ON_SubDEdge::NeighborFace(
  const ON_SubDFace* face,
    bool bStopAtCrease
  ) const
{
  if ( nullptr == face || 2 != m_face_count )
    return nullptr;
  // Do not stop at x tags
  if (bStopAtCrease && ON_SubDEdgeTag::Crease == m_edge_tag)
    return nullptr;
  const ON_SubDFace* f[2] = { ON_SUBD_FACE_POINTER(m_face2[0].m_ptr), ON_SUBD_FACE_POINTER(m_face2[1].m_ptr) };
  if (nullptr == f[0] || nullptr == f[1] )
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (face == f[0])
  {
    if (face == f[1] )
      return ON_SUBD_RETURN_ERROR(nullptr);
    return f[1];
  }
  if (face == f[1])
  {
    return f[0];
  }
  return ON_SUBD_RETURN_ERROR(nullptr);
}

const ON_SubDFacePtr ON_SubDEdge::NeighborFacePtr(
  const ON_SubDFace* face,
    bool bStopAtCrease
  ) const
{
  if ( nullptr == face || 2 != m_face_count )
    return ON_SubDFacePtr::Null;
  // Do not stop at x tags
  if (bStopAtCrease && ON_SubDEdgeTag::Crease == m_edge_tag)
    return ON_SubDFacePtr::Null;
  const ON_SubDFace* f[2] = { ON_SUBD_FACE_POINTER(m_face2[0].m_ptr), ON_SUBD_FACE_POINTER(m_face2[1].m_ptr) };
  if (nullptr == f[0] || nullptr == f[1] )
    return ON_SUBD_RETURN_ERROR(ON_SubDFacePtr::Null);
  if (face == f[0])
  {
    if (face == f[1] )
      return ON_SUBD_RETURN_ERROR(ON_SubDFacePtr::Null);
    return m_face2[1];
  }
  if (face == f[1])
  {
    return m_face2[0];
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDFacePtr::Null);
}

const ON_SubDEdgePtr ON_SubDEdge::AdjacentEdgePtr(
  unsigned int edge_vertex_index,
  unsigned int i
) const
{
  if ( edge_vertex_index >= 2 )
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  const ON_SubDFacePtr fptr = FacePtr(i);
  const ON_SubDFace* f = ON_SUBD_FACE_POINTER(fptr.m_ptr);
  if (nullptr == f)
    return ON_SubDEdgePtr::Null;
  const unsigned int fe_count = f->m_edge_count;
  if ( fe_count < 3 || fe_count > ON_SubDFace::MaximumEdgeCount)
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  const unsigned int fei = f->EdgeArrayIndex(this);
  if( fei >= fe_count)
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  const ON_SubDEdgePtr eptr = f->EdgePtr(fei);
  if ( this != ON_SUBD_EDGE_POINTER(eptr.m_ptr))
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  const ON__UINT_PTR dir = ON_SUBD_FACE_DIRECTION(fptr.m_ptr);
  if (dir != ON_SUBD_EDGE_DIRECTION(eptr.m_ptr))
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  const unsigned int fei1
    = (dir == ((ON__UINT_PTR)edge_vertex_index))
    ? ((fei + fe_count - 1) % fe_count)
    : ((fei + 1) % fe_count)
    ;
  return f->EdgePtr(fei1);
}

const ON_SubDEdge* ON_SubDEdge::AdjacentEdge(
  unsigned int edge_vertex_index,
  unsigned int i
  ) const
{
  return ON_SUBD_EDGE_POINTER(AdjacentEdgePtr(edge_vertex_index, i).m_ptr);
}

const ON_SubDVertex* ON_SubDEdge::OtherEndVertex(
  const ON_SubDVertex* vertex
  ) const
{
  if (nullptr != vertex)
  {
    if (m_vertex[0] == vertex)
    {
      if (m_vertex[1] != vertex )
        return m_vertex[1];
    }
    else if (m_vertex[1] == vertex )
      return m_vertex[0];
  }
  return nullptr;
}

const ON_SubDEdgePtr ON_SubDEdge::FromVertices(
  const ON_SubDVertex* vertex0,
  const ON_SubDVertex* vertex1
)
{
  if (nullptr != vertex0 && nullptr != vertex1 && vertex0 != vertex1 && nullptr != vertex0->m_edges)
  {
    for (unsigned short vei = 0; vei < vertex0->m_edge_count; vei++)
    {
      const ON_SubDEdgePtr eptr = vertex0->m_edges[vei];
      if (vertex1 == eptr.RelativeVertex(1) && vertex0 == eptr.RelativeVertex(0))
        return eptr;
    }
  }
  return ON_SubDEdgePtr::Null;
}

const ON_SubDEdge* ON_SubDEdge::FromVertices(
  const ON_SubDVertex* vertex0,
  const ON_SubDVertex* vertex1,
  bool bIgnoreOrientation
)
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(ON_SubDEdge::FromVertices(vertex0, vertex1).m_ptr);
  if ( nullptr != e && false == bIgnoreOrientation && vertex0 != e->m_vertex[0] )
    e = nullptr;
  return e;
}

const ON_SubDFacePtr ON_SubDFace::FromVertices(const ON_SimpleArray< const ON_SubDVertex* >& vertex_list)
{
  return ON_SubDFace::FromVertices(vertex_list.Array(), vertex_list.UnsignedCount());
}

const ON_SubDFacePtr ON_SubDFace::FromVertices(const ON_SubDVertex* const* vertex_list, size_t vertex_count)
{
  if (nullptr == vertex_list || vertex_count < 3 || vertex_count > ON_SubDFace::MaximumEdgeCount)
    return ON_SubDFacePtr::Null;

  const ON_SubDFace* candiates4[4];
  const ON_SubDFace** candidates = nullptr;
  unsigned candidate_count = 0;
  const ON_SubDFace* f = nullptr;

  const unsigned unsigned_vertex_count = (unsigned)vertex_count;
  if (unsigned_vertex_count < 3)
    return ON_SubDFacePtr::Null;
  const ON_SubDVertex* v[2] = { nullptr,vertex_list[0] };
  for (unsigned fei = 0; fei < unsigned_vertex_count; ++fei)
  {
    v[0] = v[1];
    v[1] = vertex_list[(fei + 1) % unsigned_vertex_count];
    const ON_SubDEdge* e = ON_SubDEdge::FromVertices(v[0], v[1]).Edge();
    if (nullptr == e || e->m_face_count <= 0)
      candidate_count = 0;
    else if (0 == fei)
    {
      candidates = (e->m_face_count <= 4) ? candiates4 : ((const ON_SubDFace**)onmalloc(e->m_face_count * sizeof(candidates[0])));
      for (unsigned short efi = 0; efi < e->m_face_count; ++efi)
      {
        const ON_SubDFace* ef = e->Face(efi);
        if (nullptr != ef && unsigned_vertex_count == ef->EdgeCount())
          candidates[candidate_count++] = ef;
      }
    }
    else
    {
      unsigned c = 0;
      for (unsigned i = 0; i < candidate_count; ++i)
      {
        if (e->FaceArrayIndex(candidates[i]) < ON_UNSET_UINT_INDEX)
          candidates[c++] = candidates[i];
      }
      candidate_count = c;
    }

    if (0 == candidate_count)
      break;
    if (1 == candidate_count)
    {
      f = candidates[0];
      break;
    }
  }

  if (nullptr != candidates && candidates != candiates4)
    onfree(candidates);

  if (nullptr == f)
    return ON_SubDFacePtr::Null;

  const unsigned fvi0 = f->VertexIndex(vertex_list[0]);
  if (fvi0 >= unsigned_vertex_count)
    return ON_SubDFacePtr::Null;

  const ON__UINT_PTR dir = (vertex_list[1] == f->Vertex((fvi0 + 1) % unsigned_vertex_count)) ? 0 : 1;
  if (0 == dir)
  {
    for (unsigned fvi = 2; fvi < unsigned_vertex_count; fvi++)
    {
      if (vertex_list[fvi] != f->Vertex((fvi0 + fvi) % unsigned_vertex_count))
        return ON_SubDFacePtr::Null;
    }
  }
  else
  {
    for (unsigned fvi = 1; fvi < unsigned_vertex_count; fvi++)
    {
      if (vertex_list[fvi] != f->Vertex((fvi0 + unsigned_vertex_count - fvi) % unsigned_vertex_count))
        return ON_SubDFacePtr::Null;
    }
  }
  return ON_SubDFacePtr::Create(f, dir);
}

const ON_3dPoint ON_SubDEdge::ControlNetPoint( unsigned int i) const
{
  if (i >= 2 || nullptr == m_vertex[i])
    return ON_3dPoint::NanPoint;
  return (ON_3dPoint(m_vertex[i]->m_P));
}

const ON_Line ON_SubDEdge::ControlNetLine() const
{
  return ON_Line(ControlNetPoint(0), ControlNetPoint(1));
}

const ON_3dVector ON_SubDEdge::ControlNetDirection() const
{
  if (nullptr == m_vertex[0] || nullptr == m_vertex[1])
    return ON_3dVector::NanVector;
  const ON_3dPoint P[2] = { ON_3dPoint(m_vertex[0]->m_P) ,ON_3dPoint(m_vertex[1]->m_P) };
  return (P[0].IsValid() && P[1].IsValid()) ? (P[1] - P[0]) : ON_3dVector::NanVector;
}

const ON_3dVector ON_SubDEdge::ControlNetDirectionFrom(
  const ON_SubDVertex* v
) const
{
  if (nullptr != v)
  {
    if (v == m_vertex[0] && nullptr != m_vertex[1])
      return ControlNetDirection();
    if (v == m_vertex[1] && nullptr != m_vertex[0])
      return -ControlNetDirection();
  }
  return ON_3dVector::NanVector;
}


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFace
//



//bool ON_SubDFace::IsOrdinary(
//  ON_SubD::SubDType subdivision_type,
//  bool bTestFaces
//  ) const
//{
//  unsigned int ordinary_face_edge_count = 0;
//  if (ON_SubD::SubDType::QuadCatmullClark == subdivision_type)
//    ordinary_face_edge_count = 4;
//  else if (ON_SubD::SubDType::TriLoopWarren == subdivision_type)
//    ordinary_face_edge_count = 3;
//  else
//    return false;
//
//  if (ordinary_face_edge_count != m_edge_count)
//    return false;
//
//  for (unsigned int fei = 0; fei < ordinary_face_edge_count; fei++)
//  {
//    ON__UINT_PTR eptr = m_edge4[fei].m_ptr;
//    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr);
//    if (nullptr == e || 2 != e->m_face_count || ON_SubDEdgeTag::Smooth != e->m_edge_tag)
//      return false;
//    ON__UINT_PTR edir = ON_SUBD_EDGE_DIRECTION(eptr);
//    const ON_SubDVertex* v = e->m_vertex[edir];
//    if (nullptr == v || false == v->IsOrdinary(subdivision_type,ON_SubDVertexTag::Unset,bTestFaces))
//      return false;
//  }
//  return true;
//}

void ON_SubDFace::CopyFrom(
  const ON_SubDFace* src,
  bool bCopyEdgeArray,
  bool bCopySymmetrySetNext
  )
{
  if (nullptr == src)
    src = &ON_SubDFace::Empty;

  CopyBaseFrom(src, bCopySymmetrySetNext);

  m_next_face = nullptr;

  m_material_channel_index = src->m_material_channel_index;
  m_per_face_color = src->m_per_face_color;

  m_level_zero_face_id = src->m_level_zero_face_id;

  if (bCopyEdgeArray)
  {
    if (src->m_edge_count > 0 && (src->m_edge_count <= 4 || (nullptr != src->m_edgex && nullptr != m_edgex)))
    {
      m_edge4[0] = src->m_edge4[0];
      m_edge4[1] = src->m_edge4[1];
      m_edge4[2] = src->m_edge4[2];
      m_edge4[3] = src->m_edge4[3];
      unsigned int edge_count = src->m_edge_count;
      if (edge_count > 4)
      {
        edge_count -= 4;
        for (unsigned int fei = 0; fei < edge_count; fei++)
          m_edgex[fei] = src->m_edgex[fei];
      }
      m_edge_count = src->m_edge_count;
    }
    else
      m_edge_count = 0;
  }

  // RH-56133 need to copy packed coordinate information.
  m_pack_id = src->m_pack_id;
  m_pack_rect_origin[0] = src->m_pack_rect_origin[0];
  m_pack_rect_origin[1] = src->m_pack_rect_origin[1];
  m_pack_rect_size[0] = src->m_pack_rect_size[0];
  m_pack_rect_size[1] = src->m_pack_rect_size[1];
  m_pack_status_bits = src->m_pack_status_bits;

  // and need to copy texture coordinates
  m_texture_status_bits = src->m_texture_status_bits;
  const unsigned this_texture_point_capacity = this->TexturePointsCapacity();
  const unsigned texture_point_count = (src->TexturePointsAreSet() && this_texture_point_capacity  >= this->EdgeCount()) ? this->EdgeCount() : 0;
  if (texture_point_count >= 3)
  {
    // copy texture points
    for (unsigned i = 0; i < texture_point_count; ++i)
      m_texture_points[i] = src->m_texture_points[i];
    const unsigned texture_point_capacity = this->TexturePointsCapacity();
    for (unsigned i = texture_point_count; i < texture_point_capacity; ++i)
      m_texture_points[i] = ON_3dPoint::NanPoint;
    this->m_texture_status_bits |= ON_SubDFace::TextureStatusBits::TexturePointsSet;
  }
  else
  {
    // whatever created the face failed to allocate texture point memory.
    this->m_texture_status_bits &= ON_SubDFace::TextureStatusBits::NotTexturePointsBitsMask;
  }
}

const ON_SubDEdgePtr ON_SubDFace::EdgePtr(
  unsigned int i
  ) const
{
  return (i < 4) ? m_edge4[i] : ((i < m_edge_count) ? m_edgex[i-4] : ON_SubDEdgePtr::Null);
}

unsigned int ON_SubDFace::EdgeCount() const
{
  return m_edge_count;
}


bool ON_SubDFace::HasEdges() const
{
  if (m_edge_count < 3 || m_edge_count > ON_SubDFace::MaximumEdgeCount)
    return false;
  if (m_edge_count > 4 + m_edgex_capacity)
    return false;
  const ON_SubDEdgePtr* eptr = m_edge4;
  const ON_SubDVertex* v0 = nullptr;
  const ON_SubDVertex* v1 = nullptr;
  const ON_SubDVertex* ev[2];
  for (unsigned short fei = 0; fei < m_edge_count; ++fei, ++eptr)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        return false;
      if (m_edge_count > 4 + m_edgex_capacity)
        return false;
    }
    const ON__UINT_PTR ptr = eptr->m_ptr;
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(ptr);
    if (nullptr == e)
      return false;
    if (0 == e->m_face_count)
      return false;
    if (e->m_face_count > 2 + e->m_facex_capacity)
      return false;
    if (0 == ON_SUBD_EDGE_DIRECTION(ptr))
    {
      ev[0] = e->m_vertex[0];
      ev[1] = e->m_vertex[1];
    }
    else
    {
      ev[0] = e->m_vertex[1];
      ev[1] = e->m_vertex[0];
    }
    if (nullptr == ev[0] || nullptr == ev[1] || ev[0] == ev[1])
      return false;
    if (nullptr == v0)
      v0 = ev[0];
    else if (v1 != ev[0])
      return false;
    v1 = ev[1];
    if (v1->m_edge_count < 2 || v1->m_edge_count > v1->m_edge_capacity)
      return false;
    if (v1->m_face_count < 1 || v1->m_face_count > v1->m_face_capacity)
      return false;
  }
  if ( v0 != v1)
    return false;

  return true;
}

unsigned int ON_SubDFace::MarkedEdgeCount() const
{
  unsigned int marked_edge_count = 0;
  const ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned short fei = 0; fei < m_edge_count; ++fei, ++ eptr)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        break;
    }
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
    if (nullptr != e && e->m_status.RuntimeMark())
      ++marked_edge_count;
  }
  return marked_edge_count;
}


unsigned int ON_SubDFace::SetEdgeMarks(bool bMark) const
{
  bMark = bMark ? true : false; // so exact compare can be used
  unsigned int changed_mark_count = 0;
  const ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned short fei = 0; fei < m_edge_count; ++fei, ++ eptr)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        break;
    }
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
    if (nullptr != e && bMark != e->m_status.RuntimeMark())
    {
      e->m_status.SetRuntimeMark(bMark);
      ++changed_mark_count;
    }
  }
  return changed_mark_count;
}

bool ON_SubDFace::HasSharpEdges() const
{
  const ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned short fei = 0; fei < m_edge_count; ++fei, ++eptr)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        break;
    }
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
    if (nullptr != e && e->IsSharp())
      return true;
  }
  return false;
}

unsigned int ON_SubDFace::SharpEdgeCount(ON_SubDEdgeSharpness& sharpness_range) const
{
  sharpness_range = ON_SubDEdgeSharpness::Smooth;
  unsigned int sharp_edge_count = 0;
  const ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned short fei = 0; fei < m_edge_count; ++fei, ++eptr)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        break;
    }
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
    if (nullptr == e || false == e->IsSharp())
      continue;
    const ON_SubDEdgeSharpness s = e->Sharpness(false);
    sharpness_range = ON_SubDEdgeSharpness::Union(sharpness_range, s);
    ++sharp_edge_count;
  }
  return sharp_edge_count;
}

double ON_SubDFace::MaximumEdgeSharpness() const
{
  double max_edge_sharpness = 0.0;
  const ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned short fei = 0; fei < m_edge_count; ++fei, ++eptr)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        break;
    }
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
    if (nullptr == e || false == e->IsSharp())
      continue;
    const ON_SubDEdgeSharpness s = e->Sharpness(false);
    const double m = s.MaximumEndSharpness();
    if (m > max_edge_sharpness)
      max_edge_sharpness = m;
  }
  return max_edge_sharpness;
}

unsigned int ON_SubDFace::SharpEdgeCount() const
{
  unsigned int sharp_edge_count = 0;
  const ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned short fei = 0; fei < m_edge_count; ++fei, ++eptr)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        break;
    }
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
    if (nullptr != e && e->IsSharp())
      ++sharp_edge_count;
  }
  return sharp_edge_count;
}

unsigned int ON_SubDFace::GetEdgeArray(
  ON_SimpleArray< ON_SubDEdgePtr >& face_edge_array
) const
{
  face_edge_array.SetCount(0);
  const unsigned edge_count = m_edge_count;
  face_edge_array.Reserve(edge_count);
  face_edge_array.Append(edge_count <= 4 ? edge_count : 4U, m_edge4);
  if (edge_count > 4)
  {
    if ( nullptr != m_edgex )
     face_edge_array.Append(edge_count-4U, m_edgex);
    else
    {
      for (unsigned fei = 4; fei < edge_count; ++fei)
        face_edge_array.Append(ON_SubDEdgePtr::Null);
    }
  }
  return edge_count;
}

unsigned int ON_SubDFace::SetVertexMarks(bool bMark) const
{
  bMark = bMark ? true : false; // so exact compare can be used
  unsigned int changed_mark_count = 0;
  const ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned short fei = 0; fei < m_edge_count; ++fei, ++ eptr)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        break;
    }
    const ON_SubDVertex* v = eptr->RelativeVertex(0);
    if (nullptr != v && bMark != v->m_status.RuntimeMark())
    {
      v->m_status.SetRuntimeMark(bMark);
      ++changed_mark_count;
    }
  }
  return changed_mark_count;
}

unsigned int ON_SubDFace::MarkedVertexCount() const
{
  unsigned int marked_vertex_count = 0;
  const ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned short fei = 0; fei < m_edge_count; ++fei, ++ eptr)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        break;
    }
    const ON_SubDVertex* v = eptr->RelativeVertex(0);
    if (nullptr != v && v->m_status.RuntimeMark())
      ++marked_vertex_count;
  }
  return marked_vertex_count;
}

bool ON_SubDFace::EdgeMark(
  unsigned int i,
  bool bMissingEdgeReturnValue
) const
{
  const ON_SubDEdge* e = Edge(i);
  return (nullptr != e) ? e->Mark() : bMissingEdgeReturnValue;
}

ON__UINT8 ON_SubDFace::EdgeMarkBits(
  unsigned int i,
  ON__UINT8 missing_edge_markbits
) const
{
  const ON_SubDEdge* e = Edge(i);
  return (nullptr != e) ? e->MarkBits() : missing_edge_markbits;
}

bool ON_SubDFace::VertexMark(
  unsigned int i,
  bool bMissingVertexReturnValue
) const
{
  const ON_SubDVertex* v = Vertex(i);
  return (nullptr != v) ? v->Mark() : bMissingVertexReturnValue;
}

ON__UINT8 ON_SubDFace::VertexMarkBits(
  unsigned int i,
  ON__UINT8 missing_vertex_markbits
) const
{
  const ON_SubDVertex* v = Vertex(i);
  return (nullptr != v) ? v->MarkBits() : missing_vertex_markbits;
}

const class ON_SubDVertex* ON_SubDFace::Vertex(
  unsigned int i
  ) const
{
  ON_SubDEdge* e;
  const ON__UINT_PTR edge_ptr = (i < 4) ? m_edge4[i].m_ptr : ((i < m_edge_count) ? m_edgex[i - 4].m_ptr : 0);
  return (nullptr != (e = ON_SUBD_EDGE_POINTER(edge_ptr))) ? e->m_vertex[ON_SUBD_EDGE_DIRECTION(edge_ptr)] : nullptr;
}

const ON_3dPoint ON_SubDFace::ControlNetPoint(unsigned int i) const
{
  const ON_SubDEdge* e;
  const ON__UINT_PTR edge_ptr = (i < 4) ? m_edge4[i].m_ptr : ((i < m_edge_count) ? m_edgex[i - 4].m_ptr : 0);
  const ON_SubDVertex* v = (nullptr != (e = ON_SUBD_EDGE_POINTER(edge_ptr))) ? e->m_vertex[ON_SUBD_EDGE_DIRECTION(edge_ptr)] : nullptr;
  return (nullptr != v) ? ON_3dPoint(v->m_P) : ON_3dPoint::NanPoint;
}

const ON_SubDVertex* ON_SubDFace::QuadOppositeVertex(
  const ON_SubDVertex* vertex
  ) const
{
  if ( nullptr == vertex )
    return ON_SUBD_RETURN_ERROR(nullptr);
  if ( 4 != m_edge_count)
    return nullptr; // not an error
  
  ON__UINT_PTR ptr0 = m_edge4[0].m_ptr;
  const ON_SubDEdge* e0 = ON_SUBD_EDGE_POINTER(ptr0);
  if ( nullptr == e0 )
    return ON_SUBD_RETURN_ERROR(nullptr);
  ptr0 = ON_SUBD_EDGE_DIRECTION(ptr0);
  
  ON__UINT_PTR ptr2 = m_edge4[2].m_ptr;
  const ON_SubDEdge* e2 = ON_SUBD_EDGE_POINTER(ptr2);
  if ( nullptr == e2 )
    return ON_SUBD_RETURN_ERROR(nullptr);
  ptr2 = ON_SUBD_EDGE_DIRECTION(ptr2);

  if (vertex == e0->m_vertex[ptr0])
    return e2->m_vertex[ptr2];

  if (vertex == e0->m_vertex[1-ptr0])
    return e2->m_vertex[1-ptr2];

  if (vertex == e2->m_vertex[ptr2])
    return e0->m_vertex[ptr0];

  if (vertex == e2->m_vertex[1-ptr2])
    return e0->m_vertex[1-ptr0];

  return ON_SUBD_RETURN_ERROR(nullptr);
}

const ON_SubDEdge* ON_SubDFace::QuadOppositeEdge(
  const ON_SubDEdge* edge
  ) const
{
  if ( nullptr == edge )
    return ON_SUBD_RETURN_ERROR(nullptr);
  if ( 4 != m_edge_count)
    return nullptr; // not an error
  
  for (unsigned int fei = 0; fei < 4; fei++)
  {
    const ON_SubDEdge* e0 = ON_SUBD_EDGE_POINTER(m_edge4[fei].m_ptr);
    if (nullptr == e0)
      return ON_SUBD_RETURN_ERROR(nullptr);
    if (e0 == edge)
    {
      e0 = ON_SUBD_EDGE_POINTER(m_edge4[(fei + 2) % 4].m_ptr);
      if (nullptr == e0)
        return ON_SUBD_RETURN_ERROR(nullptr);
      return e0;
    }
  }

  return ON_SUBD_RETURN_ERROR(nullptr);
}


unsigned int  ON_SubDFace::GetCornerEdges(
  const ON_SubDVertex* corner_vertex,
  ON_SubDEdgePtr& entering_edge,
  ON_SubDEdgePtr& leaving_edge
) const
{
  for (;;)
  {
    const unsigned edge_count = this->EdgeCount();
    if (edge_count < 3)
      break;
    if (nullptr == corner_vertex)
      break;
    const unsigned fvi = this->VertexIndex(corner_vertex);
    if (fvi >= edge_count)
      break;
    entering_edge = this->EdgePtr((fvi + edge_count - 1) % edge_count);
    leaving_edge = this->EdgePtr(fvi);
    return entering_edge.IsNotNull() && leaving_edge.IsNotNull();
  }
  entering_edge = ON_SubDEdgePtr::Null;
  leaving_edge = ON_SubDEdgePtr::Null;
  return ON_UNSET_UINT_INDEX;
}

const class ON_SubDEdge* ON_SubDFace::Edge(
  unsigned int i
  ) const
{
  return (i < 4) ? ON_SUBD_EDGE_POINTER(m_edge4[i].m_ptr) : ((i < m_edge_count) ? ON_SUBD_EDGE_POINTER(m_edgex[i - 4].m_ptr) : nullptr);
}

ON__UINT_PTR ON_SubDFace::EdgeDirection(
  unsigned int i
  ) const
{
  return (i < 4) ? ON_SUBD_EDGE_DIRECTION(m_edge4[i].m_ptr) : ((i < m_edge_count) ? ON_SUBD_EDGE_DIRECTION(m_edgex[i - 4].m_ptr) : 0);
}


const ON_SubDEdgePtr ON_SubDFace::EdgePtrFromEdge(
  const class ON_SubDEdge* e
) const
{
  if (nullptr != e)
  {
    const ON_SubDEdgePtr* eptr = m_edge4;
    const unsigned int face_edge_count = m_edge_count;
    for (unsigned int fei = 0; fei < face_edge_count; fei++, eptr++)
    {
      if (4 == fei)
      {
        eptr = m_edgex;
        if (nullptr == eptr)
          break;
      }
      if (e == ON_SUBD_EDGE_POINTER(eptr->m_ptr))
        return *eptr;
    }
  }

  return ON_SubDEdgePtr::Null;
}


unsigned int ON_SubDFace::EdgeArrayIndex(
  const ON_SubDEdge* e
  ) const
{
  if (nullptr != e)
  {
    const ON_SubDEdgePtr* eptr = m_edge4;
    const unsigned int face_edge_count = m_edge_count;
    for (unsigned int fei = 0; fei < face_edge_count; fei++, eptr++)
    {
      if (4 == fei)
      {
        eptr = m_edgex;
        if (nullptr == eptr)
          break;
      }
      if (e == ON_SUBD_EDGE_POINTER(eptr->m_ptr))
        return fei;
    }
  }

  return ON_UNSET_UINT_INDEX;
}


const ON_SubDEdge* ON_SubDFace::PrevEdge(
  const ON_SubDEdge* edge
  ) const
{
  unsigned int edge_index = EdgeArrayIndex(edge);
  if (ON_UNSET_UINT_INDEX == edge_index)
    return nullptr;
  const unsigned int edge_count = m_edge_count;
  edge_index = (edge_index + (edge_count - 1)) % edge_count;
  return Edge(edge_index);
}

const ON_SubDEdge* ON_SubDFace::NextEdge(
  const ON_SubDEdge* edge
  ) const
{
  unsigned int edge_index = EdgeArrayIndex(edge);
  if (ON_UNSET_UINT_INDEX == edge_index)
    return nullptr;
  edge_index = (edge_index + 1) % ((unsigned int)m_edge_count);
  return Edge(edge_index);
}

unsigned int ON_SubDFace::PrevEdgeArrayIndex(
  unsigned int edge_array_index
  ) const
{
  const unsigned int edge_count = m_edge_count;
  return (edge_array_index < edge_count) ? ((edge_array_index + edge_count - 1) % edge_count) : ON_UNSET_UINT_INDEX;
}

unsigned int ON_SubDFace::NextEdgeArrayIndex(
  unsigned int edge_array_index
  ) const
{
  const unsigned int edge_count = m_edge_count;
  return (edge_array_index < edge_count) ? ((edge_array_index +  1) % edge_count) : ON_UNSET_UINT_INDEX;
}

bool ON_SubDVertex::RemoveEdgeFromArray(const ON_SubDEdge * e)
{
  if (nullptr == e || 0 == m_edge_count || nullptr == m_edges)
    return ON_SUBD_RETURN_ERROR(false);
  unsigned short new_count = 0;
  for (unsigned short vei = 0; vei < m_edge_count; ++vei)
  {
    const ON_SubDEdgePtr eptr = m_edges[vei];
    if (e == ON_SUBD_EDGE_POINTER(eptr.m_ptr))
      continue;
    m_edges[new_count++] = eptr;
  }
  if (new_count == m_edge_count)
    return false;
  m_edge_count = new_count;
  return true;
}

bool ON_SubDVertex::RemoveFaceFromArray(const ON_SubDFace * f)
{
  if (nullptr == f || 0 == m_face_count || nullptr == m_faces)
    return ON_SUBD_RETURN_ERROR(false);
  unsigned short new_count = 0;
  for (unsigned short vfi = 0; vfi < m_face_count; ++vfi)
  {
    const ON_SubDFace* vf = m_faces[vfi];
    if (f == vf)
      continue;
    m_faces[new_count++] = vf;
  }
  if (new_count == m_face_count)
    return false;
  m_face_count = new_count;
  return true;
}

bool ON_SubD::RemoveEdgeVertexConnection(
  ON_SubDEdge* e,
  ON_SubDVertex* v
)
{
  if (nullptr == e || nullptr == v)
    return false;
  if (v == e->m_vertex[0])
    e->m_vertex[0] = nullptr;
  if (v == e->m_vertex[1])
    e->m_vertex[1] = nullptr;
  return v->RemoveEdgeFromArray(e);
}

ON_SubDVertex* ON_SubD::RemoveEdgeVertexConnection(
  ON_SubDEdge* e,
  unsigned evi
)
{
  if (nullptr == e)
    return nullptr;
  ON_SubDVertex* v = const_cast<ON_SubDVertex*>((nullptr != e && evi >= 0 && evi <= 1) ? e->m_vertex[evi] : nullptr);
  return RemoveEdgeVertexConnection(e, v) ? v : nullptr;
}

ON_SubDVertexTag ON_SubDVertex::SuggestedVertexTag(
  bool bApplyInputTagBias,
  bool bReturnBestGuessWhenInvalid
) const
{
  unsigned wire_count = 0;
  unsigned boundary_count = 0;
  unsigned interior_count = 0;

  unsigned crease_count = 0;

  const unsigned edge_count = (nullptr != m_edges ? m_edge_count : 0U);
  if ( edge_count < 2)
    return ON_SubDVertexTag::Corner;

  for (unsigned vei = 0; vei < edge_count; ++vei)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
    if (nullptr == e)
      continue;
    switch(e->m_face_count)
    {
    case 0:
      ++wire_count;
      ++crease_count;
      break;
    case 1:
      ++boundary_count;
      ++crease_count;
      break;
    case 2:
      ++interior_count;
      if (ON_SubDEdgeTag::Crease == e->m_edge_tag)
        ++crease_count;
      break;
    default: // nonmanifold edge
      return ON_SubDVertexTag::Corner;
      break;
    }
  }

  if (crease_count >= 3)
    return ON_SubDVertexTag::Corner;

  if (wire_count > 0)
  {
    if (2 == wire_count && 0 == boundary_count && 0 == interior_count)
      return (bApplyInputTagBias && ON_SubDVertexTag::Corner == m_vertex_tag) ? ON_SubDVertexTag::Corner : ON_SubDVertexTag::Crease;
    return ON_SubDVertexTag::Corner;
  }

  ON_SubDVertexTag best_guess_tag = ON_SubDVertexTag::Unset;
  // crease_count >= 3 handled above
  switch (crease_count)
  {
  case 0:
    if (interior_count >= 2)
      return ON_SubDVertexTag::Smooth;
    if (bReturnBestGuessWhenInvalid)
    {
      // can occur when there is a nullptr edge
      best_guess_tag = ON_SubDVertexTag::Smooth;
    }
    break;
  case 1:
    if (0 == boundary_count && interior_count >= 2)
      return ON_SubDVertexTag::Dart;
    if (bReturnBestGuessWhenInvalid)
    {
      // topology is far from valid and dart evaluation is very delicate. 
      // We need more boundary edges, but using corner will at least give a well defined vertex surface point.
      best_guess_tag = ON_SubDVertexTag::Corner;
    }
    break;
  case 2:
    if(  (0 == boundary_count && interior_count >= 2) || (2 == boundary_count) )
      return (bApplyInputTagBias && ON_SubDVertexTag::Corner == m_vertex_tag) ? ON_SubDVertexTag::Corner : ON_SubDVertexTag::Crease;
    if (bReturnBestGuessWhenInvalid)
    {
      // topology is far from valid and dart evaluation is very delicate. 
      // We need more boundary edges, but using corner will at least give a well defined vertex surface point.
      best_guess_tag = ON_SubDVertexTag::Corner;
    }
    break;
  }

  return best_guess_tag;
}


bool ON_SubDEdge::RemoveFaceFromArray(
  const ON_SubDFace* f
  )
{
  unsigned int i;
  if (nullptr == f)
    return false;

  if (m_face_count <= 2)
  {
    for (i = 0; i < m_face_count; i++)
    {
      if (f == ON_SUBD_FACE_POINTER(m_face2[i].m_ptr))
      {
        for (i++; i < m_face_count; i++)
          m_face2[i - 1] = m_face2[i];
        m_face_count--;
        return true;
      }
    }
  }
  else
  {
    for (i = 0; i < 2; i++)
    {
      if (f == ON_SUBD_FACE_POINTER(m_face2[i].m_ptr))
      {
        for (i++; i < 2; i++)
          m_face2[i - 1] = m_face2[i];
        m_face2[1] = m_facex[0];
        for (i = 3; i < m_face_count; i++)
          m_facex[i - 3] = m_facex[i - 2];
        m_face_count--;
        return true;
      }
    }
    for (i = 2; i < m_face_count; i++)
    {
      if (f == ON_SUBD_FACE_POINTER(m_facex[i - 2].m_ptr))
      {
        for (i++; i < m_face_count; i++)
          m_facex[i - 3] = m_facex[i - 2];
        m_face_count--;
        return true;
      }
    }
  }

  return false;
}

bool ON_SubDEdge::AddFaceToArray(
  ON_SubDFacePtr face_ptr
)
{
  if (m_face_count < 2)
    m_face2[m_face_count] = face_ptr;
  else if (nullptr != m_facex && m_face_count < 2 + m_facex_capacity)
    m_facex[m_face_count - 2] = face_ptr;
  else
  {
    // not enough room in m_facex.
    // If you really are trying to make a non-manifold subd, 
    // then use ON_SubD::GrowEdgeFaceArray().
    return ON_SUBD_RETURN_ERROR(false);
  }
  m_face_count++;
  return true;
}

bool ON_SubDEdge::RemoveFaceFromArray(
  unsigned int i,
  ON_SubDFacePtr& removed_face
  )
{
  removed_face = ON_SubDFacePtr::Null;
  unsigned int count = m_face_count;
  if ( i >= count )
    return ON_SUBD_RETURN_ERROR(false);
  if (i < 2)
  {
    removed_face = m_face2[i];
  }
  if (count > 2)
  {
    if ( nullptr == m_facex || m_facex_capacity + ((unsigned short)2) < m_face_count )
      return ON_SUBD_RETURN_ERROR(false);
    if ( i >= 2 )
      removed_face = m_facex[i-2];
  }

  unsigned int j = i+1U;

  while (j < 2 && j < count)
  {
    // NOTE: 
    // 0 <= i < j < min(2,count) <= 2 so any warning that the following line may 
    // result in an invalid write is incorrect.
    m_face2[i++] = m_face2[j++];
  }

  if (count > 2)
  {
    m_face2[1] = m_facex[0];
    i = 0;
    j = 1;
    count -= 2;
    while (j < count )
      m_facex[i++] = m_facex[j++];
  }

  m_face_count--;

  return true;

}

bool ON_SubDFace::ReplaceEdgeInArray(
  unsigned int fei0,
  ON_SubDEdge* edge_to_remove,
  ON_SubDEdge* edge_to_insert
)
{
  const unsigned int face_edge_count = m_edge_count;
  ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned int fei = 0; fei < face_edge_count; fei++, eptr++)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        break;
    }
    if (fei >= fei0 && edge_to_remove == eptr->Edge() )
    {
      const ON__UINT_PTR edir = eptr->EdgeDirection();
      *eptr = ON_SubDEdgePtr::Create(edge_to_insert,edir);
      return true;
    }
  }
  return false;
}

bool ON_SubDFace::ReplaceEdgeInArray(
  unsigned int fei0,
  ON_SubDEdge* edge_to_remove,
  ON_SubDEdgePtr edgeptr_to_insert
)
{
  const unsigned int face_edge_count = m_edge_count;
  ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned int fei = 0; fei < face_edge_count; fei++, eptr++)
  {
    if (4 == fei)
    {
      eptr = m_edgex;
      if (nullptr == eptr)
        break;
    }
    if (fei >= fei0 && edge_to_remove == eptr->Edge() )
    {
      *eptr = edgeptr_to_insert;
      return true;
    }
  }
  return false;
}


bool ON_SubDFace::RemoveEdgeFromArray(
  unsigned int i,
  ON_SubDEdgePtr& removed_edge
  )
{
  removed_edge = ON_SubDEdgePtr::Null;
  unsigned int count = m_edge_count;
  if ( i >= count )
    return ON_SUBD_RETURN_ERROR(false);
  if (i < 4)
  {
    removed_edge = m_edge4[i];
  }
  if (count > 4)
  {
    if ( nullptr == m_edgex || m_edgex_capacity + ((unsigned short)4) < m_edge_count )
      return ON_SUBD_RETURN_ERROR(false);
    if ( i >= 4 )
      removed_edge = m_edgex[i-4];
  }

  unsigned int j = i+1;

  while (j < count)
  {
    const ON_SubDEdgePtr& edge_j = j < 4 ? m_edge4[j] : m_edgex[j - 4];
    if (i < 4)
      m_edge4[i] = edge_j;
    else
      m_edgex[i - 4] = edge_j;
    i++;
    j++;
  }

  m_edge_count--;

  return true;
}

bool ON_SubDFace::RotateEdgeArray(
  unsigned int fei0
)
{
  if (0 == fei0)
    return true;

  const unsigned int edge_count = m_edge_count;
  if (edge_count < 2 || edge_count > ON_SubDFace::MaximumEdgeCount || fei0 >= edge_count)
    return false;

  ON_SubDEdgePtr stack_eptr[8];
  ON_SubDEdgePtr* eptr 
    = (edge_count*sizeof(stack_eptr[0]) > sizeof(stack_eptr)) 
    ? ((ON_SubDEdgePtr*)onmalloc(edge_count * sizeof(eptr[0])))
    : stack_eptr;
  if (nullptr == eptr)
    return false;

  ON_SubDEdgePtr* feptr = m_edge4;
  for (unsigned int fei = 0; fei < edge_count; fei++)
  {
    if (4 == fei)
    {
      feptr = m_edgex;
      if (nullptr == feptr)
      {
        if ( eptr != stack_eptr )
          onfree(eptr);  
        return false;
      }
    }
    eptr[fei] = *feptr++;
  }

  feptr = m_edge4;
  for (unsigned int fei = 0; fei < edge_count; fei++)
  {
    if (4 == fei)
      feptr = m_edgex;
    *feptr++ = eptr[(fei + fei0) % edge_count];
  }
  if ( eptr != stack_eptr )
    onfree(eptr);

  return true;
}




bool ON_SubDFace::RemoveEdgeFromArray(
  const ON_SubDEdge* e
  )
{
  unsigned int i;
  if (nullptr == e)
    return false;

  if (m_edge_count <= 4)
  {
    for (i = 0; i < m_edge_count; i++)
    {
      if (e == ON_SUBD_EDGE_POINTER(m_edge4[i].m_ptr))
      {
        for (i++; i < m_edge_count; i++)
          m_edge4[i - 1] = m_edge4[i];
        m_edge_count--;
        m_edge4[m_edge_count] = ON_SubDEdgePtr::Null;
        return true;
      }
    }
  }
  else
  {
    for (i = 0; i < 4; i++)
    {
      if (e == ON_SUBD_EDGE_POINTER(m_edge4[i].m_ptr))
      {
        for (i++; i < 4; i++)
          m_edge4[i - 1] = m_edge4[i];
        m_edge4[3] = m_edgex[0];
        for (i = 5; i < m_edge_count; i++)
          m_edgex[i - 5] = m_edgex[i - 4];
        m_edge_count--;
        m_edgex[m_edge_count-4] = ON_SubDEdgePtr::Null;
        return true;
      }
    }
    for (i = 4; i < m_edge_count; i++)
    {
      if (e == ON_SUBD_EDGE_POINTER(m_edgex[i - 4].m_ptr))
      {
        for (i++; i < m_edge_count; i++)
          m_edgex[i - 5] = m_edgex[i - 4];
        m_edge_count--;
        m_edgex[m_edge_count-4] = ON_SubDEdgePtr::Null;
        return true;
      }
    }
  }

  return false;
}

unsigned int ON_SubDFace::VertexIndex(
  const ON_SubDVertex* vertex
  ) const
{
  if (nullptr == vertex)
    return ON_UNSET_UINT_INDEX;

  const ON_SubDEdgePtr* face_edges = m_edge4;
  const unsigned int edge_count = m_edge_count;

  for (unsigned int i = 0; i < edge_count; i += 2)
  {
    if (4 == i)
    {
      face_edges = m_edgex;
      if (nullptr == face_edges)
        break;
      face_edges -= 4;
    }
    ON__UINT_PTR e_ptr = face_edges[i].m_ptr;
    const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(e_ptr);
    if (nullptr != edge)
    {
      if (vertex == edge->m_vertex[0])
        return (0 == ON_SUBD_EDGE_DIRECTION(e_ptr)) ? i : ((i + 1) % edge_count);
      if (vertex == edge->m_vertex[1])
        return (0 == ON_SUBD_EDGE_DIRECTION(e_ptr)) ? ((i + 1) % edge_count) : i;
    }
  }

  return ON_UNSET_UINT_INDEX;
}

const ON_SubDComponentPtrPair ON_SubDFace::VertexEdgePair(
  const ON_SubDVertex* vertex
) const
{
  return ON_SubDFace::VertexEdgePair(VertexIndex(vertex));
}

const ON_SubDComponentPtrPair ON_SubDFace::VertexEdgePair(
  unsigned vertex_index
) const
{
  for (;;)
  {
    const unsigned edge_count = m_edge_count;
    if (edge_count < 3)
      break;
    if (vertex_index >= edge_count)
      break;
    if (edge_count > 4 && nullptr == m_edgex)
      break;
    const unsigned fei0 = (vertex_index + (edge_count - 1)) % edge_count;
    const ON_SubDEdgePtr eptr[2] =
    {
      (fei0 < 4 ? m_edge4[fei0] : m_edgex[fei0 - 4]),
      (vertex_index < 4 ? m_edge4[vertex_index] : m_edgex[vertex_index - 4]),
    };
    const ON_SubDVertex* v = eptr[0].RelativeVertex(1);
    if (nullptr == v || v != eptr[1].RelativeVertex(0))
      break;
    return ON_SubDComponentPtrPair::Create( ON_SubDComponentPtr::Create(eptr[0]), ON_SubDComponentPtr::Create(eptr[1]) );
  }
  return ON_SubDComponentPtrPair::Null;
}


//////////////////////////////////////////////////////////////////////////
//
// ON_SubD
//

ON_OBJECT_IMPLEMENT(ON_SubD,ON_Geometry,"F09BA4D9-455B-42C3-BA3B-E6CCACEF853B");

ON_SubD::ON_SubD() ON_NOEXCEPT
  : ON_Geometry()
{}

ON_SubD::~ON_SubD()
{
  this->Destroy();
}


#if defined(ON_HAS_RVALUEREF)
ON_SubD::ON_SubD( ON_SubD&& src ) ON_NOEXCEPT
  : ON_Geometry(std::move(src))
  , m_subdimple_sp(std::move(src.m_subdimple_sp))
{}

ON_SubD& ON_SubD::operator=( ON_SubD&& src )
{
  if ( this != &src )
  {
    this->Destroy();
    ON_Geometry::operator=(std::move(src));
    m_subdimple_sp = std::move(src.m_subdimple_sp);
  }
  return *this;
}
#endif


ON__UINT64 ON_SubD::RuntimeSerialNumber() const
{
  ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? subdimple->RuntimeSerialNumber : 0;
}

ON__UINT64 ON_SubD::GeometryContentSerialNumber() const
{
  const ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? subdimple->GeometryContentSerialNumber() : 0;
}

const ON_SubDHash ON_SubD::SubDHash(
  ON_SubDHashType hash_type,
  bool bForceUpdate
) const
{
  ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? subdimple->SubDHash(hash_type, bForceUpdate) : ON_SubDHash::Create(hash_type , *this);
}

const ON_SHA1_Hash ON_SubD::GeometryHash() const
{
  return this->SubDHash(ON_SubDHashType::Geometry, false).SubDHash();
}

const ON_SHA1_Hash ON_SubD::TopologyHash() const
{
  return this->SubDHash(ON_SubDHashType::Topology, false).SubDHash();
}

const ON_SubDHash ON_SubDimple::SubDHash(
  ON_SubDHashType hash_type,
  bool bForceUpdate
) const
{
  const unsigned vertex_count = this->ActiveLevel().m_vertex_count;
  if (0 == vertex_count)
    return ON_SubDHash::Empty;

  // m_subd_topologyX_hash, m_subd_topology_and_edge_crease_hash, and m_subd_geometry_hash
  // are mutable and use lazy evaluation to stay updated.
  // subd.GeometryContentSerialNumber() is used to detect stale values.
  ON_SubDHash* h;
  switch (hash_type)
  {
  case ON_SubDHashType::Topology:
    h = &this->m_subd_toplology_hash;
    break;
  case ON_SubDHashType::TopologyAndEdgeCreases:
    h = &this->m_subd_toplology_and_edge_creases_hash;
    break;
  case ON_SubDHashType::Geometry:
    h = &this->m_subd_geometry_hash;
    break;
  default:
    h = nullptr;
    break;
  }
  if ( nullptr == h)
    return ON_SubDHash::Empty;


  const unsigned edge_count = this->ActiveLevel().m_edge_count;
  const unsigned face_count = this->ActiveLevel().m_face_count;
  const ON__UINT64 rsn = this->RuntimeSerialNumber;
  const ON__UINT64 gsn = this->GeometryContentSerialNumber();
  if (
    false == bForceUpdate
    && h->IsNotEmpty()
    && hash_type == h->HashType()
    && rsn > 0 && rsn == h->SubDRuntimeSerialNumber()
    && gsn > 0 && gsn == h->SubDGeometryContentSerialNumber()
    && vertex_count == h->VertexCount()
    && edge_count == h->EdgeCount()
    && face_count == h->FaceCount()
    )
  {
    // The cache hash values are up to date (or should be).
    // If h is out of date, something somewhere modified the SubD components and 
    // failed to change the GeometryContentSerialNumber(). 
    // All C++ SDK opennurbs code changes gsn after modifying SubD geometry (or it's a bug that should be fixed).
    // The unwashed masses can do just about anything and that's why the bForceUpdate parameter is supplied.
    return *h;
  }

  // update cached value
  *h = ON_SubDHash::Create(hash_type,this);

  // return updated value
  return *h;
}

ON__UINT64 ON_SubD::RenderContentSerialNumber() const
{
  const ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? subdimple->RenderContentSerialNumber() : 0;
}

ON__UINT64 ON_SubD::ComponentStatusSerialNumber() const
{
  ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? subdimple->ComponentStatusSerialNumber() : 0;
}

ON__UINT64 ON_SubD::ChangeGeometryContentSerialNumberForExperts(
  bool bChangePreservesSymmetry
)
{
  // changes both ON_SubD::ContentSerialNumber and ON_SubD::RenderContentSerialNumber().
  if (this == &ON_SubD::Empty)
    return 0;
  ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? subdimple->ChangeGeometryContentSerialNumber(bChangePreservesSymmetry) : 0;
}


ON__UINT64 ON_SubD::ChangeRenderContentSerialNumber() const
{
  if (this == &ON_SubD::Empty)
    return 0;
  const ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? subdimple->ChangeRenderContentSerialNumber() : 0;
}

ON_SubDComponentLocation ON_SubD::ToggleSubDAppearanceValue(ON_SubDComponentLocation subd_appearance)
{
  if (ON_SubDComponentLocation::Surface == subd_appearance)
    return ON_SubDComponentLocation::ControlNet;
  if (ON_SubDComponentLocation::ControlNet == subd_appearance)
    return ON_SubDComponentLocation::Surface;
  return subd_appearance;
}

ON_SubDComponentLocation ON_SubDMeshFragmentIterator::SubDAppearance() const
{
  return 
    (ON_SubDComponentLocation::Surface == m_subd_appearance_override || ON_SubDComponentLocation::ControlNet == m_subd_appearance_override)
    ? m_subd_appearance_override
    : SubD().SubDAppearance();
}

void ON_SubDMeshFragmentIterator::SetSubDAppearanceOverride(ON_SubDComponentLocation subd_appearance_override)
{
  if (m_subd_appearance_override != subd_appearance_override )
    m_subd_appearance_override = subd_appearance_override;
}

ON_SubDComponentLocation ON_SubD::SubDAppearance() const
{
  const ON_SubDimple* subdimple = this->SubDimple();
  return (nullptr != subdimple) ? subdimple->SubDAppearance() : ON_SubD::DefaultSubDAppearance;
}

ON_SubDComponentLocation ON_SubDimple::SubDAppearance() const
{
  return m_subd_appearance;
}

void ON_SubD::SetSubDAppearance(ON_SubDComponentLocation subd_appearance) const
{
  if (
    subd_appearance != SubDAppearance()
    && (ON_SubDComponentLocation::Surface == subd_appearance || ON_SubDComponentLocation::ControlNet == subd_appearance)
    )
  {
    const ON_SubDimple* subdimple = const_cast<ON_SubD*>(this)->SubDimple(true);
    if (nullptr != subdimple)
      subdimple->SetSubDAppearance(subd_appearance);
  }
}

void ON_SubDimple::SetSubDAppearance(ON_SubDComponentLocation subd_appearance) const
{
  if (
    subd_appearance != m_subd_appearance
    && (ON_SubDComponentLocation::Surface == subd_appearance || ON_SubDComponentLocation::ControlNet == subd_appearance)
    )
  {
    m_subd_appearance = subd_appearance;
  }
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubD - ON_Object overrides
//

//virtual 
void ON_SubD::MemoryRelocate()
{
}

static bool ON_SubDIsNotValid(bool bSilentError)
{
  ON_SubDIncrementErrorCount();
  return bSilentError ? false : ON_IsNotValid();
}

static bool EdgeSectorCoefficientIsSet(
  double edge_sector_coefficient
  )
{
  return (0.0 < edge_sector_coefficient && edge_sector_coefficient < 1.0);
}

static bool EdgeSectorCoefficientIsValid(
  double edge_vertex_coefficient,
  const ON_SubDEdge* edge
)
{
  if (0.0 <= edge_vertex_coefficient && edge_vertex_coefficient < 1.0)
    return true;

  if (ON_SubDSectorType::UnsetSectorCoefficient == edge_vertex_coefficient && nullptr != edge && 0 == edge->SubdivisionLevel())
    return true;

  return false;
}

static bool IsValidVertexEdgeLink(
  const ON_SubDVertex* vertex,
  const ON_SubDEdge* edge,
  ON__UINT_PTR end_index,
  bool bSilentError
)
{
  if (nullptr == vertex || nullptr == edge)
    return ON_SubDIsNotValid(bSilentError);

  if (end_index > 1)
    return ON_SubDIsNotValid(bSilentError);

  if (edge->m_vertex[end_index] != vertex)
    return ON_SubDIsNotValid(bSilentError);

  if (vertex->SubdivisionLevel() != edge->SubdivisionLevel())
    return ON_SubDIsNotValid(bSilentError);

  if (false == EdgeSectorCoefficientIsValid(edge->m_sector_coefficient[end_index],edge))
    return ON_SubDIsNotValid(bSilentError);

  if ( edge->IsSmooth() )
  {
    // edge->m_edge_tag is ON_SubDEdgeTag::Smooth or ON_SubDEdgeTag::SmoothX
    if (ON_SubDVertexTag::Smooth == vertex->m_vertex_tag)
    {
      if (false == (0.0 == edge->m_sector_coefficient[end_index]))
        return ON_SubDIsNotValid(bSilentError);
    }
    else
    {
      const unsigned int tagged_end_index = edge->TaggedEndIndex();
      if (ON_SubDEdgeTag::SmoothX == edge->m_edge_tag)
      {
        if (2 != tagged_end_index)
          return ON_SubDIsNotValid(bSilentError);
      }
      else
      {
        if (tagged_end_index != (unsigned int)end_index)
          return ON_SubDIsNotValid(bSilentError);
      }
       
      ON_SubDSectorType st = ON_SubDSectorType::Create(edge,(unsigned int)end_index);
      if (!st.IsValid())
        return ON_SubDIsNotValid(bSilentError);

      const double expected_sector_coefficient = st.SectorCoefficient();
      if (false == (expected_sector_coefficient == edge->m_sector_coefficient[end_index]))
        return ON_SubDIsNotValid(bSilentError);

      if (false == EdgeSectorCoefficientIsSet(expected_sector_coefficient))
        return ON_SubDIsNotValid(bSilentError);
    }
  }
  else if(ON_SubDEdgeTag::Crease == edge->m_edge_tag)
  {
    // crease edge
    if (!(0.0 == edge->m_sector_coefficient[end_index]))
      return ON_SubDIsNotValid(bSilentError);

    if (ON_SubDVertexTag::Smooth == vertex->m_vertex_tag)
      return ON_SubDIsNotValid(bSilentError);

    if (ON_SubDVertexTag::Unset == vertex->m_vertex_tag)
      return ON_SubDIsNotValid(bSilentError);
  }
  else
  {
    return ON_SubDIsNotValid(bSilentError);
  }

  return true;
}

static bool IsValidVertexFaceLink(
  const ON_SubDVertex* vertex,
  const ON_SubDFace* face,
  unsigned int vertex_face_index,
  unsigned int face_vertex_index,
  bool bSilentError
  )
{
  if (nullptr == vertex || nullptr == face)
    return ON_SubDIsNotValid(bSilentError);

  if (vertex->SubdivisionLevel() != face->SubdivisionLevel())
    return ON_SubDIsNotValid(bSilentError);

  const unsigned int vertex_face_count = vertex->m_face_count;
  if (vertex_face_count <= 0)
    return ON_SubDIsNotValid(bSilentError);
  if (nullptr == vertex->m_faces)
    return ON_SubDIsNotValid(bSilentError);

  if (vertex_face_index >= vertex_face_count && ON_UNSET_UINT_INDEX != vertex_face_index)
    return ON_SubDIsNotValid(bSilentError);

  const unsigned int face_vertex_count = face->m_edge_count;
  if (face_vertex_count <= 0)
    return ON_SubDIsNotValid(bSilentError);
  if (face_vertex_count > 4 && nullptr == face->m_edgex)
    return ON_SubDIsNotValid(bSilentError);

  if (face_vertex_index >= face_vertex_count && ON_UNSET_UINT_INDEX != face_vertex_index)
    return ON_SubDIsNotValid(bSilentError);

  for (unsigned int i = 0; i < vertex_face_count; i++)
  {
    if (face == vertex->Face(i))
    {
      if (ON_UNSET_UINT_INDEX == vertex_face_index)
        vertex_face_index = i;
      else if (i != vertex_face_index)
        return ON_SubDIsNotValid(bSilentError);
    }
    else if (i == vertex_face_index)
    {
      return ON_SubDIsNotValid(bSilentError);
    }
  }

  for (unsigned int i = 0; i < face_vertex_count; i++)
  {
    if (vertex == face->Vertex(i))
    {
      if (ON_UNSET_UINT_INDEX == face_vertex_index)
        face_vertex_index = i;
      else if (i != face_vertex_index)
        return ON_SubDIsNotValid(bSilentError);
    }
    else if (i == face_vertex_index)
    {
      return ON_SubDIsNotValid(bSilentError);
    }
  }

  return true;
}


static bool IsValidEdgeFaceLink(
  const ON_SubDEdge* edge,
  const ON_SubDFace* face,
  unsigned int edge_face_index,
  unsigned int face_edge_index,
  bool bSilentError
  )
{
  if (nullptr == edge || nullptr == face)
    return ON_SubDIsNotValid(bSilentError);

  if (edge->SubdivisionLevel() != face->SubdivisionLevel())
    return ON_SubDIsNotValid(bSilentError);

  const unsigned int edge_face_count = edge->m_face_count;
  if (edge_face_count <= 0)
    return ON_SubDIsNotValid(bSilentError);
  if (edge_face_count > 2 && nullptr == edge->m_facex)
    return ON_SubDIsNotValid(bSilentError);

  if (edge_face_index >= edge_face_count && ON_UNSET_UINT_INDEX != edge_face_index)
    return ON_SubDIsNotValid(bSilentError);

  const unsigned int face_edge_count = face->m_edge_count;
  if (face_edge_count <= 0)
    return ON_SubDIsNotValid(bSilentError);
  if (face_edge_count > 4 && nullptr == face->m_edgex)
    return ON_SubDIsNotValid(bSilentError);

  if (face_edge_index >= face_edge_count && ON_UNSET_UINT_INDEX != face_edge_index)
    return ON_SubDIsNotValid(bSilentError);

  for (unsigned int i = 0; i < edge_face_count; i++)
  {
    if (face == edge->Face(i))
    {
      if (ON_UNSET_UINT_INDEX == edge_face_index)
        edge_face_index = i;
      else if (i != edge_face_index)
        return ON_SubDIsNotValid(bSilentError);
    }
    else if (i == edge_face_index)
    {
      return ON_SubDIsNotValid(bSilentError);
    }
  }

  for (unsigned int i = 0; i < face_edge_count; i++)
  {
    if (edge == face->Edge(i))
    {
      if (ON_UNSET_UINT_INDEX == face_edge_index)
        face_edge_index = i;
      else if (i != face_edge_index)
        return ON_SubDIsNotValid(bSilentError);
    }
    else if (i == face_edge_index)
    {
      return ON_SubDIsNotValid(bSilentError);
    }
  }

  return true;
}

class ON_Internal_DamagedMarker
{
public:
  ON_Internal_DamagedMarker() = default;
  ~ON_Internal_DamagedMarker()
  {
    if (nullptr != m_subd_component)
      m_subd_component->m_status.SetDamagedState(true);
  }

private:
  ON_Internal_DamagedMarker(const ON_Internal_DamagedMarker&) = delete;
  ON_Internal_DamagedMarker& operator=(const ON_Internal_DamagedMarker&) = delete;

public:
  ON_Internal_DamagedMarker(const ON_SubDComponentBase* subd_component)
    : m_subd_component(subd_component)
  {}

  void ClearComponent()
  {
    m_subd_component = nullptr;
  }

private:
  const ON_SubDComponentBase* m_subd_component = nullptr;
};

static bool IsValidSubDVertexTag(
  const ON_SubDVertex* vertex,
  bool bSilentError
)
{
  if (nullptr == vertex)
    return true; // this error detected elsewhere.

  ON_Internal_DamagedMarker dm(vertex);

  const unsigned short vertex_edge_count = vertex->m_edge_count;
  unsigned short crease_edge_count = 0;
  unsigned short smooth_edge_count = 0;
  for (unsigned short vei = 0; vei < vertex->m_edge_count; vei++)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(vertex->m_edges[vei].m_ptr);
    if (nullptr == e)
      continue;
    if (e->IsSmooth())
      ++smooth_edge_count;
    else if (e->IsCrease())
      ++crease_edge_count;
  }
  const bool bValidEdgeTags = (vertex_edge_count == crease_edge_count + smooth_edge_count);

  switch (vertex->m_vertex_tag)
  {
  case ON_SubDVertexTag::Unset:
    return ON_SubDIsNotValid(bSilentError);
    break;

  case ON_SubDVertexTag::Smooth:
    if (false == bValidEdgeTags)
      break; // invalid edge tags detected in IsValidSubDEdgeTag();

    if (
      0 != crease_edge_count
      || vertex_edge_count < 2
      || vertex_edge_count != smooth_edge_count
      || vertex_edge_count != vertex->m_face_count
      )
    {
      return ON_SubDIsNotValid(bSilentError);
    }
    break;

  case ON_SubDVertexTag::Crease:
    if (false == bValidEdgeTags)
      break; // invalid edge tags detected in IsValidSubDEdgeTag();

    if ( 2 != crease_edge_count )
    {
      return ON_SubDIsNotValid(bSilentError);
    }
    break;

  case ON_SubDVertexTag::Corner:
    if (false == bValidEdgeTags)
      break; // invalid edge tags detected in IsValidSubDEdgeTag();

    if (0 == crease_edge_count)
    {
      // currently, isolated vertices are not permitted - may change in the future
      return ON_SubDIsNotValid(bSilentError);
    }
    if (1 == crease_edge_count)
    {
      // must be a single wire crease edge ending at this vertex 
      if ( 1 != vertex_edge_count || 0 != vertex->m_face_count)
        return ON_SubDIsNotValid(bSilentError);

    }
    break;

  case ON_SubDVertexTag::Dart:
    if (false == bValidEdgeTags)
      break; // invalid edge tags detected in IsValidSubDEdgeTag();

    if (
      1 != crease_edge_count
      || vertex_edge_count < 2
      || vertex_edge_count != smooth_edge_count + crease_edge_count
      || vertex_edge_count != vertex->m_face_count
      )
    {
      return ON_SubDIsNotValid(bSilentError);
    }
    break;

  default:
    return ON_SubDIsNotValid(bSilentError);
    break;
  }

  dm.ClearComponent();
  return true;
}

static bool IsValidSubDEdgeTag(
  const ON_SubDEdge* edge,
  bool bSilentError
)
{
  if (nullptr == edge)
    return true; // this error detected elsewhere.

  //ON_SubDVertexTag vtag[2] = { ON_SubDVertexTag::Unset,ON_SubDVertexTag::Unset };
  unsigned int smooth_vertex_count = 0;
  unsigned int crease_vertex_count = 0;
  unsigned int corner_vertex_count = 0;
  unsigned int dart_vertex_count = 0;

  for ( unsigned int evi = 0; evi < 2; evi++)
  {
    if (nullptr == edge->m_vertex[evi])
      return true; // topology errors detected elsewhere
    switch (edge->m_vertex[evi]->m_vertex_tag)
    {
    case ON_SubDVertexTag::Smooth:
      ++smooth_vertex_count;
      break;
    case ON_SubDVertexTag::Crease:
      ++crease_vertex_count;
      break;
    case ON_SubDVertexTag::Corner:
      ++corner_vertex_count;
      break;
    case ON_SubDVertexTag::Dart:
      ++dart_vertex_count;
      break;
    case ON_SubDVertexTag::Unset:
      break;
    }
  };

  if (2 != smooth_vertex_count + crease_vertex_count + corner_vertex_count + dart_vertex_count)
    return true; // invalid vertex tags detected in IsValidSubDVertexTag();

  ON_Internal_DamagedMarker dm(edge);

  //const unsigned short edge_face_count = edge->m_face_count;
  switch(edge->m_edge_tag)
  {

  case ON_SubDEdgeTag::Unset:
    return ON_SubDIsNotValid(bSilentError);
    break;

  case ON_SubDEdgeTag::Smooth:
    if ( 2 != edge->m_face_count)
      return ON_SubDIsNotValid(bSilentError);
    if ( smooth_vertex_count < 1)
      return ON_SubDIsNotValid(bSilentError);
    break;

  case ON_SubDEdgeTag::Crease:
    if ( 0 != smooth_vertex_count )
      return ON_SubDIsNotValid(bSilentError);
    break;

  case ON_SubDEdgeTag::SmoothX:
    if ( 2 != edge->m_face_count)
      return ON_SubDIsNotValid(bSilentError);
    if ( 0 != smooth_vertex_count )
      return ON_SubDIsNotValid(bSilentError);
    break;

  default:
    return ON_SubDIsNotValid(bSilentError);
    break;
  }

  dm.ClearComponent();
  return true;
}


static bool IsValidSubDVertex(
  const ON_SubDVertex* vertex,
  unsigned short level,
  unsigned int* vertex_id_range,
  unsigned short ordinary_valence_count,
  bool bSilentError
  )
{
  if (nullptr == vertex)
    return ON_SubDIsNotValid(bSilentError);
  
  if (vertex->SubdivisionLevel() != level)
    return ON_SubDIsNotValid(bSilentError);
  
  if (nullptr != vertex_id_range)
  {
    if (vertex->m_id < vertex_id_range[0])
      return ON_SubDIsNotValid(bSilentError);
    if (vertex->m_id > vertex_id_range[1])
      return ON_SubDIsNotValid(bSilentError);
  }

  ON_Internal_DamagedMarker dm(vertex);

  if (vertex->m_edge_count < vertex->m_face_count)
  {
    if ( ON_SubDVertexTag::Corner != vertex->m_vertex_tag || vertex->m_edge_count < 3 )
      return ON_SubDIsNotValid(bSilentError);
  }

  if (vertex->m_edge_count > 0 && nullptr == vertex->m_edges)
    return ON_SubDIsNotValid(bSilentError);

  if (vertex->m_face_count > 0 && nullptr == vertex->m_faces)
    return ON_SubDIsNotValid(bSilentError);

  switch (vertex->m_vertex_tag)
  {
  case ON_SubDVertexTag::Smooth: // interior vertex
    if (vertex->m_edge_count != vertex->m_face_count)
      return ON_SubDIsNotValid(bSilentError);
    break;

  case ON_SubDVertexTag::Crease:
    if ( vertex->m_edge_count < 2 )
      return ON_SubDIsNotValid(bSilentError);
    break;

  case ON_SubDVertexTag::Corner:
    if ( vertex->m_edge_count < 1 )
      return ON_SubDIsNotValid(bSilentError);
    break;

  case ON_SubDVertexTag::Dart: // interior vertex
    if (level > 0 && ordinary_valence_count != vertex->m_edge_count)
      return ON_SubDIsNotValid(bSilentError);
    if (vertex->m_edge_count != vertex->m_face_count)
      return ON_SubDIsNotValid(bSilentError);
    break;

  default:
    // invalid value for this enum
    return ON_SubDIsNotValid(bSilentError);
    break;
  }

  unsigned int count = vertex->m_edge_count;
  for (unsigned int i = 0; i < count; i++)
  {
    const ON_SubDEdge* edge = vertex->Edge(i);
    if (nullptr == edge)
      return ON_SubDIsNotValid(bSilentError);
  }

  count = vertex->m_face_count;
  for (unsigned int i = 0; i < count; i++)
  {
    const ON_SubDFace* face = vertex->Face(i);
    if (nullptr == face)
      return ON_SubDIsNotValid(bSilentError);
  }

  dm.ClearComponent();
  return true;
}


static bool IsValidSubDEdge(
  const ON_SubDEdge* edge,
  unsigned short level,
  unsigned int* edge_id_range,
  bool bSilentError
  )
{
  if (nullptr == edge)
    return ON_SubDIsNotValid(bSilentError);

  if (edge->SubdivisionLevel() != level)
    return ON_SubDIsNotValid(bSilentError);

  if (nullptr != edge_id_range)
  {
    if (edge->m_id < edge_id_range[0])
      return ON_SubDIsNotValid(bSilentError);
    if (edge->m_id > edge_id_range[1])
      return ON_SubDIsNotValid(bSilentError);
  }

  ON_Internal_DamagedMarker dm(edge);

  const ON_SubDVertex* edge_vertex[2] = {};
  for (unsigned int i = 0; i < 2; i++)
  {
    const ON_SubDVertex* vertex = edge->Vertex(i);
    if (nullptr == vertex)
      return ON_SubDIsNotValid(bSilentError);
    edge_vertex[i] = vertex;
  }
  if (edge_vertex[0] == edge_vertex[1])
    return ON_SubDIsNotValid(bSilentError);

  if (edge->IsSmooth())
  {
    // m_edge_tag is ON_SubDEdgeTag::Smooth or ON_SubDEdgeTag::SmoothX
    if ( 2 != edge->m_face_count)
      return ON_SubDIsNotValid(bSilentError);
  }
  else if (ON_SubDEdgeTag::Crease != edge->m_edge_tag)
  {
    return ON_SubDIsNotValid(bSilentError);
  }

  if (edge->m_face_count > 2 && nullptr == edge->m_facex)
    return ON_SubDIsNotValid(bSilentError);

  dm.ClearComponent();

  return true;
}

static bool IsValidSubDFace(
  const ON_SubDFace* face,
  unsigned short level,
  unsigned int* face_id_range,
  unsigned short ordinary_face_edge_count,
  bool bSilentError
  )
{
  if (nullptr == face)
    return ON_SubDIsNotValid(bSilentError);

  if (face->SubdivisionLevel() != level)
    return ON_SubDIsNotValid(bSilentError);

  if (nullptr != face_id_range)
  {
    if (face->m_id < face_id_range[0])
      return ON_SubDIsNotValid(bSilentError);
    if (face->m_id > face_id_range[1])
      return ON_SubDIsNotValid(bSilentError);
  }

  ON_Internal_DamagedMarker dm(face);

  if (face->m_edge_count < 3)
    return ON_SubDIsNotValid(bSilentError);

  if (face->m_edge_count > 4 && nullptr == face->m_edgex)
    return ON_SubDIsNotValid(bSilentError);

  if (level > 0 && ordinary_face_edge_count != face->m_edge_count)
    return ON_SubDIsNotValid(bSilentError);

  dm.ClearComponent();

  return true;
}

bool ON_SubDimple::IsValidLevel(
  const ON_SubD& subd,
  unsigned int level_index,
  bool bSilentError,
  ON_TextLog* text_log
  ) const
{
  const unsigned int level_count = m_levels.UnsignedCount();
  if (level_index >= level_count || level_index >= 0xFFFF)
    return ON_SubDIsNotValid(bSilentError);
  const ON_SubDLevel* level = m_levels[level_index];
  if ( nullptr == level)
    return ON_SubDIsNotValid(bSilentError);
  level->ClearComponentDamagedState();

  if ( level->m_level_index != level_index)
    return ON_SubDIsNotValid(bSilentError);

  if (level_index <= 0)
  {
    if (level->m_vertex_count < 3)
      return ON_SubDIsNotValid(bSilentError);
    if (level->m_edge_count < 3)
      return ON_SubDIsNotValid(bSilentError);
    if (level->m_face_count < 1)
      return ON_SubDIsNotValid(bSilentError);
  }
  else
  {
    const ON_SubDLevel* previous_level = m_levels[level_index - 1];
    if (nullptr == previous_level)
      return ON_SubDIsNotValid(bSilentError);
    if (level->m_vertex_count <= previous_level->m_vertex_count)
      return ON_SubDIsNotValid(bSilentError);
    if (level->m_edge_count <= previous_level->m_edge_count)
      return ON_SubDIsNotValid(bSilentError);
    if (level->m_face_count <= previous_level->m_face_count)
      return ON_SubDIsNotValid(bSilentError);
  }

  if (nullptr == level->m_vertex[0])
    return ON_SubDIsNotValid(bSilentError);
  if (nullptr == level->m_edge[0])
    return ON_SubDIsNotValid(bSilentError);
  if (nullptr == level->m_face[0])
    return ON_SubDIsNotValid(bSilentError);

  if (nullptr == level->m_vertex[1])
    return ON_SubDIsNotValid(bSilentError);
  if (nullptr == level->m_edge[1])
    return ON_SubDIsNotValid(bSilentError);
  if (nullptr == level->m_face[1])
    return ON_SubDIsNotValid(bSilentError);


  const unsigned short expected_level = (unsigned short)level_index;
  unsigned int i;
  const ON_SubDVertex* vertex;
  const ON_SubDEdge* edge;
  const ON_SubDFace* face;

  unsigned int v_id_range[2] = { ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX };
  unsigned int e_id_range[2] = { ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX };
  unsigned int f_id_range[2] = { ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX };

  unsigned int point_vertex_count = 0;
  unsigned int wire_edge_count = 0;

  // simple vertex validation
  if (level_index == subd.ActiveLevelIndex())
  {
    if (subd.FirstVertex() != level->m_vertex[0])
      return ON_SubDIsNotValid(bSilentError);
    ON_SubDVertexIterator vit = subd.VertexIterator();
    if (vit.FirstVertex() != level->m_vertex[0])
      return ON_SubDIsNotValid(bSilentError);
    // IsValid() should not create these clunky cached arrays.
    //ON_SubDVertexArray va = subd.VertexArray();
    //if (va.VertexCount() != level->m_vertex_count)
    //  return ON_SubDIsNotValid(bSilentError);
    //if (va[0] != level->m_vertex[0])
    //  return ON_SubDIsNotValid(bSilentError);
    //if (va[level->m_vertex_count-1] != level->m_vertex[1])
    //  return ON_SubDIsNotValid(bSilentError);
  }
  const ON_SubDVertex* last_vertex = nullptr;
  for (i = 0, vertex = level->m_vertex[0]; i < level->m_vertex_count && nullptr != vertex; i++, vertex = vertex->m_next_vertex)
  {
    if (false == IsValidSubDVertex(vertex, expected_level, nullptr, level->m_ordinary_vertex_valence, bSilentError))
      return false;

    if (0 == i)
    {
      v_id_range[0] = v_id_range[1] = vertex->m_id;
    }
    else if (vertex->m_id < v_id_range[0])
      v_id_range[0] = vertex->m_id;
    else if (vertex->m_id > v_id_range[1])
      v_id_range[1] = vertex->m_id;

    if (0 == vertex->m_edge_count)
    {
      point_vertex_count++;
    }
    last_vertex = vertex;
  }
  if (level->m_vertex[1] != last_vertex)
    return ON_SubDIsNotValid(bSilentError);


  if (i != level->m_vertex_count || nullptr != vertex)
    return ON_SubDIsNotValid(bSilentError);
  if (1 + v_id_range[1] - v_id_range[0] < level->m_vertex_count)
    return ON_SubDIsNotValid(bSilentError);
  if ( v_id_range[1] > MaximumVertexId() )
    return ON_SubDIsNotValid(bSilentError);

  // currently, point vertices are not permitted
  if (point_vertex_count > 0)
    return ON_SubDIsNotValid(bSilentError);

  // simple edge validation
  if (level_index == subd.ActiveLevelIndex())
  {
    if (subd.FirstEdge() != level->m_edge[0])
      return ON_SubDIsNotValid(bSilentError);
    ON_SubDEdgeIterator eit = subd.EdgeIterator();
    if (eit.FirstEdge() != level->m_edge[0])
      return ON_SubDIsNotValid(bSilentError);

    // IsValid() should not create these clunky cached arrays.
    //ON_SubDEdgeArray ea = subd.EdgeArray();
    //if (ea.EdgeCount() != level->m_edge_count)
    //  return ON_SubDIsNotValid(bSilentError);
    //if (ea[0] != level->m_edge[0])
    //  return ON_SubDIsNotValid(bSilentError);
    //if (ea[level->m_edge_count-1] != level->m_edge[1])
    //  return ON_SubDIsNotValid(bSilentError);
  }
  const ON_SubDEdge* last_edge = nullptr;
  for (i = 0, edge = level->m_edge[0]; i < level->m_edge_count && nullptr != edge; i++, edge = edge->m_next_edge)
  {
    if (false == IsValidSubDEdge(edge, expected_level, nullptr, bSilentError))
      return false;
    if (0 == edge->m_face_count)
    {
      wire_edge_count++;
    }
    if (0 == i)
    {
      e_id_range[0] = e_id_range[1] = edge->m_id;
    }
    else if (edge->m_id < e_id_range[0])
      e_id_range[0] = edge->m_id;
    else if (edge->m_id > e_id_range[1])
      e_id_range[1] = edge->m_id;

    last_edge = edge;
  }
  if (i != level->m_edge_count || nullptr != edge)
    return ON_SubDIsNotValid(bSilentError);
  if (1 + e_id_range[1] - e_id_range[0] < level->m_edge_count)
    return ON_SubDIsNotValid(bSilentError);
  if (level->m_edge[1] != last_edge)
    return ON_SubDIsNotValid(bSilentError);
  if ( e_id_range[1] > MaximumEdgeId() )
    return ON_SubDIsNotValid(bSilentError);
   
  // As of November 12, 2019
  // Wire edges are permitted. THey exist in subds being edited.
  ////// currently, wire edges are not permitted
  ////if (wire_edge_count > 0)
  ////  return ON_SubDIsNotValid(bSilentError);
   
  // simple face validation
  if (level_index == subd.ActiveLevelIndex())
  {
    if (subd.FirstFace() != level->m_face[0])
      return ON_SubDIsNotValid(bSilentError);
    ON_SubDFaceIterator fit = subd.FaceIterator();
    if (fit.FirstFace() != level->m_face[0])
      return ON_SubDIsNotValid(bSilentError);
    // IsValid() should not create these clunky cached arrays.
    //ON_SubDFaceArray fa = subd.FaceArray();
    //if (fa.FaceCount() != level->m_face_count)
    //  return ON_SubDIsNotValid(bSilentError);
    //if (fa[0] != level->m_face[0])
    //  return ON_SubDIsNotValid(bSilentError);
    //if (fa[0] != level->m_face[0])
    //  return ON_SubDIsNotValid(bSilentError);
  }
  const ON_SubDFace* last_face = nullptr;
  for (i = 0, face = level->m_face[0]; i < level->m_face_count && nullptr != face; i++, face = face->m_next_face)
  {
    if (false == IsValidSubDFace(face, expected_level, nullptr, level->m_ordinary_face_edge_count, bSilentError))
      return false;

    if (0 == i)
    {
      f_id_range[0] = f_id_range[1] = face->m_id;
    }
    else if (face->m_id < f_id_range[0])
      f_id_range[0] = face->m_id;
    else if (face->m_id > f_id_range[1])
      f_id_range[1] = face->m_id;

    last_face = face;
  }
  if (i != level->m_face_count || nullptr != face)
    return ON_SubDIsNotValid(bSilentError);
  if (1 + f_id_range[1] - f_id_range[0] < level->m_face_count)
    return ON_SubDIsNotValid(bSilentError);  
  if (level->m_face[1] != last_face)
    return ON_SubDIsNotValid(bSilentError);
  if ( f_id_range[1] > MaximumFaceId() )
    return ON_SubDIsNotValid(bSilentError);


  // vertex topology validation
  for (vertex = level->m_vertex[0]; nullptr != vertex; vertex = vertex->m_next_vertex)
  {
    for (i = 0; i < vertex->m_edge_count; i++)
    {
      edge = vertex->Edge(i);
      if (false == IsValidSubDEdge(edge, expected_level, e_id_range, bSilentError))
        return false;
      if (false == IsValidVertexEdgeLink(vertex, edge, vertex->EdgeDirection(i), bSilentError))
        return false;
    }

    for (i = 0; i < vertex->m_face_count; i++)
    {
      face = vertex->Face(i);
      if (false == IsValidSubDFace(face, expected_level, f_id_range, level->m_ordinary_face_edge_count, bSilentError))
        return false;
      if (false == IsValidVertexFaceLink(vertex, face, i, ON_UNSET_UINT_INDEX, bSilentError))
        return false;
    }
  }

  // edge topology validation
  for (edge = level->m_edge[0]; nullptr != edge; edge = edge->m_next_edge)
  {
    for (i = 0; i < 2; i++)
    {
      vertex = edge->m_vertex[i];
      if (false == IsValidSubDVertex(vertex, expected_level, v_id_range, level->m_ordinary_vertex_valence, bSilentError))
        return false;
      if (false == IsValidVertexEdgeLink(vertex, edge, i, bSilentError))
        return false;
    }

    for (i = 0; i < edge->m_face_count; i++)
    {
      face = edge->Face(i);
      if (false == IsValidSubDFace(face, expected_level, f_id_range, level->m_ordinary_face_edge_count, bSilentError))
        return false;
      if (false == IsValidEdgeFaceLink(edge, face, i, ON_UNSET_UINT_INDEX, bSilentError))
        return false;
    }
  }

  // face topology validation
  for (face = level->m_face[0]; nullptr != face; face = face->m_next_face)
  {
    for (i = 0; i < face->m_edge_count; i++)
    {
      edge = face->Edge(i);
      if (false == IsValidSubDEdge(edge, expected_level, e_id_range, bSilentError))
        return false;
      if (false == IsValidEdgeFaceLink(edge, face, ON_UNSET_UINT_INDEX, i, bSilentError))
        return false;
    }

    for (i = 0; i < face->m_edge_count; i++)
    {
      vertex = face->Vertex(i);
      if (false == IsValidSubDVertex(vertex, expected_level, v_id_range, level->m_ordinary_vertex_valence, bSilentError))
        return false;
      if (false == IsValidVertexFaceLink(vertex, face, ON_UNSET_UINT_INDEX, i, bSilentError))
        return false;
    }
  }


  // edge tag validation
  for (edge = level->m_edge[0]; nullptr != edge; edge = edge->m_next_edge)
  {
    if (false == IsValidSubDEdgeTag(edge, bSilentError))
      return false;
  }

  // vertex tag validation
  for (vertex = level->m_vertex[0]; nullptr != vertex; vertex = vertex->m_next_vertex)
  {
    if (false == IsValidSubDVertexTag(vertex, bSilentError))
      return false;
  }

  // edge length validation
  for (edge = level->m_edge[0]; nullptr != edge; edge = edge->m_next_edge)
  {
    const ON_3dPoint P[2] = { edge->m_vertex[0]->ControlNetPoint(), edge->m_vertex[1]->ControlNetPoint() };
    if (false == (P[0] != P[1]))
    {
      edge->m_status.SetDamagedState(true);
      return ON_SubDIsNotValid(bSilentError);
    }
  }


  return true;
}

bool ON_SubDimple::IsValid(
  const ON_SubD& subd,
  bool bSilentError,
  ON_TextLog* text_log
  ) const
{
  if (false == m_heap.IsValid(bSilentError, text_log))
  {
    if (nullptr != text_log)
      text_log->Print("Component ids are not set correctly. m_heap.ResetId() will fix this but may break externally stored component references.\n");
    return ON_SubDIsNotValid(bSilentError);
  }

  const unsigned int level_count = m_levels.UnsignedCount();
  if (level_count < 1)
  {
    return ON_SubDIsNotValid(bSilentError);
  }

  for (unsigned int level_index = 0; level_index < level_count; level_index++)
  {
    if (false == IsValidLevel(subd, level_index, bSilentError, text_log))
      return false;
  }  

  return true;
}

//virtual
bool ON_SubD::IsValid(ON_TextLog* text_logx) const
{
  // If low bit of text_log pointer is 1, then ON_Error is not called when the
  // subd is invalid.
  const ON__INT_PTR lowbit = 1;
  const ON__INT_PTR hightbits = ~lowbit;
  const bool bSilentError = (0 != (lowbit & ((ON__INT_PTR)text_logx)));
  ON_TextLog* text_log = (ON_TextLog*)(((ON__INT_PTR)text_logx) & hightbits);
  
  const ON_SubDimple* subdimple = SubDimple();
  if (nullptr == subdimple)
    return ON_SubDIsNotValid(bSilentError);

  return subdimple->IsValid(*this, bSilentError, text_log);
}

//virtual
void ON_SubD::Dump(ON_TextLog& text_log) const
{
  // At maximum verbosity, dump all vertices, edges, faces, else dump the first 16.
  const unsigned maxcount = 0x7FFFFFFF;

  const unsigned face_count = text_log.LevelOfDetailIsAtLeast(ON_TextLog::LevelOfDetail::Maximum) ? maxcount : 16;

  // Bump vertex_count up a bit to deal with small models with lots of hexagons.
  const unsigned vertex_count = face_count < maxcount ? (3 * face_count) / 2 : maxcount;

  // And ... edge_count is set this way because in a typical control net,
  // vertex count - edge count + face count is nearish to zero.
  // (Euler's formula)
  const unsigned edge_count = face_count < maxcount ? (vertex_count + face_count + 8) : maxcount;

  const ON_2udex vertex_id_range(vertex_count, 0);
  const ON_2udex edge_id_range(edge_count, 0);
  const ON_2udex face_id_range(face_count, 0);

  DumpTopology(vertex_id_range,edge_id_range,face_id_range,text_log);
}

unsigned int ON_SubD::DumpTopology(ON_TextLog & text_log) const
{
  return DumpTopology(ON_2udex::Zero,ON_2udex::Zero,ON_2udex::Zero,text_log);
}

static const ON_wString Internal_DescribeWaste(size_t waste, size_t total)
{
  if (waste <= 0 || total <= 0)
    return ON_wString::ToMemorySize(0);

  double p = 100.0 * ((double)waste) / ((double)total);
  if (p != p)
    return ON_wString::EmptyString;
  const double i = (p - floor(p) <= 0.5) ? floor(p) : ceil(p);
  double e = fabs(i - p);

  ON_wString description = ON_wString::EmptyString;
  const double negligible = 0.1;
  if (e < negligible)
  {
    if (0.0 == i)
      description = L" negligible";
    p = i;
  }
  if (description.IsEmpty())
    description = (i >= 10.0) ? ON_wString::FormatToString(L"%g%% of total", i) : ON_wString::FormatToString(L"%0.1f%% of total)", p);
  if (waste > 0)
    description += ON_wString(L" (") + ON_wString::ToMemorySize(waste) + ON_wString(L")");
  return description;
}


unsigned int ON_SubD::DumpTopology(
  ON_2udex vertex_id_range,
  ON_2udex edge_id_range,
  ON_2udex face_id_range,
  ON_TextLog& text_log
) const
{
  const class ON_SubDimple* subdimple = SubDimple();
  if (nullptr == subdimple)
  {
    text_log.Print(L"SubD: Empty\n");
    return 0;
  }

  const unsigned int level_count = LevelCount();
  const unsigned int active_level_index = ActiveLevel().m_level_index;

  const bool bIsTextHash = text_log.IsTextHash();

  // TextHash ignores settings that don't depend on 3dm file content.
  const ON__UINT64 runtime_sn = (bIsTextHash) ? 0 : RuntimeSerialNumber();
  const ON__UINT64 geometry_content_sn = (bIsTextHash) ? 0 : this->GeometryContentSerialNumber();
  const ON__UINT64 render_content_sn = (bIsTextHash) ? 0 : this->RenderContentSerialNumber();

  const unsigned subd_vertex_count = VertexCount();
  const unsigned subd_edge_count = EdgeCount();
  const unsigned subd_face_count = FaceCount();

  if (level_count > 1)
  {
    text_log.Print(L"SubD[%" PRIu64 "]: %u levels. Level %u is active (%u vertices, %u edges, %u faces).\n",
      runtime_sn,
      level_count,
      active_level_index,
      subd_vertex_count,
      subd_edge_count,
      subd_face_count
    );
  }
  else
  {
    text_log.Print(
      L"SubD[%" PRIu64 "]: %u vertices, %u edges, %u faces\n",
      runtime_sn,
      subd_vertex_count,
      subd_edge_count,
      subd_face_count
    );
  }

  ON_SubDEdgeSharpness subd_sharpness_range = ON_SubDEdgeSharpness::Smooth;
  const unsigned int subd_sharp_edge_count = SharpEdgeCount(subd_sharpness_range);
  if (subd_sharp_edge_count > 0)
  {
    text_log.PushIndent();
    if ( subd_sharpness_range.IsConstant() )
    {
      if (1 == subd_sharp_edge_count)
        text_log.Print(
          L"1 sharp edge with end sharpness = %g.\n",
          subd_sharpness_range[0]
        );
      else
        text_log.Print(
          L"%u sharp edges with end sharpness = %g.\n",
          subd_sharp_edge_count,
          subd_sharpness_range[0]
        );
    }
    else
    {
      text_log.Print(
        L"%u sharp edges with end sharpnesses from %g to %g.\n",
        subd_sharp_edge_count,
        subd_sharpness_range[0],
        subd_sharpness_range[1]
        );

    }
    text_log.PopIndent();
  }

  const ON_SubDHashType htype[] = {
    ON_SubDHashType::Topology,
    ON_SubDHashType::TopologyAndEdgeCreases,
    ON_SubDHashType::Geometry
  };

  for (size_t i = 0; i < sizeof(htype) / sizeof(htype[0]); ++i)
  {
    const ON_SubDHash h = this->SubDHash(htype[i], false);
    h.Dump(text_log);
  }


  if (false == bIsTextHash)
  {
    text_log.Print(L"Texture coordinate settings:\n");
    ON_TextLogIndent indent1(text_log);

    const ON_SubDTextureCoordinateType subd_texture_coordinate_type = this->TextureCoordinateType();
    const ON_wString subd_texture_coordinate_type_as_string = ON_SubD::TextureCoordinateTypeToString(this->TextureCoordinateType());
    text_log.Print(L"TextureCoordinateType() = %ls\n", static_cast<const wchar_t*>(subd_texture_coordinate_type_as_string));

    const bool bShowMappingTag
      = false == bIsTextHash
      || ON_SubDTextureCoordinateType::FromMapping == subd_texture_coordinate_type
      ;

    if (bShowMappingTag)
    {
      const ON_MappingTag mapping_tag = this->TextureMappingTag(true);

      const bool bUnsetMappingTag = ON_MappingTag::Unset == mapping_tag;

      const bool bSurfaceParameterMappingTag
        = false == bUnsetMappingTag
        && (
          ON_MappingTag::SurfaceParameterMapping == mapping_tag
          || (bIsTextHash && (ON_TextureMapping::TYPE::srfp_mapping == mapping_tag.m_mapping_type || ON_MappingTag::SurfaceParameterMapping.m_mapping_id == mapping_tag.m_mapping_id))
          )
        ;


      // NOTE: the mapping tag is only applied when subd_texture_coordinate_type = FromMapping
      if (ON_SubDTextureCoordinateType::FromMapping == subd_texture_coordinate_type && false == bUnsetMappingTag)
        text_log.Print(L"TextureMappingTag()");
      else
        text_log.Print(L"Inactive TextureMappingTag()");

      if (bUnsetMappingTag)
        text_log.Print(L" = ON_MappingTag::Unset\n");
      else if (bSurfaceParameterMappingTag)
        text_log.Print(L" = ON_MappingTag::SurfaceParameterMapping\n");
      else
      {
        text_log.Print(":\n");
        const ON_TextLogIndent indent2(text_log);
        text_log.Print("m_mapping_type = ");
        switch (mapping_tag.m_mapping_type)
        {
        case  ON_TextureMapping::TYPE::no_mapping:
          text_log.Print("none");
          break;
        case  ON_TextureMapping::TYPE::srfp_mapping:
          text_log.Print("srfp");
          break;
        case  ON_TextureMapping::TYPE::plane_mapping:
          text_log.Print("plane");
          break;
        case  ON_TextureMapping::TYPE::cylinder_mapping:
          text_log.Print("cylinder");
          break;
        case  ON_TextureMapping::TYPE::sphere_mapping:
          text_log.Print("sphere");
          break;
        case  ON_TextureMapping::TYPE::box_mapping:
          text_log.Print("box");
          break;
        case  ON_TextureMapping::TYPE::mesh_mapping_primitive:
          text_log.Print("mesh primitive");
          break;
        case  ON_TextureMapping::TYPE::srf_mapping_primitive:
          text_log.Print("srf primitive");
          break;
        case  ON_TextureMapping::TYPE::brep_mapping_primitive:
          text_log.Print("brep primitive");
          break;
        case  ON_TextureMapping::TYPE::ocs_mapping:
          text_log.Print("ocs");
          break;
        case  ON_TextureMapping::TYPE::false_colors:
          text_log.Print("false colors");
          break;
        case  ON_TextureMapping::TYPE::wcs_projection	:
          text_log.Print("wcs projection");
          break;
        case  ON_TextureMapping::TYPE::wcsbox_projection	:
          text_log.Print("wcs box projection");
          break;
        }
        text_log.PrintNewLine();
        text_log.Print("m_mapping_id = ");
        text_log.Print(mapping_tag.m_mapping_id);
        if (mapping_tag.m_mapping_id == ON_MappingTag::SurfaceParameterMapping.m_mapping_id)
          text_log.Print(" = ON_MappingTag::SurfaceParameterMapping.m_mapping_id");
        text_log.PrintNewLine();
        text_log.Print("m_mapping_crc = %08x\n", mapping_tag.m_mapping_crc);
        text_log.Print("m_mesh_xform:\n");
        text_log.PushIndent();
        text_log.Print(mapping_tag.m_mesh_xform);
        text_log.PopIndent();
      }
    }

    const ON_SHA1_Hash subd_texture_settings_hash = this->TextureSettingsHash();
    text_log.Print(L"TextureSettingsHash() = ");
    subd_texture_settings_hash.Dump(text_log);
    text_log.PrintNewLine();

    // runtime settings most recently used to set fragment texture coordinates.
    const ON_SHA1_Hash frament_texture_settings_hash = this->FragmentTextureCoordinatesTextureSettingsHash();
    text_log.Print(L"FragmentTextureCoordinatesTextureSettingsHash() = ");
    if (subd_texture_settings_hash == frament_texture_settings_hash)
      text_log.Print(L"TextureSettingsHash()");
    else
      frament_texture_settings_hash.Dump(text_log);
    text_log.PrintNewLine();
  }

  if (false == bIsTextHash)
  {
    text_log.Print(L"Per vertex color settings:\n");
    {
      ON_TextLogIndent indent1(text_log);
      text_log.Print(L"ColorsMappingTag() = ");
      const ON_MappingTag colors_tag = this->ColorsMappingTag();
      const ON_TextLog::LevelOfDetail lod = text_log.DecreaseLevelOfDetail();
      colors_tag.Dump(text_log);
      text_log.SetLevelOfDetail(lod);
      const ON_SHA1_Hash subd_fragment_color_settings_hash = this->FragmentColorsSettingsHash();
      text_log.Print(L"FragmentColorsSettingsHash() = ");
      subd_fragment_color_settings_hash.Dump(text_log);
      text_log.PrintNewLine();
    }
  }

  bool bIncludeSymmetrySet = false;

  if (false == bIsTextHash)
  {
    text_log.Print(L"Geometry content serial number = %" PRIu64 "\n", geometry_content_sn);
    text_log.Print(L"Render content serial number = %" PRIu64 "\n", render_content_sn);
    text_log.Print("Heap use:\n");
    {
      ON_TextLogIndent indent1(text_log);
      size_t sizeof_subd = this->SizeOfAllElements();
      text_log.PrintString(ON_wString(L"Total = ") + ON_wString::ToMemorySize(sizeof_subd) + ON_wString(L".\n"));
      const size_t sizeof_frags = this->SizeOfAllMeshFragments();
      text_log.PrintString(ON_wString(L"Mesh fragments = ") + ON_wString::ToMemorySize(sizeof_frags) + ON_wString(L".\n"));
      const size_t sizeof_frags_waste = this->SizeOfUnusedMeshFragments();
      text_log.PrintString(ON_wString(L"Reserved but ununsed = ")
        + Internal_DescribeWaste(sizeof_frags_waste, sizeof_subd)
        + ON_wString(L".\n"));
    }
  }

  text_log.Print(L"Levels:\n");

  ON_SubDLevelIterator lit(subdimple->LevelIterator());

  const ON_2udex empty_id_range(ON_UNSET_UINT_INDEX, 0);

  ON_SubDVertexIdIterator vidit(*this); 
  ON_SubDEdgeIdIterator eidit(*this); 
  ON_SubDFaceIdIterator fidit(*this);

  unsigned int error_count = 0;
  for (const ON_SubDLevel* level = lit.First(); nullptr != level; level = lit.Next())
  {
    ON_TextLogIndent indent1(text_log);
    if (nullptr == level)
      continue;
    ON_2udex level_vertex_id_range
      = (0 != vertex_id_range.j || active_level_index == level->m_level_index)
      ? vertex_id_range
      : empty_id_range;
    ON_2udex level_edge_id_range
      = (0 != edge_id_range.j || active_level_index == level->m_level_index)
      ? edge_id_range
      : empty_id_range;
    ON_2udex level_face_id_range
      = (0 != face_id_range.j || active_level_index == level->m_level_index)
      ? face_id_range
      : empty_id_range;

    error_count += level->DumpTopology(
      *this,
      subdimple->MaximumVertexId(),
      subdimple->MaximumEdgeId(),
      subdimple->MaximumFaceId(),
      level_vertex_id_range,
      level_edge_id_range, 
      level_face_id_range,
      vidit,
      eidit,
      fidit,
      bIncludeSymmetrySet,
      text_log);
  }

  return error_count;
}

ON_SubDHashType ON_SubDHashTypeFromUnsigned(
  unsigned int subd_hash_type_as_unsigned
)
{
  switch (subd_hash_type_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDHashType::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDHashType::Topology);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDHashType::TopologyAndEdgeCreases);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDHashType::Geometry);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDHashType::Unset);
}

const ON_wString ON_SubDHashTypeToString(
  ON_SubDHashType subd_hash_type,
  bool bVerbose
)
{
  const wchar_t* name;
  switch (subd_hash_type)
  {
  case ON_SubDHashType::Unset:
    name = L"Unset";
    break;
  case ON_SubDHashType::Topology:
    name = L"Topology";
    break;
  case ON_SubDHashType::TopologyAndEdgeCreases:
    name = L"TopologyAndEdgeCreases";
    break;
  case ON_SubDHashType::Geometry:
    name = L"Geometry";
    break;
  default:
    name = L"invalid";
    break;
  }

  return bVerbose ? (ON_wString(L"ON_SubDHashType::") + ON_wString(name)) : ON_wString(name);
}

ON_SubDEndCapStyle ON_SubDEndCapStyleFromUnsigned(
  unsigned int subd_cap_style_as_unsigned
)
{
  switch (subd_cap_style_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDEndCapStyle::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDEndCapStyle::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDEndCapStyle::Triangles);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDEndCapStyle::Quads);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDEndCapStyle::Ngon);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDEndCapStyle::Unset);
}

const ON_wString ON_SubDEndCapStyleToString(
  ON_SubDEndCapStyle subd_cap_style,
  bool bVerbose
)
{
  const wchar_t* s;
  switch (subd_cap_style)
  {
  case ON_SubDEndCapStyle::Unset:
    s = L"Unset";
    break;
  case ON_SubDEndCapStyle::None:
    s = L"None";
    break;
  case ON_SubDEndCapStyle::Triangles:
    s = L"Triangles";
    break;
  case ON_SubDEndCapStyle::Quads:
    s = L"Quads";
    break;
  case ON_SubDEndCapStyle::Ngon:
    s = L"Ngon";
    break;
  default:
    s = L"invalid";
    break;
  }

  return ON_wString(s);
}

static void Internal_AccumulateVertexHash(
  ON_SHA1& sha1,
  ON_SubDHashType hash_type,
  const ON_SubDVertex* v
)
{
  sha1.AccumulateInteger32(v->m_id);
  if (ON_SubDHashType::Geometry == hash_type)
  {
    sha1.AccumulateBytes(&v->m_vertex_tag, sizeof(v->m_vertex_tag));
    sha1.AccumulateDoubleArray(3, v->m_P);
  }
}

static const ON_SHA1_Hash Internal_VertexHash(ON_SubDHashType hash_type, const ON_SubDVertex* first_vertex, unsigned int level_index, ON_SubDVertexIdIterator& vidit)
{
  ON_SHA1 sha1;
  if (ON_SubDHashType::Unset != hash_type)
  {
    unsigned prev_id = 0;
    for (const ON_SubDVertex* v = first_vertex; nullptr != v; v = v->m_next_vertex)
    {
      if (prev_id > v->m_id)
      {
        // must use slower vidit to get consistent results when complex editing juggles vertex order
        sha1.Reset();
        for (v = vidit.FirstVertex(); nullptr != v; v = vidit.NextVertex())
        {
          if ( level_index == v->SubdivisionLevel() && v->IsActive() )
            Internal_AccumulateVertexHash(sha1, hash_type, v);
        }
        break;
      }
      Internal_AccumulateVertexHash(sha1, hash_type, v);
      prev_id = v->m_id;
    }
  }
  return sha1.Hash();
}

const ON_SHA1_Hash ON_SubD::VertexHash(ON_SubDHashType hash_type) const
{
  ON_SubDVertexIdIterator vidit(*this);
  return Internal_VertexHash(hash_type, FirstVertex(), this->ActiveLevelIndex(), vidit);
}

const ON_SHA1_Hash ON_SubDimple::VertexHash(ON_SubDHashType hash_type) const
{
  ON_SubDVertexIdIterator vidit;
  this->InitializeVertexIdIterator(vidit);
  return Internal_VertexHash(hash_type, ActiveLevel().m_vertex[0], this->ActiveLevelIndex(), vidit);
}

static void Internal_AccumulateEdgeHash(
  ON_SHA1& sha1,
  ON_SubDHashType hash_type,
  const ON_SubDEdge* e
)
{
  sha1.AccumulateInteger32(e->m_id);
  sha1.AccumulateInteger32(e->VertexId(0));
  sha1.AccumulateInteger32(e->VertexId(1));

  if (ON_SubDHashType::TopologyAndEdgeCreases == hash_type || ON_SubDHashType::Geometry == hash_type)
  {
    // Changing edge crease/smooth attributes often changes the regions used in face packing and exploding.
    const bool bIsCrease = e->IsCrease();
    sha1.AccumulateBool(bIsCrease);
    if (false == bIsCrease && ON_SubDHashType::Geometry == hash_type && e->IsSharp())
    {
      const ON_SubDEdgeSharpness s = e->Sharpness(false);
      const double a[2] = { s[0] ,s[1] };
      sha1.AccumulateDoubleArray(2, a);
    }
  }
}


static const ON_SHA1_Hash Internal_EdgeHash(ON_SubDHashType hash_type, const ON_SubDEdge* first_edge, unsigned int level_index, ON_SubDEdgeIdIterator& eidit)
{
  ON_SHA1 sha1;
  if (ON_SubDHashType::Unset != hash_type)
  {
    unsigned prev_id = 0;
    for (const ON_SubDEdge* e = first_edge; nullptr != e; e = e->m_next_edge)
    {
      if (prev_id > e->m_id)
      {
        // must use slower eidit to get consistent results when complex editing juggles vertex order
        sha1.Reset();
        for (e = eidit.FirstEdge(); nullptr != e; e = eidit.NextEdge())
        {
          if (level_index == e->SubdivisionLevel() && e->IsActive())
            Internal_AccumulateEdgeHash(sha1, hash_type, e);
        }
        break;
      }
      Internal_AccumulateEdgeHash(sha1, hash_type, e);
      prev_id = e->m_id;
    }
  }
  return sha1.Hash();
}

const ON_SHA1_Hash ON_SubD::EdgeHash(ON_SubDHashType hash_type) const
{
  ON_SubDEdgeIdIterator eidit(*this);
  return Internal_EdgeHash(hash_type,FirstEdge(), this->ActiveLevelIndex(), eidit);
}


const ON_SHA1_Hash ON_SubDimple::EdgeHash(ON_SubDHashType hash_type) const
{
  ON_SubDEdgeIdIterator eidit;
  this->InitializeEdgeIdIterator(eidit);
  return Internal_EdgeHash(hash_type, ActiveLevel().m_edge[0], this->ActiveLevelIndex(), eidit);
}

static void Internal_AccumulateFaceHash(
  ON_SHA1& sha1,
  ON_SubDHashType hash_type,
  const ON_SubDFace* f
)
{
  sha1.AccumulateInteger32(f->m_id);
  sha1.AccumulateInteger16(f->m_edge_count);
  const ON_SubDEdgePtr* eptr = f->m_edge4;
  for (unsigned short fei = 0; fei < f->m_edge_count; ++fei, ++eptr)
  {
    if (4 == fei)
    {
      eptr = f->m_edgex;
      if (nullptr == eptr)
        break;
    }
    sha1.AccumulateInteger32(eptr->EdgeId());
    if (0 != ON_SUBD_EDGE_DIRECTION(eptr->m_ptr))
      sha1.AccumulateBool(true);
  }
}

static const ON_SHA1_Hash Internal_FaceHash(ON_SubDHashType hash_type, const ON_SubDFace* first_face, unsigned int level_index, ON_SubDFaceIdIterator& fidit)
{
  ON_SHA1 sha1;
  if (ON_SubDHashType::Unset != hash_type)
  {
    unsigned prev_id = 0;
    for (const ON_SubDFace* f = first_face; nullptr != f; f = f->m_next_face)
    {
      if (prev_id > f->m_id)
      {
        // must use slower fidit to get consistent results when complex editing juggles vertex order
        sha1.Reset();
        for (f = fidit.FirstFace(); nullptr != f; f = fidit.NextFace())
        {
          if (level_index == f->SubdivisionLevel() && f->IsActive())
            Internal_AccumulateFaceHash(sha1, hash_type, f);
        }
        break;
      }
      Internal_AccumulateFaceHash(sha1, hash_type, f);
      prev_id = f->m_id;
    }
  }
  return sha1.Hash();
}

const ON_SHA1_Hash ON_SubD::FaceHash(ON_SubDHashType hash_type) const
{
  ON_SubDFaceIdIterator fidit(*this);
  return Internal_FaceHash(hash_type,FirstFace(), this->ActiveLevelIndex(), fidit);
}

const ON_SHA1_Hash ON_SubDimple::FaceHash(ON_SubDHashType hash_type) const
{
  ON_SubDFaceIdIterator fidit;
  this->InitializeFaceIdIterator(fidit);
  return Internal_FaceHash(hash_type, ActiveLevel().m_face[0], this->ActiveLevelIndex(), fidit);
}


static void Internal_AccumulateFragmentColorArrayHash(ON_SHA1& sha1, const ON_Color* a, unsigned count, size_t stride)
{
  if (nullptr != a && count > 0)
  {
    sha1.AccumulateInteger32(count);
    for (unsigned i = 0; i < count; ++i)
    {
      const unsigned c = a[0];
      sha1.AccumulateInteger32(c);
      a += stride;
    }
  }
}

static void Internal_AccumulateFragmentArrayHash(ON_SHA1& sha1, size_t dim, const double* a, unsigned count, size_t stride)
{
  if (nullptr != a && count > 0 && dim > 0 && (0 == stride || stride >= dim))
  {
    sha1.AccumulateInteger32((unsigned int)dim);
    sha1.AccumulateInteger32(count);
    for (unsigned i = 0; i < count; ++i)
    {
      sha1.AccumulateDoubleArray(dim, a);
      a += stride;
    }
  }
}

const ON_SubDHash ON_SubDHash::Create(ON_SubDHashType hash_type, const class ON_SubD& subd)
{
  return ON_SubDHash::Create(hash_type, subd.SubDimple());
}

const ON_SubDHash ON_SubDHash::Create(ON_SubDHashType hash_type, const class ON_SubDimple* subdimple)
{
  if (nullptr == subdimple)
    return ON_SubDHash::Empty;

  const ON_SubDLevel& active_level = subdimple->ActiveLevel();
  ON_SubDHash h;
  h.m_hash_type = hash_type;
  h.m_vertex_count = active_level.m_vertex_count;
  h.m_edge_count = active_level.m_edge_count;
  h.m_face_count = active_level.m_face_count;
  h.m_subd_runtime_serial_number = subdimple->RuntimeSerialNumber;
  if (h.m_vertex_count > 0)
  {
    h.m_subd_geometry_content_serial_number = subdimple->GeometryContentSerialNumber();
    if (ON_SubDHashType::Unset != hash_type)
    {
      h.m_vertex_hash = subdimple->VertexHash(hash_type);
      h.m_edge_hash = subdimple->EdgeHash(hash_type);
      h.m_face_hash = subdimple->FaceHash(hash_type);
    }
  }
  return h;
}

int ON_SubDHash::Compare(const ON_SubDHash& lhs, const ON_SubDHash& rhs)
{
  if (lhs.m_vertex_count < rhs.m_vertex_count)
    return -1;
  if (lhs.m_vertex_count > rhs.m_vertex_count)
    return 1;

  if (lhs.m_edge_count < rhs.m_edge_count)
    return -1;
  if (lhs.m_edge_count > rhs.m_edge_count)
    return 1;

  if (lhs.m_face_count < rhs.m_face_count)
    return -1;
  if (lhs.m_face_count > rhs.m_face_count)
    return 1;

  int rc;

  rc = ON_SHA1_Hash::Compare(lhs.m_vertex_hash, rhs.m_vertex_hash);
  if (0 != rc)
    return rc;

  rc = ON_SHA1_Hash::Compare(lhs.m_edge_hash, rhs.m_edge_hash);
  if (0 != rc)
    return rc;

  return ON_SHA1_Hash::Compare(lhs.m_face_hash, rhs.m_face_hash);
}

void ON_SubDHash::Dump(ON_TextLog& text_log) const
{
  if (text_log.IsTextHash())
    return; 

  bool bIsNotEmpty = IsNotEmpty();

  if (bIsNotEmpty)
  {
    switch (this->HashType())
    {
    case ON_SubDHashType::Topology:
      text_log.Print("SubD toplogy hash:\n");
      break;
    case ON_SubDHashType::TopologyAndEdgeCreases:
      text_log.Print("SubD toplogy and edge creases hash:\n");
      break;
    case ON_SubDHashType::Geometry:
      text_log.Print("SubD geometry hash:\n");
      break;
    default:
      bIsNotEmpty = false;
      break;
    }
  }

  if (bIsNotEmpty)
  {
    const ON_TextLogIndent indent1(text_log);
    const unsigned vcount = this->VertexCount();
    const unsigned ecount = this->EdgeCount();
    const unsigned fcount = this->FaceCount();
    const ON_wString subdsha1 = this->SubDHash().ToStringEx(true);
    text_log.Print(L"SubD SHA1 = %ls\n", static_cast<const wchar_t*>(subdsha1));
    const ON_TextLogIndent indent2(text_log);
    if (vcount > 0)
    {
      const ON_wString vsha1 = this->VertexHash().ToStringEx(true);
      text_log.Print(L"%u vertices. SHA1 = %ls\n", vcount, static_cast<const wchar_t*>(vsha1));
    }
    else
      text_log.Print("No vertices.\n");

    if (ecount > 0)
    {
      const ON_wString esha1 = this->EdgeHash().ToStringEx(true);
      text_log.Print(L"%u edges. SHA1 = %ls\n", ecount, static_cast<const wchar_t*>(esha1));
    }
    else
      text_log.Print("No edges.\n");

    if (fcount > 0)
    {
      const ON_wString fsha1 = this->FaceHash().ToStringEx(true);
      text_log.Print(L"%u faces. SHA1 = %ls\n", fcount, static_cast<const wchar_t*>(fsha1));
    }
    else
      text_log.Print("No faces.\n");
  }
  else
    text_log.Print("SubD hash: Empty\n");
}

bool ON_SubDHash::Write(class ON_BinaryArchive& archive) const
{
  if (false == archive.BeginWrite3dmAnonymousChunk(1))
    return false;
  bool rc = false;
  for (;;)
  {
    const bool bIsEmpty = IsEmpty();
    if (false == archive.WriteBool(bIsEmpty))
      break;
    if (bIsEmpty)
    {
      rc = true;
      break;
    }
    // The SubD runtime serial number and geometry content serial numbers are runtime values.
    // When appropriate, calling contexts need to take appropriate steps when writing and 
    // set these after reading.
    const unsigned char hash_type_as_unsigned = static_cast<unsigned char>(m_hash_type);
    if (false == archive.WriteChar(hash_type_as_unsigned))
      break;
    if (false == archive.WriteInt(m_vertex_count))
      break;
    if (false == this->m_vertex_hash.Write(archive))
      break;
    if (false == archive.WriteInt(m_edge_count))
      break;
    if (false == this->m_edge_hash.Write(archive))
      break;
    if (false == archive.WriteInt(m_face_count))
      break;
    if (false == this->m_face_hash.Write(archive))
      break;
    rc = true;
    break;
  }
  if (false == archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_SubDHash::Read(class ON_BinaryArchive& archive)
{
  *this = ON_SubDHash::Empty;

  int chunk_version = 0;
  if (false == archive.BeginRead3dmAnonymousChunk(&chunk_version))
    return false;

  bool rc = false;
  for (;;)
  {
    bool bIsEmpty = true;
    if (false == archive.ReadBool(&bIsEmpty))
      break;
    if (bIsEmpty)
    {
      rc = true;
      break;
    }

    // The SubD runtime serial number and geometry content serial numbers are runtime values.
    // When appropriate, calling contexts need to set these after reading.
    unsigned char hash_type_as_unsigned = 0;
    if (false == archive.ReadChar(&hash_type_as_unsigned))
      break;
    m_hash_type = ON_SubDHashTypeFromUnsigned(hash_type_as_unsigned);

    if (false == archive.ReadInt(&m_vertex_count))
      break;
    if (false == this->m_vertex_hash.Read(archive))
      break;
    if (false == archive.ReadInt(&m_edge_count))
      break;
    if (false == this->m_edge_hash.Read(archive))
      break;
    if (false == archive.ReadInt(&m_face_count))
      break;
    if (false == this->m_face_hash.Read(archive))
      break;
    rc = true;
    break;
  }

  if (false == archive.EndRead3dmChunk())
    rc = false;
  return rc;

}

ON__UINT64 ON_SubDHash::SubDRuntimeSerialNumber() const
{
  return this->m_subd_runtime_serial_number;
}

ON__UINT64 ON_SubDHash::SubDGeometryContentSerialNumber() const
{
  return this->m_subd_geometry_content_serial_number;
}

bool ON_SubDHash::IsEmpty() const
{
  return ON_SubDHashType::Unset == m_hash_type || 0 == m_vertex_count;
}

bool ON_SubDHash::IsNotEmpty() const
{
  return ON_SubDHashType::Unset != m_hash_type && m_vertex_count > 0;
}

ON_SubDHashType ON_SubDHash::HashType() const
{
  return m_hash_type;
}

unsigned int ON_SubDHash::VertexCount() const
{
  return m_vertex_count;
}

unsigned int ON_SubDHash::EdgeCount() const
{
  return m_edge_count;
}

unsigned int ON_SubDHash::FaceCount() const
{
  return m_face_count;
}

const ON_SHA1_Hash ON_SubDHash::VertexHash() const
{
  return m_vertex_hash;
}

const ON_SHA1_Hash ON_SubDHash::EdgeHash() const
{
  return m_edge_hash;
}

const ON_SHA1_Hash ON_SubDHash::FaceHash() const
{
  return m_face_hash;
}

const ON_SHA1_Hash ON_SubDHash::SubDHash() const
{
  ON_SHA1 sha1;
  if (m_vertex_count > 0)
    sha1.AccumulateInteger32(m_vertex_count);
  if (m_edge_count > 0)
    sha1.AccumulateInteger32(m_edge_count);
  if (m_face_count > 0)
    sha1.AccumulateInteger32(m_face_count);
  if (ON_SubDHashType::Unset != m_hash_type)
  {
    if (m_vertex_count > 0)
      sha1.AccumulateSubHash(m_vertex_hash);
    if (m_edge_count > 0)
      sha1.AccumulateSubHash(m_edge_hash);
    if (m_face_count > 0)
      sha1.AccumulateSubHash(m_face_hash);
  }
  return sha1.Hash();
}

bool operator==(const ON_SubDHash& lhs, const ON_SubDHash& rhs)
{
  return 0 == ON_SubDHash::Compare(lhs, rhs);
}

bool operator!=(const ON_SubDHash& lhs, const ON_SubDHash& rhs)
{
  return 0 != ON_SubDHash::Compare(lhs, rhs);
}

static const ON_SHA1_Hash Internal_PackRectHash(const ON_SubDFace* first_face)
{
  ON_SHA1 sha1;
  for (const ON_SubDFace* f = first_face; nullptr != f; f = f->m_next_face)
  {
    if (false == f->PackRectIsSet())
      continue;
    sha1.AccumulateInteger32(f->m_id);
    sha1.AccumulateInteger16(f->m_edge_count);

    // The 4 f->TextureDomain...() values specify
    // the portion and orientation of texture space
    // this face uses.
    sha1.AccumulateInteger32(f->PackRectRotationDegrees());
    const ON_2dPoint p = f->PackRectOrigin();
    sha1.Accumulate2dPoint(p);
    const ON_2dVector v = f->PackRectSize();
    sha1.Accumulate2dVector(v);
  }
  return sha1.Hash();
}

static const ON_SHA1_Hash Internal_TextureCoordinatesHash(const ON_SubDFace* first_face)
{
  ON_SHA1 sha1;
  bool bNotEmpty = false;
  for (const ON_SubDFace* f = first_face; nullptr != f; f = f->m_next_face)
  {
    if (false == f->PackRectIsSet())
      continue;
    const ON_SubDMeshFragment* first_frag = f->MeshFragments();
    if (nullptr == first_frag)
      continue;
    sha1.AccumulateInteger32(f->m_id);
    for (const ON_SubDMeshFragment* frag = first_frag; nullptr != frag; frag = frag->NextFaceFragment(false))
    {
      const double* a = frag->TextureCoordinateArray(ON_SubDComponentLocation::Surface);
      const unsigned count = frag->TextureCoordinateCount();
      if (nullptr != a && count > 0)
      {
        bNotEmpty = true;
        Internal_AccumulateFragmentArrayHash(sha1, 3, a, count, frag->TextureCoordinateArrayStride(ON_SubDComponentLocation::Surface));
      }
    }
  }
  return bNotEmpty ? sha1.Hash() : ON_SHA1_Hash::EmptyContentHash;
}

static const ON_SHA1_Hash Internal_FragmentColorsHash(const ON_SubDFace* first_face)
{
  ON_SHA1 sha1;
  bool bNotEmpty = false;
  for (const ON_SubDFace* f = first_face; nullptr != f; f = f->m_next_face)
  {
    const ON_SubDMeshFragment* first_frag = f->MeshFragments();
    if (nullptr == first_frag)
      continue;
    bool bAccumulateId = true;
    for (const ON_SubDMeshFragment* frag = first_frag; nullptr != frag; frag = frag->NextFaceFragment(false))
    {
      const unsigned count = frag->ColorArrayCount(ON_SubDComponentLocation::Surface);
      if (count > 0)
      {
        const ON_Color* a = frag->ColorArray(ON_SubDComponentLocation::Surface);
        if (nullptr != a && count > 0)
        {
          bNotEmpty = true;
          if (bAccumulateId)
          {
            sha1.AccumulateInteger32(f->m_id);
            bAccumulateId = false;
          }
          sha1.AccumulateInteger32Array(count, (const ON__INT32*)a);
        }
      }
    }
  }
  return bNotEmpty ? sha1.Hash() : ON_SHA1_Hash::EmptyContentHash;
}

static const ON_SHA1_Hash Internal_FragmentCurvaturesHash(const ON_SubDFace* first_face)
{
  ON_SHA1 sha1;
  bool bNotEmpty = false;
  for (const ON_SubDFace* f = first_face; nullptr != f; f = f->m_next_face)
  {
    const ON_SubDMeshFragment* first_frag = f->MeshFragments();
    if (nullptr == first_frag)
      continue;
    bool bAccumulateId = true;
    for (const ON_SubDMeshFragment* frag = first_frag; nullptr != frag; frag = frag->NextFaceFragment(false))
    {
      const unsigned count = frag->CurvatureArrayCount(ON_SubDComponentLocation::Surface);
      if (count > 0)
      {
        const ON_SurfaceCurvature* a = frag->CurvatureArray(ON_SubDComponentLocation::Surface);
        if (nullptr != a && count > 0)
        {
          bNotEmpty = true;
          if (bAccumulateId)
          {
            sha1.AccumulateInteger32(f->m_id);
            bAccumulateId = false;
          }
          Internal_AccumulateFragmentArrayHash(sha1, 2, (const double*)a, count, 2);
        }
      }
    }
  }
  return bNotEmpty ? sha1.Hash() : ON_SHA1_Hash::EmptyContentHash;
}


unsigned int ON_SubDLevel::DumpTopology(
  const ON_SubD& parent_subd,
  const unsigned int validate_max_vertex_id,
  const unsigned int validate_max_edge_id,
  const unsigned int validate_max_face_id,
  ON_2udex vertex_id_range,
  ON_2udex edge_id_range,
  ON_2udex face_id_range,
  ON_SubDVertexIdIterator& vidit,
  ON_SubDEdgeIdIterator& eidit,
  ON_SubDFaceIdIterator& fidit,
  bool bIncludeSymmetrySet,
  ON_TextLog& text_log
) const
{
  // NOTE WELL:
  //  This is a debugging tool.
  //  The code in this function needs to work when the topology information is corrupt.
  const unsigned short level_index = (unsigned short)m_level_index;

  const unsigned int vertex_max_dump_count 
    = (vertex_id_range.i > 0 && vertex_id_range.i != ON_UNSET_UINT_INDEX && 0 == vertex_id_range.j)
    ? vertex_id_range.i 
    : 0;
  const unsigned int edge_max_dump_count 
    = (edge_id_range.i > 0 && edge_id_range.i != ON_UNSET_UINT_INDEX && 0 == edge_id_range.j)
    ? edge_id_range.i
    : 0;
  const unsigned int face_max_dump_count 
    = (face_id_range.i > 0 && face_id_range.i != ON_UNSET_UINT_INDEX && 0 == face_id_range.j)
    ? face_id_range.i 
    : 0;

  const bool bVertexIdTest = (vertex_max_dump_count > 0) || (vertex_id_range.i < vertex_id_range.j) || (ON_UNSET_UINT_INDEX == (vertex_id_range.i));
  const bool bEdgeIdTest =  (edge_max_dump_count > 0) || (edge_id_range.i < edge_id_range.j) || (ON_UNSET_UINT_INDEX == (edge_id_range.i));
  const bool bFaceIdTest =  (face_max_dump_count > 0) || (face_id_range.i < face_id_range.j) || (ON_UNSET_UINT_INDEX == (face_id_range.i));

  const char error_code_point = '!';
  char prefix[16] = {};

  unsigned int vertex_error_count = 0;
  unsigned int edge_error_count = 0;
  unsigned int face_error_count = 0;

  text_log.Print(L"SubD level %u topology: %u vertices, %u edges", m_level_index, m_vertex_count, m_edge_count);


  unsigned int wire_edge_count = 0U;
  unsigned int boundary_edge_count = 0U;  
  unsigned int interior_edge_count = 0U;
  unsigned int nonmanifold_edge_count = 0U;
  for (const ON_SubDEdge* e = m_edge[0]; nullptr != e; e = e->m_next_edge)
  {
    if (0 == e->m_face_count)
      ++wire_edge_count;
    else if (1 == e->m_face_count)
      ++boundary_edge_count;
    else if (2 == e->m_face_count)
      ++interior_edge_count;
    else if (e->m_face_count >= 3)
      ++nonmanifold_edge_count;
  }

  if (wire_edge_count > 0U)
  {
    if (nonmanifold_edge_count > 0U)
    {
      if (boundary_edge_count > 0U && interior_edge_count > 0U)
        text_log.Print(L" (%u boundary, %u interior, %u wire, %u nonmanifold)", boundary_edge_count, interior_edge_count, wire_edge_count, nonmanifold_edge_count);
      else if (boundary_edge_count > 0U)
        text_log.Print(L" (%u boundary, %u wire, %u nonmanifold)", boundary_edge_count, wire_edge_count, nonmanifold_edge_count);
      else if (interior_edge_count > 0U)
        text_log.Print(L" (%u interior, %u wire, %u nonmanifold)", interior_edge_count, wire_edge_count, nonmanifold_edge_count);
      else
        text_log.Print(L" (%u wire, %u nonmanifold)", wire_edge_count, nonmanifold_edge_count);
    }
    else
    {
      if (boundary_edge_count > 0U && interior_edge_count > 0U)
        text_log.Print(L" (%u boundary, %u interior, %u wire)", boundary_edge_count, interior_edge_count, wire_edge_count);
      else if (boundary_edge_count > 0U)
        text_log.Print(L" (%u boundary, %u wire)", boundary_edge_count, wire_edge_count);
      else if (interior_edge_count > 0U)
        text_log.Print(L" (%u interior, %u wire)", interior_edge_count, wire_edge_count);
      else
        text_log.Print(L" (%u wire)", wire_edge_count);
    }
  }
  else if (nonmanifold_edge_count > 0U)
  {
    if (boundary_edge_count > 0U && interior_edge_count > 0U)
      text_log.Print(L" (%u boundary, %u interior, %u nonmanifold)", boundary_edge_count, interior_edge_count, nonmanifold_edge_count);
    else if (boundary_edge_count > 0U)
      text_log.Print(L" (%u boundary, %u nonmanifold)", boundary_edge_count, nonmanifold_edge_count);
    else if (interior_edge_count > 0U)
      text_log.Print(L" (%u interior, %u nonmanifold)", interior_edge_count, nonmanifold_edge_count);
    else
      text_log.Print(L" (%u nonmanifold)", nonmanifold_edge_count);
  }
  else if (boundary_edge_count > 0U && interior_edge_count > 0U)
  {
    text_log.Print(L" (%u boundary, %u interior)", boundary_edge_count, interior_edge_count);
  }

  text_log.Print(L", ");

  unsigned int ngon_count[65] = {};
  unsigned int maxN = (unsigned int)(sizeof(ngon_count) / sizeof(ngon_count[0])) - 1;

  unsigned int face_count = 0;
  unsigned int uniformN = 0;
  for (const ON_SubDFace* f = m_face[0]; nullptr != f; f = f->m_next_face)
  {
    if (face_count >= m_face_count && f->SubdivisionLevel() != level_index)
      break;
    face_count++;
    unsigned int N = f->EdgeCount();
    if (1 == face_count)
      uniformN = N;
    else if (N != uniformN)
      uniformN = 0;
    unsigned int j = (N < maxN) ? N : maxN;
    if (N < maxN)
      ngon_count[j]++;
  }

  if (face_count != m_face_count)
    face_error_count++;


  if (uniformN > 0 && face_count == m_face_count)
  {
    if (3 == uniformN)
      text_log.Print(L"%u triangles\n", m_face_count);
    else if (4 == uniformN)
      text_log.Print(L"%u quads\n", m_face_count);
    else
      text_log.Print(L"%u %u-gons\n", m_face_count, uniformN);
  }
  else
  {
    text_log.Print(L"%u faces\n", m_face_count );
    text_log.PushIndent();
    for (unsigned int N = 0; N <= maxN; N++)
    {
      if (0 == ngon_count[N])
        continue;
      if (3 == N)
        text_log.Print(L"%u triangles\n", ngon_count[N]);
      else if (4 == N)
        text_log.Print(L"%u quads\n", ngon_count[N]);
      else if (N < maxN)
        text_log.Print(L"%u %u-gons\n", ngon_count[N], N);
      else
        text_log.Print(L"%u N-gons\n", ngon_count[N]);
    }
    text_log.PopIndent();
  }

  if (IsEmpty())
    return 0;

  // The hash uniquely identifies the subd level topology and geometry.
  const ON_SubDHashType hash_type = ON_SubDHashType::Geometry;
  const ON_SHA1_Hash vhash = Internal_VertexHash(hash_type, m_vertex[0], this->m_level_index, vidit);
  const ON_SHA1_Hash ehash = Internal_EdgeHash(hash_type, m_edge[0], this->m_level_index, eidit);
  const ON_SHA1_Hash fhash = Internal_FaceHash(hash_type, m_face[0], this->m_level_index, fidit);

  ON_SHA1 level_sha1;
  level_sha1.AccumulateSubHash(vhash);
  level_sha1.AccumulateSubHash(ehash);
  level_sha1.AccumulateSubHash(fhash);
  const ON_wString hashstr = level_sha1.Hash().ToString(true);
  text_log.Print(L"Level SubD geometry SHA1 = %ls\n", static_cast<const wchar_t*>(hashstr));

  const ON_wString vhashstr = vhash.ToStringEx(true);
  const ON_wString ehashstr = ehash.ToStringEx(true);
  const ON_wString fhashstr = fhash.ToStringEx(true);
  text_log.Print(L"Vertices SHA1 = %ls\n", static_cast<const wchar_t*>(vhashstr));
  text_log.Print(L"Edges SHA1 = %ls\n", static_cast<const wchar_t*>(ehashstr));
  text_log.Print(L"Faces SHA1 = %ls\n", static_cast<const wchar_t*>(fhashstr));

  if (false == text_log.IsTextHash())
  {
    const ON_SHA1_Hash prhash = Internal_PackRectHash(m_face[0]);
    const ON_SHA1_Hash tchash = Internal_TextureCoordinatesHash(m_face[0]);
    const ON_SHA1_Hash chash = Internal_FragmentColorsHash(m_face[0]);
    const ON_SHA1_Hash khash = Internal_FragmentCurvaturesHash(m_face[0]);
    const ON_wString prhashstr = prhash.ToStringEx(true);
    const ON_wString tchashstr = tchash.ToStringEx(true);
    const ON_wString chashstr = chash.ToStringEx(true);
    const ON_wString khashstr = khash.ToStringEx(true);
    text_log.Print(L"Faces pack rectangles SHA1 = %ls\n", static_cast<const wchar_t*>(prhashstr));
    text_log.Print(L"Faces fragment texture coordinates SHA1 = %ls\n", static_cast<const wchar_t*>(tchashstr));
    text_log.Print(L"Faces fragment vertex colors SHA1 = %ls\n", static_cast<const wchar_t*>(chashstr));
    text_log.Print(L"Faces fragment vertex curvatures SHA1 = %ls\n", static_cast<const wchar_t*>(khashstr));
  }
  unsigned int damaged_vertex_count = 0;
  unsigned int damaged_edge_count = 0;
  unsigned int damaged_face_count = 0;
  enum : unsigned int
  {
    damaged_id_list_capacity = 8
  };
  for (;;)
  {
    unsigned int damaged_vertex_id[damaged_id_list_capacity] = {};
    unsigned int damaged_edge_id[damaged_id_list_capacity] = {};
    unsigned int damaged_face_id[damaged_id_list_capacity] = {};
    for (const ON_SubDVertex* v = m_vertex[0]; nullptr != v; v = v->m_next_vertex)
    {
      if (false == v->m_status.IsDamaged())
        continue;
      if (damaged_vertex_count < damaged_id_list_capacity)
        damaged_vertex_id[damaged_vertex_count] = v->m_id;
      ++damaged_vertex_count;
    }
    for (const ON_SubDEdge* e = m_edge[0]; nullptr != e; e = e->m_next_edge)
    {
      if (false == e->m_status.IsDamaged())
        continue;
      if (damaged_edge_count < damaged_id_list_capacity)
        damaged_edge_id[damaged_edge_count] = e->m_id;
      ++damaged_edge_count;
    }
    for (const ON_SubDFace* f = m_face[0]; nullptr != f; f = f->m_next_face)
    {
      if (false == f->m_status.IsDamaged())
        continue;
      if (damaged_face_count < damaged_id_list_capacity)
        damaged_face_id[damaged_face_count] = f->m_id;
      ++damaged_face_count;
    }

    if (0U == damaged_vertex_count && 0U == damaged_edge_count && 0U == damaged_face_count)
      break;
    text_log.Print("DAMAGED SubD level:\n");
    ON_TextLogIndent indent1(text_log);
    if (damaged_vertex_count > 0)
    {
      text_log.Print(L"%u DAMAGED vertices: ", damaged_vertex_count);
      text_log.Print("v%u", damaged_vertex_id[0]);
      for (unsigned i = 1U; i < damaged_vertex_count; ++i)
        text_log.Print(", v%u", damaged_vertex_id[i]);
      if (damaged_vertex_count > damaged_id_list_capacity)
        text_log.Print(", ...");
      text_log.PrintNewLine();
    }
    if (damaged_edge_count > 0)
    {
      text_log.Print(L"%u DAMAGED edges: ", damaged_edge_count);
      text_log.Print("e%u", damaged_edge_id[0]);
      for (unsigned i = 1U; i < damaged_edge_count; ++i)
        text_log.Print(", e%u", damaged_edge_id[i]);
      if (damaged_edge_count > damaged_id_list_capacity)
        text_log.Print(", ...");
      text_log.PrintNewLine();
    }
    if (damaged_face_count > 0)
    {
      text_log.Print(L"%u DAMAGED faces: ", damaged_face_count);
      text_log.Print("f%u", damaged_face_id[0]);
      for (unsigned i = 1U; i < damaged_face_count; ++i)
        text_log.Print(", f%u", damaged_face_id[i]);
      if (damaged_face_count > damaged_id_list_capacity)
        text_log.Print(", ...");
      text_log.PrintNewLine();
    }
    break;
  }

  ///////////////////////////////////////////////////////////////////
  //
  // Vertex Topology
  // vN (x, y, z)
  //   vEdges[vertex_edge_count] = { +eA, -eB, ... }
  //   vFaces[vertex_edge_count] = { fP, fQ, fR, ... }
  //
  damaged_vertex_count = 0U;
  unsigned int vertex_count = 0;
  unsigned int vertex_dump_count = 0;
  ON_2udex skipped_vertex_id = ON_2udex::Zero;
  unsigned int max_vertex_id = 0;
  bool bSkippedPreviousComponent = false;
  for (const ON_SubDVertex* v = m_vertex[0]; nullptr != v; v = v->m_next_vertex)
  {
    if (vertex_count >= m_vertex_count && v->SubdivisionLevel() != level_index)
      break;
    if (v->m_id > max_vertex_id)
      max_vertex_id = v->m_id;

    vertex_count++;
    const bool bIsDamaged = v->m_status.IsDamaged();
    if (bIsDamaged)
      ++damaged_vertex_count;

    if (bVertexIdTest && (false == bIsDamaged || damaged_vertex_count > damaged_id_list_capacity))
    {
      bool bSkip = true;
      for (;;)
      {
        if (ON_UNSET_UINT_INDEX == vertex_id_range.i)
          break;
        if (vertex_max_dump_count > 0)
        {
          if (vertex_count > vertex_max_dump_count)
            break;
        }
        else
        {
          if (v->m_id < vertex_id_range.i || v->m_id >= vertex_id_range.j)
            break;
        }
        bSkip = false;
        break;
      }
      if (bSkip)
      {
        if (0 == skipped_vertex_id.j)
        {
          skipped_vertex_id.i = v->m_id;
          skipped_vertex_id.j = v->m_id;
        }
        else if (v->m_id < skipped_vertex_id.i)
          skipped_vertex_id.i = v->m_id;
        else if (v->m_id > skipped_vertex_id.j)
          skipped_vertex_id.j = v->m_id;
        bSkippedPreviousComponent = true;
        continue;
      }
    }

    if (0 == vertex_dump_count)
      text_log.Print(L"Vertices:\n");
    vertex_dump_count++;
    ON_TextLogIndent vindent(text_log);

    const ON_3dPoint P0(v->ControlNetPoint());

    const ON_wString vtag = ON_SubD::VertexTagToString(v->m_vertex_tag,false);

    if (bSkippedPreviousComponent)
    {
      text_log.Print(L"...\n");
      bSkippedPreviousComponent = false;
    }

    {
      ON_String s = ON_String::FormatToString("v%u: ",v->m_id);

      if (bIsDamaged)
        s += "(DAMAGED) ";

      s += ON_String::FormatToString(
          "%ls (%g, %g, %g)",
          static_cast<const wchar_t*>(vtag),
          P0.x, P0.y, P0.z
        );
      if (v->m_group_id > 0)
        s += ON_String::FormatToString(" group_id=%u", v->m_group_id);      
      //s += ON_String::FormatToString(" CRC32=%u", v->TopologyCRC32(true));
      text_log.PrintString(s);
      text_log.PrintNewLine();
    }

    text_log.PushIndent();

    const double vs = v->VertexSharpness();
    if (false == (0.0 == vs))
    {
      const ON_wString vspct = ON_SubDEdgeSharpness::ToPercentageText(vs);
      text_log.Print(L"v.VertexSharpness = %ls (%g)\n", static_cast<const wchar_t*>(vspct), vs);
    }

    ON_3dPoint P1(ON_3dPoint::NanPoint);
    if (v->GetSavedSubdivisionPoint(&P1.x) && P1.IsValid())
      text_log.Print( "v.SubdivisionPoint: (%g, %g, %g)\n", P1.x, P1.y, P1.z );

    ON_3dPoint S(ON_3dPoint::NanPoint);
    if (v->GetSavedSurfacePoint(&S.x) && S.IsValid())
      text_log.Print( "v.SurfacePoint: (%g, %g, %g)\n", S.x, S.y, S.z );

    const unsigned int vertex_edge_count = v->m_edge_count;
    text_log.Print("v.Edges[%u] = ", vertex_edge_count);
    prefix[0] = '{';
    prefix[1] = ON_String::Space;
    prefix[2] = error_code_point;
    prefix[3] = 'e';
    prefix[4] = '%';
    prefix[5] = 'u';
    prefix[6] = 0;
    for (unsigned int vei = 0; vei < vertex_edge_count; vei++)
    {
      if (1 == vei)
        prefix[0] = ',';
      prefix[2] = error_code_point;
      const ON_SubDEdge* e = v->Edge(vei);
      if (nullptr != e)
      {
        if (v == e->m_vertex[0] && v != e->m_vertex[1])
          prefix[2] = '+';
        else if (v != e->m_vertex[0] && v == e->m_vertex[1])
          prefix[2] = '-';
        else
          vertex_error_count++;
        text_log.Print(prefix, e->m_id);
      }
      else
      {
        text_log.Print("%c %c", prefix[0], error_code_point);
        vertex_error_count++;
      }
    }
    text_log.Print(" }\n");

    const unsigned int vertex_face_count = v->m_face_count;
    text_log.Print("v.Faces[%u] = ", vertex_face_count);
    prefix[0] = '{';
    prefix[1] = ON_String::Space;
    prefix[2] = 'f';
    prefix[3] = '%';
    prefix[4] = 'u';
    prefix[5] = 0;
    for (unsigned int vfi = 0; vfi < vertex_face_count; vfi++)
    {
      if (1 == vfi)
        prefix[0] = ',';
      const ON_SubDFace* f = v->Face(vfi);
      if (nullptr != f)
        text_log.Print(prefix, f->m_id);
      else
      {
        text_log.Print("%c %c", prefix[0], error_code_point);
        vertex_error_count++;
      }
    }
    text_log.Print(" }\n");
    text_log.PopIndent();
  }

  text_log.PushIndent();
  if (vertex_dump_count > 0 && vertex_dump_count < vertex_count)
  {
    text_log.Print(
      L"... %u additional vertices (v%u to v%u).\n", 
      vertex_count-vertex_dump_count,
      skipped_vertex_id.i,
      skipped_vertex_id.j
    );
  }
  text_log.Print("Maximum vertex id = %u.  ",max_vertex_id);
  if (validate_max_vertex_id >= max_vertex_id)
    text_log.Print("Next id = %u.\n", validate_max_vertex_id + 1);
  else
    text_log.Print("ERROR Next id = %u.\n", validate_max_vertex_id + 1);
  text_log.PopIndent();

  ///////////////////////////////////////////////////////////////////
  //
  // Edge Topology
  // eN (+vA, -vB)
  //   eFaces[edge_face_count] = { fP, fQ, fR, ... }
  //
  damaged_edge_count = 0U;
  wire_edge_count = 0U;
  nonmanifold_edge_count = 0U;
  unsigned int edge_count = 0;
  unsigned int edge_dump_count = 0;
  ON_2udex skipped_edge_id = ON_2udex::Zero;
  unsigned int max_edge_id = 0;
  bSkippedPreviousComponent = false;
  for (const ON_SubDEdge* e = m_edge[0]; nullptr != e; e = e->m_next_edge)
  {
    if (edge_count >= m_edge_count && e->SubdivisionLevel() != level_index)
      break;
    if (e->m_id > max_edge_id)
      max_edge_id = e->m_id;
    edge_count++;

    const bool bIsDamaged = e->m_status.IsDamaged();
    if (bIsDamaged)
      ++damaged_edge_count;
    const bool bIsWireEdge = (0U == e->m_face_count);
    if (bIsWireEdge)
      ++wire_edge_count;
    const bool bIsNonmanifoldEdge = (e->m_face_count >= 3U);
    if (bIsNonmanifoldEdge)
      ++nonmanifold_edge_count;

    if (
      bEdgeIdTest 
      && (false == bIsDamaged || damaged_edge_count > damaged_id_list_capacity)
      && (false == bIsWireEdge || wire_edge_count > damaged_id_list_capacity)
      && (false == bIsNonmanifoldEdge || nonmanifold_edge_count > damaged_id_list_capacity)
      )
    {
      bool bSkip = true;
      for (;;)
      {
        if (ON_UNSET_UINT_INDEX == edge_id_range.i)
          break;
        if (edge_max_dump_count > 0)
        {
          if (edge_count > edge_max_dump_count)
            break;
        }
        else
        {
          if (e->m_id < edge_id_range.i || e->m_id >= edge_id_range.j)
            break;
        }
        bSkip = false;
        break;
      }
      if (bSkip)
      {
        if (0 == skipped_edge_id.j)
        {
          skipped_edge_id.i = e->m_id;
          skipped_edge_id.j = e->m_id;
        }
        else if (e->m_id < skipped_edge_id.i)
          skipped_edge_id.i = e->m_id;
        else if (e->m_id > skipped_edge_id.j)
          skipped_edge_id.j = e->m_id;
        bSkippedPreviousComponent = true;
        continue;
      }
    }

    if (0 == edge_dump_count)
      text_log.Print(L"Edges:\n");
    edge_dump_count++;
    ON_TextLogIndent eindent(text_log);

    const ON_wString etag = ON_SubD::EdgeTagToString(e->m_edge_tag,false);

    if (bSkippedPreviousComponent)
    {
      text_log.Print(L"...\n");
      bSkippedPreviousComponent = false;
    }

    {
      ON_String s = ON_String::FormatToString("e%u: ", e->m_id);
      if (bIsDamaged)
        s += "(DAMAGED) ";

      if (bIsWireEdge)
      {
        s += ON_String::FormatToString(
          "wire %ls ",
          static_cast<const wchar_t*>(etag)
        );
      }
      else if (bIsNonmanifoldEdge)
      {
        s += ON_String::FormatToString(
          "nonmanifold %ls ",
          static_cast<const wchar_t*>(etag)
        );
      }
      else
      {
        s += ON_String::FormatToString(
          "%ls ",
          static_cast<const wchar_t*>(etag)
        );
      }

      s += "( ";
      prefix[0] = 'v';
      prefix[1] = '%';
      prefix[2] = 'u';
      prefix[3] = 0;
      for (unsigned int evi = 0; evi < 2; evi++)
      {
        if (1 == evi)
          s += " to ";
        const ON_SubDVertex* v = e->m_vertex[evi];
        if (nullptr != v)
          s += ON_String::FormatToString(prefix, v->m_id);
        else
        {
          s += error_code_point;
          edge_error_count++;
        }
      }
      s += " )";

      //s += ON_String::FormatToString(" CRC32=%u", e->TopologyCRC32(true));

      if (e->m_group_id > 0)
        s += ON_String::FormatToString(" group_id=%u", e->m_group_id);

      text_log.PrintString(s);
      text_log.PrintNewLine();
    }

    text_log.PushIndent();

    if (e->IsSharp())
    {
      const ON_SubDEdgeSharpness sharpness = e->Sharpness(false);
      const ON_wString ss = sharpness.ToPercentageText(false);
      ON_wString s 
        = (sharpness.IsConstant())
        ? ON_String::FormatToString("e.Sharpness: %ls (%g)", static_cast<const wchar_t*>(ss), sharpness.EndSharpness(0))
        : ON_String::FormatToString("e.Sharpness: %ls (%g-%g)", static_cast<const wchar_t*>(ss), sharpness.EndSharpness(0), sharpness.EndSharpness(1));
      text_log.PrintString(s);
      text_log.PrintNewLine();
    }

    ON_3dPoint P1(ON_3dPoint::NanPoint);
    if (e->GetSavedSubdivisionPoint(&P1.x) && P1.IsValid())
      text_log.Print( "e.SubdivisionPoint: (%g, %g, %g)\n", P1.x, P1.y, P1.z );

    const unsigned int edge_face_count = e->m_face_count;
    text_log.Print("e.Faces[%u] = ", edge_face_count);
    prefix[0] = '{';
    prefix[1] = ON_String::Space;
    prefix[2] = error_code_point;
    prefix[3] = 'f';
    prefix[4] = '%';
    prefix[5] = 'u';
    prefix[6] = 0;
    for (unsigned int efi = 0; efi < edge_face_count; efi++)
    {
      if (1 == efi)
        prefix[0] = ',';
      prefix[2] = error_code_point;
      ON_SubDFacePtr fptr = e->FacePtr(efi);
      const ON_SubDFace* f = fptr.Face();
      const ON__UINT_PTR edge_fdir = fptr.FaceDirection();
      if (nullptr != f)
      {
        ON_SubDEdgePtr eptr = f->EdgePtrFromEdge(e);
        if (eptr.Edge() == e && eptr.EdgeDirection() == edge_fdir)
          prefix[2] = ((0 == edge_fdir) ? '+' : '-');
        else
          edge_error_count++;
        text_log.Print(prefix, f->m_id);
      }
      else
      {
        text_log.Print("%c %c", prefix[0], error_code_point);
        edge_error_count++;
      }
    }
    text_log.Print(" }\n");


    text_log.PopIndent();
  }

  text_log.PushIndent();
  if (edge_dump_count > 0 && edge_dump_count < edge_count)
  {
    text_log.Print(L"... %u additional edges (e%u to e%u).\n",
      edge_count - edge_dump_count,
      skipped_edge_id.i,
      skipped_edge_id.j
    );
  }
  text_log.Print("Maximum edge id = %u.  ",max_edge_id);
  if (validate_max_edge_id >= max_edge_id)
    text_log.Print("Next id = %u.\n", validate_max_edge_id + 1);
  else
    text_log.Print("ERROR Next id = %u.\n", validate_max_edge_id + 1);
  text_log.PopIndent();


  ///////////////////////////////////////////////////////////////////
  //
  // Face Topology
  // fN
  //   fEdges[face_edge_count] = { +eA, -eB, +eC, ...}
  //   fVertices[face_edge_count] = { vP, vQ, vR, ... }
  //
  damaged_face_count = 0U;
  face_count = 0;
  unsigned int face_dump_count = 0;
  ON_2udex skipped_face_id = ON_2udex::Zero;
  unsigned int max_face_id = 0;
  bSkippedPreviousComponent = false;
  for (const ON_SubDFace* f = m_face[0]; nullptr != f; f = f->m_next_face)
  {
    if (face_count >= m_face_count && f->SubdivisionLevel() != level_index)
      break;
    if (f->m_id > max_face_id)
      max_face_id = f->m_id;
    face_count++;

    const bool bIsDamaged = f->m_status.IsDamaged();
    if (bIsDamaged)
      ++damaged_face_count;

    if (bFaceIdTest && (false == bIsDamaged || damaged_face_count > damaged_id_list_capacity))
    {
      bool bSkip = true;
      for (;;)
      {
        if (ON_UNSET_UINT_INDEX == face_id_range.i)
          break;
        if (face_max_dump_count > 0)
        {
          if (face_count > face_max_dump_count)
            break;
        }
        else
        {
          if (f->m_id < face_id_range.i || f->m_id >= face_id_range.j)
            break;
        }
        bSkip = false;
        break;
      }
      if (bSkip)
      {
        if (0 == skipped_face_id.j)
        {
          skipped_face_id.i = f->m_id;
          skipped_face_id.j = f->m_id;
        }
        else if (f->m_id < skipped_face_id.i)
          skipped_face_id.i = f->m_id;
        else if (f->m_id > skipped_face_id.j)
          skipped_face_id.j = f->m_id;
        bSkippedPreviousComponent = true;
        continue;
      }
    }

    if (0 == face_dump_count)
      text_log.Print(L"Faces:\n");
    face_dump_count++;
    ON_TextLogIndent eindent(text_log);

    if (bSkippedPreviousComponent)
    {
      text_log.Print(L"...\n");
      bSkippedPreviousComponent = false;
    }
    if (bIsDamaged)
    {
      text_log.Print(
        "f%u (DAMAGED):\n",
        f->m_id
      );
    }
    else
    {
      ON_String s = ON_String::FormatToString("f%u:", f->m_id);

      //s += ON_String::FormatToString(" CRC32=%u", f->TopologyCRC32(true));

      if (f->m_group_id > 0)
        s += ON_String::FormatToString(" group_id=%u", f->m_group_id);
      text_log.PrintString(s);
      text_log.PrintNewLine();
    }

    text_log.PushIndent();

    ON_3dPoint P1(ON_3dPoint::NanPoint);
    if (f->GetSavedSubdivisionPoint(&P1.x) && P1.IsValid())
      text_log.Print( "f.SubdivisionPoint: (%g, %g, %g)\n", P1.x, P1.y, P1.z );


    const unsigned int face_edge_count = f->m_edge_count;
    text_log.Print("f.Edges[%u] = ", face_edge_count);
    prefix[0] = '{';
    prefix[1] = ON_String::Space;
    prefix[2] = error_code_point;
    prefix[3] = 'e';
    prefix[4] = '%';
    prefix[5] = 'u';
    prefix[6] = 0;
    for (unsigned int fei = 0; fei < face_edge_count; fei++)
    {
      if (1 == fei)
        prefix[0] = ',';
      prefix[2] = error_code_point;
      const ON_SubDEdgePtr eptr = f->EdgePtr(fei);
      const ON_SubDEdge* e = eptr.Edge();
      const ON__UINT_PTR face_edir = eptr.EdgeDirection();
      if (nullptr != e)
      {
        ON_SubDFacePtr fptr = e->FacePtrFromFace(f);
        if (fptr.Face() == f && fptr.FaceDirection() == face_edir)
          prefix[2] = ((0 == face_edir) ? '+' : '-');
        else
          face_error_count++;
        text_log.Print(prefix, e->m_id);
      }
      else
      {
        text_log.Print("%c %c", prefix[0], error_code_point);
        face_error_count++;
      }
    }
    text_log.Print(" }\n");

    text_log.Print("f.Vertices[%u] = ", face_edge_count);
    prefix[0] = '{';
    prefix[1] = ON_String::Space;
    prefix[2] = 'v';
    prefix[3] = '%';
    prefix[4] = 'u';
    prefix[5] = 0;
    for (unsigned int fvi = 0; fvi < face_edge_count; fvi++)
    {
      if (1 == fvi)
        prefix[0] = ',';
      const ON_SubDVertex* v = f->Vertex(fvi);
      if (nullptr != v)
        text_log.Print(prefix, v->m_id);
      else
      {
        text_log.Print("%c %c", prefix[0], error_code_point);
        face_error_count++;
      }
    }
    text_log.Print(" }\n");


    if (f->PackRectIsSet())
    {
      const ON_2dPoint pack_rect_orgin = f->PackRectOrigin();
      const ON_2dPoint pack_rect_size = f->PackRectSize();
      text_log.Print("f.PackId = %u, origin = (%g,%g), size = (%g,%g), rot = %u degrees\n",
        f->PackId(),
        pack_rect_orgin.x, pack_rect_orgin.y,
        pack_rect_size.x, pack_rect_size.y,
        f->PackRectRotationDegrees()
      );

      // Dale Lear Oct 2023:
      // Use bGridOrder = false so pack_rect corners are in quad order
      // and it is possible to clearly see how texture space is assigned
      // to triangle and quad faces. 
      // For quads and triangles, vertex order, pack rect corner ordern and face
      // texture point order are identical.
      // For triangles, the texture space corresponding to the 4th pack_rect corner
      // subrect is not mapped.
      // For n-gons with n > 4, the pack rect is subdivide into two rows ofr floor((n+1)/2)
      // subrects.
      const bool bGridOrder = false; // SEE COMMENT ABOVE for why this should be false.
      ON_2dPoint corners[4] = {
        f->PackRectCorner(bGridOrder,0),
        f->PackRectCorner(bGridOrder,1),
        f->PackRectCorner(bGridOrder,2),
        f->PackRectCorner(bGridOrder,3)
      };
      text_log.Print("f.PackRectCorners[4] = {(%g,%g), (%g,%g), (%g,%g), (%g,%g)}\n",
        corners[0].x, corners[0].y,
        corners[1].x, corners[1].y,
        corners[2].x, corners[2].y,
        corners[3].x, corners[3].y
      );
      if ( 3 == f->m_edge_count)
      {
        const ON_TextLogIndent indent2(text_log);
        const ON_2dPoint m01 = 0.5 * (corners[0] + corners[1]);
        const ON_2dPoint m12 = 0.5 * (corners[1] + corners[2]);
        const ON_2dPoint m23 = 0.5 * (corners[2] + corners[3]);
        const ON_2dPoint m30 = 0.5 * (corners[3] + corners[0]);
        const ON_2dPoint c = pack_rect_orgin + 0.5 * pack_rect_size;

        text_log.Print("3 sub rects:\n");
        const ON_TextLogIndent indent3(text_log);
        text_log.Print("{(%g,% g), (% g,% g), (% g,% g), (% g,% g)}\n",
            corners[0].x, corners[0].y,
            m01.x, m01.y,
            c.x, c.y,
            m30.x, m30.y
          );
        text_log.Print("{(%g,% g), (% g,% g), (% g,% g), (% g,% g)}\n",
          m01.x, m01.y,
          corners[1].x, corners[1].y,
          m12.x, m12.y,
          c.x, c.y
        );
        text_log.Print("{(%g,% g), (% g,% g), (% g,% g), (% g,% g)}\n",
          c.x, c.y,
          m12.x, m12.y,
          corners[2].x, corners[2].y,
          m23.x, m23.y
        );
      }
    }

    if (f->TexturePointsAreSet())
    {
      text_log.Print("f.TexturePoints[%u] = {", face_edge_count);
      prefix[0] = ON_String::Space;
      prefix[1] = 0;
      for (unsigned int fei = 0; fei < face_edge_count; fei++)
      {
        if (1 == fei)
        {
          prefix[0] = ',';
          prefix[1] = ON_String::Space;
          prefix[2] = 0;
        }
        const ON_3dPoint tp = f->TexturePoint(fei);
        text_log.Print("%s(%g,%g,%g)", prefix, tp.x, tp.y, tp.z);
      }
      text_log.Print(" }\n");
    }

    bool bNeedComma = false;

    const ON_Color per_face_color = f->PerFaceColor();
    if (ON_Color::UnsetColor != per_face_color)
    {
      if (bNeedComma)
        text_log.Print(", ");
      else
        text_log.Print("Per face ");
      bNeedComma = true;
      text_log.Print("color=");
      per_face_color.ToText(ON_Color::TextFormat::HashRGBa, 0, true, text_log);
    }

    const int per_face_material_channel_index = f->MaterialChannelIndex();
    if (0 != per_face_material_channel_index)
    {
      if (bNeedComma)
        text_log.Print(", ");
      else
        text_log.Print("Per face ");
      bNeedComma = true;
      text_log.Print("material channel index=%d", per_face_material_channel_index);
    }
    if (bNeedComma)
      text_log.PrintNewLine();



    if (false == text_log.IsTextHash())
    {
      const ON_SubDMeshFragment* first_frag = f->MeshFragments();
      if (nullptr != first_frag)
      {
        text_log.Print(L"Fragments:\n");
        const ON_TextLogIndent indent(text_log);
        for (const ON_SubDMeshFragment* frags = first_frag; nullptr != frags; frags = frags->NextFaceFragment(false))
          frags->Dump(text_log);
      }
    }

    text_log.PopIndent();
  }

  text_log.PushIndent();
  if (face_dump_count > 0 && face_dump_count < face_count)
  {
    text_log.Print(
      L"... %u additional faces (f%u to f%u).\n",
      face_count - face_dump_count,
      skipped_face_id.i,
      skipped_face_id.j
    );
  }
  text_log.Print("Maximum face id = %u.  ",max_face_id);
  if (validate_max_face_id >= max_face_id)
    text_log.Print("Next id = %u.\n", validate_max_face_id + 1);
  else
    text_log.Print("ERROR Next id = %u.\n", validate_max_face_id + 1);
  text_log.PopIndent();

 
  const unsigned int topology_error_count
    = vertex_error_count
    + edge_error_count
    + face_error_count;

  text_log.PushIndent();
  if (0 == topology_error_count)
  {
    text_log.Print("No topology inconsistencies.\n");
  }
  else
  {
    text_log.Print(
      "ERRORS: %u vertex, %u edge, %u face topology inconsistencies marked with \"%c\".\n", 
      vertex_error_count,
      edge_error_count,
      face_error_count, 
      error_code_point
    );
  }
  text_log.PopIndent();

  return topology_error_count;
}

static void Internal_DumpFragmentColorArray(ON_TextLog& text_log, const wchar_t* description, const ON_Color* a, unsigned count, size_t stride)
{
  if (nullptr != a && count > 0 && stride >= 1)
  {
    text_log.Print(L"%ls = ", description);
    if (count <= 4)
    {
      text_log.Print("{");
      for (unsigned i = 0; i < count; ++i)
      {
        if (0 != i)
          text_log.Print(L",");
        a->ToText(ON_Color::TextFormat::HashRGBa, 0, true, text_log);
        a += stride;
      }
      text_log.Print("}");
    }
    else
    {
      a->ToText(ON_Color::TextFormat::HashRGBa, 0, true, text_log);
      ON_SHA1 sha1;
      Internal_AccumulateFragmentColorArrayHash(sha1, a, count, stride);
      const ON_wString s = sha1.Hash().ToString(true);
      text_log.Print(L" ... SHA1 hash=%ls", static_cast<const wchar_t*>(s));
    }
  }
  else
  {
    text_log.Print(L"%ls: Not set.", description);
  }
  text_log.PrintNewLine();
}

static void Internal_DumpFragmentArray(ON_TextLog& text_log, const wchar_t* description, size_t dim, const double* a, unsigned count, size_t stride)
{
  if (nullptr != a && count > 0 && dim > 0 && stride >= dim)
  {
    text_log.Print(L"%ls = ", description);
    if (count <= 4)
    {
      text_log.Print("{");
      for (unsigned i = 0; i < count; ++i)
      {
        if (0 != i)
          text_log.Print(L",");
        text_log.Print(L"(%g", a[0]);
        for (unsigned j = 1; j < dim; ++j)
          text_log.Print(L",%g", a[j]);
        text_log.Print(L")");
        a += stride;
      }
      text_log.Print("}");
    }
    else
    {
      for (size_t i = 0; i < dim; ++i)
        text_log.Print(L"%g,", a[i]);
      ON_SHA1 sha1;
      Internal_AccumulateFragmentArrayHash(sha1, dim, a, count, stride);
      const ON_wString s = sha1.Hash().ToString(true);
      text_log.Print(L" ... SHA1 hash=%ls", static_cast<const wchar_t*>(s));
    }
  }
  else
  {
    text_log.Print(L"%ls: Not set.",description);
  }
  text_log.PrintNewLine();
}

void ON_SubDMeshFragment::Dump(ON_TextLog& text_log) const
{
  const unsigned count = VertexCount();
  text_log.Print("ON_SubDMeshFragment: vertex count = %u", count);
  const unsigned n = m_grid.SideSegmentCount();
  const unsigned grid_point_count = m_grid.GridPointCount();
  if (count > 0)
  {
    if (n > 0 && count == grid_point_count)
    {
      text_log.Print(
        L", %u x %u grid\n",
        n, n
      );

      ON_TextLogIndent indent1(text_log);
      text_log.Print(
        L"bounding box (%g to %g X %g to %g X %g to %g)\n",
        m_surface_bbox.m_min.x, m_surface_bbox.m_max.x,
        m_surface_bbox.m_min.y, m_surface_bbox.m_max.y,
        m_surface_bbox.m_min.z, m_surface_bbox.m_max.z
      );

      text_log.Print(
        L"pack rect (%g,%g),(%g,%g),(%g,%g),(%g,%g) \n",
        m_pack_rect[0][0], m_pack_rect[0][1],
        m_pack_rect[1][0], m_pack_rect[1][1],
        m_pack_rect[2][0], m_pack_rect[2][1],
        m_pack_rect[3][0], m_pack_rect[3][1]
      );

      for (int pass = 0; pass < 2; ++pass)
      {
        const ON_SubDComponentLocation cl = (0 == pass) ? ON_SubDComponentLocation::ControlNet : ON_SubDComponentLocation::Surface;
        if (ON_SubDComponentLocation::ControlNet == cl)
          text_log.Print("Corners:\n");
        else if (ON_SubDComponentLocation::Surface == cl)
          text_log.Print("Surface:\n");
        ON_TextLogIndent ident2(text_log);
        Internal_DumpFragmentArray(
          text_log, L"points", 3,
          PointArray(cl),
          PointArrayCount(cl),
          PointArrayStride(cl));
        Internal_DumpFragmentArray(
          text_log, L"normals", 3,
          NormalArray(cl),
          NormalArrayCount(cl),
          NormalArrayStride(cl));
        Internal_DumpFragmentArray(
          text_log, L"texture coordinates", 3, // tcs are uvw
          TextureCoordinateArray(cl),
          TextureCoordinateArrayCount(cl),
          TextureCoordinateArrayStride(cl));
        Internal_DumpFragmentArray(
          text_log, L"curvatures", 2, // 2 principal
          (const double*)(CurvatureArray(cl)),
          CurvatureArrayCount(cl),
          sizeof(ON_SurfaceCurvature)/sizeof(double));
        Internal_DumpFragmentColorArray(
          text_log, L"colors",
          ColorArray(cl),
          ColorArrayCount(cl),
          ColorArrayStride(cl)
        );
      }
    }
    else
    {
      text_log.Print(L". Invalid fragment.\n");
    }
  }
  else
  {
    text_log.PrintNewLine();
  }
}



//virtual
unsigned int ON_SubD::SizeOf() const
{
  size_t sz = ON_Geometry::SizeOf();
  sz += sizeof(*this) - sizeof(ON_Geometry);
  const ON_SubDimple* subdimple = SubDimple();
  if ( subdimple )
    sz += subdimple->SizeOf();
  return (unsigned int)sz;
}

size_t ON_SubD::SizeOfAllElements() const
{
  const ON_SubDimple* subdimple = SubDimple();
  return (nullptr != subdimple) ? subdimple->SizeOfAllElements() : 0;
}

size_t ON_SubD::SizeOfActiveElements() const
{
  const ON_SubDimple* subdimple = SubDimple();
  return (nullptr != subdimple) ? subdimple->SizeOfActiveElements() : 0;
}

size_t ON_SubD::SizeOfUnusedElements() const
{
  const ON_SubDimple* subdimple = SubDimple();
  return (nullptr != subdimple) ? subdimple->SizeOfUnusedElements() : 0;
}

size_t ON_SubD::SizeOfAllMeshFragments() const
{
  const ON_SubDimple* subdimple = SubDimple();
  return (nullptr != subdimple) ? subdimple->SizeOfAllMeshFragments() : 0;
}

size_t ON_SubD::SizeOfActiveMeshFragments() const
{
  const ON_SubDimple* subdimple = SubDimple();
  return (nullptr != subdimple) ? subdimple->SizeOfActiveMeshFragments() : 0;
}

size_t ON_SubD::SizeOfUnusedMeshFragments() const
{
  const ON_SubDimple* subdimple = SubDimple();
  return (nullptr != subdimple) ? subdimple->SizeOfUnusedMeshFragments() : 0;
}

//virtual
ON__UINT32 ON_SubD::DataCRC(ON__UINT32 current_remainder) const
{
  return this->GeometryHash().CRC32(current_remainder);
}

//virtual
ON::object_type ON_SubD::ObjectType() const
{
  return ON::subd_object;
}

//virtual
void ON_SubD::DestroyRuntimeCache( bool bDelete )
{
  const ON_SubDimple* dimple = SubDimple();
  if (nullptr != dimple)
  {
    unsigned int level_count = dimple->LevelCount();
    for (unsigned int level_index = 0; level_index < level_count; level_index++)
    {
      const ON_SubDLevel* level = dimple->SubDLevel(level_index);
      if (level)
      {
        level->ClearEvaluationCache();
        level->MarkAggregateComponentStatusAsNotCurrent();
      }
    }
    dimple->ChangeGeometryContentSerialNumber(false);
  }
  return;
}

//virtual 
int ON_SubD::Dimension() const
{
  return 3;
}

//virtual
bool ON_SubD::GetBBox(
        double* boxmin,
        double* boxmax,
        bool bGrowBox
        ) const
{ 
  int j;
  for ( j = 0; j < 3 && bGrowBox; j++ )
  {
    if ( !ON_IsValid(boxmin[j]) || !ON_IsValid(boxmax[j]) || boxmin[j] > boxmax[j])
      bGrowBox = false;
  }

  ON_BoundingBox bbox = ON_BoundingBox::EmptyBoundingBox;
  bool rc = false;

  // GetBBox must always returns the control net box - it contains both the surface and the control net.
  bbox = ActiveLevel().ControlNetBoundingBox();
  rc = bbox.IsValid();
  if (rc)
  {
    if (bGrowBox)
    {
      if (bbox.m_min.x < boxmin[0]) boxmin[0] = bbox.m_min.x;
      if (bbox.m_max.x > boxmax[0]) boxmax[0] = bbox.m_max.x;
      if (bbox.m_min.y < boxmin[1]) boxmin[1] = bbox.m_min.y;
      if (bbox.m_max.y > boxmax[1]) boxmax[1] = bbox.m_max.y;
      if (bbox.m_min.z < boxmin[2]) boxmin[2] = bbox.m_min.z;
      if (bbox.m_max.z > boxmax[2]) boxmax[2] = bbox.m_max.z;
    }
    else
    {
      boxmin[0] = bbox.m_min.x; boxmin[1] = bbox.m_min.y; boxmin[2] = bbox.m_min.z;
      boxmax[0] = bbox.m_max.x; boxmax[1] = bbox.m_max.y; boxmax[2] = bbox.m_max.z;
    }
  }

  return (rc || bGrowBox);
}

//virtual
void ON_SubD::ClearBoundingBox()
{
  // For ON_SubD, ON_SubD::ClearBoundingBox() and ON_SubD::DestroyRuntimeCache(true)

  ON_SubD::DestroyRuntimeCache(true);
}

//virtual
bool ON_SubD::Transform( 
        const ON_Xform& xform
        )
{
  if ( this == &ON_SubD::Empty)
    return true;  // transform applied to empty subd is true on purpose

  // userdata transformation, etc.
  if (!this->ON_Geometry::Transform(xform))
    return false;

  ON_SubDimple* subdimple = SubDimple(false);
  if ( 0 == subdimple )
    return true;  // transform applied to empty subd is true on purpose

  return subdimple->Transform(xform);
}

//virtual
bool ON_SubD::IsDeformable() const
{
  return true;
}

//virtual
bool ON_SubD::MakeDeformable()
{
  return true;
}

//virtual
bool ON_SubD::SwapCoordinates(
      int i,
      int j
      )
{
  return false;
}

//virtual
bool ON_SubD::HasBrepForm() const
{
  return false;
}

//virtual
ON_Brep* ON_SubD::BrepForm( ON_Brep* destination_brep) const
{
  return nullptr;
}

//virtual
ON_COMPONENT_INDEX ON_SubD::ComponentIndex() const
{
  return ON_Geometry::ComponentIndex();
}


bool ON_ObjRefEvaluationParameter::SetFromSubDComponentParameter(
  const ON_SubDComponentParameter& cp
)
{
  switch (cp.ComponentType())
  {
  case ON_SubDComponentPtr::Type::Vertex:
  {
    this->m_t_type = 9;
    const ON_SubDComponentId vertex_id = cp.ComponentIdAndType();
    const ON_SubDComponentId edge_id = cp.VertexEdge();
    const ON_SubDComponentId face_id = cp.VertexFace();
    this->m_t_ci.Set(ON_COMPONENT_INDEX::subd_vertex, vertex_id.ComponentId());
    this->m_t[0] = (double)edge_id.ComponentId();
    this->m_t[1] = (double)face_id.ComponentId();
    this->m_t[2] = 0.0;
    this->m_t[3] = 0.0;
  }
  break;

  case ON_SubDComponentPtr::Type::Edge:
  {
    this->m_t_type = 9;
    const ON_SubDComponentId edge_id = cp.ComponentIdAndType();
    const ON_SubDComponentId face_id = cp.EdgeFace();
    const double ep = cp.EdgeParameter();
    this->m_t_ci.Set(ON_COMPONENT_INDEX::subd_edge, edge_id.ComponentId());
    this->m_t[0] = (double)face_id.ComponentId();
    this->m_t[1] = ep;
    this->m_t[2] = 0.0;
    this->m_t[3] = 0.0;
    this->m_s[0] = ON_Interval(0.0, 1.0);
  }
  break;

  case ON_SubDComponentPtr::Type::Face:
  {
    this->m_t_type = 9;
    const ON_SubDComponentId face_id = cp.ComponentIdAndType();
    const ON_SubDFaceParameter fp = cp.FaceParameter();
    this->m_t_ci.Set(ON_COMPONENT_INDEX::subd_face, face_id.ComponentId());
    this->m_t[0] = (double)fp.FaceCornerDex().CornerIndex();
    this->m_t[1] = (double)fp.FaceCornerDex().EdgeCount();
    this->m_t[2] = fp.FaceCornerParameters().x;
    this->m_t[3] = fp.FaceCornerParameters().y;
    this->m_s[0] = ON_Interval(0.0, 0.5);
    this->m_s[1] = ON_Interval(0.0, 0.5);
  }
  break;
      
  case ON_SubDComponentPtr::Type::Unset:
    break;
  }

  this->Default();
  return false;
}

static bool Internal_IsValidUnsigned(double x)
{
  return x >= 0 && x <= ((double)0xFFFFFFFFu) && x == floor(x);
}

static const ON_SubDComponentId Internal_ComponentIdFromDouble(
  ON_SubDComponentPtr::Type component_type,
  double component_id_as_double
)
{
  return
    (ON_SubDComponentPtr::Type::Unset != component_type && Internal_IsValidUnsigned(component_id_as_double))
    ? ON_SubDComponentId(component_type, (unsigned)component_id_as_double)
    : ON_SubDComponentId::Unset;
}


bool ON_ObjRefEvaluationParameter::GetSubDComponentParameter(
  ON_SubDComponentParameter& cp
) const
{
  cp = ON_SubDComponentParameter::Unset;
  if (9 == this->m_t_type)
  {
    switch (this->m_t_ci.m_type)
    {
    case ON_COMPONENT_INDEX::TYPE::subd_vertex:
      if (false == Internal_IsValidUnsigned(this->m_t[0]))
        break;
      if (false == Internal_IsValidUnsigned(this->m_t[1]))
        break;
      if (false == (0.0 == this->m_t[2]))
        break;
      if (false == (0.0 == this->m_t[3]))
        break;
      {
        const ON_SubDComponentId vertex_id(ON_SubDComponentPtr::Type::Vertex, this->m_t_ci.m_index);
        cp = ON_SubDComponentParameter(
          vertex_id, 
          Internal_ComponentIdFromDouble(ON_SubDComponentPtr::Type::Edge, this->m_t[0]),
          Internal_ComponentIdFromDouble(ON_SubDComponentPtr::Type::Face, this->m_t[1]));
      }
      break;
    case ON_COMPONENT_INDEX::TYPE::subd_edge:
      if (false == Internal_IsValidUnsigned(this->m_t[0]))
        break;
      if (false == (0.0 <= this->m_t[1] && this->m_t[1] <= 1.0))
        break;
      if (false == (0.0 == this->m_t[2]))
        break;
      if (false == (0.0 == this->m_t[3]))
        break;
      {
        const ON_SubDComponentId edge_id(ON_SubDComponentPtr::Type::Edge, this->m_t_ci.m_index);
        cp = ON_SubDComponentParameter(
          edge_id,
          this->m_t[1],
          Internal_ComponentIdFromDouble(ON_SubDComponentPtr::Type::Face, this->m_t[0]));
      }
      break;
    case ON_COMPONENT_INDEX::TYPE::subd_face:
      if (false == Internal_IsValidUnsigned(this->m_t[0]))
        break;
      if (false == Internal_IsValidUnsigned(this->m_t[1]))
        break;
      if (false == (this->m_t[0] < this->m_t[1]))
        break;
      if (false == (0.0 <= this->m_t[2] && this->m_t[2] <= 0.5))
        break;
      if (false == (0.0 <= this->m_t[3] && this->m_t[3] <= 0.5))
        break;
      {
        const ON_SubDComponentId face_id(ON_SubDComponentPtr::Type::Face, this->m_t_ci.m_index);
        const ON_SubDFaceCornerDex cdex((unsigned)this->m_t[0], (unsigned)this->m_t[1]);
        ON_SubDFaceParameter fp(cdex, this->m_t[2], this->m_t[3]);
        cp = ON_SubDComponentParameter(face_id, fp);
      }
      break;
    default:
      break;
    }
  }
  return cp.IsSet();
}

//virtual
bool ON_SubD::EvaluatePoint( const class ON_ObjRef& objref, ON_3dPoint& P ) const
{
  P = ON_3dPoint::NanPoint;
  return false;
}

//////////////////////////////////////////////////////////////
//
//
//

class ON_SubDHeap* ON_SubD::Internal_Heap() const
{
  ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? &subdimple->Heap() : nullptr;
}

bool ON_SubD::InSubD(const class ON_SubDVertex* vertex) const
{
  return InSubD(ON_SubDComponentPtr::Create(vertex));
}

bool ON_SubD::InSubD(const class ON_SubDEdge* edge) const
{
  return InSubD(ON_SubDComponentPtr::Create(edge));
}

bool ON_SubD::InSubD(const class ON_SubDFace* face) const
{
  return InSubD(ON_SubDComponentPtr::Create(face));
}

bool ON_SubD::InSubD(ON_SubDComponentPtr cptr) const
{
  const ON_SubDHeap* h = this->Internal_Heap();
  return (nullptr != h) ? h->InHeap(cptr) : false;
}

const ON_SubDComponentPtr ON_SubD::InSubD(const ON_SubDComponentBase* b) const
{
  const ON_SubDHeap* h = this->Internal_Heap();
  return (nullptr != h) ? h->InHeap(b) : ON_SubDComponentPtr::Null;
}


bool ON_SubDHeap::InHeap(ON_SubDComponentPtr cptr) const
{
  const ON_FixedSizePool* fsp = this->Internal_ComponentFixedSizePool(cptr.ComponentType());
  return (nullptr != fsp) ? fsp->InPool(cptr.ComponentBase()) : false;
}

const ON_SubDComponentPtr ON_SubDHeap::InHeap(const class ON_SubDComponentBase* b) const
{
  if (nullptr != b)
  {
    ON_SubDComponentPtr::Type t[3] = {
      ON_SubDComponentPtr::Type::Vertex,
      ON_SubDComponentPtr::Type::Edge,
      ON_SubDComponentPtr::Type::Face
    };
    for (int i = 0; i < 3; ++i)
    {
      const ON_FixedSizePool* fsp = this->Internal_ComponentFixedSizePool(t[i]);
      if (nullptr != fsp && fsp->InPool(b))
      {
        switch (t[i])
        {
        case ON_SubDComponentPtr::Type::Vertex:
          return ON_SubDComponentPtr::Create((const ON_SubDVertex*)b);
          break;
        case ON_SubDComponentPtr::Type::Edge:
          return ON_SubDComponentPtr::Create((const ON_SubDEdge*)b);
          break;
        case ON_SubDComponentPtr::Type::Face:
          return ON_SubDComponentPtr::Create((const ON_SubDFace*)b);
          break;
        case ON_SubDComponentPtr::Type::Unset:
          break;
        }
      }
    }
  }
  return ON_SubDComponentPtr::Null;
}

const class ON_SubDLevel& ON_SubD::ActiveLevel() const
{
  ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? subdimple->ActiveLevel() : ON_SubDLevel::Empty;
}

class ON_SubDLevel const * ON_SubD::ActiveLevelConstPointer() const
{
  ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? subdimple->ActiveLevelPointer() : nullptr;
}

class ON_SubDLevel* ON_SubD::ActiveLevelPointer()
{
  ON_SubDimple* subdimple = m_subdimple_sp.get();
  return (nullptr != subdimple) ? subdimple->ActiveLevelPointer() : nullptr;
}

const class ON_SubDLevel& ON_SubD::LevelForExperts(unsigned int level_index) const
{
  for (;;)
  {
    ON_SubDimple* subdimple = m_subdimple_sp.get();
    if (nullptr == subdimple)
      break;
    ON_SubDLevelIterator lit = subdimple->LevelIterator();
    for (ON_SubDLevel* level = lit.First(); nullptr != level; level = lit.Next())
    {
      if (level_index == level->m_level_index)
        return *level;
    }
  }
  return ON_SubDLevel::Empty;
}

ON_SubDimple* ON_SubD::SubDimple(bool bCreateIfNeeded)
{
  ON_SubDimple* subdimple = m_subdimple_sp.get();
  if (nullptr == subdimple && bCreateIfNeeded)
  {
    subdimple = new ON_SubDimple();
    m_subdimple_sp = std::shared_ptr<ON_SubDimple>(subdimple);
  }
  return subdimple;
}

const class ON_SubDimple* ON_SubD::SubDimple() const
{
  return m_subdimple_sp.get();
}

unsigned int ON_SubD::SubDimpleUseCount() const
{
  return (unsigned int)m_subdimple_sp.use_count();
}

void ON_SubD::ShareDimple(const ON_SubD& other_subd)
{
  if (m_subdimple_sp.get() != other_subd.m_subdimple_sp.get())
  {
    m_subdimple_sp.reset();
    m_subdimple_sp = other_subd.m_subdimple_sp;
  }
}

void ON_SubD::ShareDimple(const class ON_SubDMeshImpl& subd_limple)
{
  std::shared_ptr<ON_SubDimple> limple_sp(subd_limple.m_subdimple_wp.lock());

  const ON_SubDimple* subd_imple = m_subdimple_sp.get();

  if (nullptr == limple_sp.get())
  {
    // weak pointer is nullptr, meaning there are no known references to the
    // subd used to create this limit mesh.
    const_cast<ON_SubDMeshImpl&>(subd_limple).ClearFragmentFacePointers(true);
  }

  if (subd_imple != limple_sp.get())
  {
    m_subdimple_sp.reset();
    m_subdimple_sp = limple_sp;
  }
}

void ON_SubD::SwapDimple(class ON_SubDMeshImpl& subd_limple )
{
  std::shared_ptr <ON_SubDimple> limple_sp(subd_limple.m_subdimple_wp.lock());
  if (m_subdimple_sp.get() != limple_sp.get())
  {
    m_subdimple_sp.swap(limple_sp);
    subd_limple.m_subdimple_wp = limple_sp;
  }
}


void ON_SubD::SwapDimple(ON_SubD& other_subd)
{
  if (this != &other_subd)
  {
    m_subdimple_sp.swap(other_subd.m_subdimple_sp);
  }
}

void ON_SubD::Clear()
{
  ON_SubDimple* subdimple = SubDimple(false);
  if ( subdimple )
    subdimple->Clear();
}

unsigned int ON_SubD::ClearHigherSubdivisionLevels(
  unsigned int max_level_index
  )
{
  ON_SubDimple* subdimple = SubDimple(false);
  return
    (nullptr != subdimple)
    ? subdimple->ClearHigherSubdivisionLevels(max_level_index)
    : 0U;
}

unsigned int ON_SubD::ClearLowerSubdivisionLevels(
  unsigned int min_level_index
  )
{
  ON_SubDimple* subdimple = SubDimple(false);
  return
    (nullptr != subdimple)
    ? subdimple->ClearLowerSubdivisionLevels(min_level_index)
    : 0U;
}

unsigned ON_SubD::ClearInactiveLevels()
{
  ON_SubDimple* subdimple = SubDimple(false);
  return
    (nullptr != subdimple)
    ? subdimple->ClearInactiveLevels()
    : 0U;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::NextComponent() const
{
  switch (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr)
  {
  case ON_SUBD_COMPONENT_TYPE_VERTEX:
  {
    const ON_SubDVertex* v = ON_SUBD_VERTEX_POINTER(m_ptr);
    if (nullptr != v)
      return ON_SubDComponentPtr::Create(v->m_next_vertex);
  }
  case ON_SUBD_COMPONENT_TYPE_EDGE:
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
    if (nullptr != e)
      return ON_SubDComponentPtr::Create(e->m_next_edge);
  }
  case ON_SUBD_COMPONENT_TYPE_FACE:
  {
    const ON_SubDFace* f = ON_SUBD_FACE_POINTER(m_ptr);
    if (nullptr != f)
      return ON_SubDComponentPtr::Create(f->m_next_face);
  }
  default:
    break;
  }
  return ON_SubDComponentPtr::Null;
}


const ON_SubDComponentPtr ON_SubDComponentPtr::PrevComponent() const
{
  switch (ON_SUBD_COMPONENT_TYPE_MASK & m_ptr)
  {
  case ON_SUBD_COMPONENT_TYPE_VERTEX:
  {
    const ON_SubDVertex* v = ON_SUBD_VERTEX_POINTER(m_ptr);
    if (nullptr != v)
      return ON_SubDComponentPtr::Create(v->m_prev_vertex);
  }
  case ON_SUBD_COMPONENT_TYPE_EDGE:
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
    if (nullptr != e)
      return ON_SubDComponentPtr::Create(e->m_prev_edge);
  }
  case ON_SUBD_COMPONENT_TYPE_FACE:
  {
    const ON_SubDFace* f = ON_SUBD_FACE_POINTER(m_ptr);
    if (nullptr != f)
      return ON_SubDComponentPtr::Create(f->m_prev_face);
  }
  default:
    break;
  }
  return ON_SubDComponentPtr::Null;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::operator++()
{
  // prefix ++
  *this = this->NextComponent();
  return *this;
}

const ON_SubDComponentPtr ON_SubDComponentPtr::operator++(int)
{
  // postfix ++
  const ON_SubDComponentPtr input_value = *this;
  *this = this->NextComponent();
  return input_value;
}

const ON_SubDComponentPtr ON_SubD::FirstComponent(
  ON_SubDComponentPtr::Type component_type
) const
{
  switch (component_type)
  {
  case ON_SubDComponentPtr::Type::Vertex:
    return ON_SubDComponentPtr::Create(this->FirstVertex());
    break;
  case ON_SubDComponentPtr::Type::Edge:
    return ON_SubDComponentPtr::Create(this->FirstEdge());
    break;
  case ON_SubDComponentPtr::Type::Face:
    return ON_SubDComponentPtr::Create(this->FirstFace());
    break;
  default:
    break;
  }
  return ON_SubDComponentPtr::Null;
}


unsigned ON_SubD::ComponentCount(
  ON_SubDComponentPtr::Type component_type
) const 
{
  switch (component_type)
  {
  case ON_SubDComponentPtr::Type::Vertex:
    return this->VertexCount();
    break;
  case ON_SubDComponentPtr::Type::Edge:
    return this->EdgeCount();
    break;
  case ON_SubDComponentPtr::Type::Face:
    return this->FaceCount();
    break;
  default:
    break;
  }
  return 0;
}

void ON_SubD::Destroy()
{
  m_subdimple_sp.reset();
}

class ON_SubDVertex* ON_SubD::AddVertex(
  const double* P
)
{
  return AddVertex(ON_SubDVertexTag::Unset, P);
}

class ON_SubDVertex* ON_SubD::AddVertex(
  ON_SubDVertexTag vertex_tag,
  const double* P
  )
{
  ON_SubDimple* subdimple = SubDimple(true);
  if ( 0 == subdimple )
    return 0;
  const unsigned int level_index = subdimple->ActiveLevelIndex();
  class ON_SubDVertex* v = subdimple->AllocateVertex(vertex_tag, level_index, P); // 0 = level
  subdimple->AddVertexToLevel(v);
  return v;
}

ON_SubDVertex* ON_SubD::AddVertexForExperts(
  unsigned int candidate_vertex_id,
  ON_SubDVertexTag vertex_tag,
  const double* P,
  unsigned int initial_edge_capacity,
  unsigned int initial_face_capacity
)
{
  ON_SubDimple* subdimple = SubDimple(true);
  if (0 == subdimple)
    return 0;
  ON_SubDVertex* v = subdimple->AllocateVertex( candidate_vertex_id, vertex_tag, subdimple->ActiveLevelIndex(), P, initial_edge_capacity, initial_face_capacity);
  subdimple->AddVertexToLevel(v);
  return v;
}

bool ON_SubD::ReturnVertexForExperts(
  ON_SubDVertex* v
)
{
  if (nullptr == v)
    return false;

  if (this->InSubD(v) && v->IsActive() && 0 == v->m_edge_count && 0 == v->m_face_count )
  {
    ON_SubDimple* subdimple = SubDimple(false);
    if (nullptr != subdimple)
    {
      subdimple->ReturnVertex(v);
      return true;
    }
  }

  // Caller is not an expert but a crash has been prevented.
  return ON_SUBD_RETURN_ERROR(false);
}

class ON_SubDEdge* ON_SubDimple::AddEdge(
  ON_SubDEdgeTag edge_tag,
  ON_SubDVertex* v0,
  double v0_sector_coefficient,
  ON_SubDVertex* v1,
  double v1_sector_coefficient
)
{
  return AddEdge(
    0U,
    edge_tag,
    v0,
    v0_sector_coefficient,
    v1,
    v1_sector_coefficient,
    0U
  );
}

class ON_SubDEdge* ON_SubDimple::AddEdge(
  unsigned int candidate_edge_id,
  ON_SubDEdgeTag edge_tag,
  ON_SubDVertex* v0,
  double v0_sector_coefficient,
  ON_SubDVertex* v1,
  double v1_sector_coefficient,
  unsigned initial_face_capacity
)
{
  if (false == ON_SubDSectorType::IsValidSectorCoefficientValue(v0_sector_coefficient, true))
    return ON_SUBD_RETURN_ERROR(nullptr);

  if (false == ON_SubDSectorType::IsValidSectorCoefficientValue(v1_sector_coefficient, true))
    return ON_SUBD_RETURN_ERROR(nullptr);

  if (nullptr != v0 && nullptr != v1 && v0->SubdivisionLevel() != v1->SubdivisionLevel())
    return ON_SUBD_RETURN_ERROR(nullptr);

  const bool bEdgeTagSet = ON_SubD::EdgeTagIsSet(edge_tag);

  if (bEdgeTagSet
    && ON_SubDSectorType::IgnoredSectorCoefficient != v0_sector_coefficient
    && ON_SubDSectorType::UnsetSectorCoefficient != v0_sector_coefficient
    && nullptr != v0
    && ON_SubDVertexTag::Smooth == v0->m_vertex_tag
    )
  {
    // minimizes checking when building subds because constant crease coefficients can be passed in
    v0_sector_coefficient = ON_SubDSectorType::IgnoredSectorCoefficient;
  }

  if (bEdgeTagSet
    && ON_SubDSectorType::IgnoredSectorCoefficient != v1_sector_coefficient
    && ON_SubDSectorType::UnsetSectorCoefficient != v1_sector_coefficient
    && nullptr != v1
    && ON_SubDVertexTag::Smooth == v1->m_vertex_tag
    )
  {
    // minimizes checking when building subds because constant crease coefficients can be passed in
    v1_sector_coefficient = ON_SubDSectorType::IgnoredSectorCoefficient;
  }

  class ON_SubDEdge* e = AllocateEdge(candidate_edge_id, edge_tag, 0, 0);
  if (nullptr == e)
    return ON_SUBD_RETURN_ERROR(nullptr);

  if (nullptr != v0)
    e->SetSubdivisionLevel(v0->SubdivisionLevel());
  else if (nullptr != v1)
    e->SetSubdivisionLevel(v1->SubdivisionLevel());
  else if (ActiveLevelIndex() < ON_UNSET_UINT_INDEX)
    e->SetSubdivisionLevel(ActiveLevelIndex());

  for (unsigned int i = 0; i < 2; i++)
  {
    ON_SubDVertex* v = (i ? v1 : v0);
    double vertex_coefficient = (i ? v1_sector_coefficient : v0_sector_coefficient);
    e->m_vertex[i] = v;
    e->m_sector_coefficient[i] = vertex_coefficient;
    if (nullptr != v)
    {
      if (false == m_heap.GrowVertexEdgeArrayByOne(v))
      {
        v->m_status.SetDamagedState(true);
        ReturnEdge(e);
        return ON_SUBD_RETURN_ERROR(nullptr);
      }
      v->m_edges[v->m_edge_count++] = ON_SubDEdgePtr::Create(e, i);
    }
  }

  if ( nullptr == AddEdgeToLevel(e) )
    return ON_SUBD_RETURN_ERROR(nullptr);

  if (initial_face_capacity > 2)
  {
    m_heap.GrowEdgeFaceArray(e, initial_face_capacity);
  }

  return e;
}

ON_SubDEdgeTag ON_SubD::EdgeTagFromContext(
  unsigned int edge_face_count,
  const ON_SubDVertex* v0,
  const ON_SubDVertex* v1
)
{
  return
    (nullptr != v0 && nullptr != v1)
    ? ON_SubD::EdgeTagFromContext(edge_face_count, v0->m_vertex_tag, v1->m_vertex_tag)
    : ON_SubDEdgeTag::Unset;
}

ON_SubDEdgeTag ON_SubD::EdgeTagFromContext(
  unsigned int edge_face_count,
  const ON_SubDVertexTag v0_tag,
  const ON_SubDVertexTag v1_tag
)
{
  ON_SubDEdgeTag edge_tag = ON_SubDEdgeTag::Unset;

  for(;;)
  {
    if (edge_face_count > 0x7FFFU)
      break;

    if (1 == edge_face_count || edge_face_count >= 3 )
    {
      edge_tag = ON_SubDEdgeTag::Crease;
      break;
    }

    const bool bSmooth0 = ON_SubDVertexTag::Smooth == v0_tag;
    const bool bSmooth1 = ON_SubDVertexTag::Smooth == v1_tag;

    if ( bSmooth0 || bSmooth1 )
    {
      if ( 2 == edge_face_count && bSmooth0 && bSmooth1)
        edge_tag = ON_SubDEdgeTag::Smooth;
      break;
    }

    if ( ON_SubD::VertexTagIsSet(v0_tag) && ON_SubD::VertexTagIsSet(v1_tag) )
    {
      if (2 == edge_face_count)
        edge_tag = ON_SubDEdgeTag::SmoothX;
      break;
    }

    break;
  }

  return edge_tag;
}

const ON_SubDVertex* ON_SubD::FindVertex(
  const double* control_net_point,
  double distance_tolerance
) const
{
  if (nullptr == control_net_point )
    return nullptr;
  const ON_3dPoint P(control_net_point);
  if ( false == P.IsValid() )
    return nullptr;
  if ( false == (0.0 <= distance_tolerance))
    return nullptr;

  const ON_SubDVertex* best_v = nullptr;
  ON_SubDVertexIterator vit(*this);
  for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
  {
    const double d = P.DistanceTo(v->ControlNetPoint());
    if (0.0 == d)
      return v;
    if (d < distance_tolerance && (nullptr == best_v || d <= distance_tolerance) )
    {
      distance_tolerance = d;
      best_v = v;
    }
  }
  return best_v;
}

const ON_SubDVertex* ON_SubD::FindOrAddVertex(
  const double* control_net_point,
  double distance_tolerance
)
{
  if (nullptr == control_net_point)
    return nullptr;
  const ON_3dPoint P(control_net_point);
  if (false == P.IsValid())
    return nullptr;
  if (false == (0.0 <= distance_tolerance))
    return nullptr;
  const ON_SubDVertex* v = FindVertex(&P.x, distance_tolerance);
  return (nullptr != v) ? v : AddVertex(&P.x);
}

const ON_SubDEdgePtr ON_SubD::FindEdge(
  const class ON_SubDVertex* v0,
  const class ON_SubDVertex* v1
) const
{
  return ON_SubDEdge::FromVertices(v0, v1);
}

const ON_SubDEdgePtr ON_SubD::FindOrAddEdge(
  class ON_SubDVertex* v0,
  class ON_SubDVertex* v1
)
{
  ON_SubDEdgePtr eptr = ON_SubDEdge::FromVertices(v0, v1);
  if (nullptr == eptr.Edge())
    eptr = ON_SubDEdgePtr::Create(AddEdge(v0, v1), 0);
  return eptr;
}

class ON_SubDEdge* ON_SubD::AddEdge(
  ON_SubDVertex* v0,
  ON_SubDVertex* v1
)
{
  return ON_SubD::AddEdge(ON_SubDEdgeTag::Unset, v0, v1);
}

class ON_SubDEdge* ON_SubD::AddEdge(
  ON_SubDEdgeTag edge_tag,
  ON_SubDVertex* v0,
  ON_SubDVertex* v1
  )
{
  // NO automatic edge tag setting - causes more problems than it helps.
  // Users can call ON_SubD::EdgeTagFromContext() if they want to
  // preset the edge tag based on context.

  return AddEdgeWithSectorCoefficients(
    edge_tag,
    v0,
    ON_SubDSectorType::UnsetSectorCoefficient,
    v1,
    ON_SubDSectorType::UnsetSectorCoefficient
    );
}


class ON_SubDEdge* ON_SubD::AddEdge(
  ON_SubDEdgeTag edge_tag,
  ON_SubDVertex* v0,
  ON_SubDVertex* v1,
  ON_SubDEdgeSharpness sharpness
)
{
  // NO automatic edge tag setting - causes more problems than it helps.
  // Users can call ON_SubD::EdgeTagFromContext() if they want to
  // preset the edge tag based on context.

  class ON_SubDEdge* e = AddEdgeWithSectorCoefficients(
    edge_tag,
    v0,
    ON_SubDSectorType::UnsetSectorCoefficient,
    v1,
    ON_SubDSectorType::UnsetSectorCoefficient
  );
  if (nullptr != e && e->IsSmooth())
    e->SetSharpnessForExperts(sharpness);
  return e;
}


ON_SubDEdge* ON_SubD::AddEdgeWithSectorCoefficients(
  ON_SubDEdgeTag edge_tag,
  class ON_SubDVertex* v0,
  double v0_sector_coefficient,
  class ON_SubDVertex* v1,
  double v1_sector_coefficient
)
{
  ON_SubDimple* subdimple = SubDimple(true);
  if (nullptr != subdimple)
    return subdimple->AddEdge(edge_tag, v0, v0_sector_coefficient, v1, v1_sector_coefficient);
  return ON_SUBD_RETURN_ERROR(nullptr);
}

ON_SubDEdge* ON_SubD::AddEdgeWithSectorCoefficients(
  ON_SubDEdgeTag edge_tag,
  class ON_SubDVertex* v0,
  double v0_sector_coefficient,
  class ON_SubDVertex* v1,
  double v1_sector_coefficient,
  ON_SubDEdgeSharpness sharpness
)
{
  ON_SubDimple* subdimple = SubDimple(true);
  if (nullptr != subdimple)
  {
    ON_SubDEdge* e = subdimple->AddEdge(edge_tag, v0, v0_sector_coefficient, v1, v1_sector_coefficient);
    if (nullptr != e)
    {
      if (e->IsSmooth())
        e->SetSharpnessForExperts(sharpness);
      return e;
    }
  }
  return ON_SUBD_RETURN_ERROR(nullptr);
}

class ON_SubDEdge* ON_SubD::AddEdgeForExperts(
  unsigned int candidate_edge_id,
  ON_SubDEdgeTag edge_tag,
  class ON_SubDVertex* v0,
  double v0_sector_coefficient,
  class ON_SubDVertex* v1,
  double v1_sector_coefficient,
  unsigned int initial_face_capacity
)
{
  ON_SubDimple* subdimple = SubDimple(true);
  if (nullptr != subdimple)
    return subdimple->AddEdge(candidate_edge_id, edge_tag, v0, v0_sector_coefficient, v1, v1_sector_coefficient, initial_face_capacity);
  return ON_SUBD_RETURN_ERROR(nullptr);
}

ON_SubDEdge* ON_SubD::AddEdgeForExperts(
  unsigned int candidate_edge_id,
  ON_SubDEdgeTag edge_tag,
  class ON_SubDVertex* v0,
  double v0_sector_coefficient,
  class ON_SubDVertex* v1,
  double v1_sector_coefficient,
  ON_SubDEdgeSharpness sharpness,
  unsigned int initial_face_capacity
)
{
  ON_SubDimple* subdimple = SubDimple(true);
  if (nullptr != subdimple)
  {
    ON_SubDEdge* e = subdimple->AddEdge(candidate_edge_id, edge_tag, v0, v0_sector_coefficient, v1, v1_sector_coefficient, initial_face_capacity);
    if (nullptr != e)
    {
      if (e->IsSmooth())
        e->SetSharpnessForExperts(sharpness);
      return e;
    }
  }
  return ON_SUBD_RETURN_ERROR(nullptr);
}

bool ON_SubD::ReturnEdgeForExperts(
  ON_SubDEdge* e
)
{
  if (nullptr == e)
    return false;

  if (this->InSubD(e) && e->IsActive() && 0 == e->m_face_count && nullptr == e->m_vertex[0] && nullptr == e->m_vertex[1])
  {
    ON_SubDimple* subdimple = SubDimple(false);
    if (nullptr != subdimple)
    {
      subdimple->ReturnEdge(e);
      return true;
    }
  }

  // Caller is not an expert but a crash has been prevented.
  return ON_SUBD_RETURN_ERROR(false);
}


class ON_SubDFace* ON_SubDimple::AddFace(
  unsigned int edge_count,
  const ON_SubDEdgePtr* edge
)
{
  return AddFace(0U, edge_count, edge);
}

class ON_SubDFace* ON_SubDimple::AddFace(
  unsigned int candidate_face_id,
  unsigned int edge_count,
  const ON_SubDEdgePtr* edge
  )
{
  if ( edge_count > 0 && nullptr == edge)
    return ON_SUBD_RETURN_ERROR(nullptr);

  unsigned f_level = 0;
  bool bHaveLevel = false;
  for (unsigned int i = 0; i < edge_count; i++)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(edge[i].m_ptr);
    if (nullptr == e)
      continue;
    if (bHaveLevel)
    {
      if (e->SubdivisionLevel() != f_level)
        return ON_SUBD_RETURN_ERROR(nullptr);
    }
    else
    {
      f_level = e->SubdivisionLevel();
      bHaveLevel = true;
    }
  }

  ON_SubDFace* f = AllocateFace( candidate_face_id, 0, 0);
  if ( nullptr == f)
    return ON_SUBD_RETURN_ERROR(nullptr);
  f->SetSubdivisionLevel(f_level);

  if (edge_count > 0)
  {
    if (edge_count > 4)
    {
      if (false == m_heap.GrowFaceEdgeArray(f,edge_count))
      {
        ReturnFace(f);
        return ON_SUBD_RETURN_ERROR(nullptr);
      }
    }

    ON_SubDEdgePtr* f_edge = f->m_edge4;
    for (unsigned int i = 0; i < edge_count; i++)
    {
      if (4 == i)
        f_edge = f->m_edgex - 4;

      f_edge[i] = edge[i];
      ON__UINT_PTR eptr = edge[i].m_ptr;
      ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr);
      if ( nullptr == e)
        continue;

      eptr = ON_SUBD_EDGE_DIRECTION(eptr);

      ON_SubDVertex* v = const_cast<ON_SubDVertex*>(e->m_vertex[eptr]);
      if (false == m_heap.GrowVertexFaceArrayByOne(v))
      {
        v->m_status.SetDamagedState(true);
        ReturnFace(f);
        return ON_SUBD_RETURN_ERROR(nullptr);
      }
      v->m_faces[v->m_face_count++] = f;
      //if (1 == v->m_face_count)
      //{
      //  if (4 == f->m_edge_count)
      //    v->m_vertex_facet_type = ON_SubD::VertexFacetType::Quad;
      //  else if (3 == f->m_edge_count)
      //    v->m_vertex_facet_type = ON_SubD::VertexFacetType::Tri;
      //  else if ( f->m_edge_count > 4)
      //    v->m_vertex_facet_type = ON_SubD::VertexFacetType::Ngon;
      //}
      //else
      //{
      //  const ON_SubDFace* f0 = v->m_faces[0];
      //  if (nullptr == f0 || f0->m_edge_count != f->m_edge_count)
      //    v->m_vertex_facet_type = ON_SubD::VertexFacetType::Mixed;
      //}
      //v->m_vertex_edge_order = ON_SubD::VertexEdgeOrder::unset;

      ON_SubDFacePtr* e_faces;
      if (e->m_face_count < 2)
      {
        e_faces = e->m_face2;
      }
      else
      {
        // Dale Lear, April 3, 2019 RH-49843 - we support non-manifold SubD objects now.
        //if (2 == e->m_face_count)
        //{
        //  // Getting this error in a valid situation means it is time
        //  // to support non-manifold subdivision objects.
        //  ON_SubDIncrementErrorCount();
        //  ON_WARNING("creating non-manifold subdivision object");
        //}
        if (false == m_heap.GrowEdgeFaceArrayByOne(e))
        {
          e->m_status.SetDamagedState(true);
          continue;
        }
        e_faces = e->m_facex - 2;
      }
      e_faces[e->m_face_count++] = ON_SubDFacePtr::Create(f, eptr);
    }
    f->m_edge_count = (unsigned short)edge_count;
  }

  if ( nullptr == AddFaceToLevel(f))
    return ON_SUBD_RETURN_ERROR(nullptr);

  return f;
}

unsigned int ON_SubDimple::AllocateFaceTexturePoints(const ON_SubDFace* face) const
{
  return const_cast<ON_SubDimple*>(this)->m_heap.AllocateFaceTexturePoints(face);
}

void ON_SubDimple::ReturnFaceTexturePoints(const ON_SubDFace* face) const
{
  const_cast<ON_SubDimple*>(this)->m_heap.ReturnFaceTexturePoints(face);
}


unsigned int ON_SubDHeap::AllocateFaceTexturePoints(const ON_SubDFace* face)
{
  if (nullptr == face)
    return false;
  unsigned texture_point_capacity = face->TexturePointsCapacity();
  if (texture_point_capacity < 3)
  {
    face->ClearTexturePoints();
    face->m_texture_points = this->Allocate3dPointArray(4 + face->m_edgex_capacity);
    texture_point_capacity = face->TexturePointsCapacity();
  }
  return texture_point_capacity;
}

void ON_SubDHeap::ReturnFaceTexturePoints(const ON_SubDFace* face)
{
  if (nullptr != face)
  {
    face->ClearTexturePoints();
    ON_3dPoint* a = face->m_texture_points;
    face->m_texture_points = nullptr;
    this->Return3dPointArray(a);
  }
}

bool ON_SubDEdge::UpdateEdgeSectorCoefficientsForExperts(bool bUnsetEdgeSectorCoefficientsOnly) const
{
  const double  input_sector_coefficient[2] = { m_sector_coefficient[0], m_sector_coefficient[1] };
  if (bUnsetEdgeSectorCoefficientsOnly)
  {
    if (input_sector_coefficient[0] >= 0.0 && input_sector_coefficient[0] <= 1.0
      && input_sector_coefficient[1] >= 0.0 && input_sector_coefficient[1] <= 1.0
      )
      return false;
  }
  m_sector_coefficient[0] = ON_SubDSectorType::IgnoredSectorCoefficient;
  m_sector_coefficient[1] = ON_SubDSectorType::IgnoredSectorCoefficient;
  if (ON_SubDEdgeTag::Smooth == m_edge_tag || ON_SubDEdgeTag::SmoothX == m_edge_tag)
  {
    const unsigned int tagged_end_index = TaggedEndIndex();
    if (tagged_end_index < 2)
    {
      m_sector_coefficient[tagged_end_index] = ON_SubDSectorType::Create( this, tagged_end_index).SectorCoefficient();
    }
    else if (2 == tagged_end_index)
    {
      if (ON_SubDEdgeTag::Smooth == m_edge_tag && 2 == m_face_count )
        const_cast<ON_SubDEdge*>(this)->m_edge_tag = ON_SubDEdgeTag::SmoothX;

      if (ON_SubDEdgeTag::Smooth == m_edge_tag)
        const_cast<ON_SubDEdge*>(this)->m_edge_tag = ON_SubDEdgeTag::Crease;
      else if (ON_SubDEdgeTag::SmoothX == m_edge_tag)
      {
        m_sector_coefficient[0] = ON_SubDSectorType::Create( this, 0).SectorCoefficient();
        m_sector_coefficient[1] = ON_SubDSectorType::Create( this, 1).SectorCoefficient();
      }
    }
  }

  const bool bNoChanges 
    =  input_sector_coefficient[0] == m_sector_coefficient[0]
    && input_sector_coefficient[1] == m_sector_coefficient[1];

  return (false == bNoChanges);
}

unsigned int ON_SubDLevel::UpdateEdgeSectorCoefficients(
  bool bUnsetEdgeSectorCoefficientsOnly
  ) const
{
  unsigned int changed_edge_count = 0;
  for (const ON_SubDEdge* edge = m_edge[0]; nullptr != edge; edge = edge->m_next_edge)
  {
    if (const_cast<ON_SubDEdge*>(edge)->UpdateEdgeSectorCoefficientsForExperts(bUnsetEdgeSectorCoefficientsOnly))
      ++changed_edge_count;
  }
  return changed_edge_count;
}

class ON_SubDFace* ON_SubD::AddTriangleFace(
  class ON_SubDEdge* edge0,
  class ON_SubDEdge* edge1,
  class ON_SubDEdge* edge2
)
{
  ON_SubDEdge* edges[3] = { edge0,edge1,edge2 };
  return AddFace(edges, 3);
}

class ON_SubDFace* ON_SubD::AddQuadFace(
  class ON_SubDEdge* edge0,
  class ON_SubDEdge* edge1,
  class ON_SubDEdge* edge2,
  class ON_SubDEdge* edge3
  )
{
  ON_SubDEdge* edges[4] = { edge0,edge1,edge2,edge3 };
  return AddFace(edges, 4);
}

class ON_SubDFace* ON_SubD::AddTriangleFace(
  ON_SubDEdgePtr edge0,
  ON_SubDEdgePtr edge1,
  ON_SubDEdgePtr edge2
)
{
  ON_SubDEdgePtr eptr3[3] = { edge0,edge1,edge2 };
  return AddFace(eptr3, 3);
}

class ON_SubDFace* ON_SubD::AddQuadFace(
  ON_SubDEdgePtr edge0,
  ON_SubDEdgePtr edge1,
  ON_SubDEdgePtr edge2,
  ON_SubDEdgePtr edge3
  )
{
  ON_SubDEdgePtr eptr4[4] = { edge0,edge1,edge2,edge3 };
  return AddFace(eptr4, 4);
}

class ON_SubDFace* ON_SubD::AddFace(
  const ON_SimpleArray<ON_SubDEdge*>& edges
)
{
  return AddFace(edges.Array(), edges.UnsignedCount());
}

class ON_SubDFace* ON_SubD::AddFace(
  const ON_SimpleArray<ON_SubDEdgePtr>& edges
)
{
  return AddFace(edges.Array(), edges.UnsignedCount());
}

class ON_SubDFace* ON_SubD::AddFace(
  ON_SubDEdge *const* edge,
  unsigned int edge_count
  )
{
  if (edge_count < 3 || nullptr == edge)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (nullptr == edge[0] || nullptr == edge[0]->m_vertex[0] || nullptr == edge[0]->m_vertex[1] || edge[0]->m_vertex[0] == edge[0]->m_vertex[1])
    return ON_SUBD_RETURN_ERROR(nullptr);
  if ( edge[0] == edge[edge_count-1] )
    return ON_SUBD_RETURN_ERROR(nullptr);
  ON_SubDEdgePtr* eptr = (ON_SubDEdgePtr*)onmalloc(edge_count * sizeof(*eptr));
  if (nullptr == eptr)
    return ON_SUBD_RETURN_ERROR(nullptr);
  eptr[0] = ON_SubDEdgePtr::Create(
    edge[0],
    (edge[0]->m_vertex[0] == edge[1]->m_vertex[0] || edge[0]->m_vertex[0] == edge[1]->m_vertex[1]) ? 1 : 0
  );
  eptr[edge_count - 1] = ON_SubDEdgePtr::Null;
  for (unsigned int fei = 1; fei < edge_count; ++fei)
  {
    if (nullptr == edge[fei] || nullptr == edge[fei]->m_vertex[0] || nullptr == edge[fei]->m_vertex[1] || edge[fei]->m_vertex[0] == edge[fei]->m_vertex[1])
      break;
    if (edge[fei - 1] == edge[fei])
      break;
    const ON_SubDVertex* v = eptr[fei - 1].RelativeVertex(1);
    if (nullptr == v)
      break;
    eptr[fei] = ON_SubDEdgePtr::Create(edge[fei], v == edge[fei]->m_vertex[0] ? 0 : 1);
    if (v != eptr[fei].RelativeVertex(0))
      break;
  }

  ON_SubDFace* face
    = (eptr[edge_count - 1].IsNotNull() && eptr[0].RelativeVertex(0) == eptr[edge_count - 1].RelativeVertex(1))
    ? AddFace(eptr, edge_count)
    : nullptr;
  onfree(eptr);
  if (nullptr == face)
  {
    ON_SUBD_ERROR("Invalid input edge[] array");
  }
  return face;
}

class ON_SubDFace* ON_SubD::AddFace(
  const ON_SubDEdgePtr* edge,
  unsigned int edge_count
  )
{
  ON_SubDimple* subdimple = SubDimple(true);
  return (nullptr != subdimple) ? subdimple->AddFace(edge_count, edge) : nullptr;
}


class ON_SubDFace* ON_SubD::AddFaceForExperts(
  unsigned int candiate_face_id,
  const ON_SubDEdgePtr* edge,
  unsigned int edge_count
  )
{
  ON_SubDimple* subdimple = SubDimple(true);
  return (nullptr != subdimple) ? subdimple->AddFace(candiate_face_id, edge_count, edge) : nullptr;
}

bool ON_SubD::ReturnFaceForExperts(
  ON_SubDFace* f
)
{
  if (nullptr == f)
    return false;

  if (this->InSubD(f) && f->IsActive() && 0 == f->m_edge_count)
  {
    ON_SubDimple* subdimple = SubDimple(false);
    if (nullptr != subdimple)
    {
      subdimple->ReturnFace(f);
      return true;
    }
  }

  // Caller is not an expert but a crash has been prevented.
  return ON_SUBD_RETURN_ERROR(false); 
}

bool ON_SubD::AddFaceTexturePoints(
  const class ON_SubDFace* face,
  const class ON_3dPoint* texture_points,
  size_t texture_points_count
) const
{
  if (nullptr == face)
    return false;
  face->ClearTexturePoints();
  const unsigned int face_edge_count = face->EdgeCount();
  if (nullptr != texture_points && texture_points_count >= face_edge_count && face_edge_count >= 3)
  {
    const ON_SubDimple* subdimple = SubDimple();
    if (nullptr != subdimple)
    {
      const unsigned capacity = subdimple->AllocateFaceTexturePoints(face);
      if (capacity >= face_edge_count)
      {
        for (unsigned i = 0; i < face_edge_count; ++i)
          face->SetTexturePoint(i, texture_points[i]);
      }
    }
  }
  return face->TexturePointsAreSet();
}

unsigned int ON_SubD::AllocateFaceTexturePoints(
  const class ON_SubDFace* face
) const
{
  if (nullptr == face)
    return false;
  const unsigned int face_edge_count = face->EdgeCount();
  if (face_edge_count >= 3)
  {
    const ON_SubDimple* subdimple = SubDimple();
    if (nullptr != subdimple)
      return subdimple->AllocateFaceTexturePoints(face);
  }
  face->ClearTexturePoints();
  return 0;
}

unsigned int ON_SubDFace::TexturePointsCapacity() const
{
  return ON_SubDHeap::Managed3dPointArrayCapacity(this->m_texture_points);
}

bool ON_SubDFace::TexturePointsAreSet() const
{
  return
    0 != (this->m_texture_status_bits & ON_SubDFace::TextureStatusBits::TexturePointsSet)
    && TexturePointsCapacity() >= EdgeCount()
    && EdgeCount() >= 3
    ;
}

bool ON_SubDFace::SetTexturePoint(
  unsigned i,
  ON_3dPoint texture_point
) const
{
  const unsigned texture_point_capacity = this->TexturePointsCapacity();
  if (i < texture_point_capacity)
  {
    this->m_texture_points[i] = texture_point;
    this->m_texture_status_bits |= ON_SubDFace::TextureStatusBits::TexturePointsSet;
    return true;
  }
  return false;
}

void ON_SubDFace::ClearTexturePoints() const
{
  this->m_texture_status_bits &= ON_SubDFace::TextureStatusBits::NotTexturePointsBitsMask;
}

const ON_3dPoint ON_SubDFace::TexturePoint(
  unsigned int i
) const
{
  const unsigned edge_count = this->EdgeCount();
  return (i < edge_count&& TexturePointsAreSet()) ? this->m_texture_points[i] : ON_3dPoint::NanPoint;
}

const ON_3dPoint ON_SubDFace::TextureCenterPoint() const
{
  const unsigned edge_count = this->EdgeCount();
  if (edge_count >= 3 && TexturePointsAreSet())
  {
    ON_3dPoint c = ON_3dPoint::Origin;
    for (unsigned i = 0; i < edge_count; ++i)
      c += m_texture_points[i];
    const double d = edge_count;
    c.x /= d;
    c.y /= d;
    c.z /= d;
    return c;
  }
  return ON_3dPoint::NanPoint;
}


bool ON_SubD::AddFaceEdgeConnection(
  ON_SubDFace* face,
  unsigned int i,
  ON_SubDEdge* edge,
  ON__UINT_PTR edge_direction
  )
{
  return AddFaceEdgeConnection(face, i, ON_SubDEdgePtr::Create(edge, edge_direction));
}

bool ON_SubD::AddFaceEdgeConnection(
  ON_SubDFace* face,
  unsigned int i,
  ON_SubDEdgePtr eptr
)
{
  return AddFaceEdgeConnection(face, i, eptr, false, false);
}

bool ON_SubD::AddFaceEdgeConnection(ON_SubDFace* face, unsigned int i, ON_SubDEdgePtr eptr, bool bAddbAddFaceToRelativeVertex0, bool bAddbAddFaceToRelativeVertex1)
{
  if (nullptr == face && i >= ON_SubDFace::MaximumEdgeCount)
  {
    return ON_SUBD_RETURN_ERROR(false);
  }

  unsigned int face_edge_count = (unsigned int)face->m_edge_count + 1U;
  if ( face_edge_count <= i )
    face_edge_count = i+1;

  ON_SubDEdge* edge = eptr.Edge();
  if (nullptr != edge)
  {
    if (edge->m_face_count >= edge->m_facex_capacity + (unsigned short)2)
    {
      if (false == GrowEdgeFaceArray(edge, 0))
        return ON_SUBD_RETURN_ERROR(false);
    }

    ON_SubDFacePtr fptr = ON_SubDFacePtr::Create(face,eptr.EdgeDirection());

    unsigned short efi = edge->m_face_count;
    if ( efi < 2 )
      edge->m_face2[efi] = fptr;
    else
    {
      if ( nullptr == edge->m_facex )
        return ON_SUBD_RETURN_ERROR(false);
      edge->m_facex[efi - 2] = fptr;
    }
    edge->m_face_count++;
  }

  if (face_edge_count > ((unsigned int)face->m_edgex_capacity) + 4U)
  {
    if (false == GrowFaceEdgeArray(face,face_edge_count))
      return ON_SUBD_RETURN_ERROR(false);
  }

  if (i >= ((unsigned int)face->m_edge_count))
  {
    unsigned int j = face->m_edge_count;
    for (/*empty init*/;j < 4; j++)
      face->m_edge4[j] = ON_SubDEdgePtr::Null;
    for (/*empty init*/;j < i; j++)
      face->m_edgex[j-4] = ON_SubDEdgePtr::Null;
  }
  else
  {
    for (unsigned int j = face_edge_count - 1; j > i; j--)
    {
      if (j > 4)
        face->m_edgex[j - 4] = face->m_edgex[j - 5];
      else if (4 == j)
        face->m_edgex[0] = face->m_edge4[3];
      else
        face->m_edge4[j] = face->m_edge4[j - 1];
    }
  }

  if ( i < 4 )
    face->m_edge4[i] = eptr;
  else 
    face->m_edgex[i-4] = eptr;
  face->m_edge_count = (unsigned short)face_edge_count;

  for (unsigned evi = 0; evi < 2; ++evi)
  {
    ON_SubDVertex* v = const_cast<ON_SubDVertex*>((0 == evi ? bAddbAddFaceToRelativeVertex0 : bAddbAddFaceToRelativeVertex1) ? eptr.RelativeVertex(evi) : nullptr);
    if (nullptr != v)
    {
      if ( false == this->GrowVertexFaceArray(v, v->m_face_count + 1))
        return ON_SUBD_RETURN_ERROR(false);
      v->m_faces[v->m_face_count++] = face;
    }
  }

  return true;
}


bool ON_SubD::SetFaceBoundary(
  ON_SubDFace* face,
  const ON_SimpleArray<ON_SubDEdgePtr>& edges
)
{
  return SetFaceBoundary(face, edges.Array(), edges.UnsignedCount());
}

bool ON_SubD::SetFaceBoundary(
  ON_SubDFace* face,
  const ON_SubDEdgePtr* edges,
  size_t edge_count
)
{
  // Do a little validation to prevent disasters. 
  if (nullptr == face)
    return ON_SUBD_RETURN_ERROR(false);
  if (0 != face->m_edge_count)
    return ON_SUBD_RETURN_ERROR(false);
  if (nullptr == edges || edge_count < 3 || edge_count > ((size_t)ON_SubDFace::MaximumEdgeCount))
    return ON_SUBD_RETURN_ERROR(false);
  const ON_SubDVertex* v1 = edges[edge_count - 1].RelativeVertex(1);
  if ( nullptr == v1)
    return ON_SUBD_RETURN_ERROR(false);
  for (size_t fei = 0; fei < edge_count; ++fei)
  {
    const ON_SubDVertex* v0 = edges[fei].RelativeVertex(0);
    if ( v0 != v1)
      return ON_SUBD_RETURN_ERROR(false);
    v1 = edges[fei].RelativeVertex(1);
    if ( nullptr == v1 || v0 == v1)
      return ON_SUBD_RETURN_ERROR(false);
  }

  // set face-edge pointers and add face to vertex face arrays
  if (false == this->GrowFaceEdgeArray(face, edge_count))
    return ON_SUBD_RETURN_ERROR(false);
  for (size_t fei = 0; fei < edge_count; ++fei)
  {
    ON_SubDEdgePtr eptr = edges[fei];
    if (false == this->AddFaceEdgeConnection(face, (unsigned)fei, eptr, true, false))
      return ON_SUBD_RETURN_ERROR(false);
  }

  return true;
}


bool ON_SubD::RemoveFaceEdgeConnection(
  ON_SubDFace* face,
  ON_SubDEdge* edge
  )
{
  ON_SubDEdgePtr removed_edge;
  return RemoveFaceEdgeConnection(face, face->EdgeArrayIndex(edge), removed_edge);
}

bool ON_SubD::RemoveFaceEdgeConnection(
  ON_SubDFace* face,
  unsigned int i
  )
{
  ON_SubDEdgePtr removed_edge;
  return RemoveFaceEdgeConnection(face, i, removed_edge);
}

bool ON_SubD::RemoveFaceEdgeConnection(
  ON_SubDFace* face,
  unsigned int i,
  ON_SubDEdgePtr& removed_edge
  )
{
  removed_edge = ON_SubDEdgePtr::Null;
  if ( nullptr == face || i >= (unsigned int)face->m_edge_count )
  {
    return ON_SUBD_RETURN_ERROR(false);
  }

  if ( false == face->RemoveEdgeFromArray(i,removed_edge) )
    return ON_SUBD_RETURN_ERROR(false);

  ON_SubDEdge* edge = removed_edge.Edge();
  if (nullptr != edge)
  {
    if (false == edge->RemoveFaceFromArray(face))
      return ON_SUBD_RETURN_ERROR(false);
  }

  return true;
}

bool ON_SubD::RemoveFaceConnections(
  ON_SubDFace* face
)
{
  if ( nullptr == face )
  {
    return ON_SUBD_RETURN_ERROR(false);
  }
  if (face->m_edge_count > 0)
  {
    ON_SubDEdgePtr removed_edge;
    for (unsigned short fei = face->m_edge_count; fei > 0; --fei)
    {
      removed_edge = ON_SubDEdgePtr::Null;
      if (false == face->RemoveEdgeFromArray(fei - 1, removed_edge))
        return ON_SUBD_RETURN_ERROR(false);
      ON_SubDEdge* edge = removed_edge.Edge();
      if (nullptr != edge)
      {
        if (false == edge->RemoveFaceFromArray(face))
          return ON_SUBD_RETURN_ERROR(false);

        for (int evi = 0; evi < 2; ++evi)
        {
          ON_SubDVertex* v = const_cast<ON_SubDVertex*>(edge->m_vertex[evi]);
          if (nullptr != v)
          {
            for (unsigned short vfi = 0; vfi < v->m_face_count; ++vfi)
            {
              if (face == v->m_faces[vfi])
              {
                for (++vfi; vfi < v->m_face_count; ++vfi)
                  v->m_faces[vfi - 1] = v->m_faces[vfi];
                v->m_face_count--;
                break;
              }
            }
          }
        }

      }
    }
    face->m_edge_count = 0;
  }

  return true;
}



static bool ON_SubDFace_GetSubdivisionPointError(
  const class ON_SubDFace* face,
  double subdivision_point[3],
  bool bDamagedState
  )
{
  if (nullptr == subdivision_point)
    return ON_SUBD_RETURN_ERROR(false); // caller passed a null pointer - face is not necessarily damaged

  // make sure returned point is not used by a caller who doesn't bother to check return codes.
  subdivision_point[0] = ON_DBL_QNAN;
  subdivision_point[1] = ON_DBL_QNAN;
  subdivision_point[2] = ON_DBL_QNAN;

  if (nullptr == face) 
    return ON_SUBD_RETURN_ERROR(false);

  // face is damaged in some way - mark it
  face->m_status.SetDamagedState(bDamagedState);

  return ON_SUBD_RETURN_ERROR(false);
}

const ON_3dPoint ON_SubDFace::SubdivisionPoint() const
{
  ON_3dPoint S;
  return (GetSubdivisionPoint(&S.x) && S.IsValid()) ? S : ON_3dPoint::NanPoint;
}

const ON_3dPoint ON_SubDFacePtr::SubdivisionPoint() const
{
  const ON_SubDFace* f = this->Face();
  return (nullptr != f) ? f->SubdivisionPoint() : ON_3dPoint::NanPoint;
}


bool ON_SubDFace::GetSubdivisionPoint(
  double subdivision_point[3]
) const
{
  if (nullptr == subdivision_point)
    return ON_SubDFace_GetSubdivisionPointError(this, subdivision_point, false);

  if (GetSavedSubdivisionPoint(subdivision_point))
    return true;
    
  if (EvaluateCatmullClarkSubdivisionPoint(subdivision_point))
  {
    SetSavedSubdivisionPoint(subdivision_point);
    return true;
  }

  return false;
}

bool ON_SubDFace::EvaluateCatmullClarkSubdivisionPoint(double subdivision_point[3]) const
{
  if (nullptr == subdivision_point)
    return ON_SubDFace_GetSubdivisionPointError(this,subdivision_point,false);

  const unsigned int count = m_edge_count;
  if (count < 3)
    return ON_SubDFace_GetSubdivisionPointError(this, subdivision_point, true);

  const class ON_SubDEdgePtr* edge_ptr = m_edge4;

  ON__UINT_PTR e_ptr;
  const ON_SubDEdge* e;
  ON__UINT_PTR edir;
  const double* vertexP[4];

  // Use faster code for the case when the face is a quad.
  // Since this is a Catmull-Clark subdivision scheme, this
  // case is the most common by far and code that gives quads
  // special treatment will run noticeably faster.
  e_ptr = edge_ptr[0].m_ptr;
  e = ON_SUBD_EDGE_POINTER(e_ptr);
  if ( nullptr == e || nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1] )
    return ON_SubDFace_GetSubdivisionPointError(this, subdivision_point, true);
  edir = ON_SUBD_EDGE_DIRECTION(e_ptr);
  vertexP[0] = e->m_vertex[edir]->m_P;
  vertexP[1] = e->m_vertex[1 - edir]->m_P;

  e_ptr = edge_ptr[2].m_ptr;
  e = ON_SUBD_EDGE_POINTER(e_ptr);
  if (nullptr == e || nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
    return ON_SubDFace_GetSubdivisionPointError(this, subdivision_point, true);
  edir = ON_SUBD_EDGE_DIRECTION(e_ptr);
  vertexP[2] = e->m_vertex[edir]->m_P;
  vertexP[3] = e->m_vertex[1 - edir]->m_P;

  if (4 == count)
  {
    // most common case in quad subdivision schemes
    subdivision_point[0] = (vertexP[0][0] + vertexP[1][0] + vertexP[2][0] + vertexP[3][0])*0.25;
    subdivision_point[1] = (vertexP[0][1] + vertexP[1][1] + vertexP[2][1] + vertexP[3][1])*0.25;
    subdivision_point[2] = (vertexP[0][2] + vertexP[1][2] + vertexP[2][2] + vertexP[3][2])*0.25;
    return true;
  }

  if (3 == count)
  {
    // 2nd most common case in quad subdivision schemes
    subdivision_point[0] = (vertexP[0][0] + vertexP[1][0] + vertexP[2][0]) / 3.0;
    subdivision_point[1] = (vertexP[0][1] + vertexP[1][1] + vertexP[2][1]) / 3.0;
    subdivision_point[2] = (vertexP[0][2] + vertexP[1][2] + vertexP[2][2]) / 3.0;
    return true;
  }

  // count > 4
  double faceP[3]
    = {
    (vertexP[0][0] + vertexP[1][0] + vertexP[2][0] + vertexP[3][0]),
    (vertexP[0][1] + vertexP[1][1] + vertexP[2][1] + vertexP[3][1]),
    (vertexP[0][2] + vertexP[1][2] + vertexP[2][2] + vertexP[3][2]) 
    };

  if (nullptr == m_edgex)
  {
    return ON_SubDFace_GetSubdivisionPointError(this, subdivision_point, true);
  }

  edge_ptr = m_edgex - 4; // -4 because index i begins at 4
  unsigned int i;
  for (i = 4; i + 1 < count; i += 2)
  {
    e_ptr = edge_ptr[i].m_ptr;
    e = ON_SUBD_EDGE_POINTER(e_ptr);
    if (nullptr == e || nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
      return ON_SubDFace_GetSubdivisionPointError(this, subdivision_point, true);
    edir = ON_SUBD_EDGE_DIRECTION(e_ptr);
    vertexP[0] = e->m_vertex[edir]->m_P;
    vertexP[1] = e->m_vertex[1 - edir]->m_P;

    faceP[0] += vertexP[0][0];
    faceP[1] += vertexP[0][1];
    faceP[2] += vertexP[0][2];

    faceP[0] += vertexP[1][0];
    faceP[1] += vertexP[1][1];
    faceP[2] += vertexP[1][2];
  }

  if (i < count)
  {
    // odd number of edges and vertices
    e_ptr = edge_ptr[count - 1].m_ptr;
    e = ON_SUBD_EDGE_POINTER(e_ptr);
    if (nullptr == e || nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
      return ON_SubDFace_GetSubdivisionPointError(this, subdivision_point, true);
    edir = ON_SUBD_EDGE_DIRECTION(e_ptr);
    vertexP[0] = e->m_vertex[edir]->m_P;
    faceP[0] += vertexP[0][0];
    faceP[1] += vertexP[0][1];
    faceP[2] += vertexP[0][2];
  }

  const double n = count;

  subdivision_point[0] = faceP[0] / n;
  subdivision_point[1] = faceP[1] / n;
  subdivision_point[2] = faceP[2] / n;
  return true;
}

int ON_SubDComponentBase::CompareId(
  const ON_SubDComponentBase* lhs,
  const ON_SubDComponentBase* rhs
)
{
  if (lhs == rhs)
    return 0;
  // nulls at end of list
  if (nullptr == rhs)
    return -1;
  if (nullptr == lhs)
    return 1;
  if (lhs->m_id < rhs->m_id)
    return -1;
  if (lhs->m_id > rhs->m_id)
    return 1;
  return 0;
}

void ON_SubDComponentBase::ClearSavedSubdivisionPoint() const
{
  Internal_ClearSubdivisionPointAndSurfacePointFlags();
}

bool ON_SubDComponentBase::SetSavedSubdivisionPoint(
  const double subdivision_point[3]
  ) const
{
  if (nullptr == subdivision_point)
  {
    Internal_ClearSubdivisionPointAndSurfacePointFlags();
    return true;
  }
  
  if ( ON_IsValid(subdivision_point[0])
    && ON_IsValid(subdivision_point[1])
    && ON_IsValid(subdivision_point[2])
    )
  {
    m_saved_subd_point1[0] = subdivision_point[0];
    m_saved_subd_point1[1] = subdivision_point[1];
    m_saved_subd_point1[2] = subdivision_point[2];
    m_saved_points_flags |= ON_SUBD_CACHE_POINT_FLAG_BIT;
    return true;
  }

  Internal_ClearSubdivisionPointAndSurfacePointFlags();
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubDComponentBase::GetSavedSubdivisionPoint(
  double subdivision_point[3]
  ) const
{
  if ( 0 == (ON_SUBD_CACHE_POINT_FLAG_BIT & m_saved_points_flags) )
    return false;

  if (nullptr != subdivision_point)
  {
    subdivision_point[0] = m_saved_subd_point1[0];
    subdivision_point[1] = m_saved_subd_point1[1];
    subdivision_point[2] = m_saved_subd_point1[2];
  }

  return true;
}

const ON_3dPoint ON_SubDComponentBase::SavedSubdivisionPoint() const
{
  ON_3dPoint p(ON_3dPoint::NanPoint);
  return GetSavedSubdivisionPoint(&p.x) ? p : ON_3dPoint::NanPoint;
}

unsigned const ON_SubDComponentBase::SubdivisionLevel() const
{
  return (unsigned)m_level;
}

void ON_SubDComponentBase::SetSubdivisionLevel(unsigned level)
{
  if (level <= 255U)
    m_level = ((unsigned char)level);
}

const ON_ComponentStatus ON_SubDComponentBase::Status() const
{
  return m_status;
}

bool ON_SubDComponentBase::IsActive() const
{
  return (m_id > 0 && m_archive_id != ON_UNSET_UINT_INDEX);
}


bool ON_SubDComponentBase::IsSymmetrySetPrimaryMotif() const
{
  return 1 == this->m_symmetry_set_next.ComponentDirection();
}

bool ON_SubDComponentBase::InSymmetrySet() const
{
  return this->m_symmetry_set_next.IsNotNull();
}

bool ON_SubDComponentPtr::IsSymmetrySetPrimaryMotif() const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->IsSymmetrySetPrimaryMotif() : false;
}

bool ON_SubDComponentPtr::InSymmetrySet() const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->InSymmetrySet() : false;
}

bool ON_SubDComponentBase::Mark() const
{
  return m_status.RuntimeMark();
}

bool ON_SubDComponentBase::ClearMark() const
{
 return m_status.ClearRuntimeMark();
}

bool ON_SubDComponentBase::SetMark() const
{
  return m_status.SetRuntimeMark();
}

bool ON_SubDComponentBase::SetMark(
  bool bMark
) const
{
  return m_status.SetRuntimeMark(bMark);
}


ON__UINT8 ON_SubDComponentBase::MarkBits() const
{
  return m_status.MarkBits();
}

ON__UINT8 ON_SubDComponentBase::SetMarkBits(
  ON__UINT8 mark_bits
) const
{
  return m_status.SetMarkBits(mark_bits);
}

ON__UINT8 ON_SubDComponentBase::ClearMarkBits() const
{
  return m_status.SetMarkBits(0);
}

bool ON_SubDComponentPtr::IsActive() const
{
  const ON_SubDComponentBase* c = this->ComponentBase();
  return (nullptr != c) ? c->IsActive() : false;
}

bool ON_SubDVertexPtr::IsActive() const
{
  const ON_SubDVertex* v = ON_SUBD_VERTEX_POINTER(m_ptr);
  return (nullptr != v) ? v->IsActive() : false;
}

bool ON_SubDEdgePtr::IsActive() const
{
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_ptr);
  return (nullptr != e) ? e->IsActive() : false;
}

bool ON_SubDFacePtr::IsActive() const
{
  const ON_SubDFace* f = ON_SUBD_FACE_POINTER(m_ptr);
  return (nullptr != f) ? f->IsActive() : false;
}


const ON_ComponentStatus ON_SubDVertex::NeighborhoodStatusLogicalOr(
  bool bIncludeEdges,
  bool bIncludeFaces
) const
{
  ON_ComponentStatus s(m_status);
  if (bIncludeEdges && nullptr != m_edges)
  {
    for (unsigned short vei = 0; vei < m_edge_count; vei++)
    {
      const ON_SubDEdge* e = m_edges[vei].Edge();
      if (nullptr != e)
        s = ON_ComponentStatus::LogicalOr(s, e->m_status);
    }
  }
  if (bIncludeFaces && nullptr != m_faces)
  {
    for (unsigned short vfi = 0; vfi < m_face_count; vfi++)
    {
      const ON_SubDFace* f = m_faces[vfi];
      if (nullptr != f)
        s = ON_ComponentStatus::LogicalOr(s, f->m_status);
    }
  }
  return s;
}
  
const ON_ComponentStatus ON_SubDEdge::NeighborhoodStatusLogicalOr(
  bool bIncludeVertices,
  bool bIncludeFaces
) const
{
  ON_ComponentStatus s(m_status);
  if (bIncludeVertices)
  {
    for (unsigned int evi = 0; evi < 2; evi++)
    {
      const ON_SubDVertex* v = m_vertex[evi];
      if (nullptr != v)
        s = ON_ComponentStatus::LogicalOr(s, v->m_status);
    }
  }
  if (bIncludeFaces)
  {
    const ON_SubDFacePtr* fptr = m_face2;
    for (unsigned short vfi = 0; vfi < m_face_count; vfi++)
    {
      const ON_SubDFace* f = fptr->Face();
      if (nullptr != f)
        s = ON_ComponentStatus::LogicalOr(s, f->m_status);
      if (1 == vfi)
      {
        fptr = m_facex;
        if (nullptr == fptr)
          break;
      }
      else
        fptr++;
    }
  }
  return s;
}

const ON_ComponentStatus ON_SubDFace::NeighborhoodStatusLogicalOr(bool bIncludeVertices, bool bIncludeEdges) const
{
  ON_ComponentStatus s(m_status);
  if (bIncludeVertices || bIncludeEdges)
  {
    const ON_SubDEdgePtr* eptr = m_edge4;
    for (unsigned int fei = 0; fei < m_edge_count; fei++)
    {
      if (4 == fei)
      {
        eptr = m_edgex;
        if (nullptr == eptr)
          break;
      }
      const ON_SubDEdge* e = eptr->Edge();
      if (nullptr != e)
      {
        if (bIncludeEdges)
        {
          s = ON_ComponentStatus::LogicalOr(s, e->m_status);
        }
        if (bIncludeVertices)
        {
          const ON_SubDVertex* v = e->m_vertex[(0!=eptr->EdgeDirection())?1:0];
          if (nullptr != v)
            s = ON_ComponentStatus::LogicalOr(s, v->m_status);
        }
      }
      eptr++;
    }
  }
  return s;
}

static void Internal_ClearVertexNeighborhoodCache(const ON_SubDVertex* vertex)
{
  // Clear cached values for this vertex every component touching this vertex.
  vertex->ClearSavedSubdivisionPoints();
  for (unsigned short vei = 0; vei < vertex->m_edge_count; ++vei)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(vertex->m_edges[vei].m_ptr);
    if (nullptr != e)
      e->ClearSavedSubdivisionPoints();
  }
  for (unsigned short vfi = 0; vfi < vertex->m_face_count; ++vfi)
  {
    const ON_SubDFace* f = vertex->m_faces[vfi];
    if (nullptr != f)
      f->ClearSavedSubdivisionPoints();
  }
}

static void Internal_ClearFaceNeighborhoodCache(const ON_SubDFace* face)
{
  // Clear cached values for every component associated with this face.
  face->ClearSavedSubdivisionPoints();
  const ON_SubDEdgePtr* eptr = face->m_edge4;
  for (unsigned int efi = 0; efi < face->m_edge_count; ++efi, ++eptr)
  {
    if (4 == efi)
    {
      eptr = face->m_edgex;
      if ( nullptr == eptr || face->m_edgex_capacity < face->m_edge_count - 4)
      {
        ON_SUBD_ERROR("Invalid face edge count or edgex information.");
        break;
      }
    }
    const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
    if (nullptr != edge)
    {
      edge->ClearSavedSubdivisionPoints();
      edge->UnsetSectorCoefficientsForExperts();
      for (unsigned int evi = 0; evi < 2; evi++)
      {
        const ON_SubDVertex* vertex = edge->m_vertex[evi];
        if (nullptr == vertex)
          continue;
        Internal_ClearVertexNeighborhoodCache(vertex);
      }
    }
  }
}

void ON_SubDVertex::VertexModifiedNofification() const
{
  // NOTE WELL:
  //  This function is called by ON_SubDEdge::EdgeModifiedNotification() and ON_SubDFace::FaceModifiedNotification().

  ClearSavedSubdivisionPoints();

  if (nullptr != m_edges)
  {
    for (unsigned short vei = 0; vei < m_edge_count; vei++)
    {
      const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
      if (nullptr == edge)
        continue;
      edge->ClearSavedSubdivisionPoints();
      edge->UnsetSectorCoefficientsForExperts();
      const ON_SubDVertex* v1 = edge->m_vertex[1-ON_SUBD_EDGE_DIRECTION(m_edges[vei].m_ptr)];
      if (nullptr != v1)
        v1->ClearSavedSubdivisionPoints();
    }

    if (nullptr != m_faces)
    {
      // This is needed to clear cached information in the Catmull-Clark 
      // ring that is not immediately adjacent to this vertex but whose values
      // this vertex affects.
      for (unsigned short vfi = 0; vfi < m_face_count; vfi++)
      {
        const ON_SubDFace* face = m_faces[vfi];
        if (nullptr != face)
          Internal_ClearFaceNeighborhoodCache(face);
      }
    }
  }
}

void ON_SubDEdge::EdgeModifiedNofification() const
{
  // NOTE WELL:
  //  This function is called by ON_SubDFace::FaceModifiedNotification().

  ClearSavedSubdivisionPoints();
  UnsetSectorCoefficientsForExperts();
  for (unsigned int evi = 0; evi < 2; evi++)
  {
    if (nullptr != m_vertex[evi])
      m_vertex[evi]->VertexModifiedNofification();
  }
}

void ON_SubDEdge::UnsetSectorCoefficientsForExperts() const
{
  const_cast<ON_SubDEdge*>(this)->m_sector_coefficient[0] = ON_SubDSectorType::UnsetSectorCoefficient;
  const_cast<ON_SubDEdge*>(this)->m_sector_coefficient[1] = ON_SubDSectorType::UnsetSectorCoefficient;
}

void ON_SubDVertex::UnsetSectorCoefficientsForExperts(unsigned int relative_edge_end_dex) const
{
  for (unsigned short vei = 0; vei < m_edge_count; ++vei)
  {
    ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_edges[vei].m_ptr);
    if (nullptr == e)
      continue;
    ON__UINT_PTR edir = ON_SUBD_EDGE_DIRECTION(m_edges[vei].m_ptr);
    const unsigned evi
      = (relative_edge_end_dex < 2)
      ? ((0 == edir ? false : true) == (0 == relative_edge_end_dex ? false : true) ? 0U : 1U)
      : 2U;
    if ( evi < 2)
      e->m_sector_coefficient[evi] = ON_SubDSectorType::UnsetSectorCoefficient;
    else
    {
      e->m_sector_coefficient[0] = ON_SubDSectorType::UnsetSectorCoefficient;
      e->m_sector_coefficient[1] = ON_SubDSectorType::UnsetSectorCoefficient;
    }
  }
}

void ON_SubDFace::FaceModifiedNofification() const
{
  ClearSavedSubdivisionPoints();

  const ON_SubDEdgePtr* eptr = m_edge4;
  for (unsigned int efi = 0; efi < m_edge_count; efi++)
  {
    if (4 == efi)
    {
      eptr = m_edgex;
      if ( nullptr == eptr)
        break;
    }
    const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
    if (nullptr != edge)
      edge->EdgeModifiedNofification();
    eptr++;
  }
}

unsigned int ON_SubDFace::PackId() const
{
  return m_pack_id;
}

void ON_SubDFace::SetPackIdForExperts(
  unsigned int pack_id
)
{
  m_pack_id = pack_id;
}

bool ON_SubDFace::IsValidPackRect(
  ON_2dPoint pack_rect_origin,
  ON_2dVector pack_rect_size,
  int packing_rotation_degrees
)
{
  const double fuzzy_1 = 1.0 + ON_SQRT_EPSILON;
  bool rc 
    =  0.0 <= pack_rect_origin.x && pack_rect_origin.x < 1.0
    && 0.0 <= pack_rect_origin.y && pack_rect_origin.y < 1.0
    && 0.0 < pack_rect_size.x && (pack_rect_origin.x + pack_rect_size.x) <= fuzzy_1
    && 0.0 < pack_rect_size.y && (pack_rect_origin.y + pack_rect_size.y) <= fuzzy_1
    && 0 == packing_rotation_degrees % 90
    ;
  return rc;
}

bool ON_SubDFace::SetPackRectForExperts(ON_2dPoint pack_rect_origin, ON_2dVector pack_rect_size, int packing_rotation_degrees)
{
  // r deals with negative values of input packing_rotation_degrees.
  const int r = ((packing_rotation_degrees % 360) + 360) % 360;
  const bool bValidPackRectangle = ON_SubDFace::IsValidPackRect(pack_rect_origin, pack_rect_size, packing_rotation_degrees);
  if (bValidPackRectangle)
  {
    m_pack_rect_origin[0] = pack_rect_origin.x;
    m_pack_rect_origin[1] = pack_rect_origin.y;
    m_pack_rect_size[0] = pack_rect_size.x;
    m_pack_rect_size[1] = pack_rect_size.y;

    ON_SubDFace::PackStatusBits packing_rotation = ON_SubDFace::PackStatusBits::PackingRotate0;
    switch (r)
    {
    case 90:
      packing_rotation = ON_SubDFace::PackStatusBits::PackingRotate90;
      break;
    case 180:
      packing_rotation = ON_SubDFace::PackStatusBits::PackingRotate180;
      break;
    case 270:
      packing_rotation = ON_SubDFace::PackStatusBits::PackingRotate270;
      break;
    }
    m_pack_status_bits = ON_SubDFace::PackStatusBits::PackRectSet;
    m_pack_status_bits |= packing_rotation;
  }
  else
  {
    ON_SUBD_ERROR("Invalid pack rect input");
    ClearPackRect();
  }
  return bValidPackRectangle;
}

void ON_SubDFace::ClearPackRect()
{
  m_pack_rect_origin[0] = ON_DBL_QNAN;
  m_pack_rect_origin[1] = ON_DBL_QNAN;
  m_pack_rect_size[0] = ON_DBL_QNAN;
  m_pack_rect_size[1] = ON_DBL_QNAN;
  m_pack_status_bits = 0;
}

void ON_SubDFace::ClearPackId()
{
  m_pack_id = 0;
  m_pack_rect_origin[0] = ON_DBL_QNAN;
  m_pack_rect_origin[1] = ON_DBL_QNAN;
  m_pack_rect_size[0] = ON_DBL_QNAN;
  m_pack_rect_size[1] = ON_DBL_QNAN;
  m_pack_status_bits = 0;
}

bool ON_SubDFace::PackRectIsSet() const
{
  return 0 != (m_pack_status_bits & ON_SubDFace::PackStatusBits::PackRectSet);
}

const ON_2dPoint ON_SubDFace::PackRectOrigin() const
{
  return ON_2dPoint(m_pack_rect_origin);
}

const ON_2dVector ON_SubDFace::PackRectSize() const
{
  return ON_2dVector(m_pack_rect_size);
}

unsigned int ON_SubDFace::PackRectRotationDegrees() const
{
  if (0 == (m_pack_status_bits & ON_SubDFace::PackStatusBits::PackRectSet))
    return 0;
  unsigned int packing_rotation_degrees = 0;
  switch (m_pack_status_bits & ON_SubDFace::PackStatusBits::PackingRotateMask)
  {
  case ON_SubDFace::PackStatusBits::PackingRotate90:
    packing_rotation_degrees = 90;
    break;
  case ON_SubDFace::PackStatusBits::PackingRotate180:
    packing_rotation_degrees = 180;
    break;
  case ON_SubDFace::PackStatusBits::PackingRotate270:
    packing_rotation_degrees = 270;
    break;
  }
  return packing_rotation_degrees;
}

double ON_SubDFace::PackRectRotationRadians() const
{
  if (0 == (m_pack_status_bits & ON_SubDFace::PackStatusBits::PackRectSet))
    return ON_DBL_QNAN;
  double x = 0.0;
  switch (m_pack_status_bits & ON_SubDFace::PackStatusBits::PackingRotateMask)
  {
  case ON_SubDFace::PackStatusBits::PackingRotate90:
    x = 1.0;
    break;
  case ON_SubDFace::PackStatusBits::PackingRotate180:
    x = 2.0;
    break;
  case ON_SubDFace::PackStatusBits::PackingRotate270:
    x = 3.0;
    break;
  }
  return x * 0.5 * ON_PI;
}

const ON_2dPoint ON_SubDFace::PackRectCorner(bool bGridOrder, int corner_index) const
{
  if (0 == (m_pack_status_bits & ON_SubDFace::PackStatusBits::PackRectSet))
    return ON_2dPoint::NanPoint;

  corner_index = ((corner_index % 4) + 4) % 4;
  // now corner_index = 0,1,2 or 3.

  if (bGridOrder)
  {
    if (2 == corner_index)
      corner_index = 3;
    else if (3 == corner_index)
      corner_index = 2;
  }
  // now corner index is a counter-clockwise corner index

  int packrot_dex = 0;
  switch (m_pack_status_bits & ON_SubDFace::PackStatusBits::PackingRotateMask)
  {
  case ON_SubDFace::PackStatusBits::PackingRotate90:
    packrot_dex = 3;
    break;
  case ON_SubDFace::PackStatusBits::PackingRotate180:
    packrot_dex = 2;
    break;
  case ON_SubDFace::PackStatusBits::PackingRotate270:
    packrot_dex = 1;
    break;
  }

  corner_index = (corner_index + packrot_dex) % 4;
  // now the packing rotation is taken into account.

  ON_2dPoint corner = PackRectOrigin();
  const ON_2dVector delta = PackRectSize();
  switch (corner_index)
  {
  case 1:
    corner.x += delta.x;
    break;
  case 2:
    corner.x += delta.x;
    corner.y += delta.y;
    break;
  case 3:
    corner.y += delta.y;
    break;
  }

  return corner;
}

bool ON_SubDFace::GetFacePackRectCorners(bool bGridOrder, ON_2dPoint face_pack_rect_corners[4]) const
{
  if (nullptr != face_pack_rect_corners)
  {
    if (this->PackRectIsSet())
    {
      face_pack_rect_corners[0] = PackRectCorner(bGridOrder, 0);
      face_pack_rect_corners[1] = PackRectCorner(bGridOrder, 1);
      face_pack_rect_corners[2] = PackRectCorner(bGridOrder, 2);
      face_pack_rect_corners[3] = PackRectCorner(bGridOrder, 3);
      return true;
    }
    face_pack_rect_corners[0] = ON_2dPoint::NanPoint;
    face_pack_rect_corners[1] = ON_2dPoint::NanPoint;
    face_pack_rect_corners[2] = ON_2dPoint::NanPoint;
    face_pack_rect_corners[3] = ON_2dPoint::NanPoint;
  }
  return false;
}

void ON_SubDComponentBase::Internal_ClearSubdivisionPointAndSurfacePointFlags() const
{
  ON_SUBD_CACHE_CLEAR_POINT_FLAG(m_saved_points_flags);
  ON_SUBD_CACHE_CLEAR_LIMITLOC_FLAG(m_saved_points_flags);
}

bool ON_SubDComponentBase::Internal_SubdivisionPointFlag() const
{
  return (0 != ON_SUBD_CACHE_POINT_FLAG(m_saved_points_flags));
}

void ON_SubDComponentBase::Internal_ClearSubdivisionPointFlag() const
{
  ON_SUBD_CACHE_CLEAR_POINT_FLAG(m_saved_points_flags);
}

bool ON_SubDComponentBase::Internal_SurfacePointFlag() const
{
  return (0 != ON_SUBD_CACHE_LIMITLOC_FLAG(m_saved_points_flags));
}

void ON_SubDComponentBase::Internal_ClearSurfacePointFlag() const
{
  ON_SUBD_CACHE_CLEAR_LIMITLOC_FLAG(m_saved_points_flags);
}

bool ON_SubDComponentBase::SavedSubdivisionPointIsSet() const
{
  return 
    (0 != ON_SUBD_CACHE_POINT_FLAG(m_saved_points_flags))
    ? (ON_IS_VALID(m_saved_subd_point1[0]) && ON_IS_VALID(m_saved_subd_point1[1]) && ON_IS_VALID(m_saved_subd_point1[2]))
    : false;
}

bool ON_SubDEdge::EdgeSurfaceCurveIsSet() const
{
  return false;
}

bool ON_SubDComponentBase::SubdivisionDisplacementIsNonzero() const
{
  // deprecated - never used.
  return false;
}

bool ON_SubDComponentBase::SetSubdivisionDisplacement(const double*)
{
  // deprecated - never used.
  return false;
}

void ON_SubDComponentBase::ClearSubdivisionDisplacement() const
{
  // deprecated - never used.
}

bool ON_SubDComponentBase::GetSubdivisionDisplacement(double*) const
{
  // deprecated - never used.
  return false;
}

const ON_3dVector ON_SubDComponentBase::SubdivisionDisplacement() const
{
  // deprecated - never used.
  return ON_3dVector::ZeroVector;
}

void ON_SubDComponentBase::Internal_SetSavedSurfacePointFlag(bool bSavedSurfacePointFlag) const
{
  if (bSavedSurfacePointFlag)
    m_saved_points_flags |= ON_SUBD_CACHE_LIMITLOC_FLAG_BIT;
  else
    Internal_ClearSurfacePointFlag();
}


void ON_SubDComponentBase::Internal_SetModified1Flag() const
{
  m_saved_points_flags |= ON_SubDComponentBase::ModifiedFlags::Modified1Bit;
}

void ON_SubDComponentBase::Internal_SetModified2Flag() const
{
  m_saved_points_flags |= ON_SubDComponentBase::ModifiedFlags::Modified1Bit;
}

void ON_SubDComponentBase::Internal_ClearModifiedFlags() const
{
  m_saved_points_flags &= ~ON_SubDComponentBase::ModifiedFlags::ModifiedFlagsMask;
}

bool ON_SubDComponentBase::Internal_Modified1IsSet() const
{
  return (0 != (m_saved_points_flags & ON_SubDComponentBase::ModifiedFlags::Modified1Bit));
}

bool ON_SubDComponentBase::Internal_Modified1or2IsSet() const
{
  return (0 != (m_saved_points_flags & ON_SubDComponentBase::ModifiedFlags::ModifiedFlagsMask));
}

bool ON_SubDFace::ReverseEdgeList()
{
  const unsigned int edge_count = m_edge_count;
  if ( 0 == edge_count)
    return true;
  if (edge_count > 4 && nullptr == m_edgex)
  {
    return ON_SUBD_RETURN_ERROR(false);
  }

  bool has_tpoints{ TexturePointsAreSet() };
  constexpr int buffer_size = 16;
  ON_SubDEdgePtr eptr_buffer[buffer_size]{};
  ON_3dPoint tpoint_buffer[buffer_size]{};
  ON_SubDEdgePtr* reversed_eptrs{ nullptr };
  ON_3dPoint* reversed_tpoints{ nullptr };
  if (edge_count <= buffer_size) {
    reversed_eptrs = eptr_buffer;
    reversed_tpoints = tpoint_buffer;
  }
  else
  {
    reversed_eptrs = new(std::nothrow) ON_SubDEdgePtr[edge_count];
    if (has_tpoints)
      reversed_tpoints = new(std::nothrow) ON_3dPoint[edge_count];
  }


  if (nullptr == reversed_eptrs)
    return ON_SUBD_RETURN_ERROR(false);
  if (has_tpoints && nullptr == reversed_tpoints)
  {
    has_tpoints = false;
    ClearTexturePoints();
  }

  if (!has_tpoints)
  {
    for (unsigned int fei = 0; fei < edge_count; fei++)
    {
      reversed_eptrs[fei] = ON_SubDEdgePtr::Null;
    }
  }
  else
  {
    for (unsigned int fei = 0; fei < edge_count; fei++)
    {
      reversed_eptrs[fei] = ON_SubDEdgePtr::Null;
      reversed_tpoints[fei] = ON_3dPoint::UnsetPoint;
    }
  }


  ON_SubDEdgePtr* face_eptrs = m_edge4;
  ON_3dPoint* face_tpoints = m_texture_points;
  for (unsigned int fei = 0; fei < edge_count; fei++, face_eptrs++, face_tpoints++)
  {
    if (4 == fei)
      face_eptrs = m_edgex;

    ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(face_eptrs->m_ptr);
    if ( nullptr == e)
      continue;
    ON__UINT_PTR edir = ON_SUBD_EDGE_DIRECTION(face_eptrs->m_ptr);
    reversed_eptrs[edge_count-1-fei] = ON_SubDEdgePtr::Create(e,1-edir);

    ON_SubDFacePtr* edges_fptrs = e->m_face2;
    const unsigned int face_count = e->m_face_count;
    for (unsigned int efi = 0; efi < face_count; efi++, edges_fptrs++)
    {
      if (2 == efi)
      {
        edges_fptrs = e->m_facex;
        if ( nullptr == edges_fptrs)
          break;
      }
      if ( this != ON_SUBD_FACE_POINTER(edges_fptrs->m_ptr) )
        continue;
      *edges_fptrs = ON_SubDFacePtr::Create(this,1-ON_SUBD_FACE_DIRECTION(edges_fptrs->m_ptr));
      break;
    }

    if (has_tpoints)
    {
      if (fei == 0)
        reversed_tpoints[0] = *face_tpoints;
      else
        reversed_tpoints[edge_count - fei] = *face_tpoints;
    }
  }

  if (!has_tpoints)
  {
    face_eptrs = m_edge4;
    for (unsigned int fei = 0; fei < edge_count; fei++, face_eptrs++)
    {
      if (4 == fei)
        face_eptrs = m_edgex;
      *face_eptrs = reversed_eptrs[fei];
    }
  }
  else
  {
    face_eptrs = m_edge4;
    face_tpoints = m_texture_points;
    for (unsigned int fei = 0; fei < edge_count; fei++, face_eptrs++, face_tpoints++)
    {
      if (4 == fei)
        face_eptrs = m_edgex;
      *face_eptrs = reversed_eptrs[fei];
      *face_tpoints = reversed_tpoints[fei];
    }
  }

  if (reversed_eptrs != eptr_buffer) {
    delete[] reversed_eptrs;
    if (has_tpoints)
      delete[] reversed_tpoints;
  }

  return true;
}

static bool ON_SubDEdge_GetSubdivisionPointError(
  const class ON_SubDEdge* edge,
  double edge_point[3],
  const double* edgeP[2],
  bool bDamagedState
  )
{
  if (nullptr == edge || nullptr == edge_point)
    return false; // caller passed a null pointer - edge is not necessarily damaged

  ON_SubDIncrementErrorCount();
  edge->m_status.SetDamagedState(bDamagedState);

  if (nullptr != edgeP && nullptr != edgeP[0] && nullptr != edgeP[1])
  {
    const double edgePsum[3] = { edgeP[0][0] + edgeP[1][0], edgeP[0][1] + edgeP[1][1], edgeP[0][2] + edgeP[1][2] };
    edge_point[0] = 0.5*edgePsum[0];
    edge_point[1] = 0.5*edgePsum[1];
    edge_point[2] = 0.5*edgePsum[2];
  }
  return true;
}

unsigned int ON_SubDEdge::GetFacePointSum(
  const ON_SubDFace* face,
  const ON_SubDEdge* edge,
  double* facePsum
  )
{
  const ON_SubDEdge* e;
  ON__UINT_PTR e_ptr, edir;
  const double* vertexP[2];

  if (nullptr == face)
    return 0;
  
  const unsigned int n = face->m_edge_count;

  if (3 == n)
  {
    if (edge == ON_SUBD_EDGE_POINTER(face->m_edge4[0].m_ptr))
      e_ptr = face->m_edge4[1].m_ptr;
    else if (edge == ON_SUBD_EDGE_POINTER(face->m_edge4[1].m_ptr))
      e_ptr = face->m_edge4[2].m_ptr;
    else if (edge == ON_SUBD_EDGE_POINTER(face->m_edge4[2].m_ptr))
      e_ptr = face->m_edge4[0].m_ptr;
    else
      return 0;
      e = ON_SUBD_EDGE_POINTER(e_ptr);
      if (nullptr == e)
        return 0;
      if (nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
        return 0;
      edir = ON_SUBD_EDGE_DIRECTION(e_ptr);
      if (edge->m_vertex[0] != e->m_vertex[edir] && edge->m_vertex[1] != e->m_vertex[edir])
        return 0;
      vertexP[0] = e->m_vertex[1 - edir]->m_P;
      facePsum[0] = vertexP[0][0];
      facePsum[1] = vertexP[0][1];
      facePsum[2] = vertexP[0][2];

      return n;
  }

  if (4 == n)
  {
    if (edge == ON_SUBD_EDGE_POINTER(face->m_edge4[0].m_ptr))
      e_ptr = face->m_edge4[2].m_ptr;
    else if (edge == ON_SUBD_EDGE_POINTER(face->m_edge4[1].m_ptr))
      e_ptr = face->m_edge4[3].m_ptr;
    else if (edge == ON_SUBD_EDGE_POINTER(face->m_edge4[2].m_ptr))
      e_ptr = face->m_edge4[0].m_ptr;
    else if (edge == ON_SUBD_EDGE_POINTER(face->m_edge4[3].m_ptr))
      e_ptr = face->m_edge4[1].m_ptr;
    else
      return 0;
    e = ON_SUBD_EDGE_POINTER(e_ptr);
    if (nullptr == e)
      return 0;
    if (nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
      return 0;
    edir = ON_SUBD_EDGE_DIRECTION(e_ptr);
    vertexP[0] = e->m_vertex[edir]->m_P;
    vertexP[1] = e->m_vertex[1 - edir]->m_P;
    facePsum[0] = vertexP[0][0] + vertexP[1][0];
    facePsum[1] = vertexP[0][1] + vertexP[1][1];
    facePsum[2] = vertexP[0][2] + vertexP[1][2];

    return n;
  }

  if (n < 3)
    return 0;

  const ON_SubDEdgePtr* edgeptr = face->m_edge4;
  const ON_SubDVertex* edge_vertex[2] = { edge->m_vertex[0], edge->m_vertex[1] };
  facePsum[0] = 0.0;
  facePsum[1] = 0.0;
  facePsum[2] = 0.0;
  for (unsigned i = 0; i < n; i++)
  {
    if (4 == i)
      edgeptr = face->m_edgex - 4;
    e = ON_SUBD_EDGE_POINTER(edgeptr[i].m_ptr);
    if (nullptr == e)
      return 0;
    if (edge == e)
      continue;
    edir = ON_SUBD_EDGE_DIRECTION(edgeptr[i].m_ptr);
    const ON_SubDVertex* e_vertex[2] = { e->m_vertex[edir], e->m_vertex[1 - edir] };
    if (nullptr == e_vertex[0] || nullptr == e_vertex[1])
      return 0;
    if (edge_vertex[0] != e_vertex[0] && edge_vertex[1] != e_vertex[0])
    {
      vertexP[0] = e_vertex[0]->m_P;
      facePsum[0] += vertexP[0][0];
      facePsum[1] += vertexP[0][1];
      facePsum[2] += vertexP[0][2];
    }
    if (i + 1 < n)
    {
      // start of next edge = end of this edge
      if (edge_vertex[0] != e_vertex[1] && edge_vertex[1] != e_vertex[1])
      {
        vertexP[0] = e_vertex[1]->m_P;
        facePsum[0] += vertexP[0][0];
        facePsum[1] += vertexP[0][1];
        facePsum[2] += vertexP[0][2];
      }
      i++;
      if (4 == i && n > 4)
        edgeptr = face->m_edgex - 4;
    }
  }

  return n;
}

const ON_3dPoint ON_SubDEdge::SubdivisionPoint() const
{
  ON_3dPoint S;
  return (GetSubdivisionPoint(&S.x) && S.IsValid()) ? S : ON_3dPoint::NanPoint;
}


bool ON_SubDEdge::GetSubdivisionPoint(
  double subdivision_point[3]
) const
{
  if (nullptr == subdivision_point)
    return ON_SubDEdge_GetSubdivisionPointError(this, subdivision_point, nullptr, false);

  if (GetSavedSubdivisionPoint(subdivision_point))
    return true;

  if (EvaluateCatmullClarkSubdivisionPoint(subdivision_point))
  {
    SetSavedSubdivisionPoint(subdivision_point);
    return true;
  }

  return false;
}

const ON_3dPoint ON_SubDEdge::ControlNetCenterPoint() const
{
  return 0.5*(ControlNetPoint(0) + ControlNetPoint(1));
}

const ON_3dVector ON_SubDEdge::ControlNetCenterNormal(
  unsigned int edge_face_index
) const
{
  const ON_SubDFace* face = Face(edge_face_index);
  return (nullptr != face) ? face->ControlNetCenterNormal() : ON_3dVector::NanVector;
}

bool ON_SubDEdge::EvaluateCatmullClarkSubdivisionPoint(double subdivision_point[3]) const
{
  if (nullptr == subdivision_point)
    return ON_SubDEdge_GetSubdivisionPointError(this, subdivision_point, nullptr, false);

  const ON_SubDVertex* edge_vertex[2] = { m_vertex[0], m_vertex[1] };
  if (nullptr == edge_vertex[0] || nullptr == edge_vertex[1])
    return ON_SubDEdge_GetSubdivisionPointError(this, subdivision_point, nullptr, true);

  const double* edgeP[2] = { edge_vertex[0]->m_P, edge_vertex[1]->m_P };
  const double edgePsum[3] = { edgeP[0][0] + edgeP[1][0], edgeP[0][1] + edgeP[1][1], edgeP[0][2] + edgeP[1][2] };

  if ( IsSmooth() )
  {
    // All smooth edges (Smooth and SmoothX tags) must have exactly two neighboring faces.
    // Both ends of a level 0 SmoothX edge can be non-smooth vertices but the SmoothX tag
    // indicates it is to be subdivided as a smooth edge.
    // All other smooth edge must have at least one edn attached to a smooth vertex.

    if (2 != m_face_count)
      return ON_SubDEdge_GetSubdivisionPointError(this, subdivision_point, edgeP, true);

    const ON_SubDFace* faces[2] = { ON_SUBD_FACE_POINTER(m_face2[0].m_ptr), ON_SUBD_FACE_POINTER(m_face2[1].m_ptr) };
    if (nullptr == faces[0] || nullptr == faces[1])
      return ON_SubDEdge_GetSubdivisionPointError(this, subdivision_point, edgeP, true);

    ON_3dPoint sharp_subdivision_point;
    const double edge_sharpness = this->GetSharpSubdivisionPoint(sharp_subdivision_point);
    if (edge_sharpness >= 1.0)
    {
      // sharp crease vertex with sharpness >= 1 at current level
      subdivision_point[0] = sharp_subdivision_point.x;
      subdivision_point[1] = sharp_subdivision_point.y;
      subdivision_point[2] = sharp_subdivision_point.z;
      return true;
    }

    // for each neighbor face, sum the vertex locations that are not on this edge
    double facePsum[2][3];
    const unsigned int face_edge_count[2]
      = { ON_SubDEdge::GetFacePointSum(faces[0], this, facePsum[0]),
      ON_SubDEdge::GetFacePointSum(faces[1], this, facePsum[1])
    };
    if (0 == face_edge_count[0] || 0 == face_edge_count[1])
      return ON_SubDEdge_GetSubdivisionPointError(this, subdivision_point, edgeP, true);

    const unsigned int tagged_end
      = (ON_SubDVertexTag::Smooth != edge_vertex[0]->m_vertex_tag)
      ? 0
      : ((ON_SubDVertexTag::Smooth != edge_vertex[1]->m_vertex_tag) ? 1 : ON_UNSET_UINT_INDEX);
    double EP[3];
    if (
      ON_UNSET_UINT_INDEX == tagged_end
      || 0.5 == m_sector_coefficient[tagged_end]
      || (ON_SubDEdgeTag::SmoothX == m_edge_tag)
      )
    {
      // ignore edge coefficients
      EP[0] = 0.375 * edgePsum[0];
      EP[1] = 0.375 * edgePsum[1];
      EP[2] = 0.375 * edgePsum[2];
    }
    else if (ON_SubDVertexTag::Smooth == edge_vertex[1 - tagged_end]->m_vertex_tag
      && m_sector_coefficient[tagged_end] > 0.0
      && m_sector_coefficient[tagged_end] < 1.0
      )
    {
      double w[2];
      w[tagged_end] = m_sector_coefficient[tagged_end];
      w[1 - tagged_end] = 1.0 - w[tagged_end];
      EP[0] = 0.75 * (w[0] * edgeP[0][0] + w[1] * edgeP[1][0]);
      EP[1] = 0.75 * (w[0] * edgeP[0][1] + w[1] * edgeP[1][1]);
      EP[2] = 0.75 * (w[0] * edgeP[0][2] + w[1] * edgeP[1][2]);
    }
    else
    {
      // error:
      //   Both ends of a smooth edge are tagged and coefficients are not ignored,
      //   or coefficients are incorrectly set
      //   or ...
      return ON_SubDEdge_GetSubdivisionPointError(this, subdivision_point, edgeP, true);
    }

    if (4 == face_edge_count[0] && 4 == face_edge_count[1])
    {
      // common case when both neighboring faces are quads
      subdivision_point[0] = EP[0] + 0.0625*(facePsum[0][0] + facePsum[1][0]);
      subdivision_point[1] = EP[1] + 0.0625*(facePsum[0][1] + facePsum[1][1]);
      subdivision_point[2] = EP[2] + 0.0625*(facePsum[0][2] + facePsum[1][2]);
      if (edge_sharpness > 0.0)
      {
        // sharp crease vertex with 0 < sharpness < 1 at the current level
        const double a = 1.0 - edge_sharpness;
        subdivision_point[0] = a * subdivision_point[0] + edge_sharpness * sharp_subdivision_point.x;
        subdivision_point[1] = a * subdivision_point[1] + edge_sharpness * sharp_subdivision_point.y;
        subdivision_point[2] = a * subdivision_point[2] + edge_sharpness * sharp_subdivision_point.z;
      }
      return true;
    }
    
    if (3 == face_edge_count[0] && 3 == face_edge_count[1])
    {
      // common case when both neighboring faces are triangles

      //// bug in evaluation prior to Nov 11, 2019
      ////subdivision_point[0] = EP[0] + 0.125*(facePsum[0][0] + facePsum[1][0]);
      ////subdivision_point[1] = EP[1] + 0.125*(facePsum[0][1] + facePsum[1][1]);
      ////subdivision_point[2] = EP[2] + 0.125*(facePsum[0][2] + facePsum[1][2]);
      subdivision_point[0] = EP[0] + (0.5*edgePsum[0] + facePsum[0][0] + facePsum[1][0]) / 12.0;
      subdivision_point[1] = EP[1] + (0.5*edgePsum[1] + facePsum[0][1] + facePsum[1][1]) / 12.0;
      subdivision_point[2] = EP[2] + (0.5*edgePsum[2] + facePsum[0][2] + facePsum[1][2]) / 12.0;
      if (edge_sharpness > 0.0)
      {
        // sharp crease vertex with 0 < sharpness < 1 at the current level
        const double a = 1.0 - edge_sharpness;
        subdivision_point[0] = a * subdivision_point[0] + edge_sharpness * sharp_subdivision_point.x;
        subdivision_point[1] = a * subdivision_point[1] + edge_sharpness * sharp_subdivision_point.y;
        subdivision_point[2] = a * subdivision_point[2] + edge_sharpness * sharp_subdivision_point.z;
      }
      return true;
    }

    // general formula works for all cases including face_edge_count[0] != face_count[2]
      //// bug in evaluation prior to Nov 11, 2019
    ////const double f0 = 0.125 / ((double)(face_edge_count[0] - 2));
    ////const double f1 = 0.125 / ((double)(face_edge_count[1] - 2));
    ////subdivision_point[0] = EP[0] + f0 * facePsum[0][0] + f1 * facePsum[1][0];
    ////subdivision_point[1] = EP[1] + f0 * facePsum[0][1] + f1 * facePsum[1][1];
    ////subdivision_point[2] = EP[2] + f0 * facePsum[0][2] + f1 * facePsum[1][2];

    const double f0 = (double)(face_edge_count[0] * 4U);
    const double f1 = (double)(face_edge_count[1] * 4U);
    const double x = 1.0 / f0 + 1.0 / f1 - 0.125;
    subdivision_point[0] = EP[0] + x * edgePsum[0] + facePsum[0][0] / f0 + facePsum[1][0] / f1;
    subdivision_point[1] = EP[1] + x * edgePsum[1] + facePsum[0][1] / f0 + facePsum[1][1] / f1;
    subdivision_point[2] = EP[2] + x * edgePsum[2] + facePsum[0][2] / f0 + facePsum[1][2] / f1;
    if (edge_sharpness > 0.0)
    {
      // sharp crease vertex with 0 < sharpness < 1 at the current level
      const double a = 1.0 - edge_sharpness;
      subdivision_point[0] = a * subdivision_point[0] + edge_sharpness * sharp_subdivision_point.x;
      subdivision_point[1] = a * subdivision_point[1] + edge_sharpness * sharp_subdivision_point.y;
      subdivision_point[2] = a * subdivision_point[2] + edge_sharpness * sharp_subdivision_point.z;
    }
    return true;
  }

  if ( IsCrease() )
  {
    subdivision_point[0] = 0.5*edgePsum[0];
    subdivision_point[1] = 0.5*edgePsum[1];
    subdivision_point[2] = 0.5*edgePsum[2];
    return true;
  }

  // invalid edge->m_edge_tag
  return ON_SubDEdge_GetSubdivisionPointError(this, subdivision_point, edgeP, true);
}











static unsigned int GetSectorBoundaryEdgesError()
{
  return ON_SUBD_RETURN_ERROR(0);
}

unsigned int ON_SubDEdge::GetSectorBoundaryEdges(
  unsigned int edge_vertex_index,
  ON_SubDEdgePtr* edge_ptr0,
  ON_SubDEdgePtr* edge_ptr1
  ) const
{
  if (nullptr != edge_ptr0)
    *edge_ptr0 = ON_SubDEdgePtr::Null;
  if (nullptr != edge_ptr1)
    *edge_ptr1 = ON_SubDEdgePtr::Null;

  const unsigned int edge_face_count = m_face_count;
  if (edge_face_count <= 0 || edge_face_count > 2)
    return GetSectorBoundaryEdgesError();

  if (2 == edge_face_count && ON_SubDEdgeTag::Crease == m_edge_tag)
    return GetSectorBoundaryEdgesError();

  if (0 != edge_vertex_index && 1 != edge_vertex_index)
    return GetSectorBoundaryEdgesError();

  const ON_SubDVertex* vertex = m_vertex[edge_vertex_index];
  if (nullptr == vertex || vertex->m_face_count <= 0)
    return GetSectorBoundaryEdgesError();

  const unsigned int vertex_face_count = vertex->m_face_count;
  unsigned int sector_face_count = 0;
  ON_SubDEdgePtr sector_boundary[2] = {};
  for (unsigned int edge_face_index = 0; edge_face_index < edge_face_count; edge_face_index++)
  {
    const ON_SubDEdge* edge0 = this;
    unsigned int edge0_end_index = edge_vertex_index;
    unsigned int edge0_face_index = edge_face_index;
    ON_SubDFacePtr face_ptr = edge0->m_face2[edge0_face_index];
    while (sector_face_count < vertex_face_count)
    {
      const ON_SubDFace* face = ON_SUBD_FACE_POINTER(face_ptr.m_ptr);
      if (0 == face)
        return GetSectorBoundaryEdgesError();
      ON__UINT_PTR face_dir = ON_SUBD_FACE_DIRECTION(face_ptr.m_ptr);

      sector_face_count++;

      unsigned int face_edge0_index = face->EdgeArrayIndex(edge0);
      if (ON_UNSET_UINT_INDEX == face_edge0_index)
        return 0;

      unsigned int face_edge1_index
        = face_edge0_index;
      face_edge1_index +=
        (1 == (edge0_end_index + face_dir))
        ? 1
        : (face->m_edge_count - 1);
      face_edge1_index %= face->m_edge_count;

      ON_SubDEdgePtr edge1_ptr = face->EdgePtr(face_edge1_index);
      const ON_SubDEdge* edge1 = ON_SUBD_EDGE_POINTER(edge1_ptr.m_ptr);
      if (nullptr == edge1)
        return GetSectorBoundaryEdgesError();

      unsigned int edge1_end_index = (0 == face_dir) ? (1 - edge0_end_index) : edge0_end_index;
      if (1 == ON_SUBD_EDGE_DIRECTION(edge1_ptr.m_ptr))
        edge1_end_index = 1 - edge1_end_index;
      if (vertex != edge1->m_vertex[edge1_end_index])
        return GetSectorBoundaryEdgesError();

      if ( edge1->IsSmooth() && 2 == edge1->m_face_count )
      {
        const ON_SubDFace* edge1_faces[2] = { ON_SUBD_FACE_POINTER(edge1->m_face2[0].m_ptr), ON_SUBD_FACE_POINTER(edge1->m_face2[1].m_ptr) };
        unsigned int edge1_face_index = (face == edge1_faces[0] ? 1 : 0);
        if (nullptr == edge1_faces[edge1_face_index] || face == edge1_faces[edge1_face_index])
          return GetSectorBoundaryEdgesError();
        face_ptr = edge1->m_face2[edge1_face_index];
        edge0 = edge1;
        edge0_face_index = edge1_face_index;
        edge0_end_index = edge1_end_index;
        continue;
      }

      sector_boundary[edge_face_index] = ON_SubDEdgePtr::Create(edge1, edge1_end_index);
      break;
    }
  }
  
  if (sector_face_count <= 0 || sector_boundary[0].IsNull())
    return GetSectorBoundaryEdgesError();
  if (1 == edge_face_count)
    sector_boundary[1] = ON_SubDEdgePtr::Create(this, edge_vertex_index);
  else if (sector_boundary[1].IsNull())
    return GetSectorBoundaryEdgesError();

  if (nullptr != edge_ptr0)
    *edge_ptr0 = sector_boundary[0];
  if (nullptr != edge_ptr1)
    *edge_ptr1 = sector_boundary[1];

  return sector_face_count;
}

class ON_ScratchBuffer
{
public:
  ON_ScratchBuffer(
    size_t sizeof_buffer,
    void* stack_buffer,
    size_t sizeof_stack_buffer
    )
    : m_buffer(nullptr)
    , m_heap_buffer(nullptr)
  {
    m_buffer
      = (sizeof_buffer > sizeof_stack_buffer || nullptr == stack_buffer)
      ? stack_buffer
      : (m_heap_buffer = new (std::nothrow) double[1 + sizeof_buffer / sizeof(double)]);
  }

  void* Buffer()
  {
    return m_buffer;
  }

  ~ON_ScratchBuffer()
  {
    if (nullptr != m_heap_buffer)
    {
      double* p = m_heap_buffer;
      m_heap_buffer = nullptr;
      delete[] p;
    }
  }

private:
  void* m_buffer;
  double* m_heap_buffer;

private:
  // prohibit use - no implementation
  ON_ScratchBuffer(const ON_ScratchBuffer&) = delete;
  ON_ScratchBuffer& operator=(const ON_ScratchBuffer&) = delete;
};

class FACE_AND_FACE_POINT
{
public:
  const ON_SubDFace* m_face;
  double m_faceP[3];
  static int CompareFacePointer(const void* a, const void* b);
};

int FACE_AND_FACE_POINT::CompareFacePointer(const void* a, const void* b)
{
  ON__UINT_PTR fa = (ON__UINT_PTR)(((const FACE_AND_FACE_POINT*)a)->m_face);
  ON__UINT_PTR fb = (ON__UINT_PTR)(((const FACE_AND_FACE_POINT*)b)->m_face);
  if (fa < fb)
    return -1;
  if (fa > fb)
    return 1;
  return 0;
}

const ON_3dPoint ON_SubDSectorSurfacePoint::Point() const
{
  return ON_3dPoint(m_limitP);
}

const ON_3dVector ON_SubDSectorSurfacePoint::Normal() const
{
  return ON_3dPoint(m_limitN);
}

const ON_3dVector ON_SubDSectorSurfacePoint::Tangent(int tangent_index) const
{
  if (0 == tangent_index)
    return ON_3dPoint(m_limitT1);
  if (1 == tangent_index)
    return ON_3dPoint(m_limitT2);
  return ON_3dVector::ZeroVector;
}


bool ON_SubDSectorSurfacePoint::IsUnset() const
{
  return (m_limitP[0] == ON_UNSET_VALUE);
}

bool ON_SubDSectorSurfacePoint::IsNan() const
{
  return !(m_limitP[0] == m_limitP[0]);
}

bool ON_SubDSectorSurfacePoint::IsZero() const
{
  const double* p = m_limitP;
  const double* p1 = p+12;
  while (p < p1)
  {
    if (!(0.0 == *p++))
      return false;
  }
  return true;
}

bool ON_SubDSectorSurfacePoint::IsSet(
  bool bUndefinedNormalIsPossible
) const
{
  double x, y;
  const double* p = m_limitP;
  const double* p1 = p+3;
  while (p < p1)
  {
    x = *p++;
    if (ON_UNSET_VALUE == x || !(x == x))
      return false;
  }

  p = m_limitT1;
  p1 = p + 6;
  while (p < p1)
  {
    const double* p2 = p + 3;
    y = 0.0;
    while (p < p2)
    {
      x = *p++;
      if (ON_UNSET_VALUE == x || !(x == x))
        return false;
      if (0.0 != x)
        y = x;
    }
    if (false == bUndefinedNormalIsPossible)
    {
      if (!(y != 0.0))
        return false;
    }

    p = m_limitN;
    p1 = p + 3;
    y = 0.0;
    while (p < p1)
    {
      x = *p++;
      if (ON_UNSET_VALUE == x || !(x == x))
        return false;
      y += x * x;
    }
    if (false == bUndefinedNormalIsPossible)
    {
      if (!(fabs(y - 1.0) <= 1e-4))
        return false;
    }
  }

  return true;
}

void ON_SubDVertex::CopyFrom(
  const ON_SubDVertex* src,
  bool bCopyEdgeArray,
  bool bCopyFaceArray,
  bool bCopyLimitPointList,
  bool bCopySymmetrySetNext
  )
{
  if (nullptr == src)
    src = &ON_SubDVertex::Empty;

  ClearSavedSubdivisionPoints();
  CopyBaseFrom(src, bCopySymmetrySetNext);

  m_vertex_tag = src->m_vertex_tag;

  m_P[0] = src->m_P[0];
  m_P[1] = src->m_P[1];
  m_P[2] = src->m_P[2];

  if (bCopyLimitPointList)
  {
    if ( src->SurfacePointIsSet() )
    {
      for (const ON_SubDSectorSurfacePoint* p = &src->m_limit_point; nullptr != p; p = p->m_next_sector_limit_point)
      {
        ON_SubDSectorSurfacePoint limit_point = *p;
        limit_point.m_next_sector_limit_point = (ON_SubDSectorSurfacePoint*)1; // disable checks
        SetSavedSurfacePoint( true, limit_point);
      }
    }
  }

  if (bCopyEdgeArray)
  {
    if (src->m_edge_count > 0 && nullptr != src->m_edges && nullptr != m_edges && src->m_edge_count <= m_edge_capacity)
    {
      m_edge_count = src->m_edge_count;
      const unsigned int edge_count = src->m_edge_count;
      for (unsigned int vei = 0; vei < edge_count; vei++)
        m_edges[vei] = src->m_edges[vei];
    }
    else
      m_edge_count = 0;
  }

  if (bCopyFaceArray)
  {
    if (src->m_face_count > 0 && nullptr != src->m_faces && nullptr != m_faces && src->m_face_count <= m_face_capacity)
    {
      m_face_count = src->m_face_count;
      const unsigned int face_count = src->m_face_count;
      for (unsigned int vfi = 0; vfi < face_count; vfi++)
        m_faces[vfi] = src->m_faces[vfi];
    }
    else
      m_face_count = 0;
  }
}


static bool ON_SubDVertex_GetSubdivisionPointError(
  const class ON_SubDVertex* vertex,
  double vertex_point[3],
  const double* vertexP,
  bool bDamagedState
  )
{
  if (nullptr == vertex || nullptr == vertex_point)
    return false; // caller passed a null pointer - vertex is not necessarily damaged

  ON_SubDIncrementErrorCount();
  vertex->m_status.SetDamagedState(bDamagedState);

  vertex->ClearSavedSubdivisionPoints();

  if (nullptr != vertexP)
  {
    vertex_point[0] = vertexP[0];
    vertex_point[1] = vertexP[1];
    vertex_point[2] = vertexP[2];
  }

  return true;
}

bool ON_SubDVertex::Internal_GetGeneralQuadSubdivisionPoint(
  const class ON_SubDVertex* vertex,
  double vertex_point[3]
)
{
  if (nullptr == vertex_point)
  {
    ON_SUBD_ERROR("input vertex_point is nullptr.");
    return false;
  }

  vertex_point[0] = ON_DBL_QNAN;
  vertex_point[1] = ON_DBL_QNAN;
  vertex_point[2] = ON_DBL_QNAN;

  if (nullptr == vertex)
  {
    ON_SUBD_ERROR("input vertex is nullptr.");
    return false;
  }

  const unsigned int n = vertex->m_face_count;
  if (nullptr == vertex->m_faces
    || nullptr == vertex->m_edges
    || vertex->m_face_count != vertex->m_edge_count
    || n < ON_SubDSectorType::MinimumSectorFaceCount(ON_SubDVertexTag::Smooth)
    )
  {
    ON_SUBD_ERROR("input vertex is not valid.");
    return false;
  }

  const double* vertexP = vertex->m_P;

  ON_3dPoint sharp_subdivision_point;
  const double vertex_sharpness = vertex->GetSharpSubdivisionPoint(sharp_subdivision_point);
  if (vertex_sharpness >= 1.0)
  {
    vertex_point[0] = sharp_subdivision_point.x;
    vertex_point[1] = sharp_subdivision_point.y;
    vertex_point[2] = sharp_subdivision_point.z;
    return true;
  }

  // It is critical to use the centroids of the neighboring faces
  // in this step because the number of edges in each face's
  // boundary may not be constant.
  double facePsum[3] = {};
  const ON_SubDFace*const* vertex_faces = vertex->m_faces;
  for (unsigned int i = 0; i < n; i++)
  {
    const ON_SubDFace* face = vertex_faces[i];
    if (nullptr != face)
    {
      double faceC[3];
      if (face->GetSubdivisionPoint( faceC))
      {
        facePsum[0] += faceC[0];
        facePsum[1] += faceC[1];
        facePsum[2] += faceC[2];
        continue;
      }
    }
    // treat missing or damaged face as infinitesimally small
    facePsum[0] += vertexP[0];
    facePsum[1] += vertexP[1];
    facePsum[2] += vertexP[2];
  }

  double edgePsum[3] = {};
  class ON_SubDEdgePtr* edges = vertex->m_edges;
  for (unsigned int i = 0; i < n; i++)
  {
    const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(edges[i].m_ptr);
    if (nullptr != edge)
    {
      const ON_SubDVertex* edge_vertex = edge->OtherEndVertex(vertex);
      if (nullptr != edge_vertex)
      {
        const double* edgeP = edge_vertex->m_P;
        edgePsum[0] += edgeP[0];
        edgePsum[1] += edgeP[1];
        edgePsum[2] += edgeP[2];
        continue;
      }
    }
    // treat missing or damaged edge as infinitesimally small
    edgePsum[0] += vertexP[0];
    edgePsum[1] += vertexP[1];
    edgePsum[2] += vertexP[2];
  }

  const double v_weight = 1.0 - 2.0 / ((double)n);
  const double ef_weight = 1.0 / ((double)(n*n));
  vertex_point[0] = v_weight*vertexP[0] + ef_weight*(edgePsum[0] + facePsum[0]);
  vertex_point[1] = v_weight*vertexP[1] + ef_weight*(edgePsum[1] + facePsum[1]);
  vertex_point[2] = v_weight*vertexP[2] + ef_weight*(edgePsum[2] + facePsum[2]);

  if (vertex_sharpness > 0.0)
  {
    // 0 < vertex_sharpness < 1
    const double a = 1.0 - vertex_sharpness;
    vertex_point[0] = a * vertex_point[0] + vertex_sharpness * sharp_subdivision_point.x;
    vertex_point[1] = a * vertex_point[1] + vertex_sharpness * sharp_subdivision_point.y;
    vertex_point[2] = a * vertex_point[2] + vertex_sharpness * sharp_subdivision_point.z;
    return true;
  }

  return true;
}

bool ON_SubDVertex::Internal_GetCatmullClarkSubdivisionPoint(
  const class ON_SubDVertex* vertex,
  double vertex_point[3]
  )
{
  // This function is used to convert an arbitrary control polygon into the
  // "level 1" quad subD.  It cannot use the faster sub-D formulas because
  // a face can have an arbitrary number of edges.
  if (nullptr == vertex || nullptr == vertex_point)
    return ON_SubDVertex_GetSubdivisionPointError(vertex,vertex_point,nullptr,false);

  const double* vertexP = vertex->m_P;

  const unsigned int n = (nullptr != vertex->m_edges ? vertex->m_edge_count : 0);
  if (ON_SubDVertexTag::Smooth == vertex->m_vertex_tag || ON_SubDVertexTag::Dart == vertex->m_vertex_tag)
  {
    const unsigned int minimum_n = ON_SubDSectorType::MinimumSectorEdgeCount(vertex->m_vertex_tag);
    if (n < minimum_n || n != vertex->m_face_count || nullptr == vertex->m_faces)
      return ON_SubDVertex_GetSubdivisionPointError(vertex, vertex_point, vertexP, true);

    double facePsum[3] = {};
    const ON_SubDFace*const* vertex_faces = vertex->m_faces;

    const ON_SubDFace* face = vertex_faces[0];
    if (nullptr == face)
      return ON_SubDVertex_GetSubdivisionPointError(vertex, vertex_point, vertexP, true);

    ////// for debugging code below, uncomment this line
    ////// and look for differences in results.
    ////return GetGeneralQuadSubdivisionPoint(vertex, vertex_point);

    const unsigned int k = (nullptr == face) ? 0U : face->m_edge_count;
    if (4 == k)
    {
      // possibly (probably?) every face is a quad
      double sum[3];
      for (unsigned int i = 0; i < n; i++)
      {
        const ON_SubDFace* vface = vertex_faces[i];
        const unsigned int face_n = ON_SubDVertex::Internal_GetFacePointSum(vface, vertex, sum);
        if (4 != face_n)
        {
          // The first face is a quadrangle and this face is not a quadrangle.
          //
          // It is critical to use the centroids of the neighboring faces
          // for this vertex subdivision point because the number of edges
          // in each face's boundary is not constant.
          return ON_SubDVertex::Internal_GetGeneralQuadSubdivisionPoint(vertex, vertex_point);
        }
        facePsum[0] += sum[0];
        facePsum[1] += sum[1];
        facePsum[2] += sum[2];
      }
    }
    else if (3 == k)
    {
      // possibly (probably?) every face is a triangle
      for (unsigned int i = 0; i < n; i++)
      {
        const ON_SubDFace* vface = vertex_faces[i];
        if (k != ((nullptr == vface) ? 0U : vface->m_edge_count))
        {
          // The first face is a triangle and this face is not a triangle.
          //
          // It is critical to use the centroids of the neighboring faces
          // for this vertex subdivision point because the number of edges
          // in each face's boundary is not constant.
          return ON_SubDVertex::Internal_GetGeneralQuadSubdivisionPoint(vertex, vertex_point);
        }
      }
    }
    else
    {
      // The first face has 5 or more edges.  
      // It is likely this is the initial subdivision being applied
      // to the level zero SubD control polygon.
      //
      // It may be critical to use the centroids of the neighboring faces
      // for this vertex subdivision point because the number of edges
      // in each face's boundary may not constant.  In any case, this
      // situation is not common and typically happens only on the
      // first subdivision step.
      return ON_SubDVertex::Internal_GetGeneralQuadSubdivisionPoint(vertex, vertex_point);
    }

    ON_3dPoint sharp_subdivision_point = ON_3dPoint::NanPoint;
    const double vertex_sharpness = vertex->GetSharpSubdivisionPoint(sharp_subdivision_point);
    if (vertex_sharpness >= 1.0)
    {
      // use corner subdivision point
      vertex_point[0] = sharp_subdivision_point.x;
      vertex_point[1] = sharp_subdivision_point.y;
      vertex_point[2] = sharp_subdivision_point.z;
      return true;
    }

    double edgePsum[3] = {};
    class ON_SubDEdgePtr* edges = vertex->m_edges;
    for (unsigned int i = 0; i < n; i++)
    {
      const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(edges[i].m_ptr);
      if (nullptr != edge)
      {
        const ON_SubDVertex* edge_vertex = edge->OtherEndVertex(vertex);
        if (nullptr != edge_vertex)
        {
          const double* edgeP = edge_vertex->m_P;
          edgePsum[0] += edgeP[0];
          edgePsum[1] += edgeP[1];
          edgePsum[2] += edgeP[2];
          continue;
        }
      }
      // treat missing or damaged edge as infinitesimally small
      edgePsum[0] += vertexP[0];
      edgePsum[1] += vertexP[1];
      edgePsum[2] += vertexP[2];
    }

    if (4 == k)
    {
      // all faces were quads
      const double v_weight = 1.0 - 1.75 / ((double)n);
      const double e_weight = 1.5 / ((double)(n*n));
      const double f_weight = 0.25 / ((double)(n*n));
      vertex_point[0] = v_weight*vertexP[0] + e_weight*edgePsum[0] + f_weight*facePsum[0];
      vertex_point[1] = v_weight*vertexP[1] + e_weight*edgePsum[1] + f_weight*facePsum[1];
      vertex_point[2] = v_weight*vertexP[2] + e_weight*edgePsum[2] + f_weight*facePsum[2];
    }
    else
    {
      // all faces were triangles
      const double v_weight = 1.0 - 5.0 / ((double)(3 * n));
      const double e_weight = 5.0 / ((double)(3*n*n));
      vertex_point[0] = v_weight*vertexP[0] + e_weight*edgePsum[0];
      vertex_point[1] = v_weight*vertexP[1] + e_weight*edgePsum[1];
      vertex_point[2] = v_weight*vertexP[2] + e_weight*edgePsum[2];
    }

    if (vertex_sharpness > 0.0)
    {
      // 0 < vertex_sharpness < 1
      const double a = 1.0 - vertex_sharpness;
      vertex_point[0] = a * vertex_point[0] + vertex_sharpness * sharp_subdivision_point.x;
      vertex_point[1] = a * vertex_point[1] + vertex_sharpness * sharp_subdivision_point.y;
      vertex_point[2] = a * vertex_point[2] + vertex_sharpness * sharp_subdivision_point.z;
      return true;
    }

    return true;
  }

  // vertex->m_vertex_tag is damaged
  return ON_SubDVertex_GetSubdivisionPointError(vertex, vertex_point, vertexP, true);
}


const ON_3dPoint ON_SubDVertex::SubdivisionPoint() const
{
  ON_3dPoint S;
  return (GetSubdivisionPoint(&S.x) && S.IsValid()) ? S : ON_3dPoint::NanPoint;
}

const ON_3dPoint ON_SubDVertex::CreaseVertexSubdivisionPoint(
  const ON_3dPoint& P, 
  double vertex_sharpness, 
  const ON_3dPoint& A1, 
  const ON_3dPoint& A2
)
{
  if (vertex_sharpness >= 1.0 && vertex_sharpness <= ON_SubDEdgeSharpness::MaximumValue)
    return P;

  const ON_3dPoint C(
    0.75 * P.x + 0.125 * (A1.x + A2.x),
    0.75 * P.y + 0.125 * (A1.y + A2.y),
    0.75 * P.z + 0.125 * (A1.z + A2.z)
  );

  if (vertex_sharpness > 0.0 && vertex_sharpness < 1.0)
  {
    // Apply sharp bias to C
    const double c = 1.0 - vertex_sharpness;
    return ON_3dPoint(
      c * C.x + vertex_sharpness * P.x,
      c * C.y + vertex_sharpness * P.y,
      c * C.z + vertex_sharpness * P.z
    );
  }

  return C;
}

const ON_SubDVertexSharpnessCalculator ON_SubDVertexSharpnessCalculator::Unset = ON_SubDVertexSharpnessCalculator();

void ON_SubDVertexSharpnessCalculator::Internal_SetVertex(
  ON_SubDVertexTag vertex_tag, 
  ON_3dPoint vertex_control_net_point, 
  double maximum_sharpness_at_interior_crease_vertex
)
{
  if (ON_SubDVertexTag::Unset != vertex_tag)
  {
    m_vertex_tag = vertex_tag;
    m_edge_count = 0;
    m_crease_edge_count = 0;
    m_sharp_edge_count = 0;
    m_vertex_control_net_point = vertex_control_net_point;
    if (ON_SubDVertexTag::Crease == vertex_tag
      && maximum_sharpness_at_interior_crease_vertex > 0.0
      && maximum_sharpness_at_interior_crease_vertex <= ON_SubDEdgeSharpness::MaximumValue)
      m_u1.m_max_edge_sharpness_at_vertex = maximum_sharpness_at_interior_crease_vertex;
    else
      m_u1.m_max_edge_sharpness_at_vertex = 0.0;
    m_status = ON_SubDVertexSharpnessCalculator::Status::VertexSet;
  }
}

void ON_SubDVertexSharpnessCalculator::Internal_SetVertex(
  const ON_SubDVertex* vertex
)
{
  if (nullptr != vertex)
  {
    Internal_SetVertex(
      vertex->m_vertex_tag,
      vertex->ControlNetPoint(),
      (ON_SubDVertexTag::Crease == this->m_vertex_tag && vertex->m_face_count > 0 && vertex->m_face_count + 1 == this->m_edge_count)
      ? vertex->Internal_InteriorCreaseVertexSharpnessForExperts()
      : 0.0
    );
    if (ON_SubDVertexSharpnessCalculator::Status::VertexSet == this->m_status && nullptr != vertex->m_edges)
    {
      ON_SubDEdgePtr eptr;
      const ON_SubDVertex* other_vertex;
      unsigned other_vertex_vi;
      const unsigned short edge_count = vertex->m_edge_count;
      for (unsigned short ei = 0; ei < edge_count; ++ei)
      {
        eptr = vertex->m_edges[ei];
        if (vertex == eptr.RelativeVertex(0))
          other_vertex_vi = 1;
        else if (vertex == eptr.RelativeVertex(1))
          other_vertex_vi = 0;
        else
          continue;
        other_vertex = eptr.RelativeVertex(other_vertex_vi);
        if (nullptr == other_vertex || vertex == other_vertex)
          continue;
        AddEdgeSharpnessAndControlNetPoint(eptr.RelativeSharpness(true).EndSharpness(other_vertex_vi), other_vertex->ControlNetPoint());
      }
      Internal_SetVertexSharpnessAndSharpPoint();
    }
  }
}

ON_SubDVertexSharpnessCalculator::ON_SubDVertexSharpnessCalculator(const ON_SubDVertex* vertex)
{
  Internal_SetVertex(vertex);
}

ON_SubDVertexSharpnessCalculator::ON_SubDVertexSharpnessCalculator(ON_SubDVertexTag vertex_tag, ON_3dPoint vertex_control_net_point, double maximum_sharpness_at_interior_crease_vertex)
{
  Internal_SetVertex(
    vertex_tag,
    vertex_control_net_point,
    ON_SubDVertexTag::Crease == vertex_tag
    ? maximum_sharpness_at_interior_crease_vertex
    : 0.0
  );
}

bool ON_SubDVertexSharpnessCalculator::SetVertex(const ON_SubDVertex* vertex)
{
  *this = ON_SubDVertexSharpnessCalculator::Unset;
  Internal_SetVertex(vertex);
  return (this->m_status == ON_SubDVertexSharpnessCalculator::Status::SharpnessSet);
}

bool ON_SubDVertexSharpnessCalculator::SetVertex(ON_SubDVertexTag vertex_tag, ON_3dPoint vertex_control_net_point, double maximum_sharpness_at_interior_crease_vertex)
{
  *this = ON_SubDVertexSharpnessCalculator::Unset;
  Internal_SetVertex(vertex_tag, vertex_control_net_point, maximum_sharpness_at_interior_crease_vertex);
  return (this->m_status == ON_SubDVertexSharpnessCalculator::Status::VertexSet);
}

bool ON_SubDVertexSharpnessCalculator::AddEdgeSharpnessAndControlNetPoint(double sharpness_at_vertex, ON_3dPoint other_end_control_net_point)
{
  if (ON_SubDVertexSharpnessCalculator::Status::VertexSet != this->m_status)
    return false;

  ++m_edge_count;
  if (sharpness_at_vertex > 0.0 && ON_SubDEdgeSharpness::IsValidValue(sharpness_at_vertex, true))
  {
    const unsigned i = this->m_crease_edge_count + this->m_sharp_edge_count;
    if (i < 2)
      this->m_other_end_control_net_points[i] = other_end_control_net_point;
    if (ON_SubDEdgeSharpness::CreaseValue == sharpness_at_vertex)
      ++m_crease_edge_count;
    else
    {
      ++m_sharp_edge_count;
      if (sharpness_at_vertex > this->m_u1.m_max_edge_sharpness_at_vertex)
        this->m_u1.m_max_edge_sharpness_at_vertex = sharpness_at_vertex;
    }
  }
  return true;
}

bool ON_SubDVertexSharpnessCalculator::AddCreaseEdgeControlNetPoint(ON_3dPoint other_end_control_net_point)
{
  return AddEdgeSharpnessAndControlNetPoint(ON_SubDEdgeSharpness::CreaseValue, other_end_control_net_point);
}

bool ON_SubDVertexSharpnessCalculator::VertexIsSet() const
{
  return (ON_SubDVertexSharpnessCalculator::Status::Unset != this->m_status);
}

ON_SubDVertexTag ON_SubDVertexSharpnessCalculator::VertexTag() const
{
  return this->VertexIsSet() ? this->m_vertex_tag : ON_SubDVertexTag::Unset;
}

const ON_3dPoint ON_SubDVertexSharpnessCalculator::VertexControlNetPoint() const
{
  return this->VertexIsSet() ? this->m_vertex_control_net_point : ON_3dPoint::NanPoint;
}

unsigned ON_SubDVertexSharpnessCalculator::EdgeCount() const
{
  return this->m_edge_count;
}

unsigned ON_SubDVertexSharpnessCalculator::SharpEdgeCount() const
{
  return this->m_sharp_edge_count;
}

unsigned ON_SubDVertexSharpnessCalculator::CreaseEdgeCount() const
{
  return this->m_crease_edge_count;
}


bool ON_SubDVertexSharpnessCalculator::IsSharpVertex() const
{
  return this->VertexSharpness() > 0.0;
}

bool ON_SubDVertexSharpnessCalculator::Internal_SetVertexSharpnessAndSharpPoint() const
{
  if (ON_SubDVertexSharpnessCalculator::Status::VertexSet == this->m_status && this->m_edge_count > 0)
  {
    this->m_status = ON_SubDVertexSharpnessCalculator::Status::Unset;

    const double vertex_sharpness = ON_SubDEdgeSharpness::VertexSharpness(
      this->m_vertex_tag,
      (ON_SubDVertexTag::Crease == this->m_vertex_tag ? this->m_u1.m_max_edge_sharpness_at_vertex : 0.0),
      this->m_sharp_edge_count,
      this->m_u1.m_max_edge_sharpness_at_vertex
    );

    ON_3dPoint R = ON_3dPoint::Origin; // origin rather than nan so 0.0 * VertexSharpPoint() is not a nan point
    if (vertex_sharpness > 0.0)
    {
      if (ON_SubDVertexTag::Crease == m_vertex_tag)
        R = this->m_vertex_control_net_point;
      else if (ON_SubDVertexTag::Smooth == m_vertex_tag || ON_SubDVertexTag::Dart == m_vertex_tag)
      {
        const unsigned short sharp_and_crease_edge_count = this->m_sharp_edge_count + this->m_crease_edge_count;
        if (sharp_and_crease_edge_count > 2)
          R = this->m_vertex_control_net_point;
        else if (2 == sharp_and_crease_edge_count)
          R = ON_SubDVertex::CreaseVertexSubdivisionPoint(this->m_vertex_control_net_point, 0.0, this->m_other_end_control_net_points[0], this->m_other_end_control_net_points[1]);
      }
    }

    this->m_u1.m_vertex_sharpness = vertex_sharpness;
    this->m_other_end_control_net_points[0] = R;
    this->m_other_end_control_net_points[1] = ON_3dPoint::NanPoint;

    this->m_status = ON_SubDVertexSharpnessCalculator::Status::SharpnessSet;
  }
  else
    this->m_status = ON_SubDVertexSharpnessCalculator::Status::Unset;

  return (ON_SubDVertexSharpnessCalculator::Status::SharpnessSet == this->m_status) ? this->m_u1.m_vertex_sharpness : 0.0;
}

double ON_SubDVertexSharpnessCalculator::VertexSharpness() const
{
  if (ON_SubDVertexSharpnessCalculator::Status::VertexSet == this->m_status && this->m_edge_count > 0)
    Internal_SetVertexSharpnessAndSharpPoint();
  return (ON_SubDVertexSharpnessCalculator::Status::SharpnessSet == this->m_status) ? this->m_u1.m_vertex_sharpness : 0.0;
}

const ON_3dPoint ON_SubDVertexSharpnessCalculator::VertexSharpPoint() const
{
  if (this->IsSharpVertex())
    return this->m_other_end_control_net_points[0];

  // Return origin rather than nan so that 0.0*this->VertexSharpPoint() will not be a nan point.
  return ON_3dPoint::Origin;
}



bool ON_SubDVertex::GetSubdivisionPoint(
  double subdivision_point[3]
) const
{
  if (nullptr == subdivision_point)
    return ON_SubDVertex_GetSubdivisionPointError(this, subdivision_point, nullptr, false);

  if (GetSavedSubdivisionPoint(subdivision_point))
    return true;

  if (EvaluateCatmullClarkSubdivisionPoint(subdivision_point))
  {
    SetSavedSubdivisionPoint(subdivision_point);
    return true;
  }

  return false;
}

bool ON_SubDVertex::EvaluateCatmullClarkSubdivisionPoint(
  double subdivision_point[3]) const
{
  // This function is used to convert an arbitrary control polygon into the
  // "level 1" subD.  It cannot use the faster sub-D formulas because
  // a face can have an arbitrary number of edges.
  if (nullptr == subdivision_point )
    return ON_SubDVertex_GetSubdivisionPointError(this, subdivision_point, nullptr, false);

  const double* vertexP = m_P;

  const unsigned int n = (nullptr != m_edges ? m_edge_count : 0);
  if (n < 2)
    return ON_SubDVertex_GetSubdivisionPointError(this, subdivision_point, vertexP, true);

  if (ON_SubDVertexTag::Smooth == m_vertex_tag || ON_SubDVertexTag::Dart == m_vertex_tag)
  {
    return ON_SubDVertex::Internal_GetCatmullClarkSubdivisionPoint(this, subdivision_point);
  }

  if (ON_SubDVertexTag::Crease == m_vertex_tag)
  {
    class ON_SubDEdgePtr* edges = m_edges;
    const ON_SubDVertex* edge0_vertex = nullptr;
    const ON_SubDVertex* edge1_vertex = nullptr;
    bool bSharpEdges = false;

    for (unsigned int i = 0; i < n; i++)
    {
      const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(edges[i].m_ptr);
      if (nullptr == edge)
      {
        ON_SubDVertex_GetSubdivisionPointError(this, subdivision_point, vertexP, true);
        continue;
      }

      if (ON_SubDEdgeTag::Crease != edge->m_edge_tag)
      {
        if (false == bSharpEdges)
          bSharpEdges = edge->IsSharp();
        continue;
      }

      const ON_SubDVertex* edge_vertex = edge->OtherEndVertex(this);

      if (nullptr == edge_vertex)
      {
        ON_SubDVertex_GetSubdivisionPointError(this, subdivision_point, vertexP, true);
        continue;
      }

      if (nullptr == edge0_vertex)
      {
        edge0_vertex = edge_vertex;
        continue;
      }

      if (edge0_vertex == edge_vertex)
      {
        ON_SubDVertex_GetSubdivisionPointError(this, subdivision_point, vertexP, true);
        continue;
      }

      if (nullptr == edge1_vertex)
      {
        edge1_vertex = edge_vertex;
        continue;
      }

      if (edge1_vertex == edge_vertex)
      {
        ON_SubDVertex_GetSubdivisionPointError(this, subdivision_point, vertexP, true);
        continue;
      }

      // 3 or more creased edges attached to this crease vertex.
      ON_SubDVertex_GetSubdivisionPointError(this, subdivision_point, vertexP, true);
      subdivision_point[0] = vertexP[0];
      subdivision_point[1] = vertexP[1];
      subdivision_point[2] = vertexP[2];
      return true;
    }

    if (nullptr != edge0_vertex && nullptr != edge1_vertex)
    {
      // We found the two crease edges that share this crease vertex.
      ON_3dPoint sharp_subdivision_point = ON_3dPoint::NanPoint;
      const double vertex_sharpness 
        = (bSharpEdges || this->Internal_InteriorCreaseVertexSharpnessForExperts() > 0.0)
        ? this->GetSharpSubdivisionPoint(sharp_subdivision_point)
        : 0.0;
      if (vertex_sharpness >= 1.0)
      {
        // 2 creases and a sharp edge with sharpness >= 1
        // This modification is not part of the DKT1998 Pixar algorithm.
        // It is required to get sharp edges to evenly end at
        // ordinary boundaries. It does break crease edge evaluation relying
        // only on boundary settings, but at this time (Dale Lear Nov 2022),
        // I'm guessing it is the best option out of 2 nonideal choices.
        subdivision_point[0] = sharp_subdivision_point.x;
        subdivision_point[1] = sharp_subdivision_point.y;
        subdivision_point[2] = sharp_subdivision_point.z;
        return true;
      }

      // (The parenthesis around the edgeP sum is to insure this result 
      // is independent of the order of the edges.)
      vertexP = m_P;

      const double* edgeP[2] = { edge0_vertex->m_P, edge1_vertex->m_P };
      subdivision_point[0] = (vertexP[0] * 6.0 + (edgeP[0][0] + edgeP[1][0])) * 0.125;
      subdivision_point[1] = (vertexP[1] * 6.0 + (edgeP[0][1] + edgeP[1][1])) * 0.125;
      subdivision_point[2] = (vertexP[2] * 6.0 + (edgeP[0][2] + edgeP[1][2])) * 0.125;
      if (vertex_sharpness > 0.0)
      {
        // 2 creases and a sharp edge with 0 < sharpness < 1
        // 
        // This modification is not part of the DKT1998 Pixar algorithm.
        // It is required to get sharp edges to evenly end at ordinary boundaries. 
        // It does break crease edge evaluation relying
        // only on boundary settings, but at this time (Dale Lear Nov 2022),
        // I'm guessing it is the best option out of 2 nonideal choices.
        //
        const double a = 1.0 - vertex_sharpness;
        subdivision_point[0] = a * subdivision_point[0] + vertex_sharpness * sharp_subdivision_point.x;
        subdivision_point[1] = a * subdivision_point[1] + vertex_sharpness * sharp_subdivision_point.y;
        subdivision_point[2] = a * subdivision_point[2] + vertex_sharpness * sharp_subdivision_point.z;
        return true;
      }
      return true;
    }

    return ON_SubDVertex_GetSubdivisionPointError(this, subdivision_point, vertexP, true);
  }

  if (ON_SubDVertexTag::Corner == m_vertex_tag)
  {
    vertexP = m_P;
    subdivision_point[0] = vertexP[0];
    subdivision_point[1] = vertexP[1];
    subdivision_point[2] = vertexP[2];
    return true;
  }

  // vertex is damaged
  return ON_SubDVertex_GetSubdivisionPointError(this, subdivision_point, vertexP, true);
}

unsigned int ON_SubDVertex::Internal_GetFacePointSum(
  const ON_SubDFace* face,
  const ON_SubDVertex* vertex,
  double* facePsum
  )
{
  const ON_SubDEdge* e;
  ON__UINT_PTR e_ptr, edir;
  const double* faceP;

  if (nullptr == face)
    return 0;

  const unsigned int n = face->m_edge_count;

  facePsum[0] = 0.0;
  facePsum[1] = 0.0;
  facePsum[2] = 0.0;

  if (3 == n)
  {
    return n;
  }

  if (4 == n)
  {
    for (unsigned int i = 0; i < 4; i++)
    {
      e_ptr = face->m_edge4[i].m_ptr;
      e = ON_SUBD_EDGE_POINTER(e_ptr);
      if (nullptr != e && (vertex == e->m_vertex[0] || vertex == e->m_vertex[1]))
      {
        edir = ON_SUBD_EDGE_DIRECTION(e_ptr);
        e_ptr = face->m_edge4[(i + ((vertex == e->m_vertex[edir]) ? 2 : 3)) % 4].m_ptr;
        e = ON_SUBD_EDGE_POINTER(e_ptr);
        edir = ON_SUBD_EDGE_DIRECTION(e_ptr);
        if (nullptr == e || nullptr == e->m_vertex[edir])
          return 0;
        faceP = e->m_vertex[edir]->m_P;
        facePsum[0] = faceP[0];
        facePsum[1] = faceP[1];
        facePsum[2] = faceP[2];
        return n;
      }
    }
    return 0;
  }

  if (n <= 4 || nullptr == face->m_edgex)
    return 0;

  e_ptr = face->m_edgex[n-5].m_ptr;
  e = ON_SUBD_EDGE_POINTER(e_ptr);
  if (nullptr == e)
    return 0;
  edir = ON_SUBD_EDGE_DIRECTION(e_ptr);
  unsigned int skipped_edge_count = (vertex == e->m_vertex[edir]) ? 1 : 0;
  unsigned int facePcount = 0;
  const ON_SubDEdgePtr* edge_ptrs = face->m_edge4;
  for (unsigned int i = skipped_edge_count; i < n; i++)
  {
    if (4 == i)
      edge_ptrs = face->m_edgex - 4;
    e_ptr = edge_ptrs[i].m_ptr;
    e = ON_SUBD_EDGE_POINTER(e_ptr);
    if (nullptr == e)
      return 0;
    edir = ON_SUBD_EDGE_DIRECTION(e_ptr);
    if (vertex == e->m_vertex[0] || vertex == e->m_vertex[1])
    {
      skipped_edge_count++;
      if (skipped_edge_count > 2)
      {
        facePsum[0] = 0.0;
        facePsum[1] = 0.0;
        facePsum[2] = 0.0;
        return 0;
      }
      if (vertex == e->m_vertex[edir])
      {
        i++;
        if (4 == i)
          edge_ptrs = face->m_edgex - 4;
      }
      continue;
    }
    faceP = e->m_vertex[edir]->m_P;
    facePsum[0] += faceP[0];
    facePsum[1] += faceP[1];
    facePsum[2] += faceP[2];
    facePcount++;
  }

  if (n == facePcount + 3)
    return n;

  facePsum[0] = 0.0;
  facePsum[1] = 0.0;
  facePsum[2] = 0.0;
  return 0;
}

bool ON_SubDimple::LocalSubdivide(
  ON_SubDFace const*const* face_list,
  size_t face_list_count
)
{
  if (nullptr == face_list || face_list_count < 1 || m_levels.UnsignedCount() < 1)
    return false;

  unsigned int level0_index = ON_UNSET_UINT_INDEX;
  for (size_t i = 0; i < face_list_count; ++i)
  {
    const ON_SubDFace* f = face_list[i];
    if (nullptr == f || f->m_edge_count < 3 || f->SubdivisionLevel() >= m_levels.UnsignedCount())
      continue;
    level0_index = f->SubdivisionLevel();
    break;
  }
  
  if (level0_index >= m_levels.UnsignedCount() || nullptr == m_levels[level0_index])
    return ON_SUBD_RETURN_ERROR(false);

  ClearHigherSubdivisionLevels(level0_index + 1);
  if (level0_index + 1 != m_levels.UnsignedCount())
    return ON_SUBD_RETURN_ERROR(false);

  m_active_level = m_levels[level0_index];
  if ( nullptr == m_active_level || 0 == m_active_level->m_face_count)
    return ON_SUBD_RETURN_ERROR(false);

  ON_SubDLevel& level0 = *m_levels[level0_index];
  m_active_level = &level0;

  level0.ClearRuntimeMarks(true, true, true);

  unsigned face_count = 0;
  unsigned edge_count = 0;
  unsigned vertex_count = 0;
  ON_3dPoint P;
  for (size_t i = 0; i < face_list_count; ++i)
  {
    const ON_SubDFace* f = face_list[i];
    if (nullptr == f || f->m_edge_count < 3 || level0_index != f->SubdivisionLevel() )
      continue;
    if (f->m_status.RuntimeMark())
      continue;
    f->m_status.SetRuntimeMark();
    if ( false == f->GetSubdivisionPoint(P))
      return ON_SUBD_RETURN_ERROR(false);
    const ON_SubDEdgePtr* eptr = f->m_edge4;
    for (unsigned short fei = 0; fei < f->m_edge_count; ++fei, ++eptr)
    {
      if (4 == fei)
      {
        eptr = f->m_edgex;
        if (nullptr == eptr)
          return ON_SUBD_RETURN_ERROR(false);
      }
      ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
      if (nullptr == e || nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
        return ON_SUBD_RETURN_ERROR(false);
      if (e->m_status.RuntimeMark())
        continue;
      e->UpdateEdgeSectorCoefficientsForExperts(true);
      e->m_status.SetRuntimeMark();
      if (false == e->GetSubdivisionPoint(P))
        return ON_SUBD_RETURN_ERROR(false);
      for (unsigned evi = 0; evi < 2; ++evi)
      {
        if (e->m_vertex[evi]->m_status.RuntimeMark())
          continue;
        e->m_vertex[evi]->m_status.SetRuntimeMark();
        if ( false == e->m_vertex[evi]->GetSubdivisionPoint(P) )
          return ON_SUBD_RETURN_ERROR(false);
        ++vertex_count;
      }
      ++edge_count;
    }
    ++face_count;
  }
  if (face_count < 1 || edge_count < 3 || vertex_count < 3)
    return false;
  if (face_count >= level0.m_face_count)
    return GlobalSubdivide();

  // Get face subdivision points
  ON_SimpleArray<ON_SubDFace*> faces(face_count);
  ON_SimpleArray<ON_3dPoint> face_points(face_count);

  // this subd is being modified.
  ChangeGeometryContentSerialNumber( false);

  for (const ON_SubDFace* f0 = level0.m_face[0]; nullptr != f0; f0 = f0->m_next_face)
  {
    if (false == f0->m_status.RuntimeMark())
      continue;
    faces.Append(const_cast<ON_SubDFace*>(f0));
    P = f0->SubdivisionPoint();
    if ( false == P.IsValid())
      return ON_SUBD_RETURN_ERROR(false);
    face_points.Append(P);
  }
  if (face_count != face_points.UnsignedCount())
    return ON_SUBD_RETURN_ERROR(false);

  // Get edge subdivision points
  ON_SimpleArray<ON_3dPoint> edge_points(edge_count);
  ON_SimpleArray<ON_SubDEdge*> edges(edge_count);
  for (const ON_SubDEdge* e0 = level0.m_edge[0]; nullptr != e0; e0 = e0->m_next_edge)
  {
    if (false == e0->m_status.RuntimeMark())
      continue;
    P = (e0->IsSmooth() && 2 == e0->m_face_count && 2 == e0->MarkedFaceCount()) ? e0->SubdivisionPoint() : e0->ControlNetCenterPoint();
    edge_points.Append(P);
    edges.Append(const_cast<ON_SubDEdge*>(e0));
  }
  if ( edge_count != edge_points.UnsignedCount())
    return ON_SUBD_RETURN_ERROR(false);

  // Set vertex points
  for (const ON_SubDVertex* v0 = level0.m_vertex[0]; nullptr != v0; v0 = v0->m_next_vertex)
  {
    if (false == v0->m_status.RuntimeMark() || v0->m_edge_count < 2 || ((unsigned)v0->m_edge_count) != v0->MarkedEdgeCount())
      continue;
    P = v0->SubdivisionPoint();
    ON_SubDVertex* v = const_cast<ON_SubDVertex*>(v0);
    v->m_P[0] = P.x;
    v->m_P[1] = P.y;
    v->m_P[2] = P.z;
  }

  // split edges
  for (unsigned edex = 0; edex < edge_count; ++edex)
  {
    ON_SubDEdge* e = edges[edex];

    const ON_SubDEdgeSharpness e_sharpness = e->Sharpness(false);

    e->EdgeModifiedNofification();
    const ON_SubDEdge* new_edge = SplitEdge(e, edge_points[edex]);
    if (nullptr == new_edge)
      return ON_SUBD_RETURN_ERROR(false);
    new_edge->m_status.ClearRuntimeMark();
    e->m_status.SetRuntimeMark();

    // LOCAL subdivide is more of an add control points to an existing level
    // as opposed to a global subdivision level operation. It will be common
    // for the input to include some but not all sharp edges.
    // Dale Lear's best guess on Nov 9, 2022 is that
    // reusing the original sharpness is the best way to maximize overall
    // user happiness. This makes some sense because the level of the edges
    // is not changing in a LOCAL subdivide. 
    // It is a near certainty that some users will not like this in some cases. 
    const_cast<ON_SubDEdge*>(e)->SetSharpnessForExperts(ON_SubDEdgeSharpness::FromInterval(e_sharpness[0], e_sharpness.Average()));
    const_cast<ON_SubDEdge*>(new_edge)->SetSharpnessForExperts(ON_SubDEdgeSharpness::FromInterval(e_sharpness.Average(), e_sharpness[1]));
  }

  ON_SimpleArray<ON_SubDEdgePtr> fbdry(32);
  ON_SimpleArray<ON_SubDEdge*> radial_edges(32);
  for (unsigned fdex = 0; fdex < face_count; ++fdex)
  {
    ON_SubDFace* f = faces[fdex];
    f->FaceModifiedNofification();
    P = face_points[fdex];
    fbdry.SetCount(0);
    const unsigned e_count = f->GetEdgeArray(fbdry);
    if (e_count < 6 || 0 != e_count %2)
      return ON_SUBD_RETURN_ERROR(false);

    // Get edges[] with edge[0] = marked edges.
    const ON_SubDEdgePtr* eptrs = fbdry.Array();
    if (nullptr != eptrs[0].RelativeVertex(0) && false == eptrs[0].RelativeVertex(0)->Mark() )
    {
      fbdry.Append(eptrs[0]);
      eptrs = fbdry.Array() + 1;
    }

    // save face status and candidate_face
    unsigned int candidate_face_id = f->m_id;
    const ON_ComponentStatus fstatus = f->m_status;

    for (unsigned fei = 0; fei < e_count; ++fei)
    {
      ON_SubDEdge* e = eptrs[fei].Edge();
      if ( nullptr == e)
        return ON_SUBD_RETURN_ERROR(false);
      const ON_SubDVertex* ev[2] = { eptrs[fei].RelativeVertex(0), eptrs[fei].RelativeVertex(1) };
      if ( nullptr == ev[0] || nullptr == ev[1] || ev[0] == ev[1])
        return ON_SUBD_RETURN_ERROR(false);
      if (0 == fei % 2)
      {
        if (false == ev[0]->Mark())
          return ON_SUBD_RETURN_ERROR(false);
        if (ev[1]->Mark())
          return ON_SUBD_RETURN_ERROR(false);
      }
      else
      {
        if (ev[0]->Mark())
          return ON_SUBD_RETURN_ERROR(false);
        if (false == ev[1]->Mark())
          return ON_SUBD_RETURN_ERROR(false);
      }
    }

    // remove face that will be subdivided;
    for (unsigned short fei = 0; fei < f->m_edge_count; ++fei)
    {
      eptrs[fei].Edge()->RemoveFaceFromArray(f);
      const_cast<ON_SubDVertex*>(eptrs[fei].RelativeVertex(0))->RemoveFaceFromArray(f);
    }
    ReturnFace(f);
    
    ON_SubDVertex* center = AllocateVertex(ON_SubDVertexTag::Smooth, level0_index, &P.x);
    AddVertexToLevel(center);

    radial_edges.SetCount(0);
    radial_edges.Reserve(e_count /2);
    for (unsigned fei = 0; fei < e_count; fei += 2)
    {
      ON_SubDEdge* r = AddEdge(ON_SubDEdgeTag::Smooth, center, ON_SubDSectorType::UnsetSectorCoefficient, const_cast<ON_SubDVertex*>(eptrs[fei].RelativeVertex(1)), ON_SubDSectorType::UnsetSectorCoefficient);
      radial_edges.Append(r);
    }

    ON_SubDEdge* r[2] = { nullptr,radial_edges[e_count / 2 - 1] };
    for (unsigned fei = 0; fei < e_count; fei += 2)
    {
      r[0] = r[1];
      r[1] = radial_edges[fei / 2];
      const ON_SubDEdgePtr qbdry[4] = {
        ON_SubDEdgePtr::Create(r[0],0),
        eptrs[(fei + e_count - 1) % e_count],
        eptrs[fei],
        ON_SubDEdgePtr::Create(r[1],1) 
      };
      ON_SubDFace* q = AddFace(candidate_face_id, 4, qbdry);
      candidate_face_id = 0;
      q->m_status = fstatus;
    }

  }

  level0.ClearRuntimeMarks(true, true, false);
  level0.ClearBoundingBox();
  level0.ClearEvaluationCache();
  level0.ClearEdgeFlags();

  if (nullptr != m_active_level)
    m_active_level->UpdateAllTagsAndSectorCoefficients(true);
  
  return true; 
}

const ON_UUID ON_SubD::FacePackingId() const
{
  const ON_SubDimple* dimple = this->SubDimple();
  return (nullptr != dimple) ? dimple->FacePackingId() : ON_nil_uuid;
}

const ON_UUID ON_SubDimple::FacePackingId() const
{
  return m_face_packing_id;
}

const ON_SubDHash ON_SubD::FacePackingTopologyHash() const
{
  const ON_SubDimple* dimple = this->SubDimple();
  return (nullptr != dimple) ? dimple->FacePackingTopologyHash() : ON_SubDHash::Empty;
}

const ON_SubDHash ON_SubDimple::FacePackingTopologyHash() const
{
  return m_face_packing_topology_hash;
}

unsigned int ON_SubDimple::GlobalSubdivide()
{
  if (m_levels.UnsignedCount() <= 0)
    return ON_SUBD_RETURN_ERROR(0U);
  const unsigned int level0_index = m_levels.UnsignedCount()-1;

  if ( nullptr == m_levels[level0_index])
    return ON_SUBD_RETURN_ERROR(0U);

  ON_SubDLevel& level0 = *m_levels[level0_index];
  if (level0.IsEmpty())
    return ON_SUBD_RETURN_ERROR(0U);
  if ( level0.m_edge_count <= 0U )
    return ON_SUBD_RETURN_ERROR(0U);

  level0.UpdateEdgeSectorCoefficients(true);

  const unsigned int level1_index = level0_index+1;
  
  ON_SubDLevel* level1 = SubDLevel(level1_index,true);
  if ( nullptr == level1 )
    return ON_SUBD_RETURN_ERROR(0);

  double P[3];
  ON_SubDVertex* v;

  // If the object is currently symmetric, a global subdivision will not break symmetry
  const bool bChangePreservesSymmetry = true;
  this->ChangeGeometryContentSerialNumber(bChangePreservesSymmetry);

  // Add face points
  bool bSubdividePackRect = ON_nil_uuid != this->FacePackingId();
  unsigned next_pack_id = 0U;
  for (const ON_SubDFace* f0 = level0.m_face[0]; nullptr != f0; f0 = f0->m_next_face)
  {
    if (bSubdividePackRect && f0->PackRectIsSet())
    {
      if (f0->PackId() > next_pack_id)
        next_pack_id = f0->PackId();
    }
    if (false == f0->GetSubdivisionPoint(P))
      continue;
    if (nullptr == f0->m_subd_point1)
    {
      const_cast<ON_SubDFace*>(f0)->m_subd_point1 = v = AllocateVertex(ON_SubDVertexTag::Smooth, level1_index, P);
      AddVertexToLevel(v);
    }
    else
    {
      v = const_cast<ON_SubDVertex*>(f0->m_subd_point1);
      v->m_P[0] = P[0];
      v->m_P[1] = P[1];
      v->m_P[2] = P[2];
    }
  }

  if (next_pack_id > 0)
  {
    // next_pack_id MUST be strictly greater than any pack rect id in use.
    ++next_pack_id;
  }
  else
  {
    // nothing valid to copy
    bSubdividePackRect = false;
  }

  // Add edge points
  for (const ON_SubDEdge* e0 = level0.m_edge[0]; nullptr != e0; e0 = e0->m_next_edge)
  {
    if (false == e0->GetSubdivisionPoint(P))
      continue;
    // (the subdivision point of an edge tagged as ON_SubDEdgeTag::SmoothX is a smooth vertex.)
    const ON_SubDVertexTag vertex_tag
      = ON_SubDEdgeTag::Crease == e0->m_edge_tag
      ? ON_SubDVertexTag::Crease
      : ON_SubDVertexTag::Smooth;
    if (nullptr == e0->m_subd_point1)
    {
      const_cast<ON_SubDEdge*>(e0)->m_subd_point1 = v = AllocateVertex(vertex_tag, level1_index, P );
      AddVertexToLevel(v);
    }
    else
    {
      v = const_cast<ON_SubDVertex*>(e0->m_subd_point1);
      v->m_vertex_tag = vertex_tag;
      v->m_P[0] = P[0];
      v->m_P[1] = P[1];
      v->m_P[2] = P[2];
    }
  }

  // Add vertex points
  for (const ON_SubDVertex* v0 = level0.m_vertex[0]; nullptr != v0; v0 = v0->m_next_vertex)
  {
    if (false == v0->GetSubdivisionPoint(P))
      continue;
    if (nullptr == v0->m_subd_point1)
    {
      const_cast<ON_SubDVertex*>(v0)->m_subd_point1 = v = AllocateVertex(v0->m_vertex_tag, level1_index, P);
      AddVertexToLevel(v);
    }
    else
    {
      v = const_cast<ON_SubDVertex*>(v0->m_subd_point1);
      v->m_vertex_tag = v0->m_vertex_tag;
      v->m_P[0] = P[0];
      v->m_P[1] = P[1];
      v->m_P[2] = P[2];
    }    
  }

  // subdivide edges
  for (const ON_SubDEdge* e0 = level0.m_edge[0]; nullptr != e0; e0 = e0->m_next_edge)
  {
    if (nullptr == e0->m_subd_point1)
      continue;
    ON_SubDVertex* end_vertex[2] = { const_cast<ON_SubDVertex*>(e0->m_vertex[0]->m_subd_point1), const_cast<ON_SubDVertex*>(e0->m_vertex[1]->m_subd_point1) };
    ON_SubDVertex* mid_vertex = const_cast<ON_SubDVertex*>(e0->m_subd_point1);
    double w[2] = { e0->m_sector_coefficient[0], e0->m_sector_coefficient[1] };
    ON_SubDEdgeTag edge_tag = e0->m_edge_tag;
    if (ON_SubDEdgeTag::SmoothX == edge_tag && 2 == e0->m_face_count)
    {
      if ( nullptr != mid_vertex && ON_SubDVertexTag::Smooth == mid_vertex->m_vertex_tag )
        edge_tag = ON_SubDEdgeTag::Smooth;
    }

    class ON_SubDEdge* e10 = AddEdge(edge_tag, end_vertex[0], w[0], mid_vertex, 0.0);
    class ON_SubDEdge* e11 = AddEdge(edge_tag, mid_vertex, 0.0, end_vertex[1], w[1]);
    if ( e0->IsSharp() )
    {
      const ON_SubDEdgeSharpness e0_sharpness = e0->Sharpness(false);
      if (e0_sharpness.IsSharp())
      {
        if (nullptr != e10)
          e10->SetSharpnessForExperts(e0_sharpness.Subdivided(0));
        if (nullptr != e11)
          e11->SetSharpnessForExperts(e0_sharpness.Subdivided(1));
      }
    }
  }

  for (const ON_SubDFace* f0 = level0.m_face[0]; nullptr != f0; f0 = f0->m_next_face)
  {
    Internal_GlobalQuadSubdivideFace(f0, bSubdividePackRect, next_pack_id);
  }

  return level1_index;
}

static bool Internal_SubdivideFacePacking(
  const ON_SubDFace* f0,
  unsigned f0_edge_count,
  unsigned f0_pack_id,
  unsigned& next_pack_id,
  ON_SubDFace** sub_quads
)
{
  // NOTE WELL: 
  // 1) The caller must insure input parameters are valid.
  // 2) A multi-face pack MUST be a set of quads that form a RECTANGULAR topological grid.
  // 3) The primary service provided by picking is insuring packed texture coordinates map 
  // rectangular regions of texture space to the grids of packed quads. This is important
  // for texture painting applications.

  const ON_2dPoint f0_pack_rect_origin = f0->PackRectOrigin();
  if (false == (f0_pack_rect_origin.x >= 0.0 && f0_pack_rect_origin.x < 1.0))
    return false;
  if (false == (f0_pack_rect_origin.y >= 0.0 && f0_pack_rect_origin.y < 1.0))
    return false;

  const ON_2dVector f0_pack_rect_size = f0->PackRectSize();
  if (false == (f0_pack_rect_size.x > 0.0 && f0_pack_rect_origin.x + f0_pack_rect_size.x <= 1.0 + ON_EPSILON))
    return false;
  if (false == (f0_pack_rect_size.y > 0.0 && f0_pack_rect_origin.y + f0_pack_rect_size.y <= 1.0 + ON_EPSILON))
    return false;

  const unsigned f0_packing_rotation_degrees = f0->PackRectRotationDegrees();
  if (f0_edge_count <= 4)
  {
    // NOTE WELL: A multi-face pack MUST be a set of quads that form a rectangular topological grid.
    // 
    // When f0 is a quad, the f0 pack region is subdivided into 4 sub rectangles and
    // those rectangle are assigned the original pack id. This works because neighboring
    // quad faces that belong to the same pack will also be subdivided into 4 quads
    // and the requirement that multi-face pack MUST be a set of quads that form a 
    // rectangular topological grid will be satisfied in the globally subdivided SubD.
    //
    // When f0 is a triangle, f0 necessarily is the on face with its pack id (because it cannot
    // possibly be grouped with other quads - see NOTE WELL above).
    // In addition, for triangular faces, packed textures are assigned to the triangular face
    // in a way that the first two sub quads can become a single two quad pack and can reuse the f0->PackId(). 
    // The third subquad gets a new pack id.

    const ON_2dVector f1_pack_rect_size(0.5 * f0_pack_rect_size.x, 0.5 * f0_pack_rect_size.y);
    unsigned f1_packing_rotation_degrees = (f0_packing_rotation_degrees + 90U) % 360U;
    for (unsigned i = 0; i < f0_edge_count; ++i)
    {
      const unsigned j = (i + 4 - (f0_packing_rotation_degrees / 90)) % 4;
      const ON_2dPoint f1_pack_rect_origin(
        f0_pack_rect_origin.x + ((j >= 1 && j <= 2) ? 0.5 * f0_pack_rect_size.x : 0.0),
        f0_pack_rect_origin.y + ((j >= 2) ? 0.5 * f0_pack_rect_size.y : 0.0)
      );

      // See comment above about pack id assignments
      const unsigned f1_pack_id = (3 == f0_edge_count && 2 == i) ? (next_pack_id++) : f0_pack_id;

      ON_SubDFace* f1 = sub_quads[i];
      f1->SetPackIdForExperts(f1_pack_id);
      f1->SetPackRectForExperts(
        f1_pack_rect_origin,
        f1_pack_rect_size,
        f1_packing_rotation_degrees);
      f1_packing_rotation_degrees = (f1_packing_rotation_degrees + 270U) % 360U;
    }
  }
  else
  {
    // n-gon with n >= 5
    ON_2dVector ngon_sub_pack_rect_size;
    ON_2dVector ngon_sub_pack_rect_delta;
    const ON_2udex ngon_grid_size = ON_SubDFace::GetNgonSubPackRectSizeAndDelta(
      f0_edge_count,
      f0_pack_rect_size,
      ngon_sub_pack_rect_size,
      ngon_sub_pack_rect_delta
    );

    if (ngon_grid_size.i <= 0 || ngon_grid_size.j <= 0 || ngon_grid_size.i * ngon_grid_size.j < f0_edge_count)
      return false;

    //const unsigned horiz_offset_count 
    //  = (0 == (f0_packing_rotation_degrees % 180))
    //  ? ngon_grid_size.i
    //  : ngon_grid_size.j;

    //if (0 != (f0_packing_rotation_degrees % 180))
    //{
    //  // subdivision rects coordinates need to be swapped
    //  // for 90 and 270 rotations of the level 0 ngon packing rect.
    //  double t;
    //  
    //  t = ngon_sub_pack_rect_size.x;
    //  ngon_sub_pack_rect_size.x = ngon_sub_pack_rect_size.y;
    //  ngon_sub_pack_rect_size.y = t;
    //  
    //  t = ngon_sub_pack_rect_delta.x;
    //  ngon_sub_pack_rect_delta.x = ngon_sub_pack_rect_delta.y;
    //  ngon_sub_pack_rect_delta.y = t;
    //}

    const bool bGridOrder = true;

    ON_2dPoint face_pack_rect_corners[4];
    if (false == f0->GetFacePackRectCorners(bGridOrder, face_pack_rect_corners))
      return false;

    unsigned f1_packing_rotation_degrees = (f0_packing_rotation_degrees + 270U) % 360U;
    for (unsigned i = 0; i < f0_edge_count; ++i)
    {
      ON_2dPoint subd_quad_rect_corners[4];
      if (false == ON_SubDMeshFragment::GetNgonFaceFragmentPackRectCorners(
        f0_edge_count,
        i,
        bGridOrder,
        face_pack_rect_corners,
        f0_pack_rect_size,
        ngon_grid_size,
        ngon_sub_pack_rect_size,
        ngon_sub_pack_rect_delta,
        subd_quad_rect_corners))
        continue;

      ON_2dPoint f1_pack_rect_origin = subd_quad_rect_corners[0];
      ON_2dPoint f1_pack_rect_max = subd_quad_rect_corners[0];
      for (int j = 1; j < 4; ++j)
      {
        const double x = subd_quad_rect_corners[j].x;
        if (x < f1_pack_rect_origin.x)
          f1_pack_rect_origin.x = x;
        else if (x > f1_pack_rect_max.x)
          f1_pack_rect_max.x = x;
        const double y = subd_quad_rect_corners[j].y;
        if (y < f1_pack_rect_origin.y)
          f1_pack_rect_origin.y = y;
        else if (y > f1_pack_rect_max.y)
          f1_pack_rect_max.y = y;
      }

      // NOTE WELL: A multi-face pack MUST be a set of quads that form a rectangular topological grid.
      // 
      // So, for ngons, the f0 ngon necessarily is the only face with it's pack id because it cannot
      // possibly be in a group of QUADS.
      // 
      // Packed textures are assigned to ngons in a way that each subquad must have a distinct pack id.
      // The first sub quad is assigned f0->PackId() and the subsequent subquads get a new pack id.
      const unsigned f1_pack_id = (0 == i) ? f0_pack_id : next_pack_id++;
      ON_SubDFace* f1 = sub_quads[i];
      f1->SetPackIdForExperts(f1_pack_id);
      f1->SetPackRectForExperts(
        f1_pack_rect_origin,
        f1_pack_rect_max - f1_pack_rect_origin,
        f1_packing_rotation_degrees);
    }
  }

  return true;
}

unsigned int ON_SubDimple::Internal_GlobalQuadSubdivideFace(
  const ON_SubDFace* f0,
  bool bSubdividePackRect,
  unsigned& next_pack_id
)
{
  // This is a private member function.  
  // The caller insures f0 != nullptr.

  const unsigned int f0_edge_count = f0->m_edge_count;
  if (f0_edge_count < 3)
    return 0;

  const int material_channel_index = f0->MaterialChannelIndex();
  const ON_Color per_face_color = f0->PerFaceColor();
  const unsigned int level_zero_face_id = (0 == f0->SubdivisionLevel()) ? f0->m_id : f0->m_level_zero_face_id;

  // 2022-06-30, Pierre, RH-69170. Try to keep face packs when globally subdividing
  // 2023-10-11 Dale Lear - RH-77662 - fixing bugs in ngon pact rect subdivision - triangles and ngons were not handled correctly.  

  if (nullptr == f0->m_subd_point1)
  {
    // add face centroid
    double faceC[3];
    if (false == f0->GetSubdivisionPoint( faceC))
      return 0;
    f0->SetSavedSubdivisionPoint(faceC);
    unsigned int level1_index = f0->SubdivisionLevel() + 1;
    ON_SubDVertex* v = AllocateVertex(ON_SubDVertexTag::Smooth, level1_index, faceC );
    AddVertexToLevel(v);
    const_cast<ON_SubDFace*>(f0)->m_subd_point1 = v;
  }

  ON_SubDEdge* E0[2];
  ON__UINT_PTR E0dir[2];
  ON_SubDEdge* E1[4];
  ON__UINT_PTR E1dir[4];
  ON_SubDEdgePtr f1edges[4];
  ON__UINT_PTR e_ptr;
  ON_SubDEdge* FirstE1(nullptr);
  double w;

  e_ptr = f0->EdgePtr(f0_edge_count - 1).m_ptr;
  E0[1] = ON_SUBD_EDGE_POINTER(e_ptr);
  E0dir[1] = ON_SUBD_EDGE_DIRECTION(e_ptr);
  E1[2] = nullptr;

  unsigned int f1_count = 0;

  const double w_2facesector = ON_SubDSectorType::CreaseSectorCoefficient(2);

  // The existing pack rect will be subdivided if and only if f0_pack_id > 0
  // and f0 is successfully subdivided into f0_edge_count man quads
  const unsigned f0_pack_id
    = (bSubdividePackRect && f0->PackRectIsSet() && next_pack_id > 0)
    ? f0->PackId()
    : 0u;

  // sub_quads_buffer[] is used to avoid allocation overhead
  // in the vast majority of cases.
  ON_SubDFace* sub_quads_buffer[8];
  ON_SubDFace** sub_quads;
  if (f0_pack_id > 0)
  {
    // sub_quads != nullptr if and only if f0 has texture packing information
    // that needs to be subdivided.
    sub_quads 
      = (((size_t)f0_edge_count) <= sizeof(sub_quads_buffer) / sizeof(sub_quads_buffer[0]))
      ? sub_quads_buffer
      : (ON_SubDFace**)onmalloc(f0_edge_count * sizeof(sub_quads[0]));
  }
  else
  {
    // Packing information does not exist or will not be subdivided.
    sub_quads = nullptr;
  }

  for (unsigned int i = 0; i < f0_edge_count; i++)
  {
    E0[0] = E0[1];
    E0dir[0] = E0dir[1];
    e_ptr = f0->EdgePtr(i).m_ptr;
    E0[1] = ON_SUBD_EDGE_POINTER(e_ptr);
    E0dir[1] = ON_SUBD_EDGE_DIRECTION(e_ptr);

    if (nullptr == E0[0] || nullptr == E0[1])
      continue;
    if (nullptr == E0[0]->m_subd_point1 || nullptr == E0[1]->m_subd_point1)
      continue;

    e_ptr = E0[0]->m_subd_point1->m_edges[0 == E0dir[0] ? 1 : 0].m_ptr;
    E1[0] = ON_SUBD_EDGE_POINTER(e_ptr);
    E1dir[0] = E0dir[0];

    e_ptr = E0[1]->m_subd_point1->m_edges[0 == E0dir[1] ? 0 : 1].m_ptr;
    E1[1] = ON_SUBD_EDGE_POINTER(e_ptr);
    E1dir[1] = E0dir[1];

    E1[3] = E1[2];
    if (nullptr == E1[3])
    {
      //  The value of E0[0]->m_subd_point1->m_vertex_tag should be either 
      //  ON_SubDVertexTag::Smooth or ON_SubDVertexTag::Crease. In the
      //  case when it's value is "crease", the resulting edge end coefficient
      //  will be 0.5 because the edge has two adjacent faces and "theta"
      //  will be pi/2.  
      //  The resulting quad edge coefficient is 0.5 = 1/2 + 1/3*cos(pi/2).
      w = (ON_SubDVertexTag::Crease == E0[0]->m_subd_point1->m_vertex_tag) ? w_2facesector : 0.0;
      E1[3] = AddEdge(ON_SubDEdgeTag::Smooth, const_cast<ON_SubDVertex*>(f0->m_subd_point1), 0.0, const_cast<ON_SubDVertex*>(E0[0]->m_subd_point1), w);
      if (0 == i)
        FirstE1 = E1[3];
    }
    E1dir[3] = 0;

    if (i + 1 < f0_edge_count || nullptr == FirstE1)
    {
      //  The value of E0[0]->m_subd_point1->m_vertex_tag should be either 
      //  ON_SubDVertexTag::Smooth or ON_SubDVertexTag::Crease. In the
      //  case when it's value is "crease", the resulting edge end coefficient
      //  will be zero because the edge has two adjacent faces and "theta"
      //  will be pi/2.  The resulting edge coefficient is 0.5.
      w = (ON_SubDVertexTag::Crease == E0[1]->m_subd_point1->m_vertex_tag) ? w_2facesector : 0.0;
      E1[2] = AddEdge(ON_SubDEdgeTag::Smooth, const_cast<ON_SubDVertex*>(f0->m_subd_point1), 0.0, const_cast<ON_SubDVertex*>(E0[1]->m_subd_point1), w);
    }
    else
    {
      E1[2] = FirstE1;
    }
    E1dir[2] = 1;

    f1edges[0] = ON_SubDEdgePtr::Create(E1[0], E1dir[0]);
    f1edges[1] = ON_SubDEdgePtr::Create(E1[1], E1dir[1]);
    f1edges[2] = ON_SubDEdgePtr::Create(E1[2], E1dir[2]);
    f1edges[3] = ON_SubDEdgePtr::Create(E1[3], E1dir[3]);

    ON_SubDFace* f1 = AddFace(4, f1edges);
    if (nullptr != f1)
    {
      f1->SetMaterialChannelIndex(material_channel_index);
      f1->SetPerFaceColor(per_face_color);
      f1->m_level_zero_face_id = level_zero_face_id;
      if (nullptr != sub_quads)
        sub_quads[f1_count] = f1;
      f1_count++;
    }
  }

  if (nullptr != sub_quads)
  {
    // sub_quads != nullptr if and only if f0 has texture packing information
    // that needs to be subdivided.
    // 
    // The existing pack rect needs to be subdivided and assigned to the subdivided faces
    if (f0_edge_count == f1_count)
      Internal_SubdivideFacePacking(f0, f0_edge_count, f0_pack_id, next_pack_id, sub_quads );

    if (sub_quads != sub_quads_buffer)
      onfree(sub_quads);
  }

  // return number of new sub quad faces
  return f1_count;
}

unsigned int ON_SubD::GlobalSubdivideQuadCount() const
{
  return GlobalSubdivideQuadCount(1);
}

unsigned int ON_SubD::GlobalSubdivideQuadCount(unsigned int subdivision_count) const
{
  if (subdivision_count >= 16)
    return ON_UINT_MAX;
  unsigned int subdivide_quad_count = 0;
  if (subdivision_count >= 1)
  {
    unsigned int level1_quad_count = 0;
    ON_SubDFaceIterator fit(*this);
    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
      level1_quad_count += f->EdgeCount();
    const unsigned pow4 = 1U << (2U*subdivision_count); // pow4 = 4^subdivision_count
    subdivide_quad_count = (subdivide_quad_count > ON_UINT_MAX / pow4) ? ON_UINT_MAX  : (level1_quad_count * pow4);
  }
  return subdivide_quad_count;
}

bool ON_SubD::GlobalSubdivide()
{
  return GlobalSubdivide(1U);
}

bool ON_SubD::GlobalSubdivide(
  unsigned int count
)
{
  ON_SubDimple* subdimple = SubDimple(false);
  if (nullptr == subdimple)
    return ON_SUBD_RETURN_ERROR(false);
  return subdimple->GlobalSubdivide(count);
}

bool ON_SubD::LocalSubdivide(
  const ON_SimpleArray<ON_COMPONENT_INDEX>& face_list
)
{
  const int count = face_list.Count();
  ON_SimpleArray< const ON_SubDFace* > ptr_list(count);
  for (int i = 0; i < count; ++i)
  {
    const ON_COMPONENT_INDEX ci = face_list[i];
    if (ON_COMPONENT_INDEX::TYPE::subd_face != ci.m_type)
      continue;
    if (ci.m_index <= 0)
      continue;
    const ON_SubDFace* f = this->FaceFromId(ci.m_index);
    if (nullptr == f)
      continue;
    ptr_list.Append(f);
  }
  const bool rc = LocalSubdivide(ptr_list);
  return rc;
}

bool ON_SubD::LocalSubdivide(const ON_SimpleArray< const ON_SubDFace* >& face_list)
{
  return LocalSubdivide(face_list.Array(), face_list.UnsignedCount());
}

bool ON_SubD::LocalSubdivide( ON_SubDFace const*const* face_list, size_t face_count)
{
  ON_SubDimple* subdimple = SubDimple(false);
  if (nullptr == subdimple)
    return ON_SUBD_RETURN_ERROR(false);
  return subdimple->LocalSubdivide(face_list, face_count);
}

bool ON_SubDimple::GlobalSubdivide(
  unsigned int count
  )
{
  if (m_levels.UnsignedCount() < 1)
    return ON_SUBD_RETURN_ERROR(false);
  if (nullptr == m_active_level)
  {
    m_active_level = m_levels[m_levels.UnsignedCount() - 1];
    if (nullptr == m_active_level)
      return ON_SUBD_RETURN_ERROR(false);
  }

  const unsigned level0_index = m_active_level->m_level_index;
  if (level0_index >= m_levels.UnsignedCount() || nullptr == m_levels[level0_index])
    return ON_SUBD_RETURN_ERROR(false);

  if (count <= 0)
    return ON_SUBD_RETURN_ERROR(false);

  if (level0_index + count > ON_SubD::maximum_subd_level)
    return ON_SUBD_RETURN_ERROR(false);

  ClearHigherSubdivisionLevels(level0_index + 1);
  if (level0_index + 1 != m_levels.UnsignedCount() )
    return ON_SUBD_RETURN_ERROR(false);

  m_active_level = m_levels[level0_index];
 
  for (unsigned int i = level0_index +1; i <= level0_index +count; i++)
  {
    unsigned int rc = GlobalSubdivide();
    if (i != rc)
      return ON_SUBD_RETURN_ERROR(false);
    m_active_level = m_levels[i];
  }
  return true;
}

ON_SubDEdgePtr ON_SubDimple::MergeConsecutiveEdges(
  ON_SubDEdgePtr eptr0,
  ON_SubDEdgePtr eptr1
  )
{
  if ( false == ON_SubD::EdgesAreConsecutive(eptr0,eptr1) )
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);

  ON_SubDEdge* e[2] = { ON_SUBD_EDGE_POINTER(eptr0.m_ptr), ON_SUBD_EDGE_POINTER(eptr1.m_ptr) };
  ON__UINT_PTR edir[2] = { ON_SUBD_EDGE_DIRECTION(eptr0.m_ptr), ON_SUBD_EDGE_DIRECTION(eptr1.m_ptr) };
  const ON_SubDVertex* end_v[2] = {e[0]->m_vertex[edir[0]], e[1]->m_vertex[1 - edir[1]]};
  if (nullptr == end_v[0] || nullptr == end_v[1] || end_v[0] == end_v[1] )
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);

  ON_SubDEdgeTag merged_edge_tag 
    = (e[0]->IsSmooth() || e[1]->IsSmooth())
    ? ON_SubDEdgeTag::Smooth
    : ON_SubDEdgeTag::Crease;

  for (unsigned int j = 0; j < e[1]->m_face_count; j++)
  {
    ON_SubDFace* f = const_cast<ON_SubDFace*>(e[1]->Face(j));
    if (nullptr == f)
      continue;
    f->RemoveEdgeFromArray(e[1]);
  }
  
  // remove middle vertex
  ON_SubDVertex* middle_v = const_cast< ON_SubDVertex* >(e[1]->m_vertex[edir[1]]);
  if (nullptr != middle_v && middle_v != end_v[0] && middle_v != end_v[1] )
  {
    if (middle_v->m_edge_count > 0 && nullptr != middle_v->m_edges)
    {
      unsigned int vei0 = middle_v->EdgeArrayIndex(e[0]);
      unsigned int vei1 = middle_v->EdgeArrayIndex(e[1]);      
      unsigned int vei_count = middle_v->m_edge_count;
      middle_v->m_edge_count = 0;
      for (unsigned int vei = 0; vei < vei_count; vei++)
      {
        if ( vei == vei0 || vei == vei1 )
          continue;

        // happens when middle_v is a multiple sector corner, non-manifold, or other rare cases
        if (vei > middle_v->m_edge_count)
          middle_v->m_edges[middle_v->m_edge_count] = middle_v->m_edges[vei];
        middle_v->m_edge_count++;
      }
    }
    if (0 == middle_v->m_edge_count || nullptr == middle_v->m_edges)
    {
      ReturnVertex(middle_v);
      middle_v = nullptr;
    }
  }

  e[0]->m_vertex[1-edir[0]] = nullptr;
  e[1]->m_vertex[edir[1]] = nullptr;
  e[1]->m_vertex[1-edir[1]] = nullptr;

  for (unsigned int i = 0; i < end_v[1]->m_edge_count; i++)
  {
    if (e[1] == ON_SUBD_EDGE_POINTER(end_v[1]->m_edges[i].m_ptr))
    {
      const_cast< ON_SubDVertex* >(end_v[1])->m_edges[i] = ON_SubDEdgePtr::Create(e[0], 1 - edir[0]);
      e[0]->m_vertex[1 - edir[0]] = end_v[1];
      break;
    }
  }

  e[0]->m_sector_coefficient[1 - edir[0]] = e[1]->m_sector_coefficient[1 - edir[1]];

  const bool bTagged[2] = { end_v[0]->IsCreaseOrCorner(), end_v[1]->IsCreaseOrCorner() };
  if (ON_SubDEdgeTag::Smooth == merged_edge_tag || false == bTagged[0] || false == bTagged[1])
  {
    e[0]->m_edge_tag
      = (bTagged[0] && bTagged[1])
      ? ON_SubDEdgeTag::SmoothX
      : ON_SubDEdgeTag::Smooth;
    if ( false == bTagged[0])
      e[0]->m_sector_coefficient[0] = ON_SubDSectorType::IgnoredSectorCoefficient;
    else if (!(e[0]->m_sector_coefficient[0] > 0.0 && e[0]->m_sector_coefficient[0] < 1.0))
      e[0]->m_sector_coefficient[0] = ON_SubDSectorType::UnsetSectorCoefficient;
    if ( false == bTagged[1])
      e[0]->m_sector_coefficient[1] = ON_SubDSectorType::IgnoredSectorCoefficient;
    else if (!(e[0]->m_sector_coefficient[1] > 0.0 && e[0]->m_sector_coefficient[1] < 1.0))
      e[0]->m_sector_coefficient[1] = ON_SubDSectorType::UnsetSectorCoefficient;
  }
  else
  {
    e[0]->m_edge_tag = ON_SubDEdgeTag::Crease;
    e[0]->m_sector_coefficient[0] = ON_SubDSectorType::IgnoredSectorCoefficient;
    e[0]->m_sector_coefficient[1] = ON_SubDSectorType::IgnoredSectorCoefficient;
  }

  ReturnEdge(e[1]);

  return eptr0;
}

ON_SubDEdgePtr ON_SubD::MergeConsecutiveEdges(
  ON_SubDEdgePtr eptr0,
  ON_SubDEdgePtr eptr1
  )
{
  ON_SubDimple* subdimple = SubDimple(false);
  return (nullptr != subdimple) ? subdimple->MergeConsecutiveEdges(eptr0, eptr1) : ON_SubDEdgePtr::Null;
}

static bool Internal_EdgesAreConsecutive(
  const ON_SubDEdgePtr eptr[2],
  bool bTestColinearity,
  double distance_tolerance,
  double maximum_aspect,
  double sin_angle_tolerance
  )
{
  const ON_SubDEdge* e[2] = { ON_SUBD_EDGE_POINTER(eptr[0].m_ptr), ON_SUBD_EDGE_POINTER(eptr[1].m_ptr) };
  ON__UINT_PTR edir[2] = { ON_SUBD_EDGE_DIRECTION(eptr[0].m_ptr), ON_SUBD_EDGE_DIRECTION(eptr[1].m_ptr) };
  if (
    nullptr == e[0] || nullptr == e[1] 
    || e[0] == e[1]
    || edir[0] > 1 || edir[1] > 1
    || e[0]->m_face_count != e[1]->m_face_count
    //|| e[0]->m_edge_tag != e[1]->m_edge_tag
    )
  {
    return false;
  }

  if ( nullptr == e[1]->m_vertex[0] || nullptr == e[1]->m_vertex[1] )
  {
    return false;
  }

  // v[0] = start
  // v[1] = end
  // v[2] = middle (will be removed)
  const ON_SubDVertex* v[4] = { e[0]->m_vertex[edir[0]], e[1]->m_vertex[1 - edir[1]], e[0]->m_vertex[1 - edir[0]], e[1]->m_vertex[edir[1]] };

  if (nullptr == v[0] || nullptr == v[1] || nullptr == v[2] || v[0] == v[1] || v[2] != v[3])
  {
    return false;
  }

  if (bTestColinearity)
  {
    if (ON_UNSET_UINT_INDEX == v[2]->EdgeArrayIndex(e[0]) || ON_UNSET_UINT_INDEX == v[2]->EdgeArrayIndex(e[1]))
      bTestColinearity = false;
  }

  // edges must have the same faces
  switch (e[0]->m_face_count)
  {
  case 0:
    break;

  case 1:
    if (ON_SUBD_FACE_POINTER(e[0]->m_face2[0].m_ptr) == ON_SUBD_FACE_POINTER(e[1]->m_face2[0].m_ptr))
      break;

    return false;

  case 2:
    if (ON_SUBD_FACE_POINTER(e[0]->m_face2[0].m_ptr) == ON_SUBD_FACE_POINTER(e[1]->m_face2[0].m_ptr)
      && ON_SUBD_FACE_POINTER(e[0]->m_face2[1].m_ptr) == ON_SUBD_FACE_POINTER(e[1]->m_face2[1].m_ptr))
      break;

    if (ON_SUBD_FACE_POINTER(e[0]->m_face2[0].m_ptr) == ON_SUBD_FACE_POINTER(e[1]->m_face2[1].m_ptr)
      && ON_SUBD_FACE_POINTER(e[0]->m_face2[1].m_ptr) == ON_SUBD_FACE_POINTER(e[1]->m_face2[0].m_ptr))
      break;

    return false;

  default:
    // non-manifold edge
    {
      unsigned int j, k;
      for (j = 0; j < e[0]->m_face_count; j++)
      {
        const ON_SubDFace* f = e[0]->Face(j);
        for (k = 0; k < e[1]->m_face_count; k++)
        {
          if (f == e[1]->Face(k))
            break;
        }
        if (k < e[1]->m_face_count)
          continue;
        break;
      }
      if (j != e[0]->m_face_count)
        return false;
    }
    break;
  }

  if (bTestColinearity)
  {
    const ON_3dPoint* P[3] = { (const ON_3dPoint*)v[0]->m_P, (const ON_3dPoint*)v[2]->m_P, (const ON_3dPoint*)v[1]->m_P };

    ON_3dVector D(*P[2] - *P[0]);
    const double d = D.Length();
    if (!(d > 0.0))
      return false;
    const ON_3dVector V(*P[1] - *P[0]);
    const double t = (V*D) / (d*d);
    if (!(t > ON_EPSILON && t < 1.0 - ON_EPSILON))
      return false;

    const ON_3dPoint M = (1.0 - t)*(*P[0]) + t*(*P[2]);
    const double h = P[1]->DistanceTo(M);

    if (0.0 == h)
      return true;

    if (!(h > 0.0))
      return false;

    const double miniscule_distance_tolerance = ON_ZERO_TOLERANCE;
    if (h <= miniscule_distance_tolerance && !(distance_tolerance >= 0.0 && distance_tolerance < miniscule_distance_tolerance))
    {
      // skip parameter tests for minuscule h.
      return true;
    }

    const double miniscule_maximum_aspect = 1e-4;
    if (h <= miniscule_maximum_aspect * d && !(maximum_aspect >= 0.0 && maximum_aspect < miniscule_maximum_aspect))
    {
      // skip parameter tests for minuscule h/d.
      return true;
    }

    if (distance_tolerance >= 0.0 && !(h <= distance_tolerance))
      return false; // failed distance to chord test

    if (maximum_aspect >= 0.0 && !(h <= maximum_aspect * d))
      return false; // failed maximum aspect test

    if (sin_angle_tolerance >= 0.0 && sin_angle_tolerance < 1.0 && !(ON_CrossProduct(V, (*P[1] - *P[2])).Length() <= sin_angle_tolerance))
      return false; // failed minimum angle test
  }
  return true;
}

bool ON_SubD::EdgesAreConsecutive(
  ON_SubDEdgePtr eptr0,
  ON_SubDEdgePtr eptr1
  )
{
  ON_SubDEdgePtr eptr[2] = { eptr0,eptr1 };
  return Internal_EdgesAreConsecutive(eptr,false,ON_DBL_QNAN,ON_DBL_QNAN,ON_DBL_QNAN);
}

static bool Internal_EdgesPassTypeFilter(
  const ON_SubDEdgePtr eptr[2],
  bool bMergeBoundaryEdges,
  bool bMergeInteriorCreaseEdges,
  bool bMergeInteriorSmoothEdges
)
{
  for (unsigned i = 0; i < 2; ++i)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr[i].m_ptr);
    if (nullptr == e || e->m_face_count < 1)
      return false;
    if (1 == e->m_face_count)
    {
      if (false == bMergeBoundaryEdges)
        return false;
    }
    else if (e->m_face_count >= 2)
    {
      if (false == (e->IsSmooth() ? bMergeInteriorSmoothEdges : bMergeInteriorCreaseEdges))
        return false;
    }
    else
      return false;
  };
  return true;
}

unsigned int ON_SubDimple::MergeColinearEdges(
  bool bMergeBoundaryEdges,
  bool bMergeInteriorCreaseEdges,
  bool bMergeInteriorSmoothEdges,
  double distance_tolerance,
  double maximum_aspect,
  double sin_angle_tolerance
  )
{
  if (1 != m_levels.UnsignedCount())
    return false;

  unsigned int removed_edge_count = 0;

  for (const ON_SubDFace* f = ActiveLevel().m_face[0]; nullptr != f; f = f->m_next_face)
  {
    unsigned int edge_count = f->m_edge_count;
    if (edge_count < 3)
      continue;
    
    // First - find a pair of edges that should not be merged.
    ON_SubDEdgePtr eptr[2] = { ON_SubDEdgePtr::Null, f->EdgePtr(edge_count - 1) };
    unsigned int fei0 = 0;
    while (fei0 < edge_count)
    {
      eptr[0] = eptr[1];
      eptr[1] = f->EdgePtr(fei0);
      if (false == Internal_EdgesAreConsecutive(eptr, true, distance_tolerance, maximum_aspect, sin_angle_tolerance))
        break;
      if (false == Internal_EdgesPassTypeFilter(eptr, bMergeBoundaryEdges, bMergeInteriorCreaseEdges, bMergeInteriorSmoothEdges))
        break;
      ++fei0;
    }
    if (fei0 >= edge_count)
    {
      // face is degenerate or corrupt.
      continue;
    }
    if (0 != fei0)
    {
      if (false == (const_cast<ON_SubDFace*>(f)->RotateEdgeArray(fei0)))
      {
        // face is degenerate or corrupt.
        continue;
      }
    }

    // At this point, we know the last edge and the first edge should not me merged.
    eptr[1] = f->EdgePtr(0U);
    unsigned int fei = 1;
    while ( fei < edge_count)
    {
      eptr[0] = eptr[1];
      eptr[1] = f->EdgePtr(fei);
      if (
        Internal_EdgesAreConsecutive(eptr, true, distance_tolerance, maximum_aspect, sin_angle_tolerance)
        && Internal_EdgesPassTypeFilter(eptr, bMergeBoundaryEdges, bMergeInteriorCreaseEdges, bMergeInteriorSmoothEdges)
        )
      {
        // merge edges f->Edge(fei-1) and f->Edge(fei) into f->Edge(fei-1).
        if (eptr[0].m_ptr != MergeConsecutiveEdges(eptr[0], eptr[1]).m_ptr)
        {
          ON_SUBD_ERROR("Bug in consecutive edge merging.");
          break;
        }
        ++removed_edge_count;
        --edge_count;
        eptr[1] = eptr[0];
      }
      else
      {
        ++fei;
      }
    }
  }

  return removed_edge_count;
}

unsigned int ON_SubD::MergeColinearEdges(
  bool bMergeBoundaryEdges,
  bool bMergeInteriorCreaseEdges,
  bool bMergeInteriorSmoothEdges,
  double distance_tolerance,
  double maximum_aspect,
  double sin_angle_tolerance
  )
{
  ON_SubDimple* subdimple = SubDimple(false);
  return 
    (nullptr != subdimple) 
    ? subdimple->MergeColinearEdges( bMergeBoundaryEdges, bMergeInteriorCreaseEdges, bMergeInteriorSmoothEdges, distance_tolerance, maximum_aspect, sin_angle_tolerance) 
    : 0;
}

unsigned int ON_SubD::LevelCount() const
{
  const ON_SubDimple* subdimple = SubDimple();
  return (0 != subdimple ? subdimple->LevelCount() : 0);
}


unsigned int ON_SubD::ActiveLevelIndex() const
{
  return ActiveLevel().m_level_index;
}

bool ON_SubD::IsEmpty() const
{
  return (nullptr == SubDimple());
}

bool ON_SubD::IsNotEmpty() const
{
  return (nullptr != SubDimple());
}

/////////////////////////////////////////////////////////
//
// Element (Vertex, Edge, Face) access
//
const ON_COMPONENT_INDEX ON_SubDComponentPtr::ComponentIndex() const
{
  switch (ComponentType())
  {
  case ON_SubDComponentPtr::Type::Vertex:
    {
      const ON_SubDVertex* vertex = ON_SUBD_VERTEX_POINTER(m_ptr);
      if ( nullptr != vertex)
        return ON_COMPONENT_INDEX(ON_COMPONENT_INDEX::TYPE::subd_vertex,vertex->m_id);
    }
    break;
  case ON_SubDComponentPtr::Type::Edge:
    {
      const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(m_ptr);
      if ( nullptr != edge)
        return ON_COMPONENT_INDEX(ON_COMPONENT_INDEX::TYPE::subd_edge,edge->m_id);
    }
    break;
  case ON_SubDComponentPtr::Type::Face:
    {
      const ON_SubDFace* face = ON_SUBD_FACE_POINTER(m_ptr);
      if ( nullptr != face)
        return ON_COMPONENT_INDEX(ON_COMPONENT_INDEX::TYPE::subd_face,face->m_id);
    }
    break;
  default:
    if (IsNull() )
      return ON_COMPONENT_INDEX::UnsetComponentIndex;
    break;
  }
  return ON_SUBD_RETURN_ERROR(ON_COMPONENT_INDEX::UnsetComponentIndex);
}

const ON_SubDComponentPtr ON_SubD::ComponentPtrFromComponentIndex(
  ON_COMPONENT_INDEX component_index
  ) const
{
  if (0 != component_index.m_index && -1 != component_index.m_index)
  {
    switch (component_index.m_type)
    {
    case ON_COMPONENT_INDEX::TYPE::subd_vertex:
      return ON_SubDComponentPtr::Create(VertexFromId(component_index.m_index));
    case ON_COMPONENT_INDEX::TYPE::subd_edge:
      return ON_SubDComponentPtr::Create(EdgeFromId(component_index.m_index));
    case ON_COMPONENT_INDEX::TYPE::subd_face:
      return ON_SubDComponentPtr::Create(FaceFromId(component_index.m_index));
    default:
      break;
    }
  }
  else if (ON_COMPONENT_INDEX::TYPE::invalid_type == component_index.m_type)
  {
    return ON_SubDComponentPtr::Null;
  }

  return ON_SUBD_RETURN_ERROR(ON_SubDComponentPtr::Null);
}

/////////////////////////////////////////////////////////
//
// Vertex access
//

unsigned int ON_SubD::VertexCount() const
{
  return ActiveLevel().m_vertex_count;
}

const ON_SubDVertex* ON_SubD::FirstVertex() const
{
  return ActiveLevel().m_vertex[0];
}

const ON_SubDVertex* ON_SubD::LastVertex() const
{
  return ActiveLevel().m_vertex[1];
}

ON_SubDVertexIterator ON_SubD::VertexIterator() const
{
  return ON_SubDVertexIterator(*this);
}

ON_SubDVertexIterator ON_SubDRef::VertexIterator() const
{
  return ON_SubDVertexIterator(*this);
}

ON_SubDVertexArray ON_SubD::VertexArray() const
{
  return ON_SubDVertexArray(*this);
}

const class ON_SubDVertex* ON_SubD::VertexFromId(
  unsigned int vertex_id
  ) const
{
  for (;;)
  {
    if (0 == vertex_id || ON_UNSET_UINT_INDEX == vertex_id )
      break;
    const ON_SubDimple* subdimple = SubDimple();
    if (nullptr == subdimple)
      break;
    return subdimple->VertexFromId(vertex_id);
  }
  return nullptr;
}

const class ON_SubDVertex* ON_SubD::VertexFromComponentIndex(
  ON_COMPONENT_INDEX component_index
) const
{
  return (ON_COMPONENT_INDEX::TYPE::subd_vertex == component_index.m_type) ? VertexFromId(component_index.m_index) : nullptr;
}

const ON_COMPONENT_INDEX ON_SubDVertex::ComponentIndex() const
{
  return ON_COMPONENT_INDEX(ON_COMPONENT_INDEX::TYPE::subd_vertex,m_id);
}

const ON_SubDComponentPtr ON_SubDVertex::ComponentPtr() const
{
  return ON_SubDComponentPtr::Create(this);
}

/////////////////////////////////////////////////////////
//
// Edge access
//

unsigned int ON_SubD::EdgeCount() const
{
  return ActiveLevel().m_edge_count;
}

const ON_SubDEdge* ON_SubD::FirstEdge() const
{
  return ActiveLevel().m_edge[0];
}

const ON_SubDEdge* ON_SubD::LastEdge() const
{
  return ActiveLevel().m_edge[1];
}

ON_SubDEdgeIterator ON_SubD::EdgeIterator() const
{
  return ON_SubDEdgeIterator(*this);
}

ON_SubDEdgeIterator ON_SubDRef::EdgeIterator() const
{
  return ON_SubDEdgeIterator(*this);
}

ON_SubDEdgeArray ON_SubD::EdgeArray() const
{
  return ON_SubDEdgeArray(*this);
}

const class ON_SubDEdge* ON_SubD::EdgeFromId(
  unsigned int edge_id
  ) const
{
  for (;;)
  {
    if (0 == edge_id || ON_UNSET_UINT_INDEX == edge_id )
      break;
    const ON_SubDimple* subdimple = SubDimple();
    if (nullptr == subdimple)
      break;
    return subdimple->EdgeFromId(edge_id);
  }
  return nullptr;
}

const class ON_SubDEdge* ON_SubD::EdgeFromComponentIndex(
  ON_COMPONENT_INDEX component_index
) const
{
  return (ON_COMPONENT_INDEX::TYPE::subd_edge == component_index.m_type) ? EdgeFromId(component_index.m_index) : nullptr;
}

const ON_COMPONENT_INDEX ON_SubDEdge::ComponentIndex() const
{
  return ON_COMPONENT_INDEX(ON_COMPONENT_INDEX::TYPE::subd_edge,m_id);
}

const ON_SubDComponentPtr ON_SubDEdge::ComponentPtr() const
{
  return ON_SubDComponentPtr::Create(this);
}

/////////////////////////////////////////////////////////
//
// Face access
//

unsigned int ON_SubD::FaceCount() const
{
  return ActiveLevel().m_face_count;
}

const ON_SubDFace* ON_SubD::FirstFace() const
{
  return ActiveLevel().m_face[0];
}

const ON_SubDFace* ON_SubD::LastFace() const
{
  return ActiveLevel().m_face[1];
}

ON_SubDFaceIterator ON_SubD::FaceIterator() const
{
  return ON_SubDFaceIterator(*this);
}

ON_SubDFaceIterator ON_SubDRef::FaceIterator() const
{
  return ON_SubDFaceIterator(*this);
}


ON_SubDFaceArray ON_SubD::FaceArray() const
{
  return ON_SubDFaceArray(*this);
}

const class ON_SubDFace* ON_SubD::FaceFromId(
  unsigned int face_id
  ) const
{
  for (;;)
  {
    if (0 == face_id || ON_UNSET_UINT_INDEX == face_id )
      break;
    const ON_SubDimple* subdimple = SubDimple();
    if (nullptr == subdimple)
      break;
    return subdimple->FaceFromId(face_id);
  }
  return nullptr;
}

const class ON_SubDFace* ON_SubD::FaceFromComponentIndex(
  ON_COMPONENT_INDEX component_index
) const
{
  return (ON_COMPONENT_INDEX::TYPE::subd_face == component_index.m_type) ? FaceFromId(component_index.m_index) : nullptr;
}

const ON_COMPONENT_INDEX ON_SubDFace::ComponentIndex() const
{
  return ON_COMPONENT_INDEX(ON_COMPONENT_INDEX::TYPE::subd_face,m_id);
}

const ON_SubDComponentPtr ON_SubDFace::ComponentPtr() const
{
  return ON_SubDComponentPtr::Create(this);
}

/////////////////////////////////////////////////////////
//
// ON_SubD properties
//

bool ON_SubD::IsOriented() const
{
  for (const ON_SubDEdge* edge = FirstEdge(); nullptr != edge; edge = edge->m_next_edge)
  {
    if ( 2 != edge->m_face_count )
      continue;
    if (nullptr == ON_SUBD_FACE_POINTER(edge->m_face2[0].m_ptr) || nullptr == ON_SUBD_FACE_POINTER(edge->m_face2[1].m_ptr) )
      continue;
    if ( ON_SUBD_FACE_DIRECTION(edge->m_face2[0].m_ptr) == ON_SUBD_FACE_DIRECTION(edge->m_face2[1].m_ptr) )
      return false;
  }
  return true;
}

// reverses the orientation of all facets
bool ON_SubD::ReverseOrientation() const
{

  // Limit point normals and limit surface mesh fragments will need to be recalculated.
  // DestroyRuntimeCache() will clear all this information.
  const_cast<ON_SubD*>(this)->DestroyRuntimeCache(true);


  for (const ON_SubDFace* face = FirstFace(); nullptr != face; face = face->m_next_face)
  {
    const_cast<ON_SubDFace*>(face)->ReverseEdgeList();
  }
  return true;
}

// Attempts to orient all facet to match the first facet.

static unsigned int OrientFaceNeighbors(
  unsigned int recursion_level,
  const ON_SubDFace** face_list,
  unsigned int id0,
  const ON_SubDFace* face
  )
{
  ON_SubDFace* next_set[4];
  const unsigned int next_set_capacity = (unsigned int)(sizeof(next_set) / sizeof(next_set[0]));
  unsigned int next_set_count = 0;

  const unsigned int edge_count = face->m_edge_count;
  const ON_SubDEdgePtr* face_eptr = face->m_edge4;
  const ON_SubDEdge* e;
  ON_SubDFace* neighbor_face;

  if (nullptr != face_list[face->m_id - id0])
  {
    // search for an oriented neighbor
    neighbor_face = nullptr;
    for (unsigned int fei = 0; fei < edge_count; fei++, face_eptr++)
    {
      if (4 == fei)
      {
        face_eptr = face->m_edgex;
        if (nullptr == face_eptr)
          break;
      }
      e = ON_SUBD_EDGE_POINTER(face_eptr->m_ptr);
      if (nullptr == e || 2 != e->m_face_count)
        continue;
      neighbor_face = ON_SUBD_FACE_POINTER(e->m_face2[0].m_ptr);
      if (face == neighbor_face)
        neighbor_face = ON_SUBD_FACE_POINTER(e->m_face2[1].m_ptr);
      else if (face != ON_SUBD_FACE_POINTER(e->m_face2[1].m_ptr))
        continue;
      if (nullptr == neighbor_face)
        continue;

      if (nullptr == face_list[neighbor_face->m_id - id0])
        return OrientFaceNeighbors(recursion_level,face_list,id0,neighbor_face);
    }

    // nothing near face is oriented. 
    return 0;
  }

  unsigned int orient_count = 0;
  for (unsigned int fei = 0; fei < edge_count; fei++, face_eptr++)
  {
    if (4 == fei)
    {
      face_eptr = face->m_edgex;
      if ( nullptr == face_eptr)
        break;
    }
    e = ON_SUBD_EDGE_POINTER(face_eptr->m_ptr);
    if (nullptr == e || 2 != e->m_face_count)
      continue;
    neighbor_face = ON_SUBD_FACE_POINTER(e->m_face2[0].m_ptr);
    if (face == neighbor_face)
      neighbor_face = ON_SUBD_FACE_POINTER(e->m_face2[1].m_ptr);
    else if (face != ON_SUBD_FACE_POINTER(e->m_face2[1].m_ptr))
      continue;
    if (nullptr == neighbor_face)
      continue;

    if (nullptr == face_list[neighbor_face->m_id - id0])
      continue;

    if (ON_SUBD_FACE_DIRECTION(e->m_face2[0].m_ptr) == ON_SUBD_FACE_DIRECTION(e->m_face2[1].m_ptr))
      neighbor_face->ReverseEdgeList();
    face_list[neighbor_face->m_id - id0] = nullptr;
    orient_count++;

    if (recursion_level < 12)
    {
      if (next_set_count >= next_set_capacity)
      {
        for (unsigned i = 0; i < next_set_capacity; i++)
          orient_count += OrientFaceNeighbors(recursion_level + 1, face_list, id0, next_set[i]);
        next_set_count = 0;
      }
      next_set[next_set_count++] = neighbor_face;
    }
  }

  for ( unsigned i = 0; i < next_set_count; i++)
    orient_count += OrientFaceNeighbors(recursion_level+1,face_list,id0,next_set[i]);

  return orient_count;
}

bool ON_SubD::Orient() const
{
  const ON_SubDFace* first_face = FirstFace();
  if ( nullptr == first_face || nullptr == first_face->m_next_face)
    return true;

  unsigned int nonzero_face_count = 0;
  ON_SimpleArray< const ON_SubDFace* > faces_array(FaceCount());
  unsigned int face_id0 = first_face->m_id;
  unsigned int face_id1 = first_face->m_id;
  for (const ON_SubDFace* face = FirstFace(); nullptr != face; face = face->m_next_face)
  {
    faces_array.Append(face);
    if (face->m_id > face_id1)
      face_id1 = face->m_id;
    else if (face->m_id < face_id0)
      face_id0 = face->m_id;
    nonzero_face_count++;
  }

  const unsigned int face_count = faces_array.UnsignedCount();
  if (face_count <= 1)
    return true;

  const ON_SubDFace** faces = faces_array.Array();
  if (face_id1 - face_id0 >= faces_array.UnsignedCount())
  {
    faces_array.Reserve(face_id1 - face_id0 + 1);
    faces_array.SetCount(face_id1 - face_id0 + 1);
    faces_array.Zero();
    // Update faces pointer after reallocating faces_array
    faces = faces_array.Array();
    for (const ON_SubDFace* face = FirstFace(); nullptr != face; face = face->m_next_face)
    {
      faces[face->m_id-face_id0] = face;
    }
  }

  unsigned int orient_count = 0;
  unsigned int connected_region_count = 0;
  bool bSearchForNewComponent = true;
  unsigned int first_face_index = 0;

  for (;;)
  {
    unsigned int orient_count0 = orient_count;
    while (first_face_index < face_count && nullptr == faces[first_face_index])
      first_face_index++;

    if ( first_face_index >= face_count)
      break;

    for (unsigned int i = first_face_index; i < face_count && orient_count < nonzero_face_count; i++)
    {
      const ON_SubDFace* face = faces[i];
      if (nullptr == face)
        continue;
      if (bSearchForNewComponent)
      {
        // first face in new connected component
        orient_count++;
        connected_region_count++;
        faces[i] = nullptr;
        bSearchForNewComponent = false;
        first_face_index = i+1;
      }
      orient_count += OrientFaceNeighbors(0, faces, face_id0, face);
    }
    
    if ( orient_count >= nonzero_face_count)
      break;

    if (orient_count0 >= orient_count)
    {
      if (bSearchForNewComponent)
        break;
      bSearchForNewComponent = true;
    }
  }

  return (connected_region_count > 0 && orient_count > 0);
}

const ON_SubDVertex * ON_SubD::ReplaceFaceWithTriangleFan(ON_SubDFace * face, ON_3dPoint fan_center_point, bool bMarkFaces)
{
  const unsigned edge_count = face->m_edge_count;
  if (edge_count < 3)
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON_SubDimple* subdimple = SubDimple(false);
  if (nullptr == subdimple)
    return ON_SUBD_RETURN_ERROR(nullptr);

  // validate and get centroid (which may not be needed).
  ON_3dPoint P = ON_3dPoint::Origin;
  ON_SimpleArray<ON_SubDEdgePtr> edges(edge_count);
  const ON_SubDEdgePtr* eptr = face->m_edge4;
  for (unsigned i = 0; i < edge_count; ++i, ++eptr)
  {
    if (4U == i)
    {
      eptr = face->m_edgex;
      if (nullptr == eptr)
        return ON_SUBD_RETURN_ERROR(nullptr);
    }
    const ON_SubDVertex* v = eptr->RelativeVertex(0);
    if (nullptr == v)
      return ON_SUBD_RETURN_ERROR(nullptr);
    P += v->ControlNetPoint();
    edges.Append(*eptr);
  }

  if (fan_center_point.IsValid())
    P = fan_center_point;
  else
    P /= ((double)edge_count);

  ON_SubDVertex* v0 = AddVertex(ON_SubDVertexTag::Smooth, P);
  if (nullptr == v0)
    return ON_SUBD_RETURN_ERROR(nullptr);

  for (unsigned i = 0; i < edge_count; ++i, ++eptr)
  {
    if (nullptr == AddEdge(ON_SubDEdgeTag::Smooth, v0, const_cast<ON_SubDVertex*>(edges[i].RelativeVertex(0))))
    {
      ON_SubDComponentPtr cptr = ON_SubDComponentPtr::Create(v0);
      DeleteComponents(&cptr, 1, false);
      return ON_SUBD_RETURN_ERROR(nullptr);
    }
  }

  for (unsigned i = 0; i < edge_count; ++i, ++eptr)
  {
    if (i < 4)
      face->m_edge4[i] = ON_SubDEdgePtr::Null;
    else
      face->m_edgex[i - 4] = ON_SubDEdgePtr::Null;
    ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(edges[i].m_ptr);
    e->RemoveFaceFromArray(face);
    const_cast<ON_SubDVertex*>(edges[i].RelativeVertex(0))->RemoveFaceFromArray(face);
  }

  subdimple->ReturnFace(face);
  for (unsigned i = 0; i < edge_count; ++i, ++eptr)
  {
    AddTriangleFace(v0->m_edges[i], edges[i], v0->m_edges[(i + 1) % edge_count].Reversed());
  }

  for (unsigned i = 0; i < edge_count; ++i, ++eptr)
  {
    ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(edges[i].m_ptr);
    e->EdgeModifiedNofification();
    e->UpdateEdgeSectorCoefficientsForExperts(false);
  }

  for (unsigned i = 0; i < edge_count; ++i, ++eptr)
    ON_SUBD_EDGE_POINTER(edges[i].m_ptr)->UpdateEdgeSectorCoefficientsForExperts(false);

  for (unsigned i = 0; i < edge_count; ++i, ++eptr)
    ON_SUBD_EDGE_POINTER(v0->m_edges[i].m_ptr)->UpdateEdgeSectorCoefficientsForExperts(false);

  return v0;
}



const ON_SubDEdge* ON_SubDimple::SplitEdge(
  ON_SubDEdge* edge,
  ON_3dPoint vertex_location
  )
{
  if ( nullptr == edge )
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (nullptr == edge->m_vertex[0] || nullptr == edge->m_vertex[1] )
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (nullptr == edge->m_vertex[0]->m_edges || edge->m_vertex[0]->m_edge_count <= 0 || edge->m_vertex[0]->m_edge_capacity < edge->m_vertex[0]->m_edge_count )
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (nullptr == edge->m_vertex[1]->m_edges || edge->m_vertex[1]->m_edge_count <= 0 || edge->m_vertex[1]->m_edge_capacity < edge->m_vertex[1]->m_edge_count )
    return ON_SUBD_RETURN_ERROR(nullptr);

  if ( vertex_location.IsUnsetOrNan() )
  {
    ON_Line L;
    L.from = ON_3dPoint(edge->m_vertex[0]->m_P);
    L.to = ON_3dPoint(edge->m_vertex[1]->m_P);
    vertex_location = L.PointAt(0.5);
  }
  if ( false == vertex_location.IsValid() )
    return ON_SUBD_RETURN_ERROR(nullptr);

  if ( vertex_location == ON_3dPoint(edge->m_vertex[0]->m_P) || vertex_location == ON_3dPoint(edge->m_vertex[1]->m_P) )
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON_SubDEdgeTag edge_tag = edge->m_edge_tag;
  ON_SubDVertexTag vertex_tag;
  switch (edge->m_edge_tag)
  {
  case ON_SubDEdgeTag::Smooth:
    vertex_tag = ON_SubDVertexTag::Smooth;
    break;
  case ON_SubDEdgeTag::Crease:
    vertex_tag = ON_SubDVertexTag::Crease;
    break;
  case ON_SubDEdgeTag::SmoothX:
    vertex_tag = ON_SubDVertexTag::Smooth;
    edge_tag = ON_SubDEdgeTag::Smooth;
    break;
  default:
    return ON_SUBD_RETURN_ERROR(nullptr);
    break;
  }

  const ON_SubDEdgeSharpness sharpness0 = edge->Sharpness(false);

  ON_SubDVertex* end_vertex[2] = { const_cast<ON_SubDVertex*>(edge->m_vertex[0]), const_cast<ON_SubDVertex*>(edge->m_vertex[1]) };

  ON_SubDVertex* new_vertex = nullptr;
  ON_SubDEdge* new_edge = nullptr;  
  for (;;)
  {
    new_vertex = AllocateVertex( 0U, vertex_tag, edge->SubdivisionLevel(), static_cast<const double*>(vertex_location), 2, edge->m_face_count);
    if (nullptr == new_vertex)
     break;

    new_edge = AllocateEdge( 0U, edge_tag, edge->SubdivisionLevel(), edge->m_face_count);
    if (nullptr == new_edge)
      break;

    // change end_vertex[1] edge reference from edge to new_edge
    bool bConnectedNewEdgeToEndVertex = false;
    const ON_SubDEdgePtr old_edge_reference = ON_SubDEdgePtr::Create(edge,1);
    for (unsigned short vei = 0; vei < end_vertex[1]->m_edge_count; vei++)
    {
      if (old_edge_reference.m_ptr == end_vertex[1]->m_edges[vei].m_ptr)
      {
        // change end_vertex[1]->m_edges[vei] reference
        // from "edge" to "new_edge".
        bConnectedNewEdgeToEndVertex = true;
        end_vertex[1]->m_edges[vei] = ON_SubDEdgePtr::Create(new_edge,1);
        break;
      }
    }

    if (false == bConnectedNewEdgeToEndVertex)
    {
      // end_vertex[1]->m_edges[] does not reference edge
      break;
    }

    // finish setting new_vertex and end_vertex[] <-> new_edge connections
    new_edge->m_vertex[0] = new_vertex;
    new_edge->m_vertex[1] = end_vertex[1];
    new_vertex->m_edges[new_vertex->m_edge_count++] = ON_SubDEdgePtr::Create(new_edge,0);

    // finish setting new_vertex <-> input edge and connections
    edge->m_edge_tag = edge_tag; // changes "X" to "Smooth" if required
    edge->m_vertex[1] = new_vertex;
    new_vertex->m_edges[new_vertex->m_edge_count++] = ON_SubDEdgePtr::Create(edge,1);
       
    // add new_vertex and new_edge <-> edge->m_face[] connections.
    const ON_SubDFacePtr* fptr0 = edge->m_face2;
    ON_SubDFacePtr* fptr1 = new_edge->m_face2;
    for (unsigned short efi = 0; efi < edge->m_face_count; efi++)
    {
      if (2 == efi)
      {
        fptr0 = edge->m_facex;
        fptr1 = new_edge->m_facex;
      }

      ON_SubDFace* face = ON_SUBD_FACE_POINTER(fptr0->m_ptr);

      if (nullptr != face)
      {
        face->FaceModifiedNofification();

        // add new_vertex reference to face
        new_vertex->m_faces[new_vertex->m_face_count++] = face;

        // insert new_edge into face->m_edge[] list after "edge"
        if (GrowFaceEdgeArray(face, face->m_edge_count + 1))
        {
          if ( face->m_edge_count < 4 )
            face->m_edge4[face->m_edge_count] = ON_SubDEdgePtr::Null;
          else
            face->m_edgex[face->m_edge_count-4] = ON_SubDEdgePtr::Null;
          face->m_edge_count++;
          ON_SubDEdgePtr* face_edge = face->m_edge4;
          for (unsigned short fei = 0; fei < face->m_edge_count; fei++)
          {
            if (4 == fei)
              face_edge = face->m_edgex;
            if (edge == ON_SUBD_EDGE_POINTER(face_edge->m_ptr))
            {
              ON__UINT_PTR edir = ON_SUBD_EDGE_DIRECTION(face_edge->m_ptr);
              ON_SubDEdgePtr eptr = ON_SubDEdgePtr::Create(new_edge,edir);
              if (0 == edir)
              {
                fei++;
                face_edge++;
              }
              for (/*empty init*/; fei < face->m_edge_count; fei++)
              {
                if (4 == fei)
                  face_edge = face->m_edgex;
                const ON_SubDEdgePtr tmp = *face_edge;
                *face_edge = eptr;
                eptr = tmp;
                face_edge++;
              }
              break;
            }
            face_edge++;
          }
        }
      }

      *fptr1++ = *fptr0++;
      new_edge->m_face_count++;
    }

    // original ending vertex
    new_edge->m_sector_coefficient[1] = edge->m_sector_coefficient[1];

    // Either edge was a crease, new_edge is a crease, and sector coefficients do not apply
    // or edge was X or Smooth, edge is smooth, new_edge is smooth, new_vertex is smooth,
    // and the sector coefficients at this vertex do not apply.
    edge->m_sector_coefficient[1] = ON_SubDSectorType::IgnoredSectorCoefficient;
    new_edge->m_sector_coefficient[0] = ON_SubDSectorType::IgnoredSectorCoefficient;

    AddVertexToLevel(new_vertex);
    AddEdgeToLevel(new_edge);

    if (sharpness0.IsSharp() && edge->IsSmooth() && new_edge->IsSmooth())
    {
      // Dale Lear 2024 Feb 29 - Fix RH-80388
      const double smid = sharpness0.Average();
      const ON_SubDEdgeSharpness s0 = ON_SubDEdgeSharpness::FromInterval(sharpness0[0], smid);
      const ON_SubDEdgeSharpness s1 = ON_SubDEdgeSharpness::FromInterval(smid, sharpness0[1]);
      edge->SetSharpnessForExperts(s0);
      new_edge->SetSharpnessForExperts(s1);
    }

    end_vertex[0]->VertexModifiedNofification();
    end_vertex[1]->VertexModifiedNofification();

    // TODO
    //   Delete any levels greater than this level.
    return new_edge;
  }

  if ( nullptr != new_vertex)
    ReturnVertex(new_vertex);
  if ( nullptr != new_edge)
    ReturnEdge(new_edge);
  return ON_SUBD_RETURN_ERROR(nullptr);
}

const ON_SubDEdge* ON_SubDimple::SplitFace(
  ON_SubDFace* face,
  unsigned int fvi0,
  unsigned int fvi1
  )
{
  if ( nullptr == face || fvi0 == fvi1)
    return ON_SUBD_RETURN_ERROR(nullptr);

  const unsigned int edge_count = face->m_edge_count;
  if (edge_count < 4 || (edge_count > 4 && nullptr == face->m_edgex))
    return ON_SUBD_RETURN_ERROR(nullptr);

  if (fvi0 >= edge_count || fvi1 >= edge_count)
    return ON_SUBD_RETURN_ERROR(nullptr);

  if ((fvi0 + 1) % edge_count == fvi1 || (fvi1 + 1) % edge_count == fvi0)
    return ON_SUBD_RETURN_ERROR(nullptr);

  if (face->SubdivisionLevel() >= m_levels.UnsignedCount())
    return ON_SUBD_RETURN_ERROR(nullptr);
  ON_SubDLevel* level = m_levels[face->SubdivisionLevel()];
  if ( nullptr == level)
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON_SubDVertex* v[2] = { const_cast<ON_SubDVertex*>(face->Vertex(fvi0)), const_cast<ON_SubDVertex*>(face->Vertex(fvi1)) };

  if (nullptr == v[0] || v[0]->m_face_count <= 0 || nullptr == v[0]->m_faces || v[0]->m_edge_count < 2 || nullptr == v[0]->m_edges )
    return ON_SUBD_RETURN_ERROR(nullptr);

  if (nullptr == v[1] || v[1]->m_face_count <= 0 || nullptr == v[1]->m_faces || v[1]->m_edge_count < 2 || nullptr == v[1]->m_edges)
    return ON_SUBD_RETURN_ERROR(nullptr);

  if (v[0] == v[1])
    return ON_SUBD_RETURN_ERROR(nullptr);

  unsigned new_edge_count[2];
  if (fvi0 < fvi1)
  {
    new_edge_count[1] = fvi1 - fvi0 + 1;
    new_edge_count[0] = (edge_count + 2) - new_edge_count[1];
  }
  else
  {
    new_edge_count[0] = fvi0 - fvi1 + 1;
    new_edge_count[1] = (edge_count + 2) - new_edge_count[0];
  }
  // make sure each side is at least a triangle and no overflows occurred
  if (new_edge_count[0] < 3 || new_edge_count[0] >= edge_count)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (new_edge_count[1] < 3 || new_edge_count[1] >= edge_count)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (new_edge_count[0] + new_edge_count[1] != edge_count+2 )
    return ON_SUBD_RETURN_ERROR(nullptr);
  
  // make sure face topology is valid
  ON_SimpleArray< ON_SubDEdgePtr > edges(edge_count);
  ON_SubDEdgePtr* eptr = face->m_edge4;
  edges.SetCount(edge_count);
  for (unsigned int fei = 0; fei < edge_count; ++fei, ++eptr)
  {
    if (4 == fei)
      eptr = face->m_edgex;
    const ON_SubDEdge* face_e = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
    if (nullptr == face_e)
      return ON_SUBD_RETURN_ERROR(nullptr);
    if (ON_UNSET_UINT_INDEX == face_e->FaceArrayIndex(face) )
      return ON_SUBD_RETURN_ERROR(nullptr);
    const ON_SubDVertex* face_v = face_e->m_vertex[ON_SUBD_EDGE_DIRECTION(eptr->m_ptr)];
    if ( nullptr == face_v)
      return ON_SUBD_RETURN_ERROR(nullptr);
    if (ON_UNSET_UINT_INDEX == face_v->FaceArrayIndex(face) )
      return ON_SUBD_RETURN_ERROR(nullptr);
    edges[fei] = *eptr;
  }

  // create diagonal edge
  ON_SubDEdge* new_e = nullptr;
  ON_SubDFace* new_f = nullptr;
  for (;;)
  {
    if (false == m_heap.GrowVertexFaceArrayByOne(v[0]))
      break;
    if (false == m_heap.GrowVertexFaceArrayByOne(v[1]))
      break;

    new_f = AllocateFace();
    if (nullptr == new_f)
      break;
    new_f->SetSubdivisionLevel( face->SubdivisionLevel() );
    AddFaceToLevel(new_f);
    if (new_edge_count[1] > 4)
    {
      if (false == m_heap.GrowFaceEdgeArray(new_f, new_edge_count[1]))
        break;
    }

    new_e = AddEdge(
      ((v[0]->IsSmooth() || v[1]->IsSmooth()) ? ON_SubDEdgeTag::Smooth : ON_SubDEdgeTag::SmoothX),
      v[0], ON_SubDSectorType::UnsetSectorCoefficient, 
      v[1], ON_SubDSectorType::UnsetSectorCoefficient);
    if (nullptr == new_e)
      break;

    face->FaceModifiedNofification();

    v[0]->m_faces[v[0]->m_face_count++] = new_f;
    v[1]->m_faces[v[1]->m_face_count++] = new_f;

    new_e->m_face2[0] = ON_SubDFacePtr::Create(face, 0);
    new_e->m_face2[1] = ON_SubDFacePtr::Create(new_f, 1);
    new_e->m_face_count = 2;
    const ON_SubDEdgePtr new_eptr = ON_SubDEdgePtr::Create(new_e);

    eptr = face->m_edge4;
    for (unsigned int fei = 0; fei < edge_count; ++fei, ++eptr)
    {
      if (4 == fei)
        eptr = face->m_edgex;
      *eptr = ON_SubDEdgePtr::Null;
    }
    face->m_edge_count = 0;
    if (new_edge_count[0] <= 4 && nullptr != face->m_edgex)
      m_heap.ReturnFaceExtraArray(face);

    // update old face
    face->m_edge4[0] = new_eptr;
    eptr = &(face->m_edge4[1]);
    for (unsigned fei = 1; fei < new_edge_count[0]; ++fei, ++eptr)
    {
      if (4 == fei)
        eptr = face->m_edgex;
      *eptr = edges[(fvi1 + fei - 1) % edge_count];
    }
    face->m_edge_count = (unsigned short)new_edge_count[0];

    // initialize new_f
    new_f->m_edge4[0] = new_eptr.Reversed();
    eptr = &(new_f->m_edge4[1]);
    for (unsigned fei = 1; fei < new_edge_count[1]; ++fei, ++eptr)
    {
      if (4 == fei)
        eptr = new_f->m_edgex;
      *eptr = edges[(fvi0 + fei - 1) % edge_count];

      // change edge's face reference from old face to new_f.
      ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
      e->ReplaceFaceInArray(face, new_f);

      ON_SubDVertex* vtx = const_cast<ON_SubDVertex*>(eptr->RelativeVertex(0));
      if (nullptr != vtx && v[0] != vtx && v[1] != vtx)
        vtx->ReplaceFaceInArray(face, new_f);
    }
    new_f->m_edge_count = (unsigned short)new_edge_count[1];
    
    // update sector coefficients because they depend on the number of edges
    for (unsigned int vi = 0; vi < 2; vi++)
    {
      for (unsigned short evi = 0; evi < v[vi]->m_edge_count; ++evi)
      {
        ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(v[vi]->m_edges[evi].m_ptr);
        if (nullptr != edge)
          edge->UpdateEdgeSectorCoefficientsForExperts(true);
      }
    }

    // Debugging code
    const ON_SubDVertex* v0[6] = {
      face->m_edge4[0].RelativeVertex(0),face->m_edge4[0].RelativeVertex(1),
      face->m_edge4[1].RelativeVertex(0),face->m_edge4[1].RelativeVertex(1),
      face->EdgePtr(face->m_edge_count-1).RelativeVertex(0),face->EdgePtr(face->m_edge_count - 1).RelativeVertex(1),
    };
    const ON_SubDEdge* e0[3] = {
      face->m_edge4[0].Edge(),
      face->m_edge4[1].Edge(),
      face->EdgePtr(face->m_edge_count - 1).Edge()
    };
    const ON_SubDVertex* v1[6] = {
      new_f->m_edge4[0].RelativeVertex(0),new_f->m_edge4[0].RelativeVertex(1),
      new_f->m_edge4[1].RelativeVertex(0),new_f->m_edge4[1].RelativeVertex(1),
      new_f->EdgePtr(new_f->m_edge_count - 1).RelativeVertex(0),new_f->EdgePtr(new_f->m_edge_count - 1).RelativeVertex(1),
    };
    const ON_SubDEdge* e1[3] = {
      new_f->m_edge4[0].Edge(),
      new_f->m_edge4[1].Edge(),
      new_f->EdgePtr(new_f->m_edge_count - 1).Edge()
    };
    if (nullptr == v0[5] && nullptr == v1[5] && nullptr == e0[2] && nullptr == e1[2])
      return nullptr;



    return new_e;
  }

  if ( nullptr != new_f  )
   ReturnFace(new_f);

  if (nullptr != new_e)
  {
    v[0]->m_edge_count--;
    v[0]->m_edges[v[0]->m_edge_count] = ON_SubDEdgePtr::Null;
    v[1]->m_edge_count--;
    v[1]->m_edges[v[1]->m_edge_count] = ON_SubDEdgePtr::Null;
    new_e->m_vertex[0] = nullptr;
    new_e->m_vertex[1] = nullptr;
    new_e->m_face_count = 0;
    ReturnEdge(new_e);
  }

  return ON_SUBD_RETURN_ERROR(nullptr);
}



const ON_SubDEdge* ON_SubD::SplitEdge(
  ON_SubDEdge* edge,
  ON_3dPoint vertex_location
  )
{
  ON_SubDimple* subdimple = SubDimple(false);
  if ( nullptr == subdimple )
    return ON_SUBD_RETURN_ERROR(nullptr);
  return subdimple->SplitEdge(edge,vertex_location);
}

const ON_SubDEdgePtr ON_SubD::SplitEdge(
  ON_SubDEdgePtr eptr,
  ON_3dPoint vertex_location,
  unsigned new_edge_end
)
{
  if ( 0 != new_edge_end && 1 != new_edge_end)
    return ON_SubDEdgePtr::Null;
  ON_SubDEdge* e = eptr.Edge();
  if (nullptr == e)
    return ON_SubDEdgePtr::Null;
  const ON_SubDVertex* v[3] = { e->m_vertex[0],nullptr,e->m_vertex[1] };
  ON_SubDEdge* e1 = const_cast<ON_SubDEdge*>(this->SplitEdge(e, vertex_location));
  if ( nullptr == e1)
    return ON_SubDEdgePtr::Null;

  const ON__UINT_PTR eptr_dir = eptr.EdgeDirection();
  const ON_SubDEdgePtr e1ptr = ON_SubDEdgePtr::Create(e1, eptr_dir);

  if (v[0] != e->m_vertex[0] || v[2] != e1->m_vertex[1])
  {
    ON_SUBD_ERROR("Error in SplitEdge(ON_SubDEdge*,...).");
    return e1ptr;
  }

  v[1] = e->m_vertex[1];
  if ( nullptr == v[1] || v[1] != e1->m_vertex[0] || 2 != v[1]->m_edge_count)
  {
    ON_SUBD_ERROR("Error in SplitEdge(ON_SubDEdge*,...).");
    return e1ptr;
  }

  if (e->m_face_count != e1->m_face_count)
  {
    ON_SUBD_ERROR("Error in SplitEdge(ON_SubDEdge*,...).");
    return e1ptr;
  }

  const unsigned v0edex = v[0]->EdgeArrayIndex(e);
  const unsigned v2edex = v[2]->EdgeArrayIndex(e1);
  if (v0edex >= v[0]->EdgeCount() || v2edex >= v[2]->EdgeCount())
  {
    ON_SUBD_ERROR("Error in SplitEdge(ON_SubDEdge*,...).");
    return e1ptr;
  }

  if (0 == eptr_dir && 1 == new_edge_end)
  {
    return e1ptr;
  }

  if (1 == eptr_dir && 0 == new_edge_end)
  {
    return e1ptr;
  }

  // swap e and e1 topology connections to put the "new edge" where the caller wants it.

  for (unsigned short efi = 0; efi < e->m_face_count; ++efi)
  {
    ON_SubDFace* f = const_cast<ON_SubDFace*>(e->Face(efi));
    if (nullptr == f)
      continue;
    const unsigned edge_count = f->EdgeCount();
    const unsigned fei = f->EdgeArrayIndex(e);
    const unsigned fe1i = f->EdgeArrayIndex(e1);
    if (fei >= edge_count || fe1i >= edge_count)
      continue;

    const ON_SubDEdgePtr feptr = ON_SubDEdgePtr::Create(e1, f->EdgePtr(fei).EdgeDirection()); // e1 is correct - we are swapping
    if (fei < 4)
      f->m_edge4[fei] = feptr;
    else
      f->m_edgex[fei - 4] = feptr;

    const ON_SubDEdgePtr fe1ptr = ON_SubDEdgePtr::Create(e, f->EdgePtr(fe1i).EdgeDirection()); // e is correct - we are swapping
    if (fe1i < 4)
      f->m_edge4[fe1i] = fe1ptr;
    else
      f->m_edgex[fe1i - 4] = fe1ptr;
  }

  const ON_SubDEdgePtr new_v0eptr = ON_SubDEdgePtr::Create(e1, v[0]->EdgePtr(v0edex).EdgeDirection());
  const ON_SubDEdgePtr new_v2eptr = ON_SubDEdgePtr::Create(e, v[2]->EdgePtr(v2edex).EdgeDirection());
  v[0]->m_edges[v0edex] = new_v0eptr;
  v[1]->m_edges[0] = new_v0eptr.Reversed();
  v[1]->m_edges[1] = new_v2eptr.Reversed();
  v[2]->m_edges[v2edex] = new_v2eptr;
  e1->m_vertex[0] = v[0];
  e1->m_vertex[1] = v[1];
  e->m_vertex[0] = v[1];
  e->m_vertex[1] = v[2];


  return e1ptr;
}

const ON_SubDEdge* ON_SubDimple::SpinEdge(ON_SubDEdge* edge,
                                          bool spin_clockwise) {
  if (edge == nullptr || !edge->HasInteriorEdgeTopology(true) ||
      edge->SubdivisionLevel() >= m_levels.UnsignedCount() ||
      m_levels.UnsignedCount() < 1) {
    return ON_SUBD_RETURN_ERROR(nullptr);
  }

  unsigned int level0_index{edge->SubdivisionLevel()};

  if (m_levels[level0_index] == nullptr) return ON_SUBD_RETURN_ERROR(nullptr);

  ClearHigherSubdivisionLevels(level0_index + 1);
  if (level0_index + 1 != m_levels.UnsignedCount()) {
    return ON_SUBD_RETURN_ERROR(nullptr);
  }

  m_active_level = m_levels[level0_index];
  if (m_active_level == nullptr || m_active_level->m_face_count == 0) {
    return ON_SUBD_RETURN_ERROR(nullptr);
  }

  ON_SubDVertex* vertices[2]{const_cast<ON_SubDVertex*>(edge->Vertex(0)),
                             const_cast<ON_SubDVertex*>(edge->Vertex(1))};

  const bool swap_faces{(edge->FaceDirection(0) == 1) != spin_clockwise};
  ON_SubDFace* faces[2]{
      const_cast<ON_SubDFace*>(swap_faces ? edge->Face(1) : edge->Face(0)),
      const_cast<ON_SubDFace*>(swap_faces ? edge->Face(0) : edge->Face(1))};

  const unsigned face_edge_indices[2]{faces[0]->EdgeArrayIndex(edge),
                                      faces[1]->EdgeArrayIndex(edge)};
  if (face_edge_indices[0] == ON_UNSET_UINT_INDEX ||
      face_edge_indices[1] == ON_UNSET_UINT_INDEX) {
    return ON_SUBD_RETURN_ERROR(nullptr);
  }
  ON__UINT_PTR new_directions[2]{faces[0]->EdgeDirection(face_edge_indices[0]),
                                 faces[1]->EdgeDirection(face_edge_indices[1])};

  const ON_SubDEdgePtr adjacent_edges[2]{
      spin_clockwise
          ? faces[1]->VertexEdgePair(vertices[0]).First().EdgePtr()
          : faces[1]->VertexEdgePair(vertices[0]).Second().EdgePtr(),
      spin_clockwise
          ? faces[0]->VertexEdgePair(vertices[1]).First().EdgePtr()
          : faces[0]->VertexEdgePair(vertices[1]).Second().EdgePtr()};

  ON_SubDVertex* new_vertices[2]{
      const_cast<ON_SubDVertex*>(
          adjacent_edges[0].RelativeVertex(spin_clockwise ? 0 : 1)),
      const_cast<ON_SubDVertex*>(
          adjacent_edges[1].RelativeVertex(spin_clockwise ? 0 : 1))};
  if (new_vertices[0] == nullptr || new_vertices[1] == nullptr) {
    return ON_SUBD_RETURN_ERROR(nullptr);
  }

  ON_SubDEdge* new_edge{edge};
  // Also calls vertices[i].VertexNotifiedModification()
  new_edge->EdgeModifiedNofification();

  for (unsigned int i = 0; i < 2; i++) {
    ON_SubDVertex* v = new_vertices[i];
    edge->m_vertex[i] = v;

    bool rc{true};
    rc = rc && vertices[i]->RemoveEdgeFromArray(edge);
    if (!m_heap.GrowVertexEdgeArrayByOne(v)) {
      v->m_status.SetDamagedState(true);
      return ON_SUBD_RETURN_ERROR(nullptr);
    }
    v->m_edges[v->m_edge_count++] =
        ON_SubDEdgePtr::Create(new_edge, (ON__UINT_PTR)i);

    rc = rc && vertices[i]->RemoveFaceFromArray(faces[1 - i]);
    if (!m_heap.GrowVertexFaceArrayByOne(v)) {
      v->m_status.SetDamagedState(true);
      return ON_SUBD_RETURN_ERROR(nullptr);
    }
    v->m_faces[v->m_face_count++] = faces[i];
    v->VertexModifiedNofification();

    rc = rc &&
         (adjacent_edges[i].Edge()->ReplaceFaceInArray(faces[1 - i], faces[i]) <
          adjacent_edges[i].EdgeFaceCount());

    rc = rc && faces[i]->ReplaceEdgeInArray(0, edge, adjacent_edges[i]);
    rc = rc && faces[i]->ReplaceEdgeInArray(
                   0, adjacent_edges[1 - i].Edge(),
                   ON_SubDEdgePtr::Create(new_edge, new_directions[i]));
    faces[i]->FaceModifiedNofification();
    if (!rc) return ON_SUBD_RETURN_ERROR(nullptr);
  }
  if (new_edge == nullptr) return ON_SUBD_RETURN_ERROR(nullptr);

  if (nullptr != m_active_level) {
    m_active_level->UpdateAllTagsAndSectorCoefficients(true);
  }

  ChangeGeometryContentSerialNumber(false);

  return new_edge;
}

const ON_SubDEdge* ON_SubD::SpinEdge(ON_SubDEdge* edge, bool spin_clockwise) {
  ON_SubDimple* subdimple = SubDimple(false);
  if (nullptr == subdimple) return ON_SUBD_RETURN_ERROR(nullptr);
  return subdimple->SpinEdge(edge, spin_clockwise);
}

const ON_SubDEdgePtr ON_SubD::SpinEdge(ON_SubDEdgePtr eptr,
                                       bool spin_clockwise) {
  ON_SubDEdge* edge = eptr.Edge();
  if (nullptr == edge) return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  const ON_SubDEdge* new_edge{SpinEdge(edge, spin_clockwise)};
  if (nullptr == new_edge) return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  return ON_SubDEdgePtr::Create(new_edge, eptr.EdgeDirection());
}

const ON_SubDEdge * ON_SubD::SplitFace(
  ON_SubDFace * face, 
  const ON_SubDVertex * v0,
  const ON_SubDVertex * v1
)
{
  if (nullptr == face || nullptr == v0 || nullptr == v1 || v0 == v1)
    return ON_SUBD_RETURN_ERROR(nullptr);
  unsigned int fvi0 = ON_UNSET_UINT_INDEX;
  unsigned int fvi1 = ON_UNSET_UINT_INDEX;
  ON_SubDEdgePtr* eptr = face->m_edge4;
  for (unsigned short fei = 0; fei < face->m_edge_count; ++fei, ++eptr)
  {
    if (4 == fei)
    {
      eptr = face->m_edgex;
      if (nullptr == eptr)
        return ON_SUBD_RETURN_ERROR(nullptr);
    }
    const ON_SubDVertex* v = eptr->RelativeVertex(0);
    if (v == v0)
    {
      if (ON_UNSET_UINT_INDEX != fvi0)
        return ON_SUBD_RETURN_ERROR(nullptr);
      fvi0 = fei;
    }
    else if (v == v1)
    {
      if (ON_UNSET_UINT_INDEX != fvi1)
        return ON_SUBD_RETURN_ERROR(nullptr);
      fvi1 = fei;
    }
  }
  return (ON_UNSET_UINT_INDEX != fvi0 && ON_UNSET_UINT_INDEX != fvi1)
    ? SplitFace(face, fvi0, fvi1)
    : ON_SUBD_RETURN_ERROR(nullptr);
}

const ON_SubDEdge* ON_SubD::SplitFace(
  ON_SubDFace* face,
  unsigned int fvi0,
  unsigned int fvi1
  )
{
  ON_SubDimple* subdimple = SubDimple(false);
  if ( 0 == subdimple )
    return ON_SUBD_RETURN_ERROR(nullptr);
  return subdimple->SplitFace(face,fvi0,fvi1);
}

static void Internal_SplitFaceSwapFacePtr(
  ON_SubDFace* f,
  ON__UINT_PTR pairA[2],
  ON__UINT_PTR pairB[2]
  )
{
  if (nullptr == f)
    return;

  if (pairA[0] == pairB[0] || pairA[1] == pairB[0] || pairA[0] == pairB[1] || pairA[1] == pairB[1])
  {
    ON_SUBD_ERROR("pairA[] and pairB[] must be disjoint sets of values.");
    return;
  }

  ON_SubDEdgePtr* feptr = f->m_edge4;
  for (unsigned short fei = 0; fei < f->m_edge_count; ++fei, ++feptr)
  {
    if (4 == fei)
    {
      feptr = f->m_edgex;
      if (nullptr == feptr)
        break;
    }

    ON_SubDEdge* fe = ON_SUBD_EDGE_POINTER(feptr->m_ptr);
    if (nullptr == fe)
      continue;

    ON_SubDFacePtr* efptr = fe->m_face2;
    for (unsigned short efi = 0; efi < fe->m_face_count; ++efi, ++efptr)
    {
      if (2 == efi)
      {
        efptr = fe->m_facex;
        if (nullptr == efptr)
          break;
      }
      const ON__UINT_PTR x = (efptr->m_ptr & ON_SUBD_COMPONENT_POINTER_MASK);
      const ON__UINT_PTR d = (efptr->m_ptr & ON_SUBD_COMPONENT_DIRECTION_MASK);
      if (x == pairA[0])
        efptr->m_ptr = (pairA[1] | d);
      else if (x == pairB[0])
        efptr->m_ptr = (pairB[1] | d);
    }


    ON_SubDVertex* v = const_cast<ON_SubDVertex*>(feptr->RelativeVertex(0));
    if (nullptr != v && nullptr != v->m_faces)
    {
      for (unsigned short vfi = 0; vfi < v->m_face_count; ++vfi)
      {
        const ON__UINT_PTR x = (ON__UINT_PTR)v->m_faces[vfi];
        if (x == pairA[0])
          v->m_faces[vfi] = (ON_SubDFace*)pairA[1];
        else if (x == pairB[0])
          v->m_faces[vfi] = (ON_SubDFace*)pairB[1];
      }
    }
  }
}

static bool Internal_ValidateFaceTopology(
  const ON_SubDFace* f
)
{
  if (nullptr == f)
    return false;

  if (f->m_edge_count < 3 || 0 == f->m_id)
    return ON_SUBD_RETURN_ERROR(false);

  const ON_SubDVertex* firstv = nullptr;
  const ON_SubDVertex* ev[2] = {};
  bool rc = true;
  unsigned short fdex;
  const ON_SubDEdgePtr* feptr = f->m_edge4;
  for (unsigned short fei = 0; fei < f->m_edge_count; ++fei, ++feptr)
  {
    if (4 == fei)
    {
      feptr = f->m_edgex;
      if (nullptr == feptr)
      {
        ON_SUBD_ERROR("face m_edge_count > 4 and m_edgex is nullptr.");
        rc = false;
        break;
      }
    }

    ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(feptr->m_ptr);
    if (nullptr == e || 0 == e->m_id)
    {
      ON_SUBD_ERROR("null edge in face.");
      rc = false;
      continue;
    }

    if (e != f->Edge(fei))
    {
      ON_SUBD_ERROR("face->Edge(fei) != e");
      rc = false;
    }

    for (unsigned short k = fei + 1; k < f->m_edge_count; ++k)
    {
      if (e == f->Edge(k))
      {
        ON_SUBD_ERROR("face references e 2 or more times.");
        rc = false;
      }
    }

    const ON__UINT_PTR fedir = ON_SUBD_FACE_DIRECTION(feptr->m_ptr);

    if (0 == fei)
    {
      firstv = e->m_vertex[fedir];
      ev[1] = firstv;
    }

    if (ev[1] != e->m_vertex[fedir])
    {
      ON_SUBD_ERROR("consecutive edge pointers do not have the same vertex at the end/start.");
      rc = false;
    }

    ev[0] = e->m_vertex[fedir];
    ev[1] = e->m_vertex[1-fedir];
    if (nullptr == ev[0] || nullptr == ev[1])
    {
      ON_SUBD_ERROR("edge has null vertex pointers.");
      rc = false;
    }
    else if (ev[0] == ev[1])
    {
      ON_SUBD_ERROR("edge begins and ends at the same vertex.");
      rc = false;
    }

    fdex = e->m_face_count;
    const ON_SubDFacePtr* efptr = e->m_face2;
    for (unsigned short efi = 0; efi < e->m_face_count; ++efi, ++efptr)
    {
      if (2 == efi)
      {
        efptr = e->m_facex;
        if (nullptr == efptr)
        {
          ON_SUBD_ERROR("null edge in face.");
          rc = false;
          break;
        }
      }

      const ON_SubDFace* ef = ON_SUBD_FACE_POINTER(efptr->m_ptr);
      if (f == ef)
      {
        if (fdex < e->m_face_count)
        {
          ON_SUBD_ERROR("ef references face 2 or more times.");
          rc = false;
          break;
        }
        fdex = efi;
        ON__UINT_PTR efdir = ON_SUBD_FACE_DIRECTION(efptr->m_ptr);
        if (efdir != fedir)
        {
          ON_SUBD_ERROR("face and edge have inconsistent direction settings.");
          rc = false;
          break;
        }
      }
    }
    if (fdex >= e->m_face_count)
    {
      ON_SUBD_ERROR("The face references and edge that does not reference the face.");
      rc = false;
    }

    const ON_SubDVertex* v = ev[0];
    if (nullptr != v )
    {
      if (v != f->Vertex(fei))
      {
        ON_SUBD_ERROR("face->Vertex(fei) != v");
        rc = false;
      }

      fdex = v->m_face_count;
      for (unsigned short vfi = 0; vfi < v->m_face_count; ++vfi)
      {
        const ON_SubDFace* vf = v->m_faces[vfi];
        if (f == vf)
        {
          if (fdex < v->m_face_count)
          {
            ON_SUBD_ERROR("ef references face 2 or more times.");
            rc = false;
            break;
          }
          fdex = vfi;
        }
      }
      if (fdex >= v->m_face_count)
      {
        ON_SUBD_ERROR("The face references a vertex that does not reference the face.");
        rc = false;
      }

      for (unsigned short k = fei + 1; k < f->m_edge_count; ++k)
      {
        if (v == f->Vertex(k))
        {
          ON_SUBD_ERROR("face references v 2 or more times.");
          rc = false;
        }
      }
    }
  }

  if (firstv != ev[1])
  {
    ON_SUBD_ERROR("The vertices at the end ofthe final edge and start of the initial edges are different.");
    rc = false;
  }

  return rc;
}

const ON_SubDEdgePtr ON_SubD::SplitFace(
  class ON_SubDFace* face,
  unsigned int fvi0,
  unsigned int fvi1,
  unsigned new_face_side
)
{
  if (new_face_side != 0 && new_face_side != 1)
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgePtr::Null);
  face->ClearSavedSubdivisionPoints(true);
  ON_SubDEdge* e = const_cast<ON_SubDEdge*>(this->SplitFace(face, fvi0, fvi1));
  if (nullptr == e)
    return ON_SubDEdgePtr::Null;

  const ON_SubDEdgePtr eptr = ON_SubDEdgePtr::Create(e, 0);

  ON_SubDFace* f2[2] = { const_cast<ON_SubDFace*>(eptr.RelativeFace(0)), const_cast<ON_SubDFace*>(eptr.RelativeFace(1)) };
  if (nullptr == f2[0] || nullptr == f2[1] || f2[0] == f2[1])
    return ON_SUBD_RETURN_ERROR(eptr);
  if (face != f2[0] && face != f2[1])
    return ON_SUBD_RETURN_ERROR(eptr);

  if ( face == f2[new_face_side])
  {

    // swap faces

    // markA and markB need to be different, must be values no valid heap pointer will
    // ever have, and need to be chosen so that debug runtime pointer checking code will not
    // throw exceptions. Values like 1 and 2 would work just fine except debug runtime
    // pointer checking code is mindlessly diligent. the addresses of marking_faces[0]
    // and marking_faces[1] "tricks" the debug runtime pointer checking code and
    // are values no valid app heap will ever have (they point to stack
    // used by this call).
    const ON_SubDFace marking_faces[2] = {};
    const ON__UINT_PTR markA = (ON__UINT_PTR)(&marking_faces[0]);
    const ON__UINT_PTR markB = (ON__UINT_PTR)(&marking_faces[1]);

    // The mark first, then change approach must be used because f2[0] and f2[1]
    // have multiple vertex and edge references and we must avoid swapping twice.

    // First change face references f2[0] to markA and f2[1] to markB.
    ON__UINT_PTR pairA[2] = { (ON__UINT_PTR)f2[0], markA };
    ON__UINT_PTR pairB[2] = { (ON__UINT_PTR)f2[1], markB };
    for (unsigned fdex = 0; fdex < 2; ++fdex)
      Internal_SplitFaceSwapFacePtr(f2[fdex], pairA, pairB);

    // ... then change markA to f2[1] and markB to f2[0].
    pairA[0] = markA;  pairA[1] = (ON__UINT_PTR)f2[1];
    pairB[0] = markB;  pairB[1] = (ON__UINT_PTR)f2[0];
    for (unsigned fdex = 0; fdex < 2; ++fdex)
      Internal_SplitFaceSwapFacePtr(f2[fdex], pairA, pairB);

    // At this point, all the vertex and edge references to f2[0] and f2[1] have been swapped.    

    // All that is left is to wwap edge references on f2[0] and f2[1].
    const unsigned short edge_count[2] = { f2[1]->m_edge_count, f2[0]->m_edge_count };
    const unsigned short edgex_capacity[2] = { f2[1]->m_edgex_capacity, f2[0]->m_edgex_capacity };
    ON_SubDEdgePtr edge4[2][4] = {
      {f2[1]->m_edge4[0],f2[1]->m_edge4[1],f2[1]->m_edge4[2],f2[1]->m_edge4[3]},
      {f2[0]->m_edge4[0],f2[0]->m_edge4[1],f2[0]->m_edge4[2],f2[0]->m_edge4[3]}
    };
    ON_SubDEdgePtr* edgex[2] = { f2[1]->m_edgex, f2[0]->m_edgex };
    for (unsigned i = 0; i < 2; ++i)
    {
      f2[i]->m_edge_count = edge_count[i];
      f2[i]->m_edgex_capacity = edgex_capacity[i];
      f2[i]->m_edge4[0] = edge4[i][0];
      f2[i]->m_edge4[1] = edge4[i][1];
      f2[i]->m_edge4[2] = edge4[i][2];
      f2[i]->m_edge4[3] = edge4[i][3];
      f2[i]->m_edgex = edgex[i];
    }

    //// The Internal_SplitFaceSwapFacePtr() calls above have switched the
    //// ON_SubDFace pointer values in e->m_face2[]. Because the faces
    //// are switching sides, we need to swap the directions in e->m_face2[].
    //// 
    //e->m_face2[0] = e->m_face2[0].Reversed();
    //e->m_face2[1] = e->m_face2[1].Reversed();
  }


  if (2 == e->m_face_count && face == e->m_face2[new_face_side].Face())
  {
    // Adjust the e->m_face2[] so it jibes with the relative face values exactly.
    ON_SubDFacePtr tmp = e->m_face2[0];
    e->m_face2[0] = e->m_face2[1];
    e->m_face2[1] = tmp;
  }

  if (false == Internal_ValidateFaceTopology(f2[0])
    || false == Internal_ValidateFaceTopology(f2[1])
    || f2[0] == f2[1]
    )
  {
    ON_SUBD_ERROR("Invalid faces.");
  }


  return eptr; // new face is on the requested side
}

const ON_SubDEdgePtr ON_SubD::SplitFace(
  class ON_SubDFace* face,
  const class ON_SubDVertex* v0,
  const class ON_SubDVertex* v1,
  unsigned new_face_side
)
{
  if (nullptr == face)
    return ON_SubDEdgePtr::Null;
  return this->SplitFace(face, face->VertexIndex(v0), face->VertexIndex(v1), new_face_side);
}

void ON_SubD::MarkAggregateComponentStatusAsNotCurrent() const
{
  const ON_SubDLevel* level = ActiveLevelConstPointer();
  if ( level )
    level->MarkAggregateComponentStatusAsNotCurrent();
}

unsigned int ON_SubDLevel::ClearStates(
  ON_ComponentStatus states_to_clear
  ) const
{
  unsigned int rc = 0;
  m_aggregates.m_aggregate_status.ClearAggregateStatus(states_to_clear);
  for (const ON_SubDVertex* vertex = m_vertex[0]; nullptr != vertex; vertex = vertex->m_next_vertex)
    rc += vertex->m_status.ClearStates(states_to_clear);
  for (const ON_SubDEdge* edge = m_edge[0]; nullptr != edge; edge = edge->m_next_edge)
    rc += edge->m_status.ClearStates(states_to_clear);
  for (const ON_SubDFace* face = m_face[0]; nullptr != face; face = face->m_next_face)
    rc += face->m_status.ClearStates(states_to_clear);
  return rc;
}

unsigned int ON_SubDLevel::ClearRuntimeMarks(
  bool bClearVertexMarks,
  bool bClearEdgeMarks,
  bool bClearFaceMarks
) const
{
  unsigned int rc = 0;
  if (bClearVertexMarks)
  {
    for (const ON_SubDVertex* vertex = m_vertex[0]; nullptr != vertex; vertex = vertex->m_next_vertex)
    {
      if (vertex->m_status.ClearRuntimeMark())
        ++rc;
    }
  }
  if (bClearEdgeMarks)
  {
    for (const ON_SubDEdge* edge = m_edge[0]; nullptr != edge; edge = edge->m_next_edge)
    {
      if (edge->m_status.ClearRuntimeMark())
        ++rc;
    }
  }
  if (bClearFaceMarks)
  {
    for (const ON_SubDFace* face = m_face[0]; nullptr != face; face = face->m_next_face)
    {
      if (face->m_status.ClearRuntimeMark())
        ++rc;
    }
  }
  return rc;
}

unsigned int ON_SubD::ClearComponentStates(
  ON_ComponentStatus states_to_clear
  ) const
{
  const ON_SubDLevel* level = ActiveLevelConstPointer();
  if ( level )
    return level->ClearStates(states_to_clear);
  return ON_SUBD_RETURN_ERROR(0);
}

ON_AggregateComponentStatus ON_SubD::AggregateComponentStatus() const
{  
  return ActiveLevel().AggregateComponentStatus();
}

unsigned int ON_SubDLevel::GetComponentsWithSetStates(
  ON_ComponentStatus states_filter,
  bool bAllEqualStates,
  ON_SimpleArray< ON_SubDComponentPtr >& components_with_set_states
  ) const
{
  components_with_set_states.SetCount(0);
  if (states_filter.IsClear())
    return 0;

  const ON_AggregateComponentStatusEx acs = AggregateComponentStatus();

  ON_ComponentStatus as = acs.AggregateStatus();
  if (bAllEqualStates)
  {
    if ( false == as.AllEqualStates(states_filter, states_filter) )
      return 0;
  }
  else
  {
    if ( false == as.SomeEqualStates(states_filter, states_filter) )
      return 0;
  }

  unsigned int c = 0;
  if ( states_filter.IsSelected() && c < m_aggregates.m_aggregate_status.SelectedCount() )
    c = m_aggregates.m_aggregate_status.SelectedCount();
  if ( states_filter.IsHighlighted() && c < m_aggregates.m_aggregate_status.HighlightedCount() )
    c = m_aggregates.m_aggregate_status.HighlightedCount();
  if ( states_filter.IsHidden() && c < m_aggregates.m_aggregate_status.HiddenCount() )
    c = m_aggregates.m_aggregate_status.HiddenCount();
  if ( states_filter.IsLocked() && c < m_aggregates.m_aggregate_status.LockedCount() )
    c = m_aggregates.m_aggregate_status.LockedCount();
  if ( states_filter.IsDamaged() && c < m_aggregates.m_aggregate_status.DamagedCount() )
    c = m_aggregates.m_aggregate_status.DamagedCount();
  if ( states_filter.IsSelected() && c < m_aggregates.m_aggregate_status.SelectedCount() )
    c = m_aggregates.m_aggregate_status.SelectedCount();
  components_with_set_states.Reserve(c);

  if (bAllEqualStates)
  {
    for (const ON_SubDVertex* vertex = m_vertex[0]; nullptr != vertex; vertex = vertex->m_next_vertex)
    {
      if (vertex->m_status.AllEqualStates(states_filter, states_filter))
        components_with_set_states.Append(ON_SubDComponentPtr::Create(vertex));
    }
    for (const ON_SubDEdge* edge = m_edge[0]; nullptr != edge; edge = edge->m_next_edge)
    {
      if (edge->m_status.AllEqualStates(states_filter, states_filter))
        components_with_set_states.Append(ON_SubDComponentPtr::Create(edge));
    }
    for (const ON_SubDFace* face = m_face[0]; nullptr != face; face = face->m_next_face)
    {
      if (face->m_status.AllEqualStates(states_filter, states_filter))
        components_with_set_states.Append(ON_SubDComponentPtr::Create(face));
    }
  }
  else
  {
    for (const ON_SubDVertex* vertex = m_vertex[0]; nullptr != vertex; vertex = vertex->m_next_vertex)
    {
      if (vertex->m_status.SomeEqualStates(states_filter, states_filter))
        components_with_set_states.Append(ON_SubDComponentPtr::Create(vertex));
    }
    for (const ON_SubDEdge* edge = m_edge[0]; nullptr != edge; edge = edge->m_next_edge)
    {
      if (edge->m_status.SomeEqualStates(states_filter, states_filter))
        components_with_set_states.Append(ON_SubDComponentPtr::Create(edge));
    }
    for (const ON_SubDFace* face = m_face[0]; nullptr != face; face = face->m_next_face)
    {
      if (face->m_status.SomeEqualStates(states_filter, states_filter))
        components_with_set_states.Append(ON_SubDComponentPtr::Create(face));
    }
  }

  return components_with_set_states.UnsignedCount();
}


unsigned int ON_SubD::GetComponentsWithSetStates(
  ON_ComponentStatus states_filter,
  bool bAllEqualStates,
  ON_SimpleArray< ON_SubDComponentPtr >& components_with_set_states
  ) const
{
  return ActiveLevel().GetComponentsWithSetStates(
    states_filter,
    bAllEqualStates,
    components_with_set_states
    );
}


unsigned int ON_SubD::GetComponentsWithSetStates(
  ON_ComponentStatus states_filter,
  bool bAllEqualStates,
  ON_SimpleArray< ON_COMPONENT_INDEX >& components_with_set_states
  ) const
{
  components_with_set_states.SetCount(0);
  ON_SimpleArray< ON_SubDComponentPtr > cptr;
  GetComponentsWithSetStates(
    states_filter,
    bAllEqualStates,
    cptr
    );
  unsigned int count = cptr.UnsignedCount();
  if (count > 0)
  {
    components_with_set_states.Reserve(count);
    components_with_set_states.SetCount(count);
    const ON_SubDComponentPtr* cp = cptr.Array();
    ON_COMPONENT_INDEX* ci = components_with_set_states.Array();
    for ( const ON_SubDComponentPtr* cp1 = cp+count; cp < cp1; cp++ )
      *ci++ = cp->ComponentIndex();
  }
  return count;
}

unsigned int ON_SubDLevel::SetStates(
  ON_SubDComponentPtr component_ptr,
  ON_ComponentStatus states_to_set
  ) const
{
  if (0 != component_ptr.SetStates(states_to_set))
  {
    m_aggregates.m_aggregate_status.MarkAsNotCurrent();
    return 1;
  }
  return 0;
}

unsigned int ON_SubDLevel::ClearStates(
  ON_SubDComponentPtr component_ptr,
  ON_ComponentStatus states_to_clear
  ) const
{
  if (0 != component_ptr.ClearStates(states_to_clear))
  {
    m_aggregates.m_aggregate_status.MarkAsNotCurrent();
    return 1;
  }
  return 0;
}

unsigned int ON_SubDLevel::SetStatus(
  ON_SubDComponentPtr component_ptr,
  ON_ComponentStatus status_to_copy
  ) const
{
  if (0 != component_ptr.SetStatus(status_to_copy))
  {
    m_aggregates.m_aggregate_status.MarkAsNotCurrent();
    return 1;
  }
  return 0;
}

unsigned int ON_SubD::SetComponentStates(
  ON_COMPONENT_INDEX component_index,
  ON_ComponentStatus states_to_set
  ) const
{
  return SetComponentStates(ComponentPtrFromComponentIndex(component_index),states_to_set);
}

unsigned int ON_SubD::SetComponentStates(
  ON_SubDComponentPtr component_ptr,
  ON_ComponentStatus states_to_set
  ) const
{
  const ON_SubDLevel* level = ActiveLevelConstPointer();
  if ( nullptr != level )
    return level->SetStates(component_ptr,states_to_set);
  return ON_SUBD_RETURN_ERROR(0);
}

unsigned int ON_SubD::ClearComponentStates(
  ON_COMPONENT_INDEX component_index,
  ON_ComponentStatus states_to_clear
  ) const
{
  return ClearComponentStates(ComponentPtrFromComponentIndex(component_index),states_to_clear);
}

unsigned int ON_SubD::ClearComponentStates(
  ON_SubDComponentPtr component_ptr,
  ON_ComponentStatus states_to_clear
  ) const
{
  const ON_SubDLevel* level = ActiveLevelConstPointer();
  if ( nullptr != level )
    return level->ClearStates(component_ptr,states_to_clear);
  return ON_SUBD_RETURN_ERROR(0);
}

unsigned int ON_SubD::SetComponentStatus(
  ON_COMPONENT_INDEX component_index,
  ON_ComponentStatus status_to_copy
  ) const
{
  return ClearComponentStates(ComponentPtrFromComponentIndex(component_index),status_to_copy);
}

unsigned int ON_SubD::SetComponentStatus(
  ON_SubDComponentPtr component_ptr,
  ON_ComponentStatus status_to_copy
  ) const
{
  const ON_SubDLevel* level = ActiveLevelConstPointer();
  if ( nullptr != level )
    return level->SetStatus(component_ptr,status_to_copy);
  return ON_SUBD_RETURN_ERROR(0);
}

void ON_SubDLevel::ClearEvaluationCache() const
{
  ClearEdgeFlags();
  ClearBoundingBox();
  m_surface_mesh = ON_SubDMesh::Empty;
  m_control_net_mesh = ON_SubDMesh::Empty;
  m_aggregates.MarkAllAsNotCurrent();

  for (const ON_SubDVertex* vertex = m_vertex[0]; nullptr != vertex; vertex = vertex->m_next_vertex)
  {
    vertex->ClearSavedSubdivisionPoints();
  }

  for (const ON_SubDEdge* edge = m_edge[0]; nullptr != edge; edge = edge->m_next_edge)
  {
    edge->ClearSavedSubdivisionPoints();
    // NO // edge->UnsetSectorCoefficients(); 
    // Leave these set - they are not "cached" values and except for corner case below
    // the are independent vertex locations.
    if ( edge->IsSmooth() )
    {
      for (unsigned evi = 0; evi < 2; evi++)
      {
        if ( false == (edge->m_sector_coefficient[evi] > 0.0 && edge->m_sector_coefficient[evi] < 1.0) )
          continue;
        const ON_SubDVertex* v = edge->m_vertex[evi];
        if (nullptr == v)
          continue;
        if (ON_SubDVertexTag::Corner != v->m_vertex_tag)
          continue;
        // corner sector coefficients depend on the subtended angle of the sector's crease boundary.
        // All other sector coefficients are independent of vertex location.
        const_cast<ON_SubDEdge* >(edge)->m_sector_coefficient[evi] = ON_SubDSectorType::Create(edge, evi).SectorCoefficient();
      }
    }
  }

  for (const ON_SubDFace* face = m_face[0]; nullptr != face; face = face->m_next_face)
  {
    face->ClearSavedSubdivisionPoints();
  }
}


bool ON_SubD::CopyEvaluationCacheForExperts(const ON_SubD& src)
{
  const ON_SubDimple* src_subdimple = src.m_subdimple_sp.get();
  ON_SubDimple* this_subdimple = m_subdimple_sp.get();
  const bool bCopied 
    = (nullptr != src_subdimple && nullptr != this_subdimple) 
    ? this_subdimple->CopyEvaluationCacheForExperts(*src_subdimple) 
    : false;
  if (bCopied)
  {
    if (this->HasFragmentTextureCoordinates())
      this_subdimple->Internal_SetFragmentTextureCoordinatesTextureSettingsHash(src_subdimple->FragmentColorsSettingsHash());
    if (this->HasFragmentColors())
      this_subdimple->Internal_SetFragmentColorsSettingsHash(src_subdimple->FragmentColorsSettingsHash());
  }
  return bCopied;
}

bool ON_SubDimple::CopyEvaluationCacheForExperts(const ON_SubDimple& src)
{
  const ON_SubDLevel* src_level = src.ActiveLevelConstPointer();
  ON_SubDLevel* this_level = this->ActiveLevelPointer();
  unsigned fragment_status = 0u;
  const bool bCopied = (nullptr != src_level && nullptr != this_level) ? this_level->CopyEvaluationCacheForExperts(this->m_heap , *src_level, src.m_heap, fragment_status) : false;
  if (0 != (1u& fragment_status))
  {
    if (2 != (1u & fragment_status))
      this->m_fragment_texture_settings_hash = src.m_fragment_texture_settings_hash;
    if (8 != (1u & fragment_status))
      this->m_fragment_colors_settings_hash = src.m_fragment_colors_settings_hash;
  }
  return bCopied;
}

bool ON_SubDLevel::CopyEvaluationCacheForExperts( ON_SubDHeap& this_heap, const ON_SubDLevel& src, const ON_SubDHeap& src_heap, unsigned& copy_status)
{
  copy_status = 0u;
  // Validate conditions for coping the cached evaluation information
  if (
    this == &src
    || m_vertex_count != src.m_vertex_count
    || m_edge_count != src.m_edge_count
    || m_face_count != src.m_face_count
    )
    return ON_SUBD_RETURN_ERROR(false);

  // The built in fragment cache always has adaptive ON_SubDDisplayParameters::DefaultDensity
  unsigned subd_display_density = ON_SubDDisplayParameters::AbsoluteDisplayDensityFromSubDFaceCount(ON_SubDDisplayParameters::DefaultDensity,m_face_count);
  const unsigned this_level_index = this->m_level_index;
  const unsigned src_level_index = src.m_level_index;

  // It is critical to use the this_vit/src_vit iterators so we got through the vertices in id order.
  // When a copy of an edited subd is made, it is frequently the case that the vertex linked lists
  // are in different order. 
  ON_SubDVertexIdIterator this_vit;
  ON_SubDVertexIdIterator src_vit;
  this_heap.InitializeVertexIdIterator(this_vit);
  src_heap.InitializeVertexIdIterator(src_vit);

  ON_SubDVertex* this_vertex;
  const ON_SubDVertex* src_vertex;
  ON_SubDEdgePtr this_veptr, src_veptr;
  ON_SubDFace* this_face;
  const ON_SubDFace* src_face;
  bool bCopyVertexCache = false;
  for (
    this_vertex = const_cast<ON_SubDVertex*>(this_vit.FirstVertexOnLevel(this_level_index)), src_vertex = src_vit.FirstVertexOnLevel(src_level_index);
    nullptr != this_vertex && nullptr != src_vertex; 
    this_vertex = const_cast<ON_SubDVertex*>(this_vit.NextVertexOnLevel(this_level_index)), src_vertex = src_vit.NextVertexOnLevel(src_level_index)
    )
  {
    if (this_vertex->m_id != src_vertex->m_id)
      return ON_SUBD_RETURN_ERROR(false);
    if (this_vertex->m_edge_count != src_vertex->m_edge_count)
      return ON_SUBD_RETURN_ERROR(false);
    if (this_vertex->m_face_count != src_vertex->m_face_count)
      return ON_SUBD_RETURN_ERROR(false);
    if (this_vertex->m_vertex_tag != src_vertex->m_vertex_tag)
      return ON_SUBD_RETURN_ERROR(false);
    if (false == (this_vertex->ControlNetPoint() == src_vertex->ControlNetPoint()))
      return ON_SUBD_RETURN_ERROR(false);
    if (this_vertex->SavedSubdivisionPointIsSet() && false == (this_vertex->SubdivisionPoint() == src_vertex->SubdivisionPoint()))
      return ON_SUBD_RETURN_ERROR(false);
    if (this_vertex->SavedSubdivisionPointIsSet() && this_vertex->SurfacePointIsSet())
      continue;
    if (false == src_vertex->SavedSubdivisionPointIsSet())
      continue;
    bCopyVertexCache = true;
    for (unsigned short vei = 0; vei < this_vertex->m_edge_count; ++vei)
    {
      this_veptr = this_vertex->m_edges[vei];
      src_veptr = src_vertex->m_edges[vei];
      if ( this_veptr.EdgeId() != src_veptr.EdgeId())
        return ON_SUBD_RETURN_ERROR(false);
      if (ON_SUBD_EDGE_DIRECTION(this_veptr.m_ptr) != ON_SUBD_EDGE_DIRECTION(src_veptr.m_ptr))
        return ON_SUBD_RETURN_ERROR(false);
    }
    for (unsigned short vfi = 0; vfi < this_vertex->m_face_count; ++vfi)
    {
      this_face = const_cast<ON_SubDFace*>(this_vertex->m_faces[vfi]);
      src_face = src_vertex->m_faces[vfi];
      if (nullptr == this_face || nullptr == src_face || this_face->m_id != src_face->m_id)
        return ON_SUBD_RETURN_ERROR(false);
    }
  }
  if (nullptr != this_vertex || nullptr != src_vertex)
    return ON_SUBD_RETURN_ERROR(false);

  // It is critical to use the this_eit/src_eit iterators so we got through the edges in id order.
  // When a copy of an edited subd is made, it is frequently the case that the edge linked lists
  // are in different order. 
  ON_SubDEdgeIdIterator this_eit;
  ON_SubDEdgeIdIterator src_eit;
  this_heap.InitializeEdgeIdIterator(this_eit);
  src_heap.InitializeEdgeIdIterator(src_eit);

  ON_SubDEdge* this_edge;
  const ON_SubDEdge* src_edge;
  const ON_SubDFacePtr* this_fptr;
  const ON_SubDFacePtr* src_fptr;
  bool bCopyEdgeCache = false;
  for (
    this_edge = const_cast<ON_SubDEdge*>(this_eit.FirstEdgeOnLevel(this_level_index)), src_edge = src_eit.FirstEdgeOnLevel(src_level_index);
    nullptr != this_edge && nullptr != src_edge;
    this_edge = const_cast<ON_SubDEdge*>(this_eit.NextEdgeOnLevel(this_level_index)), src_edge = src_eit.NextEdgeOnLevel(src_level_index)
    )
  {
    if (this_edge->m_id != src_edge->m_id)
      return ON_SUBD_RETURN_ERROR(false);
    if (this_edge->m_face_count != src_edge->m_face_count)
      return ON_SUBD_RETURN_ERROR(false);
    if (this_edge->m_edge_tag != src_edge->m_edge_tag)
      return ON_SUBD_RETURN_ERROR(false);
    for (int evi = 0; evi < 2; ++evi)
    {
      if (nullptr == this_edge->m_vertex[evi] || nullptr == src_edge->m_vertex[evi])
        return ON_SUBD_RETURN_ERROR(false);
      if (this_edge->m_vertex[evi]->m_id != src_edge->m_vertex[evi]->m_id)
        return ON_SUBD_RETURN_ERROR(false);
    }
    if (this_edge->SavedSubdivisionPointIsSet() && false == (this_edge->SubdivisionPoint() == src_edge->SubdivisionPoint()))
      return ON_SUBD_RETURN_ERROR(false);
    if (this_edge->SavedSubdivisionPointIsSet() && this_edge->EdgeSurfaceCurveIsSet())
      continue;
    if (false == src_edge->SavedSubdivisionPointIsSet())
      continue;
    bCopyEdgeCache = true;
    this_fptr = this_edge->m_face2;
    src_fptr = src_edge->m_face2;
    for (unsigned short efi = 0; efi < this_edge->m_face_count; ++efi, ++this_fptr, ++src_fptr)
    {
      if (2 == efi)
      {
        this_fptr = this_edge->m_facex;
        src_fptr = src_edge->m_facex;
        if (nullptr == this_fptr || nullptr == src_fptr)
          return ON_SUBD_RETURN_ERROR(false);
      }
      this_face = ON_SUBD_FACE_POINTER(this_fptr->m_ptr);
      src_face = ON_SUBD_FACE_POINTER(src_fptr->m_ptr);
      if (nullptr == this_face || nullptr == src_face || this_face->m_id != src_face->m_id )
        return ON_SUBD_RETURN_ERROR(false);
      if ( this_face->m_edge_count != src_face->m_edge_count )
        return ON_SUBD_RETURN_ERROR(false);
      if (ON_SUBD_FACE_DIRECTION(this_fptr->m_ptr) != ON_SUBD_FACE_DIRECTION(src_fptr->m_ptr))
        return ON_SUBD_RETURN_ERROR(false);
    }
  }
  if (nullptr != this_edge || nullptr != src_edge)
    return ON_SUBD_RETURN_ERROR(false);

  // It is critical to use the this_fit/src_fit iterators so we got through the faces in id order.
  // When a copy of an edited subd is made, it is frequently the case that the face linked lists
  // are in different order. 
  ON_SubDFaceIdIterator this_fit;
  ON_SubDFaceIdIterator src_fit;
  this_heap.InitializeFaceIdIterator(this_fit);
  src_heap.InitializeFaceIdIterator(src_fit);

  const ON_SubDEdgePtr* this_eptr;
  const ON_SubDEdgePtr* src_eptr;
  bool bCopyFaceCache = false;
  for (
    this_face = const_cast<ON_SubDFace*>(this_fit.FirstFaceOnLevel(this_level_index)), src_face = src_fit.FirstFaceOnLevel(src_level_index);
    nullptr != this_face && nullptr != src_face;
    this_face = const_cast<ON_SubDFace*>(this_fit.NextFaceOnLevel(this_level_index)), src_face = src_fit.NextFaceOnLevel(src_level_index)
    )
  {
    if (this_face->m_id != src_face->m_id)
      return ON_SUBD_RETURN_ERROR(false);
    if (this_face->m_edge_count != src_face->m_edge_count)
      return ON_SUBD_RETURN_ERROR(false);
    if (this_face->SavedSubdivisionPointIsSet() && false == (this_face->SubdivisionPoint() == src_face->SubdivisionPoint()) )
      return ON_SUBD_RETURN_ERROR(false);
    if (this_face->SavedSubdivisionPointIsSet() && nullptr != this_face->MeshFragments())
      continue;
    if (false == src_face->SavedSubdivisionPointIsSet())
      continue;
    bCopyFaceCache = true;
    this_eptr = this_face->m_edge4;
    src_eptr = src_face->m_edge4;
    for (unsigned short fei = 0; fei < this_face->m_edge_count; ++fei, ++this_eptr, ++src_eptr)
    {
      if (4 == fei)
      {
        this_eptr = this_face->m_edgex;
        src_eptr = src_face->m_edgex;
        if(nullptr == this_eptr || nullptr == src_eptr)
          return ON_SUBD_RETURN_ERROR(false);
      }
      if ( this_eptr->EdgeId() != src_eptr->EdgeId())
        return ON_SUBD_RETURN_ERROR(false);
      if ( ON_SUBD_EDGE_DIRECTION(this_eptr->m_ptr) != ON_SUBD_EDGE_DIRECTION(src_eptr->m_ptr))
        return ON_SUBD_RETURN_ERROR(false);
    }
  }
  if (nullptr != this_face || nullptr != src_face)
    return ON_SUBD_RETURN_ERROR(false);

  if (false == bCopyVertexCache && false == bCopyEdgeCache && false == bCopyFaceCache)
    return false;

  // this and src subd have identical geometry - copy evaluation cache

  double subdivision_point[3];
  if (bCopyVertexCache)
  {
    // It is critical to use the this_vit/src_vit iterators so we got through the vertices in id order.
    // When a copy of an edited subd is made, it is frequently the case that the vertex linked lists
    // are in different order. 
    ON_SubDSectorSurfacePoint this_limit_point;
    for (
      this_vertex = const_cast<ON_SubDVertex*>(this_vit.FirstVertexOnLevel(this_level_index)), src_vertex = src_vit.FirstVertexOnLevel(src_level_index);
      nullptr != this_vertex && nullptr != src_vertex;
      this_vertex = const_cast<ON_SubDVertex*>(this_vit.NextVertexOnLevel(this_level_index)), src_vertex = src_vit.NextVertexOnLevel(src_level_index)
      )
    {
      if (false == src_vertex->GetSavedSubdivisionPoint(subdivision_point))
        continue;
      if (false == this_vertex->SavedSubdivisionPointIsSet())
        this_vertex->SetSavedSubdivisionPoint(subdivision_point);
     
      if (false == this_vertex->SurfacePointIsSet())
      {
        for (const ON_SubDSectorSurfacePoint* src_limit_point = &src_vertex->SectorSurfacePointForExperts(); nullptr != src_limit_point; src_limit_point = src_limit_point->m_next_sector_limit_point)
        {
          this_limit_point = *src_limit_point;
          this_limit_point.m_next_sector_limit_point = (ON_SubDSectorSurfacePoint*)1;
          this_limit_point.m_sector_face = nullptr;
          if (nullptr != src_limit_point->m_sector_face)
          {
            const unsigned vfi = src_vertex->FaceArrayIndex(src_limit_point->m_sector_face);
            if (vfi >= src_vertex->m_face_count)
              break;
            this_limit_point.m_sector_face = this_vertex->m_faces[vfi];
          }
          this_vertex->SetSavedSurfacePoint(true, this_limit_point);
        }
      }
    }
  }

  if (bCopyEdgeCache)
  {    
    // It is critical to use the this_eit/src_eit iterators so we got through the edges in id order.
    // When a copy of an edited subd is made, it is frequently the case that the edge linked lists
    // are in different order. 
    ON_SimpleArray<ON_3dPoint> edge_curve_cvs(ON_SubDEdgeSurfaceCurve::MaximumControlPointCapacity);
    for (
      this_edge = const_cast<ON_SubDEdge*>(this_eit.FirstEdgeOnLevel(this_level_index)), src_edge = src_eit.FirstEdgeOnLevel(src_level_index);
      nullptr != this_edge && nullptr != src_edge;
      this_edge = const_cast<ON_SubDEdge*>(this_eit.NextEdgeOnLevel(this_level_index)), src_edge = src_eit.NextEdgeOnLevel(src_level_index)
      )
    {
      if (false == src_edge->GetSavedSubdivisionPoint(subdivision_point))
        continue;
      if (false == this_edge->SavedSubdivisionPointIsSet())
        this_edge->SetSavedSubdivisionPoint(subdivision_point);
      if ( false == this_edge->EdgeSurfaceCurveIsSet() && src_edge->EdgeSurfaceCurveIsSet( ))
        this_heap.CopyEdgeSurfaceCurve(src_edge, this_edge);
    }
  }

  if (bCopyFaceCache)
  {
    // It is critical to use the this_fit/src_fit iterators so we got through the faces in id order.
    // When a copy of an edited subd is made, it is frequently the case that the face linked lists
    // are in different order. 
    for (
      this_face = const_cast<ON_SubDFace*>(this_fit.FirstFaceOnLevel(this_level_index)), src_face = src_fit.FirstFaceOnLevel(src_level_index);
      nullptr != this_face && nullptr != src_face;
      this_face = const_cast<ON_SubDFace*>(this_fit.NextFaceOnLevel(this_level_index)), src_face = src_fit.NextFaceOnLevel(src_level_index)
      )
    {
      if (false == src_face->GetSavedSubdivisionPoint(subdivision_point))
        continue;
      if ( false == this_face->SavedSubdivisionPointIsSet())
        this_face->SetSavedSubdivisionPoint(subdivision_point);
      if (nullptr == this_face->MeshFragments() && nullptr != src_face->MeshFragments())
      {
        const ON_SubDMeshFragment* this_frag = this_heap.CopyMeshFragments(src_face, subd_display_density, this_face);
        if (nullptr != this_frag)
        {
          copy_status |= 1u;
          if (this_frag->TextureCoordinateCount() > 0)
            copy_status |= 2u;
          if (this_frag->CurvatureCount() > 0)
            copy_status |= 4u;
          if (this_frag->ColorCount() > 0)
            copy_status |= 8u;
        }
      }
    }
  }

  return true;
}

unsigned int ON_SubD::ComponentPtrFromComponentIndex(
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count,
  bool bIncludeVertices,
  bool bIncludeEdges,
  bool bIncludeFaces,
  ON_SimpleArray<ON_SubDComponentPtr>& cptr_list
) const
{
  if ( ci_count <= 0 )
    return 0;

  if (
    false == bIncludeVertices
    && false == bIncludeEdges
    && false == bIncludeFaces
    )
    return 0;

  if ( nullptr == ci_list )
    return ON_SUBD_RETURN_ERROR(0);

  const unsigned int count0 = cptr_list.UnsignedCount();

  cptr_list.Reserve(count0 + ci_count);

  const bool bFilter
    = false == bIncludeVertices
    || false == bIncludeEdges
    || false == bIncludeFaces;



  for (size_t i = 0; i < ci_count; i++)
  {
    const ON_COMPONENT_INDEX ci = ci_list[i];
    if (bFilter)
    {
      if (false == bIncludeVertices || ON_COMPONENT_INDEX::TYPE::subd_vertex == ci.m_type)
        continue;
      if (false == bIncludeEdges || ON_COMPONENT_INDEX::TYPE::subd_edge == ci.m_type)
        continue;
      if (false == bIncludeFaces || ON_COMPONENT_INDEX::TYPE::subd_face == ci.m_type)
        continue;
    }
    ON_SubDComponentPtr cptr = ComponentPtrFromComponentIndex(ci_list[i]);
    if (cptr.IsNull())
      continue;
    cptr_list.Append(cptr);
  }

  return (cptr_list.UnsignedCount() - count0);
}

unsigned int ON_SubD::ComponentPtrFromComponentIndex(
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count,
  ON_SimpleArray<ON_SubDComponentPtr>& cptr_list
) const
{
  return ComponentPtrFromComponentIndex(ci_list, ci_count, true, true, true, cptr_list);
}



bool ON_SubD::DeleteComponents(
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count
  )
{
  ON_SimpleArray<ON_SubDComponentPtr> cptr_list;
  if (ComponentPtrFromComponentIndex(ci_list,ci_count,cptr_list) <= 0)
    return true; // nothing to delete

  return DeleteComponents(cptr_list.Array(),cptr_list.UnsignedCount(),false);
}

bool ON_SubD::DeleteComponents(
  const ON_SimpleArray<ON_SubDComponentPtr>& cptr_list,
  bool bMarkDeletedFaceEdges
)
{
  return DeleteComponents(cptr_list.Array(), cptr_list.UnsignedCount(), bMarkDeletedFaceEdges);
}

bool ON_SubD::DeleteComponents(
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  bool bMarkDeletedFaceEdges
)
{
  const bool bDeleteIsolatedEdges = true;
  const bool bUpdateTagsAndCoefficients = true;
  return DeleteComponentsForExperts(cptr_list, cptr_count, bDeleteIsolatedEdges, bUpdateTagsAndCoefficients, bMarkDeletedFaceEdges);
}

bool ON_SubD::DeleteComponentsForExperts(
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  bool bDeleteIsolatedEdges,
  bool bUpdateTagsAndCoefficients,
  bool bMarkDeletedFaceEdges
)
{
  if (bMarkDeletedFaceEdges)
    ClearComponentMarks(false,true,false,nullptr);

  if ( cptr_count <= 0 )
    return true;

  if ( nullptr == cptr_list )
    return ON_SUBD_RETURN_ERROR(false);

  ON_SubDimple* subdimple = SubDimple(false);
  if ( nullptr == subdimple )
    return ON_SUBD_RETURN_ERROR(false);

  const unsigned int level_count = subdimple->LevelCount();
  if (level_count <= 0)
    return ON_SUBD_RETURN_ERROR(false);
  
  unsigned level_index = level_count;
  for (size_t i = 0; i < cptr_count; i++)
  {
    const ON_SubDComponentBase* c = cptr_list[i].ComponentBase();
    if ( nullptr == c)
      continue;
    if ( c->SubdivisionLevel() < level_index )
      level_index = c->SubdivisionLevel();
  }
  if ( level_index == level_count )
    return ON_SUBD_RETURN_ERROR(false);

  if ( false == subdimple->SetActiveLevel(level_index) )
    return ON_SUBD_RETURN_ERROR(false);

  subdimple->ClearHigherSubdivisionLevels(level_index);
  const ON_SubDLevel* level = subdimple->ActiveLevelPointer();
  if ( nullptr == level || level->m_level_index != level_index)
    return ON_SUBD_RETURN_ERROR(false);

  // Make sure no components have a status = ON_ComponentStatus::AllSet
  // because this uncommon status value is used to mark components that will be be deleted.
  ON_SubDComponentIterator cit(*this);
  for (ON_SubDComponentPtr cptr = cit.FirstComponent(); cptr.IsNotNull(); cptr = cit.NextComponent())
  {
    if ( ON_ComponentStatus::AllSet == cptr.Status() )
      cptr.ClearStates(ON_ComponentStatus::Damaged);
  }

  // Set the status of every component in cptr_list[] to ON_ComponentStatus::AllSet.
  // If that component is a vertex, set the status of every edge and face that
  // touch the vertex to ON_ComponentStatus::AllSet.
  // If that component is an edge, set the status of every face that
  // touches the edge to ON_ComponentStatus::AllSet.
  for (size_t i = 0; i < cptr_count; i++)
  {
    ON_SubDComponentPtr cptr = cptr_list[i];
    const ON_SubDComponentBase* c = cptr.ComponentBase();
    if (nullptr == c)
      continue;
    if (c->SubdivisionLevel() != level_index)
      continue;
    c->m_status = ON_ComponentStatus::AllSet;
    switch (cptr.ComponentType())
    {
    case ON_SubDComponentPtr::Type::Vertex:
      {
        const ON_SubDVertex* vertex = cptr.Vertex();
        if (nullptr == vertex)
          continue;
        for (unsigned short vei = 0; vei < vertex->m_edge_count; vei++)
        {
          const ON_SubDEdge* edge = vertex->Edge(vei);
          if (nullptr == edge)
            continue;
          edge->m_status = ON_ComponentStatus::AllSet;
        }
        for (unsigned short vfi = 0; vfi < vertex->m_face_count; vfi++)
        {
          const ON_SubDFace* face = vertex->Face(vfi);
          if (nullptr == face)
            continue;
          face->m_status = ON_ComponentStatus::AllSet;
        }
      }
      break;

    case ON_SubDComponentPtr::Type::Edge:
      {
        const ON_SubDEdge* edge = cptr.Edge();
        if (nullptr == edge)
          continue;
        edge->m_status = ON_ComponentStatus::AllSet;
        for (unsigned short efi = 0; efi < edge->m_face_count; efi++)
        {
          const ON_SubDFace* face = edge->Face(efi);
          if (nullptr == face)
            continue;
          face->m_status = ON_ComponentStatus::AllSet;
        }
      }
      break;

    case ON_SubDComponentPtr::Type::Face:
      {
        const ON_SubDFace* face = cptr.Face();
        if (nullptr == face)
          continue;
        face->m_status = ON_ComponentStatus::AllSet;
      }
      break;
            
    case ON_SubDComponentPtr::Type::Unset:
      break;
    }
  }

  // Minimum count of what will be deleted. (
  unsigned int deleted_vertex_count = 0;
  unsigned int deleted_edge_count = 0;
  unsigned int deleted_face_count = 0;
  for (ON_SubDComponentPtr cptr = cit.FirstComponent(); cptr.IsNotNull(); cptr = cit.NextComponent())
  {
    if (ON_ComponentStatus::AllSet == cptr.Status())
    {
      switch (cptr.ComponentType())
      {
      case ON_SubDComponentPtr::Type::Vertex:
        deleted_vertex_count++;
        break;

      case ON_SubDComponentPtr::Type::Edge:
        deleted_edge_count++;
        break;

      case ON_SubDComponentPtr::Type::Face:
        deleted_face_count++;
        break;
      case ON_SubDComponentPtr::Type::Unset:
        break;
      }
      continue;
    }
  }

  if ( 0 == deleted_vertex_count && 0 == deleted_edge_count && 0 ==  deleted_face_count )
    return false;

  const bool bDestroy
    = deleted_vertex_count >= level->m_vertex_count
    || deleted_edge_count >= level->m_edge_count
    || (deleted_face_count >= level->m_face_count && bDeleteIsolatedEdges)
    ;
  if (bDestroy)
  {
    Destroy();
    return true;
  }

  unsigned int deleted_component_count = subdimple->DeleteComponents(level_index,bDeleteIsolatedEdges,bUpdateTagsAndCoefficients,bMarkDeletedFaceEdges);

  if (0 == subdimple->LevelCount())
  {
    Destroy();
    return true;
  }

  if (deleted_component_count > 0 || level_index > 0)
  {
    // remove lower levels
    subdimple->ClearLowerSubdivisionLevels(level_index);
  }

  return (deleted_component_count > 0);
}

bool ON_SubD::DeleteMarkedComponents(
  bool bDeleteMarkedComponents,
  ON__UINT8 mark_bits,
  bool bMarkDeletedFaceEdges
)
{
  ON_SimpleArray<ON_SubDComponentPtr> cptr_list;
  GetMarkedComponents(bDeleteMarkedComponents, mark_bits, true, true, true, cptr_list);
  return DeleteComponents(
    cptr_list.Array(),
    cptr_list.UnsignedCount(),
    bMarkDeletedFaceEdges
  );
}

bool ON_SubD::DeleteMarkedComponentsForExperts(
  bool bDeleteMarkedComponents,
  ON__UINT8 mark_bits,
  bool bDeleteIsolatedEdges,
  bool bUpdateTagsAndCoefficients,
  bool bMarkDeletedFaceEdges
)
{
  ON_SimpleArray<ON_SubDComponentPtr> cptr_list;
  GetMarkedComponents(bDeleteMarkedComponents, mark_bits, true, true, true, cptr_list);
  return DeleteComponentsForExperts(
    cptr_list.Array(),
    cptr_list.UnsignedCount(),
    bDeleteIsolatedEdges,
    bUpdateTagsAndCoefficients,
    bMarkDeletedFaceEdges
  );
}

unsigned int ON_SubDLevel::UpdateEdgeTags(
  bool bUnsetEdgeTagsOnly
  )
{
  // Update edge flags and sector coefficients.
  unsigned int edge_change_count = 0;
  ON_SubDEdge* next_edge = m_edge[0];
  for (ON_SubDEdge* edge = next_edge; nullptr != edge; edge = next_edge)
  {
    next_edge = const_cast<ON_SubDEdge*>(edge->m_next_edge);

    if (2 != edge->m_face_count && edge->IsSmooth())
    {
      // Dale Lear - Added April 5, 2021 - don't tolerate obvious errors / oversights.
      edge->m_edge_tag = ON_SubDEdgeTag::Unset;
    }

    const ON_SubDEdgeTag edge_tag0 = edge->m_edge_tag;
    if (bUnsetEdgeTagsOnly && ON_SubDEdgeTag::Unset != edge_tag0 )
    {
      continue;
    }

    if (nullptr == edge->m_vertex[0] || nullptr == edge->m_vertex[1])
    {
      ON_SUBD_ERROR("nullptr edge->m_vertex[] values");
      continue;
    }

    const double edge_sector_coefficient0[2] = { edge->m_sector_coefficient[0], edge->m_sector_coefficient[1] };

    if (2 != edge->m_face_count)
    {
      edge->m_edge_tag = ON_SubDEdgeTag::Crease;
      edge->m_sector_coefficient[0] = ON_SubDSectorType::IgnoredSectorCoefficient;
      edge->m_sector_coefficient[1] = ON_SubDSectorType::IgnoredSectorCoefficient;
    }
    else
    {
      edge->m_sector_coefficient[0] = ON_SubDSectorType::UnsetSectorCoefficient;
      edge->m_sector_coefficient[1] = ON_SubDSectorType::UnsetSectorCoefficient;
      const bool bBothVertexTagsAreSet
        =  ON_SubDVertexTag::Unset != edge->m_vertex[0]->m_vertex_tag
        && ON_SubDVertexTag::Unset != edge->m_vertex[1]->m_vertex_tag
        ;
      const unsigned int tagged_end_index = edge->TaggedEndIndex();
      if (0 == tagged_end_index || 1 == tagged_end_index)
        edge->m_sector_coefficient[tagged_end_index] = ON_SubDSectorType::IgnoredSectorCoefficient;

      switch (edge_tag0)
      {
      case ON_SubDEdgeTag::Unset:
        if (2 == tagged_end_index)
        {
          edge->m_edge_tag = ON_SubDEdgeTag::SmoothX;
        }
        else if ( bBothVertexTagsAreSet )
        {
          edge->m_edge_tag = ON_SubDEdgeTag::Smooth;
          if (3 == tagged_end_index)
          {
            edge->m_sector_coefficient[0] = ON_SubDSectorType::IgnoredSectorCoefficient;
            edge->m_sector_coefficient[1] = ON_SubDSectorType::IgnoredSectorCoefficient;
          }
        }
        break;

      case ON_SubDEdgeTag::Smooth:
        if (2 == tagged_end_index)
        {
          edge->m_edge_tag = ON_SubDEdgeTag::SmoothX;
        }
        else if (3 == tagged_end_index && bBothVertexTagsAreSet)
        {
          edge->m_sector_coefficient[0] = ON_SubDSectorType::IgnoredSectorCoefficient;
          edge->m_sector_coefficient[1] = ON_SubDSectorType::IgnoredSectorCoefficient;
        }
        break;

      case ON_SubDEdgeTag::Crease:
        edge->m_sector_coefficient[0] = ON_SubDSectorType::IgnoredSectorCoefficient;
        edge->m_sector_coefficient[1] = ON_SubDSectorType::IgnoredSectorCoefficient;
        break;

      case ON_SubDEdgeTag::SmoothX:
        if ( 2 != tagged_end_index && bBothVertexTagsAreSet)
          edge->m_edge_tag = ON_SubDEdgeTag::Smooth;
        break;

      default:
        break;
      }
    }

    if (!(edge_tag0 == edge->m_edge_tag
      && edge_sector_coefficient0[0] == edge->m_sector_coefficient[0]
      && edge_sector_coefficient0[1] == edge->m_sector_coefficient[1]))
      edge_change_count++;
  }

  return edge_change_count;
}


unsigned int ON_SubDLevel::UpdateVertexTags(
  bool bUnsetVertexTagsOnly
  )
{
  // Update edge flags and sector coefficients.
  unsigned int vertex_change_count = 0;
 

  ON_SubDVertex* next_vertex = m_vertex[0];
  for (ON_SubDVertex* vertex = next_vertex; nullptr != vertex; vertex = next_vertex)
  {
    next_vertex = const_cast<ON_SubDVertex*>(vertex->m_next_vertex);

    const ON_SubDVertexTag vertex_tag0 = vertex->m_vertex_tag;
    if (bUnsetVertexTagsOnly && ON_SubDVertexTag::Unset != vertex_tag0 )
    {
      continue;
    }

    const ON_SubDVertexTag vertex_tag1 = vertex->SuggestedVertexTag(true, false);
    if (ON_SubDVertexTag::Unset == vertex_tag1)
      continue;

    if ( vertex_tag0 != vertex_tag1)
    {
      vertex->m_vertex_tag = vertex_tag1;
      vertex_change_count++;
    }
  }

  return vertex_change_count;
}


unsigned int ON_SubDLevel::UpdateAllTagsAndSectorCoefficients(
  bool bUnsetValuesOnly
)
{
  unsigned int change_count = 0;

  bool bUpdateEdges = true;
  bool bUpdateVertices = true;
  for ( unsigned int it_count = 0; it_count < 8; it_count++)
  {
    const unsigned int edge_change_count 
      = bUpdateEdges
      ? UpdateEdgeTags(bUnsetValuesOnly)
      : 0;
    bUpdateVertices = (edge_change_count > 0 || 0 == it_count);
    change_count += edge_change_count;

    const unsigned int vertex_change_count 
      = bUpdateVertices
      ? UpdateVertexTags(bUnsetValuesOnly)
      : 0;
    bUpdateEdges = (vertex_change_count > 0);    
    change_count += vertex_change_count;

    bUpdateVertices = false;
    if ( false == bUpdateEdges)
      break;
  }

  if (bUpdateVertices && bUpdateEdges)
  {
    ON_SUBD_ERROR("Recursion limit exceeded.");
  }

  // Adjust edge tag smooth/X settings
  // This must be done before UpdateEdgeSectorCoefficients().
  // It is done between the heavy handed setting above so as not to disturb that delicate code.
  ON_SubDEdge* next_edge = m_edge[0];
  for (ON_SubDEdge* edge = next_edge; nullptr != edge; edge = next_edge)
  {
    next_edge = const_cast<ON_SubDEdge*>(edge->m_next_edge);
    if (edge->IsSmooth())
    {
      const ON_SubDEdgeTag etag = (2 == edge->TaggedEndIndex()) ? ON_SubDEdgeTag::SmoothX : ON_SubDEdgeTag::Smooth;
      if (etag != edge->m_edge_tag)
      {
        edge->m_edge_tag = etag;
        ++change_count;
      }
    }
  }

  change_count += UpdateEdgeSectorCoefficients(false);

  if (change_count > 0)
  {
    m_surface_mesh = ON_SubDMesh::Empty;
    m_control_net_mesh = ON_SubDMesh::Empty;
  }    

  return change_count;
}

unsigned int ON_SubDLevel::ClearComponentDamagedState() const
{
  return ClearComponentDamagedState(true, true, true);
}

unsigned int ON_SubDLevel::ClearComponentDamagedState(
  bool bClearVerticesDamagedState,
  bool bClearEdgesDamagedState,
  bool bClearFacesDamagedState
) const
{
  unsigned int change_count = 0;
  unsigned int i;
  if (bClearVerticesDamagedState)
  {
    i = 0;
    for (const ON_SubDVertex* v = m_vertex[0]; nullptr != v && i++ < m_vertex_count; v = v->m_next_vertex)
      if (0 != v->m_status.SetDamagedState(false))
        ++change_count;
  }
  if (bClearEdgesDamagedState)
  {
    i = 0;
    for (const ON_SubDEdge* e = m_edge[0]; nullptr != e && i++ < m_edge_count; e = e->m_next_edge)
      if (0 != e->m_status.SetDamagedState(false))
        ++change_count;
  }
  if (bClearFacesDamagedState)
  {
    i = 0;
    for (const ON_SubDFace* f = m_face[0]; nullptr != f && i++ < m_face_count; f = f->m_next_face)
      if (0 != f->m_status.SetDamagedState(false))
        ++change_count;
  }
  return change_count;
}


unsigned int ON_SubD::UpdateVertexTags(
    bool bUnsetVertexTagsOnly
    )
{
  ON_SubDLevel* level = ActiveLevelPointer();
  if ( nullptr == level )
    return ON_SUBD_RETURN_ERROR(0);

  return level->UpdateVertexTags(bUnsetVertexTagsOnly);
}

unsigned int ON_SubD::UpdateEdgeTags(
  bool bUnsetEdgeTagsOnly
  )
{
  ON_SubDLevel* level = ActiveLevelPointer();
  if ( nullptr == level )
    return ON_SUBD_RETURN_ERROR(0);

  return level->UpdateEdgeTags(bUnsetEdgeTagsOnly);
}


unsigned int ON_SubD::UpdateEdgeSectorCoefficients(
    bool bUnsetSectorCoefficientsOnly
    ) const
{
  const ON_SubDLevel* level = ActiveLevelConstPointer();
  if ( nullptr == level )
    return ON_SUBD_RETURN_ERROR(0);

  return level->UpdateEdgeSectorCoefficients(bUnsetSectorCoefficientsOnly);
}

void ON_SubD::SubDModifiedNofification()
{
  // DestroyRuntimeCache() 
  // Clears
  //  Saved subdivision points.
  //  Saved limit surface information.
  //  Bounding boxes.
  //  
  DestroyRuntimeCache();

  // This is a heavy handed tag update.
  UpdateAllTagsAndSectorCoefficients(false);
}

unsigned int ON_SubD::UpdateAllTagsAndSectorCoefficients(
  bool bUnsetValuesOnly
)
{
  ON_SubDLevel* level = ActiveLevelPointer();
  if ( nullptr == level )
    return ON_SUBD_RETURN_ERROR(0);

  return level->UpdateAllTagsAndSectorCoefficients(bUnsetValuesOnly);
}

unsigned int ON_SubDimple::DeleteComponents(
  unsigned int level_index,
  bool bDeleteIsolatedEdges,
  bool bUpdateTagsAndCoefficients,
  bool bMarkDeletedFaceEdges
  )
{ 
  unsigned int deleted_component_count = 0;

  if (level_index >= m_levels.UnsignedCount())
    return ON_SUBD_RETURN_ERROR(0);

  ON_SubDLevel* level = m_levels[level_index];
  if (nullptr == level)
    return ON_SUBD_RETURN_ERROR(0);

  if (bMarkDeletedFaceEdges)
    level->ClearRuntimeMarks(false,true,false);

  ON_SubDFace* next_face = level->m_face[0];
  for (ON_SubDFace* face = next_face; nullptr != face; face = next_face)
  {
    next_face = const_cast< ON_SubDFace* >(face->m_next_face);
    bool bDelete = (ON_ComponentStatus::AllSet == face->m_status || 0 == face->m_edge_count);
    if (false == bDelete)
    {
      const ON_SubDEdgePtr* eptr = face->m_edge4;
      for (unsigned short fei = 0; fei < face->m_edge_count && false == bDelete; ++fei, ++eptr)
      {
        if (4 == fei)
        {
          eptr = face->m_edgex;
          if (nullptr == eptr)
            break;
        }
        const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
        if (nullptr == edge
          || nullptr == edge->m_vertex[0]
          || nullptr == edge->m_vertex[1]
          || ON_ComponentStatus::AllSet == edge->m_status
          || ON_ComponentStatus::AllSet == edge->m_vertex[0]->m_status
          || ON_ComponentStatus::AllSet == edge->m_vertex[1]->m_status
          )
        {
          bDelete = true;
          if (nullptr != edge && ON_ComponentStatus::AllSet != edge->m_status)
            edge->m_status = ON_ComponentStatus::AllSet;
        }
      }
      if (false == bDelete)
        continue;
    }

    if (bMarkDeletedFaceEdges)
    {
      // Set runtime mark on face's boundary edges.
      const ON_SubDEdgePtr* eptr = face->m_edge4;
      for (unsigned short fei = 0; fei < face->m_edge_count ; ++fei, ++eptr)
      {
        if (4 == fei)
        {
          eptr = face->m_edgex;
          if (nullptr == eptr)
            break;
        }
        const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
        if (nullptr != edge)
          edge->m_status.SetRuntimeMark();
      }
    }

    level->RemoveFace(face);
    m_heap.ReturnFace(face);
    deleted_component_count++;
  }

  ON_ComponentStatus allsetcheck;
  ON_SubDEdge* next_edge = level->m_edge[0];
  for (ON_SubDEdge* edge = next_edge; nullptr != edge; edge = next_edge)
  {
    next_edge = const_cast< ON_SubDEdge* >(edge->m_next_edge);
    allsetcheck = ON_ComponentStatus::LogicalAnd(ON_ComponentStatus::AllSet, edge->m_status);
    bool bDelete = (ON_ComponentStatus::AllSet == allsetcheck || (bDeleteIsolatedEdges && 0 == edge->m_face_count) );
    if (false == bDelete)
    {
      for (unsigned short evi = 0; evi < 2 && false == bDelete; evi++)
      {
        if (nullptr == edge->m_vertex[0]
          || nullptr == edge->m_vertex[1]
          || ON_ComponentStatus::AllSet == edge->m_vertex[0]->m_status
          || ON_ComponentStatus::AllSet == edge->m_vertex[1]->m_status
          )
          bDelete = true;
      }
      if (false == bDelete)
        continue;
    }

    level->RemoveEdge(edge);
    m_heap.ReturnEdge(edge);
    deleted_component_count++;
  }

  ON_SubDVertex* next_vertex = level->m_vertex[0];
  for (ON_SubDVertex* vertex = next_vertex; nullptr != vertex; vertex = next_vertex)
  {
    next_vertex = const_cast<ON_SubDVertex*>(vertex->m_next_vertex);
    allsetcheck = ON_ComponentStatus::LogicalAnd(ON_ComponentStatus::AllSet, vertex->m_status);
    bool bDelete = (ON_ComponentStatus::AllSet == allsetcheck || (bDeleteIsolatedEdges && 0 == vertex->m_face_count) || 0 == vertex->m_edge_count );
    if ( false == bDelete )
      continue;

    level->RemoveVertex(vertex);
    m_heap.ReturnVertex(vertex);
    deleted_component_count++;
  }

  if ( 0 == deleted_component_count )
    return 0;

  // Remove edge references to deleted faces
  next_edge = level->m_edge[0];
  for (ON_SubDEdge* edge = next_edge; nullptr != edge; edge = next_edge)
  {
    next_edge = const_cast<ON_SubDEdge*>(edge->m_next_edge);
    ON_SubDFacePtr* fptr0 = edge->m_face2;
    ON_SubDFacePtr* fptr1 = edge->m_face2;
    const unsigned short edge_face_count = edge->m_face_count;
    edge->m_face_count = 0;
    for (unsigned short efi = 0; efi < edge_face_count; efi++, fptr0++)
    {
      if (2 == efi)
        fptr0 = edge->m_facex;
      const ON_SubDFace* face = fptr0->Face();
      if (nullptr == face || ON_UNSET_UINT_INDEX == face->ArchiveId())
        continue;
      *fptr1++ = *fptr0;
      edge->m_face_count++;
      if (2 == edge->m_face_count)
        fptr1 = edge->m_facex;
    }

    if (0 == edge->m_face_count && bDeleteIsolatedEdges)
    {
      level->RemoveEdge(edge);
      m_heap.ReturnEdge(edge);
      deleted_component_count++;
      continue;
    }
    
    if (edge->m_face_count <= 2 && nullptr != edge->m_facex)
      m_heap.ReturnEdgeExtraArray(edge);

    if (bUpdateTagsAndCoefficients)
    {
      if (edge->m_face_count != 2)
        edge->m_edge_tag = ON_SubDEdgeTag::Crease;

      edge->m_sector_coefficient[0] = ON_SubDSectorType::UnsetSectorCoefficient;
      edge->m_sector_coefficient[1] = ON_SubDSectorType::UnsetSectorCoefficient;
    }
  }

  // Remove vertex references to deleted edges and faces
  next_vertex = level->m_vertex[0];
  for (ON_SubDVertex* vertex = next_vertex; nullptr != vertex; vertex = next_vertex)
  {
    next_vertex = const_cast<ON_SubDVertex*>(vertex->m_next_vertex);

    unsigned int count = vertex->m_edge_count;
    vertex->m_edge_count = 0;

    bool bInteriorVertex = true;
    unsigned int crease_count = 0;
    for (unsigned short vei = 0; vei < count; vei++)
    {
      const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(vertex->m_edges[vei].m_ptr);
      if (nullptr == edge || ON_UNSET_UINT_INDEX == edge->ArchiveId())
      {
        bInteriorVertex = false;
        continue;
      }
      if (edge->IsCrease())
        crease_count++;
      if (2 != edge->m_face_count)
        bInteriorVertex = false;
      vertex->m_edges[vertex->m_edge_count++] = vertex->m_edges[vei];
    }


    count = vertex->m_face_count;
    vertex->m_face_count = 0;
    for (unsigned short vfi = 0; vfi < count; vfi++)
    {
      const ON_SubDFace* face = vertex->m_faces[vfi];
      if (nullptr == face || ON_UNSET_UINT_INDEX == face->ArchiveId()) 
        continue;
      vertex->m_faces[vertex->m_face_count++] = vertex->m_faces[vfi];
    }

    if (0 == vertex->m_face_count && 0 == vertex->m_edge_count)
    {
      level->RemoveVertex(vertex);
      m_heap.ReturnVertex(vertex);
      deleted_component_count++;
    }
    else
    {
      if (1 == crease_count && 1 == vertex->m_edge_count && 0 == vertex->m_face_count)
        vertex->m_vertex_tag = ON_SubDVertexTag::Corner;
      else if (crease_count > 2)
        vertex->m_vertex_tag = ON_SubDVertexTag::Corner;
      else if (false == bInteriorVertex || crease_count > 1)
      {
        if (false == vertex->IsCreaseOrCorner())
          vertex->m_vertex_tag = ON_SubDVertexTag::Crease;
      }
    }
  }

  if (0 == level->m_vertex_count || 0 == level->m_edge_count || (bDeleteIsolatedEdges && 0 == level->m_face_count))
  {
    Destroy();
  }
  else
  {
    // remove all information that is no longer valid
    level->MarkAggregateComponentStatusAsNotCurrent();
    level->ClearEvaluationCache();

    ClearHigherSubdivisionLevels(level_index);

    if (bUpdateTagsAndCoefficients)
    {
      // Update vertex tags, edge tags, and sector coefficients.
      level->UpdateAllTagsAndSectorCoefficients(false);
    }
  }

  ChangeGeometryContentSerialNumber(false);

  return deleted_component_count;
}



unsigned int ON_SubD::ClearComponentMarks() const
{
  return ClearComponentMarks(true, true, true, nullptr);
}

unsigned int ON_SubD::ClearVertexMarks() const
{
  return ClearComponentMarks(true, false, false, nullptr);
}

unsigned int ON_SubD::ClearEdgeMarks() const
{
  return ClearComponentMarks(false, true, false, nullptr);
}

unsigned int ON_SubD::ClearFaceMarks() const
{
  return ClearComponentMarks(false, false, true, nullptr);
}


unsigned int ON_SubD::ClearComponentMarks(
  bool bClearVertexMarks,
  bool bClearEdgeMarks,
  bool bClearFaceMarks,
  ON_SimpleArray< const ON_SubDComponentBase* >* marked_component_list
) const
{
  unsigned int clear_count = 0;

  if (bClearVertexMarks)
  {
    ON_SubDVertexIterator vit(*this);
    for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
    {
      if (v->m_status.ClearRuntimeMark())
      {
        if (nullptr != marked_component_list)
          marked_component_list->Append(v);
        clear_count++;
      }
    }
  }

  if (bClearEdgeMarks)
  {
    ON_SubDEdgeIterator eit(*this);
    for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
    {
      if (e->m_status.ClearRuntimeMark())
      {
        if (nullptr != marked_component_list)
          marked_component_list->Append(e);
        clear_count++;
      }
    }
  }

  if (bClearFaceMarks)
  {
    ON_SubDFaceIterator fit(*this);
    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      if (f->m_status.ClearRuntimeMark())
      {
        if (nullptr != marked_component_list)
          marked_component_list->Append(f);
        clear_count++;
      }
    }
  }

  return clear_count;
}

unsigned int ON_SubD::ClearGroupIds() const
{
  return ClearComponentGroupIds(true, true, true);
}

unsigned int ON_SubD::ClearVertexGroupIds() const
{
  return ClearComponentGroupIds(true, false, false);
}

unsigned int ON_SubD::ClearEdgeGroupIds() const
{
  return ClearComponentGroupIds(false, true, false);
}

unsigned int ON_SubD::ClearFaceGroupIds() const
{
  return ClearComponentGroupIds(false, false, true);
}

unsigned int ON_SubD::ClearComponentGroupIds(
  bool bClearVertexGroupIds,
  bool bClearEdgeGroupIds,
  bool bClearFaceGroupIds
) const
{
  unsigned int clear_count = 0;

  if (bClearVertexGroupIds)
  {
    ON_SubDVertexIterator vit(*this);
    for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
    {
      if (0 != v->m_group_id)
      {
        v->m_group_id = 0;
        clear_count++;
      }
    }
  }

  if (bClearEdgeGroupIds)
  {
    ON_SubDEdgeIterator eit(*this);
    for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
    {
      if (0 != e->m_group_id)
      {
        e->m_group_id = 0;
        clear_count++;
      }
    }
  }

  if (bClearFaceGroupIds)
  {
    ON_SubDFaceIterator fit(*this);
    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      if (0 != f->m_group_id)
      {
        f->m_group_id = 0;
        clear_count++;
      }
    }
  }

  return clear_count;
}


unsigned int ON_SubD::ClearMarkBits() const
{
  return ClearComponentMarkBits(true, true, true);
}

unsigned int ON_SubD::ClearVertexMarkBits() const
{
  return ClearComponentMarkBits(true, false, false);
}

unsigned int ON_SubD::ClearEdgeMarkBits() const
{
  return ClearComponentMarkBits(false, true, false);
}

unsigned int ON_SubD::ClearFaceMarkBits() const
{
  return ClearComponentMarkBits(false, false, true);
}

unsigned int ON_SubD::ClearComponentMarkBits(
  bool bClearVertexMarkBits,
  bool bClearEdgeMarkBits,
  bool bClearFaceMarkBits
) const
{
  unsigned int clear_count = 0;

  if (bClearVertexMarkBits)
  {
    ON_SubDVertexIterator vit(*this);
    for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
    {
      if (0 != v->m_status.MarkBits())
      {
        v->m_status.SetMarkBits(0);
        clear_count++;
      }
    }
  }

  if (bClearEdgeMarkBits)
  {
    ON_SubDEdgeIterator eit(*this);
    for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
    {
      if (0 != e->m_status.MarkBits())
      {
        e->m_status.SetMarkBits(0);
        clear_count++;
      }
    }
  }

  if (bClearFaceMarkBits)
  {
    ON_SubDFaceIterator fit(*this);
    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      if (0 != f->m_status.MarkBits())
      {
        f->m_status.SetMarkBits(0);
        clear_count++;
      }
    }
  }

  return clear_count;
}

unsigned int ON_SubD::UnselectComponents(
    bool bUnselectAllVertices,
    bool bUnselectAllEdges,
    bool bUnselectAllFaces
  ) const
{
  unsigned int unselected_count = 0;

  if (bUnselectAllVertices)
  {
    ON_SubDVertexIterator vit(*this);
    for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
    {
      if (v->m_status.SetSelectedState(false, false, false))
        ++unselected_count;
    }
  }

  if (bUnselectAllEdges)
  {
    ON_SubDEdgeIterator eit(*this);
    for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
    {
      if (e->m_status.SetSelectedState(false, false, false))
        ++unselected_count;
    }
  }

  if (bUnselectAllFaces)
  {
    ON_SubDFaceIterator fit(*this);
    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      if (f->m_status.SetSelectedState(false, false, false))
        ++unselected_count;
    }
  }

  return unselected_count;
}


unsigned int ON_SubD::SetComponentMarks(
  bool bClearBeforeSet,
  const ON_SimpleArray< const ON_SubDComponentBase* >& marked_component_list
) const
{
  unsigned int set_count = 0;

  if (bClearBeforeSet)
    ClearComponentMarks(true, true, true, nullptr);

  const unsigned count = marked_component_list.Count();
  if (count <= 0)
    return 0;
  const ON_SubDComponentBase*const* a = marked_component_list.Array();
  if (nullptr == a)
    return 0;

  for (const ON_SubDComponentBase*const* a1 = a + count; a < a1; a++)
  {
    const ON_SubDComponentBase* c = *a;
    if (nullptr == c)
      continue;
    if (c->m_status.SetRuntimeMark())
      set_count++;
  }

  return set_count;
}

unsigned int ON_SubD::GetMarkedComponents(
  bool bAddMarkedComponents,
  ON__UINT8 mark_bits,
  bool bIncludeVertices,
  bool bIncludeEdges,
  bool bIncludeFaces,
  ON_SimpleArray< ON_SubDComponentPtr >& component_list
) const
{
  bAddMarkedComponents = bAddMarkedComponents ? true : false; // so we can use == on boolean values
  unsigned int mark_count = 0;

  if (bIncludeVertices)
  {
    ON_SubDVertexIterator vit(*this);
    for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
    {
      if (bAddMarkedComponents == v->m_status.IsMarked(mark_bits))
      {
        component_list.Append(v->ComponentPtr());
        mark_count++;
      }
    }
  }

  if (bIncludeEdges)
  {
    ON_SubDEdgeIterator eit(*this);
    for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
    {
      if (bAddMarkedComponents == e->m_status.IsMarked(mark_bits))
      {
        component_list.Append(e->ComponentPtr());
        mark_count++;
      }
    }
  }

  if (bIncludeFaces)
  {
    ON_SubDFaceIterator fit(*this);
    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      if (bAddMarkedComponents == f->m_status.IsMarked(mark_bits))
      {
        component_list.Append(f->ComponentPtr());
        mark_count++;
      }
    }
  }

  return mark_count;
}

unsigned int ON_SubD::GetMarkedComponents(
    bool bIncludeVertices,
    bool bIncludeEdges,
    bool bIncludeFaces,
  ON_SimpleArray< const ON_SubDComponentBase* >& marked_component_list
) const
{
  unsigned int mark_count = 0;

  if (bIncludeVertices)
  {
    ON_SubDVertexIterator vit(*this);
    for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
    {
      if (v->m_status.RuntimeMark())
      {
        marked_component_list.Append(v);
        mark_count++;
      }
    }
  }

  if (bIncludeEdges)
  {
    ON_SubDEdgeIterator eit(*this);
    for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
    {
      if (e->m_status.RuntimeMark())
      {
        marked_component_list.Append(e);
        mark_count++;
      }
    }
  }

  if (bIncludeFaces)
  {
    ON_SubDFaceIterator fit(*this);
    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      if (f->m_status.RuntimeMark())
      {
        marked_component_list.Append(f);
        mark_count++;
      }
    }
  }

  return mark_count;
}

unsigned int ON_SubD::GetComponentStatus(
  bool bGetVertexStatus,
  bool bGetEdgeStatus,
  bool bGetFaceStatus,
  bool bClearStatus,
  ON_ComponentStatus status_mask,
  ON_SimpleArray< const class ON_SubDComponentBase* >& component_list,
  ON_SimpleArray< ON_ComponentStatus >& status_list
) const
{
  component_list.SetCount(0);
  status_list.SetCount(0);
  if ( ON_ComponentStatus::NoneSet == status_mask )
    return 0;

  ON_ComponentStatus s;

  if (bGetVertexStatus)
  {
    ON_SubDVertexIterator vit(*this);
    for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
    {
      s = ON_ComponentStatus::LogicalAnd(status_mask, v->m_status);
      if (ON_ComponentStatus::NoneSet == s)
        continue;
      component_list.Append(v);
      status_list.Append(s);
    }
  }

  if (bGetEdgeStatus)
  {
    ON_SubDEdgeIterator eit(*this);
    for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
    {
      s = ON_ComponentStatus::LogicalAnd(status_mask, e->m_status);
      if (ON_ComponentStatus::NoneSet == s)
        continue;
      component_list.Append(e);
      status_list.Append(s);
    }
  }

  if (bGetFaceStatus)
  {
    ON_SubDFaceIterator fit(*this);
    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      s = ON_ComponentStatus::LogicalAnd(status_mask, f->m_status);
      if (ON_ComponentStatus::NoneSet == s)
        continue;
      component_list.Append(f);
      status_list.Append(s);
    }
  }

  const unsigned int count = component_list.UnsignedCount();
  if (bClearStatus && count > 0)
  {
    const bool bRuntimeMark = status_mask.RuntimeMark();
    for (unsigned int i = 0; i < count; ++i)
    {
      const ON_SubDComponentBase* c = component_list[i];
      if (nullptr == c)
        continue;
      c->m_status.ClearStates(status_mask);
      if (bRuntimeMark)
        c->m_status.ClearRuntimeMark();
    }
  }

  return count;
}

unsigned int ON_SubD::SetComponentStatus(
  ON_ComponentStatus status_mask,
  const ON_SimpleArray< const class ON_SubDComponentBase* >& component_list,
  const ON_SimpleArray< ON_ComponentStatus >& status_list
) const
{
  const unsigned int count = component_list.UnsignedCount();
  if (count < 1 || count != status_list.UnsignedCount())
    return 0;

  const bool bRuntimeMark = status_mask.RuntimeMark();

  for (unsigned int i = 0; i < count; ++i)
  {
    const ON_SubDComponentBase* c = component_list[i];
    if (nullptr == c)
      continue;
    const ON_ComponentStatus s = status_list[i];
    c->m_status.ClearStates(status_mask);
    c->m_status.SetStates(s);
    if (bRuntimeMark)
    {
      if ( s.RuntimeMark())
        c->m_status.SetRuntimeMark();
      else
        c->m_status.ClearRuntimeMark();
    }
  }

  return count;
}

ON_SubDComponentMarksClearAndRestore::ON_SubDComponentMarksClearAndRestore(
  const ON_SubD& subd
)  
{
  m_subd.ShareDimple(subd);
  m_subd.ClearComponentMarks(true, true, true, &m_component_list);
}

ON_SubDComponentMarksClearAndRestore::~ON_SubDComponentMarksClearAndRestore()
{
  Restore(true);
}

const ON_SimpleArray<const class ON_SubDComponentBase*>& ON_SubDComponentMarksClearAndRestore::ComponentList() const
{
  return m_component_list;
}

bool ON_SubDComponentMarksClearAndRestore::Restore(
  bool bDisableFutureRestore )
{
  const bool rc = m_bRestore;
  if (rc)
  {
    if ( bDisableFutureRestore)
      m_bRestore = false;
    
    m_subd.ClearComponentMarks(true, true, true, nullptr);

//    if ( ON_ComponentStatus::Marked == m_status_mask )
    {
      // RuntimeMark is the only bit being managed
      if (m_component_list.UnsignedCount() > 0)
        m_subd.SetComponentMarks(false, m_component_list);
    }
    //else if ( m_status_mask.IsNotClear() )
    //{
    //  // something fancier is going on

    //  // clear current settings
    //  ON_SubDVertexIterator vit(m_subd);
    //  for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
    //    v->m_status.ClearStates(m_status_mask);

    //  ON_SubDEdgeIterator eit(m_subd);
    //  for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
    //    e->m_status.ClearStates(m_status_mask);

    //  ON_SubDFaceIterator fit(m_subd);
    //  for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    //    f->m_status.ClearStates(m_status_mask);

    //  // restore settings
    //  m_subd.SetComponentStatus(m_status_mask, m_component_list, m_status_list);
    //}

    if (bDisableFutureRestore)
    {
      m_component_list.Destroy();
      //m_status_list.Destroy();
    }
  }
  return rc;
}

void ON_SubDComponentMarksClearAndRestore::DisableRestore()
{
  m_bRestore = false;
}

unsigned int ON_SubD::TransformComponents(
  const ON_Xform& xform,
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count,
  ON_SubDComponentLocation component_location
)
{
  if (
    false ==  xform.IsValidAndNotZeroAndNotIdentity()
    || ci_count <= 0
    || nullptr == ci_list
    )
    return 0;

  ON_SimpleArray<ON_SubDComponentPtr> cptr_list;
  if (ComponentPtrFromComponentIndex(ci_list,ci_count,cptr_list) <= 0)
    return true; // nothing to delete

  return TransformComponents(xform,cptr_list.Array(),cptr_list.UnsignedCount(),component_location);
}

unsigned ON_SubDVertexQuadSector::SectorVertexCount(ON_SubDVertexTag vertex_tag, unsigned sector_face_count)
{
  const unsigned center_vertex_edge_count = ON_SubDVertexQuadSector::CenterVertexEdgeCount(vertex_tag, sector_face_count);
  return (center_vertex_edge_count >= 2U) ? (1U + center_vertex_edge_count + sector_face_count) : 0U;
}

unsigned ON_SubDVertexQuadSector::SectorEdgeCount(ON_SubDVertexTag vertex_tag, unsigned sector_face_count)
{
  if (sector_face_count <= ON_SubDVertex::MaximumFaceCount)
  {
    const unsigned min_sector_face_count = ON_SubDVertexQuadSector::MinimumSectorFaceCount(vertex_tag);
    if (sector_face_count >= min_sector_face_count)
      return (2U - min_sector_face_count) + 3U * sector_face_count;
  }
  return 0U;
}

unsigned ON_SubDVertexQuadSector::CenterVertexEdgeCount(ON_SubDVertexTag center_vertex_tag, unsigned sector_face_count)
{
  unsigned center_vertex_edge_count;
  
  switch (center_vertex_tag)
  {
  case ON_SubDVertexTag::Smooth:
  case ON_SubDVertexTag::Dart:
    center_vertex_edge_count = (sector_face_count >= 2U) ? sector_face_count : 0U;
    break;

  case ON_SubDVertexTag::Crease:
  case ON_SubDVertexTag::Corner:
    center_vertex_edge_count = (sector_face_count >= 1U) ? (sector_face_count + 1U) : 0U;
    break;

  case ON_SubDVertexTag::Unset:
  default:
    center_vertex_edge_count = 0U;
    break;
  }

  return center_vertex_edge_count;
}

unsigned ON_SubDVertexQuadSector::MinimumSectorFaceCount(
  ON_SubDVertexTag vertex_tag
)
{
  unsigned min_sector_face_count;
  switch (vertex_tag)
  {
  case ON_SubDVertexTag::Smooth:
  case ON_SubDVertexTag::Dart:
    min_sector_face_count = 2U;
    break;

  case ON_SubDVertexTag::Crease:
  case ON_SubDVertexTag::Corner:
    min_sector_face_count = 1U;
    break;

  case ON_SubDVertexTag::Unset:
  default:
    min_sector_face_count = 0U;
    break;
  }

  return min_sector_face_count;
}


void ON_SubDVertexQuadSector::Internal_Destroy()
{
  void* heap = this->m_heap;
  this->m_heap = nullptr;
  this->m_v = nullptr;
  this->m_e = nullptr;
  this->m_f = nullptr;
  this->m_sector_coefficient = ON_DBL_QNAN;
  this->m_maximum_edge_end_sharpness = ON_DBL_QNAN;
  this->m_sector_face_count = 0;
  this->m_center_vertex_edge_count = 0;
  if (nullptr != heap)
    onfree(heap);
}

ON_SubDVertexQuadSector::~ON_SubDVertexQuadSector()
{
  this->Internal_Destroy();
}

void ON_SubDVertexQuadSector::Internal_CopyFrom(const ON_SubDVertexQuadSector& src)
{
  const ON_SubDVertexTag center_vertex_tag = src.CenterVertexTag();
  if (false == this->Initialize(center_vertex_tag, src.CenterVertexSharpness(), src.SectorFaceCount(), nullptr, nullptr))
    return;

  if ( ON_SubDVertexTag::Corner == center_vertex_tag)
    this->m_sector_coefficient = src.m_sector_coefficient;

  const unsigned vertex_count = src.SectorVertexCount();
  for (unsigned vi = 0; vi < vertex_count; ++vi)
  {
    ON_SubDVertex& v = m_v[vi];
    const ON_SubDVertex& srcv = src.m_v[vi];
    const ON_3dPoint p = srcv.ControlNetPoint();
    if (p.IsValid())
      v.SetControlNetPoint(p, false);
    else
      v.UnsetControlNetPoint();
    v.SetSubdivisionLevel(srcv.SubdivisionLevel());
  }

  const unsigned center_vertex_edge_count = src.CenterVertexEdgeCount();
  const unsigned edge_count = src.SectorEdgeCount();
  for (unsigned ei = 0; ei < edge_count; ++ei)
  {
    ON_SubDEdge& e = m_e[ei];
    const ON_SubDEdge& srce = src.m_e[ei];
    if (ei < center_vertex_edge_count)
    {
      const ON_SubDEdgeSharpness s = srce.Sharpness(false);
      if (s.IsSharp())
        e.SetSharpnessForExperts(s);
      if (e.IsSmooth())
        e.m_sector_coefficient[0] = this->m_sector_coefficient;
    }
  }
}

ON_SubDVertexQuadSector::ON_SubDVertexQuadSector(const ON_SubDVertexQuadSector& src)
{
  this->Internal_CopyFrom(src);
}

ON_SubDVertexQuadSector& ON_SubDVertexQuadSector::operator=(const ON_SubDVertexQuadSector& src)
{
  if (this != &src)
  {
    this->Internal_Destroy();
    this->Internal_CopyFrom(src);
  }
  return *this;
}

bool ON_SubDVertexQuadSector::Initialize(
  ON_SubDVertexTag center_vertex_tag,
  double center_vertex_sharpness,
  unsigned sector_face_count,
  const ON_3dPoint* sector_control_net_points,
  const ON_SubDEdgeSharpness* center_edge_sharpnesses
) 
{
  this->m_sector_coefficient = ON_DBL_QNAN;
  this->m_maximum_edge_end_sharpness = ON_DBL_QNAN;

  const unsigned sector_vertex_count = ON_SubDVertexQuadSector::SectorVertexCount(center_vertex_tag, sector_face_count);
  const unsigned sector_edge_count = ON_SubDVertexQuadSector::SectorEdgeCount(center_vertex_tag, sector_face_count);
  bool bValidInput = sector_vertex_count >= 4U && sector_edge_count >= sector_face_count && sector_face_count >= 1U;
  if (false == bValidInput)
  {
    ON_SUBD_ERROR("Invalid input.");
    this->Internal_Destroy();
    return false;
  }

  const bool bInteriorSector = (ON_SubDVertexTag::Smooth == center_vertex_tag || ON_SubDVertexTag::Dart == center_vertex_tag);

  const unsigned center_vertex_edge_count = sector_face_count + (bInteriorSector ? 0U : 1U);
  const unsigned ptr_count = sector_face_count + center_vertex_edge_count + 8 * (center_vertex_edge_count + sector_face_count);
  const size_t sizeofv = sector_vertex_count * sizeof(m_v[0]);
  const size_t sizeofe = sector_edge_count * sizeof(m_e[0]);
  const size_t sizeoff = sector_face_count * sizeof(m_f[0]);
  const size_t sizeofp = ptr_count * sizeof(ON__UINT_PTR);
  const size_t sizeofr = sector_vertex_count * sizeof(m_r[0]);
  const size_t sz = sizeofv + sizeofe + sizeoff + sizeofp + sizeofr;
  if ( nullptr == m_heap || sector_face_count != this->m_sector_face_count || center_vertex_edge_count != this->m_center_vertex_edge_count )
  {
    Internal_Destroy();
    m_heap = onmalloc(sz);
    if (nullptr == m_heap)
      return false;
  }

  memset(m_heap, 0, sz);
  m_v = (ON_SubDVertex*)m_heap;
  m_e = (ON_SubDEdge*)(m_v + sector_vertex_count);
  m_f = (ON_SubDFace*)(m_e + sector_edge_count);
  ON__UINT_PTR* p = (ON__UINT_PTR*)(m_f + sector_face_count);
  m_r = (ON_SubDComponentPtr*)(p + ptr_count);
  m_sector_face_count = sector_face_count;
  m_center_vertex_edge_count = center_vertex_edge_count;

  for (unsigned vi = 0; vi < sector_vertex_count; ++vi)
  {
    ON_SubDVertex* v = &m_v[vi];
    v->m_vertex_tag = ON_SubDVertexTag::Smooth;
    v->m_edge_capacity = (unsigned short)(0 == vi ? center_vertex_edge_count : 4U);
    v->m_face_capacity = (unsigned short)(0 == vi ? sector_face_count : 4U);
    v->m_edges = (ON_SubDEdgePtr*)p;
    p += v->m_edge_capacity;
    v->m_faces = (const ON_SubDFace**)p;
    p += v->m_face_capacity;
    if (1U == (vi % 2U))
    {
      const unsigned ei = (vi - 1U) / 2U;
      // When vi is odd, m_v[vi] is a ring vertex for edge m_e[ei]
      m_e[ei].m_vertex[0] = &m_v[0];
      m_e[ei].m_vertex[1] = v;
    }
  }

  for (unsigned fi = 0; fi < sector_face_count; ++fi)
  {
    ON_SubDFace* f = &m_f[fi];
    const unsigned vi = 2U * (fi + 1U);
    const unsigned ei = center_vertex_edge_count + 2U * fi;
    ON_SubDEdge* e4[4] = { &m_e[fi], &m_e[ei] , &m_e[ei + 1], &m_e[(fi + 1U) % center_vertex_edge_count] };
    ON_SubDVertex* v4[4] = {
      &m_v[0],
      const_cast<ON_SubDVertex*>(e4[0]->m_vertex[1]),
      &m_v[vi],
      const_cast<ON_SubDVertex*>(e4[3]->m_vertex[1])
    };

    e4[1]->m_vertex[0] = v4[1];
    e4[1]->m_vertex[1] = v4[2];

    e4[2]->m_vertex[0] = v4[2];
    e4[2]->m_vertex[1] = v4[3];

    for (unsigned fei = 0; fei < 4U; ++fei)
    {
      const ON__INT_PTR dir = (3 == fei) ? 1 : 0;
      f->m_edge4[fei] = ON_SubDEdgePtr::Create(e4[fei], dir);
      e4[fei]->m_face2[e4[fei]->m_face_count++] = ON_SubDFacePtr::Create(f, dir);
    }
    f->m_edge_count = 4;

    for (unsigned fvi = 0; fvi < 4U; ++fvi)
    {
      v4[fvi]->m_faces[v4[fvi]->m_face_count++] = &m_f[fi];
    }
  }

  for (unsigned ei = 0; ei < sector_edge_count; ++ei)
  {
    ON_SubDEdge* e = &m_e[ei];
    e->m_edge_tag = ON_SubDEdgeTag::Smooth;
    for (unsigned evi = 0; evi < 2; ++evi)
    {
      ON_SubDVertex* v = const_cast<ON_SubDVertex*>(e->m_vertex[evi]);
      v->m_edges[v->m_edge_count++] = ON_SubDEdgePtr::Create(e, evi);
    }
  }

  // 2024-01-12, Pierre:
  // Move up code setting control net points and edge sharpnesses.
  // Remove code that was copied below from SetCenterVertexTagAndCenterVertexEdgesTags,
  // that is not needed if sector_control_net_points and center_edge_sharpnesses are 
  // properly set before the call to SetCenterVertexTagAndCenterVertexEdgesTags.
  if (nullptr != sector_control_net_points)
  {
    for (unsigned vi = 0; vi < sector_vertex_count; ++vi)
    {
      const ON_3dPoint P = sector_control_net_points[vi];
      if (P.IsValid())
        m_v[vi].SetControlNetPoint(P, false);
      else
        m_v[vi].UnsetControlNetPoint();
      m_v[vi].m_id = vi + 1U;
    }
  }
  else
  {
    for (unsigned vi = 0; vi < sector_vertex_count; ++vi)
    {
      m_v[vi].UnsetControlNetPoint();
      m_v[vi].m_id = vi + 1U;
    }
  }

  center_vertex_sharpness = ON_SubDEdgeSharpness::Sanitize(center_vertex_sharpness, 0.0);
  if (nullptr != center_edge_sharpnesses)
  {
    this->m_maximum_edge_end_sharpness = 0.0;
    for (unsigned ei = 0; ei < m_center_vertex_edge_count; ++ei)
    {
      if (m_e[ei].IsCrease())
      {
        m_e[ei].ClearSharpnessForExperts();
      }
      else
      {
        m_e[ei].SetSharpnessForExperts(center_edge_sharpnesses[ei]);
        const ON_SubDEdgeSharpness es = m_e[ei].Sharpness(false);
        const double x = es.MaximumEndSharpness();
        if (x > this->m_maximum_edge_end_sharpness)
          this->m_maximum_edge_end_sharpness = x;
        const double y = m_e[ei].EndSharpness(&m_v[0]);
        if (y > center_vertex_sharpness)
          center_vertex_sharpness = y;
      }
      m_e[ei].m_id = ei + 1U;
    }
    for (unsigned ei = m_center_vertex_edge_count; ei < sector_edge_count; ++ei)
    {
      m_e[ei].m_id = ei + 1U;
    }
  }
  else
  {
    for (unsigned ei = 0; ei < sector_edge_count; ++ei)
    {
      m_e[ei].m_id = ei + 1U;
    }
  }

  for (unsigned fi = 0; fi < sector_face_count; ++fi)
  {
    m_f[fi].m_id = fi + 1U;
  }

  if (false == SetCenterVertexTagAndCenterVertexEdgesTags(center_vertex_tag))
  {
    this->Internal_Destroy();
    return false;
  }

  this->SetCenterVertexSharpness(center_vertex_sharpness);
  if (ON_SubDVertexTag::Crease == m_v[0].m_vertex_tag)
    m_v[0].Internal_SetInteriorCreaseVertexSharpnessForExperts(this->CenterVertexSharpness(), true);
  else
    m_v[0].Internal_ClearInteriorCreaseVertexSharpnessForExperts();

  m_r[0] = ON_SubDComponentPtr::Create(&m_v[0]);
  for (unsigned ri = 1u; ri < sector_vertex_count; ri += 2u)
    m_r[ri] = ON_SubDComponentPtr::Create(&m_e[ri / 2], 0);
  for (unsigned ri = 2u; ri < sector_vertex_count; ri += 2u)
    m_r[ri] = ON_SubDComponentPtr::Create(&m_f[ri / 2u - 1u]);

  return true;
}

bool ON_SubDVertexQuadSector::Initialize(
  ON_SubDVertexTag center_vertex_tag,
  double center_vertex_sharpness,
  unsigned sector_face_count,
  const ON_SimpleArray<ON_3dPoint>& sector_control_net_points
)
{
  const unsigned sector_vertex_count = ON_SubDVertexQuadSector::SectorVertexCount(center_vertex_tag, sector_face_count);
  return (sector_vertex_count > 0U && sector_vertex_count == sector_control_net_points.UnsignedCount())
    ? this->Initialize(center_vertex_tag, center_vertex_sharpness, sector_face_count, sector_control_net_points.Array(), nullptr)
    : false;
}

bool ON_SubDVertexQuadSector::Initialize(
  ON_SubDVertexTag center_vertex_tag,
  double center_vertex_sharpness,
  unsigned sector_face_count,
  const ON_SimpleArray<ON_3dPoint>& sector_control_net_points,
  const ON_SimpleArray<ON_SubDEdgeSharpness>& center_edge_sharpnesses
)
{
  const unsigned sector_vertex_count = ON_SubDVertexQuadSector::SectorVertexCount(center_vertex_tag, sector_face_count);
  const unsigned center_vertex_edge_count = ON_SubDVertexQuadSector::CenterVertexEdgeCount(center_vertex_tag, sector_face_count);
  return (
    sector_vertex_count > 0U 
    && (sector_vertex_count == sector_control_net_points.UnsignedCount() || 0 == sector_control_net_points.UnsignedCount())
    && (center_vertex_edge_count == center_edge_sharpnesses.UnsignedCount() || 0 == center_edge_sharpnesses.UnsignedCount())
    )
    ? this->Initialize(center_vertex_tag, center_vertex_sharpness, sector_face_count,
      (sector_vertex_count == sector_control_net_points.UnsignedCount()) ? sector_control_net_points.Array() : nullptr,      
      (center_vertex_edge_count == center_edge_sharpnesses.UnsignedCount()) ? center_edge_sharpnesses.Array() : nullptr
    )
    : false;
}

double ON_SubDVertexQuadSector::MaximumRadialEdgeEndSharpness() const
{
  if (false == (this->m_maximum_edge_end_sharpness >= 0.0))
  {
    //const ON_SubDVertexTag center_vertex_tag = this->CenterVertexTag();
    const unsigned crease_count = this->SectorCreaseEdgeCount();
    double maxs = 0.0;
    unsigned n = this->CenterVertexEdgeCount();
    if (n > 0U && 2U == crease_count)
      --n;
    for (unsigned ei = (0U == crease_count) ? 0U : 1U; ei < n; ++ei)
    {
      const double x = m_e[ei].Sharpness(false).MaximumEndSharpness();
      if (x > maxs)
        maxs = x;
      this->m_maximum_edge_end_sharpness = maxs;
    }
  }
  return this->m_maximum_edge_end_sharpness;
}

double ON_SubDVertexQuadSector::CenterVertexSharpness() const
{
  if (false == ON_SubDEdgeSharpness::IsValidValue(this->m_center_vertex_sharpness, false))
  {
    const ON_SubDVertex* v = this->CenterVertex();
    this->m_center_vertex_sharpness = (nullptr != v) ? v->VertexSharpness() : 0.0;
  }
  return this->m_center_vertex_sharpness;
}

double ON_SubDVertexQuadSector::MaximumSharpness() const
{
  const double max_es = this->MaximumRadialEdgeEndSharpness();
  const double max_vs = this->CenterVertexSharpness();
  return (max_vs > max_es) ? max_vs : max_es;
}

bool ON_SubDVertexQuadSector::SetCenterVertexTagAndCenterVertexEdgesTags(ON_SubDVertexTag center_vertex_tag)
{
  this->m_sector_coefficient = ON_DBL_QNAN;
  bool bValidTag = false;
  ON_SubDEdge* creases[2] = {};
  double sector_coefficient = ON_DBL_QNAN;
  switch (center_vertex_tag)
  {
  case ON_SubDVertexTag::Unset:
    bValidTag = false;
    break;
  case ON_SubDVertexTag::Smooth:
    if (m_sector_face_count >= 2 && m_center_vertex_edge_count == m_sector_face_count)
    {
      bValidTag = true;
      sector_coefficient = ON_SubDSectorType::SmoothSectorCoefficient();
    }
    break;
  case ON_SubDVertexTag::Crease:
    if (m_sector_face_count >= 1 && m_center_vertex_edge_count == m_sector_face_count + 1U)
    {
      bValidTag = true;
      creases[0] = &m_e[0];
      creases[1] = &m_e[m_sector_face_count];
      sector_coefficient = ON_SubDSectorType::CreaseSectorCoefficient(m_sector_face_count);
    }
    break;
  case ON_SubDVertexTag::Corner:
    if (m_sector_face_count >= 1 && m_center_vertex_edge_count == m_sector_face_count + 1U)
    {
      bValidTag = true;
      creases[0] = &m_e[0];
      creases[1] = &m_e[m_sector_face_count];
      bool bValidEdges = creases[0]->ControlNetLine().IsValid() && creases[1]->ControlNetLine().IsValid();
      double angle_radians
        = bValidEdges
        ? ON_SubDSectorType::CornerSectorAngleRadiansFromEdges(ON_SubDEdgePtr::Create(creases[0], 0), ON_SubDEdgePtr::Create(creases[1], 0))
        : ON_HALFPI;
      sector_coefficient = ON_SubDSectorType::CornerSectorCoefficient(m_sector_face_count, angle_radians);
    }
    break;
  case ON_SubDVertexTag::Dart:
    if (m_sector_face_count >= 2 && m_center_vertex_edge_count == m_sector_face_count)
    {
      bValidTag = true;
      creases[0] = &m_e[0];
      sector_coefficient = ON_SubDSectorType::DartSectorCoefficient(m_sector_face_count);
    }
    break;
  default:
    bValidTag = false;
  }

  if (false == bValidTag)
    return ON_SUBD_RETURN_ERROR(false);

  if (false == (sector_coefficient > 0.0 && sector_coefficient < 1.0))
    sector_coefficient = 0.0;

  this->m_sector_coefficient = sector_coefficient;

  m_v[0].m_vertex_tag = center_vertex_tag;
  this->m_maximum_edge_end_sharpness = 0.0;
  for (unsigned ei = 0; ei < m_center_vertex_edge_count; ++ei)
  {
    ON_SubDEdge* e = &m_e[ei];
    if (e == creases[0] || e == creases[1])
    {
      e->m_edge_tag = ON_SubDEdgeTag::Crease;
      e->m_sector_coefficient[0] = 0.0;
      e->m_sector_coefficient[1] = 0.0;
      e->ClearSharpnessForExperts();
    }
    else
    {
      e->m_edge_tag = ON_SubDEdgeTag::Smooth;
      e->m_sector_coefficient[0] = sector_coefficient;
      e->m_sector_coefficient[1] = 0.0;
      const double x = e->Sharpness(false).MaximumEndSharpness();
      if (x > this->m_maximum_edge_end_sharpness)
        this->m_maximum_edge_end_sharpness = x;
    }
  }

  // 2024-01-12, Pierre, RH-79544: There is no reason not to set these tags properly, so do it
  if (creases[0] != nullptr) 
    m_v[1].m_vertex_tag = ON_SubDVertexTag::Crease;
  if (creases[1] != nullptr) 
    m_v[m_center_vertex_edge_count + m_sector_face_count].m_vertex_tag = ON_SubDVertexTag::Crease;

  return true;
}

bool ON_SubDVertexQuadSector::SetCenterVertexSharpness(double center_vertex_sharpness)
{
  this->m_center_vertex_sharpness = ON_SubDEdgeSharpness::Sanitize(center_vertex_sharpness, 0.0);
  return ON_SubDEdgeSharpness::IsValidValue(this->m_center_vertex_sharpness, false);
}

bool ON_SubDVertexQuadSector::GetSectorControlNetPoints(
  ON_SimpleArray<ON_3dPoint>& sector_control_net_points
) const
{
  sector_control_net_points.SetCount(0);
  const unsigned sector_vertex_count = this->SectorVertexCount();
  if (sector_vertex_count > 0)
  {
    sector_control_net_points.Reserve(sector_vertex_count);
    for (unsigned vi = 0; vi < sector_vertex_count; ++vi)
      sector_control_net_points.Append(m_v[vi].ControlNetPoint());
  }
  return sector_control_net_points.Count() > 0;
}

bool ON_SubDVertexQuadSector::InitializeFromSubdividedSectorComponents(
  double center_vertex_sharpness,
  const ON_SimpleArray<ON_SubDComponentPtr>& sector_ring_components
)
{
  return this->InitializeFromSubdividedSectorComponents(
    center_vertex_sharpness,
    sector_ring_components.Array(), 
    sector_ring_components.Count());
}

bool ON_SubDVertexQuadSector::InitializeFromSubdividedSectorComponents(
  double center_vertex_sharpness,
  const ON_SubDComponentPtr* sector_ring_components, 
  size_t sector_components_count)
{
  for (;;)
  {
    const unsigned sector_ring_component_count = (nullptr != sector_ring_components) ? ((unsigned)sector_components_count) : 0u;
    if (sector_ring_component_count < 4U)
    {
      ON_SUBD_ERROR("sector_ring_component_count is too small.");
      break;
    }

    const ON_SubDVertex* center_vertex = sector_ring_components[0].Vertex();
    if (nullptr == center_vertex)
    {
      ON_SUBD_ERROR("sector_ring_components[0] must be the sector center vertex.");
      break;
    }

    const ON_SubDVertexTag center_vertex_tag = (nullptr != center_vertex) ? center_vertex->m_vertex_tag : ON_SubDVertexTag::Unset;

    if (ON_SubDVertexTag::Crease == center_vertex_tag)
    {
      const double y = center_vertex->VertexSharpness();
      if (y > center_vertex_sharpness)
        center_vertex_sharpness = y;
    }

    unsigned min_ring_count = 0U;
    switch (center_vertex_tag)
    {
    case ON_SubDVertexTag::Unset:
      break;
    case ON_SubDVertexTag::Smooth:
    case ON_SubDVertexTag::Dart:
      min_ring_count = 5U;
      break;
    case ON_SubDVertexTag::Crease:
    case ON_SubDVertexTag::Corner:
      min_ring_count = 4U;
      break;
    default:
      break;
    }

    if (min_ring_count < 4U || sector_ring_component_count < min_ring_count || (sector_ring_component_count % 2U) != (min_ring_count % 2U))
    {
      ON_SUBD_ERROR("Invalid combination of center vertex tag and sector_component_ring_count.");
      break;
    }

    if (
      ON_SubDVertexTag::Dart == center_vertex_tag 
      && false == sector_ring_components[1].EdgePtr().EdgeIsCrease()
      && 1U == (sector_ring_component_count % 2U)
      )
    {
      for (unsigned i = 1; i < sector_ring_component_count; i += 2)
      {
        if (false == sector_ring_components[i].EdgePtr().EdgeIsCrease())
          continue;

        // Roll the edges and face portion of sector_ring_components[]
        // so the dart's crease is the first edge in local_sector_ring_components[].
        ON_SimpleArray<ON_SubDComponentPtr> local_sector_ring_components(sector_ring_component_count);
        local_sector_ring_components[0] = sector_ring_components[0];
        for (unsigned k = 3U; k < sector_ring_component_count; k += 2)
        {
          local_sector_ring_components.Append(sector_ring_component_count - k, sector_ring_components + k);
          local_sector_ring_components.Append(k - 1U, sector_ring_components + 1U);
        }
        // check that there will not be infinite recursion into this roll clause 
        // and then use local_sector_ring_components[].
        if (local_sector_ring_components[0].IsVertex() && local_sector_ring_components[1].EdgePtr().EdgeIsCrease())
        {
          return this->InitializeFromSubdividedSectorComponents(center_vertex_sharpness, local_sector_ring_components);
        }

        break;
      }

      ON_SUBD_ERROR("Dart sectors must have exactly one crease in sector_ring_components[].");
      break;
    }

    const bool bCreaseOrCornerSector = ON_SubDVertexTag::Crease == center_vertex_tag || ON_SubDVertexTag::Corner == center_vertex_tag;
    const unsigned crease_dex[2] = {
      bCreaseOrCornerSector || ON_SubDVertexTag::Dart == center_vertex_tag ? 1U : ON_UNSET_UINT_INDEX,
      bCreaseOrCornerSector ? (sector_ring_component_count - 1U) : ON_UNSET_UINT_INDEX,
    };

    // ring_points[i] = sector_ring_components[i].SubdivisionPoint();
    ON_SimpleArray<ON_3dPoint> ring_points(sector_ring_component_count);

    // ring_sharpness[ei] = correctly oriented and subdividided sector_ring_components[2*ei+1].EdgeSharpness()
    ON_SimpleArray<ON_SubDEdgeSharpness> ring_sharpness(sector_ring_component_count/2);

    const ON_SubDEdge* e = nullptr;
    const ON_SubDFace* f = nullptr;
    for (unsigned i = 0U; i < sector_ring_component_count; ++i)
    {
      if (0U == i)
      {
        ring_points.Append(center_vertex->SubdivisionPoint());
      }
      else if (1 == (i % 2U))
      {
        // sector_ring_components[i] must be an edge with Direction() set so
        // that center_vertex = RelativeVertex(0)
        ON_SubDEdgePtr eptr = sector_ring_components[i].EdgePtr();
        if (center_vertex == eptr.RelativeVertex(1))
          eptr = eptr.Reversed();

        if (center_vertex != eptr.RelativeVertex(0))
          break;

        e = sector_ring_components[i].Edge();
        if (nullptr == e)
          break;
          
        if (bCreaseOrCornerSector && i + 1U == sector_ring_component_count)
        {
          if (nullptr != f && f->EdgeArrayIndex(e) >= (unsigned)f->m_edge_count)
            break;
        }

        if (i == crease_dex[0] || i == crease_dex[1])
        {
          if (false == e->IsCrease())
            break;
        }
        else
        {
          if (false == e->IsSmooth() || ((unsigned short)2) != e->m_face_count)
            break;
        }

        ring_points.Append(e->SubdivisionPoint());
        ring_sharpness.Append(eptr.RelativeSharpness(false).Subdivided(0));
      }
      else
      {
        // sector_ring_components[i] must be a face
        f = sector_ring_components[i].Face();
        if (nullptr == f || f->EdgeArrayIndex(e) >= (unsigned)f->m_edge_count)
          break;
        ring_points.Append(f->SubdivisionPoint());
      }
    }

    if (ring_points.UnsignedCount() != sector_ring_component_count)
    {
      ON_SUBD_ERROR("The edges and faces in sector_ring_components[] must alternate and be radially sorted.");
      break;
    }

    if (false == bCreaseOrCornerSector)
    {
      if (nullptr == f || f->EdgeArrayIndex(sector_ring_components[1].Edge()) >= (unsigned)f->m_edge_count)
        break;
    }

    const unsigned sector_face_count = (sector_ring_component_count - 1U) / 2U;

    if (false == this->Initialize(center_vertex_tag, ON_SubDEdgeSharpness::Sanitize(center_vertex_sharpness - 1.0, 0.0), sector_face_count, ring_points, ring_sharpness))
      break;

    if (sector_ring_component_count != this->SectorVertexCount())
      break;

    const unsigned subdivision_level = center_vertex->SubdivisionLevel() + 1U;

    const unsigned sector_vertex_count = this->SectorVertexCount();
    for (unsigned vi = 0; vi < sector_vertex_count; ++vi)
    {
      m_v[vi].SetSubdivisionLevel(subdivision_level);
    }

    const unsigned sector_edge_count = this->SectorEdgeCount();
    for (unsigned ei = 0; ei < sector_edge_count; ++ei)
    {
      m_e[ei].SetSubdivisionLevel(subdivision_level);
    }

    for (unsigned fi = 0; fi < sector_face_count; ++fi)
    {
      m_f[fi].SetSubdivisionLevel(subdivision_level);
    }

    // success
    return true;
  }

  this->Internal_Destroy();
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubDVertexQuadSector::InitializeFromSubdividedSectorIterator(const ON_SubDSectorIterator& sit)
{
  for (;;)
  {
    ON_SubDSectorIterator local_sit = sit;
    const ON_SubDVertex* center_vertex = local_sit.CenterVertex();
    if (nullptr == center_vertex)
      break;

    const ON_SubDVertexTag center_vertex_tag = center_vertex->m_vertex_tag;
    if (ON_SubDVertexTag::Unset == center_vertex_tag)
      break;

    if (center_vertex->m_face_count < ON_SubDVertexQuadSector::MinimumSectorFaceCount(center_vertex_tag))
      break;

    const unsigned max_component_count = 1U + center_vertex->m_edge_count + center_vertex->m_face_count;
    ON_SimpleArray<ON_SubDComponentPtr> sector_ring_components(max_component_count);


    if (ON_SubDVertexTag::Smooth != center_vertex_tag)
    {
      if (nullptr == local_sit.IncrementToCrease(-1))
        break;
    }

    const bool bSmoothOrDartSector = ON_SubDVertexTag::Smooth == center_vertex_tag || ON_SubDVertexTag::Dart == center_vertex_tag;
    sector_ring_components.Append(ON_SubDComponentPtr::Create(center_vertex));
    const ON_SubDEdge* first_e = local_sit.CurrentEdge(0);
    for (unsigned i = 0; sector_ring_components.UnsignedCount() < max_component_count; ++i)
    {
      ON_SubDEdgePtr eptr = local_sit.CurrentEdgePtr(0);
      const ON_SubDEdge* e = eptr.Edge();
      if (nullptr == e)
        break;
      sector_ring_components.Append(ON_SubDComponentPtr::Create(eptr));
      if (i > 0 && e->IsCrease())
        break;
      const ON_SubDFace* f = local_sit.CurrentFace();
      if (nullptr == f)
        break;
      sector_ring_components.Append(ON_SubDComponentPtr::Create(f));
      eptr = local_sit.CurrentEdgePtr(1);
      e = eptr.Edge();
      if (nullptr == e || first_e == e)
        break;
      if (e->IsCrease())
      {
        sector_ring_components.Append(ON_SubDComponentPtr::Create(eptr));
        break;
      }
      if (nullptr == local_sit.NextFace(ON_SubDSectorIterator::StopAt::AnyCrease))
        break;
    }

    if ((bSmoothOrDartSector ? 1U : 0U) == (sector_ring_components.UnsignedCount() % 2U))
      return this->InitializeFromSubdividedSectorComponents(center_vertex->VertexSharpness(), sector_ring_components);

    break;
  }

  this->Internal_Destroy();
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_SubDVertexQuadSector::Subdivide()
{
  const ON_SubDVertex* center_vertex = this->CenterVertex();
  if (nullptr == center_vertex)
    return ON_SUBD_RETURN_ERROR(false);
  const unsigned sector_face_count = this->SectorFaceCount();
  if (sector_face_count < 1U || sector_face_count != center_vertex->FaceCount())
    return ON_SUBD_RETURN_ERROR(false);

  const unsigned center_vertex_edge_count = this->CenterVertexEdgeCount();
  const bool bCreaseOrCornerSector = center_vertex->IsCreaseOrCorner();
  const bool bCreaseOrCornerOrDartSector = bCreaseOrCornerSector || center_vertex->IsDart();
  if (center_vertex_edge_count < 2U || center_vertex_edge_count != center_vertex->EdgeCount())
    return ON_SUBD_RETURN_ERROR(false);

  const unsigned sector_vertex_count = this->SectorVertexCount();
  const unsigned sector_edge_count = this->SectorEdgeCount();

  ON_SimpleArray<ON_SubDEdgeSharpness> s(center_vertex_edge_count);
  
  // Get subdivision points
  ON_SimpleArray<ON_3dPoint> R(sector_vertex_count);
  R.SetCount(sector_vertex_count);
  R[0] = center_vertex->SubdivisionPoint();
  for (unsigned ei = 0; ei < center_vertex_edge_count; ++ei)
  {
    R[1U + 2U * ei] = m_e[ei].SubdivisionPoint();
    s.Append(m_e[ei].Sharpness(false).Subdivided(0));
  }
  for (unsigned fi = 0; fi < sector_face_count; ++fi)
  {
    R[2U + 2U * fi] = m_f[fi].SubdivisionPoint();
  }

  const double crease_sector_vertex_sharpness0 = m_v[0].Internal_InteriorCreaseVertexSharpnessForExperts();

  double center_vertex_sharpness1 = 0.0;

  // subdivide the sector
  const unsigned subdivision_level = center_vertex->SubdivisionLevel() + 1U;
  for (unsigned vi = 0; vi < sector_vertex_count; ++vi)
  {
    m_v[vi].ClearSavedSubdivisionPoints(); // <- 2023-May-5 Dale Lear. This line fixes RH-74520.
    m_v[vi].SetControlNetPoint(R[vi],false);
    m_v[vi].SetSubdivisionLevel(subdivision_level);
    if (1 == vi)
      m_v[vi].m_vertex_tag = bCreaseOrCornerOrDartSector ? ON_SubDVertexTag::Crease : ON_SubDVertexTag::Smooth;
    // 2024-01-12, Pierre, RH-79544: Fix wrong vertex getting tagged Crease (was vi == center_vertex_edge_count)
    else if (vi + 1U == sector_vertex_count)  // or vi == 1 + 2 * (center_vertex_edge_count - 1)
      m_v[vi].m_vertex_tag = bCreaseOrCornerSector ? ON_SubDVertexTag::Crease : ON_SubDVertexTag::Smooth;
    else if (vi > 0U)
      m_v[vi].m_vertex_tag = ON_SubDVertexTag::Smooth;
    else
    {
      // vi = 0 and m_v[0] is the center vertex
      if (crease_sector_vertex_sharpness0 > 0.0)
      {
        // subdivide m_v[0] crease sector sharpness sharpness.
        const double crease_sector_vertex_sharpness1 = ON_SubDEdgeSharpness::Sanitize(crease_sector_vertex_sharpness0 - 1.0);
        if (crease_sector_vertex_sharpness1 > 0.0)
        {
          m_v[0].Internal_SetInteriorCreaseVertexSharpnessForExperts(crease_sector_vertex_sharpness1, false);
          if (center_vertex_sharpness1 < crease_sector_vertex_sharpness1)
            center_vertex_sharpness1 = crease_sector_vertex_sharpness1;
        }
      }
    }
  }

  this->m_maximum_edge_end_sharpness = 0.0;
  for (unsigned ei = 0; ei < sector_edge_count; ++ei)
  {
    m_e[ei].ClearSavedSubdivisionPoints();
    if (ei < center_vertex_edge_count)
    {
      if (0 == ei)
        m_e[ei].m_edge_tag = bCreaseOrCornerOrDartSector ? ON_SubDEdgeTag::Crease : ON_SubDEdgeTag::Smooth;
      else if (ei+1 == center_vertex_edge_count)
        m_e[ei].m_edge_tag = bCreaseOrCornerSector ? ON_SubDEdgeTag::Crease : ON_SubDEdgeTag::Smooth;
      else
        m_e[ei].m_edge_tag = ON_SubDEdgeTag::Smooth;
      m_e[ei].m_sector_coefficient[1] = 0.0;
      const double x = (ON_SubDEdgeTag::Smooth == m_e[ei].m_edge_tag) ? s[ei].MaximumEndSharpness() : 0.0;
      if (x > 0.0)
      {
        m_e[ei].SetSharpnessForExperts(s[ei]);
        if (this->m_maximum_edge_end_sharpness < x)
          this->m_maximum_edge_end_sharpness = x;
        const double y = m_e[ei].EndSharpness(&m_v[0]);
        if (center_vertex_sharpness1 < y)
          center_vertex_sharpness1 = y;
      }
      else
        m_e[ei].ClearSharpnessForExperts();
    }
    else
    {
      m_e[ei].m_edge_tag = ON_SubDEdgeTag::Smooth;
      m_e[ei].m_sector_coefficient[0] = 0.0;
      m_e[ei].m_sector_coefficient[1] = 0.0;
      m_e[ei].ClearSharpnessForExperts();
    }
    m_e[ei].SetSubdivisionLevel(subdivision_level);
  }

  this->SetCenterVertexSharpness(center_vertex_sharpness1);

  for (unsigned fi = 0; fi < sector_face_count; ++fi)
  {
    m_f[fi].ClearSavedSubdivisionPoints();
    m_f[fi].SetSubdivisionLevel(subdivision_level);
  }

  return true;
}

bool ON_SubDVertexQuadSector::SubdivideUntilSharpnessIsZero()
{
  unsigned int subdivision_count = 0;
  return SubdivideUntilSharpnessIsZero(subdivision_count);
}

bool ON_SubDVertexQuadSector::SubdivideUntilSharpnessIsZero(
  unsigned int& subdivision_count
)
{
  bool rc = true;
  double maxs = this->MaximumSharpness();
  subdivision_count = 0;
  if (maxs > 0.0)
  {
    // for(i < n) used to prevent infinite looping when this content is not valid.
    const unsigned n = (unsigned)ceil(maxs);
    for (unsigned i = 0; i < n && maxs > 0.0 && rc; ++i)
    {
      rc = Subdivide();
      if (rc)
        ++subdivision_count;
      maxs = this->MaximumSharpness();
    }
    if (rc && false == (0.0 == maxs))
      rc = false;
  }
  return rc;
}

const ON_SubDVertexQuadSector ON_SubDVertexQuadSector::Empty;

const ON_SubDVertex* ON_SubDVertexQuadSector::CenterVertex() const
{
  const ON_SubDVertex* center_vertex
    = (this->m_sector_face_count > 0 && nullptr != m_heap && m_heap == (void*)m_v)
    ? &m_v[0]
    : nullptr;
  return center_vertex;
}

ON_SubDVertexTag ON_SubDVertexQuadSector::CenterVertexTag() const
{
  const ON_SubDVertex* center_vertex = this->CenterVertex();
  return (nullptr != center_vertex) ? center_vertex->m_vertex_tag : ON_SubDVertexTag::Unset;
}

unsigned ON_SubDVertexQuadSector::CenterVertexEdgeCount() const
{
  return m_center_vertex_edge_count;
}

unsigned ON_SubDVertexQuadSector::SectorCreaseEdgeCount() const
{
  return ON_SubDVertexQuadSector::SectorCreaseEdgeCount(this->CenterVertexTag());
}

unsigned ON_SubDVertexQuadSector::SectorCreaseEdgeCount(ON_SubDVertexTag center_vertex_tag)
{
  switch (center_vertex_tag)
  {
  case ON_SubDVertexTag::Unset:
    break;
  case ON_SubDVertexTag::Smooth:
    return 0U;
    break;
  case ON_SubDVertexTag::Crease:
    return 2U;
    break;
  case ON_SubDVertexTag::Corner:
    return 2U;
    break;
  case ON_SubDVertexTag::Dart:
    return 1U;
    break;
  default:
    break;
  }
  return 0U;
}


unsigned ON_SubDVertexQuadSector::SectorFaceCount() const
{
  return m_sector_face_count;
}

unsigned ON_SubDVertexQuadSector::SectorVertexCount() const
{
  return 1U + m_center_vertex_edge_count + m_sector_face_count;
}

unsigned ON_SubDVertexQuadSector::SectorEdgeCount() const
{
  return m_center_vertex_edge_count + 2 * m_sector_face_count;
}

unsigned ON_SubDVertexQuadSector::SubdivisionLevel() const
{
  const ON_SubDVertex* center_vertex = this->CenterVertex();
  return (nullptr != center_vertex) ? center_vertex->SubdivisionLevel() : 0U;
}


static unsigned int Internal_MarkStuffAndMaybeMoveVertices(
  const ON_SubD& subd,
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  const ON_Xform* xform,
  ON_SubDComponentLocation component_location,
  bool bExtrusionMarking,
  bool bExtrudeBoundaries,
  unsigned int& list_vertex_count,
  unsigned int& list_edge_count,
  unsigned int& list_face_count
)
{
  list_vertex_count = 0;
  list_edge_count = 0;
  list_face_count = 0;

  if (false == bExtrusionMarking)
    bExtrudeBoundaries = false;

  const bool bTransform 
    = false == bExtrusionMarking
    && nullptr != xform 
    && xform->IsValidAndNotZeroAndNotIdentity()
    ;

  if ((bTransform ? 1 : 0) == (bExtrusionMarking ? 1 : 0))
  {
    ON_SUBD_ERROR("Invalid input.");
    return 0;
  }

  unsigned int marked_vertex_count = 0;
  //unsigned int potential_isolated_vertex_count = 0;
  unsigned int potential_isolated_edge_count = 0;

  ON_SimpleArray<unsigned int> moved_vertices;

  if (bExtrusionMarking && 0 == cptr_count && nullptr == cptr_list)
  {
    // entire subd is being extruded
    ON_SubDFaceIterator fit(subd);
    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      ++list_face_count;
      f->m_status.SetRuntimeMark();
      const unsigned int face_vertex_count = f->m_edge_count;
      for (unsigned int fvi = 0; fvi < face_vertex_count; ++fvi)
      {
        // used when extruding selected components
        const ON_SubDEdge* e = f->Edge(fvi);
        if (nullptr != e && false == e->m_status.RuntimeMark())
          e->m_status.SetRuntimeMark();
        const ON_SubDVertex* v = f->Vertex(fvi);
        if (nullptr != v && false == v->m_status.RuntimeMark())
        {
          v->m_status.SetRuntimeMark();
          ++marked_vertex_count;
        }
      }
    }
  }
  else
  {
    for (size_t i = 0; i < cptr_count; i++)
    {
      switch (cptr_list[i].ComponentType())
      {
      case ON_SubDComponentPtr::Type::Vertex:
        {
          const ON_SubDVertex* v = cptr_list[i].Vertex();
          if (nullptr == v)
            continue;
          ++list_vertex_count;
          if (v->m_status.RuntimeMark())
            continue;
          if (bTransform)
          {
            v->m_status.SetRuntimeMark();
            if (bTransform)
            {
              const_cast<ON_SubDVertex*>(v)->Transform(false, *xform);
              moved_vertices.Append(v->m_id);
            }
            ++marked_vertex_count;
          }
        }
        break;

      case ON_SubDComponentPtr::Type::Edge:
        {
          const ON_SubDEdge* e = cptr_list[i].Edge();
          if (nullptr == e)
            continue;
          ++list_edge_count;
          if (e->Mark())
            continue;
          if (bTransform)
          {
            e->SetMark();
            for (unsigned int evi = 0; evi < 2; ++evi)
            {
              const ON_SubDVertex* v = e->m_vertex[evi];
              if (nullptr != v && false == v->Mark())
              {
                v->SetMark();
                const_cast<ON_SubDVertex*>(v)->Transform(false, *xform);
                moved_vertices.Append(v->m_id);
                ++marked_vertex_count;
              }
            }
          }
          else
          {
            if (bExtrudeBoundaries && 1 == e->m_face_count && nullptr != e->m_face2[0].Face())
            {
              // It's a boundary edge and we will mark it and its vertices later after we make sure
              // a face touching this edge isn't in the cptr_list[].
              ++potential_isolated_edge_count;
            }
            // otherwise ignore interior edges
          }
        }
        break;

      case ON_SubDComponentPtr::Type::Face:
        {
          const ON_SubDFace* f = cptr_list[i].Face();
          if (nullptr != f && false == f->Mark())
          {
            ++list_face_count;
            f->SetMark();
            const unsigned int face_vertex_count = f->m_edge_count;
            for (unsigned int fvi = 0; fvi < face_vertex_count; ++fvi)
            {
              if (bExtrusionMarking)
              {
                // used when extruding selected components
                const ON_SubDEdge* e = f->Edge(fvi);
                if (nullptr != e && false == e->m_status.RuntimeMark())
                  e->m_status.SetRuntimeMark();
              }
              const ON_SubDVertex* v = f->Vertex(fvi);
              if (nullptr != v && false == v->m_status.RuntimeMark())
              {
                v->m_status.SetRuntimeMark();
                if (bTransform)
                {
                  const_cast<ON_SubDVertex*>(v)->Transform(false, *xform);
                  moved_vertices.Append(v->m_id);
                }
                ++marked_vertex_count;
              }
            }
          }
        }
        break;
              
      case ON_SubDComponentPtr::Type::Unset:
        break;
      }
    }

    if (bExtrusionMarking && potential_isolated_edge_count > 0)
    {
      for (size_t i = 0; i < cptr_count; i++)
      {
        if (ON_SubDComponentPtr::Type::Edge != cptr_list[i].ComponentType())
          continue;

        const ON_SubDEdge* e = cptr_list[i].Edge();
        if (nullptr == e)
          continue;

        if (e->Mark())
          continue; // this edge us part of a boundary belonging to a face in  cptr_list[]

        if (1 == e->m_face_count && nullptr != e->m_face2[0].Face())
        {
          // this boundary edge was explicitly picked its attached face was not picked.
          // It will be extruded to a face.
          e->SetMark();
          for (unsigned int evi = 0; evi < 2; ++evi)
          {
            const ON_SubDVertex* v = e->m_vertex[evi];
            if (nullptr != v && false == v->Mark())
            {
              v->SetMark();
              ++marked_vertex_count;
            }
          }
          if (0 == --potential_isolated_edge_count)
            break;
        }
      }
    }
  }

  const bool bSymmetryIsSet =
    false
    ;

  bool bChangePreservesSymmetry = false;


  if (bTransform)
  {
    if  ( bSymmetryIsSet || 3 * marked_vertex_count >= subd.VertexCount() )
    {
      subd.ClearEvaluationCache();
    }
    else
    {
      ON_SubDVertexIterator vit(subd);
      for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
      {
        if (v->Mark())
          v->VertexModifiedNofification();
      }
      subd.UpdateEdgeSectorCoefficients(true);
    }
    const_cast<ON_SubD&>(subd).ChangeGeometryContentSerialNumberForExperts(bChangePreservesSymmetry);
  }

  return marked_vertex_count;
}

static unsigned int Internal_MarkExtrudeComponents(
  const ON_SubD& subd,
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  bool bExtrudeBoundaries,
  unsigned int& list_vertex_count,
  unsigned int& list_edge_count,
  unsigned int& list_face_count
)
{
  const bool bExtrusionMarking = true;
  const int marked_vertex_count = Internal_MarkStuffAndMaybeMoveVertices(
    subd,
    cptr_list,
    cptr_count,
    nullptr,
    ON_SubDComponentLocation::Unset,
    bExtrusionMarking,
    bExtrudeBoundaries,
    list_vertex_count,
    list_edge_count,
    list_face_count
  );

  // It appears the best "heuristic" is to require the user to pick edges and faces.
  // isolated vertices will be ignored and no attempts to guess if a user wants to
  // extrude the boundary of a face (all its edges) or the face itself.

  // lots of delete "heuristic" code here :)

  return marked_vertex_count;
}

static unsigned int Internal_TransformComponents(
  const ON_SubD& subd,
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  const ON_Xform& xform,
  ON_SubDComponentLocation component_location
)
{
  // This version is used by SDK tools that simply transform components in cptr_list
  if (false == xform.IsValidAndNotZeroAndNotIdentity())
    return 0;

  const bool bExtrusionMarking = false;
  unsigned int list_vertex_count = 0;
  unsigned int list_edge_count = 0;
  unsigned int list_face_count = 0;

  return Internal_MarkStuffAndMaybeMoveVertices(
    subd,
    cptr_list,
    cptr_count,
    &xform,
    component_location,
    bExtrusionMarking, false,
    list_vertex_count,
    list_edge_count,
    list_face_count
  );
}



unsigned int ON_SubD::TransformComponents(
  const ON_Xform& xform,
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  ON_SubDComponentLocation component_location
)
{
  if ( 
    false == xform.IsValidAndNotZeroAndNotIdentity()
    || cptr_count <= 0
    || nullptr == cptr_list
    )
    return 0;

  ON_SimpleArray<const ON_SubDComponentBase*> marked_components;
  const bool bRestoreMarks = ClearComponentMarks(true, true, true, &marked_components) > 0;

  const unsigned int v_count = Internal_TransformComponents(*this, cptr_list, cptr_count, xform, component_location);

  if (bRestoreMarks)
    SetComponentMarks(true, marked_components);

  return (v_count > 0);
}


unsigned int ON_SubD::ExtrudeComponents(
  const ON_Xform& xform,
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count
)
{
  const bool bExtrudeBoundaries = true;
  const bool bPermitNonManifoldEdgeCreation = false;
  return ExtrudeComponents(xform, ci_list, ci_count, bExtrudeBoundaries, bPermitNonManifoldEdgeCreation);
}


unsigned int ON_SubD::ExtrudeComponents(
  const ON_Xform& xform,
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count,
  bool bExtrudeBoundaries,
  bool bPermitNonManifoldEdgeCreation
)
{
  if ( 
    false == xform.IsValidAndNotZeroAndNotIdentity()
    || xform.IsIdentity()
    || ci_count <= 0
    || nullptr == ci_list
    )
    return 0;

  ON_SimpleArray<ON_SubDComponentPtr> cptr_list;
  if (ComponentPtrFromComponentIndex(ci_list,ci_count,cptr_list) <= 0)
    return true; // nothing to extrude

  return ExtrudeComponents(
    xform,
    cptr_list.Array(),
    cptr_list.UnsignedCount(),
    bExtrudeBoundaries,
    bPermitNonManifoldEdgeCreation
    );
}

/*
ON_Internal_ExtrudedVertex manages a vertex that is extruded into a "side" edge during the extrusion process.
*/
class ON_Internal_ExtrudedVertex
{
public:
  ON_Internal_ExtrudedVertex() = default;
  ~ON_Internal_ExtrudedVertex() = default;
  ON_Internal_ExtrudedVertex(const ON_Internal_ExtrudedVertex&) = default;
  ON_Internal_ExtrudedVertex& operator=(const ON_Internal_ExtrudedVertex&) = default;

  static const ON_Internal_ExtrudedVertex Unset;

  /////////////////////////////////////////////////////////////
  //
  // Up to 2 extruded edges that share this extruded vertex.
  // In rare cases there may be more. This information is used only
  // to speed up the setting of m_side_group_id.
  // 
  class ON_Internal_ExtrudedEdge* m_extruded_edges[2] = {};
  unsigned char m_extruded_edges_count = 0; // 0, 1, 2, or 3. 3 means 3 or more

  /////////////////////////////////////////////////////////////
  //
  // State of the vertex before the extrusion was applied
  // 

  // tag the original vertex had before the extrusion was performed.
  ON_SubDVertexTag m_initial_vertex_tag = ON_SubDVertexTag::Unset;

  // in complicated cases when the initial vertex is a crease/corner, m_connecting_edge_tag may be set to crease.
  ON_SubDEdgeTag m_connecting_edge_tag = ON_SubDEdgeTag::Unset;

  // id of the original vertex - used to sort and search an array of ON_Internal_ExtrudedVertex elements.
  unsigned int m_initial_vertex_id = 0;

  //// The face counts do not include the side faces created during the extrusion process.
  //unsigned short m_moved_face_count = 0;
  //unsigned short m_stationary_face_count = 0;

  //// Edge counts do not include the side edge "m_connecting_edge" that is created during the extrusion process.
  //// There are three sets of edges
  ////   Existing edges that will be extruded into side faces.
  ////   Existing edges that will be moved during the extrusion process.
  ////   Existing edges that will be stationary during the extrusion process.
  //unsigned short m_extruded_edge_count = 0; // these are edges in the new_sides[] array
  //unsigned short m_wire_edge_count = 0; // moved or stationary
  //unsigned short m_moved_crease_edge_count = 0;
  //unsigned short m_moved_smooth_edge_count = 0;
  //unsigned short m_stationary_crease_edge_count = 0;
  //unsigned short m_stationary_smooth_edge_count = 0;
  
  /////////////////////////////////////////////////////////////
  //
  // Additional information that will be created or modified during the extrusion.
  // 

  // Used to sort the sides into groups of edges that are connected
  unsigned m_side_group_id = 0;

  // This is the vertex in the original object. (This vertex is moved).
  ON_SubDVertex* m_original_vertex = nullptr;

  // This vertex is new. It is a copy of the original vertex and remains at the original location.
  ON_SubDVertex* m_copied_vertex = nullptr;

  // m_connecting_edge begins at m_copied_vertex and terminates at m_original_vertex;
  ON_SubDEdge* m_connecting_edge = nullptr;
  

  bool SetFromInitialVertex(ON_SubDVertex* initial_vertex)
  {
    *this = ON_Internal_ExtrudedVertex::Unset;

    if ( nullptr == initial_vertex || 0 == initial_vertex->m_id )
      return false;

    // validate initial_vertex topology information so subsequent code assumptions are met.
    if (initial_vertex->m_edge_count <= 0)
      return false;
    if (initial_vertex->m_edge_count > initial_vertex->m_edge_capacity)
      return false;
    if (nullptr == initial_vertex->m_edges)
      return false;
    for (unsigned short vei = 0; vei < initial_vertex->m_edge_count; ++vei)
    {
      const ON_SubDEdgePtr eptr = initial_vertex->m_edges[vei];
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
      if (nullptr == e || nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
        return false;
      if (e->m_vertex[0]->m_id == e->m_vertex[1]->m_id)
        return false;
      if (initial_vertex != e->m_vertex[ON_SUBD_EDGE_DIRECTION(eptr.m_ptr)])
        return false;
    }

    if (initial_vertex->m_face_count > 0)
    {
      if (initial_vertex->m_face_count > initial_vertex->m_face_capacity)
        return false;
      if (nullptr == initial_vertex->m_faces)
        return false;
    }

    m_initial_vertex_tag = initial_vertex->m_vertex_tag;
    m_initial_vertex_id = initial_vertex->m_id;
    m_original_vertex = initial_vertex;

    return true;
  }

  bool SetConnectingEdgeTag();  

  bool ExtrudeVertex(ON_SubD& subd, bool bIsInset, const ON_Xform& xform)
  {
    if (nullptr != m_copied_vertex)
      return ON_SUBD_RETURN_ERROR(false);

    if (nullptr == m_original_vertex)
      return ON_SUBD_RETURN_ERROR(false);

    const ON_3dPoint P = m_original_vertex->ControlNetPoint();
    for (;;)
    {
      // transform the original vertex
      m_original_vertex->m_vertex_tag = ON_SubDVertexTag::Unset;

      if (false == bIsInset)
      {
        if (false == m_original_vertex->Transform(false, xform))
          break;
      }

      m_copied_vertex = subd.AddVertex(ON_SubDVertexTag::Unset, P);
      if (nullptr == m_copied_vertex)
        break;

      const unsigned short face_count = m_original_vertex->m_face_count;
      if (face_count > 0 && false == subd.GrowVertexFaceArray(m_copied_vertex, face_count))
        break;

      if (false == subd.GrowVertexEdgeArray(m_copied_vertex, m_original_vertex->m_edge_count + 1))
        break;

      // edge from m_copied_vertex (stationary) to m_original_vertex (moved).
      m_connecting_edge = subd.AddEdge(m_connecting_edge_tag, m_copied_vertex, m_original_vertex);
      if (nullptr == m_connecting_edge)
        break;

      //if (bMarkedInteriorCrease && bUnmarkedInteriorCrease)
      //  m_connecting_edge->m_edge_tag = ON_SubDEdgeTag::Crease;

      for (unsigned short vei = 0; vei < m_original_vertex->m_edge_count; ++vei)
      {
        ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_original_vertex->m_edges[vei].m_ptr);
        if (nullptr != e)
          e->UnsetSectorCoefficientsForExperts();
      }

      return true;
    }

    if (nullptr != m_copied_vertex)
    {
      ON_SubDComponentPtr cptr = m_copied_vertex->ComponentPtr();
      subd.DeleteComponentsForExperts(&cptr, 1, false, false, false);
      m_copied_vertex = nullptr;
    }

    ON_SUBD_ERROR("Unable to extrude m_original_vertex");
    m_original_vertex->m_vertex_tag = this->m_initial_vertex_tag;
    m_original_vertex->SetControlNetPoint(P,false);
    return false;
  }

  bool AttachUnmarkedFacesToCopiedVertex()
  {
    if (nullptr == m_copied_vertex)
      return ON_SUBD_RETURN_ERROR(false);
    if (0 != m_copied_vertex->m_face_count)
      return ON_SUBD_RETURN_ERROR(false);
    if (nullptr == m_original_vertex)
      return ON_SUBD_RETURN_ERROR(false);
    if (0 == m_original_vertex->m_face_count)
      return true; // wire edge case

    const unsigned short face_count = m_original_vertex->m_face_count;

    if (face_count > m_original_vertex->m_face_capacity)
      return ON_SUBD_RETURN_ERROR(false);
    if (face_count > m_copied_vertex->m_face_capacity)
      return ON_SUBD_RETURN_ERROR(false);

    // marked faces remain attached to m_original_vertex
    // unmarked faces are attached to m_copied_vertex 
    m_original_vertex->m_face_count = 0;
    for (unsigned short vfi = 0; vfi < face_count; vfi++)
    {
      const ON_SubDFace* f = m_original_vertex->m_faces[vfi];
      if (nullptr == f)
        continue;
      ON_SubDVertex* v
        = (f->Mark())
        ? m_original_vertex
        : m_copied_vertex;
      v->m_faces[v->m_face_count] = f;
      v->m_face_count++;
    }
    for (unsigned short vfi = m_original_vertex->m_face_count; vfi < face_count; ++vfi)
      m_original_vertex->m_faces[vfi] = nullptr;

    return true;
  }


  void UndoAttachUnmarkedFacesToCopiedVertex()
  {
    // This is used to resort the subd to a somewhat valid state after a critical error occurs
    if (nullptr == m_copied_vertex)
      return;
    if (0 == m_copied_vertex->m_face_count)
      return;
    if (nullptr == m_original_vertex)
      return;
    // Move faces from m_copied_vertex back to m_original_vertex (which is where they started).
    for (unsigned short vfi = 0; vfi < m_copied_vertex->m_face_count; vfi++)
    {
      const ON_SubDFace* f = m_copied_vertex->m_faces[vfi];
      if (nullptr == f)
        continue;
      m_copied_vertex->m_faces[vfi] = nullptr;
      if (m_original_vertex->m_face_count < m_original_vertex->m_face_capacity)
      {
        m_original_vertex->m_faces[m_original_vertex->m_face_count] = f;
        m_original_vertex->m_face_count++;
      }
    }
    m_copied_vertex->m_face_count = 0;
  }
   
  bool AddExtrudedEdgeReference(
    class ON_Internal_ExtrudedEdge* extruded_edge,
    bool bSetExtrudedEdgeToo
  );  

  static int CompareInitialVertexId(
    const ON_Internal_ExtrudedVertex* lhs,
    const ON_Internal_ExtrudedVertex* rhs
  );

  void SetBothVertexTags(ON_SubDVertexTag vertex_tag)
  {
    if (nullptr != m_original_vertex)
      m_original_vertex->m_vertex_tag = vertex_tag;
    if (nullptr != m_copied_vertex)
      m_copied_vertex->m_vertex_tag = vertex_tag;
    if (nullptr != m_connecting_edge)
    {
      switch (vertex_tag)
      {
      case ON_SubDVertexTag::Unset:
        m_connecting_edge->m_edge_tag = ON_SubDEdgeTag::Unset;
        break;
      case ON_SubDVertexTag::Smooth:
        m_connecting_edge->m_edge_tag = ON_SubDEdgeTag::Smooth;
        break;
      case ON_SubDVertexTag::Crease:
        m_connecting_edge->m_edge_tag = ON_SubDEdgeTag::SmoothX;
        break;
      case ON_SubDVertexTag::Corner:
        m_connecting_edge->m_edge_tag = ON_SubDEdgeTag::Crease;
        break;
      case ON_SubDVertexTag::Dart:
        m_connecting_edge->m_edge_tag = ON_SubDEdgeTag::SmoothX;
        break;
      default:
        m_connecting_edge->m_edge_tag = ON_SubDEdgeTag::Unset;
        break;
      }
    }
  }

  bool IsValidTopology(bool bCheckCopies) const;

};

const ON_Internal_ExtrudedVertex ON_Internal_ExtrudedVertex::Unset;

/*
ON_Internal_ExtrudedVertex manages an edge that is extruded into a "side" face extrusion process.
*/
class ON_Internal_ExtrudedEdge
{
public:
  ON_Internal_ExtrudedEdge() = default;
  ~ON_Internal_ExtrudedEdge() = default;
  ON_Internal_ExtrudedEdge(const ON_Internal_ExtrudedEdge&) = default;
  ON_Internal_ExtrudedEdge& operator=(const ON_Internal_ExtrudedEdge&) = default;

  static const ON_Internal_ExtrudedEdge Unset;

  // tag m_original_edge had before the extrusion was performed.
  ON_SubDEdgeTag m_initial_edge_tag = ON_SubDEdgeTag::Unset;

  unsigned int m_initial_vertex_id[2] = {};

  unsigned int m_initial_edge_face_count = 0;

  // Used to sort the sides into groups of edges that are connected
  unsigned m_side_group_id = 0;

  // This is the edge in the original object. (This edge is moved).
  ON_SubDEdge* m_original_edge = nullptr;

  // This edge is new. It is a copy of the original edge and remains at the original location.
  ON_SubDEdge* m_copied_edge = nullptr;

  // m_extruded_vertex[0]->m_connecting_edge begins at m_copied_edge->m_vertex[0] and terminates at m_original_edge->m_vertex[0]
  // m_extruded_vertex[1]->m_connecting_edge begins at m_copied_edge->m_vertex[1] and terminates at m_original_edge->m_vertex[1]
  ON_Internal_ExtrudedVertex* m_extruded_vertex[2] = {};

  // This is the new "side" quad with boundary made from the 4 edges above.
  ON_SubDFace* m_new_face = nullptr;

  static int CompareSideGroupId(const ON_Internal_ExtrudedEdge* lhs, const ON_Internal_ExtrudedEdge* rhs);

  bool SetFromInitialEdge(
    ON_SubDEdge* initial_edge
  )
  {
    *this = ON_Internal_ExtrudedEdge::Unset;

    if (nullptr == initial_edge)
      return false;
    if (nullptr == initial_edge->m_vertex[0] || nullptr == initial_edge->m_vertex[1] || initial_edge->m_vertex[0]->m_id == initial_edge->m_vertex[1]->m_id)
      return false;

    // validate edge / face topology information - corrupt information will cause great difficulties during the extrusion process
    const ON_SubDFacePtr* fptr = initial_edge->m_face2;
    for (unsigned short efi = 0; efi < initial_edge->m_face_count; ++efi, ++fptr)
    {
      if (2 == efi)
      {
        fptr = initial_edge->m_facex;
        if (nullptr == fptr)
          return false; // corrupt edge / face topology information
        if (initial_edge->m_facex_capacity < initial_edge->m_face_count - 2)
          return false; // corrupt edge / face topology information
      }
      const ON_SubDFace* f = ON_SUBD_FACE_POINTER(fptr->m_ptr);
      if (nullptr == f || f->m_edge_count < 3)
        return false; // corrupt edge / face topology information

      bool bFoundInitialEdge = false;
      const ON_SubDEdgePtr* eptr = f->m_edge4;
      for (unsigned short fei = 0; fei < f->m_edge_count; ++fei, ++eptr)
      {
        if (4 == fei)
        {
          eptr = f->m_edgex;
          if (nullptr == eptr)
            return false; // corrupt edge / face topology information
          if (f->m_edgex_capacity < f->m_edge_count - 4)
            return false; // corrupt edge / face topology information
        }
        const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr->m_ptr);
        if (nullptr == e)
          return false;
        if (nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1] || e->m_vertex[0]->m_id == e->m_vertex[1]->m_id)
          return false;
        if (e == initial_edge)
        {
          if (bFoundInitialEdge)
            return false;
          bFoundInitialEdge = true;
          if (ON_SUBD_EDGE_DIRECTION(eptr->m_ptr) != ON_SUBD_FACE_DIRECTION(fptr->m_ptr))
            return false;
        }
      }
      if (false == bFoundInitialEdge)
        return false;
    }

    m_initial_edge_tag = initial_edge->m_edge_tag;
    m_initial_vertex_id[0] = initial_edge->m_vertex[0]->m_id;
    m_initial_vertex_id[1] = initial_edge->m_vertex[1]->m_id;
    m_initial_edge_face_count = initial_edge->m_face_count;
    m_original_edge = initial_edge;

    return true;
  }

  ON_SubDFace* ExtrudeFace(ON_SubD& subd);

  const ON_Internal_ExtrudedVertex* ExtrudedVertex(ON__UINT_PTR evi) const
  {
    return (0 == evi || 1 == evi) ? m_extruded_vertex[evi] : nullptr;
  }

  /// Returns "side" edge created by extruding the reference vertex
  ON_SubDEdge* ConnectingEdge(ON__UINT_PTR evi) const
  {
    const ON_Internal_ExtrudedVertex* extruded_vertex = ExtrudedVertex(evi);
    return (nullptr != extruded_vertex) ? extruded_vertex->m_connecting_edge : nullptr;
  }

  ON_SubDEdge* CreateCopiedEdge(ON_SubD& subd)
  {
    if (nullptr != m_copied_edge)
      return ON_SUBD_RETURN_ERROR(nullptr);
    ON_SubDVertex* copied_vertex[2] = {};
    for (unsigned evi = 0; evi < 2; evi++)
    {
      if (nullptr == m_extruded_vertex[evi])
        return ON_SUBD_RETURN_ERROR(nullptr);
      copied_vertex[evi] = m_extruded_vertex[evi]->m_copied_vertex;
      if (nullptr == copied_vertex[evi])
        return ON_SUBD_RETURN_ERROR(nullptr);
    }
    m_copied_edge = subd.AddEdge(ON_SubDEdgeTag::Unset, copied_vertex[0], copied_vertex[1]);
    if (nullptr == m_copied_edge)
      return ON_SUBD_RETURN_ERROR(nullptr);
    m_original_edge->m_edge_tag = ON_SubDEdgeTag::Unset;
    return m_copied_edge;
  }

  /// returns true if an unset vertex pair had its id set which means recursive id setting should continue.
  bool SetSideGroupId(unsigned side_group_id)
  {
    if (m_side_group_id > 0)
      return false;
    bool rc = false;
    m_side_group_id = side_group_id;
    for (unsigned evi = 0; evi < 2; ++evi)
    {
      if (nullptr != m_extruded_vertex[evi] && 0 == m_extruded_vertex[evi]->m_side_group_id)
      {
        rc = true;
        m_extruded_vertex[evi]->m_side_group_id = side_group_id;
      }
    }
    return rc;
  }

  /// Returns true if an unset vertex pair had its id set which means recursive id setting should continue.
  bool SetSideGroupIdFromVertexPairs()
  {
    if (m_side_group_id > 0)
      return false;
    for (unsigned evi = 0; evi < 2; ++evi)
    {
      if (nullptr != m_extruded_vertex[evi] && m_extruded_vertex[evi]->m_side_group_id > 0)
        return SetSideGroupId(m_extruded_vertex[evi]->m_side_group_id);
    }
    return false;
  }

  bool InitialCrease() const
  {
    return (ON_SubDEdgeTag::Crease == m_initial_edge_tag);
  }

  bool InitialCreaseWithCorner() const
  {
    if (ON_SubDEdgeTag::Crease == m_initial_edge_tag)
    {
      for (unsigned evi = 0; evi < 2; ++evi)
      {
        if (nullptr != m_extruded_vertex[evi] && ON_SubDVertexTag::Corner == m_extruded_vertex[evi]->m_initial_vertex_tag)
          return true;
      }
    }
    return false;
  }

  void SetBothEdgeTags(ON_SubDEdgeTag edge_tag)
  {
    if (ON_SubDEdgeTag::Crease == edge_tag)
    {
      if (nullptr != m_original_edge)
        m_original_edge->m_edge_tag = ON_SubDEdgeTag::Crease;
      if (nullptr != m_copied_edge)
        m_copied_edge->m_edge_tag = ON_SubDEdgeTag::Crease;
      for (unsigned evi = 0; evi < 2; ++evi)
      {
        if (nullptr != m_extruded_vertex[evi] && ON_SubDEdgeTag::Unset == m_extruded_vertex[evi]->m_connecting_edge->m_edge_tag)
        {
          if (ON_SubDVertexTag::Corner == m_extruded_vertex[evi]->m_initial_vertex_tag)
            m_extruded_vertex[evi]->SetBothVertexTags(ON_SubDVertexTag::Corner);
          else if (nullptr != m_extruded_vertex[evi]->m_connecting_edge)
            m_extruded_vertex[evi]->m_connecting_edge->m_edge_tag = ON_SubDEdgeTag::Smooth;
        }
      }
    }
  }

  bool IsValidTopology(
    bool bCheckCopies
  ) const;
};

static bool Internal_IsNotValidExtrudedTopology()
{
  return ON_SUBD_RETURN_ERROR(false);
}

bool ON_Internal_ExtrudedVertex::IsValidTopology(bool bCheckCopies) const
{
  if (nullptr == this->m_original_vertex)
    return Internal_IsNotValidExtrudedTopology();
  if (this->m_initial_vertex_id != this->m_original_vertex->m_id)
    return Internal_IsNotValidExtrudedTopology();
  if (this->m_extruded_edges_count == 0)
    return Internal_IsNotValidExtrudedTopology();
  if (bCheckCopies && nullptr == this->m_copied_vertex)
    return Internal_IsNotValidExtrudedTopology();
  for (unsigned vei = 0; vei < 2 && vei < this->m_extruded_edges_count; ++vei)
  {
    if (nullptr == this->m_extruded_edges[vei])
      return Internal_IsNotValidExtrudedTopology();
    const ON_Internal_ExtrudedEdge& extruded_edge = *this->m_extruded_edges[vei];
    if (nullptr == extruded_edge.m_original_edge)
      return Internal_IsNotValidExtrudedTopology();
    const unsigned evi = (this->m_original_vertex == extruded_edge.m_original_edge->m_vertex[0]) ? 0 : 1;
    if (this->m_initial_vertex_id != extruded_edge.m_initial_vertex_id[evi])
      return Internal_IsNotValidExtrudedTopology();
    for (unsigned k = 0; k < (bCheckCopies ? 2U : 1U); ++k)
    {
      const ON_SubDEdge* e = (0 == k) ? extruded_edge.m_original_edge : extruded_edge.m_copied_edge;
      if (nullptr == e)
        return Internal_IsNotValidExtrudedTopology();
      if (e->m_vertex[0] == e->m_vertex[1])
        return Internal_IsNotValidExtrudedTopology();
      const ON_SubDVertex* v = (0 == k) ? this->m_original_vertex : this->m_copied_vertex;
      if (nullptr == v)
        return Internal_IsNotValidExtrudedTopology();
      if (e->m_vertex[evi] != v)
        return Internal_IsNotValidExtrudedTopology();
    }
    if (extruded_edge.m_side_group_id != this->m_side_group_id)
      return Internal_IsNotValidExtrudedTopology();
  }

  return true;
}

bool ON_Internal_ExtrudedEdge::IsValidTopology(
  bool bCheckCopies
) const
{
  if (nullptr == m_original_edge)
    return Internal_IsNotValidExtrudedTopology();

  if (bCheckCopies && nullptr == m_copied_edge)
    return Internal_IsNotValidExtrudedTopology();

  for (unsigned evi = 0; evi < 2; ++evi)
  {
    if (nullptr == this->m_extruded_vertex[evi])
      return Internal_IsNotValidExtrudedTopology();
    const ON_Internal_ExtrudedVertex& extruded_vertex = *this->m_extruded_vertex[evi];
    for (unsigned k = 0; k < (bCheckCopies ? 2U : 1U); ++k)
    {
      const ON_SubDEdge* e = (0 == k) ? this->m_original_edge : this->m_copied_edge;
      if (nullptr == e)
        return Internal_IsNotValidExtrudedTopology();
      const ON_SubDVertex* v = (0 == k) ? extruded_vertex.m_original_vertex : extruded_vertex.m_copied_vertex;
      if (nullptr == v)
        return Internal_IsNotValidExtrudedTopology();
      if (e->m_vertex[evi] != v)
        return Internal_IsNotValidExtrudedTopology();
      if (v->EdgeArrayIndex(e) >= v->m_edge_count)
        return Internal_IsNotValidExtrudedTopology();
    }
    if (extruded_vertex.m_initial_vertex_id != extruded_vertex.m_original_vertex->m_id)
      return Internal_IsNotValidExtrudedTopology();
    if (extruded_vertex.m_initial_vertex_id != this->m_initial_vertex_id[evi])
      return Internal_IsNotValidExtrudedTopology();
    if (this->m_side_group_id != extruded_vertex.m_side_group_id)
      return Internal_IsNotValidExtrudedTopology();
  }
  return true;
}

bool ON_Internal_ExtrudedVertex::AddExtrudedEdgeReference(
  class ON_Internal_ExtrudedEdge* extruded_edge,
  bool bSetExtrudedEdgeToo
)
{
  if (nullptr == m_original_vertex || 0 == m_initial_vertex_id || m_initial_vertex_id != m_original_vertex->m_id)
    return ON_SUBD_RETURN_ERROR(false);

  if (nullptr == extruded_edge || nullptr == extruded_edge->m_original_edge )
    return ON_SUBD_RETURN_ERROR(false);

  unsigned int evi;

  for (evi = 0; evi < 2; ++evi)
  {
    if (m_original_vertex == extruded_edge->m_original_edge->m_vertex[evi] && m_initial_vertex_id == extruded_edge->m_initial_vertex_id[evi])
      break;
  }
  if (evi > 1)
  {
    // edge and vertex are not attached
    return ON_SUBD_RETURN_ERROR(false);
  }

  if ( nullptr != extruded_edge->m_extruded_vertex[evi] && this != extruded_edge->m_extruded_vertex[evi])
    return ON_SUBD_RETURN_ERROR(false);

  switch (m_extruded_edges_count)
  {
  case 0:
    m_extruded_edges[0] = extruded_edge;
    m_extruded_edges_count = 1;
    break;

  case 1:
    if (m_extruded_edges[0] != extruded_edge)
    {
      m_extruded_edges[1] = extruded_edge;
      m_extruded_edges_count = 2;
    }
    break;

  case 2:
    if (m_extruded_edges[0] != extruded_edge && m_extruded_edges[1] != extruded_edge)
      m_extruded_edges_count = 3; // rare case with 3 or more extruded edges sharing an extruded vertex
    break;

  case 3:
    // do nothing this is vertex will be extruded into a non-manifold "side" connecting edge
    break;

  default:
    // invalid value of m_extruded_edges_count
    return ON_SUBD_RETURN_ERROR(false);
    break;
  }

  if (bSetExtrudedEdgeToo && nullptr == extruded_edge->m_extruded_vertex[evi])
    extruded_edge->m_extruded_vertex[evi] = this;

  return true;
}

bool ON_Internal_ExtrudedVertex::SetConnectingEdgeTag()
{
  if (nullptr == m_original_vertex || 0 == m_initial_vertex_id)
    return ON_SUBD_RETURN_ERROR(false); // to early

  if (nullptr != m_copied_vertex || nullptr != m_connecting_edge)
    return ON_SUBD_RETURN_ERROR(false); // to late

  if (m_initial_vertex_id != m_original_vertex->m_id || m_initial_vertex_tag != m_original_vertex->m_vertex_tag || ON_SubDEdgeTag::Unset != m_connecting_edge_tag)
    return ON_SUBD_RETURN_ERROR(false); // corrupt information

  if (m_extruded_edges_count != 2)
  {
    // simple case
    m_connecting_edge_tag = ON_SubDEdgeTag::Crease;
    return true;
  }

  //if (ON_SubDVertexTag::Corner == m_initial_vertex_tag)
  //{
  //  // simple case
  //  m_connecting_edge_tag = ON_SubDEdgeTag::Crease;
  //  return true;
  //}

  if (ON_SubDVertexTag::Crease != m_initial_vertex_tag && ON_SubDVertexTag::Corner != m_initial_vertex_tag)
    return true; // leaving m_connecting_edge_tag unset for anything else works best


  bool bMovedCrease = false;
  bool bStationaryCrease = false;

  const ON_SubDEdge* extruded_edge[2] = {};
  for (unsigned vei = 0; vei < 2; ++vei)
  {
    extruded_edge[vei] = (nullptr != m_extruded_edges[vei]) ? m_extruded_edges[vei]->m_original_edge : nullptr;
    if (nullptr == extruded_edge[vei])
      return ON_SUBD_RETURN_ERROR(false); // corrupt information
    if (1 == extruded_edge[vei]->m_face_count)
    {
      if (extruded_edge[vei]->MarkedFaceCount() > 0)
        bStationaryCrease = true; // the boundary (crease) will not move but the attached face does move
      else
      {
        // the boundary (crease) will move but the attached face does not move
        if (ON_SubDVertexTag::Corner == m_initial_vertex_tag)
        {
          m_connecting_edge_tag = ON_SubDEdgeTag::Crease;
          return true;
        }
        bMovedCrease = true; 
      }
    }
  }

  // determine vertex topology and edge demographics
  for (unsigned short vei = 0; vei < m_original_vertex->m_edge_count; ++vei)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(m_original_vertex->m_edges[vei].m_ptr);
    if (nullptr == e || false == e->IsCrease() || e == extruded_edge[0] || e == extruded_edge[1])
      continue;
    if (e->MarkedFaceCount() > 0)
      bMovedCrease = true;
    else
      bStationaryCrease = true;
  }

  // used the collected vertex topology and edge demographics to determine if connecting_edge_tag should be Crease
  if (bMovedCrease && bStationaryCrease)
    m_connecting_edge_tag = ON_SubDEdgeTag::Crease;

  return true;
}


int ON_Internal_ExtrudedEdge::CompareSideGroupId(const ON_Internal_ExtrudedEdge* lhs, const ON_Internal_ExtrudedEdge* rhs)
{
  const unsigned lhs_side_group_id = lhs->m_side_group_id;
  const unsigned rhs_side_group_id = rhs->m_side_group_id;
  if (lhs_side_group_id < rhs_side_group_id)
    return -1;
  if (lhs_side_group_id > rhs_side_group_id)
    return 1;
  return 0;
}

const ON_Internal_ExtrudedEdge ON_Internal_ExtrudedEdge::Unset;

int ON_Internal_ExtrudedVertex::CompareInitialVertexId(
  const ON_Internal_ExtrudedVertex* lhs,
  const ON_Internal_ExtrudedVertex* rhs
)
{
  const unsigned int lhs_id = lhs->m_initial_vertex_id;
  const unsigned int rhs_id = rhs->m_initial_vertex_id;
  if (lhs_id < rhs_id)
    return -1;
  if (lhs_id > rhs_id)
    return 1;
  return 0;
}

static void Internal_SetEdgeVertices(
  ON_SubD& subd,
  ON_Internal_ExtrudedVertex& extruded_vertex
  )
{
  // marked edges use the marked vertex.
  ON_SubDVertex* marked_vertex = extruded_vertex.m_original_vertex;
  ON_SubDVertex* unmarked_vertex =  extruded_vertex.m_copied_vertex;
  const unsigned int vertex_edge_count = marked_vertex->EdgeCount();
  unsigned int marked_edge_count = 0;
  unsigned int unmarked_edge_count = 0;
  unsigned int new_edge_count = 0;
  for (unsigned int vei = 0; vei < vertex_edge_count; vei++)
  {
    ON_SubDEdgePtr eptr = marked_vertex->m_edges[vei];
    const ON_SubDEdge* e = eptr.Edge();
    if (nullptr == e)
      continue;
    if (extruded_vertex.m_connecting_edge == e)
      new_edge_count++;
    else if (e->m_status.RuntimeMark())
      marked_edge_count++;
    else
      unmarked_edge_count++;
  }

  if (unmarked_edge_count <= 0)
    return;

  unmarked_edge_count += unmarked_vertex->m_edge_count;

  if ( unmarked_vertex->m_edge_capacity < (unmarked_edge_count+new_edge_count) )
    subd.GrowVertexEdgeArray(unmarked_vertex, unmarked_edge_count);    

  marked_vertex->m_edge_count = 0;
  for (unsigned int vei = 0; vei < vertex_edge_count; vei++)
  {
    ON_SubDEdgePtr eptr = marked_vertex->m_edges[vei];
    ON_SubDEdge* e = eptr.Edge();
    if (nullptr == e)
      continue;
    if (extruded_vertex.m_connecting_edge == e || e->m_status.RuntimeMark())
    {
      marked_vertex->m_edges[marked_vertex->m_edge_count] = eptr;
      marked_vertex->m_edge_count++;
    }
    else
    {
      if (e->m_vertex[0] == marked_vertex)
        e->m_vertex[0] = unmarked_vertex;
      else if (e->m_vertex[1] == marked_vertex)
        e->m_vertex[1] = unmarked_vertex;
      unmarked_vertex->m_edges[unmarked_vertex->m_edge_count] = eptr;
      unmarked_vertex->m_edge_count++;
    }
  }
}

ON_SubDFace* ON_Internal_ExtrudedEdge::ExtrudeFace(
  ON_SubD& subd
)
{
  // All components that will be moved have the runtime mark set.
  // All other components have a clear runtime mark.
  // The original_edge will be moved.
  // The new_edge will not be moved.
  // new edge and original edge go the same direction.
  // new_side_edges[2] run from new to original edges.
  
  // change edges of unmarked faces to use the new edge
  ON__UINT_PTR edir = 0;
  ON_SubDEdge* marked_edge = this->m_original_edge; // will be moved
  ON_SubDEdge* unmarked_edge = this->m_copied_edge; // a copy of the original edge at the original location
  unsigned int marked_edge_face_count0 = marked_edge->m_face_count;
  ON_SubDFacePtr* marked_edge_fptr1 = marked_edge->m_face2;
  const ON_SubDFacePtr* marked_edge_fptr0 = marked_edge_fptr1;
  unsigned int marked_edge_face_count1 = 0;
  subd.GrowEdgeFaceArray(unmarked_edge, marked_edge_face_count0);
  for (unsigned int efi = 0; efi < marked_edge_face_count0; efi++, marked_edge_fptr0++)
  {
    if (2 == efi)
      marked_edge_fptr0 = marked_edge->m_facex;

    if (2 == marked_edge_face_count1)
      marked_edge_fptr1 = marked_edge->m_facex;

    ON_SubDFace* f = marked_edge_fptr0->Face();
    if (nullptr == f)
    {
      ON_SUBD_ERROR("null face pointer");
      continue;
    }

    if (f->m_status.RuntimeMark())
    {
      edir = marked_edge_fptr0->FaceDirection();
      marked_edge_face_count1++;
      *marked_edge_fptr1 = *marked_edge_fptr0;
      marked_edge_fptr1++;
      continue; // this face will be moved and keeps edge e1
    }

    // f is unmarked.
    // change referenced edge from marked_edge to unmarked_edge.
    f->ReplaceEdgeInArray(0, marked_edge, unmarked_edge);

    unmarked_edge->AddFaceToArray(*marked_edge_fptr0);
  }

  // When marked_edge is a manifold edge, face_count goes from 2 to 1.
  marked_edge->m_face_count = static_cast<unsigned short>(marked_edge_face_count1);

  ON_SubDEdge* side0 = this->ConnectingEdge(edir);
  ON_SubDEdge* side1 = this->ConnectingEdge(1 - edir);
  ON_SubDEdgePtr new_face_eptr[4];
  new_face_eptr[0] = ON_SubDEdgePtr::Create(this->m_original_edge, 1-edir);
  new_face_eptr[1] = ON_SubDEdgePtr::Create(side0, 1);
  new_face_eptr[2] = ON_SubDEdgePtr::Create(this->m_copied_edge, edir);
  new_face_eptr[3] = ON_SubDEdgePtr::Create(side1, 0);
  
  this->m_new_face = subd.AddFace(new_face_eptr, 4);

  if (nullptr != this->m_new_face)
  {
    // When isolated edges are extruded, we need to flip the face.
    // In all other cases, we don't.
    bool bFlip = false;
    bool bFlipSet = false;
    for (unsigned int fei = 0; fei < 4; fei++)
    {
      const ON_SubDEdgePtr eptr = this->m_new_face->m_edge4[fei];
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
      if (nullptr == e || e->m_face_count > 2)
      {
        bFlipSet = false;
        break;
      }
      if (2 != e->m_face_count)
        continue;
      const ON__UINT_PTR fedir = ON_SUBD_EDGE_DIRECTION(eptr.m_ptr);
      const ON_SubDFacePtr fptr[2] = { e->m_face2[0], e->m_face2[1] };
      const ON_SubDFace* f[2] = { ON_SUBD_FACE_POINTER(fptr[0].m_ptr), ON_SUBD_FACE_POINTER(fptr[1].m_ptr) };
      if (nullptr == f[0] || nullptr == f[1] || f[0] == f[1])
      {
        bFlipSet = false;
        break;
      }
      if (this->m_new_face != f[0] && this->m_new_face != f[1] )
      {
        bFlipSet = false;
        break;
      }
      const ON__UINT_PTR fdir[2] = { ON_SUBD_FACE_DIRECTION(fptr[0].m_ptr), ON_SUBD_FACE_DIRECTION(fptr[1].m_ptr) };
      if (fedir != fdir[(f[0] == this->m_new_face) ? 0 : 1])
      {
        bFlipSet = false;
        break;
      }
      const bool bSameDir = (fdir[0] == fdir[1]) ? true : false;
      if (false == bFlipSet)
      {
        bFlipSet = true;
        bFlip = bSameDir;
      }
      else if (bSameDir != bFlip)
      {
        bFlipSet = false;
        break;
      }
    }
    if (bFlip)
      this->m_new_face->ReverseEdgeList();
  }

  return this->m_new_face;
}

unsigned int ON_SubD::ExtrudeComponents(
  const ON_Xform& xform,
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count
)
{
  const bool bExtrudeBoundaries = true;
  const bool bPermitNonManifoldEdgeCreation = false;
  return ExtrudeComponents(xform, cptr_list, cptr_count, bExtrudeBoundaries, bPermitNonManifoldEdgeCreation);
}

unsigned int ON_SubD::ExtrudeComponents(
  const ON_Xform& xform,
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  bool bExtrudeBoundaries,
  bool bPermitNonManifoldEdgeCreation
)
{
  if (nullptr == cptr_list || cptr_count <= 0)
    return 0;
  return Internal_ExtrudeComponents(
    xform,
    cptr_list,
    cptr_count,
    bExtrudeBoundaries,
    bPermitNonManifoldEdgeCreation
    );
}

unsigned int ON_SubD::Extrude(const ON_Xform & xform)
{
  if (IsSolid())
    return 0;
  const bool bExtrudeBoundaries = true;
  const bool bPermitNonManifoldEdgeCreation = false;
  return Internal_ExtrudeComponents(
    xform,
    nullptr,
    0,
    bExtrudeBoundaries,
    bPermitNonManifoldEdgeCreation
    );
}

static bool Internal_SetSideGroupIds(ON_SimpleArray<ON_Internal_ExtrudedEdge>& new_sides)
{
  unsigned count = new_sides.UnsignedCount();
  if (count <= 0)
    return false;
  unsigned side_group_id = 1;
  for (unsigned int i = 0; i < count; ++i)
  {
    if (false == new_sides[i].SetSideGroupId(side_group_id))
      continue;

    // propagate side_group_id through all touching components
    unsigned j0 = i + 1;
    for (bool bContinue = true; bContinue; /*empty iterator*/)
    {      
      bContinue = false;
      while (j0 < count && new_sides[j0].m_side_group_id > 0)
        ++j0;
      while (count > j0 && new_sides[count - 1].m_side_group_id > 0)
        --count;
      for (unsigned j = j0; j < count; ++j)
      {
        if (new_sides[j].SetSideGroupIdFromVertexPairs())
          bContinue = true;
      }
    }


    ++side_group_id;
  }

  if (side_group_id <= 1)
    return false;

  if (side_group_id > 2)
    new_sides.QuickSort(ON_Internal_ExtrudedEdge::CompareSideGroupId);

  return true;
}


static bool Internal_DebugValdateExtrudedTopology(
  bool bCheckCopies,
  const ON_SimpleArray<ON_Internal_ExtrudedEdge>& extruded_edges,
  const ON_SimpleArray<ON_Internal_ExtrudedVertex>& extruded_vertices
)
{
  const unsigned edge_count = extruded_edges.UnsignedCount();
  const unsigned vertex_count = extruded_vertices.UnsignedCount();

  for (unsigned ei = 0; ei < edge_count; ++ei)
  {
    const ON_Internal_ExtrudedEdge& extruded_edge = extruded_edges[ei];
    if (false == extruded_edge.IsValidTopology(bCheckCopies))
      return false;
  }

  for (unsigned vi = 0; vi < vertex_count; ++vi)
  {
    const ON_Internal_ExtrudedVertex& extruded_vertex = extruded_vertices[vi];
    if (false == extruded_vertex.IsValidTopology(bCheckCopies))
      return false;
  }

  if (vertex_count < edge_count)
    return Internal_IsNotValidExtrudedTopology();

  return true;
}

static bool Internal_IsInsetHack(
  const ON_Xform& xform,
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  bool bExtrudeBoundaries,
  bool bPermitNonManifoldEdgeCreation
)
{
  if (nullptr == cptr_list || cptr_count <= 0 || false != bPermitNonManifoldEdgeCreation)
    return false;

  // inset xform is 0 except xform[0][2] = ON_ZERO_TOLERANCE.
  for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)
  {
    if (xform.m_xform[i][j] == ((0 == i && 2 == j) ? ON_ZERO_TOLERANCE : 0.0) )
      continue;
    return false;
  }

  for (size_t i = 0; i < cptr_count; ++i)
  {
    if (nullptr == cptr_list[i].Face())
      return false;
  }

  return true;
}

unsigned int ON_SubD::Internal_ExtrudeComponents(
  const ON_Xform& xform_arg,
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  bool bExtrudeBoundaries,
  bool bPermitNonManifoldEdgeCreation
)
{
  const bool bIsInset = Internal_IsInsetHack(xform_arg, cptr_list, cptr_count, bExtrudeBoundaries, bPermitNonManifoldEdgeCreation);

  const bool bHaveCptrList = (cptr_count > 0 && nullptr != cptr_list);
  bool bExtrudeAll = false;
  if (false == bHaveCptrList && 0 == cptr_count)
  {
    bool bIsManifold = false;
    bool bIsOriented = false;
    bool bHasBoundary = false;
    int solid_orientation = 0;
    ActiveLevel().GetTopologicalAttributes(bIsManifold, bIsOriented, bHasBoundary, solid_orientation);
    bExtrudeAll = bHasBoundary;
  }
  if (
    false == xform_arg.IsValidAndNotZeroAndNotIdentity()
    || (false == bHaveCptrList && false == bExtrudeAll)
    )
    return 0;
  
  const ON_Xform& xform = bIsInset ? ON_Xform::IdentityTransformation : xform_arg;

  ON_SubDComponentMarksClearAndRestore mark_guard(*this);

  // Marks every face in cptr_list[].
  // Marks every edge attached to a marked face.
  // Marks every subd boundary edge in the cptr_list[].
  // Marks every vertex touching a marked edge or marked face.
  unsigned int list_vertex_count = 0;
  unsigned int list_edge_count = 0;
  unsigned int list_face_count = 0;
  const unsigned int marked_vertex_count = Internal_MarkExtrudeComponents(
    *this,
    cptr_list, cptr_count,
    bExtrudeBoundaries,
    list_vertex_count, list_edge_count, list_face_count
  );
  if (0 == marked_vertex_count)
    return 0;

  const bool bDestroyEvaluationCache = (4 * list_vertex_count >= VertexCount() || 4 * list_edge_count >= EdgeCount() || 4 * list_face_count >= FaceCount());

  // Set moved_faces[] = list of faces that will move.
  ON_SimpleArray<const ON_SubDFace*> moved_faces(list_face_count + 128);
  ON_SubDFaceIterator fit(*this);
  for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
  {
    const unsigned int face_vertex_count = f->m_edge_count;
    if (face_vertex_count < 3 || false == f->m_status.RuntimeMark())
      continue;
    moved_faces.Append(f);
  }
  const unsigned int moved_face_count = moved_faces.UnsignedCount();

  ON_SimpleArray<ON_Internal_ExtrudedEdge> extruded_edges(64);
  ON_SubDEdgeIterator eit(*this);
  for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
  {
    const bool bMarkedEdge = e->Mark();
    e->ClearMark();
    e->ClearMarkBits();
    if (nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
      continue;

    const unsigned int edge_face_count = e->m_face_count;

    // marked wire edges and marked boundary edges get extruded whenever bExtrudeBoundaries is true.
    bool bExtrudeEdge = bMarkedEdge && (0 == edge_face_count || (1 == edge_face_count && bExtrudeBoundaries));

    bool bAttachedToMarkedFace = false;
    bool bAttachedToUnmarkedFace = false;
    for (unsigned int efi = 0; efi < edge_face_count; efi++)
    {
      const ON_SubDFace* f = e->Face(efi);
      if (nullptr == f)
        continue;
      if (f->Mark())
        bAttachedToMarkedFace = true; // f is in the subset of faces that will be moved.
      else
        bAttachedToUnmarkedFace = true; // f is in the subset of faces that are stationary (will not be moved).

      if (bAttachedToMarkedFace && bAttachedToUnmarkedFace)
      {
        // e is on the boundary between the subset of moved faces and stationary faces
        // and will be extruded into a face.
        bExtrudeEdge = true;
        break;
      }
    }

    if (bExtrudeEdge)
    {
      ON_Internal_ExtrudedEdge& extruded_edge = extruded_edges.AppendNew();
      if (false == extruded_edge.SetFromInitialEdge(const_cast<ON_SubDEdge*>(e)))
      {
        ON_SUBD_ERROR("null e or vertex pointers");
        return 0;
      }

      // Marking e here indicates e is an extruded edge.
      // ON_Internal_ExtrudedVertex.SetFromInitialVertex() assumes marked edges are extruded edges.
      e->SetMark();
    }
  }

  const unsigned int extruded_edge_count = extruded_edges.UnsignedCount();
  
  if (0 == extruded_edge_count)
  {
    // no new faces will be made
    if (moved_face_count > 0 && false == bIsInset)
    {
      // Every face is moving 
      Transform(xform);
      return FaceCount();
    }
    return 0;
  }

  // Mark edges on the boundary of the moved subset.
  // clear vertex  marks.
  this->ClearVertexMarks();
  this->ClearVertexMarkBits();

  // build a list extruded_vertices[] of vertices that will be extruded into "side" edges
  ON_SimpleArray<ON_Internal_ExtrudedVertex> extruded_vertices(extruded_edge_count + 8);
  for (unsigned int i = 0; i < extruded_edge_count; i++)
  {
    ON_Internal_ExtrudedEdge& extruded_edge = extruded_edges[i];
    const ON_SubDEdge* e = extruded_edge.m_original_edge;
    if (nullptr == e)
    {
      ON_SUBD_ERROR("Should never be the case.");
      return 0;
    }
    for (unsigned int evi = 0; evi < 2; evi++)
    {
      ON_SubDVertex* v = const_cast<ON_SubDVertex*>(e->m_vertex[evi]);
      if (v->Mark())
        continue; // this vertex has already been added to extruded_vertices[]

      // Mark this vertex to indicate it will be extruded into a "side" edge.
      v->SetMark();

      ON_Internal_ExtrudedVertex& extruded_vertex = extruded_vertices.AppendNew();
      if (false == extruded_vertex.SetFromInitialVertex(v))
      {
        ON_SUBD_ERROR("Should never be the case.");
        return 0;
      }

      // Partially setting the topology connections here reduces the number of binary searches by about half.
      // The second parameter is false because the sorting of extruded_vertices[] will change the memory
      // location where extruded_vertex is stored.
      if (false == extruded_vertex.AddExtrudedEdgeReference(&extruded_edge, false))
        return 0;
    }
  }

  // sort vertex pairs so they can be located by the original vertex id.
  extruded_vertices.QuickSort(ON_Internal_ExtrudedVertex::CompareInitialVertexId);

  // After sorting but before searching, set extruded_edge.m_extruded_vertex[] pointer
  // for the extruded_edge used to generate the extruded_vertex in the for() loop
  // immediately before the sorting of extruded_vertices[].
  // This reduces the number of binary searches by about half.
  for (unsigned int i = 0; i < extruded_vertices.UnsignedCount(); i++)
  {
    ON_Internal_ExtrudedVertex& extruded_vertex = extruded_vertices[i];
    if (
      extruded_vertex.m_initial_vertex_id > 0
      && 1 == extruded_vertex.m_extruded_edges_count
      && nullptr != extruded_vertex.m_extruded_edges[0]
      )
    {
      if (extruded_vertex.AddExtrudedEdgeReference(extruded_vertex.m_extruded_edges[0], true))
        continue;
    }

    ON_SUBD_ERROR("bug introduced in code above since Feb 2020");
    return 0;
  }

  // Use the sorted extruded_vertices[] array and initial vertex ids to
  // finish set the topology connections between extruded_vertices[] and extruded_edges[]
  ON_Internal_ExtrudedVertex bsearch_key;
  for (unsigned int i = 0; i < extruded_edges.UnsignedCount(); i++)
  {
    ON_Internal_ExtrudedEdge& extruded_edge = extruded_edges[i];
    for (unsigned int evi = 0; evi < 2; evi++)
    {
      if (nullptr != extruded_edge.m_extruded_vertex[evi])
        continue; // this topology connection was set above and we can skip the binary search step

      // Use a binary search to find the element of extruded_vertices[] that corresponds to extruded_edge.m_original_edge->m_vertex[evi].
      bsearch_key.m_initial_vertex_id = extruded_edge.m_initial_vertex_id[evi];
      const int i0 = extruded_vertices.BinarySearch(&bsearch_key, ON_Internal_ExtrudedVertex::CompareInitialVertexId);
      if (i0 < 0)
      {
        ON_SUBD_ERROR("Should never be the case.");
        return 0;
      }
      if (false == extruded_vertices[i0].AddExtrudedEdgeReference(&extruded_edge, true))
        return 0;
    }
  }

  if (false == bPermitNonManifoldEdgeCreation)
  {
    for (unsigned int i = 0; i < extruded_vertices.UnsignedCount(); i++)
    {
      // 3 or more "side" faces will be attached to the edge made by extruding the vertex.
      // Thus, this edge will be a nonmanifold edge.
      if (extruded_vertices[i].m_extruded_edges_count >= 3)
        return 0;
    }
  }

  if (false == Internal_DebugValdateExtrudedTopology(false, extruded_edges, extruded_vertices))
    return 0;

  // Need to set some tag information that is used when we created the extruded edges and faces
  // before modifications are made to this subd.
  for (unsigned int i = 0; i < extruded_vertices.UnsignedCount(); ++i)
    extruded_vertices[i].SetConnectingEdgeTag();

  // Extrude vertices into side edges - creates new vertices and connecting edges.
  for (unsigned int i = 0; i < extruded_vertices.UnsignedCount(); ++i)
  {
    if (false == extruded_vertices[i].ExtrudeVertex(*this, bIsInset, xform))
      return 0;
  }

  // Create "side" face edge that will be opposite the original edge.
  for (unsigned int i = 0; i < extruded_edges.UnsignedCount(); ++i)
  {
    if (nullptr == extruded_edges[i].CreateCopiedEdge(*this))
      return 0;
  }

  if (false == Internal_DebugValdateExtrudedTopology(true, extruded_edges, extruded_vertices))
    return 0;

  // At this point moved_faces[] = set of marked faces.
  // Efficiency determines whither the face mark or the moved_faces[] array 
  // is used to decide if a face is moved or stationary.
  for (unsigned int i = 0; i < extruded_vertices.UnsignedCount(); ++i)
  {
    // Attach unmarked faces (stationary) to m_copied_vertex.
    // Leave the marked faces (transformed) attached to m_original_vertex.
    if (false == extruded_vertices[i].AttachUnmarkedFacesToCopiedVertex())
    {
      for (unsigned j = 0; j < i; ++j)
        extruded_vertices[i].UndoAttachUnmarkedFacesToCopiedVertex();
      return 0;
    }
  }

  // From this point on, we don't bail out, we just press on doing the best that can be done.


  // Mark everything a moved face touches
  // including interior edges and vertices.
  // Transform any vertices that are not already marked.
  // (The vertices in extruded_vertices[] are currently marked and have already been transformed.)
  for (unsigned int i = 0; i < moved_face_count; i++)
  {
    const ON_SubDFace* f = moved_faces[i];
    if (false == bDestroyEvaluationCache)
      f->ClearSavedSubdivisionPoints();
    const unsigned int face_edge_count = f->m_edge_count;
    for (unsigned int fei = 0; fei < face_edge_count; ++fei)
    {
      const ON_SubDEdge* e = f->Edge(fei);
      if (nullptr == e)
        continue;
      if (false == bDestroyEvaluationCache)
        e->ClearSavedSubdivisionPoints();
      e->SetMark();
      for (unsigned int evi = 0; evi < 2; evi++)
      {
        ON_SubDVertex* v = const_cast<ON_SubDVertex*>(e->m_vertex[evi]);
        if (nullptr != v && false == v->Mark())
        {
          if (false == bIsInset)
            v->Transform(false, xform);
          v->SetMark();
          if (false == bDestroyEvaluationCache)
            v->VertexModifiedNofification();
        }
      }
    }
  }

  // For the original boundary vertex, move unmarked edges to use the new vertex.
  for (unsigned int i = 0; i < extruded_vertices.UnsignedCount(); i++)
    Internal_SetEdgeVertices(*this, extruded_vertices[i]);

  // extrude edges into new "side" faces.
  for (unsigned int i = 0; i < extruded_edge_count; i++)
    extruded_edges[i].ExtrudeFace(*this);

  // remove cached subdivision calculations
  if (bDestroyEvaluationCache)
    ClearEvaluationCache();

  // Set tags that are clearly determined by the extrusion.
  if ( Internal_SetSideGroupIds(extruded_edges))
  {
    const unsigned count = extruded_edges.UnsignedCount();
    unsigned i1 = 0;
    for (unsigned i0 = 0; i0 < count; i0 = (i1 > i0) ? i1 : (i0 + 1))
    {
      const unsigned side_group_id = extruded_edges[i0].m_side_group_id;
      unsigned crease_count = 0;
      unsigned interior_crease_count = 0;
      unsigned corner_count = 0;
      for (i1 = i0; i1 < count && side_group_id == extruded_edges[i1].m_side_group_id; ++i1)
      {
        ON_Internal_ExtrudedEdge& extruded_edge = extruded_edges[i1];
        if (nullptr != extruded_edge.m_original_edge && 2 != extruded_edge.m_original_edge->m_face_count)
        {
          extruded_edge.m_original_edge->m_edge_tag = ON_SubDEdgeTag::Crease;
        }
        if (nullptr != extruded_edge.m_copied_edge)
        {
          if (
            2 != extruded_edge.m_copied_edge->m_face_count
            || 
            (2 == extruded_edge.m_initial_edge_face_count && ON_SubDEdgeTag::Crease == extruded_edge.m_initial_edge_tag)
            )
            extruded_edge.m_copied_edge->m_edge_tag = ON_SubDEdgeTag::Crease;
        }
        if (extruded_edge.InitialCrease())
        {
          ++crease_count;
          if (2 == extruded_edge.m_initial_edge_face_count)
            ++interior_crease_count;
          if (extruded_edge.InitialCreaseWithCorner())
          {
            ++corner_count;
            for (unsigned k = 0; k < 2; ++k)
            {
              ON_SubDEdge* e = (0 == k) ? extruded_edge.m_original_edge : extruded_edge.m_copied_edge;
              if (2 != e->m_face_count)
              {
                e->m_edge_tag = ON_SubDEdgeTag::Crease;
                for (unsigned evi = 0; evi < 2; ++evi)
                {
                  ON_Internal_ExtrudedVertex* extruded_vertex = extruded_edge.m_extruded_vertex[evi];
                  if (ON_SubDVertexTag::Corner == extruded_vertex->m_initial_vertex_tag)
                  {
                    ON_SubDVertex* v = (0 == k) ? extruded_vertex->m_original_vertex : extruded_vertex->m_copied_vertex;
                    v->m_vertex_tag = ON_SubDVertexTag::Corner;
                  }
                }
              }
            }
          }
        }
      }
      if (
        (crease_count == (i1 - i0))
        && 
        (corner_count > 0 || crease_count == interior_crease_count)
        )
      {
        for (unsigned i = i0; i < i1; ++i)
          extruded_edges[i].SetBothEdgeTags(ON_SubDEdgeTag::Crease);
      }
    }
  }

  for (unsigned i = 0; i < extruded_vertices.UnsignedCount(); ++i)
  {
    ON_Internal_ExtrudedVertex& pair = extruded_vertices[i];
    if (ON_SubDVertexTag::Corner == pair.m_initial_vertex_tag)
    {
      for (unsigned vdex = 0; vdex < 2; ++vdex)
      {
        ON_SubDVertex* v = (0 == vdex) ? pair.m_original_vertex : pair.m_copied_vertex;
        if (nullptr == v)
          continue;
        if (v->EdgeProperties().m_crease_edge_count >= 3)
          v->m_vertex_tag = ON_SubDVertexTag::Corner;
      }
    }
  }

  if ( false == bDestroyEvaluationCache)
  {
    for (unsigned int i = 0; i < extruded_vertices.UnsignedCount(); ++i)
    {
      ON_Internal_ExtrudedVertex& pair = extruded_vertices[i];
      if (nullptr != pair.m_original_vertex)
        pair.m_original_vertex->VertexModifiedNofification();
      if ( nullptr != pair.m_copied_vertex)
        pair.m_copied_vertex->VertexModifiedNofification();
    }
  }

  // Calculate unset vertex tags, unset edge tags, edge sector coefficients.
  if (false == bIsInset)
    this->UpdateAllTagsAndSectorCoefficients(true);

#if defined(ON_DEBUG)
  if ( false == bIsInset)
    IsValid();
#endif

  this->ChangeGeometryContentSerialNumberForExperts(false);

  // number of moved faces and new faces created by extruding edges
  return moved_face_count + extruded_edge_count;
}

unsigned int ON_SubD::SetVertexTags(
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count,
  ON_SubDVertexTag vertex_tag
)
{
  if (
    ON_SubDVertexTag::Smooth != vertex_tag
    && ON_SubDVertexTag::Crease != vertex_tag
    && ON_SubDVertexTag::Corner != vertex_tag
    )
    return 0;

  if (
    ci_count <= 0
    || nullptr == ci_list
    || VertexCount() <= 0
    )
    return 0;

  ON_SimpleArray<ON_SubDComponentPtr> cptr_list;
  if (ComponentPtrFromComponentIndex(ci_list,ci_count,cptr_list) <= 0)
    return 0; // nothing to change

  return SetVertexTags(
    cptr_list.Array(),
    cptr_list.UnsignedCount(),
    vertex_tag
    );
}

unsigned int ON_SubD::SetVertexTags(
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  ON_SubDVertexTag vertex_tag
)
{
  if (
    ON_SubDVertexTag::Smooth != vertex_tag
    && ON_SubDVertexTag::Crease != vertex_tag
    && ON_SubDVertexTag::Corner != vertex_tag
    )
    return 0;

  if (cptr_count <= 0 || nullptr == cptr_list)
    return 0;

  ON_SubDComponentMarksClearAndRestore mark_guard(*this);
  // be less generous with markbits.
  ClearComponentMarkBits(true, true, true);

  const ON__UINT8 smooth_bias = 1;
  const ON__UINT8 crease_bias = 2;
  

  const bool bNewVertexTagIsSmooth = (ON_SubDVertexTag::Smooth == vertex_tag);

  // count and mark vertex candidates
  // mark edges that may need to have their tag changed
  unsigned int candidate_count = 0;
  for (size_t i = 0; i < cptr_count; i++)
  {
    ON_SubDVertex* vertex = cptr_list[i].Vertex();
    if (nullptr == vertex)
      continue;
    if (vertex->m_vertex_tag == vertex_tag)
      continue;

    //const bool bRemoveCorner = ON_SubDVertexTag::Corner == vertex->m_vertex_tag;

    if (ON_SubDVertexTag::Corner != vertex_tag)
    {
      // new vertex_tag is Smooth or Crease
      if (nullptr == vertex->m_edges || vertex->m_edge_count < 2)
        continue;

      const ON_SubDVertexEdgeProperties ep = vertex->EdgeProperties();

      if (ep.m_nonmanifold_edge_count > 0)
        continue; // nonmanifold edge

      if (ep.m_boundary_edge_count + ep.m_wire_edge_count > 2)
        continue;

      if (ON_SubDVertexTag::Smooth == vertex_tag)
      {
        if (ep.m_interior_edge_count != vertex->m_edge_count)
          continue;
      }
      else if (ON_SubDVertexTag::Crease == vertex_tag)
      {
        if (2 == ep.m_crease_edge_count)
        {
          // attempt change - further refinement may be needed here
        }
        else if (2 == ep.m_boundary_edge_count)
        {
          // attempt change - further refinement may be needed here
        }
        else if (2 == ep.m_wire_edge_count)
        {
          // attempt change - further refinement may be needed here
        }
        else
        {
          // don't attempt change - further refinement may be needed here
          continue;
        }
      }
    }

    candidate_count++;
    vertex->m_status.SetRuntimeMark();
    if (nullptr != vertex->m_edges)
    {
      if (ON_SubDVertexTag::Corner == vertex_tag)
      {
        const unsigned int crease_count = vertex->EdgeCount(ON_SubDEdgeTag::Crease);
        if (crease_count >= 2)
          continue; // do not crease additional edges
      }

      for (unsigned short vei = 0; vei < vertex->m_edge_count; vei++)
      {
        const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(vertex->m_edges[vei].m_ptr);
        if (nullptr == edge)
          continue;
        if (bNewVertexTagIsSmooth)
        {
          // new vertex_tag is Smooth
          if (edge->IsSmoothNotX())
            continue;
        }
        else
        {
          // new vertex_tag is Crease or Corner
          if (edge->IsCrease())
            continue;
        }

        // This edge tag will need to be changed
        edge->m_status.SetRuntimeMark();
      }
    }
  }

  if (0 == candidate_count)
    return 0;

  bool bUpdateTags = (ON_SubDVertexTag::Crease != vertex_tag);

  // This for loop is used when new vertex_tag is ON_SubDVertexTag::Crease.
  for (int pass = 0; pass < 2 && false == bUpdateTags; pass++)
  {
    // More careful analysis is needed to accurately mark smooth edges that will become creases
    ON_SubDEdgeIterator eit(*this);
    for (const ON_SubDEdge* edge = eit.FirstEdge(); nullptr != edge; edge = eit.NextEdge())
    {
      if (false == edge->m_status.RuntimeMark())
        continue;
      
      edge->m_status.ClearRuntimeMark();
      if (false == edge->IsSmooth())
        continue;

      const ON_SubDVertex* v[2] = { edge->m_vertex[0], edge->m_vertex[1] };
      if (nullptr == v[0] || nullptr == v[1])
        continue;

      const ON_SubDVertexTag vtag[2] = {
        (v[0]->m_status.RuntimeMark() ? vertex_tag : v[0]->m_vertex_tag),
        (v[1]->m_status.RuntimeMark() ? vertex_tag : v[1]->m_vertex_tag)
      };

      // At least one of v[0] and v[1] had m_vertex_tag changed.
      const bool bGettingSmoother =
        (v[0]->IsCorner() && ON_SubDVertexTag::Corner != vertex_tag)
        ||
        (v[1]->IsCorner() && ON_SubDVertexTag::Corner != vertex_tag)
        ||
        (v[0]->IsDartOrCreaseOrCorner() && ON_SubDVertexTag::Smooth == vertex_tag)
        ||
        (v[1]->IsDartOrCreaseOrCorner() && ON_SubDVertexTag::Smooth == vertex_tag)
        ;

      ON_SubDEdgeTag edge_tag;
      for (;;)
      {
        if (2 != edge->m_face_count)
        {
          edge_tag = ON_SubDEdgeTag::Crease;
          break;
        }

        if (bGettingSmoother)
        {
          edge_tag = ON_SubDEdgeTag::Smooth;
          break;
        }

        if (2 == v[0]->m_edge_count && (ON_SubDVertexTag::Crease == vtag[0] || ON_SubDVertexTag::Corner == vtag[0]))
        {
          edge_tag = ON_SubDEdgeTag::Crease;
          break;
        }

        if (2 == v[1]->m_edge_count && (ON_SubDVertexTag::Crease == vtag[1] || ON_SubDVertexTag::Corner == vtag[1]))
        {
          edge_tag = ON_SubDEdgeTag::Crease;
          break;
        }

        if (
          (ON_SubDVertexTag::Crease == vtag[0] || ON_SubDVertexTag::Corner == vtag[0] || ON_SubDVertexTag::Dart == vtag[0])
          &&
          (ON_SubDVertexTag::Crease == vtag[1] || ON_SubDVertexTag::Corner == vtag[1] || ON_SubDVertexTag::Dart == vtag[1])
          )
        {
          edge_tag = ON_SubDEdgeTag::Crease;
          break;
        }

        edge_tag = ON_SubDEdgeTag::Smooth;
        break;
      }

      if (ON_SubDEdgeTag::Crease == edge_tag)
      {
        edge->m_status.SetRuntimeMark();
        edge->SetMarkBits(crease_bias);
      }
      else
      {
        edge->SetMarkBits(smooth_bias);
      }
    }

    // make sure new crease vertices will have the right number of creased edges
    bUpdateTags = true;
    for (size_t i = 0; i < cptr_count; i++)
    {
      ON_SubDVertex* vertex = cptr_list[i].Vertex();
      if (nullptr == vertex)
        continue;
      if (false == vertex->m_status.RuntimeMark())
        continue;
      unsigned int crease_count = 0;
      unsigned int marked_count = 0;
      for (unsigned short vei = 0; vei < vertex->m_edge_count; vei++)
      {
        const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(vertex->m_edges[vei].m_ptr);
        if (nullptr == edge)
          continue;
        if (edge->IsCrease())
          ++crease_count;
        else if (edge->m_status.RuntimeMark())
          ++marked_count;
      }
      if (crease_count + marked_count <= 2 && (0 != crease_count || 0 != marked_count))
        continue;

      if (pass > 0)
        return 0;
      bUpdateTags = false;
      if (2 == crease_count)
      {
        for (unsigned short vei = 0; vei < vertex->m_edge_count; vei++)
        {
          const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(vertex->m_edges[vei].m_ptr);
          if (nullptr != edge)
            edge->m_status.ClearRuntimeMark();
        }
      }
      else
      {
        vertex->m_status.ClearRuntimeMark();
        candidate_count--;
      }
    }

    if (0 == candidate_count)
      return 0;
  }

  if (false == bUpdateTags)
    return 0;

  unsigned int changed_vertex_count = 0;
  for (size_t i = 0; i < cptr_count; i++)
  {
    ON_SubDVertex* vertex = cptr_list[i].Vertex();
    if (nullptr == vertex)
      continue;
    if (false == vertex->m_status.RuntimeMark())
      continue;
    changed_vertex_count++;
    vertex->m_vertex_tag = vertex_tag;
    vertex->VertexModifiedNofification();
    if (ON_SubDVertexTag::Corner == vertex_tag && vertex->EdgeCount(ON_SubDEdgeTag::Crease) >= 2)
    {
      // do not crease additional edges
      continue; 
    }
    for (unsigned short vei = 0; vei < vertex->m_edge_count; vei++)
    {
      const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(vertex->m_edges[vei].m_ptr);
      if (nullptr == edge)
        continue;
      if ( false == bNewVertexTagIsSmooth
        && edge->m_status.RuntimeMark() 
        && false == edge->IsCrease()
        )
      {
        const_cast<ON_SubDEdge*>(edge)->m_edge_tag = ON_SubDEdgeTag::Crease;
        edge->EdgeModifiedNofification();
      }
      edge->m_status.SetRuntimeMark();


      const ON_SubDVertex* other_vertex = edge->OtherEndVertex(vertex);
      other_vertex->m_status.SetRuntimeMark();

      if ( false == bNewVertexTagIsSmooth
        && ON_SubDEdgeTag::Crease == edge->m_edge_tag
        && other_vertex->IsSmooth()
        )
      {
        const_cast<ON_SubDVertex*>(other_vertex)->m_vertex_tag = ON_SubDVertexTag::Dart;
        other_vertex->VertexModifiedNofification();
      }
    }
  }

  if (0 == changed_vertex_count)
    return 0;

  ON_SubDEdgeIterator eit(*this);
  for (const ON_SubDEdge* edge = eit.FirstEdge(); nullptr != edge; edge = eit.NextEdge())
  {
    if (false == edge->m_status.RuntimeMark())
      continue;
    const ON_SubDVertex* v[2] = { edge->m_vertex[0], edge->m_vertex[1] };
    if (nullptr == v[0] || nullptr == v[1])
      continue;

    ON_SubDEdgeTag edge_tag;
    if (v[0]->IsDartOrCreaseOrCorner() && v[1]->IsDartOrCreaseOrCorner())
      edge_tag = (smooth_bias == edge->MarkBits()) ? ON_SubDEdgeTag::SmoothX : ON_SubDEdgeTag::Crease;
    else
      edge_tag = ON_SubDEdgeTag::Smooth;

    if (edge->m_edge_tag == edge_tag)
      continue;
    const_cast<ON_SubDEdge*>(edge)->m_edge_tag = edge_tag;
    edge->EdgeModifiedNofification();
  }

  ON_SubDVertexIterator vit(*this);
  for (const ON_SubDVertex* vertex = vit.FirstVertex(); nullptr != vertex; vertex = vit.NextVertex())
  {
    if (false == vertex->m_status.RuntimeMark())
      continue;
    const unsigned int crease_count = vertex->EdgeCount(ON_SubDEdgeTag::Crease);
    ON_SubDVertexTag vtag = vertex->m_vertex_tag;
    if (2 == crease_count)
    {
      if ( false == vertex->IsCreaseOrCorner() )
        vtag = ON_SubDVertexTag::Crease;
    }
    else if (1 == crease_count)
      vtag = ON_SubDVertexTag::Dart;
    else if (crease_count > 2)
      vtag = ON_SubDVertexTag::Corner;
    else
      vtag = ON_SubDVertexTag::Smooth;
    if (vertex->m_vertex_tag == vtag)
      continue;
    const_cast<ON_SubDVertex*>(vertex)->m_vertex_tag = vtag;
    vertex->ClearSavedSubdivisionPoints();
  }

  ClearComponentMarkBits(true, true, true);
  ClearEvaluationCache();
  UpdateAllTagsAndSectorCoefficients(false);

  return changed_vertex_count;
}

unsigned int ON_SubD::SetEdgeTags(
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count,
  ON_SubDEdgeTag edge_tag
)
{
  if (ON_SubDEdgeTag::Smooth != edge_tag && ON_SubDEdgeTag::Crease != edge_tag)
    return 0;

  if (
    ci_count <= 0
    || nullptr == ci_list
    || EdgeCount() <= 0
    )
    return 0;

  ON_SimpleArray<ON_SubDComponentPtr> cptr_list;
  if (ComponentPtrFromComponentIndex(ci_list,ci_count,cptr_list) <= 0)
    return 0; // nothing to change

  return SetEdgeTags(
    cptr_list.Array(),
    cptr_list.UnsignedCount(),
    edge_tag
    );
}

unsigned int ON_SubD::SetEdgeTags(
  const ON_SimpleArray<ON_SubDComponentPtr>& cptr_list,
  ON_SubDEdgeTag edge_tag
)
{
  return this->SetEdgeTags(cptr_list.Array(), cptr_list.Count(), edge_tag);
}

unsigned int ON_SubD::SetEdgeTags(
  const ON_SubDComponentPtr* cptr_list,
  size_t cptr_count,
  ON_SubDEdgeTag edge_tag
)
{
  if (ON_SubDEdgeTag::Smooth != edge_tag && ON_SubDEdgeTag::Crease != edge_tag)
    return 0;

  if (
    cptr_count <= 0
    || nullptr == cptr_list
    || EdgeCount() <= 0
    )
    return 0;

  unsigned int changed_edge_count = 0;

  const bool bChangeToSmooth = (ON_SubDEdgeTag::Smooth == edge_tag) ? true : false;

  for (size_t i = 0; i < cptr_count; i++)
  {
    ON_SubDEdge* edge = cptr_list[i].Edge();
    if (nullptr == edge)
      continue;
    if (bChangeToSmooth)
    {
      if ( edge->IsSmoothNotSharp())
        continue; // already smooth
      if (2 != edge->FaceCount())
        continue; // can't be smooth
    }
    else
    {
      if (edge->IsCrease())
        continue; // already a crease
    }

    edge->EdgeModifiedNofification();

    changed_edge_count++;
    edge->m_edge_tag = edge_tag;
    edge->ClearSharpnessForExperts();
    edge->UnsetSectorCoefficientsForExperts();
    for (int evi = 0; evi < 2; evi++)
    {
      ON_SubDVertex* v = const_cast<ON_SubDVertex*>(edge->m_vertex[evi]);
      if (nullptr == v)
        continue;
      v->m_vertex_tag = ON_SubDVertexTag::Unset;
      v->ClearSavedSubdivisionPoints();
    }
  }

  if (0 == changed_edge_count)
    return 0;

  ClearEvaluationCache();

  ON_SubDVertexIterator vit(*this);
  for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
  {
    if (ON_SubDVertexTag::Unset != v->m_vertex_tag)
      continue;
    unsigned crease_count = 0;
    const unsigned vertex_edge_count = v->EdgeCount();
    for (unsigned vei = 0; vei < vertex_edge_count; vei++)
    {
      const ON_SubDEdge* e = v->Edge(vei);
      if (nullptr == e)
        continue;
      if (e->IsCrease())
      {
        crease_count++;
        if (crease_count > 2)
          break;
      }
    }
    ON_SubDVertexTag vertex_tag;
    switch (crease_count)
    {
    case 0:
      vertex_tag = ON_SubDVertexTag::Smooth;
      break;
    case 1:
      vertex_tag = ON_SubDVertexTag::Dart;
      break;
    case 2:
      vertex_tag = ON_SubDVertexTag::Crease;
      break;
    default:
      vertex_tag = ON_SubDVertexTag::Corner;
      break;
    }
    if (v->m_vertex_tag != vertex_tag)
    {
      const_cast<ON_SubDVertex*>(v)->m_vertex_tag = vertex_tag;
      v->ClearSavedSubdivisionPoints();
    }
  }

  ON_SubDEdgeIterator eit(*this);
  for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
  {
    ON_SubDEdgeTag e_tag = e->m_edge_tag;
    if (nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
      e_tag = ON_SubDEdgeTag::Unset;
    else if (ON_SubDEdgeTag::Smooth == e_tag
      && ON_SubDVertexTag::Smooth != e->m_vertex[0]->m_vertex_tag
      && ON_SubDVertexTag::Smooth != e->m_vertex[1]->m_vertex_tag)
      e_tag = ON_SubDEdgeTag::Unset;
    if (e_tag != e->m_edge_tag)
    {
      const_cast<ON_SubDEdge*>(e)->m_edge_tag = e_tag;
      e->UnsetSectorCoefficientsForExperts();
      e->ClearSavedSubdivisionPoints();
    }
  }

  UpdateAllTagsAndSectorCoefficients(false);
  return changed_edge_count;
}

unsigned int ON_SubD::RemoveAllCreases()
{
  unsigned int changed_count = 0;
  ON_SubDEdgeIterator eit(*this);
  for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
  {
    if ( (false == e->IsCrease() && false == e->IsSharp()) || 2 != e->m_face_count)
      continue;
    const_cast<ON_SubDEdge*>(e)->ClearSharpnessForExperts();
    const_cast<ON_SubDEdge*>(e)->m_edge_tag = ON_SubDEdgeTag::Smooth;
    e->UnsetSectorCoefficientsForExperts();
    for (int evi = 0; evi < 2; evi++)
    {
      if (nullptr == e->m_vertex[evi])
        continue;
      const_cast<ON_SubDVertex*>(e->m_vertex[evi])->m_vertex_tag = ON_SubDVertexTag::Unset;
    }
    ++changed_count;
  }

  if (changed_count > 0)
  {
    this->DestroyRuntimeCache(true);
    this->UpdateAllTagsAndSectorCoefficients(true);
  }

  return changed_count;
}

const ON_SubDEdgePtr ON_SubDEdgeChain::EdgeChainNeighbor(ON_SubDEdgePtr starting_edge, ON_ChainDirection search_direction, ON_SubD::ChainType chain_type)
{
  return ON_SubDEdgeChain::EdgeChainNeighbor(
    starting_edge,
    search_direction,
    chain_type,
    false,
    ON_ComponentStatus::NoneSet,
    ON_ComponentStatus::NoneSet
  );
}

const ON_SubDEdgePtr ON_SubDEdgeChain::EdgeChainNeighbor(
    ON_SubDEdgePtr starting_edge,
    ON_ChainDirection search_direction,
    ON_SubD::ChainType chain_type,
    bool bEnableStatusCheck,
    ON_ComponentStatus status_pass,
    ON_ComponentStatus status_fail
  )
{
  for (;;)
  {
    if (ON_ChainDirection::Previous != search_direction && ON_ChainDirection::Next != search_direction)
      break;
    const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(starting_edge.m_ptr);
    if (nullptr == edge)
      break;
    bool bReverse = (ON_ChainDirection::Previous == search_direction);    
    if (0 != ON_SUBD_EDGE_DIRECTION(starting_edge.m_ptr))
      bReverse = !bReverse;
    const ON_SubDVertex* v = edge->m_vertex[bReverse ? 0 : 1];
    if (nullptr == v)
      break;
    if (v->m_edge_count <= 1 || nullptr == v->m_edges)
      break;
    
    const bool bIsSmooth = edge->IsSmooth();
    const bool bIsCrease = edge->IsCrease() || 2 != edge->m_face_count;
    if (bIsSmooth != (bIsCrease?false:true))
      break;

    const unsigned short vertex_edge_count 
      = ((ON_SubD::ChainType::EqualEdgeTagAndOrdinary == chain_type || ON_SubD::ChainType::EqualEdgeAndVertexTagAndOrdinary == chain_type)
        && (1 == edge->m_face_count || 2 == edge->m_face_count))
        ? (edge->m_face_count + 2)
        : ((unsigned short)0);

    if (vertex_edge_count > 0 && vertex_edge_count != v->m_edge_count)
      break;

    if (ON_SubD::ChainType::EqualEdgeAndVertexTag == chain_type || ON_SubD::ChainType::EqualEdgeAndVertexTagAndOrdinary == chain_type)
    {
      if (bIsSmooth)
      {
        // edge is smooth so vertex must be smooth
        if (ON_SubDVertexTag::Smooth != v->m_vertex_tag)
          break;
      }
      else
      {
        // edge is crease so vertex must be crease
        if (ON_SubDVertexTag::Crease != v->m_vertex_tag)
          break;
      }
    }

    // Look for a single neighbor with same crease/smooth property and same face count
    // This lets chains turn the right way when there are both creases and smooth
    // edges.
    const double end_sharpness = edge->Sharpness(true)[bReverse ? 0 : 1];
    const ON_SubDEdge* nxt = nullptr;
    for (unsigned short vei = 0; vei < v->m_edge_count; vei++)
    {
      const ON_SubDEdgePtr eptr = v->m_edges[vei];
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
      if (edge == e)
        continue;
      if (bIsSmooth != e->IsSmooth())
        continue;
      if (bIsCrease != e->IsCrease())
        continue;
      if (e->m_face_count != edge->m_face_count)
        continue;

      // Dale Lear - 2023 May 23 - added continuous sharpness test
      const double nxt_sharpness = e->Sharpness(true)[ON_SUBD_EDGE_DIRECTION(eptr.m_ptr)];
      if (false == (end_sharpness == nxt_sharpness))
        continue;

      if (e->m_vertex[0] != v && e->m_vertex[1] != v)
        continue; // bogus edge

      // 19 Nov 2024, Mikko, RH-84736:
      // Avoid making sharp turns in the regular two neighbor face case.
      if (2 == edge->m_face_count)
      {
        if (edge->Face(0) == e->Face(0) || edge->Face(1) == e->Face(0))
          continue;
        if (edge->Face(0) == e->Face(1) || edge->Face(1) == e->Face(1))
          continue;
      }

      if (nullptr == nxt)
      {
        nxt = e;
        continue;
      }
      // ambiguous options here
      nxt = nullptr;
      break;
    }
    const int nxt_connecting_vertex_index = (ON_ChainDirection::Next == search_direction) ? 0 : 1;
    if (nullptr != nxt)
    {
      if (false == bEnableStatusCheck || ON_ComponentStatus::StatusCheck(nxt->m_status, status_pass, status_fail))
        return ON_SubDEdgePtr::Create(nxt, (v == nxt->m_vertex[nxt_connecting_vertex_index]) ? 0 : 1);
    }

    if (2 != edge->m_face_count || 4 != v->m_edge_count)
      break;
    const ON_SubDFace* f[2] = { ON_SUBD_FACE_POINTER(edge->m_face2[0].m_ptr),ON_SUBD_FACE_POINTER(edge->m_face2[1].m_ptr) };
    if (nullptr == f[0] || nullptr == f[1] || f[0] == f[1])
      break;
    for (unsigned short vei = 0; vei < v->m_edge_count; vei++)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(v->m_edges[vei].m_ptr);
      if (edge == e)
        continue;
      if (2 != e->m_face_count)
        continue;
      if (e->m_vertex[0] != v && e->m_vertex[1] != v)
        continue; // bogus edge
      const ON_SubDFace* nxtf[2] = { ON_SUBD_FACE_POINTER(e->m_face2[0].m_ptr),ON_SUBD_FACE_POINTER(e->m_face2[1].m_ptr) };
      if (nullptr == nxtf[0] || nullptr == nxtf[1] || nxtf[0] == nxtf[1])
        continue;
      if (f[0] == nxtf[0] || f[1] == nxtf[0])
        continue;
      if (f[0] == nxtf[1] || f[1] == nxtf[1])
        continue;
      if (nullptr == nxt)
      {
        nxt = e;
        continue;
      }
      // ambiguous options here
      nxt = nullptr;
      break;
    }
    if (nullptr != nxt)
    {
      if (bIsSmooth != nxt->IsSmooth())
      {
        // edge tag changed
        if ( 
          ON_SubD::ChainType::EqualEdgeTag == chain_type 
          || ON_SubD::ChainType::EqualEdgeAndVertexTag == chain_type
          || ON_SubD::ChainType::EqualEdgeTagAndOrdinary == chain_type
          || ON_SubD::ChainType::EqualEdgeAndVertexTagAndOrdinary == chain_type
          )
          break;
      }
      if (false == bEnableStatusCheck || ON_ComponentStatus::StatusCheck(nxt->m_status, status_pass, status_fail))
        return ON_SubDEdgePtr::Create(nxt, (v == nxt->m_vertex[nxt_connecting_vertex_index]) ? 0 : 1);
    }

    break;
  }

  return ON_SubDEdgePtr::Null;
}

void ON_UniqueTester::Block::DeleteBlock(Block* blk)
{
  if (nullptr != blk)
    onfree(blk);
}

ON_UniqueTester::Block* ON_UniqueTester::Block::NewBlock()
{
  size_t sz1 = sizeof(Block);
  while (0 != sz1 % 8)
    sz1++;
  size_t sz2 = ON_UniqueTester::Block::BlockCapacity * sizeof(m_a[0]);
  void* p = onmalloc(sz1 + sz2);
  Block* blk = new (p) Block();
  blk->m_a = (ON__UINT_PTR*)(((char*)(p)) + sz1);
  return blk;
}

int ON_UniqueTester::Block::Compare(ON__UINT_PTR* lhs, ON__UINT_PTR* rhs)
{
  if (*lhs < *rhs)
    return -1;
  if (*lhs > *rhs)
    return 1;
  return 0;
}

bool ON_UniqueTester::Block::InBlock(size_t sorted_count,ON__UINT_PTR x) const
{
  if (nullptr != m_a && m_count > 0)
  {
    if ( sorted_count > 0 && x >= m_a[0] && x <= m_a[sorted_count - 1])
    {
      if (nullptr != bsearch(&x, m_a, sorted_count, sizeof(m_a[0]), (int(*)(const void*, const void*))ON_UniqueTester::Block::Compare))
        return true;
    }
    if (sorted_count < m_count)
    {
      const ON__UINT_PTR* p = m_a + sorted_count;
      const ON__UINT_PTR* p1 = m_a + m_count;
      while (p < p1)
      {
        if (x == *p++)
          return true;
      }
    }
  }
  return false;
}

void ON_UniqueTester::Block::SortBlock()
{
  ON_qsort(m_a, m_count, sizeof(m_a[0]), (int(*)(const void*, const void*))ON_UniqueTester::Block::Compare);
}

void ON_UniqueTester::Internal_CopyFrom(
  const ON_UniqueTester & src
)
{
  m_block_list = nullptr;
  m_sorted_count = 0;
 
  Block* first_blk = nullptr;

  for ( Block* src_blk = src.m_block_list; nullptr != src_blk; src_blk = src_blk->m_next)
  {
    Block* blk = Block::NewBlock();
    memcpy( blk->m_a, src_blk->m_a, src_blk->m_count * sizeof(blk->m_a[0]) );
    blk->m_count = src_blk->m_count;
    if (nullptr == first_blk)
    {
      first_blk = blk;
    }
    else
    {
      blk->m_next = m_block_list;
      m_block_list = blk;
    }
  }  

  if (nullptr != first_blk)
  {
    if (src.m_sorted_count != first_blk->m_count)
      first_blk->SortBlock();
    first_blk->m_next = m_block_list;
    m_block_list = first_blk;
    m_sorted_count = first_blk->m_count;
  }
}

void ON_UniqueTester::Internal_Destroy()
{
  Block* nxt = m_block_list;
  m_block_list = nullptr;
  m_sorted_count = 0;
  for ( Block* blk = nxt; nullptr != blk; blk = nxt)
  {
    nxt = blk->m_next;
    Block::DeleteBlock(blk);
  }  
}

ON_UniqueTester::~ON_UniqueTester()
{
  Internal_Destroy();
}

ON_UniqueTester::ON_UniqueTester(const ON_UniqueTester& src)
{
  Internal_CopyFrom(src);
}

ON_UniqueTester& ON_UniqueTester::operator=(const ON_UniqueTester& src)
{
  if (this != &src)
  {
    Internal_Destroy();
    Internal_CopyFrom(src);
  }
  return *this;
}

bool ON_UniqueTester::InList(ON__UINT_PTR x) const
{
  size_t sorted_count = m_sorted_count;
  for ( const Block* blk = m_block_list; nullptr != blk; blk = blk->m_next)
  {
    if (blk->InBlock(sorted_count, x))
      return true;
    sorted_count = ON_UniqueTester::Block::BlockCapacity;
  }  
  return false;
}

bool ON_UniqueTester::AddToList(ON__UINT_PTR x)
{
  if (nullptr != m_block_list && m_sorted_count + 50 == m_block_list->m_count)
  {
    m_block_list->SortBlock();
    m_sorted_count = m_block_list->m_count;
  }
  if (InList(x))
    return false;
  Internal_AddValue(x);
  return true;
}


void ON_UniqueTester::ExpertAddNewToList(ON__UINT_PTR x)
{
  Internal_AddValue(x);
}

void ON_UniqueTester::Internal_AddValue(ON__UINT_PTR x)
{
  if (nullptr == m_block_list || ON_UniqueTester::Block::BlockCapacity == m_block_list->m_count)
  {
    if (nullptr != m_block_list && m_sorted_count < ON_UniqueTester::Block::BlockCapacity)
      m_block_list->SortBlock();
    ON_UniqueTester::Block* blk = ON_UniqueTester::Block::NewBlock();
    blk->m_next = m_block_list;
    m_block_list = blk;
    m_sorted_count = 0;
  }
  m_block_list->m_a[m_block_list->m_count++] = x;
  if ( 1 == m_block_list->m_count
    || (m_sorted_count+1 == m_block_list->m_count && x > m_block_list->m_a[m_sorted_count-1])
    )
    ++m_sorted_count;
}

void ON_UniqueTester::ClearList()
{
  Internal_Destroy();
}

unsigned int ON_UniqueTester::Count() const
{
  size_t count = 0;
  for ( const Block* blk = m_block_list; nullptr != blk; blk = blk->m_next)
  {
    count += blk->m_count;
  }
  return (unsigned int)count;
}

bool ON_SubDEdgeChain::GetSideComponents(
  unsigned relative_side,
  ON_SimpleArray<ON_SubDComponentPtr>& side_components
) const
{
  return ON_SubDEdgeChain::GetSideComponents(EdgeChain(), relative_side, side_components);
}

bool ON_SubDEdgeChain::GetSideComponents(
  const ON_SimpleArray<ON_SubDEdgePtr>& edge_chain,
  unsigned relative_side,
  ON_SimpleArray<ON_SubDComponentPtr>& side_components
)
{
  side_components.SetCount(0);
  if (relative_side > 1U)
    return false;

  const unsigned edge_count = edge_chain.UnsignedCount();
  if (edge_count < 1)
    return false;

  if (false == ON_SubDEdgeChain::IsValidEdgeChain(edge_chain, true))
    return false; // bozo vaccine

  const bool bClosedLoop = edge_count >= 3 && edge_chain[0].RelativeVertex(0) == edge_chain[edge_count - 1].RelativeVertex(1);

  ON_SubDSectorIterator sit;
  const ON__INT_PTR sitdir = ((unsigned)1 - relative_side);

  ON_SubDEdgePtr chain_eptr1 = ON_SubDEdgePtr::Null;
  const ON_SubDFace* f1 = nullptr;
  const ON_SubDVertex* v = nullptr;
  if (false == bClosedLoop)
  {
    // first edge/face pair at the chain's initial vertex
    chain_eptr1 = edge_chain[0];
    f1 = chain_eptr1.RelativeFace(relative_side);
    if (nullptr != f1)
    {
      v = chain_eptr1.RelativeVertex(0);
      if (nullptr != v && v == sit.Initialize(f1, sitdir, v))
      {
        ON_SubDEdgePtr e = sit.CurrentEdgePtr(0);
        if (e.IsNotNull())
        {
          side_components.Append(ON_SubDComponentPtr::Create(e));
          side_components.Append(ON_SubDComponentPtr::Create(f1));
        }
      }
    }
  }
  else
  {
    chain_eptr1 = edge_chain[edge_count-1];
    f1 = chain_eptr1.RelativeFace(relative_side);
  }

  // first_side_components_edge is needed for closed loops.
  ON_SubDComponentPtr first_side_components_edge = ON_SubDComponentPtr::Null;
  for (unsigned j = bClosedLoop ? 0 : 1; j < edge_count; ++j)
  {
    chain_eptr1 = edge_chain[j];
    v = chain_eptr1.RelativeVertex(0);
    const ON_SubDFace* f0 = f1;
    f1 = chain_eptr1.RelativeFace(relative_side);
    if (nullptr != f0 && f0 == f1)
    {
      // side_components[] = ...f0,v,f1.
      unsigned n = side_components.UnsignedCount();
      if (0 == n || f0 != side_components[n-1].Face())
        side_components.Append(ON_SubDComponentPtr::Create(f0));
      side_components.Append(ON_SubDComponentPtr::Create(v));
      side_components.Append(ON_SubDComponentPtr::Create(f1));
      continue;
    }

    // sit_dex < sit_max prevents possiblity of an infinite loop if the chain or subd is corrupt
    const unsigned sit_max = v->FaceCount();
    unsigned sit_dex = 1;

    const ON_SubDFace* f = nullptr;
    for (;;)
    {
      if (nullptr == f0)
        break;

      if (nullptr == v || v != sit.Initialize(f0, sitdir, v))
        break;

      ON_SubDEdgePtr eptr = sit.CurrentEdgePtr(1);
      if (eptr.IsNull())
        break;

      unsigned n = side_components.UnsignedCount();
      if (0 == n || f0 != side_components[n - 1].Face())
        side_components.Append(ON_SubDComponentPtr::Create(f0));
      side_components.Append(ON_SubDComponentPtr::Create(eptr));
      if (first_side_components_edge.IsNull())
        first_side_components_edge = ON_SubDComponentPtr::Create(eptr); // needed for closed loops

      // The HasInteriorEdgeTopology() checks prevent getting garbage from
      // non-oriented SubDs. If people complain, they need to orient
      // their SubDs before asking "side" questions.
      // Some math nerd yokel is sure to stuff the boundary of
      // a mobius strip boundary into this function and then complain.
      // Too bad for them. [Dale Lear 2021]
      if (eptr.HasInteriorEdgeTopology(true))
      {
        for (f = sit.NextFace(ON_SubDSectorIterator::StopAt::Boundary), sit_dex = 1; nullptr != f && sit_dex < sit_max; f = sit.NextFace(ON_SubDSectorIterator::StopAt::Boundary), ++sit_dex)
        {
          if (f == f0)
            break;
          eptr = sit.CurrentEdgePtr(1);
          side_components.Append(ON_SubDComponentPtr::Create(f));
          if (f == f1)
            break;
          side_components.Append(ON_SubDComponentPtr::Create(eptr));
          if (false == eptr.HasInteriorEdgeTopology(true))
            break;
        }
      }
      break;
    }

    if (f == f1)
      continue;

    for (;;)
    {
      if (nullptr == f1)
        break;
      if (nullptr == v || v != sit.Initialize(f1, 1-sitdir, v))
        break;
      const ON_SubDEdgePtr eptr1 = sit.CurrentEdgePtr(1);
      const unsigned count0 = side_components.UnsignedCount();
      if (eptr1.HasInteriorEdgeTopology(true))
      {
        const ON_SubDFace* f2 = nullptr;
        for (f = sit.NextFace(ON_SubDSectorIterator::StopAt::Boundary), sit_dex = 1; nullptr != f && sit_dex < sit_max; f = sit.NextFace(ON_SubDSectorIterator::StopAt::Boundary), ++sit_dex)
        {
          if (f == f0 || f == f1)
          {
            f = nullptr;
            break;
          }
          f2 = f;
          if (false == sit.CurrentEdgePtr(1).HasInteriorEdgeTopology(true))
            break;
        }
        if (nullptr == f2)
          break;
        if (v != sit.Initialize(f2, sitdir, v))
          break;
        for (f = sit.CurrentFace(), sit_dex = 1; nullptr != f && sit_dex < sit_max; f = sit.NextFace(ON_SubDSectorIterator::StopAt::Boundary), ++sit_dex)
        {
          ON_SubDEdgePtr eptr = sit.CurrentEdgePtr(0);
          if (f == f0 || eptr.IsNull())
          {
            f = nullptr;
            break;
          }
          side_components.Append(ON_SubDComponentPtr::Create(eptr));
          side_components.Append(ON_SubDComponentPtr::Create(f));
          if (f == f1)
            break;
          eptr = sit.CurrentEdgePtr(1);
          if (false == eptr.HasInteriorEdgeTopology(true))
          {
            f = nullptr;
            break;
          }
        }
        if (f != f1)
        {
          side_components.SetCount(count0);
        }
      }
      if ( count0 == side_components.UnsignedCount() && eptr1.IsNotNull() )
      {
        side_components.Append(ON_SubDComponentPtr::Create(eptr1));
        side_components.Append(ON_SubDComponentPtr::Create(f1));
      }
      break;
    }
  }

  if (bClosedLoop)
  {
    const unsigned side_components_count = side_components.UnsignedCount();
    if (side_components_count >= 6
      && first_side_components_edge.IsEdge()
      && side_components[0].IsFace()
      && side_components[0].Face() == side_components[side_components_count-1].Face()
      )
    {
      // rearrange side_components[] so it begins with first_side_components_eptr.
      // This eliminates the complexity of having to begin/end a SubD fillet
      // at a ... f,v,f ... location.
      const ON_SubDFace* f = side_components[0].Face();
      if (nullptr == f)
      {
        ON_SUBD_ERROR("f should be non-null.");
      }
      else
      {
        // set j0 = current side_components[] index of the first edge
        unsigned j0 = side_components_count;
        for (unsigned j = 0; j < side_components_count; ++j)
        {
          if (first_side_components_edge.m_ptr == side_components[j].m_ptr)
          {
            j0 = j;
            break;
          }
        }
        if (j0 > 0 && j0 < side_components_count)
        {
          ON_SimpleArray<ON_SubDComponentPtr> tail;
          tail.Append((int)(j0-1), side_components.Array() + 1);
          for (unsigned k = 0; k + j0 < side_components_count; ++k)
            side_components[k] = side_components[j0 + k];
          side_components.SetCount(side_components_count - j0);
          side_components.Append(tail.Count(), tail.Array());
          side_components.Append(first_side_components_edge);
        }
      }
    }
  }
  else
  {
    // last edge at the chain's final vertex
    chain_eptr1 = edge_chain[edge_count - 1];
    f1 = chain_eptr1.RelativeFace(relative_side);
    if (nullptr != f1)
    {
      v = chain_eptr1.RelativeVertex(1);
      if (nullptr != v && v == sit.Initialize(f1, sitdir, v))
      {
        ON_SubDEdgePtr eptr = sit.CurrentEdgePtr(1);
        if (eptr.IsNotNull())
        {
          unsigned n = side_components.UnsignedCount();
          if (0 == n || f1 != side_components[n - 1].Face())
            side_components.Append(ON_SubDComponentPtr::Create(f1));
          side_components.Append(ON_SubDComponentPtr::Create(eptr));
        }
      }
    }
  }

  return side_components.UnsignedCount() > 0;
}

const ON_SimpleArray<ON_SubDEdgePtr>& ON_SubDEdgeChain::EdgeChain() const
{
  return m_edge_chain;
}

const ON_SubD& ON_SubDEdgeChain::SubD() const
{
  return m_subd_ref.SubD();
}

const ON_SubDRef ON_SubDEdgeChain::SubDRef() const
{
  return m_subd_ref;
}

bool ON_SubDEdgeChain::InChain(
  const ON_SubDEdgePtr edge_ptr
) const
{
  return InChain(ON_SUBD_EDGE_POINTER(edge_ptr.m_ptr));
}

bool ON_SubDEdgeChain::InChain(
  const ON_SubDEdge* edge
) const
{
  return (nullptr == edge) ? false : m_unique_tester.InList((ON__UINT_PTR)edge);
}

bool ON_SubDEdgeChain::InChain(
  const ON_SubDVertex* vertex
) const
{
  return (nullptr == vertex) ? false : m_unique_tester.InList((ON__UINT_PTR)vertex);
}

bool ON_SubDEdgeChain::IsClosedLoop() const
{
  const unsigned int count = m_edge_chain.UnsignedCount();
  return (count >= 3 && m_edge_chain[0].RelativeVertex(0) == m_edge_chain[count - 1].RelativeVertex(1));
}

bool ON_SubDEdgeChain::IsConvexLoop(bool bStrictlyConvex) const
{
  if (false == IsClosedLoop())
    return false;

  const unsigned int count = m_edge_chain.UnsignedCount();
  ON_SimpleArray<ON_3dPoint> points(count);
  for (unsigned int i = 0; i < count; ++i)  
  {
    const ON_SubDVertex* v = m_edge_chain[i].RelativeVertex(0);
    if (nullptr == v)
      return false;
    points.Append(v->ControlNetPoint());
  }
  if ( false == (points[0] != points[count - 1]) )
    return false;

  return ON_IsConvexPolyline(points, bStrictlyConvex);
}


unsigned int ON_SubDEdgeChain::BeginEdgeChain(
  ON_UUID persistent_subd_id,
  ON_SubDRef subd_ref,
  const ON_SubDEdge* initial_edge
)
{
  return ON_SubDEdgeChain::BeginEdgeChain(persistent_subd_id, subd_ref, ON_SubDEdgePtr::Create(initial_edge, 0));
}

unsigned int ON_SubDEdgeChain::BeginEdgeChain(
  ON_UUID persistent_subd_id,
  ON_SubDRef subd_ref,
  const ON_SimpleArray<const ON_SubDEdge* >& initial_edge_chain
)
{
  return BeginEdgeChain(persistent_subd_id, subd_ref, initial_edge_chain.Array(), initial_edge_chain.UnsignedCount());
}

unsigned int ON_SubDEdgeChain::BeginEdgeChain(
  ON_UUID persistent_subd_id,
  ON_SubDRef subd_ref,
  const ON_SubDEdge*const* initial_edge_chain,
  size_t edge_count
)
{
  ClearEdgeChain();

  if (
    edge_count <= 0 
    || subd_ref.SubD().IsEmpty() 
    || subd_ref.SubD().EdgeCount() < (unsigned int)edge_count
    )
    return 0;

  if ( 1 == edge_count)
    return ON_SubDEdgeChain::BeginEdgeChain(persistent_subd_id, subd_ref, ON_SubDEdgePtr::Create(initial_edge_chain[0], 0));

  const ON_SubDEdge* e0 = initial_edge_chain[0];
  if (nullptr == e0 || nullptr == e0->m_vertex[0] || nullptr == e0->m_vertex[1] )
    return 0;
  const ON_SubDEdge* e1 = initial_edge_chain[1];
  if (nullptr == e1 || nullptr == e1->m_vertex[0] || nullptr == e1->m_vertex[1] )
    return 0;


  ON_SubDEdgePtr eptr = ON_SubDEdgePtr::Create(e0, (e0->m_vertex[1] == e1->m_vertex[0] || e0->m_vertex[1] == e1->m_vertex[1]) ? 0 : 1);

  ON_SimpleArray<ON_SubDEdgePtr> eptr_chain(edge_count);
  eptr_chain.Append(eptr);
  const ON_SubDVertex* v = eptr.RelativeVertex(1);
  for (unsigned int i = 1; i < edge_count; i++)
  {
    e1 = initial_edge_chain[i];
    if (nullptr == e1 || nullptr == e1->m_vertex[0] || nullptr == e1->m_vertex[1] )
      return 0;
    if (v != e1->m_vertex[0] && v != e1->m_vertex[1])
      return 0;
    eptr = ON_SubDEdgePtr::Create(e1, (v == e1->m_vertex[0]) ? 0 : 1);
    eptr_chain.Append(eptr);
  }

  return ON_SubDEdgeChain::BeginEdgeChain(persistent_subd_id, subd_ref,eptr_chain);
}

unsigned int ON_SubDEdgeChain::BeginEdgeChain(
  ON_UUID persistent_subd_id,
  ON_SubDRef subd_ref,
  ON_SubDEdgePtr eptr
)
{
  return ON_SubDEdgeChain::BeginEdgeChain(persistent_subd_id, subd_ref, &eptr, 1);
}

unsigned int ON_SubDEdgeChain::BeginEdgeChain(
  ON_UUID persistent_subd_id,
  ON_SubDRef subd_ref,
  const ON_SimpleArray<ON_SubDEdgePtr>& initial_edge_chain
)
{
  return ON_SubDEdgeChain::BeginEdgeChain(persistent_subd_id, subd_ref, initial_edge_chain.Array(), initial_edge_chain.UnsignedCount() );
}

unsigned int ON_SubDEdgeChain::BeginEdgeChain(
  ON_UUID persistent_subd_id,
  ON_SubDRef subd_ref,
  const ON_SubDEdgePtr* initial_edge_chain,
  size_t edge_count
  )
{
  ClearEdgeChain();

  m_persistent_subd_id = persistent_subd_id;
  m_subd_ref = subd_ref;

  if (edge_count <= 0 || m_subd_ref.SubD().IsEmpty())
    return 0;

  if ( ((size_t)subd_ref.SubD().EdgeCount()) < edge_count )
    return 0;

  m_edge_chain.Reserve(edge_count + 128);
  const ON_SubDVertex* first_vertex = nullptr;
  const ON_SubDVertex* last_vertex = nullptr;
  for (size_t i = 0; i < edge_count; i++)
  {
    const ON_SubDEdgePtr eptr = initial_edge_chain[i];
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
    if (nullptr == e)
      continue;
    if (m_unique_tester.InList((ON__UINT_PTR)e))
      continue;
    const ON__UINT_PTR edir = ON_SUBD_EDGE_DIRECTION(eptr.m_ptr);
    const ON_SubDVertex* v[2] = { e->m_vertex[edir], e->m_vertex[1 - edir] };
    if (nullptr == v[0] || nullptr == v[1] || v[0] == v[1] )
      continue;
    if (nullptr == first_vertex)
    {
      first_vertex = v[0];
      last_vertex = v[1];
      m_unique_tester.ExpertAddNewToList((ON__UINT_PTR)first_vertex);
      m_unique_tester.ExpertAddNewToList((ON__UINT_PTR)last_vertex);
    }
    else 
    {
      if (last_vertex != v[0])
        continue;
      if (v[1] != first_vertex)
      {
        if (false == m_unique_tester.AddToList((ON__UINT_PTR)v[1]))
          continue;
      }
    }
    m_edge_chain.Append(eptr);
    m_unique_tester.ExpertAddNewToList((ON__UINT_PTR)e);
    last_vertex = v[1];
    if (last_vertex == first_vertex)
      break;
  };

  return m_edge_chain.UnsignedCount();
}

const ON_UUID ON_SubDEdgeChain::PersistentSubDId() const
{
  return m_persistent_subd_id;
}

bool ON_SubDEdgeChain::HasPersistentEdgeIds() const
{
  const unsigned count = this->EdgeCount();
  return
    count > 0
    && count == m_persistent_edge_id.UnsignedCount()
    && count == m_persistent_edge_orientation.UnsignedCount()
    ;
}

bool ON_SubDEdgeChain::HasRuntimeEdgePtrs() const
{
  const unsigned count = this->EdgeCount();
  return
    count > 0
    && count == this->m_edge_chain.UnsignedCount()
    && m_subd_ref.SubD().EdgeCount() > 0
    ;
}

bool ON_SubDEdgeChain::SetPersistentEdgeIdsFromRuntimeEdgePtrs() const
{
  m_persistent_edge_id.SetCount(0);
  m_persistent_edge_orientation.SetCount(0); 
  const unsigned count = (m_subd_ref.SubD().EdgeCount() > 0) ? m_edge_chain.UnsignedCount() : 0;
  bool rc = count > 0;
  if (rc)
  {
    m_persistent_edge_id.Reserve(count);
    m_persistent_edge_orientation.Reserve(count);
    for (unsigned i = 0; i < count; ++i)
    {
      const ON_SubDEdgePtr eptr = m_edge_chain[i];
      const unsigned edge_id = eptr.EdgeId();
      if (edge_id <= 0)
        break;
      if (false == eptr.IsActive())
        break;
      m_persistent_edge_id.Append(edge_id);
      m_persistent_edge_orientation.Append(0 == eptr.EdgeDirection() ? 0 : 1);
    }
    if (count != m_persistent_edge_id.UnsignedCount() || count != m_persistent_edge_orientation.UnsignedCount())
    {
      rc = false;
      m_persistent_edge_id.SetCount(0);
      m_persistent_edge_orientation.SetCount(0);
    }
  }
  return rc;
}

bool ON_SubDEdgeChain::SetRuntimeEdgePtrsFromPersistentSubD(
  ON_UUID persistent_subd_id,
  ON_SubDRef persistent_subd_ref
)
{
  bool rc = true;
  m_edge_chain.SetCount(0);
  const unsigned count = m_persistent_edge_id.UnsignedCount();
  const ON_SubD& subd = persistent_subd_ref.SubD();
  if (count > 0 && count == m_persistent_edge_orientation.UnsignedCount() && subd.EdgeCount() > 0)
  {
    rc = false;
    ON_SimpleArray<ON_SubDEdgePtr> local_edge_chain(count);
    for (unsigned i = 0; i < count; ++i)
    {
      const ON_SubDEdge* e = subd.EdgeFromId(m_persistent_edge_id[i]);
      if (nullptr == e)
        break;
      const ON_SubDEdgePtr eptr = ON_SubDEdgePtr::Create(e, (1 == m_persistent_edge_orientation[i]) ? 1 : 0);
      local_edge_chain.Append(eptr);
    }
    if (count == local_edge_chain.UnsignedCount())
    {
      if (ON_SubDEdgeChain::IsValidEdgeChain(local_edge_chain, false))
      {
        m_edge_chain = local_edge_chain;
        rc = true;
      }
    }
  }
  if (persistent_subd_ref.SubD().RuntimeSerialNumber() != m_subd_ref.SubD().RuntimeSerialNumber())
    m_subd_ref = persistent_subd_ref;
  if (ON_UuidIsNotNil(persistent_subd_id) && 0 != ON_UuidCompare(m_persistent_subd_id, persistent_subd_id))
    m_persistent_subd_id = persistent_subd_id;
  return rc;
}

bool ON_SubDEdgeChain::Write(class ON_BinaryArchive& archive) const
{
  // This write has to work if a read happened but the m_edge_chain[] was never set.
  if (m_edge_chain.UnsignedCount() > 0)
    SetPersistentEdgeIdsFromRuntimeEdgePtrs();
  const unsigned count = m_persistent_edge_id.UnsignedCount();

  if (false == archive.BeginWrite3dmAnonymousChunk(1))
    return false;

  bool rc = false;
  for (;;)
  {
    if (false == archive.WriteUuid(m_persistent_subd_id))
      break;
    if (false == archive.WriteInt(count))
      break;
    if (count > 0)
    {
      if (false == archive.WriteArray(m_persistent_edge_id))
        break;
      if (false == archive.WriteArray(m_persistent_edge_orientation))
        break;
    }

    rc = true;
    break;
  }

  if (false == archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_SubDEdgeChain::Read(class ON_BinaryArchive& archive)
{
  *this = ON_SubDEdgeChain::Empty;

  int chunk_version = 0;
  if (false == archive.BeginRead3dmAnonymousChunk(&chunk_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (chunk_version < 1)
      break;
    if (false == archive.ReadUuid(m_persistent_subd_id))
      break;
    unsigned int count = 0;
    if (false == archive.ReadInt(&count))
      break;
    if (count > 0)
    {
      if (false == archive.ReadArray(m_persistent_edge_id))
        break;
      if (false == archive.ReadArray(m_persistent_edge_orientation))
        break;
    }

    if (count != m_persistent_edge_id.UnsignedCount() || count != m_persistent_edge_orientation.UnsignedCount())
    {
      m_persistent_edge_id.SetCount(0);
      m_persistent_edge_orientation.SetCount(0);
    }

    rc = true;
    break;
  }

  if (false == archive.EndRead3dmChunk())
    rc = false;

  // At some point, the caller will need to find the subd for this edge chain and call SetRuntimeEdgePtrsFromPersistentSubD().

  return rc;
}

void ON_SubDEdgeChain::Dump(class ON_TextLog& text_log) const
{
  const unsigned edge_count = EdgeCount();
  const ON__UINT64 subd_sn = m_subd_ref.SubD().EdgeCount() > 0 ? m_subd_ref.SubD().RuntimeSerialNumber() : 0;
  const bool bSubDIdIsNotNil = ON_UuidIsNotNil(m_persistent_subd_id);
  if (edge_count > 0 && (0 != subd_sn || bSubDIdIsNotNil))
  {
    if (0 != subd_sn)
    {
      text_log.Print(L"SubD[%" PRIu64 "]", subd_sn);
      if (bSubDIdIsNotNil)
      {
        text_log.Print(L" persistent SubD id = ");
        text_log.Print(m_persistent_subd_id);
      }
    }
    else
    {
      text_log.Print(L"Persistent SubD id = ");
      text_log.Print(m_persistent_subd_id);
    }
    text_log.Print("%u edges.\n", edge_count);

    const bool bPrintEdgePtr = (subd_sn != 0 && edge_count == m_edge_chain.UnsignedCount());
    const bool bPrintPersistentEdgeId = 
      false == bPrintEdgePtr
      && edge_count == m_persistent_edge_id.UnsignedCount()
      && edge_count == m_persistent_edge_orientation.UnsignedCount();
    ON_TextLogIndent indent1(text_log);
    if (bPrintEdgePtr || bPrintPersistentEdgeId)
    {
      const wchar_t plus_minus[3] = { '+', '-', '?' };
      for (unsigned i = 0; i < edge_count; ++i)
      {
        if (0 != i)
          text_log.Print(L", ");
        unsigned sign_dex = 2;
        unsigned edge_id = 0;
        if (bPrintEdgePtr)
        {
          const ON_SubDEdgePtr eptr = m_edge_chain[i];
          sign_dex = 0 != eptr.EdgeDirection() ? 1 : 0;
          edge_id = eptr.EdgeId();
        }
        else if (bPrintPersistentEdgeId)
        {
          sign_dex = 0 != m_persistent_edge_orientation[i] ? 1 : 0;
          edge_id = m_persistent_edge_id[i];
        }
        text_log.Print(L"%lce%u", plus_minus[sign_dex], edge_id);
        if (i == 5 && edge_count > 15)
        {
          text_log.Print(L", ...");
          i = edge_count - 5;
        }
      }
    }
    else
    {
      text_log.Print("Corrupt edge list.");
    }
  }
  else if( 0 == edge_count)
  {
    text_log.Print("Empty SubD edge chain.");
  }
  else
  {
    text_log.Print("Corrupt SubD edge chain.");
  }
  text_log.PrintNewLine();

}

void ON_SubDEdgeChain::ClearEdgeChain()
{
  m_edge_chain.SetCount(0);
  m_unique_tester.ClearList();
}

unsigned int ON_SubDEdgeChain::EdgeCount() const
{
  const unsigned edge_count = m_edge_chain.UnsignedCount();
  if (edge_count > 0)
    return edge_count;
  const unsigned id_count = (ON_UuidIsNotNil(this->m_persistent_subd_id)) ? m_persistent_edge_id.UnsignedCount() : 0;
  if (id_count > 0 && id_count == m_persistent_edge_orientation.UnsignedCount())
    return id_count;
  return 0;
}

void ON_SubDEdgeChain::SetStatusCheck(
  bool bEnableStatusCheck,
  ON_ComponentStatus status_check_pass,
  ON_ComponentStatus status_check_fail
)
{
  m_bEnableStatusCheck = bEnableStatusCheck ? true : false;
  m_status_check_pass = status_check_pass;
  m_status_check_fail = status_check_fail;  
}

bool ON_SubDEdgeChain::StatusCheckEnabled() const
{
  return m_bEnableStatusCheck;
}

void ON_SubDEdgeChain::Reverse()
{
  ON_SubDEdgeChain::ReverseEdgeChain(m_edge_chain);
}

const ON_SubDEdgePtr ON_SubDEdgeChain::FirstEdgePtr() const
{
  return m_edge_chain.UnsignedCount() > 0 ? m_edge_chain[0] : ON_SubDEdgePtr::Null;
}
const ON_SubDEdgePtr ON_SubDEdgeChain::LastEdgePtr() const
{
  return m_edge_chain.UnsignedCount() > 0 ? *(m_edge_chain.Last()) : ON_SubDEdgePtr::Null;
}

const ON_SubDEdgePtr ON_SubDEdgeChain::EdgePtr(int edge_index) const
{
  return (edge_index >= 0 && edge_index < m_edge_chain.Count()) ? m_edge_chain[edge_index] : ON_SubDEdgePtr::Null;
}

const ON_SubDEdge* ON_SubDEdgeChain::FirstEdge() const
{
  return FirstEdgePtr().Edge();
}

const ON_SubDEdge* ON_SubDEdgeChain::LastEdge() const
{
  return LastEdgePtr().Edge();
}

const ON_SubDEdge* ON_SubDEdgeChain::Edge(int edge_index) const
{
  return EdgePtr(edge_index).Edge();
}

const ON_SubDVertex* ON_SubDEdgeChain::FirstVertex() const
{
  return Vertex(0);
}

const ON_SubDVertex* ON_SubDEdgeChain::LastVertex() const
{
  return Vertex(m_edge_chain.Count());
}

const ON_SubDVertex* ON_SubDEdgeChain::Vertex(int vertex_index) const
{
  const int edge_count = m_edge_chain.Count();
  if ( vertex_index >= 0 && vertex_index <= edge_count && edge_count > 0 )
  {
    return 
      (vertex_index == edge_count)
      ? m_edge_chain[edge_count - 1].RelativeVertex(1)
      : m_edge_chain[vertex_index].RelativeVertex(0);
  }
  return nullptr;
}

const ON_3dPoint ON_SubDEdgeChain::FirstControlNetPoint() const
{
  const ON_SubDVertex* v = FirstVertex();
  return (nullptr != v) ? v->ControlNetPoint() : ON_3dPoint::NanPoint;
}

const ON_3dPoint ON_SubDEdgeChain::LastControlNetPoint() const
{
  const ON_SubDVertex* v = LastVertex();
  return (nullptr != v) ? v->ControlNetPoint() : ON_3dPoint::NanPoint;
}

const ON_3dPoint ON_SubDEdgeChain::ControlNetPoint(int vertex_index) const
{
  const ON_SubDVertex* v = Vertex(vertex_index);
  return (nullptr != v) ? v->ControlNetPoint() : ON_3dPoint::NanPoint;
}



unsigned int ON_SubDEdgeChain::AddOneNeighbor(
  ON_ChainDirection direction,
  ON_SubD::ChainType chain_type
)
{
  const unsigned int count0 = m_edge_chain.UnsignedCount();
  if (count0 <= 0 || IsClosedLoop() )
    return 0;

  ON_SubDEdgePtr eptr;
  const ON_SubDEdge* e;
  const ON_SubDVertex* v;

  const ON_SubDVertex* chain_ends[2] = { FirstVertex() ,LastVertex() };

  eptr
    = (ON_ChainDirection::Previous != direction)
    ? ON_SubDEdgeChain::EdgeChainNeighbor(LastEdgePtr(), ON_ChainDirection::Next, chain_type, m_bEnableStatusCheck, m_status_check_pass, m_status_check_fail)
    : ON_SubDEdgePtr::Null;
  e = eptr.Edge();
  v = eptr.RelativeVertex(0);
  if ( nullptr != v && v == chain_ends[1] && false == InChain(e) )
  {
    v = eptr.RelativeVertex(1);
    if (v == chain_ends[0] || m_unique_tester.AddToList((ON__UINT_PTR)v))
    {
      m_unique_tester.ExpertAddNewToList((ON__UINT_PTR)e);
      m_edge_chain.Append(eptr);
    }
  }

  eptr
    = (ON_ChainDirection::Next != direction)
    ? ON_SubDEdgeChain::EdgeChainNeighbor(FirstEdgePtr(), ON_ChainDirection::Previous, chain_type, m_bEnableStatusCheck, m_status_check_pass, m_status_check_fail)
    : ON_SubDEdgePtr::Null;
  e = eptr.Edge();
  v = eptr.RelativeVertex(1);
  if ( nullptr != v && v == chain_ends[0] && false == InChain(e) )
  {
    v = eptr.RelativeVertex(0);
    if (v == chain_ends[1] || m_unique_tester.AddToList((ON__UINT_PTR)v))
    {
      m_unique_tester.ExpertAddNewToList((ON__UINT_PTR)e);
      m_edge_chain.Insert(0, eptr);
    }
  }

  return m_edge_chain.UnsignedCount() - count0;
}

unsigned int ON_SubDEdgeChain::AddAllNeighbors(
  ON_ChainDirection direction,
  ON_SubD::ChainType chain_type
)
{
  const unsigned int count0 = m_edge_chain.UnsignedCount();
  if (count0 <= 0 || IsClosedLoop())
    return 0;

  if (ON_ChainDirection::Previous != direction)
    while (1 == AddOneNeighbor(ON_ChainDirection::Next, chain_type)) {}      
  if (ON_ChainDirection::Next != direction)
    while (1 == AddOneNeighbor(ON_ChainDirection::Previous, chain_type)) {}      

  return m_edge_chain.UnsignedCount() - count0;
}

unsigned int ON_SubDEdgeChain::AddEdge(
  const ON_SubDEdge* edge
) 
{
  const unsigned int count0 = m_edge_chain.UnsignedCount();
  if (count0 <= 0)
    return 0;

  if (
    nullptr == edge 
    || nullptr == edge->m_vertex[0]
    || nullptr == edge->m_vertex[1] 
    || edge->m_vertex[0] == edge->m_vertex[1]
    )
    return 0;

  const ON_SubDVertex* v[2] = { FirstVertex(),LastVertex() };
  if (v[0] == v[1])
    return 0;

  if ( m_bEnableStatusCheck && false == ON_ComponentStatus::StatusCheck(edge->m_status, m_status_check_pass, m_status_check_fail))
    return 0;

  ON_SubDEdgePtr eptr = ON_SubDEdgePtr::Null;

  if (v[1] == edge->m_vertex[0])
    eptr = ON_SubDEdgePtr::Create(edge, 0);
  else if (v[1] == edge->m_vertex[1])
    eptr = ON_SubDEdgePtr::Create(edge, 1);
  else if (v[0] == edge->m_vertex[1])
    eptr = ON_SubDEdgePtr::Create(edge, 0);
  else if (v[0] == edge->m_vertex[0])
    eptr = ON_SubDEdgePtr::Create(edge, 1);
  else
    return 0;

  if (m_unique_tester.InList((ON__UINT_PTR)edge))
    return 0;

  if (v[1] == eptr.RelativeVertex(0) )
  {
    if (v[0] == eptr.RelativeVertex(1) || m_unique_tester.AddToList((ON__UINT_PTR)eptr.RelativeVertex(1)))
    {
      m_edge_chain.Append(eptr);
      m_unique_tester.ExpertAddNewToList((ON__UINT_PTR)edge);
    }
  }
  else if (v[0] == eptr.RelativeVertex(1) )
  {
    if (v[1] == eptr.RelativeVertex(0) || m_unique_tester.AddToList((ON__UINT_PTR)eptr.RelativeVertex(0)))
    {
      m_edge_chain.Insert(0, eptr);
      m_unique_tester.ExpertAddNewToList((ON__UINT_PTR)edge);
    }
  }

  return m_edge_chain.UnsignedCount() - count0;
}

unsigned int ON_SubDEdgeChain::RemoveEdges(
  const ON_SubDEdge* first_edge,
  const ON_SubDEdge* last_edge
) 
{
  unsigned int count0 = m_edge_chain.UnsignedCount();
  unsigned int i0 = 0;
  unsigned int i1 = count0;
  if (nullptr != first_edge)
  {
    while (i0 < count0 && first_edge != m_edge_chain[i0].Edge())
      ++i0;
  }
  if (nullptr != last_edge)
  {
    while (i1 > i0 && last_edge != m_edge_chain[i1 - 1].Edge())
      --i1;
  }

  const unsigned int count1 = i1 - i0;
  if (count1 >= count0)
    return 0;

  if (i0 > 0)
  {
    for (unsigned int i = i0; i < i1; i++)
      m_edge_chain[i - i0] = m_edge_chain[i];
  }

  m_edge_chain.SetCount(count1);
  m_unique_tester.ClearList();
  for (unsigned int i = 0; i < count1; i++)
  {
    m_unique_tester.AddToList((ON__UINT_PTR)m_edge_chain[i].Edge());
    m_unique_tester.AddToList((ON__UINT_PTR)m_edge_chain[i].RelativeVertex(0));
  }
  if ( FirstVertex() != LastVertex() )
    m_unique_tester.AddToList((ON__UINT_PTR)LastVertex());

  return count0 - count1;
}


void ON_SubDEdgeChain::ReverseEdgeChain(
  ON_SimpleArray< ON_SubDEdgePtr >& edge_chain
)
{
  ON_SubDEdgeChain::ReverseEdgeChain(edge_chain.Array(), edge_chain.UnsignedCount());
}

void ON_SubDEdgeChain::ReverseEdgeChain(
  ON_SubDEdgePtr* edge_chain,
  size_t edge_count
  )
{
  if (edge_count <= 0 || nullptr == edge_chain)
    return;
  ON_SubDEdgePtr* p0 = edge_chain;
  ON_SubDEdgePtr* p1 = p0 + (edge_count - 1);
  while ( p0 < p1)
  {
    ON_SubDEdgePtr eptr = p0->Reversed();
    *p0 = p1->Reversed();
    *p1 = eptr;
    ++p0;
    --p1;
  }
  if (p0 == p1)
    *p0 = p0->Reversed();
}

bool ON_SubDEdgeChain::IsValidEdgeChain(
  const ON_SimpleArray< ON_SubDEdgePtr >& edge_chain,
  bool bCheckForDuplicateEdges
)
{
  return ON_SubDEdgeChain::IsValidEdgeChain(edge_chain.Array(), edge_chain.UnsignedCount(), bCheckForDuplicateEdges);
}

bool ON_SubDEdgeChain::IsValidEdgeChain(
  const ON_SubDEdgePtr* edge_chain,
  size_t edge_count,
  bool bCheckForDuplicateEdges
)
{
  if (edge_count <= 0)
    return true;
  if (nullptr == edge_chain)
    return false;

  const ON_SubDVertex* first_vertex = edge_chain->RelativeVertex(0);
  if (nullptr == first_vertex)
    return false;

  const ON_SubDVertex* v = first_vertex;
  const ON_SubDEdgePtr* p0 = edge_chain;
  const ON_SubDEdgePtr* p1 = edge_chain+1;

  for (const ON_SubDEdgePtr* p = p0; p < p1; ++p)
  {
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(p->m_ptr);
    if (nullptr == e || nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
      return false;
    ON__UINT_PTR edir = ON_SUBD_EDGE_DIRECTION(p->m_ptr);
    const ON_SubDVertex* v0 = e->m_vertex[edir];
    const ON_SubDVertex* v1 = e->m_vertex[1 - edir];
    if (v0 != v || nullptr == v1 || v0 == v1)
      return false;
    v = v1;
  }

  if (bCheckForDuplicateEdges)
  {
    const ON_SubDVertex* last_vertex = v;
    ON_UniqueTester tester;
    for (const ON_SubDEdgePtr* p = p0; p < p1; ++p)
    {
      const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(p->m_ptr);
      if (false == tester.AddToList((ON__UINT_PTR)e))
        return false; // duplicate edge
      if (false == tester.AddToList((ON__UINT_PTR)e->m_vertex[ON_SUBD_EDGE_DIRECTION(p->m_ptr)]))
        return false; // duplicate vertex
    }    
    if (first_vertex != last_vertex)
    {
      if (false == tester.AddToList((ON__UINT_PTR)last_vertex))
        return false; // duplicate vertex
    }
  }

  return true;
}

class ON_SubDMeshImpl* ON_SubDMesh::SubLimple() const
{
  return m_impl_sp.get();
}

unsigned int ON_SubDMesh::SubLimpleUseCount() const
{
  return (unsigned int)(m_impl_sp.use_count());
}


bool ON_SubD::IsSolid() const
{
  bool bIsManifold = false;
  bool bIsOriented = false;
  bool bHasBoundary = false;
  int solid_orientation = 0;
  ActiveLevel().GetTopologicalAttributes(bIsManifold, bIsOriented, bHasBoundary, solid_orientation);
  return (bIsManifold && bIsOriented && false == bHasBoundary);
}

int ON_SubD::SolidOrientation() const
{
  bool bIsManifold = false;
  bool bIsOriented = false;
  bool bHasBoundary = false;
  int solid_orientation = 0;
  ActiveLevel().GetTopologicalAttributes(bIsManifold, bIsOriented, bHasBoundary, solid_orientation);
  return solid_orientation;
}

bool ON_SubD::IsManifold( bool& bIsOriented, bool& bHasBoundary ) const
{
  bool bIsManifold = false;
  bIsOriented = false;
  bHasBoundary = false;
  int solid_orientation = 0;
  ActiveLevel().GetTopologicalAttributes(bIsManifold, bIsOriented, bHasBoundary, solid_orientation);
  return bIsManifold;
}

bool ON_SubD::IsManifold() const
{
  bool bIsOriented = false;
  bool bHasBoundary = false;
  return IsManifold(bIsOriented, bHasBoundary);
}

#ifdef ON_DEBUG
static bool Internal_UnrollChain(const ON_SimpleArray<ON_SubDEdgePtr>& chain) {
  const unsigned imax{chain.UnsignedCount()};
  ON_SimpleArray<bool> reversed_dirs{(size_t)imax};
  ON_SimpleArray<const ON_SubDEdge*> edges{(size_t)imax};
  ON_SimpleArray<const ON_SubDVertex*> vertices{(size_t)2 * (size_t)imax};
  ON_SimpleArray<unsigned> edge_ids{(size_t)imax};
  ON_SimpleArray<unsigned> vertice_ids{(size_t)2 * (size_t)imax};
  const unsigned int max_id = 0xFFFFFFFFU;
  for (unsigned i = 0; i < imax; ++i) {
    ON_SubDEdgePtr eptr = chain[i];
    const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
    if (nullptr == e) {
      reversed_dirs.Append(false);
      edges.Append(nullptr);
      vertices.Append(nullptr);
      vertices.Append(nullptr);
      edge_ids.Append(max_id);
      vertice_ids.Append(max_id);
      vertice_ids.Append(max_id);
      continue;
    }
    edges.Append(e);
    edge_ids.Append(e->m_id);
    ON__UINT_PTR edir = ON_SUBD_EDGE_DIRECTION(eptr.m_ptr);
    reversed_dirs.Append(edir == 0 ? false : true);
    const ON_SubDVertex* v[2] = {e->m_vertex[edir], e->m_vertex[1 - edir]};
    vertices.Append(v[0]);
    vertices.Append(v[1]);
    vertice_ids.Append(v[0] == nullptr ? max_id : v[0]->m_id);
    vertice_ids.Append(v[1] == nullptr ? max_id : v[1]->m_id);
  }
  return true;
}

static bool Internal_VerifyEdgeChain(
    const ON_SimpleArray<ON_SubDEdgePtr>& chain, ON_2udex& chaindex,
    unsigned* edge_count = nullptr) {
  bool valid_chain{true};
  unsigned valid_edge_count = 0U;
  const unsigned jmax{chain.UnsignedCount()};
  ON_SubDEdgePtr eptr = chain[chaindex.i];
  const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
  if (nullptr == e) {
    if (edge_count != nullptr) *edge_count = 0;
    return false;
  }
  ON__UINT_PTR edir = ON_SUBD_EDGE_DIRECTION(eptr.m_ptr);
  const ON_SubDVertex* v[2] = {e->m_vertex[edir], e->m_vertex[1 - edir]};
  if (nullptr == v[0] || nullptr == v[1] || v[0] == v[1]) {
    if (edge_count != nullptr) *edge_count = 0;
    return false;
  }
  ++valid_edge_count;
  for (chaindex.j = chaindex.i + 1; chaindex.j < jmax; ++chaindex.j) {
    valid_chain = false;
    eptr = chain[chaindex.j];
    e = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
    if (nullptr == e) { 
      // End of chain marker
      valid_chain = true;
      if (chaindex.j < jmax) ++chaindex.j;
      break;
    }
    if (nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1] ||
        e->m_vertex[0] == e->m_vertex[1]) {
      break;
    }
    edir = ON_SUBD_EDGE_DIRECTION(eptr.m_ptr);
    if (v[1] != e->m_vertex[edir]) {
      if (edge_count == nullptr) valid_chain = true;
      break;
    }
    v[1] = e->m_vertex[1 - edir];
    ++valid_edge_count;
    valid_chain = true;
  }
  if (edge_count != nullptr && *edge_count != valid_edge_count) {
    *edge_count = valid_edge_count;
    return false;
  }
  return valid_edge_count > 0 && valid_chain;
}

static bool Internal_CountAndVerifyEdgeChains(
    const ON_SimpleArray<ON_SubDEdgePtr>& sorted_edges,
    unsigned* chain_count = nullptr) {
  if (chain_count != nullptr && chain_count == 0) return false;
  unsigned valid_chain_count = 0U;
  bool valid_chains{false};
  const unsigned edge_count{sorted_edges.UnsignedCount()};
  ON_2udex chaindex{0, edge_count};
  for (chaindex = {0, edge_count}; chaindex.i < edge_count;
       chaindex.i = (chaindex.j > chaindex.i) ? chaindex.j : (chaindex.i + 1)) {
    valid_chains = false;
    if (!Internal_VerifyEdgeChain(sorted_edges, chaindex)) break;
    ++valid_chain_count;
    valid_chains = true;
  }
  if (chain_count != nullptr &&
      (*chain_count != valid_chain_count || chaindex.j != edge_count)) {
    *chain_count = valid_chain_count;
    return false;
  }
  return valid_chain_count > 0 && valid_chains;
}
#endif

//////////////////////////
//
// Better edge sorter
//


static unsigned Internal_MuchImprovedSortEdgesIntoChains(
  const ON__UINT_PTR* unsorted_edges,
  size_t unsorted_edges_count,
  ON_SimpleArray<ON_SubDEdgePtr>& sorted_edges
)
{
  // NOTE: sorted_edges and unsorted_edges should not point to the same array by this point
  sorted_edges.SetCount(0);
  sorted_edges.Reserve(unsorted_edges_count + 128U);

  if (unsorted_edges_count < 1 || nullptr == unsorted_edges)
    return 0;

  const unsigned unsorted_count = (unsigned)unsorted_edges_count;
  unsigned chain_count = 0;

  // Set MarkBits = 0 for every vertex and for every edge attached to a vertex in the edge chain.
  for (unsigned i = 0; i < unsorted_count; ++i)
  {
    const ON_SubDEdge* e = (const ON_SubDEdge*)(ON_SUBD_COMPONENT_POINTER_MASK & unsorted_edges[i]);
    if (nullptr == e)
      continue;
    e->ClearMarkBits();
    if (nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
      continue;
    if (e->m_vertex[0] == e->m_vertex[1])
      continue;
    for (unsigned evi = 0; evi < 2; ++evi)
    {
      const ON_SubDVertex* v = e->m_vertex[evi];
      v->ClearMarkBits();
      for (unsigned short vei = 0; vei < v->m_edge_count; ++vei)
      {
        const ON_SubDEdge* ve = ON_SUBD_EDGE_POINTER(v->m_edges[vei].m_ptr);
        if (nullptr != ve)
          ve->ClearMarkBits();
      }
    }
  }

  // Set e->MarkBits = 1 for every valid edge in the edge chain.
  for (unsigned i = 0; i < unsorted_count; ++i)
  {
    const ON_SubDEdge* e = (const ON_SubDEdge*)(ON_SUBD_COMPONENT_POINTER_MASK & unsorted_edges[i]);
    if (nullptr == e)
      continue;
    if (nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1])
      continue;
    if (e->m_vertex[0] == e->m_vertex[1])
      continue;
    e->SetMarkBits(1);
  }

  // Set v->MarkBits() = number of unsorted_edges[] that have v as a vertex with 3 meaning 3 or more.
  for (unsigned i = 0; i < unsorted_count; ++i)
  {
    const ON_SubDEdge* e = (const ON_SubDEdge*)(ON_SUBD_COMPONENT_POINTER_MASK & unsorted_edges[i]);
    if (nullptr == e)
      continue;
    if (0 == e->MarkBits())
      continue;
    for (unsigned evi = 0; evi < 2; ++evi)
    {
      const ON_SubDVertex* v = e->m_vertex[evi];
      const ON__UINT8 ecount = v->MarkBits();
      if (ecount < 3)
        v->SetMarkBits(ecount + 1);
    }
  }

  // Go through the unsorted edges and use the MarkBits values to quickly build the edge chains.
  ON_SimpleArray<ON_SubDEdgePtr> chain((int)unsorted_edges_count);

  for (unsigned i = 0; i < unsorted_edges_count; ++i)
  {
    const ON_SubDEdge* seed_edge = (const ON_SubDEdge*)(ON_SUBD_COMPONENT_POINTER_MASK & unsorted_edges[i]);
    if (nullptr == seed_edge || 1 != seed_edge->MarkBits())
      continue; // seed_edge is invalid or already assigned to an edge chain

    // this edge pointer direction will be reversed when the for loop evi = 1.
    chain.SetCount(0);
    chain.Append(ON_SubDEdgePtr::Create(seed_edge, 1)); // dir=1 is correct. The direction will be reversed in the for loop below when evi = 1.
    seed_edge->ClearMarkBits(); // seed_edge is now in a chain

    for (unsigned evi = 0; evi < 2; ++evi)
    {
      if (1 == evi)
      {
        ON_SubDEdgeChain::ReverseEdgeChain(chain);
        if (chain[0].RelativeVertex(0) == chain[chain.UnsignedCount() - 1].RelativeVertex(1))
          break; // we found a closed loop
      }

      const ON_SubDVertex* v = chain[chain.UnsignedCount() - 1].RelativeVertex(1);
      if (nullptr == v || 2 != v->MarkBits())
        continue; // edge chain cannot continue through v

      for (const ON_SubDVertex* v1 = nullptr; nullptr != v && 2 == v->MarkBits(); v = v1)
      {
        v->ClearMarkBits(); // clearing v->MarkBits indicates this v has been used.
        v1 = nullptr;
        for (unsigned short vei = 0; vei < v->m_edge_count; ++vei)
        {
          const ON_SubDEdge* ve = ON_SUBD_EDGE_POINTER(v->m_edges[vei].m_ptr);
          if (nullptr == ve)
            continue;
          if (1 != ve->MarkBits())
            continue; // this ve was not in unsorted_edges[] or has already been assigned to a chain.
          if (v == ve->m_vertex[0])
          {
            ve->SetMarkBits(0); // MarkBits() = 0 indicates ve is now in a chain
            chain.Append(ON_SubDEdgePtr::Create(ve, 0));
            v1 = ve->m_vertex[1];
          }
          else if (v == ve->m_vertex[1])
          {
            ve->SetMarkBits(0); // MarkBits() = 0 indicates ve is now in a chain
            chain.Append(ON_SubDEdgePtr::Create(ve, 1));
            v1 = ve->m_vertex[0];
          }
          else
          {
            ON_SUBD_ERROR("Corrupt edge/vertex topology.");
          }
        }
        v = v1;
      }
    }

#ifdef ON_DEBUG
    unsigned temp_chain_edge_count{chain.UnsignedCount()};
    ON_2udex temp_udex{0U, (unsigned)(chain.UnsignedCount() - 1)};
    if (!Internal_VerifyEdgeChain(chain, temp_udex, &temp_chain_edge_count)) {
      temp_chain_edge_count = 0;
    }
    Internal_UnrollChain(chain);
#endif
    sorted_edges.Append(chain.Count(), chain.Array());
    sorted_edges.Append(ON_SubDEdgePtr::Null); // end of chain marker
    ++chain_count;
  }

  // clear all the mark bits that may still be set when the input is corrupt.
  for (size_t i = 0; i < unsorted_edges_count; ++i)
  {
    const ON_SubDEdge* e = (const ON_SubDEdge*)(ON_SUBD_COMPONENT_POINTER_MASK & unsorted_edges[i]);
    if (nullptr == e)
      continue;
    e->ClearMarkBits();
    if (nullptr != e->m_vertex[0])
      e->m_vertex[0]->ClearMarkBits();
    if (nullptr != e->m_vertex[1])
      e->m_vertex[1]->ClearMarkBits();    
  }

#ifdef ON_DEBUG
  Internal_UnrollChain(sorted_edges);
  if (!Internal_CountAndVerifyEdgeChains(sorted_edges, &chain_count)) {
    return chain_count;
  }
#endif
  return chain_count;
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SimpleArray< ON_SubDEdgePtr >& unsorted_edges,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
)
{
  return ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
    unsorted_edges.Array(),
    unsorted_edges.Count(),
    sorted_edges
  );
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SimpleArray< const ON_SubDEdge* >& unsorted_edges,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
)
{
  return ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
    unsorted_edges.Array(),
    unsorted_edges.Count(),
    sorted_edges
  );
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SubDEdge* const* unsorted_edges,
  unsigned unsorted_edge_count,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
)
{
  return ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
    (const ON_SubDEdgePtr*)unsorted_edges,
    unsorted_edge_count,
    sorted_edges
  );
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SimpleArray< ON_SubDComponentPtr >& unsorted_edges,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
)
{
  unsigned int chain_count = 0;
  bool bCopyInput = (const void*)unsorted_edges.Array() == (const void*)sorted_edges.Array();
  const unsigned unsorted_edges_count = unsorted_edges.Count();
  for (unsigned i = 0; i < unsorted_edges_count; ++i)
  {
    ON_SubDComponentPtr cptr = unsorted_edges[i];
    if (cptr.IsEdge() || cptr.IsNull())
      continue;
    bCopyInput = true;
    break;
  }
  if (bCopyInput)
  {
    ON_SimpleArray< ON_SubDEdgePtr > local_unsorted_edges(unsorted_edges_count);
    for (unsigned i = 0; i < unsorted_edges_count; ++i)
    {
      ON_SubDComponentPtr cptr = unsorted_edges[i];
      if (cptr.IsEdge())
        local_unsorted_edges.Append(cptr.EdgePtr());
    }
    chain_count = Internal_MuchImprovedSortEdgesIntoChains(
      (const ON__UINT_PTR*)local_unsorted_edges.Array(),
      unsorted_edges.UnsignedCount(),
      sorted_edges
    );
  }
  else
  {
    chain_count = Internal_MuchImprovedSortEdgesIntoChains(
      (const ON__UINT_PTR*)unsorted_edges.Array(),
      unsorted_edges.UnsignedCount(),
      sorted_edges
    );
  }
  return chain_count;
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SubDEdgePtr* unsorted_edges,
  unsigned unsorted_edge_count,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
)
{
  unsigned int chain_count = 0;
  if (nullptr != unsorted_edges && unsorted_edge_count > 0 && unsorted_edge_count < ON_UNSET_UINT_INDEX)
  {
    if (sorted_edges.Capacity() > 0 && unsorted_edges >= sorted_edges.Array() && unsorted_edges < sorted_edges.Array() + sorted_edges.Capacity())
    {
      ON_SimpleArray< ON_SubDEdgePtr > local_unsorted_edges;
      local_unsorted_edges.Append(unsorted_edge_count, unsorted_edges);
      chain_count = Internal_MuchImprovedSortEdgesIntoChains(
        (const ON__UINT_PTR*)local_unsorted_edges.Array(),
        local_unsorted_edges.UnsignedCount(),
        sorted_edges
      );
    }
    else
    {
      chain_count = Internal_MuchImprovedSortEdgesIntoChains(
        (const ON__UINT_PTR*)unsorted_edges,
        unsorted_edge_count,
        sorted_edges
      );
    }
  }
  return chain_count;
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SubD& subd,
  const ON_SimpleArray< ON_COMPONENT_INDEX >& unsorted_edges,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
)
{
  const unsigned unsorted_count = unsorted_edges.UnsignedCount();
  ON_SimpleArray< const ON_SubDEdge* > local_unsorted_edges(unsorted_count);
  for (unsigned i = 0; i < unsorted_count; ++i)
  {
    const ON_COMPONENT_INDEX ci = unsorted_edges[i];
    if (ON_COMPONENT_INDEX::TYPE::subd_edge != ci.m_type)
      continue;
    if (0 == ci.m_index || -1 == ci.m_index)
      continue;
    const ON_SubDEdge* e = subd.EdgeFromId((unsigned)ci.m_index);
    if (nullptr == e)
      continue;
    local_unsorted_edges.Append(e);
  }

  return Internal_MuchImprovedSortEdgesIntoChains(
    (const ON__UINT_PTR*)local_unsorted_edges.Array(),
    unsorted_edges.UnsignedCount(),
    sorted_edges
  );
}

unsigned ON_SubDEdgeChain::RefineEdgeChains(
  const ON_SimpleArray<ON_SubDEdgePtr>& unconditional_edge_chains,
  bool bOrdinarySmoothChains,
  bool bOrdinaryCreaseChains,
  ON_SimpleArray<ON_SubDEdgePtr>& refined_edge_chains
)
{
  const unsigned unconditional_edge_count = unconditional_edge_chains.UnsignedCount();

  if (unconditional_edge_count > 0 && unconditional_edge_chains.Array() == refined_edge_chains.Array())
  {
    // copy unconditional_edge_chains[] to a local array so we can modify refined_edge_chains[]
    const ON_SimpleArray<ON_SubDEdgePtr> local_unconditional_edge_chains(unconditional_edge_chains);
    refined_edge_chains.SetCount(0); // In this uniquecase we do not append because in[ut array = output array.
    return ON_SubDEdgeChain::RefineEdgeChains(
      local_unconditional_edge_chains,
      bOrdinarySmoothChains,
      bOrdinaryCreaseChains,
      refined_edge_chains
    );
  }

  if (refined_edge_chains.UnsignedCount() > 0 && refined_edge_chains.Last()->IsNotNull())
  {
    // Append a null separator to refined_edge_chains[].
    refined_edge_chains.Append(ON_SubDEdgePtr::Null);
  }

  unsigned int refined_chain_count = 0;
  unsigned i1 = 0U;
  for (unsigned i0 = 0; i0 < unconditional_edge_count; i0 = (i0 < i1) ? i1 : (i0 + 1U))
  {
    const ON_SubDEdgePtr eptr0 = unconditional_edge_chains[i0];
    const ON_SubDEdge* e0 = eptr0.Edge();
    if (nullptr == e0)
      continue;

    refined_edge_chains.Append(eptr0);

    const unsigned short edge_face_count = e0->m_face_count;
    const bool bSmoothChain = e0->IsSmooth();
    const bool bSharpChain = bSmoothChain ? e0->IsSharp() : false;
    ON_SubDEdgeSharpness prev_sharpness = bSharpChain ? eptr0.RelativeSharpness(false) : ON_SubDEdgeSharpness::Smooth;

    for (i1 = i0 + 1; i1 < unconditional_edge_count; ++i1)
    {
      const ON_SubDEdgePtr eptr = unconditional_edge_chains[i1];
      const ON_SubDEdge* e = eptr.Edge();
      if (nullptr == e)
        break;
      if (edge_face_count != e->m_face_count)
        break;
      if (bSmoothChain != e->IsSmooth())
        break;
      if (bSharpChain)
      {
        if (false == e->IsSharp())
          break;
        const ON_SubDEdgeSharpness s = eptr.RelativeSharpness(false);
        if (false == (prev_sharpness.EndSharpness(1) == s.EndSharpness(0)))
          break;
        prev_sharpness = s;
      }

      // Add eptr to current chain
      refined_edge_chains.Append(eptr);

      const ON_SubDVertex* v = eptr.RelativeVertex(1);
      if (nullptr == v)
      {
        ++i1;
        break;
      }

      if (bSmoothChain)
      {
        if (false == bOrdinarySmoothChains)
          continue;
        if (false == v->IsSmooth())
        {
          ++i1;
          break;
        }        
        if (false == bSharpChain && 4 != v->m_edge_count)
        {
          ++i1;
          break;
        }
      }
      else
      {
        if (false == bOrdinaryCreaseChains)
          continue;
        if (false == v->IsCrease())
        {
          ++i1;
          break;
        }
      }
    }

    // finished with this chain.
    ++refined_chain_count;
    refined_edge_chains.Append(ON_SubDEdgePtr::Null);
  }

  return refined_chain_count;
}

unsigned ON_SubDEdgeChain::RefineEdgeChains(
  const ON_SimpleArray<ON_SubDEdgePtr>& unconditional_edge_chains,
  ON__UINT_PTR callback_context,
  bool (*continue_chain_callback_function)(ON__UINT_PTR, ON_SubDEdgePtr, ON_SubDEdgePtr),
  ON_SimpleArray<ON_SubDEdgePtr>& refined_edge_chains
)
{
  if (nullptr == continue_chain_callback_function)
  {
    continue_chain_callback_function = ON_SubDEdgeChain::ContinueChainDefaultCallback;
  }

  const unsigned unconditional_edge_count = unconditional_edge_chains.UnsignedCount();

  if (unconditional_edge_count > 0 && unconditional_edge_chains.Array() == refined_edge_chains.Array())
  {
    // copy unconditional_edge_chains[] to a local array so we can modify refined_edge_chains[]
    const ON_SimpleArray<ON_SubDEdgePtr> local_unconditional_edge_chains(unconditional_edge_chains);
    refined_edge_chains.SetCount(0); // In this uniquecase we do not append because in[ut array = output array.
    return ON_SubDEdgeChain::RefineEdgeChains(
      local_unconditional_edge_chains,
      callback_context,
      continue_chain_callback_function,
      refined_edge_chains
    );
  }

  if (refined_edge_chains.UnsignedCount() > 0 && refined_edge_chains.Last()->IsNotNull())
  {
    // Append a null separator to refined_edge_chains[].
    refined_edge_chains.Append(ON_SubDEdgePtr::Null);
  }

  unsigned int refined_chain_count = 0;
  unsigned i1 = 0U;
  for (unsigned i0 = 0; i0 < unconditional_edge_count; i0 = (i0 < i1) ? i1 : (i0 + 1U))
  {
    const ON_SubDEdgePtr eptr0 = unconditional_edge_chains[i0];
    const ON_SubDEdge* e0 = eptr0.Edge();
    if (nullptr == e0)
      continue;

    refined_edge_chains.Append(eptr0);

    ON_SubDEdgePtr prev_eptr = eptr0;

    for (i1 = i0 + 1; i1 < unconditional_edge_count; ++i1)
    {
      const ON_SubDEdgePtr eptr = unconditional_edge_chains[i1];
      const ON_SubDEdge* e = eptr.Edge();
      if (nullptr == e)
        break;
      if (false == continue_chain_callback_function(callback_context, prev_eptr, eptr))
        break;

      // Add eptr to current chain
      refined_edge_chains.Append(eptr);
      prev_eptr = eptr;
    }

    // finished with this chain.
    ++refined_chain_count;
    refined_edge_chains.Append(ON_SubDEdgePtr::Null);
  }

  return refined_chain_count;
}

class Internal_MergeCrossingEdgeChainsDoubleCallbackContext
{
public:
  Internal_MergeCrossingEdgeChainsDoubleCallbackContext(
    ON__UINT_PTR c,
    bool (*f)(ON__UINT_PTR, ON_SubDEdgePtr, ON_SubDEdgePtr)
  )
    : m_c(c)
    , m_f(f)
  {}

  ~Internal_MergeCrossingEdgeChainsDoubleCallbackContext() = default;

  const ON__UINT_PTR m_c;
  bool (*m_f)(ON__UINT_PTR, ON_SubDEdgePtr, ON_SubDEdgePtr);

private:
  Internal_MergeCrossingEdgeChainsDoubleCallbackContext() = delete;
  Internal_MergeCrossingEdgeChainsDoubleCallbackContext(const Internal_MergeCrossingEdgeChainsDoubleCallbackContext&) = delete;
  Internal_MergeCrossingEdgeChainsDoubleCallbackContext& operator=(const Internal_MergeCrossingEdgeChainsDoubleCallbackContext&) = delete;
};

static bool Internal_MergeCrossingEdgeChainsDoubleCallback(
  ON__UINT_PTR callback_context,
  ON_SubDEdgePtr left_eptr,
  ON_SubDEdgePtr right_eptr
)
{
  const Internal_MergeCrossingEdgeChainsDoubleCallbackContext* double_context = (Internal_MergeCrossingEdgeChainsDoubleCallbackContext*)callback_context;
  if (nullptr == double_context)
    return false;

  // ON_SubDEdgeChain::ContinueChainDefaultCallback(256,...) is the crossing edge check
  return
    ON_SubDEdgeChain::ContinueChainDefaultCallback(256, left_eptr, right_eptr)
    && double_context->m_f(double_context->m_c, left_eptr, right_eptr)
    ;
}

unsigned ON_SubDEdgeChain::MergeCrossingEdgeChains(
  const ON_SimpleArray<ON_SubDEdgePtr>& edge_chains,
  ON__UINT_PTR callback_context,
  bool (*continue_chain_callback_function)(ON__UINT_PTR, ON_SubDEdgePtr, ON_SubDEdgePtr),
  ON_SimpleArray<ON_SubDEdgePtr>& merged_edge_chains
)
{
  const int input_edge_count = edge_chains.Count();
  if (0 == input_edge_count)
  {
    merged_edge_chains.SetCount(0);
    return 0;
  }

  if (edge_chains.Array() == merged_edge_chains.Array())
  {
    const ON_SimpleArray<ON_SubDEdgePtr> local_edge_chains(edge_chains);
    merged_edge_chains.SetCount(0);
    return ON_SubDEdgeChain::MergeCrossingEdgeChains(
      local_edge_chains,
      callback_context,
      continue_chain_callback_function,
      merged_edge_chains
    );
  }

  if (merged_edge_chains.UnsignedCount() > 0 && merged_edge_chains.Last()->IsNotNull())
  {
    // Append a null separator to merged_edge_chains[].
    merged_edge_chains.Append(ON_SubDEdgePtr::Null);
  }

  // ON_SubDEdgeChain::ContinueChainDefaultCallback(256,...) is the crossing edge check
  const Internal_MergeCrossingEdgeChainsDoubleCallbackContext double_context(callback_context, continue_chain_callback_function);
  if (nullptr == double_context.m_f || ON_SubDEdgeChain::ContinueChainDefaultCallback == double_context.m_f)
  {
    callback_context |= 256;
    continue_chain_callback_function = ON_SubDEdgeChain::ContinueChainDefaultCallback;
  }
  else
  {
    callback_context = (ON__UINT_PTR)(&double_context);
    continue_chain_callback_function = Internal_MergeCrossingEdgeChainsDoubleCallback;
  }

  unsigned chain_count = 0;
  ON_SimpleArray<ON_2dex> chaindex(32);
  ON_2dex d(0,0);
  for ( d.i = 0; d.i < input_edge_count; d.i = (d.i < d.j) ? d.j : (d.i+1) )
  {
    if (nullptr == ON_SUBD_EDGE_POINTER(edge_chains[d.i].m_ptr))
      continue;
    for (d.j = d.i + 1; d.j < input_edge_count; ++d.j)
    {
      if (nullptr == ON_SUBD_EDGE_POINTER(edge_chains[d.j].m_ptr))
        break;
    }
    chaindex.Append(d);
  }

  // look for open chains that begin and end at a 4 valent vertex
  merged_edge_chains.Reserve(merged_edge_chains.Count() + edge_chains.Count());
  ON_SimpleArray<ON_3dex> merged_dex(32);
  const unsigned chaindex_count = chaindex.UnsignedCount();
  for (unsigned k = 0; k < chaindex_count; ++k)
  {
    d = chaindex[k];
    if (d.j <= d.i)
      continue;
    chaindex[k] = ON_2dex::Zero;
    ON_SubDEdgePtr eptr[2] = { edge_chains[d.i], edge_chains[d.j - 1] };
    const ON_SubDVertex* v[2] = {
      eptr[0].RelativeVertex(0), 
      eptr[1].RelativeVertex(1)
    };
    if (nullptr == v[0] || nullptr == v[1] || v[0] == v[1])
    {
      // Append this damaged chain as is.
      merged_edge_chains.Append(d.j - d.i, edge_chains.Array() + d.i);

      // mark the end of the chain with a null.
      merged_edge_chains.Append(ON_SubDEdgePtr::Null);
      ++chain_count;
      continue;
    }
    
    merged_dex.SetCount(0);
    merged_dex.Append(ON_3dex(d.i, d.j, 0));
    for (unsigned n = 0; n < 2; ++n)
    {

      // look for another chain that begins or ends at v[n]
      for (unsigned k1 = k + 1; k1 < chaindex_count; ++k1)
      {
        // this 4-valent v[n] test happens every time because the code below can
        // change it.
        if (4 != v[n]->m_edge_count || 4 != v[n]->m_face_count)
          break;

        d = chaindex[k1];
        if (d.j <= d.i)
          continue;

        const ON_SubDEdgePtr eptr1[2] = { edge_chains[d.i], edge_chains[d.j - 1] };
        const ON_SubDVertex* v1[2] = { eptr1[0].RelativeVertex(0), eptr1[1].RelativeVertex(1)};
        if (nullptr == v1[0] || nullptr == v1[1] || v1[0] == v1[1])
          continue;

        const int merged_dex_count0 = merged_dex.Count();
        if (v1[0] == v[n])
        {
          if (0 == n)
          {
            if (continue_chain_callback_function(callback_context, eptr1[0].Reversed(), eptr[0]))
            {
              eptr[0] = eptr1[1].Reversed();
              v[0] = v1[1];
              merged_dex.Insert(0, ON_3dex(d.i, d.j, 1));
            }
          }
          else
          {
            if (continue_chain_callback_function(callback_context, eptr[1], eptr1[0]))
            {
              eptr[1] = eptr1[1];
              v[1] = v1[1];
              merged_dex.Append(ON_3dex(d.i, d.j, 0));
            }
          }
        }
        else if (v1[1] == v[n])
        {
          if (0 == n)
          {
            if (continue_chain_callback_function(callback_context, eptr1[1], eptr[0]))
            {
              eptr[0] = eptr1[0];
              v[0] = v1[0];
              merged_dex.Insert(0, ON_3dex(d.i, d.j, 0));
            }
          }
          else
          {
            if (continue_chain_callback_function(callback_context, eptr[1], eptr1[1].Reversed()))
            {
              eptr[1] = eptr1[0].Reversed();
              v[1] = v1[0];
              merged_dex.Append(ON_3dex(d.i, d.j, 1));
            }
          }
        }

        if (merged_dex_count0 < merged_dex.Count())
        {
          // this input chain will be merged with an earlier one.
          chaindex[k1] = ON_2dex::Zero;
        }
      }
    }

    const unsigned merged_dex_count = merged_dex.UnsignedCount();
    if (merged_dex_count > 0)
    {
      for (unsigned n = 0; n < merged_dex_count; ++n)
      {
        ON_3dex d3 = merged_dex[n];
        if (d3.i >= d3.j)
          continue; // should never happen
        if (0 == d3.k)
        {
          // add this chain to merged_edge_chains[] using its current orientation
          merged_edge_chains.Append(d3.j - d3.i, edge_chains.Array() + d3.i);
        }
        else
        {
          // add this chain to merged_edge_chains[] using its reversed orientation
          for (int i = d3.j - 1; i >= d3.i; --i)
            merged_edge_chains.Append(edge_chains[i].Reversed());
        }
      }
      // mark the end of the chain with a null.
      merged_edge_chains.Append(ON_SubDEdgePtr::Null);
      ++chain_count;
    }
  }

  return chain_count;
}

bool ON_SubDEdgeChain::ContinueChainDefaultCallback(
  ON__UINT_PTR continue_condition,
  ON_SubDEdgePtr left_eptr,
  ON_SubDEdgePtr right_eptr
)
{
  // Perform edge chain topology check
  const ON_SubDEdge* e0 = ON_SUBD_EDGE_POINTER(left_eptr.m_ptr);
  if (nullptr == e0)
    return false;
  const unsigned e0dir = (unsigned)(left_eptr.m_ptr & 1U);
  const ON_SubDVertex* v0[2] = { e0->m_vertex[e0dir], e0->m_vertex[1-e0dir] } ;
  if (nullptr == v0[0] || nullptr == v0[1])
    return false;
  if (v0[0] == v0[1])
    return false;
  const ON_SubDEdge* e1 = ON_SUBD_EDGE_POINTER(right_eptr.m_ptr);
  if (nullptr == e1)
    return false;
  // edges must be distinct
  if (e0 == e1)
    return false;
  // edges must have a common middle vertex
  const unsigned e1dir = (unsigned)(right_eptr.m_ptr & 1);
  const ON_SubDVertex* v1[2] = { e1->m_vertex[e1dir], e1->m_vertex[1 - e1dir] };
  if (v0[1] != v1[0])
    return false;
  if (nullptr == v1[1])
    return false;
  if (v1[0] == v1[1])
    return false;

  // edge chain topology check passed.
  if (0 == continue_condition)
    return true;

  if (0 != (continue_condition & 1))
  {
    // same face count check
    if (e0->m_face_count != e1->m_face_count)
      return false;
  }

  if (0 != (continue_condition & 4))
  {
    // same smooth / crease property
    if (e0->IsSharp() != e1->IsSharp())
      return false;
  }

  if (0 != (continue_condition & 8))
  {
    // equal sharpness at the common vertex check
    if ( false == (e0->Sharpness(true).EndSharpness(1-e0dir) == e1->Sharpness(true).EndSharpness(e1dir)))
      return false;
  }

  while (0 != (continue_condition & (16+32+64+128)))
  {
    // vertex tag filter
    const ON_SubDVertexTag vtag = v0[1]->m_vertex_tag;
    bool bPass = (0 != (continue_condition & 16) && ON_SubDVertexTag::Smooth == vtag);
    if (false == bPass)
      bPass = (0 != (continue_condition & 32) && ON_SubDVertexTag::Crease == vtag);
    if (false == bPass)
      bPass = (0 != (continue_condition & 64) && ON_SubDVertexTag::Dart == vtag);
    if (false == bPass)
      bPass = (0 != (continue_condition & 128) && ON_SubDVertexTag::Corner == vtag);

    if (false == bPass)
      return false;

    break;
  }

  if (0 != (continue_condition & 256) && 4 == v0[1]->m_edge_count && 4 == v0[1]->m_face_count)
  {
    // opposite interior crease check
    const ON_SubDFace* f0[2] = { ON_SUBD_FACE_POINTER(e0->m_face2[0].m_ptr), ON_SUBD_FACE_POINTER(e0->m_face2[1].m_ptr) };
    if (nullptr == f0[0] || nullptr == f0[1])
      return false;
    const ON_SubDFace* f1[2] = { ON_SUBD_FACE_POINTER(e1->m_face2[0].m_ptr), ON_SUBD_FACE_POINTER(e1->m_face2[1].m_ptr) };
    if (nullptr == f1[0] || nullptr == f1[1])
      return false;
    if (f0[0] == f1[0] || f0[0] == f1[1] || f0[1] == f1[0] || f0[1] == f1[1])
      return false; // the edges share a face
  }

  // All checks passed
  return true;
}

bool ON_SubDEdgeChain::IsSingleEdgeChain(
  const ON_SimpleArray<ON_SubDEdgePtr>& edges,
  bool& bIsClosed,
  bool& bIsSorted
)
{
  bIsSorted = false;
  bIsClosed = false;

  const unsigned count = edges.UnsignedCount();
  if (count <= 1U)
  {
    const ON_SubDEdge* e = (1U == count) ? edges[0].Edge() : nullptr;
    if (
      nullptr != e 
      && nullptr != e->m_vertex[0] 
      && nullptr != e->m_vertex[1] 
      && e->m_vertex[0] != e->m_vertex[1]
      )
    {
      // 1 valid edge
      bIsSorted = true;
      return true;
    }
    return false;
  }

  // save MarkBits() values on edges[] components so they can be restored after testing.
  // Internal_MuchImprovedSortEdgesIntoChains() uses MarkBits().
  union
  {
    ON__UINT32 u32;
    ON__UINT8 u8[4];
  } u;
  ON_SimpleArray<ON__UINT32> saved_markbits(count);
  for (unsigned i = 0; i < count; ++i)
  {
    u.u32 = 0;
    const ON_SubDEdge* e = edges[i].Edge();
    if (nullptr != e)
    {
      u.u8[0] = e->MarkBits();
      if (e->m_vertex[0])
        u.u8[1] = e->m_vertex[0]->MarkBits();
      if (e->m_vertex[1])
        u.u8[2] = e->m_vertex[1]->MarkBits();
    }
    saved_markbits.Append(u.u32);
  }

  bool bIsSingleEdgeChain = false;
  for (;;)
  {
    ON_SimpleArray<ON_SubDEdgePtr> sorted_edges;
    const unsigned chain_count = Internal_MuchImprovedSortEdgesIntoChains(
      (const ON__UINT_PTR*)edges.Array(),
      count,
      sorted_edges
    );

    if (1U != chain_count)
      break; // edges[] is not a contiguous set of edges or it self intersects.
    if (count + 1U != sorted_edges.UnsignedCount())
      break; // edges[] contained null edges

    // determine edges[] sorts into a closed edge chain.
    if (count >= 3 && sorted_edges[0].RelativeVertex(0) == sorted_edges[count - 1].RelativeVertex(1))
      bIsClosed = true;

    // Determine edges[] is was already sorted.
    // Note that this test does not detect self intersections and that's
    // why ON_SubDEdgeChain::SortEdgesIntoEdgeChains() is called above.
    const ON_SubDVertex* v0 = edges[0].RelativeVertex(0);
    if (nullptr != v0)
    {
      const ON_SubDVertex* edges_ends[2] = { edges[0].RelativeVertex(0), edges[count - 1].RelativeVertex(1) };
      const ON_SubDVertex* sorted_ends[2] = { sorted_edges[0].RelativeVertex(0), sorted_edges[count - 1].RelativeVertex(1) };
      if (bIsClosed)
      {
        if (edges_ends[0] == edges_ends[1] && sorted_ends[0] == sorted_ends[1])
          bIsSorted = true;
      }
      else
      {
        // sorted_eges[] may be reversed.
        if (edges_ends[0] == sorted_ends[0] && edges_ends[1] == sorted_ends[1])
          bIsSorted = true;
        else if (edges_ends[0] == sorted_ends[1] && edges_ends[1] == sorted_ends[0])
          bIsSorted = true;
      }

      for (unsigned i = 0; bIsSorted && i < count; ++i)
      {
        const ON_SubDVertex* ev[2] = { edges[i].RelativeVertex(0), edges[i].RelativeVertex(1) };
        if (v0 != ev[0] || nullptr == ev[1] || ev[0] == ev[1])
        {
          bIsSorted = false;
          break;
        }
        v0 = ev[1];
      }
    }


    bIsSingleEdgeChain = true;
    break;
  }


  // restore MarkBits() values on edges[] components.
  for (unsigned i = 0; i < count; ++i)
  {
    u.u32 = saved_markbits[i];
    const ON_SubDEdge* e = edges[i].Edge();
    if (nullptr != e)
    {
      e->SetMarkBits(u.u8[0]);
      if (e->m_vertex[0])
        e->m_vertex[0]->SetMarkBits(u.u8[1]);
      if (e->m_vertex[1])
        e->m_vertex[1]->SetMarkBits(u.u8[2]);
    }
  }

  return bIsSingleEdgeChain;
}

bool ON_SubDEdgeChain::IsSingleEdgeChain(
  const ON_SimpleArray<ON_SubDEdgePtr>& edges
)
{
  bool bIsClosed = false;
  bool bIsSorted = false;
  return ON_SubDEdgeChain::IsSingleEdgeChain(edges, bIsClosed, bIsSorted);
}

bool ON_SubDEdgeChain::IsClosed(
  const ON_SimpleArray<ON_SubDEdgePtr>& edges
)
{
  return ON_SubDEdgeChain::IsClosed( edges.Count(), edges.Array());
}

bool ON_SubDEdgeChain::IsClosed(
  size_t edge_count,
  const ON_SubDEdgePtr* edges
)
{
  if (edge_count < 3 || nullptr == edges)
    return false;
  const ON_SubDVertex* v = edges[0].RelativeVertex(0);
  if (nullptr == v)
    return false;
  if (v != edges[edge_count - 1].RelativeVertex(1))
    return false;

  v = edges[0].RelativeVertex(1);
  for (size_t i = 1; i < edge_count; ++i)
  {
    if (nullptr == v)
      return false;
    if (v != edges[i].RelativeVertex(0))
      return false;
    v = edges[i].RelativeVertex(1);
  }

  return true;

}

class ON_SubDEdgePtrLink
{
public:
  ON_SubDEdgePtrLink() = default;
  ~ON_SubDEdgePtrLink() = default;
  ON_SubDEdgePtrLink(const ON_SubDEdgePtrLink&) = default;
  ON_SubDEdgePtrLink& operator=(const ON_SubDEdgePtrLink&) = default;

public:
  static const ON_SubDEdgePtrLink Empty;

public:
  ON_SubDEdgePtr m_ep = ON_SubDEdgePtr::Null;
  unsigned int m_index = 0;
  unsigned int m_nbr_index = 0;

  static int CompareVertex(
    const ON_SubDEdgePtrLink* lhs,
    const ON_SubDEdgePtrLink* rhs
  )
  {
    const ON_SubDVertex* lhs_v = lhs->m_ep.RelativeVertex(0);
    const ON_SubDVertex* rhs_v = rhs->m_ep.RelativeVertex(0);
    if (lhs_v < rhs_v)
      return -1;
    if (lhs_v > rhs_v)
      return 1;
    return 0;
  }

  static int CompareIndex(
    const ON_SubDEdgePtrLink* lhs,
    const ON_SubDEdgePtrLink* rhs
  )
  {
    const unsigned int lhs_i = lhs->m_index;
    const unsigned int rhs_i = rhs->m_index;
    if (lhs_i < rhs_i)
      return -1;
    if (lhs_i > rhs_i)
      return 1;
    return 0;
  }

  static void Resolve3OrMoreEdges(
    const unsigned int unset_nbr1_index,
    unsigned int count,
    const ON_SubDVertex* v,
    ON_SubDEdgePtrLink* links
  );  
};

const ON_SubDEdgePtrLink ON_SubDEdgePtrLink::Empty;

void ON_SubDEdgePtrLink::Resolve3OrMoreEdges(
  const unsigned int unset_nbr1_index,
  unsigned int count,
  const ON_SubDVertex* v,
  ON_SubDEdgePtrLink* links
)
{
  // If the case can't be resolved by Resolve3OrMoreEdges(), 
  // then the vertex will not appear in the middle of a chain.

  if (count < 3 || nullptr == v || count != (unsigned int)v->m_edge_count)
    return;

  switch (count)
  {
  case 3:
    if (false == v->IsCrease() && false == v->IsDart())
      return;
    break;

  case 4:
    if (false == v->IsCrease() && false == v->IsSmooth())
      return;
    break;

  default:
    if (false == v->IsCrease())
      return;
    break;
  }

  const ON_SubDEdge* link_edges[4] = {};
  const ON_SubDEdge* vertex_edges[4] = {};
  unsigned int crease_edge_count = 0;
  unsigned int smooth_edge_count = 0;
  unsigned int smooth_edge_link_index[4] = {};
  unsigned int crease_edge_link_index[4] = {};
  for (unsigned int j = 0; j < count; j++)
  {
    const ON_SubDEdge* e = links[j].m_ep.Edge();
    if (nullptr == e)
      return;
    const ON_SubDEdge* ve = v->Edge(j);
    if (nullptr == ve)
      return;
    if (j < 4)
    {
      link_edges[j] = e;
      vertex_edges[j] = ve;
    }

    if (e->IsSmooth() && 2 == e->m_face_count)
    {
      if ( smooth_edge_count < 4)
        smooth_edge_link_index[smooth_edge_count] = j;
      ++smooth_edge_count;
    }
    else if (e->IsCrease())
    {
      if (crease_edge_count < 4)
        crease_edge_link_index[crease_edge_count] = j;
      ++crease_edge_count;
    }
    else
      return;
  }

  if ( 2 == crease_edge_count && v->IsCrease() )
  {
    // Link the two creased edges.
    // The vertex will be interior in a chain and the edges
    // will be next to each other.
    links[crease_edge_link_index[0]].m_nbr_index = links[crease_edge_link_index[1]].m_index;
    links[crease_edge_link_index[1]].m_nbr_index = links[crease_edge_link_index[0]].m_index;
    if (1 == smooth_edge_count)
    {
      // this edge will be at the end of a chain.
      links[smooth_edge_link_index[0]].m_nbr_index = unset_nbr1_index;
    }
  }

  if (2 == smooth_edge_count)
  {
    // Link the two smooth edges.
    // The vertex will be interior in a chain and the edges
    // will be next to each other.
    links[smooth_edge_link_index[0]].m_nbr_index = links[smooth_edge_link_index[1]].m_index;
    links[smooth_edge_link_index[1]].m_nbr_index = links[smooth_edge_link_index[0]].m_index;
    if (1 == crease_edge_count)
    {
      // this edge will be at the end of a chain
      links[crease_edge_link_index[0]].m_nbr_index = unset_nbr1_index;
    }
   }

  if (
    4 != count
    || 4 != smooth_edge_count
    || 0 != crease_edge_count
    || 4 != v->m_face_count
    || 4 != v->m_edge_count
    || false == v->IsSmooth()
    )
    return;

  // make sure vertex_edges[] and link_edges[] are the same list.
  unsigned int match_count = 0;
  for (unsigned int j = 0; j == match_count && j < count; j++)
  {
    for (unsigned int k = 0; k < count; k++)
    {
      if (vertex_edges[k] == link_edges[j])
      {
        vertex_edges[k] = nullptr;
        match_count++;
        break;
      }
    }
  }
  if (match_count != count)
    return;
  
  // vertex has 4 faces and 4 smooth edges. Link opposite edges.
  const ON_SubDFace* edge_faces[4][2];
  for (unsigned int j = 0; j < 4; j++)
  {
    edge_faces[j][0] = link_edges[j]->Face(0);
    edge_faces[j][1] = link_edges[j]->Face(1);
    if (nullptr == edge_faces[j][0] || nullptr == edge_faces[j][1])
      return;
  }
  ON_2udex pairs[2];
  unsigned int pair_count = 0;
  ON_2udex pair;
  for (pair.i = 0; pair.i < 4; ++pair.i) for (pair.j = pair.i+1; pair.j < 4; ++pair.j)
  {
    if (
      edge_faces[pair.i][0] != edge_faces[pair.j][0]
      && edge_faces[pair.i][0] != edge_faces[pair.j][1]
      && edge_faces[pair.i][1] != edge_faces[pair.j][0]
      && edge_faces[pair.i][1] != edge_faces[pair.j][1]
      )
    {
      // the associated edges share no faces.
      if ( pair_count < 2)
        pairs[pair_count] = pair;
      if (++pair_count > 2)
        break;
    }
  }
  if (2 == pair_count)
  {
    links[pairs[0].i].m_nbr_index = links[pairs[0].j].m_index;
    links[pairs[0].j].m_nbr_index = links[pairs[0].i].m_index;
    links[pairs[1].i].m_nbr_index = links[pairs[1].j].m_index;
    links[pairs[1].j].m_nbr_index = links[pairs[1].i].m_index;
  }

  return;
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SubD& subd,
  const ON_SimpleArray< ON_COMPONENT_INDEX >& unsorted_edges,
  unsigned int minimum_chain_length,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
)
{
  const unsigned count = unsorted_edges.UnsignedCount();
  ON_SimpleArray< const ON_SubDEdge* > a(count);
  for (unsigned i = 0; i < count; ++i)
  {
    const ON_SubDEdge* e = subd.EdgeFromComponentIndex(unsorted_edges[i]);
    if (nullptr != e)
      a.Append(e);
  }
  return SortEdgesIntoEdgeChains(a, minimum_chain_length, sorted_edges);
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SimpleArray< ON_SubDComponentPtr >& unsorted_edges,
  unsigned int minimum_chain_length,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
)
{
  const unsigned count = unsorted_edges.UnsignedCount();
  ON_SimpleArray< const ON_SubDEdge* > a(count);
  for (unsigned i = 0; i < count; ++i)
    a.Append(unsorted_edges[i].Edge());
  return ON_SubDEdgeChain::SortEdgesIntoEdgeChains(a, minimum_chain_length, sorted_edges);
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SimpleArray< const ON_SubDEdge* >& unsorted_edges,
  unsigned int minimum_chain_length,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
)
{
  // Dale Lear - June 20 2023 https://mcneel.myjetbrains.com/youtrack/issue/RH-75228
  // To avoid breaking the the 7.x SDK 
  // Call Mikko's modified version. https://mcneel.myjetbrains.com/youtrack/issue/RH-66258
  // It is extremely unlikely anybody outside of core McNeel devs ever called the original function.
  const bool bIgnoreCorners = false;
  return ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
    unsorted_edges,
    minimum_chain_length,
    sorted_edges,
    bIgnoreCorners
  );
}


unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SimpleArray< const ON_SubDEdge* >& unsorted_edges,
  unsigned int minimum_chain_length,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges,
  const bool bIgnoreCorners
)
{
  const unsigned int unsorted_edge_count = unsorted_edges.Count();
  ON_SimpleArray< ON_SubDEdgePtr > unsorted_eptrs(unsorted_edge_count);
  for (unsigned i = 0; i < unsorted_edge_count; ++i)
  {
    const ON_SubDEdge* e = unsorted_edges[i];
    if (nullptr == e || nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1] || e->m_vertex[0] == e->m_vertex[1])
      continue;
    ON_SubDEdgePtr eptr = ON_SubDEdgePtr::Create(e, 0);
    if (1 == e->m_face_count && 0 == ON_SUBD_FACE_DIRECTION(e->m_face2[0].m_ptr))
      eptr = eptr.Reversed();
    unsorted_eptrs.Append(eptr);
  }
  return ON_SubDEdgeChain::SortEdgesIntoEdgeChains(unsorted_eptrs, minimum_chain_length, sorted_edges, bIgnoreCorners);
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SimpleArray< ON_SubDEdgePtr >& unsorted_edges,
  unsigned int minimum_chain_length,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
)
{
  // Dale Lear - June 20 2023 https://mcneel.myjetbrains.com/youtrack/issue/RH-75228
  // To avoid breaking the the 7.x SDK 
  // Call Mikko's modified version. https://mcneel.myjetbrains.com/youtrack/issue/RH-66258
  // It is extremely unlikely anybody outside of core McNeel devs ever called the original function.
  const bool bIgnoreCorners = false;
  return ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
    unsorted_edges,
    minimum_chain_length,
    sorted_edges,
    bIgnoreCorners
  );
}

unsigned int ON_SubDEdgeChain::SortEdgesIntoEdgeChains(
  const ON_SimpleArray< ON_SubDEdgePtr >& unsorted_edges,
  unsigned int minimum_chain_length,
  ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges,
  const bool bIgnoreCorners
)
{
  // NOTE:
  //  unsorted_edges[] and sorted_edges[] may reference the same array.
  ////const ON_SubDEdge* ee[2] = {};
  ////const ON_SubDVertex* vv[2] = {};

  const unsigned int unsorted_edge_count = unsorted_edges.Count();
  if (unsorted_edge_count <= 0)
  {
    sorted_edges.SetCount(0);
    return 0;
  }

  ON_SimpleArray< ON_SubDEdgePtrLink > links(2*unsorted_edge_count);
  const unsigned int unset_nbr1_index = 0xFFFFFFFEU;
  const unsigned int unset_nbrX_index = unset_nbr1_index+1;
  ON_SubDEdgePtrLink epl;
  epl.m_nbr_index = unset_nbrX_index;
  for (unsigned int i = 0; i < unsorted_edge_count; i++)
  {
    ON_SubDEdgePtr ep = unsorted_edges[i];
    const ON_SubDEdge* e = ep.Edge();
    if (nullptr == e || nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1] || e->m_vertex[0] == e->m_vertex[1])
      continue;

    // unsorted_edges[i] has 2 links with m_index = 2*i and m_index = 2*+1.

    // links with even m_index have opposite orientation as unsorted_edges[].
    // links[2*i].m_ep.RelativeVertex(0) = unsorted_edges[i].RelativeVertex(1)
    epl.m_ep = ep.Reversed();
    links.Append(epl);
    ++epl.m_index;
    ////ee[0] = epl.m_ep.Edge();
    ////vv[1] = epl.m_ep.RelativeVertex(0);

    // links with odd m_index have same orientation as unsorted_edges[].
    // links[2*i+1].m_ep.RelativeVertex(0) = unsorted_edges[i].RelativeVertex(0)
    epl.m_ep = ep;
    links.Append(epl);
    ++epl.m_index;
    ////ee[1] = epl.m_ep.Edge();
    ////vv[0] = epl.m_ep.RelativeVertex(0);
    ////if (e != ee[0] || e != ee[1] || vv[0] == vv[1])
    ////  return false;
  }

  // NOTE:
  // unsorted_edges[] and sorted_edges[] may reference the same array.
  // At this point, I'm finished with unsorted_edges[] so it's ok to 
  // modify sorted_edges[] here.
  sorted_edges.SetCount(0);
  sorted_edges.Reserve(unsorted_edge_count);

  // sort links by ON_SubDEdgePtr.RelativeVertex(0) and set m_nbr_index
  links.QuickSort(ON_SubDEdgePtrLink::CompareVertex);
  // link_count = even number
  const unsigned int link_count = links.UnsignedCount();
  unsigned int i1 = link_count;
  for (unsigned int i0 = 0; i0 < link_count; i0 = i1)
  {
    ON_SubDEdgePtrLink& epl0 = links[i0];
    const ON_SubDVertex* v = epl0.m_ep.RelativeVertex(0);
    for (i1 = i0 + 1; i1 < link_count; ++i1)
    {
      if (0 != ON_SubDEdgePtrLink::CompareVertex(&epl0, &links[i1]))
        break;
    }
    if (nullptr == v)
    {
      ON_SUBD_ERROR("Bug in code that creates the links[] array.");
      continue;
    }
    if (!bIgnoreCorners)
    {
      if (v->IsCorner())
      {
        // These edges will be at the ends of chains.
        while (i0 < i1)
          links[i0++].m_nbr_index = unset_nbr1_index;
        continue;
      }
    }

    if (i0 + 1 == i1)
    {
      // The vertex is referenced by exactly 1 edge in unsorted_edges[]
      // This edge will appear in sorted_edges[] at the start or end of a chain.
      epl0.m_nbr_index = unset_nbr1_index;
      continue; 
    }
    if (i0 + 2 == i1)
    {
      // This vertex is referenced by exactly 2 edges in  unsorted_edges[].
      // The vertex will be in the interior of a chain and the edges will 
      // appear in sorted_edges[] next to each other in the same chain.
      ON_SubDEdgePtrLink& epl1 = links[i0 + 1];
      epl0.m_nbr_index = epl1.m_index;
      epl1.m_nbr_index = epl0.m_index;
      continue;
    }

    // The vertex referenced by 3 or more edges in unsorted_edges[].
    // If the case cannot be resolved by Resolve3OrMoreEdges(), 
    // then this vertex will not be in the interior of a chain.
    ON_SubDEdgePtrLink::Resolve3OrMoreEdges(
      unset_nbr1_index,
      i1 - i0,
      v,
      links.Array() + i0
    );
  }

  // Sort links[] by m_index value to restore links[] to its original order.
  links.QuickSort(ON_SubDEdgePtrLink::CompareIndex);
  ON_SubDEdgePtrLink* links_array = links.Array();

  unsigned chain_count = 0;
  ON_SimpleArray<ON_SubDEdgePtr> chain(unsorted_edge_count);

  for (unsigned int i = 0; i < link_count; ++i)
  {
    // epl0 and epl1 are the links for edges[i/2]
    const ON_SubDEdgePtrLink epl0 = links_array[i];
    links_array[i].m_ep = ON_SubDEdgePtr::Null;
    const ON_SubDEdgePtrLink epl1 = links_array[++i];
    links_array[i].m_ep = ON_SubDEdgePtr::Null;

    if (nullptr == epl0.m_ep.Edge())
      continue; // this edge has already been inserted in sorted_edges[].

    chain.SetCount(0);

    // Add edges that come "before" edges[i/2] to chain[]
    epl = epl1;
    for (;;)
    {
      if (epl.m_nbr_index >= unset_nbr1_index)
        break;
      unsigned int j = epl.m_nbr_index;
      unsigned int j1 = (0 == (j % 2)) ? (j + 1) : (j - 1);
      // epl = "previous" link
      epl = links_array[j1];
      links_array[j].m_ep = ON_SubDEdgePtr::Null;
      links_array[j1].m_ep = ON_SubDEdgePtr::Null;
      if (nullptr == epl.m_ep.Edge())
        break;
      ////ee[0] = epl.m_ep.Edge();
      ////vv[0] = epl.m_ep.RelativeVertex(0);
      ////vv[1] = epl.m_ep.RelativeVertex(1);
      ////if (vv[0] == vv[1] || nullptr == ee[0])
      ////  return false;
      chain.Append(epl.m_ep);
    }

    const bool bClosedChain =
        chain.UnsignedCount() > 0 && (epl.m_index == epl1.m_index);
    const bool bFirstEdgeIsReversed = !bClosedChain &&
                                      unset_nbr1_index <= epl.m_nbr_index &&
                                      (0 == (epl.m_index % 2));
    bool bLastEdgeIsReversed{false};
    if (false == bClosedChain)
    {
      chain.Reverse();
    }

    ////ee[0] = epl1.m_ep.Edge();
    ////vv[0] = epl1.m_ep.RelativeVertex(0);
    ////vv[1] = epl1.m_ep.RelativeVertex(1);
    ////if (vv[0] == vv[1] || nullptr == ee[0])
    ////  return false;
    chain.Append(epl1.m_ep); // matches input edge orientation

    if (bClosedChain)
    {
      // put edges[i/2] at the start of the closed chain.
      chain.Reverse();
    }
    else
    {
      // Add edges that come "after" edges[i/2] to chain[]
      epl = epl0;
      for (;;)
      {
        if (epl.m_nbr_index >= unset_nbr1_index)
          break;
        unsigned int j = epl.m_nbr_index;
        unsigned int j1 = (0 == (j % 2)) ? (j + 1) : (j - 1);
        // epl = "next" link
        epl = links_array[j1];
        links_array[j].m_ep = ON_SubDEdgePtr::Null;
        links_array[j1].m_ep = ON_SubDEdgePtr::Null;
        if (nullptr == epl.m_ep.Edge())
          break;
        ////ee[0] = epl.m_ep.Edge();
        ////vv[0] = epl.m_ep.RelativeVertex(1);
        ////vv[1] = epl.m_ep.RelativeVertex(0);
        ////if (vv[0] == vv[1] || nullptr == ee[0])
        ////  return false;
        chain.Append(epl.m_ep.Reversed());
      }

      // No need to update bClosedChain here: if it was closed, then the circle
      // was found with the edges "before" edges[i/2]

      // First and last edge are reversed: reverse chain direction to keep first
      // edge direction the same as in unsorted_edges
      bLastEdgeIsReversed = epl.m_index % 2 == 0;
      if (bFirstEdgeIsReversed && bLastEdgeIsReversed) {
        ReverseEdgeChain(chain);
      }
    }

    const unsigned int chain_edge_count = chain.UnsignedCount();
    if (chain_edge_count > 0)
    {
      for (;;)
      {
        if (chain_edge_count < 3)
          break;
        const ON_SubDVertex* c0 = chain[0].RelativeVertex(0);
        if (nullptr == c0)
          break;
        if (c0->IsCorner())
          break;
        const ON_SubDVertex* c1 = chain[chain_edge_count-1].RelativeVertex(1);
        if (c0 != c1)
          break;
        const ON_SubDEdge* e0 = chain[0].Edge();
        if (nullptr == e0)
          break;
        const ON_SubDEdge* e1 = chain[chain_edge_count-1].Edge();
        if (nullptr == e1)
          break;
        const bool bSmooth = e0->IsSmooth();
        if (bSmooth != e1->IsSmooth())
          break;
        if (bSmooth && c0->IsCrease())
          break;
        // Check for an embedded crease vertex.
        for (unsigned int k = 1; k < chain_edge_count; ++k)
        {
          const ON_SubDVertex* v = chain[k].RelativeVertex(0);
          if (nullptr == v)
            break;
          const ON_SubDEdge* e = chain[k].Edge();
          if (nullptr == e)
            break;
          if (
            bSmooth != e->IsSmooth()
            || (bSmooth && v->IsCreaseOrCorner())
            )
          {
            // shift chain[] so it begins at chain[k];
            ON_SimpleArray<ON_SubDEdgePtr> tail;
            tail.Append(k, chain.Array());
            for (unsigned n = k; n < chain_edge_count; ++n)
              chain[n - k] = chain[n];
            chain.SetCount(chain_edge_count - k);
            chain.Append(tail.Count(), tail.Array());
            break;
          }
        }
        break;
      }
#ifdef ON_DEBUG
      unsigned temp_chain_edge_count{chain_edge_count};
      ON_2udex temp_udex{0U, (unsigned)(chain_edge_count - 1)};
      if (!Internal_VerifyEdgeChain(chain, temp_udex, &temp_chain_edge_count)) {
        temp_chain_edge_count = 0;
      }
      Internal_UnrollChain(chain);
#endif
      if (chain.UnsignedCount() >= minimum_chain_length) {
        const ON_SubDVertex* c0{chain[0].RelativeVertex(0)};
        const ON_SubDVertex* s1{sorted_edges.Last() == nullptr
                                    ? nullptr
                                    : sorted_edges.Last()->RelativeVertex(1)};
        if (c0 != nullptr && c0 == s1) {
          // If the first vertex of the chain is a corner, or a vertex with more
          // than 2 edges referencing it, we might have artificially split the
          // chain at that vertex and the last vertex of the previous chain is
          // the same as ours. Try a few tricks to put a gap between these two
          // vertices.
          const ON_SubDVertex* c1{
              chain[chain_edge_count - 1].RelativeVertex(1)};
          const ON_SubDVertex* s0{
              sorted_edges.First() == nullptr
                  ? nullptr
                  : sorted_edges.First()->RelativeVertex(0)};
          // By order of importance, try to:
          //   - Keep the orientation of the first edge the same as in unsorted_edges
          //   - Not use ReverseEdgeChain()
          //   - Append rather than Prepend to sorted_edges
          if (c1 != s0) {
            ++chain_count;
            sorted_edges.Prepend(chain.Count(), chain.Array());
          } else if (c1 != s1 && !bClosedChain &&
                     ((bFirstEdgeIsReversed && !bLastEdgeIsReversed) ||
                      (!bFirstEdgeIsReversed && bLastEdgeIsReversed))) {
            ReverseEdgeChain(chain);
            ++chain_count;
            sorted_edges.Append(chain.Count(), chain.Array());
          } else if (c0 != s0 && !bClosedChain &&
                     ((bFirstEdgeIsReversed && !bLastEdgeIsReversed) ||
                      (!bFirstEdgeIsReversed && bLastEdgeIsReversed))) {
            ReverseEdgeChain(chain);
            ++chain_count;
            sorted_edges.Prepend(chain.Count(), chain.Array());
          } else if (c1 != s1 && !bClosedChain) {
            ReverseEdgeChain(chain);
            ++chain_count;
            sorted_edges.Append(chain.Count(), chain.Array());
          } else if (c0 != s0 && !bClosedChain) {
            ReverseEdgeChain(chain);
            ++chain_count;
            sorted_edges.Prepend(chain.Count(), chain.Array());
          } else {
            // We tried, but nothing works easily enough: append the chain as
            // usual, this means the two chains are merged and chain_count does
            // not increase.
            sorted_edges.Append(chain.Count(), chain.Array());
          }
        } else {
          ++chain_count;
          sorted_edges.Append(chain.Count(), chain.Array());
        }
      }
    }

    if ( link_count == 2*sorted_edges.UnsignedCount() )
      break; // we've used all the links - no need to "skip over the rest".
  }
#ifdef ON_DEBUG
  Internal_UnrollChain(sorted_edges);
  if (!Internal_CountAndVerifyEdgeChains(sorted_edges, &chain_count)) {
    return chain_count;
  }
#endif
  return chain_count;
}

const ON_SHA1_Hash ON_SubDEdgeChain::Hash() const
{
  ON_SHA1 sha1;
  const unsigned edge_count = this->EdgeCount();
  for (unsigned i = 0; i < edge_count; ++i)
  {
    const ON_SubDEdgePtr eptr = EdgePtr(i);
    sha1.AccumulateInteger32(eptr.EdgeId());
    sha1.AccumulateInteger32(eptr.RelativeVertexId(0));
    sha1.AccumulateInteger32(eptr.RelativeVertexId(1));
  }
  return sha1.Hash();
}

unsigned int ON_SubDEdgeChain::OrientEdgesIntoEdgeChains(
  const ON_SubD& subd,
  const ON_SimpleArray< ON_COMPONENT_INDEX >& edges,
  ON_SimpleArray< ON_SubDEdgePtr >& edge_chain
)
{
  const unsigned count = edges.UnsignedCount();
  ON_SimpleArray< const ON_SubDEdge* > a(count);
  for (unsigned i = 0; i < count; ++i)
    a.Append(subd.EdgeFromComponentIndex(edges[i]));
  return ON_SubDEdgeChain::OrientEdgesIntoEdgeChains(a, edge_chain);
}

unsigned int ON_SubDEdgeChain::OrientEdgesIntoEdgeChains(
  const ON_SimpleArray< ON_SubDComponentPtr >& edges,
  ON_SimpleArray< ON_SubDEdgePtr >& edge_chain
)
{
  const unsigned count = edges.UnsignedCount();
  ON_SimpleArray< const ON_SubDEdge* > a(count);
  for (unsigned i = 0; i < count; ++i)
    a.Append(edges[i].Edge());
  return ON_SubDEdgeChain::OrientEdgesIntoEdgeChains(a, edge_chain);
}

unsigned int ON_SubDEdgeChain::OrientEdgesIntoEdgeChains(
  const ON_SimpleArray< const ON_SubDEdge* >& edges,
  ON_SimpleArray< ON_SubDEdgePtr >& edge_chains
)
{
  const unsigned count = edges.UnsignedCount();
  edge_chains.SetCount(0);
  edge_chains.Reserve(count);
  unsigned int chain_count = 0;
  unsigned chain_length = 0;
  ON_SubDEdgePtr* prev_eptr = nullptr;
  for (unsigned i = 0; i < count; ++i)
  {
    const ON_SubDEdge* e = edges[i];
    if (nullptr == e || nullptr == e->m_vertex[0] || nullptr == e->m_vertex[1] || e->m_vertex[0] == e->m_vertex[1])
      continue;
    ON_SubDEdgePtr& eptr = edge_chains.AppendNew();
    eptr = ON_SubDEdgePtr::Create(e);
    if (nullptr != prev_eptr && prev_eptr->RelativeVertex(1) != eptr.RelativeVertex(0) )
    {
      const ON_SubDVertex* prev_v[2] = { prev_eptr->RelativeVertex(0), prev_eptr->RelativeVertex(1) };
      const ON_SubDVertex* v[2] = { eptr.RelativeVertex(0), eptr.RelativeVertex(1) };
      if (prev_v[1] == v[1])
        eptr = eptr.Reversed();
      else if (1 == chain_length)
      {
        if (prev_v[0] == v[0])
          *prev_eptr = prev_eptr->Reversed();
        else if (prev_v[0] == v[1])
        {
          *prev_eptr = prev_eptr->Reversed();
          eptr = eptr.Reversed();
        }
        else
          prev_eptr = nullptr;
      }
      else
        prev_eptr = nullptr;
    }

    if (nullptr == prev_eptr)
    {
      chain_count = 1;
      chain_length = 0;
    }
    prev_eptr = &eptr;
    ++chain_length;
  }
  return chain_count;
}



ON_SubDComponentList::ON_SubDComponentList(const ON_SubDComponentList& src)
  : m_subd_runtime_serial_number(src.m_subd_runtime_serial_number)
  , m_subd_geometry_content_serial_number(src.m_subd_geometry_content_serial_number)
  , m_subd_render_content_serial_number(src.m_subd_render_content_serial_number)
  , m_subd_vertex_count(src.m_subd_vertex_count)
  , m_subd_edge_count(src.m_subd_edge_count)
  , m_subd_face_count(src.m_subd_face_count)
  , m_component_list(src.m_component_list)
{
  m_subd.ShareDimple(src.m_subd);
}

ON_SubDComponentList& ON_SubDComponentList::operator=(const ON_SubDComponentList& src)
{
  if (this != &src)
  {
    m_subd_runtime_serial_number = src.m_subd_runtime_serial_number;
    m_subd_geometry_content_serial_number = src.m_subd_geometry_content_serial_number;
    m_subd_render_content_serial_number = src.m_subd_render_content_serial_number;
    m_subd_vertex_count = src.m_subd_vertex_count;
    m_subd_edge_count = src.m_subd_edge_count;
    m_subd_face_count = src.m_subd_face_count;
    m_component_list = src.m_component_list;
    m_subd.ShareDimple(src.m_subd);
  }
  return *this;
}

ON__UINT64 ON_SubDComponentList::SubDRuntimeSerialNumber() const
{
  return m_subd_runtime_serial_number;
}

ON__UINT64 ON_SubDComponentList::SubDGeometryContentSerialNumber() const
{
  return m_subd_geometry_content_serial_number;
}

ON__UINT64 ON_SubDComponentList::SubDRenderContentSerialNumber() const
{
  return m_subd_render_content_serial_number;
}

unsigned int ON_SubDComponentList::Count() const
{
  return m_component_list.UnsignedCount();
}

const ON_SubDComponentPtr ON_SubDComponentList::operator[](int i) const
{
  return i >= 0 && i < m_component_list.Count() ? m_component_list[i] : ON_SubDComponentPtr::Null;
}

const ON_SubDComponentPtr ON_SubDComponentList::operator[](unsigned int i) const
{
  return i < m_component_list.UnsignedCount() ? m_component_list[i] : ON_SubDComponentPtr::Null;
}

const ON_SubDComponentPtr ON_SubDComponentList::operator[](ON__INT64 i) const
{
  return i >= 0 && i < ((ON__INT64)m_component_list.Count()) ? m_component_list[i] : ON_SubDComponentPtr::Null;
}

const ON_SubDComponentPtr ON_SubDComponentList::operator[](ON__UINT64 i) const
{
  return i < ((ON__UINT64)m_component_list.UnsignedCount()) ? m_component_list[i] : ON_SubDComponentPtr::Null;
}

#if defined(ON_RUNTIME_APPLE)
const ON_SubDComponentPtr ON_SubDComponentList::operator[](size_t i) const
{
  return i >= 0 && i < m_component_list.Count() ? m_component_list[i] : ON_SubDComponentPtr::Null;
}
#endif

const ON_SimpleArray< ON_SubDComponentPtr >& ON_SubDComponentList::ComponentList() const
{
  return this->m_component_list;
}

const ON_SubD& ON_SubDComponentList::SubD() const
{
  return m_subd;
}

void ON_SubDComponentList::UpdateContentSerialNumbers()
{
  m_subd_geometry_content_serial_number = m_subd.GeometryContentSerialNumber();
  m_subd_render_content_serial_number = m_subd.RenderContentSerialNumber();
}

unsigned int ON_SubDComponentList::UpdateSubDForExperts(const ON_SubD & subd, bool bUpdateDeletedComponents)
{
  const unsigned count0 = Count();
  if (subd.RuntimeSerialNumber() == m_subd.RuntimeSerialNumber())
    return count0; // the components in this list are in subd.

  // Use the component ids to update the list to reference components in subd.
  unsigned count1 = 0;
  for (unsigned i = 0; i < count0; ++i)
  {
    ON_SubDComponentPtr cptr0 = m_component_list[i];
    const ON_SubDComponentBase* c0 = cptr0.ComponentBase();
    if (nullptr == c0)
      continue;
    if (false == bUpdateDeletedComponents && false == c0->IsActive())
      continue;
    ON_COMPONENT_INDEX ci = cptr0.ComponentIndex();
    if (0 == ci.m_index)
      continue;
    ON_SubDComponentPtr cptr1 = subd.ComponentPtrFromComponentIndex(ci);
    if (cptr1.IsNull())
      continue;
    if (0 != cptr0.ComponentDirection())
      cptr1.SetComponentDirection();
    m_component_list[count1++] = cptr1;
  }
  m_component_list.SetCount(count1);
  m_subd.ShareDimple(subd);
  m_subd_runtime_serial_number = m_subd.RuntimeSerialNumber();
  m_subd_geometry_content_serial_number = m_subd.GeometryContentSerialNumber();
  m_subd_render_content_serial_number = m_subd.RenderContentSerialNumber();
  return Count();
}

unsigned ON_SubDComponentList::CreateFromComponentList(const ON_SubD& subd, const ON_SimpleArray<ON_COMPONENT_INDEX>& component_list)
{
  ON_SubDComponentMarksClearAndRestore saved_marks(subd);
  const unsigned count = component_list.UnsignedCount();
  unsigned marked_count = 0;
  for (unsigned i = 0; i < count; ++i)
  {
    const ON_COMPONENT_INDEX ci = component_list[i];
    if (ON_COMPONENT_INDEX::TYPE::subd_vertex != ci.m_type)
      continue;
    const unsigned vertex_id = (unsigned)ci.m_index;
    const ON_SubDVertex* v = subd.VertexFromId(vertex_id);
    if (nullptr == v)
      continue;
    if (v->m_status.RuntimeMark())
      continue;
    v->m_status.SetRuntimeMark();
    ++marked_count;
  }
  return Internal_Create(subd, true, true, true, true, marked_count);
}

unsigned ON_SubDComponentList::CreateFromComponentList(const ON_SubD& subd, const ON_SimpleArray<ON_SubDComponentPtr>& component_list)
{
  ON_SubDComponentMarksClearAndRestore saved_marks(subd);
  const unsigned count = component_list.UnsignedCount();
  unsigned marked_count = 0;
  for (unsigned i = 0; i < count; ++i)
  {
    const ON_SubDComponentBase* c = component_list[i].ComponentBase();
    if (nullptr == c)
      continue;
    if (c->m_status.RuntimeMark())
      continue;
    c->m_status.SetRuntimeMark();
    ++marked_count;
  }
  return Internal_Create(subd, true, true, true, true, marked_count);
}

unsigned ON_SubDComponentList::CreateFromVertexIdList(const ON_SubD& subd, const ON_SimpleArray<unsigned>& vertex_id_list)
{
  ON_SubDComponentMarksClearAndRestore saved_marks(subd);
  const unsigned count = vertex_id_list.UnsignedCount();
  unsigned marked_count = 0;
  for (unsigned i = 0; i < count; ++i)
  {
    const unsigned vertex_id = vertex_id_list[i];
    if (vertex_id <= 0 || vertex_id >= ON_UNSET_UINT_INDEX)
      continue;
    const ON_SubDVertex* v = subd.VertexFromId(vertex_id);
    if (nullptr == v)
      continue;
    if (v->m_status.RuntimeMark())
      continue;
    v->m_status.SetRuntimeMark();
    ++marked_count;
  }
  return Internal_Create(subd, true, false, false, true, marked_count);
}


unsigned ON_SubDComponentList::CreateFromVertexList(const ON_SubD& subd, const ON_SimpleArray<ON_SubDVertexPtr>& vertex_list)
{
  ON_SubDComponentMarksClearAndRestore saved_marks(subd);
  const unsigned count = vertex_list.UnsignedCount();
  unsigned marked_count = 0;
  for (unsigned i = 0; i < count; ++i)
  {
    const ON_SubDVertex* v = vertex_list[i].Vertex();
    if (nullptr == v)
      continue;
    if (v->m_status.RuntimeMark())
      continue;
    v->m_status.SetRuntimeMark();
    ++marked_count;
  }
  return Internal_Create(subd, true, false, false, true, marked_count);
}

unsigned ON_SubDComponentList::CreateFromVertexList(const ON_SubD& subd, const ON_SimpleArray<const ON_SubDVertex*>& vertex_list)
{
  ON_SubDComponentMarksClearAndRestore saved_marks(subd);
  const unsigned count = vertex_list.UnsignedCount();
  unsigned marked_count = 0;
  for (unsigned i = 0; i < count; ++i)
  {
    const ON_SubDVertex* v = vertex_list[i];
    if (nullptr == v)
      continue;
    if (v->m_status.RuntimeMark())
      continue;
    v->m_status.SetRuntimeMark();
    ++marked_count;
  }
  return Internal_Create(subd, true, false, false, true, marked_count);
}

unsigned ON_SubDComponentList::CreateFromMarkedComponents(const ON_SubD& subd, bool bComponentInListMark)
{
  unsigned marked_count = 0;
  ON_SubDComponentIterator cit(subd);
  if (bComponentInListMark)
    bComponentInListMark = true; // avoid other byte values.
  for (ON_SubDComponentPtr c = cit.FirstComponent(); c.IsNotNull(); c = cit.NextComponent())
  {
    if (bComponentInListMark != c.Mark())
      continue;
    ++marked_count;
  }
  return Internal_Create(subd, true, true, true, bComponentInListMark, marked_count);
}

unsigned ON_SubDComponentList::CreateFromMarkedVertices(const ON_SubD& subd, bool bVertexInListMark)
{
  unsigned marked_count = 0;
  ON_SubDVertexIterator vit(subd);
  if (bVertexInListMark)
    bVertexInListMark = true; // avoid other byte values.
  for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
  {
    if (bVertexInListMark != v->m_status.RuntimeMark())
      continue;
    ++marked_count;
  }
  return Internal_Create(subd, true, false, false, bVertexInListMark, marked_count);
}

unsigned ON_SubDComponentList::CreateFromMarkedEdges(const ON_SubD& subd, bool bEdgeInListMark)
{
  unsigned marked_count = 0;
  ON_SubDEdgeIterator eit(subd);
  if (bEdgeInListMark)
    bEdgeInListMark = true; // avoid other byte values.
  for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
  {
    if (bEdgeInListMark != e->m_status.RuntimeMark())
      continue;
    ++marked_count;
  }
  return Internal_Create(subd, false, true, false, bEdgeInListMark, marked_count);
}

unsigned ON_SubDComponentList::CreateFromMarkedFaces(const ON_SubD& subd, bool bFaceInListMark)
{
  unsigned marked_count = 0;
  ON_SubDFaceIterator fit(subd);
  if (bFaceInListMark)
    bFaceInListMark = true; // avoid other byte values.
  for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
  {
    if (bFaceInListMark != f->m_status.RuntimeMark())
      continue;
    ++marked_count;
  }
  return Internal_Create(subd, false, false, true, bFaceInListMark, marked_count);
}

unsigned ON_SubDComponentList::Internal_Create(const ON_SubD & subd, bool bAddVertices, bool bAddEdges, bool bAddFaces, bool bComponentInListMark, unsigned marked_component_count)
{
  Destroy();

  if (0 == marked_component_count)
    return 0;

  const unsigned face_count = bAddFaces ? subd.FaceCount() : 0U;
  const unsigned edge_count = bAddEdges ? subd.EdgeCount() : 0U;
  const unsigned vertex_count = bAddVertices ? subd.VertexCount() : 0U;
  if (0 == vertex_count && 0 == edge_count && 0 == face_count)
    return 0;

  if (marked_component_count > vertex_count + edge_count + face_count)
    return 0;

  bComponentInListMark = bComponentInListMark ? true : false;
  m_component_list.Reserve(marked_component_count);
  m_component_list.SetCount(0);
  if (vertex_count > 0)
  {
    ON_SubDVertexIterator vit(subd);
    for (const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
    {
      if (bComponentInListMark != v->m_status.RuntimeMark())
        continue;
      m_component_list.Append(v->ComponentPtr());
    }
  }
  if (edge_count > 0)
  {
    ON_SubDEdgeIterator eit(subd);
    for (const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
    {
      if (bComponentInListMark != e->m_status.RuntimeMark())
        continue;
      m_component_list.Append(e->ComponentPtr());
    }
  }
  if (face_count > 0)
  {
    ON_SubDFaceIterator fit(subd);
    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      if (bComponentInListMark != f->m_status.RuntimeMark())
        continue;
      m_component_list.Append(f->ComponentPtr());
    }
  }

  if (m_component_list.UnsignedCount() > 0)
  {
    m_subd.ShareDimple(subd);
    m_subd_runtime_serial_number = subd.RuntimeSerialNumber();
    m_subd_geometry_content_serial_number = subd.GeometryContentSerialNumber();
    m_subd_render_content_serial_number = subd.RenderContentSerialNumber();
  }
  return m_component_list.UnsignedCount();
}

unsigned int ON_SubDComponentList::RemoveAllComponents()
{
  const unsigned count0 = Count();
  m_component_list.SetCount(0);
  return count0;
}

unsigned int ON_SubDComponentList::RemoveAllVertices()
{
  return Internal_RemoveComponents(true, false, false);
}

unsigned int ON_SubDComponentList::RemoveAllEdges()
{
  return Internal_RemoveComponents(false, true, false);
}

unsigned int ON_SubDComponentList::RemoveAllFaces()
{
  return Internal_RemoveComponents(false, false, true);
}

unsigned ON_SubDComponentList::Internal_RemoveComponents(
  bool bRemoveVertices,
  bool bRemoveEdges,
  bool bRemoveFaces
)
{
  unsigned int count0 = Count();
  if (bRemoveVertices || bRemoveEdges || bRemoveFaces)
  {
    unsigned count1 = 0;
    for (unsigned i = 0; i < count0; ++i)
    {
      const ON_SubDComponentPtr cptr = m_component_list[i];
      bool bRemove = false;
      switch (cptr.ComponentType())
      {
      case ON_SubDComponentPtr::Type::Vertex:
        bRemove = bRemoveVertices;
        break;
      case ON_SubDComponentPtr::Type::Edge:
        bRemove = bRemoveEdges;
        break;
      case ON_SubDComponentPtr::Type::Face:
        bRemove = bRemoveFaces;
        break;
      default:
        bRemove = true;
      }
      if (bRemove)
        continue;
      m_component_list[count1++] = cptr;
    }
    m_component_list.SetCount(count1);
  }
  return count0 - Count();
}


void ON_SubDComponentList::Destroy()
{
  m_subd_runtime_serial_number = 0;
  m_subd_geometry_content_serial_number = 0;
  m_subd_render_content_serial_number = 0;
  m_component_list.SetCount(0);
  m_subd.ShareDimple(ON_SubD::Empty);
}

const ON_SubDComponentFilter ON_SubDComponentFilter::Create(
  bool bAcceptVertices,
  bool bAcceptEdges,
  bool bAcceptFaces
)
{
  ON_SubDComponentFilter f;
  if (false == bAcceptVertices)
    f.m_bRejectVertices = true;
  if (false == bAcceptEdges)
    f.m_bRejectEdges = true;
  if (false == bAcceptFaces)
    f.m_bRejectFaces = true;
  return f;
}

bool ON_SubDComponentFilter::AcceptComponent(ON_COMPONENT_INDEX component_index, const class ON_Geometry* geometry) const
{
  if (false == component_index.IsSubDComponentIndex())
    return false;
  const ON_SubDComponentRef* cref = ON_SubDComponentRef::Cast(geometry);
  if (nullptr == cref)
    return false;
  const ON_SubDComponentPtr cptr = cref->ComponentPtr();
  if (component_index.m_index != (int)cptr.ComponentId())
    return false;
  switch (component_index.m_type)
  {
  case ON_COMPONENT_INDEX::TYPE::subd_vertex:
    if (ON_SubDComponentPtr::Type::Vertex != cptr.ComponentType())
      return false;
    break;
  case ON_COMPONENT_INDEX::TYPE::subd_edge:
    if (ON_SubDComponentPtr::Type::Edge != cptr.ComponentType())
      return false;
    break;
  case ON_COMPONENT_INDEX::TYPE::subd_face:
    if (ON_SubDComponentPtr::Type::Face != cptr.ComponentType())
      return false;
    break;
  default: // 30 unhandled enum values
    break;
  }
  return AcceptComponent(cptr);
}

bool ON_SubDComponentFilter::AcceptComponent(const class ON_Geometry* geometry) const
{
  return AcceptComponent(ON_SubDComponentRef::Cast(geometry));
}


bool ON_SubDComponentFilter::AcceptComponent(const class ON_SubDComponentRef* cref) const
{
  return (nullptr != cref) ? AcceptComponent(cref->ComponentPtr()) : false;
}

bool ON_SubDComponentFilter::AcceptComponent(ON_SubDComponentPtr cptr) const
{
  switch (cptr.ComponentType())
  {
  case ON_SubDComponentPtr::Type::Vertex:
    return AcceptVertex(cptr.Vertex());
    break;
  case ON_SubDComponentPtr::Type::Edge:
    return AcceptEdge(cptr.Edge());
    break;
  case ON_SubDComponentPtr::Type::Face:
    return AcceptFace(cptr.Face());
    break;
  case ON_SubDComponentPtr::Type::Unset:
    break;
  }
  return false;
}

bool ON_SubDComponentFilter::AcceptVertex(ON_SubDVertexPtr vptr) const
{
  return AcceptVertex(vptr.Vertex());
}

bool ON_SubDComponentFilter::AcceptEdge(ON_SubDEdgePtr eptr) const
{
  return AcceptEdge(eptr.Edge());
}


bool ON_SubDComponentFilter::AcceptFace(ON_SubDFacePtr fptr) const
{
  return AcceptFace(fptr.Face());
}

bool ON_SubDComponentFilter::AcceptVertex(const ON_SubDVertex * v) const
{
  if (m_bRejectVertices)
    return false;

  if (nullptr == v)
    return false;

  if (false == AcceptVertexTag(v->m_vertex_tag))
    return false;

  if (ON_SubDComponentFilter::Topology::Unset != m_vertex_topology_filter)
  {
    // check boundary/interior/nonmanifold
    if (v->HasBoundaryVertexTopology())
    {
      if (0 == (static_cast<unsigned char>(ON_SubDComponentFilter::Topology::Boundary)& static_cast<unsigned char>(m_vertex_topology_filter)))
        return false;
    }
    else if (v->HasInteriorVertexTopology())
    {
      if (0 == (static_cast<unsigned char>(ON_SubDComponentFilter::Topology::Interior)& static_cast<unsigned char>(m_vertex_topology_filter)))
        return false;
    }
    else
    {
      if (0 == (static_cast<unsigned char>(ON_SubDComponentFilter::Topology::Nonmanifold)& static_cast<unsigned char>(m_vertex_topology_filter)))
        return false;
    }
  }

  return true;
}

bool ON_SubDComponentFilter::AcceptEdge(const ON_SubDEdge * e) const
{
  if (m_bRejectEdges)
    return false;

  if (nullptr == e)
    return false;

  if (false == AcceptEdgeTag(e->m_edge_tag))
    return false;

  if (ON_SubDComponentFilter::Topology::Unset != m_edge_topology_filter)
  {
    // check boundary/interior/nonmanifold
    if (1 == e->m_face_count)
    {
      if (0 == (static_cast<unsigned char>(ON_SubDComponentFilter::Topology::Boundary)& static_cast<unsigned char>(m_edge_topology_filter)))
        return false;
    }
    else if (2 == e->m_face_count)
    {
      if (0 == (static_cast<unsigned char>(ON_SubDComponentFilter::Topology::Interior)& static_cast<unsigned char>(m_edge_topology_filter)))
        return false;
    }
    else
    {
      if (0 == (static_cast<unsigned char>(ON_SubDComponentFilter::Topology::Nonmanifold)& static_cast<unsigned char>(m_edge_topology_filter)))
        return false;
    }
  }

  return true;
}

bool ON_SubDComponentFilter::AcceptFace(const ON_SubDFace * f) const
{
  if (m_bRejectFaces)
    return false;

  if (nullptr == f)
    return false;

  if (m_maximum_face_edge_count > 0U)
  {
    const unsigned face_edge_count = f->m_edge_count;
    if (face_edge_count < m_minimum_face_edge_count || face_edge_count > m_maximum_face_edge_count)
      return false;
  }

  if (ON_SubDComponentFilter::Topology::Unset != m_edge_topology_filter)
  {
    const ON_SubDEdgePtr* eptr = f->m_edge4;
    for (unsigned short fei = 0; fei < f->m_edge_count; ++fei, ++eptr)
    {
      if (4 == fei)
      {
        eptr = f->m_edgex;
        if (nullptr == eptr)
          break;
      }
      const ON_SubDEdge* e = eptr->Edge();
      if (nullptr == e)
        continue;
      if (1 == e->m_face_count)
      {
        if (0 == (static_cast<unsigned char>(ON_SubDComponentFilter::Topology::Boundary)& static_cast<unsigned char>(m_edge_topology_filter)))
          return false;
      }
      else if (2 == e->m_face_count)
      {
        if (0 == (static_cast<unsigned char>(ON_SubDComponentFilter::Topology::Interior)& static_cast<unsigned char>(m_edge_topology_filter)))
          return false;
      }
      else
      {
        if (0 == (static_cast<unsigned char>(ON_SubDComponentFilter::Topology::Nonmanifold)& static_cast<unsigned char>(m_edge_topology_filter)))
          return false;
      }
    }
  }

  return true;
}

void ON_SubDComponentFilter::SetAcceptVertices(bool bAcceptVertices)
{
  m_bRejectVertices = bAcceptVertices ? false : true;
}

bool ON_SubDComponentFilter::AcceptVertices() const
{
  return false == m_bRejectVertices;
}

void ON_SubDComponentFilter::SetAcceptEdges(bool bAcceptEdges)
{
  m_bRejectEdges = bAcceptEdges ? false : true;
}

bool ON_SubDComponentFilter::AcceptEdges() const
{
  return false == m_bRejectEdges;
}

void ON_SubDComponentFilter::SetAcceptFaces(bool bAcceptFaces)
{
  m_bRejectFaces = bAcceptFaces ? false : true;
}

bool ON_SubDComponentFilter::AcceptFaces() const
{
  return false == m_bRejectFaces;
}

void ON_SubDComponentFilter::SetVertexTopologyFilter(ON_SubDComponentFilter::Topology vertex_topology_filter)
{
  m_vertex_topology_filter = vertex_topology_filter;
}

void ON_SubDComponentFilter::ClearVertexTopologyFilter()
{
  m_vertex_topology_filter = ON_SubDComponentFilter::Topology::Unset;
}

ON_SubDComponentFilter::Topology ON_SubDComponentFilter::VertexTopologyFilter() const
{
  return m_vertex_topology_filter;
}

void ON_SubDComponentFilter::SetEdgeTopologyFilter(ON_SubDComponentFilter::Topology edge_topology_filter)
{
  m_edge_topology_filter = edge_topology_filter;
}

ON_SubDComponentFilter::Topology ON_SubDComponentFilter::EdgeTopologyFilter() const
{
  return m_edge_topology_filter;
}

void ON_SubDComponentFilter::ClearEdgeTopologyFilter()
{
  m_edge_topology_filter = ON_SubDComponentFilter::Topology::Unset;
}

void ON_SubDComponentFilter::SetFaceTopologyFilter(ON_SubDComponentFilter::Topology face_topology_filter)
{
  m_face_topology_filter = face_topology_filter;
}

ON_SubDComponentFilter::Topology ON_SubDComponentFilter::FaceTopologyFilter() const
{
  return m_face_topology_filter;
}

void ON_SubDComponentFilter::ClearFaceTopologyFilter()
{
  m_face_topology_filter = ON_SubDComponentFilter::Topology::Unset;
}

bool ON_SubDComponentFilter::AcceptVertexTag(ON_SubDVertexTag vertex_tag) const
{
  if (ON_SubDVertexTag::Unset == m_vertex_tag_filter[0])
    return true; // no tag filter

  for (size_t i = 0; i < sizeof(m_vertex_tag_filter) / sizeof(m_vertex_tag_filter[0]); ++i)
  {
    if (ON_SubDVertexTag::Unset == m_vertex_tag_filter[i])
      break;
    if (m_vertex_tag_filter[i] != vertex_tag)
      continue;
    return true;
  }
  return false;
}

void ON_SubDComponentFilter::AddAcceptedVertexTag(ON_SubDVertexTag vertex_tag)
{
  for (size_t i = 0; i < sizeof(m_vertex_tag_filter) / sizeof(m_vertex_tag_filter[0]); ++i)
  {
    if (vertex_tag == m_vertex_tag_filter[i])
      break;
    if (ON_SubDVertexTag::Unset == m_vertex_tag_filter[i])
    {
      m_vertex_tag_filter[i] = vertex_tag;
      break;
    }
  }
}

void ON_SubDComponentFilter::ClearVertexTagFilter()
{
  for (size_t i = 0; i < sizeof(m_vertex_tag_filter) / sizeof(m_vertex_tag_filter[0]); ++i)
    m_vertex_tag_filter[i] = ON_SubDVertexTag::Unset;
}


bool ON_SubDComponentFilter::AcceptEdgeTag(ON_SubDEdgeTag edge_tag) const
{
  if (ON_SubDEdgeTag::Unset == m_edge_tag_filter[0])
    return true; // no tag filter

  for (size_t i = 0; i < sizeof(m_edge_tag_filter) / sizeof(m_edge_tag_filter[0]); ++i)
  {
    if (ON_SubDEdgeTag::Unset == m_edge_tag_filter[i])
      break;
    if (m_edge_tag_filter[i] != edge_tag)
      continue;
    return true;
  }
  return false;
}

void ON_SubDComponentFilter::AddAcceptedEdgeTag(ON_SubDEdgeTag edge_tag)
{
  for (size_t i = 0; i < sizeof(m_edge_tag_filter) / sizeof(m_edge_tag_filter[0]); ++i)
  {
    if (edge_tag == m_edge_tag_filter[i])
      break;
    if (ON_SubDEdgeTag::Unset == m_edge_tag_filter[i])
    {
      m_edge_tag_filter[i] = edge_tag;
      break;
    }
  }
}

void ON_SubDComponentFilter::ClearEdgeTagFilter()
{
  for (size_t i = 0; i < sizeof(m_edge_tag_filter) / sizeof(m_edge_tag_filter[0]); ++i)
    m_edge_tag_filter[i] = ON_SubDEdgeTag::Unset;
}

bool ON_SubDComponentFilter::AcceptFaceEdgeCount(
  unsigned face_edge_count
) const
{
  return (m_maximum_face_edge_count >= 3U) ? (face_edge_count >= m_minimum_face_edge_count && face_edge_count <= m_maximum_face_edge_count) : false;
}

void ON_SubDComponentFilter::SetFaceEdgeCountFilter(
  unsigned minimum_face_edge_count,
  unsigned maximum_face_edge_count
)
{
  if (minimum_face_edge_count <= maximum_face_edge_count && maximum_face_edge_count >= 3U)
  {
    m_minimum_face_edge_count = minimum_face_edge_count;
    m_maximum_face_edge_count = maximum_face_edge_count;
  }
}

void ON_SubDComponentFilter::ClearFaceEdgeCountFilter()
{
  m_minimum_face_edge_count = 0U;
  m_maximum_face_edge_count = 0U;
}


double ON_SubD::SurfacePointRadiusFromControlPointRadius(unsigned int polygon_count, double polgon_radius)
{
  for (;;)
  {
    if (polygon_count < 3)
      break;
    if (false == ON_IsValid(polgon_radius))
      break;
    const double a = ON_2PI / ((double)polygon_count);
    ON_2dPoint cv[4] = {
      ON_2dPoint(1,0),
      ON_2dPoint(cos(a),sin(a)),
      ON_2dPoint(cos(2 * a),sin(2 * a)),
      ON_2dPoint(cos(3 * a),sin(3 * a))
    };
    double k[6] = { -2,-1,0,1,2,3 };
    ON_NurbsCurve c;
    c.m_dim = 2;
    c.m_order = 4;
    c.m_cv_count = 4;
    c.m_cv = &cv[0].x;
    c.m_cv_stride = (int)(&cv[1].x - &cv[0].x);
    c.m_knot = k;
    const ON_3dPoint p = c.PointAt(0.0);
    const double r = ON_2dPoint(p.x, p.y).DistanceTo(ON_2dPoint::Origin);
    if (r > 0.0)
      return polgon_radius * r;
    break;
  }
  return ON_DBL_QNAN;
}


double ON_SubD::ControlPointRadiusFromSurfacePointRadius(unsigned int polygon_count, double surface_radius)
{
  for (;;)
  {
    if (false == ON_IsValid(surface_radius))
      break;
    const double r = ON_SubD::SurfacePointRadiusFromControlPointRadius(polygon_count, 1.0);
    if (r > 0.0)
      return surface_radius / r;
    break;
  }
  return ON_DBL_QNAN;
}

ON_SubDFace* ON_SubD::FindOrAddFace(
  ON_SubDEdgeTag new_edge_tag,
  const ON_SubDVertex* face_vertices[],
  size_t vertex_count
)
{
  if (nullptr == face_vertices)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (vertex_count < 3)
    return ON_SUBD_RETURN_ERROR(nullptr);
  if (vertex_count > (size_t)ON_SubDFace::MaximumEdgeCount)
    return ON_SUBD_RETURN_ERROR(nullptr);


  // Make sure v[] has vertex_count unique non-null vertices.
  for (unsigned i = 0; i < vertex_count; ++i)
  {
    if (nullptr == face_vertices[i])
      return ON_SUBD_RETURN_ERROR(nullptr);
    for (unsigned j = i + 1; j < vertex_count; ++j)
    {
      if (face_vertices[i] == face_vertices[j])
        return ON_SUBD_RETURN_ERROR(nullptr);
    }
  }

  ON_SimpleArray<ON_SubDEdgePtr> eptrs(vertex_count);
  ON_SimpleArray<const ON_SubDFace*> faces(4);
  ON_SimpleArray<const ON_SubDFace*> faces_to_keep(4);
  const ON_SubDVertex* ev[2] = { nullptr, face_vertices[0] };
  for (unsigned i = 0; i < vertex_count; ++i)
  {
    ev[0] = ev[1];
    ev[1] = face_vertices[(i + 1) % vertex_count];
    ON_SubDEdgePtr eptr = ON_SubDEdge::FromVertices(ev[0], ev[1]);
    if (eptr.IsNull())
    {
      // need to create this edge
      ON_SubDEdge* e = this->AddEdge(new_edge_tag, const_cast<ON_SubDVertex*>(ev[0]), const_cast<ON_SubDVertex*>(ev[1]));
      if (nullptr == e)
        return ON_SUBD_RETURN_ERROR(nullptr);
      eptr = ON_SubDEdgePtr::Create(e, 0);
      faces.SetCount(0);
    }
    else
    {
      const ON_SubDEdge* e = eptr.Edge();
      if (nullptr == e)
        return ON_SUBD_RETURN_ERROR(nullptr);
      if (0 == e->m_face_count)
        faces.SetCount(0);
      else if (0 == i || faces.Count() > 0)
      {
        faces_to_keep.SetCount(0);
        const ON_SubDFacePtr* fptr = e->m_face2;
        for (unsigned short efi = 0; efi < e->m_face_count; ++efi, ++fptr)
        {
          if (2 == efi)
          {
            fptr = e->m_facex;
            if (nullptr == fptr)
              break;
          }
          const ON_SubDFace* f = ON_SUBD_FACE_POINTER(fptr->m_ptr);
          if (nullptr == f)
            continue;
          if (0 == i)
            faces_to_keep.Append(f);
          else
          {
            for (unsigned j = 0; j < faces.UnsignedCount(); ++j)
            {
              if (f != faces[j])
                continue;
              // every edge so far is attached to f
              faces_to_keep.Append(f);
              break;
            }
          }
        }
        faces = faces_to_keep;
      }
    }
    eptrs.Append(eptr);
  }

  if (eptrs.UnsignedCount() != vertex_count)
    return ON_SUBD_RETURN_ERROR(nullptr);

  ON_SubDFace* new_face = this->AddFace(eptrs);

  return new_face;
}

ON_SubD* ON_SubD::CreateCylinder(
  const ON_Cylinder& cylinder,
  unsigned circumference_face_count,
  unsigned height_face_count,
  ON_SubDEndCapStyle end_cap_style,
  ON_SubDEdgeTag end_cap_edge_tag,
  ON_SubDComponentLocation radius_location,
  ON_SubD* destination_subd
)
{
  if (nullptr != destination_subd)
    *destination_subd = ON_SubD::Empty;

  if (false == cylinder.IsValid())
  {
    ON_SUBD_ERROR("Invalid cylinder parameter.");
    return nullptr;
  }

  if (circumference_face_count < 3)
  {
    ON_SUBD_ERROR("Invalid circumference_face_count parameter.");
    return nullptr;
  }

  if (height_face_count < 1)
  {
    ON_SUBD_ERROR("Invalid height_face_count parameter.");
    return nullptr;
  }

  const double r = cylinder.circle.Radius();
  if (false == (r > 0.0 && r < ON_UNSET_POSITIVE_VALUE))
  {
    ON_SUBD_ERROR("Invalid cylinder radius parameter.");
    return nullptr;
  }

  ////////////////////////////////////////////
  // Validate and sanitize end_cap_style parameter
  //
  switch (end_cap_style)
  {
  case ON_SubDEndCapStyle::Unset:
    end_cap_style = ON_SubDEndCapStyle::None;
    break;

  case ON_SubDEndCapStyle::None:
    break;

  case ON_SubDEndCapStyle::Triangles:
    if (circumference_face_count < 2)
      end_cap_style = ON_SubDEndCapStyle::None;
    else if (circumference_face_count <= 3)
      end_cap_style = ON_SubDEndCapStyle::Ngon; // single triangle
    break;

  case ON_SubDEndCapStyle::Quads:
    if (circumference_face_count < 2)
      end_cap_style = ON_SubDEndCapStyle::None;
    else if (circumference_face_count <= 4)
      end_cap_style = ON_SubDEndCapStyle::Ngon; // single quad or single triangle
    else if (0 != (circumference_face_count%2))
      end_cap_style = ON_SubDEndCapStyle::Triangles; // must have even number of sized for a multi-quad cap.
    break;

  case ON_SubDEndCapStyle::Ngon:
    if (circumference_face_count < 2)
      end_cap_style = ON_SubDEndCapStyle::None;
    break;

  default:
    end_cap_style = ON_SubDEndCapStyle::None;
    break;
  }
  const bool bCapEnds = ON_SubDEndCapStyle::None != end_cap_style;

  ///////////////////////////////////////////////
  // If cylinder in infinite, choose a height that makes the faces squarish.
  //
  const double height = cylinder.IsFinite() ? cylinder.Height() : (ON_2PI*r/((double)circumference_face_count))*((double)height_face_count);
  if ( false == (ON_IsValid(height) && 0.0 != height) )
  {
    ON_SUBD_ERROR("Invalid cylinder or count parameters.");
    return nullptr;
  }

  /////////////////////////////////////////////
  // H = vector that translates a ring of vertices / edges from one circumference to the next.
  const ON_3dVector H = (height / ((double)height_face_count)) * cylinder.Axis().UnitVector();

  /////////////////////////////////////////////
  // Adjust radius so result has surface and control net in the correct location.
  //
  ON_Circle point_generator(cylinder.IsFinite() ? cylinder.CircleAt(cylinder.height[0]) : cylinder.circle);
  point_generator.radius = (ON_SubDComponentLocation::Surface == radius_location) ? ON_SubD::ControlPointRadiusFromSurfacePointRadius(circumference_face_count, r) : r;


  //////////////////////////////////////////////
  // circumference_points[] = ring of control point locations around the cylinder's base.
  //
  ON_SimpleArray<ON_3dPoint> circumference_points(circumference_face_count);
  for (unsigned i = 0; i < circumference_face_count; ++i)
  {
    const double a = ON_Interval::ZeroToTwoPi.ParameterAt(((double)i) / ((double)circumference_face_count));
    const ON_3dPoint P = point_generator.PointAt(a);
    circumference_points.Append(P);
  }

  /////////////////////////////////////////////
  // center[2] = cap centers (if needed).
  const ON_3dPoint center[2] = { point_generator.Center(), point_generator.Center() + (((double)height_face_count) * H) };

  ON_SubD* subd = (nullptr != destination_subd) ? destination_subd : new ON_SubD();

  // v00 = 1st vertex in the previous ring of vertices / edges
  ON_SubDVertex* v00 = nullptr;
  for (unsigned j = 0; j <= height_face_count; ++j)
  {
    // add a new ring of vertices / edges

    // v0 = 1st vertex in this ring of vertices / edges
    ON_SubDVertex* v0 = nullptr;
    ON_SubDVertex* ev[2] = {};

    const ON_SubDVertexTag vtag
      = (false == bCapEnds || ON_SubDEdgeTag::Crease == end_cap_edge_tag) && (0 == j || j == height_face_count)
      ? ON_SubDVertexTag::Crease
      : ON_SubDVertexTag::Smooth;
    const ON_SubDEdgeTag etag = (ON_SubDVertexTag::Crease == vtag) ? ON_SubDEdgeTag::Crease : ON_SubDEdgeTag::Smooth;


    for (unsigned i = 0; i < circumference_face_count; ++i)
    {
      const ON_3dPoint P = circumference_points[i];
      circumference_points[i] = P + H; // move circumference_points[i] up to next ring

      ev[0] = ev[1];
      ev[1] = subd->AddVertex(vtag, P);
      if (0 == i)
        v0 = ev[1];
      else
        subd->AddEdge(etag, ev[0], ev[1]);
    }
    subd->AddEdge(etag, ev[1], v0);

    if (j > 0 && nullptr != v00 && nullptr != v0)
    {
      // add a new ring of faces

      const ON_SubDVertex* fv[4] = {
        nullptr,
        v00, // 1st vertex in bottom face edge ring
        v0, // 1st vertex in top face edge ring
        nullptr
      };
      for (unsigned i = 0; i < circumference_face_count; ++i)
      {
        const bool bLastFaceInThisRing = (i+1 == circumference_face_count);
        // shift to next face's corners
        fv[0] = fv[1];
        fv[3] = fv[2];
        fv[1] = bLastFaceInThisRing ? v00 : fv[0]->m_next_vertex;
        fv[2] = bLastFaceInThisRing ? v0 : fv[3]->m_next_vertex;
        
        // make a new face
        subd->FindOrAddFace(ON_SubDEdgeTag::Smooth, fv, 4);
      }
    }

    v00 = v0;
  }

  if (bCapEnds)
  {
    ON_SimpleArray<ON_SubDEdgePtr> bdry(circumference_face_count);
    const ON_SubDVertex* last_wall_vertex = subd->LastVertex();
    const ON_SubDEdge* last_wall_edge = subd->LastEdge();

    const bool bCapHasCenterVertex = ON_SubDEndCapStyle::Triangles == end_cap_style || ON_SubDEndCapStyle::Quads == end_cap_style;

    for (unsigned enddex = 0; enddex < 2; ++enddex)
    {
      bdry.SetCount(0);
      const ON_SubDVertex* v0 = (0 == enddex) ? const_cast<ON_SubDVertex*>(subd->FirstVertex()) : v00;
      const ON_SubDVertex* ev[2] = { nullptr, v0 };
      for (unsigned i = 0; i < circumference_face_count; ++i)
      {
        ev[0] = ev[1];
        ev[1] = (i + 1 < circumference_face_count) ? const_cast<ON_SubDVertex*>(ev[1]->m_next_vertex) : v0;
        const ON_SubDEdgePtr eptr = ON_SubDEdge::FromVertices(ev[0], ev[1]);
        if (eptr.IsNull())
          break;
        bdry.Append(eptr);
      }
      if (circumference_face_count != bdry.UnsignedCount())
        break;

      if (0 == enddex)
        ON_SubDEdgeChain::ReverseEdgeChain(bdry);

      const ON_SubDVertex* fv[4] = {};
      if (bCapHasCenterVertex)
      {
        // fv[0] = vertex at the center of the cap
        fv[0] = subd->AddVertex(ON_SubDVertexTag::Smooth, center[enddex]);
        if (nullptr == fv[0])
          break;
      }

      switch (end_cap_style)
      {
      case ON_SubDEndCapStyle::Unset:
        break;

      case ON_SubDEndCapStyle::None:
        break;

      case ON_SubDEndCapStyle::Triangles:
        if (nullptr != fv[0])
        {
          // radial triangles around the center vertex
          fv[2] = bdry[0].RelativeVertex(0);
          for (unsigned i = 0; i < circumference_face_count; ++i)
          {
            fv[1] = fv[2];
            fv[2] = bdry[i].RelativeVertex(1);
            subd->FindOrAddFace(ON_SubDEdgeTag::Smooth, fv, 3);
          }
        }
        break;

      case ON_SubDEndCapStyle::Quads:
        if (nullptr != fv[0])
        {
          // radial quads around the center vertex
          fv[3] = bdry[0].RelativeVertex(0);
          for (unsigned i = 0; i < circumference_face_count; i += 2)
          {
            fv[1] = fv[3];
            fv[2] = bdry[i].RelativeVertex(1);
            fv[3] = bdry[(i+1)% circumference_face_count].RelativeVertex(1);
            subd->FindOrAddFace(ON_SubDEdgeTag::Smooth, fv, 4);
          }
        }
        break;

      case ON_SubDEndCapStyle::Ngon:
        // cap = single n-gon
        subd->AddFace(bdry);
        break;
      default:
        break;
      }
    }

    if (bCapHasCenterVertex)
    {
      // vertices and edges added inside the caps are smooth.
      for (const ON_SubDVertex* v = (nullptr != last_wall_vertex) ? last_wall_vertex->m_next_vertex : nullptr; nullptr != v; v = v->m_next_vertex)
        const_cast<ON_SubDVertex*>(v)->m_vertex_tag = ON_SubDVertexTag::Smooth;
      for (const ON_SubDEdge* e = (nullptr != last_wall_edge) ? last_wall_edge->m_next_edge : nullptr; nullptr != e; e = e->m_next_edge)
        const_cast<ON_SubDEdge*>(e)->m_edge_tag = ON_SubDEdgeTag::Smooth;
    }
  }

  if (nullptr != subd)
    subd->UpdateAllTagsAndSectorCoefficients(true);

  return subd;
}

bool ON_Symmetry::SetSymmetricObject(const ON_SubD* subd) const
{
  const ON_SubDimple* subdimple = (nullptr != subd) ? subd->SubDimple() : nullptr;
  return SetSymmetricObject(subdimple);
}

bool ON_Symmetry::SetSymmetricObject(const ON_SubDimple* subdimple) const
{
  bool rc;

  if (nullptr != subdimple && this->IsSet())
  {
    m_symmetric_object_content_serial_number = subdimple->GeometryContentSerialNumber();
    m_symmetric_object_topology_hash = subdimple->SubDHash(ON_SubDHashType::Topology, false).SubDHash();
    m_symmetric_object_geometry_hash = subdimple->SubDHash(ON_SubDHashType::Geometry, false).SubDHash();
    rc = true;
  }
  else
  {
    ClearSymmetricObject();
    rc = false;
  }

  return rc;
}

double ON_SubDExpandEdgesParameters::ConstantOffset() const
{
  return this->m_constant_offset;
}

void ON_SubDExpandEdgesParameters::SetConstantOffset(double offset)
{
  offset = ON_SubDExpandEdgesParameters::CleanupOffset(offset);
  if (ON_SubDExpandEdgesParameters::IsValidConstantOffset(offset))
    this->m_constant_offset = offset;
}


bool ON_SubDExpandEdgesParameters::IsValidForHalfOffset(
  const ON_SimpleArray<ON_SubDEdgePtr>& edge_chain
)
{
  const unsigned count = edge_chain.UnsignedCount();
  for (unsigned i = 0; i < count; ++i)
  {
    if (false == edge_chain[i].HasInteriorEdgeTopology(true))
      return false;
  }
  return ON_SubDEdgeChain::IsSingleEdgeChain(edge_chain);
}


bool ON_SubDExpandEdgesParameters::IsValidForVariableOffset(
  const ON_SimpleArray<ON_SubDEdgePtr>& edge_chain
)
{
  bool bIsClosed = false;
  bool bIsSorted = false;
  const bool IsSingleEdgeChain = ON_SubDEdgeChain::IsSingleEdgeChain(edge_chain, bIsClosed, bIsSorted);
  return IsSingleEdgeChain && false == bIsClosed;
}

const ON_Interval ON_SubDExpandEdgesParameters::VariableOffset() const
{
  return this->m_variable_offsets;
}

void ON_SubDExpandEdgesParameters::SetVariableOffset(ON_Interval variable_offsets)
{
  variable_offsets[0] = ON_SubDExpandEdgesParameters::CleanupOffset(variable_offsets[0]);
  variable_offsets[1] = ON_SubDExpandEdgesParameters::CleanupOffset(variable_offsets[1]);
  if (ON_SubDExpandEdgesParameters::IsValidVariableOffset(variable_offsets))
  {
    this->m_variable_offsets = variable_offsets;
  }
  else
  {
    // invalid input
    ClearVariableOffset();
    if (ON_SubDExpandEdgesParameters::IsValidConstantOffset(variable_offsets[0])
      && fabs(variable_offsets[0] - variable_offsets[1]) <= ON_SubDExpandEdgesParameters::OffsetTolerance
      )
    {
      SetConstantOffset(variable_offsets[0]);
    }
  }
}

void ON_SubDExpandEdgesParameters::ClearVariableOffset()
{
  this->m_variable_offsets = ON_Interval::Nan;
}

bool ON_SubDExpandEdgesParameters::IsVariableOffset() const
{
  return ON_SubDExpandEdgesParameters::IsValidVariableOffset(this->m_variable_offsets);
}

bool ON_SubDExpandEdgesParameters::IsValidConstantOffset(
  double constant_offset_candidate
)
{
  return constant_offset_candidate >= ON_SubDExpandEdgesParameters::MinimumOffset && constant_offset_candidate <= ON_SubDExpandEdgesParameters::MaximumOffset;
}

bool ON_SubDExpandEdgesParameters::IsValidVariableOffset(
  ON_Interval variable_offset_candidate
)
{
  for (int i = 0; i < 2; i++)
  {
    const double x[2] = { variable_offset_candidate[i], variable_offset_candidate[1 - i] };
    if (false == ON_SubDExpandEdgesParameters::IsValidConstantOffset(x[0]))
    {
      if (0.0 == x[0])
        return (x[1] >= ON_SubDExpandEdgesParameters::MinimumOffset && x[1] <= 1.0);
      if (1.0 == x[0])
        return (x[1] >= 0.0 && x[1] <= ON_SubDExpandEdgesParameters::MaximumOffset);
      return false;
    }
  }
  return fabs(variable_offset_candidate[0] - variable_offset_candidate[1]) > ON_SubDExpandEdgesParameters::OffsetTolerance;
}


ON_SubDExpandEdgesParameters::Style ON_SubDExpandEdgesParameters::FaceStyle() const
{
  return this->m_face_style;
}

void ON_SubDExpandEdgesParameters::SetFaceStyle(ON_SubDExpandEdgesParameters::Style face_style)
{
  this->m_face_style = face_style;
}

bool ON_SubDExpandEdgesParameters::IsHalfFaceStyle() const
{
  return
    ON_SubDExpandEdgesParameters::Style::HalfLeft == this->m_face_style
    || ON_SubDExpandEdgesParameters::Style::HalfRight == this->m_face_style
    ;
}

const ON_Color ON_SubDExpandEdgesParameters::FaceColor() const
{
  return this->m_face_color;
}

void ON_SubDExpandEdgesParameters::SetFaceColor(ON_Color face_color)
{
  this->m_face_color = face_color;
}

const ON_ComponentStatus ON_SubDExpandEdgesParameters::FaceStatus() const
{
  return this->m_face_status;
}

void ON_SubDExpandEdgesParameters::SetFaceStatus(ON_ComponentStatus face_status)
{
  this->m_face_status = ON_ComponentStatus::NoneSet;
  this->m_face_status.SetRuntimeMark(face_status.SetRuntimeMark());
  this->m_face_status.SetMarkBits(face_status.MarkBits());
  if (face_status.IsSelectedPersistent())
    this->m_face_status.SetSelectedState(ON_ComponentState::SelectedPersistent, face_status.IsHighlighted());
  else if (face_status.IsSelected())
    this->m_face_status.SetSelectedState(ON_ComponentState::Selected, face_status.IsHighlighted());
  else if (face_status.IsHighlighted())
    this->m_face_status.SetHighlightedState(true);
}

const ON_SHA1_Hash ON_SubDExpandEdgesParameters::Hash() const
{
  ON_SHA1 sha1;
  sha1.AccumulateDouble(ConstantOffset());
  sha1.AccumulateDouble(VariableOffset().m_t[0]);
  sha1.AccumulateDouble(VariableOffset().m_t[1]);
  sha1.AccumulateInteger32((unsigned int)FaceColor());
  sha1.AccumulateBytes(&m_face_status, sizeof(m_face_status));
  sha1.AccumulateInteger32((unsigned int)FaceStyle());
  return sha1.Hash();
}

bool operator==(const ON_SubDExpandEdgesParameters& lhs, const ON_SubDExpandEdgesParameters& rhs)
{
  return lhs.Hash() == rhs.Hash();
}

bool operator!=(const ON_SubDExpandEdgesParameters& lhs, const ON_SubDExpandEdgesParameters& rhs)
{
  return lhs.Hash() != rhs.Hash();
}


double ON_SubDExpandEdgesParameters::CleanupOffset(double x)
{

  const double r[] = {
    0.0,
    1.0,
    ON_SubDExpandEdgesParameters::SmallOffset,
    ON_SubDExpandEdgesParameters::MediumOffset,
    ON_SubDExpandEdgesParameters::LargeOffset,
    ON_SubDExpandEdgesParameters::MinimumOffset,
    ON_SubDExpandEdgesParameters::MaximumOffset
  };

  const size_t c = sizeof(r) / sizeof(r[0]);
  for (size_t i = 0; i < c; ++i)
  {
    if (fabs(x - r[i]) <= ON_SubDExpandEdgesParameters::OffsetTolerance)
      return r[i];
  }

  if (x > 0.0 && x < ON_SubDExpandEdgesParameters::MinimumOffset)
    x = ON_SubDExpandEdgesParameters::MinimumOffset;
  else if (x < 1.0 && x > ON_SubDExpandEdgesParameters::MaximumOffset)
    x = ON_SubDExpandEdgesParameters::MaximumOffset;

  if (x >= 0.0 && x <= 1.0)
    return x;

  return ON_DBL_QNAN;
}


