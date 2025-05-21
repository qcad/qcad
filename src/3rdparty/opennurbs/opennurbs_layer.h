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

#if !defined(OPENNURBS_LAYER_INC_)
#define OPENNURBS_LAYER_INC_

class ON_CLASS ON_Layer : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_Layer);

public:

  ON_Layer()  ON_NOEXCEPT;
  ~ON_Layer();
  ON_Layer(const ON_Layer&);
  ON_Layer& operator=(const ON_Layer&);

  static const ON_Layer Unset;   // index = ON_UNSET_INT_INDEX, id = nil
  static const ON_Layer Default; // index = -1, id set, unique and persistent

  /*
  Parameters:
    model_component_reference - [in]
    none_return_value - [in]
      value to return if ON_Layer::Cast(model_component_ref.ModelComponent())
      is nullptr
  Returns:
    If ON_Layer::Cast(model_component_ref.ModelComponent()) is not nullptr,
    that pointer is returned.  Otherwise, none_return_value is returned. 
  */
  static const ON_Layer* FromModelComponentRef(
    const class ON_ModelComponentReference& model_component_reference,
    const ON_Layer* none_return_value
    );

  bool UpdateReferencedComponents(
    const class ON_ComponentManifest& source_manifest,
    const class ON_ComponentManifest& destination_manifest,
    const class ON_ManifestMap& manifest_map
    ) override;

  //////////////////////////////////////////////////////////////////////
  //
  // ON_Object overrides
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump( ON_TextLog& ) const override; // for debugging

  bool Write(
         ON_BinaryArchive&  // serialize definition to binary archive
       ) const override;

  bool Read(
         ON_BinaryArchive&  // restore definition from binary archive
       ) override;

  ON::object_type ObjectType() const override;

  //////////////////////////////////////////////////////////////////////
  //
  // Interface

  // The PER_VIEWPORT_SETTINGS enum defines
  // the bits used to set masks in functions used
  // to specify and query per viewport layer settings.
  enum PER_VIEWPORT_SETTINGS : unsigned int
  {
    per_viewport_none              =  0,

    per_viewport_id               =  1,
    per_viewport_color            =  2,
    per_viewport_plot_color       =  4,
    per_viewport_plot_weight      =  8,
    per_viewport_visible          = 16,
    per_viewport_persistent_visibility = 32,

    per_viewport_all_settings     = 0xFFFFFFFF
    // (Developers: these values are used in file IO and must not be changed.)
  };

 /*
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then checks for per viewport
      settings for that specific viewport.
      If viewport_id is nil, then checks for per viewport settings
      in any viewport.
    settings_mask - [in]
      settings_mask is a bitfield that specifies which settings
      to check for.  The bits are defined in the
      ON_Layer::PER_VIEWPORT_PROPERTIES enum.  If you want to 
      determine if the layer has any per viewport settings,
      then pass 0xFFFFFFFF.
  Returns:
    True if the layer has per viewport override for the specified
    settings.
  */
  bool HasPerViewportSettings(
    ON_UUID viewport_id,
    unsigned int settings_mask
    ) const;

  /*
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then checks for setting for
      that specific viewport.
      If viewport_id is nil, then checks for any viewport settings.
  Returns:
    True if the layer has per viewport settings.
  */
  bool HasPerViewportSettings(
    const ON_UUID& viewport_id
    ) const;


  /*
  Description:
    Copies all per viewport settings for the source_viewport_id
  Parameters:
    source_viewport_id - [in]
      viewport id to copy all per viewport settings from
    destination_viewport_id - [in]
      viewport od to copy all per viewport settings to
  Returns:
    True if the settings could be copied, False if no per-viewport
    settings exist for the source viewport id
  */
  bool CopyPerViewportSettings( 
    ON_UUID source_viewport_id,
    ON_UUID destination_viewport_id
    );


  /*
  Description:
    Copies specified per viewport settings from a source layer to this
    layer.
  Parameters:
    source_layer - [in]
      layer to copy settings from
    viewport_id - [in]
      viewport id to copy all per viewport settings from.
      If viewport_id is nil, then the per viewport settings
      for all viewports will be copied.
    settings_mask - [in]
      bits indicate which settings to copy
      Use the ON_Layer PER_VIEWPORT_SETTINGS enum to
      set the bits.
  Returns:
    True if the settings were copied, False if no per-viewport
    settings exist for the specified viewport_id.
  */
  bool CopyPerViewportSettings( 
    const ON_Layer& source_layer,
    ON_UUID viewport_id,
    unsigned int settings_mask
    );

  /*
  Description:
    Delete per viewport layer settings.
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the settings for that
      viewport are deleted.  If viewport_id is nil, then all
      per viewport settings are deleted.
  */
  void DeletePerViewportSettings( 
    const ON_UUID& viewport_id 
    ) const;

  /*
  Description:
    Cull unused per viewport layer settings.
  Parameters:
    viewport_id_count - [in]
    viewport_id_list - [in]
      Settings for any viewports NOT in the viewport_id_list[]
      are culled.
  */
  void CullPerViewportSettings( 
    int viewport_id_count, 
    const ON_UUID* viewport_id_list
    );

  /*
  Description:
    The PerViewportSettingsCRC() can be used to determine
    when layers have different per viewport settings.
  */
  ON__UINT32 PerViewportSettingsCRC() const;

  /*
  Description:
    Set the color used by objects on this layer that do
    not have a per object color set
  Parameters:
    layer_color - [in]
      Passing ON_UNSET_COLOR will clear the settings.
    viewport_id - [in]
      If viewport_id is not nil, then the setting applies only
      to the viewport with the specified id.
  */
	void SetColor( ON_Color layer_color ); // layer display color

  /*
  Description:
    Set the color used by objects on this layer that do
    not have a per object color set
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the setting applies only
      to the viewport with the specified id.
    layer_color - [in]
      Passing ON_UNSET_COLOR will clear the settings.
  */
  void SetPerViewportColor( ON_UUID viewport_id, ON_Color layer_color );

  // /* use ON_Layer::SetPerViewportColor */
  //ON_DEPRECATED void SetColor( ON_Color, const ON_UUID& );

  /*
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the setting to use
      for a specific viewport is returned.
  Returns:
    The color used by objects on this layer that do
    not have a per object color set.
  */
	ON_Color Color() const;

  /*
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the setting to use
      for a specific viewport is returned.
  Returns:
    The color used by objects in the specified viewport and
    on this layer that do not have a per object color set.
  */
  ON_Color PerViewportColor( ON_UUID viewport_id ) const;

  /*
  Description:
    Remove any per viewport layer color setting so the
    layer's overall setting will be used for all viewports.
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the setting for this
      viewport will be deleted.  If viewport_id is nil,
      the all per viewport layer color settings will be removed.
  */
  void DeletePerViewportColor( const ON_UUID& viewport_id );

  /*
  Description:
    Set the plotting color used by objects on this layer that do
    not have a per object plotting color set
  Parameters:
    plot_color - [in]
      Passing ON_UNSET_COLOR will clear the settings.
    viewport_id - [in]
      If viewport_id is not nil, then the setting applies only
      to the viewport with the specified id.
  */
	void SetPlotColor( ON_Color plot_color ); // plotting color

  void SetPerViewportPlotColor( ON_UUID viewport_id, ON_Color plot_color );

  /*
  Returns:
    The plotting color used by objects on this layer that do
    not have a per object color set.
  */
	ON_Color PlotColor() const;

  /*
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the setting to use
      for a specific viewport is returned.
  Returns:
    The plotting color used by objects on this layer that do
    not have a per object color set.
  */
	ON_Color PerViewportPlotColor( ON_UUID viewport_id ) const;

  /*
  Description:
    Remove any per viewport plot color setting so the
    layer's overall setting will be used for all viewports.
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the setting for this
      viewport will be deleted.  If viewport_id is nil,
      the all per viewport plot color settings will be removed.
  */
  void DeletePerViewportPlotColor( const ON_UUID& viewport_id );

  /*
  Description:
    Set the index of the linetype used by objects on this layer that do
    not have a per object linetypes
  Parameters:
    linetype_index - [in]
      Passing -1 will clear the setting.
  */
	bool SetLinetypeIndex( int linetype_index );

  /*
  Returns:
    The index of the linetype used by objects on this layer that do
    not have a per object linetype set.
  */
	int LinetypeIndex() const;

  /*
  Returns:
    Returns true if objects on layer are visible.
  Remarks:
    Does not inspect per viewport settings. It is better to use the
    overload that take an ON_3dmView for visibility testing
  See Also:
    ON_Layer::SetVisible
  */
  bool IsVisible() const;

  /*
  Returns:
    Returns true if objects on layer are visible for a given view.
  See Also:
    ON_Layer::SetVisible
  */
  bool IsVisible(const class ON_3dmView* view) const;

  /*
  Description:
    Controls layer visibility
  Parameters:
    bVisible - [in] true to make layer visible, 
                    false to make layer invisible
    viewport_id - [in]
      If viewport_id is not nil, then the setting applies only
      to the viewport with the specified id.
  See Also:
    ON_Layer::IsVisible
  */
  void SetVisible( bool bVisible );

  /*
  Description:
    The persistent visibility setting is used for layers whose
    visibility can be changed by a "parent" object. A common case
    is when a layer is a child layer (ON_Layer.m_parent_id is
    not nil). In this case, when a parent layer is turned off,
    then child layers are also turned off. The persistent
    visibility setting determines what happens when the parent
    is turned on again.
  Returns:
    true: 
      If this layer's visibility is controlled by a parent object
      and the parent is turned on (after being off), then this
      layer will also be turned on.
    false:
      If this layer's visibility is controlled by a parent object
      and the parent layer is turned on (after being off), then
      this layer will continue to be off.
  Remarks:
    When the persistent visibility is not explicitly set, this
    function returns the current value of IsVisible().
  See Also:
    ON_Layer::SetPersistentVisibility
    ON_Layer::UnsetPersistentVisibility
  */
  bool PersistentVisibility() const;

  /*
  Description:
    Set the persistent visibility setting for this layer.
  Parameters:
    bPersistentVisibility - [in]
      persistent visibility setting for this layer.
  Remarks:
    See ON_Layer::PersistentVisibility for a detailed description
    of persistent visibility.
  See Also:
    ON_Layer::PersistentVisibility
    ON_Layer::UnsetPersistentVisibility
  */
  void SetPersistentVisibility( bool bPersistentVisibility );

  /*
  Description:
    Remove any explicit persistent visibility setting from this
    layer. When persistent visibility is not explicitly set,
    the value of ON_Layer::IsVisible() is used.
  Remarks:
    See ON_Layer::PersistentVisibility for a detailed description
    of persistent visibility.
  See Also:
    ON_Layer::PersistentVisibility
    ON_Layer::SetPersistentVisibility
  */
  void UnsetPersistentVisibility();
  

  /*
  Returns:
    Returns true if objects on layer are visible in model viewports.
  See Also:
    ON_Layer::IsVisible()
    ON_Layer::PerViewportIsVisible()
*/
  bool ModelIsVisible() const;

  /*
  Description:
    Controls layer visibility in  in model viewports.
  Parameters:
    bVisible - [in] true to make layer visible,
                    false to make layer invisible
  See Also:
    ON_Layer::SetVisible()
    ON_Layer::SetPerViewportVisible()
  */
  void SetModelVisible(bool bVisible);

  /*
  Returns:
    true:
      If this layer's visibility in model viewports is
      controlled by a parent object and the parent is turned on
      (after being off), then this layer will also be turned on
      in the specified viewport.
    false:
      If this layer's visibility in model viewports is
      controlled by a parent object and the parent layer is
      turned on (after being off), then this layer will continue
      to be off in the specified viewport.
  Remarks:
    See ON_Layer::SetPersistentVisibility
    for a description of persistent visibility.
  See Also:
    ON_Layer::SetModelPersistentVisibility
  */
  bool ModelPersistentVisibility() const;

  /*
  Description:
    This function allows model viewports setting the
    child visibility property.
  Parameters
    bPersistentVisibility - [in]
  Remarks:
    See ON_Layer::SetPersistentVisibility
    for a description of the child visibility property.
  See Also:
    ON_Layer::SetPersistentVisibility
  */
  void SetModelPersistentVisibility(bool bPersistentVisibility);

  void UnsetModelPersistentVisibility();

  /*
  Description:
    Remove any model viewport visibility setting so the
    layer's overall setting will be used for all viewports.
  */
  void DeleteModelVisible();

  /*
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the visibility setting
      for that viewport is returned.  

      If viewport_id is nil, the ON_Layer::IsVisible() is returned.
  Returns:
    Returns true if objects on layer are visible.
  */
	bool PerViewportIsVisible( ON_UUID viewport_id ) const;

  /*
  Description:
    Controls layer visibility in specific viewports.
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the setting applies only
      to the viewport with the specified id.  If viewport_id
      is nil, then the setting applies to all viewports with
      per viewport layer settings.
    bVisible - [in] true to make layer visible, 
                    false to make layer invisible
  See Also:
    ON_Layer::PerViewportIsVisible()
  */
  void SetPerViewportVisible( 
    ON_UUID viewport_id, 
    bool bVisible 
  );

  // /* use ON_Layer::SetPerViewportVisible */
  // ON_DEPRECATED void SetVisible( bool, const ON_UUID& );

  /*
  Parameters:
    viewport_id - [in]
      id of a viewport.  If viewport_id is nil, then 
      ON_Layer::PersistentVisibility() is returned.
  Returns:
    true: 
      If this layer's visibility in the specified viewport is 
      controlled by a parent object and the parent is turned on
      (after being off), then this layer will also be turned on
      in the specified viewport.
    false:
      If this layer's visibility in the specified viewport is
      controlled by a parent object and the parent layer is 
      turned on (after being off), then this layer will continue
      to be off in the specified viewport.
  Remarks:
    See ON_Layer::SetPersistentVisibility
    for a description of persistent visibility.
  See Also:
    ON_Layer::SetPerViewportPersistentVisibility
  */
  bool PerViewportPersistentVisibility( ON_UUID viewport_id ) const;

  /*
  Description:
    This function allows per viewport setting the
    child visibility property.
  Parameters
    viewport_id - [in]
    bPersistentVisibility - [in]
  Remarks:
    See ON_Layer::SetPersistentVisibility
    for a description of the child visibility property.
  See Also:
    ON_Layer::SetPersistentVisibility
  */
  void SetPerViewportPersistentVisibility( ON_UUID viewport_id, bool bPersistentVisibility );

  void UnsetPerViewportPersistentVisibility( ON_UUID viewport_id );    

  /*
  Description:
    Remove any per viewport visibility setting so the
    layer's overall setting will be used for all viewports.
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the setting for this
      viewport will be deleted.  If viewport_id is nil,
      the all per viewport visibility settings will be removed.
  */
  void DeletePerViewportVisible( const ON_UUID& viewport_id );

  /*
  Description:
    Get a list of the viewport ids of viewports that 
    that have per viewport visibility settings that
    override the default layer visibility setting 
    ON_Layer::m_bVisible.
  Parameters:
    viewport_id_list - [out]
      List of viewport id's that have a per viewport visibility
      setting.  If the returned list is empty, then there
      are no per viewport visibility settings.
  Returns:
    Number of ids added to the list.
  */
  void GetPerViewportVisibilityViewportIds(
    ON_SimpleArray<ON_UUID>& viewport_id_list
    ) const;

  /*
  Description:
    Controls layer locked
  Parameters:
    bLocked - [in] True to lock layer
                   False to unlock layer
  See Also:
    ON_Layer::IsLocked
  */
  void SetLocked( bool bLocked );

  /*
  Description:
    The persistent locking setting is used for layers that can
    be locked by a "parent" object. A common case is when a layer
    is a child layer (ON_Layer.m_parent_id is not nil). In this 
    case, when a parent layer is locked, then child layers are 
    also locked. The persistent locking setting determines what
    happens when the parent is unlocked again.
  Returns:
    true: 
      If this layer's locking is controlled by a parent object
      and the parent is unlocked (after being locked), then this
      layer will also be unlocked.
    false:
      If this layer's locking is controlled by a parent object
      and the parent layer is unlocked (after being locked), then
      this layer will continue to be locked.
  Remarks:
    When the persistent locking is not explicitly set, this
    function returns the current value of IsLocked().
  See Also:
    ON_Layer::SetPersistentLocking
    ON_Layer::UnsetPersistentLocking
  */
  bool PersistentLocking() const;

  /*
  Description:
    Set the persistent locking setting for this layer.
  Parameters:
    bPersistentLocking - [in]
      persistent locking for this layer.
  Remarks:
    See ON_Layer::PersistentLocking for a detailed description of
    persistent locking.
  See Also:
    ON_Layer::PersistentLocking
    ON_Layer::UnsetPersistentLocking
  */
  void SetPersistentLocking(bool bPersistentLocking);

  /*
  Description:
    Remove any explicitly persistent locking settings from this
    layer.
  Remarks:
    See ON_Layer::PersistentLocking for a detailed description of
    persistent locking.
  See Also:
    ON_Layer::PersistentLocking
    ON_Layer::SetPersistentLocking
  */
  void UnsetPersistentLocking();

  /*
  Returns:
    Value of (IsVisible() && !IsLocked()).
  */
  bool IsVisibleAndNotLocked() const;

  /*
  Returns:
    Value of (IsVisible() && IsLocked()).
  */
  bool IsVisibleAndLocked() const;

  //////////
  // Index of render material for objects on this layer that have
  // MaterialSource() == ON::material_from_layer.
  // A material index of -1 indicates no material has been assigned
  // and the material created by the default ON_Material constructor
  // should be used.
  bool SetRenderMaterialIndex( int ); // index of layer's rendering material
  int RenderMaterialIndex() const;

  bool SetIgesLevel( int ); // IGES level for this layer
  int IgesLevel() const;

  /*
  Description:
    Get the weight (thickness) of the plotting pen.
  Returns:
    Thickness of the plotting pen in millimeters.
    A thickness of  0.0 indicates the "default" pen weight should be used.
    A thickness of -1.0 indicates the layer should not be printed.
  */
  double PlotWeight() const;

  double PerViewportPlotWeight( ON_UUID viewport_id ) const;

  // /* use ON_Layer::PerViewportPlotWeight */
  // ON_DEPRECATED double PlotWeight( const ON_UUID& ) const;

  /*
  Description:
    Set the weight of the plotting pen.
  Parameters:
    plot_weight_mm - [in] Set the thickness of the plotting pen in millimeters.
       0.0 means use the default pen width which is a Rhino app setting.
      -1.0 means layer does not print (still displays on the screen)
  */
  void SetPlotWeight(double plot_weight_mm);

  /*
  Description:
    Set the weight of the plotting pen.
  Parameters:
    plot_weight_mm - [in] Set the thickness of the plotting pen in millimeters.
       0.0 means use the default pen width which is a Rhino app setting.
      -1.0 means layer does not print (still displays on the screen)
  */
  void SetPerViewportPlotWeight(ON_UUID viewport_id, double plot_weight_mm);

  /*
  Description:
    Remove any per viewport plot weight setting so the
    layer's overall setting will be used for all viewports.
  Parameters:
    viewport_id - [in]
      If viewport_id is not nil, then the setting for this
      viewport will be deleted.  If viewport_id is nil,
      the all per viewport plot weight settings will be removed.
  */
  void DeletePerViewportPlotWeight( const ON_UUID& viewport_id );

  /*
  Description:
    Use UpdateViewportIds() to change viewport ids in situations
    like merging when a viewport id conflict requires the viewport
    ids in a file to be changed.
  Returns:
    Number of viewport ids that were updated.
  */
  int UpdateViewportIds( const ON_UuidPairList& viewport_id_map );

