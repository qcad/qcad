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

#if !defined(OPENNURBS_UUID_INC_)
#define OPENNURBS_UUID_INC_

// ON_UUID is a 16 byte universally unique identifier
#if !defined(ON_UUID_DEFINED)
  // This code also exists in version.h, but needs to be here
  // to solve include ordering problems, and for standalone
  // opennurbs.dll builds.
  #define ON_UUID_DEFINED
  // ON_UUID is a 16 byte universally unique identifier
  #if defined(UUID_DEFINED)
  typedef UUID ON_UUID;
  #elif defined(GUID_DEFINED)
  typedef GUID ON_UUID;
  #else
  typedef struct ON_UUID_struct
  {
    unsigned int   Data1;    // 32 bit unsigned integer
    unsigned short Data2;    // 16 bit unsigned integer
    unsigned short Data3;    // 16 bit unsigned integer
    unsigned char  Data4[8];
    } ON_UUID;
  #endif
#endif


ON_BEGIN_EXTERNC

// All bits are zero in ON_nil_uuid and
// ON_UuidCompare( ON_nil_uuid, U ) < 0 if U != ON_nil_uuid.
extern ON_EXTERN_DECL const ON_UUID ON_nil_uuid;

// All bits are one in ON_max_uuid and
// ON_UuidCompare( U, ON_max_uuid ) < 0 if U != ON_max_uuid.
extern ON_EXTERN_DECL const ON_UUID ON_max_uuid;

// Application ids for the versions of Rhino that
// write 3dm files.  All userdata classed defined
// in the core Rhino.exe should use these ids
// as the application id.
// In situations where you want to use the id
// for the current version of Rhino, use
// ON_rhino_id and you won't have to update
// your code when Rhino versions roll.
extern ON_EXTERN_DECL const ON_UUID ON_rhino2_id;
extern ON_EXTERN_DECL const ON_UUID ON_rhino3_id;
extern ON_EXTERN_DECL const ON_UUID ON_rhino4_id;
extern ON_EXTERN_DECL const ON_UUID ON_rhino5_id;
extern ON_EXTERN_DECL const ON_UUID ON_rhino6_id;
extern ON_EXTERN_DECL const ON_UUID ON_rhino7_id;
extern ON_EXTERN_DECL const ON_UUID ON_rhino8_id;
extern ON_EXTERN_DECL const ON_UUID ON_rhino_id;

// Application ids for userdata written by versions
// of opennurbs before userdata had application ids.
extern ON_EXTERN_DECL const ON_UUID ON_v2_userdata_id;
extern ON_EXTERN_DECL const ON_UUID ON_v3_userdata_id;
extern ON_EXTERN_DECL const ON_UUID ON_v4_userdata_id;

// Application id for the versions of openNURBS that
// write userdata in 3dm files.  User data whose class
// definition is in opennurbs should use these
// ids as the user data application id.
// No other user data should use these ids.
//
// In situations where you want to use the id
// for the current version of opennurbs, use
// ON_opennurbs_id and you won't have to update
// your code when opennurbs versions roll.
#if defined(ON_COMPILING_OPENNURBS)
extern const ON_UUID ON_opennurbs4_id;
extern const ON_UUID ON_opennurbs5_id;
extern const ON_UUID ON_opennurbs6_id;
extern const ON_UUID ON_opennurbs7_id;
extern const ON_UUID ON_opennurbs8_id;
#endif
extern ON_EXTERN_DECL const ON_UUID ON_opennurbs_id;

/*
Description:
  Determine if an id is a Rhino application id.
Parameters:
  id - [in]
    id to test
Returns:
  0: id is not a Rhino application id
  N: id == ON_rhinoN_id, where "N" = 2,3,4,5,6,...
*/
ON_DECL
unsigned int ON_IsRhinoApplicationId(
  ON_UUID id
  );

/*
Description:
  Determine if an id is an opennurbs application id.
Parameters:
  id - [in]
    id to test
Returns:
  0: id is not an opennurbs application id
  N: id == ON_opennurbsN_id, where "N" = 4,5,6,...
*/
ON_DECL
unsigned int ON_IsOpennurbsApplicationId(
  ON_UUID id
  );

ON_END_EXTERNC

#if defined(ON_CPLUSPLUS)

/*
Description:
  Creates a new uuid.(&a,&b) compares two uuids.
Parameters:
  new_uuid - [out]
Returns:
  True if successful.
*/
ON_DECL 
bool ON_CreateUuid( ON_UUID& uuid );

