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

static
bool ChangeEdgeVertex( 
         ON_Brep& brep,
         ON_BrepEdge& edge,
         int edge_end,
         int old_vi,
         int new_vi,
         bool bUpdateTrims
         )
{
  // used by ON_Brep::ReplaceSurface() to change edge ends

  if ( edge_end != 0 && edge_end != 1 )
    return false;
  if ( edge.m_vi[edge_end] != old_vi )
    return false;
  if ( old_vi == new_vi )
    return true;

  ON_BrepVertex* old_v = brep.Vertex(old_vi);
  if ( old_vi >= 0 && 0 == old_v )
    return false;
  if ( old_v )
    old_v->m_tolerance = ON_UNSET_VALUE;
  
  ON_BrepVertex* new_v = brep.Vertex(new_vi);
  if ( new_vi >= 0 && 0 == new_v )
    return false;
  if ( new_v )
    old_v->m_tolerance = ON_UNSET_VALUE;

  // disconnect edge from old vertex
  if ( old_vi >= 0 )
  {
    for ( int vei = 0; vei < old_v->m_ei.Count(); vei++ )
    {
      if ( old_v->m_ei[vei] == edge.m_edge_index )
      {
        old_v->m_ei.Remove(vei);
        break;
      }
    }
  }

  edge.m_vi[edge_end] = new_vi;
  new_v->m_ei.Append(edge.m_edge_index);

  if ( bUpdateTrims )
  {
    for ( int eti = 0; eti < edge.m_ti.Count(); eti++ )
    {
      ON_BrepTrim* trim = brep.Trim(edge.m_ti[eti]);
      if ( 0 == trim )
        continue;
      int trim_end = trim->m_bRev3d ? 1-edge_end : edge_end;
      if ( trim->m_vi[trim_end] == old_vi )
        trim->m_vi[trim_end] = new_vi;
    }
  }

  return true;
}



static
bool ChangeTrimVertex( 
         ON_Brep& brep,
         ON_BrepTrim& trim,
         int trim_end,
         int old_vi,
         int new_vi,
         bool bUpdateEdge,
         bool bUpdateMates
         )
{
  // used by ON_Brep::ReplaceSurface() to change trim ends
  if ( trim_end != 0 && trim_end != 1 )
    return false;
  if ( trim.m_vi[trim_end] != old_vi )
    return false;
  if ( old_vi == new_vi )
    return true;
  trim.m_vi[trim_end] = new_vi;

  ON_BrepVertex* v = brep.Vertex(old_vi);
  if ( v )
    v->m_tolerance = ON_UNSET_VALUE;
  v = brep.Vertex(new_vi);
  if ( v )
    v->m_tolerance = ON_UNSET_VALUE;

  bool rc = true;
  if ( bUpdateEdge )
  {
    ON_BrepEdge* edge = brep.Edge(trim.m_ei);
    if ( 0 == edge )
      return true;
    int edge_end = trim.m_bRev3d ? 1-trim_end : trim_end;
    rc = ChangeEdgeVertex( brep, *edge, edge_end, old_vi, new_vi, bUpdateMates );
  }

  return true;
}

static
ON_Curve* PushUpIsoTrim( ON_Brep& brep, ON_BrepTrim& trim )
{
  ON_Curve* c3 = 0;
  const ON_Surface* srf = trim.SurfaceOf();
  if ( 0 == srf )
    return 0;
  c3 = srf->ON_Surface::Pushup( trim, 0.0 );
  if ( 0 == c3 )
  {
    ON_2dPoint p0 = trim.PointAtStart();
    ON_2dPoint p1 = trim.PointAtEnd();
    double c, t0, t1;
    int isodir;
    if (    trim.m_iso == ON_Surface::N_iso 
         || trim.m_iso == ON_Surface::S_iso 
         || trim.m_iso == ON_Surface::y_iso )
    {
      isodir = 0;
      c = p0.y;
      t0 = p0.x;
      t1 = p1.x;
    }
    else if (    trim.m_iso == ON_Surface::E_iso 
              || trim.m_iso == ON_Surface::W_iso 
              || trim.m_iso == ON_Surface::x_iso  )
    {
      isodir = 1;
      c = p0.x;
      t0 = p0.y;
      t1 = p1.y;
    }
    else
      return 0;
    c3 = srf->IsoCurve( isodir, c );
    if ( 0 == c3 )
      return 0;
    ON_Interval trim_interval(t0,t1);
    if ( trim_interval.IsDecreasing() )
      trim_interval.Swap();
    if ( !c3->Trim(trim_interval) )
    {
      delete c3;
      return 0;
    }
    if ( t0 > t1 )
      c3->Reverse();
    c3->SetDomain(trim_interval);
  }
  return c3;
}


