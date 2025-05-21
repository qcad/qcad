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

#if !defined(OPENNURBS_INSTANCE_INC_)
#define OPENNURBS_INSTANCE_INC_

class ON_CLASS ON_ReferencedComponentSettings
{
public:
  ON_ReferencedComponentSettings() = default;
  ~ON_ReferencedComponentSettings();
  ON_ReferencedComponentSettings(const ON_ReferencedComponentSettings& src);
  ON_ReferencedComponentSettings& operator=(const ON_ReferencedComponentSettings& src);

  bool Read(
    ON_BinaryArchive& archive
  );

  bool Write(
    ON_BinaryArchive& archive
  ) const;

  bool IsEmpty() const;
  bool IsNotEmpty() const;

  bool HasLayerInformation() const;
  bool HasLayerTableInformation() const;
  bool HasParentLayerInformation() const;

  /*
  Description:
    Update runtime layer color visibility, locked, ... settings in the
    layer table read from a reference file to the values to use in the
    runtime model.
    This is typically done right after the reference file layer table is
    read and before the layers are added to the runtime model.
  Parameters:
    source_archive_manifest - [in]
      manifest of archive being read (may partially read)
    model_manifest - [in]
      manifest of runtime model (may partially created)
    layer_count - [in]
      length of layers[] array;
    layers - [in/out]
      The input values should be the layer table read from the referenced file.
      The output values have color, visibility, locked, ... settings updated
      to the state they had the last time the model file (not the referenced file)
      was saved.
    linked_definition_parent_layer - [in/out]
      If linked_definition_parent_layer is not nullptr, its color, visibility, ...
      settings are updated to the state they had the last time the model file 
      (not the referenced file) was saved.
  Remarks:
    The layer idenitification information (name, index, id) are not changed by
    this function.
  */
  void AfterReferenceLayerTableRead(
    const class ON_ComponentManifest& source_archive_manifest,
    const class ON_ComponentManifest& model_manifest,
    const class ON_ManifestMap& archive_to_model_map,
    ON_Layer* linked_definition_parent_layer,
    unsigned int layer_count,
    ON_Layer** layers
  );

  /*
  Description:
    Update the mapping from from reference file layer id to runtime model layer id.
    Typically this is done immediately after the reference file layers are added
    to the runtime model.
  Parameters:
    source_archive_manifest - [in]
      manifest of archive being read (may partially read)
    model_manifest - [in]
      manifest of runtime model (may partially created)
    archive_to_model_map - [in]
      Manifest map from reference file settings to runtime model settings.
      This map typically exists while the archive is being read and is
      destroyed after reading is complete. That's why the mapping has
      to be saved.
  */
  void AfterLayerTableAddedToModel(
    const class ON_ComponentManifest& source_archive_manifest,
    const class ON_ComponentManifest& model_manifest,
    const class ON_ManifestMap& archive_to_model_map
  );

  /*
  Description:
    Save the current runtime layer color, visibility, ... states.
    Typically this is done immediately before a linked instance definition
    or worksession reference information is written.  Calling the Write()
    function destroys the information created by BeforeWrite() because
    it is generally out-of-date if modeling resumes after writing.
  Parameters:
    model_manifest - [in]
      manifest of runtime model
    destination_archive_manifest - [in]
      manifest of archive being written (may partially written)
    model_to_archive_map - [in]
      Manifest map from model to destination_archive_manifest.
    linked_definition_parent_layer - [in]
      nullptr or the parent layer
    context - [in]
      first parameter passed to ModelLayerFromIdFunc
    ModelLayerFromIdFunc - [in]
      Function to get model layers from id
  */
  void BeforeLinkedDefinitionWrite(
    const class ON_ComponentManifest& model_manifest,
    const class ON_ComponentManifest& destination_archive_manifest,
    const class ON_ManifestMap& model_to_archive_map,
    const ON_Layer* linked_definition_parent_layer,
    void* context,
    const ON_Layer*(*ModelLayerFromIdFunc)(void* context, const ON_UUID&)
  );

private:
  class ON_ReferencedComponentSettingsImpl* Impl(
    bool bCreateIfNull
    );

  class ON_ReferencedComponentSettingsImpl* m_impl = nullptr;
};

/*
Description:
  An ON_InstanceDefinition defines the geometry used by 
  instance references.
See Also:
  ON_InstanceRef
*/
class ON_CLASS ON_InstanceDefinition : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_InstanceDefinition);

