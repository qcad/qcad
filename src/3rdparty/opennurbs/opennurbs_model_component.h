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

#if !defined(ON_MODEL_COMPONENT_INC_)
#define ON_MODEL_COMPONENT_INC_

/*
Description:
  The ON_ModelComponent class is a base class for all components in a
  model and manages the index, id and other information common to all
  components in a model.
*/
class ON_CLASS ON_ModelComponent : public ON_Object
{
  ON_OBJECT_DECLARE(ON_ModelComponent);

public:
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump( 
    ON_TextLog& 
    ) const override;

  unsigned int SizeOf() const override;


  ON__UINT32 DataCRC(
    ON__UINT32 current_remainder
    ) const override;

  ON_UUID ModelObjectId() const override;

public:

#pragma region RH_C_SHARED_ENUM [ON_ModelComponent::Type] [Rhino.DocObjects.ModelComponentType] [public:byte]
  ///<summary>
  ///The ON_ModelComponent::Type enum has a value for each explicit component type
  ///and two special values, Unset and Mixed. Use an ON_ModelComponentTypeIterator
  ///instance to iterate over the ON_ModelComponent::Type values.
  ///</summary>
  enum class Type : unsigned char
  {
    ///<summary>No value set.</summary>
    Unset = 0,
    ///<summary>Embedded image (bitmap) components.</summary>
    Image = 1,
    ///<summary>Texture mapping.</summary>
    TextureMapping = 2,
    ///<summary>Material.</summary>
    Material = 3,
    ///<summary>Render material. Deprecated in favor of Material.</summary>
    RenderMaterial = Material,
    ///<summary>Line pattern (linetype).</summary>
    LinePattern = 4,
    ///<summary>Layer.</summary>
    Layer = 5,
    ///<summary>Group.</summary>
    Group = 6,
    ///<summary>Text style.</summary>
    TextStyle = 7,
    ///<summary>AnnotationDimension style.</summary>
    DimStyle = 8,
    ///<summary>Render light.</summary>
    RenderLight = 9,
    ///<summary>Hatch pattern.</summary>
    HatchPattern = 10,
    ///<summary>Instance definition.</summary>
    InstanceDefinition = 11,
    ///<summary>Model objects (points, curves, surfaces, ..., annotation, page details, ...), including objects referenced by instance definitions.</summary>
    ModelGeometry = 12,
    ///<summary>History record.</summary>
    HistoryRecord = 13,
    ///<summary>Render content.</summary>
    RenderContent = 14,
    ///<summary>Embedded file for render texture.</summary>
    EmbeddedFile = 15,
    ///<summary>This value was never used and is now obsolete.</summary>
    ObsoleteValue = 16,
    ///<summary>Section style attributes</summary>
    SectionStyle = 17,

    // If you add any more, add them here, above NumOf.

    ///<summary>Number of items above.</summary>
    NumOf,

    ///<summary>Multiple component types. Used when a component type filter must include all explicit component types.</summary>
    Mixed = 0xFE
  };
#pragma endregion

  static ON_ModelComponent::Type ComponentTypeFromUnsigned(
    unsigned int component_type_as_unsigned
    );

  static const ON_wString ComponentTypeToString(
    ON_ModelComponent::Type
    );

  /*
  Parameters:
  component_type - [in]
  Returns:
    True if component_type is a valid enum value, 
    and not equal to ON_ModelComponent::Type::Unset.
  */
  static bool ComponentTypeIsValid(
    ON_ModelComponent::Type component_type
    );

  /*
  Parameters:
    component_type - [in]
  Returns:
    True if component_type is a valid enum value, 
    and not equal to ON_ModelComponent::Type::Unset, 
    and not equal to ON_ModelComponent::Type::Mixed.
  */
  static bool ComponentTypeIsValidAndNotMixed(
    ON_ModelComponent::Type component_type
    );

  /*
  Parameters:
    component_type - [in]
  Returns:
    True if component's of the specified type require unique names.
  Remarks:
    In general, component names ignore case and parent when testing for
    equality. 
    However, there are exceptions. Use
    ON_ModelComponent::UniqueNameIncludesParent() and
    ON_ModelComponent::UniqueNameIgnoresCase() 
    to test for exceptions.
  */
  static bool UniqueNameRequired(
    ON_ModelComponent::Type component_type
    );

  /*
  Parameters:
    component_type - [in]
  Returns:
    True if objects with the same name and different parents are considered
    to have a unique name. This typically means the user interface for the
    object names is some type of tree.
  Remarks:
    Currently, layers are the only object type where this property is true.
    This function should be called "NameIncludesParent" because it 
    also applies to components like materials and geometry objects
    that are not required to have a unique name.
  */
  static bool UniqueNameIncludesParent(
    ON_ModelComponent::Type component_type
    );

  /*
  Parameters:
    component_type - [in]
  Returns:
    True if component name ignores case when testing for equality.
  Remarks:
    Currently all other component types except for groups ignore 
    case when testing for equality.
    This function should be called "NameIgnoresCase" because it 
    also applies to components like materials and geometry objects
    that are not required to have a unique name.
  */
  static bool UniqueNameIgnoresCase(
    ON_ModelComponent::Type component_type
    );

  static bool IndexRequired(
    ON_ModelComponent::Type component_type
    );

  /*
  Returns:
    True if a component name can begin with the first code point.
  Remarks:
    Component names cannot begin with a (, ), [, ], {, }, or space.
    These brackets can be the second or later code points.
    A space can be an interior code point.
  */
  static bool IsValidComponentNameFirstCodePoint(
    ON__UINT32 unicode_code_point
    );

  /*
  Parameters:
    length - [in]
      number of wchar_t elements in candidate_component_name[] or -1
      if it is a null terminated string.
    candidate_component_name - [in]
      The first code point is decoded from this string
      and passed to ON_ModelComponent::IsValidComponentNameFirstCodePoint().
  Returns:
    True if a component name can begin with the first code point.
  Remarks:
    Component names cannot begin with a (, ), [, ], {, }, or space.
    These brackets can be the second or later code points.
    A space can be an interior code point.
  */
  static bool IsValidComponentNameFirstCodePoint(
    int length,
    const wchar_t* candidate_component_name 
    );

  /*
  Parameters:
    candidate_component_name - [in]
      A null terminated string that is UTF-16 or UTF-32 encoded.
      When sizeof(wchar_t) >= 4, both UTF-16 surrogate pairs
      and UTF-32 code point values > 0xFFFF are valid and can
      appear in the same string.
  Returns:
    True if candidate_component_name is a valid component name.
  Remarks:
    Component names cannot begin with a (, ), [, ], {, }, or space.
    These brackets can be the second or later code points.
    A space can be an interior code point.
  */
  static bool IsValidComponentName(
    const wchar_t* candidate_component_name 
    );

  static bool IsValidComponentName(
    const ON_wString& candidate_component_name
    );

