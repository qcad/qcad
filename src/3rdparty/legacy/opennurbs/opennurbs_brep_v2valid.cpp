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


void ON_Brep::RebuildTrimsForV2(
                ON_BrepFace& face, 
                const ON_NurbsSurface& nurbs_surface
                )
{
  /*
    No support is available for this function.
    Expert user function used by MakeValidForV2.to
    convert trim curves from one surface to its
    NURBS form.  After calling this function, you
    need to change the face's surface to nurbs_surface.
  */

  // 6 August 2003 Dale Lear:
  //
  //   The PRIMARY use of ON_Brep::RebuildTrimsForV2()
  //   is to create geometry that can be written to 
  //   files that V2 can read.
  //
  //   NEVER change this function without first completely 
  //   understanding how TL_Brep::Write() works.  You MUST
  //   do extensive testing of saving V2 files from V3
  //   and then reading those files into Rhino V2 before
  //   you check in any changes.

  ON_Brep& brep = *this;
  ON_3dPoint uv0, uv1;
  int fli, lti, loop_trim_count;
  ON_SimpleArray< ON_2dPoint > nurbsuv;
  ON_SimpleArray< ON_3dPoint > pt;
  ON_SimpleArray< ON_BrepTrim* > loop_trim;
  const ON_Surface* face_srf = face.SurfaceOf();
  if ( 0 == face_srf )
    return;
  for ( fli = 0; fli < face.m_li.Count(); fli++ )
  {
    ON_BrepLoop* loop = brep.Loop(face.m_li[fli]);
    if ( 0 == loop )
      continue;
    loop_trim_count = loop->m_ti.Count();
    loop_trim.Reserve( loop_trim_count );
    nurbsuv.Reserve( loop_trim_count );
    pt.Reserve( loop_trim_count );
    loop_trim.SetCount(0);
    nurbsuv.SetCount(0);
    pt.SetCount(0);

    for ( lti = 0; lti < loop_trim_count; lti++ )
    {
      ON_BrepTrim* trim = brep.Trim(loop->m_ti[lti]);
      if ( 0 == trim )
        break;
      loop_trim.Append(trim);
      uv0 = trim->PointAtStart();
      pt.Append( face_srf->PointAt(uv0.x,uv0.y) );
      double xx,yy;
      if ( face.GetNurbFormParameterFromSurfaceParameter(uv0.x, uv0.y, &xx, &yy) ) // Oct 29, 2009 Dale Lear added test for function failing 
      {
        uv0.x = xx;
        uv0.y = yy;
      }

      // 17 October 2006 Chuck
      //    Fixed this to use the N0 test so we don't
      //    get complete garbage at singular points.
      //    It is still wrong, but the answer is a lot
      //    better than it was before the fix.
      ON_3dPoint N0 = nurbs_surface.PointAt(uv0.x,uv0.y);
      const ON_BrepEdge* edge = brep.Edge(trim->m_ei);
      double pbtol = edge ? edge->m_tolerance : 1.0e-5;
      if ( !ON_IsValid(pbtol) || pbtol < 1.0e-5 )
        pbtol = 1.0e-5;
      else if (pbtol > 0.01 )
        pbtol = 0.01;
      if ( pt.Last()->DistanceTo(N0) <= pbtol )
        uv1 = uv0;
      else if ( !nurbs_surface.GetLocalClosestPoint( pt[lti], uv0.x, uv0.y, &uv1.x, &uv1.y, NULL, NULL ) )
        break;
      nurbsuv.Append(uv1);
    }
    if ( nurbsuv.Count() != loop_trim_count )
      continue;
    loop->m_pbox.Destroy();
    uv1 = nurbsuv[0];
    for ( lti = 0; lti < loop_trim_count; lti++ )
    {
      uv0 = uv1;
      uv1 = nurbsuv[(lti+1)%loop_trim_count];
      ON_BrepTrim& trim = *loop_trim[lti];
      ON_Curve* c2 = 0;
      if ( trim.m_iso == ON_Surface::not_iso )
      {
        const ON_BrepEdge* edge = brep.Edge(trim.m_ei);
        if ( edge )
        {
          double pbtol = edge->m_tolerance;
          if ( pbtol < 0.001 )
            pbtol = 0.001;
          if (trim.m_bRev3d) 
            c2 = nurbs_surface.Pullback(*edge,pbtol,NULL,uv1,uv0);
          else
            c2 = nurbs_surface.Pullback(*edge,pbtol,NULL,uv0,uv1);
          if ( !c2 )
          {
            c2 = trim.DuplicateCurve();
            ON_Xform T1(1), SR(1), T2(1), x;
            ON_3dPoint a0 = trim.PointAtStart();
            ON_3dPoint a1 = trim.PointAtEnd();
            ON_3dVector v = 0.5*(a0+a1); v.z = 0.0;
            T1.Translation(-v);
            v = 0.5*(uv0+uv1); v.z = 0.0;
            T2.Translation(v);
            double s1 = a0.DistanceTo(a1);
            double s2 = uv0.DistanceTo(uv1);
            if ( s1 > 0.0 && s2 > 0.0 
                 && s2 > s1*ON_SQRT_EPSILON 
                 &&  s1 > s2*ON_SQRT_EPSILON )
            {
              ON_Xform S(1), R(1);
              S.Scale(ON_origin,s2/s1);
              ON_3dVector a = a1-a0;
              ON_3dVector b = uv1 - uv0;
              a.Unitize();
              b.Unitize();
              a.z = 0.0; b.z = 0.0;
              ON_3dVector z = ON_CrossProduct(a,b);
              double sa = z.Length();
              z.Unitize();
              double ca = a*b;
              R.Rotation( sa, ca, z, ON_origin );
              SR = S*R;
            }
            x = T2*SR*T1;
            c2->Transform(x);
          }
          else if ( c2 && trim.m_bRev3d )
            c2->Reverse();
        }
      }
      if ( 0 == c2 )
      {
        ON_NurbsCurve* nc2 = new ON_NurbsCurve(2,0,2,2);
        nc2->m_knot[0] = 0.0;
        nc2->m_knot[1] = 1.0;
        nc2->SetCV(0,uv0);
        nc2->SetCV(nc2->m_cv_count-1,uv1);
        c2 = nc2;
      }

      //some trims that weren't isos end up being isos.  Pullback creates ON_LineCurves.
      if (!ON_NurbsCurve::Cast(c2)){
        ON_NurbsCurve* nc2 = c2->NurbsCurve();
        if (0 != nc2){
          delete c2;
          c2 = nc2;
        }
      }
      c2->ON_Curve::SetDomain( trim.Domain() );
      c2->SetStartPoint(uv0);
      c2->SetEndPoint(uv1);
      int c2i = brep.AddTrimCurve(c2);
      trim.ChangeTrimCurve(c2i);
      //sometimes nearly iso curves become iso. Chuck 4/11/03
      if (trim.m_iso == ON_Surface::not_iso)
        brep.SetTrimIsoFlags(trim);
      loop->m_pbox.Union(trim.m_pbox);
    }
  }

  // 6 August 2003 Dale Lear:
  //
  //   The PRIMARY use of ON_Brep::RebuildTrimsForV2()
  //   is to create geometry that can be written to 
  //   files that V2 can read.
  //
  //   NEVER change this function without first completely 
  //   understanding how TL_Brep::Write() works.  You MUST
  //   do extensive testing of saving V2 files from V3
  //   and then reading those files into Rhino V2 before
  //   you check in any changes.
}

