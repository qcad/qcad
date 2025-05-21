/*
//
// Copyright (c) 1993-2018 Robert McNeel & Associates. All rights reserved.
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

#if !defined(OPENNURBS_WIN_DWRITE_INC_)
#define OPENNURBS_WIN_DWRITE_INC_

#if defined(ON_RUNTIME_WIN) && defined(ON_OS_WINDOWS_GDI)
#pragma ON_PRAGMA_WARNING_PUSH
/*
Suppress 4263 warnings from dwrite.h
Warning	C4263	..: member function does not override any base class virtual member function ... C:\Program Files (x86)\Windows Kits\8.1\Include\um\DWrite.h ...
Warning	C4263	..: member function does not override any base class virtual member function ... C:\Program Files (x86)\Windows Kits\8.1\Include\um\DWrite_1.h ...
Warning	C4263	..: member function does not override any base class virtual member function ... C:\Program Files (x86)\Windows Kits\8.1\Include\um\dwrite_2.h ...
*/
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4263 4264 4265 )
//#include <dwrite.h>
#include <dwrite_2.h>
#include <d2d1.h>
#include <wrl.h>
//#include <wrl\implements.h>
#pragma comment(lib, "Dwrite.lib")
#if defined(WIN32) && defined(WIN64)
#undef WIN32
#endif
#pragma ON_PRAGMA_WARNING_POP

ON_DECL
bool ON_WindowsDWriteGetGlyphMetrics(
  struct IDWriteFont* dwriteFont,
  unsigned int dwriteGlyphIndex,
  class ON_TextBox& glyph_metrics
);

ON_DECL
bool ON_WindowsDWriteGetGlyphOutline(
  struct IDWriteFont* dwriteFont,
  unsigned int dwriteGlyphIndex,
  ON_OutlineFigure::Type figure_type,
  class ON_Outline& outline
);

#endif
#endif
