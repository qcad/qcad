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
////////////////////////////////////////////////////////////////

#include "opennurbs.h"
//#include "opennurbs_text.h"
//
//#ifdef RHRICHTEXT
//
//const ON_GlyphItem* ON_GlyphMap::FindGlyph(ON__UINT32 glyph_codepoint)
//{
//  for(int i = 0; i < m_glyphs.Count(); i++)
//  {
//    if(0 == m_glyphs[i])
//      continue;
//    if(m_glyphs[i]->m_codepoint == glyph_codepoint)
//      return m_glyphs[i];
//    if(m_glyphs[i]->m_codepoint > glyph_codepoint)
//      break;
//  }
//  return 0;
//}
//
//void ON_GlyphMap::InsertGlyph(ON_GlyphItem item)
//{
//  int i = 0;
//  for(i = 0; i < m_glyphs.Count(); i++)
//  {
//    if(m_glyphs[i]->m_codepoint == item.m_codepoint)
//      return;
//    if(m_glyphs[i]->m_codepoint > item.m_codepoint)
//      break;
//  }
//  ON_GlyphItem* newitem = ON_GlyphMap::GlyphPool.AllocGlyph();
//  if(0 != newitem)
//  {
//    *newitem = item;
//    if(i < m_glyphs.Count())
//      m_glyphs.Insert(i, newitem);
//    else
//      m_glyphs.Append(newitem);
//  }
//}
//
//void ON_GlyphMap::ReplaceGlyph(ON__UINT32 codepoint, ON_GlyphItem new_item)
//{
//  ON_GlyphItem* gi = const_cast< ON_GlyphItem* >(FindGlyph(codepoint));
//  if(0 != gi)
//    *gi = new_item;
//  else
//    InsertGlyph(new_item);
//}
//
//
//#endif // RHRICHTEXT