bool ON_Brep::IsDeformable() const
{
  int ei, edge_count = m_E.Count();
  for ( ei = 0; ei < edge_count; ei++ )
  {
    const ON_BrepEdge& edge = m_E[ei];
    if ( edge.m_edge_index != ei )
      continue;
    const ON_Curve* crv = edge.EdgeCurveOf();
    if ( !crv )
      continue;
    if ( !crv->IsDeformable() )
      return false;
  }

  int fi, face_count = m_F.Count();
  for ( fi = 0; fi < face_count; fi++ )
  {
    const ON_BrepFace& face = m_F[fi];
    if ( face.m_face_index != fi )
      continue;
    const ON_Surface* srf = face.SurfaceOf();
    if ( !srf )
      continue;
    if ( !srf->IsDeformable() )
      return false;
  }

  return true;
}

bool ON_Brep::MakeDeformable()
{
  bool rc = true;

  int ei, edge_count = m_E.Count();
  for ( ei = 0; ei < edge_count; ei++ )
  {
    ON_BrepEdge& edge = m_E[ei];

    const ON_Curve* crv = edge.EdgeCurveOf();
    if ( !crv )
      continue;
    if ( crv->IsDeformable() )
      continue;
    edge.DestroyRuntimeCache();

    // Fix for RR 12669
    //   When edge uses a subset of a polycurve and MakeDeformable 
    //   reparameterizes the area where the edge begins or ends, 
    //   then the ends of the edge change.
    ON_Curve* edge_curve = 0;
    if ( edge.ProxyCurveDomain() == crv->Domain() )
    {
      if ( const_cast<ON_Curve*>(crv)->MakeDeformable() )
        continue;
      edge_curve = edge.NurbsCurve();

      // 4 April 2007 Dale Lear - don't loose user data
      // on the m_C3[] curve that will be replaced by
      // edge_curve.
      if ( edge_curve && crv )
      {
        edge_curve->CopyUserData(*crv);
      }
    }
    else
    {
      // edge.DuplicateCurve() returns a copy of the subsed of crv
      // that is used by the edge. edge.DuplicateCurve() copies
      // user data to the curve it returns.
      edge_curve = edge.DuplicateCurve();
      if ( 0 == edge_curve )
      {
        delete edge_curve;
        edge_curve = edge.NurbsCurve();
        // 4 April 2007 Dale Lear - don't loose user data
        // on the m_C3[] curve that will be replaced by
        // edge_curve.
        if ( edge_curve && crv )
        {
          edge_curve->CopyUserData(*crv);
        }
      }
      else if  ( !edge_curve->MakeDeformable() )
      {
        ON_NurbsCurve* nurbs_curve = edge_curve->NurbsCurve();
        delete edge_curve;
        edge_curve = nurbs_curve;
        // 4 April 2007 Dale Lear - don't loose user data
        // on the m_C3[] curve that will be replaced by
        // edge_curve.
        if ( edge_curve && crv )
        {
          edge_curve->CopyUserData(*crv);
        }
      }
    }

    if ( 0 == edge_curve )
    {
      rc = false;
      continue;
    }

    int c3i = edge.m_c3i;
    if ( c3i < 0 || c3i >= m_C3.Count() || crv != m_C3[c3i] )
    {
      // original curve was not "officially" in the brep
      // (I don't know why this would happen unless the
      // brep is corrupt.)
      // add edge_curve
      c3i = AddEdgeCurve( edge_curve );
    }
    else if ( EdgeCurveUseCount( c3i, 2 ) > 1 )
    {
      // multiple edges use the original curve.
      // add edge_curve
      c3i = AddEdgeCurve( edge_curve );
    }
    else
    {
      // replace original curve with edge_curve
      delete m_C3[c3i];
      m_C3[c3i] = edge_curve;
    }
    edge.SetProxyCurve(edge_curve);
    edge.m_c3i = c3i;
  }

  int fi, face_count = m_F.Count();
  for ( fi = 0; fi < face_count; fi++ )
  {
    ON_BrepFace& face = m_F[fi];
    const ON_Surface* srf = face.SurfaceOf();
    if ( 0 == srf )
      continue;
    if ( srf->IsDeformable() )
      continue;
    if ( 0 != ON_NurbsSurface::Cast(srf) )
      continue;
    if ( FaceIsSurface(fi) )
    {
      // If the trims are on the edge of the surface,
      // we can simply make the surface deformable.
      // If the trims are more complicated, we have
      // to convert the whole thing to NURBS so we
      // can reliably rebuild the trimming curves 
      // when the surface parameterization changes.
      if ( const_cast<ON_Surface*>(srf)->MakeDeformable() )
      {
        face.DestroyRuntimeCache();
        continue;
      }
    }


    ON_NurbsSurface* nurbs_surface = ON_NurbsSurface::New();
    
    int nurbform_rc = srf->GetNurbForm(*nurbs_surface);
    if ( 0 == nurbform_rc )
    {
      delete nurbs_surface;
      rc = false;
      continue;
    }
    
    // 4 April 2007 Dale Lear - copy user data
    nurbs_surface->CopyUserData(*srf);

    if ( 2 == nurbform_rc )
    {
      // 13 Sep 2005 Dale Lear
      //   We need to update the locations of the trims because the
      //   parameterization has changed.
      RebuildTrimsForV2( face, *nurbs_surface );
    }

    face.SetProxySurface(nurbs_surface);

    if ( face.m_si < 0 || face.m_si >= m_S.Count() || srf != m_S[face.m_si] )
    {
      // original srf was not "officially" in the brep
      // (I don't know why this would happen unless the
      // brep is corrupt.)
      // add nurbs_surface
      face.m_si = AddSurface( nurbs_surface );
    }
    else if ( SurfaceUseCount( face.m_si, 2 ) > 1 )
    {
      // multiple faces use srf, add nurbs_surface
      face.m_si = AddSurface( nurbs_surface );
    }
    else
    {
      // replace srf with nurbs_surface
      delete srf;
      srf = 0;
      m_S[face.m_si] = nurbs_surface;
    }
  }

  return rc;
}

