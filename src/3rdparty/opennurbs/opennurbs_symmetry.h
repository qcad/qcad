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

#if !defined(OPENNURBS_SYMMETRY_INC_)
#define OPENNURBS_SYMMETRY_INC_

//////////////////////////////////////////////////////////////////////////
//
// ON_Symmetry
//
class ON_CLASS ON_Symmetry
{
public:
  ON_Symmetry() = default;
  ~ON_Symmetry() = default;
  ON_Symmetry(const ON_Symmetry&) = default;
  ON_Symmetry& operator=(const ON_Symmetry&) = default;

public:
  static const ON_Symmetry Unset;

  enum : unsigned int
  {
    MaximumOrder = 4096
  };


  // NOTE never use the value 113 for a new ON_Symmetry::Type.
  // This value was used briefly in June 2021 for a prototype symmetry type
  // and reusing it will break SHA1 hashes and 3dm archive IO.

  enum class Type : unsigned char
  {
    Unset = 0,

    /// <summary>
    /// Reflection about a plane.
    /// The symmetric object has 2 copies of the motif.
    /// Points on the reflection plane are fixed.
    /// </summary>
    Reflect = 1,

    /// <summary>
    /// Rotation around an axis.
    /// The symmetric object has rotated copies of the motif.
    /// Points on the rotation axis are fixed.
    /// </summary>
    Rotate = 2,

    /// <summary>
    /// Reflection and rotation alternate.
    /// Rotation angle is 360/N degrees
    /// The symmetric object has 2N copies of the motif.
    /// Points on the rotation axis are fixed.
    /// </summary>
    ReflectAndRotate = 3,

    /// <summary>
    /// General case inversion symmetry.
    /// (inversion transformation)^2 = identity.
    /// Det(inversion transformation) = -1.
    /// The symmetric object has 2 copies of the motif.
    /// </summary>
    Inversion = 4,

    /// <summary>
    /// General case cyclic symmetry (order >= 2)
    /// (cyclic transformation)^N = identity. 
    /// When N is 2 or odd, Det(cyclic transformation) = 1.
    /// When N is even and greater than 2, Det(cyclic transformation) = 1 or -1.
    /// The symmetric object has N copies of the motif.
    /// </summary>
    Cyclic = 5
  };

  static ON_Symmetry::Type SymmetryTypeFromUnsigned(unsigned int symmetry_type_as_unsigned);

  static const ON_wString SymmetryTypeToString(
    ON_Symmetry::Type symmetry_type
  );


  enum class Coordinates : unsigned char
  {
    Unset = 0,

    /// <summary>
    /// The symmetry is associated with an object is is applied to.
    /// If that object is transformed, the symmetry's planes and rotation axes
    /// are also transformed.
    /// </summary>
    Object = 1,

    /// <summary>
    /// The symmetry is independent of any objects is it applied to.
    /// The symmetry's planes and rotation axes are not changed when
    /// any of those objects are transformed.
    /// </summary>
    World = 2,
  };

  /// <summary>
  /// ON_Symmetry::Region specifies various subsets of the primary motif region.
  /// </summary>
  enum class Region : unsigned char {

    /// <summary>
    /// Unset or unknown location
    /// </summary>
    Unset = 0,

    /// <summary>
    /// Above the reflection plane and inside the primary reflect motif region.
    /// Applies to Reflect symmetries.
    /// </summary>
    AboveReflectionPlane = 1,

    /// <summary>
    /// On the reflection plane. Applies to Reflect symmetries.
    /// </summary>
    OnReflectionPlane = 2,

    /// <summary>
    /// Below the reflection plane and outside the primary reflect motif region.
    /// Applies to Reflect symmetries.
    /// </summary>
    BelowReflectionPlane = 3,

    /// <summary>
    /// Something like a line segment that has points above and below the reflection plane.
    /// </summary>
    CrossesReflectionPlane = 4,

    /// <summary>
    /// On the rotation axis. Applies to Rotate and ReflectAndRotate symmetries.
    /// </summary>
    OnRotationAxis = 5,

    /// <summary>
    /// Off of (not on) the rotation axis. Applies to Rotate symmetries.
    /// </summary>
    OffRotationAxis = 6,

    /// <summary>
    /// On the reflection half plane. Applies to ReflectAndRotate symmetries.
    /// </summary>
    OnReflectionHalfPlane = 7,

    /// <summary>
    /// On the supplemental half plane. Applies to ReflectAndRotate symmetries.
    /// </summary>
    OnSupplementalHalfPlane = 8,

