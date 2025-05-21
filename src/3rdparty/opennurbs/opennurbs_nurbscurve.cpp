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

ON_OBJECT_IMPLEMENT(ON_NurbsCurve,ON_Curve,"4ED7D4DD-E947-11d3-BFE5-0010830122F0");

/*
Description:
  Helper to make a deep copy (duplicate memory) from src to dest
*/
void ON_NurbsCurve::Internal_DeepCopyFrom( const ON_NurbsCurve& src )
{
  if (this == &src)
  {
    ON_ERROR("this and &src must be different.");
    return;
  }

  // erase tags
  m_knot_capacity_and_tags &= ON_NurbsCurve::masks::knot_capacity;

  const int knot_capacity = (nullptr != src.m_knot) ? src.KnotCount() : 0;
  if (knot_capacity > 0)
  {
    ReserveKnotCapacity(knot_capacity);
    if ( nullptr != m_knot ) 
      memcpy( m_knot, src.m_knot, knot_capacity*sizeof(m_knot[0]) );
  }
  else if (nullptr != m_knot && KnotCapacity() > 0)
  {
    onfree(m_knot);
    m_knot = nullptr;
    m_knot_capacity_and_tags = 0;
  }

  int cv_count = (src.m_cv_count>0) ? src.m_cv_count : 0;
  int cv_stride = (src.m_dim > 0) ? ((src.m_is_rat) ? (src.m_dim + 1) : src.m_dim) : 0;
  const int cv_capacity = (nullptr != src.m_cv) ? (cv_count*cv_stride) : 0;
  if (cv_capacity > 0)
  {
    ReserveCVCapacity(cv_capacity);
    if ( nullptr != m_cv ) 
    {
      // copy cv array
      const int src_stride = src.m_cv_stride;
      const double *src_cv = src.m_cv;
      double *dst_cv = m_cv;
      if (src_stride == cv_stride)
      {
        memcpy(dst_cv, src_cv, cv_capacity * sizeof(dst_cv[0]));
      }
      else
      {
        const size_t sizeof_cv = (size_t)(cv_stride * sizeof(dst_cv[0]));
        for (int i = 0; i < cv_count; i++)
        {
          memcpy(dst_cv, src_cv, sizeof_cv);
          dst_cv += cv_stride;
          src_cv += src_stride;
        }
      }
    }
  }
  else
  {
    if (nullptr != m_cv && m_cv_capacity > 0)
    {
      onfree(m_cv);
      m_cv = nullptr;
    }
    m_cv_capacity = 0;
    cv_count = 0;
    cv_stride = 0;
  }
  
  m_dim       = src.m_dim;
  m_is_rat    = src.m_is_rat;
  m_order     = src.m_order;
  m_cv_count  = cv_count;
  m_cv_stride = cv_stride;

  // copy tags
  const unsigned int src_tags = (src.m_knot_capacity_and_tags & ON_NurbsCurve::masks::all_tags);
  m_knot_capacity_and_tags |= src_tags;
}

/*
Description:
  Helper to move (shallow copy) from src to dest
*/
#if defined(ON_HAS_RVALUEREF)
void ON_NurbsCurve::Internal_ShallowCopyFrom( const ON_NurbsCurve& src )
{
  if (this == &src)
  {
    ON_ERROR("this and &src must be different.");
    return;
  }
  m_dim            = src.m_dim;
  m_is_rat         = src.m_is_rat;
  m_order          = src.m_order;
  m_cv_count       = src.m_cv_count;
  m_knot_capacity_and_tags = src.m_knot_capacity_and_tags;
  m_knot           = src.m_knot;
  m_cv_stride      = src.m_cv_stride;
  m_cv_capacity    = src.m_cv_capacity;
  m_cv             = src.m_cv;
}
#endif

/*
Description:
  Helper to clear (set all member vars to zero)
*/
void ON_NurbsCurve::Internal_InitializeToZero()
{
  m_dim = 0;
  m_is_rat = 0;
  m_order = 0;
  m_cv_count = 0;
  m_knot_capacity_and_tags = 0;
  m_knot = 0;
  m_cv_stride = 0;
  m_cv_capacity = 0;
  m_cv = 0;
}

/*
Description:
  Helper to make a deep copy (duplicate memory) from src to dest
*/
void ON_NurbsCurve::Internal_Destroy()
{
  double* cv = (nullptr != m_cv && CVCapacity() > 0 ) ? m_cv : nullptr;
  double* knot = (nullptr != m_knot && KnotCapacity() > 0 ) ? m_knot : nullptr;
  Internal_InitializeToZero();
  if ( cv )
    onfree(cv);
  if ( knot )
    onfree(knot);
}

ON_NurbsCurve::ON_NurbsCurve() ON_NOEXCEPT
{
  ON__SET__THIS__PTR(m_s_ON_NurbsCurve_ptr);
  Internal_InitializeToZero();
}

ON_NurbsCurve::ON_NurbsCurve( const ON_NurbsCurve& src )
  : ON_Curve(src)
{
  ON__SET__THIS__PTR(m_s_ON_NurbsCurve_ptr);
  Internal_InitializeToZero();
  Internal_DeepCopyFrom(src);
}

ON_NurbsCurve& ON_NurbsCurve::operator=( const ON_NurbsCurve& src )
{
  if ( this != &src ) 
  {
    Internal_Destroy(); // consider removing this so "expert" knots and cv can be used.
    ON_Curve::operator=(src);
    Internal_DeepCopyFrom(src);
  }
  return *this;
}

#if defined(ON_HAS_RVALUEREF)

ON_NurbsCurve::ON_NurbsCurve( ON_NurbsCurve&& src) ON_NOEXCEPT
  : ON_Curve(std::move(src))
{
  ON__SET__THIS__PTR(m_s_ON_NurbsCurve_ptr);
  Internal_ShallowCopyFrom(src);
  src.Internal_InitializeToZero();
}

ON_NurbsCurve& ON_NurbsCurve::operator=( ON_NurbsCurve&& src)
{
  if ( this != &src )
  {
    Internal_Destroy();
    ON_Curve::operator=(std::move(src));
    Internal_ShallowCopyFrom(src);
    src.Internal_InitializeToZero();
  }
  return *this;
}

#endif

ON_NurbsCurve* ON_NurbsCurve::New()
{
  return new ON_NurbsCurve();
}

ON_NurbsCurve* ON_NurbsCurve::New(
          const ON_NurbsCurve& nurbs_curve 
          )
{
  return new ON_NurbsCurve(nurbs_curve);
}

ON_NurbsCurve* ON_NurbsCurve::New(
          const ON_BezierCurve& bezier_curve 
          )
{
  return new ON_NurbsCurve(bezier_curve);
}

ON_NurbsCurve* ON_NurbsCurve::New(
          int dimension,
          bool bIsRational,
          int order,
          int cv_count
          )
{
  return new ON_NurbsCurve(dimension,bIsRational,order,cv_count);
}

ON_NurbsCurve::ON_NurbsCurve( int dim, bool bIsRational, int order, int cv_count )
{
  ON__SET__THIS__PTR(m_s_ON_NurbsCurve_ptr);
  Initialize();
  Create(dim,bIsRational,order,cv_count);
}

ON_NurbsCurve::ON_NurbsCurve(const ON_BezierCurve& src)
{
  ON__SET__THIS__PTR(m_s_ON_NurbsCurve_ptr);
  Initialize();
  ON_NurbsCurve::operator=(src);
}

ON_NurbsCurve::~ON_NurbsCurve()
{
  Destroy();
}

unsigned int ON_NurbsCurve::SizeOf() const
{
  unsigned int sz = ON_Curve::SizeOf();
  sz += (sizeof(*this) - sizeof(ON_Curve));
  sz += KnotCapacity()*sizeof(*m_knot);
  sz += CVCapacity()*sizeof(*m_cv);
  return sz;
}

ON__UINT32 ON_NurbsCurve::DataCRC(ON__UINT32 current_remainder) const
{
  current_remainder = ON_CRC32(current_remainder,sizeof(m_dim),&m_dim);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_is_rat),&m_is_rat);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_order),&m_order);
  current_remainder = ON_CRC32(current_remainder,sizeof(m_cv_count),&m_cv_count);
  if ( m_cv_count > 0 && m_cv_stride > 0 && m_cv )
  {
    size_t sizeof_cv = CVSize()*sizeof(m_cv[0]);
    const double* cv = m_cv;
    int i;
    for ( i = 0; i < m_cv_count; i++ )
    {
      current_remainder = ON_CRC32(current_remainder,sizeof_cv,cv);
      cv += m_cv_stride;
    }
  }
  current_remainder = ON_CRC32(current_remainder,KnotCount()*sizeof(m_knot[0]),m_knot);
  return current_remainder;
}

int ON_NurbsCurve::Dimension() const
{
  return m_dim;
}

bool ON_NurbsCurve::IsRational() const
{
  return m_is_rat?true:false;
}

int ON_NurbsCurve::CVSize() const
{
  return (m_dim>0) ? (m_is_rat?(m_dim+1):m_dim) : 0;
}

int ON_NurbsCurve::Order( void ) const
{
  return m_order;
}

int ON_NurbsCurve::CVCount( void ) const
{
  return m_cv_count;
}

int ON_NurbsCurve::KnotCount( void ) const
{
  return ON_KnotCount( m_order, m_cv_count );
}

double* ON_NurbsCurve::CV( int i ) const
{
  return (m_cv) ? (m_cv + i*m_cv_stride) : nullptr;
}

ON::point_style ON_NurbsCurve::CVStyle() const
{
  return m_is_rat ? ON::homogeneous_rational : ON::not_rational;
}


double ON_NurbsCurve::Weight( int i ) const
{
  return (m_cv && m_is_rat) ? m_cv[i*m_cv_stride+m_dim] : 1.0;
}


double ON_NurbsCurve::Knot( int i ) const
{
  return (m_knot) ? m_knot[i] : 0.0;
}

int ON_NurbsCurve::KnotMultiplicity( int i ) const
{
  return ON_KnotMultiplicity(m_order,m_cv_count,m_knot,i);
}

const double* ON_NurbsCurve::Knot() const
{
  return m_knot;
}

double ON_NurbsCurve::SuperfluousKnot( int end ) const
{
  return(m_knot) ? ON_SuperfluousKnot(m_order,m_cv_count,m_knot,end) : 0.0;
}


bool ON_NurbsCurve::MakePeriodicUniformKnotVector( double delta )
{
	DestroyCurveTree();
  ReserveKnotCapacity( ON_KnotCount( m_order, m_cv_count ) );
  return ON_MakePeriodicUniformKnotVector( m_order, m_cv_count, m_knot, delta );
}


bool ON_NurbsCurve::MakeClampedUniformKnotVector( double delta )
{
	DestroyCurveTree();
  ReserveKnotCapacity( ON_KnotCount( m_order, m_cv_count ) );
  return ON_MakeClampedUniformKnotVector( m_order, m_cv_count, m_knot, delta );
}

bool ON_NurbsCurve::CreateClampedUniformNurbs( 
        int dimension,
        int order,
        int point_count,
        const ON_3dPoint* point,
        double knot_delta
        )
{
  bool rc = (dimension >= 1 && dimension<=3 && point!=nullptr);
  if (rc)
    rc = Create( dimension, false, order, point_count );
  if ( rc )
  {
    int i;
    for (i = 0; i < point_count; i++)
      SetCV( i, ON::intrinsic_point_style, point[i] );
  }
  if ( rc )
    rc = MakeClampedUniformKnotVector( knot_delta );
  return rc;
}

bool ON_NurbsCurve::CreatePeriodicUniformNurbs( 
        int dimension,
        int order,
        int point_count,
        const ON_3dPoint* point,
        double knot_delta
        )
{
  bool rc = (dimension >= 1 && dimension<=3 && point!=nullptr);
  if (rc)
    rc = Create( dimension, false, order, point_count+(order-1) );
  if ( rc )
  {
    int i;
    for (i = 0; i < point_count; i++)
      SetCV( i, ON::intrinsic_point_style, point[i] );
    for (i = 0; i <= order-2; i++)
      SetCV( m_cv_count-m_order+1+i, ON::intrinsic_point_style, CV(i) );
  }
  if ( rc )
    rc = MakePeriodicUniformKnotVector( knot_delta );
  return rc;
}

bool ON_NurbsCurve::Create(
        int dim,      // dimension (>= 1)
        bool is_rat,  // true to make a rational NURBS
        int order,    // order (>= 2)
        int cv_count  // cv count (>= order)
        )
{
  DestroyCurveTree();
  if ( dim < 1 )
    return false;
  if ( order < 2 )
    return false;
  if ( cv_count < order )
    return false;
  m_dim = dim;
  m_is_rat = (is_rat) ? true : false;
  m_order = order;
  m_cv_count = cv_count;
  m_cv_stride = (m_is_rat) ? m_dim+1 : m_dim;
  bool rc = ReserveKnotCapacity( KnotCount() );
  if ( !ReserveCVCapacity( CVCount()*m_cv_stride ) )
    rc = false;
  return rc;
}

void ON_NurbsCurve::Destroy()
{
  DestroyCurveTree();
  Internal_Destroy();
}

void ON_NurbsCurve::EmergencyDestroy()
{
  Internal_InitializeToZero();
}


void ON_NurbsCurve::Initialize()
{
  Internal_InitializeToZero();
}

ON_NurbsCurve& ON_NurbsCurve::operator=(const ON_BezierCurve& src)
{
  int i;
  Create(src.m_dim,src.m_is_rat,src.m_order,src.m_order);
  const int sizeof_cv = src.CVSize()*sizeof(double);
  for ( i = 0; i < m_cv_count; i++ ) {
    memcpy( CV(i), src.CV(i), sizeof_cv );
  }
  for ( i = 0; i <= m_order-2; i++ )
    m_knot[i] = 0.0;
  const int knot_count = KnotCount();
  for ( i = m_order-1; i < knot_count; i++ )
    m_knot[i] = 1.0;
  return *this;
}

void ON_NurbsCurve::Dump( ON_TextLog& dump ) const
{
  dump.Print( "ON_NurbsCurve dim = %d is_rat = %d\n"
               "        order = %d cv_count = %d\n",
               m_dim, m_is_rat, m_order, m_cv_count );
  dump.Print( "Knot Vector ( %d knots )\n", KnotCount() );
  dump.PrintKnotVector( m_order, m_cv_count, m_knot );
  dump.Print( "Control Points  %d %s points\n"
               "  index               value\n",
               m_cv_count, 
               (m_is_rat) ? "rational" : "non-rational" );
  if ( !m_cv ) {
    dump.Print("  nullptr cv array\n");
  }
  else {
    dump.PrintPointList( m_dim, m_is_rat, 
                      m_cv_count, m_cv_stride,
                      m_cv, 
                      "  CV" );
  }
}


static bool ON_NurbsCurveIsNotValid()
{
  return ON_IsNotValid(); // <-- good place for a breakpoint
}

static bool ON_ControlPointsAreNotValid()
{
  return ON_IsNotValid(); // <-- good place for a breakpoint
}

static bool ON_ControlPointsAreValid( int cv_size, int cv_count, int cv_stride, const double* cv, ON_TextLog* text_log )
{
  int i, j;
  if ( 0 == cv  )
  {
    if ( text_log )
    {
      text_log->Print("cv pointer is null.\n");
    }
    return ON_ControlPointsAreNotValid();
  }

  if ( cv_count < 2 )
  {
    if ( text_log )
    {
      text_log->Print("cv_count = %d (must be >= 2).\n",cv_count);
    }
    return ON_ControlPointsAreNotValid();
  }

  if ( cv_size < 1 )
  {
    if ( text_log )
    {
      text_log->Print("cv_size = %d (must be >= 1).\n",cv_size);
    }
    return ON_ControlPointsAreNotValid();
  }

  if ( cv_stride < cv_size )
  {
    if ( text_log )
    {
      text_log->Print("cv_stride = %d and cv_size = %d (cv_stride must be >= cv_size).\n",cv_stride,cv_size);
    }
    return ON_ControlPointsAreNotValid();
  }

  for ( i = 0; i < cv_count; i++, cv += cv_stride )
  {
    for ( j = 0; j < cv_size; j++ )
    {
      if ( !ON_IsValid(cv[j]) )
      {
        if ( text_log )
        {
          text_log->Print("cv[%d*cv_stride + %d] = %g is not valid.\n",i,j,cv[j]);
        }
        return ON_ControlPointsAreNotValid();
      }
    }    
  }

  return true;
}

bool ON_NurbsCurve::IsValid( ON_TextLog* text_log ) const
{
  if ( m_dim <= 0 )
  {
    if ( text_log )
    {
      text_log->Print("ON_NurbsCurve.m_dim = %d (should be > 0).\n",m_dim);
    }
    return ON_NurbsCurveIsNotValid();
  }
  
  if (m_order < 2 )
  {
    if ( text_log )
    {
      text_log->Print("ON_NurbsCurve.m_order = %d (should be >= 2).\n",m_order);
    }
    return ON_NurbsCurveIsNotValid();
  }
  
  if (m_cv_count < m_order )
  {
    if ( text_log )
    {
      text_log->Print("ON_NurbsCurve.m_cv_count = %d (should be >= m_order=%d).\n",m_cv_count,m_order);
    }
    return ON_NurbsCurveIsNotValid();
  }
  
  if (m_cv_stride < CVSize() )
  {
    if ( text_log )
    {
      text_log->Print("ON_NurbsCurve.m_cv_stride = %d (should be >= %d).\n",m_cv_stride,CVSize());
    }
  }
  
  if (m_cv == nullptr)
  {
    if ( text_log )
    {
      text_log->Print("ON_NurbsCurve.m_cv is nullptr.\n");
    }
    return ON_NurbsCurveIsNotValid();
  }
  
  if (m_knot == nullptr)
  {
    if ( text_log )
    {
      text_log->Print("ON_NurbsCurve.m_knot is nullptr.\n");
    }
    return ON_NurbsCurveIsNotValid();
  }

  if ( !ON_IsValidKnotVector( m_order, m_cv_count, m_knot, text_log ) ) 
  {
    if ( text_log )
    {
      text_log->Print("ON_NurbsCurve.m_knot[] is not a valid knot vector.\n");
    }
    return ON_NurbsCurveIsNotValid();
  }

  if ( !ON_ControlPointsAreValid(CVSize(),m_cv_count,m_cv_stride,m_cv,text_log) )
  {
    if ( text_log )
    {
      text_log->Print("ON_NurbsCurve.m_cv[] is not valid.\n");
    }
    return ON_NurbsCurveIsNotValid();
  }

  if ( m_is_rat )
  {
    // weights at fully multiple knots must be nonzero
    // partial test for weight function being zero
    double sign = 0.0;
    const double* w = &m_cv[m_dim];
    int zcount = 0;
    int i;
    for ( i = 0; i < m_cv_count; i++, w += m_cv_stride )
    {
      if ( *w == 0.0 )
        zcount++;
      else
        zcount = 0;

      if ( zcount >= m_order )
      {
        if ( text_log )
        {
          text_log->Print("ON_NurbsCurve.m_cv has zero weights for CV[%d],...,CV[%d].\n",i-m_order+1,i);
        }
        return ON_NurbsCurveIsNotValid(); // denominator is zero for entire span
      }
      
      if ( m_knot[i] == m_knot[i+m_order-2] ) 
      {
        if ( *w == 0.0 )
        {
          if ( text_log )
          {
            text_log->Print("ON_NurbsCurve.m_cv has zero weights for CV[%d].\n",i);
          }
          return ON_NurbsCurveIsNotValid();
        }
        
        if (sign == 0.0) 
        {
          sign = (*w > 0.0) ? 1.0 : -1.0;
        }
        else if ( *w * sign <= 0.0 ) 
        {
          if ( text_log )
          {
            text_log->Print("ON_NurbsCurve.m_cv has a zero denominator in the parameter interval [%g,%g].\n",
                            m_knot[i-1],m_knot[i]);
          }
          return ON_NurbsCurveIsNotValid();
        }
      }
    }

    if ( m_dim <= 3 && 2 == m_order && 2 == m_cv_count )
    {
      // fix for RR 21239
      // 16 November 2010 Chuck and Dale Lear added m_dim <= 3
      // so the 3d checking does not interfere with applications
      // that use high dimension curves where the start and end
      // points can be arbitrary.
      ON_3dPoint P0 = PointAtStart();
      ON_3dPoint P1 = PointAtEnd();
      if ( P0 == P1 )
      {
        if ( text_log )
        {
          text_log->Print("ON_NurbsCurve is a line with no length.\n");
        }
        return ON_NurbsCurveIsNotValid();
      }
    }
  }

  return true;
}

