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




static
const ON_BrepEdge* FindLinearEdge( const ON_Brep& brep, int vi0, int vi1 )
{
  // searchs for a linear edge connecting the vertices
  // brep.m_V[vi0] and brep.m_V[vi1].
  if ( vi0 < 0 || vi0 >= brep.m_V.Count() )
    return nullptr;
  if ( vi1 < 0 || vi1 >= brep.m_V.Count() )
    return nullptr;
  if ( vi0 == vi1 )
    return nullptr;
  const ON_BrepVertex& v0 = brep.m_V[vi0];
  //const ON_BrepVertex& v1 = brep.m_V[vi1];
  int vei;
  for ( vei = 0; vei < v0.m_ei.Count(); vei++ )
  {
    const ON_BrepEdge* edge = brep.Edge( v0.m_ei[vei] );
    if ( !edge )
      continue;
    if ( edge->m_vi[0] != vi0 && edge->m_vi[1] != vi0 )
      continue;
    if ( edge->m_vi[0] != vi1 && edge->m_vi[1] != vi1 )
      continue;
    if ( !edge->IsLinear() )
      continue;
    return edge;
  }
  return nullptr;
}

static
void SynchFaceOrientation( ON_Brep& brep, int fi )
{
  const ON_BrepFace* face = brep.Face(fi);
  if ( face )
  {
    int flip = -1, fli, lti;
    for ( fli = 0; fli < face->m_li.Count(); fli++ )
    {
      const ON_BrepLoop* loop = brep.Loop( face->m_li[fli] );
      if ( !loop )
        continue;
      for ( lti = 0; lti < loop->m_ti.Count(); lti++ )
      {
        const ON_BrepTrim* trim = brep.Trim( loop->m_ti[lti] );
        if ( !trim )
          continue;
        const ON_BrepEdge* edge = brep.Edge( trim->m_ei );
        if ( !edge )
          continue;
        if ( edge->m_ti.Count() != 2 )
          continue;
        const ON_BrepTrim* trim0 = brep.Trim( edge->m_ti[0] );
        const ON_BrepTrim* trim1 = brep.Trim( edge->m_ti[1] );
        if ( !trim0 || !trim1 )
          continue;
        bool bRev0 = trim0->m_bRev3d ? true : false;
        bool bRev1 = trim1->m_bRev3d ? true : false;
        if ( bRev0 == bRev1 )
        {
          if ( flip == -1 )
            flip = 1;
          else if (flip != 1 )
            return;
        }
        else
        {
          if ( flip == -1 )
            flip = 0;
          else if (flip != 0 )
            return;
        }
      }
    }
    if ( flip == 1 )
      brep.FlipFace(brep.m_F[fi]);
  }
}

ON_BrepFace* ON_Brep::NewRuledFace(
      const ON_BrepEdge& edgeA,
      bool bRevEdgeA,
      const ON_BrepEdge& edgeB, 
      bool bRevEdgeB
      )
{
  if ( edgeA.m_edge_index == edgeB.m_edge_index )
    return nullptr;
  if ( Edge( edgeA.m_edge_index) != &edgeA )
    return nullptr;
  if ( Edge( edgeB.m_edge_index) != &edgeB )
    return nullptr;

  ON_NurbsCurve cA, cB;
  if ( !edgeA.GetNurbForm( cA ) )
    return nullptr;
  if ( bRevEdgeA )
    cA.Reverse();
  if ( !edgeB.GetNurbForm( cB ) )
    return nullptr;
  if ( bRevEdgeB )
    cB.Reverse();
  ON_NurbsSurface* srf = ON_NurbsSurface::New();
  if ( !srf->CreateRuledSurface( cA, cB ) )
  {
    delete srf;
    return nullptr;
  }

  // corner vertices (sw,se,ne,nw)
  int vid[4] = {-1,-1,-1,-1};
  vid[0] = edgeA.m_vi[bRevEdgeA?1:0];
  vid[1] = edgeA.m_vi[bRevEdgeA?0:1];
  vid[2] = edgeB.m_vi[bRevEdgeB?0:1];
  vid[3] = edgeB.m_vi[bRevEdgeB?1:0];

  if ( vid[1] == vid[2] )
  {
    // make sure surface has a singular east side
    srf->CollapseSide( 1 );
  }

  if ( vid[1] == vid[2] )
  {
    // make sure surface has a singular west side
    srf->CollapseSide( 3 );
  }

  // side edges (s,e,n,w)
  int eid[4] = {-1,-1,-1,-1};
  bool bRev3d[4] = {false,false,false,false};
  
  // south side
  eid[0] = edgeA.m_edge_index;
  bRev3d[0] = bRevEdgeA;
  
  // east side
  const ON_BrepEdge* east_edge = FindLinearEdge( *this, vid[1], vid[2] );
  if ( east_edge )
  {
    eid[1] = east_edge->m_edge_index;
    bRev3d[1] = (east_edge->m_vi[0] == vid[2]);
  }

  // north side
  eid[2] = edgeB.m_edge_index;
  bRev3d[2] = !bRevEdgeB;

  // west side
  const ON_BrepEdge* west_edge = FindLinearEdge( *this, vid[3], vid[0] );
  if ( west_edge )
  {
    eid[3] = west_edge->m_edge_index;
    bRev3d[3] = (west_edge->m_vi[0] == vid[0]);
  }

  ON_BrepFace* face = NewFace( srf, vid, eid, bRev3d );
  if ( face )
    SynchFaceOrientation( *this, face->m_face_index );
  return face;
}


ON_BrepFace* ON_Brep::NewConeFace(
      const ON_BrepVertex& vertex,
      const ON_BrepEdge& edge,
      bool bRevEdge
      )
{
  if ( Edge( edge.m_edge_index) != &edge )
    return nullptr;
  if ( Vertex( vertex.m_vertex_index) != &vertex )
    return nullptr;
  if ( edge.m_vi[0] == vertex.m_vertex_index )
    return nullptr;
  if ( edge.m_vi[1] == vertex.m_vertex_index )
    return nullptr;
  ON_NurbsCurve c;
  if ( !edge.GetNurbForm( c ) )
    return nullptr;
  if ( bRevEdge )
    c.Reverse();
  ON_NurbsSurface* srf = ON_NurbsSurface::New();
  if ( !srf->CreateConeSurface( vertex.point, c ) )
  {
    delete srf;
    return nullptr;
  }

  // corner vertices (sw,se,ne,nw)
  int vid[4] = {-1,-1,-1,-1};
  vid[0] = edge.m_vi[bRevEdge?1:0];
  vid[1] = edge.m_vi[bRevEdge?0:1];
  vid[2] = vertex.m_vertex_index;
  vid[3] = vertex.m_vertex_index;

  // side edges (s,e,n,w)
  int eid[4] = {-1,-1,-1,-1};
  bool bRev3d[4] = {false,false,false,false};
  
  // south side
  eid[0] = edge.m_edge_index;
  bRev3d[0] = bRevEdge;
  
  // east side
  const ON_BrepEdge* east_edge = FindLinearEdge( *this, vid[1], vid[2] );
  if ( east_edge )
  {
    eid[1] = east_edge->m_edge_index;
    bRev3d[1] = (east_edge->m_vi[0] == vid[2]);
  }

  // west side
  const ON_BrepEdge* west_edge = FindLinearEdge( *this, vid[3], vid[0] );
  if ( west_edge )
  {
    eid[3] = west_edge->m_edge_index;
    bRev3d[3] = (west_edge->m_vi[0] == vid[0]);
  }

  ON_BrepFace* face = NewFace( srf, vid, eid, bRev3d );
  if ( face )
    SynchFaceOrientation( *this, face->m_face_index );
  return face;
}

bool ON_Brep::SetTrimBoundingBoxes( bool bLazy )
{
  bool rc = true;
  int fi, face_count = m_F.Count();
  for ( fi = 0; fi < face_count; fi++ )
  {
    if ( !SetTrimBoundingBoxes( m_F[fi], bLazy ) )
      rc = false;
  }
  return rc;
}

bool ON_Brep::SetTrimBoundingBoxes( ON_BrepFace& face, bool bLazy )
{
  bool rc = true;
  int li, fli, loop_count = m_L.Count(), fl_count = face.m_li.Count();
  for ( fli = 0; fli < fl_count; fli++ )
  {
    li = face.m_li[fli];
    if ( li >= 0 && li < loop_count )
    {
      if ( !SetTrimBoundingBoxes( m_L[li], bLazy ) )
        rc = false;
    }
  }
  return rc;
}

bool ON_Brep::SetTrimBoundingBoxes( ON_BrepLoop& loop, bool bLazy )
{
  // TL_Brep overrides this function and computes much tighter
  // bounding boxes that take trim.m_t[] into account.
  bool rc = true;
  int ti, lti, trim_count = m_T.Count(), lt_count = loop.m_ti.Count();
  bool bSetLoopBox = true;
  if ( bLazy && loop.m_pbox.IsValid() )
    bSetLoopBox = false;
  else
    loop.m_pbox.Destroy();
  for ( lti = 0; lti < lt_count; lti++ )
  {
    ti = loop.m_ti[lti];
    if ( ti >= 0 && ti < trim_count )
    {
      if ( !SetTrimBoundingBox( m_T[ti], bLazy ) )
        rc = false;
      else if ( bSetLoopBox )
        loop.m_pbox.Union( m_T[ti].m_pbox );
    }
  }
  return (rc && loop.m_pbox.IsValid()) ? true : false;
}

bool ON_Brep::SetTrimBoundingBox( ON_BrepTrim& trim, bool bLazy )
{
  // TL_Brep overrides this function and computes much 
  // tighter bounding boxes that take trim.m_t[] into account.
  bool rc = true;
  if ( !trim.m_pbox.IsValid() || !bLazy )
  {
    trim.m_pbox.Destroy();
    if ( trim.ProxyCurve() )
    {
      trim.m_pbox = trim.BoundingBox();
      trim.m_pbox.m_min.z = 0.0;
      trim.m_pbox.m_max.z = 0.0;
    }
  }
  return (rc && trim.m_pbox.IsValid()) ? true : false;
}

void ON_Brep::SetTolerancesBoxesAndFlags(
     bool bLazy,
     bool bSetVertexTolerances,
     bool bSetEdgeTolerances,
     bool bSetTrimTolerances,
     bool bSetTrimIsoFlags,
     bool bSetTrimTypeFlags,
     bool bSetLoopTypeFlags,
     bool bSetTrimBoxes
     )
{
  int ei, ti, li;
  const int trim_count = m_T.Count();
  const int loop_count = m_L.Count();
  const int edge_count = m_E.Count();
  if ( bSetVertexTolerances )
    SetVertexTolerances(bLazy);
  if ( bSetEdgeTolerances )
  {
    for ( ei = 0; ei < edge_count; ei++ )
      SetEdgeTolerance(m_E[ei],bLazy);
  }
  if ( bSetTrimTolerances )
  {
    for ( ti = 0; ti < trim_count; ti++ )
      SetTrimTolerance(m_T[ti],bLazy);
  }
  if ( bSetTrimIsoFlags )
    SetTrimIsoFlags();
  if ( bSetTrimTypeFlags )
    SetTrimTypeFlags(bLazy);
  if ( bSetTrimTypeFlags )
    SetTrimTypeFlags(bLazy);
  if ( bSetLoopTypeFlags )
  {
    for ( li = 0; li < loop_count; li++ )
    {
      ON_BrepLoop& loop = m_L[li];
      if ( loop.m_type == ON_BrepLoop::unknown || !bLazy )
      {
        loop.m_type = ComputeLoopType( loop );
      }
    }
  }
  if ( bSetTrimBoxes )
    SetTrimBoundingBoxes(bLazy);
}

static
bool CheckForMatchingVertexIndices( int i, int j, int corner_vi[4] )
{
  if (corner_vi[i] == corner_vi[j])
    return true;

  bool rc = false;
  if ( corner_vi[i] >= 0 || corner_vi[j] >= 0 )
  {
    if ( corner_vi[i] == -1 )
    {
      corner_vi[i] = corner_vi[j];
      rc = true;
    }
    else if ( corner_vi[j] == -1 )
    {
      corner_vi[j] = corner_vi[i];
      rc = true;
    }
  }

  return rc;
}


ON_BrepFace* ON_Brep::NewFace(
       ON_Surface* pSurface,
       int vid[4],
       int eid[4],
       bool bRev3d[4]
       )
{
  m_bbox.Destroy();
  m_is_solid = 0;
  bool bAddedSurface = false;
  ON_BrepFace* pFace = nullptr;
  if ( !pSurface )
    return nullptr;
  int si;
  for ( si = 0; si < m_S.Count(); si++ )
  {
    if ( pSurface == m_S[si] )
      break;
  }
  if ( si >= m_S.Count() )
  {
    si = AddSurface(pSurface);
    bAddedSurface = (si >= 0);
  }
  int face_index = NewFace(si).m_face_index;
  if ( NewOuterLoop( face_index, vid, eid, bRev3d ) )
  {
    pFace = &m_F[face_index];
  }
  else 
  {
    // failed
    if ( bAddedSurface )
    {
      m_S[si] = 0;
      if ( m_S.Count() == si+1 )
        m_S.SetCount(si);
    }
    DeleteFace( m_F[face_index], false );
    if ( m_F.Count() == face_index+1 )
    {
      m_F.SetCount(face_index);
    }
  }
  return pFace;
}


