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

#if !defined(OPENNURBS_DIMENSION_INC_)
#define OPENNURBS_DIMENSION_INC_

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template ON_ClassArray< class ON_DimStyle >;
#endif

class ON_CLASS ON_Dimension : public ON_Annotation
{
  ON_OBJECT_DECLARE(ON_Dimension);

public:
#pragma region RH_C_SHARED_ENUM [ON_Dimension::ForceArrow] [Rhino.Geometry.Dimension.ForceArrow] [nested:int]
  /// <summary>
  /// OBSOLETE enum do not use.
  /// </summary>
  enum class ForceArrow : unsigned int
  {
    /// <summary> </summary>
    Auto = 0,
    /// <summary> </summary>
    Inside = 1,
    /// <summary> </summary>
    Outside = 2,
  };
#pragma endregion

  static ON_Dimension::ForceArrow ForceArrowFromUnsigned(
    unsigned int force_arrow_as_unsigned);

#pragma region RH_C_SHARED_ENUM [ON_Dimension::ForceText] [Rhino.Geometry.Dimension.ForceText] [nested:int]
  /// <summary>
  /// OBSOLETE enum do not use.
  /// </summary>
  enum class ForceText : unsigned int
  {
    /// <summary> </summary>
    Auto = 0,
    /// <summary> </summary>
    Inside = 1,
    /// <summary> </summary>
    Right = 2,
    /// <summary> </summary>
    Left = 3,
    /// <summary> </summary>
    HintRight = 4,
    /// <summary> </summary>
    HintLeft = 5,
  };
#pragma endregion

  static ON_Dimension::ForceText ForceTextFromUnsigned(
    unsigned int force_text_as_unsigned);


protected:
  ON_Dimension( ON::AnnotationType annotation_type );
  ~ON_Dimension();
  ON_Dimension(const ON_Dimension& src);
  ON_Dimension& operator=(const ON_Dimension& src);

private:
  ON_Dimension() = delete;
  void Internal_Destroy();
  void Internal_CopyFrom(const ON_Dimension& src);

public:
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  virtual ON_2dPoint DefaultTextPoint() const;
  virtual bool UseDefaultTextPoint() const;
  virtual void SetUseDefaultTextPoint(bool usedefault);

  // Text center-midpoint in dimension plane
  ON_2dPoint TextPoint() const;
  void Set2dTextPoint(const ON_2dPoint& textpoint);

  const wchar_t* UserText() const;
  void SetUserText(const wchar_t* text);
  const wchar_t* PlainUserText() const;

  // Computes measurement value as a number
  virtual double Measurement() const = 0;

  // Add to natural rotation
  ON_DEPRECATED_MSG("ON_Dimension::TextRotation() is a mistake. Use ON_Annotation::TextRotationRadians().")
  double TextRotation() const;

  ON_DEPRECATED_MSG("ON_Dimension::SetTextRotation() is a mistake. Use ON_Annotation::SetTextRotationRadians().")
  void SetTextRotation(double rotation_radians);

  bool ArrowIsFlipped(int i) const;
  void FlipArrow(int i, bool flip) const;

  // If the dimension is a paper space object and the geometry being dimensioned is in 
  // model space, in a detail viewport, DetailMeasured() will have the UUID of the detail
  // that the dimension references.  Otherwise DetailMeasured() will be ON_nil_uuid.
  ON_UUID DetailMeasured() const;
  void SetDetailMeasured(ON_UUID uuid);

  // If DetailMeasured() returns ON_nil_uuid, DistanceScale() has no meaning
  // If the dimension is in page space and measures model space geometry,
  // DistanceScale() is the conversion from the model space distance being measured
  // to the paper space distance spanned by the dimension geometry.
  // When the zoom factor of the detail view changes, the distance scale will change
  double DistanceScale() const;
  void SetDistanceScale(double distance_scale) const;

  //virtual bool  GetBBox(
  //  const ON_Viewport* vp,
  //  double dimscale,
  //  const ON_DimStyle* dimstyle,
  //  double* boxmin,
  //  double* boxmax,
  //  bool bGrow = 0) const = 0;

  virtual bool GetTextRect(ON_3dPoint text_rect[4]) const;

  // Remakes dimension text geometry object and sets it on the dimension
  virtual bool UpdateDimensionText(
    ON::LengthUnitSystem units_in,
    const ON_DimStyle* dimstyle
  ) const;

  // Makes text geometry for a dimension
  ON_TextContent*  RebuildDimensionText(
    ON::LengthUnitSystem units_in,
    const ON_DimStyle* dimstyle,
    bool expandanglebrackets  // replace <> with the formatted distance
  ) const;