public:

  // IDEF_UPDATE_TYPE lists the possible relationships between
  // the instance definition geometry and the archive 
  // (m_source_archive) containing the original definition.
  enum class IDEF_UPDATE_TYPE : unsigned int
  {
    Unset = 0,
    Static = 1,
    LinkedAndEmbedded = 2,
    Linked = 3


    //static_def = 0,
    //embedded_def = 1,
    //  // As of 7 February, "static_def" and "embedded_def" 
    //  // and shall be treated the same. Using "static_def"
    //  // is preferred and "embedded_def" is obsolete.
    //  // The geometry for the instance definition
    //  // is saved in archives, is fixed and has no
    //  // connection to a source archive.
    //  // All source archive information should be
    //  // empty strings and m_source_archive_checksum
    //  // should be "zero".
    //linked_and_embedded_def = 2,
    //  // The geometry for the instance definition
    //  // is saved in archives.  Complete source
    //  // archive and checksum information will be 
    //  // present. The document setting 
    //  // ON_3dmIOSettings.m_idef_link_update 
    //  // determines if, when and how the instance
    //  // definition geometry is updated by reading the
    //  // source archive.
    //linked_def = 3,   
    //  // The geometry for this instance definition
    //  // is not saved in the archive that contains
    //  // this instance definition. This instance 
    //  // definition geometry is imported from a
    //  // "source archive" The "source archive" file
    //  // name and checksum information are saved
    //  // in m_source_archive and m_source_archive_checksum.
    //  // If file named in m_source_archive is not available, 
    //  // then this instance definition is not valid and any
    //  // references to it are not valid.
  };

  // Converts and integer into an IDEF_UPDATE_TYPE enum.
  static ON_InstanceDefinition::IDEF_UPDATE_TYPE InstanceDefinitionTypeFromUnsigned(
    unsigned int idef_type_as_unsigned
    );

  // Bits that identify subsets of the instance definition
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
    idef_source_archive_setting = 0x10,  // all m_source_*, layer style, update depth fields
    idef_userdata_setting       = 0x20, 
    all_idef_settings           = 0xFFFFFFFF
  };

public:
  ON_InstanceDefinition() ON_NOEXCEPT;
  ~ON_InstanceDefinition();
  ON_InstanceDefinition(const ON_InstanceDefinition&);
  ON_InstanceDefinition& operator=(const ON_InstanceDefinition&);

private:
  void Internal_Destroy();
  void Internal_Copy(const ON_InstanceDefinition& src);

public:
  
  static const ON_InstanceDefinition Unset;

  /*
  Parameters:
    model_component_reference - [in]
    none_return_value - [in]
      value to return if ON_InstanceDefinition::Cast(model_component_ref.ModelComponent())
      is nullptr
  Returns:
    If ON_InstanceDefinition::Cast(model_component_ref.ModelComponent()) is not nullptr,
    that pointer is returned.  Otherwise, none_return_value is returned. 
  */
  static const ON_InstanceDefinition* FromModelComponentRef(
    const class ON_ModelComponentReference& model_component_reference,
    const ON_InstanceDefinition* none_return_value
    );


  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  // virtual ON_Object::Dump override
  void Dump(
    ON_TextLog& text_log
    ) const override;

public:
  bool Write(
    ON_BinaryArchive& archive
    ) const override;

private:
  bool Internal_WriteV5(
    ON_BinaryArchive& archive
    ) const;
  bool Internal_WriteV6(
    ON_BinaryArchive& archive
    ) const;

public:
  bool Read(
    ON_BinaryArchive& archive
    ) override;

private:
  bool Internal_ReadV5(
    ON_BinaryArchive& archive
    );
  bool Internal_ReadV6(
    ON_BinaryArchive& archive
    );

