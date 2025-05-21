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


// openNURBS Geometry Library Errors and Warnings
//
//   If an error condition occurs during a openNURBS Geometry Library
//   computation, the ON_Error() function is called, the computation is
//   stopped, and an error code (negative integer ) is returned.  If a
//   warning condition occurs during a Trout Lake Geometry Library 
//   computation, the ON_Warning() function is called and the computation
//   continues.
//
//   ON_GetErrorCount()
//   ON_GetWarningCount()
//   ON_Error()
//   ON_Warning()
//

#define ON_MAX_ERROR_MESSAGE_COUNT ((int)ON_ErrorLog::MaximumEventCount)

static int ON_ERROR_COUNT = 0;
static int ON_WARNING_COUNT = 0;
static int ON_MATH_ERROR_COUNT = 0;
class ON_ErrorLog* ON_ACTIVE_ERROR_LOG = nullptr;



static int ON_DEBUG_ERROR_MESSAGE_OPTION = 0;


int ON_GetErrorCount(void)
{
  return ON_ERROR_COUNT;	
}	

int ON_GetWarningCount(void)
{
  return ON_WARNING_COUNT;	
}	

int ON_GetMathErrorCount(void)
{
  return ON_MATH_ERROR_COUNT;	
}	


int ON_GetDebugErrorMessage(void)
{
  return ON_DEBUG_ERROR_MESSAGE_OPTION?true:false;
}


void ON_EnableDebugErrorMessage( int bEnableDebugErrorMessage )
{
  ON_DEBUG_ERROR_MESSAGE_OPTION = bEnableDebugErrorMessage ? 1 : 0;
}


void ON_MathError( 
        const char* sModuleName,
        const char* sErrorType,
        const char* sFunctionName
        )
{
  ON_MATH_ERROR_COUNT++;

  if ( 0 == sModuleName)
    sModuleName = "";
  if ( 0 == sErrorType )
    sErrorType = "";
  if ( 0 == sFunctionName )
    sFunctionName = "";

  if ( 0 != sModuleName[0] || 0 != sErrorType[0] || 0 != sFunctionName[0] )
  {
    ON_ErrorEx(__FILE__,__LINE__,sFunctionName,
              "Math library or floating point ERROR # %d module=%s type=%s function=%s",
              ON_MATH_ERROR_COUNT, 
              sModuleName, // rhino.exe, opennurbs.dll, etc.
              sErrorType,   
              sFunctionName
              );
  }
  else
  {
    ON_ErrorEx(__FILE__,__LINE__,sFunctionName,
              "Math library or floating point ERROR # %d",
              ON_MATH_ERROR_COUNT
              );
  }
}	

static void ON_IncrementErrorCount()
{
  ON_ERROR_COUNT++;
}

static void ON_IncrementWarningCount()
{
  ON_WARNING_COUNT++;
}

void ON_BrepIncrementErrorCount()
{
  ON_ERROR_COUNT++;
  ON_Brep::ErrorCount++;
} 

void ON_SubDIncrementErrorCount()
{
  ON_ERROR_COUNT++;
  ON_SubD::ErrorCount++;
} 


bool ON_IsNotValid()
{
  return false;
}

static bool ON_Internal_PrintErrorMessage()
{
  return (0 != ON_DEBUG_ERROR_MESSAGE_OPTION && ON_ERROR_COUNT <= ON_MAX_ERROR_MESSAGE_COUNT);
}

static bool ON_Internal_PrintWarningMessage()
{
  return (0 != ON_DEBUG_ERROR_MESSAGE_OPTION && ON_WARNING_COUNT <= ON_MAX_ERROR_MESSAGE_COUNT);
}


static bool ON_Internal_LogError()
{
  return (nullptr != ON_ACTIVE_ERROR_LOG);
}

