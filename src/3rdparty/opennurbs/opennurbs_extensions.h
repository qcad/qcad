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

#if !defined(OPENNURBS_EXTENSIONS_INC_)
#define OPENNURBS_EXTENSIONS_INC_

/*
Description:
  The ONX_ErrorCounter is useful for counting errors that occur in a section of code.
*/
class ON_CLASS ONX_ErrorCounter
{
public:
  ONX_ErrorCounter() = default;
  ~ONX_ErrorCounter() = default;
  ONX_ErrorCounter(const ONX_ErrorCounter&) = default;
  ONX_ErrorCounter& operator=(const ONX_ErrorCounter&) = default;

  const ONX_ErrorCounter operator += (const ONX_ErrorCounter& rhs);
  const ONX_ErrorCounter operator + (const ONX_ErrorCounter& rhs);

  static const ONX_ErrorCounter Zero;

  /*
  Returns:
    Number of failures.
  */
  unsigned int FailureCount() const;

  /*
  Returns:
    Number of errors.
  */
  unsigned int ErrorCount() const;

  /*
  Returns:
    Number of warnings.
  */
  unsigned int WarningCount() const;

  /*
  Returns:
    Number of failures, errors, and warnings.
  */
  unsigned int TotalCount() const;

  /*
  Description:
    Adds one to the failure count.
  Returns:
    Number of failures including this one.
  */
  unsigned int IncrementFailureCount();

  /*
  Description:
    Adds one to the error count.
  Returns:
    Number of errors including this one.
  */
  unsigned int IncrementErrorCount();

  /*
  Description:
    Adds one to the warning count.
  Returns:
    Number of warnings including this one.
  */
  unsigned int IncrementWarningCount();

  /*
  Description:
    Saves the current value of ON_GetErrorCount() 
    so future calls to ON_ERROR can be counted.
  */
  void ClearLibraryErrors();

  /*
  Description:
    Adds the number of calls to ON_ERROR since the last 
    call to ClearLibraryErrors(), AddLibraryErrors(),
    ClearLibraryErrorsAndWarnings, or AddLibraryErrorsAndWarnings().
  Returns:
    The number of errors added.
  */
  unsigned int AddLibraryErrors();

  /*
  Description:
    Saves the current value of ON_GetWarningCount() 
    so future calls to ON_WARNING can be counted.
  */
  void ClearLibraryWarnings();

  /*
  Description:
    Adds the number of calls to ON_WARNING since the last 
    call to ClearLibraryWarnings(), AddLibraryWarnings(),
    ClearLibraryErrorsAndWarnings(), or AddLibraryErrorsAndWarnings().
  Returns:
    The number of warnings added.
  */
  unsigned int AddLibraryWarnings();

  /*
  Description:
    Calls ClearLibraryErrors() and ClearLibraryWarnings().
  */
  void ClearLibraryErrorsAndWarnings();

  /*
  Description:
    Calls AddLibraryErrors() and AddLibraryWarnings().
  Returns:
    The number of errors and warnings added.
  */
  unsigned int AddLibraryErrorsAndWarnings();

  void Dump(ON_TextLog& text_log) const;

private:
  unsigned int m_failure_count = 0;
  unsigned int m_error_count = 0;
  unsigned int m_warning_count = 0;

  unsigned int m_state_bit_field = 0;
  unsigned int m_opennurbs_library_error_count = 0;
  unsigned int m_opennurbs_library_warning_count = 0;
};


/*
Description:
  Used to store user data information in an ONX_Model.
*/
class ON_CLASS ONX_Model_UserData
{
public:
#if defined(OPENNURBS_EXPORTS) || defined(OPENNURBS_IMPORTS)
  // See comments at the top of opennurbs_extensions.cpp for details.

  // new/delete
  void* operator new(size_t);
  void  operator delete(void*);

  // array new/delete
  void* operator new[] (size_t);
  void  operator delete[] (void*);

  // in place new/delete
  void* operator new(size_t,void*);
  void  operator delete(void*,void*);
#endif

  ONX_Model_UserData() = default;
  ~ONX_Model_UserData() = default;
  ONX_Model_UserData(const ONX_Model_UserData&) = default;
  ONX_Model_UserData& operator=(const ONX_Model_UserData&) = default;

  void Dump( ON_TextLog& ) const;

  ON_UUID m_uuid = ON_nil_uuid;
  ON_3dmGoo m_goo;

public:
  // 3dm version = 1,2,3,4,5,50,60,...
  unsigned int m_usertable_3dm_version = 0;

  // opennurbs_version = old yyyymmddn value or
  // a value from ON_VersionNumberConstruct().
  unsigned int m_usertable_opennurbs_version = 0;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ONX_Model_UserData*>;
#endif

/*
Description:
  Pedagogical example of all the things in an OpenNURBS 3dm archive.
  The openNURBS examples use ONX_Model to store the information
  read from 3dm archives.  Please study example_read.cpp for
  details.
*/
class ON_CLASS ONX_Model
{
#if defined(OPENNURBS_EXPORTS) || defined(OPENNURBS_IMPORTS)
  // See comments at the top of opennurbs_extensions.cpp for details.

public:

  // new/delete
  void* operator new(size_t);
  void  operator delete(void*);

  // array new/delete
  void* operator new[] (size_t);
  void  operator delete[] (void*);

  // in place new/delete
  void* operator new(size_t,void*);
  void  operator delete(void*,void*);
#endif

public:
  ONX_Model();
  virtual ~ONX_Model();

  void Reset();

private:
  // prohibit use of copy construction and operator=
  ONX_Model(const ONX_Model&) = delete;
  ONX_Model& operator=(const ONX_Model&) = delete;

public:
  /*
  Description:
    Reads an openNURBS archive and saves the information in this model
  Parameters:
    archive - [in]
      archive to read from
    table_filter - [in]
      If table_filter is zero, then everything in the archive is read.
      Otherwise the bits in table_filter identify what tables should 
      be read.  The bits are defined by the 
      ON_BInaryArchive::table_type enum.
    model_object_type_filter - [in]
      If model_object_type_filter is not zero, then it is a bitfield filter 
      made by bitwise oring ON::object_type values to select which types of 
      objects will be read from the model object table.
    error_log - [out] 
      any archive reading errors are logged here.
  Returns:
    true if archive is read with no error.  False if errors occur.
    Error details are logged in error_log.  If crc errors are in
    the archive, then ONX_Model::m_crc_error_count is set to the 
    number of crc errors.
  Example:

            // for ASCII file names
            const char* sFileName = ....;
            FILE* fp = ON::OpenFile( sFileName, "rb");

            // for UNICODE file names
            const wchar_t* wsFileName = ....;
            FILE* fp = ON::OpenFile( wsFileName, L"rb");

            bool bModelRead = false;
            bool bModelIsValid = false;

            ON_TextLog error_log;
            ONX_Model model;

            if ( 0 != fp )
            {
              ON_BinaryFile archive( ON::archive_mode::read3dm, fp );
              bModelRead = model.Read( archive, error_log );
              ON::CloseFile( fp );
            }

            if ( bModelRead )
            {
              bModelIsValid = model.Validate(error_log);
            }

  See Also:
    ONX_Model::IsValid
    ONX_Model::Write
    ONX_Model::m_crc_error_count
  */
  bool Read( 
    ON_BinaryArchive& archive,
    unsigned int table_filter,
    unsigned int model_object_type_filter,
    ON_TextLog* error_log
    );

  bool Read( 
    const char* filename,
    unsigned int table_filter,
    unsigned int model_object_type_filter,
    ON_TextLog* error_log
    );

  bool Read( 
    const wchar_t* filename,
    unsigned int table_filter,
    unsigned int model_object_type_filter,
    ON_TextLog* error_log
    );

  bool Read( 
    ON_BinaryArchive& archive,
    ON_TextLog* error_log = nullptr
    );

  bool Read( 
    const char* filename,
    ON_TextLog* error_log = nullptr
    );

  bool Read( 
    const wchar_t* filename,
    ON_TextLog* error_log = nullptr
    );