    /// <summary>
    /// The half planes outside the primary motif region that are rotations
    /// of either the reflection half plane or the supplemental half plane.
    /// Applies to ReflectAndRotate symmetries.
    /// </summary>
    OnRotateAndReflectHalfPlane = 10,

    /// <summary>
    /// Above both the reflection plane and the supplemental plane.
    /// Applies to ReflectAndRotate symmetries.
    /// </summary>
    InsideRotateAndReflect = 11,

    /// <summary>
    /// Outside the primary motif region and and on one of the fixed point planes
    /// Applies to ReflectAndRotate symmetries.
    /// </summary>
    OutsideRotateAndReflect = 12
  };

  static ON_Symmetry::Region SymmetryRegionFromUnsigned(unsigned int region_as_unsigned);

  /*
  Parameters:
    point - [in]
      point to test.
    bUseCleanupTolerance - [in]
      The tolerance used to determine if a point is On an axis or plane is
      bUseCleanupTolerance ? this->CleanupTolerance() : ON_Symmetry::ZeroTolerance.
      When in doubt, pass false.
  Returns:
    The location of the point relative to the primary motif regions.
  */
  ON_Symmetry::Region PointRegion(ON_3dPoint point, bool bUseCleanupTolerance) const;

  /*
  Description:
    A symmetry region has fixed points if one or more motif transforms of the
    applicable symmetry type fixes points in the region.
    Points in these regions typically need special processing when the symmetric
    object is edited.
  Returns:
    True if symmetry_region is one of 
    ON_Symmetry::Region::OnRotationAxis,
    ON_Symmetry::Region::OnReflectionPlane, 
    ON_Symmetry::Region::OnReflectionHalfPlane, 
    ON_Symmetry::Region::OnSupplementalHalfPlane,
    or ON_Symmetry::Region::OnRotateAndReflectFixedPlane.
  */
  static bool SymmetryRegionHasFixedPoints(ON_Symmetry::Region symmetry_region);

  static ON_Symmetry::Coordinates SymmetryCoordinatesFromUnsigned(unsigned int coordinates_as_unsigned);

  static const ON_wString SymmetryCoordinatesToString(
    ON_Symmetry::Coordinates symmetry_coordinates
  );


  /*
  Parameters:
    v - [in]
      vertex to test
    bUseCleanupTolerance - [in]
      The tolerance used to determine if a point is On an axis or plane is
      bUseCleanupTolerance ? this->CleanupTolerance() : ON_Symmetry::ZeroTolerance.
      When in doubt, pass false.
  Returns:
    True if v is a vertex that might possibly be merged when
    transformed motifs are joined to create a symmetric SubD.
  */
  bool IsMotifBoundarySubDVertex(
    const class ON_SubDVertex* v, 
    bool bUseCleanupTolerance
  ) const;

  /*
  Description:
    Examples of fixed SubD components include vertices on a reflection plane or
    rotation axis, faces and edges straddling a reflection plane, 
    and faces centered about a rotation axis.
  Returns:
    True if the component is transformed to itself by every motif transformation.
  */
  bool IsFixedSubDComponent(
    const class ON_SubDComponentPtr& subd_component,
    bool bUseCleanupTolerance
  ) const;

  static const ON_UUID ReflectId;
  static const ON_UUID RotateId;
  static const ON_UUID ReflectAndRotateId;

  /*
  Description:
    Test a cyclic transformation to make sure it is stable enough to be used in an ON_Symmetry.
  Parameters:
    transformation - [in]
    transformation_order - [in]
  Returns:
    True if these 2 conditions are satisfied.
    1. identity = transformation^transformation_order.
    2. identity != transformation^i for 1 <= i < transformation_order.
  Remarks:
    The value ON_Symmetry::ZeroTolerance is used for all "zero tolerances."
  */
  static bool IsValidCyclicTranformation(
    ON_Xform transformation,
    unsigned transformation_order
  );

  /*
  Description:
    Test a transformation and transformation to make sure the transformation fixes
    points on the plane.
  Parameters:
    transformation - [in]
    fixed_plane - [in]
  Returns:
    True if the the transformation and fixed_plane are valid and
    the transformation fixes points on the plane.
  Remarks:
    The value ON_Symmetry::ZeroTolerance is used for all "zero tolerances."
  */
  static bool IsValidFixedPlane(
    ON_Xform transformation,
    ON_PlaneEquation fixed_plane
  );