bool ON_NurbsCurve::GetBBox( // returns true if successful
       double* boxmin,    // minimum
       double* boxmax,    // maximum
       bool bGrowBox  // true means grow box
       ) const
{
  return ON_GetPointListBoundingBox( 
                 m_dim, m_is_rat, m_cv_count, 
                 m_cv_stride, m_cv, 
                 boxmin, boxmax, bGrowBox?true:false
                 );
}

bool ON_NurbsCurve::Transform( const ON_Xform& xform )
{
  if ( !this->ON_Curve::Transform(xform) )
    return false;
  if ( 0 == m_is_rat )
  {
    if ( xform.m_xform[3][0] != 0.0 || xform.m_xform[3][1] != 0.0 || xform.m_xform[3][2] != 0.0 )
    {
      MakeRational();
    }
  }
  return ON_TransformPointList( m_dim, m_is_rat, m_cv_count, m_cv_stride, m_cv, xform );
}

bool ON_NurbsCurve::IsDeformable() const
{
  return true;
}

bool ON_NurbsCurve::MakeDeformable()
{
  return true;
}

bool ON_PolylineCurve::IsDeformable() const
{
  return true;
}

bool ON_PolylineCurve::MakeDeformable()
{
  return true;
}


bool ON_NurbsCurve::Write(
       ON_BinaryArchive& file // open binary file
     ) const
{
  // NOTE - check legacy I/O code if changed
  const int minor_version = (file.Archive3dmVersion() >= 60);
  bool rc = file.Write3dmChunkVersion(1,minor_version);
  if (rc)
  {
    if (rc) rc = file.WriteInt( m_dim );
    if (rc) rc = file.WriteInt( m_is_rat );
    if (rc) rc = file.WriteInt( m_order );
    if (rc) rc = file.WriteInt( m_cv_count );
    if (rc) rc = file.WriteInt( 0 ); // reserved - legacy flag values
    if (rc) rc = file.WriteInt( 0 ); // reserved   
    
    // write invalid bounding box - may be used in future
    if (rc) 
    {
      ON_BoundingBox bbox;
      rc = file.WriteBoundingBox(bbox);
    }

    // write knots
    int count = (0 != m_knot && m_cv_count >= m_order && m_order >= 2)
              ? KnotCount() 
              : 0;
    if (rc) rc = file.WriteInt(count);
    if (rc) rc = file.WriteDouble( count, m_knot );

    // write cvs
    const int cv_size = CVSize();
    count = ( m_cv && cv_size > 0 && m_cv_count > 0  && m_cv_stride >= cv_size ) 
          ? m_cv_count
          : 0;
    if (rc) rc = file.WriteInt(count);
    if (rc && count > 0 )
    {
      int i;
      for ( i = 0; i < m_cv_count && rc; i++ )
      {
        rc = file.WriteDouble( cv_size, CV(i) );
      }
    }

    if (rc && minor_version >= 1)
    {
      // April 2019 Chunk version 1.1 - added SubDFriendlyTag
      const bool bSubDFriendlyTag = SubDFriendlyTag();
      rc = file.WriteBool(bSubDFriendlyTag);
    }
  }
  return rc;
}

bool ON_NurbsCurve::Read(
       ON_BinaryArchive& file // open binary file
     )
{
  // NOTE - check legacy I/O code if changed
  Destroy();
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if (rc && major_version==1)
  {
    // common to all 1.x versions
    int dim = 0, is_rat = 0, order = 0, cv_count = 0;
    int reserved1 = 0, reserved2 = 0;
    if (rc) rc = file.ReadInt( &dim );
    if (rc) rc = file.ReadInt( &is_rat );
    if (rc) rc = file.ReadInt( &order );
    if ( order < 0 )
      rc = false;
    if (rc) rc = file.ReadInt( &cv_count );
    if ( cv_count < order )
      rc = false;
    if (rc) rc = file.ReadInt( &reserved1 ); // reserved - legacy flag values
    if (rc) rc = file.ReadInt( &reserved2 ); // reserved    

    // bounding box
    if (rc) {
      // write invalid bounding box - may be used in future
      ON_BoundingBox bbox;
      rc = file.ReadBoundingBox( bbox );
    }
    
    if ( !Create( dim, is_rat, order, cv_count ) )
      rc = false;

    // read knots
    int count = 0;
    if (rc) rc = file.ReadInt(&count);
    if ( count < 0 )
      rc = false; // fix crash bug 92841
    else if ( 0 != count && count != ON_KnotCount(order,cv_count) )
      rc = false;
    if (rc ) rc = ReserveKnotCapacity(count);
    if (rc) rc = file.ReadDouble( count, m_knot );

    // read cvs
    count = 0;
    if (rc) rc = file.ReadInt(&count);
    const int cv_size = CVSize();
    if (rc) rc = ReserveCVCapacity( count*cv_size );
    if (count > 0 && cv_size > 0 && rc )
    {
      int i;
      for ( i = 0; i < m_cv_count && rc; i++ )
      {
        rc = file.ReadDouble( cv_size, CV(i) );
      }
    }

    if (rc && minor_version >= 1)
    {
      // April 2019 Chunk version 1.1 - added SubDFriendlyTag
      bool bSubDFriendlyTag = false;
      rc = file.ReadBool(&bSubDFriendlyTag);
      if (bSubDFriendlyTag)
        SetSubDFriendlyTag(bSubDFriendlyTag);
    }
  }
  if ( !rc )
    Destroy();
  return rc;
}

ON_Interval ON_NurbsCurve::Domain() const
{
  ON_Interval d;
  if ( !ON_GetKnotVectorDomain( m_order, m_cv_count, m_knot, &d.m_t[0], &d.m_t[1] ) )
    d = ON_Interval::EmptyInterval;
  return d;
}

bool ON_NurbsCurve::SetDomain( double t0, double t1 )
{
  bool rc = false;
  if ( m_order >= 2 && m_cv_count >= m_order && m_knot && t0 < t1 ) {
	 //DestroyCurveTree();
   const double k0 = m_knot[m_order-2];
    const double k1 = m_knot[m_cv_count-1];
    if ( k0 == t0 && k1 == t1 )
      rc = true;
    else if ( k0 < k1 ) 
    {
      DestroyCurveTree();
      const double d = (t1-t0)/(k1-k0);
      const double km = 0.5*(k0+k1);
      const int knot_count = KnotCount();
      int i;
      for ( i = 0; i < knot_count; i++ ) 
      {
        if ( m_knot[i] <= km ) {
          m_knot[i] = (m_knot[i] - k0)*d + t0;
        }
        else {
          m_knot[i] = (m_knot[i] - k1)*d + t1;
        }
      }
      rc = true;
    }
  }
  return rc;
}


static ON_NurbsCurve* MoveSeamPeriodicKnot(const ON_NurbsCurve& crv, int knot_index)

{
  int dg = crv.Degree();
  if (dg < 2)
    return 0;
  if (!crv.IsPeriodic())
    return 0;
  if (knot_index < dg || knot_index >= crv.KnotCount()-dg)
    return 0;
  int sc = crv.SpanCount(); 
  if (sc < crv.KnotCount()-2*dg+1)//Not all knots are simple
    return 0;
  const double* knots = &crv.m_knot[dg-1];
  int distinct_cvc = crv.CVCount()-dg;
  double dom_len = crv.Domain().Length();
  ON_NurbsCurve* pNC = ON_NurbsCurve::New(crv);
  int curr = dg-1;
  for (int i=knot_index; i<sc+dg-1; i++){
    pNC->SetKnot(curr, pNC->Knot(i));
    curr++;
  }

  for (int i=0; i<=knot_index-dg+1; i++){
    pNC->SetKnot(curr, knots[i] + dom_len);
    curr++;
  }

  for (int i=0; i<dg-1; i++){
    pNC->SetKnot(curr+i, pNC->Knot(curr+i-1)+pNC->Knot(dg+i) - pNC->Knot(dg+i-1));
    pNC->SetKnot(dg-2-i, pNC->Knot(dg-i-1) - pNC->Knot(curr-1-i) + pNC->Knot(curr-2-i));
  }

  int cv_id = knot_index-dg+1;
  for (int i=0; i<pNC->CVCount(); i++){
    double* pcv = crv.CV(cv_id%distinct_cvc);
    pNC->SetCV(i, ON::intrinsic_point_style, pcv);
    cv_id++;
  }

  return pNC;
}


static ON_NurbsCurve* MoveSeamPeriodic(const ON_Curve& crv, double t)

{
  ON_NurbsCurve nc;
  double s = t;
  const ON_NurbsCurve*pNC = ON_NurbsCurve::Cast(&crv);
  if (pNC)
    nc = *pNC;
  else {
    if (!crv.GetNurbFormParameterFromCurveParameter(t, &s))
      return 0;
    if (!crv.GetNurbForm(nc))
      return 0;
  }
  if (!nc.IsPeriodic())
    return 0;
  //Make sure all interior knots are simple

  int sc = nc.SpanCount(); 
  if (sc < nc.KnotCount()-2*nc.Degree()+1)//Not all knots are simple
    return 0;

  int knot_index = -1;
  for (int i=0; i<nc.KnotCount(); i++){
    if (nc.Knot(i) > s){
      knot_index = i;
      break;
    }
  }
  if (knot_index < nc.Degree() || knot_index > nc.KnotCount()-nc.Degree())
    return 0;

  double k0 = nc.Knot(knot_index-1);
  double d0 = s-k0;
  double k1 = nc.Knot(knot_index);
  double d1 = k1-s;
  bool bInsert = true;
  if (d0<=d1){
    if (d0 < ON_ZERO_TOLERANCE*fabs(k0)){
      knot_index--;
      bInsert = false;
    }
  }
  else {
    if (d1 < ON_ZERO_TOLERANCE*fabs(k1))
      bInsert = false;
  }

  if (bInsert && !nc.InsertKnot(s, 1))
    return 0;

  return MoveSeamPeriodicKnot(nc, knot_index);

}



bool ON_NurbsCurve::ChangeClosedCurveSeam( double t )
{
  bool rc = IsClosed();
  if ( rc )
  {
    //bool bIsPeriodic = IsPeriodic();
    const ON_Interval old_dom = Domain();
    double k = t;
    double s = old_dom.NormalizedParameterAt(t);
    if ( s < 0.0 || s > 1.0 )
    {
      s = fmod( s, 1.0 );
      if ( s < 0.0 )
        s += 1.0;
      k = old_dom.ParameterAt(s);
    }
		s = old_dom.NormalizedParameterAt( k);
    if ( old_dom.Includes(k,true) )
    {
      ON_NurbsCurve left, right;
      // if periodic - dont' put fully multiple knot in middle.  
      bool bGotIt = false;
      if ( IsPeriodic() ){//This only works if the curve has only simple knots
        ON_NurbsCurve* pMovedNC = MoveSeamPeriodic(*this, t);
        if (pMovedNC){
          *this = *pMovedNC;
          delete pMovedNC;
          bGotIt = true;
        }
      }
      if (!bGotIt)
      {
        ON_Curve* pleft = &left;
        ON_Curve* pright = &right;
        rc = Split( k, pleft, pright );
        if ( rc )
        {
          //int a = left.IsValid();
          //int b = right.IsValid();
          right.Append(left);
          *this = right;
        }
      }
    }
    else
    {
      // k already at start/end of domain
      rc = true;
    }
    if (rc)
      SetDomain( t, t+old_dom.Length() );
  }
  return rc;
}


int ON_NurbsCurve::SpanCount() const
{
  // number of smooth spans in curve
  return ON_KnotVectorSpanCount( m_order, m_cv_count, m_knot );
}

bool ON_NurbsCurve::GetSpanVector( // span "knots" 
       double* s // array of length SpanCount() + 1 
       ) const
{
  return ON_GetKnotVectorSpanVector( m_order, m_cv_count, m_knot, s );
}

int ON_NurbsCurve::Degree() const
{
  return m_order >= 2 ? m_order-1 : 0;
}


// true if curve locus is a line segment
// tolerance to use when checking linearity
bool
ON_NurbsCurve::IsLinear(
      double tolerance
      ) const
{
  // 9 March 2009 Dale Lear
  //   Speed up IsLinear() test to accelerate loading curves into Rhino.
  //

  if ( !IsClamped() )
    return false;

  // IsClamped returning true insures that 2 <= order <= cv_count
  // and that the knot vector is clamped.

  ON_Line L;
  ON_3dPoint P, Q;
  ON_3dVector V0, V1, D;
  double t0, t, d, s;
  int i;

  // When m_cv is a null pointer, the GetCV() fails.
  if ( !GetCV(0,L.from) )
    return false;
  if ( !GetCV(m_cv_count-1,L.to) )
    return false;

  // if CV coordinates are NaNs, infinities or ON_UNSET_VALUE,
  // then "t" will end failing the ON_IsValid() test.
  D.x = L.to.x - L.from.x; D.y = L.to.y - L.from.y; D.z = L.to.z - L.from.z; 
  t = D.x*D.x + D.y*D.y + D.z*D.z;
  if ( !ON_IsValid(t) || !(t > 0.0) )
    return false;

  if ( 2 == m_cv_count )
    return true;

  t0 = 0.0;
  bool bDefaultTolerance = false;
  if ( !(tolerance > 0.0) )
  {
    bDefaultTolerance = true;
    tolerance = ON_ZERO_TOLERANCE;
  }
  const double tol2 = tolerance*tolerance;
  t = 1.0/t;
  D.x *= t; D.y *= t; D.z *= t;

  for ( i = 1; i < m_cv_count-1; i++ )
  {
    // This call to GetCV will return true because earlier calls to
    // GetCV(0,...) and GetCV(m_cv_count-1,...) worked
    GetCV(i,P); 

    // Set t = parameter of point on line L closest to P
    V0.x = P.x - L.from.x; V0.y = P.y - L.from.y; V0.z = P.z - L.from.z;
    V1.x = P.x - L.to.x;   V1.y = P.y - L.to.y;   V1.z = P.z - L.to.z;
    if ( V0.x*V0.x + V0.y*V0.y + V0.z*V0.z <= V1.x*V1.x + V1.y*V1.y + V1.z*V1.z )
    {
      // P is closest to L.from
      t = V0.x*D.x + V0.y*D.y + V0.z*D.z;
      if ( t < -0.01 )
        return false;
    }
    else 
    {
      // P is closest to L.to
      t = 1.0 + V1.x*D.x + V1.y*D.y + V1.z*D.z;
      if ( t > 1.01 )
        return false;
    }

    // set Q = L.PointAt(t)
    s = 1.0-t;
    Q.x = s*L.from.x + t*L.to.x; Q.y = s*L.from.y + t*L.to.y; Q.z = s*L.from.z + t*L.to.z;

    if ( bDefaultTolerance )
    {
      if ( !ON_PointsAreCoincident(3,0,&P.x,&Q.x) )
        return false;
    }
    else
    {
      // verify that the distance from P to Q is <= tolerance
      s = P.x-Q.x;
      d = tol2 - s*s;
      if ( d < 0.0 )
        return false;
      s = P.y-Q.y;
      d -= s*s;
      if ( d < 0.0 )
        return false;
      s = P.z-Q.z;
      d -= s*s;
      if ( d < 0.0 )
        return false;
    }

    if ( t > t0 && t0 < 1.0 )
    {
      t0 = (t < 1.0) ? t : 1.0;
    }

    if ( !(t >= t0 && t <= 1.0) )
    {
      // 14 Dec 2004
      //  Chuck and Dale Lear added this test to weed out
      //  garbage curves whose locus is a line but that self intersect.
      //  For example, circles that have been projected onto a plane 
      //  perpendicular to their axis are garbage and are not "linear".

      // either a (nearly) stacked control point or
      // the curve has reversed direction        
      P = L.PointAt(t0);
      d = Q.DistanceTo(P);
      if ( !(d <= tolerance) )
        return false; // curve has reversed direction ("garbage")
    }
  }

  return true;
}

