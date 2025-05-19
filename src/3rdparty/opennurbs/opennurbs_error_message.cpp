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

void ON_ErrorMessage(
        int message_type, // 0=warning - serious problem that code is designed to handle
                          // 1=error - serious problem code will attempt to handle
                          //           The thing causing the error is a bug that must
                          //           be fixed.
                          // 2=assert failed - crash is nearly certain
        const char* sErrorMessage 
        )
{
  // error/warning/assert message is in sMessage[] buffer.  Modify this function
  // to do whatever you want to with the message.
  if ( sErrorMessage && sErrorMessage[0] ) 
  {
#if defined(ON_COMPILER_MSC)
    ::OutputDebugStringA( "\n" );
    ::OutputDebugStringA( sErrorMessage );
    ::OutputDebugStringA( "\n" );
#elif defined(ON__DEBUG)
    // not using OutputDebugStringA
    printf("\n%s\n",sErrorMessage);
#endif
  }
}





