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

#if defined(OPENNURBS_FREETYPE_SUPPORT)
// Look in opennurbs_system_rumtime.h for the correct place to define OPENNURBS_FREETYPE_SUPPORT.
// Do NOT define OPENNURBS_FREETYPE_SUPPORT here or in your project setting ("makefile").

#include "opennurbs_internal_glyph.h"

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


// There is a compiler option for this file, opennurbs_freetype.cpp, that
// adds ./freetype263/include to the list of "system" include paths.
#include "opennurbs_freetype_include.h"

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_PUSH
/*
Suppress 4263 warnings from dwrite.h
Warning	C4263	..: member function does not override any base class virtual member function ... C:\Program Files (x86)\Windows Kits\8.1\Include\um\DWrite.h ...
Warning	C4263	..: member function does not override any base class virtual member function ... C:\Program Files (x86)\Windows Kits\8.1\Include\um\DWrite_1.h ...
Warning	C4263	..: member function does not override any base class virtual member function ... C:\Program Files (x86)\Windows Kits\8.1\Include\um\dwrite_2.h ...
*/
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4263 4264 )
#endif

#include FT_OUTLINE_H
#include FT_GLYPH_H
#include FT_MODULE_H

#include "opennurbs_win_dwrite.h"

#if defined(ON_COMPILER_MSC)
#pragma ON_PRAGMA_WARNING_POP
#endif

#if defined(ON_RUNTIME_ANDROID)
#include <android/font.h>
#include <android/font_matcher.h>
#include <android/system_fonts.h>
#endif

class ON_FontFileBuffer
{
public:
  ON_FontFileBuffer() = default;

  ~ON_FontFileBuffer()
  {
    Internal_Destroy();
  }

  ON_FontFileBuffer(const ON_FontFileBuffer& src)
  {
    Internal_CopyFrom(src);
  }

  ON_FontFileBuffer& operator=(const ON_FontFileBuffer& src)
  {
    Internal_CopyFrom(src);
    return *this;
  }

  void* Buffer() const
  {
    return m_buffer;
  }

  void* AllocateBuffer(size_t sizeof_buffer)
  {
    if (sizeof_buffer != m_sizeof_buffer)
    {
      Internal_Destroy();
      if (sizeof_buffer > 0)
      {
        m_buffer = onmalloc(sizeof_buffer);
        if (nullptr != m_buffer)
        {
          m_sizeof_buffer = sizeof_buffer;
        }
      }
    }
    return m_buffer;
  }

  size_t SizeOfBuffer() const
  {
    return m_sizeof_buffer;
  }

  void TransferTo(
    ON_FontFileBuffer& dest
  )
  {
    if (this != &dest)
    {
      dest.Internal_Destroy();
      dest.m_buffer = m_buffer;
      m_buffer = nullptr;
      dest.m_sizeof_buffer = m_sizeof_buffer;
      m_sizeof_buffer = 0;
    }
  }

private:
  size_t m_sizeof_buffer = 0;
  void* m_buffer = nullptr;

private:
  void Internal_CopyFrom(const ON_FontFileBuffer& src)
  {
    AllocateBuffer(src.m_sizeof_buffer);
    if (nullptr != m_buffer)
    {
      memcpy(m_buffer, src.m_buffer, m_sizeof_buffer);
    }
  }

  void Internal_Destroy()
  {
    if (nullptr != m_buffer)
    {
      onfree(m_buffer);
      m_buffer = nullptr;
    }
    m_sizeof_buffer = 0;
  }
};

class ON_FreeTypeFace
{
public:
  ON_FreeTypeFace() = default;
  ~ON_FreeTypeFace();
  FT_Face m_face = nullptr;
  ON_FontFileBuffer m_font_buffer;
private:
  ON_FreeTypeFace(const ON_FreeTypeFace&) = delete;
  ON_FreeTypeFace& operator=(const ON_FreeTypeFace&) = delete;
};

ON_FreeTypeFace::~ON_FreeTypeFace()
{
  //  FT_New_Memory_Face documentation states:
  //    You must not deallocate the memory before calling @FT_Done_Face.
  //    The memory refered to is m_tt_file_buffer.
  if (nullptr != m_face)
  {
    FT_Done_Face(m_face);
    m_face = nullptr;
  }
  m_font_buffer.AllocateBuffer(0);
}

class ON_FreeType
{
public:
  static FT_Library Library();

  static ON_FreeTypeFace* CreateFace(
    const ON_Font& font
  );

  /*
  Description:
    Finds the glyph id for the specified Unicode code point. When a non-zero
    glyph is is returned, the face->charmap is set to the charmap that was used
    to find the glyph. In some cases this is not a Unicode charmap and unicode_code_point
    was internally coverted to a character code appropriate for the returned charmap.
    In principle, the glyph id for a Unicode code point is independent of the charmap.
  Returns:
     0: failure
    >0: font glyph id
  */
  static unsigned int GlyphId(
    FT_Face face,
    ON__UINT32 unicode_code_point
  );

  static const ON_wString FaceFlagsToString(FT_Long face_flags);

  static const ON_wString StyleFlagsToString(FT_Long style_flags);

  static const ON_wString EncodingTypeToString(
    FT_Encoding charmap_encoding
  );

  static const ON_wString CharmapPlatformEncodingDescription(
    const FT_CharMap cmap
  );

  static bool UseUnicodeAsAppleRomanCharCode(
    FT_Face face
  );

  static bool IsDamagedCharMap(
    FT_CharMap cmap
  );

private:
  static FT_MemoryRec_ m_memory_rec;

  static FT_Library m_library;

private:
#if defined(ON_RUNTIME_WIN)
  static ON_FreeTypeFace* Internal_CreateFaceFromWindowsFont(
    const LOGFONT* logfont
  );
#endif

#if defined (ON_RUNTIME_COCOA_AVAILABLE)
  static ON_FreeTypeFace* Internal_CreateFaceFromAppleFont(CTFontRef);
#endif

#if defined (ON_RUNTIME_ANDROID)
  static ON_FreeTypeFace* Internal_CreateFaceWithAndroidNdk(const ON_Font& font);
#endif
};

FT_MemoryRec_ ON_FreeType::m_memory_rec;
FT_Library ON_FreeType::m_library = nullptr;

static void* ON_Internal_FT_Alloc_Func(
  FT_Memory  memory,
  long size)
{
  void* ptr = onmalloc(size);
  return ptr;
}

void ON_Internal_FT_Free_Func(
  FT_Memory  memory,
  void* block
)
{
  onfree(block);
}

void* ON_InternalFT_Realloc_Func(
  FT_Memory  memory,
  long cur_size,
  long new_size,
  void* block
)
{
  void* ptr = onrealloc(block, new_size);
  return ptr;
}

FT_Library ON_FreeType::Library()
{
  if (nullptr == ON_FreeType::m_library)
  {
#if 1
    // The only reason a custom memory allocator is used
    // is so memory allocated by freetype is not flagged
    // as a leak because it is used in the cached fonts
    // ON_Font::ManagedFont(). These are created as needed
    // one per face and never deleted.
    memset(&ON_FreeType::m_memory_rec, 0, sizeof(ON_FreeType::m_memory_rec));
    ON_FreeType::m_memory_rec.user = nullptr;
    ON_FreeType::m_memory_rec.alloc = ON_Internal_FT_Alloc_Func;
    ON_FreeType::m_memory_rec.free = ON_Internal_FT_Free_Func;
    ON_FreeType::m_memory_rec.realloc = ON_InternalFT_Realloc_Func;

    FT_Library library = nullptr;
    int rc = FT_New_Library(&ON_FreeType::m_memory_rec, &library);
    if ( 0 == rc && nullptr != library )
      FT_Add_Default_Modules( library );
#else
    // Works fin except freetype cached information is flagged as a memory leak
    // int rc = FT_Init_FreeType(&library);
#endif

    if (0 != rc || nullptr == library)
    {
      ON_ERROR("FreeType FT_Init_FreeType() failed.");
    }
    else
    {
      ON_FreeType::m_library = library;
    }
  }
  return ON_FreeType::m_library;
}

bool ON_FreeType::IsDamagedCharMap(
  FT_CharMap cmap
)
{
  if (nullptr == cmap || nullptr == cmap->face)
    return true;

  bool rc = false;

  switch (cmap->encoding)
  {
  case FT_ENCODING_APPLE_ROMAN:
    rc = ON_FreeType::UseUnicodeAsAppleRomanCharCode(cmap->face);
    break;
  default:
    break;
  }

  return rc;
}

#define ON__FLAG_TO_STR(flag,i,v,s) do {if ( flag == (i & flag) ) {if (s.IsNotEmpty()) s += L", "; s += v; }} while(false)

