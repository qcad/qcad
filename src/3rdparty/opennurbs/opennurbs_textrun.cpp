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

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

class ON_TextRunPool : public ON_FixedSizePool
{
public:
  static ON_TextRunPool thePool;

private:
  ON_TextRunPool()
  {
    ON_FixedSizePool::Create(sizeof(ON_TextRun), 0, 0);
  } 
  ~ON_TextRunPool() = default;
  ON_TextRunPool(const ON_TextRunPool&) = delete;
  ON_TextRunPool& operator=(const ON_TextRunPool&) = delete;
};

ON_TextRunPool ON_TextRunPool::thePool;

ON_TextRun::ON_TextRun(bool bManagedTextRun)
: m_managed_status(bManagedTextRun ? 1 : 0)
{}

ON_TextRun* ON_TextRun::GetManagedTextRun()
{
  // .NET wrappers manage objects with test runs and .NET GC runs in its own thread,
  // so text run allocation/return using the global ON_TextRunPool::thePool resource
  // must be thread safe.
  void* p = ON_TextRunPool::thePool.ThreadSafeAllocateDirtyElement();
  ON_TextRun* run 
    = (nullptr != p)
    ? new(p)ON_TextRun(true) // always happens in practice
    : new ON_TextRun(false); // could occur if a crashing working thread leaves the pool locked.
  return run;
}

ON_TextRun* ON_TextRun::GetManagedTextRun(
  const ON_TextRun& src
  )
{
  ON_TextRun* run = ON_TextRun::GetManagedTextRun();
  *run = src;
  return run;
}

/*
Description:
  Returns an ON_TextRun to the pool for reuse.
*/
bool ON_TextRun::ReturnManagedTextRun(
  ON_TextRun* run
  )
{
  if ( nullptr == run )
    return true;

  if (1 == run->m_managed_status)
  {
    if (0 == run->m_active_status)
    {
      run->Internal_Destroy();
      run->m_active_status = 1;
      // .NET wrappers manage objects with test runs and .NET GC runs in its own thread,
      // so text run allocation/return using the global ON_TextRunPool::thePool resource
      // must be thread safe.
      ON_TextRunPool::thePool.ThreadSafeReturnElement(run);
      return true;
    }
    ON_ERROR("Attempt to return a managed run that is not active.");
    return false;
  }

  ON_ERROR("Attempt to return a run that is not managed.");
  return false;
}

bool ON_TextRun::IsManagedTextRun() const
{
  return (1 == m_managed_status);
}

bool ON_TextRun::IsActiveManagedTextRun() const
{
  return (1 == m_managed_status && 0 == m_active_status);
}

void ON_TextRunArray::InsertRun(int i, ON_TextRun*& run)
{
  ON_SimpleArray< ON_TextRun* >::Insert(i, run);
  run = nullptr;
}

void ON_TextRunArray::RemoveRun(int i)
{
  ON_SimpleArray< ON_TextRun* >::Remove(i);
}

void ON_TextRunArray::AppendRun(ON_TextRun*& run)
{
  ON_TextRun*& new_run = ON_SimpleArray< ON_TextRun* >::AppendNew();
  new_run = run; // copy pointer, not data
  run = 0;       // null source pointer
}

void ON_TextRunArray::Internal_Destroy()
{
  for (int i = 0; i < m_count; i++)
  {
    ON_TextRun* text_run = m_a[i];
    if (nullptr != text_run)
    {
      m_a[i] = nullptr;
      if (text_run->IsManagedTextRun())
      {
        ON_TextRun::ReturnManagedTextRun(text_run);
      }
      else
      {
        delete text_run;
      }
    }
  }
  Empty();
}

ON_TextRun*const* ON_TextRunArray::Array() const
{
  return (m_count > 0) ? m_a : nullptr;
}


const ON_TextRun* ON_TextRunArray::operator[](int i) const
{
  return (i >= 0 && i < m_count) ? m_a[i] : nullptr;
}

ON_TextRun* ON_TextRunArray::operator[](int i)
{
  return (i >= 0 && i < m_count) ? m_a[i] : nullptr;
}

int ON_TextRunArray::Count() const
{
  return m_count;
}

unsigned int ON_TextRunArray::UnsignedCount() const
{
  return (unsigned int)m_count;
}


void ON_TextRunArray::SetTextHeight(double height)
{
  for (int ri = 0; ri < Count(); ri++)
  {
    ON_TextRun* run = m_a[ri];
    if (nullptr == run)
      continue;
    run->SetTextHeight(height);
  }
}



bool ON_TextRunArray::Get2dCorners(ON_2dPoint corners[4]) const
{
  ON_2dPoint minpt(0.0, 0.0), maxpt(0.0, 0.0);
  bool rc = false;
  for (int ri = 0; ri < Count(); ri++)
  {
    const ON_TextRun* run = m_a[ri];
    if (nullptr == run)
      continue;

    rc = true;
    const ON_2dVector& offset = run->Offset();

    const ON_BoundingBox run_bbox = run->BoundingBox();

    if (minpt.x > run_bbox.m_min.x + offset.x)
      minpt.x = run_bbox.m_min.x + offset.x;
    if (minpt.y > run_bbox.m_min.y + offset.y)
      minpt.y = run_bbox.m_min.y + offset.y;
    if (maxpt.x < run_bbox.m_max.x + offset.x)
      maxpt.x = run_bbox.m_max.x + offset.x;
    if (maxpt.y < run_bbox.m_max.y + offset.y)
      maxpt.y = run_bbox.m_max.y + offset.y;
#if defined(ON_DEBUG) && defined(ON_COMPILER_MSC)
    rc = rc; // good place for a breakpoint
#endif
  }
  corners[0].Set(minpt.x, minpt.y);
  corners[1].Set(maxpt.x, minpt.y);
  corners[2].Set(maxpt.x, maxpt.y);
  corners[3].Set(minpt.x, maxpt.y);
  return rc;
}

