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

/////////////////////////////////////////////////////////////////////////////
// Empty strings point at empty_wstring

class ON_aStringHeader
{
private:
  ON_aStringHeader() = delete;

public:
  ~ON_aStringHeader() = default;
  ON_aStringHeader(const ON_aStringHeader&) = default;
  ON_aStringHeader& operator=(const ON_aStringHeader&) = default;

public:
  ON_aStringHeader(
    int initial_ref_count,
    int capacity
  )
    : ref_count(initial_ref_count)
    , string_capacity(capacity)
  {}

public:
  // NOTE WELL: 
  //  ref_count must be a signed 32-bit integer type that
  //  supports atomic increment/decrement operations.
  std::atomic<int> ref_count;
	int string_length=0; // does not include null terminator
	int string_capacity; // does not include null terminator

public:
	char* string_array() {return (char*)(this+1);}
};

class ON_Internal_Empty_aString
{
private:
  ON_Internal_Empty_aString(const ON_Internal_Empty_aString&) = delete;
  ON_Internal_Empty_aString& operator=(const ON_Internal_Empty_aString&) = delete;

public: 
  ON_Internal_Empty_aString()
    : header(-1,0)
  {}
  ~ON_Internal_Empty_aString() = default;


public:
  ON_aStringHeader header;
  char s = 0;    
};

static ON_Internal_Empty_aString empty_astring;
static const ON_aStringHeader* pEmptyStringHeader = &empty_astring.header;
static const char* pEmptyaString = &empty_astring.s;


static void ON_aStringHeader_DecrementRefCountAndDeleteIfZero(class ON_aStringHeader* hdr)
{
  if (nullptr == hdr || hdr == pEmptyStringHeader)
    return;
  //const int ref_count = ON_AtomicDecrementInt32(&hdr->ref_count);
  const int ref_count = --hdr->ref_count;
  if (0 == ref_count)
  {
    // zero entire header to help prevent crashes from corrupt string bug
    hdr->string_length = 0;
    hdr->string_capacity = 0;
    onfree(hdr);
  }
}

//////////////////////////////////////////////////////////////////////////////
// protected helpers

bool ON_String::IsValid(
  bool bLengthTest
) const
{
  if (m_s == pEmptyaString)
    return true;
  for (;;)
  {
    // These checks attempt to detect cases when the memory used for the header information
    // no longer contains valid settings.
    const char* s = m_s;
    if (nullptr == s)
      break;
#if defined(ON_DEBUG) && defined(ON_RUNTIME_WIN) && defined(ON_64BIT_RUNTIME)
    // WINDOWS 64-bit pointer brackets in debug heap
    // https://docs.microsoft.com/en-us/windows-hardware/drivers/gettingstarted/virtual-address-spaces
    if (((ON__UINT_PTR)s) <= 0x10000ull)
      break;
    if (((ON__UINT_PTR)s) > 0x7FFFFFFFFFFull)
      break;
    if (0 != ((ON__UINT_PTR)s) % 4)
      break;
#endif
    const ON_aStringHeader* hdr = Header();
    if (nullptr == hdr)
      break;

#if defined(ON_DEBUG) && defined(ON_RUNTIME_WIN) && defined(ON_64BIT_RUNTIME)
    if (0 != ((ON__UINT_PTR)hdr) % 8)
      break;
#endif

    // If the string is corrupt, there may be a crash on one of the 3 const int xxx = hdr->xxx; lines.
    // But, if we do nothing that crash that was going to happen in the very near future when
    // the code calling this function tries to use the string.
    // If the memory was recently freed or corrupted, there is a non-zero chance
    // these checks will break out of the for(;;){} scope, we will prevent
    // the crash by setting "this" to the empty string.
    const int string_capacity = hdr->string_capacity;
    if (string_capacity <= 0)
      break;
    if (string_capacity > ON_String::MaximumStringLength)
      break;
    const int string_length = hdr->string_length;
    if (string_length < 0)
      break;
    if (string_length > string_capacity)
      break;
    const int ref_count = (int)(hdr->ref_count);
    if (ref_count <= 0)
      break;
    const char* s1 = s + string_length;
    if (s1 < s)
    {
      // overflow check
      break;
    }
#if defined(ON_DEBUG) && defined(ON_RUNTIME_WIN) && defined(ON_64BIT_RUNTIME)
    // WINDOWS 64-bit pointer brackets in debug heap
    // https://docs.microsoft.com/en-us/windows-hardware/drivers/gettingstarted/virtual-address-spaces
    if (((ON__UINT_PTR)s1) <= 0x10000ull)
      break;
    if (((ON__UINT_PTR)s1) > 0x7FFFFFFFFFFull)
      break;
#endif
    if (bLengthTest)
    {
      // Because the ON_wString m_s[] array can have internal null elements,
      // the length test has to be enabled in situations where it is certain
      // that we are in the common situation where m_s[] is a single null terminated
      // sting and hdr->string_length is the m_s[] index of the null terminator.
      while (s < s1 && 0 != *s)
        s++;
      if (s != s1)
        break;
      if (0 != *s)
        break;
    }
    return true;
  }
  // prevent imminent and unpredictable crash
  //
  // The empty string is used (as opposed to something like "YIKES - CALL TECH SUPPORT")
  // becuase anything besides the empty string introduces using heap in a class that
  // has been corrupted by some earlier operation.
  const_cast<ON_String*>(this)->m_s = (char*)pEmptyaString;
  // Devs
  //  If you get this error, some earlier operation corrupted the string
  //  It is critical to track this bug down ASAP.
  ON_ERROR("Corrupt ON_String - crash prevented.");
  return false;
}

ON_aStringHeader* ON_String::IncrementedHeader() const
{
  ON_aStringHeader* hdr = (ON_aStringHeader*)m_s;
  if (nullptr == hdr)
    return nullptr;
  
  hdr--;
  if (hdr == pEmptyStringHeader)
    return nullptr;

  //ON_AtomicIncrementInt32(&hdr->ref_count);
  ++hdr->ref_count;
  return hdr;
}

ON_aStringHeader* ON_String::Header() const
{
  ON_aStringHeader* hdr = (ON_aStringHeader*)m_s;
  if (hdr)
    hdr--;
  else
    hdr = &empty_astring.header;
  return hdr;
}

void ON_String::Create()
{
  m_s = (char*)pEmptyaString;
}

void ON_String::Destroy()
{
  ON_aStringHeader* hdr = Header();
  if (hdr != pEmptyStringHeader && nullptr != hdr && (int)(hdr->ref_count) > 0)
    ON_aStringHeader_DecrementRefCountAndDeleteIfZero(hdr);
	Create();
}

void ON_String::Empty()
{
  Destroy();
  Create();
}

void ON_String::EmergencyDestroy()
{
	Create();
}

void ON_String::EnableReferenceCounting( bool bEnable )
{
  // OBSOLETE - DELETE WHEN SDK CAN BE BROKEN
}

bool ON_String::IsReferenceCounted() const
{
  return true;
}

char* ON_String::CreateArray( int capacity )
{
  Destroy();
  if (capacity > ON_String::MaximumStringLength)
  {
    ON_ERROR("Requested capacity > ON_String::MaximumStringLength");
    return nullptr;
  }
  if ( capacity > 0 ) 
  {
    // This scope does not need atomic operations
		void* buffer = onmalloc( sizeof(ON_aStringHeader) + (capacity+1)*sizeof(*m_s) );
    ON_aStringHeader* hdr = new (buffer) ON_aStringHeader(1,capacity);
		m_s = hdr->string_array();
    memset( m_s, 0, (capacity+1)*sizeof(*m_s) );
    return m_s;
  }
  return nullptr;
}

void ON_String::CopyArray()
{
  // If 2 or more strings are using the array, it is duplicated.
  // Call CopyArray() before modifying array contents.
  // hdr0 = original header
  ON_aStringHeader* hdr0 = Header();
  if ( hdr0 != pEmptyStringHeader && nullptr != hdr0 && (int)(hdr0->ref_count) > 1 ) 
  {
    // Calling Create() here insures hdr0 remains valid until we decrement below.
    Create();
    CopyToArray( hdr0->string_capacity, hdr0->string_array() );
    if ( hdr0->string_length < hdr0->string_capacity )
    {
      // Set new header string length;
      Header()->string_length = hdr0->string_length;
    }
    // "this" no longer requires access to the original header
    // If we are in a multi-threaded situation and another thread
    // has decremented ref_count since the > 1 check above,
    // we might end up deleting hdr0.
    ON_aStringHeader_DecrementRefCountAndDeleteIfZero(hdr0);
  }
}

