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


#include "opennurbs_internal_glyph.h"
#include "opennurbs_win_dwrite.h"

unsigned int ON_Outline::FigureCount() const
{
  return m_figures.UnsignedCount();
}

const ON_ClassArray< ON_OutlineFigure >& ON_Outline::Figures() const
{
  return m_figures;
}

const ON_OutlineFigure& ON_Outline::Figure(
int i
) const
{
  return (i >= 0 && i < m_figures.Count()) ? m_figures[i] : ON_OutlineFigure::Unset;
}

unsigned int ON_OutlineAccumulator::CurrentFigurePointCount() const
{
  return m_point_accumulator.UnsignedCount();
}

unsigned int ON_Outline::OutlinePointCount() const
{
  unsigned int outline_point_count = 0;
  for (unsigned int i = 0; i < m_figures.UnsignedCount(); i++)
    outline_point_count += m_figures[i].m_points.UnsignedCount();

  return outline_point_count;
}

unsigned int ON_OutlineAccumulator::ErrorCount() const
{
  return m_error_count;
}
  
const ON_BoundingBox ON_Outline::OutlineBoundingBox() const
{
  while (0 == m_bbox_status)
  {
    m_bbox_status = 7;
    m_bbox = ON_BoundingBox::NanBoundingBox;

    const unsigned int figure_count = m_figures.UnsignedCount();
    if (0 == figure_count)
      break;

    ON_BoundingBox bbox = m_figures[0].BoundingBox();
    for (unsigned int i = 1; i < figure_count; i++)
    {
      bbox.Union(m_figures[i].BoundingBox());
    }
    if (bbox.IsValid() && bbox.IsNotEmpty())
    {
      m_bbox = bbox;
      m_bbox_status = 1;
    }
    
    break;
  }

  return m_bbox;
}
  
double ON_Outline::AreaEstimate() const
{
  if (
    ON_OutlineFigure::Type::SingleStroke == m_figure_type
    || ON_OutlineFigure::Type::DoubleStroke == m_figure_type
    )
  {
    return 0.0;
  }

  double outline_area = 0.0;
  const ON__UINT32 figure_count = m_figures.UnsignedCount();
  for (ON__UINT32 i = 0; i < figure_count; i++)
  {
    outline_area += m_figures[i].AreaEstimate();
  }
  return outline_area;
}
  
void  ON_Outline::Reverse()
{
  const ON__UINT32 figure_count = m_figures.UnsignedCount();
  for (ON__UINT32 i = 0; i < figure_count; i++)
  {
    m_figures[i].ReverseFigure();
  }
}

static int Internal_CompareAreaEstimate(ON_OutlineFigure* const* lhs, ON_OutlineFigure* const* rhs)
{
  // Used to sort the figures_sorted_by_size[] array which is constructed in a way
  // that we know all elements are not nullptr and have valid AreaEstimates().
  const double lhs_area = fabs((*lhs)->AreaEstimate());
  const double rhs_area = fabs((*rhs)->AreaEstimate());
  if (lhs_area > rhs_area)
    return -1; // largest areas are before smaller areas
  if (lhs_area < rhs_area)
    return 1; // largest areas are before smaller areas
  return 0;
}

void ON_Outline::SortFigures(
  ON_OutlineFigure::Orientation outer_loop_orientation
)
{
  if (
    ON_OutlineFigure::Orientation::Clockwise != outer_loop_orientation
    && ON_OutlineFigure::Orientation::CounterClockwise != outer_loop_orientation
    )
    return;

  if (outer_loop_orientation == m_sorted_figure_outer_orientation)
    return;

  if (ON_OutlineFigure::Orientation::Error == m_sorted_figure_outer_orientation)
    return; // not sortable

   m_sorted_figure_outer_orientation = outer_loop_orientation;

  const int figure_count = m_figures.Count();
  if (figure_count <= 0)
    return;

  const ON_OutlineFigure::Orientation inner_loop_orientation
    = (ON_OutlineFigure::Orientation::Clockwise == outer_loop_orientation)
    ? ON_OutlineFigure::Orientation::CounterClockwise
    : ON_OutlineFigure::Orientation::Clockwise;

  ON_SimpleArray<ON_OutlineFigure*> sorted_figures(figure_count);
  ON_SimpleArray<ON_OutlineFigure*> ignored_figures(figure_count);

  for (int i = 0; i < figure_count; i++)
  {
    ON_OutlineFigure* ptr = &m_figures[i];
    if (
      (ON_OutlineFigure::Type::Perimeter == ptr->FigureType()
        || ON_OutlineFigure::Type::Unknown == ptr->FigureType()
        || ON_OutlineFigure::Type::Unset == ptr->FigureType())
      )
    {
      const double figure_area = ptr->AreaEstimate();
      const ON_BoundingBox figure_bbox = ptr->BoundingBox();
      const ON_OutlineFigure::Orientation figure_orientation = ptr->FigureOrientation();

      if (
        0.0 != figure_area && ON_IsValid(figure_area)
        && figure_bbox.IsNotEmpty() && false == figure_bbox.IsPoint()
        && (outer_loop_orientation == figure_orientation
          || inner_loop_orientation == figure_orientation)
        )
      {
        sorted_figures.Append(ptr);
        continue;
      }

      // Mark this figure has NotPerimeter because something about
      // its path is not valid. This will prevent it from being 
      // used in meshing.
      ptr->m_figure_type = ON_OutlineFigure::Type::NotPerimeter;
    }

    // ignored figures are ones that are not a perimeter of an inner
    // or outer boundary.
    ignored_figures.Append(ptr);
  }

  const unsigned int sorted_figure_count = sorted_figures.UnsignedCount();

  // Sort figures so the ones with largest included area are first.
  sorted_figures.QuickSort(Internal_CompareAreaEstimate);

  // As we look at each element of sorted_figures[], it gets assigned to
  // outer_figures[] or inner_figures[]. If it is assigned to inner_figures[],
  // the smallest figure that contains it is assigned to inner_figures_parent[].
  //
  // Over the years, many more complicated approaches to sorting were tried,
  // all of which attempted to take into account the orientations from the font file. 
  // It is so common for the orientations in the font files to be wrong, 
  // that ignoring them is the most efficient and reliable approach to date.
  // It is extremly common for outer figures to overlap.
  ON_SimpleArray<ON_OutlineFigure*> outer_figures(sorted_figure_count);
  ON_SimpleArray<ON_OutlineFigure*> inner_figures(sorted_figure_count);
  ON_SimpleArray<ON_OutlineFigure*> inner_figures_parent(sorted_figure_count);

  for (  unsigned k = 0; k < sorted_figure_count; ++k)
  {
    ON_OutlineFigure* f = sorted_figures[k];

    // This for(int k0; ...) loop finds the smallest larger figure that contains f and uses
    // the orientation of this containing loop to determine the orientation of f.
    ON_OutlineFigure* parent_outer_figure = nullptr;
    for (unsigned k0 = 0; k0 < k; ++k0)
    {
      // Given our assumptions, it is impossible for bigger_f to be inside of f.
      ON_OutlineFigure* bigger_f = sorted_figures[k0];
      if (false == f->IsInsideOf(bigger_f, false))
        continue;

      if (outer_loop_orientation == bigger_f->FigureOrientation())
      {
        // f is inside of bigger_f and bigger_f is an outer loop.
        parent_outer_figure = bigger_f;
      }
      else if (inner_loop_orientation == bigger_f->FigureOrientation())
      {
        // f is inside of bigger_f and bigger_f is an inner loop.
        // So f is a nested outer (like the registered trademark glyph)
        parent_outer_figure = nullptr;
      }
    }

    if (nullptr == parent_outer_figure)
    {
      outer_figures.Append(f);
      if (inner_loop_orientation == f->FigureOrientation())
      {
        // convert this figure to an outer.
        f->ReverseFigure();
      }
    }
    else
    {
      inner_figures.Append(f);
      inner_figures_parent.Append(parent_outer_figure);
      if (outer_loop_orientation == f->FigureOrientation())
      {
        // convert this figure to an inner
        f->ReverseFigure();
      }
    }
  }

  const unsigned outer_count = outer_figures.UnsignedCount();
  const unsigned inner_count = inner_figures.UnsignedCount();

  if ( 0 == outer_count )
  {
    m_sorted_figure_outer_orientation = ON_OutlineFigure::Orientation::Error;
    return;
  }

  if (0 == inner_count)
  {
    return;
  }

  // Sort figures by outer followed by its inners.
  sorted_figures.SetCount(0);
    for (unsigned i = 0; i < outer_count; ++i)
  {
    ON_OutlineFigure* outer_figure = outer_figures[i];
    if (nullptr == outer_figure)
      continue;
    sorted_figures.Append(outer_figure);
    for (unsigned j = 0; j < inner_count; ++j)
    {
      if (outer_figure == inner_figures_parent[j])
      {
        ON_OutlineFigure* inner_figure = inner_figures[j];
        inner_figures[j] = nullptr;
        inner_figures_parent[j] = nullptr;
        if (nullptr != inner_figure)
          sorted_figures.Append(inner_figure);
      }
    }
  }

  // Put single stroke and other non-perimeter figures on the end.
  for (unsigned int k = 0; k < ignored_figures.UnsignedCount(); k++)
  {
    ON_OutlineFigure* f = ignored_figures[k];
    if (nullptr != f)
      sorted_figures.Append(f);
  }

  if (sorted_figures.Count() == figure_count)
  {
    for (int k = 0; k < figure_count; k++)
    {
      if (sorted_figures[k] != &m_figures[k])
      {
        // Need to reorder m_figures[] array
        ON_ClassArray<ON_OutlineFigure> tmp(figure_count);
        for (int i = 0; i < figure_count; i++)
        {
          tmp.Append(*sorted_figures[i]);
        }
        m_figures = tmp;
        break;
      }
    }
  }

  return;
}

ON_OutlineFigure::Orientation ON_Outline::SortedFigureOuterOrientation() const
{
  return m_sorted_figure_outer_orientation;
}

ON_OutlineFigure::Orientation ON_Outline::SortedFigureInnerOrientation() const
{
  const ON_OutlineFigure::Orientation outer_orientation = SortedFigureOuterOrientation();
  if (ON_OutlineFigure::Orientation::CounterClockwise == outer_orientation)
    return ON_OutlineFigure::Orientation::Clockwise;
  if (ON_OutlineFigure::Orientation::Clockwise == outer_orientation)
    return ON_OutlineFigure::Orientation::CounterClockwise;

  return outer_orientation;
}


const ON_TextBox ON_Outline::GlyphMetrics() const
{
  return m_glyph_metrics;
}

const ON_OutlineFigurePoint ON_OutlineAccumulator::CurrentFigureStartPoint() const
{
  return m_figure_start;
}
  
const ON_OutlineFigurePoint ON_OutlineAccumulator::CurrentFigurePreviousPoint() const
{
  return m_figure_prev;
}
  
const ON_OutlineFigurePoint ON_OutlineAccumulator::CurrentFigurePoint() const
{
  return m_figure_current;
}


const bool ON_OutlineAccumulator::CurrentFigureAccumulating() const
{
  return Internal_InFigure();
}

ON__UINT32 ON_OutlineAccumulator::UnitsPerEM() const
{
  return m_units_per_em;
}

ON__UINT32 ON_Outline::UnitsPerEM() const
{
  return m_units_per_em;
}

void ON_Outline::SetUnitsPerEM(
  ON__UINT32 units_per_em
)
{
  m_units_per_em = units_per_em;
  if (m_units_per_em > 0)
    m_short_tolerance = (m_units_per_em > 0.0) ? (m_units_per_em / 2056.0) : 0.0;
}


ON_OutlineFigure::Type ON_OutlineAccumulator::FigureType() const
{
  return m_figure_type;
}

bool ON_OutlineAccumulator::IsInitialized() const
{
  return (1 == m_status);
}

bool ON_OutlineAccumulator::IsFinalized() const
{
  return (2 == m_status);
}

bool ON_OutlineAccumulator::IsInitializedOrFinalized() const
{
  return IsInitialized() || IsFinalized();
}

ON_Outline* ON_OutlineAccumulator::HarvestOutline()
{  
  ON_Outline* outline = m_outline;
  m_outline = nullptr;
  if (outline == m_managed_outline)
    m_managed_outline = nullptr;
  Clear();
  return outline;
}


void ON_OutlineAccumulator::Clear()
{
  if (m_managed_outline)
  {
    if (m_outline == m_managed_outline)
      m_outline = nullptr;
    delete m_managed_outline;
    m_managed_outline = nullptr;
  }

  if ( nullptr != m_outline)
    *m_outline = ON_Outline::Unset;

  m_units_per_em = 0;
  m_status = 0;
  m_figure_type = ON_OutlineFigure::Type::Unset;
  m_figure_depth = 0;
  m_error_count = 0;

  AbandonCurrentFigure();
}


