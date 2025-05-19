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
#include "opennurbs_internal_defines.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4127)

ON__INT64 Integerize(float dirty)
{
  // Use this function when CRCing floats. This eliminates the problem of
  // rounding errors causing different CRCs to be generated for essentially the same value.
  return ON__INT64(
   (dirty      // 0.499999976 0.500000003 (both essentially 0.5 with float dirt).
    + 1e-6)    // 0.500000976 0.500001003
    * 1e+5)    // 050000.0976 050000.1003
    ;          //  50000      50000       (both will give the same CRC adjustment).
}

ON__INT64 Integerize(double dirty)
{
  // Use this function when CRCing doubles. This eliminates the problem of
  // rounding errors causing different CRCs to be generated for essentially the same value.
  return ON__INT64(
   (dirty      // 0.49999999999997 0.50000000000002 (both essentially 0.5 with float dirt).
    + 1e-11)   // 0.50000000000997 0.50000000001002
    * 1e+10)   //  5000000000.0997  5000000000.1002
    ;          //  5000000000       5000000000      (both will give the same CRC adjustment).
}

#ifdef _DEBUG
static void MyOutputDebugString(const wchar_t* s)
{
#ifdef ON_COMPILER_MSC
  OutputDebugString(s);
#else
  // No Mac implementation.
#endif
}
#define OUTPUT_DEBUG_STRING(x)       MyOutputDebugString(x)
#define OUTPUT_DEBUG_STRING_EOL(x) { MyOutputDebugString(x); MyOutputDebugString(L"\n"); }
#else
#define OUTPUT_DEBUG_STRING(x)     { }
#define OUTPUT_DEBUG_STRING_EOL(x) { }
#endif

std::atomic<long> g_lNodeCount(0);
std::atomic<long> g_lPropertyCount(-1); // defaultProp below increments this to zero.

#define ON_NAME       L"name"
#define ON_PARAMETER  L"parameter"

static const wchar_t* wszBase64Prefix = L"base64:";

#ifdef ON_COMPILER_MSC
static _locale_t __Locale(void)
{
  static _locale_t loc = nullptr;

  if (nullptr == loc)
    loc = _create_locale(LC_ALL, "C");

  return loc;
}

inline double ON_wtof(const wchar_t* s) { return _wtof_l(s, __Locale()); }
inline int    ON_wtoi(const wchar_t* s) { return _wtoi_l(s, __Locale()); }
#else
inline double ON_wtof(const wchar_t* s) { return wcstod(s, nullptr); }
inline int    ON_wtoi(const wchar_t* s) { return (int)wcstol(s, nullptr, 10); }
#endif

static const wchar_t* StringFromUnits(ON::LengthUnitSystem units)
{
  // These strings appear in the XML -- do not change them.

  switch (units)
  {
  case ON::LengthUnitSystem::Angstroms:         return L"angstroms";
  case ON::LengthUnitSystem::AstronomicalUnits: return L"astronomical";
  case ON::LengthUnitSystem::Centimeters:       return L"centimeters";
  case ON::LengthUnitSystem::Decimeters:        return L"decimeters";
  case ON::LengthUnitSystem::Dekameters:        return L"dekameters";
  case ON::LengthUnitSystem::Feet:              return L"feet";
  case ON::LengthUnitSystem::Gigameters:        return L"gigameters";
  case ON::LengthUnitSystem::Hectometers:       return L"hectometers";
  case ON::LengthUnitSystem::Inches:            return L"inches";
  case ON::LengthUnitSystem::Kilometers:        return L"kilometers";
  case ON::LengthUnitSystem::LightYears:        return L"lightyears";
  case ON::LengthUnitSystem::Megameters:        return L"megameters";
  case ON::LengthUnitSystem::Meters:            return L"meters";
  case ON::LengthUnitSystem::Microinches:       return L"microinches";
  case ON::LengthUnitSystem::Microns:           return L"microns";
  case ON::LengthUnitSystem::Miles:             return L"miles";
  case ON::LengthUnitSystem::Millimeters:       return L"millimeters";
  case ON::LengthUnitSystem::Mils:              return L"mils";
  case ON::LengthUnitSystem::Nanometers:        return L"nanometers";
  case ON::LengthUnitSystem::NauticalMiles:     return L"nautical-miles";
  case ON::LengthUnitSystem::Parsecs:           return L"parsecs";
  case ON::LengthUnitSystem::Yards:             return L"yards";
    default:
        break;
  }

  return L"none";
}

static ON::LengthUnitSystem UnitsFromString(const ON_wString& s)
{
  if (L"angstroms" == s)       return ON::LengthUnitSystem::Angstroms;
  if (L"astronomical" == s)    return ON::LengthUnitSystem::AstronomicalUnits;
  if (L"centimeters" == s)     return ON::LengthUnitSystem::Centimeters;
  if (L"decimeters" == s)      return ON::LengthUnitSystem::Decimeters;
  if (L"dekameters" == s)      return ON::LengthUnitSystem::Dekameters;
  if (L"feet" == s)            return ON::LengthUnitSystem::Feet;
  if (L"gigameters" == s)      return ON::LengthUnitSystem::Gigameters;
  if (L"hectometers" == s)     return ON::LengthUnitSystem::Hectometers;
  if (L"inches" == s)          return ON::LengthUnitSystem::Inches;
  if (L"kilometers" == s)      return ON::LengthUnitSystem::Kilometers;
  if (L"lightyears" == s)      return ON::LengthUnitSystem::LightYears;
  if (L"megameters" == s)      return ON::LengthUnitSystem::Megameters;
  if (L"meters" == s)          return ON::LengthUnitSystem::Meters;
  if (L"microinches" == s)     return ON::LengthUnitSystem::Microinches;
  if (L"microns" == s)         return ON::LengthUnitSystem::Microns;
  if (L"miles" == s)           return ON::LengthUnitSystem::Miles;
  if (L"millimeters" == s)     return ON::LengthUnitSystem::Millimeters;
  if (L"mils" == s)            return ON::LengthUnitSystem::Mils;
  if (L"nanometers" == s)      return ON::LengthUnitSystem::Nanometers;
  if (L"nautical-miles" == s)  return ON::LengthUnitSystem::NauticalMiles;
  if (L"parsecs" == s)         return ON::LengthUnitSystem::Parsecs;
  if (L"yards" == s)           return ON::LengthUnitSystem::Yards;

  return ON::LengthUnitSystem::None;
}

static void EncodeXML(ON_wString& s)
{
  // Call this instead of directly calling ON_wString::EncodeXMLValue().
  // The latter does not encode linefeeds and it also does not encode the string in place.
  // However, ON_wString::DecodeXMLValue() _does_ decode linefeeds.
  s = s.EncodeXMLValue();
  s.Replace(L"\n", L"&#10;");
}

static void DecodeXML(ON_wString& s)
{
  // Call this instead of directly calling ON_wString::DecodeXMLValue().
  // The latter _does_ decode linefeeds but it does not decode the string in place.
  if (s.Find(L'&') >= 0)
  {
    s = s.DecodeXMLValue();
  }
}

static bool GetTimeComponents(const ON_wString& sTime, int& y, int& m, int& d, int& h, int& n, int& s)
{
  if (19 != sTime.Length())
    return false;

  auto* wsz = static_cast<const wchar_t*>(sTime);

  if ((wsz[4] != L'.') || (wsz[7] != L'.') || (wsz[10] != L'_') || (wsz[13] != L':') || (wsz[16] != L':'))
    return false;

  y = ON_wtoi(wsz);
  m = ON_wtoi(wsz + 5);
  d = ON_wtoi(wsz + 8);
  h = ON_wtoi(wsz + 11);
  n = ON_wtoi(wsz + 14);
  s = ON_wtoi(wsz + 17);

  if ((y < 1900) || (y > 2500))
    return false;

  if ((m < 1) || (m > 12))
    return false;

  if ((d < 1) || (d > 31))
    return false;

  if ((h < 0) || (h > 23))
    return false;

  if ((n < 0) || (n > 59))
    return false;

  if ((s < 0) || (s > 59))
    return false;

  return true;
}

static ON_wString TimeToString(time_t time)
{
  tm stm = { 0 };

#ifdef ON_COMPILER_MSC
  localtime_s(&stm, &time);
#else
  localtime_r(&time, &stm);
#endif

  ON_wString st;
  st.Format(L"%04u.%02u.%02u_%02u:%02u:%02u", stm.tm_year + 1900, stm.tm_mon + 1, stm.tm_mday, stm.tm_hour, stm.tm_min, stm.tm_sec);

  return st;
}

static time_t TimeFromString(const ON_wString& sTime)
{
  int y = 0, m = 0, d = 0, h = 0, n = 0, s = 0;
  if (!GetTimeComponents(sTime, y, m, d, h, n, s))
    return -1;

  tm atm = { 0 };
  atm.tm_year  = y - 1900;
  atm.tm_mon   = m - 1;
  atm.tm_mday  = d;
  atm.tm_hour  = h;
  atm.tm_min   = n;
  atm.tm_sec   = s;
  atm.tm_isdst = -1;

  return mktime(&atm);
}

// ON_XMLVariant

class ON_XMLVariantPrivate final
{
public:
  ON_XMLVariantPrivate() { }
  ~ON_XMLVariantPrivate() { ClearBuffers(); }

  ON_Buffer& GetBuffer(void) const
  {
    if (nullptr == _buffer)
      _buffer = new ON_Buffer;
    else
      _buffer->SeekFromStart(0);

    return *_buffer;
  }

  void ClearBuffers(void)
  {
    if (nullptr != _buffer)
    {
      delete _buffer;
      _buffer = nullptr;
    }

    if (nullptr != _raw_buffer)
    {
      delete[] _raw_buffer;
      _raw_buffer = nullptr;
    }
  }

  const ON_wString& ConvertDoubleToString(double d) const
  {
    auto* buf = _string_val.SetLength(30);
    if (nullptr != buf)
    {
      const auto len = ON_wString::FormatIntoBuffer(buf, 24, L"%.15g", d);
      _string_val.SetLength(len);
    }

    return _string_val;
  }

  const ON_wString& ConvertDoubleArrayToString(int count) const
  {
    constexpr int maxCount = array_val_max;
    if ((count < 1) || (count > maxCount))
      return _string_val;

    constexpr int maxLen = 30;

    const auto num_chars = maxLen * maxCount;
    auto* buf = _string_val.SetLength(num_chars);
    if (nullptr == buf)
      return _string_val;

    int totalLen = 0;
    auto* p = buf;
    for (int i = 0; i < count; i++)
    {
      const auto len = ON_wString::FormatIntoBuffer(p, maxLen, L"%.15g", _array_val[i]);
      p += len;
      *p++ = L',';
      totalLen += len + 1;
    }

    // Real length is totalLen - 1 because final comma is excess.
    const auto length = totalLen - 1;
    if (length >= 0)
    {
      buf[length] = 0;
    }

    _string_val.SetLength(length);

    return _string_val;
  }

  mutable ON_Buffer* _buffer = nullptr;
  mutable ON_wString _string_val;

  static constexpr int array_val_max = 16;
  union
  {
    bool _bool_val;
    int _int_val;
    float _float_val;
    double _double_val;
    ON_Xform m_xform;
    time_t _time_val;
    ON_UUID _uuid_val;
    double _array_val[array_val_max] = { 0 };
  };

  ON::LengthUnitSystem _units = ON::LengthUnitSystem::None;
  ON__UINT8* _raw_buffer = nullptr;
  bool _type_pending = false;
  bool _varies = false;
  ON_XMLVariant::Types _type = ON_XMLVariant::Types::Null;
};

ON_XMLVariant::ON_XMLVariant()
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
}

ON_XMLVariant::ON_XMLVariant(int iValue)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(iValue);
}

ON_XMLVariant::ON_XMLVariant(double dValue)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(dValue);
}

ON_XMLVariant::ON_XMLVariant(float fValue)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(fValue);
}

ON_XMLVariant::ON_XMLVariant(const ON_wString& s)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(s);
}

ON_XMLVariant::ON_XMLVariant(const double* point, ArrayTypes at)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(point, at);
}

ON_XMLVariant::ON_XMLVariant(const float* point, ArrayTypes at)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(point, at);
}

ON_XMLVariant::ON_XMLVariant(const wchar_t* wsz)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  ON_wString s(wsz);
  SetValue(s);
}

ON_XMLVariant::ON_XMLVariant(const ON_2dPoint& p)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(p);
}

ON_XMLVariant::ON_XMLVariant(const ON_3dPoint& p)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(p);
}

ON_XMLVariant::ON_XMLVariant(const ON_4fColor& c)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(c);
}

ON_XMLVariant::ON_XMLVariant(bool b)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(b);
}

ON_XMLVariant::ON_XMLVariant(const ON_UUID& uuid)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(uuid);
}

ON_XMLVariant::ON_XMLVariant(const ON_Xform& xform)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(xform);
}

ON_XMLVariant::ON_XMLVariant(time_t time)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(time);
}

ON_XMLVariant::ON_XMLVariant(const void* pBuffer, size_t size)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(pBuffer, size);
}

ON_XMLVariant::ON_XMLVariant(const ON_Buffer& buffer)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  SetValue(buffer);
}

ON_XMLVariant::ON_XMLVariant(const ON_XMLVariant& src)
{
  _private = new (_PRIVATE) ON_XMLVariantPrivate; PRIVATE_CHECK(ON_XMLVariantPrivate);
  *this = src;
}

ON_XMLVariant::~ON_XMLVariant()
{
  _private->~ON_XMLVariantPrivate();
  _private = nullptr;
}

ON_Buffer& ON_XMLVariant::GetBuffer(void) const
{
  return _private->GetBuffer();
}

void ON_XMLVariant::ClearBuffers(void)
{
  _private->ClearBuffers();
}

const ON_XMLVariant& ON_XMLVariant::operator = (const ON_XMLVariant& src)
{
  _private->_type = src.Type();
  _private->_type_pending = src.TypePending();

  if (_private->_type != Types::Buffer)
  {
    ClearBuffers();
  }

  switch (_private->_type)
  {
  case Types::Null:                                                  break;
  case Types::Bool:         _private->_bool_val   = src.AsBool();    break;
  case Types::Integer:      _private->_int_val    = src.AsInteger(); break;
  case Types::Float:        _private->_float_val  = src.AsFloat();   break;
  case Types::Double:       _private->_double_val = src.AsDouble();  break;
  case Types::String:       _private->_string_val = src.AsString();  break;
  case Types::Uuid:         _private->_uuid_val   = src.AsUuid();    break;
  case Types::Time:         _private->_time_val   = src.AsTime();    break;
  case Types::DoubleArray2: SetValue(src.As2dPoint());               break;
  case Types::DoubleArray3: SetValue(src.As3dPoint());               break;
  case Types::DoubleArray4: SetValue(src.As4dPoint());               break;
  case Types::DoubleColor4: SetValue(src.AsColor());                 break;
  case Types::Matrix:       SetValue(src.AsXform()) ;                break;
  case Types::Buffer:       GetBuffer() = src.AsBuffer();            break;

  default:
    OUTPUT_DEBUG_STRING(L"ON_XMLVariant: Source has unknown type\n");
    ON_ASSERT(false);
  }

  // The above calls can reset the type pending flag on the source.
  // Make sure the source is set back to the original condition.
  src.SetTypePendingFlag(_private->_type_pending);

  _private->_varies = src.Varies();

  return *this;
}

bool ON_XMLVariant::operator == (const ON_XMLVariant& v) const
{
  if (_private->_type != v._private->_type)
    return false;

  if (_private->_units != v._private->_units)
    return false;

  switch (_private->_type)
  {
  case Types::Bool:
    return _private->_bool_val == v._private->_bool_val;

  case Types::Integer:
    return _private->_int_val == v._private->_int_val;

  case Types::Float:
    return IsFloatEqual(_private->_float_val, v._private->_float_val) ? true : false;

  case Types::Double:
    return IsDoubleEqual(_private->_double_val, v._private->_double_val) ? true : false;

  case Types::DoubleArray2:
    return ((IsDoubleEqual(_private->_array_val[0], v._private->_array_val[0])) &&
            (IsDoubleEqual(_private->_array_val[1], v._private->_array_val[1]))) ? true : false;

  case Types::DoubleArray3:
    return ((IsDoubleEqual(_private->_array_val[0], v._private->_array_val[0])) &&
            (IsDoubleEqual(_private->_array_val[1], v._private->_array_val[1])) &&
            (IsDoubleEqual(_private->_array_val[2], v._private->_array_val[2]))) ? true : false;

  case Types::DoubleColor4:
  case Types::DoubleArray4:
    return ((IsDoubleEqual(_private->_array_val[0], v._private->_array_val[0])) &&
            (IsDoubleEqual(_private->_array_val[1], v._private->_array_val[1])) &&
            (IsDoubleEqual(_private->_array_val[2], v._private->_array_val[2])) &&
            (IsDoubleEqual(_private->_array_val[3], v._private->_array_val[3]))) ? true : false;

  case Types::String:
    return _private->_string_val.CompareNoCase(v._private->_string_val) == 0;

  case Types::Uuid:
    return (_private->_uuid_val == v._private->_uuid_val) ? true : false;

  case Types::Time:
    return _private->_time_val == v._private->_time_val;

  case Types::Matrix:
      for (int i = 0; i < _private->array_val_max; i++)
      {
        if (_private->_array_val[i] != v._private->_array_val[i])
          return false;
      }
  case Types::Null:
      return true;

  default:
    ON_ASSERT(false);
  }

  return false;
}

bool ON_XMLVariant::operator != (const ON_XMLVariant& v) const
{
  return !(operator == (v));
}

bool ON_XMLVariant::NeedsXMLEncode(void) const
{
  switch (_private->_type)
  {
  case Types::Null:
  case Types::Bool:
  case Types::Integer:
  case Types::Float:
  case Types::Double:
  case Types::DoubleArray2:
  case Types::DoubleArray3:
  case Types::DoubleArray4:
  case Types::DoubleColor4:
  case Types::Uuid:
  case Types::Matrix:
  case Types::Buffer:
    return false;

  default:
    {
    const auto s = AsString();
    if (s.StartsWithNoCase(wszBase64Prefix))
      return false;

    return s.NeedsXMLEncode();
    }
  }
}

void ON_XMLVariant::SetNull()
{
  _private->_type = Types::Null;
}