  virtual bool GetDistanceDisplayText(
    ON::LengthUnitSystem units_in,
    const ON_DimStyle* dimstyle,
    ON_wString& displaytext) const;
  
  static bool GetCentermarkDisplay(
    const ON_Plane& plane,
    const ON_2dPoint center,
    double marksize,
    double radius,
    ON_DimStyle::centermark_style style,
    ON_Line lines[6],
    bool isline[6],
    int maxlines
    );

  static bool GetCentermarkSnapPoints(
    const ON_Plane& plane,
    const ON_2dPoint center,
    double marksize,
    double radius,
    ON_DimStyle::centermark_style style,
    ON_3dPoint points[13],
    bool ispoint[13]);

  // Obsolete
  ON_DEPRECATED_MSG("ON_Dimension::ArrowFit(const ON_DimStyle* parent_style)")
  ON_Dimension::ForceArrow ForceArrowPosition() const;

  ON_DEPRECATED_MSG("ON_Dimension::SetArrowFit(const ON_DimStyle* parent_style,ON_DimStyle::arrow_fit arrowfit)")
  void SetForceArrowPosition(ForceArrow force);

  ON_DEPRECATED_MSG("ON_Dimension::TextFit(const ON_DimStyle* parent_style)")
  ON_Dimension::ForceText ForceTextPosition() const;

  ON_DEPRECATED_MSG("ON_Dimension::SetTextFit(const ON_DimStyle* parent_style,ON_DimStyle::text_fit textfit)")
  void SetForceTextPosition(ForceText force);

  void SetForceDimLine(
    const ON_DimStyle* parent_style,
    bool forcedimline
  );

  bool ForceDimLine(
    const ON_DimStyle* parent_style) const;

  void SetTextFit(
    const ON_DimStyle* parent_style,
    ON_DimStyle::text_fit textfit);

  ON_DimStyle::text_fit TextFit(
    const ON_DimStyle* parent_style) const;

  void SetArrowFit(
    const ON_DimStyle* parent_style,
    ON_DimStyle::arrow_fit arrowfit);

  ON_DimStyle::arrow_fit ArrowFit(
    const ON_DimStyle* parent_style) const;



protected:
  ON_wString            m_user_text = L"<>";            // If user overridden, or "<>" to use default
  double                m_reserved = 0.0;
  mutable ON_wString    m_plain_user_text;

  bool                  m_use_default_text_point = true;
  ON_2dPoint            m_user_text_point = ON_2dPoint::UnsetPoint;   // Text point if default isn't used

  mutable bool          m_flip_arrow_1 = false;
  mutable bool          m_flip_arrow_2 = false;
  mutable bool          m_text_outside = false;
  unsigned int          m_reserved98 = 0;
  unsigned int          m_reserved99 = 0;


  // UUID of detail if dimension is in page space measuring model space geometry
  ON_UUID               m_detail_measured = ON_nil_uuid;
  // Conversion from model space size to paper space size if dimension is in page space measuring model space geometry
  mutable double        m_distance_scale = 1.0;

  bool Internal_WriteDimension(
    ON_BinaryArchive&  // serialize definition to binary archive
    ) const;

  bool Internal_ReadDimension(
    ON_BinaryArchive&  // restore definition from binary archive
    );
};

class ON_CLASS ON_DimLinear : public ON_Dimension
{
  ON_OBJECT_DECLARE(ON_DimLinear);

public:
  ON_DimLinear();
  ~ON_DimLinear() = default;
  ON_DimLinear(const ON_DimLinear& src) = default;
  ON_DimLinear& operator=(const ON_DimLinear& src) = default;

  static const ON_DimLinear Empty;

  /*
  Description:
    Create a V6 linear dimension from a V5 linear dimension
    The function is used when reading V5 files.
  Parameters:
    V5_linear_dimension -[in]
    annotation_context - [in]
      Dimstyle and other information referenced by V5_linear_dimension or nullptr if not available.
    destination - [in]
      If destination is not nullptr, then the V6 linear dimension is constructed
      in destination. If destination is nullptr, then the new V6 linear dimension
      is allocated with a call to new ON_DimLinear().
  */
  static ON_DimLinear* CreateFromV5DimLinear(
    const class ON_OBSOLETE_V5_DimLinear& V5_linear_dimension,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_DimLinear* destination
  );


