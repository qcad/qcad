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

///////////////////////////////////////////////////////////////////
//
// ON_MeshFaceSide
// 

#pragma region ON_MeshFaceSide implementation

static ON_MeshFaceSide ON_MeshFaceSide_UnsetInitializer()
{
  ON_MeshFaceSide unset;
  memset(&unset,0,sizeof(unset));
  return unset;
}

const ON_MeshFaceSide ON_MeshFaceSide::Unset = ON_MeshFaceSide_UnsetInitializer();


///////////////////////////////////////////////////////////////////
//
// ON_MeshFaceSide - sort by vertex index
//

#define ON_COMPILING_OPENNURBS_QSORT_FUNCTIONS
#define ON_SORT_TEMPLATE_STATIC_FUNCTION
#define ON_SORT_TEMPLATE_TYPE ON_MeshFaceSide

#define ON_SORT_TEMPLATE_COMPARE ON__MeshFaceSide_compare_m_vi
static int ON_SORT_TEMPLATE_COMPARE( 
        ON_SORT_TEMPLATE_TYPE const * side1, 
        ON_SORT_TEMPLATE_TYPE const * side2 
        )
{
  if ( side1->m_vi[0] < side2->m_vi[0] )
    return -1;
  if ( side1->m_vi[0] > side2->m_vi[0] )
    return 1;
  if ( side1->m_vi[1] < side2->m_vi[1] )
    return -1;
  if ( side1->m_vi[1] > side2->m_vi[1] )
    return 1;
  if ( side1->m_fi < side2->m_fi )
    return -1;
  if ( side1->m_fi > side2->m_fi )
    return 1;
  if ( side1->m_side < side2->m_side )
    return -1;
  if ( side1->m_side > side2->m_side )
    return 1;
  if ( side1->m_dir < side2->m_dir )
    return -1;
  if ( side1->m_dir > side2->m_dir )
    return 1;
  return 0;
}

#define ON_QSORT_FNAME ON__MeshFaceSide_qsort_m_vi
#include "opennurbs_qsort_template.h"

int ON_MeshFaceSide::CompareVertexIndex(
    const ON_MeshFaceSide* a,
    const ON_MeshFaceSide* b
    )
{
  if ( 0 == a )
    a = &ON_MeshFaceSide::Unset;
  if ( 0 == b )
    b = &ON_MeshFaceSide::Unset;
  return ON_SORT_TEMPLATE_COMPARE(a,b);
}

void ON_MeshFaceSide::SortByVertexIndex(
  ON_MeshFaceSide* face_sides,
  size_t face_sides_count
  )
{
  if ( face_sides_count >= 2 && 0 != face_sides )
    ON_QSORT_FNAME( face_sides, face_sides_count );
}

#undef ON_QSORT_FNAME
#undef ON_SORT_TEMPLATE_COMPARE

///////////////////////////////////////////////////////////////////
//
// ON_MeshFaceSide - sort by face index
//

#define ON_SORT_TEMPLATE_HAVE_SHORT_SORT

#define ON_SORT_TEMPLATE_COMPARE ON__MeshFaceSide_compare_m_fi
static int ON_SORT_TEMPLATE_COMPARE( 
        ON_SORT_TEMPLATE_TYPE const * side1, 
        ON_SORT_TEMPLATE_TYPE const * side2 
        )
{
  if ( side1->m_fi < side2->m_fi )
    return -1;
  if ( side1->m_fi > side2->m_fi )
    return 1;
  if ( side1->m_vi[0] < side2->m_vi[0] )
    return -1;
  if ( side1->m_vi[0] > side2->m_vi[0] )
    return 1;
  if ( side1->m_vi[1] < side2->m_vi[1] )
    return -1;
  if ( side1->m_vi[1] > side2->m_vi[1] )
    return 1;
  if ( side1->m_side < side2->m_side )
    return -1;
  if ( side1->m_side > side2->m_side )
    return 1;
  if ( side1->m_dir < side2->m_dir )
    return -1;
  if ( side1->m_dir > side2->m_dir )
    return 1;
  return 0;
}

#define ON_QSORT_FNAME ON__MeshFaceSide_qsort_m_fi
#include "opennurbs_qsort_template.h"

int ON_MeshFaceSide::CompareFaceIndex(
    const ON_MeshFaceSide* a,
    const ON_MeshFaceSide* b
    )
{
  if ( 0 == a )
    a = &ON_MeshFaceSide::Unset;
  if ( 0 == b )
    b = &ON_MeshFaceSide::Unset;
  return ON_SORT_TEMPLATE_COMPARE(a,b);
}

void ON_MeshFaceSide::SortByFaceIndex(
  ON_MeshFaceSide* face_sides,
  size_t face_sides_count
  )
{
  if ( face_sides_count >= 2 && 0 != face_sides )
    ON_QSORT_FNAME( face_sides, face_sides_count );
}

///////////////////////////////////////////////////////////////////
//
// done using sort template for ON_MeshFaceSide
//

#undef ON_COMPILING_OPENNURBS_QSORT_FUNCTIONS
#undef ON_SORT_TEMPLATE_STATIC_FUNCTION
#undef ON_SORT_TEMPLATE_TYPE
#undef ON_QSORT_FNAME
#undef ON_SORT_TEMPLATE_HAVE_SHORT_SORT
#undef ON_QSORT_SHORT_SORT_FNAME

//
// done using sort template for ON_MeshFaceSide
//
///////////////////////////////////////////////////////////////////

#pragma endregion

//
// ON_MeshFaceSide
// 
///////////////////////////////////////////////////////////////////
