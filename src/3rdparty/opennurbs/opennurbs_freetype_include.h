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

// opennurbs uses FreeType to calculate font metric, glyph metric, and glyph outline information.

// FreeType Licensing:
//
//// Retrieved March 22, 2017
//// https://www.freetype.org/freetype2/docs/index.html
////What is FreeType?
////
////FreeType is a software font engine that is designed to be small, efficient,
////highly customizable, and portable while capable of producing high-quality
////output (glyph images). It can be used in graphics libraries, display servers,
////font conversion tools, text image generation tools, and many other products as well.
////
////Note that FreeType is a font service and doesn't provide APIs to perform
////higher-level features like text layout or graphics processing
////(e.g., colored text rendering, ‘hollowing’, etc.). However, it greatly
////simplifies these tasks by providing a simple, easy to use, and uniform
////interface to access the content of font files.
////
////FreeType is released under two open-source licenses: our own BSD-like
////FreeType License and the GNU Public License, Version 2. It can thus
////be used by any kind of projects, be they proprietary or not.
////
////Please note that ‘FreeType’ is also called ‘FreeType 2’, to
////distinguish it from the old, deprecated ‘FreeType 1’ library,
////a predecessor no longer maintained and supported.
////
//// http://git.savannah.gnu.org/cgit/freetype/freetype2.git/tree/docs/FTL.TXT
////
////                    The FreeType Project LICENSE
////                    ----------------------------
////
////                            2006-Jan-27
////
////                    Copyright 1996-2002, 2006 by
////          David Turner, Robert Wilhelm, and Werner Lemberg
////
////
////
////Introduction
////============
////
////  The FreeType  Project is distributed in  several archive packages;
////  some of them may contain, in addition to the FreeType font engine,
////  various tools and  contributions which rely on, or  relate to, the
////  FreeType Project.
////
////  This  license applies  to all  files found  in such  packages, and
////  which do not  fall under their own explicit  license.  The license
////  affects  thus  the  FreeType   font  engine,  the  test  programs,
////  documentation and makefiles, at the very least.
////
////  This  license   was  inspired  by  the  BSD,   Artistic,  and  IJG
////  (Independent JPEG  Group) licenses, which  all encourage inclusion
////  and  use of  free  software in  commercial  and freeware  products
////  alike.  As a consequence, its main points are that:
////
////    o We don't promise that this software works. However, we will be
////      interested in any kind of bug reports. (`as is' distribution)
////
////    o You can  use this software for whatever you  want, in parts or
////      full form, without having to pay us. (`royalty-free' usage)
////
////    o You may not pretend that  you wrote this software.  If you use
////      it, or  only parts of it,  in a program,  you must acknowledge
////      somewhere  in  your  documentation  that  you  have  used  the
////      FreeType code. (`credits')
////
////  We  specifically  permit  and  encourage  the  inclusion  of  this
////  software, with  or without modifications,  in commercial products.
////  We  disclaim  all warranties  covering  The  FreeType Project  and
////  assume no liability related to The FreeType Project.
////
////
////  Finally,  many  people  asked  us  for  a  preferred  form  for  a
////  credit/disclaimer to use in compliance with this license.  We thus
////  encourage you to use the following text:
////
////   """
////    Portions of this software are copyright © <year> The FreeType
////    Project (www.freetype.org).  All rights reserved.
////   """
////
////  Please replace <year> with the value from the FreeType version you
////  actually use.
////
////
////Legal Terms
////===========
////
////0. Definitions
////--------------
////
////  Throughout this license,  the terms `package', `FreeType Project',
////  and  `FreeType  archive' refer  to  the  set  of files  originally
////  distributed  by the  authors  (David Turner,  Robert Wilhelm,  and
////  Werner Lemberg) as the `FreeType Project', be they named as alpha,
////  beta or final release.
////
////  `You' refers to  the licensee, or person using  the project, where
////  `using' is a generic term including compiling the project's source
////  code as  well as linking it  to form a  `program' or `executable'.
////  This  program is  referred to  as  `a program  using the  FreeType
////  engine'.
////
////  This  license applies  to all  files distributed  in  the original
////  FreeType  Project,   including  all  source   code,  binaries  and
////  documentation,  unless  otherwise  stated   in  the  file  in  its
////  original, unmodified form as  distributed in the original archive.
////  If you are  unsure whether or not a particular  file is covered by
////  this license, you must contact us to verify this.
////
////  The FreeType  Project is copyright (C) 1996-2000  by David Turner,
////  Robert Wilhelm, and Werner Lemberg.  All rights reserved except as
////  specified below.
////
////1. No Warranty
////--------------
////
////  THE FREETYPE PROJECT  IS PROVIDED `AS IS' WITHOUT  WARRANTY OF ANY
////  KIND, EITHER  EXPRESS OR IMPLIED,  INCLUDING, BUT NOT  LIMITED TO,
////  WARRANTIES  OF  MERCHANTABILITY   AND  FITNESS  FOR  A  PARTICULAR
////  PURPOSE.  IN NO EVENT WILL ANY OF THE AUTHORS OR COPYRIGHT HOLDERS
////  BE LIABLE  FOR ANY DAMAGES CAUSED  BY THE USE OR  THE INABILITY TO
////  USE, OF THE FREETYPE PROJECT.
////
////2. Redistribution
////-----------------
////
////  This  license  grants  a  worldwide, royalty-free,  perpetual  and
////  irrevocable right  and license to use,  execute, perform, compile,
////  display,  copy,   create  derivative  works   of,  distribute  and
////  sublicense the  FreeType Project (in  both source and  object code
////  forms)  and  derivative works  thereof  for  any  purpose; and  to
////  authorize others  to exercise  some or all  of the  rights granted
////  herein, subject to the following conditions:
////
////    o Redistribution of  source code  must retain this  license file
////      (`FTL.TXT') unaltered; any  additions, deletions or changes to
////      the original  files must be clearly  indicated in accompanying
////      documentation.   The  copyright   notices  of  the  unaltered,
////      original  files must  be  preserved in  all  copies of  source
////      files.
////
////    o Redistribution in binary form must provide a  disclaimer  that
////      states  that  the software is based in part of the work of the
////      FreeType Team,  in  the  distribution  documentation.  We also
////      encourage you to put an URL to the FreeType web page  in  your
////      documentation, though this isn't mandatory.
////
////  These conditions  apply to any  software derived from or  based on
////  the FreeType Project,  not just the unmodified files.   If you use
////  our work, you  must acknowledge us.  However, no  fee need be paid
////  to us.
////
////3. Advertising
////--------------
////
////  Neither the  FreeType authors and  contributors nor you  shall use
////  the name of the  other for commercial, advertising, or promotional
////  purposes without specific prior written permission.
////
////  We suggest,  but do not require, that  you use one or  more of the
////  following phrases to refer  to this software in your documentation
////  or advertising  materials: `FreeType Project',  `FreeType Engine',
////  `FreeType library', or `FreeType Distribution'.
////
////  As  you have  not signed  this license,  you are  not  required to
////  accept  it.   However,  as  the FreeType  Project  is  copyrighted
////  material, only  this license, or  another one contracted  with the
////  authors, grants you  the right to use, distribute,  and modify it.
////  Therefore,  by  using,  distributing,  or modifying  the  FreeType
////  Project, you indicate that you understand and accept all the terms
////  of this license.
////
////4. Contacts
////-----------
////
////  There are two mailing lists related to FreeType:
////
////    o freetype@nongnu.org
////
////      Discusses general use and applications of FreeType, as well as
////      future and  wanted additions to the  library and distribution.
////      If  you are looking  for support,  start in  this list  if you
////      haven't found anything to help you in the documentation.
////
////    o freetype-devel@nongnu.org
////
////      Discusses bugs,  as well  as engine internals,  design issues,
////      specific licenses, porting, etc.
////
////  Our home page can be found at
////
////    http://www.freetype.org
////
////--- end of FTL.TXT ---