static
bool ChangeTrimSingToBdry( ON_Brep& brep, ON_BrepTrim& trim, ON_BrepTrim* nexttrim )
{
  if ( trim.m_vi[0] != trim.m_vi[1] )
    return false;
  if ( trim.m_type != ON_BrepTrim::singular )
    return false;
  if ( trim.m_ei >= 0 )
    return false;

  const ON_Surface* srf = trim.SurfaceOf();
  if ( 0 == srf )
    return false;

  brep.m_V.Reserve( brep.m_V.Count() + 1 );
  ON_BrepVertex* v0 = brep.Vertex(trim.m_vi[0]);
  if ( 0 == v0 )
    return false;

  // get new 3d curve
  ON_Curve* c3 = PushUpIsoTrim( brep, trim );
  if ( 0 == c3 )
    return false;

  // valid singular trim can be changed to non-singular trim


  // create new vertex for end of this trim
  v0->m_tolerance = ON_UNSET_VALUE;

  ON_BrepVertex* v1 = 0;

  if ( c3->IsClosed() )
  {
    // 3d edge is closed so start and end vertex are still the same.
    v1 = v0;
  }
  else
  {
    // new 3d edge is not closed, so the single singular vertex
    // needs to be "split" into two vertices.
    brep.NewVertex();
    v1 = brep.m_V.Last();
  }
  trim.m_vi[1] = v1->m_vertex_index;

  // update the start of the next trim to use new vertex
  if ( nexttrim && nexttrim->m_trim_index != trim.m_trim_index )
  {
    ChangeTrimVertex( brep, *nexttrim, 0, v0->m_vertex_index, v1->m_vertex_index, true, true );
  }              

  // make a new edge
  int ci = brep.AddEdgeCurve(c3);
  c3 = 0;
  ON_BrepEdge& edge = brep.NewEdge(*v0,*v1,ci);
  edge.m_tolerance = 0.0;

  // hook trim to new edge
  trim.m_type = ON_BrepTrim::boundary;
  trim.m_bRev3d = false;
  trim.m_ei = edge.m_edge_index;
  edge.m_ti.Append(trim.m_trim_index);

  return true;
}

