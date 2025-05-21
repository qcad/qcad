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

#if !defined(OPENNURBS_3DM_ATTRIBUTES_INC_)
#define OPENNURBS_3DM_ATTRIBUTES_INC_

/*
Description: 
  Top level OpenNURBS objects have geometry and attributes.  The
  geometry is stored in some class derived from ON_Geometry and 
  the attributes are stored in an ON_3dmObjectAttributes class.
  Examples of attributes are object name, object id, display 
  attributes, group membership, layer membership, and so on.
*/

class ON_CLASS ON_3dmObjectAttributes : public ON_Object
{
  ON_OBJECT_DECLARE(ON_3dmObjectAttributes);

public:
  static const ON_3dmObjectAttributes Unset;
  static const ON_3dmObjectAttributes DefaultAttributes;

public:
  // ON_Object virtual interface.  See ON_Object for details.
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  void Dump( ON_TextLog& ) const override;
  unsigned int SizeOf() const override;
  bool Write(ON_BinaryArchive&) const override;
  bool Read(ON_BinaryArchive&) override;

  /*
  Returns:
    True if successful.
    (xform is invertable or didn't need to be).
  */
  ON_DEPRECATED_MSG("Prefer the version that takes a const ON_Geometry* - for object frame support.")
  bool Transform( const ON_Xform& xform );
  
  bool Transform(const ON_Geometry* pOriginalGeometry, const ON_Xform& xform);

  // attributes of geometry and dimension table objects
public:
  ON_3dmObjectAttributes();
  ~ON_3dmObjectAttributes();
  ON_3dmObjectAttributes(const ON_3dmObjectAttributes&);
  ON_3dmObjectAttributes& operator=(const ON_3dmObjectAttributes&);

  bool operator==(const ON_3dmObjectAttributes&) const;
  bool operator!=(const ON_3dmObjectAttributes&) const;

  // Initializes all attributes to the default values.
  void Default();


  bool UpdateReferencedComponents(
    const class ON_ComponentManifest& source_manifest,
    const class ON_ComponentManifest& destination_manifest,
    const class ON_ManifestMap& manifest_map
    ) override;

  // Interface ////////////////////////////////////////////////////////

  // An OpenNURBS object must be in one of three modes: normal, locked
  // or hidden.  If an object is in normal mode, then the object's layer
  // controls visibility and selectability.  If an object is locked, then
  // the object's layer controls visibility by the object cannot be selected.
  // If the object is hidden, it is not visible and it cannot be selected.
  ON::object_mode Mode() const;
  void SetMode( ON::object_mode ); // See Mode().

  /*
  Description:
    Use this query to determine if an object is part of an 
    instance definition.
  Returns:
    True if the object is part of an instance definition.
  */
  bool IsInstanceDefinitionObject() const;

  /*
  Returns:
    Returns true if object is visible.
  See Also:
    ON_3dmObjectAttributes::SetVisible
  */
  bool IsVisible() const;

  /*
  Description:
    Controls object visibility
  Parameters:
    bVisible - [in] true to make object visible, 
                    false to make object invisible
  See Also:
    ON_3dmObjectAttributes::IsVisible
  */
  void SetVisible( bool bVisible );

  // The Linetype used to display an OpenNURBS object is specified in one of two ways.
  // If LinetypeSource() is ON::linetype_from_layer, then the object's layer 
  // ON_Layer::Linetype() is used.
  // If LinetypeSource() is ON::linetype_from_object, then value of m_linetype is used.
  ON::object_linetype_source LinetypeSource() const;
  void SetLinetypeSource( ON::object_linetype_source ); // See LinetypeSource().

  // The color used to display an OpenNURBS object is specified in one of three ways.
  // If ColorSource() is ON::color_from_layer, then the object's layer 
  // ON_Layer::Color() is used.
  // If ColorSource() is ON::color_from_object, then value of m_color is used.
  // If ColorSource() is ON::color_from_material, then the diffuse color of the object's
  // render material is used.  See ON_3dmObjectAttributes::MaterialSource() to
  // determine where to get the definition of the object's render material.
  ON::object_color_source ColorSource() const;
  void SetColorSource( ON::object_color_source ); // See ColorSource().

  // The color used to plot an OpenNURBS object on paper is specified 
  // in one of three ways.
  // If PlotColorSource() is ON::plot_color_from_layer, then the object's layer 
  // ON_Layer::PlotColor() is used.
  // If PlotColorSource() is ON::plot_color_from_object, then value of PlotColor() is used.
  ON::plot_color_source PlotColorSource() const;
  void SetPlotColorSource( ON::plot_color_source ); // See PlotColorSource().

