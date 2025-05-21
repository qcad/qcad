#pragma once
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

#if !defined(OPENNURBS_SLEEPLOCK_INC_)
#define OPENNURBS_SLEEPLOCK_INC_

#define OPENNURBS_SLEEPLOCK_AVAILABLE

#if !defined(ON_COMPILER_MSC) || !defined(ON_RUNTIME_WIN)
// Use std::atomic_lock and std::this_thread::sleep_for(std::chrono::milliseconds(...))
#define ON_SLEEPLOCK_USES_STD_ATOMIC_FLAG
#else
// Windows uses InterlockedExchange() and ::Sleep(...) because it 
// is 1.5 times faster than std::atomic_lock.
#endif


class ON_CLASS ON_SleepLock
{
public:
  ON_SleepLock() = default;
  ~ON_SleepLock() = default;

private:
  ON_SleepLock(const ON_SleepLock&) = delete;
  ON_SleepLock& operator=(const ON_SleepLock&) = delete;

public:

  enum : unsigned int
  {
    ///<summary>
    /// The default ON_SleepLock interval is 1/20 of a second to wait between attempts to obtain the lock.
    ///</summary>
    DefaultWaitInterval = 50,

    ///<summary>
    /// A ON_SleepLock interval of 1 millisecond (1/1000 second).
    ///</summary>
    OneMillisecond = 1,

    ///<summary>
    /// A ON_SleepLock interval of 1 second.
    ///</summary>
    OneSecond = 1000,

    ///<summary>
    /// A ON_SleepLock interval of 1 minute.
    ///</summary>
    OneMinute = 60000
  };

  /*
  Description:
    ON_SleepLock::IsLocked() is not reliable. Do not use it. It will be deleted in the next SDK.
  Returns:
    An unreliable value.
  */
  ON_DEPRECATED_MSG("ON_SleepLock::IsLocked() is not reliable. Do not use it. It will be deleted in the next SDK.")
  bool IsLocked() const;

  /*
  Description:
    Gets the lock using a ON_SleepLock::DefaultWaitInterval millisecond wait interval with 
    no maximum waiting time.
  Returns:
    This version of GetLock() always returns true.
  Remarks:
    You must call ReturnLock() when finished using the protected resource.
  */
  bool GetLock();

  /*
  Description:
    Attempts to get the lock a single time.
  Returns:
    True if the lock was acquired. False if the lock was not acquired because it was already locked.
  Remarks:
    If GetLockOrReturnFalse() returns true, then you must call ReturnLock() when finished using the protected resource.
    If GetLockOrReturnFalse() returns false, then you must not call ReturnLock().
  */
  bool GetLockOrReturnFalse();

  /*
  Description:
    Gets the lock using a the specified waiting interval
    and maximum waiting time.
  Parameters:
    interval_wait_msecs - [in]
      number of milliseconds to wait between checking for the lock.
      If interval_wait_msecs is 0, then ON_SleepLock::DefaultWaitInterval is used.
      If interval_wait_msecs > max_wait_msecs > 0,
      then one attempt is made to get the lock.
    max_wait_msecs - [in]
      maximum number of milliseconds to wait for lock.
      If max_wait_msecs is 0, then no maximum waiting time is used.
  Returns:
    True if the lock is obtained.
    False if the maximum waiting time expired without getting
    the lock.

    If GetLock() returns true, then you must call ReturnLock() when finished using the protected resource.
    If GetLock() returns false, then you must not call ReturnLock().
  Remarks:
     It is easy and clear to people reading your code if you use values
     like 
        ON_SleepLock::OneSecond, 
        ON_SleepLock::OneSecond/10,
        47*ON_SleepLock::OneSecond,
        ON_SleepLock::OneMinute,
        or
        ON_SleepLock::OneMinute/3
     to specify the values for interval_wait_msecs and max_wait_msecs.
  */
  bool GetLock( 
    unsigned int interval_wait_msecs,
    unsigned int max_wait_msecs
    );

  bool GetLock( 
    unsigned int interval_wait_msecs,
    unsigned int max_wait_msecs,
    bool bStealLockAfterWaiting
    );

  /*
  Description:
    Unconditionally returns the lock.
  Returns:
    True if the lock was changed from locked to unlocked.
    False if the lock was already unlocked.
  */
  bool ReturnLock();

private:
  // When locked m_locked = 1, otherwise m_locked = 0 ;
#if defined(ON_SLEEPLOCK_USES_STD_ATOMIC_FLAG)
  mutable std::atomic_flag m_lockedX = ATOMIC_FLAG_INIT; // = 0
#else
  // 1.5 times faster on Windows 10
  int m_locked = 0; 
#endif
};

class ON_CLASS ON_SleepLockGuard
{
public:
  /*
  Description:
    Calls sleep_lock.GetLock().
  Parameters:
    sleep_lock - [in]
      ON_SleepLock to manage.
  */
  ON_SleepLockGuard(class ON_SleepLock& sleep_lock);

  // Used by The ThreadSafe...() functions and for expert users 
  // to use when managing memory controlled by this pool. Best
  // to ignore this unless you have a very clear idea of what
  // you are doing, why you are doing it, and when you are doing it.
  // Otherwise, you'll find yourself waiting forever on a nested
  // access request. 
  ON_SleepLockGuard(class ON_FixedSizePool& fsp);


  /*
  Description:
    Calls sleep_lock.GetLock(interval_wait_msecs,max_wait_msecs).
  Parameters:
    sleep_lock - [in]
      ON_SleepLock to manage.
  */
  ON_SleepLockGuard(
    class ON_SleepLock& sleep_lock,
    unsigned int interval_wait_msecs,
    unsigned int max_wait_msecs
    );

  /*
  Description:
    Calls sleep_lock.GetLock(interval_wait_msecs,max_wait_msecs,bStealLockAfterWaiting).
  Parameters:
    sleep_lock - [in]
      ON_SleepLock to manage.
  */
  ON_SleepLockGuard(
    class ON_SleepLock& sleep_lock,
    unsigned int interval_wait_msecs,
    unsigned int max_wait_msecs,
    bool bStealLockAfterWaiting
    );

  /*
  Description:
    Calls sleep_lock.ReturnLock().
  */
  ~ON_SleepLockGuard();

  /*
  Description:
    If this instance has the lock, it is returned and the destructor does nothing.
  */
  void ReturnLock();

  /*
  Returns:
    True if this instance currently has the lock.
  */
  const bool IsManagingLock() const;

private:
  // Keep m_sleep_lock private. Never add a function that provides access to m_sleep_lock.
  class ON_SleepLock& m_sleep_lock;
  bool m_bIsManagingLock = false;

private:
  ON_SleepLockGuard() = delete;
  ON_SleepLockGuard(const ON_SleepLockGuard&) = delete;
  ON_SleepLockGuard& operator=(const ON_SleepLockGuard&) = delete;

public:
  ON_SleepLockGuard(const class ON_Brep&);
};

#endif