ON_BrepLoop* ON_Brep::NewOuterLoop(
       int face_index,
       int vid[4],
       int eid[4],
       bool boolRev3d[4]
       )
{
  // 2 Sept 2020 S. Baer (RH-59952)
  // Destroy cached bounding box on breps when messing around with loops
  m_bbox.Destroy();
  m_is_solid = 0;
  if ( face_index < 0 || face_index >= m_F.Count() )
    return nullptr;
  ON_BrepFace& face = m_F[face_index];
  const ON_Surface* pSurface = face.SurfaceOf();
  if (!pSurface) 
    return nullptr;

  double u[2], v[2];
  if (!pSurface->GetDomain(0, &u[0], &u[1])) 
      return 0;
  if (!pSurface->GetDomain(1, &v[0], &v[1])) 
      return 0;

  ON_3dPoint srf_P[2][2];
  if ( !pSurface->EvPoint(u[0],v[0],srf_P[0][0] ) )
    return 0;
  if ( !pSurface->EvPoint(u[1],v[0],srf_P[1][0] ) )
    return 0;
  if ( !pSurface->EvPoint(u[0],v[1],srf_P[0][1] ) )
    return 0;
  if ( !pSurface->EvPoint(u[1],v[1],srf_P[1][1] ) )
    return 0;


  bool bIsSingular[4]; // south, east, north, west
  bool bIsClosed[2]; // u direction, v direction
  int i, eti;
  ON_Curve* c3[4] = {nullptr,nullptr,nullptr,nullptr};

  int bRev3d[4] = { 0 };
  for ( i = 0; i < 4; i++ )
  {
    if ( boolRev3d[i] )
      bRev3d[i] = 1; // do this so we can use 1-bRev3d[i] as an array index
  }

  // check specified edge indices
  for ( i = 0; i < 4; i++ )
  {
    if ( eid[i] != -1 )
    {
      if ( eid[i] < 0 || eid[i] >= m_E.Count() )
      {
        ON_ERROR("Bad edge index passed to ON_BrepNewFace.");
        return 0;
      }
      const int* edge_vi = m_E[eid[i]].m_vi;
      int vi0 = edge_vi[bRev3d[i]];
      int vi1 = edge_vi[1-bRev3d[i]];
      if ( vi0 < 0 || vi1 < 0 )
      {
        ON_ERROR("ON_Brep::NewFace(ON_Surface*,...) error: Bad edge vertex informtion.");
        return 0;
      }
      if ( vid[i] == -1 )
        vid[i] = vi0;
      else if ( vid[i] != vi0 )
      {
        ON_ERROR("ON_Brep::NewFace(ON_Surface*,...) error: Edge and vertex informtion do not match.");
        return 0;
      }
      if ( vid[(i+1)%4] == -1 )
        vid[(i+1)%4] = vi1;
      else if ( vid[(i+1)%4] != vi1 )
      {
        ON_ERROR("ON_Brep::NewFace(ON_Surface*,...) error: Edge and vertex informtion do not match.");
        return 0;
      }
    }
  }

  // check specified vertex indices
  for ( i = 0; i < 4; i++ )
  {
    if ( vid[i] != -1 )
    {
      if ( vid[i] < 0 || vid[i] >= m_V.Count() )
      {
        ON_ERROR("Bad vertex index passed to ON_Brep::NewFace.");
        return 0;
      }
    }
  }

  for ( i = 0; i < 4; i++ )
    bIsSingular[i] = pSurface->IsSingular(i);
  for ( i = 0; i < 2; i++ )
    bIsClosed[i] = pSurface->IsClosed(i);

  for (i = 0; i < 2; i++ )
  {
    if ( bIsClosed[i] )
    {
      int j = i?0:1;
      int k = j+2;
      if ( eid[j] == -1 && eid[k] != -1)
      {
        eid[j] = eid[k];
        bRev3d[j] = 1-bRev3d[k];
      }
      else if ( eid[k] == -1 && eid[j] != -1)
      {
        eid[k] = eid[j];
        bRev3d[k] = 1-bRev3d[j];
      }
      else if ( eid[k] != -1 || eid[j] != -1)
      {
        if ( eid[j] != eid[k] || bRev3d[j] != 1-bRev3d[k] )
        {
          ON_ERROR("Bad edge information passed to ON_Brep::NewFace.");
          return 0;
        }
      }
    }
  }  

  // if surface has singularities or is closed, make sure vertex and edge information is correct
  for ( i = 0; i < 4; i++ )
  {
    if ( bIsSingular[i] )
    {
      if ( eid[i] != -1 || bRev3d[i] )
      {
        ON_ERROR("Bad edge information passed to ON_Brep::NewFace.");
        return 0;
      }
    }
    if ( bIsSingular[i] || bIsClosed[i%2] )
    {
      if ( !CheckForMatchingVertexIndices(i,(i+1)%4,vid) )
      {
        ON_ERROR("Bad vertex indices passed to ON_Brep::NewFace.");
        return 0;
      }
    }
  }

  m_C3.Reserve( m_C3.Count() + 4 );
  // create missing 3d curves
  bool bEdgeIsClosed[4]; // true if 3d edge is closed or edge is singular.
  for ( i = 0; i < 4; i++ )
  {
    bEdgeIsClosed[i] = false;
    if ( eid[i] != -1 )
    {
      const ON_BrepEdge& edge = m_E[eid[i]];
      bEdgeIsClosed[i] = (edge.m_vi[0] == edge.m_vi[1]);
      continue;
    }
    if ( bIsSingular[i] )
    {
      bEdgeIsClosed[i] = true;
      continue;
    }
    if ( i >= 2 && bIsClosed[(i==2)?1:0] )
    {
      bEdgeIsClosed[i] = bEdgeIsClosed[i-2];
      continue;
    }
    switch(i)
    {
    case 0:  // south side
      c3[i] = pSurface->IsoCurve(i%2, v[0]); 
      break;
    case 1:  // east side
      c3[i] = pSurface->IsoCurve(i%2, u[1]); 
      break;
    case 2:  // north side
      c3[i] = pSurface->IsoCurve(i%2, v[1]); 
      break;
    case 3:  // west side
      c3[i] = pSurface->IsoCurve(i%2, u[0]); 
      break;
    }
    if ( !c3[i] )
    {
     ON_ERROR("ON_Brep::NewLoop unable to make 3d edge curve.");
      return 0;
    }
    if ( pSurface->IsClosed(i%2) )
      bEdgeIsClosed[i] = true;
    else
      bEdgeIsClosed[i] = c3[i]->IsClosed()?true:false;
    if ( (i <= 1 && bRev3d[i]) || (i >= 2 && !bRev3d[i]) )
    {
      c3[i]->Reverse();
    }
  }

  if ( m_V.Capacity() < 2 )
    m_V.Reserve(4);

  // create missing vertices
  if ( vid[0] == -1 )
  {
    if ( vid[1] >= 0 && bEdgeIsClosed[0] )
      vid[0] = vid[1];
    else if ( vid[3] >= 0 && bEdgeIsClosed[3] )
      vid[0] = vid[3];
    else
      vid[0] = NewVertex( srf_P[0][0],0.0).m_vertex_index;
  }

  if ( vid[1] == -1 )
  {
    if ( bEdgeIsClosed[0] ) 
      vid[1] = vid[0];
    else if ( vid[2] >= 0 && bEdgeIsClosed[1] ) 
      vid[1] = vid[2];
    else
      vid[1] = NewVertex(srf_P[1][0],0.0).m_vertex_index;
  }

  if ( vid[2] == -1 )
  {
    if ( bEdgeIsClosed[1] ) 
      vid[2] = vid[1];
    else if (vid[3] >= 0 && bEdgeIsClosed[2] ) 
      vid[2] = vid[3];
    else
      vid[2] = NewVertex( srf_P[1][1],0.0).m_vertex_index;
  }

  if ( vid[3] == -1 )
  {
    if ( bEdgeIsClosed[2] ) 
      vid[3] = vid[2];
    else if ( bEdgeIsClosed[3] ) 
      vid[3] = vid[0];
    else
      vid[3] = NewVertex( srf_P[0][1],0.0).m_vertex_index;
  }

  if ( m_E.Capacity() < 4 )
    m_E.Reserve(4);

  // create missing edges
  for ( i = 0; i < 4; i++ )
  {
    if ( c3[i] )
    {
      int i0, i1;
      if ( bRev3d[i] )
      {
        i0 = (i+1)%4;
        i1 = i;
      }
      else
      {
        i0 = i;
        i1 = (i+1)%4;
      }
      ON_BrepEdge& edge = NewEdge( m_V[vid[i0]], m_V[vid[i1]], AddEdgeCurve( c3[i] ) );
      edge.m_tolerance = 0.0;
      eid[i] = edge.m_edge_index;
      if ( i == 0 && bIsClosed[1] )
      {
        eid[2] = eid[0];
        bRev3d[2] = 1-bRev3d[0];
      }
      else if ( i == 1 && bIsClosed[0] )
      {
        eid[3] = eid[1];
        bRev3d[3] = 1-bRev3d[1];
      }
    }
  }

  m_T.Reserve( m_T.Count() + 4 );
  m_C2.Reserve( m_C2.Count() + 4 );

  ON_BrepLoop& loop = NewLoop( ON_BrepLoop::outer, face );

  loop.m_pbox.m_min.x = u[0];
  loop.m_pbox.m_min.y = v[0];
  loop.m_pbox.m_min.z = 0.0;

  loop.m_pbox.m_max.x = u[1];
  loop.m_pbox.m_max.y = v[1];
  loop.m_pbox.m_max.z = 0.0;

  ON_3dPoint corners[4];
  corners[0].Set(u[0],v[0],0.0);
  corners[1].Set(u[1],v[0],0.0);
  corners[2].Set(u[1],v[1],0.0);
  corners[3].Set(u[0],v[1],0.0);

  ON_Surface::ISO srf_iso[4] = {ON_Surface::S_iso,ON_Surface::E_iso,ON_Surface::N_iso,ON_Surface::W_iso};

  for ( i = 0; i < 4; i++ )
  {
    ON_NurbsCurve* c2 = new ON_NurbsCurve( 2, 0, 2, 2 );
    c2->SetCV(0,corners[i]);
    c2->SetCV(1,corners[(i+1)%4]);
    c2->m_knot[0] = 0.0;
    c2->m_knot[1] = 1.0;
    if ( i%2 )
      c2->SetDomain(v[0],v[1]);
    else
      c2->SetDomain(u[0],u[1]);
    int c2i = AddTrimCurve( c2 );
    if ( bIsSingular[i] )
      NewSingularTrim( m_V[vid[i]],loop,srf_iso[i],c2i);
    else
    {
      ON_BrepTrim& trim = NewTrim( m_E[eid[i]], bRev3d[i], loop, c2i);
      trim.m_iso = srf_iso[i];
      if ( bIsClosed[(i+1)%2] ) 
        trim.m_type = ON_BrepTrim::seam;
      else {
        trim.m_type = ON_BrepTrim::boundary;
        const ON_BrepEdge& edge = m_E[eid[i]];
        if ( edge.m_ti.Count() > 1 )
        {
          for ( eti = 0; eti < edge.m_ti.Count(); eti++ )
          {
            m_T[edge.m_ti[eti]].m_type = ON_BrepTrim::mated;
          }
        }
      }
      trim.m_tolerance[0] = 0.0;
      trim.m_tolerance[1] = 0.0;
      trim.m__legacy_2d_tol = 0.0;
      trim.m__legacy_3d_tol = 0.0;
      trim.m__legacy_flags_Set(-1,1);
    }
  }

  for ( i = 0; i < 4; i++ )
  {
    boolRev3d[i] = bRev3d[i] ? true : false;
  }

  return &m_L[loop.m_loop_index];
}




ON_Brep* ON_BrepBox( const ON_3dPoint* box_corners, ON_Brep* pBrep )
{
  ON_Brep* brep = 0;
  int vi, ei, fi, si, c2i;
  if (box_corners)
  {
    if ( pBrep ) {
      pBrep->Destroy();
      brep = pBrep;
    }
    else
      brep = new ON_Brep();
    brep->m_C2.Reserve(24);
    brep->m_C3.Reserve(12);
    brep->m_S.Reserve(6);
    brep->m_V.Reserve(8);
    brep->m_E.Reserve(12);
    brep->m_L.Reserve(6);
    brep->m_T.Reserve(24);
    brep->m_F.Reserve(6);
    for ( vi = 0; vi < 8; vi++ )
    {
      brep->NewVertex( box_corners[vi], 0.0 );
    }
    for ( ei = 0; ei < 4; ei++ )
    {
      ON_BrepVertex& v0 = brep->m_V[ei];
      ON_BrepVertex& v1 = brep->m_V[(ei+1)%4];
      brep->m_C3.Append( new ON_LineCurve( v0.point, v1.point ) );
      brep->NewEdge( v0, v1, ei, nullptr, 0.0 );
    }
    for ( ei = 4; ei < 8; ei++ )
    {
      ON_BrepVertex& v0 = brep->m_V[ei];
      ON_BrepVertex& v1 = brep->m_V[ei==7?4:(ei+1)];
      brep->m_C3.Append( new ON_LineCurve( v0.point, v1.point ) );
      brep->NewEdge( v0, v1, ei, nullptr, 0.0 );
    }
    for ( ei = 8; ei < 12; ei++ )
    {
      ON_BrepVertex& v0 = brep->m_V[ei-8];
      ON_BrepVertex& v1 = brep->m_V[ei-4];
      brep->m_C3.Append( new ON_LineCurve( v0.point, v1.point ) );
      brep->NewEdge( v0, v1, ei, nullptr, 0.0 );
    }

    /*
    //           v7_______e6_____v6
    //            |\             |\
    //            | e7           | e5
    //            |  \ ______e4_____\ 
    //           e11  v4         |   v5
    //            |   |        e10   |
    //            |   |          |   |
    //            3---|---e2-----2   e9
    //            \   e8         \   |
    //             e3 |           e1 |
    //              \ |            \ |
    //               \v0_____e0_____\v1
    */

    struct {
      int e[4], bRev[4];
    } f[6] = {
      {{0, 9, 4, 8},  {false, false, true,  true}},
      {{1,10, 5, 9},  {false, false, true,  true}},
      {{2,11, 6,10},  {false, false, true,  true}},
      {{3, 8, 7,11},  {false, false, true,  true}},
      {{3, 2, 1, 0},  {true,  true,  true,  true}},
      {{4, 5, 6, 7},  {false, false, false, false}}
    };
    for ( fi = 0; fi < 6; fi++ )
    {
      ON_BrepEdge& e0 = brep->m_E[f[fi].e[0]];
      ON_BrepEdge& e1 = brep->m_E[f[fi].e[1]];
      ON_BrepEdge& e2 = brep->m_E[f[fi].e[2]];
      ON_BrepEdge& e3 = brep->m_E[f[fi].e[3]];
      ON_BrepVertex& v0 = brep->m_V[e0.m_vi[f[fi].bRev[0]?1:0]];
      ON_BrepVertex& v1 = brep->m_V[e1.m_vi[f[fi].bRev[1]?1:0]];
      ON_BrepVertex& v2 = brep->m_V[e2.m_vi[f[fi].bRev[2]?1:0]];
      ON_BrepVertex& v3 = brep->m_V[e3.m_vi[f[fi].bRev[3]?1:0]];

      si = brep->AddSurface( ON_NurbsSurfaceQuadrilateral( v0.point, v1.point, v2.point, v3.point ) );
      ON_Interval s = brep->m_S[si]->Domain(0);
      ON_Interval t = brep->m_S[si]->Domain(1);
      ON_2dPoint p0(s[0],t[0]);
      ON_2dPoint p1(s[1],t[0]);
      ON_2dPoint p2(s[1],t[1]);
      ON_2dPoint p3(s[0],t[1]);

      ON_BrepFace& face = brep->NewFace( si );
      ON_BrepLoop& loop = brep->NewLoop( ON_BrepLoop::outer, face );

      loop.m_pbox.m_min.x = s[0];
      loop.m_pbox.m_min.y = t[0];
      loop.m_pbox.m_min.z = 0.0;

      loop.m_pbox.m_max.x = s[1];
      loop.m_pbox.m_max.y = t[1];
      loop.m_pbox.m_max.z = 0.0;

      // south side of surface
      c2i = brep->AddTrimCurve( new ON_LineCurve( p0, p1 ) );
      ON_BrepTrim& trim0 = brep->NewTrim( e0, f[fi].bRev[0], loop, c2i );
      trim0.m_tolerance[0] = 0.0;
      trim0.m_tolerance[1] = 0.0;
      trim0.m_type = (trim0.m_vi[0] != trim0.m_vi[1]) ? ON_BrepTrim::mated : ON_BrepTrim::singular;
      trim0.m_iso = ON_Surface::S_iso;

      // east side of surface
      c2i = brep->AddTrimCurve( new ON_LineCurve( p1, p2 ) );
      ON_BrepTrim& trim1 = brep->NewTrim( e1, f[fi].bRev[1], loop, c2i );
      trim1.m_tolerance[0] = 0.0;
      trim1.m_tolerance[1] = 0.0;
      trim1.m_type = (trim1.m_vi[0] != trim1.m_vi[1]) ? ON_BrepTrim::mated : ON_BrepTrim::singular;
      trim1.m_iso = ON_Surface::E_iso;

      // north side of surface
      c2i = brep->AddTrimCurve( new ON_LineCurve( p2, p3 ) );
      ON_BrepTrim& trim2 = brep->NewTrim( e2, f[fi].bRev[2], loop, c2i );
      trim2.m_tolerance[0] = 0.0;
      trim2.m_tolerance[1] = 0.0;
      trim2.m_type = (trim2.m_vi[0] != trim2.m_vi[1]) ? ON_BrepTrim::mated : ON_BrepTrim::singular;
      trim2.m_iso = ON_Surface::N_iso;

      // west side of surface
      c2i = brep->AddTrimCurve( new ON_LineCurve( p3, p0 ) );
      ON_BrepTrim& trim3 = brep->NewTrim( e3, f[fi].bRev[3], loop, c2i );
      trim3.m_tolerance[0] = 0.0;
      trim3.m_tolerance[1] = 0.0;
      trim3.m_type = (trim3.m_vi[0] != trim3.m_vi[1]) ? ON_BrepTrim::mated : ON_BrepTrim::singular;
      trim3.m_iso = ON_Surface::W_iso;
    }
    if ( !brep->IsValid() ) {
      if ( pBrep )
        pBrep->Destroy();
      else
        delete brep;
      brep = 0;
    }
  }
  else 
    brep = 0;
  return brep;
}


