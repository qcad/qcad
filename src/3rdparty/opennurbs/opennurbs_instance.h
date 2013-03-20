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

#if !defined(OPENNURBS_INSTANCE_INC_)
#define OPENNURBS_INSTANCE_INC_

/*
Description:
  An ON_InstanceDefinition defines the geometry used by 
  instance references.
See Also:
  ON_InstanceRef
*/
class ON_CLASS ON_InstanceDefinition : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_InstanceDefinition);

public:

  // IDEF_UPDATE_TYPE lists the possible relationships between
  // the instance definition geometry and the archive 
  // (m_source_archive) containing the original defition.
  enum IDEF_UPDATE_TYPE
  {
    static_def = 0,   // This instance definition is never updated.
                      // If m_source_archive is set, it records the
                      // origin of the instance definition geometry
                      // and, but m_source_archive is never used
                      // to update the instance definition
    embedded_def = 1, // This instance definition geometry was
                      // imported from another archive (m_source_archive)
                      // and is embedded. If m_source_archive changes,
                      // the user is asked if they want to update
                      // the instance definition.
    linked_and_embedded_def = 2,
                      // This instance definition geometry was
                      // imported from another archive (m_source_archive)
                      // and is embedded. If m_source_archive changes,
                      // the instance definition is automatically updated.
                      // If m_source_archive is not available, the
                      // instance definition is still valid.
    linked_def = 3,   // This instance definition geometry was
                      // imported from another archive (m_source_archive)
                      // and is not embedded. If m_source_archive changes,
                      // the instance definition is automatically updated.
                      // If m_source_archive is not available, the
                      // instance definition is not valid.
                      // This does not save runtime memory.  It may
                      // save a little disk space, but it is a 
                      // foolish option requested by people who do not 
                      // understand all the issues.
    force_32bit_idef_update_type = 0xFFFFFFFF
  };

  static IDEF_UPDATE_TYPE IdefUpdateType(int i);

  // Bits that identify subsets of the instance defintion
  // fields. These bits are used to determine which fields to
  // set when an ON_InstanceDefinition class is used to
  // modify an existing instance definition.
  enum
  {
    no_idef_settings            =    0,
    idef_name_setting           =    1,  // m_name
    idef_description_setting    =    2,  // m_description
    idef_url_setting            =    4,  // all m_url_* fields
    idef_units_setting          =    8,  // m_us and m_unit_scale
    idef_source_archive_setting = 0x10,  // all m_source_* fields
    idef_userdata_setting       = 0x20,  // all m_source_* fields
    all_idef_settings           = 0xFFFFFFFF
  };

public:
  ON_InstanceDefinition();
  ~ON_InstanceDefinition();

  // virtual ON_Object overrides
  ON_BOOL32 IsValid( ON_TextLog* text_log = NULL ) const;
  ON_BOOL32 Write(
         ON_BinaryArchive& binary_archive
       ) const;
  ON_BOOL32 Read(
         ON_BinaryArchive& binary_archive
       );
  ON::object_type ObjectType() const;
  unsigned int SizeOf() const;

  // virtual ON_Geometry overrides
  int Dimension() const;
  ON_BOOL32 GetBBox(
         double* boxmin,
         double* boxmax,
         int bGrowBox = false
         ) const;
  ON_BOOL32 Transform( 
         const ON_Xform& xform
         );

  // virtual
  ON_UUID ModelObjectId() const;

  // Interface
  const wchar_t* Name() const;
  void SetName( const wchar_t* name );

  const wchar_t* Description() const;
  void SetDescription( const wchar_t* description );

  const wchar_t* URL() const;
  void SetURL( const wchar_t* url );

  const wchar_t* URL_Tag() const;
  void SetURL_Tag( const wchar_t* url_tag );

  ON_UUID Uuid() const;
  void SetUuid( ON_UUID uuid );

  void SetBoundingBox( ON_BoundingBox bbox );

  // list of object ids in the instance geometry table.
  ON_SimpleArray<ON_UUID> m_object_uuid;

  /*
  Description:
    If the instance definition is linked or embedded, use
    SetSource to specify the source archive.
  Parameters:
    source_archive - [in] name of source archive
    checksum - [in] check sum used to detect changed
    source_type - [in] See comments for ON_InstanceDefinition::IDEF_UPDATE_TYPE
  Remarks:
    In all cases, the complete instance definition geometry
    is stored in the 3dm archive.  When an instance definition
    is linked or embedded, applications can examine the source
    archive settings and update the  definition when appropriate.
    The checksum can be used to detect changed files.
  */
  void SetSourceArchive( 
        const wchar_t* source_archive, 
        ON_CheckSum checksum,
        IDEF_UPDATE_TYPE update_type
        );

  /*
  Returns:
    Name of source archive.
  */
  const wchar_t* SourceArchive() const;

  /*
  Returns:
    Check sum of source archive.
  */
  ON_CheckSum SourceArchiveCheckSum() const;

  const ON_UnitSystem& UnitSystem() const;

  /*
  Description:
    Sets m_us and m_unit_scale.
  */
  void SetUnitSystem( ON::unit_system us );
  void SetUnitSystem( const ON_UnitSystem& us );

