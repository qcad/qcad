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

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

ON_OBJECT_IMPLEMENT(ON_Geometry,ON_Object,"4ED7D4DA-E947-11d3-BFE5-0010830122F0");

#if defined(ON_HAS_RVALUEREF)
ON_Geometry::ON_Geometry( ON_Geometry&& src ) ON_NOEXCEPT
  : ON_Object(std::move(src))
{}

ON_Geometry& ON_Geometry::operator=( ON_Geometry&& src )
{
  ON_Object::operator=(std::move(src));
  return *this;
}
#endif

bool ON_Geometry::IsValid(
  ON_TextLog*
  ) const
{
  return false;
}


ON_BoundingBox ON_Geometry::BoundingBox() const
{
  ON_BoundingBox bbox;
  if ( !GetBoundingBox( bbox.m_min, bbox.m_max, false ) )
    bbox.Destroy();
  return bbox;
}

bool 
ON_Geometry::GetBoundingBox( // returns true if successful
  ON_BoundingBox& bbox,
  bool bGrowBox
  ) const
{
  return (0!=GetBoundingBox( bbox.m_min, bbox.m_max, bGrowBox ));
}

bool 
ON_Geometry::GetBoundingBox( // returns true if successful
  ON_3dPoint& boxmin,
  ON_3dPoint& boxmax,
  bool bGrowBox
  ) const
{
  ON_Workspace ws;
  const int dim = Dimension();
  double *bmin, *bmax;
  if ( dim <= 3 ) {
    bmin = &boxmin.x;
    bmax = &boxmax.x;
  }
  else {
    bmin = ws.GetDoubleMemory(dim*2);
    bmax = bmin+dim;
    memset( bmin, 0, 2*dim*sizeof(*bmin) );
    if ( bGrowBox ) {
      bmin[0] = boxmin.x; bmin[1] = boxmin.y; bmin[1] = boxmin.z;
      bmax[0] = boxmax.x; bmax[1] = boxmax.y; bmax[1] = boxmax.z;
    }
  }
	// Treat invalid box on input as empty
	bool invalid=false;	//input box invalid=empty
	if(bGrowBox)
		invalid =  boxmin.x>boxmax.x || boxmin.y>boxmax.y|| boxmin.z>boxmax.z;
	if(bGrowBox && invalid)
		bGrowBox=false;

  const bool rc = (0 != GetBBox( bmin, bmax, bGrowBox ));
  if ( dim > 3 ) {
    boxmin.x = bmin[0]; boxmin.y = bmin[1]; boxmin.z = bmin[2];
    boxmax.x = bmax[0]; boxmax.y = bmax[1]; boxmax.z = bmax[2];
  }
  else if ( dim <= 2 ) {
    boxmin.z = 0.0;
    boxmax.z = 0.0;
    if ( dim <= 1 ) {
      boxmin.y = 0.0;
      boxmax.y = 0.0;
    }
  }
  return rc;
}

const ON_BoundingBox ON_Geometry::TightBoundingBox() const
{
  ON_BoundingBox bbox = ON_BoundingBox::NanBoundingBox;
  // call virtual function
  if (this->GetTightBoundingBox(bbox, false, nullptr) && bbox.IsValid())
    return bbox;
  return ON_BoundingBox::NanBoundingBox;
}

bool ON_Geometry::GetTightBoundingBox( 
	ON_BoundingBox& tight_bbox, 
  bool bGrowBoxAsInt,
	const ON_Xform* xform
  ) const
{
  //	This implementation should be overridden by classes derived
  //  from ON_Geometry
  bool bGrowBox = (0!= bGrowBoxAsInt);
  if ( bGrowBox && !tight_bbox.IsValid() )
  {
    bGrowBox = false;
  }
  if ( !bGrowBox )
  {
    tight_bbox.Destroy();
  }

  if ( xform && !xform->IsIdentity() )
  {
    ON_3dPointArray corners(8);
    ON_BoundingBox world_bbox;
    if ( GetBoundingBox(world_bbox,false) )
    {
      world_bbox.GetCorners(corners);
      if ( corners.GetTightBoundingBox(tight_bbox,bGrowBox,xform) )
        bGrowBox = true;
    }
  }
  else
  {
    if ( GetBoundingBox(tight_bbox,bGrowBox) )
      bGrowBox = true;
  }

  return bGrowBox;
}

bool ON_Geometry::SwapCoordinates(
      int i, int j        // indices of coords to swap
      )
{
  bool rc = false;
  const int dim = Dimension();
  if ( dim > 0 && dim <= 3 && i >= 0 && i < 3 && j >= 0 && j < 3 ) {
    if ( i == j ) {
      rc = true;
    }
    else {
      int k;
      ON_Xform swapij(ON_Xform::ZeroTransformation);
      for ( k = 0; k < 4; k++ ) {
        if ( i == k )
          swapij[k][j] = 1.0;
        else if ( j == k )
          swapij[k][i] = 1.0;
        else
          swapij[k][k] = 1.0;
      }
      rc = Transform( swapij );
    }
  }
  return rc;
}

bool ON_Geometry::Rotate(
      double sin_angle,          // sin(angle)
      double cos_angle,          // cos(angle)
      const ON_3dVector& axis, // axis of rotation
      const ON_3dPoint& center // center of rotation
      )
{
  if ( sin_angle == 0.0 && cos_angle == 1.0 )
    return true;
  ON_Xform rot;
  rot.Rotation( sin_angle, cos_angle, axis, center );
  return (0!=Transform( rot ));
}

bool ON_Geometry::Rotate(
      double angle,              // angle in radians
      const ON_3dVector& axis, // axis of rotation
      const ON_3dPoint& center // center of rotation
      )
{
  if ( angle == 0.0 )
    return true;
  return Rotate( sin(angle), cos(angle), axis, center );
}

bool ON_Geometry::Translate( const ON_3dVector& delta )
{
  if ( delta.IsZero() )
    return true;
  if ( false == delta.IsValid() )
    return false;
  const ON_Xform tr(ON_Xform::TranslationTransformation( delta ));
  return (0!=Transform( tr ));
}

bool ON_Geometry::Scale( double x )
{
  if ( x == 1.0 )
    return true;
  if (false == ON_IS_VALID(x))
    return false;
  ON_Xform s(ON_Xform::DiagonalTransformation(x));
  return (0!=Transform( s ));
}

int ON_Geometry::Dimension() const
{
  return 3;
}

bool ON_Geometry::GetBBox(
  double* boxmin,
  double* boxmax,
  bool bGrowBox
  ) const
{
  return false;
}

bool ON_Geometry::IsDeformable() const
{
  return false;
}

bool ON_Geometry::MakeDeformable()
{
  return false;
}

void ON_Geometry::ClearBoundingBox()
{
  // default implementation does nothing
}

bool ON_Geometry::Transform( const ON_Xform& xform )
{
  TransformUserData(xform);
  return true;
}

bool ON_Geometry::HasBrepForm() const
{
  // override if specific geometry has brep form
  return false;
}

ON_Brep* ON_Geometry::BrepForm(ON_Brep* brep) const
{
  // override if specific geometry has brep form
  return nullptr;
}

ON_COMPONENT_INDEX ON_Geometry::ComponentIndex() const
{
  // default constructor sets
  // m_type = ON_COMPONENT_INDEX::invalid_type and m_index = -1.
  ON_COMPONENT_INDEX ci;
  return ci;  
}

bool ON_Geometry::EvaluatePoint( const class ON_ObjRef& objref, ON_3dPoint& P ) const
{
  // virtual function default
  P = ON_3dPoint::UnsetPoint;
  return false;
}