int ON_NurbsCurve::IsPolyline(
      ON_SimpleArray<ON_3dPoint>* pline_points,
      ON_SimpleArray<double>* pline_t
      ) const
{
  int i;
  int rc = 0;
  if ( pline_points )
    pline_points->SetCount(0);
  if ( pline_t )
    pline_t->SetCount(0);
  if ( IsValid() )
  {
    if ( 2 == m_order )
    {
      rc = m_cv_count;
      if ( pline_points )
      {
        pline_points->Reserve(m_cv_count);
        for ( i = 0; i < m_cv_count; i++ )
        {
          GetCV(i,pline_points->AppendNew());
        }
      }
      if ( pline_t )
      {
        pline_t->Reserve(m_cv_count);
        for ( i = 0; i < m_cv_count; i++ )
          pline_t->Append(m_knot[i]);
      }
    }
    else if ( m_order > 2 && m_dim >= 2 && m_dim <= 3 )
    {
      // 16 April 2003 Dale Lear:
      //     Added to so the high degree polylines get
      //     flagged as polylines.
      const double *k = m_knot;
      double t;
      int i_local, j, span_count = m_cv_count-m_order+1;
      ON_Line line;
      ON_3dPoint P, Q;
      GetCV(0,line.to);
      for ( i_local = 0; i_local < span_count; i_local++, k++ )
      {
        if ( k[m_order-2] < k[m_order-1] )
        {
          if ( k[0] != k[m_order-2] )
          {
            // not a bezier span
            return 0;
          }
          if ( k[m_order-1] != k[2*m_order-3] )
          {
            // not a bezier span
            return 0;
          }

          // see if this bezier segment is a line
          // with (roughly) linear parameterization.
          line.from = line.to;
          GetCV(i_local+m_order-1,line.to);
          for ( j = 1; j < m_order-1; j++ )
          {
            GetCV(i_local+j,P);
            t = 0.0;
            if ( !line.ClosestPointTo(P,&t) )
              return 0;
            if ( fabs( t*(m_order-1) - j ) > 0.01 )
            {
              // not linearly parameterized.
              // Please check with Dale Lear before changing
              // this test.
              return 0;
            }
            Q = line.PointAt(t);
            // Please check with Dale Lear before changing
            // this test.
            // October 2012 Dale Lear 
            //  0.00001 is way too large.  For example in bug
            //  http://dev.mcneel.com/bugtrack/?q=115183 it turns
            //  arcs into polylines.  I'm changing it to 
            //  ON_RELATIVE_TOLERANCE because that makes sense.
            //const double rel_tol = 0.00001;
            const double rel_tol = ON_RELATIVE_TOLERANCE;
            if ( fabs(P.x - Q.x) > (fabs(P.x) + fabs(Q.x))*rel_tol + ON_ZERO_TOLERANCE )
              return 0;
            if ( fabs(P.y - Q.y) > (fabs(P.y) + fabs(Q.y))*rel_tol + ON_ZERO_TOLERANCE )
              return 0;
            if ( fabs(P.z - Q.z) > (fabs(P.z) + fabs(Q.z))*rel_tol + ON_ZERO_TOLERANCE )
              return 0;
          }
          rc++;
        }
      }

      if (rc > 0 )
      {
        rc++;
        // it's a polyline
        if ( 0 != pline_points || 0 != pline_t )
        {
          GetCV(0,P);
          if ( 0 != pline_points )
          {
            pline_points->Reserve(rc);
            GetCV(0,pline_points->AppendNew());
          }
          if ( 0 != pline_t )
          {
            pline_t->Reserve(rc);
            pline_t->Append( m_knot[m_order-2] );
          }

          const double *k_local = m_knot;
          for ( i_local = 0; i_local < span_count; i_local++, k_local++ )
          {
            if ( k_local[m_order-2] < k_local[m_order-1] )
            {
              // see if this bezier segment is a line
              // with (roughly) linear parameterization.
              if ( 0 != pline_points )
                GetCV(i_local+m_order-1,pline_points->AppendNew());
              if ( 0 != pline_t )
                pline_t->Append(k_local[m_order-1]);
            }
          }
        }
      }
    }

    if( IsClosed() && rc >= 4 && 0 != pline_points )
    {
      // GBA 2/26/03
      // Make polyline spot on closed.	
      *pline_points->Last() = *pline_points->First();
    }

  }
  return rc;
}



bool
ON_NurbsCurve::IsArc(
      const ON_Plane* plane,
      ON_Arc* arc,
      double tolerance
      ) const
{
  // If changes are made, verify that RR 8497 still works.
  // On 30 April 2003, Mikko changed the strict test to a sloppy
  // test to fix RR 8497.  This change broke other things like 
  // IGES simple entity export tests that require a strict test.
  // So on 6 May 2003 Dale Lear added in the "bLooseTest" check.
  // If the tolerance > ON_ZERO_TOLERANCE a fuzzy fit to arc
  // arc test is performed.  If tolerance <= ON_ZERO_TOLERANCE,
  // a stricter arc test is performed.
  const bool bLooseTest = (tolerance > ON_ZERO_TOLERANCE);
  const int knotcount = KnotCount();
  const int degree = m_order-1;
  if ( (2 == m_dim || 3 == m_dim)
       && m_cv_count >= m_order
       && degree >= 2
       && 0 != m_knot
       && 0 != m_cv
       && (bLooseTest || 0 != m_is_rat)
       )
  {
    if ( bLooseTest || 0 == (knotcount % degree) )
    {

      if ( !bLooseTest )
      {
        for ( int i = 0; i < m_cv_count; i += degree )
        {
          if ( m_knot[i] != m_knot[i+degree-1] )
            return false;
        }
      }

      // 24 July 2012 Dale Lear
      //   You can't be a line and an arc.  This test prevents
      //   creating arcs with small angles and large radii and
      //   prevents sloppy tolerances from classifying a span
      //   as an arc when it makes no sense.
      if ( IsLinear(tolerance) )
        return false;

      if ( ON_Curve::IsArc( plane, arc, tolerance ) )
        return true;
    }
  }

  return false;
}

bool
ON_NurbsCurve::IsPlanar(
      ON_Plane* plane, // if not nullptr and true is returned, then plane parameters
                         // are filled in
      double tolerance // tolerance to use when checking linearity
      ) const
{
  if ( m_dim == 2 )
  {
    return ON_Curve::IsPlanar(plane,tolerance);
  }

  bool rc = false;
  ON_3dPoint P;
  ON_3dVector X;
  EvTangent( Domain()[0], P, X );
  if ( IsLinear(tolerance) )
  {
    if ( plane ) 
    {
      ON_Line line( P, PointAtEnd() );
      if ( !line.InPlane( *plane, tolerance) )
        line.InPlane( *plane, 0.0 );
    }
    rc = true;
  }
  else if ( m_cv_count >= 3 )
  {
    // set P, Q, R to corners of biggest triangle
    // with corners at control points.
    ON_Plane test_plane;
    ON_3dPoint A, B, Q, R;
    Q = P;
    R = P;
    double d, maxd = 0.0;
    int i, j, k;
    k = m_cv_count/64; // to keep sample time reasonable on giant NURBS
    if ( k < 1 )
      k = 1;
    for ( i = 1; i < m_cv_count; i += k )
    {
      GetCV(i,A);
      for ( j = i+k; j < m_cv_count; j += k )
      {
        GetCV(j,B);
        d = ON_CrossProduct( A-P, B-P ).Length();
        if ( d > maxd )
        {
          maxd = d;
          Q = A;
          R = B;
        }
      }
    }
    if ( test_plane.CreateFromPoints(P,Q,R) )
    {
      ON_2dVector v( X*test_plane.xaxis, X*test_plane.yaxis );
      if ( v.Unitize() )
      {
        // Rotate test_plane's x,y axes so its x axis is parallel
        // to the curve's initial tangent.
        if ( fabs(v.y) <= ON_SQRT_EPSILON )
        {
          v.x = (v.x >= 0.0) ? 1.0 : -1.0;
          v.y = 0.0;
        }
        else if ( fabs(v.x) <= ON_SQRT_EPSILON )
        {
          v.y = (v.y >= 0.0) ? 1.0 : -1.0;
          v.x = 0.0;
        }
        X = test_plane.xaxis;
        ON_3dVector Y = test_plane.yaxis;
        test_plane.xaxis = v.x*X + v.y*Y;
        test_plane.yaxis = v.x*Y - v.y*X;
      }
      rc = IsInPlane( test_plane, tolerance );
      if ( rc && plane )
        *plane = test_plane;

      // RH-75060 GBA 9-June-23 
       // For a planar simple closed curve we should return the plane
       // whose orientation that matches the curve orientation.
      if (rc && plane && IsClosed())
      {
        if (ON_ClosedCurveOrientation(*this, *plane) < 0)
          plane->Flip();
      }
    }
  }
  return rc;
}

bool
ON_NurbsCurve::IsInPlane(
      const ON_Plane& plane, // plane to test
      double tolerance // tolerance to use when checking linearity
      ) const
{
  bool rc = IsValid();
  ON_3dPoint P;
  int i;
  for ( i = 0; rc && i < m_cv_count; i++ )
  {
    GetCV(i,P);
    if ( fabs( plane.DistanceTo(P)) > tolerance)
      rc = false;
  }
  return rc;
}

bool
ON_NurbsCurve::GetParameterTolerance( // returns tminus < tplus: parameters tminus <= s <= tplus
       double t,       // t = parameter in domain
       double* tminus, // tminus
       double* tplus   // tplus
       ) const
{
  bool rc = false;
  ON_Interval d = Domain();
  if ( d.IsIncreasing() ) {
    const double* knot = Knot();
    const int order = Order();
    const int cv_count = CVCount();
    if ( t < knot[order-1] )
      d.m_t[1] = knot[order-1];
    else if ( t > knot[cv_count-2] )
      d.m_t[0] = knot[cv_count-2];
    rc = ON_GetParameterTolerance( d.m_t[0], d.m_t[1], t, tminus, tplus );
  }
  return rc;
}



bool 
ON_NurbsCurve::Evaluate( // returns false if unable to evaluate
       double t,       // evaluation parameter
       int der_count,  // number of derivatives (>=0)
       int v_stride,   // v[] array stride (>=Dimension())
       double* v,      // v[] array of length stride*(ndir+1)
       int side,       // optional - determines which side to evaluate from
                       //         0 = default
                       //      <  0 to evaluate from below, 
                       //      >  0 to evaluate from above
       int* hint       // optional - evaluation hint (int) used to speed
                       //            repeated evaluations
       ) const
{
  bool rc = false;

  if( m_order<2)      // GBA added 01-12-06 to fix crash bug
     return false;

  int span_index = ON_NurbsSpanIndex(m_order,m_cv_count,m_knot,t,side,(hint)?*hint:0);

  if ( -2 == side || 2 == side )
  {
    // 9 November 2010 Dale Lear - ON_TuneupEvaluationParameter fix
    //   When evaluation passes through ON_CurveProxy or ON_PolyCurve reparamterization
    //   and the original side parameter was -1 or +1, it is changed to -2 or +2
    //   to indicate that if t is numerically closed to an end parameter, then
    //   it should be tuned up to be at the end parameter.
    double a = t;
    if ( ON_TuneupEvaluationParameter( side, m_knot[span_index+m_order-2], m_knot[span_index+m_order-1], &a) )
    {
      // recalculate span_index
      t = a;
      span_index = ON_NurbsSpanIndex(m_order,m_cv_count,m_knot,t,side,span_index);
    }
  }

  rc = ON_EvaluateNurbsSpan(
     m_dim, m_is_rat, m_order, 
     m_knot + span_index, 
     m_cv_stride, m_cv + (m_cv_stride*span_index),
     der_count, 
     t,
     v_stride, v 
     );
  if ( hint ) 
    *hint = span_index;
  return rc;
}


bool 
ON_NurbsCurve::IsClosed() const
{
  bool bIsClosed = false;
  if ( m_dim > 0 && m_cv_count >= 4 ) 
  {
    if ( IsPeriodic() ) {
      bIsClosed = true;
    }
    else {
      bIsClosed = ON_Curve::IsClosed();
    }
  }
  return bIsClosed;
}

bool 
ON_NurbsCurve::IsPeriodic() const
{
  bool bIsPeriodic = ON_IsKnotVectorPeriodic( m_order, m_cv_count, m_knot );
  if ( bIsPeriodic ) {
    int i0 = m_order-2;
    int i1 = m_cv_count-1;
    const double* cv0 = m_cv + i0*m_cv_stride;
    const double* cv1 = m_cv + i1*m_cv_stride;
    for ( /*empty*/; i0 >= 0; i0--, i1-- ) {
      if ( false == ON_PointsAreCoincident( m_dim, m_is_rat, cv0, cv1 ) )
        return false;
      cv0 -= m_cv_stride;
      cv1 -= m_cv_stride;      
    }
  }
  return bIsPeriodic;
}


bool ON_IsCurvatureDiscontinuity( 
  const ON_3dVector Km, 
  const ON_3dVector Kp,
  double cos_angle_tolerance,
  double curvature_tolerance,
  double zero_curvature,
  double radius_tolerance
  )
{
  // This function is provided so old code will link.
  // New code should use the version with an explicit relative_tolerance
  return ON_IsCurvatureDiscontinuity( Km, Kp, 
    cos_angle_tolerance, 
    curvature_tolerance,
    zero_curvature,
    radius_tolerance,
    0.001 // relative_tolerance - used to be hard coded in this version of the function
    );
}

bool ON_IsG2CurvatureContinuous(
  const ON_3dVector Km, 
  const ON_3dVector Kp,
  double cos_angle_tolerance,
  double curvature_tolerance
  )
{
  // 6 November 2010 Dale Lear
  //  I made up these values used for cos_Kangle_tolerance
  //  and rel_tol today.  They may need adjusting as we 
  //  get test results.
  double rel_tol = ON_RELATIVE_CURVATURE_TOLERANCE; // disables using curvature_tolerance to flag unequal scalars

  double cos_Kangle_tolerance = cos_angle_tolerance;
  if ( cos_Kangle_tolerance > ON_DEFAULT_ANGLE_TOLERANCE_COSINE )
    cos_Kangle_tolerance = ON_DEFAULT_ANGLE_TOLERANCE_COSINE;
  if ( cos_Kangle_tolerance > 0.95 )
  {
    // double the tangent angle
    if ( cos_angle_tolerance < 0.0 )
    {
      cos_Kangle_tolerance = -1.0;
    }
    else
    {
      cos_Kangle_tolerance = 2.0*cos_Kangle_tolerance*cos_Kangle_tolerance - 1.0; // = cos(2*tangent_angle_tolerance)
      if ( cos_angle_tolerance >= 0.0 && cos_Kangle_tolerance < 0.0 )
        cos_Kangle_tolerance = 0.0;
    }
  }

  return !ON_IsCurvatureDiscontinuity(Km,Kp,
            cos_Kangle_tolerance,
            curvature_tolerance,
            ON_ZERO_CURVATURE_TOLERANCE,
            ON_UNSET_VALUE, // no absolute delta radius tolerance
            rel_tol
            );
}

bool ON_IsGsmoothCurvatureContinuous(
  const ON_3dVector Km, 
  const ON_3dVector Kp,
  double cos_angle_tolerance,
  double curvature_tolerance
  )
{
  double relative_tolerance = 1.0; // disables using relative_tolerance to flag unequal scalars

  // point of inflection angle >= 90 degrees
  double cos_Kangle_tolerance = 0.0;

  // Since cos_Kangle_tolerance and rel_tol are valid settings,
  // curvature_tolerance is used only to test for equality.
  return !ON_IsCurvatureDiscontinuity(Km,Kp,
            cos_Kangle_tolerance,
            curvature_tolerance,
            ON_ZERO_CURVATURE_TOLERANCE,
            ON_UNSET_VALUE, // no absolute delta radius tolerance
            relative_tolerance
            );
}

bool ON_IsCurvatureDiscontinuity( 
  const ON_3dVector Km, 
  const ON_3dVector Kp,
  double cos_angle_tolerance,
  double curvature_tolerance,
  double zero_curvature,
  double radius_tolerance,
  double relative_tolerance
  )
{
  const double d = (Km-Kp).Length();
  if ( !ON_IsValid(d) )
  {
    // invalid curvatures - call it discontinuous because
    // there is a good chance the derivative evaluation 
    // failed or the first derivative is zero.
    return true;
  }

  // The d <= 0.0 test handles the case when 
  // curvature_tolerance is ON_UNSET_VALUE
  if ( d <= 0.0 || d <= curvature_tolerance )
    return false; // "equal" curvature vectors

  // If the scalar curvature is <= zero_curvature,
  // then K is small enough that we assume it is zero.
  // The primary reason for doing this is to prevent
  // reporting a curvature discontinuity when one
  // or both of the curvatures is small1.0e-300 and 1.0e-200
  if ( !(zero_curvature > 7.7037197787136e-34) )
    zero_curvature = 7.7037197787136e-34;
  double km = Km.Length();
  double kp = Kp.Length();
  // If km or kp are NaNs, I treat them as zero so
  // the rest of this code can assume they are 0.0
  // or positive.
  if ( !(km > zero_curvature) )
    km = 0.0;
  if ( !(kp > zero_curvature) )
  {
    kp = 0.0;
    if ( 0.0 == km )
    {
      // both curvatures are "zero"
      return false;
    }
  }

  if ( !(km > 0.0 && kp > 0.0) )
  {
    // one side is flat and the other is curved.
    return true;
  }

  // Nov 1, 2012 Dale Lear
  // This test was wrong.  Read the description of the curvature_tolerance
  // parameter in the header file.
  //////if ( 0.0 == curvature_tolerance )
  //////{
  //////  // User is asking for exact match.
  //////  return true;
  //////}

  // At this point we know km > 0 and kp > 0.

  bool bPointOfInflection = (curvature_tolerance > 0.0);
  bool bDifferentScalars = bPointOfInflection;
  // NOTE: 
  //   At this point either curvature_tolerance was not
  //   specified or |Km - Kp| > curvature_tolerance. Because
  //   it is difficult to come up with a meaningful value for
  //   curvature_tolerance that works at all scales, the
  //   additional tests below are used to determine if 
  //   Km and Kp are different enough to matter. If additional
  //   tests are performed, then bTestCurvatureTolerance
  //   is set to false. If no additional tests are performed,
  //   then bTestCurvatureTolerance will remain true and
  //   the |Km-Kp| > curvature_tolerance test is performed
  //   at the end of this function.

  if ( cos_angle_tolerance >= -1.0 && cos_angle_tolerance <= 1.0 )
  {
    const double KmoKp = Kp*Km;
    if ( KmoKp < km*kp*cos_angle_tolerance )
      return true; // Km and Kp are not parallel
    bPointOfInflection = false;
  }

  // At this point we assume Km and Kp are parallel and we
  // know km > 0 and kp > 0.
  if ( radius_tolerance >= 0.0 )
  {
    // This test is if (fabs(rm - rp) > radius_tolerance) return true
    // where rm = 1.0/km and rp = 1.0/kp.  It is coded the way
    // it is to avoid divides (not that that really matters any more).
    if ( fabs(km-kp) > kp*km*radius_tolerance )
      // radii do not agree
      return true;
    bDifferentScalars = false;
  }

  if ( relative_tolerance > 0.0 )
  {
    if ( fabs(km-kp) > ((km>kp)?km:kp)*relative_tolerance )
    {
      return true;
    }
    bDifferentScalars = false;
  }

  if ( bPointOfInflection || bDifferentScalars )
  {
    // |Km - Kp| > curvature_tolerance and we were not asked to
    // perform and other tests.
    return true;
  }

  return false; // treat Km and Kp as equal curvatures.
}

