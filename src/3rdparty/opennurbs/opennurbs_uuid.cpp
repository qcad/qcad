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
#if defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
#include "android_uuid/uuid.h"
#endif
#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

#if !defined(UUID_DEFINED) && !defined(GUID_DEFINED)

// When ON_UUID is a typdef for Microsoft 's UUID,
// the Microsoft compiler handles == and !=.
// When a ON_UUID is not a typedef for a Microsoft UUID,
// it is declared as a class and operator== and operator!= 
// need to be explicitly defined.

bool operator==(const struct ON_UUID_struct& a, const struct ON_UUID_struct& b)
{
  return (0==memcmp(&a,&b,sizeof(struct ON_UUID_struct)));
}

bool operator!=(const struct ON_UUID_struct& a, const struct ON_UUID_struct& b)
{
  return (0!=memcmp(&a,&b,sizeof(struct ON_UUID_struct)));
}

#endif

// used to map the correspondence between uuid strings and
// ON_UUIDs as an array of 16 bytes.

// for little endian CPUs (Intel, etc)
static const int little_endian_rho[16] = {3,2,1,0, 5,4, 7,6, 8,9, 10,11,12,13,14,15};

// for big endian CPUs (Motorola, MIPS, Sparc, etc.)
static const int big_endian_rho[16] = {0,1,2,3, 4,5, 6,7, 8,9, 10,11,12,13,14,15};

 
ON_UUID ON_CreateId()
{
  ON_UUID id;
  ON_CreateUuid(id);
  return id;
}

static const ON_UUID not_unique_id_base = {
    0,                                        // unsigned long  Data1;
    0,                                        // unsigned short Data2;
    // The Data 3 and Data4 values are based on the MAC address of a
    // network card that was destroyed circa 2000.
    0x11dc,                                   // unsigned short Data3;
    {0x98,0x85,0x00,0x13,0x72,0xc3,0x38,0x78} // unsigned char  Data4[8];
  };

static const ON_UUID ON_Internal_CreateNotUniqueSequentialId(
  ON__UINT64 index_64_bit
)
{
  // Creates a not unique and repeatable UUID value that has a valid format.
  //
  // It is based on the MAC address of a network card that
  // was destroyed circa 2000. The Time portion of the UUID is generated
  // from index_64_bit and will generally be well before the current time.
  // The reason for using this complicated approach is to insure
  // data structures using these i values will pass validty checking
  // that tests to see if the UUID has a valid format.

  if (0 == index_64_bit)
  {
    ON_ERROR("index_64_bit parameter cannot be zero.");
    return ON_nil_uuid;
  }

  const ON__UINT64 d2 = 0x10000;
  const ON__UINT64 data2 = index_64_bit % d2;
  const ON__UINT64 data1 = index_64_bit / d2;
  if ( data1 > 0xFFFFFFFF )
  {
    ON_ERROR("index_64_bit parameter is too large.");
    return ON_nil_uuid;
  }

  ON_UUID not_unique_id = not_unique_id_base;
  not_unique_id.Data1 = (ON__UINT32)data1;
  not_unique_id.Data2 = (ON__UINT16)data2;
  return not_unique_id;
}

ON_UUID ON_NotUniqueIdFromIndex(
  ON__UINT64 index_64_bit
)
{
  return ON_Internal_CreateNotUniqueSequentialId(index_64_bit);
}

ON_UUID ON_NotUniqueIdFromIndex(
  ON__UINT32 index
)
{
  return ON_Internal_CreateNotUniqueSequentialId((ON__UINT64)index);
}

ON_UUID ON_NextNotUniqueId(
  ON_UUID current_not_unique_id
)
{
  if (ON_nil_uuid == current_not_unique_id)
    return ON_Internal_CreateNotUniqueSequentialId(1);

  const ON__UINT64 current_not_unique_id_index = ON_IndexFromNotUniqueId(current_not_unique_id);
  return ON_Internal_CreateNotUniqueSequentialId(current_not_unique_id_index+1);
}

