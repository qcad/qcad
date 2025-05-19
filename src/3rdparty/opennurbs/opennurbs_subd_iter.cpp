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
// ON_SubDVertexArray
//
ON_SubDVertexArray::ON_SubDVertexArray(
  const class ON_SubD& subd
  )
{
  m_subd.ShareDimple(subd);
  unsigned int vertex_count = subd.VertexCount();
  if (vertex_count > 0)
  {
    m_sp = subd.ActiveLevel().VertexArray();
    m_a = m_sp.get();
    if (nullptr != m_a)
      m_vertex_count = vertex_count;
  }
}

#if defined(ON_HAS_RVALUEREF)
// rvalue copy constructor
ON_SubDVertexArray::ON_SubDVertexArray(ON_SubDVertexArray&& src) ON_NOEXCEPT
  : m_a(src.m_a)
  , m_vertex_count(src.m_vertex_count)
  , m_sp(std::move(src.m_sp))
{
  m_subd.SwapDimple(src.m_subd);
  src.m_subd.Destroy();
}

// The rvalue assignment operator calls ON_Object::operator=(ON_Object&&)
// which could throw exceptions.  See the implementation of
// ON_Object::operator=(ON_Object&&) for details.
ON_SubDVertexArray& ON_SubDVertexArray::operator=(ON_SubDVertexArray&& src)
{
  if (this != &src)
  {
    m_a = src.m_a;
    m_subd.SwapDimple(src.m_subd);
    m_vertex_count = src.m_vertex_count;
    m_sp = std::move(src.m_sp);
    src.m_subd.Destroy();
  }
  return *this;
}
#endif


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDEdgeArray
//
ON_SubDEdgeArray::ON_SubDEdgeArray(
  const class ON_SubD& subd
  )
{
  m_subd.ShareDimple(subd);
  unsigned int edge_count = subd.EdgeCount();
  if (edge_count > 0)
  {
    m_sp = subd.ActiveLevel().EdgeArray();
    m_a = m_sp.get();
    if (nullptr != m_a)
      m_edge_count = edge_count;
  }
}

#if defined(ON_HAS_RVALUEREF)
// rvalue copy constructor
ON_SubDEdgeArray::ON_SubDEdgeArray(ON_SubDEdgeArray&& src) ON_NOEXCEPT
  : m_a(src.m_a)
  , m_edge_count(src.m_edge_count)
  , m_sp(std::move(src.m_sp))
{
  m_subd.SwapDimple(src.m_subd);
  src.m_subd.Destroy();
}

// The rvalue assignment operator calls ON_Object::operator=(ON_Object&&)
// which could throw exceptions.  See the implementation of
// ON_Object::operator=(ON_Object&&) for details.
ON_SubDEdgeArray& ON_SubDEdgeArray::operator=(ON_SubDEdgeArray&& src)
{
  if (this != &src)
  {
    m_a = src.m_a;
    m_subd.SwapDimple(src.m_subd);
    m_edge_count = src.m_edge_count;
    m_sp = std::move(src.m_sp);
    src.m_subd.Destroy();
  }
  return *this;
}
#endif

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFaceArray
//
ON_SubDFaceArray::ON_SubDFaceArray(
  const class ON_SubD& subd
  )
{
  m_subd.ShareDimple(subd);
  unsigned int face_count = subd.FaceCount();
  if (face_count > 0)
  {
    m_sp = subd.ActiveLevel().FaceArray();
    m_a = m_sp.get();
    if (nullptr != m_a)
      m_face_count = face_count;
  }
}

#if defined(ON_HAS_RVALUEREF)
// rvalue copy constructor
ON_SubDFaceArray::ON_SubDFaceArray(ON_SubDFaceArray&& src) ON_NOEXCEPT
  : m_a(src.m_a)
  , m_face_count(src.m_face_count)
  , m_sp(std::move(src.m_sp))
{
  m_subd.SwapDimple(src.m_subd);
  src.m_subd.Destroy();
}

// The rvalue assignment operator calls ON_Object::operator=(ON_Object&&)
// which could throw exceptions.  See the implementation of
// ON_Object::operator=(ON_Object&&) for details.
ON_SubDFaceArray& ON_SubDFaceArray::operator=(ON_SubDFaceArray&& src)
{
  if (this != &src)
  {
    m_a = src.m_a;
    m_subd.SwapDimple(src.m_subd);
    m_face_count = src.m_face_count;
    m_sp = std::move(src.m_sp);
    src.m_subd.Destroy();
  }
  return *this;
}
#endif

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentIdIterator
//

void ON_SubDHeap::InitializeComponentIdIterator(
  ON_SubDComponentPtr::Type ctype,
  class ON_SubDComponentIdIterator& cidit
) const
{
  switch (ctype)
  {
  case ON_SubDComponentPtr::Type::Vertex:
    cidit.m_component_type = ctype;
    cidit.ON_FixedSizePoolIterator::Create(&m_fspv);
    break;

  case ON_SubDComponentPtr::Type::Edge:
    cidit.m_component_type = ctype;
    cidit.ON_FixedSizePoolIterator::Create(&m_fspe);
    break;

  case ON_SubDComponentPtr::Type::Face:
    cidit.m_component_type = ctype;
    cidit.ON_FixedSizePoolIterator::Create(&m_fspf);
    break;

  default:
    ON_SUBD_ERROR("Invalid ctype");
    break;
  }
}

void ON_SubDimple::InitializeComponentIdIterator(
  ON_SubDComponentPtr::Type ctype, 
  ON_SubDComponentIdIterator & cidit
) const
{
  m_heap.InitializeComponentIdIterator(ctype, cidit);
}

const ON_SubDComponentBase* ON_SubDComponentIdIterator::FirstComponent()
{
  for (const ON_SubDComponentBase* c = (const ON_SubDComponentBase*)FirstElement(); nullptr != c; c = (const ON_SubDComponentBase*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&c->m_id)[1])
      return c;
  }
  return nullptr;
}

const ON_SubDComponentBase* ON_SubDComponentIdIterator::NextComponent()
{
  for (const ON_SubDComponentBase* c = (const ON_SubDComponentBase*)NextElement(); nullptr != c; c = (const ON_SubDComponentBase*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&c->m_id)[1])
      return c;
  }
  return nullptr;
}

const ON_SubDComponentBase* ON_SubDComponentIdIterator::CurrentComponent() const
{
  return (const ON_SubDComponentBase*)CurrentElement();
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDVertexIterator
//

void ON_SubDHeap::InitializeVertexIdIterator(
  class ON_SubDVertexIdIterator& vidit
) const
{
  vidit.ON_FixedSizePoolIterator::Create(&m_fspv);
}

void ON_SubDimple::InitializeVertexIdIterator(
  class ON_SubDVertexIdIterator& vidit
) const
{
  m_heap.InitializeVertexIdIterator(vidit);
}

void ON_SubDVertexIdIterator::Internal_Init()
{
  const ON_SubDimple* subdimple = m_subd_ref.SubD().SubDimple();
  if (nullptr != subdimple)
    subdimple->InitializeVertexIdIterator(*this);
}

ON_SubDVertexIdIterator::ON_SubDVertexIdIterator(const ON_SubDRef& subd_ref)
  : m_subd_ref(subd_ref)
{
  Internal_Init();
}

ON_SubDVertexIdIterator::ON_SubDVertexIdIterator(const ON_SubD& subd)
  : m_subd_ref(ON_SubDRef::CreateReferenceForExperts(subd))
{
  Internal_Init();
}

const ON_SubDVertex* ON_SubDVertexIdIterator::FirstVertex()
{
  for (const ON_SubDVertex* v = (const ON_SubDVertex*)FirstElement(); nullptr != v; v = (const ON_SubDVertex*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&v->m_id)[1])
      return v;
  }
  return nullptr;
}

const ON_SubDVertex* ON_SubDVertexIdIterator::NextVertex()
{
  for (const ON_SubDVertex* v = (const ON_SubDVertex*)NextElement(); nullptr != v; v = (const ON_SubDVertex*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&v->m_id)[1])
      return v;
  }
  return nullptr;
}


const ON_SubDVertex* ON_SubDVertexIdIterator::FirstVertexOnLevel(unsigned int level_index)
{
  for (const ON_SubDVertex* v = (const ON_SubDVertex*)FirstElement(); nullptr != v; v = (const ON_SubDVertex*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&v->m_id)[1] && level_index == v->SubdivisionLevel())
      return v;
  }
  return nullptr;
}