ON_DECL 
ON_UUID ON_CreateId();

/*
Description:
  This function is used for in testing situations when an
  ON_UUID value needs to be repeatable.
Parameter:
  index_64_bit - [in]
    index_64_bit > 0 and index_64_bit <= 0X0000FFFFFFFFFFFF.
    Calling this function with the same index will create 
    an ON_UUID with the same value.
Returns:
  If index_64_bit = 0 or >0X0000FFFFFFFFFFFF, 
  then ON_nil_uuid is returned.
  Otherwise, a ON_UUID with the value
  xxxxxxxx-yyyy-11dc-9885-001372C33878
  where xxxxxxxxyyyy = the hexadecimal representation
  of index_64_bit.
  The returned id is not unique.
*/
ON_DECL
ON_UUID ON_NotUniqueIdFromIndex(
  ON__UINT64 index_64_bit
);

/*
Description:
  This function is used for in testing situations when an
  ON_UUID value needs to be repeatable.
Parameter:
  index_32_bit - [in]
    index_32_bit > 0.
    Calling this function with the same index will create 
    an ON_UUID with the same value.
Returns:
  If index_32_bit = 0, then ON_nil_uuid is returned.
  Otherwise, a ON_UUID with the value
  xxxxxxxx-yyyy-11dc-9885-001372C33878
  where xxxxxxxxyyyy = the hexadecimal representation
  of index_32_bit.
  The returned id is not unique.
*/
ON_DECL
ON_UUID ON_NotUniqueIdFromIndex(
  ON__UINT32 index_32_bit
);


/*
Description:
  This function is used for in testing situations when an
  ON_UUID value needs to be repeatable.
Parameter:
  not_unique_id - [in]
    A not unique id created by ON_NotUniqueIdFromIndex() or ON_NextNotUniqueId().
Returns:
  If not_unique_id was created by on of the NotUniqueId functions,
  then a ON_UUID with the value
  xxxxxxxx-yyyy-11dc-9885-001372C33878
  where xxxxxxxxyyyy = the hexadecimal representation
  of the int id's index + 1 is returned.
  Otherwise, NO_nil_uuid is returned.
  The returned id is not unique.
*/
ON_DECL
ON_UUID ON_NextNotUniqueId(
  ON_UUID not_unique_id
);

/*
Description:
  This function is used for in testing situations when an
  ON_UUID value needs to be repeatable.
Parameter:
  not_unique_id - [in]
    A not unique id created by ON_NotUniqueIdFromIndex() or ON_NextNotUniqueId().
Returns:
  If not_unique_id was created by on of the NotUniqueId functions,
  then the index of that id is returned. 
  Otherwise, 0 is return if not_unique_id is nil and
  0xFFFF00000000 is returned in all other cases.
*/ON_DECL
ON__UINT64 ON_IndexFromNotUniqueId(
  ON_UUID not_unique_id
);



//class ON_CLASS ON_Id : public ON_UUID
//{
//public:
//  ON_Id() = default;
//  ~ON_Id() = default;
//  ON_Id(const ON_Id&) = default;
//  ON_Id& operator=(const ON_Id&) = default;
//
//  ON_Id(const ON_UUID&);
//  ON_Id& operator=(const ON_UUID&);
//
//  operator ON_UUID&();
//  operator const ON_UUID&() const;
//  
//  static ON_Id Create();
//  static const ON_Id nil;
//
//  static int Compare(
//    const ON_Id& a, 
//    const ON_Id& b
//    );
//
//  static int ComparePtr(
//    const ON_Id* a, 
//    const ON_Id* b
//    );
//
//  static int CompareUUID(
//    const ON_UUID& a, 
//    const ON_UUID& b
//    );
//
//  static int CompareUUIDPtr(
//    const ON_UUID* a, 
//    const ON_UUID* b
//    );
//
//  bool IsNil() const;
//  bool IsNotNil() const;
//};
//
//bool operator==(const ON_Id& a, const ON_Id& b );
//bool operator==(const ON_UUID& a, const ON_Id& b );
//bool operator==(const ON_Id& a, const ON_UUID& b );
//
//bool operator!=(const ON_Id& a, const ON_Id& b );
//bool operator!=(const ON_UUID& a, const ON_Id& b );
//bool operator!=(const ON_Id& a, const ON_UUID& b );
//
//bool operator<=(const ON_Id& a, const ON_Id& b );
//bool operator<=(const ON_UUID& a, const ON_Id& b );
//bool operator<=(const ON_Id& a, const ON_UUID& b );
//
//bool operator>=(const ON_Id& a, const ON_Id& b );
//bool operator>=(const ON_UUID& a, const ON_Id& b );
//bool operator>=(const ON_Id& a, const ON_UUID& b );
//
//bool operator<(const ON_Id& a, const ON_Id& b );
//bool operator<(const ON_UUID& a, const ON_Id& b );
//bool operator<(const ON_Id& a, const ON_UUID& b );
//
//
//bool operator>(const ON_Id& a, const ON_Id& b );
//bool operator>(const ON_UUID& a, const ON_Id& b );
//bool operator>(const ON_Id& a, const ON_UUID& b );


