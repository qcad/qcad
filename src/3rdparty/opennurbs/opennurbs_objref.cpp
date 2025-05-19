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

ON_COMPONENT_INDEX::ON_COMPONENT_INDEX() 
                   : m_type(ON_COMPONENT_INDEX::invalid_type),
                     m_index(-1)
{
}

ON_COMPONENT_INDEX::ON_COMPONENT_INDEX(
                                       ON_COMPONENT_INDEX::TYPE type,
                                       int index
                                       ) 
                   : m_type(type),
                     m_index(index)
{
}

ON_COMPONENT_INDEX::TYPE ON_COMPONENT_INDEX::Type(int i)
{
  TYPE t = invalid_type;
  switch((unsigned int)i)
  {
  case ON_COMPONENT_INDEX::no_type:            t = ON_COMPONENT_INDEX::no_type;            break;
  
  case ON_COMPONENT_INDEX::brep_vertex:        t = ON_COMPONENT_INDEX::brep_vertex;        break;
  case ON_COMPONENT_INDEX::brep_edge:          t = ON_COMPONENT_INDEX::brep_edge;          break;
  case ON_COMPONENT_INDEX::brep_face:          t = ON_COMPONENT_INDEX::brep_face;          break;
  case ON_COMPONENT_INDEX::brep_trim:          t = ON_COMPONENT_INDEX::brep_trim;          break;
  case ON_COMPONENT_INDEX::brep_loop:          t = ON_COMPONENT_INDEX::brep_loop;          break;
  
  case ON_COMPONENT_INDEX::mesh_vertex:        t = ON_COMPONENT_INDEX::mesh_vertex;        break;
  case ON_COMPONENT_INDEX::meshtop_vertex:     t = ON_COMPONENT_INDEX::meshtop_vertex;     break;
  case ON_COMPONENT_INDEX::meshtop_edge:       t = ON_COMPONENT_INDEX::meshtop_edge;       break;
  case ON_COMPONENT_INDEX::mesh_face:          t = ON_COMPONENT_INDEX::mesh_face;          break;
  case ON_COMPONENT_INDEX::mesh_ngon:          t = ON_COMPONENT_INDEX::mesh_ngon;          break;

  case ON_COMPONENT_INDEX::idef_part:          t = ON_COMPONENT_INDEX::idef_part;          break;
  case ON_COMPONENT_INDEX::polycurve_segment:  t = ON_COMPONENT_INDEX::polycurve_segment;  break;
  case ON_COMPONENT_INDEX::pointcloud_point:   t = ON_COMPONENT_INDEX::pointcloud_point;   break;
  case ON_COMPONENT_INDEX::group_member:       t = ON_COMPONENT_INDEX::group_member;       break;

  case ON_COMPONENT_INDEX::extrusion_bottom_profile: t = ON_COMPONENT_INDEX::extrusion_bottom_profile; break;
  case ON_COMPONENT_INDEX::extrusion_top_profile:    t = ON_COMPONENT_INDEX::extrusion_top_profile;    break;
  case ON_COMPONENT_INDEX::extrusion_wall_edge:      t = ON_COMPONENT_INDEX::extrusion_wall_edge;      break;
  case ON_COMPONENT_INDEX::extrusion_wall_surface:   t = ON_COMPONENT_INDEX::extrusion_wall_surface;   break;
  case ON_COMPONENT_INDEX::extrusion_cap_surface:    t = ON_COMPONENT_INDEX::extrusion_cap_surface;    break;
  case ON_COMPONENT_INDEX::extrusion_path:           t = ON_COMPONENT_INDEX::extrusion_path;           break;

  case ON_COMPONENT_INDEX::subd_vertex:        t = ON_COMPONENT_INDEX::subd_vertex;        break;
  case ON_COMPONENT_INDEX::subd_edge:          t = ON_COMPONENT_INDEX::subd_edge;          break;
  case ON_COMPONENT_INDEX::subd_face:          t = ON_COMPONENT_INDEX::subd_face;          break;

  case ON_COMPONENT_INDEX::hatch_loop:         t = ON_COMPONENT_INDEX::hatch_loop;         break;

  case ON_COMPONENT_INDEX::dim_linear_point:   t = ON_COMPONENT_INDEX::dim_linear_point;   break;
  case ON_COMPONENT_INDEX::dim_radial_point:   t = ON_COMPONENT_INDEX::dim_radial_point;   break;
  case ON_COMPONENT_INDEX::dim_angular_point:  t = ON_COMPONENT_INDEX::dim_angular_point;  break;
  case ON_COMPONENT_INDEX::dim_ordinate_point: t = ON_COMPONENT_INDEX::dim_ordinate_point; break;
  case ON_COMPONENT_INDEX::dim_text_point:     t = ON_COMPONENT_INDEX::dim_text_point;     break;
  case ON_COMPONENT_INDEX::dim_centermark_point:     t = ON_COMPONENT_INDEX::dim_centermark_point;     break;
  case ON_COMPONENT_INDEX::dim_leader_point:         t = ON_COMPONENT_INDEX::dim_leader_point;         break;
  }
  return t;
}


void ON_COMPONENT_INDEX::Set(
  ON_COMPONENT_INDEX::TYPE type,
  int index
  ) 
{
  m_type = type;
  m_index = index;
}

void ON_COMPONENT_INDEX::Set(
  ON_COMPONENT_INDEX::TYPE type,
  unsigned int index
  ) 
{
  m_type = type;
  m_index = (int)index;
}

void ON_COMPONENT_INDEX::UnSet()
{
  m_type = ON_COMPONENT_INDEX::invalid_type;
  m_index = -1;
}

