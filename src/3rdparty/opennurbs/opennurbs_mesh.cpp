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
#include <functional>
#include <unordered_map>

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif




// NEVER COPY OR MOVE THE NEXT 2 LINES
#define ON_BOZO_VACCINE_17F24E7521BE4a7b9F3D7F85225247E3
#define ON_BOZO_VACCINE_B5628CA982C44CAE9883487B3E4AB28B
// NEVER COPY OR MOVE THE PREVIOUS 2 LINES




///////////////////////////////////////////////////////
//
// Rhino V5 Double precision vertices user data
// Used to read and write version 5 .3dm files.
//

class /* DO NOT copy, move, or export this class */ ON_V5_MeshDoubleVertices : public ON_UserData
{
  ON_OBJECT_DECLARE(ON_V5_MeshDoubleVertices);

public:
  ON_V5_MeshDoubleVertices();
  ~ON_V5_MeshDoubleVertices();  

  // default copy constructor and operator= work fine.

  /*
    If the mesh has ON_V5_MeshDoubleVertices user data, then return
    a pointer to it.
  */
  static ON_V5_MeshDoubleVertices* GetV5(const ON_Mesh* mesh);

  /*
    Attach new ON_V5_MeshDoubleVertices user data to the mesh.
    This will fail and return nullptr if the mesh already has
    ON_V5_MeshDoubleVertices user data.
  */
  static ON_V5_MeshDoubleVertices* AttachV5(const ON_Mesh* mesh);

  // virtual ON_Object overrides
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  void Dump( ON_TextLog& ) const override;
  unsigned int SizeOf() const override;
  ON__UINT32 DataCRC(ON__UINT32) const override;
  bool Write(ON_BinaryArchive&) const override;
  bool Read(ON_BinaryArchive&) override;

  // virtual ON_UserData overrides
  bool GetDescription( ON_wString& ) override;
  bool Archive() const override;
  bool Transform( const ON_Xform& ) override;

  bool DeleteAfterWrite(
    const class ON_BinaryArchive& archive,
    const class ON_Object* parent_object
    ) const override;

  bool DeleteAfterRead( 
    const class ON_BinaryArchive& archive,
    class ON_Object* parent_object
    ) const override;


#if !defined(ON_BOZO_VACCINE_17F24E7521BE4a7b9F3D7F85225247E3)
#error DO NOT copy, move or export the definition of ON_V5_MeshDoubleVertices
#endif
#undef ON_BOZO_VACCINE_17F24E7521BE4a7b9F3D7F85225247E3

  ON__UINT32 DoubleCRC() const;
  static ON__UINT32 FloatCRC( const ON_3fPointArray& );

  // If m_dV.Count() != m_dcount or
  // m_dCRC != ON_CRC32(0,m_dV.Count()*sizeof(ON_3dPoint),m_dV.Array()),
  // then somebody has changed m_dV and not called
  // SetDoublePrecisionVerticesAsValid() to mark the
  // values as valid.
  //
  // If ON_Mesh.M_V.Count() != m_fcount or
  // m_fCRC != ON_CRC32(0,m_V.Count()*sizeof(ON_3fPoint),m_V.Array()),
  // then somebody has changed ON_Mesh.m_V and not called
  // SetSinglePrecisionVerticesAsValid() to mark the
  // values as valid.
  //
  // Whenever there is a question about which values are valid,
  // it is assumed the m_V array is valid and the double precision
  // information should be destroyed.
  int m_fcount = 0;  // single precision vertex count
  int m_dcount = 0;  // double precision vertex count
  ON__UINT32 m_fCRC = 0; // crc of float vertex array
  ON__UINT32 m_dCRC = 0; // crc of double vertex array

  ON_3dPointArray m_V5_dV; // double precision mesh vertices
};


ON_MeshCurveParameters::ON_MeshCurveParameters()
{
  memset(this,0,sizeof(*this));
}

ON_OBJECT_IMPLEMENT(ON_Mesh,ON_Geometry,"4ED7D4E4-E947-11d3-BFE5-0010830122F0");

/*
ON_MeshEdge& ON_MeshEdge::operator=( const ON_MeshEdge& src )
{
  int fc = src.m_fcount+(src.m_fcount%1);
  if ( fc <= 2 ) {
    if ( m_fi && m_fi != m_private_fi ) onfree((void*)m_fi);
    m_fi = m_private_fi;
    fc = 2;
  }
  else {
    if ( (m_fcount+(m_fcount%1)) != fc ) {
      if ( m_fi == m_private_fi )
        m_fi = 0;
      m_fi = (int*)onrealloc(m_fi,fc*sizeof(*m_fi));
    }
  }
  memcpy(m_fi,src.m_fi,fc*sizeof(*m_fi));
  m_fcount=src.m_fcount;
  return *this;
}

void ON_MeshEdge::AppendFaceIndex(int face_index)
{
  if ( m_fcount>0 && !(m_fcount%1) ) {
    if ( m_fi == m_private_fi ) {
      m_fi = (int*)onmalloc((m_fcount+2)*sizeof(*m_fi));
      m_fi[0] = m_private_fi[0];
      m_fi[1] = m_private_fi[1];
    }
    else {
      m_fi = (int*)onrealloc(m_fi,(m_fcount+2)*sizeof(*m_fi));
    }
  }
  m_fi[m_fcount++] = face_index;
}
*/

bool
ON_MeshFace::IsValid(int mesh_vertex_count) const
{
  return (vi[0] >= 0 && vi[0] < mesh_vertex_count
    && vi[1] >= 0 && vi[1] < mesh_vertex_count
    && vi[2] >= 0 && vi[2] < mesh_vertex_count
    && vi[3] >= 0 && vi[3] < mesh_vertex_count
    && vi[0] != vi[1] && vi[1] != vi[2] && vi[2] != vi[0]
    && (vi[2] == vi[3] || (vi[0] != vi[3] && vi[1] != vi[3])));
}

bool
ON_MeshFace::IsValid(unsigned int mesh_vertex_count) const
{
  const unsigned int* uvi = (const unsigned int*)vi;
  return (uvi[0] < mesh_vertex_count
    && uvi[1] < mesh_vertex_count
    && uvi[2] < mesh_vertex_count
    && uvi[3] < mesh_vertex_count
    && uvi[0] != uvi[1] && uvi[1] != uvi[2] && uvi[2] != uvi[0]
    && (uvi[2] == uvi[3] || (uvi[0] != uvi[3] && uvi[1] != uvi[3])));
}


bool
ON_MeshFace::IsValid(int mesh_vertex_count, const ON_3fPoint* V ) const
{
  if ( !IsValid(mesh_vertex_count) )
    return false;
  if ( !(V[vi[0]] != V[vi[1]]) )
    return false;
  if ( !(V[vi[0]] != V[vi[2]]) )
    return false;
  if ( !(V[vi[1]] != V[vi[2]]) )
    return false;
  if ( vi[2] != vi[3] )
  {
  if ( !(V[vi[0]] != V[vi[3]]) )
    return false;
  if ( !(V[vi[1]] != V[vi[3]]) )
    return false;
  if ( !(V[vi[2]] != V[vi[3]]) )
    return false;
  }
  return true;
}


bool
ON_MeshFace::IsValid(int mesh_vertex_count, const ON_3dPoint* V ) const
{
  if ( !IsValid(mesh_vertex_count) )
    return false;
  if ( !(V[vi[0]] != V[vi[1]]) )
    return false;
  if ( !(V[vi[0]] != V[vi[2]]) )
    return false;
  if ( !(V[vi[1]] != V[vi[2]]) )
    return false;
  if ( vi[2] != vi[3] )
  {
  if ( !(V[vi[0]] != V[vi[3]]) )
    return false;
  if ( !(V[vi[1]] != V[vi[3]]) )
    return false;
  if ( !(V[vi[2]] != V[vi[3]]) )
    return false;
  }
  return true;
}


bool ON_MeshFace::Repair(
  int mesh_vertex_count
  )
{
  ON_MeshFace f;
  int fvi_count = 0;
  f.vi[0] = f.vi[1] = f.vi[2] = f.vi[3] = -1;
  
  if ( vi[0] >= 0 && vi[0] < mesh_vertex_count )
    f.vi[fvi_count++] = vi[0];

  if ( vi[1] >= 0 && vi[1] < mesh_vertex_count && f.vi[0] != vi[1] )
    f.vi[fvi_count++] = vi[1];

  if ( vi[2] >= 0 && vi[2] < mesh_vertex_count && f.vi[0] != vi[2] && f.vi[1] != vi[2] )
    f.vi[fvi_count++] = vi[2];

  if ( vi[3] >= 0 && vi[3] < mesh_vertex_count && f.vi[0] != vi[3] && f.vi[1] != vi[3] && f.vi[2] != vi[3] )
    f.vi[fvi_count++] = vi[3];
  
  if ( fvi_count < 3 )
    return false;
 
  if ( 3 == fvi_count )
    f.vi[3] = f.vi[2];
  
  if ( !f.IsValid(mesh_vertex_count) )
    return false;

  vi[0] = f.vi[0];
  vi[1] = f.vi[1];
  vi[2] = f.vi[2];
  vi[3] = f.vi[3];

  return true;
}

bool ON_MeshFace::Repair(
  int mesh_vertex_count,
  const ON_3fPoint* V
  )
{
  ON_MeshFace f;
  int fvi_count = 0;
  f.vi[0] = f.vi[1] = f.vi[2] = f.vi[3] = -1;
  
  if ( vi[0] >= 0 && vi[0] < mesh_vertex_count && V[vi[0]].IsValid() )
    f.vi[fvi_count++] = vi[0];

  if (vi[1] >= 0 && vi[1] < mesh_vertex_count && f.vi[0] != vi[1] && V[vi[1]].IsValid())
  {
    if ( 0 == fvi_count || V[f.vi[0]] != V[vi[1]] )
      f.vi[fvi_count++] = vi[1];
  }

  if ( fvi_count < 1 )
    return false;

  if ( vi[2] >= 0 && vi[2] < mesh_vertex_count && f.vi[0] != vi[2] && f.vi[1] != vi[2] && V[vi[2]].IsValid() && V[f.vi[0]] != V[vi[2]] )
  {
    if ( 1 == fvi_count || V[f.vi[1]] != V[vi[2]] )
      f.vi[fvi_count++] = vi[2];
  }

  if ( fvi_count < 2 )
    return false;

  if ( vi[3] >= 0 && vi[3] < mesh_vertex_count && f.vi[0] != vi[3] && f.vi[1] != vi[3] && f.vi[2] != vi[3] && V[vi[3]].IsValid() && V[f.vi[0]] != V[vi[3]] && V[f.vi[1]] != V[vi[3]] )
  {
    if ( 2 == fvi_count || V[f.vi[2]] != V[vi[3]] )
      f.vi[fvi_count++] = vi[3];
  }
  
  if ( fvi_count < 3 )
    return false;
 
  if ( 3 == fvi_count )
    f.vi[3] = f.vi[2];
  
  if ( !f.IsValid(mesh_vertex_count) )
    return false;

  vi[0] = f.vi[0];
  vi[1] = f.vi[1];
  vi[2] = f.vi[2];
  vi[3] = f.vi[3];

  return true;
}


bool ON_MeshFace::Repair(
  int mesh_vertex_count,
  const ON_3dPoint* V
  )
{
  ON_MeshFace f;
  int fvi_count = 0;
  f.vi[0] = f.vi[1] = f.vi[2] = f.vi[3] = -1;
  
  if ( vi[0] >= 0 && vi[0] < mesh_vertex_count && V[vi[0]].IsValid() )
    f.vi[fvi_count++] = vi[0];

  if (vi[1] >= 0 && vi[1] < mesh_vertex_count && f.vi[0] != vi[1] && V[vi[1]].IsValid())
  {
    if ( 0 == fvi_count || V[f.vi[0]] != V[vi[1]] )
      f.vi[fvi_count++] = vi[1];
  }

  if ( fvi_count < 1 )
    return false;

  if ( vi[2] >= 0 && vi[2] < mesh_vertex_count && f.vi[0] != vi[2] && f.vi[1] != vi[2] && V[vi[2]].IsValid() && V[f.vi[0]] != V[vi[2]] )
  {
    if ( 1 == fvi_count || V[f.vi[1]] != V[vi[2]] )
      f.vi[fvi_count++] = vi[2];
  }

  if ( fvi_count < 2 )
    return false;

  if ( vi[3] >= 0 && vi[3] < mesh_vertex_count && f.vi[0] != vi[3] && f.vi[1] != vi[3] && f.vi[2] != vi[3] && V[vi[3]].IsValid() && V[f.vi[0]] != V[vi[3]] && V[f.vi[1]] != V[vi[3]] )
  {
    if ( 2 == fvi_count || V[f.vi[2]] != V[vi[3]] )
      f.vi[fvi_count++] = vi[3];
  }
  
  if ( fvi_count < 3 )
    return false;
 
  if ( 3 == fvi_count )
    f.vi[3] = f.vi[2];
  
  if ( !f.IsValid(mesh_vertex_count) )
    return false;

  vi[0] = f.vi[0];
  vi[1] = f.vi[1];
  vi[2] = f.vi[2];
  vi[3] = f.vi[3];

  return true;
}

ON_Mesh::ON_Mesh() 
: m_packed_tex_rotate(0)
, m_parent(0)
, m_mesh_parameters(0) 
, m_invalid_count(0) 
, m_quad_count(0) 
, m_triangle_count(0)
, m_mesh_is_closed(0)
, m_mesh_is_manifold(0)
, m_mesh_is_oriented(0)
, m_mesh_is_solid(0)
{
  m_top.m_mesh = this;
  m_srf_scale[0] = 0.0;
  m_srf_scale[1] = 0.0;
  m_kstat[0] = 0;
  m_kstat[1] = 0;
  m_kstat[2] = 0;
  m_kstat[3] = 0;
  InvalidateBoundingBoxes();
  m_partition = 0;
  m_hidden_count = 0;
}


ON_Mesh::ON_Mesh(
    int initial_facet_capacity,  // initial facet array capacity
    int initial_vertex_capacity,  // initial vertex array capacity
    bool bHasVertexNormals, // true if mesh has unit vertex normals
    bool bHasTextureCoordinates // true if mesh has texture coordinates
    )
: m_V(initial_vertex_capacity)
, m_F(initial_facet_capacity)
, m_N(bHasVertexNormals?initial_vertex_capacity:0)
, m_T(bHasTextureCoordinates?initial_vertex_capacity:0)
, m_packed_tex_rotate(0)
, m_parent(0) 
, m_mesh_parameters(0)
, m_invalid_count(0) 
, m_quad_count(0) 
, m_triangle_count(0)
, m_mesh_is_closed(0)
, m_mesh_is_manifold(0)
, m_mesh_is_oriented(0)
, m_mesh_is_solid(0)
{
  m_top.m_mesh = this;
  m_srf_scale[0] = 0.0;
  m_srf_scale[1] = 0.0;
  m_kstat[0] = 0;
  m_kstat[1] = 0;
  m_kstat[2] = 0;
  m_kstat[3] = 0;
  InvalidateBoundingBoxes();
  m_partition = 0;
  m_hidden_count = 0;
}

ON_Mesh::ON_Mesh( const ON_Mesh& src ) 
: m_packed_tex_rotate(0)
, m_parent(0) 
, m_mesh_parameters(0) 
, m_invalid_count(0) 
, m_quad_count(0) 
, m_triangle_count(0)
, m_mesh_is_closed(0)
, m_mesh_is_manifold(0)
, m_mesh_is_oriented(0)
, m_mesh_is_solid(0)
{
  // Do not copy m_mesh_cache. Cached information will
  // be recalculated if it is needed.
  m_top.m_mesh = this;
  m_srf_scale[0] = 0.0;
  m_srf_scale[1] = 0.0;

  m_kstat[0] = 0;
  m_kstat[1] = 0;
  m_kstat[2] = 0;
  m_kstat[3] = 0;
  InvalidateBoundingBoxes();
  m_partition = 0;
  m_hidden_count = 0;
  ON_Mesh::operator=(src);
}


unsigned int ON_Mesh::SizeOf() const
{
  unsigned int sz = ON_Geometry::SizeOf();
  sz += m_V.SizeOfArray();
  sz += m_F.SizeOfArray();
  sz += m_N.SizeOfArray();
  sz += m_FN.SizeOfArray();
  sz += m_T.SizeOfArray();
  sz += m_TC.SizeOfArray();
  for (unsigned i = 0; i < m_TC.UnsignedCount(); ++i)
    sz += m_TC[i].m_T.SizeOfArray();
  sz += m_S.SizeOfArray();
  sz += m_K.SizeOfArray();
  sz += m_C.SizeOfArray();  
  sz += m_H.SizeOfArray();
  sz += m_top.m_topv_map.SizeOfArray();
  sz += m_top.m_topv.SizeOfArray();
  sz += m_top.m_tope.SizeOfArray();
  sz += m_top.m_topf.SizeOfArray();
  if (nullptr != m_mesh_parameters)
    sz += sizeof(*m_mesh_parameters);
  if (nullptr != m_partition)
  {
    sz += sizeof(*m_partition);
    sz += m_partition->m_part.SizeOfArray();
  }
  return sz;
}

ON__UINT32 ON_Mesh::DataCRC(ON__UINT32 current_remainder) const
{
  const ON_3fPoint* p = m_V.Array();
  current_remainder = ON_CRC32(current_remainder,m_V.Count()*sizeof(p[0]),p);
  current_remainder = ON_CRC32(current_remainder,m_F.Count()*sizeof(ON_MeshFace),m_F.Array());
  const ON_3fVector* v = m_N.Array();
  current_remainder = ON_CRC32(current_remainder,m_N.Count()*sizeof(v[0]),v);
  return current_remainder;
}

ON_Mesh& ON_Mesh::operator=( const ON_Mesh& src )
{
  if ( this != &src ) 
  {
    Destroy();
    ON_Geometry::operator=(src);

    m_V  = src.m_V;
    m_dV = src.m_dV;
    m_F  = src.m_F;
    m_N  = src.m_N;
    m_FN = src.m_FN;
    m_T  = src.m_T;
    m_TC = src.m_TC;
    m_S  = src.m_S;
    m_H  = src.m_H;
    m_hidden_count = src.m_hidden_count;


    unsigned int ngon_count = src.HasNgons() ? src.m_Ngon.UnsignedCount() : 0;
    if ( ngon_count > 0 )
    {
      const unsigned int src_V_count = src.m_V.UnsignedCount();
      const unsigned int src_F_count = src.m_F.UnsignedCount();
      m_Ngon.Reserve(ngon_count);
      for ( unsigned int i = 0; i < ngon_count; i++ )
      {
        const ON_MeshNgon* src_ngon = src.m_Ngon[i];
        if ( 0 == src_ngon )
          continue;
        if ( src_ngon->m_Vcount <= 0 )
          continue;
        if ( 0 == src_ngon->m_vi )
          continue;
        if ( src_ngon->m_Vcount > src_V_count )
        {
          ON_ERROR("Corrupt ngon");
          continue;
        }
        if ( src_ngon->m_Fcount > src_F_count )
        {
          ON_ERROR("Corrupt ngon");
          continue;
        }
        if ( 0 == src_ngon->m_fi && src_ngon->m_Fcount > 0 )
        {
          ON_ERROR("Corrupt ngon");
          continue;
        }
        ON_MeshNgon* ngon = m_NgonAllocator.CopyNgon(src_ngon);
        if (ngon)
          m_Ngon.Append(ngon);
      }
      if ( 0 != src.NgonMap())
      {
        this->CreateNgonMap();
      }
    }

    m_Ctag = src.m_Ctag;
    m_Ttag = src.m_Ttag;
    m_packed_tex_domain[0] = src.m_packed_tex_domain[0];
    m_packed_tex_domain[1] = src.m_packed_tex_domain[1];
    m_srf_domain[0] = src.m_srf_domain[0];
    m_srf_domain[1] = src.m_srf_domain[1];
    m_srf_scale[0] = src.m_srf_scale[0];
    m_srf_scale[1] = src.m_srf_scale[1];
    m_packed_tex_rotate = src.m_packed_tex_rotate;

    m_K = src.m_K;
    m_C = src.m_C;

    m_parent         = src.m_parent;
    //m_material_index = src.m_material_index;

    if ( m_mesh_parameters ) {
      delete m_mesh_parameters;
      m_mesh_parameters = 0;
    }
    if ( src.m_mesh_parameters )
      m_mesh_parameters = new ON_MeshParameters(*src.m_mesh_parameters);

    m_invalid_count = src.m_invalid_count;
    m_quad_count = src.m_quad_count;
    m_triangle_count = src.m_triangle_count;

    m_mesh_is_closed = src.m_mesh_is_closed;
    m_mesh_is_manifold = src.m_mesh_is_manifold;
    m_mesh_is_oriented = src.m_mesh_is_oriented;
    m_mesh_is_solid    = src.m_mesh_is_solid;

    m_vertex_bbox = src.m_vertex_bbox;
    m_tight_bbox_cache = src.m_tight_bbox_cache;
    memcpy(m_nbox,src.m_nbox,sizeof(m_nbox));
    memcpy(m_tbox,src.m_tbox,sizeof(m_tbox));

    int i;
    for ( i = 0; i < 4; i++ ) {
      if ( m_kstat[i] ) 
      {
        delete m_kstat[i];
        m_kstat[i] = 0;
      }
      if ( src.m_kstat[i] )
      {
        m_kstat[i] = new ON_MeshCurvatureStats(*src.m_kstat[i]);
      }
    }

    // do not copy m_top

    // Do not copy m_mesh_cache. Cached information will
    // be recalculated if it is needed.
  }
  return *this;
}

ON_Mesh::~ON_Mesh()
{
  Destroy();
  m_top.m_mesh = 0;
}

void ON_Mesh::MemoryRelocate()
{
  // the back pointer on m_top needs to be updated.
  m_top.m_mesh = this;
}

void ON_Mesh::Destroy()
{
  PurgeUserData();
  DestroyRuntimeCache( true );
  m_Ttag.Default();
  m_Ctag.Default();
  m_dV.Destroy();
  m_V.Destroy();
  m_F.Destroy();
  m_N.Destroy();
  m_FN.Destroy();
  m_T.Destroy();
  m_TC.Destroy();
  m_S.Destroy();
  m_K.Destroy();
  m_C.Destroy();
  m_NgonMap.Destroy();
  m_Ngon.Destroy();
  m_NgonAllocator.DeallocateAllNgons();
  m_vertex_bbox = ON_BoundingBox::UnsetBoundingBox;
  m_tight_bbox_cache.RemoveAllBoundingBoxes();
}

void ON_Mesh::EmergencyDestroy()
{
  DestroyRuntimeCache( false );
  m_dV.EmergencyDestroy();
  m_V.EmergencyDestroy();
  m_F.EmergencyDestroy();
  m_N.EmergencyDestroy();
  m_FN.EmergencyDestroy();
  m_T.EmergencyDestroy();
  m_TC.EmergencyDestroy();
  m_S.EmergencyDestroy();
  m_K.EmergencyDestroy();
  m_C.EmergencyDestroy();
  m_NgonMap.EmergencyDestroy();
  m_Ngon.EmergencyDestroy();
}

static bool ON_MeshIsNotValid(bool bSilentError)
{
  return bSilentError ? false : ON_IsNotValid(); // good place for a breakpoint;
}

static unsigned int ON_MeshNgonIsNotValid(bool bSilentError)
{
  if (!bSilentError)
    ON_IsNotValid(); // good place for a breakpoint;
  return 0;
}


static int compare2u(const void* a, const void*b)
{
  unsigned int x = ((const unsigned int*)a)[0];
  unsigned int y = ((const unsigned int*)b)[0];
  if ( x < y)
    return -1;
  if ( x > y)
    return 1;
  x = ((const unsigned int*)a)[1];
  y = ((const unsigned int*)b)[1];
  if ( x < y)
    return -1;
  if ( x > y)
    return 1;
  return 0;
}

unsigned int ON_MeshNgon::IsValid(
  const ON_MeshNgon* ngon,
  unsigned int ngon_index,
  ON_TextLog* text_logx,
  unsigned int mesh_vertex_count,
  unsigned int mesh_face_count,
  const ON_MeshFace* mesh_F,
  ON_SimpleArray< unsigned int >& workspace_buffer
  )
{
  workspace_buffer.SetCount(0);
  if ( nullptr == ngon )
    return true; // null ngons are ok

  const ON__INT_PTR lowbit = 1;
  const ON__INT_PTR hightbits = ~lowbit;
  bool bSilentError = ( 0 != (lowbit & ((ON__INT_PTR)text_logx)) );
  ON_TextLog* text_log = (ON_TextLog*)(((ON__INT_PTR)text_logx) & hightbits);

  if (ngon->m_Vcount < 3)
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.Ngon(%u)->m_Vcount < 3.\n",ngon_index);
    }
    return ON_MeshNgonIsNotValid(bSilentError);
  }

  if (ngon->m_Fcount < 1)
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.Ngon(%u)->m_Fcount < 1.\n",ngon_index);
    }
    return ON_MeshNgonIsNotValid(bSilentError);
  }

  if ( nullptr == ngon->m_vi )
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.Ngon(%u)->m_vi is nullptr.\n",ngon_index);
    }
    return ON_MeshNgonIsNotValid(bSilentError);
  }

  if ( nullptr == ngon->m_fi )
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.Ngon(%u)->m_fi is nullptr.\n",ngon_index);
    }
    return ON_MeshNgonIsNotValid(bSilentError);
  }

  for (unsigned int nvi = 0; nvi < ngon->m_Vcount; nvi++)
  {
    if (ngon->m_vi[nvi] >= mesh_vertex_count)
    {
      if ( text_log )
      {
        text_log->Print("ON_Mesh.Ngon(%u)->m_vi[%u] is invalid.\n",ngon_index,nvi);
      }
      return ON_MeshNgonIsNotValid(bSilentError);
    }
  }

  for (unsigned int nfi = 0; nfi < ngon->m_Fcount; nfi++)
  {
    unsigned int fi = ngon->m_fi[nfi];
    if (fi >= mesh_face_count)
    {
      if (text_log)
      {
        text_log->Print("ON_Mesh.Ngon(%u)->m_fi[%u] is invalid.\n", ngon_index, nfi);
      }
      return ON_MeshNgonIsNotValid(bSilentError);
    }
  }

  if (nullptr == mesh_F)
  {
    // mesh faces are required to check the boundary
    return true;
  }

  if (1 == ngon->m_Fcount && ngon->m_Vcount >= 3 && ngon->m_Vcount <= 4)
  {
    // fast test for a valid single face ngon
    unsigned int fi = ngon->m_fi[0];
    if (false == mesh_F[fi].IsValid(mesh_vertex_count))
    {
      if (text_log)
      {
        text_log->Print("ON_Mesh.Ngon(%u)->m_fi[0] is invalid.\n", ngon_index);
      }
      return ON_MeshNgonIsNotValid(bSilentError);
    }
    const unsigned int* fvi = (const unsigned int*)mesh_F[fi].vi;
    for (unsigned int nvi = 0; nvi < ngon->m_Vcount; nvi++)
    {
      if (fvi[0] == ngon->m_vi[nvi] && fvi[1] == ngon->m_vi[(nvi+1)%ngon->m_Vcount] && fvi[2] == ngon->m_vi[(nvi+2)%ngon->m_Vcount])
      {
        if (3 == ngon->m_Vcount && fvi[3] == fvi[2])
          return 3;
        if (4 == ngon->m_Vcount && fvi[3] == ngon->m_vi[(nvi+3)%ngon->m_Vcount])
          return 4;
      }
    }
    // boundary may be reversed
  }

  unsigned int* workspace = workspace_buffer.Reserve(8*ngon->m_Fcount);
  ON_2udex* edges = (ON_2udex*)workspace;
  unsigned int edge_count = 0;
  for (unsigned int nfi = 0; nfi < ngon->m_Fcount; nfi++)
  {
    unsigned int fi = ngon->m_fi[nfi];

    const unsigned int* fvi = (const unsigned int*)(mesh_F[fi].vi);
    unsigned int vi0;
    unsigned int vi1 = fvi[3];
    for (const unsigned int* fvi1 = fvi + 4; fvi < fvi1; fvi++)
    {
      vi0 = vi1;
      vi1 = *fvi;
      if (vi0 < vi1)
      {
        edges[edge_count].i = vi0;
        edges[edge_count++].j = vi1;
      }
      else if (vi0 > vi1)
      {
        edges[edge_count].i = vi1;
        edges[edge_count++].j = vi0;
      }
    }
  }

  if (edge_count < ngon->m_Vcount)
  {
    if (text_log)
    {
      text_log->Print("ON_Mesh.Ngon(%u) has invalid face or vertex list.\n",ngon_index);
    }
    return ON_MeshNgonIsNotValid(bSilentError);
  }

  ON_qsort(edges, edge_count, sizeof(edges[0]),compare2u);

  unsigned int bdry_edge_count = 0;
  for (unsigned int i = 0; i < edge_count; /*empty iterator*/)
  {
    const ON_2udex e0 = edges[i++];
    if (i < edge_count && e0.i == edges[i].i && e0.j == edges[i].j)
    {
      // not a boundary edge
      for (i++; i < edge_count; i++)
      {
        if (e0.i != edges[i].i || e0.j != edges[i].j)
          break;
      }
    }
    else
    {
      edges[bdry_edge_count++] = e0;
    }
  }

  if (bdry_edge_count < ngon->m_Vcount)
  {
    if (text_log)
    {
      text_log->Print("ON_Mesh.Ngon(%u) has invalid face or vertex list.\n",ngon_index);
    }
    return ON_MeshNgonIsNotValid(bSilentError);
  }

  ON_SortUnsignedIntArray( ON::sort_algorithm::quick_sort, workspace, 2*bdry_edge_count );

  for (unsigned int nvi = 0; nvi < ngon->m_Vcount; nvi++)
  {
    if ( nullptr == ON_BinarySearchUnsignedIntArray( ngon->m_vi[nvi], workspace, 2*bdry_edge_count) )
    {
      if ( text_log )
      {
        text_log->Print("ON_Mesh.Ngon(%u)->m_vi[%u] is not a boundary vertex.\n",ngon_index,nvi);
      }
      return ON_MeshNgonIsNotValid(bSilentError);
    }
  }

  // It is possible that the ngon is still not valid.
  //
  // If bdry_edge_count > ngon->m_Vcount, then there "could" be one or
  // more inner "holes" and the ngon->m_vi[] could reference a vertex
  // on an inner boundary.
  //
  // The vertices in ngon->m_v[] may not be a proper outer boundary.
  //
  // ...


  return bdry_edge_count;
}

static void Internal_ON_Mesh_IsCorruptMessage(
  bool bSilentError,
  bool& bIsCorrupt,
  ON_TextLog* text_log,
  const wchar_t* corruption_description
)
{
  if (false == bIsCorrupt)
  {
    if (false == bSilentError)
    {
      ON_ERROR("ON_Mesh data is corrupt.");
    }
    bIsCorrupt = true;
    if (nullptr != text_log)
      text_log->PrintString(corruption_description);
  }
}

bool ON_Mesh::IsCorrupt(
  bool bRepair,
  bool bSilentError,
  class ON_TextLog* text_log
) const
{
  const unsigned int V_count = m_V.UnsignedCount();
  unsigned int F_count = m_F.UnsignedCount();

  bool bIsCorrupt = false;

  // test faces first
  for (unsigned int fi = 0; fi < F_count; fi++)
  {
    unsigned int* fvi = (unsigned int*)m_F[fi].vi;
    for (int j = 0; j < 4; j++)
    {
      if (fvi[j] >= V_count)
      {
        Internal_ON_Mesh_IsCorruptMessage(
          bSilentError,
          bIsCorrupt,
          text_log,
          L"ON_Mesh.m_F[] has out of range vertex indices.\n"
        );
        if (bRepair)
        {
          fvi[0] = V_count; // mark this corrupt face for deletion below

          // deleting a face makes cached information invalid
          // and the fact the face was corrupt makes any
          // set values suspect.
          const_cast<ON_Mesh*>(this)->m_invalid_count = 0;
          const_cast<ON_Mesh*>(this)->m_quad_count = 0;
          const_cast<ON_Mesh*>(this)->m_triangle_count = 0;

          const_cast<ON_Mesh*>(this)->m_mesh_is_closed = 0;
          const_cast<ON_Mesh*>(this)->m_mesh_is_manifold = 0;
          const_cast<ON_Mesh*>(this)->m_mesh_is_oriented = 0;
          const_cast<ON_Mesh*>(this)->m_mesh_is_solid = 0;
        }
      }
    }
  }

  if (bIsCorrupt && bRepair)
  {
    // remove corrupt faces
    // N-gon indices reference faces that will get new indices
    // or get deleted.
    // If the creator couldn't get the vertex indices in a 
    // face set correctly, then they loose any N-gon work
    // too that may or may not have been done correctly. 
    // (Harsh, I know).
    const_cast<ON_Mesh*>(this)->RemoveAllNgons();


    unsigned int new_F_count = 0;
    ON_MeshFace* F = const_cast<ON_MeshFace*>(m_F.Array());
    ON_3fVector* FN =
      (F_count == m_FN.UnsignedCount())
      ? const_cast<ON_3fVector*>(m_FN.Array())
      : nullptr;
    if ( nullptr == FN)
      const_cast<ON_Mesh*>(this)->m_F.SetCount(0);

    for (unsigned int fi = 0; fi < F_count; fi++)
    {
      if (V_count ==(unsigned int)F[fi].vi[0])
        continue; // corrupt face

      F[new_F_count] = F[fi];
      if (nullptr != FN)
        FN[new_F_count] = FN[fi];
      new_F_count++;
    }

    const_cast<ON_Mesh*>(this)->m_F.SetCount(new_F_count);
    if (nullptr != FN)
      const_cast<ON_Mesh*>(this)->m_FN.SetCount(new_F_count);
    F_count = new_F_count;
  }

  if (0 != m_dV.UnsignedCount() && V_count != m_dV.UnsignedCount())
  {
    Internal_ON_Mesh_IsCorruptMessage(
      bSilentError,
      bIsCorrupt,
      text_log,
      L"ON_Mesh.m_dV[] has wrong size.\n"
    );
    if( bRepair )
      const_cast<ON_Mesh*>(this)->m_dV.SetCount(0);
  }

  return bIsCorrupt;
}

unsigned int ON_MeshNgon::IsValid(
  const ON_MeshNgon* ngon,
  unsigned int ngon_index,
  ON_TextLog* text_logx,
  unsigned int mesh_vertex_count,
  unsigned int mesh_face_count,
  const ON_MeshFace* mesh_F
  )
{
  // If low bit of text_log pointer is 1, then ON_Error is not called when the ngon is invalid.
  ON_SimpleArray< unsigned int > workspace_buffer;
  return ON_MeshNgon::IsValid(ngon,ngon_index,text_logx,mesh_vertex_count,mesh_face_count,mesh_F,workspace_buffer);
}

bool ON_Mesh::IsValid( ON_TextLog* text_logx ) const
{
  // If low bit of text_log pointer is 1, then ON_Error is not called when the mesh is invalid.
  const ON__INT_PTR lowbit = 1;
  const ON__INT_PTR hightbits = ~lowbit;
  bool bSilentError = ( 0 != (lowbit & ((ON__INT_PTR)text_logx)) );
  ON_TextLog* text_log = (ON_TextLog*)(((ON__INT_PTR)text_logx) & hightbits);

  if (IsCorrupt(false, bSilentError, text_log))
    return false;

  const unsigned int facet_count = FaceUnsignedCount();
  const unsigned int vertex_count = VertexUnsignedCount();
  unsigned int fi, vi;

  if (facet_count < 1) 
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.m_F.Count() < 1 (should be at least 1).\n");
    }
    return ON_MeshIsNotValid(bSilentError);
  }

  if ( vertex_count < 3 )
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.m_V.Count() < 3 (should be at least 3).\n");
    }
    return ON_MeshIsNotValid(bSilentError);
  }


  if ( m_V.UnsignedCount() != vertex_count )
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.m_V.Count() = %u (should be %u=vertex_count).\n",
                      m_V.UnsignedCount(),vertex_count);
    }
    return ON_MeshIsNotValid(bSilentError);
  }

  if ( m_dV.UnsignedCount() > 0 && m_dV.UnsignedCount() != vertex_count )
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.m_dV.Count() = %u (should be 0 or %u=vertex_count).\n",
                      m_dV.UnsignedCount(),vertex_count);
    }
    return ON_MeshIsNotValid(bSilentError);
  }

  if ( 0 != m_dV.UnsignedCount() )
  {
    if (false == HasSynchronizedDoubleAndSinglePrecisionVertices())
    {
      if ( text_log )
      {
        text_log->Print("ON_Mesh.m_dV[] and m_V[] are not synchronized.\n",
                        m_dV.UnsignedCount(),vertex_count);
      }
      return ON_MeshIsNotValid(bSilentError);
    }
  }

  if ( m_N.UnsignedCount() > 0 && m_N.UnsignedCount() != vertex_count )
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.m_N.Count() = %u (should be 0 or %u=vertex_count).\n",
                      m_N.UnsignedCount(),vertex_count);
    }
    return ON_MeshIsNotValid(bSilentError);
  }

  if ( m_T.UnsignedCount() > 0 && m_T.UnsignedCount() != vertex_count )
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.m_T.Count() = %u (should be 0 or %u=vertex_count).\n",
                      m_T.UnsignedCount(),vertex_count);
    }
    return ON_MeshIsNotValid(bSilentError);
  }

  if ( m_S.UnsignedCount() > 0 && m_S.UnsignedCount() != vertex_count )
  {
    if ( text_log )
    {
      text_log->Print("ON_Mesh.m_S.Count() = %u (should be 0 or %u=vertex_count).\n",
                      m_S.UnsignedCount(),vertex_count);
    }
    return ON_MeshIsNotValid(bSilentError);
  }

  if ( HasVertexNormals() ) 
  {
    float x;
    for ( vi = 0; vi < vertex_count; vi++ ) {
      x = m_N[vi][0]*m_N[vi][0] + m_N[vi][1]*m_N[vi][1] + m_N[vi][2]*m_N[vi][2];
      if ( x < 0.985 || x > 1.015 )
      {
        if ( text_log )
        {
          text_log->Print("ON_Mesh.m_N[%u] is not a unit vector (length = %g).\n",vi,sqrt(x));
        }
        return ON_MeshIsNotValid(bSilentError);
      }
    }
  }

  int i;
  for ( i = 0; i < 3; i++ )
  {    
    const double float_max = 3.402823466e+38;
    if ( m_vertex_bbox.IsNotEmpty()  )
    {
      if (
           fabs(m_vertex_bbox.m_min.MaximumCoordinate()) > float_max
        || fabs(m_vertex_bbox.m_max.MaximumCoordinate()) > float_max
        )
      {
	      // Greg Arden 9 May 2003. Fixes TRR#10604.  
        // Attempt to detect meshes with non-float-finite vertices by testing the bounding box.
        if (text_log)
        {
          text_log->Print("ON_Mesh.m_fvertex_bbox is not finite.  Check for invalid vertices\n");
        }
        return ON_MeshIsNotValid(bSilentError);
      }
    }	
  }

  const ON_3dPoint* dV = 0;
  while ( HasDoublePrecisionVertices() )
  {
    const unsigned int vertex_count_local = VertexUnsignedCount();
    bool bValidDoubles = (vertex_count_local == m_dV.UnsignedCount());
    if ( bValidDoubles )
      dV = DoublePrecisionVertices().Array();
    bool bValidFloats  = (vertex_count_local == m_V.UnsignedCount());
    bool bSynchronized = HasSynchronizedDoubleAndSinglePrecisionVertices();
    if ( bSynchronized && bValidDoubles && bValidFloats )
      break;

    if ( !bSynchronized )
    {
      if ( text_log )
      {
        text_log->Print("Single and double precision vertices are not synchronized.\n");
      }		
	    return ON_MeshIsNotValid(bSilentError);
    }

    break;
  }

  if ( 0 != dV )
  {
    for ( fi = 0; fi < facet_count; fi++ ) 
    {
      if ( !m_F[fi].IsValid( vertex_count, dV ) ) 
      {
        if ( text_log )
        {
          if ( !m_F[fi].IsValid( vertex_count) )
            text_log->Print("ON_Mesh.m_F[%u].vi[] has invalid vertex indices.\n",fi);
          else
            text_log->Print("ON_Mesh.m_F[%u] has degenerate double precision vertex locations.\n",fi);
        }
        return ON_MeshIsNotValid(bSilentError);
      }
    }
  }
  else
  {
    const ON_3fPoint* fV = m_V.Array();
    for ( fi = 0; fi < facet_count; fi++ ) 
    {
      // This test is considered relatively harsh for float precision meshes with nearly degenerate faces
      // after they are transformed by a transform with a reasonable sized translation 
      // component, as in https://mcneel.myjetbrains.com/youtrack/issue/RH-10177.
      // However, removing this creates unreasonable pressure on double precision meshes, because, after being 
      // transformed to double precision, a wrongly valid single-precision-collapsed-edge mesh makes an
      // invalid double-precision mesh altogether. This cannot be tolerated.
      // The goal should be to have invalid single-precision-only meshes be treated by MeshRepair when created.
      // See https://mcneel.myjetbrains.com/youtrack/issue/RH-54563 and
      /// https://mcneel.myjetbrains.com/youtrack/issue/RH-30283

      if ( !m_F[fi].IsValid( vertex_count, fV ) ) 
      {
        if ( text_log )
        {
          if ( !m_F[fi].IsValid( vertex_count) )
            text_log->Print("ON_Mesh.m_F[%d].vi[] has invalid vertex indices.\n",fi);
          else
            text_log->Print("ON_Mesh.m_F[%d] has degenerate float precision vertex locations.\n",fi);
        }
        return ON_MeshIsNotValid(bSilentError);
      }

      if ( !m_F[fi].IsValid( vertex_count ) ) 
      {
        if ( text_log )
          text_log->Print("ON_Mesh.m_F[%u].vi[] has invalid vertex indices.\n",fi);
        return ON_MeshIsNotValid(bSilentError);
      }
    }
  }

  const unsigned int ngon_count = m_Ngon.UnsignedCount();
  if (ngon_count > 0)
  {
    ON_SimpleArray< unsigned int > workspace_buffer;
    for (unsigned int ngon_index = 0; ngon_index < ngon_count; ngon_index++)
    {
      const ON_MeshNgon* ngon = m_Ngon[ngon_index];
      if (nullptr == ngon)
        continue; // valid - means the ngon was removed
      if (0 == ON_MeshNgon::IsValid(ngon, ngon_index, text_logx, (unsigned int)vertex_count, (unsigned int)facet_count, m_F.Array(), workspace_buffer))
        return false;
    }
  }

  return true;
}

static void Internal_PrintMeshArrayHash(ON_TextLog& text_log, ON_SHA1_Hash hash, const wchar_t* prefix, bool bNewLine)
{
  if (nullptr != prefix && 0 != prefix[0])
    text_log.Print(L"%ls ", prefix);
  hash.Dump(text_log);
  if (bNewLine)
    text_log.PrintNewLine();
}

static void Internal_PrintMeshArrayHash(ON_TextLog& text_log, const ON_SimpleArray<ON_3fVector>& a, const wchar_t* prefix, bool bNewLine)
{
  ON_SHA1 sha1;
  ON_SHA1_Accumulate3fVectorArray(sha1,a);
  const ON_SHA1_Hash hash = sha1.Hash();
  Internal_PrintMeshArrayHash(text_log, hash, prefix, bNewLine);
}

static void Internal_PrintMeshArrayHash(ON_TextLog& text_log, const ON_SimpleArray<ON_2fPoint>& a, const wchar_t* prefix, bool bNewLine)
{
  ON_SHA1 sha1;
  ON_SHA1_Accumulate2fPointArray(sha1,a);
  const ON_SHA1_Hash hash = sha1.Hash();
  Internal_PrintMeshArrayHash(text_log, hash, prefix, bNewLine);
}

static void Internal_PrintMeshArrayHash(ON_TextLog& text_log, const ON_SimpleArray<ON_3fPoint>& a, const wchar_t* prefix, bool bNewLine)
{
  ON_SHA1 sha1;
  ON_SHA1_Accumulate3fPointArray(sha1,a);
  const ON_SHA1_Hash hash = sha1.Hash();
  Internal_PrintMeshArrayHash(text_log, hash, prefix, bNewLine);
}

static void Internal_PrintMeshArrayHash(ON_TextLog& text_log, const ON_SimpleArray<ON_2dPoint>& a, const wchar_t* prefix, bool bNewLine)
{
  ON_SHA1 sha1;
  ON_SHA1_Accumulate2dPointArray(sha1,a);
  const ON_SHA1_Hash hash = sha1.Hash();
  Internal_PrintMeshArrayHash(text_log, hash, prefix, bNewLine);
}

static void Internal_PrintMeshArrayHash(ON_TextLog& text_log, const ON_SimpleArray<ON_SurfaceCurvature>& a, const wchar_t* prefix, bool bNewLine)
{
  ON_SHA1 sha1;
  sha1.AccumulateDoubleArray(a.Count() * 2, (const double*)a.Array());
  const ON_SHA1_Hash hash = sha1.Hash();
  Internal_PrintMeshArrayHash(text_log, hash, prefix, bNewLine);
}

static void Internal_PrintMeshArrayHash(ON_TextLog& text_log, const ON_SimpleArray<ON_Color>& a, const wchar_t* prefix, bool bNewLine)
{
  ON_SHA1 sha1;
  sha1.AccumulateInteger32Array(a.Count(), (const ON__INT32*)a.Array());
  const ON_SHA1_Hash hash = sha1.Hash();
  Internal_PrintMeshArrayHash(text_log, hash, prefix, bNewLine);
}

static void Internal_PrintMeshArrayHash(ON_TextLog& text_log, const ON_SimpleArray<ON_3dPoint>& a, const wchar_t* prefix, bool bNewLine)
{
  ON_SHA1 sha1;
  ON_SHA1_Accumulate3dPointArray(sha1,a);
  const ON_SHA1_Hash hash = sha1.Hash();
  Internal_PrintMeshArrayHash(text_log, hash, prefix, bNewLine);
}

static void Internal_PrintMeshArrayHash(ON_TextLog& text_log, const ON_SimpleArray<ON_MeshFace>& F, const wchar_t* prefix, bool bNewLine)
{
  ON_SHA1 sha1;
  const ON_MeshFace* aa = F.Array();
  const ON__INT32* e = (nullptr != aa) ? &aa[0].vi[0] : nullptr;
  const size_t count = F.UnsignedCount() * sizeof(aa[0]) / sizeof(e[0]);
  sha1.AccumulateInteger32Array(count,e);
  const ON_SHA1_Hash hash = sha1.Hash();
  Internal_PrintMeshArrayHash(text_log, hash, prefix, bNewLine);
}

void ON_Mesh::Dump( ON_TextLog& dump ) const
{
  const int half_max = 8;

  const int fcount = m_F.Count();
  int i;
  const int vcount = m_V.Count();
  ON_3dPoint p, q;

  bool bDoubles =    vcount > 0 
                  && HasDoublePrecisionVertices()
                  && HasSynchronizedDoubleAndSinglePrecisionVertices();

  dump.Print("ON_Mesh: vertex count = %d  facet count = %d\n", m_V.Count(), m_F.Count() );
  dump.Print("double precision: %s\n",bDoubles?"true":"false");
  dump.Print("vertex normals:   %s\n",HasVertexNormals()?"true":"false");
  dump.Print("face normals:     %s\n",HasFaceNormals()?"true":"false");
  dump.Print("n-gons:           %s\n",HasNgons()?"true":"false");
  dump.Print("srf parameters:   %s\n",HasSurfaceParameters()?"true":"false");
  dump.Print("tex coords:       %s\n",HasTextureCoordinates()?"true":"false");
  dump.Print("vertex kappa:     %s\n",HasPrincipalCurvatures()?"true":"false");
  dump.Print("vertex colors:    %s\n",HasVertexColors()?"true":"false");
  dump.Print("m_Ctag:\n"); dump.PushIndent(); m_Ctag.Dump(dump); dump.PopIndent();
  dump.Print("m_packed_tex_rotate: %s\n",m_packed_tex_rotate?"true":"false");
  dump.Print("m_packed_tex_domain: (%g,%g)x(%g,%g)\n",
             m_packed_tex_domain[0][0],m_packed_tex_domain[0][1],
             m_packed_tex_domain[1][0],m_packed_tex_domain[1][1]);
  dump.Print("m_srf_domain: (%g,%g)x(%g,%g)\n",m_srf_domain[0][0],m_srf_domain[0][1],m_srf_domain[1][0],m_srf_domain[1][1]);
  dump.Print("m_srf_scale: %g,%g\n",m_srf_scale[0],m_srf_scale[0]);
  dump.Print("m_Ttag:\n"); dump.PushIndent(); m_Ttag.Dump(dump); dump.PopIndent();
  dump.Print( ON_wString(L"Memory used: ")  + ON_wString::ToMemorySize(this->SizeOf()) + ON_wString(L"\n") );


  const ON_MeshParameters* mp = this->MeshParameters();
  if (nullptr != mp)
  {
    ON_String description;
    switch (mp->GeometrySettingsType(true))
    {
    case ON_MeshParameters::Type::Unset:
      description = ON_String::EmptyString;
      break;
    case ON_MeshParameters::Type::Default:
      description = ON_String("ON_MeshParameters::DefaultMesh");
      break;
    case ON_MeshParameters::Type::FastRender:
      description = ON_String("ON_MeshParameters::FastRenderMesh");
      break;
    case ON_MeshParameters::Type::QualityRender:
      description = ON_String("ON_MeshParameters::QualityRenderMesh");
      break;
    case ON_MeshParameters::Type::DefaultAnalysis:
      description = ON_String("ON_MeshParameters::DefaultAnalysisMesh");
      break;
    case ON_MeshParameters::Type::FromMeshDensity:
      description = ON_String::FormatToString("ON_MeshParameters::CreateFromMeshDensity(%g)", mp->MeshDensity());
      break;
    case ON_MeshParameters::Type::Custom:
      description = ON_String::EmptyString;
      break;
    default:
      description = ON_String::EmptyString;
      break;
    }

    dump.PrintNewLine();
    if (description.IsNotEmpty())
    {
      dump.Print("NURBS, ON_Brep, ON_Extrusion meshing parameters:\n");
      {
        const ON_TextLogIndent indent1(dump);
        dump.Print("%s\n", static_cast<const char*>(description));
      }
      dump.Print("SubD meshing parameters:\n");
      {
        const ON_TextLogIndent indent1(dump);
        const ON_SubDDisplayParameters subdmp = mp->SubDDisplayParameters();
        subdmp.Dump(dump);
      }
    }
    else
    {
      dump.Print("Custom meshing parameters:\n");
      const ON_TextLogIndent indent1(dump);
      mp->Dump(dump);
    }
    dump.PrintNewLine();
  }

  const ON_TextLogIndent indent1(dump);

  dump.Print("%d mesh vertices:\n",m_V.Count());
  {
    const ON_TextLogIndent indent2(dump);
    Internal_PrintMeshArrayHash(dump, m_V, L"m_V array hash", true);
    const ON_3dPoint* D = 0;
    if ( bDoubles )
    {
      Internal_PrintMeshArrayHash(dump, m_dV, L"m_dV array hash", true);
      D = DoublePrecisionVertices().Array();
    }
    for (i = 0; i < vcount; i++)
    {
      if ( i == half_max && 2*half_max < vcount )
      {
        dump.Print("...\n");
        i = vcount-half_max;
      }
      else
      {
        p = m_V[i];
        if ( 0 != D )
        {
          q = D[i];
          dump.Print("m_V[%d] = (%.17g,%.17g,%.17g) D = (%.17g,%.17g,%.17g)\n",
                     i,
                     p.x,p.y,p.z,
                     q.x,q.y,q.z
                     );
        }
        else
        {
          dump.Print("m_V[%d] = (%g,%g,%g)\n",i,p.x,p.y,p.z);
        }
      }
    }
  }

  if ( HasVertexNormals() )
  {
    dump.Print("%d mesh vertex normals:\n",m_N.Count());
    {
      const ON_TextLogIndent indent2(dump);
      Internal_PrintMeshArrayHash(dump, m_N, L"m_N array hash", true);
      for (i = 0; i < vcount; i++)
      {
        if ( i == half_max && 2*half_max < vcount )
        {
          dump.Print("...\n");
          i = vcount-half_max;
        }
        else
        {
          p = m_N[i];
          dump.Print("m_N[%d] = (%g,%g,%g)\n",i,p.x,p.y,p.z);
        }
      }
    }
  }

  if ( HasTextureCoordinates() )
  {
    dump.Print("%d mesh vertex texture coordinates:\n",m_T.Count());
    {
      const ON_TextLogIndent indent2(dump);
      Internal_PrintMeshArrayHash(dump, m_T, L"m_T array hash", true);
      for (i = 0; i < vcount; i++)
      {
        if ( i == half_max && 2*half_max < vcount )
        {
          dump.Print("...\n");
          i = vcount-half_max;
        }
        else
        {
          const ON_2dPoint tp(m_T[i]);
          dump.Print("m_T[%d] = (%g,%g)\n",i,tp.x,tp.y);
        }
      }
    }
  }

  if ( HasSurfaceParameters() )
  {
    dump.Print("%d mesh vertex surface parameters:\n",m_S.Count());
    {
      const ON_TextLogIndent indent2(dump);
      Internal_PrintMeshArrayHash(dump, m_S, L"m_S array hash", true);
      for (i = 0; i < vcount; i++)
      {
        if ( i == half_max && 2*half_max < vcount )
        {
          dump.Print("...\n");
          i = vcount-half_max;
        }
        else
        {
          const ON_2dPoint srfuv = m_S[i];
          dump.Print("m_S[%d] = (%g,%g)\n",i, srfuv.x, srfuv.y);
        }
      }
    }
  }

  if (this->HasVertexColors())
  {
    dump.Print("%d mesh vertex colors:\n", m_C.Count());
    {
      const ON_TextLogIndent indent2(dump);
      Internal_PrintMeshArrayHash(dump, m_C, L"m_C array hash", true);
      for (i = 0; i < vcount; i++)
      {
        if (i == half_max && 2 * half_max < vcount)
        {
          dump.Print("...\n");
          i = vcount - half_max;
        }
        else
        {
          const ON_wString s = m_C[i].ToString(ON_Color::TextFormat::HashRGBa, 0, true);
          dump.Print(L"m_C[%d] = %s\n", i, static_cast<const wchar_t*>(s));
        }
      }
    }
  }


  if (this->HasPrincipalCurvatures())
  {
    dump.Print("%d mesh vertex principal curvatures:\n", m_K.Count());
    {
      const ON_TextLogIndent indent2(dump);
      Internal_PrintMeshArrayHash(dump, m_K, L"m_K array hash", true);
      for (i = 0; i < vcount; i++)
      {
        if (i == half_max && 2 * half_max < vcount)
        {
          dump.Print("...\n");
          i = vcount - half_max;
        }
        else
        {
          const ON_SurfaceCurvature k = m_K[i];
          dump.Print("m_K[%d] = (%g,%g)\n", i, k.k1, k.k2);
        }
      }
    }
  }


  dump.Print("%d mesh faces:\n",m_F.Count());
  {
    const ON_TextLogIndent indent2(dump);
    Internal_PrintMeshArrayHash(dump, m_F, L"m_F array hash", true);
    for (i = 0; i < fcount; i++)
    {
      if ( i == half_max && 2*half_max < fcount )
      {
        dump.Print("...\n");
        i = fcount-half_max;
      }
      else if ( m_F[i].vi[2] == m_F[i].vi[3] )
        dump.Print("m_F[%d].vi = (%d,%d,%d)\n",i,m_F[i].vi[0],m_F[i].vi[1],m_F[i].vi[2]);
      else
        dump.Print("m_F[%d].vi = (%d,%d,%d,%d)\n",i,m_F[i].vi[0],m_F[i].vi[1],m_F[i].vi[2],m_F[i].vi[3]);
    }
  }

  if ( HasFaceNormals() )
  {
    dump.Print("%d mesh face normals:\n",m_FN.Count());
    {
      const ON_TextLogIndent indent2(dump);
      for (i = 0; i < fcount; i++)
      {
        if ( i == half_max && 2*half_max < fcount )
        {
          dump.Print("...\n");
          i = fcount-half_max;
        }
        else
        {
          p = m_FN[i];
          dump.Print("m_FN[%d] = (%g,%g,%g)\n",i,p.x,p.y,p.z);
        }
      }
    }
  }

  if ( HasNgons() )
  {
    const ON_MeshFaceList mesh_face_list(this);

    const int ngon_count = NgonCount();
    dump.Print("%d mesh n-gons:\n",ngon_count);
    {
      const ON_TextLogIndent indent2(dump);
      for (i = 0; i < ngon_count; i++)
      {
        if ( i == half_max && 2*half_max < ngon_count )
        {
          dump.Print("...\n");
          i = ngon_count-half_max;
        }
        else
        {
          const ON_MeshNgon* ngon = Ngon(i);
          if ( 0 == ngon )
            dump.Print("Ngon(%d) = null\n",i);
          else
          {
            dump.Print("Ngon(%d): ",i);
            ngon->Dump(dump);
            const int bcount = (int)ngon->BoundaryEdgeCount(mesh_face_list);
            const int outer_boundary_count = (int)ngon->OuterBoundaryEdgeCount();
            const int inner_boundary_count = bcount - outer_boundary_count;
            dump.Print(" boundary counts outer = %d, inner = %d", outer_boundary_count, inner_boundary_count);
            dump.Print("\n");
          }
        }
      }
    }
  }
}


bool ON_Mesh::WriteFaceArray( int vcount, int fcount, ON_BinaryArchive& file ) const
{
  unsigned char  cvi[4];
  unsigned short svi[4];
  const int* vi;
  int i_size = 0;
  if ( vcount < 256 ) {
    i_size = 1; // unsigned chars
  }
  else if (vcount < 65536 ) {
    i_size = 2; // unsigned shorts
  }
  else {
    i_size = 4; // 4 byte ints
  }

  bool rc = file.WriteInt( i_size );
  int i;
  switch(i_size) {
  case 1:
    for ( i = 0; i < fcount && rc ; i++ ) {
      vi = m_F[i].vi;
      cvi[0] = (unsigned char)vi[0];
      cvi[1] = (unsigned char)vi[1];
      cvi[2] = (unsigned char)vi[2];
      cvi[3] = (unsigned char)vi[3];
      rc = file.WriteChar( 4, cvi );
    }
    break;
  case 2:
    for ( i = 0; i < fcount && rc ; i++ ) {
      vi = m_F[i].vi;
      svi[0] = (unsigned short)vi[0];
      svi[1] = (unsigned short)vi[1];
      svi[2] = (unsigned short)vi[2];
      svi[3] = (unsigned short)vi[3];
      rc = file.WriteShort( 4, svi );
    }
    break;
  case 4:
    for ( i = 0; i < fcount && rc ; i++ ) {
      rc = file.WriteInt( 4, m_F[i].vi );
    }
    break;
  }

  return rc;
}

bool ON_Mesh::ReadFaceArray( int vcount, int fcount, ON_BinaryArchive& file )
{
  unsigned char  cvi[4];
  unsigned short svi[4];
  unsigned int* vi;
  int i_size = 0;

  if ( m_F.Capacity() < fcount )
    m_F.SetCapacity(fcount);
  bool rc = file.ReadInt( &i_size );
  int i = 0;
  switch(i_size) {
  case 1:
    for ( i = 0; i < fcount && rc ; i++ ) {
      rc = file.ReadChar( 4, cvi );
      vi = (unsigned int*)m_F[i].vi;
      vi[0] = cvi[0];
      vi[1] = cvi[1];
      vi[2] = cvi[2];
      vi[3] = cvi[3];
    }
    break;
  case 2:
    for ( i = 0; i < fcount && rc ; i++ ) {
      rc = file.ReadShort( 4, svi );
      vi = (unsigned int*)m_F[i].vi;
      vi[0] = svi[0];
      vi[1] = svi[1];
      vi[2] = svi[2];
      vi[3] = svi[3];
    }
    break;
  case 4:
    for ( i = 0; i < fcount && rc ; i++ ) {
      rc = file.ReadInt( 4, m_F[i].vi );
    }
    break;
  }
  m_F.SetCount(i);

  return rc;
}


bool ON_Mesh::Write_1( ON_BinaryArchive& file ) const
{
  // ver 1.0 uncompressed format

  bool rc = file.WriteArray( m_V );
  if (rc) rc = file.WriteArray( m_N );
  if (rc) rc = file.WriteArray( m_T );
  if (rc) rc = file.WriteArray( m_K );
  if (rc) rc = file.WriteArray( m_C );

  return rc;
}

bool ON_Mesh::Read_1( ON_BinaryArchive& file )
{
  // common to all 1.x formats (uncompressed)

  bool rc = file.ReadArray( m_V );
  if (rc) rc = file.ReadArray( m_N );
  if (rc) rc = file.ReadArray( m_T );
  if (rc) rc = file.ReadArray( m_K );
  if (rc) rc = file.ReadArray( m_C );

  return rc;
}

bool ON_Mesh::Write_2( int Vcount, ON_BinaryArchive& file ) const
{
  // ver 2.0 compressed format
  const ON::endian e = file.Endian();

  bool rc = true;

  if ( Vcount > m_V.Count() )
    return false;

  if ( Vcount > 0 ) 
  {
    const int Ncount = (m_V.Count() == m_N.Count()) ? Vcount : 0;
    const int Tcount = (m_V.Count() == m_T.Count()) ? Vcount : 0;
    const int Kcount = (m_V.Count() == m_K.Count()) ? Vcount : 0;
    const int Ccount = (m_V.Count() == m_C.Count()) ? Vcount : 0;

    if (e == ON::endian::big_endian)
    {
      // These calls temporarily put the m_V[], m_N[], m_T[], m_K[]
      // and m_C[] arrays in little endian byte order because 3dm archives
      // are always in little endian byte order.
      //
      // This code assumes sizeof(ON_Color)=4, sizeof(float)=4 
      // and sizeof(double)=8.
      // If this is not the case, then changing the 4's and 8's below
      // will not work.  You will have to copy the mesh definition
      // into temporary arrays of 4 byte floats/8 byte doubles
      // and them compress the temporary arrays.  If you do this,
      // then remove the "restore" byte order calls below.
      file.ToggleByteOrder( Vcount*3, 4, m_V.Array(), (void*)m_V.Array() );
      file.ToggleByteOrder( Ncount*3, 4, m_N.Array(), (void*)m_N.Array() );
      file.ToggleByteOrder( Tcount*2, 4, m_T.Array(), (void*)m_T.Array() );
      file.ToggleByteOrder( Kcount*2, 8, m_K.Array(), (void*)m_K.Array() );
      file.ToggleByteOrder( Ccount,   4, m_C.Array(), (void*)m_C.Array() );
    }
    if (rc) rc = file.WriteCompressedBuffer( Vcount*sizeof(ON_3fPoint),         m_V.Array() );
    if (rc) rc = file.WriteCompressedBuffer( Ncount*sizeof(ON_3fVector),        m_N.Array() );
    if (rc) rc = file.WriteCompressedBuffer( Tcount*sizeof(ON_2fPoint),         m_T.Array() );
    if (rc) rc = file.WriteCompressedBuffer( Kcount*sizeof(ON_SurfaceCurvature),m_K.Array() );
    if (rc) rc = file.WriteCompressedBuffer( Ccount*sizeof(ON_Color),           m_C.Array() );
    if (e == ON::endian::big_endian)
    {
      // These calls restore the m_V[], m_N[], m_T[], m_K[] and m_C[] arrays
      // to the correct big endian runtime byte order.  This must be done even
      // if rc is false.
      file.ToggleByteOrder( Vcount*3, 4, m_V.Array(), (void*)m_V.Array() );
      file.ToggleByteOrder( Ncount*3, 4, m_N.Array(), (void*)m_N.Array() );
      file.ToggleByteOrder( Tcount*2, 4, m_T.Array(), (void*)m_T.Array() );
      file.ToggleByteOrder( Kcount*2, 8, m_K.Array(), (void*)m_K.Array() );
      file.ToggleByteOrder( Ccount,   4, m_C.Array(), (void*)m_C.Array() );
    }
  }

  return rc;
}

bool ON_Mesh::Read_2( int vcount, ON_BinaryArchive& file )
{
  // common to all 2.x formats (compressed)
  const ON::endian e = file.Endian();

  bool rc = true;


  if ( vcount > 0 ) 
  {
    size_t sz = 0;
    bool bFailedCRC;

    sz = 0;
    if (rc) rc = file.ReadCompressedBufferSize( &sz );
    if (rc && sz) 
    {
      if ( sz == vcount*sizeof(m_V[0]) )
      {
        m_V.SetCapacity(vcount);
        if (rc) rc = file.ReadCompressedBuffer( sz,m_V.Array(),&bFailedCRC);
        if (rc) m_V.SetCount(vcount);
      }
      else
      {
        ON_ERROR("ON_Mesh::Read - compressed vertex point buffer size is wrong.");
        rc = false; // buffer is wrong size
      }
    }

    sz = 0;
    if (rc) rc = file.ReadCompressedBufferSize( &sz );
    if (rc && sz) 
    {
      if ( sz == vcount*sizeof(m_N[0]) )
      {
        m_N.SetCapacity(vcount);
        if (rc) rc = file.ReadCompressedBuffer( sz,m_N.Array(),&bFailedCRC );
        if (rc) m_N.SetCount(vcount);
      }
      else
      {
        ON_ERROR("ON_Mesh::Read - compressed vertex normal buffer size is wrong.");
        rc = false; // buffer is wrong size
      }
    }
    
    sz = 0;
    if (rc) rc = file.ReadCompressedBufferSize( &sz );
    if (rc && sz) 
    {
      if ( sz == vcount*sizeof(m_T[0]) )
      {
        m_T.SetCapacity(vcount);
        if (rc) rc = file.ReadCompressedBuffer( sz,m_T.Array(),&bFailedCRC );
        if (rc) m_T.SetCount(vcount);
      }
      else
      {
        ON_ERROR("ON_Mesh::Read - compressed texture coordinate buffer size is wrong.");
        rc = false; // buffer is wrong size
      }
    }
    
    sz = 0;
    if (rc) rc = file.ReadCompressedBufferSize( &sz );
    if (rc && sz) 
    {
      if ( sz == vcount*sizeof(m_K[0]) )
      {
        m_K.SetCapacity(vcount);
        if (rc) rc = file.ReadCompressedBuffer( sz,m_K.Array(),&bFailedCRC );
        if (rc) m_K.SetCount(vcount);
      }
      else
      {
        ON_ERROR("ON_Mesh::Read - compressed vertex curvature buffer size is wrong.");
        rc = false; // buffer is wrong size
      }
    }
    
    sz = 0;
    if (rc) rc = file.ReadCompressedBufferSize( &sz );
    if (rc && sz) 
    {
      if ( sz == vcount*sizeof(m_C[0]) )
      {
        m_C.SetCapacity(vcount);
        if (rc) rc = file.ReadCompressedBuffer( sz,m_C.Array(),&bFailedCRC );
        if (rc) m_C.SetCount(vcount);
      }
      else
      {
        ON_ERROR("ON_Mesh::Read - compressed vertex color buffer size is wrong.");
        rc = false; // buffer is wrong size
      }
    }
    
    if (e == ON::endian::big_endian)
    {
      // This code assumes sizeof(ON_Color)=4, sizeof(float)=4 
      // and sizeof(double)=8.
      // If this is not the case, then changing the 4's and 8's below
      // will not work.  You will have to read the compressed
      // information into temporary arrays of 4 byte floats/8 byte doubles
      // and then convert those numbers to whatever is stored in the
      // m_V[], m_N[], m_T[], m_K[] and m_C[] arrays/
      file.ToggleByteOrder( m_V.Count()*3, 4, m_V.Array(), (void*)m_V.Array() );
      file.ToggleByteOrder( m_N.Count()*3, 4, m_N.Array(), (void*)m_N.Array() );
      file.ToggleByteOrder( m_T.Count()*2, 4, m_T.Array(), (void*)m_T.Array() );
      file.ToggleByteOrder( m_K.Count()*2, 8, m_K.Array(), (void*)m_K.Array() );
      file.ToggleByteOrder( m_C.Count()*3, 4, m_C.Array(), (void*)m_C.Array() );
    }
  }

  return rc;
}

static
bool WriteMeshNgons( ON_BinaryArchive& file, const ON_SimpleArray<ON_MeshNgon*>& ngons )
{
  unsigned int i, Vcount;
  if ( !file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0) )
    return false;

  bool rc = false;
  for(;;)
  {
    unsigned int ngon_count = ngons.UnsignedCount();
    if (!file.WriteInt(ngon_count))
      break;

    for ( i = 0; i < ngon_count; i++)
    {
      const ON_MeshNgon* ngon = ngons[i];
      Vcount = ( 0 != ngon && ngon->m_Vcount > 0 && ngon->m_Fcount > 0 && 0 != ngon->m_vi && 0 != ngon->m_fi ) 
        ? ngon->m_Vcount 
        : 0;
      if ( !file.WriteInt(Vcount) )
        break;
      if (Vcount <= 0 )
        continue;
      if ( !file.WriteInt(ngon->m_Fcount) )
        break;
      if ( !file.WriteInt(Vcount,ngon->m_vi) )
        break;
      if ( !file.WriteInt(ngon->m_Fcount,ngon->m_fi) )
        break;
    }

    if (i==ngon_count)
      rc = true;

    break;
  }

  if ( !file.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

static
bool ReadMeshNgons( ON_BinaryArchive& file, ON_MeshNgonAllocator& a, ON_SimpleArray<ON_MeshNgon*>& ngons )
{
  ngons.SetCount(0);

  int major_version = 0;
  int minor_version = 0;
  unsigned int i, Vcount, Fcount;
  if ( !file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version) )
    return false;

  bool rc = false;
  for(;;)
  {
    unsigned int ngon_count = 0;
    if (!file.ReadInt(&ngon_count))
      break;

    ngons.Reserve(ngon_count);

    for ( i = 0; i < ngon_count; i++)
    {
      Vcount = 0;
      if ( !file.ReadInt(&Vcount) )
        break;
      if ( Vcount <= 0 )
        continue;
      if ( !file.ReadInt(&Fcount) )
        break;
      ON_MeshNgon* ngon = a.AllocateNgon(Vcount,Fcount);
      if ( !file.ReadInt(Vcount,ngon->m_vi) )
        break;
      if ( !file.ReadInt(ngon->m_Fcount,ngon->m_fi) )
        break;
      ngons.Append(ngon);
    }

    if (i == ngon_count)
      rc = true;

    break;
  }

  if ( !file.EndRead3dmChunk() )
    rc = false;

  return rc;
}


static
bool WriteMeshDoublePrecisionVertices(
  ON_BinaryArchive& file,
  const ON_SimpleArray<ON_3dPoint>& dV
  )
{
  const int major_version = 1;
  const int minor_version = 0;
  if ( !file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,major_version,minor_version) )
    return false;

  bool rc = false;

  for (;;)
  {
    const unsigned int dVcount = dV.UnsignedCount();
    if (!file.WriteInt(dVcount))
      break;
    if (0 == dVcount)
    {
      rc = true;
      break;
    }

    const ON::endian e = file.Endian();
    if (e == ON::endian::big_endian)
    {
      file.ToggleByteOrder(dVcount * 3, 8, dV.Array(), (void*)dV.Array());
    }
    if (!file.WriteCompressedBuffer(dVcount*sizeof(ON_3dPoint), dV.Array()))
      break;
    if (e == ON::endian::big_endian)
    {
      file.ToggleByteOrder(dVcount * 3, 8, dV.Array(), (void*)dV.Array());
    }

    rc = true;
    break;
  }

  if ( !file.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

static
bool ReadMeshDoublePrecisionVertices( 
  ON_BinaryArchive& file, 
  ON_SimpleArray<ON_3dPoint>& dV 
  )
{
  dV.SetCount(0);

  int major_version = 0;
  int minor_version = 0;
  if ( !file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version) )
    return false;

  bool rc = false;
  for(;;)
  {
    if (1 != major_version)
      break;

    unsigned int dVcount = 0;
    if (!file.ReadInt(&dVcount))
      break;

    if (0 == dVcount)
    {
      rc = true;
      break;
    }

    size_t sz = 0;
    if (!file.ReadCompressedBufferSize( &sz ))
      break;

    if (sz != ((size_t)dVcount)*sizeof(ON_3dPoint))
    {
      ON_ERROR("Compressed double precision vertex point buffer size is wrong.");
      break;
    }

    dV.SetCapacity(dVcount);
    dV.SetCount(dVcount);
    ON_3dPoint* a = dV.Array();
    if (nullptr == a || dVcount != dV.UnsignedCount())
    {
      ON_ERROR("Unable to allocate double precision vertex point array.");
      break;
    }
    
    bool bFailedCRC = 0;
    if (!file.ReadCompressedBuffer( sz, a, &bFailedCRC))
      break;

    rc = true;
    break;
  }

  if (!rc)
    dV.SetCount(0);
  if ( !file.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool ON_Mesh::Write( ON_BinaryArchive& file ) const
{
  int i;
  //const int major_version = 1; // uncompressed
  //const int major_version = 2; // beta format (never used)
  const int major_version = 3; // compressed

  const int minor_version 
    = (file.Archive3dmVersion() >= 60) 
    //? 6  // ngons saved in V6 files as of mid November, 2013
    //? 7  // double precision vertices no longer on user data.
    ? 8  // double precision vertex box
    : 5;

  bool rc = file.Write3dmChunkVersion(major_version,minor_version);

  const unsigned int vcount = VertexUnsignedCount();
  const unsigned int fcount = FaceUnsignedCount();

  if (rc) rc = file.WriteInt( vcount );
  if (rc) rc = file.WriteInt( fcount );
  if (rc) rc = file.WriteInterval( m_packed_tex_domain[0] );
  if (rc) rc = file.WriteInterval( m_packed_tex_domain[1] );
  if (rc) rc = file.WriteInterval( m_srf_domain[0] );
  if (rc) rc = file.WriteInterval( m_srf_domain[1] );
  if (rc) rc = file.WriteDouble( 2, m_srf_scale );

  // legacy float precision vertex bounding box
  float fbbox[2][3] = { { 1.0f, 1.0f, 1.0f }, { -1.0f, -1.0f, -1.0f } };
  if (m_vertex_bbox.IsNotEmpty())
  {
    fbbox[0][0] = ON_FloatFloor(m_vertex_bbox.m_min.x);
    fbbox[0][1] = ON_FloatFloor(m_vertex_bbox.m_min.y);
    fbbox[0][2] = ON_FloatFloor(m_vertex_bbox.m_min.z);
    fbbox[1][0] = ON_FloatCeil(m_vertex_bbox.m_max.x);
    fbbox[1][1] = ON_FloatCeil(m_vertex_bbox.m_max.y);
    fbbox[1][2] = ON_FloatCeil(m_vertex_bbox.m_max.z);
  }
  if (rc) rc = file.WriteFloat( 6, &fbbox[0][0] );

  if (rc) rc = file.WriteFloat( 6, &m_nbox[0][0] );
  if (rc) rc = file.WriteFloat( 4, &m_tbox[0][0] );

  // archive int value meaning: -1 = unknown 0 = mesh is not closed, 1 = mesh is closed
  i = -1;
  switch( m_mesh_is_closed )
  {
  case 0: // unset
    i = -1;
    break;
  case 1: // closed
    i = 1;
    break;
  case 2: // not closed
    i = 0;
    break;
  }
  if (rc) rc = file.WriteInt( i );

  unsigned char b = m_mesh_parameters ? 1 : 0;
  if (rc) rc = file.WriteChar(b);
  if (rc && b) {
    if (rc) rc = file.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 0 );
    if (rc) {
      rc = m_mesh_parameters->Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  for ( i = 0; rc && i < 4; i++ ) {
    b = m_kstat[i] ? 1 : 0;
    rc = file.WriteChar(b);
    if (b) {
      rc = file.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 0 );
      if (rc) {
        rc = m_kstat[i]->Write(file);
        if ( !file.EndWrite3dmChunk() )
          rc = false;
      }
    }
  }

  if (rc) rc = WriteFaceArray( vcount, fcount, file );

  if (rc) {
    // major version is a hard coded 3

    //if ( major_version == 1 )
    //  rc = Write_1(file);
    //else if ( major_version == 3 )
      rc = Write_2(vcount,file);
    //else
    //  rc = false;
  }

  // added for minor version 1.2 and 3.2
  i = m_packed_tex_rotate ? 1 : 0;
  if (rc) rc = file.WriteInt( i );

  // added for minor version 3.3
  if (rc) rc = file.WriteUuid( m_Ttag.m_mapping_id );
 
  // compressed m_S[]
  if ( rc && vcount > 0U ) 
  {
    // Before 201011049 there was a bug that let m_S[] arrays
    // with the wrong size get saved in files. 
    const unsigned int Scount = (vcount == m_S.UnsignedCount()) ? m_S.UnsignedCount() : 0;
    const ON::endian e = file.Endian();
    if (e == ON::endian::big_endian)
    {
      file.ToggleByteOrder( Scount*2, 8, m_S.Array(), (void*)m_S.Array() );
    }
    if (rc) rc = file.WriteCompressedBuffer( Scount*sizeof(ON_2dPoint),m_S.Array() );
    if (e == ON::endian::big_endian)
    {
      file.ToggleByteOrder( Scount*2, 8, m_S.Array(), (void*)m_S.Array() );
    }
  }

  // added for minor version 3.4
  if (rc) rc = m_Ttag.Write(file);

  // added for minor version 3.5
  if (rc) rc = file.WriteChar( m_mesh_is_manifold );
  if (rc) rc = file.WriteChar( m_mesh_is_oriented );
  if (rc) rc = file.WriteChar( m_mesh_is_solid );


  if ( rc && minor_version >= 6 )
  {
    // added n-gons version 3.6
    bool bHasNgons = HasNgons();    
    rc =  file.WriteBool(bHasNgons);
    if (rc && bHasNgons)
      rc = WriteMeshNgons(file,m_Ngon);

    if (rc && minor_version >= 7)
    {
      // added explicit double precision vertices chunk version 3.7
      // (used to be on user data)
      const bool bHasDoublePrecisionVertices = HasDoublePrecisionVertices();
      if (rc) rc = file.WriteBool(bHasDoublePrecisionVertices);
      if (rc && bHasDoublePrecisionVertices)
        rc = WriteMeshDoublePrecisionVertices(file, m_dV);

      if (rc && minor_version >= 8)
      {
        rc = file.WriteBoundingBox(m_vertex_bbox);
      }
    }
  }
  
  
  if (rc 
    && 50 == file.Archive3dmVersion() 
    && vcount > 0 
    && HasSynchronizedDoubleAndSinglePrecisionVertices() 
    )
  {
    // save double precision vertices using V5 user data.
    ON_V5_MeshDoubleVertices* ud = ON_V5_MeshDoubleVertices::AttachV5(this);
    if (nullptr != ud)
    {
      ud->m_V5_dV = m_dV;
      ud->m_dcount = ud->m_V5_dV.UnsignedCount();
      ud->m_dCRC = ud->DoubleCRC();
      ud->m_fcount = m_V.UnsignedCount();
      ud->m_fCRC = ON_V5_MeshDoubleVertices::FloatCRC(m_V);
      // This obsolete user data will be deleted after it is written to the V5 .3dm file.
    }
  }

  return rc;
}

//// This id was used in the ON_Mesh::m_mapping_id
//// field to indicate the texture coordinates are the
//// canonical ON_Mesh uv texture coordinates by the 
//// OpenNURBS parametric surface meshers like
//// ON_Surface::CreateMesh() and ON_Brep::CreateMesh().
//
//// {B988A6C2-61A6-45a7-AAEE-9AED7EF4E316}
static const ON_UUID obsolete_default_srfp_mapping_id = { 0xb988a6c2, 0x61a6, 0x45a7, { 0xaa, 0xee, 0x9a, 0xed, 0x7e, 0xf4, 0xe3, 0x16 } };

bool ON_TextureMapping::Internal_WriteV5(
  ON_BinaryArchive& file
  ) const
{
  bool rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,1);
  if (rc)
  {

    for(;;)
    {
      rc = file.WriteUuid( Id() );
      if (!rc) break;

      rc = file.WriteInt( static_cast<unsigned int>(m_type) );
      if (!rc) break;

      rc = file.WriteInt( static_cast<unsigned int>(m_projection) );
      if (!rc) break;

      rc = file.WriteXform( m_Pxyz );
      if (!rc) break;

      // Do not write m_Nxyz - it is calculated from m_Pxyz.
      rc = file.WriteXform( m_uvw );
      if (!rc) break;

      rc = file.WriteString(Name());
      if (!rc) break;

      rc = file.WriteObject(m_mapping_primitive.get());
      if (!rc) break;

      // 13 October 2006 ver 1.1 fields
      rc = file.WriteInt( static_cast<unsigned int>(m_texture_space) );
      if (!rc) break;

      rc = file.WriteBool(m_bCapped);
      if (!rc) break;

      break;
    }

    if ( !file.EndWrite3dmChunk() )
      rc = false;
  }

  return rc;
}

bool ON_TextureMapping::Internal_ReadV5(
  ON_BinaryArchive& file
  )
{
  *this = ON_TextureMapping::Unset;

  int major_version = 0;
  int minor_version = 0;

  bool rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if (rc)
  {
    if ( 1 == major_version )
    {
      // DO NOT SAVE m_mapping_index in archive.
      // 1.0 fields
      for(;;)
      {
        ON_UUID id = ON_nil_uuid;
        rc = file.ReadUuid( id );
        if (!rc) break;
        if (id == ON_nil_uuid || id == ON_TextureMapping::SurfaceParameterTextureMapping.Id())
        {
          // nil ids are no longer permitted and
          // system component ids can not be used by 
          // ordinary components.
          id = ON_CreateId();
        }
        SetId(id);

        unsigned int type_as_unsigned = 0;
        rc = file.ReadInt( &type_as_unsigned );
        if (!rc) break;
        m_type = TypeFromUnsigned(type_as_unsigned);

        unsigned int projection_as_unsigned = 0;
        rc = file.ReadInt( &projection_as_unsigned );
        if (!rc) break;
        m_projection = ProjectionFromUnsigned(projection_as_unsigned);

        rc = file.ReadXform( m_Pxyz );
        if (!rc) break;

        m_Pxyz.GetSurfaceNormalXform(m_Nxyz);

        rc = file.ReadXform( m_uvw );
        if (!rc) break;
        
        ON_wString name;
        rc = file.ReadString(name);
        if (!rc) break;
        SetName(name);

		ON_Object* pMappingPrimitive = nullptr;
        rc = (file.ReadObject(&pMappingPrimitive) >= 0);
        if (!rc) break;

		m_mapping_primitive.reset(pMappingPrimitive);

        if ( minor_version >= 1 )
        {
          unsigned int texture_space_as_unsigned = 0;
          rc = file.ReadInt(&texture_space_as_unsigned);
          if (!rc) break;
          m_texture_space = TextureSpaceFromUnsigned(texture_space_as_unsigned);

          rc = file.ReadBool(&m_bCapped);
          if (!rc) break;
        }

        break;
      }
    }

    if ( !file.EndRead3dmChunk() )
      rc = false;
  }

  return rc;
}

bool ON_TextureMapping::Write(
  ON_BinaryArchive& archive
  ) const
{
  return Internal_WriteV5(archive);
}

bool ON_TextureMapping::Read(
  ON_BinaryArchive& archive
  )
{
  return Internal_ReadV5(archive);
}


static
void GetSurfaceParametersHelper( const ON_Mesh& mesh,
                                 double tex_x, double tex_y, 
                                 double* srf_s, double* srf_t )
{
  // convert texture coordinates to surface parameters
  // Used to reconstruct m_S[] when old files are read.
  double tex_s, tex_t;

  if ( mesh.m_packed_tex_rotate ) 
  {
    // undo rotation and normalize
    tex_s =  mesh.m_packed_tex_domain[1].NormalizedParameterAt( tex_y );
    tex_t = 1.0 -  mesh.m_packed_tex_domain[0].NormalizedParameterAt( tex_x );
  }
  else 
  {
    // normalize
    tex_s =  mesh.m_packed_tex_domain[0].NormalizedParameterAt( tex_x );
    tex_t =  mesh.m_packed_tex_domain[1].NormalizedParameterAt( tex_y );
  }
  *srf_s =  mesh.m_srf_domain[0].ParameterAt(tex_s);
  *srf_t =  mesh.m_srf_domain[1].ParameterAt(tex_t);
}


bool ON_Mesh::Read( ON_BinaryArchive& file )
{
  Destroy();

  int major_version = 0;
  int minor_version = 0;
  int i;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  
  if (rc && (1 == major_version || 3 == major_version) ) 
  {
    int vcount = 0;
    int fcount = 0;

    if (rc) rc = file.ReadInt( &vcount );
    if (rc) rc = file.ReadInt( &fcount );
    if (rc) rc = file.ReadInterval( m_packed_tex_domain[0] );
    if (rc) rc = file.ReadInterval( m_packed_tex_domain[1] );
    if (rc) rc = file.ReadInterval( m_srf_domain[0] );
    if (rc) rc = file.ReadInterval( m_srf_domain[1] );
    if (rc) rc = file.ReadDouble( 2, m_srf_scale );

    float fbbox[2][3] = { { 1.0f, 1.0f, 1.0f }, { -1.0f, -1.0f, -1.0f } };
    if (rc) rc = file.ReadFloat( 6, &fbbox[0][0] );
    if (rc && fbbox[0][0] <= fbbox[1][0] && fbbox[0][1] <= fbbox[1][1] && fbbox[0][2] <= fbbox[1][2] )
    {
      // When minor_version >= 8, m_vertex_bbox will be read from the archive later.
      m_vertex_bbox.m_min = ON_3fPoint(fbbox[0]);
      m_vertex_bbox.m_max = ON_3fPoint(fbbox[1]);
    }

    if (rc) rc = file.ReadFloat( 6, &m_nbox[0][0] );
    if (rc) rc = file.ReadFloat( 4, &m_tbox[0][0] );

    // int value meaning: -1 = unknown 0 = mesh is not closed, 1 = mesh is closed
    i = -1;
    if (rc) rc = file.ReadInt( &i );
    if (rc)
    {
      switch(i)
      {
      case 0: // not closed;
        SetClosed(0);
        break;
      case 1: // closed;
        SetClosed(1);
        break;
      case 2: // 13 April 2010 Dale Lear - "2" value is obsolete but appears in old files
        SetClosed(1);
        break;
      }
    }

    unsigned char b = 0;
    ON__UINT32 tcode=0;
    ON__INT64 big_value=0;
    if (rc) rc = file.ReadChar(&b);
    if (rc && b) 
    {
      // mesh parameters are in an anonymous chunk
      rc = file.BeginRead3dmBigChunk(&tcode,&big_value);
      if (rc) 
      {
        if ( TCODE_ANONYMOUS_CHUNK == tcode )
        {
          m_mesh_parameters = new ON_MeshParameters();
          rc = m_mesh_parameters->Read( file );
        }
        else
          rc = false;
        if (!file.EndRead3dmChunk())
          rc = false;
      }
    }

    for ( i = 0; rc && i < 4; i++ ) 
    {
      rc = file.ReadChar(&b);
      if (rc && b) 
      {
        // m_kstat[i] curvature stats are in an anonymous chunk
        tcode = 0;
        big_value = 0;
        rc = file.BeginRead3dmBigChunk( &tcode, &big_value );
        if (rc) 
        {
          if ( TCODE_ANONYMOUS_CHUNK == tcode )
          {
            m_kstat[i] = new ON_MeshCurvatureStats();
            rc = m_kstat[i]->Read(file);
          }
          else
            rc = false;
          if ( !file.EndRead3dmChunk() )
            rc = false;
        }
      }
    }

    if (rc) rc = ReadFaceArray( vcount, fcount, file );

    if (rc) {
      if ( major_version==1) {
        rc = Read_1(file);
      }
      else if ( major_version == 3 ) {
        rc = Read_2(vcount,file);
      }
      else
        rc = false;
    }

    if ( minor_version >= 2 ) 
    {
      int b_packed_tex_rotate = m_packed_tex_rotate;
      if (rc) rc = file.ReadInt( &b_packed_tex_rotate );
      m_packed_tex_rotate = b_packed_tex_rotate?true:false;
    }

    if ( 3 == major_version )
    {
      if ( minor_version >= 3 )
      {
        // added for minor version 3.3
        if (rc) rc = file.ReadUuid( m_Ttag.m_mapping_id );

        // compressed m_S[]
        if ( rc && vcount > 0 ) 
        {
          size_t sz = 0;
          bool bFailedCRC=false;
          if (rc) rc = file.ReadCompressedBufferSize( &sz );
          if (rc && sz) 
          {
            if ( sz == vcount*sizeof(ON_2dPoint) )
            {
              m_S.SetCapacity(vcount);
              if (rc) rc = file.ReadCompressedBuffer( sz, m_S.Array(), &bFailedCRC );
              if (rc) m_S.SetCount(vcount);
              if (ON::endian::big_endian == file.Endian())
              {
                file.ToggleByteOrder( m_S.Count()*2, 8, m_S.Array(), (void*)m_S.Array() );
              }
            }
            else
            {
              ON_ERROR("ON_Mesh::Read - surface parameter buffer size is wrong.");
              if (    rc
                   && file.ArchiveOpenNURBSVersion() <= 201011049 
                   && 0 == (sz % sizeof(ON_2dPoint))
                   && sz >= sizeof(ON_2dPoint)
                 )
              {
                // Before 201011049 there was a bug that let m_S[] arrays with
                // the wrong size get saved in files. There was also a bug in 
                // the Rhino .OBJ file reader that created meshes with m_S[] 
                // arrays that had the wrong size.  The next 4 lines of code
                // let us read the junk, discard it and then successfully read
                // the rest of the file.
                int Scount = (int)(sz / sizeof(ON_2dPoint));
                m_S.SetCapacity(Scount);
                rc = file.ReadCompressedBuffer( sz, m_S.Array(), &bFailedCRC );
                m_S.Destroy();
              }
              else
              {
                rc = false; // buffer is wrong size
              }
            }
          }
        }
        if ( minor_version >= 4 && file.ArchiveOpenNURBSVersion() >= 200606010 )
        {
          if (rc) rc = m_Ttag.Read(file);
          if ( minor_version >= 5 )
          {
            if (rc) rc = file.ReadChar( &m_mesh_is_manifold );
            if (rc) rc = file.ReadChar( &m_mesh_is_oriented );
            if (rc) rc = file.ReadChar( &m_mesh_is_solid );

            if ( rc && minor_version >= 6 )
            {
              // added n-gons version 3.6
              bool bHasNgons = false;    
              rc =  file.ReadBool(&bHasNgons);
              if (rc && bHasNgons)
                rc = ReadMeshNgons(file, m_NgonAllocator, m_Ngon);
              if (rc && minor_version >= 7)
              {
                bool bHasDoublePrecisionVertices = false;
                rc = file.ReadBool(&bHasDoublePrecisionVertices);
                bool bHasInvalidDoublePrecisionVertices = false;
                if (bHasDoublePrecisionVertices)
                {
                  // Added explicit double precision vertices chunk version 3.7
                  // (used to be on user data)
                  rc = ReadMeshDoublePrecisionVertices(file, m_dV);
                  if (rc && m_dV.UnsignedCount() == m_V.UnsignedCount())
                  {
                    // Validate m_dV[] - some files contain different values for m_V[] and m_dV[].
                    // When this happens, delete m_dV[].
                    const unsigned int dvcount = m_dV.UnsignedCount();
                    for (unsigned int vdex = 0; vdex < dvcount; vdex++)
                    {
                      const ON_3fPoint P(m_dV[vdex]);
                      const double m = fabs(m_V[vdex].MaximumCoordinate());
                      const double d = fabs((P - m_V[vdex]).MaximumCoordinate());
                      if (d <= m*1.0e-6)
                        continue;
                      bHasInvalidDoublePrecisionVertices = true;
                      m_dV.Destroy();
                      break;
                    }
                  }
                  if (rc && m_dV.UnsignedCount() == m_V.UnsignedCount() && minor_version <= 7)
                  {
                    m_vertex_bbox.Set(m_dV, false);
                  }
                }
                if (rc && minor_version >= 8)
                {
                  rc = file.ReadBoundingBox(m_vertex_bbox);
                }
                if (bHasInvalidDoublePrecisionVertices)
                {
                  m_vertex_bbox.Set(m_V, false);
                }
              }
            }
          }
        }
      }
    }

    if (    0 == m_S.Count()
         && m_V.Count() > 0
         && HasTextureCoordinates()
         && m_srf_domain[0].IsIncreasing() 
         && m_srf_domain[1].IsIncreasing() 
         && m_packed_tex_domain[0].IsInterval()
         && m_packed_tex_domain[1].IsInterval()
         && 0 == m_Ttag.m_mapping_crc
         && ON_UuidIsNil(m_Ttag.m_mapping_id)
          ) 
    {
      // This is a mesh from an old file - but there is enough 
      // information to calculate the m_S[] values from the 
      // m_T[] values.
      m_S.SetCapacity(vcount);
      m_S.SetCount(0);
      ON_2dPoint sp;
      ON_2fPoint tc;
      for ( i = 0; i < vcount; i++)
      {
        tc = m_T[i];
        sp.x = tc.x;
        sp.y = tc.y;
        GetSurfaceParametersHelper(*this,sp.x,sp.y,&sp.x,&sp.y);
        m_S.Append(sp);
      }
      m_Ttag.SetDefaultSurfaceParameterMappingTag();
    }
  }

  return rc;
}

ON::object_type ON_Mesh::ObjectType() const
{
  return ON::mesh_object;
}

int ON_Mesh::Dimension() const
{
  return 3;
}

#if defined(ON_COMPILER_MSC)
// Disable the MSC /W4 warning
//   C4189: 'breakpoint_here_for_bad_vbox' : local variable is initialized but not referenced
// on the line
//   int breakpoint_here_for_bad_vbox = 0.  
// The warning disable is here because MS is ignoring it
// if I put it inside of the function.
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4189 ) 
#endif

float ON_FloatFloor(double x)
{
  // If x is a NaN, you get what you deserve.
  //
  // If x is a finite valid double in the range -3.402823466e+38
  // to +3.402823466e+38, then returned value of f is the largest
  // float value that is mathematically less than or equal to the
  // value of x.
  //
  // If x is not in the float range or x is a NaN, then you get
  // what you deserve.
  //
  // ON_FLOAT_EPSILON = 1.192092896e-07 is the smallest number such that
  // 1.0f + 1.192092896e-07f > 1.0f.  
  //
  // If x < 0, then (1.0 + 0.5*1.192092896e-07)*x rounds x down so
  // that converting the double precision mantissa cannot create a
  // float value that is mathematically larger than the value of x.  
  //
  // If x > 0, then (1.0 - 0.5*1.192092896e-07)*x rounds x down so
  // that converting the double precision mantissa cannot create a
  // float value that is mathematically larger than the value of x.  
  // 
  const double e = (x < 0.0) ? (1.0 + 0.5*ON_FLOAT_EPSILON) : (1.0 - 0.5*ON_FLOAT_EPSILON);
  float f;
  f = (float)(e*x);
  return f;
}

float ON_FloatCeil(double x)
{
  float f = (x != 0.0) ? (-ON_FloatFloor(-x)) : ((float)x);
  return f;
}

bool ON_Mesh::GetBBox( // returns true if successful
       double* boxmin, // minimum
       double* boxmax, // maximum
       bool bGrowBox
       ) const
{
  bool rc = false;
  const unsigned int facet_count  = FaceCount();
  const unsigned int vertex_count = VertexCount();
  if ( facet_count >= 1 && vertex_count >= 3 ) 
  {
    rc = m_vertex_bbox.IsNotEmpty();
    if ( false == rc ) 
    {
      if ( HasDoublePrecisionVertices() )
      {
        const ON_3dPointArray& dV = DoublePrecisionVertices();
        if ( dV.UnsignedCount() == m_V.UnsignedCount() )
          rc = m_vertex_bbox.Set(dV, false);
      }
      if (false == rc)
      {
        rc = m_vertex_bbox.Set(m_V, false);
      }
    }

    if ( rc ) 
    {
      ON_BoundingBox vbox(m_vertex_bbox);
      if ( bGrowBox )
      {
        vbox.Union( ON_BoundingBox(ON_3dPoint(boxmin),ON_3dPoint(boxmax)) );
      }
      boxmin[0] = vbox.m_min.x;
      boxmin[1] = vbox.m_min.y;
      boxmin[2] = vbox.m_min.z;
      boxmax[0] = vbox.m_max.x;
      boxmax[1] = vbox.m_max.y;
      boxmax[2] = vbox.m_max.z;
    }
  }
  return rc;
}

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif

bool ON_Mesh::IsDeformable() const
{
  return true;
}

bool ON_Mesh::MakeDeformable()
{
  return true;
}

bool ON_Mesh::Transform( 
       const ON_Xform& xform
       )
{
  // Transform user data before doing sanity checks in case rogue code
  // damages m_V[], m_dV[] or other data members.
  TransformUserData(xform);
	DestroyTree();

  const unsigned int vertex_count = VertexUnsignedCount();

  const bool bIsValid_fV = (vertex_count == m_V.UnsignedCount());
  if (false == bIsValid_fV)
    m_V.SetCount(0);

  bool bIsValid_dV = (vertex_count == m_dV.UnsignedCount());

  // 2 Jan 2020 S. Baer (RH-54464)
  // If the transform is moving the mesh into or out of "beyond single precision",
  // set up double precision vertices in order to get our best possible precision
  // after the transform.
  if (false == bIsValid_dV)
  {
    ON_BoundingBox bbox = BoundingBox();
    ON_BoundingBox transformed_bbox = bbox;
    transformed_bbox.Transform(xform);
    if (ON_BeyondSinglePrecision(bbox, nullptr) || ON_BeyondSinglePrecision(transformed_bbox, nullptr))
    {
      UpdateDoublePrecisionVertices();
      bIsValid_dV = (vertex_count == m_dV.UnsignedCount());
    }
  }


  if (false == bIsValid_dV)
    m_dV.SetCount(0);

  const bool bSyncheddV = bIsValid_fV && bIsValid_dV && HasSynchronizedDoubleAndSinglePrecisionVertices();

  if (bIsValid_dV)
    ON_TransformPointList(3, false, vertex_count, 3, &m_dV[0][0], xform);
  
  double d = xform.Determinant();
  bool rc = false;
  if ( bSyncheddV )
  {
    // transforming the double precision vertices is the 
    // best way to set the floats.
    UpdateSinglePrecisionVertices();
    rc = true;
  }
  else if ( bIsValid_fV )
  {
    rc = ON_TransformPointList( 3, false, vertex_count, 3, &m_V[0][0], xform );
  }

  if ( rc )
  {
    m_Ctag.Transform(xform);
    m_Ttag.Transform(xform);
    int tci, tccnt = m_TC.Count();
    for ( tci = 0; tci < tccnt; tci++ )
    {
      m_TC[tci].m_tag.Transform(xform);
    }
  }

  if ( rc && 0.0 == d )
  {
    // mesh has been squashed to a plane (or worse)
    if ( HasVertexNormals() )
    {
      ComputeFaceNormals();
      ComputeVertexNormals();
    }
    else if ( HasFaceNormals() )
    {
      ComputeFaceNormals();
    }
  }
  else if ( rc )
  {
    if ( HasVertexNormals() ) 
    {
      // See http://www.gignews.com/realtime020100.htm or these
      // references.
      //
      // 1. Hanrahan, Pat, 
      //    "A Survey of Ray-Surface Intersection Algorithms", 
      //     chapter 3 in Andrew Glassner (editor), 
      //     An Introduction to Ray Tracing, 
      //     Academic Press Inc., London, 1989.
      //
      // 2. Turkowski, Ken, 
      //    "Properties of Surface-Normal Transformations", 
      //     in Andrew Glassner (editor), 
      //     Graphics Gems, Academic Press, Inc., 
      //     pp. 539-547, 1990. 
      ON_Xform N_xform;
      const double det = xform.GetSurfaceNormalXform(N_xform);
      rc = ON_TransformVectorList( 3, vertex_count, 3, &m_N[0][0], N_xform )?true:false;
      if ( det < 0.0 )
      {
        FlipVertexNormals();
      }
      UnitizeVertexNormals();
    }

    if ( rc && HasFaceNormals() ) 
    {
      ComputeFaceNormals();
    }
  }

  if ( rc && HasPrincipalCurvatures() ) 
  {
    if ( fabs(fabs(d) - 1.0) > ON_SQRT_EPSILON ) 
    {
      // If it's a uniform scale, handle it, otherwise we can't do it.
      double scale = xform.m_xform[0][0];
      if ( 0.0 != scale && 0.0 != d
           && scale == xform.m_xform[1][1] 
           && scale == xform.m_xform[2][2] 
           && fabs(d - scale*scale*scale) <= d*ON_SQRT_EPSILON )
      {
        // uniform scale
        const double ks = 1.0/scale;
        ON_SurfaceCurvature* sc = m_K.Array();
        int ki = m_K.Count();
        while ( ki-- )
        {
          sc->k1 *= ks;
          sc->k2 *= ks;
          sc++;
        }

        // update curvature stats.
        for ( int j = 0; j < 4; j++ )
        {
          if ( m_kstat[j] )
            m_kstat[j]->Set( m_kstat[j]->m_style,m_K.Count(),m_K.Array(),m_N.Array() );
        }
      }
      else
      {
        ON_ERROR("ON_Mesh::Transform() cannot apply this transform to curvatures.\n");
        rc = false;
      }
    }
  }

  InvalidateVertexBoundingBox();
  InvalidateVertexNormalBoundingBox();
  if ( fabs(d) <= ON_ZERO_TOLERANCE )
    DestroyTopology(); // transform may not be one-to-one on vertices

  return rc;
}

void ON_Mesh::DestroyRuntimeCache( bool bDelete )
{
  int i;

  DestroyTree(bDelete);

  if (bDelete )
  {    
    DestroyPartition();
    m_top.Destroy();
    DeleteMeshParameters();
    InvalidateCurvatureStats();
  }
  else
  {
    // do not free any memory
    m_top.EmergencyDestroy();
  }

  InvalidateBoundingBoxes();
  m_partition = 0;
  m_mesh_parameters = 0;
  m_top.m_mesh = this;
  m_parent = 0;
  //m_material_index = -1;
  m_mesh_is_closed = 0;
  m_mesh_is_manifold = 0;
  m_mesh_is_oriented = 0;
  m_mesh_is_solid = 0;
  for ( i = 0; i < 4; i++ ) 
  {
    m_kstat[i] = 0;
  }
}

bool ON_Mesh::SwapCoordinates(
      int i, int j        // indices of coords to swap
      )
{
  if ( i == j )
    return true;

  const unsigned int vertex_count = VertexUnsignedCount();
  const bool bIsValid_fV = (vertex_count == m_V.UnsignedCount());
  const bool bIsValid_dV = (vertex_count == m_dV.UnsignedCount());

  bool rc = false; 
  if (bIsValid_dV && ON_SwapPointListCoordinates(vertex_count, 3, &m_dV[0][0], i, j))
    rc = true;

  if (bIsValid_fV && ON_SwapPointListCoordinates(vertex_count, 3, &m_V[0][0], i, j))
    rc = true;

  if ( rc && HasVertexNormals() )
  {
    rc = ON_SwapPointListCoordinates( vertex_count, 3, &m_N[0][0], i, j );
  }
  if ( rc )
  {
    float x;
    if( m_vertex_bbox.IsNotEmpty())
      m_vertex_bbox.SwapCoordinates(i, j);

    if ( m_nbox[0][0] <= m_nbox[1][0] ) 
    {
      x = m_nbox[0][i]; m_nbox[0][i] = m_nbox[0][j]; m_nbox[0][j] = x;
      x = m_nbox[1][i]; m_nbox[1][i] = m_nbox[1][j]; m_nbox[1][j] = x;
    }
  }

  return rc;
}

void ON_Mesh::SetClosed(int b)
{
  // 6 November 2003 Dale Lear - let expert user set m_mesh_is_closed
  char mesh_is_closed = 0;
  switch(b)
  {
  case 0: // not closed - at least one boundary edge
    mesh_is_closed = 2;
    SetSolidOrientation(0);
    break;
  case 1: // all edges are shared 
    // DO NOT SET m_mesh_is_solid here.
    // Meshes can be closed but not solid
    mesh_is_closed = 1; 
    break;
  case 2: // 31 April 2010 Dale Lear - 2 is obsolete - it's either 0 or 1 now.
    mesh_is_closed = 1; 
    // DO NOT SET m_mesh_is_solid here.
    // Meshes can be closed but not solid
    break;
  default:
    mesh_is_closed = 0; // unset
    break;
  }
  if ( 0 == mesh_is_closed || m_mesh_is_closed != mesh_is_closed )
  {
    m_mesh_is_closed = mesh_is_closed;
    m_mesh_is_manifold = 0; // unset - will be reevaluated when needed
    m_mesh_is_oriented = 0; // unset - will be reevaluated when needed
  }
}

void ON_Mesh::SetSolidOrientation(int solid_orientation)
{
  switch(solid_orientation)
  {
  case -1: // closed oriented manifold solid with inward face normals
    SetClosed(1);
    m_mesh_is_manifold = 1;
    m_mesh_is_oriented = 1;
    m_mesh_is_solid = 2;
    break;

  case  0: // not solid
    m_mesh_is_solid = 3;
    // DO NOT SET m_mesh_is_closed here.
    // Meshes can be closed but not solid
    break;

  case  1: // closed oriented manifold solid with outward face normals
    SetClosed(1);
    m_mesh_is_manifold = 1;
    m_mesh_is_oriented = 1;
    m_mesh_is_solid = 1;
    break;

  default:
    m_mesh_is_solid = 0;
    break;
  }
}


static 
int ON_MeshIsManifold_Compare3floats( const void* a, const void* b )
{
  // NOPE // memcmp thinks -0.0f and 0.0f are different numbers // return memcmp(a,b,sizeof(ON_3fPoint));

  const float* fa = (const float*)a;
  const float* fb = (const float*)b;
  for (const float* fa3 = fa + 3; fa < fa3; ++fa, ++fb)
  {
    const float x = *fa;
    const float y = *fb;
    if (x < y)
      return -1;
    if (x > y)
      return 1;
    if (x == y)
      continue; // neither x nor y is a nan

    // at least one of x and y is a nan
    // use convention (not a nan) < (nan) because this code must use a well ordered compare for all values.
    if (x == x)
      return -1; // x is not a nan, y is a nan
    if (y == y)
      return 1; // x is a nan, y is not a nan
  }
  return 0;
}

static 
int ON_MeshGetVertexEdges_Compare2dex( const void* a, const void* b )
{
  return ON_Compare2dex((const ON_2dex*)a,(const ON_2dex*)b);
}

static 
int ON_MeshIsManifold_Compare3dex( const void* a, const void* b )
{
  return ON_Compare3dex((const ON_3dex*)a,(const ON_3dex*)b);
}

//static 
//int ON_MeshGetVertexEdges_CompareInt( const int* a, const int* b )
//{
//  return (*a-*b);
//}


int ON_Mesh::GetVertexEdges( 
  int vertex_index_count,
  const int* vertex_index, 
  bool bNoDuplicates,
  ON_SimpleArray<ON_2dex>& edges
  ) const
{
  // Get edges connected to vertices in vertex_index[] array.
  const int edges_count0 = edges.Count();

  const int mesh_vcount = m_V.Count();

  //03/12/2007 TimH. The line below appears to be a typo.  Using the following line works better.
  //const int mesh_fcount = m_V.Count();
  const int mesh_fcount = m_F.Count();

  if (   vertex_index_count <= 0 || 0 == vertex_index 
      || mesh_fcount <= 0 || mesh_vcount < 3 )
  {
    return 0;
  }

  int vei, efi, fvi, ei, fi, j, n, vi;
  const int* f_vi;
  ON_2dex edge_ends;
  const ON_MeshFace* f = m_F.Array();

  if (   TopologyExists()
       && mesh_vcount == m_top.m_topv_map.Count()
       && m_top.m_tope.Count() > 0 )
  {
    // Topology looks good; use it to speed up the search.
    const int* topv_map = m_top.m_topv_map;
    const int top_vcount = m_top.m_topv.Count();
    const int top_ecount = m_top.m_tope.Count();
    int top_vi;
    for ( n = 0; n < vertex_index_count; n++ )
    {
      vi = vertex_index[n];
      if ( vi < 0 || vi >= mesh_vcount )
        continue;
      top_vi = topv_map[vi];
      if ( top_vi < 0 || top_vi > top_vcount )
        continue;
      edge_ends.i = vi;
      const ON_MeshTopologyVertex& v = m_top.m_topv[top_vi];
      for ( vei = 0; vei < v.m_tope_count; vei++ )
      {
        ei = v.m_topei[vei];
        if ( ei < 0 || ei >= top_ecount )
          continue;
        const ON_MeshTopologyEdge& e = m_top.m_tope[ei];
        for ( efi = 0; efi < e.m_topf_count; efi++ )
        {
          fi = e.m_topfi[efi];
          if ( fi < 0 || fi >= mesh_fcount )
            continue;
          f_vi = f[fi].vi;
          for ( fvi = 0; fvi < 4; fvi++ )
          {
            if ( f_vi[fvi] == vi )
            {
              j = f_vi[(fvi+3)%4];
              if ( j >= 0 && j < mesh_vcount && vi != j )
              {
                edge_ends.i = j;
                edge_ends.j = vi;
                edges.Append(edge_ends);
              }
              j = f_vi[ (2==fvi && f_vi[2]==f_vi[3]) ? 0 : ((fvi+1)%4) ];
              if ( j >= 0 && j < mesh_vcount && vi != j )
              {
                edge_ends.i = vi;
                edge_ends.j = j;
                edges.Append(edge_ends);
              }
              break; // done with this face
            }
          }
        }
      }
    }
  }
  else
  {
    // slow-n-stupid search through all the faces

    // Sort vertex_index[] array so we can use a quick
    // binary search to see if a face is using one of 
    // the vertices in the list.
    ON_Workspace ws;
    for ( vi = 1; vi < vertex_index_count; vi++ )
    {
      if ( vertex_index[vi] < vertex_index[vi-1] )
      {
        // need to sort vertex_index[] array
        int* tmp = ws.GetIntMemory(vertex_index_count);
        memcpy(tmp,vertex_index,vertex_index_count*sizeof(tmp[0]));
        ON_SortIntArray(ON::sort_algorithm::quick_sort,tmp,vertex_index_count);
        vertex_index = tmp;
        break;
      }
    }

    // Find all the faces that use a vertex in the vertex_index[] array.
    for ( fi = 0; fi < mesh_fcount; fi++ )
    {
      f_vi = f[fi].vi;
      for ( fvi = 0; fvi < 4; fvi++ )
      {
        vi = f_vi[fvi];
        if ( ON_BinarySearchIntArray(vi,vertex_index,vertex_index_count) )
        {
          // vi is in the vertex_index[] array.  Add the edges
          // of this face that begin and end at this vertex.
          j = f_vi[(fvi+3)%4];
          if ( j >= 0 && j < mesh_vcount && vi != j )
          {
            edge_ends.i = j;
            edge_ends.j = vi;
            edges.Append(edge_ends);
          }
          j = f_vi[ (2==fvi && f_vi[2]==f_vi[3]) ? 0 : ((fvi+1)%4) ];
          if ( j >= 0 && j < mesh_vcount && vi != j )
          {
            edge_ends.i = vi;
            edge_ends.j = j;
            edges.Append(edge_ends);
          }
        }
      }
    }
  }

  if ( bNoDuplicates && edges.Count() > edges_count0 )
  {
    for ( ei = edges_count0; ei < edges.Count(); ei++ )
    {
      edge_ends = edges[ei];
      if ( edge_ends.i > edge_ends.j )
      {
        j = edge_ends.i; edge_ends.i = edge_ends.j; edge_ends.j = j;
        edges[ei] = edge_ends;
      }
    }
    ON_qsort( edges.Array() + edges_count0,
              edges.Count() - edges_count0,
              sizeof(edge_ends), 
              ON_MeshGetVertexEdges_Compare2dex);
    edge_ends = edges[edges_count0];
    for ( ei = j = edges_count0+1; ei < edges.Count(); ei++ )
    {
      if ( ON_Compare2dex(&edge_ends,&edges[ei]) )
      {
        edge_ends = edges[ei];
        if ( j != ei )
          edges[j] = edge_ends;
        j++;
      }
    }
    edges.SetCount(j);
  }

  return (edges.Count() - edges_count0);
}

int ON_Mesh::GetMeshEdges( 
  ON_SimpleArray<ON_2dex>& edges
  ) const
{
  const int edges_count0 = edges.Count();
  int fi, ei, j, fvi;
  const int* f_vi;
  const ON_MeshFace* f = m_F.Array();
  const int mesh_vcount = m_V.Count();
  const int mesh_fcount = m_F.Count();
  edges.Reserve( edges_count0 + 4*mesh_fcount );
  ON_2dex e;

  // Find all the faces that use a vertex in the vertex_index[] array.
  for ( fi = 0; fi < mesh_fcount; fi++ )
  {
    f_vi = f[fi].vi;
    ei = f_vi[3];
    for ( fvi = 0; fvi < 4; fvi++ )
    {
      e.i = ei;
      ei = *f_vi++;
      e.j = ei;
      if ( e.i > e.j )
      {
        j = e.i; e.i = e.j; e.j = j;
      }
      if ( e.i != e.j && e.i >= 0 && e.j < mesh_vcount )
      {
        edges.Append(e);
      }
    }
  }
  

  if ( edges.Count() > edges_count0 )
  {
    ON_qsort( edges.Array() + edges_count0,
              edges.Count() - edges_count0,
              sizeof(e), 
              ON_MeshGetVertexEdges_Compare2dex);
    e = edges[edges_count0];
    for ( ei = j = edges_count0+1; ei < edges.Count(); ei++ )
    {
      if ( ON_Compare2dex(&e,&edges[ei]) )
      {
        e = edges[ei];
        if ( j != ei )
          edges[j] = e;
        j++;
      }
    }
    edges.SetCount(j);
  }

  return edges.Count() - edges_count0;
}


int ON_Mesh::SolidOrientation() const
{

  if ( m_mesh_is_solid <= 0 || m_mesh_is_solid > 3 )
  {
    // NOTE: calling IsClosed() will set m_mesh_is_solid
    //       to 3 if mes is non-manifold
    if ( IsSolid() )
    {
    }
  }

  switch(m_mesh_is_solid)
  {
  case 1:
    return 1;
    break;

  case 2:
    return -1;
    break;

  case 3:
    return 0;
    break;
  }

  return 0; // answer "no" if we don't know.
}


bool ON_Mesh::IsPointInside(
        ON_3dPoint test_point, 
        double tolerance,
        bool bStrictlyInside
        ) const
{
  if ( IsSolid() )
  {
  }
  return false;
}

bool ON_Mesh::IsSolid() const
{
  return ( IsClosed() && IsManifold() && IsOriented() );
}


bool ON_Mesh::IsManifold(
  bool bTopologicalTest,
  bool* pbIsOriented,
  bool* pbHasBoundary
  ) const
{
  bool bIsManifold = false;
  if ( pbIsOriented )
    *pbIsOriented = false;
  if ( pbHasBoundary )
    *pbHasBoundary = false;
  const int vcount = m_V.Count();
  const int fcount = m_F.Count();
  if ( vcount > 0 && fcount > 0 )
  {
    ON_Workspace ws;
    ON_3dex e;
    int i, j, ecount;
    const int* fvi;
    ON_3fPoint v0;
    const ON_3fPoint* v;
    const ON_MeshFace* f;
    int* vid = ws.GetIntMemory(vcount);
    ON_3dex* edge = (ON_3dex*)ws.GetMemory(4*fcount*sizeof(*edge));

    if ( bTopologicalTest )
    {
      // coincident vertices are assigned the same vertex id
      ON_Sort(ON::sort_algorithm::quick_sort,vid,m_V.Array(),vcount,sizeof(m_V[0]), ON_MeshIsManifold_Compare3floats);
      ecount = 0;
      v = m_V.Array();
      ecount = 0;
      j = vcount;
      for ( i = 0; i < vcount; i = j)
      {
        v0 = v[vid[i]];
        vid[i] = ecount;
        for ( j = i+1; j < vcount; j++ )
        {
          if (ON_MeshIsManifold_Compare3floats(v0,v+vid[j]) )
          {
            ecount++;
            break;
          }
          vid[j] = ecount;
        }
      }
    }
    else
    {
      // each vertex gets a unique id.
      for ( i = 0; i < vcount; i++ )
        vid[i] = i;
    }

    // build a list of edges
    f = m_F.Array();
    ecount = 0;
    for ( i = 0; i < fcount; i++ )
    {
      fvi = (f++)->vi;
      if (   fvi[0] >= 0 && fvi[0] < vcount 
          && fvi[1] >= 0 && fvi[1] < vcount
          && fvi[2] >= 0 && fvi[2] < vcount
          && fvi[3] >= 0 && fvi[3] < vcount )
      {
        // loop unrolled for speed
        j = ecount;
        e.i = vid[fvi[0]];  e.j = vid[fvi[1]];
        if ( 0 != (e.k = e.j - e.i) )
        {
          if ( e.k < 0 ) {e.k = e.i; e.i = e.j; e.j = e.k; e.k = 1;} else e.k = 0;
          edge[ecount++] = e;
        }
        e.i = vid[fvi[1]];  e.j = vid[fvi[2]];
        if ( 0 != (e.k = e.j - e.i) )
        {
          if ( e.k < 0 ) {e.k = e.i; e.i = e.j; e.j = e.k; e.k = 1;} else e.k = 0;
          edge[ecount++] = e;
        }
        e.i = vid[fvi[2]];  e.j = vid[fvi[3]];
        if ( 0 != (e.k = e.j - e.i) )
        {
          if ( e.k < 0 ) {e.k = e.i; e.i = e.j; e.j = e.k; e.k = 1;} else e.k = 0;
          edge[ecount++] = e;
        }
        e.i = vid[fvi[3]];  e.j = vid[fvi[0]];
        if ( 0 != (e.k = e.j - e.i) )
        {
          if ( e.k < 0 ) {e.k = e.i; e.i = e.j; e.j = e.k; e.k = 1;} else e.k = 0;
          edge[ecount++] = e;
        }
        if ( ecount < j+3 )
          ecount = j;
      }
    }

    if ( ecount >= 4 )
    {
      bIsManifold = true;
      bool bIsOriented  = (pbIsOriented)  ? true  : false;
      bool bHasBoundary = (pbHasBoundary) ? false : true;
      ON_qsort(edge,ecount,sizeof(edge[0]),ON_MeshIsManifold_Compare3dex);

      i = 0;
      e = *edge;
      while ( --ecount )
      {
        edge++;
        if ( memcmp(&e,edge,2*sizeof(int)) )
        {
          if (!i)
            bHasBoundary = true;
          e = *edge;
          i = 0;
        }
        else
        {
          if ( i++ )
          {
            bIsManifold = false;
            break;
          }
          if ( e.k == edge->k )
            bIsOriented = false;
        }
      }

      if ( bIsManifold )
      {
        if ( pbIsOriented )
          *pbIsOriented = bIsOriented;
        if ( pbHasBoundary )
          *pbHasBoundary = bHasBoundary;
      }
    }
  }

  return bIsManifold;
}

static void ON_hsort_3udex(ON_3udex *e, size_t nel)
{
  // dictionary sort e[]
  size_t i_end, k, i, j;
  ON_3udex e_tmp;

  if (nel < 2) return;
  k = nel >> 1;
  i_end = nel - 1;
  for (;;)
  {
    if (k)
    {
      --k;
      e_tmp = e[k];
    }
    else
    {
      e_tmp = e[i_end];
      e[i_end] = e[0];
      if (!(--i_end))
      {
        e[0] = e_tmp;
        break;
      }
    }
    i = k;
    j = (k << 1) + 1;
    while (j <= i_end)
    {
      if (j < i_end && (e[j].i < e[j + 1].i || (e[j].i == e[j + 1].i && (e[j].j < e[j + 1].j || (e[j].j == e[j + 1].j && e[j].k < e[j + 1].k)))))
        j++;

      if (e_tmp.i < e[j].i || (e_tmp.i == e[j].i && (e_tmp.j < e[j].j || (e_tmp.j == e[j].j && e_tmp.k < e[j].k))))
      {
        e[i] = e[j];
        i = j;
        j = (j << 1) + 1;
      }
      else
        j = i_end + 1;
    }
    e[i] = e_tmp;
  }
}

static void ON_Mesh_SetClosedHelper( 
          bool bClosedOnly,
          const ON_Mesh& mesh,
          const char& m_mesh_is_manifold,
          const char& m_mesh_is_oriented
          )
{
  // thread safe lazy evaluation for mesh's m_mesh_is_... flags
  // Sets: m_mesh_is_closed.
  //       If bClosedOnly is false, also sets m_mesh_is_manifold and m_mesh_is_oriented
  int is_closed = 0;
  char is_manifold = 2;
  char is_oriented = 2;
  for (;;)
  {
    const unsigned int Vcount = mesh.m_V.UnsignedCount();
    const unsigned int Fcount = mesh.m_F.UnsignedCount();
    if ( Vcount < 3 || Fcount < 1 )
    {
      ON_ERROR("Mesh is not valid.");
      break;
    }
    if ( bClosedOnly && (Vcount < 4 || Fcount < 4) )
    {
      // not closed - don't waste any more time.
      break;
    }

    unsigned int i, j;
    unsigned int Vidbuffer[256];
    unsigned int* Vid = mesh.GetVertexLocationIds(
                     1,
                     (Vcount*sizeof(*Vid) <= sizeof(Vidbuffer) ? &Vidbuffer[0] : nullptr),
                     nullptr // unwanted Vindex[] values
                    );
    if ( 0 == Vid )
    {
      ON_ERROR("Mesh has corrupt vertex information.");
      bClosedOnly = false;
      break;
    }

    // build an edge list where the "vertex" indices identify unique 3d locations
    ON_3udex* E_list = (ON_3udex*)onmalloc(4 * Fcount*sizeof(E_list[0]));
    ON_3udex E;
    unsigned int Vid0;
    const int* fvi;
    unsigned int E_count = 0;
    const ON_MeshFace* F = mesh.m_F.Array();
    for ( j = 0; j < Fcount; j++ )
    {
      fvi = F[j].vi;
      E.i = Vid[fvi[0]];
      Vid0 = E.j = Vid[fvi[1]];
      if ( E.i == E.j )
        break;
      if ( E.i > E.j )
      {
        i = E.i; E.i = E.j; E.j = i;
        E.k = 1;
      }
      else
      {
        E.k = 0;
      }
      E_list[E_count++] = E;

      E.i = Vid0;
      Vid0 = E.j = Vid[fvi[2]];
      if ( E.i == E.j )
        break;
      if ( E.i > E.j )
      {
        i = E.i; E.i = E.j; E.j = i;
        E.k = 1;
      }
      else
      {
        E.k = 0;
      }
      E_list[E_count++] = E;

      if ( fvi[2] != fvi[3] )
      {
        // quad
        E.i = Vid0;
        Vid0 = E.j = Vid[fvi[3]];
        if ( E.i == E.j )
          break;
        if ( E.i > E.j )
        {
          i = E.i; E.i = E.j; E.j = i;
          E.k = 1;
        }
        else
        {
          E.k = 0;
        }
        E_list[E_count++] = E;
      }

      E.i = Vid0;
      E.j = Vid[fvi[0]];
      if ( E.i == E.j )
        break;
      if ( E.i > E.j )
      {
        i = E.i; E.i = E.j; E.j = i;
        E.k = 1;
      }
      else
      {
        E.k = 0;
      }
      E_list[E_count++] = E;
    }
    if ( Vid != &Vidbuffer[0] )
      onfree(Vid);

    if ( E_count < 3 || j != Fcount )
    {
      ON_ERROR("Mesh is corrupt or collapsed");
      bClosedOnly = false;
      break;
    }

    // sort the the edges
    ON_hsort_3udex(E_list,E_count);

    // Look for duplicate edges.  If we find an edge with no duplicate,
    // then the mesh is open.  It is possible that degenerate meshes,
    // like a flattened box, will be flagged as closed.
    is_closed = (Fcount >= 4 && E_count >= 6) ? 1 : 0;
    is_oriented = 1;
    is_manifold = 1;
    i = 0;
    if ( !bClosedOnly || 1 == is_closed ) for ( i = 0; i < E_count; /*empty iterator*/ )
    {
      E = E_list[i];
      if ( ++i >= E_count )
      {
        // boundary edge (and the last edge in our list)
        is_closed = 0;
        break;
      }

      if ( E.i != E_list[i].i || E.j != E_list[i].j )
      {
        // boundary edge
        is_closed = 0;
        if ( 2 == is_oriented && 2 == is_manifold )
        {
          bClosedOnly = false;
          break;
        }
        if ( bClosedOnly )
          break; // don't spend time with further testing
        continue;
      }

      if ( E.k == E_list[i].k )
      {
        // opposite face normals along this edge - mesh is not oriented
        is_oriented = 2; 
      }

      if ( ++i >= E_count || E.i != E_list[i].i || E.j != E_list[i].j )
      {
        // two faces share this edge
        continue;
      }

      // three or more faces share this edge - mesh is not oriented manifold
      is_oriented = 2; 
      is_manifold = 2; 
      if ( 0 == is_closed )
      {
        bClosedOnly = false;
        break;
      }

      // Check for more faces sharing this edge.
      for ( i++; i < E_count; i++ )
      {
        if ( E.i != E_list[i].i || E.j != E_list[i].j )
        {
          // the edges E and Eid_list[i] are in different locations
          break;
        }
      }
    }
    if (E_count > 0 && i >= E_count)
    {
      // is_manifold and is_oriented are set correctly
      bClosedOnly = false;
    }

    onfree(E_list);

    break;
  }

  const_cast<ON_Mesh&>(mesh).SetClosed(is_closed);
  if ( !bClosedOnly )
  {
    // is_manifold and is_oriented are set correctly
    if ( 2 == is_manifold )
      is_oriented = 2;
    const_cast<char&>(m_mesh_is_manifold) = is_manifold;
    const_cast<char&>(m_mesh_is_oriented) = is_oriented;
  }
}

bool ON_Mesh::IsClosed() const
{
  if ( m_mesh_is_closed <= 0 || m_mesh_is_closed > 2) 
  {
    // thread safe lazy evaluation
    ON_Mesh_SetClosedHelper( true, *this, m_mesh_is_manifold, m_mesh_is_oriented );
  }

  return (1 == m_mesh_is_closed);
}

bool ON_Mesh::IsManifold() const
{
  if ( m_mesh_is_manifold <= 0 || m_mesh_is_manifold > 2 )
  {
    // thread safe lazy evaluation
    ON_Mesh_SetClosedHelper( false, *this, m_mesh_is_manifold, m_mesh_is_oriented );
  }
  return (1 == m_mesh_is_manifold);
}

bool ON_Mesh::IsOriented() const
{
  if ( m_mesh_is_oriented <= 0 || m_mesh_is_oriented > 2 )
  {
    // thread safe lazy evaluation
    ON_Mesh_SetClosedHelper( false, *this, m_mesh_is_manifold, m_mesh_is_oriented );
  }
  return (1 == m_mesh_is_oriented);
}


/*
Returns
  true if there are zero vertices and zero faces.
*/
bool ON_Mesh::IsEmpty() const
{
  // Deep sigh.  
  // The "this == &ON_Mesh::Empty" check is to handle the case when 
  // confused developers const cast ON_Mesh::Empty and then modify it.
  return (0 == VertexUnsignedCount() && 0 == FaceUnsignedCount()) || (this == &ON_Mesh::Empty);
}

bool ON_Mesh::IsNotEmpty() const
{
  // Deep sigh.  
  // The "this != &ON_Mesh::Empty" check is to handle the case when 
  // confused developers const cast ON_Mesh::Empty and then modify it.
  return ( VertexUnsignedCount() > 0 && FaceUnsignedCount() > 0 && this != &ON_Mesh::Empty);
}

bool ON_Mesh::SetVertex(
       int vertex_index,
       const ON_3dPoint& vertex_location
       )
{
  const unsigned int vertex_count = VertexUnsignedCount();
  const bool rc = vertex_index >= 0 && ((unsigned int)vertex_index) <= vertex_count;
  if ( rc )
  {
    const unsigned int i = (unsigned int)vertex_index;
    if ( vertex_count == m_dV.UnsignedCount() )
    {
      if ( i < vertex_count ) 
        m_dV[i] = vertex_location;
      else
        m_dV.Append(vertex_location);
    }
    if ( vertex_count == m_V.UnsignedCount() )
    {
      if ( i < vertex_count ) 
        m_V[i] = vertex_location;
      else
        m_V.AppendNew() = ON_3fPoint(vertex_location);
    }
  }
  return rc;
}

bool ON_Mesh::SetVertex(
       int vertex_index,
       const ON_3fPoint& vertex_location
       )
{
  const unsigned int vertex_count = VertexUnsignedCount();
  const bool rc = vertex_index >= 0 && ((unsigned int)vertex_index) <= vertex_count;
  if ( rc )
  {
    const unsigned int i = (unsigned int)vertex_index;
    if ( vertex_count == m_dV.UnsignedCount() )
    {
      if ( i < vertex_count ) 
        m_dV[i] = vertex_location;
      else
        m_dV.Append(vertex_location);
    }
    if ( vertex_count == m_V.UnsignedCount() )
    {
      if ( i < vertex_count ) 
        m_V[i] = vertex_location;
      else
        m_V.Append(vertex_location);
    }
  }
  return rc;
}

bool ON_Mesh::SetVertexNormal(
       int vertex_index,
       const ON_3dVector& normal
       )
{
  bool rc = false;
  // use double precision for unitizing normal
  ON_3dVector unit_vector = normal;
  const bool bUnitVector = unit_vector.Unitize();
  ON_3fVector v((float)unit_vector.x, (float)unit_vector.y, (float)unit_vector.z);
  int normal_count = m_N.Count();
  if ( vertex_index >= 0 ) {
    if ( vertex_index < normal_count ) {
      m_N[vertex_index] = v;
      rc = bUnitVector;
    }
    else if ( vertex_index == normal_count ) {
      m_N.Append(v);
      rc = bUnitVector;
    }
  }
  return rc;
}

bool ON_Mesh::SetVertexNormal(
       int vertex_index,
       const ON_3fVector& normal
       )
{
  ON_3dVector v(normal.x,normal.y,normal.z);
  return SetVertexNormal(vertex_index,v);
}

bool ON_Mesh::SetTextureCoord(
       int vertex_index,
       double s, double t    // texture coordinates
       )
{
  ON_2fPoint tc((float)s,(float)t);
  bool rc = false;
  int vertex_count = m_T.Count();
  if ( vertex_index >= 0 ) {
    if ( vertex_index < vertex_count ) {
      m_T[vertex_index] = tc;
      rc = true;
    }
    else if ( vertex_index == vertex_count ) {
      m_T.Append(tc);
      rc = true;
    }
  }
  return rc;
}


unsigned int ON_Mesh::AppendDuplicateVertex(
  unsigned int vertex_index
  )
{
  const unsigned int vertex_count = VertexUnsignedCount();

  if ( vertex_index >= vertex_count )
    return ON_UNSET_UINT_INDEX;
  
  if (vertex_count == m_V.UnsignedCount())
  {
    ON_3fPoint V = m_V[vertex_index];
    m_V.Append(V);
  }

  if ( vertex_count == m_dV.UnsignedCount())
  {
    ON_3dPoint D = m_dV[vertex_index];
    m_dV.Append(D);
  }

  if ( vertex_count == m_N.UnsignedCount() )
  {
    ON_3fVector N = m_N[vertex_index];
    m_N.Append(N);
  }

  if ( vertex_count == m_T.UnsignedCount() )
  {
    ON_2fPoint T = m_T[vertex_index];
    m_T.Append(T);
  }

  if ( vertex_count == m_S.UnsignedCount() )
  {
    ON_2dPoint S = m_S[vertex_index];
    m_S.Append(S);
  }

  if ( vertex_count == m_K.UnsignedCount() )
  {
    ON_SurfaceCurvature K = m_K[vertex_index];
    m_K.Append(K);
  }

  if ( vertex_count == m_C.UnsignedCount() )
  {
    ON_Color C = m_C[vertex_index];
    m_C.Append(C);
  }

  if ( vertex_count == m_H.UnsignedCount() )
  {
    bool H = m_H[vertex_index];
    m_H.Append(H);
  }

  return vertex_count;
}

/*
Description:
  Increases the capacity of arrays to be at least the requested capacity.
Parameters:
  new_vertex_capacity - [in]
    desired capacity
Returns:
  true if successful.
Remarks:
  This function is useful if you are getting ready to add a known number
  of vertices and want to increase the dynamic array capacities before
  you begin adding vertices.
*/  
bool ON_Mesh::ReserveVertexCapacity(
  size_t new_vertex_capacity
  )
{
  const unsigned int vertex_count = VertexUnsignedCount();
  if ( new_vertex_capacity <= (size_t)vertex_count )
    return true;
  
  if ( vertex_count == m_V.UnsignedCount() )
    m_V.Reserve(new_vertex_capacity);

  if ( vertex_count == m_dV.UnsignedCount() )
    m_dV.Reserve(new_vertex_capacity);

  if ( vertex_count == m_N.UnsignedCount() )
    m_N.Reserve(new_vertex_capacity);

  if ( vertex_count == m_T.UnsignedCount() )
    m_T.Reserve(new_vertex_capacity);

  if ( vertex_count == m_S.UnsignedCount() )
    m_S.Reserve(new_vertex_capacity);

  if ( vertex_count == m_K.UnsignedCount() )
    m_K.Reserve(new_vertex_capacity);

  if ( vertex_count == m_C.UnsignedCount() )
    m_C.Reserve(new_vertex_capacity);

  if ( vertex_count == m_H.UnsignedCount() )
    m_H.Reserve(new_vertex_capacity);

  return true;
}


bool ON_Mesh::SetTriangle(
       int face_index,
       int a,int b ,int c // vertex indices
       )
{
  return SetQuad( face_index, a,b,c,c );
}

bool ON_Mesh::SetQuad(
       int face_index,
       int a, int b, int c, int d // vertex indices
       )
{
  bool rc = false;
  int face_count = m_F.Count();
  if ( face_index >= 0 ) {
    ON_MeshFace f;
    f.vi[0] = a;
    f.vi[1] = b;
    f.vi[2] = c;
    f.vi[3] = d;
    if ( face_index < face_count ) {
      m_F[face_index] = f;
      rc = true;
    }
    else if ( face_index == face_count ) {
      m_F.Append(f);
      rc = true;
    }
    if ( rc )
      rc = f.IsValid(m_V.Count());
  }
  return rc;
}



int ON_Mesh::FaceCount() const
{
  return m_F.Count();
}

unsigned int ON_Mesh::FaceUnsignedCount() const
{
  return m_F.UnsignedCount();
}

int ON_Mesh::QuadCount() const
{
  // number of faces that are quads
  if (   m_quad_count     < 0
      || m_triangle_count < 0 
      || m_invalid_count  < 0 
      || m_quad_count + m_triangle_count + m_invalid_count != FaceCount() ) 
  {
    const_cast<ON_Mesh*>(this)->CountQuads();
  }
  return m_quad_count;
}

int ON_Mesh::TriangleCount() const
{
  // number of faces that are triangles
  QuadCount(); // makes sure counts are valid
  return m_triangle_count;
}

int ON_Mesh::InvalidFaceCount() const
{
  // number of faces that are invalid
  QuadCount(); // makes sure counts are valid
  return m_invalid_count;
}


int ON_Mesh::VertexCount() const
{
  // When m_V becomes obsolete, this will return m_dV.Count().
  return m_V.Count();
}

unsigned int ON_Mesh::VertexUnsignedCount() const
{
  // When m_V becomes obsolete, this will return m_dV.UnsignedCount().
  return m_V.UnsignedCount();
}

bool ON_Mesh::HasNgons() const
{
  return ( m_F.Count() > 0 && m_Ngon.Count() );
}

bool ON_Mesh::HasVertexNormals() const
{
  const int vertex_count = VertexCount();
  return ( vertex_count > 0 && m_N.Count() == vertex_count ) ? true : false;
}

bool ON_Mesh::HasFaceNormals() const
{
  const int face_count = FaceCount();
  return ( face_count > 0 && m_FN.Count() == face_count ) ? true : false;
}

bool ON_Mesh::HasTextureCoordinates() const
{
  const int vertex_count = VertexCount();
  return ( vertex_count > 0 && m_T.Count() == vertex_count ) ? true : false;
}

bool ON_Mesh::HasCachedTextureCoordinates() const
{
  const int vertex_count = VertexCount();
  if (vertex_count > 0 )
  {
    int tci, tccount = m_TC.Count();
    for ( tci = 0; tci < tccount; tci++ )
    {
      if ( vertex_count == m_TC[tci].m_T.Count() )
        return true;
    }
  }
  return false;
}

// Note: We are exporting this function for use in CRhinoObject::SetCachedTextureCoordinatesFromPlugIn
ON_DECL bool ON_Mesh_Private_CacheMappingChannel(std::function<ON_TextureMapping(const ON_MappingChannel*)> get_mapping_func, const ON_MappingChannel* pMC, const ON_SimpleArray<ON_TextureMapping::TYPE>& mappings_to_cache, const int mapping_channel_id, std::unordered_map<unsigned int, ON_TextureMapping>& mapInOut)
{
  const bool cache_all = (mappings_to_cache.Count() == 0);
  
  if (nullptr == pMC)
  {
    const ON_TextureMapping& srfp_mapping = ON_TextureMapping::SurfaceParameterTextureMapping;
    if(cache_all || mappings_to_cache.Search(srfp_mapping.m_type) >= 0)
    {
      // If the mapping channel is null, then we can assume that the textures implicitly
      // reference the surface parameter mapping.
      // This is done according to the documentation for ON_Texture::m_mapping_channel_id.
      mapInOut[mapping_channel_id] = srfp_mapping;
    }
  }
  else
  {
    ON_TextureMapping mapping = get_mapping_func(pMC);

    if (mapping.m_type != ON_TextureMapping::TYPE::no_mapping)
    {
      // How to handle ON_TextureMapping::TYPE::ocs_mapping
      // and ON_TextureMapping::TYPE::false_colors ?
      if(cache_all || mappings_to_cache.Search(mapping.m_type) >= 0)
      {
        mapInOut[mapping_channel_id] = mapping;
      }
    }
  }

  return true;
}

// Note: We are exporting this function for use in CRhinoObject::SetCachedTextureCoordinatesFromPlugIn
ON_DECL bool ON_Mesh_Private_AddPerVertexMappingChannels(std::function<ON_TextureMapping(const ON_MappingChannel*)> get_texture_mapping_func, const ON_MappingRef* mapping_ref, const ON_SimpleArray<ON_TextureMapping::TYPE>& mappings_to_cache, const ON_Material& material, std::unordered_map<unsigned int, ON_TextureMapping>& mappings)
{
  for (int i = 0; i < material.m_textures.Count(); i++)
  {
    if (material.m_textures[i].m_bOn)
    {
      // Get mapping channel id and check if mapping already is in the map
      const unsigned int mapping_channel_id = material.m_textures[i].m_mapping_channel_id;
      if (mappings.find(mapping_channel_id) == mappings.end())
      {
        const ON_MappingChannel* mapping_channel = nullptr;
        if (mapping_ref)
        {
          // Get texture mapping and add it to the map
          mapping_channel = mapping_ref->MappingChannel(mapping_channel_id);
          if (mapping_channel == nullptr)
          {
            // If a mapping channel is not found using 'mapping_channel_id', then try with a mapping channel id of 1.
            // This is done according to the documentation for ON_Texture::m_mapping_channel_id.
            mapping_channel = mapping_ref->MappingChannel(1);
          }
        }

        if (!ON_Mesh_Private_CacheMappingChannel(get_texture_mapping_func, mapping_channel, mappings_to_cache, mapping_channel_id, mappings))
          return false;
      }
    }
  }

  // If we didn't cache any texture coordinates above, but we have a material with anisotropy,
  // which requires tangents, which in turn requires texture coordinates, then we cache
  // the texture coordinates from mapping channel 1.
  if (mappings.size() == 0)
  {
    if (material.IsPhysicallyBased() && material.PhysicallyBased()->Anisotropic() > 0.0)
    {
      const ON_MappingChannel* mapping_channel = mapping_ref ? mapping_ref->MappingChannel(1) : nullptr;

      if (!ON_Mesh_Private_CacheMappingChannel(get_texture_mapping_func, mapping_channel, mappings_to_cache, 1, mappings))
        return false;
    }
  }

  return true;
}

// Note: We are exporting this function for use in CRhinoObject::SetCachedTextureCoordinatesFromPlugIn
ON_DECL bool ON_Mesh_Private_SetCachedTextureCoordinatesFromMaterial(ON_SimpleArray<const ON_Mesh*>& meshes, std::unordered_map<unsigned int, ON_TextureMapping>& per_vertex_channels, const ON_MappingRef* mapping_ref, bool perform_cleanup, std::shared_ptr<class CRhVboData>* vbo_data)
{
  ON_ClassArray<ON_SimpleArray<int>> indices_to_preserve;
  indices_to_preserve.SetCapacity(meshes.Count());
  indices_to_preserve.SetCount(meshes.Count());

  // Set cached texture coordinates for each mapping on the map for every render mesh
  for (auto pvcit = per_vertex_channels.begin(); pvcit != per_vertex_channels.end(); pvcit++)
  {
    const unsigned int mapping_channel_id = pvcit->first;
    const ON_TextureMapping& mapping = pvcit->second;

    // Get object mapping transformation
    const ON_MappingChannel* pMC = mapping_ref ? mapping_ref->MappingChannel(mapping_channel_id) : nullptr;

    const ON_Xform* pObjectXform = (pMC == nullptr || pMC->m_object_xform.IsIdentity() || pMC->m_object_xform.IsZero()) ? nullptr : &pMC->m_object_xform;

    // Set cached texture coordinates for each of the render meshes
    for (int mi = 0; mi < meshes.Count(); mi++)
    {
      // Const cast render mesh and set texture coordinates
      ON_Mesh* pMesh = const_cast<ON_Mesh*>(meshes[mi]);
      if (nullptr != pMesh)
      {
        bool has_matching_cached_tcs = false;
        for (int i = 0; i < pMesh->m_TC.Count(); i++)
        {
          if (pMesh->VertexCount() == pMesh->m_TC[i].m_T.Count() && mapping.HasMatchingTextureCoordinates(pMesh->m_TC[i].m_tag, pObjectXform))
          {
            indices_to_preserve[mi].Append(i);
            has_matching_cached_tcs = true;
            break;
          }
        }

        if (!has_matching_cached_tcs)
        {
          indices_to_preserve[mi].Append(pMesh->m_TC.Count());

          const ON_TextureCoordinates* pTC = pMesh->SetCachedTextureCoordinatesEx(mapping, pObjectXform, true, false);
          
          if(pTC && vbo_data)
            vbo_data->reset();
        }
      }
    }
  }

  if(perform_cleanup)
  {
    for (int mi = 0; mi < meshes.Count(); mi++)
    {
      ON_Mesh* pMesh = const_cast<ON_Mesh*>(meshes[mi]);
      if (nullptr != pMesh)
      {
        const int tc_count = pMesh->m_TC.Count();
        if (tc_count > per_vertex_channels.size())
        {
          int wcs_mapping_count = 0;
          int wcs_box_mapping_count = 0;
          ON_SimpleArray<int> indices_to_remove;
          
          for (int tci = tc_count - 1; tci >= 0; tci--)
          {
            if (indices_to_preserve[mi].Search(tci) == -1)
            {
              ON_TextureMapping::TYPE mapping_type = pMesh->m_TC[tci].m_tag.m_mapping_type;
              bool remove_index = true;
              
              // Only clean up WCS and WCS Box mappings if there exist more recent versions
              // in the array. They are considered more recent if they appear later in the array.
              if(mapping_type == ON_TextureMapping::TYPE::wcs_projection && wcs_mapping_count++ == 0)
              {
                remove_index = false; // Don't remove first one we find
              }
              else if(mapping_type == ON_TextureMapping::TYPE::wcsbox_projection && wcs_box_mapping_count++ == 0)
              {
                remove_index = false;  // Don't remove first one we find
              }
              
              if(remove_index)
                indices_to_remove.Append(tci);
            }
          }
          
          for (int tci = indices_to_remove.Count() - 1; tci >= 0; tci--)
            pMesh->m_TC.Remove(indices_to_remove[tci]);
          
          if(vbo_data && indices_to_remove.Count() > 0)
            vbo_data->reset();
        }
      }
    }
  }
  
  return true;
}

static ON_UUID WcsMappingId(const ON_Xform& ocsTransform, bool bBox)
{
  // {47D62129-341E-4E3D-BF11-9C051AF4ED98}
  static const ON_UUID uuidBaseWcs =
  { 0x47d62129, 0x341e, 0x4e3d, { 0xbf, 0x11, 0x9c, 0x5, 0x1a, 0xf4, 0xed, 0x98 } };

  // {4DC9AA78-9617-46FB-923F-3E65E14182FC}
  static const ON_UUID uuidBaseWcsBox =
  { 0x4dc9aa78, 0x9617, 0x46fb, { 0x92, 0x3f, 0x3e, 0x65, 0xe1, 0x41, 0x82, 0xfc } };

  ON_UUID uuid = bBox ? uuidBaseWcsBox : uuidBaseWcs;
  uuid.Data1 = ocsTransform.CRC32(uuid.Data1);
  return uuid;
}

static ON_Xform GetOcsTransform(std::function<ON_TextureMapping(const ON_MappingChannel*)> get_mapping_func, const ON_MappingRef* mapping_ref)
{
  ON_Xform ocsTransform = ON_Xform::IdentityTransformation;
  if (nullptr != mapping_ref)
  {
    const ON_MappingChannel* pMC = mapping_ref->MappingChannel(ON_ObjectRenderingAttributes::OCSMappingChannelId());
    if (nullptr != pMC)
    {
      const ON_TextureMapping tm = get_mapping_func(pMC);
      ON_Xform inverseObjectTransform = pMC->m_object_xform;
      if (inverseObjectTransform.Invert())
      {
        ocsTransform = tm.m_Pxyz * inverseObjectTransform;
      }
      else
      {
        ocsTransform = tm.m_Pxyz;
      }
    }
  }
  return ocsTransform;
}

static void CacheWcsProjections(const ON_Mesh& mesh, std::function<ON_TextureMapping(const ON_MappingChannel*)> get_mapping_func, const ON_Material& material, const ON_MappingRef* mapping_ref)
{
  bool bWcsProjectionNeeded = false;
  bool bWcsBoxProjectionNeeded = false;
  for (int ti = 0; ti < material.m_textures.Count(); ti++)
  {
    if (material.m_textures[ti].IsWcsProjected())
      bWcsProjectionNeeded = true;
    if (material.m_textures[ti].IsWcsBoxProjected())
      bWcsBoxProjectionNeeded = true;
  }

  if (bWcsProjectionNeeded)
  {
    const ON_Xform ocsTransform = GetOcsTransform(get_mapping_func, mapping_ref);
    const ON_UUID uuidWcsMapping = WcsMappingId(ocsTransform, false);
    ON_TextureMapping wcsMapping;
    wcsMapping.m_type = ON_TextureMapping::TYPE::wcs_projection;
    wcsMapping.SetId(uuidWcsMapping);
    wcsMapping.m_Pxyz = ocsTransform;
    if (!wcsMapping.HasMatchingCachedTextureCoordinates(mesh))
    {
      ON_TextureCoordinates& tcs = const_cast<ON_Mesh*>(&mesh)->m_TC.AppendNew();
      wcsMapping.GetTextureCoordinates(mesh, tcs.m_T);
      tcs.m_tag.Set(wcsMapping);
      tcs.m_tag.m_mesh_xform = ON_Xform::ZeroTransformation;
      tcs.m_dim = 2;
      return;
    }
  }
  if (bWcsBoxProjectionNeeded)
  {
    const ON_Xform ocsTransform = GetOcsTransform(get_mapping_func, mapping_ref);
    const ON_UUID uuidWcsBoxMapping = WcsMappingId(ocsTransform, true);
    ON_TextureMapping wcsBoxMapping;
    wcsBoxMapping.m_type = ON_TextureMapping::TYPE::wcsbox_projection;
    wcsBoxMapping.SetId(uuidWcsBoxMapping);
    wcsBoxMapping.m_Pxyz = ocsTransform;
    wcsBoxMapping.m_Pxyz.GetSurfaceNormalXform(wcsBoxMapping.m_Nxyz);
    if (!wcsBoxMapping.HasMatchingCachedTextureCoordinates(mesh))
    {
      ON_TextureCoordinates& tcs = const_cast<ON_Mesh*>(&mesh)->m_TC.AppendNew();
      wcsBoxMapping.GetTextureCoordinates(mesh, tcs.m_T);
      tcs.m_tag.Set(wcsBoxMapping);
      tcs.m_tag.m_mesh_xform = ON_Xform::ZeroTransformation;
      tcs.m_dim = 2;
      return;
    }
  }
}

bool SetCachedTextureCoordinatesFromMaterial(const ON_Mesh& mesh, std::function<ON_TextureMapping(const ON_MappingChannel*)> get_mapping_func, const ON_Material& material, const ON_MappingRef* mapping_ref, const ON_SimpleArray<ON_TextureMapping::TYPE>& mappings_to_cache, bool perform_cleanup)
{
  // Create a map of all texture mappings that require per-vertex texture coordinates
  std::unordered_map<unsigned int, ON_TextureMapping> per_vertex_channels;
  if (!ON_Mesh_Private_AddPerVertexMappingChannels(get_mapping_func, mapping_ref, mappings_to_cache, material, per_vertex_channels))
    return false;

  ON_SimpleArray<const ON_Mesh*> meshes;
  meshes.Append(&mesh);

  CacheWcsProjections(mesh, get_mapping_func, material, mapping_ref);

  return ON_Mesh_Private_SetCachedTextureCoordinatesFromMaterial(meshes, per_vertex_channels, mapping_ref, perform_cleanup, nullptr);
}

ON_DECL ON_TextureMapping ONX_Model_GetTextureMappingHelper(const ONX_Model& onx_model, const ON_MappingChannel* pMC)
{
  ON_TextureMapping mapping = ON_TextureMapping::SurfaceParameterTextureMapping;

  ONX_ModelComponentIterator it(onx_model, ON_ModelComponent::Type::TextureMapping);

  for (ON_ModelComponentReference cr = it.FirstComponentReference(); false == cr.IsEmpty(); cr = it.NextComponentReference())
  {
    const ON_TextureMapping* texture_mapping = ON_TextureMapping::Cast(cr.ModelComponent());
    if (nullptr == texture_mapping)
      continue;

    if (ON_UuidCompare(&texture_mapping->Id(), &pMC->m_mapping_id) == 0)
    {
      mapping = *texture_mapping;
      break;
    }
  }

  return mapping;
}

bool ON_Mesh::SetCachedTextureCoordinatesFromMaterial(const ONX_Model& onx_model, const ON_Material& material, const ON_MappingRef* mapping_ref) const
{
  auto get_mapping_func = [&onx_model](const ON_MappingChannel* pMC)
  {
    return ONX_Model_GetTextureMappingHelper(onx_model, pMC);
  };
  
  ON_SimpleArray<ON_TextureMapping::TYPE> mappings_to_cache;
  return ::SetCachedTextureCoordinatesFromMaterial(*this, get_mapping_func, material, mapping_ref, mappings_to_cache, false);
}

static const ON_TextureCoordinates* Internal_GetCachedTextureCoordinates(const ON_Mesh& mesh, std::function<ON_TextureMapping(const ON_MappingChannel*)> get_mapping_func, const ON_Texture& texture, const ON_MappingRef* mapping_ref)
{
  if (texture.IsWcsProjected() || texture.IsWcsBoxProjected())
  {
    const ON_Xform ocsTransform = GetOcsTransform(get_mapping_func, mapping_ref);
    const ON_UUID mappingId = WcsMappingId(ocsTransform, texture.IsWcsBoxProjected());
    const ON_TextureCoordinates* pTCs = mesh.CachedTextureCoordinates(mappingId);
    return pTCs;
  }
  else if (texture.m_mapping_channel_id >= 0)
  {
    if (nullptr != mapping_ref)
    {
      const ON_MappingChannel* pMC = mapping_ref->MappingChannel(texture.m_mapping_channel_id);
      if (nullptr != pMC)
      {
        const ON_TextureCoordinates* pTCs = mesh.CachedTextureCoordinates(pMC->m_mapping_id);
        // Probably best to not const cast and start setting the texture coordinates.
        // All previously returned pointers to the m_TC should be kept valid.
        //if (nullptr == pTCs)
        //{
        //  ON_TextureMapping mapping = get_mapping_func(pMC);
        //  pTCs = const_cast<ON_Mesh*>(this)->SetCachedTextureCoordinatesEx(mapping, &pMC->m_object_xform, true, false);
        //}
        return pTCs;
      }
    }
    else
    {
      // Return surface parameter mapping if there is nothing else
      const ON_TextureCoordinates* pTCs = mesh.CachedTextureCoordinates(ON_TextureMapping::SurfaceParameterTextureMappingId);
      return pTCs;
    }
  }
  return nullptr;
}

const ON_TextureCoordinates* ON_Mesh::GetCachedTextureCoordinates(const ONX_Model& onx_model, const ON_Texture& texture, const ON_MappingRef* mapping_ref) const
{
  auto get_mapping_func = [&onx_model](const ON_MappingChannel* pMC)
    {
      return ONX_Model_GetTextureMappingHelper(onx_model, pMC);
    };

  return ::Internal_GetCachedTextureCoordinates(*this, get_mapping_func, texture, mapping_ref);
}

static GET_TEXMAP_FROM_DOCUMENT pFnGetTexMapFromDocument = nullptr;

// Note: We are exporting this function for use in CRhinoObject::SetCachedTextureCoordinatesFromPlugIn
ON_DECL std::function<ON_TextureMapping(const ON_MappingChannel*)> ON_Mesh_Private_GetTextureMappingFromDocumentLambda(const CRhinoDoc& rhino_doc)
{
  return [&rhino_doc](const ON_MappingChannel* pMC)
  {
    if ( pFnGetTexMapFromDocument )
    {
      // Call into Rhino
      return pFnGetTexMapFromDocument(rhino_doc, pMC);
    }
    else
    {
      return ON_TextureMapping::SurfaceParameterTextureMapping;
    }
  };
}


const ON_TextureCoordinates* 
ON_Mesh::CachedTextureCoordinates( const ON_UUID& mapping_id ) const
{
  const int vertex_count = VertexCount();
  if (vertex_count > 0 )
  {
    const ON_TextureCoordinates* TC = m_TC.Array();
    int tci, tccount = m_TC.Count();
    for ( tci = 0; tci < tccount; tci++ )
    {
      if (   vertex_count == TC->m_T.Count() 
          && mapping_id == TC->m_tag.m_mapping_id )
      {
        return TC;
      }
      TC++;
    }
  }
  return 0;
}

bool ON_Mesh::HasSurfaceParameters() const
{
  const int vertex_count = VertexCount();
  return ( vertex_count > 0 && m_S.Count() == vertex_count ) ? true : false;
}

bool ON_Mesh::HasPrincipalCurvatures() const
{
  const int vertex_count = VertexCount();
  return ( vertex_count > 0 && m_K.Count() == vertex_count ) ? true : false;
}

bool ON_Mesh::HasVertexColors() const
{
  const int vertex_count = VertexCount();
  return (vertex_count > 0 && m_C.Count() == vertex_count) ? true : false;
}

bool ON_Mesh::HasVertexColors(
  ON_MappingTag color_tag
) const
{
  return this->HasVertexColors() && color_tag == this->m_Ctag;
}

void ON_Mesh::ClearVertexColors()
{
  this->m_C.SetCount(0);
  this->m_Ctag = ON_MappingTag::Unset;
}

bool ON_Mesh::SetDraftAngleColorAnalysisColors(
  bool bLazy,
  ON_SurfaceDraftAngleColorMapping draft_angle_colors
)
{
  const bool bSetColors = draft_angle_colors.IsSet() && this->HasVertexNormals();
  const ON_MappingTag Ctag = draft_angle_colors.ColorMappingTag();
  if (bSetColors && bLazy && this->m_Ctag == Ctag)
    return true;

  this->ClearVertexColors();

  if (false == bSetColors)
    return false;

  const unsigned count = this->m_N.Count();
  this->m_C.Reserve(count);
  for (unsigned i = 0; i < count; ++i)
  {
    const ON_Color c = draft_angle_colors.Color(ON_3dVector(this->m_N[i]));
    this->m_C.Append(c);
  }
  this->m_Ctag = Ctag;

  return true;
}

bool ON_Mesh::SetCurvatureColorAnalysisColors(
  bool bLazy,
  ON_SurfaceCurvatureColorMapping kappa_colors
)
{
  if (false == this->HasPrincipalCurvatures())
  {
#if 0
    // will be added April/May of 2024
    if (kappa_colors.IsSet())
    {
      this->ComputeVertexPrincipalCurvatures(ON_Mesh::CurvatureSettingMethod::DiscreteDefault, false);
      bLazy = false; // m_C[] is probably out of date even if the mapping tag is set.
    }
#endif
    return this->HasPrincipalCurvatures();
  }
  const bool bSetColors = kappa_colors.IsSet() && this->HasPrincipalCurvatures();
  const ON_MappingTag Ctag = kappa_colors.ColorMappingTag();
  if (bSetColors && bLazy && HasVertexColors() && this->m_Ctag == Ctag)
    return true;

  this->ClearVertexColors();

  if (false == bSetColors)
    return false;

  const unsigned count = this->m_K.Count();
  this->m_C.SetCount(0);
  this->m_C.Reserve(count);
  for (unsigned i = 0; i < count; ++i)
  {
    const ON_Color c = kappa_colors.Color(this->m_K[i]);
    this->m_C.Append(c);
  }
  this->m_Ctag = Ctag;

  return true;
}


void ON_Mesh::InvalidateBoundingBoxes()
{
  InvalidateVertexBoundingBox();
  InvalidateVertexNormalBoundingBox();
  InvalidateTextureCoordinateBoundingBox();
  InvalidateCurvatureStats();
}

void ON_Mesh::InvalidateVertexBoundingBox()
{
  m_vertex_bbox = ON_BoundingBox::UnsetBoundingBox;
  m_tight_bbox_cache.RemoveAllBoundingBoxes();
}

void ON_Mesh::InvalidateVertexNormalBoundingBox()
{
  m_nbox[0][0] = m_nbox[0][1] = m_nbox[0][2] =  1.0;
  m_nbox[1][0] = m_nbox[1][1] = m_nbox[1][2] = -1.0;
}

void ON_Mesh::InvalidateTextureCoordinateBoundingBox()
{
  m_tbox[0][0] = m_tbox[0][1] =  1.0;
  m_tbox[1][0] = m_tbox[1][1] = -1.0;
}

void ON_Mesh::InvalidateCurvatureStats()
{
  int i;
  for ( i = 0; i < 4; i++ ) {
    if ( m_kstat[i] ) {
      delete m_kstat[i];
      m_kstat[i] = 0;
    }
  }
}

bool ON_Mesh::UnitizeVertexNormals()
{
  bool rc = HasVertexNormals();
  if ( rc ) {
    const int vertex_count = VertexCount();
    float* n = &m_N[0][0];
    int i;
    ON_3dVector N;
    for ( i = 0; i < vertex_count; i++ ) {
      N.x = n[0];
      N.y = n[1];
      N.z = n[2];
      if ( !N.Unitize() )
        rc = false;
      *n++ = (float)N.x;
      *n++ = (float)N.y;
      *n++ = (float)N.z;
    }
  }
  return rc;
}

bool ON_Mesh::UnitizeFaceNormals()
{
  bool rc = HasFaceNormals();
  if ( rc ) {
    const int face_count = FaceCount();
    float* n = &m_FN[0][0];
    int i;
    ON_3dVector N;
    for ( i = 0; i < face_count; i++ ) {
      N.x = n[0];
      N.y = n[1];
      N.z = n[2];
      if ( !N.Unitize() )
        rc = false;
      *n++ = (float)N.x;
      *n++ = (float)N.y;
      *n++ = (float)N.z;
    }
  }
  return rc;
}


bool ON_Mesh::GetCurvatureStats( // returns true if successful
       ON::curvature_style kappa_style,
       ON_MeshCurvatureStats& stats
       ) const
{
  bool rc = false;
  stats.Destroy();
  int ksi;
  switch ( kappa_style ) {
    case ON::gaussian_curvature:
      ksi = 0;
      break;
    case ON::mean_curvature:
      ksi = 1;
      break;
    case ON::min_curvature: // minimum unsigned radius of curvature
      ksi = 2;
      break;
    case ON::max_curvature: // maximum unsigned radius of curvature
      ksi = 3;
      break;
    //case ON::section_curvature_x:
    //  ksi = 4;
    //  break;
    //case ON::section_curvature_y:
    //  ksi = 5;
    //  break;
    //case ON::section_curvature_z:
    //  ksi = 6;
    //  break;
    default:
      ksi = -1;
      break;
  }
  if ( ksi >= 0 && ksi <= 3 && HasPrincipalCurvatures() ) {
    ON_Mesh* p = (ON_Mesh*)this; // const lie 
    if ( !m_kstat[ksi] ) {
      p->m_kstat[ksi] = new ON_MeshCurvatureStats();
      p->m_kstat[ksi]->Set( kappa_style, m_K.Count(), m_K.Array(), m_N.Array() );
    }
    if ( p->m_kstat[ksi] ) {
      stats = *p->m_kstat[ksi];
      rc = true;
    }
  }
  return rc;
}

int ON_MeshTopology::WaitUntilReady(int sleep_value) const
{

  return m_b32IsValid;

}


bool ON_Mesh::TopologyExists() const
{
  return HasMeshTopology();
}

bool ON_Mesh::HasMeshTopology() const
{
  return (1 == m_top.WaitUntilReady(0));
}

const ON_MeshTopology& ON_Mesh::Topology() const
{
  int top_b32IsValid =  m_top.WaitUntilReady(-1);

  if ( 0 == top_b32IsValid ) 
  {
    ON_MeshTopology& top = const_cast<ON_MeshTopology&>(m_top);
    top.m_mesh = this;
    top_b32IsValid = top.Create() ? 1 : 0;
    top.m_b32IsValid = top_b32IsValid;
  }

  return m_top;
}

static ON_MeshTriangle ON_UnsetMeshTriangleInitalizer()
{
  ON_MeshTriangle unset_mesh_triangle;
  unset_mesh_triangle.m_vi[0] = ON_UNSET_UINT_INDEX;
  unset_mesh_triangle.m_vi[1] = ON_UNSET_UINT_INDEX;
  unset_mesh_triangle.m_vi[2] = ON_UNSET_UINT_INDEX;
  return unset_mesh_triangle;
}


const ON_MeshTriangle ON_MeshTriangle::UnsetMeshTriangle(ON_UnsetMeshTriangleInitalizer());

bool ON_MeshTriangle::IsValid( 
      size_t mesh_vertex_count
      ) const
{
  if ( mesh_vertex_count < 2 || mesh_vertex_count >= (size_t)ON_UNSET_UINT_INDEX )
    return false;
  if ( m_vi[0] == m_vi[1] || m_vi[1] == m_vi[2] || m_vi[2] == m_vi[0] )
    return false;
  const unsigned int c = (unsigned int)mesh_vertex_count;
  if ( m_vi[0] >= c || m_vi[1] >= c || m_vi[2] >= c )
    return false;
  return true;  
}

bool ON_MeshTriangle::IsValid(
      size_t mesh_vertex_count,
      const class ON_3fPoint* V
      ) const
{
  if ( false == IsValid(mesh_vertex_count) )
    return false;
  if ( 0 == V )
    return false;
  return ( V[m_vi[0]] != V[m_vi[1]] && V[m_vi[1]] != V[m_vi[2]] && V[m_vi[2]] != V[m_vi[0]] );
}

bool ON_MeshTriangle::IsValid(
      size_t mesh_vertex_count,
      const class ON_3dPoint* V
      ) const
{
  if ( false == IsValid(mesh_vertex_count) )
    return false;
  if ( 0 == V )
    return false;
  return ( V[m_vi[0]] != V[m_vi[1]] && V[m_vi[1]] != V[m_vi[2]] && V[m_vi[2]] != V[m_vi[0]] );
}

bool ON_MeshTriangle::IsValid(
      const class ON_3dPointListRef& vertex_list
      ) const
{
  if ( false == IsValid(vertex_list.PointCount()) )
    return false;
  ON_3dPoint V[3] = {vertex_list[m_vi[0]],vertex_list[m_vi[1]],vertex_list[m_vi[2]]};
  return ( V[0] != V[1] && V[1] != V[2] && V[2] != V[0] );
}

void ON_MeshTriangle::Flip()
{
  unsigned int i = m_vi[1];
  m_vi[1] = m_vi[2];
  m_vi[2] = i;
}


static bool ON_MeshTriangle_GetTriangleNormal(
   const double* p,
   const double* q,
   const double* r,
   class ON_3dVector& triangle_normal
  )
{
  const double a[3] = {r[0]-p[0],r[1]-p[1],r[2]-p[2]};
  const double b[3] = {p[0]-q[0],p[1]-q[1],p[2]-q[2]};

  triangle_normal.x = a[1]*b[2] - b[1]*a[2];
  triangle_normal.y = a[2]*b[0] - b[2]*a[0];
  triangle_normal.z = a[0]*b[1] - b[0]*a[1];
  return triangle_normal.Unitize();
}

bool ON_MeshTriangle::GetTriangleNormal(
  const class ON_3dPoint* dV, 
  class ON_3dVector& triangle_normal 
  ) const
{
  if ( 0 == dV )
    return false;
  return ON_MeshTriangle_GetTriangleNormal(&dV[m_vi[0]].x,&dV[m_vi[1]].x,&dV[m_vi[2]].x,triangle_normal);
}

bool ON_MeshTriangle::GetTriangleNormal(
  const class ON_3fPoint* fV, 
  class ON_3dVector& triangle_normal 
  ) const
{
  const ON_3dPoint p(fV[m_vi[0]]);
  const ON_3dPoint q(fV[m_vi[1]]);
  const ON_3dPoint r(fV[m_vi[2]]);
  return ON_MeshTriangle_GetTriangleNormal(&p.x,&q.x,&r.x,triangle_normal);
}

bool ON_MeshTriangle::GetTriangleNormal(
  const class ON_3dPointListRef& vertex_list, 
  class ON_3dVector& triangle_normal
  ) const
{
  const ON_3dPoint p(vertex_list[m_vi[0]]);
  const ON_3dPoint q(vertex_list[m_vi[1]]);
  const ON_3dPoint r(vertex_list[m_vi[2]]);
  return ON_MeshTriangle_GetTriangleNormal(&p.x,&q.x,&r.x,triangle_normal);
}

bool ON_MeshTriangle::GetTriangleNormal(
   ON_3dPoint point0,
   ON_3dPoint point1,
   ON_3dPoint point2,
   class ON_3dVector& triangle_normal
  )
{
  return ON_MeshTriangle_GetTriangleNormal(&point0.x,&point1.x,&point2.x,triangle_normal);
}

static ON_MeshFace ON_UnsetMeshFaceInitalizer()
{
  ON_MeshFace unset_mesh_face;
  unset_mesh_face.vi[0] = -1;
  unset_mesh_face.vi[1] = -1;
  unset_mesh_face.vi[2] = -1;
  unset_mesh_face.vi[3] = -1;
  return unset_mesh_face;
}

const ON_MeshFace ON_MeshFace::UnsetMeshFace(ON_UnsetMeshFaceInitalizer());

void ON_Mesh::DestroyTopology()
{
  m_top.Destroy();
}

bool
ON_MeshFace::IsTriangle() const 
{
  return vi[2]==vi[3];
}

bool
ON_MeshFace::IsQuad() const 
{
  return vi[2]!=vi[3];
}

void
ON_MeshFace::Flip()
{
  int i;
  if ( vi[2] == vi[3] ) {
    i = vi[1];
    vi[1] = vi[2];
    vi[2] = i;
    vi[3] = i;
  }
  else {
    i = vi[1];
    vi[1] = vi[3];
    vi[3] = i;
  }
}

void 
ON_Mesh::Flip()
{
  FlipFaceOrientation();
  FlipFaceNormals();
  FlipVertexNormals();
  FlipNgonOrientation();

  // Do not modify m_S[] or m_T[]
  // values here.
}

void 
ON_Mesh::FlipVertexNormals()
{
  int i;
  const int vcount = VertexCount();
  if ( HasVertexNormals() ) {
    for ( i = 0; i < vcount; i++ ) {
      m_N[i] = -m_N[i];
    }
  }
}

void 
ON_Mesh::FlipFaceNormals()
{
  int i;
  const int fcount = FaceCount();
  if ( HasFaceNormals() ) {
    for( i = 0; i < fcount; i++ ) {
      m_FN[i] = -m_FN[i];
    }
  }
}

void 
ON_Mesh::FlipFaceOrientation()
{
  int i;
  const int fcount = FaceCount();
  for( i = 0; i < fcount; i++ ) {
    m_F[i].Flip();
  }
  if ( fcount > 0 )
    DestroyTopology(); // flipping changes order of face corners
}



bool ON_MeshFace::ComputeFaceNormal( const ON_3dPoint* dV, ON_3dVector& FN ) const
{
  if ( 0 != dV )
  {
    ON_3dVector a = dV[vi[2]] - dV[vi[0]];
    ON_3dVector b = dV[vi[3]] - dV[vi[1]];
    FN = ON_CrossProduct( a, b ); // works for triangles, quads, and nonplanar quads
    if ( FN.Unitize() )
      return true;
  }

  FN = ON_3dVector::ZeroVector;
  return false;
}

bool ON_MeshFace::ComputeFaceNormal( const ON_3fPoint* fV, ON_3dVector& FN ) const
{
  if ( 0 != fV )
  {
    ON_3dVector a = fV[vi[2]] - fV[vi[0]];
    ON_3dVector b = fV[vi[3]] - fV[vi[1]];
    FN = ON_CrossProduct( a, b ); // works for triangles, quads, and nonplanar quads
    if ( FN.Unitize() )
      return true;
  }

  FN = ON_3dVector::ZeroVector;
  return false;
}

bool ON_MeshFace::ComputeFaceNormal( const class ON_3dPointListRef& vertex_list, ON_3dVector& FN ) const
{
  ON_3dVector a = vertex_list[vi[2]] - vertex_list[vi[0]];
  ON_3dVector b = vertex_list[vi[3]] - vertex_list[vi[1]];
  FN = ON_CrossProduct( a, b ); // works for triangles, quads, and nonplanar quads
  if ( FN.Unitize() )
    return true;

  FN = ON_3dVector::ZeroVector;
  return false;
}


unsigned int ON_MeshFace::GetCornerNormals(
  const class ON_3dPointListRef& vertex_list,
  ON_3dVector corner_normals[4]
  ) const
{
  unsigned int rc = 0;
  
  if (vi[2] == vi[3])
  {
    if (ComputeFaceNormal(vertex_list, corner_normals[0]))
    {
      rc = 4;
    }
    else
    {
      corner_normals[0] = ON_3dVector::UnsetVector;
      corner_normals[1] = corner_normals[0];
      corner_normals[2] = corner_normals[0];
      corner_normals[3] = corner_normals[0];
    }
    return rc;
  }
  else
  {
    const double unset_x = ON_3dVector::UnsetVector.x;
    ON_3dVector C = vertex_list[vi[0]] - vertex_list[vi[3]];
    if (!C.Unitize())
      C = ON_3dVector::UnsetVector;
    ON_3dVector B = C;
    for (unsigned int i = 0; i < 4; i++)
    {
      ON_3dVector A = B;
      if (3 == i)
        B = C;
      else
      {
        B = vertex_list[vi[i + 1]] - vertex_list[vi[i]];
        if (!B.Unitize())
          B = ON_3dVector::UnsetVector;
      }

      if (unset_x != A.x && unset_x != B.x)
      {
        corner_normals[i] = ON_CrossProduct(A, B);
        if (corner_normals[i].Unitize())
        {
          rc++;
          continue;
        }
      }

      corner_normals[i] = ON_3dVector::UnsetVector;
    }
  }

  return rc;
}

bool ON_MeshFace::GetPlaneEquation(
  const class ON_3dPointListRef& vertex_list,
  ON_PlaneEquation& face_plane_equation
  ) const
{
  ON_3dVector N;
  if (ComputeFaceNormal(vertex_list, N) && face_plane_equation.Create(vertex_list[vi[0]], N))
    return true;

  face_plane_equation = ON_PlaneEquation::UnsetPlaneEquation;
  return false;
}

bool ON_MeshFace::IsPlanar( 
  double planar_tolerance,
  double angle_tolerance_radians,
  const class ON_3dPointListRef& vertex_list, 
  ON_PlaneEquation* face_plane_equation
  ) const
{
  ON_PlaneEquation e;

  for (;;)
  {
    if (!GetPlaneEquation(vertex_list, e))
      break;

    if ( face_plane_equation )
      *face_plane_equation = e;

    if (vi[2] == vi[3])
      return true; // triangle

    if (planar_tolerance >= 0.0)
    {
      double h0, h1, h;
      h0 = h1 = 0.0;
      for (int i = 1; i < 3; i++)
      {
        if (vi[i - 1] == vi[i])
          continue;
        h = e.ValueAt(vertex_list[vi[i]]);
        if (h < h0)
          h0 = h;
        else if (h > h1)
          h1 = h;
        else
          continue;
        if (h1 - h0 > planar_tolerance)
        {
          return false;
        }
      }
    }

    if (angle_tolerance_radians >= 0.0)
    {
      ON_3dVector corner_normals[4];
      GetCornerNormals(vertex_list, corner_normals);
      const double unset_x = ON_3dVector::UnsetVector.x;
      const double cos_atol = (angle_tolerance_radians < ON_PI) ? cos(angle_tolerance_radians) : -1.0;
      for (unsigned int i = 0; i < 2; i++)
      {
        if (unset_x != corner_normals[i].x && unset_x != corner_normals[i+2].x && corner_normals[i] * corner_normals[i+2] < cos_atol)
          return false;
      }
    }

    return true;
  }

  if (face_plane_equation)
    *face_plane_equation = ON_PlaneEquation::UnsetPlaneEquation;

  return false;
}


bool ON_Mesh::ComputeFaceNormal( int fi )
{
  if ( fi < 0 )
    return false;
  if ( fi >= m_F.Count() )
    return false;
  if ( m_FN.Count() != m_F.Count() )
    return false;
  
  ON_3dVector FN;
  bool rc = ( HasDoublePrecisionVertices() )
          ? m_F[fi].ComputeFaceNormal(DoublePrecisionVertices().Array(),FN)
          : m_F[fi].ComputeFaceNormal(m_V.Array(),FN);
  
  m_FN[fi] = FN;

  return rc;
}

bool ON_Mesh::ComputeFaceNormals()
{
  bool rc = false;
  //const unsigned int vcount = VertexUnsignedCount();
  const int fcount = FaceCount();
  if ( fcount > 0 )
  {
    ON_3dVector a, b, n;
    int fi;
    const int* vi;
    if ( m_FN.Capacity() < fcount )
      m_FN.SetCapacity(fcount);
    m_FN.SetCount(0);
    rc = true;
    if ( HasSynchronizedDoubleAndSinglePrecisionVertices() )
    {      
      const ON_3dPointArray& dV = DoublePrecisionVertices();
      for ( fi = 0; fi < fcount; fi++ ) {
        vi = m_F[fi].vi;
        a = dV[vi[2]] - dV[vi[0]];
        b = dV[vi[3]] - dV[vi[1]];
        n = ON_CrossProduct( a, b ); // works for triangles, quads, and nonplanar quads
        n.Unitize();
        m_FN.AppendNew() = ON_3fVector(n);
      }
    }
    else
    {
      for ( fi = 0; fi < fcount; fi++ ) {
        vi = m_F[fi].vi;
        a = m_V[vi[2]] - m_V[vi[0]];
        b = m_V[vi[3]] - m_V[vi[1]];
        n = ON_CrossProduct( a, b ); // works for triangles, quads, and nonplanar quads
        n.Unitize();
        m_FN.AppendNew() = ON_3fVector(n);
      }
    }
  }
  else 
  {
    m_FN.Destroy();
  }
  return rc;
}


//static int compareRadial3fPoint( const ON_3fPoint* a, const ON_3fPoint* b )
//{
//  double ar = a->x+a->y+a->z;
//  double br = b->x+b->y+b->z;
//  if ( ar < br )
//    return -1;
//  if ( ar > br )
//    return 1;
//  return 0;
//}

bool ON_Mesh::CombineCoincidentVertices( 
        const ON_3fVector tolerance,
        double cos_normal_angle // = -1.0  // cosine(break angle) -1.0 will merge all coincident vertices
        )
{
  // TODO - If you need this function, please ask Dale Lear to finish it.
  //bool rc = false;
  //const int vcount = VertexCount();
  //if ( vcount > 0 && rc ) {
  //  ON_Workspace ws;
  //  int* index = ws.GetIntMemory(vcount);
  //  rc = m_V.Sort( ON::sort_algorithm::quick_sort, index, compareRadial3fPoint );
  //  int i, j;
  //  ON_3fPoint p0, p1, pmin, pmax;
  //  for ( i = 0; i < vcount; i++ ) {
  //    p0 = m_V[i];
  //    pmin = p0 - tolerance;
  //    pmax = p0 + tolerance;
  //    for ( j = i+1; j < vcount; j++ ) {
  //      p1 = m_V[j];
  //      // TODO        
  //    }
  //  }
  //}
  return false;
}


struct tagMESHPOINTS
{
  // p0 = bogus pointer - never dereferenced - that is used
  //      to calculate vertex index in CompareMeshPoint().
  const char* p0;
  ON_3fPoint*  V;
  ON_2fPoint*  T;
  ON_3fVector* N;
  ON_SurfaceCurvature* K;
  ON_Color* C;
};

static int CompareMeshPoint(const void* a,const void* b,void* ptr)
{
  float d;
  const struct tagMESHPOINTS * mp = (const struct tagMESHPOINTS *)ptr;

  // use bogus pointer to convert a,b into vertex indices
  int i = (int)(((const char*)a) - mp->p0); // the (int) is for 64 bit size_t conversion
  int j = (int)(((const char*)b) - mp->p0);

  d = mp->V[j].x - mp->V[i].x;
  if ( d == 0.0f )
  {
    d = mp->V[j].y - mp->V[i].y;
    if ( d == 0.0f )
    {
      d = mp->V[j].z - mp->V[i].z;

      //if ( d == 0.0f )
      //  return 0;

      if ( d == 0.0f && 0 != mp->N)
      {
        d = mp->N[j].x - mp->N[i].x;
        if ( d == 0.0f )
        {
          d = mp->N[j].y - mp->N[i].y;
          if ( d == 0.0f )
          {
            d = mp->N[j].z - mp->N[i].z;
          }
        }
      }

      if ( d == 0.0f && 0 != mp->T)
      {
        d = mp->T[j].x - mp->T[i].x;
        if ( d == 0.0f )
        {
          d = mp->T[j].y - mp->T[i].y;
        }
      }

      if ( d == 0.0f && 0 != mp->C )
      {
        int u = ((int)mp->C[j])-((int)mp->C[i]);
        if ( u < 0 )
          d = -1.0f;
        else if ( u > 0 )
          d = 1.0f;
      }

      if ( d == 0.0f && 0 != mp->K )
      {
        double dk = mp->K[j].k1 - mp->K[i].k1;
        if ( dk < 0.0 )
          d = -1.0;
        else if ( dk > 0.0 )
          d = 1.0;
        else
        {
          dk = mp->K[j].k2 - mp->K[i].k2;
          if ( dk < 0.0 )
            d = -1.0;
          else if ( dk > 0.0 )
            d = 1.0;
        }
      }
    }
  }
  
  if ( d < 0.0f )
    return -1;
  if ( d > 0.0f )
    return 1;
  return 0;
}

unsigned int ON_Mesh::RemoveAllCreases()
{
  unsigned int vertex_count0 = this->VertexUnsignedCount();
  bool bChanged = this->CombineIdenticalVertices(true, true);
  const unsigned int vertex_count1 = this->VertexUnsignedCount();

  if (vertex_count0 == vertex_count1 && bChanged)
    vertex_count0 = vertex_count1 + 1;
  return (vertex_count0 - vertex_count1);
}

bool ON_Mesh::CombineIdenticalVertices(
                                bool bIgnoreVertexNormals,
                                bool bIgnoreTextureCoordinates
                                )
{
  // 11 June 2003 - added and tested.
  bool rc = false;
  ON_Mesh& mesh = *this;

  int vertex_count = mesh.m_V.Count();
  if ( vertex_count > 0 )
  {
    ON_SimpleArray<int> index_array(vertex_count);
    ON_SimpleArray<int> remap_array(vertex_count);

    int remap_vertex_count = 0;
    int merge_count = 0;
    int i0, i1, k;

    struct tagMESHPOINTS mp;
    memset(&mp,0,sizeof(mp));
    mp.p0 = (const char*)&mp; // bogus pointer - never dereferenced
    mp.V = mesh.m_V.Array();
    mp.N = mesh.HasVertexNormals()       ? mesh.m_N.Array() : 0;
    mp.T = mesh.HasTextureCoordinates()  ? mesh.m_T.Array() : 0;
    mp.C = mesh.HasVertexColors()        ? mesh.m_C.Array() : 0;
    mp.K = mesh.HasPrincipalCurvatures() ? mesh.m_K.Array() : 0;

    if ( bIgnoreVertexNormals )
    {
      mp.N = 0;
    }

    if ( bIgnoreTextureCoordinates )
    {
      mp.T = 0;
      mp.C = 0;
      mp.K = 0;
    }

    index_array.SetCount(vertex_count);
    index_array.Zero();
    int* index = index_array.Array();

    remap_array.SetCount(vertex_count);
    int* remap = remap_array.Array();
    for ( k = 0; k < vertex_count; k++ )
      remap[k] = -1;

    ON_Sort( 
          ON::sort_algorithm::quick_sort,
          index,
          mp.p0,                 // data buffer
          vertex_count,
          sizeof(*mp.p0),
          CompareMeshPoint,
          &mp
         );

    for ( i0 = 0; i0 < vertex_count; i0 = i1 )
    {
      for ( i1 = i0+1; i1 < vertex_count; i1++ )
      {
        if ( CompareMeshPoint( mp.p0+index[i0], mp.p0+index[i1], &mp ) )
          break;
        else
          merge_count++;
      }
      for ( /*empty*/; i0 < i1; i0++ )
      {
        remap[index[i0]] = remap_vertex_count;
      }
      remap_vertex_count++;
    }

    if ( bIgnoreVertexNormals )
    {
      mp.N = mesh.HasVertexNormals() ? mesh.m_N.Array() : 0;
    }

    if ( bIgnoreTextureCoordinates )
    {
      mp.T = mesh.HasTextureCoordinates()  ? mesh.m_T.Array() : 0;
      mp.C = mesh.HasVertexColors()        ? mesh.m_C.Array() : 0;
      mp.K = mesh.HasPrincipalCurvatures() ? mesh.m_K.Array() : 0;
    }

    if ( remap_vertex_count > 0 && remap_vertex_count < vertex_count )
    {
      ON_SimpleArray<ON_3fPoint> p_array(remap_vertex_count);
      p_array.SetCount(remap_vertex_count);
      ON_3fPoint* p = p_array.Array();
      ON_3fVector* v = (ON_3fVector*)p;

      for ( k = 0; k < vertex_count; k++ )
      {
        p[remap[k]] = mp.V[k];
      }
      for ( k = 0; k < remap_vertex_count; k++ )
        mp.V[k] = p[k];
      mesh.m_V.SetCount(remap_vertex_count);

      if (vertex_count == m_dV.Count())
      {
        ON_SimpleArray<ON_3dPoint> dp_array;
        ON_3dPoint* dp = dp_array.Reserve(remap_vertex_count);
        ON_3dPoint* D = m_dV.Array();
        for (k = 0; k < vertex_count; k++)
        {
          dp[remap[k]] = D[k];
        }
        for (k = 0; k < remap_vertex_count; k++)
          D[k] = dp[k];
        m_dV.SetCount(remap_vertex_count);
      }
      else
        m_dV.Destroy();

      if ( 0 != mp.N )
      {
        if ( bIgnoreVertexNormals )
        {
          // average vertex normals of combined vertices
          p_array.Zero();
          for ( k = 0; k < vertex_count; k++ )
          {
            v[remap[k]] += mp.N[k];
          }
          for ( k = 0; k < remap_vertex_count; k++ )
          {
            v[k].Unitize();
          }
        }
        else
        {
          for ( k = 0; k < vertex_count; k++ )
          {
            v[remap[k]] = mp.N[k];
          }
        }
        for ( k = 0; k < remap_vertex_count; k++ )
          mp.N[k] = v[k];
        mesh.m_N.SetCount(remap_vertex_count);
      }
      else
        mesh.m_N.SetCount(0);

      if ( 0 != mp.T && !bIgnoreTextureCoordinates )
      {
        for ( k = 0; k < vertex_count; k++ )
        {
          p[remap[k]] = mp.T[k];
        }
        for ( k = 0; k < remap_vertex_count; k++ )
          mp.T[k] = p[k];
        mesh.m_T.SetCount(remap_vertex_count);
      }
      else
        mesh.m_T.SetCount(0);

      if ( 0 != mp.C && !bIgnoreTextureCoordinates )
      {
        ON_SimpleArray<ON_Color> c_array(remap_vertex_count);
        c_array.SetCount(remap_vertex_count);
        ON_Color* c = c_array.Array();
        for ( k = 0; k < vertex_count; k++ )
        {
          c[remap[k]] = mp.C[k];
        }
        for ( k = 0; k < remap_vertex_count; k++ )
          mp.C[k] = c[k];
        mesh.m_C.SetCount(remap_vertex_count);
      }
      else
        mesh.m_C.SetCount(0);

      if ( 0 != mp.K && !bIgnoreTextureCoordinates )
      {
        ON_SimpleArray<ON_SurfaceCurvature> s_array(remap_vertex_count);
        s_array.SetCount(remap_vertex_count);
        ON_SurfaceCurvature* s = s_array.Array();
        for ( k = 0; k < vertex_count; k++ )
        {
          s[remap[k]] = mp.K[k];
        }
        for ( k = 0; k < remap_vertex_count; k++ )
          mp.K[k] = s[k];
        mesh.m_K.SetCount(remap_vertex_count);
      }
      else
        mesh.m_K.SetCount(0);

      const int face_count = mesh.m_F.Count();
      ON_MeshFace* f = mesh.m_F.Array();
      int* fvi;
      for ( k = 0; k < face_count; k++ )
      {
        fvi = f[k].vi;
        fvi[0] = remap[fvi[0]];
        fvi[1] = remap[fvi[1]];
        fvi[2] = remap[fvi[2]];
        fvi[3] = remap[fvi[3]];
      }

      if ( HasNgons() )
      {
        for ( int ngon_index = 0; ngon_index < m_Ngon.Count(); ngon_index++ )
        {
          ON_MeshNgon* ngon = m_Ngon[ngon_index];
          if ( 0 == ngon )
            continue;
          for ( unsigned int ngon_vertex_index = 0; ngon_vertex_index < ngon->m_Vcount; ngon_vertex_index++ )
            ngon->m_vi[ngon_vertex_index] = remap[ngon->m_vi[ngon_vertex_index]];
        }
      }

      //if (0 != V4V5_NgonList())
      //{
      //  //This mesh has an ngon list.
      //  //Modify the vertex indexes in the ngons as 
      //  //we did the faces above
      //  ON_V4V5_MeshNgonList* ngonlist = V4V5_ModifyNgonList();
      //  int kk, kkct = ngonlist->V4V5_NgonCount();
      //  for (kk = 0; kk < kkct; kk++)
      //  {
      //    ON_MeshNgon* ngon = ngonlist->V4V5_Ngon(kk);
      //    if (0 == ngon)
      //      continue;
      //    for ( k = 0; k < ngon->m_N; k++ )
      //      ngon->m_vi[k] = remap[ngon->m_vi[k]];
      //  }
      //}

      mesh.DestroyPartition();
      mesh.DestroyTopology();
      mesh.m_S.Destroy();

      if ( mesh.m_V.Capacity() > 4*mesh.m_V.Count() && mesh.m_V.Capacity() > 50 )
      {
        // There is lots of unused memory in the dynamic arrays.
        // Release what we can.
        mesh.Compact();
      }
      rc = true;
    }
  }
  return rc;
}

void ON_Mesh::Append( std::vector<std::shared_ptr<const ON_Mesh>> meshes )
{
  if ( meshes.size() == 0 )
    return;

  int vcount0 = VertexCount();
  if ( vcount0 <= 0 )
    m_F.SetCount(0);
  int fcount0 = FaceCount();

  // The calls to Has*() must happen before the m_V[] and m_F[] arrays get enlarged
  // Allow the appendage of VertexNormals, TextureCoordinates, PrincipalCurvatures to empty meshes
  // by checking for 0 == vcount0 && 0 == fcount0
  bool bHasVertexNormals       = (0 == vcount0 || HasVertexNormals());
  bool bHasFaceNormals         = (0 == vcount0 || 0 == fcount0 || HasFaceNormals());
  bool bHasTextureCoordinates  = (0 == vcount0 || HasTextureCoordinates());
  bool bHasPrincipalCurvatures = (0 == vcount0 || HasPrincipalCurvatures());
  bool bHasVertexColors        = (0 == vcount0 || HasVertexColors());
  bool bHasSurfaceParameters   = (0 == vcount0 || HasSurfaceParameters());
  bool bHasDoubles             = (0 == vcount0 || HasSynchronizedDoubleAndSinglePrecisionVertices());
  bool bHasNgonMap             = (NgonCount() > 0 && 0 != NgonMap());

  bool bSetMeshParameters = true;
  const ON_MeshParameters* mp = nullptr;
  ON_SHA1_Hash mp_hash = ON_SHA1_Hash::EmptyContentHash;
  if (0 != vcount0)
  {
    mp = this->MeshParameters();
    if (nullptr == mp)
      bSetMeshParameters = false;
    else
      mp_hash = mp->GeometrySettingsHash();
  }

  bool bHasSurfaceDomain
    = bHasSurfaceParameters
    && (0 == vcount0 || (m_srf_domain[0].IsIncreasing() && m_srf_domain[1].IsIncreasing()));

  ON_Interval srf_domain[2];
  srf_domain[0] = (bHasSurfaceDomain && vcount0  > 0) ? m_srf_domain[0] : ON_Interval::EmptyInterval;
  srf_domain[1] = (bHasSurfaceDomain && vcount0  > 0) ? m_srf_domain[1] : ON_Interval::EmptyInterval;
  
  bool bHasTexturePackingDomain
    = bHasTextureCoordinates
    && (0 == vcount0 || (m_packed_tex_domain[0].IsIncreasing() && m_packed_tex_domain[1].IsIncreasing()));

  ON_Interval packed_tex_domain[2];
  packed_tex_domain[0] = (bHasTexturePackingDomain && vcount0  > 0) ? m_packed_tex_domain[0] : ON_Interval::EmptyInterval;
  packed_tex_domain[1] = (bHasTexturePackingDomain && vcount0  > 0) ? m_packed_tex_domain[1] : ON_Interval::EmptyInterval;
  bool packed_tex_rotate = (bHasTexturePackingDomain && m_packed_tex_rotate) ? true : false;

  double srf_scale[2] = { m_srf_scale[0], m_srf_scale[1]};

  int fcount = fcount0;
  int vcount = vcount0;
  unsigned int merged_count = vcount0 > 0 ? 1 : 0;

  int mesh_index = 0;
  for ( auto m : meshes )
  {
    if (!m )
      continue;
    int vcount1 = m->m_V.Count();
    if ( vcount1 <= 0 )
      continue;

    merged_count++;

    if (bSetMeshParameters)
    {
      const ON_MeshParameters* this_mesh_mp = m->MeshParameters();
      if (nullptr == this_mesh_mp)
        bSetMeshParameters = false;
      else
      {
        const ON_SHA1_Hash this_mesh_mp_hash = this_mesh_mp->GeometrySettingsHash();
        if (nullptr == mp)
        {
          // first mesh parameters.
          mp = this_mesh_mp;
          mp_hash = this_mesh_mp_hash;
        }
        else
        {
          if (this_mesh_mp_hash != mp_hash)
          {
            // variable mesh parameters - means output gets none.
            bSetMeshParameters = false;
          }
        }
      }
    }

    int fcount1 = m->m_F.Count();
    if ( fcount1 > 0 )
      fcount += fcount1;
    vcount += vcount1;
    if ( bHasVertexNormals && !m->HasVertexNormals() )
      bHasVertexNormals = false;
    if ( bHasTextureCoordinates && !m->HasTextureCoordinates())
      bHasTextureCoordinates = false;
    if ( bHasPrincipalCurvatures && !m->HasPrincipalCurvatures())
      bHasPrincipalCurvatures = false;
    if ( bHasVertexColors && !m->HasVertexColors())
      bHasVertexColors = false;
    if ( bHasSurfaceParameters && !m->HasSurfaceParameters())
      bHasSurfaceParameters = false;
    if ( bHasDoubles && !m->HasSynchronizedDoubleAndSinglePrecisionVertices())
      bHasDoubles = false;
    if ( bHasFaceNormals && fcount1 > 0 && !m->HasFaceNormals() )
      bHasFaceNormals = false;

    if (bHasSurfaceDomain)
    {
      bHasSurfaceDomain
        = bHasSurfaceParameters
        && m->m_srf_domain[0].IsIncreasing()
        && m->m_srf_domain[1].IsIncreasing();
      if (bHasSurfaceDomain)
      {
        srf_domain[0].Union(m->m_srf_domain[0]);
        srf_domain[1].Union(m->m_srf_domain[1]);
      }
    }

    if (1 == merged_count && bHasSurfaceParameters && bHasSurfaceDomain)
    {
      srf_scale[0] = m->m_srf_scale[0];
      srf_scale[1] = m->m_srf_scale[1];
    }
    else
    {
      srf_scale[0] = 0.0;
      srf_scale[1] = 0.0;
    }

    if (bHasTexturePackingDomain)
    {
      // 2014-04-01 Dale Lear
      //   Trying to merger packed_tex_domain[] intervals
      //   is questionable at best.
      //   A strong argument can be made for simply deleting
      //   packed texture domain information when there are
      //   two non-empty meshes that are merged.
      bHasTexturePackingDomain
        = bHasTextureCoordinates
        && m->m_packed_tex_domain[0].IsIncreasing()
        && m->m_packed_tex_domain[1].IsIncreasing();
      if (packed_tex_rotate != (m->m_packed_tex_rotate?true:false))
      {
        if (0 == vcount0 && 0 == mesh_index)
        {
          packed_tex_rotate = (m->m_packed_tex_rotate ? true : false);
        }
        else
        {
          bHasTexturePackingDomain = false;
        }
      }
      if (bHasTexturePackingDomain)
      {
        if (1 == merged_count)
        {
          packed_tex_rotate = (m->m_packed_tex_rotate ? true : false);
        }
        else if (packed_tex_rotate != (m->m_packed_tex_rotate ? true : false))
        {
          bHasTexturePackingDomain = false;
        }
        packed_tex_domain[0].Union(m->m_packed_tex_domain[0]);
        packed_tex_domain[1].Union(m->m_packed_tex_domain[1]);
      }     
    }

    mesh_index++;
  }


  if ( vcount <= vcount0 && fcount <= fcount0 )
    return;

  if (!bHasSurfaceParameters || !bHasSurfaceDomain)
  {
    srf_domain[0] = ON_Interval::EmptyInterval;
    srf_domain[1] = ON_Interval::EmptyInterval;
    srf_scale[0] = 0.0;
    srf_scale[1] = 0.0;
  }

  if (!bHasTextureCoordinates || !bHasTexturePackingDomain)
  {
    packed_tex_domain[0] = ON_Interval::EmptyInterval;
    packed_tex_domain[1] = ON_Interval::EmptyInterval;
    packed_tex_rotate = false;
  }

  m_srf_domain[0] = srf_domain[0];
  m_srf_domain[1] = srf_domain[1];
  m_srf_scale[0] = srf_scale[0];
  m_srf_scale[1] = srf_scale[1];

  m_packed_tex_domain[0] = packed_tex_domain[0];
  m_packed_tex_domain[1] = packed_tex_domain[1];
  m_packed_tex_rotate = packed_tex_rotate;

  m_top.Destroy();

  // It is critical to call DoublePrecisionVertices() before 
  // we modify m_V[] because DoublePrecisionVertices() will
  // attempt to update the double precision information
  // when it notices that m_V has new vertices added.

  m_V.Reserve(vcount);
  m_F.Reserve(fcount);
  for (auto m : meshes)
  {
    const unsigned int vcount0_local = m_V.UnsignedCount();
    const unsigned int fcount0_local = m_F.UnsignedCount();

    if (!m)
      continue;

    int vcount1 = m->m_V.Count();
    if ( vcount1 <= 0 )
      continue;
    int fcount1 = m->m_F.Count();
    if ( fcount1 > 0 )
    {
      auto j = m_F.Count();
      m_F.Append(fcount1,m->m_F.Array());
      fcount1 += j;
      while (j < fcount1)
      {
        const auto vi = m_F[j].vi;
        vi[0] += (int)vcount0_local;
        vi[1] += (int)vcount0_local;
        vi[2] += (int)vcount0_local;
        vi[3] += (int)vcount0_local;
        j++;
      }
    }
    m_V.Append(vcount1,m->m_V.Array());
    if ( m->HasNgons() )
    {
      if ( 0 != m->NgonMap() )
        bHasNgonMap = true;
      m_NgonMap.Destroy();
      unsigned int ngon_count = m->NgonUnsignedCount();
      for ( unsigned int ni = 0; ni < ngon_count; ni++ )
      {
        const ON_MeshNgon* ngon0 = m->Ngon(ni);
        if ( 0 == ngon0 )
          continue;
        if ( 0 == ngon0->m_Vcount && 0 == ngon0->m_Fcount )
          continue;
        ON_MeshNgon* ngon1 = this->m_NgonAllocator.CopyNgon(ngon0);
        if ( 0 == ngon1 )
          continue;
        for ( unsigned int nvi = 0; nvi < ngon1->m_Vcount; nvi++ )
        {
          ngon1->m_vi[nvi] += vcount0_local;
        }
        for ( unsigned int nfi = 0; nfi < ngon1->m_Fcount; nfi++ )
        {
          ngon1->m_fi[nfi] += fcount0_local;
        }
        this->AddNgon(ngon1);
      }
    }
  }

  if ( bHasDoubles)
  {
    // Now update the double precision vertex locations.
    m_dV.Reserve(vcount);
    for (auto m : meshes)
    {
      if ( !m || m->m_dV.Count() <= 0 )
        continue;

      m_dV.Append(m->m_dV.Count(),m->m_dV.Array());
    }
    if (m_dV.Count() != vcount)
      bHasDoubles = false;
  }

  if ( false == bHasDoubles )
  {
    bHasDoubles = false;
    DestroyDoublePrecisionVertices();
  }
  
  if ( bHasVertexNormals ) 
  {
    m_N.Reserve(vcount);
    for (auto m : meshes)
    {
      if (!m)
        continue;
      m_N.Append(m->m_N.Count(), m->m_N.Array());
    }
  }
  else
  {
    m_N.Destroy();
  }


  if ( bHasFaceNormals ) 
  {
    m_FN.Reserve(fcount);
    for (auto m : meshes)
    {
      if ( !m || m->m_V.Count() <= 0 )
        continue;
      m_FN.Append(m->m_FN.Count(), m->m_FN.Array());
    }
  }
  else
  {
    m_FN.Destroy();
  }

  if ( bHasTextureCoordinates ) 
  {
    m_T.Reserve(vcount);
    for (auto m : meshes)
    {
      if (!m )
        continue;
      m_T.Append(m->m_T.Count(), m->m_T.Array());
    }
  }
  else 
  {
    m_T.Destroy();
  }


  if ( bHasSurfaceParameters )
  {
    m_S.Reserve(vcount);
    for (auto m : meshes)
    {
      if ( !m )
        continue;
      m_S.Append(m->m_S.Count(), m->m_S.Array());
    }
  }
  else 
  {
    m_S.Destroy();
  }

  if ( bHasPrincipalCurvatures )
  {
    m_K.Reserve(vcount);
    for (auto m : meshes)
    {
      if ( !m )
        continue;
      m_K.Append(m->m_K.Count(), m->m_K.Array());
    }
  }
  else
  {
    m_K.Destroy();
  }

  if ( bHasVertexColors ) 
  {
    m_C.Reserve(vcount);
    for (auto m : meshes)
    {
      if (!m)
        continue;
      m_C.Append(m->m_C.Count(), m->m_C.Array());
    }
  }
  else 
  {
    m_C.Destroy();
  }

  if ( 0 !=  m_mesh_parameters )
  {
    for (auto m : meshes)
    {
      if (!m)
        continue;
      if ( 0 == m->m_mesh_parameters || *m_mesh_parameters != *m->m_mesh_parameters )
      {
        delete m_mesh_parameters;
        m_mesh_parameters = 0;
        break;
      }
    }
  }

  for ( int j = 0; j < 4; j++ ) 
  {
    if ( m_kstat[j] ) 
    {
      // will be recomputed if required
      delete m_kstat[j];
      m_kstat[j] = 0;
    }
  }

  SetClosed(-99);
  SetSolidOrientation(-99);
  InvalidateBoundingBoxes();

  if ( NgonCount() > 0 && bHasNgonMap )
    CreateNgonMap();

  if (bSetMeshParameters && nullptr != mp && mp != this->MeshParameters())
  {
    // Appending to an empty this and all appendees have matching mesh parameters.
    this->SetMeshParameters(*mp);
  }
}


void ON_Mesh::Append(int mesh_count, const ON_Mesh* const* meshes)
{
  if (mesh_count <= 0 || 0 == meshes)
    return;

  int mi;
  int vcount0 = VertexCount();
  if (vcount0 <= 0)
    m_F.SetCount(0);
  int fcount0 = FaceCount();
  int* vi;
  int j;
  const ON_Mesh* m;

  // The calls to Has*() must happen before the m_V[] and m_F[] arrays get enlarged
  // Allow the appendage of VertexNormals, TextureCoordinates, PrincipalCurvatures to empty meshes
  // by checking for 0 == vcount0 && 0 == fcount0
  bool bHasVertexNormals = (0 == vcount0 || HasVertexNormals());
  bool bHasFaceNormals = (0 == vcount0 || 0 == fcount0 || HasFaceNormals());
  bool bHasTextureCoordinates = (0 == vcount0 || HasTextureCoordinates());
  bool bHasPrincipalCurvatures = (0 == vcount0 || HasPrincipalCurvatures());
  bool bHasVertexColors = (0 == vcount0 || HasVertexColors());
  bool bHasSurfaceParameters = (0 == vcount0 || HasSurfaceParameters());
  bool bHasDoubles = (0 == vcount0 || HasSynchronizedDoubleAndSinglePrecisionVertices());
  bool bHasNgonMap = (NgonCount() > 0 && 0 != NgonMap());

  bool bSetMeshParameters = true;
  const ON_MeshParameters* mp = nullptr;
  ON_SHA1_Hash mp_hash = ON_SHA1_Hash::EmptyContentHash;
  if (0 != vcount0)
  {
    mp = this->MeshParameters();
    if (nullptr == mp)
      bSetMeshParameters = false;
    else
      mp_hash = mp->GeometrySettingsHash();
  }

  bool bHasSurfaceDomain
    = bHasSurfaceParameters
    && (0 == vcount0 || (m_srf_domain[0].IsIncreasing() && m_srf_domain[1].IsIncreasing()));

  ON_Interval srf_domain[2];
  srf_domain[0] = (bHasSurfaceDomain && vcount0 > 0) ? m_srf_domain[0] : ON_Interval::EmptyInterval;
  srf_domain[1] = (bHasSurfaceDomain && vcount0 > 0) ? m_srf_domain[1] : ON_Interval::EmptyInterval;

  bool bHasTexturePackingDomain
    = bHasTextureCoordinates
    && (0 == vcount0 || (m_packed_tex_domain[0].IsIncreasing() && m_packed_tex_domain[1].IsIncreasing()));

  ON_Interval packed_tex_domain[2];
  packed_tex_domain[0] = (bHasTexturePackingDomain && vcount0 > 0) ? m_packed_tex_domain[0] : ON_Interval::EmptyInterval;
  packed_tex_domain[1] = (bHasTexturePackingDomain && vcount0 > 0) ? m_packed_tex_domain[1] : ON_Interval::EmptyInterval;
  bool packed_tex_rotate = (bHasTexturePackingDomain && m_packed_tex_rotate) ? true : false;

  double srf_scale[2] = { m_srf_scale[0], m_srf_scale[1] };

  int fcount = fcount0;
  int vcount = vcount0;
  unsigned int merged_count = vcount0 > 0 ? 1 : 0;
  for (mi = 0; mi < mesh_count; mi++)
  {
    m = meshes[mi];
    if (0 == m)
      continue;
    int vcount1 = m->m_V.Count();
    if (vcount1 <= 0)
      continue;

    merged_count++;

    if (bSetMeshParameters)
    {
      const ON_MeshParameters* this_mesh_mp = m->MeshParameters();
      if (nullptr == this_mesh_mp)
        bSetMeshParameters = false;
      else
      {
        const ON_SHA1_Hash this_mesh_mp_hash = this_mesh_mp->GeometrySettingsHash();
        if (nullptr == mp)
        {
          // first mesh parameters.
          mp = this_mesh_mp;
          mp_hash = this_mesh_mp_hash;
        }
        else
        {
          if (this_mesh_mp_hash != mp_hash)
          {
            // variable mesh paramters - means output gets none.
            bSetMeshParameters = false;
          }
        }
      }
    }

    int fcount1 = m->m_F.Count();
    if (fcount1 > 0)
      fcount += fcount1;
    vcount += vcount1;
    if (bHasVertexNormals && !m->HasVertexNormals())
      bHasVertexNormals = false;
    if (bHasTextureCoordinates && !m->HasTextureCoordinates())
      bHasTextureCoordinates = false;
    if (bHasPrincipalCurvatures && !m->HasPrincipalCurvatures())
      bHasPrincipalCurvatures = false;
    if (bHasVertexColors && !m->HasVertexColors())
      bHasVertexColors = false;
    if (bHasSurfaceParameters && !m->HasSurfaceParameters())
      bHasSurfaceParameters = false;
    if (bHasDoubles && !m->HasSynchronizedDoubleAndSinglePrecisionVertices())
      bHasDoubles = false;
    if (bHasFaceNormals && fcount1 > 0 && !m->HasFaceNormals())
      bHasFaceNormals = false;

    if (bHasSurfaceDomain)
    {
      bHasSurfaceDomain
        = bHasSurfaceParameters
        && m->m_srf_domain[0].IsIncreasing()
        && m->m_srf_domain[1].IsIncreasing();
      if (bHasSurfaceDomain)
      {
        srf_domain[0].Union(m->m_srf_domain[0]);
        srf_domain[1].Union(m->m_srf_domain[1]);
      }
    }

    if (1 == merged_count && bHasSurfaceParameters && bHasSurfaceDomain)
    {
      srf_scale[0] = m->m_srf_scale[0];
      srf_scale[1] = m->m_srf_scale[1];
    }
    else
    {
      srf_scale[0] = 0.0;
      srf_scale[1] = 0.0;
    }

    if (bHasTexturePackingDomain)
    {
      // 2014-04-01 Dale Lear
      //   Trying to merger packed_tex_domain[] intervals
      //   is questionable at best.
      //   A strong argument can be made for simply deleting
      //   packed texture domain information when there are
      //   two non-empty meshes that are merged.
      bHasTexturePackingDomain
        = bHasTextureCoordinates
        && m->m_packed_tex_domain[0].IsIncreasing()
        && m->m_packed_tex_domain[1].IsIncreasing();
      if (packed_tex_rotate != (m->m_packed_tex_rotate ? true : false))
      {
        if (0 == vcount0 && 0 == mi)
        {
          packed_tex_rotate = (m->m_packed_tex_rotate ? true : false);
        }
        else
        {
          bHasTexturePackingDomain = false;
        }
      }
      if (bHasTexturePackingDomain)
      {
        if (1 == merged_count)
        {
          packed_tex_rotate = (m->m_packed_tex_rotate ? true : false);
        }
        else if (packed_tex_rotate != (m->m_packed_tex_rotate ? true : false))
        {
          bHasTexturePackingDomain = false;
        }
        packed_tex_domain[0].Union(m->m_packed_tex_domain[0]);
        packed_tex_domain[1].Union(m->m_packed_tex_domain[1]);
      }
    }
  }


  if (vcount <= vcount0 && fcount <= fcount0)
    return;

  if (!bHasSurfaceParameters || !bHasSurfaceDomain)
  {
    srf_domain[0] = ON_Interval::EmptyInterval;
    srf_domain[1] = ON_Interval::EmptyInterval;
    srf_scale[0] = 0.0;
    srf_scale[1] = 0.0;
  }

  if (!bHasTextureCoordinates || !bHasTexturePackingDomain)
  {
    packed_tex_domain[0] = ON_Interval::EmptyInterval;
    packed_tex_domain[1] = ON_Interval::EmptyInterval;
    packed_tex_rotate = false;
  }

  m_srf_domain[0] = srf_domain[0];
  m_srf_domain[1] = srf_domain[1];
  m_srf_scale[0] = srf_scale[0];
  m_srf_scale[1] = srf_scale[1];

  m_packed_tex_domain[0] = packed_tex_domain[0];
  m_packed_tex_domain[1] = packed_tex_domain[1];
  m_packed_tex_rotate = packed_tex_rotate;

  m_top.Destroy();

  // It is critical to call DoublePrecisionVertices() before 
  // we modify m_V[] because DoublePrecisionVertices() will
  // attempt to update the double precision information
  // when it notices that m_V has new vertices added.

  m_V.Reserve(vcount);
  m_F.Reserve(fcount);
  for (mi = 0; mi < mesh_count; mi++)
  {
    const unsigned int vcount0_local = m_V.UnsignedCount();
    const unsigned int fcount0_local = m_F.UnsignedCount();
    m = meshes[mi];
    if (0 == m)
      continue;
    int vcount1 = m->m_V.Count();
    if (vcount1 <= 0)
      continue;
    int fcount1 = m->m_F.Count();
    if (fcount1 > 0)
    {
      j = m_F.Count();
      m_F.Append(fcount1, m->m_F.Array());
      fcount1 += j;
      while (j < fcount1)
      {
        vi = m_F[j].vi;
        vi[0] += (int)vcount0_local;
        vi[1] += (int)vcount0_local;
        vi[2] += (int)vcount0_local;
        vi[3] += (int)vcount0_local;
        j++;
      }
    }
    m_V.Append(vcount1, m->m_V.Array());
    if (m->HasNgons())
    {
      if (0 != m->NgonMap())
        bHasNgonMap = true;
      m_NgonMap.Destroy();
      unsigned int ngon_count = m->NgonUnsignedCount();
      for (unsigned int ni = 0; ni < ngon_count; ni++)
      {
        const ON_MeshNgon* ngon0 = m->Ngon(ni);
        if (0 == ngon0)
          continue;
        if (0 == ngon0->m_Vcount && 0 == ngon0->m_Fcount)
          continue;
        ON_MeshNgon* ngon1 = this->m_NgonAllocator.CopyNgon(ngon0);
        if (0 == ngon1)
          continue;
        for (unsigned int nvi = 0; nvi < ngon1->m_Vcount; nvi++)
        {
          ngon1->m_vi[nvi] += vcount0_local;
        }
        for (unsigned int nfi = 0; nfi < ngon1->m_Fcount; nfi++)
        {
          ngon1->m_fi[nfi] += fcount0_local;
        }
        this->AddNgon(ngon1);
      }
    }
  }

  if (bHasDoubles)
  {
    // Now update the double precision vertex locations.
    m_dV.Reserve(vcount);
    for (mi = 0; mi < mesh_count; mi++)
    {
      m = meshes[mi];
      if (0 == m || m->m_dV.Count() <= 0)
        continue;
      m_dV.Append(m->m_dV.Count(), m->m_dV.Array());
    }
    if (m_dV.Count() != vcount)
      bHasDoubles = false;
  }

  if (false == bHasDoubles)
  {
    bHasDoubles = false;
    DestroyDoublePrecisionVertices();
  }

  if (bHasVertexNormals)
  {
    m_N.Reserve(vcount);
    for (mi = 0; mi < mesh_count; mi++)
    {
      m = meshes[mi];
      if (0 == m)
        continue;
      m_N.Append(m->m_N.Count(), m->m_N.Array());
    }
  }
  else
  {
    m_N.Destroy();
  }


  if (bHasFaceNormals)
  {
    m_FN.Reserve(fcount);
    for (mi = 0; mi < mesh_count; mi++)
    {
      m = meshes[mi];
      if (0 == m || m->m_V.Count() <= 0)
        continue;
      m_FN.Append(m->m_FN.Count(), m->m_FN.Array());
    }
  }
  else
  {
    m_FN.Destroy();
  }

  if (bHasTextureCoordinates)
  {
    m_T.Reserve(vcount);
    for (mi = 0; mi < mesh_count; mi++)
    {
      m = meshes[mi];
      if (0 == m)
        continue;
      m_T.Append(m->m_T.Count(), m->m_T.Array());
    }
  }
  else
  {
    m_T.Destroy();
  }


  if (bHasSurfaceParameters)
  {
    m_S.Reserve(vcount);
    for (mi = 0; mi < mesh_count; mi++)
    {
      m = meshes[mi];
      if (0 == m)
        continue;
      m_S.Append(m->m_S.Count(), m->m_S.Array());
    }
  }
  else
  {
    m_S.Destroy();
  }

  if (bHasPrincipalCurvatures)
  {
    m_K.Reserve(vcount);
    for (mi = 0; mi < mesh_count; mi++)
    {
      m = meshes[mi];
      if (0 == m)
        continue;
      m_K.Append(m->m_K.Count(), m->m_K.Array());
    }
  }
  else
  {
    m_K.Destroy();
  }

  if (bHasVertexColors)
  {
    m_C.Reserve(vcount);
    for (mi = 0; mi < mesh_count; mi++)
    {
      m = meshes[mi];
      if (0 == m)
        continue;
      m_C.Append(m->m_C.Count(), m->m_C.Array());
    }
  }
  else
  {
    m_C.Destroy();
  }

  if (0 != m_mesh_parameters)
  {
    for (mi = 0; mi < mesh_count; mi++)
    {
      m = meshes[mi];
      if (0 == m)
        continue;
      if (0 == m->m_mesh_parameters || *m_mesh_parameters != *m->m_mesh_parameters)
      {
        delete m_mesh_parameters;
        m_mesh_parameters = 0;
        break;
      }
    }
  }

  for (j = 0; j < 4; j++)
  {
    if (m_kstat[j])
    {
      // will be recomputed if required
      delete m_kstat[j];
      m_kstat[j] = 0;
    }
  }

  bool bAllowNewCachedTCs = (vcount0 == 0);
  for (mi = 0; mi < mesh_count; mi++)
  {
    m = meshes[mi];
    if (0 == m)
      continue;

    if (bAllowNewCachedTCs)
    {
      m_TC = m->m_TC;
      bAllowNewCachedTCs = false;
    }
    else
    {
      for (int tci = 0; tci < m_TC.Count(); tci++)
      {
        bool bKeep = false;
        for (int tcimi = 0; tcimi < m->m_TC.Count(); tcimi++)
        {
          if (m_TC[tci].m_tag == m->m_TC[tcimi].m_tag)
          {
            m_TC[tci].m_T.Append(m->m_TC[tcimi].m_T.Count(), m->m_TC[tcimi].m_T.Array());
            bKeep = true;
          }
        }
        if (!bKeep)
        {
          m_TC.Remove(tci);
          tci--;
        }
      }
    }
  }

  SetClosed(-99);
  SetSolidOrientation(-99);
  InvalidateBoundingBoxes();

  if (NgonCount() > 0 && bHasNgonMap)
    CreateNgonMap();

  if (bSetMeshParameters && nullptr != mp && mp != this->MeshParameters())
  {
    // Appending to an empty this and all appendees have matching mesh parameters.
    this->SetMeshParameters(*mp);
  }
}

void ON_Mesh::Append(const ON_Mesh& m)
{
  const ON_Mesh* meshes[1];
  meshes[0] = &m;
  Append(1, meshes);
}


ON_MeshParameters::MESH_STYLE ON_MeshParameters::MeshStyleFromUnsigned(
  unsigned int mesh_style_as_unsigned
)
{
  switch (mesh_style_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_STYLE::unset_mesh_style);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_STYLE::render_mesh_fast);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_STYLE::render_mesh_quality);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_STYLE::render_mesh_custom);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_STYLE::render_mesh_per_object);
  }

  ON_ERROR("Invalid mesh_style_as_unsigned parameter");
  return ON_MeshParameters::MESH_STYLE::unset_mesh_style;
}


ON_MeshParameters::MESH_PARAMETER_ID ON_MeshParameters::MeshParameterIdFromUnsigned(
  unsigned int mesh_parameter_id_as_unsigned
)
{
  switch (mesh_parameter_id_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::unspecified_mesh_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::bComputeCurvature_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::bSimplePlanes_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::bRefine_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::bJaggedSeams_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::bDoublePrecision_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::mesher_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::texture_range_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::tolerance_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::relative_tolerance_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::min_tolerance_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::min_edge_length_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::max_edge_length_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::grid_aspect_ratio_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::grid_min_count_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::grid_max_count_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::grid_angle_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::grid_amplification_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::refine_angle_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::face_type_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::srf_domain_parameter_id);

  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::bClosedObjectPostProcess_id);

  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::mesher_id);

  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::crv_tess_min_num_segments_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::crv_tess_angle_tol_in_degrees_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::crv_tess_max_dist_between_points_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::crv_tess_min_parametric_ratio_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::bEvaluatorBasedTessellation_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::srf_tess_chord_height_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::srf_tess_angle_tol_in_degrees_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::srf_tess_max_edge_length_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::srf_tess_min_edge_length_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::srf_tess_min_edge_length_ratio_uv_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::srf_tess_max_aspect_ratio_parameter_id);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::smoothing_passes_parameter_id);
  
  ON_ENUM_FROM_UNSIGNED_CASE(ON_MeshParameters::MESH_PARAMETER_ID::max_mesh_parameter_id);
  }
  
  ON_ERROR("Invalid mesh_parameter_id_as_unsigned parameter");
  return ON_MeshParameters::MESH_PARAMETER_ID::unspecified_mesh_parameter_id;

}

void ON_MeshParameters::Internal_SetCharHelper(unsigned int u, unsigned char minc, unsigned char maxc, unsigned char* dest)
{
  if (u > 255)
    return;
  const unsigned char c = (unsigned char)u;
  if (c >= minc && c <= maxc && c != *dest)
  {
    m_geometry_settings_hash = ON_SHA1_Hash::ZeroDigest;
    *dest = c;
  }
}

void ON_MeshParameters::Internal_SetBoolHelper(bool b, bool* dest)
{
  b = b ? true : false;
  if (b != *dest)
  {
    m_geometry_settings_hash = ON_SHA1_Hash::ZeroDigest;
    *dest = b;
  }
}

void ON_MeshParameters::Internal_SetDoubleHelper(double x, double minx, double maxx, double* dest)
{
  if (!ON_IsValid(x))
    return;
  if (ON_UNSET_VALUE != minx && !(x >= minx))
    return;
  if (ON_UNSET_VALUE != maxx && !(x <= maxx))
    return;
  if (x == *dest)
    return;
  m_geometry_settings_hash = ON_SHA1_Hash::ZeroDigest;
  *dest = x;
}

void ON_MeshParameters::Internal_SetIntHelper(int i, int mini, int maxi, int* dest)
{
  if (!ON_IsValid(i))
    return;
  if (ON_UNSET_INT_INDEX != mini && !(i >= mini))
    return;
  if (ON_UNSET_INT_INDEX != maxi && !(i <= maxi))
    return;
  if (i == *dest)
    return;
  m_geometry_settings_hash = ON_SHA1_Hash::ZeroDigest;
  *dest = i;
}

const bool ON_MeshParameters::CustomSettings() const
{
  return m_bCustomSettings;
}

void ON_MeshParameters::SetCustomSettings(
  bool bCustomSettings
)
{
  Internal_SetBoolHelper(bCustomSettings, &m_bCustomSettings);
}

const bool ON_MeshParameters::CustomSettingsEnabled() const
{
  return m_bCustomSettingsEnabled;
}

void ON_MeshParameters::SetCustomSettingsEnabled(
  bool bCustomSettingsEnabled
)
{
  Internal_SetBoolHelper(bCustomSettingsEnabled, &m_bCustomSettingsEnabled);
}


const bool ON_MeshParameters::ComputeCurvature() const
{
  return m_bComputeCurvature;
}

void ON_MeshParameters::SetComputeCurvature(
  bool bComputeCurvature
)
{
  Internal_SetBoolHelper(bComputeCurvature, &m_bComputeCurvature);
  ON_SubDDisplayParameters smp = this->SubDDisplayParameters();
  smp.SetComputeCurvature(bComputeCurvature);
  this->SetSubDDisplayParameters(smp);
}



const bool ON_MeshParameters::SimplePlanes() const
{
  return m_bSimplePlanes;
}

void ON_MeshParameters::SetSimplePlanes(
  bool bSimplePlanes
)
{
  Internal_SetBoolHelper(bSimplePlanes, &m_bSimplePlanes);
}

ON_SubDComponentLocation ON_SubDComponentLocationFromUnsigned(
  unsigned int loc_as_unsigned
)
{
  switch (loc_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDComponentLocation::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDComponentLocation::ControlNet);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDComponentLocation::Surface);
  }

  ON_ERROR("Invalid loc_as_unsigned parameter");
  return ON_SubDComponentLocation::Unset;
}


void ON_MeshParameters::SetSubDDisplayParameters(
  const ON_SubDDisplayParameters& subd_parameters
)
{
  const unsigned char subd_mesh_paramters_as_char = subd_parameters.EncodeAsUnsignedChar();
  if (subd_mesh_paramters_as_char != m_subd_mesh_parameters_as_char)
  {
    m_geometry_settings_hash = ON_SHA1_Hash::ZeroDigest;
    m_subd_mesh_parameters_as_char = subd_mesh_paramters_as_char;
  }
}
  
const ON_SubDDisplayParameters ON_MeshParameters::SubDDisplayParameters() const
{
  return ON_SubDDisplayParameters::DecodeFromUnsignedChar(m_subd_mesh_parameters_as_char);
}

const bool ON_MeshParameters::Refine() const
{
  return m_bRefine;
}

void ON_MeshParameters::SetRefine(
  bool bRefine
)
{
  Internal_SetBoolHelper(bRefine, &m_bRefine);
}



const bool ON_MeshParameters::JaggedSeams() const
{
  return m_bJaggedSeams;
}

void ON_MeshParameters::SetJaggedSeams(
  bool bJaggedSeams
)
{
  Internal_SetBoolHelper(bJaggedSeams, &m_bJaggedSeams);
}

const bool ON_MeshParameters::DoublePrecision() const
{
  return m_bDoublePrecision;
}

void ON_MeshParameters::SetDoublePrecision(
  bool bDoublePrecision
)
{
  Internal_SetBoolHelper(bDoublePrecision, &m_bDoublePrecision);
}

const unsigned int ON_MeshParameters::Mesher() const
{ 
  return static_cast<unsigned int>(m_mesher);

}

void ON_MeshParameters::SetMesher(
  unsigned int mesher
)
{
  Internal_SetCharHelper(mesher, 0, 1, &m_mesher);
}

const unsigned int ON_MeshParameters::TextureRange() const
{
  return static_cast<unsigned int>(m_texture_range);
}

void ON_MeshParameters::SetTextureRange(
  unsigned int texture_range
)
{
  Internal_SetCharHelper(texture_range, 1, 2, &m_texture_range);
}

const bool ON_MeshParameters::TextureRangeIsValid() const
{
  return (1 == m_texture_range || 2 == m_texture_range);
}

void ON_MeshParameters::SetTextureRangePictureFrameHack()
{
  // A 2012 hack to fix cited issues. Search for calls in core Rhino
  // code for comments with more details.
  //   Fix http://mcneel.myjetbrains.com/youtrack/issue/RH-17042
  //     Setting mp.TextureRange() = 0 here fixes RH-17042.
  //     What's one more hack where picture frames are concerned?
  //     As of March 26, tech support felt this picture frame tc bug was
  //     so critical that we held up the release of Rhino 5 SR2
  //     for this fix.
  //
  //   In November of 2012, tech support felt the following
  //   five bugs were so critical, Rhino SR1 could not be released.
  //     http://dev.mcneel.com/bugtrack/?q=120560 = http://mcneel.myjetbrains.com/youtrack/issue/RH-15423
  //     http://dev.mcneel.com/bugtrack/?q=101150 = http://mcneel.myjetbrains.com/youtrack/issue/RH-12450
  //     http://dev.mcneel.com/bugtrack/?q=105787 = http://mcneel.myjetbrains.com/youtrack/issue/RH-13203
  //     http://dev.mcneel.com/bugtrack/?q=119292 = http://mcneel.myjetbrains.com/youtrack/issue/RH-15277
  //     http://dev.mcneel.com/bugtrack/?q=119294 = http://mcneel.myjetbrains.com/youtrack/issue/RH-15279
  //
  // Do not modify this code without testing all the bugs listed above.
  // If you modify this code, put in an extensive comment that includes
  // bug citations.
  unsigned int invalid_texture_range = 0;
  Internal_SetCharHelper(invalid_texture_range, 0, 0, &m_texture_range);
}


const bool ON_MeshParameters::ClosedObjectPostProcess() const
{
  return m_bClosedObjectPostProcess;
}
void ON_MeshParameters::SetClosedObjectPostProcess(
  bool bClosedObjectPostProcess
) 
{
  Internal_SetBoolHelper(bClosedObjectPostProcess, &m_bClosedObjectPostProcess);
}


const double ON_MeshParameters::Tolerance() const 
{
  return m_tolerance;
}

void ON_MeshParameters::SetTolerance(
  double tolerance
) 
{
  Internal_SetDoubleHelper(tolerance, 0.0, ON_UNSET_VALUE, &m_tolerance);
}

const double ON_MeshParameters::RelativeTolerance() const
{
  return m_relative_tolerance;
}

void ON_MeshParameters::SetRelativeTolerance(
  double relative_tolerance
)
{
  Internal_SetDoubleHelper(relative_tolerance, 0.0, 1.0, &m_relative_tolerance);
}
        
const double ON_MeshParameters::MinimumTolerance() const 
{
  return m_min_tolerance;
}

void ON_MeshParameters::SetMinimumTolerance(
  double minimum_tolerance
)
{
  Internal_SetDoubleHelper(minimum_tolerance, 0.0, ON_UNSET_VALUE, &m_min_tolerance);
}

const double ON_MeshParameters::MinimumEdgeLength() const
{ 
  return m_min_edge_length;
}

void ON_MeshParameters::SetMinimumEdgeLength(
  double minimum_edge_length
)
{
  // Allow 0.0 or values >= ON_ZERO_TOLERANCE
  const double minx
    = (0.0 == minimum_edge_length)
    ? 0.0
    : ON_ZERO_TOLERANCE;
  Internal_SetDoubleHelper(minimum_edge_length, minx, ON_UNSET_VALUE, &m_min_edge_length);
}

const double ON_MeshParameters::MaximumEdgeLength() const { return m_max_edge_length; }
void ON_MeshParameters::SetMaximumEdgeLength(
  double maximum_edge_length
) 
{
  Internal_SetDoubleHelper(maximum_edge_length, 0.0, ON_UNSET_VALUE, &m_max_edge_length);
}

const double ON_MeshParameters::GridAspectRatio() const
{
  return m_grid_aspect_ratio;
}

void ON_MeshParameters::SetGridAspectRatio(
  double grid_aspect_ratio
)
{
  Internal_SetDoubleHelper(grid_aspect_ratio, 0.0, ON_UNSET_VALUE, &m_grid_aspect_ratio);
}

const int ON_MeshParameters::GridMinCount() const
{
  return m_grid_min_count;
}

void ON_MeshParameters::SetGridMinCount(
  int grid_min_count
)
{
  Internal_SetIntHelper(grid_min_count, 0, ON_UNSET_INT_INDEX, &m_grid_min_count);
}

const int ON_MeshParameters::GridMaxCount() const
{
  return m_grid_max_count;
}

void ON_MeshParameters::SetGridMaxCount(
  int grid_max_count
)
{
  Internal_SetIntHelper(grid_max_count, 0, ON_UNSET_INT_INDEX, &m_grid_max_count);
}

const double ON_MeshParameters::GridAngleRadians() const
{
  return m_grid_angle_radians;
}

void ON_MeshParameters::SetGridAngleRadians(
  double grid_angle_radians
)
{
  if (grid_angle_radians > ON_PI && grid_angle_radians < (1.0 + ON_EPSILON)*2.0*ON_PI)
    grid_angle_radians = ON_PI;
  Internal_SetDoubleHelper(grid_angle_radians, 0.0, ON_PI, &m_grid_angle_radians);
}

const double ON_MeshParameters::GridAngleDegrees() const
{
  return ON_DegreesFromRadians(GridAngleRadians());
}

void ON_MeshParameters::SetGridAngleDegrees(
  double grid_angle_degrees
)
{
  SetGridAngleRadians(ON_RadiansFromDegrees(grid_angle_degrees));
}

const double ON_MeshParameters::GridAmplification() const
{
  return m_grid_amplification;
}

void ON_MeshParameters::SetGridAmplification(
  double grid_amplification
)
{
  Internal_SetDoubleHelper(grid_amplification, 0.0, ON_UNSET_VALUE, &m_grid_amplification);
}

const double ON_MeshParameters::RefineAngleRadians() const
{
  return m_refine_angle_radians;
}

void ON_MeshParameters::SetRefineAngleRadians(
  double refine_angle_radians
) 
{
  if (refine_angle_radians > ON_PI && refine_angle_radians < (1.0 + ON_EPSILON)*2.0*ON_PI)
    refine_angle_radians = ON_PI;
  Internal_SetDoubleHelper(refine_angle_radians, 0.0, ON_PI, &m_refine_angle_radians);
}


const double ON_MeshParameters::RefineAngleDegrees() const
{
  return ON_DegreesFromRadians(RefineAngleRadians());
}

void ON_MeshParameters::SetRefineAngleDegrees(
  double refine_angle_degrees
) 
{
  SetRefineAngleRadians(ON_RadiansFromDegrees(refine_angle_degrees));
}

const unsigned int ON_MeshParameters::FaceType() const
{
  return static_cast<unsigned int>(m_face_type);
}

void ON_MeshParameters::SetFaceType(
  unsigned int face_type
)
{
  Internal_SetCharHelper(face_type, 0, 2, &m_face_type);
}


ON_MeshParameters::ON_MeshParameters(
  double normalized_mesh_density,
  double min_edge_length
  )
{
  // non-default values
  SetTextureRange(0);
  SetGridAngleRadians(0.0);
  SetGridAmplification(0.0);
  SetRefineAngleRadians(0.0);
  SetMinimumEdgeLength(min_edge_length);

  if ( ON_IsValid(normalized_mesh_density) )
  {
    if (normalized_mesh_density < 0.0 )
      normalized_mesh_density = 0.0;
    else if (normalized_mesh_density > 1.0 )
      normalized_mesh_density = 1.0;
    SetRelativeTolerance(normalized_mesh_density);
    SetRefine((normalized_mesh_density < 0.65));
    SetSimplePlanes((0.0 == normalized_mesh_density));

    ON_SubDDisplayParameters subd_parameters = ON_SubDDisplayParameters::CreateFromMeshDensity(normalized_mesh_density);
    SetSubDDisplayParameters(subd_parameters);
  }
}

double ON_MeshParameters::ClampMeshDensityValue(double slider_value)
{
  // Make "fuzzy" values of 0.0, 0.5, and 1.0 exactly 0, 0.5, and 1.0 so
  // siders of various int resolutions and code that uses float instead 
  // of double precision values behaves in the expected way.
  if (slider_value >= -ON_SQRT_EPSILON && slider_value <= ON_SQRT_EPSILON)
    slider_value = 0.0;
  else if (slider_value >= (0.5 - ON_SQRT_EPSILON) && slider_value <= (0.5 + ON_SQRT_EPSILON))
    slider_value = 0.5;
  else if (slider_value >= (1.0 - ON_SQRT_EPSILON) && slider_value <= (1.0 + ON_SQRT_EPSILON))
    slider_value = 1.0;
  else if (false == (slider_value >= 0.0 && slider_value <= 1.0))
  {
    // If you get this error, your user interface code has a bug.
    ON_ERROR("Invalid slider_value - defaulting to 0.5");
    slider_value = 0.5; // invalid input treated as 0.5.
  }

  return slider_value;
}

const ON_wString ON_MeshParameters::Description() const
{
  ON_wString description;
  const double silder_value = this->MeshDensity();

  const ON_SHA1_Hash hash = this->GeometrySettingsHash();
  if (hash == ON_MeshParameters::FastRenderMesh.GeometrySettingsHash())
    description = ON_wString(L"Fast");
  else if (hash == ON_MeshParameters::QualityRenderMesh.GeometrySettingsHash())
    description = ON_wString(L"Quality");
  else if (silder_value >= 0.0 && silder_value <= 1.0)
    description = ON_wString::FormatToString(L"Density(%g%%)", ON_MeshParameters::MeshDensityAsPercentage(silder_value));
  else if (hash == ON_MeshParameters::DefaultAnalysisMesh.GeometrySettingsHash())
    description = ON_wString(L"DefaultAnalysis");
  else if (hash == ON_MeshParameters::DefaultMesh.GeometrySettingsHash())
    description = ON_wString(L"Default");
  else
  {
    description = ON_wString(L"Custom(");
    description += hash.ToString(true);
    description += L")";
  }

  return description;
}

const ON_MeshParameters ON_MeshParameters::CreateFromMeshDensity(double normalized_mesh_density)
{
  return ON_MeshParameters(ON_MeshParameters::ClampMeshDensityValue(normalized_mesh_density));
}

double ON_MeshParameters::MeshDensityAsPercentage(double normalized_mesh_density)
{
  if (normalized_mesh_density >= 0.0 && normalized_mesh_density <= 1.0)
  {
    const double percent_fuzz_tol = 1.0e-4;
    const double slider_percent = normalized_mesh_density * 100.0; // percent = slider_value as a percentage.
    const double n = floor(slider_percent + 0.25);
    if (fabs(n - slider_percent) <= percent_fuzz_tol)
      return n; // slider_percent is within fuzz of being an integer - return the integer

    const double p = 100.0*(floor(1024.0 * normalized_mesh_density + 0.25) / 1024.0);
    if (fabs(p - slider_percent) <= percent_fuzz_tol)
      return p; // slider_percent is within fuzz of 100.0*(N/1024.0). Return 100.0*(N/1024.0).

    return slider_percent; // return percentage with no fuzz removal
  }
  return ON_DBL_QNAN; // not a percent
}

double ON_MeshParameters::MeshDensity() const
{
  const bool bIgnoreSubDParameters = false;
  return MeshDensity(bIgnoreSubDParameters);
}

double ON_MeshParameters::MeshDensity(bool bIgnoreSubDParameters) const
{
  for (;;)
  {
    const double candidate_density = this->RelativeTolerance();
    if (false == (candidate_density >= 0.0 && candidate_density <= 1.0))
      break; // invalid candidate_density
    
    // 5 fast tests for quick rejection
    if ((this->m_bSimplePlanes ? 1 : 0) != ((0.0 == candidate_density) ? 1 : 0))
      break;
    if (false == (this->m_grid_angle_radians == 0.0))
      break;
    if (false == (this->m_grid_amplification == 0.0))
      break;
    if (false == (this->m_refine_angle_radians == 0.0))
      break;

    if (false == bIgnoreSubDParameters)
    {
      const ON_SubDDisplayParameters subdp = this->SubDDisplayParameters();
      if (subdp.DisplayDensityIsAbsolute())
        break; // mesh dialog "slider" UI is always controls adaptive subd display density
      if (subdp.DisplayDensity(ON_SubD::Empty) != ON_SubDDisplayParameters::CreateFromMeshDensity(candidate_density).DisplayDensity(ON_SubD::Empty))
        break;
    }

    // Now build one with the candidate_density slider value
    const ON_MeshParameters candidate_mp = ON_MeshParameters::CreateFromMeshDensity(candidate_density);

    if (candidate_mp.RelativeTolerance() != candidate_density)
      break;
    if (candidate_mp.GeometrySettingsHash(bIgnoreSubDParameters) != GeometrySettingsHash(bIgnoreSubDParameters))
      break;

    // These mesh parameters will create the same mesh geometry as ON_MeshParameters::CreateFromMeshDensity().
    return candidate_density;
  }

  return ON_DBL_QNAN;
}

double ON_MeshParameters::MinimumEdgeLengthFromTolerance( 
  double max_edge_length,
  double tolerance 
)
{
  // The 1.0e-4 is a guess.  1.0e-12 was too small to help with objects
  // like the one in 67885.
  double min_edge_length = 1.0e-4;
  if ( max_edge_length > 0.0 && min_edge_length > 1.0e-3*max_edge_length )
    min_edge_length =  1.0e-3*max_edge_length;
  if ( tolerance > 0.0 && min_edge_length > 1.0e-2*tolerance )
    min_edge_length =  1.0e-2*tolerance;
  return min_edge_length;
}

double ON_MeshParameters::ToleranceFromObjectSize(
  double relative_tolerance,
  double actual_size
)
{
  // min_rel_tol creates the most facets
  //const double min_rel_tol = 5.0e-5;

  //max rel tol creates the fewest facets
  //const double max_rel_tol = 0.1;
  //m_relative_tolerance = 0.0;
  //if ( relative_tolerance <= 0.0 )
  //  m_relative_tolerance = max_rel_tol;
  //else if ( relative_tolerance >= 1.0 )
  //  m_relative_tolerance = min_rel_tol;
  //else
  //{
  //  ON_Interval e(log10(max_rel_tol),log10(min_rel_tol));
  //  m_relative_tolerance = pow(10.0,e.ParameterAt(relative_tolerance));
  //}

  double tol = 0.0;
  double x, e;
  if ( ON_IsValid(relative_tolerance) && ON_IsValid(actual_size)
       && relative_tolerance > 0.0 && actual_size > 0.0 )
  {
    if ( relative_tolerance > 1.0 )
      relative_tolerance = 1.0;

    //e = (relative_tolerance*(12.0 + relative_tolerance*(2.0*relative_tolerance - 9.0)));
    //e = (1.0 + relative_tolerance*(8.0 - 4.0*relative_tolerance));
    //e = 1.0 + relative_tolerance*4.0;
    //x = 5.0*pow(10.0,-e);

    e = (relative_tolerance < 0.5) 
      ? 1.0 + relative_tolerance*(6.0 - 4.0*relative_tolerance) // 1.0 + 4.0*relative_tolerance
      : 2.0 + 2.0*relative_tolerance;
    x = pow(10.0,-e);

    tol = actual_size*x;
  }
  return tol;
}

bool operator==(const ON_MeshParameters& a, const ON_MeshParameters& b)
{
  return 0 == ON_MeshParameters::Compare(a,b);
}

bool operator!=(const ON_MeshParameters& a, const ON_MeshParameters& b)
{
  return 0 != ON_MeshParameters::Compare(a,b);
}

void ON_MeshParameters::Dump( ON_TextLog& text_log ) const
{
  const ON_wString description = this->Description();
  text_log.Print(L"Description: %ls\n", static_cast<const wchar_t*>(description));
  text_log.Print(L"Gridding:\n");
  {
    const ON_TextLogIndent indent1(text_log);
    text_log.Print(L"Min grid count = %d\n", m_grid_min_count);
    text_log.Print(L"Max grid count = %d\n", m_grid_max_count);
    text_log.Print(L"Gridding angle = %g radians (%g degrees)\n", GridAngleRadians(), GridAngleDegrees());
    text_log.Print(L"Aspect ratio = %g\n", m_grid_aspect_ratio);
    text_log.Print(L"Amplification = %g\n", m_grid_amplification);
  }

  text_log.Print(L"Refining:\n");
  {
    const ON_TextLogIndent indent1(text_log);
    text_log.Print(L"Refine = %ls\n", m_bRefine ? L"true" : L"false");
    text_log.Print(L"Refine angle = %g radians (%g degrees)\n", RefineAngleRadians(), RefineAngleDegrees());
  }

  text_log.Print(L"Metrics:\n");
  {
    const ON_TextLogIndent indent1(text_log);
    text_log.Print(L"Tolerance from size 1 object = %g (relative tolerance = %g)\n", ON_MeshParameters::ToleranceFromObjectSize(RelativeTolerance(), 1.0), RelativeTolerance());
    text_log.Print(L"Minimum tolerance = %g\n", MinimumTolerance());
    text_log.Print(L"Tolerance = %g\n", m_tolerance);
    text_log.Print(L"Min edge length = %g\n", m_min_edge_length);
    text_log.Print(L"Max edge length = %g\n", m_max_edge_length);
  }

  text_log.Print(L"SubDMeshParameters:\n");
  {
    const ON_TextLogIndent indent1(text_log);
    this->SubDDisplayParameters().Dump(text_log);
  }

  text_log.Print(L"Miscellaneous:\n");
  {
    const ON_TextLogIndent indent1(text_log);
    text_log.Print(L"Face type = %d\n", m_face_type);
    text_log.Print(L"Compute curvature = %ls\n", m_bComputeCurvature ? L"true" : L"false");
    text_log.Print(L"Texture range = %d\n", m_texture_range);
    text_log.Print(L"Simple planes = %ls\n", m_bSimplePlanes ? L"true" : L"false");
    text_log.Print(L"Jagged Seams = %ls\n", m_bJaggedSeams ? L"true" : L"false");
    text_log.Print(L"Double Precision = %ls\n", m_bDoublePrecision ? L"true" : L"false");
    text_log.Print(L"Closed object mesh healing = %ls\n", ClosedObjectPostProcess() ? L"true" : L"false");
  }

  text_log.Print(L"Custom:\n");
  {
    const ON_TextLogIndent indent1(text_log);
    text_log.Print(L"Custom settings = %ls\n", m_bCustomSettings ? L"true" : L"false");
    text_log.Print(L"Custom settings enabled = %ls\n", m_bCustomSettingsEnabled ? L"true" : L"false");
    const ON_UUID id = MesherId();
    if (ON_UuidIsNotNil(id))
    {
      text_log.Print(L"Mesher ID = ");
      text_log.Print(id);
      text_log.PrintNewLine();
    }
  }
}

static double ON_MeshParameters_SHA1Double(double t, double default_value)
{
  return (ON_IsValid(t) && t > 0.0) ? t : default_value;
}

int ON_MeshParameters::Compare(
  const ON_MeshParameters& a,
  const ON_MeshParameters& b
  )
{
  return ON_SHA1_Hash::Compare(a.ContentHash(), b.ContentHash());
}

int ON_MeshParameters::CompareGeometrySettings(
  const ON_MeshParameters& a,
  const ON_MeshParameters& b
  )
{
  return CompareGeometrySettings(a, b, false);
}

int ON_MeshParameters::CompareGeometrySettings(
  const ON_MeshParameters& a,
  const ON_MeshParameters& b,
  const bool bIgnoreSubDParameters
  )
{
  return ON_SHA1_Hash::Compare(a.GeometrySettingsHash(bIgnoreSubDParameters), b.GeometrySettingsHash(bIgnoreSubDParameters));
}

ON_SHA1_Hash ON_MeshParameters::ContentHash() const
{
  // Please discuss any changes with Dale Lear

  // These values are intentionally ignored
  //   m_bCustomSettingsEnabled
  //   m_bDoublePrecision

  // Use ON_MeshParameters::GeometrySettingsHash() if you want to ignore any of these values, like m_bComputeCurvature.
  ON_SHA1 sha1;
  sha1.AccumulateBool(m_bCustomSettings);
  sha1.AccumulateBool(m_bComputeCurvature); 
  sha1.AccumulateUnsigned32(m_texture_range);
  sha1.AccumulateUnsigned32(m_bClosedObjectPostProcess);

  const ON_SHA1_Hash geometry_settings_hash = GeometrySettingsHash();
  sha1.AccumulateSubHash(geometry_settings_hash);

  if (ON_UuidIsNil(m_mesher_id))
  {
    // When m_mesher_id is nil, the Pangolin parameters are not included in 
    // GeometrySettingsHash() because they do not apply.
    // Since ContentHash() is a hash of every ON_MeshParameters setting,
    // the Pangolin get accumulated here.
    sha1.AccumulateId(m_mesher_id);

    // Pangolin parameters
    Internal_AccumulatePangolinParameters(ON_MeshParameters::DefaultMesh, sha1);
  }

  return sha1.Hash();
}

void ON_MeshParameters::Internal_AccumulatePangolinParameters(
  const ON_MeshParameters & pangolin_defaults,
  ON_SHA1& sha1
) const
{
  // Pangolin parameters
  if (pangolin_defaults.m_bEvaluatorBasedTessellation != m_bEvaluatorBasedTessellation)
    sha1.AccumulateBool(m_bEvaluatorBasedTessellation);
  if (pangolin_defaults.m_curve_tess_min_num_segments != m_curve_tess_min_num_segments)
    sha1.AccumulateInteger32(m_curve_tess_min_num_segments);
  if (pangolin_defaults.m_curve_tess_angle_tol_in_degrees != m_curve_tess_angle_tol_in_degrees)
    sha1.AccumulateDouble(m_curve_tess_angle_tol_in_degrees);
  if (pangolin_defaults.m_curve_tess_max_dist_between_points != m_curve_tess_max_dist_between_points)
    sha1.AccumulateDouble(m_curve_tess_max_dist_between_points);
  if (pangolin_defaults.m_curve_tess_min_parametric_ratio != m_curve_tess_min_parametric_ratio)
    sha1.AccumulateDouble(m_curve_tess_min_parametric_ratio);
  if (pangolin_defaults.m_surface_tess_angle_tol_in_degrees != m_surface_tess_angle_tol_in_degrees)
    sha1.AccumulateDouble(m_surface_tess_angle_tol_in_degrees);
  if (pangolin_defaults.m_surface_tess_max_edge_length != m_surface_tess_max_edge_length)
    sha1.AccumulateDouble(m_surface_tess_max_edge_length);
  if (pangolin_defaults.m_surface_tess_min_edge_length != m_surface_tess_min_edge_length)
    sha1.AccumulateDouble(m_surface_tess_min_edge_length);
  if (pangolin_defaults.m_surface_tess_min_edge_length_ratio_uv != m_surface_tess_min_edge_length_ratio_uv)
    sha1.AccumulateDouble(m_surface_tess_min_edge_length_ratio_uv);
  if (pangolin_defaults.m_surface_tess_max_aspect_ratio != m_surface_tess_max_aspect_ratio)
    sha1.AccumulateDouble(m_surface_tess_max_aspect_ratio);
  if (pangolin_defaults.m_smoothing_passes != m_smoothing_passes)
    sha1.AccumulateInteger32(m_smoothing_passes);
}


ON_SHA1_Hash ON_MeshParameters::GeometrySettingsHash() const
{
  bool bIgnoreSubDParameters = false;
  return GeometrySettingsHash(bIgnoreSubDParameters);
}

ON_SHA1_Hash ON_MeshParameters::GeometrySettingsHash(bool bIgnoreSubDParameters) const
{
  // Please discuss any changes with Dale Lear

  // These values are intentionally ignored.
  //   m_bCustomSettings
  //   m_bCustomSettingsEnabled
  //   m_bComputeCurvature
  //   m_bDoublePrecision
  //   m_bClosedObjectPostProcess
  //   m_texture_range
  //   If they are included here, Rhino will remesh when it should not because it treats
  //   Texture coordinates as a mutable property (const_cast widely used in Rhino).
  //   Curvature is added/removed from analysis mode as needed.
  //   Custom settings controls where the mesh settings come from and when they 
  //   match what was used to create an existing mesh, a remesh is extremely wasteful,
  //   ClosedObjectPostProcess is added/removed as needed and is a hack to cover up core bugs.

  if (bIgnoreSubDParameters || m_geometry_settings_hash.IsZeroDigest())
  {
    ON_SHA1 sha1;
    sha1.AccumulateBool(m_bSimplePlanes);
    sha1.AccumulateBool(m_bRefine);
    sha1.AccumulateBool(m_bJaggedSeams);
    sha1.AccumulateUnsigned32(m_mesher);
    sha1.AccumulateDouble(ON_MeshParameters_SHA1Double(m_tolerance,0.0));
    sha1.AccumulateDouble(ON_MeshParameters_SHA1Double(m_relative_tolerance,0.0));

    // Do not include m_min_tolerance as a geometry setting.
    // It is a runtime lower bound clamp.
    // If it is included here, Rhino will remesh everytime model tolerance changes.
    sha1.AccumulateDouble(ON_MeshParameters_SHA1Double(m_min_edge_length,0.0));
    sha1.AccumulateDouble(ON_MeshParameters_SHA1Double(m_max_edge_length,0.0));
    sha1.AccumulateDouble(ON_MeshParameters_SHA1Double(m_grid_aspect_ratio,0.0));
    sha1.AccumulateInteger32(m_grid_min_count);
    sha1.AccumulateInteger32(m_grid_max_count);
    sha1.AccumulateDouble(ON_MeshParameters_SHA1Double(m_grid_angle_radians,ON_PI));
    sha1.AccumulateDouble(ON_MeshParameters_SHA1Double(m_refine_angle_radians,0.0));
    sha1.AccumulateDouble(ON_MeshParameters_SHA1Double(m_grid_amplification,1.0));
    sha1.AccumulateUnsigned32(m_face_type);

    if (false == bIgnoreSubDParameters)
    {
      // 2023-05-12, Pierre: Changes in RH-50501 make ON_MeshParameters::SetComputeCurvature also
      // act on the SubD mesh parameters, and I believe this is good (keeping the compute curvature bit
      // in sync between Brep meshing parameters and SubD mesh parameters). This means Breps with
      // compute curvature on also have non-default SubD meshing parameters (they always have the SubD
      // parameters, they just used to be default).
      // These values are intentionally ignored:
      //   m_reserved
      //   m_context
      //   m_bComputeCurvature
      //   m_reserved3
      //   m_reserved4
      //   m_reserved5
      //   m_reserved6
      //   m_reserved7
      //   m_terminator
      //   m_progress_reporter
      //   m_progress_reporter_interval
      ON_SubDDisplayParameters subd_params{
          ON_SubDDisplayParameters::DecodeFromUnsignedChar(m_subd_mesh_parameters_as_char)};
      sha1.AccumulateBool(subd_params.DisplayDensityIsAbsolute());
      sha1.AccumulateUnsigned8((ON__UINT8)subd_params.GetRawDisplayDensityForExperts());  // display density fits in a char
      sha1.AccumulateBool(subd_params.MeshLocation() == ON_SubDComponentLocation::ControlNet);
    }

    if (ON_UuidIsNotNil(m_mesher_id))
    {
      // The Pangolin parameters and any other, parameters we add in the future,
      // contribute to the SHA1 only when they differ from default values.
      // This keeps old SHA-1 values correct and prevents remeshing when openning
      // old files.
      sha1.AccumulateId(m_mesher_id);

      // Pangolin parameters
      Internal_AccumulatePangolinParameters(ON_MeshParameters::DefaultMesh, sha1);
    }
    
    if (bIgnoreSubDParameters)
      return sha1.Hash();

    m_geometry_settings_hash = sha1.Hash();
  }
  return m_geometry_settings_hash;
}

ON_UUID ON_MeshParameters::MesherId() const
{
  return m_mesher_id;
}

void ON_MeshParameters::SetMesherId(
  ON_UUID id
)
{
  if (id != m_mesher_id)
  {
    m_geometry_settings_hash = ON_SHA1_Hash::ZeroDigest;
    m_mesher_id = id;
  }
}


const ON_MeshParameters::MESH_STYLE ON_MeshParameters::GeometrySettingsRenderMeshStyle(
  const ON_MeshParameters* custom_mp,
  MESH_STYLE no_match_found_result
  ) const
{
  if ( 0 == ON_MeshParameters::CompareGeometrySettings(ON_MeshParameters::FastRenderMesh,*this))
    return ON_MeshParameters::MESH_STYLE::render_mesh_fast;

  if ( 0 == ON_MeshParameters::CompareGeometrySettings(ON_MeshParameters::QualityRenderMesh,*this))
    return ON_MeshParameters::MESH_STYLE::render_mesh_quality;

  if ( 0 != custom_mp && 0 == ON_MeshParameters::CompareGeometrySettings(*custom_mp,*this))
    return ON_MeshParameters::MESH_STYLE::render_mesh_custom;

  return no_match_found_result;
}

const int ON_MeshParameters::GeometrySettingsDensityPercentage(
  int no_match_found_result
  ) const
{
  const double slider_value = this->MeshDensity();
  if (slider_value >= 0.0 && slider_value <= 1.0)
  {
    const int n = (int)floor(100.0 * slider_value + 0.4999);
    if (n >= 0 && n <= 100)
      return n;

    // The code BELOW is slower and less reliable. Different platforms and code convert 
    // user interface int values to normalized double "slider value" slightly differently.
    // (Some user interface controls use int ranges that are not multiples of 10 or are greater than 100).
    // The code ABOVE will insures if a "simple slider" user interface set the mesh parameters,
    // then this function will return an integer between 0 and 100 that produces
    // identical or nearly identical meshing parameters.
    //
    // NO //for (int n = 0; n <= 100; n++)
    // NO //{
    // NO //  double density = (50 == n) ? 0.5 : (n / 100.0);
    // NO //  ON_MeshParameters mp_at_n = ON_MeshParameters::CreateFromMeshDensity(density);
    // NO //  mp_at_n.m_bDoublePrecision = m_bDoublePrecision;
    // NO //  mp_at_n.m_texture_range = m_texture_range;
    // NO //  if (0 == ON_MeshParameters::CompareGeometrySettings(mp_at_n, *this))
    // NO //    return n;
    // NO //}
  }
  return no_match_found_result;
}

ON__UINT32 ON_MeshParameters::DataCRC(ON__UINT32 current_remainder) const
{
  const ON_SHA1_Hash content_hash = ContentHash();
  const ON__UINT32 crc = ON_CRC32(current_remainder,sizeof(content_hash),&content_hash);  
  return crc;
}

bool ON_MeshParameters::Write( ON_BinaryArchive& file ) const
{
  int minor_version = 5; 
  bool rc = file.Write3dmChunkVersion(1,minor_version);
  if (rc) 
  {
    if (rc) rc = file.WriteInt(m_bComputeCurvature);
    if (rc) rc = file.WriteInt(m_bSimplePlanes);
    if (rc) rc = file.WriteInt(m_bRefine);
    if (rc) rc = file.WriteInt(m_bJaggedSeams);
    if (rc) rc = file.WriteInt(0); // obsolete m_bWeld field
    if (rc) rc = file.WriteDouble(m_tolerance);
    if (rc) rc = file.WriteDouble(m_min_edge_length);
    if (rc) rc = file.WriteDouble(m_max_edge_length);
    if (rc) rc = file.WriteDouble(m_grid_aspect_ratio);
    if (rc) rc = file.WriteInt(m_grid_min_count);
    if (rc) rc = file.WriteInt(m_grid_max_count);
    if (rc) rc = file.WriteDouble(m_grid_angle_radians);
    if (rc) rc = file.WriteDouble(m_grid_amplification);
    if (rc) rc = file.WriteDouble(m_refine_angle_radians);
    if (rc) rc = file.WriteDouble(5.0*ON_PI/180.0); // obsolete m_combine_angle field
    int mft = m_face_type;
    if ( mft < 0 || mft > 2 ) 
    {
      ON_ERROR("ON_MeshParameters::Write() - m_face_type out of bounds.");
      mft = 0;
    }
    if (rc) rc = file.WriteInt(mft);

    // added for chunk version 1.1
    if (rc) rc = file.WriteInt( m_texture_range );

    // added for chunk version 1.2 - 14 October 2005
    if (rc) rc = file.WriteBool( m_bCustomSettings );
    if (rc) rc = file.WriteDouble( m_relative_tolerance );
    // DO NOT SAVE m_min_tolerance - yet ??

    // added for chunk version 1.3 - 20 February 2006
    if (rc) rc = file.WriteChar(m_mesher);

    // added for chunk version 1.4 - 3 March 2011
    if (rc) rc = file.WriteBool( m_bCustomSettingsEnabled );

    if (rc)
    {
      // added for chunk version 1.5 - June 19, 2020
      const ON_SubDDisplayParameters subdp = SubDDisplayParameters();
      rc = subdp.Write(file);
    }
  }
  return rc;
}

/*ON_MeshParameters::Type GeometrySettingsType(
    bool bIgnoreSubDParameters
  ) const*/
enum ON_MeshParameters::Type ON_MeshParameters::GeometrySettingsType() const
{
  const bool bIgnoreSubDParameters = false;
  return GeometrySettingsType(bIgnoreSubDParameters);
}

enum ON_MeshParameters::Type ON_MeshParameters::GeometrySettingsType(bool bIgnoreSubDParameters) const
{
  const ON_SHA1_Hash mp_hash = GeometrySettingsHash(bIgnoreSubDParameters);

  if ( mp_hash == ON_MeshParameters::DefaultMesh.GeometrySettingsHash(bIgnoreSubDParameters))
    return ON_MeshParameters::Type::Default;
  if ( mp_hash == ON_MeshParameters::FastRenderMesh.GeometrySettingsHash(bIgnoreSubDParameters))
    return ON_MeshParameters::Type::FastRender;
  if ( mp_hash == ON_MeshParameters::QualityRenderMesh.GeometrySettingsHash(bIgnoreSubDParameters))
    return ON_MeshParameters::Type::QualityRender;
  if ( mp_hash == ON_MeshParameters::DefaultAnalysisMesh.GeometrySettingsHash(bIgnoreSubDParameters))
    return ON_MeshParameters::Type::DefaultAnalysis;

  const double mesh_density = MeshDensity();
  if (mesh_density == RelativeTolerance())
    return ON_MeshParameters::Type::FromMeshDensity;

  return ON_MeshParameters::Type::Custom;
}

static bool Internal_MeshParametersRead_UpdateSubDParameters(
  const unsigned archive_opennurbs_version,
  ON_MeshParameters& archive_mp
)
{
  // Returns true if subd settings get updated.

  if (ON_MeshParameters::Type::Custom != archive_mp.GeometrySettingsType())
    return false; // a current built-in type - common and leave the as is.

  /*
  The adaptive SubD stuff appeared in early Nov 2020. The Dec 1 2020 date gives the changes
  time to work through the build and distribution processes.
  */
  const unsigned before_adaptive_subd_display = ON_VersionNumberConstruct(7, 1, 2020, 12, 1, 0);
  if (archive_opennurbs_version >= before_adaptive_subd_display)
    return false;

  // Adaptive SubD meshing was added Nov 11 and the way m_relative_tolerance set the subd density changed.
  // Version check padded to Dec 1, 2020 to give time for this code to get committed and built into daily distribution. 
  const ON_SHA1_Hash archive_mp_hash = archive_mp.GeometrySettingsHash();
  const ON_SubDDisplayParameters archive_subdp = archive_mp.SubDDisplayParameters();

  ON_MeshParameters mp[] = {
    ON_MeshParameters::DefaultMesh,
    ON_MeshParameters::FastRenderMesh,
    ON_MeshParameters::QualityRenderMesh,
    ON_MeshParameters::DefaultAnalysisMesh,
    ON_MeshParameters::CreateFromMeshDensity(archive_mp.RelativeTolerance())
  };

  const size_t mp_count = sizeof(mp) / sizeof(mp[0]);
  for (size_t mp_dex = 0; mp_dex < mp_count; ++mp_dex)
  {
    // If the only geometry setting difference between a built-in type and archive_mp
    // is the subd meshing parameters, update archive_mp to use the built-in's subd 
    // meshing parameters.
    const ON_SubDDisplayParameters mp_subdp = mp[mp_dex].SubDDisplayParameters();
    mp[mp_dex].SetSubDDisplayParameters(archive_subdp);
    if (archive_mp_hash == mp[mp_dex].GeometrySettingsHash())
    {
      // Update archive_mp to use new SubD defaults in mp_subdp.
      // This prevents "this" from being treated as customized instead
      // of one the the defaults and things will work as expected 
      // going forward in time with this model.
      archive_mp.SetSubDDisplayParameters(mp_subdp);
      return true;
    }
  }

  return false;
}

bool ON_MeshParameters::Read( ON_BinaryArchive& file )
{
  *this = ON_MeshParameters::DefaultMesh;
  m_geometry_settings_hash = ON_SHA1_Hash::ZeroDigest;

  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if ( rc && major_version == 1 ) 
  {
    int i;

    i = m_bComputeCurvature;
    if (rc) rc = file.ReadInt(&i);
    m_bComputeCurvature = i?true:false;

    i = m_bSimplePlanes;
    if (rc) rc = file.ReadInt(&i);
    m_bSimplePlanes = i?true:false;

    i = m_bRefine;
    if (rc) rc = file.ReadInt(&i);
    m_bRefine = i?true:false;

    i = m_bJaggedSeams;
    if (rc) rc = file.ReadInt(&i);
    m_bJaggedSeams = i?true:false;

    int obsolete_m_bWeld;
    if (rc) rc = file.ReadInt(&obsolete_m_bWeld);

    if (rc) rc = file.ReadDouble(&m_tolerance);
    if (rc) rc = file.ReadDouble(&m_min_edge_length);
    if (rc) rc = file.ReadDouble(&m_max_edge_length);
    if (rc) rc = file.ReadDouble(&m_grid_aspect_ratio);
    if (rc) rc = file.ReadInt(&m_grid_min_count);
    if (rc) rc = file.ReadInt(&m_grid_max_count);
    if (rc) rc = file.ReadDouble(&m_grid_angle_radians);
    if (rc) rc = file.ReadDouble(&m_grid_amplification);
    if (rc) rc = file.ReadDouble(&m_refine_angle_radians);
    double obsolete_m_combine_angle;
    if (rc) rc = file.ReadDouble(&obsolete_m_combine_angle);
    unsigned int face_type = FaceType();
    if (rc) rc = file.ReadInt(&face_type);
    if (rc) 
      SetFaceType(face_type);

    if ( rc && minor_version >= 1 ) 
    {
      unsigned int texture_range = TextureRange();
      rc = file.ReadInt( &texture_range );
      if (rc)
        SetTextureRange(texture_range);
      if ( rc && minor_version >= 2 )
      {
        rc = file.ReadBool(&m_bCustomSettings);
        if (rc) rc = file.ReadDouble(&m_relative_tolerance);
        if ( rc && minor_version >= 3 )
        {
          unsigned char mesher = (unsigned char)Mesher();
          rc = file.ReadChar(&mesher);
          if (rc)
            SetMesher(mesher);
          if ( rc && minor_version >= 4 )
          {
            rc = file.ReadBool(&m_bCustomSettingsEnabled);
            if (rc && minor_version >= 5)
            {
              ON_SubDDisplayParameters subdp = ON_SubDDisplayParameters::Default;
              rc = subdp.Read(file);
              if (rc)
              {
                this->SetSubDDisplayParameters(subdp);
                Internal_MeshParametersRead_UpdateSubDParameters(file.ArchiveOpenNURBSVersion(), *this);
              }
            }
          }
        }
      }
    }
  }

  return rc;
}

bool ON_SubDDisplayParameters::Write(class ON_BinaryArchive& archive) const
{
  if (false == archive.BeginWrite3dmAnonymousChunk(3))
    return false;
  bool rc = false;
  for(;;)
  {
    const unsigned int display_density = this->m_display_density;
    if (false == archive.WriteInt(display_density))
      break;

    const ON_SubDComponentLocation loc = this->MeshLocation();
    const unsigned int loc_as_unsigned = static_cast<unsigned char>(loc);
    if (false == archive.WriteInt(loc_as_unsigned))
      break;

    if (false == archive.WriteBool(this->m_bDisplayDensityIsAbsolute))
      break;

    if (false == archive.WriteBool(this->m_bComputeCurvature))
      break;

    rc = true;
    break;
  }
  if (false == archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_SubDDisplayParameters::Read(class ON_BinaryArchive& archive)
{
  *this = ON_SubDDisplayParameters::Default;
  int chunk_version = 0;
  if (false == archive.BeginRead3dmAnonymousChunk(&chunk_version))
    return false;
  bool rc = false;
  for (;;)
  {
    if (chunk_version <= 0)
      break;

    unsigned int display_density = this->DisplayDensity(ON_SubD::Empty);
    if (false == archive.ReadInt(&display_density))
      break;
    SetAdaptiveDisplayDensity(display_density);

    unsigned int loc_as_unsigned = static_cast<unsigned char>(this->MeshLocation());
    if (false == archive.ReadInt(&loc_as_unsigned))
      break;
    const ON_SubDComponentLocation loc = ON_SubDComponentLocationFromUnsigned(loc_as_unsigned);
    SetMeshLocation(loc);

    if (chunk_version >= 2)
    {
      bool bDisplayDensityIsAbsolute = false;
      if (false == archive.ReadBool(&bDisplayDensityIsAbsolute))
        break;
      if (bDisplayDensityIsAbsolute)
        this->SetAbsoluteDisplayDensity(display_density);

      if (chunk_version >= 3)
      {
        bool bComputeCurvature = false;
        if (false == archive.ReadBool(&bComputeCurvature))
          break;
        this->SetComputeCurvature(bComputeCurvature);
      }
    }

    rc = true;
    break;
  }
  if (false == archive.EndRead3dmChunk())
    rc = false;
  return rc;
}


ON_MeshCurvatureStats::ON_MeshCurvatureStats()
{
  Destroy(); // initializes defaults
}

ON_MeshCurvatureStats::~ON_MeshCurvatureStats()
{}

void ON_MeshCurvatureStats::Destroy()
{
  m_style = ON::unknown_curvature_style;
  m_infinity = 0.0;
  m_count_infinite = 0;
  m_count = 0;
  m_mode = 0.0;
  m_average = 0.0;
  m_adev = 0.0;
  m_range.Set(0.0,0.0);
}

void ON_MeshCurvatureStats::EmergencyDestroy()
{
  Destroy(); // - no memory is freed so Destroy() will work
}

ON_MeshCurvatureStats::ON_MeshCurvatureStats(const ON_MeshCurvatureStats& src)
{
  *this = src;
}

ON_MeshCurvatureStats& ON_MeshCurvatureStats::operator=(const ON_MeshCurvatureStats& src)
{
  if ( this != &src ) {
    m_style          = src.m_style;
    m_infinity       = src.m_infinity;
    m_count_infinite = src.m_count_infinite;
    m_count          = src.m_count;
    m_mode           = src.m_mode;
    m_average        = src.m_average;
    m_adev           = src.m_adev;
    m_range          = src.m_range;
  }
  return *this;
}

bool ON_MeshCurvatureStats::Write( ON_BinaryArchive& file ) const
{
  int i;
  bool rc = file.Write3dmChunkVersion(1,1);
  if (rc) {
    i = m_style;
    if (rc) rc = file.WriteInt(i);
    if (rc) rc = file.WriteDouble(m_infinity);
    if (rc) rc = file.WriteInt(m_count_infinite);
    if (rc) rc = file.WriteInt(m_count);
    if (rc) rc = file.WriteDouble(m_mode);
    if (rc) rc = file.WriteDouble(m_average);
    if (rc) rc = file.WriteDouble(m_adev);
    if (rc) rc = file.WriteInterval(m_range);
  }
  return rc;
}


bool ON_MeshCurvatureStats::Read( ON_BinaryArchive& file )
{
  int major_version = 0;
  int minor_version = 0;
  Destroy();
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if (rc && major_version == 1) {
    int i=0;
    if (rc) rc = file.ReadInt(&i);
    if (rc) m_style = ON::CurvatureStyle(i);
    if (rc) rc = file.ReadDouble(&m_infinity);
    if (rc) rc = file.ReadInt(&m_count_infinite);
    if (rc) rc = file.ReadInt(&m_count);
    if (rc) rc = file.ReadDouble(&m_mode);
    if (rc) rc = file.ReadDouble(&m_average);
    if (rc) rc = file.ReadDouble(&m_adev);
    if (rc) rc = file.ReadInterval(m_range);
  }
  return rc;
}

bool ON_MeshCurvatureStats::Set( ON::curvature_style kappa_style,
                                 int Kcount,
                                 const ON_SurfaceCurvature* K,
                                 const ON_3fVector* N, // needed for normal sectional curvatures
                                 double infinity
                                 )
{
  bool rc = (Kcount > 0 && K != nullptr);

  Destroy();

  if (rc) {
    ON_Workspace ws;
    //ON_3dVector tangent;
    double k;
    double* kappa = ws.GetDoubleMemory(Kcount);
    int i;

    switch( kappa_style ) {
    case ON::gaussian_curvature:
      m_style = kappa_style;
      m_infinity = ( infinity > 0.0 ) ? infinity : 1.0e20;
      break;
    case ON::mean_curvature: // unsigned mean
      m_style = kappa_style;
      m_infinity = ( infinity > 0.0 ) ? infinity : 1.0e10;
      break;
    case ON::min_curvature: // minimum unsigned radius of curvature
      m_style = kappa_style;
      m_infinity = ( infinity > 0.0 ) ? infinity : 1.0e10;
      break;
    case ON::max_curvature: // maximum unsigned radius of curvature
      m_style = kappa_style;
      m_infinity = ( infinity > 0.0 ) ? infinity : 1.0e10;
      break;
    //case ON::section_curvature_x:
    //  if ( !N )
    //    kappa_style = ON::unknown_curvature_style;
    //  m_style = kappa_style;
    //  m_infinity = ( infinity > 0.0 ) ? infinity : 1.0e10;
    //  break;
    //case ON::section_curvature_y:
    //  if ( !N )
    //    kappa_style = ON::unknown_curvature_style;
    //  m_style = kappa_style;
    //  m_infinity = ( infinity > 0.0 ) ? infinity : 1.0e10;
    //  break;
    //case ON::section_curvature_z:
    //  if ( !N )
    //    kappa_style = ON::unknown_curvature_style;
    //  m_style = kappa_style;
    //  m_infinity = ( infinity > 0.0 ) ? infinity : 1.0e10;
    //  break;
    default:
      rc = false;
      break;
    }

    for ( i = 0; i < Kcount; i++ ) {
      switch( kappa_style ) {
      case ON::gaussian_curvature:
        k = K[i].GaussianCurvature();
        break;
      case ON::mean_curvature: // unsigned mean
        k = fabs(K[i].MeanCurvature());
        break;
      case ON::min_curvature: // minimum unsigned radius of curvature
        k = fabs(K[i].MinimumRadius());
        break;
      case ON::max_curvature: // maximum unsigned radius of curvature
        k = fabs(K[i].MaximumRadius());
        break;
      //case ON::section_curvature_x:
      //  tangent.x = 0.0; tangent.y = -N[i].z; tangent.z = N[i].y;
      //  if ( fabs(tangent.y) <= ON_SQRT_EPSILON && fabs(tangent.z) <= ON_SQRT_EPSILON )
      //    tangent.Zero();
      //  else
      //    tangent.Unitize();
      //  k = fabs(K[i].NormalCurvature(tangent));
      //  break;
      //case ON::section_curvature_y:
      //  tangent.x = N[i].z; tangent.y = 0.0; tangent.z = -N[i].x;
      //  if ( fabs(tangent.x) <= ON_SQRT_EPSILON && fabs(tangent.z) <= ON_SQRT_EPSILON )
      //    tangent.Zero();
      //  else
      //    tangent.Unitize();
      //  k = fabs(K[i].NormalCurvature(tangent));
      //  break;
      //case ON::section_curvature_z:
      //  tangent.x = -N[i].y; tangent.y = N[i].x; tangent.z = 0.0;
      //  if ( fabs(tangent.x) <= ON_SQRT_EPSILON && fabs(tangent.y) <= ON_SQRT_EPSILON )
      //    tangent.Zero();
      //  else
      //    tangent.Unitize();
      //  k = fabs(K[i].NormalCurvature(tangent));
      //  break;
      default:
        k=0.0;
        break;
      }
      if ( fabs(k) >= m_infinity ) {
        m_count_infinite++;
        continue;
      }
      if ( m_count ) {
        if ( k < m_range.m_t[0] )
          m_range.m_t[0] = k;
        else if ( k > m_range.m_t[1] )
          m_range.m_t[1] = k;
      }
      else {
        m_range.m_t[0] = m_range.m_t[1] = k;
      }
      kappa[m_count++] = k;
    }


    if ( m_count == 0 )
      rc = false;
    else {
      // sum curvatures
      ON_SortDoubleArray( ON::sort_algorithm::quick_sort, kappa, m_count );

      // mode
      m_mode = kappa[m_count/2];
      if ( 0 == (m_count % 2) ) {
        m_mode += kappa[(m_count/2)-1];
        m_mode *= 0.5;
      }

      // average
      for ( i = 0; i < m_count; i++ ) {
        m_average += kappa[i];
      }
      m_average = m_average/m_count;
      
      // average deviation
      for ( i = 0; i < m_count; i++ ) {
        m_adev += fabs(kappa[i] - m_average);
      }
      m_adev = m_adev/m_count;
    }  
  }
  
  return rc;  
}

struct EDGEINFO
{
  int fi[2]; // m_F[] triangles on either side of the edge
  int vi[4]; // potential m_V[] quad indices
  int flag; // 0 = available, 
            // 1 = side of quad, 
            // 2 = bndry or nonmanifold edge,
            // 3 = edge crease angle > angle_tol_radians
            // 4 = edge is not longest side of triangle
            // 5 = edge length is zero
            // 6 = edge would be a boundary if mesh were exploded
            // 7 = quad would not be convex
            // 8 = if the edge were removed, the quad would not pass the min_diagonal_length_ratio test (not "square" enough)
            // 16 = tha diagonal is too short to remove in the first pass that makes the "obvious" quads.
  double length;
};

bool ON_Mesh::ConvertTrianglesToQuads( 
              double angle_tol_radians,
              double min_diagonal_length_ratio
              )
{
  ON_Workspace ws;

  ON_3dPoint QCornerPoints[4];
  ON_3dVector QuadSides[4];
  ON_3dVector QuadCornerNormals[4];
  double QuadCornerDots[4];

  double d;

  int i, ii, jj;
  int diagonal_count;
  const int* f0vi;
  const int* f1vi;
  const int* fei;

  diagonal_count = 0;

  if ( angle_tol_radians < 0.0
    || !ON_IsValid(angle_tol_radians)
    || angle_tol_radians > 0.5*ON_PI )
  {
    // 2.5 degrees
    angle_tol_radians = 0.043633231299858239423092269212215;
  }
  else if ( angle_tol_radians < ON_ZERO_TOLERANCE )
  {
    angle_tol_radians = ON_ZERO_TOLERANCE;
  }

  angle_tol_radians = cos(angle_tol_radians);
  if ( angle_tol_radians < 0.5 )
    angle_tol_radians = 0.5;
  else if ( angle_tol_radians > 1.0-ON_SQRT_EPSILON )
    angle_tol_radians = 1.0-ON_SQRT_EPSILON;

  const ON_MeshTopology& top = Topology();

  if ( !HasFaceNormals() )
    ComputeFaceNormals();

  if ( min_diagonal_length_ratio < ON_ZERO_TOLERANCE )
    min_diagonal_length_ratio = ON_ZERO_TOLERANCE;

  double max_diagonal_length_ratio = 1.0/min_diagonal_length_ratio;

  if( min_diagonal_length_ratio > max_diagonal_length_ratio )
  {
    d = min_diagonal_length_ratio;
    min_diagonal_length_ratio = max_diagonal_length_ratio;
    max_diagonal_length_ratio = d;
  }

  //double rel_tol = ON_SQRT_EPSILON;
  double rel_tol = 8.0*ON_SQRT_EPSILON; // to fix RR 51543
  if ( min_diagonal_length_ratio > 1.0-rel_tol )
    min_diagonal_length_ratio = 1.0-rel_tol;
  if ( max_diagonal_length_ratio < 1.0+rel_tol )
    max_diagonal_length_ratio = 1.0+rel_tol;


  const int face_count = m_F.Count();
  int* face_flag = ws.GetIntMemory(face_count);  
  for ( i = 0; i < face_count; i++ )
  {
    f0vi = m_F[i].vi;
    face_flag[i] = ( f0vi[2] == f0vi[3] ) ? 0 : 1;
  }

  const int edge_count = top.m_tope.Count();
  struct EDGEINFO* EI = (struct EDGEINFO*)ws.GetMemory(edge_count*sizeof(*EI));

  for ( i = 0; i < edge_count; i++ )
  {
    struct EDGEINFO& ei = EI[i];
    const ON_MeshTopologyEdge& tope = top.m_tope[i];
    ei.flag = 0;
    ei.vi[0] = top.m_topv[tope.m_topvi[0]].m_vi[0];
    ei.vi[2] = top.m_topv[tope.m_topvi[1]].m_vi[0];
    ei.length = m_V[ei.vi[0]].DistanceTo(m_V[ei.vi[2]]);
    if ( !(ei.length > 0.0) || !ON_IsValid(ei.length) )
    {
      // ei.length is a nan or worse
      ei.flag = 5;
    }
    else if ( tope.m_topf_count != 2 )
    {
      ei.flag = 2;
    }
    else
    {
      ei.fi[0] = tope.m_topfi[0];
      ei.fi[1] = tope.m_topfi[1];
      if (face_flag[ei.fi[0]] || face_flag[ei.fi[1]] )
      {
        ei.flag = 1;
      }
      else if ( m_FN[ei.fi[0]] * m_FN[ei.fi[1]] < angle_tol_radians )
      {
        ei.flag = 3;
      }
      else 
      {
        f0vi = m_F[ei.fi[0]].vi;
        f1vi = m_F[ei.fi[1]].vi;
        ei.flag = 6;
        for ( ii = 0; ii < 3 && 0 != ei.flag; ii++ )
        {
          for (jj = 0; jj < 3; jj++)
          {
            if (    f0vi[ii] == f1vi[jj] 
                 && f0vi[(ii+1)%3] == f1vi[(jj+2)%3]
                 && f0vi[(ii+2)%3] != f1vi[(jj+1)%3] )
            {
              if ( ei.fi[0] > ei.fi[1] )
              {
                jj = ei.fi[0]; ei.fi[0] = ei.fi[1]; ei.fi[1] = jj;
              }
              ei.vi[0] = f0vi[ii];
              ei.vi[1] = f1vi[(jj+1)%3];
              ei.vi[2] = f0vi[(ii+1)%3];
              ei.vi[3] = f0vi[(ii+2)%3];

              // convexity test
              QCornerPoints[0] = m_V[ei.vi[0]];
              QCornerPoints[1] = m_V[ei.vi[1]];
              QCornerPoints[2] = m_V[ei.vi[2]];
              QCornerPoints[3] = m_V[ei.vi[3]];
              QuadSides[0] = QCornerPoints[1] - QCornerPoints[0];
              QuadSides[1] = QCornerPoints[2] - QCornerPoints[1];
              QuadSides[2] = QCornerPoints[3] - QCornerPoints[2];
              QuadSides[3] = QCornerPoints[0] - QCornerPoints[3];
              // Actually, opposite normal but
              QuadCornerNormals[0] = ON_CrossProduct(QuadSides[0], QuadSides[3]);
              QuadCornerNormals[1] = ON_CrossProduct(QuadSides[1], QuadSides[0]);
              QuadCornerNormals[2] = ON_CrossProduct(QuadSides[2], QuadSides[1]);
              QuadCornerNormals[3] = ON_CrossProduct(QuadSides[3], QuadSides[2]);
              QuadCornerDots[0] = QuadCornerNormals[0] * QuadCornerNormals[1];
              QuadCornerDots[1] = QuadCornerNormals[1] * QuadCornerNormals[2];
              QuadCornerDots[2] = QuadCornerNormals[2] * QuadCornerNormals[3];
              QuadCornerDots[3] = QuadCornerNormals[3] * QuadCornerNormals[0];
              if (QuadCornerDots[0] > 0.0)
              {
                if (QuadCornerDots[1] > 0.0 && QuadCornerDots[2] > 0.0 && QuadCornerDots[3] > 0.0)
                {
                  // If the diagonal were removed, the resulting quad would be convex
                  // so this edge is a candidate for being removed.
                  ei.flag = 0; 
                  break;
                }
              }              
              else if (QuadCornerDots[0] < 0.0)
              {
                if (QuadCornerDots[1] < 0.0 && QuadCornerDots[2] < 0.0 && QuadCornerDots[3] < 0.0)
                {
                  // If the diagonal were removed, the resulting quad would be convex
                  // so this edge is a candidate for being removed.
                  ei.flag = 0;
                  break;
                }
              }

              // If the diagonal were removed, the resulting quad would not be convex
              // or one of the QuadCornerDots[] values is a nan.
              // In either case, this edge will not be removed.
              ei.flag = 7; 
              break;
            }
          }
        }
      }
    }
  }

  for ( i = 0; i < edge_count; i++ )
  {
    struct EDGEINFO& ei = EI[i];
    if ( 0 != ei.flag )
      continue;

    d = m_V[ei.vi[1]].DistanceTo(m_V[ei.vi[3]]);
    d /= ei.length;
    if (d < min_diagonal_length_ratio || d > max_diagonal_length_ratio)
    {
      // quad wouldn't be square enough
      ei.flag = 8;
      continue;
    }
      
    if (face_count > 2)
    {
      // It is CRITICAL that the length compare use >=.
      // Otherwise tesselations of equailateral triangles
      // will not work right in this fuction.
      fei = top.m_topf[ei.fi[0]].m_topei;
      if ((i != fei[0] && EI[fei[0]].length >= ei.length)
        || (i != fei[1] && EI[fei[1]].length >= ei.length)
        || (i != fei[2] && EI[fei[2]].length >= ei.length)
        )
      {
        // diagonal is not strictly longest in this triangle.
        // A 2nd pass would be required to determine which
        // diagonals could be removed. 
        // See the file "RH-5481 IssueClarified.3dm" in
        // http://mcneel.myjetbrains.com/youtrack/issue/RH-5481
        // for an example.
        ei.flag = 16;
        continue;
      }

      // It is CRITICAL that the length compare use >=.
      // Otherwise tesselations of equilateral triangles
      // will not work right in this function.
      fei = top.m_topf[ei.fi[1]].m_topei;
      if ((i != fei[0] && EI[fei[0]].length >= ei.length)
        || (i != fei[1] && EI[fei[1]].length >= ei.length)
        || (i != fei[2] && EI[fei[2]].length >= ei.length)
        )
      {
        // diagonal is not strictly longest in this triangle
        // A 2nd pass would be required to determine which
        // diagonals could be removed. 
        // See the file "RH-5481 IssueClarified.3dm" in
        // http://mcneel.myjetbrains.com/youtrack/issue/RH-5481
        // for an example.
        ei.flag = 16;
        continue;
      }


    }

    ei.flag = 0;

    diagonal_count++;
  }

  
  // Dale Lear 2016-March-28
  // If we are going to fix bugs like the issue raised in 
  //  http://mcneel.myjetbrains.com/youtrack/issue/RH-5481
  // Additional passes need to be made here that decide which diagonals to 
  // remove hen the diagonal is shorter than a resulting quad side.
  // See the file "RH-5481 IssueClarified.3dm" in
  // http://mcneel.myjetbrains.com/youtrack/issue/RH-5481
  // for an example.

  
  if ( diagonal_count > 0 )
  {
    DestroyTree();
    DestroyPartition();
    m_top.Destroy();
    m_invalid_count = 0;
    m_triangle_count = 0;
    m_quad_count = 0;
    for (i = 0; i < edge_count; i++)
    {
      struct EDGEINFO& ei = EI[i];
      if ( ei.flag )
        continue;
      memcpy( m_F[ei.fi[0]].vi, ei.vi, 4*sizeof(ei.vi[0]) );
      memset( m_F[ei.fi[1]].vi, 0xFF,  4*sizeof(ei.vi[0]) );
    }    
    CullDegenerateFaces();
  }

  return (diagonal_count > 0 );
}

bool ON_Mesh::ConvertQuadsToTriangles()
{
  double planar_tolerance = ON_UNSET_VALUE;
  double angle_tolerance_radians = ON_UNSET_VALUE;
  unsigned int split_method = 1;

  ConvertNonPlanarQuadsToTriangles(
    planar_tolerance, 
    angle_tolerance_radians,
    split_method
  );

  return ( QuadCount() == 0 && TriangleCount() == FaceCount() ) ? true : false;
}

double ON_TriangleArea3d(ON_3dPoint A, ON_3dPoint B, ON_3dPoint C)
{
  // MF, March 18 24:
  // a faster and numerically more robust version would be William Kahan's version of Heron's formula,
  // see "Accuracy and Stability of Numerical Algorithms", N. Higham.

  // speed this up if needed
  return 0.5*ON_CrossProduct(B-A,C-A).Length();
}

double ON_TriangleArea2d(ON_2dPoint A, ON_2dPoint B, ON_2dPoint C)
{
  const double ABx = B.x-A.x;
  const double ABy = B.y-A.y;
  const double CAx = C.x-A.x;
  const double CAy = C.y-A.y;
  return 0.5*fabs((ABx*CAy) - (ABy*CAx));
}

unsigned int ON_Mesh::ConvertNonPlanarQuadsToTriangles(
  double planar_tolerance,
  double angle_tolerance_radians,
  unsigned int split_method
)
{
  bool bDeleteNgonsContainingSplitQuads = false;
  return ConvertNonPlanarQuadsToTriangles(
    planar_tolerance,
    angle_tolerance_radians,
    split_method,
    bDeleteNgonsContainingSplitQuads
    );
}

static int ON_CompareUnsignedInt(const unsigned int* i0, const unsigned int* i1)
{
  if ( i0 < i1 )
    return -1;
  if ( i0 > i1 )
    return 1;
  return 0;
}

unsigned int ON_Mesh::ConvertNonPlanarQuadsToTriangles(
  double planar_tolerance,
  double angle_tolerance_radians,
  unsigned int split_method,
  bool bDeleteNgonsContainingSplitQuads
  )
{
  const unsigned int face_count0 = FaceUnsignedCount();
  if ( face_count0 <= 0 )
    return 0;

  const ON_3dPointListRef vertex_list(this);
  const unsigned int vertex_count = vertex_list.PointCount();
  if ( vertex_count <= 0 )
    return 0;

  const unsigned int quad_count0 = (unsigned int)QuadCount();

  if ( quad_count0 <= 0 )
    return 0;

  const bool bSplitAllQuads = (ON_UNSET_VALUE == planar_tolerance && ON_UNSET_VALUE == angle_tolerance_radians);

  if (false == bSplitAllQuads && !(planar_tolerance >= 0.0) && !(angle_tolerance_radians >= 0.0))
    return 0;
  
  if ( 0 == split_method )
    split_method = 1;
  
  if ( split_method < 1 || split_method > 6 )
    return 0;

  const bool bHasFaceNormals = HasFaceNormals();

  unsigned int ngon_count = HasNgons() ? NgonUnsignedCount() : 0;
  unsigned int ngon_index = ON_UNSET_UINT_INDEX;

  unsigned int fi;
  int idmin;
  double d0, d1, dmin, d;
  ON_3dPoint P[4];

  // use SetCapacity() instead of Reserve() because it's unlikely
  // this mesh will have anything else added and we don't want to
  // waste memory.
  if ( ((unsigned int)m_F.Capacity()) < face_count0 + quad_count0 )
    m_F.SetCapacity( face_count0 + quad_count0 );
  if ( bHasFaceNormals && ((unsigned int)m_FN.Capacity()) < face_count0 + quad_count0 )
    m_FN.SetCapacity( face_count0 + quad_count0 );

  const double rel_tol = 8.0*( vertex_list.DoublePrecision() ? ON_EPSILON : ON_FLOAT_EPSILON );

  ON_3dVector FN;

  // If bDeleteNgonsContainingSplitQuads = true, then uint_buffer[] is a list
  // of ngons to delete.
  //
  // if bDeleteNgonsContainingSplitQuads = false, then ...  // 
  // If the mesh has n-gons, then ngon_new_face_count[ngon_index]
  // is the number of new faces to add to an existing ngon.
  // This happens when an n-gon contains a quad that is divided
  // into two triangles.
  ON_SimpleArray<unsigned int> uint_buffer;


  unsigned int* ngon_new_face_count = nullptr;
  bool bUpdateNgons = false;
  bool bDeleteNgonMap = false;
  if ( ngon_count > 0 )
  {
    if (bDeleteNgonsContainingSplitQuads)
    {
      uint_buffer.Reserve(64);
    }
    else
    {
      bDeleteNgonMap = (0 == NgonMap());
      if (0 == CreateNgonMap())
      {
        ngon_count = 0;
        bDeleteNgonMap = true;
        bDeleteNgonsContainingSplitQuads = true;
      }
      else
      {
        uint_buffer.Reserve(ngon_count);
        uint_buffer.SetCount(ngon_count);
        uint_buffer.Zero();
        ngon_new_face_count = uint_buffer.Array();
      }
    }
  }


  for ( fi = 0; fi < face_count0; fi++ ) 
  {
    ON_MeshFace& f0 = m_F[fi];
    if ( ngon_count > 0 )
    {            
      ngon_index = m_NgonMap[fi];
      if ( ngon_index >= ngon_count )
      {
        ngon_index = ON_UNSET_UINT_INDEX;
        m_NgonMap[fi] = ngon_index;
      }
    }

    if ( false == f0.IsValid(vertex_count) )
      continue;

    if ( false == f0.IsQuad() )
      continue;

    if (planar_tolerance >= 0.0 || angle_tolerance_radians >= 0.0)
    {
      if (true == f0.IsPlanar(planar_tolerance, angle_tolerance_radians, vertex_list, 0))
        continue;
    }
 
    P[0] = vertex_list[f0.vi[0]];
    P[1] = vertex_list[f0.vi[1]];
    P[2] = vertex_list[f0.vi[2]];
    P[3] = vertex_list[f0.vi[3]];
    d0 = P[0].DistanceTo(P[2]);
    d1 = P[1].DistanceTo(P[3]);

    // if quad is degenerate, just turn it into a triangle
    idmin = -1;
    dmin = ((d0<=d1)?d0:d1)*rel_tol;
    if ( dmin > ON_ZERO_TOLERANCE )
      dmin = ON_ZERO_TOLERANCE;
    d = P[0].DistanceTo(P[1]);
    if ( d < dmin )
    {
      idmin = 0;
      dmin = d;
    }
    d = P[1].DistanceTo(P[2]);
    if ( d < dmin )
    {
      idmin = 1;
      dmin = d;
    }
    d = P[2].DistanceTo(P[3]);
    if ( d < dmin )
    {
      idmin = 2;
      dmin = d;
    }
    d = P[3].DistanceTo(P[0]);
    if ( d < dmin )
    {
      idmin = 3;
      dmin = d;
    }
    

    if ( !(d0 > 0.0) )
    {
      if ( !(d1 > 0.0) )
        continue;
      // d0 = 0 or is invalid and d1 > 0
      // force split along v[1],v[3]
      idmin = -1;
      d0 = 1.0;
      d1 = 0.0;
    }
    else if ( !(d1 > 0.0) )
    {
      // d1 = 0 or is invalid and d0 > 0
      // force split along v[0],v[1]
      idmin = -1;
      d1 = 1.0;
      d0 = 0.0;
    }

    m_quad_count--;
    m_triangle_count++;
    if ( 0 == idmin ) // m_V[f0.vi[0]] == m_V[f0.vi[1]] (nearly)
    {
      // degenerate quad - remove duplicate vertex
      f0.vi[0] = f0.vi[1];
      f0.vi[1] = f0.vi[2];
      f0.vi[2] = f0.vi[3];
    }
    else if ( 1 == idmin ) // m_V[f0.vi[1]] == m_V[f0.vi[2]] (nearly)
    {
      // degenerate quad - remove duplicate vertex
      int vi0 = f0.vi[0]; 
      f0.vi[0] = f0.vi[2];
      f0.vi[1] = f0.vi[3];
      f0.vi[2] = vi0;
      f0.vi[3] = vi0;
    }
    else if ( 2 == idmin ) // m_V[f0.vi[2]] == m_V[f0.vi[3]] (nearly)
    {
      // degenerate quad - remove duplicate vertex
      f0.vi[2] = f0.vi[1];
      f0.vi[1] = f0.vi[0];
      f0.vi[0] = f0.vi[3];
      f0.vi[3] = f0.vi[2];
    }
    else if ( 3 == idmin ) // m_V[f0.vi[3]] == m_V[f0.vi[0]] (nearly)
    {
      // degenerate quad - remove duplicate vertex
      f0.vi[3] = f0.vi[2];
    }
    else
    {
      // split non-degenerate quad into two triangles

      if ( ngon_count > 0 )
      {            
        if (bDeleteNgonsContainingSplitQuads)
        {
          if (ON_UNSET_INT_INDEX != ngon_index)
          {
            uint_buffer.Append(ngon_index);
            bUpdateNgons = true;
          }
        }
        else
        {
          // update n-gon map
          m_NgonMap.Append(ngon_index);
          if (ngon_index < ngon_count)
          {
            // The quad was in an n-gon and the new face index
            // will be appended to the n-gons m_fi[] list.
            ngon_new_face_count[ngon_index]++;
            bUpdateNgons = true;
          }
        }
      }

      ON_MeshFace& f1 = m_F.AppendNew();
      bool bSplitAlongDiagonal02 = true;
      switch(split_method)
      {
      case 1:
        if ( d1 < d0 )
          bSplitAlongDiagonal02 = false;
        break;

      case 2:
        if ( d1 > d0 )
          bSplitAlongDiagonal02 = false;
        break;

      case 3:
      case 4:
        {
          double a0 = ON_TriangleArea3d(P[0],P[1],P[2]) + ON_TriangleArea3d(P[0],P[2],P[3]);
          double a1 = ON_TriangleArea3d(P[0],P[1],P[3]) + ON_TriangleArea3d(P[1],P[2],P[3]);
          if (a0 == a1)
          {
            if (d1 < d0)
              bSplitAlongDiagonal02 = false;
          }
          else if ( 3 == split_method )
          {
            // minimize area
            if (a1 < a0)
              bSplitAlongDiagonal02 = false;
          }
          else
          {
            // maximize area
            if (a1 > a0)
              bSplitAlongDiagonal02 = false;
          }
        }
        break;

      case 5:
      case 6:
        {
          ON_3dVector corner_normals[4];
          if (f0.GetCornerNormals(vertex_list, corner_normals))
          {
            double a[2];
            for (unsigned int i = 0; i < 2; i++)
            {
              a[i]
                = (ON_UNSET_VALUE != corner_normals[i].x && ON_UNSET_VALUE != corner_normals[i + 2].x)
                ? corner_normals[i] * corner_normals[i + 2]
                : 2.0; // some valid number bigger than 1.0
            }

            if (a[0] == a[1])
            {
              if (d1 < d)
                bSplitAlongDiagonal02 = false;
            }
            else if (5 == split_method)
            {
              // minimize angle
              if (a[0] > a[1])
                bSplitAlongDiagonal02 = false;
            }
            else
            {
              // maximize angle
              if (a[0] < a[1])
                bSplitAlongDiagonal02 = false;
            }
          }
        }
        break;
      }

      if  ( bSplitAlongDiagonal02 ) 
      {
        f1.vi[0] = f0.vi[0];
        f1.vi[1] = f0.vi[2];
        f1.vi[2] = f0.vi[3];
        f1.vi[3] = f1.vi[2];
        f0.vi[3] = f0.vi[2];
      }
      else 
      {
        f1.vi[0] = f0.vi[1];
        f1.vi[1] = f0.vi[2];
        f1.vi[2] = f0.vi[3];
        f1.vi[3] = f1.vi[2];
        f0.vi[2] = f0.vi[3];
      }

      if ( bHasFaceNormals ) 
      {
        m_F[fi].ComputeFaceNormal(vertex_list,FN);
        m_FN[fi] = FN;
        m_F[m_F.Count()-1].ComputeFaceNormal(vertex_list,FN);
        m_FN.AppendNew() = FN;
      }
    }
  }

  if ( face_count0 != m_F.UnsignedCount() )
  {
    // we added some triangles which means cached topology
    // and partition information is no longer valid.
    DestroyTopology(); 
    DestroyPartition();
  }

  if ( bUpdateNgons )
  {
    if (bDeleteNgonsContainingSplitQuads)
    {
      const unsigned int uint_buffer_count = uint_buffer.UnsignedCount();
      if (uint_buffer_count > 0)
      {
        uint_buffer.QuickSort(ON_CompareUnsignedInt);
        unsigned int ngon_index_count = 0;
        unsigned int* ngon_index_list = uint_buffer.Array();
        ngon_index = ON_UNSET_UINT_INDEX;
        for (unsigned int i = 0; i < uint_buffer_count; i++ )
        {
          if (ngon_index == uint_buffer[i])
            continue;
          ngon_index = uint_buffer[i];
          ngon_index_list[ngon_index_count++] = ngon_index;
        }
        RemoveNgons(ngon_index_count, ngon_index_list);
      }
    }
    else
    {
      if (m_NgonMap.UnsignedCount() == m_F.UnsignedCount())
      {
        // allocate room for new face indices
        for (ngon_index = 0; ngon_index < ngon_count; ngon_index++)
        {
          if (ngon_new_face_count[ngon_index] <= 0)
            continue;
          ON_MeshNgon* ngon = this->m_Ngon[ngon_index];
          if (0 == ngon)
            continue;
          unsigned int Fcount0 = ngon->m_Fcount;
          ngon = m_NgonAllocator.ReallocateNgon(ngon, ngon->m_Vcount, ngon->m_Fcount + ngon_new_face_count[ngon_index]);
          ngon->m_Fcount = Fcount0;
          m_Ngon[ngon_index] = ngon;
        }

        // Add new faces to appropriate ngon face index lists
        for (fi = face_count0; fi < m_F.UnsignedCount(); fi++)
        {
          ngon_index = m_NgonMap[fi];
          if (ngon_index < ngon_count)
          {
            ON_MeshNgon* ngon = m_Ngon[ngon_index];
            if (ngon)
              ngon->m_fi[ngon->m_Fcount++] = fi;
          }
        }
      }
      else
      {
        bDeleteNgonMap = true;
      }
    }
  }

  if ( bDeleteNgonMap )
    m_NgonMap.Destroy();

  return quad_count0 - QuadCount();
}

bool ON_Mesh::CountQuads()
{
  const int fcount = FaceCount();
  const int vcount = VertexCount();
  int fi;
  m_quad_count = 0;
  m_triangle_count = 0;
  m_invalid_count = 0;
  for ( fi = 0; fi < fcount; fi++ ) {
    const ON_MeshFace& f = m_F[fi];
    if ( f.IsValid(vcount) ) {
      if ( f.IsTriangle() )
        m_triangle_count++;
      else
        m_quad_count++;
    }
    else
      m_invalid_count++;
  }
  return true;
}

bool ON_Mesh::ComputeVertexNormals()
{
  bool rc = false;
  const int fcount = FaceCount();
  const int vcount = VertexCount();
  int vi, fi, j;
  ON_3fVector n;

  if ( fcount > 0 && vcount > 0 ) {
    rc = HasFaceNormals();
    if ( !rc )
      rc = ComputeFaceNormals();
    if ( rc ) {
      ON_Workspace ws;
      //double* face_area = ws.GetDoubleMemory(fcount);
      int* vfcount = ws.GetIntMemory( vcount );
      memset ( vfcount, 0, vcount*sizeof(*vfcount) );

      // count number of faces that use each vertex
      for ( fi = 0; fi < fcount; fi++ ) {
        ON_MeshFace& f = m_F[fi];
        if ( f.IsValid(vcount) ) {
          vfcount[f.vi[0]]++;
          vfcount[f.vi[1]]++;
          vfcount[f.vi[2]]++;
          if ( f.IsQuad() )
            vfcount[f.vi[3]]++;
        }
      }

      // set vfi[vi][] = array of face indices that use vertex vi
      int** vfi = (int**)ws.GetMemory( vcount*sizeof(vfi[0] ) );
      {
        int scratch_sz = 0;
        for ( vi = 0; vi < vcount; vi++ ) {
          scratch_sz += vfcount[vi];
        }
        int* scratch = ws.GetIntMemory(scratch_sz);
        for ( vi = 0; vi < vcount; vi++ ) {
          if ( vfcount[vi] ) {
            vfi[vi] = scratch;
            scratch += vfcount[vi];
          }
          vfcount[vi] = 0;
        }
      }
      for ( fi = 0; fi < fcount; fi++ ) {
        ON_MeshFace& f = m_F[fi];
        if ( f.IsValid(vcount) ) {
          vi = f.vi[0]; vfi[vi][vfcount[vi]++] = fi;
          vi = f.vi[1]; vfi[vi][vfcount[vi]++] = fi;
          vi = f.vi[2]; vfi[vi][vfcount[vi]++] = fi;
          if ( f.IsQuad() ) {
            vi = f.vi[3]; vfi[vi][vfcount[vi]++] = fi;
          }
        }
      }

      // average face normals to get an estimate for a vertex normal
      m_N.SetCapacity(vcount);
      m_N.SetCount(0);
      for ( vi = 0; vi < vcount; vi++ )
      {
        n = ON_3fVector::ZeroVector;
        for ( j = vfcount[vi]-1; j >= 0; j-- ) 
        {
          n += m_FN[vfi[vi][j]];
        }
        if ( !n.Unitize() )
        {
          // this vertex is not used by a face or the face normals cancel out.
          // set a unit z normal and press on.
          n.Set(0,0,1);
        }
        m_N.Append(n);
      }
    }
  }
  return rc;
}


#if 0
// Will be added April/may of 2024
bool ON_Mesh::ComputeVertexPrincipalCurvatures(
  ON_Mesh::CurvatureSettingMethod method,
  bool bLazy
)
{
  // NOT INCLUDED IN PUBLIC OPENNURBS
  return false;
}
#endif

bool ON_Mesh::NormalizeTextureCoordinates()
{
  ON_2fPoint t0;//, t1;
  int ti;
  const int vertex_count = m_V.Count();
  bool rc = HasSurfaceParameters();
  if ( rc )
  {
    const ON_2dPoint* S = m_S.Array();
    ON_Interval udom = m_srf_domain[0];
    ON_Interval vdom = m_srf_domain[1];
    rc = udom.IsIncreasing() && vdom.IsIncreasing();
    if ( !rc )
    {
      udom.Set(S[0].x,S[0].x);
      vdom.Set(S[0].y,S[0].y);
      for ( ti = 1; ti < vertex_count; ti++ )
      {
        if      ( S[ti].x < udom.m_t[0] ) udom.m_t[0] = S[ti].x;
        else if ( S[ti].x > udom.m_t[1] ) udom.m_t[1] = S[ti].x;
        if      ( S[ti].y < vdom.m_t[0] ) vdom.m_t[0] = S[ti].y;
        else if ( S[ti].y > vdom.m_t[1] ) vdom.m_t[1] = S[ti].y;
      }
      rc = udom.IsIncreasing() && vdom.IsIncreasing();
    }

    if (rc)
    {
      m_T.Reserve(vertex_count);
      m_T.SetCount(0);
      for (ti = 0; ti < vertex_count; ti++ )
      {
        t0.x = (float)udom.NormalizedParameterAt(S[ti].x);
        t0.y = (float)vdom.NormalizedParameterAt(S[ti].y);
        m_T.Append(t0);
      }
      m_packed_tex_domain[0].Set(0.0,1.0);
      m_packed_tex_domain[1].Set(0.0,1.0);
      m_packed_tex_rotate = false;
      m_Ttag.SetDefaultSurfaceParameterMappingTag();
      if ( m_mesh_parameters )
        m_mesh_parameters->SetTextureRange(1);

      // Jussi Nov 11 2024, RH-84445:
      //  Texture packing has been modified. Therefore all cached surface parameter mapping texture coordinates need to be invalidated.
      InvalidateCachedTextureCoordinates(true);
    }
  }

  return rc;
}

bool ON_Mesh::TransposeSurfaceParameters()
{
	// swap m_srf_domain 
	ON_Interval temp = m_srf_domain[0];
	m_srf_domain[0]  = m_srf_domain[1];
	m_srf_domain[1]  = temp;

	double t = m_srf_scale[0];
	m_srf_scale[0] = m_srf_scale[1];
  m_srf_scale[1] = t;

  int S_count = m_S.Count();
  ON_2dPoint* S_array = m_S.Array();
  for (int i = 0; i < S_count; i++ )
  {
    ON_2dPoint& S = S_array[i];
    t = S.x; S.x = S.y; S.y = t;
  }
  return true;
}

bool ON_Mesh::HasPackedTextureRegion() const
{
  return (    ON_IsValid(m_srf_scale[0])
           && m_srf_scale[0] > 0.0
           && ON_IsValid(m_srf_scale[1])
           && m_srf_scale[1] > 0.0
           && m_packed_tex_domain[0].IsInterval()
           && m_packed_tex_domain[1].IsInterval()
           && 0.0 <= m_packed_tex_domain[0].Min()
           && m_packed_tex_domain[0].Max() <= 1.0
           && 0.0 <= m_packed_tex_domain[1].Min()
           && m_packed_tex_domain[1].Max() <= 1.0
           && (   fabs(m_packed_tex_domain[0].Length()) < 1.0
               || fabs(m_packed_tex_domain[1].Length()) < 1.0)
         );
}


bool ON_Mesh::TransposeTextureCoordinates()
{
  if ( !HasTextureCoordinates() )
    return false;

  const int vcnt = m_T.Count();
  int i;

  bool bPackedRegion =  HasPackedTextureRegion();

  bool bSrfParamTag = (!m_Ttag.IsSet() || m_Ttag.IsDefaultSurfaceParameterMapping());

  if ( bPackedRegion && bSrfParamTag )
  {
    // The region of the bitmap the texture uses 
    // cannot change.  The texture coordinates 
    // themselves get reflected in the subrectangle
    // about either the lowerleft to upperright
    // diagonal (llur = true) or the lowerright
    // to upperleft diagonal (llur = false).
    bool bRevU = m_packed_tex_domain[0].IsDecreasing();
    bool bRevV = m_packed_tex_domain[1].IsDecreasing();
    bool llur = (bRevU == bRevV) ? true : false;
    if ( m_packed_tex_rotate )
      llur = !llur;

    ON_Interval TD[2];
  	TD[0] = m_packed_tex_domain[0];
	  TD[1] = m_packed_tex_domain[1];
	  TD[0].MakeIncreasing(); 
	  TD[1].MakeIncreasing(); 
    for( i=0; i<vcnt; i++)
    {
	    ON_2fPoint tc = m_T[i];
	    double x = TD[0].NormalizedParameterAt(tc[0]);
	    double y = TD[1].NormalizedParameterAt(tc[1]);
	    if(!llur)
      {
		    x = 1.0-x;
		    y = 1.0-y;
	    }	
	    double s = TD[0].ParameterAt(y);
	    double t = TD[1].ParameterAt(x);
	    m_T[i].Set((float)s,(float)t);
    }
  }
  else
  {
    float f;
	  for(i=0; i<vcnt; i++)
    {
		  ON_2fPoint& tc = m_T[i];
      f = tc.x; tc.x = tc.y; tc.y = f;
	  }
  }
  // 12 Jan 2024 - Jeff: https://mcneel.myjetbrains.com/youtrack/issue/RH-79611
  InvalidateCachedTextureCoordinates();
  return true;
}

bool ON_Mesh::ReverseTextureCoordinates( int dir )
{
  if ( dir < 0 || dir > 1 || !HasTextureCoordinates() )
    return false;

  bool bPackedRegion =  HasPackedTextureRegion();

  bool bSrfParamTag = (!m_Ttag.IsSet() || m_Ttag.IsDefaultSurfaceParameterMapping());

  const int vcount = m_T.Count();
  int i;
  if ( bPackedRegion && bSrfParamTag )
  {
    // The region of the bitmap the texture uses 
    // cannot change.  The texture coordinates 
    // themselves get reflected in the subrectangle
    // about either the lowerleft to upperright
    // diagonal (llur = true) or the lowerright
    // to upperleft diagonal (llur = false).
    if ( m_packed_tex_rotate )
      dir = 1-dir;
    const ON_Interval tex_dom = m_packed_tex_domain[dir];
    double s;
    m_packed_tex_domain[dir].Swap(); // Swap() is correct - Reverse() is wrong.
    for (i = 0; i < vcount; i++ )
    {
      ON_2fPoint& tc = m_T[i];
      s = 1.0 - tex_dom.NormalizedParameterAt(tc[dir]);
      if ( dir )
        tc.y = (float)tex_dom.ParameterAt(s);
      else
        tc.x = (float)tex_dom.ParameterAt(s);
    }
  }
  else
  {
    for (i = 0; i < vcount; i++ )
    {
      ON_2fPoint& tc = m_T[i];
      if ( dir )
        tc.y = 1.0f-tc.y;
      else
        tc.x = 1.0f-tc.x;
    }
  }
  // 12 Jan 2024 - Jeff: https://mcneel.myjetbrains.com/youtrack/issue/RH-79611
  InvalidateCachedTextureCoordinates();
  return true;
}

bool ON_Mesh::ReverseSurfaceParameters( int dir )
{
  if ( dir < 0 || dir > 1 || !HasSurfaceParameters() )
    return false;
  if ( m_srf_domain[dir].IsIncreasing() )
    m_srf_domain[dir].Reverse();
  int i, vcount = m_S.Count();
  for (i = 0; i < vcount; i++)
  {
    ON_2dPoint& S = m_S[i];
    if ( dir )
      S.y = -S.y;
    else
      S.x = -S.x;
  }
  return true;
}


bool ON_Mesh::EvaluateMeshGeometry( const ON_Surface& srf )
{
  bool rc = false;
  const int vcount = VertexCount();
  const bool bHasSurfaceParameters = HasSurfaceParameters();
  if ( bHasSurfaceParameters )
  {
    const bool bHasDoublePrecisionVertices = this->HasDoublePrecisionVertices();
    if (false == bHasDoublePrecisionVertices)
      this->m_dV.Destroy();
    const bool bHasVertexNormals = HasVertexNormals();
    m_N.SetCapacity(vcount);
    int vi, side, hint[2];
    ON_3dPoint point;
    ON_3dVector normal, Ds, Dt, Dss, Dst, Dtt, K1, K2;
    const ON_2dPoint* srf_st;
    double s, t, kgauss, kmean;
    side = 0;
    hint[0] = 0;
    hint[1] = 0;
    const double smax = srf.Domain(0)[1];
    const double tmax = srf.Domain(1)[1];
    if ( HasPrincipalCurvatures() ) 
    {
      for ( vi = 0; vi < vcount; vi++ ) 
      {
        //ON_2fPoint& tex = m_T[vi];
        // convert texture coordinates to normalizied texture coordinates
        srf_st = &m_S[vi];
        s = srf_st->x;
        t = srf_st->y;
        // 19 April 2006 Dale Lear - added side setter so singular normals
        //                           are correctly evaluated RR 12482
        side = ( smax == s ) ? ((tmax == t) ? 3 : 2) : ((tmax == t) ? 4 : 1);
        srf.Ev2Der( s, t, point, Ds, Dt, Dss, Dst, Dtt, side, hint );
        ON_EvNormal( side, Ds, Dt, Dss, Dst, Dtt, normal );
        ON_EvPrincipalCurvatures( Ds, Dt, Dss, Dst, Dtt, normal,
                                  &kgauss, &kmean, 
                                  &m_K[vi].k1, &m_K[vi].k2, 
                                  K1, K2 ); //m_K[vi].e1, m_K[vi].e2 );
        m_V[vi] = ON_3fPoint(&point.x); // use ON_3fPoint double* conversion (quiets gcc)
        if (bHasDoublePrecisionVertices)
          m_dV[vi] = point;
        if ( bHasVertexNormals )
          m_N[vi] = ON_3fVector(&normal.x); // use ON_3fVector double* conversion (quiets gcc)
      }
      InvalidateCurvatureStats();
    }
    else if ( bHasVertexNormals ) 
    {
      for ( vi = 0; vi < vcount; vi++ ) 
      {
        //ON_2fPoint& tex = m_T[vi];
        srf_st = &m_S[vi];
        s = srf_st->x;
        t = srf_st->y;
        // 19 April 2006 Dale Lear - added side setter so singular normals
        //                           are correctly evaluated RR 12482
        side = ( smax == s ) ? ((tmax == t) ? 3 : 2) : ((tmax == t) ? 4 : 1);
        srf.EvNormal( s, t, point, normal, side, hint );
        m_V[vi] = ON_3fPoint(&point.x); // use ON_3fPoint double* conversion (quiets gcc)
        if (bHasDoublePrecisionVertices)
          m_dV[vi] = point;
        m_N[vi] = ON_3fVector(&normal.x); // use ON_3fVector double* conversion (quiets gcc)
      }
    }
    else 
    {
      for ( vi = 0; vi < vcount; vi++ ) 
      {
        //ON_2fPoint& tex = m_T[vi];
        srf_st = &m_S[vi];
        s = srf_st->x;
        t = srf_st->y;
        srf.EvPoint( s, t, point, side, hint );
        m_V[vi] = ON_3fPoint(&point.x);
        if (bHasDoublePrecisionVertices)
          m_dV[vi] = point;
      }
    }
    if ( HasFaceNormals() )
    {
      ComputeFaceNormals();
    }
    rc = true;

    m_Ctag.Default();
    InvalidateVertexBoundingBox();
    InvalidateVertexNormalBoundingBox();
    DeleteMeshParameters();
    DestroyTree();
  }
  return rc;
}

void ON_Mesh::SetMeshParameters( const ON_MeshParameters& mp )
{
  DeleteMeshParameters();
  m_mesh_parameters = new ON_MeshParameters(mp);
}

const ON_MeshParameters* ON_Mesh::MeshParameters() const
{
  return m_mesh_parameters;
}

void ON_Mesh::DeleteMeshParameters()
{
  if ( m_mesh_parameters ) {
    delete m_mesh_parameters;
    m_mesh_parameters = 0;
  }
}

static bool isValid3fPoint(const ON_3fPoint* a)
{
  return (ON_IS_VALID_FLOAT(a->x) && ON_IS_VALID_FLOAT(a->y) && ON_IS_VALID_FLOAT(a->z)) ? true : false;
}

static int compare3fPoint( const ON_3fPoint* a, const ON_3fPoint* b )
{
  const bool aValid = isValid3fPoint(a);
  const bool bValid = isValid3fPoint(b);
  if (aValid != bValid)
    return (aValid ? -1 : 1); // invalid points sort to end.
  if (false == aValid)
    return 0; // all invalid points are "equal"
  if ( a->x < b->x ) return -1;
  if ( a->x > b->x ) return  1;
  if ( a->y < b->y ) return -1;
  if ( a->y > b->y ) return  1;
  if ( a->z < b->z ) return -1;
  if ( a->z > b->z ) return  1;
  return 0;
}


static bool isValid3dPoint(const ON_3dPoint* a)
{
  return (ON_IS_VALID(a->x) && ON_IS_VALID(a->y) && ON_IS_VALID(a->z)) ? true : false;
}

static int compare3dPoint( const ON_3dPoint* a, const ON_3dPoint* b )
{
  const bool aValid = isValid3dPoint(a);
  const bool bValid = isValid3dPoint(b);
  if (aValid != bValid)
    return (aValid ? -1 : 1); // invalid points sort to end.
  if (false == aValid)
    return 0; // all invalid points are "equal"
  if ( a->x < b->x ) return -1;
  if ( a->x > b->x ) return  1;
  if ( a->y < b->y ) return -1;
  if ( a->y > b->y ) return  1;
  if ( a->z < b->z ) return -1;
  if ( a->z > b->z ) return  1;
  return 0;
}

typedef int (*ON_COMPAR_LPVOID_LPVOID)(const void*,const void*);

static 
unsigned int GetRemoveDegenerateFacesPointMap(
  unsigned int pt_count,
  const ON_3fPoint* fV,
  const ON_3dPoint* dV,
  ON_SimpleArray<unsigned int>& pt_map
)
{
  // Faster than ON_Mesh::GetVertexLocationIds()
  //  This static is used only in CullDegenerateFaces().
  //
  // Builds a mapping array, pt_map[], such that the length of pt_map[] 
  // is pt_count and pt_map[i] == pt_map[j] if and only if pt[i] == pt[j]
  // as 3d points.  The values in map[] run from 0 to max_pt_index.
  unsigned int vt0, vt1;
  ON_3fPoint fp0;
  ON_3dPoint dp0;
  unsigned int* map;
  unsigned int* index;
  unsigned int max_pt_index = 0;
  if (pt_count > 0 && (nullptr != dV || nullptr != fV))
  {
    index = (unsigned int*)onmalloc(pt_count*sizeof(*index));
    
    if ( dV )
      ON_Sort( ON::sort_algorithm::quick_sort, index, dV, pt_count, sizeof(*dV), (ON_COMPAR_LPVOID_LPVOID)compare3dPoint );
    else
      ON_Sort( ON::sort_algorithm::quick_sort, index, fV, pt_count, sizeof(*fV), (ON_COMPAR_LPVOID_LPVOID)compare3fPoint );
    
    pt_map.SetCapacity( pt_count );
    pt_map.SetCount( pt_count );
    map = pt_map.Array();
    for (vt0 = 0; vt0 < pt_count; vt0++)
      map[vt0] = ON_UNSET_UINT_INDEX;

    if ( dV )
    {
      for (vt0 = 0; vt0 < pt_count; vt0 = vt1, max_pt_index++) 
      {
        dp0 = dV[index[vt0]];
        for ( vt1=vt0+1; vt1<pt_count && 0==compare3dPoint(&dp0,dV+index[vt1]); vt1++ ) {
          // empty
        }
        while ( vt0 < vt1 ) {
          map[index[vt0++]] = max_pt_index;
        }
      }

      // invalid points are sorted to the end
      vt1 = pt_count;
      while (vt1-- > 0)
      {
        if (isValid3dPoint(dV + index[vt1]))
          break;
        map[index[vt1]] = ON_UNSET_UINT_INDEX; // invalid point get invalid index
      }
    }
    else
    {
      for (vt0 = 0; vt0 < pt_count; vt0 = vt1, max_pt_index++) 
      {
        fp0 = fV[index[vt0]];
        for ( vt1=vt0+1; vt1<pt_count && 0==compare3fPoint(&fp0,fV+index[vt1]); vt1++ ) {
          // empty
        }
        while ( vt0 < vt1 ) {
          map[index[vt0++]] = max_pt_index;
        }
      }

      // invalid points are sorted to the end
      vt1 = pt_count;
      while (vt1-- > 0)
      {
        if (isValid3fPoint(fV + index[vt1]))
          break;
        map[index[vt1]] = ON_UNSET_UINT_INDEX; // invalid point get invalid index
      }
    }
    onfree(index);
  }
  if ( max_pt_index == 0 )
    pt_map.Destroy();

  return max_pt_index;
}

unsigned int ON_Mesh::CullDegenerateFaces()
{
  const unsigned int face_count0 = m_F.UnsignedCount();
  
  DeleteComponents(
    nullptr,
    0,
    true,  // bIgnoreInvalidComponents
    true,  // bRemoveDegenerateFaces
    false, // bRemoveUnusedVertices
    true   // bRemoveEmptyNgons
    );

  const unsigned int face_count1 = m_F.UnsignedCount();

  return (face_count0 > face_count1) ? face_count0 - face_count1 : 0;
}

unsigned int ON_Mesh::CullDegenerates()
{
  const int mesh_vertex_count0 = VertexCount();
  const int mesh_face_count0 = FaceCount();
  const int mesh_quad_count0 = QuadCount();
  const int mesh_tri_count0 = TriangleCount();

  // now cull bad faces, invalid vertices, and unreferenced vertices
  DeleteComponents(
    nullptr,
    0,
    true,
    true,
    true,
    true
    );

  const int mesh_vertex_count1 = VertexUnsignedCount();
  const int mesh_face_count1 = FaceUnsignedCount();
  const int mesh_quad_count1 = QuadCount();
  const int mesh_tri_count1 = TriangleCount();
  if (
    mesh_vertex_count0 == mesh_vertex_count1
    && mesh_face_count0 == mesh_face_count1
    && mesh_quad_count0 == mesh_quad_count1
    && mesh_tri_count0 == mesh_tri_count1
    )
    return 0;

  int rc = abs(mesh_vertex_count1 - mesh_vertex_count0) + abs(mesh_face_count1 - mesh_face_count0);
  if (0 == rc)
  {
    // need to return nonzero if a degenerate quad got changed into a triangle
    rc = abs(mesh_quad_count1 - mesh_quad_count0);
    if (0 == rc)
    {
      rc = abs(mesh_tri_count1 - mesh_tri_count0);
    }
  }

  return (unsigned int)rc;
}

int ON_Mesh::CullUnusedVertices()
{
  const unsigned int vcount0 = m_V.UnsignedCount();

  DeleteComponents(
    nullptr, // ci_list
    0,       // ci_count
    true,    // bIgnoreInvalidComponents
    false,   // bRemoveDegenerateFaces
    true,    // bRemoveUnusedVertices
    false    // bRemoveEmptyNgons
    );

  if ( 0 == m_V.UnsignedCount() )
    Destroy();

  return ((int)(vcount0 - m_V.UnsignedCount()));
}

bool ON_Mesh::Compact()
{
  unsigned int meshVcount = m_V.UnsignedCount();
  unsigned int meshFcount = m_F.UnsignedCount();

  if (m_FN.UnsignedCount() != meshFcount)
    m_FN.Destroy();

  if (m_N.UnsignedCount() != meshVcount)
    m_N.Destroy();

  if (m_T.UnsignedCount() != meshVcount)
    m_T.Destroy();

  for (int i = m_TC.Count() - 1; i >= 0; i--)
  {
    if (m_TC[i].m_T.UnsignedCount() != meshVcount)
      m_TC.Remove(i);
  }

  if (m_S.UnsignedCount() != meshVcount)
    m_S.Destroy();

  if (m_K.UnsignedCount() != meshVcount)
    m_K.Destroy();

  if (m_C.UnsignedCount() != meshVcount)
    m_C.Destroy();

  if (m_H.UnsignedCount() != meshVcount)
    m_H.Destroy();

  CullUnusedVertices();

  m_V.Shrink();
  m_F.Shrink();
  m_N.Shrink();
  m_FN.Shrink();
  m_K.Shrink();
  m_C.Shrink();
  m_S.Shrink();
  m_T.Shrink();

  for (int i = 0; i < m_TC.Count(); i++)
    m_TC[i].m_T.Shrink();

  return true;
}

void ON_Mesh::Cleanup(
  bool bRemoveNgons, 
  bool bRemoveDegenerateFaces, 
  bool bCompact
  )
{
  V4V5_DestroyNgonList(); // old junk
  
  if ( bRemoveNgons )
    SetNgonCount(0);
  
  if (bRemoveDegenerateFaces)
    CullDegenerateFaces();

  DestroyRuntimeCache(true);  
  
  if ( bCompact )
    Compact();
}

void ON_Mesh::Cleanup(bool bRemoveNgons)
{
  const bool bRemoveDegenerateFaces = true;
  const bool bCompact = true;
  Cleanup(
    bRemoveNgons,
    bRemoveDegenerateFaces,
    bCompact
    );
}

////////////////////////////////////////////////////////////////
//
//   ON_SurfaceCurvature
//
const ON_SurfaceCurvature ON_SurfaceCurvature::CreateFromPrincipalCurvatures(
  double k1,
  double k2
)
{
  ON_SurfaceCurvature k;
  k.k1 = k1;
  k.k2 = k2;
  return k;
}

const ON_SurfaceCurvature ON_SurfaceCurvature::CreateFromGaussianAndMeanCurvatures(
  double gaussian_curvature,
  double mean_curvature
)
{
  if (ON_IS_VALID(gaussian_curvature) && ON_IS_VALID(mean_curvature))
  {
    const double r = mean_curvature * mean_curvature - gaussian_curvature;
    if (r >= 0.0)
    {
      const double k1 = mean_curvature + sqrt(r);
      const double k2 = mean_curvature - sqrt(r);
      return ON_SurfaceCurvature::CreateFromPrincipalCurvatures(k1, k2);
    }
    else if (r < 0.0)
    {
      // Dale Lear - March 2024 - RH-81078
      // We end up here when r < 0 and gaussian_curvature > 0.
      // We are in one of 3 cases:
      // 1) We are dealing with a very small and noisy negative r.
      // 2) We are dealing with esimates of mean and gaussian.        
      // 3) Something else that is uncommon.
      
      // In case 1, mean*mean and gaussian are both larger relative to fabs(r).
      // We don't know which input value is more precise, but people typically
      // care more about gaussian so we use k1=k2=sign(mean)*sqrt(gaussian) instead of
      // k1 = k2 = mean.
      // 
      // In case 2, the value of gaussian is typically more important than the value 
      // of mean, because people are often testing to see how a mesh can be flattened.
      //
      // So, we assume we are at or near an umbilic (k1=k2) and set them so that
      // k1*k2 = gaussian_curvature and sign(k1+k2) = sign(mean). 
      // These choices preserve gaussian minimize fabs( 0.5*(k1+k2) - mean_curvature).
      const double k1 = ((mean_curvature < 0.0) ? -1.0 : 1.0) * sqrt(gaussian_curvature);
      const double k2 = k1;
      return ON_SurfaceCurvature::CreateFromPrincipalCurvatures(k1, k2);
      // put a breakpoint on the line above to dectect when we are in
      // this unusual situation.
    } 
  }
  if (ON_IS_VALID(gaussian_curvature))
  {
    // It can happen that only Gaussian was estimated, whether on purpose or not.
    const double k1 = sqrt(fabs(gaussian_curvature));
    const double k2 = ((gaussian_curvature < 0.0) ? -1.0 : 1.0) * k1;
    return ON_SurfaceCurvature::CreateFromPrincipalCurvatures(k1, k2);
  }
  if (ON_IS_VALID(mean_curvature))
  {
    // It can also happen that only mean was estimated, whether on purpose or not.
    return ON_SurfaceCurvature::CreateFromPrincipalCurvatures(mean_curvature, mean_curvature);
  }
  return ON_SurfaceCurvature::Nan;
}

const ON_SurfaceCurvature ON_SurfaceCurvature::FlipSurfaceOrientation() const
{
  // negate and reverse the order of (this->k1, this->k2)
  return ON_SurfaceCurvature::CreateFromPrincipalCurvatures(-k2, -k1);
}

int ON_SurfaceCurvature::Compare(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs)
{
  if (lhs.IsNan())
    return rhs.IsNan() ? 0 : 1; // nans sort last
  if (rhs.IsNan())
    return -1;  // nans sort last
  if (lhs.k1 < rhs.k1)
    return -1;
  if (lhs.k1 > rhs.k1)
    return 1;
  if (lhs.k2 < rhs.k2)
    return -1;
  if (lhs.k2 > rhs.k2)
    return 1;
  return 0;
}

int ON_SurfaceCurvature::CompareMaximumAndMinimumPrincipalCurvatures(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs)
{
  const int rc = ON_SurfaceCurvature::CompareMaximumPrincipalCurvature(lhs, rhs);
  return 0 != rc ? rc : ON_SurfaceCurvature::CompareMinimumPrincipalCurvature(lhs, rhs);
}

int ON_SurfaceCurvature::CompareMaximumPrincipalCurvature(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs)
{
  return ON_DBL::CompareValue(lhs.MaximumPrincipalCurvature(), rhs.MaximumPrincipalCurvature());
}

int ON_SurfaceCurvature::CompareMinimumPrincipalCurvature(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs)
{
  return ON_DBL::CompareValue(lhs.MinimumPrincipalCurvature(), rhs.MinimumPrincipalCurvature());
}

int ON_SurfaceCurvature::CompareGaussianCurvature(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs)
{
  return ON_DBL::CompareValue(lhs.GaussianCurvature(), rhs.GaussianCurvature());
}

int ON_SurfaceCurvature::CompareMeanCurvature(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs)
{
  return ON_DBL::CompareValue(lhs.MeanCurvature(), rhs.MeanCurvature());
}

int ON_SurfaceCurvature::CompareMaximumRadius(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs)
{
  return ON_DBL::CompareValue(lhs.MaximumRadius(), rhs.MaximumRadius());
}

int ON_SurfaceCurvature::CompareMinimumRadius(const ON_SurfaceCurvature& lhs, const ON_SurfaceCurvature& rhs)
{
  return ON_DBL::CompareValue(lhs.MinimumRadius(), rhs.MinimumRadius());
}



double ON_SurfaceCurvature::KappaValue(ON::curvature_style kappa_style) const
{
  double k;
  switch (kappa_style)
  {
  case ON::gaussian_curvature:
    k = this->GaussianCurvature();
    break;

  case ON::mean_curvature:
    // fabs() is correct here.
    // Turns out the vast majority of users don't appear to care about 
    // signed mean curvature and find it confusing.
    k = fabs(this->MeanCurvature());
    break;

  case ON::min_curvature:
    k = this->MinimumRadius();
    break;

  case ON::max_curvature:
    k = this->MaximumRadius();
    break;

  default:
    k = ON_DBL_QNAN;
    break;
  }
  return k;
}

const ON_Color ON_SurfaceCurvatureColorMapping::Color(
  ON_SurfaceCurvature K
) const
{
  // This is the curvature analysis color used by the current version of Rhino.
  // The code can be updated as the method for assigning a color to surface curvatures changes.

  const double k = K.KappaValue(this->m_kappa_style);

  if (ON_IS_NAN(k))
    return ON_Color::UnsetColor;

  // convert k to hue
  const double mn = this->m_kappa_range.m_t[0];
  const double mx = this->m_kappa_range.m_t[1];
  double f;
  if (mn != mx)
  {
    const double d = 1.0 / (mx - mn);
    f = (mx - k) * d;
    if (f <= 0.0)
      f = 0.0;
    else if (f >= 1.0)
      f = 1.0;
  }
  else if (mn == mx)
  {
    if (k > mn)
      f = 0.0;
    else if (k < mn)
      f = 1.0;
    else
      f = 0.5;
  }
  else
    return ON_Color::UnsetColor;


  if (f >= 0.0 && f <= 1.0)
    return ON_Color::FromHueInRadians(this->m_hue_range_in_radians.ParameterAt(f));

  return ON_Color::UnsetColor;
}

bool ON_SurfaceCurvatureColorMapping::IsSet() const
{
  if (1 == this->m_is_set)
    return true;
  if (0 == this->m_is_set)
    return false;
  for (;;)
  {
    if ((int)(this->m_kappa_style) <= (int)(ON::curvature_style::unknown_curvature_style))
      break;
    if ((int)(this->m_kappa_style) >= (int)(ON::curvature_style::curvature_style_count))
      break;
    if (false == m_kappa_range.IsValid())
      break;
    if (false == m_hue_range_in_radians.IsValid())
      break;
    this->m_is_set = 1;
    return true;
  }
  this->m_is_set = 0;
  return false;
}

bool ON_SurfaceCurvatureColorMapping::IsUnset() const
{
  return this->IsSet() ? false : true;
}

bool operator==(const ON_SurfaceCurvatureColorMapping& lhs, const ON_SurfaceCurvatureColorMapping& rhs)
{
  // if any double is a nan, this compare must be false.
  const ON::curvature_style cs[2] = { lhs.KappaStyle(), rhs.KappaStyle() };
  if (cs[0] == cs[1])
  {
    const ON_Interval kr[2] = { lhs.KappaRange() ,rhs.KappaRange() };
    if (kr[0].m_t[0] == kr[1].m_t[0] && kr[0].m_t[1] == kr[1].m_t[1])
    {
      const ON_Interval hr[2] = { lhs.HueRangeInRadians() ,rhs.HueRangeInRadians() };
      if (hr[0].m_t[0] == hr[1].m_t[0] && hr[0].m_t[1] == hr[1].m_t[1])
        return true;
    }
  }
  return false;
}

bool operator!=(const ON_SurfaceCurvatureColorMapping& lhs, const ON_SurfaceCurvatureColorMapping& rhs)
{
  // if any double is a nan, this compare must be false.
  const ON::curvature_style cs[2] = { lhs.KappaStyle(), rhs.KappaStyle() };
  if (cs[0] != cs[1])
  {
    const ON_Interval kr[2] = { lhs.KappaRange() ,rhs.KappaRange() };
    if (kr[0].m_t[0] != kr[1].m_t[0] || kr[0].m_t[1] != kr[1].m_t[1])
    {
      const ON_Interval hr[2] = { lhs.HueRangeInRadians() ,rhs.HueRangeInRadians() };
      if (hr[0].m_t[0] != hr[1].m_t[0] || hr[0].m_t[1] != hr[1].m_t[1])
      {
        // any compare involving nans is false
        if (ON_IS_NAN(kr[0].m_t[0]) || ON_IS_NAN(kr[0].m_t[1]) || ON_IS_NAN(kr[1].m_t[0]) || ON_IS_NAN(kr[1].m_t[1]))
          return false;
        if (ON_IS_NAN(hr[0].m_t[0]) || ON_IS_NAN(hr[0].m_t[1]) || ON_IS_NAN(hr[1].m_t[0]) || ON_IS_NAN(hr[1].m_t[1]))
          return false;

        return true;
      }
    }
  }
  return false;
}

bool operator==(
  const ON_SurfaceCurvature& lhs,
  const ON_SurfaceCurvature& rhs
  )
{
  return (lhs.k1 == rhs.k1 && lhs.k2 == rhs.k2);
}

bool operator!=(
  const ON_SurfaceCurvature& lhs,
  const ON_SurfaceCurvature& rhs
  )
{
  // Note well: 
  // ON_SurfaceCurvature::IsNan() is true if either of k1 or k2 is a nan.
  // and the code below is correct.
  return (lhs.k1 != rhs.k1 || lhs.k2 != rhs.k2) || (lhs.IsNan() && rhs.IsNan());
}

bool ON_SurfaceCurvature::IsSet() const
{
  return (ON_UNSET_VALUE < k1 && k1 < ON_UNSET_POSITIVE_VALUE && ON_UNSET_VALUE < k2 && k2 < ON_UNSET_POSITIVE_VALUE);
}

bool ON_SurfaceCurvature::IsZero() const
{
  return (0.0 == k1 && 0.0 == k2);
}

bool ON_SurfaceCurvature::IsUnset() const
{
  return IsSet() ? false : true;
}

bool ON_SurfaceCurvature::IsNan() const
{
  return (ON_IS_NAN(k1) || ON_IS_NAN(k2));
}


double ON_SurfaceCurvature::MaximumPrincipalCurvature() const
{
  return IsSet() ? ((k1 >= k2) ? k1 : k2) : ON_DBL_QNAN;
}

double ON_SurfaceCurvature::MinimumPrincipalCurvature() const
{
  return IsSet() ? ((k1 <= k2) ? k1 : k2) : ON_DBL_QNAN;
}

double ON_SurfaceCurvature::GaussianCurvature() const
{
  return (ON_IS_VALID(k1) && ON_IS_VALID(k2)) ? (k1 * k2) : ON_DBL_QNAN;
}

double ON_SurfaceCurvature::MeanCurvature() const
{
  return (ON_IS_VALID(k1) && ON_IS_VALID(k2)) ? ((k1 == k2) ? k1 : 0.5 * (k1 + k2)) : ON_DBL_QNAN;
}

double ON_SurfaceCurvature::MinimumRadius() const
{
  if (ON_IS_VALID(k1) && ON_IS_VALID(k2))
  {
    // k = maximum directional curvature
    const double k = (fabs(k1) >= fabs(k2)) ? fabs(k1) : fabs(k2); 

    // 1/k = minimum radius of curvature
    return
      (k > (1.0 / ON_SurfaceCurvature::InfinteRadius)) 
      ? 1.0 / k 
      : ON_SurfaceCurvature::InfinteRadius;
  }

  return ON_DBL_QNAN;
}

double ON_SurfaceCurvature::MaximumRadius() const
{
  if (ON_IS_VALID(k1) && ON_IS_VALID(k2))
  {
    // k = minimum directional curvature
    double k;
    if (ON_DBL::Sign(k1)*ON_DBL::Sign(k2) <= 0 || fabs(k1) <= 1e-300 || fabs(k2) <= 1e-300)
    {
      // If principal curvatures have opposite signs,
      // there is a direction with zero directional curvature.
      k = 0.0;
    }
    else
    {
      // The minimum directional curvature is in a principal curvature direction.
      k = (fabs(k1) <= fabs(k2)) ? fabs(k1) : fabs(k2);
    }

    // 1/k = maximum radius of curvature
    return
      (k > (1.0 / ON_SurfaceCurvature::InfinteRadius))
      ? 1.0 / k 
      : ON_SurfaceCurvature::InfinteRadius; 
  }

  return ON_DBL_QNAN;
}

ON_MeshTopology::ON_MeshTopology() 
: m_mesh(0)
, m_memchunk(0)
, m_b32IsValid(0)
{
}

ON_MeshTopology::~ON_MeshTopology()
{
  Destroy();
}

void ON_MeshTopology::Destroy()
{
  m_topv_map.Destroy();
  m_topv.Destroy();
  m_tope.Destroy();
  m_topf.Destroy();
  struct memchunk *p, *n;
  n = m_memchunk;
  while(n)
  {
    p = n;
    n = n->next;
    onfree(p);
  }
  m_memchunk = 0;
  if ( -1 != m_b32IsValid)
    m_b32IsValid = 0;
}

void ON_MeshTopology::EmergencyDestroy()
{
  m_mesh = 0;
  m_topv_map.EmergencyDestroy();
  m_topv.EmergencyDestroy();
  m_tope.EmergencyDestroy();
  m_topf.EmergencyDestroy();
  m_memchunk = 0;
  m_b32IsValid = 0;
}

int ON_MeshTopology::TopVertexCount() const
{
  return m_topv.Count();
}

//////////
// number of topoligical edges
int ON_MeshTopology::TopEdgeCount() const
{
  return m_tope.Count();
}

//////////
// number of topoligical faces (same as m_mesh.FaceCount())
int ON_MeshTopology::TopFaceCount() const
{
  return m_topf.Count();
}

ON_3dPoint ON_MeshTopology::TopVertexPoint(int vtopi) const
{

  const int mesh_vertex_index = m_topv[vtopi].m_vi[0];
  if (mesh_vertex_index >= 0)
  {
    const unsigned int vertex_count = m_mesh->VertexUnsignedCount();
    if ((unsigned int)mesh_vertex_index < vertex_count)
    {
      if (vertex_count == m_mesh->m_dV.UnsignedCount())
        return m_mesh->m_dV[mesh_vertex_index];
      if (vertex_count == m_mesh->m_V.UnsignedCount())
        return m_mesh->m_V[mesh_vertex_index];
    }
  }
  ON_ERROR("Invalid topology");
  return  ON_3dPoint::NanPoint;
}

ON_Line ON_MeshTopology::TopEdgeLine( int tope_index ) const
{
  ON_Line L(ON_3dPoint::UnsetPoint,ON_3dPoint::UnsetPoint);
  if ( m_mesh && tope_index >= 0 && tope_index < m_tope.Count() )
  {
    const int* topvi = m_tope[tope_index].m_topvi;
    if (   topvi[0] >= 0 && topvi[0] < m_topv.Count() 
        && topvi[1] >= 0 && topvi[1] < m_topv.Count() )
    {
      const ON_MeshTopologyVertex& v0 = m_topv[topvi[0]];
      const ON_MeshTopologyVertex& v1 = m_topv[topvi[1]];
      if ( v0.m_v_count > 0 && v0.m_vi && v1.m_v_count > 0 && v1.m_vi )
      {
        int vi0 = v0.m_vi[0];
        int vi1 = v1.m_vi[0];
        int vcount = m_mesh->m_V.Count();
        if ( vi0 >= 0 && vi0 < vcount && vi1 >= 0 && vi1 < vcount )
        {
          const ON_3dPointListRef vertex_list(m_mesh);
          L.from = vertex_list[vi0];
          L.to   = vertex_list[vi1];
        }
      }
    }
  }
  return L;
}

////////
// returns index of edge that connects topological vertices
// returns -1 if no edge is found.
int ON_MeshTopology::TopEdge( int vtopi0, int vtopi1 ) const
{
  int i0, i1, ei, vi0;
  if ( vtopi0 > vtopi1 ) {vi0 = vtopi0; vtopi0 = vtopi1; vtopi1 = vi0;}
  if ( vtopi0 < vtopi1 ) {
    const int tope_count = TopEdgeCount();
    const ON_MeshTopologyEdge* tope = m_tope.Array(); // to speed array access
    i0 = 0;
    i1 = tope_count;
    while ( i0 < i1 )
    {
      ei = (i0+i1)/2;
      vi0 = tope[ei].m_topvi[0];
      if ( vi0 < vtopi0 ) {
        if ( i0 == ei )
          break;
        i0 = ei;
      }
      else if ( vi0 > vtopi0 ) {
        if ( i1 == ei )
          break;
        i1 = ei;
      }
      else {
        while (ei > 0 && tope[ei-1].m_topvi[0] == vtopi0 )
          ei--;
        while ( ei < tope_count && tope[ei].m_topvi[0] == vtopi0 ) {
          if ( tope[ei].m_topvi[1] == vtopi1 )
            return ei;
          ei++;
        }
        break;
      }
    }
  }
  return -1;
}

bool ON_MeshTopology::GetTopFaceVertices( int fi, int topvi[4] ) const
{
  if ( fi >= 0 && fi < m_mesh->m_F.Count() ) {
    const int* fvi = m_mesh->m_F[fi].vi;
    topvi[0] = m_topv_map[fvi[0]];
    topvi[1] = m_topv_map[fvi[1]];
    topvi[2] = m_topv_map[fvi[2]];
    topvi[3] = m_topv_map[fvi[3]];
  }
  return true;
}

bool ON_MeshTopology::SortVertexEdges() const
{
  bool rc = true;
  int topvi, topv_count = m_topv.Count();
  for ( topvi = 0; topvi < topv_count; topvi++ )
  {
    if ( !SortVertexEdges(topvi) )
      rc = false;
  }
  return rc;
}

// TODO make public and add to header file new ON_SortIntArray
static
void ON_ReverseIntArray(
        int* e,    // array of ints
        size_t  nel   // length of array
        )
{
  int ei;
  size_t i;
  nel--;
  for ( i = 0; i<nel; i++, nel--)
  {
    ei = e[i];
    e[i] = e[nel];
    e[nel] = ei;
  }
}

bool ON_MeshTopology::SortVertexEdges(int topvi) const
{
  if ( topvi < 0 || topvi >= m_topv.Count() )
    return false;

  const ON_MeshTopologyVertex& topv = m_topv[topvi];
  if ( topv.m_tope_count < 2 )
    return true;

  // Divide the edges that use this vertex into two sets:
  //   e1f[] = indices of edges that bound 1 face, 3 or 
  //           more faces, or no faces (in that order).
  //   e2f[] = indices of edges that bound exactly 2 faces.
  int i, j;
  int topei;
  int vei;
  int efcnt;
  ON_SimpleArray<int> new_tope_buffer(5*topv.m_tope_count);
  new_tope_buffer.SetCount(5*topv.m_tope_count);
  int* new_tope = new_tope_buffer.Array();
  int* e2f  = new_tope + topv.m_tope_count;
  int* e1f  = e2f + topv.m_tope_count;
  int e1fcnt = 0;
  int e2fcnt = 0;
  {
    int* e3f  = e1f + topv.m_tope_count; // e3f[] = edges with 3 or more faces
    int* e0f  = e3f + topv.m_tope_count; // e0f[] = edges with no faces
    int e3fcnt = 0;
    int e0fcnt = 0;

    for ( vei = 0; vei < topv.m_tope_count; vei++ )
    {
      topei = topv.m_topei[vei];
      if ( topei >= 0 && topei < m_tope.Count() )
      {
        const ON_MeshTopologyEdge& tope = m_tope[topei];
        if ( tope.m_topvi[0] == topvi || tope.m_topvi[1] == topvi )
        {
          efcnt = m_tope[topei].m_topf_count;
          if ( efcnt < 0 )
          {
            ON_ERROR("ON_MeshTopology::SortVertexEdges(int topvi) - m_tope[topei].m_topf_count < 0"); 
            return false;
          }
          switch(efcnt)
          {
          case 0: // edge has no faces 
            // (never happens if topology is from a valid ON_Mesh.)
            e0f[e0fcnt++] = topei;                                   
            break;

          case 1: // edge has exactly one face
            e1f[e1fcnt++] = topei; 
            break;

          case 2: // edge has exactly two faces
            e2f[e2fcnt++] = topei;
            break;

          default: // edge has 3 or more faces
            // (happens when mesh is non-manifold)
            e3f[e3fcnt++] = topei;
            break;
          }
        }
      }
    }
  
    // append list of non-manifold edges (3 or more faces) to e1f[]
    for ( i = 0; i < e3fcnt; i++ )
    {
      e1f[e1fcnt++] = e3f[i];
    }

    // append list of wire edges (0 faces) to e1f[]
    for ( i = 0; i < e0fcnt; i++ )
    {
      e1f[e1fcnt++] = e0f[i];
    }

    e0fcnt = 0;
    e3fcnt = 0;
    e0f = 0;
    e3f = 0;
  }

  // Put the edge indices in new_tope[] in radial order.
  // NOTE: The code below works for non-oriented meshes and
  //       non-manifold meshes.  If you change the code, you
  //       must make sure that it still works in these cases.
  if ( e1fcnt + e2fcnt != topv.m_tope_count )
  {
    ON_ERROR("ON_MeshTopology::SortVertexEdges() input vertex had bogus m_topei[]");
    return false;
  }
  int fi = -1;
  int next_topei = -1;
  int efi, fecnt, fei, next_fei;
  vei = 0;
  int vei0 = 0;
  int vei1 = 0;
  int elist_dir = 0;
  while(vei < topv.m_tope_count)
  {
    if ( next_topei >= 0 )
    {
      // continue with this group of edges
      topei = next_topei;
      next_topei = -1;
    }
    else if ( e1fcnt > 0 )
    {
      // start a new group of edges
      topei = *e1f++;
      e1fcnt--;
      vei1 = vei;
    }
    else if ( e2fcnt > 0 )
    {
      // start a new group of edges
      // (this only happens in non-manifold cases)
      topei = *e2f++;
      e2fcnt--;
      vei1 = vei;
    }
    else
    {
      ON_ERROR("ON_MeshTopology::SortVertexEdges() input vertex had bogus topology information.");
      return false;
    }

    if ( vei0 < vei1 )
    {
      if ( 1 == elist_dir )
      {
        // 30 December 2003 Dale Lear added this feature
        //   edges new_tope[vei0],...,new_tope[vei1-1] are radially sorted
        //   but the order is not counterclockwise with respect to
        //   the normal of the face attached to the first edge.
        //   So, this group of edges in new_tope[] needs to
        //   be reversed.
        ON_ReverseIntArray( new_tope+vei0, vei1-vei0 );
      }
      elist_dir = 0;
      vei0 = vei1;
    }

    new_tope[vei++] = topei;

    // search faces connected to tope for the next edge
    const ON_MeshTopologyEdge& tope = m_tope[topei];
    for ( efi = 0; next_topei < 0 && efi < tope.m_topf_count; efi++ )
    {
      fi = tope.m_topfi[efi];
      if ( fi < 0 || fi >= m_topf.Count() )
      {
        // bogus face index into m_topf[] array
        continue;
      }

      // find fei so that topf.m_topei[fei] = topei
      const ON_MeshTopologyFace& topf = m_topf[fi];
      fecnt = topf.IsQuad() ? 4 : 3;
      for ( fei = 0; fei < fecnt; fei++ )
      {
        if ( topf.m_topei[fei] != topei )
          continue;

        if ( tope.m_topvi[0] == topvi )
        {
          next_fei = ( topf.m_reve[fei] ) ?  1 : -1;
        }
        else
        {
          next_fei = ( topf.m_reve[fei] ) ? -1 :  1;
        }

        if ( 0 == elist_dir )
          elist_dir = next_fei;

        next_fei = (fei+next_fei+fecnt)%fecnt;
        next_topei = topf.m_topei[next_fei];

        // next_topei = candidate for the next edge
        //  Check to see that it is available by
        //  finding it in the e1f[] or e2f[] arrays.
        j = 0;
        for ( i = 0; i < e1fcnt; i++ )
        {
          if ( next_topei == e1f[i] )
          {
            // found it in the e1f list.
            for ( j = i+1; j < e1fcnt; j++ )
              e1f[j-1] = e1f[j];
            e1fcnt--;
            break;
          }
        }
        if ( 0 == j )
        {
          // search the e2f[] list
          for ( i = 0; i < e2fcnt; i++ )
          {
            if ( next_topei == e2f[i] )
            {
              for ( j = i+1; j < e2fcnt; j++ )
                e2f[j-1] = e2f[j];
              e2fcnt--;
              break;
            }
          }
        }
        if ( 0 == j )
        {
          // the candidate was already used, check the next
          // face attached to this edge.
          next_topei = -1;
        }
        else
        {
          break;
        }
      }
    }
  }

  if ( topv.m_tope_count != vei )
  {
    ON_ERROR("ON_MeshTopology::SortVertexEdges() edge sorting error.");
    return false;
  }

  vei1 = vei;
  if ( vei0 < vei1 )
  {
    if ( 1 == elist_dir )
    {
      // 30 December 2003 Dale Lear added this feature
      //   edges new_tope[vei0],...,new_tope[vei1-1] are radially sorted
      //   but the order is not counterclockwise with respect to
      //   the normal of the face attached to the first edge.
      //   So, this group of edges in new_tope[] needs to
      //   be reversed.
      ON_ReverseIntArray( new_tope+vei0, vei1-vei0 );
    }
    elist_dir = 0;
    vei0 = vei1;
  }

  int* topv_m_topei = const_cast<int*>(topv.m_topei);
  for ( vei = 0; vei < topv.m_tope_count; vei++ )
  {
    topv_m_topei[vei] = new_tope[vei];
  }

  return true;
}

int* ON_MeshTopology::GetIntArray(int length)
{
  int* a = 0;
  if ( length > 0 ) {
    struct memchunk* pm;
    pm = (struct memchunk*)onmalloc(length*sizeof(*a) + sizeof(*pm));
    if ( pm ) {
      pm->next = m_memchunk;
      m_memchunk = pm++;
      a = (int*)pm;
    }
  }
  return a;
}

bool ON_MeshTopology::IsWeldedEdge(int top_ei) const
{
  if (top_ei < 0 || top_ei >= m_tope.Count() || nullptr == m_mesh)
    return false;

  const ON_MeshTopologyEdge& e = m_tope[top_ei];
  if (e.m_topf_count <= 1 || e.m_topvi[0] < 0 || e.m_topvi[1] < 0)
    return false;

  const int face_count = m_topf.Count();
  if (face_count < 2 || face_count != m_mesh->FaceCount())
    return false;

  if (e.m_topvi[0] < 0 || e.m_topvi[1] < 0 || e.m_topvi[0] == e.m_topvi[1] )
    return false;
  const int topv_count = m_topv.Count();
  if (e.m_topvi[0] >= topv_count || e.m_topvi[1] >= topv_count || topv_count < 3)
    return false;

  const int meshv_count = m_mesh->VertexCount();
  if (meshv_count < topv_count || meshv_count != m_topv_map.Count())
    return false;
  if (1 == m_topv[e.m_topvi[0]].m_v_count && 1 == m_topv[e.m_topvi[1]].m_v_count)
    return true;

  // need to examine faces
  int mesh_vi[2] = { -1,-1 };
  for (int efi = 0; efi < e.m_topf_count; ++efi)
  {
    int top_fi = e.m_topfi[efi];
    if (top_fi < 0 || top_fi >= face_count)
      return false;
    const ON_MeshTopologyFace& f = m_topf[top_fi];
    const int fe_count = f.IsTriangle() ? 3 : 4;
    int fvi[2] = { -1, -1 };
    for (int fei = 0; fei < fe_count; ++fei)
    {
      if (top_ei != f.m_topei[fei])
        continue;
      const ON_MeshFace& mf = m_mesh->m_F[top_fi];
      const bool bRev = f.m_reve[fei];
      fvi[bRev?1:0] = mf.vi[(fei + fe_count - 1) % fe_count];
      fvi[bRev?0:1] = mf.vi[fei];
      if (fvi[0] < 0 || fvi[0] >= meshv_count)
        return false;
      if (fvi[1] < 0 || fvi[1] >= meshv_count)
        return false;
      if (m_topv_map[fvi[0]] != e.m_topvi[0] || m_topv_map[fvi[1]] != e.m_topvi[1])
      {
        ON_ERROR("Bug in this loop or bad mesh topology.");
        fvi[0] = -1;
        fvi[1] = -1;
        continue;
      }
      break;
    }
    if (0 == efi)
    {
      if (fvi[0] < 0 || fvi[1] < 0 || fvi[0] == fvi[1])
        return false;
      mesh_vi[0] = fvi[0];
      mesh_vi[1] = fvi[1];
    }
    else
    {
      if (mesh_vi[0] != fvi[0])
        return false;
      if (mesh_vi[1] != fvi[1])
        return false;
    }
  }

  return (mesh_vi[0] >= 0 && mesh_vi[1]);
}


bool ON_MeshTopologyFace::IsTriangle() const
{
  return ( m_topei[2] == m_topei[3] && m_topei[0] != m_topei[1] )
         ? true : false;
}

bool ON_MeshTopologyFace::IsQuad() const
{
  return ( m_topei[2] != m_topei[3] ) ? true : false;
}

bool ON_MeshTopologyFace::IsValid() const
{
  return ( m_topei[0] != m_topei[1] ) ? true : false;
}


bool ON_MeshTopology::IsValid() const
{
  ON_Workspace ws;
  int topvi, topei, topfi, vi, fi, j, jmax, k, tfvi[4];
  ON_3fPoint p;

  WaitUntilReady(0);

  // simple checks
  if ( 1 != m_b32IsValid )
    return false;
  if ( !m_mesh )
    return false;
  if ( this != &(m_mesh->Topology()) )
    return false;
  const int v_count = m_mesh->VertexCount();
  const int f_count = m_mesh->FaceCount();
  const int topv_count = TopVertexCount();
  const int tope_count = TopEdgeCount();
  const int topf_count = TopFaceCount();
  if ( topv_count > v_count || topv_count < 0 )
    return false;
  if ( topv_count == 0 && v_count > 0 )
    return false;
  if ( topf_count != f_count )
    return false;
  if ( f_count > 0 && tope_count < 3 )
    return false;
  if ( m_topv_map.Count() != v_count )
    return false;

  // check vertex information
  for ( vi = 0; vi < v_count; vi++ ) {
    topvi = m_topv_map[vi];
    if ( topvi < 0 || topvi >= topv_count )
      return false;
  }

  char* vCheck = (char*)ws.GetMemory( v_count*sizeof(*vCheck) );
  memset( vCheck, 0, v_count*sizeof(*vCheck) );
  for ( topvi = 0; topvi < topv_count; topvi++ )
  {
    const ON_MeshTopologyVertex& topv = m_topv[topvi];
    if ( topv.m_v_count <= 0 )
      return false;
    if ( !topv.m_vi )
      return false;
    p = TopVertexPoint(topvi);
    for ( j = 0; j < topv.m_v_count; j++ ) {
      vi = topv.m_vi[j];
      if ( vi < 0 )
        return false;
      if ( vi >= v_count )
        return false;
      if ( vCheck[vi] != 0 )
        return false; // mesh.m_V[vi] is referenced multiple times
      if ( compare3fPoint( &p, &m_mesh->m_V[vi] ) )
        return false; // mesh.m_V[vi] not at same location as topv
      if ( m_topv_map[vi] != topvi )
        return false; 
      vCheck[vi] = 1;
    }

    // check that edges in m_topei[] list have topvi has a start/end
    if ( topv.m_tope_count < 0 )
      return false;
    if ( topv.m_tope_count == 0 && topv.m_topei )
      return false; // array should be nullptr
    if ( topv.m_tope_count > 0 && !topv.m_topei )
      return false; // array should not be nullptr
    for ( j = 0; j < topv.m_tope_count; j++ ) {
      topei = topv.m_topei[j];
      if ( topei < 0 )
        return false;
      if ( topei >= tope_count )
        return false;
      const ON_MeshTopologyEdge& tope = m_tope[topei];
      if ( tope.m_topvi[0] != topvi && tope.m_topvi[1] != topvi )
        return false; // edge doesn't reference this top vtx
      for ( k = 0; k < j; k++ ) {
        if ( topv.m_topei[k] == topei )
          return false; // edge listed multiple times
      }
    }
  }

  // make sure every mesh.m_V[] maps to a topological vertex
  for ( vi = 0; vi < v_count; vi++ ) {
    if ( vCheck[vi] != 1 )
      return false; // mesh.m_V[vi] is not referenced
    topvi = m_topv_map[vi];
    if ( topvi < 0 )
      return false;
    if ( topvi >= topv_count )
      return false;
    const ON_MeshTopologyVertex& topv = m_topv[topvi];
    for ( j = 0; j < topv.m_v_count; j++ ) {
      if ( topv.m_vi[j] == vi )
        break;
    }
    if ( j >= topv.m_v_count )
      return false; // bogus m_topv_map[] array
  }

  // check edges
  for ( topei = 0; topei < tope_count; topei++ ) {
    const ON_MeshTopologyEdge& tope = m_tope[topei];
    if ( tope.m_topvi[0] < 0 || tope.m_topvi[0] >= topv_count )
      return false;
    if ( tope.m_topvi[1] < 0 || tope.m_topvi[1] >= topv_count )
      return false;
    if ( tope.m_topvi[0] == tope.m_topvi[1] )
      return false;

    const ON_MeshTopologyVertex& topv0 = m_topv[tope.m_topvi[0]];
    for ( j = 0; j < topv0.m_tope_count; j++ ) {
      if ( topv0.m_topei[j] == topei )
        break;
    }
    if ( j >= topv0.m_tope_count )
      return false; // start vtx not linked to edge

    const ON_MeshTopologyVertex& topv1 = m_topv[tope.m_topvi[1]];
    for ( j = 0; j < topv1.m_tope_count; j++ ) {
      if ( topv1.m_topei[j] == topei )
        break;
    }
    if ( j >= topv1.m_tope_count )
      return false; // end vtx not linked to edge

    if ( tope.m_topf_count < 0 )
      return false;
    if ( tope.m_topf_count == 0 && tope.m_topfi )
      return false; // array should be nullptr
    if ( tope.m_topf_count > 0 && !tope.m_topfi )
      return false; // array should not be nullptr
    for ( j = 0; j < tope.m_topf_count; j++ ) {
      fi = tope.m_topfi[j];
      if ( fi < 0 || fi >= f_count )
        return false;
      const ON_MeshTopologyFace& topf = m_topf[fi];
      for ( k = 0; k < 4; k++ ) {
        if ( topf.m_topei[k] == topei )
          break;
      }
      if ( k >= 4 )
        return false; // edge not in face's list
    }
  }

  // check faces
  for ( fi = 0; fi < f_count; fi++ ) {
    topfi = fi;
    const ON_MeshTopologyFace& topf = m_topf[topfi];
    const ON_MeshFace& f = m_mesh->m_F[fi];
    if ( topf.m_topei[0] < 0 || topf.m_topei[0] >= tope_count )
      return false;
    if ( topf.m_topei[1] < 0 || topf.m_topei[1] >= tope_count )
      return false;
    if ( topf.m_topei[2] < 0 || topf.m_topei[2] >= tope_count )
      return false;
    if ( topf.m_topei[3] < 0 || topf.m_topei[3] >= tope_count )
      return false;
    tfvi[0] = m_topv_map[f.vi[0]];
    tfvi[1] = m_topv_map[f.vi[1]];
    tfvi[2] = m_topv_map[f.vi[2]];
    tfvi[3] = m_topv_map[f.vi[3]];
    if (    topf.m_topei[0] != 0 || topf.m_topei[1] != 0 
         || topf.m_topei[2] != 0 || topf.m_topei[3] != 0 ) {
      if ( !f.IsValid(v_count) )
        return false;
      if ( f.IsTriangle() ) {
        if (topf.m_topei[2] != topf.m_topei[3] )
          return false;
        jmax = 3;
      }
      else {
        if (topf.m_topei[2] == topf.m_topei[3] )
          return false;
        jmax = 4;
      }
      for ( j = 0; j < jmax; j++ ) {
        const ON_MeshTopologyEdge& tope = m_tope[topf.m_topei[j]];
        for ( k = 0; k < tope.m_topf_count; k++ ) {
          if ( tope.m_topfi[k] == topfi )
            break;
        }
        if ( k >= tope.m_topf_count )
          return false;

        // topedge m_tope[topf.m_topei[j]] ENDS at topvtx m_topv[tfvi[j]]
        if ( topf.m_reve[j] ) {
          if ( tope.m_topvi[1] != tfvi[(j+3)%4] )
            return false;
          if ( tope.m_topvi[0] != tfvi[j] )
            return false;
        }
        else {
          if ( tope.m_topvi[0] != tfvi[(j+3)%4] )
            return false;
          if ( tope.m_topvi[1] != tfvi[j] )
            return false;
        }
      }      
    }
    else {
      // all topf.m_topei[] must be zeros
      if (    topf.m_topei[0] != 0 || topf.m_topei[1] != 0 
           || topf.m_topei[2] != 0 || topf.m_topei[3] != 0 )
        return false;
    }
  }
  return true;
}

void ON_MeshTopology::Dump( ON_TextLog& dump ) const
{
  ON_3fPoint p;
  int vi, ei, fi, j;
  const int topv_count = m_topv.Count();
  const int tope_count = m_tope.Count();
  const int topf_count = m_topf.Count();

  // topological vertex information
  for ( vi = 0; vi < topv_count; vi++ ) {
    const ON_MeshTopologyVertex& v = m_topv[vi];
    dump.Print("topv %d: ",vi);
    if (m_mesh) {
      // dump geometric location of this vertex
      p = m_mesh->m_V[v.m_vi[0]];
      dump.Print("{%g,%g,%g} ", p.x, p.y, p.z);
    }

    // list all mesh geometry vertices that are coincident with this
    // topological vertex
    dump.Print("(");
    for ( j = 0; j < v.m_v_count; j++ ) {
      if ( j )
        dump.Print(",");
      dump.Print("m_V[%d]",v.m_vi[j]);
    }

    // list all topological edges that begin/end at this topological vertex
    dump.Print(") (");
    for ( j = 0; j < v.m_tope_count; j++ ) {
      if ( j )
        dump.Print(",");
      dump.Print("%d",v.m_topei[j]);
    }
    dump.Print(")\n");
  }

  // topological edge information
  for ( ei = 0; ei < tope_count; ei++ ) {
    const ON_MeshTopologyEdge& e = m_tope[ei];
    dump.Print("tope %d: topv%d to topvv%d (", ei, e.m_topvi[0], e.m_topvi[1] );
    // list all mesh topological faces attached to this topological edge
    for ( j = 0; j < e.m_topf_count; j++ ) {
      if (j)
        dump.Print(",");
      dump.Print("f%d",e.m_topfi[j]);
    }
    dump.Print(")\n");
  }

  // topological face information
  // mesh m_F[] index = mesh topology m_topf[] index
  for ( fi = 0; fi < topf_count; fi++ ) {
    const ON_MeshTopologyFace& f = m_topf[fi];
    dump.Print("topf %d: (",fi);
    for ( j = 0; j < 4; j++ ) {
      if ( j == 3 && f.m_topei[3] == f.m_topei[2] )
        break; // triangular face
      if (j)
        dump.Print(",");
      dump.Print("%ce%d",f.m_reve[j]?'-':'+',f.m_topei[j]);
    }
    dump.Print(")\n");
  }
}


bool ON_MeshTopology::Create()
{
  // When -1 == m_b32IsValid, this ON_MeshTopology
  // is the m_top field on an ON_Mesh and is being
  // created in an ON_Mesh::Topology() call and a
  // sleep lock is used to keep ON_Mesh::Topology()
  // thread safe.
  //
  // When 0 == m_b32IsValid, this ON_MeshTopology
  // is being created stand alone.
  //
  // When 1 == m_b32IsValid, this ON_MeshTopology
  // is already created and valid.

  if ( 1 == m_b32IsValid )
    return true;

  const int b32IsValid0 = m_b32IsValid;

  if ( 0 == b32IsValid0 )
  {
    // no sleep lock is being used
    m_b32IsValid = -1;
  }
  int b32IsValid = b32IsValid0;

  while ( 0 == b32IsValid || -1 == b32IsValid ) 
  {
    // while() is for flow control - this is a while() {... break;} statement.
    Destroy();
    b32IsValid = 0;

    // build vertex topology information
    const int fcount = m_mesh->FaceCount();
    const int vcount = m_mesh->VertexCount();
    if ( 0 == vcount )
      break;

    unsigned int* vindex = (unsigned int*)GetIntArray(vcount);
    m_topv_map.SetCapacity( vcount );
    m_topv_map.SetCount( vcount );
    if (  0 == m_mesh->GetVertexLocationIds( 
      0, // first id
      (unsigned int*)m_topv_map.Array(), // vertex ids returned here
      vindex
      ) )
    {
      Destroy();
      break;
    }

    {
      int topv_count = m_topv_map[vindex[vcount-1]]+1;
      m_topv_map.SetCapacity( vcount );
      m_topv_map.SetCount( vcount );
      m_topv.SetCapacity( topv_count );
      int vt0, vt1, topvi;
      for (vt0 = 0; vt0 < vcount; vt0 = vt1)
      {
        topvi = m_topv.Count();
#if defined(ON_DEBUG)
        if ( topvi != m_topv_map[vindex[vt0]] )
        {
          // 20 April 2010 Dale Lear:
          //  If you get this error, save the mesh and tell Dale Lear.
          ON_ERROR("ON_MeshTopology::Create() - topvi != vertex id from GetVertexLocationIds()");
        }
#endif
        ON_MeshTopologyVertex& topv = m_topv.AppendNew();
        topv.m_vi = (const int*)(vindex+vt0);
        for ( vt1=vt0+1; vt1<vcount && topvi == m_topv_map[vindex[vt1]]; vt1++ ) {
          // empty
        }
        topv.m_v_count = vt1-vt0;
      }
    }

    // build edge topology information
    const int topv_count = m_topv.Count();
    if ( topv_count >= 2 ) 
    {
      bool rc = false;
      int ei, ecnt, vi0, vi1, fi, efi, topfvi[4];
      ON_MeshFace f;

      if ( fcount > 0 && vcount > 0 ) 
      {
        // When working on this code be sure to test bug# 9271 and 9254 and file fsv_r4.3dm
        ON_Workspace ws;
        ON_MeshFaceSide* e = (ON_MeshFaceSide*)ws.GetMemory( 4*fcount*sizeof(*e) );
        ecnt = m_mesh->GetMeshFaceSideList( (const unsigned int*)m_topv_map.Array(), e );
        
        if ( ecnt > 0 ) 
        {
          rc = true;
          ON_MeshFaceSide::SortByVertexIndex( e, ecnt );

          // count number of topological edges and allocate storage
          int etop_count = 0;
          ei = 0;
          while( ei < ecnt ) 
          {
            vi0 = e[ei].m_vi[0];
            vi1 = e[ei].m_vi[1];
            ei++;
            while (ei < ecnt && e[ei].m_vi[0] == (unsigned int)vi0 && e[ei].m_vi[1] == (unsigned int)vi1 )
              ei++;
            etop_count++;
          }
          m_tope.SetCapacity(etop_count);

          // fill in the m_tope[] array information
          int* efindex = GetIntArray(ecnt);
          for ( ei = 0; ei < ecnt; /*empty*/ )
          {
            ON_MeshTopologyEdge& tope = m_tope.AppendNew();
            tope.m_topvi[0] = (int)(vi0 = e[ei].m_vi[0]);
            tope.m_topvi[1] = (int)(vi1 = e[ei].m_vi[1]);
            tope.m_topfi = efindex;
            tope.m_topf_count = 0;
            *efindex++ = (int)e[ei].m_fi;
            tope.m_topf_count++;
            ei++;
            while( ei < ecnt && e[ei].m_vi[0] == (unsigned int)vi0 && e[ei].m_vi[1] == (unsigned int)vi1 ) 
            {
              *efindex++ = (int)e[ei].m_fi;
              tope.m_topf_count++;
              ei++;
            }
          }
          efindex = 0; // memory deallocated by ~ON_MeshTopology()

          // connect vertices to edges;
          ecnt = m_tope.Count();
          int* ve_count = (int*)onmalloc(topv_count*sizeof(*ve_count));
          // set ve_count[topvi] = number of edges that begin or end at m_topv[topvi]
          memset( ve_count, 0, topv_count*sizeof(*ve_count));
          for ( ei = 0; ei < ecnt; ei++ ) {
            const ON_MeshTopologyEdge& tope = m_tope[ei];
            ve_count[tope.m_topvi[0]]++;
            ve_count[tope.m_topvi[1]]++;
          }
          // allocate and distribute storage for the mopv.m_topei[] array
          int* vei = GetIntArray(2*ecnt);
          for ( vi0 = 0; vi0 < topv_count; vi0++ ) {
            ON_MeshTopologyVertex& topv = m_topv[vi0];
            if ( ve_count[vi0] > 0 ) {
              topv.m_topei = vei;
              vei += ve_count[vi0];
            }
          }
          onfree(ve_count); ve_count = 0;
          vei = 0; // memory deallocated by ~ON_MeshTopology()

          // fill in the m_topv[].m_topei[] values
          for ( ei = 0; ei < ecnt; ei++ ) {
            ON_MeshTopologyEdge& tope = m_tope[ei];
            ON_MeshTopologyVertex& topv0 = m_topv[tope.m_topvi[0]];
            ON_MeshTopologyVertex& topv1 = m_topv[tope.m_topvi[1]];
            vei = const_cast<int*>(topv0.m_topei);
            vei[topv0.m_tope_count++] = ei;
            vei = const_cast<int*>(topv1.m_topei);
            vei[topv1.m_tope_count++] = ei;
          }

          // build face topology information
          m_topf.SetCapacity(fcount);
          m_topf.SetCount(fcount);
          memset( m_topf.Array(), 0, fcount*sizeof(ON_MeshTopologyFace) );
          for ( fi = 0; fi < fcount; fi++ ) {
            ON_MeshTopologyFace& f_local = m_topf[fi];
            f_local.m_topei[0] = -1;
            f_local.m_topei[1] = -1;
            f_local.m_topei[2] = -1;
            f_local.m_topei[3] = -1;
          }
          for ( ei = 0; ei < ecnt; ei++ ) {
            ON_MeshTopologyEdge& tope = m_tope[ei];
            for (efi = 0; efi < tope.m_topf_count; efi++ ) {
              // Because ON_MeshFace.vi[2] == ON_MeshFace.vi[3] for triangles,
              // we have topf.m_topei[j] BEGIN at ON_MeshFace.vi[(j+3)%4] and END at ON_MeshFace.vi[j]
              fi = tope.m_topfi[efi];
              f = m_mesh->m_F[fi];
              topfvi[0] = m_topv_map[f.vi[0]];
              topfvi[1] = m_topv_map[f.vi[1]];
              topfvi[2] = m_topv_map[f.vi[2]];
              topfvi[3] = m_topv_map[f.vi[3]];
              ON_MeshTopologyFace& topf = m_topf[fi];
              vi0 = tope.m_topvi[0];
              vi1 = tope.m_topvi[1];
              // unroll loop for speed
              if      ( vi0 == topfvi[3] && vi1 == topfvi[0] ) {
                topf.m_topei[0] = ei;
                topf.m_reve[0] = 0;
              }
              else if ( vi0 == topfvi[0] && vi1 == topfvi[1] ) {
                topf.m_topei[1] = ei;
                topf.m_reve[1] = 0;
              }
              else if ( vi0 == topfvi[1] && vi1 == topfvi[2] ) {
                topf.m_topei[2] = ei;
                topf.m_reve[2] = 0;
              }
              else if ( vi0 == topfvi[2] && vi1 == topfvi[3] ) {
                topf.m_topei[3] = ei;
                topf.m_reve[3] = 0;
              }
              else if ( vi1 == topfvi[3] && vi0 == topfvi[0] ) {
                topf.m_topei[0] = ei;
                topf.m_reve[0] = 1;
              }
              else if ( vi1 == topfvi[0] && vi0 == topfvi[1] ) {
                topf.m_topei[1] = ei;
                topf.m_reve[1] = 1;
              }
              else if ( vi1 == topfvi[1] && vi0 == topfvi[2] ) {
                topf.m_topei[2] = ei;
                topf.m_reve[2] = 1;
              }
              else if ( vi1 == topfvi[2] && vi0 == topfvi[3] ) {
                topf.m_topei[3] = ei;
                topf.m_reve[3] = 1;
              }
            }
          }
          for ( fi = 0; fi < fcount; fi++ ) 
          {
            ON_MeshTopologyFace& f_local = m_topf[fi];
            bool bIsGood = false;
            if (    f_local.m_topei[0] >= 0 && f_local.m_topei[1] >= 0 && f_local.m_topei[2] >=0 
                 && f_local.m_topei[0] != f_local.m_topei[1] 
                 && f_local.m_topei[1] != f_local.m_topei[2] 
                 && f_local.m_topei[2] != f_local.m_topei[0] 
                 ) {
              if ( m_mesh->m_F[fi].IsTriangle() ) {
                bIsGood = true;
                f_local.m_topei[3] = f_local.m_topei[2];
              }
              else if (   f_local.m_topei[3] >= 0 
                       && f_local.m_topei[0] != f_local.m_topei[3] 
                       && f_local.m_topei[1] != f_local.m_topei[3] 
                       && f_local.m_topei[2] != f_local.m_topei[3] ) {
                bIsGood = true;
              }
            }
            if ( !bIsGood ) {
              f_local.m_topei[0] = 0;
              f_local.m_topei[1] = 0;
              f_local.m_topei[2] = 0;
              f_local.m_topei[3] = 0;
              f_local.m_reve[0] = 0;
              f_local.m_reve[1] = 0;
              f_local.m_reve[2] = 0;
              f_local.m_reve[3] = 0;
            }
          }

        }
      }
    }

    b32IsValid = 1;
    break;
  }

  if ( -1 != b32IsValid0 )
  {
    // no sleep lock is in use
    m_b32IsValid = b32IsValid;
  }

  if ( 1 != b32IsValid )
  {
    Destroy();
  }

  return (1 == b32IsValid);
}

struct tagFPT
{
  int x, y, z;
};

//static int compare_fpt( const struct tagFPT* a, const struct tagFPT* b )
//{
//  if ( a->x < b->x )
//    return -1;
//  if ( a->x > b->x )
//    return 1;
//  if ( a->y < b->y )
//    return -1;
//  if ( a->y > b->y )
//    return 1;
//  if ( a->z < b->z )
//    return -1;
//  if ( a->z > b->z )
//    return 1;
//  return 0;
//}

static int compare_pmark( const int* a, const int* b )
{
  if ( *a < *b )
    return -1;
  if ( *a > *b )
    return 1;
  if ( a < b )
    return -1;
  if ( a > b )
    return 1;
  return 0;
}

static int compare_vmap( const void* a, const void* b )
{
  int i = *((int*)a);
  int j = *((int*)b);
  if ( i < j )
    return -1;
  if ( i > j )
    return 1;
  return 0;
}

static int DupVertex( ON_Mesh* mesh, int vi )
{
  int vertex_count = mesh->m_V.Count();
  ON_3fVector n;
  ON_3fPoint v;
  ON_Color c;
  ON_2fPoint t;
  ON_SurfaceCurvature k;
  v = mesh->m_V[vi];
  mesh->m_V.Append(v);
  if (mesh->m_N.Count() == vertex_count) {
    n = mesh->m_N[vi];
    mesh->m_N.Append(n);
  }
  if (mesh->m_T.Count() == vertex_count) {
    t = mesh->m_T[vi];
    mesh->m_T.Append(t);
  }
  if (mesh->m_K.Count() == vertex_count) {
    k = mesh->m_K[vi];
    mesh->m_K.Append(k);
  }
  if (mesh->m_C.Count() == vertex_count) {
    c = mesh->m_C[vi];
    mesh->m_C.Append(c);
  }
  return vertex_count;
}


static int AddToPartition( ON_Mesh* mesh, ON_SimpleArray<int>& pmark, int vi, int partition_mark, int fi0 )
{
  bool b = true;
  int i, fi, new_vi, face_count, *fvi;
  i = pmark[vi];
  if ( !i ) {
    pmark[vi] = partition_mark;
  }
  else if ( i != partition_mark && i != partition_mark-1 ) {
    if ( i == partition_mark-2 )
      pmark[vi] = partition_mark-1; // vertex vi shared between two partitions
    else {
      new_vi = DupVertex(mesh,vi);
      face_count = mesh->m_F.Count();
      for ( fi = fi0; fi < face_count; fi++ ) {
        fvi = mesh->m_F[fi].vi;
        if ( fvi[0] == vi )
          fvi[0] = new_vi;
        if ( fvi[1] == vi )
          fvi[1] = new_vi;
        if ( fvi[2] == vi )
          fvi[2] = new_vi;
        if ( fvi[3] == vi )
          fvi[3] = new_vi;
      }
      pmark.Append(partition_mark);
    }
  }
  else
    b = false; // vertex already in this partition
  return b;
}

bool ON_MeshPartition_IsValid( const ON_MeshPartition& p, const ON_Mesh& mesh )
{
  bool rc = false;
  const int* fvi;
  int j, tcnt, fi, parti, partcount;
  partcount = p.m_part.Count();
  rc = ( partcount > 0 );
  if ( p.m_partition_max_triangle_count < 1 )
    rc = false;
  if ( p.m_partition_max_vertex_count < 3 )
    rc = false;
  for ( parti = 0; parti < partcount && rc; parti++ ) {
    const ON_MeshPart& part = p.m_part[parti];
    if ( part.triangle_count < 1 )
      rc = false;
    if ( part.vertex_count < 1 )
      rc = false;
    if ( part.vertex_count != part.vi[1] - part.vi[0] )
      rc = false;
    tcnt = 0;
    for ( fi = part.fi[0]; fi < part.fi[1]; fi++ ) {
      fvi = mesh.m_F[fi].vi;
      tcnt++;
      if ( fvi[2] != fvi[3] )
        tcnt++;
      for ( j = 0; j < 4; j++ ) {
        if ( fvi[j] < part.vi[0] || fvi[j] >= part.vi[1] )
          rc = false;
      }
    }
    if ( tcnt != part.triangle_count )
      rc = false;
    if ( parti ) {
      if ( part.fi[0] != p.m_part[parti-1].fi[1] )
        rc = false;
      if ( part.vi[0] > p.m_part[parti-1].vi[1] )
        rc = false;
    }
  }
  if ( partcount ) {
    if ( p.m_part[0].fi[0] != 0 || p.m_part[partcount-1].fi[1] != mesh.m_F.Count() )
      rc = false;
  }
  return rc;
}

static
bool ON_Mesh_CreatePartition_SortFaces(const ON_Mesh& mesh, int* fmap )
{
  ON_RTree rt;
  if ( !rt.CreateMeshFaceTree(&mesh) )
    return false;

  const int mesh_F_count = mesh.m_F.Count();
  int fmap_count = 0;

  const ON_RTreeBranch* branch;
  ON_RTreeIterator rit(rt);
  for ( rit.First(); 0 != (branch = rit.Value()); rit.Next() )
  {
    if ( fmap_count > mesh_F_count )
      break;
    fmap[fmap_count++] = (int)(branch->m_id);
  }  

  if ( fmap_count != mesh_F_count )
  {
    ON_ERROR("ON_Mesh::CreatePartition unable to get fmap[]");
    return false;
  }

  return true;
}

const ON_MeshPartition* ON_Mesh::CreatePartition( 
              int partition_max_vertex_count, // maximum number of vertices in a partition
              int partition_max_triangle_count // maximum number of triangles in a partition
              )
{
  ON_Workspace ws;
  bool bNeedFaceSort = true;
  if ( m_partition ) 
  {
    bNeedFaceSort = false;
    if (   m_partition->m_partition_max_triangle_count > partition_max_triangle_count
        || m_partition->m_partition_max_vertex_count > partition_max_vertex_count )
        DestroyPartition();
  }
  if ( !m_partition ) 
  {
    // TODO: create one
    struct ON_MeshPart p;
    int vertex_count = VertexCount();
    const int face_count = FaceCount();
    const int triangle_count = TriangleCount() + 2*QuadCount();
    m_partition = new ON_MeshPartition();
    int k = triangle_count/partition_max_triangle_count;
    if ( k < vertex_count/partition_max_vertex_count )
      k = vertex_count/partition_max_vertex_count;
    k++;
    m_partition->m_part.Reserve(k);
    if ( vertex_count   <= partition_max_vertex_count && 
         triangle_count <= partition_max_triangle_count ) 
    {
      m_partition->m_partition_max_vertex_count = vertex_count;
      m_partition->m_partition_max_triangle_count = triangle_count;
      memset(&p,0,sizeof(p));
      p.vi[0] = 0;
      p.vi[1] = vertex_count;
      p.fi[0] = 0;
      p.fi[1] = face_count;
      p.vertex_count = vertex_count;
      p.triangle_count = triangle_count;
      m_partition->m_part.Append(p);
    }
    else 
    {
      int fi;
      int* fvi;
      DestroyTopology();

      // sort faces
      int* fmap = (int*)ws.GetMemory( face_count*sizeof(fmap[0]) );
      if ( !ON_Mesh_CreatePartition_SortFaces(*this,fmap) )
      {
        for ( fi = 0; fi < face_count; fi++ )
          fmap[fi] = fi;
      }

      //ON_SimpleArray<struct tagFPT> fpt(face_count);
      //fpt.SetCount(face_count);
      //if ( HasTextureCoordinates() )
      //{
      //  ON_2fPoint fcenter;
      //  ON_BoundingBox bbox = ON_PointListBoundingBox(2,0,m_T.Count(),2,&m_T[0].x);
      //  const ON_Interval txdom(bbox.m_min.x,bbox.m_max.x);
      //  const ON_Interval tydom(bbox.m_min.y,bbox.m_max.y);
      //  for ( fi = 0; fi < face_count; fi++ ) {
      //    fvi = m_F[fi].vi;
      //    if ( fvi[2] == fvi[3] ) {
      //      fcenter = 0.333333333333333333f*(m_T[fvi[0]] + m_T[fvi[1]] + m_T[fvi[2]]);
      //    }
      //    else {
      //      fcenter = 0.25f*(m_T[fvi[0]] + m_T[fvi[1]] + m_T[fvi[2]] + m_T[fvi[3]]);
      //    }
      //    fpt[fi].x = (int)floor(txdom.NormalizedParameterAt(fcenter.x)*100);
      //    fpt[fi].y = (int)floor(tydom.NormalizedParameterAt(fcenter.y)*100);
      //    fpt[fi].z = 0;
      //  }
      //}
      //else
      //{
      //  ON_3dPoint fcenter;
      //  ON_BoundingBox bbox = BoundingBox();
      //  const ON_Interval vxdom(bbox.m_min.x,bbox.m_max.x);
      //  const ON_Interval vydom(bbox.m_min.y,bbox.m_max.y);
      //  const ON_Interval vzdom(bbox.m_min.z,bbox.m_max.z);
      //  for ( fi = 0; fi < face_count; fi++ ) {
      //    fvi = m_F[fi].vi;
      //    if ( fvi[2] == fvi[3] ) {
      //      fcenter = 0.333333333333333333f*(m_V[fvi[0]] + m_V[fvi[1]] + m_V[fvi[2]]);
      //    }
      //    else {
      //      fcenter = 0.25f*(m_V[fvi[0]] + m_V[fvi[1]] + m_V[fvi[2]] + m_V[fvi[3]]);
      //    }
      //    fpt[fi].x = (int)floor(vxdom.NormalizedParameterAt(fcenter.x)*100);
      //    fpt[fi].y = (int)floor(vydom.NormalizedParameterAt(fcenter.y)*100);
      //    fpt[fi].z = (int)floor(vzdom.NormalizedParameterAt(fcenter.z)*100);
      //  }
      //}
      //fpt.Sort( ON::sort_algorithm::quick_sort, fmap, compare_fpt ); 
      m_F.Permute( fmap );
      if ( m_FN.Count() == face_count )
        m_FN.Permute( fmap );

      // sort vertices
      ON_SimpleArray<int>pmark(2*vertex_count);
      pmark.SetCount(vertex_count);
      pmark.Zero();
      int fi0, fi1, partition_mark, partition_vertex_count, partition_triangle_count;
      fi1 = 0;
      fi0 = 0;
      for ( partition_mark = 3, fi0 = 0; fi0 < face_count; fi0 = fi1, partition_mark += 2 ) 
      {
        partition_vertex_count = 0;
        partition_triangle_count = 0;
        for ( fi1 = fi0; 
              fi1 < face_count
              && partition_triangle_count+2 <= partition_max_triangle_count
              && partition_vertex_count+4 <= partition_max_vertex_count;
              fi1++ ) 
        {
          fvi = m_F[fi1].vi;
          partition_triangle_count++;
          if ( AddToPartition( this, pmark, fvi[0], partition_mark, fi0 ) )
            partition_vertex_count++;
          if ( AddToPartition( this, pmark, fvi[1], partition_mark, fi0 ) )
            partition_vertex_count++;
          if ( AddToPartition( this, pmark, fvi[2], partition_mark, fi0 ) )
            partition_vertex_count++;
          if ( fvi[2] != fvi[3] ) {
            partition_triangle_count++; // quads = 2 triangles
            if ( AddToPartition( this, pmark, fvi[3], partition_mark, fi0 ) )
              partition_vertex_count++;
          }
        }
        if ( fi0 < fi1 ) {
          struct ON_MeshPart p_local;
          memset(&p_local,0,sizeof(p_local));
          p_local.fi[0] = fi0;
          p_local.fi[1] = fi1;
          p_local.vertex_count = partition_vertex_count;
          p_local.triangle_count = partition_triangle_count;
          m_partition->m_part.Append(p_local);
        }
        if ( partition_triangle_count > m_partition->m_partition_max_triangle_count )
          m_partition->m_partition_max_triangle_count = partition_triangle_count;
        if ( partition_vertex_count > m_partition->m_partition_max_vertex_count )
          m_partition->m_partition_max_vertex_count = partition_vertex_count;
      }

      // the calls to AddToPartition() may have increased vertex count
      vertex_count = m_V.Count();

      // sort vertices
      int* vmap = (int*)ws.GetMemory( vertex_count*sizeof(vmap[0]) );
      pmark.Sort( ON::sort_algorithm::quick_sort, vmap, compare_pmark );
      m_V.Permute( vmap );
      if ( m_N.Count() == vertex_count )
        m_N.Permute( vmap );
      if ( m_T.Count() == vertex_count )
        m_T.Permute( vmap );
      if ( m_K.Count() == vertex_count )
        m_K.Permute( vmap );
      if ( m_C.Count() == vertex_count )
        m_C.Permute( vmap );
      pmark.Permute( vmap );
      // pamv[] = inverse of mapv permutation
      int* pamv = (int*)ws.GetMemory( vertex_count*sizeof(pamv[0]) );
      ON_Sort( ON::sort_algorithm::quick_sort, pamv, vmap, vertex_count, sizeof(vmap[0]), compare_vmap );
      for ( fi = 0; fi < face_count; fi++ ) {
        fvi = m_F[fi].vi;
        fvi[0] = pamv[fvi[0]];
        fvi[1] = pamv[fvi[1]];
        fvi[2] = pamv[fvi[2]];
        fvi[3] = pamv[fvi[3]];
      }

      // fill in m_part.vi[]
      int m, pi, partition_count = m_partition->m_part.Count();
      int vi0, vi1, vi2, vi3;
      for (vi2 = 0; vi2 < vertex_count && pmark[vi2]<2; vi2++)
      {/*empty for body*/}
      vi3=vi2;
      for ( pi = 0; pi < partition_count; pi++ ) {
        vi0 = vi2;
        vi1 = vi3;
        m = 2*pi + 4;
        for ( vi2 = vi3; vi2 < vertex_count && pmark[vi2] <  m; vi2++) 
        {/*empty for body*/}
        for ( vi3 = vi2; vi3 < vertex_count && pmark[vi3] <= m; vi3++) 
        {/*empty for body*/}
        m_partition->m_part[pi].vi[0] = vi0;
        m_partition->m_part[pi].vi[1] = vi3;
      }
    }
    // debugging - test partition
    if ( m_partition && !ON_MeshPartition_IsValid( *m_partition, *this ) ) {
      delete m_partition;
      m_partition = 0;
    }
  }

  return m_partition;
}

const ON_MeshPartition* ON_Mesh::Partition() const
{
  return m_partition;
}

void ON_Mesh::DestroyPartition()
{
  if ( m_partition ) {
    delete m_partition;
    m_partition = 0;
  }
}

ON_MeshPartition::ON_MeshPartition()
{
  m_partition_max_vertex_count = 0;
  m_partition_max_triangle_count = 0;
  m_part = 0;
}

ON_MeshPartition::~ON_MeshPartition()
{
  m_part.Destroy();
}


ON_Mesh* ON_Mesh::MeshPart( 
  const ON_MeshPart& mesh_part,
  ON_Mesh* mesh 
  ) const
{
  if ( this == mesh )
  {
    ON_ERROR("ON_Mesh::MeshPart this == mesh");
    return 0;
  }

  if ( mesh )
    mesh->Destroy();

  if (    mesh_part.fi[0] < 0 
       || mesh_part.fi[1] > m_F.Count()
       || mesh_part.fi[0] > mesh_part.fi[1]
       )
  {
    ON_ERROR("ON_Mesh::MeshPart mesh_part.fi[] is not valid");
    return 0;
  }

  if (    mesh_part.vi[0] < 0
       || mesh_part.vi[1] > m_V.Count()
       || mesh_part.vi[0] >= mesh_part.vi[1]
       )
  {
    ON_ERROR("ON_Mesh::MeshPart mesh_part.vi[] is not valid");
    return 0;
  }

  const int submesh_V_count = mesh_part.vi[1] - mesh_part.vi[0];
  const int submesh_F_count = mesh_part.fi[1] - mesh_part.fi[0];

  const bool bHasVertexNormals = HasVertexNormals();
  const bool bHasTextureCoordinates = HasTextureCoordinates();
  const bool bHasVertexColors = HasVertexColors();
  const bool bHasFaceNormals = HasFaceNormals();
  const bool bHasSurfaceParameters = HasSurfaceParameters();
  const bool bHasPrincipalCurvatures = HasPrincipalCurvatures();
  const bool bHasHiddenVertices = HiddenVertexCount() > 0;

  ON_Mesh* submesh = (0 != mesh)
                   ? mesh
                   : new ON_Mesh(mesh_part.triangle_count,
                                 mesh_part.vertex_count,
                                 bHasVertexNormals,
                                 bHasTextureCoordinates
                                 );

  if ( bHasVertexColors )
    submesh->m_C.Reserve(submesh_V_count);
  if ( bHasSurfaceParameters )
    submesh->m_S.Reserve(submesh_V_count);
  if ( bHasPrincipalCurvatures )
    submesh->m_K.Reserve(submesh_V_count);
  if ( bHasHiddenVertices )
    submesh->m_H.Reserve(submesh_V_count);
  if ( bHasFaceNormals )
    submesh->m_FN.Reserve(submesh_F_count);

  // put vertex information into submesh
  const int vi0 = mesh_part.vi[0];
  const int vi1 = mesh_part.vi[1];
  for ( int vi = vi0; vi < vi1; vi++ )
  {
    submesh->m_V.Append(m_V[vi]);
    if ( bHasVertexNormals )
      submesh->m_N.Append(m_N[vi]);
    if ( bHasTextureCoordinates )
      submesh->m_T.Append(m_T[vi]);
    if ( bHasVertexColors )
      submesh->m_C.Append(m_C[vi]);
    if ( bHasSurfaceParameters )
      submesh->m_S.Append(m_S[vi]);
    if ( bHasPrincipalCurvatures )
      submesh->m_K.Append(m_K[vi]);
    if ( bHasHiddenVertices )
    {
      bool bHidden = m_H[vi];
      submesh->m_H.Append(bHidden);
      if ( bHidden )
        submesh->m_hidden_count++;
    }
  }
  if ( submesh->m_hidden_count <= 0 )
  {
    submesh->m_H.Destroy();
    submesh->m_hidden_count = 0;
  }

  // put face information into submesh
  int bad_face_count = 0;
  const int fi0 = mesh_part.fi[0];
  const int fi1 = mesh_part.fi[1];
  for ( int fi = fi0; fi < fi1; fi++ )
  {
    ON_MeshFace f = m_F[fi];
    f.vi[0] -= vi0;
    f.vi[1] -= vi0;
    f.vi[2] -= vi0;
    f.vi[3] -= vi0;
    if (    f.vi[0] >= submesh_V_count || f.vi[0] < 0 
         || f.vi[1] >= submesh_V_count || f.vi[1] < 0 
         || f.vi[2] >= submesh_V_count || f.vi[2] < 0 
         || f.vi[3] >= submesh_V_count || f.vi[3] < 0 
         )
    {
      bad_face_count++;
      ON_ERROR("ON_Mesh::MeshPart Invalid face in partition");
      continue;
    }
    submesh->m_F.Append(f);
    if ( bHasFaceNormals )
      submesh->m_FN.Append(m_FN[fi]);
  }

  if ( submesh->m_F.Count() < 1 && bad_face_count > 0 )
  {
    if ( submesh != mesh )
      delete submesh;
    else
      mesh->Destroy();

    submesh = 0;
  }

  return submesh;
}

ON_Mesh* ON_Mesh::DuplicateFace( int face_index, ON_Mesh* mesh ) const
{
  if ( mesh == this )
    return nullptr;
  if ( 0 != mesh )
    mesh->Destroy();
  if ( face_index < 0 || face_index >= m_F.Count() )
    return nullptr;
  const unsigned int vcnt = VertexUnsignedCount();
  if ( vcnt < 3 )
    return nullptr;

  const ON_3dPoint* dV = ( vcnt == m_dV.UnsignedCount() ) ? m_dV.Array() : nullptr;
  const ON_3fPoint* fV = (nullptr == dV && vcnt == m_V.UnsignedCount() ) ? m_V.Array() : nullptr;
  bool bHasFaceNormals = HasFaceNormals();
  bool bHasVertexNormals = HasVertexNormals();
  bool bHasVertexColors = HasVertexColors();
  bool bHasTextureCoordinates = HasTextureCoordinates();
  bool bHasSurfaceParameters = HasSurfaceParameters();
  bool bHasPrincipalCurvatures = HasPrincipalCurvatures();

  ON_MeshFace f = m_F[face_index];
  if ( nullptr != dV )
  {
    if ( !f.IsValid(vcnt,dV) )
    {
      // invalid vertex indices - see if it can be fixed
      if ( !f.Repair(vcnt,dV) )
        return nullptr;
    }
  }
  else if (nullptr != fV)
  {
    if (!f.IsValid(vcnt, fV))
    {
      // invalid vertex indices - see if it can be fixed
      if (!f.Repair(vcnt, fV))
        return nullptr;
    }
  }
  else
    return nullptr;

  const int newvcnt = f.IsTriangle() ? 3 : 4;
  if ( 0 == mesh )
    mesh = new ON_Mesh();
  ON_3dPointArray* newdV = 0;
  if ( dV )
  {
    newdV = &mesh->m_dV;
    newdV->Reserve(newvcnt);
  }
  mesh->m_V.Reserve(newvcnt);
  mesh->m_F.Reserve(1);
  ON_MeshFace& newface = mesh->m_F.AppendNew();
  newface.vi[0] = 0;
  newface.vi[1] = 1;
  newface.vi[2] = 2;
  newface.vi[3] = (4 == newvcnt) ? 3 : newface.vi[2];

  if ( bHasFaceNormals )
  {
    mesh->m_FN.Reserve(1);
    mesh->m_FN.Append(m_FN[face_index]);
  }

  if ( bHasVertexNormals )
    mesh->m_N.Reserve(newvcnt);
  if ( bHasTextureCoordinates )
    mesh->m_T.Reserve(newvcnt);
  if ( bHasVertexColors )
    mesh->m_C.Reserve(newvcnt);
  if ( bHasSurfaceParameters )
    mesh->m_S.Reserve(newvcnt);
  if ( bHasPrincipalCurvatures )
    mesh->m_K.Reserve(newvcnt);
  for ( int vi = 0; vi < newvcnt; vi++ )
  {
    if ( dV )
      newdV->Append(dV[f.vi[vi]]);
    else
      mesh->m_V.Append(fV[f.vi[vi]]);
    if ( bHasVertexNormals )
      mesh->m_N.Append(m_N[f.vi[vi]]);
    if ( bHasTextureCoordinates )
      mesh->m_T.Append(m_T[f.vi[vi]]);
    if ( bHasVertexColors )
      mesh->m_C.Append(m_C[f.vi[vi]]);
    if ( bHasSurfaceParameters )
      mesh->m_S.Append(m_S[f.vi[vi]]);
    if ( bHasPrincipalCurvatures )
      mesh->m_K.Append(m_K[f.vi[vi]]);
  }
  if ( nullptr != dV )
    mesh->UpdateSinglePrecisionVertices();

  return mesh;
}


//ON_OBJECT_IMPLEMENT(ON_MeshVertexRef,ON_Geometry,"C547B4BD-BDCD-49b6-A983-0C4A7F02E31A");
//
//ON_OBJECT_IMPLEMENT(ON_MeshEdgeRef,ON_Geometry,"ED727872-463A-4424-851F-9EC02CB0F155");
//
//ON_OBJECT_IMPLEMENT(ON_MeshFaceRef,ON_Geometry,"4F529AA5-EF8D-4c25-BCBB-162D510AA280");

ON_OBJECT_IMPLEMENT(ON_MeshComponentRef,ON_Geometry,"1FD2F2BE-3346-4D7A-AE94-73C0B326D8F4");


const ON_MeshComponentRef ON_MeshComponentRef::Unset;


ON_MeshComponentRef::ON_MeshComponentRef()
  : m_mesh(0)
  , m_mesh_ci(ON_COMPONENT_INDEX::invalid_type,-1)
{
}

ON_MeshComponentRef::ON_MeshComponentRef(
  const class ON_Mesh* mesh,
  ON_COMPONENT_INDEX ci 
  )
  : m_mesh(mesh)
  , m_mesh_ci(ci)
{
}

ON_MeshComponentRef::~ON_MeshComponentRef()
{
  m_mesh = 0;
  m_mesh_ci.Set(ON_COMPONENT_INDEX::invalid_type,-1);
}

ON_MeshComponentRef& ON_MeshComponentRef::operator=(const ON_MeshComponentRef& src)
{
  if ( this != &src )
  {
    ON_Geometry::operator=(src);
    m_mesh = src.m_mesh;
    m_mesh_ci = src.m_mesh_ci;
  }
  return *this;
}

void ON_MeshComponentRef::Set(
  const class ON_Mesh* mesh,
  ON_COMPONENT_INDEX ci 
  )
{
  m_mesh = mesh;
  m_mesh_ci = ci;
}

int ON_MeshComponentRef::CompareMeshPointer(const ON_MeshComponentRef* lhs, const ON_MeshComponentRef* rhs)
{
  if (lhs == rhs)
    return 0;

  // nullptrs are last
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;

  const ON__UINT_PTR lhs_ptr = (ON__UINT_PTR)lhs->m_mesh;
  const ON__UINT_PTR rhs_ptr = (ON__UINT_PTR)rhs->m_mesh;
  if (lhs_ptr < rhs_ptr)
    return -1;
  if (lhs_ptr > rhs_ptr)
    return 1;

  return 0;
}


int ON_MeshComponentRef::Compare(const ON_MeshComponentRef* lhs, const ON_MeshComponentRef* rhs)
{
  if (lhs == rhs)
    return 0;

  // nullptrs are last
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;

  const ON__UINT_PTR lhs_ptr = (ON__UINT_PTR)lhs->m_mesh;
  const ON__UINT_PTR rhs_ptr = (ON__UINT_PTR)rhs->m_mesh;
  if (lhs_ptr < rhs_ptr)
    return -1;
  if (lhs_ptr > rhs_ptr)
    return 1;

  return ON_COMPONENT_INDEX::Compare(&lhs->m_mesh_ci, &rhs->m_mesh_ci);
}

int ON_MeshComponentRef::Compare2(const ON_MeshComponentRef*const* lhs, const ON_MeshComponentRef*const* rhs)
{
  if (lhs == rhs)
    return 0;

  // nullptrs are last
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;

  return ON_MeshComponentRef::Compare(*lhs, *rhs);
}

bool ON_MeshComponentRef::IsValid( ON_TextLog* text_log ) const
{
  if ( 0 == m_mesh)
  {
    if ( 0 != text_log )
    {
      text_log->Print("m_mesh = nullptr.\n");
    }
    return false;
  }

  if ( false == m_mesh_ci.IsMeshComponentIndex() )
  {
    if ( 0 != text_log )
    {
      text_log->Print("m_mesh_ci = ");
      m_mesh_ci.Dump(*text_log);
      text_log->Print(" has an invalid m_type.\n");
    }
    return false;
  }

  if ( false == m_mesh->IsValidMeshComponentIndex(m_mesh_ci) )
  {
    if ( 0 != text_log )
    {
      text_log->Print("m_mesh_ci = ");
      m_mesh_ci.Dump(*text_log);
      text_log->Print(" has an invalid m_index.\n");
    }
    return false;
  }

  return true;
}

void ON_MeshComponentRef::Dump( ON_TextLog& text_log ) const
{
  text_log.Print("m_mesh=%p, m_mesh_ci: ",m_mesh);
  m_mesh_ci.Dump(text_log);
  text_log.Print("\n");
}

unsigned int ON_MeshComponentRef::SizeOf() const
{
  unsigned int sz = sizeof(*this) - sizeof(ON_Geometry);
  sz += ON_Geometry::SizeOf();
  return sz;
}

ON::object_type ON_MeshComponentRef::ObjectType() const
{
  return ON::meshcomponent_reference;
}

// overrides of virtual ON_Geometry functions
int ON_MeshComponentRef::Dimension() const
{
  return 3;
}

bool ON_MeshComponentRef::GetBBox(
       double* boxmin,
       double* boxmax,
       bool bGrowBox
       ) const
{
  const unsigned int* vdex_list = 0;
  unsigned int vdex_count = 0;
  unsigned int vdex_buffer[2];

  if ( 0 == m_mesh )
    return false;

  switch(m_mesh_ci.m_type)
  {
  case ON_COMPONENT_INDEX::mesh_vertex:
    if (m_mesh_ci.m_index >= 0)
      vdex_buffer[vdex_count++] = (unsigned int)m_mesh_ci.m_index;
    break;

  case ON_COMPONENT_INDEX::meshtop_vertex:
    if ( m_mesh_ci.m_index >= 0 )
    {
      const ON_MeshTopology* top = MeshTopology();
      if ( 0 != top && m_mesh_ci.m_index < top->m_topv.Count())
      {
        const ON_MeshTopologyVertex& v = top->m_topv[m_mesh_ci.m_index];
        if ( v.m_v_count > 0 && 0 != v.m_vi && v.m_vi[0] >= 0 )
          vdex_buffer[vdex_count++] = (unsigned int)v.m_vi[0];
      }
    }
    break;

  case ON_COMPONENT_INDEX::meshtop_edge:
    if ( m_mesh_ci.m_index >= 0 )
    {
      const ON_MeshTopology* top = MeshTopology();
      if ( 0 != top && m_mesh_ci.m_index < top->m_tope.Count())
      {
        const ON_MeshTopologyEdge& e = top->m_tope[m_mesh_ci.m_index];
        for ( unsigned int j = 0; j < 2; j++ )
        {
          if ( e.m_topvi[j] >= 0 && e.m_topvi[j] < top->m_topv.Count() )
          {
            const ON_MeshTopologyVertex& v = top->m_topv[e.m_topvi[j]];
            if ( v.m_v_count > 0 && 0 != v.m_vi && v.m_vi[0] >= 0 )
            {
              vdex_buffer[vdex_count++] = (unsigned int)v.m_vi[0];
            }
          }
        }
      }
    }
    break;

  case ON_COMPONENT_INDEX::mesh_face:
    if (m_mesh_ci.m_index >= 0 && m_mesh_ci.m_index < m_mesh->m_F.Count())
    {
      vdex_list = (const unsigned int*)(m_mesh->m_F[m_mesh_ci.m_index].vi);
      vdex_count = (vdex_list[2] == vdex_list[3]) ? 3 : 4;
    }
    break;

  case ON_COMPONENT_INDEX::mesh_ngon:
    {
      const ON_MeshNgon* ngon = m_mesh->Ngon(m_mesh_ci.m_index);
      if ( ngon && ngon->m_Vcount > 0 && 0 != ngon->m_vi )
      {
        vdex_list = ngon->m_vi;
        vdex_count = ngon->m_Vcount;
      }
    }
    break;

  default:
    break;
  }

  if ( 0 == vdex_list )
  {
    if ( 0 == vdex_count )
      return 0;
    vdex_list = vdex_buffer;
  }

  bool rc = false;
  const ON_3dPointListRef vertex_list(m_mesh);
  const unsigned int vertex_count = vertex_list.PointCount();
  ON_3dPoint v[16];
  const unsigned int v_capacity = (unsigned int)(sizeof(v)/sizeof(v[0]));
  unsigned int v_count = 0;
  for ( unsigned int i = 0; i < vdex_count; i++ )
  {
    if ( vdex_list[i] < vertex_count )
    {
      vertex_list.GetPoint(vdex_list[i],&v[v_count].x);
      if ( v[v_count].IsValid() )
      {
        v_count++;
        if ( v_capacity == v_count )
        {
          if ( ON_GetPointListBoundingBox( 3, 0, v_count, 3, &v[0].x, boxmin, boxmax, bGrowBox?true:false ) )
          {
            bGrowBox = true;
            rc = true;
          }
          v_count = 0;
        }
      }
    }
  }

  if ( v_count > 0 )
  {
    if ( ON_GetPointListBoundingBox( 3, 0, v_count, 3, &v[0].x, boxmin, boxmax, bGrowBox?true:false ) )
      rc = true;
    v_count = 0;
  }

  return rc;
}

bool ON_MeshComponentRef::Transform( 
       const ON_Xform& xform
       )
{
  return false;
}

const ON_MeshTopology* ON_MeshComponentRef::MeshTopology() const
{
  const ON_MeshTopology* top = 0;

  if ( 0 != m_mesh )
  {
    if (m_mesh && m_mesh->HasMeshTopology()) 
    {
      top = &m_mesh->Topology();
    }
    else if ( m_mesh->m_V.UnsignedCount() >= 3 && m_mesh->m_F.UnsignedCount() > 0 )
    {
      if (    ON_COMPONENT_INDEX::meshtop_vertex == m_mesh_ci.m_type 
           || ON_COMPONENT_INDEX::meshtop_edge == m_mesh_ci.m_type 
         )
      {
        // create missing topology
        top = &m_mesh->Topology();
      }
    }
  }

  return top;
}

unsigned int ON_MeshComponentRef::VertexIndex() const
{
  unsigned int vi = ON_UNSET_UINT_INDEX;
  if ( 0 != m_mesh && m_mesh_ci.m_index >= 0 )
  {
    switch(m_mesh_ci.m_type)
    {
    case ON_COMPONENT_INDEX::meshtop_vertex:
      {
        const struct ON_MeshTopologyVertex* v = MeshTopologyVertex();
        if ( 0 != v && 1 == v->m_v_count && 0 != v->m_vi 
             && ((unsigned int)v->m_vi[0]) < m_mesh->m_V.UnsignedCount()
           )
        {
          vi = (unsigned int)v->m_vi[0];
        }
      }
      break;

    case ON_COMPONENT_INDEX::mesh_vertex:
      if ( ((unsigned int)m_mesh_ci.m_index) < m_mesh->m_V.UnsignedCount() )
        vi = (unsigned int)m_mesh_ci.m_index;
      break;
    
    default:
      break;
    }
  }
  return vi;
}

ON_3dPoint ON_MeshComponentRef::VertexPoint() const
{
  double buffer[3];
  ON_3dPointListRef(m_mesh).GetPoint(VertexIndex(),buffer);
  return *((const ON_3dPoint*)buffer);
}


unsigned int ON_MeshComponentRef::GetVertexPoint(class ON_3dPoint& point) const
{
  const unsigned int vi = VertexIndex();
  if ( ON_UNSET_UINT_INDEX != vi )
  {
    const ON_3dPointListRef vertex_list(m_mesh);
    vertex_list.GetPoint(vi,&point.x);
  }
  else
  {
    point = ON_3dPoint::UnsetPoint;
  }
  return vi;
}

const struct ON_MeshTopologyVertex* ON_MeshComponentRef::MeshTopologyVertex() const
{
  const struct ON_MeshTopologyVertex* topv;
  ON_3dPoint point;
  GetMeshTopologyVertexAndPoint(topv,point);
  return topv;
}

unsigned int ON_MeshComponentRef::MeshTopologyVertexIndex() const
{
  const struct ON_MeshTopologyVertex* topv;
  ON_3dPoint point;
  return GetMeshTopologyVertexAndPoint(topv,point);
}

unsigned int ON_MeshComponentRef::GetMeshTopologyVertexPoint(
  class ON_3dPoint& point
  ) const
{
  const struct ON_MeshTopologyVertex* topv;
  return GetMeshTopologyVertexAndPoint(topv,point);
}
  
unsigned int ON_MeshComponentRef::GetMeshTopologyVertex(
  const struct ON_MeshTopologyVertex*& topv
  ) const
{
  ON_3dPoint point;
  return GetMeshTopologyVertexAndPoint(topv,point);
}

unsigned int ON_MeshComponentRef::GetMeshTopologyVertexAndPoint(
  const struct ON_MeshTopologyVertex*& topv,
  class ON_3dPoint& point
  ) const
{
  if ( m_mesh && m_mesh_ci.m_index >= 0 )
  {
    const ON_MeshTopology* top = MeshTopology();
    if ( 0 != top )
    {
      const ON_3dPointListRef vertex_list(m_mesh);
      if ( top->m_topv_map.UnsignedCount() == vertex_list.PointCount() )
      {
        switch(m_mesh_ci.m_type)
        {
        case ON_COMPONENT_INDEX::mesh_vertex:
          if ( (unsigned int)m_mesh_ci.m_index < vertex_list.PointCount() )
          {
            int tvi = top->m_topv_map[m_mesh_ci.m_index];
            if ( tvi >= 0 && tvi < top->m_topv.Count() )
            {
              topv = &top->m_topv[tvi];
              vertex_list.GetPoint(m_mesh_ci.m_index,&point.x);
              return (unsigned int)tvi;
            }
          }
          break;

        case ON_COMPONENT_INDEX::meshtop_vertex:
          if ( (unsigned int)m_mesh_ci.m_index < top->m_topv.UnsignedCount() )
          {
            const ON_MeshTopologyVertex& v = top->m_topv[m_mesh_ci.m_index];
            topv = &v;
            if ( v.m_v_count > 0 && 0 != v.m_vi && v.m_vi[0] >= 0 && (unsigned int)v.m_vi[0] < vertex_list.PointCount() )
              vertex_list.GetPoint(v.m_vi[0],&point.x);
            else
              point = ON_3dPoint::UnsetPoint;
            return (unsigned int)m_mesh_ci.m_index;
          }
          break;
        
        default:
          break;
        }
      }
    }
  }

  topv = 0;
  point = ON_3dPoint::UnsetPoint;
  return ON_UNSET_UINT_INDEX;
}

unsigned int ON_MeshComponentRef::MeshTopologyEdgeIndex() const
{
  const struct ON_MeshTopologyEdge* tope;
  return GetMeshTopologyEdge(tope);
}


const struct ON_MeshTopologyEdge* ON_MeshComponentRef::MeshTopologyEdge() const
{
  const struct ON_MeshTopologyEdge* tope;
  GetMeshTopologyEdge(tope);
  return tope;
}

unsigned int ON_MeshComponentRef::GetMeshTopologyEdge(
  const struct ON_MeshTopologyEdge*& tope
  ) const
{
  if ( ON_COMPONENT_INDEX::meshtop_edge == m_mesh_ci.m_type && m_mesh_ci.m_index >= 0 )
  {
    const ON_MeshTopology* top = MeshTopology();
    if ( top && m_mesh_ci.m_index < top->m_tope.Count() )
    {
      tope = &top->m_tope[m_mesh_ci.m_index];
      return (unsigned int)m_mesh_ci.m_index;
    }
  }
  tope = 0;
  return ON_UNSET_UINT_INDEX;
}

unsigned int ON_MeshComponentRef::GetMeshTopologyEdgeLine(
  class ON_Line& line
  ) const
{
  const struct ON_MeshTopologyEdge* tope;
  return GetMeshTopologyEdgeAndLine(tope,line);
}

unsigned int ON_MeshComponentRef::GetMeshTopologyEdgeAndLine(
  const struct ON_MeshTopologyEdge*& tope,
  ON_Line& line 
  ) const
{
  tope = 0;
  unsigned int topei = GetMeshTopologyEdge(tope);
  if ( ON_UNSET_UINT_INDEX != topei && 0 != tope && tope->m_topvi[0] >= 0 && tope->m_topvi[1] >= 0 )
  {
    const ON_MeshTopology* top = MeshTopology();
    if ( 0 != top )
    {
      int topv_count = top->m_topv.Count();
      if ( tope->m_topvi[0] < topv_count && tope->m_topvi[1] < topv_count )
      {
        const ON_MeshTopologyVertex& v0 = top->m_topv[tope->m_topvi[0]];
        const ON_MeshTopologyVertex& v1 = top->m_topv[tope->m_topvi[1]];
        if ( v0.m_v_count > 0 && v1.m_v_count > 0 && 0 != v0.m_vi && 0 != v1.m_vi )
        {
          if ( v0.m_vi[0] >= 0 && v1.m_vi[0] >= 0 && v0.m_vi[0] < m_mesh->m_V.Count() && v1.m_vi[0] < m_mesh->m_V.Count() )
          {
            ON_3dPointListRef vlist(m_mesh);
            vlist.GetPoint(v0.m_vi[0],&line.from.x);
            vlist.GetPoint(v1.m_vi[0],&line.to.x);
            return topei;
          }
        }
      }
    }
  }

  line = ON_Line::UnsetLine;
  return topei;
}

unsigned int ON_MeshComponentRef::MeshFaceIndex() const
{
  const ON_MeshFace* mesh_face;
  return GetMeshFace(mesh_face);
}

const class ON_MeshFace* ON_MeshComponentRef::MeshFace() const
{
  const ON_MeshFace* mesh_face = 0;
  GetMeshFace(mesh_face);
  return mesh_face;
}

unsigned int ON_MeshComponentRef::GetMeshFace(
  const ON_MeshFace*& mesh_face
  ) const
{
  if ( 0 != m_mesh && m_mesh_ci.m_index >= 0 )
  {
    switch(m_mesh_ci.m_type)
    {     
    case ON_COMPONENT_INDEX::mesh_face:
      if ( m_mesh_ci.m_index < m_mesh->m_F.Count() )
      {
        mesh_face = &m_mesh->m_F[m_mesh_ci.m_index];
        return (unsigned int)m_mesh_ci.m_index;
      }
      break;

    case ON_COMPONENT_INDEX::mesh_ngon:
      {
        const ON_MeshNgon* ngon = m_mesh->Ngon(m_mesh_ci.m_index);
        if ( 0 != ngon && 1 == ngon->m_Fcount && 0 != ngon->m_fi )
        {
          if ( ngon->m_fi[0] < m_mesh->m_F.UnsignedCount() )
          {
            mesh_face = &m_mesh->m_F[ngon->m_fi[0]];
            return ngon->m_fi[0];
          }
        }
      }
      break;
    
    default:
      break;
    }
  }

  mesh_face = 0;
  return ON_UNSET_UINT_INDEX;
}

unsigned int ON_MeshComponentRef::MeshNgonIndex() const
{
  unsigned int ngon_index = ON_UNSET_UINT_INDEX;
  if ( 0 != m_mesh && m_mesh_ci.m_index >= 0 )
  {
    switch( m_mesh_ci.m_type)
    {
    case ON_COMPONENT_INDEX::mesh_face:
      if ( m_mesh_ci.m_index < m_mesh->m_F.Count() )
      {
        ngon_index = m_mesh->NgonIndexFromFaceIndex(m_mesh_ci.m_index);
        if ( ngon_index < ON_UNSET_UINT_INDEX && 0 == m_mesh->Ngon(ngon_index) )
          ngon_index = ON_UNSET_UINT_INDEX;
      }
      break;
    case ON_COMPONENT_INDEX::mesh_ngon:
      if ( 0 != m_mesh->Ngon(m_mesh_ci.m_index) )
        ngon_index = (unsigned int)m_mesh_ci.m_index;
      break;
    
    default:
      break;
    }
  }
  return ngon_index;
}

const class ON_MeshNgon* ON_MeshComponentRef::MeshNgon(
    class ON_MeshNgonBuffer& ngon_buffer
    ) const
{
  const class ON_MeshNgon* ngon = 0;
  if ( 0 != m_mesh && m_mesh_ci.m_index >= 0 )
  {
    if ( ON_COMPONENT_INDEX::mesh_ngon == m_mesh_ci.m_type )
    {
      ngon = m_mesh->Ngon(m_mesh_ci.m_index);
    }
    else if ( ON_COMPONENT_INDEX::mesh_face == m_mesh_ci.m_type && m_mesh_ci.m_index < m_mesh->m_F.Count() )
    {
      ngon = ON_MeshNgon::NgonFromMeshFace(ngon_buffer,(unsigned int)m_mesh_ci.m_index,(const unsigned int*)m_mesh->m_F[m_mesh_ci.m_index].vi);
    }
  }
  return ngon;
}

const class ON_MeshNgon* ON_MeshComponentRef::MeshNgon() const
{
  unsigned int ngon_index = MeshNgonIndex();
  return ( ON_UNSET_UINT_INDEX != ngon_index ) ? m_mesh->Ngon(ngon_index) : 0;
}

ON_MeshComponentRef ON_Mesh::MeshComponentRef(
  ON_COMPONENT_INDEX ci
  ) const
{
  ON_MeshComponentRef cr;
  if ( ci.IsMeshComponentIndex() && ci.m_index >= 0 )
  {
    cr.Set( this, ci );
  }
  return cr;
}

const ON_COMPONENT_INDEX ON_MeshTopology::TopVertexComponentIndex(
  ON_COMPONENT_INDEX ci
) const
{
  switch (ci.m_type)
  {
  case ON_COMPONENT_INDEX::TYPE::mesh_vertex:
    if (ci.m_index >= 0
      && nullptr != m_mesh 
      && ci.m_index < m_mesh->VertexCount() 
      && m_mesh->VertexCount() == m_topv_map.Count() 
      )
    {
      ci.m_type = ON_COMPONENT_INDEX::TYPE::meshtop_vertex;
      ci.m_index = m_topv_map[ci.m_index];
    }
    // no break here
  case ON_COMPONENT_INDEX::TYPE::meshtop_vertex:
    if (ci.m_index >= 0 && ci.m_index < m_topv.Count())
    {
      return ci;
    }
    break;
          
  default:
    break;
  }

  return ON_COMPONENT_INDEX::UnsetComponentIndex;
}


ON_MeshComponentRef ON_MeshTopology::MeshComponentRef(ON_COMPONENT_INDEX ci) const
{
  ON_MeshComponentRef cr;
  if ( 0 != m_mesh )
    cr = m_mesh->MeshComponentRef(ci);
  return cr;
}

const ON_Mesh* ON_MeshComponentRef::Mesh() const
{
  return m_mesh;
}

ON_COMPONENT_INDEX ON_MeshComponentRef::ComponentIndex() const
{
  ON_COMPONENT_INDEX ci;
  if ( m_mesh && m_mesh->IsValidMeshComponentIndex(m_mesh_ci) )
    ci = m_mesh_ci;
  return ci;
}

bool ON_Mesh::IsValidMeshComponentIndex(
  ON_COMPONENT_INDEX ci
  ) const
{
  bool rc = ci.m_index >= 0;
  if (rc)
  {
    switch(ci.m_type)
    {
    case ON_COMPONENT_INDEX::mesh_vertex:
      if (ci.m_index >= m_V.Count())
        rc = false;
      break;

    case ON_COMPONENT_INDEX::meshtop_vertex:
      if ( false == TopologyExists() || ci.m_index >= m_top.m_topv.Count() )
        rc = false;
      break;

    case ON_COMPONENT_INDEX::meshtop_edge:
      if ( false == TopologyExists() || ci.m_index >= m_top.m_tope.Count() )
        rc = false;
      break;

    case ON_COMPONENT_INDEX::mesh_face:
      if (ci.m_index >= m_F.Count())
        rc = false;
      break;

    case ON_COMPONENT_INDEX::mesh_ngon:
      if ( 0 == Ngon(ci.m_index) )
        rc = false;
      break;

    default:
      rc = false;
      break;
    }
  }
  return rc;
}


ON_MeshComponentRef* ON_Mesh::MeshComponent( 
  ON_COMPONENT_INDEX ci
  ) const
{
  ON_MeshComponentRef* cr_ptr = 0;
  ON_MeshComponentRef cr = MeshComponentRef(ci);
  if ( this == cr.Mesh() && cr.ComponentIndex() == ci )
    cr_ptr = new ON_MeshComponentRef(cr);
  return cr_ptr;
}


ON_3dVector ON_TriangleNormal(
        const ON_3dPoint& A,
        const ON_3dPoint& B,
        const ON_3dPoint& C
        )
{
  // N = normal to triangle's plane
  ON_3dVector N;
  double a, b, c, d;
  N.x = A.y*(B.z-C.z) + B.y*(C.z-A.z) + C.y*(A.z-B.z);
  N.y = A.z*(B.x-C.x) + B.z*(C.x-A.x) + C.z*(A.x-B.x);
  N.z = A.x*(B.y-C.y) + B.x*(C.y-A.y) + C.x*(A.y-B.y);

  a = fabs(N.x);
  b = fabs(N.y);
  c = fabs(N.z);
  if ( b > a )
  {
    if ( c > b )
    {
      // c is largest
      if ( c > ON_DBL_MIN )
      {
        a /= c; b /= c; d = c*sqrt(1.0 + a*a + b*b);
      }
      else
      {
        d = c;
      }
    }
    else
    {
      if ( b > ON_DBL_MIN )
      {
        // b is largest
        a /= b; c /= b; d = b*sqrt(1.0 + c*c + a*a);
      }
      else
      {
        d = b;
      }
    }
  }
  else if ( c > a )
  {
    // c is largest
    if ( c > ON_DBL_MIN )
    {
      a /= c; b /= c; d = c*sqrt(1.0 + a*a + b*b);
    }
    else
    {
      d = c;
    }
  }
  else if ( a > ON_DBL_MIN )
  {
    // a is largest
    b /= a; c /= a; d = a*sqrt(1.0 + b*b + c*c);
  }
  else
  {
    d = a;
  }

  if ( d > 0.0 )
  {
    N.x /= d; N.y /= d; N.z /= d;
  }

  return N;
}

bool ON_GetTrianglePlaneEquation(
        const ON_3dPoint& A,
        const ON_3dPoint& B,
        const ON_3dPoint& C,
        double* a,
        double* b,
        double* c,
        double* d,
        double* evaluation_tol
        )
{
  const ON_3dVector N(ON_TriangleNormal(A,B,C));
  const double dd( -(N.x*A.x + N.y*A.y + N.z*A.z) );
  
  *a = N.x;
  *b = N.y;
  *c = N.z;
  *d = dd;
  
  if ( 0 != evaluation_tol )
  {
    *evaluation_tol = fabs(N.x*A.x + N.y*A.y + N.z*A.z + dd);
    double e = fabs(N.x*B.x + N.y*B.y + N.z*B.z + dd);
    if ( e > *evaluation_tol )
      *evaluation_tol = e;
    e = fabs(N.x*C.x + N.y*C.y + N.z*C.z + dd);
    if ( e > *evaluation_tol )
      *evaluation_tol = e;
    *evaluation_tol *= (1.0 + ON_EPSILON);
  }

  return (0.0 != N.x || 0.0 != N.y || 0.0 != N.z);
}


const bool* ON_Mesh::HiddenVertexArray() const
{
  return ( ( m_hidden_count > 0 && m_H.Count() == m_V.Count() ) ? m_H.Array() : 0);
}

void ON_Mesh::DestroyHiddenVertexArray()
{
  m_H.Destroy();
  m_hidden_count = 0;
}

int ON_Mesh::HiddenVertexCount() const
{
  return ((m_H.Count() == m_V.Count()) ? m_hidden_count : 0);
}

void ON_Mesh::SetVertexHiddenFlag( int meshvi, bool bHidden )
{
  const int vcount = m_V.Count();
  if ( meshvi >= 0 && meshvi < vcount )
  {
    if ( bHidden )
    {
      if ( vcount != m_H.Count() )
      {
        m_H.SetCapacity(vcount);
        m_H.SetCount(vcount);
        m_H.Zero();
        m_H[meshvi] = true;
        m_hidden_count = 1;
      }
      else if ( false == m_H[meshvi] )
      {
        m_H[meshvi] = true;
        m_hidden_count++;
      }
    }
    else
    {
      // show this vertex
      if ( m_hidden_count > 0 && vcount == m_H.Count() )
      {
        if  ( m_H[meshvi] )
        {
          m_H[meshvi] = false;
          m_hidden_count--;
          if ( 0 == m_hidden_count )
          {
            DestroyHiddenVertexArray();
          }
        }
      }
      else if ( m_hidden_count > 0 || m_H.Capacity() > 0 )
      {
        // if m_H exists, it is bogus.
        DestroyHiddenVertexArray();
      }
    }
  }
}


bool ON_Mesh::VertexIsHidden(int meshvi) const
{
  const int vcount = m_V.Count();
  return ((m_hidden_count > 0 && meshvi >= 0 && meshvi < vcount && vcount == m_H.Count()) 
          ? m_H[meshvi]
          : false);
}

bool ON_Mesh::FaceIsHidden(int meshfi) const
{
  const bool* bHiddenVertex = HiddenVertexArray();
  if ( bHiddenVertex && meshfi >= 0 && meshfi < m_F.Count() )
  {
    ON_MeshFace f = m_F[meshfi];
    if ( bHiddenVertex[f.vi[0]] || bHiddenVertex[f.vi[1]] || bHiddenVertex[f.vi[2]] || bHiddenVertex[f.vi[3]] )
      return true;
  }
  return false;
}

bool ON_MeshTopology::TopVertexIsHidden( int topvi ) const
{
  const bool* bHiddenVertex = m_mesh ? m_mesh->HiddenVertexArray() : 0;
  if ( bHiddenVertex && topvi >= 0 && topvi < m_topv.Count() )
  {
    const ON_MeshTopologyVertex& topv = m_topv[topvi];
    int i;
    for ( i = 0; i < topv.m_v_count; i++ )
    {
      if ( !bHiddenVertex[topv.m_vi[i]] )
        return false;
    }
    return true;
  }
  return false;
}

bool ON_MeshTopology::TopEdgeIsHidden( int topei ) const
{
  // ugly - but faster than calling TopVertexIsHidden()
  const bool* bHiddenVertex = m_mesh ? m_mesh->HiddenVertexArray() : 0;
  if ( bHiddenVertex && topei >= 0 && topei < m_tope.Count()  )
  {
    const ON_MeshTopologyEdge& tope = m_tope[topei];
    const ON_MeshTopologyVertex& topv0 = m_topv[tope.m_topvi[0]];
    const ON_MeshTopologyVertex& topv1 = m_topv[tope.m_topvi[1]];
    int i;

    for ( i = 0; i < topv0.m_v_count; i++ )
    {
      if ( !bHiddenVertex[topv0.m_vi[i]] )
        break;
    }
    if ( i >= topv0.m_v_count )
      return true;

    for ( i = 0; i < topv1.m_v_count; i++ )
    {
      if ( !bHiddenVertex[topv1.m_vi[i]] )
        return false;
    }

    return true;
  }
  return false;
}

bool ON_MeshTopology::TopFaceIsHidden( int topfi ) const
{
  // topology and mesh face indices are the same
  return m_mesh ? m_mesh->FaceIsHidden(topfi) : false;
}

ON_MappingTag::ON_MappingTag()
{
  Default();
}

const ON_Xform ON_MappingTag::Transform() const
{
  return TransformIsIdentity() ? ON_Xform::IdentityTransformation : m_mesh_xform;
}

ON_SurfaceCurvatureColorMapping::ON_SurfaceCurvatureColorMapping(
  ON::curvature_style kappa_style,
  ON_Interval kappa_range
)
  : m_is_set(2)
  , m_kappa_style(ON::CurvatureStyle((int)(kappa_style)))
  , m_kappa_range(kappa_range.IsValid() ? kappa_range : ON_Interval::Nan)
{}

ON_SurfaceCurvatureColorMapping::ON_SurfaceCurvatureColorMapping(
  ON::curvature_style kappa_style,
  ON_Interval kappa_range,
  ON_Interval hue_range_in_radians
)
  : m_is_set(2)
  , m_kappa_style(ON::CurvatureStyle((int)(kappa_style)))
  , m_kappa_range(kappa_range.IsValid() ? kappa_range : ON_Interval::Nan)
  , m_hue_range_in_radians(hue_range_in_radians.IsValid() ? hue_range_in_radians : ON_Interval::Nan)
{}

const ON_SHA1_Hash ON_SurfaceCurvatureColorMapping::Hash() const
{
  if (this->IsSet())
  {
    ON_SHA1 sha1;

    // The uuid is accumulated because an int,double,double could easily
    // be the intput data int many unrelated contexts. This sha1 is used
    // to avoid expensive recalculations of curvatures and their false colors.
    const ON_UUID uniqueness_boost = ON_SurfaceCurvatureColorMapping::Id;
    sha1.AccumulateId(uniqueness_boost);

    const unsigned u = (unsigned)this->m_kappa_style;
    sha1.AccumulateInteger32(u);

    sha1.AccumulateDoubleArray(2, this->m_kappa_range.m_t);

    sha1.AccumulateDoubleArray(2, this->m_hue_range_in_radians.m_t);

    return sha1.Hash();
  }
  return ON_SHA1_Hash::EmptyContentHash;
}

ON__UINT32 ON_SurfaceCurvatureColorMapping::CRC32() const
{
  return this->IsSet() ? this->Hash().CRC32(0) : 0;
}

const ON_MappingTag ON_SurfaceCurvatureColorMapping::ColorMappingTag() const
{
  ON_MappingTag mt = ON_MappingTag::Unset;
  if (this->IsSet())
  {

    mt.m_mapping_id = ON_SurfaceCurvatureColorMapping::Id;
    mt.m_mapping_type = ON_TextureMapping::TYPE::false_colors;

    // DO NOT INCLUDE anything in the crc that does not directly control vertex colors.
    // This value is used to determine when the parameters used to calculate the vertex
    // colors have changed.
    mt.m_mapping_crc = this->CRC32();

    // The m_mesh_xform in meaningless for false color curvature analysis,
    // but setting it to the identity greases the wheels when downstream
    // code looks at it for unknown reasons.
    mt.m_mesh_xform = ON_Xform::IdentityTransformation;
  }

  return mt;
}

ON::curvature_style ON_SurfaceCurvatureColorMapping::KappaStyle() const
{
  return m_kappa_style;
}

const ON_Interval ON_SurfaceCurvatureColorMapping::KappaRange() const
{
  return m_kappa_range;
}

const ON_Interval ON_SurfaceCurvatureColorMapping::HueRangeInRadians() const
{
  return m_hue_range_in_radians;
}

ON_SurfaceDraftAngleColorMapping::ON_SurfaceDraftAngleColorMapping(
  ON_3dVector up,
  ON_Interval angle_range_in_radians
)
  : m_is_set(2)
  , m_up(up.IsValid() ? up : ON_3dVector::NanVector)
  , m_angle_range_in_radians(angle_range_in_radians.IsValid() ? angle_range_in_radians : ON_Interval::Nan)
  , m_hue_range_in_radians(ON_SurfaceDraftAngleColorMapping::DefaultHueRangeRadians)
{}

ON_SurfaceDraftAngleColorMapping::ON_SurfaceDraftAngleColorMapping(
  ON_3dVector up,
  ON_Interval angle_range_in_radians,
  ON_Interval hue_range_in_radians
)
  : m_is_set(2)
  , m_up(up.IsValid() ? up : ON_3dVector::NanVector)
  , m_angle_range_in_radians(angle_range_in_radians.IsValid() ? angle_range_in_radians : ON_Interval::Nan)
  , m_hue_range_in_radians(hue_range_in_radians.IsValid() ? hue_range_in_radians : ON_Interval::Nan)
{}

const ON_3dVector ON_SurfaceDraftAngleColorMapping::Up() const
{
  return this->m_up;
}

const ON_Interval ON_SurfaceDraftAngleColorMapping::AngleRangeInRadians() const
{
  return this->m_angle_range_in_radians;
}

const ON_Interval ON_SurfaceDraftAngleColorMapping::HueRangeInRadians() const
{
  return this->m_hue_range_in_radians;
}


const ON_SHA1_Hash ON_SurfaceDraftAngleColorMapping::Hash() const
{
  if (this->IsSet())
  {
    ON_SHA1 sha1;    // The uuid is accumulated because an int,double,double could easily
    // be the intput data int many unrelated contexts. This sha1 is used
    // to avoid expensive recalculations of curvatures and their false colors.
    const ON_UUID uniqueness_boost = ON_SurfaceDraftAngleColorMapping::Id;
    sha1.AccumulateId(uniqueness_boost);
    sha1.AccumulateDoubleArray(3, &this->m_up.x);
    sha1.AccumulateDoubleArray(2, this->m_angle_range_in_radians.m_t);
    sha1.AccumulateDoubleArray(2, this->m_hue_range_in_radians.m_t);
    return sha1.Hash();
  }
  return ON_SHA1_Hash::EmptyContentHash;
}

ON__UINT32 ON_SurfaceDraftAngleColorMapping::CRC32() const
{
  return this->IsSet() ? this->Hash().CRC32(0) : 0;
}


const ON_MappingTag ON_SurfaceDraftAngleColorMapping::ColorMappingTag() const
{
  ON_MappingTag mt = ON_MappingTag::Unset;

  if (this->IsSet())
  {
    mt.m_mapping_id = ON_SurfaceDraftAngleColorMapping::Id;
    mt.m_mapping_type = ON_TextureMapping::TYPE::false_colors;

    // DO NOT INCLUDE anything in the crc that does not directly control vertex colors.
    // This value is used to determine when the parameters used to calculate the vertex
    // colors have changed.
    mt.m_mapping_crc = this->CRC32();

    // The m_mesh_xform in meaningless for false color curvature analysis,
    // but setting it to the identity greases the wheels when downstream
    // code looks at it for unknown reasons.
    mt.m_mesh_xform = ON_Xform::IdentityTransformation;
  }

  return mt;
}

bool ON_SurfaceDraftAngleColorMapping::IsSet() const
{
  if (1 == this->m_is_set)
    return true;
  if (0 == this->m_is_set)
    return false;
  for (;;)
  {
    if (false == this->m_up.IsValid())
      break;
    if (false == this->m_angle_range_in_radians.IsValid())
      break;
    if (false == this->m_hue_range_in_radians.IsValid())
      break;
    this->m_is_set = 1;
    return true;
  }
  this->m_is_set = 0;
  return false;
}

bool ON_SurfaceDraftAngleColorMapping::IsUnset() const
{
  return this->IsSet() ? false : true;
}

bool operator==(const ON_SurfaceDraftAngleColorMapping& lhs, const ON_SurfaceDraftAngleColorMapping& rhs)
{
  // if any double is a nan, this compare must be false.
  if (lhs.IsSet() == rhs.IsSet())
  {
    const ON_3dVector up[2] = { lhs.Up(), rhs.Up() };
    if (up[0] == up[1])
    {
      const ON_Interval ar[2] = { lhs.AngleRangeInRadians() ,rhs.AngleRangeInRadians() };
      if (ar[0].m_t[0] == ar[1].m_t[0] && ar[0].m_t[1] == ar[1].m_t[1])
      {
        const ON_Interval hr[2] = { lhs.HueRangeInRadians() ,rhs.HueRangeInRadians() };
        if (hr[0].m_t[0] == hr[1].m_t[0] && hr[0].m_t[1] == hr[1].m_t[1])
          return true;
      }
    }
  }
  return false;
}

bool operator!=(const ON_SurfaceDraftAngleColorMapping& lhs, const ON_SurfaceDraftAngleColorMapping& rhs)
{
  // if any double is a nan, this compare must be false.
  const ON_3dVector up[2] = { lhs.Up(), rhs.Up() };
  if (up[0] != up[1])
  {
    const ON_Interval ar[2] = { lhs.AngleRangeInRadians() ,rhs.AngleRangeInRadians() };
    if (ar[0].m_t[0] != ar[1].m_t[0] || ar[0].m_t[1] != ar[1].m_t[1])
    {
      const ON_Interval hr[2] = { lhs.HueRangeInRadians() ,rhs.HueRangeInRadians() };
      if (hr[0].m_t[0] != hr[1].m_t[0] || hr[0].m_t[1] != hr[1].m_t[1])
      {
        // any compare involving nans is false
        if (ON_IS_NAN(ar[0].m_t[0]) || ON_IS_NAN(ar[0].m_t[1]) || ON_IS_NAN(ar[1].m_t[0]) || ON_IS_NAN(ar[1].m_t[1]))
          return false;
        if (ON_IS_NAN(hr[0].m_t[0]) || ON_IS_NAN(hr[0].m_t[1]) || ON_IS_NAN(hr[1].m_t[0]) || ON_IS_NAN(hr[1].m_t[1]))
          return false;

        return true;
      }
    }
  }
  return false;
}


const ON_Color ON_SurfaceDraftAngleColorMapping::Color(
  ON_3dVector surface_normal
) const
{
  for (;;)
  {
    if (false == IsSet())
      break;

    const double a0 = ON_HALFPI - this->m_angle_range_in_radians[0];
    const double a1 = ON_HALFPI - this->m_angle_range_in_radians[1];
    const double mn = cos(a0);
    const double mx = cos(a1);

    const double n_dot_up = surface_normal * this->m_up;
    double h;

    if (fabs(mn - mx) <= 1e-8)
    {
      if (n_dot_up < mn && n_dot_up < mx)
        h = this->m_hue_range_in_radians[0];
      else if (n_dot_up > mn && n_dot_up > mx)
        h = this->m_hue_range_in_radians[1];
      else
        h = this->m_hue_range_in_radians.ParameterAt(0.5);
    }
    else if (mn != mx)
    {
      double t = (n_dot_up - mn) / (mx - mn);
      if (t <= 0.0)
        h = this->m_hue_range_in_radians[0];
      else if (t >= 1.0)
        h = this->m_hue_range_in_radians[1];
      else
        h = this->m_hue_range_in_radians.ParameterAt(t);
    }
    else
      break;

    return ON_Color::FromHueInRadians(h);
  }
  return ON_Color::UnsetColor;
}


bool ON_MappingTag::TransformIsIdentity() const
{
  return ON_MappingTag::TransformTreatedIsIdentity(&m_mesh_xform);
}

bool ON_MappingTag::TransformTreatedIsIdentity(const ON_Xform* xform)
{
  if (nullptr == xform)
    return true; // a missing xform is treated as the idenity.
  if (xform->IsIdentity(ON_ZERO_TOLERANCE))
    return true;
  if (xform->IsZero())
    return true; // zero is not a valid mapping object xform
  if (!xform->IsValid())
    return true; // an invalid object xform is treated as the identity
  return false; // a valid non zero, non identity xform is actually used.
}

ON_MappingTag::ON_MappingTag(const ON_TextureMapping & mapping, const ON_Xform * xform)
{
  Default();
  Set(mapping);
  if ( false == ON_MappingTag::TransformTreatedIsIdentity(xform))
    m_mesh_xform = *xform;
}

void ON_MappingTag::Dump( ON_TextLog& text_log ) const
{
  if (text_log.IsTextHash())
  {
    // The code is a mess with respect to mapping tags and they are
    // often mutable or changed with const/cast in unpredictable ways.
    text_log.Print("Texture/color mapping tag:\n");
    text_log.Print("  ...\n");
    return;
  }

  const ON_TextLog::LevelOfDetail lod = text_log.GetLevelOfDetail();

  if (lod >= ON_TextLog::LevelOfDetail::Maximum)
  {
    text_log.Print("Texture/color mapping tag:\n");
    text_log.PushIndent();
  }

  if (ON_MappingTag::Unset == *this)
  {
    text_log.Print("ON_MappingTag::Unset\n");
  }
  else if (ON_MappingTag::SurfaceParameterMapping == *this)
  {
    text_log.Print("ON_MappingTag::SurfaceParameterMapping\n");
  }
  else
  {
    text_log.Print("mapping type = ");
    switch (m_mapping_type)
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
    case  ON_TextureMapping::TYPE::wcs_projection:
      text_log.Print("wcs projection");
      break;
    case  ON_TextureMapping::TYPE::wcsbox_projection:
      text_log.Print("wcs box projection");
      break;
    }
    text_log.Print("\n");

    text_log.Print("mapping id = ");
    text_log.Print(m_mapping_id);
    if (m_mapping_id == ON_MappingTag::SurfaceParameterMapping.m_mapping_id)
      text_log.Print(" = ON_MappingTag::SurfaceParameterMapping.m_mapping_id");
    else if (m_mapping_id == ON_SurfaceCurvatureColorMapping::Id)
      text_log.Print(" = ON_SurfaceCurvatureColorMapping::Id");
    else if (m_mapping_id == ON_SurfaceDraftAngleColorMapping::Id)
      text_log.Print(" = ON_SurfaceDraftAngleColorMapping::Id");
    text_log.PrintNewLine();

    text_log.Print("mapping crc: %08x\n", m_mapping_crc);

    text_log.Print("mesh xform:");
    if (ON_Xform::IdentityTransformation == m_mesh_xform)
      text_log.Print(" ON_Xform::IdentityTransformation\n");
    else if (ON_Xform::ZeroTransformation == m_mesh_xform)
      text_log.Print(" ON_Xform::ZeroTransformation\n");
    else if (ON_Xform::Zero4x4 == m_mesh_xform)
      text_log.Print(" ON_Xform::Zero4x4\n");
    else if (ON_Xform::Unset == m_mesh_xform)
      text_log.Print(" ON_Xform::Unset\n");
    else
    {
      text_log.PrintNewLine();
      const ON_TextLogIndent indent2(text_log);
      text_log.Print(m_mesh_xform);
    }
  }

  if (lod >= ON_TextLog::LevelOfDetail::Maximum)
  {
    text_log.PopIndent();
  }
}

void ON_MappingTag::Transform( const ON_Xform& xform )
{
  if ( !ON_UuidIsNil(m_mapping_id) )
  {
    // Update mapping transformation.
    // Do NOT change the value of m_mapping_crc.
    m_mesh_xform = xform*m_mesh_xform;
  }
}

void ON_MappingTag::SetDefaultSurfaceParameterMappingTag()
{
  Set(ON_TextureMapping::SurfaceParameterTextureMapping); 
}

void ON_MappingTag::Set(const ON_TextureMapping& mapping)
{
  Default();
  m_mapping_id   = mapping.Id();
  m_mapping_type = mapping.m_type;
  m_mapping_crc  = mapping.MappingCRC();
}

bool ON_MappingTag::IsSet() const
{
  return (0 != m_mapping_crc || !ON_UuidIsNil(m_mapping_id));
}

bool ON_MappingTag::IsDefaultSurfaceParameterMapping() const
{
  bool rc = (ON_TextureMapping::TYPE::srfp_mapping == m_mapping_type);
  if ( rc )
  {
    // The crc needs to be checked to insure that m_uvw
    // was the identity.
    rc = (m_mapping_crc == ON_TextureMapping::SurfaceParameterTextureMapping.MappingCRC());
  }
  return rc;
}


const ON_SHA1_Hash ON_MappingTag::Hash() const
{
  bool bHashType = true;
  bool bHashIdAndCRC = false;
  bool bHashXform = false;
  switch (m_mapping_type)
  {
  case ON_TextureMapping::TYPE::no_mapping:
    bHashType = false;
    break;
  case ON_TextureMapping::TYPE::srfp_mapping:
    break;
  case ON_TextureMapping::TYPE::plane_mapping:
  case ON_TextureMapping::TYPE::cylinder_mapping:
  case ON_TextureMapping::TYPE::sphere_mapping:
  case ON_TextureMapping::TYPE::box_mapping:
  case ON_TextureMapping::TYPE::mesh_mapping_primitive:
  case ON_TextureMapping::TYPE::srf_mapping_primitive:
  case ON_TextureMapping::TYPE::brep_mapping_primitive:
  case ON_TextureMapping::TYPE::ocs_mapping:
    if (IsSet())
    {
      bHashIdAndCRC = true;
      if (false == m_mesh_xform.IsIdentity(ON_ZERO_TOLERANCE) && false == m_mesh_xform.IsZero() && m_mesh_xform.IsValid())
        bHashXform = true;
    }
    else
      bHashType = false; // bogus mapping - treat as unset 
    break;
  default:
    // Perhaps somebody added a value to the enum after June 2020 and failed to update this code?
    ON_ERROR("Invalid m_mapping_type value.");
    break;
  }

  ON_SHA1 sha1;
  if (bHashType)
  {
    const unsigned char u = (unsigned char)m_mapping_type;
    sha1.AccumulateBytes(&u,1);
  }
  if (bHashIdAndCRC)
  {
    sha1.AccumulateId(m_mapping_id);
    sha1.AccumulateInteger32(m_mapping_crc);
  }
  if (bHashXform)
  {
    sha1.AccumulateTransformation(m_mesh_xform);
  }
  return sha1.Hash();
}


void ON_MappingTag::Default()
{
  memset(this,0,sizeof(*this));
  m_mesh_xform.m_xform[0][0] = 1.0;
  m_mesh_xform.m_xform[1][1] = 1.0;
  m_mesh_xform.m_xform[2][2] = 1.0;
  m_mesh_xform.m_xform[3][3] = 1.0;
}


int ON_MappingTag::CompareAll(const ON_MappingTag& lhs, const ON_MappingTag& rhs)
{
  const unsigned lhs_type = static_cast<unsigned int>(lhs.m_mapping_type);
  const unsigned rhs_type = static_cast<unsigned int>(rhs.m_mapping_type);
  if (lhs_type < rhs_type)
    return -1;
  if (lhs_type > rhs_type)
    return 1;
  int rc = ON_UuidCompare(lhs.m_mapping_id, rhs.m_mapping_id);
  if (0 != rc)
    return rc;
  if (lhs.m_mapping_crc < rhs.m_mapping_crc)
    return -1;
  if (lhs.m_mapping_crc > rhs.m_mapping_crc)
    return 1;
  return  lhs.m_mesh_xform.Compare(rhs.m_mesh_xform);
}

bool operator==(const ON_MappingTag& lhs, const ON_MappingTag& rhs)
{
  if (lhs.m_mapping_type == rhs.m_mapping_type && lhs.m_mapping_id == rhs.m_mapping_id)
  {
    if (ON_TextureMapping::TYPE::no_mapping == lhs.m_mapping_type && ON_nil_uuid == lhs.m_mapping_id)
    {
      // m_mapping_crc and m_mesh_xform are meaningless and are ignored
      return true;
    }    

    if (ON_TextureMapping::TYPE::srfp_mapping == lhs.m_mapping_type && ON_MappingTag::SurfaceParameterMapping.m_mapping_id == lhs.m_mapping_id)
    {
      // m_mesh_xform is meaningless and is ignored
      // (m_mapping_crc can be from a uvw texture coordinate transformation and must be checked)
      return lhs.m_mapping_crc == rhs.m_mapping_crc;
    }
  }

  return lhs.m_mapping_crc == rhs.m_mapping_crc && 0 == lhs.m_mesh_xform.Compare(rhs.m_mesh_xform);
}

bool operator!=(const ON_MappingTag& lhs, const ON_MappingTag& rhs)
{
  if (lhs.m_mapping_type != rhs.m_mapping_type || false == (lhs.m_mapping_id == rhs.m_mapping_id))
    return true;

  if (ON_TextureMapping::TYPE::no_mapping == lhs.m_mapping_type && ON_nil_uuid == lhs.m_mapping_id)
  {
    // m_mapping_crc and m_mesh_xform are meaningless and are ignored
    return false;
  }

  if (ON_TextureMapping::TYPE::srfp_mapping == lhs.m_mapping_type && ON_MappingTag::SurfaceParameterMapping.m_mapping_id == lhs.m_mapping_id)
  {
    // m_mesh_xform is meaningless and is ignored
    // (m_mapping_crc can be from a uvw texture coordinate transformation and must be checked)
    return lhs.m_mapping_crc != rhs.m_mapping_crc;
  }

  return (lhs.m_mapping_crc != rhs.m_mapping_crc || 0 != lhs.m_mesh_xform.Compare(rhs.m_mesh_xform));
}

int ON_MappingTag::CompareAllFromPointer(const ON_MappingTag* lhs, const ON_MappingTag* rhs)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  return ON_MappingTag::CompareAll(*lhs, *rhs);
}

int ON_MappingTag::Compare( 
             const ON_MappingTag& other,
             bool bCompareId,
             bool bCompareCRC,
             bool bCompareXform
             ) const
{
  int rc = 0;
  if ( !rc && bCompareId )
  {
    rc = ON_UuidCompare(m_mapping_id,other.m_mapping_id);
  }
  if ( !rc && bCompareCRC )
  {
    if (m_mapping_crc < other.m_mapping_crc)
      return -1;
    if (m_mapping_crc > other.m_mapping_crc)
      return 1;
  }
  if ( !rc && bCompareXform )
  {
    rc = m_mesh_xform.Compare(other.m_mesh_xform);
  }
  return rc;
}



bool ON_MappingTag::Write(ON_BinaryArchive& archive) const
{
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,1);
  if (!rc)
    return false;

  for(;;)
  {
    rc = archive.WriteUuid(m_mapping_id);
    if(!rc) break;
    rc = archive.WriteInt(m_mapping_crc);
    if(!rc) break;
    rc = archive.WriteXform(m_mesh_xform);
    if(!rc) break;

    // 1.1 fields
    rc = archive.WriteInt(static_cast<unsigned int>(m_mapping_type));
    if (!rc) break;

    break;
  }

  if ( !archive.EndWrite3dmChunk() )
    rc = false;
  
  return rc;
}

bool ON_MappingTag::Read(ON_BinaryArchive& archive)
{
  Default();
  int mjv = 0, mnv = 0;
  bool rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&mjv,&mnv);
  if (!rc)
    return false;

  for(;;)
  {
    rc = (1 == mjv);
    if (!rc) break;
    rc = archive.ReadUuid(m_mapping_id);
    if(!rc) break;
    if ( 0 == ON_UuidCompare(&obsolete_default_srfp_mapping_id,&m_mapping_id) )
      m_mapping_id = ON_nil_uuid;
    rc = archive.ReadInt(&m_mapping_crc);
    if(!rc) break;
    rc = archive.ReadXform(m_mesh_xform);
    if(!rc) break;

    if ( mnv >= 1 )
    {
      // 1.1 fields
      unsigned int i = static_cast<unsigned int>(m_mapping_type);
      rc = archive.ReadInt(&i);
      if ( rc )
        m_mapping_type = ON_TextureMapping::TypeFromUnsigned(i);
      if (!rc) break;
    }

    break;
  }

  if ( !archive.EndRead3dmChunk() )
    rc = false;
  
  return rc;
}

ON_TextureCoordinates::ON_TextureCoordinates()
{
  m_dim = 0;
}


///////////////////////////////////////////////////////
//
// Double precision vertices
//

ON_OBJECT_IMPLEMENT(ON_V5_MeshDoubleVertices,ON_UserData,"17F24E75-21BE-4a7b-9F3D-7F85225247E3");

ON_V5_MeshDoubleVertices* ON_V5_MeshDoubleVertices::GetV5(const ON_Mesh* mesh)
{
  return ON_V5_MeshDoubleVertices::Cast(mesh->GetUserData(ON_CLASS_ID(ON_V5_MeshDoubleVertices)));
}

ON_V5_MeshDoubleVertices* ON_V5_MeshDoubleVertices::AttachV5(const ON_Mesh* mesh)
{
  ON_V5_MeshDoubleVertices* dv = ON_V5_MeshDoubleVertices::GetV5(mesh);
  if ( 0 != dv )
    return 0;
  dv = new ON_V5_MeshDoubleVertices();
  const_cast<ON_Mesh*>(mesh)->AttachUserData(dv);
  return dv;
}

ON_V5_MeshDoubleVertices::ON_V5_MeshDoubleVertices()
{
  m_userdata_uuid = ON_CLASS_ID(ON_V5_MeshDoubleVertices);
  m_application_uuid = ON_opennurbs5_id;
  m_userdata_copycount = 1;
}

ON_V5_MeshDoubleVertices::~ON_V5_MeshDoubleVertices()
{}

bool ON_V5_MeshDoubleVertices::IsValid( ON_TextLog* ) const
{
  return true;
}

void ON_V5_MeshDoubleVertices::Dump( ON_TextLog& text_log ) const
{
  // TODO - print some double values
  ON_UserData::Dump(text_log);
}

unsigned int ON_V5_MeshDoubleVertices::SizeOf() const
{
  return m_V5_dV.SizeOfArray() + ON_UserData::SizeOf();
}

ON__UINT32 ON_V5_MeshDoubleVertices::DataCRC(ON__UINT32 current_remainder) const
{
  current_remainder = ON_CRC32(current_remainder,sizeof(m_fcount),&m_fcount);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_dcount),&m_dcount);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_fCRC),&m_fCRC);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_dCRC),&m_dCRC);
  current_remainder = m_V5_dV.DataCRC(current_remainder);
  return current_remainder;  
}

bool ON_V5_MeshDoubleVertices::DeleteAfterWrite(
  const class ON_BinaryArchive& archive,
  const class ON_Object* parent_object
  ) const
{
  // ON_V5_MeshDoubleVertices is used when saving earlier versions of files and then deleted.
  return true;
}

bool ON_V5_MeshDoubleVertices::DeleteAfterRead(
  const class ON_BinaryArchive& archive,
  class ON_Object* parent_object
  ) const
{
  ON_Mesh* mesh = ON_Mesh::Cast(parent_object);
  if (nullptr != mesh && 0 == mesh->m_dV.UnsignedCount() )
  {
    const unsigned int vertex_count = mesh->VertexUnsignedCount();
    if (vertex_count == m_V5_dV.UnsignedCount())
    {
      mesh->m_dV = m_V5_dV;
      if (false == mesh->HasSynchronizedDoubleAndSinglePrecisionVertices())
        mesh->DestroyDoublePrecisionVertices();
      else
      {
        // update vertex bounding boxes
        mesh->InvalidateVertexBoundingBox();
        mesh->BoundingBox();
      }
    }
  }
  return true;
}

bool ON_V5_MeshDoubleVertices::Write(ON_BinaryArchive& file) const
{
  bool rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
  if (!rc)
    return false;
  for(;;)
  {
    rc = file.WriteInt(m_fcount);
    if (!rc)
      break;
    rc = file.WriteInt(m_dcount);
    if (!rc)
      break;
    rc = file.WriteInt(m_fCRC);
    if (!rc)
      break;
    rc = file.WriteInt(m_dCRC);
    if (!rc)
      break;
    rc = file.WriteArray(m_V5_dV);
    if (!rc)
      break;
    break;
  }
  if ( !file.EndWrite3dmChunk() )
    rc = false;
  return rc;
}

bool ON_V5_MeshDoubleVertices::Read(ON_BinaryArchive& file)
{
  m_fcount = 0;
  m_dcount = 0;
  m_fCRC = 0;
  m_dCRC = 0;
  m_V5_dV.Destroy();

  int major_version = 0;
  int minor_version = 0;
  bool rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if (!rc)
    return false;
  for(;;)
  {
    rc = file.ReadInt(&m_fcount);
    if (!rc)
      break;
    rc = file.ReadInt(&m_dcount);
    if (!rc)
      break;
    rc = file.ReadInt(&m_fCRC);
    if (!rc)
      break;
    rc = file.ReadInt(&m_dCRC);
    if (!rc)
      break;
    rc = file.ReadArray(m_V5_dV);
    if (!rc)
      break;
    break;
  }
  if ( !file.EndRead3dmChunk() )
    rc = false;
    return rc;
}

// virtual ON_UserData overrides
bool ON_V5_MeshDoubleVertices::GetDescription( ON_wString& description )
{
  description = L"ON_Mesh double precision vertices";
  return true;
}

bool ON_V5_MeshDoubleVertices::Archive() const
{
  // refuse to save garbage in files.

  if ( m_fcount != m_dcount )
  {
    ON_ERROR("m_fcount != m_dcount");
    return false;
  }

  if ( m_dcount != m_V5_dV.Count() )
  {
    ON_ERROR("m_dcount != m_dV.Count()");
    return false;
  }

  if ( m_dCRC != DoubleCRC() )
  {
    ON_ERROR("m_dCRC != DoubleCRC()");
    return false;
  }

  const ON_Mesh* mesh = ON_Mesh::Cast( Owner() );
  if ( 0 == mesh )
  {
    ON_ERROR("0 = ON_Mesh::Cast( Owner() )");
    return false;
  }

  if ( m_fcount != mesh->m_V.Count() )
  {
    ON_ERROR("m_fcount != mesh->m_V.Count()");
    return false;
  }

  if ( m_fCRC != ON_V5_MeshDoubleVertices::FloatCRC(mesh->m_V) )
  {
    ON_ERROR("m_fCRC != ON_V5_MeshDoubleVertices::FloatCRC(mesh->m_V)");
    return false;
  }

  return true;
}

bool ON_V5_MeshDoubleVertices::Transform( const ON_Xform& xform )
{
  if ( !xform.IsIdentity() )
  {
    const ON__UINT32 crc0 = DoubleCRC();
    m_V5_dV.Transform(xform);
    const ON__UINT32 crc1 = DoubleCRC();
    if ( crc0 == m_dCRC && m_V5_dV.Count() == m_dcount )
      m_dCRC = crc1; // update m_dCRC so it stays valid
    else
      m_dCRC = (0==crc1)?1:0; // make sure m_dCRC is not valid
  }
  return true;
}

ON_Mesh* ON_Mesh::OffsetMesh(const double distance, const ON_3dVector& direction) const
{
  if (0.0 == distance)
    return nullptr;

  ON_3fVector VN;
  ON_3dVector N;
  ON_3dPoint P;

  int k, tvi, vi;

  //Make the topology for the old mesh in the event that it does not already exist.
  Topology();

  ON_Mesh* new_mesh = Duplicate();
  if (nullptr == new_mesh)
    return nullptr;

  if (!new_mesh->HasVertexNormals())
    new_mesh->ComputeVertexNormals();

  // D = double precision vertices
  ON_3dPoint* D = 0;
  if (new_mesh->HasDoublePrecisionVertices())
  {
    if (new_mesh->m_dV.Count() > 0)
      D = new_mesh->m_dV.Array();
    else
      new_mesh->DestroyDoublePrecisionVertices();
  }

  const ON_MeshTopology& top = new_mesh->Topology();

  if (false == top.IsValid() || false == new_mesh->HasVertexNormals())
  {
    delete new_mesh;
    return nullptr;
  }

  for (tvi = 0; tvi < top.m_topv.Count(); tvi++)
  {
    N = ON_3dVector::ZeroVector;
    const ON_MeshTopologyVertex& topv = top.m_topv[tvi];
    if (direction == ON_3dVector::UnsetVector)
    {
      // Per-vertex offset direction
      for (k = 0; k < topv.m_v_count; k++)
      {
        vi = topv.m_vi[k];
        VN = new_mesh->m_N[vi];
        N.x += VN.x; N.y += VN.y; N.z += VN.z;
      }
    }
    else
    {
      // Single offset direction for all vertices
      N = direction;
    }
    N.Unitize();
    N = distance * N;
    for (k = 0; k < topv.m_v_count; k++)
    {
      vi = topv.m_vi[k];
      if (0 != D)
      {
        // double precision calculation
        P = D[vi];
        P = P + N;
        D[vi] = P;
      }
      else
      {
        // single precision calculation
        P = new_mesh->m_V[vi];
        P = P + N;
        new_mesh->m_V[vi] = P;
      }
    }
  }

  if (0 != D)
  {
    new_mesh->UpdateSinglePrecisionVertices();
  }

  new_mesh->DestroyPartition();
  new_mesh->DestroyRuntimeCache();
  new_mesh->DestroyTopology();
  new_mesh->InvalidateVertexBoundingBox();
  new_mesh->InvalidateVertexNormalBoundingBox();
  new_mesh->InvalidateCurvatureStats();

  return new_mesh;
}




bool ON_Mesh::HasSynchronizedDoubleAndSinglePrecisionVertices() const
{
  const unsigned int vertex_count = VertexUnsignedCount();
  if (0 == vertex_count)
    return false;

  if (vertex_count != m_V.UnsignedCount())
    return false;
  if (vertex_count != m_dV.UnsignedCount())
    return false;

  ON_3dPoint P;
  const ON_3fPoint* FV = m_V.Array();
  const ON_3dPoint* DV = m_dV.Array();
  for (unsigned int vi = 0; vi < vertex_count; vi++ )
  {
    // Compare float values.
    P.x = (float)DV->x;
    P.y = (float)DV->y;
    P.z = (float)DV->z;
    if ( !(P.x == FV->x && P.y == FV->y && P.z == FV->z) )
      return false;
    DV++;
    FV++;
  }
  return true;
}

bool ON_Mesh::HasDoublePrecisionVertices() const
{
  const unsigned int vertex_count = VertexUnsignedCount();
  return ( vertex_count > 0 && vertex_count == m_dV.UnsignedCount() );
}

bool ON_Mesh::HasSinglePrecisionVertices() const
{
  const unsigned int vertex_count = VertexUnsignedCount();
  return ( vertex_count > 0 && vertex_count == m_V.UnsignedCount() );
}

void ON_Mesh::DestroyDoublePrecisionVertices()
{
  m_dV.Destroy();
}

ON__UINT32 ON_V5_MeshDoubleVertices::FloatCRC( const ON_3fPointArray& V )
{
  return V.DataCRC(0);
}

ON__UINT32 ON_V5_MeshDoubleVertices::DoubleCRC() const
{
  return m_V5_dV.DataCRC(0);
}

void ON_Mesh::UpdateSinglePrecisionVertices()
{
  unsigned int vertex_count = m_dV.UnsignedCount();
  m_V.Reserve(vertex_count);
  m_V.SetCount(vertex_count);
  if (0 == vertex_count)
    return;

  ON_3fPoint* fV = m_V.Array();
  ON_3fPoint* fVend = fV + vertex_count;
  const ON_3dPoint* dV = m_dV.Array();
  while (fV < fVend)
  {
    fV->x = (float)dV->x;
    fV->y = (float)dV->y;
    fV->z = (float)dV->z;
    fV++;
    dV++;
  }
}

void ON_Mesh::UpdateDoublePrecisionVertices()
{
  const unsigned int vertex_count = m_V.UnsignedCount();
  const bool bSelectiveUpdate = (vertex_count == m_dV.UnsignedCount());

  m_dV.Reserve(vertex_count);
  m_dV.SetCount(vertex_count);
  if (0 == vertex_count)
    return;

  ON_3dPoint* dV = m_dV.Array();
  ON_3dPoint* dVend = dV + vertex_count;
  const ON_3fPoint* fV = m_V.Array();
  if ( bSelectiveUpdate )
  {
    // double precision vertices already existed
    // and there is a reasonable chance that 
    // a subset of the float precision vertices
    // have been modified.  So, attempt to
    // keep the precision on double vertices
    // that already agree with the float vertices
    // in float precision.
    ON_3fPoint P;
    while (dV < dVend)
    {
      P.x = (float)dV->x;
      P.y = (float)dV->y;
      P.z = (float)dV->z;
      if ( !(P.x == fV->x && P.y == fV->y && P.z == fV->z) )
      {
        // (float)dV != fV, so update dV
        dV->x = (double)fV->x;
        dV->y = (double)fV->y;
        dV->z = (double)fV->z;
      }
      dV++;
      fV++;
    }
  }
  else
  {
    while (dV < dVend)
    {
      dV->x = (double)fV->x;
      dV->y = (double)fV->y;
      dV->z = (double)fV->z;
      dV++;
      fV++;
    }
  }
}

ON_3dPointArray& ON_Mesh::DoublePrecisionVertices()
{
  const unsigned int vertex_count = VertexUnsignedCount();
  if ( vertex_count != m_dV.UnsignedCount() )
    UpdateDoublePrecisionVertices();

  return m_dV;
}

ON_3dPoint ON_Mesh::Vertex(int vertex_index) const
{
  const unsigned int vertex_count = m_V.UnsignedCount();
  if ( vertex_index < 0 || ((unsigned int)vertex_index) >= vertex_count )
    return ON_3dPoint::UnsetPoint;

  const ON_3fPoint F = m_V[vertex_index];
  if (vertex_count == m_dV.UnsignedCount())
  {
    ON_3dPoint D = m_dV[vertex_index];
    if ( F.x == (float)D.x && F.y == (float)D.y && F.z == (float)D.z )
    {
      // double precision vertex is valid
      return D;
    }
  }

  return F;
}

const ON_3dPointArray& ON_Mesh::DoublePrecisionVertices() const
{
  ON_Mesh& mesh = const_cast<ON_Mesh&>(*this);
  ON_3dPointArray& a = mesh.DoublePrecisionVertices();
  return a;
}

////////////////////////////////////////////////////////////////
//
// BEGIN ON_PerObjectMeshParameters user data class
//


class /*NEVER EXPORT THIS CLASS DEFINITION*/ ON_PerObjectMeshParameters : public ON_UserData
{
#if !defined(ON_BOZO_VACCINE_B5628CA982C44CAE9883487B3E4AB28B)
#error Never copy this class definition or put this definition in a header file!
#endif
  ON_OBJECT_DECLARE(ON_PerObjectMeshParameters);

public:
  ON_PerObjectMeshParameters();
  ~ON_PerObjectMeshParameters();
  // default copy constructor and operator= work fine.

public:
  // virtual ON_Object override
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  // virtual ON_Object override
  unsigned int SizeOf() const override;
  // virtual ON_Object override
  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const override;
  // virtual ON_Object override
  bool Write(ON_BinaryArchive& binary_archive) const override;
  // virtual ON_Object override
  bool Read(ON_BinaryArchive& binary_archive) override;
  // virtual ON_UserData override
  bool Archive() const override;
  // virtual ON_UserData override
  bool GetDescription( ON_wString& description ) override;

public:
  static
  ON_PerObjectMeshParameters* FindOrCreate( const ON_Object*, bool bCreate );

  ON_MeshParameters m_mp;
};

#undef ON_BOZO_VACCINE_B5628CA982C44CAE9883487B3E4AB28B

ON_OBJECT_IMPLEMENT(ON_PerObjectMeshParameters,ON_UserData,"B5628CA9-82C4-4CAE-9883-487B3E4AB28B");

ON_PerObjectMeshParameters* ON_PerObjectMeshParameters::FindOrCreate(const ON_Object* object,bool bCreate)
{
  if ( 0 == object )
    return 0;
  ON_PerObjectMeshParameters* ud = ON_PerObjectMeshParameters::Cast(object->GetUserData(ON_CLASS_ID(ON_PerObjectMeshParameters)));
  if ( !ud && bCreate )
  {
    ud = new ON_PerObjectMeshParameters();
    const_cast< ON_Object* >(object)->AttachUserData(ud);
  }
  return ud;
}

ON_PerObjectMeshParameters::ON_PerObjectMeshParameters()
: m_mp(ON_MeshParameters::FastRenderMesh)
{
  m_userdata_uuid = ON_CLASS_ID(ON_PerObjectMeshParameters);
  m_application_uuid = ON_opennurbs5_id;
  m_userdata_copycount = 1;
  m_mp.SetCustomSettings(true);
  m_mp.SetComputeCurvature(false);
}

ON_PerObjectMeshParameters::~ON_PerObjectMeshParameters()
{
}

// virtual ON_Object override
bool ON_PerObjectMeshParameters::IsValid( ON_TextLog* text_log ) const
{
  return true;
}

// virtual ON_Object override
unsigned int ON_PerObjectMeshParameters::SizeOf() const
{
  size_t sz = sizeof(*this) - sizeof(ON_UserData);
  return (unsigned int)sz;
}

// virtual ON_Object override
ON__UINT32 ON_PerObjectMeshParameters::DataCRC(ON__UINT32 current_remainder) const
{
  return m_mp.DataCRC(current_remainder);
}

// virtual ON_Object override
bool ON_PerObjectMeshParameters::Write(ON_BinaryArchive& binary_archive) const
{
  if ( !binary_archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0) )
    return false;

  bool rc = false;
  for(;;)
  {
    if ( !binary_archive.BeginWrite3dmBigChunk(TCODE_ANONYMOUS_CHUNK,0) )
      break;
    bool mprc = m_mp.Write(binary_archive);
    if ( !binary_archive.EndWrite3dmChunk() )
      break;
    if ( !mprc )
      break;
    rc = true;
    break;
  }

  if ( !binary_archive.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

// virtual ON_Object override
bool ON_PerObjectMeshParameters::Read(ON_BinaryArchive& binary_archive)
{
  m_mp = ON_MeshParameters::FastRenderMesh;
  m_mp.SetCustomSettings(true);
  m_mp.SetComputeCurvature(false);

  int major_version = 0;
  int minor_version = 0;
  if ( !binary_archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version) )
    return false;
    
  bool rc = false;
  for(;;)
  {
    if ( 1 != major_version )
      break;

    unsigned int tcode(0);
    ON__INT64 value(0);
    if (!binary_archive.BeginRead3dmBigChunk(&tcode,&value))
      break;
    bool mprc = false;
    for(;;)
    {
      if (TCODE_ANONYMOUS_CHUNK != tcode )
        break;
      if (value <= 0)
        break;
      if (!m_mp.Read(binary_archive))
        break;
      mprc = true;
      break;
    }
    if (!binary_archive.EndRead3dmChunk())
      break;
    if (!mprc)
      break;

    rc = true;
    break;
  }

  if ( !binary_archive.EndRead3dmChunk() )
    rc = false;

  m_mp.SetCustomSettings(true);
  m_mp.SetComputeCurvature(false);

  return rc;
}

// virtual ON_UserData override
bool ON_PerObjectMeshParameters::Archive() const
{
  return true;
}

// virtual ON_UserData override
bool ON_PerObjectMeshParameters::GetDescription( ON_wString& description )
{
  description = L"Custom Render Mesh Parameters";
  return true;
}

//
// END ON_PerObjectMeshParameters user data class
//
////////////////////////////////////////////////////////////////

const ON_MeshParameters* ON_3dmObjectAttributes::CustomRenderMeshParameters() const
{
  const ON_PerObjectMeshParameters* ud = ON_PerObjectMeshParameters::FindOrCreate(this,false);
  return (0 != ud) ? &ud->m_mp : 0;
}

bool ON_3dmObjectAttributes::SetCustomRenderMeshParameters( const ON_MeshParameters& mp )
{
  ON_PerObjectMeshParameters* ud = ON_PerObjectMeshParameters::FindOrCreate(this,true);
  if ( 0 == ud )
    return false;
  ud->m_mp = mp;
  ud->m_mp.SetCustomSettings(true);
  ud->m_mp.SetComputeCurvature(false);
  return true;
}

void ON_3dmObjectAttributes::DeleteCustomRenderMeshParameters()
{
  ON_PerObjectMeshParameters* ud = ON_PerObjectMeshParameters::FindOrCreate(this,false);
  if ( 0 != ud )
    delete ud;
}

bool ON_3dmObjectAttributes::EnableCustomRenderMeshParameters(bool bEnable)
{
  ON_PerObjectMeshParameters* ud = ON_PerObjectMeshParameters::FindOrCreate(this,false);
  if ( 0 != ud )
    ud->m_mp.SetCustomSettingsEnabled(bEnable);
  return (!bEnable || nullptr != ud);
}

void ON_Mesh::DestroyTree( bool bDeleteTree )
{
}




static int compare2fPoint(const void* a, const void* b)
{
  const float* af = (const float*)a;
  const float* bf = (const float*)b;
  if (af[0] < bf[0])
    return -1;
  if (af[0] > bf[0])
    return 1;
  if (af[1] < bf[1])
    return -1;
  if (af[1] > bf[1])
    return 1;
  return 0;
}

static int compare2dPoint(const void* a, const void* b)
{
  const double* af = (const double*)a;
  const double* bf = (const double*)b;
  if (af[0] < bf[0])
    return -1;
  if (af[0] > bf[0])
    return 1;
  if (af[1] < bf[1])
    return -1;
  if (af[1] > bf[1])
    return 1;
  return 0;
}

//static int compare3fPoint(const void* a, const void* b)
//{
//  const float* af = (const float*)a;
//  const float* bf = (const float*)b;
//  if (af[0] < bf[0])
//    return -1;
//  if (af[0] > bf[0])
//    return 1;
//  if (af[1] < bf[1])
//    return -1;
//  if (af[1] > bf[1])
//    return 1;
//  if (af[2] < bf[2])
//    return -1;
//  if (af[2] > bf[2])
//    return 1;
//  return 0;
//}
//
//static int compare3dPoint(const void* a, const void* b)
//{
//  const double* af = (const double*)a;
//  const double* bf = (const double*)b;
//  if (af[0] < bf[0])
//    return -1;
//  if (af[0] > bf[0])
//    return 1;
//  if (af[1] < bf[1])
//    return -1;
//  if (af[1] > bf[1])
//    return 1;
//  if (af[2] < bf[2])
//    return -1;
//  if (af[2] > bf[2])
//    return 1;
//  return 0;
//}


static int comparedUnsignedPair(const void* a, const void* b)
{
  const unsigned int* au = ((const unsigned int*)a);
  const unsigned int* bu = ((const unsigned int*)b);
  if (au[0] < bu[0])
    return -1;
  if (au[0] > bu[0])
    return 1;
  if (au[1] < bu[1])
    return -1;
  if (au[1] > bu[1])
    return 1;
  return 0;
}

static unsigned int* ON_GetPointLocationIdsHelper(
  size_t point_dim,
  size_t point_count,
  size_t point_stride,
  const float* fPoints, 
  const double* dPoints, 
  unsigned int first_vid, 
  unsigned int* Vid, 
  unsigned int* Vindex
  )
{
  // Used here and in opennurbs_plus_xmeshfast.cpp

  if (point_count <= 0 || point_dim < 2 || point_dim > 3 || point_stride < point_dim)
    return nullptr;

  if (nullptr == fPoints && nullptr == dPoints)
    return nullptr;

  const unsigned int Vcount = (unsigned int)point_count;
  if (0 == Vid)
    Vid = (unsigned int*)onmalloc(Vcount*sizeof(*Vid));

  if (1 == point_count)
  {
    Vid[0] = first_vid;
    if (nullptr != Vindex)
      Vindex[0] = 0;
    return Vid;
  }

  if (2 == point_dim)
  {
    // Dictionary sort the 2d points (sort on x, then y).
    if (nullptr != dPoints)
      ON_Sort(ON::sort_algorithm::quick_sort, Vid, dPoints, Vcount, point_stride*sizeof(dPoints[0]), compare2dPoint);
    else
      ON_Sort(ON::sort_algorithm::quick_sort, Vid, fPoints, Vcount, point_stride*sizeof(fPoints[0]), compare2fPoint);
  }
  else
  {
    // Dictionary sort the 3d points (sort on x, then y, then z).
    if (nullptr != dPoints)
      ON_Sort(ON::sort_algorithm::quick_sort, Vid, dPoints, Vcount, point_stride*sizeof(dPoints[0]), (ON_COMPAR_LPVOID_LPVOID)compare3dPoint);
    else
      ON_Sort(ON::sort_algorithm::quick_sort, Vid, fPoints, Vcount, point_stride*sizeof(fPoints[0]), (ON_COMPAR_LPVOID_LPVOID)compare3fPoint);
  }
    
  // Assign a unique temporary id to each group of coincident points.
  // The id is temporary because the order of the above sort will change
  // if the point set is rotated.
  struct tagUnsignedPair
  {
    unsigned int m_temporary_id;
    unsigned int m_vertex_index;
  } *up = new tagUnsignedPair[Vcount];

  unsigned int temporary_id = Vid[0];
  unsigned int i0 = 0;
  if (nullptr != dPoints)
  {
    const double* dP0 = dPoints + point_stride*Vid[0];
    if (3 == point_dim)
    {
      for (unsigned int i = 1; i < Vcount; i++)
      {
        const double* dP1 = dPoints + point_stride*Vid[i];
        if (dP0[0] == dP1[0] && dP0[1] == dP1[1] && dP0[2] == dP1[2])
        {
          if (Vid[i] < temporary_id)
            temporary_id = Vid[i];
        }
        else
        {
          while (i0 < i)
          {
            up[i0].m_temporary_id = temporary_id;
            up[i0].m_vertex_index = Vid[i0];
            i0++;
          }
          temporary_id = Vid[i0];
          dP0 = dP1;
        }
      }
    }
    else
    {
      for (unsigned int i = 1; i < Vcount; i++)
      {
        const double* dP1 = dPoints + point_stride*Vid[i];
        if (dP0[0] == dP1[0] && dP0[1] == dP1[1])
        {
          if (Vid[i] < temporary_id)
            temporary_id = Vid[i];
        }
        else
        {
          while (i0 < i)
          {
            up[i0].m_temporary_id = temporary_id;
            up[i0].m_vertex_index = Vid[i0];
            i0++;
          }
          temporary_id = Vid[i0];
          dP0 = dP1;
        }
      }
    }
  }
  else
  {
    const float* fP0 = fPoints + point_stride*Vid[0];
    if (3 == point_dim)
    {
      for (unsigned int i = 1; i < Vcount; i++)
      {
        const float* fP1 = fPoints + point_stride*Vid[i];
        if (fP0[0] == fP1[0] && fP0[1] == fP1[1] && fP0[2] == fP1[2])
        {
          if (Vid[i] < temporary_id)
            temporary_id = Vid[i];
        }
        else
        {
          while (i0 < i)
          {
            up[i0].m_temporary_id = temporary_id;
            up[i0].m_vertex_index = Vid[i0];
            i0++;
          }
          temporary_id = Vid[i0];
          fP0 = fP1;
        }
      }
    }
    else
    {
      for (unsigned int i = 1; i < Vcount; i++)
      {
        const float* fP1 = fPoints + point_stride*Vid[i];
        if (fP0[0] == fP1[0] && fP0[1] == fP1[1])
        {
          if (Vid[i] < temporary_id)
            temporary_id = Vid[i];
        }
        else
        {
          while (i0 < i)
          {
            up[i0].m_temporary_id = temporary_id;
            up[i0].m_vertex_index = Vid[i0];
            i0++;
          }
          temporary_id = Vid[i0];
          fP0 = fP1;
        }
      }
    }
  }

  while (i0 < Vcount)
  {
    up[i0].m_temporary_id = temporary_id;
    up[i0].m_vertex_index = Vid[i0];
    i0++;
  }

  // This sort is necessary to insure the vertex id does not change when 
  // the point set is transformed. It is important that the id be the
  // same in these situations so that vertex id groups retain the same 
  // id when meshes are rotated.
  ON_qsort(up, Vcount, sizeof(up[0]), comparedUnsignedPair);

  temporary_id = up[0].m_temporary_id;
  unsigned int id = first_vid;
  Vid[up[0].m_vertex_index] = id;
  for (unsigned int i = 1; i < Vcount; i++)
  {
    if (temporary_id != up[i].m_temporary_id)
    {
      temporary_id = up[i].m_temporary_id;
      id++;
    }
    Vid[up[i].m_vertex_index] = id;
  }

  if (0 != Vindex)
  {
    for (unsigned int i = 0; i < Vcount; i++)
    {
      Vindex[i] = up[i].m_vertex_index;
    }
  }

  delete[] up;

  return Vid;
}


unsigned int* ON_GetPointLocationIds(
  size_t point_dim,
  size_t point_count,
  size_t point_stride,
  const float* points,
  unsigned int first_point_id,
  unsigned int* point_ids,
  unsigned int* point_id_index
  )
{
  return ON_GetPointLocationIdsHelper(
    point_dim,
    point_count,
    point_stride,
    points,
    nullptr,
    first_point_id,
    point_ids,
    point_id_index
    );
}


unsigned int* ON_GetPointLocationIds(
  size_t point_dim,
  size_t point_count,
  size_t point_stride,
  const double* points,
  unsigned int first_point_id,
  unsigned int* point_ids,
  unsigned int* point_id_index
  )
{
  return ON_GetPointLocationIdsHelper(
    point_dim,
    point_count,
    point_stride,
    nullptr,
    points,
    first_point_id,
    point_ids,
    point_id_index
    );
}


unsigned int* ON_GetPointLocationIds(
  size_t point_count,
  const class  ON_2fPoint* points,
  unsigned int first_point_id,
  unsigned int* point_ids,
  unsigned int* point_id_map
  )
{
  const unsigned int point_dim = 2;
  return ON_GetPointLocationIds(point_dim, point_count, point_dim, (const float*)points, first_point_id, point_ids, point_id_map);
}


unsigned int* ON_GetPointLocationIds(
  size_t point_count,
  const class ON_3fPoint* points,
  unsigned int first_point_id,
  unsigned int* point_ids,
  unsigned int* point_id_map
  )
{
  const unsigned int point_dim = 3;
  return ON_GetPointLocationIds(point_dim, point_count, point_dim, (const float*)points, first_point_id, point_ids, point_id_map);
}


unsigned int* ON_GetPointLocationIds(
  size_t point_count,
  const class  ON_2dPoint* points,
  unsigned int first_point_id,
  unsigned int* point_ids,
  unsigned int* point_id_map
  )
{
  const unsigned int point_dim = 2;
  return ON_GetPointLocationIds(point_dim, point_count, point_dim, (const double*)points, first_point_id, point_ids, point_id_map);
}


unsigned int* ON_GetPointLocationIds(
  size_t point_count,
  const class ON_3dPoint* points,
  unsigned int first_point_id,
  unsigned int* point_ids,
  unsigned int* point_id_map
  )
{
  const unsigned int point_dim = 3;
  return ON_GetPointLocationIds(point_dim, point_count, point_dim, (const double*)points, first_point_id, point_ids, point_id_map);
}

unsigned int* ON_Mesh::GetVertexLocationIds(
  unsigned int first_vid,
  unsigned int* Vid,
  unsigned int* Vindex
  ) const
{
  const unsigned int vertex_count = VertexUnsignedCount();
  return (HasSynchronizedDoubleAndSinglePrecisionVertices())
    ? ON_GetPointLocationIds(vertex_count, m_dV.Array(), first_vid, Vid, Vindex)
    : ON_GetPointLocationIds(vertex_count, m_V.Array(), first_vid, Vid, Vindex);
}

unsigned int ON_MeshFaceSide::GetFaceSideList(
  size_t mesh_vertex_count,
  const class ON_MeshFaceList& mesh_face_list,
  const unsigned int* fi_list,
  size_t fi_list_count,
  const unsigned int* vertex_id_map,
  ON_MeshFaceSide*& face_side_list
  )
{
  const unsigned int Vcount = (unsigned int)mesh_vertex_count;
  if ( Vcount <= 0 )
    return 0;

  const unsigned int mesh_face_count = mesh_face_list.FaceCount();
  const unsigned int Fcount = (0 == fi_list) ? mesh_face_count : ((unsigned int)fi_list_count);

  if ( Fcount <= 0 )
    return 0;

  unsigned int fvi[4];
  int face_side_count = 0;
  ON_MeshFaceSide face_side = ON_MeshFaceSide::Unset;
  ON_MeshFaceSide* fs_list = face_side_list;

  if ( 0 == fs_list )
  {
    fs_list = (ON_MeshFaceSide*)onmalloc(4*Fcount*sizeof(fs_list[0]));
    if ( 0 == fs_list )
      return 0;
  }
  
  for ( face_side.m_fi = 0; face_side.m_fi < Fcount; face_side.m_fi++ )
  {
    if ( 0 != fi_list )
    {
      if ( fi_list[face_side.m_fi] >= mesh_face_count )
        continue;
      mesh_face_list.QuadFvi(fi_list[face_side.m_fi],fvi);
    }
    else
    {
      mesh_face_list.QuadFvi(face_side.m_fi,fvi);
    }

    // These checks are necessary to prevent crashes
    if ( fvi[0] >= Vcount )
      continue;
    if ( fvi[1] >= Vcount )
      continue;
    if ( fvi[2] >= Vcount )
      continue;
    if ( fvi[3] >= Vcount )
      continue;

    if ( 0 != vertex_id_map )
    {
      fvi[0] = vertex_id_map[fvi[0]];
      fvi[1] = vertex_id_map[fvi[1]];
      fvi[2] = vertex_id_map[fvi[2]];
      fvi[3] = vertex_id_map[fvi[3]];
    }

    if ( fvi[0] < fvi[1] )
    {
      face_side.m_vi[0] = fvi[0];
      face_side.m_vi[1] = fvi[1];
      face_side.m_side = 0;
      face_side.m_dir = 0;
      fs_list[face_side_count++] = face_side;
    }
    else if ( fvi[0] > fvi[1] )
    {
      face_side.m_vi[0] = fvi[1];
      face_side.m_vi[1] = fvi[0];
      face_side.m_side = 0;
      face_side.m_dir = 1;
      fs_list[face_side_count++] = face_side;
    }

    if ( fvi[1] < fvi[2] )
    {
      face_side.m_vi[0] = fvi[1];
      face_side.m_vi[1] = fvi[2];
      face_side.m_side = 1;
      face_side.m_dir = 0;
      fs_list[face_side_count++] = face_side;
    }
    else if ( fvi[1] > fvi[2] )
    {
      face_side.m_vi[0] = fvi[2];
      face_side.m_vi[1] = fvi[1];
      face_side.m_side = 1;
      face_side.m_dir = 1;
      fs_list[face_side_count++] = face_side;
    }

    if ( fvi[2] < fvi[3] )
    {
      face_side.m_vi[0] = fvi[2];
      face_side.m_vi[1] = fvi[3];
      face_side.m_side = 2;
      face_side.m_dir = 0;
      fs_list[face_side_count++] = face_side;
    }
    else if ( fvi[2] > fvi[3] )
    {
      face_side.m_vi[0] = fvi[3];
      face_side.m_vi[1] = fvi[2];
      face_side.m_side = 2;
      face_side.m_dir = 1;
      fs_list[face_side_count++] = face_side;
    }

    if ( fvi[3] < fvi[0] )
    {
      face_side.m_vi[0] = fvi[3];
      face_side.m_vi[1] = fvi[0];
      face_side.m_side = 3;
      face_side.m_dir = 0;
      fs_list[face_side_count++] = face_side;
    }
    else if ( fvi[3] > fvi[0] )
    {
      face_side.m_vi[0] = fvi[0];
      face_side.m_vi[1] = fvi[3];
      face_side.m_side = 3;
      face_side.m_dir = 1;
      fs_list[face_side_count++] = face_side;
    }
  }

  if ( 0 == face_side_list )
  {
    if ( face_side_count <= 0 )
      onfree(fs_list);
    else
      face_side_list = fs_list;
  }

  return face_side_count;
}

unsigned int ON_Mesh::GetMeshFaceSideList( 
    const unsigned int* Vid,
    ON_MeshFaceSide*& face_side_list
    ) const
{
  const unsigned int mesh_vertex_count = m_V.UnsignedCount();
  if ( mesh_vertex_count < 2 )
    return 0;

  const ON_MeshFaceList mesh_face_list(this);
  if ( mesh_face_list.FaceCount() < 1 )
    return 0;

  return (int)ON_MeshFaceSide::GetFaceSideList(
    mesh_vertex_count,
    mesh_face_list,
    0,0,
    Vid,
    face_side_list
    );
}


bool ON_Mesh::DeleteComponents(
  const ON_SimpleArray<ON_COMPONENT_INDEX>& ci_list
  )
{
  return DeleteComponents(ci_list.Array(), ci_list.UnsignedCount());
}

bool ON_Mesh::DeleteComponent(
  ON_COMPONENT_INDEX ci
  )
{
  return DeleteComponents(&ci, 1);
}

bool ON_Mesh::DeleteComponents(
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count
  )
{
  if (ci_count <= 0)
    return true;

  if (nullptr == ci_list)
    return false;

  bool bIgnoreInvalidComponents = true;
  bool bRemoveDegenerateFaces = false;
  bool bRemoveUnusedVertices = true;
  bool bRemoveEmptyNgons = true;

  return DeleteComponents(
  ci_list,ci_count,
  bIgnoreInvalidComponents,
  bRemoveDegenerateFaces,
  bRemoveUnusedVertices,
  bRemoveEmptyNgons
  );
}

bool ON_Mesh::DeleteComponents(
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count,
  bool bIgnoreInvalidComponents,
  bool bRemoveDegenerateFaces,
  bool bRemoveUnusedVertices,
  bool bRemoveEmptyNgons
)
{
  return DeleteComponents(ci_list, ci_count,
    bIgnoreInvalidComponents, bRemoveDegenerateFaces, bRemoveUnusedVertices, bRemoveEmptyNgons,
    nullptr);
}

static int Internal_FaceDegenerateAreaCheck(
  ON_MeshFace& f,
  int vertex_count,
  const ON_3fPoint* fV,
  const ON_3dPoint* dV
)
{
  // returns:
  // 0: f is degenerate
  // 1: f is not degenerate
  // 2: f was a degenerate quad and fixed to be a good triangle
  ON_3dPoint V[4];
  double a[2];
  const double atol = 1.0e-36; // a hair bigger than the smallest positive normalized float.
  if (nullptr != dV)
  {
    V[0] = dV[f.vi[0]];
    V[1] = dV[f.vi[1]];
    V[2] = dV[f.vi[2]];
    V[3] = dV[f.vi[3]];
  }
  else
  {
    V[0] = fV[f.vi[0]];
    V[1] = fV[f.vi[1]];
    V[2] = fV[f.vi[2]];
    V[3] = fV[f.vi[3]];
  }

  if (f.IsTriangle())
  {
    a[0] = ON_CrossProduct(V[1]-V[0],V[2]-V[0]).Length();
    return (a[0] > atol) ? 1 : 0;
  }
  
  a[0] = V[0].DistanceTo(V[2]);
  a[1] = V[1].DistanceTo(V[3]);

  // discard L shaped quads
  if (false == (a[0] > atol && a[1] > atol))
    return 0;

  if (a[0] <= a[1] * 1e-8)
    return 0; // quad is L shaped at floating point precision
  if (a[1] <= a[0] * 1e-8)
    return 0; // quad is L shaped at floating point precision

  if (a[0] <= a[1])
  {
    a[0] = ON_CrossProduct(V[1] - V[0], V[2] - V[0]).Length();
    a[1] = ON_CrossProduct(V[2] - V[0], V[3] - V[0]).Length();
    if (a[0] > atol)
    {
      if (a[1] > atol)
        return 1;
      f.vi[3] = -1;
    }
    else if (a[1] > atol)
      f.vi[1] = -1;
  }
  else if (a[1] < a[0] )
  {
    a[0] = ON_CrossProduct(V[2] - V[1], V[3] - V[1]).Length();
    a[1] = ON_CrossProduct(V[3] - V[1], V[0] - V[1]).Length();
    if (a[0] > atol)
    {
      if (a[1] > atol)
        return 1;
      f.vi[0] = -1;
    }
    else if (a[1] > atol)
      f.vi[2] = -1;
  }
  else
    return 0; // nan snuck through

  const bool bRepaired = (nullptr != dV) ? f.Repair(vertex_count, dV) : f.Repair(vertex_count, fV);
  return bRepaired ? 2 : 0;
}

bool ON_Mesh::DeleteComponents(
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count,
  bool bIgnoreInvalidComponents,
  bool bRemoveDegenerateFaces,
  bool bRemoveUnusedVertices,
  bool bRemoveEmptyNgons,
  unsigned int* faceMap
)
{
  if (ci_count <= 0 && false == bRemoveUnusedVertices && false == bRemoveEmptyNgons && false == bRemoveDegenerateFaces)
    return true;
  if (0 == ci_list && ci_count > 0)
    return false;

  const ON_MeshTopology* top = m_top.IsValid() ? &m_top : 0;
  const unsigned int vertex_count0 = m_V.UnsignedCount();
  const unsigned int face_count0 = m_F.UnsignedCount();
  const unsigned int ngon_count0 = NgonUnsignedCount();
  const unsigned int topvertex_count0 = top ? top->m_topv.UnsignedCount() : 0;
  const unsigned int topedge_count0 = top ? top->m_tope.UnsignedCount() : 0;
  unsigned int cdex, fi;
  ON_SimpleArray< unsigned int > point_id_map_buffer;
  ON_MeshFace point_id_map_f;
  unsigned int* point_id_map_fvi = (unsigned int*)point_id_map_f.vi;


  if (false == bIgnoreInvalidComponents)
  {
    for (size_t i = 0; i < ci_count; i++)
    {
      cdex = (unsigned int)(ci_list[i].m_index);
      switch (ci_list[i].m_type)
      {
      case ON_COMPONENT_INDEX::mesh_vertex:
        if (cdex >= vertex_count0)
          return false;
        break;
      case ON_COMPONENT_INDEX::meshtop_vertex:
        if (cdex >= topvertex_count0)
          return false;
        break;
      case ON_COMPONENT_INDEX::meshtop_edge:
        if (cdex >= topedge_count0)
          return false;
        break;
      case ON_COMPONENT_INDEX::mesh_face:
        if (cdex >= face_count0)
          return false;
        break;
      case ON_COMPONENT_INDEX::mesh_ngon:
        if (cdex >= ngon_count0)
          return false;
        break;
      
      default:
        break;
      }
    }
  }

  if (vertex_count0 <= 0)
    return (face_count0 <= 0);

  ON_SimpleArray<unsigned int> vertex_status_buffer(vertex_count0);
  vertex_status_buffer.SetCount(vertex_count0);
  vertex_status_buffer.Zero();
  unsigned int* vertex_status = vertex_status_buffer.Array();

  ON_SimpleArray<unsigned int> face_status_buffer;
  unsigned int* face_status;
  if (faceMap == nullptr)
  {
    face_status_buffer.SetCapacity(face_count0);
    face_status_buffer.SetCount(face_count0);
    face_status = face_status_buffer.Array();
  }
  else
  {
    face_status = faceMap;
  }
  memset(face_status, 0, m_F.UnsignedCount() * sizeof(unsigned int));

  bool bDoomedFaces = false;
  bool bDoomedVertices = false;
  bool bDoomedNgons = false;
  bool bModifiedFaces = false;

  const unsigned int* fvi;

  for (size_t i = 0; i < ci_count; i++)
  {
    cdex = (unsigned int)(ci_list[i].m_index);
    switch (ci_list[i].m_type)
    {
    case ON_COMPONENT_INDEX::mesh_vertex:
      if (cdex < vertex_count0)
      {
        bDoomedVertices = true;
        vertex_status[cdex] = ON_UNSET_UINT_INDEX;
      }
      break;

    case ON_COMPONENT_INDEX::meshtop_vertex:
      if (cdex < topvertex_count0)
      {
        const ON_MeshTopologyVertex& tv = top->m_topv[cdex];
        for (int tvi = 0; tvi < tv.m_v_count; tvi++)
        {
          const unsigned int vi = (unsigned int)(tv.m_vi[tvi]);
          if (vi < vertex_count0)
          {
            bDoomedVertices = true;
            vertex_status[vi] = ON_UNSET_UINT_INDEX;
          }
        }
      }
      break;

    case ON_COMPONENT_INDEX::meshtop_edge:
      if (cdex < topedge_count0)
      {
        const ON_MeshTopologyEdge& te = top->m_tope[cdex];
        if (0 != te.m_topfi)
        {
          for (int j = 0; j < te.m_topf_count; j++)
          {
            fi = (unsigned int)(te.m_topfi[j]);
            if (fi < face_count0)
            {
              bDoomedFaces = true;
              face_status[fi] = ON_UNSET_UINT_INDEX;
            }
          }
        }
      }
      break;

    case ON_COMPONENT_INDEX::mesh_face:
      if (cdex < face_count0)
      {
        bDoomedFaces = true;
        face_status[cdex] = ON_UNSET_UINT_INDEX;
      }
      break;

    case ON_COMPONENT_INDEX::mesh_ngon:
      if (cdex < ngon_count0)
      {
        const ON_MeshNgon* ngon = Ngon(cdex);
        if (0 != ngon)
        {
          const int ngon_index = cdex;
          bDoomedNgons = true;
          m_NgonMap.SetCount(0);
          if (0 != ngon->m_fi)
          {
            for (unsigned int j = 0; j < ngon->m_Fcount; j++)
            {
              fi = ngon->m_fi[j];
              if (fi < face_count0)
              {
                bDoomedFaces = true;
                face_status[fi] = ON_UNSET_UINT_INDEX;
              }
            }
          }
          RemoveNgon(ngon_index);
        }
      }
      break;
    
    default:
      break;
    }
  }


  unsigned int point_id_count = 0;
  const unsigned int* point_id_map = nullptr;
  if (bRemoveDegenerateFaces)
  {
    // point_id_map[vi0] == point_id_map[vi1] if and only if m_V[vi0] == m_V[vi1].
    const unsigned int point_count = m_V.UnsignedCount();
    ON_3fPoint* fV = m_V.Array();
    ON_3dPoint* dV = HasDoublePrecisionVertices() ? DoublePrecisionVertices().Array() : 0;
    if (nullptr != dV)
    {
      ON_3dPoint* p1 = dV + point_count;
      const ON_3dPoint badp(ON_DBL_MAX, ON_DBL_MAX, ON_DBL_MAX);
      for (ON_3dPoint* p = dV; p < p1; ++p)
      {
        if (p->IsValid())
          continue;
        *p = badp; // so bad points will sort las
      }
    }
    point_id_count = GetRemoveDegenerateFacesPointMap(point_count, fV, dV, point_id_map_buffer);
    if (point_id_count > 0
      && point_id_count <= point_id_map_buffer.UnsignedCount()
      && point_count == point_id_map_buffer.UnsignedCount()
      )
    {
      point_id_map = point_id_map_buffer.Array();
    }
    else
    {
      point_id_count = 0;
    }
  }

  unsigned int face_count1 = 0;
  {
    const ON_3fPoint* fV = m_V.Array();
    const ON_3dPoint* dV = HasDoublePrecisionVertices() ? DoublePrecisionVertices().Array() : 0;
    for (fi = 0; fi < face_count0; fi++)
    {
      if (0 != face_status[fi])
        continue; // this face status is already known
      
      ON_MeshFace& f0 = m_F[fi];
      fvi = (const unsigned int*)f0.vi;
      for (unsigned int j = 0; j < 4; j++)
      {
        if (fvi[j] >= vertex_count0 || ON_UNSET_UINT_INDEX == vertex_status[fvi[j]])
        {
          bDoomedFaces = true;
          face_status[fi] = ON_UNSET_UINT_INDEX;
          break;
        }
      }
      if (ON_UNSET_UINT_INDEX == face_status[fi])
        continue; // f0 has invalid vertex indices
        
      if (point_id_count > 0)
      {
        // if point_id_count > 0, then bRemoveDegenerateFaces = true.
        // set point_id_map_f.vi[] to values of "topological indices"
        point_id_map_fvi[0] = point_id_map[f0.vi[0]];
        point_id_map_fvi[1] = point_id_map[f0.vi[1]];
        point_id_map_fvi[2] = point_id_map[f0.vi[2]];
        point_id_map_fvi[3] = point_id_map[f0.vi[3]];
        if (false == point_id_map_f.IsValid(point_id_count))
        {
          // point_id_map_f invalid means we have a degenerate quad or worse.

          if (f0.IsQuad() && (point_id_map_f.vi[0] == point_id_map_f.vi[2] || point_id_map_f.vi[1] == point_id_map_f.vi[3]))
          {
            // "L" quads just get deleted.
            bDoomedFaces = true;
            face_status[fi] = ON_UNSET_UINT_INDEX;
            continue;
          }

          // the corners of face f0 are not perfect. We either have to convert a quad to a triangle
          // or we have a degenerate face.
          if ((nullptr != dV) ? f0.Repair(vertex_count0, dV) : f0.Repair(vertex_count0, fV))
          {
            // f0 what an invalid quad fixed to be a valid triangle
            bModifiedFaces = true;
          }
          else
          {
            // face cannot be repaired by juggling vertex indices
            bDoomedFaces = true;
            face_status[fi] = ON_UNSET_UINT_INDEX;
            continue;
          }
        }

        switch (Internal_FaceDegenerateAreaCheck(f0, (int)vertex_count0, fV, dV))
        {
        case 0:
          bDoomedFaces = true;
          face_status[fi] = ON_UNSET_UINT_INDEX;
          break;

        case 1:
          // f0 is totally valid
          break;

        case 2:
          // f0 what an invalid quad fixed to be a valid triangle
          bModifiedFaces = true;
          break;
        }

        if (ON_UNSET_UINT_INDEX == face_status[fi])
          continue;
      }

      face_status[fi] = face_count1++;
      for (unsigned int j = 0; j < 4; j++)
      {
        vertex_status[fvi[j]] = 1; // vertex is referenced by a face
      }
    }
  }

  unsigned int vertex_count1 = 0;
  if ( bRemoveUnusedVertices )
  {
    for ( unsigned int vi = 0; vi < vertex_count0; vi++ )
    {
      if ( 1 == vertex_status[vi] )
        vertex_status[vi] = vertex_count1++; // vertex referenced by a face
      else
        vertex_status[vi] = ON_UNSET_UINT_INDEX; // vertex deleted or not referenced by a face
    }
  }
  else
  {
    for ( unsigned int vi = 0; vi < vertex_count0; vi++ )
    {
      if ( vertex_status[vi] <= 1 )
        vertex_status[vi] = vertex_count1++;
      else
        vertex_status[vi] = ON_UNSET_UINT_INDEX; // vertex explicitly deleted
    }
  }

  if ( 0 == vertex_count1 || 0 == face_count1 )
  {
    Destroy();
    return true;
  }

  if ( vertex_count1 < vertex_count0 || face_count1 < face_count0 )
  {
    DestroyTopology();
    DestroyPartition();
    DestroyTree();

    for ( unsigned int ngon_index = 0; ngon_index < ngon_count0; ngon_index ++ )
    {
      const ON_MeshNgon* ngon = Ngon(ngon_index);
      if ( 0 == ngon || 0 == ngon->m_vi )
        continue;

      if ( face_count1 < face_count0 )
      {
        for ( unsigned int j = 0; j < ngon->m_Fcount; j++ )
        {
          fi = ngon->m_fi[j];
          if ( fi >= face_count0 || ON_UNSET_UINT_INDEX == face_status[fi] )
          {
            bDoomedNgons = true;
            RemoveNgon(ngon_index);
            ngon = 0;
            break;
          }
          ngon->m_fi[j] = face_status[fi];
        }
        if ( 0 == ngon )
          continue;
      }

      if ( vertex_count1 < vertex_count0 )
      {
        for ( unsigned int j = 0; j < ngon->m_Vcount; j++ )
        {
          const unsigned int vi = ngon->m_vi[j];
          if ( vi >= vertex_count0 || ON_UNSET_UINT_INDEX == vertex_status[vi] )
          {
            bDoomedNgons = true;
            RemoveNgon(ngon_index);
            ngon = 0;
            break;
          }
          ngon->m_vi[j] = vertex_status[vi];
        }
      }
    }

    unsigned int* fvi1;
    ON_MeshFace* F = m_F.Array();
    ON_3fVector* FN = HasFaceNormals() ? m_FN.Array() : 0;
    if ( vertex_count1 == vertex_count0 )
    {
      for ( face_count1 = 0; face_count1 < face_count0; face_count1++ )
      {
        if ( ON_UNSET_UINT_INDEX == face_status[face_count1] )
          break;
      }
    }
    else
    {
      face_count1 = 0;
    }
    for ( fi = face_count1; fi < face_count0; fi++ )
    {
      if ( ON_UNSET_UINT_INDEX == face_status[fi] )
        continue;
      fvi = (const unsigned int*)F[fi].vi;
      fvi1 = (unsigned int*)(F[face_count1].vi);
      fvi1[0] = vertex_status[fvi[0]];
      fvi1[1] = vertex_status[fvi[1]];
      fvi1[2] = vertex_status[fvi[2]];
      fvi1[3] = vertex_status[fvi[3]];
      if ( FN )
        FN[face_count1] = FN[fi];
      face_count1++;
    }

    if ( face_count1 < face_count0 )
    {
      m_F.SetCount(face_count1);
      m_F.Shrink();
      if ( FN )
      {
        m_FN.SetCount(face_count1);
        m_FN.Shrink();
      }
    }

    if ( vertex_count1 < vertex_count0 )
    {
      vertex_count1 = 0;
      bool bValidSingles = (VertexUnsignedCount() == m_V.UnsignedCount());
      bool bValidDoubles = (VertexUnsignedCount() == m_dV.UnsignedCount());
      ON_3fPoint* fV = bValidSingles ? m_V.Array() : nullptr;
      ON_3dPoint* dV = bValidDoubles ? m_dV.Array() : nullptr;
      ON_2dPoint* S = HasSurfaceParameters() ? m_S.Array() : 0;
      ON_3fVector* N = HasVertexNormals() ? m_N.Array() : 0;
      ON_2fPoint* T = HasTextureCoordinates() ? m_T.Array() : 0;
      ON_SurfaceCurvature* K = HasPrincipalCurvatures() ? m_K.Array() : 0;
      ON_Color* C = HasVertexColors() ? m_C.Array() : 0;

      for ( vertex_count1 = 0; vertex_count1 < vertex_count0; vertex_count1++ )
      {
        if ( ON_UNSET_UINT_INDEX == vertex_status[vertex_count1] )
          break;
      }

      for ( unsigned int vi = vertex_count1+1; vi < vertex_count0; vi++ )
      {
        if ( ON_UNSET_UINT_INDEX == vertex_status[vi] )
          continue;
        if ( fV )
          fV[vertex_count1] = fV[vi];
        if ( dV )
          dV[vertex_count1] = dV[vi];
        if ( S )
          S[vertex_count1] = S[vi];
        if ( N )
          N[vertex_count1] = N[vi];
        if ( T )
          T[vertex_count1] = T[vi];
        if ( K )
          K[vertex_count1] = K[vi];
        if ( C )
          C[vertex_count1] = C[vi];

        for (int i = 0; i < m_TC.Count(); i++)
        {
          ON_TextureCoordinates& tcs = m_TC[i];
          if (tcs.m_T.Count() == VertexCount())
            tcs.m_T[vertex_count1] = tcs.m_T[vi];
        }

        vertex_count1++;
      }

      if ( fV )
      {
        m_V.SetCount(vertex_count1);
        m_V.Shrink();
      }
      if ( dV )
      {
        m_dV.SetCount(vertex_count1);
        m_dV.Shrink();
      }
      if ( S )
      {
        m_S.SetCount(vertex_count1);
        m_S.Shrink();
      }
      if ( N )
      {
        m_N.SetCount(vertex_count1);
        m_N.Shrink();
      }
      if ( T )
      {
        m_T.SetCount(vertex_count1);
        m_T.Shrink();
      }
      if ( K )
      {
        m_K.SetCount(vertex_count1);
        m_K.Shrink();
      }
      if ( C )
      {
        m_C.SetCount(vertex_count1);
        m_C.Shrink();
      }

      for (int i = 0; i < m_TC.Count(); i++)
      {
        ON_TextureCoordinates& tcs = m_TC[i];
        tcs.m_T.SetCount(vertex_count1);
        tcs.m_T.Shrink();
      }

      InvalidateBoundingBoxes();
    }

    m_invalid_count = 0;
    m_quad_count = 0;
    m_triangle_count = 0;

    SetClosed(-1);
  }
  else if (bModifiedFaces)
  {
    // converted degenerate quads into triangles
    DestroyTopology();
    m_invalid_count = 0;
    m_quad_count = 0;
    m_triangle_count = 0;
    SetClosed(-1);
  }

  if ( bRemoveEmptyNgons )
    RemoveEmptyNgons();

  return true;
}

unsigned int* InitializeMap(unsigned int count,ON_SimpleArray< unsigned int >& map_buffer)
{
  map_buffer.Reserve(count);
  map_buffer.SetCount(count);
  unsigned int* map = map_buffer.Array();
  for ( unsigned int i = 0; i < count; i++ )
    map[i] = ON_UNSET_UINT_INDEX;
  return map;
}

ON_Mesh* ON_Mesh::CopyComponents(
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count,
  class ON_Mesh* destination_mesh
  ) const
{
  if ( ci_count <= 0 || 0 == ci_list )
    return 0;

  const unsigned int vertex_count = m_V.UnsignedCount();
  const unsigned int face_count = m_F.UnsignedCount();

  if ( vertex_count <= 0 && face_count <= 0 )
    return 0;

  const ON_MeshTopology* top = TopologyExists() ? &Topology() : 0;
  const unsigned int topv_count = top ? top->m_topv.UnsignedCount() : 0;
  const unsigned int tope_count = top ? top->m_tope.UnsignedCount() : 0;
  
  ON_SimpleArray< unsigned int > vertex_map_buffer;
  ON_SimpleArray< unsigned int > face_map_buffer;

  unsigned int* vertex_map = 0;
  unsigned int* face_map = 0;
  unsigned int i, fi, vi;

  ON_MeshNgonBuffer ngon_buffer;
  
  for ( size_t ci_index = 0; ci_index < ci_count; ci_index++ )
  {
    ON_COMPONENT_INDEX ci = ci_list[ci_index];
    if ( !ci.IsMeshComponentIndex() )
      continue;
    if ( ci.m_index < 0 )
      continue;
    i = (unsigned int)ci.m_index;

    switch(ci.m_type)
    {
    case ON_COMPONENT_INDEX::mesh_vertex:
      if ( i >= vertex_count )
        break;
      if ( 0 == vertex_map )
        vertex_map = InitializeMap(vertex_count,vertex_map_buffer);
      vertex_map[i] = 0;
      break;

    case ON_COMPONENT_INDEX::mesh_face:
    case ON_COMPONENT_INDEX::mesh_ngon:
      {
        const ON_MeshNgon* ngon = NgonFromComponentIndex(ngon_buffer,ci);
        if ( 0 == ngon )
          break;
        if ( 0 != ngon->m_vi )
        {
          for ( i = 0; i < ngon->m_Vcount; i++ )
          {
            vi = ngon->m_vi[i];
            if ( vi >= vertex_count )
              continue;
            if ( 0 == vertex_map )
              vertex_map = InitializeMap(vertex_count,vertex_map_buffer);
            vertex_map[vi] = 0;
          }
        }
        if ( 0 != ngon->m_fi )
        {
          for ( i = 0; i < ngon->m_Fcount; i++ )
          {
            fi = ngon->m_fi[i];
            if ( fi >= face_count )
              continue;
            if ( 0 == face_map )
              face_map = InitializeMap(face_count,face_map_buffer);
            face_map[fi] = 0;
          }
        }
      }
      break;

    case ON_COMPONENT_INDEX::meshtop_vertex:
      if ( i < topv_count )
      {
        const ON_MeshTopologyVertex& v = top->m_topv[i];
        if ( v.m_vi )
        {
          for ( int j = 0; j < v.m_v_count; j++ )
          {
            if ( v.m_vi[j] < 0 )
              continue;
            vi = (unsigned int)v.m_vi[j];
            if ( vi < vertex_count )
            {
              if ( 0 == vertex_map )
                vertex_map = InitializeMap(vertex_count,vertex_map_buffer);
              vertex_map[vi] = 0;
            }
          }
        }
      }
      break;

    case ON_COMPONENT_INDEX::meshtop_edge:
      if ( i < tope_count )
      {
        const ON_MeshTopologyEdge& e = top->m_tope[i];
        if ( e.m_topfi )
        {
          for ( int j = 0; j < e.m_topf_count; j++ )
          {
            if ( e.m_topfi[j] < 0 )
              continue;
            fi = (unsigned int)e.m_topfi[j];
            if ( fi >= face_count )
              continue;
            if ( 0 == face_map )
              face_map = InitializeMap(face_count,face_map_buffer);
            face_map[fi] = 0;
          }
        }
      }
      break;

    default:
      break;
    }
  }

  unsigned int face_count1 = 0;
  if ( 0 != face_map )
  {
    for ( i = 0; i < face_count; i++ )
    {
      if ( 0 == face_map[i] )
      {
        ON_MeshFace f = m_F[i];
        if ( f.IsValid(vertex_count) )
        {
          face_map[i] = face_count1++;
          if ( 0 == vertex_map )
            vertex_map = InitializeMap(vertex_count,vertex_map_buffer);
          vertex_map[f.vi[0]] = 0;
          vertex_map[f.vi[1]] = 0;
          vertex_map[f.vi[2]] = 0;
          vertex_map[f.vi[3]] = 0;
        }
        else
          face_map[i] = ON_UNSET_UINT_INDEX; // bogus input face
      }
    }
  }

  if ( 0 == vertex_map )
    return 0;

  unsigned int vertex_count1 = 0;
  for ( i = 0; i < vertex_count; i++ )
  {
    if ( 0 == vertex_map[i] )
      vertex_map[i] = vertex_count1++;
  }

  if ( vertex_count1 <= 0 )
    return 0;

  ON_Mesh* mesh_copy = 0;
  if ( destination_mesh )
  {
    destination_mesh->Destroy();
    mesh_copy = destination_mesh;
  }
  else
  {
    mesh_copy = new ON_Mesh();
  }

  if ( face_count1 > 0 )
  {
    // copy face information
    const ON_MeshFace* F = m_F.Array();
    mesh_copy->m_F.Reserve(face_count1);
    const ON_3fVector* FN = HasFaceNormals() ? m_FN.Array() : 0;
    if ( 0 != FN )
      mesh_copy->m_FN.Reserve(face_count1);
    const unsigned int* fvi;
    unsigned int* fvi1;
    for ( fi = 0; fi < face_count; fi++ )
    {
      if ( ON_UNSET_UINT_INDEX == face_map[fi] )
        continue;
      fvi = (const unsigned int*)F[fi].vi;
      fvi1 = (unsigned int*)(mesh_copy->m_F.AppendNew().vi);
      fvi1[0] = vertex_map[fvi[0]];
      fvi1[1] = vertex_map[fvi[1]];
      fvi1[2] = vertex_map[fvi[2]];
      fvi1[3] = vertex_map[fvi[3]];
      if ( FN )
        mesh_copy->m_FN.AppendNew() = FN[fi];
    }
  }

  const bool bValidSingles = (VertexUnsignedCount() == m_V.UnsignedCount());
  const ON_3fPoint* fV = bValidSingles ? m_V.Array() : nullptr;
  const bool bValidDoubles = (VertexUnsignedCount() == m_dV.UnsignedCount());
  const ON_3dPoint* dV = bValidDoubles ? m_dV.Array() : nullptr;
  const ON_2dPoint* S = HasSurfaceParameters() ? m_S.Array() : 0;
  const ON_3fVector* N = HasVertexNormals() ? m_N.Array() : 0;
  const ON_2fPoint* T = HasTextureCoordinates() ? m_T.Array() : 0;
  const ON_SurfaceCurvature* K = HasPrincipalCurvatures() ? m_K.Array() : 0;
  const ON_Color* C = HasVertexColors() ? m_C.Array() : 0;

  if (fV)
    mesh_copy->m_V.Reserve(vertex_count1);
  if (dV)
    mesh_copy->m_dV.Reserve(vertex_count1);
  if (S)
    mesh_copy->m_S.Reserve(vertex_count1);
  if (N)
    mesh_copy->m_N.Reserve(vertex_count1);
  if (T)
    mesh_copy->m_T.Reserve(vertex_count1);
  if (K)
    mesh_copy->m_K.Reserve(vertex_count1);
  if (C)
    mesh_copy->m_C.Reserve(vertex_count1);

  for ( vi = 0; vi < vertex_count; vi++ )
  {
    if ( ON_UNSET_UINT_INDEX == vertex_map[vi] )
      continue;
    if (fV)
      mesh_copy->m_V.AppendNew() = fV[vi];
    if (dV)
      mesh_copy->m_dV.AppendNew() = dV[vi];
    if ( S )
      mesh_copy->m_S.AppendNew() = S[vi];
    if ( N )
      mesh_copy->m_N.AppendNew() = N[vi];
    if ( T )
      mesh_copy->m_T.AppendNew() = T[vi];
    if ( K )
      mesh_copy->m_K.AppendNew() = K[vi];
    if ( C )
      mesh_copy->m_C.AppendNew() = C[vi];
  }

  const unsigned int ngon_count = NgonCount();
  for ( unsigned int ngon_index = 0; ngon_index < ngon_count; ngon_index++ )
  {
    const ON_MeshNgon* ngon = Ngon(ngon_index);
    if ( 0 == ngon )
      continue;
    if ( 0 == ngon->m_Vcount || 0 == ngon->m_vi )
      continue;
    if ( 0 == ngon->m_Fcount || 0 == ngon->m_fi )
      continue;
    
    unsigned int j;
    
    for ( j = 0; j < ngon->m_Vcount; j++ )
    {
      vi = ngon->m_vi[j];
      if ( vi >= vertex_count )
        break;
      if ( ON_UNSET_UINT_INDEX == vertex_map[vi] )
        break;
    }
    if ( j < ngon->m_Vcount )
      continue;

    for ( j = 0; j < ngon->m_Fcount; j++ )
    {
      fi = ngon->m_fi[j];
      if ( fi >= face_count )
        break;
      if ( ON_UNSET_UINT_INDEX == face_map[fi] )
        break;
    }
    if ( j < ngon->m_Fcount )
      continue;

    ON_MeshNgon* ngon1 = mesh_copy->AllocateNgon(ngon->m_Vcount,ngon->m_Fcount);

    ngon1->m_Vcount = 0;
    ngon1->m_Fcount = 0;
    for ( j = 0; j < ngon->m_Vcount; j++ )
    {
      ngon1->m_vi[ngon1->m_Vcount++] = vertex_map[ngon->m_vi[j]];
    }
    for ( j = 0; j < ngon->m_Fcount; j++ )
    {
      ngon1->m_fi[ngon1->m_Fcount++] = face_map[ngon->m_fi[j]];
    }

    mesh_copy->AddNgon(ngon1);

    if ( 0 != NgonMap() )
      mesh_copy->CreateNgonMap();
  }

  return mesh_copy;
}

ON_Mesh* ON_Mesh::CopyComponents(
  const ON_SimpleArray<ON_COMPONENT_INDEX>& ci_list,
  class ON_Mesh* destination_mesh
  ) const
{
  return CopyComponents(ci_list.Array(), ci_list.UnsignedCount(), destination_mesh);
}

bool ON_Mesh::SetSurfaceParametersFromTextureCoodinates(const ON_SimpleArray<ON_2fPoint>& TCs)
{
  unsigned int i;
  const unsigned int vcount = m_V.UnsignedCount();

  bool rc;
  ON_Interval dom;
  if (vcount == TCs.UnsignedCount())
  {
    dom.Set(0.0, 1.0);
    m_S.SetCount(0);
    m_S.Reserve(vcount);
    for (i = 0; i < vcount; i++)
    {
      ON_2dPoint S = TCs[i];
      m_S.Append(S);
    }
    rc = true;
  }
  else
  {
    dom = ON_Interval::EmptyInterval;
    m_S.Destroy();
    rc = false;
  }

  m_srf_domain[0] = dom;
  m_srf_domain[1] = dom;
  m_srf_scale[0] = 0.0;
  m_srf_scale[1] = 0.0;
  m_packed_tex_domain[0] = dom;
  m_packed_tex_domain[1] = dom;
  m_packed_tex_rotate = false;

  return rc;

  //bool rc = (vcount > 0 && vcount == m_T.UnsignedCount() && vcount != m_S.UnsignedCount());
  //if (!rc)
  //  return false;
  //  
  //ON_2dPoint Tmin = m_T[0];
  //ON_2dPoint Tmax = m_T[0];
  //ON_2dPoint T;
  //for (i = 1; i < vcount; i++)
  //{
  //  T = m_T[i];
  //  if (T.x < Tmin.x)
  //    Tmin.x = T.x;
  //  else if (T.x > Tmax.x)
  //    Tmax.x = T.x;
  //  if (T.y < Tmin.y)
  //    Tmin.y = T.y;
  //  else if (T.y > Tmax.y)
  //    Tmax.y = T.y;
  //}
  //  
  //rc = (0.0f <= Tmin.x && Tmax.x <= 1.0f && 0.0f <= Tmin.y && Tmax.y <= 1.0f);
  //if (!rc)
  //  return false;

  //ON_Interval packed_tex_domain[2];
  //packed_tex_domain[0] = m_packed_tex_domain[0];
  //packed_tex_domain[1] = m_packed_tex_domain[1];
  //const float Ttol = 1.0e-5f;

  //if (packed_tex_domain[0].IsIncreasing() && packed_tex_domain[1].IsIncreasing())
  //{
  //  rc = (packed_tex_domain[0].IsIncreasing() && packed_tex_domain[1].IsIncreasing());
  //  if (!rc)
  //    return false;
  //  rc = (packed_tex_domain[0][0] <= Tmin.x && Tmax.x <= packed_tex_domain[0][1]);
  //  if (!rc)
  //    return false;
  //  rc = (packed_tex_domain[1][0] <= Tmin.y && Tmax.y <= packed_tex_domain[1][1]);
  //  if (!rc)
  //    return false;
  //}
  //else if (Tmin.x > Ttol || Tmax.x < 1.0 - Ttol || Tmin.y > Ttol || Tmax.y < 1.0 - Ttol)
  //{
  //  packed_tex_domain[0].Set(Tmin.x, Tmax.x);
  //  packed_tex_domain[1].Set(Tmin.y, Tmax.y);
  //}
  //else
  //{
  //  packed_tex_domain[0].Set(0.0, 1.0);
  //  packed_tex_domain[1].Set(0.0, 1.0);
  //}

  //ON_Interval Sdomain[2];
  //if (m_packed_tex_rotate)
  //{
  //  Sdomain[0] = packed_tex_domain[1];
  //  Sdomain[1].Set(1.0 - packed_tex_domain[0][1], 1.0 - packed_tex_domain[0][0]);
  //}
  //else
  //{
  //  Sdomain[0] = packed_tex_domain[0];
  //  Sdomain[1] = packed_tex_domain[1];
  //}

  //rc = Sdomain[0].IsIncreasing() && Sdomain[1].IsIncreasing();
  //if (!rc)
  //  return false;

  //m_packed_tex_domain[0] = packed_tex_domain[0];
  //m_packed_tex_domain[1] = packed_tex_domain[1];
  //m_srf_scale[0] = 0.0;
  //m_srf_scale[1] = 0.0;
  //m_srf_domain[0] = Sdomain[0];
  //m_srf_domain[1] = Sdomain[1];

  //m_S.Reserve(vcount);
  //m_S.SetCount(0);
  //ON_2dPoint S;
  //if (m_packed_tex_rotate)
  //{
  //  for (i = 0; i < vcount; i++)
  //  {
  //    T = m_T[i];
  //    double x = m_packed_tex_domain[0].NormalizedParameterAt(T.x);
  //    double y = m_packed_tex_domain[1].NormalizedParameterAt(T.y);
  //    S.x = m_srf_domain[0].ParameterAt(y);
  //    S.y = m_srf_domain[1].ParameterAt(1.0 - x);
  //    S = T;
  //    m_S.Append(S);
  //  }
  //}
  //else
  //{
  //  for (i = 0; i < vcount; i++)
  //  { 
  //    T = m_T[i];
  //    S = T;
  //    m_S.Append(S);
  //  }
  //}

  //return true;
}

bool ON_Mesh::SetSurfaceParamtersFromTextureCoodinates()
{
  return SetSurfaceParametersFromTextureCoodinates(m_T);
}


//////////////////////////////////////////////////////////////////////////
//
// ON_MeshCache
//

class ON_MeshCacheItem
{
public:
  ON_MeshCacheItem() = default;
  ~ON_MeshCacheItem() = default;
  ON_MeshCacheItem(const ON_MeshCacheItem&) = default;
  ON_MeshCacheItem& operator=(const ON_MeshCacheItem&) = default;

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_MeshCacheItem( ON_MeshCacheItem&& ) ON_NOEXCEPT;
  // rvalue assignment operator
  ON_MeshCacheItem& operator=( ON_MeshCacheItem&& );
#endif


  bool Write(
    ON_BinaryArchive& archive
    ) const;

  bool Read(
    ON_BinaryArchive& archive
    );

  void Dump(
    ON_TextLog& text_log
    ) const;

public:
  ON_UUID m_mesh_id = ON_nil_uuid;
  std::shared_ptr<ON_Mesh> m_mesh_sp;
  ON_MeshCacheItem* m_next = nullptr;
};

#if defined(ON_HAS_RVALUEREF)

ON_MeshCacheItem::ON_MeshCacheItem( ON_MeshCacheItem&& src ) ON_NOEXCEPT
  : m_mesh_id(src.m_mesh_id)
  , m_mesh_sp(std::move(src.m_mesh_sp))
{

}

ON_MeshCacheItem& ON_MeshCacheItem::operator=( ON_MeshCacheItem&& src )
{
  std::move(src.m_mesh_sp).swap(m_mesh_sp);
  m_mesh_id = src.m_mesh_id;
  return *this;
}

#endif


bool ON_MeshCacheItem::Write(
  ON_BinaryArchive& archive
  ) const
{
  const ON_Mesh* mesh = m_mesh_sp.get();
  if (nullptr == mesh)
    return true; // not an error

  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0))
    return false;

  bool rc = false;
  for (;;)
  {
    if (!archive.WriteUuid(m_mesh_id))
      break;
    if ( !archive.WriteObject(mesh) )
      break;
    rc = true;
    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_MeshCacheItem::Read(
  ON_BinaryArchive& archive
  )
{
  m_mesh_id = ON_nil_uuid;
  m_mesh_sp.reset();

  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if ( 1 != major_version )
      break;

    if (!archive.ReadUuid(m_mesh_id))
      break;

    ON_Object* mesh_object = nullptr;
    if ( !archive.ReadObject(&mesh_object) )
      break;
    if ( nullptr == mesh_object )
      break;
    ON_Mesh* mesh = ON_Mesh::Cast(mesh_object);
    if (nullptr == mesh)
    {
      delete mesh_object;
      break;
    }
    std::shared_ptr<ON_Mesh>(mesh).swap(m_mesh_sp);
    rc = true;
    break;
  }

  if (!archive.EndRead3dmChunk())
    rc = false;

  return rc;
}


void ON_MeshCacheItem::Dump(
  ON_TextLog& text_log
  ) const
{
  const char* description = nullptr;
  if ( ON_MeshCache::RenderMeshId == m_mesh_id )
    description = "Render Mesh";
  else if ( ON_MeshCache::AnalysisMeshId == m_mesh_id )
    description = "Analysis Mesh";
  else if ( ON_MeshCache::PreviewMeshId == m_mesh_id )
    description = "Preview Mesh";

  if (nullptr != description)
  {
    text_log.Print("%s\n", description);
  }
  else
  {
    char buffer[48] = { 0 };
    ON_UuidToString(m_mesh_id, buffer);
    text_log.Print("mesh id: %s\n",buffer);
  }

  text_log.PushIndent();
  const ON_Mesh* mesh = m_mesh_sp.get();
  if (nullptr == mesh)
    text_log.Print("Null mesh\n");
  else if (mesh->IsEmpty())
    text_log.Print("Empty mesh\n");
  else
  {
    const char* mp_style = "Custom";
    const ON_MeshParameters* mp = mesh->MeshParameters();
    if (mp)
    {
      if (0 == ON_MeshParameters::CompareGeometrySettings(*mp, ON_MeshParameters::FastRenderMesh))
        mp_style = "Fast";
      else if (0 == ON_MeshParameters::CompareGeometrySettings(*mp, ON_MeshParameters::QualityRenderMesh))
        mp_style = "Quality";
    }
    text_log.Print("%s mesh with %d faces and %d vertices.\n", mp_style, mesh->FaceCount(), mesh->VertexCount());
  }
  text_log.PopIndent();
}

ON_UUID ON_MeshCache::MeshIdFromMeshType(
  ON::mesh_type mesh_type
  )
{
  switch (mesh_type)
  {
  case ON::default_mesh:
    return ON_MeshCache::CoarseMeshId;
    break;
  case ON::render_mesh:
    return ON_MeshCache::RenderMeshId;
    break;
  case ON::analysis_mesh:
    return ON_MeshCache::AnalysisMeshId;
    break;
  case ON::preview_mesh:
    return ON_MeshCache::PreviewMeshId;
    break;
  case ON::any_mesh:
    return ON_MeshCache::AnyMeshId;
    break;
  default:
    break;
  }

  return ON_nil_uuid;
}


class ON_MeshCacheItem* ON_MeshCache::Internal_CreateItem()
{
  // Items must come from the main memory pool to prevent
  // crashing when meshing operations are canceled.
  // Use placement operator new with main heap memory.
  ON_MeshCacheItem* item;
  void* p = onmalloc(sizeof(*item));
  item = new (p) ON_MeshCacheItem();
  return item;
}

class ON_MeshCacheItem* ON_MeshCache::Internal_CopyItem(const class ON_MeshCacheItem& src_item)
{
  // Items must come from the main memory pool to prevent
  // crashing when meshing operations are canceled.
  // Use placement operator new with main heap memory.
  ON_MeshCacheItem* item;
  void* p = onmalloc(sizeof(*item));
  item = new (p) ON_MeshCacheItem(src_item);
  item->m_next = nullptr;
  return item;
}

void ON_MeshCache::Internal_DeleteItem(class ON_MeshCacheItem* item, bool bDeleteMesh)
{
  if (nullptr == item)
    return;
  void* p = (void*)item;

  // When bDeleteMesh is false, the memory used by item->m_mesh_sp and the ON_Mesh
  // it points to belongs to a memory pool that has been deleted because a worker
  // thread was canceled.  In this case, calling ~ON_MeshCacheItem() will crash the
  // application.
  if ( bDeleteMesh )
  {
    item->~ON_MeshCacheItem();
  }

  onfree(p);
}

void ON_MeshCache::Internal_CopyHelper(
  const class ON_MeshCacheItem* src_impl
  )
{
  m_impl = 0;
  ON_MeshCacheItem* prev = nullptr;
  for (const ON_MeshCacheItem* src_item = src_impl; nullptr != src_item; src_item = src_item->m_next)
  {
    ON_MeshCacheItem* item_copy = Internal_CopyItem(*src_item);
    if (nullptr == prev)
      m_impl = item_copy;
    else
      prev->m_next = item_copy;
    prev = item_copy;
  }
}

class ON_MeshCacheItem* ON_MeshCache::Internal_FindHelper(
  ON_UUID mesh_id
  ) const
{
  unsigned int coarse_mesh_face_count = 0xFFFFFFFFU;
  unsigned int fine_mesh_face_count = 0;
  ON_MeshCacheItem* item_coarse_mesh = nullptr;
  ON_MeshCacheItem* item_fine_mesh = nullptr;

  const bool bCountFaces = (ON_MeshCache::FineMeshId == mesh_id || ON_MeshCache::CoarseMeshId == mesh_id);

  for (ON_MeshCacheItem* item = m_impl; nullptr != item; item = item->m_next)
  {
    if (mesh_id == item->m_mesh_id)
      return item;
    if (false == bCountFaces)
      continue;
    const ON_Mesh* mesh = item->m_mesh_sp.get();
    if (nullptr == mesh)
      continue;
    unsigned int mesh_face_count = mesh->FaceUnsignedCount();
    if (mesh_face_count <= 0 || mesh->VertexUnsignedCount() < 3)
      continue;
    if (mesh_face_count > fine_mesh_face_count)
    {
      item_fine_mesh = item;
      fine_mesh_face_count = mesh_face_count;
    }
    if (mesh_face_count < coarse_mesh_face_count)
    {
      item_coarse_mesh = item;
      coarse_mesh_face_count = mesh_face_count;
    }
  }
  
  if (ON_MeshCache::CoarseMeshId == mesh_id)
    return item_coarse_mesh;
  
  if (ON_MeshCache::FineMeshId == mesh_id)
    return item_fine_mesh;

  return nullptr;
}

ON_MeshCache::~ON_MeshCache()
{
  ClearAllMeshes();
}

ON_MeshCache::ON_MeshCache(const ON_MeshCache& src)
{
  Internal_CopyHelper(src.m_impl);
}

ON_MeshCache& ON_MeshCache::operator=(const ON_MeshCache& src)
{
  if (this != &src)
  {
    ClearAllMeshes();
    Internal_CopyHelper(src.m_impl);
  }
  return *this;
}

#if defined(ON_HAS_RVALUEREF)
// rvalue copy constructor
ON_MeshCache::ON_MeshCache( ON_MeshCache&& src) ON_NOEXCEPT
{
  m_impl = src.m_impl;
  src.m_impl = nullptr;
}

ON_MeshCache& ON_MeshCache::operator=( ON_MeshCache&& src )
{
  if (this != &src)
  {
    m_impl = src.m_impl;
    src.m_impl = nullptr;
  }
  return *this;
}

#endif


void ON_MeshCache::SetMesh(
  ON::mesh_type mesh_type,
  const std::shared_ptr<ON_Mesh>& mesh_sp
  )
{
  SetMesh(ON_MeshCache::MeshIdFromMeshType(mesh_type),mesh_sp);
}

void ON_MeshCache::SetMesh(
  ON_UUID mesh_id,
  const std::shared_ptr<ON_Mesh>& mesh_sp
  )
{
  if ( ON_nil_uuid == mesh_id )
    return;
  if ( ON_max_uuid == mesh_id )
    return;

  const ON_Mesh* mesh = mesh_sp.get();

  if (nullptr == mesh || mesh->IsEmpty())
  {
    ClearMesh(mesh_id);
    return;
  }

  if ( ON_MeshCache::AnyMeshId == mesh_id )
    return;

  ON_MeshCacheItem* item = Internal_FindHelper(mesh_id);
  if (nullptr == item)
  {
    item = Internal_CreateItem();
    item->m_mesh_id = mesh_id;
    item->m_next = m_impl;
    m_impl = item;
  }
  if ( nullptr == item )
    return;

  item->m_mesh_sp = mesh_sp;
}
  
void ON_MeshCache::ClearMesh(
  ON::mesh_type mesh_type
  )
{
  ClearMesh(mesh_type, true);
}
  
void ON_MeshCache::ClearMesh(
  ON::mesh_type mesh_type,
  bool bDeleteMesh
  )
{
  ClearMesh(ON_MeshCache::MeshIdFromMeshType(mesh_type),bDeleteMesh);
}

void ON_MeshCache::ClearMesh(
  ON_UUID mesh_id
  )
{
  ClearMesh(mesh_id, true);
}  

void ON_MeshCache::ClearMesh(
  ON_UUID mesh_id,
  bool bDeleteMesh
  )
{
  if (ON_MeshCache::AnyMeshId == mesh_id)
    ClearAllMeshes(bDeleteMesh);
  else
  {
    ON_MeshCacheItem* prev = nullptr;
    for (ON_MeshCacheItem* item = m_impl; nullptr != item; item = item->m_next)
    {
      if (mesh_id == item->m_mesh_id)
      {
        if ( nullptr == prev )
          m_impl = item->m_next;
        else
          prev->m_next = item->m_next;
        Internal_DeleteItem(item,bDeleteMesh);
        return;
      }
      prev = item;
    }
  }
}  

void ON_MeshCache::ClearAllMeshes()
{
  ClearAllMeshes(true);
}

void ON_MeshCache::ClearAllMeshes(bool bDeleteMesh)
{
  if ( 0 != m_impl )
  {
    ON_MeshCacheItem* next = m_impl;
    m_impl = nullptr;
    for (ON_MeshCacheItem* item = next; nullptr != item; item = next)
    {
      next = item->m_next;
      Internal_DeleteItem(item,bDeleteMesh);
    }
  }
}
  
const ON_Mesh* ON_MeshCache::Mesh(
  ON::mesh_type mesh_type
  ) const
{
  return Mesh(ON_MeshCache::MeshIdFromMeshType(mesh_type));
}
  
const ON_Mesh* ON_MeshCache::Mesh(
  ON_UUID mesh_id
  ) const
{
  return MeshSharedPtr(mesh_id).get();
}

std::shared_ptr<ON_Mesh> ON_MeshCache::MeshSharedPtr(
  ON::mesh_type mesh_type
  ) const
{
  return MeshSharedPtr(ON_MeshCache::MeshIdFromMeshType(mesh_type));
}

std::shared_ptr<ON_Mesh> ON_MeshCache::MeshSharedPtr(
  ON_UUID mesh_id
  ) const
{
  const ON_MeshCacheItem* item 
    = (ON_MeshCache::AnyMeshId == mesh_id)
    ? m_impl
    : Internal_FindHelper(mesh_id);
  if ( item )
    return item->m_mesh_sp;
  return std::shared_ptr<ON_Mesh>();
}

bool ON_MeshCache::Write(
  ON_BinaryArchive& archive
  ) const
{
  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0))
    return false;
  bool rc = true;
  char c;
  for (const ON_MeshCacheItem* item = m_impl; nullptr != item; item = item->m_next)
  {
    c = 1;
    rc = archive.WriteChar(c);
    if ( false == rc )
      break;
    rc = item->Write(archive);
    if ( false == rc )
      break;
  }
  if (rc)
  {
    c = 0;
    rc = archive.WriteChar(c);
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_MeshCache::Read(
  ON_BinaryArchive& archive
  )
{
  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (1 != major_version)
      break;
    ON_MeshCacheItem* prev = nullptr;

    for (;;)
    {
      char c = 0;
      if (!archive.ReadChar(&c))
        break;
      if (0 == c)
      {
        rc = true;
        break;
      }
      if (1 != c)
        break;
      ON_MeshCacheItem* item = Internal_CreateItem();
      if (!item->Read(archive))
      {
        Internal_DeleteItem(item,true);
        break;
      }
      if (nullptr == prev)
        m_impl = item;
      else
        prev->m_next = item;
      prev = item;
    }
    break;
  }

  if (!archive.EndRead3dmChunk())
    rc = false;

  return rc;
}

unsigned int ON_MeshCache::MeshCount() const
{
  unsigned int count = 0;
  for (const ON_MeshCacheItem* item = m_impl; nullptr != item; item = item->m_next)
  {
    count++;
  }
  return count;
}

void ON_MeshCache::Dump(
  ON_TextLog& text_log
  ) const
{
  unsigned int count = MeshCount();
  text_log.Print("%u cached meshes.\n",count);
  for (const ON_MeshCacheItem* item = m_impl; nullptr != item; item = item->m_next)
  {
    item->Dump(text_log);
  }
}

bool ON_MeshCache::Transform(
  const ON_Xform& xform
  )
{
  if (!xform.IsValid())
    return false;
  if (xform.IsZero())
    return false;
  if (xform.IsIdentity())
    return true;
  bool rc = true;
  for (ON_MeshCacheItem* item = m_impl; nullptr != item; item = item->m_next)
  {
    ON_Mesh* mesh = item->m_mesh_sp.get();
    if (nullptr == mesh || mesh->IsEmpty())
      continue;
    // NOTE: use_count() == 1 is an approximation in multi-threaded environments
    // https:// en.cppreference.com/w/cpp/memory/shared_ptr/unique
    if (item->m_mesh_sp.use_count() != 1)
    {
      // make a copy and transform the copy
      std::shared_ptr<ON_Mesh>(new ON_Mesh(*mesh)).swap(item->m_mesh_sp);
      mesh = item->m_mesh_sp.get();
    }
    if ( !mesh->Transform(xform) )
      rc = false;
  }
  return rc;
}

//////////////////////////////////////////////////////////////////////////
//
// ON_MeshRef
//

ON_MeshRef::ON_MeshRef() ON_NOEXCEPT
{}

ON_MeshRef::~ON_MeshRef()
{
  m_mesh_sp.reset();
}

ON_MeshRef::ON_MeshRef(const ON_MeshRef& src) ON_NOEXCEPT
  : m_mesh_sp(src.m_mesh_sp)
{}

ON_MeshRef& ON_MeshRef::operator=(const ON_MeshRef& src)
{
  if ( this != &src )
    m_mesh_sp = src.m_mesh_sp;
  return *this;
}

#if defined(ON_HAS_RVALUEREF)
// rvalue copy constructor
ON_MeshRef::ON_MeshRef( ON_MeshRef&& src) ON_NOEXCEPT
  : m_mesh_sp(std::move(src.m_mesh_sp))
{}

// rvalue assignment operator
ON_MeshRef& ON_MeshRef::operator=(ON_MeshRef&& src)
{
  m_mesh_sp.reset();
  m_mesh_sp = std::move(src.m_mesh_sp);
  return *this;
}
#endif

bool ON_MeshRef::IsEmpty() const
{
  const ON_Mesh* mesh = m_mesh_sp.get();
  return (nullptr == mesh);
}

bool ON_MeshRef::IsNotEmpty() const
{
  return (false == IsEmpty());
}

const class ON_Mesh& ON_MeshRef::Mesh() const
{
  const ON_Mesh* mesh = m_mesh_sp.get();
  if ( nullptr == mesh )
    mesh = &ON_Mesh::Empty;
  return *mesh;
}

unsigned int ON_MeshRef::ReferenceCount() const
{
  return (unsigned int)m_mesh_sp.use_count();
}

void ON_MeshRef::Clear()
{
  m_mesh_sp.reset();
}

class ON_Mesh& ON_MeshRef::NewMesh()
{
  ON_Mesh* mesh = new ON_Mesh();
  ON_Mesh* managed_mesh = SetMeshForExperts(mesh);
  return *managed_mesh;
}

class ON_Mesh& ON_MeshRef::CopyMesh(
  const ON_MeshRef& src
  )
{
  return CopyMesh(src.Mesh());
}

class ON_Mesh& ON_MeshRef::CopyMesh(
  const ON_Mesh& src
  )
{
  ON_Mesh* mesh_copy = new ON_Mesh(src);
  ON_Mesh* managed_mesh = SetMeshForExperts(mesh_copy);
  return *managed_mesh;
}

class ON_Mesh& ON_MeshRef::UniqueMesh()
{
  const ON_Mesh& mesh = Mesh();
  if (m_mesh_sp.use_count() > 1 )
    return CopyMesh(mesh);
  return const_cast< ON_Mesh& >(mesh);
}

const std::shared_ptr<class ON_Mesh>& ON_MeshRef::SharedMesh() const
{
  return m_mesh_sp;
}

class ON_Mesh* ON_MeshRef::SetMeshForExperts(
  class ON_Mesh*& mesh
  )
{
  Clear();
  ON_Mesh* managed_mesh = ( mesh == &ON_Mesh::Empty ) ? nullptr : mesh;
  mesh = nullptr;
  if (nullptr != managed_mesh )
    m_mesh_sp = std::shared_ptr<class ON_Mesh>(managed_mesh);
  return managed_mesh;
}



unsigned int ON_Mesh::DissolveOrDelete(
  const ON_SimpleArray<ON_COMPONENT_INDEX>& ci_list
)
{
  // Dissolve edges and vertices, delete faces
  const unsigned int bailout_rc = ON_UNSET_UINT_INDEX;

  const int ci_list_count = ci_list.UnsignedCount();
  if (ci_list_count <= 0)
    return bailout_rc;


  const int mesh0_vertex_count = this->VertexCount();
  if (mesh0_vertex_count < 3)
    return bailout_rc;
  const int mesh0_face_count = this->FaceCount();
  if (mesh0_face_count < 1)
    return bailout_rc;

  const ON_MeshTopology& top0 = Topology();
  const int top0_vertex_count = top0.m_topv.Count();


  ON_SimpleArray<ON_COMPONENT_INDEX> faces(ci_list_count);
  ON_SimpleArray<ON_COMPONENT_INDEX> edges_and_vertices(ci_list_count);
  ON_SimpleArray<ON_2dex> edges(ci_list_count);

  for (int i = 0; i < ci_list_count; ++i)
  {
    ON_COMPONENT_INDEX ci = ci_list[i];
    if (ci.m_index < 0)
      continue;
    switch (ci.m_type)
    {
    case ON_COMPONENT_INDEX::TYPE::mesh_vertex:
      if ( ci.m_index < mesh0_vertex_count)
        edges_and_vertices.Append(ci);
      break;

    case ON_COMPONENT_INDEX::TYPE::meshtop_vertex:
      // must save input top vertex as an ordinary vertex index
      // because input topology indices will be changed if faces are deleted.
      if (ci.m_index < top0_vertex_count)
      {
        const ON_MeshTopologyVertex& v = top0.m_topv[ci.m_index];
        if (v.m_v_count > 0 && nullptr != v.m_vi)
        {
          ON_COMPONENT_INDEX vci(ON_COMPONENT_INDEX::TYPE::mesh_vertex, v.m_vi[0]);
          if ( vci.m_index >= 0 && vci.m_index < mesh0_vertex_count)
            edges_and_vertices.Append(vci);
        }
      }
      break;

    case ON_COMPONENT_INDEX::TYPE::meshtop_edge:
      // must save input edge as a pair of ordinary vertex indices
      // because input topology indices will be changed if faces are deleted.
      if ( ci.m_index < top0.m_tope.Count())
      {
        const ON_MeshTopologyEdge& e = top0.m_tope[ci.m_index];
        ON_2dex evdex(-1, -1);
        int* evi = &evdex.i;
        for (int j = 0; j < 2; j++)
        {
          if (e.m_topvi[j] < 0 || e.m_topvi[j] >= top0_vertex_count)
            break;
          const ON_MeshTopologyVertex& v = top0.m_topv[e.m_topvi[j]];
          if (v.m_v_count > 0 && nullptr != v.m_vi)
            evi[j] = v.m_vi[0];
        }
        if (evdex.i > evdex.j)
        {
          const int x = evdex.i;
          evdex.i = evdex.j;
          evdex.j = x;
        }
        if (0 <= evdex.i && evdex.i < evdex.j && evdex.j < mesh0_vertex_count)
          edges.Append(evdex);
      }
      break;

    case ON_COMPONENT_INDEX::TYPE::mesh_face:
      faces.Append(ci);
      break;

    case ON_COMPONENT_INDEX::TYPE::mesh_ngon:
      {
        // must convert ngon to a bucnh of face indices
        const ON_MeshNgon* ngon = this->Ngon(ci.m_index);
        if (nullptr == ngon || nullptr == ngon->m_fi)
          break;
        ON_COMPONENT_INDEX fci(ON_COMPONENT_INDEX::TYPE::mesh_face, -1);
        for (unsigned nfi = 0; nfi < ngon->m_Fcount; ++nfi)
        {
          fci.m_index = ngon->m_fi[nfi];
          if ( fci.m_index < mesh0_face_count)
            faces.Append(fci);
        }
      }
      break;
            
    default:
      break;
    };
  }


  // delete the faces in a way that does not change ordinary vertex indices
  DeleteComponents(
    faces.Array(),
    faces.UnsignedCount(),
    true, // bIgnoreInvalidComponents,
    true, // bRemoveDegenerateFaces,
    false, // bRemoveUnusedVertices CRITICAL to preserve vertex index values
    true, // bRemoveEmptyNgons,
    nullptr // unsigned int* faceMap
  );

  if (FaceCount() <= 0)
  {
    Destroy();
    return bailout_rc;
  }

  if (mesh0_vertex_count != VertexCount())
    return bailout_rc; // vertex array was modified

  if (edges.Count() > 0 || edges_and_vertices.Count() > 0)
  {
    // convert ordinary vertex indices into top1 indices
    const ON_MeshTopology& top1 = Topology();
    const int top1_vertex_count = top1.m_topv.Count();
    const int top1_edge_count = top1.m_tope.Count();
    if (mesh0_vertex_count == top1.m_topv_map.Count())
    {
      // get a clean list of top1.m_topv[] indices
      int vertex_count = 0;
      for (int i = 0; i < edges_and_vertices.Count(); ++i)
      {
        ON_COMPONENT_INDEX ci = edges_and_vertices[i];
        ci.m_type = ON_COMPONENT_INDEX::TYPE::meshtop_vertex;
        ci.m_index = top1.m_topv_map[ci.m_index];
        if (ci.m_index >= 0 && ci.m_index < top1_vertex_count)
          edges_and_vertices[vertex_count++] = ci;
      }
      edges_and_vertices.SetCount(vertex_count);
      edges_and_vertices.QuickSortAndRemoveDuplicates(ON_COMPONENT_INDEX::Compare);
      vertex_count = edges_and_vertices.Count();

      // now add edges to edges_and_vertices[]
      ON_COMPONENT_INDEX eci(ON_COMPONENT_INDEX::TYPE::meshtop_edge, -1);
      for (int i = 0; i < edges.Count(); i++)
      {
        ON_2dex evi = edges[i];
        const int topv[2] = { top1.m_topv_map[evi.i],top1.m_topv_map[evi.j] };
        if (
          topv[0] != topv[1]
          && topv[0] >= 0 && topv[0] < top1_vertex_count
          && topv[1] >= 0 && topv[1] < top1_vertex_count
          )
        {
          const ON_MeshTopologyVertex& v0 = top1.m_topv[topv[0]];
          if ( v0.m_tope_count > 0 && nullptr != v0.m_topei )
          {
            // find the edge connecting the two vertices
            for (int k = 0; k < v0.m_tope_count; ++k)
            {
              eci.m_index = v0.m_topei[k];
              if (eci.m_index >= 0 && eci.m_index < top1_edge_count)
              {
                const ON_MeshTopologyEdge& e = top1.m_tope[eci.m_index];
                if (
                  (e.m_topvi[0] == topv[0] && e.m_topvi[1] == topv[1])
                  || (e.m_topvi[0] == topv[1] && e.m_topvi[1] == topv[0]))
                {
                  edges_and_vertices.Append(eci);
                }
              }
            }
          }
        }
      }
    }
  }

  // dissolve the edges and vertices by merging faces
  unsigned int rc 
    = (edges_and_vertices.Count() > 0)
    ? MergeFaceSets(edges_and_vertices)
    : bailout_rc;

  // Finally, we can remove unused vertices.
  DeleteComponents(
    nullptr,
    0,
    true, // bIgnoreInvalidComponents,
    true, // bRemoveDegenerateFaces,
    true, // bRemoveUnusedVertices,
    true, // bRemoveEmptyNgons,
    nullptr // unsigned int* faceMap
  );

  return rc;
}

static void Internal_WeldNgonCandiate(
  const ON_Mesh& mesh,
  const ON_MeshTopology& top,
  unsigned char* fmarks,
  const unsigned char xmark,
  const ON_SimpleArray<unsigned>& ngon_fi
)
{
  const unsigned ngon_face_count = ngon_fi.UnsignedCount();
  if (ngon_face_count < 2)
    return;

  // Assumption fmarks[] has no xmark.
  // Set xmark for all faces referenced in ngon_fi[] and
  // use that mark to find interior vertices that need
  // to be welded before the ngon can be created.
  for (unsigned nfi = 0; nfi < ngon_face_count; ++nfi)
    fmarks[ngon_fi[nfi]] |= xmark;

  for (unsigned nfi = 0; nfi < ngon_face_count; ++nfi)
  {
    const int fi = ngon_fi[nfi];
    const ON_MeshTopologyFace& f = top.m_topf[fi];
    const int fv_count = f.IsTriangle() ? 3 : 4;
    int* fvi = const_cast<int*>( mesh.m_F[fi].vi );
    for (int fei = 0; fei < fv_count; ++fei)
    {
      const int evi = (0 == f.m_reve[fei]) ? 1 : 0;
      const ON_MeshTopologyEdge& fe = top.m_tope[f.m_topei[fei]];
      const int topvi = fe.m_topvi[evi];
      const ON_MeshTopologyVertex& v = top.m_topv[topvi];
      if (v.m_v_count <= 1 || nullptr == v.m_vi)
        continue;
      int mesh_vi[2] = { fvi[fei],fvi[fei] };
      for (int pass = 0; pass < 2; ++pass)
      {
        for (int vei = 0; vei < v.m_v_count; ++vei)
        {
          const ON_MeshTopologyEdge& ve = top.m_tope[f.m_topei[fei]];
          for (int efi = 0; efi < ve.m_topf_count; ++efi)
          {
            const int f1i = ve.m_topfi[efi];
            if (fi == f1i)
              continue;
            if (0 == fmarks[f1i])
              continue; // this face is not in the ngon
            const ON_MeshTopologyFace& f1 = top.m_topf[f1i];
            int* f1vi = const_cast<int*>( mesh.m_F[f1i].vi );
            const int f1v_count = f1.IsTriangle() ? 3 : 4;
            for (int f1ei = 0; f1ei < f1v_count; ++f1ei)
            {
              const int k = (0 == f1.m_reve[f1ei]) ? 1 : 0;
              const ON_MeshTopologyEdge& f1e = top.m_tope[f1.m_topei[f1ei]];
              if (topvi == f1e.m_topvi[k])
              {
                if (0 == pass)
                {
                  if (f1vi[f1ei] < mesh_vi[0])
                    mesh_vi[0] = f1vi[f1ei];
                  else if (f1vi[f1ei] > mesh_vi[1])
                    mesh_vi[1] = f1vi[f1ei];
                }
                else
                {
                  // weld all faces in ngon to use vertex mesh_vi[0]
                  if (2 == f1ei && f1vi[2] == f1vi[3])
                  {
                    f1vi[2] = mesh_vi[0];
                    f1vi[3] = mesh_vi[0];
                  }
                  else
                  {
                    f1vi[f1ei] = mesh_vi[0];
                  }
                }
              }
            }
            if (3 == f1v_count)
              f1vi[3] = f1vi[2];
          }
        }
        if (0 == pass)
        {
          if (mesh_vi[0] == mesh_vi[1])
            break;
        }
        else
        {
          // weld all faces in ngon to use vertex mesh_vi[0]
          if (2 == fei && fvi[2] == fvi[3])
          {
            fvi[2] = mesh_vi[0];
            fvi[3] = mesh_vi[0];
          }
          else
          {
            fvi[fei] = mesh_vi[0];
          }
        }
      }
    }
  }

  // clear the xmarks set above
  const unsigned char mask = ~xmark;
  for (unsigned nfi = 0; nfi < ngon_face_count; ++nfi)
    fmarks[ngon_fi[nfi]] &= mask;
}

static void Internal_GrowNgon(
  const ON_MeshTopology& top,
  unsigned char* emarks,
  unsigned char* fmarks,
  unsigned char etest_mask,
  unsigned char etest_result,
  unsigned char ftest_mask,
  unsigned char ftest_result,
  const unsigned char merged_mark,
  ON_SimpleArray<unsigned>& ngon_fi
)
{
  if (ngon_fi.Count() <= 0)
    return;

  const int face_count = top.m_topf.Count();

  for (int nfi = 0; nfi < ngon_fi.Count(); ++nfi)
    fmarks[ngon_fi[nfi]] |= merged_mark;

  etest_mask |= merged_mark;
  etest_result &= ~merged_mark;

  ftest_mask |= merged_mark;
  ftest_result &= ~merged_mark;

  for (int nfi = 0; nfi < ngon_fi.Count(); ++nfi)
  {
    const int f0i = ngon_fi[nfi];
    const ON_MeshTopologyFace& f0 = top.m_topf[f0i];
    const int f0_ecount = f0.IsTriangle() ? 3 : 4;
    for (int fei = 0; fei < f0_ecount; ++fei)
    {
      const int ei = f0.m_topei[fei];
      if (ei < 0 || ei > top.m_tope.Count())
        continue;
      if (etest_result != (emarks[ei] & etest_mask))
        continue;
      emarks[ei] |= merged_mark;
      const ON_MeshTopologyEdge& e = top.m_tope[ei];
      if (2 != e.m_topf_count || nullptr == e.m_topfi)
        continue;
      const int efi = (f0i != e.m_topfi[0]) ? 0 : 1;
      const int f1i = e.m_topfi[efi];
      if (f1i < 0 || f1i >= face_count)
        continue;
      if (ftest_result != (fmarks[f1i] & ftest_mask))
        continue;
      fmarks[f1i] |= merged_mark;
      ngon_fi.Append(f1i);
    }
  }
}

static void Internal_AddMarkToFaceAndEdgesAndVertices(
  const ON_Mesh& mesh,
  const ON_MeshTopology& top,
  const unsigned int* ngon0_map,
  int face_index,
  const unsigned char mark,
  unsigned char* fmarks,
  unsigned char* emarks,
  unsigned char* vmarks
)
{
  if (0 == mark || face_index < 0 || face_index > top.m_topf.Count())
    return;
  if (nullptr == fmarks && nullptr == emarks && nullptr == vmarks)
    return;

  unsigned fi_count = 1;
  const int* fi_list = &face_index;
  if (nullptr != ngon0_map)
  {
    const unsigned ni = ngon0_map[face_index];
    if (ni < mesh.NgonUnsignedCount())
    {
      const ON_MeshNgon* ngon = mesh.Ngon(ni);
      if (ngon->m_Fcount > 1 && nullptr != ngon->m_fi)
      {
        for (unsigned nfi = 0; nfi < ngon->m_Fcount; ++nfi)
        {
          if (face_index == (int)(ngon->m_fi[nfi]))
          {
            fi_count = ngon->m_Fcount;
            fi_list = (const int*)ngon->m_fi;
            break;
          }
        }
      }
    }
  }

  for (unsigned nfi = 0; nfi < fi_count; ++nfi)
  {
    int fi = fi_list[nfi];
    if (fi < 0 || fi >= top.m_topf.Count())
      continue;
    if (nullptr != fmarks)
      fmarks[fi] |= mark;
    if (nullptr != emarks || nullptr != vmarks)
    {
      const ON_MeshTopologyFace& f = top.m_topf[fi];
      //const int fecount = f.IsTriangle() ? 3 : 4;
      const int tope_count = top.m_tope.Count();
      const int topv_count = top.m_topv.Count();
      for (int fei = 0; fei < 4; fei++)
      {
        const int ei = f.m_topei[fei];
        if (ei < 0 || ei >= tope_count)
          continue;
        if (nullptr != emarks)
          emarks[ei] |= mark;
        if (nullptr != vmarks)
        {
          const ON_MeshTopologyEdge& e = top.m_tope[ei];
          for (int evi = 0; evi < 2; ++evi)
          {
            const int topvi = e.m_topvi[evi];
            if (topvi < 0 || topvi >= topv_count)
              continue;
            vmarks[topvi] |= mark;
          }
        }
      }
    }
  }
}


static void Internal_AddMarkToNgonInteriorEdges(
  const ON_Mesh& mesh,
  const ON_MeshTopology& top,
  const unsigned int* ngon0_map,
  int face_index,
  const unsigned char interior_edge_mark,
  unsigned char* emarks
)
{
  if (nullptr == ngon0_map)
    return;
  const int face_count = top.m_topf.Count();
  const int edge_count = top.m_tope.Count();
  if (face_index < 0 || face_index >= face_count)
    return;
  const unsigned ni = ngon0_map[face_index];
  if (ni >= mesh.NgonUnsignedCount())
    return;
  const ON_MeshNgon* ngon = mesh.Ngon(ni);
  if (nullptr == ngon || ngon->m_Fcount < 2 || nullptr == ngon->m_fi)
    return;

  for (unsigned nfi = 0; nfi < ngon->m_Fcount; ++nfi)
  {
    const int fi = (int)ngon->m_fi[nfi];
    if (fi < 0 || fi >= face_count)
      continue;
    const ON_MeshTopologyFace& f = top.m_topf[fi];
    const int f_ecount = f.IsTriangle() ? 3 : 4;
    for (int fei = 0; fei < f_ecount; ++fei)
    {
      const int ei = f.m_topei[fei];
      if (ei < 0 || ei >= edge_count)
        continue;
      const ON_MeshTopologyEdge& e = top.m_tope[ei];
      if (2 != e.m_topf_count || nullptr == e.m_topfi)
        continue;
      const int f1i = e.m_topfi[(fi != e.m_topfi[0]) ? 0 : 1];
      if (ni == ngon0_map[f1i])
        emarks[ei] |= interior_edge_mark;
    }
  }
}

static void Internal_WeldAndAddNgon(
  ON_Mesh& mesh,
  const ON_MeshTopology& top,
  const unsigned char xmark,
  unsigned char* fmarks,
   ON_SimpleArray<unsigned>& ngon_fi
)
{
  if (ngon_fi.Count() < 2)
    return;

  // ngons must be welded and MergeFaces supports making an ngon across an unwelded edge.
  Internal_WeldNgonCandiate(mesh,top,fmarks,xmark,ngon_fi);

  if (
    2 == ngon_fi.Count() 
    &&ngon_fi[0] != ngon_fi[1]
    && mesh.m_F[ngon_fi[0]].IsTriangle() 
    && mesh.m_F[ngon_fi[1]].IsTriangle()
    )
  {
    // make a single quad face
    ON_MeshFace f[2] = {mesh.m_F[ngon_fi[0]],mesh.m_F[ngon_fi[1]]};
    for (int f0ei = 0; f0ei < 3; ++f0ei)
    {
      const int f0vi[2] = { f[0].vi[f0ei],f[0].vi[(f0ei + 1) % 3] };
      for (int f1ei = 0; f1ei < 3; ++f1ei)
      {
        const int f1vi[2] = { f[1].vi[f1ei],f[1].vi[(f1ei + 1) % 3] };
        if (f0vi[0] != f1vi[1] || f0vi[1] != f1vi[0])
          continue;
        // merge triangles into a quad
        ON_MeshFace q;
        q.vi[f0ei] = f[0].vi[f0ei];
        q.vi[(f0ei+1)%4] = f[1].vi[(f1ei+2)%3];
        q.vi[(f0ei+2)%4] = f[0].vi[(f0ei+1)%3];
        q.vi[(f0ei+3)%4] = f[0].vi[(f0ei+2)%3];
        if (q.IsQuad() && q.IsValid(mesh.m_V.Count()))
        {
          mesh.m_F[ngon_fi[0]] = q;
          q.vi[0] = -1;
          q.vi[1] = -1;
          q.vi[2] = -1;
          q.vi[3] = -1;
          mesh.m_F[ngon_fi[1]] = q;
          ngon_fi.SetCount(1);
          mesh.AddNgon(1, ngon_fi.Array());
          return;
        }
      }
    }
  }

  mesh.AddNgon(ngon_fi.UnsignedCount(), ngon_fi.Array());
}

unsigned int ON_Mesh::MergeFaceSets(
  const ON_SimpleArray<ON_COMPONENT_INDEX>& ci_list
)
{
  const unsigned int bailout_rc = ON_UNSET_UINT_INDEX;

  const int ci_list_count = ci_list.UnsignedCount();
  if (ci_list_count <= 0)
    return bailout_rc;

  const int vertex_count = VertexCount();
  const int face_count = FaceCount();
  if (face_count < 1 || vertex_count < 3)
    return bailout_rc;


  const ON_MeshTopology& top = Topology();
  if (top.m_topf.Count() != face_count)
    return bailout_rc;

  const int topv_count = top.m_topv.Count();
  const int tope_count = top.m_tope.Count();

  if (topv_count < 3 || topv_count > vertex_count || tope_count < 3)
    return bailout_rc;

  ON_SimpleArray<unsigned char> vmarks_buffer(topv_count);
  vmarks_buffer.SetCount(topv_count);
  vmarks_buffer.Zero();
  unsigned char* vmarks = vmarks_buffer.Array();

  ON_SimpleArray<unsigned char> emarks_buffer(tope_count);
  emarks_buffer.SetCount(tope_count);
  emarks_buffer.Zero();
  unsigned char* emarks = emarks_buffer.Array();

  ON_SimpleArray<unsigned char> fmarks_buffer(face_count);
  fmarks_buffer.SetCount(face_count);
  fmarks_buffer.Zero();
  unsigned char* fmarks = fmarks_buffer.Array();


  const unsigned char in_ci_list_mark = 1;
  const unsigned char vmark = 2;
  const unsigned char emark = 4;
  const unsigned char fmark = 8;
  const unsigned char xmark = 0x10;
  const unsigned char v_list_mark = vmark | in_ci_list_mark;
  const unsigned char e_list_mark = emark | in_ci_list_mark;
  const unsigned char f_list_mark = fmark | in_ci_list_mark;
  const unsigned char v_x_mark = vmark | xmark;
  const unsigned char e_x_mark = emark | xmark;
  //const unsigned char f_x_mark = fmark | xmark;
  const unsigned char merged_mark = 0x80; // face has been merged

  ON_MeshNgonBuffer ngon_buffer;

  unsigned ngon0_count = this->NgonCount();
  const unsigned int* ngon0_map = ( ngon0_count > 0) ? this->NgonMap(true) : nullptr;

  // Mark faces, edges, and vertices referenced in ci_list[]
  // by setting bits in fmarks[], emarks[], and vmarks[]
  for (int i = 0; i < ci_list_count; ++i)
  {
    ON_COMPONENT_INDEX ci = ci_list[i];
    if (ci.m_index < 0)
      continue;
    switch (ci.m_type)
    {
    case ON_COMPONENT_INDEX::mesh_vertex:
      // convert ci.m_index from a ON_COMPONENT_INDEX::mesh_vertex 
      // to a ON_COMPONENT_INDEX::meshtop_vertex index.
      if (ci.m_index >= vertex_count)
        break;
      ci.m_index = top.m_topv_map[ci.m_index];
      if (ci.m_index < 0)
        break;
      // no break here
    case ON_COMPONENT_INDEX::meshtop_vertex:
      if (ci.m_index < topv_count)
      {
        const ON_MeshTopologyVertex& v = top.m_topv[ci.m_index];
        if (nullptr == v.m_topei || v.m_tope_count < 2)
          break;

        // validate the vertex
        unsigned ni[2] = { ON_UNSET_UINT_INDEX,ON_UNSET_UINT_INDEX };
        bool bValid = (v.m_tope_count >= 2 && nullptr != v.m_topei);
        for (int vei = 0; vei < v.m_tope_count && bValid; ++vei)
        {
          int topei = v.m_topei[vei];
          bValid = (topei >= 0 && topei < tope_count);
          if (bValid)
          {
            const ON_MeshTopologyEdge& e = top.m_tope[topei];
            bValid = (nullptr != e.m_topfi && e.m_topf_count >= 1 && e.m_topf_count <= 2);
            for (int efi = 0; efi < e.m_topf_count && bValid; ++efi)
            {
              int fi = e.m_topfi[efi];
              bValid = (fi >= 0 && fi < face_count);
              if (nullptr != ngon0_map && ni[0] == ni[1])
              {
                const unsigned k = ngon0_map[fi];
                const ON_MeshNgon* ngon = (k < ngon0_count) ? Ngon(k) : nullptr;
                if (nullptr != ngon && ngon->m_Fcount >= 2 && nullptr != ngon->m_fi)
                {
                  if (ON_UNSET_UINT_INDEX == ni[0])
                    ni[0] = k;
                  ni[1] = k;
                }
                else
                {
                  // this face is not part of an ngon - stop checking
                  ni[0] = ON_UNSET_UINT_INDEX;
                  ni[1] = 0;
                }
              }
            }
          }
        }
        if (false == bValid)
          break;
        if (ON_UNSET_UINT_INDEX != ni[0] && ni[0] == ni[1])
          break; // v is inside an ngon

        vmarks[ci.m_index] |= v_list_mark;

        // add a vmark to every face touching this vertex
        for (int vei = 0; vei < v.m_tope_count; ++vei)
        {
          const ON_MeshTopologyEdge& e = top.m_tope[v.m_topei[vei]];
          for (int efi = 0; efi < e.m_topf_count; ++efi)
            Internal_AddMarkToFaceAndEdgesAndVertices(*this, top, ngon0_map, e.m_topfi[efi], vmark, fmarks, nullptr, nullptr);
        }
      }
      break;

    case ON_COMPONENT_INDEX::meshtop_edge:
      if (ci.m_index < tope_count)
      {
        const ON_MeshTopologyEdge& e = top.m_tope[ci.m_index];
        if (nullptr == e.m_topfi || 2 != e.m_topf_count)
          continue;
        if (e.m_topvi[0] < 0 || e.m_topvi[0] >= topv_count)
          continue;
        if (e.m_topvi[1] < 0 || e.m_topvi[1] >= topv_count)
          continue;
        if (e.m_topfi[0] < 0 || e.m_topfi[0] >= face_count)
          continue;
        if (e.m_topfi[1] < 0 || e.m_topfi[1] >= face_count)
          continue;

        if (nullptr != ngon0_map)
        {
          const unsigned ni[2] = { ngon0_map[e.m_topfi[0]],ngon0_map[e.m_topfi[1]] };
          if (ni[0] < ngon0_count && ni[0] == ni[1])
            continue; // edge is inside an ngon
        }

        emarks[ci.m_index] |= e_list_mark;

        // add an emark to face touching this edge
        vmarks[e.m_topvi[0]] |= emark;
        vmarks[e.m_topvi[1]] |= emark;
        for (int efi = 0; efi < e.m_topf_count; ++efi)
        {
          const int fi = e.m_topfi[efi];
          Internal_AddMarkToFaceAndEdgesAndVertices(*this, top, ngon0_map, fi, emark, fmarks, nullptr, nullptr);
          Internal_AddMarkToNgonInteriorEdges(*this, top, ngon0_map, fi, e_list_mark, emarks);
        }
      }
      break;

    case ON_COMPONENT_INDEX::mesh_face:
      if (ci.m_index >= face_count)
        break;
      if (ngon0_count > 0)
      {
        const unsigned ni = ngon0_map[ci.m_index];
        if (ni < ngon0_count )
        {
          const ON_MeshNgon* ngon = Ngon(ni);
          if (nullptr != ngon && ngon->m_Fcount > 1 && nullptr != ngon->m_fi)
          {
            ci.m_type = ON_COMPONENT_INDEX::mesh_ngon;
            ci.m_index = (int)ni;
          }
        }
      }
      // no break here;
    case ON_COMPONENT_INDEX::mesh_ngon:
      if (ON_COMPONENT_INDEX::mesh_face == ci.m_type || ci.m_index < NgonCount())
      {
        const ON_MeshNgon* ngon = 
          (ON_COMPONENT_INDEX::mesh_face == ci.m_type)
          ? ngon_buffer.CreateFromMeshFaceIndex(this,ci.m_index)
          : Ngon(ci.m_index);
        if (nullptr == ngon || nullptr == ngon->m_fi || ngon->m_Fcount <  1)
          break;
        for (unsigned nfi = 0; nfi < ngon->m_Fcount; ++nfi)
        {
          int fi = ngon->m_fi[nfi];
          if (fi >= 0 && fi < face_count)
          {
            const ON_MeshTopologyFace& f = top.m_topf[fi];
            bool bValidFace = true;
            for (int fei = 0; fei < 4 && bValidFace; fei++)
            {
              const int ei = f.m_topei[fei];
              bValidFace = (ei >= 0 && ei < tope_count);
              if (bValidFace)
              {
                const ON_MeshTopologyEdge& e = top.m_tope[ei];
                for (int evi = 0; evi < 2 && bValidFace; ++evi)
                {
                  int topvi = e.m_topvi[evi];
                  bValidFace = (topvi >= 0 && topvi < topv_count);
                }
              }
            }

            if (bValidFace)
            {
              fmarks[fi] |= f_list_mark;
              Internal_AddMarkToFaceAndEdgesAndVertices(*this, top, ngon0_map, fi, fmark, fmarks, emarks, vmarks);
            }
          }
        }
      }
      break;

    default:
      break;
    }
  }

  // Resolve multi-marked faces and remove all marked faces from ngons.
  unsigned int fmark_face_count = 0;
  unsigned int vmark_face_count = 0;
  unsigned int emark_face_count = 0;

  for (int fi = 0; fi < face_count; ++fi)
  {
    if (f_list_mark == ( fmarks[fi] & f_list_mark ))
    {
      fmarks[fi] = (f_list_mark | xmark);
      ++fmark_face_count;
    }
    else if (emark == (fmarks[fi] & e_list_mark))
    {
      fmarks[fi] = emark;
      ++emark_face_count;
    }
    else if (vmark == (fmarks[fi] & v_list_mark))
    {
      fmarks[fi] = vmark;
      ++vmark_face_count;
    }
    else
    {
      fmarks[fi] = 0;
    }
  }

  unsigned int emark_count = 0;
  if (emark_face_count >= 2)
  {
    // ignore edges that are part of a boundary of a face in ci_list[]
    emark_face_count = 0;
    for (int ei = 0; ei < tope_count; ++ei)
    {
      unsigned char m = emarks[ei];
      emarks[ei] = 0;
      if (e_list_mark != m)
        continue;
      const ON_MeshTopologyEdge& e = top.m_tope[ei];
      for (int efi = 0; efi < e.m_topf_count && 0 != m; ++efi)
      {
        const int fi = e.m_topfi[efi];
        if (emark != fmarks[fi] && e_x_mark != fmarks[fi])
          m = 0;
      }
      if (0 != m)
      {
        emarks[ei] = e_list_mark;
        ++emark_count;
        for (int efi = 0; efi < e.m_topf_count && 0 != m; ++efi)
        {
          const int fi = e.m_topfi[efi];
          Internal_AddMarkToFaceAndEdgesAndVertices(*this, top, ngon0_map, fi, emark, fmarks, emarks, vmarks);
          if (emark == fmarks[fi])
          {
            fmarks[fi] |= xmark;
            ++emark_face_count;
          }
        }
      }
    }
  }
  if (0 == emark_count)
    emark_face_count = 0;

  unsigned int vmark_count = 0;
  if (vmark_face_count >= 2)
  {
    // ignore vertices that belong to faces or edges in ci_list[]
    vmark_face_count = 0;
    for (int topvi = 0; topvi < topv_count; ++topvi)
    {
      unsigned char m = vmarks[topvi];
      vmarks[topvi] = 0;
      if (v_list_mark != m)
        continue;
      const ON_MeshTopologyVertex& v = top.m_topv[topvi];
      for (int vei = 0; vei < v.m_tope_count && 0 != m; ++vei)
      {
        const int ei = v.m_topei[vei];
        if (0 != (emarks[ei] & (fmark|emark)) )
          m = 0;
        else
        {
          const ON_MeshTopologyEdge& e = top.m_tope[ei];
          for (int efi = 0; efi < e.m_topf_count && 0 != m; ++efi)
          {
            const int fi = e.m_topfi[efi];
            if (vmark != fmarks[fi] && v_x_mark != fmarks[fi])
              m = 0;
          }
        }
      }
      if (0 != m)
      {
        vmarks[topvi] = v_list_mark;
        ++vmark_count;
        for (int vei = 0; vei < v.m_tope_count && 0 != m; ++vei)
        {
          const int ei = v.m_topei[vei];
          emarks[ei] |= vmark;
          const ON_MeshTopologyEdge& e = top.m_tope[ei];
          for (int efi = 0; efi < e.m_topf_count && 0 != m; ++efi)
          {
            const int fi = e.m_topfi[efi];
            Internal_AddMarkToFaceAndEdgesAndVertices(*this, top, ngon0_map, fi, vmark, fmarks, nullptr, vmarks);
            Internal_AddMarkToNgonInteriorEdges(*this, top, ngon0_map, fi, vmark, emarks);
            if (vmark == fmarks[fi])
            {
              fmarks[fi] |= xmark;
              ++vmark_face_count;
            }
          }
        }
      }
    }
  }
  if (0 == vmark_count)
    vmark_face_count = 0;

  unsigned max_ngon_face_count = fmark_face_count;
  if (max_ngon_face_count < emark_face_count)
    max_ngon_face_count = emark_face_count;
  if (max_ngon_face_count < vmark_face_count)
    max_ngon_face_count = vmark_face_count;

  if (max_ngon_face_count < 2 )
    return bailout_rc;

  ON_SimpleArray<unsigned> ngon_fi(max_ngon_face_count);

  if (ngon0_count > 0)
  {
    // remove ngons that include marked faces
    const unsigned int* ngon_map = ( ngon0_count > 0) ? this->NgonMap(true) : nullptr;
    for (int fi = 0; fi < face_count; ++fi)
    {
      if (0 != (fmarks[fi] & xmark))
      {
        unsigned int ngon_index = (nullptr != ngon_map) ? ngon_map[fi] : ON_UNSET_UINT_INDEX;
        if (ngon_index < ngon0_count)
          ngon_fi.Append(ngon_index);
      }
    }
    ngon_fi.QuickSortAndRemoveDuplicates(ON_CompareDecreasing< unsigned>);
    for (int i = 0; i < ngon_fi.Count(); ++i)
      this->RemoveNgon((unsigned)ngon_fi[i]);
    this->RemoveEmptyNgons();

    // Any ngons with indices >= ngon0_count are ngons added by the code below.
    ngon0_count = this->NgonCount();


    ngon_fi.SetCount(0);
  }

  // zero x mark in fmarks[] because it is used in Internal_WeldAndAddNgon()
  for (int fi = 0; fi < face_count; ++fi)
    fmarks[fi] &= ~xmark;

  for (int fi = 0; fi < face_count; ++fi)
  {
    if (f_list_mark != (fmarks[fi] & (f_list_mark | merged_mark)))
      continue; // face not in ci_list[] or already merged

    // seed ngon with this face
    ngon_fi.SetCount(0);
    fmarks[fi] |= merged_mark;
    ngon_fi.Append((unsigned)fi);

    // grow ngon by adding other faces in ci_list[] that share and edge with a face in the ngon.
    Internal_GrowNgon(
      top, emarks, fmarks,
      0, // etest_mask,
      0, // etest_result,
      f_list_mark, // ftest_mask,
      f_list_mark, // ftest_result,
      merged_mark,
      ngon_fi
    );

    // weld ngon vertices and then add ngon
    Internal_WeldAndAddNgon(*this, top, xmark, fmarks, ngon_fi);
  }

  for (int ei = 0; ei < tope_count; ++ei)
  {
    if ( e_list_mark != (emarks[ei] & (e_list_mark | merged_mark)) )
      continue; // edge not in ci_list[] or already merged
    emarks[ei] |= merged_mark;
    const ON_MeshTopologyEdge& e = top.m_tope[ei];

    // seed ngon with faces attached to this edge
    ngon_fi.SetCount(0);
    for (int efi = 0; efi < e.m_topf_count; ++efi)
    {
      const int fi = e.m_topfi[efi];
      if (fi < 0 || fi >= face_count)
        break;
      if (emark != (fmarks[fi] & (emark|fmark|in_ci_list_mark|merged_mark)))
        break;
      fmarks[fi] |= merged_mark;
      ngon_fi.Append(fi);
    }

    // grow ngon by jumping across edges in ci_list[]
    Internal_GrowNgon(
      top, emarks, fmarks,
      e_list_mark | fmark, // etest_mask,
      e_list_mark, // etest_result,
      emark | fmark, // ftest_mask,
      emark, // ftest_result,
      merged_mark,
      ngon_fi
    );

    // weld ngon vertices and then add ngon
    Internal_WeldAndAddNgon(*this, top, xmark, fmarks, ngon_fi);
  }


  unsigned int mark_mask = v_list_mark | merged_mark;
  for (int vi = 0; vi < topv_count; ++vi)
  {
    if (v_list_mark != (vmarks[vi] & mark_mask))
      continue; // edge not in ci_list[] or already merged
    vmarks[vi] |= merged_mark;
    const ON_MeshTopologyVertex& v = top.m_topv[vi];

    // seed ngon with faces attached to this vertex
    ngon_fi.SetCount(0);
    for (int vei = 0; vei < v.m_tope_count; ++vei)
    {
      const ON_MeshTopologyEdge& e = top.m_tope[v.m_topei[vei]];
      for (int efi = 0; efi < e.m_topf_count; ++efi)
      {
        int fi = e.m_topfi[efi];
        if (fi < 0 || fi >= face_count)
          continue;
        if (vmark != (fmarks[fi] & (vmark|emark|fmark|in_ci_list_mark|merged_mark)))
          continue;
        fmarks[fi] |= merged_mark;
        ngon_fi.Append(fi);
      }
    }

    // grow ngon by jumping across edges with a vmark
    Internal_GrowNgon(
      top, emarks, fmarks,
      vmark, // etest_mask,
      vmark, // etest_result,
      vmark | emark | fmark, // ftest_mask,
      vmark, // ftest_result,
      merged_mark,
      ngon_fi
    );

    // weld ngon vertices and then add ngon
    Internal_WeldAndAddNgon(*this, top, xmark, fmarks, ngon_fi);
  }

  // clean up
  DeleteComponents(
    nullptr,
    0,
    true, // bIgnoreInvalidComponents
    true, // bRemoveDegenerateFaces
    true, // bRemoveUnusedVertices
    true  // bRemoveEmptyNgons
    );

  const unsigned ngon1_count = this->NgonCount();

  // return index where new ngons begin
  return (ngon1_count > ngon0_count) ? ngon0_count : bailout_rc;
}

static
void ClosestPtToEdge(const ON_3dPoint& P,
  const ON_3dPoint& A, const ON_3dPoint& B,
  double& a, double& b)
{
  const double D[3] = { A.x - B.x, A.y - B.y, A.z - B.z };
  double t = D[0] * D[0] + D[1] * D[1] + D[2] * D[2];
  if (t <= 0.0)
  {
    a = 1.0;
    b = 0.0;
  }
  else
  {
    const double P0[3] = { A.x - P.x, A.y - P.y, A.z - P.z };
    const double P1[3] = { P.x - B.x, P.y - B.y, P.z - B.z };
    t = 1.0 / t;
    if (P0[0] * P0[0] + P0[1] * P0[1] + P0[2] * P0[2] <= P1[0] * P1[0] + P1[1] * P1[1] + P1[2] * P1[2])
    {
      // A is closest to P
      t = (P0[0] * D[0] + P0[1] * D[1] + P0[2] * D[2]) * t;
      if (t <= ON_ZERO_TOLERANCE)
      {
        a = 1.0;
        b = 0.0;
      }
      else if (t >= 1.0 - ON_ZERO_TOLERANCE)
      {
        a = 0.0;
        b = 1.0;
      }
      else
      {
        a = 1.0 - t;
        b = t;
      }
    }
    else
    {
      // B is closest to P
      t = (P1[0] * D[0] + P1[1] * D[1] + P1[2] * D[2]) * t;
      if (t <= ON_ZERO_TOLERANCE)
      {
        a = 0.0;
        b = 1.0;
      }
      else if (t >= 1.0 - ON_ZERO_TOLERANCE)
      {
        a = 1.0;
        b = 0.0;
      }
      else
      {
        a = t;
        b = 1.0 - t;
      }
    }
  }
}

static bool ClosestPtToTriangleHelper(const ON_3dPoint& R,
  const ON_3dPoint& S,
  const ON_3dPoint& T,
  ON_3dPoint Q,
  double* r, double* s, double* t)
{
  double a00, a01, a10, a11, b0, b1, ss, tt;

  const ON_3dPoint V0(R.x - T.x, R.y - T.y, R.z - T.z);
  const ON_3dPoint V1(S.x - T.x, S.y - T.y, S.z - T.z);

  Q.x -= T.x;
  Q.y -= T.y;
  Q.z -= T.z;

  a00 = V0.x * V0.x + V0.y * V0.y + V0.z * V0.z;
  if (a00 <= 0.0)
    return false;
  a00 = 1.0 / a00;

  a11 = V1.x * V1.x + V1.y * V1.y + V1.z * V1.z;
  if (a11 <= 0.0)
    return false;
  a11 = 1.0 / a11;

  a01 = V0.x * V1.x + V0.y * V1.y + V0.z * V1.z;
  a10 = a01 * a11;
  a01 *= a00;

  b0 = (V0.x * Q.x + V0.y * Q.y + V0.z * Q.z) * a00;
  b1 = (V1.x * Q.x + V1.y * Q.y + V1.z * Q.z) * a11;

  if (a00 <= a11)
  {
    a11 = 1.0 - a01 * a10;
    if (0.0 == a11)
      return false;
    tt = (b1 - a10 * b0) / a11;
    ss = (b0 - a01 * tt);
  }
  else
  {
    a00 = 1.0 - a01 * a10;
    if (0.0 == a00)
      return false;
    ss = (b0 - a01 * b1) / a00;
    tt = (b1 - a10 * ss);
  }

  *r = ss;
  *s = tt;
  *t = 1.0 - ss - tt;

  return true;
}

static void ClosestPtToTriangle(const ON_3dPoint& input, ON_3dPoint& output, const ON_3dPoint* tri, double& baryA, double& baryB, double& baryC)
{
  if (!ClosestPtToTriangleHelper(tri[0], tri[1], tri[2], input, &baryA, &baryB, &baryC))
  {
    // bogus triangle - check edges
    double a, b, c, d;

    ClosestPtToEdge(input, tri[0], tri[1], baryA, baryB);
    baryC = 0.0;
    d = input.DistanceTo(baryA * tri[0] + baryB * tri[1]);

    ClosestPtToEdge(input, tri[1], tri[2], a, b);
    c = input.DistanceTo(a * tri[1] + b * tri[2]);
    if (c < d)
    {
      d = c;
      baryA = 0.0;
      baryB = a;
      baryC = b;
    }

    ClosestPtToEdge(input, tri[2], tri[0], a, b);
    c = input.DistanceTo(a * tri[2] + b * tri[0]);
    if (c < d)
    {
      baryA = b;
      baryB = 0.0;
      baryC = a;
    }
  }
  else
  {
    if (baryA <= ON_ZERO_TOLERANCE)
      baryA = 0.0;

    if (baryB <= ON_ZERO_TOLERANCE)
      baryB = 0.0;

    if (baryC <= ON_ZERO_TOLERANCE)
      baryC = 0.0;

    if (baryA == 0.0 || baryB == 0.0 || baryC == 0.0)
    {
      // Candidate bary-coords
      double baryA0, baryB0, baryC0;
      double baryA1, baryB1, baryC1;

      baryA0 = baryB0 = baryC0 = -1.0;
      baryA1 = baryB1 = baryC1 = -1.0;

      bool has_second_cadidate_coords = false;

      if (0.0 == baryA)
      {
        if (0.0 == baryB) {
          ClosestPtToEdge(input, tri[0], tri[2], baryA0, baryC0);
          baryB0 = 1.0 - baryA0 - baryC0;

          ClosestPtToEdge(input, tri[1], tri[2], baryB1, baryC1);
          baryA1 = 1.0 - baryB1 - baryC1;
          has_second_cadidate_coords = true;
        }
        else if (0.0 == baryC) {
          ClosestPtToEdge(input, tri[0], tri[1], baryA0, baryB0);
          baryC0 = 1.0 - baryA0 - baryB0;

          ClosestPtToEdge(input, tri[2], tri[1], baryC1, baryB1);
          baryA1 = 1.0 - baryC1 - baryB1;
          has_second_cadidate_coords = true;
        }
        else {
          ClosestPtToEdge(input, tri[1], tri[2], baryB0, baryC0);
          baryA0 = 1.0 - baryB0 - baryC0;
        }
      }
      else if (0.0 == baryB)
      {
        if (0.0 == baryC) {
          ClosestPtToEdge(input, tri[1], tri[0], baryB0, baryA0);
          baryC0 = 1.0 - baryB0 - baryA0;

          ClosestPtToEdge(input, tri[2], tri[0], baryC1, baryA1);
          baryB1 = 1.0 - baryC1 - baryA1;
          has_second_cadidate_coords = true;
        }
        else {
          ClosestPtToEdge(input, tri[2], tri[0], baryC0, baryA0);
          baryB0 = 1.0 - baryC0 - baryA0;
        }
      }
      else if (0.0 == baryC) {
        ClosestPtToEdge(input, tri[0], tri[1], baryA0, baryB0);
        baryC0 = 1.0 - baryA0 - baryB0;
      }

      // Start by assuming the first bary-coords are correct
      baryA = baryA0;
      baryB = baryB0;
      baryC = baryC0;

      if (has_second_cadidate_coords)
      {
        ON_3dPoint point0 = baryA0 * tri[0] + baryB0 * tri[1] + baryC0 * tri[2];
        ON_3dPoint point1 = baryA1 * tri[0] + baryB1 * tri[1] + baryC1 * tri[2];

        // If other bary-coords are closer to point, use those instead
        if ((point0 - input).LengthSquared() > (point1 - input).LengthSquared()) {
          baryA = baryA1;
          baryB = baryB1;
          baryC = baryC1;
        }
      }

      if (baryA <= ON_ZERO_TOLERANCE)
        baryA = 0.0;

      if (baryB <= ON_ZERO_TOLERANCE)
        baryB = 0.0;

      if (baryC <= ON_ZERO_TOLERANCE)
        baryC = 0.0;
    }
  }

  output = baryA * tri[0] + baryB * tri[1] + baryC * tri[2];
}

void ClosestPtToMeshFace(const ON_Mesh* mesh, const int fi, const ON_3dPoint& ptIn, ON_3dPoint& POut, double(&tOut)[4])
{
  // no need to check input - it should be perfect - if it's not, 
  // fix bug in tree creation code

  const int* face_vi = mesh->m_F[fi].vi;
  const ON_3fPoint* mesh_V = mesh->m_V;
  ON_3dPoint tri[3];

  if (face_vi[2] == face_vi[3])
  {
    tri[0] = mesh_V[face_vi[0]];
    tri[1] = mesh_V[face_vi[1]];
    tri[2] = mesh_V[face_vi[2]];
    ClosestPtToTriangle(ptIn, POut, tri, tOut[0], tOut[1], tOut[2]);
    tOut[3] = 0.0;
  }
  else
  {
    // split quad into two triangles
    ON_3dPoint POut2;
    double tOut2[4] = { 0.0, 0.0, 0.0, 0.0 };
    double d0 = mesh_V[face_vi[0]].DistanceTo(mesh_V[face_vi[2]]);
    double d1 = mesh_V[face_vi[1]].DistanceTo(mesh_V[face_vi[3]]);
    if (d0 <= d1)
    {
      // diagonal from 0 to 2 is shortest, so use triangles 0,1,2 and 0,2,3
      tri[0] = mesh_V[face_vi[0]];
      tri[1] = mesh_V[face_vi[1]];
      tri[2] = mesh_V[face_vi[2]];
      ClosestPtToTriangle(ptIn, POut, tri, tOut[0], tOut[1], tOut[2]);
      tOut[3] = 0.0;

      // tri[0] = mesh_V[face_vi[0]];
      tri[1] = tri[2]; // tri[1] = mesh_V[face_vi[2]];
      tri[2] = mesh_V[face_vi[3]];
      ClosestPtToTriangle(ptIn, POut2, tri, tOut2[0], tOut2[2], tOut2[3]);
      tOut2[1] = 0.0;
    }
    else
    {
      // diagonal from 1 to 3 is shortest, so use triangles 0,1,3 and 1,2,3
      tri[0] = mesh_V[face_vi[0]];
      tri[1] = mesh_V[face_vi[1]];
      tri[2] = mesh_V[face_vi[3]];
      ClosestPtToTriangle(ptIn, POut, tri, tOut[0], tOut[1], tOut[3]);
      tOut[2] = 0.0;

      tri[0] = tri[1]; // tri[0] = mesh_V[face_vi[1]];
      tri[1] = mesh_V[face_vi[2]];
      //tri[2] = mesh_V[face_vi[3]];
      ClosestPtToTriangle(ptIn, POut2, tri, tOut2[1], tOut2[2], tOut2[3]);
      tOut2[0] = 0.0;
    }

    d0 = ptIn.DistanceTo(POut);
    d1 = ptIn.DistanceTo(POut2);
    if (d1 < d0)
    {
      // point on 2nd triangle was closer
      POut = POut2;
      tOut[0] = tOut2[0];
      tOut[1] = tOut2[1];
      tOut[2] = tOut2[2];
      tOut[3] = tOut2[3];
    }
  }
}