  /*
  Parameters:
    length - [in]
      > 0.
      The expected number of elements before the null terminator in candidate_component_name[].
    candidate_component_name - [in]
      A null terminated string that is UTF-16 or UTF-32 encoded.
      When sizeof(wchar_t) >= 4, both UTF-16 surrogate pairs
      and UTF-32 code point values > 0xFFFF are valid and can
      appear in the same string.
      The capacity of candidate_component_name[] must be >= length+1.
      This validity test fails if candidate_component_name[length] is not zero
      or if a null terminator appears before candidate_component_name[length].
  Returns:
    True if candidate_component_name is a valid component name.
  Remarks:
    Component names cannot begin with a (, ), [, ], {, }, or space.
    These brackets can be the second or later code points.
    A space can be an interior code point.
  */

  static bool IsValidComponentName(
    size_t length,
    const wchar_t* candidate_component_name 
    );

  /*
  Parameters:
    model_component - [in]
    model_manfest - [in]
      current model contents
    valid_name - [in]
      Valid name for this component in a model with the specified manifest.
  Returns:
    true: model_component.Name() is valid
    false: model_component.Name() is not valid    
  */
  static bool IsValidComponentName(
    const class ON_ComponentManifest&  model_manfest,
    const ON_ModelComponent& model_component,
    bool bPermitReferencePrefix,
    ON_wString& valid_name
  );

private:
  friend class CRhinoObject;

  ON_ModelComponent(ON__UINT64 runtime_serial_number) ON_NOEXCEPT;

public:
  static const ON_ModelComponent Unset;

  ON_ModelComponent() ON_NOEXCEPT;

  ~ON_ModelComponent() = default;
  
  // Locked status of source attributes is not copied to permit copy and modify operations.
  // Runtime serial number and content version number are not copied.
  ON_ModelComponent(
    const ON_ModelComponent& source
    );

  /*
  Description:
    Sets and locks the component type attribute.
  Parameters:
    component_type - [in]
  */
  ON_ModelComponent(
    ON_ModelComponent::Type component_type
    ) ON_NOEXCEPT;

  // Locked status of source attributes is not copied to permit copy and modify operations.
  ON_ModelComponent(
    ON_ModelComponent::Type component_type,
    const ON_ModelComponent& source
    ) ON_NOEXCEPT;
  
  /*
  Remarks:
    operator= will not change locked destination attributes.
    Locked status of source attributes is not copied to permit copy and modify operations.
  */
  ON_ModelComponent& operator=(const ON_ModelComponent& source);

  /*
  The ON_ModelComponent::Attributes enum is used to set bits that identify
  model component attributes.
  */
  enum Attributes : unsigned int
  {
    NoAttributes = 0U,

    ComponentSerialNumberAttribute = 0x0001U,
    TypeAttribute = 0x0002U,
    ModelSerialNumberAttribute = 0x0004U,
    IdAttribute = 0x0008U,
    IndexAttribute = 0x0010U,
    NameAttribute = 0x0020U,
    ParentIdAttribute = 0x0040U,
    DeletedNameAttribute = 0x0080U,
    ComponentStatusAttribute = 0x0100U,

    // Default model attributes saved in binary archives.
    // Id, ParentId, Name, Index
    // Do not include SystemComponentAttribute in BinaryArchiveAttributes
    BinaryArchiveAttributes = 0x78U,

    // Do not include SystemComponentAttribute in AllAttributes
    AllAttributes = 0x1FFU,

    SystemComponentAttribute = 0x8000U
  };

  unsigned int CopyFrom(
    const ON_ModelComponent& src,
    unsigned int attributes_filter
    );

  bool WriteModelComponentAttributes(
    class ON_BinaryArchive& archive,
    unsigned int attributes_filter
    ) const;

  bool ReadModelComponentAttributes(
    class ON_BinaryArchive& archive
    );
  
  ///////////////////////////////////////////////////////////////////////////////
  //
  // Model Serial Number interface
  //
  //  The ModelSerialNumber() identifies the model that manages the component.
  //  If the component is from some type of reference model, then one or both of
  //  the reference model serial number and InstanceDefinitionModelSerialNumber()
  //  identify the source model.
  //

  /*
  Description:
    Specify the model that is managing this component.
  Parameters:
    model_serial_number - [in]
      In Rhino, this is the document runtime serial number.
  Returns:
    true if the model_serial_number value was changed to component_model_serial_number or is already equal to component_model_serial_number.
    false if the model_serial_number value is locked and component_model_serial_number != locked value.
  */
  bool SetModelSerialNumber(
    unsigned int model_serial_number
    );

  /*
  Description:
    Specify the model that is managing this component.
  Parameters:
    model_serial_number - [in]
      In Rhino, this is the document runtime serial number.
    reference_model_serial_number - [in]
      In Rhino, this is the worksession reference model serial number.
      instance_definition_model_serial_number - [in]
      In Rhino, this is the linked instance definition model serial number.
  Returns:
    true if the model_serial_number value was changed to component_model_serial_number or is already equal to component_model_serial_number.
    false if the model_serial_number value is locked and component_model_serial_number != locked value.
  */
  bool SetModelSerialNumber(
    unsigned int model_serial_number,
    unsigned int reference_model_serial_number,
    unsigned int instance_definition_model_serial_number
    );

  /*
  Returns:
    A value identifying the model that manages this component.
  Remarks:
    If the component is being managed by a model, this value identifies the model.
    In Rhino, this value is the document runtime serial number.
    Typically this value is set and locked by the code that adds 
    a component to a model.
    This value is copied by the copy constructor and operator=. 
    This value is not saved in .3dm archives.
  */
  unsigned int ModelSerialNumber() const;

  /*
  Returns:
    When a component is in a model for reference, this value identifies the
    reference model.
  Remarks:
    Reference components are not saved in .3dm archives.
    Typically this value is set and locked by the code that adds 
    a component to a model.
    This value is copied by the copy constructor and operator=. 
    This value is not saved in .3dm archives.

    In Rhino, this value is a worksession model runtime serial number and 
    these values are used.
           0: not from a worksession reference model
           1: from an unidentified reference model
      2-1000: reserved for future use
       >1000: worksession reference model serial number
  */
  unsigned int ReferenceModelSerialNumber() const;

  /*
  Returns:
    When a component is in a model as part of the information required
    for a linked instance definition, this value identifies the the linked
    instance definition reference model.
  Remarks:
    Reference components are not saved in .3dm archives.
    Typically this value is set and locked by the code that adds 
    a component to a model.
    This value is copied by the copy constructor and operator=. 
    This value is not saved in .3dm archives.

    In Rhino, this value is a linked instance definition runtime serial number
    and  these values are used..
            0: Active model component.
       1-1000: reserved for future use
        >1000: linked instance definition serial number
  */
  unsigned int InstanceDefinitionModelSerialNumber() const;

  /*
  Description:
    Sets the model serial number, reference model serial number and instance
    definition model serial number values to 0 and flags these values
    as unset.
  */
  bool ClearModelSerialNumber();

