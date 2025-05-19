#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

ON_MeshNgonBuffer::ON_MeshNgonBuffer()
{
  memset(m_ngon_buffer,0,sizeof(m_ngon_buffer));
}

const class ON_MeshNgon* ON_MeshNgonBuffer::Ngon() const
{
  return (const class ON_MeshNgon*)m_ngon_buffer;
}
  
const class ON_MeshNgon* ON_MeshNgonBuffer::CreateFromMeshFaceIndex(
  const class ON_Mesh* mesh,
  unsigned int face_index
  )
{
  const class ON_MeshFace* mesh_face = ( mesh && face_index < mesh->m_F.UnsignedCount() )
                                     ? &mesh->m_F[face_index] 
                                     : 0;
  if (nullptr == mesh_face || false == mesh_face->IsValid(mesh->m_V.Count()))
    return nullptr;
  return CreateFromMeshFace(mesh_face,face_index);
}
  
const class ON_MeshNgon* ON_MeshNgonBuffer::CreateFromMeshFace(
  const class ON_MeshFace* mesh_face,
  unsigned int face_index
  )
{
  return CreateFromQuad(mesh_face ? ((const unsigned int*)mesh_face->vi) : 0, face_index );
}
  
const class ON_MeshNgon* ON_MeshNgonBuffer::CreateFromTriangle(
  const unsigned int triangle_vertex_indices[3],
  unsigned int face_index
  )
{
  if ( 0 != triangle_vertex_indices )
  {
    const unsigned int quad_vertex_indices[4] = {
      triangle_vertex_indices[0],
      triangle_vertex_indices[1],
      triangle_vertex_indices[2],
      0
    };
    return ON_MeshNgon::NgonFromMeshFace(*this,face_index,quad_vertex_indices);
  }
  return ON_MeshNgon::NgonFromMeshFace(*this,face_index,0);
}

const class ON_MeshNgon* ON_MeshNgonBuffer::CreateFromQuad(
  const unsigned int quad_vertex_indices[4],
  unsigned int face_index
  )
{
  memset(m_ngon_buffer,0,sizeof(m_ngon_buffer));
  return ON_MeshNgon::NgonFromMeshFace(*this,face_index,quad_vertex_indices);
}

ON__UINT32 ON_MeshNgon::CRC32() const
{
  ON__UINT32 crc = 0;
  if ( m_Vcount > 0 && m_vi )
    crc = ON_CRC32(crc,m_Vcount*sizeof(m_vi[0]),m_vi);  
  if ( m_Fcount > 0 && m_fi )
    crc = ON_CRC32(crc,m_Fcount*sizeof(m_fi[0]),m_fi);
  return crc;
}

ON_SHA1_Hash ON_MeshNgon::ContentHash() const
{
  ON_SHA1 sha1;
  if ( m_Vcount > 0 && m_vi )
    sha1.AccumulateBytes(m_vi,m_Vcount*sizeof(m_vi[0]));  
  if ( m_Fcount > 0 && m_fi )
    sha1.AccumulateBytes(m_fi,m_Fcount*sizeof(m_fi[0]));
  return sha1.Hash();
}

static int Internal_compare_ngon_edges(const void* a, const void* b)
{
  const unsigned int* ai = (const unsigned int*)a;
  const unsigned int* bi = (const unsigned int*)b;
  if (*ai < *bi)
    return -1;
  if (*ai > *bi)
    return 1;
  ai++;
  bi++;
  if (*ai < *bi)
    return -1;
  if (*ai > *bi)
    return 1;
  return 0;
}

unsigned int ON_MeshNgon::BoundaryEdgeCount(const ON_MeshFaceList & mesh_face_list) const
{
  if (m_Fcount <= 0 || nullptr == m_fi)
    return 0;
  const unsigned int mesh_face_count = mesh_face_list.FaceCount();
  if (mesh_face_count <= 0)
    return 0;

  const unsigned int edge_capacity = 4 * mesh_face_count;
  ON_SimpleArray<ON_2udex> edge_buffer(edge_capacity);
  edge_buffer.SetCount(edge_capacity);
  ON_2udex* edges = edge_buffer.Array();
  unsigned int edge_count = 0;
  unsigned int face_vi[4];

  ON_2udex e;
  for (unsigned int i = 0; i < m_Fcount; i++)
  {
    mesh_face_list.QuadFvi(m_fi[i], face_vi);
    e.j = face_vi[3];
    for (unsigned int j = 0; j < 4; j++)
    {
      e.i = e.j;
      e.j = face_vi[j];
      if (e.i == e.j)
        continue;
      if (e.i < e.j)
      {
        edges[edge_count] = e;
      }
      else
      {
        edges[edge_count].i = e.j;
        edges[edge_count].j = e.i;
      }
      edge_count++;
    }
  }

  ON_qsort(edges, edge_count, sizeof(edges[0]), Internal_compare_ngon_edges);
  unsigned int boundary_edge_count = 0;

  for (unsigned int i = 0; i < edge_count; /*empty iterator*/)
  {
    e = edges[i++];
    const unsigned int i1 = i;
    for (/*empty init*/; i < edge_count; i++)
    {
      if (edges[i].i != e.i || edges[i].j != e.j)
        break;
    }
    if (i1 == i)
      boundary_edge_count++;
  }

  return boundary_edge_count;
}

unsigned int ON_MeshNgon::OuterBoundaryEdgeCount() const
{
  return (m_Vcount >= 3 && nullptr != m_vi) ? m_Vcount : 0;
}

int ON_MeshNgon::Orientation(
  const ON_Mesh* mesh,
  bool bPermitHoles
) const
{
  const ON_MeshFaceList face_list(mesh);
  return Orientation(face_list, bPermitHoles);
}


static int ON_Internal_CompareNgonEdge(
  const void* lhs,
  const void* rhs
)
{
  const int i = (((const unsigned int*)lhs)[0] <= ((const unsigned int*)lhs)[1]) ? 0 : 1;
  const int j = (((const unsigned int*)rhs)[0] <= ((const unsigned int*)rhs)[1]) ? 0 : 1;
  if (((const unsigned int*)lhs)[i] < ((const unsigned int*)rhs)[j])
    return -1;
  if (((const unsigned int*)lhs)[i] > ((const unsigned int*)rhs)[j])
    return 1;
  if (((const unsigned int*)lhs)[1-i] < ((const unsigned int*)rhs)[1-j])
    return -1;
  if (((const unsigned int*)lhs)[1-i] > ((const unsigned int*)rhs)[1-j])
    return 1;
  if (((const unsigned int*)lhs)[2] < ((const unsigned int*)rhs)[2])
    return -1;
  if (((const unsigned int*)lhs)[2] > ((const unsigned int*)rhs)[2])
    return 1;
  return 0;  
}

static int ON_Internal_MeshNgon_NotOriented()
{
  // optimized away in release builds
  return 0; // nice place for a breakpoint.
}

int ON_MeshNgon::Orientation(
  const ON_MeshFaceList& mesh_face_list,
  bool bPermitHoles
) const
{
  if (m_Fcount < 1 || nullptr == m_fi)
    return ON_Internal_MeshNgon_NotOriented();

  if (m_Vcount < 3 || nullptr == m_vi)
    return ON_Internal_MeshNgon_NotOriented();
  
  const unsigned int mesh_Fcount = mesh_face_list.FaceCount();

  if (mesh_Fcount < m_Fcount)
    return ON_Internal_MeshNgon_NotOriented();

  unsigned int face_vi[4];
  if (1 == m_Fcount && m_Vcount >= 3 && m_Vcount <= 4)
  {
    // fast check for common case of a single face ngon
    mesh_face_list.QuadFvi(m_fi[0], face_vi);
    if (m_vi[0] == face_vi[0]
      && m_vi[1] == face_vi[1]
      && m_vi[2] == face_vi[2]
      && m_vi[(3 % m_Vcount)] == face_vi[3]
      )
    {
      // ngon = mesh face
      return 1;
    }
  }

  const int a_capacity = (int)(4 * m_Fcount + 2 * m_Vcount);
  
  ON_SimpleArray<ON_3udex> buffer;
  buffer.Reserve(a_capacity);
  ON_3udex* edge = buffer.Array();


  ON_3udex e;

  unsigned int edge_count = 0;

  e.k = 0; // from a face
  for (unsigned int nfi = 0; nfi < m_Fcount; nfi++)
  {
    unsigned int fi = m_fi[nfi];
    if (fi >= mesh_Fcount)
      return ON_Internal_MeshNgon_NotOriented(); // invalid ngon m_fi[] value.
    mesh_face_list.QuadFvi(fi, face_vi);
    const unsigned int fvi_count = face_vi[2] != face_vi[3] ? 4 : 3;
    e.j = face_vi[3];
    for (unsigned int fvi = 0; fvi < fvi_count; fvi++)
    {
      e.i = e.j;
      e.j = face_vi[fvi];
      if (e.i == e.j)
        return ON_Internal_MeshNgon_NotOriented(); // invalid face
      edge[edge_count++] = e;
    }
  }

  e.k = 1; // from ngon boundary
  e.j = m_vi[m_Vcount - 1];
  for (unsigned int nvi = 0; nvi < m_Vcount; nvi++)
  {
    e.i = e.j;
    e.j = m_vi[nvi];
    if (e.i == e.j)
      return ON_Internal_MeshNgon_NotOriented(); // ngon m_vi[] has duplicates
    edge[edge_count++] = e;
  }

  if (edge_count < 6
    || (false == bPermitHoles && 0 != (edge_count % 2))
    )
  {
    return ON_Internal_MeshNgon_NotOriented();
  }

  ON_qsort(edge, edge_count, sizeof(edge[0]), ON_Internal_CompareNgonEdge);
  e.i = 0;
  e.j = 0;
  e.k = 0;
  int orientation = 0;
  unsigned int interior_boundary_edge_count = 0;
  unsigned int outer_boundary_edge_count = 0;
  for (unsigned int ei = 0; ei < edge_count; ei++)
  {
    if (0 != edge[ei].k )
      return ON_Internal_MeshNgon_NotOriented(); // invalid ngon boundary.

    e.k = 0;
    if (0 == ON_Internal_CompareNgonEdge(&e, &edge[ei]))
    {
      // non-manifold or invalid
      return ON_Internal_MeshNgon_NotOriented();
    }

    if (ei + 1 >= edge_count)
    {
      // last edge;
      if (bPermitHoles)
      {
        interior_boundary_edge_count++;
        break;
      }
      return ON_Internal_MeshNgon_NotOriented();
    }

    e = edge[ei+1];
    if (0 == e.k)
    {
      // edge[ei + 1] is a face edge
      const int c = ON_Internal_CompareNgonEdge(&edge[ei], &e);
      if (c > 0)
      {
        ON_ERROR("bug in this code");
        return ON_Internal_MeshNgon_NotOriented();
      }
      if (c < 0)
      {
        // face edge with no matching edge on another face or ngon outer boundary
        if (bPermitHoles)
        {
          // assume it is interior
          interior_boundary_edge_count++;
          continue;
        }

        // face edge with no matching edge
        return ON_Internal_MeshNgon_NotOriented();
      }

      // edge[ei] and e are face edges and they should have opposite orientations.
      if (e.j != edge[ei].i || e.i != edge[ei].j)
      {
        // face set is not oriented, it's a hole and bPermitHoles=false, or other invalid situation
        return ON_Internal_MeshNgon_NotOriented();
      }
    }
    else
    {
      // edge[ei + 1] is an ngon outer boundary edge
      outer_boundary_edge_count++;
      if (1 == orientation)
      {
        // edge[ei] is a face edge, e is an ngon outer boundary edge, and they should have the same orientations
        if (e.i != edge[ei].i || e.j != edge[ei].j)
          return ON_Internal_MeshNgon_NotOriented(); // ngon boundary orientation is not consistent or face set is not oriented.
      }
      else if (-1 == orientation)
      {
        // edge[ei] is a face edge, e is an ngon outer boundary edge, and they should have opposite orientations
        if (e.j != edge[ei].i || e.i != edge[ei].j)
          return ON_Internal_MeshNgon_NotOriented(); // ngon boundary orientation is not consistent or face set is not oriented.
      }
      else
      {
        // edge[ei] is a face edge, e is an ngon outer boundary edge, 
        // and e is the first ngon ngon outer boundary edge encountered.
        if (e.i == edge[ei].i && e.j == edge[ei].j)
          orientation = 1; // this ngon edge orientation is the same as the face's edge.
        else if (e.j == edge[ei].i && e.i == edge[ei].j)
          orientation = -1; // this ngon edge orientation is opposite the face's edge.
        else
          return ON_Internal_MeshNgon_NotOriented(); // the ngon boundary edge e is not an edge of a face
      }
    }
    ei++;
  }

  if ( 0 == orientation )
    return ON_Internal_MeshNgon_NotOriented();

  if ( outer_boundary_edge_count != m_Vcount )
    return ON_Internal_MeshNgon_NotOriented();

  if ( outer_boundary_edge_count != m_Vcount )
    return ON_Internal_MeshNgon_NotOriented();

  if (interior_boundary_edge_count >= 1 && interior_boundary_edge_count <= 2)
  {
    // a valid interior bound must have at least 3 edges
    return ON_Internal_MeshNgon_NotOriented();
  }

  return orientation;
}


unsigned int ON_MeshNgon::BoundaryEdgeCount(const ON_Mesh * mesh) const
{
  const ON_MeshFaceList face_list(mesh);
  return BoundaryEdgeCount(face_list);
}

unsigned ON_Mesh::NgonBoundaryEdgeCount(unsigned int ngon_index) const
{
  const ON_MeshNgon* ngon = Ngon(ngon_index);
  return (nullptr == ngon) ? 0 : ngon->BoundaryEdgeCount(this);
}

unsigned int ON_MeshNgon::Capacity() const
{
  if ( (0 != m_vi || 0 != m_fi) )
  {
    unsigned int capacity;
    const unsigned int* a = (const unsigned int*)(this+1);
    if ( (m_vi == a+1 || (0 == m_Vcount && 0 == m_vi && m_fi == a+1)) && *a >= 7 )
    {
      capacity = (unsigned int)*a++;
      if ( 7 == capacity || 15 == capacity || 31 == capacity || (capacity >= 63 && 7 == (capacity%8) && capacity < 0x100000U) )
      {
        if ( capacity >= m_Vcount + m_Fcount 
             && ((0 == m_Fcount && 0 == m_fi) || (m_fi >= m_vi + m_Vcount && m_fi < a + capacity))
           )
          return capacity;
      }
    }
  }

  return 0;
}

int ON_MeshNgon::Compare(
    const ON_MeshNgon* A,
    const ON_MeshNgon* B
    )
{
  const unsigned int* pA;
  const unsigned int* pB;
  int c;
  if ( 0 == A )
  {
    return ( 0 == B  ) ? 0 : -1;
  }
  
  if ( 0 == B )
  {
    return 1;
  }

  if ( A->m_Vcount < B->m_Vcount )
    return -1;
  if ( A->m_Vcount > B->m_Vcount )
    return 1;
  if ( A->m_Fcount < B->m_Fcount )
    return -1;
  if ( A->m_Fcount > B->m_Fcount )
    return -1;

  pA = A->m_vi;
  pB = B->m_vi;
  if ( 0 == pA )
  {
    return ( 0 == pB  ) ? 0 : -1;
  }
  if ( 0 == pB )
  {
    return 1;
  }
  c = A->m_Vcount;
  while (c--)
  {
    if ( *pA < *pB )
      return -1;
    if ( *pA > *pB )
      return 1;
  }

  pA = A->m_fi;
  pB = B->m_fi;
  if ( 0 == pA )
  {
    return ( 0 == pB  ) ? 0 : -1;
  }
  if ( 0 == pB )
  {
    return 1;
  }
  c = A->m_Fcount;
  while (c--)
  {
    if ( *pA < *pB )
      return -1;
    if ( *pA > *pB )
      return 1;
  }

  return 0;
}

static char* ToStringHelper( const char* src_str, char* dst_str, const char* dst_str_end )
{
  if ( 0 == dst_str || dst_str_end <= dst_str )
    return 0;

  if ( 0 == src_str )
    src_str = "";
  while ( dst_str < dst_str_end )
  {
    if ( 0 == (*dst_str = *src_str++) )
      return dst_str;
    dst_str++;
  }
  return 0;
}


static char* ToStringHelper( unsigned int u, char* dst_str, const char* dst_str_end )
{
  char ubuffer[32]; // unsigned int to string storage buffer
  unsigned int i, j;

  if ( ON_UNSET_UINT_INDEX == u )
    return ToStringHelper( "unset", dst_str, dst_str_end );

  i = u;
  j = (unsigned int)(sizeof(ubuffer)/sizeof(ubuffer[0]));
  j--;
  ubuffer[j] = 0;
  while(j > 0)
  {
    j--;
    ubuffer[j] = (char)('0'+i%10);
    i /= 10;
    if ( 0 == i )
      return ToStringHelper( &ubuffer[j], dst_str, dst_str_end );
  }

  return 0;
}

static char* ToStringHelper( const unsigned int* a, unsigned int count, char* dst_str, const char* dst_str_end )
{
  unsigned int i, imax;

  dst_str = ToStringHelper("[",dst_str,dst_str_end);
  dst_str = ToStringHelper(count,dst_str,dst_str_end);
  dst_str = ToStringHelper("]=",dst_str,dst_str_end);
  if ( 0 == a )
    dst_str = ToStringHelper("null",dst_str,dst_str_end);
  else
  {
    dst_str = ToStringHelper("(",dst_str,dst_str_end);
    if ( ON_UNSET_UINT_INDEX == count )
    {
      dst_str = ToStringHelper("?",dst_str,dst_str_end);
    }
    else
    {
      imax = (count <= 7 ? count : 4 );
      for ( i = 0; i < imax; i++ )
      {
        if ( i )
          dst_str = ToStringHelper(",",dst_str,dst_str_end);
        dst_str = ToStringHelper(a[i],dst_str,dst_str_end);
      }
      if ( i < count )
      {
        dst_str = ToStringHelper(",...,",dst_str,dst_str_end);
        dst_str = ToStringHelper(a[count-1],dst_str,dst_str_end);
      }
    }
    dst_str = ToStringHelper(")",dst_str,dst_str_end);
  }

  return dst_str;
}

static char* ToStringHelper( const ON_MeshNgon* ngon, char* buffer, size_t sizeof_buffer)
{
  if ( 0 == buffer || sizeof_buffer <= 0 )
    return 0;

  char* dst_str = buffer;
  char* dst_str_end = dst_str + ((sizeof_buffer/sizeof(buffer[0])) - 1);
  unsigned int capacity;

  if ( 0 == ngon )
    return ToStringHelper("null",dst_str,dst_str_end);
  else
  {
    dst_str = ToStringHelper("m_vi",dst_str,dst_str_end);
    dst_str = ToStringHelper(ngon->m_vi,ngon->m_Vcount,dst_str,dst_str_end);
    dst_str = ToStringHelper(" ",dst_str,dst_str_end);
    dst_str = ToStringHelper("m_fi",dst_str,dst_str_end);
    dst_str = ToStringHelper(ngon->m_fi,ngon->m_Fcount,dst_str,dst_str_end);

    capacity = ngon->Capacity();
    if ( capacity > 0 )
    {
      dst_str = ToStringHelper(" capacity=",dst_str,dst_str_end);
      dst_str = ToStringHelper(capacity,dst_str,dst_str_end);
    }
  }
  return dst_str;
}

ON_String ON_MeshNgon::ToString() const
{
  // supports this == null
  char buffer[256];
  return ( 0 == ToStringHelper(this,buffer,sizeof(buffer)) ) 
         ? ON_String::EmptyString
         : ON_String(buffer);
}

ON_wString ON_MeshNgon::ToWideString() const
{
  // supports this == null
  char buffer[256];
  return ( 0 == ToStringHelper(this,buffer,sizeof(buffer)) ) 
         ? ON_wString::EmptyString
         : ON_wString(buffer);
}

void ON_MeshNgon::Dump( 
  class ON_TextLog& text_log 
  )const
{
  // supports this == null
  char buffer[256];
  if ( 0 != ToStringHelper(this,buffer,sizeof(buffer)) ) 
    text_log.Print("%s",buffer);
}

void ON_MeshNgon::AppendToString( 
  class ON_String& s
  )const
{
  // supports this == null
  char buffer[256];
  if ( 0 != ToStringHelper(this,buffer,sizeof(buffer)) ) 
    s += buffer;
}

void ON_MeshNgon::AppendToString( 
  class ON_wString& s
  )const
{
  // supports this == null
  char buffer[256];
  if ( 0 != ToStringHelper(this,buffer,sizeof(buffer)) ) 
    s += buffer;
}

unsigned int ON_Mesh::NgonUnsignedCount() const
{
  return m_Ngon.UnsignedCount();
}

int ON_Mesh::NgonCount() const
{
  return m_Ngon.Count();
}

const ON_MeshNgon* const * ON_Mesh::Ngons() const
{
  return m_Ngon.Array();
}

const ON_MeshNgon* ON_Mesh::Ngon(
  unsigned int ngon_index
  ) const
{
  return (ngon_index < m_Ngon.UnsignedCount()) ? m_Ngon[ngon_index] : 0;
}


bool ON_Mesh::IsValidNewNgonInformation(
  unsigned int Vcount, 
  const unsigned int* ngon_vi,
  unsigned int Fcount, 
  const unsigned int* ngon_fi
  ) const
{
  unsigned int i;
  const unsigned int meshVcount = m_V.UnsignedCount();
  const unsigned int meshFcount = m_F.UnsignedCount();
  if ( Vcount < 3 )
    return false;

  for ( i = 0; i < Vcount; i++ )
  {
    if ( ngon_vi[i] >= meshVcount )
      return false;
  }

  const unsigned int* ngon_map = (Fcount > 0) ? NgonMap() : 0;

  for ( i = 0; i < Fcount; i++ )
  {
    if ( ngon_fi[i] >= meshFcount )
      return false;
    if ( ngon_map && ON_UNSET_UINT_INDEX != ngon_map[ngon_fi[i]] )
      return false;
  }

  return true;
}

void ON_Mesh::RemoveNgonMap()
{
  m_NgonMap.Destroy();
}

const unsigned int* ON_Mesh::NgonMap() const
{
  if ( m_Ngon.UnsignedCount() > 0 && m_F.UnsignedCount() == m_NgonMap.UnsignedCount() )
    return m_NgonMap.Array();
  return 0;
}

