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

#ifndef OPENNURBS_HATCH_H_INCLUDED
#define OPENNURBS_HATCH_H_INCLUDED

/*
  class ON_HatchLoop
  /////////////////////////////////////////////////////////////////
  Represents a 3d boundary loop curve
*/
class ON_CLASS ON_HatchLoop
{
public:
#if defined(OPENNURBS_EXPORTS) || defined(OPENNURBS_IMPORTS)
  // When the Microsoft CRT(s) is/are used, this is the best
  // way to prevent crashes that happen when a hatch loop is
  // allocated with new in one DLL and deallocated with
  // delete in another DLL.

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

  enum eLoopType
  {
    ltOuter = 0,
    ltInner = 1,
  };

  ON_HatchLoop();
  ON_HatchLoop( ON_Curve* pCurve2d, eLoopType type = ltOuter);
  ON_HatchLoop( const ON_HatchLoop& src);
  ~ON_HatchLoop();

  ON_HatchLoop& operator=( const ON_HatchLoop& src);

  bool IsValid( ON_TextLog* text_log = nullptr ) const;
  void Dump( ON_TextLog& ) const; // for debugging
  bool Write( ON_BinaryArchive&) const;
  bool Read( ON_BinaryArchive&);

  // Interface
  /////////////////////////////////////////////////////////////////

  /*
  Description:
    Get a closed 2d curve boundary loop
  Parameters:
  Return:
    Pointer to loop's 2d curve
  */
  const ON_Curve* Curve() const;
 
  /*
  Description:
    Specify the 2d loop curve in the hatch's plane coordinates
  Parameters:
    curve - [in] 2d input curve
  Return:
    true: success, false, curve couldn't be duplicated
  Remarks:
    The curve is copied
  */
  bool SetCurve( const ON_Curve& curve);

  /*
  Description:
    Get the type flag of the loop
  Returns:
    eLoopType::ltInner or eLoopType::ltOuter
  */
  eLoopType Type() const;

  /*
  Description:
    Specify the type flag of the loop
  Parameters:
    type - [in] ltInner or ltOuter
  */
  void SetType( eLoopType type);

protected:
  friend class ON_Hatch;
  eLoopType m_type;         // loop type flag - inner or outer
  ON_Curve* m_p2dCurve;     // 2d closed curve bounding the hatch
                            // This is really a 3d curve with z coordinates = 0
};


/*
  class ON_HatchLine
  /////////////////////////////////////////////////////////////////
  Represents one line of a hatch pattern
  Similar to AutoCAD's .pat file definition
  ON_HatchLine's are used by ON_HatchPattern
    to specify the dashes and offset patterns of the lines.

  Each line has the following information:
  Angle is the direction of the line CCW from the x axis
  The first line origin is at base
  Each line repetition is offset by offset from the previous line
    offset.x is parallel to the line and 
    offset.y is perpendicular to the line
  The base and offset values are rotated by the line's angle to 
    produce a location in the hatch pattern's coordinate system
  There can be gaps and dashes specified for drawing the line

  If there are no dashes, the line is solid
  Negative length dashes are gaps
  Positive length dashes are drawn as line segments
*/

class ON_CLASS ON_HatchLine
{
public:
  // Default constructor creates ON_HatchLine::SolidHorizontal
  ON_HatchLine() = default;
  ~ON_HatchLine() = default;
  ON_HatchLine(const ON_HatchLine&) = default;
  ON_HatchLine& operator=(const ON_HatchLine&) = default;

  static const ON_HatchLine Unset;           // angle = unset
  static const ON_HatchLine SolidHorizontal; // angle = 0
  static const ON_HatchLine SolidVertical;   // angle = pi/2

  static int Compare(
    const ON_HatchLine& a,
    const ON_HatchLine& b
    );

  ON_HatchLine( 
    double angle_in_radians, 
    ON_2dPoint base, 
    ON_2dVector offset,
    const ON_SimpleArray<double>& dashes
    );

  // constructs solid line
  ON_HatchLine( 
    double angle_in_radians
    );

  bool operator==( const ON_HatchLine&) const;
  bool operator!=( const ON_HatchLine&) const;