bool ON_OutlineAccumulator::BeginGlyphOutline(
  ON__UINT32 font_units_per_em,
  ON_OutlineFigure::Type figure_type,
  ON_Outline* destination_outline
)
{
  Clear();
  m_units_per_em = font_units_per_em;
  m_status = (m_units_per_em > 0) ? 1 : 0;
  m_figure_type = figure_type;

  if (nullptr == destination_outline)
  {
    m_managed_outline = new ON_Outline();
    m_outline = m_managed_outline;
  }
  else
  {
    *destination_outline = ON_Outline::Unset;
    m_outline = destination_outline;
  }

  m_outline->SetUnitsPerEM(font_units_per_em);
  m_outline->m_figure_type = figure_type;

  return (1 == m_status);
}

bool ON_OutlineFigure::Internal_HasValidEnds(
  bool bLogErrors
) const
{
  if (m_points.UnsignedCount() >= 2
    && m_points[0].IsBeginFigurePoint()
    && m_points.Last()->IsEndFigurePoint()
    )
    return true;
  if (bLogErrors)
  {
    ON_ERROR("Invalid figure start or end information.");
  }
  return false;
}

static void Internal_GrowBBox(
  const ON_2fPoint& pmin,
  const ON_2fPoint& pmax,
  ON_2fPoint& bbox_min,
  ON_2fPoint& bbox_max
)
{
  if (pmin.x < bbox_min.x) bbox_min.x = pmin.x; else if (pmax.x > bbox_max.x) bbox_max.x = pmax.x;
  if (pmin.y < bbox_min.y) bbox_min.y = pmin.y; else if (pmax.y > bbox_max.y) bbox_max.y = pmax.y;
}

const ON_BoundingBox ON_OutlineFigure::BoundingBox() const
{
  while (0 == m_bbox_status)
  {
    m_bbox_status = 7;

    const ON__UINT32 figure_end_dex = Internal_FigureEndDex(false);
    if (0 == figure_end_dex)
      break;

    const ON_OutlineFigurePoint* a = m_points.Array();
    ON_2fPoint bbox_min = a[0].m_point;
    ON_2fPoint bbox_max = bbox_min;
    ON_2fPoint bbox_cv_min = bbox_min;
    ON_2fPoint bbox_cv_max = bbox_max;
    
    for (ON__UINT32 i = 0U; i < figure_end_dex; ++i)
    {
      const ON__UINT32 degree = ON_OutlineFigure::Internal_SegmentDegree(i);
      if (degree < 1U || degree > 3U)
        continue;
      // a[i] = start of bezier (line,quadratic,or cubic)
      ON_OutlineFigurePoint p = a[i+degree]; // p = a[i+degree] = end of bezier (line,quadratic,or cubic)
      Internal_GrowBBox(p.m_point, p.m_point, bbox_min, bbox_max);
      if (degree >= 2U)
      {
        p = a[++i]; // p = 1st interior cv of a quadratic or cubic bezier
        Internal_GrowBBox(p.m_point, p.m_point, bbox_cv_min, bbox_cv_max);
        if (3U == degree)
        {
          p = a[++i]; // p = 2nd interior cv of a cubic bezier
          Internal_GrowBBox(p.m_point, p.m_point, bbox_cv_min, bbox_cv_max);
        }
      }
    }

    if (
      bbox_cv_min.x >= bbox_min.x 
      && bbox_cv_max.x <= bbox_max.x
      && bbox_cv_min.y >= bbox_min.y 
      && bbox_cv_max.y <= bbox_max.y
      )
    {
      // If there were any bezier segments, their control points were inside the bounding box of the segment end points.
      m_bbox_min = bbox_min;
      m_bbox_max = bbox_max;
      m_bbox_status = 1;
      break;
    }

    // get bezeir bounding boxes as needed
    ON_OutlineFigurePoint cv[4];
    cv[3] = a[0]; // to suppress potintial uninitialized memory warning

    for (ON__UINT32 i = 0U; i < figure_end_dex; ++i)
    {
      const ON__UINT32 degree = ON_OutlineFigure::Internal_SegmentDegree(i);
      if (degree < 2U || degree > 3U)
        continue; // correct to continue when degree = 1
      cv[0] = a[i]; // [a[i] = start of quadratic or cubic bezier
      cv[1] = a[++i]; // 1st interior cv of a  quadratic or cubic bezer
      bbox_cv_min = cv[1].m_point;
      bbox_cv_max = bbox_cv_min;
      cv[2] = a[i + 1]; // end of quadratic bezier or penultimate cv of a cubic bezier
      if (3U == degree)
      {
        Internal_GrowBBox(cv[2].m_point, cv[2].m_point, bbox_cv_min, bbox_cv_max);
        ++i;
        cv[3] = a[i + 1]; // end of a cubic bezier
      }

      if (
        bbox_cv_min.x >= bbox_min.x 
        && bbox_cv_max.x <= bbox_max.x
        && bbox_cv_min.y >= bbox_min.y 
        && bbox_cv_max.y <= bbox_max.y
        )
      {
        // the control points of this bezier are inside the current bounding box.
        continue;
      }

      // get tight bounding box of this bezier
      ON_BezierCurve bez(3, false, degree + 1);
      for (ON__UINT32 j = 0; j <= degree; j++)
        bez.SetCV(j, ON_3dPoint(cv[j].m_point.x, cv[j].m_point.y, 0.0));

      const ON_BoundingBox bez_bbox = bez.BoundingBox();
      if (bez_bbox.IsNotEmpty())
      {
        const double minf = ON_UNSET_FLOAT;
        const double maxf = ON_UNSET_POSITIVE_FLOAT;
        if (
          minf < bez_bbox.m_min.x 
          && bez_bbox.m_max.x < maxf
          && minf < bez_bbox.m_min.y 
          && bez_bbox.m_max.y < maxf
          )
        {
          bbox_cv_min.Set((float)bez_bbox.m_min.x, (float)bez_bbox.m_min.y);
          bbox_cv_max.Set((float)bez_bbox.m_max.x, (float)bez_bbox.m_max.y);
        }
      }

      Internal_GrowBBox(bbox_cv_min, bbox_cv_max, bbox_cv_min, bbox_cv_max);
    }

    m_bbox_min = bbox_min;
    m_bbox_max = bbox_max;
    m_bbox_status = 1;
    if (m_bbox_min == m_bbox_max)
    {
      if (
        ON_OutlineFigure::Type::Perimeter == m_figure_type
        || ON_OutlineFigure::Type::Unset == m_figure_type
        || ON_OutlineFigure::Type::Unknown == m_figure_type
        )
      {
        m_figure_type = ON_OutlineFigure::Type::NotPerimeter;
      }
    }
    break;
  }

  if (1 == m_bbox_status)
    return ON_BoundingBox(ON_3dPoint(m_bbox_min), ON_3dPoint(m_bbox_max));

  return ON_BoundingBox::NanBoundingBox;
}

bool ON_OutlineFigure::Internal_NegateY( ON_2fPoint& p )
{
  if (0.0 != p.y && p.y > ON_UNSET_FLOAT && p.y < ON_UNSET_POSITIVE_FLOAT)
  {
    p.y = -p.y;
    return true;
  }
  return false;
}

bool ON_OutlineFigure::NegateY()
{
  bool rc = false;
  const ON__UINT32 count = m_points.UnsignedCount();
  ON_OutlineFigurePoint* a = m_points.Array();
  for (ON__UINT32 i = 0; i < count; i++)
  {
    if ( ON_OutlineFigure::Internal_NegateY(a[i].m_point) )
      rc = true;
  }

  if (rc)
  {
    if (ON_OutlineFigure::Orientation::Clockwise == m_orientation)
      m_orientation = ON_OutlineFigure::Orientation::CounterClockwise;
    else if (ON_OutlineFigure::Orientation::CounterClockwise == m_orientation)
      m_orientation = ON_OutlineFigure::Orientation::Clockwise;

    if (ON_IsValid(m_area_estimate) && 0.0 != m_area_estimate)
      m_area_estimate = -m_area_estimate;
  }

  return rc;
}

static double Internal_DeltaArea(
  const ON_2dPoint& p0,
  const ON_2dPoint& p1
)
{
  return (p0.x - p1.x)*(p0.y + p1.y);
}

ON_OutlineFigure::Type ON_OutlineFigure::FigureType() const
{
  return m_figure_type;
}


ON__UINT16 ON_OutlineFigure::FigureIndex() const
{
  return m_figure_index;
}

double ON_OutlineFigure::BoxArea() const
{
  const ON_BoundingBox bbox = BoundingBox();
  double bbox_area = 0.0;
  if (bbox.IsNotEmpty())
  {
    const double dx = bbox.m_max.x - bbox.m_min.x;
    const double dy = bbox.m_max.y - bbox.m_min.y;
    bbox_area = (dx >= 0.0 && dy >= 0.0) ? (dx*dy) : 0.0;
  }
  else
  {
    bbox_area = 0.0;
  }
  return bbox_area;
}

unsigned ON_OutlineFigure::GetUpToFourPointsOnFigure(ON_2fPoint p[4]) const
{
  if (nullptr == p)
    return 0;
  
  unsigned point_count = 0;
  const ON__UINT32 end_dex = Internal_FigureEndDex(false);
  if (end_dex > 0)
  {
    // p[0] = point at the start
    const ON_2fPoint p0 = this->m_points[0].m_point;
    p[point_count++] = p0;


    // p[1] = point between start and middle
    ON_2fPoint prev_p = p0;
    unsigned i1 = end_dex / 2;
    if (i1 >= 2)
    {
      for (ON__UINT32 i = i1 - 1; i > 0; --i)
      {
        if (false == this->m_points[i].IsOnFigure())
          continue;
        const ON_2fPoint candidate_p = this->m_points[i].m_point;
        if (prev_p != candidate_p)
        {
          prev_p = candidate_p;
          p[point_count++] = candidate_p;
          break;
        }
      }
    }

    // p[2] = point between middle and end
    for (/*empty init*/; i1 <= end_dex; ++i1)
    {
      if (false == this->m_points[i1].IsOnFigure())
        continue;
      const ON_2fPoint candidate_p = this->m_points[i1].m_point;
      if (prev_p != candidate_p)
      {
        prev_p = candidate_p;
        p[point_count++] = candidate_p;
        break;
      }
    }

    // p[3] = point close to end
    for (ON__UINT32 i = end_dex; i > i1; --i)
    {
      if (false == this->m_points[i].IsOnFigure())
        continue;
      const ON_2fPoint candidate_p = this->m_points[i].m_point;
      if (prev_p != candidate_p && p0 != candidate_p)
      {
        p[point_count++] = candidate_p;
        break;
      }
    }
  }

  for (unsigned i = point_count; i < 4; ++i)
    p[i] = ON_2fPoint::NanPoint;
  return point_count;
}

