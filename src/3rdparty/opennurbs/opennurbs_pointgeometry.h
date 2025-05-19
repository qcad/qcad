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

#if !defined(OPENNURBS_POINT_GEOMETRY_INC_)
#define OPENNURBS_POINT_GEOMETRY_INC_

// NOTE:  ON_3dPoint is much more efficient than ON_Point.
//        Use ON_Point when you need a polymorphic 3d point
//        that is derived from ON_Geometry or ON_Object.

class ON_CLASS ON_Point : public ON_Geometry
{
public:
  ON_3dPoint point;

  ON_Point();
  ON_Point(const ON_Point&);
  ON_Point(const ON_3dPoint&);
  ON_Point(double,double,double);
  ~ON_Point();
  ON_Point& operator=(const ON_Point&);
  ON_Point& operator=(const ON_3dPoint&);
  
  operator double*();
  operator const double*() const;
  operator ON_3dPoint*();
  operator const ON_3dPoint*() const;
  operator ON_3dPoint&();
  operator const ON_3dPoint&() const;

  /////////////////////////////////////////////////////////////////
  //
  // ON_Object overrides
  //

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump( ON_TextLog& ) const override; // for debugging

  bool Write(
         ON_BinaryArchive&  // serialize definition to binary archive
       ) const override;

  bool Read(
         ON_BinaryArchive&  // restore definition from binary archive
       ) override;

  ON::object_type ObjectType() const override;

  /////////////////////////////////////////////////////////////////
  //
  // ON_Geometry overrides
  //

  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

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


private:
  ON_OBJECT_DECLARE(ON_Point);
};

#endif