bool ON_COMPONENT_INDEX::IsMeshComponentIndex() const
{
  bool rc = false;
  switch(m_type)
  {
  case ON_COMPONENT_INDEX::mesh_vertex:
  case ON_COMPONENT_INDEX::meshtop_vertex:
  case ON_COMPONENT_INDEX::meshtop_edge:
  case ON_COMPONENT_INDEX::mesh_face:
  case ON_COMPONENT_INDEX::mesh_ngon:
    if ( m_index >= 0 )
    {
      rc = true;
    }
    break;
  default:
    // intentionally skipping other ON_COMPONENT_INDEX::TYPE enum values
    break;
  }
  return rc;
}

bool ON_COMPONENT_INDEX::IsSubDComponentIndex() const
{
  bool rc = false;
  switch(m_type)
  {
  case ON_COMPONENT_INDEX::subd_vertex:
  case ON_COMPONENT_INDEX::subd_edge:
  case ON_COMPONENT_INDEX::subd_face:
    if ( -1 != m_index && 0 != m_index )
    {
      rc = true;
    }
    break;
  default:
    // intentionally skipping other ON_COMPONENT_INDEX::TYPE enum values
    break;
  }
  return rc;
}


bool ON_COMPONENT_INDEX::IsAnnotationComponentIndex() const
{
  bool rc = false;
  switch(m_type)
  {
  case ON_COMPONENT_INDEX::dim_linear_point:
  case ON_COMPONENT_INDEX::dim_radial_point:
  case ON_COMPONENT_INDEX::dim_angular_point:
  case ON_COMPONENT_INDEX::dim_ordinate_point:
  case ON_COMPONENT_INDEX::dim_text_point:
    if ( m_index >= 0 )
    {
      rc = true;
    }
    break;
  default:
    // intentionally skipping other ON_COMPONENT_INDEX::TYPE enum values
    break;
  }
  return rc;
}

bool ON_COMPONENT_INDEX::IsBrepComponentIndex() const
{
  bool rc = false;
  switch(m_type)
  {
  case ON_COMPONENT_INDEX::brep_vertex:
  case ON_COMPONENT_INDEX::brep_trim:
  case ON_COMPONENT_INDEX::brep_loop:
  case ON_COMPONENT_INDEX::brep_edge:
  case ON_COMPONENT_INDEX::brep_face:
    if ( m_index >= 0 )
    {
      rc = true;
    }
    break;
  default:
    // intentionally skipping other ON_COMPONENT_INDEX::TYPE enum values
    break;
  }
  return rc;
}

bool  ON_COMPONENT_INDEX::IsIDefComponentIndex() const
{
  return ( ON_COMPONENT_INDEX::idef_part == m_type && m_index >= 0 );
}

bool  ON_COMPONENT_INDEX::IsPolyCurveComponentIndex() const
{
  return ( ON_COMPONENT_INDEX::polycurve_segment == m_type && m_index >= 0 );
}

bool  ON_COMPONENT_INDEX::IsGroupMemberComponentIndex() const
{
  return ( ON_COMPONENT_INDEX::group_member == m_type && m_index >= 0 );
}

bool  ON_COMPONENT_INDEX::IsExtrusionProfileComponentIndex() const
{
  return ( (   ON_COMPONENT_INDEX::extrusion_bottom_profile  == m_type 
            || ON_COMPONENT_INDEX::extrusion_top_profile     == m_type
            )
            && m_index >= 0 
         );
}

bool  ON_COMPONENT_INDEX::IsExtrusionPathComponentIndex() const
{
  return ( ON_COMPONENT_INDEX::extrusion_path  == m_type 
           && m_index >= -1 
           && m_index <= 1
         );
}

bool  ON_COMPONENT_INDEX::IsExtrusionWallEdgeComponentIndex() const
{
  return ( ON_COMPONENT_INDEX::extrusion_wall_edge  == m_type 
           && m_index >= 0 
         );
}

bool  ON_COMPONENT_INDEX::IsExtrusionWallSurfaceComponentIndex() const
{
  return ( ON_COMPONENT_INDEX::extrusion_wall_surface  == m_type 
           && m_index >= 0
         );
}

bool  ON_COMPONENT_INDEX::IsExtrusionWallComponentIndex() const
{
  return ( (   ON_COMPONENT_INDEX::extrusion_wall_edge == m_type 
             || ON_COMPONENT_INDEX::extrusion_wall_surface == m_type
           )
           && m_index >= 0
         );
}

bool  ON_COMPONENT_INDEX::IsExtrusionComponentIndex() const
{
  return ( (   ON_COMPONENT_INDEX::extrusion_bottom_profile  == m_type 
            || ON_COMPONENT_INDEX::extrusion_top_profile     == m_type
            || ON_COMPONENT_INDEX::extrusion_wall_edge       == m_type
            || ON_COMPONENT_INDEX::extrusion_wall_surface    == m_type
            || ON_COMPONENT_INDEX::extrusion_cap_surface     == m_type
            || ON_COMPONENT_INDEX::extrusion_path            == m_type
            )
            && 
            (  m_index >= 0 
              || (-1 == m_index && ON_COMPONENT_INDEX::extrusion_path == m_type)
            )
         );
}

bool  ON_COMPONENT_INDEX::IsPointCloudComponentIndex() const
{
  return ( ON_COMPONENT_INDEX::pointcloud_point == m_type && m_index >= 0 );
}

bool  ON_COMPONENT_INDEX::IsHatchLoopComponentIndex() const
{
  return (ON_COMPONENT_INDEX::hatch_loop == m_type && m_index >= 0);
}