  /*
  Description:
    Reads everything up to the object table.

  Parameters:
    archive - [in] 
      archive to read from
    bManageComponents - [in]
      true: 
        The ONX_Model destructor will delete the model components
        created by this function.
      false: 
        The caller must delete the ON_ModelComponent components after
        the ONX_Model is destroyed.
    table_filter - [in]
      If table_filter is zero, then everything in the archive before
      the model object table is read.  Otherwise the bits in 
      table_filter identify what tables should be read.  The bits
      are defined by the ON_BInaryArchive::table_type enum.
    error_log - [out] any archive reading errors are logged here.
     pass nullptr if you don't want to log errors

  Returns:
    If the input is valid and everything before the model object
    table is successfully read, then true is returned.  Otherwise
    false is returned.

  Example:

            // for ASCII file names
            const char* sFileName = ....;
            FILE* fp = ON::OpenFile( sFileName, "rb");

            // for UNICODE file names
            const wchar_t* wsFileName = ....;
            FILE* fp = ON::OpenFile( wsFileName, L"rb");

            bool bModelRead = false;
            bool bModelIsValid = false;

            ON_TextLog error_log;

            if ( 0 != fp )
            {
              ON_BinaryFile archive( ON::archive_mode::read3dm, fp );
              ONX_Model model;
              
              // Read settings, layer information, and other tables
              // with information that is referenced by model object
              // attributes.
              bModelRead = model.IncrementalReadBegin( archive, error_log );

              if ( bModelRead )
              {
                object_filter = ON::mesh_object   // read meshes
                              | ON::curve_object  //  and curves
                              ;
                for(;;)
                {
                  // read the next model object
                  ON_ModelGeometryComponent* pModelObject = model.IncrementalReadModelObject(object_filter,0);
                  if ( 0 == pModelObject )
                    break;
                  
                  ... // work with this model object

                  // done with this object.
                  pModelObject = 0;
                  model.m_object_table.Remove();
                }                
              }
              ON::CloseFile( fp );
            }
  See Also:
    ONX_Model::IsValid
    ONX_Model::Write
    ONX_Model::m_crc_error_count
  */
  bool IncrementalReadBegin(
    ON_BinaryArchive& archive,
    bool bManageComponents,
    unsigned int table_filter,
    ON_TextLog* error_log
    );

  /*
  Description:
    Reads the next item in the model geometry table.

  Parameters:
    archive - [in]
    bManageModelGeometryComponent - [in]
      true: 
        The ONX_Model destructor will delete the ON_ModelGeometryComponent components
        created by this function.
      false: 
        The caller must delete the ON_ModelGeometryComponent components after
        the ONX_Model is destroyed.
    bManageGeometry - [in]
      true: 
        The ON_ModelGeometryComponent destructor will delete the ON_Geometry 
        classes created by this function.
      false: 
        The caller must delete the ON_Geometry classes after
        the ONX_Model and ON_ModelGeometryComponent components are destroyed.
    bManageAttributes - [in]
      true: 
        The ON_ModelGeometryComponent destructor will delete the ON_3dmObjectAttributes
        classes created by this function.
      false: 
        The caller must delete the ON_3dmObjectAttributes classes after
        the ONX_Model and ON_ModelGeometryComponent components are destroyed.
    model_object_type_filter - [in]
      If model_object_type_filter is not zero, then it is a bitfield filter 
      made by bitwise oring ON::object_type values to select which types of
      objects will be read from the model object table.
    model_geometry_reference - [out]
      A reference to an ON_ModelGeometryComponent.  This referenced ON_ModelGeometryComponent
      component is also added to the ONX_Model. 
      Call ONX_Model.RemoveComponent() if you want to discard it before
      continuing.  
  Returns:
    True
      Successful.  If model_geometry_reference.IsEmpty() is true, 
      then no more geometry objects are available and you should call
      IncrementalReadFinish().
    False
      An error occurred and reading should terminate.
  Remarks:
    You must call IncrementalReadBegin() before making any calls to
    IncrementalReadModelObject().
  */
  bool IncrementalReadModelGeometry(
    ON_BinaryArchive& archive,
    bool bManageModelGeometryComponent,
    bool bManageGeometry,
    bool bManageAttributes,
    unsigned int model_object_type_filter,
    ON_ModelComponentReference& model_geometry_reference
    );

  /*
  Description:
    Reads everything up to the object table.

  Parameters:
    archive - [in] 
      archive to read from
    bManageComponents - [in]
      true: 
        The ONX_Model destructor will delete the model components
        created by this function.
      false: 
        The caller must delete the ON_ModelComponent components after
        the ONX_Model is destroyed.
    table_filter - [in]
      If table_filter is zero, then everything in the archive before
      the model object table is read.  Otherwise the bits in 
      table_filter identify what tables should be read.  The bits
      are defined by the ON_BInaryArchive::table_type enum.
    error_log - [out] any archive reading errors are logged here.
     pass nullptr if you don't want to log errors

  Returns:
    If the input is valid and everything before the model object
    table is successfully read, then true is returned.  Otherwise
    false is returned.

  See Also:
    ONX_Model::IsValid
    ONX_Model::Write
    ONX_Model::m_crc_error_count
  */
  bool IncrementalReadFinish(
    ON_BinaryArchive& archive,
    bool bManageComponents,
    unsigned int table_filter,
    ON_TextLog* error_log
    );

  /*
  Description:
    Writes contents of this model to an openNURBS archive.

  Parameters:
    filename - [in]

    version - [in] 
      Version of the openNURBS archive to write.
        0 default value and suggested.
           When 0 is passed in, the value of ON_BinaryArchive::CurrentArchiveVersion()
           is used.
        2, 3, 4, 50, 60, ...
          If you pass in a value < ON_BinaryArchive::CurrentArchiveVersion(), then some
          information in current data structures will not be saved in the 3dm archive.
          Rhino 2.x can read version 2 files.
          Rhino 3.x can read version 2 and 3 files.
          Rhino 4.x can read version 2, 3, and 4 files.
          Rhino 5.x can read version 2, 3, 4, 5, and 50 files.
          Rhino 6.x can read version 2, 3, 4, 5, 50, and 60 files.

    error_log - [out]
      any archive writing errors are logged here.

  Returns:
    True if archive is written with no error. 
    False if errors occur.
    Error details are logged in error_log.
  */
  bool Write( 
    const char* filename,
    int version = 0,
    ON_TextLog* error_log = nullptr
    ) const;

  /*
  Description:
    Writes contents of this model to an openNURBS archive.

  Parameters:
    filename - [in]

    version - [in] 
      Version of the openNURBS archive to write.
        0 default value and suggested.
           When 0 is passed in, the value of ON_BinaryArchive::CurrentArchiveVersion()
           is used.
        2, 3, 4, 50, 60, ...
          If you pass in a value < ON_BinaryArchive::CurrentArchiveVersion(), then some
          information in current data structures will not be saved in the 3dm archive.
          Rhino 2.x can read version 2 files.
          Rhino 3.x can read version 2 and 3 files.
          Rhino 4.x can read version 2, 3, and 4 files.
          Rhino 5.x can read version 2, 3, 4, 5, and 50 files.
          Rhino 6.x can read version 2, 3, 4, 5, 50, and 60 files.

    error_log - [out]
      any archive writing errors are logged here.

  Returns:
    True if archive is written with no error. 
    False if errors occur.
    Error details are logged in error_log.
  */
  bool Write( 
    const wchar_t* filename,
    int version = 0,
    ON_TextLog* error_log = nullptr
    ) const;