  ON::plot_weight_source PlotWeightSource() const;
  void SetPlotWeightSource( ON::plot_weight_source );

  /*
  Description:
    If "this" has attributes (color, plot weight, ...) with 
    "by parent" sources, then the values of those attributes 
    on parent_attributes are copied.
  Parameters:
    parent_attributes - [in]
    parent_layer - [in]
    control_limits - [in]
      The bits in control_limits determine which attributes may
      may be copied.
                1: visibility
                2: color
                4: render material
                8: plot color
             0x10: plot weight
             0x20: linetype
             0x40: display order
             0x80: clip participation
  Returns:
     The bits in the returned integer indicate which attributes were
     actually modified.

                1: visibility
                2: color
                4: render material
                8: plot color
             0x10: plot weight
             0x20: linetype
             0x40: display order
             0x80: clip participation
            0x100: section style
  */
  unsigned int ApplyParentalControl(
         const ON_3dmObjectAttributes& parent_attributes,
         const ON_Layer& parent_layer,
         unsigned int control_limits = 0xFFFFFFFF
         );

  unsigned int ApplyParentalControl(
    const ON_3dmObjectAttributes& parent_attributes,
    const ON_Layer& parent_layer,
    const ON_UUID& viewport_id,
    unsigned int control_limits = 0xFFFFFFFF
  );

  // Every OpenNURBS object has a UUID (universally unique identifier). When
  // an OpenNURBS object is added to a model, the value is checked.  If the
  // value is ON_nil_uuid, a new UUID is created.  If the value is not
  // ON_nil_uuid but it is already used by another object in the model, a new
  // UUID is created.  If the value is not ON_nil_uuid and it is not used by 
  // another object in the model, then that value persists. When an object
  // is updated, by a move for example, the value of m_uuid persists.
  ON_UUID m_uuid = ON_nil_uuid;

  // The m_name member is public to avoid breaking the SDK.
  // Use SetName() and Name() for proper validation.
  // OpenNURBS object have optional text names.  More than one object in
  // a model can have the same name and some objects may have no name.
  // ON_ModelComponent::IsValidComponentName(m_name) should be true.
  ON_wString m_name;

  bool SetName(
    const wchar_t* name,
    bool bFixInvalidName
  );

  const ON_wString Name() const;

  // OpenNURBS objects may have an URL.  There are no restrictions on what
  // value this URL may have.  As an example, if the object came from a
  // commercial part library, the URL might point to the definition of that
  // part.
  ON_wString m_url;

  // Layer definitions in an OpenNURBS model are stored in a layer table.
  // The layer table is conceptually an array of ON_Layer classes.  Every
  // OpenNURBS object in a model is on some layer.  The object's layer
  // is specified by zero based indices into the ON_Layer array.
  int m_layer_index = 0;

  // Linetype definitions in an OpenNURBS model are stored in a linetype table.
  // The linetype table is conceptually an array of ON_Linetype classes.  Every
  // OpenNURBS object in a model references some linetype.  The object's linetype
  // is specified by zero based indices into the ON_Linetype array.
  // index 0 is reserved for continuous linetype (no pattern)
  int m_linetype_index = -1;

  // Rendering material:
  //   If you want something simple and fast, set 
  //   m_material_index to the index of the rendering material 
  //   and ignore m_rendering_attributes.
  //   If you are developing a high quality plug-in renderer, 
  //   and a user is assigning one of your fabulous rendering 
  //   materials to this object, then add rendering material 
  //   information to the  m_rendering_attributes.m_materials[] 
  //   array. 
  //
  // Developers:
  //   As soon as m_rendering_attributes.m_materials[] is not empty,
  //   rendering material queries slow down.  Do not populate
  //   m_rendering_attributes.m_materials[] when setting 
  //   m_material_index will take care of your needs.
  int m_material_index = -1;
  ON_ObjectRenderingAttributes m_rendering_attributes;

  //////////////////////////////////////////////////////////////////
  //
  // BEGIN: Per object mesh parameter support
  //

  /*
  Parameters:
    mp - [in]
      per object mesh parameters
  Returns:
    True if successful.
  */
  bool SetCustomRenderMeshParameters(const class ON_MeshParameters& mp);