void ON_TextRunArray::Internal_CopyFrom(const ON_TextRunArray& src)
{
  SetCount(0);
  Reserve(src.m_count);
  for (int i = 0; i < src.m_count; i++)
  {
    const ON_TextRun* src_text_run = src.m_a[i];
    if ( nullptr != src_text_run )
      AppendNew() = ON_TextRun::GetManagedTextRun(*src_text_run);
  }
}


ON_TextRunArray::~ON_TextRunArray()
{
  Internal_Destroy();
}

ON_TextRunArray& ON_TextRunArray::operator=(const ON_TextRunArray& src)
{
  if (this != &src)
  {
    Internal_Destroy();
    Internal_CopyFrom(src);
  }

  return *this;
}

ON_TextRunArray::ON_TextRunArray(const ON_TextRunArray& src)
{
  Internal_CopyFrom(src);
}

//------------------------------------------------------------

ON_StackedText::~ON_StackedText()
{
  // NOTE WELL:
  //  https://mcneel.myjetbrains.com/youtrack/issue/RH-57616
  //  ON_StackedText::Empty is a global const instance.
  //  Compilers like VS 2019 16.5.0 set the memory for that instance to read-only.
  //  This destructor must not write to memory used by const instances.
  //
  // m_top_run, m_bottom_run, and m_parent_run are set to nullptr to prevent crashes 
  // if in-place classes are referenced after destruction.
  // This is done because bugs are better than crashes in the released product.

  if (nullptr != m_top_run)
  {
    ON_TextRun::ReturnManagedTextRun(m_top_run);
    m_top_run = nullptr;
  }
  if (nullptr != m_bottom_run)
  {
    ON_TextRun::ReturnManagedTextRun(m_bottom_run);
    m_bottom_run = nullptr;
  }
  if (nullptr != m_parent_run)
  {
    m_parent_run = nullptr;
  }
}

ON_StackedText::ON_StackedText(const ON_StackedText& src)
  : ON_StackedText()
{
  if (this != &src)
    *this = src;
}

ON_StackedText& ON_StackedText::operator=(const ON_StackedText& src)
{
  if (&src != this)
  {
    ON_TextRun::ReturnManagedTextRun(m_top_run);
    ON_TextRun::ReturnManagedTextRun(m_bottom_run);
    m_top_run = nullptr;
    m_bottom_run = nullptr;
    if (nullptr != src.m_top_run)
    {
      m_top_run = ON_TextRun::GetManagedTextRun();
      *m_top_run = *src.m_top_run;
    }
    if (nullptr != src.m_bottom_run)
    {
      m_bottom_run = ON_TextRun::GetManagedTextRun();
      *m_bottom_run = *src.m_bottom_run;
    }

    m_separator = src.m_separator;
    m_parent_run = nullptr;
  }
  return *this;
}


//bool ON_StackedText::Write(
//  ON_BinaryArchive& archive
//  ) const
//{
//  return WriteNested(0,archive);
//}
//
//bool ON_StackedText::Read(
//  ON_BinaryArchive& archive
//  )
//{
//  return ReadNested(0,archive);
//}
//
//bool ON_StackedText::WriteNested(
//  unsigned int nested_depth,
//  ON_BinaryArchive& archive
//  ) const
//{
//  if ( nested_depth > 8 )
//    return false;
//
//  if ( !archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0))
//    return false;
//
//  nested_depth++;
//
//  bool rc = false;
//  for (;;)
//  {
//    if (!archive.WriteBool(nullptr != m_top_run))
//      break;
//    if (nullptr != m_top_run)
//    {
//      if (!m_top_run->WriteNested(nested_depth,archive))
//        break;
//    }
//
//    if (!archive.WriteBool(nullptr != m_bottom_run))
//      break;
//    if (nullptr != m_bottom_run)
//    {
//      if (!m_bottom_run->WriteNested(nested_depth,archive))
//        break;
//    }
//
//    unsigned int u = static_cast<unsigned int>(m_separator);
//    if (!archive.WriteInt(u))
//      break;
//
//    rc = true;
//    break;
//  }
//
//  if (!archive.EndWrite3dmChunk())
//    rc = false;
//
//  return rc;
//}
//
//bool ON_StackedText::ReadNested(
//  unsigned int nested_depth,
//  ON_BinaryArchive& archive
//  )
//{
//  *this = ON_StackedText::Empty;
//  if ( nested_depth > 8 )
//    return false;
//
//  int major_version = 0;
//  int minor_version = 0;
//  if ( !archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version))
//    return false;
//
//  nested_depth++;
//
//  bool rc = false;
//  for (;;)
//  {
//    if (1 != major_version)
//    {
//      // This is prototype IO code and increasing major_version is not an error
//      // until we are sure we got it right.
//      rc = true;
//      break;
//    }
//
//    bool b = false;
//    if (!archive.ReadBool(&b))
//      break;
//    if (b)
//    {
//      m_top_run = ON_TextRun::GetManagedTextRun();
//      if (!m_top_run->ReadNested(nested_depth, archive))
//      {
//        ON_TextRun::ReturnManagedTextRun(m_top_run);
//        m_top_run = nullptr;
//        break;
//      }
//    }
//
//    if (!archive.ReadBool(&b))
//      break;
//    if (b)
//    {
//      m_bottom_run = ON_TextRun::GetManagedTextRun();
//      if (!m_bottom_run->ReadNested(nested_depth, archive))
//      {
//        ON_TextRun::ReturnManagedTextRun(m_bottom_run);
//        m_bottom_run = nullptr;
//        break;
//      }
//    }
//
//    unsigned int u = 0;
//    if (!archive.ReadInt(&u))
//      break;
//
//    m_separator = static_cast<wchar_t>(u);
//
//    rc = true;
//    break;
//  }
//
//  if (!archive.EndRead3dmChunk())
//    rc = false;
//
//  return rc;
//}
//
//------------------------------------------------------------