bool 
ON_NurbsCurve::SetWeight( int i, double w )
{
  DestroyCurveTree();

  bool rc = false;

  if (0 == m_is_rat && w > 0.0 && w < ON_UNSET_POSITIVE_VALUE)
  {
    MakeRational();
  }

  if ( m_is_rat )
  {
    double* cv = CV(i);
    if (cv) {
      cv[m_dim] = w;
      rc = true;
    }
  }
  else if ( w == 1.0 ) 
  {
    rc = true;
  }

  return rc;
}

bool 
ON_NurbsCurve::SetCV( int i, ON::point_style style, const double* Point )
{
  bool rc = true;
  int k;
  double w;

  // feeble but fast check for properly initialized class
  if ( !m_cv || i < 0 || i >= m_cv_count )
    return false;

  double* cv = m_cv + i*m_cv_stride;

  switch ( style ) {

  case ON::not_rational:  // input Point is not rational
    memcpy( cv, Point, m_dim*sizeof(*cv) );
    if ( IsRational() ) {
      // NURBS curve is rational - set weight to one
      cv[m_dim] = 1.0;
    }
    break;

  case ON::homogeneous_rational:  // input Point is homogeneous rational
    if ( IsRational() ) {
      // NURBS curve is rational
      memcpy( cv, Point, (m_dim+1)*sizeof(*cv) );
    }
    else {
      // NURBS curve is not rational
      w = (Point[m_dim] != 0.0) ? 1.0/Point[m_dim] : 1.0;
      for ( k = 0; k < m_dim; k++ ) {
        cv[k] = w*Point[k];
      }
    }
    break;

  case ON::euclidean_rational:  // input Point is euclidean rational
    if ( IsRational() ) {
      // NURBS curve is rational - convert euclean point to homogeneous form
      w = Point[m_dim];
      for ( k = 0; k < m_dim; k++ )
        cv[k] = w*Point[k]; // 22 April 2003 - bug fix [i] to [k]
      cv[m_dim] = w;
    }
    else {
      // NURBS curve is not rational
      memcpy( cv, Point, m_dim*sizeof(*cv) );
    }
    break;

  case ON::intrinsic_point_style:
    memcpy( cv, Point, CVSize()*sizeof(*cv) );
    break;
    
  default:
    rc = false;
    break;
  }
	DestroyCurveTree();
  return rc;
}

bool 
ON_NurbsCurve::SetCV( int i, const ON_3dPoint& point )
{
  bool rc = false;
  double* cv = CV(i);
  if ( cv ) {
    cv[0] = point.x;
    if ( m_dim > 1 ) {
      cv[1] = point.y;
      if ( m_dim > 2 )
        cv[2] = point.z;
      if ( m_dim > 3 ) {
        memset( &cv[3], 0, (m_dim-3)*sizeof(*cv) );
      }
    }
    if ( m_is_rat ) {
      cv[m_dim] = 1.0;
    }
    rc = true;
  }
	DestroyCurveTree();
  return rc;
}

bool 
ON_NurbsCurve::SetCV( int i, const ON_4dPoint& point )
{
  bool rc = false;
  double* cv = CV(i);
  if ( cv ) {
    if ( m_is_rat ) {
      cv[0] = point.x;
      if ( m_dim > 1 ) {
        cv[1] = point.y;
        if ( m_dim > 2 )
          cv[2] = point.z;
        if ( m_dim > 3 ) {
          memset( &cv[3], 0, (m_dim-3)*sizeof(*cv) );
        }
      }
      cv[m_dim] = point.w;
      rc = true;
    }
    else {
      double w;
      if ( point.w != 0.0 ) {
        w = 1.0/point.w;
        rc = true;
      }
      else {
        w = 1.0;
      }
      cv[0] = w*point.x;
      if ( m_dim > 1 ) {
        cv[1] = w*point.y;
        if ( m_dim > 2 ) {
          cv[2] = w*point.z;
        }
        if ( m_dim > 3 ) {
          memset( &cv[3], 0, (m_dim-3)*sizeof(*cv) );
        }
      }
    }
  }
	DestroyCurveTree();
  return rc;
}

bool 
ON_NurbsCurve::GetCV( int i, ON::point_style style, double* Point ) const
{
  const double* cv = CV(i);
  if ( !cv )
    return false;
  int dim = Dimension();
  double w = ( IsRational() ) ? cv[dim] : 1.0;
  switch(style) {
  case ON::euclidean_rational:
    Point[dim] = w;
    // no break here
  case ON::not_rational:
    if ( w == 0.0 )
      return false;
    w = 1.0/w;
    while(dim--) *Point++ = *cv++ * w;
    break;
  case ON::homogeneous_rational:
    Point[dim] = w;
    memcpy( Point, cv, dim*sizeof(*Point) );
    break;
  case ON::intrinsic_point_style:
    memcpy( Point, cv, CVSize()*sizeof(*Point) );
    break;
  default:
    return false;
  }
  return true;
}

const ON_4dPoint ON_NurbsCurve::ControlPoint(
  int cv_index
) const
{
  ON_4dPoint cv;
  if (!GetCV(cv_index, cv))
    cv = ON_4dPoint::Nan;
  return cv;
}

const ON_2dex ON_NurbsCurve::ControlPointSpans(int control_point_index) const
{
  return ON_BsplineControlPointSpans(m_order, m_cv_count, control_point_index);
}

const ON_Interval ON_NurbsCurve::ControlPointSupport(int control_point_index) const
{
  return ON_BsplineControlPointSupport(m_order, m_cv_count, m_knot, control_point_index);
}

bool 
ON_NurbsCurve::GetCV( int i, ON_3dPoint& point ) const
{
  bool rc = false;
  const double* cv = CV(i);
  if ( cv ) {
    if ( m_is_rat ) {
      if (cv[m_dim] != 0.0) {
        const double w = 1.0/cv[m_dim];
        point.x = cv[0]*w;
        point.y = (m_dim>1)? cv[1]*w : 0.0;
        point.z = (m_dim>2)? cv[2]*w : 0.0;
        rc = true;
      }
    }
    else {
      point.x = cv[0];
      point.y = (m_dim>1)? cv[1] : 0.0;
      point.z = (m_dim>2)? cv[2] : 0.0;
      rc = true;
    }
  }
  return rc;
}

bool 
ON_NurbsCurve::GetCV( int i, ON_4dPoint& point ) const
{
  bool rc = false;
  if (m_dim > 0 && i >= 0 && i < m_cv_count)
  {
    const double* cv = CV(i);
    if (cv) {
      point.x = cv[0];
      point.y = (m_dim > 1) ? cv[1] : 0.0;
      point.z = (m_dim > 2) ? cv[2] : 0.0;
      point.w = (m_is_rat) ? cv[m_dim] : 1.0;
      rc = true;
    }
  }
  return rc;
}

bool ON_NurbsCurve::SetKnot( int knot_index, double k )
{
  if ( knot_index < 0 || knot_index >= KnotCount() )
    return false;
  m_knot[knot_index] = k;
	DestroyCurveTree();
  return true;
}

bool ON_NurbsCurve::SetStartPoint(
        ON_3dPoint start_point
        )
{
  bool rc = false;
  if ( IsValid() )
  {
    if (ON_Curve::SetStartPoint(start_point))
    {
      rc = true;
    }
    else
    {
      ClampEnd(2);


      double w = 1.0;
      if (IsRational()) {
        w = Weight(0);
        start_point *= w;
      }
      SetCV(0,start_point);
      if (IsRational())
        SetWeight(0, w);


      DestroyCurveTree();
      rc = true;
    }
  }
  return rc;
}

bool ON_NurbsCurve::SetEndPoint(
        ON_3dPoint end_point
        )
{
  bool rc = false;
  if ( IsValid() )
  {
    if (ON_Curve::SetEndPoint(end_point))
    {
      rc = true;
    }
    else
    {
      ClampEnd(2);


      double w = 1.0;
      if (IsRational()) {
        w = Weight(m_cv_count-1);
        end_point *= w;
      }
      SetCV(m_cv_count-1,end_point);
      if (IsRational())
        SetWeight(m_cv_count-1, w);


    	DestroyCurveTree();
      rc = true;
    }
  }
  return rc;
}


bool
ON_NurbsCurve::Reverse()
{
  bool rc0 = ON_ReverseKnotVector( m_order, m_cv_count, m_knot );
  bool rc1 = ON_ReversePointList( m_dim, m_is_rat, m_cv_count, m_cv_stride, m_cv );
	DestroyCurveTree();
  return rc0 && rc1;
}

bool
ON_NurbsCurve::SwapCoordinates( int i, int j )
{
	DestroyCurveTree();
  return  ON_SwapPointListCoordinates( m_cv_count, m_cv_stride, m_cv, i, j );
}

double ON_NurbsCurve::GrevilleAbcissa(
         int gindex  // index (0 <= index < CVCount(dir)
         ) const
{
  return ON_GrevilleAbcissa( m_order, m_knot+gindex );
}

bool ON_NurbsCurve::GetGrevilleAbcissae( // see ON_GetGrevilleAbcissa() for details
         double* g         // g[m_cv_count]
         ) const
{
  // The "false" for the 4th parameter is on purpose and should not be
  // replaced with this->IsPeriodic().  The problem
  // being that when the 4th parameter is true, it is not possible
  // to determine which subset of the full list of Greville abcissae
  // was returned.
  return ON_GetGrevilleAbcissae( m_order, m_cv_count, m_knot, false, g );
}


bool ON_NurbsCurve::ZeroCVs()
{
  bool rc = false;
  int i;
  if ( m_cv ) 
  {
    if ( CVCapacity() > 0 )
    {
      memset( m_cv, 0, CVCapacity()*sizeof(*m_cv) );
      if ( m_is_rat ) {
        for ( i = 0; i < m_cv_count; i++ ) {
          SetWeight( i, 1.0 );
        }
      }
      rc = true;
    }
    else {
      double* cv;
      int s = CVSize()*sizeof(*cv);
      for ( i = 0; i < m_cv_count; i++ ) {
        cv = CV(i);
        memset(cv,0,s);
        if ( m_is_rat )
          cv[m_dim] = 1.0;
      }
      rc = (i>0) ? true : false;
    }
  }
	DestroyCurveTree();
  return rc;
}

bool ON_NurbsCurve::IsClamped( // determine if knot vector is clamped
      int end // (default= 2) end to check: 0 = start, 1 = end, 2 = start and end
      ) const
{
  return ON_IsKnotVectorClamped( m_order, m_cv_count, m_knot, end );
}
  
bool ON_NurbsCurve::IsNatural(int end) const
{
  bool rc = false;
  ON_3dPoint CV0, CV2, P;
  ON_3dVector D1, D2;
  const ON_Interval domain(Domain());
  for (int pass = ((0==end||2==end) ? 0 : 1); pass < ((1==end||2==end)?2 : 1); ++pass)
  {
    ON_BezierCurve span;
    if (false == ConvertSpanToBezier(((0 == pass) ? 0 : (m_cv_count - m_order)), span) || span.m_order < 2)
      return false;
    int i0 = (0 == pass) ? 0 : span.m_order - 1;
    int di = (0 == pass) ? 1 : -1;
    if (span.m_order > 2)
      di *= 2;
    if (false == span.GetCV(i0, CV0))
      return false;
    if (false == span.GetCV(i0 + di, CV2))
      return false;
    Ev2Der(domain[pass], P, D1, D2, (0 == pass) ? 1 : -1);
    const double d2 = D2.Length();
    const double tol = CV0.DistanceTo(CV2)*1.0e-8;
    if (false == (d2 <= tol))
      return false;
    rc = true;      
  }
  return rc;
}

int ON_NurbsCurve::CVCapacity() const
{
  // If m_cv_capacity > 0, then m_cv[] was allocated by onmalloc(sz)/onrealloc(...,sz)
  // where sz = m_cv_capacity*sizeof(double).
  return m_cv_capacity; // number of doubles in m_cv
}

bool ON_NurbsCurve::ReserveCVCapacity(int desired_capacity)
{
  if (nullptr != m_cv && 0 == m_cv_capacity)
  {
    // If m_cv_capacity == 0 and m_cv != nullptr, then the "expert" user
    // has hand built the ON_NurbsCurve.m_cv array and is responsible
    // for making sure it's always big enough.
    return true;
  }

  const int current_capacity = (nullptr != m_cv && m_cv_capacity > 0) ? m_cv_capacity : 0;
  if ( desired_capacity > current_capacity )
  {
    m_cv = (0 == current_capacity)
      ? (double*)onmalloc(desired_capacity*sizeof(*m_cv))
      : (double*)onrealloc(m_cv,desired_capacity*sizeof(*m_cv));
    m_cv_capacity = ( nullptr != m_cv ) ? desired_capacity : 0;
  }

  const bool rc = (m_cv_capacity >= desired_capacity);
  return rc;
}

int ON_NurbsCurve::KnotCapacity() const
{
  const int knot_capacity 
    = (nullptr == m_knot) 
    ? 0 
    : ((int)(m_knot_capacity_and_tags & ON_NurbsCurve::masks::knot_capacity));
  return knot_capacity;
}

void ON_NurbsCurve::UnmanageKnotForExperts(
  int& knot_capacity,
  double*& knot
)
{
  knot_capacity = KnotCapacity();
  knot = m_knot;
  m_knot_capacity_and_tags &= ON_NurbsCurve::masks::all_tags; // knot_capacity = 0;  
  m_knot = nullptr;
}

void ON_NurbsCurve::ManageKnotForExperts(
  int knot_capacity,
  double* knot
)
{
  // Unconditionally set m_knot and KnotCapacity().
  // (Do not free preexisting m_knot.)
  const unsigned int tags = (m_knot_capacity_and_tags & ON_NurbsCurve::masks::all_tags);
  const unsigned int new_knot_capacity = (knot_capacity > 0) ? (((unsigned int)knot_capacity) & ON_NurbsCurve::masks::knot_capacity) : 0U;
  m_knot_capacity_and_tags = (tags | new_knot_capacity);
  m_knot = knot;
}

bool ON_NurbsCurve::ReserveKnotCapacity(int desired_capacity)
{
  const int current_knot_capacity = KnotCapacity();

  if (nullptr != m_knot && 0 == current_knot_capacity)
  {
    // If knot_capacity == 0 and m_knot != nullptr, then the "expert" user
    // has hand built the ON_NurbsCurve.m_knot array and is responsible
    // for making sure it's always big enough.
    return true;
  }

  if ( desired_capacity > current_knot_capacity )
  {
    double* knot 
      = ( 0 == current_knot_capacity )
      ? (double*)onmalloc(desired_capacity*sizeof(knot[0]))
      : (double*)onrealloc(m_knot,desired_capacity*sizeof(knot[0]));
    this->ManageKnotForExperts((nullptr != knot) ? desired_capacity : 0, knot);
  }

  bool rc = (nullptr != m_knot && KnotCapacity() >= desired_capacity);
  return rc;
}


bool ON_NurbsCurve::ConvertSpanToBezier( int span_index, ON_BezierCurve& bez ) const
{
  bool rc = false;
  if ( span_index >= 0 && span_index <= m_cv_count-m_order && m_knot && m_cv ) 
  {
    const int cvdim = CVSize();
    const int sizeof_cv = cvdim*sizeof(*bez.m_cv);
    int i;
    rc = bez.ReserveCVCapacity( cvdim*m_order );
    if ( rc ) {
      bez.m_dim = m_dim;
      bez.m_is_rat = m_is_rat;
      bez.m_order = m_order;
      bez.m_cv_stride = cvdim;
      if ( bez.m_cv_stride == m_cv_stride )
      {
        memcpy( bez.m_cv, CV(span_index), bez.m_order*sizeof_cv );
      }
      else
      {
        for ( i = 0; i < m_order; i++ ) {
          memcpy( bez.CV(i), CV(span_index+i), sizeof_cv );
        }
      }
      const double* knot = m_knot + span_index;
			if( knot[m_order-2] < knot[m_order-1] )
				ON_ConvertNurbSpanToBezier( cvdim, bez.m_order, bez.m_cv_stride, bez.m_cv,
																		knot, knot[m_order-2], knot[m_order-1] );
			else
				rc = false;
    }
  }
  return rc;
}


bool ON_NurbsCurve::HasBezierSpans() const
{
  return ON_KnotVectorHasBezierSpans( m_order, m_cv_count, m_knot );
}

bool ON_NurbsCurve::MakePiecewiseBezier( bool bSetEndWeightsToOne )
{
  bool rc = HasBezierSpans();
  if ( !rc && IsValid() ) 
  {
    ON_Workspace ws;
    DestroyRuntimeCache();
    if ( !ClampEnd(2) )
      return false;
    int span_count = SpanCount();
    //int knot_count = KnotCount();
    ReserveKnotCapacity( (span_count + 1)*(m_order-1) );
    ReserveCVCapacity( m_cv_stride*(span_count*(m_order-1) + 1) );
    double* t = ws.GetDoubleMemory( span_count+1);
    GetSpanVector( t );
    int cvdim = CVSize();
    ON_BezierCurve* bez = new ON_BezierCurve[span_count];
    int ki, spani, i;
    for ( ki = m_order-2, spani = 0; ki < m_cv_count-1 && spani < span_count; ki++ ) {
      if ( m_knot[ki] < m_knot[ki+1] ) {
        bez[spani].Create(m_dim,m_is_rat,m_order);
        for ( i = 0; i < m_order; i++ )
          bez[spani].SetCV(  i, ON::intrinsic_point_style, CV( i + ki - m_order + 2 ) );
        ON_ConvertNurbSpanToBezier( cvdim, bez[spani].m_order, bez[spani].m_cv_stride, bez[spani].m_cv,
                                    m_knot+ki-m_order+2, m_knot[ki], m_knot[ki+1] );
        spani++;
      }
    }
    m_cv_count = span_count*(m_order-1) + 1;
    for ( spani = 0; spani < span_count; spani++ ) {
      for ( i = 0; i < m_order; i++ ) {
        SetCV(  spani*(m_order-1) + i, ON::intrinsic_point_style, bez[spani].CV( i ) );
      }
      for ( ki = 0; ki < m_order-1; ki++ )
        m_knot[ki+spani*(m_order-1)] = t[spani];
    }
    for ( ki = 0; ki < m_order-1; ki++ )
      m_knot[ki+span_count*(m_order-1)] = t[spani];
    delete[] bez;
    rc = true;
  }
  if ( rc && bSetEndWeightsToOne && m_is_rat )
  {
    // 2 June 2003 Dale Lear - added support for bSetEndWeightsToOne=true option.
    double w0, w1;
    ON_BezierCurve bez;
    bez.m_dim = m_dim;
    bez.m_is_rat = m_is_rat;
    bez.m_order = m_order;
    bez.m_cv_stride = m_cv_stride;

    bez.m_cv = CV(0);
    if ( bez.Weight(0) != 1.0 )
    {
      DestroyRuntimeCache();
      w0 = 1.0;
      w1 = (m_order == m_cv_count) ? 1.0 : bez.Weight(m_order-1);
      bez.ChangeWeights(0,w0,m_order-1,w1);
    }
 
    bez.m_cv = CV(m_cv_count-m_order);
    if ( bez.Weight(m_order-1) != 1.0 )
    {
      DestroyRuntimeCache();
      w0 = bez.Weight(0);
      w1 = 1.0; // 23 June 2003
      bez.ChangeWeights(0,w0,m_order-1,w1);
    }

    bez.m_cv = 0;
  }
  return rc;
}


