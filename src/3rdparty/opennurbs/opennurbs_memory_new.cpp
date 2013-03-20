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

#if defined(ON_DLL_EXPORTS) || defined(ON_DLL_IMPORTS)

/* See comments at the start of opennurbs_memory.h and 
// opennurbs_object.cpp for details.
//
*/
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//
// OPTIONAL replacements for operator new and operator delete that use 
// onmalloc()/onfree().  The openNURBS toolkit does NOT require you to
// override new and delete.  
//
// If you choose to not use these overrides and you are using openNURBS
// as a Windows DLL, see the comments at the top of opennurbs_object.cpp.
//
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#if defined(ON_OS_WINDOWS)
#pragma message( " --- OpenNURBS overriding new and delete" )
#endif

void* operator new[]( size_t sz )
{
  // The else "sz?sz:1" is there because section 3.7.3.1, 
  // paragraph 2 of the C++ "standard" says something along
  // the lines of:
  //
  //   The function shall return the address of the start of a 
  //   block of storage whose length in bytes shall be at least
  //   as large as the requested size. There are no constraints
  //   on the contents of the allocated storage on return from 
  //   the allocation function. The order, contiguity, and initial
  //   value of storage allocated by successive calls to an 
  //   allocation function is unspecified. The pointer returned 
  //   shall be suitably aligned so that it can be converted to a 
  //   pointer of any complete object type and then used to
  //   access the object or array in the storage allocated (until
  //   the storage is explicitly deallocated by a call to a 
  //   corresponding deallocation function). If the size of the 
  //   space requested is zero, the value returned shall not be a
  //   null pointer value. The results of dereferencing a pointer
  //   returned as a request for zero size are undefined.
  
  return onmalloc(sz?sz:1);
}

void operator delete[]( void* p )
{
  onfree(p);
}

