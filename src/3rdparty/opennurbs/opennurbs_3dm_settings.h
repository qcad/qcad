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

#if !defined(OPENNURBS_3DM_SETTINGS_INC_)
#define OPENNURBS_3DM_SETTINGS_INC_

///////////////////////////////////////////////////////////////////////
//
// units and tolerances
//

class ON_CLASS ON_3dmUnitsAndTolerances
{
public:
  // The default constructor set units to millimeters and tolerance = 0.001mm
  ON_3dmUnitsAndTolerances() = default;
  ~ON_3dmUnitsAndTolerances() = default;

  ON_3dmUnitsAndTolerances(const ON_3dmUnitsAndTolerances&) = default;
  ON_3dmUnitsAndTolerances& operator=(const ON_3dmUnitsAndTolerances&) = default;

  bool operator==(const ON_3dmUnitsAndTolerances& other) const;
  bool operator!=(const ON_3dmUnitsAndTolerances& other) const;

  bool Read( ON_BinaryArchive& );
  bool Write( ON_BinaryArchive& ) const;

  void Dump( ON_TextLog& ) const;

  bool IsValid() const;

  // Gets and sets the absolute tolerance in units, > 0.0
  double AbsoluteTolerance() const;
  void SetAbsoluteTolerance(double absolute_tolerance);

  // Gets and sets the angle tolerance in radians, > 0.0 and <= ON_PI
  double AngleTolerance() const;
  void SetAngleTolerance(double angle_tolerance);

  // Gets and sets the relative tolerance, fraction > 0.0 and < 1.0
  double RelativeTolerance() const;
  void SetRelativeTolerance(double relative_tolerance);

  // Gets and sets the distance display mode
  ON::OBSOLETE_DistanceDisplayMode DistanceDisplayMode() const;
  void SetDistanceDisplayMode(ON::OBSOLETE_DistanceDisplayMode distance_display_mode);

  // Gets and sets the distance display precision, >= 0 and <= 7
  int DistanceDisplayPrecision() const;
  void SetDistanceDisplayPrecision(int distance_display_precision);

  // Returns true if absolute, angle, and relative tolerances values are valid.
  bool TolerancesAreValid() const;

  /*
  Description:
    If m_absolute_tolerance is not set to a valid value, it is set
    to ON_3dmUnitsAndTolerances::DefaultValue.m_absolute_tolerance.
    If m_angle_tolerance is not set to a valid value, it is set
    to ON_3dmUnitsAndTolerances::DefaultValue.m_angle_tolerance.
    If m_relative_tolerance is not set to a valid value, it is set
    to ON_3dmUnitsAndTolerances::DefaultValue.m_relative_tolerance.
  Returns:
    0: all tolerances were valid
    0 != (rc & 1):
      m_absolute_tolerance was invalid and set to the default value
    0 != (rc & 2):
      m_angle_tolerance was invalid and set to the default value
    0 != (rc & 4):
      m_relative_tolerance was invalid and set to the default value
  */
  unsigned int SetInvalidTolerancesToDefaultValues();

  // Returns scale factor that needs to be applied to change from
  // the argument's unit system to m_unit_system.  
  // When m_unit_system is not ON::LengthUnitSystem::CustomUnits,
  // Scale(us) = ON::UnitScale(us,m_unit_system).  When Scale(us)
  // When m_unit_system is ON::LengthUnitSystem::CustomUnits,
  // Scale(us) = ON::UnitScale(us,ON::LengthUnitSystem::Meters)*m_custom_unit_scale.
  double Scale( ON::LengthUnitSystem ) const;

  // Expert access to member variables
  ON_UnitSystem m_unit_system = ON_UnitSystem::Millimeters;
  double m_absolute_tolerance = 0.001;    // in units > 0.0
  double m_angle_tolerance = ON_PI/180.0; // in radians > 0.0 and <= ON_PI
  double m_relative_tolerance = 0.01;     // fraction > 0.0 and < 1.0
  ON::OBSOLETE_DistanceDisplayMode m_distance_display_mode = ON::OBSOLETE_DistanceDisplayMode::Decimal; // decimal or fractional
  int m_distance_display_precision = 3;   // decimal mode: number of decimal places
                                          // fractional modes: denominator = (1/2)^m_distance_display_precision

public:
  /*
  DefaultValue
    m_unit_system                 ON::LengthUnitSystem::Millimeters
    m_absolute_tolerance          0.001
    m_angle_tolerance             pi/180 = 1 degree
    m_relative_tolerance          0.01 = 1%
    m_distance_display_mode       ON::OBSOLETE_DistanceDisplayMode::Decimal
    m_distance_display_precision  3
  */
  static const ON_3dmUnitsAndTolerances Millimeters;
};

///////////////////////////////////////////////////////////////////////
//
// Model settings
//   render mesh defaults
//   viewports
//   construction planes
//

class ON_CLASS ON_3dmAnnotationSettings
{
public:
  ON_3dmAnnotationSettings() = default;
  ~ON_3dmAnnotationSettings();
  ON_3dmAnnotationSettings(const ON_3dmAnnotationSettings&);
  ON_3dmAnnotationSettings& operator=(const ON_3dmAnnotationSettings&);

  static const ON_3dmAnnotationSettings Default;

  bool Read(ON_BinaryArchive&);
  bool Write(ON_BinaryArchive&) const;

  void Dump(ON_TextLog& text_log) const;

  // these are the running defaults for making dimensions
  // they are also the things written to the 3dm file as dimension settings
  double m_dimscale = 1.0;       // model size / plotted size
  double m_textheight = 1.0;
  double m_dimexe = 1.0;
  double m_dimexo = 1.0;
  double m_arrowlength = 1.0;
  double m_arrowwidth = 1.0;
  double m_centermark = 1.0;

  /*
  Returns:
    Gets the world view text scale.
  */
  double WorldViewTextScale() const;

  /*
  Description:
    Sets the world view text scale.
  */
  void SetWorldViewTextScale(double world_view_text_scale );

  /*
  Returns:
    Gets the world view hatch scale.
  */
  double WorldViewHatchScale() const;

  /*
  Description:
    Sets the world view hatch scale.
  */
  void SetWorldViewHatchScale(double world_view_hatch_scale );


  /*
  Returns:
  Value of m_b_V5_EnableAnnotationScaling;
  */
  bool Is_V5_AnnotationScalingEnabled() const;

  /*
  Parameters:
  bEnable - [in]
  Sets value of m_b_V5_EnableAnnotationScaling.
  */
  void Enable_V5_AnnotationScaling(bool bEnable);

  /*
  Parameters:
  bEnable - [in]
  Sets value of m_bEnableModelSpaceAnnotationScaling.
  */
  void EnableModelSpaceAnnotationScaling(bool bEnable);

  /*
  Returns:
  Value of m_bEnableModelSpaceAnnotationScaling;
  */
  bool IsModelSpaceAnnotationScalingEnabled() const;

  /*
  Parameters:
  bEnable - [in]
  Sets value of m_bEnableLayoutSpaceAnnotationScaling.
  */
  void EnableLayoutSpaceAnnotationScaling(bool bEnable);

  /*
  Returns:
  Value of m_bEnableLayoutSpaceAnnotationScaling;
  */
  bool IsLayoutSpaceAnnotationScalingEnabled() const;

  /*
  Returns:
    Value of m_bEnableHatchScaling;
  */
  bool IsHatchScalingEnabled() const;

  /*
  Parameters:
    bEnable - [in]
      Sets value of m_bEnableHatchScaling.
  */
  void EnableHatchScaling(bool bEnable);

  /*
  Returns:
    If true, then new annotations are added to the layer with the id returned by DimensionLayerId().
    If false, then new annotations are added to the document's current layer.
  */
  bool UseDimensionLayer() const;