  /*
  Description:
    Calling LockModelSerialNumber() will prohibit future changes to the 
    ModelSerialNumber(), ReferenceModelSerialNumber(), and
    InstanceDefinitionModelSerialNumber() attributes.
  */
  void LockModelSerialNumber();

  /*
  Returns:
    True if the ModelSerialNumber(), ReferenceModelSerialNumber(), and
    InstanceDefinitionModelSerialNumber() attributes are locked.
  */
  bool ModelSerialNumberIsLocked() const;

  /*
  Returns:
    True if the ModelSerialNumber(), ReferenceModelSerialNumber(), and
    InstanceDefinitionModelSerialNumber() attributes are set.
  */
  bool ModelSerialNumberIsSet() const;

  /*
  Returns 
    True if ReferenceModelSerialNumber() or InstanceDefinitionModelSerialNumber() are not zero.
  */
  bool IsReferenceComponent() const;

  ///////////////////////////////////////////////////////////////////////////////
  //
  // Type interface
  //

  /*
  Returns:
    Value of the Type attribute.
  Remarks:
    If the component is in a model, then the component_type is unique for all components
    of identical type in the model and is locked.
  */
  ON_ModelComponent::Type ComponentType() const;

  /*
  Parameters:
    component_component_type - [in]
  Returns:
    true if the component_type value was changed to component_component_type or is already equal to component_component_type.
    false if the component_type value is locked and component_component_type != locked value.
  */
  bool SetComponentType(
    ON_ModelComponent::Type component_component_type
    );

  /*
  Description:
    Set the model serial number value to the ON_ModelComponent::Unset.Type()
    and change the state so TypeIsSet() returns false.
  */
  bool ClearComponentType();

  /*
  Description:
    Calling LockType() will prohibit future changes to the Type attribute.
  */
  void LockComponentType();

  /*
  Returns:
    True if the Type attribute is locked.
  */
  bool ComponentTypeIsLocked() const;

  /*
  Returns:
    True if the Type attribute is set.
  */
  bool ComponentTypeIsSet() const;

  ///////////////////////////////////////////////////////////////////////////////
  //
  // Id interface
  //
  //  The component id is intended to be unique in the context of a model.
  //

  /*
  Returns:
    Value of the Id attribute.
  Remarks:
    If the component is in a model, then the id is unique for all components in
    the model and is locked.
  */
  const ON_UUID& Id() const;

  bool IdIsNil() const;
  bool IdIsNotNil() const;

  /*
  Parameters:
    component_id - [in]
  Returns:
    true if the id value was changed to component_id or is already equal to component_id.
    false if the id value is locked and component_id != locked value.
  */
  bool SetId(
    const ON_UUID& component_id
    );

  /*
  Description:
    Sets the id to a new value created by ON_CreateUuid().
  Returns:
    ON_nil_uuid: Id is locked.
    Otherwise the value of the new id.
  */
  const ON_UUID& SetId();

  /*
  Description:
    If the it is nil, call SetId().
  */
  const ON_UUID& IfIdIsNilSetId();

  /*
  Description:
    Sets the id to a new value created by ON_CreateUuid() and locks the 
    id attribute so it cannot be changed.
  Returns:
    ON_nil_uuid: Id is locked.
    Otherwise the value of the new id.
  */  
  const ON_UUID& SetAndLockId();
  

  /*
  Description:
    Set the component id value to the ON_ModelComponent::Unset.ModelComponentId()
    and change the state so ModelComponentIdIsSet() returns false.
  */
  bool ClearId();

  /*
  Description:
    Calling LockModelComponentId() will prohibit future changes to the ModelComponentId attribute.
  */
  void LockId();

  /*
  Returns:
    True if the ModelComponentId attribute is locked.
  */
  bool IdIsLocked() const;

  /*
  Returns:
    True if the ModelComponentId attribute is set.
  */
  bool IdIsSet() const;


  ///////////////////////////////////////////////////////////////////////////////
  //
  // Index interface
  //
  //  When a component is managed by a model, the component index is identifies
  //  the component within the context of that model.
  //

  /*
  Returns:
    Value of the runtime model component index attribute.
  Remarks:
    If the component is in a model, then the index is unique for all components
    of identical type in the model and is locked.
    If the index has not been set, ON_UNSET_INT_INDEX is returned.
    The Index() value can change when saved in an archive (.3dm file).
    Use the Id() when you need to reference model components in an archive.
  */
  int Index() const;

  /*
  Returns:
    Value of the model component index attribute.
  Parameters:
    unset_index_value - [in]
      Value to return if the index has not been set.
      ON_UNSET_INT_INDEX or indices of default components are often
      used for this parameter.
  Returns:
    IndexIsSet() ? Index() : unset_index_value;
  Remarks:
    If the component is in a model, then the index is unique for all components
    of identical type in the model and is locked.
  */
  int Index(
    int unset_index_value
    ) const;

  /*
  Parameters:
    component_index - [in]
  Returns:
    true if the index value was changed to component_index or is already equal to component_index.
    false if the index value is locked and component_index != locked value.
  */
  bool SetIndex(
    int component_index
    );

  /*
  Description:
    Set the component index value to the ON_ModelComponent::Unset.ModelComponentIndex()
    and change the state so ModelComponentIndexIsSet() returns false.
  */
  bool ClearIndex();

  /*
  Description:
    Calling LockModelComponentIndex() will prohibit future changes to the ModelComponentIndex attribute.
  */
  void LockIndex();

  /*
  Returns:
    True if the ModelComponentIndex attribute is locked.
  */
  bool IndexIsLocked() const;

  /*
  Returns:
    True if the ModelComponentIndex attribute is set.
  */
  bool IndexIsSet() const;

  ///////////////////////////////////////////////////////////////////////////////
  //
  // Parent object interface
  //
  //
  const ON_UUID& ParentId() const;

  bool ParentIdIsNil() const;
  bool ParentIdIsNotNil() const;

  bool SetParentId(
    const ON_UUID& parent_id
    );
  bool ClearParentId();
  void LockParentId();
  bool ParentIdIsLocked() const;
  bool ParentIdIsSet() const;

  ///////////////////////////////////////////////////////////////////////////////
  //
  // Model component locked, hidden, deleted, selected, highlights, damaged, ... status interface
  //
  //
  ON_ComponentStatus ModelComponentStatus() const;

  bool SetModelComponentStatus(
    ON_ComponentStatus component_status
    );

  bool ClearModelComponentStatus();

  void LockModelComponentStatus();

  bool ModelComponentStatusIsLocked() const;

  bool ModelComponentStatusIsSet() const;

  /*
  Returns:
    The component's deleted state.
  Remarks:
    Deleted components can be undeleted.
  */
  bool IsDeleted() const;

  /*
  Parameters:
    bDeleted - [in]
    manifest - [in/out]
      optional manifest to update
  Returns:
    True if the component's deleted state was changed from
    !bDeleted to bDeleted and all other name and manifest information
    was updated as expected.
  */
  bool SetDeletedModelComponentState(
    bool bDeleted,
    class ON_ComponentManifest* manifest
    );