char* ON_String::ReserveArray( size_t array_capacity )
{
  if (array_capacity <= 0)
    return nullptr;

  ON_aStringHeader* hdr0 = Header();

  if (array_capacity > (size_t)ON_String::MaximumStringLength)
  {
    ON_ERROR("Requested capacity > ON_String::MaximumStringLength");
    return nullptr;
  }

  const int capacity = (int)array_capacity; // for 64 bit compiler
  if ( hdr0 == pEmptyStringHeader || nullptr == hdr0 ) 
  {
		CreateArray(capacity);
  }
  else if ( (int)(hdr0->ref_count) > 1 ) 
  {
    // Calling Create() here insures hdr0 remains valid until we decrement below.
    Create();

    // Allocate a new array
		CreateArray(capacity);
    ON_aStringHeader* hdr1 = Header();
    const int size = (capacity < hdr0->string_length) ? capacity : hdr0->string_length;
    if ( size > 0 ) 
    {
      memcpy( hdr1->string_array(), hdr0->string_array(), size*sizeof(*m_s) );
      hdr1->string_length = size;
    }
    // "this" no longer requires access to the original header
    // If we are in a multi-threaded situation and another thread
    // has decremented ref_count since the > 1 check above,
    // we might end up deleting hdr0.
    ON_aStringHeader_DecrementRefCountAndDeleteIfZero(hdr0);
  }
	else if ( capacity > hdr0->string_capacity ) 
  {
		hdr0 = (ON_aStringHeader*)onrealloc( hdr0, sizeof(ON_aStringHeader) + (capacity+1)*sizeof(*m_s) );
    m_s = hdr0->string_array();
    memset( &m_s[hdr0->string_capacity], 0, (1 + capacity - hdr0->string_capacity)*sizeof(*m_s) );
    hdr0->string_capacity = capacity;
	}
  return Array();
}

void ON_String::ShrinkArray()
{
  ON_aStringHeader* hdr0 = Header();
  if (nullptr == hdr0)
  {
    Create();
  }
  else if ( hdr0 != pEmptyStringHeader ) 
  {
    if ( hdr0->string_length < 1 ) 
    {
      Destroy();
      Create();
    }
    else if ( (int)(hdr0->ref_count) > 1 ) 
    {
      // Calling Create() here insures hdr0 remains valid until we decrement below.
      Create();

      // shared string
      CreateArray(hdr0->string_length);
		  ON_aStringHeader* hdr1 = Header();
      memcpy( m_s, hdr0->string_array(), hdr0->string_length*sizeof(*m_s));
      hdr1->string_length = hdr0->string_length;
      m_s[hdr1->string_length] = 0;
      // "this" no longer requires access to the original header
      // If we are in a multi-threaded situation and another thread
      // has decremented ref_count since the > 1 check above,
      // we might end up deleting hdr0.
      ON_aStringHeader_DecrementRefCountAndDeleteIfZero(hdr0);
    }
	  else if ( hdr0->string_length < hdr0->string_capacity )
    {
      // onrealloc string
		  hdr0 = (ON_aStringHeader*)onrealloc( hdr0, sizeof(ON_aStringHeader) + (hdr0->string_length+1)*sizeof(*m_s) );
      hdr0->string_capacity = hdr0->string_length;
      m_s = hdr0->string_array();
      m_s[hdr0->string_length] = 0;
	  }
  }
}

void ON_String::CopyToArray( const ON_String& s )
{
  CopyToArray( s.Length(), s.Array() );
}

void ON_String::CopyToArray( int size, const char* s )
{
  if (size > ON_String::MaximumStringLength)
  {
    ON_ERROR("Requested size > ON_String::MaximumStringLength.");
    size = 0;
  }

  if ( size > 0 && s && s[0] ) 
  {
    ON_aStringHeader* hdr0 = Header();
    // Calling Create() here preserves hdr0 in case s is in its m_s[] buffer.
    Create();

    // ReserveArray() will allocate a new header 
	  ReserveArray(size);
    ON_aStringHeader* hdr1 = Header();
    if (nullptr != hdr1 && hdr1 != pEmptyStringHeader)
    {
      memcpy(m_s, s, size * sizeof(*m_s));
      hdr1->string_length = size;
      m_s[hdr1->string_length] = 0;
    }
    // "this" no longer requires access to the original header
    ON_aStringHeader_DecrementRefCountAndDeleteIfZero(hdr0);
  }
  else 
  {
    Destroy();
    Create();
  }
}

void ON_String::CopyToArray( int size, const unsigned char* s )
{
  CopyToArray( size, ((char*)s) );
}

void ON_String::AppendToArray( const ON_String& s )
{
  AppendToArray( s.Length(), s.Array() );
}

void ON_String::AppendToArray( int size, const char* s )
{
  if ( size > 0 && s && s[0] ) 
  {
    if (nullptr == ReserveArray(size + Header()->string_length))
      return;
    // m_s = char array
	  memcpy(&m_s[Header()->string_length], s, size*sizeof(*m_s));
	  Header()->string_length += size;
    m_s[Header()->string_length] = 0;
  }
}

void ON_String::AppendToArray( int size, const unsigned char* s )
{
  AppendToArray( size, ((char*)s) );
}

int ON_String::Length(const char* s)
{
  return ON_String::Length(s, 2147483645);
}

int ON_String::Length(
  const char* s,
  size_t string_capacity
)
{
  if (nullptr == s)
    return 0;
  if (string_capacity > 2147483645)
    string_capacity = 2147483645;
  size_t slen = 0;
  while (slen < string_capacity && 0 != *s++)
    slen++;
  return ((int)slen);
}

unsigned int ON_String::UnsignedLength( const char* s )
{
  return (unsigned int)ON_String::Length( s );
}

//////////////////////////////////////////////////////////////////////////////
// Construction/Destruction


ON_String::ON_String() ON_NOEXCEPT
{
	Create();
}

ON_String::~ON_String()
{
  Destroy();
}

ON_String::ON_String(const ON_String& src)
{
  const ON_aStringHeader* p = src.IncrementedHeader();
	if ( nullptr != p )	
  {
		m_s = src.m_s;
	}
	else 
  {
		Create();
	}
}

#if defined(ON_HAS_RVALUEREF)

// Clone constructor
ON_String::ON_String( ON_String&& src ) ON_NOEXCEPT
{
  m_s = src.m_s;
  src.m_s = (char*)pEmptyaString;
}

// Clone Assignment operator
ON_String& ON_String::operator=( ON_String&& src ) ON_NOEXCEPT
{
  if ( this != &src )
  {
    this->Destroy();
    m_s = src.m_s;
    src.m_s = (char*)pEmptyaString;
  }
  return *this;
}

#endif


ON_String::ON_String( const char* s )
{
	Create();
  if ( s && s[0] )
  {    
    CopyToArray( ON_String::Length(s), s );
  }
}

ON_String::ON_String( const char* s, int length )
{
	Create();
  if ( s && length > 0 ) 
  {
    CopyToArray(length,s);
	}
}

ON_String::ON_String( char c, int repeat_count )
{
  Create();
  if (repeat_count > ON_String::MaximumStringLength)
  {
    ON_ERROR("Requested size > ON_String::MaximumStringLength");
    return;
  }

  if ( repeat_count > 0 && c != 0)
  {
    ReserveArray(repeat_count);
    memset( m_s, c, repeat_count*sizeof(*m_s) );
    m_s[repeat_count] = 0;
    Header()->string_length = repeat_count;
  }
}

ON_String::ON_String( const unsigned char* s )
{
	Create();
  if ( s && s[0] ) 
  {
    CopyToArray( ON_String::Length((const char*)s), (const char*)s );
  }
}

ON_String::ON_String( const unsigned char* s, int length )
{
	Create();
  if ( s && length > 0 )
  {
    CopyToArray(length,s);
	}
}

ON_String::ON_String( unsigned char c, int repeat_count )
{
  Create();
  if (repeat_count > ON_String::MaximumStringLength)
  {
    ON_ERROR("Requested size > ON_String::MaximumStringLength");
    return;
  }
  if ( repeat_count > 0 && c != 0)
  {
    ReserveArray(repeat_count);
    memset( m_s, c, repeat_count*sizeof(*m_s) );
    m_s[repeat_count] = 0;
    Header()->string_length = repeat_count;
  }
}


ON_String::ON_String( const wchar_t* w)
{
  Create();
  if ( w && w[0] )
  {
    *this = w;
  }
}

ON_String::ON_String( const wchar_t* w, int w_length )
{
  // from substring
  Create();
  if ( w && w[0] ) 
  {
    CopyToArray( w_length, w );
  }
}


