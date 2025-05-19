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

#if defined(OPENNURBS_EXPORTS)


//
//
////////////////////////////////////////////////////////////////////////////////

#endif

unsigned int ON_IsRhinoApplicationId(
  ON_UUID id
  )
{
  if (ON_rhino2_id == id)
    return 2;
  if (ON_rhino3_id == id)
    return 3;
  if (ON_rhino4_id == id)
    return 4;
  if (ON_rhino5_id == id)
    return 5;
  if (ON_rhino6_id == id)
    return 6;
  if (ON_rhino7_id == id)
    return 7;
  if (ON_rhino8_id == id)
    return 8;
  return 0;
}

unsigned int ON_IsOpennurbsApplicationId(
  ON_UUID id
  )
{
  if (ON_opennurbs4_id == id)
    return 4;
  if (ON_opennurbs5_id == id)
    return 5;
  if (ON_opennurbs6_id == id)
    return 6;
  if (ON_opennurbs7_id == id)
    return 7;
  if (ON_opennurbs8_id == id)
    return 8;
  return 0;
}

static int ON__isnand(const double* x)
{
  const unsigned char* b = (const unsigned char*)x;
  static unsigned int b7 = 0;
  static unsigned int b6 = 0;
  if (0 == b6)
  {
    // different bytes on
    union
    {
      double x;
      unsigned char b[8];
    } u;  u.x = 2.0; // sign = 0; fraction = 0; exponent = 100 0000 0000 binary

    if (0x40 == u.b[7] && 0 == u.b[0]
      && 0 == u.b[1] && 0 == u.b[2] && 0 == u.b[3]
      && 0 == u.b[4] && 0 == u.b[5] && 0 == u.b[6]
      )
    {
      // little endian doubles
      b7 = 7;
      b6 = 6;
    }
    else if (0x40 == u.b[0] && 0 == u.b[7]
      && 0 == u.b[1] && 0 == u.b[2] && 0 == u.b[3]
      && 0 == u.b[4] && 0 == u.b[5] && 0 == u.b[6]
      )
    {
      // big endian doubles
      b7 = 0;
      b6 = 1;
    }
    else
    {
      // This situation is not handled by this algorithm
      // and that is a bug in the algorithm.
      ON_ERROR("Unexpected bit pattern in double 2.0.");
      // assume little endian doubles
      b7 = 7;
      b6 = 6;
    }
  }

  if (0x7F == (0x7F & b[b7]) && (0xF0 == (0xF0 & b[b6])))
  {
    // All exponent bits are set
    if (0x08 & b[b6])
    {
      // The most significant fraction bit is set.
      // This must be a QNaN
      return 2;
    }
    else
    {
      // The most significant fraction bit is is clear.  
      // If any other fraction bits are set, it's an SNaN
      if (0 != (0x0F & b[b6]))
        return 1;
      if (6 == b6)
      {
        // little endian
        return
          (0 != b[0] || 0 != b[1] || 0 != b[2] || 0 != b[3] || 0 != b[4] || 0 != b[5])
          ? 1  // some fraction bit is set
          : 0; // all fraction bits are clear.
      }
      else
      {
        // big endian
        return
          (0 != b[2] || 0 != b[3] || 0 != b[4] || 0 != b[5] || 0 != b[6] || 0 != b[7])
          ? 1  // some fraction bit is set
          : 0; // all fraction bits are clear.
      }
    }
  }

  return 0; // not a NaN
}

static int ON__isnanf(const float* x)
{
  const unsigned char* b = (const unsigned char*)x;

  static unsigned int b3 = 0;
  static unsigned int b2 = 0;

  if (0 == b2)
  {
    union
    {
      float x;
      unsigned char b[4];
    } u;

    // different bytes on
    u.x = 2.0f; // sign = 0; mantissa = 0; exponent = 1000 0000
    if (0x40 == u.b[3] && 0 == u.b[0] && 0 == u.b[1] && 0 == u.b[2])
    {
      // little endian floats
      b3 = 3; b2 = 2;
    }
    else if (0x40 == u.b[0] && 0 == u.b[3] && 0 == u.b[1] && 0 == u.b[2])
    {
      // big endian floats
      b3 = 0; b2 = 1;
    }
    else
    {
      // This situation is not handled by this algorithm
      // and that is a bug in the algorithm.
      ON_ERROR("Unexpected bit pattern in float 2.0f.");
      // assume little endian floats
      b3 = 3; b2 = 2;
    }
  }

  if (0x7F == (0x7F & b[b3]) && (0x80 == (0x80 & b[b2])))
  {
    // All exponent bits are set

    if (0x7F & b[b2])
    {
      // The most significant fraction bit is set.
      // This must be a QNaN
      return 2;
    }
    else
    {
      // The most significant fraction bit is is clear.  
      // If any other fraction bits are set, it's an SNaN
      if (0 != (0x0F & b[b2]))
        return 1;
      if (2 == b2)
      {
        // little endian
        return
          (0 != b[0] || 0 != b[1])
          ? 1  // some fraction bit is set
          : 0; // all fraction bits are clear.
      }
      else
      {
        // big endian
        return
          (0 != b[2] || 0 != b[3])
          ? 1  // some fraction bit is set
          : 0; // all fraction bits are clear.
      }
    }
  }

  return 0; // not a NaN
}

void ON_DBL_SNAN( double* x)
{
  union 
  {
    double x;
    unsigned char b[8];
  } u;

#if   defined(ON_LITTLE_ENDIAN)
#define i7 7
#define i6 6
#elif defined(ON_BIG_ENDIAN)
#define i7 0
#define i6 1
#else
  unsigned int i7, i6;

  u.x = 2.0; // sign = 0; fraction = 0; exponent = 100 0000 0000 binary

  if ( 0x40 == u.b[7] && 0 == u.b[0]
       && 0 == u.b[1] && 0 == u.b[2] && 0 == u.b[3]
       && 0 == u.b[4] && 0 == u.b[5] && 0 == u.b[6] 
     )
  {
    // little endian doubles
    i7 = 7; i6 = 6;
  }
  else if ( 0x40 == u.b[0]  && 0 == u.b[7]
            && 0 == u.b[1] && 0 == u.b[2] && 0 == u.b[3]
            && 0 == u.b[4] && 0 == u.b[5] && 0 == u.b[6] 
          )
  {
    // big endian doubles
    i7 = 0; i6 = 1;
  }
  else
  {
    // this sitation is not handled by this algorithm
    // and that is a bug in the algorithm.
    ON_ERROR("CPU has unexpected bit pattern in double 2.0.");
    i7 = 0;
    i6 = 0;
    memset(&x,0xFF,sizeof(*x));
    return;
  }
#endif

  // all exponent bits = 1
  // fraction bits = 010...0
  u.b[i7]   = 0x7F; // 0111 1111
  u.b[i6]   = 0xF4; // 1111 0100
  u.b[5]    = 0;    // 0...
  u.b[4]    = 0;
  u.b[3]    = 0;
  u.b[2]    = 0;
  u.b[7-i6] = 0;
  u.b[7-i7] = 0;

#if defined(i7)
#undef i7
#undef i6
#endif


  // must use memcpy().  On Intel FPU, assignment using x = u.x 
  // will set x to qnan and invalid op exception occurs.
  memcpy(x,&u.x,sizeof(*x));
}

void ON_FLT_SNAN( float* x)
{
  union 
  {
    float x;
    unsigned char b[4];
  } u;

#if   defined(ON_LITTLE_ENDIAN)
#define i3 3
#define i2 2
#elif defined(ON_BIG_ENDIAN)
#define i3 0
#define i2 1
#else
  unsigned int i3, i2;

  u.x = 2.0f; // sign = 0; mantissa = 0; exponent = 1000 0000

  if ( 0x40 == u.b[3] && 0 == u.b[0] && 0 == u.b[1] && 0 == u.b[2] )
  {
    // little endian doubles
    i3 = 3; i2 = 2;
  }
  else if ( 0x40 == u.b[0] && 0 == u.b[3] && 0 == u.b[1] && 0 == u.b[2] )
  {
    // big endian doubles
    i3 = 0; i2 = 1;
  }
  else
  {
    // this sitation is not handled by this algorithm
    // and that is a bug in the algorithm.
    ON_ERROR("CPU has unexpected bit pattern in float 2.0f.");
    memset(&x,0xFF,sizeof(*x));
    return;
  }
#endif

  // all exponent bits = 1
  // fraction bits = 011...1
  u.b[i3]   = 0x7F; // 0111 1111
  u.b[i2]   = 0xA0; // 1010 0000
  u.b[3-i2] = 0;    // 0...
  u.b[3-i3] = 0;

#if defined(i3)
#undef i3
#undef i2
#endif

  // must use memcpy().  On Intel FPU, assignment using x = u.x 
  // will set x to qnan and invalid op exception occurs.
  memcpy(x,&u.x,sizeof(*x));
}