void ON_XMLVariant::SetValue(int v)
{
  ClearBuffers();
  _private->_type = Types::Integer;
  _private->_int_val = v;
  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(double v)
{
  ClearBuffers();
  _private->_type = Types::Double;
  _private->_double_val = v;
  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(float v)
{
  ClearBuffers();
  _private->_type = Types::Float;
  _private->_float_val = v;
  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(const wchar_t* s)
{
  ClearBuffers();
  _private->_type = Types::String;
  _private->_string_val = s;
  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(const ON_wString& s)
{
  ClearBuffers();
  _private->_type = Types::String;
  _private->_string_val = s;
  _private->_varies = false;
  _private->_type_pending = false;
}

inline static void Fill(double* a, const double* b, int count)
{
  for (int i = 0; i < count; i++)
  {
    a[i] = b[i];
  }
}

inline static void Fill(double* a, const float* b, int count)
{
  for (int i = 0; i < count; i++)
  {
    a[i] = double(b[i]);
  }
}

void ON_XMLVariant::SetValue(const double* p, ArrayTypes at)
{
  ClearBuffers();

  switch (at)
  {
  case ArrayTypes::Array2:  _private->_type = Types::DoubleArray2; Fill(_private->_array_val, p, 2);  break;
  case ArrayTypes::Array3:  _private->_type = Types::DoubleArray3; Fill(_private->_array_val, p, 3);  break;
  case ArrayTypes::Array4:  _private->_type = Types::DoubleArray4; Fill(_private->_array_val, p, 4);  break;
  case ArrayTypes::Array16: _private->_type = Types::Matrix;       Fill(_private->_array_val, p, 16); break;
  }

  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(const float* p, ArrayTypes at)
{
  ClearBuffers();

  switch (at)
  {
  case ArrayTypes::Array2:  _private->_type = Types::DoubleArray2; Fill(_private->_array_val, p, 2);  break;
  case ArrayTypes::Array3:  _private->_type = Types::DoubleArray3; Fill(_private->_array_val, p, 3);  break;
  case ArrayTypes::Array4:  _private->_type = Types::DoubleArray4; Fill(_private->_array_val, p, 4);  break;
  case ArrayTypes::Array16: _private->_type = Types::Matrix;       Fill(_private->_array_val, p, 16); break;
  }

  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(const ON_2dPoint& v)
{
  ClearBuffers();

  _private->_type = Types::DoubleArray2;

  _private->_array_val[0] = v.x;
  _private->_array_val[1] = v.y;

  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(const ON_3dPoint& v)
{
  ClearBuffers();

  _private->_type = Types::DoubleArray3;

  _private->_array_val[0] = v.x;
  _private->_array_val[1] = v.y;
  _private->_array_val[2] = v.z;

  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(const ON_4dPoint& p)
{
  ClearBuffers();

  _private->_type = Types::DoubleArray4;

  _private->_array_val[0] = p.x;
  _private->_array_val[1] = p.y;
  _private->_array_val[2] = p.z;
  _private->_array_val[3] = p.w;

  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(const ON_4fColor& c)
{
  ClearBuffers();

  _private->_type = Types::DoubleColor4;

  _private->_array_val[0] = c.Red();
  _private->_array_val[1] = c.Green();
  _private->_array_val[2] = c.Blue();
  _private->_array_val[3] = c.Alpha();

  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(bool b)
{
  ClearBuffers();

  _private->_type = Types::Bool;

  _private->_bool_val = b;
  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(const ON_UUID& uuid)
{
  ClearBuffers();

  _private->_type = Types::Uuid;

  _private->_uuid_val = uuid;
  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(time_t time)
{
  ClearBuffers();

  _private->_type = Types::Time;

  _private->_time_val = time;
  _private->_varies = false;
  _private->_type_pending = false;
}

void ON_XMLVariant::SetValue(const void* pBuffer, size_t size)
{
  ClearBuffers();

  _private->_type = Types::Buffer;

  _private->_varies = false;
  _private->_type_pending = false;

  GetBuffer().Write(size, pBuffer);
}

void ON_XMLVariant::SetValue(const ON_Buffer& buffer)
{
  _private->_type = Types::Buffer;

  _private->_varies = false;
  _private->_type_pending = false;

  GetBuffer() = buffer;
}

void ON_XMLVariant::SetValue(const ON_Xform& xform)
{
  ClearBuffers();

  _private->_type = Types::Matrix;

  _private->m_xform = xform;
  _private->_varies = false;
  _private->_type_pending = false;
}

bool ON_XMLVariant::AsBool(void) const
{
  switch (_private->_type)
  {
  case Types::Bool:    return _private->_bool_val;
  case Types::Integer: return _private->_int_val != 0;
  case Types::Double:  return _private->_double_val != 0;
  case Types::Float:   return _private->_float_val != 0;

  case Types::String:
    if (_private->_string_val.CompareNoCase(L"true") == 0) return true;
    if (_private->_string_val.CompareNoCase(L"t")    == 0) return true;
    return ON_wtoi(_private->_string_val) != 0;

  default:
    return false;
  }
}

int ON_XMLVariant::AsInteger(void) const
{
  switch (_private->_type)
  {
  case Types::Bool:    return     _private->_bool_val ? 1 : 0;
  case Types::Integer: return     _private->_int_val;
  case Types::Double:  return int(_private->_double_val);
  case Types::Float:   return int(_private->_float_val);

  case Types::String:
    if (_private->_string_val.CompareNoCase(L"true") == 0) return 1;
    if (_private->_string_val.CompareNoCase(L"t") == 0) return true;
    return ON_wtoi(_private->_string_val);

  default:
    return 0;
  }
}

static bool IsValidRealNumber(const ON_wString& s)
{
  if (s.ContainsNoCase(L"nan"))
    return false;

  if (s.ContainsNoCase(L"in")) // ind, inf.
    return false;

  return true;
}

double ON_XMLVariant::AsDouble(void) const
{
  switch (_private->_type)
  {
  case Types::Bool:    return         _private->_bool_val ? 1.0 : 0.0;
  case Types::Float:   return         _private->_float_val;
  case Types::Double:  return         _private->_double_val;
  case Types::Integer: return double (_private->_int_val);
  case Types::String:
    if (IsValidRealNumber(_private->_string_val))
      return ON_wtof(_private->_string_val);

  default:
    return 0.0;
  }
}

float ON_XMLVariant::AsFloat(void) const
{
  switch (_private->_type)
  {
  case Types::Bool:    return       _private->_bool_val ? 1.0f : 0.0f;
  case Types::Float:   return       _private->_float_val;
  case Types::Double:  return float(_private->_double_val);
  case Types::Integer: return float(_private->_int_val);
  case Types::String:
    if (IsValidRealNumber(_private->_string_val))
      return float(ON_wtof(_private->_string_val));

  default:
    return 0.0f;
  }
}

ON_2dPoint ON_XMLVariant::As2dPoint(void) const
{
  switch (_private->_type)
  {
  case Types::DoubleArray2:
  case Types::DoubleArray3:
  case Types::DoubleArray4:
  case Types::DoubleColor4:
    break;

  case Types::String:
    if (_private->_string_val.IsValid2dPoint())
      StringToPoint(2);
      break;

  default:
    return ON_2dPoint::Origin;
  }

  return ON_2dPoint(_private->_array_val[0], _private->_array_val[1]);
}

ON_3dPoint ON_XMLVariant::As3dPoint(void) const
{
  switch (_private->_type)
  {
  case Types::DoubleArray2:
    _private->_array_val[2] = 0.0;
    break;

  case Types::DoubleArray3:
  case Types::DoubleArray4:
  case Types::DoubleColor4:
    break;

  case Types::String:
    if (_private->_string_val.IsValid3dPoint())
      StringToPoint(3);
    break;

  default:
    return ON_3dPoint::Origin;
  }

  return ON_3dPoint(_private->_array_val[0], _private->_array_val[1], _private->_array_val[2]);
}

ON_4dPoint ON_XMLVariant::As4dPoint(void) const
{
  switch (_private->_type)
  {
  case Types::DoubleArray2:
    _private->_array_val[2] = 0.0;
  case Types::DoubleArray3:
    _private->_array_val[3] = 0.0;
    break;

  case Types::DoubleArray4:
  case Types::DoubleColor4:
    break;

  case Types::String:
    if (_private->_string_val.IsValid4dPoint())
      StringToPoint(4);
    break;

  default:
    return ON_4dPoint::Zero;
  }

  return ON_4dPoint(_private->_array_val[0], _private->_array_val[1], _private->_array_val[2], _private->_array_val[3]);
}

ON_Xform ON_XMLVariant::AsXform(void) const
{
  switch (_private->_type)
  {
  case Types::Matrix:
    return _private->m_xform;

  case Types::String:
    if (_private->_string_val.IsValidMatrix())
    {
      StringToPoint(16);
      return _private->m_xform;
    }

  default:
    return ON_Xform::Zero4x4;
  }
}

ON_4fColor ON_XMLVariant::AsColor(void) const
{
  ON_4fColor col(ON_Color(0, 0, 0, 0));

  switch (_private->_type)
  {
  case Types::String:
    StringToPoint(4);
    // No break...
  case Types::DoubleArray4:
  case Types::DoubleColor4:
    col.SetRGBA(float(_private->_array_val[0]), float(_private->_array_val[1]), float(_private->_array_val[2]), float(_private->_array_val[3]));
  
  default:
    break;
  }

  return col;
}

ON_UUID ON_XMLVariant::AsUuid(void) const
{
  switch (_private->_type)
  {
  case Types::String:
    return ON_UuidFromString(_private->_string_val);

  case Types::Uuid:
    return _private->_uuid_val;

  default:
    return ON_nil_uuid;
  }
}

time_t ON_XMLVariant::AsTime(void) const
{
  switch (_private->_type)
  {
  case Types::String:
    return TimeFromString(_private->_string_val);

  case Types::Time:
    return _private->_time_val;
          
  default: return 0;
  }
}

ON_Buffer ON_XMLVariant::AsBuffer(void) const
{
  ON_Buffer buf;
#if defined(ON_RUNTIME_APPLE)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"
#endif
  switch (_private->_type)
  {
  case Types::Buffer:
    buf = GetBuffer();
    break;

  case Types::String:
    auto& s = _private->_string_val;
    if (s.StartsWithNoCase(wszBase64Prefix) && (s != wszBase64Prefix))
    {
      // Base64 is about 33% bigger than the resulting data so the string length is always enough.
      const auto size = size_t(s.Length());
      auto* p = new ON__UINT8[size];
      const auto prefix_len = ON_wString(wszBase64Prefix).Length();
      const auto decoded = ON_Base64::Decode(s.Mid(prefix_len), p);
      buf.Write(decoded, p);
      delete[] p;
    }
    break;
  }
#if defined(ON_RUNTIME_APPLE)
#pragma clang diagnostic pop
#endif
  return buf;
}

void* ON_XMLVariant::AsBuffer(size_t& size_out) const
{
  auto buf = AsBuffer();
  size_out = size_t(buf.Size());

  if (nullptr != _private->_raw_buffer)
    delete[] _private->_raw_buffer;

  _private->_raw_buffer = new ON__UINT8[size_out];
  buf.Read(size_out, _private->_raw_buffer);

  return _private->_raw_buffer;
}

ON_wString ON_XMLVariant::AsString(void) const
{
  switch (_private->_type)
  {
  case Types::Integer:
    return _private->ConvertDoubleToString(double(_private->_int_val));

  case Types::Float:
    return _private->ConvertDoubleToString(double(_private->_float_val));

  case Types::Double:
    return _private->ConvertDoubleToString(_private->_double_val);

  case Types::DoubleArray3:
    return _private->ConvertDoubleArrayToString(3);

  case Types::DoubleArray4:
  case Types::DoubleColor4:
    return _private->ConvertDoubleArrayToString(4);

  case Types::DoubleArray2:
    return _private->ConvertDoubleArrayToString(2);

  case Types::Matrix:
    return _private->ConvertDoubleArrayToString(16);

  case Types::Bool:
    _private->_string_val = _private->_bool_val ? L"true" : L"false";
    // No break...
  case Types::String:
    return _private->_string_val;

  case Types::Uuid:
    ON_UuidToString(_private->_uuid_val, _private->_string_val);
    _private->_string_val.MakeUpperOrdinal();
    return _private->_string_val;

  case Types::Time:
    _private->_string_val = TimeToString(_private->_time_val);
    return _private->_string_val;

  case Types::Buffer:
    {
      _private->_string_val = wszBase64Prefix;
      auto& buffer = GetBuffer();
      const auto buf_size = buffer.Size();
      auto* buf = new char[size_t(buf_size)];
      buffer.Read(buf_size, buf);
      ON_Base64::Encode(buf, size_t(buf_size), _private->_string_val, true);
      delete[] buf;
      return _private->_string_val;
    }
  
  case Types::Null:
  default:
    break;
  }

  return L"";
}

ON_XMLVariant::operator double() const
{
  return AsDouble();
}

ON_XMLVariant::operator float() const
{
  return AsFloat();
}

ON_XMLVariant::operator int() const
{
  return AsInteger();
}

ON_XMLVariant::operator ON_wString() const
{
  return AsString();
}

ON_XMLVariant::operator bool() const
{
  return AsBool();
}

ON_XMLVariant::operator ON_UUID() const
{
  return AsUuid();
}

ON_XMLVariant::operator ON_2dPoint() const
{
  return As2dPoint();
}

ON_XMLVariant::operator ON_3dPoint() const
{
  return As3dPoint();
}

ON_XMLVariant::operator ON_4dPoint() const
{
  return As4dPoint();
}

ON_XMLVariant::operator ON_4fColor() const
{
  return AsColor();
}

ON_XMLVariant::operator time_t() const
{
  return AsTime();
}

ON_XMLVariant::operator ON_Buffer() const
{
  return AsBuffer();
}

void ON_XMLVariant::StringToPoint(int numValues) const
{
  // 22nd September 2022 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-77182
  // This function crashed on the Mac inside wcstod_l() which must be getting called from the call to
  // ON_wtof(). The only way that function can fail is if either the input pointers are invalid or the
  // input string or locale is corrupted. I don't have any control over the locale (I don't even know
  // how it's being accessed on the Mac), so all I can do is check the input string. It's unlikely that
  // an incorrectly formatted string (i.e., not a float) would cause a crash, but I can do some simple
  // validation to try and avoid trouble.

  bool good = true;

  if ((numValues < 0) || (numValues > _private->array_val_max))
  {
    good = false;
  }
  else
  if (_private->_string_val.IsEmpty())
  {
    good = false;
  }

  if (good)
  {
    ON_wString s = _private->_string_val + L",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,";

    auto* p = static_cast<const wchar_t*>(s);
    for (int i = 0; i < numValues; i++)
    {
      // Skip white space. iswspace() returns 0 for the terminator so we can't go off the end of the buffer.
      while (0 != iswspace(*p))
      {
        p++;
      }

      // Quick and simple sanity check at the start of a float value.
      if (isdigit(*p) || (*p == '.') || (*p == '+') || (*p == '-'))
      {
        _private->_array_val[i] = ON_wtof(p);
      }

      // Because we've appended a fixed string containing commas, we know the pointer can't go off
      // the end of the buffer while checking for a comma.
      while (*p != L',')
      {
        p++;
      }

      // 'p' is now pointing to a comma.
      ON_ASSERT(*p == L',');

      // After incrementing it, the worst case scenario is that it's pointing to the terminator.
      p++;
    }
  }
  else
  {
    // Bad input; clear the result to all zeroes.
    for (int i = 0; i < _private->array_val_max; i++)
    {
      _private->_array_val[i] = 0.0;
    }
  }
}

ON_XMLVariant::Types ON_XMLVariant::Type(void) const
{
  return _private->_type;
}

bool ON_XMLVariant::IsNull(void) const
{
  return Types::Null == _private->_type;
}

bool ON_XMLVariant::IsEmpty(void) const
{
  return AsString().IsEmpty() ? true : false;
}

bool ON_XMLVariant::Varies(void) const
{
	return _private->_varies;
}

void ON_XMLVariant::SetVaries(void)
{
  if (IsNull())
  {
    ON_ERROR("Can't set ON_XMLVariant as VARIES when it's NULL");
  }
  else
  {
    _private->_varies = true;
  }
}

ON::LengthUnitSystem ON_XMLVariant::Units(void) const
{
  return _private->_units;
}

void ON_XMLVariant::SetUnits(ON::LengthUnitSystem units)
{
  _private->_units = units;
}

bool ON_XMLVariant::TypePending(void) const
{
  return _private->_type_pending;
}

void ON_XMLVariant::SetTypePendingFlag(bool bTypePending) const
{
  _private->_type_pending = bTypePending;
}

ON_wString ON_XMLVariant::TypeAsString(void) const
{
  switch (_private->_type)
  {
  case Types::Bool:         return L"bool";
  case Types::Integer:      return L"integer";
  case Types::Float:        return L"float";
  case Types::Double:       return L"double";
  case Types::DoubleArray2: return L"2-double-array";
  case Types::DoubleArray3: return L"3-double-array";
  case Types::DoubleArray4: return L"4-double-array";
  case Types::DoubleColor4: return L"color";
  case Types::Matrix:       return L"matrix-4x4";
  case Types::Uuid:         return L"uuid";
  case Types::String:       return L"string";
  case Types::Time:         return L"time";
  case Types::Buffer:       return L"buffer";
  case Types::Null:
  default:
    return L"null";
  }
}

template <typename T>
static ON__UINT32 CRCReal(ON__UINT32 crc, T v)
{
  const auto x = Integerize(v);
  return ON_CRC32(crc, sizeof(x), &x);
}

ON__UINT32 ON_XMLVariant::DataCRC(ON__UINT32 crc) const
{
  switch (Type())
  {
  default:
    return crc;

  case Types::Double:
    return CRCReal(crc, _private->_double_val);

  case Types::Float:
    return CRCReal(crc, _private->_float_val);

  case Types::Integer:
  {
    const auto x = _private->_int_val;
    return ON_CRC32(crc, sizeof(x), &x);
  }

  case Types::DoubleArray2:
  {
    ON__INT64 x[2] = { 0 };
    for (int i = 0; i < 2; i++) x[i] = Integerize(_private->_array_val[i]);
    return ON_CRC32(crc, sizeof(x), &x);
  }

  case Types::DoubleArray3:
  {
    ON__INT64 x[3] = { 0 };
    for (int i = 0; i < 3; i++) x[i] = Integerize(_private->_array_val[i]);
    return ON_CRC32(crc, sizeof(x), &x);
  }

  case Types::DoubleArray4:
  case Types::DoubleColor4:
  {
    ON__INT64 x[4] = { 0 };
    for (int i = 0; i < 4; i++) x[i] = Integerize(_private->_array_val[i]);
    return ON_CRC32(crc, sizeof(x), &x);
  }

  case Types::Matrix:
  {
    int index = 0;
    ON__INT64 x[16] = { 0 };
    for (int j = 0; j < 4; j++)
      for (int i = 0; i < 4; i++)
        x[index++] = Integerize(_private->m_xform.m_xform[i][j]);
    return ON_CRC32(crc, sizeof(x), &x);
  }

  case Types::Bool:
  {
    const auto x = _private->_bool_val;
    return ON_CRC32(crc, sizeof(x), &x);
  }

  case Types::Uuid:
  {
    const auto u = _private->_uuid_val;
    return ON_CRC32(crc, sizeof(u), &u);
  }

  case Types::Time:
  {
    const auto t = _private->_time_val;
    return ON_CRC32(crc, sizeof(t), &t);
  }

  case Types::Buffer:
  {
    return AsBuffer().CRC32(crc);
  }

  case Types::String:
    return AsString().DataCRCLower(crc);
  }
}

void ON_XMLVariant::Format(ON_wString& sOut) const
{
  ON_wString sType;

  switch (_private->_type)
  {
  case Types::Null:
    sOut = "[null]";
    return;

  case Types::Bool:
    sType = L"Bool";
    break;

  case Types::Float:
    sType = L"Float";
    break;

  case Types::Double:
    sType = L"Double";
    break;

  case Types::Integer:
    sType = L"Integer";
    break;

  case Types::DoubleColor4:
    sType = L"DoubleColor4";
    break;

  case Types::DoubleArray2:
    sType = L"DoubleArray2";
    break;

  case Types::DoubleArray3:
    sType = L"DoubleArray3";
    break;

  case Types::DoubleArray4:
    sType = L"DoubleArray4";
    break;

  case Types::String:
    sType = L"String";
    break;

  case Types::Uuid:
    sType = L"UUID";
    break;

  case Types::Matrix:
    sType = L"Matrix";
    break;

  case Types::Time:
    sType = L"Time";
    break;

  case Types::Buffer:
    sType = L"Buffer";
    break;
  }

  sOut.Format(L"Type=%s, Value=%s, Units=%s, CRC=%08X",
              sType.Array(), AsString().Array(), StringFromUnits(Units()), DataCRC(0));
}

// ON_XMLProperty

class CPropertyData final
{
public:
  CPropertyData() { g_lPropertyCount++; }
  CPropertyData(const CPropertyData& src) { g_lPropertyCount++; m_sName = src.m_sName; m_value = src.m_value; }
  CPropertyData(const ON_XMLVariant& v)   { g_lPropertyCount++; m_value = v; }
  CPropertyData(const ON_wString& sName, const ON_XMLVariant& v) { g_lPropertyCount++; SetName(sName); SetValue(v); }
  ~CPropertyData() { ON_ASSERT(m_iRefCount == 0); g_lPropertyCount--; }

public:
  void AddRef(void)
  {
    std::lock_guard<std::recursive_mutex> lg(m_mutex);
    m_iRefCount++;
  }

  void Release(void)
  {
    bool del = false;
    {
      std::lock_guard<std::recursive_mutex> lg(m_mutex);
      del = (0 == --m_iRefCount);
    }

    if (del)
      delete this;
  }

  const ON_wString& Name(void) const { return m_sName; }
  void SetName(const wchar_t* name) { m_sName = name; m_sName.TrimLeft(); m_sName.TrimRight(); }

  ON__UINT32 DataCRC(ON__UINT32 crc) const { return m_value.DataCRC(m_sName.DataCRC(crc)); }

  bool operator < (const CPropertyData& pd) const { return m_sName < pd.m_sName; }

  bool IsDefaultProperty(void) const { return m_sName.IsEmpty(); }

  const ON_XMLVariant& GetValue(void) const { return m_value; }
  void SetValue(const ON_XMLVariant& value) { m_value = value; }

  void SetHugeStringValue(const ON_wString& s);

public:
  ON_wString m_sName;
  ON_XMLVariant m_value;
  int m_iRefCount = 1;
  std::recursive_mutex m_mutex;

protected:
  const CPropertyData& operator = (const CPropertyData& d) { m_sName = d.m_sName; m_value = d.m_value; return *this; }
};

void CPropertyData::SetHugeStringValue(const ON_wString& s)
{
  // Because ON_wString is reference-counted, there is no longer any need to worry about huge string copies.
  m_value.SetValue(s);
}

class ON_XMLPropertyPrivate final
{
public:
  ON_XMLPropertyPrivate();
  ON_XMLPropertyPrivate(const ON_XMLVariant& sValue);
  ON_XMLPropertyPrivate(const ON_wString& sName, const ON_XMLVariant& value);
  ON_XMLPropertyPrivate(const ON_XMLProperty& prop);
  ~ON_XMLPropertyPrivate();

  const ON_wString& Name(void) const { return _data->Name(); }
  void SetName(const wchar_t* wsz) { CopyOnWrite(); _data->SetName(wsz); }

  ON__UINT32 DataCRC(ON__UINT32 crc) const { return _data->DataCRC(crc); }

  bool operator < (const ON_XMLProperty& prop) const;
  void operator = (const ON_XMLPropertyPrivate& pimpl);

  bool IsDefaultProperty(void) const { return _data->IsDefaultProperty(); }
  const ON_XMLVariant& GetValue(void) const { return _data->GetValue(); }
  ON_XMLVariant& GetNonConstValue(void) { CopyOnWrite(); return _data->m_value; }
  void SetValue(const ON_XMLVariant& value) { CopyOnWrite(); _data->SetValue(value); }
  void SetHugeStringValue(const ON_wString& s) { CopyOnWrite(); _data->SetHugeStringValue(s); }
  void CopyOnWrite(void);

  CPropertyData* _data = nullptr;
  ON_XMLNode* _owner = nullptr;
  ON_XMLProperty* _next = nullptr;
};

ON_XMLPropertyPrivate::ON_XMLPropertyPrivate()
{
  _data = new CPropertyData;
}

ON_XMLPropertyPrivate::ON_XMLPropertyPrivate(const ON_XMLVariant& sValue)
{
  _data = new CPropertyData(sValue);
}

ON_XMLPropertyPrivate::ON_XMLPropertyPrivate(const ON_wString& sName, const ON_XMLVariant& value)
{
  _data = new CPropertyData(sName, value);
}

ON_XMLPropertyPrivate::ON_XMLPropertyPrivate(const ON_XMLProperty& prop)
{
  prop._private->_data->AddRef();
  _data = prop._private->_data;
}

ON_XMLPropertyPrivate::~ON_XMLPropertyPrivate()
{
  _data->Release();
}

bool ON_XMLPropertyPrivate::operator < (const ON_XMLProperty& prop) const
{
  return _data->operator < (*prop._private->_data);
}

void ON_XMLPropertyPrivate::operator = (const ON_XMLPropertyPrivate& other)
{
  if (&other == this)
    return;

  ON_ASSERT(nullptr != _data);
  ON_ASSERT(nullptr != other._data);

  other._data->AddRef();
  _data->Release();
  _data = other._data;
}

void ON_XMLPropertyPrivate::CopyOnWrite(void)
{
  if (_data->m_iRefCount > 1)
  {
    auto* pData = new CPropertyData(*_data);
    _data->Release();
    _data = pData;
  }
}

ON_XMLProperty::ON_XMLProperty()
{
  _private = new (_PRIVATE) ON_XMLPropertyPrivate; PRIVATE_CHECK(ON_XMLPropertyPrivate);
}

ON_XMLProperty::ON_XMLProperty(const ON_XMLVariant& sValue)
{
  _private = new (_PRIVATE) ON_XMLPropertyPrivate(sValue); PRIVATE_CHECK(ON_XMLPropertyPrivate);
}

ON_XMLProperty::ON_XMLProperty(const ON_wString& sName, const ON_XMLVariant& value)
{
  _private = new (_PRIVATE) ON_XMLPropertyPrivate(sName, value); PRIVATE_CHECK(ON_XMLPropertyPrivate);
}

ON_XMLProperty::ON_XMLProperty(const ON_XMLProperty& prop)
{
  _private = new (_PRIVATE) ON_XMLPropertyPrivate(prop); PRIVATE_CHECK(ON_XMLPropertyPrivate);
}

ON_XMLProperty::~ON_XMLProperty()
{
  _private->~ON_XMLPropertyPrivate();
  _private = nullptr;
}

const ON_wString& ON_XMLProperty::Name(void) const
{
  return _private->Name();
}

void ON_XMLProperty::SetName(const wchar_t* wsz)
{
  _private->SetName(wsz);
}

ON__UINT32 ON_XMLProperty::DataCRC(ON__UINT32 crc) const
{
  return _private->DataCRC(crc);
}

bool ON_XMLProperty::operator < (const ON_XMLProperty& prop) const
{
  return _private->operator < (prop);
}

const ON_XMLProperty& ON_XMLProperty::operator = (const ON_XMLProperty& prop)
{
  _private->operator = (*prop._private);

  return *this;
}

bool ON_XMLProperty::IsDefaultProperty(void) const
{
  return _private->IsDefaultProperty();
}

const ON_XMLVariant& ON_XMLProperty::GetValue(void) const
{
  return _private->GetValue();
}

void ON_XMLProperty::SetValue(const ON_XMLVariant& v)
{
  _private->SetValue(v);
}

void ON_XMLProperty::SetHugeStringValue(const ON_wString& s)
{
  _private->SetHugeStringValue(s);
}

ON_XMLVariant& ON_XMLProperty::GetNonConstValue(void)
{
  return _private->GetNonConstValue();
}

ON_XMLProperty* ON_XMLProperty::Next(void) const
{
  return _private->_next;
}

void* ON_XMLProperty::EVF(const wchar_t*, void*)
{
  return nullptr;
}

// ON_XMLSegmentedStream

class ON_XMLSegmentedStreamPrivate
{
public:
  ON_SimpleArray<wchar_t*> m_a;
};

ON_XMLSegmentedStream::ON_XMLSegmentedStream()
{
  _private = new ON_XMLSegmentedStreamPrivate;
}

ON_XMLSegmentedStream::~ON_XMLSegmentedStream()
{
  for (int i = 0; i < _private->m_a.Count(); i++)
  {
    delete[] _private->m_a[i];
  }

  delete _private;
}

int ON_XMLSegmentedStream::Count(void) const
{
  return _private->m_a.Count();
}

void ON_XMLSegmentedStream::Append(wchar_t* wsz)
{
  _private->m_a.Append(wsz);
}

wchar_t* ON_XMLSegmentedStream::Segment(int index) const
{
  if ((index < 0) || (index >= _private->m_a.Count()))
    return nullptr;

  return _private->m_a[index];
}

void* ON_XMLSegmentedStream::EVF(const wchar_t*, void*)
{
  return nullptr;
}

// ON_XMLNode

static int g_iWarningsFlagCounter = 0;

class CWarningHelper final
{
public:
  CWarningHelper(bool b) : m_bWarningsAsErrors(b) { if (m_bWarningsAsErrors) g_iWarningsFlagCounter++; }
  ~CWarningHelper()                               { if (m_bWarningsAsErrors) g_iWarningsFlagCounter--; }

private:
  bool m_bWarningsAsErrors;
};

class ON_XMLNodePrivate final
{
public:
  ON_XMLNodePrivate(ON_XMLNode& n) : m_node(n) { g_lNodeCount++; }

  ~ON_XMLNodePrivate()
  {
    RemoveAllProperties();
    RemoveAllChildren();
    --g_lNodeCount;
  }

  bool GetPropertiesFromTag(const ON_wString& sTag);
  bool IsClosingTag(const ON_wString& sTag) const;
  ON_XMLNode* GetNodeAtPath(const wchar_t* wszPath, bool bCreate);
  ON_XMLProperty* AddProperty(const ON_XMLProperty& prop, bool add_to_end = false);
  void AddEmptyDefaultProperty(void);
  ON_XMLProperty* AttachProperty(ON_XMLProperty* pProp);
  bool RemoveProperty(const wchar_t* name);
  ON_XMLNode* DetachChild(ON_XMLNode& child);
  void RemoveAllProperties(void);
  const ON_XMLNode& TopLevel(void) const;
  ON_XMLNode* AttachChildNode(ON_XMLNode* pNode);
  void RemoveAllChildren(void);
  const ON_wString& TagName(void) const;
  void SetTagName(const wchar_t* name);
  ON_XMLNode* PrevSibling(void) const;
  void MoveBefore(ON_XMLNode& other);
  void MoveAfter(ON_XMLNode& other);
  bool RecurseChildren(ON_XMLRecurseChildrenCallback callback, void* pv) const;
  ON__UINT32 DataCRC(ON__UINT32 crc, bool recursive) const;

  static bool AssertValidTag(const ON_wString& sTag);
  static void AttemptToFixTag(ON_wString& tag);
  static bool RecoverProperty(const ON_wString& tag, int iEqualSign, ON_wString& sProp);
  static bool GetNextTag(ON_wString& tag, wchar_t*& pBuffer, bool bValidateTag);
  static ON_wString GetNameFromTag(const wchar_t* wszTag);
  static bool IsValidXMLNameWithDebugging(const wchar_t* name);
  static bool IsValidXMLName(const wchar_t* name);

  static bool m_bAutoTypePropValue;

  ON_XMLNode& m_node;
  ON_wString  m_name;
  ON_XMLNode* m_next_sibling = nullptr;
  ON_XMLNode* m_parent = nullptr;
  ON_XMLNode* m_first_child = nullptr;
  ON_XMLNode* m_last_child = nullptr;
  ON_XMLProperty* m_first_property = nullptr;
  void* m_last_read_buf_ptr = nullptr;
  mutable std::recursive_mutex m_mutex;
  bool m_debug_auto_test_read = true;
};

bool ON_XMLNodePrivate::m_bAutoTypePropValue = false;

ON_wString ON_XMLNodePrivate::GetNameFromTag(const wchar_t* wszTag) // Static.
{
  ON_wString name = wszTag;
  name.TrimLeft(L"</ ");
  name.TrimRight(L">/ ");

  const int pos = name.Find(L' ');
  if (pos >= 0)
  {
    name.SetLength(pos);
  }

  return name;
}

bool ON_XMLNodePrivate::IsValidXMLNameWithDebugging(const wchar_t* tag_name) // Static.
{
  if (IsValidXMLName(tag_name))
    return true;

  OUTPUT_DEBUG_STRING(L"Invalid XML tag syntax - ");
  OUTPUT_DEBUG_STRING_EOL(tag_name);

  ON_ASSERT(false);

  return false;
}

bool ON_XMLNodePrivate::IsValidXMLName(const wchar_t* wszTagName) // Static.
{
  // https://www.xml.com/pub/a/2001/07/25/namingparts.html
  //
  // A 'Name' is a token beginning with a letter or one of a few punctuation characters, and continuing with
  // letters, digits, hyphens, underscores, colons, or full stops, together known as name characters.
  // This definition is formally expressed in Extended Backus-Naur Form (EBNF) notation as follows:
  // 
  //  NameChar ::=  Letter | Digit | '.' | '-' | '_' | ':' | CombiningChar | Extender
  //  Name     ::= (Letter | '_' | ':') (NameChar)*

  // We also simplify as follows:
  //
  // - ':' is not actually allowed in tags, it's reserved for XML namespaces, so we disallow it.
  // - 'Letter' must be an ASCII letter: Letter ::= 'a' to 'z' or 'A' to 'Z'.
  // - 'Digit'  must be an ASCII digit:  Digit  ::= '0' to '9'.
  // - 'CombiningChar' and 'Extender' are not supported (disallowed).

  const ON_wString sTagName = wszTagName;
  if (sTagName.IsEmpty())
    return false;

  bool bad = false;

  const int len = sTagName.Length();
  for (int i = 0; i < len; i++)
  {
    const auto& ch = sTagName[i];

    if ((ch >= L'a') && (ch <= L'z'))
      continue;

    if ((ch >= L'A') && (ch <= L'Z'))
      continue;

    if (ch == L'_')
      continue;

    if (i > 0)
    {
      if ((ch >= L'0') && (ch <= L'9'))
        continue;

      if ((ch == '-') || (ch == '.'))
        continue;
    }

    bad = true;
  }

  if (bad)
  {
    return false;
  }

  return true;
}

static const wchar_t* StringFromPropType(ON_XMLVariant::Types vt)
{
  switch (vt)
  {
  case ON_XMLVariant::Types::Integer:      return L"int";
  case ON_XMLVariant::Types::Float:        return L"float";
  case ON_XMLVariant::Types::Double:       return L"double";
  case ON_XMLVariant::Types::String:       return L"string";
  case ON_XMLVariant::Types::Bool:         return L"bool";
  case ON_XMLVariant::Types::Matrix:       return L"matrix";
  case ON_XMLVariant::Types::Uuid:         return L"uuid";
  case ON_XMLVariant::Types::Time:         return L"time";
  case ON_XMLVariant::Types::Buffer:       return L"buffer";
  case ON_XMLVariant::Types::DoubleColor4: return L"color";
  case ON_XMLVariant::Types::DoubleArray2: return L"2da";
  case ON_XMLVariant::Types::DoubleArray3: return L"3da";
  case ON_XMLVariant::Types::DoubleArray4: return L"4da";
  case ON_XMLVariant::Types::Null:
  default:
    return L"null";
  }
}

ON__UINT32 ON_XMLNodePrivate::DataCRC(ON__UINT32 crc, bool recursive) const
{
  crc = TagName().DataCRCLower(crc);

  auto pit = m_node.GetPropertyIterator();
  ON_XMLProperty* prop = nullptr;
  while (nullptr != (prop = pit.GetNextProperty()))
  {
    crc = prop->DataCRC(crc);
  }

  if (recursive)
  {
    auto cit = m_node.GetChildIterator();
    ON_XMLNode* child = nullptr;
    while (nullptr != (child = cit.GetNextChild()))
    {
      crc = child->_private->DataCRC(crc, recursive);
    }
  }

  return crc;
}

const ON_wString& ON_XMLNodePrivate::TagName(void) const
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  return m_name;
}

void ON_XMLNodePrivate::SetTagName(const wchar_t* name)
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  m_name = name;
  m_name.TrimLeft();
  m_name.TrimRight();
}

const ON_XMLNode& ON_XMLNodePrivate::TopLevel(void) const
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  const auto* pNode = &m_node;
  while (nullptr != pNode->_private->m_parent)
  {
    pNode = pNode->_private->m_parent;
  }

  return *pNode;
}

ON_XMLNode* ON_XMLNodePrivate::AttachChildNode(ON_XMLNode* pNode)
{
  if (nullptr == pNode)
    return nullptr;

  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  if (nullptr == m_last_child)
  {
    // There are no children - add one.
    m_last_child = m_first_child = pNode;
  }
  else
  {
    // There are children - add one to the end.
    m_last_child->_private->m_next_sibling = pNode;
    m_last_child = pNode;
  }

  pNode->_private->m_next_sibling = nullptr;
  pNode->_private->m_parent = &m_node;

  return pNode;
}

void ON_XMLNodePrivate::AddEmptyDefaultProperty(void)
{
  AddProperty(ON_XMLProperty(L""));
}

void ON_XMLNodePrivate::RemoveAllChildren(void)
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  if (nullptr == m_first_child)
    return;

  auto* pNode = m_first_child;
  while (nullptr != pNode)
  {
    auto* pDelete = pNode;
    pNode = pNode->NextSibling();
    delete pDelete;
  }

  m_first_child = nullptr;
  m_last_child = nullptr;
}

ON_XMLNode* ON_XMLNodePrivate::DetachChild(ON_XMLNode& child)
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  if (child._private->m_parent != &m_node)
    return nullptr;

  ON_XMLNode* pChild = nullptr;

  auto* pChildNextSibling = child._private->m_next_sibling;

  if (m_first_child == &child)
  {
    if (m_last_child == m_first_child)
      m_last_child = pChildNextSibling;

    m_first_child = pChildNextSibling;

    pChild = &child;
  }
  else
  {
    auto* pNode = m_first_child;
    while (nullptr != pNode)
    {
      if (pNode->_private->m_next_sibling == &child)
      {
        pNode->_private->m_next_sibling = pChildNextSibling;

        if (nullptr == pChildNextSibling)
          m_last_child = pNode;

        pChild = &child;
        break;
      }

      pNode = pNode->_private->m_next_sibling;
    }
  }

  if (nullptr != pChild)
  {
    pChild->_private->m_parent = nullptr;
    pChild->_private->m_next_sibling = nullptr;
  }

  return pChild;
}

ON_XMLNode* ON_XMLNodePrivate::PrevSibling(void) const
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  auto* pPrev = m_parent->_private->m_first_child;
  if (pPrev == &m_node)
    return nullptr;

  while (pPrev->_private->m_next_sibling != &m_node)
  {
    pPrev = pPrev->_private->m_next_sibling;
  }

  return pPrev;
}

void ON_XMLNodePrivate::MoveBefore(ON_XMLNode& other)
{
  if (&other == &m_node)
    return;

  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  auto* pBeforeOther = other.PrevSibling();
  if (pBeforeOther == &m_node)
    return;

  auto* pPrev = PrevSibling();
  if (nullptr != pPrev)
  {
    pPrev->_private->m_next_sibling = m_next_sibling;
  }
  else
  {
    // 'this' was the head; redirect the parent's first child.
    m_parent->_private->m_first_child = m_next_sibling;
  }

  m_next_sibling = &other;

  if (nullptr == pBeforeOther)
  {
    // 'other' was the head; redirect the parent's first child.
    m_parent->_private->m_first_child = &m_node;
  }
  else
  {
    pBeforeOther->_private->m_next_sibling = &m_node;
  }

  // 13th February 2025 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-86050
  if (m_parent->_private->m_last_child == &m_node)
  {
    // 'this' was the tail; redirect the parent's last child.
    m_parent->_private->m_last_child = pPrev;
  }
}

void ON_XMLNodePrivate::MoveAfter(ON_XMLNode& other)
{
  if (&other == &m_node)
    return;

  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  auto* pPrev = PrevSibling();
  if (pPrev == &other)
    return;

  if (nullptr != pPrev)
  {
    pPrev->_private->m_next_sibling = m_next_sibling;
  }
  else
  {
    // 'this' was the head; redirect the parent's first child.
    m_parent->_private->m_first_child = m_next_sibling;
  }

  // 13th February 2025 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-86050
  if (m_parent->_private->m_last_child == &m_node)
  {
    // 'this' was the tail; redirect the parent's last child.
    m_parent->_private->m_last_child = pPrev;
  }

  m_next_sibling = other._private->m_next_sibling;

  other._private->m_next_sibling = &m_node;
}

bool ON_XMLNodePrivate::RecurseChildren(ON_XMLRecurseChildrenCallback callback, void* pv) const
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  auto it = m_node.GetChildIterator();

  ON_XMLNode* pChild = nullptr;
  while (nullptr != (pChild = it.GetNextChild()))
  {
    if (!callback(pChild, pv))
      return false;

    if (!pChild->RecurseChildren(callback, pv))
      return false;
  }

  return true;
}

ON_XMLProperty* ON_XMLNodePrivate::AddProperty(const ON_XMLProperty& prop, bool add_to_end)
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  auto* prop_copy = new ON_XMLProperty(prop);
  prop_copy->_private->_owner = &m_node;

  if (!add_to_end || nullptr == m_first_property)
  {
    prop_copy->_private->_next = m_first_property;
    m_first_property = prop_copy;
  }
  else
  {
    auto last = m_first_property;
    prop_copy->_private->_next = nullptr;

    //Spin to the end.
    while (auto n = last->Next())
    {
      last = n;
    }

    ON_ASSERT(nullptr != last);
    ON_ASSERT(nullptr == last->Next());

    last->_private->_next = prop_copy;
  }

  return prop_copy;
}

ON_XMLProperty* ON_XMLNodePrivate::AttachProperty(ON_XMLProperty* prop)
{
  if (nullptr == prop)
    return nullptr;

  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  RemoveProperty(prop->Name());

  prop->_private->_next = m_first_property;
  m_first_property = prop;
  m_first_property->_private->_owner = &m_node;

  return prop;
}

bool ON_XMLNodePrivate::RemoveProperty(const wchar_t* name)
{
  ON_XMLProperty* pPrev = nullptr;

  auto* pProp = m_first_property;
  while (nullptr != pProp)
  {
    if (pProp->Name().CompareNoCase(name) == 0)
    {
      if (nullptr == pPrev)
      {
        m_first_property = pProp->Next();
      }
      else
      {
        pPrev->_private->_next = pProp->Next();
      }

      delete pProp;
      return true;
    }

    pPrev = pProp;
    pProp = pProp->_private->_next;
  }

  return false;
}

void ON_XMLNodePrivate::RemoveAllProperties(void)
{
  if (nullptr == m_first_property)
    return;

  auto* pProp = m_first_property;
  while (nullptr != pProp)
  {
    auto* pDelete = pProp;
    pProp = pProp->Next();
    delete pDelete;
  }

  m_first_property = nullptr;
}

ON_XMLNode* ON_XMLNodePrivate::GetNodeAtPath(const wchar_t* wszPath, bool bCreate)
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  // Forward slash "/" is the separator.

  if (nullptr == wszPath)
    return &m_node;

  const wchar_t* p = wszPath;
  while (*p != 0)
  {
    if (!iswspace(*p) && *p != L'/')
      break;
    p++;
  }

  if (*p == 0)
    return &m_node; // The input string was empty.

  constexpr int maxBuf = 260;
  wchar_t wsz[maxBuf+1];
  wcsncpy(wsz, p, maxBuf);
  wsz[maxBuf] = 0;

  // Now right trim out the white space.
  const int iLength = (int)wcslen(wsz);

  for (int i = iLength - 1; i >= 0; i--)
  {
    if (iswspace(wsz[i]))
      wsz[i] = 0;
    else
      break;
  }

  // Check for a resultant empty string.
  if (*wsz == 0)
    return &m_node;

  const wchar_t* pNext = nullptr;
  const wchar_t* pstr = wcschr(wsz, L'/');

  const int pos = (pstr != nullptr) ? (int)(pstr - wsz) : -1;
  if (-1 != pos)
  {
    // sNext is the rest of the string that we're going to recurse through.
    pNext = wsz + pos + 1;
    wsz[pos] = 0;
  }

  auto it = m_node.GetChildIterator();
  ON_XMLNode* pChild = nullptr;
  while (nullptr != (pChild = it.GetNextChild()))
  {
    if (on_wcsicmp(wsz, pChild->TagName()) == 0)
    {
      return pChild->_private->GetNodeAtPath(pNext, bCreate);
    }
  }

  // The child was not found.
  if (bCreate)
  {
    return AttachChildNode(new ON_XMLNode(wsz))->_private->GetNodeAtPath(pNext, bCreate);
  }

  return nullptr;
}

bool ON_XMLNodePrivate::RecoverProperty(const ON_wString& tag, int equalSign, ON_wString& sProp) // Static.
{
  // Move left, looking for a space and ensuring every character is a valid name char.
  ON_ASSERT(tag[equalSign] == L'=');

  ON_wString sName;
  int leftScan = equalSign - 1;
  while (leftScan > 0 && tag[leftScan] != L' ')
  {
    sName = ON_wString(tag[leftScan--]) + sName;
  }

  if (!IsValidXMLNameWithDebugging(sName) || sName.IsEmpty())
    return false;

  // Now try to recover the value.
  const int start = equalSign + 2;
  if (start >= tag.Length())
    return false;

  if (tag[equalSign + 1] != L'\"')
    return false;

  const int secondQuote = tag.Find(L'\"', start);
  if (secondQuote == -1)
    return false;

  ON_wString sValue = tag.Mid(start, secondQuote - start);
  EncodeXML(sValue);

  sProp = sName + L"=\"" + sValue + L"\"";

  return true;
}

void ON_XMLNodePrivate::AttemptToFixTag(ON_wString& tag) // Static.
{
  // We're going to rebuild the tag from the name and the number of valid properties we find.
  const ON_wString sName = GetNameFromTag(tag);
  if (sName.IsEmpty() || tag.Length() < 2)
    return;

  const bool bSelfClosingTag = (0 == wcscmp(tag.Right(2), L"/>"));

  ON_wString sNewTag = ON_wString(L"<") + sName;

  // Now find all of the potential properties - looking for = signs.
  int pos = 0;
  int equalSign = -1;
  ON_wString sProp;

  while ((equalSign = tag.Find(L'=', pos)) >= 0)
  {
    // Move the search past this one for next time around.
    pos = equalSign + 1;

    if (RecoverProperty(tag, equalSign, sProp))
    {
      sNewTag += L" ";
      sNewTag += sProp;
    }
  }

  if (bSelfClosingTag)
  {
    sNewTag += L"/>";
  }
  else
  {
    sNewTag += L">";
  }

  tag = sNewTag;
}

bool ON_XMLNodePrivate::GetNextTag(ON_wString& tag, wchar_t*& pBuffer, bool bValidateTag) // Static.
{
  auto* start = pBuffer;
  while (*start != L'<')
  {
    if (0 == *start)
    {
      OUTPUT_DEBUG_STRING_EOL(L"Start of tag '<' not found");
      return false;
    }

    start++;
  }

  while (start[1] == L'?')
  {
    // This is a nasty document description tag - need to look for the end tag and skip it.
    while (!(start[0] == L'?' && start[1] == L'>'))
    {
      if (0 == *start)
      {
        OUTPUT_DEBUG_STRING_EOL(L"End of document description tag '>' not found");
        return false;
      }

      start++;
    }

    while (*start != L'<')
    {
      start++;
    }
  }

  while ((start[1] == L'!') && (start[2] == L'-') && (start[3] == L'-'))
  {
    // This is a comment tag - need to look for the end tag and skip it.
    while (!(start[0] == L'-' && start[1] == L'-' && start[2] == L'>'))
    {
      if (0 == *start)
      {
        OUTPUT_DEBUG_STRING_EOL(L"End of comment tag '>' not found");
        return false;
      }

      start++;
    }

    while (*start != L'<')
    {
      start++;
    }
  }

  wchar_t* pEnd = start;
  while (*pEnd != L'>')
  {
    if (0 == *pEnd)
    {
      OUTPUT_DEBUG_STRING_EOL(L"End of tag '>' not found");
      return false;
    }

    pEnd++;
  }

  pBuffer = pEnd + 1;

  // Copy the tag into the ready-made string.
  const auto numChars = int(pEnd - start + 1);
  if (numChars < 2)
    return false;

  tag.Set(start, numChars);

  if (bValidateTag)
  {
    if (!AssertValidTag(tag))
    {
      AttemptToFixTag(tag);
      AssertValidTag(tag);
    }
  }

  return true;
}

bool ON_XMLNodePrivate::AssertValidTag(const ON_wString& tag) // Static.
{
  // Check for an even number of quotes - odd means there are quotes in the strings.
  const int quoteCount = tag.Count(L'\"');

  if ((quoteCount % 2) != 0)
  {
    // Odd number of quotes; fail.
    OUTPUT_DEBUG_STRING_EOL(L"Odd number of quotes");
    return false;
  }

  if (tag.Count(L'<') != tag.Count(L'>'))
  {
    OUTPUT_DEBUG_STRING_EOL(L"Bad tag format; even on nested tags, < and > should be equal");
    return false;
  }

  // Check for lone ampersands.
  int pos = 0;
  int find = -1;
  do
  {
    find = tag.Find(L'&', pos);
    if (find >= 0)
    {
      pos = find + 1;
      const int semicolon = tag.Find(L';', find);
      if (semicolon < 0)
      {
        OUTPUT_DEBUG_STRING_EOL(L"Unterminated entity reference");
        return false;
      }

      const auto sEsc = tag.Mid(pos - 1, semicolon - pos + 2);
      if (!sEsc.IsXMLSpecialCharacterEncoding())
      {
        OUTPUT_DEBUG_STRING_EOL(L"Malformed tag on read");
        return false;
      }
    }
  }
  while (find >= 0);

  return true;
}

ON_XMLNode::ON_XMLNode(const wchar_t* name)
{
  _private = new (_PRIVATE) ON_XMLNodePrivate(*this); PRIVATE_CHECK(ON_XMLNodePrivate);

  SetTagName(name);

  _private->AddEmptyDefaultProperty();
}

ON_XMLNode::ON_XMLNode(const ON_XMLNode& src)
{
  _private = new (_PRIVATE) ON_XMLNodePrivate(*this); PRIVATE_CHECK(ON_XMLNodePrivate);
  *this = src;
}

ON_XMLNode::~ON_XMLNode()
{
  _private->~ON_XMLNodePrivate();
  _private = nullptr;
}

const ON_XMLNode& ON_XMLNode::operator = (const ON_XMLNode& src)
{
  if (this == &src)
    return *this;

  std::lock_guard<std::recursive_mutex> lg1(_private->m_mutex);
  std::lock_guard<std::recursive_mutex> lg2(src._private->m_mutex);

  _private->RemoveAllProperties();
  _private->RemoveAllChildren();

  _private->m_name = src._private->m_name;

  // Copy in the properties.
  ON_XMLProperty* pProperty = nullptr;
  auto pi = src.GetPropertyIterator();
  while (nullptr != (pProperty = pi.GetNextProperty()))
  {
    _private->AddProperty(*pProperty, true);  //Add it to the end so that the order stays the same.
  }

  // Copy in the children.
  ON_XMLNode* pChild = nullptr;
  auto ci = src.GetChildIterator();
  while (nullptr != (pChild = ci.GetNextChild()))
  {
    AttachChildNode(new ON_XMLNode(*pChild));
  }

  return *this;
}

bool ON_XMLNode::operator == (const ON_XMLNode& other) const
{
  ON_XMLProperty* prop_other = nullptr;
  auto pio = other.GetPropertyIterator();
  while (nullptr != (prop_other = pio.GetNextProperty()))
  {
    auto* prop_this = GetNamedProperty(prop_other->Name());
    if (nullptr == prop_this)
      return false;

    if (!(prop_this->GetValue() == prop_other->GetValue()))
      return false;
  }

  ON_XMLNode* child_other = nullptr;
  auto cio = other.GetChildIterator();
  while (nullptr != (child_other = cio.GetNextChild()))
  {
    auto* child_this = GetNamedChild(child_other->TagName());
    if (nullptr == child_this)
      return false;

    if (!(*child_this == *child_other))
      return false;
  }

  return true;
}

bool ON_XMLNode::operator != (const ON_XMLNode& node) const
{
    return !(operator == (node));
}

bool ON_XMLNode::AutoTypePropValue(void)
{
  return ON_XMLNodePrivate::m_bAutoTypePropValue;
}

void ON_XMLNode::SetAutoTypePropValue(bool b)
{
  ON_XMLNodePrivate::m_bAutoTypePropValue = b;
}

bool ON_XMLNode::MergeFrom(const ON_XMLNode& src)
{
  std::lock_guard<std::recursive_mutex> lg1(_private->m_mutex);
  std::lock_guard<std::recursive_mutex> lg2(src._private->m_mutex);

  if (_private->m_name != src.TagName())
    return false;

  // Copy in the parameters.
  ON_XMLProperty* pProperty = nullptr;

  auto pi = src.GetPropertyIterator();
  while (nullptr != (pProperty = pi.GetNextProperty()))
  {
    // Replaces any that are already there.
    SetProperty(*pProperty);
  }

  // Copy in the children.
  const auto bNeedToMerge = ChildCount() != 0;

  ON_XMLNode* pChild = nullptr;
  auto ci = src.GetChildIterator();
  while (nullptr != (pChild = ci.GetNextChild()))
  {
    auto* pLocalChildNode = bNeedToMerge ? GetNodeAtPath(pChild->TagName()) : nullptr;
    if (nullptr != pLocalChildNode)
    {
      pLocalChildNode->MergeFrom(*pChild);
    }
    else
    {
      AttachChildNode(new ON_XMLNode(*pChild));
    }
  }

  return true;
}

void ON_XMLNode::Clear(void)
{
  SetTagName(L"");
  RemoveAllProperties();
  RemoveAllChildren();
}

void ON_XMLNode::RemoveAllChildren(void)
{
  _private->RemoveAllChildren();
}

void ON_XMLNode::RemoveAllProperties(void)
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  _private->RemoveAllProperties();
  _private->AddEmptyDefaultProperty();
}

ON_XMLProperty* ON_XMLNode::SetProperty(const ON_XMLProperty& prop)
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  if (g_iWarningsFlagCounter > 0)
  {
    if (prop.Name().Contains(L"\n") || prop.Name().Contains(L"\r"))
    {
      // The name string contain LF or CR codes - this is likely to cause problems but is still valid XML.
      ON_ASSERT(false);
    }

    const ON_wString sValue = prop.GetValue().AsString();
    if (sValue.Contains(L"\n") || sValue.Contains(L"\r"))
    {
      // The value string contain LF or CR codes - this is likely to cause problems but is still valid XML.
      ON_ASSERT(false);
    }
  }

  _private->RemoveProperty(prop.Name());

  // Copy the property, then add it to the tree.
  return _private->AddProperty(prop);
}

const ON_wString& ON_XMLNode::TagName(void) const
{
  return _private->TagName();
}

void ON_XMLNode::SetTagName(const wchar_t* name)
{
  _private->SetTagName(name);
}

ON_XMLNode* ON_XMLNode::Parent(void) const
{
  return _private->m_parent;
}

const ON_XMLNode& ON_XMLNode::TopLevel(void) const
{
  return _private->TopLevel();
}

ON_XMLNode* ON_XMLNode::AttachChildNode(ON_XMLNode* pNode)
{
  return _private->AttachChildNode(pNode);
}

ON_XMLProperty* ON_XMLNode::AttachProperty(ON_XMLProperty* pProp)
{
  return _private->AttachProperty(pProp);
}

bool ON_XMLNode::RemoveProperty(const wchar_t* wszPropertyName)
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  return _private->RemoveProperty(wszPropertyName);
}