ON_String::ON_String( const ON_wString& w )
{
  Create();
  *this = w;
}



#if defined (ON_RUNTIME_WIN)
bool ON_String::LoadResourceString( HINSTANCE instance, UINT id )
{
  char s[2048]; // room for 2047 characters
  int length;

  Destroy();
  length = ::LoadStringA( instance, id, s, 2047 );
  if ( length > 0 && length < 2048 ) {
    CopyToArray( length, s );
  }
  return (length > 0 );
}
#endif

int ON_String::Length() const
{
  return Header()->string_length;
}

unsigned int ON_String::UnsignedLength() const
{
  return (unsigned int)Length();
}

// 25 October 2007 Dale Lear - remove bogus decl and defn
//void Destroy();
//void EmergencyDestroy()
//{
//}

ON_String::operator const char*() const
{
  return ( nullptr == m_s || m_s == pEmptyaString ) ? "" : m_s;
}

char& ON_String::operator[](int i)
{
  CopyArray();
  return m_s[i];
}

char ON_String::operator[](int i) const
{
  return m_s[i];
}

bool ON_String::IsEmpty() const
{
  return (Header()->string_length <= 0) ? true : false;
}

bool ON_String::IsNotEmpty() const
{
  return (Header()->string_length > 0) ? true : false;
}

ON_String& ON_String::operator=(const ON_String& src)
{
	if (m_s != src.m_s)	
  {
    if ( nullptr != src.IncrementedHeader() )
    {
      Destroy();
      m_s = src.m_s;
    }
    else
    {
      Destroy();
      Create();
    }
  }
	return *this;
}

ON_String& ON_String::operator=( char c )
{
	CopyToArray( 1, &c );
	return *this;
}

ON_String& ON_String::operator=( const char* s )
{
  if ( (void*)s != (void*)m_s )
	  CopyToArray( ON_String::Length(s), s);
	return *this;
}

ON_String& ON_String::operator=( unsigned char c )
{
	CopyToArray( 1, &c );
	return *this;
}

ON_String& ON_String::operator=( const unsigned char* s )
{
  if ( (void*)s != (void*)m_s )
	  CopyToArray( ON_String::Length((const char*)s), s);
	return *this;
}

ON_String& ON_String::operator=( const wchar_t* w )
{
  // converts wide string to byte string
  const int w_length = ON_wString::Length(w);
  CopyToArray( w_length, w);
	return *this;
}

ON_String& ON_String::operator=( const ON_wString& w )
{
  *this = w.Array();
  return *this;
}


ON_String ON_String::operator+(const ON_String& s2) const
{
	ON_String s(*this);
  s.AppendToArray( s2 );
	return s;
}

ON_String ON_String::operator+( char s2 ) const
{
	ON_String s(*this);
  s.AppendToArray( 1, &s2 );
	return s;
}

ON_String ON_String::operator+( unsigned char s2 ) const
{
	ON_String s(*this);
  s.AppendToArray( 1, &s2 );
	return s;
}

ON_String ON_String::operator+(const char* s2) const
{
	ON_String s(*this);
  s.AppendToArray( ON_String::Length(s2), s2 );
	return s;
}

ON_String ON_String::operator+( const unsigned char* s2) const
{
	ON_String s(*this);
  s.AppendToArray( ON_String::Length((const char*)s2), s2 );
	return s;
}

//////////////////////////////////////////////////////////////////////////////
// operator+=()


void ON_String::Append( const char* s , int count )
{
  // append specified number of characters
  if ( s && count > 0 )
    AppendToArray(count,s);
}

void ON_String::Append( const unsigned char* s , int count )
{
  // append specified number of characters
  if ( s && count > 0 )
    AppendToArray(count,s);
}

const ON_String& ON_String::operator+=(const ON_String& s)
{
  // 28th July 2022 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-69587
  // When the strings are the same object AppendToArray() doesn't work properly. The safest
  // thing to do is copy the incoming string so they are not the same object anymore.
  if (this == &s)
  {
    ON_String copy = s;
    AppendToArray(copy);
  }
  else
  {
    AppendToArray(s);
  }

  return *this;
}

const ON_String& ON_String::operator+=( char s )
{
  AppendToArray(1,&s);
	return *this;
}

const ON_String& ON_String::operator+=( unsigned char s )
{
  AppendToArray(1,&s);
	return *this;
}

const ON_String& ON_String::operator+=( const char* s )
{
  AppendToArray(Length(s),s);
	return *this;
}

const ON_String& ON_String::operator+=( const unsigned char* s )
{
  AppendToArray(ON_String::Length((const char*)s),s);
	return *this;
}

char* ON_String::SetLength(size_t string_length)
{
  int length = (int)string_length; // for 64 bit compilers
  if ( length >= Header()->string_capacity ) {
    ReserveArray(length);
  }
  if ( length >= 0 && length <= Header()->string_capacity ) {
    CopyArray();
    Header()->string_length = length;
    m_s[length] = 0;
    return m_s;
  }
  return nullptr;
}

char* ON_String::Array()
{
  CopyArray();
  return ( Header()->string_capacity > 0 ) ? m_s : 0;
}

const char* ON_String::Array() const
{
  return ( Header()->string_capacity > 0 ) ? m_s : 0;
}

const ON_String ON_String::Duplicate() const
{
  if (Length() <= 0)
    return ON_String::EmptyString;
  ON_String s = *this;
  s.CopyArray();
  return s;
}

/*
Returns:
  Total number of bytes of memory used by this class.
  (For use in ON_Object::SizeOf() overrides.
*/
unsigned int ON_String::SizeOf() const
{
  size_t sz = sizeof(*this);
  if ( ((const void*)m_s) != ((const void*)pEmptyaString) )
    sz += (sizeof(ON_aStringHeader) + (Header()->string_capacity+1));
  return (unsigned int)sz;
}

ON__UINT32 ON_String::DataCRC(ON__UINT32 current_remainder) const
{
  int string_length = Header()->string_length;
  if ( string_length > 0 )
  {
    current_remainder = ON_CRC32(current_remainder, string_length*sizeof(*m_s), m_s);
  }
  return current_remainder;
}

int ON_StringLengthUTF8(
  const char* string
  )
{
  const char* string1 = string;
  if (nullptr != string1)
  {
    while (0 != *string1)
      string1++;
  }
  return (int)(string1 - string);
}

int ON_StringLengthUTF16(
  const ON__UINT16* string
  )
{
  const ON__UINT16* string1 = string;
  if (nullptr != string1)
  {
    while (0 != *string1)
      string1++;
  }
  return (int)(string1 - string);
}

int ON_StringLengthUTF32(
  const ON__UINT32* string
  )
{
  const ON__UINT32* string1 = string;
  if (nullptr != string1)
  {
    while (0 != *string1)
      string1++;
  }
  return (int)(string1 - string);
}

int ON_StringLengthWideChar(
  const wchar_t* string
  )
{
#if (1 == ON_SIZEOF_WCHAR_T)
  return ON_StringLengthUTF8((const char*)string);
#elif (2 == ON_SIZEOF_WCHAR_T)
  return ON_StringLengthUTF16((const ON__UINT16*)string);
#elif (4 == ON_SIZEOF_WCHAR_T)
  return ON_StringLengthUTF32((const ON__UINT32*)string);
#else
#error ON_SIZEOF_WCHAR_T is not defined or has an unexpected value
#endif
}

int ON_StringLengthUTF8(
  const char* string,
  size_t string_capacity
  )
{
  const char* string1 = string;
  if (nullptr != string1 && string_capacity > 0 )
  {
    for (const char* end = string1 + string_capacity; string1 < end; string1++)
    {
      if ( 0 == *string1)
        break;
    }
  }
  return (int)(string1 - string);
}

int ON_StringLengthUTF16(
  const ON__UINT16* string,
  size_t string_capacity
  )
{
  const ON__UINT16* string1 = string;
  if (nullptr != string1 && string_capacity > 0 )
  {
    for (const ON__UINT16* end = string1 + string_capacity; string1 < end; string1++)
    {
      if ( 0 == *string1)
        break;
    }
  }
  return (int)(string1 - string);
}

int ON_StringLengthUTF32(
  const ON__UINT32* string,
  size_t string_capacity
  )
{
  const ON__UINT32* string1 = string;
  if (nullptr != string1 && string_capacity > 0 )
  {
    for (const ON__UINT32* end = string1 + string_capacity; string1 < end; string1++)
    {
      if ( 0 == *string1)
        break;
    }
  }
  return (int)(string1 - string);
}