bool ON_IsNaNd(double x)
{
  return 0 != ON__isnand(&x);
}

bool ON_IsQNaNd(double x)
{
  return 2 == ON__isnand(&x);
}

bool ON_IsSNaNd(double x)
{
  return 1 == ON__isnand(&x);
}

bool ON_IsNaNf(float x)
{
  return 0 != ON__isnanf(&x);
}

bool ON_IsQNaNf(float x)
{
  return 2 == ON__isnanf(&x);
}

bool ON_IsSNaNf(float x)
{
  return 1 == ON__isnanf(&x);
}

float ON_FloatFromDouble(
  double x
)
{
  if (ON_UNSET_VALUE == x)
    return ON_UNSET_FLOAT;
  if (ON_UNSET_POSITIVE_VALUE == x)
    return ON_UNSET_POSITIVE_FLOAT;
  return static_cast<float>(x);
}

double ON_DoubleFromFloat(
  float x
)
{
  if (ON_UNSET_FLOAT == x)
    return ON_UNSET_VALUE;
  if (ON_UNSET_POSITIVE_FLOAT == x)
    return ON_UNSET_POSITIVE_VALUE;
  return static_cast<double>(x);
}


bool ON_IsNullPtr(const void* ptr)
{
  return (nullptr == ptr);
}

bool ON_IsNullPtr(const ON__UINT_PTR ptr)
{
  return (0 == ptr);
}

bool ON_IsNullPtr(const ON__INT_PTR ptr)
{
  return (0 == ptr);
}


static void ValidateSizesHelper()
{
  static bool bSizedValidated = false;
  if ( !bSizedValidated )
  {
    // Validate int and pointer sizes
    bSizedValidated = true;

    // These conditional expressions are all constant and should
    // all be false.  If any are true, then portions of OpenNURBS
    // code will fail and probably crash.

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_PUSH
// Disable warning C4127: conditional expression is constant
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
#endif

    if ( ON_SIZEOF_POINTER != sizeof(void*) )
    {
      ON_ERROR("ON_SIZEOF_POINTER is not correctly defined.");
    }
    if ( ON_SIZEOF_POINTER != sizeof(ON__INT_PTR) )
    {
      ON_ERROR("ON_INT_PTR is not correctly defined.");
    }
    if ( 1 !=  sizeof(char) )
    {
      ON_ERROR("OpenNURBS assumes sizeof(char) = 1.");
    }
    if ( 2 !=  sizeof(ON__INT16) )
    {
      ON_ERROR("ON__INT16 is not correctly defined.");
    }
    if ( 4 !=  sizeof(ON__INT32) )
    {
      ON_ERROR("ON__INT32 is not correctly defined.");
    }
    if ( 8 !=  sizeof(ON__INT64) )
    {
      ON_ERROR("ON__INT32 is not correctly defined.");
    }
    if ( sizeof(int) > sizeof(void*) )
    {
      ON_ERROR("OpenNURBS assumes sizeof(int) <= sizeof(void*).");
    }
    if ( 4 !=  sizeof(float) )
    {
      ON_ERROR("OpenNURBS assumes sizeof(float) = 4.");
    }
    if ( 8 !=  sizeof(double) )
    {
      ON_ERROR("OpenNURBS assumes sizeof(double) = 8.");
    }

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif
  }
}


unsigned int ON::LibraryStatus()
{
  return ON::m_opennurbs_library_status;
}

void ON::SetLibraryStatus(unsigned int status)
{
  ON::m_opennurbs_library_status = status;
}


void ON::Begin()
{
  if ( 0 != ON::m_opennurbs_library_status )
    return;

  ON::m_opennurbs_library_status = 1;

  ValidateSizesHelper();


#if !defined(OPENNURBS_EXPORTS)
  // Some statically linked library optimizations discard
  // object code that is not explicitly referenced.
  // By explicitly calling all the ON_Object::Cast overrides,
  // we can insure that the class definitions get linked in
  // by making a single call to ON::Begin().  These definitions
  // are needed for the file reading code to work right.
  const ON_Object* p=0;

  ON_Object::Cast(p);
  ON_3dmObjectAttributes::Cast(p);
  ON_Bitmap::Cast(p);
  ON_EmbeddedBitmap::Cast(p);
  ON_WindowsBitmap::Cast(p);
  ON_WindowsBitmapEx::Cast(p);
  ON_DimStyle::Cast(p);
  ON_DocumentUserStringList::Cast(p);
  ON_TextStyle::Cast(p);
  ON_Geometry::Cast(p);
  ON_Annotation::Cast(p);
  ON_Text::Cast(p);
  ON_Leader::Cast(p);
  ON_Dimension::Cast(p);
  ON_DimLinear::Cast(p);
  ON_DimAngular::Cast(p);
  ON_DimRadial::Cast(p);
  ON_DimOrdinate::Cast(p);
  ON_Centermark::Cast(p);
  ON_Brep::Cast(p);
  ON_BrepLoop::Cast(p);
  ON_Curve::Cast(p);
  ON_ArcCurve::Cast(p);
  ON_CurveOnSurface::Cast(p);
  ON_CurveProxy::Cast(p);
  ON_BrepEdge::Cast(p);
  ON_BrepTrim::Cast(p);
  ON_LineCurve::Cast(p);
  ON_NurbsCurve::Cast(p);
  ON_PolyCurve::Cast(p);
  ON_PolylineCurve::Cast(p);
  ON_DetailView::Cast(p);
  ON_Hatch::Cast(p);
  ON_InstanceDefinition::Cast(p);
  ON_InstanceRef::Cast(p);
  ON_Light::Cast(p);
  ON_Mesh::Cast(p);
  ON_MeshComponentRef::Cast(p);
  ON_MorphControl::Cast(p);
  ON_NurbsCage::Cast(p);
  ON_Point::Cast(p);
  ON_BrepVertex::Cast(p);
  ON_PointCloud::Cast(p);
  ON_PointGrid::Cast(p);
  ON_Surface::Cast(p);
  ON_Extrusion::Cast(p);
  ON_NurbsSurface::Cast(p);
  ON_PlaneSurface::Cast(p);
  ON_ClippingPlaneSurface::Cast(p);
  ON_RevSurface::Cast(p);
  ON_SumSurface::Cast(p);
  ON_SurfaceProxy::Cast(p);
  ON_BrepFace::Cast(p);
  ON_OffsetSurface::Cast(p);
  ON_TextDot::Cast(p);
  ON_Viewport::Cast(p);
  ON_Group::Cast(p);
  ON_HatchPattern::Cast(p);
  ON_HistoryRecord::Cast(p);
  ON_Layer::Cast(p);
  ON_Linetype::Cast(p);
  ON_Material::Cast(p);
  ON_Texture::Cast(p);
  ON_TextureMapping::Cast(p);
  ON_UserData::Cast(p);
  ON_UnknownUserData::Cast(p);
  ON_UserStringList::Cast(p);

#endif

  // Lock and mark all constant system components
  ON_ModelComponent::Internal_SystemComponentHelper();

  ON::m_opennurbs_library_status = 2;
}

void ON::End()
{
}

int ON_ClassId::CurrentMark()
{
  return m_mark0;
}

int ON_ClassId::IncrementMark()
{
  m_mark0++;
  return m_mark0;
}

int ON_ClassId::Purge( int mark_value )
{
  // Fundamental openNURBS class ids have a mark value of 0 and cannot be purged.
  int purge_count = 0;
  if ( mark_value > 0 ) {
    ON_ClassId* prev = 0;
    ON_ClassId* next = 0;
    ON_ClassId* p;
    for ( p = m_p0; p; p = next )
    {
      next = p->m_pNext;
      if ( (0x7FFFFFFF & p->m_mark) == mark_value ) {
        purge_count++;
        if ( prev )
          prev->m_pNext = next;
        else
          m_p0 = next;
        p->m_pNext = 0;
      }
      else
        prev = p;
    }
  }
  return purge_count;
}

const ON_ClassId* ON_ClassId::LastClassId()
{
  return m_p1;
}

bool ON_ClassId::PurgeAfter(const ON_ClassId* pClassId)
{
  // If you crash in on the p=p->m_pNext iterator in
  // the for() loop, it is because somebody incorrectly
  // unloaded a dll that contains an ON_OBJECT_IMPLEMENT 
  // macro.
  for (ON_ClassId* p = m_p0; p; p = p->m_pNext)
  {
    if (pClassId == p)
    {
      // All class ids after pClassId are assumed to
      // be bad.
      p->m_pNext = 0;
      m_p1 = p;
      return true;
    }
  }

  ON_ERROR("ON_ClassId::PurgeAfter pClassId is not active");
  return false;
}