const ON_SubDVertex* ON_SubDVertexIdIterator::NextVertexOnLevel(unsigned int level_index)
{
  for (const ON_SubDVertex* v = (const ON_SubDVertex*)NextElement(); nullptr != v; v = (const ON_SubDVertex*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&v->m_id)[1] && level_index == v->SubdivisionLevel())
      return v;
  }
  return nullptr;
}

const ON_SubDVertex* ON_SubDVertexIdIterator::CurrentVertex() const
{
  return (const ON_SubDVertex*)CurrentElement();
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDEdgeIterator
//

void ON_SubDHeap::InitializeEdgeIdIterator(
  class ON_SubDEdgeIdIterator& eidit
) const
{
  eidit.ON_FixedSizePoolIterator::Create(&m_fspe);
}

void ON_SubDimple::InitializeEdgeIdIterator(
  class ON_SubDEdgeIdIterator& eidit
) const
{
  m_heap.InitializeEdgeIdIterator(eidit);
}

void ON_SubDEdgeIdIterator::Internal_Init()
{
  const ON_SubDimple* subdimple = m_subd_ref.SubD().SubDimple();
  if (nullptr != subdimple)
    subdimple->InitializeEdgeIdIterator(*this);
}

ON_SubDEdgeIdIterator::ON_SubDEdgeIdIterator(const ON_SubDRef& subd_ref)
  : m_subd_ref(subd_ref)
{
  Internal_Init();
}

ON_SubDEdgeIdIterator::ON_SubDEdgeIdIterator(const ON_SubD& subd)
  : m_subd_ref(ON_SubDRef::CreateReferenceForExperts(subd))
{
  Internal_Init();
}

const ON_SubDEdge* ON_SubDEdgeIdIterator::FirstEdge()
{
  for (const ON_SubDEdge* e = (const ON_SubDEdge*)FirstElement(); nullptr != e; e = (const ON_SubDEdge*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&e->m_id)[1])
      return e;
  }
  return nullptr;
}

const ON_SubDEdge* ON_SubDEdgeIdIterator::NextEdge()
{
  for (const ON_SubDEdge* e = (const ON_SubDEdge*)NextElement(); nullptr != e; e = (const ON_SubDEdge*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&e->m_id)[1])
      return e;
  }
  return nullptr;
}

const ON_SubDEdge* ON_SubDEdgeIdIterator::FirstEdgeOnLevel(unsigned int level_index)
{
  for (const ON_SubDEdge* e = (const ON_SubDEdge*)FirstElement(); nullptr != e; e = (const ON_SubDEdge*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&e->m_id)[1] && level_index == e->SubdivisionLevel())
      return e;
  }
  return nullptr;
}

const ON_SubDEdge* ON_SubDEdgeIdIterator::NextEdgeOnLevel(unsigned int level_index)
{
  for (const ON_SubDEdge* e = (const ON_SubDEdge*)NextElement(); nullptr != e; e = (const ON_SubDEdge*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&e->m_id)[1] && level_index == e->SubdivisionLevel())
      return e;
  }
  return nullptr;
}

const ON_SubDEdge* ON_SubDEdgeIdIterator::CurrentEdge() const
{
  return (const ON_SubDEdge*)CurrentElement();
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFaceIterator
//

void ON_SubDHeap::InitializeFaceIdIterator(
  class ON_SubDFaceIdIterator& fidit
) const
{
  fidit.ON_FixedSizePoolIterator::Create(&m_fspf);
}

void ON_SubDimple::InitializeFaceIdIterator(
  class ON_SubDFaceIdIterator& fidit
) const
{
  m_heap.InitializeFaceIdIterator(fidit);
}

void ON_SubDFaceIdIterator::Internal_Init()
{
  const ON_SubDimple* subdimple = m_subd_ref.SubD().SubDimple();
  if (nullptr != subdimple)
    subdimple->InitializeFaceIdIterator(*this);
}

ON_SubDFaceIdIterator::ON_SubDFaceIdIterator(const ON_SubDRef& subd_ref)
  : m_subd_ref(subd_ref)
{
  Internal_Init();
}

ON_SubDFaceIdIterator::ON_SubDFaceIdIterator(const ON_SubD& subd)
  : m_subd_ref(ON_SubDRef::CreateReferenceForExperts(subd))
{
  Internal_Init();
}

const ON_SubDFace* ON_SubDFaceIdIterator::FirstFace()
{
  for (const ON_SubDFace* f = (const ON_SubDFace*)FirstElement(); nullptr != f; f = (const ON_SubDFace*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&f->m_id)[1])
      return f;
  }
  return nullptr;
}

const ON_SubDFace* ON_SubDFaceIdIterator::NextFace()
{
  for (const ON_SubDFace* f = (const ON_SubDFace*)NextElement(); nullptr != f; f = (const ON_SubDFace*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&f->m_id)[1])
      return f;
  }
  return nullptr;
}

const ON_SubDFace* ON_SubDFaceIdIterator::FirstFaceOnLevel(unsigned int level_index)
{
  for (const ON_SubDFace* f = (const ON_SubDFace*)FirstElement(); nullptr != f; f = (const ON_SubDFace*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&f->m_id)[1] && level_index == f->SubdivisionLevel())
      return f;
  }
  return nullptr;
}

const ON_SubDFace* ON_SubDFaceIdIterator::NextFaceOnLevel(unsigned int level_index)
{
  for (const ON_SubDFace* f = (const ON_SubDFace*)NextElement(); nullptr != f; f = (const ON_SubDFace*)NextElement())
  {
    if (ON_UNSET_UINT_INDEX != (&f->m_id)[1] && level_index == f->SubdivisionLevel())
      return f;
  }
  return nullptr;
}


const ON_SubDFace* ON_SubDFaceIdIterator::CurrentFace() const
{
  return (const ON_SubDFace*)CurrentElement();
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDVertexIterator
//

void ON_SubDVertexIterator::Internal_Init(
  const ON_SubDRef& subd_ref,
  unsigned int vertex_count,
  const ON_SubDVertex* first,
  const ON_SubDVertex* last,
  ON_SubDComponentPtr component_ptr
)
{
  m_subd_ref = subd_ref;
  if (nullptr != first && nullptr != last && vertex_count > 0)
  {
    m_v_first = first;
    m_v_last = last;
    m_v_current = m_v_first;
    m_vertex_count = vertex_count;
    m_component_ptr
      = (ON_SubDComponentPtr::Type::Unset == component_ptr.ComponentType())
      ? ON_SubDComponentPtr::Null
      : component_ptr;
  }
}

ON_SubDVertexIterator::ON_SubDVertexIterator(
  const class ON_SubD& subd
  )
{
  const ON_SubDLevel& level = subd.ActiveLevel();
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    level.m_vertex_count,
    level.m_vertex[0],
    level.m_vertex[1],
    ON_SubDComponentPtr::Null
  );
}


ON_SubDVertexIterator::ON_SubDVertexIterator(
  const class ON_SubD& subd,
  unsigned level_index

)
{
  const ON_SubDLevel& level = subd.LevelForExperts(level_index);
    Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    level.m_vertex_count,
    level.m_vertex[0],
    level.m_vertex[1],
    ON_SubDComponentPtr::Null
  );
}


ON_SubDVertexIterator::ON_SubDVertexIterator(
  const class ON_SubDRef& subd_ref
  )
{
  const ON_SubDLevel& level = subd_ref.SubD().ActiveLevel();
  Internal_Init(
    subd_ref,
    level.m_vertex_count,
    level.m_vertex[0],
    level.m_vertex[1],
    ON_SubDComponentPtr::Null
  );
}

ON_SubDVertexIterator::ON_SubDVertexIterator(
  const ON_SubD& subd,
  const ON_SubDVertex& vertex
  )
{
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    1,
    &vertex,
    &vertex,
    ON_SubDComponentPtr::Null
  );
}

ON_SubDVertexIterator::ON_SubDVertexIterator(
  const ON_SubDRef& subd_ref,
  const ON_SubDVertex& vertex
  )
{
  Internal_Init(
    subd_ref,
    1,
    &vertex,
    &vertex,
    ON_SubDComponentPtr::Null
  );
}

ON_SubDVertexIterator::ON_SubDVertexIterator(
  const class ON_SubD& subd,
  const class ON_SubDEdge& edge
  )
{
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    2,
    edge.Vertex(0),
    edge.Vertex(1),
    ON_SubDComponentPtr::Create(&edge)
  );
}