const ON_wString ON_FreeType::FaceFlagsToString(FT_Long face_flags)
{
  ON_wString s;
  ON__FLAG_TO_STR(FT_FACE_FLAG_SCALABLE, face_flags, L"SCALABLE", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_FIXED_SIZES, face_flags, L"FIXED_SIZES", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_FIXED_WIDTH, face_flags, L"FIXED_WIDTH", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_SFNT, face_flags, L"SFNT", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_HORIZONTAL, face_flags, L"HORIZONTAL", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_VERTICAL, face_flags, L"VERTICAL", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_KERNING, face_flags, L"KERNING", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_FAST_GLYPHS, face_flags, L"FAST_GLYPHS", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_MULTIPLE_MASTERS, face_flags, L"MULTIPLE_MASTERS", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_GLYPH_NAMES, face_flags, L"GLYPH_NAMES", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_EXTERNAL_STREAM, face_flags, L"EXTERNAL_STREAM", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_HINTER, face_flags, L"FLAG_HINTER", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_CID_KEYED, face_flags, L"CID_KEYED", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_TRICKY, face_flags, L"FLAG_TRICKY", s);
  ON__FLAG_TO_STR(FT_FACE_FLAG_COLOR, face_flags, L"FLAG_COLOR", s);
  return s;
}

const ON_wString ON_FreeType::StyleFlagsToString(FT_Long style_flags)
{
  ON_wString s;
  ON__FLAG_TO_STR(FT_STYLE_FLAG_BOLD, style_flags, L"BOLD", s);
  ON__FLAG_TO_STR(FT_STYLE_FLAG_ITALIC, style_flags, L"ITALIC", s);
  return s;
}


bool ON_FreeType::UseUnicodeAsAppleRomanCharCode(FT_Face face)
{

  // It's not clear if the bug is in these font files or Windows or Freetype or
  // the way we are selecting maps, but the fonts listed below need this hack to
  // find the correct glyph and other fonts don't.
  //
  // The mighty internet contains mentions of other people having trouble with these fonts as well.
  //
  // It appears that for these fonts, passing a Unicode code point value
  // to the cmap[] idenfied as "FT_ENCODING_APPLE_ROMAN" will get the correct
  // glyph id.
  //
  // I have verified that the way opennurbs handles FT_ENCODING_APPLE_ROMAN charmaps
  // and the funciton ON_MapUnicodeToAppleRoman() works correctly with all the
  // TTF fonts shipped with Windows 10 pro.
  //
  if (
    nullptr != face
    && 1 == face->num_faces
    && 3 == face->num_charmaps
    && nullptr != face->charmaps[0]
    && nullptr != face->charmaps[1]
    && nullptr != face->charmaps[2]
    && 0 == face->charmaps[0]->platform_id && 0 == face->charmaps[0]->encoding_id
    && 1 == face->charmaps[1]->platform_id && 0 == face->charmaps[1]->encoding_id
    && 3 == face->charmaps[2]->platform_id && 0 == face->charmaps[2]->encoding_id
    )
  {
    // May 2017 Dale Lear:
    //
    // Fonts we've found where FT_ENCODING_APPLE_ROMAN charmap does not work correctly
    // with Apple Roman char codes.
    //
    // Linguist's Software CityBlueprint 2.0 generated with Altsys Fontographer 4.1 9/17/96
    // Linguist's Software CountryBlueprint 2.0 generated with Altsys Fontographer 4.1 9/17/96
    // Linguist's Software Romantic 2.0 generated with Altsys Fontographer 4.1 9/17/96
    // Linguist's Software SansSerif 2.0 generated with Altsys Fontographer 4.1 9/17/96
    // Linguist's Software Technic 2.0 generated with Altsys Fontographer 4.1 9/17/96
    //
    // So far, all styles with these face names have the buggy cmap[].
    if (ON_String::EqualOrdinal(face->family_name, "CityBlueprint", false))
      return true;
    if (ON_String::EqualOrdinal(face->family_name, "CountryBlueprint", false))
      return true;
    if (ON_String::EqualOrdinal(face->family_name, "Romantic", false))
      return true;
    if (ON_String::EqualOrdinal(face->family_name, "SansSerif", false))
      return true;
    if (ON_String::EqualOrdinal(face->family_name, "Technic", false))
      return true;
  }
  return false;
}

const ON_wString ON_FreeType::EncodingTypeToString( FT_Encoding charmap_encoding )
{
  ON_wString e;

  switch (charmap_encoding)
  {
  case FT_ENCODING_NONE:           e = L"FT_ENCODING_NONE"; break;
  case FT_ENCODING_UNICODE:        e = L"FT_ENCODING_UNICODE"; break;
  case FT_ENCODING_MS_SYMBOL:      e = L"FT_ENCODING_MS_SYMBOL"; break;
  case FT_ENCODING_ADOBE_LATIN_1:  e = L"FT_ENCODING_ADOBE_LATIN_1"; break;
  case FT_ENCODING_OLD_LATIN_2:    e = L"FT_ENCODING_OLD_LATIN_2"; break;
  case FT_ENCODING_SJIS:           e = L"FT_ENCODING_SJIS"; break;
  case FT_ENCODING_GB2312:         e = L"FT_ENCODING_GB2312"; break;
  case FT_ENCODING_BIG5:           e = L"FT_ENCODING_BIG5"; break;
  case FT_ENCODING_WANSUNG:        e = L"FT_ENCODING_WANSUNG"; break;
  case FT_ENCODING_JOHAB:          e = L"FT_ENCODING_JOHAB"; break;
  case FT_ENCODING_ADOBE_STANDARD: e = L"FT_ENCODING_ADOBE_STANDARD"; break;
  case FT_ENCODING_ADOBE_EXPERT:   e = L"FT_ENCODING_ADOBE_EXPERT"; break;
  case FT_ENCODING_ADOBE_CUSTOM:   e = L"FT_ENCODING_ADOBE_CUSTOM"; break;
  case FT_ENCODING_APPLE_ROMAN:    e = L"FT_ENCODING_APPLE_ROMAN"; break;
  default:
    e = ON_wString::FormatToString(
      L"((FT_Encoding)%u)",
      static_cast<unsigned int>(charmap_encoding)
    );
    break;
  }

  return e;
}

const ON_wString ON_FreeType::CharmapPlatformEncodingDescription( const FT_CharMap cmap )
{
  // Reference
  // https://www.microsoft.com/typography/otspec/name.htm#enc3

  ON_wString platform;
  ON_wString encoding;
  switch (cmap->platform_id)
  {
  case 0:
    platform = L"Unicode";
    switch (cmap->encoding_id)
    {
    case 0: encoding = L"Unicode 1.0 semantics [deprecated]"; break;
    case 1: encoding = L"Unicode 1.1 semantics [deprecated]"; break;
    case 2: encoding = L"ISO/IEC 10646 semantics [deprecated]"; break;
    case 3: encoding = L"Unicode 2.0+ semantics BMP only"; break;
    case 4: encoding = L"Unicode 2.0+ semantics"; break;
    case 5: encoding = L"Unicode Variation Sequences"; break;
    case 6: encoding = L"Unicode full repertoire"; break;
    }
    break;

  case 1:
    platform = L"Apple Script Manager";
    switch (cmap->encoding_id)
    {
    case  0: encoding = L"Roman"; break;
    case  1: encoding = L"Japanese"; break;
    case  2: encoding = L"Chinese (Traditional)"; break;
    case  3: encoding = L"Korean"; break;
    case  4: encoding = L"Arabic"; break;
    case  5: encoding = L"Hebrew"; break;
    case  6: encoding = L"Greek"; break;
    case  7: encoding = L"Russian"; break;
    case  8: encoding = L"RSymbol"; break;
    case  9: encoding = L"Devanagari"; break;
    case 10: encoding = L"Gurmukhi"; break;
    case 11: encoding = L"Gujarati"; break;
    case 12: encoding = L"Oriya"; break;
    case 13: encoding = L"Bengali"; break;
    case 14: encoding = L"Tamil"; break;
    case 15: encoding = L"Telugu"; break;
    case 16: encoding = L"Kannada"; break;
    case 17: encoding = L"Malayalam"; break;
    case 18: encoding = L"Sinhalese"; break;
    case 19: encoding = L"Burmese"; break;
    case 20: encoding = L"Khmer"; break;
    case 21: encoding = L"Thai"; break;
    case 22: encoding = L"Laotian"; break;
    case 23: encoding = L"Georgian"; break;
    case 24: encoding = L"Armenian"; break;
    case 25: encoding = L"Chinese (Simplified)"; break;
    case 26: encoding = L"Tibetan"; break;
    case 27: encoding = L"Mongolian"; break;
    case 28: encoding = L"Geez"; break;
    case 29: encoding = L"Slavic"; break;
    case 30: encoding = L"Vietnamese"; break;
    case 31: encoding = L"Sindhi"; break;
    case 32: encoding = L"Uninterpreted"; break;
    }
    break;

  case 2:
    platform = L"ISO [deprecated]";
    switch (cmap->encoding_id)
    {
    case 0: encoding = L"7-bit ASCII"; break;
    case 1: encoding = L"ISO 10646"; break;
    case 2: encoding = L"ISO 8859-1"; break;
    }
    break;

  case 3:
    platform = L"Windows";
    switch (cmap->encoding_id)
    {
    case  0: encoding = L"Symbol"; break;
    case  1: encoding = L"Unicode BMP UCS-2"; break;
    case  2: encoding = L"ShiftJIS"; break;
    case  3: encoding = L"PRC"; break;
    case  4: encoding = L"Big5"; break;
    case  5: encoding = L"Wansung"; break;
    case  6: encoding = L"Johab"; break;
    case 10: encoding = L"Unicode UCS-4"; break;
    }
    break;
  }


  const ON_wString e = ON_FreeType::EncodingTypeToString(cmap->encoding);

  ON_wString s = ON_wString::FormatToString(
    L"%ls %d-%d",
    static_cast<const wchar_t*>(e),
    cmap->platform_id,
    cmap->encoding_id
  );

  if (platform.IsNotEmpty())
  {
    if (encoding.IsEmpty())
      encoding = L"unknown";
    s += ON_wString::FormatToString(
      L" (%ls %ls)",
      static_cast<const wchar_t*>(platform),
      static_cast<const wchar_t*>(encoding)
    );
  }

  return s;
}