int ON_StringLengthWideChar(
  const wchar_t* string,
  size_t string_capacity
  )
{
#if (1 == ON_SIZEOF_WCHAR_T)
  return ON_StringLengthUTF8((const char*)string,string_capacity);
#elif (2 == ON_SIZEOF_WCHAR_T)
  return ON_StringLengthUTF16((const ON__UINT16*)string,string_capacity);
#elif (4 == ON_SIZEOF_WCHAR_T)
  return ON_StringLengthUTF32((const ON__UINT32*)string,string_capacity);
#else
#error ON_SIZEOF_WCHAR_T is not defined or has an unexpected value
#endif
}


bool ON_WildCardMatch(const char* s, const char* pattern)
{
  if ( !pattern || !pattern[0] ) {
    return ( !s || !s[0] ) ? true : false;
  }

  if ( *pattern == '*' ) {
    pattern++;
    while ( *pattern == '*' )
      pattern++;
    
    if ( !pattern[0] )
      return true;

    while (*s) {
      if ( ON_WildCardMatch(s,pattern) )
        return true;
      s++;
    }

    return false;
  }

  while ( *pattern != '*' )
  {
    if ( *pattern == '?' ) {
      if ( *s) {
        pattern++;
        s++;
        continue;
      }
      return false;
    }
    
    if ( *pattern == '\\' ) {
      switch( pattern[1] )
      {
      case '*':
      case '?':
        pattern++;
        break;
      }
    }
    if ( *pattern != *s ) {
      return false;
    }

    if ( *s == 0 )
      return true;

    pattern++;
    s++;
  }
  
  return ON_WildCardMatch(s,pattern);
}


bool ON_WildCardMatchNoCase(const char* s, const char* pattern)
{
  if ( !pattern || !pattern[0] ) {
    return ( !s || !s[0] ) ? true : false;
  }

  if ( *pattern == '*' ) 
  {
    pattern++;
    while ( *pattern == '*' )
      pattern++;
    
    if ( !pattern[0] )
      return true;

    while (*s) {
      if ( ON_WildCardMatchNoCase(s,pattern) )
        return true;
      s++;
    }

    return false;
  }

  while ( *pattern != '*' )
  {
    if ( *pattern == '?' ) {
      if ( *s) {
        pattern++;
        s++;
        continue;
      }
      return false;
    }
    
    if ( *pattern == '\\' ) {
      switch( pattern[1] )
      {
      case '*':
      case '?':
        pattern++;
        break;
      }
    }
    if ( toupper(*pattern) != toupper(*s) ) {
      return false;
    }

    if ( *s == 0 )
      return true;

    pattern++;
    s++;
  }
  
  return ON_WildCardMatchNoCase(s,pattern);
}

bool ON_String::WildCardMatch( const char* pattern) const
{
  return ON_WildCardMatch(m_s,pattern);
}

bool ON_String::WildCardMatch( const unsigned char* pattern ) const
{
  return ON_WildCardMatch(m_s,(const char*)pattern);
}

bool ON_String::WildCardMatchNoCase( const char* pattern) const
{
  return ON_WildCardMatchNoCase(m_s,pattern);
}

bool ON_String::WildCardMatchNoCase( const unsigned char* pattern ) const
{
  return ON_WildCardMatchNoCase(m_s,(const char*)pattern);
}

int ON_String::Replace( const char* token1, const char* token2 )
{
  int count = 0;

  if ( 0 != token1 && 0 != token1[0] )
  {
    if ( 0 == token2 )
      token2 = "";
    const int len1 = (int)strlen(token1);
    if ( len1 > 0 )
    {
      const int len2 = (int)strlen(token2);
      int len = Length();
      if ( len >= len1 )
      {
        // in-place
        ON_SimpleArray<int> n(32);
        const char* s = m_s;
        int i;
        for ( i = 0; i <= len-len1; /*empty*/ )
        {
          if ( strncmp(s,token1,len1) )
          {
            s++;
            i++;
          }
          else
          {
            n.Append(i);
            i += len1;
            s += len1;
          }
        }

        count = n.Count();

        // reserve array space - must be done even when len2 <= len1
        // so that shared arrays are not corrupted.
        const int newlen = len + (count*(len2-len1));
        if ( 0 == newlen )
        {
          Destroy();
          return count;
        }

        CopyArray();

        // 24 August 2006 Dale Lear
        //    This used to say
        //       ReserveArray(newlen);
        //    but when newlen < len and the string had multiple
        //    references, the ReserveArray(newlen) call truncated
        //    the input array.  
        ReserveArray( ((newlen<len) ? len : newlen) );

        int i0, i1, ni, j;

        if ( len2 > len1 )
        {
          // copy from back to front
          i1 = newlen;
          i0 = len;
          for ( ni =0; ni < count; ni++ )
            n[ni] = n[ni] + len1;
          for ( ni = count-1; ni >= 0; ni-- )
          {
            j = n[ni];
            while ( i0 > j )
            {
              i0--;
              i1--;
              m_s[i1] = m_s[i0];
            }
            i1 -= len2;
            i0 -= len1;
            memcpy(&m_s[i1],token2,len2*sizeof(m_s[0]));
          }
        }
        else
        {
          // copy from front to back
          i0 = i1 = n[0];
          n.Append(len);
          for ( ni = 0; ni < count; ni++ )
          {
            if ( len2 > 0 )
            {
              memcpy(&m_s[i1],token2,len2*sizeof(m_s[0]));
              i1 += len2;
            }
            i0 += len1;
            j = n[ni+1];
            while ( i0 < j )
            {
              m_s[i1++] = m_s[i0++];
            }
          }
        }
        Header()->string_length = newlen;
        m_s[newlen] = 0;
      }
    }
  }

  return count;
}

int ON_String::Replace( const unsigned char* token1, const unsigned char* token2 )
{
  return Replace((const char*)token1, (const char*)token2);
}

int ON_String::Replace(char utf8_single_byte_c1, char utf8_single_byte_c2)
{
  int count = 0;
  if (ON_IsValidSingleByteUTF8CharValue(utf8_single_byte_c1) && ON_IsValidSingleByteUTF8CharValue(utf8_single_byte_c2))
  {
    int i = Length();
    while (i--)
    {
      if (utf8_single_byte_c1 == m_s[i])
      {
        if (0 == count)
          CopyArray();
        m_s[i] = utf8_single_byte_c2;
        count++;
      }
    }
  }
  return count;
}

int ON_String::Replace( unsigned char token1, unsigned char token2 )
{
  return Replace((const char)token1, (const char)token2);
}


///////////////////////////////////////////////////////////////////////////////

int ON_String::Find(char utf8_single_byte_c) const
{
	// find first single character
  if (ON_IsValidSingleByteUTF8CharValue(utf8_single_byte_c))
  {
    char s[2];
    s[0] = utf8_single_byte_c;
    s[1] = 0;
    return Find(s);
  }
  return -1;
}

int ON_String::Find(unsigned char utf8_single_byte_c) const
{
  return Find((char)utf8_single_byte_c);
}

int ON_String::ReverseFind(char utf8_single_byte_c) const
{
	// find first single character
  if (IsNotEmpty() && ON_IsValidSingleByteUTF8CharValue(utf8_single_byte_c))
  {
    const char* p0 = m_s;
    const char* p = p0 + Length();
    while ( p > p0)
    {
      p--;
      if (utf8_single_byte_c == *p)
        return ((int)(p - p0));
    }
  }
  return -1;
}

int ON_String::ReverseFind(unsigned char utf8_single_byte_c) const
{
  return ReverseFind((char)utf8_single_byte_c);
}

int ON_String::Find( const char* s ) const
{
  return Find(s, 0);
}

int ON_String::Find( const unsigned char* s ) const
{
  return Find((const char*)s, 0);
}

int ON_String::Find(const char* s, int start_index) const
{
  int rc = -1;
  const int length = Length();
  if (s && s[0] && length>0 && start_index>=0 && start_index<length) {
    const char* source = m_s + start_index;
    const char* p = strstr(source, s);
    if (p)
    {
      rc = ((int)(p - m_s)); // the (int) is for 64 bit size_t conversion
    }
  }
  return rc;
}

int ON_String::Find(const unsigned char* s, int start_index) const
{
  return Find((const char*)s, start_index);
}

int ON_String::ReverseFind(const char* s) const
{
  int rc = -1;
  if (s && s[0] && !IsEmpty()) 
  {
    int s_len = 0;
    while (0 != s[s_len])
      s_len++;
    if (Length() >= s_len)
    {
      const char* p0 = m_s;
      const char* p = p0 + (Length()-s_len);
      while (p >= p0)
      {
        if (0 == strncmp(p, s, s_len))
          return ((int)(p - p0));
        p--;
      }
    }
  }
  return rc;
}