unsigned int ON_Mesh::NgonIndexFromFaceIndex(
  unsigned int face_index
  ) const
{
  unsigned int ngon_index = ON_UNSET_UINT_INDEX;
  const unsigned int meshFcount = m_F.UnsignedCount();
  const unsigned int ngonCount = m_Ngon.UnsignedCount();
  if (face_index < meshFcount && ngonCount > 0)
  {
    if (meshFcount == m_NgonMap.UnsignedCount())
    {
      // fast way - use m_NgonMap[]
      ngon_index = m_NgonMap[face_index];
    }
    else
    {
      // slow way - search
      //  cannot build ngon map without making it a piece of thread safe
      //  cached information.
      for (unsigned int ni = 0; ni < ngonCount; ni++)
      {
        const ON_MeshNgon* ngon = m_Ngon[ni];
        if (0 == ngon || 0 == ngon->m_fi)
          continue;
        for (unsigned int nfi = 0; nfi < ngon->m_Fcount; nfi++)
        {
          if (face_index == ngon->m_fi[nfi])
            return ni;
        }
      }
    }
  }
  return ngon_index;
}

const unsigned int* ON_Mesh::NgonMap(
  bool bCreateIfNeeded
  )
{
  const unsigned int* fdex_to_ndex_map = NgonMap();
  if ( 0 == fdex_to_ndex_map && bCreateIfNeeded )
    fdex_to_ndex_map = CreateNgonMap();
  return fdex_to_ndex_map;
}

bool ON_Mesh::CreateNgonMap(ON_SimpleArray<unsigned int>& map) const
{
  unsigned int* ngon_map = 0;
  const ON_MeshNgon* ngon;
  unsigned int fi;
  unsigned int ngon_index;
  unsigned int j;

  const unsigned int ngon_count = m_Ngon.UnsignedCount();
  
  const unsigned int meshFcount = m_F.UnsignedCount();
  if (meshFcount <= 0)
  {
    map.SetCount(0);
    return false;
  }

  map.Reserve(meshFcount);
  map.SetCount(meshFcount);
  ngon_map = map.Array();

  for ( fi = 0; fi < meshFcount; fi++ )
    ngon_map[fi] = ON_UNSET_UINT_INDEX;
    
  const ON_MeshNgon*const* ngons = m_Ngon.Array();
  for ( ngon_index = 0; ngon_index < ngon_count; ngon_index++ )
  {
    ngon = ngons[ngon_index];
    if ( 0 == ngon || 0 == ngon->m_fi )
      continue;
    for ( j = 0; j < ngon->m_Fcount; j++ )
    {
      fi = ngon->m_fi[j];
      if (fi < meshFcount)
      {
        if (ON_UNSET_UINT_INDEX == ngon_map[fi])
          ngon_map[fi] = ngon_index;
        else
        {
          ON_ERROR("mesh face referenced more than one time by an ngon.");
        }
      }
    }
  }

  return true;
}

bool ON_Mesh::CreateNgonMap(unsigned int* map) const
{
  ON_SimpleArray<unsigned int> new_map {};
  new_map.SetArray(map, m_F.Count(), m_F.Count());
  
  if (!CreateNgonMap(new_map)) return false;
  new_map.KeepArray();
  return true;
}

const unsigned int* ON_Mesh::CreateNgonMap()
{
  if (!CreateNgonMap(m_NgonMap)) return nullptr;

  return m_NgonMap.Array();
}



bool ON_Mesh::ModifyNgon(
  unsigned int ngon_index,
  unsigned int Vcount, 
  const unsigned int* ngon_vi,
  unsigned int Fcount, 
  const unsigned int* ngon_fi
  )
{
  ON_MeshNgon ngon;
  ngon.m_Vcount = Vcount;
  ngon.m_vi = (unsigned int*)ngon_vi;
  ngon.m_Fcount = Fcount;
  ngon.m_fi = (unsigned int*)ngon_fi;
  bool rc = ModifyNgon(ngon_index,&ngon);
  ngon.m_vi = 0;
  ngon.m_fi = 0;
  return rc;
}

bool ON_Mesh::InsertNgon(
  unsigned int ngon_index,
  const ON_MeshNgon* ngon
  )
{
  if ( ngon_index >= ON_UNSET_UINT_INDEX )
    return false;

  if ( ngon_index >= m_Ngon.UnsignedCount() )
  {
    SetNgonCount(ngon_index+1);
  }
  else
  {
    bool bUpdateNgonMap = (m_NgonMap.UnsignedCount() == m_F.UnsignedCount());
    m_Ngon.Insert(ngon_index,0);
    if (bUpdateNgonMap)
      CreateNgonMap();
  }
  return ModifyNgon(ngon_index,ngon);
}

bool ON_Mesh::ModifyNgon(
  unsigned int ngon_index,
  const ON_MeshNgon* ngon
  )
{
  ON_MeshNgon* ngon1 = 0;
  
  if ( ngon_index >= m_Ngon.UnsignedCount() )
    return false;
  
  if ( m_Ngon[ngon_index] )
    RemoveNgon(ngon_index);

  if ( 0 == ngon )
    return true;

  if ( 0 == ngon->m_Vcount || 0 == ngon->m_Fcount )
    return true;

  if ( IsValidNewNgonInformation(ngon->m_Vcount,ngon->m_vi,ngon->m_Fcount,ngon->m_fi) )
  {
    ngon1 = m_NgonAllocator.CopyNgon(ngon);
    if ( ngon1 )
    {
      const unsigned int meshFcount = m_F.UnsignedCount();
      unsigned int* ngon_map = (meshFcount > 0 && meshFcount == m_NgonMap.UnsignedCount()) ? m_NgonMap.Array() : 0;
      if ( ngon_map )
      {
        for ( unsigned j = 0; j < ngon->m_Fcount; j++ )
        {
          unsigned int fi = ngon->m_fi[j];
          if ( fi < meshFcount )
            ngon_map[fi] = ngon_index;
        }
      }

      m_Ngon[ngon_index] = ngon1;
      return true;
    }
  }

  return false;
}

static bool Internal_ListContainNgon(
  unsigned int count,
  const int* fi,
  ON_SimpleArray< const ON_MeshNgon* >& tested_ngons, 
  const ON_MeshNgon* ngon
)
{
  if (nullptr == ngon || ngon->m_Fcount <= 0)
    return true; // nothing to test.

  if (ngon->m_Fcount > count)
    return false;

  if (tested_ngons.Search(ngon) >= 0)
    return true; // already tested this ngon

  // fi[] is a sorted list
  for (unsigned int k = 0; k < ngon->m_Fcount; ++k)
  {
    if (nullptr == ON_BinarySearchIntArray((int)ngon->m_fi[k], fi, count))
      return false; // ngon->m_fi[k] is not in fi[]
  }

  if (ngon->m_Fcount > 1)
    tested_ngons.Append(ngon); // no need to test this one again

  // Every index in ngon->m_fi[] is also in fi[]
  return true;
}

unsigned int ON_Mesh::AddNgons(
  const ON_SimpleArray<ON_COMPONENT_INDEX>& ci_list
)
{
  const int ci_count = ci_list.UnsignedCount();
  if (ci_count < 2)
    return 0;

  const int face_count = FaceCount();
  if (face_count < 2)
    return 0;
  const int ngon_count = NgonCount();
  const unsigned int ngon_ucount = NgonUnsignedCount();

  /////////////////////
  //
  // fi_list[] = list of faces to be merged into ngons
  ON_SimpleArray<int> fi_list(ci_count);
  ON_COMPONENT_INDEX ci;
  for (int i = 0; i < ci_count; ++i)
  {
    ci = ci_list[i];
    if (ci.m_index < 0)
      continue;
    switch (ci.m_type)
    {
    case ON_COMPONENT_INDEX::TYPE::mesh_face:
      if (ci.m_index < face_count)
        fi_list.Append(ci.m_index);
      break;
    case ON_COMPONENT_INDEX::TYPE::mesh_ngon:
      if (ci.m_index < ngon_count)
      {
        const ON_MeshNgon* ngon = Ngon(ci.m_index);
        if (nullptr == ngon)
          break;
        for (unsigned j = 0; j < ngon->m_Fcount; ++j)
        {
          const int fi = ngon->m_fi[j];
          if (fi >= 0 && fi < face_count)
            fi_list.Append(fi);
        }
      }
      break;
    default:
      break;
    }
  }
  fi_list.QuickSortAndRemoveDuplicates(ON_CompareIncreasing<int>);
  const int fi_count = fi_list.Count();
  if (fi_count < 2)
    return 0;

  /////////////////////
  //
  // Partition fi_list[] into subsets where each subset will be a new ngon.
  const ON_MeshTopology& top = Topology();
  if (face_count != top.m_topf.Count())
    return 0;

  const int edge_count = top.TopEdgeCount();

  ON_SimpleArray<bool> face_available_buffer(face_count);
  face_available_buffer.SetCount(face_count);
  face_available_buffer.Zero();
  bool* face_available = face_available_buffer.Array();

  for (int i = 0; i < fi_count; ++i)
    face_available[fi_list[i]] = true;

  /////////////////////
  //
  // ngon_faces[] is the same set of indiced that are in fi_list[], but with indices for 
  // each new ngon grouped together.
  // ngon_partition[] is used to find the new ngon subsets.
  // If i0 = ngon_partition[j] && i1 = ngon_partition[j+1], then
  // (ngon_faces[i0],...,ngon_faces[i1-1]) are the face indices for a new ngon.
  //
  ON_SimpleArray<int> ngon_faces(fi_count);
  ON_SimpleArray<unsigned int> ngon_partition(64);

  const unsigned int* ngon_map = (ngon_count > 0) ? NgonMap(true) : nullptr;

  ON_SimpleArray< const ON_MeshNgon* > old_ngons_inside_new_ngon(32);

  for (int i = 0; i < fi_count; ++i)
  {
    const int face_index = fi_list[i];
    if (false == face_available[face_index])
      continue; // face is no longer available.

    // find the new ngon contain face_index.
    face_available[face_index] = false;
    const unsigned int count0 = ngon_faces.UnsignedCount();
    unsigned int i0 = 0;
    unsigned int i1 = count0;
    ngon_partition.Append(count0);
    ngon_faces.Append(face_index);
    for (;;)
    {
      i0 = i1;
      i1 = ngon_faces.Count();
      if (i0 >= i1)
        break;
      for (/*empty init*/; i0 < i1; ++i0)
      {
        const int fi = ngon_faces[i0];
        const ON_MeshTopologyFace& topf = top.m_topf[fi];
        const int fe_count = topf.IsQuad() ? 4 : 3;
        for (int fei = 0; fei < fe_count; ++fei)
        {
          int ei = topf.m_topei[fei];
          if (ei < 0 || ei >= edge_count)
            continue;
          const ON_MeshTopologyEdge& tope = top.m_tope[ei];
          if (2 != tope.m_topf_count)
            continue;
          if (2 != tope.m_topf_count || false == top.IsWeldedEdge(ei))
            continue;
          int neighbor_fi = tope.m_topfi[(fi == tope.m_topfi[0]) ? 1 : 0];
          if (neighbor_fi < 0 || neighbor_fi >= face_count || false == face_available[neighbor_fi])
            continue;
          face_available[neighbor_fi] = false;
          ngon_faces.Append(neighbor_fi);
        }
      }
    }

    const unsigned new_ngon_F_count = ngon_faces.UnsignedCount() - count0;
    int* new_ngon_fi = ngon_faces.Array() + count0;
    ON_SortIntArray(ON::sort_algorithm::quick_sort, new_ngon_fi, new_ngon_F_count);
    bool bSkipNewNgon = (new_ngon_F_count < 2);
    if (false == bSkipNewNgon && nullptr != ngon_map)
    {
      old_ngons_inside_new_ngon.SetCount(0);

      // Make sure the new ngon doesn't contain proper subsets of existing ngons.
      for (unsigned j = 0; j < new_ngon_F_count; ++j)
      {
        int fi = new_ngon_fi[j];
        const unsigned int ngon_dex = ngon_map[fi];
        if (ngon_dex >= ngon_ucount)
          continue;
        const ON_MeshNgon* existing_ngon = Ngon(ngon_dex);
        if (nullptr == existing_ngon)
          continue;
        if (false == Internal_ListContainNgon(new_ngon_F_count, new_ngon_fi, old_ngons_inside_new_ngon, existing_ngon))
        {
          // existing ngon has faces that are not in new ngon.
          bSkipNewNgon = true;
          break;
        }
        if (existing_ngon->m_Fcount == new_ngon_F_count)
        {
          // new ngon and existing ngon are the same.
          bSkipNewNgon = true;
          break;
        }
      }
    }
    if (bSkipNewNgon)
    {
      ngon_faces.SetCount(count0);
      ngon_partition.Remove();
    }
  }

  if (ngon_partition.UnsignedCount() < 1 || ngon_faces.UnsignedCount() < 2)
    return 0;

  ngon_partition.Append(ngon_faces.UnsignedCount());

  bool bRemoveddNgons = false;
  if (nullptr != ngon_map)
  {
    // Delete ngons that are being merged into bigger ngons
    ON_SimpleArray<bool> delete_old_ngon(ngon_count);
    delete_old_ngon.SetCount(ngon_count);
    for (int j = 0; j < ngon_faces.Count(); ++j)
    {
      unsigned ngon_dex = ngon_map[ngon_faces[j]];
      if (ngon_dex < ngon_ucount)
        delete_old_ngon[ngon_dex] = true;
    }
    for (int j = ngon_count; j > 0; --j)
    {
      unsigned int ngon_dex = (unsigned int)(j - 1);
      if (delete_old_ngon[ngon_dex])
      {
        RemoveNgon(ngon_dex);
        bRemoveddNgons = true;
      }
    }
  }

  // Add new ngons
  unsigned int new_ngon_count = 0;
  unsigned int i1 = ngon_partition[0];
  for (unsigned int i = 1; i < ngon_partition.UnsignedCount(); ++i)
  {
    const unsigned int i0 = i1;
    i1 = ngon_partition[i];
    if (i0 + 2 <= i1)
    {
      if (AddNgon(i1 - i0, (const unsigned int*)(ngon_faces.Array() + i0)) >= 0)
        ++new_ngon_count;
    }
  }

  if (bRemoveddNgons || new_ngon_count > 0)
  {
    // clean up ngon storage
    m_NgonMap.SetCount(0);
    int count = 0;
    for (int i = 0; i < m_Ngon.Count(); ++i)
    {
      ON_MeshNgon* n = m_Ngon[i];
      if (nullptr == n)
        continue;
      m_Ngon[count++] = n;
    }
    m_Ngon.SetCount(count);
    NgonMap(true);
  }

  return new_ngon_count;
}

int ON_Mesh::AddNgon(const ON_SimpleArray<unsigned int>& ngon_fi)
{
  return AddNgon(ngon_fi.UnsignedCount(), ngon_fi.Array());
}

int ON_Mesh::AddNgon(const ON_SimpleArray<unsigned int>& ngon_fi, bool bPermitHoles)
{
  return AddNgon(ngon_fi.UnsignedCount(), ngon_fi.Array(), bPermitHoles);
}

int ON_Mesh::AddNgon(
  unsigned int Fcount,
  const unsigned int* ngon_fi
)
{
  return AddNgon(Fcount, ngon_fi, false);
}

int ON_Mesh::AddNgon(
  unsigned int Fcount,
  const unsigned int* ngon_fi,
  bool bPermitHoles
)
{
  ON_MeshVertexFaceMap* vertexFaceMap = nullptr;
  return AddNgon_Expert(Fcount, ngon_fi, bPermitHoles, vertexFaceMap);
}

int ON_Mesh::AddNgon_Expert(
  unsigned int Fcount,
  const unsigned int* ngon_fi,
  bool bPermitHoles,
  ON_MeshVertexFaceMap* vertexFaceMap
)
{
  unsigned int ngon_index = ON_UNSET_UINT_INDEX;
  if (Fcount < 1 || nullptr == ngon_fi)
    return ngon_index;

  ON_SimpleArray<unsigned int> ngon_vi;
  const ON_3dPointListRef mesh_vertex_list(this);
  const ON_MeshFaceList& mesh_face_list(this);

  const int face_count = m_F.Count();
  const unsigned int ngon_count0 = HasNgons() ? NgonUnsignedCount() : 0U;
  bool bCheckNgonMap = (ngon_count0 > 0 && face_count == m_NgonMap.Count());
  for (unsigned int i = 0; i < Fcount; ++i)
  {
    unsigned int fi = ngon_fi[i];
    if (fi >= (unsigned int)face_count)
      return ngon_index;
    if (bCheckNgonMap && m_NgonMap[fi] < ngon_count0)
      return ngon_index; // input faces are already in an ngon
  }

  unsigned int vi_count;
  if (bPermitHoles)
    vi_count = ON_MeshNgon::FindNgonBoundary(
      mesh_vertex_list,
      mesh_face_list,
      vertexFaceMap,
      Fcount,
      ngon_fi,
      ngon_vi
    );
  else
    vi_count = ON_MeshNgon::FindNgonOuterBoundary(
      mesh_vertex_list,
      mesh_face_list,
      vertexFaceMap,
      Fcount,
      ngon_fi,
      ngon_vi
    );

  if (vi_count < 3 || ngon_vi.Count() < 3)
    return ngon_index; // 

  return AddNgon(ngon_vi.UnsignedCount(), ngon_vi.Array(), Fcount, ngon_fi);
}

int ON_Mesh::AddNgon(
  unsigned int Vcount, 
  const unsigned int* ngon_vi,
  unsigned int Fcount, 
  const unsigned int* ngon_fi
  )
{
  unsigned int ngon_index = ON_UNSET_UINT_INDEX;
  for(;;)
  {
    if ( Vcount < 3 )
      break;
    if ( 0 == ngon_vi )
      break;
    if ( Fcount <= 0 )
      break;
    if ( 0 == ngon_fi )
      break;

    ON_MeshNgon* ngon = m_NgonAllocator.AllocateNgon(Vcount,Fcount);
    if ( 0 == ngon )
      break;
    memcpy(ngon->m_vi,ngon_vi,ngon->m_Vcount*sizeof(ngon->m_vi[0]));
    memcpy(ngon->m_fi,ngon_fi,ngon->m_Fcount*sizeof(ngon->m_fi[0]));
    ngon_index = AddNgon(ngon);
    break;
  }

  return ngon_index;
}

bool ON_Mesh::OrientNgons(bool bPermitHoles)
{
  bool rc = true;
  for (;;)
  {
    const unsigned int ngon_count = m_Ngon.UnsignedCount();
    if (0 == ngon_count)
      break;

    ON_MeshNgon** ngons = m_Ngon.Array();
    if (0 == ngons)
      break;

    const ON_MeshFaceList face_list = ON_MeshFaceList(this);
    for (unsigned int ni = 0; ni < ngon_count; ni++)
    {
      ON_MeshNgon* ngon = ngons[ni];
      if (nullptr == ngon)
        continue;
      if (0 == ngon->m_Fcount && 0 == ngon->m_Vcount)
        continue;
      const int ngon_orientation = ngon->Orientation(face_list,bPermitHoles);
      if (1 == ngon_orientation)
      {
        continue;
      }
      if (-1 == ngon_orientation)
      {
        ngon->ReverseOuterBoundary();
        continue;
      }
      rc = false; // ngon cannot be oriented
    }
    break;
  }
  return rc; 

}

void ON_MeshNgon::ReverseOuterBoundary()
{
  if (m_Vcount < 3 || nullptr == m_vi)
    return;
  unsigned int vi;
  unsigned int i0 = 1;
  unsigned i1 = m_Vcount - 1;
  while (i0 < i1)
  {
    vi = m_vi[i0];
    m_vi[i0] = m_vi[i1];
    m_vi[i1] = vi;
    i0++;
    i1--;
  }
}

void ON_Mesh::FlipNgonOrientation()
{
  const unsigned int ngon_count = m_Ngon.UnsignedCount();
  if ( 0 == ngon_count )
    return;
  ON_MeshNgon** ngons = m_Ngon.Array();
  if ( 0 == ngons )
    return;
  for (unsigned int ni = 0; ni < ngon_count; ni++)
  {
    ON_MeshNgon* ngon = ngons[ni];
    if (nullptr == ngon || ngon->m_Vcount <= 0)
      continue;
    ngon->ReverseOuterBoundary();
  }
}




bool ON_Mesh::RemoveNgon(
  unsigned int ngon_index
  )
{
  return (1==RemoveNgons(1,&ngon_index));
}

unsigned int ON_Mesh::RemoveNgons(
  unsigned int ngon_index_count,
  const unsigned int* ngon_index_list
  )
{
  if ( ngon_index_count <= 0 || 0 == ngon_index_list )
    return 0;
  const unsigned int ngon_count = m_Ngon.UnsignedCount();
  if ( 0 == ngon_count )
    return 0;
  ON_MeshNgon** ngons = m_Ngon.Array();
  if ( 0 == ngons )
    return 0;

  unsigned int removed_count = 0;
  unsigned int i, k, ngon_index, face_index;
  const unsigned int* fi;
  ON_MeshNgon* ngon;
  const unsigned int meshFcount = m_F.UnsignedCount();
  unsigned int* ngon_map = ( meshFcount == m_NgonMap.UnsignedCount() ) ? m_NgonMap.Array() : 0;
  for ( k = 0; k < ngon_index_count; k++ )
  {
    ngon_index = ngon_index_list[k];
    if (ngon_index >= ngon_count )
      continue;
    ngon = ngons[ngon_index];
    if ( 0 == ngon )
      continue;
    ngons[ngon_index] = 0;
    fi = (const unsigned int*)ngon->m_fi;
    if ( 0 != fi )
    {
      if ( ngon_map )
      {
        for ( i = 0; i < ngon->m_Fcount; i++ )
        {
          face_index = fi[i];
          if ( face_index < meshFcount && ngon_map[face_index] == ngon_index )
            ngon_map[face_index] = ON_UNSET_UINT_INDEX;
        }
      }
    }

    m_NgonAllocator.DeallocateNgon(ngon);
    removed_count++;
  }

  return removed_count;
}

ON_3dPoint ON_Mesh::NgonCenter(unsigned int ngon_index) const
{
  return NgonCenter(ngon_index < m_Ngon.UnsignedCount() ? m_Ngon[ngon_index] : 0);
}

