/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#include "opennurbs.h"

ON_X_EVENT::ON_X_EVENT()
{
  memset(this,0,sizeof(*this));
}

int ON_X_EVENT::Compare( const ON_X_EVENT* a, const ON_X_EVENT* b) 
{
  if ( !a )
  {
    return b ? 1 : 0;
  }

  if  (!b)
    return -1;

	if( a->m_a[0] < b->m_a[0])
		return -1;
	
  if( a->m_a[0] > b->m_a[0])
		return 1;

	if( a->m_a[1] < b->m_a[1])
		return -1;
	
  if( a->m_a[1] > b->m_a[1])
		return 1;

	return 0;
}

static void DumpDistanceABHelper( ON_TextLog& text_log, ON_3dPoint A, ON_3dPoint B )
{
  const double tinyd = 1.0e-14;
  double d = A.DistanceTo(B);
  text_log.Print("distance A to B");
  if ( !ON_IsValid(d) || d >= 1.0e-14 || d <= 0.0 )
  {
    text_log.Print(" = ");
  }
  else
  {
    // This prevents diff from compaining about tiny changes.
    text_log.Print(" < ");
    d = tinyd;
  }
  text_log.Print(d);
  text_log.Print("\n");
}

static void DumpDistanceABHelper( ON_TextLog& text_log, ON_3dPoint A0, ON_3dPoint B0, ON_3dPoint A1, ON_3dPoint B1 )
{
  if ( A0.DistanceTo(B0) <= A1.DistanceTo(B0) )
    DumpDistanceABHelper( text_log, A0, B0 );
  else
    DumpDistanceABHelper( text_log, A1, B1 );
}