static bool Internal_ExtraInsideOfPolylineText(
  const ON_OutlineFigure* outer_figure,
  const ON_OutlineFigure* inner_figure
)
{
  // This function is called when an extra test is needed to be certain
  // that outer_pline contains inner_pline. Generating the input
  // for this text and performing this test is computationally expensive.
  // It is called sparingly.

  if (nullptr == outer_figure || nullptr == inner_figure)
    return false;

  ON_SimpleArray<ON_2dPoint> outer_pline;
  outer_figure->GetPolyline(0.0, outer_pline);
  const unsigned outer_count = outer_pline.UnsignedCount();
  if (outer_count < 4)
    return false;

  ON_SimpleArray<ON_2dPoint> inner_pline;
  inner_figure->GetPolyline(0.0, inner_pline);
  const unsigned inner_count = inner_pline.UnsignedCount();
  if (inner_count < 2)
    return false;

  const ON_2dPoint* a = outer_pline.Array();
  const ON_2dPoint* b = inner_pline.Array();

  // Bmin, Bmax = bounding box of inner_pline.
  ON_2dPoint Bmin = b[0];
  ON_2dPoint Bmax = Bmin;
  double c;
  for (unsigned j = 1; j < inner_count; ++j)
  {
    c = b[j].x;
    if (c < Bmin.x)
      Bmin.x = c;
    else if (c > Bmax.x)
      Bmax.x = c;
    c = b[j].y;
    if (c < Bmin.y)
      Bmin.y = c;
    else if (c > Bmax.y)
      Bmax.y = c;
  }

  ON_2dPoint Amin;
  ON_2dPoint Amax;
  ON_2dPoint A[2] = { ON_2dPoint::NanPoint,a[0] };
  ON_2dPoint B[2] = { ON_2dPoint::NanPoint,ON_2dPoint::NanPoint };
  double alpha[3] = { ON_DBL_QNAN, ON_DBL_QNAN, ON_DBL_QNAN };
  for (unsigned i = 1; i < outer_count; ++i)
  {
    A[0] = A[1];
    A[1] = a[i];
    if (A[0] == A[1])
      continue;

    // Amin,Amax = bounding box of outer line segment

    if (A[0].x <= A[1].x)
    {
      Amin.x = A[0].x;
      Amax.x = A[1].x;
    }
    else
    {
      Amin.x = A[1].x;
      Amax.x = A[0].x;
    }
    if (Amax.x < Bmin.x)
      continue;
    if (Amin.x > Bmax.x)
      continue;

    if (A[0].y <= A[1].y)
    {
      Amin.y = A[0].y;
      Amax.y = A[1].y;
    }
    else
    {
      Amin.y = A[1].y;
      Amax.y = A[0].y;
    }
    if (Amax.y < Bmin.y)
      continue;
    if (Amin.y > Bmax.y)
      continue;

    alpha[0] = ON_DBL_QNAN;

    B[1] = b[0];
    for (unsigned j = 1; j < inner_count; ++j)
    {
      B[0] = B[1];
      B[1] = b[j];
      if (B[0] == B[1])
        continue;

      // line segment bounding box check
      if (B[0].x < Amin.x && B[1].x < Amin.x)
        continue;
      if (B[0].y < Amin.y && B[1].y < Amin.y)
        continue;
      if (B[0].x > Amax.x && B[1].x > Amax.x)
        continue;
      if (B[0].y > Amax.y && B[1].y > Amax.y)
        continue;

      if (alpha[0] != alpha[0])
      {
        // need to initialize alpha[3] 
        alpha[0] = A[1].y - A[0].y;
        alpha[1] = A[0].x - A[1].x;
        alpha[2] = A[1].x * A[0].y - A[0].x * A[1].y;
      };

      double h[2] = {
        alpha[0] * B[0].x + alpha[1] * B[0].y + alpha[2],
        alpha[0] * B[1].x + alpha[1] * B[1].y + alpha[2]
      };
      if (h[0] < 0.0 && h[1] < 0.0)
        continue; // B[0] and B[1] on same side of infinite line through A[0],A[1]
      if (h[0] > 0.0 && h[1] > 0.0)
        continue; // B[0] and B[1] on same side of infinite line through A[0],A[1]

      const double beta[3] =
      {
        B[1].y - B[0].y,
        B[0].x - B[1].x,
        B[1].x * B[0].y - B[0].x * B[1].y
      };

      h[0] = beta[0] * B[0].x + beta[1] * B[0].y + beta[2];
      h[1] = beta[0] * B[1].x + beta[1] * B[1].y + beta[2];
      if (h[0] < 0.0 && h[1] < 0.0)
        continue; // A[0] and A[1] on same side of infinite line through B[0],B[1]
      if (h[0] > 0.0 && h[1] > 0.0)
        continue; // A[0] and A[1] on same side of infinite line through B[0],B[1]

      // The line segment A[0],A[1] and line segment B[0],B[1] intersect someplace.
      // The location of the intersection doesn't matter, even if it's one of the end points.
      return false;
    }
  }

  return true;
}

bool ON_OutlineFigure::IsInsideOf(
  const ON_OutlineFigure* outer_figure,
  bool bPerformExtraChecking
) const
{
  if (nullptr == outer_figure)
    return false;

  const ON_OutlineFigure::Orientation outer_orientation = outer_figure->FigureOrientation();
  if (ON_OutlineFigure::Orientation::Clockwise != outer_orientation && ON_OutlineFigure::Orientation::CounterClockwise != outer_orientation)
    return false;


  const ON_BoundingBox this_bbox = this->BoundingBox();
  const ON_BoundingBox outer_bbox = outer_figure->BoundingBox();
  if (false == outer_bbox.Includes(this_bbox))
  {
    // The bounding boxes are from the glyph outline control polygons.
    // There are rare case when this f is inside of other_f
    // but this_bbox is not contained in other_bbox. In practice, this
    // is quite rare, but that's why "probably" is part of this function's name.
    return false;
  }

  const double outer_area = fabs(outer_figure->AreaEstimate());
  const double this_area = fabs(this->AreaEstimate());
  if (false == (0.0 < this_area && this_area < outer_area))
    return false; // this figure is too big to be inside of other_f

  // Check that the 3 standard test points on this are inside of other_f.
  // Again, it is possible that the 3 test points are inside but some other
  // point is outside. In practice this is rare and that possibility
  // is why "probably" is in this function's name.

  const int outer_orientation_sign = ON_OutlineFigure::Orientation::CounterClockwise == outer_orientation ? 1 : -1;

  ON_2fPoint this_p[4];
  unsigned  this_point_count = this->GetUpToFourPointsOnFigure(this_p);

  for (unsigned i = 0; i < this_point_count; ++i)
  {
    // check start point.
    const int wn = outer_orientation_sign * outer_figure->WindingNumber(this_p[i]);
    if (1 != wn)
    {
      // this_p[i] is not inside of other_f.
      return false;
    }
  }

  if (0 == this_point_count)
    return false;

  const ON_OutlineFigure::Orientation this_orientation = this->FigureOrientation();

  if (outer_orientation == this_orientation || bPerformExtraChecking)
  {
    // The context that calls this function is sorting nested loops.
    // The orientation of outer_figure has been decided and set at this point.
    // When this orientation of this is not different, we need more checking
    // to verify that the orientation from the font definition file was really "wrong".
    // The "A crossbar" in Bahnschrift U+00C5 is one of many cases that
    // require this additional checking. More generally, glyphs with
    // orientations set correctly and which use overlapping outer 
    // boundaries need this test to prevent incorrectly. This situation is
    // common in fonts like Bahnschrift and fonts for Asian language scripts
    // that have "brush stroke" boundaries that overlap.
    if (false == Internal_ExtraInsideOfPolylineText(outer_figure, this))
      return false;
  }

  return true;
}


ON__UINT32 ON_OutlineFigure::UnitsPerEM() const
{
  return m_units_per_em;
}

double ON_OutlineFigure::AreaEstimate() const
{
  while (0 == m_area_status)
  {
    m_area_estimate = ON_DBL_QNAN;
    m_area_status = 7;

    const ON__UINT32 figure_end_dex = Internal_FigureEndDex(false);
    if (0 == figure_end_dex)
      break;

    const ON_OutlineFigurePoint* a = m_points.Array();

    const ON_OutlineFigurePoint figure_start = a[0];
    const ON_OutlineFigurePoint figure_end = a[figure_end_dex];

    if (
      ON_OutlineFigurePoint::Type::BeginFigureOpen == figure_start.m_point_type
      || ON_OutlineFigurePoint::Type::EndFigureOpen == figure_end.m_point_type
      || figure_end_dex <= 2
      )
    {
      m_area_estimate = 0.0;
      m_area_status = 1;
      if (
        ON_OutlineFigure::Type::Perimeter == m_figure_type
        || ON_OutlineFigure::Type::Unset == m_figure_type
        || ON_OutlineFigure::Type::Unknown == m_figure_type
        )
      {
        m_figure_type = ON_OutlineFigure::Type::NotPerimeter;
      }
      break;
    }

    ON_2dPoint cv[4], p0, p1;

    double quad[3][3];
    double cubic[3][4];

    quad[0][0] = ON_UNSET_VALUE;
    cubic[0][0] = ON_UNSET_VALUE;
    double twice_area = 0.0;

    p1 = figure_start.m_point;
    ON__UINT32 i;
    for ( i = 1; i < figure_end_dex; i++)
    {
      const ON_OutlineFigurePoint p = a[i];
      p0 = p1;
      p1 = p.m_point;

      if (ON_OutlineFigurePoint::Type::LineTo == p.m_point_type)
      {
        twice_area += Internal_DeltaArea(p0, p1);
        continue;
      }

      if (ON_OutlineFigurePoint::Type::QuadraticBezierPoint == p.m_point_type)
      {
        if (
          p.IsOffFigure()
          && i + 1 < figure_end_dex
          && p.m_point_type == a[i + 1].m_point_type
          &&  a[i + 1].IsOnFigure()
          )
        {
          // approximate quadratic with 4 line segments
          if (ON_UNSET_VALUE == quad[0][0])
          {
            for (int tdex = 1; tdex <= 3; tdex++)
            {
              const double t = 0.25 * tdex;
              //const double s = 1.0 - t;
              for (int cvdex = 0; cvdex < 3; cvdex++)
              {
                quad[tdex - 1][cvdex] = ON_EvaluateBernsteinBasis(2, cvdex, t);
              }
            }
          }
          cv[0] = p0;
          cv[1] = p1;
          cv[2] = a[++i].m_point;
          p1 = p0;
          for (int j = 0; j < 3; j++)
          {
            p0 = p1;
            p1 = quad[j][0] * cv[0] + quad[j][1] * cv[1] + quad[j][2] * cv[2];
            twice_area += Internal_DeltaArea(p0, p1);
          }
          p0 = p1;
          p1 = cv[2];
          twice_area += Internal_DeltaArea(p0, p1);
          continue;
        }
        // error
        break;
      }

      if (ON_OutlineFigurePoint::Type::CubicBezierPoint == p.m_point_type)
      {
        if (
          // approximate cubic with 4 line segments
          p.IsOffFigure()
          && i + 2 < figure_end_dex
          && p.m_point_type == a[i + 1].m_point_type
          && a[i + 1].IsOffFigure()
          && p.m_point_type == a[i + 2].m_point_type
          && a[i + 2].IsOnFigure()
          )
        {
          if (ON_UNSET_VALUE == cubic[0][0])
          {
            for (int tdex = 1; tdex <= 3; tdex++)
            {
              const double t = 0.25 * tdex;
              //const double s = 1.0 - t;
              for (int cvdex = 0; cvdex < 4; cvdex++)
              {
                cubic[tdex - 1][cvdex] = ON_EvaluateBernsteinBasis(3, cvdex, t);
              }
            }
          }
          cv[0] = p0;
          cv[1] = p1;
          cv[2] = a[++i].m_point;
          cv[3] = a[++i].m_point;
          p1 = p0;
          for (int j = 0; j < 3; j++)
          {
            p0 = p1;
            p1 = cubic[j][0] * cv[0] + cubic[j][1] * cv[1] + cubic[j][2] * cv[2] + cubic[j][3] * cv[3];
            twice_area += Internal_DeltaArea(p0, p1);
          }
          p0 = p1;
          p1 = cv[3];
          twice_area += Internal_DeltaArea(p0, p1);
          continue;
        }
        // error
        break;
      }

      break;
    }

    if (i != figure_end_dex)
    {
      ON_ERROR("Area calculation failed.");
      if (
        ON_OutlineFigure::Type::Perimeter == m_figure_type
        || ON_OutlineFigure::Type::Unset == m_figure_type
        || ON_OutlineFigure::Type::Unknown == m_figure_type
        )
      {
        m_figure_type = ON_OutlineFigure::Type::NotPerimeter;
      }
      break; // error
    }

    p0 = p1;
    p1 = figure_start.m_point;
    twice_area += Internal_DeltaArea(p0, p1);

    m_area_estimate = 0.5*twice_area;
    m_area_status = 1;
    break;
  }

  return m_area_estimate;
}


bool ON_OutlineFigure::ReverseFigure()
{
  const bool error_rc = false;

  const ON__UINT32 figure_end_dex = Internal_FigureEndDex(true);
  if (0 == figure_end_dex)
    return error_rc;

  const ON__UINT32 figure_start_dex = 0;

  ON_OutlineFigurePoint* a = m_points.Array();

  // Original beginning point
  const ON_OutlineFigurePoint B0 = a[figure_start_dex];

  // Original ending point
  const ON_OutlineFigurePoint E0 = a[figure_end_dex];

  for (ON__UINT32 i = figure_start_dex+1; i < figure_end_dex; i++)
  {
    if ( false == a[i].IsInteriorFigurePoint() )
    {
      // a[] contains errors, unsets, or embedded figures
      return error_rc;
    }
  }

  // New beginning point
  ON_OutlineFigurePoint B1 = a[figure_end_dex-1];
  B1.m_point_type = B0.m_point_type;


  // New ending point
  ON_OutlineFigurePoint E1 = B1;
  E1.m_point_type = E0.m_point_type;

  // shift internal type flags to account for segment reversal
  for (ON__UINT32 i = figure_start_dex+1; i < figure_end_dex; i++)
  {
    a[i - 1].m_point_type = a[i].m_point_type;
  }

  // reverse a[] order
  ON__UINT32 j = figure_end_dex-1;
  for (ON__UINT32 i = figure_start_dex; i < j; i++, j--)
  {
    ON_OutlineFigurePoint x = a[i];
    a[i] = a[j];
    a[j] = x;
  }

  // set new begin/end 
  a[figure_start_dex] = B1;
  a[figure_end_dex] = E1;

  if (ON_OutlineFigure::Orientation::Clockwise == m_orientation)
    m_orientation = ON_OutlineFigure::Orientation::CounterClockwise;
  else if (ON_OutlineFigure::Orientation::CounterClockwise == m_orientation)
    m_orientation = ON_OutlineFigure::Orientation::Clockwise;

  if (ON_IsValid(m_area_estimate) && 0.0 != m_area_estimate)
    m_area_estimate = -m_area_estimate;

  return true;
}