static
bool ChangeTrimBdryToSing( ON_Brep& brep, ON_BrepTrim& trim, 
                           ON_BrepTrim* prevtrim, ON_BrepTrim* nexttrim )
{
  if ( trim.m_vi[0] == trim.m_vi[1] )
    return false;
  if ( trim.m_type == ON_BrepTrim::singular )
    return false;
  if ( trim.m_ei < 0 )
    return false;

  int vi0 = trim.m_vi[0];
  int vi1 = trim.m_vi[1];

  int sing_vi = vi0;

  ON_BrepVertex* v0 = brep.Vertex(vi0);
  if ( v0 )
    v0->m_tolerance = ON_UNSET_VALUE;
  ON_BrepVertex* v1 = brep.Vertex(vi1);
  if ( v1 )
    v1->m_tolerance = ON_UNSET_VALUE;

  ON_BrepEdge* edge = brep.Edge(trim.m_ei);
  if ( edge )
  {
    for ( int eti = 0; eti < edge->m_ti.Count(); eti++ )
    {
      if ( edge->m_ti[eti] == trim.m_trim_index )
      {
        edge->m_ti.Remove(eti);
        break;
      }
    }

    trim.m_ei = -1;
    if ( 0 == edge->m_ti.Count() )
    {
      brep.DeleteEdge( *edge, true );
    }
    else if ( 1 == edge->m_ti.Count() && ON_BrepTrim::seam == trim.m_type )
    {
      // change neighbor trim type
      ON_BrepTrim* other_trim = brep.Trim(edge->m_ti[0]);
      if ( 0 != other_trim && ON_BrepTrim::seam == other_trim->m_type )
      {
        other_trim->m_type = ON_BrepTrim::boundary;
        int j = (trim.m_bRev3d == other_trim->m_bRev3d) ? 0 : 1;
        if (    trim.m_vi[0] == other_trim->m_vi[j] 
             && trim.m_vi[1] == other_trim->m_vi[1-j] )
        {
          // we need a new singular vertex
          sing_vi = brep.NewVertex(ON_UNSET_POINT).m_vertex_index;
        }
      }
    }
  }

  trim.m_vi[0] = sing_vi;
  trim.m_vi[1] = sing_vi;
  trim.m_type = ON_BrepTrim::singular;
  trim.m_bRev3d = false;

  if ( nexttrim )
    ChangeTrimVertex( brep,*nexttrim,0,vi1,sing_vi,true,true);
  if ( prevtrim )
    ChangeTrimVertex( brep,*prevtrim,1,vi0,sing_vi,true,true);

  return true;
}