void ON_X_EVENT::Dump(ON_TextLog& text_log) const
{
  int j;

  text_log.Print("m_type: ");
  switch( m_type )
  {
  case ON_X_EVENT::no_x_event:
    text_log.Print("no_x_event");
    break;
  case ON_X_EVENT::ccx_point:
    text_log.Print("ccx_point");
    break;
  case ON_X_EVENT::ccx_overlap:
    text_log.Print("ccx_overlap");
    break;
  case ON_X_EVENT::csx_point:
    text_log.Print("csx_point");
    break;
  case ON_X_EVENT::csx_overlap:
    text_log.Print("csx_overlap");
    break;
  default:
    text_log.Print("illegal value");
    break;
  }
  text_log.Print("\n");
  text_log.PushIndent();

  switch( m_type )
  {
  case ON_X_EVENT::ccx_point:
  case ON_X_EVENT::csx_point:
    // don't use %g so the text_log double format can control display precision
    text_log.Print("curveA(");
    text_log.Print(m_a[0]);
    text_log.Print(") = \n");
    text_log.PushIndent();
    text_log.Print(m_A[0]);
    text_log.Print("\n");
    text_log.PopIndent();
    break;

  case ON_X_EVENT::ccx_overlap:
  case ON_X_EVENT::csx_overlap:
    // don't use %g so the text_log double format can control display precision
    text_log.Print("curveA(");
    text_log.Print(m_a[0]);
    text_log.Print(" to ");
    text_log.Print(m_a[1]);
    text_log.Print(") = \n");
    text_log.PushIndent();
    text_log.Print(m_A[0]);
    text_log.Print(" to ");
    text_log.Print(m_A[1]);
    text_log.Print("\n");
    text_log.PopIndent();
    break;

  case ON_X_EVENT::no_x_event:
    break;
  }

  switch( m_type )
  {
  case ON_X_EVENT::ccx_point:
    // don't use %g so the text_log double format can control display precision
    text_log.Print("curveB(");
    text_log.Print(m_b[0]);
    text_log.Print(") = \n");
    text_log.PushIndent();
    text_log.Print(m_B[0]);
    text_log.Print("\n");
    text_log.PopIndent();
    DumpDistanceABHelper(text_log,m_A[0],m_B[0]);
    break;

  case ON_X_EVENT::csx_point:
    // don't use %g so the text_log double format can control display precision
    text_log.Print("surfaceB");
    text_log.Print(ON_2dPoint(m_b[0],m_b[1]));
    text_log.Print(" = \n");
    text_log.PushIndent();
    text_log.Print(m_B[0]);
    text_log.Print("\n");
    text_log.PopIndent();
    DumpDistanceABHelper(text_log,m_A[0],m_B[0]);
    break;

  case ON_X_EVENT::ccx_overlap:
    // don't use %g so the text_log double format can control display precision
    text_log.Print("curveB(");
    text_log.Print(m_b[0]);
    text_log.Print(" to ");
    text_log.Print(m_b[1]);
    text_log.Print(") = \n");
    text_log.PushIndent();
    text_log.Print(m_B[0]);
    text_log.Print(" to ");
    text_log.Print(m_B[1]);
    text_log.Print("\n");
    text_log.PopIndent();
    DumpDistanceABHelper(text_log,m_A[0],m_B[0],m_A[1],m_B[1]);
    break;

  case ON_X_EVENT::csx_overlap:
    // don't use %g so the text_log double format can control display precision
    text_log.Print("surface(");
    text_log.Print(ON_2dPoint(m_b[0],m_b[1]));
    text_log.Print(" to ");
    text_log.Print(ON_2dPoint(m_b[2],m_b[3]));
    text_log.Print(") =  \n");
    text_log.PushIndent();
    text_log.Print(m_B[0]);
    text_log.Print(" to ");
    text_log.Print(m_B[1]);
    text_log.Print("\n");
    text_log.PopIndent();
    DumpDistanceABHelper(text_log,m_A[0],m_B[0],m_A[1],m_B[1]);
    break;

  case ON_X_EVENT::no_x_event:
    break;
  }

  text_log.Print("m_dirA[] = (");
  for ( j = 0; j < 2; j++ )
  {
    if (j)
    {
      text_log.Print(", ");
    }
    switch(m_dirA[j])
    {
    case ON_X_EVENT::no_x_dir:
      text_log.Print("no_x_dir");
      break;
    case ON_X_EVENT::at_end_dir:
      text_log.Print("at_end_dir");
      break;
    case ON_X_EVENT::from_above_dir:
      text_log.Print("from_above_dir");
      break;
    case ON_X_EVENT::from_below_dir:
      text_log.Print("from_below_dir");
      break;
    case ON_X_EVENT::from_on_dir:
      text_log.Print("from_on_dir");
      break;
    case ON_X_EVENT::to_above_dir:
      text_log.Print("to_above_dir");
      break;
    case ON_X_EVENT::to_below_dir:
      text_log.Print("to_below_dir");
      break;
    case ON_X_EVENT::to_on_dir:
      text_log.Print("to_on_dir");
      break;
    default:
      text_log.Print("illegal value");
      break;
    }
  }
  text_log.Print(")\n");

#if defined(OPENNURBS_PLUS_INC_)
  switch( m_type )
  {
  case ON_X_EVENT::ccx_point:
  case ON_X_EVENT::ccx_overlap:
    text_log.Print("cnodeA sn = %d,%d  ",m_cnodeA[0]?m_cnodeA[0]->m_nodesn:-1,m_cnodeA[1]?m_cnodeA[1]->m_nodesn:-1);
    text_log.Print("cnodeB sn = %d,%d\n",m_cnodeB[0]?m_cnodeB[0]->m_nodesn:-1,m_cnodeB[1]?m_cnodeB[1]->m_nodesn:-1);
    break;

  case ON_X_EVENT::csx_point:
  case ON_X_EVENT::csx_overlap:
    text_log.Print("cnodeA sn = %d,%d  ",m_cnodeA[0]?m_cnodeA[0]->m_nodesn:-1,m_cnodeA[1]?m_cnodeA[1]->m_nodesn:-1);
    text_log.Print("snodeB sn = %d,%d\n",m_snodeB[0]?m_snodeB[0]->m_nodesn:-1,m_snodeB[1]?m_snodeB[1]->m_nodesn:-1);
    break;
  }
#endif

  text_log.PopIndent();
}


double ON_X_EVENT::IntersectionTolerance( double intersection_tolerance )
{
  if ( intersection_tolerance <= 0.0 || !ON_IsValid(intersection_tolerance) )
  {
    intersection_tolerance = 0.001;
  }
  else if ( intersection_tolerance < 1.0e-6 )
  {
    intersection_tolerance = 1.0e-6;
  }
  return intersection_tolerance;
}