  bool IsValid( ON_TextLog* text_log = nullptr ) const;
  void Dump( ON_TextLog& ) const; // for debugging

public:
  bool Write( ON_BinaryArchive&) const;  // serialize definition to binary archive
  bool Read( ON_BinaryArchive&);  // restore definition from binary archive

private:
  bool WriteV5(ON_BinaryArchive&) const;  // serialize definition to binary archive
  bool ReadV5(ON_BinaryArchive&);  // restore definition from binary archive

public:
  /////////////////////////////////////////////////////////////////
  //
  // Interface
  //

  /*
  Description:
    Get angle of the hatch line.
    CCW from x-axis
  Parameters:
  Return:
    The angle in radians
  */
  double AngleRadians() const;

  double AngleDegrees() const;

  /*
  Description:
    Set angle of the hatch line.
    CCW from x-axis
  Parameters:
    angle - [in] angle in radians
  Return:
  */
  void SetAngleRadians( 
    double angle_in_radians
    );
  
  void SetAngleDegrees(
    double angle_in_degrees
    );

  /*
  Description:
    Get this line's 2d basepoint
  Parameters:
  Return:
    the base point
  */
  ON_2dPoint Base() const;
  /*
  Description:
    Set this line's 2d basepoint
  Parameters:
    base - [in] the basepoint
  Return:
  */
  void SetBase( const ON_2dPoint& base);
  
  /*
  Description:
    Get this line's 2d offset for line repetitions
    Offset().x is shift parallel to line
    Offset().y is spacing perpendicular to line
  Parameters:
  Return:
    the offset
  */
  ON_2dVector Offset() const;

  /*
  Description:
    Get this line's 2d offset for line repetitions
    Offset().x is shift parallel to line
    Offset().y is spacing perpendicular to line
  Parameters:
    offset - [in] the shift,spacing for repeated lines
  Return:
  */
  void SetOffset( const ON_2dVector& offset);

  /*
  Description:
    Get the number of gaps + dashes in the line
  Parameters:
  Return:
    number of dashes in the line
  */
  int DashCount() const;

  /*
  Description:
    Get the dash length at index
  Parameters:
    index - [in] the dash to get
  Return:
    the length of the dash ( gap if negative)
  */
  double Dash( int) const;

  /*
  Description:
    Add a dash to the pattern
  Parameters:
    dash - [in] length to append - < 0 for a gap
  */
  void AppendDash( double dash);

  /*
  Description:
    Specify a new dash array
  Parameters:
    dashes - [in] array of dash lengths
  */
  void SetDashes( const ON_SimpleArray<double>& dashes);

  const ON_SimpleArray<double>& Dashes() const;

  /*
  Description:
    Get the line's angle, base, offset and dashes 
    in one function call
  Parameters:
    angle_radians  - [out] angle in radians CCW from x-axis
    base   - [out] origin of the master line
    offset - [out] offset for line replications
    dashes - [out] the dash array for the line
  Return:
  */
  void GetLineData(
    double& angle_radians, 
    ON_2dPoint& base, 
    ON_2dVector& offset, 
    ON_SimpleArray<double>& dashes) const;

  /*
  Description:
    Get the total length of a pattern repeat
  Parameters:
  Return:
    Pattern length
  */
  double GetPatternLength() const;

private:
  double m_angle_radians = 0.0;
  ON_2dPoint m_base = ON_2dPoint::Origin;
  ON_2dVector m_offset = ON_2dVector::ZeroVector;
  ON_SimpleArray< double> m_dashes;
};




#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_HatchLoop*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_HatchLine>;
#endif