  /*
  Description:
    Test a transformation and reflection plane.
  Parameters:
    reflection - [in]
    reflection_plane - [in]
  Returns:
    True if these 3 conditions are satisfied.
    1. identity = reflection^2
    2. identity != reflection
    3. Points on the reflection_plane are fixed.
  */
  static bool IsValidReflectionTranformationAndFixedPlane(
    ON_Xform reflection,
    ON_PlaneEquation reflection_plane
  );

  /*
  Parameters:
    rotation_axis - [in]
    rotation_count - [in]
    fixed_plane - [in]
  Returns:
    True if these 4 conditions are satisfied.
    1. rotation_axis is a valid line.
    2. rotation_count >= 2 
    3. rotation_count <= ON_Symmetry::MaximumOrder
    4. fixed_plane contains the rotation axis.
  Remarks:
    The value ON_Symmetry::ZeroTolerance is used for all "zero tolerances."
  */
  static bool IsValidRotationAxisAndFixedPlane(
    ON_Line rotation_axis,
    unsigned int rotation_count,
    ON_PlaneEquation fixed_plane
  );

  /*
  Parameters:
    rotation_axis - [in]
    rotation_count - [in]
    fixed_plane - [in]
  Returns:
    True if these 3 conditions are satisfied.
    1. rotation_axis is a valid line.
    2. rotation_count >= 2
    3. rotation_count <= ON_Symmetry::MaximumOrder
  Remarks:
    The value ON_Symmetry::ZeroTolerance is used for all "zero tolerances."
  */
  static bool IsValidRotationAxis(
    ON_Line rotation_axis,
    unsigned int rotation_count
  );

  /*
  Description:
    Reflection about a plane.
    The symmetric object has 2 copies of the motif.
    Points on the reflection plane are fixed.
  Parameters:
    reflection_plane - [in]
      A point P is in the primary motif when reflection_plane.ValueAt(P) >= 0.
    symmetry_coordinates - [in]
      object or world.
  Example:
    If the reflection_plane is the y-z plane,
    then (x,y,z) -> (-x,y,z) -> (x,y,z).
  Remarks:
    InversionTransformation() = reflection.
    CyclicTransformation() = identity.
  */
  static const ON_Symmetry CreateReflectSymmetry(
    ON_PlaneEquation reflection_plane,
    ON_Symmetry::Coordinates symmetry_coordinates
  );

  /*
  Description:
    Rotation around an axis.
    The symmetric object has reflection_count copies of the motif.
    Points on the axis are fixed.
  Parameters:
    rotation_axis - [in]
    rotation_count - [in]
      rotation_count must be >= 2 and the rotation angle is (360/rotation_count) degrees.
    symmetry_coordinates - [in]
      object or world.
  Example:
    If the rotation axis is the z-axis and the order is N, then the generator is
    then (x,y,z) -> (r*cos(a), r*sin(a), z) -> (r*cos(2*a), r*sin(2*a), z) -> ... -> (x,y,z),
    where r = sqrt(x*x + y*y) and a = (360 degrees)/N.
  Remarks:
    CyclicTransformation() = rotation.
    InversionTransformation() = identity.
  */
  ////ON_WIP_SDK
  static const ON_Symmetry CreateRotateSymmetry(
    ON_Line rotation_axis,
    unsigned int rotation_count,
    ON_Symmetry::Coordinates symmetry_coordinates
  );

  /*
  Description:
    Reflection and rotation alternate.
    The symmetric object has 2*reflection copies of the motif.
    Points on the rotation axis are fixed.    
  Parameters:
    reflection_plane - [in]
    rotation_axis - [in]
      A line in the reflection plane.
    rotation_count - [in]
      rotation_count must be >= 2 and the rotation angle is (360/rotation_count) degrees.
    symmetry_coordinates - [in]
      object or world.
  Example:
    If the reflection_plane is the y-z plane, the rotation axis is the z-axis,
    and rotation_count = 2, 
    then (x,y,z) -> (-x,y,z) -> (-x-y,z) -> (x,-y,z) -> (x,y,z).
  Remarks:
    InversionTransformation() = reflection.
    CyclicTransformation() = rotation by (360/rotation_count) degrees.
  */
  ////ON_WIP_SDK
  static const ON_Symmetry CreateReflectAndRotateSymmetry(
    ON_PlaneEquation reflection_plane, 
    ON_Line rotation_axis, 
    unsigned int rotation_count,
    ON_Symmetry::Coordinates symmetry_coordinates
  );

private:
  /*
  Description:
    Create an inversion symmetry from a transformation.
    The symmetric object has 2 copies of the modif.
  Parameters:
    symmetry_id - [in]
      An id you can assign to the symmetry
    inversion_transform - [in]
    fixed_plane - [in]
      inversion_transform^2 = identity.
      Det(inversion_transform) = -1.
      inversion_transform must fix the plane specified by fixed_plane.
    symmetry_coordinates - [in]
      object or world.
  Remarks:
    If inversion_transform is a reflection, consider using CreateReflectSymmetry() instead.
    When Det(transformation) = 1 and transformation^2 = identity, use CreateCyclicSymmetry() instead.
  */
  static const ON_Symmetry Internal_CreateInversionSymmetry(
    ON_UUID symmetry_id,
    ON_Xform inversion_transform,
    ON_PlaneEquation fixed_plane,
    ON_Symmetry::Coordinates symmetry_coordinates
  );