double ON_NurbsCurve::ControlPolygonLength() const
{
  double length = 0.0;
  ON_GetPolylineLength( m_dim, m_is_rat, m_cv_count, m_cv_stride, m_cv, &length );
  return length;
}


bool ON_NurbsCurve::InsertKnot( double knot_value, int knot_multiplicity )
{
  bool rc = false;

  const int degree = Degree();

  double t0, t1;
  {
    ON_Interval d = Domain();
    if ( !d.IsIncreasing() )
      return false;
    t0 = d[0];
    t1 = d[1];
  }
  
  if ( knot_multiplicity < 1 || knot_multiplicity > degree ) 
  {
    ON_ERROR("ON_NurbsCurve::ON_InsertKnot(): knot_multiplicity < 1 or knot_multiplicity > degree.");
    return false;
  }

  if( knot_value < t0 || knot_value > t1 )
  {
    ON_ERROR("ON_InsertKnot(): knot_value not in NURBS curve domain.");
    return false;
  }

  if ( knot_value == t0 ) 
  {
    if ( knot_multiplicity == degree ) 
    {
      rc = ClampEnd(0);
    }
    else if ( knot_multiplicity == 1 ) 
    {
      rc = true;
    }
    else 
    {
      ON_ERROR("ON_InsertKnot(): knot_value = t0 and 1 < knot_multiplicity < degree.");
      rc = false;
    }
    return rc;
  }

  if ( knot_value == t1 ) 
  {
    if ( knot_multiplicity == degree ) 
    {
      rc = ClampEnd(1);
    }
    else if ( knot_multiplicity == 1 ) 
    {
      rc = true;
    }
    else 
    {
      ON_ERROR("ON_InsertKnot(): knot_value = t1 and 1 < knot_multiplicity < degree.");
      rc = false;
    }
    return rc;
  }

  DestroyCurveTree();

  bool bIsPeriodic = (degree>1) ? IsPeriodic() : false;
  int span_index = ON_NurbsSpanIndex( m_order, m_cv_count, m_knot, knot_value, 0, 0 );

  // reserve room for new knots and cvs
  if ( !ReserveCVCapacity( m_cv_stride*(m_cv_count+knot_multiplicity) ) )
    return false;
  if ( !ReserveKnotCapacity( KnotCount()+knot_multiplicity ) )
    return false;
  if ( bIsPeriodic ) {
  }

  rc = true;
  int span_hint = span_index;
  int new_knot_count = ON_InsertKnot( knot_value, knot_multiplicity, 
                                      CVSize(), m_order, m_cv_count, 
                                      m_cv_stride, m_cv, m_knot, &span_hint );
  if ( new_knot_count > 0 ) 
  {
    m_cv_count += new_knot_count;
  }

  if ( bIsPeriodic && rc && !IsPeriodic() ) {
    // restore periodic form
    if ( ON_MakeKnotVectorPeriodic( m_order, m_cv_count, m_knot ) ) {
      int i0, i1;
      for ( i0 = 0, i1 = m_cv_count-degree; i0 < degree; i0++, i1++ ) {
        //14 May 2015 - Chuck - Fix for curves with low span count.  See RH-30358
        //if ( span_index < degree-1)
        if (i0 > span_index)
          SetCV( i1, ON::intrinsic_point_style, CV(i0) ); // cv[i1] = cv[i0]
        else
          SetCV( i0, ON::intrinsic_point_style, CV(i1) ); // cv[i0] = cv[i1]
      }
    }
    else {
      ClampEnd(2);
    }
  }

  return rc;
}

bool ON_NurbsCurve::MakeRational()
{
  if ( !IsRational() ) {
    const int dim = Dimension();
    const int cv_count = CVCount();
    if ( cv_count > 0 && m_cv_stride >= dim && dim > 0 ) {
      const int new_stride = (m_cv_stride == dim) ? dim+1 : m_cv_stride;
      ReserveCVCapacity( cv_count*new_stride );
      const double* old_cv;
      double* new_cv;
      int cvi, j;
      for ( cvi = cv_count-1; cvi>=0; cvi-- ) {
        old_cv = CV(cvi);
        new_cv = m_cv+(cvi*new_stride);
        for ( j = dim-1; j >= 0; j-- ) {
          new_cv[j] = old_cv[j];
        }
        new_cv[dim] = 1.0;
      }
      m_cv_stride = new_stride;
      m_is_rat = 1;
    }
  }
  return IsRational();
}

bool ON_NurbsCurve::MakeNonRational()
{
  if ( IsRational() ) {
    const int dim = Dimension();
    const int cv_count = CVCount();
    if ( cv_count > 0 && m_cv_stride >= dim+1 && dim > 0 ) {
      double w;
      const double* old_cv;
      double* new_cv = m_cv;
      int cvi, j;
      for ( cvi = 0; cvi < cv_count; cvi++ ) {
        old_cv = CV(cvi);
        w = old_cv[dim];
        w = ( w != 0.0 ) ? 1.0/w : 1.0;
        for ( j = 0; j < dim; j++ ) {
          *new_cv++ = w*(*old_cv++);
        }
      }
      m_is_rat = 0;
      m_cv_stride = dim;
    }
  }
	DestroyCurveTree();
  return ( !IsRational() ) ? true : false;
}

static bool GetRaisedDegreeCV(int old_order, 
                              int cvdim,
                              int old_cvstride,
                              const double* oldCV, //old_cvstride*old_order
                              const double* oldkn, //2*old_degree
                              const double* newkn, //2*old_order
                              int cv_id,     //0 <= cv_id <= old_order
                              double* newCV  //cvdim
                              )

{
  int i,j,k;

  if (!oldCV || !oldkn || !newkn || !newCV || cv_id < 0 || cv_id > old_order)
    return false;

  int old_degree = old_order-1;
  int new_degree = old_degree+1;

  double* t = (double*)onmalloc(old_degree*sizeof(double));
  if (!t) return false;
  double* P = (double*)onmalloc(cvdim*sizeof(double));
  if (!P) {
    onfree((void*)t);
    return false;
  }

  memset(newCV, 0, cvdim*sizeof(double));

  const double* kn = newkn + cv_id;

  for (i=0; i<new_degree; i++){
    k=0;
    for (j=0; j<new_degree; j++){
      if (j != i) {
        t[k] = kn[j];
        k++;
      }
    }
    if (!ON_EvaluateNurbsBlossom(cvdim, old_order, 
      old_cvstride, oldCV, oldkn, t, P)){
      onfree((void*)t);
      onfree((void*)P);
      return false;
    }
    for (k=0; k<cvdim; k++) newCV[k] += P[k];
  }

  double denom = (double)new_degree;
  for (i=0; i<cvdim; i++) 
    newCV[i] /= denom;

  onfree((void*)t);
  onfree((void*)P);

  return true;
}


static bool IncrementNurbDegree(ON_NurbsCurve& N)
//for use only in ON_NurbsCurve::IncreaseDegree().  No validation done.
//N is assumed to have sufficient knot and cv capacities, clamped ends

{
  ON_NurbsCurve M = N;
  int span_count = M.SpanCount();
  int new_kcount = M.KnotCount() + span_count + 1;
  N.m_order = M.Order()+1;
  N.m_cv_count = new_kcount - N.Order() + 2;

  //set N's knots
  int i=0;
  int k=0;
  int j;
  while (i<M.CVCount()){
    double kn = M.Knot(i);
    int mult = M.KnotMultiplicity(i);
    for (j=0; j<=mult; j++) {
      N.SetKnot(k, kn);
      k++;
    }
    i+=mult;
  }
  //zero out N's cvs
  memset(N.m_cv, 0, N.CVCapacity()*sizeof(double));
  int cvdim = N.CVSize();
  const double* cvM;
  double* cvN;
  const double* knotN;
  const double* knotM;
  int siN = 0;
  int siM = 0;

  for (i=0; i<span_count; i++){
    knotN = &N.m_knot[siN];
    knotM = &M.m_knot[siM];
    cvM = M.CV(siM);
    cvN = N.CV(siN);
    int span_mult = N.KnotMultiplicity(siN+N.Degree()-1);
    int skip = N.Order()-span_mult;
    cvN += skip*N.m_cv_stride;
    for (j=skip; j<N.Order(); j++){//calculate each cv of the span
      GetRaisedDegreeCV(M.Order(), cvdim, M.m_cv_stride, cvM, knotM, knotN, j, cvN);
      cvN += N.m_cv_stride;
    }
    siN = ON_NextNurbsSpanIndex(N.Order(), N.CVCount(), N.m_knot, siN);
    siM = ON_NextNurbsSpanIndex(M.Order(), M.CVCount(), M.m_knot, siM);
  }

  //set first and last equal to original
  cvM = M.CV(0);
  cvN = N.CV(0);
  for (i=0; i<cvdim; i++) cvN[i] = cvM[i];

  cvM = M.CV(M.CVCount()-1);
  cvN = N.CV(N.CVCount()-1);
  for (i=0; i<cvdim; i++) cvN[i] = cvM[i];

  return true;
}

bool ON_NurbsCurve::IncreaseDegree( int desired_degree )
{
  if ( desired_degree < 1 || desired_degree < m_order-1 ) return false;
  if ( desired_degree == m_order-1 ) return true;
  if (!ClampEnd(2)) return false;

  int del = desired_degree - Degree();
  int new_order = Order()+del;
  int span_count = SpanCount();
  int new_kcount = KnotCount()+(span_count+1)*del;
  int new_cvcount = new_kcount - new_order + 2;

  if (!ReserveKnotCapacity(new_kcount)) return false;
  if (!ReserveCVCapacity(new_cvcount*m_cv_stride)) return false;

  for (int i=0; i<del; i++) {
    if (!IncrementNurbDegree(*this)) return false;
  }

  return true;
}

bool ON_NurbsCurve::ChangeDimension( int desired_dimension )
{
  bool rc = false;
  int i, j;
  if ( desired_dimension < 1 )
    return false;
  if ( desired_dimension == m_dim )
    return true;

  DestroyCurveTree();

  if ( desired_dimension < m_dim ) 
  {
    if ( m_is_rat ) {
      double* cv;
      for ( i = 0; i < m_cv_count; i++ ) {
        cv = CV(i);
        cv[desired_dimension] = cv[m_dim];
      }
    }
    m_dim = desired_dimension;
    rc = true;
  }
  else 
  {
    const double* cv0;
    double* cv1;
    //const int cv_size0 = CVSize();
    const int cv_size1 = m_is_rat ? desired_dimension + 1 : desired_dimension;
    const int cv_stride1 = (m_cv_stride < cv_size1) ? cv_size1 : m_cv_stride;
    if ( m_cv_stride < cv_stride1 && CVCapacity() > 0 )
    {
      const int new_cv_capacity = cv_stride1*m_cv_count;
      m_cv = (double*)onrealloc( m_cv, new_cv_capacity*sizeof(*m_cv) );
      if (nullptr != m_cv)
        m_cv_capacity = new_cv_capacity;
    }
    for ( i = CVCount()-1; i >= 0; i-- ) {
      cv0 = CV(i);
      cv1 = m_cv + (i*cv_stride1);
      if ( m_is_rat )
        cv1[desired_dimension] = cv0[m_dim];
      for ( j = desired_dimension-1; j >= m_dim; j-- ) {
        cv1[j] = 0.0;
      }
      for ( j = m_dim-1; j >= 0; j-- ) {
        cv1[j] = cv0[j];
      }
    }
    m_dim = desired_dimension;
    m_cv_stride = cv_stride1;
    rc = true;
  }
  return rc;
}

bool ON_NurbsCurve::Append( const ON_NurbsCurve& c )
{
  bool rc = false;

  if ( CVCount() == 0 ) {
    *this = c;
    return IsValid()?true:false;
  }

  if ( c.IsRational() && !IsRational() ) {
    if ( !MakeRational() )
      return false;
  }
  if ( c.Degree() > Degree() ) {
    if ( !IncreaseDegree( c.Degree() ) )
      return false;
  }
  if ( c.Dimension() > Dimension() ) {
    if ( !ChangeDimension( c.Dimension() ) )
      return false;
  }

  if (    (IsRational() && !c.IsRational())
       || c.Degree() < Degree() 
       || !c.IsClamped(0) 
       || c.Dimension() < Dimension() ) 
  {
    ON_NurbsCurve tmp(c);
    if ( !tmp.IncreaseDegree( Degree() ) )
      return false;
    if ( !tmp.ChangeDimension( Dimension() ) )
      return false;
    if ( IsRational() ) {
      if ( !tmp.MakeRational() )
        return false;
    }
    if ( !tmp.ClampEnd(0) )
      return false;

    // make sure we don't reenter this scope
    if ( tmp.IsRational() != IsRational() )
      return false;
    if ( tmp.Degree() != Degree() )
      return false;
    if ( tmp.Dimension() != Dimension() )
      return false;
    if ( !tmp.IsClamped(0) )
      return false;
    return Append(tmp);
  }

  if (    IsValid() 
       && c.IsValid() 
       && Degree() == c.Degree() 
       && IsRational() == c.IsRational() 
       && Dimension() == c.Dimension() ) 
  {
    if ( !ClampEnd(1) )
      return false;
    const double w0 = c.Weight(0);
    const double w1 = Weight(CVCount()-1);
    double w = 1.0;
    if ( IsRational() && w0 != w1 ) {
      w = w1/w0;
    }
    ReserveCVCapacity( (CVCount()+c.CVCount())*m_cv_stride );
    ReserveKnotCapacity( ON_KnotCount(Order(),CVCount()+c.CVCount()) );
    const double dk = Knot(CVCount()-1) - c.Knot(c.Order()-2);


    //const int c_cv_count = c.CVCount();
    const int c_knot_count = c.KnotCount();
    int i0, i1, i2, j;

		// i0 and cv index into m_knot and m_cv respectively 
		i0 = KnotCount();
		double* cv = CV(CVCount() - 1);
		const int cv_dim = CVSize();
		const int sizeof_cv = cv_dim * sizeof(*cv);

		// i1 and i2 index c's knots and cvs respectively
		i2 = 1;
		for ( i1 = c.Order()-1; i1 < c_knot_count; i1++, i2++ ) {
			double knot = c.Knot(i1) + dk;
			// GBA 20-April-2017  Check for span collapse
			if (knot > m_knot[i0 - Order() + 1])
			{
				m_knot[i0++] = knot;
				cv += m_cv_stride;
				m_cv_count++;
			}
			memcpy(cv, c.CV(i2), sizeof_cv);
			if (w != 1.0) {
				for (j = 0; j < cv_dim; j++)
					cv[j] *= w;
			}	
		}

    rc = true;
  }
  return rc;
}

static
bool TweakSplitTrimParameter(double k0, double k1, double& t )
{
  // [k0,k1] = knots that bracket trim/split parameter t
  // returns true if parameter is tweaked
  // The purpose of the tweak is to avoid creating knot
  // vectors that cause numerical problems during evaluation.
  bool rc = false;
  if (k0 < t && t < k1)
  {
    // Nov 7, 2008 Lowell Walmsley 
    // Changed this from ON_SQRT_EPSILON to 4*ON_SQRT_EPSILON because 
    // to make it less likely to get very narrow knot spans
    // Dale says the intention is to round off to 8 sig figs
    //
    // 2014-July-7 Dale Lear
    //  Fix RH-21610 (k0 = 5e6, k1 = k0 + 1, t = k1 - 0.2)
    //  I changed the test Lowell refers to above.  Lowell's 4.0*ON_SQRT_EPSILON
    //  is now 8.0*ON_EPSILON in the ktol2 initialization value.
    //  I added ktol1 base on the span length.  
    //  If you modify this code in the future, please reference a bug with sample 
    //  files so any new "fixes" don't break something we've already fixed.
    const double ktol1 = (k1 - k0)*ON_SQRT_EPSILON;
    const double ktol2 = (fabs(k0) + fabs(k1))*8.0*ON_EPSILON;
    const double ktol = (ktol1 > ktol2) ? ktol1 : ktol2;
    if (t - k0 <= ktol && k1 - t > 16.0*ktol)
    {
      t = k0;
      rc = true;
    }
    else if (k1 - t <= ktol && t - k0 > 16.0*ktol)
    {
      t = k1;
      rc = true;
    }
  }
  return rc;
}



bool ON_NurbsCurve::Trim( const ON_Interval& in )
{
  if ( !in.IsIncreasing() )
    return false;

  const int cv_dim = CVSize();
  const int order = Order();
  double t, split_t;
  int ki, side, i0, i1, i1_max, new_cv_count;

	//Greg Arden 28 April 2003.  Do not change any curve that is trimmed to its entire domain.
	//             This is especially important for periodic curves.
	if(in==Domain())
	  return true;


  DestroyCurveTree();

  // cut off right end (or extend if in.m_t[1] > Domain.Max()
  side = -1;
  t = in.m_t[1]; // trimming parameter
  ki = ON_NurbsSpanIndex( order, m_cv_count, m_knot, t, side, 0 );

  // if t is very close to a knot value, then trim at the knot
  split_t = t;
  if ( TweakSplitTrimParameter(m_knot[ki+order-2], m_knot[ki+order-1], split_t ) )
    ki = ON_NurbsSpanIndex( order, m_cv_count, m_knot, split_t, side, ki );

  if ( !ON_EvaluateNurbsDeBoor( cv_dim, order, m_cv_stride, CV(ki),
                                m_knot + ki, side, 0.0, t ) ) 
  {
    ON_ERROR("ON_NurbsCurve::Trim() - right end de Boor algorithm failed.");
    return false;
  }
  // clamp right end knots
  m_cv_count = ki + order;
  for ( i0 = ON_KnotCount( order, m_cv_count)-1; i0 >= m_cv_count-1; i0--)
    m_knot[i0] = t;

  // cut off left end (or extend if in.m_t[0] < Domain.Max()
  side = 1;
  t = in.m_t[0]; // trimming parameter
  ki = ON_NurbsSpanIndex( order, m_cv_count, m_knot, t, side, 0 );

  // if t is very close to a knot value, then trim at the knot
  split_t = t;
  if (TweakSplitTrimParameter(m_knot[ki + order - 2], m_knot[ki + order - 1], split_t))
    ki = ON_NurbsSpanIndex( order, m_cv_count, m_knot, split_t, side, ki );

  if ( !ON_EvaluateNurbsDeBoor( cv_dim, order, m_cv_stride, CV(ki),
                                m_knot + ki, side, 0.0, t ) ) 
  {
    ON_ERROR("ON_NurbsCurve::Trim() - right end de Boor algorithm failed.");
    return false;
  }

  // remove surplus cvs and knots
  new_cv_count = m_cv_count - ki;
  if ( new_cv_count < m_cv_count ) {
    // move cvs and knots over
    i1_max = m_cv_stride*m_cv_count;
    for ( i0 = 0, i1 = ki*m_cv_stride; i1 < i1_max; i0++, i1++ )
      m_cv[i0] = m_cv[i1];
    i1_max = ON_KnotCount( order, m_cv_count );
    for ( i0 = 0, i1 = ki; i1 < i1_max; i0++, i1++ )
      m_knot[i0] = m_knot[i1];
    m_cv_count = new_cv_count;
  }

  // clamp left end knots
  for (i0 = 0; i0 <= order-2; i0++)
    m_knot[i0] = t;

  ClampEnd(2); // 26 June 2003 Dale Lear

	DestroyCurveTree();
  return true;
}


