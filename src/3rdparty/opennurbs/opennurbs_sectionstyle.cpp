//
// Copyright (c) 1993-2023 Robert McNeel & Associates. All rights reserved.
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

class ON_SectionStylePrivate
{
public:
  ON_SectionStyle::SectionBackgroundFillMode m_background_fill_mode = ON_SectionStyle::SectionBackgroundFillMode::Viewport;
  ON::SectionFillRule m_fill_rule = ON::SectionFillRule::ClosedCurves;
  int m_hatch_index = ON_UNSET_INT_INDEX; // ON_HatchPattern::Unset.Index();
  double m_hatch_scale = 1.0;
  double m_hatch_rotation = 0.0;
  ON_Color m_background_fill_color = ON_Color::UnsetColor;
  ON_Color m_background_fill_print_color = ON_Color::UnsetColor;
  ON_Color m_boundary_color = ON_Color::UnsetColor;
  ON_Color m_boundary_print_color = ON_Color::UnsetColor;
  ON_Color m_hatch_color = ON_Color::UnsetColor;
  ON_Color m_hatch_print_color = ON_Color::UnsetColor;
  bool m_boundary_visible = true;
  double m_boundary_width_scale = 3.0;
  std::shared_ptr<ON_Linetype> m_custom_linetype;
  bool operator==(const ON_SectionStylePrivate& other) const;
};

static ON_SectionStylePrivate DefaultSectionStylePrivate;

bool ON_SectionStylePrivate::operator==(const ON_SectionStylePrivate& other) const
{
  {
    const ON_Linetype* customThis = m_custom_linetype.get();
    const ON_Linetype* customOther = other.m_custom_linetype.get();
    if (nullptr == customThis && customOther)
      return false;
    if (customThis && nullptr == customOther)
      return false;
    if (customThis && customOther)
    {
      if ((*customThis) != (*customOther))
        return false;
    }
  }

  return m_background_fill_mode == other.m_background_fill_mode &&
    m_fill_rule == other.m_fill_rule &&
    m_hatch_index == other.m_hatch_index &&
    m_hatch_rotation == other.m_hatch_rotation &&
    m_background_fill_color == other.m_background_fill_color &&
    m_background_fill_print_color == other.m_background_fill_print_color &&
    m_boundary_color == other.m_boundary_color &&
    m_boundary_print_color == other.m_boundary_print_color &&
    m_hatch_color == other.m_hatch_color &&
    m_hatch_print_color == other.m_hatch_print_color &&
    m_boundary_visible == other.m_boundary_visible &&
    m_boundary_width_scale == other.m_boundary_width_scale;
}

//////////////////////////////////////////////////////////////////////
// class ON_SectionStyle

ON_OBJECT_IMPLEMENT( ON_SectionStyle, ON_ModelComponent, "6D0DE8B6-598B-4784-B2CA-A42BEB77B521" );

ON_SectionStyle::ON_SectionStyle() ON_NOEXCEPT
  : ON_ModelComponent(ON_ModelComponent::Type::SectionStyle)
{
}

ON_SectionStyle::ON_SectionStyle( const ON_SectionStyle& src )
  : ON_ModelComponent(ON_ModelComponent::Type::SectionStyle,src)
{
  if (src.m_private)
    m_private = new ON_SectionStylePrivate(*src.m_private);
}

ON_SectionStyle::~ON_SectionStyle()
{
  if (m_private)
    delete m_private;
}

ON_SectionStyle& ON_SectionStyle::operator=(const ON_SectionStyle& other)
{
  if (this != &other)
  {
    ON_ModelComponent::operator=(other);
    if (m_private)
    {
      delete m_private;
      m_private = nullptr;
    }
    if (other.m_private)
      m_private = new ON_SectionStylePrivate(*other.m_private);
  }
  return *this;
}
bool ON_SectionStyle::IsValid( ON_TextLog* text_log ) const
{
  if (false == ON_ModelComponent::IsValid(text_log))
    return false;

  // An ON_SectionStyle with an empty name is valid.
  if (BoundaryWidthScale() <= 0)
  {
    if ( text_log )
      text_log->Print("ON_SectionStyle::BoundaryWidthScale <= 0\n");
    return false;
  }

  if (HatchScale() <= 0)
  {
    if (text_log)
      text_log->Print("ON_SectionStyle::SectionHatchScale <= 0\n");
    return false;
  }

  return true;
}

