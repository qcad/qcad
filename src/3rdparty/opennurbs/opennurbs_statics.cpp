#include "opennurbs.h"
#include "opennurbs.h"
#include "opennurbs_testclass.h"
#include "opennurbs_subd_data.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

#if defined(ON_COMPILER_MSC)
// Force this module to be inited first so the important globals
// are initialized before there is any possibility they are used.
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4073 )
#pragma init_seg(lib)
#pragma ON_PRAGMA_WARNING_POP
#endif

const ON_ErrorEvent ON_ErrorEvent::Unset;

static unsigned int Internal_ON_LibraryStatusInit()
{
  return 0;
}

unsigned int ON::m_opennurbs_library_status = Internal_ON_LibraryStatusInit();

unsigned int ON_MemoryAllocationTracking::m_g_stack_depth = 0;
int ON_MemoryAllocationTracking::m_g_crt_dbg_flag0 = 0;

ON_MemoryAllocationTracking::ON_MemoryAllocationTracking(bool bEnableAllocationTracking)
#if defined(ON_DEBUG_MEMORY_MSC_WIN)
  : m_this_statck_depth(++ON_MemoryAllocationTracking::m_g_stack_depth)
  , m_this_crt_dbg_flag0(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else
  : m_this_statck_depth(0)
  , m_this_crt_dbg_flag0(0)
#endif
{
#if defined(ON_DEBUG_MEMORY_MSC_WIN)
  // Dale Lear - Dec 2017
  //   Not thread safe but good enough for now and won't crash or assert.
  //   Relax, it's just a debugging tool based on ancient Microsoft debug heap tools.
  if (1 == m_this_statck_depth)
    ON_MemoryAllocationTracking::m_g_crt_dbg_flag0 = m_this_crt_dbg_flag0;
  if (bEnableAllocationTracking)
  {
    if ( 0 == (m_this_crt_dbg_flag0 & _CRTDBG_ALLOC_MEM_DF))
      _CrtSetDbgFlag(m_this_crt_dbg_flag0 | _CRTDBG_ALLOC_MEM_DF);
  }
  else if ( 0 != m_this_crt_dbg_flag0 )
  {
    _CrtSetDbgFlag(0);
  }
#endif
}

ON_MemoryAllocationTracking::~ON_MemoryAllocationTracking()
{
#if defined(ON_DEBUG_MEMORY_MSC_WIN)
  // Dale Lear - Dec 2017
  //   Not thread safe but good enough for now and won't crash or assert.
  //   Relax, it's just a debugging tool based on ancient Microsoft debug heap tools.
  if (ON_MemoryAllocationTracking::m_g_stack_depth > 0)
  {
    const bool bOutOfOrder = (m_this_statck_depth != ON_MemoryAllocationTracking::m_g_stack_depth);

    const int crt_dbg_flag0
      = bOutOfOrder
      ? ON_MemoryAllocationTracking::m_this_crt_dbg_flag0
      : m_this_crt_dbg_flag0;

    const int crt_dbg_flag1 = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

    if ( crt_dbg_flag1 != crt_dbg_flag0 )
    {
      _CrtSetDbgFlag(crt_dbg_flag0);
    }
    ON_MemoryAllocationTracking::m_g_stack_depth--;
  }
#endif
}

#if !defined(OPENNURBS_NO_STD_MUTEX)
// It is critical that ON_TestClass::global_mutex, ON_TestClass::CtorSerialNumberGenerator, and
// ON_TestClass::PopulationCounter be initialized before any instance of ON_TestClass is created. 
std::mutex ON_TestClass::internal_counter_mutex;
ON__UINT64 ON_TestClass::internal_CtorSerialNumberGenerator = 0;
ON__UINT64 ON_TestClass::internal_PopulationCounter = 0;
#endif

ON__UINT64 ON_NextContentSerialNumber()
{
  static ON__UINT64 serial_number = 0;
  // If it's ever an issue with multiple threads, 
  // this value can be made atomic, but that will slow down performance.
  return (0 != ++serial_number) ? serial_number : ++serial_number;
}

// All opennurbs static members are initialized here so that initialization happens in a predictable order.
/*
IEEE 754
Storage
size      sign     exponent         fraction
float    4 bytes   bit 31    8 bits (30-23)  23 bits (22-0)
double   8 bytes   bit 63   11 bits (62-52)  52 bits (51-0)
sign bit = 1 indicates negative
sign bit = 0 indicates positive
float  absolute value = 2^(e-127)  * 1+(f/2^23)
e = value of the 8 bit number in the exponent field
f = value of the 23 bit number in the fraction field
double absolute value = 2^(e-1023) * 1+(f/2^51)
e = value of the 11 bit number in the exponent field
f = value of the 51 bit number in the fraction field
Exceptions:
If all exponent bits are all 0 (e = 0) and the fraction bits
are all zero, then the value of the number is zero.
If all exponent bits are all 0 (e = 0) and at least one fraction
bits is not zero, then the representation is "denormalized".
In this case, the float absolute value is 0.f*2^-126 and the
double absolute value is 0.f*2^-1022.
If all exponent bits are 1 (float e = 11111111binary = 255decimal
or double e = 11111111111 binary = 2047 decimal) and the fraction
bits are all zero, the number is infinity.  The sign bit
determines the sign of infinity.

If all exponent bits are 1 and at least one fraction bit is
not zero, the number is a "NaN" (not a number).  If the most
significant fraction bit is 1, the number is a quiet NaN or
"QNaN".  If the most significant fraction bit is 0, the number
is a signalling NaN or "SNaN".

Some authors (SH)   QNaNs are used to indicate
indeterminant operations, like sqrt(-1.0).  SNaNs are used
to indicate invalid operations.
SH - http://steve.hollasch.net/cgindex/coding/ieeefloat.html
Intel -
*/
static double Internal_ON__dblinithelper(int i)
{
  // called twice - performance is not important
  union
  {
    double x;
    unsigned char b[8];
  } u;
  unsigned int i7, i6;

  // different bytes on
  u.x = 2.0; // sign = 0; fraction = 0; exponent = 100 0000 0000 binary

  if (0x40 == u.b[7] && 0 == u.b[0]
    && 0 == u.b[1] && 0 == u.b[2] && 0 == u.b[3]
    && 0 == u.b[4] && 0 == u.b[5] && 0 == u.b[6]
    )
  {
    // little endian doubles
    i7 = 7; i6 = 6;
  }
  else if (0x40 == u.b[0] && 0 == u.b[7]
    && 0 == u.b[1] && 0 == u.b[2] && 0 == u.b[3]
    && 0 == u.b[4] && 0 == u.b[5] && 0 == u.b[6]
    )
  {
    // big endian doubles
    i7 = 0; i6 = 1;
  }
  else
  {
    // this situation is not handled by this algorithm
    // and that is a bug in the algorithm.
    ON_ERROR("CPU has unexpected bit pattern in double 2.0.");
    i7 = 0;
    i6 = 0;
    i = 99;
  }

  if (1 == i) // positive quiet NaN
  {
    // all exponent bits = 1
    // fraction bits = 100...0
    u.b[i7] = 0x7F; // 0111 1111
    u.b[i6] = 0xF8; // 1111 1000
    u.b[5] = 0;    // 0...
    u.b[4] = 0;
    u.b[3] = 0;
    u.b[2] = 0;
    u.b[7 - i6] = 0;
    u.b[7 - i7] = 0;
  }
  else if (2 == i) // positive infinity
  {
    // all exponent bits = 1
    // all fraction bits = 0
    u.b[i7] = 0x7F; // 0111 1111
    u.b[i6] = 0xF0; // 1111 0000
    u.b[5] = 0;    // 0...
    u.b[4] = 0;
    u.b[3] = 0;
    u.b[2] = 0;
    u.b[7 - i6] = 0;
    u.b[7 - i7] = 0;
  }
  else
  {
    // invalid input 
    u.b[0] = 0xFF;
    u.b[1] = 0xFF;
    u.b[2] = 0xFF;
    u.b[3] = 0xFF;
    u.b[4] = 0xFF;
    u.b[5] = 0xFF;
    u.b[6] = 0xFF;
    u.b[7] = 0xFF;
  }

  return u.x;
}

static float Internal_ON__fltinithelper(int i)
{
  // called twice - performance is not important
  union
  {
    float x;
    unsigned char b[4];
  } u;
  unsigned int i3, i2;

  // different bytes on
  u.x = 2.0f; // sign = 0; mantissa = 0; exponent = 1000 0000
  if (0x40 == u.b[3] && 0 == u.b[0] && 0 == u.b[1] && 0 == u.b[2])
  {
    // little endian doubles
    i3 = 3; i2 = 2;
  }
  else if (0x40 == u.b[0] && 0 == u.b[3] && 0 == u.b[1] && 0 == u.b[2])
  {
    // big endian doubles
    i3 = 0; i2 = 1;
  }
  else
  {
    // this situation is not handled by this algorithm
    // and that is a bug in the algorithm.
    ON_ERROR("CPU has unexpected bit pattern in float 2.0f.");
    i3 = 0;
    i2 = 0;
    i = 99;
  }

  if (1 == i) // positive quiet NaN
  {
    // all exponent bits = 1
    // fraction bits = 100...0
    u.b[i3] = 0x7F; // 0111 1111
    u.b[i2] = 0xC0; // 1100 0000
    u.b[3 - i2] = 0;    // 0...
    u.b[3 - i3] = 0;
  }
  else if (2 == i) // positive infinity
  {
    // all exponent bits = 1
    // all fraction bits = 0
    u.b[i3] = 0x7F; // 0111 1111
    u.b[i2] = 0x80; // 1000 0000
    u.b[3 - i2] = 0;    // 0...
    u.b[3 - i3] = 0;
  }
  else
  {
    // invalid input 
    u.b[0] = 0xFF;
    u.b[1] = 0xFF;
    u.b[2] = 0xFF;
    u.b[3] = 0xFF;
  }

  return u.x;
}

const double ON_DBL_QNAN = Internal_ON__dblinithelper(1);
const double ON_DBL_PINF = Internal_ON__dblinithelper(2);
const double ON_DBL_NINF = -Internal_ON__dblinithelper(2);

const double ON_DBL::Nan = ON_DBL_QNAN;
const double ON_DBL::PositiveInfinity = ON_DBL_PINF;
const double ON_DBL::NegativeInfinity = ON_DBL_NINF;

const double ON_DBL::PositiveMax = ON_DBL_MAX;
const double ON_DBL::NegativeMax = -ON_DBL_MAX;

const double ON_DBL::PositiveMin = ON_DBL_MIN;
const double ON_DBL::NegativeMin = -ON_DBL_MIN;

const double ON_DBL::Unset = ON_UNSET_VALUE;
const double ON_DBL::PositiveUnset = ON_UNSET_POSITIVE_VALUE;

bool ON_DBL::IsValid(double x)
{
  return x > ON_UNSET_VALUE && x < ON_UNSET_POSITIVE_VALUE;
}

bool ON_DBL::IsNan(double x)
{
  return (x == x) ? false : true;
}

int ON_DBL::Sign(double x)
{
  return (x > 0.0 ? 1 : ((x < 0.0) ? -1 : 0));
}

bool ON_DBL::IsInfinity(double x)
{
  return (x >= ON_DBL_PINF || x <= ON_DBL_NINF);
}

bool ON_DBL::IsPositiveInfinity(double x)
{
  return (x >= ON_DBL_PINF);
}

bool ON_DBL::IsNegativeInfinity(double x)
{
  return (x <= ON_DBL_NINF);
}

bool ON_DBL::IsNotNan(double x)
{
  return (x == x);
}

bool ON_DBL::IsUnset(double x)
{
  return (ON_UNSET_VALUE == fabs(x));
}

int ON_DBL::CompareValue(double lhs, double rhs)
{
  if (lhs < rhs)
    return -1;
  if (lhs > rhs)
    return 1;
  if (lhs == rhs)
    return 0; 

  // At least one of lhs or rhs is a nan. Sort nans to end
  return (ON_IS_NAN(lhs) ? 1 : 0) - (ON_IS_NAN(rhs) ? 1 : 0);
}


int ON_DBL::Compare(const double* lhs, const double* rhs)
{
  // sort nullptr to the end
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return 1;
  if (nullptr == rhs)
    return -1;
  return ON_DBL::CompareValue(*lhs, *rhs);
}

const float  ON_FLT_QNAN = Internal_ON__fltinithelper(1);
const float  ON_FLT_PINF = Internal_ON__fltinithelper(2);
const float  ON_FLT_NINF = -Internal_ON__fltinithelper(2);

// It is critical that ON_ModelComponent::Internal_RuntimeSerialNumberGenerator
// be constructed before any instance of a class derived from ON_ModelComponent.
// That is why it is above the ClassId stuff in this .cpp file.
// Serial numbers below UINT32_MAX + 1 are reserved for Rhino use.
std::atomic<ON__UINT64> ON_ModelComponent::Internal_RuntimeSerialNumberGenerator(UINT32_MAX + 1ULL);

std::atomic<ON__UINT64> ON_SubDimple::Internal_RuntimeSerialNumberGenerator;

const double ON_SubDExpandEdgesParameters::OffsetTolerance = 0.001;

const double ON_SubDExpandEdgesParameters::MinimumOffset = 0.05;

const double ON_SubDExpandEdgesParameters::MaximumOffset = 0.95;

const double ON_SubDExpandEdgesParameters::SmallOffset = 0.125;

const double ON_SubDExpandEdgesParameters::MediumOffset = 0.25;

const double ON_SubDExpandEdgesParameters::LargeOffset = 0.5;

const ON_SubDExpandEdgesParameters ON_SubDExpandEdgesParameters::Default;

const ON_SubDComponentLocation ON_SubD::DefaultSubDAppearance = ON_SubDComponentLocation::Surface;

// The default type must be packed, unpacked, zero, or nan and should be packed or unpacked.
const ON_SubDTextureCoordinateType ON_SubD::DefaultTextureCoordinateType = ON_SubDTextureCoordinateType::Packed;


// NOTE WELL: 
// It is required that (3 + 2^ON_SubDEdgeSharpness::MaximumValue) <= ON_SubDEdgeSurfaceCurve::MaximumControlPointCapacity
const double ON_SubDEdgeSharpness::MaximumValue = 4.0;
const double ON_SubDEdgeSharpness::SmoothValue = 0.0;
const double ON_SubDEdgeSharpness::CreaseValue = ON_SubDEdgeSharpness::MaximumValue + 1.0;
const double ON_SubDEdgeSharpness::Tolerance = 0.01;

const ON_SubDEdgeSharpness ON_SubDEdgeSharpness::Smooth;

const ON_SubDEdgeSharpness ON_SubDEdgeSharpness::Maximum = ON_SubDEdgeSharpness::FromConstant(ON_SubDEdgeSharpness::MaximumValue);

const ON_SubDEdgeSharpness ON_SubDEdgeSharpness::Nan = ON_SubDEdgeSharpness::FromConstant(ON_DBL_QNAN);

const ON_SubDEdgeSharpness ON_SubDEdgeSharpness::Crease = ON_SubDEdgeSharpness::FromConstant(ON_SubDEdgeSharpness::CreaseValue);

const ON_SubDFaceCornerDex ON_SubDFaceCornerDex::Unset(0, 0);

const ON_SubDFaceParameter ON_SubDFaceParameter::Nan = { ON_SubDFaceCornerDex::Unset, ON_DBL_QNAN, ON_DBL_QNAN };

const double ON_SubDSectorType::MinimumCornerAngleRadians = (2.0*ON_PI)/((double)(ON_SubDSectorType::MaximumCornerAngleIndex));
const double ON_SubDSectorType::MaximumCornerAngleRadians = 2.0*ON_PI - ON_SubDSectorType::MinimumCornerAngleRadians;

const ON_SubDSectorId ON_SubDSectorId::Zero;
const ON_SubDSectorId ON_SubDSectorId::Invalid = ON_SubDSectorId::Create(nullptr, nullptr);

const ON_SubDHash ON_SubDHash::Empty;

// {C3D8DD54-F8C8-4455-BB0E-2A2F4988EC81}
const ON_UUID ON_SubD::FastAndSimpleFacePackingId =
{ 0xc3d8dd54, 0xf8c8, 0x4455, { 0xbb, 0xe, 0x2a, 0x2f, 0x49, 0x88, 0xec, 0x81 } };

// {9C491E5C-2B46-48AA-BD43-7B18FDC52D58}
const ON_UUID ON_SubD::QuadSphereFacePackingId =
{ 0x9c491e5c, 0x2b46, 0x48aa, { 0xbd, 0x43, 0x7b, 0x18, 0xfd, 0xc5, 0x2d, 0x58 } };

// {63CA2FC1-8F6C-4EFC-9A07-C6A26A8C93FB}
const ON_UUID ON_SubD::GlobeSphereFacePackingId =
{ 0x63ca2fc1, 0x8f6c, 0x4efc, { 0x9a, 0x7, 0xc6, 0xa2, 0x6a, 0x8c, 0x93, 0xfb } };

// {91FD7018-8BBE-4492-8D2E-E8761C505ACF}
const ON_UUID ON_SubD::CustomFacePackingId =
{ 0x91fd7018, 0x8bbe, 0x4492, { 0x8d, 0x2e, 0xe8, 0x76, 0x1c, 0x50, 0x5a, 0xcf } };


// ON_SubD::DefaultFacePackingId must always identity a built-in face packing
// algorithm. If a new built-in algorithm is developed that produces generally
// better packings and is as fast and reliable as the current default, then
// ON_SubD::DefaultFacePackingId can be changed. Under no circumstances, should
// the default be changed to anything that is more than 1.5 times slower than 
// the either the fast and simple or the current default on large models 
// like the Mt St Helens Subd. 
//
// ** If it's not really fast, then it cannot be the the default. **
const ON_UUID ON_SubD::DefaultFacePackingId = ON_SubD::FastAndSimpleFacePackingId;

const ON_SubDToBrepParameters Internal_SubDToBrepParameters(bool bPackedFaces)
{
  ON_SubDToBrepParameters p;
  p.SetPackFaces(bPackedFaces);
  return p;
}

const ON_SubDToBrepParameters ON_SubDToBrepParameters::Default;
const ON_SubDToBrepParameters ON_SubDToBrepParameters::DefaultUnpacked = Internal_SubDToBrepParameters(false);
const ON_SubDToBrepParameters ON_SubDToBrepParameters::DefaultPacked = Internal_SubDToBrepParameters(true);


const ON_SubDRTreeVertexFinder ON_SubDRTreeVertexFinder::Unset;


ON_ClassId* ON_ClassId::m_p0 = 0; // static pointer to first id in list
ON_ClassId* ON_ClassId::m_p1 = 0; // static pointer to last id in list
int ON_ClassId::m_mark0 = 0;

// {1311ADCB-D89E-4051-A3F0-F64441FB8EC6}
const ON_UUID ON_StandardDisplayModeId::Wireframe =
{ 0x1311ADCB,0xD89E,0x4051,{ 0xA3,0xF0,0xF6,0x44,0x41,0xFB,0x8E,0xC6 } };

// {8BC8DEBE-C83B-4c47-B13C-9DB074510CAC}
const ON_UUID ON_StandardDisplayModeId::Shaded =
{ 0x8BC8DEBE,0xC83B,0x4c47,{ 0xB1,0x3C,0x9D,0xB0,0x74,0x51,0x0C,0xAC } };

// {CAE60BAE-2D51-4299-ABF7-A339FCA86F3B}
const ON_UUID ON_StandardDisplayModeId::Rendered =
{ 0xCAE60BAE,0x2D51,0x4299,{ 0xAB,0xF7,0xA3,0x39,0xFC,0xA8,0x6F,0x3B } };

// {FF608B97-81D3-4186-831C-41F7DC140881}
const ON_UUID ON_StandardDisplayModeId::Ghosted =
{ 0xFF608B97,0x81D3,0x4186,{ 0x83,0x1C,0x41,0xF7,0xDC,0x14,0x08,0x81 } };

// {B5C19D5D-0AEC-4ff7-A10E-E052E660263A}
const ON_UUID ON_StandardDisplayModeId::XrayShade =
{ 0xB5C19D5D,0x0AEC,0x4ff7,{ 0xA1,0x0E,0xE0,0x52,0xE6,0x60,0x26,0x3A } };

// {A5545314-9D87-428d-95AE-91052EEAD0FA}
const ON_UUID ON_StandardDisplayModeId::RenderedShadows =
{ 0xA5545314,0x9D87,0x428d,{ 0x95,0xAE,0x91,0x05,0x2E,0xEA,0xD0,0xFA } };

// {63612C72-778F-4afd-B81B-17426FDFE8A6}
const ON_UUID ON_StandardDisplayModeId::Technical =
{ 0x63612C72,0x778F,0x4afd,{ 0xB8,0x1B,0x17,0x42,0x6F,0xDF,0xE8,0xA6 } };

// {B46AB226-05A0-4568-B454-4B1AB721C675}
const ON_UUID ON_StandardDisplayModeId::Artistic =
{ 0xB46AB226,0x05A0,0x4568,{ 0xB4,0x54,0x4B,0x1A,0xB7,0x21,0xC6,0x75 } };

// {F4616FA5-A831-4620-A97E-9B807D5EC376}
const ON_UUID ON_StandardDisplayModeId::Pen =
{ 0xF4616FA5,0xA831,0x4620,{ 0xA9,0x7E,0x9B,0x80,0x7D,0x5E,0xC3,0x76 } };

// {E1B5C8A2-ED43-4872-9A01-814E612D5363}
const ON_UUID ON_StandardDisplayModeId::Monochrome =
{ 0xE1B5C8A2, 0xED43, 0x4872, { 0x9A, 0x1, 0x81, 0x4E, 0x61, 0x2D, 0x53, 0x63 } };

// {C32B72C3-41BD-4ADC-82A8-B7AEF4456A37}
const ON_UUID ON_StandardDisplayModeId::AmbientOcclusion = 
{ 0xc32b72c3, 0x41bd, 0x4adc, { 0x82, 0xa8, 0xb7, 0xae, 0xf4, 0x45, 0x6a, 0x37 } };

// {69E0C7A5-1C6A-46C8-B98B-8779686CD181}
const ON_UUID ON_StandardDisplayModeId::Raytraced = 
{ 0x69e0c7a5, 0x1c6a, 0x46c8, { 0xb9, 0x8b, 0x87, 0x79, 0x68, 0x6c, 0xd1, 0x81 } };


const ON_UUID ON_nil_uuid = { 0,0,0,{ 0,0,0,0,0,0,0,0 } };
const ON_UUID ON_max_uuid = { 0xFFFFFFFF,0xFFFF,0xFFFF,{ 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF } };

const ON_UUID ON_rhino2_id = { 0x16d0eca6, 0x359, 0x4e4c,{ 0x9f, 0xe, 0xf2, 0x69, 0xfd, 0x47, 0x6c, 0xc4 } };

const ON_UUID ON_rhino3_id = { 0xA7BBFF3C, 0xFF19, 0x4883,{ 0x85, 0x8D, 0xB1, 0xE7, 0xDB, 0x4F, 0x1A, 0x7E } };

// {E2143A46-BB01-4b0c-AC4D-C34B5652FAE0}
const ON_UUID ON_rhino4_id = { 0xe2143a46, 0xbb01, 0x4b0c,{ 0xac, 0x4d, 0xc3, 0x4b, 0x56, 0x52, 0xfa, 0xe0 } };

// {60515F84-8F7F-41da-801D-1C87E32F88F5}
const ON_UUID ON_rhino5_id = { 0x60515f84, 0x8f7f, 0x41da,{ 0x80, 0x1d, 0x1c, 0x87, 0xe3, 0x2f, 0x88, 0xf5 } };

// {06BB1079-5A56-47A1-AD6D-0B45183D894B}
const ON_UUID ON_rhino6_id = { 0x6bb1079, 0x5a56, 0x47a1,{ 0xad, 0x6d, 0xb, 0x45, 0x18, 0x3d, 0x89, 0x4b } };

// {78464C2C-9AEB-456E-8C27-865A524F5CA0}
const ON_UUID ON_rhino7_id = { 0x78464c2c, 0x9aeb, 0x456e,{ 0x8c, 0x27, 0x86, 0x5a, 0x52, 0x4f, 0x5c, 0xa0 } };

// {868c63f5-3760-4a45-8600-5399cc57b47c}
const ON_UUID ON_rhino8_id = { 0x868c63f5, 0x3760, 0x4a45,{ 0x86, 0x00, 0x53, 0x99, 0xcc, 0x57, 0xb4, 0x7c } };

// ON_rhino_id is always set to the value for the current version
// of Rhino.  ON_rhino_id is the id that should be used as the
// userdata application id for userdata class definitions that are
// in the core Rhino executable.
const ON_UUID ON_rhino_id = ON_rhino8_id;

// Used to identify userdata read from V2 files
// which were written before userdata had application ids.
// {132F2340-DB90-494e-BF02-C36F0EA3197C}
const ON_UUID ON_v2_userdata_id = { 0x132f2340, 0xdb90, 0x494e,{ 0xbf, 0x2, 0xc3, 0x6f, 0xe, 0xa3, 0x19, 0x7c } };

// Used to identify userdata read from V3 files
// which were written before userdata had application ids.
// {4307B91D-6A9D-478e-B0A2-7C577997C663}
const ON_UUID ON_v3_userdata_id = { 0x4307b91d, 0x6a9d, 0x478e,{ 0xb0, 0xa2, 0x7c, 0x57, 0x79, 0x97, 0xc6, 0x63 } };

// Used to identify userdata read from V4 files
// which were written before opennurbs 200609190
// required application ids.
// {F73F2953-A244-44c2-B7C2-7E27390D1196}
const ON_UUID ON_v4_userdata_id = { 0xf73f2953, 0xa244, 0x44c2,{ 0xb7, 0xc2, 0x7e, 0x27, 0x39, 0xd, 0x11, 0x96 } };

// {17B3ECDA-17BA-4e45-9E67-A2B8D9BE520D}
const ON_UUID ON_opennurbs4_id = { 0x17b3ecda, 0x17ba, 0x4e45,{ 0x9e, 0x67, 0xa2, 0xb8, 0xd9, 0xbe, 0x52, 0xd } };

// {C8CDA597-D957-4625-A4B3-A0B510FC30D4}
const ON_UUID ON_opennurbs5_id = { 0xc8cda597, 0xd957, 0x4625,{ 0xa4, 0xb3, 0xa0, 0xb5, 0x10, 0xfc, 0x30, 0xd4 } };

// {7B0B585D-7A31-45D0-925E-BDD7DDF3E4E3}
const ON_UUID ON_opennurbs6_id = { 0x7b0b585d, 0x7a31, 0x45d0,{ 0x92, 0x5e, 0xbd, 0xd7, 0xdd, 0xf3, 0xe4, 0xe3 } };

// {523bfe6e-ef49-4b75-a8d6-253faf5044d3}
const ON_UUID ON_opennurbs7_id = { 0x523bfe6e, 0xef49, 0x4b75,{ 0xa8, 0xd6, 0x25, 0x3f, 0xaf, 0x50, 0x44, 0xd3 } };

// {50EDE5C9-1487-4B4C-B3AA-6840B460E3CF}
const ON_UUID ON_opennurbs8_id = { 0x50ede5c9, 0x1487, 0x4b4c, { 0xb3, 0xaa, 0x68, 0x40, 0xb4, 0x60, 0xe3, 0xcf } };


// ON_opennurbs_id is always set to the value for the current version
// of opennurbs.  ON_opennurbs_id is the id that should be used as
// the userdata application id for userdata classes definitions that
// are in the opennurbs library.
const ON_UUID ON_opennurbs_id = ON_opennurbs8_id;

const ON_UuidPairList ON_UuidPairList::EmptyList;
const ON_UuidPairList2 ON_UuidPairList2::EmptyList;

const ON_COMPONENT_INDEX ON_COMPONENT_INDEX::UnsetComponentIndex;
const ON_COMPONENT_INDEX ON_COMPONENT_INDEX::WholeObject;
const ON_ComponentIndexAndNumber ON_ComponentIndexAndNumber::UnsetAndNan = ON_ComponentIndexAndNumber::Create(ON_COMPONENT_INDEX::UnsetComponentIndex, ON_DBL_QNAN);
const ON_ComponentIndexAndNumber ON_ComponentIndexAndNumber::UnsetAndZero = ON_ComponentIndexAndNumber::Create(ON_COMPONENT_INDEX::UnsetComponentIndex, 0.0);


const ON_2dex ON_2dex::Unset(ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX);
const ON_2dex ON_2dex::Zero(0, 0);
const ON_3dex ON_3dex::Unset(ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX);
const ON_3dex ON_3dex::Zero(0, 0, 0);
const ON_4dex ON_4dex::Unset(ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX);
const ON_4dex ON_4dex::Zero(0, 0, 0, 0);

const ON_2udex ON_2udex::Unset(ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX);
const ON_2udex ON_2udex::Zero(0, 0);
const ON_3udex ON_3udex::Unset(ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX);
const ON_3udex ON_3udex::Zero(0, 0, 0);
const ON_4udex ON_4udex::Unset(ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX, ON_UNSET_UINT_INDEX);
const ON_4udex ON_4udex::Zero(0, 0, 0, 0);

const ON_Interval ON_Interval::EmptyInterval(ON_UNSET_VALUE,ON_UNSET_VALUE);
const ON_Interval ON_Interval::ZeroToOne(0.0,1.0);
const ON_Interval ON_Interval::ZeroToTwoPi(0.0,2.0*ON_PI);
const ON_Interval ON_Interval::Nan(ON_DBL_QNAN,ON_DBL_QNAN);

const ON_TextBox ON_TextBox::Unset;

const ON_CheckSum ON_CheckSum::UnsetCheckSum;

const ONX_ErrorCounter ONX_ErrorCounter::Zero;

static ON_MD5_Hash Internal_ON_MD5_Hash_EmptyContentHash()
{
  ON_MD5 md5;
  return md5.Hash();
}
const ON_MD5_Hash ON_MD5_Hash::EmptyContentHash = Internal_ON_MD5_Hash_EmptyContentHash();
const ON_MD5_Hash ON_MD5_Hash::ZeroDigest;

static ON_SHA1_Hash Internal_ON_SHA1_Hash_EmptyContentHash()
{
  ON_SHA1 sha1;
  return sha1.Hash();
}
const ON_SHA1_Hash ON_SHA1_Hash::EmptyContentHash = Internal_ON_SHA1_Hash_EmptyContentHash();
const ON_SHA1_Hash ON_SHA1_Hash::ZeroDigest;

const ONX_ModelTest ONX_ModelTest::Unset;

// Works with Microsoft's CL, fails for Apple's CLang
////   const struct ON_UnicodeErrorParameters ON_UnicodeErrorParameters::MaskErrors   = { 0, 0xFFFFFFFF, ON_UnicodeCodePoint::ON_ReplacementCharacter };
////   const struct ON_UnicodeErrorParameters ON_UnicodeErrorParameters::FailOnErrors = { 0, 0,          ON_UnicodeCodePoint::ON_ReplacementCharacter };
// Works with Microsoft's CL and less capable compilers
static struct ON_UnicodeErrorParameters ON_Internal_UnicodeErrorParameters_Default(unsigned int error_mask)
{
  struct ON_UnicodeErrorParameters uep;
  memset(&uep, 0, sizeof(uep));
  uep.m_error_status = 0;
  uep.m_error_mask = error_mask;
  uep.m_error_code_point = ON_UnicodeCodePoint::ON_ReplacementCharacter;
  return uep;
}
const struct ON_UnicodeErrorParameters ON_UnicodeErrorParameters::MaskErrors = ON_Internal_UnicodeErrorParameters_Default(0xFFFFFFFF);
const struct ON_UnicodeErrorParameters ON_UnicodeErrorParameters::FailOnErrors = ON_Internal_UnicodeErrorParameters_Default(0);


const ON_UnicodeShortCodePoint ON_UnicodeShortCodePoint::Null = ON_UnicodeShortCodePoint::Create(0);
const ON_UnicodeShortCodePoint ON_UnicodeShortCodePoint::ReplacementCharacter = ON_UnicodeShortCodePoint::Create(0xFFFD);
const ON_UnicodeShortCodePoint ON_UnicodeShortCodePoint::ByteOrderMark = ON_UnicodeShortCodePoint::Create(0xFFFE);
const ON_UnicodeShortCodePoint ON_UnicodeShortCodePoint::Error = ON_UnicodeShortCodePoint::Create(0xFFFF);

const ON_Big5CodePoint ON_Big5CodePoint::Null = ON_Big5CodePoint::Create(0);
const ON_Big5CodePoint ON_Big5CodePoint::WindowsEuro = ON_Big5CodePoint::Create(0xA3E1);
const ON_Big5CodePoint ON_Big5CodePoint::Error = ON_Big5CodePoint::Create(0xFFFF);

const ON_Big5UnicodePair ON_Big5UnicodePair::Null = ON_Big5UnicodePair::Create(ON_Big5CodePoint::Null, ON_UnicodeShortCodePoint::Null);
const ON_Big5UnicodePair ON_Big5UnicodePair::Error = ON_Big5UnicodePair::Create(ON_Big5CodePoint::Error, ON_UnicodeShortCodePoint::Error);

const ON_String ON_String::EmptyString;
static const ON_String ON_Internal_ByteOrderMark()
{
  // UTF-8 encoded byte order mark.
  const unsigned char bom[4] = {0xEFU,0xBBU,0xBFU,0x00U};
  return ON_String((const char*)bom);
}
const ON_String ON_String::ByteOrderMark(ON_Internal_ByteOrderMark());

const ON_wString ON_wString::EmptyString;
const ON_wString ON_wString::ByteOrderMark((wchar_t)ON_UnicodeCodePoint::ON_ByteOrderMark);

const ON_NameHash ON_NameHash::UnsetNameHash;
const ON_NameHash ON_NameHash::EmptyNameHash = ON_NameHash::CreateIdAndEmptyName(ON_nil_uuid);
const ON_wString ON_ModelComponent::ReferencePrefixDelimiter(L" : ");
const ON_wString ON_ModelComponent::ReferencePrefixSeparator(L">");
const ON_wString ON_ModelComponent::NamePathSeparator(L"::");

const char ON_FileSystemPath::DirectorySeparatorAsChar =
#if defined(ON_RUNTIME_WIN)
// Windows
ON_String::Backslash
#else
// Apple, Android, Unix, ...
ON_String::Slash
#endif
;
const wchar_t ON_FileSystemPath::DirectorySeparator = (wchar_t)ON_FileSystemPath::DirectorySeparatorAsChar;

const char ON_FileSystemPath::AlternateDirectorySeparatorAsChar =
#if defined(ON_RUNTIME_WIN)
// Windows
ON_String::Slash
#else
// Apple, Android, Unix, ...
ON_String::Backslash
#endif
;
const wchar_t ON_FileSystemPath::AlternateDirectorySeparator = (wchar_t)ON_FileSystemPath::AlternateDirectorySeparatorAsChar;



const ON_ContentHash ON_ContentHash::Unset;
const ON_FileReference ON_FileReference::Unset;

const ON_3dmRevisionHistory ON_3dmRevisionHistory::Empty;
const ON_3dmProperties ON_3dmProperties::Empty;



static ON_Xform Internal_ON_Xform_Init(double x, bool bDiagonal)
{
  ON_Xform xform;
  memset(&xform, 0, sizeof(xform));
  if (bDiagonal)
  {
    xform.m_xform[0][0] = x;
    xform.m_xform[1][1] = x;
    xform.m_xform[2][2] = x;
    xform.m_xform[3][3] = 1.0;
  }
  else
  {
    double* p = &xform.m_xform[0][0];
    double* p1 = p + 16;
    while (p < p1)
      *p++ = x;
  }
  return xform;
}

const ON_Xform ON_Xform::IdentityTransformation = Internal_ON_Xform_Init(1.0, true);
const ON_Xform ON_Xform::ZeroTransformation = Internal_ON_Xform_Init(0.0, true);

const ON_Xform ON_Xform::Zero4x4 = Internal_ON_Xform_Init(0.0, false);
const ON_Xform ON_Xform::Unset = Internal_ON_Xform_Init(ON_UNSET_VALUE, false);
const ON_Xform ON_Xform::Nan = Internal_ON_Xform_Init(ON_DBL_QNAN, false);

const double ON_SurfaceCurvature::InfinteRadius = 1e300;
const ON_SurfaceCurvature ON_SurfaceCurvature::Nan = ON_SurfaceCurvature::CreateFromPrincipalCurvatures(ON_DBL_QNAN, ON_DBL_QNAN);
const ON_SurfaceCurvature ON_SurfaceCurvature::Zero = ON_SurfaceCurvature::CreateFromPrincipalCurvatures(0.0, 0.0);

const ON_2dPoint ON_2dPoint::Origin(0.0, 0.0);
const ON_2dPoint ON_2dPoint::UnsetPoint(ON_UNSET_VALUE, ON_UNSET_VALUE);
const ON_2dPoint ON_2dPoint::NanPoint(ON_DBL_QNAN, ON_DBL_QNAN);


const ON_3dPoint ON_3dPoint::Origin(0.0, 0.0, 0.0);
const ON_3dPoint ON_3dPoint::UnsetPoint(ON_UNSET_VALUE, ON_UNSET_VALUE, ON_UNSET_VALUE);
const ON_3dPoint ON_3dPoint::NanPoint(ON_DBL_QNAN, ON_DBL_QNAN, ON_DBL_QNAN);

const ON_4dPoint ON_4dPoint::Zero(0.0, 0.0, 0.0, 0.0);
const ON_4dPoint ON_4dPoint::Nan(ON_DBL_QNAN, ON_DBL_QNAN, ON_DBL_QNAN, ON_DBL_QNAN);


const ON_Triangle ON_Triangle::ZeroTriangle(ON_3dPoint::Origin, ON_3dPoint::Origin, ON_3dPoint::Origin);
const ON_Triangle ON_Triangle::UnsetTriangle(ON_3dPoint::UnsetPoint, ON_3dPoint::UnsetPoint, ON_3dPoint::UnsetPoint);
const ON_Triangle ON_Triangle::NanTriangle(ON_3dPoint::NanPoint, ON_3dPoint::NanPoint, ON_3dPoint::NanPoint);

const ON_2dVector ON_2dVector::ZeroVector(0.0, 0.0);
const ON_2dVector ON_2dVector::XAxis(1.0, 0.0);
const ON_2dVector ON_2dVector::YAxis(0.0, 1.0);
const ON_2dVector ON_2dVector::UnsetVector(ON_UNSET_VALUE, ON_UNSET_VALUE);
const ON_2dVector ON_2dVector::NanVector(ON_DBL_QNAN, ON_DBL_QNAN);

const ON_3dVector ON_3dVector::ZeroVector(0.0, 0.0, 0.0);
const ON_3dVector ON_3dVector::XAxis(1.0, 0.0, 0.0);
const ON_3dVector ON_3dVector::YAxis(0.0, 1.0, 0.0);
const ON_3dVector ON_3dVector::ZAxis(0.0, 0.0, 1.0);
const ON_3dVector ON_3dVector::UnsetVector(ON_UNSET_VALUE, ON_UNSET_VALUE, ON_UNSET_VALUE);
const ON_3dVector ON_3dVector::NanVector(ON_DBL_QNAN, ON_DBL_QNAN, ON_DBL_QNAN);

const ON_2fPoint ON_2fPoint::Origin(0.0f, 0.0f);
const ON_2fPoint ON_2fPoint::NanPoint(ON_FLT_QNAN, ON_FLT_QNAN);

const ON_3fPoint ON_3fPoint::Origin(0.0f, 0.0f, 0.0f);
const ON_3fPoint ON_3fPoint::NanPoint(ON_FLT_QNAN, ON_FLT_QNAN, ON_FLT_QNAN);

const ON_4fPoint ON_4fPoint::Zero(0.0f, 0.0f, 0.0f, 0.0f);
const ON_4fPoint ON_4fPoint::Nan(ON_FLT_QNAN, ON_FLT_QNAN, ON_FLT_QNAN, ON_FLT_QNAN);

const ON_2fVector ON_2fVector::NanVector(ON_FLT_QNAN, ON_FLT_QNAN);
const ON_2fVector ON_2fVector::ZeroVector(0.0f, 0.0f);
const ON_2fVector ON_2fVector::XAxis(1.0f, 0.0f);
const ON_2fVector ON_2fVector::YAxis(0.0f, 1.0f);

const ON_3fVector ON_3fVector::NanVector(ON_FLT_QNAN, ON_FLT_QNAN, ON_FLT_QNAN);
const ON_3fVector ON_3fVector::ZeroVector(0.0f, 0.0f, 0.0f);
const ON_3fVector ON_3fVector::XAxis(1.0f, 0.0f, 0.0f);
const ON_3fVector ON_3fVector::YAxis(0.0f, 1.0f, 0.0f);
const ON_3fVector ON_3fVector::ZAxis(0.0f, 0.0f, 1.0f);

const ON_WindingNumber ON_WindingNumber::Unset;

// Do not increase this tolerance to fix a specific bug.
// This tolerance is used after input has been cleaned up
// to detect flaws.
const double ON_Symmetry::ZeroTolerance = 1.0e-8; 

const ON_Symmetry ON_Symmetry::Unset;

// {3C6C7ABD-F3D5-41C2-96C9-DB9AEAF06E90}
const ON_UUID ON_Symmetry::ReflectId =
{ 0x3c6c7abd, 0xf3d5, 0x41c2, { 0x96, 0xc9, 0xdb, 0x9a, 0xea, 0xf0, 0x6e, 0x90 } };

// {C1592254-DEAC-4E8E-B01E-0522450E03F7}
const ON_UUID ON_Symmetry::RotateId =
{ 0xc1592254, 0xdeac, 0x4e8e, { 0xb0, 0x1e, 0x5, 0x22, 0x45, 0xe, 0x3, 0xf7 } };

// {9133927D-5A4E-4DDD-9924-EF3A6360C19A}
const ON_UUID ON_Symmetry::ReflectAndRotateId =
{ 0x9133927d, 0x5a4e, 0x4ddd, { 0x99, 0x24, 0xef, 0x3a, 0x63, 0x60, 0xc1, 0x9a } };

static ON_BoundingBox Internal_BoundingBoxInit(double x)
{
  ON_BoundingBox bbox;
  bbox.m_min.x = x;
  bbox.m_min.y = x;
  bbox.m_min.z = x;
  bbox.m_max.x = x;
  bbox.m_max.y = x;
  bbox.m_max.z = x;
  return bbox;
}
const ON_BoundingBox ON_BoundingBox::EmptyBoundingBox;
const ON_BoundingBox ON_BoundingBox::UnsetBoundingBox = Internal_BoundingBoxInit(ON_UNSET_VALUE);
const ON_BoundingBox ON_BoundingBox::NanBoundingBox = Internal_BoundingBoxInit(ON_DBL_QNAN);

const ON_UnitSystem ON_UnitSystem::None(ON::LengthUnitSystem::None);
const ON_UnitSystem ON_UnitSystem::Angstroms(ON::LengthUnitSystem::Angstroms);
const ON_UnitSystem ON_UnitSystem::Nanometers(ON::LengthUnitSystem::Nanometers);
const ON_UnitSystem ON_UnitSystem::Microns(ON::LengthUnitSystem::Microns);
const ON_UnitSystem ON_UnitSystem::Millimeters(ON::LengthUnitSystem::Millimeters);
const ON_UnitSystem ON_UnitSystem::Centimeters(ON::LengthUnitSystem::Centimeters);
const ON_UnitSystem ON_UnitSystem::Decimeters(ON::LengthUnitSystem::Decimeters);
const ON_UnitSystem ON_UnitSystem::Meters(ON::LengthUnitSystem::Meters);
const ON_UnitSystem ON_UnitSystem::Dekameters(ON::LengthUnitSystem::Dekameters);
const ON_UnitSystem ON_UnitSystem::Hectometers(ON::LengthUnitSystem::Hectometers);
const ON_UnitSystem ON_UnitSystem::Kilometers(ON::LengthUnitSystem::Kilometers);
const ON_UnitSystem ON_UnitSystem::Megameters(ON::LengthUnitSystem::Megameters);
const ON_UnitSystem ON_UnitSystem::Gigameters(ON::LengthUnitSystem::Gigameters);
const ON_UnitSystem ON_UnitSystem::Microinches(ON::LengthUnitSystem::Microinches);
const ON_UnitSystem ON_UnitSystem::Mils(ON::LengthUnitSystem::Mils);
const ON_UnitSystem ON_UnitSystem::Inches(ON::LengthUnitSystem::Inches);
const ON_UnitSystem ON_UnitSystem::Feet(ON::LengthUnitSystem::Feet);
const ON_UnitSystem ON_UnitSystem::Yards(ON::LengthUnitSystem::Yards);
const ON_UnitSystem ON_UnitSystem::Miles(ON::LengthUnitSystem::Miles);
const ON_UnitSystem ON_UnitSystem::PrinterPoints(ON::LengthUnitSystem::PrinterPoints);
const ON_UnitSystem ON_UnitSystem::PrinterPicas(ON::LengthUnitSystem::PrinterPicas);
const ON_UnitSystem ON_UnitSystem::NauticalMiles(ON::LengthUnitSystem::NauticalMiles);
const ON_UnitSystem ON_UnitSystem::AstronomicalUnits(ON::LengthUnitSystem::AstronomicalUnits);
const ON_UnitSystem ON_UnitSystem::LightYears(ON::LengthUnitSystem::LightYears);
const ON_UnitSystem ON_UnitSystem::Parsecs(ON::LengthUnitSystem::Parsecs);
const ON_UnitSystem ON_UnitSystem::Unset(ON::LengthUnitSystem::Unset);

const ON_LengthUnitName ON_LengthUnitName::None;
const ON_AngleUnitName ON_AngleUnitName::None;

const ON_LengthValue ON_LengthValue::Unset;
const ON_LengthValue ON_LengthValue::Zero = ON_LengthValue::Create(0.0, ON::LengthUnitSystem::None, 0, ON_LengthValue::StringFormat::CleanDecimal);

const ON_AngleValue ON_AngleValue::Unset;
const ON_AngleValue ON_AngleValue::Zero = ON_AngleValue::Create(0.0, ON::AngleUnitSystem::None, 0, ON_AngleValue::StringFormat::CleanDecimal );

const ON_ScaleValue ON_ScaleValue::Unset;
const ON_ScaleValue ON_ScaleValue::OneToOne = ON_ScaleValue::Create(
  ON_LengthValue::Create(1.0, ON::LengthUnitSystem::None, 0, ON_LengthValue::StringFormat::CleanDecimal),
  ON_LengthValue::Create(1.0, ON::LengthUnitSystem::None, 0, ON_LengthValue::StringFormat::CleanDecimal),
  ON_ScaleValue::ScaleStringFormat::RatioFormat
);

// ON_PTR_SEMAPHORE1 triggers a special case in the constructor.
// See ON_TextLog::AppendText() and Internal_TextLogIsNull() for implementation
// details.
ON_TextLog ON_TextLog::Null( (FILE*)ON_PTR_SEMAPHORE1 );

// Discuss any changes of these values with Dale Lear
//
// For 32 bit float based OpenGL drivers, the value of
// the ON_Viewport::DefaultMinNearOverFar constant must 
// be <0.01 and >= 0.0001.  
// If you change this value, you need to retest RR 8902 on OpenGL
// drivers that (internally) use float precision transformations.
// Some OpenGL drivers, like the Microsoft software emulation
// driver for XP crash in some cases when near/far > 1e8.
//
// ON_Viewport::DefaultMinNearOverFar = 0.001    // used in Rhino 3.0 beta testing until 11 Sep 2002
// ON_Viewport::DefaultMinNearOverFar = 0.01     // used for Rhino 3.0 CD1 and CD2
// ON_Viewport::DefaultMinNearOverFar = 0.000001 // used for Rhino 3.0 CD3
// ON_Viewport::DefaultMinNearOverFar = 0.0001   // used for Rhino 4.0 Fixes RR 8902
//
// Discuss any changes of these values with Dale Lear
const double ON_Viewport::DefaultNearDist = 0.005;
const double ON_Viewport::DefaultFarDist = 1000.0;
const double ON_Viewport::DefaultMinNearDist = 0.0001;
const double ON_Viewport::DefaultMinNearOverFar = 0.0001;

const ON_3dVector ON_Viewport::Default3dCameraDirection(-0.43301270189221932338186158537647,0.75,-0.5);
const ON_3dPoint ON_Viewport::DefaultCameraLocation(0.0, 0.0, 100.0);
const ON_Viewport ON_Viewport::DefaultTopViewYUp;
static ON_Viewport Internal_ON_Viewport_DefaultPerspectiveView_Init()
{
  ON_Viewport vp;
  vp.SetCameraDirection(ON_Viewport::Default3dCameraDirection);
  vp.SetCameraUp(ON_3dVector::ZAxis);
  vp.SetCameraLocation(ON_Viewport::DefaultCameraLocation.DistanceTo(ON_3dPoint::Origin)*vp.CameraZ());

  return vp;
}
const ON_Viewport ON_Viewport::DefaultPerspectiveViewZUp = Internal_ON_Viewport_DefaultPerspectiveView_Init();


const ON_3dmIOSettings ON_3dmIOSettings::Default;
const ON_3dmConstructionPlaneGridDefaults ON_3dmConstructionPlaneGridDefaults::Default;

ON_EarthAnchorPoint Internal_EarthAnchorPointConstant(int which)
{
  ON_EarthAnchorPoint eap;
  switch (which)
  {
  case 1: // Seattle Space Needle
    {
      const double latitude_degrees = 47.620397; // Cal Topo Maps (downloaded June 24, 2016)
      const double longitude_degrees = -122.349179; // Cal Topo Maps (downloaded June 24, 2016)
      const double ground_elevation_feet = 207.0; // feet c. Geonames - Cal Topo Maps (downloaded June 24, 2016)
      const double observation_deck_height_feet = 520.0; // feet above the ground  http://www.spaceneedle.com/fun-facts/
      eap.SetEarthLocation(
        ON::EarthCoordinateSystem::MeanSeaLevel, 
        ON::LengthUnitSystem::Feet,
        latitude_degrees,
        longitude_degrees,
        ground_elevation_feet + observation_deck_height_feet
      );
    }
    break;
  }
  return eap;
}
const ON_EarthAnchorPoint ON_EarthAnchorPoint::Unset = Internal_EarthAnchorPointConstant(0);
const ON_EarthAnchorPoint ON_EarthAnchorPoint::SeattleSpaceNeedle = Internal_EarthAnchorPointConstant(1);

const ON_3dmAnnotationSettings ON_3dmAnnotationSettings::Default;

const ON_3dmAnnotationContext ON_3dmAnnotationContext::Default;

const ON_3dmArchiveTableStatus ON_3dmArchiveTableStatus::Unset;

const wchar_t* ON_TextDot::DefaultFontFace = L"Arial";
const int ON_TextDot::DefaultHeightInPoints = 14;
const int ON_TextDot::MinimumHeightInPoints = 3;
const ON_TextDot ON_TextDot::Unset;

const ON_Locale ON_Locale::Ordinal = ON_Locale::FromWindowsLCID(ON_Locale::OrdinalLCID);
const ON_Locale ON_Locale::InvariantCulture = ON_Locale::FromWindowsLCID(ON_Locale::InvariantCultureLCID);

// DLL_Main() andc other appropriate places in Rhino application
// initialization call ON_Locale::SetCurrentCulture() to initialize
// ON_Locale::m_CurrentCulture.
ON_Locale ON_Locale::m_CurrentCulture = ON_Locale::Ordinal;
const ON_Locale& ON_Locale::CurrentCulture = ON_Locale::m_CurrentCulture;

static ON_ClippingRegionPoints Internal_ON_ClippingRegionPoints_EmptyInit()
{
  ON_ClippingRegionPoints empty_clip_points;
  memset(&empty_clip_points, 0, sizeof(empty_clip_points));
  return empty_clip_points;
}

const ON_ClippingRegionPoints ON_ClippingRegionPoints::Empty = Internal_ON_ClippingRegionPoints_EmptyInit();

static ON_PickPoint Internal_ON_PickPoint_UnsetInit()
{
  ON_PickPoint unset_pick_point;
  double* p = unset_pick_point.m_t;
  double* p1 = p + sizeof(unset_pick_point.m_t) / sizeof(unset_pick_point.m_t[0]);
  while (p < p1)
    *p++ = ON_UNSET_VALUE;
  return unset_pick_point;
}

const ON_PickPoint ON_PickPoint::Unset = Internal_ON_PickPoint_UnsetInit();

const ON_Color ON_Color::UnsetColor(ON_UNSET_COLOR);
const ON_Color ON_Color::Black(0, 0, 0);
const ON_Color ON_Color::White(255, 255, 255);
const ON_Color ON_Color::SaturatedRed(255, 0, 0);
const ON_Color ON_Color::SaturatedGreen(0, 255, 0);
const ON_Color ON_Color::SaturatedBlue(0, 0, 255);
const ON_Color ON_Color::SaturatedYellow(255, 255, 0);
const ON_Color ON_Color::SaturatedCyan(0, 255, 255);
const ON_Color ON_Color::SaturatedMagenta(255, 0, 255);
const ON_Color ON_Color::SaturatedGold(255, 191, 0);
const ON_Color ON_Color::Gray105(105, 105, 105);
const ON_Color ON_Color::Gray126(126, 126, 126);
const ON_Color ON_Color::Gray160(160, 160, 160);
const ON_Color ON_Color::Gray230(230, 230, 230);
const ON_Color ON_Color::Gray250(250, 250, 250);

const ON_4fColor ON_4fColor::Unset;

const ON_UuidIndex ON_UuidIndex::NilIndex = ON_UuidIndex();
const ON_UuidPtr ON_UuidPtr::NilPtr = ON_UuidPtr();

const ON_Line ON_Line::ZeroLine(ON_3dPoint::Origin, ON_3dPoint::Origin);
const ON_Line ON_Line::UnsetLine(ON_3dPoint::UnsetPoint, ON_3dPoint::UnsetPoint);
const ON_Line ON_Line::NanLine(ON_3dPoint::NanPoint, ON_3dPoint::NanPoint);

const ON_PlaneEquation ON_PlaneEquation::UnsetPlaneEquation(ON_UNSET_VALUE, ON_UNSET_VALUE, ON_UNSET_VALUE, ON_UNSET_VALUE);
const ON_PlaneEquation ON_PlaneEquation::ZeroPlaneEquation(0.0, 0.0, 0.0, 0.0);
const ON_PlaneEquation ON_PlaneEquation::NanPlaneEquation(ON_DBL_QNAN, ON_DBL_QNAN, ON_DBL_QNAN, ON_DBL_QNAN);
const ON_PlaneEquation ON_PlaneEquation::WorldXY(0.0, 0.0, 1.0, 0.0);
const ON_PlaneEquation ON_PlaneEquation::WorldYZ(1.0, 0.0, 0.0, 0.0);
const ON_PlaneEquation ON_PlaneEquation::WorldZX(0.0, 1.0, 0.0, 0.0);


const ON_Plane ON_Plane::World_xy(ON_3dPoint::Origin, ON_3dVector::XAxis, ON_3dVector::YAxis);
const ON_Plane ON_Plane::World_yz(ON_3dPoint::Origin, ON_3dVector::YAxis, ON_3dVector::ZAxis);
const ON_Plane ON_Plane::World_zx(ON_3dPoint::Origin, ON_3dVector::ZAxis, ON_3dVector::XAxis);

// obsolete names for world planes
const ON_Plane ON_xy_plane = ON_Plane::World_xy;
const ON_Plane ON_yz_plane = ON_Plane::World_yz;
const ON_Plane ON_zx_plane = ON_Plane::World_zx;

static ON_Plane ON_Plane_UnsetPlane()
{
  ON_Plane unset_plane;
  unset_plane.xaxis = ON_3dVector::UnsetVector;
  unset_plane.yaxis = ON_3dVector::UnsetVector;
  unset_plane.zaxis = ON_3dVector::UnsetVector;
  unset_plane.origin = ON_3dPoint::UnsetPoint;
  unset_plane.plane_equation = ON_PlaneEquation::UnsetPlaneEquation;
  return unset_plane;
}

const ON_Plane ON_Plane::UnsetPlane(ON_Plane_UnsetPlane());

static ON_Plane Internal_ON_Plane_NanPlane()
{
  ON_Plane nan_plane;
  nan_plane.xaxis = ON_3dVector::NanVector;
  nan_plane.yaxis = ON_3dVector::NanVector;
  nan_plane.zaxis = ON_3dVector::NanVector;
  nan_plane.origin = ON_3dPoint::NanPoint;
  nan_plane.plane_equation = ON_PlaneEquation::NanPlaneEquation;
  return nan_plane;
}
const ON_Plane ON_Plane::NanPlane(Internal_ON_Plane_NanPlane());

// ON_SubDDisplayParameters statics before ON_MeshParameters statics
const ON_SubDDisplayParameters ON_SubDDisplayParameters::Empty;
const ON_SubDDisplayParameters ON_SubDDisplayParameters::ExtraCoarse = ON_SubDDisplayParameters::CreateFromDisplayDensity(ON_SubDDisplayParameters::ExtraCoarseDensity);
const ON_SubDDisplayParameters ON_SubDDisplayParameters::Coarse = ON_SubDDisplayParameters::CreateFromDisplayDensity(ON_SubDDisplayParameters::CoarseDensity);
const ON_SubDDisplayParameters ON_SubDDisplayParameters::Medium = ON_SubDDisplayParameters::CreateFromDisplayDensity(ON_SubDDisplayParameters::MediumDensity);
const ON_SubDDisplayParameters ON_SubDDisplayParameters::Fine = ON_SubDDisplayParameters::CreateFromDisplayDensity(ON_SubDDisplayParameters::FineDensity);
const ON_SubDDisplayParameters ON_SubDDisplayParameters::ExtraFine = ON_SubDDisplayParameters::CreateFromDisplayDensity(ON_SubDDisplayParameters::ExtraFineDensity);
const ON_SubDDisplayParameters ON_SubDDisplayParameters::Default = ON_SubDDisplayParameters::CreateFromDisplayDensity(ON_SubDDisplayParameters::DefaultDensity);

// {F15F67AA-4AF9-4B25-A3B8-517CEDDAB134}
const ON_UUID ON_MeshParameters::RhinoLegacyMesherId = { 0xf15f67aa, 0x4af9, 0x4b25,{ 0xa3, 0xb8, 0x51, 0x7c, 0xed, 0xda, 0xb1, 0x34 } };

// {EB6F6F3F-F975-4546-9D1C-64E9423BEB7F}
const ON_UUID ON_MeshParameters::PangolinMesherId = { 0xeb6f6f3f, 0xf975, 0x4546,{ 0x9d, 0x1c, 0x64, 0xe9, 0x42, 0x3b, 0xeb, 0x7f } };

static ON_MeshParameters Internal_ON_MeshParameters_Constants(
  int selector
  )
{
  ON_MeshParameters mp;

  // If you change any parameter values, put your name, the date, and the reasons for
  // the change in a comment by the changed value. Include the previous value in
  // your comment. This is critically important so we can keep track of what we are
  // trying to accomplish.
  //
  // You must also update the mesh parameters file reading code so that settings with old defaults
  // are replaced with setting that have the new defaults AND old defaults get saved in earlier version
  // 3dm files. This requires somebody with a solid understanding of how ON_MeshParameters::Read()/Write()
  // works, how saving earlier versions of 3dm files works, and how reading old version files works.

  switch (selector)
  {
  case 0: // ON_MeshParameters::DefaultMesh
    break;

  case 1: 
    // ON_MeshParameters::FastRenderMesh
    // Added 27 April 2006 for the Meshkateers
    //   Attempting to make jagged and faster render meshes a little
    //   more dense.
    //
    // Turn off everything ...
    mp.SetComputeCurvature(false);
    mp.SetTolerance(0.0);
    mp.SetJaggedSeams(false);
    mp.SetMaximumEdgeLength(0.0);
    mp.SetGridAspectRatio(0.0);
    mp.SetGridMaxCount(0);
    mp.SetGridAngleRadians(0.0);
    mp.SetGridAmplification(0.0);
    mp.SetRefineAngleRadians(0.0);

    // ... except ...
    // The m_relative_tolerance setting must be set so that
    // 0.0005 = ON_MeshParameters::Tolerance(m_relative_tolerance,1.0).
    mp.SetRelativeTolerance(0.65);
    //double x = Tolerance(m_relative_tolerance,1.0);

    mp.SetGridMinCount(16);
    mp.SetMinimumEdgeLength(0.0001);
    mp.SetRefine(true);
    mp.SetSimplePlanes(true);

    mp.SetTextureRange(2); // Don't change this without speaking to Dale Lear

                            //{
                            //  // 16 July, 2002 - copied V2 hard coded "jagged and faster" render mesh settings
                            //  //
                            //  // Settings used in V2, V3 and early V4 beta
                            //  mp.m_refine_angle       = 20.0*ON_PI/180.0;
                            //  mp.m_grid_angle         = 20.0*ON_PI/180.0;
                            //  mp.m_grid_aspect_ratio  = 0.0;
                            //  mp.m_min_edge_length    = 0.0001;
                            //  mp.m_max_edge_length    = 0.0;
                            //  mp.m_tolerance          = 0.0;
                            //  mp.m_grid_min_count     = 16;
                            //  mp.m_bRefine            = 1;
                            //  mp.m_bJaggedSeams       = 0;
                            //  mp.m_bSimplePlanes      = 0;
                            //}
    break;

  case 2: // ON_MeshParameters::QualityRenderMesh
          // Added 27 April 2006 for the Meshkateers
          //   Attempting to make smooth and slower render meshing a little
          //   faster.
          //
          // Turn off everything ...
    mp.SetComputeCurvature(false);
    mp.SetTolerance(0.0);
    mp.SetJaggedSeams(false);
    mp.SetMaximumEdgeLength(0.0);
    mp.SetGridAspectRatio(0.0);
    mp.SetGridMaxCount(0);
    mp.SetGridAngleRadians(0.0);
    mp.SetGridAmplification(0.0);

    // ... except ...
    // The m_relative_tolerance setting must be set so that
    // 0.00025 = ON_MeshParameters::Tolerance(m_relative_tolerance,1.0).
    mp.SetRelativeTolerance(0.8);
    //double x = Tolerance(m_relative_tolerance,1.0);

    mp.SetGridMinCount(16);
    mp.SetMinimumEdgeLength(0.0001);
    mp.SetRefine(true);
    mp.SetSimplePlanes(true);
    mp.SetRefineAngleDegrees(20.0);

    mp.SetTextureRange(2); // Don't change this without speaking to Dale Lear


                            //// 16 July, 2002 - copied V2 hard coded "smooth and slower" render mesh settings
                            ////
                            //// Settings used in V2, V3 and early V4 beta
                            //mp.Setrefine_angle       = 15.0*ON_PI/180.0;
                            //mp.Setgrid_angle         = 15.0*ON_PI/180.0;
                            //mp.Setgrid_aspect_ratio  = 6.0;
                            //mp.Setmin_edge_length    = 0.0001;
                            //mp.Setmax_edge_length    = 0.0;
                            //mp.Settolerance          = 0.0;
                            //mp.Setgrid_min_count     = 16;
                            //mp.SetbRefine            = 1;
                            //mp.SetbJaggedSeams       = 0;
                            //mp.SetbSimplePlanes      = 0;
    break;

  case 3: // ON_MeshParameters::DefaultAnalysisMesh
    // 7 July 2006 Dale Lear Rhino 5
    //    I switched from the default constructor to the density=0.5 constructor to fix RR 10330.
    //mp = ON_MeshParameters(0.5, ON_MeshParameters::DefaultMesh.MinimumEdgeLength());
    //mp.SetTextureRange(1); // m_texture_range must be 1.  Do not change this setting.

    // Rhino 6, 7 defaults;
    mp = ON_MeshParameters(0.8, ON_MeshParameters::DefaultMesh.MinimumEdgeLength());
    mp.SetTextureRange(1); // m_texture_range must be 1.  Do not change this setting.
    mp.SetGridAspectRatio(0.0);
    mp.SetGridAngleRadians(20.0*ON_DEGREES_TO_RADIANS);
    mp.SetGridAmplification(1.0);
    mp.SetRefineAngleRadians(20.0 * ON_DEGREES_TO_RADIANS);
    mp.SetComputeCurvature(true);
    mp.SetGridMinCount(16);
    mp.SetSubDDisplayParameters(ON_SubDDisplayParameters::Default);
    mp.SetRefine(true);

    break;
  }

  if (0 != selector)
  {
    if (1 == selector )
    {
      // ON_MeshParameters::DefaultMesh has been initialized.
      // ON_MeshParameters::DefaultMesh must be initialized before ContentHash() can be used.
      ON_MeshParameters::DefaultMesh.ContentHash();
    }
    // Compute cached sha1 content hash.
    mp.ContentHash();
  }

  return mp;
}

const ON_MeshParameters ON_MeshParameters::DefaultMesh = Internal_ON_MeshParameters_Constants(0);
const ON_MeshParameters ON_MeshParameters::FastRenderMesh = Internal_ON_MeshParameters_Constants(1);
const ON_MeshParameters ON_MeshParameters::QualityRenderMesh = Internal_ON_MeshParameters_Constants(2);
const ON_MeshParameters ON_MeshParameters::DefaultAnalysisMesh = Internal_ON_MeshParameters_Constants(3);

bool ON_MeshParameters_AreValid()
{
  // This is a validation test to insure the code that sets default mesh parameters
  // and the code that detects default mesh parameters works correctly.
  // This validation test passes as of November 2020. If ON_ERROR() is called in this function
  // it means new bugs have been introduced. These need to be fixed immediately in order to
  // keep the code that generates display meshes working properly.
  if (ON_MeshParameters::Type::Default != ON_MeshParameters::DefaultMesh.GeometrySettingsType())
  {
    ON_ERROR("ON_MeshParameters::DefaultMesh.GeometrySettingsType() returned an unexpected value.");
    return false;
  }
  if (ON_MeshParameters::Type::FastRender != ON_MeshParameters::FastRenderMesh.GeometrySettingsType())
  {
    ON_ERROR("ON_MeshParameters::FastRenderMesh.GeometrySettingsType() returned an unexpected value.");
    return false;
  }
  if (ON_MeshParameters::Type::QualityRender != ON_MeshParameters::QualityRenderMesh.GeometrySettingsType())
  {
    ON_ERROR("ON_MeshParameters::QualityRenderMesh.GeometrySettingsType() returned an unexpected value.");
    return false;
  }
  if (ON_MeshParameters::Type::DefaultAnalysis != ON_MeshParameters::DefaultAnalysisMesh.GeometrySettingsType())
  {
    ON_ERROR("ON_MeshParameters::DefaultAnalysisMesh.GeometrySettingsType() returned an unexpected value.");
    return false;
  }
  for (double normalized_mesh_density = 0.0; normalized_mesh_density <= 1.0; normalized_mesh_density += 0.125)
  {
    const ON_MeshParameters mp = ON_MeshParameters::CreateFromMeshDensity(normalized_mesh_density);
    if (ON_MeshParameters::Type::FromMeshDensity != mp.GeometrySettingsType())
    {
      ON_ERROR("ON_MeshParameters::ON_MeshParameters::CreateFromMeshDensity(...).GeometrySettingsType() returned an unexpected value.");
      return false;
    }
    if (normalized_mesh_density != mp.MeshDensity())
    {
      ON_ERROR("ON_MeshParameters::ON_MeshParameters::CreateFromMeshDensity(...).MeshDensity() returned an unexpected value.");
      return false;
    }
  }
  return true;
}

const static bool Internal_ON_MeshParameters_AreValid_ = ON_MeshParameters_AreValid();

const ON_3dmUnitsAndTolerances ON_3dmUnitsAndTolerances::Millimeters;

const ON_Circle ON_Circle::UnitCircle;
const ON_Arc ON_Arc::UnitCircle;

const ON_3dmRenderSettings ON_3dmRenderSettings::Default;

const ON_3dmSettings ON_3dmSettings::Default;

const ON_ProgressStepCounter ON_ProgressStepCounter::Empty;

const ON_HistoryRecord ON_HistoryRecord::Empty;

const ON_RTreeMemPool ON_RTreeMemPool::Empty;
const ON_RTree ON_RTree::Empty;

// {F5E3BAA9-A7A2-49FD-B8A1-66EB274A5F91}
const ON_UUID ON_MeshCache::RenderMeshId =
{ 0xf5e3baa9, 0xa7a2, 0x49fd,{ 0xb8, 0xa1, 0x66, 0xeb, 0x27, 0x4a, 0x5f, 0x91 } };

// {AC12F955-A29F-437B-A4C9-06C85B7FF57C}
const ON_UUID ON_MeshCache::AnalysisMeshId =
{ 0xac12f955, 0xa29f, 0x437b,{ 0xa4, 0xc9, 0x6, 0xc8, 0x5b, 0x7f, 0xf5, 0x7c } };

// {3AACA7F2-0444-4587-8083-A13C5BA0AE50}
const ON_UUID ON_MeshCache::PreviewMeshId =
{ 0x3aaca7f2, 0x444, 0x4587,{ 0x80, 0x83, 0xa1, 0x3c, 0x5b, 0xa0, 0xae, 0x50 } };

// {85D9E08D-386C-45C3-83DC-0C354685D504}
const ON_UUID ON_MeshCache::CoarseMeshId =
{ 0x85d9e08d, 0x386c, 0x45c3,{ 0x83, 0xdc, 0xc, 0x35, 0x46, 0x85, 0xd5, 0x4 } };

// {A2DAF594-F44B-44A6-A44B-E856CD7C05E8}
const ON_UUID ON_MeshCache::FineMeshId =
{ 0xa2daf594, 0xf44b, 0x44a6,{ 0xa4, 0x4b, 0xe8, 0x56, 0xcd, 0x7c, 0x5, 0xe8 } };

// {A82C0F1B-13E8-4DEC-AD35-D3DDD277203C}
const ON_UUID ON_MeshCache::AnyMeshId =
{ 0xa82c0f1b, 0x13e8, 0x4dec,{ 0xad, 0x35, 0xd3, 0xdd, 0xd2, 0x77, 0x20, 0x3c } };

const ON_MeshCache ON_MeshCache::Empty;

#if defined(OPENNURBS_ANNOTATION_TABLE_WIP)
const double ON_Table::MinColWidth    = 1.0;
const double ON_Table::MinRowHeight   = 0.1;
const double ON_Table::MinTableWidth  = 1.0;
const double ON_Table::MinTableHeight = 0.1;
#endif

const ON_2iPoint ON_2iPoint::Origin(0, 0);
const ON_2iPoint ON_2iPoint::Unset(ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX);

const ON_2iVector ON_2iVector::Zero(0, 0);
const ON_2iVector ON_2iVector::UnitX(1, 0);
const ON_2iVector ON_2iVector::UnitY(0, 1);
const ON_2iVector ON_2iVector::Unset(ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX);

const ON_2iBoundingBox ON_2iBoundingBox::Zero(ON_2iPoint::Origin,ON_2iPoint::Origin);
const ON_2iBoundingBox ON_2iBoundingBox::Unset(ON_2iPoint::Unset, ON_2iPoint::Unset);

const ON_2iSize ON_2iSize::Zero(0, 0);
const ON_2iSize ON_2iSize::Unset(ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX);

const ON_4iRect ON_4iRect::Zero(0, 0, 0, 0);
const ON_4iRect ON_4iRect::Unset(ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX, ON_UNSET_INT_INDEX);

const ON_2dSize ON_2dSize::Zero(0.0, 0.0);
const ON_2dSize ON_2dSize::Unset(ON_UNSET_VALUE, ON_UNSET_VALUE);

const ON_4dRect ON_4dRect::Zero(0.0, 0.0, 0.0, 0.0);
const ON_4dRect ON_4dRect::Unset(ON_UNSET_VALUE, ON_UNSET_VALUE, ON_UNSET_VALUE, ON_UNSET_VALUE);

const ON_OutlineFigure::Orientation ON_Outline::DefaultOuterOrientation = ON_OutlineFigure::Orientation::Clockwise;

const ON_OutlineFigurePoint ON_OutlineFigurePoint::Unset;
static ON_OutlineFigurePoint Internal_FontGlyphOutlinePoint()
{
  ON_OutlineFigurePoint p;
  p.m_point_type = ON_OutlineFigurePoint::Type::Error;
  return p;
}
const ON_OutlineFigurePoint ON_OutlineFigurePoint::Error(Internal_FontGlyphOutlinePoint());

const ON_OutlineFigure ON_OutlineFigure::Unset;

const ON_Outline ON_Outline::Unset;

const ON_FontGlyph ON_FontGlyph::Unset;

const ON_PANOSE1 ON_PANOSE1::Zero;

const double ON_FontMetrics::DefaultLineFeedRatio = 1.6;
const ON__UINT32 ON_FontMetrics::HeightOfCapitalCodePoint = 'I';
const ON_FontMetrics ON_FontMetrics::Unset;

static ON_FontMetrics Internal_LastResortNormalizedFontMetrics()
{
  /*
    Normalized font metrics:
      Units per EM = 256
      Ascent = 232
      Descent = -55
      Distance between baselines = 295
      Ascent of I = 184
      Strikeout thickness = 10
      Strikeout position = 92
      Underscore thickness = 19
      Underscore position = -37
    Font file metrics:
      Units per EM = 2048
      Ascent = 1854
      Descent = -434
      Distance between baselines = 2355
      Ascent of I = 1466
      Strikeout thickness = 75
      Strikeout position = 733
      Underscore thickness = 150
      Underscore position = -292
  
  */
  const int last_restort_UPM = 256; // needs to be as large or larger than "real" UPM
  ON_FontMetrics last_restort;
  last_restort.SetHeights(232,-55,last_restort_UPM,295);
  last_restort.SetAscentOfI(184);
  last_restort.SetStrikeout(92, 10);
  last_restort.SetUnderscore(-37, 19);

  if ( false == last_restort.IsSet() || false == last_restort.HeightsAreValid())
  {
    ON_ERROR("Immediately fix ON_FontMetrics::LastResortNormailizedMetrics");
    return last_restort;
  }

  // As of March 2018, ON_Font::Constants::AnnotationFontCellHeight = 256 and 
  // normalized_scale = 1.0; The code below is in place to handle any future
  // changes to ON_Font::Constants::AnnotationFontCellHeight.
  const double normalized_scale = ((double)ON_Font::Constants::AnnotationFontCellHeight) / ((double)last_restort.UPM());
  if ( 1.0 == normalized_scale )
    return last_restort;

  const ON_FontMetrics last_restort_normalized =  ON_FontMetrics::Scale(last_restort, normalized_scale);
  if ( false == last_restort_normalized.IsSet() || false == last_restort_normalized.HeightsAreValid())
  {
    ON_ERROR("Immediately fix scale section of ON_FontMetrics::LastResortNormailizedMetrics");
    return last_restort;
  }

  return last_restort_normalized;
}

const ON_FontMetrics ON_FontMetrics::LastResortNormalizedMetrics( Internal_LastResortNormalizedFontMetrics());

static ON_FontMetrics Internal_LastResortFontMetrics()
{
  const int last_restort_UPM = 2048; // needs to be as large or larger than any common "real" UPM
  const double scale = ((double)last_restort_UPM) / ((double)ON_Font::Constants::AnnotationFontCellHeight);
  ON_FontMetrics last_restort = ON_FontMetrics::Scale(ON_FontMetrics::LastResortNormalizedMetrics, scale);
  return last_restort;
}

const ON_FontMetrics ON_FontMetrics::LastResortMetrics( Internal_LastResortFontMetrics());

ON_Font::ON_GetGlyphMetricsFuncType ON_Font::Internal_CustomGetGlyphMetricsFunc = nullptr;
ON_Font::ON_GetFontMetricsFuncType ON_Font::Internal_CustomGetFontMetricsFunc = nullptr;
ON_Font::ON_GetGlyphOutlineFuncType ON_Font::Internal_CustomGetGlyphOutlineFunc = nullptr;

// Used to test freetype
//ON_Font::ON_GetGlyphMetricsFuncType ON_Font::Internal_CustomGetGlyphMetricsFunc = ON_FreeTypeGetGlyphMetrics;
//ON_Font::ON_GetFontMetricsFuncType ON_Font::Internal_CustomGetFontMetricsFunc = ON_FreeTypeGetFontMetrics;
//ON_Font::ON_GetGlyphOutlineFuncType ON_Font::Internal_CustomGetGlyphOutlineFunc = ON_FreeTypeGetGlyphOutline;

//// Used to test Windows DWrite
//#include "opennurbs_internal_glyph.h"
//ON_Font::ON_GetGlyphMetricsFuncType ON_Font::Internal_CustomGetGlyphMetricsFunc = ON_WindowsDWriteGetGlyphMetrics;
//ON_Font::ON_GetFontMetricsFuncType ON_Font::Internal_CustomGetFontMetricsFunc = ON_WindowsDWriteGetFontMetrics;
//ON_Font::ON_GetGlyphOutlineFuncType ON_Font::Internal_CustomGetGlyphOutlineFunc = ON_WindowsDWriteGetGlyphOutline;


unsigned int ON_Font::__runtime_serial_number_generator = 1;

static void Internal_SystemModelComponentInit(
  ON_UUID id,
  int index,
  const wchar_t* name,
  ON_ModelComponent& model_component
  )
{
  if (ON_nil_uuid != id)
    model_component.SetId(id);
  if (ON_UNSET_INT_INDEX != index)
    model_component.SetIndex(index);
  if (nullptr != name && 0 != name[0])
    model_component.SetName(name);

  // non-empty names are locked after application localization
  model_component.LockAllSettingsExceptName();
  if (model_component.NameIsEmpty())
    model_component.LockName();
}

const wchar_t* ON_Font::DefaultFamilyName()
{
  const wchar_t* s;
#if defined(ON_RUNTIME_WIN)
  s = L"Arial";
#elif defined(ON_RUNTIME_APPLE)
  s = L"Helvetica Neue";
#else
  s = L"Arial";
#endif
  return s;
}

const wchar_t* ON_Font::DefaultFaceName()
{
  const wchar_t* s;
#if defined(ON_RUNTIME_WIN)
  s = L"Regular";
#elif defined(ON_RUNTIME_APPLE)
  s = L"Regular";
#else
  s = L"Regular";
#endif
  return s;
}

const wchar_t* ON_Font::DefaultPostScriptName()
{
  const wchar_t* s;
#if defined(ON_RUNTIME_WIN)
  s = L"ArialMT";
#elif defined(ON_RUNTIME_APPLE)
  s = L"HelveticaNeue";
#else
  s = L"ArialMT";
#endif
  return s;
}

const wchar_t* ON_Font::DefaultWindowsLogfontName()
{
  const wchar_t* s;
#if defined(ON_RUNTIME_WIN)
  s = L"Arial";
#elif defined(ON_RUNTIME_APPLE)
  s = L"Helvetica Neue";
#else
  s = L"Arial";
#endif
  return s;
}

#include "opennurbs_internal_glyph.h"

// ON_GlyphMap::GlyphPool needs to be allocated before  ON_ManagedFonts::List. 
// This is so the pool is still around when the ON_ManagedFonts::List
// is being destroyed.
ON_Internal_FontGlyphPool ON_Internal_FontGlyphPool::theGlyphItemPool;

// ON_ManagedFonts::List needs to be allocated before ON_Font::Default
// This list of installed fonts is used to initialize ON_Font::Default.
ON_ManagedFonts ON_ManagedFonts::List((ON__UINT_PTR)0);

// The ON_PTR_SEMAPHORE1 parameter to the
// ON_Font::ON_Font(const ON_Font&) copy ctor triggers special
// initialization for the static font ON_Font::Unset.
// See ON_Font::ON_Font(const ON_Font&) and ON_Font::Internal_CopyFrom()
// for implementation details.
const ON_Font ON_Font::Unset(*((const ON_Font*)ON_PTR_SEMAPHORE1));

// The ON_PTR_SEMAPHORE2 parameter to the
// ON_Font::ON_Font(const ON_Font&) copy ctor triggers special
// initialization for the static font ON_Font::Default.
// See ON_Font::ON_Font(const ON_Font&) and ON_Font::Internal_CopyFrom()
// for implementation details.
const ON_Font ON_Font::Default(*((const ON_Font*)ON_PTR_SEMAPHORE2));

const ON_Geometry ON_Geometry::Unset;

const ON_3dmObjectAttributes ON_3dmObjectAttributes::Unset;

const ON_3dmObjectAttributes ON_3dmObjectAttributes::DefaultAttributes;


static const ON_ModelComponentTypeIterator Internal_ON_ModelComponentIterator_Init(
  int list_selector
  )
{
  //const ON_ModelComponent::Type all_types[] =
  //{
  //  ON_ModelComponent::Type::Unset,
  //  ON_ModelComponent::Type::Image,
  //  ON_ModelComponent::Type::TextureMapping,
  //  ON_ModelComponent::Type::RenderMaterial,
  //  ON_ModelComponent::Type::LinePattern,
  //  ON_ModelComponent::Type::Layer,
  //  ON_ModelComponent::Type::Group,
  //  ON_ModelComponent::Type::TextStyle,
  //  ON_ModelComponent::Type::DimStyle,
  //  ON_ModelComponent::Type::RenderLight,
  //  ON_ModelComponent::Type::HatchPattern,
  //  ON_ModelComponent::Type::InstanceDefinition,
  //  ON_ModelComponent::Type::ModelGeometry,
  //  ON_ModelComponent::Type::HistoryRecord,
  //  ON_ModelComponent::Type::Mixed,
  //};

  const ON_ModelComponent::Type explicit_types[] =
  {
    //ALWAYS EXCLUDE// ON_ModelComponent::Type::Unset,
    ON_ModelComponent::Type::Image,
    ON_ModelComponent::Type::TextureMapping,
    ON_ModelComponent::Type::RenderMaterial,
    ON_ModelComponent::Type::LinePattern,
    ON_ModelComponent::Type::Layer,
    ON_ModelComponent::Type::Group,
    ON_ModelComponent::Type::TextStyle,
    ON_ModelComponent::Type::DimStyle,
    ON_ModelComponent::Type::RenderLight,
    ON_ModelComponent::Type::HatchPattern,
    ON_ModelComponent::Type::InstanceDefinition,
    ON_ModelComponent::Type::ModelGeometry,
    ON_ModelComponent::Type::HistoryRecord,
    //ALWAYS EXCLUDE// ON_ModelComponent::Type::Mixed,
  };

  const ON_ModelComponent::Type table_types[] =
  {
    //ALWAYS EXCLUDE// ON_ModelComponent::Type::Unset,
    //ON_ModelComponent::Type::Image,
    ON_ModelComponent::Type::TextureMapping,
    ON_ModelComponent::Type::RenderMaterial,
    ON_ModelComponent::Type::LinePattern,
    ON_ModelComponent::Type::Layer,
    ON_ModelComponent::Type::Group,
    ON_ModelComponent::Type::TextStyle,
    ON_ModelComponent::Type::DimStyle,
    //ON_ModelComponent::Type::RenderLight,
    ON_ModelComponent::Type::HatchPattern,
    ON_ModelComponent::Type::InstanceDefinition,
    //ON_ModelComponent::Type::ModelGeometry,
    //ON_ModelComponent::Type::HistoryRecord,
    //ALWAYS EXCLUDE// ON_ModelComponent::Type::Mixed,
  };

  switch (list_selector)
  {
    //case 0:
    //  return ON_ModelComponentTypeIterator(sizeof(all_types) / sizeof(all_types[0]), all_types);
  case 1:
    return ON_ModelComponentTypeIterator(sizeof(explicit_types) / sizeof(explicit_types[0]), explicit_types);
  case 2:
    return ON_ModelComponentTypeIterator(sizeof(table_types) / sizeof(table_types[0]), table_types);
  }

  return ON_ModelComponentTypeIterator(0, nullptr);
}

const ON_ModelComponentTypeIterator ON_ModelComponentTypeIterator::ExplicitComponentTypes(Internal_ON_ModelComponentIterator_Init(1));
const ON_ModelComponentTypeIterator ON_ModelComponentTypeIterator::TableComponentTypes(Internal_ON_ModelComponentIterator_Init(2));

const ON_ModelComponent ON_ModelComponent::Unset(ON_ModelComponent::Type::Unset, (ON__UINT64) 0);

const ON_ModelComponentReference ON_ModelComponentReference::Empty;
const ON_ModelComponentWeakReference ON_ModelComponentWeakReference::Empty;

const ON_ModelComponentContentMark ON_ModelComponentContentMark::Unset;


// explicit constructor added to work around Apple CLANG bug.
const ON_ComponentManifest ON_ComponentManifest::Empty;

const ON_ManifestMapItem ON_ManifestMapItem::Unset;

// explicit constructor added to work around Apple CLANG bug.
const ON_ManifestMap ON_ManifestMap::Empty;

const ON_ComponentManifestItem ON_ComponentManifestItem::UnsetItem;

const ON_Bitmap ON_Bitmap::Unset;

const ON_EmbeddedBitmap ON_EmbeddedBitmap::Unset;

const ON_WindowsBitmap ON_WindowsBitmap::Unset;

const ON_WindowsBitmapEx ON_WindowsBitmapEx::Unset;

const ON_Light ON_Light::Unset;

const ON_InstanceDefinition ON_InstanceDefinition::Unset;

const ON_ModelGeometryComponent ON_ModelGeometryComponent::Unset = ON_ModelGeometryComponent(ON_ModelComponent::Type::Unset);

const ON_Texture ON_Texture::Default;

const double ON_Material::MaxShine = 255.0;

const ON_Material ON_Material::Unset;

static ON_Material Internal_SystemMaterialInit(int index)
{
  ON_Material m;
  switch (index)
  {
  case -1: // Default
    {
      // {CF2BE1DE-B81C-4D69-9418-DDE91D266086}
      const ON_UUID id =
      { 0xcf2be1de, 0xb81c, 0x4d69, { 0x94, 0x18, 0xdd, 0xe9, 0x1d, 0x26, 0x60, 0x86 } };
      Internal_SystemModelComponentInit(id, index, nullptr, m);
      m.m_diffuse = ON_Color::Gray250;
    }
    break;

  case -2: // Locked Object Color
    {
      // {70BD1640-E92D-4FFF-818A-9A150BAE3139}
      const ON_UUID id =
      { 0x70bd1640, 0xe92d, 0x4fff, { 0x81, 0x8a, 0x9a, 0x15, 0xb, 0xae, 0x31, 0x39 } };
      Internal_SystemModelComponentInit(id, index, nullptr, m);
      m.m_diffuse = ON_Color::Gray105;
    }
    break;

  default:
    ON_ERROR("Invalid index.");
    break;
  }
  return m;
}
const ON_Material ON_Material::Default(Internal_SystemMaterialInit(-1));
const ON_Material ON_Material::DefaultLockedObject(Internal_SystemMaterialInit(-2));

const ON_TextureMapping ON_TextureMapping::Unset;

// {B988A6C2-61A6-45a7-AAEE-9AED7EF4E316}
const ON_UUID ON_TextureMapping::SurfaceParameterTextureMappingId = { 0xb988a6c2, 0x61a6, 0x45a7,{ 0xaa, 0xee, 0x9a, 0xed, 0x7e, 0xf4, 0xe3, 0x16 } };

static ON_TextureMapping Internal_SurfaceParameterTextureMappingInitializer()
{
  ON_TextureMapping tm;
  tm.SetId(ON_TextureMapping::SurfaceParameterTextureMappingId);
  tm.SetIndex(-1);
  // name = empty

  tm.m_type = ON_TextureMapping::TYPE::srfp_mapping;

  return tm;
}
const ON_TextureMapping ON_TextureMapping::SurfaceParameterTextureMapping(Internal_SurfaceParameterTextureMappingInitializer());

const ON_MappingTag ON_MappingTag::Unset;
const ON_MappingTag ON_MappingTag::SurfaceParameterMapping(ON_TextureMapping::SurfaceParameterTextureMapping,nullptr);

// {639E9144-1C1A-4bba-8248-D330F50D7B69}
// RHINO_CURVATURE_COLOR_ANALYSIS_MODE_ID and ON_SurfaceCurvatureColorMapping::Id
// are identical ids and must never be changed.
const ON_UUID ON_SurfaceCurvatureColorMapping::Id =
{ 0x639e9144, 0x1c1a, 0x4bba, { 0x82, 0x48, 0xd3, 0x30, 0xf5, 0xd, 0x7b, 0x69 } };

// Hue range used by the Rhino surface curvature color analysis.
// Currently red to blue.
const ON_Interval ON_SurfaceCurvatureColorMapping::DefaultHueRangeRadians(0.0, 4.0 * ON_PI / 3.0);

const ON_SurfaceCurvatureColorMapping ON_SurfaceCurvatureColorMapping::Unset;

// {F08463F4-22E2-4cf1-B810-F01925446D71}
// RHINO_DRAFT_ANGLE_ANALYSIS_MODE_ID and ON_SurfaceDraftAngleColorMapping::Id
// are identical ids and must never be changed.
const ON_UUID ON_SurfaceDraftAngleColorMapping::Id =
{ 0xf08463f4, 0x22e2, 0x4cf1, { 0xb8, 0x10, 0xf0, 0x19, 0x25, 0x44, 0x6d, 0x71 } };

// Hue range used by the Rhino draft angle color analysis.
// Currently red to blue.
const ON_Interval ON_SurfaceDraftAngleColorMapping::DefaultHueRangeRadians(0.0, 4.0 * ON_PI / 3.0);

const ON_SurfaceDraftAngleColorMapping ON_SurfaceDraftAngleColorMapping::Unset;

const ON_LinetypeSegment ON_LinetypeSegment::Unset;
const ON_LinetypeSegment ON_LinetypeSegment::OneMillimeterLine(1.0, ON_LinetypeSegment::eSegType::stLine);


const ON_Group ON_Group::Unset;

const ON_Linetype ON_Linetype::Unset;

static ON_Linetype Internal_BuiltInLinePattern( int index )
{
  ON_Linetype line_pattern;
  ON_SimpleArray<double> segments(8);

  switch (index)
  {
  case -1: // Continuous
    {
      const ON_UUID line_pattern_id =
      { 0x3999bed5, 0x78ee, 0x4d73,{ 0xa0, 0x59, 0x3, 0x22, 0x24, 0xc6, 0xfd, 0x55 } };
      Internal_SystemModelComponentInit(
        line_pattern_id,
        index,
        L"Continuous",
        line_pattern
      );
      line_pattern.AppendSegment(ON_LinetypeSegment::OneMillimeterLine);
    }
    break;

  case -2: // By Layer
    {
      const ON_UUID line_pattern_id =
      { 0x913882da, 0xbce9, 0x4a67,{ 0x8d, 0x86, 0xd4, 0x49, 0xfd, 0x58, 0x50, 0xb8 } };
      Internal_SystemModelComponentInit(
        line_pattern_id,
        index,
        L"By Layer",
        line_pattern
        );
      line_pattern.AppendSegment(ON_LinetypeSegment::OneMillimeterLine);
    }
    break;

  case -3: // By Parent
    {
      const ON_UUID line_pattern_id =
      { 0xef59d771, 0x5099, 0x4f60,{ 0x99, 0x14, 0xc1, 0x83, 0x6a, 0xeb, 0xe4, 0x84 } };
      Internal_SystemModelComponentInit(
        line_pattern_id,
        index,
        L"By Parent",
        line_pattern
        );
      line_pattern.AppendSegment(ON_LinetypeSegment::OneMillimeterLine);
    }
    break;

  case -4: // Hidden
    {
      // {7A55AC0F-803C-431B-A7FE-A43319436C8A}
      const ON_UUID line_pattern_id = 
      { 0x7a55ac0f, 0x803c, 0x431b, { 0xa7, 0xfe, 0xa4, 0x33, 0x19, 0x43, 0x6c, 0x8a } };
      Internal_SystemModelComponentInit(
        line_pattern_id,
        index,
        L"Hidden",
        line_pattern
        );
      segments.Append(2.0);
      segments.Append(-2.0);
    }
    break;

  case -5: // Dashed
    {
      // {864526FB-1EEC-40B9-85E1-4619C1F670C5}
      const ON_UUID line_pattern_id =
      { 0x864526fb, 0x1eec, 0x40b9, { 0x85, 0xe1, 0x46, 0x19, 0xc1, 0xf6, 0x70, 0xc5 } };
      Internal_SystemModelComponentInit(
        line_pattern_id,
        index,
        L"Dashed",
        line_pattern
        );
      segments.Append(5.0);
      segments.Append(-5.0);
    }
    break;

  case -6: // DashDot
    {
      // {249AD50D-96C7-44A7-AB20-136EAE74C34D}
      const ON_UUID line_pattern_id =
      { 0x249ad50d, 0x96c7, 0x44a7, { 0xab, 0x20, 0x13, 0x6e, 0xae, 0x74, 0xc3, 0x4d } };
      Internal_SystemModelComponentInit(
        line_pattern_id,
        index,
        L"DashDot",
        line_pattern
        );
      segments.Append(4.0);
      segments.Append(-1.0);
      segments.Append(0.0);
      segments.Append(-1.0);
    }
    break;

  case -7: // Center
    {
      // {B59B1B65-F88F-4854-BED4-E52C51970D0C}
      const ON_UUID line_pattern_id =
      { 0xb59b1b65, 0xf88f, 0x4854, { 0xbe, 0xd4, 0xe5, 0x2c, 0x51, 0x97, 0xd, 0xc } };
      Internal_SystemModelComponentInit(
        line_pattern_id,
        index,
        L"Center",
        line_pattern
        );
      segments.Append(2.5);
      segments.Append(-0.5);
      segments.Append(0.5);
      segments.Append(-0.5);
    }
    break;

  case -8: // Border
    {
      // {93721775-52EA-4193-83A5-3A541A335630}
      const ON_UUID line_pattern_id =
      { 0x93721775, 0x52ea, 0x4193, { 0x83, 0xa5, 0x3a, 0x54, 0x1a, 0x33, 0x56, 0x30 } };
      Internal_SystemModelComponentInit(
        line_pattern_id,
        index,
        L"Border",
        line_pattern
        );
      segments.Append(4.0);
      segments.Append(-1.0);
      segments.Append(4.0);
      segments.Append(-1.0);
      segments.Append(1.0);
      segments.Append(-1.0);
    }
    break;

  case -9: // Dots
    {
      // {E6A283A4-EBBE-4C25-A20C-B1135A791908}
      const ON_UUID line_pattern_id =
      { 0xe6a283a4, 0xebbe, 0x4c25, { 0xa2, 0xc, 0xb1, 0x13, 0x5a, 0x79, 0x19, 0x8 } };
      Internal_SystemModelComponentInit(
        line_pattern_id,
        index,
        L"Dots",
        line_pattern
        );
      segments.Append(0.0);
      segments.Append(-1.0);
    }
    break;

  default:
    ON_ERROR("Invalid index parameter");
    break;
  }

  if (segments.Count() > 0)
  {
    ON_LinetypeSegment segment;
    for( int i = 0; i < segments.Count(); i++)
    {
      segment.m_length = fabs(segments[i]);
      segment.m_seg_type = (segments[i] >=  0.0)
                         ? ON_LinetypeSegment::eSegType::stLine
                         : ON_LinetypeSegment::eSegType::stSpace;    
      line_pattern.AppendSegment(segment);
    }
  }
  line_pattern.LockPattern();

  return line_pattern;
}

const ON_Linetype ON_Linetype::Continuous(Internal_BuiltInLinePattern(-1));
const ON_Linetype ON_Linetype::ByLayer(Internal_BuiltInLinePattern(-2));
const ON_Linetype ON_Linetype::ByParent(Internal_BuiltInLinePattern(-3));
const ON_Linetype ON_Linetype::Hidden(Internal_BuiltInLinePattern(-4));
const ON_Linetype ON_Linetype::Dashed(Internal_BuiltInLinePattern(-5));
const ON_Linetype ON_Linetype::DashDot(Internal_BuiltInLinePattern(-6));
const ON_Linetype ON_Linetype::Center(Internal_BuiltInLinePattern(-7));
const ON_Linetype ON_Linetype::Border(Internal_BuiltInLinePattern(-8));
const ON_Linetype ON_Linetype::Dots(Internal_BuiltInLinePattern(-9));

static void Internal_TextStyleInit(
  const wchar_t* name,
  ON_UUID id,
  int index,
  const ON_Font* font,
  ON_TextStyle& text_style
  )
{
  ON_wString font_description;
  bool bLockName = false;
  if (nullptr != font)
  {
    font_description = font->Description();
    text_style.SetFont(font);

    if ( (nullptr == name || 0 == name[0]) && font_description.IsNotEmpty() )
    {
      name = font_description;
      bLockName = true;
    }
  }

  Internal_SystemModelComponentInit(id, index, name, text_style);

  if (bLockName)
    text_style.LockName();
}

const ON_Layer ON_Layer::Unset;

static ON_Layer Internal_ON_Layer_Default()
{
  // {061DF99E-2EF8-4A3F-8F2D-4B123A166089}
  const ON_UUID id = { 0x61df99e, 0x2ef8, 0x4a3f,{ 0x8f, 0x2d, 0x4b, 0x12, 0x3a, 0x16, 0x60, 0x89 } };
  ON_Layer layer;
  layer.SetParentId(ON_nil_uuid);
  Internal_SystemModelComponentInit(id, -1, L"Default", layer);
  return layer;
}
const ON_Layer ON_Layer::Default = Internal_ON_Layer_Default();

static ON_TextStyle Internal_UnsetTextStyle()
{
  ON_TextStyle text_style;
  Internal_TextStyleInit(nullptr, ON_nil_uuid, 0, nullptr, text_style);
  return text_style;
}

static ON_TextStyle Internal_DefaultTextStyle()
{
  // {8F3A5848-7741-4AA9-B6A0-FA4F76C9D918}
  const ON_UUID default_text_style_id =
  { 0x8f3a5848, 0x7741, 0x4aa9,{ 0xb6, 0xa0, 0xfa, 0x4f, 0x76, 0xc9, 0xd9, 0x18 } };

  ON_TextStyle text_style;
  Internal_TextStyleInit(L"Default", default_text_style_id, -1, &ON_Font::Default, text_style);
  return text_style;
}

static ON_TextStyle Internal_ByLayerTextStyle()
{
  // {DA800C9A-EB00-4251-8237-615017F3BB67}
  const ON_UUID ByLayer_text_style_id =
  { 0xda800c9a, 0xeb00, 0x4251,{ 0x82, 0x37, 0x61, 0x50, 0x17, 0xf3, 0xbb, 0x67 } };

  ON_TextStyle text_style;
  Internal_TextStyleInit(L"By Layer", ByLayer_text_style_id, -2, nullptr, text_style);
  return text_style;
}

static ON_TextStyle Internal_ByParentTextStyle()
{
  // {4D82AFFA-0433-4CE0-92C8-BD328E23C49F}
  const ON_UUID ByParent_text_style_id =
  { 0x4d82affa, 0x433, 0x4ce0,{ 0x92, 0xc8, 0xbd, 0x32, 0x8e, 0x23, 0xc4, 0x9f } };

  ON_TextStyle text_style;
  Internal_TextStyleInit(L"By Parent", ByParent_text_style_id, -3, nullptr, text_style);
  return text_style;
}

const ON_TextStyle ON_TextStyle::Unset(Internal_UnsetTextStyle());
const ON_TextStyle ON_TextStyle::Default(Internal_DefaultTextStyle());
const ON_TextStyle ON_TextStyle::ByLayer(Internal_ByLayerTextStyle());
const ON_TextStyle ON_TextStyle::ByParent(Internal_ByParentTextStyle());

const ON_TextMask ON_TextMask::None;

//static bool ValidateCpyStuff(const ON_DimStyle& src)
//{
//  ON_DimStyle cpyctor(src);
//  ON_DimStyle opeq;
//  opeq = src;
//  const ON_ScaleValue v1 = src.ScaleValue();
//  const ON_ScaleValue v2 = cpyctor.ScaleValue();
//  const ON_ScaleValue v3 = opeq.ScaleValue();
//
//  bool rc = v1.RightToLeftScale() == v2.RightToLeftScale() && v1.RightToLeftScale() == v2.RightToLeftScale();
//
//  return rc;
//}

const ON_FontFaceQuartet ON_FontFaceQuartet::Empty;

static void Internal_DimStyleInit(
  const wchar_t* name,
  int index,
  ON_UUID id,
  ON_DimStyle& dimension_style
  )
{
  Internal_SystemModelComponentInit(id, index, name, dimension_style);

  dimension_style.SetAlternatePrefix(L" [");
  dimension_style.SetAlternateSuffix(L"]");
  // identical values for most or all built-in dimension styles
  dimension_style.SetFont(ON_Font::Default);
  dimension_style.SetDimTextLocation(ON_DimStyle::TextLocation::AboveDimLine);
}

static void Internal_SystemDimStyleFinalize(
  ON_DimStyle& dimension_style
)
{
  dimension_style.ClearAllFieldOverrides();
  dimension_style.ContentHash();
}

// Static DimStyle definitions

static void Internal_DimStyleDefaultInit(ON_DimStyle& ds)
{
  ds.SetExtExtension                     (0.5);
  ds.SetExtOffset                        (0.5);
  ds.SetArrowSize                        (1.0);
  ds.SetLeaderArrowSize                  (1.0);
  ds.SetCenterMark                       (0.5);
  ds.SetCenterMarkStyle                  (ON_DimStyle::centermark_style::Mark);
  ds.SetTextGap                          (0.25);
  ds.SetTextHeight                       (1.0);
  ds.SetDimTextLocation                  (ON_DimStyle::TextLocation::AboveDimLine);
  ds.SetDimRadialTextLocation            (ON_DimStyle::TextLocation::InDimLine);
  ds.SetAngleFormat                      (ON_DimStyle::angle_format::DecimalDegrees);
  ds.SetAngleResolution                  (2);
  ds.SetDimensionLengthDisplay           (ON_DimStyle::LengthDisplay::ModelUnits);
  ds.SetAlternateDimensionLengthDisplay  (ON_DimStyle::LengthDisplay::ModelUnits);
  ds.SetLengthResolution                 (2);
  ds.SetAlternateLengthResolution        (2);
  ds.SetLengthFactor                     (1.0);
  ds.SetAlternateLengthFactor            (1.0);
  ds.SetAlternate                        (false);
  ds.SetForceDimLine                     (true);
  ds.SetDecimalSeparator                 (L'.');
  ds.SetPrefix                           (L"");
  ds.SetSuffix                           (L"");
  ds.SetAlternatePrefix                  (L" [");
  ds.SetAlternateSuffix                  (L"]");
  ds.SetDimExtension                     (0.0);
  ds.SetSuppressExtension1               (false);
  ds.SetSuppressExtension2               (false);
  ds.SetToleranceFormat                  (ON_DimStyle::tolerance_format::None);
  ds.SetToleranceResolution              (4);
  ds.SetToleranceUpperValue              (0.0);
  ds.SetToleranceLowerValue              (0.0);
  ds.SetToleranceHeightScale             (1.0);
  ds.SetBaselineSpacing                  (3.0);
     ON_TextMask tm;
  ds.SetTextMask                         (tm);
  ds.SetDimScaleSource                   (0);
  ds.SetExtensionLineColorSource         (ON::object_color_source::color_from_layer);
  ds.SetDimensionLineColorSource         (ON::object_color_source::color_from_layer);
  ds.SetArrowColorSource                 (ON::object_color_source::color_from_layer);
  ds.SetTextColorSource                  (ON::object_color_source::color_from_layer);
  ds.SetExtensionLineColor               (ON_Color(0));
  ds.SetDimensionLineColor               (ON_Color(0));
  ds.SetArrowColor                       (ON_Color(0));
  ds.SetTextColor                        (ON_Color(0));
  ds.SetExtensionLinePlotColorSource     (ON::plot_color_source::plot_color_from_layer);
  ds.SetDimensionLinePlotColorSource     (ON::plot_color_source::plot_color_from_layer);
  ds.SetArrowPlotColorSource             (ON::plot_color_source::plot_color_from_layer);
  ds.SetTextPlotColorSource              (ON::object_color_source::color_from_layer);
  ds.SetExtensionLinePlotColor           (ON_Color(0));
  ds.SetDimensionLinePlotColor           (ON_Color(0));
  ds.SetArrowPlotColor                   (ON_Color(0));
  ds.SetTextPlotColor                    (ON_Color(0));
  ds.SetExtensionLinePlotWeightSource    (ON::plot_weight_source::plot_weight_from_layer);
  ds.SetDimensionLinePlotWeightSource    (ON::plot_weight_source::plot_weight_from_layer);
  ds.SetExtensionLinePlotWeight          (0.0);
  ds.SetDimensionLinePlotWeight          (0.0);
  ds.SetFixedExtensionLen                (1.0);
  ds.SetFixedExtensionLenOn              (false);
  ds.SetTextRotation                     (0.0);
  ds.SetAlternateLengthResolution        (4);
  ds.SetToleranceHeightScale             (0.6);
  ds.SetSuppressArrow1                   (false);
  ds.SetSuppressArrow2                   (false);
  ds.SetTextMoveLeader                   (0);
  ds.SetArcLengthSymbol                  (L'\0');
  ds.SetStackHeightScale                 (0.7);
  ds.SetStackFractionFormat              (ON_DimStyle::stack_format::StackHorizontal);
  ds.SetAlternateRoundOff                (0.0);
  ds.SetRoundOff                         (0.0);
  ds.SetAngleRoundOff                    (0.0);
  ds.SetZeroSuppress                     (ON_DimStyle::suppress_zero::None);
  ds.SetAlternateZeroSuppress            (ON_DimStyle::suppress_zero::None);
  ds.SetAngleZeroSuppress                (ON_DimStyle::suppress_zero::None);
  ds.SetAlternateBelow                   (false);
  ds.SetArrowType1                       (ON_Arrowhead::arrow_type::SolidTriangle);
  ds.SetArrowType2                       (ON_Arrowhead::arrow_type::SolidTriangle);
  ds.SetLeaderArrowType                  (ON_Arrowhead::arrow_type::SolidTriangle);
  ds.SetTextVerticalAlignment            (ON::TextVerticalAlignment::Top);
  ds.SetTextHorizontalAlignment          (ON::TextHorizontalAlignment::Left);
  ds.SetLeaderTextVerticalAlignment      (ON::TextVerticalAlignment::MiddleOfTop);
  ds.SetLeaderTextHorizontalAlignment    (ON::TextHorizontalAlignment::Left);
  ds.SetLeaderContentAngleStyle          (ON_DimStyle::ContentAngleStyle::Horizontal);
  ds.SetLeaderCurveType                  (ON_DimStyle::leader_curve_type::Polyline);
  ds.SetLeaderContentAngleRadians        (0.0);
  ds.SetLeaderHasLanding                 (false);
  ds.SetLeaderLandingLength              (1.0);
  ds.SetDrawForward                      (true);
  ds.SetSignedOrdinate                   (true);
  ds.SetDimScale                         (1.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::None);
  ds.SetTextOrientation                  (ON::TextOrientation::InPlane);
  ds.SetLeaderTextOrientation            (ON::TextOrientation::InPlane);
  ds.SetDimTextOrientation               (ON::TextOrientation::InPlane);
  ds.SetDimRadialTextOrientation         (ON::TextOrientation::InPlane);
  ds.SetDimTextAngleStyle                (ON_DimStyle::ContentAngleStyle::Aligned);
  ds.SetDimRadialTextAngleStyle          (ON_DimStyle::ContentAngleStyle::Horizontal);
  ds.SetTextUnderlined                   (false);
}

static void Internal_DimStyleMillimeterArchitecturalInit(ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetExtExtension                     (1.0);
  ds.SetArrowSize                        (3.0);
  ds.SetLeaderArrowSize                  (3.0);
  ds.SetCenterMark                       (3.0);
  ds.SetTextGap                          (1.0);
  ds.SetTextHeight                       (3.0);
  ds.SetAngleResolution                  (0);
  ds.SetDimensionLengthDisplay           (ON_DimStyle::LengthDisplay::Millmeters);
  ds.SetAlternateDimensionLengthDisplay  (ON_DimStyle::LengthDisplay::InchesDecimal);
  ds.SetLengthResolution                 (0);
  ds.SetBaselineSpacing                  (9.0);
  ds.SetArrowType1                       (ON_Arrowhead::arrow_type::Tick);
  ds.SetArrowType2                       (ON_Arrowhead::arrow_type::Tick);
  ds.SetLeaderArrowType                  (ON_Arrowhead::arrow_type::OpenArrow);
  ds.SetDimScale                         (100.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Millimeters);
}

static void Internal_DimStyleMillimeterLargeInit(ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetExtExtension                     (1.0);
  ds.SetArrowSize                        (3.5);
  ds.SetLeaderArrowSize                  (3.5);
  ds.SetCenterMark                       (3.5);
  ds.SetTextGap                          (1.0);
  ds.SetTextHeight                       (3.5);
  ds.SetAngleResolution                  (0);
  ds.SetDimensionLengthDisplay           (ON_DimStyle::LengthDisplay::Millmeters);
  ds.SetAlternateDimensionLengthDisplay  (ON_DimStyle::LengthDisplay::InchesDecimal);
  ds.SetLengthResolution                 (1);
  ds.SetToleranceHeightScale             (1.0);
  ds.SetBaselineSpacing                  (10.5);
  ds.SetLeaderLandingLength              (3.5);
  ds.SetDimScale                         (100.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Millimeters);
}

static void Internal_DimStyleMillimeterSmallInit (ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetExtExtension                     (1.0);
  ds.SetArrowSize                        (3.0);
  ds.SetLeaderArrowSize                  (3.0);
  ds.SetCenterMark                       (2.5);
  ds.SetTextGap                          (0.8);
  ds.SetTextHeight                       (2.5);
  ds.SetAngleResolution                  (1);
  ds.SetDimensionLengthDisplay           (ON_DimStyle::LengthDisplay::Millmeters);
  ds.SetAlternateDimensionLengthDisplay  (ON_DimStyle::LengthDisplay::InchesDecimal);
  ds.SetBaselineSpacing                  (7.5);
  ds.SetLeaderLandingLength              (2.5);
  ds.SetDimScale                         (10.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Millimeters);
}

static void Internal_DimStyleInchDecimalInit(ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetExtExtension                     (0.125);
  ds.SetExtOffset                        (0.0625);
  ds.SetArrowSize                        (0.125);
  ds.SetLeaderArrowSize                  (0.125);
  ds.SetCenterMark                       (0.25);
  ds.SetTextGap                          (0.0625);
  ds.SetTextHeight                       (0.125);
  ds.SetAngleResolution                  (0);
  ds.SetDimensionLengthDisplay           (ON_DimStyle::LengthDisplay::InchesDecimal);
  ds.SetToleranceHeightScale             (1.0);
  ds.SetBaselineSpacing                  (0.38);
  ds.SetLeaderLandingLength              (0.125);
  ds.SetDimScale                         (10.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Inches);
}

static void Internal_DimStyleInchFractionalInit(ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetExtExtension                     (0.125);
  ds.SetExtOffset                        (0.0625);
  ds.SetArrowSize                        (0.1);
  ds.SetLeaderArrowSize                  (0.1);
  ds.SetCenterMark                       (0.25);
  ds.SetTextGap                          (0.0625);
  ds.SetTextHeight                       (0.125);
  ds.SetAngleResolution                  (1);
  ds.SetDimensionLengthDisplay           (ON_DimStyle::LengthDisplay::InchesFractional);
  ds.SetLengthResolution                 (4);
  ds.SetDimExtension                     (0.1);
  ds.SetBaselineSpacing                  (0.38);
  ds.SetArrowType1                       (ON_Arrowhead::arrow_type::Tick);
  ds.SetArrowType2                       (ON_Arrowhead::arrow_type::Tick);
  ds.SetLeaderArrowType                  (ON_Arrowhead::arrow_type::OpenArrow);
  ds.SetLeaderLandingLength              (0.125);
  ds.SetDimScale                         (12.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Inches);
}

static void Internal_DimStyleFootInchArchitecturalInit(ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetExtExtension                     (0.125);
  ds.SetExtOffset                        (0.0625);
  ds.SetArrowSize                        (0.1);
  ds.SetLeaderArrowSize                  (0.1);
  ds.SetCenterMark                       (0.25);
  ds.SetTextGap                          (0.0625);
  ds.SetTextHeight                       (0.125);
  ds.SetAngleResolution                  (0);
  ds.SetDimensionLengthDisplay           (ON_DimStyle::LengthDisplay::FeetAndInches);
  ds.SetAlternateLengthResolution        (1);
  ds.SetBaselineSpacing                  (0.38);
  ds.SetZeroSuppress                     (ON_DimStyle::suppress_zero::SuppressZeroFeet);
  ds.SetArrowType1                       (ON_Arrowhead::arrow_type::Tick);
  ds.SetArrowType2                       (ON_Arrowhead::arrow_type::Tick);
  ds.SetLeaderArrowType                  (ON_Arrowhead::arrow_type::OpenArrow);
  ds.SetLeaderLandingLength              (0.125);
  ds.SetDimScale                         (96.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Inches);
}

static void Internal_DimStyleFeetDecimalInit(ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetExtExtension                     (0.125);
  ds.SetExtOffset                        (0.0625);
  ds.SetArrowSize                        (0.125);
  ds.SetLeaderArrowSize                  (0.125);
  ds.SetCenterMark                       (0.25);
  ds.SetTextGap                          (0.0625);
  ds.SetTextHeight                       (0.125);
  ds.SetAngleResolution                  (0);
  ds.SetDimensionLengthDisplay           (ON_DimStyle::LengthDisplay::FeetDecimal);
  ds.SetBaselineSpacing                  (0.38);
  ds.SetLeaderLandingLength              (0.125);
  ds.SetDimScale                         (12.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Inches);
}

static void Internal_DimStyleModelUnitsDecimalInit(ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetExtExtension                     (0.125);
  ds.SetExtOffset                        (0.0625);
  ds.SetArrowSize                        (0.125);
  ds.SetLeaderArrowSize                  (0.125);
  ds.SetCenterMark                       (0.25);
  ds.SetTextGap                          (0.0625);
  ds.SetTextHeight                       (0.125);
  ds.SetAngleResolution                  (0);
  ds.SetBaselineSpacing                  (0.38);
  ds.SetLeaderLandingLength              (0.125);
  ds.SetDimScale                         (10.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Inches);
}

static void Internal_DimStyleFeetEngraveInit(ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetDimensionLengthDisplay           (ON_DimStyle::LengthDisplay::FeetDecimal);
  ds.SetTextVerticalAlignment            (ON::TextVerticalAlignment::Bottom);
  ds.SetDimScale                         (12.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Inches);
}

static void Internal_DimStyleMillimeterEngraveInit(ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetExtExtension                     (1.5);
  ds.SetExtOffset                        (1.5);
  ds.SetArrowSize                        (3.0);
  ds.SetLeaderArrowSize                  (3.0);
  ds.SetCenterMark                       (1.5);
  ds.SetTextGap                          (0.75);
  ds.SetTextHeight                       (3.0);
  ds.SetDimensionLengthDisplay           (ON_DimStyle::LengthDisplay::Millmeters);
  ds.SetBaselineSpacing                  (9.0);
  ds.SetFixedExtensionLen                (3.0);
  ds.SetLeaderLandingLength              (3.0);
  ds.SetDimScale                         (10.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Millimeters);
}

static void Internal_DimStyleModelUnitsEngraveInit(ON_DimStyle& ds)
{
  Internal_DimStyleDefaultInit(ds);
  ds.SetAlternateDimensionLengthDisplay  (ON_DimStyle::LengthDisplay::Millmeters);
  ds.SetToleranceHeightScale             (1.0);
  ds.SetTextVerticalAlignment            (ON::TextVerticalAlignment::Bottom);
  ds.SetDimScale                         (10.0);
  ds.SetUnitSystem                       (ON::LengthUnitSystem::Inches);
}


static ON_DimStyle Internal_DimStyleDefault()
{
  const ON_UUID id =
  { 0x25b90869, 0x22, 0x4e04,{ 0xb4, 0x98, 0x98, 0xb4, 0x17, 0x5f, 0x65, 0xfd } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Default", -1, id, dimstyle);
  Internal_DimStyleDefaultInit(dimstyle);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleInchDecimal()
{
  const ON_UUID id =
  { 0x2105610c, 0xcfc7, 0x4473,{ 0xa5, 0x80, 0xc3, 0xd9, 0xc, 0xe8, 0xc7, 0xa3 } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Inch Decimal", -2, id, dimstyle);
  Internal_DimStyleInchDecimalInit(dimstyle);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleInchFractional()
{
  const ON_UUID id =
  { 0x6bcb1506, 0x699f, 0x445d,{ 0xa1, 0x22, 0x4f, 0xc7, 0x78, 0x2b, 0xc4, 0x86 } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Inch Fractional", -3, id, dimstyle);
  Internal_DimStyleInchFractionalInit(dimstyle);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleFootInchArchitectural()
{
  const ON_UUID id =
  { 0x50d6ef1b, 0xd1d0, 0x408a,{ 0x86, 0xc0, 0xee, 0x8b, 0x36, 0x8, 0x88, 0x3e } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Foot-Inch Architectural", -4, id, dimstyle);
  Internal_DimStyleFootInchArchitecturalInit(dimstyle);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleMillimeterSmall()
{
  const ON_UUID id =
  { 0xdbe22573, 0x8cad, 0x4ced,{ 0x89, 0x47, 0x3, 0xa0, 0x48, 0xed, 0xde, 0x56 } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Millimeter Small", -5, id, dimstyle);
  Internal_DimStyleMillimeterSmallInit(dimstyle);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleMillimeterLarge()
{
  const ON_UUID id =
  { 0xf7b30534, 0x773e, 0x45bc,{ 0x9d, 0x87, 0x9d, 0x14, 0x80, 0x9c, 0x96, 0x44 } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Millimeter Large", -6, id, dimstyle);
  Internal_DimStyleMillimeterLargeInit(dimstyle);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleMillimeterArchitectural()
{
  const ON_UUID id =
  { 0xe5a4c08f, 0x23b3, 0x4033,{ 0x90, 0xb2, 0xfb, 0x31, 0xec, 0x45, 0x92, 0x9b } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Millimeter Architectural", -7, id, dimstyle);
  Internal_DimStyleMillimeterArchitecturalInit(dimstyle);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleFeetDecimal()
{
  // {6F4B1840-8A12-4DE9-BF84-6A98B06C508D}
  const ON_UUID id =
  { 0x6f4b1840, 0x8a12, 0x4de9, { 0xbf, 0x84, 0x6a, 0x98, 0xb0, 0x6c, 0x50, 0x8d } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Feet Decimal", -8, id, dimstyle);
  Internal_DimStyleFeetDecimalInit(dimstyle);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleModelUnitsDecimal()
{
  const ON_UUID id =
  { 0x93a38bdf, 0x4c1c, 0x428c, { 0x8b, 0x97, 0x93, 0x59, 0xf1, 0xbd, 0xed, 0x17 } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Model Units Decimal", -9, id, dimstyle);
  Internal_DimStyleModelUnitsDecimalInit(dimstyle);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleFeetEngrave()
{
  const ON_UUID id =
  { 0xc2d8846b, 0x918d, 0x4779, { 0x96, 0xec, 0x31, 0xb4, 0xe2, 0x75, 0xfb, 0x4e } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Feet Engrave", -10, id, dimstyle);
  Internal_DimStyleFeetEngraveInit(dimstyle);
  const ON_Font* font = ON_Font::DefaultEngravingFont();
  if (nullptr != font)
    dimstyle.SetFont(*font);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleMillimeterEngrave()
{
  const ON_UUID id =
  { 0x741980ff, 0xde0f, 0x4ed7, { 0xaa, 0x6f, 0xee, 0x91, 0xb3, 0xbe, 0x96, 0xc6 } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Millimeter Engrave", -11, id, dimstyle);
  Internal_DimStyleMillimeterEngraveInit(dimstyle);
  const ON_Font* font = ON_Font::DefaultEngravingFont();
  if (nullptr != font)
    dimstyle.SetFont(*font);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

static ON_DimStyle Internal_DimStyleModelUnitsEngrave()
{
  const ON_UUID id =
  { 0x2cc3a895, 0x5389, 0x467e, { 0x9d, 0xbe, 0x3a, 0xca, 0xb4, 0x38, 0x60, 0xfa } };

  ON_DimStyle dimstyle;
  Internal_DimStyleInit(L"Model Units Engrave", -12, id, dimstyle);
  Internal_DimStyleModelUnitsEngraveInit(dimstyle);
  const ON_Font* font = ON_Font::DefaultEngravingFont();
  if (nullptr != font)
    dimstyle.SetFont(*font);
  Internal_SystemDimStyleFinalize(dimstyle);
  return dimstyle;
}

const ON_DimStyle ON_DimStyle::Unset;

const ON_DimStyle ON_DimStyle::Default(Internal_DimStyleDefault());

const ON_DimStyle ON_DimStyle::DefaultInchDecimal(Internal_DimStyleInchDecimal());
const ON_DimStyle ON_DimStyle::DefaultInchFractional(Internal_DimStyleInchFractional());
const ON_DimStyle ON_DimStyle::DefaultFootInchArchitecture(Internal_DimStyleFootInchArchitectural());

const ON_DimStyle ON_DimStyle::DefaultMillimeterSmall(Internal_DimStyleMillimeterSmall());
const ON_DimStyle ON_DimStyle::DefaultMillimeterLarge(Internal_DimStyleMillimeterLarge());
const ON_DimStyle ON_DimStyle::DefaultMillimeterArchitecture(Internal_DimStyleMillimeterArchitectural());

const ON_DimStyle ON_DimStyle::DefaultFeetDecimal(Internal_DimStyleFeetDecimal());
const ON_DimStyle ON_DimStyle::DefaultModelUnitsDecimal(Internal_DimStyleModelUnitsDecimal());

const ON_DimStyle ON_DimStyle::DefaultFeetEngrave(Internal_DimStyleFeetEngrave());
const ON_DimStyle ON_DimStyle::DefaultMillimeterEngrave(Internal_DimStyleMillimeterEngrave());
const ON_DimStyle ON_DimStyle::DefaultModelUnitsEngrave(Internal_DimStyleModelUnitsEngrave());

const ON_StackedText ON_StackedText::Empty;
const ON_TextRun ON_TextRun::Empty;
const ON_TextRunArray ON_TextRunArray::EmptyArray;
const ON_TextContent ON_TextContent::Empty;

const ON_Text ON_Text::Empty;
const ON_Leader ON_Leader::Empty;
const ON_DimLinear ON_DimLinear::Empty;
const ON_DimAngular ON_DimAngular::Empty;
const ON_DimRadial ON_DimRadial::Empty;
const ON_DimOrdinate ON_DimOrdinate::Empty;
const ON_Centermark ON_Centermark::Empty;

const ON_HatchLine ON_HatchLine::Unset(ON_UNSET_VALUE);           // angle = unset
const ON_HatchLine ON_HatchLine::SolidHorizontal(0.0); // angle = 0
const ON_HatchLine ON_HatchLine::SolidVertical(ON_PI / 2);   // angle = pi/2

static ON_HatchPattern Internal_SolidHatchPatternInit()
{
  // {B319435D-86B6-4D89-972D-1F75FEF0D950}
  ON_UUID id = { 0xb319435d, 0x86b6, 0x4d89,{ 0x97, 0x2d, 0x1f, 0x75, 0xfe, 0xf0, 0xd9, 0x50 } };


  ON_HatchPattern hatch_pattern;
  hatch_pattern.SetFillType(ON_HatchPattern::HatchFillType::Solid);
  Internal_SystemModelComponentInit(id, -1, L"Solid", hatch_pattern);

  return hatch_pattern;
}

static ON_HatchPattern Internal_LineHatchPatternInit(
  const int hatch_index
  )
{
  ON_UUID id = ON_nil_uuid;
  ON_HatchLine lines[4];
  unsigned int line_count = 0;
  const wchar_t* name = nullptr;
  switch (hatch_index)
  {
  case -2:
  {
    // {3C25B9D3-0521-4120-8877-111FB5EA0016}
    const ON_UUID idctor = { 0x3c25b9d3, 0x521, 0x4120,{ 0x88, 0x77, 0x11, 0x1f, 0xb5, 0xea, 0x0, 0x16 } };
    id = idctor;
    name = L"Hatch1";
    ON_HatchLine& line0 = lines[line_count++];
    line0.SetAngleRadians(0.0);
    line0.SetBase(ON_2dPoint::Origin);
    line0.SetOffset(ON_2dVector(0.0, 0.125));
  }
  break;

  case -3:
  {
    // {23287413-6AE6-4409-93DC-140796FA7864}
    const ON_UUID idctor = { 0x23287413, 0x6ae6, 0x4409,{ 0x93, 0xdc, 0x14, 0x7, 0x96, 0xfa, 0x78, 0x64 } };
    id = idctor;
    name = L"Hatch2";
    ON_HatchLine& line0 = lines[line_count++];
    line0.SetAngleRadians(0.0);
    line0.SetBase(ON_2dPoint::Origin);
    line0.SetOffset(ON_2dVector(0.0, 0.375));

    ON_HatchLine& line1 = lines[line_count++];
    line1 = line0;
    line1.SetBase(ON_2dPoint(0.0, 0.0625));
  }
  break;

  case -4:
  {
    // {282CBE0A-DB30-4241-BB5B-7290AF0BBD55}
    const ON_UUID idctor = { 0x282cbe0a, 0xdb30, 0x4241,{ 0xbb, 0x5b, 0x72, 0x90, 0xaf, 0xb, 0xbd, 0x55 } };
    id = idctor;
    name = L"Hatch3";
    ON_HatchLine& line0 = lines[line_count++];
    line0.SetAngleRadians(0.0);
    line0.SetBase(ON_2dPoint::Origin);
    line0.SetOffset(ON_2dVector(0.0, 0.5));

    ON_HatchLine& line1 = lines[line_count++];
    line1 = line0;
    line1.SetBase(ON_2dPoint(0.0, 0.0625));

    ON_HatchLine& line2 = lines[line_count++];
    line2 = line0;
    line2.SetBase(ON_2dPoint(0.0, 0.125));
  }
  break;

  case -5:
  {
    // {70710CA6-185D-42FE-AEB5-6437A8C15E7B}
    const ON_UUID idctor = { 0x70710ca6, 0x185d, 0x42fe,{ 0xae, 0xb5, 0x64, 0x37, 0xa8, 0xc1, 0x5e, 0x7b } };
    id = idctor;
    name = L"HatchDash";
    ON_HatchLine& line0 = lines[line_count++];
    line0.SetAngleRadians(0.0);
    line0.SetBase(ON_2dPoint::Origin);
    line0.SetOffset(ON_2dVector(0.0, 0.25));

    ON_HatchLine& line1 = lines[line_count++];
    line1.SetAngleRadians(0.0);
    line1.SetBase(ON_2dPoint(0.0, 0.125));
    line1.SetOffset(ON_2dVector(0.0, 0.25));
    line1.AppendDash(0.125);
    line1.AppendDash(-0.125);
  }
  break;

  case -6:
  {
    // {86D5A4E7-AA8F-4FBA-BAA3-C844EF1704A1}
    const ON_UUID idctor = { 0x86d5a4e7, 0xaa8f, 0x4fba,{ 0xba, 0xa3, 0xc8, 0x44, 0xef, 0x17, 0x4, 0xa1 } };
    id = idctor;
    name = L"Grid";
    ON_HatchLine& line0 = lines[line_count++];
    line0.SetAngleRadians(0.0);
    line0.SetBase(ON_2dPoint::Origin);
    line0.SetOffset(ON_2dVector(0.0, 0.25));

    ON_HatchLine& line1 = lines[line_count++];
    line1 = line0;
    line1.SetAngleRadians(ON_PI / 2.0);
  }
  break;

  case -7:
  {
    // {060226AB-2BA8-4550-BB0A-BC1A3CD8E2A1}
    const ON_UUID idctor = { 0x60226ab, 0x2ba8, 0x4550,{ 0xbb, 0xa, 0xbc, 0x1a, 0x3c, 0xd8, 0xe2, 0xa1 } };
    id = idctor;
    name = L"Grid60";
    ON_HatchLine& line0 = lines[line_count++];
    line0.SetAngleRadians(0.0);
    line0.SetOffset(ON_2dVector(0.0, 0.25));

    ON_HatchLine& line1 = lines[line_count++];
    line1 = line0;
    line1.SetAngleDegrees(60.0);

    ON_HatchLine& line2 = lines[line_count++];
    line2 = line0;
    line2.SetAngleDegrees(120.0);
  }
  break;

  case -8:
  {
    // {5FA0C0A0-B5F6-4799-ADED-AE202E260888}
    const ON_UUID idctor = { 0x5fa0c0a0, 0xb5f6, 0x4799,{ 0xad, 0xed, 0xae, 0x20, 0x2e, 0x26, 0x8, 0x88 } };
    id = idctor;
    name = L"Plus";
    ON_HatchLine& line0 = lines[line_count++];
    line0.SetAngleRadians(0.0);
    line0.SetBase(ON_2dPoint(-0.125, 0.0));
    line0.SetOffset(ON_2dVector(0.0, 1.0));
    line0.AppendDash(0.25);
    line0.AppendDash(-0.75);

    ON_HatchLine& line1 = lines[line_count++];
    line1 = line0;
    line1.SetAngleRadians(ON_PI / 2.0);
    line1.SetBase(ON_2dPoint(0.0, -0.125));
  }
  break;

  case -9:
  {
    // {05B0404B-77AD-4206-8022-FD7D9D0ECECF}
    const ON_UUID idctor = { 0x5b0404b, 0x77ad, 0x4206,{ 0x80, 0x22, 0xfd, 0x7d, 0x9d, 0xe, 0xce, 0xcf } };
    id = idctor;
    name = L"Squares";
    ON_HatchLine& line0 = lines[line_count++];
    line0.SetAngleRadians(0.0);
    line0.SetBase(ON_2dPoint::Origin);
    line0.SetOffset(ON_2dVector(0.0, 0.25));
    line0.AppendDash(0.25);
    line0.AppendDash(-0.25);

    ON_HatchLine& line1 = lines[line_count++];
    line1 = line0;
    line1.SetAngleRadians(ON_PI / 2.0);
  }
  break;
  }

  ON_HatchPattern hatch_pattern;
  hatch_pattern.SetHatchLines(line_count, lines);
  Internal_SystemModelComponentInit(id, hatch_index, name, hatch_pattern);
  return hatch_pattern;
}

const ON_HatchPattern ON_HatchPattern::Unset;
const ON_HatchPattern ON_HatchPattern::Solid(Internal_SolidHatchPatternInit()); // index = -1, id set, unique and persistent
const ON_HatchPattern ON_HatchPattern::Hatch1(Internal_LineHatchPatternInit(-2));    // index = -2, id set, unique and persistent
const ON_HatchPattern ON_HatchPattern::Hatch2(Internal_LineHatchPatternInit(-3));    // index = -3, id set, unique and persistent
const ON_HatchPattern ON_HatchPattern::Hatch3(Internal_LineHatchPatternInit(-4));    // index = -4, id set, unique and persistent
const ON_HatchPattern ON_HatchPattern::HatchDash(Internal_LineHatchPatternInit(-5)); // index = -5, id set, unique and persistent
const ON_HatchPattern ON_HatchPattern::Grid(Internal_LineHatchPatternInit(-6));      // index = -6, id set, unique and persistent
const ON_HatchPattern ON_HatchPattern::Grid60(Internal_LineHatchPatternInit(-7));    // index = -7, id set, unique and persistent
const ON_HatchPattern ON_HatchPattern::Plus(Internal_LineHatchPatternInit(-8));      // index = -8, id set, unique and persistent
const ON_HatchPattern ON_HatchPattern::Squares(Internal_LineHatchPatternInit(-9));   // index = -9, id set, unique and persistent


const ON_Mesh ON_Mesh::Empty;
const ON_MeshRef ON_MeshRef::Empty;

unsigned int ON_SubD::ErrorCount = 0;
unsigned int ON_Brep::ErrorCount = 0;

const bool ON_SubD::AutomaticRhino5BoxModeTSplineToSubDDefault = true;
const bool ON_SubD::AutomaticFBXMeshWithDivisionLevelsToSubDDefault = false;

bool ON_SubD::AutomaticRhino5BoxModeTSplineToSubD = ON_SubD::AutomaticRhino5BoxModeTSplineToSubDDefault;
bool ON_SubD::AutomaticFBXMeshWithDivisionLevelsToSubD = ON_SubD::AutomaticFBXMeshWithDivisionLevelsToSubDDefault;


void ON_SubD::AutomaticMeshToSubDRestoreDefaults(
  ON_SubD::AutomaticMeshToSubDContext context
  )
{
  switch (context)
  {
  case ON_SubD::AutomaticMeshToSubDContext::Unset:
  default:
    ON_SubD::AutomaticRhino5BoxModeTSplineToSubD = ON_SubD::AutomaticRhino5BoxModeTSplineToSubDDefault;
    ON_SubD::AutomaticFBXMeshWithDivisionLevelsToSubD = ON_SubD::AutomaticFBXMeshWithDivisionLevelsToSubDDefault;
    break;
  case ON_SubD::AutomaticMeshToSubDContext::Rhino5BoxModeTSpline:
    ON_SubD::AutomaticRhino5BoxModeTSplineToSubD = ON_SubD::AutomaticRhino5BoxModeTSplineToSubDDefault;
    break;
  case ON_SubD::AutomaticMeshToSubDContext::FBXMeshWithDivisionLevels:
    ON_SubD::AutomaticFBXMeshWithDivisionLevelsToSubD = ON_SubD::AutomaticFBXMeshWithDivisionLevelsToSubDDefault;
    break;
  }
}

bool ON_SubD::AutomaticMeshToSubD(
  ON_SubD::AutomaticMeshToSubDContext context
)
{
  bool bAutomaticallyCreateSubD;
  switch (context)
  {
  case ON_SubD::AutomaticMeshToSubDContext::Unset:
    bAutomaticallyCreateSubD = false;
    break;
  case ON_SubD::AutomaticMeshToSubDContext::Rhino5BoxModeTSpline:
    bAutomaticallyCreateSubD = ON_SubD::AutomaticRhino5BoxModeTSplineToSubD;
    break;
  case ON_SubD::AutomaticMeshToSubDContext::FBXMeshWithDivisionLevels:
    bAutomaticallyCreateSubD = ON_SubD::AutomaticFBXMeshWithDivisionLevelsToSubD;
    break;
  default:
    bAutomaticallyCreateSubD = false;
    break;
  }
  return bAutomaticallyCreateSubD;
}

void ON_SubD::SetAutomaticMeshToSubD(
  ON_SubD::AutomaticMeshToSubDContext context,
  bool bAutomaticallyCreateSubD
)
{
  // remove possibility of hacks to use this as a char value
  bAutomaticallyCreateSubD = bAutomaticallyCreateSubD ? true : false;

  switch (context)
  {
  case ON_SubD::AutomaticMeshToSubDContext::Unset:
    break;
  case ON_SubD::AutomaticMeshToSubDContext::Rhino5BoxModeTSpline:
    ON_SubD::AutomaticRhino5BoxModeTSplineToSubD = bAutomaticallyCreateSubD;
    break;
  case ON_SubD::AutomaticMeshToSubDContext::FBXMeshWithDivisionLevels:
    ON_SubD::AutomaticFBXMeshWithDivisionLevelsToSubD = bAutomaticallyCreateSubD;
    break;
  default:
    break;
  }
}


const ON_SubDVertexEdgeProperties ON_SubDVertexEdgeProperties::Zero;

const ON_SubDVertexPtr ON_SubDVertexPtr::Null = { 0 };
const ON_SubDEdgePtr ON_SubDEdgePtr::Null = { 0 };
const ON_SubDFacePtr ON_SubDFacePtr::Null = { 0 };
const ON_SubDComponentPtr ON_SubDComponentPtr::Null = { 0 };
const ON_SubDComponentPtr ON_SubDComponentPtr::NullVertex = { 2 };
const ON_SubDComponentPtr ON_SubDComponentPtr::NullEdge = { 4 };
const ON_SubDComponentPtr ON_SubDComponentPtr::NullFace = { 6 };

const ON_SubDComponentId ON_SubDComponentId::Unset(ON_SubDComponentPtr::Null);

const ON_SubDComponentParameter ON_SubDComponentParameter::Unset = {};

const ON_SubDComponentPtrPair ON_SubDComponentPtrPair::Null = ON_SubDComponentPtrPair::Create(ON_SubDComponentPtr::Null,ON_SubDComponentPtr::Null);

const ON_SubDComponentAndNumber ON_SubDComponentAndNumber::NullAndNan = ON_SubDComponentAndNumber::Create(ON_SubDComponentPtr::Null, ON_DBL_QNAN);
const ON_SubDComponentAndNumber ON_SubDComponentAndNumber::NullAndZero = ON_SubDComponentAndNumber::Create(ON_SubDComponentPtr::Null, 0.0);

const ON_SubDComponentAndPoint ON_SubDComponentAndPoint::NullAndNan = ON_SubDComponentAndPoint::Create(ON_SubDComponentPtr::Null, ON_3dPoint::NanPoint);
const ON_SubDComponentAndPoint ON_SubDComponentAndPoint::NullAndOrigin = ON_SubDComponentAndPoint::Create(ON_SubDComponentPtr::Null, ON_3dPoint::Origin);

const ON_SubDComponentList ON_SubDComponentList::Empty;
const ON_SubD_ComponentIdTypeAndTag ON_SubD_ComponentIdTypeAndTag::Unset;

const ON_SubDComponentId ON_SubDComponentIdUnset(ON_SubDComponentPtr::Type::Unset, 0U);

// Passes() returns true for every non nullptr component.
const ON_SubDComponentTest ON_SubDComponentTest::AllPass((ON__UINT_PTR)1);
const ON_SubDComponentTest ON_SubDComponentTest::AllFail((ON__UINT_PTR)0);


const ON_SubDEdgeChain ON_SubDEdgeChain::Empty;

static ON_SubDSectorSurfacePoint Internal_ON_SubDSectorLimitPoint_Init(double x)
{
  ON_SubDSectorSurfacePoint lp;
  memset(&lp, 0, sizeof(lp));

  lp.m_limitP[0] = x;
  lp.m_limitP[1] = x;
  lp.m_limitP[2] = x;

  lp.m_limitT1[0] = x;
  lp.m_limitT1[1] = x;
  lp.m_limitT1[2] = x;

  lp.m_limitT2[0] = x;
  lp.m_limitT2[1] = x;
  lp.m_limitT2[2] = x;

  lp.m_limitN[0] = x;
  lp.m_limitN[1] = x;
  lp.m_limitN[2] = x;

  return lp;
}

const ON_SubDSectorSurfacePoint ON_SubDSectorSurfacePoint::Unset = Internal_ON_SubDSectorLimitPoint_Init(ON_UNSET_VALUE);
const ON_SubDSectorSurfacePoint ON_SubDSectorSurfacePoint::Nan = Internal_ON_SubDSectorLimitPoint_Init(ON_DBL_QNAN);
const ON_SubDSectorSurfacePoint ON_SubDSectorSurfacePoint::Zero = Internal_ON_SubDSectorLimitPoint_Init(0.0);

const ON_SubDVertexSurfacePointCoefficient ON_SubDVertexSurfacePointCoefficient::Zero = ON_SubDVertexSurfacePointCoefficient::Create(nullptr,nullptr,0.0);
const ON_SubDVertexSurfacePointCoefficient ON_SubDVertexSurfacePointCoefficient::Nan = ON_SubDVertexSurfacePointCoefficient::Create(nullptr,nullptr,ON_DBL_QNAN);
const ON_SubDVertexSurfacePointCoefficient ON_SubDVertexSurfacePointCoefficient::Unset = ON_SubDVertexSurfacePointCoefficient::Create(nullptr,nullptr,ON_UNSET_VALUE);

const double ON_SubDSectorType::IgnoredCornerSectorAngle = 0.0;
const double ON_SubDSectorType::UnsetCornerSectorAngle = -8881.0;
const double ON_SubDSectorType::ErrorCornerSectorAngle = -9991.0;

const double ON_SubDSectorType::SmoothSectorTheta = 0.5*ON_PI;
const double ON_SubDSectorType::UnsetSectorTheta = -8882.0;
const double ON_SubDSectorType::ErrorSectorTheta = -9992.0;

const double ON_SubDSectorType::IgnoredSectorCoefficient = 0.0;
const double ON_SubDSectorType::UnsetSectorCoefficient = -8883.0;
const double ON_SubDSectorType::ErrorSectorCoefficient = -9993.0;


const ON_SubDComponentRegionIndex ON_SubDComponentRegionIndex::Zero;

static ON_SubDComponentRegionIndex InternalON_SubDComponentRegionIndex_Unset()
{
  ON_SubDComponentRegionIndex unset;
  memset(&unset, 0xFF, sizeof(unset));
  return unset;
}
const ON_SubDComponentRegionIndex ON_SubDComponentRegionIndex::Unset = InternalON_SubDComponentRegionIndex_Unset();

const ON_SubDComponentRegion ON_SubDComponentRegion::Empty;
const ON_SubDFaceRegion ON_SubDFaceRegion::Empty;

const ON_ComponentStatus ON_ComponentStatus::NoneSet = ON_ComponentStatus(ON_ComponentState::Clear);
const ON_ComponentStatus ON_ComponentStatus::Selected = ON_ComponentStatus(ON_ComponentState::Selected);
const ON_ComponentStatus ON_ComponentStatus::SelectedPersistent = ON_ComponentStatus(ON_ComponentState::SelectedPersistent);
const ON_ComponentStatus ON_ComponentStatus::Highlighted = ON_ComponentStatus(ON_ComponentState::Highlighted);
const ON_ComponentStatus ON_ComponentStatus::Hidden = ON_ComponentStatus(ON_ComponentState::Hidden);
const ON_ComponentStatus ON_ComponentStatus::Locked = ON_ComponentStatus(ON_ComponentState::Locked);
const ON_ComponentStatus ON_ComponentStatus::Deleted = ON_ComponentStatus(ON_ComponentState::Deleted);
const ON_ComponentStatus ON_ComponentStatus::Damaged = ON_ComponentStatus(ON_ComponentState::Damaged);
const ON_ComponentStatus ON_ComponentStatus::Marked = ON_ComponentStatus(ON_ComponentState::RuntimeMarkSet);
static ON_ComponentStatus Internal_ON_ComponentStatus_AllSet()
{
  ON_ComponentStatus s;
  s.SetStates(ON_ComponentStatus::SelectedPersistent);
  s.SetStates(ON_ComponentStatus::Highlighted);
  s.SetStates(ON_ComponentStatus::Hidden);
  s.SetStates(ON_ComponentStatus::Locked);
  s.SetStates(ON_ComponentStatus::Damaged);
  return s;
}
const ON_ComponentStatus ON_ComponentStatus::AllSet = Internal_ON_ComponentStatus_AllSet();

static ON_AggregateComponentStatus ON_Internal_AggregateComponentStatus_Init(int k)
{
  ON_AggregateComponentStatus s;
  memset(&s, 0, sizeof(s));
  if (1 == k)
    s.MarkAsNotCurrent();
  return s;
}
const ON_AggregateComponentStatus ON_AggregateComponentStatus::Empty = ON_Internal_AggregateComponentStatus_Init(0);
const ON_AggregateComponentStatus ON_AggregateComponentStatus::NotCurrent = ON_Internal_AggregateComponentStatus_Init(1);


static ON_AggregateComponentStatusEx ON_Internal_AggregateComponentStatusEx_Init(int k)
{
  ON_AggregateComponentStatusEx s(ON_Internal_AggregateComponentStatus_Init(k));
  *((ON__UINT64*)(((char*)(&s)) + sizeof(ON_AggregateComponentStatus))) = 0; // m_component_status_serial_number = 0 
  return s;
}
const ON_AggregateComponentStatusEx ON_AggregateComponentStatusEx::Empty = ON_Internal_AggregateComponentStatusEx_Init(0);
const ON_AggregateComponentStatusEx ON_AggregateComponentStatusEx::NotCurrent = ON_Internal_AggregateComponentStatusEx_Init(1);



const ON_SubDComponentPoint ON_SubDComponentPoint::Unset = ON_SubDComponentPoint();

static ON_SubDMeshFragmentGrid Internal_EmptyLimitMeshFragmentGridInit()
{
  ON_SubDMeshFragmentGrid empty;
  memset(&empty, 0, sizeof(empty));
  return empty;
}

static ON_SubDMeshFragment Internal_EmptyLimitMeshFragmentInit()
{
  ON_SubDMeshFragment empty;
  memset(&empty, 0, sizeof(empty));
  return empty;
}

const ON_SubDMeshFragmentGrid ON_SubDMeshFragmentGrid::Empty = Internal_EmptyLimitMeshFragmentGridInit();
const ON_SubDMeshFragment ON_SubDMeshFragment::Empty = Internal_EmptyLimitMeshFragmentInit();



const ON_SubDMeshFragmentGrid ON_SubDMeshFragmentGrid::OneQuadGrid = ON_SubDMeshFragmentGrid::QuadGridFromSideSegmentCount(1, 0);

static const ON_SubDComponentBase Internal_UnsetComponentBaseInit()
{
  // For efficiency, ON_SubDComponentBase() does not waste time
  // m_cache_subd_P[], m_displacementV[]
  // but the offical "Unset" ON_SubDComponentBase should have every byte initialized.
  ON_SubDComponentBase unset;
  memset(&unset, 0, sizeof(unset));
  return unset;
}

static const ON_SubDVertex Internal_EmptyVertexInit()
{
  // For efficiency, ON_SubDVertex() does not waste time
  // initializing m_limitP[], ..., m_cache_subd_P[], m_displacementV[]
  // but the offical "Empty" vertex should have every byte initialized.
  ON_SubDVertex empty;
  memset(&empty, 0, sizeof(empty));
  return empty;
}

static const ON_SubDEdge Internal_EmptyEdgeInit()
{
  // For efficiency, ON_SubDEdge() does not waste time
  // initializing m_cache_subd_P[], m_displacementV[]
  // but the offical "Empty" edge should have every byte initialized.
  ON_SubDEdge empty;
  memset(&empty, 0, sizeof(empty));
  return empty;
}

static const ON_SubDFace Internal_EmptyFaceInit()
{
  // For efficiency, ON_SubDFace() does not waste time
  // initializing m_cache_subd_P[], m_displacementV[]
  // but the offical "Empty" face should have every byte initialized.
  ON_SubDFace empty;
  memset(&empty, 0, sizeof(empty));
  return empty;
}

const ON_SubDComponentBase ON_SubDComponentBase::Unset = Internal_UnsetComponentBaseInit();
const ON_SubDVertex ON_SubDVertex::Empty = Internal_EmptyVertexInit();
const ON_SubDEdge ON_SubDEdge::Empty = Internal_EmptyEdgeInit();
const ON_SubDFace ON_SubDFace::Empty = Internal_EmptyFaceInit();

const ON_SubD ON_SubD::Empty;
const ON_SubDRef ON_SubDRef::Empty;
const ON_SubDMesh ON_SubDMesh::Empty;
const ON_SubDSectorType ON_SubDSectorType::Empty;
const ON_SubDMatrix ON_SubDMatrix::Empty;
const ON_SubDComponentRef ON_SubDComponentRef::Empty;

static ON_SubDFromMeshParameters Internal_InteriorCreases()
{
  ON_SubDFromMeshParameters cp;
  cp.SetInteriorCreaseOption(ON_SubDFromMeshParameters::InteriorCreaseOption::AtMeshDoubleEdge);
  return cp;
}

static ON_SubDFromMeshParameters Internal_ConvexCornersAndInteriorCreases()
{
  ON_SubDFromMeshParameters cp;
  cp.SetInteriorCreaseOption(ON_SubDFromMeshParameters::InteriorCreaseOption::AtMeshDoubleEdge);
  cp.SetConvexCornerOption(ON_SubDFromMeshParameters::ConvexCornerOption::AtMeshCorner);
  return cp;
}

static ON_SubDFromMeshParameters Internal_ConvexAndConcaveCornersAndInteriorCreases()
{
  ON_SubDFromMeshParameters cp;
  cp.SetInteriorCreaseOption(ON_SubDFromMeshParameters::InteriorCreaseOption::AtMeshDoubleEdge);
  cp.SetConvexCornerOption(ON_SubDFromMeshParameters::ConvexCornerOption::AtMeshCorner);
  cp.SetConcaveCornerOption(ON_SubDFromMeshParameters::ConcaveCornerOption::AtMeshCorner);
  return cp;
}

const ON_SubDFromMeshParameters ON_SubDFromMeshParameters::Smooth;
const ON_SubDFromMeshParameters ON_SubDFromMeshParameters::InteriorCreases = Internal_InteriorCreases();
const ON_SubDFromMeshParameters ON_SubDFromMeshParameters::ConvexCornersAndInteriorCreases = Internal_ConvexCornersAndInteriorCreases();
const ON_SubDFromMeshParameters ON_SubDFromMeshParameters::ConvexAndConcaveCornersAndInteriorCreases = Internal_ConvexAndConcaveCornersAndInteriorCreases();

const ON_SubDFromSurfaceParameters ON_SubDFromSurfaceParameters::Default;

static const ON_SubDFromSurfaceParameters Internal_InitSubDFromSurfaceParameters(
  ON_SubDFromSurfaceParameters::Methods method,
  bool bCorners
  )
{
  ON_SubDFromSurfaceParameters p;
  if (ON_SubDFromSurfaceParameters::Methods::Unset != method)
    p.SetMethod(method);
  p.SetCorners(bCorners);
  return p;
}

const ON_SubDFromSurfaceParameters ON_SubDFromSurfaceParameters::DefaultWithCorners = Internal_InitSubDFromSurfaceParameters(ON_SubDFromSurfaceParameters::Methods::Unset, true);
const ON_SubDFromSurfaceParameters ON_SubDFromSurfaceParameters::ControlNet = Internal_InitSubDFromSurfaceParameters(ON_SubDFromSurfaceParameters::Methods::FromNurbsControlNet, false);
const ON_SubDFromSurfaceParameters ON_SubDFromSurfaceParameters::ControlNetWithCorners = Internal_InitSubDFromSurfaceParameters(ON_SubDFromSurfaceParameters::Methods::FromNurbsControlNet, true);


const ON_SubDComponentFilter ON_SubDComponentFilter::Unset = ON_SubDComponentFilter::Create(true, true, true);
const ON_SubDComponentFilter ON_SubDComponentFilter::OnlyVertices = ON_SubDComponentFilter::Create(true, false, false);
const ON_SubDComponentFilter ON_SubDComponentFilter::OnlyEdges = ON_SubDComponentFilter::Create(false, true, false);
const ON_SubDComponentFilter ON_SubDComponentFilter::OnlyFaces = ON_SubDComponentFilter::Create(false, false, true);

unsigned int ON_ModelComponent::Internal_SystemComponentHelper()
{
  static unsigned int rc = 0;
  if (0 == rc)
  {
    rc = 1;
    const ON_ModelComponent* list[] =
    {
      &ON_ModelComponent::Unset,
      &ON_InstanceDefinition::Unset,
      &ON_Linetype::Unset,
      &ON_Layer::Unset,
      &ON_TextStyle::Unset,
      &ON_DimStyle::Unset,
      &ON_Material::Unset,
      &ON_Material::Default,
      &ON_Material::DefaultLockedObject,
      &ON_TextureMapping::Unset,
      &ON_TextureMapping::SurfaceParameterTextureMapping,
      &ON_HatchPattern::Unset,
      &ON_Group::Unset,
      &ON_HistoryRecord::Empty
    };

    const ON_ModelComponent* list_localized_name[] =
    {
      &ON_Linetype::Continuous,
      &ON_Linetype::ByLayer,
      &ON_Linetype::ByParent,
      &ON_Linetype::Hidden,
      &ON_Linetype::Dashed,
      &ON_Linetype::DashDot,
      &ON_Linetype::Center,
      &ON_Linetype::Border,
      &ON_Linetype::Dots,

      &ON_Layer::Default,

      &ON_TextStyle::Default,
      &ON_TextStyle::ByLayer,
      &ON_TextStyle::ByParent,

      &ON_DimStyle::Default,
      &ON_DimStyle::DefaultInchDecimal,
      &ON_DimStyle::DefaultInchFractional,
      &ON_DimStyle::DefaultFootInchArchitecture,
      &ON_DimStyle::DefaultMillimeterSmall,
      &ON_DimStyle::DefaultMillimeterLarge,
      &ON_DimStyle::DefaultMillimeterArchitecture,
      &ON_DimStyle::DefaultFeetDecimal,
      &ON_DimStyle::DefaultModelUnitsDecimal,
      &ON_DimStyle::DefaultFeetEngrave,
      &ON_DimStyle::DefaultMillimeterEngrave,
      &ON_DimStyle::DefaultModelUnitsEngrave,
 
      &ON_HatchPattern::Solid,
      &ON_HatchPattern::Hatch1,
      &ON_HatchPattern::Hatch2,
      &ON_HatchPattern::Hatch3,
      &ON_HatchPattern::HatchDash,
      &ON_HatchPattern::Grid,
      &ON_HatchPattern::Grid60,
      &ON_HatchPattern::Plus,
      &ON_HatchPattern::Squares
    };

    const size_t list_count = sizeof(list) / sizeof(list[0]);
    for (size_t i = 0; i < list_count; i++)
    {
      *(const_cast<unsigned short*>(&list[i]->m_locked_status)) = 0xFFFFU;
      *(const_cast<ON__UINT64*>(&list[i]->m_content_version_number)) = 0;
    }

    const unsigned int name_bit = ON_ModelComponent::Attributes::NameAttribute;
    const unsigned int name_mask = ~name_bit;
    const unsigned short bits
      = (unsigned short)((name_mask & ON_ModelComponent::Attributes::AllAttributes) | ON_ModelComponent::Attributes::SystemComponentAttribute);
    const size_t list_localized_name_count = sizeof(list_localized_name) / sizeof(list_localized_name[0]);
    for (size_t i = 0; i < list_localized_name_count; i++)
    {
      *(const_cast<unsigned short*>(&list_localized_name[i]->m_locked_status)) = bits;
      *(const_cast<ON__UINT64*>(&list_localized_name[i]->m_content_version_number)) = 0;
    }

    rc = (unsigned int)(list_count + list_localized_name_count);
  }
  return rc;
}

const ON_SectionStyle ON_SectionStyle::Unset;