ON_SubDVertexIterator::ON_SubDVertexIterator(
  const class ON_SubDRef& subd_ref,
  const class ON_SubDEdge& edge
)
{
  Internal_Init(
    subd_ref,
    2,
    edge.Vertex(0),
    edge.Vertex(1),
    ON_SubDComponentPtr::Create(&edge)
  );
}

ON_SubDVertexIterator::ON_SubDVertexIterator(
  const class ON_SubD& subd,
  const class ON_SubDFace& face
)
{
  const unsigned int vertex_count = face.EdgeCount();
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    vertex_count,
    face.Vertex(0),
    face.Vertex(vertex_count-1),
    ON_SubDComponentPtr::Create(&face)    
  );
}

ON_SubDVertexIterator::ON_SubDVertexIterator(
  const class ON_SubDRef& subd_ref,
  const class ON_SubDFace& face
)
{
  const unsigned int vertex_count = face.EdgeCount();
  Internal_Init(
    subd_ref,
    vertex_count,
    face.Vertex(0),
    face.Vertex(vertex_count-1),
    ON_SubDComponentPtr::Create(&face)    
  );
}

#if defined(ON_HAS_RVALUEREF)
// rvalue copy constructor
ON_SubDVertexIterator::ON_SubDVertexIterator( ON_SubDVertexIterator&& src) ON_NOEXCEPT
  : m_subd_ref(std::move(src.m_subd_ref))
  , m_v_first(src.m_v_first)
  , m_v_last(src.m_v_last)
  , m_v_current(src.m_v_current)
  , m_vertex_index(src.m_vertex_index)
  , m_vertex_count(src.m_vertex_count)
  , m_component_ptr(src.m_component_ptr)
{}

// rvalue assignment operator
ON_SubDVertexIterator& ON_SubDVertexIterator::operator=(ON_SubDVertexIterator&& src)
{
  m_subd_ref.Clear();
  m_subd_ref = std::move(src.m_subd_ref);
  m_v_first = src.m_v_first;
  m_v_last = src.m_v_last;
  m_v_current = src.m_v_current;
  m_vertex_index = src.m_vertex_index;
  m_vertex_count = src.m_vertex_count;
  m_component_ptr = src.m_component_ptr;
  return *this;
}
#endif

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDEdgeIterator
//
void ON_SubDEdgeIterator::Internal_Init(
  const ON_SubDRef& subd_ref,
  unsigned int edge_count,
  const ON_SubDEdge* first,
  const ON_SubDEdge* last,
  ON_SubDComponentPtr component_ptr
)
{
  m_subd_ref = subd_ref;
  if (nullptr != first && nullptr != last && edge_count > 0)
  {
    m_e_first = first;
    m_e_last = last;
    m_e_current = m_e_first;
    m_edge_count = edge_count;
    m_component_ptr
      = (ON_SubDComponentPtr::Type::Unset == component_ptr.ComponentType())
      ? ON_SubDComponentPtr::Null
      : component_ptr;
  }
}

ON_SubDEdgeIterator::ON_SubDEdgeIterator(
  const class ON_SubD& subd
  )
{
  const ON_SubDLevel& level = subd.ActiveLevel();
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    level.m_edge_count,
    level.m_edge[0],
    level.m_edge[1],
    ON_SubDComponentPtr::Null
  );
}

ON_SubDEdgeIterator::ON_SubDEdgeIterator(
  const class ON_SubD& subd,
  unsigned level_index
)
{
  const ON_SubDLevel& level = subd.LevelForExperts(level_index);
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    level.m_edge_count,
    level.m_edge[0],
    level.m_edge[1],
    ON_SubDComponentPtr::Null
  );
}

ON_SubDEdgeIterator::ON_SubDEdgeIterator(
  const class ON_SubDRef& subd_ref
  )
{
  const ON_SubDLevel& level = subd_ref.SubD().ActiveLevel();
  Internal_Init(
    subd_ref,
    level.m_edge_count,
    level.m_edge[0],
    level.m_edge[1],
    ON_SubDComponentPtr::Null
  );
}


ON_SubDEdgeIterator::ON_SubDEdgeIterator(
  const ON_SubD& subd,
  const ON_SubDEdge& edge
  )
{
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    1,
    &edge,
    &edge,
    ON_SubDComponentPtr::Null
  );
}

ON_SubDEdgeIterator::ON_SubDEdgeIterator(
  const ON_SubDRef& subd_ref,
  const ON_SubDEdge& edge
  )
{
  Internal_Init(
    subd_ref,
    1,
    &edge,
    &edge,
    ON_SubDComponentPtr::Null
  );
}

ON_SubDEdgeIterator::ON_SubDEdgeIterator(
  const class ON_SubD& subd,
  const class ON_SubDVertex& vertex
  )
{
  const unsigned int edge_count = vertex.EdgeCount();
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    edge_count,
    vertex.Edge(0),
    vertex.Edge(edge_count - 1),
    ON_SubDComponentPtr::Create(&vertex)
  );
}

ON_SubDEdgeIterator::ON_SubDEdgeIterator(
  const class ON_SubDRef& subd_ref,
  const class ON_SubDVertex& vertex
  )
{
  const unsigned int edge_count = vertex.EdgeCount();
  Internal_Init(
    subd_ref,
    edge_count,
    vertex.Edge(0),
    vertex.Edge(edge_count - 1),
    ON_SubDComponentPtr::Create(&vertex)
  );
}

ON_SubDEdgeIterator::ON_SubDEdgeIterator(
  const class ON_SubD& subd,
  const class ON_SubDFace& face
  )
{
  const unsigned int edge_count = face.EdgeCount();
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    edge_count,
    face.Edge(0),
    face.Edge(edge_count - 1),
    ON_SubDComponentPtr::Create(&face)
  );
}

ON_SubDEdgeIterator::ON_SubDEdgeIterator(
  const class ON_SubDRef& subd_ref,
  const class ON_SubDFace& face
  )
  : m_subd_ref(subd_ref)
{
  const unsigned int edge_count = face.EdgeCount();
  Internal_Init(
    subd_ref,
    edge_count,
    face.Edge(0),
    face.Edge(edge_count - 1),
    ON_SubDComponentPtr::Create(&face)
  );
}

#if defined(ON_HAS_RVALUEREF)
// rvalue copy constructor
ON_SubDEdgeIterator::ON_SubDEdgeIterator( ON_SubDEdgeIterator&& src) ON_NOEXCEPT
  : m_subd_ref(std::move(src.m_subd_ref))
  , m_e_first(src.m_e_first)
  , m_e_last(src.m_e_last)
  , m_e_current(src.m_e_current)
  , m_edge_index(src.m_edge_index)
  , m_edge_count(src.m_edge_count)
  , m_component_ptr(src.m_component_ptr)
{}

// rvalue assignment operator
ON_SubDEdgeIterator& ON_SubDEdgeIterator::operator=(ON_SubDEdgeIterator&& src)
{
  m_subd_ref.Clear();
  m_subd_ref = std::move(src.m_subd_ref);
  m_e_first = src.m_e_first;
  m_e_last = src.m_e_last;
  m_e_current = src.m_e_current;
  m_edge_index = src.m_edge_index;
  m_edge_count = src.m_edge_count;
  m_component_ptr = src.m_component_ptr;
  return *this;
}
#endif

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFaceIterator
//
void ON_SubDFaceIterator::Internal_Init(
  const ON_SubDRef& subd_ref,
  unsigned int face_count,
  const ON_SubDFace* first,
  const ON_SubDFace* last,
  ON_SubDComponentPtr component_ptr
)
{
  m_subd_ref = subd_ref;
  if (nullptr != first && nullptr != last && face_count > 0)
  {
    m_face_first = first;
    m_face_last = last;
    m_face_current = m_face_first;
    m_face_count = face_count;
    m_component_ptr
      = (ON_SubDComponentPtr::Type::Unset == component_ptr.ComponentType())
      ? ON_SubDComponentPtr::Null
      : component_ptr;
  }
}

ON_SubDFaceIterator::ON_SubDFaceIterator(
  const ON_SubD& subd
  )
{
  const ON_SubDLevel& level = subd.ActiveLevel();
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    level.m_face_count,
    level.m_face[0],
    level.m_face[1],
    ON_SubDComponentPtr::Null
  );
}