static void ON_Internal_RecordErrorEvent(
  const ON_ErrorEvent& error_event,
  bool bPrint
  )
{
  if (nullptr != ON_ACTIVE_ERROR_LOG)
    ON_ACTIVE_ERROR_LOG->Append(error_event);


  if ( 0 == ON_DEBUG_ERROR_MESSAGE_OPTION )
    return;

  if (false == bPrint)
    return;

  
  const ON_ErrorEvent::Type error_type = error_event.EventType();
  ON_String s;      
  if ( ON_ErrorEvent::Type::Warning == error_type )
  {
    if (ON_WARNING_COUNT == ON_MAX_ERROR_MESSAGE_COUNT)
      s = ON_String::FormatToString("ON_WARNING # %d: ... suspending warning messages.", ON_WARNING_COUNT);
    else
      s = ON_String::FormatToString("ON_WARNING # %d: ", ON_WARNING_COUNT) + error_event.ToString();
  }
  else
  {
    if (ON_ERROR_COUNT == ON_MAX_ERROR_MESSAGE_COUNT)
      s = ON_String::FormatToString("ON_ERROR # %d: ... suspending error messages.", ON_ERROR_COUNT);
    else
      s = ON_String::FormatToString("ON_ERROR # %d: ", ON_ERROR_COUNT) + error_event.ToString();
  }

  if ( s.IsNotEmpty() )
  {
    int obsolete_type;
    switch (error_type)
    {
    case ON_ErrorEvent::Type::Unset:
      obsolete_type = 0;
      break;
    case ON_ErrorEvent::Type::Warning:
      obsolete_type = 0;
      break;
    case ON_ErrorEvent::Type::Error:
      obsolete_type = 1;
      break;
    case ON_ErrorEvent::Type::Assert:
      obsolete_type = 2;
      break;
    case ON_ErrorEvent::Type::Custom:
      obsolete_type = 0;
      break;
    case ON_ErrorEvent::Type::SubDError:
      obsolete_type = 0;
      break;
    case ON_ErrorEvent::Type::NotValid:
      obsolete_type = 0;
      break;
    default:
      obsolete_type = 0;
      break;
    }
    ON_ErrorMessage(obsolete_type,static_cast<const char*>(s));
  }
}

void ON_VARGS_FUNC_CDECL ON_Error(
  const char* sFileName, 
  int line_number,
  const char* sFormat,
  ...
)
{
  ON_IncrementErrorCount();

  const bool bPrintErrorMessage = ON_Internal_PrintErrorMessage();
  if ( bPrintErrorMessage || ON_Internal_LogError() )
  {
    ON_String description;
    if (sFormat && sFormat[0]) 
    {
      va_list args;
      va_start(args, sFormat);
      description.FormatVargs(sFormat, args);
      va_end(args);
    }

    const ON_ErrorEvent error_event(
      ON_ErrorEvent::Type::Error,
      sFileName,
      (unsigned int)line_number,
      nullptr,
      description
    );

    ON_Internal_RecordErrorEvent(error_event, bPrintErrorMessage);
  }

}

void ON_VARGS_FUNC_CDECL ON_ErrorEx(
  const char* sFileName,
  int line_number, 
  const char* sFunctionName,
  const char* sFormat,
  ...
)
{
  ON_IncrementErrorCount();

  const bool bPrintErrorMessage = ON_Internal_PrintErrorMessage();
  if (bPrintErrorMessage || ON_Internal_LogError())
  {
    ON_String description;
    if (sFormat && sFormat[0])
    {
      va_list args;
      va_start(args, sFormat);
      description.FormatVargs(sFormat, args);
      va_end(args);
    }

    const ON_ErrorEvent error_event(
      ON_ErrorEvent::Type::Error,
      sFileName,
      (unsigned int)line_number,
      sFunctionName,
      description
    );

    ON_Internal_RecordErrorEvent(error_event, bPrintErrorMessage);
  }

}

void ON_VARGS_FUNC_CDECL ON_Warning(
  const char* sFileName,
  int line_number,
  const char* sFormat,
  ...
)
{
  ON_IncrementWarningCount();

  const bool bPrintErrorMessage = ON_Internal_PrintWarningMessage();
  if ( bPrintErrorMessage || ON_Internal_LogError())
  {
    ON_String description;
    if (sFormat && sFormat[0]) 
    {
      va_list args;
      va_start(args, sFormat);
      description.FormatVargs(sFormat, args);
      va_end(args);
    }

    const ON_ErrorEvent error_event(
      ON_ErrorEvent::Type::Warning,
      sFileName,
      (unsigned int)line_number,
      nullptr,
      description
    );

    ON_Internal_RecordErrorEvent(error_event, bPrintErrorMessage);
  }

}

void ON_VARGS_FUNC_CDECL ON_WarningEx(
  const char* sFileName, 
  int line_number,
  const char* sFunctionName,
  const char* sFormat,
  ...
)
{
  ON_IncrementWarningCount();

  const bool bPrintErrorMessage = ON_Internal_PrintWarningMessage();
  if ( bPrintErrorMessage || ON_Internal_LogError())
  {
    ON_String description;
    if (sFormat && sFormat[0]) 
    {
      va_list args;
      va_start(args, sFormat);
      description.FormatVargs(sFormat, args);
      va_end(args);
    }

    const ON_ErrorEvent error_event(
      ON_ErrorEvent::Type::Warning,
      sFileName,
      (unsigned int)line_number,
      sFunctionName,
      description
    );

    ON_Internal_RecordErrorEvent(error_event, bPrintErrorMessage);
  }

}

