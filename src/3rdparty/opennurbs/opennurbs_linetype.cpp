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

class ON_LinetypePrivate
{
public:
  ON_SimpleArray<ON_LinetypeSegment> m_segments;
  ON_SimpleArray<ON_2dPoint> m_taper_points;
  bool m_always_model_distances = false;
};

bool ON_IsHairlinePrintWidth(double width_mm)
{
  if(width_mm > 0.0 && width_mm < 0.001)
    return true;

  return false;
}

double ON_HairlinePrintWidth()
{
  return 0.0001;
}


//////////////////////////////////////////////////////////////////////
// class ON_LinetypeSegment
bool ON_LinetypeSegment::operator==( const ON_LinetypeSegment& src) const
{
  return ( m_length == src.m_length && m_seg_type == src.m_seg_type);
}

bool ON_LinetypeSegment::operator!=( const ON_LinetypeSegment& src) const
{
  return ( m_length != src.m_length || m_seg_type != src.m_seg_type);
}

ON_LinetypeSegment::eSegType ON_LinetypeSegment::SegmentTypeFromUnsigned(
  unsigned int segment_type_as_unsigned
  )
{
  switch (segment_type_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_LinetypeSegment::eSegType::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_LinetypeSegment::eSegType::stLine);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_LinetypeSegment::eSegType::stSpace);
  }
  ON_ERROR("Invalid segment_type_as_unsigned value.");
  return ON_LinetypeSegment::eSegType::stLine;
}

ON_LinetypeSegment::ON_LinetypeSegment(
  double segment_length,
  ON_LinetypeSegment::eSegType segment_type
  )
  : m_length(segment_length)
  , m_seg_type(segment_type)
{}

void ON_LinetypeSegment::Dump( ON_TextLog& dump) const
{
  switch( m_seg_type)
  {
  case ON_LinetypeSegment::eSegType::stLine:
    dump.Print( "Segment type = Line: %g\n", m_length);
    break;
  case ON_LinetypeSegment::eSegType::stSpace:
    dump.Print( "Segment type = Space: %g\n", m_length);
    break;
  case ON_LinetypeSegment::eSegType::Unset:
    break;
  }
}

//////////////////////////////////////////////////////////////////////
// class ON_Linetype

ON_OBJECT_IMPLEMENT( ON_Linetype, ON_ModelComponent, "26F10A24-7D13-4f05-8FDA-8E364DAF8EA6" );

const ON_Linetype* ON_Linetype::FromModelComponentRef(
  const class ON_ModelComponentReference& model_component_reference,
  const ON_Linetype* none_return_value
  )
{
  const ON_Linetype* p = ON_Linetype::Cast(model_component_reference.ModelComponent());
  return (nullptr != p) ? p : none_return_value;
}


ON_Linetype::ON_Linetype() ON_NOEXCEPT
  : ON_ModelComponent(ON_ModelComponent::Type::LinePattern)
{
  m_private = new ON_LinetypePrivate();
}

ON_Linetype::ON_Linetype( const ON_Linetype& src )
  : ON_ModelComponent(ON_ModelComponent::Type::LinePattern,src)
  , m_is_set_bits(src.m_is_set_bits)
  , m_is_locked_bits(src.m_is_locked_bits)
  , m_cap_style(src.m_cap_style)
  , m_join_style(src.m_join_style)
  , m_width(src.m_width)
  , m_width_units(src.m_width_units)
{
  m_private = new ON_LinetypePrivate(*src.m_private);
}

ON_Linetype::~ON_Linetype()
{
  delete m_private;
}

ON_Linetype& ON_Linetype::operator=(const ON_Linetype& other)
{
  if (this != &other)
  {
    ON_ModelComponent::operator=(other);
    m_is_set_bits = other.m_is_set_bits;
    m_is_locked_bits = other.m_is_locked_bits;
    m_cap_style = other.m_cap_style;
    m_join_style = other.m_join_style;
    m_width = other.m_width;
    m_width_units = other.m_width_units;
    *m_private = *other.m_private;
  }
  return *this;
}

ON_Linetype* ON_Linetype::DuplicateLinetype() const
{
  ON_Linetype* rc = new ON_Linetype(*this);
  if (rc)
  {
    rc->ClearName();
    rc->ClearId();
    rc->m_is_locked_bits = 0;
  }
  return rc;
}


