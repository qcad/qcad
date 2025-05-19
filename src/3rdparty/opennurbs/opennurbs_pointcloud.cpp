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

ON_OBJECT_IMPLEMENT(ON_PointCloud, ON_Geometry, "2488F347-F8FA-11d3-BFEC-0010830122F0");


ON_3dPoint& ON_PointCloud::operator[](int i)
{
  return m_P[i];
}

const ON_3dPoint& ON_PointCloud::operator[](int i) const
{
  return m_P[i];
}

ON_3dPoint ON_PointCloud::Point( ON_COMPONENT_INDEX ci ) const
{
  return (ON_COMPONENT_INDEX::pointcloud_point == ci.m_type && ci.m_index >= 0 && ci.m_index < m_P.Count() )
    ? m_P[ci.m_index]
    : ON_3dPoint::UnsetPoint;
}

ON_PointCloud::ON_PointCloud() : m_flags(0)
{
  m_hidden_count=0;
}

ON_PointCloud::ON_PointCloud( int capacity ) : m_P(capacity), m_flags(0)
{
  m_hidden_count=0;
}

ON_PointCloud::ON_PointCloud( const ON_PointCloud& src )
{
  *this = src;
}

ON_PointCloud& ON_PointCloud::operator=( const ON_PointCloud& src )
{
  if ( this != &src ) {
    Destroy();
    ON_Geometry::operator=(src);
    m_P = src.m_P;
    m_H = src.m_H;
    m_C = src.m_C;
    m_V = src.m_V;
    m_N = src.m_N;
    m_hidden_count = src.m_hidden_count;

    m_plane = src.m_plane;
    m_bbox = src.m_bbox;
    m_flags = src.m_flags;
  }
  return *this;
}

ON_PointCloud::ON_PointCloud(const ON_3dPoint* P0, int count) : m_P(count)
{
  m_P.Create(3, false, count, 3, P0[0]);
}

ON_PointCloud::ON_PointCloud(const double* P0, int dim, bool is_rat, int count) : m_P(count)
{
  m_P.Create(dim, is_rat, count, dim + is_rat, P0);
}

ON_PointCloud::~ON_PointCloud()
{
  Destroy();
}

void ON_PointCloud::Destroy()
{
  m_H.Destroy();
  m_C.Destroy();
  m_V.Destroy();
  m_N.Destroy();
  m_P.Destroy();
  m_hidden_count=0;
  m_flags = 0;
  m_bbox.Destroy();
}

void ON_PointCloud::EmergencyDestroy()
{
  m_P.EmergencyDestroy();
  m_C.EmergencyDestroy();
  m_V.EmergencyDestroy();
  m_H.EmergencyDestroy();
  m_N.EmergencyDestroy();
  m_hidden_count=0;
  m_flags = 0;
  m_bbox.Destroy();
}

bool ON_PointCloud::IsValid( ON_TextLog* text_log ) const
{
  return ( m_P.Count() > 0 ) ? true : false;
}

void ON_PointCloud::Dump( ON_TextLog& dump ) const
{
  // Aug 23, 2016 Tim - Fix for RH-35351
  // half_max is arbitrary, if you want more than 100 points 
  // change it to your liking. This is to prevent all of the 
  // points from displaying when you have a very large point 
  // cloud, like a billion. (see model on RH-35348)
  const int half_max = 50;

  int i;
  const bool bHasNormals = HasPointNormals();
  const bool bHasColors = HasPointColors();
  const bool bHasHiddenPoints = (HiddenPointCount() > 0);
  const int point_count = m_P.Count();
  dump.Print("ON_PointCloud: %d points\n",point_count);
  dump.PushIndent();
  for ( i = 0; i < point_count; i++ ) 
  {
    if (i == half_max && 2 * half_max < point_count)
    {
      dump.Print("...\n");
      i = point_count - half_max;
    }
    else
    {
      dump.Print("point[%2d]: ", i);
      dump.Print(m_P[i]);
      if (bHasNormals)
      {
        dump.Print(", normal = ");
        dump.Print(m_N[i]);
      }
      if (bHasColors)
      {
        dump.Print(", color = ");
        dump.PrintRGB(m_C[i]);
      }
      if (bHasHiddenPoints && m_H[i])
      {
        dump.Print(" (hidden)");
      }
      dump.Print("\n");
    }
  }
  dump.PopIndent();
}