/*
Description:
  This class is used by ON_UuidIndexList.  It is used when
  uuids are used to search for items that can be found by
  an integer index.
*/
class ON_CLASS ON_UuidIndex
{
public:
  static const ON_UuidIndex NilIndex; // uuid = nil, index = 0

  ON_UuidIndex() = default;
  ~ON_UuidIndex() = default;
  ON_UuidIndex(const ON_UuidIndex&) = default;
  ON_UuidIndex& operator=(const ON_UuidIndex&) = default;

  ON_UuidIndex(ON_UUID id, int index);

  /*
  Dictionary compare m_id and then m_i.
  */
  static 
  int CompareIdAndIndex( const ON_UuidIndex* a, const ON_UuidIndex* b );

  /*
  Dictionary compare m_id and then m_i.
  */
  static 
  int CompareIndexAndId( const ON_UuidIndex* a, const ON_UuidIndex* b );

  /*
  Compare m_id and ignore m_i.
  */
  static 
  int CompareId( const ON_UuidIndex* a, const ON_UuidIndex* b );

  /*
  Compare m_i and ignore m_id.
  */
  static 
  int CompareIndex( const ON_UuidIndex* a, const ON_UuidIndex* b );

  // In cases when there is a discrepancy between the m_id and
  // m_i, m_id is assumed to be valid unless comments where this
  // class is used indicate otherwise.
  ON_UUID m_id = ON_nil_uuid;
  int m_i = 0;
};


/*
Description:
  This class is used by ON_UuidIndexList.  It is used when
  uuids are used to search for items that can be found by
  an integer index.
*/
class ON_CLASS ON_UuidPtr
{
public:
  static const ON_UuidPtr NilPtr; // uuid = nil, ptr = 0;

  ON_UuidPtr() = default;
  ~ON_UuidPtr() = default;
  ON_UuidPtr(const ON_UuidPtr&) = default;
  ON_UuidPtr& operator=(const ON_UuidPtr&) = default;

  /*
  Dictionary compare m_id and then m_ptr.
  */
  static 
  int CompareIdAndPtr( const ON_UuidPtr* a, const ON_UuidPtr* b );

  /*
  Dictionary compare m_id and then m_ptr.
  */
  static 
  int ComparePtrAndId( const ON_UuidPtr* a, const ON_UuidPtr* b );

  /*
  Compare m_id and ignore m_ptr.
  */
  static 
  int CompareId( const ON_UuidPtr* a, const ON_UuidPtr* b );

  /*
  Compare m_ptr and ignore m_id.
  */
  static 
  int ComparePtr( const ON_UuidPtr* a, const ON_UuidPtr* b );

  // In cases when there is a discrepancy between the m_id and
  // m_ptr, m_id is assumed to be valid unless comments where this
  // class is used indicate otherwise.
  ON_UUID m_id = ON_nil_uuid;
  ON__UINT_PTR m_ptr = 0;
};

/*
Description:
  ON_UuidCompare(&a,&b) compares two uuids.
Parameters:
  a - [in]
  b - [in]
Returns:
  @untitled table
  -1    a < b
   0    a == b
  +1    a > b
Remarks:
  A nullptr pointer is considered < a non-nullptr pointer.
*/
ON_DECL 
int ON_UuidCompare( 
        const ON_UUID* a, 
        const ON_UUID* b 
        );

/*
Description:
  ON_UuidCompare(a,b) compares two uuids.
Parameters:
  a - [in]
  b - [in]
Returns:
  @untitled table
  -1    a < b
   0    a == b
  +1    a > b
*/
ON_DECL 
int ON_UuidCompare( 
        const ON_UUID& a, 
        const ON_UUID& b
        );

/*
Description:
  Test uuid to see if it is nil (identically zero).
Parameters:
  uuid - [in]
Returns:
  true if uuid is nil.
*/
ON_DECL
bool ON_UuidIsNil( 
        const ON_UUID& uuid 
        );