// Description:
//   Change brep so it is valid for saving
//   in V2 3DM archives.
bool ON_Brep::MakeValidForV2()
{
  int fi,ti,ei,li,lti,next_lti,next_ti, loop_trim_count;
  const ON_Surface* surface;
  ON_3dPoint P0, P1;
  double* cv;
  double w;
  int short_seg_count = 0;

  int saved_is_solid = m_is_solid;

  // prune ends of 2d curves that are trimmed by setting
  // trim.m_t to be a subinterval of the 2d curve's domain.
  const int trim_count = m_T.Count();
  for ( ti = 0; ti < trim_count; ti++ )
  {
    ON_BrepTrim& trim = m_T[ti];
    if( trim.m_trim_index != ti )
    {
      trim.m_trim_index = -1;
      continue;
    }
    if ( IsValidForV2(trim) )
      continue;
    ON_NurbsCurve* c = new ON_NurbsCurve;
    if ( trim.GetNurbForm( *c ) )
    {
      c->ClampEnd(2);
      if ( c->m_dim != 2 )
        c->ChangeDimension(2);

      // V2 is closed check
      if ( c->m_cv_count >= 4 && 0 == ON_ComparePoint( c->m_dim, c->m_is_rat, c->m_cv, c->CV(c->m_cv_count-1) ) )
      {
        // c is "closed" by V2 standards
        if ( trim.m_vi[0] != trim.m_vi[1] )
        {
          const ON_BrepLoop* loop = Loop(trim.m_li);
          if ( 0 != loop && loop->m_ti.Count() > 1 )
          {
            if ( c->IsShort(0.0001) )
            {
              // 2 June 2003 Dale Lear - RR 8843 fix
              // If this is a micro segment, then make it a line so it will read into v2.
              ON_3dPoint P0, P1;
              c->GetCV(0,P0);
              c->GetCV(c->m_cv_count-1,P1);
              c->m_knot[0] = c->m_knot[c->m_order-2];
              c->m_knot[1] = c->m_knot[c->m_cv_count-1];
              c->m_order = 2;
              c->m_cv_count = 2;
              c->m_dim = 2;
              c->m_is_rat = 0;
              c->m_cv_stride = 2;
              c->SetCV(0,P0);
              c->SetCV(1,P1);
            }
          }
        }
      }

      c->MakePiecewiseBezier(true);// 2 June 2003 Dale Lear - V2 likes end weights to be 1.0
      if ( c->RemoveShortSegments(1.0e-8) )
      {
        short_seg_count++;
      }
      trim.m_pline.Destroy();
      trim.DestroyCurveTree();
      trim.m_pbox = c->BoundingBox();
      trim.m_c2i = AddTrimCurve(c);
      trim.SetProxyCurve(m_C2[trim.m_c2i]);
    }
    else
      delete c;
  }

  const int edge_count = m_E.Count();
  for ( ei = 0; ei < edge_count; ei++ )
  {
    ON_BrepEdge& edge = m_E[ei];
    if( edge.m_edge_index != ei )
    {
      edge.m_edge_index = -1;
      continue;
    }
    if ( IsValidForV2(edge) )
      continue;
    ON_NurbsCurve* c = new ON_NurbsCurve;
    if ( edge.GetNurbForm( *c ) )
    {
      c->ClampEnd(2);
      if ( c->m_dim != 3 )
        c->ChangeDimension(3);
      if ( c->m_is_rat )
      {
        // 2 June 2003 Dale Lear - RR 8809 fix
        //    V2 likes end weights to be 1.0
        if ( c->m_cv[3] != 1.0 || c->CV(c->m_cv_count-1)[3] != 1.0 )
        {
          c->MakePiecewiseBezier(true);
        }
      }

      // V2 is closed check
      if ( c->m_cv_count >= 4 && 0 == ON_ComparePoint( c->m_dim, c->m_is_rat, c->m_cv, c->CV(c->m_cv_count-1) ) )
      {
        // c is "closed" by V2 standards
        if ( edge.m_vi[0] != edge.m_vi[1] && c->IsShort(0.0005) )
        {
          // 2 June 2003 Dale Lear - RR 8808 fix
          // If this is a micro segment, then make it a line so it will read into v2.
          ON_3dPoint P0, P1;
          c->GetCV(0,P0);
          c->GetCV(c->m_cv_count-1,P1);
          c->m_knot[0] = c->m_knot[c->m_order-2];
          c->m_knot[1] = c->m_knot[c->m_cv_count-1];
          c->m_order = 2;
          c->m_cv_count = 2;
          c->m_dim = 3;
          c->m_is_rat = 0;
          c->m_cv_stride = 3;
          c->SetCV(0,P0);
          c->SetCV(1,P1);
        }
      }
      else if ( edge.m_vi[0] == edge.m_vi[1] && !c->IsShort(0.0005) && c->m_cv_count >= 4 )
      {
        // see if we should force c to be closed.
        ON_3dPoint P0, P1;
        c->GetCV(0,P0);
        c->GetCV(c->m_cv_count-1,P1);
        if ( P0.DistanceTo(P1) <= 0.05*c->ControlPolygonLength() )
        {
          // close up c
          c->SetCV(c->m_cv_count-1,P0);
        }
      }

      if ( c->RemoveShortSegments(1.0e-6) )
      {
        short_seg_count++;
      }

      edge.DestroyCurveTree();
      edge.m_c3i = AddEdgeCurve(c);
      edge.SetProxyCurve(m_C3[edge.m_c3i]);
    }
    else
      delete c;
  }

  // force ends of trimming curves to be exactly equal
  const int loop_count = m_L.Count();
  for ( li = 0; li < loop_count; li++ )
  {
    ON_BrepLoop& loop = m_L[li];
    loop_trim_count = loop.m_ti.Count();
    loop.m_pbox.Destroy();
    for ( lti = 0; lti < loop_trim_count; lti++ )
    {
      next_lti = (lti+1)%loop_trim_count;
      ti = loop.m_ti[lti];
      next_ti = loop.m_ti[next_lti];
      if ( ti < 0 || ti >= trim_count )
        continue;
      if ( next_ti < 0 || next_ti >= trim_count )
        continue;
      ON_BrepTrim& trim = m_T[ti];
      ON_BrepTrim& next_trim = m_T[next_ti];
      P0 = trim.PointAtEnd();
      P1 = next_trim.PointAtStart();
      if ( P0 != P1 )
      {
        // tweak end of curve 
        ON_NurbsCurve* c = new ON_NurbsCurve;
        if ( trim.GetNurbForm( *c ) )
        {
          if ( c->m_is_rat && c->Weight(c->m_cv_count-1) != 1.0 )
          {
            cv = c->CV(c->m_cv_count-1);
            w = cv[c->m_dim];
            cv[0] = P1.x*w;
            cv[1] = P1.y*w;
          }
          else
            c->SetCV( c->m_cv_count-1, P1 );
          trim.m_pbox = c->BoundingBox(); // no intersection because end point moved
          trim.m_c2i = AddTrimCurve(c);
          trim.SetProxyCurve( m_C2[trim.m_c2i] );
          trim.m_pline.Destroy();
          trim.DestroyCurveTree();
        }
        else
          delete c;
      }
      loop.m_pbox.Union(trim.m_pbox);
    }
  }
  
  const int face_count = m_F.Count();
  for ( fi = 0; fi < face_count; fi++ )
  {
    ON_BrepFace& face = m_F[fi];
    surface = face.SurfaceOf();
    if ( !surface )
      continue;
    if ( ON_NurbsSurface::Cast(surface) )
      continue;
    // get a NURBS surface form of the surface;
    ON_NurbsSurface* nurbs_surface = new ON_NurbsSurface();
    int rc = surface->GetNurbForm( *nurbs_surface, 0.0 );
    if ( rc < 1 )
      delete nurbs_surface;
    else
    {
      if ( rc > 1 )
        RebuildTrimsForV2(face,*nurbs_surface);
      face.m_si = AddSurface(nurbs_surface);
      face.SetProxySurface(nurbs_surface);
    }
  }

  // removed unused items from m_V, m_E, m_T, m_F, m_C2, m_C2, and m_S arrays.
  Compact();

  m_is_solid = saved_is_solid;

  return IsValidForV2();
}