  /*
  Returns:
    The component's user interface locked state.
  Remarks:
    This is a user interface locked state and does not effect
    changing the component values.
  */
  bool IsLocked() const;

  void SetLockedModelComponentState(
    bool bLocked 
    );

  /*
  Returns:
    The component's user interface hidden state.
  Remarks:
    This is a user interface hidden state and does not effect
    changing the component values.
  */
  bool IsHidden() const;

  void SetHiddenModelComponentState(
    bool bHidden 
    );


  ///////////////////////////////////////////////////////////////////////////////
  //
  // Name interface
  //
  //

  /*
  Returns:
    Value of the Name attribute.
  Remarks:
    If the component is in a model, then the name is unique among all components in
    the model. Names are formatted as reference : parent::leaf. 
    For example in "A.3dm : Z", "A.3dm" is the reference and "Z" is the leaf. 
    For a layer full path "X::Y::Z", "X::Y" is the parent and "Z" is the leaf.
    For most models, only the leaf is present in the name. 
    The reference portion appears when a model component originates in a reference file
    (a linked instance definition with reference component names or a worksession reference).
    Components with a tree hierarchy, like layers, can have a parent and leaf.
  */
  const ON_wString Name() const;

  const ON_wString DeletedName() const;

  /*
  Parameters:
    component_name - [out]
  Returns:
    A pointer to the string in component_name.
  */
  const wchar_t* GetName(
    ON_wString& component_name
    ) const;
  
  /*
  Description:
    Get a platform independent hash of the name suitable for equality testing
    and binary searching.
    When testing for equality or doing binary searches, using ON_NameHash values
    is faster than using the CompareName or ON_wString::CompareAttributeName.
  */
  const ON_NameHash& NameHash() const;
  const ON_NameHash& DeletedNameHash() const;

  /*
  Parameters:
    new_name - [in]      
  Returns:
    If new_name is empty or a valid component name, then name hash this component would have if SetName(new_name) were called.
    If new_name is not valid, then ON_NameHash::UnsetNameHash is returned.
  Remarks:
    This function trims leading and trailing white space, includes the parent id when 
    ON_ModelComponent::UniqueNameIncludesParent(ComponentType()) is true,
    and uses ON_ModelComponent::IsValidComponentName() to determine if a 
    non-empty name is valid.    
  */
  const ON_NameHash NewNameHash(
    const wchar_t* new_name
    ) const;

  /*
  Description:
    Returns the string " : ".  This is the string Rhino uses
    to separate the reference file names from and model component names
    read from those files.

  Example:
      File A.3dm contains a layer "alpha", dimstyle "a1", an embedded block "A_blk",
      and a linked block "X" referencing B.3dm with reference component names.
      File B.3dm contains a layer "beta", dimstyle "b1", an embedded block "B_blk",
      and linked block "Y" referencing C.3dm.
      File C.3dm contains a layer gamma, dimstyle "c1", an embedded block "C_blk",
      and linked block "Z" referencing D.3dm.
      File D.3dm contains a layer "delta", dimstyle "d1", and an embedded block "D_blk".
      
      Reading file A.3dm will create the following components:
      Layers:
        alpha
        X>B.3dm
          beta (full layer path "X>B.3dm::beta")
        Y>C.3dm
          gamma (full layer path "Y>C.3dm::gamma")
        Z>D.3dm
          delta (full layer path "Z>D.3dm::delta")
      Blocks:
        X
        A_blk
        Y
        B.3dm : B_blk
        Z
        C.3dm : C_blk
        D.3dm : D_blk
      Annotation styles
        a1
        B.3dm : b1
        C.3dm : c1
        D.3dm : d1

  See Also:
    ON_ModelComponent::ReferencePrefixDelimiter = " : "
    ON_ModelComponent::ReferencePrefixSeparator = ">"
    ON_ModelComponent::NamePathSeparator = "::"
  */
  static const ON_wString ReferencePrefixDelimiter;

  /*
  Description:
    Returns the string ">".  This is the string Rhino uses
    to separate the block definition name and linked file name
    in grandparent layers.

  Example:
      File A.3dm contains a layer "alpha", dimstyle "a1", an embedded block "A_blk",
      and a linked block "X" referencing B.3dm with reference component names.
      File B.3dm contains a layer "beta", dimstyle "b1", an embedded block "B_blk",
      and linked block "Y" referencing C.3dm.
      File C.3dm contains a layer gamma, dimstyle "c1", an embedded block "C_blk",
      and linked block "Z" referencing D.3dm.
      File D.3dm contains a layer "delta", dimstyle "d1", and an embedded block "D_blk".
      
      Reading file A.3dm will create the following components:
      Layers:
        alpha
        X>B.3dm
          beta (full layer path "X>B.3dm::beta")
        Y>C.3dm
          gamma (full layer path "Y>C.3dm::gamma")
        Z>D.3dm
          delta (full layer path "Z>D.3dm::delta")
      Blocks:
        X
        A_blk
        Y
        B.3dm : B_blk
        Z
        C.3dm : C_blk
        D.3dm : D_blk
      Annotation styles
        a1
        B.3dm : b1
        C.3dm : c1
        D.3dm : d1

  See Also:
    ON_ModelComponent::ReferencePrefixDelimiter = " : "
    ON_ModelComponent::ReferencePrefixSeparator = ">"
    ON_ModelComponent::NamePathSeparator = "::"
  */
  static const ON_wString ReferencePrefixSeparator;


  /*
  Description:
    Returns the string "::".  This is the string Rhino uses in layer
    full path names to separate the names of individual layers.

  Example:
      If a model has layers
      A
        B
          C
      then the full path names are
      "A", "A::B", "A::B::C".

  See Also:
    ON_ModelComponent::ReferencePrefixDelimiter = " : "
    ON_ModelComponent::ReferencePrefixSeparator = ">"
    ON_ModelComponent::NamePathSeparator = "::"
  */
  static const ON_wString NamePathSeparator;

  ///*
  //Description:
  //Parameters:
  //  reference_prefix - [in]
  //Returns:
  //  The worksession component name reference prefix.
  //Example:
  //  "[ A.3dm ]" = ON_ModelComponent::WorksessionReferencePrefix("A.3dm")
  //*/
  //static const ON_wString WorksessionReferencePrefix(
  //  const wchar_t* reference_prefix,
  //  bool bAppendReferencePrefixDelimiter
  //);


  /*
  Description:
    Test a string to see if its beginning matches the 
    string returned by ON_ModelComponent::NameReferenceDelimiter.
  Parameters:
    s - [in];
      string to test.
  Returns:
    null:
      The beginning of the string does not match ON_ModelComponent::NameReferenceDelimiter.
    non-null:
      The beginning of the string matches ON_ModelComponent::NameReferenceDelimiter.
      The returned pointer is the first character in s after the last character
      of the delimiter.  Put another way, if the beginning of s matches
      the string ON_ModelComponent::NameReferenceDelimiter, then the returned pointer is
      s + ON_ModelComponent::NameReferenceDelimiter.Length().
  */
  static const wchar_t* IsReferencePrefixDelimiter(
    const wchar_t* s
  );