ON_Brep* ON_BrepWedge( const ON_3dPoint* corners, ON_Brep* pBrep )
{
  ON_Brep* brep = 0;

  int vi, ei, ti, fi, si, c2i;
  
  if(corners)
  {
    // use the one passed in or make a new one
    if( pBrep ) 
    {
      pBrep->Destroy();
      brep = pBrep;
    }
    else
      brep = new ON_Brep();
    
    brep->m_C2.Reserve(18);
    brep->m_C3.Reserve(9);
    brep->m_S.Reserve(5);
    brep->m_V.Reserve(6);
    brep->m_E.Reserve(9);
    brep->m_L.Reserve(5);
    brep->m_T.Reserve(18);
    brep->m_F.Reserve(5);

    // vertices
    for ( vi = 0; vi < 6; vi++ )
    {
      brep->NewVertex( corners[vi], 0.0 );
    }
    
    // 3d edges around bottom e0 - e2
    for ( ei = 0; ei < 3; ei++ )
    {
      ON_BrepVertex& v0 = brep->m_V[ei];
      ON_BrepVertex& v1 = brep->m_V[(ei+1)%3];
      brep->m_C3.Append( new ON_LineCurve( v0.point, v1.point ) );
      brep->NewEdge( v0, v1, ei, nullptr, 0.0 );
    }
    // 3d edges around top e3 - e5
    for ( ei = 3; ei < 6; ei++ )
    {
      ON_BrepVertex& v0 = brep->m_V[ei];
      ON_BrepVertex& v1 = brep->m_V[ei==5?3:(ei+1)];
      brep->m_C3.Append( new ON_LineCurve( v0.point, v1.point ) );
      brep->NewEdge( v0, v1, ei, nullptr, 0.0 );
    }
    // 3d vertical edges e6 - e8
    for ( ei = 6; ei < 9; ei++ )
    {
      ON_BrepVertex& v0 = brep->m_V[ei-6];
      ON_BrepVertex& v1 = brep->m_V[ei-3];
      brep->m_C3.Append( new ON_LineCurve( v0.point, v1.point ) );
      brep->NewEdge( v0, v1, ei, nullptr, 0.0 );
    }

    /*
    //
    //                      /v5    
    //                     /|\       
    //                    / | \     
    //                   e5 |  e4   
    //                  /   e8  \     
    //                 /__e3_____\  
    //               v3|    |    |v4     
    //                 |    |    |       
    //                 |    /v2  |   
    //                 e6  / \   e7   
    //                 |  /   \  |   
    //                 | e2    e1|   
    //                 |/       \|     
    //                 /____e0___\  
    //               v0           v1
    */

    struct {
      int e[4], bRev[4];
    } f[5] = {
      {{0, 7, 3, 6},  {false, false, true,  true}},  // vertical front
      {{1, 8, 4, 7},  {false, false, true,  true}},  // vertical right
      {{2, 6, 5, 8},  {false, false, true,  true}},  // vertical left
      {{2, 1, 0,-1},  {true,  true,  true,  true}},  // bottom
      {{3, 4, 5,-1},  {false, false, false, false}}  // top
    };
    for ( fi = 0; fi < 5; fi++ )
    {
      ON_BrepEdge* e0;
      ON_BrepEdge* e1;
      ON_BrepEdge* e2;
      ON_BrepEdge* e3=0;

      e0 = &brep->m_E[f[fi].e[0]];
      e1 = &brep->m_E[f[fi].e[1]];
      e2 = &brep->m_E[f[fi].e[2]];
      if( f[fi].e[3] >= 0)
        e3 = &brep->m_E[f[fi].e[3]];

      ON_BrepVertex* v0;
      ON_BrepVertex* v1;
      ON_BrepVertex* v2;
      ON_BrepVertex* v3=0;

      v0 = &brep->m_V[e0->m_vi[f[fi].bRev[0]?1:0]];
      v1 = &brep->m_V[e1->m_vi[f[fi].bRev[1]?1:0]];
      v2 = &brep->m_V[e2->m_vi[f[fi].bRev[2]?1:0]];
      if( f[fi].e[3] >= 0)
        v3 = &brep->m_V[e3->m_vi[f[fi].bRev[3]?1:0]];

      ON_NurbsSurface* srf;

      if( f[fi].e[3] >= 0)
        // 4 sided face
        srf = ON_NurbsSurfaceQuadrilateral( v0->point, v1->point, v2->point, v3->point);
      else
        // 3 sided face
        srf = ON_NurbsSurfaceQuadrilateral( v0->point, v1->point, v1->point + (v2->point - v0->point), v2->point);

      si = brep->AddSurface( srf);

      ON_Interval s = brep->m_S[si]->Domain(0);
      ON_Interval t = brep->m_S[si]->Domain(1);
      ON_2dPoint p0, p1, p2, p3;
      p0.Set(s[0],t[0]);
      p1.Set(s[1],t[0]);
      p2.Set(s[1],t[1]);
      p3.Set(s[0],t[1]);

      ON_BrepFace& face = brep->NewFace( si );
      ON_BrepLoop& loop = brep->NewLoop( ON_BrepLoop::outer, face );

      if( f[fi].e[3] >= 0)
      {
        // south side of surface
        c2i = brep->AddTrimCurve( new ON_LineCurve( p0, p1 ) );
        brep->NewTrim( *e0, f[fi].bRev[0], loop, c2i ).m_iso = ON_Surface::S_iso;
        
        // east side of surface
        c2i = brep->AddTrimCurve( new ON_LineCurve( p1, p2 ) );
        brep->NewTrim( *e1, f[fi].bRev[1], loop, c2i ).m_iso = ON_Surface::E_iso;
        
        // north side of surface
        c2i = brep->AddTrimCurve( new ON_LineCurve( p2, p3 ) );
        brep->NewTrim( *e2, f[fi].bRev[2], loop, c2i ).m_iso = ON_Surface::N_iso;

        // west side of surface
        c2i = brep->AddTrimCurve( new ON_LineCurve( p3, p0 ) );
        brep->NewTrim( *e3, f[fi].bRev[3], loop, c2i ).m_iso = ON_Surface::W_iso;
      }
      else
      {
        // south side of surface
        c2i = brep->AddTrimCurve( new ON_LineCurve( p0, p1 ) );
        brep->NewTrim( *e0, f[fi].bRev[0], loop, c2i ).m_iso = ON_Surface::S_iso;
        
        // diagonal from upper left to lower right
        c2i = brep->AddTrimCurve( new ON_LineCurve( p1, p3 ) );
        brep->NewTrim( *e1, f[fi].bRev[1], loop, c2i ).m_iso = ON_Surface::not_iso;

        // west side of surface
        c2i = brep->AddTrimCurve( new ON_LineCurve( p3, p0 ) );
        brep->NewTrim( *e2, f[fi].bRev[2], loop, c2i ).m_iso = ON_Surface::W_iso;
      }
    }

    // set trim m_type and m_tolerance[]
    for ( ti = 0; ti < brep->m_T.Count(); ti++ )
    {
      ON_BrepTrim& trim = brep->m_T[ti];
      trim.m_type =  ( trim.m_vi[0] != trim.m_vi[1] && trim.m_ei >= 0 )
                  ? ON_BrepTrim::mated
                  : ON_BrepTrim::singular;
      trim.m_tolerance[0] = 0.0;
      trim.m_tolerance[1] = 0.0;
    }

    if ( !brep->IsValid() ) {
      if ( pBrep )
        pBrep->Destroy();
      else
        delete brep;
      brep = 0;
    }
  }
  else 
    brep = 0;
  return brep;
}


ON_Brep* ON_BrepSphere( const ON_Sphere& sphere, ON_Brep* pBrep )
{
  bool bArcLengthParameterization = true;
  ON_Brep* brep = nullptr;
  if ( pBrep )
    pBrep->Destroy();
  ON_RevSurface* pRevSurface = sphere.RevSurfaceForm(bArcLengthParameterization);
  if ( pRevSurface )
  {
    brep = ON_BrepRevSurface( pRevSurface, false, false, pBrep );
    if ( !brep )
      delete pRevSurface;
  }
  return brep;
}

ON_Brep* ON_BrepQuadSphere( const ON_3dPoint& Center, double radius, ON_Brep* pBrep)

{
  if (radius < 0.0)
    return 0;
  ON_Brep* brep = nullptr;
  if ( pBrep ){
    pBrep->Destroy();
    brep = pBrep;
  }
  else
    brep = ON_Brep::New();

  ON_4dPoint CV[3][3];
  CV[0][0].Set(-0.57735026918962584*radius, -0.57735026918962584*radius, 0.57735026918962584*radius, 1.0);
  CV[0][1].Set(-0.70710678118654746*radius, 0.0, 0.70710678118654746*radius, 0.81649658092772603);
  CV[0][2].Set(-0.57735026918962584*radius, 0.57735026918962584*radius, 0.57735026918962584*radius, 1.0);

  CV[1][0].Set(0.0, -0.70710678118654746*radius, 0.70710678118654746*radius, 0.81649658092772603);
  CV[1][1].Set(0.0, 0.0, 1.1093897997411788*radius, 0.46796046944844738);
  CV[1][2].Set(0.0, 0.70710678118654746*radius, 0.70710678118654746*radius, 0.81649658092772603);

  CV[2][0].Set(0.57735026918962584*radius, -0.57735026918962584*radius, 0.57735026918962584*radius, 1.0);
  CV[2][1].Set(0.70710678118654746*radius, 0.0, 0.70710678118654746*radius, 0.81649658092772603);
  CV[2][2].Set(0.57735026918962584*radius, 0.57735026918962584*radius, 0.57735026918962584*radius, 1.0);


  ON_NurbsSurface* pZp = ON_NurbsSurface::New(3, true, 3, 3, 3, 3);
  for (int i=0; i<2; i++){
    pZp->m_knot[i][0] = pZp->m_knot[i][1] = 0.0;
    pZp->m_knot[i][2] = pZp->m_knot[i][3] = radius;
  }

  for (int i=0; i<3; i++){
    for (int j=0; j<3; j++)
      pZp->SetCV(i, j, CV[i][j]);
  }

  ON_Xform roty;
  roty[0][0] = roty[0][1] = roty[0][2] = 0.0;
  roty[0][2] = 1.0;
  roty[1][0] = roty[1][2] = roty[1][3] = 0.0;
  roty[1][1] = 1.0;
  roty[2][1] = roty[2][2] = roty[2][3] = 0.0;
  roty[2][0] = -1.0;
  roty[3][0] = roty[3][1] = roty[3][2] = 0.0;
  roty[3][3] = 1.0;

  ON_NurbsSurface* pXp = ON_NurbsSurface::New(*pZp);
  pXp->Transform(roty);

  ON_NurbsSurface* pZn = ON_NurbsSurface::New(*pXp);
  pZn->Transform(roty);

  ON_NurbsSurface* pXn = ON_NurbsSurface::New(*pZn);
  pXn->Transform(roty);

  ON_Xform rotx;
  rotx[0][1] = rotx[0][2] = rotx[0][3] = 0.0;
  rotx[0][0] = 1.0;
  rotx[1][0] = rotx[1][1] = rotx[1][3] = 0.0;
  rotx[1][2] = 1.0;
  rotx[2][0] = rotx[2][2] = rotx[2][3] = 0.0;
  rotx[2][1] = -1.0;
  rotx[3][0] = rotx[3][1] = rotx[3][2] = 0.0;
  rotx[3][3] = 1.0;

  ON_NurbsSurface* pYp = ON_NurbsSurface::New(*pZp);
  pYp->Transform(rotx);

  ON_NurbsSurface* pYn = ON_NurbsSurface::New(*pZn);
  pYn->Transform(rotx);

  brep->Create(pZp);

  ON_Brep brepxp;
  brepxp.Create(pXp);
  brep->Append(brepxp);

  ON_Brep brepzn;
  brepzn.Create(pZn);
  brep->Append(brepzn);

  ON_Brep brepxn;
  brepxn.Create(pXn);
  brep->Append(brepxn);

  ON_Brep brepyp;
  brepyp.Create(pYp);
  brep->Append(brepyp);

  ON_Brep brepyn;
  brepyn.Create(pYn);
  brep->Append(brepyn);
  
  brep->CombineCoincidentVertices(brep->m_V[0], brep->m_V[13]);
  brep->CombineCoincidentVertices(brep->m_V[0], brep->m_V[21]);

  brep->CombineCoincidentVertices(brep->m_V[1], brep->m_V[4]);
  brep->CombineCoincidentVertices(brep->m_V[1], brep->m_V[20]);

  brep->CombineCoincidentVertices(brep->m_V[2], brep->m_V[7]);
  brep->CombineCoincidentVertices(brep->m_V[2], brep->m_V[17]);

  brep->CombineCoincidentVertices(brep->m_V[3], brep->m_V[14]);
  brep->CombineCoincidentVertices(brep->m_V[3], brep->m_V[16]);

  brep->CombineCoincidentVertices(brep->m_V[5], brep->m_V[8]);
  brep->CombineCoincidentVertices(brep->m_V[5], brep->m_V[23]);

  brep->CombineCoincidentVertices(brep->m_V[6], brep->m_V[11]);
  brep->CombineCoincidentVertices(brep->m_V[6], brep->m_V[18]);

  brep->CombineCoincidentVertices(brep->m_V[9], brep->m_V[12]);
  brep->CombineCoincidentVertices(brep->m_V[9], brep->m_V[22]);

  brep->CombineCoincidentVertices(brep->m_V[10], brep->m_V[15]);
  brep->CombineCoincidentVertices(brep->m_V[10], brep->m_V[19]);

  brep->m_E[20].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[0], brep->m_E[20]);

  brep->m_E[7].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[1], brep->m_E[7]);

  brep->m_E[16].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[2], brep->m_E[16]);

  brep->m_E[13].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[3], brep->m_E[13]);

  brep->m_E[23].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[4], brep->m_E[23]);

  brep->m_E[11].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[5], brep->m_E[11]);

  brep->m_E[17].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[6], brep->m_E[17]);

  brep->m_E[22].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[8], brep->m_E[22]);

  brep->m_E[15].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[9], brep->m_E[15]);

  brep->m_E[18].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[10], brep->m_E[18]);

  brep->m_E[21].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[12], brep->m_E[21]);

  brep->m_E[19].Reverse();
  brep->CombineCoincidentEdges(brep->m_E[14], brep->m_E[19]);
  

  brep->Compact();

  ON_Xform trans;
  trans = ON_Xform::TranslationTransformation(Center.x, Center.y, Center.z);
  brep->Transform(trans);

  brep->SetTolerancesBoxesAndFlags();

  return brep;
}

ON_Brep* ON_BrepTorus( const ON_Torus& torus, ON_Brep* pBrep )
{
  bool bArcLengthParameterization = true;
  ON_Brep* brep = nullptr;
  if ( pBrep )
    pBrep->Destroy();
  ON_RevSurface* pRevSurface = torus.RevSurfaceForm();
  if ( pRevSurface )
  {
    if ( bArcLengthParameterization )
    {
      double r = fabs(torus.major_radius);
      if ( r <= ON_SQRT_EPSILON )
        r = 1.0;
      r *= ON_PI;
      pRevSurface->SetDomain(0,0.0,2.0*r);
      r = fabs(torus.minor_radius);
      if ( r <= ON_SQRT_EPSILON )
        r = 1.0;
      r *= ON_PI;
      pRevSurface->SetDomain(1,0.0,2.0*r);
    }
    brep = ON_BrepRevSurface( pRevSurface, false, false, pBrep );
    if ( !brep )
      delete pRevSurface;
  }
  return brep;
}


ON_Brep* ON_BrepCylinder( const ON_Cylinder& cylinder, 
                          bool bCapBottom,
                          bool bCapTop,
                          ON_Brep* pBrep )
{
  bool bArcLengthParameterization = true;
  ON_Brep* brep = nullptr;
  if ( pBrep )
    pBrep->Destroy();
  ON_RevSurface* pRevSurface = cylinder.RevSurfaceForm();
  if ( pRevSurface )
  {
    if ( bArcLengthParameterization )
    {
      double r = fabs(cylinder.circle.radius);
      if ( r <= ON_SQRT_EPSILON )
        r = 1.0;
      pRevSurface->SetDomain(0,0.0,2.0*ON_PI*r);
    }
    brep = ON_BrepRevSurface( pRevSurface, bCapBottom, bCapTop, pBrep );
    if ( !brep )
      delete pRevSurface;
  }
  return brep;
}


ON_Brep* ON_BrepCone( const ON_Cone& cone, bool bCapBase, ON_Brep* pBrep )
{
  bool bArcLengthParameterization = true;
  ON_Brep* brep = nullptr;
  if ( pBrep )
    pBrep->Destroy();
  ON_RevSurface* pRevSurface = cone.RevSurfaceForm();
  if ( pRevSurface )
  {
    if ( bArcLengthParameterization )
    {
      double r = fabs(cone.radius);
      if ( r <= ON_SQRT_EPSILON )
        r = 1.0;
      pRevSurface->SetDomain(0,0.0,2.0*ON_PI*r);
    }
    brep = ON_BrepRevSurface( pRevSurface, bCapBase, bCapBase, pBrep );
    if ( !brep )
      delete pRevSurface;
  }
  return brep;
}


ON_Brep* ON_BrepRevSurface( 
          ON_RevSurface*& pRevSurface,
          bool bCapStart,
          bool bCapEnd,
          ON_Brep* pBrep 
          )
{
  ON_Brep* brep = 0;
  if ( pBrep )
    pBrep->Destroy();
  if ( pRevSurface && pRevSurface->m_curve )
  {
    if ( pBrep )
      brep = pBrep;
    else
      brep = new ON_Brep();

    bool bTransposed = pRevSurface->m_bTransposed;
    ON_Line axis = pRevSurface->m_axis;
    ON_3dPoint R[2];
    R[0] = pRevSurface->m_curve->PointAtStart();
    R[1] = pRevSurface->m_curve->PointAtEnd();
    if ( !pRevSurface->IsClosed(bTransposed?1:0) )
    {
      bCapStart = false;
      bCapEnd = false;
    }

    if ( !brep->Create(pRevSurface) )
    {
      if (pBrep != brep)
        delete brep;
      brep = 0;
    }
    else if ( bCapStart || bCapEnd )
    {
      // cap ends
      for ( int capcount = 0; capcount < 2; capcount++ )
      {
        int srf_trim_ti = -1;
        // capcount = 0 for bottom cap and 1 for top cap
        if ( capcount == 0 )
        {
          // cap circle at start of revolute
          if ( !bCapStart )
            continue;
          srf_trim_ti = (bTransposed) ? 3 : 0;
        }
        else
        {
          // cap circle at start of revolute
          if ( !bCapEnd )
            continue;
          srf_trim_ti = (bTransposed) ? 1 : 2;
        }
        if ( srf_trim_ti < 0 || srf_trim_ti >= brep->m_T.Count() )
          continue;

        if ( brep->m_T[srf_trim_ti].m_type != ON_BrepTrim::boundary )
          continue;
        if ( brep->m_T[srf_trim_ti].m_ei < 0 )
          continue;
        ON_BrepEdge& edge = brep->m_E[brep->m_T[srf_trim_ti].m_ei];
        if ( !edge.IsClosed() )
          continue;

        ON_Circle circle;
        {
          ON_Arc arc;
          const ON_Curve* edge_curve = edge.EdgeCurveOf();
          if ( 0 == edge_curve )
            continue;
          if ( !edge_curve->IsArc( nullptr, &arc ) )
            continue;
          if ( !arc.IsCircle() )
            continue;
          circle = arc;
        }

        /*
        if ( capcount == 0 )
          circle.Reverse();
          */
        circle.Reverse();

        // create cap surface
        double radius = circle.radius;
        ON_NurbsSurface* pCapSurface = ON_NurbsSurfaceQuadrilateral( 
          circle.plane.PointAt(-radius,-radius),
          circle.plane.PointAt(+radius,-radius),
          circle.plane.PointAt(+radius,+radius),
          circle.plane.PointAt(-radius,+radius)
          );
        pCapSurface->m_knot[0][0] = -fabs(radius);
        pCapSurface->m_knot[0][1] =  fabs(radius);
        pCapSurface->m_knot[1][0] = pCapSurface->m_knot[0][0];
        pCapSurface->m_knot[1][1] = pCapSurface->m_knot[0][1];

        // trim curve circle
        circle.Create( ON_xy_plane, ON_3dPoint::Origin, radius );
        ON_NurbsCurve* c2 = new ON_NurbsCurve();
        circle.GetNurbForm(*c2);
        c2->ChangeDimension(2);

        int si = brep->AddSurface(pCapSurface);
        int c2i = brep->AddTrimCurve(c2);
        ON_BrepFace& cap = brep->NewFace( si );
        ON_BrepLoop& loop = brep->NewLoop( ON_BrepLoop::outer, cap );
        ON_BrepTrim& trim = brep->NewTrim( edge, true, loop, c2i );
        for ( int eti = 0; eti < edge.m_ti.Count(); eti++ )
          brep->m_T[ edge.m_ti[eti] ].m_type = ON_BrepTrim::mated;
        trim.m_tolerance[0] = 0.0;
        trim.m_tolerance[1] = 0.0;
        trim.m_pbox.m_min.x = -radius;
        trim.m_pbox.m_min.y = -radius;
        trim.m_pbox.m_min.z = 0.0;
        trim.m_pbox.m_max.x = radius;
        trim.m_pbox.m_max.y = radius;
        trim.m_pbox.m_max.z = 0.0;
        trim.m__legacy_2d_tol = 0.0;
        trim.m__legacy_3d_tol = 0.0;
        loop.m_pbox = trim.m_pbox;
        brep->SetTrimTypeFlags(trim);
        brep->SetTrimIsoFlags(trim);
      }
    }
  }
  return brep;
}