ON_3dPoint ON_Mesh::NgonCenter(const ON_MeshNgon* ngon) const
{
  ON_3dPoint center(ON_3dPoint::UnsetPoint);
  if ( 0 != ngon && ngon->m_Vcount > 0 && 0 != ngon->m_vi )
  {
    ON_3dPointListRef mesh_vertex_list;
    mesh_vertex_list.SetFromMesh(this);
    const unsigned int meshVcount = mesh_vertex_list.PointCount();
    if ( meshVcount > 0 )
    {
      ON_3dPoint P;
      double count = 0.0;
      for ( unsigned int i = 0; i < ngon->m_Vcount; i++ )
      {
        unsigned int vi = (unsigned int)ngon->m_vi[i];
        if ( vi < meshVcount )
        {
          mesh_vertex_list.GetPoint(vi,&P.x);
          if ( 0.0 == count )
          {
            center = P;
            count = 1.0;
          }
          else
          {
            center += P;
            count += 1.0;
          }
        }
      }
      if ( count > 0.0 )
        center /= count;
    }
  }
  return center;
}

ON_BoundingBox ON_Mesh::NgonBoundaryBoundingBox(unsigned int ngon_index) const
{
  return NgonBoundaryBoundingBox(ngon_index < m_Ngon.UnsignedCount() ? m_Ngon[ngon_index] : 0);
}

ON_BoundingBox ON_Mesh::NgonBoundaryBoundingBox(const ON_MeshNgon* ngon) const
{
  ON_BoundingBox bbox;
  ON_3dPointListRef mesh_vertex_list;
  mesh_vertex_list.SetFromMesh(this);
  const unsigned int meshVcount = mesh_vertex_list.PointCount();
  if ( meshVcount > 0 )
  {
    if ( 0 != ngon && ngon->m_Vcount > 0 && 0 != ngon->m_vi )
    {
      ON_3dPoint P;
      bool bGrow = false;
      for ( unsigned int i = 0; i < ngon->m_Vcount; i++ )
      {
        unsigned int vi = ngon->m_vi[i];
        if ( vi < meshVcount )
        {
          mesh_vertex_list.GetPoint(vi,&P.x);
          if ( bbox.Set(P,bGrow) )
            bGrow = true;
        }
      }
    }
  }
  return bbox;
}

unsigned int ON_MeshNgon::GetOuterBoundaryPoints(
  const class ON_3dPointListRef& mesh_vertex_list,
  bool bAppendStartPoint,
  ON_SimpleArray<ON_3dPoint>& ngon_boundary_points
  ) const
{  
  if ( m_Vcount > 0 )
  {
    ngon_boundary_points.Reserve(bAppendStartPoint ? (m_Vcount+1) : m_Vcount);
    ngon_boundary_points.SetCount( GetOuterBoundaryPoints(mesh_vertex_list,bAppendStartPoint,ngon_boundary_points.Array()) );
  }
  else
  {
    ngon_boundary_points.SetCount(0);
  }
  return ngon_boundary_points.UnsignedCount();
}

unsigned int ON_MeshNgon::GetOuterBoundaryPoints(
  const class ON_3dPointListRef& mesh_vertex_list,
  bool bAppendStartPoint,
  ON_3dPoint* ngon_boundary_points
  ) const
{
  if ( m_Vcount <= 0 || 0 == m_vi )
    return 0;

  const unsigned int meshVcount = mesh_vertex_list.PointCount();
  if ( meshVcount <= 0 )
    return 0;

  for ( unsigned int i = 0; i < m_Vcount; i++ )
  {
    unsigned int vi = m_vi[i];
    if ( vi >= meshVcount )
      return 0;
    mesh_vertex_list.GetPoint(vi,&ngon_boundary_points[i].x);
  }
  
  if ( bAppendStartPoint )
  {
    ngon_boundary_points[m_Vcount] = ngon_boundary_points[0];
    return (m_Vcount+1);
  }

  return m_Vcount;
}

unsigned int ON_Mesh::GetNgonBoundaryPoints(
  const ON_MeshNgon* ngon,
  bool bAppendStartPoint,
  ON_SimpleArray<ON_3dPoint>& ngon_boundary_points
  ) const
{
  if ( ngon )
  {
    ON_3dPointListRef mesh_vertex_list;
    mesh_vertex_list.SetFromMesh(this);
    return ngon->GetOuterBoundaryPoints(mesh_vertex_list,bAppendStartPoint,ngon_boundary_points);
  }
  ngon_boundary_points.SetCount(0);
  return 0;
}

unsigned int ON_Mesh::GetNgonBoundaryPoints(
  const ON_MeshNgon* ngon,
  bool bAppendStartPoint,
  ON_3dPoint* ngon_boundary_points
  ) const
{
  if ( ngon )
  {
    ON_3dPointListRef mesh_vertex_list;
    mesh_vertex_list.SetFromMesh(this);
    return ngon->GetOuterBoundaryPoints(mesh_vertex_list,bAppendStartPoint,ngon_boundary_points);
  }
  return 0;
}

void ON_Mesh::SetNgonCount(
  unsigned int ngon_count
  )
{
  if ( ngon_count <= 0 )
  {
    m_NgonMap.Destroy();
    m_Ngon.Destroy();
    m_NgonAllocator.DeallocateAllNgons();
    return;
  }

  unsigned int ngon_count0 = m_Ngon.UnsignedCount();
  ON_MeshNgon** a;
  
  if ( ngon_count > ngon_count0 )
  {
    m_Ngon.Reserve(ngon_count);
    m_Ngon.SetCount(ngon_count);
    a = m_Ngon.Array();
    if ( a )
    {
      memset(a+ngon_count0,0,(ngon_count-ngon_count0)*sizeof(a[0]));
    }
    return;
  }
  
  if ( ngon_count < ngon_count0 )
  {
    bool bUpdateNgonMap = (m_NgonMap.UnsignedCount() == ngon_count0);
    a = m_Ngon.Array();
    if ( bUpdateNgonMap && 2*ngon_count >=  ngon_count0 )
    {
      // less expensive to clean up map array
      while ( --ngon_count0 >= ngon_count )
      {
        if ( a[ngon_count0] )
          RemoveNgon(ngon_count0);
      }
    }
    else
    {
      // less expensive to recalculate map array
      while ( --ngon_count0 >= ngon_count )
      {
        if ( a[ngon_count0] )
        {

          m_NgonAllocator.DeallocateNgon(a[ngon_count0]);
          a[ngon_count0] = 0;
        }
      }
      m_Ngon.SetCount(ngon_count);
      if ( bUpdateNgonMap )
        CreateNgonMap();
      else
        m_NgonMap.SetCount(0);
    }

    return;
  }

  return;
}

void ON_Mesh::RemoveEmptyNgons()
{
  ON_MeshNgon* ngon;
  ON_MeshNgon** ngons = m_Ngon.Array();
  const unsigned int ngon_count0 = m_Ngon.UnsignedCount();
  unsigned int ngon_count1 = 0;
  unsigned int i;

  for ( i = 0; i < ngon_count0; i++ )
  {
    ngon = ngons[i];
    if ( 0 == ngon )
      continue;
    if ( 0 != ngon && ngon->m_Vcount > 0 && 0 != ngon->m_vi && ngon->m_Fcount > 0 && 0 != ngon->m_fi)
    {
      if (i > ngon_count1 )
        ngons[ngon_count1] = ngons[i];
      ngon_count1++;
    }
    else
    {
      ngons[i] = 0;
      m_NgonAllocator.DeallocateNgon(ngon);
    }
  }

  if ( ngon_count1 < ngon_count0 )
  {
    m_Ngon.SetCount(ngon_count1);
    if ( ngon_count0 == m_NgonMap.UnsignedCount() )
      CreateNgonMap();
    else
      m_NgonMap.SetCount(0);
  }

  return;
}

void ON_Mesh::RemoveAllNgons()
{
  SetNgonCount(0);
}

ON_MeshNgon* ON_Mesh::AllocateNgon(
  unsigned int Vcount, 
  unsigned int Fcount
  )
{
  ON_MeshNgon* ngon = m_NgonAllocator.AllocateNgon(Vcount,Fcount);
  if ( ngon  )
  {
    if ( ngon->m_Vcount > 0 )
      memset(ngon->m_vi,0xFF,ngon->m_Vcount*sizeof(ngon->m_vi[0]));
    if ( ngon->m_Fcount > 0 )
      memset(ngon->m_fi,0xFF,ngon->m_Fcount*sizeof(ngon->m_fi[0]));
  }
  return ngon;
}

bool ON_Mesh::DeallocateNgon(
  ON_MeshNgon* ngon
  )
{
  return m_NgonAllocator.DeallocateNgon(ngon);
}

unsigned int ON_Mesh::AddNgon(
  ON_MeshNgon* ngon
  )
{
  int ngon_index = ON_UNSET_UINT_INDEX;

  if ( ngon )
  {
    ngon_index = m_Ngon.Count();
    const unsigned int meshFcount = m_F.UnsignedCount();
    if ( meshFcount <= 0 && ngon->m_Fcount > 0 )
      return ON_UNSET_UINT_INDEX;

    if ( meshFcount > 0 )
    {
      unsigned int fi;
      unsigned int* ngon_map;
      if ( 0 == ngon_index )
      {
        m_NgonMap.Reserve(meshFcount);
        m_NgonMap.SetCount(meshFcount);
        ngon_map = m_NgonMap.Array();
        if ( 0 != ngon_map )
          memset(ngon_map,0xFF,m_NgonMap.SizeOfArray());
      }
      else if ( meshFcount == m_NgonMap.UnsignedCount() )
        ngon_map = m_NgonMap.Array();
      else
        ngon_map = 0;

      if ( 0 != ngon_map )
      {
        for ( unsigned int i = 0; i < ngon->m_Fcount; i++ )
        {
          fi = ngon->m_fi[i];
          if ( fi >= meshFcount )
          {
            // clean up ngon_map
            for ( i = 0; i < ngon->m_Fcount; i++ )
            {
              fi = ngon->m_fi[i];
              if ( fi < meshFcount )
                ngon_map[fi] = ON_UNSET_UINT_INDEX;
            }
            return ON_UNSET_UINT_INDEX;
          }
          ngon_map[fi] = ngon_index;
        }
      }
      else
        m_NgonMap.SetCount(0);
    }
    m_Ngon.Append(ngon);
  }
  return ngon_index;
}



struct ON_MeshNgonLink
{
  struct ON_MeshNgonLink* next;
  struct ON_MeshNgonLink* prev;
};

static size_t SizeofNgon(unsigned int capacity)
{
  return sizeof(ON_MeshNgon) + (capacity+1)*sizeof(unsigned int);
}

ON_MeshNgonAllocator::ON_MeshNgonAllocator() ON_NOEXCEPT
  : m_31(0)
  , m_63(0)
  , m_active(0)
{}

ON_MeshNgonAllocator::~ON_MeshNgonAllocator()
{
  void DeallocateAllNgons();
}

ON_MeshNgon* ON_MeshNgonAllocator::CopyNgon(
    const ON_MeshNgon* ngon
    )
{
  ON_MeshNgon* ngon_copy = AllocateNgon(ngon->m_vi ? ngon->m_Vcount : 0,ngon->m_fi ? ngon->m_Fcount : 0);
  if ( ngon_copy )
  {
    if ( ngon_copy->m_Vcount > 0 )
      memcpy(ngon_copy->m_vi,ngon->m_vi,ngon_copy->m_Vcount*sizeof(ngon_copy->m_vi[0]));
    if ( ngon_copy->m_Fcount > 0 )
      memcpy(ngon_copy->m_fi,ngon->m_fi,ngon_copy->m_Fcount*sizeof(ngon_copy->m_fi[0]));
  }
  return ngon_copy;
}

ON_MeshNgon* ON_MeshNgonAllocator::AllocateNgon(
  unsigned int Vcount,
  unsigned int Fcount
  )
{
  struct ON_MeshNgonLink* link;
  ON_MeshNgon* ngon;
  unsigned int* a;
  unsigned int capacity;

  if ( Vcount < 3  )
    return 0;

  capacity = Vcount+Fcount;
  if ( capacity <= 7 )
  {
    capacity = 7;
    if ( SizeofNgon(capacity) != m_7.SizeofElement() )
      m_7.Create(SizeofNgon(capacity),0,0);
    ngon = (ON_MeshNgon*)m_7.AllocateElement();
  }
  else if ( capacity <= 15 )
  {
    capacity = 15;
    if ( SizeofNgon(capacity) != m_15.SizeofElement() )
      m_15.Create(SizeofNgon(capacity),0,0);
    ngon = (ON_MeshNgon*)m_15.AllocateElement();
  }
  else 
  {
    for(;;)
    {
      link = 0;
      if ( capacity <= 31 )
      {
        capacity = 31;
        if ( 0 != m_31 )
        {
          link = (struct ON_MeshNgonLink*)m_31;
          m_31 = link->next;
          break;
        }
      }
      else if ( capacity <= 63 )
      {
        capacity = 63;
        if ( 0 != m_63 )
        {
          link = (struct ON_MeshNgonLink*)m_63;
          m_63 = link->next;
          break;
        }
      }
      else
      {
        // make capacity % 8 = 7
        unsigned int n = (capacity % 8);
        capacity += (7-n);
      }
      link = (struct ON_MeshNgonLink*)onmalloc(sizeof(*link) + SizeofNgon(capacity));
      break;
    }
    if ( 0 == link )
      return 0;
    ngon = (ON_MeshNgon*)(link+1);
    link->next = (struct ON_MeshNgonLink*)m_active;
    if ( link->next )
      link->next->prev = link;
    link->prev = 0;
    m_active = link;
  }

  if ( 0 != ngon )
  {
    a = (unsigned int*)(ngon+1);
    *a++ = capacity;
    ngon->m_vi = a;
    ngon->m_fi = (Fcount > 0) ? (ngon->m_vi + Vcount) : 0;
    ngon->m_Vcount = Vcount;
    ngon->m_Fcount = Fcount;
    //memset(a,0xFF,capacity*sizeof(a[0])); // almost always a waste of time - user must init
  }

  return ngon;
}

ON_MeshNgon* ON_MeshNgonAllocator::ReallocateNgon(
  ON_MeshNgon* ngon,
  unsigned int Vcount,
  unsigned int Fcount
  )
{
  if ( 0 == Vcount && 0 == Fcount )
  {
    DeallocateNgon(ngon);
    return 0;
  }
  
  if ( Vcount < 3 )
    return 0;

  if ( 0 == ngon )
    return AllocateNgon(Vcount,Fcount);

  if ( Vcount <= ngon->m_Vcount && Fcount <= ngon->m_Fcount )
  {
    ngon->m_Vcount = Vcount;
    ngon->m_Fcount = Fcount;
    return ngon;
  }

  unsigned int capacity = ngon->Capacity();
  ON_MeshNgon* ngon1 = ( Vcount + Fcount <= capacity ) ? ngon : AllocateNgon(Vcount,Fcount);
  if ( 0 == ngon1 )
    return 0;

  unsigned int* vi = ngon1->m_vi;
  unsigned int* fi = (Fcount > 0) ? (vi + Vcount) : 0;
  unsigned int i, c;

  if ( 0 != fi && (0 == ngon->m_Fcount || 0 != ngon->m_fi) )
  {
    c = Fcount < ngon->m_Fcount ? Fcount : ngon->m_Fcount;
    for ( i = 0; i < c; i++ )
      fi[i] = ngon->m_fi[i];
    for ( i = c; i < Fcount; i++ )
      fi[i] = ON_UNSET_UINT_INDEX;
  }

  if ( 0 != vi && ( 0 == ngon->m_Vcount || 0 != ngon->m_vi) )
  {
    c = Vcount < ngon->m_Vcount ? Vcount : ngon->m_Vcount;
    for ( i = 0; i < c; i++ )
      vi[i] = ngon->m_vi[i];
    for ( i = c; i < Vcount; i++ )
      vi[i] = ON_UNSET_UINT_INDEX;
  }

  ngon1->m_Vcount = Vcount;
  ngon1->m_Fcount = Fcount;
  ngon1->m_vi = vi;
  ngon1->m_fi = fi;

  if (ngon1 != ngon )
    DeallocateNgon(ngon);

  return ngon1;
}


bool ON_MeshNgonAllocator::DeallocateNgon(
  ON_MeshNgon* ngon
  )
{
  struct ON_MeshNgonLink* link;
  unsigned int capacity = ngon ? ngon->Capacity() : 0;
  
  if ( 7 == capacity )
  {
    m_7.ReturnElement(ngon);
    return true;
  }
  
  if ( 15 == capacity )
  {
    m_15.ReturnElement(ngon);
    return true;
  }
  
  if ( 31 == capacity || capacity >= 63 )
  {
    link = ((struct ON_MeshNgonLink*)ngon)-1;

    // remove from active list
    if ( link == m_active )
    {
      if ( link->prev )
        return false;
      m_active = link->next;
    }
    else if ( link->prev )
      link->prev->next = link->next;
    else
      return false;
    if ( link->next )
      link->next->prev = link->prev;

    switch(capacity)
    {
    case 31:
      link->prev = 0;
      link->next = (struct ON_MeshNgonLink*)m_31;
      m_31 = link;     
      break;
    case 63:
      link->prev = 0;
      link->next = (struct ON_MeshNgonLink*)m_63;
      m_63 = link;   
      break;
    default:
      // deallocate heap
      onfree(link);
    }

    return true;
  }

  return false;
}


void ON_MeshNgonAllocator::DeallocateAllNgons()
{
  struct ON_MeshNgonLink* link;
  struct ON_MeshNgonLink* next;
  struct ON_MeshNgonLink* links[3] = {(struct ON_MeshNgonLink*)m_31,(struct ON_MeshNgonLink*)m_63,(struct ON_MeshNgonLink*)m_active};
  m_7.Destroy();
  m_15.Destroy();
  m_31 = 0;
  m_63 = 0;
  m_active = 0;
  for ( int i = 0; i < sizeof(links)/sizeof(links[0]); i++ )
  {
    next = links[i];
    while (next)
    {
      link = next;
      next = next->next;
      onfree(link);
    }
  }
}


#if defined(ON_HAS_RVALUEREF)
ON_MeshNgonAllocator::ON_MeshNgonAllocator(ON_MeshNgonAllocator&& src)
  : m_31(src.m_31)
  , m_63(src.m_63)
  , m_active(src.m_active)
{
  src.m_31 = 0;
  src.m_63 = 0;
  src.m_active = 0;
}

ON_MeshNgonAllocator& ON_MeshNgonAllocator::operator=(ON_MeshNgonAllocator&& src)
{
  if ( this != &src )
  {
    DeallocateAllNgons();
    m_31 = src.m_31;
    m_63 = src.m_63;
    m_active = src.m_active;
    src.m_31 = 0;
    src.m_63 = 0;
    src.m_active = 0;
  }
  return *this;
}

#endif


// DO NOT COPY THIS DEFINE
#define ON_NGON_BOZO_VACCINE

// Do not copy or move the definition of
// the ON_NGON_MEMBLK structure.
struct ON_NGON_MEMBLK
{
#if !defined(ON_NGON_BOZO_VACCINE)
#error You are a bozo!  Read the comments.
#endif
  struct ON_NGON_MEMBLK* next;
};


class ON_V4V5_MeshNgon
{
public:
  // Number of N-gon corners (N >= 3)
  int N;

  // N-gon vertex indices
  // An array of N indices into the mesh's m_V[] vertex array.
  // If the ON_MeshNgon is returned by the ON_V4V5_MeshNgonList::AddNgon()
  // function, then the memory for vi is managed by the ON_V4V5_MeshNgonList
  // class.  
  int* vi;

  // N-gon face indices
  // An array of Fcount indices into the mesh's m_F[] face array.
  // Often, only N-2 indices are used. Unused indices are set to -1.
  // If the ON_MeshNgon is returned by the ON_V4V5_MeshNgonList::AddNgon()
  // function, then the memory for fi is managed by the ON_V4V5_MeshNgonList
  // class.  
  int* fi;
};

class ON_V4V5_MeshNgonList
{
public:
  ON_V4V5_MeshNgonList();
  ~ON_V4V5_MeshNgonList();
  ON_V4V5_MeshNgonList(const ON_V4V5_MeshNgonList&);
  ON_V4V5_MeshNgonList& operator=(const ON_V4V5_MeshNgonList&);


  /*
  Description:
    Add an N-gon to the list
  Parameters:
    N - [in] number of vertices ( >= 5)
    vi - [in] array of N vertex indices into the mesh's m_V[] array.
    fi - [in] array of N face indices into the mesh's m_F[] array.
              Unused indices are set to -1.  In many cases
              there are N-2 valid indices and these are triangles.
  Remarks:
    Adding an N-gon may invalidate any pointers previously
    returned by Ngon.
  */
  bool V4V5_AddNgon(int N, const int* vi, const int* fi);
  class ON_V4V5_MeshNgon* V4V5_AddNgon(int N);

  /*
  Returns:
    Number of Ngons
  */
  int V4V5_NgonCount() const;

  /*
  Parameters:
    Ngon_index - [in] zero based index
  Returns:
    nullptr or a pointer to the Ngon
  */
  ON_V4V5_MeshNgon* V4V5_Ngon(int Ngon_index) const;

  /*
  Description:
    If you know about how many ngons you will need,
    then use the function to reserve space for them.
  */
  bool V4V5_ReserveNgonCapacity(int capacity);

  /*
  Description:
    Destroy N-gon list
  */
  void V4V5_Destroy();

  /*
  Returns:
    Approximate number of bytes used by this class.
  */
  unsigned int V4V5_SizeOf() const;

private:
  int m_ngons_count;
  int m_ngons_capacity;
  ON_V4V5_MeshNgon* m_ngons;
  struct ON_NGON_MEMBLK* m_memblk_list;
};

ON_V4V5_MeshNgonList::ON_V4V5_MeshNgonList()
{
  m_ngons_count = 0;
  m_ngons_capacity = 0;
  m_ngons = 0;
  m_memblk_list = 0; 
}

ON_V4V5_MeshNgonList::~ON_V4V5_MeshNgonList()
{
  V4V5_Destroy();
}

void ON_V4V5_MeshNgonList::V4V5_Destroy()
{
  m_ngons_count = 0;
  m_ngons_capacity = 0;
  if ( 0 != m_ngons )
  {
    onfree(m_ngons);
    m_ngons = 0;
  }
  struct ON_NGON_MEMBLK* p = m_memblk_list;
  m_memblk_list = 0;
  while(p)
  {
    struct ON_NGON_MEMBLK* next = p->next;
    onfree(p);
    p = next;
  }
}


ON_V4V5_MeshNgonList::ON_V4V5_MeshNgonList(const ON_V4V5_MeshNgonList& src)
{
  m_ngons_count = 0;
  m_ngons_capacity = 0;
  m_ngons = 0;
  m_memblk_list = 0; 
  if ( src.m_ngons_count > 0 && 0 != src.m_ngons )
  {
    *this = src;
  }
}