bool ON_Brep::IsValidForV2( const ON_BrepTrim& trim ) const
{
  int ti = trim.m_trim_index;
  if ( ti < 0 || ti >= m_T.Count() )
    return false;
  if ( &trim != &m_T[ti] )
    return false;
  if ( trim.ProxyCurveIsReversed() )
    return false;
  if ( trim.Domain() != trim.ProxyCurveDomain() )
    return false;
  const ON_Curve * curve = trim.TrimCurveOf();
  if ( curve != trim.ProxyCurve() )
    return false;
  const ON_NurbsCurve* nurbs_curve = ON_NurbsCurve::Cast(curve);
  if ( 0 == nurbs_curve )
    return false;
  if ( !nurbs_curve->IsClamped(2) )
    return false;
  if ( nurbs_curve->m_dim != 2 )
    return false;
  if ( nurbs_curve->m_is_rat )
  {
    // 2 June 2003 Dale Lear - RR 8809 fix
    //    V2 likes end weights to be 1.0
    if ( nurbs_curve->m_cv[2] != 1.0 || nurbs_curve->CV(nurbs_curve->m_cv_count-1)[2] != 1.0 )
    {
      return false;
    }
  }

  if (    nurbs_curve->m_cv_count >= 4 
       && 0 == ON_ComparePoint( nurbs_curve->m_dim, nurbs_curve->m_is_rat, nurbs_curve->m_cv, nurbs_curve->CV(nurbs_curve->m_cv_count-1) ) 
       )
  {
    // 14 April 2003 Dale Lear
    //     RR 8843 - V2 wants ends of this trim farther apart
    if ( trim.m_vi[0] != trim.m_vi[1] )
    {
      const ON_BrepLoop* loop = Loop(trim.m_li);
      if ( 0 != loop && loop->m_ti.Count() > 1 )
        return false;
    }
  }
  
  if ( curve->Domain() != trim.Domain() )
    return false;

  // 2 June 2003 Dale Lear
  //   RemoveShortSegments(_,false) does not modify curve.
  if ( const_cast<ON_NurbsCurve*>(nurbs_curve)->RemoveShortSegments(1.0e-8,false) )
  {
    // curve has micro segments
    return false;
  }

  return true;
}

