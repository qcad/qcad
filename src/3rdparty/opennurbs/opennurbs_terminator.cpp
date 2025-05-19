#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

ON_Terminator::ON_Terminator()
{
  m_reserved1[0] = false;
  m_reserved1[1] = false;
  m_reserved1[2] = false;
  m_reserved1[3] = false;
  m_reserved1[4] = false;
  m_reserved1[5] = false;
  m_reserved2[0] = 0;
  m_reserved2[1] = 0;
}

ON_Terminator::~ON_Terminator()
{
  m_callback_function = 0;
  m_callback_context = 0;
}

void ON_Terminator::SetTerminationQueryCallbackFunction(
  bool (*callback_function)(ON__UINT_PTR context),
  ON__UINT_PTR callback_context
  )
{
  if (    nullptr == callback_function 
       || callback_function != m_callback_function
       || callback_context != m_callback_context
     )
  {
    m_callback_context = callback_context;
    m_callback_function = callback_function;
    m_previous_query_clock = 0;
  }
}

ON__UINT_PTR ON_Terminator::CallbackFunction() const
{
  return reinterpret_cast<ON__UINT_PTR>(m_callback_function);
}

ON__UINT_PTR ON_Terminator::CallbackContext() const
{
  return m_callback_context;
}

void ON_Terminator::SetThreadId(
  ON__UINT_PTR thread_id
  )
{
  m_thread_id = thread_id;
}

ON__UINT_PTR ON_Terminator::ThreadId() const
{
  return m_thread_id;
}

void ON_Terminator::RequestTermination()
{
  m_bTerminationRequested = true;
}

void ON_Terminator::RequestTermination(
  ON_Terminator* terminator
  )
{
  if ( nullptr != terminator )
    terminator->RequestTermination();
}


bool ON_Terminator::TerminationRequested( ON_Terminator* terminator )
{
  return TerminationRequestedExpert( terminator, CLOCKS_PER_SEC/10 );
}

void ON_Terminator::SetAllowDefaultCancellationHandling(bool bAllow)
{
  m_bAllowDefaultCancellationHandling = bAllow;
}

bool ON_Terminator::AllowDefaultCancellationHandling(void) const
{
  return m_bAllowDefaultCancellationHandling;
}

bool ON_Terminator::TerminationRequestedExpert(
  ON_Terminator* terminator,
  ON__UINT64 callback_delta
  )
{
  if ( nullptr != terminator )
  {
    if ( terminator->m_bTerminationRequested )
      return true;

    if ( nullptr != terminator->m_callback_function && callback_delta > 0 )
    {
      const ON__UINT64 current_clock = clock();
      if ( 0 == terminator->m_previous_query_clock
           || current_clock < terminator->m_previous_query_clock // clock() rolled over
           || current_clock - terminator->m_previous_query_clock >= callback_delta
          )
      {
        terminator->m_previous_query_clock = current_clock;
        if ( terminator->m_callback_function(terminator->m_callback_context) )
        {
          terminator->m_bTerminationRequested = true;
          return true;
        }
      }
    }
  }

  return false;
}
 