void ON_XMLNode::Remove(void)
{
  auto* pParent = Parent();
  if (nullptr != pParent)
  {
    pParent->RemoveChild(this);
  }
  else
  {
    delete this;
  }
}

ON_XMLNode* ON_XMLNode::DetachChild(ON_XMLNode& child)
{
  return _private->DetachChild(child);
}

bool ON_XMLNode::RemoveChild(ON_XMLNode* child)
{
  if (nullptr == child)
    return false;

  ON_XMLNode* detach = _private->DetachChild(*child);
  if (nullptr != detach)
  {
    delete detach;
    return true;
  }

  return false;
}

ON_XMLNode::ChildIterator ON_XMLNode::GetChildIterator(void) const
{
  return ChildIterator(this);
}

ON_XMLNode::PropertyIterator ON_XMLNode::GetPropertyIterator(bool bAlphabetized) const
{
  return PropertyIterator(this, bAlphabetized);
}

int ON_XMLNode::PropertyCount(void) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  int count = 0;
  auto it = GetPropertyIterator();
  while (it.GetNextProperty())
  {
    count++;
  }

  return count;
}

int ON_XMLNode::ChildCount(void) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  int count = 0;
  auto it = GetChildIterator();
  while (it.GetNextChild())
  {
    count++;
  }

  return count;
}