bool ON_FontGlyph::TestFreeTypeFaceCharMaps(
  ON_TextLog* text_log
) const
{
  // In order for false to be returned, charmaps[] have to exist and
  // an explicit error has to be detected. Otherwise, true is returned.
  const ON_Font* font = Font();
  if (nullptr == font)
  {
    if (text_log)
      text_log->Print("Font() = nullptr. Nothing to test.\n");
    return true; // nothing to test.
  }

  if (false == font->IsManagedFont())
  {
    // this "should" never happen.
    if (text_log)
      text_log->Print("Font().IsManagedFont() = false. Nothing to test.\n");
    return true; // nothing to test.
  }

  const ON__UINT32 unicode_code_point = CodePoint();
  if (false == ON_IsValidUnicodeCodePoint(unicode_code_point))
  {
    if (text_log)
      text_log->Print("CodePoint() is not valid. Nothing to test.\n");
    return true; // nothing to test.
  }

  FT_Face face = reinterpret_cast<FT_Face>(ON_Font::FreeTypeFace(font));
  if (nullptr == face)
  {
    if (text_log)
      text_log->Print("Face is nullptr. Nothing to test.\n");
    return true; // nothing to test.
  }

  const unsigned int glyph_index = FontGlyphIndex();
  if ( 0 == glyph_index )
  {
    if (text_log)
      text_log->Print("FontGlyphIndex is 0. Nothing to test.\n");
    return true; // nothing to test.
  }

  // Save current face charmap state
  FT_CharMap charmap0 = face->charmap;

  bool rc = true;
  for (int charmap_index = 0; charmap_index < face->num_charmaps; charmap_index++)
  {
    FT_CharMap charmap = face->charmaps[charmap_index];
    if (nullptr == charmap)
      continue;


    bool bHaveCharMap = false;
    bool bHaveCharCode = false;
    bool bBuggyMap = false;
    bool bUnicode = false;
    unsigned int char_code = 0xFFFFFFFF;
    unsigned int gid = 0;

    const ON_wString e = ON_FreeType::CharmapPlatformEncodingDescription(charmap);

    switch (charmap->encoding)
    {
    case FT_ENCODING_UNICODE:
      char_code = unicode_code_point;
      bHaveCharCode = true;
      bUnicode = true;
      break;

    case FT_ENCODING_APPLE_ROMAN:
      bBuggyMap = ON_FreeType::UseUnicodeAsAppleRomanCharCode(face);
      if ( bBuggyMap )
      {
        bHaveCharCode = unicode_code_point <= 0xFF;
        if (bHaveCharCode)
        {
          bUnicode = true;
          char_code = unicode_code_point;
        }
      }
      else
      {
        // Microsoft code page 10000 = Apple Roman encoding
        char_code = ON_MapUnicodeToMSSBCP(10000, unicode_code_point);
        bHaveCharCode = (char_code <= 0xFF);
      }
      break;

    case FT_ENCODING_MS_SYMBOL:
      bHaveCharCode = true;
      char_code = unicode_code_point;
      break;

    default:
      break;
    }

    if (bHaveCharCode)
    {
      bHaveCharMap
        = FT_Err_Ok == FT_Set_Charmap(face, charmap)
        && charmap == face->charmap;
      if (bHaveCharMap)
      {
        gid = FT_Get_Char_Index(face, char_code);
        if (glyph_index != gid)
          rc = false;
      }
      else
        rc = false;
    }

    if (text_log)
    {
      const wchar_t* damaged = ( bBuggyMap || ON_FreeType::IsDamagedCharMap(charmap) )? L"DAMAGED " : L"";
      ON_wString s = ON_wString::FormatToString(
        L"%lscmap[%d] %ls",
        damaged,
        charmap_index,
        static_cast<const wchar_t*>(e)
      );

      s += ON_wString::FormatToString(L" U+%04X", unicode_code_point);
      if (false == bHaveCharCode)
        s += L" (no char code)";
      if (false == bUnicode || bBuggyMap || char_code != unicode_code_point)
        s += ON_wString::FormatToString(L" -> char code 0x%X (%u)", char_code, char_code);

      if (false == bHaveCharMap)
      {
        s += L" ERROR(cannot use cmap)";
      }
      else if (0 == gid)
      {
        s += ON_wString::FormatToString(
          L" no glpyh",
          char_code
        );
      }
      else
      {
        s += ON_wString::FormatToString(
          L" -> glyph id %u",
          gid
        );
        if (glyph_index != gid)
        {
          s += ON_wString::FormatToString(L"ERROR(expected glyph index %u)",glyph_index);
        }
      }
      text_log->Print(L"%ls\n", static_cast<const wchar_t*>(s));
    }
  }

  // restore face charmap state
  FT_Set_Charmap(face, charmap0);

  return rc;
}