static
bool SplitSeam( ON_Brep& brep, 
                ON_BrepTrim& trimA, ON_BrepTrim& trimB,
                ON_BrepTrim& prevtrimB,
                ON_BrepTrim& nexttrimB,
                int vcount0 // number of verts before singular fixups
                )
{
  if ( trimA.m_trim_index == trimB.m_trim_index )
    return false;
  if ( trimA.m_trim_index == prevtrimB.m_trim_index )
    return false;
  if ( trimA.m_trim_index == nexttrimB.m_trim_index )
    return false;
  if ( trimB.m_trim_index == prevtrimB.m_trim_index )
    return false;
  if ( trimB.m_trim_index == nexttrimB.m_trim_index )
    return false;
  if ( prevtrimB.m_trim_index == nexttrimB.m_trim_index )
    return false;
  if ( trimA.m_type != ON_BrepTrim::seam )
    return false;
  if ( trimB.m_type != ON_BrepTrim::seam )
    return false;
  if ( trimA.m_ei != trimB.m_ei )
    return false;
  if (    trimA.m_vi[0] != trimB.m_vi[1] 
       && trimA.m_vi[0] < vcount0
       && trimB.m_vi[1] < vcount0 )
    return false;
  if (    trimA.m_vi[1] != trimB.m_vi[0] 
       && trimA.m_vi[1] < vcount0
       && trimB.m_vi[0] < vcount0 )
    return false;
  if ( prevtrimB.m_vi[1] != trimB.m_vi[0] 
       && prevtrimB.m_vi[1] < vcount0
       && trimB.m_vi[0] < vcount0 )
    return false;
  if ( nexttrimB.m_vi[0] != trimB.m_vi[1]
       && prevtrimB.m_vi[0] < vcount0
       && trimB.m_vi[1] < vcount0 )
    return false;
  if ( trimA.m_li != trimB.m_li )
    return false;
  if ( trimA.m_li != prevtrimB.m_li )
    return false;
  if ( trimA.m_li != nexttrimB.m_li )
    return false;
  if ( trimA.m_bRev3d == trimB.m_bRev3d )
    return false;
  const ON_Surface* srf = trimA.SurfaceOf();
  if ( 0 == srf )
    return false;
  ON_BrepEdge* edgeA = brep.Edge(trimA.m_ei);
  if ( 0 == edgeA )
    return false;
  if ( edgeA->m_ti.Count() != 2 )
    return false;
  if ( edgeA->m_ti[0] != trimA.m_trim_index && edgeA->m_ti[1] != trimA.m_trim_index )
    return false;
  if ( edgeA->m_ti[0] != trimB.m_trim_index && edgeA->m_ti[1] != trimB.m_trim_index )
    return false;

  // reserve space now so the vA0 and vA1 pointers
  // will be valid if m_V[] is grown.
  brep.m_V.Reserve( brep.m_V.Count()+2 );

  ON_BrepVertex* vA0 = brep.Vertex(trimA.m_vi[0]);
  if ( 0 == vA0 )
    return false;
  ON_BrepVertex* vA1 = brep.Vertex(trimA.m_vi[1]);
  if ( 0 == vA1 )
    return false;

  // looks like we have a valid seam to blow apart

  // get a new 3d curve for trimB
  ON_Curve* cB3 = PushUpIsoTrim( brep, trimB );
  if ( 0 == cB3 )
    return false;
  int c3i = brep.AddEdgeCurve(cB3);

  vA0->m_tolerance = ON_UNSET_VALUE;
  vA1->m_tolerance = ON_UNSET_VALUE;

  // make new vertices for trimB
  ON_BrepVertex* vB0 = 0;
  ON_BrepVertex* vB1 = 0;

  ON_3dPoint PA, PB;
  bool bSame = false;

  if (brep.GetTrim3dStart(trimB.m_trim_index, PB) && brep.GetTrim3dEnd(trimA.m_trim_index, PA))
    bSame = PB.DistanceTo(PA) < ON_ZERO_TOLERANCE;
  if (bSame || trimB.m_vi[0] != trimA.m_vi[1] )
  {
    // sing fixups have already blown apart this end
    vB0 = brep.Vertex( trimB.m_vi[0] );
  }

  bSame = false;
  if (brep.GetTrim3dStart(trimA.m_trim_index, PA) && brep.GetTrim3dEnd(trimB.m_trim_index, PB))
    bSame = PB.DistanceTo(PA) < ON_ZERO_TOLERANCE;
  if (bSame || trimB.m_vi[1] != trimA.m_vi[0] )
  {
    // sing fixups have already blown apart this end
    vB1 = brep.Vertex( trimB.m_vi[1] );
  }
  if ( 0 == vB0 )
  {
    ON_BrepVertex& v = brep.NewVertex();
    vB0 = &v;
    trimB.m_vi[0] = vB0->m_vertex_index;
  }
  if ( 0 == vB1 )
  {
    ON_BrepVertex& v = brep.NewVertex();
    vB1 = &v;
    trimB.m_vi[1] = vB1->m_vertex_index;
  }

  // disconnect edgeA and trimB
  trimB.m_ei = -1;
  if ( edgeA->m_ti[0] == trimB.m_trim_index )
    edgeA->m_ti.Remove(0);
  else if ( edgeA->m_ti[1] == trimB.m_trim_index )
    edgeA->m_ti.Remove(1);
  ChangeTrimVertex( brep, trimB, 0, vA1->m_vertex_index, vB0->m_vertex_index, true, true );
  ChangeTrimVertex( brep, trimB, 1, vA0->m_vertex_index, vB1->m_vertex_index, true, true );

  ChangeTrimVertex( brep, prevtrimB, 1, vA1->m_vertex_index, vB0->m_vertex_index, true, true );
  ChangeTrimVertex( brep, nexttrimB, 0, vA0->m_vertex_index, vB1->m_vertex_index, true, true );

  // make a new edgeB and connect it to trimB
  ON_BrepEdge& edgeB = brep.NewEdge( *vB0, *vB1, c3i );
  edgeA = 0; // pointer may be invalid after m_E[] grows

  edgeB.m_ti.Append(trimB.m_trim_index);
  trimB.m_ei = edgeB.m_edge_index;
  trimB.m_bRev3d = false;

  trimA.m_type = ON_BrepTrim::boundary;
  trimB.m_type = ON_BrepTrim::boundary;

  return true;
}

static bool RebuildVertexToTrimEnd(ON_BrepTrim& T, int end)