ON_SubDFaceIterator::ON_SubDFaceIterator(
  const class ON_SubD& subd,
  unsigned level_index

)
{
  const ON_SubDLevel& level = subd.LevelForExperts(level_index);
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    level.m_face_count,
    level.m_face[0],
    level.m_face[1],
    ON_SubDComponentPtr::Null
  );
}

ON_SubDFaceIterator::ON_SubDFaceIterator(
  const ON_SubDRef& subd_ref
  )
{
  const ON_SubDLevel& level = subd_ref.SubD().ActiveLevel();
  Internal_Init(
    subd_ref,
    level.m_face_count,
    level.m_face[0],
    level.m_face[1],
    ON_SubDComponentPtr::Null
  );
}


ON_SubDFaceIterator::ON_SubDFaceIterator(
  const ON_SubD& subd,
  const ON_SubDFace& face
  )
{
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    1,
    &face,
    &face,
    ON_SubDComponentPtr::Null
  );
}


ON_SubDFaceIterator::ON_SubDFaceIterator(
  const ON_SubDRef& subd_ref,
  const ON_SubDFace& face
  )
{
  Internal_Init(
    subd_ref,
    1,
    &face,
    &face,
    ON_SubDComponentPtr::Null
  );
}

ON_SubDFaceIterator::ON_SubDFaceIterator(
  const class ON_SubD& subd,
  const class ON_SubDVertex& vertex
)
{
  const unsigned int face_count = vertex.FaceCount();
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    face_count,
    vertex.Face(0),
    vertex.Face(face_count - 1),
    ON_SubDComponentPtr::Create(&vertex)
  );
}

ON_SubDFaceIterator::ON_SubDFaceIterator(
  const class ON_SubDRef& subd_ref,
  const class ON_SubDVertex& vertex
)
{
  const unsigned int face_count = vertex.FaceCount();
  Internal_Init(
    subd_ref,
    face_count,
    vertex.Face(0),
    vertex.Face(face_count - 1),
    ON_SubDComponentPtr::Create(&vertex)
  );
}

ON_SubDFaceIterator::ON_SubDFaceIterator(
  const class ON_SubD& subd,
  const class ON_SubDEdge& edge
)
{
  const unsigned int face_count = edge.FaceCount();
  Internal_Init(
    ON_SubDRef::CreateReferenceForExperts(subd),
    face_count,
    edge.Face(0),
    edge.Face(face_count - 1),
    ON_SubDComponentPtr::Create(&edge)
  );
}

ON_SubDFaceIterator::ON_SubDFaceIterator(
  const class ON_SubDRef& subd_ref,
  const class ON_SubDEdge& edge
)
{
  const unsigned int face_count = edge.FaceCount();
  Internal_Init(
    subd_ref,
    face_count,
    edge.Face(0),
    edge.Face(face_count - 1),
    ON_SubDComponentPtr::Create(&edge)
  );
}

#if defined(ON_HAS_RVALUEREF)
// rvalue copy constructor
ON_SubDFaceIterator::ON_SubDFaceIterator( ON_SubDFaceIterator&& src) ON_NOEXCEPT
  : m_subd_ref(std::move(src.m_subd_ref))
  , m_face_first(src.m_face_first)
  , m_face_last(src.m_face_last)
  , m_face_current(src.m_face_current)
  , m_face_index(src.m_face_index)
  , m_face_count(src.m_face_count)
  , m_component_ptr(src.m_component_ptr)
{}

// rvalue assignment operator
ON_SubDFaceIterator& ON_SubDFaceIterator::operator=(ON_SubDFaceIterator&& src)
{
  m_subd_ref.Clear();
  m_subd_ref = std::move(src.m_subd_ref);
  m_face_first = src.m_face_first;
  m_face_last = src.m_face_last;
  m_face_current = src.m_face_current;
  m_face_index = src.m_face_index;
  m_face_count = src.m_face_count;
  m_component_ptr = src.m_component_ptr;
  return *this;
}
#endif

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFaceEdgeIterator
//

ON_SubDFaceEdgeIterator::ON_SubDFaceEdgeIterator()
  : m_face(nullptr)
  , m_edge_count(0)
  , m_edge_index0(0)
  , m_edge_index(0)
{}

ON_SubDFaceEdgeIterator::ON_SubDFaceEdgeIterator(
  const ON_SubDFace* face
  )
  : m_face(nullptr)
  , m_edge_count(0)
  , m_edge_index0(0)
  , m_edge_index(0)
{
  Initialize(face, nullptr);
}

ON_SubDFaceEdgeIterator::ON_SubDFaceEdgeIterator(
  const ON_SubDFace* face,
  const ON_SubDEdge* first_edge
  )
  : m_face(nullptr)
  , m_edge_count(0)
  , m_edge_index0(0)
  , m_edge_index(0)
{
  Initialize(face, first_edge);
}

unsigned int ON_SubDFaceEdgeIterator::Initialize(
  const ON_SubDFace* face
  )
{
  return Initialize(face, nullptr);
}

unsigned int ON_SubDFaceEdgeIterator::Initialize(
  const ON_SubDFace* face,
  const ON_SubDEdge* first_edge
  )
{
  m_face = face;
  m_edge_count = (nullptr != face) ? face->m_edge_count : 0;
  if (m_edge_count > 0 && nullptr != first_edge)
  {
    m_edge_index0 = face->EdgeArrayIndex(first_edge);
    if (ON_UNSET_UINT_INDEX == m_edge_index0)
    {
      m_edge_count = 0;
      m_edge_index0 = 0;
    }
  }
  else
  {
    m_edge_index0 = 0;
  }
  m_edge_index = m_edge_index0;
  return m_edge_count;
}

unsigned int ON_SubDFaceEdgeIterator::EdgeCount() const
{
  return m_edge_count;
}

const ON_SubDEdge* ON_SubDFaceEdgeIterator::FirstEdge()
{
  m_edge_index = m_edge_index0;
  return CurrentEdge();
}

const ON_SubDEdge* ON_SubDFaceEdgeIterator::CurrentEdge() const
{
  return (nullptr != m_face) ? m_face->Edge(m_edge_index) : nullptr;
}

const ON_SubDEdge* ON_SubDFaceEdgeIterator::NextEdge()
{
  if (m_edge_count > 0)
  {
    m_edge_index = (m_edge_index + 1) % m_edge_count;
    return CurrentEdge();
  }
  return nullptr;
}

const ON_SubDEdge* ON_SubDFaceEdgeIterator::PrevEdge()
{
  if (m_edge_count > 0)
  {
    m_edge_index = (m_edge_index + (m_edge_count - 1)) % m_edge_count;
    return CurrentEdge();
  }
  return nullptr;
}


const ON_SubDEdge* ON_SubDFaceEdgeIterator::NextEdge(bool bReturnNullAtFirstEdge)
{
  if (m_edge_count > 0)
  {
    const unsigned int next_edge_index = (m_edge_index + 1) % m_edge_count;
    if (bReturnNullAtFirstEdge && next_edge_index == m_edge_index0)
      return nullptr;
    m_edge_index = next_edge_index;
    return CurrentEdge();
  }
  return nullptr;
}

const ON_SubDEdge* ON_SubDFaceEdgeIterator::PrevEdge(bool bReturnNullAtFirstEdge)
{
  if (m_edge_count > 0)
  {
    const unsigned int prev_edge_index = (m_edge_index + (m_edge_count - 1)) % m_edge_count;
    if (bReturnNullAtFirstEdge && prev_edge_index == m_edge_index0)
      return nullptr;
    m_edge_index = prev_edge_index;
    return CurrentEdge();
  }
  return nullptr;
}

unsigned int ON_SubDFaceEdgeIterator::FirstEdgeIndex() const
{
  return m_edge_index0;
}