// 12 Aug 2021 S. Baer
// When adding new fields written to 3dm files, always add information to this
// Dump function. Dump is used by the opennurbs file testing framework to
// perform comparisons and is useful for manual comparison in when tests fail.
void ON_SectionStyle::Dump( ON_TextLog& dump ) const
{
  ON_ModelComponent::Dump(dump);

  switch (BackgroundFillMode())
  {
  case ON_SectionStyle::SectionBackgroundFillMode::None:
    dump.Print("No background fill\n");
    break;
  case ON_SectionStyle::SectionBackgroundFillMode::Viewport:
    dump.Print("Viewport background fill\n");
    break;
  case ON_SectionStyle::SectionBackgroundFillMode::SolidColor:
    dump.Print("Solid color background fill\n");
    break;
  }

  if (BoundaryVisible())
    dump.Print("Boundary visible\n");
  else
    dump.Print("Boundary not visible\n");

  dump.Print("Boundary width scale = %g\n", BoundaryWidthScale());
  switch (SectionFillRule())
  {
  case ON::SectionFillRule::ClosedCurves:
    dump.Print("Fill when section makes closed curves\n");
    break;
  case ON::SectionFillRule::SolidObjects:
    dump.Print("Fill only with solid objects\n");
    break;
  }

  dump.Print("Hatch index = %d\n", HatchIndex());
  dump.Print("Hatch scale = %g\n", HatchScale());
  dump.Print("Hatch rotation = %g\n", HatchRotation());

  dump.Print("Boundary color");
  dump.PrintColor(BoundaryColor(false));
  dump.Print("\n");
  dump.Print("Boundary print color");
  dump.PrintColor(BoundaryColor(true));
  dump.Print("\n");
  dump.Print("Background fill color");
  dump.PrintColor(BackgroundFillColor(false));
  dump.Print("\n");
  dump.Print("Background fill print color");
  dump.PrintColor(BackgroundFillColor(true));
  dump.Print("\n");
  dump.Print("Hatch color");
  dump.PrintColor(HatchColor(false));
  dump.Print("\n");
  dump.Print("Hatch print color");
  dump.PrintColor(HatchColor(true));
  dump.Print("\n");
}

// 29 Nov. 2022 S. Baer
// This enum is patterned off of ON_3dmObjectAttributeTypeCode
enum ON_SectionStyleTypeCodes : unsigned char
{
  BackgroundFillMode = 1,
  BackgroundFillColor = 2,
  BoundaryVisible = 3,
  BoundaryColor = 4,
  BoundaryWidthScale = 5,
  SectionFillRule = 6,
  HatchIndex = 7,
  HatchScale = 8,
  HatchRotation = 9,
  HatchColor = 10,
  BoundaryLinetype = 11,

  LastSectionStyleTypeCode = 11
};