bool ON_NurbsCurve::Extend(
  const ON_Interval& domain
  )

{
  if (IsClosed()) return false;
  bool is_rat = IsRational() ? true : false;
  int dim = Dimension();
  int cvdim = dim+is_rat;

  bool changed = false;
  if (domain[0] < Domain()[0]){
    ClampEnd(0);
    ON_EvaluateNurbsDeBoor(cvdim,Order(),m_cv_stride, CV(0),m_knot,1,0.0,domain[0]);
    for (int i = 0; i < Order()-1; i++)
			m_knot[i] = domain[0];
    changed = true;
  }
  if (domain[1] > Domain()[1]){
    ClampEnd(1);
    int i = CVCount() - Order();
    ON_EvaluateNurbsDeBoor(cvdim,Order(),m_cv_stride, CV(i),m_knot + i,-1,0.0,domain[1]);
    for (i = KnotCount()-1; i >= CVCount()-1; i--)
			m_knot[i] = domain[1];
    changed = true;
  }

  if (changed){
    DestroyCurveTree();
  }
  return changed;
}

bool ON_NurbsCurve::Split(
    double t,    // t = curve parameter to split curve at
    ON_Curve*& left_crv, // left portion returned here (must be an ON_NurbsCurve)
    ON_Curve*& right_crv // right portion returned here (must be an ON_NurbsCurve)
  ) const
{

  int i;
  bool rc = false;
  if ( left_crv && !ON_NurbsCurve::Cast(left_crv) )
    return false;
  if ( right_crv && !ON_NurbsCurve::Cast(right_crv) )
    return false;
  if ( IsValid() && t > m_knot[m_order-2] && t < m_knot[m_cv_count-1] ) 
  {
    ON_NurbsCurve* left = (ON_NurbsCurve*)left_crv;
    ON_NurbsCurve* right = (ON_NurbsCurve*)right_crv;
    if ( !left )
      left = new ON_NurbsCurve();
    else if ( left == right )
      return false;

    if ( !right )
      right = new ON_NurbsCurve();
    left->DestroyCurveTree();
    right->DestroyCurveTree();
    
    int span_index = ON_NurbsSpanIndex(m_order,m_cv_count,m_knot,t,1,0);
    // if t is very close to a knot value, then split at the knot
    double split_t = t;
    if (TweakSplitTrimParameter(m_knot[span_index + m_order - 2], m_knot[span_index + m_order - 1], split_t))
    {
      if ( split_t <= m_knot[m_order-2] || split_t >= m_knot[m_cv_count-1] ){
        // 22 October - greg added bailout code but didn't clean up???
        //   chuck fixed leak.
        if (!left_crv) delete left;
        if (!right_crv) delete right;
        return false;
      }
      span_index = ON_NurbsSpanIndex(m_order,m_cv_count,m_knot,split_t,1,span_index);
    }

    if ( span_index >= 0 && span_index <= m_cv_count - m_order ) 
    {
      const int cvdim = CVSize();

      //23 April 2015 - Chuck - maintain stride
      const int cv_stride = m_cv_stride;
      //const int sizeof_cv = cvdim*sizeof(double);
      const int sizeof_cv = cv_stride*sizeof(double);

      int left_cv_count = m_order + span_index;
      if ( span_index > 0 && split_t == m_knot[span_index+m_order-2] )
      { 
        // splitting exactly at a knot value
        int k;
        for ( k = 0; left_cv_count >= m_order && k <= span_index+m_order-2; k++ )
        {
          if ( split_t == m_knot[span_index+m_order-2-k] )
            left_cv_count--;
          else
            break;
        }
      }
      int right_cv_count = m_cv_count - span_index;
      if ( left_cv_count < m_order || right_cv_count < m_order ){
        // 22 October - greg added bailout code but didn't clean up???
        //   chuck fixed leak.
        if (!left_crv) delete left;
        if (!right_crv) delete right;
        return false;
      }

      if ( left != this )
      {
        left->m_dim = m_dim;
        left->m_is_rat = m_is_rat;
        left->m_order = m_order;
        left->m_cv_count = left_cv_count;
        //23 April 2015 - Chuck - maintain stride
        //left->m_cv_stride = cvdim;
        left->m_cv_stride = cv_stride;
      }
      if ( right != this )
      {
        right->m_dim = m_dim;
        right->m_is_rat = m_is_rat;
        right->m_order = m_order;
        right->m_cv_count = right_cv_count;
        //23 April 2015 - Chuck - maintain stride
        //right->m_cv_stride = cvdim;
        right->m_cv_stride = cv_stride;
      }

      // fill in left allowing for possibility that left = this
      if ( left->m_cv != m_cv ) 
      {
        //23 April 2015 - Chuck - maintain stride
        //left->ReserveCVCapacity(cvdim*left_cv_count);
        left->ReserveCVCapacity(cv_stride*left_cv_count);
        for( i = 0; i < left_cv_count; i++ ) {
          //23 April 2015 - Chuck - maintain stride
          //memcpy( left->m_cv + i*cvdim, CV(i), sizeof_cv );
          memcpy( left->m_cv + i*cv_stride, CV(i), sizeof_cv );
        }
      }
      if ( left->m_knot != m_knot ) 
      {
        i = ON_KnotCount( m_order, left_cv_count);
        left->ReserveKnotCapacity( i );
        memcpy( left->m_knot, m_knot, i*sizeof(left->m_knot[0]) );
      }
      
      // fill in right allowing for possibility that right = this
      if ( right->m_cv != m_cv || span_index > 0 )
      {
        //23 April 2015 - Chuck - maintain stride
        //right->ReserveCVCapacity(cvdim*right_cv_count);
        right->ReserveCVCapacity(cv_stride*right_cv_count);
        for( i = 0; i < right_cv_count; i++ ) {
          //23 April 2015 - Chuck - maintain stride
          //memmove( right->m_cv + i*cvdim, CV(i+span_index), sizeof_cv );
          memmove( right->m_cv + i*cv_stride, CV(i+span_index), sizeof_cv );
        }
      }
      if ( right->m_knot != m_knot || span_index > 0 ) 
      {
        i = ON_KnotCount(m_order, right_cv_count);
        right->ReserveKnotCapacity( i );
        memmove( right->m_knot, m_knot + span_index, i*sizeof(right->m_knot[0]) );
      }

      if ( right == this ) {
        right->m_cv_count = right_cv_count;
        //23 April 2015 - Chuck - maintain stride
        right->m_cv_stride = cv_stride;
      }

      if ( left == this ) {
        left->m_cv_count = left_cv_count;
        //23 April 2015 - Chuck - maintain stride
        left->m_cv_stride = cv_stride;
      }

      // trim right end of left NURBS
      i = left->m_cv_count - left->m_order;

      //23 April 2015 - Chuck - maintain stride
      // 31 Aug 2022 GBA RH69916 split at split_t not t.  Splitting at t produces a gap that can't be right.
      //ON_EvaluateNurbsDeBoor( cvdim, m_order, cvdim, left->CV(i), left->m_knot + i, -1, 0.0, t );
      ON_EvaluateNurbsDeBoor( cvdim, m_order, cv_stride, left->CV(i), left->m_knot + i, -1, 0.0, split_t);
      for ( i = left->m_cv_count-1; i < ON_KnotCount(left->m_order,left->m_cv_count); i++ )
        left->m_knot[i] = t;
      left->ClampEnd(2); // 26 June 2003 Dale Lear

      // trim left end of right NURBS

      //23 April 2015 - Chuck - maintain stride
     // 31 Aug 2022 GBA RH69916 split at split_t not t. Splitting at t produces a gap that can't be right.
      //ON_EvaluateNurbsDeBoor( cvdim, m_order, cvdim, right->m_cv, right->m_knot, +1, 0.0, t );
      ON_EvaluateNurbsDeBoor( cvdim, m_order, cv_stride, right->m_cv, right->m_knot, +1, 0.0, split_t);
      for ( i = 0; i <= right->m_order-2; i++ )
        right->m_knot[i] = t;
      right->ClampEnd(2); // 26 June 2003 Dale Lear

      if ( 0 == left_crv )
        left_crv = left;
      if ( 0 == right_crv )
        right_crv = right;
      rc = true;
    }
  }
  return rc;
}


int ON_NurbsCurve::GetNurbForm( ON_NurbsCurve& curve, 
                                double tolerance,
                                const ON_Interval* subdomain  // OPTIONAL subdomain of ON::ProxyCurve::Domain()
                                ) const
{
  int rc = 1;

  // 4 May 2007 Dale Lear
  //   I'm replacing the call to operator= with a call to
  //   Internal_DeepCopyFrom().  The operator= call
  //   was copying userdata and that does not happen for
  //   any other GetNurbForm overrides.  Copying userdata
  //   in GetNurbForm is causing trouble in Make2D and 
  //   other places that are creating NURBS copies in
  //   worker memory pools.

  // curve = *this; // copied user data

  curve.DestroyRuntimeCache(true);
  if (this != &curve)
  {
    curve.Internal_DeepCopyFrom(*this); // does not copy user data
  }

  if ( subdomain ) 
  {
    if ( !curve.Trim(*subdomain) )
      rc = 0;
  }
  return rc;
}

int ON_NurbsCurve::HasNurbForm() const
{
  return 1;
}


bool ON_NurbsCurve::GetCurveParameterFromNurbFormParameter(
      double nurbs_t,
      double* curve_t
      ) const
{
  *curve_t = nurbs_t;
  return true;
}

bool ON_NurbsCurve::GetNurbFormParameterFromCurveParameter(
      double curve_t,
      double* nurbs_t
      ) const
{
  *nurbs_t = curve_t;
  return true;
}

bool ON_NurbsCurve::ClampEnd( 
        int end // 0 = clamp start, 1 = clamp end, 2 = clamp start and end 
        )
{
  // Curve tree doesn't change when you clamp // DestroyCurveTree();
  return ON_ClampKnotVector( CVSize(), m_order, 
                             m_cv_count, m_cv_stride, m_cv, 
                             m_knot, end );
}


double ON_NurbsCurve::GetCubicBezierApproximation(
  double max_deviation,
  class ON_BezierCurve& bezierCurve
) const
{
  ON_3dPoint bezCV[4];
  const double deviation = GetCubicBezierApproximation(max_deviation, bezCV);
  if (deviation >= 0.0)
  {
    bezierCurve.Create(3, false, 4);
    bezierCurve.SetCV(0, bezCV[0]);
    bezierCurve.SetCV(1, bezCV[1]);
    bezierCurve.SetCV(2, bezCV[2]);
    bezierCurve.SetCV(3, bezCV[3]);
  }
  return deviation;
}

double ON_NurbsCurve::GetCubicBezierApproximation(
  double max_deviation,
  ON_3dPoint bezCV[4]
) const
{
  const double failed_rc = ON_DBL_QNAN;

  if (ThisIsNullptr(false))
    return failed_rc;
  if (m_order < 2)
    return failed_rc;
  if (m_cv_count < m_order)
    return failed_rc;
  if ( nullptr == bezCV)
    return failed_rc;

  if (
    0 == m_is_rat
    && 4 == m_order
    && 4 == m_cv_count
    && m_knot[0] == m_knot[2]
    && m_knot[3] == m_knot[5]
    )
  {
    GetCV(0, bezCV[0]);
    GetCV(1, bezCV[1]);
    GetCV(2, bezCV[2]);
    GetCV(3, bezCV[3]);
    return 0.0;
  }

  const ON_Interval domain = Domain();


  // bez0CV[] are cubic bezier control points set from end locations and interpolating 2 interior points.
  ON_3dPoint bez0CV[4] = { ON_3dPoint::Origin, ON_3dPoint::Origin, ON_3dPoint::Origin, ON_3dPoint::Origin };
  // bez1CV[] are cubic bezier control points set from end locations and derivatives.
  ON_3dPoint bez1CV[4] = { ON_3dPoint::Origin, ON_3dPoint::Origin, ON_3dPoint::Origin, ON_3dPoint::Origin };

  // bez1CV[] are cubic bezier control points set from end locations and derivatives.
  Evaluate(domain[0], 1, 3, &bez1CV[0].x, 0, nullptr);
  Evaluate(domain[1], 1, 3, &bez1CV[2].x, 0, nullptr);
  bez0CV[0] = bez1CV[0];
  bez0CV[3] = bez1CV[2];
  const double c = domain[1] - domain[0];
  const ON_3dVector D[2]{ c * bez1CV[1], c * bez1CV[3] };
  bez1CV[1] = bez0CV[0] + D[0]/3.0;
  bez1CV[2] = bez0CV[3] - D[1]/3.0;
  bez1CV[3] = bez0CV[3];

  // bez0CV[] are cubic bezier control points set from end locations and interpolating 2 interior points.
  ON_3dPoint P[2] = {ON_3dPoint::Origin,ON_3dPoint::Origin};
  int hint = 0;
  Evaluate(domain.ParameterAt(1.0/3.0), 0, 3, &P[0].x, 0, &hint);
  Evaluate(domain.ParameterAt(2.0/3.0), 0, 3, &P[1].x, 0, &hint);
  bez0CV[1] = (bez0CV[3] - 2.5*bez0CV[0])/3.0 + (3.0*P[0] - 1.5*P[1]);
  bez0CV[2] = (bez0CV[0] - 2.5*bez0CV[3])/3.0 + (3.0*P[1] - 1.5*P[0]);

  double zero_tol = 0.0;
  double deviation0 = 0.0;
  double deviation1 = 0.0;
  if (4 != m_order || 4 != m_cv_count || 0 != m_is_rat)
  {
    // g[] = parameters for evaluation test
    double g32[32];
    double* g = (m_cv_count <= 32) ? g32 : (double*)onmalloc(m_cv_count * sizeof(g[0]));
    GetGrevilleAbcissae(g);
    if (3 == m_order)
    {
      const double* k = m_knot;
      if (k[0] < k[2])
      {
        g[0] = k[2];
        g[1] = (2.0*k[2] + k[3]) / 3.0;
      }
      k += (m_cv_count - m_order);
      if (k[3] < k[5])
      {
        g[m_cv_count - 1] = k[3];
        g[m_cv_count - 2] = (2.0*k[3] + k[2]) / 3.0;
      }
    }
  
    // test evaluation
    ON_BezierCurve bez;
    bez.m_dim = 3;
    bez.m_is_rat = 0;
    bez.m_order = 4;
    bez.m_cv_stride = 3;
    bez.m_cv = &bez0CV[0].x;

    ON_3dPoint A, B;
    bez.Evaluate(1.0 / 3.0, 0, 3, &A.x);
    bez.Evaluate(2.0 / 3.0, 0, 3, &B.x);
    zero_tol = 16.0*(P[0].DistanceTo(A) + P[1].DistanceTo(B)) + 1.0e-14;
    double d;
    for (int i = 1; i < m_cv_count; i++)
    {
      for (int pass = 0; pass < 2; pass++)
      {
        const double t = (0==pass) ? 0.5*(g[i - 1] + g[i]) : g[i];
        const double s = domain.NormalizedParameterAt(t);
        if (false == (s > 0.0 && s < 1.0))
          continue;

        Evaluate(t, 0, 3, &A.x, 0, &hint);

        // test bez0CV[]
        bez.m_cv = &bez0CV[0].x;
        bez.Evaluate(s, 0, 3, &B.x);
        d = A.DistanceTo(B);
        if (d > deviation0)
          deviation0 = d;

        // test bez1CV[]
        bez.m_cv = &bez1CV[0].x;
        bez.Evaluate(s, 0, 3, &B.x);
        d = A.DistanceTo(B);
        if (d > deviation1)
          deviation1 = d;

        if (max_deviation > zero_tol && deviation0 > max_deviation && deviation1 > max_deviation)
          return failed_rc;
      }
    }

    bez.m_cv = nullptr;

    if (g != g32)
      onfree(g);
  }


  if (deviation1 <= zero_tol || deviation1 <= deviation0)
  {
    // use cubic bezier CVs calculated from end locations and interpolating end derivatives.
    bezCV[0] = bez1CV[0];
    bezCV[1] = bez1CV[1];
    bezCV[2] = bez1CV[2];
    bezCV[3] = bez1CV[3];
    return (deviation1 > zero_tol) ? deviation1 : 0.0;
  }

  // use cubic bezier CVs calculated from end locations and interpolating 2 interior points.
  bezCV[0] = bez0CV[0];
  bezCV[1] = bez0CV[1];
  bezCV[2] = bez0CV[2];
  bezCV[3] = bez0CV[3];
  return (deviation0 > zero_tol) ? deviation0 : 0.0;
}

double ON_NurbsSurface::GetCubicBezierApproximation(
  double max_deviation,
  class ON_BezierSurface& bezierSurface
) const
{
  ON_3dPoint bezCV[4][4];
  const double deviation = GetCubicBezierApproximation(max_deviation, bezCV);
  if (deviation >= 0.0)
  {
    bezierSurface.Create(3, false, 4, 4);
    for ( int i = 0; i < 4; i++) for ( int j = 0; j < 4; j++)
      bezierSurface.SetCV(i, j, bezCV[i][j]);
  }
  return deviation;
}