  /*
  Description:
    Writes contents of this model to an openNURBS archive.

  Parameters:
    archive - [in]
      archive to write to
      You must call archive.SetArchiveFullPath(...) i order for file references to work correctly.

    version - [in] 
      Version of the openNURBS archive to write.
        0 default value and suggested.
           When 0 is passed in, the value of ON_BinaryArchive::CurrentArchiveVersion()
           is used.
        2, 3, 4, 50, 60, ...
          If you pass in a value < ON_BinaryArchive::CurrentArchiveVersion(), then some
          information in current data structures will not be saved in the 3dm archive.
          Rhino 2.x can read version 2 files.
          Rhino 3.x can read version 2 and 3 files.
          Rhino 4.x can read version 2, 3, and 4 files.
          Rhino 5.x can read version 2, 3, 4, 5, and 50 files.
          Rhino 6.x can read version 2, 3, 4, 5, 50, and 60 files.

    error_log - [out]
      any archive writing errors are logged here.

  Returns:
    True if archive is written with no error. 
    False if errors occur.
    Error details are logged in error_log.

  Example:

            model = ...;
            if ( model.IsValid( error_log ) )
            {
              const wchar_t* wsFileName = ....;
              FILE* fp = ON::OpenFile( wsFileName, L"wb");

              bool ok = false;
              if ( 0 != fp )
              {
                const char* sStartSectionComment = "...";
                int version = 5; // 2, 3, 4 or 5 are valid
                ON_BinaryFile archive( ON::archive_mode::write3dm, fp );
                archive.SetArchiveFullPath(wsFileName);
                ok = model.write( archive, 
                                  version, 
                                  sStartSectionComment, 
                                  error_log );
                ON::CloseFile( fp );
              }
           }

  */
  bool Write( 
    ON_BinaryArchive& archive,
    int version = 0,
    ON_TextLog* error_log = nullptr
    ) const;

  /////////////////////////////////////////////////////////////////////
  //
  // BEGIN model definitions
  //

  // 3dm archive start section information
  int m_3dm_file_version = 0;
  unsigned int m_3dm_opennurbs_version = 0;
  ON__UINT64 m_3dm_file_byte_count = 0;

  ON_String m_sStartSectionComments;

  // Properties include revision history, notes, information about
  // the application that created the file, and an optional preview image.
  ON_3dmProperties m_properties;

  // Settings include tolerance, and unit system, and defaults used
  // for creating views and objects.
  ON_3dmSettings m_settings;

  /*
  Description:
    A manifest of every model component in this ONX_Model.
  Remarks:
    Use the manifest to find model objects from a name, id or index.

    The manifest Id, Name, and Index values are values used in
    the model. These are assigned when a component is added to the ONX_Model.
    When possible the id and name are not changed.

    The manifest=model and original component values are different when:
    - The original component Id or Name was not set and a value was automatically
      assigned.
    - The original component Id or Name was not unique and was modified when the component
      was added to the model.
    - Generally the original component index differs from the manifest=model component
      index.
    
    The OriginalToModelMap() can be used to convert original component index 
    and id to the manifest=model index and id.
    
    The ModelToOriginalMap() can be used to manifest=model index and id to
    the original component index and id.
  */
  const ON_ComponentManifest& Manifest() const;

  /*
  Returns:
    A map from original component index and id to manifest=model index and id.
  Remarks:
    ON_ManifestMapItem Source = original component index and id.
    ON_ManifestMapItem Destination = model-manifest index and id.
  */
  const ON_ManifestMap& OriginalToModelMap() const;

  /*
  Returns:
    A map from manifest=model index and id to original component index and id.
  Remarks:
    ON_ManifestMapItem Source = model-manifest index and id.
    ON_ManifestMapItem Destination = original component index and id.
  */
  const ON_ManifestMap& ModelToOriginalMap() const;

  /*
  Description:
    This number changes every time the content of the ONX_Model is modified.
  */
  ON__UINT64 ModelContentVersionNumber() const;

  /*
  Description:
    Add a copy of a model_component to this model.
  model_component - [in]
    A copy of model_component is added to this model.
    The index, id, and name of the copied component are
    set the the model values (Manifest() "Manifest" index, name, and id).
  
  bResolveIdAndNameConflicts - [in]
    If bResolveIdAndNameConflicts is false, then model_component.Id() must be non-nil 
    and not used in this model and model_component.Name() must be correctly set.
    If bResolveIdAndNameConflicts is true, then id and name will be modified
    as needed in the model and manifest.

  Returns:
    A reference to the added model component.
    If the reference is empty (ON_ModelComponent::IsEmpty() is true)
    then the input was not valid.
  */
  ON_ModelComponentReference AddModelComponent(
    const class ON_ModelComponent& model_component,
    bool bResolveIdAndNameConflicts
    );

  ON_ModelComponentReference AddModelComponent(
    const class ON_ModelComponent& model_component
    );

  ON_ModelComponentReference RemoveModelComponent(
    ON_ModelComponent::Type component_type,
    ON_UUID component_id
    );
  
  /*
  Description:
    Easy way to add a layer to the model.
  Returns:
    If layer_name is valid, the layer's index (>=0) is returned. Otherwise,
    ON_UNSET_INT_INDEX is returned.
  */
  int AddLayer(
    const wchar_t* layer_name,
    ON_Color layer_color
  );

  /*
  Description:
    Easy way to add a default layer to the model.
  Properties:
    layer_name - [in]
      can be nullptr or empty.
    layer_color - [in]
      can be ON_Color::UnsetColor
  Returns:
    The default layer's index (>=0) is returned.
  */
  int AddDefaultLayer(
    const wchar_t* layer_name,
    ON_Color layer_color
  );

  /*
  Description:
    Easy way to add a default dimension style to the model.
  Parameters:
    dimension_style_name - [in]
      can be nullptr or empty
    length_unit_system - [in]
      If ON::LengthUnitSystem::Unset, then settings length unit system is used.
    tolerance - [in]
      If not > 0, then settings tolerance is used.
  Returns:
    The default dimension style's index (>=0) is returned.
  */
  int AddDefaultDimensionStyle(
    const wchar_t* dimension_style_name,
    ON::LengthUnitSystem length_unit_system,
    double model_tolerance
  );

  /*
  Description:
    Easy way to add a render material to the model. Creates a PBR material.
  Returns:
    If mat_name is valid and the function succeeds, the material's index is returned.
    Otherwise ON_UNSET_INT_INDEX is returned.
  */
  int AddRenderMaterial(
    const wchar_t* mat_name
  );

  /*
  Description:
    Easy way to add a render environment to the model. Creates a basic environment.
  Returns:
    If env_name is valid and the function succeeds, the environment's index is returned.
    Otherwise ON_UNSET_INT_INDEX is returned.
  */
  int AddRenderEnvironment(
    const wchar_t* env_name
  );

  /*
  Description:
    Easy way to add a render texture to the model. Creates a bitmap texture.
    The texture's name is derived from the supplied file name. The file must exist locally
    or the function will fail.
  Returns:
    If the function succeeds, the texture's index is returned.
    Otherwise ON_UNSET_INT_INDEX is returned.
  */
  int AddRenderTexture(
    const wchar_t* filename
  );

  /*
  Description:
    Add a managed model component (ON_Layer, ON_DimStyle, ...) to this model.

  managed_model_component - [in]
    managed_model_component must be created by operator new and on the heap.
    It will be deleted when the model and last ON_ModelComponentReference are 
    destroyed.
  
  bResolveIdAndNameConflicts - [in]
    If bResolveIdAndNameConflicts is false, then model_component.Id() must be non-nil 
    and not used in this model and model_component.Name() must be correctly set.
    If bResolveIdAndNameConflicts is true, then id and name will be modified
    as needed in managed_model_component, the model, and the manifest.

  Returns:
    A reference to the added model component.
    If the reference is empty (ON_ModelComponent::IsEmpty() is true)
    then the input was not valid.
  */
  ON_ModelComponentReference AddManagedModelComponent(
    class ON_ModelComponent* managed_model_component,
    bool bResolveIdAndNameConflicts
    );

  ON_ModelComponentReference AddManagedModelComponent(
    class ON_ModelComponent* managed_model_component
    );

  /*
  Description:
    Add a model component to this model and control how the model_component instance
    is managed.
  
  model_component - [in]
    An ON_ModelComponent created on the heap by calling new X where X is
    derived from ON_ModelComponent.

  bManagedComponent  - [in]
    If bManagedComponent is true, then ~ONX_Model will delete the component.
    If bManagedComponent is false, then you are responsible for insuring
    the component exists past the destruction of this ONX_Model.

  bResolveIdAndNameConflicts  - [in]
    If bResolveIdAndNameConflicts is false, then model_component.Id() must be non-nil 
    and not used in this model and model_component.Name() must be correctly set.
    If bResolveIdAndNameConflicts is true, then id and name will be modified
    as needed.
    
  bUpdateComponentIdentification - [in]
    The model_component Index(), Id(), and Name() values are set to match
    the ones used in the model (Manifest() "Manifest" values.)
    
  Returns:
    A reference to the added model component.
    If the reference is empty (ON_ModelComponentReference::IsEmpty() is true),
    then the input was not valid and the model component was not added.
  */
  ON_ModelComponentReference AddModelComponentForExperts(
    class ON_ModelComponent* model_component,
    bool bManagedComponent,
    bool bResolveIdAndNameConflicts,
    bool bUpdateComponentIdentification
    );

