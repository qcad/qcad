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

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDRef
//

ON_SubDRef::ON_SubDRef() ON_NOEXCEPT
{}

ON_SubDRef::~ON_SubDRef()
{
  m_subd_sp.reset();
}

ON_SubDRef::ON_SubDRef(const ON_SubDRef& src) ON_NOEXCEPT
  : m_subd_sp(src.m_subd_sp)
{}

ON_SubDRef& ON_SubDRef::operator=(const ON_SubDRef& src)
{
  if ( this != &src )
    m_subd_sp = src.m_subd_sp;
  return *this;
}

#if defined(ON_HAS_RVALUEREF)
// rvalue copy constructor
ON_SubDRef::ON_SubDRef( ON_SubDRef&& src) ON_NOEXCEPT
  : m_subd_sp(std::move(src.m_subd_sp))
{}

// rvalue assignment operator
ON_SubDRef& ON_SubDRef::operator=(ON_SubDRef&& src)
{
  m_subd_sp.reset();
  m_subd_sp = std::move(src.m_subd_sp);
  return *this;
}
#endif

const class ON_SubD& ON_SubDRef::SubD() const
{
  const ON_SubD* subd = m_subd_sp.get();
  if ( nullptr == subd )
    subd = &ON_SubD::Empty;
  return *subd;
}

unsigned int ON_SubDRef::ReferenceCount() const
{
  return (unsigned int)m_subd_sp.use_count();
}

void ON_SubDRef::Clear()
{
  m_subd_sp.reset();
}

class ON_SubD& ON_SubDRef::NewSubD()
{
  ON_SubD* subd = new ON_SubD();
  ON_SubD* managed_subd = SetSubDForExperts(subd);
  return *managed_subd;
}

class ON_SubD& ON_SubDRef::CopySubD(
  const ON_SubDRef& src
  )
{
  return CopySubD(src.SubD());
}

class ON_SubD& ON_SubDRef::CopySubD(
  const ON_SubD& src
  )
{
  ON_SubD* subd_copy = new ON_SubD(src);
  ON_SubD* managed_subd = SetSubDForExperts(subd_copy);
  return *managed_subd;
}

class ON_SubD& ON_SubDRef::UniqueSubD()
{
  const ON_SubD& subd = SubD();
  if (m_subd_sp.use_count() > 1 )
    return CopySubD(subd);
  if (subd.m_subdimple_sp.use_count() > 1)
    return CopySubD(subd);
  return const_cast< ON_SubD& >(subd);
}

class ON_SubD* ON_SubDRef::SetSubDForExperts(
  class ON_SubD*& subd
  )
{
  Clear();
  ON_SubD* managed_subd = ( subd == &ON_SubD::Empty ) ? nullptr : subd;
  subd = nullptr;
  if (nullptr != managed_subd )
    m_subd_sp = std::shared_ptr<class ON_SubD>(managed_subd);
  return managed_subd;
}

ON_SubDRef::ON_SubDRef(
  const ON_SubD& subd
  )
{
  const ON_SubDimple* subdimple = subd.SubDimple();
  if (nullptr != subdimple)
  {
    ON_SubD* managed_subd = new ON_SubD();
    managed_subd->ShareDimple(subd);
    this->SetSubDForExperts(managed_subd);
    if (nullptr != managed_subd)
      delete managed_subd;
  }
}