double ON_NurbsSurface::GetCubicBezierApproximation(
  double max_deviation,
  ON_3dPoint bezCV[4][4]
) const
{
  const double failed_rc = ON_DBL_QNAN;

  if ( ThisIsNullptr(false) )
    return failed_rc;
  if (this->m_order[0] < 2 || this->m_order[1] < 2)
    return failed_rc;
  if (this->m_cv_count[0] < this->m_order[0] || this->m_cv_count[0] > 64)
    return failed_rc;
  if (this->m_cv_count[1] < this->m_order[1] || this->m_cv_count[1] > 64)
    return failed_rc;

  ON_3dPoint Q[4];
  
  const ON_Interval domain[2] = { this->Domain(0),this->Domain(1) };
  
  const double c[4] = { domain[1][0],domain[0][1],domain[1][1],domain[0][0] };
  const double maximum_deviation = ON_DBL_QNAN;
  double deviation = 0.0;
  for (int side = 0; side < 4; side++)
  {
    ON_Curve* iso = this->IsoCurve((side%2), c[side]);
    if (nullptr == iso)
      return failed_rc;
    const ON_NurbsCurve* nurbs_curve = ON_NurbsCurve::Cast(iso);
    double d
      = (nullptr != nurbs_curve)
      ? nurbs_curve->GetCubicBezierApproximation(
        maximum_deviation,
        (0 == (side % 2)) ? Q : &bezCV[(1 == side) ? 3 : 0][0])
      : ON_DBL_QNAN;
    if (false == (d >= 0.0))
      return failed_rc;
    if (d > deviation)
      deviation = d;
    if (0 == (side % 2))
    {
      int j = (0 == side) ? 0 : 3;
      bezCV[1][j] = Q[1];
      bezCV[2][j] = Q[2];
    }
    delete iso;
  }

  bezCV[1][1] = ON_3dPoint::Origin;
  bezCV[1][2] = ON_3dPoint::Origin;
  bezCV[2][1] = ON_3dPoint::Origin;
  bezCV[2][2] = ON_3dPoint::Origin;

  ON_BezierSurface bezS;
  bezS.m_dim = 3;
  bezS.m_is_rat = 0;
  bezS.m_order[0] = 4;
  bezS.m_order[1] = 4;
  bezS.m_cv_stride[0] = (int)(&bezCV[1][0].x - &bezCV[0][0].x);
  bezS.m_cv_stride[1] = (int)(&bezCV[0][1].x - &bezCV[0][0].x);
  bezS.m_cv = &bezCV[0][0].x;


  // b[0][] = 27*(bernstein cubics at 1/3)
  // b[1][] = 27*(bernstein cubics at 2/3)
  const double b[2][4] = {
    { 8.0, 12.0, 6.0, 1.0 },
    { 1.0, 6.0, 12.0, 8.0 } 
  };

  // uv[4] = {{1/3,1/3}, {2/3,1/3}, {1/3,2/3}, {2/3,2/3} }
  // K[n] = (27*27)*bezCV(uv[n])
  // P[n] = this(domain.ParameterAt(uv[n]));
  // 36* M * Transpose[C11,C21,C12,C22] = [X0,X1,X2,X3]
  // uv[4] = {{1/3,1/3{, {2/3,1/3}, {1/3,2/3}, {2/3,2/3} }
  // X0 = nurbs_srf(1/3,1/3) - K[0]/(27*27)
  // A[4][4] = 4x4 matrix with rows
  // 36*A[0][] = {b1[1]*b1[1], b1[2]*b1[1], b1[1]*b1[2], b1[2]*b1[2] }
  // 36*A[1][] = {b2[1]*b1[1], b2[2]*b1[1], b2[1]*b1[2], b2[2]*b1[2] }
  // 36*A[2][] = {b1[1]*b2[1], b1[2]*b2[1], b1[1]*b2[2], b1[2]*b2[2] }
  // 36*A[3][] = {b2[1]*b2[1], b2[2]*b2[1], b2[1]*b2[2], b2[2]*b2[2] }
  // K[n] + 36*(A[n][0]*C11 + A[n][1]*C21 + A[n][2]*C12 + A[n][3]*C22) = (27*27)P[n]
  // A*Transpose(C11,C21,C12,C22) = Transpose(X[0],X[1],X[2],X[3])
  // X[n] = ((27*27)P[n] - K[n])/36 = 81/4*P[n] - K[n]/36.0
  // Inverse(A) = M/9.
  // Transpose(C11,C21,C12,C22) = M*Transpose(X[0],X[1],X[2],X[3])/9
  // Q[n] = X[n]/9 = 2.25*P[n] - K[n]/324.0
  // bezCV[cvdex[n].i][cvdex[n].i] = M*Transpose(X[0],X[1],X[2],X[3])/9
  const double bezuv[4][2] =
  {
    {(1.0 / 3.0), (1.0 / 3.0)},
    {(2.0 / 3.0), (1.0 / 3.0)},
    {(1.0 / 3.0), (2.0 / 3.0)},
    {(2.0 / 3.0), (2.0 / 3.0)}
  };
  ON_3dPoint srfP[4] = { ON_3dPoint::Origin,ON_3dPoint::Origin,ON_3dPoint::Origin,ON_3dPoint::Origin };
  int hint[2] = {};
  for (int n = 0; n < 4; n++)
  {
    this->Evaluate(domain[0].ParameterAt(bezuv[n][0]),domain[1].ParameterAt(bezuv[n][1]), 0, 3, &srfP[n].x, 0, hint);
    const double* bi = b[n%2];
    const double* bj = b[n/2];
    ON_3dPoint K(0.0, 0.0, 0.0);
    ON_3dPoint valQ(0, 0, 0);
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)
    {
      if ((1 == i || 2 == i) && (1 == j || 2 == j))
        continue;
      K += (bi[i] * bj[j])*bezCV[i][j];
    }
    Q[n] = (2.25*srfP[n]) - (K/324.0);
  }

  const ON_2dex cvdex[4]{ON_2dex(1,1),ON_2dex(2,1),ON_2dex(1,2),ON_2dex(2,2)};

  ////const double A[4][4] =
  ////{
  ////  {4.0, 2.0, 2.0, 1.0},
  ////  {2.0, 4.0, 1.0, 2.0},
  ////  {2.0, 1.0, 4.0, 2.0},
  ////  {1.0, 2.0, 2.0, 4.0}
  ////};

  const double M[4][4] =
  {
    {4.0,-2.0,-2.0,1.0},
    {-2.0,4.0,1.0,-2.0},
    {-2.0,1.0,4.0,-2.0},
    {1.0,-2.0,-2.0,4.0}
  };

  for (int n = 0; n < 4; n++)
    bezCV[cvdex[n].i][cvdex[n].j] = M[n][0] * Q[0] + M[n][1] * Q[1] + M[n][2] * Q[2] + M[n][3] * Q[3];

  double zero_tol = 0.0;
  for (int n = 0; n < 4; n++)
  {
    ON_3dPoint bezP(0.0, 0.0, 0.0);
    bezS.Evaluate(bezuv[n][0], bezuv[n][1], 0, 3, &bezP.x);
    double d = srfP[n].DistanceTo(bezP);
    zero_tol += d;
  }
  zero_tol = 16.0*zero_tol;

  double g_buffer[64];
  double* g[2];
  g[0] 
    = (m_cv_count[0] + m_cv_count[1] <= 32)
    ? g_buffer 
    : (double*)onmalloc((m_cv_count[0] + m_cv_count[1]) * sizeof(g[0][0]));
  g[1] = g[0] + m_cv_count[0];
  for (int dir = 0; dir < 2; dir++)
  {
    this->GetGrevilleAbcissae(dir, g[dir]);
    if (4 == this->m_order[dir])
    {
      const double* k = this->m_knot[dir];
      if (k[0] < k[2])
      {
        g[dir][0] = k[2];
        g[dir][1] = (2.0*k[2] + k[3]) / 3.0;
      }
      const int cv_count = this->m_cv_count[dir];
      k += (cv_count - this->m_order[dir]);
      if (k[3] < k[5])
      {
        g[dir][cv_count-1] = k[3];
        g[dir][cv_count-2] = (2.0*k[3] + k[2]) / 3.0;
      }
    }
  }

  ON_3dPoint bezP(ON_3dPoint::Origin), nurbsP(ON_3dPoint::Origin);
  hint[0] = 0;
  hint[1] = 0;
  for (int i = 1; i < this->m_cv_count[0]; i++)
  {
    for (int passi = 0; passi < 2; passi++)
    {
      const double t0 = (0 == passi) ? 0.5*(g[0][i - 1] + g[0][i]) : g[0][i];
      const double s0 = domain[0].NormalizedParameterAt(t0);
      if (false == (s0 > 0.0 && s0 < 1.0))
        continue;
      for (int j = 1; j < this->m_cv_count[1]; j++)
      {
        for (int passj = 0; passj < 2; passj++)
        {
          const double t1 = (0 == passj) ? 0.5*(g[1][j - 1] + g[1][j]) : g[1][j];
          const double s1 = domain[1].NormalizedParameterAt(t1);
          if (false == (s1 > 0.0 && s1 < 1.0))
            continue;
          bezS.Evaluate(s0,s1, 0, 3, &bezP.x);
          this->Evaluate(t0,t1, 0, 3, &nurbsP.x, 0, hint);
          double d = nurbsP.DistanceTo(bezP);
          if (d > zero_tol && d > deviation)
          {
            deviation = d;
            if (max_deviation >= 0.0 && deviation > max_deviation)
              return failed_rc;
          }
        }
      }
    }
  }

  return deviation;
} 


/*
static 
bool ON_DuplicateKnots( int order, int cv_count, bool bRevKnot1,
                        double* knot0, 
                        double* knot1
                        )
{
  return false;
}

static 
bool ON_DuplicateContolPoints( int dim, bool is_rat, int cv_count, 
                               bool bRevCV1,
                               int stride0, double* cv0, 
                               int stride1, double* cv1
                              )
{
  return false;
}
*/

static bool ON_IsDuplicateKnotVector( int order, int cv_count, 
               const double* knot, const double* other_knot,
               bool bIgnoreParameterization )
{
  bool rc = (    0 != knot 
              && 0 != other_knot 
              && order >= 2 
              && cv_count >= order);

  if (rc)
  {
    const int knot_count = ON_KnotCount( order, cv_count );
    int i;
    if ( bIgnoreParameterization )
    {
      const ON_Interval dom(knot[order-2],knot[cv_count-1]);
      const ON_Interval other_dom(other_knot[order-2],other_knot[cv_count-1]);
      double k, other_k;
      for ( i = 0; i < knot_count && rc; i++ )
      {
        k = dom.NormalizedParameterAt(knot[i]);
        other_k = dom.NormalizedParameterAt(other_knot[i]);
        rc = (fabs(k-other_k) <= ON_ZERO_TOLERANCE);
      }
    }
    else
    {
      for ( i = 0; i < knot_count && rc; i++ )
      {
        rc = (knot[i] == other_knot[i]);
      }
    }
  }
  return rc;
}

static bool ON_IsDuplicatePointList( int dim, bool is_rat,
                                     int count, 
                                     int stride, 
                                     const double* cv,
                                     int other_stride,
                                     const double* other_cv,
                                     double tolerance
                                     )
{
  bool rc = (dim > 0 && count > 0
             && std::abs(stride) >= (dim+(is_rat?1:0)) && std::abs(other_stride) >= (dim+(is_rat?1:0))
             && 0 != cv && 0 != other_cv);
  if (rc)
  {
    if ( tolerance < 0.0 )
      tolerance = 0.0;
    int i, j;
    double w = 1.0;
    double other_w = 1.0;
    double cv_tol = tolerance;
    for ( i = 0; i < count && rc; i++ )
    {
      if ( is_rat )
      {
        w = cv[dim];
        other_w = other_cv[dim];
        cv_tol = fabs(w*tolerance);
        rc = ( w == other_w );
      }

      for ( j = 0; j < dim && rc; j++ )
      {
        rc = (fabs(cv[j] - other_cv[j]) <= cv_tol);
      }
      cv += stride;
      other_cv += other_stride;
    }
  }
  return rc;
}
                                   

bool ON_NurbsCurve::IsDuplicate( 
        const ON_NurbsCurve& other, 
        bool bIgnoreParameterization,
        double tolerance 
        ) const
{
  bool rc = (this == &other);
  if ( !rc
       && m_dim      == other.m_dim
       && m_is_rat   == other.m_is_rat
       && m_order    == other.m_order
       && m_cv_count == other.m_cv_count
       )
  {
    // compare knots
    rc = ON_IsDuplicateKnotVector( m_order, m_cv_count, m_knot, other.m_knot, bIgnoreParameterization );

    // compare control points
    if (rc)
      rc = ON_IsDuplicatePointList( m_dim, m_is_rat?1:0, m_cv_count,
                                    m_cv_stride, m_cv,
                                    other.m_cv_stride, other.m_cv,
                                    tolerance );
  }
  return rc;
}

bool ON_NurbsSurface::IsDuplicate( 
        const ON_NurbsSurface& other, 
        bool bIgnoreParameterization,
        double tolerance 
        ) const
{
  bool rc = (this == &other);
  if ( !rc
       && m_dim      == other.m_dim
       && m_is_rat   == other.m_is_rat
       && m_order[0] == other.m_order[0]
       && m_order[1] == other.m_order[1]
       && m_cv_count[0] == other.m_cv_count[0]
       && m_cv_count[1] == other.m_cv_count[1]
       )
  {
    // compare knots
    rc = ON_IsDuplicateKnotVector( m_order[0], m_cv_count[0], m_knot[0], other.m_knot[0], bIgnoreParameterization );
    if (rc)
      rc = ON_IsDuplicateKnotVector( m_order[1], m_cv_count[1], m_knot[1], other.m_knot[1], bIgnoreParameterization );

    // compare control points
    int i;
    for ( i = 0; i < m_cv_count[0] && rc; i++ )
    {
      rc = ON_IsDuplicatePointList( m_dim, m_is_rat?1:0, m_cv_count[1],
                                    m_cv_stride[1], CV(i,0),
                                    other.m_cv_stride[1], other.CV(i,0),
                                    tolerance );
    }
  }
  return rc;
}


bool ON_Brep::IsDuplicate( 
        const ON_Brep& other, 
        double tolerance 
        ) const
{
  // OBSOLETE FUNCTION - REMOVE
  return false;
}

bool ON_NurbsCurve::Reparameterize(double c)
{
  if ( !ON_IsValid(c) || 0.0 == c )
    return false;

  if ( 1.0 == c )
    return true;

  if ( !MakeRational() )
    return false;

  return ON_ReparameterizeRationalNurbsCurve(
           c,
           m_dim,m_order,m_cv_count,
           m_cv_stride,m_cv,m_knot
           );
}

bool ON_ReparameterizeRationalNurbsCurve(
          double c, 
          int dim, 
          int order, 
          int cv_count,
          int cvstride,
          double* cv,
          double* knot
          )
{
  // Reference
  //  E. T. Y. Lee and M. L. Lucian 
  //  Mobius reparameterization of rational B-splines
  //  CAGD Vol8 pp 213-215 1991
  const double c1 = c-1.0;
  double k0, k1, k, d, w0, w1;
  int i,j;

  if ( !ON_IsValid(c) || !ON_IsValid(c1) || 0.0 == c )
    return false;

  if ( 1.0 == c )
    return true;

  // change domain to [0,1] and then adjust knots
  k0 = knot[order-2];
  k1 = knot[cv_count-1];
  d = k1 - k0;
  if ( !ON_IsValid(d) || d <= 0.0 )
    return false;
  d = 1.0/d;
  j = cv_count+order-2;
  for ( i = 0; i < j; i++ )
  {
    k = knot[i];
    k = (k - k0)*d;
    knot[i] = c*k/(c1*k+1.0);
  }

  // adjust cvs
  order -= 2;
  cvstride -= (dim+1);
  for ( i = 0; i < cv_count; i++ )
  {
    d = c - c1*(*knot++);
    j = order;
    while(j--)
    {
      d *= c - c1*knot[j];
    }
    w0 = cv[dim];
    w1 = w0*d;
    j = dim;
    while(j--)
      *cv++ *= d;
    *cv++ = w1;
    cv += cvstride;
  }
  order += 2;
  cvstride += (dim+1);
  cv -= cv_count*cvstride;
  knot -= cv_count;

  // change domain back to [k0,k1]
  j = cv_count+order-2;
  for ( i = 0; i < j; i++ )
  {
    k = knot[i];
    knot[i] = (1.0-k)*k0 + k*k1;
  }

  return true;
}

bool ON_NurbsCurve::ChangeEndWeights(double w0, double w1)
{
  if ( m_cv_count < m_order || m_order < 2 || 0 == m_cv )
    return false;

  if ( !ON_IsValid(w0) || !ON_IsValid(w1) || 0.0 == w0 || 0.0 == w1 )
    return false;

  if ( (w0 < 0.0 && w1 > 0.0) || (w0 > 0.0 && w1 < 0.0) )
    return false;

  if (!ClampEnd(2))
    return false;

  if ( w0 == Weight(0) && w1 == Weight(m_cv_count-1) )
    return true;

  if ( !MakeRational() )
    return false;

  return ON_ChangeRationalNurbsCurveEndWeights(
          m_dim,m_order,
          m_cv_count,m_cv_stride,m_cv,
          m_knot,
          w0,w1);
}

bool ON_ChangeRationalNurbsCurveEndWeights(
          int dim, 
          int order, 
          int cv_count,
          int cvstride, 
          double* cv, 
          double* knot,
          double w0, 
          double w1
          )
{
  double r, s, v0, v1;
  int i, j;

  if ( !ON_IsValid(w0) || !ON_IsValid(w1) || 0.0 == w0 || 0.0 == w1 )
    return false;
  if ( (w0 < 0.0 && w1 > 0.0) || (w0 > 0.0 && w1 < 0.0) )
    return false;

  if ( !ON_ClampKnotVector( dim+1, order, cv_count, cvstride, cv, knot, 2 ) )
    return false;

  v0 = cv[dim];
  v1 = cv[cvstride*(cv_count-1)+dim];
  if (!ON_IsValid(v0) || !ON_IsValid(v1) || v0 == 0.0 || v1 == 0.0)
    return false;
  if (v0 < 0.0 && v1 > 0.0)
    return false;
  if ( v0 > 0.0 && v1 < 0.0)
    return false;

  r = w0/v0;
  s = w1/v1;
  if ( fabs(r-s) <= fabs(s)*ON_SQRT_EPSILON )
  {
    // simply scale
    if ( r != s )
      s = 0.5*(r+s);
    r = s;
  }

  if ( 1.0 != s && v1 != w1 )
  {
    // scale to get last weight set to w1
    dim++;
    cvstride -= dim;
    i = cv_count;
    while(i--)
    {
      j = dim;
      while(j--)
        *cv++ *= s;
      cv += cvstride;
    }
    cvstride += dim;
    dim--;
    cv -= cvstride*cv_count;
  }

  if ( r != s )
  {
    v0 = cv[dim];
    v1 = cv[cvstride*(cv_count-1)+dim];
    if ( ON_IsValid(v0) && ON_IsValid(v1) && 0.0 != v0 )
    {
      // need to scale and reparameterize
      r = pow(w0/v0,1.0/((double)(order-1)));
      if ( !ON_IsValid(r) )
        return false;
      if ( !ON_ReparameterizeRationalNurbsCurve(r,dim,order,cv_count,cvstride,cv,knot) )
        return false;
    }
  }

  // make sure weights agree to the last bit! 
  cv[dim] = w0;
  cv[cvstride*(cv_count-1)+dim] = w1;

  return true;
}