  /*
  Description:
    Add an copy of the model_geometry and attributes to this model.

  Parameters:
    geometry_object - [in]
      geometry_object must point to a geometric object (curve, surface, brep, mesh, points, ...),
      a render light, an annotation object, or a detail object.
      A copy of geometry_object is added to and managed by this model.
    attributes - [in]
      nullptr if not available.
      A copy of attributes is added to and managed by this model.
  
  bResolveIdAndNameConflicts - [in]
    If bResolveIdAndNameConflicts is false, then attributes must be nullptr 
    or attributes->m_uid must be non-nil and not used in this model.
    If bResolveIdAndNameConflicts is true, then id will be modified
    as needed.

  Returns:
    A reference to the added model component.
    If the reference is empty (ON_ModelComponent::IsEmpty() is true)
    then the input was not valid.
  */
  ON_ModelComponentReference AddModelGeometryComponent(
    const class ON_Object* geometry_object,
    const class ON_3dmObjectAttributes* attributes,
    bool bResolveIdAndNameConflicts
    );

  ON_ModelComponentReference AddModelGeometryComponent(
    const class ON_Object* geometry_object,
    const class ON_3dmObjectAttributes* attributes
    );

  /*
  Description:
    Add an copy of the model_geometry and attributes to this model.

  Parameters:
    managed_geometry_object - [in]
      managed_geometry_object must point to an instance geometric object (curve, surface, brep, mesh, points, ...),
      a render light, an annotation object, or a detail object created by operator new and on the heap.
      It will be deleted when the this ONX_Model and the last ON_ModelComponentReference are destroyed.

    managed_attributes - [in]
      managed_attributes should be nullptr or point to an instance created by operator new and on the heap.
      It will be deleted when the this ONX_Model and the last ON_ModelComponentReference are destroyed.  

  bResolveIdAndNameConflicts - [in]
    If bResolveIdAndNameConflicts is false, then managed_attributes must be nullptr 
    or managed_attributes->m_uuid must be non-nil and not used in this model.
    If bResolveIdAndNameConflicts is true, then id will be modified
    as needed.

  Returns:
    A reference to the added model component.
    If the reference is empty (ON_ModelComponent::IsEmpty() is true)
    then the input was not valid.
  */
  ON_ModelComponentReference AddManagedModelGeometryComponent(
    class ON_Object* managed_geometry_object,
    class ON_3dmObjectAttributes* managed_attributes,
    bool bResolveIdAndNameConflicts
    );

  ON_ModelComponentReference AddManagedModelGeometryComponent(
    class ON_Object* managed_geometry_object,
    class ON_3dmObjectAttributes* managed_attributes
    );

  /*
  Description:
    Add geometry and attributes to this model and control how the instances are managed.

  Parameters:
    bManageGeometry - [in]
      If true, geometry_object should point to an instance created by operator new and on the heap.
      It will be deleted when the this ONX_Model and the last ON_ModelComponentReference are destroyed.
      If false, the expert caller is carefully managing the instance and memory to insure
      model_geometry is a valid instance while this ONX_Model and any ON_ModelComponentReference 
      are active.

    geometry_object - [in]
      geometry_object should point to a geometric object (curve, surface, brep, mesh, points, ...),
      a render light, an annotation object, or a detail object.

    bManageAttributes - [in]
      If true, attributes should be nullptr or point to an instance created by operator new and on the heap.
      It will be deleted when the this ONX_Model and the last ON_ModelComponentReference are destroyed.
      If false, the expert caller is carefully managing the instance and memory to insure
      attributes is a valid instance while this ONX_Model and and ON_ModelComponentReference 
      are active.

    attributes - [in]
      nullptr if not available.
  
  bResolveIdAndNameConflicts - [in]
    If bResolveIdAndNameConflicts is false, then attributes must be nullptr 
    or attributes->m_uid must be non-nil and not used in this model.
    If bResolveIdAndNameConflicts is true, then id will be modified
    as needed.

  Returns:
    A reference to the added model component.
    If the reference is empty (ON_ModelComponent::IsEmpty() is true)
    then the input was not valid.
  */
  ON_ModelComponentReference AddModelGeometryComponentForExperts(
    bool bManageGeometry,
    class ON_Object* geometry_object,
    bool bManageAttributes,
    class ON_3dmObjectAttributes* attributes,
    bool bResolveIdAndNameConflicts
    );

  unsigned int ComponentIndexLimit(
    ON_ModelComponent::Type component_type
    ) const;

  /*
  Returns:
    Number of active and deleted components.
    Count does not include system components.
  */
  unsigned int ActiveAndDeletedComponentCount(
    ON_ModelComponent::Type component_type
    ) const;

  /*
  Returns:
    Number of active components.
    Count does not include system components.
  */
  unsigned int ActiveComponentCount(
    ON_ModelComponent::Type component_type
    ) const;

  /*
  Returns:
    Number of deleted components.
  */
  unsigned int DeletedComponentCount(
    ON_ModelComponent::Type component_type
    ) const;

  ON_ModelComponentReference ComponentFromIndex(
    ON_ModelComponent::Type component_type,
    int component_model_index
    ) const;    

  ON_ModelComponentReference ComponentFromUnsignedIndex(
    ON_ModelComponent::Type component_type,
    unsigned int component_model_index
    ) const;    

  ON_ModelComponentReference ComponentFromId(
    ON_ModelComponent::Type component_type,
    ON_UUID component_model_id
    ) const;  

  ON_ModelComponentReference ComponentFromName(
    ON_ModelComponent::Type component_type,
    ON_UUID component_parent_id,
    const wchar_t* component_model_name
    ) const;

  ON_ModelComponentReference ComponentFromNameHash(
    ON_ModelComponent::Type component_type,
    const ON_NameHash& component_model_name_hash
    ) const;

  /*
  Parameters:
    runtime_serial_number - [in]
      Value of ON_ModelComponent::RuntimeSerialNumber() to search for.
  Returns:
    If there is a model component with the specified runtime serial number,
    then a reference to that component is returned.
    Otherwise, ON_ModelComponentReference::Empty is returned.
  Remarks:
    ONX_Model::ComponentFromRuntimeSerialNumber() used to get a reference rather than a copy of the model's 
    primary ON_ModelComponentReference. This is the function that must be used if a caller is going to 
    use exclusive access functions like

      ON_ModelComponent* ON_ModelComponentReference::ExclusiveModelComponent()
      ON_3dmObjectAttributes* ON_ModelGeometryComponent::ExclusiveAttributes()
      ON_Geometry* ON_ModelGeometryComponent::ExclusiveGeometry()

    to modify content that is in the ONX_Model. The exclusive access functions 
    will only return non-nullptr values when there are no external references to
    the model component.
  */
  const ON_ModelComponentReference& ComponentFromRuntimeSerialNumber(
    ON__UINT64 runtime_serial_number
  ) const;

  /*
  Description:
    Get an image from its model index.
  Parameters:
    image_model_index - [in]
  Returns:
    An ON_ModelComponentReference to the image.
  Remarks:
    Model index and Manifest() manifest item index are the same.
  */
  ON_ModelComponentReference ImageFromIndex(
    int image_model_index
    ) const;

  ON_ModelComponentReference ImageFromId(
    ON_UUID image_id
    ) const;

  ON_ModelComponentReference ImageFromFileFullPath(
    const wchar_t* image_file_full_path_name
    ) const;

  ON_ModelComponentReference ImageFromFileContent(
    const ON_ContentHash& image_file_content_hash
    ) const;

