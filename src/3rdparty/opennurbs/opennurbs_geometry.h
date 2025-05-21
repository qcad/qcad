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

////////////////////////////////////////////////////////////////
//
//   virtual base class for all geometric objects
//
////////////////////////////////////////////////////////////////

#if !defined(OPENNURBS_GEOMETRY_INC_)
#define OPENNURBS_GEOMETRY_INC_

class ON_Brep;

////////////////////////////////////////////////////////////////

// Description:
//   Base class for all geometry classes that must
//   provide runtime class id.  Provides interface
//   for common geometric operations like finding bounding
//   boxes and transforming.
//
class ON_CLASS ON_Geometry : public ON_Object
{
  // Any object derived from ON_Geometry should have a
  //   ON_OBJECT_DECLARE(ON_...);
  // as the last line of its class definition and a
  //   ON_OBJECT_IMPLEMENT( ON_..., ON_baseclass );
  // in a .cpp file.
  //
  // See the definition of ON_Object for details.
  ON_OBJECT_DECLARE(ON_Geometry);

public:
  const static ON_Geometry Unset;

public:
  ON_Geometry() = default;
  ~ON_Geometry() = default;
  ON_Geometry(const ON_Geometry&) = default;
  ON_Geometry& operator=(const ON_Geometry&) = default;

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_Geometry( ON_Geometry&& ) ON_NOEXCEPT;

  // The rvalue assignment operator calls ON_Object::operator=(ON_Object&&)
  // which could throw exceptions.  See the implementation of
  // ON_Object::operator=(ON_Object&&) for details.
  ON_Geometry& operator=( ON_Geometry&& );
#endif

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  // Description: 
  //   Get object's 3d axis aligned bounding box.
  // Returns:
  //   3d bounding box.
  // Remarks:
  //   Uses virtual GetBBox() function to calculate the result.
  ON_BoundingBox BoundingBox() const;

  // Description:
  //   Get object's 3d axis aligned bounding box or the
  //   union of the input box with the object's bounding box.
  // Parameters:
  //   bbox - [in/out] 3d axis aligned bounding box
  //   bGrowBox - [in] (default=false) 
  //     If true, then the union of the input bbox and the 
  //     object's bounding box is returned in bbox.  
  //     If false, the object's bounding box is returned in bbox.
  // Returns:
  //   true if object has bounding box and calculation was successful.
  // Remarks:
  //   Uses virtual GetBBox() function to calculate the result.
  bool GetBoundingBox(
    ON_BoundingBox& bbox,
    bool bGrowBox = false
    ) const;

  // Description:
  //   Get corners of object's 3d axis aligned bounding box
  //   or the union of the input box with the object's bounding
  //   box.
  // Parameters:
  //   bbox_min - [in/out] minimum corner of the 3d bounding box
  //   bbox_max - [in/out] maximum corner of the 3d bounding box
  //   bGrowBox - [in] (default=false) 
  //     If true, then the union of the input bbox and the 
  //     object's bounding box is returned.
  //     If false, the object's bounding box is returned.
  // Returns:
  //   true if successful.
  bool GetBoundingBox(
    ON_3dPoint& bbox_min,
    ON_3dPoint& bbox_max,
    bool bGrowBox = false
    ) const;

  // Description:
  //   Rotates the object about the specified axis.  A positive
  //   rotation angle results in a counter-clockwise rotation
  //   about the axis (right hand rule).
  // Parameters:
  //   sin_angle - [in] sine of rotation angle
  //   cos_angle - [in] sine of rotation angle
  //   rotation_axis - [in] direction of the axis of rotation
  //   rotation_center - [in] point on the axis of rotation
  // Returns:
  //   true if object successfully rotated
  // Remarks:
  //   Uses virtual Transform() function to calculate the result.
  bool Rotate(
        double sin_angle,
        double cos_angle,
        const ON_3dVector& rotation_axis,
        const ON_3dPoint& rotation_center
        );

  // Description:
  //   Rotates the object about the specified axis.  A positive
  //   rotation angle results in a counter-clockwise rotation
  //   about the axis (right hand rule).
  // Parameters:
  //   rotation_angle - [in] angle of rotation in radians
  //   rotation_axis - [in] direction of the axis of rotation
  //   rotation_center - [in] point on the axis of rotation
  // Returns:
  //   true if object successfully rotated
  // Remarks:
  //   Uses virtual Transform() function to calculate the result.
  bool Rotate(
    double rotation_angle,
    const ON_3dVector& rotation_axis,
    const ON_3dPoint& rotation_center
    );

  // Description:
  //   Translates the object along the specified vector.
  // Parameters:
  //   translation_vector - [in] translation vector
  // Returns:
  //   true if object successfully translated
  // Remarks:
  //   Uses virtual Transform() function to calculate the result.
  bool Translate( 
    const ON_3dVector& translation_vector
    );

  // Description:
  //   Scales the object by the specified factor.  The scale is
  //   centered at the origin.
  // Parameters:
  //   scale_factor - [in] scale factor
  // Returns:
  //   true if object successfully scaled
  // Remarks:
  //   Uses virtual Transform() function to calculate the result.
  bool Scale( 
    double scale_factor
    );

  // Description:
  //   Dimension of the object.
  // Returns:
  //   Dimension of the object.
  // Remarks:
  //   The dimension is typically three.  For parameter space trimming
  //   curves the dimension is two.  In rare cases the dimension can
  //   be one or greater than three.
  virtual int Dimension() const;

