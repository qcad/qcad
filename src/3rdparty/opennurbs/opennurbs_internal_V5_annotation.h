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

#ifndef OPENNURBS_INTERNAL_V5_ANNOTATION_H_INC
#define OPENNURBS_INTERNAL_V5_ANNOTATION_H_INC

#if defined(ON_COMPILING_OPENNURBS)
// V5 annotation classes are internal to opennurbs and are used exclusively
// to support reading and writing V5 3dm archives.

#if defined(ON_OS_WINDOWS_GDI)
#define ON_OBSOLETE_V5_RECT RECT
#else
typedef struct tagON_RECT
{
    int    left;
    int    top;
    int    right;
    int    bottom;
} ON_OBSOLETE_V5_RECT;
#endif

class ON_OBSOLETE_V5_AnnotationText : public ON_wString
{
public:
  ON_OBSOLETE_V5_AnnotationText();
  ~ON_OBSOLETE_V5_AnnotationText();

 
  ON_OBSOLETE_V5_AnnotationText& operator=(const char*);
  ON_OBSOLETE_V5_AnnotationText& operator=(const wchar_t*);

  void SetText( const char* s );
  void SetText( const wchar_t* s );

  // m_rect is a Windows gdi RECT that bounds text 
  // ("x" increases to the right and "y" increases downwards).
  // If all fields are 0, then m_rect is not set.
  // If left < right and top < bottom, then the rect bounds 
  // the text when it is drawn with its font's 
  // lfHeight=ON_Font::Constants::AnnotationFontCellHeight and (0,0) left baseline
  // point of the leftmost character on the first line
  // of text. If (x,y) is a point on the drawn text, then
  // left <= x < right and top <= y < bottom.
  ON_OBSOLETE_V5_RECT m_rect;
};

// Extension to ON_OBSOLETE_V2_TextObject added 12/10/2009 for Text background drawing
class ON_OBSOLETE_V5_TextExtra : public ON_UserData
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V5_TextExtra);
public:

  ON_OBSOLETE_V5_TextExtra();
  ~ON_OBSOLETE_V5_TextExtra();

  static
  ON_OBSOLETE_V5_TextExtra* TextExtension(class ON_OBSOLETE_V5_TextObject* pDim, bool bCreate);
  static const 
  ON_OBSOLETE_V5_TextExtra* TextExtension(const class ON_OBSOLETE_V5_TextObject* pDim, bool bCreate);

  void SetDefaults();

  // override virtual ON_Object::Dump function
  void Dump( ON_TextLog& text_log ) const override;

  // override virtual ON_Object::Dump function
  unsigned int SizeOf() const override;

  // override virtual ON_Object::Write function
  bool Write(ON_BinaryArchive& binary_archive) const override;

  // override virtual ON_Object::Read function
  bool Read(ON_BinaryArchive& binary_archive) override;

  // override virtual ON_UserData::GetDescription function
  bool GetDescription( ON_wString& description ) override;

  // override virtual ON_UserData::Archive function
  bool Archive() const override; 

  ON_UUID ParentUUID() const;
  void SetParentUUID( ON_UUID parent_uuid);

  bool DrawTextMask() const;
  void SetDrawTextMask(bool bDraw);

  int MaskColorSource() const;
  void SetMaskColorSource(int source);

  ON_Color MaskColor() const;  // Only works right if MaskColorSource returns 2.
                               // Does not return viewport background color
  void SetMaskColor(ON_Color color);

  double MaskOffsetFactor() const;
  void SetMaskOffsetFactor(double offset);

  ON_UUID  m_parent_uuid;    // uuid of the text using this extension

  bool     m_bDrawMask;      // do or don't draw a mask

  int      m_color_source;   // 0: Use background color from viewport
                             // 1: Use specific color from m_mask_color

  ON_Color m_mask_color;     // Color to use for mask if m_color_source is 2

  double   m_border_offset;  // Offset for the border around text to the rectangle used to draw the mask
                             // This number * HeightOfI for the text is the offset on each side of the 
                             // tight rectangle around the text characters to the mask rectangle.
};


class ON_OBSOLETE_V5_DimExtra : public ON_UserData
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V5_DimExtra);
public:

  ON_OBSOLETE_V5_DimExtra();
  ~ON_OBSOLETE_V5_DimExtra();

  static
  ON_OBSOLETE_V5_DimExtra* DimensionExtension(class ON_OBSOLETE_V5_DimLinear* pDim, bool bCreate);
  static const 
  ON_OBSOLETE_V5_DimExtra* DimensionExtension(const class ON_OBSOLETE_V5_DimLinear* pDim, bool bCreate);
  static
  ON_OBSOLETE_V5_DimExtra* DimensionExtension(class ON_OBSOLETE_V5_DimRadial* pDim, bool bCreate);
  static const 
  ON_OBSOLETE_V5_DimExtra* DimensionExtension(const class ON_OBSOLETE_V5_DimRadial* pDim, bool bCreate);
  static
  ON_OBSOLETE_V5_DimExtra* DimensionExtension(class ON_OBSOLETE_V5_DimOrdinate* pDim, bool bCreate);
  static const 
  ON_OBSOLETE_V5_DimExtra* DimensionExtension(const class ON_OBSOLETE_V5_DimOrdinate* pDim, bool bCreate);

  void SetDefaults();

  // override virtual ON_Object::Dump function
  void Dump( ON_TextLog& text_log ) const override;

  // override virtual ON_Object::Dump function
  unsigned int SizeOf() const override;

  // override virtual ON_Object::Write function
  bool Write(ON_BinaryArchive& binary_archive) const override;

  // override virtual ON_Object::Read function
  bool Read(ON_BinaryArchive& binary_archive) override;

  // override virtual ON_UserData::GetDescription function
  bool GetDescription( ON_wString& description ) override;

  // override virtual ON_UserData::Archive function
  bool Archive() const override; 

  ON_UUID ParentUUID() const;
  void SetParentUUID( ON_UUID parent_uuid);

  //  0: default position
  //  1: force inside
  // -1: force outside
  int ArrowPosition() const;
  void SetArrowPosition( int position);

  // For a dimension in page space that measures between points in model space
  // of a detail view, this is the ratio of the page distance / model distance.
  // When the dimension text is displayed, the distance measured in model space
  // is multiplied by this number to get the value to display.
  double DistanceScale() const;
  void SetDistanceScale(double s);

  // Basepont in modelspace coordinates for ordinate dimensions
  void SetModelSpaceBasePoint(ON_3dPoint basepoint);
  ON_3dPoint ModelSpaceBasePoint() const;

  // If this dimension measures objects in the model space of a detail view
  // this is the detail view, otherwise, nil_uuid
  ON_UUID DetailMeasured() const;
  void SetDetailMeasured(ON_UUID detail_id);

  //const wchar_t* ToleranceUpperString() const;
  //ON_wString& ToleranceUpperString();
  //void SetToleranceUpperString( const wchar_t* upper_string);
  //void SetToleranceUpperString( ON_wString& upper_string);

  //const wchar_t* ToleranceLowerString() const;
  //ON_wString& ToleranceLowerString();
  //void SetToleranceLowerString( const wchar_t* lower_string);
  //void SetToleranceLowerString( ON_wString& lower_string);

  //const wchar_t* AlternateString() const;
  //ON_wString& AlternateString();
  //void SetAlternateString( const wchar_t* alt_string);
  //void SetAlternateString( ON_wString& alt_string);

  //const wchar_t* AlternateToleranceUpperString() const;
  //ON_wString& AlternateToleranceUpperString();
  //void SetAlternateToleranceUpperString( const wchar_t* upper_string);
  //void SetAlternateToleranceUpperString( ON_wString& upper_string);

  //const wchar_t* AlternateToleranceLowerString() const;
  //ON_wString& AlternateToleranceLowerString();
  //void SetAlternateToleranceLowerString( const wchar_t* lower_string);
  //void SetAlternateToleranceLowerString( ON_wString& lower_string);

  ON_UUID m_partent_uuid;  // the dimension using this extension

  int m_arrow_position;

  // This is either nullptr or an array of GDI rects for the substrings 
  // that make up the dimension string.
  // If the dimension text is all on the same line, there is just one
  // rectangle needed to bound the text and that is the same as the
  // m_rect on the ON_OBSOLETE_V5_AnnotationText.
  // If the dimension has tolerances or for some other reason has more
  // than one line of text, m_text_rects is an array of 7 rects, one
  // each for the substrings that might be needed to display the dimension.
  // If some of the rects aren't used, they are empty at 0,0
  // The strings that correspond to these rectangles are generated from
  // info in the dimstyle
  ON_OBSOLETE_V5_RECT* m_text_rects;

  double m_distance_scale;
  ON_3dPoint m_modelspace_basepoint;

  // If this dimension measures objects in the model space of a detail view
  // this is the detail view
  // 27 Aug, 2014, v6
  ON_UUID m_detail_measured;
};