ON_SubDRef ON_SubDRef::CreateReferenceForExperts(
  const ON_SubD& subd
  )
{
  ON_SubDRef subd_ref(subd);
  return subd_ref;
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentRef
//

ON_OBJECT_IMPLEMENT(ON_SubDComponentRef,ON_Geometry,"C221FC6D-36B7-47E8-90AA-AC8EC784E3DD");

ON_SubDComponentRef::ON_SubDComponentRef(const ON_SubDComponentRef& src) ON_NOEXCEPT
  : ON_Geometry(src)
  , m_subd_ref(src.m_subd_ref)
  , m_component_ptr(src.m_component_ptr)
  , m_component_index(src.m_component_index)
  , m_component_location(src.m_component_location)
  , m_reference_id(src.m_reference_id)
{}

ON_SubDComponentRef& ON_SubDComponentRef::operator=(const ON_SubDComponentRef& src)
{
  if (this != &src)
  {
    ON_Geometry::operator=(src);
    m_subd_ref = src.m_subd_ref;
    m_component_ptr = src.m_component_ptr;
    m_component_index = src.m_component_index;
    m_component_location = src.m_component_location;
    m_reference_id = src.m_reference_id;
  }
  return *this;
}

#if defined(ON_HAS_RVALUEREF)
ON_SubDComponentRef::ON_SubDComponentRef( ON_SubDComponentRef&& src ) ON_NOEXCEPT
  : ON_Geometry(std::move(src))
  , m_subd_ref(std::move(src.m_subd_ref))
  , m_component_ptr(src.m_component_ptr)
  ,  m_component_index(src.m_component_index)
  , m_component_location(src.m_component_location)
  , m_reference_id(src.m_reference_id)
{}

ON_SubDComponentRef& ON_SubDComponentRef::operator=(ON_SubDComponentRef&& src)
{
  if ( this != &src )
  {
    Clear();
    ON_Geometry::operator=(std::move(src));
    m_subd_ref = std::move(src.m_subd_ref);
    m_component_ptr = src.m_component_ptr;
    m_component_index = src.m_component_index;
    m_component_location = src.m_component_location;
    m_reference_id = src.m_reference_id;
  }
  return *this;
}

#endif


int ON_SubDComponentRef::Compare(const ON_SubDComponentRef* lhs, const ON_SubDComponentRef* rhs)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  const ON__UINT64 lhs_sn = lhs->m_subd_ref.SubD().RuntimeSerialNumber();
  const ON__UINT64 rhs_sn = rhs->m_subd_ref.SubD().RuntimeSerialNumber();
  if (lhs_sn < rhs_sn)
    return -1;
  if (lhs_sn > rhs_sn)
    return 1;
  return ON_COMPONENT_INDEX::Compare(&lhs->m_component_index, &rhs->m_component_index);
}

int ON_SubDComponentRef::Compare2(const ON_SubDComponentRef* const* lhs, const ON_SubDComponentRef* const* rhs)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  return ON_SubDComponentRef::Compare(*lhs, *rhs);
}

const ON_SubDComponentRef ON_SubDComponentRef::Create(
  const ON_SubDRef& subd_ref,
  ON_COMPONENT_INDEX component_index,
  ON_SubDComponentLocation component_location,
  ON__UINT_PTR reference_id
  )
{
  ON_SubDComponentPtr component_ptr = subd_ref.SubD().ComponentPtrFromComponentIndex(component_index);
  return ON_SubDComponentRef::Create(subd_ref,component_ptr,component_location,reference_id);
}