bool ON_SectionStyle::Write( ON_BinaryArchive& file) const
{
  bool rc = false;
  {
    const int minor_version = 1;
    if (!file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, 1, minor_version))
      return false;
    for (;;)
    {
      // chunk version 1.0 fields
      if (!file.WriteModelComponentAttributes(*this,ON_ModelComponent::Attributes::BinaryArchiveAttributes))
        break;

      // Only write non-default values in a similar fashion as ON_3dmObjectAttributes
      if (BackgroundFillMode() != ON_SectionStyle::Unset.BackgroundFillMode())
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::BackgroundFillMode; // 1
        if (!file.WriteChar(itemType))
          break;
        unsigned char mode = (unsigned char)BackgroundFillMode();
        if (!file.WriteChar(mode))
          break;
      }
      if (BackgroundFillColor(false).IsSet() || BackgroundFillColor(true).IsSet())
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::BackgroundFillColor; // 2
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteColor(BackgroundFillColor(false)))
          break;
        if (!file.WriteColor(BackgroundFillColor(true)))
          break;
      }
      if (BoundaryVisible() != true)
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::BoundaryVisible; // 3
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteBool(BoundaryVisible()))
          break;
      }
      if (BoundaryColor(false).IsSet() || BoundaryColor(true).IsSet())
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::BoundaryColor; // 4
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteColor(BoundaryColor(false)))
          break;
        if (!file.WriteColor(BoundaryColor(true)))
          break;
      }
      if (fabs(BoundaryWidthScale() - DefaultSectionStylePrivate.m_boundary_width_scale) > ON_EPSILON)
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::BoundaryWidthScale; // 5
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteDouble(BoundaryWidthScale()))
          break;
      }
      if (SectionFillRule() != DefaultSectionStylePrivate.m_fill_rule)
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::SectionFillRule; // 6
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteChar((unsigned char)SectionFillRule()))
          break;
      }
      if (HatchIndex() != DefaultSectionStylePrivate.m_hatch_index)
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::HatchIndex; // 7
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteInt(HatchIndex()))
          break;
      }
      if (fabs(HatchScale() - 1.0) > ON_EPSILON)
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::HatchScale; // 8
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteDouble(HatchScale()))
          break;
      }
      if (HatchRotation() != 0.0)
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::HatchRotation; // 9
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteDouble(HatchRotation()))
          break;
      }
      if (HatchColor(false).IsSet() || HatchColor(true).IsSet())
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::HatchColor; // 10
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteColor(HatchColor(false)))
          break;
        if (!file.WriteColor(HatchColor(true)))
          break;
      }

      // chunk version 1.1 fields
      const ON_Linetype* customLinetype = BoundaryLinetype();
      if (customLinetype != nullptr)
      {
        const unsigned char itemType = ON_SectionStyleTypeCodes::BoundaryLinetype; // 11
        if (!file.WriteChar(itemType))
          break;
        if (!customLinetype->Write(file))
          break;
      }

      // 0 indicates end of new linetype attributes
      const unsigned char attributes_end = 0;
      if (!file.WriteChar(attributes_end))
        break;

      rc = true;
      break;
    }
  }
  if (!file.EndWrite3dmChunk())
    rc = false;
  return rc;
}

static ON_SectionStyle::SectionBackgroundFillMode SectionBackgroundFillModeFromUnsigned(unsigned int i)
{
  if ((unsigned int)ON_SectionStyle::SectionBackgroundFillMode::None == i)
    return ON_SectionStyle::SectionBackgroundFillMode::None;
  if ((unsigned int)ON_SectionStyle::SectionBackgroundFillMode::SolidColor == i)
    return ON_SectionStyle::SectionBackgroundFillMode::SolidColor;

  return ON_SectionStyle::SectionBackgroundFillMode::Viewport;
}