/*
  class ON_OBSOLETE_V5_Annotation

    Description:
      Used to serialize definitions of annotation objects (dimensions, text, leaders, etc.).
      Virtual base class for annotation objects
      Replaces ON_OBSOLETE_V2_Annotation
*/
class ON_OBSOLETE_V5_Annotation : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V5_Annotation);

protected:
  ON_OBSOLETE_V5_Annotation();
  ON_OBSOLETE_V5_Annotation(const ON_OBSOLETE_V5_Annotation&) = default;
  ON_OBSOLETE_V5_Annotation& operator=(const ON_OBSOLETE_V5_Annotation&) = default;

public:
  virtual ~ON_OBSOLETE_V5_Annotation();

protected:
  void Internal_InitializeFromV2Annotation(
    const class ON_OBSOLETE_V2_Annotation& V2_annotation,
    const class ON_3dmAnnotationContext* annotation_context
  );

public:
  static ON_OBSOLETE_V5_Annotation* CreateFromV2Annotation(
    const class ON_OBSOLETE_V2_Annotation& V2_annotation,
    const class ON_3dmAnnotationContext* annotation_context
  );

public:
  static ON_OBSOLETE_V5_Annotation* CreateFromV6Annotation(
    const class ON_Annotation& V6_annotation,
    const class ON_3dmAnnotationContext* annotation_context
  );

protected:
  ////void Internal_SetDimStyleFromV6Annotation(
  ////  const class ON_Annotation& V6_annotation,
  ////  const class ON_3dmAnnotationContext* annotation_context
  ////);

public:

  // Description:
  //   Sets initial defaults
  void Create();

  void Destroy();

  void EmergencyDestroy();

  /////////////////////////////////////////////////////////////////
  //
  // ON_Object overrides
  //

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;


  /*
    Description: Writes the object to a file

    Returns:
      @untitled Table
      true     Success
      false    Failure
  */
  bool Write(
         ON_BinaryArchive&
       ) const override;

  /*
    Description: Reads the object from a file

    Returns:
      @untitled Table
      true     Success
      false    Failure
  */
  bool Read(
         ON_BinaryArchive&
       ) override;

  /*
    Returns: The Object Type of this object
  */
  ON::object_type ObjectType() const override;

  /////////////////////////////////////////////////////////////////
  //
  // ON_Geometry overrides
  //

  /*
    Returns the geometric dimension of the object ( usually 3)
  */
  int Dimension() const override;

  // overrides virtual ON_Geometry::Transform()
  bool Transform( const ON_Xform& xform ) override;

  // virtual ON_Geometry override
  bool EvaluatePoint( const class ON_ObjRef& objref, ON_3dPoint& P ) const override;

  /////////////////////////////////////////////////////////////////
  //
  // ON_OBSOLETE_V5_Annotation interface
  //

  // Definitions of text justification
  // Not implemented on all annotation objects
  enum eTextJustification
  {
    tjUndefined = 0,
    tjLeft   = 1<<0,
    tjCenter = 1<<1,
    tjRight  = 1<<2,
    tjBottom = 1<<16,
    tjMiddle = 1<<17,
    tjTop    = 1<<18,
    tjBottomLeft   = tjBottom | tjLeft,
    tjBottomCenter = tjBottom | tjCenter,
    tjBottomRight  = tjBottom | tjRight,
    tjMiddleLeft   = tjMiddle | tjLeft,
    tjMiddleCenter = tjMiddle | tjCenter,
    tjMiddleRight  = tjMiddle | tjRight,
    tjTopLeft      = tjTop    | tjLeft,
    tjTopCenter    = tjTop    | tjCenter,
    tjTopRight     = tjTop    | tjRight,
  };

  /*
    Description:
      Query if the annotation object is a text object
    Parameters:
      none
    Returns:
      @untitled table
      true    It is text
      false   Its not text
  */
  bool IsText() const;

  /*
    Description:
      Query if the annotation object is a leader
    Parameters:
      none
    Returns:
      @untitled table
      true    It is a leader
      false   Its not a leader
  */
  bool IsLeader() const;

  /*
    Description:
      Query if the annotation object is a dimension
    Parameters:
      none
    Returns:
      @untitled table
      true    It is a dimension
      false   Its not a dimension
  */
  bool IsDimension() const;

public:
  int V5_3dmArchiveDimStyleIndex() const;

  /*
  Description:
    If IsText() is false, the dimension style is set.
  */
  void SetV5_3dmArchiveDimStyleIndex( 
    int V5_dim_style_index
    );

  ////ON_UUID V6_DimStyleId() const;



  /////*
  ////Description:
  ////  If IsText() is false, the dimension style is set.
  ////*/
  ////void SetV6_DimStyleId( 
  ////  ON_UUID dim_style_id,
  ////  int V5_dim_style_index
  ////  );

  ////const ON_DimStyle* V6_DimStyleOverride() const;

  /////*
  ////Description:
  ////  If IsText() is false, the dimension style is set.
  ////*/
  ////void SetV6_DimStyleOverride( 
  ////  const ON_DimStyle* dim_style_override,
  ////  int V5_dim_style_index
  ////  );