  ON_ModelComponentReference ImageFromFileReference(
    const ON_FileReference& file_reference
    ) const;

  /*
  Description:
    Get a line pattern from its model index.
  Parameters:
    line_pattern_model_index - [in]
  Returns:
    An ON_ModelComponentReference to the line pattern.
  Remarks:
    Model index and Manifest() manifest item index are the same.
  */
  ON_ModelComponentReference LinePatternFromIndex(
    int line_pattern_model_index
    ) const;

  ON_ModelComponentReference LinePatternFromId(
    ON_UUID line_pattern_model_id
    ) const;

  ON_ModelComponentReference LinePatternFromName(
    const wchar_t* line_pattern_name
    ) const;

  ON_ModelComponentReference LinePatternFromNameHash(
    ON_NameHash line_pattern_model_name_hash
    ) const;

  /*
  Description:
    Get linetype from object attributes.
  Parameters:
    attributes - [in] object attributes.
    line_pattern - [out] linetype
  */
  ON_ModelComponentReference LinePatternFromAttributes( 
    const ON_3dmObjectAttributes& attributes
    ) const;

  ON_ModelComponentReference LinePatternFromLayerIndex( 
    int layer_index
    ) const;

  // These methods are deprecated due to the use of the phrase 'RenderMaterial' which now refers to
  // materials provided by the RDK. The materials used by _these_ methods are plain ON_Materials.
  ON_DEPRECATED ON_ModelComponentReference RenderMaterialFromLayerIndex(int) const;
  ON_DEPRECATED ON_ModelComponentReference RenderMaterialFromAttributes(const ON_3dmObjectAttributes&) const;
  ON_DEPRECATED ON_ModelComponentReference RenderMaterialFromIndex(int) const;
  ON_DEPRECATED ON_ModelComponentReference RenderMaterialFromId(ON_UUID) const;

  /*
  Description:
    Get material from layer index.
  Parameters:
    layer_index - [in] layer index.
  */
  ON_ModelComponentReference MaterialFromLayerIndex(
    int layer_index
    ) const;

  /*
  Description:
    Get material from object attributes.
  Parameters:
    attributes - [in] object attributes.
  */
  ON_ModelComponentReference MaterialFromAttributes(
    const ON_3dmObjectAttributes& attributes
    ) const;

  /*
  Description:
    Get material from index.
  Parameters:
    material_index - [in] index.
  */
  ON_ModelComponentReference MaterialFromIndex(
    int material_index
    ) const;

  /*
  Description:
    Get material from id.
  Parameters:
    material_id - [in] id.
  */
  ON_ModelComponentReference MaterialFromId(
    ON_UUID material_id
    ) const;

  /*
  Description:
    Get a layer from its model index.
  Parameters:
    layer_model_index - [in]
  Returns:
    An ON_ModelComponentReference to the layer.
  Remarks:
    Model index and Manifest() manifest item index are the same.
  */
  ON_ModelComponentReference LayerFromIndex(
    int layer_model_index
    ) const;

  ON_ModelComponentReference LayerFromId(
    ON_UUID layer_model_id
    ) const;

  ON_ModelComponentReference LayerFromName(
    ON_UUID layer_parent_id,
    const wchar_t* layer_name
    ) const;

  ON_ModelComponentReference LayerFromNameHash(
    const ON_NameHash& layer_model_name_hash
    ) const;

  ON_ModelComponentReference LayerFromAttributes( 
    const ON_3dmObjectAttributes& attributes
    ) const;

  /*
  Description:
    Get a dimension style from its model index.
  Parameters:
    dimension_style_model_index - [in]
  Returns:
    An ON_ModelComponentReference to the dimension style.
  Remarks:
    Model index and Manifest() manifest item index are the same.
  */
  ON_ModelComponentReference DimensionStyleFromIndex(
    int dimension_style_index
    ) const;
  ON_ModelComponentReference DimensionStyleFromId(
    ON_UUID dimension_styleid
    ) const;
  ON_ModelComponentReference DimensionStyleFromName(
    const wchar_t* dimension_style_name
    ) const;
  ON_ModelComponentReference DimensionStyleFromNameHash(
    ON_NameHash dimension_style_name_hash
    ) const;

  /*
  Returns:
    Id of the current dimension style or nil if the current style is 
    not set or not in this model.
  */
  ON_UUID CurrentDimensionStyleId() const;

  /*
  Parameters:
    dimension_style_id - [in]
      Id of a dimension style in this model, a system dimension style, or ON_nil_uuid.
  Returns:
    true if dimension_style_id is valid and is set.
  */
  bool SetCurrentDimensionStyleId(
    ON_UUID dimension_style_id
  );

  /*
  Returns:
    Current dimension style
    = DimensionStyleFromId(CurrentDimensionStyleId())
  */
  ON_ModelComponentReference CurrentDimensionStyle() const;

  /*
  Returns:
    A system dimension style that is the default for this model
    and is used when a referenced dimension style is missing from
    this model.
  */
  ON_ModelComponentReference DefaultDimensionStyle() const;

  /*
  Parameters:
    font - [in]
    model_space_text_scale - [in]
      If model_space_text_scale > 0, then the DimScale() must be equal to model_space_text_scale.
    bIgnoreSystemDimStyles - [in]
  Returns:
    The first dimension style with the specified font.
  Remarks:
    dimension styles with a non-nil parent id are ignored.
  */
  ON_ModelComponentReference FirstDimensionStyleFromFont(
    const ON_Font* font,
    double model_space_text_scale,
    bool bIgnoreSystemDimStyles
    ) const;

  /*
  Parameters:
    managed_font_serial_number - [in]
    model_space_text_scale - [in]
      If model_space_text_scale > 0, then the DimScale() must be equal to model_space_text_scale.
    bIgnoreSystemDimStyles - [in]
  Returns:
    The first dimension style with the specified font.
  Remarks:
    dimension styles with a non-nil parent id are ignored.
  */
  ON_ModelComponentReference FirstDimensionStyleFromManagedFontSerialNumber(
    unsigned int managed_font_serial_number,
    double model_space_text_scale,
    bool bIgnoreSystemDimStyles
    ) const;

  /*
  Description:
    Find or create a dimension style with the specified font characteristics.
  */
  ON_ModelComponentReference DimensionStyleWithFontCharacteristics(
    const ON_Font& font_characteristics,
    double model_space_text_scale
    );

  /*
  Description:
    Find a model geometry component from Id
  Parameters:
    model_geometry_component_id - [in]
  Returns:
    If there is a model geometry component with the id, it is returned.
    Otherwise, ON_ModelComponentReference::Empty is returned.
  */
  ON_ModelComponentReference ModelGeometryFromId(
    ON_UUID model_geometry_component_id
    ) const;