double ON_X_EVENT::OverlapTolerance( double intersection_tolerance, double overlap_tolerance )
{
  if ( overlap_tolerance <= 0.0 || !ON_IsValid(overlap_tolerance) )
  {
    overlap_tolerance = 2.0*IntersectionTolerance(intersection_tolerance);
  }
  else if ( overlap_tolerance < 1.0e-6 )
  {
    overlap_tolerance = 1.0e-6;
  }
  return overlap_tolerance;
}

bool ON_X_EVENT::IsPointEvent() const
{
  return (ccx_point == m_type || csx_point == m_type);
}

bool ON_X_EVENT::IsOverlapEvent() const
{
  return (ccx_overlap == m_type || csx_overlap == m_type);
}

bool ON_X_EVENT::IsCCXEvent() const
{
  return (ccx_point == m_type || ccx_overlap == m_type);
}

bool ON_X_EVENT::IsCSXEvent() const
{
  return (csx_point == m_type || csx_overlap == m_type);
}



ON_SSX_EVENT::ON_SSX_EVENT()
{
  memset(this,0,sizeof(*this));
}

ON_SSX_EVENT::~ON_SSX_EVENT()
{
  if ( m_curveA )
  {
    delete m_curveA;
    m_curveA = 0;
  }
  if ( m_curveB )
  {
    delete m_curveB;
    m_curveB = 0;
  }
  if ( m_curve3d )
  {
    delete m_curve3d;
    m_curve3d = 0;
  }
}

void ON_SSX_EVENT::Dump(ON_TextLog& text_log) const
{
 
  text_log.Print("m_type: ");
  switch( m_type )
  {
  case ON_SSX_EVENT::no_ssx_event:
    text_log.Print("no_ssx_event");
    break;
  case ON_SSX_EVENT::ssx_transverse:
    text_log.Print("ssx_transverse");
    break;
  case ON_SSX_EVENT::ssx_tangent:
    text_log.Print("ssx_tangent");
    break;
  case ON_SSX_EVENT::ssx_overlap:
    text_log.Print("ssx_overlap");
    break;
  case ON_SSX_EVENT::ssx_transverse_point:
    text_log.Print("ssx_transverse_point");
    break;
	case ON_SSX_EVENT::ssx_tangent_point:
    text_log.Print("ssx_tangent_point");
    break;
  default:
    text_log.Print("illegal value");
    break;
  }
  text_log.Print("\n");
  text_log.PushIndent();

  switch( m_type )
  {
  case ON_SSX_EVENT::ssx_transverse_point:
  case ON_SSX_EVENT::ssx_tangent_point:
    // don't use %g so the text_log double format can control display precision
    text_log.Print("SurfaceA(");
    text_log.Print(m_pointA[0]);
    text_log.Print(",");
    text_log.Print(m_pointA[1]);
    text_log.Print(") = \n");

    text_log.Print("SurfaceB(");
    text_log.Print(m_pointB[0]);
    text_log.Print(",");
    text_log.Print(m_pointB[1]);
    text_log.Print(") = \n");

    text_log.PushIndent();
    text_log.Print(m_point3d);
    text_log.Print("\n");
    text_log.PopIndent();
    break;

  case ON_SSX_EVENT::no_ssx_event:
  case ON_SSX_EVENT::ssx_transverse:
  case ON_SSX_EVENT::ssx_tangent:
  case ON_SSX_EVENT::ssx_overlap:
  case ON_SSX_EVENT::ssx_32bit_enum:
    // these extra cses keep gcc happy and quiet
    break;
	}
}

class ON__SSXTester_Helper {
public:
  ON__SSXTester_Helper( ON_TextLog* text_log,
                    const class ON_Surface* surfaceA,
                    const class ON_Interval surfaceA_domain[2],
                    const class ON_Surface* surfaceB,
                    const class ON_Interval surfaceB_domain[2]);
  const ON_Surface& SA;
  const ON_Surface& SB;
  ON_Interval Adom[2];
  ON_Interval Bdom[2];

  ON_TextLog* log;

  double tol;
  bool TestDir;