unsigned int ON_FreeType::GlyphId(
    FT_Face face,
    ON__UINT32 unicode_code_point
  )
{
  if (nullptr == face)
    return 0;

  const FT_CharMap charmap0 = face->charmap;
  if (nullptr == charmap0 || FT_ENCODING_UNICODE != charmap0->encoding)
  {
    if (FT_Err_Ok != FT_Select_Charmap(face, FT_ENCODING_UNICODE))
      FT_Set_Charmap(face, charmap0);
  }

  FT_CharMap charmap1 = face->charmap;
  if (nullptr != charmap1 && FT_ENCODING_UNICODE == charmap1->encoding)
  {
    unsigned int glyph_id = FT_Get_Char_Index(face, unicode_code_point);
    if (0 != glyph_id)
    {
      // commonly happens for well designed modern fonts.
      return glyph_id;
    }
  }
  else
  {
    charmap1 = nullptr;
  }

  // May 2017 Dale Lear
  //
  // In some fonts, there are multiple FT_ENCODING_UNICODE charmaps
  // and they can map different unicode code points. These typically are
  // Windows UCS-2 and Windows UCS-4 cmaps. UCS-2 and UCS-4 values subsets of Unicode.
  //
  // In fonts like CityBlueprint and CountryBlueprint (which many customers use), there
  // is no FT_ENCODING_UNICODE charmap but there is a viable FT_ENCODING_APPLE_ROMAN charmap.
  //
  // As we discover fonts that customers use, we will add support for their charmaps.
  //
  // TrueType platform_id and encoding_id. The encoding id is platform specific.
  // platform_id-encoding_id
  //
  //  0-* "Apple *code" - encoding id varies
  //
  //  1-0 Apple Roman (256 codes - see ON_MapAppleRomanToUnicode())
  //  1-* Apple (encoding id = script manager)
  //
  //  2-* ISO (encoding id = ISO encoding)
  //
  //  3-0 Windows Symbol
  //  3-1 Wnidows UCS-2 (subset of Unicode)
  //  3-2 Windows ShiftJIS
  //  3-3 Windows Big5
  //  3-4 WIndows PRC
  //  3-5 Windows Wansung
  //  3-6 Windows Johab
  //  3-10 Wnidows UCS-4 (subset of Unicode)
  //
  //  4-* Custom
  //
  // http://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=iws-chapter08
  //
  const FT_Encoding encoding_pass[]
  {
    FT_ENCODING_UNICODE,
    FT_ENCODING_APPLE_ROMAN,
    FT_ENCODING_NONE // FT_ENCODING_NONE must terminate the array
  };

  const size_t pass_count = sizeof(encoding_pass) / sizeof(encoding_pass[0]);

  for (size_t pass = 0; pass < pass_count; pass++)
  {
    if (pass+1 >= pass_count && unicode_code_point >= 0x80)
    {
      // As a last gasp pass, when the unicode_code_point < 0x80, we try every charmap
      // because using the "ASCII encoding" for those code points was farily common
      // in old fonts and the charmap identifion may be incorrect.
      break;
    }

    // Often, ft_face has multiple FT_ENCODING_UNICODE charmaps and
    // sometimes FT_Select_Charmap() sometimes selects the wrong one
    // when we want a glyph for a specific unicode code point.
    const FT_Encoding e = encoding_pass[pass];
    for ( int charmap_index = 0; charmap_index < face->num_charmaps; charmap_index++)
    {
      const FT_CharMap charmap = face->charmaps[charmap_index];
      if (nullptr == charmap)
        continue;

      if (charmap1 == charmap)
        continue; // charmap1 was already tested.

      if (FT_ENCODING_NONE != e)
      {
        if ( e != charmap->encoding)
         continue; // wrong encoding for this pass
      }
      else
      {
        if (FT_ENCODING_UNICODE == charmap->encoding)
          continue; // already tested
      }

      if (FT_Err_Ok != FT_Set_Charmap(face, charmap))
        continue;
      if (charmap != face->charmap)
        continue;

      unsigned int charcode = 0xFFFFFFFF;
      switch (e)
      {
      case FT_ENCODING_APPLE_ROMAN:
        // Required to get CityBlueprint and CountryBlueprint fonts to work correctly.
        if (ON_FreeType::UseUnicodeAsAppleRomanCharCode(face))
        {
          // Buggy font.
          // The FT_ENCODING_APPLE_ROMAN encoding in these fonts is really a unicode encoding.
          charcode = unicode_code_point;
        }
        else
        {
          // Microsoft code page 10000 = Apple Roman
          // Single byte encoding
          charcode = ON_MapUnicodeToMSSBCP(10000, unicode_code_point);
          if (charcode > 0xFF)
            continue; // no mapping from Unicode to Apple Roman
        }
        break;

      case FT_ENCODING_UNICODE:
        charcode = unicode_code_point;
        break;

      default:
        // This is risky but might work when unicode_code_point < 0x80
        charcode = unicode_code_point;
        break;
      }

      // see if the glyph is in this char map
      unsigned int glyph_id = FT_Get_Char_Index(face, charcode);
      if (0 == glyph_id)
        continue;

      return glyph_id;
    }
  }

  // No glpyh for this unicode code point is available.
  FT_Set_Charmap(face, charmap0);

  return 0;
}

#if defined(ON_RUNTIME_WIN)

static bool Internal_CreateFontBufferFromDirectWrite(
  IDWriteFont* dwriteFont,
  ON_FontFileBuffer& font_buffer
)
{
  font_buffer.AllocateBuffer(0);

  if (nullptr == dwriteFont)
    return false;

  Microsoft::WRL::ComPtr<IDWriteFontFace> dwriteFontFace = nullptr;
  HRESULT hr = dwriteFont->CreateFontFace(&dwriteFontFace);
  if (FAILED(hr))
    return false;
  if (nullptr == dwriteFontFace || nullptr == dwriteFontFace.Get() )
    return false;

  UINT32 numfiles = 0;
  hr = dwriteFontFace->GetFiles(&numfiles, nullptr);
  if (FAILED(hr))
    return false;
  if (numfiles <= 0)
    return false;

  if (numfiles > 1)
  {
    // The docs state that this function should be called twice; first to obtain
    // the number of files. In the context of FreeType, I'm not sure what to do
    // with multiple files.
    ON_WARNING("Multiple font files.");
    numfiles = 1;
  }

  Microsoft::WRL::ComPtr<IDWriteFontFile> dwriteFontFile = nullptr;
  hr = dwriteFontFace->GetFiles(&numfiles, &dwriteFontFile);
  if (FAILED(hr))
    return false;
  if (nullptr == dwriteFontFile || nullptr == dwriteFontFile.Get())
    return false;

  const void* reference_key = nullptr;
  UINT32 reference_key_size = 0;
  hr = dwriteFontFile->GetReferenceKey(&reference_key, &reference_key_size);
  if (FAILED(hr))
    return false;

  Microsoft::WRL::ComPtr<IDWriteFontFileLoader> dwriteFontFileLoader = nullptr;
  hr = dwriteFontFile->GetLoader(&dwriteFontFileLoader);
  if (FAILED(hr))
    return false;
  if (nullptr == dwriteFontFileLoader || nullptr == dwriteFontFileLoader.Get() )
    return false;

  Microsoft::WRL::ComPtr<IDWriteFontFileStream> dwriteFontFileStream = nullptr;
  hr = dwriteFontFileLoader->CreateStreamFromKey(reference_key, reference_key_size, &dwriteFontFileStream);
  if (FAILED(hr))
    return false;
  if (nullptr == dwriteFontFileStream || nullptr == dwriteFontFileStream.Get() )
    return false;

  UINT64 filesize = 0;
  hr = dwriteFontFileStream->GetFileSize(&filesize);
  if (FAILED(hr))
    return false;
  if (filesize <= 0)
    return false;

  const void *fragstart = nullptr;
  void *fragcontext = nullptr;
  hr = dwriteFontFileStream->ReadFileFragment(&fragstart, 0, filesize, &fragcontext);
  if (FAILED(hr))
    return false;

  if (nullptr != fragstart)
  {
    void* buffer = font_buffer.AllocateBuffer((size_t)filesize);
    if (nullptr != buffer && font_buffer.SizeOfBuffer() >= (size_t)filesize)
      memcpy(buffer, fragstart, font_buffer.SizeOfBuffer());
  }

  dwriteFontFileStream->ReleaseFileFragment(fragcontext);

  return (font_buffer.SizeOfBuffer() > 0);
}

static bool Internal_CreateFontBufferFromDirectWrite(
  const LOGFONT& logfont,
  ON_FontFileBuffer& font_buffer
)
{
  font_buffer.AllocateBuffer(0);

  if (0 == logfont.lfFaceName[0])
    return false;

  Microsoft::WRL::ComPtr<IDWriteFactory> dwriteFactory = nullptr;
  HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &dwriteFactory);
  if (FAILED(hr))
    return false;
  if (nullptr == dwriteFactory || nullptr == dwriteFactory.Get())
    return false;

  //fonts on this computer
  Microsoft::WRL::ComPtr<IDWriteFontCollection> dwriteFontCollection = nullptr;
  hr = dwriteFactory->GetSystemFontCollection(&dwriteFontCollection, true);
  if (FAILED(hr))
    return false;
  if (nullptr == dwriteFontCollection || nullptr == dwriteFontCollection.Get())
    return false;

  Microsoft::WRL::ComPtr< IDWriteGdiInterop > dwriteGdiInterop = nullptr;
  hr = dwriteFactory->GetGdiInterop(&dwriteGdiInterop);
  if (FAILED(hr))
    return false;
  if (nullptr == dwriteGdiInterop || nullptr == dwriteGdiInterop.Get())
    return false;

  LOGFONT cleanLogFont = logfont;

  cleanLogFont.lfHeight = 0;
  cleanLogFont.lfWidth = 0;
  cleanLogFont.lfEscapement = 0;
  cleanLogFont.lfOrientation = 0;
  if (cleanLogFont.lfWeight < 1 || cleanLogFont.lfWeight > 999)
    cleanLogFont.lfWeight = 400;
  if (0 != cleanLogFont.lfItalic)
    cleanLogFont.lfItalic = 1;
  if (0 != cleanLogFont.lfUnderline)
    cleanLogFont.lfUnderline = 1;
  if (0 != cleanLogFont.lfStrikeOut)
    cleanLogFont.lfStrikeOut = 1;
  if (ON_Font::WindowsConstants::logfont_symbol_charset != cleanLogFont.lfCharSet)
    cleanLogFont.lfCharSet = ON_Font::WindowsConstants::logfont_default_charset;
  cleanLogFont.lfOutPrecision = ON_Font::WindowsConstants::logfont_out_precis;
  cleanLogFont.lfClipPrecision = 0;
  cleanLogFont.lfQuality = ON_Font::WindowsConstants::logfont_quality;
  cleanLogFont.lfPitchAndFamily = ON_Font::WindowsConstants::logfont_pitch_and_family;

  Microsoft::WRL::ComPtr<IDWriteFont> dwriteFont = nullptr;
  hr = dwriteGdiInterop->CreateFontFromLOGFONT(&cleanLogFont, &dwriteFont);
  if (FAILED(hr))
    return false;
  if (nullptr == dwriteFont || nullptr == dwriteFont.Get())
    return false;

  return Internal_CreateFontBufferFromDirectWrite(dwriteFont.Get(), font_buffer);
}