static void ToStringHelper( ON_COMPONENT_INDEX ci, char* buffer, size_t sizeof_buffer )
{
  char* str = buffer;
  size_t str_capacity = sizeof_buffer/sizeof(buffer[0]);
  const char* s;
  const char* str_end;
  char ubuffer[32]; // unsigned int to string storage ubuffer
  unsigned int i, j;

  if ( nullptr == str || str_capacity <= 0 )
    return;

  str[--str_capacity] = 0;
  if (str_capacity <= 0)
    return;

  str_end = str + str_capacity;

  s = "m_type=";
  while ( str < str_end )
  {
    const char c = *s++;
    if (0 == c)
      break;

    *str++ = c;
  }

  switch(ci.m_type)
  {
  case ON_COMPONENT_INDEX::no_type:            s = "ON_COMPONENT_INDEX::no_type";            break;
  
  case ON_COMPONENT_INDEX::brep_vertex:        s = "ON_COMPONENT_INDEX::brep_vertex";        break;
  case ON_COMPONENT_INDEX::brep_edge:          s = "ON_COMPONENT_INDEX::brep_edge";          break;
  case ON_COMPONENT_INDEX::brep_face:          s = "ON_COMPONENT_INDEX::brep_face";          break;
  case ON_COMPONENT_INDEX::brep_trim:          s = "ON_COMPONENT_INDEX::brep_trim";          break;
  case ON_COMPONENT_INDEX::brep_loop:          s = "ON_COMPONENT_INDEX::brep_loop";          break;
  
  case ON_COMPONENT_INDEX::mesh_vertex:        s = "ON_COMPONENT_INDEX::mesh_vertex";        break;
  case ON_COMPONENT_INDEX::meshtop_vertex:     s = "ON_COMPONENT_INDEX::meshtop_vertex";     break;
  case ON_COMPONENT_INDEX::meshtop_edge:       s = "ON_COMPONENT_INDEX::meshtop_edge";       break;
  case ON_COMPONENT_INDEX::mesh_face:          s = "ON_COMPONENT_INDEX::mesh_face";          break;
  case ON_COMPONENT_INDEX::mesh_ngon:          s = "ON_COMPONENT_INDEX::mesh_ngon";          break;

  case ON_COMPONENT_INDEX::idef_part:          s = "ON_COMPONENT_INDEX::idef_part";          break;
  case ON_COMPONENT_INDEX::polycurve_segment:  s = "ON_COMPONENT_INDEX::polycurve_segment";  break;
  case ON_COMPONENT_INDEX::pointcloud_point:   s = "ON_COMPONENT_INDEX::pointcloud_point";   break;
  case ON_COMPONENT_INDEX::group_member:       s = "ON_COMPONENT_INDEX::group_member";       break;

  case ON_COMPONENT_INDEX::extrusion_bottom_profile: s = "ON_COMPONENT_INDEX::extrusion_bottom_profile"; break;
  case ON_COMPONENT_INDEX::extrusion_top_profile:    s = "ON_COMPONENT_INDEX::extrusion_top_profile";    break;
  case ON_COMPONENT_INDEX::extrusion_wall_edge:      s = "ON_COMPONENT_INDEX::extrusion_wall_edge";      break;
  case ON_COMPONENT_INDEX::extrusion_wall_surface:   s = "ON_COMPONENT_INDEX::extrusion_wall_surface";   break;
  case ON_COMPONENT_INDEX::extrusion_cap_surface:    s = "ON_COMPONENT_INDEX::extrusion_cap_surface";    break;
  case ON_COMPONENT_INDEX::extrusion_path:           s = "ON_COMPONENT_INDEX::extrusion_path";           break;

  case ON_COMPONENT_INDEX::subd_vertex:        s = "ON_COMPONENT_INDEX::subd_vertex";        break;
  case ON_COMPONENT_INDEX::subd_edge:          s = "ON_COMPONENT_INDEX::subd_edge";          break;
  case ON_COMPONENT_INDEX::subd_face:          s = "ON_COMPONENT_INDEX::subd_face";          break;

  case ON_COMPONENT_INDEX::hatch_loop:         s = "ON_COMPONENT_INDEX::hatch_loop";         break;

  case ON_COMPONENT_INDEX::dim_linear_point:   s = "ON_COMPONENT_INDEX::dim_linear_point";   break;
  case ON_COMPONENT_INDEX::dim_radial_point:   s = "ON_COMPONENT_INDEX::dim_radial_point";   break;
  case ON_COMPONENT_INDEX::dim_angular_point:  s = "ON_COMPONENT_INDEX::dim_angular_point";  break;
  case ON_COMPONENT_INDEX::dim_ordinate_point: s = "ON_COMPONENT_INDEX::dim_ordinate_point"; break;
  case ON_COMPONENT_INDEX::dim_text_point:     s = "ON_COMPONENT_INDEX::dim_text_point";     break;
  case ON_COMPONENT_INDEX::dim_centermark_point:     s = "ON_COMPONENT_INDEX::dim_centermark_point";     break;
  case ON_COMPONENT_INDEX::dim_leader_point:         s = "ON_COMPONENT_INDEX::dim_leader_point";         break;

  default: s = 0; break;
  }

  if ( 0 != s )
  {
    while ( str < str_end )
    {
      const char c = *s++;
      if (0 == c)
        break;

      *str++ = c;
    }
  }

  s = " m_index=";
  while ( str < str_end )
  {
    const char c = *s++;
    if (0 == c)
      break;

    *str++ = c;
  }

  if ( ci.m_index < 1 )
  {
    i = (unsigned int)(-ci.m_index);
    s = "-";
    while ( str < str_end )
    {
      const char c = *s++;
      if (0 == c)
        break;

      *str++ = c;
    }
  }
  else
  {
    i = (unsigned int)(ci.m_index);
  }
  
  j = sizeof(ubuffer)/sizeof(ubuffer[0]);
  j--;
  ubuffer[j] = 0;
  while(j > 0)
  {
    j--;
    ubuffer[j] = (char)('0'+i%10);
    i /= 10;
    if ( 0 == i )
      break;
  }

  s = &ubuffer[j];
  while ( str < str_end )
  {
    if ( 0 == (*str++ = *s++))
      break;
  }
}