public:

  /*
  Returns:
    Dimension type
    Linear dim:  distance between arrow tips
    Radial dim:  radius or diameter depending on m_type value
    Angular dim: angle in degrees
    Leader:      ON_UNSET_VALUE
    Text:        ON_UNSET_VALUE
  */
  virtual 
  double NumericValue() const;

  /*
    Description:
      Set  or Get the height of the text in this annotation
    Parameters:
      [in] double new text height to set
    Returns:
      double Height of the text
    Remarks:
      Height is in model units
  */
  void SetHeight( double);
  double Height() const;

  /*
    Description:
      Sets or gets the object type member to a specific annotation type:
           dtDimLinear, dtDimAligned, dtDimAngular, etc.
    Parameters:
      [in] ON_INTERNAL_OBSOLETE::V5_eAnnotationType type - dtDimLinear, dtDimAligned, dtDimAngular, etc.
    Returns:
      ON_INTERNAL_OBSOLETE::V5_eAnnotationType of the object
  */
  void SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType);
  ON_INTERNAL_OBSOLETE::V5_eAnnotationType Type() const;

  /*
    Description:
      Set or get the plane for the object's ECS
    Parameters:
      [in] ON_Plane& plane in WCS
    Returns:
      const ON_Plane& - the object's ECS plane in WCS coords
  */
  void SetPlane( const ON_Plane&);
  const ON_Plane& Plane() const;

  /*
    Description:
      Returns the number of definition points this object has
    Parameters:
      none
    Returns:
      @untitled table
      int   the object's point count
  */
  int PointCount() const;
  void SetPointCount( int count);

  /*
    Description:
      Set or get the object's whole points array at once
    Parameters:
      [in] ON_2dPointArray& pts
    Returns:
      const ON_2dPointArray& - ref to the object's point array
  */
  void SetPoints( const ON_2dPointArray&);
  const ON_2dPointArray& Points() const;

  /*
    Description:
      Set individual definition points for the annotation
    Parameters:
      @untitled table
      [in] int index               index of the point to set in ECS 2d coordinates
      [in] const ON_2dPoint& pt    the new point value
    Returns:
      ON_2dPoint   the point coordinates in ECS
  */
  void SetPoint( int, const ON_2dPoint&);
  ON_2dPoint Point( int) const;

  /*
    Description:
      
      Set or get the string value of the user text, with no substitution for "<>"
    Parameters:
      [in] const wchar_t* string   the new value for UserText
    Returns:
      const ON_wString&    The object's UserText
    Remarks:
      UserText is the string that gets printed when the dimensoin is drawn.
      If it contains the token "<>", that token is replaced with the measured
      value for the dimension, formatted according to the DimStyle settings.
      "<>" is the default for linear dimensions.
      Other dimensions include "<>" in their default string
  */

  ON_DEPRECATED_MSG("use SetTextValue function")
  void SetUserText( const wchar_t* text_value );

  ON_DEPRECATED_MSG("use TextValue function")
  const ON_wString& UserText() const;


  /*
  Description:
    Gets the value of the annotation text.
  Returns:
    Value of the annotation text.
  See Also:
    ON_OBSOLETE_V5_AnnotationText::SetTextValue()
    ON_OBSOLETE_V5_AnnotationText::SetTextFormula()
    ON_OBSOLETE_V5_AnnotationText::TextFormula()    
  Remarks:
    This gets the literal value of the text, there is no
    substitution for any "<>" substrings.  When a dimension
    is drawn, any occurrence of "<>" will be replaced
    with the measured value for the dimension and formatted
    according to the DimStyle settings.

    Annotation text values can be constant or the result 
    of evaluating text formula containing %<...>% 
    expressions. The ...TextValue() functions set
    and get the text's value.  The ...TextFormula()
    functions get and set the text's formula.
  */
  const wchar_t* TextValue() const;

  /*
  Description:
    Sets the value of the annotation text.  No changes
    are made to the text_value string.
  Parameters:
    text_value - [in]
  Returns:
    Value of the annotation text.
  See Also:
    ON_OBSOLETE_V5_AnnotationText::SetTextFormula()
    ON_OBSOLETE_V5_AnnotationText::TextValue()    
    ON_OBSOLETE_V5_AnnotationText::TextFormula()    
  Remarks:
    Annotation text values can be constant or the result 
    of evaluating text formula containing %<...>% 
    expressions. The ...TextValue() functions set
    and get the text's value.  The ...TextFormula()
    functions get and set the text's formula.
  */
  void SetTextValue( const wchar_t* text_value );

  /*
  Description:
    Gets the formula for the annotation text.
  Parameters:
    text_value - [in]
  Returns:
    Value of the annotation text.
  See Also:
    ON_OBSOLETE_V5_AnnotationText::SetTextValue()
    ON_OBSOLETE_V5_AnnotationText::TextValue()    
    ON_OBSOLETE_V5_AnnotationText::TextFormula()    
  Remarks:
    Annotation text values can be constant or the result 
    of evaluating text formula containing %<...>% 
    expressions. The ...TextValue() functions set
    and get the text's value.  The ...TextFormula()
    functions get and set the text's formula.
  */
  const wchar_t* TextFormula() const;

  /*
  Description:
    Sets the formula for the annotation text.
  Parameters:
    text_value - [in]
  Returns:
    Value of the annotation text.
  See Also:
    ON_OBSOLETE_V5_AnnotationText::SetTextValue()
    ON_OBSOLETE_V5_AnnotationText::Value()    
    ON_OBSOLETE_V5_AnnotationText::Formula()    
  Remarks:
    Annotation text values can be constant or the result 
    of evaluating text formula containing %<...>% 
    expressions. The ...TextValue() functions set
    and get the text's value.  The ...TextFormula()
    functions get and set the text's formula.
  */
  void SetTextFormula( const wchar_t* s );

  /*
    Description:
      Set or get a flag indication that the dimension text has been moved
      from the default location.
    Parameters:
      bUserPositionedText - [in] 
               true to indicate that the text has been placed by the user.
               false to indicate that it hasn't
    Returns:
      @untitled table
      true    The text has been moved
      false   The text is in the default location
    Remarks:
      If the text is in the default location, it should be repositioned
      automatically when the dimension is adjusted.
      If it has been moved, it should not be automatically positioned.
  */
  void SetUserPositionedText( int bUserPositionedText );
  bool UserPositionedText() const;

  /*
    Description:
      Set or get the text display mode for the annotation
    Parameters:
      [in] ON::eTextDisplayMode mode - new mode to set
    Returns:
      ON::eTextDisplayMode  - current mode
    Remarks:
      This is the way the text is oriented with respect to the dimension line or screen:
      Above line, In LIne, Horizontal
  */
  void SetTextDisplayMode( ON_INTERNAL_OBSOLETE::V5_TextDisplayMode);
  ON_INTERNAL_OBSOLETE::V5_TextDisplayMode TextDisplayMode() const;


  /*
    Description:
      Gets a transform matrix to change from the object's 2d ECS to 3d WCS
    Parameters:
      [out] xform   set to produce the ECS to WCS transform
    Returns:
      @untitled table
      true    Success
      false   Failure
  */
  bool GetECStoWCSXform( ON_Xform&) const;

  /*
    Description:
      Gets a transform matrix to change from to 3d WCS to the object's 2d ECS
    Parameters:
      [out] xform - set to produce the WCS to ECS transform
    Returns:
      @untitled table
      true    Success
      false   Failure
  */
  bool GetWCStoECSXform( ON_Xform& xform) const;

  /*
    Description:
      Set the object's point array to a specified length
    Parameters:
      [in] length - the new size of the array
    Returns:
      void
  */
  void ReservePoints( int);


  /*
    Description:
      static function to provide the default UserText string for the object
    Returns:
      const wchar_t* - the default string to use
  */
  static const wchar_t* DefaultText();

  /*
    Description:
      Set or Get the text justification
    Parameters:
      justification [in] See enum eJustification for meanings
    Returns:
      The justification for the text in this object
    Comments:
      This is not implemented on all annotation objects.
      The default SetJustification() does nothing
      The default Justification() always returns 0

  */
  virtual
  void SetJustification( unsigned int justification);

  virtual unsigned int Justification() const;

  /*
    Description:
      Get the transformation that maps the annotation's
      text to world coordinates.
      Added Oct 30, 07 LW
    Parameters:
      gdi_text_rect - [in] 
              Windows gdi rect of text when it is drawn with
              LOGFONT lfHeight = ON_Font::Constants::AnnotationFontCellHeight.
      gdi_height_of_I - [in]
         Value returned by ON_Font::HeightOfI().
      dimstyle_textheight - [in]
         Height of text in world units.  If the annotation is
         an ON_OBSOLETE_V5_TextObject, this is the m_textheight value.  
         If the annotation is not an ON_OBSOLETE_V5_TextObject, pass in 
         the value returned by the dimension style's 
         ON_DimStyle::TextHeight() 
      dimstyle_textgap - [in]
         The value of the annotation's dimension style's 
         ON_DimStyle::TextGap().
      dimstyle_textalignment - [in]
         ON_INTERNAL_OBSOLETE::V5_TextDisplayMode(ON_DimStyle::TextAlignment()).
      dimscale - [in]
         Global dimension scaling value.  If you are using the
         Rhino SDK, this value is returned by
         CRhinoDoc::Properties().AnnotationSettings().DimScale().
         If you are using the OpenNURBS IO toolkit, this value
         is on ON_3dmSettings::m_AnnotationSettings.m_dimscale.
      cameraX - [in]
         zero or the view's unit camera right vector
      cameraY - [in]
         zero or the view's unit camera up vector
      model_xform - [in] transforms the text's parent entity 
         to world coordinates in case its instance geometry
         nullptr == Identity
      text_xform - [out]
    Returns:
      True if text_xform is set.
  */
  bool GetTextXform( 
        ON_OBSOLETE_V5_RECT gdi_text_rect,
        int gdi_height_of_I,
        double dimstyle_textheight,
        double dimstyle_textgap,
        ON_INTERNAL_OBSOLETE::V5_TextDisplayMode dimstyle_textalignment,
        double dimscale,
        ON_3dVector cameraX,
        ON_3dVector cameraY,
        const ON_Xform* model_xform,
        ON_Xform& text_xform // output
        ) const;

  /*
    Description:

    This function has been replaced with a version that
    takes a model transform to transform block instance 
    geometry to world coordinates  Oct 30, 07 LW

      Get the transformation that maps the annotation's
      text to world coordinates.
    Parameters:
      gdi_text_rect - [in] 
              Windows gdi rect of text when it is drawn with
              LOGFONT lfHeight = ON_Font::Constants::AnnotationFontCellHeight.
      gdi_height_of_I - [in]
         Value returned by ON_Font::HeightOfI().
      dimstyle_textheight - [in]
         Height of text in world units.  If the annotation is
         an ON_OBSOLETE_V5_TextObject, this is the m_textheight value.  
         If the annotation is not an ON_OBSOLETE_V5_TextObject, pass in 
         the value returned by the dimension style's 
         ON_DimStyle::TextHeight() 
      dimstyle_textgap - [in]
         The value of the annotation's dimension style's 
         ON_DimStyle::TextGap().
      dimstyle_textalignment - [in]
         ON_INTERNAL_OBSOLETE::V5_TextDisplayMode(ON_DimStyle::TextAlignment()).
      dimscale - [in]
         Global dimension scaling value.  If you are using the
         Rhino SDK, this value is returned by
         CRhinoDoc::Properties().AnnotationSettings().DimScale().
         If you are using the OpenNURBS IO toolkit, this value
         is on ON_3dmSettings::m_AnnotationSettings.m_dimscale.
      cameraX - [in]
         zero or the view's unit camera right vector
      cameraY - [in]
         zero or the view's unit camera up vector
      xform - [out]
    Returns:
      True if xform is set.
  */
  bool GetTextXform( 
        ON_OBSOLETE_V5_RECT gdi_text_rect,
        int gdi_height_of_I,
        double dimstyle_textheight,
        double dimstyle_textgap,
        ON_INTERNAL_OBSOLETE::V5_TextDisplayMode dimstyle_textalignment,
        double dimscale,
        ON_3dVector cameraX,
        ON_3dVector cameraY,
        ON_Xform& xform
        ) const;

  /*
    Description:
      Get the transformation that maps the annotation's
      text to world coordinates.
      Oct 30, 07 LW
    Parameters:
      gdi_text_rect - [in] 
              Windows gdi rect of text when it is drawn with
              LOGFONT lfHeight = ON_Font::Constants::AnnotationFontCellHeight.
      font - [in]
      dimstyle - [in]
      dimscale - [in]
         Global dimension scaling value.  If you are using the
         Rhino SDK, this value is returned by
         CRhinoDoc::Properties().AnnotationSettings().DimScale().
         If you are using the OpenNURBS IO toolkit, this value
         is on ON_3dmSettings::m_AnnotationSettings.m_dimscale.
      vp - [in]
      model_xform - [in] transforms the text's parent entity 
         to world coordinates in case its instance geometry
         nullptr == Identity
      text_xform - [out]
    Returns:
      True if text_xform is set.
  */
  bool GetTextXform( 
      const ON_OBSOLETE_V5_RECT gdi_text_rect,
      const ON_Font& font,
      const ON_DimStyle* dimstyle,
      double dimscale,
      const ON_Viewport* vp,
      const ON_Xform* model_xform,
      ON_Xform& text_xform  // output
      ) const;

  /*
  Description:
    Get the annotation plane coordinates (ECS) of the point
    that is used to position the text.  The relative position
    of the text to this points depends on the type of
    annotation, the dimstyle's text alignment flag, and the
    view projection.
    This point is not  the same as the base point of the text.
  Parameters:
    text_point - [out];
  Returns:
    True if text_point is set.
  */
  bool GetTextPoint( ON_2dPoint& text_2d_point ) const;

  // enum for tyoe of annotation DimLinear, DimRadius, etc.
  ON_INTERNAL_OBSOLETE::V5_eAnnotationType m_type;

  // m_textdisplaymode controls the orientation
  // of the text.
  // If m_textdisplaymode = dtHorizontal, then
  // the text is always horizontal and in the
  // view plane.  Otherwise it lies in m_plane.
  ON_INTERNAL_OBSOLETE::V5_TextDisplayMode m_textdisplaymode;

  // m_plane is the plane containing the annotation.
  // All parts of the annotation that are not
  // text lie in this plane. If
  // m_textdisplaymode != dtHorizontal, then
  // the text lies in the plane too.  
  // (ECS reference plane in WCS coordinates.)
  ON_Plane m_plane;

  // Definition points for the dimension.
  // These are 2d coordinates in m_plane.
  // The location of these points depends on the
  // type of annotation class.  There is a comment
  // at the start of the definions for
  // ON_OBSOLETE_V5_DimLinear, ON_OBSOLETE_V5_DimRadial,
  // ON_OBSOLETE_V5_DimAngular, ON_OBSOLETE_V5_TextObject, and
  // ON_OBSOLETE_V5_Leader that explains how the points are used.
  ON_2dPointArray m_points;

  // With the addition of tolerances and therefore multi-line
  // text, the ON_wString in m_usertext will hold multiple 
  // strings with NULLs between them.  
  // The strings will be in this order:
  // Result of expanding "<>", or user override
  // Alternate dimension
  // Tolerance upper
  // Tolerance lower
  // Alt tolerance upper
  // Alt tolerance lower
  // Prefix
  // Suffix
  // Alt prefix
  // Alt suffix
  // 
  ON_OBSOLETE_V5_AnnotationText m_usertext;

  // true: User has positioned text
  // false: use default location
  bool m_userpositionedtext;
  // Added 13 Aug, 2010 - Lowell
  // This determines whether the object will be scaled according to detail
  // scale factor or by 1.0 in paperspace rather than by 
  // dimscale or text scale.
  // For the first try this will only be used on text and its
  // here on the base class because it would fit and in case 
  // its needed later on dimensions.
  bool m_annotative_scale;