static bool Internal_CreateFontBufferFromGDI(
  const LOGFONT& logfont,
  ON_FontFileBuffer& font_buffer
)
{
  font_buffer.AllocateBuffer(0);

  HDC font_hdc = nullptr;
  HFONT hfont = nullptr;
  HGDIOBJ hfont_original = nullptr;
  bool rc = false;
  for (;;)
  {
    hfont = ::CreateFontIndirect(&logfont);
    if (0 == hfont)
    {
      ON_ERROR("CreateFontIndirect failed.");
      break;
    }

    font_hdc = ON_Font::CreateWindowsLogfontDeviceContext();
    if (nullptr == font_hdc)
    {
      ON_ERROR("ON_Font::CreateWindowsLogfontDeviceContext()(nullptr) failed.");
      break;
    }

    hfont_original = ::SelectObject(font_hdc, hfont);
    if (nullptr == hfont_original)
    {
      ON_ERROR("SelectObject(hdc, hfont) failed.");
      break;
    }

    //const DWORD dwTable_TrueTypeCollection = 0x66637474;
    DWORD  dwTable = 0;
    DWORD  dwOffset = 0;
    const DWORD buffer_capacity = ::GetFontData(font_hdc, dwTable, dwOffset, nullptr, 0);
    if (buffer_capacity <= 0)
    {
      ON_ERROR("GetFontData(...,nullptr,0) failed.");
      break;
    }

    void* buffer = font_buffer.AllocateBuffer(buffer_capacity);
    if (nullptr == buffer)
    {
      ON_ERROR("onmalloc(buffer_capacity) failed.");
      break;
    }
    memset(buffer, 0, buffer_capacity);

    const DWORD buffer_size = ::GetFontData(font_hdc, dwTable, dwOffset, buffer, buffer_capacity);
    if ( buffer_size != buffer_capacity )
    {
      ON_ERROR("GetFontData(...,nullptr,0) failed.");
      break;
    }

    rc = true;
    break;
  }

  if (false == rc)
  {
    font_buffer.AllocateBuffer(0);
  }

  if (nullptr != font_hdc)
  {
    if (nullptr != hfont_original)
      ::SelectObject(font_hdc, hfont_original);
    ON_Font::DeleteWindowsLogfontDeviceContext(font_hdc);
  }

  if (nullptr != hfont)
  {
    ::DeleteObject(hfont);
  }

  return (font_buffer.SizeOfBuffer() > 0);
}

ON_FreeTypeFace* ON_FreeType::Internal_CreateFaceFromWindowsFont(
  const LOGFONT* logfont
)
{
  if (nullptr == logfont)
    return nullptr;

  FT_Library freetype_library = ON_FreeType::Library();
  if (nullptr == freetype_library)
    return nullptr;
  for (int pass = 1; pass <= 2; pass++)
  {
    ON_FontFileBuffer font_buffer;

    // May 2015 Dale Lear
    //  The DirectWrite approach yields better results in some cases.
    //  For example, the Yu Gothic in Windows 10
    //    The font_buffer created by DirectWrite results in an FT_Face
    //    with 3 charmaps (2 Uniocde) and the font_buffer created by
    //    GDI has 0 charmaps which means getting a glyph from a code point
    //    is not possible.
    const bool bHaveBuffer
      = (1 == pass)
      ? Internal_CreateFontBufferFromDirectWrite(*logfont, font_buffer)
      : Internal_CreateFontBufferFromGDI(*logfont, font_buffer);

    if (false == bHaveBuffer)
      continue;
    if (font_buffer.SizeOfBuffer() <= 0)
      continue;
    if (nullptr == font_buffer.Buffer())
      continue;

    int font_face_index = 0;
    FT_Face face = nullptr;
    FT_Error rc = FT_New_Memory_Face(
      freetype_library,
      reinterpret_cast<const FT_Byte*>(font_buffer.Buffer()),
      (FT_Long)font_buffer.SizeOfBuffer(),
      font_face_index,
      &face
    );

    if (nullptr == face)
      continue;

    if (FT_Err_Ok != rc)
    {
      FT_Done_Face(face);
      continue;
    }

    ON_FreeTypeFace* f = new ON_FreeTypeFace();

    f->m_face = face;
    font_buffer.TransferTo(f->m_font_buffer);

    return f;
  }

  return nullptr;
}

#endif


#if defined (ON_RUNTIME_COCOA_AVAILABLE)

ON_FreeTypeFace* ON_FreeType::Internal_CreateFaceFromAppleFont (CTFontRef fontRef)
{
  if (nullptr == fontRef)
    return nullptr;

  // determine file path for CTFont
  CFURLRef fontURLRef = (CFURLRef) CTFontCopyAttribute (fontRef, kCTFontURLAttribute);

  NSURL* fontURL = (NSURL*) CFBridgingRelease (fontURLRef);
  const char* path = fontURL.path.UTF8String;

  // Search all the faces in this font file for a face that matches the NSFont family and style
  FT_Face ftFace;
  FT_Error err = FT_New_Face (ON_FreeType::Library(), path, 0, &ftFace);    // get first face
  if (err)
    return nullptr;     // that didn't work

  const int numFaces = (int)ftFace->num_faces; // determine number of faces in the font file

  ON_FreeTypeFace* rc = new ON_FreeTypeFace();
  if (numFaces <= 1)
  {
    rc->m_face = ftFace;
    return rc;       // only one face, so this must be the right one
  }

  int faceIndex = 0;
  for (;;)
  {
    const ON_wString appleFamilyName = ON_Font::AppleCTFontFamilyName(fontRef);
    const ON_wString appleStyleName = ON_Font::AppleCTFontFaceName(fontRef);
    const ON_wString ftFamilyName(ftFace->family_name);
    const ON_wString ftStyleName(ftFace->style_name);

    if (
        ON_wString::EqualOrdinal(appleFamilyName, ftFamilyName, true)
        && ON_wString::EqualOrdinal(appleStyleName, ftStyleName, true)
        )
    {
      rc->m_face = ftFace;
      return rc;
    }

    // No match.  Step to next face.
    FT_Done_Face (ftFace);

    FT_Error err = FT_New_Face (ON_FreeType::Library(), path, ++faceIndex, &ftFace);
    if (ftFace == nullptr || err || faceIndex >= numFaces) {
      // Ran out of faces to inspect or FT_New_Face returned an error.
      FT_Done_Face (ftFace);
      break;
    }
  }

  // When no match found, use first face in font file as the default face.
  FT_New_Face (ON_FreeType::Library(), path, 0, &ftFace);    // get first face

  rc->m_face = ftFace;
  return rc;
}

#endif    // ON_RUNTIME_APPLE

#if defined(ON_RUNTIME_ANDROID)
ON_FreeTypeFace* ON_FreeType::Internal_CreateFaceWithAndroidNdk(const ON_Font& font)
{
  AFontMatcher* ndkFontMatcher = AFontMatcher_create();
  if (nullptr == ndkFontMatcher)
    return nullptr;
  ON_String familyName = font.FamilyName();
  const uint16_t* text = (const uint16_t*)"XYZ";
  ON_FreeTypeFace* rc = nullptr;
  AFont* ndkFont = AFontMatcher_match(ndkFontMatcher, familyName, text, 3, nullptr);
  if (ndkFont)
  {
    size_t index = AFont_getCollectionIndex(ndkFont);
    const char* path = AFont_getFontFilePath(ndkFont);
    FT_Face ftFace;
    FT_Error err = FT_New_Face (ON_FreeType::Library(), path, 0, &ftFace);    // get first face
    if (0 == err)
    {
      rc = new ON_FreeTypeFace();
      rc->m_face = ftFace;
    }
    AFont_close(ndkFont);
  }
  AFontMatcher_destroy(ndkFontMatcher);
  return rc;
}

#endif

ON_FreeTypeFace* ON_FreeType::CreateFace(
  const ON_Font& font
)
{
  ON_FreeTypeFace* f = nullptr;

  if (false == font.IsManagedFont())
  {
    // Managed fonts have valid settings.
    return nullptr;
  }

#if defined(ON_RUNTIME_WIN)
  LOGFONT logfont = font.WindowsLogFont(0,nullptr);
  f = ON_FreeType::Internal_CreateFaceFromWindowsFont(&logfont);
#endif

#if defined (ON_RUNTIME_COCOA_AVAILABLE)
  bool bIsSubstituteFont = false;
  f = ON_FreeType::Internal_CreateFaceFromAppleFont(font.AppleCTFont(bIsSubstituteFont));
#endif

#if defined(ON_RUNTIME_ANDROID)
  f = ON_FreeType::Internal_CreateFaceWithAndroidNdk(font);
#endif

  // Create empty holder so this function doesn't repeatedly
  // try to load the freetype face.
  if (nullptr == f)
    f = new ON_FreeTypeFace();

  return f;
}