static bool AddC3Curve( const ON_Curve* c3, ON_SimpleArray<ON_Curve*>& C3 )
{
  int j;
  if ( !c3 )
    return false;
  const int c3dim = c3->Dimension();
  if ( c3dim != 3 && c3dim != 2 )
    return false;
  if ( ON_PolyCurve::Cast(c3) )
  {
    const ON_PolyCurve* polycrv = static_cast<const ON_PolyCurve*>(c3);
    for ( j = 0; j < polycrv->Count(); j++ )
    {
      if ( !AddC3Curve( polycrv->SegmentCurve(j), C3 ) )
        return false;
    }
  }
  else if ( ON_PolylineCurve::Cast(c3) )
  {
    ON_Line line;
    //ON_LineCurve* linecrv = 0;
    const ON_PolylineCurve* pline = static_cast<const ON_PolylineCurve*>(c3);
    line.to = pline->m_pline[0];
    if ( 2 == c3dim )
      line.to.z = 0.0;
    for ( j = 1; j < pline->m_pline.Count(); j++ )
    {
      line.from = line.to;
      line.to = pline->m_pline[j];
      if ( 2 == c3dim )
        line.to.z = 0.0;
      if ( line.Length() > 0 )
        C3.Append( new ON_LineCurve(line) );
    }
  }
  else
  {
    ON_Curve* c3dup = c3->DuplicateCurve();
    if ( 0 == c3dup )
      return false;
    if ( 2 == c3dup->Dimension() )
    {
      c3dup->ChangeDimension(3);
      if ( 3 != c3dup->Dimension() )
      {
        delete c3dup;
        return false;
      }
    }
    C3.Append( c3dup );
  }
  return true;
}

bool ON_Brep::NewPlanarFaceLoop(
      int face_index,
      ON_BrepLoop::TYPE loop_type,
      ON_SimpleArray<ON_Curve*>& boundary,
      bool bDuplicateCurves
      )
{
  m_is_solid = 0;
  if ( face_index < 0 || face_index >= m_F.Count() || boundary.Count() < 1 )
    return false;
  ON_BrepFace& face = m_F[face_index];
  const ON_PlaneSurface* pPlaneSurface = ON_PlaneSurface::Cast(face.SurfaceOf());
  if ( !pPlaneSurface )
    return false;
  const ON_Plane plane(pPlaneSurface->m_plane);

  // get 3d edge curves
  ON_SimpleArray<ON_Curve*> C3( 2*boundary.Count() );
  ON_Curve* c3;
  int i, count = boundary.Count();
  for ( i = 0; i < count; i++ )
  {
    c3 = boundary[i];
    if ( !c3 )
      break;
    if ( bDuplicateCurves )
    {
      if ( !AddC3Curve( c3, C3 ) )
        break;
    }
    else
    {
      C3.Append(c3);
      boundary[i] = 0;
    }
  }

  if ( i < count )
  {
    ON_ERROR("ON_Brep::NewPlanarFaceLoop - null 3d curve in boundary[] array");
    if ( bDuplicateCurves )
    {
      for ( i = 0; i < C3.Count(); i++ )
        delete C3[i];
    }
    else
    {
      for ( i = 0; i < C3.Count(); i++ )
        boundary[i] = C3[i];
    }
    return false;
  }

  // get 2d trim curves
  ON_Xform proj_to_plane;
  proj_to_plane[0][0] = plane.xaxis.x;
  proj_to_plane[0][1] = plane.xaxis.y;
  proj_to_plane[0][2] = plane.xaxis.z;
  proj_to_plane[0][3] = -(plane.xaxis*plane.origin);
  proj_to_plane[1][0] = plane.yaxis.x;
  proj_to_plane[1][1] = plane.yaxis.y;
  proj_to_plane[1][2] = plane.yaxis.z;
  proj_to_plane[1][3] = -(plane.yaxis*plane.origin);
  proj_to_plane[2][0] = plane.zaxis.x;
  proj_to_plane[2][1] = plane.zaxis.y;
  proj_to_plane[2][2] = plane.zaxis.z;
  proj_to_plane[2][3] = -(plane.zaxis*plane.origin);
  proj_to_plane[3][0] = 0.0;
  proj_to_plane[3][1] = 0.0;
  proj_to_plane[3][2] = 0.0;
  proj_to_plane[3][3] = 1.0;

  count = C3.Count();
  ON_BoundingBox loop_pbox, cbox;
  ON_SimpleArray<double> edge_tol(count);
  ON_SimpleArray<ON_NurbsCurve*> C2( count );
  ON_NurbsCurve* c2;
  for ( i = 0; i < count; i++ )
  {
    c3 = C3[i];
    c2 = new ON_NurbsCurve();
    if ( !c3->GetNurbForm(*c2) )
      break;
    if ( !c2->Transform(proj_to_plane) )
      break;
    if ( !c2->GetBoundingBox(cbox) )
      break;
    double d = fabs(cbox.m_max.z);
    if ( d < fabs(cbox.m_min.z) )
      d = fabs(cbox.m_min.z);
    if ( d <= ON_ZERO_TOLERANCE )
      d = 0.0;
    edge_tol.Append( d );
    if ( !c2->ChangeDimension(2) )
      break;
    if ( !c2->MakePiecewiseBezier() )
      break;
    cbox.m_min.z = 0.0;
    cbox.m_max.z = 0.0;
    loop_pbox.Union(cbox);
    C2.Append(c2);
  }
  if ( i < count )
  {
    ON_ERROR("ON_Brep::NewPlanarFaceLoop - unable to create 2d trim curve");
    for ( i = 0; i < C2.Count(); i++ )
      delete C2[i];
    for ( i = 0; i < C3.Count(); i++ )
      delete C3[i];
    return false;
  }

  // add new vertices
  const int vi0 = m_V.Count();
  m_V.Reserve( vi0 + count );
  for ( i = 0; i < count; i++ )
    NewVertex( C3[i]->PointAtStart() );

  // add new edges
  const int ei0 = m_E.Count();
  m_E.Reserve( ei0 + count );
  for ( i = 0; i < count; i++ ) 
  {
    int c3i = AddEdgeCurve( C3[i] );
    ON_BrepEdge& edge = NewEdge( m_V[vi0+i], m_V[vi0+((i+1)%count)], c3i );
    edge.m_tolerance = edge_tol[i];
  }

  // add new trims
  ON_3dPoint P, Q;
  double trim_tol[2];
  ON_BrepLoop& loop = NewLoop( loop_type, face );
  loop.m_pbox = loop_pbox;
  for (i = 0; i < count; i++)
  {
    int c2i = AddTrimCurve( C2[i] );
    trim_tol[0] = 0.0;
    trim_tol[1] = 0.0;
    ON_NurbsCurve* c2_local = C2[i];
    P = c2_local->PointAtEnd();
    Q = C2[(i+1)%count]->PointAtStart();
    double w = (c2_local->IsRational()) ? c2_local->Weight(c2_local->m_cv_count-1) : 1.0;
    if (w < ON_ZERO_TOLERANCE)
      w = 1.0;
    if (c2_local->IsRational())
      Q *= w;
    c2_local->SetCV( c2_local->m_cv_count-1, Q );
    if (c2_local->IsRational())
      c2_local->SetWeight(c2_local->m_cv_count-1, w);
    trim_tol[0] = fabs(P.x - Q.x);
    trim_tol[1] = fabs(P.y - Q.y);
    if ( trim_tol[0] <= ON_ZERO_TOLERANCE )
      trim_tol[0] = 0.0;
    if ( trim_tol[1] <= ON_ZERO_TOLERANCE )
      trim_tol[1] = 0.0;
    ON_BrepEdge& edge = m_E[ei0+i];
    ON_BrepTrim& trim = NewTrim( edge, false, loop, c2i );
    trim.m_type = ON_BrepTrim::boundary;
    trim.m_tolerance[0] = 1.1*trim_tol[0];
    trim.m_tolerance[1] = 1.1*trim_tol[1];
  }
  int loop_dir = LoopDirection( loop );
  switch ( loop_type )
  {
  case ON_BrepLoop::outer:
    if ( loop_dir < 0 )
      FlipLoop( loop );
    break;
  case ON_BrepLoop::inner:
    if ( loop_dir > 0 )
      FlipLoop( loop );
    break;
  case ON_BrepLoop::unknown:
    if ( loop_dir > 0 )
      loop.m_type = ON_BrepLoop::outer;
    else if ( loop_dir < 0 )
      loop.m_type = ON_BrepLoop::inner;
    break;
  default:
    // intentionally ignoring other ON_Brep::TYPE enum values
    break;
  }

  SetTrimIsoFlags();
  for ( i = vi0; i < m_V.Count(); i++ )
    SetVertexTolerance( m_V[i] );

  return true;
}


ON_Brep* ON_BrepTrimmedPlane( 
            const ON_Plane& plane, 
            ON_SimpleArray<ON_Curve*>& boundary,
            bool bDuplicateCurves,
            ON_Brep* pBrep )
{
  ON_Brep* brep;
  if ( pBrep )
  {
    pBrep->Destroy();
    brep = pBrep;
  }
  else
    brep = new ON_Brep();

  ON_PlaneSurface* s = new ON_PlaneSurface();
  s->m_plane = plane;
  s->SetDomain(0, -100.0, 100.0 ); // any domain and extents will do for now
  s->SetDomain(1, -100.0, 100.0 );
  s->SetExtents(0, s->Domain(0) );
  s->SetExtents(1, s->Domain(1) );
  const int si = brep->AddSurface(s);
  ON_BrepFace& face = brep->NewFace( si );
  face.DestroyRuntimeCache();
  if ( brep->NewPlanarFaceLoop( face.m_face_index, ON_BrepLoop::outer, boundary, bDuplicateCurves ) )
  {
    // set face domain
    const ON_BrepLoop* loop = brep->m_L.Last();
    s->SetDomain(0, loop->m_pbox.m_min.x, loop->m_pbox.m_max.x );
    s->SetDomain(1, loop->m_pbox.m_min.y, loop->m_pbox.m_max.y );
    s->SetExtents(0,s->Domain(0));
    s->SetExtents(1,s->Domain(1));

    // need to update trim m_iso flags because we changed surface shape
    brep->SetTrimIsoFlags(face);
  }
  else
  {
    if ( pBrep )
      pBrep->Destroy();
    else
      delete brep;
    brep = nullptr;
  }
  return brep;
}



ON_Brep* ON_BrepTrimmedPlane( 
            const ON_Plane& plane, 
            const ON_Curve& boundary,
            ON_Brep* pBrep )
{
  ON_SimpleArray<ON_Curve*> c;
  c.Append(const_cast<ON_Curve*>(&boundary));
  return ON_BrepTrimmedPlane( plane, c, true, pBrep );
}


ON_DECL
ON_Brep* ON_BrepFromMesh(
  const ON_MeshTopology& mesh_topology,
  bool bTrimmedTriangles,
  ON_Brep* pBrep
)
{
  double tol = .01;
  return ON_BrepFromMeshWithNgons(mesh_topology, bTrimmedTriangles, false, tol, pBrep);
}

static ON_Mesh* NgonulateMesh(const ON_Mesh* mesh_input, double tol)
{
  if (nullptr == mesh_input)
    return nullptr;

  ON_Mesh* mesh_output = new ON_Mesh(*mesh_input);
  if (nullptr == mesh_output)
    return nullptr;

  if (0 < mesh_output->QuadCount())
    mesh_output->ConvertNonPlanarQuadsToTriangles(tol, ON_UNSET_VALUE, 0);

  mesh_output->SetNgonCount(0);

  ON_MeshVertexFaceMap vfmap;
  vfmap.SetFromMesh(mesh_output, true);

  mesh_output->AddPlanarNgons(vfmap.VertexFaceMap(), tol, 3, 0, true );
  //ON_DebugWriteObject(mesh_output);

  if (mesh_output->NgonCount() <= 0)
  {
    delete mesh_output;
    return nullptr;
  }

  mesh_output->SeparateNgons(const_cast<unsigned int**>(vfmap.VertexFaceMap()), 0, mesh_output->NgonUnsignedCount());
  // adding vertices invalidates vfmap;
  vfmap.Destroy();
  vfmap.SetFromMesh(mesh_output, true);

  mesh_output->SetNgonVertexNormals(0, mesh_output->NgonUnsignedCount());

  mesh_output->RemoveNgonInteriorVertices(vfmap.VertexFaceMap(), 0, mesh_output->NgonUnsignedCount());

  return mesh_output;
}

static bool FixNonPlanarNgons(ON_Mesh& mesh, double tol)
{
  mesh.RemoveAllNgons();
  ON_Mesh* pMesh = NgonulateMesh(&mesh, tol);
  if (nullptr != pMesh)
  {
    mesh = *pMesh;
    delete pMesh;
    return true;
  }

  return false;
}

static bool AllNgonsArePlanar(const ON_Mesh* pMesh, double tol)
{
  bool rc = true;
  int i, ict = pMesh->NgonCount();
  for (i = 0; ict > i && true == rc; i++)
  {
    const ON_MeshNgon* pNgon = pMesh->Ngon(i);
    // establish a comparison plane with the first face.
    int fi, fct = pNgon->m_Fcount;
    if (0 == fct)
      continue;

    ON_MeshFace face = pMesh->m_F[pNgon->m_fi[0]];
    ON_Plane plane;
    plane.CreateFromPoints(pMesh->Vertex(face.vi[0]), pMesh->Vertex(face.vi[1]), pMesh->Vertex(face.vi[3]));
    for (fi = 0; fct > fi && true == rc; fi++)
    {
      face = pMesh->m_F[pNgon->m_fi[fi]];
      for (int vi = 0; 4 > vi && true == rc; vi++)
      {
        if (tol < plane.DistanceTo(pMesh->Vertex(face.vi[vi])))
          rc = false;
      }
    }
  }

  return rc;
}