ON_V4V5_MeshNgonList& ON_V4V5_MeshNgonList::operator=(const ON_V4V5_MeshNgonList& src)
{
  if ( this != &src )
  {
    V4V5_Destroy();
    V4V5_ReserveNgonCapacity(src.m_ngons_count);
    for ( int i = 0; i < src.m_ngons_count; i++ )
    {
      const ON_V4V5_MeshNgon& ngon = src.m_ngons[i];
      V4V5_AddNgon(ngon.N,ngon.vi,ngon.fi);
    }
  }
  return *this;
}


bool ON_V4V5_MeshNgonList::V4V5_ReserveNgonCapacity(int capacity)
{
  bool rc = true;
  if ( capacity > m_ngons_capacity )
  {
    m_ngons = (ON_V4V5_MeshNgon*)onrealloc(m_ngons,capacity*sizeof(m_ngons[0]));
    if ( 0 == m_ngons )
    {
      m_ngons_capacity = 0;
      m_ngons_count = 0;
      rc = false;
    }
    else
    {
      m_ngons_capacity = capacity;
    }
  }
  return rc;
}

class ON_V4V5_MeshNgon* ON_V4V5_MeshNgonList::V4V5_AddNgon(int N)
{
  if ( N < 3 || N > 100000 )
    return 0;

  if ( m_ngons_count >= m_ngons_capacity )
  {
    int capacity = 2*m_ngons_count;
    if (capacity < m_ngons_count+16)
      capacity = m_ngons_count+16;
    if ( !V4V5_ReserveNgonCapacity(capacity) )
      return 0;
  }
  ON_V4V5_MeshNgon& ngon = m_ngons[m_ngons_count++];

  ngon.N = N;
  struct ON_NGON_MEMBLK* blk = (struct ON_NGON_MEMBLK*)onmalloc(sizeof(*blk) + (2*N)*sizeof(int));
  if ( 0 == blk )
    return 0;
  ngon.vi = (int*)(blk + 1);
  ngon.fi = ngon.vi + N;
  memset(ngon.vi,0xFF,(2*N)*sizeof(int)); // set all indices to -1
  blk->next = m_memblk_list;
  m_memblk_list = blk;
  return &ngon;
}

bool ON_V4V5_MeshNgonList::V4V5_AddNgon(int N, const int* vi, const int* fi)
{
  if ( 0 == vi || 0 == fi )
    return false;
  class ON_V4V5_MeshNgon* ngon = V4V5_AddNgon(N);
  if ( 0 == ngon )
    return false;
  memcpy(ngon->vi,vi,N*sizeof(ngon->vi[0]));
  memcpy(ngon->fi,fi,N*sizeof(ngon->fi[0]));
  return true;
}

int ON_V4V5_MeshNgonList::V4V5_NgonCount() const
{
  return m_ngons_count;
}

ON_V4V5_MeshNgon* ON_V4V5_MeshNgonList::V4V5_Ngon(int Ngon_index) const
{
  return (Ngon_index < 0 || Ngon_index >= m_ngons_count) ? 0 : m_ngons+Ngon_index;
}


class /* DO NOT EXPORT THIS CLASS */ ON_V4V5_MeshNgonUserData : public ON_UserData
{
#if !defined(ON_NGON_BOZO_VACCINE)
#error You are a bozo!  Read the comments.
#endif
  ON_OBJECT_DECLARE(ON_V4V5_MeshNgonUserData);

public:
  ON_V4V5_MeshNgonUserData();
  ~ON_V4V5_MeshNgonUserData();
  ON_V4V5_MeshNgonUserData(const ON_V4V5_MeshNgonUserData&);
  ON_V4V5_MeshNgonUserData& operator=(const ON_V4V5_MeshNgonUserData&);

  // virtual ON_UserData override
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  unsigned int SizeOf() const override;
  bool Write(ON_BinaryArchive&) const override;
  bool Read(ON_BinaryArchive&) override;

  // virtual ON_UserData override
  bool GetDescription( ON_wString& ) override;
  bool Archive() const override;

public:
  ON_V4V5_MeshNgonList* m_ngon_list;

  // used to validate ngon list.
  // If the information here does not match the
  // information in the mesh, then the ngon list
  // is known to be invalid.
  int m_mesh_F_count;
  int m_mesh_V_count;
};

ON_OBJECT_IMPLEMENT(ON_V4V5_MeshNgonUserData,ON_UserData,"31F55AA3-71FB-49f5-A975-757584D937FF");

ON_V4V5_MeshNgonUserData::ON_V4V5_MeshNgonUserData()
{
  m_userdata_uuid = ON_CLASS_ID(ON_V4V5_MeshNgonUserData);
  m_application_uuid = ON_opennurbs4_id;
  m_userdata_copycount = 1;
  m_ngon_list = 0;
  m_mesh_F_count = 0;
  m_mesh_V_count = 0;
}

ON_V4V5_MeshNgonUserData::~ON_V4V5_MeshNgonUserData()
{
  if ( 0 != m_ngon_list )
  {
    delete m_ngon_list;
    m_ngon_list = 0;
  }
}

ON_V4V5_MeshNgonUserData::ON_V4V5_MeshNgonUserData(const ON_V4V5_MeshNgonUserData& src) 
: ON_UserData(src)
, m_mesh_F_count(src.m_mesh_F_count)
, m_mesh_V_count(src.m_mesh_V_count)
{
  m_ngon_list = (0 != src.m_ngon_list) 
              ? new ON_V4V5_MeshNgonList(*src.m_ngon_list)
              : 0;
}

ON_V4V5_MeshNgonUserData& ON_V4V5_MeshNgonUserData::operator=(const ON_V4V5_MeshNgonUserData& src)
{
  if ( this != &src )
  {
    if (0 != m_ngon_list )
    {
      delete m_ngon_list;
      m_ngon_list = 0;
    }
    ON_UserData::operator=(src);
    if (0 != src.m_ngon_list) 
    {
       m_ngon_list = new ON_V4V5_MeshNgonList(*src.m_ngon_list);
    }
    m_mesh_F_count = src.m_mesh_F_count;
    m_mesh_V_count = src.m_mesh_V_count;
  }
  return *this;
}

bool ON_V4V5_MeshNgonUserData::IsValid( ON_TextLog* text_log ) const
{
  return true;
}

unsigned int ON_V4V5_MeshNgonList::V4V5_SizeOf() const
{
  unsigned int sz = sizeof(*this);
  int icount = 0;
  for ( int i = 0; i < m_ngons_count; i++ )
  {
    icount += 2*m_ngons[i].N;
  }
  sz += m_ngons_capacity*sizeof(m_ngons[0]);
  sz += icount*sizeof(int);
  return sz;
}

unsigned int ON_V4V5_MeshNgonUserData::SizeOf() const
{
  unsigned int sz = ON_UserData::SizeOf();
  if ( 0 != m_ngon_list )
    sz += m_ngon_list->V4V5_SizeOf();
  return sz;
}


bool ON_V4V5_MeshNgonUserData::Write(ON_BinaryArchive& archive) const
{
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,1);
  if (!rc)
    return false;
  for (;;)
  {
    int count = ( 0 == m_ngon_list ) ? 0 : m_ngon_list->V4V5_NgonCount();
    const ON_V4V5_MeshNgon* ngon_array = (count > 0) ? m_ngon_list->V4V5_Ngon(0) : 0;
    if ( 0 == ngon_array )
      count = 0;
    rc = archive.WriteInt(count);
    if (count <= 0 || !rc)
      break;
    for ( int i = 0; i < count; i++ )
    {
      const class ON_V4V5_MeshNgon& ngon = ngon_array[i];

      rc = archive.WriteInt(ngon.N);
      if (!rc)
        break;
      rc = archive.WriteInt(ngon.N,ngon.vi);
      if (!rc)
        break;
      rc = archive.WriteInt(ngon.N,ngon.fi);
      if (!rc)
        break;
    }
    if (!rc)
      break;

    // chunk version 1.1 added face and vertex validation counts.
    rc = archive.WriteInt(m_mesh_F_count);
    if (!rc)
      break;
    rc = archive.WriteInt(m_mesh_V_count);
    if (!rc)
      break;

    break;
  }
  if ( !archive.EndWrite3dmChunk() )
    rc = false;
  return rc;
}

bool ON_V4V5_MeshNgonUserData::Read(ON_BinaryArchive& archive)
{
  if ( 0 != m_ngon_list )
  {
    delete m_ngon_list;
    m_ngon_list = 0;
  }
  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if (!rc)
    return false;
  for (;;)
  {
    rc = (1 == major_version);
    if (!rc)
      break;
    int count = 0;
    rc = archive.ReadInt(&count);
    if (count <= 0 || !rc)
      break;

    m_ngon_list = new ON_V4V5_MeshNgonList();
    if ( 0 == m_ngon_list )
      break;

    m_ngon_list->V4V5_ReserveNgonCapacity(count);

    for ( int i = 0; i < count; i++ )
    {
      int N = 0;
      rc = archive.ReadInt(&N);
      if (!rc)
        break;
      if ( N <= 0 )
        continue;
      class ON_V4V5_MeshNgon* ngon = m_ngon_list->V4V5_AddNgon(N);
      if ( 0 == ngon )
        break;

      rc = archive.ReadInt(N,ngon->vi);
      if (!rc)
        break;
      rc = archive.ReadInt(N,ngon->fi);
      if (!rc)
        break;
      ngon->N = N;
    }
    if (!rc)
      break;

    if ( minor_version >= 1 )
    {
      // chunk version 1.1 added face and vertex validation counts.
      rc = archive.ReadInt(&m_mesh_F_count);
      if (!rc)
        break;
      rc = archive.ReadInt(&m_mesh_V_count);
      if (!rc)
        break;
    }

    break;
  }
  if ( !archive.EndRead3dmChunk() )
    rc = false;
  return rc;
}

// virtual ON_UserData override
bool ON_V4V5_MeshNgonUserData::GetDescription( ON_wString& description )
{
  description = L"Mesh N-gon list";
  return true;
}

bool ON_V4V5_MeshNgonUserData::Archive() const
{
  return ( 0 != m_ngon_list && m_ngon_list->V4V5_NgonCount() > 0 );
}

static
bool ON_ValidateNgon(
  const ON_V4V5_MeshNgon* ngon,
  int mesh_V_count,
  int mesh_F_count
  )
{
  unsigned int j;
  if ( 0 == ngon || ngon->N < 0 )
    return false;
  const unsigned int N = ngon->N;
  for ( j = 0; j < N; j++ )
  {
    if ( ngon->vi[j] < 0 || ngon->vi[j] >= mesh_V_count )
      return false;
    if ( ngon->fi[j] < 0 || ngon->fi[j] >= mesh_F_count )
    {
      if ( -1 == ngon->fi[j] )
      {
        for ( j++; j < N; j++ )
        {
          if ( ngon->vi[j] < 0 || ngon->vi[j] >= mesh_V_count )
            return false;
          if ( -1 != ngon->fi[j] )
            return false;
        }
        break;
      }
      return false;
    }
  }
  return true;
}

static 
bool ON_ValidateMeshNgonUserData(
  ON_V4V5_MeshNgonUserData* ngud,
  const ON_Mesh& mesh
  )
{
  int i;
  if ( 0 == ngud || 0 == ngud->m_ngon_list )
    return false;

  const int mesh_V_count = mesh.m_V.Count();
  const int mesh_F_count = mesh.m_F.Count();

  if ( 0 == ngud->m_mesh_V_count && 0 == ngud->m_mesh_F_count )
  {
    // This is old user data that did not have validation counts
    // saved in the file.

    // Set validation counts to -1 so we never do this slow validation again.
    ngud->m_mesh_V_count = -1;
    ngud->m_mesh_F_count = -1;

    const int ngon_count = ngud->m_ngon_list->V4V5_NgonCount();

    for ( i = 0; i < ngon_count; i++ )
    {
      if ( !ON_ValidateNgon(ngud->m_ngon_list->V4V5_Ngon(i),mesh_V_count,mesh_F_count) )
        return false;
    }

    // Set validation counts to proper values because we will 
    // assume this old ngon information is valid since the indices
    // are in range.  This assumption may not be valid, but
    // at least the ngon won't cause a crash.
    ngud->m_mesh_V_count = mesh_V_count;
    ngud->m_mesh_F_count = mesh_F_count;
  }

  return ( ngud->m_mesh_F_count == mesh_F_count && ngud->m_mesh_V_count == mesh_V_count );
}
                         

const class ON_V4V5_MeshNgonList* ON_Mesh::V4V5_NgonList() const
{
  ON_UserData* ud = GetUserData(ON_CLASS_ID(ON_V4V5_MeshNgonUserData));
  ON_V4V5_MeshNgonUserData* ngud = ON_V4V5_MeshNgonUserData::Cast(ud);
  
  if ( 0 != ngud && !ON_ValidateMeshNgonUserData(ngud,*this) )
  {
    delete ngud;
    ngud = 0;
  }

  return (0 == ngud) ? 0 : ngud->m_ngon_list;
}


class ON_V4V5_MeshNgonList* ON_Mesh::V4V5_ModifyNgonList()
{
  ON_UserData* ud = GetUserData(ON_CLASS_ID(ON_V4V5_MeshNgonUserData));
  ON_V4V5_MeshNgonUserData* ngud = ON_V4V5_MeshNgonUserData::Cast(ud);
  if ( 0 == ngud )
  {
    if ( ud )
    {
      delete ud;
      ud = 0;
    }
    ngud = new ON_V4V5_MeshNgonUserData();
    ngud->m_mesh_F_count = m_F.Count();
    ngud->m_mesh_V_count = m_V.Count();
    AttachUserData(ngud);
  }
  else if ( 0 != ngud->m_ngon_list && !ON_ValidateMeshNgonUserData(ngud,*this) )
  {
    delete ngud->m_ngon_list;
    ngud->m_ngon_list = 0;
  }

  if ( 0 == ngud->m_ngon_list )
  {
    ngud->m_ngon_list = new ON_V4V5_MeshNgonList();
    ngud->m_mesh_F_count = m_F.Count();
    ngud->m_mesh_V_count = m_V.Count();
  }

  return ngud->m_ngon_list;
}


void ON_Mesh::V4V5_DestroyNgonList()
{
  ON_UserData* ud = GetUserData(ON_CLASS_ID(ON_V4V5_MeshNgonUserData));
  if ( 0 != ud )
  {
    delete ud;
    ud = 0;
  }
}

static void InitializeVertexFaceMap(
  ON__UINT_PTR* vertex_face_map,
  unsigned int i0,
  unsigned int i1,
  unsigned int* a
  )
{
  if ( i1 > i0 )
  {
    ON__UINT_PTR vertex_face_count;
    vertex_face_map += i0;
    //i1 -= i0;
    for ( i1 -= i0; i1 > 0; i1-- )
    {
      vertex_face_count = vertex_face_map[0];
      if ( 0 != vertex_face_count )
      {
        a[0] = 0;
        vertex_face_map[0] = (ON__UINT_PTR)a;
        a += (vertex_face_count+1);
      }
      vertex_face_map++;
    }
  }
}

const ON_MeshFaceList ON_MeshFaceList::EmptyFaceList;

ON_MeshFaceList::ON_MeshFaceList(
  const ON_Mesh* mesh
  )
{
  SetFromMesh(mesh);
}

unsigned int ON_MeshFaceList::SetFromTriangleList(
  size_t triangle_count,
  size_t triangle_stride,
  const unsigned int* triangles
  )
{
  if ( triangle_count > 0 && triangle_stride >= 3 && 0 != triangles )
  {
    m_bQuadFaces = false;
    m_face_count = (unsigned int)triangle_count;
    m_face_stride = (unsigned int)triangle_stride;
    m_faces = (const unsigned int*)triangles;
  }
  else
  {
    m_bQuadFaces = false;
    m_face_count = 0;
    m_face_stride = 0;
    m_faces = 0;
  }
  return m_face_count;
}
  
unsigned int ON_MeshFaceList::SetFromQuadList(
  size_t quad_count,
  size_t quad_stride,
  const unsigned int* quads
  )
{
  if ( quad_count > 0 && quad_stride >= 4 && 0 != quads )
  {
    m_bQuadFaces = true;
    m_face_count = (unsigned int)quad_count;
    m_face_stride = (unsigned int)quad_stride;
    m_faces = quads;
  }
  else
  {
    m_bQuadFaces = false;
    m_face_count = 0;
    m_face_stride = 0;
    m_faces = 0;
  }
  return m_face_count;
}

unsigned int ON_MeshFaceList::SetFromMesh(const ON_Mesh* mesh)
{
  if ( 0 != mesh )
  {
    SetFromQuadList(mesh->m_F.UnsignedCount(),4,(const unsigned int*)mesh->m_F.Array());
  }
  else
  {
    SetFromQuadList(0,0,0);
  }
  return m_face_count;
}


unsigned int ON_MeshFaceList::GetVertexIndexInterval(
  unsigned int minimum_valid_vertex_index,
  unsigned int maximum_valid_vertex_index,
  unsigned int* minimum_vertex_index,
  unsigned int* maximum_vertex_index
  ) const
{
  unsigned int vertex0 = 0;
  unsigned int vertex1 = 0;
  unsigned int v0, v1, vi;
  unsigned int valid_face_count = 0;
  for (;;)
  {
    if (0 == m_face_count || m_face_stride < 3 || nullptr == m_faces)
      break;
    const unsigned int face_vertex_count = m_bQuadFaces ? 4 : 3;
    const unsigned int delta_f = m_face_stride - face_vertex_count;
    const unsigned int* f1 = m_faces + (m_face_count*m_face_stride);
    for (const unsigned int* f = m_faces; f < f1; f += delta_f)
    {
      v0 = v1 = *f++;
      vi = *f++;
      if (vi < v0) v0 = vi; else if (vi > v1) v1 = vi;
      vi = *f++;
      if (vi < v0) v0 = vi; else if (vi > v1) v1 = vi;
      if (m_bQuadFaces)
      {
        vi = *f++;
        if (vi < v0) v0 = vi; else if (vi > v1) v1 = vi;
      }
      if (v0 < minimum_valid_vertex_index || v1 > maximum_valid_vertex_index)
        continue;
      if (0 == valid_face_count)
      {
        vertex0 = v0;
        vertex1 = v1;
      }
      else
      {
        if (v0 < vertex0)
          vertex0 = v0;
        if (v1 > vertex1)
          vertex1 = v1;
      }
      valid_face_count++;
    }
    break;
  }
  if (minimum_vertex_index)
    *minimum_vertex_index = vertex0;
  if (maximum_vertex_index)
    *maximum_vertex_index = vertex1;
  return valid_face_count;
}

struct ON_MeshVertexFaceMap_BLK
{
  struct ON_MeshVertexFaceMap_BLK* m_next;
  static const size_t m_target_block_size;
};

// Four pages less a bit for overhead
const size_t ON_MeshVertexFaceMap_BLK::m_target_block_size(4096*4 - sizeof(ON_MeshVertexFaceMap_BLK) - 32);


void* ON_MeshVertexFaceMap::m_alloc(size_t sz)
{
  // The returned pointer is used for arrays of pointers
  // and arrays of unsigned ints.
  // This code will need to be modified if the definition of 
  // struct ON_MeshVertexFaceMap_BLK changes in order to 
  // make certain alignment constraints are met on all
  // "reasonable" CPUs.

  struct ON_MeshVertexFaceMap_BLK* blk;

  if ( sz <= 0 )
    return 0;

  if (sz % sizeof(struct ON_MeshVertexFaceMap_BLK)) 
    sz += sizeof(struct ON_MeshVertexFaceMap_BLK);
  
  blk = new (std::nothrow) ON_MeshVertexFaceMap_BLK[1 + sz/sizeof(struct ON_MeshVertexFaceMap_BLK)];
  
  if ( 0 == blk )
    return 0;

  blk->m_next = (struct ON_MeshVertexFaceMap_BLK*)m_p;
  m_p = blk;
  return (blk+1);
}

void ON_MeshVertexFaceMap::Destroy()
{
  ON_MeshVertexFaceMap_BLK* blk;
  ON_MeshVertexFaceMap_BLK* next;

  blk = (ON_MeshVertexFaceMap_BLK*)m_p;
  
  m_vertex_count = 0;
  m_face_count = 0;
  m_vertex_face_map = 0;
  m_p = 0;

  while ( blk )
  {
    next = blk->m_next;
    delete[] blk;
    blk = next;
  }
}

void ON_MeshVertexFaceMap::m_copy(const ON_MeshVertexFaceMap& src)
{
  const size_t blk_sz = ON_MeshVertexFaceMap_BLK::m_target_block_size;
  size_t sz, delta_sz;

  const unsigned int* const * src_vf_map;
  unsigned int** vf_map;
  unsigned int* a;
  const unsigned int* src_a;
  unsigned int i0, i1, vf_count, a_count;

  for(;;)
  {
    vf_map = 0;
    sz = 0;
    delta_sz = 0;

    vf_count = src.m_vertex_count;
    src_vf_map =  src.m_vertex_face_map;
    
    if ( vf_count <= 0 )
      break;

    if ( 0 == src_vf_map )
      break;

    sz = vf_count*sizeof(vf_map[0]);

    for ( i0 = i1 = 0; i1 < vf_count; i1++)
    {
      if ( nullptr == src_vf_map[i1] || src_vf_map[i1][0] == 0 )
        continue; // 0 faces use vertex i1.
      delta_sz += src_vf_map[i1][0]*sizeof(a[0]);
      if ( sz + delta_sz > blk_sz )
      {
        if ( 0 == vf_map )
        {
          vf_map = (unsigned int**)m_alloc(sz);
          a = (unsigned int*)(vf_map ? (vf_map + vf_count) : 0);
        }
        else
        {
          a = (unsigned int*)m_alloc(sz);
        }
        if ( 0 == a )
          break;
        while(i0 < i1)
        {
          src_a = src_vf_map[i0];
          if ( 0 != src_a && (a_count = src_a[0]) > 0 )
          {
            vf_map[i0] = a;
            *a++ = *src_a++; // count
            *a++ = *src_a++; // initial face index
            while(--a_count > 0 )
              *a++ = *src_a++; // additional face indices
          }
          else
          {
            vf_map[i0] = 0;
          }
          i0++;
        }
        sz = 0;
      }
      sz += delta_sz;
    }

    if ( i0 < i1 && sz > 0 )
    {
      if ( 0 == vf_map )
      {
        vf_map = (unsigned int**)m_alloc(sz);
        a = (unsigned int*)(vf_map ? (vf_map + vf_count) : 0);
      }
      else
      {
        a = (unsigned int*)m_alloc(sz);
      }
      if ( 0 == a )
        break;
      while(i0 < i1)
      {
        src_a = src_vf_map[i0];
        if ( 0 != src_a && (a_count = src_a[0]) > 0 )
        {
          vf_map[i0] = a;
          *a++ = *src_a++; // count
          *a++ = *src_a++; // initial face index
          while(--a_count > 0 )
            *a++ = *src_a++; // additional face indices
        }
        else
        {
          vf_map[i0] = 0;
        }
        i0++;
      }
      sz = 0;
    }

    return; // success
  }

  if ( 0 != vf_map )
    Destroy(); // failure
}