void ON_VARGS_FUNC_CDECL ON_REMOVE_ASAP_AssertEx(
  int bCondition,
  const char* sFileName,
  int line_number,
  const char* sFunctionName,
  const char* sFormat,
  ...
)
{
  if ( false == bCondition)
  {

    const bool bPrintErrorMessage = ON_Internal_PrintErrorMessage();
    if ( bPrintErrorMessage || ON_Internal_LogError())
    {
      ON_String description;
      if (sFormat && sFormat[0]) 
      {
        va_list args;
        va_start(args, sFormat);
        description.FormatVargs(sFormat, args);
        va_end(args);
      }

      const ON_ErrorEvent error_event(
        ON_ErrorEvent::Type::Warning,
        sFileName,
        (unsigned int)line_number,
        sFunctionName,
        description
      );

      ON_Internal_RecordErrorEvent(error_event, bPrintErrorMessage);
    }
  }
}

////////////////////////////////////////////////////////////////////////
//
// ON_ErrorEvent
//
ON_ErrorEvent::ON_ErrorEvent(const ON_ErrorEvent& src)
{
  Internal_CopyFrom(src);
}

ON_ErrorEvent& ON_ErrorEvent::operator=(const ON_ErrorEvent& src)
{
  if (this != &src)
  {
    Internal_CopyFrom(src);
  }
  return *this;
}

void ON_ErrorEvent::Internal_CopyFrom(const ON_ErrorEvent& src)
{
  m_event_type = src.m_event_type;
  m_line_number = src.m_line_number;
  m_file_name = nullptr;
  m_function_name = nullptr;
  m_description = nullptr;

  const size_t sizeof_buffer = sizeof(m_buffer);
  memcpy(m_buffer, src.m_buffer, sizeof_buffer);

  // buffer_capacity keeps code working if char changes to wchar_t
  const size_t buffer_capacity = sizeof_buffer/sizeof(m_buffer[0]); 
  const char* src_buffer = &src.m_buffer[0];

  if (nullptr != src.m_file_name && src.m_file_name >= src_buffer)
  {
    const size_t i = (src.m_file_name - src_buffer);
    if (i >= 0 && i < buffer_capacity)
      m_file_name = &m_buffer[i];
  }
  if (nullptr != src.m_function_name && src.m_function_name >= src_buffer)
  {
    const size_t i = (src.m_function_name - src_buffer);
    if (i >= 0 && i < buffer_capacity)
      m_function_name = &m_buffer[i];
  }
  if (nullptr != src.m_description && src.m_description >= src_buffer)
  {
    const size_t i = (src.m_description - src_buffer);
    if (i >= 0 && i < buffer_capacity)
      m_description = &m_buffer[i];
  }
}


ON_ErrorEvent::ON_ErrorEvent(
  ON_ErrorEvent::Type event_type,
  const char* file_name,
  unsigned int line_number,
  const char* function_name,
  const char* description
)
  : m_event_type(event_type)
  , m_line_number(line_number)
{
  const size_t buffer_capacity = sizeof(m_buffer) / sizeof(m_buffer[0]);
  size_t file_name_length = ON_String::Length(file_name);
  size_t function_name_length = ON_String::Length(function_name);
  size_t description_length = ON_String::Length(description);
  if (file_name_length + function_name_length + description_length + 3 > buffer_capacity)
  {
    const size_t cap = buffer_capacity / 4;
    if (file_name_length > cap )
    {
      file_name += (file_name_length - cap);
      file_name_length = cap;
    }
    if (file_name_length + function_name_length + description_length + 3 > buffer_capacity)
    {
      if (function_name_length > cap)
      {
        function_name += (function_name_length - cap);
        function_name_length = cap;
      }
    }
  }

  char* c = m_buffer;
  char* c1 = m_buffer + (buffer_capacity - 1);

  if (file_name_length > 0 && c < c1)
  {
    m_file_name = c;
    for (size_t i = 0; i < file_name_length && c < c1; i++)
      *c++ = file_name[i];
    if (c < c1)
      *c++ = 0;
  }

  if (function_name_length > 0 && c < c1)
  {
    m_function_name = c;
    for (size_t i = 0; i < function_name_length && c < c1; i++)
      *c++ = function_name[i];
    if (c < c1)
      *c++ = 0;
  }

  if (description_length > 0 && c < c1)
  {
    m_description = c;
    for (size_t i = 0; i < description_length && c < c1; i++)
      *c++ = description[i];
    if (c < c1)
      *c++ = 0;
  }

  *c1 = 0;
}

const ON_ErrorEvent ON_ErrorEvent::Create(
  ON_ErrorEvent::Type event_type,
  const char* file_name,
  unsigned int line_number,
  const char* function_name,
  const char* description
)
{
  return ON_ErrorEvent(
    event_type,
    file_name,
    line_number,
    function_name,
    description
  );
}