unsigned int ON_OutlineFigure::Internal_SegmentDegree(
  ON__UINT32 segment_start_dex
) const
{
  const ON__UINT32 count = m_points.UnsignedCount();  
  if (count < 2 || segment_start_dex > count-2)
    return 0;

  const ON_OutlineFigurePoint* a = m_points.Array();
  if (nullptr == a)
    return 0;

  const ON_OutlineFigurePoint p0 = a[segment_start_dex];
  if (false == p0.IsOnFigure())
    return 0;

  const ON_OutlineFigurePoint p1 = a[segment_start_dex+1];

  switch (p1.m_point_proximity)
  {
  case ON_OutlineFigurePoint::Proximity::OnFigure:
    if (ON_OutlineFigurePoint::Type::LineTo == p1.m_point_type || p1.IsEndFigurePoint())
      return 1;
    break;

  case ON_OutlineFigurePoint::Proximity::OffFigure:
    if (segment_start_dex + 2 < count)
    {
      const ON_OutlineFigurePoint p2 = a[segment_start_dex + 2];
      if (p2.m_point_type != p1.m_point_type || p2.m_figure_index != p1.m_figure_index)
        break;

      if (ON_OutlineFigurePoint::Type::QuadraticBezierPoint == p1.m_point_type)
      {
        if (p2.IsOnFigure())
          return 2;
      }
      else if (ON_OutlineFigurePoint::Type::CubicBezierPoint == p1.m_point_type)
      {
        if (false == p2.IsOffFigure())
          break;
        if (segment_start_dex + 3 >= count)
          break;
        const ON_OutlineFigurePoint p3 = a[segment_start_dex + 3];
        if (p3.m_point_type == p1.m_point_type && p3.IsOnFigure())
          return 3;
      }
    }
    break;
  default:
    break;
  }

  return 0;
}

ON_OutlineFigure::Orientation ON_OutlineFigure::FigureOrientation() const
{
  if (ON_OutlineFigure::Orientation::Unset == m_orientation)
  {
    const double area_estimate = AreaEstimate();
    const double area_tolerance = (m_short_tolerance > 0.0) ? (m_short_tolerance*m_short_tolerance) : 1e-10;
    if (fabs(area_estimate) <= area_tolerance)
      m_orientation = ON_OutlineFigure::Orientation::NotOriented;
    else if (area_estimate > 0.0)
      m_orientation = ON_OutlineFigure::Orientation::CounterClockwise;
    else if (area_estimate < 0.0)
      m_orientation = ON_OutlineFigure::Orientation::Clockwise;
    else
      m_orientation = ON_OutlineFigure::Orientation::Error;
  }
  return m_orientation;
}

unsigned int ON_OutlineFigure::GetFigureCurves(
  double scale,
  bool b3d,
  ON_SimpleArray< ON_Curve* >& figure_curves
  ) const
{
  ON_SimpleArray< ON_NurbsCurve* >& figure_nurbs_curves = *((ON_SimpleArray< ON_NurbsCurve* > *)&figure_curves);
  return GetFigureCurves(
    scale,
    b3d,
    figure_nurbs_curves
  );
}

unsigned int ON_OutlineFigure::GetFigureCurves(
  double scale,
  bool b3d,
  ON_SimpleArray< ON_NurbsCurve* >& figure_curves
) const
{
  if (false == Internal_HasValidEnds(false))
    return 0;

  const unsigned int figure_curves_count0 = figure_curves.UnsignedCount();

  const bool bApplyScale = ON_IsValid(scale) && scale > 0.0 && fabs(scale - 1.0) > 1.0e-5;
  if (false == bApplyScale)
    scale = 1.0;

  const ON__UINT32 figure_start_dex = 0;
  const ON__UINT32 figure_end_dex = m_points.UnsignedCount() - 1;

  //const ON_OutlineFigurePoint figure_start = m_points[figure_start_dex];
  //const ON_OutlineFigurePoint figure_end = m_points[figure_end_dex];
    
  // Find the end of this figure curve and estimate its NURBS curve segment_count.
  //bool bClosedFigure
  //  = ON_OutlineFigurePoint::Type::EndFigureOpen != figure_end.m_point_type
  //  && figure_end.IsOnFigure()
  //  && figure_start.m_point == figure_end.m_point
  //  ;

  // estimate number of NURBS curve segments
  figure_curves.Reserve(Internal_EstimateFigureSegmentCount());

  // get NURBS curve segments
  ON__UINT32 segment_start_dex = figure_start_dex;
  while (segment_start_dex < figure_end_dex)
  {
    ON__UINT32 i = 0;
    ON_NurbsCurve* figures_segment = Internal_GetFigureCurve(
      figure_end_dex,
      segment_start_dex,
      &i,
      b3d,
      nullptr
    );

    if (i <= segment_start_dex)
    {
      ON_ERROR("Failed to parse a figure segment.");
      //bClosedFigure = false;
      break;
    }

    if (nullptr != figures_segment)
    {
      if (bApplyScale)
        figures_segment->Scale(scale);
      figure_curves.Append(figures_segment);
    }
    //else
    //{
    //  bClosedFigure = false;
    //}

    segment_start_dex = i;
  }

  return (figure_curves.UnsignedCount() - figure_curves_count0);
}


void ON_Outline::Internal_ClearCachedValues() const
{
  m_bbox_status = 0;
  m_bbox = ON_BoundingBox::NanBoundingBox;
}

ON__UINT16 ON_Outline::AppendFigure(
  const ON_SimpleArray<ON_OutlineFigurePoint>& points
)
{
  return AppendFigure(points.UnsignedCount(), points.Array());
}

ON__UINT16 ON_Outline::AppendFigure(
  size_t point_count,
  const ON_OutlineFigurePoint* points
)
{
  const bool bSkipPointFigures = true;
  return Internal_AppendFigure(point_count, points, 0.0, bSkipPointFigures);
}

void ON_Outline::SetGlyphMetrics(
  ON_TextBox glyph_metrics
)
{
  m_glyph_metrics = glyph_metrics;
}

ON__UINT16 ON_Outline::Internal_AppendFigure(
  size_t point_count_as_size_t,
  const ON_OutlineFigurePoint* points,
  double short_tolerance,
  bool bSkipPointFigures
)
{
  if (0 == point_count_as_size_t)
    return 0;
  
  const unsigned int point_count = (unsigned int)point_count_as_size_t;

  if (point_count < 2 || nullptr == points)
  {
    ON_ERROR("Invalid point_count or points[] array.");
    return 0;
  }

  const ON_OutlineFigurePoint figure_start = points[0];
  if (
    false == figure_start.IsBeginFigurePoint()
    || false == figure_start.IsOnFigure()
    || false == figure_start.m_point.IsValid()
    )
  {
    ON_ERROR("points[0] is not a valid BeginFigure point.");
    return 0;
  }

  const ON_OutlineFigurePoint figure_end = points[point_count-1];
  if (
    false == figure_end.IsEndFigurePoint()
    || false == figure_end.IsOnFigure()
    || false == figure_end.m_point.IsValid()
    )
  {
    ON_ERROR("points[point_count-1] is not a valid EndFigure point.");
    return 0;
  }

  if (bSkipPointFigures && 2 == point_count && figure_start.m_point == figure_end.m_point)
    return 0;

  const bool bDoubleStrokeReductionTest
    = ON_OutlineFigure::Type::DoubleStroke == m_figure_type
    && point_count >= 3
    && ON_OutlineFigurePoint::Type::BeginFigureClosed == figure_start.PointType()
    && ON_OutlineFigurePoint::Type::EndFigureClosed == figure_end.PointType()
    && figure_start.m_point == figure_end.m_point;

  while (
    bDoubleStrokeReductionTest
    && point_count >= 4
    && m_figures.UnsignedCount() > 0
    )
  {
    ON_OutlineFigure& prev_figure = m_figures[m_figures.UnsignedCount() - 1];
    if (ON_OutlineFigure::Type::DoubleStroke != prev_figure.m_figure_type)
      break;
    if (point_count != (prev_figure.m_points.UnsignedCount()))
      break;
    const ON_OutlineFigurePoint prev_figure_start = prev_figure.m_points[0];
    const ON_OutlineFigurePoint prev_figure_end = prev_figure.m_points[point_count-1];
    if (ON_OutlineFigurePoint::Type::BeginFigureClosed != prev_figure_start.PointType())
      break;
    if (ON_OutlineFigurePoint::Type::EndFigureClosed != prev_figure_end.PointType())
      break;
    if (false == (prev_figure_start.m_point == figure_start.m_point) )
      break;
    if (false == (prev_figure_end.m_point == figure_start.m_point) )
      break;

    for (int dup_check_pass = 0; dup_check_pass < 2; dup_check_pass++)
    {
      bool bDuplicateLoop = true;
      for (unsigned int i = 0; i < point_count; i++)
      {
        const unsigned int j = (0 == dup_check_pass) ? i : (point_count - i - 1);
        const ON_OutlineFigurePoint& prev_point = prev_figure.m_points[j];
        bDuplicateLoop
          = (prev_point.IsOnFigure() == points[i].IsOnFigure() || prev_point.PointType() == points[i].PointType())
          && prev_point.m_point == points[i].m_point;
        if (false == bDuplicateLoop)
          break;
      }
      if (false == bDuplicateLoop)
        continue;

      // This figure is the double stroke duplicate of the previous figure (double stroke glphys like O).
      prev_figure.m_points[0].m_point_type = ON_OutlineFigurePoint::Type::BeginFigureOpen;
      if (
        prev_figure.m_points[point_count - 2].IsOnFigure()
        && false == (prev_figure_end.m_point == prev_figure.m_points[point_count - 2].m_point)
        )
      {
        ON_OutlineFigurePoint& new_figure_end = prev_figure.m_points.AppendNew();
        ON_OutlineFigurePoint& p = prev_figure.m_points[prev_figure.m_points.UnsignedCount() - 2];
        p.m_point_type = ON_OutlineFigurePoint::Type::LineTo;
        new_figure_end = p;
        new_figure_end.m_point_type = ON_OutlineFigurePoint::Type::EndFigureOpen;
      }
      prev_figure.m_figure_type = ON_OutlineFigure::Type::SingleStroke;
      return prev_figure.FigureIndex();
    }
    break;
  }
  
  ON_OutlineFigure& figure = m_figures.AppendNew();
  figure.m_figure_index = (ON__UINT16)m_figures.UnsignedCount();
  figure.m_short_tolerance = (short_tolerance>0.0) ? short_tolerance : m_short_tolerance;
  figure.m_points.Append((int)point_count, points);
  figure.m_points[0] = figure_start;
  figure.m_figure_type = m_figure_type;
  figure.m_units_per_em = this->m_units_per_em;

  while (bDoubleStrokeReductionTest)
  {
    // check for a double stroke figure like those in CamBam Stick fonts
    unsigned int i0 = 0;

    ON_2fPoint Qpoint(ON_2fPoint::NanPoint);
    bool bPrependQseg = false;
    unsigned int i1 = (unsigned int)(point_count - 1);
    if (i1 - 2 > 0)
    {
      if (
        false == figure.m_points[i1 - 2].IsOnFigure()
        && figure.m_points[i1 - 1].IsOnFigure()
        && figure.m_points[i1 - 1].m_point == figure_end.m_point
        )
      {
        i1--;
      }
      else if (
        figure.m_points[i1 - 2].IsOnFigure()
        && figure.m_points[i1 - 2].m_point == figure_start.m_point
        && figure.m_points[i1 - 1].IsOnFigure()
        && ON_OutlineFigurePoint::Type::LineTo == figure.m_points[i1 - 1].PointType()
        )
      {
        Qpoint = figure.m_points[i1 - 1].m_point;
        if (false == (Qpoint == figure_end.m_point))
          bPrependQseg = true;
        i1 -= 2;
      }
    }
   
    if (i0 >= i1)
      break;

    if (0 != (i1 - i0) % 2)
      break;

    while (i0 < i1)
    {
      if (false == (figure.m_points[i0].m_point == figure.m_points[i1].m_point))
        break;
      if (false == figure.m_points[i0].IsOnFigure() || false == figure.m_points[i1].IsOnFigure())
        break;
      i0++;
      i1--;
      while (
        i0 < i1
        && false == figure.m_points[i0].IsOnFigure()
        && false == figure.m_points[i1].IsOnFigure()
        && figure.m_points[i0].PointType() == figure.m_points[i1].PointType()
        && figure.m_points[i0].m_point == figure.m_points[i1].m_point
        )
      {
        i0++;
        i1--;
      }
    }
    if (i0 != i1)
      break;
    if (false == figure.m_points[i1].IsOnFigure())
      break;
    if (figure.m_points[i1].IsEndFigurePoint())
      break;
    if ((size_t)(i1 + 2) > point_count)
      break;

    if ( bPrependQseg )
    {
      if ((i1 + 3) > point_count)
        break;
      for (unsigned int i = i1 + 1; i > 0; i--)
        figure.m_points[i] = figure.m_points[i - 1];
      figure.m_points[0].m_point = Qpoint;
      figure.m_points[1].m_point_type = ON_OutlineFigurePoint::Type::LineTo;
      i1++;
    }
    figure.m_points[0].m_point_type = ON_OutlineFigurePoint::Type::BeginFigureOpen;
    figure.m_points[i1 + 1].m_point = figure.m_points[i1].m_point;
    figure.m_points[i1 + 1].m_point_type = ON_OutlineFigurePoint::Type::EndFigureOpen;
    figure.m_points[i1 + 1].m_point_proximity = ON_OutlineFigurePoint::Proximity::OnFigure;
    figure.m_figure_type = ON_OutlineFigure::Type::SingleStroke;
    figure.m_points.SetCount(i1 + 2);

    break;
  }

  m_sorted_figure_outer_orientation = ON_OutlineFigure::Orientation::Unset;
  return figure.m_figure_index;
}