void ON_COMPONENT_INDEX::Dump( 
  class ON_TextLog& text_log 
  )const
{
  char buffer[128];
  ToStringHelper(*this,buffer,sizeof(buffer));
  text_log.Print(buffer);
}

void ON_COMPONENT_INDEX::AppendToString( 
  class ON_String& s
  )const
{
  char buffer[128];
  ToStringHelper(*this,buffer,sizeof(buffer));
  s += buffer;
}

void ON_COMPONENT_INDEX::AppendToString( 
  class ON_wString& s
  )const
{
  char buffer[128];
  ToStringHelper(*this,buffer,sizeof(buffer));
  s += buffer;
}

bool ON_COMPONENT_INDEX::IsNotSet() const
{
  return (false == IsSet());
}

bool ON_COMPONENT_INDEX::IsSet() const
{
  bool rc = false;
  switch(m_type)
  {
  case ON_COMPONENT_INDEX::invalid_type:
    rc = false;
    break;

  case ON_COMPONENT_INDEX::no_type:
    rc = false;
    break;

  case ON_COMPONENT_INDEX::brep_vertex:
  case ON_COMPONENT_INDEX::brep_edge:
  case ON_COMPONENT_INDEX::brep_face:
  case ON_COMPONENT_INDEX::brep_trim:
  case ON_COMPONENT_INDEX::brep_loop:

  case ON_COMPONENT_INDEX::mesh_vertex:
  case ON_COMPONENT_INDEX::meshtop_vertex:
  case ON_COMPONENT_INDEX::meshtop_edge:
  case ON_COMPONENT_INDEX::mesh_face:
  case ON_COMPONENT_INDEX::mesh_ngon:

  case ON_COMPONENT_INDEX::idef_part:
  case ON_COMPONENT_INDEX::polycurve_segment:
  case ON_COMPONENT_INDEX::pointcloud_point:
  case ON_COMPONENT_INDEX::group_member:

  case ON_COMPONENT_INDEX::subd_vertex:
  case ON_COMPONENT_INDEX::subd_edge:
  case ON_COMPONENT_INDEX::subd_face:

  case ON_COMPONENT_INDEX::hatch_loop:

  case ON_COMPONENT_INDEX::dim_linear_point:
  case ON_COMPONENT_INDEX::dim_radial_point:
  case ON_COMPONENT_INDEX::dim_angular_point:
  case ON_COMPONENT_INDEX::dim_ordinate_point:
  case ON_COMPONENT_INDEX::dim_text_point:
  case ON_COMPONENT_INDEX::dim_centermark_point:
  case ON_COMPONENT_INDEX::dim_leader_point:

    rc = (m_index != -1);
    break;

  default:
    rc = false;
    break;
  }
  return rc;
}


int ON_COMPONENT_INDEX::CompareType( const ON_COMPONENT_INDEX* lhs, const ON_COMPONENT_INDEX* rhs )
{
  const int lhs_i = (int)lhs->m_type;
  const int rhs_i = (int)rhs->m_type;
  if (lhs_i < rhs_i)
    return -1;
  if (lhs_i > rhs_i)
    return 1;
  return 0;
}


int ON_COMPONENT_INDEX::Compare( const ON_COMPONENT_INDEX* lhs, const ON_COMPONENT_INDEX* rhs )
{
  const int lhs_i = (int)lhs->m_type;
  const int rhs_i = (int)rhs->m_type;
  if (lhs_i < rhs_i)
    return -1;
  if (lhs_i > rhs_i)
    return 1;

  if (lhs->m_index < rhs->m_index)
    return -1;
  if (lhs->m_index > rhs->m_index)
    return 1;
  return 0;
}

bool ON_COMPONENT_INDEX::operator==(const ON_COMPONENT_INDEX& other) const
{
  return (m_type == other.m_type && m_index == other.m_index);
}

bool ON_COMPONENT_INDEX::operator!=(const ON_COMPONENT_INDEX& other) const
{
  return (m_type != other.m_type || m_index != other.m_index);
}

bool ON_COMPONENT_INDEX::operator<(const ON_COMPONENT_INDEX& other) const
{
  return (ON_COMPONENT_INDEX::Compare(this,&other) < 0);
}

bool ON_COMPONENT_INDEX::operator<=(const ON_COMPONENT_INDEX& other) const
{
  return (ON_COMPONENT_INDEX::Compare(this,&other) <= 0);
}

bool ON_COMPONENT_INDEX::operator>(const ON_COMPONENT_INDEX& other) const
{
  return (ON_COMPONENT_INDEX::Compare(this,&other) > 0);
}

bool ON_COMPONENT_INDEX::operator>=(const ON_COMPONENT_INDEX& other) const
{
  return (ON_COMPONENT_INDEX::Compare(this,&other) >= 0);
}

const ON_ComponentIndexAndNumber ON_ComponentIndexAndNumber::Create(
  ON_COMPONENT_INDEX ci,
  double x
)
{
  ON_ComponentIndexAndNumber cx;
  cx.m_ci = ci;
  cx.m_x = x;
  return cx;
}

int ON_ComponentIndexAndNumber::CompareComponent(
  const ON_ComponentIndexAndNumber* a,
  const ON_ComponentIndexAndNumber* b
)
{
  if (a == b)
    return 0;
  if (nullptr == a)
    return -1; // nulls sort last
  if (nullptr == b)
    return -1; // nulls sort last
  return ON_COMPONENT_INDEX::Compare(&a->m_ci, &b->m_ci);
}

int ON_ComponentIndexAndNumber::CompareNumber(
  const ON_ComponentIndexAndNumber* a,
  const ON_ComponentIndexAndNumber* b
)
{
  if (a == b)
    return 0;
  if (nullptr == a)
    return -1; // nulls sort last
  if (nullptr == b)
    return -1; // nulls sort last
  return ON_CompareDouble(a->m_x, b->m_x);
}