  /*
  Parameters:
    annotation_type - [in]
      annotation type to test
  Returns:
    True if input parameter is one of the valid linear dimension types
    ON::AnnotationType::Aligned or ON::AnnotationType::Rotated.
  */
  static bool IsValidLinearDimensionType(
    ON::AnnotationType annotation_type
  );

  /*
  Parameters:
    linear_dimension_type - [in]
      ON::AnnotationType::Aligned or ON::AnnotationType::Rotated.
  Returns:
    True if input parameter is valid and type is set.
  */
  bool SetLinearDimensionType(
    ON::AnnotationType linear_dimension_type
  );

  bool Write(
    ON_BinaryArchive&  // serialize definition to binary archive
    ) const override;

  bool Read(
    ON_BinaryArchive&  // restore definition from binary archive
    ) override;

  bool Transform(const ON_Xform& xform) override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  bool GetAnnotationBoundingBox(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    double* boxmin,
    double* boxmax,
    bool bGrow = false
  ) const override; // ON_Annotation override

  // Gets transform for dimension text from ON_xy_plane to 3d display location
  bool GetTextXform(
    const ON_Xform* model_xform,
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    ON_Xform& text_xform_out
  ) const;

  bool GetTextXform(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    ON_Xform& text_xform_out
  ) const override;

  bool Create(
    ON::AnnotationType dim_type,
    const ON_UUID style_id,
    const ON_Plane& plane,
    const ON_3dVector& ref_horizontal,
    const ON_3dPoint& def_pt1,
    const ON_3dPoint& def_pt2,
    const ON_3dPoint& dimline_pt,
    double rotation_in_plane = 0.0
    );

  /*
  Description:
    Create an aligned linear dimension. The dimension line is
    parallel to the segment connecting the extension points.
  Parameters:
    extension_point0 - [in]
    extension_point1 - [in]
      locations of one of the points being dimensioned.
      The dimension line will be parallel to the segment
      connecting these points.
    dimension_line_point - [in]
      a point on the linear dimension line.
    plane_normal - [in]
      A vector perpindcular to the line between the extension points
      that defines the orientation of the dimension's plane.
    dim_style_id - [in]
    destination - [in]
      If nullptr, the returned ON_DimLinear is allocated by operator new.
      Otherwise, the reuturned ON_DimLinear is created in destination.
  */
  static ON_DimLinear* CreateAligned(
    ON_3dPoint extension_point0,
    ON_3dPoint extension_point1,
    ON_3dPoint dimension_line_point,
    ON_3dVector plane_normal,
    ON_UUID style_id,
    ON_DimLinear* destination
  );

  /*
  Description:
    Create a rotated linear dimension to the document.
    The dimension line is explicitly specified.
  Parameters:
    extension_point0 - [in]
    extension_point1 - [in]
      locations of one of the points being dimensioned.
      The dimension line will be parallel to the segment
      connecting these points.
    dimension_line - [in]
      the dimension line. This is treated as an infinite
      line and the points are automatically calculated.
    plane_normal - [in]
      A vector perpindcular to the line between the extension points
      that defines the orientation of the dimension's plane. 
      The dimension line is projected to this plane.
    dim_style_id - [in]
    destination - [in]
      If nullptr, the returned ON_DimLinear is allocated by operator new.
      Otherwise, the reuturned ON_DimLinear is created in destination.
  */
  static ON_DimLinear* CreateRotated(
    ON_3dPoint extension_point0,
    ON_3dPoint extension_point1,
    ON_Line dimension_line,
    ON_3dVector plane_normal,
    ON_UUID style_id,
    ON_DimLinear* destination
  );

  // virtual
  double Measurement() const override;
  ON_2dPoint DefaultTextPoint() const override;

  // DefPoint1 is m_plane.origin
  // Meaasurement is between DefPoint1 and DefPoint2
  // parallel to the m_plane x-axis.
  ON_2dPoint DefPoint1() const;
  ON_2dPoint DefPoint2() const;
  ON_2dPoint DimlinePoint() const;

  void Set2dDefPoint1(ON_2dPoint pt);
  void Set2dDefPoint2(ON_2dPoint pt);
  void Set2dDimlinePoint(ON_2dPoint pt);

  void Set3dDefPoint1(ON_3dPoint pt);
  void Set3dDefPoint2(ON_3dPoint pt);
  void Set3dDimlinePoint(ON_3dPoint pt);

  ON_2dPoint ArrowPoint1() const;    // Calculated
  ON_2dPoint ArrowPoint2() const;    // Calculated

  bool Get3dPoints(
    ON_3dPoint* defpt1,
    ON_3dPoint* defpt2,
    ON_3dPoint* arrowpt1,
    ON_3dPoint* arrowpt2,
    ON_3dPoint* dimline,
    ON_3dPoint* textpt) const;