  /*
  Description:
    Find a model geometry component from Id
  Parameters:
    model_geometry_component_id - [in]
  Returns:
    If there is a model geometry component with the id, it is returned.
    Otherwise, ON_ModelGeometryComponent::Unset is returned.
  */
  const ON_ModelGeometryComponent& ModelGeometryComponentFromId(
    ON_UUID model_geometry_component_id
    ) const;

public:
  ON_SimpleArray<ONX_Model_UserData*> m_userdata_table;

private:
  ON_ModelComponentReference m_default_render_material = ON_ModelComponentReference::CreateConstantSystemComponentReference(ON_Material::Default);
  ON_ModelComponentReference m_default_line_pattern = ON_ModelComponentReference::CreateConstantSystemComponentReference(ON_Linetype::Continuous);
  ON_ModelComponentReference m_default_layer = ON_ModelComponentReference::CreateConstantSystemComponentReference(ON_Layer::Default);
  ON_ModelComponentReference m_default_text_style = ON_ModelComponentReference::CreateConstantSystemComponentReference(ON_TextStyle::Default);
  ON_ModelComponentReference m_default_dimension_style = ON_ModelComponentReference::CreateConstantSystemComponentReference(ON_DimStyle::Default);

private:
  ON_ModelComponentReference Internal_AddModelComponent(
    ON_ModelComponent* model_component,
    ON_UUID id,
    ON_UUID name_parent_id,
    const ON_wString& name,
    bool bManagedComponent,
    bool bUpdateComponentIdentification
    );

private: // Private extension.
  friend class ONX_ModelPrivate;
  class ONX_ModelPrivate* m_private;

private:
  void Internal_IncrementModelContentVersionNumber();

private:
  // A manifest of everything in the model. Use the manifest to find
  // objects from a name, id or index.
  ON_ComponentManifest m_manifest;
  ON_ManifestMap m_original_to_manifest_map;
  ON_ManifestMap m_manifest_to_original_map;

private:
  friend class ONX_ModelComponentIterator;
  class ONX_ModelComponentReferenceLink* Internal_ModelComponentLinkFromSerialNumber( 
    ON__UINT64 model_component_runtime_serial_number 
    ) const;
  class ONX_ModelComponentReferenceLink* Internal_AddModelComponentReference(
    ON_ModelComponentReference mcr
    );
  void Internal_RemoveModelComponentReferenceLink(
    class ONX_ModelComponentReferenceLink* mcr_link
    );
  // A map used to lookup by serial number.
  ON_SerialNumberMap m_mcr_sn_map;
  ON_FixedSizePool m_mcr_link_fsp;

#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: "...needs to have dll-interface to be used by clients of class". This warning is not correct.
  // m_mcr_lists is private and all code that manages it is explicitly implemented in the DLL.
  class ONX_ModelComponentList
  {
  public:
    ON_ModelComponent::Type m_component_type = ON_ModelComponent::Type::Unset;
    unsigned int m_count = 0;
    class ONX_ModelComponentReferenceLink* m_first_mcr_link = nullptr;
    class ONX_ModelComponentReferenceLink* m_last_mcr_link = nullptr;
  };

  //-------------------------------------------------------------------------------------------
  // The following two lines are deprecated due to limiting the number of types to 16.
  // They are no longer used. Instead, a new list inside the extension is used. This is private
  // and is only used internally to ONX_Model but it can't be removed without breaking the SDK.
  //-------------------------------------------------------------------------------------------
  enum : unsigned int { ONX_MCR_LIST_COUNT = 16 };        // DEPRECATED -- not used.
  ONX_ModelComponentList m_mcr_lists[ONX_MCR_LIST_COUNT]; // DEPRECATED -- not used.
  //-------------------------------------------------------------------------------------------

  const ONX_ModelComponentList& Internal_ComponentListConst(ON_ModelComponent::Type component_type) const;
  ONX_ModelComponentList& Internal_ComponentList(ON_ModelComponent::Type component_type);
#pragma ON_PRAGMA_WARNING_POP

public:
  bool ValdateComponentIdAndName(
    ON_ModelComponent::Type component_type,
    const ON_UUID& candidate_id,
    const ON_UUID& component_parent_id,
    const wchar_t* candidate_name,
    bool bResolveIdConflict,
    bool bResolveNameConflict,
    ON_UUID& model_id,
    ON_wString& model_name
    ) const;

  //
  // END model definitions
  //
  /////////////////////////////////////////////////////////////////////

public:
  /*
  Returns:
    Bounding box of every object in m_object_table[].
  */
  ON_BoundingBox ModelGeometryBoundingBox() const;

  /*
  Returns:
    Bounding box of every render light in m_light_table[].
  */
  ON_BoundingBox RenderLightBoundingBox() const;

private:
  void Internal_ComponentTypeBoundingBox(
    const ON_ModelComponent::Type component_type,
    ON_BoundingBox& bbox
    ) const;

public:
  /*
  Description:
    Get wireframe drawing color from object attributes.
  Parameters:
    attributes - [in] object attributes.
  Returns:
    Wireframe drawing color.
  */
  ON_Color WireframeColorFromAttributes(
    const ON_3dmObjectAttributes& attributes
    ) const;

  /* 
  Description:
    See if the instance reference iref refers to an instance
    definition.
  Parameters:
    iref - [in]
    idef_uuid - [in] id of idef we are looking for
  Returns:
    @untitled table
     0         iref does not use idef
     1         iref directly references idef
    >1         iref has a nested reference to idef (nesting depth returned)
    -1         iref.m_instance_definition_uuid is not valid
    -2         invalid idef found
  */
  int UsesIDef( 
    const ON_InstanceRef& iref,
    ON_UUID idef_uuid
    ) const;

  /////////////////////////////////////////////////////////////////////
  //
  // BEGIN model document level user string tools
  //

  /*
  Description:
    Attach a user string to the document.
  Parameters:
    key - [in] id used to retrieve this string.
    string_value - [in] 
      If nullptr, the string with this id will be removed.
  Returns:
    True if successful.
  */
  bool SetDocumentUserString( 
    const wchar_t* key, 
    const wchar_t* string_value 
    );

  /*
  Description:
    Get user string from the document.
  Parameters:
    key - [in] id used to retrieve the string.
    string_value - [out]
  Returns:
    True if a string with id was found.
  */
  bool GetDocumentUserString( 
    const wchar_t* key, 
    ON_wString& string_value 
    ) const;

  /*
  Description:
    Get a list of all user strings in the document.
  Parameters:
    user_strings - [out]
      user strings are appended to this list.
  Returns:
    Number of elements appended to the user_strings list.
  */
  int GetDocumentUserStrings( ON_ClassArray<ON_UserString>& user_strings ) const;

  //
  // END model document level user string tools
  //
  /////////////////////////////////////////////////////////////////////


  /////////////////////////////////////////////////////////////////////
  //
  // BEGIN model text dump tools
  //

  // text dump of entire model
  void Dump( ON_TextLog& ) const;
  
  // text dump of model properties and settings
  void DumpSummary( ON_TextLog& ) const;

  // text dump of user data table
  void DumpUserDataTable( ON_TextLog& ) const;

  void DumpComponentList( 
    ON_ModelComponent::Type component_type,
    ON_TextLog& text_log
    ) const;

  /*
  Returns:
    A text dump of all component lists.
  */
  void DumpComponentLists(
    ON_TextLog& text_log
  ) const;

  /*
  Returns:
    A SHA-1 hash of the model's content. If two models have identical content,
    then the have equal ContentHash() values.
  */
  ON_SHA1_Hash ContentHash() const;

private:
  void Internal_DumpSummary(
    ON_TextLog& dump, 
    bool bInvariantContentOnly
  ) const;

  //
  // END model text dump tools
  //
  /////////////////////////////////////////////////////////////////////

public:
  /////////////////////////////////////////////////////////////////////
  //
  // BEGIN Rendering information
  //

  ON_DEPRECATED_MSG("This function is deprecated.")
  static bool IsRDKDocumentInformation(const ONX_Model_UserData& docud);

  ON_DEPRECATED_MSG("This function is deprecated.")
  static bool GetRDKDocumentInformation(const ONX_Model_UserData& docud, ON_wString& rdk_xml_document_data);

  ON_DEPRECATED_MSG("This function is deprecated as it did not return the buffer sizes, making it useless")
  static bool GetRDKEmbeddedFiles(const ONX_Model_UserData& docud, ON_ClassArray<ON_wString>& paths, ON_SimpleArray<unsigned char*>& embedded_files_as_buffers);

  ON_DEPRECATED_MSG("This function is deprecated in favor of ON_EmbeddedFile.")
  static bool GetRDKEmbeddedFiles(const ONX_Model_UserData& docud, ON_ClassArray<ON_wString>& paths, ON_SimpleArray<unsigned char*>& embedded_files_as_buffers, ON_SimpleArray<size_t>& buffer_sizes);

  ON_DEPRECATED_MSG("This function is deprecated in favor of ON_EmbeddedFile.")
  static bool GetRDKEmbeddedFilePaths(const ONX_Model_UserData& docud, ON_ClassArray<ON_wString>& paths);

  ON_DEPRECATED_MSG("This function is deprecated in favor of ON_EmbeddedFile.")
  static bool GetRDKEmbeddedFile(const ONX_Model_UserData& docud, const wchar_t* path, ON_SimpleArray<unsigned char>& bytes);

  ON_DEPRECATED_MSG("This function is deprecated.")
  static bool IsRDKObjectInformation(const ON_UserData& objectud);