  /*
  Description:
    Enables or disables the use of a dimension layer.
  */
  void EnableUseDimensionLayer(bool bEnable);

  /*
  Description:
    Gets the id of the dimension layer.
    Note, if id is ON_nil_uuid or if a layer with the id does not exist,
    the current layer will be used.
  */
  ON_UUID DimensionLayerId() const;

  /*
  Description:
    Sets the dimension layer id. To, clear, use ON_nil_uuid.
  */
  void SetDimensionLayerId(const ON_UUID& dimension_layer_id);

private:
  mutable class ON_3dmAnnotationSettingsPrivate* m_private = nullptr;

private:
  // If m_bEnableAnnotationScaling is false:
  //   * m_world_view_text_scale is ignored.
  //   * text is not scaled.
  //   * ON_DimStyle::DimScale() determines the scale 
  //     applied to all other annotation objects in all 
  //     types of views.
  //   * The value of ON_DetailView::m_page_per_model_ratio
  //     is applied to all objects (annotation and geometry)
  //     in the detail view.
  //
  // If m_bEnableAnnotationScaling is true:
  //   * m_world_view_text_scale is used as described above.
  //   * ON_DimStyle::DimScale() determines the scale 
  //     applied to all non text annotation objects in 
  //     world views. 
  //   * ON_DimStyle::DimScale() is ignored in page and 
  //     detail views. 
  //   * ON_DetailView::m_page_per_model_ratio is ignored
  //     for annotation objects in detail views, other
  //     geometry is scaled.
  //
  // Default is true.
  unsigned char m_b_V5_EnableAnnotationScaling = 1;

  // [Lowell 3-28-2013] New fields for V6
  unsigned char m_bEnableModelSpaceAnnotationScaling = 1;
  unsigned char m_bEnableLayoutSpaceAnnotationScaling = 1;

  unsigned char m_bEnableHatchScaling = 1;

private:
  ON__UINT32 m_reserved1 = 0;
  ON__UINT8 m_reserved2 = 0;
  ON__UINT8 m_reserved3 = 0;
  ON__UINT8 m_reserved4 = 0;

public:
  ON::LengthUnitSystem m_dimunits = ON::LengthUnitSystem::None;  // units used to measure the dimension
  int m_arrowtype = 0;     // 0: filled narrow triangular arrow (= ((ON_Arrowhead::arrow_type enum value as int ) - 2))
  int m_angularunits = 0;  // 0: degrees, 1: radians
  int m_lengthformat = 0;  // 2 = ON_DimStyle::LengthDisplay::FeetAndInches, treat everything else as ON_DimStyle::LengthDisplay::ModelUnits
  int m_angleformat = 0;   // 0: decimal degrees, ... ( ON_DimStyle::angle_format enum as int )

  //ON_INTERNAL_OBSOLETE::V5_TextDisplayMode m_settings_textalign;     // In V2 files -  0: above line, 1: in line, 2: horizontal
  //                              // After V2 files - 0: normal (converts to above_line), 1: horizontal, 2: above_line, 3: in_line 

  int m_resolution = 0;    // depends on m_lengthformat
                       // for decimal, digits past the decimal point

  ON_wString m_facename; // [LF_FACESIZE] // windows font name

private:
  void Internal_CopyFrom(const ON_3dmAnnotationSettings& src);
  void Internal_Destroy();
};

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmConstructionPlaneGridDefaults
//
// Default settings used for construction plane grids
class ON_CLASS ON_3dmConstructionPlaneGridDefaults
{
public:
  ON_3dmConstructionPlaneGridDefaults() = default;
  ~ON_3dmConstructionPlaneGridDefaults() = default;
  ON_3dmConstructionPlaneGridDefaults(const ON_3dmConstructionPlaneGridDefaults&) = default;
  ON_3dmConstructionPlaneGridDefaults& operator=(const ON_3dmConstructionPlaneGridDefaults&) = default;

  static const ON_3dmConstructionPlaneGridDefaults Default;

  bool Write( ON_BinaryArchive& ) const;
  bool Read( ON_BinaryArchive& );

  void Dump( ON_TextLog& text_log ) const;

	double m_grid_spacing = 1.0;   // distance between grid lines
  double m_snap_spacing = 1.0;   // when "grid snap" is enabled, the
                           // distance between snap points.  Typically
                           // this is the same distance as grid spacing.
	int m_grid_line_count = 70;   // number of grid lines in each direction
  int m_grid_thick_frequency = 5; // thick line frequency
                            // 0: none, 
                            // 1: all lines are thick, 
                            // 2: every other is thick, ...

  bool m_bShowGrid = true;
  bool m_bShowGridAxes = true;
  bool m_bShowWorldAxes = true;
};

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmConstructionPlane
//
class ON_CLASS ON_3dmConstructionPlane
{
public:
  ON_3dmConstructionPlane();
  ~ON_3dmConstructionPlane();

  ON_3dmConstructionPlane(const ON_Plane& plane);

  // default copy constructor and operator= work fine
  //ON_3dmConstructionPlane(const ON_3dmConstructionPlane&);
  //ON_3dmConstructionPlane& operator=(const ON_3dmConstructionPlane&);

  void Default();

  bool Write( ON_BinaryArchive& ) const;
  bool Read( ON_BinaryArchive& );

  void Dump( ON_TextLog& text_log ) const;

  ON_Plane    m_plane;

  // construction grid appearance
	double m_grid_spacing;   // distance between grid lines
  double m_snap_spacing;   // when "grid snap" is enabled, the
                           // distance between snap points.  Typically
                           // this is the same distance as grid spacing.
	int m_grid_line_count;   // number of grid lines in each direction
  int m_grid_thick_frequency; // thick line frequency
                            // 0: none, 
                            // 1: all lines are thick, 
                            // 2: every other is thick, ...
  bool m_bDepthBuffer; // false=grid is always drawn behind 3d geometry
                       // true=grid is drawn at its depth as a 3d plane
                       // and grid lines obscure things behind the grid.

  ON_wString  m_name;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_3dmConstructionPlane>;
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmViewPosition
//
class ON_CLASS ON_3dmViewPosition
{
public:
  // view window relative position and state in parent frame
  ON_3dmViewPosition();
  ~ON_3dmViewPosition();
  ON_3dmViewPosition(const ON_3dmViewPosition&);
  ON_3dmViewPosition& operator=(const ON_3dmViewPosition&);

  void Default();

  bool Write( ON_BinaryArchive& ) const;
  bool Read( ON_BinaryArchive& );

  // relative position of view window in main frame
  // if m_floating_viewport>0, this is relative position of the view window
  // on the virtual screen (union of potentially multiple monitors)
  double m_wnd_left;    // 0.0 to 1.0
  double m_wnd_right;
  double m_wnd_top;
  double m_wnd_bottom;

  bool m_bMaximized; // true if view window is maximized

  // m_floating_viewport is used to track floating viewport information.
  //  0 = the view is docked in the main application window.
  // >0 = the view is floating. When floating, this corresponds to the
  //      number of monitors on on the user's computer when the file was saved
  unsigned char m_floating_viewport;
private:
  // reserved for future use
  unsigned char m_reserved_1;
  unsigned char m_reserved_2;
  unsigned char m_reserved_3;
};

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmViewTraceImage
//
class ON_CLASS ON_3dmViewTraceImage
{
public:
  ON_3dmViewTraceImage();
  ~ON_3dmViewTraceImage();
  bool operator==( const ON_3dmViewTraceImage& ) const;
  bool operator!=( const ON_3dmViewTraceImage& ) const;

  void Default();

  bool Write( ON_BinaryArchive& ) const;
  bool Read( ON_BinaryArchive& );