  /*
  Parameters:
    bEnable - [in]
      true to enable use of the per object mesh parameters.
      false to disable use of the per object mesh parameters.
  Returns:
    False if the object doe not have per object mesh parameters
    and bEnable was true.  Use SetMeshParameters() to set
    per object mesh parameters.
  Remarks:
    Sets the value of ON_MeshParameters::m_bCustomSettingsDisabled 
    to !bEnable
  */
  bool EnableCustomRenderMeshParameters(bool bEnable);

  /*
  Returns:
    Null or a pointer to fragile mesh parameters.
    If a non-null pointer is returned, copy it and use the copy.
    * DO NOT SAVE THIS POINTER FOR LATER USE. A call to 
      DeleteMeshParameters() will delete the class.
    * DO NOT const_cast the returned pointer and change its
      settings.  You must use either SetMeshParameters()
      or EnableMeshParameters() to change settings.
  Remarks:
    If the value of ON_MeshParameters::m_bCustomSettingsDisabled is
    true, then do no use these parameters to make a render mesh.
  */
  const ON_MeshParameters* CustomRenderMeshParameters() const;

  /*
  Description:
    Deletes any per object mesh parameters.
  */
  void DeleteCustomRenderMeshParameters();

  //
  // END: Per object mesh parameter support
  //
  //////////////////////////////////////////////////////////////////


  /*
  Description:
    Determine if the simple material should come from
    the object or from it's layer.
    High quality rendering plug-ins should use m_rendering_attributes.
  Returns:
    Where to get material information if you do are too lazy
    to look in m_rendering_attributes.m_materials[].
  */
  ON::object_material_source MaterialSource() const;

  /*
  Description:
    Specifies if the simple material should be the one
    indicated by the material index or the one indicated
    by the object's layer.
  Parameters:
    ms - [in]
  */
  void SetMaterialSource( ON::object_material_source ms );

  // If ON::color_from_object == ColorSource(), then m_color is the object's
  // display color.
  ON_Color      m_color;

  // If ON::plot_color_from_object == PlotColorSource(), then m_color is the object's
  // display color.
  ON_Color      m_plot_color;

  // Display order used to force objects to be drawn on top or behind each other
  // 0  = draw object in standard depth buffered order
  // <0 = draw object behind "normal" draw order objects
  // >0 = draw object on top of "normal" draw order objects
  // Larger number draws on top of smaller number.
  int m_display_order = 0;

  // Plot weight in millimeters.
  //   =0.0 means use the default width
  //   <0.0 means don't plot (visible for screen display, but does not show on plot)
  double m_plot_weight_mm = 0;

  // Used to indicate an object has a decoration (like an arrowhead on a curve)
  ON::object_decoration  m_object_decoration = ON::no_object_decoration;

  // When a surface object is displayed in wireframe, m_wire_density controls
  // how many isoparametric wires are used.
  //
  //   @table
  //   value    number of isoparametric wires
  //   -1       boundary wires
  //    0       boundary and knot wires 
  //    1       boundary and knot wires and, if there are no
  //            interior knots, a single interior wire.
  //   N>=2     boundary and knot wires and (N-1) interior wires
  int m_wire_density = 1;


  // If m_viewport_id is ON_nil_uuid, the object is active in all viewports.
  // If m_viewport_id is not ON_nil_uuid, then this object is only active in a
  // specific view. This field is primarily used to assign page space objects
  // to a specific page, but it can also be used to restrict model space to a
  // specific view.
  ON_UUID m_viewport_id = ON_nil_uuid;

  // Starting with V4, objects can be in either model space
  // or page space.  If an object is in page space, then
  // m_viewport_id is not nil and identifies the page it 
  // is on.
  ON::active_space m_space = ON::model_space;

#pragma region Section Attributes
  // Sections are the product of intersecting a plane with an object.
  // For surface type geometry (ON_Brep, ON_Extrusion, ON_SubD, ON_Mesh)
  // this intersection can result in curves as well as hatches for the
  // closed curves generated

  // Source for all section related attributes
  ON::SectionAttributesSource SectionAttributesSource() const;
  void SetSectionAttributesSource(ON::SectionAttributesSource source);

  /*
  Description:
    Attributes can have optional custom section style associated with them.
    This function adds a custom section style for this attribute.
  */
  void SetCustomSectionStyle(const ON_SectionStyle& sectionStyle);

  /*
  Description:
    Attributes can have optional custom section styles associated with them.
    This function returns the custom section style if one exists.
  Parameters:
    sectionStyle [out] - if not nullptr and a custom section style exists,
      the data in the custom section style is copied to sectionStyle
  */
  const ON_SectionStyle* CustomSectionStyle(ON_SectionStyle* sectionStyle = nullptr) const;

