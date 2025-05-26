/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#include "opennurbs.h"


ON_OBJECT_IMPLEMENT( ON_InstanceDefinition, ON_Geometry, "26F8BFF6-2618-417f-A158-153D64A94989" );

ON_InstanceDefinition::ON_InstanceDefinition()
{
  m_uuid = ON_nil_uuid;
  m_idef_update_type = ON_InstanceDefinition::static_def;
  m_idef_update_depth = 0;
  m_us.m_unit_system = ON::no_unit_system;
  m_us.m_custom_unit_scale = 0.0;
  m_us.m_custom_unit_name.Destroy();
  m_source_bRelativePath = false;
}

ON_InstanceDefinition::~ON_InstanceDefinition()
{
}

ON_BOOL32 ON_InstanceDefinition::IsValid( ON_TextLog* text_log ) const
{
  if ( 0 == ON_UuidCompare( m_uuid, ON_nil_uuid) )
  {
    if (text_log)
    {
      text_log->Print("ON_InstanceDefinition has nil uuid.\n");
    }
    return false;
  }
  if ( !m_bbox.IsValid() )
  {
    if (text_log)
    {
      text_log->Print("ON_InstanceDefinition has invalid bounding box.\n");
    }
    return false;
  }
  switch( m_idef_update_type)
  {
    case embedded_def:
    case linked_def:
    case linked_and_embedded_def:
      if( m_source_archive.IsEmpty())
      {
        if (text_log)
        {
          text_log->Print("ON_InstanceDefinition is linked or embedded but m_source_archive is empty.\n");
        }
        return false;
      }
      break;
    default:
      // do nothing on rest of cases
      break;
  }

  // TODO
  return true;
}


unsigned int ON_InstanceDefinition::SizeOf() const
{
  unsigned int sz = sizeof(*this) - sizeof(ON_Geometry);
  sz += ON_Geometry::SizeOf();
  sz += this->m_object_uuid.SizeOfArray();
  sz += this->m_name.SizeOf();
  sz += this->m_description.SizeOf();
  sz += this->m_url.SizeOf();
  sz += this->m_url_tag.SizeOf();
  sz += this->m_source_archive.SizeOf();
  return sz;
}


ON_BOOL32 ON_InstanceDefinition::Write(
       ON_BinaryArchive& binary_archive
     ) const
{
  bool rc = binary_archive.Write3dmChunkVersion(1,5);

  // version 1.0 fields
  if ( rc )
    rc = binary_archive.WriteUuid( m_uuid );
  if ( rc )
  {
    if (    binary_archive.Archive3dmVersion() >= 4
         && ON_InstanceDefinition::linked_def == m_idef_update_type )
    {
      // linked instance definition geometry is never in the file
      ON_SimpleArray<ON_UUID> empty_uuid_list;
      rc = binary_archive.WriteArray( empty_uuid_list );
    }
    else
    {
      rc = binary_archive.WriteArray( m_object_uuid );
    }
  }
  if ( rc )
    rc = binary_archive.WriteString( m_name );
  if ( rc )
    rc = binary_archive.WriteString( m_description );
  if ( rc )
    rc = binary_archive.WriteString( m_url );
  if ( rc )
    rc = binary_archive.WriteString( m_url_tag );
  if ( rc )
    rc = binary_archive.WriteBoundingBox( m_bbox );
  // m_idef_update_type was an unsigned int and got changed to an enum.  Read and write
  // as an unsigned int to support backwards compatibility
  if ( rc )
    rc = binary_archive.WriteInt( (unsigned int)m_idef_update_type );
  if ( rc )
    rc = binary_archive.WriteString( m_source_archive );
  
  // version 1.1 fields
  if (rc)
    rc = m_source_archive_checksum.Write( binary_archive );
  
  // version 1.2 fields
  if (rc)
    rc = binary_archive.WriteInt( m_us.m_unit_system );

  // version 1.3 fields - added 6 March 2006
  if (rc)
    rc = binary_archive.WriteDouble( m_us.m_custom_unit_scale );

  if ( rc )
    rc = binary_archive.WriteBool( m_source_bRelativePath );

  // version 1.4 fields
  if (rc)
    rc = m_us.Write(binary_archive);

  // version 1.5 fields
  if (rc)
    rc = binary_archive.WriteInt(m_idef_update_depth);

  return rc;
}