  // view window relative position and state in parent frame
  ON_Plane m_plane;
  double   m_width;
  double   m_height;

  ON_FileReference m_image_file_reference;

  bool m_bGrayScale; // true if image should be black and white
  bool m_bHidden;    // true if image is currently hidden from view
  bool m_bFiltered;  // true if image should be filtered (bilinear) before displayed.
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmViewTraceImage
//
class ON_CLASS ON_3dmWallpaperImage
{
public:
  ON_3dmWallpaperImage();
  ~ON_3dmWallpaperImage();
  bool operator==( const ON_3dmWallpaperImage& ) const;
  bool operator!=( const ON_3dmWallpaperImage& ) const;

  void Default();

  bool Write( ON_BinaryArchive& ) const;
  bool Read( ON_BinaryArchive& );

  ON_FileReference m_image_file_reference;

  bool m_bGrayScale; // true if image should be black and white
  bool m_bHidden;    // true if image is currently hidden from view
};

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmView
//

class ON_CLASS ON_3dmPageSettings
{
public:
  ON_3dmPageSettings();
  ~ON_3dmPageSettings();

  bool IsValid( ON_TextLog* text_log = 0 ) const;

  void Default();

  int m_page_number;

  // Overall size of the page in millimeters
  double m_width_mm;
  double m_height_mm;

  // Page margins in millimeters
  double m_left_margin_mm;
  double m_right_margin_mm;
  double m_top_margin_mm;
  double m_bottom_margin_mm;

  ON_wString m_printer_name;

  bool Write(ON_BinaryArchive& archive) const;
  bool Read(ON_BinaryArchive& archive);
};

class ON_CLASS ON_StandardDisplayModeId
{
public:
  static const ON_UUID Wireframe;        // {1311ADCB-D89E-4051-A3F0-F64441FB8EC6}
  static const ON_UUID Shaded;           // {8BC8DEBE-C83B-4c47-B13C-9DB074510CAC}
  static const ON_UUID Rendered;         // {CAE60BAE-2D51-4299-ABF7-A339FCA86F3B}
  static const ON_UUID Ghosted;          // {FF608B97-81D3-4186-831C-41F7DC140881}
  static const ON_UUID XrayShade;        // {B5C19D5D-0AEC-4ff7-A10E-E052E660263A}
  static const ON_UUID RenderedShadows;  // {A5545314-9D87-428d-95AE-91052EEAD0FA}
  static const ON_UUID Technical;        // {63612C72-778F-4afd-B81B-17426FDFE8A6}
  static const ON_UUID Artistic;         // {B46AB226-05A0-4568-B454-4B1AB721C675}
  static const ON_UUID Pen;              // {F4616FA5-A831-4620-A97E-9B807D5EC376}
  static const ON_UUID Monochrome;       // {E1B5C8A2-ED43-4872-9A01-814E612D5363}
  static const ON_UUID AmbientOcclusion; // {C32B72C3-41BD-4ADC-82A8-B7AEF4456A37}
  static const ON_UUID Raytraced;        // {69E0C7A5-1C6A-46C8-B98B-8779686CD181}

  /*
  Parameters:
    id - [in]
  Returns:
    True if id is one of the standard display modes listed above.
  */
  static bool IsStandardDisplayModeId(
    ON_UUID id
    );

  /*
  Parameters:
    id - [in]
  Returns:
    The legacy V3 display mode enum that is the closest match to
    the display mode id.
  */
  static ON::v3_display_mode ToV3DisplayMode(
    ON_UUID id
    );

  /*
  Parameters:
    dm - [in]
      v3 display mode enum value
  Returns:
    display mode id that corresponds to the enum value.
  */
  static ON_UUID FromV3DisplayMode(
    ON::v3_display_mode dm
    );


private:
  // prohibit instantiation
  ON_StandardDisplayModeId(); // no implementation
  ~ON_StandardDisplayModeId(); // no implementation
};

enum class ON_FocalBlurModes : unsigned int
{
    None,      // No focal blur.
    Automatic, // Autofocus on selected objects.
    Manual,    // Fully manual focus.
};

class ON_CLASS ON_3dmView
{
public:
  ON_3dmView();
  ~ON_3dmView();

  // The C++ default copy constructor and operator= work fine.
  // Do not provide customized versions.
  // NO // ON_3dmView(const ON_3dmView&);
  // NO // ON_3dmView& operator=(const ON_3dmView&);

  void Default();

  bool Write( ON_BinaryArchive& ) const;
  bool Read( ON_BinaryArchive& );

  void Dump( ON_TextLog& text_log ) const;

  bool IsValid( ON_TextLog* text_log = 0 ) const;

  // view projection information
  ON_Viewport m_vp;

  // clipping planes
  // Prior to Dec 14, 2010 m_clipping_planes was not saved with the view. 
  // After Dec 14, 2010 m_clipping_planes is saved.
  ON_SimpleArray<ON_ClippingPlaneInfo> m_clipping_planes;

  // If true, the the camera location, camera direction,
  // and lens angle should not be changed.
  // It is ok to adjust clipping planes.
  bool m_bLockedProjection;

  ON::ViewSectionBehavior SectionBehavior() const;
  void SetSectionBehavior(ON::ViewSectionBehavior behavior);
private:
  ON::ViewSectionBehavior m_section_behavior = ON::ViewSectionBehavior::ClipAndSection;
  unsigned char m_reserved[6];
public:
  ///////////////////////////////////////////////////////////////////////
  //
  // target point
  //

  /*
  Returns:
    Target point.  This point is saved on m_vp.m_target_point.
    The default constructor sets the target point to 
    ON_3dPoint::UnsetPoint. You must explicitly set the target
    point if you want to use it.
  Remarks:
    The target point is stored on m_vp.m_target_point.  The
    value ON_3dmView.m_target is obsolete. This function always
    returns the value of m_vp.m_target_point.

  */
  ON_3dPoint TargetPoint() const;

  /*
  Description:
    Sets the viewport target point. 
  Parameters:
    target_point - [in]
      When in doubt, the point m_vp.FrustumCenterPoint(ON_UNSET_VALUE)
      is a good choice.
  Remarks:
    This point is saved on m_vp.m_target_point.
  */
  bool SetTargetPoint(ON_3dPoint target_point);

  //
  ///////////////////////////////////////////////////////////////////////

  ON_wString  m_name; // name on window
  
  // The value of m_display_mode_id can be one of the "standard" ids
  // from ON_StandardDisplayModeId, nil, or a custom display mode
  // settings on a particular computer.  If you encounter a nil id
  // or any other id that is not one of the "standard" display mode
  // ids, then your application should use a default display mode,
  // typically either wireframe or shaded, that is appropriate for
  // general model viewing.  The function ON::RhinoV3DisplayMode(id)
  // will convert a display mode id into a legacy Rhino V3 display
  // mode enum value.
  ON_UUID m_display_mode_id;

  // position of view in parent window 
  // (relative display device coordinates)
  ON_3dmViewPosition m_position;

  ON::view_type m_view_type; // model, page, nested or uveditor

  // If m_view_type == ON::page_view_type, then the m_page_settings
  // records the page size.  Otherwise, m_page_settings should
  // be ignored.
  ON_3dmPageSettings m_page_settings;

  ///////////////////////////////////////////////////////////////////////
  //
  // Named view information
  //
  // If this view was created from a named view, then m_named_view_id 
  // identifies the named view.
  //
  // The named views are ON_3dmView classes saved in ON_3dmSettings.m_named_views[].
  // A named view's id is the value returned by ON_3dmView.m_vp.ViewportId()
  // A named view's name is the value returned by ON_3dmView.m_name
  //
  // If this view is a named view, then m_named_view_id should be equal to
  // m_vp.m_viewport_id.
  //
  // If this view is not a named view and not created from a named view,
  // then m_named_view_id is equal to ON_nil_uuid.
  ON_UUID m_named_view_id; 