/*
  class ON_HatchPattern
  /////////////////////////////////////////////////////////////////
  Fill definition for a hatch

  The hatch  will be one of 
    ON_Hatch::ON_HatchPattern::HatchFillType::Lines     - pat file style definition
    ON_Hatch::ON_HatchPattern::HatchFillType::Gradient  - uses a color function
    ON_Hatch::ON_HatchPattern::HatchFillType::Solid     - uses entity color

*/
class ON_CLASS ON_HatchPattern : public ON_ModelComponent
{
  ON_OBJECT_DECLARE( ON_HatchPattern);

public:
  ON_HatchPattern() ON_NOEXCEPT;
  ~ON_HatchPattern() = default;
  ON_HatchPattern(const ON_HatchPattern&);
  ON_HatchPattern& operator=(const ON_HatchPattern&) = default;

public:
  static const ON_HatchPattern Unset;   // index = ON_UNSET_INT_INDEX, id = nil
  static const ON_HatchPattern Solid; // index = -1, id set, unique and persistent
  static const ON_HatchPattern Hatch1;    // index = -2, id set, unique and persistent
  static const ON_HatchPattern Hatch2;    // index = -3, id set, unique and persistent
  static const ON_HatchPattern Hatch3;    // index = -4, id set, unique and persistent
  static const ON_HatchPattern HatchDash; // index = -5, id set, unique and persistent
  static const ON_HatchPattern Grid;      // index = -6, id set, unique and persistent
  static const ON_HatchPattern Grid60;    // index = -7, id set, unique and persistent
  static const ON_HatchPattern Plus;      // index = -8, id set, unique and persistent
  static const ON_HatchPattern Squares;   // index = -9, id set, unique and persistent

  // compare everything except Index() value.
  static int Compare( 
    const ON_HatchPattern& a,
    const ON_HatchPattern& b
    );

  // Compare all settings (type, lines, ...) that effect the appearance.
  // Ignore Index(), Id(), Name()
  static int CompareAppearance( 
    const ON_HatchPattern& a,
    const ON_HatchPattern& b
    );
  
public:
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
  static const ON_HatchPattern* FromModelComponentRef(
    const class ON_ModelComponentReference& model_component_reference,
    const ON_HatchPattern* none_return_value
    );

public:

  enum class HatchFillType : unsigned int
  {
    Solid    = 0,  // uses entity color
    Lines    = 1,  // pat file definition
    //Gradient = 2,  // uses a fill color function
  };

  static ON_HatchPattern::HatchFillType HatchFillTypeFromUnsigned(
    unsigned hatch_fill_type_as_unsigned
    );


  /////////////////////////////////////////////////////////////////
  // ON_Object overrides
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  void Dump( ON_TextLog& ) const override; // for debugging
  bool Write( ON_BinaryArchive&) const override;
  bool Read( ON_BinaryArchive&) override;
private:
  bool WriteV5(ON_BinaryArchive&) const;
  bool ReadV5(ON_BinaryArchive&);
public:

  //////////////////////////////////////////////////////////////////////
  // Interface

  /*
  Description:
    Return the pattern's fill type
  Parameters:
  */
  ON_HatchPattern::HatchFillType FillType() const;

  /*
  Description:
    Set the pattern's fill type
  Parameters:
    type - [in] the new filltype
  */
  void SetFillType(
    ON_HatchPattern::HatchFillType fill_type
    );

  /*
  Description:
    Set the name of the pattern
  Parameters:
    pDescription - [in] the new description
  Returns:
  */
  void SetDescription( 
    const wchar_t* pDescription
    );
  
  /*
  Description:
    Get a short description of the pattern
  Parameters:
    string - [out] The string is returned here
  */
  const ON_wString& Description() const;


  // Interface functions for line hatches
  /////////////////////////////////////////////////////////////////
  /*
  Description:
    Get the number of ON_HatchLines in the pattern
  Parameters:
  Return:
    number of lines
  */
  int HatchLineCount() const;

  /*
  Description:
    Add an ON_HatchLine to the pattern
  Parameters:
    line - [in] the line to add
  Return:
    >= 0 index of the new line
    -1 on failure
  */
  int AddHatchLine( 
    const ON_HatchLine& line
    );

  /*
  Description:
    Get the ON_HatchLine at index
  Parameters:
    index - [in] Index of the line to get
  Return:
    the hatch line
    nullptr if index is out of range
  */
  const ON_HatchLine* HatchLine(
    int index
    ) const;

  /*
  Description:
    Remove a hatch line from the pattern
  Parameters:
    index - [in] Index of the line to remove
  Return:
    true - success
    false - index out of range
  */
  bool RemoveHatchLine(
    int index
    );

  /*
  Description:
    Remove all of the hatch line from the pattern
  Parameters:

  Return:
    true - success
    false - index out of range
  */
  void RemoveAllHatchLines();