  bool GetDisplayLines(
    const ON_Viewport* vp,
    const ON_DimStyle* style,
    double dimscale,
    ON_3dPoint text_rect[4],
    ON_Line lines[4],
    bool isline[4],
    int maxlines) const;

  void GetArrowXform(
    int which_end,
    double scale,
    bool arrowflipped,
    bool from_the_back,
    ON_Xform& arrow_xform_out) const;

public:
	bool GetTextXform(
		const ON_Xform* model_xform,
		const ON_3dVector view_x,
		const ON_3dVector view_y,
		const ON_3dVector view_z,
		ON::view_projection projection,
		bool bDrawForward,
		const ON_DimStyle* dimstyle,
		double dimscale,
		ON_Xform& text_xform_out
	) const;


protected:
  ON_2dPoint m_def_pt_2 = ON_2dPoint::UnsetPoint;
  ON_2dPoint m_dimline_pt = ON_2dPoint::UnsetPoint;
};

//---------------------------------------------------------------------

class ON_CLASS ON_DimAngular : public ON_Dimension
{
  ON_OBJECT_DECLARE(ON_DimAngular);

public:
  ON_DimAngular();
  ~ON_DimAngular() = default;
  ON_DimAngular(const ON_DimAngular& src) = default;
  ON_DimAngular& operator=(const ON_DimAngular& src) = default;

  static const ON_DimAngular Empty;

  /*
  Parameters:
  annotation_type - [in]
  annotation type to test
  Returns:
  True if input parameter is one of the valid linear dimension types
  ON::AnnotationType::Angular or ON::AnnotationType::Angular3pt.
  */
  static bool IsValidAngularDimensionType(
    ON::AnnotationType annotation_type
  );

  /*
  Parameters:
  angular_dimension_type - [in]
  ON::AnnotationType::Angular or ON::AnnotationType::Angular3pt.
  Returns:
  True if input parameter is valid and type is set.
  */
  bool SetAngularDimensionType(
    ON::AnnotationType angular_dimension_type
  );

  static ON_DimAngular* CreateFromV5DimAngular(
    const class ON_OBSOLETE_V5_DimAngular& V5_dim_angle,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_DimAngular* destination
  );

  bool Write(
    ON_BinaryArchive&  // serialize definition to binary archive
    ) const override;

  bool Read(
    ON_BinaryArchive&  // restore definition from binary archive
    ) override;

  bool Transform(const ON_Xform& xform) override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  bool GetAnnotationBoundingBox(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    double* boxmin,
    double* boxmax,
    bool bGrow = false
  ) const override; // ON_Annotation override

// Gets transform for dimension text from ON_xy_plane to 3d display location
  bool GetTextXform(
    const ON_Xform* model_xform,
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    ON_Xform& text_xform_out
  ) const;

  bool GetTextXform(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    ON_Xform& text_xform_out
  ) const override;

  /*
  Parameters:
    dim_style - [in]
      Pass nullptr if a dim_style is not available.
    arc - [in]
      arc being dimensioned
    offset - [in]
      distance from the arc being dimensioned to the angular dimension arc.
      When offset > 0, the dimension is outside the arc's circle. 
      When offset < 0 and > - arc.Radius(), the dimension is inside the arc's circle. 
      In all other cases, the angular dimension arc is on the arc.
  Returns:
    True if successful.
    False if input is not valid. In this case  ON_DimAngle::Empty settings are returned.
  */
  bool Create(
    const ON_DimStyle* dim_style,
    ON_Arc arc,
    double offset
  );