public:

  // Layers are organized in a hierarchical
  // structure (like file folders).
  // If a layer is in a parent layer,
  // then m_parent_layer_id is the id of
  // the parent layer.
  ON_UUID ParentLayerId() const;

  void SetParentLayerId(
    ON_UUID parent_layer_id
    );

  int m_iges_level = -1;        // IGES level number if this layer was made during IGES import
  
  // Rendering material:
  //   If you want something simple and fast, set 
  //   m_material_index to the index of your rendering material 
  //   and ignore m_rendering_attributes.
  //   If you are developing a fancy plug-in renderer, and a user is
  //   assigning one of your fabulous rendering materials to this
  //   layer, then add rendering material information to the 
  //   m_rendering_attributes.m_materials[] array. 
  //
  // Developers:
  //   As soon as m_rendering_attributes.m_materials[] is not empty,
  //   rendering material queries slow down.  Do not populate
  //   m_rendering_attributes.m_materials[] when setting
  //   m_material_index will take care of your needs.
  int m_material_index = -1;
  ON_RenderingAttributes m_rendering_attributes;

  int m_linetype_index = -1;    // index of linetype

  // Layer display attributes.
  //   If m_display_material_id is nil, then m_color is the layer color
  //   and defaults are used for all other display attributes.
  //   If m_display_material_id is not nil, then some complicated
  //   scheme is used to decide what objects on this layer look like.
  //   In all cases, m_color is a good choice if you don't want to
  //   deal with m_display_material_id.  In Rhino, m_display_material_id
  //   is used to identify a registry entry that contains user specific
  //   display preferences.
  ON_Color m_color = ON_Color::Black;
  ON_UUID m_display_material_id = ON_nil_uuid;

  // Layer printing (plotting) attributes.
  ON_Color m_plot_color = ON_Color::UnsetColor;   // printing color
                           // ON_UNSET_COLOR means use layer color
  double m_plot_weight_mm = 0.0; // printing pen thickness in mm
                           //  0.0 means use the default width (a Rhino app setting)
                           // -1.0 means layer does not print (still visible on screen)

  bool m_bExpanded = true; // If true, when the layer table is displayed in
                    // a tree control then the list of child layers is
                    // shown in the control.