  ON_DEPRECATED_MSG("This function is deprecated. Please use GetDecalIterator(), AddDecal() and GetDecal() instead.")
  static bool GetRDKObjectInformation(const ON_Object& object, ON_wString& xml);

  //
  // END Rendering information
  //
  /////////////////////////////////////////////////////////////////////

private:
  mutable ON_BoundingBox m_model_geometry_bbox = ON_BoundingBox::UnsetBoundingBox;
  mutable ON_BoundingBox m_render_light_bbox = ON_BoundingBox::UnsetBoundingBox;
  class ON_DocumentUserStringList* m_model_user_string_list = nullptr;
};

class ON_CLASS ONX_ModelComponentIterator
{
public:
  ONX_ModelComponentIterator() = default;
  ~ONX_ModelComponentIterator() = default;
  ONX_ModelComponentIterator(const ONX_ModelComponentIterator&) = default;
  ONX_ModelComponentIterator& operator=(const ONX_ModelComponentIterator&) = default;

  ONX_ModelComponentIterator(
    const ONX_Model& model,
    ON_ModelComponent::Type component_type
    );

  const ONX_Model* Model() const;

  ON_ModelComponentReference FirstComponentReference();
  ON_ModelComponentReference LastComponentReference();
  ON_ModelComponentReference CurrentComponentReference() const;
  ON_ModelComponentReference NextComponentReference();
  ON_ModelComponentReference PreviousComponentReference();

  ON_ModelComponentWeakReference FirstComponentWeakReference();
  ON_ModelComponentWeakReference LastComponentWeakReference();
  ON_ModelComponentWeakReference NextComponentWeakReference();
  ON_ModelComponentWeakReference PreviousComponentWeakReference();
  ON_ModelComponentWeakReference CurrentComponentWeakReference() const;

  // Use these with caution unless it is clear you are the only thread
  // with references to the model and the iterator.
  const ON_ModelComponent* FirstComponent();
  const ON_ModelComponent* LastComponent();
  const ON_ModelComponent* CurrentComponent() const;
  const ON_ModelComponent* NextComponent();
  const ON_ModelComponent* PreviousComponent();

  /*
  Returns:
    Number of active components in the current model.
  Remarks:
    If the model is modified during iteration, this value will changes.
  */
  unsigned int ActiveComponentCount() const;
  
private:
  const class ONX_Model::ONX_ModelComponentList* Internal_List() const;
  void Internal_SetLink(const class ONX_ModelComponentReferenceLink* link) const;
  void Internal_SetLink(ON__UINT64 model_component_sn) const;

  ON_ModelComponent::Type m_component_type = ON_ModelComponent::Type::Unset;
  const class ONX_Model* m_model = nullptr;
  mutable ON__UINT64 m_model_content_version = 0;
  mutable const class ONX_Model::ONX_ModelComponentList* m_list = nullptr;
  mutable const class ONX_ModelComponentReferenceLink* m_link = nullptr;
  mutable ON__UINT64 m_current_component_sn = 0;
  mutable ON__UINT64 m_next_component_sn = 0;
  mutable ON__UINT64 m_prev_component_sn = 0;

  // The current component is a weak ref so that a stand alone iterator cannot
  // keep the current element alive since iterations often involve deletion.
  // The iterators next/prev will still work as expected when the current element
  // is deleted. In particular, an iterator can be used to efficiently delete
  // portions of a model and have the deletion occur when many people
  // expect it to occur and not at a later time. This makes debugging 
  // invalid deletions much easier.
  mutable ON_ModelComponentWeakReference m_current_component_weak_ref;
};

class ON_CLASS ONX_ModelTest
{
public:
  ONX_ModelTest() = default;
  ~ONX_ModelTest() = default;
  ONX_ModelTest(const ONX_ModelTest&) = default;
  ONX_ModelTest& operator=(const ONX_ModelTest&) = default;

  static const ONX_ModelTest Unset;

public:

#pragma region // XXRH_C_SHARED_ENUM // [ONX_ModelTest::Type] [Rhino.Geometry.Something.Type] [nested:byte]
  /// <summary>
  /// ONX_ModelTest::Type identifies the type of file reading test to perform.
  /// </summary>
  enum class Type : unsigned char
  {
    Unset = 0,

    ///<summary>
    /// Read the source 3dm file.
    ///</summary>
    Read = 1,

    ///<summary>
    /// Read the source 3dm file and write one or two temporary 3dm files. The original
    /// source file is not modified. If the 3dm version of the source file
    /// is < ON_BinaryArchive::CurrentArchiveVersion(), then two temporary 3dm
    /// files are written, the first with 3dm version = ON_BinaryArchive::CurrentArchiveVersion()-10
    /// and the second with 3dm version = ON_BinaryArchive::CurrentArchiveVersion().
    /// For example, if Rhino 6 is the current version of Rhino and a file written 
    /// by Rhino 5 is read, then both a temporary Rhino 5 and a temporary Rhino 6 3dm
    /// file are written.
    ///</summary>
    ReadWrite = 2,

    ///<summary>
    /// Perform the ReadWrite test and read the temporary files.
    ///</summary>
    ReadWriteRead = 3,

    ///<summary>
    /// Perform the ReadWriteRead test. If one of the temporary files has the same 3dm version
    /// as the original source file, verify that the ONX_Models created by reading the original
    /// 3dm file and the temporary 3dm file with the same version have identical values
    /// of ONX_Model::ContentHash().
    ///</summary>
    ReadWriteReadCompare = 4
  };
#pragma endregion

  static const char* TestTypeToString(ONX_ModelTest::Type test_type);
  static const wchar_t* TestTypeToWideString(ONX_ModelTest::Type test_type);

#pragma region // XXRH_C_SHARED_ENUM // [ONX_ModelTest::Result] [Rhino.Geometry.Something.Result] [nested:byte]
  /// <summary>
  /// ONX_ModelTest::Result reports the result of a test.
  /// </summary>
  enum class Result : unsigned char
  {
    ///<summary>
    /// Test result is not set.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// Test failed to complete.
    ///</summary>
    Fail = 1,

    ///<summary>
    /// Test was performed and completed, but at least one ON_ERROR occurred.
    ///</summary>
    Errors = 2,

    ///<summary>
    /// Test was performed and completed, but at least one ON_WARNING occurred.
    ///</summary>
    Warnings = 3,
 

    ///<summary>
    /// Test was performed and passed.
    ///</summary>
    Pass = 4,

    ///<summary>
    /// Test was not performed because the input did not satisfy prerequisites or an
    /// earlier test failed.
    /// For example, if a ONX_ModelReadTest::TestType::ReadWriteReadCompare 
    /// test is requested and the source file is a Rhino 1 file, the compare
    /// test is skipped.
    /// For example, if a ONX_ModelReadTest::TestType::ReadWriteRead 
    /// test is requested and the Write test fails, the second Read test is skipped.
    ///</summary>
    Skip = 5,
  };
#pragma endregion

  static const char* ResultToString(ONX_ModelTest::Result result);
  static const wchar_t* ResultToWideString(ONX_ModelTest::Result result);

  static ONX_ModelTest::Result WorstResult(
    ONX_ModelTest::Result a,
    ONX_ModelTest::Result b
  );

  /*
  Parameters:
    error_count - [in]
    no_errors_result - [in]
      result to return when 0 = error_count.TotalCount().
  */
  static ONX_ModelTest::Result ResultFromErrorCounter(
    ONX_ErrorCounter error_count,
    ONX_ModelTest::Result no_errors_result
    );

  /*
  Description:
    Test ONX_Model::Read() and ONX_Model::Write().
  Parameters:
    file_path - [in]
      file path
    test_type - [in]
      test to perform.
    bKeepModels - [in]
      If true, then the ONX_Models created by reading 3dm archives are saved
      so the can be examined after the tests complete.
    text_log_file_path - [in]
      If not empty, the string to use for file_path in the output text_log.
      This is used to create logs on different computers that can be compared.
    text_log - [in]
      If text_log is not nullptr, then a summary of the test is sent to text_log.
  Returns:
    True if every test passed with no warnings or errors.
    False if a test failed or warnings or errors occurred.
  */
  bool ReadTest(
    const char* file_path,
    ONX_ModelTest::Type test_type,
    bool bKeepModels,
    const char* text_log_file_path,
    ON_TextLog* text_log
  );