ON__UINT64 ON_IndexFromNotUniqueId(
  ON_UUID not_unique_id
)
{
  if (
    not_unique_id.Data3 == not_unique_id_base.Data3
    && *((const ON__UINT32*)(&not_unique_id.Data4[0])) == *((const ON__UINT32*)(&not_unique_id_base.Data4[0]))
    && *((const ON__UINT32*)(&not_unique_id.Data4[4])) == *((const ON__UINT32*)(&not_unique_id_base.Data4[4]))
    )
  {
    const ON__UINT64 data1 = (ON__UINT64)not_unique_id.Data1;
    const ON__UINT64 data2 = (ON__UINT64)not_unique_id.Data2;
    const ON__UINT64 index = data1 * 0x10000 + data2;
    return index;
  }

  ON_ERROR("not_unique_id was not created by ON_NotUniqueIdFromIndex().");
  return (ON_nil_uuid == not_unique_id) ? 0 : 0xFFFF00000000;
}

bool ON_CreateUuid( ON_UUID& new_uuid )
{
  // See http://www.faqs.org/rfcs/rfc4122.html for uuid details.

#if 0
  {
    // Use this code when testing reqires "repeatable uniqueness".
    // NEVER check in this code.
    static ON_UUID x = ON_nil_uid;
    x = ON_NextNotUniqueId(x);
    new_uuid = x;
#pramga message("warning: NEVER COMMIT THIS CODE - ON_CreateUuid in TEST MODE.")
  }
  return true;

#else

#if defined(ON_COMPILER_MSC)
  // Header: Declared in Rpcdce.h.
  // Library: Use Rpcrt4.lib  
#pragma comment(lib, "Rpcrt4.lib")
  ::UuidCreate(&new_uuid);
  //::UuidCreateSequential(&new_uuid); // faster but computer MAC address
                                       // identifies the user and some
                                       // customers may object.
  return true;
#elif defined(ON_RUNTIME_APPLE)
  // Header: #include <uuid/uuid.h>
  if ( ON::endian::little_endian == ON::Endian() )
  {
    // Intel cpu mac
    // The uuid_generate() function returns a UUID in network or 
    // big-endian order.  The rest of OpenNURBS assumes that a UUID
    // is stored in native byte order, so we switch the byte order
    // of the UUID.
    uuid_t apple_osx_uuid;
    uuid_generate(apple_osx_uuid);
    unsigned char* dst = (unsigned char*)&new_uuid;
    const unsigned char* src = (const unsigned char*)&apple_osx_uuid;
    *dst++ = src[little_endian_rho[ 0]]; 
    *dst++ = src[little_endian_rho[ 1]]; 
    *dst++ = src[little_endian_rho[ 2]]; 
    *dst++ = src[little_endian_rho[ 3]]; 
    *dst++ = src[little_endian_rho[ 4]]; 
    *dst++ = src[little_endian_rho[ 5]]; 
    *dst++ = src[little_endian_rho[ 6]]; 
    *dst++ = src[little_endian_rho[ 7]]; 
    *dst++ = src[little_endian_rho[ 8]]; 
    *dst++ = src[little_endian_rho[ 9]]; 
    *dst++ = src[little_endian_rho[10]]; 
    *dst++ = src[little_endian_rho[11]]; 
    *dst++ = src[little_endian_rho[12]]; 
    *dst++ = src[little_endian_rho[13]]; 
    *dst++ = src[little_endian_rho[14]]; 
    *dst   = src[little_endian_rho[15]]; 
  }
  else
  {
    // Motorola cpu mac
    uuid_generate((unsigned char*)&new_uuid);
  }
  
#if defined (ON_DEBUG)
  // OS X generates version 4 UUIDs.  Check that this is still true after changing the byte order.
  if ((new_uuid.Data3 & 0xF000) != 0x4000)
    ON_ERROR("ON_CreateUuid() failure 1");
  if (new_uuid.Data4[0] < 0x80 || new_uuid.Data4[0] >= 0xC0)
    ON_ERROR("ON_CreateUuid() failure 2");
#endif

  return true;
#else

#if defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
  uuid_generate((unsigned char*)&new_uuid);
  return true;
#else

  // You must supply a way to create unique ids or you 
  // will not be able to write 3dm files.
#error TODO - generate uuid
  memset(&new_uuid,0,sizeof(ON_UUID));
  return false;
#endif

#endif
#endif
}