ON_MeshVertexFaceMap::ON_MeshVertexFaceMap() ON_NOEXCEPT
  : m_vertex_count(0)
  , m_face_count(0)
  , m_vertex_face_map(0)
  , m_p(0)
{
}

ON_MeshVertexFaceMap::~ON_MeshVertexFaceMap()
{
  Destroy();
}

ON_MeshVertexFaceMap::ON_MeshVertexFaceMap(const ON_MeshVertexFaceMap& src)
  : m_vertex_count(0)
  , m_face_count(0)
  , m_vertex_face_map(0)
  , m_p(0)
{
  m_copy(src);
}

ON_MeshVertexFaceMap& ON_MeshVertexFaceMap::operator=(const ON_MeshVertexFaceMap& src)
{
  if ( this != &src )
  {
    Destroy();
    m_copy(src);
  }
  return *this;
}


#if defined(ON_HAS_RVALUEREF)
ON_MeshVertexFaceMap::ON_MeshVertexFaceMap( ON_MeshVertexFaceMap&& src) ON_NOEXCEPT
  : m_vertex_count(src.m_vertex_count)
  , m_face_count(src.m_face_count)
  , m_vertex_face_map(src.m_vertex_face_map)
  , m_p(src.m_p)
{
  src.m_vertex_count = 0;
  src.m_face_count = 0;
  src.m_vertex_face_map = 0;
  src.m_p = 0;
}

ON_MeshVertexFaceMap& ON_MeshVertexFaceMap::operator=( ON_MeshVertexFaceMap&& src) ON_NOEXCEPT
{
  if ( this != &src )
  {
    Destroy();

    m_vertex_count = src.m_vertex_count;
    m_face_count = src.m_face_count;
    m_vertex_face_map = src.m_vertex_face_map;
    m_p = src.m_p;

    src.m_vertex_count = 0;
    src.m_face_count = 0;
    src.m_vertex_face_map = 0;
    src.m_p = 0;
  }
  return *this;
}
#endif

bool ON_MeshVertexFaceMap::SetFromMesh(
  const ON_Mesh* mesh,
  bool bMapInvalidFaces
  )
{
  ON_MeshFaceList face_list;

  if ( face_list.SetFromMesh(mesh) > 0 )
  {
    return SetFromFaceList(
      mesh->m_V.UnsignedCount(),
      face_list,
      bMapInvalidFaces
      );
  }

  // failure
  Destroy();
  return false;
}


bool ON_MeshVertexFaceMap::SetFromFaceList(
  unsigned int vertex_count,
  const ON_MeshFaceList& face_list,
  bool bMapInvalidFaces
  )
{
  size_t sz, delta_sz;
  unsigned int* a;
  ON__UINT_PTR* vertex_face_map = 0;
  unsigned int fi, j, k, vi0, vi1, Fvi[4];

  Destroy();

  const unsigned int face_count = face_list.FaceCount();

  
  for(;;)
  {
    const unsigned int max_valid_vertex_count = 0xFFFF0000U;
    if (0 == vertex_count || vertex_count > max_valid_vertex_count)
    {
      if ( face_list.GetVertexIndexInterval(0,max_valid_vertex_count-1,0,&vertex_count) < 1 )
        break;
      vertex_count++;
    }
    if ( vertex_count <= 0  )
      break;
    if ( face_count <= 0  )
      break;
    
    sz = vertex_count*sizeof(vertex_face_map[0]);
    vertex_face_map = (ON__UINT_PTR*)m_alloc(sz);
    if ( 0 == vertex_face_map )
      break;
    memset(vertex_face_map,0,sz);

    // count the number of faces at each vertex
    sz = 0;
    for ( fi = 0; fi < face_count; fi++ )
    {
      face_list.QuadFvi(fi,Fvi);
      k = (Fvi[2]!=Fvi[3]) ? 4 : 3;
      for ( j = 0; j < k; j++ )
      {
        if ( Fvi[j] < vertex_count )
        {
          sz++;
          if ( 0 == vertex_face_map[Fvi[j]]++ )
            sz++;
          continue;
        }
        else if ( !bMapInvalidFaces )
          break; // bogus face
      }
    }

    if ( sz*sizeof(a[0]) <= 4*ON_MeshVertexFaceMap_BLK::m_target_block_size )
    {
      a = (unsigned int*)m_alloc(sz*sizeof(a[0]));
      if ( 0 == a )
        return 0;
      InitializeVertexFaceMap(vertex_face_map,0,vertex_count,a);
    }
    else
    {
      // allocate memory in 4 page chunks
      sz = 0;
      k = 0;
      for ( j = 0; j < vertex_count; j++ )
      {
        if ( vertex_face_map[j] > 0 )
        {
          delta_sz = (vertex_face_map[j]+1)*sizeof(a[0]);
          if ( sz + delta_sz > ON_MeshVertexFaceMap_BLK::m_target_block_size )
          {
            a = (unsigned int*)m_alloc(sz);
            if ( 0 == a )
              return 0;
            InitializeVertexFaceMap(vertex_face_map,k,j,a);
            k = j;
            sz = 0;
          }
          sz += delta_sz;
        }
      }

      if ( sz > 0 )
      {
        a = (unsigned int*)m_alloc(sz);
        if ( 0 == a )
          return 0;
        InitializeVertexFaceMap(vertex_face_map,k,vertex_count,a);
      }
    }

    // Fill in the vertex_face_map[].
    sz = 0; // sz is used to count vertex_face_map[] entries that need to be nulled out
    for ( fi = 0; fi < face_count; fi++ )
    {
      face_list.QuadFvi(fi,Fvi);
      k = (Fvi[2]!=Fvi[3]) ? 3 : 2;
      vi0 = Fvi[3];
      for ( j = 0; j <= k; j++ )
      {
        vi1 = Fvi[j];
        if ( vi0 == vi1 )
        {
          if ( bMapInvalidFaces )
          {
            // caller wants the indices of invalid faces left in the vertex face map
            continue;
          }
        }
        else if ( vi1 < vertex_count )
        {
          a = (unsigned int*)vertex_face_map[vi1];
          vi0 = ++(a[0]); // vi0 temporarily used as an a[] index
          a[vi0] = fi;
          vi0 = vi1; // ... now set vi0 = previous vertex index
          continue;
        }

        // The code in this for loop below this comment
        // is run only when F[fi].vi[] is not valid.

        if ( bMapInvalidFaces )
        {
          // caller wants the indices of invalid faces left in the vertex face map
          continue;
        }

        // The face vertex list F[fi].vi[] is not valid - remove any references to it.
        if ( j > 0 )
        {
          for (k = 0; k < j; k++ )
          {
            a = (unsigned int*)vertex_face_map[Fvi[k]];
            a[0]--;
            if ( 0 == a[0] )
            {
              // If sz > 0, then further cleanup may be required
              // if no other valid faces use this vertex.  This 
              // is done below.
              sz++;
            }
          }
        }
        else if ( vi1 < vertex_count )
        {
          // If mesh face F[fi] is the only face that references the vertex
          // with index vi1 = F[fi].vi[0], then vertex_face_map[vi1] 
          // will be removed.
          a = (unsigned int*)vertex_face_map[vi1];
          if ( 0 != a && 0 == a[0] )
            sz++;
        }
        break;
      }
    }

    if ( sz > 0 )
    {
      // need to check for empty vertex_face_map[] arrays and remove them
      for ( j = 0; j < vertex_count; j++ )
      {
        a = (unsigned int*)vertex_face_map[j];
        if ( 0 != a && 0 == a[0] )
        {
          // Every face that uses this vertex is not valid.
          vertex_face_map[j] = 0;
          sz--;
          if ( 0 == sz )
          {
            // finished with repairs. 
            // Note:
            //   When a vertex is used by both valid and invalid faces,
            //   sz will not return to zero and this loop will terminate with
            //   j == meshVcount.
            break; 
          }
        }
      }
    }

    m_vertex_face_map = (const unsigned int *const*)vertex_face_map;
    m_vertex_count = vertex_count;
    return true;
  }
  
  if ( vertex_face_map )
    Destroy();

  return false;
}


unsigned int ON_MeshVertexFaceMap::VertexCount() const
{
  return m_vertex_count;
}

unsigned int ON_MeshVertexFaceMap::FaceCount() const
{
  return m_face_count;
}

unsigned int ON_MeshVertexFaceMap::VertexFaceCount(
  unsigned int vertex_index
  ) const
{
  const unsigned int* vf_list = (vertex_index < m_vertex_count) ? m_vertex_face_map[vertex_index] : 0;
  return vf_list ? vf_list[0] : 0;
}
  
const unsigned int* ON_MeshVertexFaceMap::VertexFaceList(
  unsigned int vertex_index
  ) const
{
  const unsigned int* vf_list = (vertex_index < m_vertex_count) ? m_vertex_face_map[vertex_index] : 0;
  return (vf_list && vf_list[0] > 0) ? (vf_list+1) : 0;
}

const unsigned int *const* ON_MeshVertexFaceMap::VertexFaceMap() const
{
  return m_vertex_face_map;
}

static bool FaceInPlane(
  double planar_tolerance,
  ON_PlaneEquation e,
  const ON_3dPointListRef& vertex_list,
  const unsigned int Fvi[4]
  )
{
  // Note:
  //   This function is called only with Fvi[] lists that have been checked to
  //   have valid entries.
  double point_buffer[3];

  if ( !(fabs(e.ValueAt(vertex_list.GetPoint(Fvi[0],point_buffer))) <= planar_tolerance) )
    return false;
  if ( !(fabs(e.ValueAt(vertex_list.GetPoint(Fvi[1],point_buffer))) <= planar_tolerance) )
    return false;
  if ( !(fabs(e.ValueAt(vertex_list.GetPoint(Fvi[2],point_buffer))) <= planar_tolerance) )
    return false;
  if ( (Fvi[3] != Fvi[2]) && !(fabs(e.ValueAt(vertex_list.GetPoint(Fvi[3],point_buffer))) <= planar_tolerance) )
    return false;

  return true;
}

static bool GetFacePlaneEquation(
  const ON_3dPointListRef& vertex_list,
  bool bQuadFaces,
  const unsigned int* Fvi,
  double planar_tolerance,
  ON_PlaneEquation& e
  )
{
  // The  P = (ON_3dPoint*)buffer; technique is used to
  // avoid calling constructor code in this performance
  // critical calculation.
  ON_3dPoint* P;
  double buffer[4][3];
  unsigned int i;
  const unsigned int vertex_count = vertex_list.PointCount();
  const unsigned int k = bQuadFaces?4:3;

  if ( Fvi[0] == Fvi[1] || Fvi[1] == Fvi[2] || Fvi[0] == Fvi[k-1] )
  {
    // all FindNgon() code after this line can
    // assume Fvi[0] !+ Fvi[1], Fvi[1] != Fvi[2] and Fvi[3] != Fvi[0] 
    return false; 
  }

  P = (ON_3dPoint*)buffer;
  for ( i = 0; i < k; i++ )
  {
    if ( Fvi[i] >= vertex_count )
      return false;
    vertex_list.GetPoint(Fvi[i],buffer[i]);
  }

  if ( !bQuadFaces )
    P[3] = P[2];

  const ON_3dVector A(P[2].x-P[0].x,P[2].y-P[0].y,P[2].z-P[0].z);
  const ON_3dVector B(P[3].x-P[1].x,P[3].y-P[1].y,P[3].z-P[1].z);
  ON_3dVector N(A.y*B.z - B.y*A.z, A.z*B.x - B.z*A.x, A.x*B.y - B.x*A.y );
  double d = N.Length();
  if ( !(d > 0.0) )
    return false;
  N.x /= d;
  N.y /= d;
  N.z /= d;
  d = -(N.x*P[0].x + N.y*P[0].y + N.z*P[0].z);
  if ( !(fabs(N.x*P[1].x + N.y*P[1].y + N.z*P[1].z + d) <= planar_tolerance) )
    return false;
  if ( !(fabs(N.x*P[2].x + N.y*P[2].y + N.z*P[2].z + d) <= planar_tolerance) )
    return false;
  if ( !(fabs(N.x*P[3].x + N.y*P[3].y + N.z*P[3].z + d) <= planar_tolerance) )
    return false;

  e.x = N.x;
  e.y = N.y;
  e.z = N.z;
  e.d = d;

  return true;
}

/*
Returns:
  index into the ON_MeshNgon.m_fi[] array.
*/
static ON__UINT_PTR DecodeNFS_NgonFaceIndex( ON__UINT_PTR nfs )
{
  return (nfs/8);
}

static unsigned int DecodeNFS_EdgeIndex( ON__UINT_PTR nfs )
{
  return ((unsigned int)(nfs & 0x3));
}

/*
Parameters:
  ngon_face_index - [in]
    ON_MeshNgon.m_fi[] array index
  face_edge_index - [in]
   0 to 3
   the edge runs from 
     vertex index ON_MeshFace.vi[face_edge_index] 
   to 
     vertex index ON_MeshFace.vi[(face_edge_index+1)%4].
    
Returns:
  index into the ON_MeshNgon.m_fi[] array.
*/
static ON__UINT_PTR EncodeNFS_Neighbor(ON__UINT_PTR ngon_face_index, ON__UINT_PTR face_edge_index)
{
  // The 0x4 makes the value non-zero when ngon_face_index and face_edge_index are both zero.
  return ((ngon_face_index*8) | face_edge_index | 0x4 );
}

static ON__UINT_PTR EncodeNFS_BoundaryIndex(ON__UINT_PTR boundary_index)
{
  // 0 = (boundary_mark & 0x4)
  // 0 != boundary_mark
  return (boundary_index*8 | 0x1);
}

static bool IsNFS_Neighbor(ON__UINT_PTR nfs)
{
  return ( 0 != (nfs&0x4) );
}

struct NgonNeighbors
{
  // NFS = N-gon face and Side information
  // DecodeNFS_NgonFaceIndex(m_NFS[side_index]) = index into the ON_MeshNgon.m_fi[] array
  // DecodeNFS_EdgeIndex(m_NFS[side_index]) = 0,1,2 or 3 identifies the edge
  ON__UINT_PTR m_NFS[4];
};

static unsigned int FaceListIndex(
  unsigned int face_index_count,
  const unsigned int* face_index_list,
  unsigned int face_index
  )
{
  for ( unsigned int i = 0; i < face_index_count; i++ )
  {
    if ( face_index == face_index_list[i] )
      return i;
  }
  return ON_UNSET_UINT_INDEX;
}

static unsigned int SetFaceNeighborMap(
  unsigned int mesh_vertex_count,
  const ON_MeshFaceList& mesh_face_list,
  const unsigned int *const* vertex_face_map,
  ON_MeshVertexFaceMap* vertex_face_map_obj,
  unsigned int face_index_count,
  const unsigned int* face_index_list,
  struct NgonNeighbors* face_nbr_map
  )
{
  //const unsigned int mesh_vertex_count = mesh_vertex_list.VertexCount();
  const unsigned int mesh_face_count = mesh_face_list.FaceCount();
  unsigned int face_index, nbr_face_index, viA, viB, Adex;
  unsigned int Fvi[4], nbr_Fvi[4]; // quad face vertex indices
  unsigned int face_side, nbr_face_side; // 0 to 3 = face side index
  unsigned int fdex, nbr_fdex; // indices into the face_index_list[] array
  const unsigned int* face_listA;
  const unsigned int* face_listB;

  unsigned int boundary_count = 0;

  if ( face_index_count <= 0 || 0 == face_index_list || 0 == face_nbr_map )
    return 0;

  ON_MeshVertexFaceMap vf_tmp;
  ON_MeshVertexFaceMap* vf_map = &vf_tmp;

  const unsigned int* const* localVertexFaceMap = vertex_face_map;
  if (nullptr == localVertexFaceMap)
  {
    if (vertex_face_map_obj != nullptr)
    {
      localVertexFaceMap = vertex_face_map_obj->VertexFaceMap();
    }
  }
  if (vertex_face_map_obj != nullptr && vertex_face_map == nullptr)
  {
    vf_map = vertex_face_map_obj;
  }

  if (nullptr == localVertexFaceMap)
  {
    if ( !vf_map->SetFromFaceList(mesh_vertex_count,mesh_face_list,false) )
      return 0;
    localVertexFaceMap = vf_map->VertexFaceMap();
    if ( 0 == localVertexFaceMap)
      return 0;
    mesh_vertex_count = vf_map->VertexCount();
  }

  memset(face_nbr_map,0,face_index_count*sizeof(face_nbr_map[0]));
  for ( fdex = 0; fdex < face_index_count; fdex++ )
  {
    face_index = face_index_list[fdex];
    if ( face_index >= mesh_face_count )
      continue;

    mesh_face_list.QuadFvi(face_index,Fvi);
    viB = Fvi[0];
    face_listB = ( viB <= mesh_vertex_count ) ? localVertexFaceMap[viB] : 0;
    if ( 0 != face_listB && face_listB[0] <= 1 )
      face_listB = 0;

    for ( face_side = 0; face_side < 4; face_side++ )
    {
      viA = viB;
      viB = Fvi[(face_side+1)%4];
      if ( viA == viB )
        continue;

      boundary_count++;

      face_listA = face_listB;
      face_listB = ( viB <= mesh_vertex_count ) ? localVertexFaceMap[viB] : 0;
      if ( 0 == face_listB )
        continue;
      if ( face_listB[0] <= 1 )
      {
        face_listB = 0;
        continue;
      }
      if ( 0 == face_listA )
        continue;

      if ( 0 != face_nbr_map[fdex].m_NFS[face_side] )
      {
        boundary_count--;
        continue; // already found a neighbor for this side
      }

      // look for a neighbor from viB to viA
      for ( Adex = 1; Adex <= face_listA[0]; Adex++ )
      {
        nbr_face_index = face_listA[Adex];
        if ( face_index == nbr_face_index)
          continue;
        nbr_fdex = FaceListIndex(face_index_count,face_index_list,nbr_face_index);
        if ( nbr_fdex >= face_index_count )
          continue; // nbr_face_index is not in the face_index_list[] array
        if ( nbr_fdex <= fdex )
          continue; // this combination of faces has already been checked.

        mesh_face_list.QuadFvi(nbr_face_index,nbr_Fvi);
        for ( nbr_face_side = 0; nbr_face_side < 4; nbr_face_side++ )
        {
          if ( viB != nbr_Fvi[nbr_face_side] )
            continue;

          if ( viA != nbr_Fvi[(nbr_face_side+1)%4] )
            continue; // happens for the duplicate vertex in a triangle

          if ( 0 != face_nbr_map[nbr_fdex].m_NFS[nbr_face_side] )
            continue; // this side of the neighbor has a neighbor (unexpected)

          // record the fact these faces share an edge
          face_nbr_map[nbr_fdex].m_NFS[nbr_face_side] = EncodeNFS_Neighbor(fdex,face_side);
          face_nbr_map[fdex].m_NFS[face_side] = EncodeNFS_Neighbor(nbr_fdex,nbr_face_side);
          boundary_count--;
          nbr_face_side = 5;
          break;
        }
        if ( 5 == nbr_face_side )
          break; // we found a neighbor and are finished searching
      }
    }
  }

  return boundary_count;
}


static int GetCoplanarConnectedFaces(
  const ON_3dPointListRef& vertex_list,
  const ON_MeshFaceList& face_list,
  const unsigned int ngonIndex,
  unsigned int* ngonMap,
  const unsigned int *const* vertex_face_map,
  double planar_tolerance,
  unsigned int starting_face_index,
  ON_PlaneEquation e,
  ON_SimpleArray<unsigned int>& ngon_fi,
  ON_SimpleArray<struct NgonNeighbors>& ngon_nbr_map
  )
{
  ON__UINT_PTR face_side, nbr_face_side;
  unsigned int boundary_count, ngon_fi_dex0, ngon_fi_dex1, nbr_ngon_fi_dex, viA, viB, Adex, nbr_face_index, face_index;
  unsigned int Fvi[4], nbr_Fvi[4];
  const unsigned int* face_listA;
  const unsigned int* face_listB;
  const unsigned int vertex_count = vertex_list.PointCount();

  ngon_fi.SetCount(0);
  ngon_fi.Append(starting_face_index);

  ngon_nbr_map.SetCount(0);
  ngon_nbr_map.AppendNew();

  ngonMap[starting_face_index] = ngonIndex;

  boundary_count = 0;

  ngon_fi_dex1 = 0;
  while( ngon_fi_dex1 < ngon_fi.UnsignedCount() )
  {
    ngon_fi_dex0 = ngon_fi_dex1;
    for (ngon_fi_dex1 = ngon_fi.Count(); ngon_fi_dex0 < ngon_fi_dex1; ngon_fi_dex0++ )
    {
      // look for neighbors of F[face_index]
      face_index = ngon_fi[ngon_fi_dex0];
      face_list.QuadFvi(face_index,Fvi);
      viB = Fvi[0];
      face_listB = ( viB <= vertex_count ) ? vertex_face_map[viB] : 0;
      if ( 0 != face_listB && face_listB[0] <= 1 )
        face_listB = 0;
      for ( face_side = 0; face_side < 4; face_side++ )
      {
        viA = viB;
        viB = Fvi[(face_side+1)%4];
        if ( viA == viB )
          continue;

        boundary_count++;

        face_listA = face_listB;
        face_listB = ( viB <= vertex_count ) ? vertex_face_map[viB] : 0;
        if ( 0 == face_listB )
          continue;
        if ( face_listB[0] <= 1 )
        {
          face_listB = 0;
          continue;
        }
        if ( 0 == face_listA )
          continue;

        if ( 0 != ngon_nbr_map[ngon_fi_dex0].m_NFS[face_side] )
        {
          boundary_count--;
          continue; // already found a neighbor for this side
        }

        // look for a coplanar neighbor from viB to viA
        for ( Adex = 1; Adex <= face_listA[0]; Adex++ )
        {
          nbr_face_index = face_listA[Adex];
          if ( face_index == nbr_face_index || nbr_face_index <= starting_face_index)
            continue;
          if ( ON_UNSET_UINT_INDEX != ngonMap[nbr_face_index] && ngonIndex != ngonMap[nbr_face_index])
            continue; // ON_Mesh.m_F[nbr_face_index] belongs to another n-gon

          face_list.QuadFvi(nbr_face_index,nbr_Fvi);
          for ( nbr_face_side = 0; nbr_face_side < 4; nbr_face_side++ )
          {
            if ( viB != nbr_Fvi[nbr_face_side] )
              continue;

            if ( viA != nbr_Fvi[(nbr_face_side+1)%4] )
              continue; // happens for the duplicate vertex in a triangle

            if ( !FaceInPlane(planar_tolerance,e,vertex_list,nbr_Fvi) )
              break; // shared edge but not coplanar

            if ( ON_UNSET_UINT_INDEX == ngonMap[nbr_face_index] )
            {
              // add ON_Mesh.m_F[nbr_face_index] to this ngon
              nbr_ngon_fi_dex = ngon_fi.Count();
              ngonMap[nbr_face_index] = ngonIndex;
              ngon_fi.Append(nbr_face_index);
              ngon_nbr_map.AppendNew().m_NFS[nbr_face_side] = EncodeNFS_Neighbor(ngon_fi_dex0,face_side);
            }
            else
            {
              // If things are as expected, then ON_Mesh.m_F[nbr_face_index]
              // face was been added to the ngon after the face we are working
              // on ( ON_Mesh.m_F[ngon_fi[ngon_fi_dex0]] ).
              for ( nbr_ngon_fi_dex = ngon_fi.Count()-1; nbr_ngon_fi_dex > ngon_fi_dex0; nbr_ngon_fi_dex-- )
              {
                if (nbr_face_index == ngon_fi[nbr_ngon_fi_dex])
                  break;
              }
              if ( nbr_ngon_fi_dex <= ngon_fi_dex0 )
                break; // not expected for an oriented manifold mesh
                
              if ( 0 != ngon_nbr_map[nbr_ngon_fi_dex].m_NFS[nbr_face_side] )
                break; // not expected for an oriented manifold mesh

              ngon_nbr_map[nbr_ngon_fi_dex].m_NFS[nbr_face_side] = EncodeNFS_Neighbor(ngon_fi_dex0,face_side);
            }

            if ( nbr_ngon_fi_dex > ngon_fi_dex0 )
            {
              ngon_nbr_map[ngon_fi_dex0].m_NFS[face_side] = EncodeNFS_Neighbor(nbr_ngon_fi_dex,nbr_face_side);
              boundary_count--;
              nbr_face_side = 5;
            }
            break;
          }
          if ( 5 == nbr_face_side )
            break; // we found a neighbor and are finished searching
        }
      }
    }
  }

  return boundary_count;
}