  /*
  Description:
    Set all of the hatch lines at once. 
    Existing hatchlines are deleted.
  Parameters:
    lines - [in] Array of lines to add.  Lines are copied
  Return:
    number of lines added
  */
  int SetHatchLines(
    const ON_ClassArray<ON_HatchLine>& lines
    );

  int SetHatchLines(
    size_t count,
    const ON_HatchLine* lines
    );

  const ON_ClassArray<ON_HatchLine>& HatchLines() const;

private:
  ON_HatchPattern::HatchFillType m_type = ON_HatchPattern::HatchFillType::Solid;
  
  ON_wString m_description = ON_wString::EmptyString;  // String description of the pattern

  // Represents a collection of ON_HatchLine's to make a complete pattern
  // This is the definition of a hatch pattern.
  // Simple solid line hatches with fixed angle and spacing are also 
  // represented with this type of hatch
  ON_ClassArray<ON_HatchLine> m_lines; // used by line hatches
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_HatchPattern*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<const ON_HatchPattern*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ObjectArray<ON_HatchPattern>;
#endif

/*
  class ON_Hatch
  /////////////////////////////////////////////////////////////////
  Represents a hatch in planar boundary loop or loops 
  This is a 2d entity with a plane defining a local coordinate system
  The loops, patterns, angles, etc are all in this local coordinate system

  The ON_Hatch object manages the plane and loop array
  Fill definitions are in the ON_HatchPattern or class derived from ON_HatchPattern
  ON_Hatch has an index to get the pattern definition from the pattern table

*/
class ON_CLASS ON_Hatch : public ON_Geometry
{
  ON_OBJECT_DECLARE( ON_Hatch);

public:
  // Default constructor
  ON_Hatch() = default;
  ~ON_Hatch();
  ON_Hatch( const ON_Hatch&);
  ON_Hatch& operator=(const ON_Hatch&);

  static ON_Hatch* HatchFromBrep(
    ON_Hatch* use_this_hatch,
    const ON_Brep* brep,
    int face_index,
    int pattern_index,
    double pattern_rotation_radians, 
    double pattern_scale,
    ON_3dPoint basepoint);

private:
  void Internal_Destroy();
  void Internal_CopyFrom(const ON_Hatch& src);
public:

  virtual ON_Hatch* DuplicateHatch() const;

  // ON_Object overrides
  /////////////////////////////////////////////////////////////////
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  void Dump( ON_TextLog& ) const override;
  bool Write( ON_BinaryArchive&) const override;
  bool Read( ON_BinaryArchive&) override;
  ON::object_type ObjectType() const override;

  // ON_Geometry overrides
  /////////////////////////////////////////////////////////////////
  /*
    Returns the geometric dimension of the object ( usually 3)
  */
  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  // virtual ON_Geometry GetTightBoundingBox override		
  bool GetTightBoundingBox( class ON_BoundingBox& tight_bbox, bool bGrowBox = false, const class ON_Xform* xform = nullptr ) const override;

  /*
    Description:
      Transform the object by a 4x4 xform matrix

    Parameters:
      [in] xform  - An ON_Xform with the transformation information
    Returns:
      true = Success
      false = Failure
    Remarks:
      The object has been transformed when the function returns.
  */
  bool Transform( const ON_Xform&) override;

  /*
    Description:
      Scales the hatch's pattern by a 4x4 xform matrix
    Parameters:
      [in] xform  - An ON_Xform with the transformation information
    Returns:
      true = Success
      false = Failure
    Remarks:
      The hatch pattern scale is multiplied by the change in length of a
      unit vector in the hatch plane x direction when that vector is
      scaled by the input xform
  */
  bool ScalePattern(ON_Xform xform);

  /*
  Description:
  If possible, BrepForm() creates a brep form of the
  ON_Geometry.
  Parameters:
  brep - [in] if not nullptr, brep is used to store the brep
  form of the geometry.
  Result:
  Returns a pointer to on ON_Brep or nullptr.  If the brep
  parameter is not nullptr, then brep is returned if the
  geometry has a brep form and nullptr is returned if the
  geometry does not have a brep form.
  Remarks:
  The caller is responsible for managing the brep memory.
  See Also
  ON_Geometry::HasBrepForm
  */
  class ON_Brep* BrepForm(
      class ON_Brep* brep = nullptr
    ) const override; 