const char* ON_ParseUuidString(const char* sUUID, ON_UUID* uuid)
{
  // NOTE WELL: This code has to work on non-Windows OSs and on
  //            both big and little endian CPUs.  On Windows OSs
  //            is must return the same result as 
  //            Windows's UuidFromString().
  //

  // string has format like "85A08515-F383-11d3-BFE7-0010830122F0"
  // or like "85A08515-F383-11d3-BFE7-0010830122F0".
  // Hyphens are optional and ignored.
  //
  // Windows users can use "guidgen" to create UUID strings.

  /*
  #if defined(ON_DEBUG) && defined(ON_RUNTIME_WIN)
  RPC_STATUS st;
  union
  {
  ON_UUID uuid;
  unsigned char b[16];
  } u1;
  st = UuidFromString( (unsigned char*)sUUID, &u1.uuid );
  #endif
  */

  static const int* rho = (ON::endian::big_endian == ON::Endian())
    ? big_endian_rho
    : little_endian_rho;

  union
  {
    ON_UUID uuid;
    unsigned char b[16];
  } u;
  bool bFailed;
  int bi, ci;
  unsigned char c;
  unsigned char byte_value[2];

  memset(&u, 0, sizeof(u));
  //for ( bi = 0; bi < 16; bi++ ) 
  //  u.b[bi] = 0;

  bFailed = sUUID ? false : true;

  if (!bFailed)
  {
    for (bi = 0; bi < 16; bi++)
    {
      ci = 0;
      byte_value[0] = 0;
      byte_value[1] = 0;
      while (ci < 2)
      {
        c = *sUUID;
        if (!c) {
          bFailed = true;
          break;
        }
        if (c >= 'A' && c <= 'F') {
          byte_value[ci++] = (c - 'A' + 10);
        }
        else if (c >= '0' && c <= '9') {
          byte_value[ci++] = (c - '0');
        }
        else if (c >= 'a' && c <= 'f') {
          byte_value[ci++] = (c - 'a' + 10);
        }
        else if (c != '-') {
          bFailed = true;
          break;
        }
        sUUID++;
      }
      if (bFailed)
        break;
      u.b[rho[bi]] = 16 * byte_value[0] + byte_value[1];
    }
  }

  if (bFailed) 
  {
    // 09 August 2006 John Morse
    // There are times when Rhino is looking for a plug-in but the SDK or command
    // allows the plug-in to be specified by name or UUID.  Rhino calls ON_UuidFromString()
    // to see if the string is a plug-in UUID so it knows if it should be comparing the string
    // or plug-in name when looking for a plug-in.  The ON_ERROR line makes the Rhino commands
    // generate an OpenNURBS message box (in DEBUG builds) when the command completes and is
    // a pain so I commented it out per Dale Lear.
    //ON_ERROR("ON_UuidFromString(): bad string passed in");
    u.uuid = ON_nil_uuid;
  }

  if (uuid)
    *uuid = u.uuid;

  return bFailed ? 0 : sUUID;
}

 
ON_UUID ON_UuidFromString( const char* sUUID )
{
  // NOTE WELL: This code has to work on non-Windows OSs and on
  //            both big and little endian CPUs.  On Windows OSs
  //            is must return the same result as 
  //            Windows's UuidFromString().
  //

  // string has format like "85A08515-F383-11d3-BFE7-0010830122F0"
  // or like "{85A08515-F383-11d3-BFE7-0010830122F0}".  Brackets
  // and hyphens are optional and ignored.
  //
  // Windows users can use "guidgen" to create UUID strings.

  /*
#if defined(ON_DEBUG) && defined(ON_RUNTIME_WIN)
  RPC_STATUS st;
  union 
  {
    ON_UUID uuid;
    unsigned char b[16];
  } u1;
  st = UuidFromString( (unsigned char*)sUUID, &u1.uuid );
#endif
*/

  static const int* rho = (ON::endian::big_endian == ON::Endian())
                        ? big_endian_rho 
                        : little_endian_rho;

  union 
  {
    ON_UUID uuid;
    unsigned char b[16];
  } u;
  bool bFailed;
  int bi, ci;
  unsigned char c;
  unsigned char byte_value[2];

  memset(&u,0,sizeof(u));
  //for ( bi = 0; bi < 16; bi++ ) 
  //  u.b[bi] = 0;

  bFailed = sUUID ? false : true;

  if ( !bFailed ) {
    while ( *sUUID && *sUUID <= ' ' ) // skip leading white space
      sUUID++;
    if ( *sUUID == '{' )
      sUUID++;
    for ( bi = 0; bi < 16; bi++ ) {
      ci = 0;
      byte_value[0] = 0;
      byte_value[1] = 0;
      while ( ci < 2 ) {
        c = *sUUID++;
        if ( !c ) {
          bFailed = true;
          break;
        }
        if ( c >= 'A' && c <= 'F' ) {
          byte_value[ci++] = (c-'A'+10);
        }
        else if ( c >= '0' && c <='9' ) {
          byte_value[ci++] = (c-'0');
        }
        else if ( c >= 'a' && c <= 'f' ) {
          byte_value[ci++] = (c-'a'+10);
        }
        else if ( c != '-' ) {
          bFailed = true;
          break;
        }
      }
      if ( bFailed )
        break;
      u.b[rho[bi]] = 16*byte_value[0] + byte_value[1];
    }
  }

  if ( bFailed ) {
    // 09 August 2006 John Morse
    // There are times when Rhino is looking for a plug-in but the SDK or command
    // allows the plug-in to be specified by name or UUID.  Rhino calls ON_UuidFromString()
    // to see if the string is a plug-in UUID so it knows if it should be comparing the string
    // or plug-in name when looking for a plug-in.  The ON_ERROR line makes the Rhino commands
    // generate an OpenNURBS message box (in DEBUG builds) when the command completes and is
    // a pain so I commented it out per Dale Lear.
    //ON_ERROR("ON_UuidFromString(): bad string passed in");
    u.uuid = ON_nil_uuid;
  }

/*
#if defined(ON_DEBUG) && defined(ON_RUNTIME_WIN)
  if ( memcmp( &u.uuid, &u1.uuid, 16 ) ) {
    ON_ERROR("ON_UuidFromString() failed");
  }
  if ( UuidCompare( &u.uuid, &u1.uuid, &st ) ) {
    ON_ERROR("ON_UuidFromString() failed");
  }
  if ( ON_UuidCompare( &u.uuid, &u1.uuid ) ) {
    ON_ERROR("ON_UuidCompare() failed");
  }
#endif
*/
  return u.uuid;
}