#pragma region Section Attributes
  // Sections are the product of intersecting a plane with an object.
  // For surface type geometry (ON_Brep, ON_Extrusion, ON_SubD, ON_Mesh)
  // this intersection can result in curves as well as hatches for the
  // closed curves generated

  /*
  Description:
    Layers can have optional custom section style associated with them.
    This function adds a custom section style for this layer.
  */
  void SetCustomSectionStyle(const ON_SectionStyle& sectionStyle);

  /*
  Description:
    Layers can have optional custom section styles associated with them.
    This function returns the custom section style if one exists.
  Parameters:
    sectionStyle [out] - if not nullptr and a custom section style exists,
      the data in the custom section style is copied to sectionStyle
  */
  const ON_SectionStyle* CustomSectionStyle(ON_SectionStyle* sectionStyle = nullptr) const;

  /*
  Description:
    Remove any custom section style associated with this layer
  */
  void RemoveCustomSectionStyle();

  /*
  Description:
    Returns true if a layer's per-viewport visibility property will be true,
    initially, in newly created detail views.
  */
  bool PerViewportIsVisibleInNewDetails() const;
  void SetPerViewportIsVisibleInNewDetails(bool bVisible);

private:
  // The following information may not be accurate and is subject
  // to change at any time.
  //
  // m_extension_bits & 0x01: 
  //   The value of ( m_extension_bits & 0x01) is used to speed
  //   common per viewport visibility and color queries.
  //     0x00 = there may be per viewport settings on this layer.
  //     0x01 = there are no per viewport settings on this layer.
  //
  // m_extension_bits & 0x06:
  //   The value of ( m_extension_bits & 0x06) is the persistent
  //   visibility setting for this layer.
  //     0x00 = no persistent visibility setting
  //     0x02 = persistent visibility = true
  //     0x04 = persistent visibility = false
  //     0x06 = invalid value - treated as 0x00
  //
  // m_extension_bits & 0x18:
  //   The value of ( m_extension_bits & 0x18) is the persistent
  //   locking setting for this layer.
  //     0x00 = no persistent locking setting
  //     0x08 = persistent locking = true
  //     0x10 = persistent locking = false
  //     0x18 = invalid value - treated as 0x00
  ON__UINT8 m_extension_bits = 0;
  ON__UINT16 m_reserved = 0;

private:
  mutable class ON_LayerPrivate* m_private = nullptr;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Layer*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ObjectArray<ON_Layer>;
#endif

#endif