bool ON_SectionStyle::Read( ON_BinaryArchive& file)
{
  *this = ON_SectionStyle();

  int major_version=0;
  int minor_version=0;
  if (!file.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version ))
    return false;

  bool rc = false;

  if ( 1 == major_version )
  {
    for (;;)
    {
      // chunk version 1.0 fields
      unsigned int model_component_attributes_filter = 0;
      if (!file.ReadModelComponentAttributes(*this,&model_component_attributes_filter))
        break;

      unsigned char item_id = 0;
      if (!file.ReadChar(&item_id))
        break;

      if (ON_SectionStyleTypeCodes::BackgroundFillMode == item_id) // 1
      {
        unsigned char c = 0;
        if (!file.ReadChar(&c))
          break;

        SectionBackgroundFillMode mode = SectionBackgroundFillModeFromUnsigned(c);
        SetBackgroundFillMode(mode);
        if (!file.ReadChar(&item_id))
          break;
      }
      if (ON_SectionStyleTypeCodes::BackgroundFillColor == item_id) // 2
      {
        ON_Color c = ON_Color::UnsetColor;
        if (!file.ReadColor(c))
          break;
        SetBackgroundFillColor(c, false);
        if (!file.ReadColor(c))
          break;
        SetBackgroundFillColor(c, true);
        if (!file.ReadChar(&item_id))
          break;
      }
      if (ON_SectionStyleTypeCodes::BoundaryVisible == item_id) // 3
      {
        bool b = true;
        if (!file.ReadBool(&b))
          break;
        SetBoundaryVisible(b);
        if (!file.ReadChar(&item_id))
          break;
      }
      if (ON_SectionStyleTypeCodes::BoundaryColor == item_id) // 4
      {
        ON_Color c = ON_Color::UnsetColor;
        if (!file.ReadColor(c))
          break;
        SetBoundaryColor(c, false);
        if (!file.ReadColor(c))
          break;
        SetBoundaryColor(c, true);
        if (!file.ReadChar(&item_id))
          break;
      }
      if (ON_SectionStyleTypeCodes::BoundaryWidthScale == item_id) // 5
      {
        double scale = 1.0;
        if (!file.ReadDouble(&scale))
          break;
        SetBoundaryWidthScale(scale);
        if (!file.ReadChar(&item_id))
          break;
      }
      if (ON_SectionStyleTypeCodes::SectionFillRule == item_id) // 6
      {
        unsigned char rule = 0;
        if (!file.ReadChar(&rule))
          break;
        SetSectionFillRule(ON::SectionFillRuleFromUnsigned(rule));
        if (!file.ReadChar(&item_id))
          break;
      }
      if (ON_SectionStyleTypeCodes::HatchIndex == item_id) // 7
      {
        int index = 0;
        if (!file.ReadInt(&index))
          break;
        SetHatchIndex(index);
        if (!file.ReadChar(&item_id))
          break;
      }
      if (ON_SectionStyleTypeCodes::HatchScale == item_id) // 8
      {
        double scale = 1.0;
        if (!file.ReadDouble(&scale))
          break;
        SetHatchScale(scale);
        if (!file.ReadChar(&item_id))
          break;
      }
      if (ON_SectionStyleTypeCodes::HatchRotation == item_id) // 9
      {
        double rotation = 0;
        if (!file.ReadDouble(&rotation))
          break;
        SetHatchRotation(rotation);
        if (!file.ReadChar(&item_id))
          break;
      }
      if (ON_SectionStyleTypeCodes::HatchColor == item_id) // 10
      {
        ON_Color c = ON_Color::UnsetColor;
        if (!file.ReadColor(c))
          break;
        SetHatchColor(c, false);
        if (!file.ReadColor(c))
          break;
        SetHatchColor(c, true);
        if (!file.ReadChar(&item_id))
          break;
      }
      if (ON_SectionStyleTypeCodes::BoundaryLinetype == item_id) // 11
      {
        ON_Linetype lt;
        if(!lt.Read(file))
          break;
        SetBoundaryLinetype(lt);
        if (!file.ReadChar(&item_id))
          break;
      }

      if (item_id > ON_SectionStyleTypeCodes::LastSectionStyleTypeCode)
      {
        // we are reading file written with code newer
        // than this code (minor_version > 0)
        item_id = 0;
      }

      rc = true;
      break;
    }
  }

  if ( !file.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool ON_SectionStyle::SectionAttributesEqual(const ON_SectionStyle& other) const
{
  if (nullptr == m_private && nullptr == other.m_private)
    return true;

  if (m_private && other.m_private)
  {
    return (*m_private) == (*other.m_private);
  }

  return false;
}

ON_SectionStyle::SectionBackgroundFillMode ON_SectionStyle::BackgroundFillMode() const
{
  return m_private ? m_private->m_background_fill_mode : DefaultSectionStylePrivate.m_background_fill_mode;
}
void ON_SectionStyle::SetBackgroundFillMode(ON_SectionStyle::SectionBackgroundFillMode mode)
{
  if (BackgroundFillMode() == mode)
    return;
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();
  m_private->m_background_fill_mode = mode;
}

ON_Color ON_SectionStyle::BackgroundFillColor(bool print) const
{
  if (m_private)
    return print ? m_private->m_background_fill_print_color : m_private->m_background_fill_color;
  return ON_Color::UnsetColor;
}
void ON_SectionStyle::SetBackgroundFillColor(const ON_Color& color, bool print)
{
  if (BackgroundFillColor(print) == color)
    return;
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();

  if (print)
    m_private->m_background_fill_print_color = color;
  else
    m_private->m_background_fill_color = color;
}

bool ON_SectionStyle::BoundaryVisible() const
{
  return m_private ? m_private->m_boundary_visible : DefaultSectionStylePrivate.m_boundary_visible;
}
void ON_SectionStyle::SetBoundaryVisible(bool on)
{
  if (BoundaryVisible() == on)
    return;
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();
  m_private->m_boundary_visible = on;
}

ON_Color ON_SectionStyle::BoundaryColor(bool print) const
{
  if (m_private)
    return print ? m_private->m_boundary_print_color : m_private->m_boundary_color;
  return ON_Color::UnsetColor;
}
void ON_SectionStyle::SetBoundaryColor(const ON_Color& color, bool print)
{
  if (BoundaryColor(print) == color)
    return;
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();

  if (print)
    m_private->m_boundary_print_color = color;
  else
    m_private->m_boundary_color = color;
}

double ON_SectionStyle::BoundaryWidthScale() const
{
  return m_private ? m_private->m_boundary_width_scale : DefaultSectionStylePrivate.m_boundary_width_scale;
}
void ON_SectionStyle::SetBoundaryWidthScale(double scale)
{
  if (fabs(BoundaryWidthScale() - scale) < ON_EPSILON)
    return;
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();
  m_private->m_boundary_width_scale = scale;
}

ON::SectionFillRule ON_SectionStyle::SectionFillRule() const
{
  return m_private ? m_private->m_fill_rule : DefaultSectionStylePrivate.m_fill_rule;
}
void ON_SectionStyle::SetSectionFillRule(ON::SectionFillRule rule)
{
  if (SectionFillRule() == rule)
    return;
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();
  m_private->m_fill_rule = rule;
}

int ON_SectionStyle::HatchIndex() const
{
  return m_private ? m_private->m_hatch_index : DefaultSectionStylePrivate.m_hatch_index;
}
void ON_SectionStyle::SetHatchIndex(int index)
{
  if (HatchIndex() == index)
    return;
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();
  m_private->m_hatch_index = index;
}

double ON_SectionStyle::HatchScale() const
{
  return m_private ? m_private->m_hatch_scale : DefaultSectionStylePrivate.m_hatch_scale;
}
void ON_SectionStyle::SetHatchScale(double scale)
{
  if (fabs(HatchScale() - scale) < ON_EPSILON)
    return;
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();
  m_private->m_hatch_scale = scale;
}

double ON_SectionStyle::HatchRotation() const
{
  return m_private ? m_private->m_hatch_rotation : DefaultSectionStylePrivate.m_hatch_rotation;
}
void ON_SectionStyle::SetHatchRotation(double rotation)
{
  if (fabs(HatchRotation() - rotation) < ON_EPSILON)
    return;
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();
  m_private->m_hatch_rotation = rotation;
}

ON_Color ON_SectionStyle::HatchColor(bool print) const
{
  if (m_private)
    return print ? m_private->m_hatch_print_color : m_private->m_hatch_color;
  return ON_Color::UnsetColor;
}
void ON_SectionStyle::SetHatchColor(const ON_Color& color, bool print)
{
  if (HatchColor(print) == color)
    return;
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();

  if (print)
    m_private->m_hatch_print_color = color;
  else
    m_private->m_hatch_color = color;
}

const ON_Linetype* ON_SectionStyle::BoundaryLinetype() const
{
  if (m_private)
    return m_private->m_custom_linetype.get();
  return nullptr;
}
void ON_SectionStyle::SetBoundaryLinetype(const ON_Linetype& linetype)
{
  if (nullptr == m_private)
    m_private = new ON_SectionStylePrivate();

  m_private->m_custom_linetype.reset(new ON_Linetype(linetype));
}
void ON_SectionStyle::RemoveBoundaryLinetype()
{
  if (m_private)
    m_private->m_custom_linetype.reset();
}