//////////////////////////////////////////////////////////////////////////////

static bool g_bDisableDemotion = false;

static void IntToString( int i, char s[7] )
{
  // avoid format printing during early start up
  int j;
  int digit;
  char sdig[10];
  sdig[0] = '0';
  sdig[1] = '1';
  sdig[2] = '2';
  sdig[3] = '3';
  sdig[4] = '4';
  sdig[5] = '5';
  sdig[6] = '6';
  sdig[7] = '7';
  sdig[8] = '8';
  sdig[9] = '9';
  for ( digit = 5; digit > 0; digit-- )
  {
    j = i%10;
    if ( j > 9 || j < 0 )
    {
      s[digit] = '-';
    }
    else
    {
      s[digit] = sdig[j];
    }
    i /= 10;
  }
  s[0] = '-';
  s[6] = 0;
}

ON_ClassId::ON_ClassId( const char* sClassName, 
                        const char* sBaseClassName, 
                        ON_Object* (*create)(),
                        const char* sUUID // UUID in registry format from guidgen
                        ) 
                        : m_pNext(0),
                          m_pBaseClassId(0),
                          m_create(create),
                          m_mark(m_mark0),
                          m_class_id_version(0),
                          m_f1(0),
                          m_f2(0),
                          m_f3(0),
                          m_f4(0),
                          m_f5(0),
                          m_f6(0),
                          m_f7(0),
                          m_f8(0)
{
  // code compiled on or after opennurbs 200703060 calls this constructor
  ConstructorHelper(sClassName,sBaseClassName,sUUID);
  m_mark |= 0x80000000; // This bit of m_mark is a flag that indicates 
                        // the new constructor was called.
}

void ON_ClassId::ConstructorHelper( const char* sClassName, 
                        const char* sBaseClassName, 
                        const char* sUUID // UUID in registry format from guidgen
                        ) 
{
  // Do not initialize "m_class_id_version" or any fields
  // after it in this helper.  See comments in the constructors
  // for more information.
  memset( m_sClassName, 0, sizeof(m_sClassName) );
  memset( m_sBaseClassName, 0, sizeof(m_sBaseClassName) );
  m_uuid = ON_UuidFromString(sUUID);
  if ( sClassName ) {
    strncpy( m_sClassName, sClassName, sizeof(m_sClassName)-1 );
  }
  if ( sBaseClassName ) {
    strncpy( m_sBaseClassName, sBaseClassName, sizeof(m_sBaseClassName)-1 );
  }
  m_pBaseClassId = ClassId( m_sBaseClassName );

  if ( !m_sClassName[0] ) {
    ON_ERROR("ON_ClassId::ON_ClassId() - missing class name");
    return;
  }

  const ON_ClassId* duplicate_class = ClassId( m_sClassName );
  // The m_mark0 > 2 test prevents opennurbs and Rhino from
  // having two ON_Object derived classes that have the same
  // name.  Plug-ins are free to use any name.
  if ( 0 != duplicate_class && m_mark0 > 2 )
  {
    char s[7];
    int ver;
    ON_WARNING("ON_ClassId::ON_ClassId() - class name already in use.  Will append number to make it unique.");
    for ( ver = 1; ver < 10000 && 0 != duplicate_class; ver++ )
    {
      IntToString(ver,s);
      s[6] = 0;
      strncpy( m_sClassName, sClassName, sizeof(m_sClassName)-1 );
      strncat( m_sClassName, s, sizeof(m_sClassName)-1 );
      duplicate_class = ClassId( m_sClassName );
    }
  }

  if ( 0 != duplicate_class )
  {
    // Do NOT permit core classes to have duplicate names.
    ON_ERROR("ON_ClassId::ON_ClassId() - class name already in use.");
    return;
  }

  if (    m_sClassName[0] != 'O'
       || m_sClassName[1] != 'N'
       || m_sClassName[2] != '_'
       || m_sClassName[3] != 'O'
       || m_sClassName[4] != 'b'
       || m_sClassName[5] != 'j'
       || m_sClassName[6] != 'e'
       || m_sClassName[7] != 'c'
       || m_sClassName[8] != 't'
       || m_sClassName[9] != 0 ) {
    if ( !m_sBaseClassName[0] ) 
    {
      ON_ERROR("ON_ClassId::ON_ClassId() - missing baseclass name.");
      return;
    }
  }

  g_bDisableDemotion = true;
  if ( ClassId( m_uuid ) ) 
  {
    g_bDisableDemotion = false;
    ON_ERROR("ON_ClassId::ON_ClassId() - class uuid already in use.");
    return;
  }
  g_bDisableDemotion = false;

  if ( ON_UuidIsNil( m_uuid ) ) {
    ON_ERROR("ON_ClassId::ON_ClassId() - class uuid is nill.");
    return;
  }

  // see if any derived classes need to be updated because their static
  // members got initialized first
  if ( m_sClassName[0] ) 
  {
    for ( ON_ClassId* p = m_p0; p; p = p->m_pNext )
    {
      if ( 
        0 == p->m_pBaseClassId 
        && 0 != p->m_sBaseClassName[0] 
        && 0 == p->m_sBaseClassName[sizeof(p->m_sBaseClassName)/sizeof(p->m_sBaseClassName[0]) - 1] 
        )
      {
        if ( 0 == strcmp( m_sClassName, p->m_sBaseClassName ) )
          p->m_pBaseClassId = this;
      }
    }
  }

  // Append to the list of class ids
  if ( m_p0 && m_p1 )
  {
    m_p1->m_pNext = this;
    m_p1 = this;
  }
  else
  {
    // first class id
    m_p0 = this;
  }
  m_p1 = this;
  m_p1->m_pNext = 0;
}

ON_ClassId::~ON_ClassId()
{}

static ON_UUID s_most_recent_class_id_create_uuid;

ON_UUID ON_GetMostRecentClassIdCreateUuid()
{
  return s_most_recent_class_id_create_uuid;
}

ON_Object* ON_ClassId::Create() const
{
  // Save the uuid so that Rhino's .NET SDK
  // can create appropriate class.  The C++
  // opennurbs toolkit never uses this value.
  s_most_recent_class_id_create_uuid = m_uuid;
  return m_create ? m_create() : 0;
}

const ON_ClassId* ON_ClassId::ClassId( const char* sClassName )
{
  // static member function
  // search list of class ids for one with a matching class name
  ON_ClassId* p;
  const char* s0;
  const char* s1;
  if ( !sClassName || !sClassName[0] || sClassName[0] == '0' )
    return nullptr;
  for(p = m_p0; p; p = p->m_pNext) {
    // avoid strcmp() because it crashes on nullptr strings
    s0 = sClassName;
    s1 = p->m_sClassName;
    if ( s0 && s1 && *s0 ) {
      while ( *s0 && *s0 == *s1 )
        {s0++; s1++;}
      if ( !(*s0) && !(*s1) )
        break;
    }
    else {
      break;
    }
  }
  return p;
}


