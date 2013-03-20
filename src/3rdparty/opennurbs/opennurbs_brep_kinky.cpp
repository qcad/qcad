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


bool ON_Brep::SplitKinkyFaces( 
        double kink_tol_radians,
        bool bCompactIfNeeded
        )
{
  bool rc = true;
  // see if splitting is required
  const int ecount = m_E.Count();
  const int fcount = m_F.Count();
  for (int j=0; j<fcount; j++)
  {
    if ( !SplitKinkyFace(j,kink_tol_radians) )
      rc = false;
  }
  if (bCompactIfNeeded && ( fcount != m_F.Count() || ecount != m_E.Count()) )
  {
    Compact();
  }
  return true;
}


bool ON_Brep::SplitKinkyFace( 
  int,   // face_index - formal parameter intentionally ignored in this virtual function
  double // kink_tol_radians - formal parameter intentionally ignored in this virtual function
  )
{
  // works in RHino SDK - not part of free opennurbs
  return false;
}

bool ON_Brep::SplitKinkyEdge( 
  int edge_index, 
  double kink_tol_radians
  )
{
  // Default kink_tol_radians MUST BE ON_PI/180.0.
  //
  // The default kink tol must be kept in sync with the default for 
  // TL_Brep::SplitKinkyFace() and ON_Brep::SplitKinkyFace().
  // See comments in TL_Brep::SplitKinkyFace() for more details.

  bool rc = true;
  if (kink_tol_radians < ON_ZERO_TOLERANCE) kink_tol_radians = ON_ZERO_TOLERANCE;
  else if (kink_tol_radians > ON_PI - ON_ZERO_TOLERANCE) 
    kink_tol_radians = ON_PI - ON_ZERO_TOLERANCE;
  double atol = cos(kink_tol_radians);
  if (edge_index < 0 || edge_index >= m_E.Count()) return false;
  ON_BrepEdge& E = m_E[edge_index];
  if (E.m_c3i < 0) return false;
  ON_SimpleArray<double> split_t(4);
  double t0 = E.Domain()[0];
  int hint = 0;
  ON_Curve* curve = m_C3[E.m_c3i];
  if (!curve) return false;
  int scount = curve->SpanCount();
  while (split_t.Count() < scount){
    double t;
    if (!E.GetNextDiscontinuity(ON::G1_continuous, t0, E.Domain()[1], 
      &t, &hint, NULL, atol)) break;
    split_t.Append(t);
    t0 = t;
  }
  if (split_t.Count() >= scount) return false;

  if (split_t.Count() == 0) return true;//no kinks

  split_t.Reverse();
  for (int i=0; i<split_t.Count(); i++){
    //if split parameter is near start or end, just adjust domain.
    double t0, t1;
    m_E[edge_index].GetDomain(&t0, &t1);
    if (t1 - t0 < 10.0*ON_ZERO_TOLERANCE) continue;

    //6 Dec 2002 Dale Lear:
    //   I added the relative edge_split_s and trm_split_s tests to detect
    //   attempts to trim a nano-gnats-wisker of the end of a trim.

    // set to true if edge should be trimmed instead of split.
    bool bTrimEdgeEnd = false; 

    double edge_split_s = ON_Interval(t0,t1).NormalizedParameterAt(split_t[i]);
    double trim_split_s = 0.5;

    if (split_t[i] - t0 <= ON_ZERO_TOLERANCE || edge_split_s <= ON_SQRT_EPSILON )
    {
      //m_E[edge_index].ON_CurveProxy::Trim(ON_Interval(split_t[i], t1));
      if ( split_t[i] - t0 <= ON_ZERO_TOLERANCE )
        edge_split_s = 0.0;  // just in case edge_split_s is too large for later test
      bTrimEdgeEnd = true;
      continue;
    }
    else if (t1 - split_t[i] <= ON_ZERO_TOLERANCE || edge_split_s >= 1.0-ON_SQRT_EPSILON)
    {
      //m_E[edge_index].ON_CurveProxy::Trim(ON_Interval(t0, split_t[i]));
      if ( t1 - split_t[i] <= ON_ZERO_TOLERANCE )
        edge_split_s = 1.0; // just in case edge_split_s is too small for later test
      bTrimEdgeEnd = true;
      continue;
    }

    // trim_t[] = corresponding trim parameters
    ON_SimpleArray<double> trim_t(m_E[edge_index].m_ti.Count());


    if ( !bTrimEdgeEnd )
    {
      for (int j=0; j<m_E[edge_index].m_ti.Count(); j++)
      {
        double t;
        if (!GetTrimParameter(m_E[edge_index].m_ti[j], split_t[i], &t)){
          rc = false;
          continue;
        }
        trim_t.Append(t);
        const ON_BrepTrim& trim = m_T[m_E[edge_index].m_ti[j]];
        ON_Interval trim_domain = trim.Domain();
        trim_split_s = trim_domain.NormalizedParameterAt(t);
        if ( trim_split_s <= ON_SQRT_EPSILON || t - trim_domain[0] <= ON_ZERO_TOLERANCE )
        {
          bTrimEdgeEnd = true;
          break;
        }
        if ( trim_split_s >= 1.0-ON_SQRT_EPSILON || trim_domain[1] - t <= ON_ZERO_TOLERANCE )
        {
          bTrimEdgeEnd = true;
          break;
        }
      }
    }

    if ( bTrimEdgeEnd )
    {
      // if we get here, a split parameter we got was too close to
      // the end of the edge or a trim for us to split it.
      if ( edge_split_s <= 0.01 )
      {
        if ( t0 < split_t[i] )
          m_E[edge_index].ON_CurveProxy::Trim(ON_Interval(split_t[i], t1));
      }
      else if ( edge_split_s >= 0.99 )
      {
        if ( split_t[i] < t1 )
          m_E[edge_index].ON_CurveProxy::Trim(ON_Interval(t0, split_t[i]));
      }
      else
      {
        // no decent agreement between trims and edges - continue
        // with other parameters but this is basically the same
        // thing as having SplitEdge() fail.
        rc = false;
      }

      continue;
    }

    if (!SplitEdge(edge_index, split_t[i], trim_t)){
      rc = false;
      continue;
    }
    ON_Curve* new_curve0 = m_E[edge_index].DuplicateCurve();
    if (new_curve0){
      m_E[edge_index].m_c3i = AddEdgeCurve(new_curve0);
      m_E[edge_index].SetProxyCurve(new_curve0);
    }
    ON_Curve* new_curve1 = m_E.Last()->DuplicateCurve();
    if (new_curve1){
      m_E.Last()->m_c3i = AddEdgeCurve(new_curve1);
      m_E.Last()->SetProxyCurve(new_curve1);
    }
  }

  return rc;
}