  /*
  Description:
    Create a cyclic symmetry from a transformation.
    The symmetric object has order copies of the modif.
  Parameters:
    symmetry_id - [in]
      An id you can assign to the symmetry
    cyclic_transform - [in]
      cyclic_transform^order = identity
      cyclic_transform^i != identity when 0 < i < order
      If order is even and at least 4, then Det(cyclic_transform) = 1 or -1.
      Otherwise Det(cyclic_transform) = 1.
    cyclic_order - [in]
      cyclic_order >= 2
    zero_plane - [in]
      zero_plane must contain all fixed points of cyclic_transform.
      For any point P,  F = P + cyclic_transform*P + ... + cyclic_transform^(cyclic_order-1)*P
      is a fixed point of cyclic_transform.
    symmetry_coordinates - [in]
      object or world.
  Remarks:
    If cyclic_transform is a rotation, use CreateRotationSymmetry().
    If cyclic_transform is a reflection, use CreateReflectionSymmetry().
    If 2 = cyclic_order and Det(cyclic_transform) = -1, use CreateInversionSymmetry().
  */
  static const ON_Symmetry Internal_CreateCyclicSymmetry(
    ON_UUID symmetry_id,
    ON_Xform cyclic_transform,
    unsigned int cyclic_order,
    ON_PlaneEquation zero_plane,
    ON_Symmetry::Coordinates symmetry_coordinates
  );


  /*
  Description:
    Create a cyclic symmetry from a transformation.
    The symmetric object has order copies of the modif.
  Parameters:
    symmetry_id - [in]
      An id you can assign to the symmetry
    cyclic_transform - [in]
      cyclic_transform^order = identity
      cyclic_transform^i != identity when 0 < i < order
      If order is even and at least 4, then Det(cyclic_transform) = 1 or -1.
      Otherwise Det(cyclic_transform) = 1.
    cyclic_order - [in]
      cyclic_order >= 2
    fixed_line - [in]
      fixed_line must contain all fixed points of cyclic_transform.
      For any point P,  F = P + cyclic_transform*P + ... + cyclic_transform^(cyclic_order-1)*P
      is a fixed point of cyclic_transform.
    symmetry_coordinates - [in]
      object or world.
  Remarks:
    If cyclic_transform is a rotation, use CreateRotationSymmetry().
    If cyclic_transform is a reflection, use CreateReflectionSymmetry().
    If 2 = cyclic_order and Det(cyclic_transform) = -1, use CreateInversionSymmetry().
  */
  static const ON_Symmetry Internal_CreateCyclicSymmetry(
    ON_UUID symmetry_id,
    ON_Xform cyclic_transform,
    unsigned int cyclic_order,
    ON_Line fixed_line,
    ON_Symmetry::Coordinates symmetry_coordinates
  );

public:

  /*
  Returns:
    0 if lhs and rhs define identical symmetries (types and transformations).
  Remarks:
    The symmtric object information is not compared.
  */
  static int Compare(const ON_Symmetry* lhs, const ON_Symmetry* rhs);

  /*
  Returns:
    0 if the symmetry transformations are the same to tolerance.
    Otherwise returns ON_Symmetry::Compare(lhs,rhs). 
  */
  static int CompareSymmetryTransformation(const ON_Symmetry* lhs, const ON_Symmetry* rhs, double zero_tolerance);

public:
  /*
  Returns:
    Symmetry type.
  */
  ON_Symmetry::Type SymmetryType() const;

  /*
  Returns:
    True if SymmetryType() is ON_Symmetry::Type::Rotate
  */
  bool IsRotate() const;

