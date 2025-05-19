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

#if !defined(OPENNURBS_LOCK_INC_)
#define OPENNURBS_LOCK_INC_

/*
Description:
  ON_Lock is a thread safe lock semaphore. It is implemented using
  platform specific compare and set functions.
*/
class ON_CLASS ON_Lock
{
public:
#if defined(ON_COMPILER_CLANG)
  ON_Lock() ON_NOEXCEPT;
#else
  ON_Lock() = default;
#endif
  ~ON_Lock() = default;

  // Copy constructor and operator= are implicitly deleted because
  // __atomic_base<int, false> has a deleted copy constructor
  // ON_Lock(const ON_Lock&) = default;
  // ON_Lock& operator=(const ON_Lock&) = default;

  // ON_Lock::InvalidLockValue (= -1) may never be used as a lock value.
  enum : int
  {
    UnlockedValue = 0,
    DefaultLockedValue = 1,
    InvalidLockValue = -1
  };

  /*
  Returns:
    Current lock value
    ON_Lock::UnlockedValue indicates the the resource protected by the lock is available.
  */
  int IsLocked();

  /*
  Description:
    Calls GetLock(ON_Lock::DefaultLockedValue);
  Returns:
    True if the lock state was unlocked
    and the current lock value was changed from ON_Lock::UnlockedValue to ON_Lock::DefaultLockedValue.
    False otherwise.
  */
  bool GetDefaultLock();

  /*
  Description:
    Calls ReturnLock(ON_Lock::DefaultLockedValue);
  Returns:
    True if the lock state was locked with a lock value = ON_Lock::DefaultLockedValue
    and the current lock value was changed from ON_Lock::DefaultLockedValue to ON_Lock::UnlockedValue.
    False otherwise.
  */
  bool ReturnDefaultLock();

  /*
  Parameters:
    lock_value - [in]
      any value except ON_Lock::UnlockedValue or ON_Lock::InvalidLockValue.
      Typically ON_Lock::DefaultLockedValue is used.
  Returns:
    True if the lock_value parameter was valid and the current
    lock value was changed from ON_Lock::UnlockedValue to lock_value.
    False otherwise.
  */
  bool GetLock(int lock_value);

  /*
  Parameters:
    lock_value - [in]
      any value except ON_Lock::UnlockedValue or ON_Lock::InvalidLockValue.
      Typically this is the value that was passed to GetLock().
  Returns:
    True if the lock_value parameter was valid and the current
    lock value was changed from that value to zero.
    False otherwise.
  */
  bool ReturnLock(int lock_value);

  /*
  Description:
    Unconditionally sets the lock value to ON_Lock::UnlockedValue.
  Returns:
    previous value of the lock.
      ON_Lock::UnlockedValue indicates the lock was available
      otherwise the lock passed to GetLock() is returned
  */
  int BreakLock();

private:
  // It is important that sizeof(ON_Lock) = sizeof(int)
  // and that m_lock_value be an int.
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: 'ON_Lock::m_lock_value': struct 'std::atomic<int>' 
  //         needs to have dll-interface to be used by clients of class 'ON_Lock'
  // m_lock_value is private and all code that manages m_lock_value is explicitly implemented in the DLL.
private:
#if defined(ON_COMPILER_CLANG) || defined(ON_RUNTIME_LINUX) || defined(ON_RUNTIME_WASM)
    std::atomic<int> m_lock_value;
#else
  std::atomic<int> m_lock_value = ON_Lock::UnlockedValue;
#endif
#pragma ON_PRAGMA_WARNING_POP
};

#endif