bool ON_NurbsCurve::SpanIsSingular( 
  int span_index 
  ) const
{
  const int cv_size = CVSize();
  if (    m_order < 2 
       || m_cv_count < m_order
       || m_dim <= 0
       || cv_size > m_cv_stride 
       || 0 == m_knot
       || 0 == m_cv
       )
  {
    ON_ERROR("Invalid NURBS curve.");
    return false;
  }

  if ( span_index < 0 || span_index > m_cv_count-m_order )
  {
    ON_ERROR("span_index parameter is out of range.");
    return false;
  }

  const double* cv = CV(span_index);
  const double* knot = m_knot + span_index;

  if ( !(knot[m_order-2] < knot[m_order-1]) )
  {
    // vacuous question because there is no "span" evaluate.
    // I chose return false here so people won't try to
    // remove this empty span.
    // no call to ON_ERROR here
    return false; 
  }

  double* p = 0;
  int cv_stride = m_cv_stride;
  if ( knot[0] != knot[m_order-2] || knot[m_order-1] != knot[2*m_order-3] )
  {
    const size_t sizeof_cv = cv_size*sizeof(p[0]);
    p = (double*)onmalloc(sizeof_cv*m_order);
    for ( int i = 0; i < m_order; i++ )
      memcpy( p+(i*cv_size), cv+(i*cv_stride), sizeof_cv );
    ON_ConvertNurbSpanToBezier( cv_size, m_order, cv_size, p,
															  knot, knot[m_order-2], knot[m_order-1] 
                              );
    cv_stride = cv_size;
    cv = p;
  }
  const bool rc = ON_PointsAreCoincident(m_dim,m_is_rat,m_order,cv_stride,cv);
  if ( 0 != p )
    onfree(p);

  return rc;
}

bool ON_NurbsCurve::RemoveSpan(
  int span_index 
  )
{
  const int cv_size = CVSize();
  if (    m_order < 2 
       || m_cv_count < m_order
       || m_dim <= 0
       || cv_size > m_cv_stride 
       || 0 == m_knot
       || 0 == m_cv
       )
  {
    ON_ERROR("Invalid NURBS curve.");
    return false;
  }

  if ( span_index < 0 || span_index > m_cv_count-m_order )
  {
    ON_ERROR("span_index parameter is out of range.");
    return false;
  }

  if ( m_cv_count == m_order )
  {
    ON_ERROR("Cannot remove the only span from a Bezier NURBS curve.");
    return false;
  }

  const size_t sizeof_cv = cv_size*sizeof(m_cv[0]);
  int i, j;

  const double knot0 = m_knot[span_index+m_order-2];
  const double knot1 = m_knot[span_index+m_order-1];
  const double knot_delta = (knot0 < knot1) ? (knot1 - knot0) : 0.0;

  const bool bIsPeriodic0 = IsPeriodic()?true:false;

  if ( span_index <= 0 )
  {
    // remove initial span
    // set span_index = index of the span to keep.
    for ( span_index = 1; span_index < m_cv_count-m_order; span_index++ )
    {
      if ( m_knot[span_index+m_order-2] < m_knot[span_index+m_order-1] )
        break;
    }
    for ( i = 0; i+span_index < m_cv_count; i++ )
      memcpy(CV(i),CV(i+span_index),sizeof_cv);
    for ( i = 0; i+span_index < m_cv_count+m_order-2; i++ )
    {
      m_knot[i] = (knot1 == m_knot[i+span_index])
                ? knot0
                : (m_knot[i+span_index] - knot_delta);
    }
    m_cv_count -= span_index;
  }
  else if ( span_index >= m_cv_count-m_order )
  {
    // remove final span
    // set span_index = index of the span to keep.
    for ( span_index = m_cv_count-m_order-1; span_index > 0; span_index-- )
    {
      if ( m_knot[span_index+m_order-2] < m_knot[span_index+m_order-1] )
        break;
    }
    m_cv_count = span_index+m_order;
  }
  else
  {
    // remove interior span
    int k0 = span_index+m_order-2;
    int k1 = span_index+m_order-1;
    int i0 = k0;
    int i1 = k1;
    for ( i0 = k0; i0 > 0; i0-- )
    {
      if ( m_knot[i0-1] < m_knot[k0] )
        break;
    }
    for ( i1 = k1; i1 < m_cv_count+m_order-3; i1++ )
    {
      if ( m_knot[i1+1] > m_knot[k1] )
        break;
    }
    int m = (i1-i0+1);
    if ( !(knot_delta > 0.0) )
    {
      if ( !(m_knot[i0] == m_knot[i1]) || m < m_order )
      {
        ON_ERROR("span_index parameter identifies an empty span.");
        return false;
      }
    }

    int span_index0 = i0 - (m_order-1);
    double* cv0 = 0;
    if ( span_index0 >= 0 && k0 - i0 + 1 < m_order-1 )
    {
      cv0 = (double*)onmalloc( (m_order*cv_size + 2*m_order-2)*sizeof(cv0[0]) );
      double* knot0_local = cv0 + (m_order*cv_size);
      memcpy( knot0_local, m_knot+span_index0, (2*m_order-2)*sizeof(knot0_local[0]) );
      for ( i = 0; i < m_order; i++ )
        memcpy( cv0 + (i*cv_size), CV(span_index0+i), sizeof_cv );
      ON_ClampKnotVector( cv_size, m_order, m_order, cv_size, cv0, knot0_local, 1 );
    }

    if ( m < m_order-1 )
    {
      i = m_order-1 - m;
      ReserveCVCapacity( m_cv_stride*(m_cv_count+i) );
      ReserveKnotCapacity( m_cv_count+m_order-2+i );
      for ( j = m_cv_count+m_order-3; j >= i1-m_order+2; j-- )
        m_knot[j+i] = m_knot[j];
      for ( j = m_cv_count-1; j >= i1-m_order+2; j-- )
        memcpy(CV(j+i),CV(j),sizeof_cv);
      i1 += i;
      k1 += i;
      m_cv_count += i;
    }

    if ( i1-k1 < m_order-2 )
      ON_ClampKnotVector( cv_size, m_order, m_order, m_cv_stride, 
                          m_cv + ((i1-m_order+2)*m_cv_stride), 
                          m_knot + (i1-m_order+2), 
                          0 );

    k0 = i0;
    k1 = i1-m_order+2;

    if ( 0 != cv0 )
    {
      for ( i = 0; i < m_order-1; i++ )
        memcpy(CV(i+span_index0),cv0 + (i*cv_size),sizeof_cv);
      onfree(cv0);
      cv0 = 0;
    }

    if ( k0 < k1 )
    {
      for ( i = 0; i + k1 < m_cv_count; i++ )
        memcpy(CV(i+k0),CV(i+k1),sizeof_cv);
      for ( i = 0; i + k1 < m_cv_count+m_order-2; i++ )
      {
        m_knot[i+k0] = (knot1 == m_knot[i+k1]) 
                     ? knot0
                     : (m_knot[i+k1] - knot_delta);
      }
      m_cv_count -= (k1-k0);
    }
    else if ( k0 == k1 && knot_delta > 0.0 )
    {
      for ( i = k0; i < m_cv_count+m_order-2; i++ )
      {
        m_knot[i] = (knot1 == m_knot[i])
                  ? knot0
                  : (m_knot[i] - knot_delta);
      }
    }
  }

  if ( false == bIsPeriodic0 || false == IsPeriodic() )
    ClampEnd(2);

  return true;
}

int ON_NurbsCurve::RemoveSingularSpans()
{
  const int cv_size = CVSize();
  if (    m_order < 2 
       || m_cv_count < m_order
       || m_dim <= 0
       || cv_size > m_cv_stride 
       || 0 == m_knot
       || 0 == m_cv
       )
  {
    ON_ERROR("Invalid NURBS curve.");
    return 0;
  }

  int singular_span_count = 0;

  for ( int span_index = 0; m_cv_count > m_order && span_index <= m_cv_count-m_order; span_index++ )
  {
    if (    m_knot[span_index+m_order-2] < m_knot[span_index+m_order-1] 
         && SpanIsSingular(span_index) 
       )
    {
      const int cv_count0 = m_cv_count;
      if ( RemoveSpan(span_index) )
        singular_span_count++;
      if ( 0 == span_index || m_cv_count < cv_count0 )
        span_index--;
    }
  }

  return singular_span_count;
}


static bool Internal_UnclampedKnots(
  int order,
  int cv_count,
  const double* cv,
  const double* knot
  )
{
  return
    order >= 3
    && cv_count >= order
    && nullptr != cv
    && nullptr != knot
    && knot[0] > ON_UNSET_VALUE
    && knot[cv_count + order - 3] < ON_UNSET_POSITIVE_VALUE
    && knot[order - 2] < knot[order - 1] - ON_ZERO_TOLERANCE
    && knot[cv_count - 2] < knot[cv_count - 1] - ON_ZERO_TOLERANCE
    && ((knot[0] < knot[order - 2] - ON_ZERO_TOLERANCE) || (knot[cv_count - 1] < knot[cv_count + order - 3] - ON_ZERO_TOLERANCE))
    ;
}

bool ON_NurbsCurve::UnclampedTagForExperts() const
{
  if (
    0 != (m_knot_capacity_and_tags & ON_NurbsCurve::masks::unclamped_knots_tag)
    && Internal_UnclampedKnots(m_order,m_cv_count,m_cv,m_knot)
    && false == IsPeriodic()
    )
  {
    return true;
  }
  return false;
}

/*
Description:
  Set the curve's UnclampedTag() property.
Parameters:
  bUnclampedTag - [in]
    If bUnclampedTag is true, the curve has unclamped knots,
    and the curve is not periodic,
    then the UnclampedTag() property is set to true.
    Otherwise the UnclampedTag() property is set to false.
*/
void ON_NurbsCurve::SetUnclampedTagForExperts(
  bool bUnclampedTag
)
{
  if (
    bUnclampedTag
    && Internal_UnclampedKnots(m_order, m_cv_count, m_cv, m_knot)
    && false == this->IsPeriodic()
    )
    m_knot_capacity_and_tags |= ON_NurbsCurve::masks::unclamped_knots_tag;
  else
    m_knot_capacity_and_tags &= ~ON_NurbsCurve::masks::unclamped_knots_tag;
}

bool ON_NurbsCurve::SubDFriendlyTag() const
{
  if (0 != (m_knot_capacity_and_tags & ON_NurbsCurve::masks::subdfriendly_tag))
  {
    if (IsSubDFriendly(true))
      return true;
    // Something modified NURBS properties after the tag was set.
    const_cast<ON_NurbsCurve*>(this)->SetSubDFriendlyTag(false);
  }
  return false;
}

void ON_NurbsCurve::SetSubDFriendlyTag(
  bool bSubDFriendlyTag
)
{
  if (bSubDFriendlyTag && IsSubDFriendly(true))
    m_knot_capacity_and_tags |= ON_NurbsCurve::masks::subdfriendly_tag;
  else
    m_knot_capacity_and_tags &= ~ON_NurbsCurve::masks::subdfriendly_tag;
}

static bool Internal_IsSubDFriendlyEnd(
  int endex,
  const double* cubic_cpan_knots,
  const ON_3dPoint& cv0,
  const ON_3dPoint& cv1,
  const ON_3dPoint& cv2
)
{
  ON_3dPoint Q;
  if (0 == endex)
  {
    Q = (cubic_cpan_knots[0] == cubic_cpan_knots[2] && cubic_cpan_knots[3] < cubic_cpan_knots[5])
      ? ((2.0*cv0 + cv2) / 3.0)
      : (0.5*(cv0 + cv2))
      ;
  }
  else
  {
    Q = (cubic_cpan_knots[0] < cubic_cpan_knots[2] && cubic_cpan_knots[3] == cubic_cpan_knots[5])
      ? ((cv0 + 2.0*cv2) / 3.0)
      : (0.5*(cv0 + cv2))
      ;
  }
  const double d = cv0.DistanceTo(cv2);
  const double tol = 1.0e-6*d;
  const double e = cv1.DistanceTo(Q);
  return (e <= tol);
}

bool ON_NurbsCurve::IsSubDFriendly(
  bool bPermitCreases
) const
{
  for (;;)
  {
    if (m_dim <= 0)
      break;
    if (false != m_is_rat)
      break;
    if (4 != m_order)
      break;
    if (m_cv_count < 4)
      break;
    if (nullptr == m_knot)
      break;
    if (m_cv_stride < m_dim)
      break;
    if (nullptr == m_cv)
      break;

    // knots must be piecewise uniform
    const ON_SubD::SubDFriendlyKnotType knot_type = ON_SubD::NurbsKnotType(m_order, m_cv_count, m_knot);
    if (ON_SubD::SubDFriendlyKnotType::Unset == knot_type || ON_SubD::SubDFriendlyKnotType::Unfriendly == knot_type)
      return false;
    if (ON_SubD::SubDFriendlyKnotType::ClampedPiecewiseUniform == knot_type && false == bPermitCreases)
      return false;

    ON_3dPoint CV[2] = { ON_3dPoint::NanPoint,ON_3dPoint::NanPoint };
    if (false == GetCV(0, CV[0]))
      break;
    if (false == GetCV(1, CV[1]))
      break;
    bool bAllEqual = CV[0] == CV[1];
    if (bAllEqual)
    {
      // All CVs must be equal - curve is a "point" used in lofting to a point.
      for (int i = 2; bAllEqual && i < m_cv_count; ++i)
      {
        bAllEqual = GetCV(i, CV[1]) && CV[0] == CV[1];
      }
      if (false == bAllEqual)
        break;
    }
    
    // curve must be periodic or natural
    bool bNaturalEnds = (m_cv_count >= 6 && IsPeriodic());
    if ( false == bNaturalEnds)
    {
      // test ends for natural end conditions
      ON_3dPoint P[3];
      bNaturalEnds = true;
      for (int endex = 0; endex < 2 && bNaturalEnds; ++endex)
      {
        const int cv_dex = (0 == endex) ? 0 : ( CVCount() - 3);
        for (int j = 0; j < 3 && bNaturalEnds; ++j)
          bNaturalEnds = GetCV(cv_dex+j, P[j]);
        if (false == bNaturalEnds)
          break;
        const double* span_knots = m_knot + ((0 == endex) ? 0 : (m_cv_count - m_order));
        bNaturalEnds = Internal_IsSubDFriendlyEnd(endex, span_knots, P[0], P[1], P[2]);
      }
    }

    if ( bNaturalEnds && ON_SubD::SubDFriendlyKnotType::ClampedPiecewiseUniform == knot_type )
    {
      // Interior triple knots must be natural on either side of the triple knot.
      // Interior triple knots are used to place kinks inside the curve.
      ON_3dPoint P[5];
      const unsigned int knot_count = (unsigned int)KnotCount();    
      const double* knot = m_knot;
      for (unsigned int knot_dex = 3; knot_dex < knot_count - 4U && bNaturalEnds; ++knot_dex)
      {
        if (knot[knot_dex] == knot[knot_dex + 1])
        {
          // This tests that the 2nd derivative is zero when evaluated from both below and above knot[knot_dex].
          bNaturalEnds =
            knot[knot_dex - 1] < knot[knot_dex]
            // tested above to enter this scope // && knot[knot_dex] == knot[knot_dex+1]
            && knot[knot_dex + 1] == knot[knot_dex + 2]
            && knot[knot_dex + 2] < knot[knot_dex + 3]
            && GetCV(knot_dex - 2, P[0])
            && GetCV(knot_dex - 1, P[1])
            && GetCV(knot_dex, P[2])
            && GetCV(knot_dex + 1, P[3])
            && GetCV(knot_dex + 2, P[4])
            && Internal_IsSubDFriendlyEnd(1,knot+knot_dex-3, P[0], P[1], P[2])
            && Internal_IsSubDFriendlyEnd(0,knot+knot_dex, P[2], P[3], P[4]);
          ++knot_dex;
        }
      }
    }

    if (false == bNaturalEnds)
      break;

    return true;
  }

  return false;
}

ON_SubD::SubDFriendlyKnotType ON_SubD::NurbsKnotType(
  int order,
  int cv_count,
  const double* knots
)
{
  return ON_SubD::NurbsKnotType(order, cv_count, knots, nullptr);
}

ON_SubD::SubDFriendlyKnotType ON_SubD::NurbsKnotType(
    int order,
    int cv_count,
    const double* knots,
    ON_SimpleArray<double>* triple_knots
  )
{
  if (nullptr != triple_knots)
    triple_knots->SetCount(0);
  for (;;)
  {
    if (4 != order || cv_count < order || nullptr == knots)
      break;

    const double delta = knots[3] - knots[2];
    if (false == (delta > 0.0))
      break;

    const double deltatol = ON_SQRT_EPSILON * delta;

    const bool bClamped0 = knots[0] == knots[1] && knots[1] == knots[2];
    const bool bClamped1 = knots[cv_count - 1] == knots[cv_count] && knots[cv_count] == knots[cv_count + 1];
    if (bClamped0 && nullptr != triple_knots)
      triple_knots->Append(knots[2]);

    const bool bClamped = bClamped0 && bClamped1;
    const bool bUnclamped =
      (false == bClamped)
      && fabs(knots[1] - knots[0] - delta) <= deltatol
      && fabs(knots[2] - knots[1] - delta) <= deltatol
      && fabs(knots[cv_count] - knots[cv_count - 1] - delta) <= deltatol
      && fabs(knots[cv_count + 1] - knots[cv_count] - delta) <= deltatol
      ;
    if ( bClamped == bUnclamped)
      break;

    bool bPiecewiseUniform = false;
    for (int knot_dex = 3; knot_dex < cv_count - 1; ++knot_dex)
    {
      const double d = knots[knot_dex + 1] - knots[knot_dex];
      if (0.0 == d)
      {
        if (bClamped && knots[knot_dex + 2] == knots[knot_dex])
        {
          bPiecewiseUniform = true;
          ++knot_dex;
          if (bClamped1 && nullptr != triple_knots)
            triple_knots->Append(knots[knot_dex]);
          continue;
        }
      }
      else
      {
        if (fabs(d - delta) <= deltatol)
          continue;
      }
      return ON_SubD::SubDFriendlyKnotType::Unfriendly;
    }

    if (bClamped1 && nullptr != triple_knots)
      triple_knots->Append(knots[cv_count - 1]);

    return
      bClamped
      ? (bPiecewiseUniform ? ON_SubD::SubDFriendlyKnotType::ClampedPiecewiseUniform : ON_SubD::SubDFriendlyKnotType::ClampedUniform)
      : ON_SubD::SubDFriendlyKnotType::UnclampedUniform;
  }

  return ON_SubD::SubDFriendlyKnotType::Unfriendly;
}