  /*
  Returns:
    True if SymmetryType() is ON_Symmetry::Type::Reflect
  */
  bool IsReflect() const;

  /*
  Returns:
    True if SymmetryType() is ON_Symmetry::Type::ReflectAndRotate
  */
  bool IsReflectAndRotate() const;

  /*
  Returns:
    Symmetry type.
  */
  ON_Symmetry::Coordinates SymmetryCoordinates() const;

  /*
  Returns:
    Symmetry unique id
  */
  const ON_UUID SymmetryId() const;

  /*
  Description:
    Set this instance to ON_Symmetry::Unset.
  */
  void Clear();

  /*
  Returns:
    True if this instance is set to a symmetry.
  */
  bool IsSet() const;

  /*
  Returns:
    True if this instance is not set.
  */
  bool IsUnset() const;

  /*
  Returns:
    Number of types the motif appears in the symmetric object.
  Remarks:
    MotifCount() = CyclicOrder()*InversionOrder().
  */
  unsigned int MotifCount() const;

  /*
  Returns:
    0: unset symmetry
    1: InversionTransformation() = identity
    2: InversionTransformation()^2 = identity and InversionTransform() != identity
  Remarks:
    In common cases, InversionTransformation() is either the identity or a reflection.
  */
  unsigned int InversionOrder() const;

  /*
  Returns:
    0: unset symmetry
    1: the cyclic transformation is the identity.
    N >= 2: CyclicTransformation()^N = identity and CyclicTransform()^i != identity when 0 < i < N.
  Remarks:
    In common cases, CyclicTransformation() is either the identity or a rotation.
  */
  unsigned int CyclicOrder() const;

  /*
  Description:
    Get the transformation that maps the starting motif to the specified copy.
  Parameters:
    index - [in]
      0 based index of the copy (negative values are supported)
      0 returns the identity transformation.
  Remarks:
    "0 based" means when index is a multiple of MotifCount(), the identity is returned.
  */
  const ON_Xform MotifTransformation(
    int index
  ) const;

  /*
  Description:
    Get the set of motif transformations that maps the starting motif to the copies.
  Parameters:
    bIncludeIdentity - [in]
      If true, then motif_transformations[0] = identity and MotifCount() transformations are returned.
      Otherwise, motif_transformations[0] = MotifTransformation(1) and (MotifCount() -1) transformations are returned.
    motif_transformations[] - out
      motif transformations are returned here.
  Returns:
    MotifCount().
  */
  unsigned GetMotifTransformations(
    bool bIncludeIdentity,
    ON_SimpleArray<ON_Xform>& motif_transformations
  ) const;

  /*
  Returns:
    The inversion transformation is returned.
    InversionTransformation()^InversionOrder() = identity.
  Remarks:
    In common cases, InversionTransformation() is either the identity or a reflection (mirror).
  Remarks:
    NOTE: A symmetry with SymmetryOrder() = 2 and transformation S can be represented
    as either InversionTransformation() = S and CyclicTransformation() = identity or
    or CyclicTransformation() = S and InversionTransformation() = identity.
    The convention is to use the cyclic transforms when S is a 180 rotations
    and inversion transforms otherwise.
  */
  const ON_Xform InversionTransformation() const;

  /*
  Returns:
    The cyclic transformation is returned.
    CyclicTransformation()^CyclicOrder() = identity.
  Remarks:
    In common cases, CyclicTransformation() is either the identity or a rotation.
  Remarks:
    NOTE: A symmetry with SymmetryOrder() = 2 and transformation S can be represented
    as either InversionTransformation() = S and CyclicTransformation() = identity or
    or CyclicTransformation() = S and InversionTransformation() = identity.
    The convention is to use the cyclic transforms when S is a 180 rotations
    and inversion transforms otherwise.
  */
  const ON_Xform CyclicTransformation() const;

  /*
  Returns:
    A plane containing all the fixed points of the symmetry.
    When the symmetry type is Reflect, FixedPlane() = ReflectionPlane().
    When the symmetry type is Rotate, FixedPlane() contains the axis of rotation
    and defines the zero angle.
    When the symmetry type is ReflectAndRotate, FixedPlane() = ReflectionPlane().
  */
  const ON_PlaneEquation FixedPlane() const;

  /*
  Returns:
    A SHA1 hash uniquely identifying the symmetry
  */
  const ON_SHA1_Hash Hash() const;

