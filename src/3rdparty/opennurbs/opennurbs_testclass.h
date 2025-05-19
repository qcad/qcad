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

#if !defined(OPENNURBS_TEST_CLASS_INC_)
#define OPENNURBS_TEST_CLASS_INC_

#if defined(ON_CPLUSPLUS)

#if !defined(OPENNURBS_NO_STD_MUTEX)

class ON_CLASS ON_TestClass
{
public:
  ON_TestClass();
  ~ON_TestClass();
  ON_TestClass(const ON_TestClass&);
  ON_TestClass& operator=(const ON_TestClass&);

public:

  /*
  The first instance of a ON_TestClass has serial number 1.
  */
  const ON__UINT64 SerialNumber;

  /*
  If this class was created by the copy constructor, then
  CopiedFrom is the serial number of the source class.
  Otherwise, CopiedFrom is zero.
  */
  const ON__UINT64 CopiedFrom;

  /*
  Time this instance was constructed. 
  Seconds since Jan 1, 1970, UCT from C-runtime time(nullptr).
  */
  const ON__UINT64 ConstructedAt;
  
  /*
  Returns:
    Number of ON_TestClass instances that have been constructed.
  Remarks:
    Thread safe.
    If you need to know two or more of  ConstructedCount(), DestructedCount(),
    and CurrentCount() the same time, call GetCurrentAndConstructedCount().
  */
  static ON__UINT64 ConstructedCount();

  /*
  Returns:
    Number of ON_TestClass instances that have been destroyed.
  Remarks:
    Thread safe.
    If you need to know two or more of  ConstructedCount(), DestructedCount(),
    and CurrentCount() the same time, call GetCurrentAndConstructedCount().
  */
  static ON__UINT64 DestructedCount();

  /*
  Returns:
    Number of ON_TestClass instances that currently exist.
  Remarks:
    Thread safe.
    If you need to know two or more of  ConstructedCount(), DestructedCount(),
    and CurrentCount() the same time, call GetCurrentAndConstructedCount().
  */
  static ON__UINT64 CurrentCount();

  /*
  Parameters:
    constructed_count - [out]
      Number of ON_TestClass that have been constructed.
    current_count - [out]
      Number of ON_TestClass that currently exist.
  Remarks:
    Thread safe.
  */
  static void GetCurrentAndConstructedCount(
    ON__UINT64& constructed_count,
    ON__UINT64& current_count
  );

  /*
  Returns:
    String value.
  Remarks:
    Thread safe.
  */
  const ON_wString Value() const;

  /*
  Returns:
    String value.
  Remarks:
    Thread safe.
  */
  void SetValue(
    const ON_wString s
    );

  /*
  Returns:
    String value.
  Remarks:
    Thread safe.
  */
  void Dump(class ON_TextLog& text_log) const;

  /*
  Returns:
    A string with the format
    ON_TestClass[<SERIAL_NUMBER>] \"<STRING_VALUE>\"
    where <SERIAL_NUMBER> is this->SerialNumber and <STRING_VALUE>
    is the string returned by this->Value().

  Remarks:
    Thread safe.
  */
  const ON_wString ToString() const;

private:
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_mutex is private and all code that manages m_mutex is explicitly implemented in the DLL.
  //
  // m_local_mutex is used for thread safe access to instance members
  mutable std::mutex m_local_mutex;
#pragma ON_PRAGMA_WARNING_POP


  // ON_wString is multi-thread safe
private:
  ON_wString m_string;

private:
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // These are private and all code that manages m_mutex is explicitly implemented in the DLL.
  // internal_counter_mutex protects access to internal_* counters.
  static std::mutex internal_counter_mutex;
  static ON__UINT64 internal_CtorSerialNumberGenerator;
  static ON__UINT64 internal_PopulationCounter;
  static ON__UINT64 Internal_CounterHelper(
    int task, // 0 = construct, 1 = destruct, 2 = query
    ON__UINT64* constructed_count,
    ON__UINT64* current_count
  );
#pragma ON_PRAGMA_WARNING_POP
};

#endif

#endif

#endif