unsigned int ON_SubDFaceEdgeIterator::CurrentEdgeIndex() const
{
  return m_edge_index;
}

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDSectorId
//
const ON_SubDSectorId ON_SubDSectorId::Create(
  const ON_SubDVertex* vertex,
  const ON_SubDFace* face
)
{
  ON_SubDSectorId sid;

  if (nullptr == face && nullptr != vertex && vertex->IsSingleSectorVertex())
    face = vertex->Face(0);

  if (nullptr == vertex || nullptr == face)
  {
    // Creation of ON_SubDSectorId::Invalid in opennurbs_statics.cpp or 
    // just another invalid input.
    sid.m_vertex_id = 0;
    sid.m_minimum_face_id = 0;
    sid.m_sector_face_count = 0xFFFFFFFFU;
    return sid;
  }

  for (;;)
  {
    if (vertex->m_id <= 0 || vertex->m_id >= ON_UNSET_UINT_INDEX)
      break;
    if (face->m_id <= 0 || face->m_id >= ON_UNSET_UINT_INDEX)
      break;
    if (face->m_edge_count < 3)
      break;
    if (vertex->m_edge_count < 2)
      break;
    if (vertex->m_face_count < 1)
      break;
    const unsigned face_vi = face->VertexIndex(vertex);
    if (face_vi >= face->m_edge_count)
      break;

    sid.m_vertex_id = vertex->m_id;
    sid.m_minimum_face_id = face->m_id;
    const unsigned short n = vertex->m_face_count;
    unsigned short crease_face_count = 0;
    unsigned int expected_crease_count = 0;
    if (vertex->IsSmoothOrDart())
    {
      if (n < 2 || n != vertex->m_edge_count)
        break;
      const bool bIsDart = vertex->IsDart();
      crease_face_count = bIsDart ? 2 : 0;
      expected_crease_count = bIsDart ? 1 : 0;
    }
    else if ( vertex->IsCreaseOrCorner())
    {
      const ON_SubDComponentPtrPair pair 
        = (n + 1 == vertex->m_edge_count && 2==vertex->CreasedEdgeCount(true,true,true,false))
          ? vertex->BoundaryEdgePair()
          : ON_SubDComponentPtrPair::Null;
      if (pair.BothAreNotNull())
      {
        // we can avoid using a sector iterator
        const ON_SubDEdge* e[2] = { pair.First().Edge(),pair.Second().Edge() };
        if (nullptr == e[0] || nullptr == e[1])
          break;
        if (1 != e[0]->m_face_count || 1 != e[1]->m_face_count)
          break;
        crease_face_count = 1;
        expected_crease_count = 2;
      }
      else
      {
        if (vertex->IsCrease())
        {
          if (n != vertex->m_edge_count)
            return ON_SubDSectorId::Invalid;
        }

        // complicated case needs to use more time consuming sector iterator 
        ON_SubDSectorIterator sit0;
        if ( vertex != sit0.Initialize(face, 0, face_vi))
          return ON_SubDSectorId::Invalid;
        ON_SubDSectorIterator sit1(sit0);
        // advance sit0 until we hit a crease;
        sid.m_sector_face_count = 1;
        for (const ON_SubDFace* f = sit0.NextFace(ON_SubDSectorIterator::StopAt::AnyCrease); nullptr != f && sid.m_sector_face_count <= vertex->m_face_count; f = sit0.NextFace(ON_SubDSectorIterator::StopAt::AnyCrease))
        {
          ++sid.m_sector_face_count;
          if (f->m_id < sid.m_minimum_face_id)
            sid.m_minimum_face_id = f->m_id;
        }
        // advance sit1 until we hit a crease;
        for (const ON_SubDFace* f = sit1.PrevFace(ON_SubDSectorIterator::StopAt::AnyCrease); nullptr != f && sid.m_sector_face_count <= vertex->m_face_count; f = sit1.PrevFace(ON_SubDSectorIterator::StopAt::AnyCrease))
        {
          ++sid.m_sector_face_count;
          if (f->m_id < sid.m_minimum_face_id)
            sid.m_minimum_face_id = f->m_id;
        }
        break;
      }
    }
    else
    {
      break;
    }

    if (0 == sid.m_sector_face_count)
    {
      // we can avoid expensive sector iterator.
      unsigned int crease_count = 0;
      const ON_SubDFace* f;
      for (unsigned short vei = 0; vei < vertex->m_edge_count; ++vei)
      {
        const ON_SubDEdge* e = ON_SUBD_EDGE_POINTER(vertex->m_edges[vei].m_ptr);
        if (nullptr == e || 0 == e->m_face_count)
          return ON_SubDSectorId::Invalid;
        f = ON_SUBD_FACE_POINTER(e->m_face2[0].m_ptr);
        if (nullptr == f)
          return ON_SubDSectorId::Invalid;
        if (f->m_id < sid.m_minimum_face_id)
          sid.m_minimum_face_id = f->m_id;
        if (ON_SubDEdgeTag::Crease == e->m_edge_tag)
        {
          ++crease_count;
          if (crease_count > expected_crease_count)
            return ON_SubDSectorId::Invalid;
          if (crease_face_count != e->m_face_count)
            return ON_SubDSectorId::Invalid;
          if (1 == crease_face_count)
            continue;
        }
        if (2 != e->m_face_count)
          return ON_SubDSectorId::Invalid;
        f = ON_SUBD_FACE_POINTER(e->m_face2[1].m_ptr);
        if (nullptr == f)
          return ON_SubDSectorId::Invalid;
        if (f->m_id < sid.m_minimum_face_id)
          sid.m_minimum_face_id = f->m_id;
      }
      if (crease_count == expected_crease_count)
        sid.m_sector_face_count = n;
    }
    break;
  }

  return (sid.IsSet() && sid.m_sector_face_count <= vertex->m_face_count) ? sid : ON_SubDSectorId::Invalid;
}

const ON_SubDSectorId ON_SubDSectorId::CreateFromIds(
  unsigned int vertex_id,
  unsigned int minimum_face_id
)
{
  ON_SubDSectorId sid;
  sid.m_vertex_id = vertex_id;
  sid.m_minimum_face_id = minimum_face_id;
  sid.m_sector_face_count = 0;
  return sid;
}

int ON_SubDSectorId::Compare(ON_SubDSectorId lhs, ON_SubDSectorId rhs)
{
  if (lhs.m_vertex_id < rhs.m_vertex_id)
    return -1;
  if (lhs.m_vertex_id > rhs.m_vertex_id)
    return 1;
  if (lhs.m_minimum_face_id < rhs.m_minimum_face_id)
    return -1;
  if (lhs.m_minimum_face_id > rhs.m_minimum_face_id)
    return 1;
  if (lhs.m_sector_face_count < rhs.m_sector_face_count)
    return -1;
  if (lhs.m_sector_face_count > rhs.m_sector_face_count)
    return 1;
  return 0;
}

int ON_SubDSectorId::CompareFromPointers(const ON_SubDSectorId* lhs, const ON_SubDSectorId* rhs)
{
  if (nullptr == lhs || nullptr == rhs)
  {
    // sort nullptr to end
    if (nullptr != lhs)
      return -1;
    if (nullptr != rhs)
      return 1; 
    return 0;
  }
  return ON_SubDSectorId::Compare(*lhs, *rhs);
}

const unsigned int ON_SubDSectorId::VertexId() const
{
  return m_vertex_id;
}

const unsigned int ON_SubDSectorId::MinimumFaceId() const
{
  return m_minimum_face_id;
}

const unsigned int ON_SubDSectorId::SectorFaceCount() const
{
  return m_sector_face_count <= 0x10000U ? m_sector_face_count : 0U;
}

bool ON_SubDSectorId::IsZero() const
{
  return 0 == m_vertex_id && 0 == m_minimum_face_id && 0 == m_sector_face_count;
}

bool ON_SubDSectorId::IsSet() const
{
  // the maximum valid subd vertex face count is 0xFFFF.
  return m_vertex_id > 0 && m_minimum_face_id > 0 && m_sector_face_count > 0 && m_vertex_id < ON_UNSET_UINT_INDEX&& m_minimum_face_id < ON_UNSET_UINT_INDEX&& m_sector_face_count < 0x10000U;
}


bool operator==(ON_SubDSectorId lhs, ON_SubDSectorId rhs)
{
  return 0 == ON_SubDSectorId::Compare(lhs, rhs);
}

bool operator!=(ON_SubDSectorId lhs, ON_SubDSectorId rhs)
{
  return 0 != ON_SubDSectorId::Compare(lhs, rhs);
}

bool operator>(ON_SubDSectorId lhs, ON_SubDSectorId rhs)
{
  return ON_SubDSectorId::Compare(lhs, rhs) < 0;
}

bool operator<(ON_SubDSectorId lhs, ON_SubDSectorId rhs)
{
  return ON_SubDSectorId::Compare(lhs, rhs) > 0;
}

bool operator>=(ON_SubDSectorId lhs, ON_SubDSectorId rhs)
{
  return ON_SubDSectorId::Compare(lhs, rhs) >= 0;
}