  /*
  Returns:
    If the symmetry is type is Reflect or ReflectAndRotate, then the reflection plane is returned.
    Otherwise ON_Plane::Nan is returned.
  */
  const ON_PlaneEquation ReflectionPlane() const;

  /*
  Returns:
    If the symmetry is type is Reflect or ReflectAndRotate, then the reflection plane is returned.
    Otherwise ON_Plane::Nan is returned.
  */
  const ON_Xform ReflectionTransformation() const;


private:
  /*
  Returns:
    True if the symmetry type requires a valid rotation axis.
    False otherwise
  */
  bool Internal_RequiresRotationAxis() const;

  /*
  Returns:
    True if the symmetry type requires a valid fixed plane.
    False otherwise
  */
  bool Internal_RequiresFixedPlane() const;

  /*
  Returns:
    True if the symmetry type is Reflect, Rotate, ReflectAndRotate.
  */
  bool Internal_IsStandardType() const;

public:
  /*
  Returns:
    If the symmetry is type is Rotate or ReflectAndRotate, then the rotation axis is returned.
    Otherwise ON_Line::Nan is returned.
  */
  const ON_Line RotationAxis() const;

  /*
  Returns:
    If the symmetry is type is Rotate or ReflectAndRotate, then a point on the rotation axis is returned.
    Otherwise ON_3dPoint::Nan is returned.
  */
  const ON_3dPoint RotationAxisPoint() const;

  /*
  Returns:
    If the symmetry is type is Rotate or ReflectAndRotate, then the direction of the rotation axis is returned.
    Otherwise ON_3dVector::Nan is returned.
  Remarks:
    This vector may have length != 1
  */
  const ON_3dVector RotationAxisDirection() const;

  /*
  Returns:
    If the symmetry is type is Rotate or ReflectAndRotate, then a unit vector in the direction of the rotation axis is returned.
    Otherwise ON_3dVector::Nan is returned.
  */
  const ON_3dVector RotationAxisTangent() const;

  /*
  Returns:
    If the symmetry is type is Rotate or ReflectAndRotate, then the rotation count is returned.
    Otherwise 0 is returned.
  */
  unsigned int RotationCount() const;

  /*
  Returns:
    If the symmetry is type is Rotate or ReflectAndRotate, then the rotation angle in degrees is returned.
    Otherwise ON_DBL_QNAN is returned.
  Remarks:
    RotationAngleDegrees() = 360.0/RotationCount()
  */
  double RotationAngleDegrees() const;

  /*
  Returns:
    If the symmetry is type is Rotate or ReflectAndRotate, then the rotation transformation is returned.
    Otherwise ON_Xform::Nan is returned.
  */
  const ON_Xform RotationTransformation() const;

  /*
  Returns:
    If the symmetry is type is Rotate or ReflectAndRotate, then the rotation angle in radians is returned.
    Otherwise ON_DBL_QNAN is returned.
  Remarks:
    RotationAngleRadians() = (2.0*ON_PI)/RotationCount()
  */
  double RotationAngleRadians() const;


  /*
  Description:
    A reflect and rotate symmetry has three important planes.
    * The reflection plane. 
    This plane is returned by ReflectAndRotatePlane(0).
    * The supplemental plane. This plane is the reflection plane rotated
    around the rotation axis by angle = -0.5*RotationAngle() and then reversed. 
    This plane is returned by ReflectAndRotatePlane(1).
    * The reflection plane rotated around the rotation axis by pi/2. 
    This plane is returned by ReflectAndRotatePlane(2).

    The primary motif region for a reflect and rotate symmetry is region above both 
    the reflection plane and the supplemental plane.
        
    The normals of all planes point into the primary motif region.

  Parameters:
    plane_index - [in]
      Selects the plane.
      0: returns the reflection plane.
      1: returns the supplemental plane.
      2: returns the half space bounding plane.
  
  Returns:
    If the symmetry type is ReflectAndRotate and plane_index is valid, the requested plane is returned. 
    Otherwise ON_PlaneEquation::Nan is returned.
  */
  const ON_PlaneEquation ReflectAndRotatePlane(
    unsigned int plane_index
  ) const;

  bool OnReflectAndRotateFixedPlane( ON_3dPoint P, bool bUseCleanupTolerance) const;

public:
  bool Write(class ON_BinaryArchive&) const;
  bool Read(class ON_BinaryArchive&);
  void Dump(class ON_TextLog&) const;
  void ToText(
    bool bIncludeSymmetricObject,
    class ON_TextLog& text_log
    ) const;