ON__UINT_PTR ON_Font::FreeTypeFace(
  const ON_Font* font
)
{
  if (nullptr == font)
    return 0;
  const ON_Font* managed_font = font->ManagedFont();
  if (nullptr == managed_font)
    return 0;

  if (0 == managed_font->m_free_type_face)
  {
    managed_font->m_free_type_face = ON_FreeType::CreateFace(*managed_font);
  }

  FT_Face ft_face
    = (nullptr != managed_font->m_free_type_face)
    ? managed_font->m_free_type_face->m_face
    : nullptr;

  return (ON__UINT_PTR)ft_face;
}

void ON_Font::DestroyFreeTypeFace(
  const ON_Font* font
)
{
  if (nullptr != font && nullptr != font->m_free_type_face)
  {
    if (font->IsManagedFont())
      delete font->m_free_type_face;
    font->m_free_type_face = nullptr;
  }
}

const ON__UINT_PTR ON_FontGlyph::FreeTypeFace() const
{
  return
    (nullptr == m_managed_font)
    ? 0
    : ON_Font::FreeTypeFace(m_managed_font);
}

unsigned int ON_FreeTypeGetFontUnitsPerM(
  const ON_Font* font
  )
{
  for(;;)
  {
    if (nullptr == font)
      break;
    font = font->ManagedFont();
    if (nullptr == font)
      break;

    const ON__UINT_PTR ft_face_as_uint = ON_Font::FreeTypeFace(font);
    if (0 == ft_face_as_uint)
      break;

    FT_Face ft_face = (FT_Face)ft_face_as_uint;

    unsigned int freetypeUPM =  (unsigned int)ft_face->units_per_EM;
    if (freetypeUPM > 0 && freetypeUPM < 0xFFFFFFF)
      return freetypeUPM;

    break;
  }

  return 0;
}

#if defined(ON_RUNTIME_APPLE)
#include "opennurbs_apple_nsfont.h"
#endif

void ON_FreeTypeGetFontMetrics(
  const ON_Font* font,
  ON_FontMetrics& font_unit_font_metrics
)
{
  font_unit_font_metrics = ON_FontMetrics::Unset;

  font = font->ManagedFont();
  if (nullptr == font)
    return;

  const ON__UINT_PTR ft_face_as_uint = ON_Font::FreeTypeFace(font);
  if (0 == ft_face_as_uint)
    return;

  FT_Face ft_face = (FT_Face)ft_face_as_uint;

  /*

  if (nullptr == glyph || false == glyph->CodePointIsSet())
    return 0;

  const ON_Font* font = glyph->Font();
  if (nullptr == font)
    return 0;
  font = font->ManagedFont();
  if (nullptr == font)
    return 0;



  const unsigned int glyph_id
    = glyph->FontGlyphIdIsSet()
    ? (unsigned int)glyph->FontGlyphId()
    : ON_FreeType::GlyphId(face, glyph->CodePoint());
  if (0 == glyph_id)
    return 0;
    */

  // Turns out that checking H and I doesn't work very well for some
  // fonts designed for Asian languages, symbol fonts, and emoji fonts.
  const ON_FontGlyph Iglyph(font, 'I');
  ON_TextBox Ibox = ON_TextBox::Unset;
  const int ascent_of_I
    = (0 != ON_FreeTypeGetGlyphMetrics(&Iglyph, Ibox) && Ibox.IsSet() && Ibox.m_bbmax.j > 0)
    ? Ibox.m_bbmax.j
    : 0;

  const ON_FontGlyph Hglyph(font, 'H');
  ON_TextBox Hbox = ON_TextBox::Unset;
  const int ascent_of_H
    = (0 != ON_FreeTypeGetGlyphMetrics(&Hglyph, Hbox) && Hbox.IsSet() && Hbox.m_bbmax.j > 0)
    ? Hbox.m_bbmax.j
    : 0;

  const int ascent_of_capital = (ascent_of_H >= ascent_of_I) ? ascent_of_H : ascent_of_I;

  font_unit_font_metrics.SetAscentOfCapital(ascent_of_capital);

  font_unit_font_metrics.SetHeights(
    ft_face->ascender,
    ft_face->descender,
    ft_face->units_per_EM,
    ft_face->height
  );

  font_unit_font_metrics.SetUnderscore(
    ft_face->underline_position,
    ft_face->underline_thickness
  );

  // Turns out there are better strikeout values in DWRITE  information.
  double h = (double)((ascent_of_capital > 0) ? ascent_of_capital : ft_face->ascender);
  font_unit_font_metrics.SetStrikeout(
    (0.5*h),
    (0.5*((double)ft_face->underline_thickness))
  );

}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class ON_FreeTypeOutlineAccumlator : public ON_OutlineAccumulator
{
public:
  ON_FreeTypeOutlineAccumlator() = default;
  ~ON_FreeTypeOutlineAccumlator() = default;

  bool AddFreeTypeFiguresToOutline(
    FT_Face ft_face,
    FT_UInt font_glyph_id,
    ON_Outline& outline
  );

private:
  ON_FreeTypeOutlineAccumlator(const ON_FreeTypeOutlineAccumlator&) = delete;
  ON_FreeTypeOutlineAccumlator& operator=(const ON_FreeTypeOutlineAccumlator&) = delete;

//public:
//  bool BeginGlyphOutline(
//    ON__UINT32 font_units_per_em,
//    bool bSingleStrokeFont,
//    ON_Outline* destination_outline,
//    FT_Face ft_face, FT_UInt font_glyph_id, FT_Orientation* ft_orientation
//  );
//
//  bool BeginGlyphOutline(
//    ON__UINT32 font_units_per_em,
//    bool bSingleStrokeFont,
//    ON_Outline* destination_outline,
//    FT_Face ft_face, FT_UInt font_glyph_id, FT_Orientation* ft_orientation
//  );

private:
  FT_Orientation m_ft_orientation = FT_ORIENTATION_NONE;
  ON_OutlineFigurePoint::Type m_end_figure_point_type = ON_OutlineFigurePoint::Type::Unset;

  FT_Vector m_start_point;
  FT_Vector m_prev_point;

  static const ON_2fPoint Internal_To2fPoint(const FT_Vector* v) { return ON_2fPoint((float)(v->x), (float)(v->y)); }

  bool Internal_EndPreviousFigure()
  {
    // Freetype has a bad habit of leaving the last figure unclosed.
    const bool rc = (CurrentFigurePointCount() >= 2 && CurrentFigureAccumulating() && CurrentFigurePoint().IsOnFigure());
    if (rc)
      EndFigure(m_end_figure_point_type);
    return rc;
  }

  static int Internal_FreeTypeOutlineMoveToFunc(
    const FT_Vector* to,
    void* user
  );
  static int Internal_FreeTypeOutlineLineToFunc(
    const FT_Vector* to,
    void* user
  );
  static int Internal_FreeTypeOutlineConicToFunc(
    const FT_Vector* control,
    const FT_Vector* to,
    void* user
  );
  static int Internal_FreeTypeOutlineCubicToFunc(
    const FT_Vector* control1,
    const FT_Vector* control2,
    const FT_Vector* to,
    void* user
  );
  static int Internal_FreeTypeOutlineLineToCloseContourFunc(
    const FT_Vector* to,
    void* user
  );
};


const ON_TextBox ON_TextBox_CreateFromFreeTypeGlyphMetrics(
  const FT_Glyph_Metrics* ft_glyph_metrics
)
{
  if (nullptr == ft_glyph_metrics)
    return ON_TextBox::Unset;

  // Must use ft_load_flags that include FT_LOAD_NO_SCALE, in order
  // to get units are expressed in font design units.
  ON_TextBox glyph_metrics;
  glyph_metrics.m_bbmin.i = (int)(ft_glyph_metrics->horiBearingX);
  glyph_metrics.m_bbmin.j = (int)(ft_glyph_metrics->horiBearingY - ft_glyph_metrics->height);
  glyph_metrics.m_bbmax.i = (int)(ft_glyph_metrics->horiBearingX + ft_glyph_metrics->width);
  glyph_metrics.m_bbmax.j = (int)(ft_glyph_metrics->horiBearingY);
  glyph_metrics.m_advance.i = (int)(ft_glyph_metrics->horiAdvance);
  glyph_metrics.m_advance.j = (int)(ft_glyph_metrics->vertAdvance); // positive values mean downwards advance

  return glyph_metrics;
}