ON_TextRun::~ON_TextRun()
{
  Internal_Destroy();
}

ON_TextRun::ON_TextRun(const ON_TextRun& src)
{
  Internal_CopyFrom(src);
}

void ON_TextRun::Internal_Destroy()
{
  m_managed_font = nullptr;
  if (nullptr != m_codepoints)
  {
    onfree(m_codepoints);
    m_codepoints = nullptr;
  }
  m_text_string.Destroy();
  m_display_string.Destroy();
  if (nullptr != m_stacked_text)
  {
    delete m_stacked_text;
    m_stacked_text = nullptr;
  }
}

void ON_TextRun::Internal_CopyFrom(const ON_TextRun& src)
{
  // "this" is clean.

  m_managed_font     = src.m_managed_font;
  size_t cplen = CodepointCount(src.m_codepoints);
  SetUnicodeString(cplen, src.m_codepoints);

  m_text_string      = src.m_text_string;

  m_display_string   = src.m_display_string;
  
  m_text_stacked          = src.m_text_stacked;
  if (nullptr != src.m_stacked_text)
  {
    m_stacked_text = new ON_StackedText(*src.m_stacked_text);
    m_stacked_text->m_parent_run = this;
  }
  m_color            = src.m_color;
  m_run_type         = src.m_run_type;
  m_direction        = src.m_direction;

  m_run_text_height  = src.m_run_text_height;
  m_offset           = src.m_offset;
  m_advance          = src.m_advance;
  m_bbox             = src.m_bbox;
  m_height_scale     = src.m_height_scale;
  m_stackscale       = src.m_stackscale;

  m_indent       = src.m_indent;
  m_left_margin  = src.m_left_margin;
  m_right_margin = src.m_right_margin;
  m_line_index   = src.m_line_index;
}

ON_TextRun& ON_TextRun::operator=(const ON_TextRun& src)
{
  if ( &src != this )
  {
    Internal_Destroy();
    Internal_CopyFrom(src);
  }
  return *this;
}

void ON_TextRun::Init(
  const ON_Font* managed_font,
  double height,
  double stackscale,
  ON_Color color,
  bool bold,
  bool italic,
  bool underlined,
  bool strikethrough,
  bool deletedisplay)
{
  *this = ON_TextRun::Empty;
  m_color = color;
  m_run_text_height = height;
  m_stackscale = stackscale;

  if (nullptr == managed_font)
    managed_font = &ON_Font::Default;
  if (
    false == managed_font->IsManagedFont()
    || managed_font->IsBoldInQuartet() != bold // NEVER call IsBold() - it doesn't work with light, heavy, black, ... fonts!
    || managed_font->IsItalicInQuartet() != italic
    || managed_font->IsUnderlined() != underlined
    || managed_font->IsStrikethrough() != strikethrough
    )
  {
    // Dale Lear - March 2021 - RH-62974
    // There are multiple places in the text run, rich text parsing, and Rhino UI code
    // that need find a font from rich text properties.
    // They must all do it the same way. If for some reason, you must change this call,
    // please take the time to create a single function that replaces this call, search
    // for all the places ON_Font::FontFromRichTextProperties is called in
    //  src4/rhino/... 
    //  opennurbs_textrun.cpp
    //  opennurbs_textiterator.cpp
    // and replace every call to ON_Font::FontFromRichTextProperties with a call to
    // your new function.
    managed_font = ON_Font::FontFromRichTextProperties(
      ON_Font::RichTextFontName(managed_font, true),
      bold,
      italic,
      underlined,
      strikethrough);
  }
  m_managed_font = managed_font;
}

bool ON_TextRun::IsText() const
{
  return Type() == RunType::kText;
}
bool ON_TextRun::IsNewline() const
{
  return Type() == RunType::kNewline;
}
bool ON_TextRun::IsColumn() const
{
  return Type() == RunType::kColumn;
}

static bool RunIsInvalid()
{
  return false;
}