{
  ON_Brep* pB = T.Brep();
  if (!pB) return false;
  int vid = T.m_vi[end];
  if (vid < 0) return false;
  ON_BrepVertex& V = pB->m_V[vid];
  ON_3dPoint P;
  if (end){
    if (!pB->GetTrim3dEnd(T.m_trim_index, P))
      return false;
  }
  else {
    if (!pB->GetTrim3dStart(T.m_trim_index, P))
      return false;
  }

  V.SetPoint(P);

  return true;

}


static bool SealSeam(int closed_dir, ON_BrepFace& F)

{
  if (closed_dir) closed_dir = 1;
  int seam_dir = 1-closed_dir;
  ON_Brep* pBrep = F.Brep();
  if (!pBrep) return false;
  const ON_Surface* pSrf = F.SurfaceOf();
  if (!pSrf || !pSrf->IsClosed(closed_dir)) return false;

  ON_Surface::ISO isoA = ON_Surface::not_iso;//same dir as isocurve
  ON_Surface::ISO isoB = ON_Surface::not_iso;//opposite dir as isocurve
  if (closed_dir){
    isoA = ON_Surface::S_iso;
    isoB = ON_Surface::N_iso;
  }
  else {
    isoA = ON_Surface::E_iso;
    isoB = ON_Surface::W_iso;
  }

  /* TODO: Handle cases where there is more than one trim on a seam side 
     or seam edges do not fully overlap.
  */

  //Look for a single pair of trims that match across parameter space.

  int A_id = -1;
  int B_id = -1;

  int li;
  for (li=0; li<F.m_li.Count(); li++){
    const ON_BrepLoop* L = F.Loop(li);
    if (!L || L->m_type !=  ON_BrepLoop::outer) continue;
    int lti;
    for (lti = 0; lti<L->m_ti.Count(); lti++ ){
      ON_BrepTrim* T = L->Trim(lti);
      if (!T) continue;
      if (T->m_iso == isoA) {
        if (A_id >= 0)
          return false;
        A_id = T->m_trim_index;
      }
      else if (T->m_iso == isoB) {
        if (B_id >= 0)
          return false;
        B_id = T->m_trim_index;
      }
    }
  }

  if (A_id < 0 || B_id < 0)
    return true;//no seam to join

  ON_BrepTrim& TA = pBrep->m_T[A_id];
  ON_BrepTrim& TB = pBrep->m_T[B_id];

  ON_BrepEdge* pEA = TA.Edge();
  ON_BrepEdge* pEB = TB.Edge();
  if (!pEA || !pEB)
    return false;

  ON_Interval a,b;
  int i;
  for (i=0; i<2; i++){
    a[i] = TA.PointAt(TA.Domain()[i])[seam_dir];
    b[i] = TB.PointAt(TB.Domain()[i])[seam_dir];
  }

  a.MakeIncreasing();
  b.MakeIncreasing();

  if (a[0] >= b[1] || b[0] >= a[1])
    return true; //nothing to be joined;

  double pspace_tol = 1.0e-8;

  if (a.Length() < 10.0*pspace_tol)
    return false;
  if (fabs(a[0] - b[0]) > pspace_tol || fabs(a[1] - b[1]) > pspace_tol)
    return false;

  //fix vertices so join will work.

  RebuildVertexToTrimEnd(TA, 0);
  RebuildVertexToTrimEnd(TA, 1);
  RebuildVertexToTrimEnd(TB, 0);
  RebuildVertexToTrimEnd(TB, 1);

  double join_tol = 1.0e-6;
  if (!pBrep->JoinEdges(*pEA, *pEB, join_tol))
    return false;

  TA.m_type = ON_BrepTrim::seam;
  TB.m_type = ON_BrepTrim::seam;

  return true;
}