bool operator<=(ON_SubDSectorId lhs, ON_SubDSectorId rhs)
{
  return ON_SubDSectorId::Compare(lhs, rhs) <= 0;
}


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDSectorIterator
//

static ON_SubDSectorIterator ON_SectorIterator_EmptyInitialize()
{  
  ON_SubDSectorIterator empty_init;
  empty_init.Initialize();
  return empty_init;
}

const ON_SubDSectorIterator ON_SubDSectorIterator::Empty(ON_SectorIterator_EmptyInitialize());

void ON_SubDSectorIterator::Initialize()
{
  // apply in place construction to this
  new (this) ON_SubDSectorIterator();
  m_current_eptr[0] = ON_SubDEdgePtr::Null;
  m_current_eptr[1] = ON_SubDEdgePtr::Null;
  m_current_fei[0] = 0;
  m_current_fei[1] = 0;
}

const ON_SubDVertex* ON_SubDSectorIterator::Initialize(
  const ON_SubDVertex* center_vertex
  )
{
  Initialize();
  if (nullptr == center_vertex || 0 == center_vertex->m_face_count || nullptr == center_vertex->m_faces)
    return ON_SUBD_RETURN_ERROR(nullptr);
  ON__UINT_PTR initial_face_direction = 0;
  return Initialize(center_vertex->m_faces[0], initial_face_direction, center_vertex);
}

const ON_SubDVertex* ON_SubDSectorIterator::Initialize(
  const ON_SubDFace* initial_face,
  ON__UINT_PTR iterator_orientation,
  const ON_SubDVertex* center_vertex
  )
{
  if (nullptr != center_vertex && nullptr != initial_face)
  {
    ON__UINT_PTR eptr;
    const ON_SubDEdge* edge;
    const unsigned int edge_count = initial_face->m_edge_count;
    const ON_SubDEdgePtr* face_eptr = initial_face->m_edge4;
    for (unsigned int efi = 0; efi < edge_count; efi++, face_eptr++)
    {
      if (4 == efi)
      {
        face_eptr = initial_face->m_edgex;
        if (nullptr == face_eptr)
          break;
      }
      eptr = face_eptr->m_ptr;
      edge = ON_SUBD_EDGE_POINTER(eptr);
      if (nullptr == edge)
        continue;
      eptr = ON_SUBD_EDGE_DIRECTION(eptr);
      if (center_vertex == edge->m_vertex[eptr])
        return Initialize(initial_face, iterator_orientation, efi);
    }
  }

  Initialize();
  return ON_SUBD_RETURN_ERROR(nullptr);
}

const ON_SubDVertex* ON_SubDSectorIterator::Initialize(
  const ON_SubDFace* initial_face,
  ON__UINT_PTR iterator_orientation,
  unsigned int face_vertex_index
  )
{
  Initialize();

  for (;;)
  {
    if (nullptr == initial_face)
      break;

    if (0 != iterator_orientation && 1 != iterator_orientation)
      break;

    const unsigned int face_edge_count = initial_face->m_edge_count;
    if (face_vertex_index >= face_edge_count)
      break;

    m_initial_face = initial_face;
    m_initial_fvi = face_vertex_index;

    //  initial_face->Edge(face_vertex_index) = edge "leaving" the center vertex
    ON_SubDEdgePtr eptr;
    if (face_vertex_index < 4)
    {
      eptr = initial_face->m_edge4[face_vertex_index];
    }
    else
    {
      if (nullptr == initial_face->m_edgex)
        return ON_SUBD_RETURN_ERROR(nullptr);
      eptr = initial_face->m_edgex[face_vertex_index - 4];
    }

    const ON_SubDEdge* edge0 = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
    if (nullptr == edge0)
      break;

    // m_current_eptr[0] = "prev" side edge
    m_current_fei[0] = face_vertex_index;
    m_current_eptr[0] = eptr;


    //  back up one vertex on the face
    face_vertex_index = (face_vertex_index+face_edge_count-1) % face_edge_count;

    //  initial_face->Edge(face_vertex_index) = edge "entering" the center vertex
    if (face_vertex_index < 4)
    {
      eptr = initial_face->m_edge4[face_vertex_index];
    }
    else
    {
      if (nullptr == initial_face->m_edgex)
        return ON_SUBD_RETURN_ERROR(nullptr);
      eptr = initial_face->m_edgex[face_vertex_index - 4];
    }

    const ON_SubDEdge* edge1 = ON_SUBD_EDGE_POINTER(eptr.m_ptr);
    if (nullptr == edge1)
      break;

    // m_current_eptr[1] = "next" side edge
    m_current_fei[1] = face_vertex_index;
    m_current_eptr[1] = eptr.Reversed(); // (reversed because face's eptr ends at center vertex)

    const ON_SubDVertex* center_vertex0 = edge0->m_vertex[ON_SUBD_EDGE_DIRECTION(m_current_eptr[0].m_ptr)];
    const ON_SubDVertex* center_vertex1 = edge1->m_vertex[ON_SUBD_EDGE_DIRECTION(m_current_eptr[1].m_ptr)];
    
    if (center_vertex0 != center_vertex1)
    {
      if (nullptr == center_vertex0)
        m_center_vertex = center_vertex1;
      else if ( nullptr == center_vertex1)
        m_center_vertex = center_vertex0;
      else
        break;
    }
    else if (nullptr != center_vertex0)
      m_center_vertex = center_vertex0;
    else
      break;

    if (1 == iterator_orientation)
    {
      m_initial_face_dir = 1;
      unsigned int i = m_current_fei[0];
      m_current_fei[0] = m_current_fei[1];
      m_current_fei[1] = i;
      eptr = m_current_eptr[0];
      m_current_eptr[0] = m_current_eptr[1];
      m_current_eptr[1] = eptr;
    }
    m_current_face = m_initial_face;
    m_current_face_dir = m_initial_face_dir;
    m_current_fvi = m_initial_fvi;
    
#if defined(ON_DEBUG)
    IsValid();
#endif

    return m_center_vertex;
  }

  Initialize();
  return ON_SUBD_RETURN_ERROR(nullptr);
}

const ON_SubDFace* ON_SubDSectorIterator::FirstFace()
{
  if (nullptr == m_initial_face)
    Initialize();
  else
    Initialize(m_initial_face, m_initial_face_dir, m_initial_fvi);
  return m_initial_face;
}

bool ON_SubDSectorIterator::IsValid() const
{
  if (nullptr == m_center_vertex && nullptr == m_initial_face)
    return true;

  if (nullptr == m_center_vertex || nullptr == m_initial_face)
    return ON_SUBD_RETURN_ERROR(false);

  if ( m_center_vertex != m_initial_face->Vertex(m_initial_fvi) )
    return ON_SUBD_RETURN_ERROR(false);

  if (nullptr == m_current_face)
    return true; // finished iterating

  if (m_center_vertex != m_current_face->Vertex(m_current_fvi))
    return ON_SUBD_RETURN_ERROR(false);

  const ON_SubDEdge* edge[2] = { m_current_eptr[0].Edge(), m_current_eptr[1].Edge() };
  if (nullptr == edge[0] || nullptr == edge[1])
    return ON_SUBD_RETURN_ERROR(false);
  if (m_center_vertex != edge[0]->m_vertex[ON_SUBD_EDGE_DIRECTION(m_current_eptr[0].m_ptr)])
    return ON_SUBD_RETURN_ERROR(false);
  if (m_center_vertex != edge[1]->m_vertex[ON_SUBD_EDGE_DIRECTION(m_current_eptr[1].m_ptr)])
    return ON_SUBD_RETURN_ERROR(false);

  const ON_SubDEdgePtr feptr[2] = { m_current_face->EdgePtr(m_current_fei[0]), m_current_face->EdgePtr(m_current_fei[1]) };
  
  if (edge[0] != ON_SUBD_EDGE_POINTER(feptr[0].m_ptr))
    return ON_SUBD_RETURN_ERROR(false);

  if (edge[1] != ON_SUBD_EDGE_POINTER(feptr[1].m_ptr))
    return ON_SUBD_RETURN_ERROR(false);

  return true;
}


const ON_SubDVertex* ON_SubDSectorIterator::CenterVertex() const
{
  return m_center_vertex;
}

const ON_SubDFace* ON_SubDSectorIterator::InitialFace() const
{
  return m_initial_face;
}