ON_DECL
ON_Brep* ON_BrepFromMeshWithNgons(
  const ON_MeshTopology& input_topology, 
  bool bTrimmedTriangles,
  bool bUseNgonsIfTheyExist,
  double tol,
  ON_Brep* pBrep
  )
{
  ON_BezierCurve edge_line(3,false,2);
  ON_BezierCurve trim_line(2,false,2);
  ON_Brep* brep = nullptr;
  if ( pBrep )
    pBrep->Destroy();

  const ON_MeshTopology* mesh_topology = &input_topology;
  const ON_Mesh* pMesh = mesh_topology->m_mesh;
  if (nullptr == pMesh || false == mesh_topology->IsValid())
    return nullptr;

  bUseNgonsIfTheyExist = bUseNgonsIfTheyExist && pMesh->HasNgons();
  bool bAllNgonsArePlanar = true;
  if (true == bUseNgonsIfTheyExist)
    bAllNgonsArePlanar = AllNgonsArePlanar(pMesh, tol);

  ON_Mesh tmpmesh = *pMesh;
  if (false == bAllNgonsArePlanar)
  {
    if (true == FixNonPlanarNgons(tmpmesh, tol))
    {
      pMesh = &tmpmesh;
      mesh_topology = &pMesh->Topology();
    }
  }

  if (nullptr == pMesh || false == mesh_topology->IsValid())
    return nullptr;

  const int ngon_count = pMesh->NgonCount();

  bTrimmedTriangles = bTrimmedTriangles || bUseNgonsIfTheyExist;
  bUseNgonsIfTheyExist = bUseNgonsIfTheyExist && pMesh->HasNgons();

  brep = (pBrep != nullptr) ? pBrep : new ON_Brep();
  const int vertex_count = mesh_topology->TopVertexCount();
  const int edge_count = mesh_topology->TopEdgeCount();
  const int face_count = mesh_topology->TopFaceCount();
  brep->m_V.Reserve( vertex_count );
  brep->m_E.Reserve( edge_count );
  brep->m_C3.Reserve( edge_count );
  brep->m_F.Reserve( face_count );
  brep->m_L.Reserve( face_count );
  brep->m_T.Reserve( 4*static_cast<size_t>(face_count) );
  brep->m_C2.Reserve( 4*static_cast<size_t>(face_count) );

  ON_Interval srf_dom[2];
  ON_3dPoint srf_2d_corner[4];
  ON_3dPoint srf_3d_corner[4];
  ON_Surface::ISO quad_iso[4] = {ON_Surface::S_iso,ON_Surface::E_iso,ON_Surface::N_iso,ON_Surface::W_iso};
  ON_Surface::ISO tri_iso[3] = {ON_Surface::S_iso,ON_Surface::E_iso,ON_Surface::not_iso};

  // May 1, 2012 Tim Fix for RR 104209
  // Use double precision vertexes from the mesh if they exist
  const ON_3dPointArray* pDPV = 0;
  if (pMesh->HasDoublePrecisionVertices())
    pDPV = &pMesh->DoublePrecisionVertices();

  for ( int vi = 0; vi < vertex_count; vi++ )
  {
    onmalloc(0);//for canceling.  
    ON_3dPoint pt;

    // May 1, 2012 Tim Fix for RR 104209
    // Use double precision vertexes from the mesh if they exist
    const ON_MeshTopologyVertex& topvert = mesh_topology->m_topv[vi];
    if (0 != pDPV)
      pt = *pDPV->At(topvert.m_vi[0]);
    else
      pt = pMesh->m_V[topvert.m_vi[0]];

    ON_BrepVertex& vertex = brep->NewVertex( pt, 0.0 );
    memset(&vertex.m_vertex_user, 0, sizeof(vertex.m_vertex_user));
  }

  for ( int ei = 0; ei < edge_count; ei++ )
  {
    onmalloc(0);//for canceling.  
    const ON_MeshTopologyEdge& mesh_edge = mesh_topology->m_tope[ei];
    ON_BrepVertex& v0 = brep->m_V[mesh_edge.m_topvi[0]];
    ON_BrepVertex& v1 = brep->m_V[mesh_edge.m_topvi[1]];
    edge_line.SetCV(0, v0.point);
    edge_line.SetCV(1, v1.point);
    ON_Curve* pEdgeCurve = new ON_NurbsCurve( edge_line );
    int c3i = brep->AddEdgeCurve( pEdgeCurve );
    ON_BrepEdge& edge = brep->NewEdge( v0, v1, c3i );    
    memset(&edge.m_edge_user, 0, sizeof(edge.m_edge_user));
    edge.m_tolerance = 0.0;
  }

  ON_SimpleArray<bool> usedfaces(face_count);
  usedfaces.SetCount(face_count);
  usedfaces.MemSet(0);

  if (true == bUseNgonsIfTheyExist)
  {
    const ON_3dPointListRef mesh_vertex_list(pMesh);
    const ON_MeshFaceList& mesh_face_list(pMesh);
    ON_MeshVertexFaceMap vf_map;
    vf_map.SetFromMesh(pMesh, true);

    for (int fi = 0; ngon_count > fi; fi++)
    {
      const ON_MeshNgon* pNgon = pMesh->Ngon(fi);
      if (nullptr == pNgon || 1 == pNgon->m_Fcount)
        continue; // handle single face ngons with original tri/quad code

      int vcount = pNgon->m_Vcount;
      ON_SimpleArray<ON_3dPoint> pts(vcount);
      for (int lti = 0; vcount > lti; lti++)
        pts.Append(pMesh->Vertex(pNgon->m_vi[lti]));

      ON_Plane plane = ON_Plane::FromPointList(pts);
      if (ON_Plane::UnsetPlane == plane)
        continue;

      ON_3dVector A(pMesh->Vertex(pMesh->m_F[pNgon->m_fi[0]].vi[1]) - pMesh->Vertex(pMesh->m_F[pNgon->m_fi[0]].vi[0]));
      ON_3dVector B(pMesh->Vertex(pMesh->m_F[pNgon->m_fi[0]].vi[3]) - pMesh->Vertex(pMesh->m_F[pNgon->m_fi[0]].vi[0]));
      A.Unitize(); B.Unitize();
      ON_3dVector C = ON_CrossProduct(A, B);
      double dot = ON_DotProduct(C, plane.Normal());
      if (0 > dot)
        plane.Flip();

      ON_PlaneSurface* pSurface = new ON_PlaneSurface(plane);
      if (nullptr == pSurface)
        continue;

      ON_BoundingBox bbox = ON_PointListBoundingBox(3, false, pts.Count(), 3, (double*)pts.Array());

      double u0, u1, v0, v1;
      plane.ClosestPointTo(bbox.Min(), &u0, &v0);
      plane.ClosestPointTo(bbox.Max(), &u1, &v1);
      pSurface->SetDomain(0, u0-10, u1+10);
      pSurface->SetDomain(1, v0-10, v1+10);
      pSurface->SetExtents(0, ON_Interval(u0 - 10, u1 + 10), true);
      pSurface->SetExtents(1, ON_Interval(v0 - 10, v1 + 10), true);

      ON_BrepFace& face = brep->NewFace(brep->AddSurface(pSurface));

      ON_SimpleArray<unsigned int> ngon_vi;
      ON_SimpleArray<unsigned int> ngon_vi_markers;
      pNgon->FindNgonBoundaries(mesh_vertex_list, mesh_face_list, &vf_map, pNgon->m_Fcount, pNgon->m_fi, ngon_vi, ngon_vi_markers);
      ON_SimpleArray<ON_3dPoint> boundary_pts(ngon_vi.Count());
      for (int vi = 0; ngon_vi.Count() > vi; vi++)
        boundary_pts.Append(pMesh->Vertex(ngon_vi[vi]));

      int ct = 0;
      for (int li = 0; ngon_vi_markers.Count() > li; li++)
      {
        ON_BrepLoop* pLoop = nullptr;
        if (0 == li)
          pLoop = &brep->NewLoop(ON_BrepLoop::outer, face);
        else
          pLoop = &brep->NewLoop(ON_BrepLoop::inner, face);
        if (nullptr == pLoop)
          continue;

        bbox = ON_PointListBoundingBox(3, false, ngon_vi_markers[li], 3, (double*)boundary_pts.At(ct));
        pLoop->m_pbox.m_min = bbox.Min();
        pLoop->m_pbox.m_max = bbox.Max();

        unsigned int* ngon_vi_loop = &ngon_vi[ct];
        ct += ngon_vi_markers[li];

        bool bFoundBadEdge = false;
        for (unsigned int lti = 0; ngon_vi_markers[li] > lti && false == bFoundBadEdge; lti++)
        {
          onmalloc(0);//for canceling. 
          int topv0 = mesh_topology->m_topv_map[ngon_vi_loop[lti]];
          int topv1 = mesh_topology->m_topv_map[ngon_vi_loop[0]];
          if (ngon_vi_markers[li] - 1 > lti)
            topv1 = mesh_topology->m_topv_map[ngon_vi_loop[lti + 1]];


          int edge_index = mesh_topology->TopEdge(topv0, topv1);
          if (-1 == edge_index)
          {
            bFoundBadEdge = true;
            continue;
          }

          ON_BrepEdge& brep_edge = brep->m_E[edge_index];
          // set the flag for vertex/edge we use and purge what isn't used when done.
          brep_edge.m_edge_user.i = 1;
          brep->m_V[brep_edge.m_vi[0]].m_vertex_user.i = 1;
          brep->m_V[brep_edge.m_vi[1]].m_vertex_user.i = 1;

          plane.ClosestPointTo(pMesh->m_V[mesh_topology->m_topv[topv0].m_vi[0]], &u0, &v0);
          trim_line.SetCV(0, ON_3dPoint(u0, v0, 0));
          plane.ClosestPointTo(pMesh->m_V[mesh_topology->m_topv[topv1].m_vi[0]], &u1, &v1);
          trim_line.SetCV(1, ON_3dPoint(u1, v1, 0));
          ON_Curve* pTrimCurve = new ON_NurbsCurve(trim_line);
          int c2i = brep->AddTrimCurve(pTrimCurve);

          const ON_MeshTopologyEdge& edge = mesh_topology->m_tope[edge_index];
          bool b_reve = false, b_foundmatch = false;
          for (int ff = 0; edge.m_topf_count > ff && false == b_foundmatch; ff++)
          {
            int face_idx = -1;
            for (unsigned int hh = 0; pNgon->m_Fcount > hh; hh++)
            {
              if (pNgon->m_fi[hh] == (unsigned int)edge.m_topfi[ff])
                face_idx = pNgon->m_fi[hh];
            }

            if (-1 == face_idx)
              continue;

            const ON_MeshTopologyFace& mesh_face = mesh_topology->m_topf[face_idx];
            int gg_ct = mesh_face.IsQuad() ? 4 : 3;
            for (int gg = 0; gg_ct > gg && false == b_foundmatch; gg++)
            {
              if (edge_index == mesh_face.m_topei[gg])
              {
                b_reve = mesh_face.m_reve[gg];
                b_foundmatch = true;
              }
            }
          }

          ON_BrepTrim& trim = brep->NewTrim(brep_edge, b_reve ? true : false, *pLoop, c2i);
          trim.m__legacy_2d_tol = 0.0;
          trim.m__legacy_3d_tol = 0.0;
          trim.m_tolerance[0] = 0.0;
          trim.m_tolerance[1] = 0.0;
          trim.m_iso = ON_Surface::not_iso;
          trim.m_type = (edge.m_topf_count > 1) ? ON_BrepTrim::mated : ON_BrepTrim::boundary;
        }
      }

      //On success mark faces to omit.
      for (unsigned int ff = 0;  pNgon->m_Fcount > ff; ff++)
        usedfaces[pNgon->m_fi[ff]] = true;
    }
  }

  for ( int fi = 0; fi < face_count; fi++ )
  {
    if (true == usedfaces[fi])
      continue;

    onmalloc(0);//for canceling.  
    const ON_MeshTopologyFace& mesh_face = mesh_topology->m_topf[fi];
    // NOTE: mesh_face.m_topei[0] ENDS at vertex fvi[0].
    int fvi[4];
    mesh_topology->GetTopFaceVertices( fi, fvi );
    bool bTriangle = mesh_face.IsTriangle();
    srf_3d_corner[0] = brep->m_V[fvi[0]].point;
    srf_3d_corner[1] = brep->m_V[fvi[1]].point;
    srf_3d_corner[2] = brep->m_V[fvi[2]].point;
    if ( bTriangle )
    {
      if ( bTrimmedTriangles )
      {
        // trimmed triangle 
        srf_3d_corner[3] = srf_3d_corner[2] - srf_3d_corner[1] + srf_3d_corner[0];
      }
      else 
      {
        // singular triangle
        srf_3d_corner[3] = srf_3d_corner[0];
      }
    }
    else
    {
      // quad
      srf_3d_corner[3] = brep->m_V[fvi[3]].point;
    }

    ON_Surface* pSurface = ON_NurbsSurfaceQuadrilateral(
                            srf_3d_corner[0], srf_3d_corner[1], 
                            srf_3d_corner[2], srf_3d_corner[3] );

    if (nullptr == pSurface)
      continue;

    srf_dom[0] = pSurface->Domain(0);
    srf_dom[1] = pSurface->Domain(1);
    srf_2d_corner[0].Set( srf_dom[0][0], srf_dom[1][0], 0.0 ); // SW parameter space corner
    srf_2d_corner[1].Set( srf_dom[0][1], srf_dom[1][0], 0.0 ); // SE parameter space corner
    srf_2d_corner[2].Set( srf_dom[0][1], srf_dom[1][1], 0.0 ); // NE parameter space corner
    srf_2d_corner[3].Set( srf_dom[0][0], srf_dom[1][1], 0.0 ); // NW parameter space corner
    ON_BrepFace& face = brep->NewFace(brep->AddSurface(pSurface));
    ON_BrepLoop& loop = brep->NewLoop( ON_BrepLoop::outer, face );
    loop.m_pbox.m_min = srf_2d_corner[0];
    loop.m_pbox.m_max = srf_2d_corner[2];

    int edge_index;
    int fei;
    if ( bTriangle && bTrimmedTriangles )
    {
      // trimmed triangle
      for ( int lti = 0; lti < 3; lti++ )
      {
        onmalloc(0);//for canceling.  
        fei = (lti+1)%3;
        edge_index = mesh_face.m_topei[fei];
        ON_BrepEdge& brep_edge = brep->m_E[edge_index];
        // set the flag for vertex/edge we use and purge what isn't used when done.
        brep_edge.m_edge_user.i = 1;
        brep->m_V[brep_edge.m_vi[0]].m_vertex_user.i = 1;
        brep->m_V[brep_edge.m_vi[1]].m_vertex_user.i = 1;

        const ON_MeshTopologyEdge& mesh_edge = mesh_topology->m_tope[edge_index];
        trim_line.SetCV(0,srf_2d_corner[lti]);
        trim_line.SetCV(1,srf_2d_corner[(lti+1)%3]);
        ON_Curve* pTrimCurve = new ON_NurbsCurve( trim_line );
        int c2i = brep->AddTrimCurve( pTrimCurve );
        ON_BrepTrim& trim = brep->NewTrim( brep_edge, 
                                            mesh_face.m_reve[fei]?true:false, 
                                            loop, 
                                            c2i );
        trim.m__legacy_2d_tol = 0.0;
        trim.m__legacy_3d_tol = 0.0;
        trim.m_tolerance[0] = 0.0;
        trim.m_tolerance[1] = 0.0;
        trim.m_iso = tri_iso[lti];
        trim.m_type = (mesh_edge.m_topf_count > 1) ? ON_BrepTrim::mated : ON_BrepTrim::boundary;
      }
    }
    else
    {
      for ( int lti = 0; lti < 4; lti++ )
      {
        onmalloc(0);//for canceling.  
        trim_line.SetCV(0,srf_2d_corner[lti]);
        trim_line.SetCV(1,srf_2d_corner[(lti+1)%4]);
        ON_Curve* c2 = new ON_NurbsCurve( trim_line );
        int c2i = brep->AddTrimCurve( c2 );
        if ( bTriangle && lti == 3 )
        {
          // build a new singular edge
          brep->NewSingularTrim( brep->m_V[fvi[0]], 
                                              loop, 
                                              quad_iso[lti],
                                              c2i );
        }
        else 
        {
          fei = bTriangle ? ((lti+1)%3) : ((lti+1)%4);
          edge_index = mesh_face.m_topei[fei];
          ON_BrepEdge& brep_edge = brep->m_E[edge_index];
          // set the flag for vertex/edge we use and purge what isn't used when done.
          brep_edge.m_edge_user.i = 1;
          brep->m_V[brep_edge.m_vi[0]].m_vertex_user.i = 1;
          brep->m_V[brep_edge.m_vi[1]].m_vertex_user.i = 1;

          const ON_MeshTopologyEdge& mesh_edge = mesh_topology->m_tope[edge_index];
          ON_BrepTrim& trim = brep->NewTrim( brep_edge, 
                                              mesh_face.m_reve[fei]?true:false, 
                                              loop, 
                                              c2i );
          trim.m__legacy_2d_tol = 0.0;
          trim.m__legacy_3d_tol = 0.0;
          trim.m_tolerance[0] = 0.0;
          trim.m_tolerance[1] = 0.0;
          trim.m_iso = quad_iso[lti];
          trim.m_type = (mesh_edge.m_topf_count > 1) ? ON_BrepTrim::mated : ON_BrepTrim::boundary;
        }
      }
    }      
  }

  // delete unused edges
  int ee = 0, ect = brep->m_E.Count();
  for (; ect > ee; ee++)
  {
    if (0 == brep->Edge(ee)->m_edge_user.i)
      brep->DeleteEdge(*brep->Edge(ee), false);
  }

  // delete unused vertexes
  int vv = 0, vct = brep->m_V.Count();
  for (; vct > vv; vv++)
  {
    if (0 == brep->Vertex(vv)->m_vertex_user.i)
      brep->DeleteVertex(*brep->Vertex(vv));
  }

  brep->Compact();
  brep->SetTolerancesBoxesAndFlags(
    false, //bool bLazy = false,
    true,  //bool bSetVertexTolerances = true,
    true,  //bool bSetEdgeTolerances = true,
    true,  //bool bSetTrimTolerances = true,
    true,  //bool bSetTrimIsoFlags = true,
    true,  //bool bSetTrimTypeFlags = true,
    false, //bool bSetLoopTypeFlags = true,
    true   //bool bSetTrimBoxes = true
  );
  return brep;
}


//t0 and t1 will be indices into L.m_ti
static bool FoundSlitPair(const ON_BrepLoop& L, int* t0, int* t1)

{
  ON_Brep* B = L.Brep();
  if (!B) return false;
  const ON_Surface* Srf = L.SurfaceOf();
  double utol = 0.1*Srf->Domain(0).Length();
  double vtol = 0.1*Srf->Domain(1).Length();
  if (!Srf) return false;
  int i, count = L.m_ti.Count();
  for (i=0; i<count; i++){
    int s0 = L.m_ti[i];
    ON_BrepTrim& T0 = B->m_T[s0];
    if (T0.m_type != ON_BrepTrim::seam) continue;
    int s1 = (L.m_ti[(i+1)%count]);
    ON_BrepTrim& T1 = B->m_T[s1];
    if (T1.m_type != ON_BrepTrim::seam) continue;
    if (T0.m_vi[0] != T1.m_vi[1]) continue;
    if (T0.m_ei != T1.m_ei) continue;
    const ON_BrepEdge& E = B->m_E[T0.m_ei];
    if (E.m_ti.Count() != 2) continue;
    ON_2dPoint P0, P1;
    if (!B->GetTrim2dStart(s0, P0)) continue;
    if (!B->GetTrim2dEnd(s1, P1)) continue;
    if (fabs(P0[0] - P1[0]) > utol || fabs(P0[1] - P1[1]) > vtol) continue;
    //*t0 = s0;
    //*t1 = s1;
    *t0 = i;
    *t1 = (i+1)%count;
    return true;
  }

  return false;

}

bool ON_Brep::HasSlits(const ON_BrepLoop& L) const

{
  if (L.m_loop_index < 0)
    return false;
  if (L.m_type == ON_BrepLoop::slit)
    return true;
  int t0, t1;
  return FoundSlitPair(L, &t0, &t1);
}

bool ON_Brep::HasSlits(const ON_BrepFace& F) const

{
  if (F.m_face_index < 0)
    return false;
  int i;
  for (i=0; i<F.m_li.Count(); i++){
    const ON_BrepLoop* pL = F.Loop(i);
    if (!pL)
      continue;
    if (HasSlits(*pL))
      return true;
  }
  return false;
}