private:
  bool m_reserved_b1;
  bool m_reserved_b2;
public:

private:
  // At this point, the ON_OBSOLETE_V5_Annotation and derived classes
  // exists for a single purpose - to support reading and writing
  // V5 (4,3,2) 3dm archives. 
  // In V5 archives all dimension styles, including per object overrides
  // were in the archive dimstyle table. In V6 and later, override dimstyles
  // are managed by the object that uses them.
  //
  // This class used to have a single dimstyle table index.
  // That index has been removed and replaced with the following
  // information that is parallel to the information on ON_Annotation.
   
  // Dimstyle index to use when writing a V5 archive.
  int m_v5_3dm_archive_dimstyle_index = ON_UNSET_INT_INDEX;

public:
  // Text height in model units
  // This is used by text, but not by dimensions
  // Dimensions get their height from dimension styles
  double m_textheight;

  // Left, Center, Right / Bottom, Middle, Top text justification
  // See eTextJustification above
  unsigned int m_justification;
};


// Subclass of ON_OBSOLETE_V5_Annotation to provide linear dimensions
class ON_OBSOLETE_V5_DimLinear : public ON_OBSOLETE_V5_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V5_DimLinear);

public:

  /*
    The annotation's dimstyle controls the position of TEXT,
    the size of the arrowheads, and the amount the ends of 
    linear dimension's extension lines extend beyond the 
    dimension lines.

    In the picture below, [n] means ON_OBSOLETE_V5_Annotation::m_points[n].

                                                     [2]
                                                      |
        |                                             |
       [1]-------------------------------------------[3]
        |                                             |
        |                       TEXT
        |                       [4]
       [0]

      The "x" and "y" coordinates of [0] must be (0.0, 0.0).

      The "x" coordinate of [1] = "x" of [0]
      The "y" coordinate of [1] can be any value.

      The "x" and "y" coordinates of [2] can be any value.

      The "x" coordinate of [3] = "x" coordinate of [2].
      The "y" coordinate of [3] = "y" coordinate of [1].
  */

  enum POINT_INDEX
  {
    // Do not change these enum values.  They are saved in files as the 
    // ON_COMPONENT_INDEX.m_index value.
    //
    // Indices of linear dimension definition points in 
    // the m_points[] array
    ext0_pt_index    = 0, // end of first extension line
    arrow0_pt_index  = 1, // arrowhead tip on first extension line
    ext1_pt_index    = 2, // end of second extension line
    arrow1_pt_index  = 3, // arrowhead tip on second extension line
    userpositionedtext_pt_index = 4,
    dim_pt_count     = 5, // number of m_points[] in an angular dim

    // Points calculated from values in m_points[]
    text_pivot_pt = 10000, // center of dimension text
    dim_mid_pt    = 10001  // midpoint of dimension line
  };