const ON_SubDComponentRef ON_SubDComponentRef::Create(
  const ON_SubDRef& subd_ref,
  ON_SubDComponentPtr component_ptr,
  ON_SubDComponentLocation component_location,
  ON__UINT_PTR reference_id
  )
{
  ON_SubDComponentRef component_ref;
  component_ref.m_subd_ref = subd_ref;
  component_ref.m_reference_id = reference_id;
  bool bValidInput = false;
  switch (component_ptr.ComponentType())
  {
  case ON_SubDComponentPtr::Type::Vertex:
    {
      const ON_SubDVertex* vertex = ON_SUBD_VERTEX_POINTER(component_ptr.m_ptr);
      if (nullptr != vertex && vertex->m_id > 0 && vertex->m_id < ON_UNSET_UINT_INDEX)
      {
        component_ref.m_component_ptr = component_ptr;
        component_ref.m_component_index.Set(ON_COMPONENT_INDEX::TYPE::subd_vertex,(int)vertex->m_id);
        component_ref.m_component_location = component_location;
        bValidInput = true;
      }
    }
    break;
  case ON_SubDComponentPtr::Type::Edge:
    {
      const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(component_ptr.m_ptr);
      if (nullptr != edge && edge->m_id > 0 && edge->m_id < ON_UNSET_UINT_INDEX)
      {
        component_ref.m_component_ptr = component_ptr;
        component_ref.m_component_index.Set(ON_COMPONENT_INDEX::TYPE::subd_edge,(int)edge->m_id);
        component_ref.m_component_location = component_location;
        bValidInput = true;
      }
    }
    break;
  case ON_SubDComponentPtr::Type::Face:
    {
      const ON_SubDFace* face = ON_SUBD_FACE_POINTER(component_ptr.m_ptr);
      if (nullptr != face && face->m_id > 0 && face->m_id < ON_UNSET_UINT_INDEX)
      {
        component_ref.m_component_ptr = component_ptr;
        component_ref.m_component_index.Set(ON_COMPONENT_INDEX::TYPE::subd_face,(int)face->m_id);
        component_ref.m_component_location = component_location;
        bValidInput = true;
      }
    }
    break;
  default:
    if ( component_ptr.IsNull() )
      bValidInput = true;
  }

  if (bValidInput)
  {
    return component_ref;
  }

  return ON_SUBD_RETURN_ERROR(component_ref);
}

const ON_SubDComponentRef ON_SubDComponentRef::Create(
  const ON_SubDRef& subd_ref,
  const class ON_SubDVertex* vertex,
  ON_SubDComponentLocation component_location,
  ON__UINT_PTR reference_id
  )
{
  return ON_SubDComponentRef::Create(subd_ref, ON_SubDComponentPtr::Create(vertex),component_location,reference_id);
}

const ON_SubDComponentRef ON_SubDComponentRef::Create(
  const ON_SubDRef& subd_ref,
  const class ON_SubDEdge* edge,
  ON_SubDComponentLocation component_location,
  ON__UINT_PTR reference_id
  )
{
  return ON_SubDComponentRef::Create(subd_ref, ON_SubDComponentPtr::Create(edge),component_location,reference_id);
}

const ON_SubDComponentRef ON_SubDComponentRef::Create(
  const ON_SubDRef& subd_ref,
  const class ON_SubDFace* face,
  ON_SubDComponentLocation component_location,
  ON__UINT_PTR reference_id
  )
{
  return ON_SubDComponentRef::Create(subd_ref, ON_SubDComponentPtr::Create(face),component_location,reference_id);
}

void ON_SubDComponentRef::Clear()
{
  ON_Geometry::DestroyRuntimeCache();
  PurgeUserData();
  m_subd_ref.Clear();
  m_component_ptr = ON_SubDComponentPtr::Null;
  m_component_index = ON_COMPONENT_INDEX::UnsetComponentIndex;
  m_reference_id = 0;
}

ON_SubDRef ON_SubDComponentRef::SubDRef() const
{
  return m_subd_ref;
}

const class ON_SubD& ON_SubDComponentRef::SubD() const
{
  return m_subd_ref.SubD();
}

ON_COMPONENT_INDEX ON_SubDComponentRef::ComponentIndex() const
{
  return m_component_index;
}

ON_SubDComponentPtr ON_SubDComponentRef::ComponentPtr() const
{
  return m_component_ptr;
}

ON_SubDComponentLocation ON_SubDComponentRef::ComponentLocation() const
{
  return m_component_location;
}

const class ON_SubDVertex* ON_SubDComponentRef::Vertex() const
{
  return m_component_ptr.Vertex();
}

const class ON_SubDEdge* ON_SubDComponentRef::Edge() const
{
  return m_component_ptr.Edge();
}

