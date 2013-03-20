/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#include "opennurbs.h"

// opennurbs_dll.cpp : Defines the entry point for the Windows DLL application.
//

#if defined(ON_OS_WINDOWS) && defined(ON_DLL_EXPORTS)

ON_BOOL32 APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
  static int bRunning = 0;
  if ( !bRunning ) 
  {
    ON_MemoryManagerBegin();
    bRunning = true;
  }

  switch( ul_reason_for_call ) {

  case DLL_PROCESS_ATTACH:
    ::OutputDebugStringA("OpenNURBS DllMain() ul_reason_for_call = DLL_PROCESS_ATTACH\n");
    ON_ClassId::IncrementMark(); // make sure each DLL that each process that 
                                 // uses OpenNURBS has a unique mark.
    break;

  case DLL_THREAD_ATTACH:
    ::OutputDebugStringA("OpenNURBS DllMain() ul_reason_for_call = DLL_THREAD_ATTACH\n");
    break;

  case DLL_THREAD_DETACH:
    ::OutputDebugStringA("OpenNURBS DllMain() ul_reason_for_call = DLL_THREAD_DETACH\n");
    break;

  case DLL_PROCESS_DETACH:
    ::OutputDebugStringA("OpenNURBS DllMain() ul_reason_for_call = DLL_PROCESS_DETACH\n");
    break;

  default:
    ::OutputDebugStringA("OpenNURBS DllMain() ul_reason_for_call = ?\n");
    break;
  }

  return true;
}


///////////////////////////////////////////////////////////////////////////////
//
// For testing crash handling in opennurbs.dll
//

#define ON_CRASH_TEST_STATICS
#include "opennurbs_crashtest.h"
#undef ON_CRASH_TEST_STATICS
int ON_CrashTest( int crash_type, ON_TextLog& textlog )
{
  return CrashTestHelper( crash_type, textlog );
}

#endif