bool ON_FreeTypeOutlineAccumlator::AddFreeTypeFiguresToOutline(
  FT_Face ft_face,
  FT_UInt font_glyph_id,
  ON_Outline& outline
)
{
  bool rc = false;

  for (;;)
  {

    if (nullptr == ft_face)
      break;

    if (0 == font_glyph_id)
      break;

    if (false == ON_FreeTypeLoadGlyph((ON__UINT_PTR)ft_face, font_glyph_id, false))
      break;

    rc = true;

    const ON_TextBox glyph_metrics_in_font_design_units = ON_TextBox_CreateFromFreeTypeGlyphMetrics(&ft_face->glyph->metrics);
    outline.SetGlyphMetrics(glyph_metrics_in_font_design_units);

    FT_Glyph ft_glyph = nullptr;
    if (FT_Err_Ok != FT_Get_Glyph(ft_face->glyph, &ft_glyph))
      break;
    if (nullptr == ft_glyph)
      break;

    if (FT_GLYPH_FORMAT_OUTLINE != ft_glyph->format)
      break;

    const FT_OutlineGlyph ft_outline_glyph = (FT_OutlineGlyph)ft_glyph;

    FT_Outline ft_outline = ft_outline_glyph->outline;

    if (ft_outline.n_points <= 0 || nullptr == ft_outline.points)
    {
      FT_Done_Glyph(ft_glyph);
      break;
    }

    m_ft_orientation = FT_Outline_Get_Orientation(&ft_outline);
    m_end_figure_point_type
      = (ON_OutlineFigure::Type::SingleStroke == outline.FigureType())
     ? ON_OutlineFigurePoint::Type::EndFigureOpen
     : ON_OutlineFigurePoint::Type::EndFigureClosed;


    FT_Outline_Funcs ft_outline_funcs;
    memset(&ft_outline_funcs, 0, sizeof(ft_outline_funcs));
    ft_outline_funcs.move_to = ON_FreeTypeOutlineAccumlator::Internal_FreeTypeOutlineMoveToFunc;
    ft_outline_funcs.line_to = ON_FreeTypeOutlineAccumlator::Internal_FreeTypeOutlineLineToFunc;
    ft_outline_funcs.conic_to = ON_FreeTypeOutlineAccumlator::Internal_FreeTypeOutlineConicToFunc;
    ft_outline_funcs.cubic_to = ON_FreeTypeOutlineAccumlator::Internal_FreeTypeOutlineCubicToFunc;
    ft_outline_funcs.line_to_close_contour = ON_FreeTypeOutlineAccumlator::Internal_FreeTypeOutlineLineToCloseContourFunc;

    FT_Outline_Decompose(&ft_outline, &ft_outline_funcs, (void*)this);

    // Frees point memory
    FT_Done_Glyph(ft_glyph);

    // Freetype has a bad habit of leaving the last figure unclosed.
    Internal_EndPreviousFigure();

    break;
  }

  return rc;
}

int ON_FreeTypeOutlineAccumlator::Internal_FreeTypeOutlineMoveToFunc(
  const FT_Vector* to,
  void* user
)
{
  ON_FreeTypeOutlineAccumlator* a = (ON_FreeTypeOutlineAccumlator*)user;
  if (nullptr == a)
    return FT_Err_Invalid_Argument;

  // freetype has a bad habit of failing to end the previous figure.
  a->Internal_EndPreviousFigure();

  a->BeginFigure(ON_OutlineFigurePoint::Type::BeginFigureUnknown, Internal_To2fPoint(to));
  a->m_start_point = *to;
  a->m_prev_point = *to;

  return FT_Err_Ok;
}

int ON_FreeTypeOutlineAccumlator::Internal_FreeTypeOutlineLineToFunc(
  const FT_Vector* to,
  void* user
)
{
  ON_FreeTypeOutlineAccumlator* a = (ON_FreeTypeOutlineAccumlator*)user;
  if (nullptr == a)
    return FT_Err_Invalid_Argument;

  a->AppendLine(Internal_To2fPoint(to));
  a->m_prev_point = *to;

  return FT_Err_Ok;
}

int ON_FreeTypeOutlineAccumlator::Internal_FreeTypeOutlineLineToCloseContourFunc(
  const FT_Vector* to,
  void* user
)
{
  ON_FreeTypeOutlineAccumlator* a = (ON_FreeTypeOutlineAccumlator*)user;
  if (nullptr == a)
    return FT_Err_Invalid_Argument;

  a->EndFigure(a->m_end_figure_point_type);
  a->m_prev_point = *to;

  return FT_Err_Ok;
}

int ON_FreeTypeOutlineAccumlator::Internal_FreeTypeOutlineConicToFunc(
  const FT_Vector* control,
  const FT_Vector* to,
  void* user
)
{
  ON_FreeTypeOutlineAccumlator* a = (ON_FreeTypeOutlineAccumlator*)user;
  if (nullptr == a)
    return FT_Err_Invalid_Argument;

  a->AppendQuadraticBezier(Internal_To2fPoint(control),Internal_To2fPoint(to));
  a->m_prev_point = *to;

  return FT_Err_Ok;
}

int ON_FreeTypeOutlineAccumlator::Internal_FreeTypeOutlineCubicToFunc(
  const FT_Vector* control1,
  const FT_Vector* control2,
  const FT_Vector* to,
  void* user
)
{
  ON_FreeTypeOutlineAccumlator* a = (ON_FreeTypeOutlineAccumlator*)user;
  if (nullptr == a)
    return FT_Err_Invalid_Argument;

  a->AppendCubicBezier(Internal_To2fPoint(control1),Internal_To2fPoint(control2),Internal_To2fPoint(to));
  a->m_prev_point = *to;

  return FT_Err_Ok;
}


bool ON_FreeTypeLoadGlyph(
  ON__UINT_PTR ft_face_ptr,
  unsigned int ft_glyph_index,
  bool bLoadRenderBitmap
)
{
  FT_Face ft_face = (FT_Face)ft_face_ptr;
  if (nullptr == ft_face)
    return false;

  const FT_UInt font_glyph_id = (FT_UInt)ft_glyph_index;
  if (0 == font_glyph_id)
    return false;

#if defined(ON_RUNTIME_WIN)
  const int pass0 = 1;
#else
  const int pass0 = 1;
#endif
  for (int pass = bLoadRenderBitmap ? 1 : pass0; pass < 2; pass++)
  {
    FT_Int32 ft_face_load_no_scale_flag
      = (0 == pass)
      ? 0
      : FT_LOAD_NO_SCALE;


    if (0 == pass)
    {
      const FT_UInt ft_font_height
        = (0 == pass)
        ? ((FT_UInt)ON_Font::Constants::AnnotationFontCellHeight)
        : ((FT_UInt)ft_face->units_per_EM);
      /*
        Avoid use of FT_LOAD_NO_SCALE
        https://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_LOAD_NO_SCALE
          If the font is ‘tricky’ (see FT_FACE_FLAG_TRICKY for more), using FT_LOAD_NO_SCALE
          usually yields meaningless outlines because the subglyphs must be scaled and
          positioned with hinting instructions. This can be solved by loading the font
          without FT_LOAD_NO_SCALE and setting the character size to ‘font->units_per_EM’.
      */
#if defined(ON_RUNTIME_WIN)
      // Unit Systems:
      //  "ppt" = printers points = 1/72 inch
      // "lfu" = Windows logical font units = LOGFONT.lfHeight units
      // "linch" = "logical" inch units used by ::GetDeviceCaps(hdc, LOGPIXELS*)
      // "pixels" = "pixel" units used by ::GetDeviceCaps(hdc, LOGPIXELS*)
      HDC font_hdc = ON_Font::CreateWindowsLogfontDeviceContext();
      const int horiz_pixels_per_inch = ::GetDeviceCaps(font_hdc, LOGPIXELSX); // units = horiz pixels/"logical inch"
      const int vert_pixels_per_inch = ::GetDeviceCaps(font_hdc, LOGPIXELSY); // units = vertical pixels/"logical inch"
      ON_Font::DeleteWindowsLogfontDeviceContext(font_hdc);
      const double logical_font_height = ((double)ON_Font::Constants::AnnotationFontCellHeight); // units = lfu
      const double ppts_per_inch = 72.0; // printer points / inch
      // If "logical font units"/("pixels"/"logical inch") = "real" inch = 2.54 cm
      // then vpptr and hppts are in printers points.
      const double vppts = ppts_per_inch * logical_font_height / ((double)vert_pixels_per_inch);
      const double hppts = ppts_per_inch * logical_font_height / ((double)horiz_pixels_per_inch);

      const FT_F26Dot6 ft_char_width = (int)ceil(hppts*64.0);
      const FT_F26Dot6 ft_char_height = (int)ceil(vppts*64.0);
#else
      const FT_F26Dot6 ft_char_width = 0;
      const FT_F26Dot6 ft_char_height = 0;
#endif
      if (0 == ft_char_width || 0 == ft_char_height)
        continue;
      if (FT_Err_Ok != FT_Set_Char_Size(
        ft_face,
        ft_char_width,
        ft_char_height,
        ft_font_height,
        ft_font_height
      ))
      {
        continue;
      }
    }

    const FT_Int32 ft_load_outline_flags
      = FT_LOAD_NO_BITMAP
      | FT_LOAD_NO_HINTING
      | FT_LOAD_NO_AUTOHINT
      | ft_face_load_no_scale_flag
      | FT_LOAD_LINEAR_DESIGN
      | FT_LOAD_IGNORE_TRANSFORM
      ;

    const FT_Int32 ft_load_flags
      = (bLoadRenderBitmap)
      ? FT_LOAD_RENDER
      : ft_load_outline_flags;

    if (FT_Err_Ok != FT_Load_Glyph(ft_face, font_glyph_id, ft_load_flags))
      continue;

    return true;
  }

  return false;
}

