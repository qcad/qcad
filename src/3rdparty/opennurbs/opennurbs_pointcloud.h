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

#if !defined(OPENNURBS_POINTCLOUD_INC_)
#define OPENNURBS_POINTCLOUD_INC_

///////////////////////////////////////////////////////////////////////////////
//
// Class  ON_PointCloud  - unordered set of points
//          ON_PointField  - point height field
//

class ON_CLASS ON_PointCloud : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_PointCloud);

public:
  ON_PointCloud();
  ON_PointCloud(
    int  // initial point array capacity
    );
  ON_PointCloud( const ON_PointCloud& );
  ~ON_PointCloud();

  ON_PointCloud(const ON_3dPoint* P0, int count);

  // 0<dim<4 stride is dim+is_rat
  ON_PointCloud(const double* P0, int dim, bool is_rat, int count); 
  ON_PointCloud& operator=( const ON_PointCloud& );

  ON_3dPoint& operator[](int);
  const ON_3dPoint& operator[](int) const;

  /*
  Description:
    Get a point cloud point from an ON_COMPONENT_INDEX.
  Parameters:
    ci - [in] a component index with m_typ set to ON_COMPONENT_INDEX::pointcloud_point
              and 0 <= m_index and m_index < m_P.Count().
  Returns:
    Point at [ci.m_index] or ON_3dPoint::UnsetPoint if ci is not valid.
  */
  ON_3dPoint Point( ON_COMPONENT_INDEX ci ) const;

  void Destroy();

  /*
  Description:
    Call when the memory pool used the point cloud's arrays is
    no longer in existence.
  */
  void EmergencyDestroy();

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  // virtual ON_Object override
  void Dump( ON_TextLog& ) const override; // for debugging

  // virtual ON_Object override
  bool Write( ON_BinaryArchive& ) const override;

  // virtual ON_Object override
  bool Read( ON_BinaryArchive& ) override;

  // virtual ON_Object override
  ON::object_type ObjectType() const override;

  // virtual ON_Object::SizeOf override
  unsigned int SizeOf() const override;

  // virtual ON_Geometry override
  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  // virtual ON_Geometry GetTightBoundingBox override		
  bool GetTightBoundingBox( class ON_BoundingBox& tight_bbox, bool bGrowBox = false, const class ON_Xform* xform = nullptr ) const override;

  // virtual ON_Geometry override
  bool Transform( 
         const ON_Xform&
         ) override;

  // virtual ON_Geometry override
  bool IsDeformable() const override;

  // virtual ON_Geometry override
  bool MakeDeformable() override;

  // virtual ON_Geometry override
  bool SwapCoordinates(
        int, int        // indices of coords to swap
        ) override;


  /*
  Description:
    Get the index of the point in the point cloud that is closest
    to P.
  Parameters:
    P - [in]
    closest_point_index - [out]
    maximum_distance - [in] optional distance constraint.
        If maximum_distance > 0, then only points Q with
        |P-Q| <= maximum_distance are tested.
  Returns:
    True if a point is found; in which case *closest_point_index
    is the index of the point.  False if no point is found
    or the input is not valid.
  See Also:
    ON_GetClosestPointInPointList
  */
  bool GetClosestPoint( 
          ON_3dPoint P,
          int* closest_point_index,
          double maximum_distance = 0.0
          ) const;


  /////////////////////////////////////////////////////////////////
  // Interface
  // 
  int PointCount() const;
  void AppendPoint( const ON_3dPoint& );
  void InvalidateBoundingBox(); // call if you change values of points

  // for ordered streams
  void SetOrdered(bool bOrdered); // true if set is ordered stream
  bool IsOrdered() const; // true if set is ordered stream

  // for height fields
  bool HasPlane() const; // true if set is height field above a plane
  void SetPlane( const ON_Plane& );
  const ON_Plane& Plane();
  double Height(int);

  /*
  Returns:
    True if m_N.Count() == m_P.Count().
  */
  bool HasPointNormals() const;

  /*
  Returns:
    True if m_C.Count() == m_P.Count().
  */
  bool HasPointColors() const;

  /*
  Returns:
    True if m_V.Count() == m_P.Count().
  */
  bool HasPointValues() const;

  /*
  Returns:
    Number of points that are hidden.
  */
  int HiddenPointCount() const;
  unsigned int HiddenPointUnsignedCount() const;

  /*
  Description:
    Destroys the m_H[] array and sets m_hidden_count=0.
  */
  void DestroyHiddenPointArray();

  /*
  Returns:
    If the point cloud has some hidden points, then an array
    of length PointCount() is returned and the i-th
    element is true if the i-th vertex is hidden.
    If no points are hidden, nullptr is returned.
  */
  const bool* HiddenPointArray() const;

  /*
  Description:
    Set the runtime hidden point flag.
  Parameters:
    point_index - [in] point vertex index
    bHidden - [in] true to hide vertex
  */
  void SetHiddenPointFlag( int point_index, bool bHidden );

  /*
  Description:
    Returns true if the point is hidden.  This is a runtime
    setting that is not saved in 3dm files.
  Parameters:
    point_index - [in]
  Returns:
    True if the point is hidden.
  */
  bool PointIsHidden( int point_index ) const;

  /*
  Description:
    Returns a random subsample of a point cloud.
  Parameters:
    source_point_cloud - [in] The point cloud to subsample.
    subsample_point_count - [in] The number of points to keep.
    destination_point_cloud - [out] If nullptr, then a new ON_PointCloud() 
        will be the destination. This can be the source point cloud.
    progress_reporter - [in] Optional progress reporter, can be nullptr.
    terminator - [in] Optional terminator, can be nullptr.
  Returns:
    A new ON_PointCloud which is a subsample of source_point_cloud.
    If destination_point_cloud == nullptr, then memory will be allocated for
    the returned point cloud and becomes the responsibility of the caller.
  */
  static ON_PointCloud* RandomSubsample(
    const ON_PointCloud* source_point_cloud,
    const unsigned int subsample_point_count,
    ON_PointCloud* destination_point_cloud,
    ON_ProgressReporter* progress_reporter,
    ON_Terminator* terminator
  );

  /*
  Description:
    Removes points at given indices.
  Parameters:
    indices - [in] An array of indices of the points to remove.
  Returns:
    The number of points removed from the point cloud.
  */
  int RemoveRange(const ON_SimpleArray<int>& indices);
  
  /*
  Description:
    Removes points at given indices.
  Parameters:
    count - [in] The number of indices of the points to remove.
    indices - [in] An array of indices of the points to remove.
  Returns:
    The number of points removed from the point cloud.
  */
  int RemoveRange(int count, const int* indices);


  /////////////////////////////////////////////////////////////////
  // Implementation
  ON_3dPointArray m_P;

  /////////////////////////////////////////////////////////////////
  // Implementation - OPTIONAL point normal
  //    Either m_N[] has zero count or it has the same
  //    count as m_P[], in which case m_N[j] reports
  //    the color assigned to m_P[j].
  ON_SimpleArray<ON_3dVector> m_N;

  /////////////////////////////////////////////////////////////////
  // Implementation - OPTIONAL point color
  //    Either m_C[] has zero count or it has the same
  //    count as m_P[], in which case m_C[j] reports
  //    the color assigned to m_P[j].
  ON_SimpleArray<ON_Color> m_C;

  /////////////////////////////////////////////////////////////////
  // Implementation - OPTIONAL point value (intensity)
  //    Either m_V[] has zero count or it has the same
  //    count as m_P[], in which case m_V[j] reports
  //    the value assigned to m_P[j].
  ON_SimpleArray<double> m_V;

  /////////////////////////////////////////////////////////////////
  // Implementation - RUNTIME point visibility - not saved in 3dm files.
  //    If m_H.Count() = m_P.Count(), then
  //    m_H[j] is true if the point m_P[j] 
  //    is hidden.  Otherwise, all points are visible.
  //    m_hidden_count = number of true values in the m_H[] array.
  ON_SimpleArray<bool> m_H;
  unsigned int m_hidden_count = 0;

  ON_Plane m_plane;
  ON_BoundingBox m_bbox;
  unsigned int m_flags = 0; // bit 1 is set if ordered
                            // bit 2 is set if plane is set

};

#endif