  /*
  Description:
    The angle between the lines is dimensioned. 
    
    If the lines intersect in a single point, that point is used as the center
    of the angular dimension arc. In this case, there are eight possible angles
    to dimension. The point_on_angular_dimension_arc and point_on_line parameters
    are used to select the correct angle to dimension. If a point_on_line parameter
    is not set, the corresponding line's midpoint is used.
    
    If the lines are colinear, the point on the line closest to 
    point_on_angular_dimension_arc is the center of the angular dimension arc.

  Parameters:
    dim_style - [in]
      Pass nullptr if a dim_style is not available.
    line1 - [in]
    point_on_line1 - [in]
      If point_on_line1 is specified, it indicates which semi-infinite portion of line1 to dimension.
      Otherwise the midpoint of lne1 as a segment is used.
      When in doubt, pass ON_3dPoint::UnsetPoint.
    line2 - [in]
    point_on_line2 - [in]
      If point_on_line2 is specified, it indicates which semi-infinite portion of line2 to dimension.
      Otherwise the midpoint of line2 as a segment is used.
      When in doubt, pass ON_3dPoint::UnsetPoint.
    point_on_angular_dimension_arc - [in]
      A point on the interior of the angular dimension arc. 
    bSetExtensionPoints - [in]
      If bSetExtensionPoints is true, and a point_on_line parameter is valid, that point
      is used as the extension point. Otherwise the angular dimension arc endpoint is used.
  Returns:
    True if successful.
    False if input is not valid. In this case  ON_DimAngle::Empty settings are returned.
  */
  bool Create(
    const ON_DimStyle* dim_style,
    ON_Line line1,
    ON_3dPoint point_on_line1,
    ON_Line line2,
    ON_3dPoint point_on_line2,
    ON_3dPoint point_on_angular_dimension_arc,
    bool bSetExtensionPoints
  );

  bool Create(
    const ON_UUID style_id,
    const ON_Plane& plane,
    const ON_3dVector& ref_horizontal,
    const ON_3dPoint& center_pt,
    const ON_3dPoint& extension_pt1,     // point on first extension vector
    const ON_3dPoint& extension_pt2,     // point on second extension vector
    const ON_3dPoint& dimline_pt         // point on dimension line
  );

  bool Create(
    const ON_UUID style_id,
    const ON_Plane& plane,
    const ON_3dVector& ref_horizontal,
    const ON_3dPoint& extension_pt1,     // start of first extension line
    const ON_3dPoint& extension_pt2,     // start of second extension line
    const ON_3dPoint& direction_pt1,     // point on first extension vector
    const ON_3dPoint& direction_pt2,     // point on second extension vector
    const ON_3dPoint& dimline_pt         // point on dimension line
  );

  bool AdjustFromPoints(
    const ON_Plane& plane,
    const ON_3dPoint& center_pt,          
    const ON_3dPoint& extension_pt1,      // point on first extension vector
    const ON_3dPoint& extension_pt2,      // point on second extension vector
    const ON_3dPoint& dimline_pt          // point on dimension line
    );

  bool AdjustFromPoints(
    const ON_Plane& plane,
    const ON_3dPoint& extension_pt1,     // start of first extension line
    const ON_3dPoint& extension_pt2,     // start of second extension line
    const ON_3dPoint& direction_pt1,     // point on first extension vector
    const ON_3dPoint& direction_pt2,     // point on second extension vector
    const ON_3dPoint& dimline_pt         // point on dimension line
  );

  static bool FindAngleVertex(
    ON_Line lines[2],
    ON_3dPoint pickpoints[2],
    const ON_Plane& plane,
    ON_3dPoint& centerpoint_out);


  bool UpdateDimensionText(const ON_DimStyle* dimstyle) const;

  bool GetAngleDisplayText(const ON_DimStyle* dimstyle, ON_wString& displaytext) const;

  // virtual
  double Measurement() const override;  // angle in radians
  ON_2dPoint DefaultTextPoint() const override;
  bool GetAngles(double* start_ang, double* end_ang, double* mid_ang) const;
  double Radius() const;

  // CenterPoint is m_plane.origin
  // Measurement is angle between m_vec_1 & m_vec_2 in radians
  ON_2dPoint CenterPoint() const;
  ON_2dPoint DefPoint1() const;     // Start of first extension
  ON_2dPoint DefPoint2() const;     // Start of second extension
  ON_2dPoint DimlinePoint() const;  // Point on dimension arc
  ON_2dPoint UserTextPoint() const; // Text point if user positioned
  ON_2dVector ExtDir1() const;      // Direction of first extension
  ON_2dVector ExtDir2() const;      // Direction of second extension
  void SetExtDir1(const ON_2dVector& dir1);
  void SetExtDir2(const ON_2dVector& dir2);
  
  void SetUserTextPoint(const ON_3dPoint& point);

  void Set2dCenterPoint(ON_2dPoint pt);   // Apex of angle
  void Set2dDefPoint1(ON_2dPoint pt);     // Point where first extension starts
  void Set2dDefPoint2(ON_2dPoint pt);     // Point where second extension starts
  void Set2dDimlinePoint(ON_2dPoint pt);  // Point on dimension arc

  //void Set2dDefPoint1(ON_2dPoint pt);     // Point where first extension starts
  //void Set2dDefPoint2(ON_2dPoint pt);     // Point where second extension starts
  //void Set2dDimlinePoint(ON_2dPoint pt);  // Point on dimension arc