ON_UUID ON_UuidFromString( const wchar_t* sUUID )
{
  wchar_t w;
  char s[64];
  int i;
  if( nullptr == sUUID )
    return ON_nil_uuid;
  while ( *sUUID && *sUUID <= ' ' ) // skip leading white space
    sUUID++;
  if ( *sUUID == '{' )
    sUUID++;
  i = 0;
  while (i < 63 )
  {
    w = *sUUID++;
    if ( w >= 'A' && w <= 'F' )
      s[i++] = (char)w;
    else if ( w >= '0' && w <='9' )
      s[i++] = (char)w;
    else if ( w >= 'a' && w <= 'f' )
      s[i++] = (char)w;
    else if ( w != '-' ) 
      break;
  }
  s[i] = 0;

  return ON_UuidFromString(s);

}
 
ON_UuidIndex::ON_UuidIndex(ON_UUID id, int index)
  : m_id(id)
  , m_i(index)
{}
int ON_UuidIndex::CompareIdAndIndex( const ON_UuidIndex* a, const ON_UuidIndex* b )
{
  int i;
  if ( !a )
    return (b ? -1 : 0 );
  if ( !b )
    return 1;

  // compare id first
  if (0 == (i = ON_UuidCompare(&a->m_id, &b->m_id)))
  {
    if (a->m_i < b->m_i)
      i = -1;
    else if (a->m_i > b->m_i)
      i = 1;
  }

  return i;
}

int ON_UuidIndex::CompareIndexAndId( const ON_UuidIndex* a, const ON_UuidIndex* b )
{
  int i;
  if ( !a )
    return (b ? -1 : 0 );
  if ( !b )
    return 1;

  // compare index first
  if (a->m_i < b->m_i)
    i = -1;
  else if (a->m_i > b->m_i)
    i = 1;
  else
    i = ON_UuidCompare(&a->m_id,&b->m_id);

  return i;
}

int ON_UuidIndex::CompareId( const ON_UuidIndex* a, const ON_UuidIndex* b )
{
  if ( !a )
    return (b ? -1 : 0 );
  if ( !b )
    return 1;
  return ON_UuidCompare(&a->m_id,&b->m_id);
}