const ON_ClassId* ON_ClassId::ClassId( ON_UUID uuid )
{
  // static member function
  // search list of class ids for one with a matching typecode
  const ON_ClassId* p;
  for(p = m_p0; p; p = p->m_pNext) 
  {
    if ( !ON_UuidCompare(&p->m_uuid,&uuid) )
      break;
  }

  if ( nullptr == p && false == g_bDisableDemotion) 
  {
    // enable OpenNURBS toolkit to read files that contain old uuids even when
    // old class definitions are not loaded.

    // 5EAF1119-0B51-11d4-BFFE-0010830122F0 = TL_NurbsCurve
    ON_UUID nc0 = {0x5EAF1119,0x0B51,0x11d4,{0xBF,0xFE,  0x00,0x10,0x83,0x01,0x22,0xF0}};

    // 76A709D5-1550-11d4-8000-0010830122F0 = old nurbs curve
    ON_UUID nc1 = {0x76A709D5,0x1550,0x11d4,{0x80,0x00,  0x00,0x10,0x83,0x01,0x22,0xF0}};

    // 4760C817-0BE3-11d4-BFFE-0010830122F0 = TL_NurbsSurface
    ON_UUID ns0 = {0x4760C817,0x0BE3,0x11d4,{0xBF,0xFE,  0x00,0x10,0x83,0x01,0x22,0xF0}};

    // FA4FD4B5-1613-11d4-8000-0010830122F0 = old nurbs surface
    ON_UUID ns1 = {0xFA4FD4B5,0x1613,0x11d4,{0x80,0x00,  0x00,0x10,0x83,0x01,0x22,0xF0}};

    // EF638317-154B-11d4-8000-0010830122F0 = old poly curve
    ON_UUID pc0 = {0xEF638317,0x154B,0x11d4,{0x80,0x00,  0x00,0x10,0x83,0x01,0x22,0xF0}};

    // 0705FDEF-3E2A-11d4-800E-0010830122F0 = old trimmed surface
    ON_UUID br0 = {0x0705FDEF,0x3E2A,0x11d4,{0x80,0x0E,  0x00,0x10,0x83,0x01,0x22,0xF0}};

    // 2D4CFEDB-3E2A-11d4-800E-0010830122F0 = old b-rep
    ON_UUID br1 = {0x2D4CFEDB,0x3E2A,0x11d4,{0x80,0x0E,  0x00,0x10,0x83,0x01,0x22,0xF0}};

    // F06FC243-A32A-4608-9DD8-A7D2C4CE2A36 = TL_Brep
    ON_UUID br2 = {0xF06FC243,0xA32A,0x4608,{0x9D,0xD8, 0xA7,0xD2,0xC4,0xCE,0x2A,0x36}};

    // 0A8401B6-4D34-4b99-8615-1B4E723DC4E5 = TL_RevSurface
    ON_UUID revsrf = { 0xa8401b6, 0x4d34, 0x4b99, { 0x86, 0x15, 0x1b, 0x4e, 0x72, 0x3d, 0xc4, 0xe5 } };

    // 665F6331-2A66-4cce-81D0-B5EEBD9B5417 = TL_SumSurface
    ON_UUID sumsrf = { 0x665f6331, 0x2a66, 0x4cce, { 0x81, 0xd0, 0xb5, 0xee, 0xbd, 0x9b, 0x54, 0x17 } };

    if      ( !ON_UuidCompare( &uuid, &nc0 ) || !ON_UuidCompare( &uuid, &nc1 ) )
      p = &ON_CLASS_RTTI(ON_NurbsCurve);
    else if ( !ON_UuidCompare( &uuid, &ns0 ) || !ON_UuidCompare( &uuid, &ns1 ) )
      p = &ON_CLASS_RTTI(ON_NurbsSurface);
    else if ( !ON_UuidCompare( &uuid, &pc0 ) )
      p = &ON_CLASS_RTTI(ON_PolyCurve);
    else if ( !ON_UuidCompare( &uuid, &br0 ) || !ON_UuidCompare( &uuid, &br1 ) || !ON_UuidCompare( &uuid, &br2 ) )
      p = &ON_CLASS_RTTI(ON_Brep);
    else if ( !ON_UuidCompare( &uuid, &revsrf ) )
      p = &ON_CLASS_RTTI(ON_RevSurface);
    else if ( !ON_UuidCompare( &uuid, &sumsrf ) )
      p = &ON_CLASS_RTTI(ON_SumSurface);
    else
    {
      // The p = nullptr line does nothing (p is already nullptr) but, if you're working on
      // file reading bugs or other cases that involving rtti bugs, then it's a good 
      // location for a debugger breakpoint.
      p = nullptr;
    }
  }
  return p;
}

class ON__ClassIdDumpNode
{
public:
  ON__ClassIdDumpNode();
  ~ON__ClassIdDumpNode();
  const ON_ClassId* m_class_id;
  class ON__ClassIdDumpNode* m_parent_node;
  int m_depth;
  ON_SimpleArray<class ON__ClassIdDumpNode*> m_child_nodes;
  int CompareClassUuid( const class ON__ClassIdDumpNode& ) const;
  int CompareClassName( const class ON__ClassIdDumpNode& ) const;
  bool Dump( int depth, ON_TextLog& text_log );
};

ON__ClassIdDumpNode::ON__ClassIdDumpNode() 
{
  m_class_id=0;
  m_parent_node=0;
  m_depth=0;
};

ON__ClassIdDumpNode::~ON__ClassIdDumpNode() 
{
}

int ON__ClassIdDumpNode::CompareClassUuid( const class ON__ClassIdDumpNode& other ) const
{
  int rc = 0;
  const ON_ClassId* a = m_class_id;
  const ON_ClassId* b = other.m_class_id;
  if ( a != b )
  {
    if ( 0 == a )
    {
      rc = -1;
    }
    else if ( 0 == b )
      rc = 1;
    else
    {
      rc = ON_UuidCompare(a->Uuid(),b->Uuid());
      if ( 0 == rc )
      {
        rc = CompareClassName(other);
      }
    }
  }
  return rc;
}

int ON__ClassIdDumpNode::CompareClassName( const class ON__ClassIdDumpNode& other ) const
{
  int rc = 0;
  const ON_ClassId* a = m_class_id;
  const ON_ClassId* b = other.m_class_id;
  if ( a != b )
  {
    if ( 0 == a )
    {
      rc = -1;
    }
    else if ( 0 == b )
      rc = 1;
    else
    {
      const char* a_name = a->ClassName();
      const char* b_name = b->ClassName();
      if ( 0 == a_name )
      {
        if ( 0 == b_name )
        {
          rc = b->Mark() - a->Mark();
          if ( 0 == rc )
            rc = ON_UuidCompare(a->Uuid(),b->Uuid());
        }
        else
          rc = -1;
      }
      else if ( 0 == b_name )
      {
        rc = 1;
      }
      else
      {
        rc = on_stricmp(a_name,b_name);
        if ( 0 == rc )
        {
          rc = strcmp(a_name,b_name);
          if ( 0 == rc )
          {
            rc = b->Mark() - a->Mark();
            if ( 0 == rc )
              rc = ON_UuidCompare(a->Uuid(),b->Uuid());
          }
        }
      }
    }
  }
  return rc;
}


static int ON__ClassIdDumpNode_CompareUuid( const ON__ClassIdDumpNode* a, const ON__ClassIdDumpNode* b )
{
  int rc = 0;
  if ( 0 == a )
  {
    rc = (0 == b) ? 0 : -1;
  }
  else if ( 0 == b )
  {
    rc = 1;
  }
  else
  {
    rc = a->CompareClassUuid(*b);
  }
  return rc;
}

static int ON__ClassIdDumpNode_CompareName( ON__ClassIdDumpNode *const* a, ON__ClassIdDumpNode *const* b )
{
  int rc = 0;
  if ( 0 == a )
  {
    rc = (0 == b) ? 0 : -1;
  }
  else if ( 0 == b )
  {
    rc = 1;
  }
  else
  {
    rc = (*a)->CompareClassName(*(*b));
  }
  return rc;
}

bool ON__ClassIdDumpNode::Dump( int depth, ON_TextLog& text_log )
{
  bool rc = true;
  if ( 0 == m_class_id || m_depth != 0 || depth < 1)
    rc = false;
  else
  {
    m_depth = depth;
    const char* class_name = m_class_id->ClassName();
    if ( 0 == class_name )
    {
      class_name = "!!ERROR!!";
      rc = false;
    }
    text_log.Print("%s::ClassId: ",m_class_id->ClassName());
    text_log.Print( "mark=%d ",m_class_id->Mark() );
    text_log.Print( m_class_id->Uuid() );
    text_log.Print("  (%08x)\n",m_class_id);
    int i, count = m_child_nodes.Count();
    if ( count > 0 )
    {
      // dump children names alphabetically
      m_child_nodes.QuickSort( ON__ClassIdDumpNode_CompareName );

      text_log.PushIndent();
      for ( i = 0; i < count; i++ )
      {
        ON__ClassIdDumpNode* child_node = m_child_nodes[i];
        if ( 0 == child_node )
          rc = false;
        else
        {
          if ( !child_node->Dump(depth+1,text_log) )
            rc = false;
        }
      }
      text_log.PopIndent();
    }
  }
  return rc;
}