  ///////////////////////////////////////////////////////////////////////
  //
  // Construction plane
  //
  ON_3dmConstructionPlane m_cplane;
  bool m_bShowConstructionGrid;
  bool m_bShowConstructionAxes;
  bool m_bShowConstructionZAxis;

  // world axes icon
  bool m_bShowWorldAxes;

  // tracing image
  ON_3dmViewTraceImage m_trace_image;

  // wallpaper image
  ON_3dmWallpaperImage m_wallpaper_image;

public:

  double FocalBlurDistance(void) const;
  void SetFocalBlurDistance(double d);

  double FocalBlurAperture(void) const;
  void SetFocalBlurAperture(double d);

  double FocalBlurJitter(void) const;
  void SetFocalBlurJitter(double d);

  unsigned int FocalBlurSampleCount(void) const;
  void SetFocalBlurSampleCount(unsigned int count);

  ON_FocalBlurModes FocalBlurMode(void) const;
  void SetFocalBlurMode(ON_FocalBlurModes m);

  ON_2iSize RenderingSize() const;
  void SetRenderingSize(const ON_2iSize& size);

  //Focal blur settings - per view for renderers.
private:
  double m_dFocalBlurDistance = 100.0;
  double m_dFocalBlurAperture = 64.0;
  double m_dFocalBlurJitter = 0.1;
  unsigned int m_uFocalBlurSampleCount = 10;
  ON_FocalBlurModes m_FocalBlurMode = ON_FocalBlurModes::None;
  ON_2iSize m_sizeRendering = ON_2iSize(640, 480);

private:
  ON__INT_PTR reserved = 0;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_3dmView>;
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmRenderSettings
//

class ON_CLASS ON_3dmRenderSettings : public ON_Object
{
  ON_OBJECT_DECLARE(ON_3dmRenderSettings);

public:
  ON_3dmRenderSettings() = default;
  virtual ~ON_3dmRenderSettings();

  ON_3dmRenderSettings(const ON_3dmRenderSettings&);
  ON_3dmRenderSettings& operator=(const ON_3dmRenderSettings&);

  static const ON_3dmRenderSettings Default;

  bool Write( ON_BinaryArchive& ) const override;
  bool Read( ON_BinaryArchive& ) override;
  void Dump( ON_TextLog& text_log ) const override;

private:
  static bool UseV5ReadWrite(const ON_BinaryArchive&);
  bool WriteV5( ON_BinaryArchive& ) const;
  bool ReadV5( ON_BinaryArchive& );

public:
  //New for V6, rendering source (render directly from a NamedView or Snapshot)
  //https://mcneel.myjetbrains.com/youtrack/issue/RH-39593
  enum class RenderingSources : unsigned int
  {
    ActiveViewport,      // Get the rendering view from the currently active viewport (as in all previous versions of Rhino)
    SpecificViewport,    // Get the rendering view from the named viewport (see NamedViewport below)
    NamedView,           // Get the rendering view from a specific named view (see NamedView below)
    SnapShot,            // Before rendering, restore the Snapshot specified in Snapshot below, then render.
  };

  RenderingSources RenderingSource(void) const;
  void SetRenderingSource(RenderingSources);

  ON_wString SpecificViewport(void) const;
  void SetSpecificViewport(const ON_wString&);

  ON_wString NamedView(void) const;
  void SetNamedView(const ON_wString&);

  ON_wString Snapshot(void) const;
  void SetSnapshot(const ON_wString&);

private:
  RenderingSources m_rendering_source = RenderingSources::ActiveViewport;
  ON_wString m_specific_viewport;
  ON_wString m_named_view;
  ON_wString m_snapshot;

public:
  bool ScaleBackgroundToFit() const;
  void SetScaleBackgroundToFit( bool bScaleBackgroundToFit );

public:
  // Access to Ground Plane information.
  class ON_GroundPlane& GroundPlane(void);
  const ON_GroundPlane& GroundPlane(void) const;

  // Access to Dithering information.
  class ON_Dithering& Dithering(void);
  const ON_Dithering& Dithering(void) const;

  // Access to Safe Frame information.
  class ON_SafeFrame& SafeFrame(void);
  const ON_SafeFrame& SafeFrame(void) const;

  // Access to Skylight information.
  class ON_Skylight& Skylight(void);
  const ON_Skylight& Skylight(void) const;

  // Access to Linear Workflow information.
  class ON_LinearWorkflow& LinearWorkflow(void);
  const ON_LinearWorkflow& LinearWorkflow(void) const;

  // Access to Render Channels information.
  class ON_RenderChannels& RenderChannels(void);
  const ON_RenderChannels& RenderChannels(void) const;

  // Access to Sun information.
  class ON_Sun& Sun(void);
  const ON_Sun& Sun(void) const;

  // Access to Post Effect information.
  class ON_PostEffects& PostEffects(void);
  const ON_PostEffects& PostEffects(void) const;

  // Access to information about which environments are used for rendering.

  enum class EnvironmentUsage : unsigned int
  {
    Background,  // Specifies the 360 background environment.
    Reflection,  // Specifies the custom reflective environment. Also used for refraction.
    Skylighting, // Specifies the custom skylighting environment.
  };

  enum class EnvironmentPurpose : unsigned int
  {
    Standard,     // Used to directly get and set the environment instance id.
    ForRendering, // Used to get the environment instance id to be used for actual rendering.
  };

  // Returns whether or not the rendering environment for a particular usage is overriding the background
  // environment. Only really makes sense for usage Reflection and Skylighting, but for convenience,
  // it also works for usage Background by checking if the background style is set to Environment.
  bool RenderEnvironmentOverride(EnvironmentUsage usage) const;

  // Sets whether or not the rendering environment for a particular usage is overriding the background
  // environment. Only works for usage Reflection and Skylighting.
  void SetRenderEnvironmentOverride(EnvironmentUsage usage, bool on);

  // Returns the id of the rendering environment for a particular usage.
  // Param 'purpose' specifies the purpose the environment will be used for:
  // - If purpose is Standard, this directly returns the id of the environment.
  // - If purpose is ForRendering, this returns the id of the environment to be used during rendering.
  //   It includes all the logic for checking if the environment is enabled and available and for
  //   deferring to other environments if the requested usage is not available.
  ON_UUID RenderEnvironmentId(EnvironmentUsage usage, EnvironmentPurpose purpose) const;

  // Sets the id of the rendering environment for a particular usage.
  void SetRenderEnvironmentId(EnvironmentUsage usage, const ON_UUID& id);

  // Invalidate any caches in the render settings.
  void InvalidateCaches(void) const;

private:
  unsigned short m_reserved1 = 0;

public:
  //////////////////////////////////////////////////////////////
  //
  // Force viewport aspect ratio:
  //   If m_bCustomImageSize is true and m_bForceViewportAspectRatio is true
  //   then the image height should be calculated by multiplying the m_image_width
  //   by the viewport aspect ratio.  Note that this might be affected by m_rendering_source
  //   In this case, m_image_height should not be used.
  //
  bool m_bForceViewportAspectRatio = false;

  //////////////////////////////////////////////////////////////
  //
  // Custom image size:
  //   If m_bCustomImageSize is true, then the image pixel size
  //   is m_image_width X m_image_height pixels.
  //   If m_bCustomImageSize is false, then the image pixel size
  //   is the size of the viewport being rendered.
  //
  bool m_bCustomImageSize = false;
  int  m_image_width  = 800;  // image width in pixels
  int  m_image_height = 600;  // image height in pixels

private:
  unsigned int m_reserved3 = 0;

public:
  ////////
  // Number of dots/inch (dots=pixels) to use when printing and 
  // saving bitmaps. The default is 72.0 dots/inch.
  double m_image_dpi = 72.0; 