  /*
  Description:
    Remove any custom section style associated with this attribute
  */
  void RemoveCustomSectionStyle();
#pragma endregion

  // Per object linetype scale
  double LinetypePatternScale() const;
  void SetLinetypePatternScale(double scale);

  /*
  Description:
    Attributes can have optional custom linetypes associated with them. When a
    custom linetype is attached to an attribute, this linetype is used for an
    attribute instead of the linetype referenced by the linetype index. This
    function adds a custom linetype for this attribute.
  */
  void SetCustomLinetype(const ON_Linetype& linetype);

  /*
  Description:
    Attributes can have optional custom linetypes associated with them. This
    function returns the custom linetype if one exists. If a custom linetype is
    not attached to this attribute, then nullptr is returned
  */
  const ON_Linetype* CustomLinetype() const;

  /*
  Description:
    Remove any custom linetype associated with this attribute
  */
  void RemoveCustomLinetype();

#pragma region Hatch Specific Attributes
  ON_Color HatchBackgroundFillColor() const;
  void SetHatchBackgroundFillColor(const ON_Color& color);
  bool HatchBoundaryVisible() const;
  void SetHatchBoundaryVisible(bool on);
#pragma endregion

  ON::SectionLabelStyle ClippingPlaneLabelStyle() const;
  void SetClippingPlaneLabelStyle(ON::SectionLabelStyle style);

  ON_Plane ObjectFrame(const ON_COMPONENT_INDEX& ci) const;
  void SetObjectFrame(const ON_COMPONENT_INDEX& ci, const ON_Xform& wcs_to_ocs);
  void SetObjectFrame(const ON_COMPONENT_INDEX& ci, const ON_Plane& plane);

private:
  bool m_bVisible = true;
  // (m_mode % 16) = ON::object_mode values
  // (m_mode / 16) = ON::display_mode values
  unsigned char m_mode = ON::normal_object;
  unsigned char m_color_source = ON::color_from_layer;
  unsigned char m_plot_color_source = ON::plot_color_from_layer;
  unsigned char m_plot_weight_source = ON::plot_weight_from_layer;
  unsigned char m_material_source = ON::material_from_layer;
  unsigned char m_linetype_source = ON::linetype_from_layer;
  
  unsigned char m_reserved_0 = 0;

  ON_Plane m_object_frame = ON_Plane::UnsetPlane;
  
  ON_SimpleArray<int> m_group; // array of zero based group indices

private:
  void CopyHelper(const ON_3dmObjectAttributes& src);
  mutable class ON_3dmObjectAttributesPrivate* m_private = nullptr;

public:
  // group interface

  // returns number of groups object belongs to
  int GroupCount() const;

  // Returns and array an array of GroupCount() zero based 
  // group indices.  If GroupCount() is zero, then GroupList()
  // returns nullptr.
  const int* GroupList() const;

  // Returns GroupCount() and puts a list of zero based group indices 
  // into the array.
  int GetGroupList(ON_SimpleArray<int>&) const;

  // Returns the index of the last group in the group list
  // or -1 if the object is not in any groups
  int TopGroup() const;

  // Returns true if object is in group with the specified index
  bool IsInGroup(
    int // zero based group index
    ) const;

  // Returns true if the object is in any of the groups in the list
  bool IsInGroups(
    int,       // group_list_count
    const int* // group_list[] array
    ) const;

  // Returns true if object is in any of the groups in the list
  bool IsInGroups(
    const ON_SimpleArray<int>& // group_list[] array
    ) const;

  // Adds object to the group with specified index by appending index to
  // group list (If the object is already in group, nothing is changed.)
  void AddToGroup(
    int // zero based group index
    );

  // Removes object from the group with specified index.  If the 
  // object is not in the group, nothing is changed.
  void RemoveFromGroup(
    int // zero based group index
    );

  // Removes the object from the last group in the group list.
  void RemoveFromTopGroup();

  // Removes object from all groups.
  void RemoveFromAllGroups();

  // Decals.

  /*
  Description:
    Get an array of decals that are stored on this attributes object.
    Do not store or delete pointers from the array.
  */
  const ON_SimpleArray<ON_Decal*>& GetDecalArray(void) const;

  /*
  Description:
    Add a new decal to this attributes object. The returned pointer points to an object
    that is owned by the attributes. Do not store or delete it.
  */
  ON_Decal* AddDecal(void);