void ON_ClassId::Dump( ON_TextLog& dump )
{
  int i, j, count = 0;
  const ON_ClassId* p;
  for(p = m_p0; p && count < 1000000; p = p->m_pNext) 
  {
    count++;
  }
  if ( 0 != p )
  {
    dump.Print("ON_ClassId::m_p0 list is damaged.\n");
  }
  else
  {
    ON__ClassIdDumpNode tmp_node;
    ON_ClassArray<ON__ClassIdDumpNode> nodes(count);
    for(p = m_p0; p; p = p->m_pNext) 
    {
      ON__ClassIdDumpNode& node = nodes.AppendNew();
      node.m_class_id = p;
    }

    // sort nodes by class id's uuid
    nodes.QuickSort(ON__ClassIdDumpNode_CompareUuid);

    // fill in m_parent_node and m_child_nodes[]
    for ( i = 0; i < count; i++ )
    {
      ON__ClassIdDumpNode& node = nodes[i];
      p = node.m_class_id;
      if ( 0 != p )
      {
        tmp_node.m_class_id = p->BaseClass();
        j = nodes.BinarySearch(&tmp_node,ON__ClassIdDumpNode_CompareUuid);
        if ( j >= 0 && i != j)
        {
          ON__ClassIdDumpNode& base_node = nodes[j];
          node.m_parent_node = &base_node;
          base_node.m_child_nodes.Append(&node);
        }
      }      
    }

    // print class tree
	  tmp_node.m_class_id = &ON_CLASS_RTTI(ON_Object);
    i = nodes.BinarySearch(&tmp_node,ON__ClassIdDumpNode_CompareUuid);
    bool rc = false;
    if ( i >= 0 )
    {
      // recursively dump class tree
      rc = nodes[i].Dump(1,dump);
      for ( i = 0; i < count && rc; i++ )
      {
        if ( nodes[i].m_depth <= 0 )
          rc = false;
      }
    }

    if (!rc)
    {
      // should never happen
      for(p = m_p0; p; p = p->m_pNext) 
      {
        dump.Print("%s::ClassId: ",p->m_sClassName);
        dump.Print( "mark=%d ",p->m_mark );
        dump.Print( p->m_uuid );
        dump.Print("  (%08x)\n",p);
      }
    }
  }
}

const char* ON_ClassId::ClassName() const
{
  return m_sClassName;
}

const char* ON_ClassId::BaseClassName() const
{
  return m_sBaseClassName;
}

ON_UUID ON_ClassId::Uuid() const
{
  return m_uuid;
}

int ON_ClassId::Mark() const
{
  return (m_mark & 0x7FFFFFFF);
}

unsigned int ON_ClassId::ClassIdVersion() const
{
  return (0 != (m_mark & 0x80000000)) ? m_class_id_version : 0;
}


const ON_ClassId* ON_ClassId::BaseClass() const
{
  return m_pBaseClassId;
}

bool ON_ClassId::IsDerivedFrom( const ON_ClassId* pBaseClassId ) const
{
  // determine if this is derived from pBaseClassId
  bool b = false;
  if ( pBaseClassId ) {
    const ON_ClassId* p = this;
    for(;p;) {
      if ( p == pBaseClassId ) {
        b = true;
        break;
      }
      p = p->m_pBaseClassId;
    }
  }
  return b;
}

//////////////////////////////////////////////////////////////////////////////

ON_VIRTUAL_OBJECT_IMPLEMENT(ON_Object,0,"60B5DBBD-E660-11d3-BFE4-0010830122F0");

ON_Object::ON_Object() ON_NOEXCEPT
: m_userdata_list(0)
{}

ON_Object::ON_Object(const ON_Object& src)
  : m_userdata_list(0)
{
  this->CopyUserData(src);
}

ON_Object& ON_Object::operator=(const ON_Object& src)
{
  // DO NOT MODIFY this->m_mempool here
  if ( this != &src ) 
  {
    this->PurgeUserData();
    this->CopyUserData(src);
  }
  return *this;
}

#if defined(ON_HAS_RVALUEREF)
ON_Object::ON_Object( ON_Object&& src ) ON_NOEXCEPT
  : m_userdata_list(0)
{
  this->MoveUserData(src);
}

ON_Object& ON_Object::operator=( ON_Object&& src )
{
  if ( this != &src )
  {
    this->PurgeUserData();
    this->MoveUserData(src);
  }
  return *this;
}
#endif

ON_Object::~ON_Object()
{
  this->PurgeUserData();
}

// DO NOT PUT THIS DECL IN A HEADER FILE.
// THIS FUNCTION IS USED IN SPECIAL CIRCUMSTANCES
// AND IS NOT INTENDED TO BE CALLED.
ON_DECL bool ON__EnableLeakUserData(bool bEnable);

static bool g__bLeakUserData = false;

bool ON__EnableLeakUserData(bool bEnable)
{
  bool b = bEnable;
  g__bLeakUserData = bEnable ? true : false;
  return b;
}

void ON_Object::EmergencyDestroy()
{
  m_userdata_list = 0;
}


void ON_Object::PurgeUserData()
{
  ON_UserData* p;
  ON_UserData* next;
  bool bDeleteUserData;
  if ( 0 != (next=m_userdata_list) ) 
  {
    m_userdata_list = 0;
    bDeleteUserData = !g__bLeakUserData;
    while( 0 != (p=next) ) 
    {
      next = p->m_userdata_next;
      p->m_userdata_owner = 0;
      p->m_userdata_next = 0;
      if ( bDeleteUserData )
        delete p;
    }
  }
}

bool ON_Object::AttachUserData( ON_UserData* p )
{
  bool rc = false;
  if ( p 
       && nullptr == p->m_userdata_owner
       && ON_UuidCompare( &ON_nil_uuid, &p->m_userdata_uuid) 
       && nullptr == GetUserData( p->m_userdata_uuid )
       ) {
    if ( p->IsUnknownUserData() ) {
      // make sure we have valid user data - the first beta release of Rhino 2.0 
      // created empty user data.
      ON_UnknownUserData* uud = ON_UnknownUserData::Cast(p);
      if (uud)
        rc = uud->IsValid();
      if ( !rc ) {
        ON_ERROR("ON_Object::AttachUserData() - attempt to attach invalid UnknownUserData.");
      }
    }
    else
      rc = true;
    if (rc) 
    {
      p->m_userdata_owner = this;
      p->m_userdata_next = m_userdata_list;
      m_userdata_list = p;
    }
  }
  return rc;
}

bool ON_Object::DetachUserData( ON_UserData* p )
{
  bool rc = false;
  if ( p && p->m_userdata_owner == this ) 
  {
    ON_UserData* prev = 0;
    ON_UserData* ud = m_userdata_list;
    while ( ud ) 
    {
      if ( ud == p ) 
      {
        if ( prev )
          prev->m_userdata_next = ud->m_userdata_next;
        else
          m_userdata_list = ud->m_userdata_next;
        ud->m_userdata_owner = 0;
        ud->m_userdata_next = 0;
        rc = true;
        break;
      }
      prev = ud;
      ud = ud->m_userdata_next;
    }
  }
  return rc;
}


ON_UserData* ON_Object::GetUserData( const ON_UUID& userdata_uuid ) const
 {
  ON_UserData* prev = nullptr;
  ON_UserData* p;
  for ( p = m_userdata_list; p; prev = p, p = p->m_userdata_next ) 
  {
    if ( !ON_UuidCompare( &p->m_userdata_uuid, &userdata_uuid ) ) 
    {
      if ( p->IsUnknownUserData() ) 
      {
        // See if we can convert this unknown user data into something useful.
        // Unknown user data is created when a 3dm archive is read and
        // the definition of the specific user data class is not loaded.
        // If something is getting around to asking for a specific kind
        // of user data, the class definition has probably be dynamically
        // loaded.
        ON_UnknownUserData* uud = ON_UnknownUserData::Cast(p);
        if ( uud ) {
          ON_UserData* realp = uud->Convert();
          if ( realp ) 
          {
            // replace unknown user data with the real thing
            if ( prev )
              prev->m_userdata_next = realp;
            else if ( p == m_userdata_list ) 
            {
              // little white lie to attach the "real" user
              // data to the object in place of the unknown
              // user data.
              ON_Object* pNotConst = const_cast<ON_Object*>(this);
              pNotConst->m_userdata_list = realp;
              realp->m_userdata_owner = pNotConst; // Dale Lear added 22 Jan 2004 to fix I/O bug 
            }
            realp->m_userdata_next = p->m_userdata_next;
            p->m_userdata_next = 0;
            p->m_userdata_owner = 0;
            delete p;
            p = realp;
          }
        }
      }
      break;
    }
  }
  return p; 
}

ON_UserData* ON_Object::FirstUserData() const
{
  return m_userdata_list;
}


void ON_Object::TransformUserData( const ON_Xform& x )
{
  ON_UserData *p, *next;
  for ( p = m_userdata_list; p; p = next ) {
    next = p->m_userdata_next;
    if ( !p->Transform(x) )
      delete p;
  }
}

