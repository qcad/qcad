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

// ON_SleepLock::IsLocked() is not reliable. Do not use it. It will be deleted in the next SDK.
bool ON_SleepLock::IsLocked() const
{
  // ON_SleepLock::IsLocked() is not reliable. Do not use it. It will be deleted in the next SDK.
#if defined(ON_SLEEPLOCK_USES_STD_ATOMIC_FLAG)
  const bool b = m_lockedX.test_and_set(std::memory_order_acquire);
  if (false == b)
    m_lockedX.clear(std::memory_order_release);
  return b;
#else
  return 0 != m_locked;
#endif
}

bool ON_SleepLock::GetLockOrReturnFalse()
{
  // returns true if the value of the m_locked changed from 0 to 1.
  // returns false if the value of m_locked was 1 and was not changed.
  // In all cases, the final value of m_locked = 1.

#if defined(ON_SLEEPLOCK_USES_STD_ATOMIC_FLAG)
  // std::atomic_flag.test_and_set
  // does the following as an atomic operation:
  //    bool b = m_lockedX;
  //    m_lockedX = true;
  //    // in all cases, the final value of m_lockedX = true.
  bool locked = m_lockedX.test_and_set(std::memory_order_acquire);
  return (false == locked);
#else
  // Windows int locked = InterlockedCompareExchange(((LONG*)(&(m_locked))), 1, 0)
  // does the following as an atomic operation:
  //    int locked = m_locked;
  //    if ( 0 == m_locked )
  //      m_locked = 1;
  //    // in all cases, the final value of m_locked = 1.
  int locked = InterlockedCompareExchange(((LONG*)(&(m_locked))), 1, 0);
  return (0 == locked);
#endif
}

bool ON_SleepLock::ReturnLock()
{
  // returns true if the input value of m_locked != 0.
  // returns false of the input value of m_locked = 0.
  // In all cases, the final value of m_locked = 0.

#if defined(ON_SLEEPLOCK_USES_STD_ATOMIC_FLAG)
  const bool b = m_lockedX.test_and_set(std::memory_order_acquire);
  m_lockedX.clear(std::memory_order_release);
  return b;
#else
  // Windows int locked = InterlockedExchange(((LONG*)(&(m_locked))),0);
  // does the following as an atomic operation:
  //    int locked = m_locked;
  //    m_locked = 0;
  //    // in all cases, the final value of m_locked = 0.
  int locked = InterlockedExchange(((LONG*)(&(m_locked))),0);
  return (0 != locked);
#endif
}

bool ON_SleepLock::GetLock()
{
  return GetLock(ON_SleepLock::DefaultWaitInterval,0);
}

bool ON_SleepLock::GetLock(
  unsigned int interval_wait_msecs,
  unsigned int max_wait_msecs
  )
{
  return GetLock(interval_wait_msecs,max_wait_msecs,false);
}

bool ON_SleepLock::GetLock( 
  unsigned int interval_wait_msecs,
  unsigned int max_wait_msecs,
  bool bStealLockAfterWaiting
  )
{
  // int locked = ON_IntSleepLock_Test(m_locked,0,1)
  // performs the following test and assignment in
  // an atomic operation.
  //
  // int locked = m_locked;
  // if ( 0 == locked )
  //   m_locked = 1;
  if ( GetLockOrReturnFalse() )
    return true; // acquired lock

  if ( interval_wait_msecs <= 0 )
    interval_wait_msecs = ON_SleepLock::DefaultWaitInterval;

  for(;;)
  {
    // Something else currently has this lock.

    // ON_PointerSleepLock_SuspendThisThread() suspends the thread
    // (not the process) for the specified number of milliseconds.
#if defined(ON_SLEEPLOCK_USES_STD_ATOMIC_FLAG)
    std::this_thread::sleep_for(std::chrono::milliseconds(interval_wait_msecs));
#else
    // Windows - sleep the thread (not the process)
    ::Sleep(interval_wait_msecs);
#endif

    // locked = ON_IntSleepLock_Test(m_locked,0,1)
    // performs the following test and assignment in
    // an atomic operation.
    //
    // locked = m_locked;
    // if ( 0 == locked )
    //   m_locked = 1;
    if ( GetLockOrReturnFalse() )
      return true; // acquired lock
    
    if ( max_wait_msecs > 0 )
    {
      if ( interval_wait_msecs >= max_wait_msecs )
      {
        if (bStealLockAfterWaiting)
        {
          // If the caller set max_wait_msecs to a value that is too small, 
          // has a bug in their code, then this is a bad idea, 
          // but it's also their own fault.
          //
          // If the resource is locked because another thread locked it and 
          // then forgot to unlock it or terminated before it could be unlocked,
          // then this is a good thing because it gets this thread unblocked 
          // and back in business.
          //
          ON_WARNING("Stealing a resource lock.");
          GetLockOrReturnFalse();
          return true;
        }

        // Give up and return false.
        break;
      }
      max_wait_msecs -= interval_wait_msecs;
    }
  }

  return false;  
}


ON_SleepLockGuard::ON_SleepLockGuard(class ON_SleepLock& sleep_lock)
  : m_sleep_lock(sleep_lock)
{
  m_bIsManagingLock = m_sleep_lock.GetLock();
}

ON_SleepLockGuard::ON_SleepLockGuard(class ON_FixedSizePool& fsp)
  : m_sleep_lock(fsp.m_sleep_lock)
{
  m_bIsManagingLock = m_sleep_lock.GetLock();
}

ON_SleepLockGuard::ON_SleepLockGuard(
  class ON_SleepLock& sleep_lock,
  unsigned int interval_wait_msecs,
  unsigned int max_wait_msecs
  )
  : m_sleep_lock(sleep_lock)
{
  m_bIsManagingLock = sleep_lock.GetLock(interval_wait_msecs,max_wait_msecs);
}

ON_SleepLockGuard::ON_SleepLockGuard(
  class ON_SleepLock& sleep_lock,
  unsigned int interval_wait_msecs,
  unsigned int max_wait_msecs,
  bool bStealLockAfterWaiting
  )
  : m_sleep_lock(sleep_lock)
{
  m_bIsManagingLock = sleep_lock.GetLock(interval_wait_msecs,max_wait_msecs,bStealLockAfterWaiting);
}

ON_SleepLockGuard::~ON_SleepLockGuard()
{
  ReturnLock();
}


void ON_SleepLockGuard::ReturnLock()
{
  if (m_bIsManagingLock)
  {
    m_bIsManagingLock = false;
    m_sleep_lock.ReturnLock();
  }
}

const bool ON_SleepLockGuard::IsManagingLock() const
{
  return m_bIsManagingLock;
}