/*
Description:
  Test uuid to see if it is not nil (not identically zero).
Parameters:
  uuid - [in]
Returns:
  true if uuid is not nil (non zero)
*/
ON_DECL
bool ON_UuidIsNotNil( 
        const ON_UUID& uuid 
        );

/*
Description:
  Converts a string like
    "{85A08515-f383-11d3-BFE7-0010830122F0}" 
  into a uuid.
  The brackets are optional and are ignored.
  Hyphens can appear anywhere or be missing.
  The hex digits can be upper or lower case.
Parameters:
  s - [in]
Returns:
  uuid.  
  If the string is not a uuid, then ON_nil_uuid is returned.
*/
ON_DECL 
ON_UUID ON_UuidFromString( const char* s );

/*
Description:
  Converts a string like
    "{85A08515-f383-11d3-BFE7-0010830122F0}" 
  into a uuid.
  The brackets are optional and are ignored.
  Hyphens can appear anywhere or be missing.
  The hex digits can be upper or lower case.
Parameters:
  s - [in]
Returns:
  uuid.  
  If the string is not a uuid, then ON_nil_uuid is returned.
*/
ON_DECL 
ON_UUID ON_UuidFromString( const wchar_t* s );

/*
Description:
  Converts a uuid to a null terminated ASCII string like
     "85a08515-f383-11d3-bfe7-0010830122f0". 
Parameters:
  uuid - [in]
  s - [out]  The s[] char array must have length >= 37.  
             The returned char array will have a 36 
             character uuid in s[0..35] and a null in s[36].
Returns:
  The pointer to the array is returned.
*/
ON_DECL 
char* ON_UuidToString( const ON_UUID& uuid, char* s );


/*
Description:
  Converts a uuid to a null terminated UNICODE string like
     "85a08515-f383-11d3-bfe7-0010830122f0". 
Parameters:
  uuid - [in]
  s - [out]  The s[] wchar_t array must have length >= 37.  
             The returned char array will have a 36 
             character uuid in s[0..35] and a null in s[36].
Returns:
  The pointer to the array is returned.
*/
ON_DECL 
wchar_t* ON_UuidToString( const ON_UUID& uuid, wchar_t* s );

/*
Description:
  Parses a string like "85a08515-f383-11d3-bfe7-0010830122f0" 
  and returns the value as a uuid. Hyphens can appear anywhere
  and are ignored. Parsing stops at any character that is not
  a hexadecimal digit or hyphen.  Parsing stops after 32 hexadecimal
  digits are read;
Parameters:
  sUuid - [in]
  uuid - [out]
Returns:
  null 
    Parsing failed and uuid is set to ON_nil_uuid.
  non null 
    Parsing succeeded and uuid is set to the parsed value.
    The returned pointer is the character in sUUID immediately
    after the last parsed character.
*/
ON_DECL
const char* ON_ParseUuidString(
  const char* sUUID,
  ON_UUID* uuid
  );

class ON_String;

/*
Description:
  Converts a uuid to a null terminated string like
     "85a08515-f383-11d3-bfe7-0010830122f0". 
Parameters:
  uuid - [in]
  s - [out]
Returns:
  The pointer to the array is returned.
*/
ON_DECL 
const char* ON_UuidToString( const ON_UUID& uuid, ON_String& s);

class ON_wString;

/*
Description:
  Converts a uuid to a null terminated string like
     "85a08515-f383-11d3-bfe7-0010830122f0". 
Parameters:
  uuid - [in]
  s - [out]
Returns:
  The pointer to the array is returned.
*/
ON_DECL 
const wchar_t* ON_UuidToString( const ON_UUID& uuid, ON_wString& s);

ON_DECL
const ON_wString ON_IdToString(
  ON_UUID id
);

ON_DECL
const ON_wString ON_AddIdPrefixToString(
  const ON_UUID id,
  const wchar_t* separator,
  const wchar_t* source
  );

ON_DECL
const ON_wString ON_RemoveIdPrefixFromString(
  const ON_UUID id,
  const wchar_t* separator,
  const wchar_t* source
);

ON_DECL
const ON_wString ON_AddIdSuffixToString(
  const wchar_t* source,
  const wchar_t* separator,
  const ON_UUID id
);

ON_DECL
const ON_wString ON_RemoveIdSuffixFromString(
  const wchar_t* source,
  const wchar_t* separator,
  const ON_UUID id
);


#endif

#endif