  /*
  Description:
    Remove a decal from this attributes object. Returns true if successful, else false.
  */
  bool RemoveDecal(ON_Decal& decal);

  /*
  Description:
    Remove all decals from this attributes object.
  */
  void RemoveAllDecals(void);

  // Mesh Modifiers.

  /*
  Description:
    Get the mesh modifiers that are stored on this attributes object.
  */
  class ON_MeshModifiers& MeshModifiers(void) const;

  // Display material references.

  /*
  Description:
    Searches for a matching display material.  For a given
    viewport id, there is at most one display material.
    For a given display material id, there can be multiple
    viewports.  If there is a display reference in the
    list with a nil viewport id, then the display material
    will be used in all viewports that are not explicitly
    referenced in other ON_DisplayMaterialRefs.

  Parameters:
    search_material - [in] 
    found_material - [out]
    
    If FindDisplayMaterialRef(), the input value of search_material
    is never changed.  If FindDisplayMaterialRef() returns true, 
    the chart shows the output value of display_material.  When
    there are multiple possibilities for a match, the matches
    at the top of the chart have higher priority.

    search_material  found_material
    input value      output value

    (nil,nil)        (nil,did) if (nil,did) is in the list.
    (nil,did)        (vid,did) if (vid,did) is in the list.
    (nil,did)        (nil,did) if (nil,did) is in the list.
    (vid,nil)        (vid,did) if (vid,did) is in the list
    (vid,nil)        (vid,did) if (nil,did) is in the list
    (vid,did)        (vid,did) if (vid,did) is in the list.

  Example:
    ON_UUID display_material_id = ON_nil_uuid;
    ON_Viewport vp = ...;
    ON_DisplayMaterialRef search_dm;
    search_dm.m_viewport_id = vp.ViewportId();
    ON_DisplayMaterialRef found_dm;
    if ( attributes.FindDisplayMaterial(search_dm, &found_dm) )
    {
      display_material_id = found_dm.m_display_material_id;
    }

  Returns:
    True if a matching display material is found.
  See Also:
    ON_3dmObjectAttributes::AddDisplayMaterialRef
    ON_3dmObjectAttributes::RemoveDisplayMaterialRef
  */
  bool FindDisplayMaterialRef(
      const ON_DisplayMaterialRef& search_material,
      ON_DisplayMaterialRef* found_material = nullptr
    ) const;

  /*
  Description:
    Quick way to see if a viewport has a special material.
  Parameters:
    viewport_id - [in]
    display_material_id - [out]
  Returns:
    True if a material_id is assigned.
  */
  bool FindDisplayMaterialId( 
        const ON_UUID& viewport_id, 
        ON_UUID* display_material_id = nullptr
        ) const;
     
  /*
  Description:
    Add a display material reference to the attributes.  If
    there is an existing entry with a matching viewport id,
    the existing entry is replaced.
  Parameters:
    display_material - [in]
  Returns:
    True if input is valid (material id != nil)
  See Also:
    ON_3dmObjectAttributes::FindDisplayMaterialRef
    ON_3dmObjectAttributes::RemoveDisplayMaterialRef
  */
  bool AddDisplayMaterialRef(
    ON_DisplayMaterialRef display_material
    );

  /*
  Description:
    Remove a display material reference from the list.
  Parameters:
    viewport_id - [in] Any display material references
      with this viewport id will be removed.  If nil,
      then viewport_id is ignored.
    display_material_id - [in]
      Any display material references that match the
      viewport_id and have this display_material_id
      will be removed.  If nil, then display_material_id
      is ignored.
  Returns:
    True if a display material reference was removed.
  See Also:
    ON_3dmObjectAttributes::FindDisplayMaterialRef
    ON_3dmObjectAttributes::AddDisplayMaterialRef
  */
  bool RemoveDisplayMaterialRef(
    ON_UUID viewport_id,
    ON_UUID display_material_id = ON_nil_uuid
    );

  /*
  Description:
    Remove the entire display material reference list.
  */
  void RemoveAllDisplayMaterialRefs();

  /*
  Returns:
    Number of display material references.
  */
  int DisplayMaterialRefCount() const;

  ON_SimpleArray<ON_DisplayMaterialRef> m_dmref;

private:
  bool Internal_WriteV5( ON_BinaryArchive& archive ) const;
  bool Internal_ReadV5( ON_BinaryArchive& archive );
};

#endif
