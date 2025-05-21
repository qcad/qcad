#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

ON_ProgressReporter::ON_ProgressReporter()
: m_callback_function(0)
, m_callback_context(0)
, m_fraction_complete(0.0)
, m_previous_callback_fraction_complete(-1.0) // any value <= -1.0 will work
{
  m_reserved[0] = 0;
  m_reserved[1] = 0;
  m_reserved[2] = 0;
  m_reserved[3] = 0;
}


ON_ProgressReporter::~ON_ProgressReporter()
{
  m_callback_function = 0;
  m_callback_context = 0;
}

void ON_ProgressReporter::SetSynchronousProgressCallbackFunction(
  void (*callback_function)(ON__UINT_PTR context,double fraction_complete),
  ON__UINT_PTR callback_context
  )
{
  if (    0 == callback_function
       || m_callback_function != callback_function
       || m_callback_context != callback_context
     )
  {
    m_callback_context = callback_context;
    m_callback_function = callback_function;
    m_previous_callback_fraction_complete = -1.0; // any value <= -1.0 will work
  }
}

void ON_ProgressReporter::ReportProgress( 
  ON_ProgressReporter* progress_reporter,
  double fraction_complete
  )
{
  if ( 0 != progress_reporter )
  {
    if (    fraction_complete > progress_reporter->m_fraction_complete 
         || progress_reporter->m_previous_callback_fraction_complete <= -1.0 
       )
    {
      if ( fraction_complete > progress_reporter->m_fraction_complete )
      {
        progress_reporter->m_fraction_complete = (fraction_complete < 1.0) ? fraction_complete : 1.0;
      }

      if ( 0 != progress_reporter->m_callback_function )
      {
        // callback at most 1026 times
        const double max_callback_count = 1024.0;
        if (    (progress_reporter->m_fraction_complete >= progress_reporter->m_previous_callback_fraction_complete + 1.0/max_callback_count )
             || (1.0 == progress_reporter->m_fraction_complete && progress_reporter->m_previous_callback_fraction_complete < 1.0)
           )
        {
          progress_reporter->m_callback_function(progress_reporter->m_callback_context,progress_reporter->m_fraction_complete);
          progress_reporter->m_previous_callback_fraction_complete = progress_reporter->m_fraction_complete;
        }
      }
    }
  }
}

void ON_ProgressReporter::ReportProgress(
  ON_ProgressReporter* progress_reporter,
  int i,
  int max_i
  )
{
  if ( i <= 0 )
    ON_ProgressReporter::ReportProgress( progress_reporter, 0.0 );
  else
    ON_ProgressReporter::ReportProgress( progress_reporter, i >= max_i ? 1.0 : ((double)i)/((double)max_i) );
}

void ON_ProgressReporter::ReportProgress(
  ON_ProgressReporter* progress_reporter,
  unsigned int i,
  unsigned int max_i
  )
{
  ON_ProgressReporter::ReportProgress( progress_reporter, i >= max_i ? 1.0 : ((double)i)/((double)max_i) );
} 

double ON_ProgressReporter::FractionComplete(
  ON_ProgressReporter* progress_reporter
  )
{
  return ( nullptr != progress_reporter ) ? progress_reporter->m_fraction_complete : ON_UNSET_VALUE;
}

ON_ProgressStepCounter ON_ProgressStepCounter::Create(
  ON_ProgressReporter* progress_reporter,
  unsigned int step_count
  )
{
  return ON_ProgressStepCounter::Create(
    progress_reporter,
    step_count,
    0.0, 1.0,
    step_count < 100 ? step_count : 100
    );
}

ON_ProgressStepCounter ON_ProgressStepCounter::Create(
  ON_ProgressReporter* progress_reporter,
  unsigned int step_count,
  double progress_interval_start,
  double progress_interval_finish,
  unsigned int maximum_progress_reports
  )
{
  if (nullptr != progress_reporter
    && step_count > 0
    && 0.0 <= progress_interval_start
    && progress_interval_start < progress_interval_finish
    && progress_interval_finish <= 1.0
    && maximum_progress_reports > 0
    )
  {
    ON_ProgressStepCounter counter;
    counter.m_step_index = 0;
    counter.m_step_count = step_count;
    counter.m_step_interval = (step_count <= maximum_progress_reports) ? step_count : (step_count/maximum_progress_reports);
    if ( counter.m_step_interval <= 0 )
      counter.m_step_interval = 1;
    counter.m_progress_interval_start = progress_interval_start;
    counter.m_progress_interval_finish = progress_interval_finish;
    counter.m_progress_reporter = progress_reporter;
    ON_ProgressReporter::ReportProgress(progress_reporter,counter.Progress());
    return counter;
  }

  return ON_ProgressStepCounter::Empty;
}


void ON_ProgressStepCounter::IncrementStep()
{
  if (m_step_index < m_step_count)
  {
    m_step_index++;
    if (0 == m_step_index % m_step_interval || m_step_index == m_step_count)
      ON_ProgressReporter::ReportProgress(m_progress_reporter,Progress());
  }
}

void ON_ProgressStepCounter::Finished()
{
  if (m_step_index < m_step_count)
  {
    m_step_index = m_step_count-1;
    IncrementStep();
  }
}


double ON_ProgressStepCounter::Progress() const
{
  if (m_step_index <= 0)
    return m_progress_interval_start;
  if (m_step_index >= m_step_count)
    return m_progress_interval_finish;
  const double s = ((double)m_step_index)/((double)m_step_count);
  return (1.0 - s)*m_progress_interval_start + s*m_progress_interval_finish;
}

unsigned int ON_ProgressStepCounter::Step() const
{
  return m_step_index;
}


unsigned int ON_ProgressStepCounter::StepCount() const
{
  return m_step_count;
}