bool ON_Linetype::IsValid( ON_TextLog* text_log ) const
{
  if (false == ON_ModelComponent::IsValid(text_log))
    return false;

  // An ON_Linetype with an empty name is valid.

  const ON_SimpleArray<ON_LinetypeSegment>& segments = m_private->m_segments;
  int count = segments.Count();
  if ( count < 1 )
  {
    if ( text_log )
      text_log->Print("ON_Linetype m_segments.Count() = 0\n");
    return false;
  }

  if ( 1 == count )
  {
    if ( segments[0].m_length <= 0.0  )
    {
      if ( text_log )
        text_log->Print("ON_Linetype bogus single segment linetype - length <= 0.0 (it must be > 0)\n");
      return false;
    }

    if ( ON_LinetypeSegment::eSegType::stLine != segments[0].m_seg_type )
    {
      if ( text_log )
        text_log->Print("ON_Linetype bogus single segment linetype - type != stLine\n");
      return false;
    }
  }
  else
  {
    for (int i = 0; i < count; i++ )
    {
      if ( segments[i].m_length < 0.0 )
      {
        if ( text_log )
          text_log->Print("ON_Linetype segment has negative length.\n");
        return false;
      }

      if ( ON_LinetypeSegment::eSegType::stLine != segments[i].m_seg_type && ON_LinetypeSegment::eSegType::stSpace != segments[i].m_seg_type )
      {
        if ( text_log )
          text_log->Print("ON_Linetype segment has invalid m_seg_type.\n");
        return false;
      }

      if ( i )
      {
        if ( segments[i].m_seg_type == segments[i-1].m_seg_type )
        {
          if ( text_log )
            text_log->Print("ON_Linetype consecutive segments have same type.\n");
          return false;
        }

        if ( 0.0 == segments[i].m_length && 0.0 == segments[i-1].m_length )
        {
          if ( text_log )
            text_log->Print("ON_Linetype consecutive segments have length zero.\n");
          return false;
        }
      }
    }
  }

  return true;
}

// 12 Aug 2021 S. Baer
// When adding new fields written to 3dm files, always add information to this
// Dump function. Dump is used by the opennurbs file testing framework to
// perform comparisons and is useful for manual comparison in when tests fail.
void ON_Linetype::Dump( ON_TextLog& dump ) const
{
  ON_ModelComponent::Dump(dump);
  const int segmentCount = SegmentCount();
  dump.Print( "Segment count = %d\n", segmentCount);
  dump.Print( "Pattern length = %g\n", PatternLength());
  dump.Print( "Pattern = (" );
  for( int i = 0; i < segmentCount; i++)
  {
    const ON_LinetypeSegment& seg = m_private->m_segments[i];
    if ( i )
      dump.Print(",");
    switch( seg.m_seg_type)
    {
    case ON_LinetypeSegment::eSegType::stLine:
      dump.Print( "line");
      break;
    case ON_LinetypeSegment::eSegType::stSpace:
      dump.Print( "space");
      break;
    default:
      dump.Print( "invalid");
      break;
    }
  }
  dump.Print(")\n");

  switch (m_cap_style)
  {
  case ON::LineCapStyle::Flat:
    dump.Print("Cap = Flat\n");
    break;
  case ON::LineCapStyle::Square:
    dump.Print("Cap = Square\n");
    break;
  case ON::LineCapStyle::Round:
  default:
    dump.Print("Cap = Round\n");
    break;
  }

  switch (m_join_style)
  {
  case ON::LineJoinStyle::Bevel:
    dump.Print("Join = Bevel\n");
    break;
  case ON::LineJoinStyle::Miter:
    dump.Print("Join = Miter\n");
    break;
  case ON::LineJoinStyle::Round:
  default:
    dump.Print("Join = Round\n");
    break;
  }

  dump.Print("Width = %d\n", Width());
  ON_UnitSystem us(WidthUnits());
  ON_wString usn = us.UnitSystemName();
  const wchar_t* s = usn.Array();
  dump.Print("Width Units = %ls\n", s);
  
  const ON_SimpleArray<ON_2dPoint>* taper = TaperPoints();
  if (taper && taper->Count()>0)
  {
    dump.Print("Taper count = %d\n", taper->Count());
  }
}