  //void Set3dCenterPoint(ON_3dPoint pt);
  //void Set3dDefPoint1(ON_3dPoint pt);
  //void Set3dDefPoint2(ON_3dPoint pt);
  //void Set3dDimlinePoint(ON_3dPoint pt);

  ON_2dPoint ArrowPoint1() const;    // Calculated - start of arc
  ON_2dPoint ArrowPoint2() const;    // Calculated - end of arc

  bool Get3dPoints(
    ON_3dPoint* center,
    ON_3dPoint* defpt1,
    ON_3dPoint* defpt2,
    ON_3dPoint* arrowpt1,
    ON_3dPoint* arrowpt2,
    ON_3dPoint* dimline,
    ON_3dPoint* textpt) const;

  bool GetDisplayLines(
    const ON_Viewport* vp,
    const ON_DimStyle* style,
    double dimscale,
    const ON_3dPoint text_rect[4],
    ON_Line lines[2],
    bool isline[2],
    ON_Arc arcs[2],
    bool isarc[2],
    int maxlines,
    int maxarcs) const;

  void GetArrowXform(
    int which_end,
    double arrowlength,
    bool arrowflipped,
    bool from_the_back,
    ON_Xform& arrow_xform_out) const;

  bool UpdateDimensionText(
    ON::LengthUnitSystem units_in,
    const ON_DimStyle* dimstyle) const override;

  bool GetDistanceDisplayText(
    ON::LengthUnitSystem units_in,
    const ON_DimStyle* dimstyle,
    ON_wString& displaytext) const override;

protected:
  // Center point is at plane origin (0,0)
  ON_2dVector       m_vec_1 = ON_2dVector::XAxis;         
  ON_2dVector       m_vec_2 = ON_2dVector::YAxis;
  double            m_ext_offset_1 = 0.0;  // distance along m_vec_1 to start extension line 1
  double            m_ext_offset_2 = 0.0;  // distance along m_vec_2 to start extension line 2
  ON_2dPoint        m_dimline_pt = ON_2dPoint(1.0, 1.0);  // point on interior of dimension arc
};

//---------------------------------------------------------------------

class ON_CLASS ON_DimRadial : public ON_Dimension
{
  ON_OBJECT_DECLARE(ON_DimRadial);

public:
  ON_DimRadial();
  ~ON_DimRadial() = default;
  ON_DimRadial(const ON_DimRadial& src) = default;
  ON_DimRadial& operator=(const ON_DimRadial& src) = default;

  static const ON_DimRadial Empty;


  /*
  Description:
    Create a V6 radial dimension from a V5 radial dimension
    The function is used when reading V5 files.
  Parameters:
    V5_radial_dimension -[in]
    annotation_context - [in]
      Dimstyle and other information referenced by V5_radial_dimension or nullptr if not available.
    destination - [in]
      If destination is not nullptr, then the V6 radial dimension is constructed
      in destination. If destination is nullptr, then the new V6 radial dimension
      is allocated with a call to new ON_DimRadial().
  */
  static ON_DimRadial* CreateFromV5DimRadial(
    const class ON_OBSOLETE_V5_DimRadial& V5_radial_dimension,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_DimRadial* destination
  );
  
  /*
  Parameters:
    annotation_type - [in]
      annotation type to test
  Returns:
    True if input parameter is one of the valid radial dimension types
    ON::AnnotationType::Radius or ON::AnnotationType::Diameter.
  */
  static bool IsValidRadialDimensionType(
    ON::AnnotationType annotation_type
  );

  /*
  Parameters:
    radial_dimension_type - [in]
      ON::AnnotationType::Radius or ON::AnnotationType::Diameter.
  Returns:
    True if input parameter is valid and type is set.
  */
  bool SetRadialDimensionType(
    ON::AnnotationType radial_dimension_type
  );

  bool Write(
    ON_BinaryArchive&  // serialize definition to binary archive
    ) const override;

  bool Read(
    ON_BinaryArchive&  // restore definition from binary archive
    ) override;

  bool Transform(const ON_Xform& xform) override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  bool GetAnnotationBoundingBox(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    double* boxmin,
    double* boxmax,
    bool bGrow = false
  ) const override; // ON_Annotation override

  // Gets transform for dimension text from ON_xy_plane to 3d display location
  bool GetTextXform(
    const ON_Xform* model_xform,
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    ON_Xform& text_xform_out
  ) const;

  bool GetTextXform(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    ON_Xform& text_xform_out
  ) const override;