bool ON_Brep::HasSlits() const

{
  int i;
  for (i=0; i<m_F.Count(); i++){
    const ON_BrepFace& F = m_F[i];
    if (HasSlits(F))
      return true;
  }
  return false;
}

static bool MakeNurbClosed(ON_NurbsCurve& NC)

{
  if (NC.IsLinear()) return false;
  if (NC.CVCount() == 3){
    double a[2];
    if (NC.Order() == 3){
      for (int i=0; i<2; i++) a[i] = NC.Domain().ParameterAt((double)i/3.0);
    }
    else { //order = 2;
      for (int i=0; i<2; i++) a[i] = 0.5*(NC.Knot(i)+NC.Knot(i+1));
    }
    for (int i=0; i<2; i++) NC.InsertKnot(a[i], 1);
  }

  NC.ClampEnd(2);
  ON_3dPoint P = 0.5*(NC.PointAtStart()+NC.PointAtEnd());

  ON_4dPoint CV;
  NC.GetCV(NC.CVCount()-1, CV);
  CV[0] = P[0]*CV[3];
  if (NC.Dimension() > 1)
    CV[1] = P[1]*CV[3];
  if (NC.Dimension() == 3)
    CV[2] = P[2]*CV[3];
  NC.SetCV(NC.CVCount()-1, CV);

  NC.GetCV(0, CV);
  CV[0] = P[0]*CV[3];
  if (NC.Dimension() > 1)
    CV[1] = P[1]*CV[3];
  if (NC.Dimension() == 3)
    CV[2] = P[2]*CV[3];
  NC.SetCV(0, CV);

  return true;
}


bool ON_Brep::MatchTrimEnds(ON_BrepTrim& T0,
                           ON_BrepTrim& T1 
                           )

{
  // Jan 28, 2009 - Lowell changed this to let any pair with any unset vertices through
  // so it can work with loops that aren't completely done being built
  if ( T0.m_vi[1] != T1.m_vi[0] && -1 != T0.m_vi[1] && -1 != T1.m_vi[0] )
    return false;

  // 6 June 2012 Dale Lear
  //    I changed from checking for the same face index to checking
  //    for the same loop index.
  if ( T0.m_li != T1.m_li && -1 != T0.m_li && -1 != T1.m_li )
    return false;

  ON_2dPoint p0;
  if (!GetTrim2dEnd(T0.m_trim_index, p0))
    return false;

  ON_2dPoint p1;
  if (!GetTrim2dStart(T1.m_trim_index, p1))
    return false;

  if (p0 == p1)
    return true;

  // 6 June 2012 Dale Lear
  //   This makes no sense to me.  I'm commenting it out.
  //////const ON_Surface* pSrf = (T0.m_li >= 0) ? T0.SurfaceOf() : T1.SurfaceOf();
  //////if (!pSrf) 
  //////  return false;
  //////if (fabs(p0[0] - p1[0]) > 0.1*pSrf->Domain(0).Length()
  //////  || fabs(p0[1] - p1[1]) > 0.1*pSrf->Domain(1).Length())
  //////  return true; //probably across a seam.

  ON_NurbsCurve* nc0 = MakeTrimCurveNurb(T0);
  if (0 == nc0) 
    return false;
  ON_NurbsCurve* nc1 = (&T0 == &T1) 
                     ? nc0
                     : MakeTrimCurveNurb(T1);
  if (0 == nc1) 
    return false;

  if ( nc0 == nc1 ) 
  {
    bool rc = MakeNurbClosed(*nc0);
    if (rc)
    {
      T0.m_pline.Destroy();
      // the m_pbox will still be valid
      T0.DestroyCurveTree();
    }
  }

  ON_2dPoint p = 0.5*(p0+p1);
  if ( p0.x == p1.x )
    p.x = p0.x; // because x != 0.5*(x+x) for finite precision doubles
  if ( p0.y == p1.y )
    p.y = p0.y; // because y != 0.5*(y+y) for finite precision doubles

  bool xiso0 = false, yiso0 = false, xiso1 = false, yiso1 = false;

  if(T0.m_iso > ON_Surface::not_iso)
  {
    if(T0.m_iso % 2 == 1) xiso0 = true;
    else                  yiso0 = true;
  }
  if(T1.m_iso > ON_Surface::not_iso)
  {
    if(T1.m_iso % 2 == 1) xiso1 = true;
    else                  yiso1 = true;
  }

  if(xiso0 != xiso1 || yiso0 != yiso1) // not both xiso or both yiso
  {
    if(xiso0) p.x = p0.x;
    if(yiso0) p.y = p0.y;

    if(xiso1) p.x = p1.x;
    if(yiso1) p.y = p1.y;
  }

  if (!nc0->SetEndPoint(ON_3dPoint(p)))
    return false;

  ON_BrepLoop* pLoop = T0.Loop();
  if (pLoop && pLoop != T1.Loop())
    pLoop = nullptr;

  // clean up T1 flags and cached information
  if(xiso0 && p0.x != p.x) T0.m_iso = ON_Surface::not_iso;
  if(yiso0 && p0.y != p.y) T0.m_iso = ON_Surface::not_iso;
  T0.m_pline.Destroy();

  if ( T0.m_pbox.IsValid())
  {
    T0.m_pbox.Set( ON_3dPoint(p), true);

    if (pLoop && pLoop->m_pbox.IsValid())
    {
      pLoop->m_pbox.Set(ON_3dPoint(p), true);
    }
  }
  T0.DestroyCurveTree();

  if (!nc1->SetStartPoint(ON_3dPoint(p)))
    return false;

  // clean up T1 flags and cached information
  if(xiso1 && p1.x != p.x) T1.m_iso = ON_Surface::not_iso;
  if(yiso1 && p1.y != p.y) T1.m_iso = ON_Surface::not_iso;
  T1.m_pline.Destroy();
  if ( T1.m_pbox.IsValid())
  {
    T1.m_pbox.Set( ON_3dPoint(p), true);

    if (pLoop && pLoop->m_pbox.IsValid())
    {
      pLoop->m_pbox.Set(ON_3dPoint(p), true);
    }
  }
  T1.DestroyCurveTree();

  return true;
}

//match this trim to itsa next and prev in loop
bool ON_Brep::MatchTrimEnds(int trim_index)

{
  if (trim_index < 0) return false;
  ON_BrepTrim& T = m_T[trim_index];
  if (T.m_li < 0) return false;
  bool rc = true;
  int pt = PrevTrim(trim_index);
  if (pt >= 0) {
    ON_BrepTrim& TP = m_T[pt];
    if (!MatchTrimEnds(TP, T)) rc = false;
  }
  int nt = NextTrim(trim_index);
  if (nt >= 0) {
    ON_BrepTrim& TN = m_T[nt];
    if (!MatchTrimEnds(T, TN)) rc = false;
  }
  return rc;
}

bool ON_Brep::MatchTrimEnds(ON_BrepLoop& Loop)

{
  int i;
  bool rc = true;
  int count = Loop.m_ti.Count();
  for (i=0; i<count; i++){
    if (!MatchTrimEnds(m_T[Loop.m_ti[i]], m_T[Loop.m_ti[(i+1)%count]]))
    {
      rc = false;
    }
  }

  // 11 Nov 2002 Dale Lear: I added this pbox setting stuff
  Loop.m_pbox.Destroy();
  for (i=0; i<count; i++)
  {
    ON_BrepTrim& trim = m_T[Loop.m_ti[i]];
    trim.m_pbox.m_min.z = 0.0;
    trim.m_pbox.m_max.z = 0.0;
    Loop.m_pbox.Union( trim.m_pbox );
  }

  return rc;
}

bool ON_Brep::MatchTrimEnds()

{
  bool rc = true;
  for (int i=0; i<m_L.Count(); i++){
    if (!MatchTrimEnds(m_L[i])) rc = false;
  }
  return rc;
}


//after calling this, m_C2[T.m_c2i] will be a nurbs curve only referenced by 
//T, with domain = T.m_t.   
ON_NurbsCurve* ON_Brep::MakeTrimCurveNurb(ON_BrepTrim& T)

{
  // 11 Nov 2002 Dale Lear: I added the check to make sure we need to 
  // make a new NURBS curve
  ON_NurbsCurve* nc = 0;

  if (    T.m_c2i >= 0 
       && T.m_c2i < m_C2.Count() 
       && m_C2[T.m_c2i] == T.ProxyCurve()
       && T.ProxyCurveIsReversed() ==  false)
  {
    nc = ON_NurbsCurve::Cast(m_C2[T.m_c2i]);
    if ( 0 != nc 
         && T.ProxyCurveDomain() == nc->Domain()
         && 1 == TrimCurveUseCount( T.m_c2i, 2 ) )
    {
      // the trim's curve is OK.
      return nc;
    }
  }

  // get NURBS form
  nc = new ON_NurbsCurve();
  if ( !T.GetNurbForm(*nc) )
  {
    delete nc;
    nc = 0;
  }
  else
  {
    nc->MakePiecewiseBezier();
    T.m_c2i = AddTrimCurve(nc);
    T.SetProxyCurve(nc);
    //Dec 14 2010 - Chuck - this routine should not cause an iso to be not_iso.
    //MakeTrimCuerveNurb is called in the middle of MatchTrimEnds() which uses m_iso.
    //T.m_iso = ON_Surface::not_iso;
    T.m_pline.Destroy();
    T.m_pbox = nc->BoundingBox();
    T.m_pbox.m_min.z = 0.0;
    T.m_pbox.m_max.z = 0.0;
    T.DestroyCurveTree();
  }

  return nc;
}

// Remove a slit pair found by FoundSlitPair.  The Trims L.Trim(lti0) and L.Trim(lti1)
// will be removed, where L is   If they are not consecutive in the loop
// a new loop will be created and will be returned in newloop, else newloop is returned as null.
// Returns false if an error was detected and the pair couldn't be deleted.
// Run compact afterward and delete the loop if it has been colapsed.
static 
bool RemoveSlitPair(ON_Brep& B, int LI, int lti0, int lti1, ON_BrepLoop*& newloop)
{
  bool rc = false;
  ON_BrepLoop* L = B.Loop(LI);
  newloop = nullptr;
  int trim_count = L->TrimCount();
  ON_ASSERT_OR_RETURN( lti0>=0 && lti0<trim_count, false );
  ON_ASSERT_OR_RETURN( lti1>=0 && lti1<trim_count, false );
  ON_ASSERT_OR_RETURN( lti0!=lti1, false );
  ON_BrepFace* F = L->Face();
  if( !F)
    return rc;
  if( LI<0 || LI>=B.m_L.Count())
    return rc;


  int delta = (lti0-lti1+trim_count)%trim_count;

  if( delta == 1 || delta == trim_count-1){
    // trims are consecutive. Just remove them
      int s0 = L->Trim(lti0)->m_trim_index;
      int s1 = L->Trim(lti1)->m_trim_index;
      int pti = B.PrevTrim(s0);
      int nti;
      if (pti == s1){
        pti = B.PrevTrim(s1);
        nti = B.NextTrim(s0);
      }
      else 
        nti = B.NextTrim(s1);

			// TRR#62112 crashed when the loop consist only of Trim(lti0) and Trim(lti1)
			bool NextPrev =true;		// true when pti and nti are distinct from s0 and s1
			if( s0==pti || s1==pti)
				NextPrev = false;

      if( s0>=0 && s0<= B.m_T.Count() && s1>=0 && s1<= B.m_T.Count() ){ 
        B.DeleteTrim(*B.Trim(s0), true);
        B.DeleteTrim(*B.Trim(s1), true);
        if (NextPrev && pti >= 0 && nti >= 0 && B.NextTrim(pti) == nti){
          ON_BrepTrim& Tprev = B.m_T[pti];
          ON_BrepTrim& Tnext = B.m_T[nti];
          B.MatchTrimEnds( Tprev, Tnext );  

          // set m_type fields
          // set m_pbox
          B.SetTrimBoundingBoxes(*L);
        }

        rc = true;
      }
  }
  else{
    // Trims are not consecutive
    // Split the existing loop into 2 loops
    ON_BrepLoop::TYPE original_type = L->m_type;
    if( original_type!=ON_BrepLoop::inner && original_type!=ON_BrepLoop::outer)
      return false;

    newloop = &B.NewLoop(original_type);    // Check and possibly change the type later
    L = B.Loop(LI);                         // Refresh L after possible reallocation of m_L array
    if(lti0>lti1){
      int temp = lti0;
      lti0 = lti1;
      lti1 = temp;
    }

     // remove slit trims from the loop
    ON_BrepTrim& T0 = *L->Trim(lti0);
    ON_BrepTrim& T1 = *L->Trim(lti1);
    T0.m_li = -1;
    T1.m_li = -1;
    L->m_ti[lti0] = -1;
    L->m_ti[lti1] = -1;

    // build newloop->m_ti array by moving trims from L->m_ti
    int lti, ltis;
    for(lti=lti0+1; lti<lti1; lti++){
      ON_BrepTrim* T = L->Trim(lti);
      newloop->m_ti.Append( L->m_ti[lti] );
      T->m_li = newloop->m_loop_index;
      L->m_ti[lti] = -1;
    }

    for( lti = lti0, ltis = lti1+1 ; ltis<trim_count; lti++, ltis++)
      L->m_ti[lti] = L->m_ti[ltis];
    L->m_ti.SetCount(lti);


//  Tune up newly adjacent trims to be sure they meet spot on.
    newloop->m_fi = L->m_fi;          // temporarily put the newloop on same face as old loop
    ON_BrepTrim& Tstart = *newloop->Trim(0);
    ON_BrepTrim& Tend = *newloop->Trim( newloop->TrimCount()-1);
    B.MatchTrimEnds( Tend , Tstart );  

    int tc = L->TrimCount();
    ON_BrepTrim& Tprev = *L->Trim( ( lti0 -1 + tc)%tc);
    ON_BrepTrim& Tnext = *L->Trim( ( lti1+1)%tc) ;
    B.MatchTrimEnds( Tprev, Tnext );  

    B.DeleteTrim(T0, true);
    B.DeleteTrim(T1, true); 

    // set m_type fields
    L->m_type = B.ComputeLoopType(*L);
    newloop->m_type = B.ComputeLoopType(*newloop);

    // set m_pbox
    B.SetTrimBoundingBoxes(*L);
    B.SetTrimBoundingBoxes(*newloop);

    if( L->m_type==original_type && newloop->m_type==ON_BrepLoop::inner){
      // Add new inner loop to original face
      newloop->m_fi = L->m_fi;
      F->m_li.Append(newloop->m_loop_index);
      rc = true;
    }
    else if( L->m_type==original_type && newloop->m_type==ON_BrepLoop::outer){
      // New loop is outer loop on a new face
      ON_BrepFace& newface = B.NewFace( F->m_si );
      F = nullptr;       // F may no longer be a valid pointer because of array reallocation
      newface.m_li.Append( newloop->m_loop_index);
      newloop->m_fi = newface.m_face_index;
      rc = true;
    }
    else if( original_type==ON_BrepLoop::inner && 
              L->m_type== ON_BrepLoop::outer && 
              newloop->m_type == ON_BrepLoop::inner)
    { 
      // Add new inner loop to original face
      newloop->m_fi = L->m_fi;
      F->m_li.Append( newloop->m_loop_index );

      // Remove L from *F.  Move L to a new face
      for(int fli=0; fli<F->LoopCount(); fli++)
        if( F->m_li[fli]==L->m_loop_index  ) {
          F->m_li.Remove(fli);
          break;
        }

      // Place L on a new face
      ON_BrepFace& newface = B.NewFace( F->m_si );
      F = nullptr;       // F may no longer be a valid pointer because of array reallocation
      newface.m_li.Append( L->m_loop_index);
      L->m_fi = newface.m_face_index;
      rc = true;
    }
    else if( original_type==ON_BrepLoop::outer && 
              L->m_type== ON_BrepLoop::inner && 
              newloop->m_type == ON_BrepLoop::outer)
    {  
      // Add new outer loop to original face
      newloop->m_fi = L->m_fi;
      F->m_li.Insert(0,newloop->m_loop_index);  
      rc =  true;
    }
  }
  return rc;

}

bool ON_Brep::RemoveSlits(ON_BrepLoop& L)

{
  bool rc = false;
  bool rval = true;
  const int li = L.m_loop_index;

  int lti0, lti1;
  while (rval && FoundSlitPair(*Loop(li), &lti0, &lti1)){ 
    ON_BrepLoop* newloop = nullptr;
		// Warning- This can add a loop and or face causing
		//  reallocation of arrays so refernces (like L) are
		//  no longer valid.
    rval = RemoveSlitPair(*this, li, lti0, lti1, newloop);
    rc = rc || rval;
    if(rval && newloop)
      RemoveSlits(*newloop);
  }

	// 22-Oct-2009 Crash Fix TRR#55897
  if (Loop(li) && Loop(li)->m_ti.Count() == 0) 
    DeleteLoop(*Loop(li), true);
  
  return rc;
}

/*
bool ON_Brep::RemoveSlits(ON_BrepLoop& L)

{
  if (L.m_loop_index < 0) 
    return false;
  if (L.m_type == ON_BrepLoop::slit) {
    DeleteLoop(L, true);
    return true;
  }
  bool rc = false;
  int t0, t1;
  while (FoundSlitPair(L, &t0, &t1)){
    rc = true;
    DeleteTrim(m_T[t0], true);
    DeleteTrim(m_T[t1], true);
  }
  if (L.m_ti.Count() == 0)
    DeleteLoop(L, true);
  return rc;
}
*/

bool ON_Brep::RemoveSlits(ON_BrepFace& F)