  //////////
  // unit system to use when converting image pixel size and dpi
  // information into a print size.  Default = inches
  ON::LengthUnitSystem m_image_us = ON::LengthUnitSystem::Inches;

  ON_Color m_ambient_light = ON_Color::Black;

  int m_background_style = 0; // 0 = solid color, 1 = "wallpaper" image, 2 = Gradient, 3 = Environment

  // m_background_color was changed from ON_Color::Gray160 to ON_Color::White for "white studio" look.
  // m_background_color = Top color of gradient...
  ON_Color m_background_color = ON_Color::White;
  ON_Color m_background_bottom_color = ON_Color::Gray160;

  ON_wString m_background_bitmap_filename;
  // If m_background_bitmap_filename is not empty, the file cannot be found,
  // and m_embedded_file_id identifies an embedded image file in the model,
  // then that file will be used as the background bitmap.
  ON_UUID m_embedded_image_file_id = ON_nil_uuid;

  bool m_bUseHiddenLights = false;

  bool m_bDepthCue = false;
  bool m_bFlatShade = false;

  bool m_bRenderBackfaces = true;
  bool m_bRenderPoints = false;
  bool m_bRenderCurves = false;
  bool m_bRenderIsoparams = false;
  bool m_bRenderMeshEdges = false;
  bool m_bRenderAnnotation = false;
  bool m_bScaleBackgroundToFit = false;
  bool m_bTransparentBackground = false;

private:
  unsigned char m_reserved4 = 0;
  unsigned int  m_reserved5 = 0;
public:
  
  int m_antialias_style = 1; // 0 = none, 1 = normal, 2 = medium, 3 = best

  int m_shadowmap_style = 1; // 0 = none, 1 = normal, 2 = best
  int m_shadowmap_width= 1000;
  int m_shadowmap_height = 1000;
  double m_shadowmap_offset = 0.75;

  // Flags that are used to determine which render settings a render
  // plugin uses, and which ones the display pipeline should use.
  // Note: Render plugins set these, and they don't need to persist
  //       in the document...Also, when set, they turn OFF their
  //       corresponding setting in the Display Attributes Manager's
  //       UI pages for "Rendered" mode.
  bool m_bUsesAmbientAttr = true;
  bool m_bUsesBackgroundAttr = true;
  bool m_bUsesBackfaceAttr = false;
  bool m_bUsesPointsAttr = false;
  bool m_bUsesCurvesAttr = true;
  bool m_bUsesIsoparmsAttr = true;
  bool m_bUsesMeshEdgesAttr = false;
  bool m_bUsesAnnotationAttr = true;
  bool m_bUsesHiddenLightsAttr = true;

private:
  unsigned char  m_reserved6 = 0;
  unsigned short m_reserved7 = 0;
  unsigned short m_reserved8 = 0;

private: // For internal use only.
  friend class ONX_ModelPrivate;
  friend class ON_3dmRenderSettingsPrivate;
  mutable class ON_3dmRenderSettingsPrivate* m_private = nullptr;
};

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_EarthAnchorPoint
//

class ON_CLASS ON_EarthAnchorPoint
{
public:
  ON_EarthAnchorPoint() = default;
  ~ON_EarthAnchorPoint() = default;
  ON_EarthAnchorPoint(const ON_EarthAnchorPoint&) = default;
  ON_EarthAnchorPoint& operator=(const ON_EarthAnchorPoint&) = default;

  // Latitude, longitude, and elevation are ON_UNSET_VALUE.
  static const ON_EarthAnchorPoint Unset;

  // Latitude, longitude, and elevation are the Seattle Space Needle. 
  static const ON_EarthAnchorPoint SeattleSpaceNeedle;

  static
  int Compare(
          const ON_EarthAnchorPoint*, 
          const ON_EarthAnchorPoint*
          );

  static
  int CompareEarthLocation(
          const ON_EarthAnchorPoint*, 
          const ON_EarthAnchorPoint*
          );

  static
  int CompareModelDirection(
          const ON_EarthAnchorPoint*, 
          const ON_EarthAnchorPoint*
          );

  static
  int CompareIdentification(
          const ON_EarthAnchorPoint*, 
          const ON_EarthAnchorPoint*
          );

  bool Read( ON_BinaryArchive& );
  bool Write( ON_BinaryArchive& ) const;

  /*
  Returns:
    True if the latitude, longitude, and elevation are set.
  */
  bool EarthLocationIsSet() const;

  /*
  Returns:
    True if model basepoint, north and east are set.
  */
  bool ModelLocationIsSet() const;

  /*
  Parameters:
    elevation_unit_system - [in]
    elevation - [in]      
  */
  void SetEarthLocation(
    ON::EarthCoordinateSystem earth_coordinate_system,
    const class ON_UnitSystem& elevation_unit_system,
    double latitude_degrees,
    double longitude_degrees,
    double elevation
  );

  void SetEarthLocation(
    ON::EarthCoordinateSystem earth_coordinate_system,
    ON::LengthUnitSystem elevation_unit_system,
    double latitude_degrees,
    double longitude_degrees,
    double elevation
  );

  void SetLatitudeAndLongitude(
    double latitude_degrees,
    double longitude_degrees
  );

  /*
  Returns:
    A 3d point with coordinates (latitude in degrees, longitude in degrees, elevation in meters).
  Remarks:
    Some coordinates may be ON_UNSET_VALUE.
  */
  ON_3dPoint EarthLocation() const;

  /*
  Parameters:
    unset_location - [in]
      Location to return if EarthlocationIsSet() is false.
  Returns:
    A 3d point with coordinates (latitude, longitude, elevation).
  */
  ON_3dPoint EarthLocation(
    ON_3dPoint unset_location
  ) const;

  /*
  Returns:
    Earth location latitude in degrees. Can be ON_UNSET_VALUE
  */
  double Latitude() const;

  /*
  Parameters:
    unset_latitude - [in]
      Value to return if the Earth location latitude is not set.
  Returns:
    Earth location latitude in degrees.
  */
  double Latitude(
    double unset_latitude
  ) const;

  void SetLatitude(
    double latitude_degrees
  );

  /*
  Returns:
    Earth location longitude in degrees. Can be ON_UNSET_VALUE
  */
  double Longitude() const;

  /*
  Parameters:
    unset_longitude - [in]
      Value to return if the Earth location latitude is not set.
  Returns:
    Earth location longitude in degrees.
  */
  double Longitude(
    double unset_longitude
  ) const;
  
  void SetLongitude(
    double longitude_degrees
  );

  /*
    System used to define latitude, longitude and elevation.
  */
  ON::EarthCoordinateSystem EarthCoordinateSystem() const;

  /*
    System used to define Earth latiude, longitude, and elevation coordinates.
  */
  void SetEarthCoordinateSystem(
    ON::EarthCoordinateSystem earth_coordinate_system
  );

  double ElevationInMeters() const;


  /*
  Parameters:
    elevation_unit_system - [in]
      length unit system for returned value.
  Returns:
    Earth location elevation in in elevation_unit_system.
    The value is with
    Can be ON_UNSET_VALUE
  */
  double Elevation(
    const class ON_UnitSystem& elevation_unit_system
    ) const;

  /*
  Parameters:
    elevation_unit_system - [in]
      length unit system for returned value.
  Returns:
    Earth location elevation in degrees. Can be ON_UNSET_VALUE
  */
  double Elevation(
    ON::LengthUnitSystem elevation_unit_system
    ) const;