const class ON_SubDFace* ON_SubDComponentRef::Face() const
{
  return m_component_ptr.Face();
}

ON__UINT_PTR ON_SubDComponentRef::ReferenceId() const
{
  return m_reference_id;
}

void ON_SubDComponentRef::SetReferenceId(
  ON__UINT_PTR reference_id
)
{
  m_reference_id = reference_id;
}

bool ON_SubDComponentRef::IsValid(ON_TextLog* text_log) const
{
  return (
    m_component_ptr.IsNotNull() 
    && (ON_SubDComponentLocation::ControlNet == m_component_location || ON_SubDComponentLocation::Surface == m_component_location)
    && false == SubD().IsEmpty()
    );
}

void ON_SubDComponentRef::Dump(ON_TextLog& text_log) const
{
  return;
}

unsigned int ON_SubDComponentRef::SizeOf() const
{
  size_t sz = ON_Geometry::SizeOf() + sizeof(*this) - sizeof(ON_Geometry);
  return (unsigned int)sz;
}

ON::object_type ON_SubDComponentRef::ObjectType() const
{
  return ON::object_type::subd_object;
}

// overrides of virtual ON_Geometry functions
int ON_SubDComponentRef::Dimension() const
{
  return 3;
}

bool ON_SubDComponentRef::GetBBox(
  double* boxmin,
  double* boxmax,
  bool bGrowBox
  ) const
{
  if ( nullptr == boxmin || nullptr == boxmax )
    return false;

  ON_BoundingBox bbox = ON_BoundingBox::EmptyBoundingBox;

  switch (m_component_ptr.ComponentType())
  {
      case ON_SubDComponentPtr::Type::Unset:
        break;
      
      case ON_SubDComponentPtr::Type::Vertex:
    {
      const ON_SubDVertex* vertex = m_component_ptr.Vertex();
      if ( nullptr == vertex )
        break;
      switch (m_component_location)
      {
      case ON_SubDComponentLocation::Surface:
        // public opennurbs does not provide limit mesh tools.
      case ON_SubDComponentLocation::ControlNet:
        bbox = vertex->ControlNetBoundingBox();
        break;
              
      case ON_SubDComponentLocation::Unset:
        break;
      }
    }
    break;
  case ON_SubDComponentPtr::Type::Edge:
    {
      const ON_SubDEdge* edge = m_component_ptr.Edge();
      if ( nullptr == edge )
        break;
      switch (m_component_location)
      {
      case ON_SubDComponentLocation::Surface:
        // public opennurbs does not provide limit mesh tools.
      case ON_SubDComponentLocation::ControlNet:
        bbox = edge->ControlNetBoundingBox();
        break;
      case ON_SubDComponentLocation::Unset:
        break;
      }
    }
    break;
  case ON_SubDComponentPtr::Type::Face:
    {
      const ON_SubDFace* face = m_component_ptr.Face();
      if ( nullptr == face )
        break;
      switch (m_component_location)
      {
      case ON_SubDComponentLocation::Surface:
        // public opennurbs does not provide limit mesh tools.
      case ON_SubDComponentLocation::ControlNet:
        bbox = face->ControlNetBoundingBox();
        break;
      case ON_SubDComponentLocation::Unset:
        break;
      }
    }
    break;
  }

  if (bGrowBox)
  {
    ON_BoundingBox bbox1;
    bbox1.m_min = boxmin;
    bbox1.m_max = boxmax;
    if (bbox1.IsValid())
      bbox.Union(bbox1);
  }

  boxmin[0] = bbox.m_min.x;
  boxmin[1] = bbox.m_min.y;
  boxmin[2] = bbox.m_min.z;

  boxmax[0] = bbox.m_max.x;
  boxmax[1] = bbox.m_max.y;
  boxmax[2] = bbox.m_max.z;

  return bbox.IsValid();
}