bool ON_PointCloud::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.Write3dmChunkVersion(1,2);

  if (rc) rc = file.WriteArray( m_P );
  if (rc) rc = file.WritePlane( m_plane );
  if (rc) rc = file.WriteBoundingBox( m_bbox );
  if (rc) rc = file.WriteInt( m_flags);

  // added for 1.1  (7 December 2005)
  if (rc) rc = file.WriteArray(m_N);
  if (rc) rc = file.WriteArray(m_C);


  // added for 1.2  (8 August 2016)
  if (rc) rc = file.WriteArray(m_V);

  return rc;
}

bool ON_PointCloud::Read( ON_BinaryArchive& file )
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if (rc && major_version == 1 ) 
  {
    if (rc) rc = file.ReadArray( m_P );
    if (rc) rc = file.ReadPlane( m_plane );
    if (rc) rc = file.ReadBoundingBox( m_bbox );
    if (rc) rc = file.ReadInt( &m_flags);

    if (rc && minor_version >= 1 )
    {
      if (rc) rc = file.ReadArray( m_N );
      if (rc) rc = file.ReadArray( m_C );
      if (rc && minor_version >= 2)
      {
        rc = file.ReadArray( m_V );
      }
    }
  }
  return rc;
}

ON::object_type ON_PointCloud::ObjectType() const
{
  return ON::pointset_object;
}

unsigned int ON_PointCloud::SizeOf() const
{
  // Dale Lear fixed this function in April 2021.
  // Before that all point clouds were reported to have 
  // ON_Geometry::SizeOf() bytes.

  size_t sz = ON_Geometry::SizeOf();

  sz += (sizeof(*this) - sizeof(ON_Geometry));
  sz += (size_t)(m_P.SizeOfArray());
  sz += (size_t)(m_N.SizeOfArray());
  sz += (size_t)(m_C.SizeOfArray());
  sz += (size_t)(m_V.SizeOfArray());
  sz += (size_t)(m_H.SizeOfArray());

  // Avoid overflowing 4 byte unsigned int
  // and hope the consumer of this information is 
  // converting back to size_t before doing arithmetic.
  // The low 4 bytes are zeroed so small additions won't
  // overflow unsigned int.
  return (sz > 0xFFFF0000U) ? 0xFFFF0000U : ((unsigned int)sz);
}


int ON_PointCloud::Dimension() const
{
  return 3;
}

bool ON_PointCloud::GetBBox( // returns true if successful
       double* boxmin,    // minimum
       double* boxmax,    // maximum
       bool bGrowBox  // true means grow box
       ) const
{
  if ( !m_bbox.IsValid() ) {
    m_P.GetBBox( (double*)&m_bbox.m_min.x, (double*)&m_bbox.m_max.x, false );
  }
  bool rc = m_bbox.IsValid();
  if (rc) {
    if ( bGrowBox ) {
      if ( boxmin ) {
        if ( boxmin[0] > m_bbox.m_min.x ) boxmin[0] = m_bbox.m_min.x;
        if ( boxmin[1] > m_bbox.m_min.y ) boxmin[1] = m_bbox.m_min.y;
        if ( boxmin[2] > m_bbox.m_min.z ) boxmin[2] = m_bbox.m_min.z;
      }
      if ( boxmax ) {
        if ( boxmax[0] < m_bbox.m_max.x ) boxmax[0] = m_bbox.m_max.x;
        if ( boxmax[1] < m_bbox.m_max.y ) boxmax[1] = m_bbox.m_max.y;
        if ( boxmax[2] < m_bbox.m_max.z ) boxmax[2] = m_bbox.m_max.z;
      }
    }
    else {
      if ( boxmin ) {
        boxmin[0] = m_bbox.m_min.x;
        boxmin[1] = m_bbox.m_min.y;
        boxmin[2] = m_bbox.m_min.z;
      }
      if ( boxmax ) {
        boxmax[0] = m_bbox.m_max.x;
        boxmax[1] = m_bbox.m_max.y;
        boxmax[2] = m_bbox.m_max.z;
      }
    }
  }
  return rc;
}

bool ON_PointCloud::Transform( 
       const ON_Xform& xform
       )
{
  TransformUserData(xform);
  bool rc = m_P.Transform(xform);
  if (rc && HasPlane() )
    rc = m_plane.Transform(xform);
  m_bbox.Destroy();
  return rc;
}

