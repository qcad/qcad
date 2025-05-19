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

#if !defined(OPENNURBS_ERROR_INC_)
#define OPENNURBS_ERROR_INC_

/*
// Macros used to log errors and warnings.  The ON_Warning() and ON_Error()
// functions are defined in opennurbs_error.cpp.
*/
#define ON_ERROR(msg) ON_ErrorEx(__FILE__,__LINE__,OPENNURBS__FUNCTION__,msg)
#define ON_WARNING(msg) ON_WarningEx(__FILE__,__LINE__,OPENNURBS__FUNCTION__,msg)
#define ON_ASSERT_OR_RETURN(cond,returncode) do{if (!(cond)) {ON_ErrorEx(__FILE__,__LINE__,OPENNURBS__FUNCTION__, #cond " is false");return(returncode);}}while(0)
#define ON_ASSERT_OR_RETURNVOID(cond) do{if (!(cond)) {ON_ErrorEx(__FILE__,__LINE__,OPENNURBS__FUNCTION__, #cond " is false");return;}}while(0)

// Do not use ON_ASSERT. If a condition can be checked by ON_ASSERT, then the
// code must be written detect and respond to that condition. This define will
// be deleted ASAP. It is being used to detect situations where a crash will
// occur and then letting the crash occur. 
#define ON_ASSERT(cond) ON_REMOVE_ASAP_AssertEx(cond,__FILE__,__LINE__,OPENNURBS__FUNCTION__, #cond " is false")


ON_BEGIN_EXTERNC

/*
// All error/warning messages are sent to ON_ErrorMessage().  Replace the
// default handler (defined in opennurbs_error_message.cpp) with something
// that is appropriate for debugging your application.
*/
ON_DECL
void ON_ErrorMessage( 
       int,         /* 0 = warning message, 1 = serious error message, 2 = assert failure */
       const char*  
       ); 

/*
Returns:
  Number of opennurbs errors since program started.
*/
ON_DECL
int ON_GetErrorCount(void);

/*
Returns:
  Number of opennurbs warnings since program started.
*/
ON_DECL
int ON_GetWarningCount(void);

/*
Returns:
  Number of math library or floating point errors that have 
  been handled since program started.
*/
ON_DECL
int ON_GetMathErrorCount(void);


ON_DECL
int ON_GetDebugErrorMessage(void);

ON_DECL
void ON_EnableDebugErrorMessage( int bEnableDebugErrorMessage );

ON_DECL
void ON_VARGS_FUNC_CDECL ON_Error(
  const char* file_name, /* __FILE__ will do fine */
  int line_number,       /* __LINE__ will do fine */
  const char* format,    /* format string */
  ...                    /* format ags */
  );

ON_DECL
void ON_VARGS_FUNC_CDECL ON_ErrorEx(
  const char* file_name,      /* __FILE__ will do fine */
  int line_number,            /* __LINE__ will do fine */
  const char* function_name,  /* OPENNURBS__FUNCTION__ will do fine */
  const char* format,         /* format string */
  ...                         /* format ags */
  );

ON_DECL
void ON_VARGS_FUNC_CDECL ON_Warning(
  const char* file_name, /* __FILE__ will do fine */
  int line_number,       /* __LINE__ will do fine */
  const char* format,    /* format string */
  ...                    /* format ags */
  );

ON_DECL
void ON_VARGS_FUNC_CDECL ON_WarningEx(
  const char* file_name,      /* __FILE__ will do fine */
  int line_number,            /* __LINE__ will do fine */
  const char* function_name,  /*OPENNURBS__FUNCTION__ will do fine */
  const char* format,         /* format string */
  ...                         /* format ags */
  );

// Ideally - these "assert" functions will be deleted when the SDK can be changed.
ON_DECL
void ON_VARGS_FUNC_CDECL ON_REMOVE_ASAP_AssertEx(
  int,        // if false, error is flagged
  const char* file_name,      /* __FILE__ will do fine */
  int line_number,            /* __LINE__ will do fine */
  const char* function_name,  /* OPENNURBS__FUNCTION__ will do fine */
  const char* format,         /* format string */
  ...                         /* format ags */
  );