  bool TestPoint( ON_2dPoint A, ON_2dPoint B, ON_3dPoint P , double* error=NULL);

private:
  // no implementation
  ON__SSXTester_Helper& operator=(const ON__SSXTester_Helper&);
};

bool ON_SSX_EVENT::IsValid(
        ON_TextLog* text_log,
        double intersection_tolerance,
        double overlap_tolerance,
        double fitting_tolerance,
        const class ON_Surface* surfaceA,
        const class ON_Interval* surfaceA_domain0,
        const class ON_Interval* surfaceA_domain1,
        const class ON_Surface* surfaceB,
        const class ON_Interval* surfaceB_domain0,
        const class ON_Interval* surfaceB_domain1
        ) const
{
  ON_Interval ADomain[2];
  ON_Interval BDomain[2];

  double xtol = intersection_tolerance;
  double otol = overlap_tolerance;
  double ftol = fitting_tolerance;

  if( surfaceA==NULL)
  {
     ON_ERROR("ON_SSX_EVENT::IsValid - No surfaceA passed in");
     return false;
  }

  if( surfaceB==NULL)
  {
     ON_ERROR("ON_SSX_EVENT::IsValid - No surfaceB passed in");
     return false;
  }

  // fill in default tolerance values
  if ( !ON_IsValid(xtol) || xtol <= 0.0 )
    xtol = 0.001;
  if ( !ON_IsValid(otol) || otol <= 0.0 )
    otol = 2.0*xtol;
  if ( !ON_IsValid(ftol) || ftol <= 0.0 )
  {
    ftol = xtol;
    if ( ftol < 0.0001 ) //GBA 15 Nov 2007 . I changed this from .001 to .0001
      ftol = 0.0001;
  }


  // Check domain parameters
 if(surfaceA_domain0)
 {
    if ( !surfaceA_domain0->IsIncreasing() )
    {
      ON_ERROR("ON_SSX_EVENT::IsValid - Bogus surfaceA_domain0 passed in");
      surfaceA_domain0 = NULL;
    }    
 }
 if(surfaceA_domain1)
 {
    if ( !surfaceA_domain1->IsIncreasing() )
    {
      ON_ERROR("ON_SSX_EVENT::IsValid - Bogus surfaceA_domain1 passed in");
      surfaceA_domain1 = NULL;
    }    
 }
 if(surfaceB_domain0)
 {
    if ( !surfaceB_domain0->IsIncreasing() )
    {
      ON_ERROR("ON_SSX_EVENT::IsValid - Bogus surfaceB_domain0 passed in");
      surfaceB_domain0 = NULL;
    }    
 }
 if(surfaceB_domain1)
 {
    if ( !surfaceB_domain1->IsIncreasing() )
    {
      ON_ERROR("ON_SSX_EVENT::IsValid - Bogus surfaceB_domain1 passed in");
      surfaceB_domain1 = NULL;
    }    
 }

 ON_Interval dom;
 ADomain[0]=surfaceA->Domain(0);
 if( surfaceA_domain0)
 {
    dom.Intersection( ADomain[0], *surfaceA_domain0);
    if(dom.IsEmptySet())
      ON_ERROR("ON_SSX_EVENT::IsValid() surfaceA_domain0 is disjoint from SurfaceA->Domain(0)");
    else
      ADomain[0]=dom;
 }

 ADomain[1]=surfaceA->Domain(1);
 if( surfaceA_domain1)
 {
    dom.Intersection( ADomain[1], *surfaceA_domain1);
    if(dom.IsEmptySet())
      ON_ERROR("ON_SSX_EVENT::IsValid() surfaceA_domain1 is disjoint from SurfaceA->Domain(1)");
    else
      ADomain[1]=dom;
 }

 BDomain[0]=surfaceB->Domain(0);
 if( surfaceB_domain0)
 {
    dom.Intersection( BDomain[0], *surfaceB_domain0);
    if(dom.IsEmptySet())
      ON_ERROR("ON_SSX_EVENT::IsValid() surfaceB_domain0 is disjoint from SurfaceB->Domain(0)");
    else
      BDomain[0]=dom;
 }

 BDomain[1]=surfaceB->Domain(1);
 if( surfaceB_domain1)
 {
    dom.Intersection( BDomain[1], *surfaceB_domain1);
    if(dom.IsEmptySet())
      ON_ERROR("ON_SSX_EVENT::IsValid() surfaceB_domain1 is disjoint from SurfaceB->Domain(1)");
    else
      BDomain[1]=dom;
 }

  bool rc = true;
  double dist = ON_UNSET_VALUE;
  ON_3dPoint A;
  ON_3dPoint B ;

  if(text_log)
    text_log->SetIndentSize(6);

  switch(m_type)
  {
  case no_ssx_event:
    if ( text_log )
      text_log->Print("ON_SSX_EVENT::m_type = no_ssx_event - should be set to a valid value.\n");
    return false;

  case ssx_transverse:
    {
      if( !m_curveA || !m_curveB || !m_curve3d)
      {
        if(text_log)
          text_log->Print("ON_SSX_EVENT::m_curve** == NULL for an ssx_transverse event.\n");
        return false; 
      }

      m_curveA->IsValid( text_log);
      m_curveB->IsValid( text_log);
      m_curve3d->IsValid( text_log);

      ON_Interval cdom= m_curve3d->Domain();
      ON_Interval adom = m_curveA->Domain();
      ON_Interval bdom = m_curveB->Domain();
      if( adom!=cdom)
      {
        if( text_log)
          text_log->Print("ON_SSX_EVENT::m_curve3d->Domain() != m_curveA->Domain().\n");
        rc = false;
      }
      if( bdom!=cdom)
      {
        if( text_log)
          text_log->Print("ON_SSX_EVENT::m_curve3d->Domain() != m_curveB->Domain().\n");
        rc = false;
      }
      int cvcnt = 8;
      ON_NurbsCurve* nc = ON_NurbsCurve::Cast(m_curve3d);
      if(nc && nc->CVCount()>cvcnt)
        cvcnt = nc->CVCount();
      nc = ON_NurbsCurve::Cast(m_curveA);
      if(nc && nc->CVCount()>cvcnt)
        cvcnt = nc->CVCount(); 
      nc = ON_NurbsCurve::Cast(m_curveB);
      if(nc && nc->CVCount()>cvcnt)
        cvcnt = nc->CVCount();
      
      ON__SSXTester_Helper TestIt(text_log,  surfaceA,  ADomain, surfaceB, BDomain); 
      TestIt.tol = ftol;

      cvcnt = (cvcnt-3)*5;

      ON_3dPoint P;
      ON_2dPoint A,B;
      bool ok = true;
      ON_wString smax_log;
      ON_wString sfirst_log;
      ON_wString spoint_log;

      double t=ON_UNSET_VALUE;
      double maxerr = 0;
      for(int i=0;  i<=cvcnt; i++)
      {
        double err=0;
        ON_wString spoint_log;
        ON_TextLog point_log(spoint_log);
        TestIt.log = &point_log;

        t = cdom.ParameterAt( double(i)/cvcnt);
        P = m_curve3d->PointAt(t);
        A = m_curveA->PointAt(t);
        B = m_curveB->PointAt(t);
        if( !TestIt.TestPoint(A, B, P, &err))
        {
					if(err>maxerr)
          {
            maxerr = err;
            smax_log = spoint_log;
          }
					else if( ok){
						sfirst_log = spoint_log;
					}
          ok = false; 
        }
      }
      if(!ok)
      {
        if(text_log)
        {
          text_log->Print("ON_SSX_EVENT: Curve point at parameter %g not valid intersection point:\n", t);
          text_log->PushIndent();
          text_log->Print( sfirst_log );
          text_log->Print( smax_log );
          text_log->PopIndent();
        }
      }
      if (rc)
        rc = ok;
      break;
    }

  case ssx_tangent:
    {
      if( !m_curveA || !m_curveB || !m_curve3d)
      {
        if(text_log)
          text_log->Print(" m_curve** == NULL for an ssx_tangent event.\n");
        return false; 
      }

      m_curveA->IsValid( text_log);
      m_curveB->IsValid( text_log);
      m_curve3d->IsValid( text_log);

      ON_Interval cdom= m_curve3d->Domain();
      ON_Interval adom = m_curveA->Domain();
      ON_Interval bdom = m_curveB->Domain();
      if( adom!=cdom)
      {
        if( text_log)
         text_log->Print("  ON_SSX_EVENT m_curve3d->Domain() != m_curveA->Domain().\n");
      }
      if( bdom!=cdom)
      {
        if( text_log)
         text_log->Print("  ON_SSX_EVENT m_curve3d->Domain() != m_curveB->Domain().\n");
      }
      int cvcnt = 8;
      ON_NurbsCurve* nc = ON_NurbsCurve::Cast(m_curve3d);
      if(nc && nc->CVCount()>cvcnt)
        cvcnt = nc->CVCount();
      nc = ON_NurbsCurve::Cast(m_curveA);
      if(nc && nc->CVCount()>cvcnt)
        cvcnt = nc->CVCount(); 
      nc = ON_NurbsCurve::Cast(m_curveB);
      if(nc && nc->CVCount()>cvcnt)
        cvcnt = nc->CVCount();
      
      ON__SSXTester_Helper TestIt(text_log,  surfaceA,  ADomain, surfaceB, BDomain); 
      TestIt.tol = xtol;
      TestIt.log = text_log;

      cvcnt = (cvcnt-3)*5;

      ON_3dPoint P;
      ON_2dPoint A,B;
      bool ok = true;
      for(int i=0; ok && i<=cvcnt; i++)
      {
        double t = cdom.ParameterAt( double(i)/cvcnt);
        P = m_curve3d->PointAt(t);
        A = m_curveA->PointAt(t);
        B = m_curveB->PointAt(t);
        ok = TestIt.TestPoint(A, B, P);
      }
      rc = ok;
      break;
    }


  case ssx_overlap:
    if( !m_curveA || !m_curveB || !m_curve3d)
    {
      if(text_log)
        text_log->Print(" m_curve** == NULL for an ssx_overlap event.\n");
      return false; 
    }

    m_curveA->IsValid( text_log);
    m_curveB->IsValid( text_log);
    m_curve3d->IsValid( text_log);
    //todo ...

    break;

  case ssx_tangent_point:
    if( m_curveA || m_curveB || m_curve3d)
    {
      if( text_log)
        text_log->Print("ON_SSX_EVENT:m_curve* !=NULL for an ssx_tangent_point event.\n");
      rc = false;
    }

    if( m_pointA.z!=0)
    {
       if( text_log)
         text_log->Print("ON_SSX_EVENT::m_pointA.z != 0.0 for an ssx_tangent_point event.\n");
       rc = false;
    }
    if( m_pointB.z!=0)
    {
       if( text_log)
         text_log->Print("ON_SSX_EVENT::m_pointB.z != 0.0 for an ssx_tangent_point event.\n");
       rc = false;
    }

    if( !ADomain[0].Includes(m_pointA.x) || !ADomain[1].Includes(m_pointA.y) )
    {
      if( text_log)
        text_log->Print("  m_pointA outside of surfaceA.Domain().\n");
      rc = false;
    }
    if( !BDomain[0].Includes(m_pointB.x) || !BDomain[1].Includes(m_pointB.y) )
    {
      if( text_log)
        text_log->Print("  m_pointB outside of surfaceB.Domain().\n");
      rc = false;
    }
    if(!rc)
      return false;

    A = surfaceA->PointAt( m_pointA.x, m_pointA.y );
    B = surfaceA->PointAt( m_pointB.x, m_pointB.y );
    dist = A.DistanceTo(m_point3d);
    if(dist>xtol)
    {
      if(text_log)
        text_log->Print(" SurfaceA->PointAt( m_pointA).DistanceTo(m_point3d)=%g > intersection_tolerance = &g.\n", dist, xtol); 
      rc = false;
    }
    dist = B.DistanceTo(m_point3d);
    if(dist>xtol)
    {
      if(text_log)
        text_log->Print(" SurfaceB->PointAt( m_pointA).DistanceTo(m_point3d)=%g > intersection_tolerance = &g.\n", dist, xtol); 
      rc = false;
    }
    dist = B.DistanceTo(A);
    if(dist>xtol)
    {
      if(text_log)
        text_log->Print(" SurfaceB->PointAt( m_pointA).DistanceTo(SurfaceB->PointAt( m_pointB))=%g > intersection_tolerance = &g.\n", dist, xtol); 
      rc = false;
    }
    break;

  case ssx_transverse_point:
    if( m_curveA || m_curveB || m_curve3d)
    {
      if( text_log)
        text_log->Print("ON_SSX_EVENT:m_curve* !=NULL for an ssx_transverse_point event.\n");
      rc = false;
    }

   if( m_pointA.z!=0)
    {
       if( text_log)
         text_log->Print("ON_SSX_EVENT::m_pointA.z != 0.0 for an ssx_transverse_point event.\n");
       rc = false;
    }
    if( m_pointB.z!=0)
    {
       if( text_log)
         text_log->Print("ON_SSX_EVENT::m_pointB.z != 0.0 for an ssx_transverse_point event.\n");
       rc = false;
    }



    if( !ADomain[0].Includes(m_pointA.x) || !ADomain[1].Includes(m_pointA.y) )
    {
      if( text_log)
        text_log->Print("  m_pointA outside of surfaceA.Domain().\n");
      rc = false;
    }
    if( !BDomain[0].Includes(m_pointB.x) || !BDomain[1].Includes(m_pointB.y) )
    {
      if( text_log)
        text_log->Print("  m_pointB outside of surfaceB.Domain().\n");
      rc = false;
    }
    if(!rc)
      return false;

    A = surfaceA->PointAt( m_pointA.x, m_pointA.y );
    B = surfaceB->PointAt( m_pointB.x, m_pointB.y );
    dist = A.DistanceTo(m_point3d);
    if(dist>xtol)
    {
      if(text_log)
        text_log->Print(" SurfaceA->PointAt( m_pointA).DistanceTo(m_point3d)=%g > intersection_tolerance = &g.\n", dist, xtol); 
      rc = false;
    }
    dist = B.DistanceTo(m_point3d);
    if(dist>xtol)
    {
      if(text_log)
        text_log->Print(" SurfaceB->PointAt( m_pointA).DistanceTo(m_point3d)=%g > intersection_tolerance = &g.\n", dist, xtol); 
      rc = false;
    }
    dist = B.DistanceTo(A);
    if(dist>xtol)
    {
      if(text_log)
        text_log->Print(" SurfaceB->PointAt( m_pointA).DistanceTo(SurfaceB->PointAt( m_pointB))=%g > intersection_tolerance = &g.\n", dist, xtol); 
      rc = false;
    }
    break;

  default:
    if ( text_log )
      text_log->Print("ON_SSX_EVENT.m_type set to undefined value.\n");
    return false;
  }
 
 return rc;
}