bool ON_PointCloud::IsDeformable() const
{
  return true;
}

bool ON_PointCloud::MakeDeformable()
{
  return true;
}

bool ON_PointCloud::SwapCoordinates(
      int i, int j        // indices of coords to swap
      )
{
  bool rc = m_P.SwapCoordinates(i,j);
  if ( rc && HasPlane() ) {
    rc = m_plane.SwapCoordinates(i,j);
  }
  if ( rc && m_bbox.IsValid() ) {
    rc = m_bbox.SwapCoordinates(i,j);
  }
  return rc;
}

int ON_PointCloud::PointCount() const
{
  return m_P.Count();
}

void ON_PointCloud::AppendPoint( const ON_3dPoint& pt )
{
  m_P.Append(pt);
}

void ON_PointCloud::InvalidateBoundingBox()
{
  m_bbox.Destroy();
}

void ON_PointCloud::SetOrdered(bool b)
{
  if ( b ) {
    m_flags |= 1;
  }
  else {
    m_flags &= 0xFFFFFFFE;
  }
}

bool ON_PointCloud::IsOrdered() const
{
  return (m_flags & 1) ? true : false;
}

bool ON_PointCloud::HasPlane() const
{
  return ( m_flags&2) ? true : false;
}

void ON_PointCloud::SetPlane( const ON_Plane& plane )
{
  m_plane = plane;
  if ( m_plane.IsValid() ) {
    m_flags |= 2;
  }
  else {
    m_flags &= 0xFFFFFFFD;
  }
}

const ON_Plane& ON_PointCloud::Plane()
{
  return m_plane;
}





double ON_PointCloud::Height(int i)
{
  return (m_P[i] - m_plane.origin)*m_plane.zaxis;
}

bool ON_GetClosestPointInPointList( 
          int point_count,
          const ON_3dPoint* point_list,
          ON_3dPoint P,
          int* closest_point_index
          )
{
  bool rc = false;
  if ( point_count>0 && 0 != point_list && closest_point_index )
  {
    double d = 1.0e300;
    double d2 = 1.0e300;
    double x,e;
    int i;
    int best_i = -1;
    //const double* pl = &point_list[0].x;
    for ( i = point_count; i--; point_list++ )
    {
      e = d2;
      x = point_list->x - P.x;
      e = x*x;
      if ( e >= d2 ) continue;
      x = point_list->y - P.y;
      e += x*x;
      if ( e >= d2 ) continue;
      x = point_list->z - P.z;
      e += x*x;
      if ( e >= d2 ) continue;
      d2 = (1.0+ON_SQRT_EPSILON)*e;
      e = P.DistanceTo(*point_list);
      if ( e < d )
      {
        d = e;
        best_i = point_count-i-1;
      }
    }
    if ( best_i >= 0 )
    {
      if ( closest_point_index )
        *closest_point_index = best_i;
      rc = true;
    }
  }
  return rc;
}

bool ON_3dPointArray::GetClosestPoint( 
          ON_3dPoint P,
          int* closest_point_index,
          double maximum_distance
          ) const
{
  int i;

  bool rc = ON_GetClosestPointInPointList( m_count, m_a , P, &i );

  if (rc)
  {
    if ( maximum_distance > 0.0 && P.DistanceTo(m_a[i]) > maximum_distance )
    {
      rc = false;
    }
    else if ( closest_point_index )
    {
      *closest_point_index = i;
    }
  }

  return rc;
}

bool ON_PointCloud::HasPointColors() const
{
  const unsigned int point_count = m_P.UnsignedCount();
  return (point_count > 0 && point_count == m_C.UnsignedCount());
}

bool ON_PointCloud::HasPointValues() const
{
  const unsigned int point_count = m_P.UnsignedCount();
  return (point_count > 0 && point_count == m_V.UnsignedCount());
}

bool ON_PointCloud::HasPointNormals() const
{
  const unsigned int point_count = m_P.UnsignedCount();
  return (point_count > 0 && point_count == m_N.UnsignedCount());
}

bool ON_PointCloud::GetClosestPoint(
                ON_3dPoint P,
                int* closest_point_index,
                double maximum_distance 
                ) const
{
  if ( maximum_distance > 0.0 && m_bbox.IsValid() )
  {
    // check bounding box
    if ( m_bbox.MinimumDistanceTo(P) > maximum_distance )
      return false;
  }
  return m_P.GetClosestPoint( P, closest_point_index, maximum_distance );
}