ON_OutlineFigure::Type ON_Outline::FigureType() const
{
  return m_figure_type;
}

unsigned int ON_Outline::GetOutlineCurves(
    double scale,
    bool b3d,
    ON_ClassArray< ON_SimpleArray< ON_Curve* > >& outline_curves
    )
  const
{
  const ON__UINT32 outline_curves_count0 = outline_curves.UnsignedCount();

  const ON__UINT32 figure_count = m_figures.UnsignedCount();
  if (figure_count <= 0)
    return 0;

  outline_curves.Reserve(outline_curves.UnsignedCount() + figure_count);

  for ( ON__UINT32 i = 0; i <figure_count; i++ )
  {
    ON_SimpleArray< ON_Curve* >& figure_curves = outline_curves.AppendNew();

    m_figures[i].GetFigureCurves(scale, b3d, figure_curves);

    if (figure_curves.UnsignedCount() <= 0)
    {
      figure_curves.Remove();
      continue;
    }
  }

  return outline_curves.UnsignedCount() - outline_curves_count0;
}

ON__UINT32 ON_OutlineFigure::Internal_FigureEndDex(
  bool bLogErrors
  ) const
{
  const ON__UINT32 count = m_points.UnsignedCount();
  if (
    count >= 2
    && m_points[0].IsBeginFigurePoint()
    && m_points[count - 1].IsEndFigurePoint()
    )
  {
    return (count - 1);
  }

  if (bLogErrors)
  {
    ON_ERROR("Figure is missing start or end point.");    
  }
  return 0;
}

ON__UINT32 ON_OutlineFigure::Internal_EstimateFigureSegmentCount() const
{
  ON__UINT32 figure_end_dex = Internal_FigureEndDex(false);
  const ON__UINT32 count = m_points.UnsignedCount();
  if (0 == figure_end_dex || figure_end_dex >= count)
    return 0;

  ON_OutlineFigurePoint::Type point_type = ON_OutlineFigurePoint::Type::Unset;
  const ON_OutlineFigurePoint* a = m_points.Array();
  const ON_OutlineFigurePoint figure_end = a[figure_end_dex];
  if (
    figure_end.IsOnFigure()
    && ON_OutlineFigurePoint::Type::EndFigureClosed == figure_end.m_point_type
    && 0 != a[figure_end_dex - 1].IsOnFigure()
    && a[figure_end_dex - 1].m_point == figure_end.m_point
    )
  {
    // ignore final zero length segment
    figure_end_dex--;
  }

  int segment_count = 0;
  for (ON__UINT32 i = 1; i <= figure_end_dex; i++)
  {
    if (false == a[i].IsOnFigure() || a[i].m_point_type == point_type)
      continue;
    point_type = a[i].m_point_type;
    segment_count++;
  }

  return segment_count;
}

class ON_NurbsCurve* ON_OutlineFigure::Internal_GetFigureCurve(
    ON__UINT32 figure_end_dex,
    ON__UINT32 segment_start_dex,
    ON__UINT32* segment_end_dex,
    bool b3d,
    class ON_NurbsCurve* destination_curve
  ) const
{
  ON_NurbsCurve* nurbs_curve = destination_curve;

  if (nullptr != nurbs_curve)
  {
    nurbs_curve->m_dim = 0;
    nurbs_curve->m_is_rat = 0;
    nurbs_curve->m_order = 0;
    nurbs_curve->m_cv_count = 0;
  }

  *segment_end_dex = ON_UNSET_UINT_INDEX;

  if (
    segment_start_dex >= figure_end_dex
    || figure_end_dex >= m_points.UnsignedCount()
    || (figure_end_dex - segment_start_dex) < 1
    )
  {
    ON_ERROR("Invalid start and end indices.");
    return nullptr;
  }

  const ON_OutlineFigurePoint* a = m_points.Array();
  if (nullptr == a)
    return nullptr;

  const ON_OutlineFigurePoint segment_start = a[segment_start_dex];

  if (false == segment_start.IsOnFigure())
  {
    ON_ERROR("m_outline_points[segment_start_dex].m_bToPoint is false.");
    return nullptr;
  }

  if (0 == segment_start.m_figure_index)
  {
    ON_ERROR("m_outline_points[segment_start_dex].m_contour_index is zero.");
    return nullptr;
  }

  const unsigned int degree = Internal_SegmentDegree(segment_start_dex);
  if (0 == degree)
  {
    ON_ERROR("m_outline_points[segment_start_dex] or nearby subsequent points are non valid.");
    return nullptr;
  }

  ON__UINT32 i1 = segment_start_dex + degree; 
  while(i1+degree <= figure_end_dex)
  {
    if (segment_start.m_figure_index != a[i1].m_figure_index)
      break;
    if (degree != Internal_SegmentDegree(i1))
      break;
    if ( a[i1 - 1].m_point == a[i1 + 1].m_point )
    {
      if (degree == 1)
      {
        // double back line segment overlap
        break;
      }
      if ( 
        a[i1-degree].m_point == a[i1+degree].m_point 
        && (2 == degree || a[i1-2].m_point == a[i1+2].m_point)
        )
      {
        // double back bezier overlap
        break;
      }
    }
    i1 += degree;
  }

  *segment_end_dex = i1;

  if (1 == degree)
  {
    while (segment_start_dex < i1 && a[i1 - 1].m_point == a[i1].m_point)
      i1--;
    while (segment_start_dex < i1 && a[segment_start_dex].m_point == a[segment_start_dex + 1].m_point)
      segment_start_dex++;
    if (segment_start_dex >= i1)
      return nullptr; // zero length line segment
  }
  else
  {
    if (
      false == a[i1].IsEndFigurePoint()
      && i1 < figure_end_dex
      && a[i1 + 1].IsEndFigurePoint()
      && a[i1].m_point == a[i1 + 1].m_point
      )
    {
      // Happens when the last segment in a figure is a bezier that ends at the figure starting point (common).
      *segment_end_dex = i1 + 1;
    }
  }

  const int cv_count = (int)(i1 - segment_start_dex + 1);
  const int order = (int)(degree + 1);
  if (cv_count < order)
  {
    ON_ERROR("Bug in this function.");
    return nullptr;
  }
  const int dim = b3d ? 3 : 2;
  const int knot_count = cv_count + order - 2;

  // Create NURBS curve
  if (nullptr == nurbs_curve)
    nurbs_curve = new ON_NurbsCurve(dim, false, order, cv_count);
  else
  {
    nurbs_curve->ReserveCVCapacity(cv_count*dim);
    nurbs_curve->ReserveKnotCapacity(knot_count);
    nurbs_curve->m_dim = dim;
    nurbs_curve->m_is_rat = 0;
    nurbs_curve->m_order = order;
    nurbs_curve->m_cv_count = cv_count;
    nurbs_curve->m_cv_stride = dim;
  }

  double k = 0.0;
  double* knot = nurbs_curve->m_knot;
  double* knot1 = knot + knot_count;
  switch (degree)
  {
  case 1:
    while(knot < knot1)
    {
      *knot++ = k;
      k += 1.0;
    }
    break;

  case 2:
    while(knot < knot1)
    {
      *knot++ = k;
      *knot++ = k;
      k += 1.0;
    }
    break;

  case 3:
    while(knot < knot1)
    {
      *knot++ = k;
      *knot++ = k;
      *knot++ = k;
      k += 1.0;
    }
    break;
  }

  nurbs_curve->m_cv_count = 0;
  ON_3dPoint prev_cv = ON_3dPoint::NanPoint;
  int cv_dex = 0;
  ON__UINT32 i;
  for( i = segment_start_dex; i <= i1 && cv_dex < cv_count; i++)
  {
    const ON_3dPoint cv(a[i].m_point);
    if (cv_dex > 0 && 2 == order && prev_cv == cv)
      continue;
    nurbs_curve->SetCV(cv_dex, cv);
    cv_dex++;
    prev_cv = cv;
  }
  nurbs_curve->m_cv_count = cv_dex;

  if (i <= i1)
  {
    ON_ERROR("Bug in this function.");
  }

  if (nurbs_curve->m_cv_count < nurbs_curve->m_order)
  {
    ON_ERROR("Bug in this function.");
    if (destination_curve == nurbs_curve)
    {
      nurbs_curve->m_dim = 0;
      nurbs_curve->m_is_rat = 0;
      nurbs_curve->m_order = 0;
      nurbs_curve->m_cv_count = 0;
    }
    else
    {
      delete nurbs_curve;
    }
    nurbs_curve = nullptr;
  }

  return nurbs_curve;
}

#if 1

class Internal_OutlineFigureToPolyline
{
public:
  double m_2x_tolerance = 0.0; // 2*tolerance (2* saves multiplications)
  void(*m_PointCallbackFunc)(float x, float y, void*);
  void* m_context = nullptr;
  ON_2fPoint m_prev_point = ON_2fPoint::NanPoint;
  unsigned int m_point_count = 0;

  void AddPoint(ON_2fPoint pt)
  {
    if (pt.IsValid() && false == (pt == m_prev_point))
    {
      m_PointCallbackFunc(pt.x, pt.y, m_context );
      m_prev_point = pt;
      m_point_count++;
    }
  }

  void AddQuadraticBezier(ON_2fPoint bez_cv[3])
  {
    Internal_OutlineFigureToPolyline::Internal_AddBezier(0, 3, bez_cv);
  }

  void AddCubicBezier(ON_2fPoint bez_cv[4])
  {
    Internal_OutlineFigureToPolyline::Internal_AddBezier(0, 4, bez_cv);
  }

public:
  static void PointCallbackFunc2f(float x, float y, void*);
  static void PointCallbackFunc2d(float x, float y, void*);
  static void PointCallbackFunc3f(float x, float y, void*);
  static void PointCallbackFunc3d(float x, float y, void*);

private:
  void Internal_AddBezier(
    int level,
    int order,
    const ON_2fPoint bez_cv[] // bez[order] control points
  );
};

void Internal_OutlineFigureToPolyline::PointCallbackFunc2f(float x, float y, void* context)
{
  ((ON_SimpleArray<ON_2fPoint> *)(context))->Append(ON_2fPoint(x, y));
}

void Internal_OutlineFigureToPolyline::PointCallbackFunc2d(float x, float y, void* context)
{
  ((ON_SimpleArray<ON_2dPoint> *)(context))->Append(ON_2dPoint(x, y));
}

void Internal_OutlineFigureToPolyline::PointCallbackFunc3f(float x, float y, void* context)
{
  ((ON_SimpleArray<ON_3fPoint> *)(context))->Append(ON_3fPoint(x, y, 0.0));
}

void Internal_OutlineFigureToPolyline::PointCallbackFunc3d(float x, float y, void* context)
{
  ((ON_SimpleArray<ON_3dPoint> *)(context))->Append(ON_3dPoint(x, y, 0.0));
}