public:
  ON_OBSOLETE_V5_DimLinear();
  ~ON_OBSOLETE_V5_DimLinear();
  ON_OBSOLETE_V5_DimLinear( const ON_OBSOLETE_V5_DimLinear& ) = default;
  ON_OBSOLETE_V5_DimLinear& operator=(const ON_OBSOLETE_V5_DimLinear&) = default;

  /*
  Description:
    Create a V5 linear dimension from a V6 linear dimension. 
    The function is used when writing V5 files.
  Parameters:
    V6_dim_linear -[in]
    annotation_context - [in]
      Dimstyle and other information referenced by V6_dim_linear or nullptr if not available.
    destination - [in]
      If destination is not nullptr, then the V5 linear dimension is constructed
      in destination. If destination is nullptr, then the new V5 linear dimension
      is allocated with a call to new ON_OBSOLETE_V5_DimLinear().
  */
  static ON_OBSOLETE_V5_DimLinear* CreateFromV6DimLinear(
    const class ON_DimLinear& V6_dim_linear,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V5_DimLinear* destination
  );

  static ON_OBSOLETE_V5_DimLinear* CreateFromV2LinearDimension( 
    const class ON_OBSOLETE_V2_DimLinear& V2_linear_dimension,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V5_DimLinear* destination
  );

  // overrides virtual ON_Geometry::Transform()
  bool Transform( const ON_Xform& xform ) override;

  /*
  Description:
    Checks the linear dimension and repairs any point locations or flags
    that are not set correctly.
  Returns:
    0:  linear dimension is damaged beyond repair
    1:  linear dimension was perfect and nothing needed to be repaired.
    2:  linear dimension had flaws that were repaired.
  */
  int Repair();

  /*
  Description:
    Get the m_plane coordinates of the dimension point.
  Parameters:
    point_index - [in] One of the POINT_INDEX enum values
  Returns:
    2d point or ON_3dPoint::UnsetPoint if point_index or m_points[]
    array is not valid.
  */
  ON_2dPoint Dim2dPoint(
       int point_index
       ) const;

  /*
  Description:
    Get the m_plane coordinates of the dimension point.
  Parameters:
    point_index - [in] One of the POINT_INDEX enum values
  Returns:
    2d point or ON_3dPoint::UnsetPoint if point_index or m_points[]
    array is not valid.
  */
  ON_3dPoint Dim3dPoint(
       int point_index
       ) const;

  // overrides virual ON_Object::IsValid
  bool IsValid( ON_TextLog* text_log = nullptr ) const override;

  // overrides virual ON_Object::Write
  bool Write(ON_BinaryArchive&) const override;

  // overrides virual ON_Object::Read
  bool Read(ON_BinaryArchive&) override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  // virtual ON_Geometry GetTightBoundingBox override		
  bool GetTightBoundingBox( class ON_BoundingBox& tight_bbox, bool bGrowBox = false, const class ON_Xform* xform = nullptr ) const override;

  /*
  Description:
    Overrides virtual ON_OBSOLETE_V5_Annotation::NumericValue();
  Returns:
    distance between arrow tips
  */
  double NumericValue() const override;

  /*
    Description:
      Get or set the DimStyle index in the dimstyle table for the dimension
    Parameters:
      [in] int  the new index (Set)
    Returns:
      int -  The current index (Get)
  */
  int StyleIndex() const;
  void SetStyleIndex( int);

  /*
    Description:
      static function to provide the default UserText string for the object
    Returns:
      const wchar_t* - the default string to use
  */
  static const wchar_t* DefaultText();


  /*
  Description:
    Get the annotation plane x coordinates of the dimension
    line. The y coordinate of the dimension line is m_ponts[1].y.
  Parameters:
    gdi_text_rect - [in] 
       Windows rect (left < right, top < bottom) that bounds text.
       The baseline of the text should be at y=0 in the rect coordinates.
    gdi_height_of_I - [in] 
       Height of an I in the text in the same.
    gdi_to_world - [in] 
       transform returned by ON_OBSOLETE_V5_Annotation::GetTextXform().
    dimstyle - [in]
      dimscale - [in]
    vp - [in]
    x - [out] plane x coordinates of the dimension line.
              The y coordinate = m_points[arrow0_pt_index].y
    bInside - [out] true if arrowheads go inside extension lines, 
                    false if they go outside
  Returns:
    0: the input or class is not valid
    1: A single line from x[0] to x[1] with arrow heads at both ends.
        Arrowtips at x[4] & x[5]
    2: Two lines from x[0] to x[1] and from x[1] to x[2].  The
        Arrowtips at x[4] & x[5]
       
  */
  int GetDimensionLineSegments(
      ON_OBSOLETE_V5_RECT gdi_text_rect,
      int gdi_height_of_I,
      ON_Xform gdi_to_world,
      const ON_DimStyle& dimstyle,
      double dimscale,
      const ON_Viewport* vp,
      double a[6],
      bool& bInside
      ) const;


  // Added for V5. 4/24/07 LW
  // Get the userdata extension for this dimension
  ON_OBSOLETE_V5_DimExtra* DimensionExtension();
  const ON_OBSOLETE_V5_DimExtra* DimensionExtension() const;
};

//////////
// class ON_OBSOLETE_V5_DimRadial
class ON_OBSOLETE_V5_DimRadial : public ON_OBSOLETE_V5_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V5_DimRadial);

public:

  /*
    The annotation's dimstyle controls the position of TEXT,
    and the size of the arrowheads.

    In the picture below, [n] means ON_OBSOLETE_V5_Annotation::m_points[n].

    Radial dimensions do not permit user positioned text


           knee
            [3]--------[2] TEXT
            /         (tail)
           /
          /
        [1] (arrow head here)


    + [0] = (usually at (0,0) = center of circle)
  */

  enum POINT_INDEX
  {
    // Do not change these enum values.  They are saved in files as the 
    // ON_COMPONENT_INDEX.m_index value.
    //
    // Indices of radial dimension definition points in 
    // the m_points[] array
    center_pt_index = 0, // location of + (usually at center of circle)
    arrow_pt_index  = 1, // arrow tip
    tail_pt_index   = 2, // end of radial dimension
    knee_pt_index   = 3, // number of m_points[] in a radial dim
    dim_pt_count    = 4, // number of m_points[] in a radial dim

    // Points calculated from values in m_points[]
    text_pivot_pt = 10000, // start/end of dimension text at tail
  };

  ON_OBSOLETE_V5_DimRadial();
  ~ON_OBSOLETE_V5_DimRadial() = default;
  ON_OBSOLETE_V5_DimRadial(const ON_OBSOLETE_V5_DimRadial&) = default;
  ON_OBSOLETE_V5_DimRadial& operator=(const ON_OBSOLETE_V5_DimRadial&) = default;


  static ON_OBSOLETE_V5_DimRadial* CreateFromV6DimRadial(
      const class ON_DimRadial& V6_dim_radial,
      const class ON_3dmAnnotationContext* annotation_context,
      ON_OBSOLETE_V5_DimRadial* destination
    );

  static ON_OBSOLETE_V5_DimRadial* CreateFromV2RadialDimension(
    const class ON_OBSOLETE_V2_DimRadial& V2_radial_dimension,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V5_DimRadial* destination
  );

  // overrides virtual ON_Geometry::Transform()
  bool Transform( const ON_Xform& xform ) override;

  /*
  Description:
    Get the m_plane coordinates of the dimension point.
  Parameters:
    point_index - [in] One of the POINT_INDEX enum values
  Returns:
    2d point or ON_3dPoint::UnsetPoint if point_index or m_points[]
    array is not valid.
  */
  ON_2dPoint Dim2dPoint(
       int point_index
       ) const;

  /*
  Description:
    Get the m_plane coordinates of the dimension point.
  Parameters:
    point_index - [in] One of the POINT_INDEX enum values
  Returns:
    2d point or ON_3dPoint::UnsetPoint if point_index or m_points[]
    array is not valid.
  */
  ON_3dPoint Dim3dPoint(
       int point_index
       ) const;


  // overrides virual ON_Object::IsValid
  bool IsValid( ON_TextLog* text_log = nullptr ) const override;

  // overrides virual ON_Object::Write
  bool Write(ON_BinaryArchive&) const override;

  // overrides virual ON_Object::Read
  bool Read(ON_BinaryArchive&) override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  // virtual ON_Geometry GetTightBoundingBox override		
  bool GetTightBoundingBox( class ON_BoundingBox& tight_bbox, bool bGrowBox = false, const class ON_Xform* xform = nullptr ) const override;

  /*
    Description:
      Set the plane and definition points from WCS 3d input
    Parameters:
      center - [in] center of circle
      arrowtip - [in] 3d point on the circle at the dimension arrow tip
      xaxis - [in] x axis of the dimension's plane
      normal - [in] normal to the dimension's plane
      offset_distance - [in] distance from arrow tip to knee point
    Returns:
      @untitled table
      true     Success
      false    Failure
  */
  bool CreateFromPoints( 
          ON_3dPoint center, 
          ON_3dPoint arrowtip, 
          ON_3dVector xaxis, 
          ON_3dVector normal,
          double offset_distance
          );

  /*
  Description:
    Overrides virtual ON_OBSOLETE_V5_Annotation::NumericValue();
  Returns:
    If m_type is ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter, then the diameter
    is returned, otherwise the radius is returned.
  */
  double NumericValue() const override;

  /*
    Description:
      Get or set the DimStyle index in the dimstyle table for the dimension
    Parameters:
      [in] int  the new index (Set)
    Returns:
      int -  The current index (Get)
  */
  int StyleIndex() const;
  void SetStyleIndex( int);

  /*
    Description:
      static function to provide the default UserText string for the object
    Returns:
      const wchar_t* - the default string to use
  */
  static const wchar_t* DefaultDiameterText();
  static const wchar_t* DefaultRadiusText();

  bool CreateFromV2( 
      const class ON_OBSOLETE_V2_Annotation& v2_ann,
      const class ON_3dmAnnotationSettings& settings,
      int dimstyle_index
      );

  bool GetArrowHeadDirection( ON_2dVector& arrowhead_dir ) const;
  bool GetArrowHeadTip( ON_2dPoint& arrowhead_tip ) const;
};