bool ON_TextRun::IsValid() const
{
  switch (Type())
  {
  case RunType::kField:
  case RunType::kText:
  {
    Stacked is_stacked = IsStacked();
    if ( IsStacked() != Stacked::kStacked &&
       (nullptr == m_codepoints ||
        0 == ON_TextRun::CodepointCount(m_codepoints)) &&
       !m_text_string.IsEmpty())
      return RunIsInvalid();

    if (!(m_run_text_height > 0.0))
      return RunIsInvalid();

    switch (is_stacked)
    {
    case Stacked::kNone:
    {
      if (nullptr != m_stacked_text)
        return RunIsInvalid();
      break;
    }
    case Stacked::kStacked:
    {
      if (nullptr == m_stacked_text)
        return RunIsInvalid();
      if (nullptr == m_stacked_text->m_top_run)
        return RunIsInvalid();
      if (!m_stacked_text->m_top_run->IsValid())
        return RunIsInvalid();
      if (nullptr == m_stacked_text->m_bottom_run)
        return RunIsInvalid();
      if (!m_stacked_text->m_bottom_run->IsValid())
        return RunIsInvalid();
      break;
    }
    case Stacked::kTop:
    {
      if (nullptr == m_stacked_text)
        return RunIsInvalid();
      if (nullptr == m_stacked_text->m_top_run)
        return RunIsInvalid();
      if (!m_stacked_text->m_top_run->IsValid())
        return RunIsInvalid();
      break;
    }
    case Stacked::kBottom:
    {
      if (nullptr == m_stacked_text)
        return RunIsInvalid();
      if (nullptr == m_stacked_text->m_bottom_run)
        return RunIsInvalid();
      if (!m_stacked_text->m_bottom_run->IsValid())
        return RunIsInvalid();
      break;
    }
    }
    break;
  }
  case RunType::kNewline:
  case RunType::kParagraph:
  case RunType::kSoftreturn:
  {
    if (!(m_run_text_height > 0.0))
      return RunIsInvalid();
    break;
  }
  default:
    return RunIsInvalid();
  }
  return true;
}

void ON_TextRun::Internal_ContentChanged() const
{
  m_text_run_hash = ON_SHA1_Hash::ZeroDigest;
  m_text_run_display_hash = ON_SHA1_Hash::ZeroDigest;
}

void ON_TextRun::SetType(ON_TextRun::RunType type)
{
  //if (type == ON_TextRun::RunType::kField)
  //  type = type;
  if (m_run_type != type)
  {
    Internal_ContentChanged();
    m_run_type = type;
  }
}

ON_TextRun::RunType ON_TextRun::Type() const
{
  //if (m_run_type == ON_TextRun::RunType::kField)
  //  int i = 2;
  return m_run_type;
}

ON_TextRun::RunDirection ON_TextRun::FlowDirection() const
{
  return m_direction;
}

void ON_TextRun::SetDisplayString(const wchar_t* str)
{
  if (str != m_display_string.Array())
  {
    ON_wString local(str);
    if (m_display_string != local)
    {
      Internal_ContentChanged();
      m_display_string = local;
    }
  }
}

const wchar_t* ON_TextRun::DisplayString() const
{
  if (m_display_string.IsEmpty())
    return TextString();
  else
    return m_display_string.Array();
}

const wchar_t* ON_TextRun::TextString() const
{
  if (m_text_string.IsEmpty())
  {
    if (nullptr != m_codepoints)
    {
      bool b = sizeof(wchar_t) == sizeof(m_codepoints[0]);
      if (b)
        return (const wchar_t*)m_codepoints;

      size_t cplen = ON_TextRun::CodepointCount(m_codepoints);
      if (0 < cplen) 
        ON_TextContext::ConvertCodepointsToString((int)cplen, m_codepoints, m_text_string);
    }
  }
  return m_text_string.Array();
}

ON_TextRun::Stacked ON_TextRun::IsStacked() const
{
  return m_text_stacked;
}

void ON_TextRun::SetStacked(Stacked stacked)
{
  if (m_text_stacked != stacked)
  {
    Internal_ContentChanged();
    m_text_stacked = stacked;
  }
}

void ON_TextRun::SetStackedOff()
{
  SetStacked(Stacked::kNone);
}

double ON_TextRun::TextHeight() const
{
  return m_run_text_height;
}

void ON_TextRun::SetTextHeight(double h)
{
  if(h > 0.0)
  {
    if (!(m_run_text_height == h))
    {
      Internal_ContentChanged();
      m_run_text_height = h;
    }
    if (!(m_height_scale == -1.0))
    {
      Internal_ContentChanged();
      m_height_scale = -1.0;
    }
  }
}

ON_Color ON_TextRun::Color() const
{
  return m_color;
}

void ON_TextRun::SetColor(ON_Color color)
{
  if (m_color != color)
  {
    Internal_ContentChanged();
    m_color = color;
  }
}

void ON_TextRun::SetFont(const ON_Font* font)
{
  const ON_Font* managed_font
    = (nullptr != font)
    ? font->ManagedFont()
    : nullptr;
  if (m_managed_font != managed_font)
  {
    Internal_ContentChanged();
    m_managed_font = managed_font;
  }
  if (!(m_height_scale == -1.0))
  {
    Internal_ContentChanged();
    m_height_scale = -1.0;
  }
}

const ON_Font* ON_TextRun::Font() const
{
  return m_managed_font;
}

const ON_BoundingBox& ON_TextRun::BoundingBox() const
{
  return m_bbox;
};