ON_UserData* ON_Object::TransferUserDataItem(
  const ON_UserData* source_ud_copy_this,
  ON_UserData* source_ud_move_this,
  bool bPerformConflictCheck,
  ON_Object::UserDataConflictResolution userdata_conflict_resolution
  )
{
  const ON_UserData* source_ud; // do not initialize so compiler will detect future bugs

  if (nullptr != source_ud_move_this)
  {
    if (nullptr != source_ud_copy_this)
    {
      ON_ERROR("At most one source_ud pointer can be not null.");
      return nullptr;
    }
    if (nullptr != source_ud_move_this->m_userdata_owner || nullptr != source_ud_move_this->m_userdata_next)
    {
      ON_ERROR("Cannot move userdata that is attached to another object.");
      return nullptr;
    }
    source_ud = source_ud_move_this;
  }
  else if ( nullptr != source_ud_copy_this )
  {
    if (this == source_ud_copy_this->m_userdata_owner)
    {
      ON_ERROR("source_ud_copy_this is already attached to this object.");
      return nullptr;
    }
    source_ud = source_ud_copy_this;
  }
  else
  {
    // nothing to do
    return nullptr;
  }

  if (source_ud->IsUnknownUserData())
  {
    // make sure we have valid user data - the first beta release of Rhino 2.0 
    // created empty user data.
    const ON_UnknownUserData* uud = ON_UnknownUserData::Cast(source_ud);
    if (nullptr == uud && false == uud->IsValid())
    {
      return nullptr;
    }
  }
  
  ON_UserData* dest_ud = bPerformConflictCheck ? GetUserData(source_ud->m_userdata_uuid) : nullptr;

  bool bDeleteDestinationItem = false;
  bool bTransferSourceItem; // no initialization
  if (nullptr == dest_ud)
  {
    bTransferSourceItem = true;
  }
  else
  {
    switch (userdata_conflict_resolution)
    {
    case ON_Object::UserDataConflictResolution::destination_object:
      bTransferSourceItem = false;
      break;

    case ON_Object::UserDataConflictResolution::source_object:
      bTransferSourceItem = true;
      break;

    case ON_Object::UserDataConflictResolution::source_copycount_gt:
      bTransferSourceItem = (source_ud->m_userdata_copycount > dest_ud->m_userdata_copycount);
      break;

    case ON_Object::UserDataConflictResolution::source_copycount_ge:
      bTransferSourceItem =  (source_ud->m_userdata_copycount >= dest_ud->m_userdata_copycount);
      break;

    case ON_Object::UserDataConflictResolution::destination_copycount_gt:
      bTransferSourceItem = (dest_ud->m_userdata_copycount > source_ud->m_userdata_copycount);
      break;

    case ON_Object::UserDataConflictResolution::destination_copycount_ge:
      bTransferSourceItem =  (dest_ud->m_userdata_copycount >= source_ud->m_userdata_copycount);
      break;

    case ON_Object::UserDataConflictResolution::delete_item:
      bTransferSourceItem = false;
      bDeleteDestinationItem = true;
      break;

    default:
      bTransferSourceItem = false;
      break;
    }
  }

  if (false == bTransferSourceItem)
  {
    if (bDeleteDestinationItem && nullptr != dest_ud)
    {
      delete dest_ud;
    }
    return nullptr;
  }


  if (nullptr != source_ud_copy_this)
  {
    ON_Object* p = source_ud_copy_this->Duplicate();
    if ( nullptr == p )
      return nullptr;
    source_ud_move_this = ON_UserData::Cast(p);

    if (nullptr == source_ud_move_this)
    {
      delete p;
      return nullptr;
    }
    source_ud_move_this->m_userdata_owner = nullptr;
  }

  if (nullptr == source_ud_move_this)
  {
    ON_ERROR("Bug in the code above.");
    return nullptr;
  }

  if (nullptr != dest_ud)
  {
    delete dest_ud;
  }

  source_ud_move_this->m_userdata_owner = this;
  source_ud_move_this->m_userdata_next = m_userdata_list;
  m_userdata_list = source_ud_move_this;
  
  return m_userdata_list;
};

unsigned int ON_Object::CopyUserData(
  const ON_Object& source_object,
  ON_UUID source_userdata_item_id,
  ON_Object::UserDataConflictResolution userdata_conflict_resolution
  )
{
  unsigned int copied_item_count = 0;

  if (this == &source_object)
    return copied_item_count;

  const bool bPerformConflictCheck = (nullptr != m_userdata_list);

  const bool bIgnoreUserDataItemId = (ON_nil_uuid == source_userdata_item_id);

  for (const ON_UserData* source_ud = source_object.m_userdata_list; nullptr != source_ud; source_ud = source_ud->m_userdata_next)
  {
    if (source_ud->m_userdata_copycount <= 0)
      continue;
    if (bIgnoreUserDataItemId || source_ud->m_userdata_uuid == source_userdata_item_id)
    {
      if (nullptr != TransferUserDataItem(source_ud, nullptr, bPerformConflictCheck, userdata_conflict_resolution))
        copied_item_count++;
    }
  }
  return copied_item_count;
}


unsigned int ON_Object::MoveUserData(
  ON_Object& source_object,
  ON_UUID source_userdata_item_id,
  ON_Object::UserDataConflictResolution userdata_conflict_resolution,
  bool bDeleteAllSourceItems)
{
  unsigned int moved_item_count = 0;

  const bool bIgnoreUserDataItemId = (ON_nil_uuid == source_userdata_item_id);

  if ( nullptr == m_userdata_list && bIgnoreUserDataItemId )
  {
    // quick and simple when the "this" doesn't
    // have any user data.
    if ( nullptr != source_object.m_userdata_list )
    {
      m_userdata_list = source_object.m_userdata_list;
      source_object.m_userdata_list = nullptr;
      for (ON_UserData* dest_ud = m_userdata_list; nullptr != dest_ud; dest_ud = dest_ud->m_userdata_next)
      {
        dest_ud->m_userdata_owner = this;
        moved_item_count++;
      }
    }
  }
  else
  {    
    // Carefully move userdata an item at a time from source_object to "this"
    const bool bPerformConflictCheck = true;
    ON_UserData* source_ud_next = source_object.m_userdata_list;
    source_object.m_userdata_list = nullptr;
    ON_UserData* source_object_userdata_last = nullptr;
    for ( ON_UserData* source_ud = source_ud_next; nullptr != source_ud; source_ud = source_ud_next)
    {
      source_ud_next = source_ud->m_userdata_next;
      source_ud->m_userdata_next = nullptr;
      source_ud->m_userdata_owner = nullptr;

      if (bIgnoreUserDataItemId || source_ud->m_userdata_uuid == source_userdata_item_id)
      {
        if (TransferUserDataItem(nullptr, source_ud, bPerformConflictCheck, userdata_conflict_resolution))
        {
          moved_item_count++;
          continue;
        }
      }

      // The transfer did not occur.  Resolve state of orphaned source_ud.
      if (nullptr != source_ud->m_userdata_owner || nullptr != source_ud->m_userdata_next)
      {
        ON_ERROR("There is a serious bug in this code.");
        continue;
      }
      if (bDeleteAllSourceItems)
      {
        // delete the orphan
        delete source_ud;
      }
      else
      {
        // reattach the orphan to source_object
        source_ud->m_userdata_owner = &source_object;
        if (nullptr == source_object.m_userdata_list)
        {
          source_object.m_userdata_list = source_ud;
        }
        else if (nullptr != source_object_userdata_last)
        {
          source_object_userdata_last->m_userdata_next = source_ud;
        }
        source_object_userdata_last = source_ud;
      }
    }
  }

  return moved_item_count;
}


void ON_Object::CopyUserData( const ON_Object& src )
{
  CopyUserData(src,ON_nil_uuid,ON_Object::UserDataConflictResolution::destination_object);
}

void ON_Object::MoveUserData( ON_Object& src )
{
  MoveUserData(src,ON_nil_uuid,ON_Object::UserDataConflictResolution::destination_object,true);
}



bool ON_Object::UpdateReferencedComponents(
  const class ON_ComponentManifest& source_manifest,
  const class ON_ComponentManifest& destination_manifest,
  const class ON_ManifestMap& manifest_map
  )
{
  return true;
}

void ON_Object::MemoryRelocate()
{
  // When the memory location of an ON_Object changes,
  // the back-pointers on its user data need to be updated.
  ON_UserData* ud;
  for ( ud = m_userdata_list; ud; ud = ud->m_userdata_next )
  {
    ud->m_userdata_owner = this;
  }
}

bool ON_Object::IsKindOf( const ON_ClassId* pBaseClassId ) const
{
  bool b = false;
  const ON_ClassId* p = ClassId();
  if ( p )
    b = p->IsDerivedFrom( pBaseClassId );
  return b;
}


ON::object_type ON_Object::ObjectType() const
{
  // virtual function that is generally overridden
  return ON::unknown_object_type;
}

ON_UUID ON_Object::ModelObjectId() const
{
  return ON_nil_uuid;
}

ON_UUID ON_Light::ModelObjectId() const
{
  return m_light_id;
}

unsigned int ON_Object::SizeOf() const
{
  unsigned int sz = sizeof(*this);
  const ON_UserData* ud = m_userdata_list;
  while ( ud )
  {
    sz += ud->SizeOf();
    ud = ud->m_userdata_next;
  }
  return sz;
}