int ON_ComponentIndexAndNumber::CompareComponentAndNumber(
  const ON_ComponentIndexAndNumber* a,
  const ON_ComponentIndexAndNumber* b
)
{
  const int rc = ON_ComponentIndexAndNumber::CompareComponent(a, b);
  return (0 == rc) ? ON_ComponentIndexAndNumber::CompareNumber(a,b) : rc;
}


const ON_COMPONENT_INDEX ON_ComponentIndexAndNumber::Component() const
{
  return m_ci;
}

void ON_ComponentIndexAndNumber::SetComponent(ON_COMPONENT_INDEX ci)
{
  m_ci = ci;
}

double ON_ComponentIndexAndNumber::Number() const
{
  return m_x;
}

void ON_ComponentIndexAndNumber::SetNumber(double x)
{
  m_x = x;
}

ON_ObjRefEvaluationParameter::ON_ObjRefEvaluationParameter()
: m_t_type(0)
, m_reserved(0)
{
  m_t[0] = ON_UNSET_VALUE;
  m_t[1] = ON_UNSET_VALUE;
  m_t[2] = ON_UNSET_VALUE;
  m_t[3] = ON_UNSET_VALUE;
}

void ON_ObjRefEvaluationParameter::Default()
{
  ON_ObjRefEvaluationParameter d;
  *this = d;
}

ON_ObjRefEvaluationParameter::~ON_ObjRefEvaluationParameter()
{
}