  /*
  Description:
    Test a string to see if its beginning matches the 
    string returned by ON_ModelComponent::NameReferenceSeparator.
  Parameters:
    s - [in];
      string to test.
  Returns:
    null:
      The beginning of the string does not match ON_ModelComponent::NameReferenceSeparator.
    non-null:
      The beginning of the string matches ON_ModelComponent::NameReferenceSeparator.
      The returned pointer is the first character in s after the last character
      of the delimiter.  Put another way, if the beginning of s matches
      the string ON_ModelComponent::NameReferenceSeparator, then the returned pointer is
      s + ON_ModelComponent::NameReferenceSeparator.Length().
  */
  static const wchar_t* IsReferencePrefixSeparator(
    const wchar_t* s
  );

  /*
  Description:
    Test a string to see if its beginning matches the 
    string returned by ON_ModelComponent::NamePathSeparator.
  Parameters:
    s - [in];
      string to test.
  Returns:
    null:
      The beginning of the string does not match ON_ModelComponent::NamePathSeparator.
    non-null:
      The beginning of the string matches ON_ModelComponent::NamePathSeparator.
      The returned pointer is the first character in s after the last character
      of the delimiter.  Put another way, if the beginning of s matches
      the string ON_ModelComponent::NamePathSeparator, then the returned pointer is
      s + ON_ModelComponent::NamePathSeparator.Length().
  */
  static const wchar_t* IsNamePathSeparator(
    const wchar_t* s
  );

  /*
  Example:
    If a full layer name is "A.3dm : X::Y::Z", then
    reference_prefix = "A.3dm"
    name_parent = "X::Y"
    name_leaf = "Z"
  */
  static void SplitName(
    const wchar_t* name,
    ON_wString& reference_prefix,
    ON_wString& name_parent,
    ON_wString& name_leaf
  );

  /*
  Parameters:
    name - [in]
  Example:
    If the name is "A.3dm : X", then "A.3dm" is returned.
  */
  static const ON_wString NameReferencePrefix(
    const wchar_t* name
  );

  /*
  Parameters:
    name - [in]
    bIncludeReference - [in]
  Example:
    If the name is "A.3dm>B.3dm : X::Y::Z" and bIncludeReference is true, 
    then "A.3dm>B.3dm : X::Y" is returned.
    If the name is "A.3dm>B.3dm : X::Y::Z" and bIncludeReference is false, 
    then "X::Y" is returned.
  */
  static const ON_wString NameParent(
    const wchar_t* name,
    bool bIncludeReference
  );

  /*
  Example:
    If the name is "A.3dm>B.3dm : X::Y::Z", 
    then name_leaf = "Z" is returned.
  */
  static const ON_wString NameLeaf(
    const wchar_t* name
  );

  /*
  Parameters:
    name - [in]
  Example:
    If the name is "A.3dm : X", then "X" is returned.
  */
  static const ON_wString RemoveReferencePrefix(
    const wchar_t* name
  );

  /*
  Description:
    Remove all occurrences of ON::NameReferenceDelimiter() from name.
  */
  static const ON_wString RemoveAllReferencePrefixDelimiters(
    const wchar_t* name
  );

  /*
  Description:
    Remove any trailing occurrence of ON_ModelComponent::NameReferenceDelimiter from name.
  Example:
    "A.3dm" = ON_ModelComponent::RemoveTrailingRemoveReferencePrefixDelimiter("A.3dm : ");
  */
  static const ON_wString RemoveTrailingReferencePrefixDelimiter(
    const wchar_t* name
  );

  /*
  Description:
    Remove any trailing occurrence of ON_ModelComponent::NameReferenceSeparator from name.
  */
  static const ON_wString RemoveTrailingReferencePrefixSeparator(
    const wchar_t* name
  );

  /*
  Description:
    Remove any trailing occurrence of ON_ModelComponent::NamePathSeparator from name.
  */
  static const ON_wString RemoveTrailingNamePathSeparator(
    const wchar_t* name
  );


  
private:
  const ON_NameHash& Internal_NameHash() const;

public:
  /*
  Description:
    Expert user function that gets a pointer to the name.
  Returns:
    A pointer to the string that contains the name. This pointer
    must be used immediately and then discarded before any code
    can possibly call SetName() or the ON_ModelComponent destructor
    could be called.
  Remarks:
    About the only good use for this function is when a model component is
    persistent and the name is needed for a formatted string.  For any
    other use, call the Name() function and store the result in an
    ON_wString.  This function is dangerous because the returned pointer
    will be invalid if SetName() is called.
  */
  const wchar_t* NameAsPointer() const;

  /*
  Returns:
    true if the name is unset or is set to the empty string.
  */
  bool NameIsEmpty() const;

  /*
  Returns:
    true if the name is set and the value is not the empty string.
  */
  bool NameIsNotEmpty() const;

  /*
  Parameters:
    component_name - [in]
      Leading and trailing nonzero unicode code points with values <= ON_wString::Space are ignored.
  Returns:
    true 
      if the name attribute was changed to component_name or is already equal to component_name.
    false 
      False is returned and no changes are made if 
      the name attribute is locked and component_name != locked value 
      or
      component_name is not empty and ON_ModelComponent::IsValidComponentName(component_name) is false.
  Remarks:
    If component_name is nullptr or the empty string, the NameIsSet() state will still be true.
  */
  bool SetName(
    const wchar_t* component_name
    );

  /*
  Description:
    Change the name of a component and optionally update a manifest.
  Parameters:
    new_name - [in]
      New name for the component.
    manifest - [in]
      nullptr or a manifest with an item for the component.
  */
  bool ChangeName(
    const wchar_t* new_name,
    class ON_ComponentManifest* manifest
  );

  /*
  Description:
    Set the component name value to the ON_ModelComponent::Unset.Name()
    and change the state so NameIsSet() and DeletedNameIsSet() both return false.
  */
  bool ClearName();

  /*
  Description:
    Calling LockName() will prohibit future changes to the Name attribute.
  */
  void LockName();

  /*
  Returns:
    True if the Name attribute is locked.
  */
  bool NameIsLocked() const;

  /*
  Returns:
    True if the name attribute is set.
  Remarks:
    At most one of NameIsSet() and DeletedNameIsSet() is true.
    A name can be set to the empty string.
  */
  bool NameIsSet() const;

  /*
  Returns:
    True if the deleted name attribute is set.
  Remarks:
    At most one of NameIsSet() and DeletedNameIsSet() is true.
  */
  bool DeletedNameIsSet() const;