int ON_String::ReverseFind(const unsigned char* s) const
{
  return ReverseFind((const char*)s);
}


void ON_String::MakeReverse()
{
  if ( IsNotEmpty() ) 
  {
  	CopyArray();
    ON_String::Reverse(m_s,Length());
  }
}

ON_String ON_String::Reverse() const
{
  ON_String reverse_string(*this);
  reverse_string.MakeReverse();
  return reverse_string;
}

static void ON_String_ReverseUTF8(
  char* string,
  int element_count
  )
{
  if ( element_count < 2 || nullptr == string )
    return;
  ON_String buffer(string,element_count);
  const char* b0 = static_cast<const char*>(buffer);
  const char* b1 = b0+element_count;
  char* s1 = string + (element_count-1);

  ON_UnicodeErrorParameters e;
  e.m_error_mask = 8; // mask overlong UTF-8 encoding errors.
  ON__UINT32 unicode_code_point;
  int count;
  memset(&e, 0, sizeof(e));
  while (b0 < b1)
  {
    const char* c0 = b0++;

    if (0xC0 == (*c0 & 0xC0))
    {
      // *c0 should be the first element in a UTF-8 multi-char encoding.

      while (b0 < b1 && 0x80 == (*b0 & 0xC0))
        b0++;

      unicode_code_point = 0;
      e.m_error_status = 0;
      count = (int)(b0 - c0);
      if (count != ON_DecodeUTF8(c0, count, &e, &unicode_code_point) && 0 != e.m_error_status)
      {
        // not a valid UTF-8 string
        b0 = c0+1;
      }
    }
    
    const char* c = b0;
    while (c > c0)
    {
      c--;
      *s1-- = *c;
    }
  }
}

char* ON_String::Reverse(
  char* string,
  int element_count
  )
{
  if (element_count < 0)
  {
    element_count = ON_String::Length(string);
    if (element_count < 0)
      return nullptr;
  }
  if ( 0 == element_count )
    return string;

  if (nullptr == string)
  {
    ON_ERROR("string is nullptr.");
    return nullptr;
  }

  int i, j;
  char a, b;

  for ( i = 0, j = element_count-1; i < j; i++, j-- ) 
  {
    a = string[i];
    b = string[j];
    if (0 == (0x80 & a) && 0 == (0x80 & b))
    {
      string[i] = b;
      string[j] = a;
      continue;
    }

    // code points with multi char element encodings need to be handled
    ON_String_ReverseUTF8(string+i,j-i+1);
    break;
  }

  return string;
}


void ON_String::TrimLeft(const char* s)
{
  char c;
  const char* sc;
  char* dc;
  int i;
  if ( !IsEmpty() ) {
    if (nullptr == s)
    {
      for (i = 0; 0 != (c = m_s[i]); i++)
      {
        if ( c < 0 || (c > ON_String::Space && c != ON_String::Delete))
          break;
      }
    }
    else
    {
      for (i = 0; 0 != (c = m_s[i]); i++)
      {
        for (sc = s; *sc; sc++) {
          if (*sc == c)
            break;
        }
        if (!(*sc))
          break;
      }
    }
    if ( i > 0 ) {
      if ( m_s[i] ) {
        CopyArray();
        dc = m_s;
        sc = m_s+i;
        while( 0 != (*dc++ = *sc++) );
        Header()->string_length -= i;
      }
      else
        Destroy();
    }
  }
}

void ON_String::TrimRight(const char* s)
{
  char c;
  const char* sc;
  int i = Header()->string_length;
  if ( i > 0 ) {
    if (nullptr == s)
    {
      for (i--; i >= 0 && 0 != (c = m_s[i]); i--)
      {
        if ( c < 0 || (c > ON_String::Space && c != ON_String::Delete))
          break;
      }
    }
    else
    {
      for (i--; i >= 0 && 0 != (c = m_s[i]); i--)
      {
        for (sc = s; *sc; sc++) {
          if (*sc == c)
            break;
        }
        if (!(*sc))
          break;
      }
    }
    if ( i < 0 )
      Destroy();
    else if ( m_s[i+1] ) {
      CopyArray();
      m_s[i+1] = 0;
      Header()->string_length = i+1;
    }
  }
}

void ON_String::TrimLeftAndRight(const char* s)
{
  TrimRight(s);
  TrimLeft(s);
}

int ON_String::Remove(const char utf8_single_byte_c)
{
  if (false == ON_IsValidSingleByteUTF8CharValue(utf8_single_byte_c))
    return 0;

  CopyArray();

  char* pstrSource = m_s;
  char* pstrDest = m_s;
  char* pstrEnd = m_s + Length();

  while( pstrSource && pstrSource  < pstrEnd)
  {
    if (*pstrSource != utf8_single_byte_c)
    {
      *pstrDest = *pstrSource;
      pstrDest++;
    }
    pstrSource++;
  }

  *pstrDest = 0;
  int nCount = (int)(pstrSource - pstrDest); // the (int) is for 64 bit size_t conversion

  Header()->string_length -= nCount;

  return nCount;
}

char ON_String::GetAt( int i ) const
{
  // no error checking
  return m_s[i];
}

void ON_String::SetAt( int i, char c )
{
  if ( i >= 0 && i < Header()->string_length ) {
	  CopyArray();
	  m_s[i] = c;
  }
}

void ON_String::SetAt( int i, unsigned char c )
{
  SetAt( i, (char)c );
}

ON_String ON_String::Mid(int i, int count) const
{
  ON_String(s);
  if ( i >= 0 && i < Length() && count > 0 ) {
    if ( count > Length() - i )
      count = Length() - i;
    s.CopyToArray( count, &m_s[i] );
  }
  return s;
}

ON_String ON_String::Mid(int i) const
{
  return Mid( i, Length() - i );
}

ON_String ON_String::Left(int count) const
{
  ON_String s;
  if ( count > Length() )
    count = Length();
  if ( count > 0 ) {
    s.CopyToArray( count, m_s );
  }
  return s;
}

ON_String ON_String::Right(int count) const
{
  ON_String s;
  if ( count > Length() )
    count = Length();
  if ( count > 0 ) {
    s.CopyToArray( count, &m_s[Length()-count] );
  }
  return s;
}


static bool ON_IsBig5Encoded(const char* buffer, int buffer_length)
{
  if (nullptr == buffer)
    return false;
  if (-1 == buffer_length)
    buffer_length = ON_String::Length(buffer);
  if (buffer_length <= 0 || buffer_length > ON_String::MaximumStringLength)
    return false;

  int db_count = 0;

  int delta_i = 0;
  for (int i = 0; i < buffer_length; i += (delta_i > 0) ? delta_i : 1)
  {
    delta_i = 1;
    const char c = buffer[i];
    if (c >= 0 && c <= 0x7F)
      continue; // ASCII single byte
    if (i + 2 <= buffer_length)
    {
      ON_Big5CodePoint big5_cp = ON_Big5CodePoint::Error;
      const char* b2 = ON_Big5CodePoint::Decode(
        buffer + i,
        2,
        false, false,
        &big5_cp
      );
      if (b2 == buffer + i + 2 && big5_cp.IsValid(false, false))
      {
        delta_i = 2;
        ++db_count;
        continue;
      }
    }
    return false;
  }

  return (db_count > 0);
}



static unsigned Internal_Big5ToUTF32(
  const char* buffer, 
  int buffer_length,
  ON_SimpleArray<ON__UINT32>& utf32
)
{
  unsigned replacement_count = 0;

  utf32.SetCount(0);

  if (nullptr == buffer)
    return false;
  if (-1 == buffer_length)
    buffer_length = ON_String::Length(buffer);
  if (buffer_length <= 0 || buffer_length > ON_String::MaximumStringLength)
    return false;

  utf32.Reserve(buffer_length);

  int db_count = 0;

  int delta_i = 0;
  for (int i = 0; i < buffer_length; i += (delta_i > 0) ? delta_i : 1)
  {
    delta_i = 1;
    const char c = buffer[i];
    if (c >= 0 && c <= 0x7F)
    {
      // ASCII single byte
      utf32.Append((unsigned char)c);
      continue; 
    }
    if (i + 2 <= buffer_length)
    {
      ON_Big5CodePoint big5_cp = ON_Big5CodePoint::Error;
      const char* b2 = ON_Big5CodePoint::Decode(
        buffer + i,
        2,
        false, false,
        &big5_cp
      );
      if (b2 == buffer + i + 2 && big5_cp.IsValid(false, false))
      {
        const ON_UnicodeShortCodePoint u = ON_UnicodeShortCodePoint::CreateFromBig5(big5_cp, ON_UnicodeShortCodePoint::ReplacementCharacter);
        if (u.IsReplacementCharacter())
          ++replacement_count;
        utf32.Append(u.UnicodeCodePoint());
        delta_i = 2;
        ++db_count;
        continue;
      }
    }
    utf32.Append(ON_UnicodeCodePoint::ON_ReplacementCharacter);
    ++replacement_count;
  }

  return replacement_count;
}