public:
  ON::object_type ObjectType() const override;

  // virtual ON_Object:: override
  unsigned int SizeOf() const override;

  const ON_BoundingBox BoundingBox() const;
  
  void SetBoundingBox( ON_BoundingBox bbox );
  
  void ClearBoundingBox();

  const ON_wString Description() const;
  void SetDescription( const wchar_t* description );

  const ON_wString URL() const;
  void SetURL( const wchar_t* url );

  const ON_wString URL_Tag() const;
  void SetURL_Tag( const wchar_t* url_tag );

  /*
  Returns:
    A list of object ids in the instance geometry table sorted by id.
  */
  const ON_SimpleArray<ON_UUID>& InstanceGeometryIdList() const;

  /*
  Parameters:
    instance_geometry_id_list - [in]
       A list of object ids in the instance geometry table.
  */
  void SetInstanceGeometryIdList(
    const ON_SimpleArray<ON_UUID>& instance_geometry_id_list
  );

  /*
  Description:
    Remove all ids from the InstanceGeometryIdList().
  */
  void ClearInstanceGeometryIdList();

  /*
  Description:
    Remove id from the InstanceGeometryIdList().
  */
  bool RemoveInstanceGeometryId(
    ON_UUID id
  );

  /*
  Description:
    Remove InstanceGeometryIdList()[id_index] from the InstanceGeometryIdList() array.
  */
  bool RemoveInstanceGeometryId(
    int id_index
  );

  /*
  Description:
    Add id to the InstanceGeometryIdList().
  Parameters:
    id - [in]
      non-nil id to add.
  Returns:
    True if id is not nil and was added to the InstanceGeometryIdList().
  */
  bool AddInstanceGeometryId(
    ON_UUID id
  );

  /*
  Returns:
    True if id is in the InstanceGeometryIdList().
  */
  bool IsInstanceGeometryId(
    ON_UUID id
  ) const;

private:
  int Internal_InstanceGeometryIdIndex(
    ON_UUID id
  ) const;

public:
  /*
  Parameters:
    instance_definition_type - [in]
      ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset - change the type to Unset 
        and remove all linked file information.
      ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static - change the type to Static 
        and remove all linked file information.
      ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded - change 
        the type to from Linked to LinkedAndEmbedded.  If the current type
        is not Linked, then no changes are made.
      ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked - change 
        the type to from LinkedAndEmbedded to Linked.  If the current type
        is not LinkedAndEmbedded, then no changes are made.
  */
  bool SetInstanceDefinitionType(
    const ON_InstanceDefinition::IDEF_UPDATE_TYPE instance_definition_type
    );

  /*
  Parameters:
    linked_definition_type - [in]
      Either ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded
      or ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked.
    linked_file_reference - [in]
  */
  bool SetLinkedFileReference(
    ON_InstanceDefinition::IDEF_UPDATE_TYPE linked_definition_type,
    ON_FileReference linked_file_reference
    );

  bool SetLinkedFileReference(
    ON_InstanceDefinition::IDEF_UPDATE_TYPE linked_definition_type,
    const wchar_t* linked_file_full_path
    );

  const ON_FileReference LinkedFileReference() const;

  /*
    Destroy all linked file path information and convert the type to Static.
  */
  void ClearLinkedFileReference();

  void ClearLinkedFileContentHash();

  void ClearLinkedFileRelativePath();
  
  const ON_wString& LinkedFilePath() const;
  
  const ON_UnitSystem& UnitSystem() const;

public:
  /*
  Description:
    Sets m_us and m_unit_scale.
  */
  void SetUnitSystem( ON::LengthUnitSystem us );
  void SetUnitSystem( const ON_UnitSystem& us );

  /*
  Returns:
    True if this is a linked instance definition with
    layer settings information.
  */
  bool HasLinkedIdefReferenceComponentSettings() const;

  void ClearLinkedIdefReferenceComponentSettings();

  /*
  Parameters:
    bCreateIfNonePresent - [in]
      When bCreateIfNonePresent is true and the idef type is ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked,
      then ON_ReferencedComponentSettings will be created if none are present.
  Return:
    ON_ReferencedComponentSettings pointer or nullptr.
  */
  const ON_ReferencedComponentSettings* LinkedIdefReferenceComponentSettings() const;

  /*
  Parameters:
    bCreateIfNonePresent - [in]
      When bCreateIfNonePresent is true and the idef type is ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked,
      then ON_ReferencedComponentSettings will be created if none are present.
  Return:
    ON_ReferencedComponentSettings pointer or nullptr.
  */
  ON_ReferencedComponentSettings* LinkedIdefReferenceComponentSettings(
    bool bCreateIfNonePresent
  );

public:

  // OBSOLETE - change IdefUpdateType() to InstanceDefinitionType()
  ON_InstanceDefinition::IDEF_UPDATE_TYPE IdefUpdateType() const;

  ON_InstanceDefinition::IDEF_UPDATE_TYPE InstanceDefinitionType() const;

  /*
  Returns:
    true if InstanceDefinitionType() = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked or ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded.
  */
  bool IsLinkedType() const;

  /*
  Description:
    This property applies when an instance definition is linked.
  Returns:
    true:
      When reading the file that defines the content of the linked instance definition,
      skip any linked instance definitions found in that file.
    false:
      When reading the file that defines the content of the linked instance definition,
      recursively load linked instance definitions found in that file.
  */
  bool SkipNestedLinkedDefinitions() const;

  void SetSkipNestedLinkedDefinitions(
    bool bSkipNestedLinkedDefinitions
  );