void ON_TextRun::SetBoundingBox(ON_2dPoint pmin, ON_2dPoint pmax)
{
  // If this function is removed and bounding box lazy evaluation
  // is used, then remove m_bbox from the SHA1 hash calculation.
  if (
    !(m_bbox.m_min.x == pmin.x && m_bbox.m_min.y == pmin.y && 0.0 == m_bbox.m_min.z
      && m_bbox.m_max.x == pmax.x  && m_bbox.m_max.y == pmax.y && 0.0 == m_bbox.m_max.z
      )
    )
  {
    Internal_ContentChanged();
    m_bbox.m_min.x = pmin.x;
    m_bbox.m_min.y = pmin.y;
    m_bbox.m_min.z = 0.0;
    m_bbox.m_max.x = pmax.x;
    m_bbox.m_max.y = pmax.y;
    m_bbox.m_max.z = 0.0;
  }
}

const ON_2dVector& ON_TextRun::Offset() const
{
  return m_offset;
}

void ON_TextRun::SetOffset(ON_2dVector offset)
{
  if (!(m_offset == offset))
  {
    Internal_ContentChanged();
    m_offset = offset;
  }
}

const ON_2dVector& ON_TextRun::Advance() const
{
  return m_advance;
}

void ON_TextRun::SetAdvance(ON_2dVector advance)
{
  if (m_advance != advance)
  {
    Internal_ContentChanged();
    m_advance = advance;
  }
}


ON_SHA1_Hash ON_TextRun::TextRunContentHash() const
{
  return TextRunContentHash(true);
}


ON_SHA1_Hash ON_TextRun::TextRunContentHash(
  bool bEvaluateFields
) const
{
  if (ON_SHA1_Hash::ZeroDigest == m_text_run_hash)
  {
    ON_SHA1 sha1;
    
    const bool bIsStacked = (
      ON_TextRun::Stacked::kStacked == IsStacked() 
      && nullptr != m_stacked_text
      && this != m_stacked_text->m_top_run
      && this != m_stacked_text->m_bottom_run
      && (nullptr != m_stacked_text->m_top_run || nullptr != m_stacked_text->m_bottom_run)
      );

    if (nullptr != m_managed_font)
    {
      sha1.AccumulateSubHash(m_managed_font->FontCharacteristicsHash());
    }

    TextString(); // insure m_text_string is set.
    sha1.AccumulateString(m_text_string);

    sha1.AccumulateDouble(m_run_text_height);
    if ( m_height_scale > 0.0 )
      sha1.AccumulateDouble(m_height_scale);
    sha1.AccumulateDouble(m_stackscale);
    sha1.Accumulate2dVector(m_advance);
    sha1.Accumulate2dVector(m_offset);
    sha1.AccumulateDouble(m_indent);
    sha1.AccumulateDouble(m_left_margin);
    sha1.AccumulateDouble(m_right_margin);
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_color));
    sha1.AccumulateUnsigned8(static_cast<unsigned char>(m_text_stacked));
    sha1.AccumulateUnsigned8(static_cast<unsigned char>(m_run_type));
    sha1.AccumulateUnsigned8(static_cast<unsigned char>(m_direction));
    if ( m_bbox.IsValid() )
      sha1.AccumulateBoundingBox(m_bbox);

    if( bIsStacked )
    {
      sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_stacked_text->m_separator));
      if (nullptr != m_stacked_text->m_top_run)
      {
        sha1.AccumulateSubHash(m_stacked_text->m_top_run->TextRunContentHash(false));
      }
      if (nullptr != m_stacked_text->m_bottom_run)
      {
        sha1.AccumulateSubHash(m_stacked_text->m_bottom_run->TextRunContentHash(false));
      }
    }

    m_text_run_hash = sha1.Hash();
    if (m_display_string.IsEmpty())
    {
      m_text_run_display_hash = m_text_run_hash;
    }
    else
    {
      sha1.AccumulateString(m_display_string);
      if( bIsStacked )
      {
        if (nullptr != m_stacked_text->m_top_run && m_stacked_text->m_top_run->m_display_string.IsNotEmpty() )
        {
          sha1.AccumulateString(m_stacked_text->m_top_run->m_display_string);
        }
        if (nullptr != m_stacked_text->m_bottom_run && m_stacked_text->m_bottom_run->m_display_string.IsNotEmpty() )
        {
          sha1.AccumulateString(m_stacked_text->m_bottom_run->m_display_string);
        }
      }
      m_text_run_display_hash = sha1.Hash();
    }
  }

  return
    bEvaluateFields
    ? m_text_run_display_hash
    : m_text_run_hash;
}

void ON_TextRun::SetStackFractionHeight(double stackscale)
{
  if (ON_SQRT_EPSILON < stackscale && 10000.0 > stackscale)
  {
    if (!(m_stackscale == stackscale))
    {
      Internal_ContentChanged();
      m_stackscale = stackscale;
    }
  }
}

double ON_TextRun::StackHeightFraction() const
{
  return m_stackscale;
}

//static 
double ON_TextRun::DefaultStackFractionHeight()
{
  return 0.7;
}

void ON_TextRun::Get2dCorners(ON_2dPoint corners[4]) const
{
  const ON_2dVector& offset = Offset();
  corners[0].Set(m_bbox.m_min.x + offset.x, m_bbox.m_min.y + offset.y);
  corners[1].Set(m_bbox.m_max.x + offset.x, m_bbox.m_min.y + offset.y);
  corners[2].Set(m_bbox.m_max.x + offset.x, m_bbox.m_max.y + offset.y);
  corners[3].Set(m_bbox.m_min.x + offset.x, m_bbox.m_max.y + offset.y);
}