bool ON_SSX_EVENT::IsPointEvent() const
{
  return (    ON_SSX_EVENT::ssx_transverse_point == m_type 
           || ON_SSX_EVENT::ssx_tangent_point == m_type);
}

bool ON_SSX_EVENT::IsTinyEvent(double tiny_tolerance) const
{
  if (    ON_SSX_EVENT::ssx_transverse_point == m_type 
       || ON_SSX_EVENT::ssx_tangent_point == m_type
     )
    return true; // point event is always "tiny"

  if (   ON_SSX_EVENT::ssx_transverse != m_type 
      && ON_SSX_EVENT::ssx_tangent    != m_type
      && ON_SSX_EVENT::ssx_overlap    != m_type
      )
    return false;

  if ( !m_curve3d )
    return false;

  if ( tiny_tolerance <= 0.0 || !ON_IsValid(tiny_tolerance) )
    return false;


  // quick endpoint check to avoid bounding box
  // calculation in most cases
  ON_3dPoint P0 = m_curve3d->PointAtStart();
  ON_3dPoint P1 = m_curve3d->PointAtEnd();
  if ( !P0.IsValid() )
    return false;
  if ( !P1.IsValid() )
    return false;
  if ( fabs(P0.x-P1.x) > tiny_tolerance )
    return false;
  if ( fabs(P0.y-P1.y) > tiny_tolerance )
    return false;
  if ( fabs(P0.z-P1.z) > tiny_tolerance )
    return false;

  // check m_curve3d's bounding box
  P0.z = P1.z = 0.0;
  if ( !m_curve3d->GetBBox(&P0.x,&P1.x,false) )
    return false;
  if ( fabs(P0.x-P1.x) > tiny_tolerance )
    return false;
  if ( fabs(P0.y-P1.y) > tiny_tolerance )
    return false;
  if ( fabs(P0.z-P1.z) > tiny_tolerance )
    return false;

  return true; // curve event is "tiny"
}