  /*
  Parameters:
    elevation_unit_system - [in]
      length unit system for returned value.
    unset_elevation - [in]
      Value to return if the Earth location elevation is not set.
  */
  double Elevation(
    const class ON_UnitSystem& elevation_unit_system,
    double unset_elevation
  ) const;

  /*
  Parameters:
    elevation_unit_system - [in]
      length unit system for returned value.
    unset_elevation - [in]
      Value to return if the Earth location elevation is not set.
  */
  double Elevation(
    ON::LengthUnitSystem elevation_unit_system,
    double unset_elevation
  ) const;

  /*
  Parameters:
    elevation_unit_system - [in]
    elevation - [in]      
  */
  void SetElevation(
    const ON_UnitSystem& elevation_unit_system,
    double elevation
  );

  void SetElevation(
    ON::LengthUnitSystem elevation_unit_system,
    double elevation
  );

  const ON_3dPoint& ModelPoint() const;
  const ON_3dVector& ModelNorth() const;
  const ON_3dVector& ModelEast() const;

  void SetModelPoint(
    ON_3dPoint model_point
  );

  void SetModelNorth(
    ON_3dVector model_north
  );

  void SetModelEast(
    ON_3dVector model_east
  );

  void SetModelLocation(
    ON_3dPoint model_point,
    ON_3dVector model_north,
    ON_3dVector model_east
    );

  /*
  Description:
    Find the Keyhole Markup Language (KML) orientation angles (in radians) of a rotation
    transformation that maps model (east,north,up) to ((1,0,0),(0,1,0),(0,0,1)).
    KML Earth Z axis = up, KML Earth X axis = east, KML Earth Y axis = north.
    NOTE WELL: In KML, positive rotations are CLOCKWISE looking down
    specified axis vector towards the origin. This is rotation direction
    is opposite the conventional "right hand rule."
  Parameters:
    heading_radians - [out]
      angle (in radians) of rotation around KML Earth Z axis (Earth up).
      NOTE WELL: In KML, positive rotations are CLOCKWISE looking down
      specified axis vector towards the origin. This is rotation direction
      is opposite the conventional "right hand rule."
    tilt_radians - [out]
      angle (in radians) of rotation around KML Earth X axis (Earth east).
      NOTE WELL: In KML, positive rotations are CLOCKWISE looking down
      specified axis vector towards the origin. This is rotation direction
      is opposite the conventional "right hand rule."
    roll_radians - [out]
      angle (in radians) of rotation around KML Earth Y axis (Earth north).
      NOTE WELL: In KML, positive rotations are CLOCKWISE looking down
      specified axis vector towards the origin. This is rotation direction
      is opposite the conventional "right hand rule."
  Returns:
    True if the model location is set (this->ModelLocationIsSet() is true)
    and the KML orientation angles are returned.
    Otherwise false is returned and all of the angle values are ON_DLB_QNAN.
  See Also:
    https://developers.google.com/kml/documentation/kmlreference#orientation
  */
  bool GetKMLOrientationAnglesRadians(
    double& heading_radians, 
    double& tilt_radians, 
    double& roll_radians
  ) const;

  /*
    If the model location is set (this->ModelLocationIsSet() is true), then the
    Keyhole Markup Language orientation heading angle in radians is returned.
    Otherwise ON_DBL_QNAN is returned.
  See Also:
    https://developers.google.com/kml/documentation/kmlreference#orientation
  */
  const double KMLOrientationHeadingAngleRadians() const;

  /*
  Returns:
    If the model location is set (this->ModelLocationIsSet() is true), then the
    Keyhole Markup Language orientation tilt angle in radians is returned.
    Otherwise ON_DBL_QNAN is returned.
  See Also:
    https://developers.google.com/kml/documentation/kmlreference#orientation
  */
  const double KMLOrientationTiltAngleRadians() const;

  /*
  Returns:
    If the model location is set (this->ModelLocationIsSet() is true), then the
    Keyhole Markup Language orientation roll angle in radians is returned.
    Otherwise ON_DBL_QNAN is returned.
  See Also:
    https://developers.google.com/kml/documentation/kmlreference#orientation
  */
  const double KMLOrientationRollAngleRadians() const;

  /*
  Description:
    Find the Keyhole Markup Language (KML) orientation angles (in degrees) of a rotation
    transformation that maps model (east,north,up) to ((1,0,0),(0,1,0),(0,0,1)).
    KML Earth Z axis = up, KML Earth X axis = east, KML Earth Y axis = north.
    NOTE WELL: In KML, positive rotations are CLOCKWISE looking down
    specified axis vector towards the origin. This is rotation direction
    is opposite the conventional "right hand rule."
  Parameters:
    heading_degrees - [out]
      angle (in degrees) of rotation around KML Earth Z axis (Earth up).
      NOTE WELL: In KML, positive rotations are CLOCKWISE looking down
      specified axis vector towards the origin. This is rotation direction
      is opposite the conventional "right hand rule."
    tilt_degrees - [out]
      angle (in degrees) of rotation around KML Earth X axis (Earth east).
      NOTE WELL: In KML, positive rotations are CLOCKWISE looking down
      specified axis vector towards the origin. This is rotation direction
      is opposite the conventional "right hand rule."
    roll_degrees - [out]
      angle (in degrees) of rotation around KML Earth Y axis (Earth north).
      NOTE WELL: In KML, positive rotations are CLOCKWISE looking down
      specified axis vector towards the origin. This is rotation direction
      is opposite the conventional "right hand rule."
  Returns:
    True if the model location is set (this->ModelLocationIsSet() is true)
    and the KML orientation angles are returned.
    Otherwise false is returned and all of the angle values are ON_DLB_QNAN.
  See Also:
    https://developers.google.com/kml/documentation/kmlreference#orientation
  */
  bool GetKMLOrientationAnglesDegrees(
    double& heading_degrees, 
    double& tilt_degrees, 
    double& roll_degrees
  ) const;

  /*
  Returns:
    If the model location is set (this->ModelLocationIsSet() is true), then the
    Keyhole Markup Language orientation heading angle in degrees is returned.
    Otherwise ON_DBL_QNAN is returned.
  See Also:
    https://developers.google.com/kml/documentation/kmlreference#orientation
  */
  const double KMLOrientationHeadingAngleDegrees() const;

  /*
  Returns:
    If the model location is set (this->ModelLocationIsSet() is true), then the
    Keyhole Markup Language orientation tilt angle in degrees is returned.
    Otherwise ON_DBL_QNAN is returned.
  See Also:
    https://developers.google.com/kml/documentation/kmlreference#orientation
  */
  const double KMLOrientationTiltAngleDegrees() const;

  /*
    If the model location is set (this->ModelLocationIsSet() is true), then the
    Keyhole Markup Language orientation roll angle in degrees is returned.
    Otherwise ON_DBL_QNAN is returned.
  See Also:
    https://developers.google.com/kml/documentation/kmlreference#orientation
  */
  const double KMLOrientationRollAngleDegrees() const;

private:
  // Point on the Earth
  //   Latitude (degrees):  +90 = north pole, 0 = equator, -90 = south pole
  //   Longitude (degrees):   0 = prime meridian (Greenwich meridian)
  //   Elevation (meters):    
  double m_earth_latitude = ON_UNSET_VALUE;  // in decimal degrees
  double m_earth_longitude = ON_UNSET_VALUE; // in decimal degrees
  double m_earth_elevation_meters = 0.0;

  ON::EarthCoordinateSystem m_earth_coordinate_system = ON::EarthCoordinateSystem::Unset;

private:
  unsigned char m_reserved1 = 0;
  unsigned char m_reserved2 = 0;
  unsigned char m_reserved3 = 0;
  ON__UINT32 m_reserved4 = 0;

private:
  // Corresponding model point in model coordinates.
  ON_3dPoint  m_model_point = ON_3dPoint::Origin; // in model coordinates

