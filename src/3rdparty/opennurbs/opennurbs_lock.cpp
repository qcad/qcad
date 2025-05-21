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


#if defined(ON_COMPILER_CLANG)
ON_Lock::ON_Lock() ON_NOEXCEPT
: m_lock_value(ON_Lock::UnlockedValue)
{}
#endif

/*
Description:
  ON_TestIntLock is used as the test function in sleep locks that
  set 4 byte integer values.  If the input value of lock is test_value,
  then it is set to sleep_value.
Parameters:
  test_value - [in]
  sleep_value - [in]
  lock - [in/out]
    4 byte integer to test. 
    If lock == test_value, then lock is set to sleep_value. 
    If lock != test_value, then the value of lock is not changed
Returns:
  The input value of lock.
*/

/*
Description:
  ON_SetIntLock is used to unconditionally 
  lock = lock_value and return the original value of lock
  as an atomic operation.
  It is intended to be used when a sleep lock is employed to make
  setting the lock thread safe.
Parameters:
  lock - [in/out]
    4 byte integer to set
  lock_value - [in]
Returns:
  The input value of lock.
*/

int ON_Lock::IsLocked()
{
  const int is_locked = m_lock_value;
  return is_locked;
}

bool ON_Lock::GetDefaultLock()
{
  return GetLock(ON_Lock::DefaultLockedValue);
}

bool ON_Lock::ReturnDefaultLock()
{
  return ReturnLock(ON_Lock::DefaultLockedValue);
}

bool ON_Lock::GetLock(int lock_value)
{
  if ( ON_Lock::UnlockedValue == lock_value || ON_Lock::InvalidLockValue == lock_value )
    return false;
  int test_value = ON_Lock::UnlockedValue;
  const bool rc = m_lock_value.compare_exchange_strong(test_value, lock_value);
  return (rc && ON_Lock::UnlockedValue == test_value);
}

bool ON_Lock::ReturnLock(int lock_value)
{
  if ( ON_Lock::UnlockedValue == lock_value || ON_Lock::InvalidLockValue == lock_value )
    return false;
  int test_value = lock_value;
  const bool rc = m_lock_value.compare_exchange_strong(test_value,ON_Lock::UnlockedValue);
  return (rc && lock_value == test_value);
}

int ON_Lock::BreakLock()
{
  const int previous_lock_value = m_lock_value;
  m_lock_value = ON_Lock::UnlockedValue;
  return previous_lock_value;
}