int ON_XMLNode::GetNestedDepth(void) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  int depth = 0;

  const auto* pNode = this;
  while (nullptr != pNode->_private->m_parent)
  {
    pNode = pNode->_private->m_parent;
    depth++;
  }

  return depth;
}

static bool PrependNodeToStringAndRecurseParents(const ON_XMLNode* pNode, ON_wString& s)
{
  // Recursive function to pile up the path.

  if (nullptr == pNode)
    return false;

  auto* pParent = pNode->Parent();
  if (nullptr == pParent)
    return false;

  s.Insert(0, L'/', 1);
  s.Insert(0, pNode->TagName());

  PrependNodeToStringAndRecurseParents(pParent, s);

  return true;
}

ON_wString ON_XMLNode::GetPathFromRoot(void) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  ON_wString sPath = TagName();
  PrependNodeToStringAndRecurseParents(Parent(), sPath);

  return sPath;
}

ON_XMLProperty& ON_XMLNode::GetDefaultProperty(void) const
{
  auto* pProp = GetNamedProperty(L"");

  ON_ASSERT(nullptr != pProp); // Always created by constructor.

  return *pProp;
}

ON_XMLProperty* ON_XMLNode::GetNamedProperty(const wchar_t* name) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  auto it = GetPropertyIterator();
  ON_XMLProperty* pProp = nullptr;

  while (nullptr != (pProp = it.GetNextProperty()))
  {
    if (on_wcsicmp(name, pProp->Name()) == 0)
      return pProp;
  }

  return nullptr;
}

ON_XMLNode* ON_XMLNode::GetNamedChild(const wchar_t* name) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  ON_XMLNode* node = nullptr;

  auto it = GetChildIterator();
  while (nullptr != (node = it.GetNextChild()))
  {
    if (on_wcsicmp(name, node->TagName()) == 0)
      return node;
  }

  return nullptr;
}

void* ON_XMLNode::LastReadBufferPointer(void) const
{
  return _private->m_last_read_buf_ptr;
}

bool ON_XMLNodePrivate::GetPropertiesFromTag(const ON_wString& sTag)
{
  SetTagName(GetNameFromTag(sTag));

  ON_wString tag(sTag);
  tag.TrimLeft(L"</ ");
  tag.TrimRight(L">/ ");

  int pos1 = tag.Find(L' ');
  if (pos1 < 0)
    return true; // No properties.

  tag.TruncateMid(pos1 + 1);

  ON_wString sPropertyName, sPropertyValue;
  ON_XMLVariant vValue;

  // We are now at the start of the properties.
  bool bClear = false;

  while (!tag.IsEmpty())
  {
    pos1 = tag.Find(L'=');
    if (pos1 >= 0)
    {
      sPropertyName = tag.Left(pos1);
      sPropertyName.TrimLeft();

      tag.TruncateMid(pos1);

      pos1 = tag.Find(L'\"');
      if (pos1 >= 0)
      {
        tag.TruncateMid(pos1 + 1);
        pos1 = tag.Find(L'\"');
        if (pos1 >= 0)
        {
          sPropertyValue = tag.Left(pos1);
          tag.TruncateMid(pos1 + 1);
          tag.TrimLeft();
          DecodeXML(sPropertyValue);

          const int pos2 = m_bAutoTypePropValue ? sPropertyValue.Find(L':') : -1;
          if (pos2 > 0)
          {
            vValue = sPropertyValue.Mid(pos2 + 1);
            vValue.SetTypePendingFlag(true);
          }
          else
          {
            // This allows for lazy typing of the property.
            vValue.SetTypePendingFlag(true);
            vValue = sPropertyValue;
          }

          AttachProperty(new ON_XMLProperty(sPropertyName, vValue));

          bClear = true;
        }
      }
    }

    if (!bClear)
    {
      ON_ERROR("GetPropertiesFromTag failed");
      return false;
    }

    bClear = false;

    tag.TrimLeft();
  }

  return true;
}

bool ON_XMLNodePrivate::IsClosingTag(const ON_wString& sTag) const
{
  if (sTag.Length() < 3)
    return false;

  if (sTag[0] != L'<')
    return false;

  if (sTag[1] != L'/')
    return false;

  if (GetNameFromTag(sTag).CompareNoCase(TagName()) == 0)
    return true;

  return false;
}

ON_XMLNode::operator ON_wString() const
{
  return String();
}

ON_wString ON_XMLNode::String(bool includeFormatting, bool forceLongFormat, bool sortedProperties) const
{
  // Pretend to write the node to get the buffer size that needs to be allocated.
  const auto numChars = WriteToStream(nullptr, 0, includeFormatting, forceLongFormat, sortedProperties);

  // Create a buffer of that size inside a string.
  ON_wString s;
  auto* pBuffer = s.SetLength(numChars);
  if (nullptr != pBuffer)
  {
    // Now really write the node to the created buffer.
    const auto finalNumChars = WriteToStream(pBuffer, numChars+1, includeFormatting, forceLongFormat, sortedProperties);
    s.SetLength(finalNumChars); // Also ensures termination.
  }

  return s;
}

ON_XMLNode::CharacterCounts ON_XMLNode::WriteHeaderToStream(wchar_t* stream, ON__UINT32 max_chars, bool includeFormatting, bool forceLongFormat, bool sortedProperties) const
{
  const bool write = (max_chars != 0);

  // Form the header in a string. The string is only formed if write is true. This is an optimization.
  // logical_header_length keeps track of the length of the string even if it's not being formed.

  ON_wString header;

  if (write)
  {
    ON_ASSERT(_private->m_name.IsNotEmpty());
    header = L"<";
    header += _private->m_name;
  }

  auto logical_header_length = ON__UINT32(_private->m_name.Length()) + 1; // +1 for '<'.

  if (includeFormatting)
  {
    const int depth = GetNestedDepth();
    if (depth > 0)
    {
      if (write)
      {
        header.Insert(0, L'\t', depth);
      }

      logical_header_length += depth;
    }
  }

  /////////////////////////////////////////////////////////////////////////////////
  // This is pure evil.
  // TODO: Find a way to get rid of this psDefaultProperty horror.
  ON_wString def_prop;
  ON_wString encoded_def_prop;
  const ON_wString* psDefaultProperty = nullptr;
  /////////////////////////////////////////////////////////////////////////////////

  auto it = GetPropertyIterator(sortedProperties);
  ON_XMLProperty* pProp = nullptr;
  while (nullptr != (pProp = it.GetNextProperty()))
  {
    if (pProp->IsDefaultProperty())
    {
      const auto& vDP = pProp->GetValue();
      def_prop = vDP.AsString();

      if (vDP.NeedsXMLEncode())
      {
        encoded_def_prop = def_prop;
        EncodeXML(encoded_def_prop);

        if (!encoded_def_prop.IsEmpty())
        {
          psDefaultProperty = &encoded_def_prop;
        }
      }
      else
      {
        if (def_prop.IsNotEmpty())
          psDefaultProperty = &def_prop;
      }
    }
    else
    {
      if (write)
      {
        header += L' ';
        header += pProp->Name();
        header += L"=\"";
      }

      logical_header_length += 3; // +=3 for ' ' and '=\"'.
      logical_header_length += pProp->Name().Length();

      const auto& vValue = pProp->GetValue();

      if (ON_XMLNodePrivate::m_bAutoTypePropValue)
      {
        const ON_wString sType = StringFromPropType(pProp->GetValue().Type());
        if (write)
          header += sType + L':';

        logical_header_length += size_t(sType.Length()) + 1; // +1 for colon.
      }

      const ON_wString value_string = vValue.AsString();

      if (!vValue.NeedsXMLEncode())
      {
        if (write)
          header += value_string;

        logical_header_length += value_string.Length();
      }
      else
      {
        ON_wString encoded_value_string = value_string;
        EncodeXML(encoded_value_string);

        if (write)
          header += encoded_value_string;

        logical_header_length += encoded_value_string.Length();
      }

      if (write)
        header += L'\"';

      logical_header_length++; // ++ for quote.
    }
  }

  if ((nullptr != psDefaultProperty) || (ChildCount() > 0) || forceLongFormat)
  {
    ON_wString sType;

    const bool bType = ON_XMLNodePrivate::m_bAutoTypePropValue && (nullptr != psDefaultProperty);
    if (bType)
      sType = StringFromPropType(GetDefaultProperty().GetValue().Type());

    if (write)
    {
      header += L'>';
      if (bType)
        header += sType + L':';

      if (nullptr != psDefaultProperty)
        header += *psDefaultProperty;
    }

    logical_header_length++; // ++ for '>'.

    if (bType)
      logical_header_length += size_t(sType.Length()) + 1; // +1 for ':'

    if (nullptr != psDefaultProperty)
      logical_header_length += psDefaultProperty->Length();

    if (includeFormatting && (ChildCount() > 0))
    {
      if (write)
        header += L"\r\n";

      logical_header_length += 2; // +2 for \r\n.
    }
  }

  CharacterCounts counts;
  counts._logical = logical_header_length;

  if (0 != max_chars)
  {
    const auto physical_header_length = ON__UINT32(header.Length());
    const auto chars_to_copy = std::min(max_chars, physical_header_length + 1);
    memcpy(stream, static_cast<const wchar_t*>(header), chars_to_copy * sizeof(wchar_t));
    counts._physical = std::min(max_chars, physical_header_length);
    ON_ASSERT(logical_header_length == physical_header_length);
  }

  ON_ASSERT(logical_header_length <= UINT_MAX);

  return counts;
}

ON_XMLNode::CharacterCounts ON_XMLNode::WriteChildrenToStream(wchar_t* stream, ON__UINT32 max_chars, bool includeFormatting, bool forceLongFormat, bool sortedProperties) const
{
  CharacterCounts counts;

  ON_XMLNode* pChild = nullptr;
  auto it = GetChildIterator();
  while (nullptr != (pChild = it.GetNextChild()))
  {
    const auto cc = pChild->WriteToStreamEx(stream, max_chars, includeFormatting, forceLongFormat, sortedProperties);
    counts += cc;
    if (nullptr != stream)
      stream += cc._physical;
    max_chars = std::max(0, int(max_chars - cc._logical));
  }

  return counts;
}

ON_XMLNode::CharacterCounts ON_XMLNode::WriteFooterToStream(wchar_t* stream, ON__UINT32 max_chars, bool includeFormatting, bool forceLongFormat) const
{
  const auto child_count = ChildCount();
  const bool hasDefaultProp = GetDefaultProperty().GetValue().AsString().IsNotEmpty();

  ON_wString footer;

  if (hasDefaultProp || (child_count > 0) || forceLongFormat)
  {
    footer = L"</";
    footer += _private->m_name;
    footer += L'>';

    if (includeFormatting)
    {
      footer += L"\r\n";

      if (child_count > 0)
      {
        const int depth = GetNestedDepth();
        if (depth > 0)
        {
          footer.Insert(0, L'\t', depth);
        }
      }
    }
  }
  else
  {
    footer = L"/>";
    if (includeFormatting)
      footer += L"\r\n";
  }

  CharacterCounts counts;
  counts._logical = ON__UINT32(footer.Length());

  if (0 != max_chars)
  {
    const auto chars_to_copy = std::min(max_chars, counts._logical + 1);
    memcpy(stream, static_cast<const wchar_t*>(footer), chars_to_copy * sizeof(wchar_t));
    counts._physical = std::min(max_chars, counts._logical);
  }

  return counts;
}

void ON_XMLNode::SetInternalDebuggingFlags(ON__UINT64 flags)
{
  _private->m_debug_auto_test_read = (flags & 1);
}

void ON_XMLNode::CharacterCounts::operator += (const CharacterCounts& cw)
{
  _logical  += cw._logical;
  _physical += cw._physical;
}

ON__UINT32 ON_XMLNode::WriteToStream(wchar_t* stream, ON__UINT32 max_chars, bool include_formatting,
                       bool force_long_format, bool sorted_props) const
{
  const auto cc = WriteToStreamEx(stream, max_chars, include_formatting, force_long_format, sorted_props);

#ifdef _DEBUG
  if (_private->m_debug_auto_test_read && (nullptr != stream))
  {
    ON_XMLNode test(TagName());
    const auto read = test.ReadFromStream(stream, true, true);
    if (read != cc._logical)
    {
      ON_ERROR("CRITICAL: Could not read back what was written");
    }
  }
#endif

  return cc._logical;
}

ON_XMLNode::CharacterCounts ON_XMLNode::WriteToStreamEx(wchar_t* stream, ON__UINT32 max_chars, bool includeFormatting, bool forceLongFormat, bool sortedProperties) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  CharacterCounts counts;

  if ((0 != max_chars) && (nullptr == stream))
  {
    ON_ERROR("'stream' cannot be null when 'max_chars' is non-zero");
    return counts;
  }

  auto cc = WriteHeaderToStream(stream, max_chars, includeFormatting, forceLongFormat, sortedProperties);
  counts += cc;
  if (nullptr != stream)
    stream += cc._physical;

  max_chars = std::max(0, int(max_chars - cc._logical));

  cc = WriteChildrenToStream(stream, max_chars, includeFormatting, forceLongFormat, sortedProperties);
  counts += cc;
  if (nullptr != stream)
    stream += cc._physical;

  max_chars = std::max(0, int(max_chars - cc._logical));

  cc = WriteFooterToStream(stream, max_chars, includeFormatting, forceLongFormat);
  counts += cc;

  return counts;
}

bool ON_XMLNode::WriteToSegmentedStream(ON_XMLSegmentedStream& segs, bool includeFormatting, bool forceLongFormat, bool sortedProperties) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  const auto header_cw = WriteHeaderToStream(nullptr, 0, includeFormatting, forceLongFormat, sortedProperties);
  auto* pHeader = new wchar_t[size_t(header_cw._logical) + 1];
  WriteHeaderToStream(pHeader, header_cw._logical + 1, includeFormatting, forceLongFormat, sortedProperties);
  segs.Append(pHeader);

  auto it = GetChildIterator();
  ON_XMLNode* pChild = nullptr;
  while (nullptr != (pChild = it.GetNextChild()))
  {
    pChild->WriteToSegmentedStream(segs, includeFormatting, forceLongFormat, sortedProperties);
  }

  const auto footer_cw = WriteFooterToStream(nullptr, 0, includeFormatting, forceLongFormat);
  auto* pFooter = new wchar_t[size_t(footer_cw._logical) + 1];
  WriteFooterToStream(pFooter, footer_cw._logical + 1, includeFormatting, forceLongFormat);
  segs.Append(pFooter);

  return true;
}

ON_XMLNode* ON_XMLNode::FirstChild(void) const
{
  return _private->m_first_child;
}

ON_XMLNode* ON_XMLNode::PrevSibling(void) const
{
  return _private->PrevSibling();
}

void ON_XMLNode::MoveBefore(ON_XMLNode& other)
{
  _private->MoveBefore(other);
}

void ON_XMLNode::MoveAfter(ON_XMLNode& other)
{
  _private->MoveAfter(other);
}

bool ON_XMLNode::RecurseChildren(ON_XMLRecurseChildrenCallback callback, void* pv) const
{
  return _private->RecurseChildren(callback, pv);
}

ON_XMLNode* ON_XMLNode::NextSibling(void) const
{
  return _private->m_next_sibling;
}

ON__UINT32 ON_XMLNode::DataCRC(ON__UINT32 crc, bool recursive) const
{
  return _private->DataCRC(crc, recursive);
}

void* ON_XMLNode::EVF(const wchar_t*, void*)
{
  return nullptr;
}

ON_XMLNode* ON_XMLNode::GetNodeAtPath(const wchar_t* wszPath) const
{
  return _private->GetNodeAtPath(wszPath, false);
}

ON_XMLNode* ON_XMLNode::CreateNodeAtPath(const wchar_t* wszPath)
{
  return _private->GetNodeAtPath(wszPath, true);
}

void ON_XMLNode::OnNodeReadFromStream(const ON_XMLNode*) const
{
}

ON__UINT32 ON_XMLNode::ReadFromStream(const wchar_t* stream, bool bWarningsAsErrors, bool bValidateTags)
{
  if (nullptr == stream)
  {
    ON_ERROR("Stream cannot be null");
    return ReadError;
  }

  CWarningHelper wh(bWarningsAsErrors);

  Clear();

  // Search for the opening tag "<" character.
  wchar_t* pBuffer = const_cast<wchar_t*>(stream);

  ON_wString tag;

  // 1st August 2022 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-66795
  // The original code was not checking GetNextTag() for failure and blindly continuing with an empty tag.
  // Then in some places it assumed that the tag was not empty. This is confusing because I thought
  // this was causing RH-66795, but it couldn't be because this bug was not in 7.x, and RH-66795 is 7.13.
  if (!_private->GetNextTag(tag, pBuffer, bValidateTags))
    return ReadError;

  if (tag.IsEmpty())
    return ReadError;

  _private->m_last_read_buf_ptr = (void*)stream;

  _private->GetPropertiesFromTag(tag);

  const auto pos1 = tag.Length() - 2; // Assumes the tag is not empty.
  if (tag[pos1] != L'/')
  {
    // This tag either has children, or a default property.
    ON_wString sDefaultProperty;

    bool bClosingTag = false;
    do
    {
      auto* pStoreBuffer = pBuffer;

      // Get anything between the tags and store as the default parameter.
      auto* start = pBuffer;
      while ((*start != L'<') && (*start != 0))
      {
        start++;
      }

      if (0 == *start)
      {
        // We ran off the end of the buffer - no idea why, but this is bad, so fail.
        // See http://mcneel.myjetbrains.com/youtrack/issue/RH-16605 for example.
        return ReadError;
      }

      ON_ASSERT(*start == L'<');

      if (nullptr != start && *start == L'<')
      {
        sDefaultProperty.Append(pBuffer, (int)(start - pBuffer));
      }

      pBuffer = start;

      // 1st August 2022 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-66795
      // The original code was not checking GetNextTag() for failure and blindly continuing with
      // an empty tag. This caused continuous child recursion because the buffer pointer was
      // still pointing at the same (bad) XML. This is confusing because I thought this was causing
      // RH-66795, but it couldn't be because this bug was not in 7.x, and RH-66795 is 7.13.
      if (!_private->GetNextTag(tag, pBuffer, bValidateTags))
        return ReadError;

      bClosingTag = _private->IsClosingTag(tag);

      if (!bClosingTag)
      {
        auto* pNode = new ON_XMLNode(L"");
        AttachChildNode(pNode);

        const auto read = pNode->ReadFromStream(pStoreBuffer, bWarningsAsErrors, bValidateTags);
        if (ReadError == read)
          return ReadError;

        pBuffer = pStoreBuffer + read;
      }
    }
    while (!bClosingTag);

    sDefaultProperty.TrimLeft();
    sDefaultProperty.TrimRight();
    DecodeXML(sDefaultProperty);

    if (!sDefaultProperty.IsEmpty())
    {
      auto* pProp = new ON_XMLProperty;
      AttachProperty(pProp);

      const int pos2 = ON_XMLNodePrivate::m_bAutoTypePropValue ? sDefaultProperty.Find(L":") : -1;
      if (pos2 > 0)
      {
        auto& v = pProp->GetNonConstValue();
        v = sDefaultProperty.Mid(pos2 + 1);
        v.SetTypePendingFlag(true);
      }
      else
      {
        pProp->_private->SetHugeStringValue(sDefaultProperty);
        pProp->_private->GetNonConstValue().SetTypePendingFlag(true);
      }
    }
  }

  TopLevel().OnNodeReadFromStream(this);

  while ((*pBuffer == L'\r') || (*pBuffer == L'\n'))
    pBuffer++;

  return ON__UINT32(pBuffer - stream);
}