ON__UINT32 ON_Object::DataCRC(ON__UINT32 current_remainder) const
{
  // do not include user data.
  return current_remainder;
}

bool ON_Object::IsValid(ON_TextLog* text_log) const
{
  return true;
}

bool ON_Object::ThisIsNullptr(
  bool bSilentError
) const
{
  // CLang warns that these tests may be omitted because in "well-defined C++ code"
  // they are always false. 
  //
  // Earth to CLang: 
  //   This tool to find code that is not well formed, alert us to that fact, 
  //   but not potentiall not crash so our loyal customers don't loose their work.
  //
  // return (this == nullptr);
  // return ( nullptr == this );
  if (0 != ((ON__UINT_PTR)this))
    return false;

  if (false == bSilentError)
    ON_ERROR("this is nullptr.");

  return true;
}

bool ON_Object::IsCorrupt(
  bool bRepair,
  bool bSilentError,
  class ON_TextLog* text_log
) const
{
  bool rc = true;
  if (false == ThisIsNullptr(bSilentError) )
  {
    switch (ObjectType())
    {
    case ON::object_type::brep_object:
      {
        const ON_Brep* brep = ON_Brep::Cast(this);
        if (brep)
          rc = brep->ON_Brep::IsCorrupt(bRepair, bSilentError, text_log);
        else if ( false == bSilentError )
          ON_ERROR("ON_Brep::Cast(this) failed.");
      }
      break;

    case ON::object_type::mesh_object:
      {
        const ON_Mesh* mesh = ON_Mesh::Cast(this);
        if (mesh)
          rc = mesh->ON_Mesh::IsCorrupt(bRepair, bSilentError, text_log);
        else if ( false == bSilentError )
          ON_ERROR("ON_Mesh::Cast(this) failed.");
      }
      break;

    default:
      rc = false;
      break;
    }
  }
  return rc;
}

void ON_Object::Dump( ON_TextLog& dump ) const
{
  const ON_ClassId* p = ClassId();
  if ( p ) 
  {
    const char* class_name = p->ClassName();
    if ( 0 == class_name ) 
      class_name = "unknown";
    dump.Print("class name: %s\n",class_name);
    dump.Print("class uuid: ");
    dump.Print(p->Uuid());
    dump.Print("\n");
  }
  else 
  {
    dump.Print("ON_Object::ClassId() FAILED\n");
  }
}

bool ON_Object::Write(
       ON_BinaryArchive&
     ) const
{
  // default Write() does nothing.
  return false;

  // object derived from ON_Object should have a Write() that looks
  // something like

  /*
  bool rc = file.Write3dmChunkVersion(1,0);
  if (rc) {
    // TODO
  }
  return rc;
  */

}

bool ON_Object::Read(
       ON_BinaryArchive&
     )
{
  // default Read() does nothing.
  return false;

  // object derived from ON_Object should have a Read() that looks
  // something like

  /*
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if (rc && major_version==1) {
    // common to all 1.x versions
    // TODO
  }
  return rc;
  */

}

void ON_Object::DestroyRuntimeCache( bool bDelete )
{
}

void ON_Curve::DestroyRuntimeCache( bool bDelete )
{
}


void ON_CurveProxy::DestroyRuntimeCache( bool bDelete )
{
  ON_Curve::DestroyRuntimeCache(bDelete);
  if ( 0 != m_real_curve && m_real_curve != this )
  {
    ON_Curve* curve = const_cast<ON_Curve*>(m_real_curve);
    if ( 0 != curve )
      curve->DestroyRuntimeCache( bDelete );
  }
}

void ON_Surface::DestroyRuntimeCache( bool bDelete )
{
}

void ON_SurfaceProxy::DestroyRuntimeCache( bool bDelete )
{
  ON_Surface::DestroyRuntimeCache( bDelete );
  if ( 0 != m_surface && m_surface != this )
  {
    ON_Surface* surface = const_cast<ON_Surface*>(m_surface);
    if ( 0 != surface )
      surface->DestroyRuntimeCache( bDelete );
  }
}

void ON_Brep::DestroyRuntimeCache( bool bDelete )
{
  int i, count;

  count = m_C2.Count();
  for ( i = 0; i < count; i++ )
  {
    if ( m_C2[i] )
      m_C2[i]->DestroyRuntimeCache(bDelete);
  }

  count = m_C3.Count();
  for ( i = 0; i < count; i++ )
  {
    if ( m_C3[i] )
      m_C3[i]->DestroyRuntimeCache(bDelete);
  }

  count = m_S.Count();
  for ( i = 0; i < count; i++ )
  {
    if ( m_S[i] )
      m_S[i]->DestroyRuntimeCache(bDelete);
  }

  count = m_T.Count();
  for ( i = 0; i < count; i++ )
  {
    m_T[i].DestroyRuntimeCache(bDelete);
  }

  count = m_E.Count();
  for ( i = 0; i < count; i++ )
  {
    m_E[i].DestroyRuntimeCache(bDelete);
  }

  count = m_F.Count();
  for ( i = 0; i < count; i++ )
  {
    m_F[i].DestroyRuntimeCache(bDelete);
  }

  // 15 August 2003 Dale Lear:
  //    I added the line to destroy the face's m_bbox.
  //    Since m_bbox is private, it will be recalculated
  //    when it is needed.  (We hope.)  The fact the face
  //    m_bbox is private and recalculated as needed makes
  //    it different than the m_pbox info on trims and loops.
  m_bbox.Destroy();
}


template <class T> class ON_ArrayIterator
{
public:
  ON_ArrayIterator() = default;
  ~ON_ArrayIterator() = default;
  ON_ArrayIterator(const ON_ArrayIterator<T>&) = default;
  ON_ArrayIterator& operator=(const ON_ArrayIterator<T>&) = default;

  ON_ArrayIterator(
    T* first,
    size_t count
    )
  {
    m_first = (count > 0) ? first : nullptr;
    m_last = (nullptr != m_first) ? (m_first+(count-1)) : nullptr;
    m_current = m_first;
  }

  ON_ArrayIterator(
    T* first,
    T* last
    )
  {
    m_first = (nullptr != first && first <= last) ? first : nullptr;
    m_last = (nullptr != m_first) ? last : nullptr;
    m_current = m_first;
  }

  ON_ArrayIterator(
    ON_SimpleArray < T >& a
    )
  {
    unsigned int count = a.UnsignedCount();
    T* first = a.Array();
    m_first = (count > 0) ? first : nullptr;
    m_last = (nullptr != m_first) ? (m_first+(count-1)) : nullptr;
    m_current = m_first;
  }

  ON_ArrayIterator(
    ON_ClassArray < T >& a
    )
  {
    unsigned int count = a.UnsignedCount();
    T* first = a.Array();
    m_first = (count > 0) ? first : nullptr;
    m_last = (nullptr != m_first) ? (m_first+(count-1)) : nullptr;
    m_current = m_first;
  }

  ON_ArrayIterator(
    ON_ObjectArray < T >& a
    )
  {
    unsigned int count = a.UnsignedCount();
    T* first = a.Array();
    m_first = (count > 0) ? first : nullptr;
    m_last = (nullptr != m_first) ? (m_first+(count-1)) : nullptr;
    m_current = m_first;
  }

  T* First()
  {
    m_current = m_first;
    return m_first;
  }

  T* Next()
  {
    if (m_current < m_last)
      m_current++;
    else
      m_current = nullptr;
    return m_current;
  }

  T* Current() const
  {
    return m_current;
  }

  size_t Count() const
  {
    return (m_last - m_first);
  }

private:
  T* m_first = nullptr;
  T* m_last = nullptr;
  T* m_current = nullptr;
};

//virtual
unsigned int ON_Brep::ClearComponentStates(
  ON_ComponentStatus states_to_clear
  ) const
{
  if (states_to_clear.IsClear())
    return 0U;

  m_aggregate_status = ON_AggregateComponentStatus::NotCurrent;

  unsigned int rc = 0;

  ON_ArrayIterator< const ON_BrepVertex > vit( m_V.Array(), m_V.UnsignedCount() );
  for ( const ON_BrepVertex* p = vit.First(); nullptr != p; p = vit.Next())
  {
    rc += p->m_status.ClearStates(states_to_clear);
  }

  ON_ArrayIterator< const ON_BrepEdge > eit( m_E.Array(), m_E.UnsignedCount() );
  for ( const ON_BrepEdge* p = eit.First(); nullptr != p; p = eit.Next())
  {
    rc += p->m_status.ClearStates(states_to_clear);
  }

  ON_ArrayIterator< const ON_BrepTrim > tit( m_T.Array(), m_T.UnsignedCount() );
  for ( const ON_BrepTrim* p = tit.First(); nullptr != p; p = tit.Next())
  {
    rc += p->m_status.ClearStates(states_to_clear);
  }

  ON_ArrayIterator< const ON_BrepLoop > lit( m_L.Array(), m_L.UnsignedCount() );
  for ( const ON_BrepLoop* p = lit.First(); nullptr != p; p = lit.Next())
  {
    rc += p->m_status.ClearStates(states_to_clear);
  }

  ON_ArrayIterator< const ON_BrepFace > fit( m_F.Array(), m_F.UnsignedCount() );
  for ( const ON_BrepFace* p = fit.First(); nullptr != p; p = fit.Next())
  {
    rc += p->m_status.ClearStates(states_to_clear);
  }

  return rc;
}