// Returns font glyph id or 0
unsigned int ON_FreeTypeGetGlyphMetrics(
  const ON_FontGlyph* glyph,
  class ON_TextBox& glyph_metrics_in_font_design_units
)
{
  glyph_metrics_in_font_design_units = ON_TextBox::Unset;

  if (nullptr == glyph || false == glyph->CodePointIsSet())
    return 0;

  const ON_Font* font = glyph->Font();
  if (nullptr == font)
    return 0;
  font = font->ManagedFont();
  if (nullptr == font)
    return 0;

  const ON__UINT_PTR ft_face_as_uint = ON_Font::FreeTypeFace(font);
  if (0 == ft_face_as_uint)
    return 0;

  FT_Face face = (FT_Face)ft_face_as_uint;

  const unsigned int glyph_index
    = glyph->FontGlyphIndexIsSet()
    ? glyph->FontGlyphIndex()
    : ON_FreeType::GlyphId(face, glyph->CodePoint());
  if (0 == glyph_index)
    return 0;

  ////#if defined(ON_RUNTIME_APPLE) && defined(ON_DEBUG)
  ////  const unsigned int apple_glyph_id = ON_AppleNSFontGlyphIndex(font->AppleFont(), glyph->CodePoint());
  ////  if (glyph_id != apple_glyph_id)
  ////  {
  ////    // In an Aug 20, 2018 test, anytime glyph_id != apple_glyph_id, the freetype value
  ////    // was incorrect. AppleGothic is a good test case. When freetype and ON_AppleNSFontGlyphIndex
  ////    // are different, freetype is referencing a glyph index that font book doesn't show
  ////    // (and is unable to get outlines) or one that is a solid box (and freetype delivers
  ////    // a square for the glyph instead of the correct glyph).
  ////    ON_ERROR("ON_AppleNSFontGlyphIndex() failed.");
  ////    ON_AppleNSFontGlyphIndex(font->AppleFont(), glyph->CodePoint());
  ////  }
  ////#endif


  const bool bLoadRenderBitmap = false;
  // bLoadRenderBitmap = false means we load using FT_LOAD_NO_SCALE
  // This won't work for "tricky" font faces that render glyphs using composites.
  if (false == ON_FreeTypeLoadGlyph(ft_face_as_uint, glyph_index, bLoadRenderBitmap))
    return 0;

  if ( nullptr == face->glyph)
    return 0;

  // Because ft_load_flags includes FT_LOAD_NO_SCALE, the
  // face->glyph->metrics units are expressed in font design units.
  glyph_metrics_in_font_design_units = ON_TextBox_CreateFromFreeTypeGlyphMetrics(&face->glyph->metrics);

  return glyph_index;
}


bool ON_FreeTypeGetGlyphOutline(
  const ON_FontGlyph* glyph,
  ON_OutlineFigure::Type figure_type,
  class ON_Outline& outline
)
{
  const unsigned int glyph_index = 0;
  return ON_FreeTypeGetGlyphOutline(glyph, glyph_index, figure_type, outline);
}

bool ON_FreeTypeGetGlyphOutline(
  const ON_FontGlyph* glyph,
  unsigned int glyph_index,
  ON_OutlineFigure::Type figure_type,
  class ON_Outline& outline
)
{
  outline = ON_Outline::Unset;

  if (nullptr == glyph)
    return false;

  if (false == glyph->CodePointIsSet())
    return false;

  glyph = glyph->ManagedGlyph();

  const ON_Font* font = glyph->Font();
  if (nullptr == font)
    return false;

  if (ON_OutlineFigure::Type::Unset == figure_type)
  {
    ON_OutlineFigure::Type font_figure_type = font->OutlineFigureType();
    if (ON_OutlineFigure::Type::Unset != font_figure_type)
    {
      figure_type = font_figure_type;
    }
  }

  if (0 == glyph_index)
  {
    glyph_index = glyph->FontGlyphIndex();
    if (glyph_index <= 0)
      return false;
  }

  FT_Face ft_face = (FT_Face)(ON_Font::FreeTypeFace(font));
  if (nullptr == ft_face)
    return false;

  const ON_FontMetrics fm = font->FontUnitFontMetrics();

  ON_FreeTypeOutlineAccumlator a;

  bool rc = a.BeginGlyphOutline(fm.UPM(), figure_type, &outline);

  if (rc)
  {

    rc = a.AddFreeTypeFiguresToOutline(
      ft_face,
      (FT_UInt)glyph_index,
      outline
    );

    if (false == a.EndOutline())
      rc = false;
  }

  // Generally, AddFreeTypeFiguresToOutline() set the outline glyph metrics.
  if (false == outline.GlyphMetrics().IsSet())
    outline.SetGlyphMetrics(glyph->FontUnitGlyphBox());

  return rc;
}

void ON_Font::DumpFreeTypeFace(
  ON__UINT_PTR free_type_face_ptr,
  ON_TextLog& text_log
)
{
  FT_Face face = (FT_Face)free_type_face_ptr;
  if (nullptr == face)
  {
    text_log.Print("FT_Face nullptr\n");
    return;
  }

  text_log.Print(
    "FT_Face: face[%d] (%d faces in font definition)\n",
    face->face_index,
    face->num_faces
  );

  text_log.PushIndent();
  ON_wString s;

  s = face->family_name;
  text_log.Print("Family name = %ls\n", static_cast<const wchar_t*>(s));

  s = face->style_name;
  text_log.Print("Style name = %ls\n", static_cast<const wchar_t*>(s));

  FT_Long style_mask = 0xFFFF;
  s = ON_FreeType::StyleFlagsToString(face->style_flags);
  if ( 0 != (style_mask&face->style_flags) || s.IsNotEmpty() )
     text_log.Print( "Style flags = 0x%04x %ls\n", (style_mask&face->style_flags), static_cast<const wchar_t*>(s) );

  s = ON_FreeType::FaceFlagsToString(face->face_flags);
  if ( 0 != face->face_flags || s.IsNotEmpty() )
     text_log.Print( "Face flags = 0x%x %ls\n", (face->face_flags), static_cast<const wchar_t*>(s) );

  text_log.Print("%d glyphs\n", face->num_glyphs);
  text_log.Print("%d charmaps\n", face->num_charmaps);

  text_log.PushIndent();
  if (nullptr != face->charmaps)
  {
    for (int i = 0; i < face->num_charmaps; i++)
    {
      FT_CharMap cmap = face->charmaps[i];
      const wchar_t* damaged
        = ON_FreeType::IsDamagedCharMap(cmap)
        ? L"DAMAGED "
        : L"";
      s = ON_wString::FormatToString( L"%lscmap[%d]", damaged, i );
      if (nullptr == cmap)
        s += L"nullptr";
      else
      {
        const ON_wString s1 = ON_FreeType::CharmapPlatformEncodingDescription(cmap);
        s += ON_wString::FormatToString(L" %ls", static_cast<const wchar_t*>(s1));
      }
      text_log.Print("%ls\n", static_cast<const wchar_t*>(s));
    }
  }
  text_log.PopIndent();

  text_log.PopIndent();

  return;
}

void ON_Font::DumpFreeType(
  ON_TextLog& text_log
) const
{
  const ON_Font* managed_font = this->ManagedFont();
  if (nullptr == managed_font)
    return;
  if (nullptr == managed_font->m_free_type_face)
    return;
  if (this != managed_font && ON_Font::CompareFontCharacteristicsForExperts(true, false, *this, *managed_font))
  {
    text_log.Print("FreeType managed font = <%u>\n", managed_font->RuntimeSerialNumber());
  }
  ON_Font::DumpFreeTypeFace((ON__UINT_PTR)(managed_font->m_free_type_face->m_face), text_log);
}

#endif