private:
  // list of object ids in the instance geometry table.
  ON_SimpleArray<ON_UUID> m_object_uuid;

private:
  ON_wString m_description; 
  ON_wString m_url;
  ON_wString m_url_tag;     // UI link text for m_url

private:
  ON_BoundingBox m_bbox = ON_BoundingBox::EmptyBoundingBox;

private:
  ON_UnitSystem  m_us = ON_UnitSystem::None;
  
private:
  // Note: the embedded_def type is obsolete.
  //  To avoid having to deal with this obsolete type in
  //  your code, using ON_InstanceDefintion::IdefUpdateType()
  //  to get this value.  The IdefUpdateType() function
  //  with convert the obsolete value to the correct
  //  value.
  ON_InstanceDefinition::IDEF_UPDATE_TYPE m_idef_update_type = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static; 

private:
  bool m_bSkipNestedLinkedDefinitions = false;

private:
  /////////////////////////////////////////////////////////////
  //
  // linked instance definition internals
  //
private:
  ON_FileReference m_linked_file_reference;

  // For V5 3dm archive compatibility.
  // Set as needed by the Write() function for new idefs and saved if the idef is read from a V5 file.
private:
  mutable ON_CheckSum m_linked_file_V5_checksum = ON_CheckSum::UnsetCheckSum;
private:
  bool Internal_SetLinkedFileReference(
    ON_InstanceDefinition::IDEF_UPDATE_TYPE linked_definition_type,
    const ON_FileReference& linked_file_reference,
    ON_CheckSum V5_checksum
    );

  // See comment for Internal_ReferencedComponentSettings() function.
private:
  mutable class ON_ReferencedComponentSettings* m_linked_idef_component_settings = nullptr;

public:
  
  /// <summary>
  /// ON_InstanceDefinition::LinkedComponentStates specifies how model components
  /// (layers, materials, dimension styles, ...) from linked instance definition files
  /// are appear in the active model.
  /// </summary>  
  enum class eLinkedComponentAppearance : unsigned char
  {
    ///<summary>
    /// This is the only valid layer style when the instance definition type is
    /// ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static or
    /// ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded.
    /// This style is not valid when the instance definition type
    /// ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// Model components (layers, materials, dimension styles, ...) from 
    /// linked instance definition files are embedded as ordinary components 
    /// in the active model.
    /// This layer style may be used when the instance definition type is
    /// ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked.
    ///</summary>
    Active = 1,

    ///<summary>
    /// Layers from the linked instance definition are reference components in the model.
    /// This is the default layer style when the instance definition type is
    /// ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked.
    /// This layer style may be used when the instance definition type is
    /// ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked.
    ///</summary>
    Reference = 2
  };

  static ON_InstanceDefinition::eLinkedComponentAppearance LinkedComponentAppearanceFromUnsigned(
    unsigned int linked_component_appearance_as_unsigned
    );

  ON_InstanceDefinition::eLinkedComponentAppearance LinkedComponentAppearance() const;

  bool SetLinkedComponentAppearance(
    ON_InstanceDefinition::eLinkedComponentAppearance linked_component_appearance
    );
  
private:
  ON_InstanceDefinition::eLinkedComponentAppearance m_linked_component_appearance = ON_InstanceDefinition::eLinkedComponentAppearance::Unset;
                               
public:

  /*
  Returns:
    A SHA-1 hash of these instance definitions properties:   

    InstanceGeometryIdList()
    BoundingBox()
    UnitSystem()
    InstanceDefinitionType()
    LinkedFileReference()
    LinkedComponentAppearance()
  */    
  const ON_SHA1_Hash GeometryContentHash() const;

  /*
  Returns:
    A SHA-1 hash of these instance definitions properties
    Description()
    URL()
    URL_Tag()
    and all the properties that contribute to the GeometryContentHash().
  */    
  const ON_SHA1_Hash ContentHash() const;

private:
  void Internal_AccumulateHash() const;

private:
  // Internal_AccumulateHash() uses lazy evaluation to set m_geometry_content_hash when needed.
  mutable ON_SHA1_Hash m_geometry_content_hash = ON_SHA1_Hash::ZeroDigest;

  // Internal_AccumulateHash() uses lazy evaluation to set m_content_hash when needed.
  mutable ON_SHA1_Hash m_content_hash = ON_SHA1_Hash::ZeroDigest;

private:
  // Increments content version number and sets hashes to ON_SHA1_Hash::ZeroDigest.
  void Internal_ContentChanged();