#if !defined(OPENNURBS_FREETYPE_INCLUDE_INC_)
#define OPENNURBS_FREETYPE_INCLUDE_INC_

// NOTE:
//   This header file is not included in opennurbs.h because
//   FreeType 2.6.3 has deeply nested includes and uses angle brackets
//   in its include files (instead of double quotes and relative paths like opennurbs),
//   the directory ./freetype263/include must be in the "system" includes path.
//   It is not feasible or reasonable for all projects that include opennurbs.h to have the
//   freetype includes directory in the system includes path.

#if defined(OPENNURBS_FREETYPE_SUPPORT)
// Look in opennurbs_system_rumtime.h for the correct place to define OPENNURBS_FREETYPE_SUPPORT.
// Do NOT define OPENNURBS_FREETYPE_SUPPORT here or in your project setting ("makefile").


// Angle brackets are used on #include <ft2build.h> because if it fails,
// the following #include FT_FREETYPE_H will fail, but in more mysterious ways.
#if defined(OPENNURBS_EXPORTS) || defined(OPENNURBS_IMPORTS)
// WHen opennurbs is a DLL, freetype is linked as a DLL
#if defined(ON_COMPILER_MSC)
/* Windows DLL */
#define OPENNURBS_FREETYPE_DECL __declspec(dllimport)
#elif defined(ON_COMPILER_CLANG)
/* Apple shared library */
#define OPENNURBS_FREETYPE_DECL __attribute__ ((visibility ("default")))
#endif
#endif

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
// Angle brackets must be used in the ft2build.h include because
// that's what the freetype defined includes like FT_FREETYPE_H
// use and they must work. If you get a compiler (CLang) error telling you
// to use "quotes" instead,
// ignore it and include the freetype directory in the header search
// path for opennurbs_freetype.cpp.
#include <ft2build.h>
#include FT_FREETYPE_H
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#if defined(ON_COMPILER_MSC)