static void UnsetNgonMap(
  const unsigned int* ngon_face_index_list,
  unsigned int ngon_face_index_count,
  const unsigned int ngonIndex,
  const unsigned int ngonUnsetIndex,
  unsigned int* ngonMap
  )
{  
  int fi;
  for ( unsigned int i = 0; i < ngon_face_index_count; i++ )
  {
    fi = ngon_face_index_list[i];
    if (ngonIndex == ngonMap[fi])
      ngonMap[fi] = ngonUnsetIndex;
  }
}

static unsigned int EncodeNgonSide(
  unsigned int ngon_fdex,
  unsigned int quad_side_index,
  unsigned int bReversed
  )
{
  return (ngon_fdex*8 + quad_side_index + (bReversed ? 4 : 0));
}


/*
Description:
  NEVER EXPORT THIS WORKER FUNCTION.

  Given a set of connected faces, this function finds the
  boundary of the n-gon.
Parameters:
  face_list - [in]
  ngon_fi_count - [in]
    >= 0
  ngon_fi - [in]
    array of length ngon_fi_count that contains the
    indices of faces that make up the ngon.
  ngon_boundary_index - [in]
    index of the next boundary segment to be added.
  ngon_nbr_map - [in/out]
    array of length ngon_fi_count that contains the
    face neighbor information.  
    ngon_nbr_map[face_index].m_NFS[j] must be zero
    for open boundaries.  If the face side identified by
    ngon_nbr_map[face_index].m_NFS[j] is assigned to an
    ngon boundary, then it is marked as a boundary segment.
  ngon_vi - [out]
    If true is returned, then ngon_vi is an array of vertex
    indices that make up the boundary of the ngon.
  ngon_side - [out]
    ngon_side[i]/8 = ON_MeshNgon.m_fi[] index
    ngon_side[i]%4 = quad side index (side=0 means vtx 0 to vtx 1)
    (ngon_side[i] & 8) != 0 means side is reversed.
Returns:
  Number of vertices/segments added for the boundary component.
*/
static unsigned int GetNgonBoundarySegments(
  const ON_MeshFaceList& face_list,
  unsigned int ngon_fi_count,
  const unsigned int* ngon_fi,
  unsigned int ngon_boundary_index,
  struct NgonNeighbors* ngon_nbr_map,
  ON_SimpleArray<unsigned int>* ngon_vi,
  ON_SimpleArray<unsigned int>* ngon_side
  )
{
  unsigned int j0, next_j0, j1;
  unsigned int Fvi[4];
  unsigned int vi0, vi1, fi, max_vertex_count;
  unsigned int ngon_fdex, nbr_ngon_fdex, face_vist_count, max_face_visit_count;

  const unsigned int ngon_boundary_index0 = ngon_boundary_index;

  if ( ngon_fi_count <= 0 || 0 == ngon_fi || 0 == ngon_nbr_map )
    return 0;

  if ( 1 == ngon_fi_count )
  {
    if (    0 != ngon_nbr_map[0].m_NFS[0] 
         || 0 != ngon_nbr_map[0].m_NFS[1] 
         || 0 != ngon_nbr_map[0].m_NFS[2] 
         || 0 != ngon_nbr_map[0].m_NFS[3] 
         )
    {
      return 0;
    }
    face_list.QuadFvi(ngon_fi[0],Fvi);

    if ( ngon_vi )
      ngon_vi->Append(Fvi[0]);
    if ( ngon_side )
      ngon_side->AppendNew() = EncodeNgonSide(0,0,false);
    ngon_nbr_map[0].m_NFS[0] = EncodeNFS_BoundaryIndex(ngon_boundary_index++);

    if ( ngon_vi )
      ngon_vi->Append(Fvi[1]);
    if ( ngon_side )
      ngon_side->AppendNew() = EncodeNgonSide(0,1,false);
    ngon_nbr_map[0].m_NFS[1] = EncodeNFS_BoundaryIndex(ngon_boundary_index++);

    if ( Fvi[2] != Fvi[3] )
    {
      if ( ngon_vi )
        ngon_vi->Append(Fvi[2]);
      if ( ngon_side )
        ngon_side->AppendNew() = EncodeNgonSide(0,2,false);
      ngon_nbr_map[0].m_NFS[2] = EncodeNFS_BoundaryIndex(ngon_boundary_index++);
    }

    if ( ngon_vi )
      ngon_vi->Append(Fvi[3]);
    if ( ngon_side )
      ngon_side->AppendNew() = EncodeNgonSide(0,3,false);
    ngon_nbr_map[0].m_NFS[3] = EncodeNFS_BoundaryIndex(ngon_boundary_index++);

    return ngon_boundary_index - ngon_boundary_index0;
  }


  fi = 0;  // keep lint quiet - at this point ngon_fi_count > 0
  j0 = 0;  // keep lint quiet - at this point ngon_fi_count > 0
  
  // find a boundary edge
  for ( ngon_fdex = 0; ngon_fdex < ngon_fi_count; ngon_fdex++ )
  {
    fi = ngon_fi[ngon_fdex];
    face_list.QuadFvi(fi,Fvi);
    for ( j0 = 0; j0 < 4; j0++ )
    {
      if ( Fvi[j0] == Fvi[(j0+1)%4] )
        continue;
      if ( 0 != ngon_nbr_map[ngon_fdex].m_NFS[j0] )
        continue; // has a neighbor or is part of a previously found boundary component when holes are allowed

      // we being at the vertex with index Fvi[j]
      break;
    }    
    if ( j0 < 4 )
      break;
  }
  
  if ( ngon_fdex >= ngon_fi_count )
    return 0;

  // max_vertex_count is used to prevent infinite recursion
  // when the mesh information is not valid or there is
  // a bug in this code.  The maximum value occurs
  // for a strip of quads.
  max_vertex_count = 2*ngon_fi_count + 2;


  // max_face_visit_count is used to prevent infinite recursion
  // when the mesh information is not valid or there is
  // a bug in this code.  The maximum value occurs
  // for a strip of quads when the initial face is
  // at the end of a strip.
  max_face_visit_count = 2*ngon_fi_count - 1;

  ngon_nbr_map[ngon_fdex].m_NFS[j0] = EncodeNFS_BoundaryIndex(ngon_boundary_index++);
  if ( ngon_side )
    ngon_side->AppendNew() = EncodeNgonSide(ngon_fdex,j0,false);

  vi0 = Fvi[j0];
  j0 = (j0+1)%4;
  vi1 = Fvi[j0];
  if ( ngon_vi )
  {
    ngon_vi->Append(vi0);
    ngon_vi->Append(vi1);
  }
  for ( face_vist_count = 0;
        face_vist_count <= max_face_visit_count && ngon_boundary_index - ngon_boundary_index0 <= max_vertex_count;
        face_vist_count++ 
      )
  {
    for (j1 = 0; j1 < 4; j1++, j0 = next_j0 )
    {
      if ( 0 != ngon_nbr_map[ngon_fdex].m_NFS[j0] )
        break; // has a neighbor or is a boundary

      next_j0 = (j0+1)%4;
      if ( vi1 == Fvi[next_j0] )
        continue; // skip over duplicate vertex in triangles

      ngon_nbr_map[ngon_fdex].m_NFS[j0] = EncodeNFS_BoundaryIndex(ngon_boundary_index++);
      if ( ngon_side )
        ngon_side->AppendNew() = EncodeNgonSide(ngon_fdex,j0,false);

      vi1 = Fvi[next_j0];
      if ( vi0 == vi1 )
      {
        // this is where successful searches end with (ngon_vi.Count() >= 3)
        if ( ngon_boundary_index - ngon_boundary_index0 >= 3 )
        {
          return ngon_boundary_index - ngon_boundary_index0;
        }
        return 0;
      }
      if ( ngon_vi )
        ngon_vi->Append(vi1);
    }

    if ( j1 >= 4 )
      break; // not expected - there is a bug or a bogus mesh

    if ( false == IsNFS_Neighbor(ngon_nbr_map[ngon_fdex].m_NFS[j0]) )
      break; // not expected - there is a bug or a bogus mesh

    // switch to neighbor face;
    nbr_ngon_fdex = (unsigned int)DecodeNFS_NgonFaceIndex(ngon_nbr_map[ngon_fdex].m_NFS[j0]);

    if ( nbr_ngon_fdex == ngon_fdex || nbr_ngon_fdex >= ngon_fi_count )
    {
      // Unexpected - bail rather than crash.
      // This means there is a bug in the code that 
      // set the values in the ngon_nbr_map[] array.
      // The same face may be visited multiple times (strip of quads for example),
      // but a face can never be its own neighbor.
      break;
    }

    // move onto the neighbor
    j0 = DecodeNFS_EdgeIndex(ngon_nbr_map[ngon_fdex].m_NFS[j0]);

    ngon_fdex = nbr_ngon_fdex;
    fi = ngon_fi[ngon_fdex];
    face_list.QuadFvi(fi,Fvi);
    // faces have compatible orientations 
    // (The shared edge is reversed when going to neighboring face)
    j0 = (j0+1)%4; // move the the vertex at the end of the shared edge

    if ( vi1 != Fvi[j0] )
    {
      // not expected - there is a bug or a bogus mesh
      break;
    }
  }

  return 0;
}


class ON_MeshNgon* ON_MeshNgon::NgonFromMeshFace(
  class ON_MeshNgonBuffer& ngon_buffer,
  unsigned int mesh_face_index,
  const unsigned int* fvi
  )
{
  // The nullptr check is weird.
  // Speculation: There is / was some way that a null reference (like a * of a bona fide nullptr)
  // was in use?
  if ( ON_IsNullPtr(&ngon_buffer) || 0 == fvi )
    return 0;

  // local_fvi[] allows the fvi[] input to be stored in the buffer[] memory.
  unsigned int local_fvi[4] = {fvi[0],fvi[1],fvi[2],fvi[3]};
  fvi = local_fvi;

  unsigned int Vcount = (fvi[3] < ON_UNSET_UINT_INDEX && fvi[3] != fvi[2]) ? 4 : 3;

  ON_MeshNgon* ngon = (ON_MeshNgon*)(&ngon_buffer);
  ngon->m_vi = (unsigned int*)(ngon+1);
  ngon->m_fi = ngon->m_vi + Vcount;

  ngon->m_Vcount = Vcount;
  ngon->m_vi[0] = fvi[0];
  ngon->m_vi[1] = fvi[1];
  ngon->m_vi[2] = fvi[2];
  if ( 4 == ngon->m_Vcount )
    ngon->m_vi[3] = fvi[3];

  ngon->m_Fcount = 1;
  ngon->m_fi[0] = mesh_face_index;

  return ngon;
}

class ON_MeshNgon** ON_MeshNgon::NgonListFromMeshFace(
  class ON_MeshNgonBuffer& ngon_buffer,
  unsigned int mesh_face_index,
  const unsigned int* fvi
  )
{
  ON_MeshNgon* ngon = NgonFromMeshFace(ngon_buffer,mesh_face_index,fvi);
  if ( 0 == ngon )
    return 0;

  ON_MeshNgon** ngon_list = (ON_MeshNgon**)(ngon+1);
  ngon_list[0] = ngon;

  return ngon_list;
}

const ON_MeshNgon* ON_Mesh::NgonFromComponentIndex(
  class ON_MeshNgonBuffer& ngon_buffer,
  ON_COMPONENT_INDEX ci
  ) const
{
  const ON_MeshNgon* ngon = 0;
  switch( ci.m_type )
  {
  case ON_COMPONENT_INDEX::mesh_face:
    if ( ci.m_index >= 0 && ci.m_index < m_F.Count() )
    {
      ngon = ON_MeshNgon::NgonFromMeshFace(ngon_buffer,(unsigned int)ci.m_index,(const unsigned int*)m_F[ci.m_index].vi);
    }
    break;

  case ON_COMPONENT_INDEX::mesh_ngon:
    ngon = Ngon(ci.m_index);
    break;
      
  default:
    break;
  }

  return ngon;
}

static unsigned int FindNgonBoundary_Helper(
  const ON_3dPointListRef& mesh_vertex_list,
  const ON_MeshFaceList& mesh_face_list,
  const unsigned int *const* vertex_face_map,
  ON_MeshVertexFaceMap* vertex_face_map_obj,
  size_t ngon_fi_count,
  const unsigned int* ngon_fi,
  ON_SimpleArray<unsigned int>& ngon_vi,
  bool permitOnlyOneBoundary
)
{
  const unsigned int mesh_vertex_count = mesh_vertex_list.PointCount();
  const unsigned int ngon_boundary_index = 1;
  unsigned int boundary_edge_count;


  for (;;)
  {
    if (mesh_vertex_count <= 0 || ON_UNSET_UINT_INDEX == mesh_vertex_count)
      break;

    if (ngon_fi_count <= 0 || 0 == ngon_fi)
      break;

    ON_SimpleArray<struct NgonNeighbors> ngon_nbr_map;
    ngon_nbr_map.Reserve((unsigned int)ngon_fi_count);
    ngon_nbr_map.SetCount((unsigned int)ngon_fi_count);
    boundary_edge_count = SetFaceNeighborMap(
      mesh_vertex_count,
      mesh_face_list,
      vertex_face_map,
      vertex_face_map_obj,
      (unsigned int)ngon_fi_count,
      ngon_fi,
      ngon_nbr_map.Array()
    );

    if (boundary_edge_count <= 0)
      break;

    ngon_vi.SetCount(0);
    ngon_vi.Reserve(boundary_edge_count);
    if (!GetNgonBoundarySegments(
      mesh_face_list,
      (unsigned int)ngon_fi_count,
      ngon_fi,
      ngon_boundary_index,
      ngon_nbr_map.Array(),
      &ngon_vi,
      0
    ))
      break;

    if (permitOnlyOneBoundary && boundary_edge_count != ngon_vi.UnsignedCount())
      break; // inner boundaries exist - ngon has holes

    return ngon_vi.UnsignedCount();
  }

  // failure
  ngon_vi.SetCount(0);
  return 0;
}

static
double Internal_NgonBoundaryArea(
  const ON_Plane& ngon_plane,
  const ON_3dPointListRef& vertex_list,
  const ON_SimpleArray< unsigned int >& ngon_vi
)
{
  ON_2dPoint p0, p1;
  const unsigned int count = ngon_vi.UnsignedCount();
  if (count < 3)
    return 0.0;
  if (false == ngon_plane.ClosestPointTo(vertex_list[ngon_vi[count - 1]], &p1.x, &p1.y))
    return 0.0;
  double twice_area = 0.0;
  for (unsigned int i = 0; i < count; i++)
  {
    p0 = p1;
    if (false == ngon_plane.ClosestPointTo(vertex_list[ngon_vi[i]], &p1.x, &p1.y))
      return 0.0;
    twice_area += (p0.x - p1.x) * (p0.y + p1.y);
  }
  return fabs(0.5 * twice_area);
}

static unsigned int FindNgonBoundaries_Helper(
  const ON_3dPointListRef& mesh_vertex_list,
  const ON_MeshFaceList& mesh_face_list,
  const unsigned int* const* vertex_face_map,
  ON_MeshVertexFaceMap* vertex_face_map_obj,
  size_t ngon_fi_count,
  const unsigned int* ngon_fi,
  ON_SimpleArray<unsigned int>& ngon_vi,
  ON_SimpleArray<unsigned int>& ngon_vi_markers,
  bool permitOnlyOneBoundary
)
{
  const unsigned int mesh_vertex_count = mesh_vertex_list.PointCount();
  unsigned int boundary_edge_count;
  unsigned int ngon_boundary_index = 0;

  for (;;)
  {
    if (mesh_vertex_count <= 0 || ON_UNSET_UINT_INDEX == mesh_vertex_count)
      break;

    if (ngon_fi_count <= 0 || 0 == ngon_fi)
      break;

    ON_SimpleArray<struct NgonNeighbors> ngon_nbr_map;
    ngon_nbr_map.Reserve((unsigned int)ngon_fi_count);
    ngon_nbr_map.SetCount((unsigned int)ngon_fi_count);
    boundary_edge_count = SetFaceNeighborMap(mesh_vertex_count, mesh_face_list, vertex_face_map, vertex_face_map_obj, (unsigned int)ngon_fi_count, ngon_fi, ngon_nbr_map.Array());

    ngon_boundary_index++;
    ngon_vi.SetCount(0);
    if (0 == GetNgonBoundarySegments(mesh_face_list, (unsigned int)ngon_fi_count, ngon_fi, ngon_boundary_index, ngon_nbr_map.Array(), &ngon_vi, 0))
      break;

    ngon_vi_markers.Append(ngon_vi.Count());

    if (ngon_vi.UnsignedCount() < boundary_edge_count)
    {
      ON_SimpleArray<unsigned int> tmp;
      // ngon has holes.
      // The boundary with the largest area is the outer boundary.
      ON_3dVector A(mesh_vertex_list[ngon_vi[1]] - mesh_vertex_list[ngon_vi[0]]);
      ON_3dVector B(mesh_vertex_list[ngon_vi[ngon_vi.Count()-1]] - mesh_vertex_list[ngon_vi[0]]);
      A.Unitize(); B.Unitize();
      const ON_Plane ngon_plane(mesh_vertex_list[ngon_vi[0]], ON_CrossProduct(A, B));

      double ngon_vi_area = Internal_NgonBoundaryArea(ngon_plane, mesh_vertex_list, ngon_vi);

      for (;;)
      {
        ON_SimpleArray<unsigned int> ngon_vi1;
        ngon_boundary_index++;
        if (0 == GetNgonBoundarySegments(mesh_face_list, (unsigned int)ngon_fi_count, ngon_fi, ngon_boundary_index, ngon_nbr_map.Array(), &ngon_vi1, 0))
          break;
        if (ngon_vi1.UnsignedCount() < 3)
          break;
        double ngon_vi1_area = Internal_NgonBoundaryArea(ngon_plane, mesh_vertex_list, ngon_vi1);
        if (ngon_vi1_area > ngon_vi_area)
        {
          ngon_vi_area = ngon_vi1_area;
          tmp.Empty();
          tmp.Append(ngon_vi1.Count(), ngon_vi1.Array());
          tmp.Append(ngon_vi.Count(), ngon_vi.Array());
          ngon_vi = tmp;
          ngon_vi_markers.Insert(0, ngon_vi1.Count());
        }
        else
        {
          ngon_vi_markers.Append(ngon_vi1.Count());
          ngon_vi.Append(ngon_vi1.Count(), ngon_vi1.Array());
        }
      }
    }

    //if (permitOnlyOneBoundary && boundary_edge_count != ngon_vi.UnsignedCount())
    //  break; // inner boundaries exist - ngon has holes

    return ngon_vi.UnsignedCount();
  }

  // failure
  ngon_vi.SetCount(0);
  return 0;
}


unsigned int ON_MeshNgon::FindNgonOuterBoundary(
  const ON_3dPointListRef& mesh_vertex_list,
  const ON_MeshFaceList& mesh_face_list,
  const unsigned int *const* vertex_face_map,
  size_t ngon_fi_count,
  const unsigned int* ngon_fi,
  ON_SimpleArray<unsigned int>& ngon_vi
  )
{
  return FindNgonBoundary_Helper(
    mesh_vertex_list,
    mesh_face_list,
    vertex_face_map,
    nullptr,
    ngon_fi_count,
    ngon_fi,
    ngon_vi,
    true
  );
}

unsigned int ON_MeshNgon::FindNgonOuterBoundary(
  const ON_3dPointListRef& mesh_vertex_list,
  const ON_MeshFaceList& mesh_face_list,
  ON_MeshVertexFaceMap* vertex_face_map,
  size_t ngon_fi_count,
  const unsigned int* ngon_fi,
  ON_SimpleArray<unsigned int>& ngon_vi
)
{
  return FindNgonBoundary_Helper(
  mesh_vertex_list,
  mesh_face_list,
  nullptr,
  vertex_face_map,
  ngon_fi_count,
  ngon_fi,
  ngon_vi,
  true
  );
}