int ON_SubDSectorIterator::CurrentRingIndex() const
{
  return m_current_ring_index;
}

const ON_SubDFace* ON_SubDSectorIterator::CurrentFace() const
{
  return m_current_face;
}

ON_SubDFacePtr ON_SubDSectorIterator::CurrentFacePtr() const
{
  return ON_SubDFacePtr::Create(m_current_face,m_current_face_dir);
}

unsigned int ON_SubDSectorIterator::InitialFaceCenterVertexIndex() const
{
  return m_initial_fvi;
}

unsigned int ON_SubDSectorIterator::CurrentFaceCenterVertexIndex() const
{
  return m_current_fvi;
}


unsigned int ON_SubDSectorIterator::CurrentFaceDirection() const
{
  return m_current_face_dir;
}

ON_SubDEdgePtr ON_SubDSectorIterator::CurrentEdgePtr(
  unsigned int face_side_index
  ) const
{
  return (face_side_index < 2) ? m_current_eptr[face_side_index] : ON_SubDEdgePtr::Null;
}



const ON_SubDEdge* ON_SubDSectorIterator::CurrentEdge(
  unsigned int face_side_index
  ) const
{
  return (face_side_index < 2) ? ON_SUBD_EDGE_POINTER(m_current_eptr[face_side_index].m_ptr) : nullptr;
}

ON__UINT_PTR ON_SubDSectorIterator::CurrentEdgeDirection(
  unsigned int face_side_index
  ) const
{
  return (face_side_index < 2) ? ON_SUBD_EDGE_DIRECTION(m_current_eptr[face_side_index].m_ptr) : 0;
}

const ON_SubDVertex* ON_SubDSectorIterator::CurrentEdgeRingVertex(
  unsigned int face_side_index
  ) const
{
  if (face_side_index >= 2)
    return ON_SUBD_RETURN_ERROR(nullptr);
  ON__UINT_PTR eptr = m_current_eptr[face_side_index].m_ptr;
  const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(eptr);
  if (nullptr == edge)
    return ON_SUBD_RETURN_ERROR(nullptr);
  const ON_SubDVertex* edge_ring_vertex = edge->m_vertex[1 - ON_SUBD_EDGE_DIRECTION(eptr)];
  if ( nullptr == edge_ring_vertex || edge_ring_vertex == m_center_vertex)
    return ON_SUBD_RETURN_ERROR(nullptr);
  return edge_ring_vertex;
}

const ON_SubDFace* ON_SubDSectorIterator::NextFace(
  ON_SubDSectorIterator::StopAt stop_at
  )
{
  return IncrementFace(1, stop_at);
}

const ON_SubDFace* ON_SubDSectorIterator::PrevFace(
  ON_SubDSectorIterator::StopAt stop_at
  )
{
  return IncrementFace(-1, stop_at);
}

const ON_SubDFace* ON_SubDSectorIterator::IncrementFace(
  int increment_direction,
  ON_SubDSectorIterator::StopAt stop_at
  )
{
  if (nullptr == m_current_face)
  {
    return ON_SUBD_RETURN_ERROR(nullptr);
  }

  // increment_direction > 0 means counterclockwise / next
  // increment_direction <= 0 means clockwise / prev
  unsigned int side_index = (increment_direction > 0) ? 1 : 0; 
  ON__UINT_PTR eptr = m_current_eptr[side_index].m_ptr;
  const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(eptr);
  if (nullptr == edge)
  {
    return ON_SUBD_RETURN_ERROR(nullptr);
  }

  for (;;)
  {
    if (edge->m_face_count != 2)
    {
      // set stop_at to something not equal to Boundary
      stop_at = ON_SubDSectorIterator::StopAt::AnyCrease;
      break;
    }

    if (ON_SubDSectorIterator::StopAt::Boundary != stop_at)
    {
      if (ON_SubDEdgeTag::Crease == edge->m_edge_tag)
      {
        if (ON_SubDSectorIterator::StopAt::AnyCrease == stop_at)
          break;
        if (ON_SubDSectorIterator::StopAt::HardCrease == stop_at && edge->IsHardCrease())
          break;
      }
      stop_at = ON_SubDSectorIterator::StopAt::Boundary;
    }

    unsigned int efi;
    if (m_current_face == ON_SUBD_FACE_POINTER(edge->m_face2[0].m_ptr))
    {
      efi = 0;
    }
    else if (m_current_face == ON_SUBD_FACE_POINTER(edge->m_face2[1].m_ptr))
    {
      efi = 1;
    }
    else
      break;
    const ON__UINT_PTR ef0dir = ON_SUBD_FACE_DIRECTION(edge->m_face2[efi].m_ptr);
    efi = 1 - efi;
    const ON__UINT_PTR ef1dir = ON_SUBD_FACE_DIRECTION(edge->m_face2[efi].m_ptr);
    const ON_SubDFace* face1 = ON_SUBD_FACE_POINTER(edge->m_face2[efi].m_ptr);
    if (nullptr == face1)
      break;
    const unsigned int face1_edge_count = face1->m_edge_count;
    const ON_SubDEdgePtr* face1_edges = face1->m_edge4;
    for (unsigned int fei = 0; fei < face1_edge_count; fei++, face1_edges++)
    {
      if (4 == fei)
      {
        if (nullptr == (face1_edges = face1->m_edgex))
          break;
      }

      if (edge != ON_SUBD_EDGE_POINTER(face1_edges->m_ptr))
        continue;

      // At this point, face1->Edges(fei) is the edge I just hopped across
      // to get from the old current face to face 1. Update current face
      // information and return.
      m_current_face = face1; 
      if (ef0dir == ef1dir)
        m_current_face_dir = 1 - m_current_face_dir;

      side_index = 1 - side_index;
      m_current_fei[side_index] = fei;
      if (m_center_vertex == edge->m_vertex[0])
        m_current_eptr[side_index] = ON_SubDEdgePtr::Create(edge,0);
      else if (m_center_vertex == edge->m_vertex[1])
        m_current_eptr[side_index] = ON_SubDEdgePtr::Create(edge,1);
      else
        break;

      if (side_index == m_current_face_dir)
      {
        m_current_fvi = fei;
        fei = (fei > 0) ? (fei - 1) : (face1_edge_count - 1);
      }
      else
      {
        fei = (fei + 1) % face1_edge_count;
        m_current_fvi = fei;
      }

      if (fei < 4)
        face1_edges = face1->m_edge4;
      else
      {
        if (nullptr == (face1_edges = face1->m_edgex))
          break;
        face1_edges -= 4;
      }
      side_index = 1 - side_index;
      m_current_fei[side_index] = fei;
      edge = ON_SUBD_EDGE_POINTER(face1_edges[fei].m_ptr);
      if ( nullptr == edge)
        break;
      if (m_center_vertex == edge->m_vertex[0])
        m_current_eptr[side_index] = ON_SubDEdgePtr::Create(edge,0);
      else if (m_center_vertex == edge->m_vertex[1])
        m_current_eptr[side_index] = ON_SubDEdgePtr::Create(edge,1);
      else
        break;

      if (increment_direction > 0)
        m_current_ring_index++;
      else
        m_current_ring_index--;

#if defined(ON_DEBUG)
      IsValid();
#endif

      return m_current_face;
    }

    break;
  }

  // termination
  m_current_face = nullptr;
  m_current_fvi = 0;
  m_current_fei[0] = 0;
  m_current_fei[1] = 0;
  
  if (ON_SubDSectorIterator::StopAt::Boundary != stop_at)
  {
    // termination at a crease, nonmanifold edge, or edge with one face
    m_current_eptr[1 - side_index] = m_current_eptr[side_index];
    m_current_eptr[side_index] = ON_SubDEdgePtr::Null;
    return nullptr;
  }

  // error condition
  m_current_eptr[0] = ON_SubDEdgePtr::Null;
  m_current_eptr[0] = ON_SubDEdgePtr::Null;

  return ON_SUBD_RETURN_ERROR(nullptr);
}

const ON_SubDFace* ON_SubDSectorIterator::IncrementToCrease(
  int increment_direction
)
{
  const ON_SubDEdgeTag etag = this->IncrementToCrease(
    increment_direction,
    nullptr
  );
  return (ON_SubDEdgeTag::Crease == etag) ? this->CurrentFace() : nullptr;
}