  /*
  Description:
    ONX_Model::ReadTest() can be used to test reading a specific file.
  Parameters:
    file_path - [in]
      file path
    test_type - [in]
      test to perform.
    bKeepModels - [in]
      If true, then the ONX_Models created by reading 3dm archives are saved
      so the can be examined after the tests complete.
    text_log_file_path - [in]
      If not empty, the string to use for file_path in the output text_log.
      This is used to create logs on different computers that can be compared.
    text_log - [in]
      If text_log is not nullptr, then a summary of the test is sent to text_log.
  Returns:
    True if every test passed with no warnings or errors.
    False if a test failed or warnings or errors occurred.
  */
  bool ReadTest(
    const wchar_t* file_path,
    ONX_ModelTest::Type test_type,
    bool bKeepModels,
    const wchar_t* text_log_file_path,
    ON_TextLog* text_log
  );

  /*
  Description:
    ONX_Model::ReadTest() can be used to test reading a specific file.
  Parameters:
    fp - [in]
      fp pointer to a file opened with ON_FileStream::Opent(...,"rb");
    test_type - [in]
      test to perform.
    bKeepModels - [in]
      If true, then the ONX_Models created by reading 3dm archives are saved
      so the can be examined after the tests complete.
    text_log_file_path - [in]
      If not empty, the string to use for file_path in the output text_log.
      This is used to create logs on different computers that can be compared.
    text_log - [in]
      If text_log is not nullptr, then a summary of the test is sent to text_log.
  Returns:
    True if every test passed with no warnings or errors.
    False if a test failed or warnings or errors occurred.
  */
  bool ReadTest(
    FILE* fp,
    ONX_ModelTest::Type test_type,
    bool bKeepModels,
    const wchar_t* text_log_file_path,
    ON_TextLog* text_log
  );


  /*
  Description:
    ONX_Model::Test() can be used to test reading a specific file.
  Parameters:
    archive - [in]      
    test_type - [in]
      test to perform.
    bKeepModels - [in]
      If true, then the ONX_Models created by reading 3dm archives are saved
      so the can be examined after the tests complete.
    text_log_file_path - [in]
      If not empty, the string to use for file_path in the output text_log.
      This is used to create logs on different computers that can be compared.
    text_log - [in]
      If text_log is not nullptr, then a summary of the test is sent to text_log.
  Returns:
    True if every test passed with no warnings or errors.
    False if a test failed or warnings or errors occurred.
  */
  bool ReadTest(
    ON_BinaryArchive& archive,
    ONX_ModelTest::Type test_type,
    bool bKeepModels,
    const wchar_t* text_log_file_path,
    ON_TextLog* text_log
  );

  /*
  Description:
    Prints test results.
  */
  void Dump(ON_TextLog& text_log) const;


  /*
  Description:
    Prints the model context to text_log.
  */
  static bool DumpModel(const ONX_Model* model, ON_TextLog& text_log);

  /*
  Description:
    Prints the source model context to text file next to the source file
    with the file _ONX_ModelText_original_<PLATFORM>.txt appended to the 
    source file name.
  Remark:
    Call after test is completed.
  */
  bool DumpSourceModel() const;

  /*
  Description:
    Prints the source model context to text_log.
  Remark:
    Call after test is completed.
  */
  bool DumpSourceModel(const wchar_t* text_file_full_path) const;

  /*
  Description:
    Prints the source model context to text_log.
  Remark:
    Call after test is completed.
  */
  bool DumpSourceModel(ON_TextLog& text_log) const;

  /*
  Description:
    Prints the model obtained from the last read in the read-write-read test to
    with the file _ONX_ModelText_copy_<PLATFORM>.txt appended to the 
    original source file name.
  Remark:
    Call after test is completed.
  */
  bool DumpReadWriteReadModel() const;

  /*
  Description:
    Prints the model obtained from the last read in the read-write-read test to
    with the file _ONX_ModelText_copy_<PLATFORM>.txt appended to a text file
    with the specified name.
  Remark:
    Call after test is completed.
  */
  bool DumpReadWriteReadModel(const wchar_t* text_file_full_path) const;

  /*
  Description:
    Prints the model obtained from the last read in the read-write-read test to
    with the file _ONX_ModelText_copy_<PLATFORM>.txt appended to the text_log.
  Remark:
    Call after test is completed.
  */
  bool DumpReadWriteReadModel(ON_TextLog& text_log) const;

private:
  void Internal_BeginTest();

  void Internal_EndCurrentTest();

  void Internal_BeginNextTest(
    ONX_ModelTest::Type test_type
  );


  void Internal_ReadTest(
    ON_BinaryArchive& archive,
    ONX_ModelTest::Type test_type,
    bool bKeepModels,
    const wchar_t* text_log_file_path,
    ON_TextLog* text_log
  );

  bool Internal_TallyTestResults();

public:

  // Test that was performed.
  ONX_ModelTest::Type TestType() const;

  /*
  Returns:
    The name of the source 3dm file.
  */
  const ON_wString Source3dmFilePath() const;

  /*
  Returns:
    The string used in the output log to identify the source 3dm file.
  */
  const ON_wString TextLogSource3dmFilePath() const;

  /*
  Returns:
    Version of the 3dm fie, 1,2,3,4,5,50,60,...
  */
  unsigned int Source3dmFileVersion() const;
  
  /*
  Returns:
    Worst result for any test that was attempted.
  */
  ONX_ModelTest::Result TestResult() const;
 
  /*
  Parameters:
    test_type - [in]
  Returns:
    Result of the test identified by the test_type parameter.
  */
  ONX_ModelTest::Result TestResult(
    ONX_ModelTest::Type test_type
  );

  static bool SkipCompare(
  unsigned int source_3dm_file_version
  );

  /*
  Returns:
    Total number of failures, errors, and warnings for all tests that
    were performed.
  */
  ONX_ErrorCounter ErrorCounter() const;
 
  /*
  Returns:
    Total number of failures, errors, and warnings for all tests that
    were performed.
  */
  ONX_ErrorCounter ErrorCounter(
   ONX_ModelTest::Type test_type
   ) const;

  const ON_SHA1_Hash SourceModelHash();
  const ON_SHA1_Hash ReadWriteReadModelHash();

  /*
  Returns:
    nullptr if the test was run with bKeepModels=false or the 
    source archive could not be read.
    Otherwise, a pointer to the source model.
  */
  std::shared_ptr<ONX_Model> SourceModel() const;

  /*
  Returns:
    nullptr if the read write read test was not performed or was run with bKeepModels=false.
    Otherwise, a pointer to the result of the read write read test.
  */
  std::shared_ptr<ONX_Model> ReadWriteReadModel() const;


private:
  ONX_ModelTest::Type m_test_type = ONX_ModelTest::Type::Unset;

  ON_wString m_source_3dm_file_path;

  // if set, used when printing the name of m_source_3dm_file_path in the text
  // log so results from different computers can be compared.
  ON_wString m_text_log_3dm_file_path;

  unsigned int m_model_3dm_file_version[3] = {0};

  unsigned int m_current_test_index = 0;

  ONX_ModelTest::Result m_test_result = ONX_ModelTest::Result::Unset;
  ONX_ModelTest::Result m_test_results[7] = {};

  ONX_ErrorCounter m_error_count;
  ONX_ErrorCounter m_error_counts[7];

#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: ... : class 'std::shared_ptr<ON_MeshThicknessAnalysisImpl>' 
  //        needs to have dll-interface to be used by clients ...
  // m_model[] is private and all code that manages m_sp is explicitly implemented in the DLL.

  // m_model[0] = model from source file
  // m_model[1] = model[0] -> write to current 3dm version -> read into model[1]
  // m_model[2] = model[0] -> write to prev 3dm version -> read into model[2]
  std::shared_ptr<ONX_Model> m_model[3];
#pragma ON_PRAGMA_WARNING_POP

  // m_model_hash[i] = m_model[0].Hash()
  ON_SHA1_Hash m_model_hash[3];
};


#endif