  /*
  Description:
    If SymmetryCoordinates() = ON_Symmetry::Coordinates::Object, then the symmetry definition
    is transformed.
  */
  const ON_Symmetry TransformConditionally(const ON_Xform& xform) const;

  /*
  Description:
    The the symmetry definition is transformed.
  */
  const ON_Symmetry TransformUnconditionally(const ON_Xform& xform) const;

public:
  /*
  Returns:
    A SHA1 hash value that uniquely identifies the symmetry settings.
  Remarks:
    The symmetric object content serial number and symmetric object hashes 
    are not included in the symmetry hash.
  */
  const ON_SHA1_Hash SymmetryHash() const;

  /*
  Description:
    If the SubD is known to have the symmetry specified by this ON_Symmetry,
    then SetSymmetricObject() is used to save the subd's geometry and topology
    hash on this ON_Symmetry.
  Parameters:
    subd - [in]
      This subd must have the symmetry specified by this ON_Symmetry.
  Returns:
    True if the symmetric object state was saved on this.
    False if input is not valid.
  Remarks:
    At a later time and after unknown modifications or copying, use
    SameSymmetricObjectGeometry(subd1) and SameSymmetricObjectTopology(subd1)
    to determine if subd1 has the same geometry or topology as subd at the
    time SetSymmetryObject(sub) was called.
  */
  bool SetSymmetricObject(const class ON_SubD* subd) const;

  /*
  Description:
    If the parent SubD is known to have the symmetry specified by this ON_Symmetry,
    then SetSymmetricObject() is used to save the subd's geometry and topology
    hash on this ON_Symmetry.
  Parameters:
    subdimple - [in]
      The parent SubD must have the symmetry specified by this ON_Symmetry.
  Returns:
    True if the symmetric object state was saved on this.
    False if input is not valid.
  Remarks:
    The ON_SubDimple version is used internally. Pretend this doesn't exist.

    At a later time and after unknown modifications or copying, use
    SameSymmetricObjectGeometry(subd1) and SameSymmetricObjectTopology(subd1)
    to determine if subd1 has the same geometry or topology as subd at the
    time SetSymmetryObject(sub) was called.
  */
  bool SetSymmetricObject(const class ON_SubDimple* subdimple) const;

  /*
  Description:
    Clears the symmetric object geometry and topology hashes.
  */
  void ClearSymmetricObject() const;

  /*
  Returns:
    True if subd has identical geometry to the subd passed to SetSymmetricObject().
  */
  bool SameSymmetricObjectGeometry(const class ON_SubD* subd) const;

  bool SameSymmetricObjectGeometry(const class ON_SubDimple* subdimple) const;

  /*
  Returns:
    True if subd has identical topology to the subd passed to SetSymmetricObject().
  */
  bool SameSymmetricObjectTopology(const class ON_SubD* subd) const;

  bool SameSymmetricObjectTopology(const class ON_SubDimple* subdimple) const;

public:
  // ON_Symmetry::ZeroTolerance is a 3d tolerance use to validate
  // transformations, rotation axis locations, and plane equations.
  // This tolerance is constant across all applications and used to validate symmetric objects.
  // Use the per symmetry ON_Symmetry.CleanupTolerance() to prepare input objects.
  // In a valid symmetric object, the distance between distinct SubD vertex locations
  // must always be greater than ON_Symmetry::ZeroTolerance.
  static const double ZeroTolerance;

public:
  /*
  Description:
    Cleanup tolerance is a 3d world unt length used to preprocess input when creating
    symmetric objects. For example, in a reflect symmetry, cleanup tolerance would be
    used to move vertices near the reflection plane to be on the reflection plane.
    This tolerance is context sensitive. In the same model it could vary between two
    different input objects. The value is saved with the symmetry so calculations driven
    by modifying an input object can be repeated using the same cleanup tolerance.
  Parameters:
    cleanup_tolerance - [in]
      cleanup_tolerance >= ON_Symmetry::ZeroTolerance.
      The cleanup tolerance for this specific symmetry. The default is ON_Symmetry::ZeroTolerance.
  */
  void SetCleanupTolerance(
    double cleanup_tolerance
  );

  /*
  Description:
    Cleanup tolerance is a 3d world unt length used to preprocess input when creating
    symmetric objects. For example, in a reflect symmetry, cleanup tolerance would be
    used to move vertices near the reflection plane to be on the reflection plane.
    This tolerance is context sensitive. In the same model it could vary between two
    different input objects. The value is saved with the symmetry so calculations driven
    by modifying an input object can be repeated using the same cleanup tolerance.
  Returns:
    The cleanup tolerance for this specific symmetry. It is always >= ON_Symmetry::ZeroTolerance.
    The default is ON_Symmetry::ZeroTolerance.
  */
  double CleanupTolerance() const;