  bool Create(
    ON::AnnotationType type,
    const ON_UUID style_id,
    const ON_Plane& plane,
    const ON_3dPoint& center_pt,
    const ON_3dPoint& radius_pt,
    const ON_3dPoint& dimline_pt
    );

  bool AdjustFromPoints(
    const ON_Plane& plane,
    const ON_3dPoint& center_pt,
    const ON_3dPoint& radius_pt,
    const ON_3dPoint& dimline_pt
    );

  double Measurement() const override;

  ON_2dPoint DefaultTextPoint() const override;
  ON_2dPoint CenterPoint() const;
  ON_2dPoint RadiusPoint() const;      // Point on arc being measured
  ON_2dPoint DimlinePoint() const;     // Endpoint of leader tail, not including landing
  ON_2dPoint KneePoint() const;        // Point where leader tail bends

  void Set2dCenterPoint(ON_2dPoint pt);
  void Set2dRadiusPoint(ON_2dPoint pt);
  void Set2dDimlinePoint(ON_2dPoint pt);

  void Set3dCenterPoint(ON_3dPoint pt);
  void Set3dRadiusPoint(ON_3dPoint pt);
  void Set3dDimlinePoint(ON_3dPoint pt);

  bool Get3dPoints(
    ON_3dPoint* center_pt,
    ON_3dPoint* radius_pt,
    ON_3dPoint* dimline_pt,
    ON_3dPoint* knee_pt) const;

  bool GetDisplayLines(
    const ON_DimStyle* style,
    double dimscale,
    ON_3dPoint text_rect[4],
    ON_Line lines[9],
    bool isline[9],
    int maxlines) const;

  void GetArrowXform(
    double scale,
    ON_Xform& arrow_xform_out) const;

protected:
  ON_2dPoint        m_radius_pt = ON_2dPoint::UnsetPoint;
  ON_2dPoint        m_dimline_pt = ON_2dPoint::UnsetPoint;
};


//---------------------------------------------------------------------
//            + dimpt
//            |
//            |
//            |
//            + kinkpt2
//             \
//              \  kinkoffset2
//               \
//                + kinkpt1
//                |
//                |  kinkoffset1
//                |
//                +  ldrpt
//                1
//                2
//                3

class ON_CLASS ON_DimOrdinate : public ON_Dimension
{
  ON_OBJECT_DECLARE(ON_DimOrdinate);

public:
  ON_DimOrdinate();
  ~ON_DimOrdinate() = default;
  ON_DimOrdinate(const ON_DimOrdinate& src) = default;
  ON_DimOrdinate& operator=(const ON_DimOrdinate& src) = default;

  static const ON_DimOrdinate Empty;

#pragma region RH_C_SHARED_ENUM [ON_DimOrdinate::MeasuredDirection] [Rhino.Geometry.OrdinateDimension.MeasuredDirection] [nested:byte]
  /// <summary>
  /// Ordinate dimension measures x or y direction
  /// </summary>
  enum class MeasuredDirection : unsigned char
  {
    /// <summary> </summary>
    Unset = 0,
    /// <summary> Measures horizontal distance </summary>
    Xaxis = 1,
    /// <summary> Measures vertical distance </summary>
    Yaxis = 2,
  };
#pragma endregion

  static ON_DimOrdinate::MeasuredDirection MeasuredDirectionFromUnsigned(
    unsigned int measured_direction_as_unsigned
    );

  static ON_DimOrdinate* CreateFromV5DimOrdinate(
    const class ON_OBSOLETE_V5_DimOrdinate& V5_dim_ordinate,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_DimOrdinate* destination
  );

  bool Write(
    ON_BinaryArchive& archive
    ) const override;

  bool Read(
    ON_BinaryArchive& archive
    ) override;

  bool Transform(const ON_Xform& xform) override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  bool GetAnnotationBoundingBox(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    double* boxmin,
    double* boxmax,
    bool bGrow = false
  ) const override; // ON_Annotation override

  // Gets transform for dimension text from ON_xy_plane to 3d display location
  bool GetTextXform(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    ON_Xform& text_xform_out
  ) const override;

  bool GetTextXform(
    const ON_Xform* model_xform,
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    ON_Xform& text_xform_out
  ) const;

  bool Create(
    const ON_UUID style_id,
    const ON_Plane& plane,
    MeasuredDirection direction,
    const ON_3dPoint& basept,
    const ON_3dPoint& defpt,
    const ON_3dPoint& ldrpt,
    double kinkoffset1,
    double kinkoffset2
    );