  /*
  Description:
    If NameIsSet() is true, then the name is deleted in a way that can be undone by calling UndeleteName() and
    the DeletedNameIsSet() property is changed to true.

    If NameIsSet() is false or NameIsLocked() is true, then nothing is changed.

    Note that a name can be set to the empty string and there is a difference between
    a name being set to the empty string and a name being unset.
    If you want to make the name attribute unset, call ClearName().
  */
  bool DeleteName();

  bool UndeleteName();

  void LockAllSettingsExceptName();
  bool SetLocalizedSystemComponentName(
    const wchar_t* system_component_localized_name
    );

  /*
  Parameters:
    other_name -[in]
  Returns:
    ON_wString::CompareAttributeName(this->Name(), other_name)
  Remarks:
    CompareName() is the correct tool to use when looking up objects by name.
  */
  int CompareName(
    const ON_UUID& other_parent_id,
    const wchar_t* other_name
    ) const;
  int CompareName(
    const wchar_t* other_name
    ) const;

  /*
  Parameters:
    other_name -[in]
  Returns:
    int rc = ON_wString::CompareAttributeName(this->Name(), other_name);
    return (0 != rc) ? rc : ON_wString::CompareOrdinal(this->Name(), other_name, false);
  Remarks:
    CompareNameExact() is the correct tool to use when detecting changes in
    case are important.  Use CompareName() when searching for components by name. 
  */
  int CompareNameExact(
    const ON_UUID& other_parent_id,
    const wchar_t* other_name
    ) const;
  int CompareNameExact(
    const wchar_t* other_name
    ) const;


  /*
  Parameters:
    a -[in]
    b -[in]
  Returns:
    ON_wString::CompareAttributeName(a.Name(), b.Name() )
  Remarks:
    CompareName() is the correct tool to use when looking up objects by name.
  */
  static int CompareName(
    const ON_ModelComponent& a,
    const ON_ModelComponent& b
    );

  /*
  Parameters:
    a -[in]
    b -[in]
  Returns:
    int rc = ON_wString::CompareAttributeName(a.Name(), b.Name());
    return (0 != rc) ? rc : ON_wString::CompareOrdinal(a.Name(), b.Name(), false);
  Remarks:
    CompareNameExact() is the correct tool to use when detecting changes in
    case are important.  Use CompareName() when searching for components by name. 
  */
  static int CompareNameExact(
    const ON_ModelComponent& a,
    const ON_ModelComponent& b
    );

  static int CompareId(
    const ON_ModelComponent& a,
    const ON_ModelComponent& b
    );

  /*
  Description 
    Call ON_ModelComponent::CompareName() and then ON_ModelComponent::CompareId().
    When used for sorting, will be sorted by name and then by id.
  */
  static int CompareNameAndId(
    const ON_ModelComponent& a,
    const ON_ModelComponent& b
    );

  /*
  Description 
    Call ON_ModelComponent::Id()and then ON_ModelComponent::CompareName().
    When used for sorting, will be sorted by id and then by name.
  */
  static int CompareIdAndName(
    const ON_ModelComponent& a,
    const ON_ModelComponent& b
    );

  /*
  Description:
    Set a component's id, name and index to the manifest_item values.
  Parameters:
    manifest_item - [in]
    manifest_name - [in]
    bSetId - [in]
      Set the component id to manifest_item.m_manifest_id.
    bSetParentId - [in]
      Use manifest_item.NameHash().ParentId()
    bSetName - [in]
      Set the component name to manifest_name.
    bSetIndex - [in]
      Set the component index to manifest_item.m_manifest_index.
  */
  bool SetIdentification(
    const class ON_ComponentManifestItem& manifest_item,
    const wchar_t* manifest_name,
    bool bSetId,
    bool bParentId,
    bool bSetName,
    bool bSetIndex
    );
  

  ///////////////////////////////////////////////////////////////////////////////
  //
  // General attributes interface
  //
  //

  /*
  Description:
    Writes the attributes identified by the component_filter parameter.
  Parameters:
    attributes_filter - [in]
      A bitfield that determines which attributes will be cleared.
  Returns:
    a bitfield indicating which attributes were cleared.
    (Locked attributes cannot be cleared.)
  */
  unsigned int ClearModelComponentAttributes(
    unsigned int attributes_filter
    );

  /*
  Returns:
    The runtime serial number.  
    This value is unique for every instance of an ON_ModelComponent class.  
    This value is never saved in .3dm archives.
  */
  ON__UINT64 RuntimeSerialNumber() const;

  /*
  Returns:
    The next ON_ModelComponent instance will have runtime serial number
    >= ON_ModelComponent::NextRuntimeSerialNumber();
  */
  static ON__UINT64 NextRuntimeSerialNumber();

  /*
  Description:
    Whenever an attribute is changed, the content version number is incremented.
    The ContentVersionNumber() is commonly used by consumers of the model 
    component attributes to trigger updates when needed.
  Remarks:
    The ContentVersionNumber value is copied by the copy constructor and operator=.
    The value is not saved in .3dm archives.
  */
  ON__UINT64 ContentVersionNumber() const;

  /*
  Returns:
    True if this model component is a system constant.  
  Remarks:
    An incomplete list of system constant model components is below:

      ON_ModelComponent::Unset

      ON_InstanceDefinition::Empty

      ON_Linetype::Unset
      ON_Linetype::Continuous
      ON_Linetype::ByLayer
      ON_Linetype::ByParent

      ON_Layer::Unset
      ON_Layer::Default

      ON_TextStyle::Unset
      ON_TextStyle::Default
      ON_TextStyle::ByLayer
      ON_TextStyle::ByParent

      ON_DimStyle::Unset
      ON_DimStyle::Default
      ON_DimStyle::DefaultInchDecimal
      ON_DimStyle::DefaultInchFractional
      ON_DimStyle::DefaultFootInchArchitectural
      ON_DimStyle::DefaultMillimeterSmall
      ON_DimStyle::DefaultMillimeterLarge
      ON_DimStyle::DefaultMillimeterArchitectural
  */
  bool IsSystemComponent() const;

  bool EraseIdentification(
    bool bIgnoreLocks
    );

  bool SetAsSystemComponent();
  bool SetAsUnsetSystemComponent();

private:
  bool Internal_SetAsSystemComponent(
    bool bUnsetSystemComponent
    );

protected:
  /*
    Classes derived from ON_ModelComponent should have private data members and
    call IncrementContentVersionNumber() when the data member value changes.
  */
  void IncrementContentVersionNumber() const;

private:
  const ON__UINT64 m_runtime_serial_number;  
  mutable ON__UINT64 m_content_version_number = 0;
  ON__UINT32 m_model_serial_number = 0;
  ON__UINT32 m_reference_model_serial_number = 0;
  ON__UINT32 m_linked_idef_serial_number = 0;
  ON_ModelComponent::Type m_component_type = ON_ModelComponent::Type::Unset;
 
  ON__UINT16 m_locked_status = 0;
  ON__UINT16 m_set_status = 0;
  ON_ComponentStatus m_component_status = ON_ComponentStatus::NoneSet;
  ON__UINT16 m_reserved2 = 0;