// This returns the scale of run.m_height(the wcs text height) / HeightOfI. to
// convert from font native units to model units.
// It doesn't take into account anything about annotation scaling
double ON_TextRun::HeightScale(const ON_Font* font) const
{
  if(m_height_scale <= 0.0)
  {
    if (0 != font)
      const_cast< ON_TextRun* >(this)->m_height_scale = font->FontMetrics().GlyphScale(m_run_text_height);
  }
  return m_height_scale;
}

// Does not include terminating 0
// static
size_t ON_TextRun::CodepointCount(const ON__UINT32* cp)
{
  if (0 == cp)
    return 0;
  size_t i = 0;
  while (0 != cp[i])
    i++;
  return i;
}

const ON__UINT32* ON_TextRun::UnicodeString() const
{
  return m_codepoints;
}


// count doesn't include terminating 0, but a terminating 0 is added
void ON_TextRun::SetUnicodeString(size_t count, const ON__UINT32* cp)
{
  m_bbox.Destroy();
  m_text_string.Empty();
  m_display_string.Empty();
  SetUnicodeString(m_codepoints, count, cp);
#ifdef _DEBUG
  TextString();
#endif
}

void ON_TextRun::SetUnicodeString(ON__UINT32*& dest, size_t count, const ON__UINT32* cp)
{
  if (0 == count || 0 == cp)
  {
    if (0 != dest)
    {
      onfree(dest);
      dest = nullptr;
    }
    return;
  }
  ON__UINT32* newcp = (ON__UINT32*)onrealloc(dest, (count + 1)*sizeof(ON__UINT32));
  if(0 == newcp)
  {
    onfree(dest);
    dest = nullptr;
  }
  else
  {
    dest = newcp;
    memcpy(dest, cp, count*sizeof(ON__UINT32));
    dest[count] = 0; // add terminating zero
  }
}

int ON_TextRun::WrapTextRun(
  int call_count,         // recursion depth
  int start_char_offset,  // char offset in cp array
  double wrapwidth,       // max linewidth
  double& y_offset,       // y offset from input run from previously added soft returns
  double& linewidth,      // linewidth so far
  ON_TextRunArray& newruns// new runs made by wrapping
) const
{
  int new_count = 0;

  if (500 < call_count)
  {
    ON_ERROR("WrapTextRun: Recursion too deep.");
    return 0;
  }
  if (0 > start_char_offset)
  {
    ON_ERROR("WrapTextRun: String start offset < 0.");
    start_char_offset = 0;
  }

  if (0.0 > linewidth)
  {
    ON_ERROR("WrapTextRun: Linewidtht < 0.");
    linewidth = 0.0;
  }

  const wchar_t* display_string = DisplayString();

  size_t wcscount = 0;
  if (nullptr != display_string)
    wcscount = wcslen(display_string);

  const ON_Font* font = Font();
  if (nullptr == font)
    return 0;
  double height_scale = HeightScale(font); // Font units to world units

  ON_SimpleArray< const ON_FontGlyph*> glyph_list;
  ON_TextBox text_box;

  ON_FontGlyph::GetGlyphList(display_string, font, ON_NextLine, glyph_list, text_box);
  int glyph_count = glyph_list.Count();

  const ON_FontGlyph* Aglyph = font->CodePointGlyph((ON__UINT32)L'A');
  if (nullptr == Aglyph)
    return 0;
  const ON_TextBox Aglyph_box = Aglyph->GlyphBox();
  double Awidth = Aglyph_box.m_advance.i * height_scale;
  // height scale is ~1e-3 so floor() will pretty much always make this value 0
  // when text height is much less than 1, so this is a test for a NAN result
  if (floor(Awidth) < 0.0)
  {
    ON_ERROR("Font height scale * width of 'A' is less than 0\n");
    return 0;
  }
  if (!(Awidth > 0.0 && wrapwidth >= Awidth))
    return 0;

#pragma region Run Width
  double runwidth = 0.0;  // run width without trailing spaces
  //double runwidth0 = 0.0; // run width including trailing spaces
  if (0 == start_char_offset)  // using the whole run
  {
    //runwidth = Advance().x;
    runwidth = text_box.m_advance.i * height_scale;
  }
  else // Part of the run has already been picked off and added to the previous line
  {
    // Find width of remaining characters
    for (int ci = start_char_offset; ci < wcscount && ci < glyph_count; ci++)
    {
      const ON_FontGlyph* gi = glyph_list[ci];

      if (nullptr != gi)
      {
        const ON_TextBox glyph_box = gi->GlyphBox();
        double charwidth = glyph_box.m_advance.i * height_scale;
        runwidth += charwidth;
      }
    }
  }

  if (0.0 > runwidth)
    runwidth = 0.0;
#pragma endregion Run Width

#pragma region Whole Run
  wchar_t* temp_display_str = (wchar_t*)onmalloc((wcscount + 1) * sizeof(wchar_t));
  if (runwidth + linewidth <= wrapwidth || 2 > wcscount)
  {
    // Adding this entire run won't go past wrap width
    // or the run has only 0 or 1 character and can't be wrapped
    ON_TextRun* newrun = ON_TextRun::GetManagedTextRun();
    if (nullptr != newrun)
    {
      *newrun = *this;
      if (Type() == ON_TextRun::RunType::kNewline ||
        Type() == ON_TextRun::RunType::kParagraph ||
        Type() == ON_TextRun::RunType::kSoftreturn)
        linewidth = 0.0;
      else
      {
        if (0 != start_char_offset)
        {
          wcsncpy(temp_display_str, display_string + start_char_offset, wcscount - start_char_offset);
          temp_display_str[wcscount - start_char_offset] = 0;
          newrun->SetDisplayString(temp_display_str);
        }
        linewidth += runwidth;
      }
      newruns.AppendRun(newrun);
      onfree(temp_display_str);
      return 1; // 1 new run was added
    }
  }
#pragma endregion Whole Run

  // Find what part of the run will fit
  bool found_space = false;
  int last_space = -1;
  int run_length = 0;
  double curwidth = 0.0;
  double linefeedheight = font->FontMetrics().LineSpace() * height_scale;

  int sp_count = 0;
  for (int ci = start_char_offset; ci < (int)wcscount; ci++)
  {
    if ((ci + 1) < wcscount &&
      display_string[ci] >= 0xD800 && display_string[ci] < 0xDC00 &&
      display_string[ci + 1] >= 0xDC00 && display_string[ci + 1] < 0xE000)
    {
      sp_count++;
      continue;
    }

    int gi = ci - sp_count;
    if (gi >= glyph_count)
      break;

    const ON_FontGlyph* glyph = glyph_list[gi];
    if (nullptr != glyph)
    {
      const ON_TextBox glyph_box = glyph->GlyphBox();
      curwidth += glyph_box.m_advance.i * height_scale;
      run_length++;

      if (linewidth + curwidth > wrapwidth) // reached wrapping width
      {
        if (found_space) // store run up to last space
          run_length = last_space - start_char_offset + 1;
        else if (0.0 < linewidth) // A line is already started
          run_length = 0;
        else  // no space yet - store run up to this char position
          run_length = ci - start_char_offset;

        if (0 < run_length)
        {
          ON_TextRun* newrun = ON_TextRun::GetManagedTextRun();  // make a new run
          if (nullptr != newrun)
          {
            *newrun = *this;
            wcsncpy(temp_display_str, display_string + start_char_offset, run_length);
            temp_display_str[run_length] = 0;
            newrun->SetDisplayString(temp_display_str);
            newrun->SetOffset(ON_2dVector(0.0, y_offset + Offset().y));
            newruns.AppendRun(newrun);
          }
        }
        // add a soft return
        ON_TextRun* lfrun = ON_TextRun::GetManagedTextRun();
        if (nullptr != lfrun)
        {
          lfrun->SetFont(Font());
          lfrun->SetType(ON_TextRun::RunType::kSoftreturn);
          lfrun->SetTextHeight(this->TextHeight());
          newruns.AppendRun(lfrun);

          // Starting a new line now
          linewidth = 0.0;
          curwidth = 0.0;
          y_offset -= linefeedheight;
        }

        int wrapcount = WrapTextRun(call_count + 1, run_length + start_char_offset, wrapwidth, y_offset, linewidth, newruns);
        onfree(temp_display_str);
        return new_count + wrapcount;
      }
      if (iswspace(display_string[ci]))
      {
        found_space = true;
        last_space = ci;
      }
    }
  }

  ON_TextRun* newrun = ON_TextRun::GetManagedTextRun();  // make a new run
  if (nullptr != newrun)
  {
    *newrun = *this;
    wcsncpy(temp_display_str, display_string + start_char_offset, run_length);
    temp_display_str[run_length] = 0;
    newrun->SetOffset(ON_2dVector(0.0, y_offset + Offset().y));
    newruns.AppendRun(newrun);
    new_count += 1;
  }
  onfree(temp_display_str);
  return new_count;
}