void* operator new( size_t sz )
{
  // If you copy and paste these definitions into a Rhino plug-in
  // or any Windows MFC DLL for that matter, then carefully
  // test your code in release builds.  If you have any questions,
  // please ask Dale Lear.
  
  #if defined(_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
  // We are building a Release build Windows DLL that uses MFC

  static bool b = 0;
  if ( !b )
  {
    /*
    There are two critical pieces of background information that
    you must understand if you want to successfully override the 
    global operator new and delete in a release build Windows MFC DLL.

    Background Information Item 1:

      In release builds using MFC, the definitions of
      CObject::operator new(size_t) and CObject::operator delete(void*)
      are inlined. The definitions can be found in
      <<VISUAL_STUDIO_INSTALL_DIRECTORY>>\VC\atlmfc\include\afx.inl
      and look like

        _AFX_INLINE void PASCAL CObject::operator delete(void* p)
          { ::operator delete(p); }
        _AFX_INLINE void* PASCAL CObject::operator new(size_t nSize)
          { return ::operator new(nSize); }

      This means that, in release builds, if CMfcObjectClass is derived 
      from CObject then a call to new like

        CMfcObjectClass* pMfcObjectClass = new CMfcObjectClass();

      will use the global operator new from the executable module (DLL or EXE)
      containing the call to allocate the memory.  Because CObject has a virtual
      desctructor

        delete pMfcObjectClass;

      is compiled to call CMfcObjectClass::`scalar deleting destructor'.  
      The "scalar deleting destructor" is the second entry in the vtable 
      for the class and points to code in Microsoft's MFC DLL.  The
      "scalar deleting destructor" basically calls ~CMfcObjectClass()
      and then calls the CObject::delete to deallocate the memory.  Since
      the CObject::delete was inlined and compiled in the MFC DLL, it
      calls the global operator delete for the MFC DLL module.

      To prevent heap corruption, which will eventually lead to a crash,
      it is critical that the memory allocated by the global operator
      new in the call "pMfcObjectClass = new CMfcObjectClass()" come 
      from the same heap that will deallocate it in the call
      "delete pMfcObjectClass".

    Background Information Item 2:

      When your MFC DLL (a Rhino plug-in is an MFC DLL) is loaded it 
      allocates a CDynLinkLibrary class in a function called InternalDllMain().
      The class CDynLinkLibrary is derived from CCmdTarget which is derived 
      from CObject and CDynLinkLibrary uses the inline CObject new and delete
      operators described in Item 1. When your DLL is loaded, the call stack
      looks something like
      
        yourmodule.dll!InternalDllMain(HINSTANCE__ * hInstance=..., unsigned long dwReason=0, void * __formal=0)  Line 133
        yourmodule.dll!__DllMainCRTStartup(void * hDllHandle=..., unsigned long dwReason=0, void * lpreserved=0)  Line 498
        yourmodule.dll!_DllMainCRTStartup(void * hDllHandle=..., unsigned long dwReason=1, void * lpreserved=0)  Line 462
        ...
        LoadLibraryEx(...)

      The definition of InternalDllMain() is in 
      <<VISUAL_STUDIO_INSTALL_DIRECTORY>>\VC\atlmfc\src\mfc\dllmodule.cpp 
      and at line 133 of InstallDllMain(), operator new is used to
      allocate a new CDynLinkLibrary class.  

      CDynLinkLibrary* pDLL; 
      pDLL = new CDynLinkLibrary(controlDLL);   // line 133 of dllmodule.cpp 
      
      The definition of InternalDllMain() is staticly linked into your MFC DLL
      by the compiler.  This means that the memory for the CDynLinkLibrary
      class will be allocated by the global operator new in your DLL.

      When your DLL is unloaded the CDynLinkLibrary class is destroyed and
      deallocated using the CDynLinkLibrary::`scalar deleting destructor'.
      The CDynLinkLibrary::`scalar deleting destructor' is in Microsoft's
      mfc80u.dll and it calls the global operator delete in mfc80u.dll.

      At this point the call stack looks something like

        mfc80u.dll!CDynLinkLibrary::~CDynLinkLibrary()  Line 88
        mfc80u.dll!CDynLinkLibrary::`scalar deleting destructor'()
        mfc80u.dll!AfxTermExtensionModule(AFX_EXTENSION_MODULE & state={...}, int bAll=1)
        yourplugin.rhp!InternalDllMain(HINSTANCE__ * hInstance=..., unsigned long dwReason=0, void * __formal=0) Line 187
        yourplugin.rhp!__DllMainCRTStartup(void * hDllHandle=..., unsigned long dwReason=0, void * lpreserved=0) Line 498
        yourplugin.rhp!_DllMainCRTStartup(void * hDllHandle=..., unsigned long dwReason=0, void * lpreserved=0) Line 462
        ...
        FreeLibrary(...)

     Conclusion:
       If you override the global operator new and delete in a release build
       of an MFC DLL, then you must make sure the memory allocated
       for the CDynLinkLibrary class described in Item 2 comes from
       the same heap used by Microsoft's mfc80u.dll or you risk crashing
       when your DLL is unloaded.  By experimenting, it turns out that
       the memory for the CDynLinkLibrary class described in Item 2
       is allocated by the first call to the global operator new.
       Also, by experimenting, it turns out that the global operator
       new in mfc80u.dll simply calls the malloc() in MSVCRT.dll.
    */
    if ( sz == sizeof(CDynLinkLibrary) )
    {
      b = 1; // All subseqent allocations will use onmalloc()
      return malloc(sz);
    }
    else
    {
      static int early_allocation_counter = 0;
      early_allocation_counter++;
      if ( early_allocation_counter > 16 )
        b = 1;
    }
  }
  #endif

  // The else "sz?sz:1" in the call to onmalloc() is there 
  // because section 3.7.3.1, paragraph 2 of the C++ 
  // "standard" says something along the lines of:
  //
  //   The function shall return the address of the start of a 
  //   block of storage whose length in bytes shall be at least
  //   as large as the requested size. There are no constraints
  //   on the contents of the allocated storage on return from 
  //   the allocation function. The order, contiguity, and initial
  //   value of storage allocated by successive calls to an 
  //   allocation function is unspecified. The pointer returned 
  //   shall be suitably aligned so that it can be converted to a 
  //   pointer of any complete object type and then used to
  //   access the object or array in the storage allocated (until
  //   the storage is explicitly deallocated by a call to a 
  //   corresponding deallocation function). If the size of the 
  //   space requested is zero, the value returned shall not be a
  //   null pointer value. The results of dereferencing a pointer
  //   returned as a request for zero size are undefined.
  return onmalloc(sz?sz:1);
}

void operator delete( void* p )
{
  onfree(p);
}

#endif