void ON_SubDComponentRefList::Internal_Destroy()
{
  for (unsigned int i = 0; i < m_list.UnsignedCount(); i++)
  {
    ON_SubDComponentRef* p = m_list[i];
    m_list[i] = nullptr;
    if (nullptr != p)
      delete p;
  }
  m_list.SetCount(0);
  m_bIsClean = false;
}

void ON_SubDComponentRefList::Internal_CopyFrom(const ON_SubDComponentRefList& src)
{
  const unsigned int count = src.m_list.UnsignedCount();
  m_list.Reserve(count);
  m_list.SetCount(0);
  for (unsigned int i = 0; i < count; i++)
  {
    const ON_SubDComponentRef* p = src.m_list[i];
    if (nullptr == p)
      m_list.Append(nullptr);
    else
      m_list.Append(new ON_SubDComponentRef(*p));

    m_subd_count = src.m_subd_count;
    m_subd_vertex_smooth_count = src.m_subd_vertex_smooth_count;
    m_subd_vertex_dart_count = src.m_subd_vertex_dart_count;
    m_subd_vertex_crease_count = src.m_subd_vertex_crease_count;
    m_subd_vertex_corner_count = src.m_subd_vertex_corner_count;
    m_subd_edge_smooth_count = src.m_subd_edge_smooth_count;
    m_subd_edge_crease_count = src.m_subd_edge_crease_count;
    m_subd_face_count = src.m_subd_face_count;

    m_bIsClean = src.m_bIsClean;
  }
}

ON_SubDComponentRefList::~ON_SubDComponentRefList()
{
  Internal_Destroy();
}

ON_SubDComponentRefList::ON_SubDComponentRefList(const ON_SubDComponentRefList& src)
{
  Internal_CopyFrom(src);
}

ON_SubDComponentRefList& ON_SubDComponentRefList::operator=(const ON_SubDComponentRefList& src)
{
  if (this != &src)
  {
    Internal_Destroy();
    Internal_CopyFrom(src);
  }
  return *this;
}

bool ON_SubDComponentRefList::Internal_UpdateCount(const ON_SubDComponentRef& r, int i)
{
  if (r.SubD().IsEmpty())
    return false;

  bool rc = false;
  ON_SubDComponentPtr cptr = r.ComponentPtr();
  switch (cptr.ComponentType())
  {
      case ON_SubDComponentPtr::Type::Unset:
        break;
          
      case ON_SubDComponentPtr::Type::Vertex:
    {
      const ON_SubDVertex* v = cptr.Vertex();
      if (nullptr == v)
        break;
      switch (v->m_vertex_tag)
      {
      case ON_SubDVertexTag::Smooth:
        m_subd_vertex_smooth_count += i;
        rc = true;
        break;
      case ON_SubDVertexTag::Crease:
        m_subd_vertex_crease_count += i;
        rc = true;
        break;
      case ON_SubDVertexTag::Corner:
        m_subd_vertex_corner_count += i;
        rc = true;
        break;
      case ON_SubDVertexTag::Dart:
        m_subd_vertex_dart_count += i;
        rc = true;
        break;
      case ON_SubDVertexTag::Unset:
        break;
      }
    }
    break;

  case ON_SubDComponentPtr::Type::Edge:
    {
      const ON_SubDEdge* e = cptr.Edge();
      if (nullptr == e)
        break;
      switch (e->m_edge_tag)
      {
      case ON_SubDEdgeTag::Smooth:
      case ON_SubDEdgeTag::SmoothX:
        m_subd_edge_smooth_count += i;
        rc = true;
        break;
      case ON_SubDEdgeTag::Crease:
        m_subd_edge_crease_count += i;
        rc = true;
        break;
      case ON_SubDEdgeTag::Unset:
        break;
      }
    }
    break;

  case ON_SubDComponentPtr::Type::Face:
    if (nullptr != cptr.Face())
    {
      m_subd_face_count += i;
      rc = true;
    }
    break;
  }

  return rc;
}