bool ON_ObjRefEvaluationParameter::Write( ON_BinaryArchive& archive ) const
{
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
  if (!rc)
    return rc;

  for(;;)
  {
    rc = archive.WriteInt(m_t_type);
    if (!rc) break;

    rc = archive.WriteComponentIndex(m_t_ci);
    if (!rc) break;

    rc = archive.WriteDouble(4,m_t);
    if (!rc) break;

    rc = archive.WriteInterval(m_s[0]);
    if (!rc) break;

    rc = archive.WriteInterval(m_s[1]);
    if (!rc) break;

    rc = archive.WriteInterval(m_s[2]);
    if (!rc) break;

    break;
  }

  if ( !archive.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

bool ON_ObjRefEvaluationParameter::Read( ON_BinaryArchive& archive )
{
  Default();

  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if (!rc)
    return rc;

  for(;;)
  {
    rc = (1 == major_version);
    if (!rc) break;

    rc = archive.ReadInt(&m_t_type);
    if (!rc) break;

    rc = archive.ReadComponentIndex(m_t_ci);
    if (!rc) break;

    rc = archive.ReadDouble(4,m_t);
    if (!rc) break;

    rc = archive.ReadInterval(m_s[0]);
    if (!rc) break;

    rc = archive.ReadInterval(m_s[1]);
    if (!rc) break;

    rc = archive.ReadInterval(m_s[2]);
    if (!rc) break;

    break;
  }

  if ( !archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

ON_ObjRef::ON_ObjRef() 
          : m_uuid(ON_nil_uuid),
            m_geometry(0),
            m_parent_geometry(0),
            m_geometry_type(ON::unknown_object_type),
            m_runtime_sn(0),
            m_point(ON_3dPoint::UnsetPoint),
            m_osnap_mode(ON::os_none),
            m__proxy1(0),
            m__proxy2(0),
            m__proxy_ref_count(0)
{
}

void ON_ObjRef::Destroy()
{
  DecrementProxyReferenceCount();
  m_uuid = ON_nil_uuid;
  m_geometry = 0;
  m_parent_geometry = 0;
  m_geometry_type = ON::unknown_object_type;
  m_runtime_sn = 0;
  m_point = ON_3dPoint::UnsetPoint;
  m_osnap_mode = ON::os_none;
  m__proxy1 = 0;
  m__proxy2 = 0;
  m__proxy_ref_count = 0;
}


ON_ObjRef::ON_ObjRef( const ON_ObjRef& src ) 
          : m_uuid(src.m_uuid),
            m_geometry(src.m_geometry),
            m_parent_geometry(src.m_parent_geometry),
            m_component_index(src.m_component_index),
            m_geometry_type(src.m_geometry_type),
            m_runtime_sn(src.m_runtime_sn),
            m_point(src.m_point),
            m_osnap_mode(src.m_osnap_mode),
            m_evp(src.m_evp),
            m__iref(src.m__iref),
            m__proxy1(src.m__proxy1),
            m__proxy2(src.m__proxy2),
            m__proxy_ref_count(src.m__proxy_ref_count)
{
  if ( m__proxy_ref_count && *m__proxy_ref_count > 0 )
  {
    *m__proxy_ref_count = *m__proxy_ref_count + 1;
  }
}

ON_ObjRef& ON_ObjRef::operator=( const ON_ObjRef& src ) 
{
  if ( this != &src )
  {
    // Remove any reference this ON_ObjRef class 
    // may currently have.
    DecrementProxyReferenceCount();

    // copy the values from src
    m_uuid = src.m_uuid;
    m_geometry = src.m_geometry;
    m_parent_geometry = src.m_parent_geometry;
    m_component_index = src.m_component_index;
    m_geometry_type = src.m_geometry_type;
    m_runtime_sn = src.m_runtime_sn;
    m_point = src.m_point;
    m_osnap_mode = src.m_osnap_mode;
    m_evp = src.m_evp;
    m__iref = src.m__iref;
    m__proxy1 = src.m__proxy1;
    m__proxy2 = src.m__proxy2;
    m__proxy_ref_count = src.m__proxy_ref_count;

    if ( m__proxy_ref_count && *m__proxy_ref_count > 0 )
    {
      *m__proxy_ref_count = *m__proxy_ref_count + 1;
    }
  }

  return *this;
}

bool ON_ObjRef_IRefID::Write( ON_BinaryArchive& archive ) const
{
  bool rc = archive.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 1, 1 );
  if ( !rc )
    return false;

  for(;;)
  {
    rc = archive.WriteUuid(m_iref_uuid);
    if (!rc) break;

    rc = archive.WriteXform(m_iref_xform);
    if (!rc) break;

    rc = archive.WriteUuid(m_idef_uuid);
    if (!rc) break;

    rc = archive.WriteInt(m_idef_geometry_index);
    if (!rc) break;

    // 13 July 2006 - 1.1 - added m_component_index and m_evp
    rc = archive.WriteComponentIndex(m_component_index);
    if (!rc) break;

    rc = m_evp.Write(archive);
    if (!rc) break;

    break;
  }

  if ( !archive.EndWrite3dmChunk() )
    rc = false;
  return rc;
}

bool ON_ObjRef_IRefID::Read( ON_BinaryArchive& archive )
{
  Default();

  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk( 
                          TCODE_ANONYMOUS_CHUNK, 
                          &major_version, 
                          &minor_version );
  if ( !rc )
    return false;

  for(;;)
  {
    rc = (1 == major_version);
    if (!rc) break;

    rc = archive.ReadUuid(m_iref_uuid);
    if (!rc) break;

    rc = archive.ReadXform(m_iref_xform);
    if (!rc) break;

    rc = archive.ReadUuid(m_idef_uuid);
    if (!rc) break;

    rc = archive.ReadInt(&m_idef_geometry_index);
    if (!rc) break;

    if ( minor_version >= 1 )
    {
      // 13 July 2006 - 1.1 - added m_component_index and m_evp
      rc = archive.ReadComponentIndex(m_component_index);
      if (!rc) break;

      rc = m_evp.Read(archive);
      if (!rc) break;
    }

    break;
  }

  if ( !archive.EndRead3dmChunk() )
    rc = false;
  return rc;
}


bool ON_ObjRef::Write( ON_BinaryArchive& archive ) const
{
  bool rc = archive.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 1, 3 );
  if ( !rc )
    return false;

  for(;;)
  {
    rc = archive.WriteUuid(m_uuid);
    if (!rc) break;

    rc = archive.WriteComponentIndex(m_component_index);
    if (!rc) break;

    rc = archive.WriteInt(m_geometry_type);
    if (!rc) break;

    // Do not save the value of m_runtime_sn in the
    // archive.  When the file is read in, the object
    // will have a different value of m_runtime_sn.

    rc = archive.WritePoint(m_point);
    if (!rc) break;

    // Prior to 13 July 2006, the evaluation parameters
    // m_evp were members of ON_ObjRef.  That's why the
    // m_evp fields are written directly rather than
    // using m_evp.Write().
    rc = archive.WriteInt(m_evp.m_t_type);
    if (!rc) break;

    rc = archive.WriteComponentIndex(m_evp.m_t_ci);
    if (!rc) break;

    rc = archive.WriteDouble(4,m_evp.m_t);
    if (!rc) break;

    rc = archive.WriteArray(m__iref);
    if (!rc) break;

    // 1.1 IO fields
    rc = archive.WriteInterval(m_evp.m_s[0]);
    if (!rc) break;

    rc = archive.WriteInterval(m_evp.m_s[1]);
    if (!rc) break;

    // 1.2 IO fields
    rc = archive.WriteInterval(m_evp.m_s[2]);
    if (!rc) break;

    // 1.3 IO fields
    rc = archive.WriteInt((int)m_osnap_mode);
    if (!rc) break;

    break;
  }

  if ( !archive.EndWrite3dmChunk() )
    rc = false;
  return rc;
}

bool ON_ObjRef::Read( ON_BinaryArchive& archive )
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version );
  if ( !rc )
    return false;

  for(;;)
  {
    rc = (1 == major_version);
    if (!rc) break;

    rc = archive.ReadUuid(m_uuid);
    if (!rc) break;

    rc = archive.ReadComponentIndex(m_component_index);
    if (!rc) break;

    rc = archive.ReadInt(&m_geometry_type);
    if (!rc) break;

    rc = archive.ReadPoint(m_point);
    if (!rc) break;

    // Prior to 13 July 2006, the evaluation parameters
    // m_evp were members of ON_ObjRef.  That's why the
    // m_evp fields are read directly rather than
    // using m_evp.Read().
    rc = archive.ReadInt(&m_evp.m_t_type);
    if (!rc) break;

    rc = archive.ReadComponentIndex(m_evp.m_t_ci);
    if (!rc) break;

    rc = archive.ReadDouble(4,m_evp.m_t);
    if (!rc) break;

    rc = archive.ReadArray(m__iref);
    if (!rc) break;

    if ( minor_version >= 1 )
    {
      // 1.1 IO fields
      rc = archive.ReadInterval(m_evp.m_s[0]);
      if (!rc) break;
      rc = archive.ReadInterval(m_evp.m_s[1]);
      if (!rc) break;
      if ( minor_version >= 2 )
      {
        rc = archive.ReadInterval(m_evp.m_s[2]);
        if (!rc) break;
        if (minor_version >= 3)
        {
          int osmode = 0;
          rc = archive.ReadInt(&osmode);
          if (!rc) break;
          m_osnap_mode = ON::OSnapMode(osmode);
        }
      }
    }

    break;
  }

  if ( !archive.EndRead3dmChunk() )
    rc = false;
  return rc;
}


ON_ObjRef::~ON_ObjRef()
{
  DecrementProxyReferenceCount();
}


void ON_ObjRef::RemapObjectId( const ON_SimpleArray<ON_UuidPair>& id_remap )
{
  // The cast is a lie but it works because ON_UuidPair::CompareFirstUuid
  // looks for an id in the first 16 bytes of the ON_UuidPair.
  int i = id_remap.BinarySearch((const ON_UuidPair*)&m_uuid,ON_UuidPair::CompareFirstUuid);
  if ( i >= 0 )
    m_uuid = id_remap[i].m_uuid[1];
}