{
  int i;
  bool rc = false;
  ON_SimpleArray<int> li = F.m_li;
  for (i=0; i<li.Count(); i++){
    ON_BrepLoop& L = m_L[li[i]];
    if (L.m_loop_index != li[i]) 
      continue;
    if (RemoveSlits(L))
      rc = true;
  }
  return rc;
}



bool ON_Brep::RemoveSlits()

{
  bool rc = false;
  int i;
  for (i=0; i<m_F.Count(); i++){
    ON_BrepFace& F = m_F[i];
    if (F.m_face_index != i) continue;
    if (RemoveSlits(F))
      rc = true;
  }
  return rc;
}

bool ON_Brep::ChangeVertex( int old_vi, int new_vi, bool bClearTolerances )
{
  if ( old_vi == new_vi )
    return true;

  ON_BrepVertex* old_v = Vertex(old_vi);
  ON_BrepVertex* new_v = Vertex(new_vi);
  
  if ( 0 == old_v )
    return false;
  if ( 0 == new_v )
    return false;
  if( old_v == new_v )
    return true;

  // clear type bits
  old_vi = (int)(old_v - m_V.Array()); // the (int) is for 64 bit size_t conversion
  new_vi = (int)(new_v - m_V.Array());
  if ( old_vi == new_vi )
    return true;

  int vei, evi, eti, tvi, ei;

  for ( vei = 0; vei < old_v->m_ei.Count(); vei++ )
  {
    ei = old_v->m_ei[vei];
    ON_BrepEdge* edge = Edge( ei );
    if ( 0 == edge )
      continue;
    // edges that start/end at the same vertex are listed twice in old_v->m_ei[].
    if ( edge->m_vi[0] == old_v->m_vertex_index )
      evi = 0;
    else if ( edge->m_vi[1] == old_v->m_vertex_index )
      evi = 1;
    else
      continue;

    // connect edge to new vertex
    new_v->m_ei.Append(ei);
    edge->m_vi[evi] = new_vi;
    if ( bClearTolerances )
    {
      edge->m_tolerance = ON_UNSET_VALUE;
      new_v->m_tolerance = ON_UNSET_VALUE;
    }

    for ( eti = 0; eti < edge->m_ti.Count(); eti++ )
    {
      ON_BrepTrim* trim = Trim( edge->m_ti[eti]);
      if ( 0 == trim )
        continue;
      tvi = trim->m_bRev3d ? 1-evi : evi;
      trim->m_vi[tvi] = new_vi;
      for(;;)
      {
        if ( 0 == tvi )
          trim = Trim(PrevTrim(trim->m_trim_index));
        else if ( 1 == tvi )
          trim = Trim(NextTrim(trim->m_trim_index));
        else
          break;

        if ( 0 == trim )
          break;

        if ( trim->m_ei >= 0 )
          break; // not singular

        if ( trim->m_vi[1-tvi] == old_vi )
          trim->m_vi[1-tvi] = new_vi;
        else
          break;

        if ( trim->m_vi[tvi] == old_vi )
          trim->m_vi[tvi] = new_vi;
        else
          break;
      }
    }
  }
  old_v->m_ei.Destroy();
  return true;
}

/* Obsolete.  ON_Curve::SetStartPoint and SetEndPoint do the right thing.
bool ON_BrepEdge::SetStartPoint(ON_3dPoint start_point)
{
  return false;
}

bool ON_BrepEdge::SetEndPoint(ON_3dPoint end_point)
{
  return false;
}


bool ON_BrepTrim::SetStartPoint(ON_3dPoint point)
{
  if ( 0 == m_brep )
    return false;
  if ( point.x == ON_UNSET_VALUE || point.y == ON_UNSET_VALUE )
    return false;
  if ( m_c2i < 0 || m_c2i >= m_brep->m_C2.Count() )
    return false;
  const ON_Curve* c2 = m_brep->m_C2[m_c2i];
  if ( 0 == c2 )
    return false;

  point.z = 0.0;
  ON_Interval domain = Domain();
  ON_3dPoint q = PointAtStart();
  q.z = 0;
  if ( point != q )
  {
   
    ON_NurbsCurve* nc2 = 0;
    if ( ProxyCurveDomain() == c2->Domain() && !ProxyCurveIsReversed() )
      nc2 = ON_NurbsCurve::Cast(c2);
    int use_count = (0 != nc2 ) ? m_brep->TrimCurveUseCount(m_c2i,2) : 0;
    if ( 0 == nc2 || use_count )
    {
      nc2 = NurbsCurve();
      if ( 0 == nc2 )
        return false;
    }
    nc2->ClampEnd();
    nc2->SetDomain(domain[0],domain[1]);
    if ( nc2->GetLocalClosestPoint( point, domain[0], &t ) )
    {
      nc2->Trim( ON_Interval(t,domain[1] );
    }

  }
  return false;
}


bool ON_BrepTrim::SetEndPoint(ON_3dPoint end_point)
{
  return false;
}
*/


bool ON_Brep::CloseTrimGap( ON_BrepTrim& trim0, ON_BrepTrim& trim1 )
{

  // carefully close gap between end of prev_trim and start of next_trim

  // make sure trim0 and trim1 are adjacent trims in a trimming loop
  if ( trim0.m_vi[1] != trim1.m_vi[0] )
    return false;
  if ( trim0.m_li != trim1.m_li )
    return false;
  if ( trim0.m_li < 0 || trim0.m_li >= m_L.Count() )
    return false;
  ON_BrepLoop& loop = m_L[trim0.m_li];
  int lti;
  if ( loop.m_ti.Count() == 1 && trim0.m_trim_index == trim1.m_trim_index )
  {
    if ( trim0.IsClosed() )
      return true;
    lti = 0;
  }
  else
  {
    for ( lti = 0; lti < loop.m_ti.Count(); lti++ )
    {
      if ( loop.m_ti[lti] == trim0.m_trim_index && loop.m_ti[(lti+1)%loop.m_ti.Count()] == trim1.m_trim_index )
        break;
    }
  }
  if ( lti >= loop.m_ti.Count() )
    return false;

  // determine where trims end and where they should meet.
  ON_Interval domain0 = trim0.Domain();
  ON_Interval domain1 = trim1.Domain();
  double t0 = domain0[1];
  double t1 = domain1[0];
  ON_3dPoint p0, p1;
  trim0.EvPoint( t0, p0 );
  trim1.EvPoint( t1, p1 );
  p0.z = 0.0;
  p1.z = 0.0;
  ON_3dPoint p = ON_Line(p0,p1).PointAt(0.5);
  if ( p0.x == p1.x )
    p.x = p0.x;
  if ( p0.y == p1.y )
    p.y = p0.y;

  int coord0_lock = -1;
  int coord1_lock = -1;
  switch(trim0.m_iso)
  {
  case ON_Surface::x_iso:
  case ON_Surface::W_iso:
  case ON_Surface::E_iso:
    // vertical iso curve - lock x coordinate
    coord0_lock = 0;
    break;
  case ON_Surface::y_iso:
  case ON_Surface::S_iso:
  case ON_Surface::N_iso:
    // horizontal iso curve - lock y coordinate
    coord0_lock = 1;
    break;
  default:
    coord0_lock = -1;
  }

  switch(trim1.m_iso)
  {
  case ON_Surface::x_iso:
  case ON_Surface::W_iso:
  case ON_Surface::E_iso:
    // vertical iso curve - lock x coordinate
    coord1_lock = 0;
    switch(coord0_lock)
    {
    case 0:
      if ( ON_Surface::x_iso == trim0.m_iso && ON_Surface::x_iso != trim1.m_iso )
        p.x = p1.x; // trim1 is on surface edge
      else if ( ON_Surface::x_iso != trim0.m_iso && ON_Surface::x_iso == trim1.m_iso )
        p.x = p0.x; // trim0 is on surface edge
      else
      {
        // longest one wins
        if ( p0.DistanceTo(trim0.PointAtStart()) >= p1.DistanceTo(trim1.PointAtEnd()) )
          p.x = p0.x;
        else
          p.x = p1.x;
      }
      break;
    case 1:
      p.x = p1.x;
      p.y = p0.y;
      break;
    default:
      p.x = p1.x;
      break;
    }
    break;
  case ON_Surface::y_iso:
  case ON_Surface::S_iso:
  case ON_Surface::N_iso:
    // horizontal iso curve - lock y coordinate
    coord1_lock = 1;
    switch(coord0_lock)
    {
    case 0:
      p.x = p0.x;
      p.y = p1.y;
      break;
    case 1:
      if ( ON_Surface::x_iso == trim0.m_iso && ON_Surface::x_iso != trim1.m_iso )
        p.y = p1.y; // trim1 is on surface edge
      else if ( ON_Surface::x_iso != trim0.m_iso && ON_Surface::x_iso == trim1.m_iso )
        p.y = p0.y; // trim0 is on surface edge
      else
      {
        // longest one wins
        if ( p0.DistanceTo(trim0.PointAtStart()) >= p1.DistanceTo(trim1.PointAtEnd()) )
          p.y = p0.y;
        else
          p.y = p1.y;
      }
      break;
    default:
      p.x = p1.x;
      break;
    }
    break;
  default:
    switch(coord0_lock)
    {
    case 0:
      p.x = p0.x;
      break;
    case 1:
      p.y = p0.y;
      break;
    }
    break;
  }

  if (ON_ComparePoint(3,0,&p.x,&p0.x))
  {
    trim0.SetEndPoint(p);
  }
  if (ON_ComparePoint(3,0,&p.x,&p1.x))
  {
    trim1.SetStartPoint(p);
  }

  return true;
}

bool ON_Brep::CollapseEdge( int edge_index, bool bCloseTrimGap, int vertex_index  )
{
  ON_BrepEdge* edge = Edge(edge_index);
  if ( 0 == edge )
    return false;
  edge_index = edge->m_edge_index; // clear high bit

  int orig_vid0 = edge->m_vi[0];
  int orig_vid1 = edge->m_vi[1];

  if ( -1 == vertex_index )
    vertex_index = edge->m_vi[0];
  ON_BrepVertex* vertex = Vertex(vertex_index);
  if ( 0 == vertex )
    return false;
  vertex_index = vertex->m_vertex_index; // clear high bit

  int trim_count = edge->m_ti.Count();
  if ( trim_count > 0 )
  {
    ON_SimpleArray<int> ti(trim_count);
    ON_SimpleArray<int> li(trim_count);
    ON_SimpleArray<int> prev_ti(trim_count);
    ON_SimpleArray<int> next_ti(trim_count);
    int i, eti;
    for ( eti = 0; eti < trim_count; eti++ )
    {
      i = edge->m_ti[eti];
      if ( i < 0 || i >= m_T.Count() )
        continue;
      const ON_BrepTrim& trim = m_T[i];
      if ( trim.m_trim_index != i )
        return false;
      if ( trim.m_li < 0 || trim.m_li >= m_L.Count() )
        return false;
      i = PrevTrim(trim.m_trim_index);
      if ( i < 0 || i == trim.m_trim_index )
        return false;
      prev_ti.Append(i);
      i = NextTrim(trim.m_trim_index);
      if ( i < 0 || i == trim.m_trim_index )
        return false;
      next_ti.Append(i);
      ti.Append(trim.m_trim_index);
      li.Append(trim.m_li);
    }

    ChangeVertex(edge->m_vi[0], vertex_index, true);
    ChangeVertex(edge->m_vi[1], vertex_index, true);
    
    trim_count = ti.Count();
    for ( eti = 0; eti < trim_count; eti++ )
    {
      i = ti[eti];
      ON_BrepTrim& trim = m_T[i];
      //ON_BrepLoop& loop = m_L[li[eti]];
      ON_BrepTrim& prev_trim = m_T[prev_ti[eti]];
      ON_BrepTrim& next_trim = m_T[next_ti[eti]];
      DeleteTrim(trim,false);
      if ( bCloseTrimGap )
        CloseTrimGap(prev_trim,next_trim);
    }
  }

  DeleteEdge(*edge,false);
  ON_BrepVertex* V0 = Vertex(orig_vid0);
  if (V0 && V0->EdgeCount() == 0)
    DeleteVertex(*V0);
  ON_BrepVertex* V1 = Vertex(orig_vid1);
  if (V1 && V1->EdgeCount() == 0)
    DeleteVertex(*V1);
  return true;
}

int ON_Brep::RemoveWireEdges( bool bDeleteVertices )
{
  int rc = 0;
  int ei, count = m_E.Count();
  for ( ei = 0; ei < count; ei++ )
  {
    if ( ei == m_E[ei].m_edge_index && 0 == m_E[ei].m_ti.Count() )
    {
      rc++;
      DeleteEdge( m_E[ei], bDeleteVertices );
    }
  }
  return rc;
}

int ON_Brep::RemoveWireVertices()
{
  int rc = 0;
  int vi, count = m_V.Count();
  for ( vi = 0; vi < count; vi++ )
  {
    if ( vi == m_V[vi].m_vertex_index && 0 == m_V[vi].m_ei.Count() )
    {
      rc++;
      DeleteVertex( m_V[vi] );
    }
  }
  return rc;
}


bool ON_Brep::RemoveNesting(
        bool bExtractSingleSegments,
        bool bEdges, 
        bool bTrimCurves
        )
{
  bool rc = false;
  // TODO
  int i, count;
  ON_PolyCurve* polycurve;

  if ( bEdges )
  {
    count = m_C3.Count();
    for ( i = 0; i < count; i++ )
    {
      polycurve = ON_PolyCurve::Cast(m_C3[i]);
      if ( 0 != polycurve )
      {
        if ( polycurve->RemoveNesting() )
          rc = true;
        if ( bExtractSingleSegments && 1 == polycurve->Count() )
        {
          // TODO - extract segment and update edge's proxy information
        }
      }
    }
  }

  if ( bTrimCurves )
  {
    count = m_C2.Count();
    for ( i = 0; i < count; i++ )
    {
      polycurve = ON_PolyCurve::Cast(m_C2[i]);
      if ( 0 != polycurve )
      {
        if ( polycurve->RemoveNesting() )
          rc = true;
        if ( bExtractSingleSegments && 1 == polycurve->Count() )
        {
          // TODO - extract segment and update trims's proxy information
        }
      }
    }
  }

  return rc;
}


static bool IsSlitTrim(const ON_BrepTrim& T)

{
  int tid = T.m_trim_index;
  if (tid < 0)
    return false;

  const ON_BrepLoop* pL = T.Loop();
  if (!pL)
    return false;

  const ON_Brep* pB = T.Brep();
  if (!pB)
    return false;

  const ON_BrepEdge* pE = T.Edge();
  if (!pE || pE->m_edge_index < 0 || pE->m_ti.Count() != 2)
    return false;

  int atid = (pE->m_ti[0] == tid) ? pE->m_ti[1] : pE->m_ti[0];
  if (atid < 0)
    return false;

  const ON_BrepTrim& AT = pB->m_T[atid];
  if (AT.m_trim_index < 0)
    return false;

  if (AT.Loop() != pL)
    return false;

  const ON_Surface* pSrf = T.SurfaceOf();
  if (!pSrf)
    return false;

  double utol = 0.25*pSrf->Domain(0).Length();
  double vtol = 0.25*pSrf->Domain(1).Length();

  bool bRev = (T.m_bRev3d == AT.m_bRev3d) ? false : true;

  ON_2dPoint P(T.PointAtStart());
  ON_2dPoint AP((bRev) ? AT.PointAtEnd() : AT.PointAtStart());

  if (fabs(P[0] - AP[0]) > utol)
    return false;
  if (fabs(P[1] - AP[1]) > vtol)
    return false;

  P = T.PointAtEnd();
  AP = (bRev) ? AT.PointAtStart() : AT.PointAtEnd();

  if (fabs(P[0] - AP[0]) > utol)
    return false;
  if (fabs(P[1] - AP[1]) > vtol)
    return false;

  return true;
}

static bool ON_BrepRemoveSlits(ON_BrepLoop& L)

