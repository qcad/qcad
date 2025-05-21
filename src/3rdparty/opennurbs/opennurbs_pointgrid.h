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

#if !defined(OPENNURBS_POINT_GRID_INC_)
#define OPENNURBS_POINT_GRID_INC_

class ON_CLASS ON_PointGrid : public ON_Geometry
{
public:
  ON_PointGrid();
  ON_PointGrid(const ON_PointGrid&);
  ON_PointGrid(
          int,  // point count0 (>=1)
          int   // point count1 (>=1)
          );

  void Initialize(void);  // zeros all fields

  bool Create( 
          int,  // point count0 (>=1)
          int   // point count1 (>=1)
          );

  void Destroy();

  virtual ~ON_PointGrid();
  void EmergencyDestroy(); // call if memory used by point grid becomes invalid

	ON_PointGrid& operator=(const ON_PointGrid&);

  // point_grid[i][j] returns GetPoint(i,j)
  ON_3dPoint* operator[](int);             // 0 <= index < PointCount(0)
  const ON_3dPoint* operator[](int) const; // 0 <= index < PointCount(0)
  
  /////////////////////////////////////////////////////////////////
  // ON_Object overrides

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump( ON_TextLog& ) const override; // for debugging

  bool Write(
         ON_BinaryArchive&  // open binary file
       ) const override;

  bool Read(
         ON_BinaryArchive&  // open binary file
       ) override;

  ON::object_type ObjectType() const override;

  /////////////////////////////////////////////////////////////////
  // ON_Geometry overrides

  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  // virtual ON_Geometry GetTightBoundingBox override		
  bool GetTightBoundingBox( class ON_BoundingBox& tight_bbox, bool bGrowBox = false, const class ON_Xform* xform = nullptr ) const override;

  bool Transform( 
         const ON_Xform&
         ) override;

  // virtual ON_Geometry::IsDeformable() override
  bool IsDeformable() const override;

  // virtual ON_Geometry::MakeDeformable() override
  bool MakeDeformable() override;

  bool SwapCoordinates(
        int, int        // indices of coords to swap
        ) override;

  /////////////////////////////////////////////////////////////////
  // Interface

  bool IsClosed( 
        int // dir
        ) const;

  int PointCount(   // number of points in grid direction
        int         // dir 0 = "s", 1 = "t"
        ) const;

  int PointCount(   // total number of points in grid
        void
        ) const;

  ON_3dPoint& Point(
        int, int // point index ( 0 <= i <= PointCount(0), 0 <= j <= PointCount(1)
        );

  ON_3dPoint Point(
        int, int // point index ( 0 <= i <= PointCount(0), 0 <= j <= PointCount(1)
        ) const;

  double* PointArray();

  const double* PointArray() const;

  int PointArrayStride(  // point stride in grid direction
        int         // dir 0 = "s", 1 = "t"
        ) const;

  bool SetPoint(      // set a single point
        int, int, // point index ( 0 <= i <= PointCount(0), 0 <= j <= PointCount(1)
        const ON_3dPoint& // value of point
        );

  bool GetPoint(              // get a single control vertex
        int, int,   // CV index ( 0 <= i <= CVCount(0), 0 <= j <= CVCount(1)
        ON_3dPoint&      // gets euclidean cv when NURBS is rational
        ) const;

  bool Reverse(  // reverse grid order
    int // dir  0 = "s", 1 = "t"
    );

  bool Transpose(); // transpose grid points

  /////////////////////////////////////////////////////////////////
  // Implementation
protected:

  int m_point_count[2];   // number of points (>=1)
  int m_point_stride0;    // >= m_point_count[1]
  ON_3dPointArray m_point;
  // point[i][j] = m_point[i*m_point_stride0+j]

private:
  static ON_3dPoint m_no_point; // prevent crashes when sizes are 0

  ON_OBJECT_DECLARE(ON_PointGrid);
};


#endif