  // Interface
  /////////////////////////////////////////////////////////////////

  /*
  Description:
    Create a hatch from input geometry and parameters
  Parameters:
    plane [I] - ON_Plane to make the hatch on
    loops [I] - Array of boundary loops with the outer one first
    pattern_index [I] - Index into the hatch table
    pattern_rotation [I] - ccw in radians about plane origin
    pattern_scale [I] - Scale factor for pattern definition
  Returns:
    true = success, false = failure
  */
  bool Create( const ON_Plane& plane,
               const ON_SimpleArray<const ON_Curve*> loops, 
               int pattern_index, 
               double pattern_rotation, 
               double pattern_scale);

  /*
  Description:
    Get the plane defining the hatch's coordinate system
  Parameters:
  Returns:
    the plane
  */
  const ON_Plane& Plane() const;

  /*
  Description:
    Set the plane defining the hatch's coordinate system
  Parameters:
    plane - [in] the plane to set
  Returns:
  */
  void SetPlane( const ON_Plane& plane);
  
  /*
  Description:
    Gets the rotation applied to the hatch pattern 
    when it is mapped to the hatch's plane
  Returns:
    The rotation in radians
  Remarks:
    The pattern is rotated counter-clockwise around
    the hatch's plane origin by this value
  */
  double PatternRotation() const;

/*
  Description:
    Sets the rotation applied to the hatch pattern 
    when it is mapped to the hatch's plane
  Parameters:
    rotation - [in] The rotation in radians
  Remarks:
    The pattern is rotated counter-clockwise around
    the hatch's plane origin by this value
  */
  void SetPatternRotation( double rotation);
  
  /*
  Description:
    Gets the scale applied to the hatch pattern 
    when it is mapped to the hatch's plane
  Returns:
    The scale
  Remarks:
    The pattern is scaled around
    the hatch's plane origin by this value
  */
  double PatternScale() const;

/*
  Description:
    Sets the scale applied to the hatch pattern 
    when it is mapped to the hatch's plane
  Parameters:
    scale - [in] The scale
  Remarks:
    The pattern is scaled around
    the hatch's plane origin by this value
  */
  void SetPatternScale( double scale);
  
  /*
  Description:
    Get the number of loops used by this hatch
  Parameters:
  Returns:
    the number of loops
  */
  int LoopCount() const;

  /*
  Description:
    Add a loop to the hatch
  Parameters:
    loop - [in] the loop to add. Memory management for the loop is managed
           by this class.
  Returns:
  */
  void AddLoop( ON_HatchLoop* loop);

  /*
  Description:
    Insert a loop to the hatch at the specified index
  Parameters:
    index - [in] zero based index of the position where insert the loop to.
    loop - [in] the loop to insert. Memory management for the loop is managed
                by this class on success.
  Returns:
    true if success
	  false if index is lower than 0 or greater than current loop count.
  */
  bool InsertLoop( int index,
                   ON_HatchLoop* loop);

  /*
  Description:
    Remove a loop in the hatch
  Parameters:
    loop - [in] zero based index of the loop to remove.
  Returns:
    true if success
  */
  bool RemoveLoop( int index);

  /*
  Description:
    Get the loop at index
  Parameters:
    index - [in] which loop to get
  Returns:
    pointer to loop at index
    nullptr if index is out of range
  */
  const ON_HatchLoop* Loop( int index) const;

  /*
  Description:
    Get the 3d curve corresponding to loop[index]
  Parameters:
    index - [in] which loop to get
  Returns:
    pointer to 3d curve of loop at index
    nullptr if index is out of range or curve can't be made
    Caller deletes the returned curve
  */
  ON_Curve* LoopCurve3d( int index) const;

  /*
  Description:
    Get the index of the hatch's pattern
  Parameters:
  Returns:
    index of the pattern
  */
  int PatternIndex() const;

/*
  Description:
    Set the index of the hatch's pattern
  Parameters:
    index - [in] pattern index to set
  Returns:
  */
  void SetPatternIndex( int index);