unsigned int ON_PointCloud::HiddenPointUnsignedCount() const
{
  unsigned int point_count;
  return (    m_hidden_count > 0 
           && (point_count = m_P.UnsignedCount()) > 0
           && m_hidden_count <= point_count 
           && m_H.UnsignedCount() == point_count 
           )
           ? m_hidden_count
           : 0;
}


int ON_PointCloud::HiddenPointCount() const
{
  return (int)HiddenPointUnsignedCount();
}

void ON_PointCloud::DestroyHiddenPointArray()
{
  m_hidden_count = 0;
  m_H.Destroy();
}

const bool* ON_PointCloud::HiddenPointArray() const
{
  return (m_hidden_count > 0 && m_H.UnsignedCount() == m_P.UnsignedCount()) 
         ? m_H.Array() 
         : 0;
}

void ON_PointCloud::SetHiddenPointFlag( int point_index, bool bHidden )
{
  const int point_count = m_P.Count();
  if ( point_index >= 0 && point_index < point_count )
  {
    if ( bHidden )
    {
      if ( point_count != m_H.Count() )
      {
        m_H.SetCapacity(point_count);
        m_H.SetCount(point_count);
        m_H.Zero();
        m_H[point_index] = true;
        m_hidden_count = 1;
      }
      else if ( false == m_H[point_index] )
      {
        m_H[point_index] = true;
        m_hidden_count++;
      }
    }
    else
    {
      // show this vertex
      if ( m_hidden_count > 0 && point_count == m_H.Count() )
      {
        if  ( m_H[point_index] )
        {
          m_H[point_index] = false;
          m_hidden_count--;
          if ( 0 == m_hidden_count )
          {
            DestroyHiddenPointArray();
          }
        }
      }
      else if ( m_hidden_count > 0 || m_H.Capacity() > 0 )
      {
        // if m_H exists, it is bogus.
        DestroyHiddenPointArray();
      }
    }
  }
}

bool ON_PointCloud::PointIsHidden( int point_index ) const
{
  int point_count;
  return (    point_index >= 0
           && point_index < (point_count = m_P.Count())
           && m_H.Count() == point_count )
           ? m_H[point_index]
           : false;
}

ON_PointCloud* ON_PointCloud::RandomSubsample(
  const ON_PointCloud* source_point_cloud,
  const unsigned int subsample_point_count,
  ON_PointCloud* destination_point_cloud,
  ON_ProgressReporter* progress_reporter,
  ON_Terminator* terminator
)
{
  if (
       nullptr == source_point_cloud 
    || subsample_point_count <= 0 
    || subsample_point_count >= source_point_cloud->m_P.UnsignedCount()
    )
    return nullptr;

  const unsigned int point_count = source_point_cloud->m_P.UnsignedCount();
  const unsigned int points_to_remove = point_count - subsample_point_count;
  if (points_to_remove <= 0)
    return nullptr;

  const bool bHaveNormals = point_count == source_point_cloud->m_N.UnsignedCount();
  const bool bHaveColors = point_count == source_point_cloud->m_C.UnsignedCount();
  const bool bHaveValues = point_count == source_point_cloud->m_V.UnsignedCount();
  const bool bHaveHidden = point_count == source_point_cloud->m_H.UnsignedCount();

  bool bAlloc = false;
  if (destination_point_cloud)
  {
    if (source_point_cloud != destination_point_cloud)
    {
      destination_point_cloud->Destroy();
      *destination_point_cloud = *source_point_cloud;
    }
  }
  else
  {
    destination_point_cloud = new ON_PointCloud(*source_point_cloud);
    bAlloc = true;
  }

  ON_RandomNumberGenerator gen;
  gen.Seed();

  unsigned int last_point_count = point_count;
  for (unsigned int i = 0; i < points_to_remove; i++)
  {
    if (terminator && ON_Terminator::TerminationRequested(terminator))
    {
      if (source_point_cloud != destination_point_cloud)
        destination_point_cloud->Destroy();
      if (bAlloc)
        delete destination_point_cloud;
      return nullptr;
    }

    if (progress_reporter)
      ON_ProgressReporter::ReportProgress(progress_reporter, i / (double)points_to_remove);

    // For (min <= r < max): min + RandomNumber() % (max-min)
    const int point_index = gen.RandomNumber() % last_point_count;

    destination_point_cloud->m_P.Swap(point_index, last_point_count - 1);
    if (bHaveNormals)
      destination_point_cloud->m_N.Swap(point_index, last_point_count - 1);
    if (bHaveColors)
      destination_point_cloud->m_C.Swap(point_index, last_point_count - 1);
    if (bHaveValues)
      destination_point_cloud->m_V.Swap(point_index, last_point_count - 1);
    if (bHaveHidden)
      destination_point_cloud->m_H.Swap(point_index, last_point_count - 1);

    last_point_count--;
    if (last_point_count <= 0)
      break;
  }

  if (progress_reporter)
    ON_ProgressReporter::ReportProgress(progress_reporter, 1.0);

  destination_point_cloud->m_P.SetCount(subsample_point_count);
  destination_point_cloud->m_P.Shrink();
  if (bHaveNormals)
  {
    destination_point_cloud->m_N.SetCount(subsample_point_count);
    destination_point_cloud->m_N.Shrink();
  }
  if (bHaveColors)
  {
    destination_point_cloud->m_C.SetCount(subsample_point_count);
    destination_point_cloud->m_C.Shrink();
  }
  if (bHaveValues)
  {
    destination_point_cloud->m_V.SetCount(subsample_point_count);
    destination_point_cloud->m_V.Shrink();
  }
  if (bHaveHidden)
  {
    destination_point_cloud->m_H.SetCount(subsample_point_count);
    destination_point_cloud->m_H.Shrink();
    destination_point_cloud->m_hidden_count = 0;
    for (unsigned int i = 0; i < destination_point_cloud->m_H.UnsignedCount(); i++)
    {
      if (destination_point_cloud->m_H[i])
        destination_point_cloud->m_hidden_count++;
    }
  }

  return destination_point_cloud;
}