ON_wString ON_XMLNode::GetNameFromTag(const wchar_t* wszTag) // Static.
{
  return ON_XMLNodePrivate::GetNameFromTag(wszTag);
}

bool ON_XMLNode::IsValidXMLNameWithDebugging(const wchar_t* name) // Static.
{
  return ON_XMLNodePrivate::IsValidXMLNameWithDebugging(name);
}

bool ON_XMLNode::IsValidXMLName(const wchar_t* name) // Static.
{
  return ON_XMLNodePrivate::IsValidXMLName(name);
}

class ON_XMLNodeChildIteratorPrivate final
{
public:
  ON_XMLNode* _current = nullptr;
};

ON_XMLNode::ChildIterator::ChildIterator(const ON_XMLNode* parent)
{
  _private = new ON_XMLNodeChildIteratorPrivate;

  if (nullptr != parent)
  {
    _private->_current = parent->_private->m_first_child;
  }
}

ON_XMLNode::ChildIterator::ChildIterator(const ChildIterator& other)
{
  _private = new ON_XMLNodeChildIteratorPrivate;
  operator = (other);
}

ON_XMLNode::ChildIterator::~ChildIterator()
{
  delete _private;
}

const ON_XMLNode::ChildIterator& ON_XMLNode::ChildIterator::operator = (const ChildIterator& other)
{
  _private->_current = other._private->_current;

  return *this;
}

ON_XMLNode* ON_XMLNode::ChildIterator::GetNextChild(void)
{
  ON_XMLNode* node = _private->_current;
  if (nullptr != node)
  {
    _private->_current = node->_private->m_next_sibling;
  }

  return node;
}

void* ON_XMLNode::ChildIterator::EVF(const wchar_t*, void*)
{
  return nullptr;
}

// ON_XMLNode::PropertyIterator
 
class ON_XMLNodePropertyIteratorPrivate final
{
public:
  ~ON_XMLNodePropertyIteratorPrivate();

  ON_XMLProperty* GetNextPropertySorted(void)
  {
    // First time through, we build the list.
    if (m_iIndex == 0)
    {
      // While sorting properties, don't allow anything else to access the parent node.
      std::lock_guard<std::recursive_mutex> lg(m_pNode->_private->m_mutex);

      ON_XMLNode::PropertyIterator pi(m_pNode, false);

      ON_ASSERT(m_paSortedProperties == nullptr);
      m_paSortedProperties = new std::vector<ON_XMLProperty>;

      ON_XMLProperty* p = nullptr;
      while (nullptr != (p = pi.GetNextProperty()))
      {
        m_paSortedProperties->push_back(*p);
      }

      std::sort(m_paSortedProperties->begin(), m_paSortedProperties->end());
    }

    ON_ASSERT(m_paSortedProperties != nullptr);

    if (m_iIndex >= int(m_paSortedProperties->size()))
      return nullptr;

    return &(*m_paSortedProperties)[m_iIndex++];
  }

public:
  ON_XMLProperty* m_pCurrent = nullptr;
  const ON_XMLNode* m_pNode = nullptr;
  std::vector<ON_XMLProperty>* m_paSortedProperties = nullptr;
  int m_iIndex = 0;
  bool m_bSorted = false;
};

ON_XMLNodePropertyIteratorPrivate::~ON_XMLNodePropertyIteratorPrivate()
{
  delete m_paSortedProperties;
  m_paSortedProperties = nullptr;
}

ON_XMLNode::PropertyIterator::PropertyIterator(const ON_XMLNode* pNode, bool bSorted)
{
  _private = new ON_XMLNodePropertyIteratorPrivate;

  _private->m_bSorted = bSorted;

  if (_private->m_bSorted)
  {
    if (pNode->PropertyCount() > 1)
    {
      _private->m_pNode = pNode;
      _private->m_iIndex = 0;
    }
    else
    {
      _private->m_bSorted = false;
    }
  }

  if (!_private->m_bSorted)
  {
    if (nullptr != pNode)
    {
      _private->m_pCurrent = pNode->_private->m_first_property;
    }
  }
}

ON_XMLNode::PropertyIterator::PropertyIterator(const PropertyIterator& other)
{
  _private = new ON_XMLNodePropertyIteratorPrivate;
  operator = (other);
}

ON_XMLNode::PropertyIterator::~PropertyIterator()
{
  delete _private;
}

const ON_XMLNode::PropertyIterator& ON_XMLNode::PropertyIterator::operator = (const PropertyIterator& other)
{
  _private->m_pCurrent           = other._private->m_pCurrent;
  _private->m_pNode              = other._private->m_pNode;
  _private->m_iIndex             = other._private->m_iIndex;
  _private->m_bSorted            = other._private->m_bSorted;
  _private->m_paSortedProperties = other._private->m_paSortedProperties;

  return *this;
}

ON_XMLProperty* ON_XMLNode::PropertyIterator::GetNextProperty(void)
{
  if (_private->m_bSorted)
    return _private->GetNextPropertySorted();

  ON_XMLProperty* prop = _private->m_pCurrent;
  if (nullptr != prop)
  {
    _private->m_pCurrent = prop->_private->_next;
  }

  return prop;
}

void* ON_XMLNode::PropertyIterator::EVF(const wchar_t*, void*)
{
  return nullptr;
}

// ON_XMLRootNode

// TODO: Somehow I managed to port the non-rc version of the root node.
//       TODO: We really need the rc version.

static const ON_wString sXMLRootNodeName(L"xml");

//class ON_XMLRootNodePrivate final // For future use.
//{
//};

ON_XMLRootNode::ON_XMLRootNode()
  :
  ON_XMLNode(sXMLRootNodeName)
{
  _private = nullptr; //new ON_XMLRootNodePrivate;
}

ON_XMLRootNode::ON_XMLRootNode(const ON_XMLNode& src)
  :
  ON_XMLNode(sXMLRootNodeName)
{
  _private = nullptr; //new ON_XMLRootNodePrivate;
  *this = src;
}

ON_XMLRootNode::ON_XMLRootNode(const ON_XMLRootNode& src)
  :
  ON_XMLNode(sXMLRootNodeName)
{
  _private = nullptr; //new ON_XMLRootNodePrivate;
  *this = src;
}

ON_XMLRootNode::~ON_XMLRootNode()
{
  //delete _private;
}

const ON_XMLRootNode& ON_XMLRootNode::operator = (const ON_XMLNode& src)
{
  *static_cast<ON_XMLNode*>(this) = src;

  return *this;
}

const ON_XMLRootNode& ON_XMLRootNode::operator = (const ON_XMLRootNode& src)
{
  *static_cast<ON_XMLNode*>(this) = src;

  return *this;
}

const ON_XMLRootNode& ON_XMLRootNode::NodeForRead(void) const
{
  return *this;
}

ON_XMLRootNode& ON_XMLRootNode::NodeForWrite(void)
{
  return *this;
}

bool ON_XMLRootNode::ReadFromFile(const wchar_t* wszPath, bool bWarningsAsErrors, bool bValidateTags)
{
  CWarningHelper wh(bWarningsAsErrors);

  ON_UnicodeTextFile file;
  if (!file.Open(wszPath, ON_UnicodeTextFile::Modes::Read))
  {
    ON_wString s;
    s.Format(L"Failed to open file %s", wszPath);
    OUTPUT_DEBUG_STRING_EOL(s);
    return false;
  }

  ON_wString sXML;
  if (!file.ReadString(sXML))
  {
    ON_wString s;
    s.Format(L"Failed to read file %s", wszPath);
    OUTPUT_DEBUG_STRING_EOL(s);
    return false;
  }

  const auto* stream = static_cast<const wchar_t*>(sXML);
  const auto read = ReadFromStream(stream, bWarningsAsErrors, bValidateTags);
  if (read == ReadError)
  {
    ON_wString s;
    s.Format(L"XML error reading file %s", wszPath);
    OUTPUT_DEBUG_STRING_EOL(s);
    return false;
  }

  if (0 == read)
  {
    ON_wString s;
    s.Format(L"No valid XML was read from the file %s", wszPath);
    OUTPUT_DEBUG_STRING_EOL(s);
    return false;
  }

  return true;
}

bool ON_XMLRootNode::WriteToFile(const wchar_t* wszPath, bool includeFormatting, bool bUTF8, bool sortedProperties) const
{
  const auto type = bUTF8 ? ON_UnicodeTextFile::Types::UTF8 : ON_UnicodeTextFile::Types::UTF16;
  ON_UnicodeTextFile file(type);
  if (!file.Open(wszPath, ON_UnicodeTextFile::Modes::Write))
    return false;

  ON_XMLSegmentedStream segs;
  WriteToSegmentedStream(segs, includeFormatting, false, sortedProperties);

  for (int i = 0; i < segs.Count(); i++)
  {
    file.WriteString(segs.Segment(i));
  }

  file.Close();

  return true;
}

void ON_XMLRootNode::Clear(void)
{
  ON_XMLNode::Clear();

  SetTagName(sXMLRootNodeName);
}

// ON_XMLUserData -- Specializes ON_UserData for XML use.

class ON_XMLUserDataPrivate final
{
public:
  ON_XMLRootNode m_XMLRoot;
};

ON_XMLUserData::ON_XMLUserData()
{
  _private = new (_PRIVATE) ON_XMLUserDataPrivate; PRIVATE_CHECK(ON_XMLUserDataPrivate);

  m_userdata_copycount = 1;
  m_userdata_uuid = ON_nil_uuid;
}

ON_XMLUserData::ON_XMLUserData(const ON_XMLUserData& ud)
  :
  ON_UserData(ud)
{
  _private = new (_PRIVATE) ON_XMLUserDataPrivate; PRIVATE_CHECK(ON_XMLUserDataPrivate);

  m_userdata_copycount = ud.m_userdata_copycount;
  m_userdata_uuid = ud.m_userdata_uuid;
}

ON_XMLUserData::~ON_XMLUserData()
{
  _private->~ON_XMLUserDataPrivate();
  _private = nullptr;
}

const ON_XMLUserData& ON_XMLUserData::operator = (const ON_XMLUserData& ud)
{
  ON_UserData::operator = (ud); // CRITICAL - Be sure to call base class.

  m_userdata_uuid = ud.m_userdata_uuid;

  _private->m_XMLRoot = ud._private->m_XMLRoot;

  return *this;
}

const ON_XMLRootNode& ON_XMLUserData::XMLRootForRead(void) const
{
  return _private->m_XMLRoot.NodeForRead();
}

ON_XMLRootNode& ON_XMLUserData::XMLRootForWrite(void) const // const is a mistake. [SDK_UNFREEZE]
{
  // 22nd January 2025 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-67878
  // Per conversation with Dale Lear, this is bad because we are actually going to change the user data while
  // it's already attached to the attributes. We're actually expected to delete the old user data and create
  // new user data with the changes in it, because otherwise Rhino can't know that it was changed. However,
  // Dale suggested the easiest way to fix this is to just bump the copy count, because the optimization in
  // CRhinoObject::ModifyAttributes() involving the copy count is really a hack anyway.

  if (m_userdata_copycount > 0) // Zero means we are not even copying user data.
  {
    const_cast<ON_XMLUserData*>(this)->m_userdata_copycount++;
  }

  return _private->m_XMLRoot.NodeForWrite();
}

ON_XMLProperty* ON_XMLUserData::Property(const wchar_t* wszXMLPath, const wchar_t* wszPropertyName) const
{
  auto* pProp = InternalProperty(wszXMLPath, wszPropertyName);
  if (nullptr == pProp)
  {
    // Failed to get the property. This probably means that the XML strings have been changed
    // and this is old user data. Reset to defaults.
    SetToDefaults();

    // This can still return nullptr if the path and/or property were not set as one of the defaults.
    pProp = InternalProperty(wszXMLPath, wszPropertyName);
  }

  return pProp;
}

ON_XMLVariant ON_XMLUserData::Value(const wchar_t* wszXMLPath, const wchar_t* wszPropertyName) const
{
  const auto* pProp = Property(wszXMLPath, wszPropertyName);
  if (pProp != nullptr)
  {
    return pProp->GetValue();
  }

  return ON_XMLVariant();
}

bool ON_XMLUserData::SetValue(const wchar_t* wszXMLPath, const wchar_t* wszPropertyName, const ON_XMLVariant& value)
{
  auto* pProp = Property(wszXMLPath, wszPropertyName);
  if (pProp != nullptr)
  {
    pProp->SetValue(value);
    return true;
  }

  return false;
}

void ON_XMLUserData::SetValue(const wchar_t* wszXMLPath, const ON_XMLVariant& value)
{
  SetValue(wszXMLPath, L"", value);
}

void ON_XMLUserData::Clear(void) const
{
  _private->m_XMLRoot.Clear();
}

int ON_XMLUserData::Version(void) const
{
  return 2;
}

ON_XMLProperty* ON_XMLUserData::InternalProperty(const wchar_t* wszXMLPath, const wchar_t* wszPropertyName) const
{
  const auto* pNode = _private->m_XMLRoot.NodeForRead().GetNodeAtPath(wszXMLPath);
  if (nullptr == pNode)
    return nullptr;

  return pNode->GetNamedProperty(wszPropertyName);
}

void ON_XMLUserData::SetToDefaultsImpl(int) const
{
  SetToDefaults();
}

bool ON_XMLUserData::Archive(void) const
{
  // 12th July 2023 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-75697
  // We only want to archive the user data if there's something useful in the XML. For there
  // to be something useful in the XML, the root node must have at least one child node.
  return _private->m_XMLRoot.ChildCount() > 0;
}

bool ON_XMLUserData::Read(ON_BinaryArchive& archive)
{
  // Read the version number.
  int version = 0;
  if (!archive.ReadInt(&version))
    return false;

  // Cannot load user data with a version number greater than mine.
  if (version > Version())
  {
    ReportVersionError();
    return false;
  }

  // Clear any existing XML data.
  XMLRootForWrite().Clear();

  if (1 == version)
  {
    // Original version. Read the archive into a string.
    ON_wString s;
    if (!archive.ReadString(s))
      return false;

    // Read the string into the XML root.
    XMLRootForWrite().ReadFromStream(s);

    return true;
  }

  // UTF8 version. Read the length of the UTF8 buffer from the archive.
  int length_utf8 = 0;
  if (!archive.ReadInt(&length_utf8))
    return false;

  // Read the UTF8 buffer from the archive.
  auto utf8 = std::unique_ptr<char[]>(new char[size_t(length_utf8)+1]);
  auto* pUTF8 = utf8.get();

  if (!archive.ReadChar(length_utf8, pUTF8))
    return false;

  pUTF8[length_utf8] = 0; // Terminator.

  // Convert the UTF8 data to wide chars and read it into the root node.
  const auto num_chars = ON_ConvertUTF8ToWideChar(false, pUTF8, -1, nullptr, 0, nullptr, 0, 0, nullptr);
  auto wide = std::unique_ptr<wchar_t[]>(new wchar_t[size_t(num_chars) + 1]);
  auto* pWide = wide.get();
  ON_ConvertUTF8ToWideChar(false, pUTF8, -1, pWide, num_chars+1, nullptr, 0, 0, nullptr);

  if (ON_XMLNode::ReadError == XMLRootForWrite().ReadFromStream(pWide))
    return false;

  return true;
}

bool ON_XMLUserData::Write(ON_BinaryArchive& archive) const
{
  // Write the version number to the archive.
  if (!archive.WriteInt(Version()))
    return false;

  // Convert the XML string to UTF8.
  const auto sXML = XMLRootForRead().String();
  const auto* wsz = static_cast<const wchar_t*>(sXML);

  const auto num_chars = ON_ConvertWideCharToUTF8(false, wsz, -1, nullptr, 0, nullptr, 0, 0, nullptr);

  auto utf8 = std::unique_ptr<char[]>(new char[num_chars]);
  auto* pUTF8 = utf8.get();

  ON_ConvertWideCharToUTF8(false, wsz, -1, pUTF8, num_chars, nullptr, 0, 0, nullptr);

  // Write the length of the UTF8 buffer to the archive.
  if (!archive.WriteInt(num_chars))
    return false;

  // Write the UTF8 buffer to the archive.
  if (!archive.WriteChar(num_chars, pUTF8))
    return false;

  return true;
}

void ON_XMLUserData::_Dump(const wchar_t* wszFileName) const
{
  _private->m_XMLRoot.WriteToFile(wszFileName);
}

void* ON_XMLUserData::EVF(const wchar_t*, void*)
{
  return nullptr;
}

// ON_XMLParameters

class ON_XMLParametersPrivate
{
public:
  ON_XMLParametersPrivate(ON_XMLNode& n) : _node(n) { }

  ON_XMLNode& _node;
  ON_wString _default_type;
  bool _write_type_property = true;
};

ON_XMLNode* ON_XMLParameters::ObtainChildNodeForWrite(ON_XMLNode& node, const wchar_t* wszParamName) const
{
  // <ambient...

  // If the parameter name is not valid XML, we can't write this parameter in the legacy format.
  if (!ON_XMLNode::IsValidXMLName(wszParamName))
    return nullptr;

  auto* pChildNode = node.GetNamedChild(wszParamName);
  if (nullptr == pChildNode)
  {
    pChildNode = node.AttachChildNode(new ON_XMLNode(wszParamName));
  }

  return pChildNode;
}

ON_XMLParameters::ON_XMLParameters(ON_XMLNode& node)
{
  _private = new ON_XMLParametersPrivate(node);
}

ON_XMLParameters::ON_XMLParameters(const ON_XMLNode& node)
{
  _private = new ON_XMLParametersPrivate(const_cast<ON_XMLNode&>(node));
}

ON_XMLParameters::~ON_XMLParameters()
{
  delete _private;
}

void ON_XMLParameters::SetWriteTypeProperty(bool b)
{
  _private->_write_type_property = b;
}

void ON_XMLParameters::SetDefaultReadType(const wchar_t* wszType)
{
  _private->_default_type = wszType;
}

ON_wString ON_XMLParameters::AsString(void) const
{
  return _private->_node.String();
}

void ON_XMLParameters::SetAsString(const wchar_t* wsz)
{
  _private->_node.ReadFromStream(wsz);
}

bool ON_XMLParameters::GetParam(const wchar_t* wszParamName, ON_XMLVariant& vValueOut) const
{
  // This expects the legacy format where the param name is the XML tag.
  // If you want to use the new system, you should be using ON_XMLParametersV8.

  const auto* pNode = _private->_node.GetNodeAtPath(wszParamName);
  if (nullptr == pNode)
    return false;

  if (!GetParamNode(*pNode, vValueOut))
    return false;

  return true;
}

ON_XMLNode* ON_XMLParameters::SetParam(const wchar_t* wszParamName, const ON_XMLVariant& value)
{
  if (ON_wString(wszParamName).IsEmpty())
    return nullptr;

  // Set the parameter node.
  return SetParamNode(_private->_node, wszParamName, value);
}

ON_XMLVariant ON_XMLParameters::GetParam(const wchar_t* param_name, const ON_XMLVariant& default_value) const
{
  ON_XMLVariant value;
  if (GetParam(param_name, value))
    return value;

  return default_value;
}

ON_XMLNode* ON_XMLParameters::SetParamNode(ON_XMLNode& node, const wchar_t* wszParamName, const ON_XMLVariant& vValue)
{
  auto* pChildNode = ObtainChildNodeForWrite(node, wszParamName);
  if (nullptr == pChildNode)
    return nullptr;

  const wchar_t* wszType = L"";
  switch (vValue.Type())
  {
  case ON_XMLVariant::Types::Integer:      wszType = L"int";      break;
  case ON_XMLVariant::Types::Float:        wszType = L"float";    break;
  case ON_XMLVariant::Types::Double:       wszType = L"double";   break;
  case ON_XMLVariant::Types::String:       wszType = L"string";   break;
  case ON_XMLVariant::Types::Bool:         wszType = L"bool";     break;
  case ON_XMLVariant::Types::DoubleColor4: wszType = L"color";    break;
  case ON_XMLVariant::Types::DoubleArray2: wszType = L"vector2d"; break;
  case ON_XMLVariant::Types::DoubleArray3: wszType = L"vector3d"; break;
  case ON_XMLVariant::Types::DoubleArray4: wszType = L"point4d";  break;
  case ON_XMLVariant::Types::Uuid:         wszType = L"uuid";     break;
  case ON_XMLVariant::Types::Matrix:       wszType = L"matrix";   break;
  case ON_XMLVariant::Types::Time:         wszType = L"time";     break;
  case ON_XMLVariant::Types::Buffer:       wszType = L"buffer";   break;

  default:
    ; // NULL variant is normal these days.
  }

  // Default property is the actual value.
  ON_XMLProperty prop;
  prop.SetValue(vValue);
  pChildNode->SetProperty(prop);

  // Set units (if any).
  if (ON::LengthUnitSystem::None != vValue.Units())
  {
    prop.SetName(L"units");
    const auto* wsz = StringFromUnits(vValue.Units());
    prop.SetValue(wsz);
    pChildNode->SetProperty(prop);
  }

  if (_private->_write_type_property)
  {
    // Set type.
    prop.SetName(L"type");
    prop.SetValue(wszType);
    pChildNode->SetProperty(prop);
  }

  return pChildNode;
}

ON_XMLNode& ON_XMLParameters::Node(void)
{
  return _private->_node;
}

const ON_XMLNode& ON_XMLParameters::Node(void) const
{
  return _private->_node;
}