private:
  unsigned char m_reserved2A = 0;
  unsigned char m_reserved2B = 0;
  unsigned char m_reserved2C = 0;

private:
  unsigned int m_reserved1 = 0;

private:
  ON__UINT_PTR m_reserved_ptr = 0;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_InstanceDefinition*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ObjectArray<ON_InstanceDefinition>;
#endif

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
  ON_InstanceRef() = default;
  ~ON_InstanceRef() = default;
  ON_InstanceRef(const ON_InstanceRef&) = default;
  ON_InstanceRef& operator=(const ON_InstanceRef&) = default;

public:
  /////////////////////////////////////////////////////////////
  //
  // virtual ON_Object overrides
  //
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  bool Write(
         ON_BinaryArchive& binary_archive
       ) const override;
  bool Read(
         ON_BinaryArchive& binary_archive
       ) override;
  ON::object_type ObjectType() const override;

  /////////////////////////////////////////////////////////////
  //
  // virtual ON_Geometry overrides
  //
  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  bool Transform( 
         const ON_Xform& xform
         ) override;

  // virtual ON_Geometry::IsDeformable() override
  bool IsDeformable() const override;

  // virtual ON_Geometry::MakeDeformable() override
  bool MakeDeformable() override;

  /////////////////////////////////////////////////////////////
  //

  // Unique id of the instance definition (ON_InstanceDefinition) 
  // in the instance definition table that defines the geometry
  // used by this reference.
  ON_UUID m_instance_definition_uuid = ON_nil_uuid;

  // Transformation for this reference.
  ON_Xform m_xform = ON_Xform::IdentityTransformation;

  // Bounding box for this reference.
  ON_BoundingBox m_bbox;

#if 0
public:
  /*
  Remove all reference to the nested linked idef information.
  */
  void ClearReferenceToNestedLinkedIdef();

  /*
  Returns:
    true
      if input was valid and the reference to the nested linked idef was set.
    false 
      if reference to the nested linked idef was not set.
  */
  bool SetReferenceToNestedLinkedIdef(
    const ON_UUID& parent_idef_uuid,
    const ON_FileReference& parent_reference_file,
    const ON_FileReference& nested_reference_file
  );

  /*
  Parameters:
    parent_idef_uuid - [in]
      The persistent id of the parent idef that contains the (possibly deeply nested)
      instance definion this reference refers to.
    parent_reference_file - [in]
      the file for the parent idef.
    nested_reference_file - [in]
      if the referenced idef is itself linked, nested_reference_file identifies 
      the file.

  Returns:
    True if this is a reference to a nested linked idef.
  */
  bool GetReferenceToNestedLinkedIdef(
    ON_UUID& parent_idef_uuid,
    ON_FileReference& parent_reference_file,
    ON_FileReference& nested_reference_file
  ) const;

  /*
  Returns:
    True if this is a reference to a nested linked idef.
  */
  bool ContainsReferenceToNestedLinkedIdef() const;

private:
  /////////////////////////////////////////////////////////////
  //
  // Additional information used when this reference is to
  // an instance definition that is nested inside an ordinary
  // linked instance definition.
  //
  // For example, if 
  // idefA = linked instance definition referencing file A.
  // idefX = any type of instance definition found in idefA.
  // 
  // iref = model geometry reference to idefX.
  //
  // When A is not a 3dm file or the 3dm id of idefX is
  // in use in the current model, the id of idefX will change
  // every time A is read. This means saving the value of
  // iref.m_instance_definition_uuid is not sufficient to identify
  // idefX. In this case, the additional information
  //
  //  iref.m_bReferenceToNestedLinkedIdef = true
  //  iref.m_parent_idef_uuid = idefA.Id()
  //  iref.m_parent_reference_file = idefA.FileReference().
  //  iref.m_nested_reference_file = idefX.FileReference().
  // 
  // is used to identify idefX in a persistent way.
  //
  bool m_bReferenceToNestedLinkedIdef = false;
  ON_UUID m_parent_idef_uuid = ON_nil_uuid; // persistent id
  ON_FileReference m_parent_reference_file = ON_FileReference::Unset;
  ON_FileReference m_nested_reference_file = ON_FileReference::Unset;
#endif

public:
  // Tolerance to use for flagging instance xforms
  // as singular.
  // A valid ON_InstanceRef.m_xform satisfies:
  //   true == (m_xform.Inverse()*m_xform).IsIdentity(ON_InstanceRef::SingularTransformationTolerance)
  static const double SingularTransformationTolerance;
};

#endif