unsigned int ON_MeshNgon::FindNgonBoundaries(
  const class ON_3dPointListRef& mesh_vertex_list,
  const class ON_MeshFaceList& mesh_face_list,
  ON_MeshVertexFaceMap* vertex_face_map,
  size_t ngon_fi_count,
  const unsigned int* ngon_fi,
  ON_SimpleArray<unsigned int>& ngon_vi,
  ON_SimpleArray<unsigned int>& ngon_vi_markers
)
{
  return FindNgonBoundaries_Helper(
    mesh_vertex_list,
    mesh_face_list,
    nullptr,
    vertex_face_map,
    ngon_fi_count,
    ngon_fi,
    ngon_vi,
    ngon_vi_markers,
    false
  );
}

unsigned int ON_MeshNgon::FindNgonBoundary(
  const ON_3dPointListRef& mesh_vertex_list,
  const ON_MeshFaceList& mesh_face_list,
  const unsigned int *const* vertex_face_map,
  size_t ngon_fi_count,
  const unsigned int* ngon_fi,
  ON_SimpleArray<unsigned int>& ngon_vi
)
{
  return FindNgonBoundary_Helper(
    mesh_vertex_list,
    mesh_face_list,
    vertex_face_map,
    nullptr,
    ngon_fi_count,
    ngon_fi,
    ngon_vi,
    false
  );
}



unsigned int ON_MeshNgon::FindNgonBoundary(
  const ON_3dPointListRef& mesh_vertex_list,
  const ON_MeshFaceList& mesh_face_list,
  ON_MeshVertexFaceMap* vertex_face_map,
  size_t ngon_fi_count,
  const unsigned int* ngon_fi,
  ON_SimpleArray<unsigned int>& ngon_vi
)
{
  return FindNgonBoundary_Helper(
    mesh_vertex_list,
    mesh_face_list,
    nullptr,
    vertex_face_map,
    ngon_fi_count,
    ngon_fi,
    ngon_vi,
    false
  );
}

unsigned int ON_MeshNgon::GetBoundarySides(
  const class ON_MeshFaceList& mesh_face_list,
  ON_SimpleArray<unsigned int>& ngon_boundary_sides
  ) const
{
  unsigned int ngon_boundary_segment_count = 0;
  unsigned int boundary_edge_count;

  ngon_boundary_sides.SetCount(0);


  for(;;)
  {
    const unsigned int ngon_fi_count(m_Fcount);
    const unsigned int* ngon_fi(m_fi);
    if ( ngon_fi_count <= 0 || 0 == ngon_fi )
      break;

    const unsigned int mesh_vertex_count = 0xFFFFFFFE;
    const unsigned int *const* vertex_face_map = 0;

    ON_SimpleArray<struct NgonNeighbors> ngon_nbr_map;
    ngon_nbr_map.Reserve(ngon_fi_count);
    ngon_nbr_map.SetCount(ngon_fi_count);
    boundary_edge_count = SetFaceNeighborMap(
      mesh_vertex_count,
      mesh_face_list,
      vertex_face_map,
      nullptr,
      ngon_fi_count,
      ngon_fi,
      ngon_nbr_map.Array()
      );

    if ( boundary_edge_count <= 0 )
      break;

    ngon_boundary_sides.SetCount(0);
    ngon_boundary_sides.Reserve(boundary_edge_count);

    for(;;)
    {
      // keep adding boundary components until we
      // find all of them or there is an error
      unsigned int segment_count =  GetNgonBoundarySegments(
        mesh_face_list,
        (unsigned int)ngon_fi_count,
        ngon_fi,
        ngon_boundary_segment_count,
        ngon_nbr_map.Array(),
        0,
        &ngon_boundary_sides
        );
      if ( segment_count <= 0 )
        break; //error

      ngon_boundary_segment_count += segment_count;
      if ( ngon_boundary_segment_count >= boundary_edge_count )
        return ngon_boundary_sides.UnsignedCount(); // found them all
    }

    break; // error if we get here
  }

  // failure
  ngon_boundary_sides.SetCount(0);

  return 0;
}

unsigned int ON_Mesh::GetNgonOuterBoundary(
    unsigned int ngon_fi_count,
    const unsigned int* ngon_fi,
    ON_SimpleArray<unsigned int>& ngon_vi
    ) const
{
  ON_3dPointListRef mesh_vertex_list;
  ON_MeshFaceList mesh_face_list;
  mesh_vertex_list.SetFromMesh(this);
  mesh_face_list.SetFromMesh(this);
  return ON_MeshNgon::FindNgonOuterBoundary(mesh_vertex_list,mesh_face_list,(ON_MeshVertexFaceMap*)nullptr,ngon_fi_count,ngon_fi,ngon_vi);
}

unsigned int ON_MeshNgon::FindPlanarNgons(
  const ON_3dPointListRef& vertex_list,
  const ON_MeshFaceList& face_list,
  const unsigned int *const* vertex_face_map,
  double planar_tolerance,
  unsigned int minimum_ngon_vertex_count,
  unsigned int minimum_ngon_face_count,
  bool bAllowHoles,
  ON_MeshNgonAllocator& NgonAllocator,
  ON_SimpleArray<unsigned int>& NgonMap,
  ON_SimpleArray<ON_MeshNgon*>& Ngons
  )
{
  const unsigned int NgonsCount0 = Ngons.UnsignedCount();
  const unsigned int vertex_count = vertex_list.PointCount();
  const unsigned int face_count = face_list.FaceCount();
  unsigned int ngon_boundary_index = 0;
  const bool bQuadFaces = (4 == face_list.FaceVertexCount());

  ON_MeshVertexFaceMap ws_vfmap;

  ON_MeshNgon* ngon;
  unsigned int Fvi[4];
  unsigned int face_index, ngon_boundary_edge_count;
  ON_SimpleArray<unsigned int> ngon_vi;
  ON_SimpleArray<unsigned int> ngon_fi;
  ON_SimpleArray<struct NgonNeighbors> ngon_nbr_map;
  ON_PlaneEquation e;

  bool bCleanUpNgonMap = false;

  for (;;)
  {
    if ( face_count <= 0 || face_count != NgonMap.UnsignedCount() )
      NgonMap.SetCount(0);

    if ( face_count <= 0 || vertex_count <= 0 )
      break;
   
    if ( 0 == vertex_face_map )
    {
      if ( !ws_vfmap.SetFromFaceList(vertex_count,face_list,false) )
        break;
      vertex_face_map = ws_vfmap.VertexFaceMap();
      if ( 0 == vertex_face_map )
        break;
    }

    ngon_vi.Reserve(128);
    ngon_fi.Reserve(128);
    ngon_nbr_map.Reserve(128);

    unsigned int* ngonMap = NgonMap.Array();
    if ( face_count != NgonMap.UnsignedCount() )
    {
      NgonMap.Reserve(face_count);
      NgonMap.SetCount(face_count);
      ngonMap = NgonMap.Array(); // in case a reallocation occurred.
      for ( face_index = 0; face_index < face_count; face_index++ )
        ngonMap[face_index] = ON_UNSET_UINT_INDEX;
    }

    int ngonIndex = NgonsCount0;
    unsigned int ngonUnsetIndex;
    const unsigned int omitted_face_mark = ON_UNSET_UINT_INDEX - 1;

    for ( face_index = 0; face_index < face_count; face_index++ )
    {
      if ( ON_UNSET_UINT_INDEX != ngonMap[face_index] )
        continue; // this face is not eligable for being in an n-gon

      face_list.QuadFvi(face_index,Fvi);
      if ( !GetFacePlaneEquation(vertex_list,bQuadFaces,Fvi,planar_tolerance,e) )
        continue; // degenerate face

      for (;;)
      {
        ngon = 0;
        ngonUnsetIndex = ON_UNSET_UINT_INDEX;

        // Note:
        //   ngon_boundary_count includes interior edges when the n-gon has holes
        ngon_boundary_edge_count = GetCoplanarConnectedFaces(
          vertex_list,
          face_list,
          ngonIndex, ngonMap, vertex_face_map,
          planar_tolerance, face_index, e, 
          ngon_fi,
          ngon_nbr_map
          );

        if ( ngon_boundary_edge_count < minimum_ngon_vertex_count )
          break;

        if ( ngon_fi.UnsignedCount() < minimum_ngon_face_count )
          break;

        ngon_boundary_index++;
        ngon_vi.SetCount(0);
        if ( !GetNgonBoundarySegments(face_list,
                            ngon_fi.UnsignedCount(),ngon_fi.Array(),
                            ngon_boundary_index,
                            ngon_nbr_map.Array(),
                            &ngon_vi,
                            0
                            ) 
           )
          break;

        if ( ngon_vi.UnsignedCount() < minimum_ngon_vertex_count )
          break;

        if ( ngon_vi.UnsignedCount() < ngon_boundary_edge_count )
        {
          // ngon has holes.
          // The boundary with the largest area is the outer boundary.
          const ON_Plane ngon_plane(vertex_list[ngon_vi[0]], e.UnitNormal());

          double ngon_vi_area = Internal_NgonBoundaryArea(ngon_plane, vertex_list, ngon_vi);

          for(;;)
          {
            ON_SimpleArray<unsigned int> ngon_vi1;
            ngon_boundary_index++;
            if ( !GetNgonBoundarySegments(face_list,
                                ngon_fi.UnsignedCount(),ngon_fi.Array(),
                                ngon_boundary_index,
                                ngon_nbr_map.Array(),
                                &ngon_vi1, 0) 
               )
              break;
            if ( ngon_vi1.UnsignedCount() < 3 )
              break;
            double ngon_vi1_area = Internal_NgonBoundaryArea(ngon_plane, vertex_list, ngon_vi1);
            if (ngon_vi1_area > ngon_vi_area)
            {
              ngon_vi_area = ngon_vi1_area;
              ngon_vi = ngon_vi1;
            }
          }

          if (false == bAllowHoles)
          {
            ngonUnsetIndex = omitted_face_mark;
            bCleanUpNgonMap = true;
            break;
          }
        }

        ngon = NgonAllocator.AllocateNgon(ngon_vi.UnsignedCount(),ngon_fi.UnsignedCount());
        if ( 0 == ngon )
          break;

        memcpy(ngon->m_vi,ngon_vi.Array(),ngon->m_Vcount*sizeof(ngon->m_vi[0]));
        memcpy(ngon->m_fi,ngon_fi.Array(),ngon->m_Fcount*sizeof(ngon->m_fi[0]));
        break; // finished new ngon
      }

      if (0 == ngon)
      {
        // undo any modifications that were made to ngonMap[]
        UnsetNgonMap(ngon_fi.Array(),ngon_fi.UnsignedCount(),ngonIndex,ngonUnsetIndex,ngonMap);
        continue;
      }

      // found a new ngon
      Ngons.Append(ngon);
      ngonIndex++;
    }
    if (bCleanUpNgonMap)
    {
      for (face_index = 0; face_index < face_count; face_index++)
      {
        if (omitted_face_mark == ngonMap[face_index])
          ngonMap[face_index] = ON_UNSET_UINT_INDEX;
      }
    }
    break;
  }



  return Ngons.UnsignedCount() - NgonsCount0;
}

unsigned int ON_Mesh::AddPlanarNgons(
  const unsigned int *const* vertex_face_map,
  double planar_tolerance,
  unsigned int minimum_ngon_vertex_count,
  unsigned int minimum_ngon_face_count,
  bool bAllowHoles
  )
{
  const ON_3dPointListRef vertex_list(this);
  const ON_MeshFaceList face_list(this);

  unsigned int added_ngon_count = ON_MeshNgon::FindPlanarNgons(
    vertex_list,
    face_list,
    vertex_face_map,
    planar_tolerance,
    minimum_ngon_vertex_count,
    minimum_ngon_face_count,
    bAllowHoles,
    m_NgonAllocator,
    m_NgonMap,
    m_Ngon
    );

  return added_ngon_count;
}

class ON_VertexIndexRef
{
public:
  const unsigned int* m_vertex_index_ptr; // address of a unsigned int vertex index
  unsigned int m_old_vertex_index;
  unsigned int m_new_vertex_index; // new vertex index value
};

class /* DO NOT EXPORT THIS CLASS OR PUT IT IN A HEADER FILE */ ON_MeshSeparateNgonInfo
{
  // This class is used to pass around information needed
  // by the functions used by ON_Mesh::SeparateNgons()
  // to duplicated shared vertices.
public:
  ON_MeshSeparateNgonInfo(
    ON_Mesh* mesh,
    unsigned int** vertex_face_map
    )
    : m_mesh(mesh)
    , m_vertex_face_map(vertex_face_map)
    , m_face_count(mesh ? mesh->FaceUnsignedCount() : 0)
    , m_vertex_count0(mesh ? mesh->VertexUnsignedCount() : 0)
    , m_vertex_count1(m_vertex_count0)
    , m_vertex_count2(m_vertex_count0)
  {
    if ( 0 != mesh )
    {
      m_ngondex_from_facedex_map = ( m_face_count != mesh->m_NgonMap.UnsignedCount() )
        ? mesh->CreateNgonMap()
        : mesh->NgonMap();
    
      if ( 0 == m_vertex_face_map )
      {
        m_local_vfmap.SetFromMesh(mesh,true);
        m_vertex_face_map = const_cast<unsigned int**>(m_local_vfmap.VertexFaceMap());
      }
    }
  }

public:

  bool IsValid() const
  {
    if ( 0 == m_mesh )
      return false;
    if ( m_vertex_count0 <= 3 )
      return false;
    if ( m_face_count <= 1 )
      return false;
    if ( 0 == m_vertex_face_map )
      return false;
    if ( 0 == m_ngondex_from_facedex_map )
      return false;
    if ( 0 == m_ngondex_from_facedex_map )
      return false;
    return true;
  }

  // After SetNgon() sets the ngon, 
  bool FindSharedNgonVertices(
    unsigned int ngon_index
    );

  // FindSharedNgonVertices() uses TestNgonVertex()
  bool TestNgonVertex(
    const unsigned int* vertex_index_ptr
    );

  void DuplicateSharedNgonVertices();

   bool AddVertexIndexRef(
    const unsigned int* vertex_index_ptr,
    unsigned int new_vertex_index
    )
  {
    if ( 0 == vertex_index_ptr )
      return false;
    unsigned int old_vertex_index = *vertex_index_ptr;
    if ( old_vertex_index >= m_vertex_count0 )
      return false;
    if ( new_vertex_index < m_vertex_count0 )
      return false;
    if ( 0 == m_virefpool.SizeofElement() )
      m_virefpool.Create(sizeof(ON_VertexIndexRef),0,0);
    ON_VertexIndexRef* viref = (ON_VertexIndexRef*)m_virefpool.AllocateElement();
    if ( 0 == viref )
      return false;
    viref->m_vertex_index_ptr = vertex_index_ptr;
    viref->m_old_vertex_index = old_vertex_index;
    viref->m_new_vertex_index = new_vertex_index;
    return true;
  }

  ON_Mesh* m_mesh = nullptr;
  unsigned int** m_vertex_face_map = nullptr;
  const unsigned int* m_ngondex_from_facedex_map = nullptr;
  unsigned int* m_ngon_vmap = nullptr;
  const unsigned int m_face_count;    // mesh face count
  const unsigned int m_vertex_count0; // original vertex count
  unsigned int m_vertex_count1 = 0;
  unsigned int m_vertex_count2 = 0;
  unsigned int m_ni = ON_UNSET_UINT_INDEX;
  unsigned int m_fi = ON_UNSET_UINT_INDEX;
  unsigned int m_vi= ON_UNSET_UINT_INDEX;
  unsigned int m_ngon_vmark = 0;
  const ON_MeshNgon* m_ngon = nullptr;

private:
  ON_SimpleArray<unsigned int> m_ngon_vmap_buffer;
  ON_MeshVertexFaceMap m_local_vfmap;
  ON_FixedSizePool m_virefpool;
};

void ON_MeshSeparateNgonInfo::DuplicateSharedNgonVertices()
{
  unsigned int vertex_count = m_mesh->VertexUnsignedCount();
  ON_FixedSizePoolIterator fit(m_virefpool);
  for ( ON_VertexIndexRef* vr = (ON_VertexIndexRef*)fit.FirstElement(); 
        0 != vr; 
        vr = (ON_VertexIndexRef*)fit.NextElement() 
      )
  {
    if ( 0 == vr->m_vertex_index_ptr )
      continue;
    if ( vr->m_old_vertex_index != *vr->m_vertex_index_ptr )
      continue;
    if ( vr->m_old_vertex_index >= m_vertex_count0 )
      continue;
    if ( vr->m_new_vertex_index < m_vertex_count0 )
      continue;
    if ( vr->m_new_vertex_index > vertex_count )
      continue;
    if ( vr->m_new_vertex_index == vertex_count )
    {
      if ( vertex_count != m_mesh->AppendDuplicateVertex(vr->m_old_vertex_index) )
        return;
      vertex_count++;
    }
    *const_cast<unsigned int*>(vr->m_vertex_index_ptr) = vr->m_new_vertex_index;
  }
}

bool ON_MeshSeparateNgonInfo::TestNgonVertex(
  const unsigned int* vertex_index_ptr
  )
{
  if ( 0 == vertex_index_ptr )
    return false;
  m_vi = *vertex_index_ptr;
  if ( m_vi >= m_vertex_count0 )
  {
    // The source of this vertex index contained a bogus value.
    return true;
  }

  const unsigned int n = m_ngon_vmap[m_vi];
  
  if ( m_ngon_vmark == n )
  {
    // This vertex is known to be referenced only
    // by this ngon and does not need to be tested
    // or duplicated.
    return true;
  }

  if ( m_vertex_count1 <= n && n < m_vertex_count2 )
  {
    // this vertex is flagged for duplication in this ngon.
    return AddVertexIndexRef(vertex_index_ptr,n);
  }

  unsigned int* vfm = m_vertex_face_map[m_vi];
  const unsigned int vfm_count0 = (0 != vfm) ? *vfm++ : 0;
  if ( vfm_count0 > 0 )
  {
    for ( unsigned int vfmi = 0; vfmi < vfm_count0; vfmi++ )
    {
      unsigned int vfi = vfm[vfmi];
      if( m_fi == vfi )
        continue;
      if ( vfi >= m_face_count )
        continue;
      if ( m_ni == m_ngondex_from_facedex_map[vfi] )
        continue; // face[vfi] is in this ngon

      // this vertex is shared by a face not belonging to this ngon.
      if ( false == AddVertexIndexRef(vertex_index_ptr,m_vertex_count2) )
        return false;
      m_ngon_vmap[m_vi] = m_vertex_count2;
      m_vertex_count2++;

      // Any faces in this ngon that reference vertex m_vi
      // will be modified to reference vertex m_vertex_count2.
      // These faces need to be removed from vfm[], so
      // future searches for faces that share vertex m_vi
      // will be correct.
      unsigned int vfm_count1 = 0;
      for ( vfmi = 0; vfmi < vfm_count0; vfmi++ )
      {
        unsigned int vfi_local = vfm[vfmi];
        if( m_fi == vfi_local )
          continue;
        if ( vfi_local < m_face_count && m_ni == m_ngondex_from_facedex_map[vfi_local] )
          continue; // face[vfi_local] is in this ngon
        if ( vfmi > vfm_count1 )
          vfm[vfm_count1] = vfi_local;
        vfm_count1++;
      }
      vfm[-1] = vfm_count1;
      return true;
    }
  }

  // vertex is not shared
  m_ngon_vmap[m_vi] = m_ngon_vmark;
  return true;
}

bool ON_MeshSeparateNgonInfo::FindSharedNgonVertices(
  unsigned int ngon_index
  )
{
  m_ni = ngon_index;
  m_fi = ON_UNSET_UINT_INDEX;
  m_vi = ON_UNSET_UINT_INDEX;
  m_ngon_vmark = 0;
  m_ngon = m_mesh ? m_mesh->Ngon(m_ni) : 0;

  if ( 0 == m_ngon )
    return true;
  if ( m_ngon->m_Vcount <= 0 && m_ngon->m_Fcount <= 0 )
    return true;
  if ( m_ngon->m_Vcount > 0 && 0 == m_ngon->m_vi )
    return true;
  if ( m_ngon->m_Fcount > 0 && 0 == m_ngon->m_fi )
    return true;

  unsigned int prev_ngon_mark = m_ngon_vmark;
  m_ngon_vmark = m_ni+1 < m_vertex_count0 ? (m_ni+1) : 1;
  if ( 0 == m_ngon_vmap || prev_ngon_mark >= m_ngon_vmark )
  {
    if ( 0 == m_ngon_vmap )
    {
      m_ngon_vmap_buffer.Reserve(m_vertex_count0);
      m_ngon_vmap_buffer.SetCount(m_vertex_count0);
      m_ngon_vmap = m_ngon_vmap_buffer.Array();
    }
    m_ngon_vmap_buffer.Zero();    
  }

  m_vertex_count2 = m_vertex_count1;

  for ( unsigned int k = 0; k < m_ngon->m_Fcount; k++ )
  {
    m_fi = m_ngon->m_fi[k];
    if ( m_fi >= m_face_count )
      continue; // bogus face index

    const unsigned int* fvi = (const unsigned int*)m_mesh->m_F[m_fi].vi;
    for ( unsigned int j = 0; j < 4; j++ )
    {
      if ( false == TestNgonVertex(fvi+j) )
        return false;
    }
  }

  m_fi = ON_UNSET_UINT_INDEX;

  for ( unsigned k = 0; k < m_ngon->m_Vcount; k++ )
  {
    if ( false == TestNgonVertex(m_ngon->m_vi + k) )
      return false;
  }

  m_vertex_count1 = m_vertex_count2;

  return true;
}

bool ON_Mesh::SeparateNgons(
  unsigned int** vertex_face_map,
  unsigned int ngon_index0,
  unsigned int ngon_index1
  )
{
  if ( ngon_index1 > NgonUnsignedCount() )
    ngon_index1 = NgonUnsignedCount();
  if ( ngon_index1 <= ngon_index0 )
    return false;

  ON_MeshSeparateNgonInfo X(this,vertex_face_map);
  if ( false == X.IsValid() )
    return false;

  // Count number of new vertices that are required
  // to separate the ngons and save a list of what
  // needs to be updated in "X".  This loop modifies
  // vertex_face_map[] by removing references
  // to faces of vertices that will be duplicated.
  for ( unsigned int ni = ngon_index0; ni < ngon_index1; ni++ )
  {
    if( false == X.FindSharedNgonVertices(ni) )
      return 0;
  }

  // Add new vertices to ngons.
  if ( X.m_vertex_count1 > X.m_vertex_count0 )
  {
    // Duplicate the shared vertices and update the
    // ngon and face vertex index lists to reference
    // the duplicated vertices.
    X.DuplicateSharedNgonVertices();
  }

  return (VertexUnsignedCount() > X.m_vertex_count0);
}