ON_SubDEdgeTag ON_SubDSectorIterator::IncrementToCrease(
  int increment_direction,
  unsigned* increment_count
)
{
  if (nullptr != increment_count)
    *increment_count = 0;
  if (nullptr == m_center_vertex)
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgeTag::Unset);

  const unsigned int N = m_center_vertex->m_edge_count;
  const unsigned int edge_side = increment_direction > 0 ? 1 : 0;

  ON_SubDSectorIterator sit(*this);
  const ON_SubDFace* face0 = sit.CurrentFace();
  if (nullptr == face0)
    return ON_SUBD_RETURN_ERROR(ON_SubDEdgeTag::Unset);

  // The for (unsigned int i = 0; i < N; i++) {} prevents infinite looping
  // if the topology is pointers contain an invalid cycle.
  for (unsigned int i = 0; i < N; i++)
  {
    const ON_SubDEdge* edge = sit.CurrentEdge(edge_side);
    if (nullptr == edge)
      return ON_SUBD_RETURN_ERROR(ON_SubDEdgeTag::Unset);

    if (edge->m_face_count != 2 || ON_SubDEdgeTag::Crease == edge->m_edge_tag)
    {
      if (nullptr != increment_count)
        *increment_count = i;
      *this = sit;
      return ON_SubDEdgeTag::Crease;
    }

    const ON_SubDFace* face = sit.IncrementFace(increment_direction,ON_SubDSectorIterator::StopAt::AnyCrease);
    if (nullptr == face)
      return ON_SUBD_RETURN_ERROR(ON_SubDEdgeTag::Unset);
    if ( face == face0 )
      return ON_SubDEdgeTag::Smooth; // no crease and back where we started
  }

  return ON_SUBD_RETURN_ERROR(ON_SubDEdgeTag::Unset);
}

bool ON_SubDSectorIterator::InitializeToCurrentFace()
{
  const ON_SubDFace* face = CurrentFace();
  if ( nullptr == face)
    return ON_SUBD_RETURN_ERROR(false);
  ON_SubDSectorIterator sit;
  if (nullptr == sit.Initialize(face, sit.CurrentFaceDirection(), sit.CurrentFaceCenterVertexIndex()))
    return ON_SUBD_RETURN_ERROR(false);
  if (face != sit.CurrentFace())
    return ON_SUBD_RETURN_ERROR(false);
  *this = sit;
  return true;
}



//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentIterator
//

ON_SubDComponentIterator::ON_SubDComponentIterator(
  const class ON_SubD& subd
  )
{
  *this = ON_SubDComponentIterator(ON_SubDRef::CreateReferenceForExperts(subd));
}

ON_SubDComponentIterator::ON_SubDComponentIterator(
  const class ON_SubDRef& subd_ref
  )
{
  m_subd_ref = subd_ref;
  const ON_SubDLevel& level = subd_ref.SubD().ActiveLevel();
  const ON_SubDFace* f_first = level.m_face[0];
  const ON_SubDFace* f_last = level.m_face[1];
  if (f_first && f_last)
  {
    m_face_first = f_first;
    m_face_last = f_last;
    m_cptr_current = ON_SubDComponentPtr::Create(m_face_first);
  }

  const ON_SubDEdge* e_first = level.m_edge[0];
  const ON_SubDEdge* e_last = level.m_edge[1];
  if (e_first && e_last)
  {
    m_edge_first = e_first;
    m_edge_last = e_last;
    m_cptr_current = ON_SubDComponentPtr::Create(m_edge_first);
  }

  const ON_SubDVertex* v_first = level.m_vertex[0];
  const ON_SubDVertex* v_last = level.m_vertex[1];
  if (v_first && v_last)
  {
    m_vertex_first = v_first;
    m_vertex_last = v_last;
    m_cptr_current = ON_SubDComponentPtr::Create(m_vertex_first);
  }
}

#if defined(ON_HAS_RVALUEREF)
// rvalue copy constructor
ON_SubDComponentIterator::ON_SubDComponentIterator( ON_SubDComponentIterator&& src) ON_NOEXCEPT
  : m_subd_ref(std::move(src.m_subd_ref))
  , m_subd_level(src.m_subd_level)
  , m_vertex_first(src.m_vertex_first)
  , m_vertex_last(src.m_vertex_last)
  , m_edge_first(src.m_edge_first)
  , m_edge_last(src.m_edge_last)
  , m_face_first(src.m_face_first)
  , m_face_last(src.m_face_last)
  , m_cptr_current(src.m_cptr_current)
{}

// rvalue assignment operator
ON_SubDComponentIterator& ON_SubDComponentIterator::operator=(ON_SubDComponentIterator&& src)
{
  m_subd_ref.Clear();
  m_subd_ref = std::move(src.m_subd_ref);
  m_subd_level = src.m_subd_level;
  m_vertex_first = src.m_vertex_first;
  m_vertex_last = src.m_vertex_last;
  m_edge_first = src.m_edge_first;
  m_edge_last = src.m_edge_last;
  m_face_first = src.m_face_first;
  m_face_last = src.m_face_last;
  m_cptr_current = src.m_cptr_current;
  return *this;
}
#endif

/*
Description:
  Set the iterator to the beginning of the component list.
Returns:
  First component in the list.
*/
const class ON_SubDComponentPtr ON_SubDComponentIterator::FirstComponent()
{
  if (nullptr != m_vertex_first)
    m_cptr_current = ON_SubDComponentPtr::Create(m_vertex_first);
  else if (nullptr != m_edge_first)
    m_cptr_current = ON_SubDComponentPtr::Create(m_edge_first);
  else if (nullptr != m_face_first)
    m_cptr_current = ON_SubDComponentPtr::Create(m_face_first);
  else
    m_cptr_current = ON_SubDComponentPtr::Null;
  return m_cptr_current;
}


const class ON_SubDComponentPtr ON_SubDComponentIterator::NextComponent()
{
  switch (m_cptr_current.ComponentType())
  {
  case ON_SubDComponentPtr::Type::Vertex:
    {
      const ON_SubDVertex* vertex = ON_SUBD_VERTEX_POINTER(m_cptr_current.m_ptr);
      if (nullptr != vertex && vertex != m_vertex_last && nullptr != vertex->m_next_vertex)
      {
        m_cptr_current = ON_SubDComponentPtr::Create(vertex->m_next_vertex);
        return m_cptr_current;
      }
    }
    m_cptr_current = ON_SubDComponentPtr::Null;
    // no break here

  case ON_SubDComponentPtr::Type::Edge:
    {
      if (0 == m_cptr_current.m_ptr && nullptr != m_edge_first)
      {
        // switching from vertex to edge
        m_cptr_current = ON_SubDComponentPtr::Create(m_edge_first);
        return m_cptr_current;
      }
      const ON_SubDEdge* edge = ON_SUBD_EDGE_POINTER(m_cptr_current.m_ptr);
      if (nullptr != edge && edge != m_edge_last && nullptr != edge->m_next_edge )
      {
        m_cptr_current = ON_SubDComponentPtr::Create(edge->m_next_edge);
        return m_cptr_current;
      }
    }
    m_cptr_current = ON_SubDComponentPtr::Null;
    // no break here

  case ON_SubDComponentPtr::Type::Face:
    {
      if (0 == m_cptr_current.m_ptr && nullptr != m_face_first)
      {
        // switching from edge to face
        m_cptr_current = ON_SubDComponentPtr::Create(m_face_first);
        return m_cptr_current;
      }
      const ON_SubDFace* face = ON_SUBD_FACE_POINTER(m_cptr_current.m_ptr);
      if (nullptr != face && face != m_face_last && nullptr != face->m_next_face)
      {
        m_cptr_current = ON_SubDComponentPtr::Create(face->m_next_face);
        return m_cptr_current;
      }
    }
    m_cptr_current = ON_SubDComponentPtr::Null;
    break;

  default:
    break;
  }
  
  return m_cptr_current;
}

const class ON_SubDComponentPtr ON_SubDComponentIterator::LastComponent()
{
  if (nullptr != m_face_last)
    m_cptr_current = ON_SubDComponentPtr::Create(m_face_last);
  else if (nullptr != m_edge_last)
    m_cptr_current = ON_SubDComponentPtr::Create(m_edge_last);
  else if (nullptr != m_vertex_last)
    m_cptr_current = ON_SubDComponentPtr::Create(m_vertex_last);
  else
    m_cptr_current = ON_SubDComponentPtr::Null;
  return m_cptr_current;
}
