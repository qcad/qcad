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

#if !defined(OPENNURBS_TERMINATOR_INC_)
#define OPENNURBS_TERMINATOR_INC_

class ON_CLASS ON_Terminator
{
public:
  ON_Terminator();
  ~ON_Terminator();

  /*
  Description:
    Set the function that is called when a calculation wants
    to determine if the calculation should stop or continue.
  Parameters:
    callback_function - [in]
      * The function that is called when a calculation wants
        to determine if the calculation should stop or continue.
      * If this callback function returns true, the calculation will
        terminate as soon as possible.
      * If this callback function returns false, the calculation will
        continue.
      * The calculation thread calls in this callback function.
      * The callback function should do something that is fast and simple.
      Parameters passed to the callback function:
        context - [in] 
          the value of callback_context.
  Example:
            bool bStopCalculation = false;
  
            bool StopCalculation( ON__UINT_PTR context )
            {
              if ( 0 != context )
              {
                const bool* p = (const bool*)context;
                if ( *p )
                  return true; // terminate calculation as soon as possible
               }
               return false; // continue calculation
            }

            ...

            ON_Terminator terminator;
            terminator.SetTerminationQueryCallbackFunction(StopCalculation,(ON__UINT_PTR)(&bStopCalculation));
            ...
            Pass &terminator to a calculation and then set bStopCalculation = true to terminate it.
            The calculation will generally be running in another thread, but can be in the same
            thread if it is structured to pump windows messages or something similar.
  */
  void SetTerminationQueryCallbackFunction(
    bool (*callback_function)(ON__UINT_PTR context),
    ON__UINT_PTR callback_context
    );

  ON__UINT_PTR CallbackFunction() const;
  ON__UINT_PTR CallbackContext() const;

  void SetThreadId(
    ON__UINT_PTR thread_id
    );

  ON__UINT_PTR ThreadId() const;

  /*
  Description:
    Sets m_bTerminationRequested = true.
    All future calls to TerminationRequested(this) will return true.
  */
  void RequestTermination();

  /*
  Description:
    If terminator is not nullptr, sets terminator->m_bTerminationRequested = true.
    If terminator is not nullptr, all future calls to TerminationRequested(terminator)
    will return true.
  Parameters:
    terminator - [in] (can be nullptr)
  Remarks:
    This is convenience function and is identical to the code

    if (nullptr != terminator)
      terminator->RequestTermination();
  */
  static void RequestTermination(
    ON_Terminator* terminator
    );

  /*
  Description:
    A calculation calls ON_Terminator::TerminationRequested(terminator) 
    to determine if it should continue or quit.
  Parameters:
    terminator - [in]
      A pointer to an ON_Terminator or null pointer.
  Returns:
    True if the calculation should terminate as soon as possible.
    False if the calculation should continue.
  Example:    
            void MyLongCalculation( ..., ON_Terminator* terminator, ...)
            {
               for ( i = 0; i < count; i++ )
               {
                 if ( ON_Terminator::TerminationRequested(terminator) )
                   break;
                 ...
               }
            }
  */
  static bool TerminationRequested( ON_Terminator* terminator);

  /*
  Description:
    An expert user function to determine if a calculation should continue.    
  Parameters:
    terminator - [in]
      A pointer to an ON_Terminator or null pointer.
    callback_delta - [in]
      Minimum amount of time to delay between calls to the registered callback function
      in clock() time units.
      0 will omit making any call to the registered function.
      ON_Terminator::TerminationRequested( terminator ) uses a value of 
      callback_delta = CLOCKS_PER_SEC/10 meaning a maximum 
      of 10 callbacks per second.
  Returns:
    True if the calculation should terminate as soon as possible.
    False if the calculation should continue.
  Remarks:
    In general, call the ON_Terminator::TerminationRequested( terminator ).
  */
  static bool TerminationRequestedExpert( 
    ON_Terminator* terminator, 
    ON__UINT64 callback_delta
    );


  /*
  Description:
    If bAllow is true, the worker thread cancellation handling (escape key presses etc) will cause RequestTermination to be called.
    If bAllow is false, cancellation must be implemented through the callback function, otherwise all cancellation will be disabled.
  Parameters:
    bAllow - [in] (see above)
  */
  void SetAllowDefaultCancellationHandling(bool bAllow);

  /*
  Description:
    returns true if default cancellation processing is allowed, otherwise false.  See SetAllowDefaultCancellationHandling
  */
  bool AllowDefaultCancellationHandling(void) const;

private:
  bool (*m_callback_function)(ON__UINT_PTR) = nullptr;
  ON__UINT_PTR m_callback_context = 0;
  ON__UINT64 m_previous_query_clock = 0;
  bool m_bTerminationRequested = false;
  bool m_bAllowDefaultCancellationHandling = true;
  bool m_reserved1[6];
  ON__UINT_PTR m_thread_id = 0;
  ON__UINT64 m_reserved2[2];
};


#endif