bool ON_Mesh::SetNgonVertexNormals(
  unsigned int ngon_index0,
  unsigned int ngon_index1
  )
{
  if ( false == HasVertexNormals() )
    return false;

  if ( ngon_index1 > NgonUnsignedCount() )
    ngon_index1 = NgonUnsignedCount();
  if ( ngon_index1 <= ngon_index0 )
    return false;

  ON_3dPointListRef vertex_list(this);
  ON_MeshFaceList face_list(this);
  
  unsigned int ni, nvi, vi, nfi, fi;
  const ON_MeshNgon* ngon;

  const unsigned int vertex_count0 = vertex_list.PointCount();
  const unsigned int face_count0 = face_list.FaceCount();

  ON_3dVector dN;
  ON_3fVector fN;
  bool rc = false;

  for ( ni = ngon_index0; ni < ngon_index1; ni++ )
  {
    ngon = m_Ngon[ni];
    if ( 0 == ngon )
      continue;

    // validate ngon
    if ( ngon->m_Vcount > 0 && 0 == ngon->m_vi )
      continue;
    if ( ngon->m_Fcount <= 0 || 0 == ngon->m_fi )
      continue;
      
    // Get ngon plane equation and normal.
    fi = ngon->m_fi[0];
    if ( fi >= face_count0 )
      continue;
    if ( !m_F[fi].ComputeFaceNormal(vertex_list,dN) )
      continue;

    fN = dN;

    // update boundary vertex normals
    for ( nvi = 0; nvi < ngon->m_Vcount; nvi++ )
    {
      vi = ngon->m_vi[nvi];
      if ( vi >= vertex_count0 )
        continue;
      m_N[vi] = fN;
      rc = true;
    }

    // update face vertex normals
    for (nfi = 0; nfi < ngon->m_Fcount; nfi++ )
    {
      fi = ngon->m_fi[nfi];
      if ( fi >= face_count0 )
        continue;
      unsigned int* fvi = (unsigned int*)m_F[fi].vi;
      for ( unsigned int j = 0; j < 4; j++ )
      {
        vi = fvi[j];
        if ( vi >= vertex_count0 )
          continue;
        rc = true;
        m_N[vi] = fN;
      }
    }
  }

  return rc;
}

bool ON_Mesh::RemoveNgonInteriorVertices(
  const unsigned int *const* vertex_face_map,
  unsigned int ngon_index0,
  unsigned int ngon_index1
  )
{
  if ( ngon_index1 > NgonUnsignedCount() )
    ngon_index1 = NgonUnsignedCount();
  if ( ngon_index1 <= ngon_index0 )
    return false;

  ON_MeshVertexFaceMap m_local_vfmap;

  for ( unsigned int ni = ngon_index0; ni < ngon_index1; ni++ )
  {
  }

  return false;
}

unsigned int ON_MeshTopology::NgonIndexFromTopologyVertexIndex(
  unsigned int topvi,
  const unsigned int* mesh_facedex_to_ngondex_map
  ) const
{
  if ( topvi >= m_topv.UnsignedCount() )
    return ON_UNSET_UINT_INDEX;
  const ON_MeshTopologyVertex& v = m_topv[topvi];
  if ( v.m_tope_count <= 2 || 0 == v.m_topei )
    return ON_UNSET_UINT_INDEX;

  const ON_Mesh* mesh = m_mesh;
  if ( 0 == mesh || false == mesh->HasNgons() )
    return ON_UNSET_UINT_INDEX;
  if ( 0 == mesh_facedex_to_ngondex_map )
  {
    mesh_facedex_to_ngondex_map = mesh->NgonMap();
    if ( 0 == mesh_facedex_to_ngondex_map )
      return ON_UNSET_UINT_INDEX;
  }
  
  const unsigned int ngon_index = NgonIndexFromTopologyEdgeIndex((unsigned int)(v.m_topei[0]),mesh_facedex_to_ngondex_map);
  if ( ON_UNSET_UINT_INDEX == ngon_index )
    return ON_UNSET_UINT_INDEX;
  for ( int tvtei = 1; tvtei < v.m_tope_count; tvtei++ )
  {
    if ( ngon_index != NgonIndexFromTopologyEdgeIndex((unsigned int)(v.m_topei[tvtei]),mesh_facedex_to_ngondex_map) )
      return ON_UNSET_UINT_INDEX;
  }
  return ngon_index;
}

unsigned int ON_MeshTopology::NgonIndexFromTopologyEdgeIndex(
  unsigned int topei,
  const unsigned int* mesh_facedex_to_ngondex_map
  ) const
{
  if ( topei >= m_tope.UnsignedCount() )
    return ON_UNSET_UINT_INDEX;
  const ON_MeshTopologyEdge& e = m_tope[topei];
  if ( e.m_topf_count <= 0 || 0 == e.m_topfi )
    return ON_UNSET_UINT_INDEX;
  const ON_Mesh* mesh = m_mesh;
  if ( 0 == mesh || false == mesh->HasNgons() )
    return ON_UNSET_UINT_INDEX;
  if ( 0 == mesh_facedex_to_ngondex_map )
  {
    mesh_facedex_to_ngondex_map = mesh->NgonMap();
    if ( 0 == mesh_facedex_to_ngondex_map )
      return ON_UNSET_UINT_INDEX;
  }
  const unsigned int mesh_face_count = mesh->FaceUnsignedCount();

  const ON_MeshNgon* ngon = 0;
  unsigned int ngon_index = ON_UNSET_UINT_INDEX;
  unsigned int rc = ON_UNSET_UINT_INDEX;
  for ( int tefi = 0; tefi < e.m_topf_count; tefi++ )
  {
    unsigned int fi = (unsigned int)e.m_topfi[tefi];
    if ( fi >= mesh_face_count )
    {
      // bogus face index
      return ON_UNSET_UINT_INDEX;
    }

    if ( 0 != ngon && ngon_index == mesh_facedex_to_ngondex_map[fi] )
    {
      // this edge has 2 or more faces and all the faces 
      // that have been checked belong to the same ngon.
      rc = ngon_index;
      continue;
    }

    if ( 0 != ngon || ON_UNSET_UINT_INDEX == mesh_facedex_to_ngondex_map[fi] )
    {
      // this edge is not interior to the same ngon
      return ON_UNSET_UINT_INDEX;
    }

    ngon_index = mesh_facedex_to_ngondex_map[fi];
    ngon = mesh->Ngon(ngon_index);
    if ( 0 == ngon )
    {
      // bogus ngon information - let user pick this edge
      return ON_UNSET_UINT_INDEX;
    }
  }
  return rc;
}


ON_Plane ON_Plane::FromPointList(
  size_t point_list_count,
  const ON_3dPoint* point_list
  )
{
  ON_3dPointListRef vertex_list;
  vertex_list.SetFromDoubleArray(point_list_count,3,(const double*)point_list);
  return ON_Plane::FromPointList(vertex_list);
}

ON_Plane ON_Plane::FromPointList(
  const ON_SimpleArray< ON_3dPoint >& point_list
  )
{
  return ON_Plane::FromPointList(point_list.UnsignedCount(),point_list.Array());
}


ON_Plane ON_Plane::FromPointList(
  size_t point_list_count,
  const ON_3fPoint* point_list
  )
{
  ON_3dPointListRef vertex_list;
  vertex_list.SetFromFloatArray(point_list_count,3,(const float*)point_list);
  return ON_Plane::FromPointList(vertex_list);
}

ON_Plane ON_Plane::FromPointList(
  const ON_SimpleArray< ON_3fPoint >& point_list
  )
{
  return ON_Plane::FromPointList(point_list.UnsignedCount(),point_list.Array());
}


ON_Plane ON_Plane::FromPointList(
  const class ON_3dPointListRef& point_list
  )
{
  return ON_Plane::FromPointList(point_list.PointCount(),0,point_list);
}

ON_Plane ON_Plane::FromPointList(
  size_t point_index_count,
  const unsigned int* point_index_list,
  const class ON_3dPointListRef& point_list
  )
{
  const size_t point_index_stride = (0 != point_index_list) ? 1 : 0;

  return ON_Plane::FromPointList(
    point_index_count,
    point_index_stride,
    point_index_list,
    point_list
    );
}

ON_Plane ON_Plane::FromPointList(
  size_t point_index_count,
  size_t point_index_stride,
  const unsigned int* point_index_list,
  const class ON_3dPointListRef& point_list
  )
{
  unsigned int i;
  ON_3dPoint Pi, Pi0, Pi1;

  //////////////////////////////////////////////////////////
  //
  // Do not tolerate garbage.
  //
  if ( point_index_count < 3 || point_index_count >= (size_t)ON_UNSET_UINT_INDEX )
    return ON_Plane::UnsetPlane;

  if ( 0 != point_index_list )
  {
    if ( point_index_stride < 1 || point_index_stride >= (size_t)ON_UNSET_UINT_INDEX )
      return ON_Plane::UnsetPlane;
  }

  const unsigned int point_count = (unsigned int)point_index_count;
  const unsigned int point_stride = (0 != point_index_list ) ? ((unsigned int)point_index_stride) : 1;
  const unsigned int vertex_count = point_list.PointCount();
  
  if ( vertex_count < point_count )
    return ON_Plane::UnsetPlane;

  if ( point_index_list )
  {
    for ( i = 0; i < point_count; i += point_stride )
    {
      if ( point_index_list[i] >= vertex_count )
        return ON_Plane::UnsetPlane;
    }
  }

  i = point_stride*(point_count-1);
  Pi = point_list[point_index_list ? point_index_list[i] : i];
  for ( i = 0; i < point_count; i += point_stride )
  {
    Pi0 = Pi;
    Pi = point_list[point_index_list ? point_index_list[i] : i];
    if ( false == Pi.IsValid() )
      return ON_Plane::UnsetPlane;
    if ( false == (Pi0 != Pi) )
      return ON_Plane::UnsetPlane;
  }

  //////////////////////////////////////////////////////////
  //
  // Find a plane to project the 3d points to.
  //
  ON_3dVector N(ON_3dVector::ZeroVector);
  ON_3dVector X(ON_3dVector::UnsetVector);
  if ( point_index_count <= 4 )
  {
    // use "standard" face normal for quads and triangles.
    const unsigned int index_0123[4] = {0,1,2,3};
    if ( 0 == point_index_list )
      point_index_list = index_0123;
    Pi0 = point_list[point_index_list[point_stride*(point_count-1)]];
    Pi1 = point_list[point_index_list[point_stride]];
    X = Pi1 - Pi0;
    Pi0 = point_list[point_index_list[0]];
    Pi1 = point_list[point_index_list[2*point_stride]];
    N = ON_CrossProduct(
      X,
      Pi1-Pi0
    );
    if ( X.Length() < Pi1.DistanceTo(Pi0) )
      X = Pi1-Pi0;
  }

  if (N == ON_3dVector::ZeroVector)
  {
    // find far apart points
    unsigned int i0 = 0;
    unsigned int i1 = point_stride;
    ON_Line L(point_list[point_index_list ? point_index_list[i0] : i0],point_list[point_index_list ? point_index_list[i1] : i1]);
    double d = L.Length();
    for ( i = i1+point_stride; i < point_count*point_stride; i += point_stride )
    {
      Pi = point_list[point_index_list ? point_index_list[i] : i];
      double d0 = L.from.DistanceTo(Pi);
      double d1 = L.to.DistanceTo(Pi);
      if ( d0 > d && d0 >= d1 )
      {
        d = d0;
        i1 = i;
        L.to = Pi;
      }
      else if ( d1 > d )
      {
        d = d1;
        i0 = i;
        L.from = Pi;
      }
    }
    if ( i0 == i1 || !(d > 0.0) )
      return ON_Plane::UnsetPlane;
    X = L.Direction();

    d = 0.0;
    unsigned int i2 = ON_UNSET_UINT_INDEX;
    ON_3dPoint P(ON_3dPoint::UnsetPoint);
    for ( i = 0; i < point_count*point_stride; i += point_stride )
    {
      if ( i == i0 || i == i1 )
        continue;
      Pi = point_list[point_index_list ? point_index_list[i] : i];
      double t1 = ON_UNSET_VALUE;
      if ( !L.ClosestPointTo(Pi,&t1) || !(t1 != ON_UNSET_VALUE) )
        continue;    
      ON_3dPoint Q = L.PointAt(t1);
      double d1 = Q.DistanceTo(Pi);
      if ( d1 > d )
      {
        d = d1;
        P = Q;
        i2 = i;
      }
    }
    if ( ON_UNSET_UINT_INDEX == i2 || i0 == i2 || i1 == i2 || !(d > 0.0) || !P.IsValid() )
      return ON_Plane::UnsetPlane;
    Pi = point_list[point_index_list ? point_index_list[i2] : i2];
    N = ON_CrossProduct(X,Pi-P);
  }

  ON_Plane plane;

  if      ( 0.0 != N.x && 0.0 == N.y && 0.0 == N.z )
    i = 0;
  else if ( 0.0 == N.x && 0.0 != N.y && 0.0 == N.z )
    i = 1;
  else if ( 0.0 == N.x && 0.0 == N.y && 0.0 != N.z )
    i = 2;
  else
    i = 3;

  if ( i < 3 )
  {
    ON_3dVector a[3] = {ON_3dVector::XAxis,ON_3dVector::YAxis,ON_3dVector::ZAxis};
    plane.zaxis = a[i];
    plane.xaxis = a[(i+1)%3];
    plane.yaxis = a[(i+2)%3];
  }
  else
  {
    plane.zaxis = N;
    plane.xaxis = X;
    if ( !plane.zaxis.Unitize() )
      return ON_Plane::UnsetPlane;
    if ( !plane.xaxis.Unitize() )
      return ON_Plane::UnsetPlane;
    plane.yaxis = ON_CrossProduct(plane.zaxis,plane.xaxis);
  }
  plane.origin = point_list[point_index_list ? point_index_list[0] : 0];
  plane.UpdateEquation();
  if ( !plane.IsValid() )
    return ON_Plane::UnsetPlane;
  
  return plane;
}




const ON_MeshNgonIterator ON_MeshNgonIterator::EmptyMeshNgonIterator;

ON_MeshNgonIterator::ON_MeshNgonIterator(
  const class ON_Mesh* mesh
  )
{
  if ( 0 != mesh )
    SetMesh(mesh,mesh->NgonMap());
}

ON_MeshNgonIterator::ON_MeshNgonIterator(
  const ON_MeshNgonIterator& src
  )
  : m_mesh(src.m_mesh)
  , m_facedex_to_ngondex_map(src.m_facedex_to_ngondex_map)
  , m_current_ngon_ci(src.m_current_ngon_ci)
  , m_mesh_face_count(src.m_mesh_face_count)
  , m_mesh_ngon_count(src.m_mesh_ngon_count)
  , m_iterator_index(src.m_iterator_index)
{
  if (    ON_COMPONENT_INDEX::mesh_face == m_current_ngon_ci.m_type 
       || ON_COMPONENT_INDEX::mesh_ngon == m_current_ngon_ci.m_type 
     )
  {
    if ( 0 != m_mesh )
      m_current_ngon = (ON__UINT_PTR)(m_mesh->NgonFromComponentIndex(m_ngon_buffer,m_current_ngon_ci));
  }
}

ON_MeshNgonIterator& ON_MeshNgonIterator::operator=(
  const ON_MeshNgonIterator& src
  )
{
  if ( this != &src )
  {
     m_mesh = src.m_mesh;
     m_facedex_to_ngondex_map = src.m_facedex_to_ngondex_map;
     m_current_ngon_ci = src.m_current_ngon_ci;
     m_current_ngon = 0;
     m_mesh_face_count = src.m_mesh_face_count;
     m_mesh_ngon_count = src.m_mesh_ngon_count;
     m_iterator_index = src.m_iterator_index;
    if (    ON_COMPONENT_INDEX::mesh_face == m_current_ngon_ci.m_type 
         || ON_COMPONENT_INDEX::mesh_ngon == m_current_ngon_ci.m_type 
       )
    {
      if ( 0 != m_mesh )
        m_current_ngon = (ON__UINT_PTR)(m_mesh->NgonFromComponentIndex(m_ngon_buffer,m_current_ngon_ci));
    }
  }
  return *this;
}

void ON_MeshNgonIterator::SetMesh(
  const class ON_Mesh* mesh,
  const unsigned int* meshfdex_to_meshngondex_map
  )
{
  *this = ON_MeshNgonIterator::EmptyMeshNgonIterator;
  m_mesh = mesh;
  m_facedex_to_ngondex_map = (0 != m_mesh && 0 == meshfdex_to_meshngondex_map)
                            ? m_mesh->NgonMap()
                            : meshfdex_to_meshngondex_map;
  if ( 0 != m_mesh )
  {
    m_mesh_face_count = m_mesh->FaceUnsignedCount();
    m_mesh_ngon_count = m_mesh->NgonCount();
    m_current_ngon_ci.Set(ON_COMPONENT_INDEX::invalid_type,1);
  }
}

const ON_Mesh* ON_MeshNgonIterator::Mesh() const
{
  return m_mesh;
}

const class ON_MeshNgon* ON_MeshNgonIterator::FirstNgon()
{
  m_current_ngon_ci.Set(ON_COMPONENT_INDEX::invalid_type,1);
  m_current_ngon = 0;
  m_iterator_index = 0;
  return NextNgon();
}

const class ON_MeshNgon* ON_MeshNgonIterator::NextNgon()
{
  unsigned int fi, ni;
  
  const class ON_MeshNgon* ngon = 0;
  switch( m_current_ngon_ci.m_type )
  {
  case ON_COMPONENT_INDEX::invalid_type:
    m_current_ngon = 0;
    if ( 1 != m_current_ngon_ci.m_index )
      break;
    m_current_ngon_ci.Set(ON_COMPONENT_INDEX::mesh_ngon,-1);
    m_iterator_index = ON_UNSET_UINT_INDEX;
    // no break here - iterator will look through ngon list

  case ON_COMPONENT_INDEX::mesh_ngon:
    for ( ni = ( -1 == m_current_ngon_ci.m_index ) ? 0 : m_current_ngon_ci.UnsignedIndex()+1;
          ni < m_mesh_ngon_count;
          ni++
        )
    {
      ngon = m_mesh->Ngon(ni);
      if ( 0 == ngon )
        continue;
      if ( ON_UNSET_UINT_INDEX == m_iterator_index )
        m_iterator_index = 0;
      else
        m_iterator_index++;
      m_current_ngon_ci.m_index = (int)ni;
      m_current_ngon = (ON__UINT_PTR)ngon;
      return ngon;
    }
    m_current_ngon_ci.Set(ON_COMPONENT_INDEX::mesh_face,-1);
    // no break here - iterator will look for mesh faces that are not part of ngons

  case ON_COMPONENT_INDEX::mesh_face:
    for ( fi = ( -1 == m_current_ngon_ci.m_index ) ? 0 : m_current_ngon_ci.UnsignedIndex()+1;
          fi < m_mesh_face_count;
          fi++
        )
    {
      ni = m_facedex_to_ngondex_map ? m_facedex_to_ngondex_map[fi] : ON_UNSET_UINT_INDEX;
      if ( ni < m_mesh_ngon_count )
        continue;
      ngon = ON_MeshNgon::NgonFromMeshFace(m_ngon_buffer,fi,(const unsigned int*)m_mesh->m_F[fi].vi);
      if ( 0 == ngon )
        continue;
      if ( ON_UNSET_UINT_INDEX == m_iterator_index )
        m_iterator_index = 0;
      else
        m_iterator_index++;
      m_current_ngon_ci.m_index = (int)fi;
      m_current_ngon = (ON__UINT_PTR)ngon;
      return ngon;
    }
    // no break here - iterator is finished

  default:
    m_current_ngon_ci.Set(ON_COMPONENT_INDEX::invalid_type,0);
    m_current_ngon = 0;
  }

  return ngon;
}
  
const class ON_MeshNgon* ON_MeshNgonIterator::CurrentNgon()
{
  const class ON_MeshNgon* ngon = 0;
  if ( 0 != m_current_ngon )
  {
    ngon = (0 != m_mesh)
         ? m_mesh->NgonFromComponentIndex(m_ngon_buffer,m_current_ngon_ci)
         : 0;
    if ( m_current_ngon != (ON__UINT_PTR)ngon )
    {
      ngon = 0;
      m_current_ngon = 0;
    }
  }
  return ngon;
}

ON_COMPONENT_INDEX ON_MeshNgonIterator::CurrentNgonComponentIndex() const
{
  return m_current_ngon_ci;
}

bool ON_MeshNgonIterator::CurrentNgonIsMeshFace() const
{
  return (    ON_COMPONENT_INDEX::mesh_face == m_current_ngon_ci.m_type 
           && m_current_ngon == (ON__UINT_PTR)&m_ngon_buffer 
         );
}

bool ON_MeshNgonIterator::CurrentNgonIsMeshNgon() const
{
  return (   0 != m_current_ngon 
          && 0 != m_mesh 
          && ON_COMPONENT_INDEX::mesh_ngon == m_current_ngon_ci.m_type
          && m_current_ngon == (ON__UINT_PTR)m_mesh->Ngon(m_current_ngon_ci.m_index)
          );
}
  
void ON_MeshNgonIterator::Reset()
{
  const ON_Mesh* mesh = m_mesh;
  const unsigned int* fdex_to_ndex_map = m_facedex_to_ngondex_map;
  SetMesh(mesh,fdex_to_ndex_map);
}


unsigned int ON_MeshNgonIterator::Count() const
{
	unsigned int count = 0;

  if (nullptr != m_mesh)
  {
    count = m_mesh->m_F.UnsignedCount();
    unsigned int explicit_ngon_count = m_mesh->NgonUnsignedCount();
    if (explicit_ngon_count > 0)
    {
      // subtract the number of mesh faces that are in explicit ngons from count.
      const ON_MeshNgon* const * ngons = m_mesh->Ngons();
      if (nullptr != ngons)
      {
        for (unsigned int ni = 0; ni < explicit_ngon_count; ni++)
        {
          const ON_MeshNgon* ngon = ngons[ni];
          if (nullptr == ngon)
            explicit_ngon_count--;
          else if (ngon->m_Fcount <= count)
            count -= ngon->m_Fcount;
          else
          {
            ON_ERROR("Invalid ngon information on mesh");
            return 0;
          }
        }
      }

      // add the number of explicit ngons to count
      count += explicit_ngon_count;
    }
  }

  // return the number of explicit ngons + the number of faces that are not in an explicit ngon.
	return count;
}