ON_StackedText::StackStyle ON_StackedText::StackStyleFromUnsigned(
  unsigned int stack_style_as_unsigned
)
{
  switch (stack_style_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_StackedText::StackStyle::kUnset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_StackedText::StackStyle::kHorizontalToScreen);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_StackedText::StackStyle::kSlanted);
  }
  ON_ERROR("stack_style_as_unsigned parameter is not valid");
  return ON_StackedText::StackStyle::kUnset;
}

ON_TextRun::RunType ON_TextRun::RunTypeFromUnsigned(
  unsigned int run_type_as_unsigned
  )
{
  switch (run_type_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kNone);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kText);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kNewline);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kSoftreturn);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kParagraph);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kColumn);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kField);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kFieldValue);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kFontdef);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kHeader);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunType::kFonttbl);
  }
  ON_ERROR("run_type_as_unsigned parameter is not valid");
  return ON_TextRun::RunType::kNone;
}

enum class Stacked : unsigned char
{
  kNone     = 0,
  kStacked  = 1,
  kTop      = 2,
  kBottom   = 3
};

ON_TextRun::Stacked ON_TextRun::StackedFromUnsigned(
  unsigned int stacked_as_unsigned
  )
{
  switch (stacked_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::Stacked::kNone);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::Stacked::kStacked);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::Stacked::kTop);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::Stacked::kBottom);
  }
  ON_ERROR("stacked_as_unsigned parameter is not valid");
  return ON_TextRun::Stacked::kNone;
}

enum class RunDirection : unsigned char
{
  kLtR      = 0,
  kRtL      = 1,
};
  
ON_TextRun::RunDirection ON_TextRun::RunDirectionFromUnsigned(
  unsigned int run_direction_as_unsigned
  )
{
  switch (run_direction_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunDirection::kLtR);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_TextRun::RunDirection::kRtL);
  }
  ON_ERROR("run_direction_as_unsigned parameter is not valid");
  return ON_TextRun::RunDirection::kLtR;
}