  // Earth directions in model coordinates
  ON_3dVector m_model_north = ON_3dVector::YAxis; // in model coordinates
  ON_3dVector m_model_east = ON_3dVector::XAxis;  // in model coordinates

public:
  // Identification information about this location
  ON_UUID    m_id = ON_nil_uuid;  // unique id for this anchor point
  ON_wString m_name;
  ON_wString m_description; 
  ON_wString m_url;
  ON_wString m_url_tag; // UI link text for m_url

  /*
  Parameters:
    model_compass - [out]
      A plane in model coordinates whose xaxis points East,
      yaxis points North and zaxis points up.  The origin
      is set to m_model_basepoint.
  */
  bool GetModelCompass( 
          ON_Plane& model_compass 
          ) const;

  /*
  Description:
    Get a transformation from model coordinates to earth coordinates.
    This transformation assumes the model is small enough that
    the curvature of the earth can be ignored.  
  Parameters:
    model_unit_system - [in]
    model_to_earth - [out]
      Transformation from model coordinates to earth locations
      (degrees latitude,degrees longitude,elevation in meters)
  Remarks:
    If M is a point in model coordinates and E = model_to_earth*M,
    then 
       E.x = latitude in decimal degrees
       E.y = longitude in decimal degrees
       E.z = elevation in meters above mean sea level

    Because the earth is not flat, there is a small amount of error
    when using a linear transformation to calculate oblate spherical 
    coordinates.  This error is small.  If the distance from P to M
    is d meters, then the approximation error is

       latitude error  <=
       longitude error <=
       elevation error <= 6379000*((1 + (d/6356000)^2)-1) meters

    In particular, if every point in the model is within 1000 meters of
    the m_model_basepoint, then the maximum approximation errors are

       latitude error  <=
       longitude error <=
       elevation error <= 8 centimeters
  */
  bool GetModelToEarthXform(
          const ON_UnitSystem& model_unit_system,
          ON_Xform& model_to_earth
          ) const;

private:
  const ON_Xform Internal_KMLOrientationXform() const;
};



class ON_CLASS ON_3dmIOSettings
{
public:
  ON_3dmIOSettings() = default;
  ~ON_3dmIOSettings() = default;
  ON_3dmIOSettings(const ON_3dmIOSettings&) = default;
  ON_3dmIOSettings& operator=(const ON_3dmIOSettings&) = default;

  static const ON_3dmIOSettings Default;

  bool Read(ON_BinaryArchive&);
  bool Write(ON_BinaryArchive&) const;

  // bitmaps associated with rendering materials
  bool m_bSaveTextureBitmapsInFile = false;

  // As of 7 February 2012, the m_idef_link_update setting
  // controls if, when and how linked and linked_and_embedded
  // instance definitions are updated when the source archive
  // that was used to create the idef has changed.
  int m_idef_link_update = 1;  
      // 1 = prompt - ask the user if the idef should be updated.
      // 2 = always update - no prompting
      // 3 = never update - no prompting
      // Any value not equal to 1,2 or 3 shall be treated as 1.
};

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmSettings
//

class ON_CLASS ON_3dmSettings
{
public:
  ON_3dmSettings() = default;
  ~ON_3dmSettings() = default;

  ON_3dmSettings(const ON_3dmSettings&) = default;
  ON_3dmSettings& operator=(const ON_3dmSettings&) = default;

  static const ON_3dmSettings Default;

  bool Read(ON_BinaryArchive&);
  bool Write(ON_BinaryArchive&) const;

  void Dump( ON_TextLog& ) const;

  // model URL (can be empty)
  ON_wString m_model_URL = ON_wString::EmptyString;

  // Model basepoint is used when the file is read as
  // an instance definition and is the point that is
  // mapped to the origin in the instance definition.
  ON_3dPoint m_model_basepoint = ON_3dPoint::Origin;

  // If set, this is the model's location on the earth.
  // This information is used when the model is used
  // with GIS information.
  ON_EarthAnchorPoint m_earth_anchor_point = ON_EarthAnchorPoint::Unset;

  // Model space tolerances and unit system
  ON_3dmUnitsAndTolerances m_ModelUnitsAndTolerances = ON_3dmUnitsAndTolerances::Millimeters;

  // Page space (printing/paper) tolerances and unit system
  ON_3dmUnitsAndTolerances m_PageUnitsAndTolerances = ON_3dmUnitsAndTolerances::Millimeters;

  // settings used for automatically created rendering meshes
  ON_MeshParameters m_RenderMeshSettings = ON_MeshParameters::DefaultMesh;

  // saved custom settings
  ON_MeshParameters m_CustomRenderMeshSettings = ON_MeshParameters::DefaultMesh;

  /*
  Returns:
    ON_MeshParameters::render_mesh_fast
      m_RenderMeshSettings and ON_MeshParameters::FastRenderMesh have
      the same mesh geometry parameter settings.
    ON_MeshParameters::render_mesh_quality
      m_RenderMeshSettings and ON_MeshParameters::QualityRenderMesh have
      the same mesh geometry parameter settings.
    ON_MeshParameters::render_mesh_custom
      m_RenderMeshSettings and m_CustomRenderMeshSettings have
      the same mesh geometry parameter settings.
    no_match_found_result
      otherwise
  */
  ON_MeshParameters::MESH_STYLE RenderMeshStyle(
    ON_MeshParameters::MESH_STYLE no_match_found_result
    ) const;

  // settings used for automatically created analysis meshes
  ON_MeshParameters m_AnalysisMeshSettings = ON_MeshParameters::DefaultAnalysisMesh;

  // settings used when annotation objects are created
  ON_3dmAnnotationSettings m_AnnotationSettings;

  ON_ClassArray<ON_3dmConstructionPlane> m_named_cplanes;
  ON_ClassArray<ON_3dmView>              m_named_views;
  ON_ClassArray<ON_3dmView>              m_views; // current viewports
  ON_UUID m_active_view_id = ON_nil_uuid; // id of "active" viewport              

  // These fields determine what layer, material, color, line style, and
  // wire density are used for new objects.

public:
  void SetCurrentLayerId(
    ON_UUID layer_id
    );
  void SetV5CurrentLayerIndex(
    int V5_current_layer_index
    );
  int CurrentLayerIndex() const;
  ON_UUID CurrentLayerId() const;
private:
  // The index is for reading V5 and earlier files.
  int m_V5_current_layer_index = ON_UNSET_INT_INDEX;
  ON_UUID m_current_layer_id = ON_nil_uuid;

public:
  void SetCurrentMaterialId(
    ON_UUID material_id
    );
  int CurrentMaterialIndex() const;
  ON_UUID CurrentMaterialId() const;
private:
  // The index is for reading V5 and earlier files.
  int m_V5_current_render_material_index = ON_UNSET_INT_INDEX;
  ON_UUID m_current_render_material_id = ON_nil_uuid;

public:
  ON::object_material_source m_current_material_source = ON::material_from_layer;
  
  ON_Color m_current_color = ON_Color::Black;
  ON::object_color_source m_current_color_source = ON::color_from_layer;

