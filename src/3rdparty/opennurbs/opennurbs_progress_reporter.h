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

#if !defined(OPENNURBS_PROGRESS_REPORTER_INC_)
#define OPENNURBS_PROGRESS_REPORTER_INC_

/////////////////////////////////////////////////////////////
//
// Calculation use ON_ProgressReporter to 
// report progress to the calling code.
//
class ON_CLASS ON_ProgressReporter
{
public:
  ON_ProgressReporter();
  ~ON_ProgressReporter();

  /*
  Description:
    Set the function that is called when a calculation calls ReportProgress().
  Parameters:
    callback_function - [in]
      * This function is called when the calculation reports progress.
      * The calculation thread calls in this callback function.
      * The callback function should do something that is fast and simple,
        like post a message to a user interface control and return
        immediately.      
      Parameters passed to the callback function:
        context - [in] 
          the value of callback_context.
        fraction_complete - [in]
          A value between 0.0 and 1.0 indicating how much of the
          calculation is compete.
  Example:

              struct MyWindowsMessage
              {
                HWND m_hWnd;
                UINT m_Msg,
                WPARAM m_wParam
              };

              ...

              void MyProgressCallback(
                ON__UINT_PTR context,
                double fraction_complete
                )
              {
                if ( 0 != context )
                {
                  MyWindowsMessage* msg = (MyWindowsMessage*)context;
                  LPARAM lParam = (UINT)ceil(100.0*fraction_complete); // 0 to 100.
                  PostWindowsMessage(msg.m_hWnd,msg.m_Msg,msg.m_wParam,lParam);
                }
              }

              ...

              struct MyWindowsMessage my_msg;
              my_msg.m_hWnd = my progress bar window
              my_msg.m_Msg = RegisterWindowMessage(L"MyProgressBarWindowsMessage");
              my_msg.m_wParam = ...;

              ON_ProgressReporter pr;
              pr.SetSynchronousProgressCallbackFunction(MyProgressCallback,&my_msg);
              ...
              Pass &pr to a calculation function.  The calculation will generally be running
              in a different thread or allowing Windows messages to be pumped.
  */
  void SetSynchronousProgressCallbackFunction(
    void (*callback_function)(ON__UINT_PTR context,double fraction_complete),
    ON__UINT_PTR callback_context
    );

  /*
  Description:
    The calculation calls ON_ProgressReporter::ReportProgress to report
    its current progress.  If it is the first call to ReportProgress, 
    or the faction_complete is 1.0, or the fraction_complete has 
    increased a reasonable amount, then the callback function is called.
  Parameters:
    progress_reporter - [in]
      A pointer to an ON_ProgressReporter or null pointer.
    fraction_complete - [in]
      a value between 0.0 and 1.0 where 0.0 indicates the calculation
      is beginning and 1.0 indicates the calculation is complete.
  Example:    
            void MyLongCalculation( ..., ON_ProgressReporter* pr, ...)
            {
               ...
               for ( i = 0; i < count; i++ )
               {
                 ON_ProgressReporter::ReportProgress(pr,i/((double)count));   
                 ...
               }
               ON_ProgressReporter::ReportProgress(pr,1.0); // finished
               ...
            }
  */
  static void ReportProgress( 
    ON_ProgressReporter* progress_reporter,
    double fraction_complete
    );

  /*
  Description:
    The calculation calls ON_ProgressReporter::ReportProgress to report
    its current progress.  If it is the first call to ReportProgress, 
    or the faction_complete is 1.0, or the fraction_complete has 
    increased a reasonable amount, then the callback function is called.
  Parameters:
    progress_reporter - [in]
      A pointer to an ON_ProgressReporter or null pointer.
    fraction_complete - [in]
      a value between 0.0 and 1.0 where 0.0 indicates the calculation
      is beginning and 1.0 indicates the calculation is complete.
  Example:    
            void MyLongCalculation( ..., ON_ProgressReporter* pr, ...)
            {
               ...
               for ( i = 0; i < count; i++ )
               {
                 ON_ProgressReporter::ReportProgress(pr,i,count);   
                 ...
               }
               ON_ProgressReporter::ReportProgress(pr,1.0); // finished
               ...
            }
  */
  static void ReportProgress( 
    ON_ProgressReporter* progress_reporter,
    int i,
    int max_i
    );