bool ON_XMLParameters::GetParamNode(const ON_XMLNode& node, ON_XMLVariant& vValueOut) const
{
  vValueOut.SetUnits(ON::LengthUnitSystem::None);

  const auto& v = node.GetDefaultProperty().GetValue();

  ON_wString sType = _private->_default_type;

  ON_XMLProperty* prop = node.GetNamedProperty(L"type");
  if (nullptr != prop)
  {
    sType = prop->GetValue().AsString();
  }
  else
  if (sType.IsEmpty())
  {
    // The node contains no type specifier and a default type was not specified by the caller. Fail.
    vValueOut.SetNull();
    return false;
  }

  // Andy hack to solve the problem with matrices stored as strings on early versions of RDK.
  if ((vValueOut.Type() == ON_XMLVariant::Types::Matrix) && (sType == L"string"))
  {
    sType = L"matrix";
  }

  if (sType.IsEmpty())
  {
    vValueOut.SetNull();
  }
  else
  if (sType.CompareNoCase(L"bool") == 0)
  {
    vValueOut = v.AsBool();
  }
  else
  if ((sType.CompareNoCase(L"int") == 0)   ||
      (sType.CompareNoCase(L"short") == 0) ||
      (sType.CompareNoCase(L"char") == 0)  ||
      (sType.CompareNoCase(L"long") == 0))
  {
    vValueOut = v.AsInteger();
  }
  else
  if (sType.CompareNoCase(L"float") == 0)
  {
    vValueOut = v.AsFloat();
  }
  else
  if ((sType.CompareNoCase(L"double") == 0) ||
      (sType.CompareNoCase(L"real") == 0))  // For backward compatibility with old XML.
  {
    vValueOut = v.AsDouble();
  }
  else
  if (sType.CompareNoCase(L"point") == 0)  // For backward compatibility with old XML.
  {
    vValueOut = v.AsColor();
  }
  else
  if (sType.CompareNoCase(L"color") == 0)
  {
    // Get both as 3d and 4d points; that way it works for old files
    // that only had 3d points and also for new files that have 4d points.

    const auto t = v.Type();
    ON_4dPoint pt(0.0, 0.0, 0.0, 1.0);

    if (t == ON_XMLVariant::Types::DoubleArray3)
    {
      const ON_3dPoint p3(v.As3dPoint());
      pt.x = p3.x;
      pt.y = p3.y;
      pt.z = p3.z;
    }
    else
    if ((t == ON_XMLVariant::Types::DoubleArray4) || (t == ON_XMLVariant::Types::DoubleColor4))
    {
      pt = v.As4dPoint();
    }
    else
    {
      const auto sColor = v.AsString();

      if (sColor.IsValid4dPoint())
      {
        pt = v.As4dPoint();
      }

      if (sColor.IsValid3dPoint())
      {
        const ON_3dPoint p3(v.As3dPoint());
        pt.x = p3.x;
        pt.y = p3.y;
        pt.z = p3.z;
      }
    }

    // Get x, y, z from 3d point and w from 4d point.
    ON_4fColor c;
    c.SetRGBA(float(pt.x), float(pt.y), float(pt.z), float(pt.w));
    vValueOut = c;
  }
  else
  if (sType.CompareNoCase(L"vector2d") == 0)
  {
    vValueOut = ON_XMLVariant(v.As2dPoint(), ON_XMLVariant::ArrayTypes::Array2);
  }
  else
  if ((sType.CompareNoCase(L"vector3d") == 0) ||
      (sType.CompareNoCase(L"vector") == 0))  // For backward compatibilty with old XML.
  {
    vValueOut = ON_XMLVariant(v.As3dPoint(), ON_XMLVariant::ArrayTypes::Array3);
  }
  else
  if (sType.CompareNoCase(L"point4d") == 0)
  {
    vValueOut = ON_XMLVariant(v.As4dPoint(), ON_XMLVariant::ArrayTypes::Array4);
  }
  else
  if (sType.CompareNoCase(L"string") == 0)
  {
    vValueOut = v.AsString();
  }
  else
  if (sType.CompareNoCase(L"matrix") == 0)
  {
    vValueOut = v.AsXform();
  }
  else
  if (sType.CompareNoCase(L"uuid") == 0)
  {
    vValueOut = v.AsUuid();
  }
  else
  if (sType.CompareNoCase(L"time") == 0)
  {
    vValueOut = v.AsTime();
  }
  else
  if (sType.CompareNoCase(L"buffer") == 0)
  {
    vValueOut = v.AsBuffer();
  }

  prop = node.GetNamedProperty(L"units");
  if (nullptr != prop)
  {
    const auto sUnits = prop->GetValue().AsString();
    vValueOut.SetUnits(UnitsFromString(sUnits));
  }

  return true;
}

ON_XMLParameters::CIterator* ON_XMLParameters::NewIterator(void) const
{
  return new CIterator(*this);
}

void* ON_XMLParameters::EVF(const wchar_t*, void*)
{
  return nullptr;
}

class ON_XMLParametersIteratorPrivate
{
public:
  ON_XMLParametersIteratorPrivate(const ON_XMLParameters& p)
    : m_Params(p), m_XMLIterator(&p._private->_node) { }

  const ON_XMLParameters& m_Params;
  ON_XMLNode::ChildIterator m_XMLIterator;
};

ON_XMLParameters::CIterator::CIterator(const ON_XMLParameters& p)
{
  _private = new ON_XMLParametersIteratorPrivate(p);
}

ON_XMLParameters::CIterator::~CIterator()
{
  delete _private;
}

bool ON_XMLParameters::CIterator::Next(ON_wString& sParamNameOut, ON_XMLVariant& vParamValueOut) const
{
  const auto* pNode = _private->m_XMLIterator.GetNextChild();
  if (nullptr == pNode)
    return false;

  sParamNameOut = pNode->TagName();

  _private->m_Params.GetParamNode(*pNode, vParamValueOut);

  return true;
}

void* ON_XMLParameters::CIterator::EVF(const wchar_t*, void*)
{
  return nullptr;
}

// ON_XMLParametersV8

ON_XMLParametersV8::ON_XMLParametersV8(ON_XMLNode& node)
  :
  ON_XMLParameters(node)
{
}

ON_XMLParametersV8::ON_XMLParametersV8(const ON_XMLNode& node)
  :
  ON_XMLParameters(node)
{
}

ON_XMLNode* ON_XMLParametersV8::ObtainChildNodeForWrite(ON_XMLNode& node, const wchar_t* wszParamName) const
{
  // <parameter name="ambient"...

  auto* pChildNode = FindNodeByNameProperty(wszParamName);
  if (nullptr == pChildNode)
  {
    pChildNode = node.AttachChildNode(new ON_XMLNode(ON_PARAMETER));

    // Set the parameter name.
    ON_XMLProperty prop;
    prop.SetName(ON_NAME);
    prop.SetValue(wszParamName);
    pChildNode->SetProperty(prop);
  }

  return pChildNode;
}

ON_XMLNode* ON_XMLParametersV8::FindNodeByNameProperty(const wchar_t* wszParamName) const
{
  auto* pNode = Node().FirstChild();
  while (nullptr != pNode)
  {
    auto* pProp = pNode->GetNamedProperty(ON_NAME);
    if (nullptr != pProp)
    {
      if (pProp->GetValue().AsString() == wszParamName)
        return pNode;
    }

    pNode = pNode->NextSibling();
  }

  return nullptr;
}

bool ON_XMLParametersV8::GetParam(const wchar_t* wszParamName, ON_XMLVariant& vValueOut) const
{
  const auto* pNode = FindNodeByNameProperty(wszParamName);
  if (nullptr == pNode)
    return false;

  if (!GetParamNode(*pNode, vValueOut))
    return false;

  return true;
}

#define ON_RDK_UD_MATERIAL     L"material"
#define ON_RDK_UD_INSTANCE_ID  L"instance-id"

ON_UUID ON_UuidDefaultMaterialInstance    = ON_RenderContentType_DefaultMaterial;
ON_UUID ON_UuidDefaultEnvironmentInstance = ON_RenderContentType_DefaultEnvironment;

ON_OBJECT_IMPLEMENT(ON_RdkUserData, ON_UserData, "AFA82772-1525-43dd-A63C-C84AC5806911");

static ON_RdkUserData::ReadCallback      g_RdkUserDataReadCallback = nullptr;
static ON_RdkUserData::WriteCallback     g_RdkUserDataWriteCallback = nullptr;
static ON_RdkUserData::TransformCallback g_RdkUserDataTransformCallback = nullptr;

void ON_RdkUserData::SetCallbacks(ReadCallback rc, WriteCallback wc, TransformCallback tc) // Static.
{
  g_RdkUserDataReadCallback = rc;
  g_RdkUserDataWriteCallback = wc;
  g_RdkUserDataTransformCallback = tc;
}

ON_UUID ON_RdkUserData::Uuid(void) // Static.
{
  const ON_UUID uuid = { 0xb63ed079, 0xcf67, 0x416c, { 0x80, 0xd, 0x22, 0x2, 0x3a, 0xe1, 0xbe, 0x21 } };
  return uuid;
}

ON_RdkUserData::ON_RdkUserData()
{
  m_userdata_uuid = Uuid();

  m_application_uuid = RdkPlugInId();

  m_userdata_copycount = 1;

  SetToDefaults();
}

ON_RdkUserData::ON_RdkUserData(const ON_RdkUserData& ud)
  :
  ON_XMLUserData(ud) // CRITICAL - Be sure to call base class.
{
  m_userdata_uuid = Uuid();

  m_application_uuid = RdkPlugInId();

  // DO NOT SET OTHER ON_UserData fields
  // In particular, do not set m_userdata_copycount

  *this = ud;
}

ON_RdkUserData::~ON_RdkUserData()
{
}

const ON_RdkUserData& ON_RdkUserData::operator = (const ON_RdkUserData& ud)
{
  if (this != &ud)
  {
    // Use the base class operator=() to correctly copy all ON_UserData fields.
    ON_XMLUserData::operator = (ud);
  }

  return *this;
}

void ON_RdkUserData::SetToDefaults(void) const
{
  const_cast<ON_RdkUserData*>(this)->Clear();
}

void ON_RdkUserData::ReportVersionError(void) const
{
  //::RhRdkErrorBox(RhLocalizeString( L"This document was created with a more recent version of RDK", 23067));
}

bool ON_RdkUserData::GetDescription(ON_wString& s)
{
  s = L"RDK data";

  return true;
}

bool ON_RdkUserData::Read(ON_BinaryArchive& ar)
{
  if (!ON_XMLUserData::Read(ar))
    return false;

  if (nullptr != g_RdkUserDataReadCallback)
  {
    (*g_RdkUserDataReadCallback)(*this);
  }

  return true;
}

bool ON_RdkUserData::Write(ON_BinaryArchive& ar) const
{
  if (!ON_XMLUserData::Write(ar))
    return false;

  if (nullptr != g_RdkUserDataWriteCallback)
  {
    (*g_RdkUserDataWriteCallback)(*this);
  }

  return true;
}

bool ON_RdkUserData::DeleteAfterWrite(const ON_BinaryArchive& archive, const ON_Object* parent_object) const
{
  // RDK user data has been used to attach information to both ON_Material and non-ON_Material classes.
  // Its use on ON_Material is now obsolete and this case should never happen again.
  ON_ASSERT(nullptr == ON_Material::Cast(parent_object));

  return false; // false means the user data will continue to exist.
}

bool ON_RdkUserData::DeleteAfterRead(const ON_BinaryArchive& archive, ON_Object* parent_object) const
{
  // Pre V6 May 16, 2014, the RDK material instance id for ON_Materials was stored as user data.
  // As of V6, May 16, 2014, the id is stored on ON_Material::m_rdk_material_instance_id.
  //
  // This virtual ON_UserData override is used to delete RDK user data that is:
  //  - attached to ON_Material
  //  - stores the obsolete material instance id that is now on ON_Material::m_rdk_material_instance_id

  auto* pOnMaterial = ON_Material::Cast(parent_object);
  if (nullptr == pOnMaterial)
  {
    // CRhRdkUserData has been used to attach information to both ON_Material and non-ON_Material classes.
    // Its use on ON_Material is now obsolete and this case is handled below.
    // When the parent object is not an ON_Material, ON_RdkUserData is now used (replaces CRhRdkUserData).
    return false; // false means the user data will continue to exist.
  }

  // Because this RDK user data was on the material, set its plug-in id to 'universal'.
  // This replaces a hack in CRhinoRead3dmHelper::ReadMaterialTable() which corrected
  // the plug-in id of V4 materials. These materials were wrongly saved by V4 with the
  // current render engine id instead of 'universal'.
  pOnMaterial->SetMaterialPlugInId(ON_UniversalRenderEngineId); // Fixes RH-27240 'V4 RDK materials do not work correctly in V6'

  // Transfer the instance id from the user data to the new member variable.
  const auto* wsz = ON_RDK_UD_ROOT  ON_XML_SLASH  ON_RDK_UD_MATERIAL;
  const auto uuidInstance = Value(wsz, ON_RDK_UD_INSTANCE_ID).AsUuid();
  ON_ASSERT(pOnMaterial->RdkMaterialInstanceIdIsNil() || (uuidInstance == pOnMaterial->RdkMaterialInstanceId()));
  pOnMaterial->SetRdkMaterialInstanceId(uuidInstance);

  return true; // true means this obsolete userdata will be deleted by the ON_BinaryArchive reading code.
}