//virtual
unsigned int ON_Brep::GetComponentsWithSetStates(
  ON_ComponentStatus states_filter,
  bool bAllEqualStates,
  ON_SimpleArray< ON_COMPONENT_INDEX >& components
  ) const
{
  components.SetCount(0);

  if (states_filter.IsClear())
    return 0;

  ON_AggregateComponentStatus acs = AggregateComponentStatus();

  ON_ComponentStatus as = acs.AggregateStatus();
  if (bAllEqualStates)
  {
    if ( false == as.AllEqualStates(states_filter, states_filter) )
      return 0;
  }
  else
  {
    if ( false == as.SomeEqualStates(states_filter, states_filter) )
      return 0;
  }

  unsigned int c = 0;
  if ( states_filter.IsSelected() && c < m_aggregate_status.SelectedCount() )
    c = m_aggregate_status.SelectedCount();
  if ( states_filter.IsHighlighted() && c < m_aggregate_status.HighlightedCount() )
    c = m_aggregate_status.HighlightedCount();
  if ( states_filter.IsHidden() && c < m_aggregate_status.HiddenCount() )
    c = m_aggregate_status.HiddenCount();
  if ( states_filter.IsLocked() && c < m_aggregate_status.LockedCount() )
    c = m_aggregate_status.LockedCount();
  if ( states_filter.IsDamaged() && c < m_aggregate_status.DamagedCount() )
    c = m_aggregate_status.DamagedCount();
  if ( states_filter.IsSelected() && c < m_aggregate_status.SelectedCount() )
    c = m_aggregate_status.SelectedCount();
  components.Reserve(c);

  ON_ArrayIterator< const ON_BrepVertex > vit( m_V.Array(), m_V.UnsignedCount() );
  for ( const ON_BrepVertex* p = vit.First(); nullptr != p; p = vit.Next())
  {
    if (bAllEqualStates ? p->m_status.AllEqualStates(states_filter, states_filter) : p->m_status.SomeEqualStates(states_filter, states_filter))
      components.Append(p->ComponentIndex());
  }

  ON_ArrayIterator< const ON_BrepEdge > eit( m_E.Array(), m_E.UnsignedCount() );
  for ( const ON_BrepEdge* p = eit.First(); nullptr != p; p = eit.Next())
  {
    if (bAllEqualStates ? p->m_status.AllEqualStates(states_filter, states_filter) : p->m_status.SomeEqualStates(states_filter, states_filter))
      components.Append(p->ComponentIndex());
  }

  ON_ArrayIterator< const ON_BrepTrim > tit( m_T.Array(), m_T.UnsignedCount() );
  for ( const ON_BrepTrim* p = tit.First(); nullptr != p; p = tit.Next())
  {
    if (bAllEqualStates ? p->m_status.AllEqualStates(states_filter, states_filter) : p->m_status.SomeEqualStates(states_filter, states_filter))
      components.Append(p->ComponentIndex());
  }

  ON_ArrayIterator< const ON_BrepLoop > lit( m_L.Array(), m_L.UnsignedCount() );
  for ( const ON_BrepLoop* p = lit.First(); nullptr != p; p = lit.Next())
  {
    if (bAllEqualStates ? p->m_status.AllEqualStates(states_filter, states_filter) : p->m_status.SomeEqualStates(states_filter, states_filter))
      components.Append(p->ComponentIndex());
  }

  ON_ArrayIterator< const ON_BrepFace > fit( m_F.Array(), m_F.UnsignedCount() );
  for ( const ON_BrepFace* p = fit.First(); nullptr != p; p = fit.Next())
  {
    if (bAllEqualStates ? p->m_status.AllEqualStates(states_filter, states_filter) : p->m_status.SomeEqualStates(states_filter, states_filter))
      components.Append(p->ComponentIndex());
  }

  return components.UnsignedCount();
}

static ON_ComponentStatus* BrepComponentStatus(
  const ON_Brep& brep,
  ON_COMPONENT_INDEX component_index
  )
{
  if (component_index.m_index >= 0)
  {
    switch (component_index.m_type)
    {
    case ON_COMPONENT_INDEX::TYPE::brep_vertex:
      if ( component_index.m_index < brep.m_V.Count() )
        return &brep.m_V[component_index.m_index].m_status;
      break;
    case ON_COMPONENT_INDEX::TYPE::brep_edge:
      if ( component_index.m_index < brep.m_E.Count() )
        return &brep.m_E[component_index.m_index].m_status;
      break;
    case ON_COMPONENT_INDEX::TYPE::brep_trim:
      if ( component_index.m_index < brep.m_T.Count() )
        return &brep.m_T[component_index.m_index].m_status;
      break;
    case ON_COMPONENT_INDEX::TYPE::brep_loop:
      if ( component_index.m_index < brep.m_L.Count() )
        return &brep.m_L[component_index.m_index].m_status;
      break;
    case ON_COMPONENT_INDEX::TYPE::brep_face:
      if ( component_index.m_index < brep.m_F.Count() )
        return &brep.m_F[component_index.m_index].m_status;
      break;
    default:
      break;
    }
  }
  return nullptr;
}
  
//virtual
unsigned int ON_Brep::SetComponentStates(
  ON_COMPONENT_INDEX component_index,
  ON_ComponentStatus states_to_set
  ) const
{
  ON_ComponentStatus* s = BrepComponentStatus(*this,component_index);
  return 
    (nullptr == s)
    ? 0U
    : s->SetStates(states_to_set);
}

//virtual
unsigned int ON_Brep::ClearComponentStates(
  ON_COMPONENT_INDEX component_index,
  ON_ComponentStatus states_to_clear
  ) const
{
  ON_ComponentStatus* s = BrepComponentStatus(*this,component_index);
  return 
    (nullptr == s)
    ? 0U
    : s->ClearStates(states_to_clear);
}
  
//virtual
unsigned int ON_Brep::SetComponentStatus(
  ON_COMPONENT_INDEX component_index,
  ON_ComponentStatus status_to_copy
  ) const
{
  ON_ComponentStatus* s = BrepComponentStatus(*this,component_index);
  return 
    (nullptr == s)
    ? 0U
    : s->SetStatus(status_to_copy);
}

//virtual
ON_AggregateComponentStatus ON_Brep::AggregateComponentStatus() const
{
  if (false == m_aggregate_status.IsCurrent())
  {
    if (m_V.UnsignedCount() == 0 )
      return ON_AggregateComponentStatus::Empty;

    ON_AggregateComponentStatus a = ON_AggregateComponentStatus::Empty;

    ON_ArrayIterator< const ON_BrepVertex > vit( m_V.Array(), m_V.UnsignedCount() );
    for ( const ON_BrepVertex* p = vit.First(); nullptr != p; p = vit.Next())
    {
      a.Add(p->m_status);
    }

    ON_ArrayIterator< const ON_BrepEdge > eit( m_E.Array(), m_E.UnsignedCount() );
    for ( const ON_BrepEdge* p = eit.First(); nullptr != p; p = eit.Next())
    {
      a.Add(p->m_status);
    }

    ON_ArrayIterator< const ON_BrepTrim > tit( m_T.Array(), m_T.UnsignedCount() );
    for ( const ON_BrepTrim* p = tit.First(); nullptr != p; p = tit.Next())
    {
      a.Add(p->m_status);
    }

    ON_ArrayIterator< const ON_BrepLoop > lit( m_L.Array(), m_L.UnsignedCount() );
    for ( const ON_BrepLoop* p = lit.First(); nullptr != p; p = lit.Next())
    {
      a.Add(p->m_status);
    }

    ON_ArrayIterator< const ON_BrepFace > fit( m_F.Array(), m_F.UnsignedCount() );
    for ( const ON_BrepFace* p = fit.First(); nullptr != p; p = fit.Next())
    {
      a.Add(p->m_status);
    }

    m_aggregate_status = a;
  }

  return m_aggregate_status;
}

//virtual
void ON_Brep::MarkAggregateComponentStatusAsNotCurrent() const
{
  this->m_aggregate_status.MarkAsNotCurrent();
}