  // Basepoint functions added March 23, 2008 -LW
  /*
  Description:
    Set 2d Base point for hatch pattern alignment.
  Parameters:
    basepoint - 2d point in hatch's ECS
  */
  void SetBasePoint(ON_2dPoint basepoint);

  /*
  Description:
    Set 3d Base point for hatch pattern alignment.
  Parameters:
    point - 3d WCS point
  Remarks:
    Projects point to hatch's plane and sets 2d point
  */
  void SetBasePoint(ON_3dPoint point);

  /*
  Description:
    Return 3d WCS point that lies on hatch's plane used for pattern origin.
  */
  ON_3dPoint BasePoint() const;

  /*
  Description:
    Return 2d ECS point used for pattern origin.
  */
  ON_2dPoint BasePoint2d() const;

  /*
  Function added June 12 2008 LW
  Description:
    Remove all of the loops on the hatch and add the curves in 'loops' as new loops
  Parameters:
    loops - [in] An array of pointers to 2d or 3d curves
                 If the curves are 2d, add them to the hatch directly
                 If they are 3d, project them to the hatch's plane first
  Returns:
    true  - success
    false - no loops in input array or an error adding them
  */
  bool ReplaceLoops(ON_SimpleArray<const ON_Curve*>& loops);

  /*
  Description:
    Returns gradient fill type for this hatch
  */
  ON_GradientType GetGradientType() const;
  
  /*
  Description:
    Set the gradient fill type for this hatch
  */
  void SetGradientType(ON_GradientType gt);

  /*
  Description:
    Get list of color stops used for gradient drawing.
  */
  void GetGradientColors(ON_SimpleArray<ON_ColorStop>& colors) const;

  /*
  Description:
    Set list of color stops used for gradient drawing.
  */
  bool SetGradientColors(const ON_SimpleArray<ON_ColorStop>& colors);

  /*
  Description:
    Get gradient repeat factor for gradient drawing.
    > 1 repeat reflected number of times between start and end point
    < -1 repeat wrap number of times between start and end point
    any other value does not affect repeat on a gradient
  */
  double GetGradientRepeat() const;
  
  /*
  Description:
    Set gradient repeat factor for gradient drawing
    > 1 repeat reflected number of times between start and end point
    < -1 repeat wrap number of times between start and end point
    any other value does not affect repeat on a gradient
  Returns:
    True if the repeat factor was successfully set
  */
  bool SetGradientRepeat(double repeat);

  /*
  Description:
    Get the start and end points for gradient drawing in 3d
  */
  void GetGradientEndPoints(ON_3dPoint& startPoint, ON_3dPoint& endPoint) const;

  /*
  Description:
    Set the start and end points for gradient drawing
  */
  bool SetGradientEndPoints(ON_3dPoint startpoint, ON_3dPoint endPoint);

private:
  ON_Plane m_plane;
  double m_pattern_scale = 1.0;
  double m_pattern_rotation = 0.0;
  ON_2dPoint m_basepoint = ON_2dPoint::Origin;
  ON_SimpleArray<ON_HatchLoop*> m_loops;
  int m_pattern_index = -1;
};

//Part of a boundary. An element has a curve subdomain and a flag to say 
//whether that piece of curve should be reversed
class ON_CLASS ON_CurveRegionBoundaryElement
{
public :
  ON_CurveRegionBoundaryElement();
  ON_CurveRegionBoundaryElement(const ON_CurveRegionBoundaryElement& src);
  ~ON_CurveRegionBoundaryElement();
  ON_CurveRegionBoundaryElement& operator=(const ON_CurveRegionBoundaryElement& src);
  int m_curve_id;
  ON_Interval m_subdomain;
  bool m_bReversed;
};

//A list of curve subdomains that form a closed boundary with active space on the left.
typedef ON_ClassArray<ON_CurveRegionBoundaryElement> ON_CurveRegionBoundary;

//A list of region boundaries that bound a single connected region of the plane.
//The first boundary is always the outer boundary.
typedef ON_ClassArray<ON_CurveRegionBoundary> ON_CurveRegion;


#endif