static bool ON_IsUTF8Encoded(bool bSloppy, const char* buffer, int buffer_length)
{
  if (nullptr == buffer)
    return false;
  if (-1 == buffer_length)
    buffer_length = ON_String::Length(buffer);
  if (buffer_length <= 0 || buffer_length > ON_String::MaximumStringLength)
    return false;

  struct ON_UnicodeErrorParameters e0
    = bSloppy
    ? ON_UnicodeErrorParameters::FailOnErrors
    : ON_UnicodeErrorParameters::MaskErrors;
  e0.m_error_code_point = ON_UnicodeCodePoint::ON_InvalidCodePoint;
  ON__UINT32 unicode_code_point;
  int delta_i = 0;
  for (int i = 0; i < buffer_length; i += (delta_i > 0) ? delta_i : 1)
  {
    struct ON_UnicodeErrorParameters e = e0;
    unicode_code_point = ON_UnicodeCodePoint::ON_InvalidCodePoint;
    delta_i = ON_DecodeUTF8(buffer + i, buffer_length - i, &e, &unicode_code_point);
    if (delta_i > 0 && ON_IsValidUnicodeCodePoint(unicode_code_point) && i + delta_i <= buffer_length)
      continue;
    return false;
  }

  return true;
}


static bool ON_IsASCIIEncoded(const char* buffer, int buffer_length)
{
  if (nullptr == buffer)
    return false;
  if (-1 == buffer_length)
    buffer_length = ON_String::Length(buffer);
  if (buffer_length <= 0 || buffer_length > ON_String::MaximumStringLength)
    return false;

  if (buffer_length <= 0 || buffer_length > ON_String::MaximumStringLength)
    return false;

  for (int i = 0; i < buffer_length; ++i)
  {
    char c = buffer[i];
    if (c >= 0 && c <= 127)
      continue;
    return false;
  }

  return true;
}


bool ON_String::IsPossibleEncoding(
  ON_String::Encoding encoding,
  const char* buffer,
  int buffer_length
)
{
  // In practice, this is used to choose between BIG5 and UTF when parsing strings that
  // are names of components.
  // 
  // If you need something more clever like NOTPOAD++ encoding detection, then you need
  // to find a library that uses some sampling and linguistic analysis.
  if (ON_String::Encoding::Unset == encoding)
    return false;
  if (ON_String::Encoding::Unknown == encoding)
    return false;
  if (nullptr == buffer)
    return false;
  if (-1 == buffer_length)
    buffer_length = ON_String::Length(buffer);
  if (0 == buffer_length)
    return true;
  if (buffer_length < 0)
    return false;

  switch (encoding)
  {
  case ON_String::Encoding::ASCII:
    return ON_IsASCIIEncoded(buffer, buffer_length);
  case ON_String::Encoding::UTF8:
    return ON_IsUTF8Encoded(false, buffer, buffer_length);
  case ON_String::Encoding::BIG5andASCII:
    return ON_IsBig5Encoded(buffer, buffer_length);
  case ON_String::Encoding::SloppyUTF8:
    return ON_IsUTF8Encoded(false, buffer, buffer_length);
  default:
    break;
  }

  return false;
}

bool ON_String::IsPossibleEncoding(
  ON_String::Encoding encoding
) const
{
  return ON_String::IsPossibleEncoding(encoding, this->Array(), this->Length());
}

ON_String::Encoding ON_String::ProbableEncoding() const
{
  return ON_String::ProbableEncoding(this->Array(), this->Length());
}

ON_String::Encoding ON_String::ProbableEncoding(
  const char* buffer,
  int buffer_length
)
{
  if (nullptr == buffer)
    return ON_String::Encoding::Unknown;
  if (-1 == buffer_length)
    buffer_length = ON_String::Length(buffer);

  if (buffer_length <= 0)
    return ON_String::Encoding::Unknown;

  if (ON_String::IsPossibleEncoding(ON_String::Encoding::ASCII, buffer, buffer_length))
    return ON_String::Encoding::ASCII;
  if (ON_String::IsPossibleEncoding(ON_String::Encoding::UTF8, buffer, buffer_length))
    return ON_String::Encoding::UTF8;
  if (ON_String::IsPossibleEncoding(ON_String::Encoding::BIG5andASCII, buffer, buffer_length))
    return ON_String::Encoding::BIG5andASCII;
  if (ON_String::IsPossibleEncoding(ON_String::Encoding::SloppyUTF8, buffer, buffer_length))
    return ON_String::Encoding::SloppyUTF8;

  return ON_String::Encoding::Unknown;
}

const ON_String ON_String::ToUTF8(
  const char* buffer,
  int buffer_length
)
{
  if (nullptr == buffer)
    return ON_String::EmptyString;
  if (-1 == buffer_length)
    buffer_length = ON_String::Length(buffer);
  if (buffer_length <= 0)
    return ON_String::EmptyString;

  unsigned bad_utf32_count = 0;
  ON_SimpleArray<ON__UINT32> utf32;

  const ON_String::Encoding e = ON_String::ProbableEncoding(buffer, buffer_length);
  switch (e)
  {
  case ON_String::Encoding::ASCII:
  case ON_String::Encoding::UTF8:
    return ON_String(buffer, buffer_length);
    break;

  case ON_String::Encoding::SloppyUTF8:
    // ON_String -> ON_wString cleans up the slop.
    // ON_wString -> ON_String converts the wchar_t UTF-X encoding to UTF-8.
    return ON_String(ON_wString(ON_String(buffer, buffer_length)));
    break;

  case ON_String::Encoding::BIG5andASCII:
    bad_utf32_count = Internal_Big5ToUTF32(buffer, buffer_length, utf32);
    break;

  default:
    break;
  }

  const unsigned utf32_count = utf32.UnsignedCount();
  if (utf32_count > 0 && utf32_count >= 2* bad_utf32_count)
  {
    unsigned int error_status = 0;
    const unsigned int error_mask = 0xFFFFFFFFu;
    const int utf8_count = ON_ConvertUTF32ToUTF8(
      false, // bTestByteOrder,
      utf32.Array(),
      utf32.Count(),
      nullptr, // char* sUTF8,
      0, // int sUTF8_count,
      &error_status,
      error_mask,
      ON_UnicodeCodePoint::ON_ReplacementCharacter,
      nullptr //const ON__UINT32 * *sNextUTF32
    );
    if (utf8_count > 0)
    {
      error_status = 0;
      ON_String utf8;
      utf8.ReserveArray(utf8_count);
      utf8.SetLength(utf8_count);
      ON_ConvertUTF32ToUTF8(
        false, // bTestByteOrder,
        utf32.Array(),
        utf32.Count(),
        utf8.Array(),
        utf8_count,
        &error_status,
        error_mask,
        ON_UnicodeCodePoint::ON_ReplacementCharacter,
        nullptr //const ON__UINT32 * *sNextUTF32
      );
      return utf8;
    }
  }

  return ON_String::EmptyString;
}

const ON_String ON_String::ToUTF8() const
{
  if (IsPossibleEncoding(ON_String::Encoding::UTF8))
    return *this;
  return ON_String::ToUTF8( this->Array(), this->Length() );
}