ON_DECL
void ON_MathError( 
  const char*, /* sModuleName */
  const char*, /* sErrorType */
  const char*  /* sFunctionName */
  );

ON_END_EXTERNC

#if defined(ON_CPLUSPLUS)

class ON_CLASS ON_ErrorEvent
{
public:
  enum class Type : unsigned char
  {
    Unset = 0,
    Warning = 1,   // call to ON_WARNING / ON_Warning / ON_WarningEx
    Error = 2,     // call to ON_ERROR / ON_Error / ON_ErrorEx
    Assert = 3,    // ON_ASSERT (do not use ON_ASSERT - write code that handles errors and calls ON_ERROR)
    Custom = 4,
    SubDError = 5, // call to ON_SubDIncrementErrorCount()
    BrepError = 6, // call to ON_BrepIncrementErrorCount()
    NotValid = 7   // call to ON_IsNotValid()
  };

  static const char* TypeToString(
    ON_ErrorEvent::Type event_type
  );

  const ON_String ToString() const;

public:
  ON_ErrorEvent() = default;
  ~ON_ErrorEvent() = default;
  ON_ErrorEvent(const ON_ErrorEvent&);
  ON_ErrorEvent& operator=(const ON_ErrorEvent&);

  ON_ErrorEvent(
    ON_ErrorEvent::Type event_type,
    const char* file_name,
    unsigned int line_number,
    const char* function_name,
    const char* description
  );

  static const ON_ErrorEvent Create(
    ON_ErrorEvent::Type event_type,
    const char* file_name,
    unsigned int line_number,
    const char* function_name,
    const char* description
  );

  static const ON_ErrorEvent Unset;

  const char* FileName() const;
  const char* FunctionName() const;
  const char* Description() const;
  unsigned int LineNumber() const;
  ON_ErrorEvent::Type EventType() const;

  void Dump(
    class ON_TextLog& text_log
  ) const;

private:
  friend class ON_ErrorLog;

  ON_ErrorEvent::Type m_event_type = ON_ErrorEvent::Type::Unset;
  unsigned char m_reserved1 = 0;
  unsigned short m_reserved2 = 0;
  unsigned int m_line_number = 0;
  const char* m_file_name = nullptr;
  const char* m_function_name = nullptr;
  const char* m_description = nullptr;
  char m_buffer[128] = {};

  void Internal_CopyFrom(const ON_ErrorEvent& src);
};


class ON_CLASS ON_ErrorLog
{
public:
  enum : unsigned int
  {
    MaximumEventCount = 32
  };
public:
  ON_ErrorLog() = default;
  virtual ~ON_ErrorLog();
  ON_ErrorLog(const ON_ErrorLog&) = default;
  ON_ErrorLog& operator=(const ON_ErrorLog&) = default;

  /*
  Parameters:
    error_event - [in]
      event to add
  Returns:
    0: Event not added because maximum capacity reached.
    >0: Number of events after adding error_event.
  */
  virtual
  unsigned int Append(
    const ON_ErrorEvent& error_event
  );

  /*
  Returns:
    Total number of error events.
  */
  unsigned int Count() const;

  /*
  Parameters:
    i - [in]
      zero based event index.
  Returns
    Event at specified index or ON_ErrorEvent::Unset if the index is out of range.
  */
  const ON_ErrorEvent& Event(unsigned int i) const;

  void Clear();

  /*
  Returns:
    True if up to ON_ErrorLog::MaximumErrorCount error events will be saved in this to this error log.
    False if another error log is active.
  */
  bool EnableLogging();

  /*
  Description:
    Stop logging errors to this error log.
  */
  void DisableLogging();

  void Dump(
    class ON_TextLog& text_log
  ) const;

protected:
  unsigned int m_event_count = 0;
  ON_ErrorEvent m_events[ON_ErrorLog::MaximumEventCount];
};

#endif

#endif