ON_InstanceDefinition::IDEF_UPDATE_TYPE ON_InstanceDefinition::IdefUpdateType(int i)
{
  IDEF_UPDATE_TYPE t;
  switch(i)
  {
  case ON_InstanceDefinition::static_def:
    t = ON_InstanceDefinition::static_def;
    break;
  case ON_InstanceDefinition::embedded_def:
    t = ON_InstanceDefinition::embedded_def;
    break;
  case ON_InstanceDefinition::linked_and_embedded_def:
    t = ON_InstanceDefinition::linked_and_embedded_def;
    break;
  case ON_InstanceDefinition::linked_def:
    t = ON_InstanceDefinition::linked_def;
    break;
  default:
    t = ON_InstanceDefinition::static_def;
    break;
  }
  return t;
}


ON_BOOL32 ON_InstanceDefinition::Read(
       ON_BinaryArchive& binary_archive
     )
{
  int major_version = 0;
  int minor_version = 0;

  m_us.m_custom_unit_scale = 0.0;
  m_us.m_custom_unit_name.Destroy();
  m_us.m_unit_system = ON::no_unit_system;
  m_source_bRelativePath = false;
  m_source_archive.Destroy();

  bool rc = binary_archive.Read3dmChunkVersion(&major_version,&minor_version);
  if ( rc )
  {
    if ( major_version != 1 )
      rc = false;
    // version 1.0 fields
    if ( rc )
      rc = binary_archive.ReadUuid( m_uuid );
    if ( rc )
      rc = binary_archive.ReadArray( m_object_uuid );
    if ( rc )
      rc = binary_archive.ReadString( m_name );
    if ( rc )
      rc = binary_archive.ReadString( m_description );
    if ( rc )
      rc = binary_archive.ReadString( m_url );
    if ( rc )
      rc = binary_archive.ReadString( m_url_tag );
    if ( rc )
      rc = binary_archive.ReadBoundingBox( m_bbox );
    // m_idef_update_type was an unsigned int and got changed to an enum.  Read and write
    // as an unsigned int to support backwards compatibility
    unsigned int source = m_idef_update_type;
    if ( rc )
      rc = binary_archive.ReadInt( &source );
    if( rc)
      m_idef_update_type = ON_InstanceDefinition::IdefUpdateType(source);
    if ( rc )
      rc = binary_archive.ReadString( m_source_archive );

    // version 1.1 fields
    if ( minor_version >= 1 )
    {
      if ( rc )
        rc = m_source_archive_checksum.Read( binary_archive );
    }

    // version 1.2 fields
    if ( minor_version >= 2 )
    {
      int us = ON::no_unit_system;
      if ( rc )
        rc = binary_archive.ReadInt( &us );
      m_us.m_unit_system = ON::UnitSystem(us);
      if ( ON::custom_unit_system != m_us.m_unit_system && ON::no_unit_system != m_us.m_unit_system )
      {
        m_us.m_custom_unit_scale = ON::UnitScale( m_us.m_unit_system, ON::meters );
      }
      else
      {
        m_us.m_custom_unit_scale = 0.0;
      }

      if ( minor_version >= 3 )
      {
        // version 1.3 fields - added 6 March 2006
        //int us = ON::no_unit_system;
        if ( rc )
          rc = binary_archive.ReadDouble( &m_us.m_custom_unit_scale );
        if ( rc )
          rc = binary_archive.ReadBool( &m_source_bRelativePath );
        if ( rc && minor_version >= 4 )
        {
          rc = m_us.Read(binary_archive);
          if (rc && minor_version >= 5 )
          {
            rc = binary_archive.ReadInt(&m_idef_update_depth);
          }
        }
      }
    }
  }
  return rc;
}

ON::object_type ON_InstanceDefinition::ObjectType() const
{
  return ON::instance_definition;
}


// virtual ON_Geometry overrides
int ON_InstanceDefinition::Dimension() const
{
  return 3;
}