{
  if (L.m_loop_index < 0)
    return false;
  ON_BrepFace* pF = L.Face();
  if (!pF)
    return false;
  ON_Brep* pB = L.Brep();
  if (!pB)
    return false;
  //Check if anything or everything can be removed.
  ON_SimpleArray<bool> bIsSlit(L.m_ti.Count());
  ON_SimpleArray<int> slits(L.m_ti.Count());
  bool all_slits = true;
  bool some_slits = false;
  int tcount = L.m_ti.Count();
  int i;
  for (i=0; i<tcount; i++){
    ON_BrepTrim& T = pB->m_T[L.m_ti[i]];
    if (IsSlitTrim(T)){
      bIsSlit.Append(true);
      slits.Append(T.m_trim_index);
      some_slits = true;
    }
    else {
      bIsSlit.Append(false);
      all_slits = false;
    }
  }

  if (all_slits){
    pB->DeleteLoop(L, true);
    return true;
  }

  if (!some_slits)
    return false;

  ON_SimpleArray<bool> bUsed = bIsSlit;

  ON_ClassArray<ON_SimpleArray<int> > NewLoops;

  //bool done = false;
  int b = 0;
  while (b < tcount){
    int start_trim = -1;
    for (i=0; i<tcount; i++){
      if (!bUsed[i]){
        start_trim = i;
        break;
      }
    }
    if (start_trim < 0)
      break;
    ON_SimpleArray<int>& nl = NewLoops.AppendNew();
    b++;
    nl.Append(start_trim);
    bUsed[start_trim] = true;
    int next_trim = (start_trim+1)%tcount;
    int c = 0;
    while (c < tcount){
      if (!bUsed[next_trim]){
        nl.Append(next_trim);
        bUsed[next_trim] = true;
        next_trim = (next_trim+1)%tcount;
        c++;
        continue;
      }
      if (next_trim == start_trim)
        break;
      if (bIsSlit[next_trim]){
        int this_trim = next_trim;
        ON_BrepTrim& T = pB->m_T[L.m_ti[next_trim]];
        ON_BrepEdge* pE = T.Edge();
        int atid = (pE->m_ti[0] == T.m_trim_index) ? pE->m_ti[1] : pE->m_ti[0];
        next_trim = -1;
        for (i=0; i<tcount; i++){
          if (L.m_ti[i] == atid){
            next_trim = i;
            break;
          }
        }
        if (next_trim == -1)
          return false;
        if (next_trim > this_trim)
          c += next_trim - this_trim;
        else c += tcount - this_trim + next_trim;
        next_trim = (next_trim+1)%tcount;
        c++;
      }
    }
    if (c >= tcount)
      return false;
  }
  if (b >= tcount)
    return false;

  for (i=0; i<NewLoops.Count(); i++){
    ON_SimpleArray<int>& nl = NewLoops[i];
    int j;
    for (j=0; j<nl.Count(); j++)
      nl[j] = L.m_ti[nl[j]];
  }

  bool bOuter = (L.m_type == ON_BrepLoop::outer) ? true : false;

  for (i=0; i<slits.Count(); i++){
    ON_BrepTrim& T = pB->m_T[slits[i]];
    T.m_li = -1;
    pB->DeleteTrim(T, true);
  }

  //int loop_count = pB->m_L.Count();

  L.m_ti.SetCount(0);
  pB->DeleteLoop(L, true);

  for (i=0; i<NewLoops.Count(); i++){
    ON_BrepLoop& nL = pB->NewLoop(ON_BrepLoop::unknown, *pF);
    ON_SimpleArray<int>& nl = NewLoops[i];
    nL.m_ti = nl;
    int j;
    for (j=0; j<nl.Count(); j++){
      ON_BrepTrim& T = pB->m_T[nl[j]];
      T.m_li = nL.m_loop_index;
    }
    nL.m_type = pB->ComputeLoopType(nL);
    if (bOuter && nL.m_type == ON_BrepLoop::outer){
      int a = pF->m_li[0];
      pF->m_li[0] = nL.m_loop_index;
      for (j=pF->m_li.Count()-1; j>0; j--){
        if (pF->m_li[j] == nL.m_loop_index){
          pF->m_li[j] = a;
          break;
        }
      }
    }
    pB->MatchTrimEnds(nL);
    pB->SetTrimBoundingBoxes(nL, true);
  }
  return true;
}

//This removes all slit trims  from F that are not joined to another face.
//Unlike ON_Brep::RemoveSlits(), this will remove slit pairs from a loop in cases 
//that will result in the creation of more loops. Caller is responsible for calling 
//ON_Brep::Compact() to get rid of deleted trims and loops.

bool ON_BrepRemoveSlits(ON_BrepFace& F)

{
  //For each loop, look for slit pairs that fall between non slits and 
  //break the loop at the pair.
  //After all loops have been split, call ON_Brep::RemoveSlits() on the result.

  if (F.m_face_index < 0)
    return false;
  ON_Brep* pB = F.Brep();
  if (!pB)
    return false;
  bool rc = false;
  int loop_count = F.m_li.Count();
  int i;
  for (i=0; i<loop_count; i++){
    ON_BrepLoop& L = pB->m_L[F.m_li[i]];
    if (L.m_loop_index < 0)
      continue;
    if (ON_BrepRemoveSlits(L))
      rc = true;
  }
  return rc;
}


static void CreateNewTrimList(const ON_BrepLoop& L0, int tid0,//into L0.m_ti
                               const ON_BrepLoop& L1, int tid1,//into L1.m_ti
                               ON_SimpleArray<int>& new_tids //into brep.m_T
                               )

{
  new_tids.Reserve(L0.m_ti.Count() + L1.m_ti.Count() - 2);

  int count = L0.m_ti.Count();
  int i;
  for (i=0; i<count-1; i++)
    new_tids.Append(L0.m_ti[(tid0+1+i)%count]);

  count = L1.m_ti.Count();
  for (i=0; i<count-1; i++)
    new_tids.Append(L1.m_ti[(tid1+1+i)%count]);

  return;
}

int ON_BrepMergeFaces(ON_Brep& B, int fid0, int fid1)

{
  if (fid0 == fid1)
    return -1;

  if (fid0 < 0 || fid0 >= B.m_F.Count())
    return -1;
  ON_BrepFace& F0 = B.m_F[fid0];
  if (F0.m_face_index < 0)
    return -1;

  if (fid1 < 0 || fid1 >= B.m_F.Count())
    return -1;
  ON_BrepFace& F1 = B.m_F[fid1];
  if (F1.m_face_index < 0)
    return -1;

  if (F0.m_si != F1.m_si)
    return -1;

  //Find a manifold edge that joins the two faces and combine the loops by removing 
  //the trims at that edge.

  ON_BrepEdge* pE = 0;

  int li;
  int tid0 = -1, tid1 = -1;
  for (li=0; li<F0.m_li.Count() && !pE; li++){
    ON_BrepLoop& L = B.m_L[F0.m_li[li]];
    int ti;
    for (ti=0; ti<L.m_ti.Count() && !pE; ti++){
      ON_BrepTrim& T0 = B.m_T[L.m_ti[ti]];
      ON_BrepEdge* pEE = T0.Edge();
      if (!pEE || pEE->m_ti.Count() != 2)
        continue;
      tid0 =T0.m_trim_index;
      tid1 = (pEE->m_ti[0] == tid0) ? pEE->m_ti[1] : pEE->m_ti[0];
      if (tid0 < 0 || tid1 < 0)
        continue;
      ON_BrepTrim& T1 = B.m_T[tid1];
      if (T1.FaceIndexOf() == fid1 && T0.m_bRev3d != T1.m_bRev3d 
        && T0.m_iso == T1.m_iso){//Don't combine across seams.
        pE = pEE;
        break;
      }
    }
  }

  if (!pE || tid0 < 0 || tid1 < 0)
    return -1;

  ON_BrepTrim& T0 = B.m_T[tid0];
  ON_BrepTrim& T1 = B.m_T[tid1];

  int lid0 = T0.m_li;
  if (lid0 < 0)
    return -1;
  ON_BrepLoop& L0 = B.m_L[lid0];
  if (L0.m_loop_index < 0)
    return -1;
  if (L0.Face() != &F0)
    return -1;
  int i;
  int ti0 = -1;
  for (i=0; i<L0.m_ti.Count(); i++){
    const ON_BrepTrim& T = B.m_T[L0.m_ti[i]];
    if (T.m_trim_index == tid0){
      ti0 = i;
      break;
    }
  }
  if (ti0 < 0)
    return -1;

  int lid1 = T1.m_li;
  if (lid1 < 0)
    return -1;
  ON_BrepLoop& L1 = B.m_L[lid1];
  if (L1.m_loop_index < 0)
    return -1;
  if (L1.Face() != &F1)
    return -1;
  int ti1 = -1;
  for (i=0; i<L1.m_ti.Count(); i++){
    const ON_BrepTrim& T = B.m_T[L1.m_ti[i]];
    if (T.m_trim_index == tid1){
      ti1 = i;
      break;
    }
  }
  if (ti1 < 0)
    return -1;


  ON_SimpleArray<int> new_tids;
  CreateNewTrimList(L0, ti0, L1, ti1, new_tids);

  ON_BrepLoop* pL;
  ON_BrepLoop* pD;
  ON_BrepFace* pF;
  ON_BrepFace* pDF;
  int rc;
  if (L1.m_type != ON_BrepLoop::inner){
    pL = &L0;
    pD = &L1;
    rc = fid0;
    pF = &F0;
    pDF = &F1;
  }
  else {
    pL = &L1;
    pD = &L0;
    rc = fid1;
    pF = &F1;
    pDF = &F0;
  }
  pL->m_ti = new_tids;
  pL->m_pbox.Destroy();
  pD->m_ti.SetCount(0);
  T0.m_li = -1;
  T1.m_li = -1;
  B.DeleteTrim(T0, true);
  B.DeleteTrim(T1, true);
  B.DeleteLoop(*pD, true);
  for (i=0; i<pL->m_ti.Count(); i++)
    B.m_T[pL->m_ti[i]].m_li = pL->m_loop_index;

  B.MatchTrimEnds(*pL);

  for (i=0; i<pDF->m_li.Count(); i++){
    ON_BrepLoop& ML = B.m_L[pDF->m_li[i]];
    ML.m_fi = rc;
    pF->m_li.Append(ML.m_loop_index);
  }
  pDF->m_li.SetCount(0);
  B.DeleteFace(*pDF, true);
  const ON_Surface* pSrf = B.m_F[rc].SurfaceOf();
  if (pSrf->IsClosed(0) || pSrf->IsClosed(1))
    B.SetTrimTypeFlags(B.m_F[rc]);//Some mateds may have become seams.
  ON_BrepRemoveSlits(B.m_F[rc]);

  B.SetTrimBoundingBoxes(B.m_F[rc], true);

  return rc;

}

typedef int srf_face[2];

static int sfsort(const srf_face* a, const srf_face* b)
{
  if ((*a)[0] < (*b)[0])
    return -1;
  if ((*b)[0] < (*a)[0])
    return 1;
  return 0;
}

bool ON_BrepMergeFaces(ON_Brep& B)

{
  bool rc = false;
  ON_SimpleArray<srf_face> SF(B.m_F.Count());
  int i;
  for (i=0; i<B.m_F.Count(); i++){
    const ON_BrepFace& F = B.m_F[i];
    if (F.m_face_index < 0)
      continue;
    if (F.m_si < 0)
      continue;
    srf_face& sf = SF.AppendNew();
    sf[0] = F.m_si;
    sf[1] = i;
  }
  if (SF.Count() < 2)
    return false;
  SF.QuickSort(sfsort);
  //int si = SF[0][0];
  int start_i = 0;
  while (start_i<SF.Count()){
    int next_i = start_i+1;
    while (next_i<SF.Count() && SF[next_i][0] == SF[start_i][0])
      next_i++;
    if (next_i == start_i+1){
      start_i++;
      continue;
    }
    for (i=start_i; i<next_i-1; i++){
      int j;
      for (j=i+1; j<next_i; j++){
        int new_id = ON_BrepMergeFaces(B, SF[i][1], SF[j][1]);
        if (new_id < 0)
          continue;
        SF[j][1] = new_id;
        rc = true;
        break;
      }
    }
    start_i = next_i;
  }

  ON_BrepMergeAllEdges(B);
  return rc;
}


static int MergeAdjacentEdge(ON_Brep& B, int eid)

{
  ON_BrepEdge& E = B.m_E[eid];
  if (!E.IsValid())
    return -1;

  /*
  if (E.m_edge_user.i >= 0)
    return -1;
    */

  if (E.m_ti.Count() == 0)
    return -1;

  int i;
  for (i=0; i<2; i++){
    int neid = B.NextEdge(eid, i);
    if (neid >= 0){
      ON_BrepEdge* pE = B.CombineContiguousEdges(eid, neid);
      if (pE)
        return pE->m_edge_index;
    }
  }

  return -1;
}

//Merges all possible edges
void ON_BrepMergeAllEdges(ON_Brep& B)

{
  int i;
  int count = B.m_E.Count();
  for (i=0; i<count; i++){
    int eid = i;
    int j = 0;
    while (eid >= 0 && j < count){
      eid = MergeAdjacentEdge(B, eid);
      j++;
    }
  }
  return;
}


//returns false if a naked edge is found.
static bool OrderEdgesAroundClosedVertex(const ON_Brep& B, int vid, ON_2dex* trim_ends)

{
  if (vid<0)
    return false;
  const ON_BrepVertex& V = B.m_V[vid];
  if (V.m_vertex_index < 0)
    return false;
  if (V.m_ei.Count() < 1)
    return false;
  //trim_ends.SetCount(0);
  //trim_ends.Reserve(V.m_ei.Count());
  ON_2dex& first_te = trim_ends[0];
  const ON_BrepEdge& FirstEdge = B.m_E[V.m_ei[0]];
  if (FirstEdge.m_ti.Count() != 2)
    return false;
  first_te.i = FirstEdge.m_ti[0];
  const ON_BrepTrim& FirstTrim = B.m_T[FirstEdge.m_ti[0]];
  int first_edge_end = (FirstEdge.m_vi[0] == vid) ? 0 : 1;
  first_te.j = (FirstTrim.m_bRev3d) ? 1-first_edge_end : first_edge_end;
  int count = 0;
  while (count < V.m_ei.Count()){
    const ON_2dex& lte = trim_ends[count];
    count++;
    int next_ti =  (lte.j) ? B.NextNonsingularTrim(lte.i) : B.PrevNonsingularTrim(lte.i);
    if (next_ti<0)
      return false;
    const ON_BrepTrim& NT = B.m_T[next_ti];
    const ON_BrepEdge* pNE = NT.Edge();
    if (!pNE)
      return false;
    if (pNE->m_ti.Count() != 2)
      return false;
    ON_2dex nte;
    nte.i = (pNE->m_ti[0] == next_ti) ? pNE->m_ti[1] : pNE->m_ti[0];
    const ON_BrepTrim& NTi = B.m_T[nte.i];
    nte.j = (NTi.m_bRev3d == NT.m_bRev3d) ? 1-lte.j : lte.j;
    if (nte.i == first_te.i && nte.j == first_te.j)
      return (count == V.m_ei.Count()) ? true : false;
    int j;
    for (j=1; j<count; j++){
      if (nte.i == trim_ends[j].i && nte.j == trim_ends[j].j)
        return false;
    }
    trim_ends[count] = nte;
  }
  return false;
}

//returns false if there are not exactly 2 naked edge ends at the vertex.
//trim_ends will be pairs of trim ids and ends.  First and last will be naked.
//trim_ends at least as big as vertex's edge count
bool OrderEdgesAroundOpenVertex(const ON_Brep& B, int vid, ON_2dex* trim_ends)

{
  if (vid<0)
    return false;
  const ON_BrepVertex& V = B.m_V[vid];
  if (V.m_vertex_index < 0)
    return false;
  if (V.m_ei.Count() < 2)
    return false;
  int i;
  int start = -1;
  int end = -1;
  for (i=0; i<V.m_ei.Count(); i++){
    const ON_BrepEdge& E = B.m_E[V.m_ei[i]];
    if (E.m_edge_index < 0)
      return false;
    if (E.m_ti.Count() == 1){
      if (start < 0)
        start = i;
      else if (end < 0)
        end = i;
      else
        return false;
    }
  }
  if (start < 0 || end < 0)
    return false;
  const ON_BrepEdge& StartE = B.m_E[V.m_ei[start]];
  bool bAtStart = (StartE.m_vi[0] == vid) ? true : false;
  const ON_BrepTrim& StartT = B.m_T[StartE.m_ti[0]];
  ON_2dex& start_te = trim_ends[0];
  start_te.i = StartE.m_ti[0];
  start_te.j = (bAtStart == StartT.m_bRev3d) ? 1 : 0;
  int count = 0;
  while (count < V.m_ei.Count()){
    const ON_2dex& lte = trim_ends[count];
    count++;
    int next_ti =  (lte.j) ? B.NextNonsingularTrim(lte.i) : B.PrevNonsingularTrim(lte.i);
   if (next_ti<0)
     return false;
   const ON_BrepTrim& NT = B.m_T[next_ti];
   const ON_BrepEdge* pNE = NT.Edge();
   if (!pNE)
     return false;
   if (pNE->m_ti.Count() > 2)
     return false;
   if (pNE->m_ti.Count() == 1){
     if (NT.m_ei == V.m_ei[end]){
       if (count != V.m_ei.Count()-1)
         return false;
       ON_2dex& end_te = trim_ends[count];
       end_te.i = next_ti;
       end_te.j = 1-lte.j;
       return true;
     }
     return false;
   }
   ON_2dex& nte = trim_ends[count];
   nte.i = (pNE->m_ti[0] == next_ti) ? pNE->m_ti[1] : pNE->m_ti[0];
   const ON_BrepTrim& NTi = B.m_T[nte.i];
   nte.j = (NTi.m_bRev3d == NT.m_bRev3d) ? 1-lte.j : lte.j;
  }
  return false;
}

bool ON_OrderEdgesAroundVertex(const ON_Brep& B, int vid,
  ON_SimpleArray<ON_2dex>& trim_ends,
  bool& bClosed)

{
  if(vid<0)
    return false;
  const ON_BrepVertex& V = B.m_V[vid];
  if(V.m_vertex_index < 0)
    return false;
  trim_ends.Reserve(V.m_ei.Count());
  trim_ends.SetCount(V.m_ei.Count());
  return ON_OrderEdgesAroundVertex(B, vid, trim_ends.Array(), bClosed);
}

bool ON_OrderEdgesAroundVertex(const ON_Brep& B, int vid,
                               ON_2dex* trim_ends,//Must be at as big as the edge count at the vertex
                               bool& bClosed)

{
  bClosed = false;
  if (vid<0)
    return false;
  const ON_BrepVertex& V = B.m_V[vid];
  if (V.m_vertex_index < 0)
    return false;
  int i;
  bClosed = true;
  for (i=0; i<V.m_ei.Count(); i++){
    const ON_BrepEdge& E = B.m_E[V.m_ei[i]];
    if (E.m_ti.Count() == 2)
      continue;
    if (E.m_ti.Count() == 1){
      bClosed = false;
      break;
    }
    return false;
  }
  return (bClosed) ? 
    OrderEdgesAroundClosedVertex(B, vid, trim_ends) : OrderEdgesAroundOpenVertex(B, vid, trim_ends);
}