const ON_String ON_String::ToBIG5(
  const char* buffer,
  int buffer_length,
  int* error_count
)
{
  if (nullptr != error_count)
    *error_count = 0;

  if (nullptr == buffer)
    return ON_String::EmptyString;

  if (-1 == buffer_length)
    buffer_length = ON_String::Length(buffer);
  if (buffer_length <= 0 || buffer_length > ON_String::MaximumStringLength)
    return ON_String::EmptyString;

  switch (ON_String::ProbableEncoding(buffer,buffer_length))
  {
  case ON_String::Encoding::ASCII:
  case ON_String::Encoding::BIG5andASCII:
    return ON_String(buffer,buffer_length);
    break;

  case ON_String::Encoding::UTF8:
  case ON_String::Encoding::SloppyUTF8:
  {
    const ON_SimpleArray< ON_Big5UnicodePair>& unicode_to_big5 = ON_Big5UnicodePair::UnicodeToBig5();

    const int big5_capacity = 2 * buffer_length;
    int big5_len = 0;
    ON_String big5;
    char* big5_buffer = big5.ReserveArray(big5_capacity + 1);

    int code_point_count = 0;
    int big5_code_point_count = 0;
    int fail_count = 0;
    int delta_i = 0;
    for (int i = 0; i < buffer_length; i += (delta_i > 0 ? delta_i : 1))
    {
      ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::MaskErrors;
      e.m_error_code_point = ON_UnicodeCodePoint::ON_InvalidCodePoint;
      ON__UINT32 unicode_code_point = e.m_error_code_point;
      delta_i = ON_DecodeUTF8(
        buffer + i,
        buffer_length - i,
        &e,
        &unicode_code_point
      );
      ++code_point_count;

      ON_Big5UnicodePair pair = ON_Big5UnicodePair::Error;
      for (;;)
      {
        if (delta_i <= 0)
          break;
        if (false == ON_IsStandardUnicodeCodePoint(unicode_code_point))
          break;

        if (unicode_code_point >= 0 && unicode_code_point <= 0x7F)
        {
          // ASCII code point.
          pair = ON_Big5UnicodePair::Create(unicode_code_point, unicode_code_point);
          break;
        }

        const ON_Big5UnicodePair key = ON_Big5UnicodePair::Create(0, unicode_code_point);
        if (unicode_code_point != key.UnicodeCodePoint())
          break;
        const int k = unicode_to_big5.BinarySearch(&key, ON_Big5UnicodePair::CompareUnicodeCodePoint);
        if (k < 0)
          break;

        // BIG5 code point
        pair = unicode_to_big5[k];
        break;
      }

      const int big5_delta = pair.IsValid(true, true) ? pair.Big5().Encode(big5_buffer + big5_len, big5_capacity - big5_len) : 0;
      if (1 == big5_delta || 2 == big5_delta)
      {
        if (2 == big5_delta)
          ++big5_code_point_count;
        big5_len += big5_delta;
      }
      else
      {
        big5_buffer[big5_len++] = '?';
        ++fail_count;
      }
    }
    if (big5_code_point_count > 0 && 2 * fail_count < code_point_count)
    {
      big5.SetLength(big5_len);
      return big5;
    }
  }
  break;

  default:
    break;
  }
  return ON_String::EmptyString;
}

const ON_String ON_String::ToBIG5(
  int* error_count
) const
{
  const ON_String::Encoding e = this->ProbableEncoding();
  if (ON_String::Encoding::ASCII == e || ON_String::Encoding::BIG5andASCII == e)
    return *this;

  return ON_String::ToBIG5(this->Array(), this->Length(), error_count);
}

ON_CheckSum::ON_CheckSum()
{
  Zero();
}

ON_CheckSum::~ON_CheckSum()
{
  Zero();
}

void ON_CheckSum::Zero()
{
  m_size = 0;
  m_time = 0;
  for ( int i = 0; i < 8; i++ ) 
    m_crc[i] = 0;
}

bool ON_CheckSum::IsSet() const
{
  return ( 0 != m_size 
           || 0 != m_time 
           || 0 != m_crc[0]
           || 0 != m_crc[1]
           || 0 != m_crc[2]
           || 0 != m_crc[3]
           || 0 != m_crc[4]
           || 0 != m_crc[5]
           || 0 != m_crc[6]
           || 0 != m_crc[7]
           );           
}

bool ON_CheckSum::SetBufferCheckSum( 
                size_t size, 
                const void* buffer,
                time_t time
               )
{
  bool rc = false;
  Zero();
  if ( size != 0 && buffer != 0 )
  {
    m_size = (unsigned int)size;

    ON__INT32 crc = 0;
    size_t sz, maxsize = 0x40000;
    const unsigned char* p = (const unsigned char*)buffer;
    for ( int i = 0; i < 7; i++ )
    {
      if ( size > 0 )
      {
        sz = (size > maxsize) ? maxsize : size;
        crc = ON_CRC32(crc,sz,p);
        p += sz;
        size -= sz;
        maxsize *= 2;
      }
      m_crc[i] = crc;
    }
    if ( size > 0 )
    {
      crc = ON_CRC32(crc,size,p);
    }
    m_crc[7] = crc;
    rc = true;
  }
  else if ( 0 == size )
  {
    rc = true;
  }
  m_time = time;
  return rc;
}

bool ON::GetFileStats( const wchar_t* filename,
                       size_t* filesize,
                       time_t* create_time,
                       time_t* lastmodify_time
                      )
{
  bool rc = false;

  if (filesize)
    *filesize = 0;
  if (create_time)
    *create_time = 0;
  if (lastmodify_time)
    *lastmodify_time = 0;

  if ( filename && filename[0] )
  {
    FILE* fp = ON::OpenFile(filename,L"rb");
    if ( fp )
    {
      rc = ON::GetFileStats(fp,filesize,create_time,lastmodify_time);
      ON::CloseFile(fp);
    }
  }

  return rc;
}

bool ON::GetFileStats( FILE* fp,
                       size_t* filesize,
                       time_t* create_time,
                       time_t* lastmodify_time
                      )
{
  bool rc = false;

  if (filesize)
    *filesize = 0;
  if (create_time)
    *create_time = 0;
  if (lastmodify_time)
    *lastmodify_time = 0;

  if ( fp )
  {

#if defined(ON_COMPILER_MSC)

    // Microsoft compilers
    int fd = _fileno(fp);    
#if (_MSC_VER >= 1400)
    // VC 8 (2005) 
    // works for file sizes > 4GB 
    // when size_t is a 64 bit integer
    struct _stat64 sb;
    memset(&sb,0,sizeof(sb));
    int fstat_rc = _fstat64(fd, &sb);
#else
    // VC6 compiler
    // works on most compilers
    struct _stat sb;
    memset(&sb,0,sizeof(sb));
    int fstat_rc = _fstat(fd, &sb);
#endif

#else
    // works on most compilers
    int fd = fileno(fp);
    struct stat sb;
    memset(&sb,0,sizeof(sb));
    int fstat_rc = fstat(fd, &sb);
#endif


    if (0 == fstat_rc)
    {
      if (filesize)
        *filesize = (size_t)sb.st_size;
      if (create_time)
        *create_time = (time_t)sb.st_ctime;
      if (lastmodify_time)
        *lastmodify_time = (time_t)sb.st_mtime;
      rc = true;
    }
  }

  return rc;
}

bool ON::IsDirectory( const wchar_t* pathname )
{
  bool rc = false;

  if ( 0 != pathname && 0 != pathname[0] )
  {
    ON_wString buffer;
    const wchar_t* stail = pathname;
    while ( 0 != *stail )
      stail++;
    stail--;
    if ( '\\' == *stail || '/' == *stail ) 
    {
      const wchar_t trim[2] = {*stail,0};
      buffer = pathname;
      buffer.TrimRight(trim);
      if ( buffer.Length() > 0 )
        pathname = static_cast< const wchar_t* >(buffer);
    }
#if defined(ON_COMPILER_MSC)
    // this works on Windows
    struct _stat64 buf;
    memset(&buf,0,sizeof(buf));
    int stat_errno = _wstat64( pathname, &buf );
    if ( 0 == stat_errno && 0 != (_S_IFDIR & buf.st_mode) )
    {
      rc = true;
    }
#else
    ON_String s = pathname;
    const char* utf8pathname = s;
    rc = ON::IsDirectory(utf8pathname);
#endif
  }

  return rc;
}

bool ON::IsDirectory( const char* utf8pathname )
{
  bool rc = false;

  if ( 0 != utf8pathname && 0 != utf8pathname[0] )
  {
    ON_String buffer;
    const char* stail = utf8pathname;
    while ( 0 != *stail )
      stail++;
    stail--;
    if ( '\\' == *stail || '/' == *stail ) 
    {
      const char trim[2] = {*stail,0};
      buffer = utf8pathname;
      buffer.TrimRight(trim);
      if ( buffer.Length() > 0 )
        utf8pathname = static_cast< const char* >(buffer);
    }
#if defined(ON_COMPILER_MSC)
    // this works on Windows
    struct _stat64 buf;
    memset(&buf,0,sizeof(buf));
    int stat_errno = _stat64( utf8pathname, &buf );
    if ( 0 == stat_errno && 0 != (_S_IFDIR & buf.st_mode) )
    {
      rc = true;
    }
#else
    // this works on Apple and gcc implementations.
    struct stat buf;
    memset(&buf,0,sizeof(buf));
    int stat_errno = stat( utf8pathname, &buf );
    if ( 0 == stat_errno && S_ISDIR(buf.st_mode) )
    {
      rc = true;
    }
#endif
  }

  return rc;
}