//////////
// class ON_OBSOLETE_V5_DimAngular
class ON_OBSOLETE_V5_DimAngular : public ON_OBSOLETE_V5_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V5_DimAngular);

public:

  /*
    The annotation's dimstyle controls the position of TEXT,
    the size of the arrowheads, and the amount the ends of 
    linear dimension's extension lines extend beyond the 
    dimension lines.

    In the picture below, [n] means ON_OBSOLETE_V5_Annotation::m_points[n].

    [0] = if m_userpositionedtext=true, this is the center of text.
          If m_userpositionedtext=false, this point is not used and
          the center of the text is at the arc's midpoint.

    Always counter clockwise arc in m_plane with center = (0,0)
    [1] = a point somewhere on the line from the center through the start point.
          The distance from center to [1] can be any value.
    [2] = a point somewhere on the line from the center through the end point.
          The distance from center to [2] can be any value.
    [3] = a point on the interior of the arc.  The distance 
          from (0,0) to [3] is the radius of the arc.


                  /
                [2]
                /
               /         [0]TEXT
              /
             /    [3]
     -----(0,0)----------[1]---
           /
          /
         /

  */

  enum POINT_INDEX
  {
    // Do not change these enum values.  They are saved in files as the 
    // ON_COMPONENT_INDEX.m_index value.
    //
    // Indices of angular dimension definition points in 
    // the m_points[] array
    userpositionedtext_pt_index  = 0, // 
    start_pt_index = 1, // point on the start ray (not necessarily on arc)
    end_pt_index   = 2, // point on the end ray (not necessarily on arc)
    arc_pt_index   = 3, // point on the interior of dimension arc
    dim_pt_count   = 4, // number of m_points[] in an angular dim

    // Points calculated from values in m_points[]
    text_pivot_pt = 10000, // center of dimension text
    arcstart_pt   = 10001,
    arcend_pt     = 10002,
    arcmid_pt     = 10003,
    arccenter_pt  = 10004, // center of circle arc lies on  
    extension0_pt = 10005, // point where first extension line starts
    extension1_pt = 10006  // point where second extension line starts
  };

public:
  ON_OBSOLETE_V5_DimAngular();
  ~ON_OBSOLETE_V5_DimAngular() = default;
  ON_OBSOLETE_V5_DimAngular(const ON_OBSOLETE_V5_DimAngular&) = default;
  ON_OBSOLETE_V5_DimAngular& operator=(const ON_OBSOLETE_V5_DimAngular&) = default;

  static ON_OBSOLETE_V5_DimAngular* CreateFromV6DimAngular(
    const class ON_DimAngular& V6_dim_angular,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V5_DimAngular* destination
  );

  static ON_OBSOLETE_V5_DimAngular* CreateFromV2AngularDimension( 
    const class ON_OBSOLETE_V2_DimAngular& V2_angular_dimension,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V5_DimAngular* destination
  );


  // overrides virtual ON_Geometry::Transform()
  bool Transform( const ON_Xform& xform ) override;

  /*
  Description:
    Get the m_plane coordinates of the dimension point.
  Parameters:
    point_index - [in] One of the POINT_INDEX enum values
  Returns:
    2d point or ON_3dPoint::UnsetPoint if point_index or m_points[]
    array is not valid.
  */
  ON_2dPoint Dim2dPoint(
       int point_index
       ) const;

  /*
  Description:
    Get the m_plane coordinates of the dimension point.
  Parameters:
    point_index - [in] One of the POINT_INDEX enum values
  Returns:
    2d point or ON_3dPoint::UnsetPoint if point_index or m_points[]
    array is not valid.
  */
  ON_3dPoint Dim3dPoint(
       int point_index
       ) const;


  // overrides virual ON_Object::IsValid
  bool IsValid( ON_TextLog* text_log = nullptr ) const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  // virtual ON_Geometry GetTightBoundingBox override		
  bool GetTightBoundingBox( class ON_BoundingBox& tight_bbox, bool bGrowBox = false, const class ON_Xform* xform = nullptr ) const override;

  /*
    Description:
      Read from or write to a file
    Returns:
      @untitled Table
      true     Success
      false    Failure
  */
  bool Write( ON_BinaryArchive& file ) const override;
  bool Read( ON_BinaryArchive& file ) override;

  /*
    Description:
      Set the plane and definition points from 3d points
      in world coordinates.
    Parameters:
      apex - [in] 3d apex of the dimension
                  (center of arc)
      p0 - [in] 3d point on first line
      p1 - [in] 3d point on second line
      arcpt - [in] 3d point on dimension arc 
                   (determines radius of arc)
      Normal - [in] normal of the plane on which to make the dimension
                    (must be perpendicular to p0-apex and p1-apex) 
    Returns:
      @untitled table
      true     Success
      false    Failure
  */
  bool CreateFromPoints( 
    const ON_3dPoint& apex, 
    const ON_3dPoint& p0, 
    const ON_3dPoint& p1, 
    ON_3dPoint& arcpt, 
    ON_3dVector& Normal
    );

  /*
    Description:
      Set the plane and definition points from a 3d arc.
    Parameters:
      arc - [in]
    Returns:
      @untitled table
      true     Success
      false    Failure
  */
  bool CreateFromArc( 
    const ON_Arc& arc
    );

  bool GetArc( ON_Arc& arc ) const;

  bool GetExtensionLines(ON_Line extensions[2]) const;

  // Set or get the measured angle in radians
  void SetAngle( double angle);
  double Angle() const;
  void SetRadius( double radius);
  double Radius() const;

  /*
  Description:
    Overrides virtual ON_OBSOLETE_V5_Annotation::NumericValue();
  Returns:
    Angle in degrees
  */
  double NumericValue() const override;

  /*
    Description:
      Get or set the DimStyle index in the dimstyle table for the dimension
    Parameters:
      [in] int  the new index (Set)
    Returns:
      int -  The current index (Get)
  */
  int StyleIndex() const;
  void SetStyleIndex( int);

  /*
    Description:
      static function to provide the default UserText string for the object
    Returns:
      const wchar_t* - the default string to use
  */
  static const wchar_t* DefaultText();

  double m_angle = 0.0;      // angle being dimensioned
  double m_radius = 1.0;     // radius for dimension arc

  /*
  Description:
    Get the annotation plane angles of the dimension arc.
  Parameters:
    gdi_text_rect - [in] Windows rect (left < right, top < bottom)
       that bounds text.
    gdi_height_of_I - [in] 
       Height of an I in the text.
    gdi_to_world - [in] 
       transform returned by ON_OBSOLETE_V5_Annotation::GetTextXform().
    dimstyle - [in]
      dimscale - [in]
    vp - [in]
    a - [out]
      angles at the ends of the arc segment(s) and the arrow tips
    bInside - [out] true if arrowheads go inside, false if they go outside
  Returns:
    number of arc segments to draw
    0: the input or class is not valid
    1: A single arc from a[0] to a[1] with arrow heads at a[4] & a[5].
    2: Two arcs from a[0] to a[1] & from a[2] to a[3].
       Arrowheads are at a[4] & a[5].
  */
  int GetDimensionArcSegments(
      ON_OBSOLETE_V5_RECT gdi_text_rect,
      int gdi_height_of_I,
      ON_Xform gdi_to_world,
      const ON_DimStyle& dimstyle,
      double dimscale,
      const ON_Viewport* vp,
      double a[6],
      bool& bInside
      ) const;

  
  /*
  Description:
    Get distance from dimension apex to extension line offset points
  Parameters:
    index - [in]  which distance to get
  Returns:
    Distance to offset point [index]
  */
  double DimpointOffset(
    int index) const;

  /*
  Description:
    Set distance from dimension apex to extension line offset points
  Parameters:
    index  - [in]  which distance to set
    offset - [in] Value to set
  */
  void SetDimpointOffset(
    int index, 
    double offset);
};