bool ON_BrepFace::ChangeSurface(
  int si
  )
{
  if ( 0 == m_brep )
    return false;
  if ( si < 0 || si >= m_brep->m_S.Count() )
    return false;
  const ON_Surface* pSurface = m_brep->m_S[si];
  
  m_brep->DestroyMesh( ON::any_mesh );

  const ON_Surface* old_srf = SurfaceOf();
  m_si = si;
  SetProxySurface(pSurface);
  if ( pSurface )
    m_bbox = pSurface->BoundingBox();
  else
    m_bbox.Destroy();
  m_brep->m_bbox.Destroy();

  if ( old_srf && pSurface )
  {
    // If domain changed, tehn update 2d trim curve locations
    ON_Interval udom0 = old_srf->Domain(0);
    ON_Interval vdom0 = old_srf->Domain(1);
    ON_Interval udom1 = pSurface->Domain(0);
    ON_Interval vdom1 = pSurface->Domain(1);
    if ( udom0 != udom1 || vdom0 != vdom1 )
    {
      // need to transform trimming curves
      ON_Xform x(1), xu(1), xv(1);
      if ( udom0 != udom1 )
        xu.IntervalChange(0,udom0,udom1);
      if ( vdom0 != vdom1 )
        xv.IntervalChange(1,vdom0,vdom1);
      x = xv*xu;
      TransformTrim(x);
    }

    int vcount0 = m_brep->m_V.Count();

    // If singular points changed, then add/remove edges
    // and update trim.m_type flags
    int i;
    {
      bool bSing0[4];
      bool bSing1[4];
      for ( i = 0; i < 4; i++ )
      {
        bSing0[i] = old_srf->IsSingular(i) ? true : false;
        bSing1[i] = pSurface->IsSingular(i) ? true : false;
      }
      int sing_fix, sing_fix_max = 1;
      for ( sing_fix = 0; sing_fix < sing_fix_max; sing_fix++ )
      {
        // sing_fix:
        //   0: expands old singularities and checks for new ones
        //   1: collapses old edges to new singular points.
        for ( i = 0; i < 4; i++ )
        {
          if ( bSing0[i] == bSing1[i] )
            continue;

          ON_Surface::ISO iso = ON_Surface::not_iso;
          switch(i)
          {
          case 0: iso = ON_Surface::S_iso; break;
          case 1: iso = ON_Surface::E_iso; break;
          case 2: iso = ON_Surface::N_iso; break;
          case 3: iso = ON_Surface::W_iso; break;
          }

          if ( bSing0[i] && sing_fix != 0 )
          {
            // we already expanded old singular trims into edge trims
            continue;
          }

          for ( int fli = 0; fli < m_li.Count(); fli++ )
          {
            const ON_BrepLoop* loop = Loop(fli);
            if ( 0 == loop )
              continue;
            if ( loop->m_type != ON_BrepLoop::outer )
              continue;
            for ( int lti = 0; lti < loop->m_ti.Count(); lti++ )
            {
              ON_BrepTrim* trim = loop->Trim(lti);
              if ( !trim )
                continue;
              if ( trim->m_iso != iso )
                continue;
              ON_BrepTrim* nexttrim = loop->Trim((lti+1)%loop->m_ti.Count());
              if ( bSing0[i] )
              {
                // valid singular trim changing to non-singular trim
                if( 0 == sing_fix )
                  ChangeTrimSingToBdry( *m_brep, *trim, nexttrim );
              }
              else if ( bSing1[i] )
              {
                if ( 0 == sing_fix )
                {
                  // we need a 2nd pass to collapse this edge
                  // to a singular trim.
                  sing_fix_max = 2;
                }
                else
                {
                  // valid non-singular trim changing to singular trim
                  ON_BrepTrim* prevtrim = loop->Trim((lti-1+loop->m_ti.Count())%loop->m_ti.Count());
                  ChangeTrimBdryToSing( *m_brep, *trim, prevtrim, nexttrim );
                }
              }
            }
          }
        }
      }
    }

    // If closed/open status changed, then add/remove edges
    // and update m_type flag
    for ( i = 0; i < 2; i++ )
    {
      bool bClosed0 = old_srf->IsClosed(i) ? true : false;
      bool bClosed1 = pSurface->IsClosed(i) ? true : false;
      if ( bClosed0 == bClosed1 )
        continue;
      ON_Surface::ISO isoA = ON_Surface::not_iso;
      ON_Surface::ISO isoB = ON_Surface::not_iso;
      switch(i)
      {
      case 0: isoA = ON_Surface::W_iso; isoB = ON_Surface::E_iso; break;
      case 1: isoA = ON_Surface::S_iso; isoB = ON_Surface::N_iso; break;
      }

      for ( int fli = 0; fli < m_li.Count(); fli++ )
      {
        const ON_BrepLoop* loop = Loop(fli);
        if ( 0 == loop )
          continue;
        if ( loop->m_type != ON_BrepLoop::outer )
          continue;
        int loop_trim_count = loop->m_ti.Count();
        for ( int ltiA = 0; ltiA < loop_trim_count; ltiA++ )
        {
          ON_BrepTrim* trimA = loop->Trim(ltiA);
          if ( !trimA )
            continue;
          if ( trimA->m_iso != isoA )
            continue;

          if ( bClosed0 )
          {
            // old surface has a seam and new surface does not
            if ( trimA->m_type != ON_BrepTrim::seam )
              continue;
            const ON_BrepEdge* edge = m_brep->Edge(trimA->m_ei);
            if ( 0 == edge )
              continue;
            if ( edge->m_ti.Count() != 2 )
              continue;
            int etiB = (edge->m_ti[0] == trimA->m_trim_index) ? 1 : 0;
            ON_BrepTrim* trimB = edge->Trim(etiB);
            if ( 0 == trimB )
              continue;
            if ( trimA == trimB )
              continue;
            if ( trimB->m_li != trimA->m_li )
              continue;
            if ( trimB->m_type != ON_BrepTrim::seam )
              continue;
            if ( trimB->m_iso != isoB )
              continue;
            for ( int ltiB = 0; ltiB < loop_trim_count; ltiB++ )
            {
              if ( trimB != loop->Trim(ltiB) )
                continue;
              ON_BrepTrim* prevtrimB = loop->Trim((ltiB+loop_trim_count-1)%loop_trim_count);
              ON_BrepTrim* nexttrimB = loop->Trim((ltiB+1)%loop_trim_count);
              if ( 0 == prevtrimB )
                continue;
              if ( 0 == nexttrimB )
                continue;
              if ( prevtrimB == trimA || prevtrimB == trimB )
                continue;
              if ( nexttrimB == trimA || nexttrimB == trimB )
                continue;
              if ( prevtrimB == nexttrimB )
                continue;
              SplitSeam( *m_brep, *trimA, *trimB, *prevtrimB, *nexttrimB, vcount0 );
              break;
            }
          }
          else
          {
            // open sides replaced with a seam
            // TODO
            bool sok;
            sok = SealSeam(i, *this);
            if (sok)
              sok = !sok;
          }
        }
      }
    }
  }

  if ( pSurface )
  {
    for ( int fli = 0; fli < m_li.Count(); fli++ )
    {
      const ON_BrepLoop* loop = Loop(fli);
      if ( 0 == loop )
        continue;
      for ( int lti = 0; lti < loop->m_ti.Count(); lti++ )
      {
        const ON_BrepTrim* trim = loop->Trim(lti);
        if ( 0 ==  trim )
          continue;
        ON_BrepVertex* v0 = m_brep->Vertex(trim->m_vi[0]);
        if ( 0 != v0 )
        {
          if ( v0->point == ON_UNSET_POINT )
          {
            ON_3dPoint uv = trim->PointAtStart();
            v0->point = pSurface->PointAt( uv.x, uv.y );
          }
        }
      }
    }
  }

  return true;
}

//bool ON_Brep::ReplaceSurface( ON_BrepFace& face, 
//                     ON_Surface* pSurface
//                     )
//{
//  bool rc = false;
//  if ( pSurface )
//  {
//    int si = AddSurface(pSurface);
//    rc = face.ChangeSurface(si);
//  }
//  return rc;
//}