  /*
  Returns:
    bUseCleanupTolerance ? this->CleanupTolerance() : ON_Symmetry::ZeroTolerance;
  */
  double Tolerance(bool bUseCleanupTolerance) const;

private:
  ON_Symmetry::Type m_type = ON_Symmetry::Type::Unset;

  ON_Symmetry::Coordinates m_coordinates = ON_Symmetry::Coordinates::Unset;

  // m_inversion_order (0 = unset, 1 = identity (no inversion), 2 = (non-identity inversion)
  unsigned char m_inversion_order = 0;

  unsigned char m_reserved1 = 0;

  // m_cyclic_order (0 = unset, 1 = identity (no cyclic), >= 2 cyclic order (non-identity cyclic)
  unsigned int m_cyclic_order = 0;

  // id is a preset value for the 3 built in symmetries and user defined for others
  ON_UUID m_id = ON_nil_uuid;
  
  // m_inversion_transform^2 = identity
  ON_Xform m_inversion_transform = ON_Xform::Nan;
  
  // m_cyclic_transform^m_cyclic_order = identity
  ON_Xform m_cyclic_transform = ON_Xform::Nan;

  // m_fixed_plane contains all fixed points of the symmetry transformation.
  // When type is Reflect, m_fixed_plane is the reflection plane.
  // When type is Rotate, m_fixed_plane contains the rotation axis and is used to define zero rotation angle.
  // When type is ReflectAndRotate, m_fixed_plane is the reflection plane.
  ON_PlaneEquation m_fixed_plane = ON_PlaneEquation::NanPlaneEquation;

  // Set when type is Rotate or ReflectAndRotate
  // m_rotation_axis always lies in m_plane.
  ON_Line m_rotation_axis = ON_Line::NanLine;

  // Using 0.0 insures the default returned by CleanupTolerance() is always ON_Symmetry::ZeroTolerance.
  double m_cleanup_tolerance = 0.0;

private:
  ///////////////////////////////////////////////////////////////////////////
  // 
  // NOTE WELL:
  //   Avoid the temptation to provide SDK access to any of the m_symmetric_object* values.
  // 
  //   Use one of the ON_Symmetry::SetSymmetricObject(...) overrides to set these.
  //   Use ON_Symmetry::ClearSymmetricObject() to clear the m_symmetric_object* values.
  // 
  //   Use one of the ON_Symmetry::SameSymmetricObjectGeometry(...) to see if the geometry
  //   of the object you have is has the symmetry defined by this ON_Symmetry.
  // 
  //   Use one of the ON_Symmetry::SameSymmetricObjectTopology(...) to see if the topology
  //   of the object you have is has the symmetry defined by this ON_Symmetry.

  // The triplet
  //   m_symmetric_object_content_serial_number, 
  //   m_symmetric_object_topology_hash, 
  //   m_symmetric_object_geometry_hash
  // is used to detect if a previously symmtetric object is still symmetric
  // and to determine how it should be updated to return to being symmetric.
  // Legacy 3dm files have only the m_symmetric_object_content_serial_number.
  // Rhino 7.6 and later files have the SHA1 hashes as well.
  mutable ON__UINT64 m_symmetric_object_content_serial_number = 0;
  // For ON_SubD, this is the value of ON_SubD.TopologyHash() at the time the SubD
  // was known to be perfectly symmetric.
  mutable ON_SHA1_Hash m_symmetric_object_topology_hash = ON_SHA1_Hash::ZeroDigest;
  // For ON_SubD, this is the value of ON_SubD.GeometryHash() at the time the SubD
  // was known to be perfectly symmetric.
  mutable ON_SHA1_Hash m_symmetric_object_geometry_hash = ON_SHA1_Hash::ZeroDigest;

private:
  static int Internal_CompareDouble(const double* lhs, const double* rhs, size_t count);
  const ON_Xform Internal_ReflectAndRotateTransformation(unsigned index) const;
  static const ON_Xform Internal_RotationXform(ON_Line axis, int rotation_index, int rotation_count);
  const ON_Xform Internal_RotationXform(int rotation_index, int rotation_count) const;
  static const ON_PlaneEquation Internal_UnitizePlaneEquationParameter(ON_PlaneEquation);
};

#endif