public:

  ON_UUID m_uuid;     // unique id for this instance definition
  ON_wString m_name;  // The "name" is for human comfort.  
                      // It can be empty and duplicates
                      // may exist. Instance reference use
                      // m_uuid to find instance definitions.
  ON_wString m_description; 

  ON_wString m_url;
  ON_wString m_url_tag;     // UI link text for m_url

  ON_BoundingBox m_bbox;

  ON_UnitSystem  m_us;
  
  IDEF_UPDATE_TYPE m_idef_update_type; 

  int m_idef_update_depth; // Controls how much geometry is read when
                           // a linked idef is updated.
                           //   0: read everything, included nested linked idefs
                           //   1: skip nested linked idefs.

  ON_wString m_source_archive;   // filename used to update idef 
                                 // (it can be empty or relative)
  bool m_source_bRelativePath;  // True if the filename in m_source_archive is
                                 // a relative the location of the 3dm file
                                 // containing this instance definition.

  ON_CheckSum m_source_archive_checksum; // used to detect when idef is out of
                                         // synch with source archive.
};


/*
Description:
  An ON_InstanceRef is a reference to an instance definition
  along with transformation to apply to the definition.
See Also:
  ON_InstanceRef
*/
class ON_CLASS ON_InstanceRef : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_InstanceRef);

public:
  ON_InstanceRef();

  /////////////////////////////////////////////////////////////
  //
  // virtual ON_Object overrides
  //
  ON_BOOL32 IsValid( ON_TextLog* text_log = NULL ) const;
  ON_BOOL32 Write(
         ON_BinaryArchive& binary_archive
       ) const;
  ON_BOOL32 Read(
         ON_BinaryArchive& binary_archive
       );
  ON::object_type ObjectType() const;

  /////////////////////////////////////////////////////////////
  //
  // virtual ON_Geometry overrides
  //
  int Dimension() const;
  ON_BOOL32 GetBBox(
         double* boxmin,
         double* boxmax,
         int bGrowBox = false
         ) const;
  ON_BOOL32 Transform( 
         const ON_Xform& xform
         );

  // virtual ON_Geometry::IsDeformable() override
  bool IsDeformable() const;

  // virtual ON_Geometry::MakeDeformable() override
  bool MakeDeformable();

  /////////////////////////////////////////////////////////////
  //

  // Unique id of the instance definition (ON_InstanceDefinition) 
  // in the instance definition table that defines the geometry
  // used by this reference.
  ON_UUID m_instance_definition_uuid;

  // Transformation for this reference.
  ON_Xform m_xform;

  // Bounding box for this reference.
  ON_BoundingBox m_bbox;

  // Tolerance to use for flagging instance xforms
  // as singular.
  static const double m_singular_xform_tol;
};

#endif