bool ON_RdkUserData::Transform(const ON_Xform& xform)
{
  if (nullptr != g_RdkUserDataTransformCallback)
  {
    (*g_RdkUserDataTransformCallback)(*this, xform);
  }

  return ON_XMLUserData::Transform(xform);
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////             ///////////////////////////////////////
////////////////////////////////////  T E S T S  ///////////////////////////////////////
////////////////////////////////////             ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

static bool g_bXMLTestsOK = true;

#ifdef ON_RUNTIME_WIN
static size_t CallbackDone = 0;
static char CallbackBuffer[1000];
#endif

static std::recursive_mutex g_mutex;

static void ThreadFunc(wchar_t c)
{
  std::lock_guard<std::recursive_mutex> lg(g_mutex);

  ON_wString s = c;
  for (int i = 0; i < 100; i++)
  {
    OUTPUT_DEBUG_STRING(s);
  }

  OUTPUT_DEBUG_STRING(L"\n");
}

#ifdef ON_RUNTIME_WIN
static bool Base64Callback(void* context, ON__UINT32 size, const void* buffer)
{
  memcpy(CallbackBuffer + CallbackDone, buffer, size);

  CallbackDone += size;

  return true;
}
#endif

static void Validate(bool b)
{
  ON_ASSERT(b);
  if (!b)
    g_bXMLTestsOK = false;
}

void GetRDKTestXML(ON_wString& sXML)
{
    //const auto sFile = L"C:\\Users\\croud\\Desktop\\RdkSave.txt";
    //ON_UnicodeTextFile file;
    //if (file.Open(sFile, ON_UnicodeTextFile::Modes::Load))
    //{
    //  ON_wString s;
    //  Validate(file.ReadString(s));
    //  Validate(file.Close());
    //
    //  ON_wString sBase64;
    //  ON_Base64::Encode(s.Array(), s.Length() * sizeof(wchar_t), sBase64, false);
    //
    //  file.Close();
    //}

    // Decode a huge Base64 string into a load of RDK XML in UTF16.
    const auto* wszBase64 =
   L"PAB4AG0AbAA+AA0ACgAJADwAcgBlAG4AZABlAHIALQBjAG8AbgB0AGUAbgB0AC0AbQBhAG4AYQBnAGUAcgAtAGQAbwBjAHUAbQBlAG4AdAA+AA0ACgAJAAkAPABtAGEAdABlAHIAaQBhAGwALQBzAGUAYwB0AGkAbwBuAD4ADQAKAAkACQAJADwAbQBhAHQAZQByAGkAYQBsACAAdAB5AHAAZQAtAG4AYQBtAGUAPQAiAHIAYwBtAC0AYgBhAHMAaQBjAC0AbQBhAHQAZQByAGkAYQBsACIAIAByAGUAbgBkAGUAcgAtAGUAbgBnAGkAbgBlAC0AaQBkAD0AIgA5ADkAOQA5ADkAOQA5ADkALQA5ADkAOQA5AC0AOQA5ADkAOQAtADkAOQA5ADkALQA5ADkAOQA5ADkAOQA5ADkAOQA5ADkAOQAiACAAcABsAHUAZwAtAGkAbgAtAGkAZAA9AC"
    "IAMQA2ADUAOQAyAEQANQA4AC0ANABBADIARgAtADQAMAAxAEQALQBCAEYANQBFAC0AMwBCADgANwA3ADQAMQBDADEAQgAxAEIAIgAgAHQAeQBwAGUALQBpAGQAPQAiAEIAQQA1ADEAQwAwADAAMAAtAEIAQQA1ADEALQBDADAAMAAwAC0AQgBBADUAMQAtAEMAMABCAEEANQAxAEMAMAAwADAAMAAwACIAIABpAG4AcwB0AGEAbgBjAGUALQBpAGQAPQAiADQAQgA5ADcAMABCADYANQAtADQARAA4AEMALQA0ADQAOQAyAC0AOQAxAEEAOQAtADkARgBEADcARgBEAEUARQA5ADMAMAAxACIAIABpAG4AcwB0AGEAbgBjAGUALQBuAGEAbQBlAD0AIgBDAHUAcwB0AG8AbQAiACAAbgBvAHQAZQBzAD0AIgAiACAAdABhAGcAcwA9ACIAIgAg"
    "AGgAaQBkAGQAZQBuAD0AIgBmAGEAbABzAGUAIgAgAHIAZQBmAGUAcgBlAG4AYwBlAD0AIgBmAGEAbABzAGUAIgAgAGEAdQB0AG8ALQBkAGUAbABlAHQAZQA9ACIAZgBhAGwAcwBlACIAPgANAAoACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByAHMALQB2ADgAPgANAAoACQAJAAkACQAJADwAcABhAHIAYQBtAGUAdABlAHIAIABuAGEAbQBlAD0AIgB2AGUAcgBzAGkAbwBuACIAIAB0AHkAcABlAD0AIgBpAG4AdAAiAD4AMgA8AC8AcABhAHIAYQBtAGUAdABlAHIAPgANAAoACQAJAAkACQAJADwAcABhAHIAYQBtAGUAdABlAHIAIABuAGEAbQBlAD0AIgBkAGkAZgBmAHUAcwBlACIAIAB0AHkAcABlAD0AIgBjAG8AbABvAHIAIg"
    "A+ADAALgA5ADgAMAAzADkAMgAxADUAOAAwADMAMQA0ADYANAAsADAALgA5ADgAMAAzADkAMgAxADUAOAAwADMAMQA0ADYANAAsADAALgA5ADgAMAAzADkAMgAxADUAOAAwADMAMQA0ADYANAAsADEAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAcwBwAGUAYwB1AGwAYQByACIAIAB0AHkAcABlAD0AIgBjAG8AbABvAHIAIgA+ADEALAAxACwAMQAsADEAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAcwBoAGkAbgBlACIAIAB0AHkAcABlAD0AIgBkAG8AdQBiAGwA"
    "ZQAiAD4AMAA8AC8AcABhAHIAYQBtAGUAdABlAHIAPgANAAoACQAJAAkACQAJADwAcABhAHIAYQBtAGUAdABlAHIAIABuAGEAbQBlAD0AIgB0AHIAYQBuAHMAcABhAHIAZQBuAGMAeQAiACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIgA+ADAAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAcgBlAGYAbABlAGMAdABpAHYAaQB0AHkAIgAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAwADwALwBwAGEAcgBhAG0AZQB0AGUAcgA+AA0ACgAJAAkACQAJAAkAPABwAGEAcgBhAG0AZQB0AGUAcgAgAG4AYQBtAGUAPQAiAGkAbwByACIAIAB0AH"
    "kAcABlAD0AIgBkAG8AdQBiAGwAZQAiAD4AMQA8AC8AcABhAHIAYQBtAGUAdABlAHIAPgANAAoACQAJAAkACQAJADwAcABhAHIAYQBtAGUAdABlAHIAIABuAGEAbQBlAD0AIgB0AHIAYQBuAHMAcABhAHIAZQBuAGMAeQAtAGMAbwBsAG8AcgAiACAAdAB5AHAAZQA9ACIAYwBvAGwAbwByACIAPgAxACwAMQAsADEALAAxADwALwBwAGEAcgBhAG0AZQB0AGUAcgA+AA0ACgAJAAkACQAJAAkAPABwAGEAcgBhAG0AZQB0AGUAcgAgAG4AYQBtAGUAPQAiAHIAZQBmAGwAZQBjAHQAaQB2AGkAdAB5AC0AYwBvAGwAbwByACIAIAB0AHkAcABlAD0AIgBjAG8AbABvAHIAIgA+ADEALAAxACwAMQAsADEAPAAvAHAAYQByAGEAbQBlAHQAZQBy"
    "AD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAZQBtAGkAcwBzAGkAbwBuACIAIAB0AHkAcABlAD0AIgBjAG8AbABvAHIAIgA+ADAALAAwACwAMAAsADEAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAYQBtAGIAaQBlAG4AdAAiACAAdAB5AHAAZQA9ACIAYwBvAGwAbwByACIAPgAwACwAMAAsADAALAAxADwALwBwAGEAcgBhAG0AZQB0AGUAcgA+AA0ACgAJAAkACQAJAAkAPABwAGEAcgBhAG0AZQB0AGUAcgAgAG4AYQBtAGUAPQAiAGYAbABhAG0AaQBuAGcAbwAtAGwAaQBiAHIAYQByAHkAIgAgAHQAeQ"
    "BwAGUAPQAiAHMAdAByAGkAbgBnACIALwA+AA0ACgAJAAkACQAJAAkAPABwAGEAcgBhAG0AZQB0AGUAcgAgAG4AYQBtAGUAPQAiAGQAaQBzAGEAYgBsAGUALQBsAGkAZwBoAHQAaQBuAGcAIgAgAHQAeQBwAGUAPQAiAGIAbwBvAGwAIgA+AGYAYQBsAHMAZQA8AC8AcABhAHIAYQBtAGUAdABlAHIAPgANAAoACQAJAAkACQAJADwAcABhAHIAYQBtAGUAdABlAHIAIABuAGEAbQBlAD0AIgBmAHIAZQBzAG4AZQBsAC0AZQBuAGEAYgBsAGUAZAAiACAAdAB5AHAAZQA9ACIAYgBvAG8AbAAiAD4AZgBhAGwAcwBlADwALwBwAGEAcgBhAG0AZQB0AGUAcgA+AA0ACgAJAAkACQAJAAkAPABwAGEAcgBhAG0AZQB0AGUAcgAgAG4AYQBtAGUA"
    "PQAiAHAAbwBsAGkAcwBoAC0AYQBtAG8AdQBuAHQAIgAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAxADwALwBwAGEAcgBhAG0AZQB0AGUAcgA+AA0ACgAJAAkACQAJAAkAPABwAGEAcgBhAG0AZQB0AGUAcgAgAG4AYQBtAGUAPQAiAGMAbABhAHIAaQB0AHkALQBhAG0AbwB1AG4AdAAiACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIgA+ADEAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAYQBsAHAAaABhAC0AdAByAGEAbgBzAHAAYQByAGUAbgBjAHkAIgAgAHQAeQBwAGUAPQAiAGIAbwBvAGwAIgA+AHQAcgB1AGUAPAAvAHAAYQByAG"
    "EAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAYgBpAHQAbQBhAHAALQB0AGUAeAB0AHUAcgBlACIAIAB0AHkAcABlAD0AIgAiAC8APgANAAoACQAJAAkACQAJADwAcABhAHIAYQBtAGUAdABlAHIAIABuAGEAbQBlAD0AIgBiAGkAdABtAGEAcAAtAHQAZQB4AHQAdQByAGUALQBvAG4AIgAgAHQAeQBwAGUAPQAiAGIAbwBvAGwAIgA+AGYAYQBsAHMAZQA8AC8AcABhAHIAYQBtAGUAdABlAHIAPgANAAoACQAJAAkACQAJADwAcABhAHIAYQBtAGUAdABlAHIAIABuAGEAbQBlAD0AIgBiAGkAdABtAGEAcAAtAHQAZQB4AHQAdQByAGUALQBkAG8AdQBiAGwAZQAtAGEAbQBv"
    "AHUAbgB0ACIAIAB0AHkAcABlAD0AIgBkAG8AdQBiAGwAZQAiAD4AMQA8AC8AcABhAHIAYQBtAGUAdABlAHIAPgANAAoACQAJAAkACQAJADwAcABhAHIAYQBtAGUAdABlAHIAIABuAGEAbQBlAD0AIgBiAGkAdABtAGEAcAAtAHQAZQB4AHQAdQByAGUALQBhAG0AbwB1AG4AdAAiACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIgA+ADEAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAYgB1AG0AcAAtAHQAZQB4AHQAdQByAGUAIgAgAHQAeQBwAGUAPQAiACIALwA+AA0ACgAJAAkACQAJAAkAPABwAGEAcgBhAG0AZQB0AGUAcgAgAG4AYQBtAGUAPQ"
    "AiAGIAdQBtAHAALQB0AGUAeAB0AHUAcgBlAC0AbwBuACIAIAB0AHkAcABlAD0AIgBiAG8AbwBsACIAPgBmAGEAbABzAGUAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAYgB1AG0AcAAtAHQAZQB4AHQAdQByAGUALQBkAG8AdQBiAGwAZQAtAGEAbQBvAHUAbgB0ACIAIAB0AHkAcABlAD0AIgBkAG8AdQBiAGwAZQAiAD4AMAAuADMAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAYgB1AG0AcAAtAHQAZQB4AHQAdQByAGUALQBhAG0AbwB1AG4AdAAiACAAdAB5AHAA"
    "ZQA9ACIAZABvAHUAYgBsAGUAIgA+ADAALgAzADwALwBwAGEAcgBhAG0AZQB0AGUAcgA+AA0ACgAJAAkACQAJAAkAPABwAGEAcgBhAG0AZQB0AGUAcgAgAG4AYQBtAGUAPQAiAHQAcgBhAG4AcwBwAGEAcgBlAG4AYwB5AC0AdABlAHgAdAB1AHIAZQAiACAAdAB5AHAAZQA9ACIAIgAvAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAdAByAGEAbgBzAHAAYQByAGUAbgBjAHkALQB0AGUAeAB0AHUAcgBlAC0AbwBuACIAIAB0AHkAcABlAD0AIgBiAG8AbwBsACIAPgBmAGEAbABzAGUAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByAC"
    "AAbgBhAG0AZQA9ACIAdAByAGEAbgBzAHAAYQByAGUAbgBjAHkALQB0AGUAeAB0AHUAcgBlAC0AZABvAHUAYgBsAGUALQBhAG0AbwB1AG4AdAAiACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIgA+ADEAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAdAByAGEAbgBzAHAAYQByAGUAbgBjAHkALQB0AGUAeAB0AHUAcgBlAC0AYQBtAG8AdQBuAHQAIgAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAxADwALwBwAGEAcgBhAG0AZQB0AGUAcgA+AA0ACgAJAAkACQAJAAkAPABwAGEAcgBhAG0AZQB0AGUAcgAgAG4AYQBtAGUAPQAiAGUAbgB2"
    "AGkAcgBvAG4AbQBlAG4AdAAtAHQAZQB4AHQAdQByAGUAIgAgAHQAeQBwAGUAPQAiACIALwA+AA0ACgAJAAkACQAJAAkAPABwAGEAcgBhAG0AZQB0AGUAcgAgAG4AYQBtAGUAPQAiAGUAbgB2AGkAcgBvAG4AbQBlAG4AdAAtAHQAZQB4AHQAdQByAGUALQBvAG4AIgAgAHQAeQBwAGUAPQAiAGIAbwBvAGwAIgA+AGYAYQBsAHMAZQA8AC8AcABhAHIAYQBtAGUAdABlAHIAPgANAAoACQAJAAkACQAJADwAcABhAHIAYQBtAGUAdABlAHIAIABuAGEAbQBlAD0AIgBlAG4AdgBpAHIAbwBuAG0AZQBuAHQALQB0AGUAeAB0AHUAcgBlAC0AZABvAHUAYgBsAGUALQBhAG0AbwB1AG4AdAAiACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIg"
    "A+ADEAPAAvAHAAYQByAGEAbQBlAHQAZQByAD4ADQAKAAkACQAJAAkACQA8AHAAYQByAGEAbQBlAHQAZQByACAAbgBhAG0AZQA9ACIAZQBuAHYAaQByAG8AbgBtAGUAbgB0AC0AdABlAHgAdAB1AHIAZQAtAGEAbQBvAHUAbgB0ACIAIAB0AHkAcABlAD0AIgBkAG8AdQBiAGwAZQAiAD4AMQA8AC8AcABhAHIAYQBtAGUAdABlAHIAPgANAAoACQAJAAkACQA8AC8AcABhAHIAYQBtAGUAdABlAHIAcwAtAHYAOAA+AA0ACgAJAAkACQAJADwAcABhAHIAYQBtAGUAdABlAHIAcwA+AA0ACgAJAAkACQAJAAkAPAB2AGUAcgBzAGkAbwBuACAAdAB5AHAAZQA9ACIAaQBuAHQAIgA+ADIAPAAvAHYAZQByAHMAaQBvAG4APgANAAoACQAJAAkA"
    "CQAJADwAZABpAGYAZgB1AHMAZQAgAHQAeQBwAGUAPQAiAGMAbwBsAG8AcgAiAD4AMAAuADkAOAAwADMAOQAyADEANQA4ADAAMwAxADQANgA0ACwAMAAuADkAOAAwADMAOQAyADEANQA4ADAAMwAxADQANgA0ACwAMAAuADkAOAAwADMAOQAyADEANQA4ADAAMwAxADQANgA0ACwAMQA8AC8AZABpAGYAZgB1AHMAZQA+AA0ACgAJAAkACQAJAAkAPABzAHAAZQBjAHUAbABhAHIAIAB0AHkAcABlAD0AIgBjAG8AbABvAHIAIgA+ADEALAAxACwAMQAsADEAPAAvAHMAcABlAGMAdQBsAGEAcgA+AA0ACgAJAAkACQAJAAkAPABzAGgAaQBuAGUAIAB0AHkAcABlAD0AIgBkAG8AdQBiAGwAZQAiAD4AMAA8AC8AcwBoAGkAbgBlAD4ADQAKAA"
    "kACQAJAAkACQA8AHQAcgBhAG4AcwBwAGEAcgBlAG4AYwB5ACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIgA+ADAAPAAvAHQAcgBhAG4AcwBwAGEAcgBlAG4AYwB5AD4ADQAKAAkACQAJAAkACQA8AHIAZQBmAGwAZQBjAHQAaQB2AGkAdAB5ACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIgA+ADAAPAAvAHIAZQBmAGwAZQBjAHQAaQB2AGkAdAB5AD4ADQAKAAkACQAJAAkACQA8AGkAbwByACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIgA+ADEAPAAvAGkAbwByAD4ADQAKAAkACQAJAAkACQA8AHQAcgBhAG4AcwBwAGEAcgBlAG4AYwB5AC0AYwBvAGwAbwByACAAdAB5AHAAZQA9ACIAYwBvAGwAbwByACIAPgAxACwAMQAs"
    "ADEALAAxADwALwB0AHIAYQBuAHMAcABhAHIAZQBuAGMAeQAtAGMAbwBsAG8AcgA+AA0ACgAJAAkACQAJAAkAPAByAGUAZgBsAGUAYwB0AGkAdgBpAHQAeQAtAGMAbwBsAG8AcgAgAHQAeQBwAGUAPQAiAGMAbwBsAG8AcgAiAD4AMQAsADEALAAxACwAMQA8AC8AcgBlAGYAbABlAGMAdABpAHYAaQB0AHkALQBjAG8AbABvAHIAPgANAAoACQAJAAkACQAJADwAZQBtAGkAcwBzAGkAbwBuACAAdAB5AHAAZQA9ACIAYwBvAGwAbwByACIAPgAwACwAMAAsADAALAAxADwALwBlAG0AaQBzAHMAaQBvAG4APgANAAoACQAJAAkACQAJADwAYQBtAGIAaQBlAG4AdAAgAHQAeQBwAGUAPQAiAGMAbwBsAG8AcgAiAD4AMAAsADAALAAwACwAMQ"
    "A8AC8AYQBtAGIAaQBlAG4AdAA+AA0ACgAJAAkACQAJAAkAPABmAGwAYQBtAGkAbgBnAG8ALQBsAGkAYgByAGEAcgB5ACAAdAB5AHAAZQA9ACIAcwB0AHIAaQBuAGcAIgAvAD4ADQAKAAkACQAJAAkACQA8AGQAaQBzAGEAYgBsAGUALQBsAGkAZwBoAHQAaQBuAGcAIAB0AHkAcABlAD0AIgBiAG8AbwBsACIAPgBmAGEAbABzAGUAPAAvAGQAaQBzAGEAYgBsAGUALQBsAGkAZwBoAHQAaQBuAGcAPgANAAoACQAJAAkACQAJADwAZgByAGUAcwBuAGUAbAAtAGUAbgBhAGIAbABlAGQAIAB0AHkAcABlAD0AIgBiAG8AbwBsACIAPgBmAGEAbABzAGUAPAAvAGYAcgBlAHMAbgBlAGwALQBlAG4AYQBiAGwAZQBkAD4ADQAKAAkACQAJAAkA"
    "CQA8AHAAbwBsAGkAcwBoAC0AYQBtAG8AdQBuAHQAIAB0AHkAcABlAD0AIgBkAG8AdQBiAGwAZQAiAD4AMQA8AC8AcABvAGwAaQBzAGgALQBhAG0AbwB1AG4AdAA+AA0ACgAJAAkACQAJAAkAPABjAGwAYQByAGkAdAB5AC0AYQBtAG8AdQBuAHQAIAB0AHkAcABlAD0AIgBkAG8AdQBiAGwAZQAiAD4AMQA8AC8AYwBsAGEAcgBpAHQAeQAtAGEAbQBvAHUAbgB0AD4ADQAKAAkACQAJAAkACQA8AGEAbABwAGgAYQAtAHQAcgBhAG4AcwBwAGEAcgBlAG4AYwB5ACAAdAB5AHAAZQA9ACIAYgBvAG8AbAAiAD4AdAByAHUAZQA8AC8AYQBsAHAAaABhAC0AdAByAGEAbgBzAHAAYQByAGUAbgBjAHkAPgANAAoACQAJAAkACQAJADwAYgBpAH"
    "QAbQBhAHAALQB0AGUAeAB0AHUAcgBlACAAdAB5AHAAZQA9ACIAIgAvAD4ADQAKAAkACQAJAAkACQA8AGIAaQB0AG0AYQBwAC0AdABlAHgAdAB1AHIAZQAtAG8AbgAgAHQAeQBwAGUAPQAiAGIAbwBvAGwAIgA+AGYAYQBsAHMAZQA8AC8AYgBpAHQAbQBhAHAALQB0AGUAeAB0AHUAcgBlAC0AbwBuAD4ADQAKAAkACQAJAAkACQA8AGIAaQB0AG0AYQBwAC0AdABlAHgAdAB1AHIAZQAtAGQAbwB1AGIAbABlAC0AYQBtAG8AdQBuAHQAIAB0AHkAcABlAD0AIgBkAG8AdQBiAGwAZQAiAD4AMQA8AC8AYgBpAHQAbQBhAHAALQB0AGUAeAB0AHUAcgBlAC0AZABvAHUAYgBsAGUALQBhAG0AbwB1AG4AdAA+AA0ACgAJAAkACQAJAAkAPABi"
    "AGkAdABtAGEAcAAtAHQAZQB4AHQAdQByAGUALQBhAG0AbwB1AG4AdAAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAxADwALwBiAGkAdABtAGEAcAAtAHQAZQB4AHQAdQByAGUALQBhAG0AbwB1AG4AdAA+AA0ACgAJAAkACQAJAAkAPABiAHUAbQBwAC0AdABlAHgAdAB1AHIAZQAgAHQAeQBwAGUAPQAiACIALwA+AA0ACgAJAAkACQAJAAkAPABiAHUAbQBwAC0AdABlAHgAdAB1AHIAZQAtAG8AbgAgAHQAeQBwAGUAPQAiAGIAbwBvAGwAIgA+AGYAYQBsAHMAZQA8AC8AYgB1AG0AcAAtAHQAZQB4AHQAdQByAGUALQBvAG4APgANAAoACQAJAAkACQAJADwAYgB1AG0AcAAtAHQAZQB4AHQAdQByAGUALQBkAG8AdQBiAGwAZQ"
    "AtAGEAbQBvAHUAbgB0ACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIgA+ADAALgAzADwALwBiAHUAbQBwAC0AdABlAHgAdAB1AHIAZQAtAGQAbwB1AGIAbABlAC0AYQBtAG8AdQBuAHQAPgANAAoACQAJAAkACQAJADwAYgB1AG0AcAAtAHQAZQB4AHQAdQByAGUALQBhAG0AbwB1AG4AdAAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAwAC4AMwA8AC8AYgB1AG0AcAAtAHQAZQB4AHQAdQByAGUALQBhAG0AbwB1AG4AdAA+AA0ACgAJAAkACQAJAAkAPAB0AHIAYQBuAHMAcABhAHIAZQBuAGMAeQAtAHQAZQB4AHQAdQByAGUAIAB0AHkAcABlAD0AIgAiAC8APgANAAoACQAJAAkACQAJADwAdAByAGEAbgBzAHAAYQByAGUA"
    "bgBjAHkALQB0AGUAeAB0AHUAcgBlAC0AbwBuACAAdAB5AHAAZQA9ACIAYgBvAG8AbAAiAD4AZgBhAGwAcwBlADwALwB0AHIAYQBuAHMAcABhAHIAZQBuAGMAeQAtAHQAZQB4AHQAdQByAGUALQBvAG4APgANAAoACQAJAAkACQAJADwAdAByAGEAbgBzAHAAYQByAGUAbgBjAHkALQB0AGUAeAB0AHUAcgBlAC0AZABvAHUAYgBsAGUALQBhAG0AbwB1AG4AdAAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAxADwALwB0AHIAYQBuAHMAcABhAHIAZQBuAGMAeQAtAHQAZQB4AHQAdQByAGUALQBkAG8AdQBiAGwAZQAtAGEAbQBvAHUAbgB0AD4ADQAKAAkACQAJAAkACQA8AHQAcgBhAG4AcwBwAGEAcgBlAG4AYwB5AC0AdABlAH"
    "gAdAB1AHIAZQAtAGEAbQBvAHUAbgB0ACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIgA+ADEAPAAvAHQAcgBhAG4AcwBwAGEAcgBlAG4AYwB5AC0AdABlAHgAdAB1AHIAZQAtAGEAbQBvAHUAbgB0AD4ADQAKAAkACQAJAAkACQA8AGUAbgB2AGkAcgBvAG4AbQBlAG4AdAAtAHQAZQB4AHQAdQByAGUAIAB0AHkAcABlAD0AIgAiAC8APgANAAoACQAJAAkACQAJADwAZQBuAHYAaQByAG8AbgBtAGUAbgB0AC0AdABlAHgAdAB1AHIAZQAtAG8AbgAgAHQAeQBwAGUAPQAiAGIAbwBvAGwAIgA+AGYAYQBsAHMAZQA8AC8AZQBuAHYAaQByAG8AbgBtAGUAbgB0AC0AdABlAHgAdAB1AHIAZQAtAG8AbgA+AA0ACgAJAAkACQAJAAkAPABl"
    "AG4AdgBpAHIAbwBuAG0AZQBuAHQALQB0AGUAeAB0AHUAcgBlAC0AZABvAHUAYgBsAGUALQBhAG0AbwB1AG4AdAAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAxADwALwBlAG4AdgBpAHIAbwBuAG0AZQBuAHQALQB0AGUAeAB0AHUAcgBlAC0AZABvAHUAYgBsAGUALQBhAG0AbwB1AG4AdAA+AA0ACgAJAAkACQAJAAkAPABlAG4AdgBpAHIAbwBuAG0AZQBuAHQALQB0AGUAeAB0AHUAcgBlAC0AYQBtAG8AdQBuAHQAIAB0AHkAcABlAD0AIgBkAG8AdQBiAGwAZQAiAD4AMQA8AC8AZQBuAHYAaQByAG8AbgBtAGUAbgB0AC0AdABlAHgAdAB1AHIAZQAtAGEAbQBvAHUAbgB0AD4ADQAKAAkACQAJAAkAPAAvAHAAYQByAGEAbQ"
    "BlAHQAZQByAHMAPgANAAoACQAJAAkACQA8AHMAaQBtAHUAbABhAHQAaQBvAG4APgANAAoACQAJAAkACQAJADwAYQBtAGIAaQBlAG4AdAAgAHQAeQBwAGUAPQAiAGMAbwBsAG8AcgAiAD4AMAAsADAALAAwACwAMQA8AC8AYQBtAGIAaQBlAG4AdAA+AA0ACgAJAAkACQAJAAkAPABkAGkAZgBmAHUAcwBlACAAdAB5AHAAZQA9ACIAYwBvAGwAbwByACIAPgAwAC4AOQA4ADAAMwA5ADIAMQA1ADgAMAAzADEANAA2ADQALAAwAC4AOQA4ADAAMwA5ADIAMQA1ADgAMAAzADEANAA2ADQALAAwAC4AOQA4ADAAMwA5ADIAMQA1ADgAMAAzADEANAA2ADQALAAxADwALwBkAGkAZgBmAHUAcwBlAD4ADQAKAAkACQAJAAkACQA8AGUAbQBpAHMA"
    "cwBpAG8AbgAgAHQAeQBwAGUAPQAiAGMAbwBsAG8AcgAiAD4AMAAsADAALAAwACwAMQA8AC8AZQBtAGkAcwBzAGkAbwBuAD4ADQAKAAkACQAJAAkACQA8AHMAcABlAGMAdQBsAGEAcgAgAHQAeQBwAGUAPQAiAGMAbwBsAG8AcgAiAD4AMQAsADEALAAxACwAMQA8AC8AcwBwAGUAYwB1AGwAYQByAD4ADQAKAAkACQAJAAkACQA8AHIAZQBmAGwAZQBjAHQAaQBvAG4AIAB0AHkAcABlAD0AIgBjAG8AbABvAHIAIgA+ADEALAAxACwAMQAsADEAPAAvAHIAZQBmAGwAZQBjAHQAaQBvAG4APgANAAoACQAJAAkACQAJADwAcwBoAGkAbgBlACAAdAB5AHAAZQA9ACIAZABvAHUAYgBsAGUAIgA+ADAAPAAvAHMAaABpAG4AZQA+AA0ACgAJAA"
    "kACQAJAAkAPAB0AHIAYQBuAHMAcABhAHIAZQBuAGMAeQAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAwADwALwB0AHIAYQBuAHMAcABhAHIAZQBuAGMAeQA+AA0ACgAJAAkACQAJAAkAPAByAGUAZgBsAGUAYwB0AGkAdgBpAHQAeQAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAwADwALwByAGUAZgBsAGUAYwB0AGkAdgBpAHQAeQA+AA0ACgAJAAkACQAJAAkAPABpAG8AcgAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAxADwALwBpAG8AcgA+AA0ACgAJAAkACQAJAAkAPABmAHIAZQBzAG4AZQBsAC0AZQBuAGEAYgBsAGUAZAAgAHQAeQBwAGUAPQAiAGIAbwBvAGwAIgA+AGYAYQBsAHMAZQA8AC8AZgBy"
    "AGUAcwBuAGUAbAAtAGUAbgBhAGIAbABlAGQAPgANAAoACQAJAAkACQAJADwAcABvAGwAaQBzAGgALQBhAG0AbwB1AG4AdAAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAxADwALwBwAG8AbABpAHMAaAAtAGEAbQBvAHUAbgB0AD4ADQAKAAkACQAJAAkACQA8AGMAbABhAHIAaQB0AHkALQBhAG0AbwB1AG4AdAAgAHQAeQBwAGUAPQAiAGQAbwB1AGIAbABlACIAPgAxADwALwBjAGwAYQByAGkAdAB5AC0AYQBtAG8AdQBuAHQAPgANAAoACQAJAAkACQAJADwAdAByAGEAbgBzAHAAYQByAGUAbgB0ACAAdAB5AHAAZQA9ACIAYwBvAGwAbwByACIAPgAxACwAMQAsADEALAAxADwALwB0AHIAYQBuAHMAcABhAHIAZQBuAHQAPg"
    "ANAAoACQAJAAkACQAJADwAaQBzAC0AcABoAHkAcwBpAGMAYQBsAGwAeQAtAGIAYQBzAGUAZAAgAHQAeQBwAGUAPQAiAGIAbwBvAGwAIgA+AGYAYQBsAHMAZQA8AC8AaQBzAC0AcABoAHkAcwBpAGMAYQBsAGwAeQAtAGIAYQBzAGUAZAA+AA0ACgAJAAkACQAJADwALwBzAGkAbQB1AGwAYQB0AGkAbwBuAD4ADQAKAAkACQAJADwALwBtAGEAdABlAHIAaQBhAGwAPgANAAoACQAJADwALwBtAGEAdABlAHIAaQBhAGwALQBzAGUAYwB0AGkAbwBuAD4ADQAKAAkAPAAvAHIAZQBuAGQAZQByAC0AYwBvAG4AdABlAG4AdAAtAG0AYQBuAGEAZwBlAHIALQBkAG8AYwB1AG0AZQBuAHQAPgANAAoAPAAvAHgAbQBsAD4ADQAKAA==";

    const auto len = wcslen(wszBase64);
    auto* p = new char[len+1];
    memset(p, 0, len);
    ON_Base64::Decode(wszBase64, p);
#ifdef ON_RUNTIME_WIN
    sXML = reinterpret_cast<const wchar_t*>(p);
#else
    const auto* pUTF16 = (ON__UINT16*)p;
    unsigned int error_status = 0;
    int error_mask = 0, error_code_point = 0;
    const auto num_chars = ON_ConvertUTF16ToUTF32(false, pUTF16, -1, nullptr, 0, &error_status, error_mask, error_code_point, nullptr);
    auto* string_buf = sXML.SetLength(num_chars);
    ON_ASSERT(sizeof(wchar_t) == sizeof(ON__UINT32));
    auto* pWide = reinterpret_cast<ON__UINT32*>(string_buf);
    ON_ConvertUTF16ToUTF32(false, pUTF16, -1, pWide, num_chars+1, &error_status, error_mask, error_code_point, nullptr);
#endif
    delete[] p;
}

static const auto*  szQuick =  "The quick brown fox jumps over the lazy dog";
static const auto* wszQuick = L"The quick brown fox jumps over the lazy dog";

bool ON_RunXMLTests(const wchar_t* test_folder)
{
//  ::SetThreadAffinityMask(::GetCurrentThread(), 0x01);

  // Remember the current node and property counts.
  const auto nodeCount = long(g_lNodeCount);
  const auto propCount = long(g_lPropertyCount);

  // Test variant.
  {
    ON_wString s = L"123.456e-10";
    Validate(s.IsValidRealNumber());
    Validate(!s.IsValidIntegerNumber());
  }
  {
    ON_wString s = L"123456";
    Validate(s.IsValidIntegerNumber());
    Validate(s.IsValidRealNumber());
  }
  {
    ON_wString s = L"Quack";
    Validate(!s.IsValidIntegerNumber());
    Validate(!s.IsValidRealNumber());
  }
  {
    ON_XMLVariant v(true);
    Validate(v.AsBool() == true);
    Validate(v.AsInteger() == 1);
    Validate(v.AsFloat() == 1.0f);
    Validate(v.AsDouble() == 1.0);
    Validate(v.AsString() == L"true");
  }
  {
    ON_XMLVariant v(25);
    Validate(v.AsBool() == true);
    Validate(v.AsInteger() == 25);
    Validate(v.AsFloat() == 25.0f);
    Validate(v.AsDouble() == 25.0);
    Validate(v.AsString() == L"25");
  }
  {
    ON_XMLVariant v(63.5f);
    Validate(v.AsBool() == true);
    Validate(v.AsInteger() == 63);
    Validate(v.AsFloat() == 63.5f);
    Validate(v.AsDouble() == 63.5);
    Validate(v.AsString() == L"63.5");
  }
  {
    ON_XMLVariant v(77.9);
    Validate(v.AsBool() == true);
    Validate(v.AsInteger() == 77);
    Validate(v.AsFloat() == 77.9f);
    Validate(v.AsDouble() == 77.9);
    Validate(v.AsString() == L"77.9");
  }
  {
    ON_4fColor col(ON_Color(12, 34, 56, 0));
    ON_XMLVariant v(col);
    Validate(v.AsColor().Compare(col) == 0);

    auto s = v.AsString();
    auto pos = s.Find(L",");
    auto s1 = s.Left(pos);
    s = s.Mid(pos+1);
    Validate(s1.Left(8) == L"0.047058");
    pos = s.Find(L",");
    s1 = s.Left(pos);
    s = s.Mid(pos+1);
    Validate(s1.Left(8) == L"0.133333");
    pos = s.Find(L",");
    s1 = s.Left(pos);
    s = s.Mid(pos+1);
    Validate(s1.Left(8) == L"0.219607");
    Validate(s == L"1");

    const auto p = v.As4dPoint();
    Validate(p[0] == col.Red());
    Validate(p[1] == col.Green());
    Validate(p[2] == col.Blue());
    Validate(p[3] == col.Alpha());
  }
  {
    ON_XMLVariant v(L"123, 456");
    const auto p = v.As2dPoint();
    Validate(p[0] == 123.0);
    Validate(p[1] == 456.0);
    Validate(v.AsString().Length() == 8);
    Validate(v.AsString() == L"123, 456");
  }
  {
    ON_XMLVariant v(L"123, 456, 789");
    const auto p = v.As3dPoint();
    Validate(p[0] == 123.0);
    Validate(p[1] == 456.0);
    Validate(p[2] == 789.0);
    Validate(v.AsString().Length() == 13);
    Validate(v.AsString() == L"123, 456, 789");
  }
  {
    ON_XMLVariant v(L"123, 2.4, 33.9, 456.");
    const auto p = v.As4dPoint();
    Validate(p[0] == 123.0);
    Validate(p[1] == 2.4);
    Validate(p[2] == 33.9);
    Validate(p[3] == 456.0);
    Validate(v.AsString().Length() == 20);
    Validate(v.AsString() == L"123, 2.4, 33.9, 456.");
  }
  {
    ON_wString sTime = L"2021.11.21_02:34:00";
    ON_XMLVariant v1(sTime);
    auto time = v1.AsTime();
    ON_XMLVariant v2(time);
    Validate(v2.AsString().Length() == 19);
    Validate(v2.AsString() == sTime);
  }
  {
    ON_Buffer b;
    b.Write(43, szQuick);
    ON_XMLVariant v1(b);
    const auto& s = v1.AsString();
    Validate(s == L"base64:VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==");
  }

  const auto* wszSentence = L"The quick brown fox";

  const ON_wString sSentence = wszSentence;

  // Test new ON_wString functions.
  for (int i = 0; i < sSentence.Length(); i++)
  {
    ON_wString s = sSentence;
    if (s.TruncateMid(i))
    {
      Validate(s == sSentence.Mid(i));
    }
  }
 
  {
    Validate(sSentence.StartsWith(L"The quick"));
    Validate(sSentence.StartsWithNoCase(L"the quick"));
    Validate(sSentence.StartsWithNoCase(L"THE QUICK"));
  }
  {
    ON_wString s = sSentence;
    ON_wString t = s; // t is a new reference to the same string.
    Validate(s.Insert(3, L'!', 4));
    Validate(s == L"The!!!! quick brown fox"); // Validate that chars were inserted.
    Validate(t == wszSentence);                // Validate that 't' is not corrupted.

    t = s; // t is a new reference to the same string.
    Validate(s.Insert(s.Length(), L'!', 1));
    Validate(s == L"The!!!! quick brown fox!"); // Validate that chars were inserted.
    Validate(t == L"The!!!! quick brown fox");  // Validate that 't' is not corrupted.

    s = sSentence + L"!";
    t = s; // t is a new reference to the same string.
    Validate(s.Insert(s.Length()-1, L" jumps over the lazy dog"));
    Validate(s == L"The quick brown fox jumps over the lazy dog!"); // Validate that chars were inserted.
    Validate(t == L"The quick brown fox!");                         // Validate that 't' is not corrupted.

    ON_wString z;
    Validate( z.Insert(0, 'x', 1));
    Validate(!z.Insert(0, 'x', -1));
    Validate(!z.Insert(-1, 'x', 1));
    Validate(!z.Insert(-1, L"x"));
    Validate(!z.Insert(0, nullptr));
  }

  // Test XML node.
  {
    ON_XMLNode node(L"parent");
    node.AttachChildNode(new ON_XMLNode(L"child"));
    auto s = node.String();
    s.RemoveWhiteSpace();
    Validate(s == L"<parent><child/></parent>");
  }

  // Test XML properties.
  {
    const auto* szPropName1 = L"number";
    const auto* szPropName2 = L"time";
    ON_XMLNode node(L"parent");
    ON_XMLProperty prop1(szPropName1, 25);
    node.SetProperty(prop1);
    const auto time = time_t(617283945);
    ON_XMLProperty prop2(szPropName2, time);
    node.SetProperty(prop2);
    auto s = node.String();
    s.RemoveWhiteSpace();
    Validate(s == L"<parenttime=\"1989.07.24_04:45:45\"number=\"25\"/>");

    auto pi = node.GetPropertyIterator(true); // Sorted.
    auto* pProp = pi.GetNextProperty();
    Validate((nullptr != pProp) && pProp->Name().IsEmpty());
    pProp = pi.GetNextProperty();
    Validate((nullptr != pProp) && (pProp->Name() == szPropName1));
    pProp = pi.GetNextProperty();
    Validate((nullptr != pProp) && (pProp->Name() == szPropName2));
    pProp = pi.GetNextProperty();
    Validate(nullptr == pProp);

    Validate(node.RemoveProperty(szPropName1));
    Validate(node.RemoveProperty(szPropName2));
    s = node.String();
    s.RemoveWhiteSpace();
    Validate(s == L"<parent/>");
    node.SetProperty(prop1);

    pProp = node.GetNamedProperty(szPropName1);
    Validate(pProp != nullptr);
    if (pProp != nullptr)
      pProp->SetValue(23.4);
    s = node.String();
    s.RemoveWhiteSpace();
    Validate(s == L"<parentnumber=\"23.4\"/>");

    node.RemoveAllProperties();
    s = node.String();
    s.RemoveWhiteSpace();
    Validate(s == L"<parent/>");
    node.GetDefaultProperty().SetValue(true);
    s = node.String();
    s.RemoveWhiteSpace();
    Validate(s == L"<parent>true</parent>");
  }

  // Test Unicode text file.
  const ON_wString sFolder = test_folder;
  {
    const auto sFile = sFolder + L"UTF8.txt";
    ON_UnicodeTextFile file(ON_UnicodeTextFile::Types::UTF8);

    if (file.Open(sFile, ON_UnicodeTextFile::Modes::Write))
    {
      Validate(file.WriteString(wszQuick));
      Validate(file.Close());
    }

    if (file.Open(sFile, ON_UnicodeTextFile::Modes::Read))
    {
      ON_wString s;
      Validate(file.ReadString(s));
      Validate(s == wszQuick);
      Validate(file.Close());
    }
  }
  {
    const auto sFile = sFolder + L"UTF16.txt";
    ON_UnicodeTextFile file(ON_UnicodeTextFile::Types::UTF16);

    if (file.Open(sFile, ON_UnicodeTextFile::Modes::Write))
    {
      Validate(file.WriteString(wszQuick));
      Validate(file.Close());
    }

    if (file.Open(sFile, ON_UnicodeTextFile::Modes::Read))
    {
      ON_wString s;
      Validate(file.ReadString(s));
      Validate(s == wszQuick);
      Validate(file.Close());
    }
  }

  // Test XML root node.
  {
    const auto* szPropName1 = L"number";
    const auto* szPropName2 = L"time";
    ON_XMLRootNode root;
    ON_XMLProperty prop1(szPropName1, 25);
    root.SetProperty(prop1);
    const auto time = time_t(617283945);
    ON_XMLProperty prop2(szPropName2, time);
    root.SetProperty(prop2);
    auto s = root.String();
    s.RemoveWhiteSpace();
    Validate(s == L"<xmltime=\"1989.07.24_04:45:45\"number=\"25\"/>");

    const auto sFile = sFolder + ON_FileSystemPath::DirectorySeparator + L"UTF16-2.txt";
    Validate(root.WriteToFile(sFile));
    Validate(root.ReadFromFile(sFile));
  }

  {
    ON_wString sXML;
    GetRDKTestXML(sXML);

    ON_XMLRootNode root;
    root.ReadFromStream(sXML.Array());
    auto* pNode = root.GetNodeAtPath(L"render-content-manager-document/material-section");
    Validate(pNode != nullptr);

    const auto sFile = sFolder + ON_FileSystemPath::DirectorySeparator + L"UTF16-3.txt";
    Validate(root.WriteToFile(sFile));
  }

#ifdef ON_RUNTIME_WIN
  // Base 64 speed test.
  LARGE_INTEGER start, now, freq;
  ::QueryPerformanceFrequency(&freq);

  const auto* buf = szQuick;
  const auto buf_len = strlen(buf);

  ON_wString sBase64;

#ifdef _DEBUG
  const int numIterations = 100000;
#else
  const int numIterations = 100000000;
#endif

  ::QueryPerformanceCounter(&start);
  for (int i = 0; i < numIterations; i++)
  {
    ON_Base64::Encode(buf, buf_len, sBase64, false);
  }
  ::QueryPerformanceCounter(&now);

  ON_wString sOutput;
  sOutput.Format(L"Time for %u Base64 iterations: %g seconds", numIterations, double(now.QuadPart - start.QuadPart) / double(freq.QuadPart));
  OUTPUT_DEBUG_STRING_EOL(sOutput);

  sBase64.Empty();
  ON_Base64EncodeStream bes;
  bes.SetCallback(Base64Callback, nullptr);

  ::QueryPerformanceCounter(&start);
  for (int i = 0; i < numIterations; i++)
  {
    CallbackDone = 0;
    bes.Begin();
    bes.In(buf_len, buf);
    bes.End();
  }
  ::QueryPerformanceCounter(&now);

  sOutput.Format(L"Time for %u Base64 iterations: %g seconds", numIterations, double(now.QuadPart - start.QuadPart) / double(freq.QuadPart));
  OUTPUT_DEBUG_STRING_EOL(sOutput);

  sBase64 = CallbackBuffer;
#endif

  // Test critical section.
  OUTPUT_DEBUG_STRING_EOL(L"Characters should not be mixed");
  std::thread th1(ThreadFunc, L'*');
  std::thread th2(ThreadFunc, L'$');
  th1.join();
  th2.join();

  // Check for node and property leaks.
  Validate(nodeCount == long(g_lNodeCount));
  Validate(propCount == long(g_lPropertyCount));

  return g_bXMLTestsOK;
}

#pragma ON_PRAGMA_WARNING_POP

//-------------------------------------------------------------------------------------------------------------------
ON_UUID uuidPostEffect_ToneMapper_Clamp = { 0xacb8d258, 0xc1d6, 0x499d, { 0xaa, 0x23, 0x02, 0xdc, 0xde, 0xa2, 0xb0, 0xa2 } };
ON_UUID uuidPostEffect_Gamma            = { 0x84c0798d, 0xc43a, 0x4402, { 0x88, 0x91, 0xe0, 0xc8, 0x08, 0x8e, 0x67, 0xca } };
ON_UUID chanRGBA                        = { 0x453a9a1c, 0x9307, 0x4976, { 0xb2, 0x82, 0x4e, 0xad, 0x4d, 0x53, 0x98, 0x79 } };
ON_UUID chanDistanceFromCamera          = { 0xb752ce0b, 0xc219, 0x4bdd, { 0xb1, 0x34, 0x26, 0x42, 0x5e, 0x1c, 0x43, 0x31 } };
#ifdef RDK_RENDER_PRESETS
ON_UUID uuidRenderPreset_Studio         = { 0x5898cc05, 0x4202, 0x4dfb, { 0x83, 0xfe, 0x8f, 0xa8, 0x8f, 0x91, 0xc7, 0xd6 } };
ON_UUID uuidRenderPreset_Custom         = { 0xc89a74fb, 0x1451, 0x4a9b, { 0xb8, 0x7d, 0xe3, 0x0f, 0xf3, 0x51, 0x0f, 0x96 } };
ON_UUID uuidRenderPreset_Exterior       = { 0x1346FE79, 0xBF49, 0x4BB6, { 0x86, 0xF4, 0xF2, 0xC2, 0x81, 0xD1, 0xD5, 0x5A } };
ON_UUID uuidRenderPreset_Interior       = { 0x14A1D7E9, 0xC75D, 0x464D, { 0xBB, 0x81, 0x38, 0x1C, 0xA2, 0xF1, 0xC9, 0x58 } };
#endif

//-------------------------------------------------------------------------------------------------------------------

#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4456) // Declaration hides previous local declaration

class CreateXMLException
{
};

static ON_XMLNode& Create(ON_XMLNode& node, const wchar_t* s)
{
  auto* child_node = node.CreateNodeAtPath(s);
  if (nullptr == child_node)
    throw CreateXMLException(); // This should never, ever happen.

  return *child_node;
}

ON_RdkDocumentDefaults::ON_RdkDocumentDefaults(int version, ValueSets vs, void*)
  :
  _vs(vs),
  _major_version(version),
  _reserved(nullptr)
{
  try
  {
    CreateXML();
  }
  catch (CreateXMLException)
  {
    ON_ERROR("CRITICAL - Failed to create default XML");
  }
}

void ON_RdkDocumentDefaults::CreateXML(void)
{
  auto& doc = Create(_root, ON_RDK_DOCUMENT);
  {
    if (ValueSets::All == _vs)
    {
      Create(doc, ON_RDK_CURRENT_CONTENT).CreateNodeAtPath(ON_RDK_BACKGROUND_ENVIRONMENT);
      Create(doc, ON_RDK_DEFAULT_CONTENT_SECTION);
    }

    auto& settings = Create(doc, ON_RDK_SETTINGS);
    {
      if (ValueSets::All == _vs)
      {
        // Named items.
        ON_XMLParameters(Create(settings, ON_RDK_NAMED_VIEWS    )).SetParam(ON_RDK_SORT_MODE, L"");
        ON_XMLParameters(Create(settings, ON_RDK_NAMED_CPLANES  )).SetParam(ON_RDK_SORT_MODE, L"");
        ON_XMLParameters(Create(settings, ON_RDK_NAMED_POSITIONS)).SetParam(ON_RDK_SORT_MODE, L"");
        ON_XMLParameters(Create(settings, ON_RDK_NAMED_SNAPSHOTS)).SetParam(ON_RDK_SORT_MODE, L"");

        // Miscellaneous.
        auto& misc = Create(settings, ON_RDK_MISCELLANEOUS);
        ON_XMLParameters(misc).SetParam(ON_RDK_CUSTOM_IMAGE_SIZE_IS_PRESET, false);
        {
          // Name collision suppression.
          ON_XMLParameters p(Create(misc, ON_RDK_NAME_COLLISION_SUPPRESS));
          p.SetParam(ON_RDK_IMPORT, false);
          p.SetParam(ON_RDK_PASTE , false);
        }

        // Excluded render engines.
        ON_XMLParameters p(Create(settings, ON_RDK_EXCLUDED_RENDER_ENGINES));
        p.SetParam(ON_RDK_UUIDS, L"");

        // Filters.
        ON_XMLParameters f(Create(settings, ON_RDK_FILTERS));
        f.SetParam(ON_RDK_NAME_FILTER, L"");
        f.SetParam(ON_RDK_NAME_FILTER_INVERT, false);
        f.SetParam(ON_RDK_SHOW_UNASSIGNED, true);
        f.SetParam(ON_RDK_SHOW_V4, true);
        f.SetParam(ON_RDK_SHOW_HIDDEN, false);
        f.SetParam(ON_RDK_SHOW_REFERENCE, false);

        // Post effects.
        auto& peps = Create(settings, ON_RDK_POST_EFFECTS);
        {
          Create(peps, ON_RDK_PEP_TYPE_EARLY);
          Create(peps, ON_RDK_PEP_TYPE_TONE_MAPPING);
          Create(peps, ON_RDK_PEP_TYPE_LATE);
        }
      }

      // Rendering section.
      auto& rendering = Create(settings, ON_RDK_RENDERING);
      {
        if (ValueSets::All == _vs)
        {
          // Render channels.
          auto& render_channels = Create(rendering, ON_RDK_RENDER_CHANNELS);
          {
            ON_wString a, b;
            ON_UuidToString(chanRGBA, a);
            ON_UuidToString(chanDistanceFromCamera, b);
            a.MakeUpper(); b.MakeUpper();
            ON_XMLParameters p(render_channels);
            p.SetParam(ON_RDK_RCH_LIST, a + L";" + b);
            p.SetParam(ON_RDK_RCH_MODE, ON_RDK_RCH_MODE_AUTOMATIC);
          }

          // Misc rendering settings.
          ON_XMLParameters p(rendering);
          p.SetParam(ON_RDK_EMBED_SUPPORT_FILES_ON, true); // Only for monitoring. Not loaded.
          p.SetParam(ON_RDK_DITHERING_ENABLED, false);
          p.SetParam(ON_RDK_DITHERING_METHOD, ON_RDK_DITHERING_METHOD_FLOYD_STEINBERG);
          p.SetParam(ON_RDK_CUSTOM_REFLECTIVE_ENVIRONMENT, ON_nil_uuid);
          p.SetParam(ON_RDK_CUSTOM_REFLECTIVE_ENVIRONMENT_ON, (_major_version < 6) ? false : true);
#ifdef RDK_RENDER_PRESETS
          p.SetParam(ON_RDK_CURRENT_RENDER_PRESET, (_major_version < 8) ? uuidRenderPreset_Custom
                                                                        : uuidRenderPreset_Studio);
#endif
          p.SetParam(ON_RDK_POST_PROCESS_GAMMA_ON, true);
          p.SetParam(ON_RDK_POST_PROCESS_GAMMA,   (_major_version < 6) ? 1.0f : 2.2f);
          p.SetParam(ON_RDK_PRE_PROCESS_GAMMA_ON, (_major_version < 6) ? false : true);
        }
        else
        {
          ON_XMLParameters p(rendering);

          if (_major_version < 6)
          {
            p.SetParam(ON_RDK_CUSTOM_REFLECTIVE_ENVIRONMENT_ON, false);
          }

#ifdef RDK_RENDER_PRESETS
          if (_major_version < 8)
          {
            p.SetParam(ON_RDK_CURRENT_RENDER_PRESET, uuidRenderPreset_Custom);
          }
#endif
        }
      }

      if (ValueSets::All == _vs)
      {
        // Sun and Skylight.
        auto& sun = Create(settings, ON_RDK_SUN);
        {
          ON_XMLParameters p(sun);
          p.SetParam(ON_RDK_SUN_ENABLE_ALLOWED, true);
          p.SetParam(ON_RDK_SUN_ENABLE_ON, false);
          p.SetParam(ON_RDK_SUN_MANUAL_CONTROL_ALLOWED, true);
          p.SetParam(ON_RDK_SUN_MANUAL_CONTROL_ON, false);
          p.SetParam(ON_RDK_SUN_INTENSITY, 1.0);
          p.SetParam(ON_RDK_SUN_SHADOW_INTENSITY, 1.0);
          p.SetParam(ON_RDK_SUN_DAYLIGHT_SAVING_ON, false);
          p.SetParam(ON_RDK_SUN_DAYLIGHT_SAVING_MINUTES, 60);

          int dy = 0, dm = 0, dd = 0; double dh = 0.0;
          ON_SunEngine::GetDefaultLocalDateTime(dy, dm, dd, dh);

          ON_SunEngine engine(ON_SunEngine::Accuracy::Minimum);
          engine.SetLocalDateTime(dy, dm, dd, dh);
          int y = 0, m = 0, d = 0; double h = 0.0;
          engine.LocalDateTime(y, m, d, h);
          p.SetParam(ON_RDK_SUN_DATE_YEAR,  y);
          p.SetParam(ON_RDK_SUN_DATE_MONTH, m);
          p.SetParam(ON_RDK_SUN_DATE_DAY,   d);
          p.SetParam(ON_RDK_SUN_TIME_HOURS, h);
          p.SetParam(ON_RDK_SUN_AZIMUTH,  engine.Azimuth());
          p.SetParam(ON_RDK_SUN_ALTITUDE, engine.Altitude());

          p.SetParam(ON_RDK_SUN_SKYLIGHT_ENABLED, (_major_version < 6) ? false : true);
          p.SetParam(ON_RDK_SUN_SKYLIGHT_SHADOW_INTENSITY, 1.0);
          p.SetParam(ON_RDK_SUN_SKYLIGHT_ENVIRONMENT_OVERRIDE, (_major_version < 6) ? false : true);
          p.SetParam(ON_RDK_SUN_SKYLIGHT_ENVIRONMENT_ID, ON_nil_uuid);

          // Don't create defaults for North, Latitude or Longitude because they are stored in the
          // earth anchor point. However, the time zone is not, so create the default for it.
          p.SetParam(ON_RDK_SUN_OBSERVER_TIMEZONE, 0.0);
        }

        // Safe frame.
        auto& safe_frame = Create(settings, ON_RDK_SAFE_FRAME);
        {
          ON_XMLParameters p(safe_frame);
          p.SetParam(ON_RDK_SF_ENABLED, false);
          p.SetParam(ON_RDK_SF_PERSPECTIVE_ONLY, true);
          p.SetParam(ON_RDK_SF_4x3_FIELD_GRID_ON, false);

          auto& live_frame = Create(safe_frame, ON_RDK_SF_LIVE_FRAME);
          {
            ON_XMLParameters p(live_frame);
            p.SetParam(ON_RDK_SFF_ON, true);
          }

          auto& action_frame = Create(safe_frame, ON_RDK_SF_ACTION_FRAME);
          {
            ON_XMLParameters p(action_frame);
            p.SetParam(ON_RDK_SFF_ON, true);
            p.SetParam(ON_RDK_SFF_XSCALE, 0.9);
            p.SetParam(ON_RDK_SFF_YSCALE, 0.9);
            p.SetParam(ON_RDK_SFF_LINK, true);
          }

          auto& title_frame = Create(safe_frame, ON_RDK_SF_TITLE_FRAME);
          {
            ON_XMLParameters p(title_frame);
            p.SetParam(ON_RDK_SFF_ON, true);
            p.SetParam(ON_RDK_SFF_XSCALE, 0.8);
            p.SetParam(ON_RDK_SFF_YSCALE, 0.8);
            p.SetParam(ON_RDK_SFF_LINK, true);
          }
        }
      }

      // Ground plane.
      if (ValueSets::All == _vs)
      {
        auto& ground_plane = Create(settings, ON_RDK_GROUND_PLANE);
        {
          ON_XMLParameters p(ground_plane);
          p.SetParam(ON_RDK_GP_ENABLED, (_major_version < 6) ? false : true);
          p.SetParam(ON_RDK_GP_SHOW_UNDERSIDE, false);
          p.SetParam(ON_RDK_GP_ALTITUDE, 0.0);
          p.SetParam(ON_RDK_GP_AUTO_ALTITUDE, true);
          p.SetParam(ON_RDK_GP_SHADOW_ONLY, (_major_version < 6) ? false : true);
          p.SetParam(ON_RDK_GP_MATERIAL_ID, L"");
          p.SetParam(ON_RDK_GP_TEXTURE_SIZE, ON_2dPoint(1.0, 1.0));
          p.SetParam(ON_RDK_GP_TEXTURE_OFFSET, ON_2dPoint(0.0, 0.0));
          p.SetParam(ON_RDK_GP_TEXTURE_ROTATION, 0.0);
          p.SetParam(ON_RDK_GP_TEXTURE_OFFSET_LOCKED, false);
          p.SetParam(ON_RDK_GP_TEXTURE_SIZE_LOCKED, true);
        }
      }
      else
      {
        if (_major_version < 6)
        {
          auto& ground_plane = Create(settings, ON_RDK_GROUND_PLANE);
          {
            ON_XMLParameters p(ground_plane);
            p.SetParam(ON_RDK_GP_SHADOW_ONLY, false);
          }
        }
      }
    }
  }
}

const ON_XMLNode& ON_RdkDocumentDefaults::Node(void) const
{
  return _root;
}

void ON_RdkDocumentDefaults::CopyDefaultsTo(ON_XMLNode& dest) const
{
  if (ValueSets::All == _vs)
  {
    dest = _root;
  }
  else
  {
    dest.MergeFrom(_root);
  }
}

ON_RdkDocumentDefaults::~ON_RdkDocumentDefaults()
{
}

void* ON_RdkDocumentDefaults::EVF(const wchar_t*, void*)
{
  return nullptr;
}

ON_XMLParamBlock::ON_XMLParamBlock()
  :
  _reserved(0),
  ON_XMLParameters(_node)
{
}

ON_XMLParamBlock::~ON_XMLParamBlock()
{
}

#pragma ON_PRAGMA_WARNING_POP