void Internal_OutlineFigureToPolyline::Internal_AddBezier( 
  int level,
  int order,
  const ON_2fPoint bez_cv[]
  )
{
  if ( order == 2 ) 
  {
    this->AddPoint(bez_cv[1]);
    return;
  }
  
  const float* cv0 = &bez_cv[0].x;

  if (3 == order )
  {
    if (level > 0)
    {
      if ( 
        fabs(bez_cv[0].x + bez_cv[2].x - 2.0*bez_cv[1].x) <= 2.0*m_2x_tolerance
        && fabs(bez_cv[0].y + bez_cv[2].y - 2.0*bez_cv[1].y) <= 2.0*m_2x_tolerance
        )
      {
        // bez midpoint is within tolerance of the chord from bez[0] to bez[2]
        this->AddPoint(bez_cv[2]);
        return;
      }
    }
  }
  else if ( 4 == order )
  {
    if ( level > 1 )
    {
      // x coordinate of bezier evaluated at t 0.5 is
      // a = 1/8*bez_cv[0].x + 3/8*bez_cv[1].x + 3/8*bez_cv[2].x + 1/8*bez_cv[3].x
      //
      // x coordinate of midpoint of chord is 
      // b = (bez_cv[0].x + bez_cv[3].x)/2
      //
      // a-b = c = 3/8(bez_cv[0].x - bez_cv[1].x - bez_cv[2].x + bez_cv[3].x)
      // c <= tol  if and only if 2*c <= 2*tol
      // 
      if ( 
        fabs( 0.75*(bez_cv[0].x - bez_cv[1].x - bez_cv[2].x + bez_cv[3].x) ) <= m_2x_tolerance
        && fabs( 0.75*(bez_cv[0].y - bez_cv[1].y - bez_cv[2].y + bez_cv[3].y) ) <= m_2x_tolerance 
        )
      {
        // bez midpoint is within tolerance of the chord from bez[0] to bez[3]
        this->AddPoint(bez_cv[3]);
        return;
      }
    }
  }
  else
  {
    // invalid order
    return;
  }

  // use de Casteljau to bisect bezier
  float f14[14];
  ON_2fPoint* cv  = (ON_2fPoint*)f14;

  float* cv1 = &cv[0].x;
  *cv1++ = *cv0++; *cv1++ = *cv0++; // cv[0] = bez_cv[0]
  cv1 += 2;
  *cv1++ = *cv0++; *cv1++ = *cv0++; // cv[2] = bez_cv[1]
  cv1 += 2;
  *cv1++ = *cv0++; *cv1++ = *cv0++; // cv[4] = bez_cv[2]
  if ( 4 == order )
  {
    cv1 += 2;
    *cv1++ = *cv0++; *cv1++ = *cv0++; // cv[6] = bez_cv[3]
  }

  float* cv2;
  for ( int k = 1;  k < order;  k++ ) 
  {
    cv1 = &cv[k].x;
    cv0 = cv1 - 2;
    cv2 = cv1 + 2;
    int i = order-k;
    while (i--) 
    {
      *cv1++ = 0.5f*(*cv0++ + *cv2++);
      *cv1++ = 0.5f*(*cv0++ + *cv2++);
      cv1 += 2; 
      cv0 += 2; 
      cv2 += 2; 
    } 
  }

  if ( level >= 8 ) 
  {
    // reached recursion limit
    // cv[order-1] = middle point = bez(1/2)
    this->AddPoint(cv[order-1]);
    // cv[2*order-2].x = end point = bez(1)
    this->AddPoint(cv[2*order-2]);
    return;
  }
  else
  {
    // add left half
    Internal_OutlineFigureToPolyline::Internal_AddBezier(level + 1, order, cv);

    // add right half
    Internal_OutlineFigureToPolyline::Internal_AddBezier(level + 1, order, cv + (order - 1));
  }

  return;
}

#endif

double ON_OutlineFigure::DefaultPolylineTolerance(
  double units_per_em
)
{
  const double default_polyline_tolerance 
    = (units_per_em > 0.0 && units_per_em < ON_UNSET_POSITIVE_VALUE && units_per_em != ON_UNSET_FLOAT)
    ? (units_per_em  / 1024.0) 
    : 1.0;
  return default_polyline_tolerance;
}

double ON_OutlineFigure::DefaultPolylineTolerance() const
{
  return ON_OutlineFigure::DefaultPolylineTolerance(m_units_per_em);
}

unsigned int ON_OutlineFigure::GetPolyline(
  double tolerance, 
  void(* PointCallbackFunc)(float x, float y, void *), 
  void * context
) const
{
  if (nullptr == PointCallbackFunc)
    return 0;

  const ON_OutlineFigurePoint* a = m_points.Array();
  const unsigned int c = m_points.UnsignedCount();
  if (nullptr == a || c <= 0)
    return 0;
  
  Internal_OutlineFigureToPolyline tp;
  tp.m_PointCallbackFunc = PointCallbackFunc;
  tp.m_context = context;

  const double default_tolerance = DefaultPolylineTolerance();

  tp.m_2x_tolerance = 2.0*((tolerance > 0.0) ? tolerance : default_tolerance);

  ON_2fPoint bez_cv[4];

  for (unsigned int i = 0; i < c; i++)
  {
    if (tp.m_point_count > 0)
    {
      if (
        ON_OutlineFigurePoint::Type::QuadraticBezierPoint == a[i].m_point_type
        && i + 1 < c
        && ON_OutlineFigurePoint::Type::QuadraticBezierPoint == a[i + 1].m_point_type
        )
      {
        bez_cv[0] = tp.m_prev_point;
        bez_cv[1] = a[i++].m_point;
        bez_cv[2] = a[i].m_point;
        tp.AddQuadraticBezier(bez_cv);
        continue;
      }

      if (
        ON_OutlineFigurePoint::Type::CubicBezierPoint == a[i].m_point_type
        && i + 2 < c
        && ON_OutlineFigurePoint::Type::CubicBezierPoint == a[i + 1].m_point_type
        && ON_OutlineFigurePoint::Type::CubicBezierPoint == a[i + 2].m_point_type
        )
      {
        bez_cv[0] = tp.m_prev_point;
        bez_cv[1] = a[i++].m_point;
        bez_cv[2] = a[i++].m_point;
        bez_cv[3] = a[i].m_point;
        tp.AddCubicBezier(bez_cv);
        continue;
      }
    }

    tp.AddPoint(a[i].m_point);
  }

  return tp.m_point_count;
}

unsigned int ON_OutlineFigure::GetPolyline(
  double tolerance,
  ON_SimpleArray<ON_2fPoint>& points
) const
{
  if (m_points.UnsignedCount() < 2)
    return 0;
  points.Reserve(3 * m_points.UnsignedCount());
  return GetPolyline(tolerance, Internal_OutlineFigureToPolyline::PointCallbackFunc2f, &points);
}

unsigned int ON_OutlineFigure::GetPolyline(
  double tolerance,
  ON_SimpleArray<ON_2dPoint>& points
) const
{
  if (m_points.UnsignedCount() < 2)
    return 0;
  points.Reserve(3 * m_points.UnsignedCount());
  return GetPolyline(tolerance, Internal_OutlineFigureToPolyline::PointCallbackFunc2d, &points);
}

unsigned int ON_OutlineFigure::GetPolyline(
  double tolerance,
  ON_SimpleArray<ON_3fPoint>& points
) const
{
  if (m_points.UnsignedCount() < 2)
    return 0;
  points.Reserve(3 * m_points.UnsignedCount());
  return GetPolyline(tolerance, Internal_OutlineFigureToPolyline::PointCallbackFunc3f, &points);
}

unsigned int ON_OutlineFigure::GetPolyline(
  double tolerance,
  ON_SimpleArray<ON_3dPoint>& points
) const
{
  if (m_points.UnsignedCount() < 2)
    return 0;
  points.Reserve(3 * m_points.UnsignedCount());
  return GetPolyline(tolerance, Internal_OutlineFigureToPolyline::PointCallbackFunc3d, &points);
}

static void ON_Internal_FigureWindingNumberCallback(float x, float y, void *context)
{
  ((ON_WindingNumber*)context)->AddBoundary(ON_2dPoint(x, y));
}

int ON_OutlineFigure::WindingNumber(
  ON_2fPoint winding_point
) const
{
  if (false == winding_point.IsValid())
    return 0;
 
  const ON_BoundingBox bbox = BoundingBox();
  if (false == (winding_point.x >= bbox.m_min.x && winding_point.x <= bbox.m_max.x))
    return false;
  if (false == (winding_point.y >= bbox.m_min.y && winding_point.y <= bbox.m_max.y))
    return false;

  const ON_OutlineFigurePoint* a = m_points.Array();
  const unsigned int c = m_points.UnsignedCount();
  if (nullptr == a || c <= 0)
    return 0;
  
  ON_WindingNumber wn;
  wn.SetWindingPoint(winding_point.x,winding_point.y);

  Internal_OutlineFigureToPolyline tp;
  tp.m_PointCallbackFunc = ON_Internal_FigureWindingNumberCallback;
  tp.m_context = &wn;
  tp.m_2x_tolerance = 2.0;

  ON_2fPoint bez_cv[4];

  ON_2fPoint bbox_min, bbox_max;

  for (unsigned int i = 0; i < c; i++)
  {
    if (tp.m_point_count > 0)
    {
      if (
        ON_OutlineFigurePoint::Type::QuadraticBezierPoint == a[i].m_point_type
        && i + 1 < c
        && ON_OutlineFigurePoint::Type::QuadraticBezierPoint == a[i + 1].m_point_type
        )
      {
        bez_cv[0] = tp.m_prev_point;
        bez_cv[1] = a[i++].m_point;
        bez_cv[2] = a[i].m_point;
       
        bbox_min = bez_cv[0];
        bbox_max = bbox_min;
        for (int j = 1; j < 2; j++)
        {
          if (bez_cv[j].x < bbox_min.x) 
            bbox_min.x = bez_cv[j].x;
          else if (bez_cv[j].x > bbox_max.x) 
            bbox_max.x = bez_cv[j].x;
          if (bez_cv[j].y < bbox_min.y) 
            bbox_min.y = bez_cv[j].y;
          else if (bez_cv[j].y > bbox_max.y) 
            bbox_max.y = bez_cv[j].y;
        }

        if (bbox.m_min.y <= winding_point.y && winding_point.y <= bbox.m_max.y)
        {
          if (bbox.m_min.x <= winding_point.x && winding_point.x <= bbox.m_max.x)
            tp.AddQuadraticBezier(bez_cv);
          else
            wn.AddBoundary(ON_2dPoint(tp.m_prev_point), ON_2dPoint(a[i].m_point));
        }
        tp.m_prev_point = bez_cv[2];
        continue;
      }

      if (
        ON_OutlineFigurePoint::Type::CubicBezierPoint == a[i].m_point_type
        && i + 2 < c
        && ON_OutlineFigurePoint::Type::CubicBezierPoint == a[i + 1].m_point_type
        && ON_OutlineFigurePoint::Type::CubicBezierPoint == a[i + 2].m_point_type
        )
      {
        bez_cv[0] = tp.m_prev_point;
        bez_cv[1] = a[i++].m_point;
        bez_cv[2] = a[i++].m_point;
        bez_cv[3] = a[i].m_point;

        bbox_min = bez_cv[0];
        bbox_max = bbox_min;
        for (int j = 1; j < 3; j++)
        {
          if (bez_cv[j].x < bbox_min.x) 
            bbox_min.x = bez_cv[j].x;
          else if (bez_cv[j].x > bbox_max.x) 
            bbox_max.x = bez_cv[j].x;
          if (bez_cv[j].y < bbox_min.y) 
            bbox_min.y = bez_cv[j].y;
          else if (bez_cv[j].y > bbox_max.y) 
            bbox_max.y = bez_cv[j].y;
        }

        if (bbox.m_min.y <= winding_point.y && winding_point.y <= bbox.m_max.y)
        {
          if (bbox.m_min.x <= winding_point.x && winding_point.x <= bbox.m_max.x)
            tp.AddCubicBezier(bez_cv);
          else
            wn.AddBoundary(ON_2dPoint(tp.m_prev_point), ON_2dPoint(a[i].m_point));
        }
        tp.m_prev_point = bez_cv[3];
        continue;
      }
    }

    if ( tp.m_point_count > 0 )
      wn.AddBoundary(ON_2dPoint(tp.m_prev_point), ON_2dPoint(a[i].m_point));

    tp.AddPoint(a[i].m_point);
  }

  return wn.WindingNumber();
}


bool  ON_Outline::IsValidOutline(
  bool bLogErrors
) const
{
  const ON__UINT32 figure_count = m_figures.UnsignedCount();
  if (figure_count <= 0)
  {
    if (bLogErrors) ON_ERROR("No figures in the outline");
    return false;
  }

  for (ON__UINT32 i = 0; i < figure_count; i++)
  {
    if (false == m_figures[i].IsValidFigure(bLogErrors))
      return false;
  }

  return true;
}

bool ON_OutlineAccumulator::EndOutline()
{
  return EndOutline(false, ON_Outline::DefaultOuterOrientation);
}

bool ON_OutlineAccumulator::EndOutline(
  bool bNegatePointY,
  ON_OutlineFigure::Orientation orientation
)
{
  if (1 != m_status)
    return false;

  AbandonCurrentFigure();

  m_status = 2;  

  ON_Outline& outline = Internal_Outline();

  if (bNegatePointY)
  {
    const ON__UINT32 figure_count = outline.m_figures.UnsignedCount();
    for (ON__UINT32 i = 0; i < figure_count; i++)
      outline.m_figures[i].NegateY();
  }

  if ( 
    ON_OutlineFigure::Type::SingleStroke != m_figure_type
    && ON_OutlineFigure::Type::DoubleStroke != m_figure_type
    )
  {
    const double desired_area_sign =
      ON_OutlineFigure::Orientation::CounterClockwise == orientation
      ? 1.0
      : (ON_OutlineFigure::Orientation::Clockwise == orientation ? -1.0 : 0.0);

    if (0.0 != desired_area_sign)
    {
      double outline_area = outline.AreaEstimate();
      if ((desired_area_sign*outline_area) < 0.0)
        outline.Reverse();

      outline.SortFigures(orientation);
    }
  }

  return true;
}

const ON_OutlineFigurePoint ON_OutlineAccumulator::ActiveFigureStartPoint() const
{
  return (m_figure_depth > 0) ? m_figure_start : ON_OutlineFigurePoint::Unset;
}