// 29 Nov. 2022 S. Baer
// This enum is patterned off of ON_3dmObjectAttributeTypeCode
enum ON_LinetypeTypeCodes : unsigned char
{
  LineCap = 1,
  LineJoin = 2,
  // minor version = 2
  // add width, width units, taper
  Width = 3,
  WidthUnits = 4,
  Taper = 5,
  //minor version = 3
  AlwaysModelDistance = 6,

  LastLinetypeTypeCode = 6
};

bool ON_Linetype::Write( ON_BinaryArchive& file) const
{
  bool rc = false;
  if (file.Archive3dmVersion() < 60)
  {
    if (!file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, 1, 1))
      return false;
    for (;;)
    {
      // chunk version 1.0 fields
      if (!file.Write3dmReferencedComponentIndex(*this))
        break;
        
      ON_wString linetype_name;
      GetName(linetype_name);
      if (!file.WriteString(linetype_name))
        break;

      if (!file.WriteArray(m_private->m_segments))
        break;

      // chunk version 1.1 fields
      if (!file.WriteUuid(Id()))
        break;

      rc = true;
      break;
    }
  }
  else
  {
    // 12 Aug 2021 S. Baer (RH-2285)
    // minor_version = 1: add cap and join styles to linetype
    // 29 Nov 2022 S. Baer (RH-7262)
    // minor_version = 2: add width, width units, and taper
    // 13 Feb 2024 S. Baer (RH-79551)
    // minor_version = 3: add AlwaysModelDistance
    const int minor_version = 3;
    if (!file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, 2, minor_version))
      return false;
    for (;;)
    {
      // chunk version 1.0 fields
      if (!file.WriteModelComponentAttributes(*this,ON_ModelComponent::Attributes::BinaryArchiveAttributes))
        break;

      if (!file.WriteArray(m_private->m_segments))
        break;

      // Only write non-default values in a similar fashion as ON_3dmObjectAttributes
      if (m_cap_style != ON::LineCapStyle::Round)
      {
        const unsigned char itemType = ON_LinetypeTypeCodes::LineCap; // 1
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteChar((unsigned char)m_cap_style))
          break;
      }

      if (m_join_style != ON::LineJoinStyle::Round)
      {
        const unsigned char itemType = ON_LinetypeTypeCodes::LineJoin; // 2
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteChar((unsigned char)m_join_style))
          break;
      }

      if (fabs(Width() - 1.0) > ON_EPSILON)
      {
        const unsigned char itemType = ON_LinetypeTypeCodes::Width; // 3
        if (!file.WriteChar(itemType))
          break;
        if (!file.WriteDouble(Width()))
          break;
      }

      if (WidthUnits() != ON::LengthUnitSystem::None)
      {
        const unsigned char itemType = ON_LinetypeTypeCodes::WidthUnits; // 4
        if (!file.WriteChar(itemType))
          break;

        unsigned char units = (unsigned char)WidthUnits();
        if (!file.WriteChar(units))
          break;
      }

      const ON_SimpleArray<ON_2dPoint>* taper = TaperPoints();
      if (taper && taper->Count() > 0)
      {
        const unsigned char itemType = ON_LinetypeTypeCodes::Taper; // 5
        if (!file.WriteChar(itemType))
          break;

        if (!file.WriteArray(*taper))
          break;
      }

      if (AlwaysModelDistances() == true)
      {
        const unsigned char itemType = ON_LinetypeTypeCodes::AlwaysModelDistance; // 6
        if (!file.WriteChar(itemType))
          break;

        if (!file.WriteBool(AlwaysModelDistances()))
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

bool ON_Linetype::Read( ON_BinaryArchive& file)
{
  *this = ON_Linetype::Unset;

  int major_version=0;
  int minor_version=0;
  if (!file.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version ))
    return false;

  bool rc = false;


  if( 1 == major_version ) 
  {
    for (;;)
    {
      // chunk version 1.0 fields
      int linetype_index = Index();
      if (!file.ReadInt(&linetype_index))
        break;
      SetIndex(linetype_index);

      ON_wString linetype_name;
      GetName(linetype_name);
      if (!file.ReadString(linetype_name))
        break;
      SetName(linetype_name);

      if (!file.ReadArray(m_private->m_segments))
        break;

      if (minor_version >= 1)
      {
        ON_UUID linetype_id = Id();
        if (!file.ReadUuid(linetype_id))
          break;
        SetId(linetype_id);
      }

      rc = true;
      break;
    }
  }
  else if ( 2 == major_version )
  {
    for (;;)
    {
      // chunk version 2.0 fields
      unsigned int model_component_attributes_filter = 0;
      if (!file.ReadModelComponentAttributes(*this,&model_component_attributes_filter))
        break;

      if (!file.ReadArray(m_private->m_segments))
        break;

      unsigned char item_id = 0;
      // 12 Aug 2021 S. Baer (RH-2285)
      // Add cap and join style to linetype
      if (minor_version >= 1)
      {
        if (!file.ReadChar(&item_id))
          break;

        if (ON_LinetypeTypeCodes::LineCap == item_id)
        {
          unsigned char cap = 0;
          if (!file.ReadChar(&cap))
            break;
          m_cap_style = ON::LineCapStyleFromUnsigned(cap);

          if (!file.ReadChar(&item_id))
            break;
        }

        if (ON_LinetypeTypeCodes::LineJoin == item_id)
        {
          unsigned char join = 0;
          if (!file.ReadChar(&join))
            break;
          m_join_style = ON::LineJoinStyleFromUnsigned(join);

          if (!file.ReadChar(&item_id))
            break;
        }

        if (1 == minor_version && item_id != 0)
        {
          ON_ERROR("Bug in ON_Linetype::Read for chunk version 2.1");
        }
      }

      // 12 Aug 2021 S. Baer (RH-2285)
      // Add cap and join style to linetype
      if (minor_version >= 2)
      {
        if (ON_LinetypeTypeCodes::Width == item_id)
        {
          double width = 1;
          if (!file.ReadDouble(&width))
            break;
          SetWidth(width);

          if (!file.ReadChar(&item_id))
            break;
        }

        if (ON_LinetypeTypeCodes::WidthUnits == item_id)
        {
          unsigned char width_units = 0;
          if (!file.ReadChar(&width_units))
            break;
          SetWidthUnits(ON::LengthUnitSystemFromUnsigned(width_units));

          if (!file.ReadChar(&item_id))
            break;
        }

        if (ON_LinetypeTypeCodes::Taper == item_id)
        {
          ON_SimpleArray<ON_2dPoint> taper;
          if (!file.ReadArray(taper))
            break;
          if (nullptr == m_private)
            m_private = new ON_LinetypePrivate();
          m_private->m_taper_points = taper;

          if (!file.ReadChar(&item_id))
            break;
        }

        if (2 == minor_version && item_id != 0)
        {
          ON_ERROR("Bug in ON_Linetype::Read for chunk version 2.2");
        }
      }

      if (minor_version >= 3)
      {
        if (ON_LinetypeTypeCodes::AlwaysModelDistance == item_id)
        {
          bool always = false;
          if (!file.ReadBool(&always))
            break;
          SetAlwaysModelDistances(always);

          if (!file.ReadChar(&item_id))
            break;
        }

        if (3 == minor_version && item_id != 0)
        {
          ON_ERROR("Bug in ON_Linetype::Read for chunk version 2.3");
        }
      }

      if (item_id > ON_LinetypeTypeCodes::LastLinetypeTypeCode)
      {
        // we are reading file written with code newer
        // than this code (minor_version > 2)
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

bool ON_Linetype::PatternIsSet() const
{
  return (0 != (m_is_set_bits & ON_Linetype::pattern_bit));
}


bool ON_Linetype::ClearPattern()
{
  if (false == PatternIsLocked())
  {
    m_is_set_bits &= ~ON_Linetype::pattern_bit;
    m_private->m_segments.Destroy();
  }
  return (false == PatternIsSet());
}

bool ON_Linetype::PatternIsLocked() const
{
  return (0 != (m_is_locked_bits & ON_Linetype::pattern_bit));
}

void ON_Linetype::LockPattern()
{
  m_is_locked_bits |= ON_Linetype::pattern_bit;
}

double ON_Linetype::PatternLength() const
{
  double length = 0.0;
  int seg_count = m_private->m_segments.Count();
  for( int i = 0; i < seg_count; i++)
  {
    length += m_private->m_segments[i].m_length;
  }
  return length;
}

ON_SimpleArray<ON_LinetypeSegment>* ON_Linetype::ExpertSegments()
{
  if (PatternIsLocked())
    return nullptr;
  return &m_private->m_segments;
}

const ON_SimpleArray<ON_LinetypeSegment>& ON_Linetype::Segments() const
{
  return m_private->m_segments;
}

int ON_Linetype::SegmentCount() const
{
  return m_private->m_segments.Count();
}

int ON_Linetype::AppendSegment( const ON_LinetypeSegment& segment)
{
  if (PatternIsLocked())
    return -1;

  m_private->m_segments.Append( segment);
  return(m_private->m_segments.Count()-1);
}

bool ON_Linetype::RemoveSegment( int index )
{
  if (PatternIsLocked())
    return false;
  bool rc = ( index >= 0 && index < m_private->m_segments.Count());
  if (rc)
    m_private->m_segments.Remove(index);
  return rc;
}

bool ON_Linetype::SetSegment( int index, const ON_LinetypeSegment& segment)
{
  if (PatternIsLocked())
    return false;

  if( index >= 0 && index < m_private->m_segments.Count())
  {
    m_private->m_segments[index] = segment;
    return true;
  }
  else
    return false;
}

bool ON_Linetype::SetSegment( int index, double length, ON_LinetypeSegment::eSegType type)
{
  if (PatternIsLocked())
    return false;

  if( index >= 0 && index < m_private->m_segments.Count())
  {
    m_private->m_segments[index].m_length = length;
    m_private->m_segments[index].m_seg_type = type;
    return true;
  }
  else
    return false;
}

bool ON_Linetype::SetSegments(const ON_SimpleArray<ON_LinetypeSegment>& segments)
{
  if (PatternIsLocked())
    return false;

  m_private->m_segments = segments;
  return true;
}


ON_LinetypeSegment ON_Linetype::Segment( int index) const
{
  if( index >= 0 && index < m_private->m_segments.Count())
    return m_private->m_segments[index];
  else
    return ON_LinetypeSegment::OneMillimeterLine;
}

void ON_Linetype::SetLineCapStyle(ON::LineCapStyle style)
{
  m_cap_style = style;
}

ON::LineCapStyle ON_Linetype::LineCapStyle() const
{
  return m_cap_style;
}

void ON_Linetype::SetLineJoinStyle(ON::LineJoinStyle style)
{
  m_join_style = style;
}

ON::LineJoinStyle ON_Linetype::LineJoinStyle() const
{
  return m_join_style;
}

double ON_Linetype::Width() const
{
  return m_width;
}
void ON_Linetype::SetWidth(double width)
{
  m_width = width;
}
ON::LengthUnitSystem ON_Linetype::WidthUnits() const
{
  return m_width_units;
}
void ON_Linetype::SetWidthUnits(ON::LengthUnitSystem units)
{
  m_width_units = units;
}
const ON_SimpleArray<ON_2dPoint>* ON_Linetype::TaperPoints() const
{
  if (m_private->m_taper_points.Count() < 1)
    return nullptr;
  return &(m_private->m_taper_points);
}

bool ON_Linetype::SetTaper(double startWidth, double endWidth)
{
  if (startWidth < 0 || endWidth < 0)
    return false;

  m_private->m_taper_points.Empty();
  m_private->m_taper_points.Append(ON_2dPoint(0, startWidth));
  m_private->m_taper_points.Append(ON_2dPoint(1.0, endWidth));
  return true;
}
bool ON_Linetype::SetTaper(double startWidth, ON_2dPoint taperPoint, double endWidth)
{
  if (startWidth < 0 || endWidth < 0)
    return false;

  if (!taperPoint.IsValid())
    return false;
  if (taperPoint.x < 0.0 || taperPoint.x > 1.0)
    return false;
  if (taperPoint.y < 0.0)
    return false;

  m_private->m_taper_points.Empty();
  m_private->m_taper_points.Append(ON_2dPoint(0, startWidth));
  m_private->m_taper_points.Append(taperPoint);
  m_private->m_taper_points.Append(ON_2dPoint(1.0, endWidth));
  return true;
}

void ON_Linetype::RemoveTaper()
{
  m_private->m_taper_points.Empty();
}

void ON_Linetype::ClearBits()
{
  m_is_set_bits = 0;
  m_is_locked_bits = 0;
}

bool ON_Linetype::AlwaysModelDistances() const
{
  return m_private->m_always_model_distances;
}

void ON_Linetype::SetAlwaysModelDistances(bool on)
{
  m_private->m_always_model_distances = on;
}