const char* ON_ErrorEvent::FileName() const
{
  return (nullptr != m_file_name || 0 != m_file_name) ? m_file_name : "";
}

const char* ON_ErrorEvent::FunctionName() const
{
  return (nullptr != m_function_name || 0 != m_function_name) ? m_function_name : "";
}

const char* ON_ErrorEvent::Description() const
{
  return (nullptr != m_description || 0 != m_description) ? m_description : "";
}

unsigned int ON_ErrorEvent::LineNumber() const
{
  return m_line_number;
}

ON_ErrorEvent::Type ON_ErrorEvent::EventType() const
{
  return m_event_type;
}

const char* ON_ErrorEvent::TypeToString(
  ON_ErrorEvent::Type event_type
)
{
  const char* s;
  switch (event_type)
  {
  case ON_ErrorEvent::Type::Unset:
    s = "Unset";
    break;
  case ON_ErrorEvent::Type::Warning:
    s = "Warning";
    break;
  case ON_ErrorEvent::Type::Error:
    s = "Error";
    break;
  case ON_ErrorEvent::Type::Assert:
    s = "Assert";
    break;
  case ON_ErrorEvent::Type::Custom:
    s = "Custom";
    break;
  case ON_ErrorEvent::Type::SubDError:
    s = "SubDError";
    break;
  case ON_ErrorEvent::Type::NotValid:
    s = "NotValid";
    break;
  default:
    s = "Invalid";
    break;
  }

  return s;
}

const ON_String ON_ErrorEvent::ToString() const
{
  const char* function_name = FunctionName();
  const char* description = Description();
  if (0 != function_name[0])
  {
    return ON_String::FormatToString(
      "%s.%u %s(): %s \"%s\"",
      FileName(), 
      LineNumber(), 
      function_name,
      ON_ErrorEvent::TypeToString(m_event_type),
      description
    );
  }
  return ON_String::FormatToString(
    "%s.%u: %s \"%s\"",
    FileName(), 
    LineNumber(), 
    ON_ErrorEvent::TypeToString(m_event_type),
    description
  );
}

void ON_ErrorEvent::Dump(
  class ON_TextLog& text_log
) const
{
  const ON_String s(ToString());
  text_log.Print("%s\n", static_cast<const char*>(s));
}


////////////////////////////////////////////////////////////////////////
//
// ON_ErrorLog
//

bool ON_ErrorLog::EnableLogging()
{
  if ( 0 == ((ON__UINT_PTR)this) )
    return false;
  if (this == ON_ACTIVE_ERROR_LOG)
    return true;
  if (nullptr != ON_ACTIVE_ERROR_LOG)
    return false;
  if (Count() >= ON_ErrorLog::MaximumEventCount)
    return false;

  ON_ACTIVE_ERROR_LOG = this;
  return true;
}

void ON_ErrorLog::DisableLogging()
{
  if (nullptr != ON_ACTIVE_ERROR_LOG && this == ON_ACTIVE_ERROR_LOG)
  {
    ON_ACTIVE_ERROR_LOG = nullptr;
  }
}

void ON_ErrorLog::Dump(
  class ON_TextLog& text_log
) const
{
  const unsigned int count = Count();
  text_log.Print("Error log: %u events\n", count);
  ON_TextLogIndent indent1(text_log);
  for (unsigned int i = 0; i < count; i++)
  {
    m_events[i].Dump(text_log);
  }
}


ON_ErrorLog::~ON_ErrorLog()
{
  if (ON_ACTIVE_ERROR_LOG == this)
    ON_ACTIVE_ERROR_LOG = nullptr;
}

unsigned int ON_ErrorLog::Append(
  const ON_ErrorEvent& error_event
)
{
  const unsigned int event_capacity = (unsigned int)(sizeof(m_events) / sizeof(m_events[0]));
  if (m_event_count >= event_capacity)
    return 0;

  if (m_event_count < event_capacity)
  {
    m_events[m_event_count++] = error_event;
    if (m_event_count == event_capacity && ON_ACTIVE_ERROR_LOG == this)
    {
      // stop wasting time logging errors
      ON_ACTIVE_ERROR_LOG = nullptr;
    }
  }
  return m_event_count;
}

unsigned int ON_ErrorLog::Count() const
{
  return m_event_count <= ON_ErrorLog::MaximumEventCount ? m_event_count : ON_ErrorLog::MaximumEventCount;
}

const ON_ErrorEvent& ON_ErrorLog::Event(unsigned int i) const
{
  return (i < m_event_count) ? m_events[i] : ON_ErrorEvent::Unset;
}

void ON_ErrorLog::Clear()
{
  m_event_count = 0;
}