bool ON_SSX_EVENT::IsCurveEvent() const
{
  return (ON_SSX_EVENT::ssx_transverse == m_type || ON_SSX_EVENT::ssx_tangent == m_type);
}

bool ON_SSX_EVENT::IsTangentEvent() const
{
  return (ON_SSX_EVENT::ssx_tangent == m_type || ON_SSX_EVENT::ssx_tangent_point == m_type);
}

bool ON_SSX_EVENT::IsOverlapEvent() const
{
  return (ON_SSX_EVENT::ssx_overlap == m_type);
}

// helper class for test intersection points


ON__SSXTester_Helper::ON__SSXTester_Helper(ON_TextLog* text_log,
                    const class ON_Surface* surfaceA,
                    const class ON_Interval surfaceA_domain[2],
                    const class ON_Surface* surfaceB,
                    const class ON_Interval surfaceB_domain[2]) :
SA(*surfaceA), SB(*surfaceB) 
{
	Adom[0] = surfaceA_domain[0];
	Adom[1] = surfaceA_domain[1]; 
	Bdom[0] = surfaceB_domain[0]; 
    Bdom[1] = surfaceB_domain[1]; 
   tol = .01;

   log = text_log;
}

bool ON__SSXTester_Helper::TestPoint(ON_2dPoint A, ON_2dPoint B, ON_3dPoint P, double* error)
{
  bool rc = true;
  double err=0;

  if( !Adom[0].Includes(A.x) || !Adom[1].Includes(A.y) )
  {
    if(log)
      log-> Print("  Point a outside of SurfaceA domain.\n");
    rc = false;
  }
  if( !Bdom[0].Includes(B.x) || !Bdom[1].Includes(B.y) )
  {
    if(log)
      log-> Print("  Point b outside of SurfaceB domain.\n");
    rc = false;
  }


  double dist;

  ON_2dPoint st, uv;
  st = A;
  SA.GetLocalClosestPoint(P, A.x, A.y, &st.x, &st.y, &Adom[0], &Adom[1] );
  ON_3dPoint PA = SA.PointAt(st.x, st.y); 
  dist = P.DistanceTo(PA);

  if( dist>tol)
  {
    if(log)
      log->Print(" Distance(P, Srf_A) = %g > tolerance = %g.\n", dist, tol);
    rc = false;
    if(dist>err) err = dist;
  }
  uv = B;
  SB.GetLocalClosestPoint(P, uv.x, uv.y, &uv.x, &uv.y, &Bdom[0], &Bdom[1] );
  ON_3dPoint PB = SB.PointAt(uv.x, uv.y); 
  dist = P.DistanceTo(PB);

  if( dist>tol)
  {
    if(log)
      log->Print(" Distance(P, Srf_B) = %g > tolerance = %g.\n", dist, tol);
    rc = false;
    if(dist>err) err = dist;
  }


  PA = SA.PointAt(A.x, A.y);
  SB.GetLocalClosestPoint(PA, B.x, B.y, &uv.x, &uv.y, &Bdom[0], &Bdom[1] );
  PB = SB.PointAt(uv.x, uv.y); 
  dist = PA.DistanceTo(PB);
  if( dist>tol)
  {
    if(log)
      log->Print(" Distance(S(A), Srf_B) = %g > tolerance = %g.\n", dist, tol);
    rc = false;
    if(dist>err) err = dist;
  }

  PB = SB.PointAt(B.x, B.y);
  SA.GetLocalClosestPoint(PB, A.x, A.y, &st.x, &st.y, &Adom[0], &Adom[1] );
  PA = SA.PointAt(st.x, st.y); 
  dist = PA.DistanceTo(PB);
  if( dist>tol)
  {
    if(log)
      log->Print(" Distance(S(B), Srf_A) = %g > tolerance = %g.\n", dist, tol);
    rc = false;
    if(dist>err) err = dist;
  }

  if(!rc && error)
    *error = err;
  return rc;
}