bool ON_Brep::IsValidForV2( const ON_BrepEdge& edge ) const
{
  int ei = edge.m_edge_index;
  if ( ei < 0 || ei >= m_E.Count() )
    return false;
  if ( &edge != &m_E[ei] )
    return false;
  if ( edge.ProxyCurveIsReversed() )
    return false;
  if ( edge.Domain() != edge.ProxyCurveDomain() )
    return false;
  const ON_Curve * curve = edge.EdgeCurveOf();
  if ( curve != edge.ProxyCurve() )
    return false;
  const ON_NurbsCurve* nurbs_curve = ON_NurbsCurve::Cast(curve);
  if ( 0 == nurbs_curve )
    return false;
  if ( !nurbs_curve->IsClamped(2) )
    return false;
  if ( nurbs_curve->m_dim != 3 )
    return false;
  if ( nurbs_curve->m_is_rat )
  {
    // 2 June 2003 Dale Lear - RR 8809 fix
    //    V2 likes end weights to be 1.0
    if ( nurbs_curve->m_cv[3] != 1.0 || nurbs_curve->CV(nurbs_curve->m_cv_count-1)[3] != 1.0 )
    {
      return false;
    }
  }

  if ( curve->Domain() != edge.Domain() )
    return false;

  // 14 April 2003 Dale Lear
  //     RR 8808 - V2 requires edges to be strictly closed/open
  if (    nurbs_curve->m_cv_count >= 4 
       && 0 == ON_ComparePoint( nurbs_curve->m_dim, nurbs_curve->m_is_rat, nurbs_curve->m_cv, nurbs_curve->CV(nurbs_curve->m_cv_count-1) ) 
       )
  {
    if ( edge.m_vi[0] != edge.m_vi[1] )
      return false;
  }
  else if (edge.m_vi[0] == edge.m_vi[1] )
  {
    return false;
  }

  // 2 June 2003 Dale Lear
  //   RemoveShortSegments(_,false) does not modify curve.
  if ( const_cast<ON_NurbsCurve*>(nurbs_curve)->RemoveShortSegments(1.0e-6,false) )
  {
    // curve has micro segments
    return false;
  }

  return true;
}