  // m_component_index is the index of the component in the model identified 
  // by m_model_serial_number.
  //
  // Some components use small negative indices (-1,-2,-3,...) to identify
  // default or constant components.  An incomplete list includes these:
  //   ON_TextStyle::Default, (index = -1) 
  //   ON_TextStyle::ByLayer,  (index = -2) 
  //   ON_TextStyle::ByParent,  (index = -3) 
  //   ON_Linetype::Continuous,  (index = -1) 
  //   ON_Linetype::ByLayer,  (index = -2) 
  //   ON_Linetype::ByParent,  (index = -3) 
  //
  // ON_UNSET_INT_INDEX is a large negative number.
  ON__INT32 m_component_index = ON_UNSET_INT_INDEX;  
  ON__UINT32 m_reserved3 = 0;

  ON_UUID m_component_id = ON_nil_uuid;
  ON_UUID m_component_parent_id = ON_nil_uuid;
  // lazy evaluation is used top initialize m_component_name_hash
  mutable ON_NameHash m_component_name_hash;

  ON_wString m_component_name;

public:
  // For internal use.  Never call this function.
  static unsigned int Internal_SystemComponentHelper();

private:
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 )
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // This warning is not correct.
  // Internal_RuntimeSerialNumberGenerator is private and all code that manages it is explicitly implemented in the DLL.
  static std::atomic<ON__UINT64> Internal_RuntimeSerialNumberGenerator;
#pragma ON_PRAGMA_WARNING_POP
};


class ON_CLASS ON_ModelComponentContentMark
{
public:
  static const ON_ModelComponentContentMark Unset;
public:
  ON_ModelComponentContentMark() = default;
  ~ON_ModelComponentContentMark() = default;
  ON_ModelComponentContentMark(const ON_ModelComponentContentMark&) = default;
  ON_ModelComponentContentMark& operator=(const ON_ModelComponentContentMark&) = default;

  /*
  Description:
    Save the current content state of model_component.
  Parameters:
    model_component - [in]
  */
  ON_ModelComponentContentMark(
    const class ON_ModelComponent& model_component
  );

  /*
  Description:
    Save the current content state of model_component.
  Parameters:
    model_component - [in]
  */
  ON_ModelComponentContentMark(
    const class ON_ModelComponent* model_component
  );

  /*
  Description:
    Save the current content state of model_component.
  Parameters:
    model_component - [in]
  */
  void Set(
    const class ON_ModelComponent& model_component
  );

  /*
  Description:
    Save the current content state of model_component.
  Parameters:
    model_component - [in]
  */
  void Set(
    const class ON_ModelComponent* model_component
  );
  
  /*
  Parameters:
    model_component - [in]
  Returns:
    true if the content of model_component is identical
    to the content state saved in this ON_ModelComponentContentMark.
    false otherwise.
  */
  bool EqualContent(
    const class ON_ModelComponent& model_component
  ) const;
    
  /*
  Parameters:
    model_component - [in]
  Returns:
    true if the content of model_component is identical
    to the content state saved in this ON_ModelComponentContentMark.
    false otherwise.
  */
  bool EqualContent(
    const class ON_ModelComponent* model_component
  ) const;
  
  /*
  Parameters:
    lhs - [in]
    rhs - [in]
  Returns:
    true if lhs and rhs are identical.
    false otherwise.
  */
  static bool EqualContent(
    const ON_ModelComponentContentMark& lhs,
    const ON_ModelComponentContentMark& rhs
  );

  /*
  Returns:
    Saved model component id.
  */
  ON_UUID ComponentId() const;

  /*
  Returns:
    Saved model component runtime serial number.
  */
  ON__UINT64 ComponentRuntimeSerialNumber() const;

  /*
  Returns:
    Saved model component content version number.
  */
  ON__UINT64 ComponentContentVersionNumber() const;

  /*
  Returns:
    Saved model component type.
  */
  ON_ModelComponent::Type ComponentType() const;

  /*
  Returns:
    True if a model component content state is saved in this ON_ModelComponentContentMark.
    False otherwise.
  */
  bool IsSet() const;

  /*
  Returns:
    True if a model component content state is saved in this ON_ModelComponentContentMark.
    False otherwise.
  */
  bool IsUnset() const;

private:
  ON_UUID m_component_id = ON_nil_uuid;
  ON__UINT64 m_component_serial_number = 0;  
  ON__UINT64 m_component_content_version_number = 0;
  ON_ModelComponent::Type m_component_type = ON_ModelComponent::Type::Unset;

private:
  unsigned char m_reserved1 = 0;
  unsigned char m_reserved2 = 0;
  unsigned char m_reserved3 = 0;
  unsigned int m_reserved4 = 0;
};

bool operator==(
  const ON_ModelComponentContentMark& lhs,
  const ON_ModelComponentContentMark& rhs
  );

bool operator!=(
  const ON_ModelComponentContentMark& lhs,
  const ON_ModelComponentContentMark& rhs
  );

class ON_CLASS ON_ModelComponentTypeIterator
{
public:
  // Default constructor creates ON_ModelComponentTypeIterator::Empty
  ON_ModelComponentTypeIterator() ON_NOEXCEPT;

  ~ON_ModelComponentTypeIterator() = default;
  ON_ModelComponentTypeIterator(const ON_ModelComponentTypeIterator&) = default;
  ON_ModelComponentTypeIterator& operator=(const ON_ModelComponentTypeIterator&) = default;

  /*
  Parameters:
    type_count - [in] number of types
    types - [in]
      list of types to iterate over
  */
  ON_ModelComponentTypeIterator(
    size_t type_count,
    const ON_ModelComponent::Type* types
    ) ON_NOEXCEPT;
  
  // Contains no types
  static const ON_ModelComponentTypeIterator Empty;

  // Contains all explicit component types (excludes Unset and Mixed).
  static const ON_ModelComponentTypeIterator ExplicitComponentTypes;

  // Every type in ON_ModelComponentTypeIterator::ExplicitComponents
  // except Image, RenderLight, ModelGeometry, and HistoryRecord
  // The types in ON_ModelComponentTypeIterator::Tables
  // identify the most commonly used "table" component types.
  static const ON_ModelComponentTypeIterator TableComponentTypes;

  // Number of types in the iterator
  unsigned int TypeCount() const;

  /*
  Description:
    Sets the iterator to point to the first available type. 
  Returns:
    The first available type.
  */
  ON_ModelComponent::Type FirstType();

  /*
  Description:
    Sets the iterator to point to the last available type. 
  Returns:
    The last available type.
  */
  ON_ModelComponent::Type LastType();

  /*
  Description:
    Increments the iterator and returns the new type.
  Returns:
    The new type.
    ON_ModelComponent::Type::Unset if the iterator is incremented the last type.
  */
  ON_ModelComponent::Type NextType();
  
  /*
  Description:
    Decrements the iterator and returns the new type.
  Returns:
    The new type
    ON_ModelComponent::Type::Unset if the iterator is decremented the first type.
  */
  ON_ModelComponent::Type PreviousType();