//bool ON_TextRun::Write(
//  ON_BinaryArchive& archive
//  ) const
//{
//  return WriteNested(0,archive);
//}
//
//bool ON_TextRun::Read(
//  ON_BinaryArchive& archive
//  )
//{
//  return ReadNested(0,archive);
//}
//
//bool ON_TextRun::WriteNested(
//  unsigned int nested_depth,
//  ON_BinaryArchive& archive
//  ) const
//{
//  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0))
//    return false;
//  bool rc = false;
//  for (;;)
//  {
//    if (!archive.WriteUuid(m_Font_id))
//      break;
//
//    
//    const ON__UINT32* cp1 = m_codepoints;
//    if (nullptr != cp1)
//    {
//      while ( 0 != *cp1 )
//        cp1++;
//    }
//
//    unsigned int count = static_cast<unsigned int>(cp1 - m_codepoints);
//    if (!archive.WriteInt(count))
//      break;
//    if (!archive.WriteInt(count,m_codepoints))
//      break;
//    
//    unsigned int u = static_cast<unsigned int>(m_stacked);
//    if (!archive.WriteInt(u))
//      break;
//
//    if (!archive.WriteBool(nullptr!=m_stacked_text))
//      break;
//    if (nullptr != m_stacked_text)
//    {
//      // nested_depth is correct.
//      // m_stacked_text will increment nested_depth if it calls back to ON_TextRun::WriteNested().
//      if (!m_stacked_text->WriteNested(nested_depth,archive))
//        break;
//    }
//
//    if (!archive.WriteColor(m_color))
//      break;
//
//    u = static_cast<unsigned int>(m_type);
//    if (!archive.WriteInt(u))
//      break;
//
//    u = static_cast<unsigned int>(m_direction);
//    if (!archive.WriteInt(u))
//      break;
//
//    if (!archive.WriteDouble(m_height))
//      break;
//    if (!archive.WriteVector(m_offset))
//      break;
//    if (!archive.WriteVector(m_advance))
//      break;
//    if (!archive.WriteBoundingBox(m_bbox))
//      break;
//    if (!archive.WriteDouble(m_height_scale))
//      break;
//    if (!archive.WriteDouble(m_indent))
//      break;
//    if (!archive.WriteDouble(m_left_margin))
//      break;
//    if (!archive.WriteDouble(m_right_margin))
//      break;
//    if (!archive.WriteInt(m_line_index))
//      break;
//
//    rc = true;
//    break;
//  }
//  if (!archive.EndWrite3dmChunk())
//    rc = false;
//  return rc;
//}
//
//bool ON_TextRun::ReadNested(
//  unsigned int nested_depth,
//  ON_BinaryArchive& archive
//  )
//{
//  *this = ON_TextRun::Empty;
//  if ( nested_depth > 8 )
//    return false;
//
//  int major_version = 0;
//  int minor_version = 0;
//  if ( !archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version))
//    return false;
//
//  nested_depth++;
//
//  bool rc = false;
//  for (;;)
//  {
//    if (1 != major_version)
//    {
//      // This is prototype IO code and increasing major_version is not an error
//      // until we are sure we got it right.
//      rc = true;
//      break;
//    }
//
//    if (!archive.ReadUuid(m_Font_id))
//      break;
//
//    unsigned int count = 0;
//    if (!archive.ReadInt(&count))
//      break;
//    if (count > 0)
//    {
//      m_codepoints = (ON__UINT32*)onmalloc( (count + 1)*sizeof(m_codepoints[0]));
//      if ( nullptr == m_codepoints )
//        break;
//      m_codepoints[count] = 0;
//      if (!archive.ReadInt(count,m_codepoints))
//        break;
//    }
//
//    unsigned int u = static_cast<unsigned int>(m_stacked);
//    if (!archive.WriteInt(u))
//      break;
//
//    if (!archive.WriteBool(nullptr!=m_stacked_text))
//      break;
//    if (nullptr != m_stacked_text)
//    {
//      // nested_depth is correct.
//      // m_stacked_text will increment nested_depth if it calls back to ON_TextRun::WriteNested().
//      if (!m_stacked_text->WriteNested(nested_depth,archive))
//        break;
//    }
//
//    if (!archive.WriteColor(m_color))
//      break;
//
//    u = static_cast<unsigned int>(m_type);
//    if (!archive.WriteInt(u))
//      break;
//
//    u = static_cast<unsigned int>(m_direction);
//    if (!archive.WriteInt(u))
//      break;
//
//    if (!archive.WriteDouble(m_height))
//      break;
//    if (!archive.WriteVector(m_offset))
//      break;
//    if (!archive.WriteVector(m_advance))
//      break;
//    if (!archive.WriteBoundingBox(m_bbox))
//      break;
//    if (!archive.WriteDouble(m_height_scale))
//      break;
//    if (!archive.WriteDouble(m_indent))
//      break;
//    if (!archive.WriteDouble(m_left_margin))
//      break;
//    if (!archive.WriteDouble(m_right_margin))
//      break;
//    if (!archive.WriteInt(m_line_index))
//      break;
//
//    rc = true;
//    break;
//  }
//
//  if (!archive.EndRead3dmChunk())
//    rc = false;
//
//  return rc;
//}

//------------------------------------------------------------