int ON_UuidIndex::CompareIndex( const ON_UuidIndex* a, const ON_UuidIndex* b )
{
  if ( !a )
    return (b ? -1 : 0 );
  if ( !b )
    return 1;
  if (a->m_i < b->m_i)
    return -1;
  if (a->m_i > b->m_i)
    return 1;
  return 0;
}

 
int ON_UuidPtr::CompareIdAndPtr( const ON_UuidPtr* a, const ON_UuidPtr* b )
{
  int i;
  if ( !a )
    return (b ? -1 : 0 );
  if ( !b )
    return 1;

  // compare id first
  if (0 == (i = ON_UuidCompare(&a->m_id, &b->m_id)))
  {
    if (a->m_ptr < b->m_ptr)
      i = -1;
    else if (a->m_ptr > b->m_ptr)
      i = 1;
  }

  return i;
}

int ON_UuidPtr::ComparePtrAndId( const ON_UuidPtr* a, const ON_UuidPtr* b )
{
  int i;
  if ( !a )
    return (b ? -1 : 0 );
  if ( !b )
    return 1;

  if (a->m_ptr < b->m_ptr)
    i = -1;
  else if (a->m_ptr > b->m_ptr)
    i = 1;
  else
    i = ON_UuidCompare(&a->m_id,&b->m_id);

  return i;
}

int ON_UuidPtr::CompareId( const ON_UuidPtr* a, const ON_UuidPtr* b )
{
  if ( !a )
    return (b ? -1 : 0 );
  if ( !b )
    return 1;
  return ON_UuidCompare(&a->m_id,&b->m_id);
}

int ON_UuidPtr::ComparePtr( const ON_UuidPtr* a, const ON_UuidPtr* b )
{
  if ( !a )
    return (b ? -1 : 0 );
  if ( !b )
    return 1;
  if (a->m_ptr < b->m_ptr)
    return -1;
  if (a->m_ptr > b->m_ptr)
    return 1;
  return 0;
}


// Test code for ON_UuidCompare
////{
////  RPC_STATUS rpc_status = 0;
////  ON_UUID a,b;
////  size_t sz = sizeof(a);
////  unsigned char* pa = (unsigned char*)&a;
////  unsigned char* pb = (unsigned char*)&b;
////  unsigned char u[10] = {0,1,3,63,64,65,127,128,129,255};
////  int x,y,z;
////  for ( int aa = 0; aa < 10; aa++ ) for ( int bb = 0; bb < 10; bb++ )
////  {
////    for ( size_t i = 0; i < sz; i++ )
////    {
////      memset(pa,0,sz);
////      pa[i] = u[aa];
////      for ( size_t j = 0; j < sz; j++ )
////      {
////        memset(pb,0,sz);
////        pb[j] = u[bb];
////        rpc_status = 0;
////        y = ON_UuidCompare(&a,&b);
////        z = ::UuidCompare(&a,&b,&rpc_status);
////        if ( y != z )
////        {
////          int mscomparediff = 99; 
////        }
////      }      
////    }
////  }
////}

int ON_UuidCompare( const ON_UUID* a, const ON_UUID* b )
{
  // NOTE WELL: This code has to work the same way
  //            on Windows and non-Windows OSs and on
  //            both big and little endian CPUs
  //            taking into account the way ON_UUIDs
  //            are read/written by ON_BinaryArchive.
  //
  //            On Windows, ::UuidCompare() must agree 
  //            with this function.

  if ( !a ) 
  {
    return b ? -1 : 0;
  }
  if ( !b )
    return 1;

  if ( a->Data1 < b->Data1 ) return -1;
  if ( a->Data1 > b->Data1 ) return  1;

  if ( a->Data2 < b->Data2 ) return -1;
  if ( a->Data2 > b->Data2 ) return  1;

  if ( a->Data3 < b->Data3 ) return -1;
  if ( a->Data3 > b->Data3 ) return  1;
  return memcmp(a->Data4,b->Data4,sizeof(a->Data4));
}
 
int ON_UuidCompare( const ON_UUID& a, const ON_UUID& b)
{
  return ON_UuidCompare(&a,&b);
}

bool ON_UuidIsNil( 
        const ON_UUID& uuid 
        )
{
  const ON__INT32* p = (const ON__INT32*)&uuid;
  return ( p[0] || p[1] || p[2] || p[3] ) ? false : true;
}


bool ON_UuidIsNotNil( 
        const ON_UUID& uuid 
        )
{
  const ON__INT32* p = (const ON__INT32*)&uuid;
  return ( p[0] || p[1] || p[2] || p[3] ) ? true : false;
}