  /*
  Description:
    Decrements the iterator and returns the new type.
  Returns:
    The current type.
  */
  ON_ModelComponent::Type CurrentType() const;

private:
  ON__INT32 m_type_count = 0;

  // -1 iterated before first, m_type_count = iterated past last
  ON__INT32 m_current_index = ON_UNSET_UINT_INDEX; 

  ON_ModelComponent::Type m_types[32];
};

/// <summary>
/// ON_ModelComponentReference is a persistent reference to a model component.
/// ON_ModelComponentReference and ON_ModelComponentWeakReference are based on
/// like std::shared_ptr and std::weak_ptr.
/// </summary>
class ON_CLASS ON_ModelComponentReference
{
public:
  static const ON_ModelComponentReference Empty;
  
  // No = default to insure m_sp is completely managed in the opennurbs DLL.
  ON_ModelComponentReference() ON_NOEXCEPT; // No = default to insure m_sp is completely managed in the opennurbs DLL.
  ~ON_ModelComponentReference(); // No = default to insure m_sp is completely managed in the opennurbs DLL.
  ON_ModelComponentReference(const ON_ModelComponentReference&) ON_NOEXCEPT; // No = default to insure m_sp is completely managed in the opennurbs DLL.
  ON_ModelComponentReference& operator=(const ON_ModelComponentReference&); // No = default to insure m_sp is completely managed in the opennurbs DLL.
  
#if defined(ON_HAS_RVALUEREF)
  ON_ModelComponentReference( ON_ModelComponentReference&& ) ON_NOEXCEPT;
  ON_ModelComponentReference& operator=( ON_ModelComponentReference&& );
#endif

  ON_ModelComponentReference(
    const class ON_ModelComponentWeakReference& weak_ref
  )  ON_NOEXCEPT;

  ON_ModelComponentReference& operator=( const ON_ModelComponentWeakReference& );


  ON_ModelComponentReference(
    std::shared_ptr<ON_ModelComponent>& sp
    ) ON_NOEXCEPT;

  ON_ModelComponentReference& operator=(
    std::shared_ptr<ON_ModelComponent>& sp
    );
  
  /*
  Parameters:
    constant_system_component - [in]
      A constant system component that exists for the duration of 
      the application.
  Remarks:
    See ON_ModelComponent::CreateConstantSystemComponentReference()
    for more information about constant system components.

  */
  static ON_ModelComponentReference CreateConstantSystemComponentReference(
    const class ON_ModelComponent& constant_system_component
    ) ON_NOEXCEPT;

  /*
  Parameters:
    model_component - [in]
    bManagedComponentReference - [in]
      true
        model_component will be deleted by the last ON_ModelComponentReference
        and must have been created by call to operator new() with heap allocation.
      false 
        model_component must remain in scope until the last ON_ModelComponentReference
        is destroyed.
  Remarks:
    The input pointer will be managed and deleted by the returned
    by ON_ModelComponentReference.
  */
  static ON_ModelComponentReference CreateForExperts(
    class ON_ModelComponent* model_component,
    bool bManagedComponentReference
    ) ON_NOEXCEPT;

  /*
  Return:
    A pointer to the managed model component or nullptr.
  See Also:
    ON_ModelComponentRef::ExclusiveModelComponent();
  */
  const class ON_ModelComponent* ModelComponent() const ON_NOEXCEPT;

  /*
  Return:
    If this is the only reference to a component, the a pointer to
    that component is returned.
    Otherwise, nullptr is returned
  See Also:
    ON_ModelGeometryComponent::Attributes()
    ON_ModelGeometryComponent::Geometry()
    ON_ModelGeometryComponent::ExclusiveAttributes()
    ON_ModelGeometryComponent::ExclusiveGeometry();
    ON_ModelComponentRef::ExclusiveModelComponent();
    ONX_Model::ComponentFromRuntimeSerialNumber()
  Remarks:
    If .NET or other wrappers using "lazy garbage collection" memory management are in use,
    there may be stale references awaiting garbage collection and this function will return
    nullptr when you think it should not. 
    For this function to work reliably, the ONX_Model and its components 
    and references should be in well constructed C++ code with carefully 
    crafted memory management.
  */
  class ON_ModelComponent* ExclusiveModelComponent() const ON_NOEXCEPT;

  ON__UINT64 ModelComponentRuntimeSerialNumber() const ON_NOEXCEPT;
  const ON_UUID ModelComponentId() const ON_NOEXCEPT;
  const ON_NameHash ModelComponentNameHash() const ON_NOEXCEPT;
  int ModelComponentIndex() const ON_NOEXCEPT;

  unsigned int ReferenceCount() const ON_NOEXCEPT;
  
  bool IsEmpty() const ON_NOEXCEPT;

  void Dump(
    ON_TextLog& text_log
    ) const;

private:
  friend class ON_ModelComponentWeakReference;

#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_sp is private and all code that manages m_sp is explicitly implemented in the DLL.
  std::shared_ptr<ON_ModelComponent> m_sp;
#pragma ON_PRAGMA_WARNING_POP
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_ModelComponentReference>;
#endif

/// <summary>
/// ON_ModelComponentWeakReference is a weak shared reference to a model component.
/// ON_ModelComponentReference and ON_ModelComponentWeakReference are based on
/// like std::shared_ptr and std::weak_ptr.
/// </summary>
class ON_CLASS ON_ModelComponentWeakReference
{
public:
  static const ON_ModelComponentWeakReference Empty;

public:
  // No = default to insure m_sp is completely managed in the opennurbs DLL.
  ON_ModelComponentWeakReference() ON_NOEXCEPT; // No = default to insure m_sp is completely managed in the opennurbs DLL.
  ~ON_ModelComponentWeakReference(); // No = default to insure m_sp is completely managed in the opennurbs DLL.
  ON_ModelComponentWeakReference(const ON_ModelComponentWeakReference&) ON_NOEXCEPT; // No = default to insure m_sp is completely managed in the opennurbs DLL.
  ON_ModelComponentWeakReference& operator=(const ON_ModelComponentWeakReference&); // No = default to insure m_sp is completely managed in the opennurbs DLL.
  
#if defined(ON_HAS_RVALUEREF)
  ON_ModelComponentWeakReference( ON_ModelComponentWeakReference&& ) ON_NOEXCEPT;
  ON_ModelComponentWeakReference& operator=( ON_ModelComponentWeakReference&& );
#endif

  ON_ModelComponentWeakReference(
    const class ON_ModelComponentReference&
  )  ON_NOEXCEPT;

  ON_ModelComponentWeakReference& operator=( const ON_ModelComponentReference& );


private:
  friend class ON_ModelComponentReference;
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_weak_sp is private and all code that manages m_weak_sp is explicitly implemented in the DLL.
  std::weak_ptr<ON_ModelComponent> m_wp;
#pragma ON_PRAGMA_WARNING_POP
};

#endif