int ON::IsOpenNURBSFile( FILE* fp )
{
  ON_String sStartSectionComment;
  int version = 0;
  if ( 0 != fp )
  {
    ON_BinaryFile archive(ON::archive_mode::read3dm,fp);
    if ( !archive.Read3dmStartSection(&version,sStartSectionComment) )
      version = 0;
  }
  return version;
}

int ON::IsOpenNURBSFile( const wchar_t* pathname )
{
  int version = 0;
  if ( 0 != pathname && 0 != pathname[0] )
  {
    FILE* fp = ON::OpenFile(pathname,L"rb");
    if ( 0 != fp )
    {
      version = ON::IsOpenNURBSFile(fp);
      ON::CloseFile(fp);
    }
  }
  return version;
}

int ON::IsOpenNURBSFile( const char* utf8pathname )
{
  int version = 0;
  if ( 0 != utf8pathname && 0 != utf8pathname[0] )
  {
    FILE* fp = ON::OpenFile(utf8pathname,"rb");
    if ( 0 != fp )
    {
      version = ON::IsOpenNURBSFile(fp);
      ON::CloseFile(fp);
    }
  }
  return version;
}

bool ON_CheckSum::SetFileCheckSum( FILE* fp )
{
  bool rc = false;
  Zero();
  if ( fp )
  {
    size_t filesize = 0;
    time_t filetime = 0;
    if ( ON::GetFileStats(fp,&filesize,nullptr,&filetime) )
    {
      m_time = filetime;
    }

    unsigned char buffer[1024];
    int count=1024;
    ON__INT32 crc = 0;
    size_t sz0 = 0, maxsize = 0x40000;

    for( int i = 0; i < 7; i++ )
    {
      sz0 += maxsize;
      while(1024 == count && m_size < sz0)
      {
        count = (int)fread( buffer, 1, 1024, fp ); // the (int) is for 64 bit size_t conversion
        if ( count > 0 )
        {
          m_size += count;
          crc = ON_CRC32( crc, count, buffer );
        }
      }
      maxsize *= 2;
      m_crc[i] = crc;
    }

    while(1024 == count)
    {
      count = (int)fread( buffer, 1, 1024, fp ); // the (int) is for 64 bit size_t conversion
      if ( count > 0 )
      {
        m_size += count;
        crc = ON_CRC32( crc, count, buffer );
      }
    }
    m_crc[7] = crc;

    rc = (filesize == m_size);
  }
  return rc;
}

bool ON_CheckSum::Write(ON_BinaryArchive& archive) const
{
  bool rc = false;
  if ( archive.Archive3dmVersion() < 4 )
  {
    // V3 files had other information
    // 48 bytes of zeros will work ok
    unsigned char b[48];
    memset(b,0,sizeof(b));
    rc = archive.WriteByte(48,b);
  }
  else
  {
    rc = archive.WriteBigSize(m_size);
    if (rc)
      rc = archive.WriteBigTime(m_time);
    if (rc)
      rc = archive.WriteInt(8,&m_crc[0]);
  }
  return rc;
}

bool ON_CheckSum::Read(ON_BinaryArchive& archive)
{
  bool rc;

  Zero();

  rc  = archive.ReadBigSize(&m_size);
  if (rc)
    rc = archive.ReadBigTime(&m_time);
  if (rc)
    rc = archive.ReadInt(8,&m_crc[0]);

  if (    archive.ArchiveOpenNURBSVersion() < 200603100 
       || archive.Archive3dmVersion() < 4 
       )
  {
    // ON_CheckSums in V3 archives and V4 archives with
    // version < 200603100 have the same size but an 
    // incompatible format.  These were not used.
    Zero();
  }

  return rc;
}


bool ON_CheckSum::SetFileCheckSum( const wchar_t* filename )
{
  bool rc = false;
  Zero();
  if ( 0 == filename || 0 == filename[0] )
  {
    rc = true;
  }
  else
  {
    FILE* fp = ON::OpenFile(filename,L"rb");
    if ( fp )
    {
      rc = SetFileCheckSum(fp);
      ON::CloseFile(fp);
    }
  }
  return rc;
}

bool ON_CheckSum::CheckBuffer( 
  size_t size, 
  const void* buffer
  ) const
{
  if ( m_size != size )
    return false;
  if ( 0 == size )
    return true;
  if ( 0 == buffer )
    return false;

  ON__UINT32 crc = 0;
  size_t sz, maxsize = 0x40000;
  const unsigned char* p = (const unsigned char*)buffer;
  for ( int i = 0; i < 7; i++ )
  {
    if ( size > 0 )
    {
      sz = (size > maxsize) ? maxsize : size;
      crc = ON_CRC32(crc,sz,p);
      p += sz;
      size -= sz;
      maxsize *= 2;
    }
    if ( m_crc[i] != crc )
      return false;
  }
  if ( size > 0 )
  {
    crc = ON_CRC32(crc,size,p);
  }
  if ( m_crc[7] != crc )
    return false;

  return true;
}

bool ON_CheckSum::CheckFile( 
  FILE* fp,
  bool bSkipTimeCheck
  ) const
{
  if ( !fp )
    return false;

  size_t filesize=0;
  time_t filetime=0;
  if ( ON::GetFileStats( fp, &filesize, nullptr, &filetime ) )
  {
    if ( m_size != filesize )
    {
      return false;
    }

    if ( !bSkipTimeCheck && m_time != filetime)
    {
      return false;
    }
  }

  unsigned char buffer[1024];
  int count=1024;
  ON__UINT32 crc = 0;
  size_t sz0 = 0, maxsize = 0x40000;
  size_t sz = 0;

  for( int i = 0; i < 7; i++ )
  {
    sz0 += maxsize;
    while(1024 == count && sz < sz0)
    {
      count = (int)fread( buffer, 1, 1024, fp ); // the (int) is for 64 bit size_t conversion
      if ( count > 0 )
      {
        sz += count;
        crc = ON_CRC32( crc, count, buffer );
      }
    }
    maxsize *= 2;
    if ( m_crc[i] != crc )
      return false;
  }

  while(1024 == count)
  {
    count = (int)fread( buffer, 1, 1024, fp ); // the (int) is for 64 bit size_t conversion
    if ( count > 0 )
    {
      sz += count;
      crc = ON_CRC32( crc, count, buffer );
    }
  }
  if (m_crc[7] != crc)
    return false;

  if ( sz != m_size )
    return false;

  return true;
}

bool ON_CheckSum::CheckFile( 
  const wchar_t* filename,
  bool bSkipTimeCheck
  ) const
{
  bool rc = false;
  if ( filename && filename[0] )
  {
    FILE* fp = ON::OpenFile(filename,L"rb");
    if ( fp )
    {
      rc = CheckFile(fp,bSkipTimeCheck);
      ON::CloseFile(fp);
    }
  }
  return rc;
}

void ON_CheckSum::Dump(ON_TextLog& text_log) const
{
  // Using %llu so this code is portable for both 32 and 64 bit
  // builds on a wide range of compilers.

  unsigned long long u; // 8 bytes in windows and gcc - should be at least as big
                        // as a size_t or time_t.

  text_log.Print("Checksum:");
  if ( !IsSet() )
    text_log.Print("zero (not set)\n");
  else
  {
    text_log.PushIndent();
    text_log.Print("\n");
    u = (unsigned long long)m_size;
    text_log.Print("Size: %llu bytes\n",u);
    u = (unsigned long long)m_time;
    text_log.Print("Last Modified Time: %u (seconds since January 1, 1970, UCT)\n",u);
    text_log.Print("CRC List: %08x, %08x, %08x, %08x, %08x, %08x, %08x, %08x\n",
                   m_crc[0],m_crc[1],m_crc[2],m_crc[3],m_crc[4],m_crc[5],m_crc[6],m_crc[7]
                   );
    text_log.PopIndent();
  }
}

/*
TODO for apple support
https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man3/wcscmp.3.html

 wcscasecmp_l(const wchar_t *s1, const wchar_t *s2, locale_t loc);
 wcsncasecmp_l(const wchar_t *s1, const wchar_t *s2, size_t n, locale_t loc);

 look in SetPOSIXLocale() to set up calls to opennurbs locale setter.

 ON_Locale will need to have posix locale_t available for apple functions.

*/