#if !defined(OPENNURBS_FREETYPE_LIB_DIR)

#include "opennurbs_input_libsdir.h"

#if defined(OPENNURBS_INPUT_LIBS_DIR)
// Typically, OPENNURBS_LIB_DIR is defined in opennurbs_msbuild.Cpp.props
#define OPENNURBS_FREETYPE_LIB_DIR OPENNURBS_INPUT_LIBS_DIR
#else
// Define OPENNURBS_FREETYPE_LIB_DIR to be the directory containing freetype263.lib
#error You must define OPENNURBS_FREETYPE_LIB_DIR
#endif

#endif

#if defined(_LIB) && !defined(OPENNURBS_IMPORTS) && !defined(OPENNURBS_EXPORTS)

// Microsoft static library
#if defined(_MT) && !defined(_DLL)
// Microsoft dynamic library freetype263_mt.lib used multithreaded static C-runtime
#pragma message ( "Linking with freetype263_mt.lib in " OPENNURBS_PP2STR(OPENNURBS_FREETYPE_LIB_DIR) )
#pragma comment(lib, "\"" OPENNURBS_FREETYPE_LIB_DIR "/" "freetype263_mt.lib" "\"")
#else
// Microsoft dynamic library freetype263_staticlib.lib uses DLL C-runtime
#pragma message ( "Linking with freetype263_staticlib.lib in " OPENNURBS_PP2STR(OPENNURBS_FREETYPE_LIB_DIR) )
#pragma comment(lib, "\"" OPENNURBS_FREETYPE_LIB_DIR "/" "freetype263_staticlib.lib" "\"")
#endif

#else
// Microsoft dynamic library freetype263.lib + freetype263.dll
#pragma message ( "Linking with freetype263.lib in " OPENNURBS_PP2STR(OPENNURBS_FREETYPE_LIB_DIR) )
#pragma comment(lib, "\"" OPENNURBS_FREETYPE_LIB_DIR "/" "freetype263.lib" "\"")
#endif
#endif

#endif

#endif