int ON_PointCloud::RemoveRange(const ON_SimpleArray<int>& indices)
{
  return RemoveRange(indices.Count(), indices.Array());
}

int ON_PointCloud::RemoveRange(int count, const int* pIndices)
{
  const unsigned int point_count = m_P.UnsignedCount();
  if (0 == point_count || count <= 0 || nullptr == pIndices)
    return 0;

  ON_SimpleArray<int> indices(count);
  indices.Append(count, pIndices);
  indices.QuickSortAndRemoveDuplicates(ON_CompareDecreasing<int>);

  const unsigned int index_count = indices.Count();
  if (index_count <= 0)
    return 0;

  const bool bHaveNormals = point_count == m_N.UnsignedCount();
  const bool bHaveColors = point_count == m_C.UnsignedCount();
  const bool bHaveValues = point_count == m_V.UnsignedCount();
  const bool bHaveHidden = point_count == m_H.UnsignedCount();

  unsigned int points_removed = 0;
  unsigned int last_point_count = point_count;
  for (unsigned int i = 0; i < index_count; i++)
  {
    const unsigned int point_index = indices[i];
    if (point_index >= 0 && point_index < point_count)
    {
      m_P.Swap(point_index, last_point_count - 1);
      if (bHaveNormals)
        m_N.Swap(point_index, last_point_count - 1);
      if (bHaveColors)
        m_C.Swap(point_index, last_point_count - 1);
      if (bHaveValues)
        m_V.Swap(point_index, last_point_count - 1);
      if (bHaveHidden)
        m_H.Swap(point_index, last_point_count - 1);

      points_removed++;
      last_point_count--;
      if (last_point_count <= 0)
        break;
    }
  }

  m_P.SetCount(last_point_count);
  m_P.Shrink();
  if (bHaveNormals)
  {
    m_N.SetCount(last_point_count);
    m_N.Shrink();
  }
  if (bHaveColors)
  {
    m_C.SetCount(last_point_count);
    m_C.Shrink();
  }
  if (bHaveValues)
  {
    m_V.SetCount(last_point_count);
    m_V.Shrink();
  }
  if (bHaveHidden)
  {
    m_H.SetCount(last_point_count);
    m_H.Shrink();
    m_hidden_count = 0;
    for (unsigned int i = 0; i < m_H.UnsignedCount(); i++)
    {
      if (m_H[i])
        m_hidden_count++;
    }
    InvalidateBoundingBox();
  }

  return points_removed;
}