const ON_OutlineFigurePoint ON_OutlineAccumulator::ActiveFigureCurrentPoint() const
{
  return (m_figure_depth > 0) ? m_figure_current : ON_OutlineFigurePoint::Unset;
}


bool ON_OutlineAccumulator::BeginFigure(
  ON_OutlineFigurePoint::Type point_type,
  ON_2fPoint point_location
)
{
  if (1 != m_status)
  {
    ON_ERROR("ON_OutlineAccumulator is not initialized.");
    Internal_AccumulateError(true);
    return false;
  }

  if ( false == ON_OutlineFigurePoint::IsBeginFigurePointType(point_type) )
  {
    ON_ERROR("Invalid point_type for BeginFigure2f.");
    Internal_AccumulateError(true);
    return false;
  }

  return Internal_AccumulatePoint(point_type,point_location, true);
}


bool ON_OutlineAccumulator::AppendLine(
  ON_2fPoint point_location
)
{
  if (false == Internal_InFigure())
  {
    ON_ERROR("Not continuing a figure.");
    Internal_AccumulateError(true);
    return false;
  }

  if (false == m_figure_current.IsOnFigure())
  {
    ON_ERROR("Invalid start of line segment.");
    Internal_AccumulateError(true);
    return false;
  }

  if (m_figure_current.m_point == point_location)
  {
    // silently skip empty segments.
    return false;
  }

  return Internal_AccumulatePoint(
    ON_OutlineFigurePoint::Type::LineTo,
    point_location,
    true
  );
}



bool ON_OutlineAccumulator::AppendQuadraticBezier(
  ON_2fPoint cv1,
  ON_2fPoint cv2
)
{
  if (false == Internal_InFigure())
  {
    ON_ERROR("Not continuing a figure.");
    Internal_AccumulateError(true);
    return false;
  }

  if (false == m_figure_current.IsOnFigure())
  {
    ON_ERROR("Invalid start of quadratic bezier segment.");
    Internal_AccumulateError(true);
    return false;
  }

  const ON_2fPoint cv0 = m_figure_current.m_point;

  if (cv0 == cv1 && cv0 == cv2)
  {
    // silently skip empty segments
    return false;
  }

  if (cv0 == cv1 || cv2 == cv1)
    return AppendLine(cv2);

  if (cv0 == cv2)
  {
    // silently skip degenerate segments
    //ON_ERROR("Degenerate quadratic bezier segment.");
    return false;
  }

  const ON_OutlineFigurePoint::Type point_type = ON_OutlineFigurePoint::Type::QuadraticBezierPoint;

  const ON__UINT32 count0 = m_point_accumulator.UnsignedCount();
  const bool rc
    =  Internal_AccumulatePoint(point_type, cv1, false)
    && Internal_AccumulatePoint(point_type, cv2, true)
    ;
  if (false == rc)
  {
    m_figure_current = ON_OutlineFigurePoint::Error;
    if ( m_point_accumulator.UnsignedCount() > count0)
      m_point_accumulator.SetCount((int)count0);
  }

  return rc;
}

static bool Internal_IsQuadraticBezier(
  ON_2fPoint cv0,
  ON_2fPoint cv1,
  ON_2fPoint cv2,
  ON_2fPoint cv3,
  ON_2fPoint& qcv1
)
{  
  const double ftol = 1.0 / 4098.0;
  const double itol = 0.5*ftol;

  double s, t, c0, c1, c2, c3;

  // test x coordinate
  c0 = ((double)cv0.x);
  c1 = ((double)cv1.x);
  s = 0.5*(3.0*c1 - c0);

  c2 = ((double)cv2.x);
  c3 = ((double)cv3.x);
  t = 0.5*(3.0*c2 - c3);

  // q1x = candidate for quadratic cv
  s = (s == t) ? s : 0.5*(s + t);
  t = floor(s);
  if (t + 0.5 < s)
    t = ceil(s);
  const double q1x = fabs(s - t) <= itol ? t : s;
  
  // test to see if cv1.x was a result of degree increase
  t = (2.0*q1x + c0) / 3.0;
  if (!(fabs(t - c1) <= ftol))
    return false; 

  // test to see if cv2.x was a result of degree increase
  t = (2.0*q1x + c3) / 3.0;
  if (!(fabs(t - c2) <= ftol))
    return false; 

  // test y coordinate
  c0 = ((double)cv0.y);
  c1 = ((double)cv1.y);
  s = 0.5*(3.0*c1 - c0);

  c2 = ((double)cv2.y);
  c3 = ((double)cv3.y);
  t = 0.5*(3.0*c2 - c3);

  // q1y = candidate for quadratic cv
  s = (s == t) ? s : 0.5*(s + t);
  t = floor(s);
  if (t + 0.5 < s)
    t = ceil(s);
  const double q1y = fabs(s - t) <= itol ? t : s;

  // test to see if cv1.y was a result of degree increase
  t = (2.0*q1y + c0) / 3.0;
  if (!(fabs(t - c1) <= ftol))
    return false; 

  // test to see if cv2.y was a result of degree increase
  t = (2.0*q1y + c3) / 3.0;
  if (!(fabs(t - c2) <= ftol))
    return false; 
  
  // Cubic bezier is actually a quadratic and the internal quadratic control point has integer coordinates
  qcv1.x = (float)q1x;
  qcv1.y = (float)q1y;
  return true;
}

bool ON_OutlineAccumulator::AppendCubicBezier(
  ON_2fPoint cv1,
  ON_2fPoint cv2,
  ON_2fPoint cv3
)
{
  if (false == Internal_InFigure())
  {
    ON_ERROR("Not continuing a figure.");
    Internal_AccumulateError(true);
    return false;
  }    

  if (false == m_figure_current.IsOnFigure())
  {
    ON_ERROR("Invalid beginning of a quadratic bezeir segment.");
    Internal_AccumulateError(true);
    return false;
  }

  const ON_2fPoint cv0 = m_figure_current.m_point;

  if (cv0 == cv1 && cv0 == cv2 && cv0 == cv3)
  {
    // silently skip empty segments
    return false;
  }

  if (cv0 == cv3)
  {
    // Check for degenerate cubic (all cvs on a line segment)
    const double triangle_area2x
      = cv0.y*(cv2.x - cv1.x)
      + cv1.y*(cv0.x - cv2.x)
      + cv2.y*(cv1.x - cv0.x);
    const double tol = UnitsPerEM() / 16384.0;
    if (fabs(triangle_area2x) <= tol*tol)
    {
      // silently skip degenerate segments
      //ON_ERROR("Degenerate cubic bezier segment.");
      return false;
    }
  }

  // Some glyph outline API's including Microsoft's IDWrite::GetGlyphRunOutline()
  // convert quadratic beziers into to cubic beziers.
  // Every capital letter in the Microsoft Arial font uses quadratic beziers
  // an is an example of where this test helps yield higher quality results.
  ON_2fPoint qcv1;
  if (Internal_IsQuadraticBezier(cv0, cv1, cv2, cv3, qcv1))
  {
    return AppendQuadraticBezier(qcv1, cv3);
  }

  const ON_OutlineFigurePoint::Type point_type = ON_OutlineFigurePoint::Type::CubicBezierPoint;

  const ON__UINT32 count0 = m_point_accumulator.UnsignedCount();
  const bool rc
    =  Internal_AccumulatePoint(point_type, cv1, false)
    && Internal_AccumulatePoint(point_type, cv2, false)
    && Internal_AccumulatePoint(point_type, cv3, true)
    ;
  if (false == rc)
  {
    m_figure_current = ON_OutlineFigurePoint::Error;
    if ( m_point_accumulator.UnsignedCount() > count0)
      m_point_accumulator.SetCount((int)count0);
  }

  return rc;
}

bool ON_OutlineAccumulator::EndFigure(
  ON_OutlineFigurePoint::Type point_type
)
{
  if ( false == ON_OutlineFigurePoint::IsEndFigurePointType(point_type) )
  {
    ON_ERROR("Invalid point_type for EndFigure.");
    Internal_AccumulateError(true);
    return false;
  }

  if (false == Internal_InFigure())
  {
    ON_ERROR("Not continuing a figure.");
    Internal_AccumulateError(true);
    return false;
  }

  const bool rc = Internal_AccumulatePoint(point_type, ON_2fPoint::NanPoint, false);

  return rc;
}

bool ON_OutlineFigure::IsValidFigure(
  bool bLogErrors
) const
{
  const ON__UINT32 figure_end_dex = Internal_FigureEndDex(bLogErrors);
  if (0 == figure_end_dex)
  {
    return false;
  }

  const ON_OutlineFigurePoint* a = m_points.Array();


  const ON_OutlineFigurePoint figure_start = a[0];
  if (false == figure_start.IsBeginFigurePoint())
  {
    if ( bLogErrors ) ON_ERROR("m_points[0] is not a BeginFigure point.");
    return false;
  }
  if ( ON_OutlineFigurePoint::Type::BeginFigureUnknown == figure_start.m_point_type)
  {
    // Finished figures never have BeginFigureUnknown point type.
    if ( bLogErrors ) ON_ERROR("m_outline_points[figure_start_dex] is ON_OutlineFigurePoint::Type::BeginFigureUnknown.");
    return false;
  }

  const ON__UINT16 figure_id = figure_start.m_figure_index;
  if (0 == figure_id)
  {
    if ( bLogErrors ) ON_ERROR("BeginFigure point has 0 = m_contour_index.");
    return false;
  }

  const ON_OutlineFigurePoint figure_end = a[figure_end_dex];
  if (figure_id != figure_end.m_figure_index)
  {
    if ( bLogErrors ) ON_ERROR("BeginFigure and EndFigure points have different m_contour_index values.");
    return false;
  }

  if ( false == figure_start.IsOnFigure())
  {
    if ( bLogErrors ) ON_ERROR("BeginFigure point IsOnFigure() is false.");
    return false;
  }

  if (false == figure_end.IsOnFigure())
  {
    if ( bLogErrors ) ON_ERROR("EndFigure point IsOnFigure() is false.");
    return false;
  }

  const bool bClosedFigure = (ON_OutlineFigurePoint::Type::BeginFigureOpen != figure_start.m_point_type);
  if (bClosedFigure)
  {
    if (ON_OutlineFigurePoint::Type::EndFigureClosed != figure_end.m_point_type)
    {
      if ( bLogErrors ) ON_ERROR("Closed figure is not terminated with an EndFigureClosed point.");
      return false;
    }
    if (false == (figure_start.m_point == figure_end.m_point))
    {
      if ( bLogErrors ) ON_ERROR("Closed figure has different start and end points.");
      return false;
    }
  }
  else
  {
    if (ON_OutlineFigurePoint::Type::EndFigureOpen != figure_end.m_point_type)
    {
      if ( bLogErrors ) ON_ERROR("Open figure is not terminated with an EndFigureOpen point.");
      return false;
    }
  }

  // Validate EndFigure bToPoint setting.

  ON_OutlineFigurePoint p0, p1;
  p1 = figure_start;
  for (ON__UINT32 i = 1; i < figure_end_dex; i++)
  {
    p0 = p1;
    p1 = a[i];
    if (figure_id != p1.m_figure_index)
    {
      if (bLogErrors) ON_ERROR("BeginFigure and interior point have different m_contour_index values.");
      return false;
    }
    
    if (ON_OutlineFigurePoint::Type::LineTo == p1.m_point_type)
    {
      if (false == p1.IsOnFigure())
      {
        if (bLogErrors) ON_ERROR("LineTo point IsOnFigure() is false.");
        return false;
      }
      continue;
    }

    if (ON_OutlineFigurePoint::Type::QuadraticBezierPoint == p1.m_point_type)
    {
      if (false == p1.IsOffFigure())
      {
        if (bLogErrors) ON_ERROR("Interior QuadraticBezier point IsOffFigure() is false.");
        return false;
      }

      if (i + 1 >= figure_end_dex)
      {
        if (bLogErrors) ON_ERROR("Invalid QuadraticBezier segment.");
        return false;
      }

      p1 = a[++i];
      if (figure_id != p1.m_figure_index)
      {
        if (bLogErrors) ON_ERROR("BeginFigure and interior point have different m_contour_index values.");
        return false;
      }

      if (ON_OutlineFigurePoint::Type::QuadraticBezierPoint != p1.m_point_type)
      {
        if (bLogErrors) ON_ERROR("Invalid end of QuadraticBezier segment point type.");
        return false;
      }

      if (false == p1.IsOnFigure())
      {
        if (bLogErrors) ON_ERROR("End of QuadraticBezier point IsOnFigure() is false.");
        return false;
      }
      continue;
    }

    if (ON_OutlineFigurePoint::Type::CubicBezierPoint == p1.m_point_type)
    {
      if (false == p1.IsOffFigure())
      {
        if (bLogErrors) ON_ERROR("Interior CubicBezierPoint point IsOffFigure() is false.");
        return false;
      }

      for (int cv_dex = 2; cv_dex <= 3; cv_dex++)
      {
        if (i + 1 >= figure_end_dex)
        {
          if (bLogErrors) ON_ERROR("Invalid CubicBezierPoint segment.");
          return false;
        }

        p1 = a[++i];
        if (figure_id != p1.m_figure_index)
        {
          if (bLogErrors) ON_ERROR("BeginFigure and interior point have different m_contour_index values.");
          return false;
        }

        if (ON_OutlineFigurePoint::Type::CubicBezierPoint != p1.m_point_type)
        {
          if (bLogErrors) ON_ERROR("Invalid end of QuadraticBezier segment point type.");
          return false;
        }

        if (2 == cv_dex)
        {
          if (false == p1.IsOffFigure())
          {
            if (bLogErrors) ON_ERROR("Interior CubicBezierPoint point IsOffFigure() is false.");
            return false;
          }
        }
        else
        {
          if (false == p1.IsOnFigure())
          {
            if (bLogErrors) ON_ERROR("End of QuadraticBezier point IsOnFigure() is false.");
            return false;
          }
        }
      }
      continue;
    }

    if (bLogErrors) ON_ERROR("Invalid point type for figure interior.");
    return false;
  }

  return true;
}