int ON_ObjRef::ProxyReferenceCount() const
{
  return m__proxy_ref_count ? *m__proxy_ref_count : 0;
}

const ON_Brep* ON_BrepParent( const ON_Geometry* geo )
{
  const ON_Brep* brep = 0;

  if ( geo == nullptr )
    return nullptr;

  if  ( ON::brep_object == geo->ObjectType() )
  {
    brep = ON_Brep::Cast(geo);
  }
  else
  {
    // ComponentIndex() is the fastest way
    switch( geo->ComponentIndex().m_type )
    {
    case ON_COMPONENT_INDEX::brep_edge:
      {
        const ON_BrepEdge* edge = ON_BrepEdge::Cast(geo);
        if ( edge )
          brep = edge->Brep();
      }
      break;

    case ON_COMPONENT_INDEX::brep_face:
      {
        const ON_BrepFace* face = ON_BrepFace::Cast(geo);
        if ( face )
          brep = face->Brep();
      }
      break;

    case ON_COMPONENT_INDEX::brep_trim:
      {
        const ON_BrepTrim* trim = ON_BrepTrim::Cast(geo);
        if ( trim )
          brep = trim->Brep();
      }
      break;

    case ON_COMPONENT_INDEX::brep_loop:
      {
        const ON_BrepLoop* loop = ON_BrepLoop::Cast(geo);
        if ( loop )
          brep = loop->Brep();
      }
      break;

    default:
      // intentionally skipping other ON_COMPONENT_INDEX::TYPE enum values
      break;
    }
  }

  return brep;
}


const ON_Mesh* ON_MeshParent( const ON_Geometry* geo )
{
  const ON_Mesh* mesh = 0;

  if ( geo == nullptr )
    return nullptr;

  if  ( ON::mesh_object == geo->ObjectType() )
  {
    mesh = ON_Mesh::Cast(geo);
  }
  else if ( geo->ComponentIndex().IsMeshComponentIndex() )
  {
    const ON_MeshComponentRef* cref = ON_MeshComponentRef::Cast(geo);
    if ( cref )
      mesh = cref->Mesh();
  }

  return mesh;
}

bool ON_ObjRef::SetParentIRef( const ON_InstanceRef& iref,
                               ON_UUID iref_id,
                               int idef_geometry_index
                               )
{
  bool rc = false;

  if ( m__iref.Count() > 0 )
  {
    // nested irefs
    if (    0 == m__proxy2
         || 0 == m__proxy_ref_count 
         || *m__proxy_ref_count <= 0 )
    {
      return false;
    }
    ON_Geometry* proxy_geo = ON_Geometry::Cast(m__proxy2);
    if ( !proxy_geo )
      return false;
    if ( !proxy_geo->Transform(iref.m_xform) )
      return false;
    rc = true;
  }
  else if ( ON_COMPONENT_INDEX::invalid_type == m_component_index.m_type )
  {
    // handle top level objects    
    while ( m__proxy1 || m__proxy2 || m__proxy_ref_count )
    {
      // It it's an brep proxy for an extrusion object, then keep going.
      if (    0 != m__proxy1
           && 0 == m__proxy2 
           && 0 != m__proxy_ref_count 
           && 1 == *m__proxy_ref_count 
           && m__proxy1 != m_geometry
           && 0 != ON_Brep::Cast(m_geometry)
           )
      {
        // 13 July 2011 - Part of the fix for bug 87827
        // is to break here instead of returning false
        // because we have something like a brep proxy 
        // of an extrusion.
        break;        
      }
      return false;
    }

    if ( !m_geometry )
    {
      return false;
    }
    if ( m_geometry->ComponentIndex().m_type != ON_COMPONENT_INDEX::invalid_type )
    {
      return false;
    }
    if ( m_parent_geometry && m_geometry != m_parent_geometry )
    {
      return false;
    }
    ON_Geometry* proxy_geo = m_geometry->Duplicate();
    if ( !proxy_geo->Transform(iref.m_xform) )
    {
      delete proxy_geo;
      return false;
    }

    // 24 June 2024, Mikko, RH-82669:
    // Flip brep/mesh/SubD if the xform is orientation reversing.
    if (-1 == iref.m_xform.IsSimilarity())
    {
      switch (proxy_geo->ObjectType())
      {
      case ON::object_type::brep_object:
      {
        ON_Brep* brep = ON_Brep::Cast(proxy_geo);
        if (0 != brep)
          brep->Flip();
      }
      break;

      case ON::object_type::mesh_object:
      {
        ON_Mesh* mesh = ON_Mesh::Cast(proxy_geo);
        if (0 != mesh)
          mesh->Flip();
      }
      break;

      case ON::object_type::subd_object:
      {
        ON_SubD* subd = ON_SubD::Cast(proxy_geo);
        if (0 != subd)
          subd->ReverseOrientation();
      }
      break;

      default:
        break;
      }
    }

    // 13 July 2011 - Part of the fix for bug 87827
    // was to put the m_geometry and m_parent_geometry
    // assignments after the call to SetProxy() which
    // was zeroing m_geometry and m_parent_geometry.
    SetProxy(0,proxy_geo,true);
    m_geometry = proxy_geo;
    m_parent_geometry = proxy_geo;
    rc = true;
  }
  else
  {
    // handle brep and mesh subobjects
    // create proxy object
    if ( m__proxy2 )
      return false;

    const ON_Brep* parent_brep = ON_BrepParent(m_parent_geometry);
    if ( !parent_brep)
      parent_brep = ON_BrepParent(m_geometry);
    if ( parent_brep )
    {
      // handle breps and their parts

      // 6 June 2013, Mikko, RH-9846:
      // This is a near facsimile of the 87827 fix above.
      // If it's a brep proxy component for an extrusion object, then keep going.
      if (    0 != m__proxy1
           && 0 == m__proxy2 
           && 0 != m__proxy_ref_count 
           && 1 == *m__proxy_ref_count 
           && m__proxy1 != m_geometry
           && m_geometry->ComponentIndex().IsBrepComponentIndex()
           )
      {
        // brep proxy component for an extrusion object, keep going
      }
      else
      if ( m__proxy1 || m__proxy_ref_count )
      {
        return false;
      }
      if ( m_parent_geometry != parent_brep && 0 != m_parent_geometry )
      {
        return false;
      }
      if ( m_geometry != parent_brep->BrepComponent(m_component_index) )
      {
        return false;
      }
      ON_Brep* proxy_brep = parent_brep->Duplicate();
      if ( !proxy_brep->Transform(iref.m_xform) )
      {
        delete proxy_brep;
        return false;
      }
      const ON_Geometry* brep_component = proxy_brep->BrepComponent(m_component_index);
      if ( !brep_component )
      {
        delete brep_component;
        return false;
      }
      SetProxy(0,proxy_brep,true);
      m_geometry        = brep_component;
      m_parent_geometry = proxy_brep;
      rc = true;
    }
    else
    {
      const ON_Mesh* parent_mesh = ON_MeshParent(m_parent_geometry);
      if ( !parent_mesh)
        parent_mesh = ON_MeshParent(m_geometry);
      if ( parent_mesh  )
      {
        // handle meshes and their parts
        if ( m_component_index.IsMeshComponentIndex() )
        {
          if ( m_geometry->ComponentIndex() != m_component_index )
            return false;
          ON_Mesh* proxy_mesh = parent_mesh->Duplicate();
          if ( !proxy_mesh->Transform(iref.m_xform) )
          {
            delete proxy_mesh;
            return false;
          }
          ON_Geometry* proxy_component = proxy_mesh->MeshComponent(m_component_index);
          if( !proxy_component )
          {
            delete proxy_mesh;
            return false;
          }
          m_geometry = proxy_component;
          m_parent_geometry = proxy_mesh;
          SetProxy(proxy_component,proxy_mesh,true);
          rc = true;
        }
        else
        {
          return false;
        }
      }
    }
  }

  if ( rc )
  {
    // This is a valid reference to a piece of geometry
    // in an instance definition.

    ON_Xform geometry_xform(ON_Xform::IdentityTransformation);
    if ( m__iref.Count() > 0 )
      geometry_xform = m__iref.Last()->m_geometry_xform;

    ON_ObjRef_IRefID& this_ref     = m__iref.AppendNew();
    this_ref.m_iref_uuid           = iref_id;
    this_ref.m_iref_xform          = iref.m_xform;
    this_ref.m_idef_uuid           = iref.m_instance_definition_uuid;
    this_ref.m_idef_geometry_index = idef_geometry_index;
    this_ref.m_geometry_xform      = iref.m_xform*geometry_xform;

    m_uuid = this_ref.m_iref_uuid;
  }

  return rc;
}