  // Description:
  //   This is the virtual function that actually calculates axis
  //   aligned bounding boxes.
  // Parameters:
  //   boxmin - [in/out] array of Dimension() doubles
  //   boxmax - [in/out] array of Dimension() doubles
  //   bGrowBox - [in] (default=false) 
  //     If true, then the union of the input bbox and the 
  //     object's bounding box is returned in bbox.  
  //     If false, the object's bounding box is returned in bbox.
  // Returns:
  //   true if object has bounding box and calculation was successful
  virtual bool GetBBox(
    double* boxmin,
    double* boxmax,
    bool bGrowBox = false
    ) const;

  /*
	Description:
    Get tight bounding box.
	Parameters:
		tight_bbox - [in/out] tight bounding box
		bGrowBox -[in]	(default=false)			
      If true and the input tight_bbox is valid, then returned
      tight_bbox is the union of the input tight_bbox and the 
      curve's tight bounding box.
		xform -[in] (default=nullptr)
      If not nullptr, the tight bounding box of the transformed
      geometry is calculated.  The geometry is not modified.
	Returns:
    True if a valid tight_bbox is returned.
  Remarks:
    In general, GetTightBoundingBox is slower that BoundingBox,
    especially when xform is not null.
  */
  virtual bool GetTightBoundingBox( 
    class ON_BoundingBox& tight_bbox,
    bool bGrowBox = false,
    const class ON_Xform* xform = nullptr
  ) const;

  const ON_BoundingBox TightBoundingBox() const;

  // Description:
  //   Some objects cache bounding box information.
  //   If you modify an object, then call ClearBoundingBox()
  //   to inform the object that any cached bounding boxes
  //   are invalid.  
  //
  // Remarks:
  //   Generally, ClearBoundingBox() overrides
  //   simply invalidate a cached bounding box and then wait
  //   for a call to GetBBox() before recomputing the bounding box.
  //
  //   The default implementation does nothing.
  virtual void ClearBoundingBox();

  /*
  Description:
    Transforms the object.
 
  Parameters:
    xform - [in] transformation to apply to object.
      If xform.IsSimilarity() is zero, then you may
      want to call MakeSquishy() before calling
      Transform.
 
  Remarks:
    When overriding this function, be sure to include a call
    to ON_Object::TransformUserData() which takes care of 
    transforming any ON_UserData that may be attached to 
    the object.

  See Also:
    ON_Geometry::IsDeformable();

  Remarks:
    Classes derived from ON_Geometry should call
    ON_Geometry::Transform() to handle user data
    transformations and then transform their
    definition.
  */
  virtual
  bool Transform( 
    const ON_Xform& xform
    );

  /*
  Returns:
    True if object can be accurately modified with 
    "squishy" transformations like projections, 
    shears, an non-uniform scaling.
  See Also:
    ON_Geometry::MakeDeformable();
  */
  virtual
  bool IsDeformable() const;

  /*
  Description:
    If possible, converts the object into a form that can
    be accurately modified with "squishy" transformations
    like projections, shears, an non-uniform scaling.
  Returns:
    False if object cannot be converted to a deformable
    object.  True if object was already deformable or
    was converted into a deformable object.
  See Also:
    ON_Geometry::IsDeformable();
  */
  virtual
  bool MakeDeformable();

  // Description:
  //   Swaps object coordinate values with indices i and j.
  //
  // Parameters:
  //   i - [in] coordinate index
  //   j - [in] coordinate index
  //
  // Remarks:
  //   The default implementation uses the virtual Transform() 
  //   function to calculate the result.  If you are creating
  //   an object where Transform() is slow, coordinate swapping
  //   will be frequently used, and coordinate swapping can
  //   be quickly accomplished, then override this function.
  //
  // Example:
  //
  //          ON_Point point(7,8,9);
  //          point.SwapCoordinates(0,2);
  //          // point = (9,8,7)
  virtual
  bool SwapCoordinates(
    int i,
    int j
    );



  /*
  Description:
    Query an object to see if it has an ON_Brep form.
  Result:
    Returns true if the virtual ON_Geometry::BrepForm can compute
    an ON_Brep representation of this object.
  Remarks:
    The default implementation of ON_Geometry::BrepForm returns 
    false.
  See Also
    ON_Geometry::BrepForm
  */
  virtual
  bool HasBrepForm() const;

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
  virtual
    class ON_Brep* BrepForm(
      class ON_Brep* brep = nullptr
    ) const;

  /*
  Description:
    If this piece of geometry is a component in something
    larger, like an ON_BrepEdge in an ON_Brep, then this
    function returns the component index.
  Returns:
    This object's component index.  If this object is
    not a sub-piece of a larger geometric entity, then
    the returned index has 
    m_type = ON_COMPONENT_INDEX::invalid_type
    and
    m_index = -1.
  */
  virtual
  ON_COMPONENT_INDEX ComponentIndex() const;

  /*
  Description:
    Evaluate the location of a point from the object
    reference.
  Parameters:
    objref - [in]
    point - [out]
      If the evaluation cannot be performed, ON_3dPoint::UnsetPoint
      is returned.
  Returns:
    True if successful.
  */
  virtual
  bool EvaluatePoint( 
    const class ON_ObjRef& objref,
    ON_3dPoint& P
    ) const;
};

#endif