const ON_Outline& ON_OutlineAccumulator::Outline() const
{
  return (nullptr == m_outline) ? *m_outline : ON_Outline::Unset;
}

ON_Outline& ON_OutlineAccumulator::Internal_Outline()
{
  if (nullptr == m_outline)
  {
    m_outline = new ON_Outline();
    m_outline->SetUnitsPerEM(m_units_per_em);
  }
  return *m_outline;
}

bool ON_OutlineAccumulator::Internal_InFigure() const
{
  if (
    1 == m_status
    && 1 == m_figure_depth
    && m_point_accumulator.UnsignedCount() > 0
    && m_figure_start.IsBeginFigurePoint()
    && m_figure_start.m_figure_index > 0
    && m_figure_current.m_figure_index == m_figure_start.m_figure_index
    && (m_figure_prev.m_figure_index == m_figure_start.m_figure_index || 1 == m_point_accumulator.UnsignedCount())
    )
  {
    return true;
  }
  return false;
}

void ON_OutlineAccumulator::Internal_AccumulateError(
  bool bCancelCurrentFigure
)
{
  m_error_count++;
  if (bCancelCurrentFigure)
  {
    m_figure_depth = 0;
  }
}

void ON_OutlineAccumulator::ON_OutlineAccumulator::AbandonCurrentFigure()
{
  m_figure_depth = 0;
  m_point_accumulator.SetCount(0);
  m_figure_start = ON_OutlineFigurePoint::Unset;
  m_figure_prev = ON_OutlineFigurePoint::Unset;
  m_figure_current = ON_OutlineFigurePoint::Unset;
}

bool ON_OutlineAccumulator::Internal_AccumulatePoint(
  ON_OutlineFigurePoint::Type point_type,
  ON_2fPoint point_location,
  bool bPointInBoundingBox
)
{
  int state = 0; // 0 = error, 1 = begin figure, 2 = continue figure, 3 = end figure

  switch (point_type)
  {
  case ON_OutlineFigurePoint::Type::Unset:
    ON_ERROR("point_type is Unset");
    break;

  case ON_OutlineFigurePoint::Type::QuadraticBezierPoint:
  case ON_OutlineFigurePoint::Type::CubicBezierPoint:
  case ON_OutlineFigurePoint::Type::LineTo:
    state = 2; // continue a figure
    break;

  case ON_OutlineFigurePoint::Type::BeginFigureUnknown:
  case ON_OutlineFigurePoint::Type::BeginFigureOpen:
  case ON_OutlineFigurePoint::Type::BeginFigureClosed:
    if ( ON_OutlineFigure::Type::SingleStroke == m_figure_type )
      point_type = ON_OutlineFigurePoint::Type::BeginFigureOpen;
    bPointInBoundingBox = true;
    state = 1; // begin a figure
    break;

  //case ON_OutlineFigurePoint::Type::LineToCloseContour:
  case ON_OutlineFigurePoint::Type::EndFigureClosed:
    if ( ON_OutlineFigure::Type::SingleStroke == m_figure_type )
      point_type = ON_OutlineFigurePoint::Type::EndFigureOpen;
    state = 3; // end a figure - point_location input parameter is ignored.
    break;

  case ON_OutlineFigurePoint::Type::EndFigureOpen:
    state = 3; // end a figure - point_location input parameter is ignored.
    break;

  case ON_OutlineFigurePoint::Type::Error:
    break;

  default:
    ON_ERROR("point_type is invalid.");
    break;
  }

  switch (state)
  {
  case 0: // error
    break;

  case 1: // begin a figure
    if (0 != m_figure_depth)
    {
      ON_ERROR("Beginning a figure in an unexpected state.");
      Internal_AccumulateError(true);
    }
    bPointInBoundingBox = true;
    m_point_accumulator.SetCount(0);
    if (0 == m_point_accumulator.Capacity())
      m_point_accumulator.Reserve(64);
    m_figure_depth = 1;
    m_figure_start = ON_OutlineFigurePoint::Unset;
    m_figure_prev = ON_OutlineFigurePoint::Unset;
    m_figure_current = ON_OutlineFigurePoint::Unset;
    break;

  case 2: // continue a figure
    if ( false == Internal_InFigure() )
    {
      ON_ERROR("Continuing a figure in an unexpected state.");
      state = 0;
    }
    else
    {
      if (ON_OutlineFigurePoint::Type::LineTo == point_type)
        bPointInBoundingBox = true;
    }
    break;

  case 3: // end a figure
    if ( false == Internal_InFigure() )
    {
      ON_ERROR("Ending a figure in an unexpected state.");
      state = 0;
    }
    else
    {
      if ( ON_OutlineFigurePoint::Type::BeginFigureUnknown == m_figure_start.m_point_type )
      {
        if ( ON_OutlineFigurePoint::Type::EndFigureClosed == point_type )
          m_figure_start.m_point_type = ON_OutlineFigurePoint::Type::BeginFigureClosed;
        else if ( ON_OutlineFigurePoint::Type::EndFigureOpen == point_type )
          m_figure_start.m_point_type = ON_OutlineFigurePoint::Type::BeginFigureOpen;
        ON_OutlineFigurePoint q = m_point_accumulator[0];
        if (
          ON_OutlineFigurePoint::Type::BeginFigureUnknown == q.m_point_type
          && m_figure_start.m_figure_index == q.m_figure_index
          && m_figure_start.m_point == q.m_point
          )
        {
          q.m_point_type = m_figure_start.m_point_type;
          m_point_accumulator[0] = q;
        }
      }
      
      if (ON_OutlineFigurePoint::Type::BeginFigureOpen == m_figure_start.m_point_type)
      {
        if (ON_OutlineFigurePoint::Type::EndFigureOpen != point_type)
        {
          ON_ERROR("EndFigureClosed used to finish an open figure");
          point_type = ON_OutlineFigurePoint::Type::EndFigureOpen;
        }
        point_location = m_figure_current.m_point;
      }
      else
      {
        if (ON_OutlineFigurePoint::Type::EndFigureClosed != point_type)
        {
          ON_ERROR("EndFigureOpen used to finish an closed figure");
          point_type = ON_OutlineFigurePoint::Type::EndFigureClosed;
        }
        point_location = m_figure_start.m_point;
      }
      bPointInBoundingBox = true;
    }
    m_figure_depth = 0;
    break;

  default: // invalid value for state
    {
      ON_ERROR("Bug in this function.");
      state = 0;
    }
    break;
  }

  if (0 == state)
  {
    Internal_AccumulateError(false);
    m_figure_current = ON_OutlineFigurePoint::Unset;
    return false;
  }

  // Accumulate the information that goes with this point.
  ON_Outline& outline = Internal_Outline();

  const ON__UINT16 figure_index = (ON__UINT16)(1+outline.FigureCount());


  ON_OutlineFigurePoint gp;
  gp.m_point_type = point_type;
  gp.m_point_proximity = bPointInBoundingBox ? ON_OutlineFigurePoint::Proximity::OnFigure : ON_OutlineFigurePoint::Proximity::OffFigure;
  gp.m_figure_index = figure_index;
  gp.m_point = point_location;

  m_figure_prev = m_figure_current;
  m_figure_current = gp;

  if (state <= 2)
  {
    if (1 == state)
    {
      m_figure_start = gp;
      m_figure_prev = ON_OutlineFigurePoint::Unset;
    }
  }   

  m_point_accumulator.Append(gp);

  if (3 == state)
  {
    outline.AppendFigure(m_point_accumulator);
    AbandonCurrentFigure();
  }
    
  // ready for the next point.
  return true;
}

bool ON_FontGlyph::GetOutline(
  bool bSingleStrokeFont,
  class ON_Outline& outline
) const
{
  outline = ON_Outline::Unset;
  const ON_Font* font = Font();
  if (nullptr == font)
    return false;

  // When it comes to the difference between a single stroke and a double stroke font,
  // users and programmers are confused most of the time. This code protects
  // them from the consequences of that confusion.
  ON_OutlineFigure::Type font_figure_type = font->OutlineFigureType();
  if (ON_OutlineFigure::Type::SingleStroke == font_figure_type)
    bSingleStrokeFont = true;
  else if (ON_OutlineFigure::Type::DoubleStroke == font_figure_type)
    bSingleStrokeFont = false;
  else if (bSingleStrokeFont)
    font_figure_type = ON_OutlineFigure::Type::SingleStroke;

  bool rc = false;
  if (nullptr != ON_Font::Internal_CustomGetGlyphOutlineFunc)
  {
    rc = ON_Font::Internal_CustomGetGlyphOutlineFunc(
      this,
      bSingleStrokeFont,
      outline
    );
  }
  else
  {
#if defined(ON_OS_WINDOWS_GDI)
    // Use Windows Direct Write based tools
    rc = ON_WindowsDWriteGetGlyphOutline(
      this,
      font_figure_type,
      outline
    );
#elif defined(ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
    // Use Apple Core Text based tools
    rc = ON_AppleFontGetGlyphOutline(
      this,
      font_figure_type,
      outline
    );
#elif defined(OPENNURBS_FREETYPE_SUPPORT)
    // Look in opennurbs_system_runtime.h for the correct place to define OPENNURBS_FREETYPE_SUPPORT.
    // Do NOT define OPENNURBS_FREETYPE_SUPPORT here or in your project setting ("makefile").
    // Use freetype based tools (least reliable results).
    // Freetype is basically a file reading utility that can parse outline 
    // information in older formats of font files. It fails on newer formats 
    // and it also commonly fails to correctly map UNICODE code points to 
    // glyph indices. Freetype should only be used as a last resort.
    rc = ON_FreeTypeGetGlyphOutline(
      this,
      font_figure_type,
      outline
    );
#endif
  }

  return (rc || outline.FigureCount() > 0);
}

bool ON_FontGlyph::GetGlyphContours(
  bool bSingleStrokeFont,
  double height_of_capital,
  ON_ClassArray< ON_SimpleArray< ON_Curve* > >& glyph_contours,
  ON_BoundingBox* glyph_bbox,
  ON_3dVector* glyph_advance
) const
{
  const ON_Font* font = Font();
  if (nullptr == font)
    return false;

  ON_Outline outline;
  GetOutline(bSingleStrokeFont, outline);

  const ON_FontMetrics fm = font->FontUnitFontMetrics();
  double scale = 1.0;
  if (height_of_capital > 0.0 && height_of_capital < ON_UNSET_POSITIVE_FLOAT)
  {
    scale = fm.GlyphScale(height_of_capital);
  }
  else if ( 
    ON_UNSET_VALUE == height_of_capital
    || ON_UNSET_POSITIVE_VALUE == height_of_capital
    || ON_UNSET_FLOAT == height_of_capital
    || ON_UNSET_POSITIVE_FLOAT == height_of_capital
    )
  {
    // return results in font design units
    scale = 1.0;
  }
  else
  {
    // normalized units.
    const double font_UPM = font->FontUnitFontMetrics().AscentOfCapital();
    if ( font_UPM > 0.0 &&  font_UPM < ON_UNSET_POSITIVE_FLOAT )
    scale = ((double)ON_Font::AnnotationFontCellHeight) / font_UPM;
  }

  unsigned int rc = outline.GetOutlineCurves(
    scale,
    true, // 3d curves
    glyph_contours
  );

  const ON_TextBox glyph_metrics = outline.GlyphMetrics();

  if (nullptr != glyph_advance)
    *glyph_advance = scale * ON_3dVector(glyph_metrics.m_advance.i, glyph_metrics.m_advance.j, 0.0);

  if (nullptr != glyph_bbox)
    *glyph_bbox = ON_BoundingBox(
      scale*ON_3dPoint(glyph_metrics.m_bbmin.i, glyph_metrics.m_bbmin.j, 0.0),
      scale*ON_3dPoint(glyph_metrics.m_bbmax.i, glyph_metrics.m_bbmax.j, 0.0)
    );

  return (rc > 0);
}