  bool AdjustFromPoints(
    const ON_Plane& plane,
    MeasuredDirection direction,
    const ON_3dPoint& basept,
    const ON_3dPoint& defpt,
    const ON_3dPoint& ldrpt,
    double kinkoffset1,
    double kinkoffset2
    );

  ON_2dPoint DefPt() const;
  ON_2dPoint LeaderPt() const;
  ON_2dPoint KinkPt1() const;
  ON_2dPoint KinkPt2() const;
  double KinkOffset1() const;
  double KinkOffset2() const;

  void Set2dDefPt(ON_2dPoint pt);
  void Set2dLeaderPt(ON_2dPoint pt);
  void SetKinkOffset1(double d);
  void SetKinkOffset2(double d);

  void Set3dBasePoint(ON_3dPoint pt);
  void Set3dDefPt(ON_3dPoint pt);
  void Set3dLeaderPt(ON_3dPoint pt);

  ON_3dPoint Get3dBasePoint() const;
  ON_3dPoint Get3dDefPt() const;
  ON_3dPoint Get3dLeaderPt() const;
  ON_3dPoint Get3dKinkPt1(double default_kink_offset = 1.0) const;
  ON_3dPoint Get3dKinkPt2(double default_kink_offset = 1.0) const;

  bool Get3dPoints(
    ON_3dPoint* base_pt,
    ON_3dPoint* def_pt,
    ON_3dPoint* ldr_pt,
    ON_3dPoint* kink_pt1,
    ON_3dPoint* kink_pt2,
    double default_kink_offset = 1.0) const;

  bool GetDisplayLines(
    const ON_DimStyle* style,
    double dimscale,
    ON_3dPoint text_rect[4],
    ON_Line lines[3],
    bool isline[3],
    int maxlines) const;

  bool CalcKinkPoints(
    ON_2dPoint defpt,
    ON_2dPoint ldrpt,
    MeasuredDirection direction,
    double default_kink_offset,
    ON_2dPoint& kinkpt1_out,
    ON_2dPoint& kinkpt2_out) const;

  MeasuredDirection ImpliedDirection(
    ON_2dPoint defpt,
    ON_2dPoint ldrpt
    ) const;

  MeasuredDirection GetMeasuredDirection() const;
  void SetMeasuredDirection(MeasuredDirection direction);

  double Measurement() const override;

protected:
  // Plane origin is base for measurements
  // Measurements are from plane origin to dimension point
  // in either x or y axis direction
  MeasuredDirection  m_direction = MeasuredDirection::Unset;

  ON_2dPoint        m_def_pt = ON_2dPoint::UnsetPoint;
  ON_2dPoint        m_ldr_pt = ON_2dPoint::UnsetPoint;

  double            m_kink_offset_1 = ON_UNSET_VALUE; // measures from defpt1 toward defpt2 to kink1
  double            m_kink_offset_2 = ON_UNSET_VALUE; // measures from kink1 toward defpt2 to kink2
};


//---------------------------------------------------------------------

class ON_CLASS ON_Centermark : public ON_Dimension
{
  ON_OBJECT_DECLARE(ON_Centermark);

public:
  ON_Centermark();
  ~ON_Centermark() = default;
  ON_Centermark(const ON_Centermark& src) = default;
  ON_Centermark& operator=(const ON_Centermark& src) = default;

  static const ON_Centermark Empty;

  bool Write(
    ON_BinaryArchive&  // serialize definition to binary archive
    ) const override;

  bool Read(
    ON_BinaryArchive&  // restore definition from binary archive
    ) override;

  bool Transform(const ON_Xform& xform) override;

  bool GetTextXform(
    const ON_Viewport*,
    const ON_DimStyle*,
    double,
    ON_Xform&
  ) const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  bool GetAnnotationBoundingBox(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    double* boxmin,
    double* boxmax,
    bool bGrow = false
  ) const override; // ON_Annotation override

  bool Create(
    const ON_UUID style_id,
    const ON_Plane& plane,
    const ON_3dPoint& center_pt,
    const double radius
    );

  bool AdjustFromPoints(
    const ON_Plane& plane,
    const ON_3dPoint& center_pt
    );

  double Measurement() const override;

  ON_2dPoint CenterPoint() const;
  void Set2dCenterPoint(ON_2dPoint pt);
  void Set3dCenterPoint(ON_3dPoint pt);

  bool GetDisplayLines(
    const ON_DimStyle* style,
    double dimscale,
    ON_Line lines[6],
    bool isline[6],
    int maxlines) const;

  double Radius() const;         // radius of marked circle
  void SetRadius(double radius);

private:
  double m_radius = 0.0;
};




#endif