  ON_Color m_current_plot_color = ON_Color::UnsetColor;
  ON::plot_color_source m_current_plot_color_source = ON::plot_color_from_layer;

public:
  void SetCurrentLinePatternId(
    ON_UUID line_pattern_id
    );
  int CurrentLinePatternIndex() const;
  ON_UUID CurrentLinePatternId() const;
private:
  // The index is for reading V5 and earlier files.
  int m_V5_current_line_pattern_index = ON_UNSET_INT_INDEX;
  ON_UUID m_current_line_pattern_id = ON_nil_uuid;

public:
  ON::object_linetype_source m_current_linetype_source = ON::linetype_from_layer;

public:
  void SetCurrentTextStyleId(
    ON_UUID text_style_id
    );
  int CurrentTextStyleIndex() const;
  ON_UUID CurrentTextStyleId() const;
private:
  // The index is for reading V5 and earlier files.
  int m_V5_current_text_style_index = ON_UNSET_INT_INDEX;
  ON_UUID m_current_text_style_id = ON_nil_uuid;

public:
  void SetCurrentDimensionStyleId(
    ON_UUID dimension_style_id
    );
  int CurrentDimensionStyleIndex() const;
  ON_UUID CurrentDimensionStyleId() const;
private:
  // The index is for reading V5 and earlier files.
  int m_V5_current_dimension_style_index = ON_UNSET_INT_INDEX;
  ON_UUID m_current_dimension_style_id = ON_nil_uuid;

public:
  void SetCurrentHatchPatternId(
    ON_UUID hatch_pattern_id
    );
  ON_UUID CurrentHatchPatternId() const;
private:
  ON_UUID m_current_hatch_pattern_id = ON_nil_uuid;
 
public:
  // Surface wireframe density
  //
  //   @untitled table
  //   0       boundary + "knot" wires 
  //   1       boundary + "knot" wires + 1 interior wire if no interior "knots"
  //   N>=2    boundary + "knot" wires + (N-1) interior wires
  int m_current_wire_density = 1;

  ON_3dmRenderSettings m_RenderSettings = ON_3dmRenderSettings::Default;

  // default settings for construction plane grids
  ON_3dmConstructionPlaneGridDefaults m_GridDefaults = ON_3dmConstructionPlaneGridDefaults::Default;

  // World scale factor to apply to non-solid linetypes
  // for model display.  For plotting, the linetype settings
  // are used without scaling.
  double m_linetype_display_scale = 1.0;

  // Plugins that were loaded when the file was saved.
  ON_ClassArray<ON_PlugInRef> m_plugin_list;

  ON_3dmIOSettings m_IO_settings = ON_3dmIOSettings::Default;
private:
  bool Read_v1(ON_BinaryArchive&);
  bool Read_v2(ON_BinaryArchive&);
  bool Write_v1(ON_BinaryArchive&) const;
  bool Write_v2(ON_BinaryArchive&) const;
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmAnimationProperties
//

class ON_CLASS ON_3dmAnimationProperties
{
public:
  ON_3dmAnimationProperties() = default;
  ~ON_3dmAnimationProperties() = default;
  ON_3dmAnimationProperties(const ON_3dmAnimationProperties&) = default;
  ON_3dmAnimationProperties& operator=(const ON_3dmAnimationProperties&) = default;

  static const ON_3dmAnimationProperties Default;

  bool Read(ON_BinaryArchive&);
  bool Write(ON_BinaryArchive&) const;

public:
  enum class CaptureTypes : int
  {
    path = 0,
    turntable,
    flythrough,
    day_sun_study,
    seasonal_sun_study,
    none
  };

  CaptureTypes CaptureType(void) const;
  void SetCaptureType(CaptureTypes t);

  ON_wString FileExtension(void) const;
  void SetFileExtension(const ON_wString& s);

  ON_wString CaptureMethod(void) const;
  void SetCaptureMethod(const ON_wString& s);

  ON_wString ViewportName(void) const;
  void SetViewportName(const ON_wString& s);

  ON_wString HtmlFilename(void) const;
  void SetHtmlFilename(const ON_wString& s);

  ON_UUID DisplayMode(void) const;
  void SetDisplayMode(const ON_UUID& id);

  ON_3dPointArray& CameraPoints(void);
  const ON_3dPointArray& CameraPoints(void) const;

  ON_3dPointArray& TargetPoints(void);
  const ON_3dPointArray& TargetPoints(void) const;

  int FrameCount(void) const;
  void SetFrameCount(int i);

  int CurrentFrame(void) const;
  void SetCurrentFrame(int i);

  ON_UUID CameraPathId(void) const;
  void SetCameraPathId(const ON_UUID& id);

  ON_UUID TargetPathId(void) const;
  void SetTargetPathId(const ON_UUID& id);

  double Latitude(void) const;
  void SetLatitude(double d);

  double Longitude(void) const;
  void SetLongitude(double d);

  double NorthAngle(void) const;
  void SetNorthAngle(double d);

  int StartDay(void) const;
  void SetStartDay(int i);

  int StartMonth(void) const;
  void SetStartMonth(int i);

  int StartYear(void) const;
  void SetStartYear(int i);

  int EndDay(void) const;
  void SetEndDay(int i);

  int EndMonth(void) const;
  void SetEndMonth(int i);

  int EndYear(void) const;
  void SetEndYear(int i);

  int StartHour(void) const;
  void SetStartHour(int i);

  int StartMinutes(void) const;
  void SetStartMinutes(int i);

  int StartSeconds(void) const;
  void SetStartSeconds(int i);

  int EndHour(void) const;
  void SetEndHour(int i);

  int EndMinutes(void) const;
  void SetEndMinutes(int i);

  int EndSeconds(void) const;
  void SetEndSeconds(int i);

  int DaysBetweenFrames(void) const;
  void SetDaysBetweenFrames(int i);

  int MinutesBetweenFrames(void) const;
  void SetMinutesBetweenFrames(int i);

  int LightIndex(void) const;
  void SetLightIndex(int i);

  ON_wString FolderName(void) const;
  void SetFolderName(const ON_wString& s);

  ON_ClassArray<ON_wString>& Images(void);
  const ON_ClassArray<ON_wString>& Images(void) const;

  ON_ClassArray<ON_wString>& Dates(void);
  const ON_ClassArray<ON_wString>& Dates(void) const;

  bool RenderFull(void) const;
  void SetRenderFull(const bool b);

  bool RenderPreview(void) const;
  void SetRenderPreview(const bool b);

private:
  CaptureTypes m_CaptureTypes  = CaptureTypes::none;
  ON_wString m_sFileExtension = L"jpg";
  ON_wString m_sCaptureMethod;
  ON_wString m_sHtmlFilename;
  ON_wString m_sViewport;
  ON_UUID m_idDisplayMode = ON_nil_uuid;
  ON_3dPointArray m_aCameraPoints;
  ON_3dPointArray m_aTargetPoints;
  int m_iFrameCount = 100;
  int m_iCurrentFrame = 1;
  ON_UUID m_idCameraPath = ON_nil_uuid;
  ON_UUID m_idTargetPath = ON_nil_uuid;
  double m_dLatitude = 51.2838;
  double m_dLongitude = 0.0;
  double m_dNorthAngle = 0.0;
  int m_iStartDay = 1;
  int m_iStartMonth = 6;
  int m_iStartYear = 2010;
  int m_iEndDay = 1;
  int m_iEndMonth = 6;
  int m_iEndYear = 2012;
  int m_iStartHour = 6;
  int m_iStartMinutes = 0;
  int m_iStartSeconds = 0;
  int m_iEndHour = 18;
  int m_iEndMinutes = 0;
  int m_iEndSeconds = 59;
  int m_iDaysBetweenFrames = 30;
  int m_iMinutesBetweenFrames = 30;
  int m_iLightIndex = -1;
  ON_wString m_sFolderName;
  ON_ClassArray<ON_wString> m_aImages;
  ON_ClassArray<ON_wString> m_aDates;
  bool m_bRenderFull = false;
  bool m_bRenderPreview = false;

private:
  unsigned char m_reserved1 = 0;
  unsigned char m_reserved2 = 0;
  ON__UINT32 m_reserved4 = 0;
  ON__INT_PTR reserved = 0;
};

#endif