const ON_Object* ON_ObjRef::ProxyObject(int proxy_object_index) const
{
  return ( (1 == proxy_object_index) 
           ? m__proxy1 
           : ((2==proxy_object_index) ? m__proxy2 : 0) 
         );
}

void ON_ObjRef::SetProxy( 
          ON_Object* proxy1, 
          ON_Object* proxy2, 
          bool bCountReferences 
          )
{
  if ( m__proxy1 || m__proxy2 || m__proxy_ref_count )
  {
    // Remove any reference this ON_ObjRef class 
    // may currently have.
    DecrementProxyReferenceCount();
  }

  m__proxy1 = proxy1;
  m__proxy2 = proxy2;
  if ( bCountReferences && (m__proxy1 || m__proxy2) )
  {
    m__proxy_ref_count = (int*)onmalloc( sizeof(*m__proxy_ref_count) );
    *m__proxy_ref_count = 1;
  }
}

void ON_ObjRef::DecrementProxyReferenceCount()
{
  if ( 0 != m__proxy_ref_count ) 
  {
    if (*m__proxy_ref_count > 1) 
    {
      // Including this class, there are *m__proxy_ref_count
      // ON_ObjRef classes using m__proxy and m_geometry.
      // Decrement the reference counter and set the
      // pointers to zero.
      *m__proxy_ref_count = *m__proxy_ref_count - 1;
    }
    else if ( 1 == *m__proxy_ref_count )
    {
      // This is the only ON_ObjRef class using
      // m__proxy and m_geometry.  Set *m__proxy_ref_count
      // to zero (in case some rogue reference still exists),
      // delete m__proxy and m__proxy_ref_count, and
      // set m_geometry (which points to some part of m__proxy)
      // to nullptr.

      // Setting *m__proxy_ref_count to zero, prevents crashes
      // if somebody incorrectly uses memcpy() instead of the 
      // copy constructor or operator= to duplicate this class.
      *m__proxy_ref_count = 0;
      if ( m__proxy1 )
      {
        // delete proxy geometry
        delete m__proxy1;
      }
      if ( m__proxy2 )
      {
        // delete proxy geometry
        delete m__proxy2;
      }
      onfree(m__proxy_ref_count);
    }
    else
    {
      // Somebody did something along the lines of using
      // memcpy() instead of the copy constructor or operator=
      // to duplicate this class.
      ON_ERROR("ON_ObjRef::DecrementReferenceCount() *m__proxy_ref_count <= 0");
    }
  }

  // In all cases, setting these pointers to zero indicates this
  // ON_ObjRef is no longer referencing any runtime geometry.
  m__proxy_ref_count = 0;
  m__proxy1 = 0;
  m__proxy2 = 0;
  m_geometry = 0;
}

void ON_ObjRef_IRefID::Default()
{
  ON_ObjRef_IRefID d;
  *this = d;
}
