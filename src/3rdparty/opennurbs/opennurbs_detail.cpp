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

ON_OBJECT_IMPLEMENT(ON_DetailView,ON_Geometry,"C8C66EFA-B3CB-4e00-9440-2AD66203379E");

ON_DetailView::ON_DetailView()
{
  m_page_per_model_ratio = 0.0;
}

ON_DetailView::~ON_DetailView()
{
}

void ON_DetailView::MemoryRelocate()
{
  m_boundary.MemoryRelocate();
}

bool ON_DetailView::IsValid( ON_TextLog* text_log ) const
{
  // Don't bother checking m_view - during runtime it's
  // not filled in. It is only used for IO.  See
  // CRhDetailViewObject::PrepareToWrite() for details.
  return m_boundary.IsValid(text_log);
}

void ON_DetailView::Dump( ON_TextLog& text_log ) const
{
  m_view.Dump(text_log);
  m_boundary.Dump(text_log);
}

unsigned int ON_DetailView::SizeOf() const
{
  unsigned int sz = ON_Geometry::SizeOf();
  sz += sizeof(*this) - sizeof(ON_Geometry);
  sz += m_boundary.SizeOf();
  return sz;
}

bool ON_DetailView::Write( ON_BinaryArchive& archive ) const
{
  bool rc = archive.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 1, 1 );
  if (!rc)
    return false;

  for(;;)
  {
    // m_view is wrapped in a subchunk so ON_3dmView can be expanded 
    // without breaking the file format.
    rc = archive.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 1, 0 );
    if (rc) 
    {
      rc = m_view.Write(archive);
      if (!archive.EndWrite3dmChunk())
        rc = false;
    }
    if(!rc)
      break;

    // m_boundary is wrapped in a subchunk so ON_NurbsCurve can be expanded 
    // without breaking the file format.
    rc = archive.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 1, 0 );
    if (rc) 
    {
      rc = m_boundary.Write(archive)?true:false;
      if (!archive.EndWrite3dmChunk())
        rc = false;
    }
    if(!rc)
      break;

    // 28 Feb 2006  1.1 fields added
    rc = archive.WriteDouble(m_page_per_model_ratio);
    if ( !rc )
      break;

    break;
  }

  if ( !archive.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

bool ON_DetailView::Read(ON_BinaryArchive& archive)
{
  m_page_per_model_ratio = 0.0;
  m_view.Default();
  m_boundary.Destroy();

  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version );
  if (!rc)
    return false;

  for(;;)
  {
    rc = (1 == major_version );
    if (!rc) break;

    // m_view is wrapped in a subchunk so ON_3dmView can be expanded 
    // without breaking the file format.
    int mj = 0, mn = 0;
    rc = archive.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &mj, &mn );
    if (rc) 
    {
      rc = m_view.Read(archive);
      if (!archive.EndRead3dmChunk())
        rc = false;
    }
    if (!rc) break;


    // m_boundary is wrapped in a subchunk so ON_NurbsCurve can be expanded 
    // without breaking the file format.
    mj = mn = 0;
    rc = archive.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &mj, &mn );
    if (rc) 
    {
      rc = m_boundary.Read(archive)?true:false;
      if (!archive.EndRead3dmChunk())
        rc = false;
    }
    if (!rc) break;

    if ( minor_version >= 1 )
    {
      rc = archive.ReadDouble(&m_page_per_model_ratio);
    }


    break;
  }

  if ( !archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

ON::object_type ON_DetailView::ObjectType() const
{
  return ON::detail_object;
}

int ON_DetailView::Dimension() const
{
  return m_boundary.Dimension();
}

bool ON_DetailView::GetBBox(
    double* boxmin,
    double* boxmax,
    bool bGrowBox
    ) const
{
  return m_boundary.GetBBox(boxmin,boxmax,bGrowBox);
}

bool ON_DetailView::GetTightBoundingBox( 
      ON_BoundingBox& tight_bbox, bool bGrowBox, const ON_Xform* xform
      ) const
{
  return m_boundary.GetTightBoundingBox(tight_bbox,bGrowBox,xform);
}

bool ON_DetailView::Transform( const ON_Xform& xform )
{
  return m_boundary.Transform(xform);
}

bool ON_DetailView::UpdateFrustum(
  ON::LengthUnitSystem model_units,
  ON::LengthUnitSystem paper_units
)
{
  if (!m_view.m_vp.IsParallelProjection())
    return false;
  if (!(m_page_per_model_ratio > 0.0))
    return false;

  ON_BoundingBox bbox = BoundingBox();
  double port_width = bbox.m_max.x - bbox.m_min.x;
  double port_height = bbox.m_max.y - bbox.m_min.y;
  if (!(port_height > 0.0) || !(port_width > 0.0))
    return false; 

  double detail_width_on_paper = bbox.m_max.x - bbox.m_min.x;
  double detail_width_on_paper_mm = detail_width_on_paper * ON::UnitScale(paper_units, ON::LengthUnitSystem::Millimeters);
  if (!(detail_width_on_paper_mm > 0.0))
    return false;

  double frustum_width_mm = detail_width_on_paper_mm / m_page_per_model_ratio;
  double frustum_width = frustum_width_mm * ON::UnitScale(ON_UnitSystem(ON::LengthUnitSystem::Millimeters), model_units);

  double aspect = fabs(port_width / port_height);
  if (!(aspect > 0.0))
    return false;

  double frustum_height = frustum_width / aspect;
  if (!(frustum_height > 0.0))
    return false;

  double fr_left, fr_right, fr_top, fr_bottom, fr_near, fr_far;
  if (m_view.m_vp.GetFrustum(&fr_left, &fr_right, &fr_bottom, &fr_top, &fr_near, &fr_far))
  {
    fr_left = (fr_left + fr_right) / 2.0 - frustum_width / 2.0;
    fr_right = fr_left + frustum_width;
    fr_bottom = (fr_bottom + fr_top) / 2.0 - frustum_height / 2.0;
    fr_top = fr_bottom + frustum_height;
    return m_view.m_vp.SetFrustum(fr_left, fr_right, fr_bottom, fr_top, fr_near, fr_far);
  }
  return false;
}