/*
  class ON_OBSOLETE_V5_DimLinear

  Description:
    Override od ON_OBSOLETE_V5_Annotation to provide linear dimensions
*/
class ON_OBSOLETE_V5_DimOrdinate : public ON_OBSOLETE_V5_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V5_DimOrdinate);

public:

  /*
    In the picture below, [n] means ON_OBSOLETE_V5_Annotation::m_points[n].

    Measures in X direction

                       [1]
                        |
                        |
                        |
                        |
                        |
                       [0]
       +
 [plane origin]                                      [plane origin]
                                                           +

      or - Measures in Y direction                                                   *---[1]       
                                                                                    /
                                                                                   /
                   [0]--------------------[1]                   [0]---------------*


                                                                              * = calculated, not stored


       +     
 [plane origin]


      The reference point of for the dimension is at the entity plane origin
      The "x" and "y" coordinates of [1] can be any value.
      The "x" and "y" coordinates of [2] can be any value.
      If Direction is "x", the dimension measures along the "x" axis
      If Direction is "y", the dimension measures along the "y" axis
      If Direction is "x" and [1][x] <> [0][x], an offset segment is drawn
      If Direction is "y" and [1][y] <> [0][y], an offset segment is drawn
      The dimension lines are always drawn in the X or Y directions of the entity plane
      The distance represented by the dimension is measured from the 
        plane origin to point [0], parallel to the appropriate axis.
      The points of the offset segment are calculated rather than stored
  */

  enum POINT_INDEX
  {
    // Do not change these enum values.  They are saved in files as the 
    // ON_COMPONENT_INDEX.m_index value.
    //
    // Indices of linear dimension definition points in 
    // the m_points[] array
    definition_pt_index    = 0, // First end of the dimension line
    leader_end_pt_index    = 1, // Other end of the leader (near the text)
    dim_pt_count           = 2, // Number of m_points[] in an ordinate dim

    // Points calculated from values in m_points[]
    text_pivot_pt = 10000, // Center of dimension text
    offset_pt_0   = 10001, // First offset point  (nearest text)
    offset_pt_1   = 10002  // Second offset point
  };

  enum DIRECTION
  {
    x = 0,  // measures horizontally
    y = 1,  // measures vertically
  };

  ON_OBSOLETE_V5_DimOrdinate();
  ~ON_OBSOLETE_V5_DimOrdinate();

  static ON_OBSOLETE_V5_DimOrdinate* CreateFromV6DimOrdinate(
    const class ON_DimOrdinate& V6_dim_ordinate,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V5_DimOrdinate* destination
    );


  // overrides virtual ON_Geometry::Transform()
  bool Transform( const ON_Xform& xform ) override;

  /*
  Description:
    Get the m_plane coordinates of the dimension point.
  Parameters:
    point_index - [in] One of the POINT_INDEX enum values
    default_offset [in] - kink offset to use if m_kink_offset_0
                          or m_kink_offset_1 are ON_UNSET_VALUE
  Returns:
    2d point or ON_3dPoint::UnsetPoint if point_index or m_points[]
    array is not valid.
  */
  ON_2dPoint Dim2dPoint(
       int point_index,
       double default_offset = 1.0
       ) const;

  /*
  Description:
    Get the m_plane coordinates of the dimension point.
  Parameters:
    point_index - [in] One of the POINT_INDEX enum values
    default_offset [in] - kink offset to use if m_kink_offset_0
                          or m_kink_offset_1 are ON_UNSET_VALUE
  Returns:
    2d point or ON_3dPoint::UnsetPoint if point_index or m_points[]
    array is not valid.
  */
  ON_3dPoint Dim3dPoint(
       int point_index,
       double default_offset = 1.0
       ) const;

  // overrides virual ON_Object::IsValid
  bool IsValid( ON_TextLog* text_log = nullptr ) const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  // virtual ON_Geometry GetTightBoundingBox override		
  bool GetTightBoundingBox( class ON_BoundingBox& tight_bbox, bool bGrowBox = false, const class ON_Xform* xform = nullptr ) const override;

  /*
    Description:
      Read from or write to a file
    Returns:
      @untitled Table
      true     Success
      false    Failure
  */
  bool Write( ON_BinaryArchive& file ) const override;
  bool Read( ON_BinaryArchive& file ) override;

  /*
  Description:
    Overrides virtual ON_OBSOLETE_V5_Annotation::NumericValue();
  Returns:
    If Direction is 'X', x coordinate of point[1]
    If Direction is 'Y', y coordinate of point[1]
  */
  double NumericValue() const override;

  /*
    Description:
      Get or set the DimStyle index in the dimstyle table for the dimension
    Parameters:
      [in] int  the new index (Set)
    Returns:
      int -  The current index (Get)
  */
  int StyleIndex() const;
  void SetStyleIndex( int);

  /*
    Description:
      Gets the direction ( X or Y) that the ordinate dimension measures
      based on the relative location of the defining point and leader endpoint
    Returns:
      0: measures parallel to the entity plane x axis
      1: measures parallel to the entity plane y axis
    Remarks:
      This does not consider the dimension's explicit Direction setting 
  */
  int ImpliedDirection() const;

  /*
    Description:
      Gets or sets the direction ( X or Y) that the ordinate dimension measures
    Returns:
     -1: direction determined by dim point and leader point
      0: measures parallel to the entity plane x axis
      1: measures parallel to the entity plane y axis
  */
  int Direction() const;
  void SetDirection( int direction);

  /*
    Description:
      Get the height of the text in this dimension
      by asking the dimension's dimstyle
    Returns:
      double Height of the text
    Remarks:
      Height is in model units
  double Height() const;
  */

  /*
    Description:
      static function to provide the default UserText string for the object
    Returns:
      const wchar_t* - the default string to use
  */
  static const wchar_t* DefaultText();

  /*
    Description:
      Returns or sets the offset distance parallel to the dimension 
      line direction of from the text end of the dimension line to 
      the offset point 
      If the offset point hasn't been explicitly defined, returns 
      ON_UNSET_VALUE and a default should be used to find the point.
    Parameters:
      index [in] - which offset distance to return 
                   (0 is closer to the text)
      offset [in] - the offset distance to set
  */
  double KinkOffset( int index) const;
  void SetKinkOffset( int index, double offset);


  int m_direction;   // -1 == underermined
                     //  0 == x direction
                     //  1 == y direction

  // kink offsets added 2-4-06 - LW
  double m_kink_offset_0;  // from leader_end_point to first break point
  double m_kink_offset_1;  // from first break point to second break point

  /*
    Description:
      Calculates the 2d point locations of the dimension line kinks

    Parameters:
      p0, p1 [in] - End points of the dimension line
      direction [in] - orientation of the dimension
      default_offset [in] - Use this if offsets are ON_UNSET_VALUE
      k0, k1 [out] - The kink points
    Remarks:
      The offsets must be set to the right values before calling this, or
      If they are ON_UNSET_VALUE, they will be set to the defaults
  */
  void CalcKinkPoints( ON_2dPoint p0, ON_2dPoint p1, 
                       int direction, double default_offset,
                       ON_2dPoint& k0, ON_2dPoint& k1) const;

};