const ON_SubDComponentRef& ON_SubDComponentRefList::Append(
  const ON_SubDRef & subd_ref,
  ON_COMPONENT_INDEX ci, 
  ON_SubDComponentLocation component_location,
  ON__UINT_PTR reference_id
  )
{
  for (;;)
  {
    if (subd_ref.SubD().IsEmpty())
      break;
    if (false == ci.IsSubDComponentIndex())
      break;
    const ON_SubDComponentRef r(ON_SubDComponentRef::Create(subd_ref, ci, component_location, reference_id));
    return Append(&r);
  }
  return ON_SubDComponentRef::Empty;
}

const ON_SubDComponentRef& ON_SubDComponentRefList::Append(
  const ON_SubDRef & subd_ref, 
  ON_SubDComponentPtr component_ptr, 
  ON_SubDComponentLocation component_location,
  ON__UINT_PTR reference_id
)
{
  for (;;)
  {
    if (subd_ref.SubD().IsEmpty())
      break;
    if (false == component_ptr.IsNull())
      break;
    const ON_SubDComponentRef r(ON_SubDComponentRef::Create(subd_ref, component_ptr, component_location,reference_id));
    return Append(&r);
  }
  return ON_SubDComponentRef::Empty;
}

const ON_SubDComponentRef& ON_SubDComponentRefList::Append(const ON_SubDComponentRef& src_ref)
{
  return Append(&src_ref);
}

const ON_SubDComponentRef& ON_SubDComponentRefList::Append(const ON_SubDComponentRef* src_ref)
{
  for (;;)
  {
    if (nullptr == src_ref)
      break;
    if (src_ref->SubD().IsEmpty())
      break;
    if (false == Internal_UpdateCount(*src_ref,1))
      break;
    m_list.Append(new ON_SubDComponentRef(*src_ref));
    m_bIsClean = false;
    return **(m_list.Last());
  }
  return ON_SubDComponentRef::Empty;
}

const ON_SubDComponentRef& ON_SubDComponentRefList::AppendForExperts(ON_SubDComponentRef*& ref)
{
  for (;;)
  {
    if (nullptr == ref)
      break;
    if (ref->SubD().IsEmpty())
      break;
    if (false == Internal_UpdateCount(*ref,1))
      break;
    m_list.Append(ref);
    m_bIsClean = false;
    return *ref;
  }
  return ON_SubDComponentRef::Empty;
}

const ON_SubDComponentRef& ON_SubDComponentRefList::AppendForExperts(
  const ON_SubD& subd,
  ON_COMPONENT_INDEX ci,
  ON_SubDComponentLocation component_location,
  ON__UINT_PTR reference_id
)
{
  for (;;)
  {
    if (subd.IsEmpty())
      break;
    return Append(ON_SubDRef::CreateReferenceForExperts(subd),ci,component_location,reference_id);
  }
  return ON_SubDComponentRef::Empty;
}

const ON_SubDComponentRef& ON_SubDComponentRefList::AppendForExperts(
  const ON_SubD& subd,
  ON_SubDComponentPtr component_ptr,
  ON_SubDComponentLocation component_location,
  ON__UINT_PTR reference_id
)
{
  for (;;)
  {
    if (subd.IsEmpty())
      break;
    return Append(ON_SubDRef::CreateReferenceForExperts(subd),component_ptr,component_location,reference_id);
  }
  return ON_SubDComponentRef::Empty;
}