  /*
  Description:
    The calculation calls ON_ProgressReporter::ReportProgress to report
    its current progress.  If it is the first call to ReportProgress, 
    or the faction_complete is 1.0, or the fraction_complete has 
    increased a reasonable amount, then the callback function is called.
  Parameters:
    progress_reporter - [in]
      A pointer to an ON_ProgressReporter or null pointer.
    fraction_complete - [in]
      a value between 0.0 and 1.0 where 0.0 indicates the calculation
      is beginning and 1.0 indicates the calculation is complete.
  Example:    
            void MyLongCalculation( ..., ON_ProgressReporter* pr, ...)
            {
               ...
               for ( i = 0; i < count; i++ )
               {
                 ON_ProgressReporter::ReportProgress(pr,i,count);   
                 ...
               }
               ON_ProgressReporter::ReportProgress(pr,1.0); // finished
               ...
            }
  */
  static void ReportProgress( 
    ON_ProgressReporter* progress_reporter,
    unsigned int i,
    unsigned int max_i
    );

  /*
  Description:
    The calculation may call ON_ProgressReporter::FractionComplete to get
    the current fraction completed.
  Parameters:
    progress_reporter - [in]
      A pointer to an ON_ProgressReporter or null pointer.
  Returns:
    ON_UNSET_VALUE is returned when progress_reporter is nullptr.
    Otherwise, a value between 0.0 and 1.0 is returned where 0.0 indicates
    the calculation is beginning and 1.0 indicates the calculation is complete.
  */
  static double FractionComplete( 
    ON_ProgressReporter* progress_reporter
    );

private:
  void (*m_callback_function)(ON__UINT_PTR,double);
  ON__UINT_PTR m_callback_context;
  double m_fraction_complete;
  
  // Information for the previous call to callbackFunction
  double m_previous_callback_fraction_complete;
  ON__UINT64 m_reserved[4];
};

class ON_CLASS ON_ProgressStepCounter
{
public:

  // This class makes it easy for functions to use a progress reporter.
  ON_ProgressStepCounter() = default;
  ~ON_ProgressStepCounter() = default;
  ON_ProgressStepCounter(const ON_ProgressStepCounter&) = default;
  ON_ProgressStepCounter& operator=(const ON_ProgressStepCounter&) = default;

  /*
  Description:
    When you have a process that needs to call a ON_ProgressReporter::ReportProgress()
    a reasonable number of times and you can calculate the number of steps your process 
    takes, then ON_ProgressStepCounter will handle all the details.
  Parameters:
    progress_reporter - [in]
      Parameter passed to ON_ProgressReporter::ReportProgress().
    step_count - [in]
      Number of steps.
  Remarks:
    This will create a ON_ProgressStepCounter that will call 
    ON_ProgressReporter::ReportProgress(progress_reporter) at most 101 times.
    The first call reports progress 0.0.
    The last call reports progress 1.0.
  */
  static ON_ProgressStepCounter Create(
    ON_ProgressReporter* progress_reporter,
    unsigned int step_count
    );

  /*
  Description:
    When you have a process that needs to call a ON_ProgressReporter::ReportProgress()
    a reasonable number of times and you can calculate the number of steps your process 
    takes, then ON_ProgressStepCounter will handle all the details.
  Parameters:
    progress_reporter - [in]
      Parameter passed to ON_ProgressReporter::ReportProgress().
    step_count - [in]
      Number of steps.
    progress_interval_start - [in]
    progress_interval_finish - [in]
      0.0 <= progress_interval_start < progress_interval_finish <= 1.0
    maximum_progress_reports - [in]
      Maximum number of times to call ON_ProgressReporter::ReportProgress()
      after the initial call reporting progress of progress_interval_start.
      10 to 100 are good values.
  */
  static ON_ProgressStepCounter Create(
    ON_ProgressReporter* progress_reporter,
    unsigned int step_count,
    double progress_interval_start,
    double progress_interval_finish,
    unsigned int maximum_progress_reports
    );

  static const ON_ProgressStepCounter Empty;

  /*
  Description:
    Call IncrementStep() after you complete each step.    
  */
  void IncrementStep();  

 /*
  Description:
    Call Finished() after you complete the process.
  */
  void Finished();

  double Progress() const;

  unsigned int Step() const;

  unsigned int StepCount() const;
private:
  ON_ProgressReporter* m_progress_reporter  = nullptr;
  unsigned int m_step_index = 0;
  unsigned int m_step_count = 0;
  unsigned int m_step_interval = 0;
  double m_progress_interval_start = 0.0;
  double m_progress_interval_finish = 0.0;
};

#endif