//////////
// class ON_OBSOLETE_V5_TextObject
class ON_OBSOLETE_V5_TextObject : public ON_OBSOLETE_V5_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V5_TextObject);

public:
  ON_OBSOLETE_V5_TextObject();
  ~ON_OBSOLETE_V5_TextObject();

  /*
  Description:
    Create a V6 text object from a V5 text object. 
    The function is used when writing V5 files.
  Parameters:
    v6_text_object -[in]
    dimstyle - [in]
      Dimstyle referenced by v6_text_object or nullptr if not available.
    destination - [in]
      If destination is not nullptr, then the V5 text object is constructed
      in destination. If destination is nullptr, then the new V5 text object
      is allocated with a call to new ON_OBSOLETE_V5_TextObject().
  */
  static ON_OBSOLETE_V5_TextObject* CreateFromV6TextObject(
    const class ON_Text& V6_text_object,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V5_TextObject* destination
  );

  static ON_OBSOLETE_V5_TextObject* CreateFromV2TextObject(
    const class ON_OBSOLETE_V2_TextObject& V2_text_object,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V5_TextObject* destination
  );

  // overrides virual ON_Object::IsValid
  // Text entities with strings that contain no "printable" characters
  // are considered to be NOT valid.
  bool IsValid( ON_TextLog* text_log = nullptr ) const override;

  // overrides virual ON_Object::Write
  bool Write(ON_BinaryArchive&) const override;

  // overrides virual ON_Object::Read
  bool Read(ON_BinaryArchive&) override;

  // overrides virtual ON_Geometry::Transform()
  bool Transform( const ON_Xform& xform ) override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  // virtual ON_Geometry GetTightBoundingBox override		
  bool GetTightBoundingBox( class ON_BoundingBox& tight_bbox, bool bGrowBox = false, const class ON_Xform* xform = nullptr ) const override;

  void SetJustification( unsigned int justification) override;

  unsigned int Justification() const override;

  // Determines whether or not to draw a Text Mask
  bool DrawTextMask() const;
  void SetDrawTextMask(bool bDraw);

  // Determines where to get the color to draw a Text Mask
  // 0: Use background color of the viewport.  Initially, gradient backgrounds will not be supported
  // 1: Use the ON_Color returned by MaskColor()
  int MaskColorSource() const;
  void SetMaskColorSource(int source);

  ON_Color MaskColor() const;  // Only works right if MaskColorSource returns 1.
                               // Does not return viewport background color
  void SetMaskColor(ON_Color color);

  // Offset for the border around text to the rectangle used to draw the mask
  // This number * CRhinoAnnotation::TextHeight() for the text is the offset 
  // on each side of the tight rectangle around the text characters to the mask rectangle.
  double MaskOffsetFactor() const;
  void SetMaskOffsetFactor(double offset);

  // Scale annotation according to detail scale factor in paperspace
  // or by 1.0 in paperspace and not in a detail
  // Otherwise, dimscale or text scale is used
  bool AnnotativeScaling() const;
  void SetAnnotativeScaling(bool b);
};

//////////
// class ON_OBSOLETE_V5_Leader
class ON_OBSOLETE_V5_Leader : public ON_OBSOLETE_V5_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V5_Leader);

public:

  /*
    The annotation's dimstyle controls the position of TEXT,
    the size of the arrowheads, and the amount the ends of 
    linear dimension's extension lines extend beyond the 
    dimension lines.

    Leaders:

      Polyline with N=m_points.Count() points (N >= 2).

                      [N-2] ----- [N-1] TEXT
                        /         (tail)
                       /
                      /
            [1]------[2]
            /
           /
          /
        [0] (arrow)

      Leaders ignore the m_userpositionedtext setting.  If the
      default leader text handling is not adequate, then use
      a leader with no text and an ON_OBSOLETE_V5_TextObject.
  */

  enum POINT_INDEX
  {
    // Do not change these enum values.  They are saved in files as the 
    // ON_COMPONENT_INDEX.m_index value.
    //
    // Indices of leader definition points in 
    // the m_points[] array
    arrow_pt_index  = 0, // arrow tip

    // Points calculated from values in m_points[]
    text_pivot_pt = 10000, // start/end of dimension text at tail
    tail_pt       = 10001
  };

  // Constructors
  ON_OBSOLETE_V5_Leader();
  ~ON_OBSOLETE_V5_Leader();
  // C++ automatically provides the correct copy constructor and operator= .
  //ON_OBSOLETE_V5_Leader(const ON_OBSOLETE_V5_Leader&);
  //ON_OBSOLETE_V5_Leader& operator=(const ON_OBSOLETE_V5_Leader&);

  /*
  Description:
    Create a V5 leader from a V6 leader. 
    The function is used when writing V5 files.
  Parameters:
    v6_leader -[in]
    dimstyle - [in]
      Dimstyle referenced by v6_leader or nullptr if not available.
    destination - [in]
      If destination is not nullptr, then the V5 leader is constructed
      in destination. If destination is nullptr, then the new V5 leader
      is allocated with a call to new ON_V5_Leader().
  */
  static ON_OBSOLETE_V5_Leader* CreateFromV6Leader(
    const class ON_Leader& V6_leader,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V5_Leader* destination
  );


  static ON_OBSOLETE_V5_Leader* CreateFromV2Leader(
    const class ON_OBSOLETE_V2_Leader& V2_leader,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V5_Leader* destination
  );

  // overrides virtual ON_Geometry::Transform()
  bool Transform( const ON_Xform& xform ) override;

  /*
  Description:
    Get the m_plane coordinates of the dimension point.
  Parameters:
    point_index - [in] One of the POINT_INDEX enum values
  Returns:
    2d point or ON_3dPoint::UnsetPoint if point_index or m_points[]
    array is not valid.
  */
  ON_2dPoint Dim2dPoint(
       int point_index
       ) const;

  /*
  Description:
    Get the m_plane coordinates of the dimension point.
  Parameters:
    point_index - [in] One of the POINT_INDEX enum values
  Returns:
    2d point or ON_3dPoint::UnsetPoint if point_index or m_points[]
    array is not valid.
  */
  ON_3dPoint Dim3dPoint(
       int point_index
       ) const;

  // overrides virual ON_Object::IsValid
  bool IsValid( ON_TextLog* text_log = nullptr ) const override;

  // overrides virual ON_Object::Write
  bool Write(ON_BinaryArchive&) const override;

  // overrides virual ON_Object::Read
  bool Read(ON_BinaryArchive&) override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  // virtual ON_Geometry GetTightBoundingBox override		
  bool GetTightBoundingBox( class ON_BoundingBox& tight_bbox, bool bGrowBox = false, const class ON_Xform* xform = nullptr ) const override;

  /*
    Description:
      Add or delete points to the leader
    Parameters:
      index [in] the point to delete
      point [in]  The point to add
    Returns:
      @untitled table
      true     Success
      False    Failure
  */
  void AddPoint( const ON_2dPoint& point);
  bool RemovePoint( int index = -1);

// April 22, 2010 Lowell - Added to support right justified text on left pointing leader tails rr64292
  bool GetTextDirection( ON_2dVector& text_dir ) const;
  bool GetArrowHeadDirection( ON_2dVector& arrowhead_dir ) const;
  bool GetArrowHeadTip( ON_2dPoint& arrowhead_tip ) const;
};

#endif

#endif