char* ON_UuidToString( const ON_UUID& uuid, char* s)
{
  // s - [out]  The s[] char array must have length >= 37.  
  //            The returned char array will have a 36 
  //            character uuid in s[0..35] and a null in s[36].

  // NOTE WELL: 
  //   This code has to work on non-Windows OSs and on both big and
  //   little endian CPUs.  The result must satisfy
  //   uuid == ON_UuidFromString(ON_UuidToString(uuid,s))

  // 31 August 2005 Dale Lear
  //     Changed upper case to lower case so result is
  //     identical to the string returned by Windows' ::UuidToString().
  //static const char x[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  static const char x[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
  static const int addhyphen[16] = {0,0,0,1, 0,1, 0,1, 0,1,  0, 0, 0, 0, 0, 0};
  const unsigned char* b = (const unsigned char*)&uuid;
  char* p;
  int i;
  
  static const int* rho = (ON::endian::big_endian == ON::Endian())
                        ? big_endian_rho 
                        : little_endian_rho;

  // 5 December 2002 Dale Lear:
  //   There is either a bug in Purify (likely) or perhaps a bug in the 
  //   way Microsoft compiles  c>>4 when c is an unsigned char.  In any
  //   case, changing c to an unsigned int makes purify happy and should
  //   work just as well.
  //
  //unsigned char c;

  unsigned int c;

  if ( !s )
    return 0;
  p = s;
  for ( i = 0; i < 16; i++ ) {
    c = b[rho[i]];
    *p++ = x[c>>4];  // purify gripes here if c is an unsigned char - the code runs fine.
    *p++ = x[c&0x0F];
    if ( addhyphen[i] )
      *p++ = '-';
  }
  *p = 0;

#if defined(ON_DEBUG)
  {
    ON_UUID u = ON_UuidFromString(s);
    if ( ON_UuidCompare(&u,&uuid) ) {
      ON_ERROR("ON_UuidToString() bug"); // <- breakpoint here
    }
  }
#endif

  return s;
}

wchar_t* ON_UuidToString( const ON_UUID& uuid, wchar_t* s)
{
  // s - [out]  The s[] char array must have length >= 37.  
  //            The returned char array will have a 36 
  //            character uuid in s[0..35] and a null in s[36].

  // NOTE WELL: 
  //   This code has to work on non-Windows OSs and on both big and
  //   little endian CPUs.  The result must satisfy
  //   uuid == ON_UuidFromString(ON_UuidToString(uuid,s))
  char x[37];
  if ( s && ON_UuidToString(uuid,x) )
  {
    int i;
    for (i = 0; i < 37; i++ )
    {
      s[i] = (wchar_t)x[i];
    }
  }
  else
  {
    s = 0;
  }
  return s;
}

 
const char* ON_UuidToString( const ON_UUID& uuid, ON_String& s )
{
  char x[37];
  s = ON_UuidToString( uuid, x );
  return s.Array();
}

 
const wchar_t* ON_UuidToString( const ON_UUID& uuid, ON_wString& s )
{
  wchar_t x[37];
  s = ON_UuidToString( uuid, x );
  return s.Array();
}


const ON_wString ON_IdToString(
  ON_UUID id
)
{
  ON_wString s;
  ON_UuidToString(id, s);
  return s;
}

const ON_wString ON_AddIdPrefixToString(
  const ON_UUID id,
  const wchar_t* separator,
  const wchar_t* source
)
{
  ON_wString s = ON_IdToString(id);
  s += separator;
  s += source;
  return s;
}

ON_DECL
const ON_wString ON_RemoveIdPrefixFromString(
  const ON_UUID id,
  const wchar_t* separator,
  const wchar_t* source
)
{
  ON_wString s(source);
  ON_wString prefix = ON_IdToString(id);
  prefix += separator;
  return s.RemovePrefix(prefix,ON_Locale::Ordinal,true);
}

ON_DECL
const ON_wString ON_AddIdSuffixToString(
  const wchar_t* source,
  const wchar_t* separator,
  const ON_UUID id
)
{
  ON_wString s(source);
  s += separator;
  s += ON_IdToString(id);
  return s;

}

ON_DECL
const ON_wString ON_RemoveIdSuffixFromString(
  const wchar_t* source,
  const wchar_t* separator,
  const ON_UUID id
)
{
  ON_wString s(source);
  ON_wString suffix(separator);
  suffix += ON_IdToString(id);
  return s.RemoveSuffix(suffix,ON_Locale::Ordinal,true);
}
