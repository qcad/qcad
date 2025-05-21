/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2015 Robert McNeel & Associates. All rights reserved.
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
*/

#if !defined(OPENNURBS_CPP_BASE_INC_)
#define OPENNURBS_CPP_BASE_INC_

// basic C++ declarations


#if !defined(UUID_DEFINED) && !defined(GUID_DEFINED)
// basic C++ declarations
bool operator==(const struct ON_UUID_struct& a, const struct ON_UUID_struct& b);
bool operator!=(const struct ON_UUID_struct& a, const struct ON_UUID_struct& b);
#endif

class ON_CLASS ON_StopWatch
{
public:
  ON_StopWatch() = default;
  ~ON_StopWatch() = default;
  ON_StopWatch(const ON_StopWatch&) = default;
  ON_StopWatch& operator=(const ON_StopWatch&) = default;

public:
  enum class State : unsigned char
  {
    ///<summary>
    /// The stopwatch is off.
    ///</summary>
    Off = 0, 

    ///<summary>
    /// The stopwatch is started and running. 
    ///</summary>
    Running = 1,

    ///<summary>
    /// The stopwatch has been started and stopped.
    ///</summary>
    Stopped = 2
  };

  /*
  Description:
    If the stopwatch is off or stopped, it is started. Otherwise nothing happens. 
  */
  void Start();

  /*
  Description:
    If the stopwatch is running, then it is stopped. Otherwise nothing happens. 
  Returns:
    If the stopwatch was running, the elapsed time from the most recent Start().
    Otherwise, 0.0 is returned.
  */
  double Stop();

  /*
  Description:
    The stopwatch is reset and turned off. Any previously set times are lost.
  */
  void Reset();

  /*
  Returns:
    Current state of the stopwatch.
  */
  ON_StopWatch::State CurrentState() const;


  /*
  Returns:
    The elapsed time in seconds.
  Remarks:
    If the stopwatch is running, the elapsed time is the duration from the most recent Start() to now.
    If the stopwatch is stopped, the elapsed time is the duration between the most recent Start() and Stop().
    If the stopwatch is off, the elapsed time is zero.
  */
  double ElapsedTime() const;

private:
  // current state
  ON_StopWatch::State m_state = ON_StopWatch::State::Off;
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: ... : class 'std::...' 
  //        needs to have dll-interface to be used by clients ...
  // m_start and m_stop are private and all code that manages them is explicitly implemented in the DLL.
  std::chrono::high_resolution_clock::time_point m_start; // most recent Start() time.
  std::chrono::high_resolution_clock::time_point m_stop; // most recent Stop() time.
#pragma ON_PRAGMA_WARNING_POP
};


#endif