ON_BOOL32 ON_InstanceDefinition::GetBBox(
       double* boxmin,
       double* boxmax,
       ON_BOOL32 bGrowBox
       ) const
{
  if ( boxmin )
  {
    boxmin[0] = m_bbox.m_min.x;
    boxmin[1] = m_bbox.m_min.y;
    boxmin[2] = m_bbox.m_min.z;
  }
  if ( boxmax )
  {
    boxmax[0] = m_bbox.m_max.x;
    boxmax[1] = m_bbox.m_max.y;
    boxmax[2] = m_bbox.m_max.z;
  }
  return m_bbox.IsValid();
}

ON_BOOL32 ON_InstanceDefinition::Transform( 
       const ON_Xform& xform
       )
{
  // instance DEFs cannot be transformed
  return false;
}

const wchar_t* ON_InstanceDefinition::Name() const
{
  return m_name;
}

void ON_InstanceDefinition::SetName( const wchar_t* name )
{
  m_name = name;
  m_name.TrimLeft();
  m_name.TrimRight();
}


const wchar_t* ON_InstanceDefinition::URL() const
{
  return m_url;
}

void ON_InstanceDefinition::SetURL( const wchar_t* url )
{
  m_url = url;
  m_url.TrimLeft();
  m_url.TrimRight();
}

const wchar_t* ON_InstanceDefinition::URL_Tag() const
{
  return m_url_tag;
}

void ON_InstanceDefinition::SetURL_Tag( const wchar_t* url_tag )
{
  m_url_tag = url_tag;
  m_url_tag.TrimLeft();
  m_url_tag.TrimRight();
}

ON_UUID ON_InstanceDefinition::Uuid() const
{
  return m_uuid;
}

void ON_InstanceDefinition::SetUuid( ON_UUID uuid )
{
  m_uuid = uuid;
}

const wchar_t* ON_InstanceDefinition::Description() const
{
  return m_description;
}

void ON_InstanceDefinition::SetDescription( const wchar_t* description )
{
  m_description = description;
  m_description.TrimLeft();
  m_description.TrimRight();
}

void ON_InstanceDefinition::SetBoundingBox( ON_BoundingBox bbox )
{
  m_bbox = bbox;
}

void ON_InstanceDefinition::SetSourceArchive( const wchar_t* source_archive, 
                                              ON_CheckSum checksum,
                                              ON_InstanceDefinition::IDEF_UPDATE_TYPE idef_update_type)
{
  ON_wString s = source_archive;
  s.TrimLeftAndRight();
  m_source_archive = s;
  m_source_archive_checksum = checksum;
  if ( m_source_archive.IsEmpty() )
    m_idef_update_type = ON_InstanceDefinition::static_def;
  else
    m_idef_update_type = ON_InstanceDefinition::IdefUpdateType(idef_update_type);
}

const wchar_t* ON_InstanceDefinition::SourceArchive() const
{
  return m_source_archive;
}

ON_CheckSum ON_InstanceDefinition::SourceArchiveCheckSum() const
{
  return m_source_archive_checksum;
}

const ON_UnitSystem& ON_InstanceDefinition::UnitSystem() const
{
  return m_us;
}

void ON_InstanceDefinition::SetUnitSystem( ON::unit_system us )
{
  // make sure we are not getting garbage cast as an ON::unit_system
  if ( us == ON::UnitSystem(us) )
  {
    m_us.m_unit_system = us;
    if ( ON::custom_unit_system != m_us.m_unit_system )
    {
      m_us.m_custom_unit_scale = ( ON::no_unit_system == m_us.m_unit_system )
                               ? 0.0
                               : ON::UnitScale(ON::meters,m_us.m_unit_system);
    }
  }
}

void ON_InstanceDefinition::SetUnitSystem( const ON_UnitSystem& us )
{
  // make sure we are not getting garbage cast as an ON::unit_system
  if ( us.IsValid() )
  {
    m_us = us;
    if ( ON::custom_unit_system != m_us.m_unit_system )
    {
      m_us.m_custom_unit_scale = ( ON::no_unit_system == m_us.m_unit_system )
                               ? 0.0
                               : ON::UnitScale(ON::meters,m_us.m_unit_system);
    }
  }
}

ON_OBJECT_IMPLEMENT( ON_InstanceRef, ON_Geometry, "F9CFB638-B9D4-4340-87E3-C56E7865D96A" );

const double ON_InstanceRef::m_singular_xform_tol = 1.0e-6;