bool ON_Brep::IsValidForV2() const
{
  bool rc = IsValidTopology()?true:false;
  if ( rc )
  {
    int c2i, c3i, si, ti, li, ei, vi, fi, next_ti, lti, next_lti, loop_trim_count;
    ON_3dPoint P0, P1;

    const int c2_count = m_C2.Count();
    const int c3_count = m_C3.Count();
    const int s_count  = m_S.Count();
    const int vertex_count = m_V.Count();
    const int edge_count = m_E.Count();
    const int face_count = m_F.Count();
    const int loop_count = m_L.Count();
    const int trim_count = m_T.Count();

    for ( c2i = 0; c2i < c2_count; c2i++ )
    {
      // v2 3dm files expect NURBS curves
      if ( !ON_NurbsCurve::Cast(m_C2[c2i]) )
        return false;
    }

    for ( c3i = 0; c3i < c3_count; c3i++ )
    {
      // v2 3dm files expect NURBS curves
      if ( !ON_NurbsCurve::Cast(m_C3[c3i]) )
        return false;
    }

    for ( si = 0; si < s_count; si++ )
    {
      // v2 3dm files expect NURBS surfaces
      if ( !ON_NurbsSurface::Cast(m_S[si]) )
        return false;
    }

    for ( vi = 0; vi < vertex_count; vi++ )
    {
      const ON_BrepVertex& vertex = m_V[vi];
      if ( vertex.m_vertex_index != vi )
        return false;
    }

    for ( fi = 0; fi < face_count; fi++ )
    {
      const ON_BrepFace& face = m_F[fi];
      if ( face.m_face_index != fi )
        return false;
    }

    for ( ti = 0; ti < trim_count; ti++ )
    {
      if ( !IsValidForV2( m_T[ti] ) )
        return false;
    }

    for ( ei = 0; ei < edge_count; ei++ )
    {
      if ( !IsValidForV2(m_E[ei]) )
        return false;
    }

    for ( li = 0; li < loop_count; li++ )
    {
      const ON_BrepLoop& loop = m_L[li];
      if ( loop.m_loop_index == -1 )
        return false;
      loop_trim_count = loop.m_ti.Count();
      for ( lti = 0; lti < loop_trim_count; lti++ )
      {
        next_lti = (lti+1)%loop_trim_count;
        ti = loop.m_ti[lti];
        next_ti = loop.m_ti[next_lti];
        if ( ti < 0 || ti >= trim_count )
          return false;
        if ( next_ti < 0 || next_ti >= trim_count )
          return false;
        P0 = m_T[ti].PointAtEnd();
        P1 = m_T[next_ti].PointAtStart();
        if ( P0.DistanceTo(P1) > ON_ZERO_TOLERANCE )
          return false;
      }
    }
  }

  return rc;
}