int ON_SubDComponentRefList::Clean()
{
  if (m_bIsClean)
    return m_list.UnsignedCount();

  const unsigned dirty_count = m_list.UnsignedCount();

  ((ON_SimpleArray< const ON_SubDComponentRef* > *)(&m_list))->QuickSort(ON_SubDComponentRef::Compare2);

  m_subd_count = 0;
  m_subd_vertex_smooth_count = 0;
  m_subd_vertex_dart_count = 0;
  m_subd_vertex_crease_count = 0;
  m_subd_vertex_corner_count = 0;
  m_subd_edge_smooth_count = 0;
  m_subd_edge_crease_count = 0;
  m_subd_face_count = 0;

  unsigned int clean_count = 0;
  const ON_SubDComponentRef* prev_scr = nullptr;
  for (unsigned int i = 0; i < dirty_count; i++)
  {
    ON_SubDComponentRef* scr = m_list[i];
    if (nullptr == scr)
      continue;
    if (
      0 == ON_SubDComponentRef::Compare(prev_scr, scr)
      || false == Internal_UpdateCount(*scr,1)
      )
    {
      delete scr;
      continue;
    }
    if (nullptr == prev_scr || prev_scr->SubD().RuntimeSerialNumber() != scr->SubD().RuntimeSerialNumber())
      m_subd_count++;
    m_list[clean_count++] = scr;
    prev_scr = scr;
  }
  for (unsigned i = clean_count; i < dirty_count; i++)
    m_list[i] = nullptr;
  m_list.SetCount(clean_count);
  m_bIsClean = true;
  return clean_count;
}

int ON_SubDComponentRefList::Count() const
{
  return m_list.Count();
}

void ON_SubDComponentRefList::Remove(int i)
{
  ON_SubDComponentRef* p = TransferForExperts(i);
  if (nullptr != p)
    delete p;
}

ON_SubDComponentRef * ON_SubDComponentRefList::TransferForExperts(int i)
{
  ON_SubDComponentRef * p = (i >= 0 && i < m_list.Count()) ? m_list[i] : nullptr;
  if (p != nullptr)
  {
    Internal_UpdateCount(*p, -1);
    m_bIsClean = false;
  }
  return p;
}

const ON_SubDComponentRef& ON_SubDComponentRefList::operator[](int i) const
{
  const ON_SubDComponentRef * p = (i >= 0 && i < m_list.Count()) ? m_list[i] : nullptr;
  return (nullptr == p) ? ON_SubDComponentRef::Empty : *p;
}

int ON_SubDComponentRefList::SubDCount() const
{
  return m_bIsClean ? m_subd_count : 0;
}

int ON_SubDComponentRefList::VertexCount() const
{
  return
    m_subd_vertex_smooth_count
    + m_subd_vertex_dart_count
    + m_subd_vertex_crease_count
    + m_subd_vertex_corner_count;
}

int ON_SubDComponentRefList::VertexCount(ON_SubDVertexTag vertex_tag) const
{
  int c = 0;
  switch (vertex_tag)
  {
  case ON_SubDVertexTag::Smooth:
    c = m_subd_vertex_smooth_count;
    break;
  case ON_SubDVertexTag::Crease:
    c = m_subd_vertex_crease_count;
    break;
  case ON_SubDVertexTag::Corner:
    c = m_subd_vertex_corner_count;
    break;
  case ON_SubDVertexTag::Dart:
    c = m_subd_vertex_dart_count;
    break;
  case ON_SubDVertexTag::Unset:
    break;
  }

  return c;
}

int ON_SubDComponentRefList::EdgeCount() const
{
  return m_subd_edge_crease_count + m_subd_edge_smooth_count;
}

int ON_SubDComponentRefList::EdgeCount(ON_SubDEdgeTag edge_tag) const
{
  int c = 0;
  switch (edge_tag)
  {
  case ON_SubDEdgeTag::Unset:
    break;
  case ON_SubDEdgeTag::Smooth:
    c = m_subd_edge_smooth_count;
    break;
  case ON_SubDEdgeTag::Crease:
    c = m_subd_edge_crease_count;
    break;
  case ON_SubDEdgeTag::SmoothX:
    break;
  }
  return c;
}

int ON_SubDComponentRefList::FaceCount() const
{
  return m_subd_face_count;
}

int ON_SubDComponentRefList::ComponentCount() const
{
  return m_list.Count();
}