ON_InstanceRef::ON_InstanceRef()
{
  m_instance_definition_uuid = ON_nil_uuid;
  m_xform.Identity();
}

ON_BOOL32 ON_InstanceRef::IsValid( ON_TextLog* text_log ) const
{
  if ( 0 == ON_UuidCompare( m_instance_definition_uuid, ON_nil_uuid) )
  {
    if ( text_log )
      text_log->Print("ON_InstanceRef has nil m_instance_definition_uuid.\n");
    return false;
  }

  ON_Xform tmp = m_xform.Inverse()*m_xform;
  if ( !tmp.IsIdentity( ON_InstanceRef::m_singular_xform_tol ) )
  {
    if ( text_log )
      text_log->Print("ON_InstanceRef has singular m_xform.\n");
    return false;
  }
  return true;
}

ON_BOOL32 ON_InstanceRef::Write(
       ON_BinaryArchive& binary_archive
     ) const
{
  bool rc = binary_archive.Write3dmChunkVersion(1,0);
  if ( rc )
    rc = binary_archive.WriteUuid( m_instance_definition_uuid );
  if ( rc )
    rc = binary_archive.WriteXform( m_xform );
  if ( rc )
    rc = binary_archive.WriteBoundingBox( m_bbox );
  return rc;
}

ON_BOOL32 ON_InstanceRef::Read(
       ON_BinaryArchive& binary_archive
     )
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = binary_archive.Read3dmChunkVersion(&major_version,&minor_version);
  if ( rc )
  {
    if ( major_version != 1 )
      rc = false;
    if (rc )
      rc = binary_archive.ReadUuid( m_instance_definition_uuid );
    if ( rc )
      rc = binary_archive.ReadXform( m_xform );
    if ( rc )
      rc = binary_archive.ReadBoundingBox( m_bbox );
  }
  return rc;
}

ON::object_type ON_InstanceRef::ObjectType() const
{
  return ON::instance_reference;
}


// virtual ON_Geometry overrides
int ON_InstanceRef::Dimension() const
{
  return 3;
}

ON_BOOL32 ON_InstanceRef::GetBBox(
       double* boxmin,
       double* boxmax,
       ON_BOOL32 bGrowBox
       ) const
{
  if ( !boxmin || !boxmax )
  {
    bGrowBox = false;
  }
  else if ( bGrowBox )
  {
    bGrowBox = ON_BoundingBox(ON_3dPoint(boxmin),ON_3dPoint(boxmax)).IsValid();
  }

  if( m_bbox.IsValid() )
  {
    if( bGrowBox )
    {
      if( boxmin[0] > m_bbox.m_min.x ) boxmin[0] = m_bbox.m_min.x;
      if( boxmin[1] > m_bbox.m_min.y ) boxmin[1] = m_bbox.m_min.y;
      if( boxmin[2] > m_bbox.m_min.z ) boxmin[2] = m_bbox.m_min.z;

      if( boxmax[0] < m_bbox.m_max.x ) boxmax[0] = m_bbox.m_max.x;
      if( boxmax[1] < m_bbox.m_max.y ) boxmax[1] = m_bbox.m_max.y;
      if( boxmax[2] < m_bbox.m_max.z ) boxmax[2] = m_bbox.m_max.z;
    }
    else
    {
      if( boxmin )
      {
        boxmin[0] = m_bbox.m_min.x;
        boxmin[1] = m_bbox.m_min.y;
        boxmin[2] = m_bbox.m_min.z;
      }
      if( boxmax )
      {
        boxmax[0] = m_bbox.m_max.x;
        boxmax[1] = m_bbox.m_max.y;
        boxmax[2] = m_bbox.m_max.z;
      }
      bGrowBox = true;
    }
  }

  return bGrowBox;
}

ON_BOOL32 ON_InstanceRef::Transform( 
       const ON_Xform& xform
       )
{
  ON_Geometry::Transform(xform);
  m_xform = xform*m_xform;
  m_bbox.Transform(xform);
  return true;
}

bool ON_InstanceRef::IsDeformable() const
{
  // 25 Feb 2006 Dale Lear - this seems wrong to me.
  return true;
}

bool ON_InstanceRef::MakeDeformable()
{
  // 25 Feb 2006 Dale Lear - this seems wrong to me.
  return true;
}
