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

class ON_OBSOLETE_V5_HatchExtra : public ON_UserData
{
  //March 23, 2008 - LW
  //Adding ON_OBSOLETE_V5_HatchExtra class to support movable base point for hatches
  //This should be combined with the ON_Hatch class next time that is possible
  // Don't put this extension class in a header file or export it.

  ON_OBJECT_DECLARE(ON_OBSOLETE_V5_HatchExtra);

public:
  ON_OBSOLETE_V5_HatchExtra();
  ~ON_OBSOLETE_V5_HatchExtra() = default;
  ON_OBSOLETE_V5_HatchExtra(const ON_OBSOLETE_V5_HatchExtra&) = default;
  ON_OBSOLETE_V5_HatchExtra& operator=(const ON_OBSOLETE_V5_HatchExtra&) = default;

public:
  static ON_OBSOLETE_V5_HatchExtra* HatchExtension(const ON_Hatch* pHatch);

  // override virtual ON_Object::Dump function
  void Dump( ON_TextLog& text_log ) const override;

  // override virtual ON_Object::SizeOf function
  unsigned int SizeOf() const override;

  // override virtual ON_Object::Write function
  bool Write(ON_BinaryArchive& binary_archive) const override;

  // override virtual ON_Object::Read function
  bool Read(ON_BinaryArchive& binary_archive) override;

  // override virtual ON_UserData::GetDescription function
  bool GetDescription( ON_wString& description ) override;

  // override virtual ON_UserData::Archive function
  bool Archive() const override; 

  bool WriteToArchive(
    const class ON_BinaryArchive& archive,
    const class ON_Object* parent_object
    ) const override;

  bool DeleteAfterWrite(
    const class ON_BinaryArchive& archive,
    const class ON_Object* parent_object
  ) const override;

  bool DeleteAfterRead(
    const class ON_BinaryArchive& archive,
    class ON_Object* parent_object
  ) const override;

  ON_2dPoint m_basepoint = ON_2dPoint::Origin;
};

ON_OBJECT_IMPLEMENT(ON_OBSOLETE_V5_HatchExtra,ON_UserData,"3FF7007C-3D04-463f-84E3-132ACEB91062");

ON_OBSOLETE_V5_HatchExtra* ON_OBSOLETE_V5_HatchExtra::HatchExtension(const ON_Hatch* pHatch)
{
  ON_OBSOLETE_V5_HatchExtra* pExtra = nullptr;
  if(pHatch)
  {
    pExtra = ON_OBSOLETE_V5_HatchExtra::Cast(pHatch->GetUserData(ON_CLASS_ID(ON_OBSOLETE_V5_HatchExtra)));
    if(pExtra == nullptr)
    {
      pExtra = new ON_OBSOLETE_V5_HatchExtra;
      if(pExtra)
      {
        if(!const_cast<ON_Hatch*>(pHatch)->AttachUserData(pExtra))
        {
          delete pExtra;
          pExtra = nullptr;
        }
      }  
    }
  }
  return pExtra;
}

ON_OBSOLETE_V5_HatchExtra::ON_OBSOLETE_V5_HatchExtra()
{
  m_userdata_uuid = ON_CLASS_ID(ON_OBSOLETE_V5_HatchExtra);
  m_application_uuid = ON_opennurbs5_id; // opennurbs.dll reads/writes this userdata
                                         // The id must be the version 5 id because
                                         // V6 SaveAs V5 needs to work, but SaveAs
                                         // V4 should not write this userdata.   
  m_userdata_copycount = 0;
}

void ON_OBSOLETE_V5_HatchExtra::Dump(ON_TextLog& text_log) const
{
}

unsigned int ON_OBSOLETE_V5_HatchExtra::SizeOf() const
{
  unsigned int sz = ON_UserData::SizeOf();
  sz += sizeof(*this)-sizeof(ON_UserData);
  return sz;
}

bool ON_OBSOLETE_V5_HatchExtra::Write(ON_BinaryArchive& archive) const
{
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);

  if(rc) rc = archive.WriteUuid( ON_nil_uuid);
  if(rc) rc = archive.WritePoint(m_basepoint);

  if(!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_OBSOLETE_V5_HatchExtra::Read(ON_BinaryArchive& archive)
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);

  if(major_version != 1)
      rc = false;

  m_basepoint.Set(0.0,0.0);
  ON_UUID ignored_id = ON_nil_uuid;
  if(rc) rc = archive.ReadUuid(ignored_id);
  if(rc) rc = archive.ReadPoint(m_basepoint);

  if(!archive.EndRead3dmChunk())
    rc = false;

  return rc;
}

bool ON_OBSOLETE_V5_HatchExtra::GetDescription( ON_wString& description)
{
  description = L"OBSOLETE V5 ON_Hatch basepoint userdata.";
  return true;
}

bool ON_OBSOLETE_V5_HatchExtra::Archive() const
{
  return true;
}

bool ON_OBSOLETE_V5_HatchExtra::WriteToArchive(
  const class ON_BinaryArchive& archive,
  const class ON_Object* parent_object
  ) const
{
  return (50 == archive.Archive3dmVersion() && nullptr != ON_Hatch::Cast(parent_object));
}


bool ON_OBSOLETE_V5_HatchExtra::DeleteAfterWrite(
  const class ON_BinaryArchive& archive,
  const class ON_Object* parent_object
) const
{
  return true;
}

bool ON_OBSOLETE_V5_HatchExtra::DeleteAfterRead(
  const class ON_BinaryArchive& archive,
  class ON_Object* parent_object
) const
{
  for (;;)
  {
    if (false == m_basepoint.IsValid())
      break;
    ON_Hatch* hatch = ON_Hatch::Cast(parent_object);
    if (nullptr == hatch)
      break;
    ON_2dPoint p = hatch->BasePoint2d();
    if (p.x != m_basepoint.x || p.y != m_basepoint.y)
    {
      hatch->SetBasePoint(m_basepoint);
    }
    break;
  }
  return true;
}

/////////////////////////////////////////////////////////////////
//  class ON_HatchLine
/////////////////////////////////////////////////////////////////

ON_HatchLine::ON_HatchLine(
  double angle_in_radians
  )
  : m_angle_radians( angle_in_radians)
{}

ON_HatchLine::ON_HatchLine(
  double angle_in_radians, 
  ON_2dPoint base, 
  ON_2dVector offset,
  const ON_SimpleArray<double>& dashes
  )
  : m_angle_radians( angle_in_radians)
  , m_base( base)
  , m_offset( offset)
  , m_dashes( dashes)
{}

bool ON_HatchLine::operator==(const ON_HatchLine& src) const
{
  return(
    m_angle_radians == src.m_angle_radians
    && m_base == src.m_base
    && m_offset == src.m_offset
    && m_dashes == src.m_dashes
    );
}

bool ON_HatchLine::operator!=(const ON_HatchLine& src) const
{
  return(
    m_angle_radians != src.m_angle_radians
    || m_base != src.m_base
    || m_offset != src.m_offset
    || m_dashes != src.m_dashes
    );
}

bool ON_HatchLine::IsValid( ON_TextLog* text_log) const
{
  bool rc = m_angle_radians >= 0.0;
  if( !rc)
  {
    if( text_log)
      text_log->Print( "Angle ( %lf) must be >= 0.0\n", m_angle_radians);
    return false;
  }
  rc = m_angle_radians < ON_PI * 2.0;
  if( !rc)
  {
    if( text_log)
      text_log->Print( "Angle ( %lf) must be < 2*Pi.\n", m_angle_radians);
    return false;
  }
  rc = m_base.IsValid();
  if( !rc)
  {
    if( text_log)
      text_log->Print( "Base is not a valid point.\n");
    return false;
  }
  rc = m_offset.IsValid();
  if( !rc)
  {
    if( text_log)
      text_log->Print( "Offset is not a valid vector.\n");
    return false;
  }
  return true;
}

void ON_HatchLine::Dump( ON_TextLog& dump) const
{
  dump.Print( "ON_HatchLine: angle = %lf radians ( %lf degrees) ", 
    AngleRadians(), AngleDegrees());
  dump.Print( " base = ");
  dump.Print( m_base);
  dump.Print( " offset = ");
  dump.Print( m_offset);
  int count = m_dashes.Count();
  dump.Print( "\nDash count = %d: ", count);
  for( int i = 0; i < count; i++)
  {
    dump.Print( "%lf", Dash( i));
    if( i < count-1)
      dump.Print( ", ");
  }
  dump.Print( "\n");
}


bool ON_HatchLine::Write(ON_BinaryArchive& archive) const
{
  if (archive.Archive3dmVersion() < 60)
    return WriteV5(archive);

  const int major_version = 1;
  const int minor_version = 0;
  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, major_version, minor_version))
    return false;
  bool rc = false;
  for (;;)
  {
    if (!archive.WriteDouble(m_angle_radians))
      break;
    if (!archive.WritePoint(m_base))
      break;
    if (!archive.WriteVector(m_offset))
      break;
    if (!archive.WriteArray(m_dashes))
      break;
    rc = true;
    break;
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

static bool Internal_UseHatchReadV5(
  ON_BinaryArchive& archive
  )
{
  if (archive.Archive3dmVersion() < 60)
    return true;
  if (archive.Archive3dmVersion() > 60)
    return false;
  
  // There are 4 possible Feb 26 version numbers depending on the build system
  // archive.Archive3dmVersion() % 4 = (0=developer,1=windows build system,2 = mac build system, 3=unused)
  const unsigned int Feb_26_2016_opennurbs_version_number0 = 2348833956;
  const unsigned int Feb_26_2016_opennurbs_version_number3 = 2348833956+3; 

  const unsigned int archive_opennurbs_version_number = archive.ArchiveOpenNURBSVersion();

  if (archive_opennurbs_version_number < Feb_26_2016_opennurbs_version_number0)
    return true; // "old" opennurbs hatch code

  if (  archive_opennurbs_version_number >= Feb_26_2016_opennurbs_version_number0
    && archive_opennurbs_version_number <= Feb_26_2016_opennurbs_version_number3
    )
  {
    // new hatch IO code pushed to master branch on Feb 26, 2016.
    // THis clunky test has to be used on files written with the Feb 26, 2016 version of opennurbs source code.
    ON__UINT32 tcode = 0;
    ON__INT64 big_value = 0;
    archive.PeekAt3dmBigChunkType(&tcode, &big_value);
    if (TCODE_ANONYMOUS_CHUNK == tcode)
      return false; // use "new" IO
    return true; // use "old" IO
  }

  // 6.0 or later file created with executable using opennurbs code on Feb 27, 2016 or later
  return false;
}

bool ON_HatchLine::Read(ON_BinaryArchive& archive)
{
  if ( Internal_UseHatchReadV5(archive) )
    return ReadV5(archive);

  *this = ON_HatchLine::SolidHorizontal;
  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version))
    return false;
  bool rc = false;
  for (;;)
  {
    if (1 != major_version)
      break;
    if (!archive.ReadDouble(&m_angle_radians))
      break;
    if (!archive.ReadPoint(m_base))
      break;
    if (!archive.ReadVector(m_offset))
      break;
    if (!archive.ReadArray(m_dashes))
      break;
    rc = true;
    break;
  }
  if (!archive.EndRead3dmChunk())
    rc = false;

  return rc;
}


bool ON_HatchLine::WriteV5( ON_BinaryArchive& ar) const
{
  // Incorrectly designed chunk IO - never change version numbers.
  bool rc = ar.Write3dmChunkVersion(1,1);

  if (rc) rc = ar.WriteDouble( m_angle_radians);
  if (rc) rc = ar.WritePoint( m_base);
  if (rc) rc = ar.WriteVector( m_offset);
  if (rc) rc = ar.WriteArray( m_dashes);

  return rc;
}

bool ON_HatchLine::ReadV5( ON_BinaryArchive& ar)
{
  *this = ON_HatchLine::SolidHorizontal;
  // Incorrectly designed chunk IO - never change version numbers.
  int major_version = 0;
  int minor_version = 0;
  bool rc = ar.Read3dmChunkVersion( &major_version, &minor_version);
  if (rc)
    rc = (1 == major_version);
  if ( rc )
  {
    if ( rc) rc = ar.ReadDouble( &m_angle_radians);
    if ( rc) rc = ar.ReadPoint( m_base);
    if ( rc) rc = ar.ReadVector( m_offset);
    if ( rc) rc = ar.ReadArray( m_dashes);
  }
  return rc;
}



int ON_HatchLine::Compare(
  const ON_HatchLine& a,
  const ON_HatchLine& b
  )
{
  int rc = ON_CompareDouble(a.m_angle_radians, b.m_angle_radians);
  if (rc) return rc;
  rc = ON_2dPoint::Compare(a.m_base, b.m_base);
  if (rc) return rc;
  rc = ON_2dVector::Compare(a.m_offset, b.m_offset);
  if (rc) return rc;
  size_t acount = (size_t)a.m_dashes.UnsignedCount();
  size_t bcount = (size_t)b.m_dashes.UnsignedCount();
  if (acount < bcount)
    return -1;
  if (acount > bcount)
    return 1;
  return ON_CompareDoubleArray(acount, a.m_dashes.Array(), b.m_dashes.Array());
}

// ON_HatchLine Interface
double ON_HatchLine::AngleRadians() const
{
  return m_angle_radians;
}

double ON_HatchLine::AngleDegrees() const
{
  if (0.0 <= m_angle_radians && m_angle_radians < 2.0*ON_PI)
  {
    double angle_degrees = m_angle_radians*(180.0/ON_PI);
    if (angle_degrees >= 360.0)
      angle_degrees = 0.0;
    return angle_degrees;
  }
  return m_angle_radians; // UNSET VALUE OR NaN
}

static double DealWithUnsetAngles(
  double a
  )
{
  if (((double)ON_UNSET_FLOAT) == a)
    return ON_UNSET_VALUE;
  
  if (((double)ON_UNSET_POSITIVE_FLOAT) == a)
    return ON_UNSET_POSITIVE_VALUE;
  
  if (a < ON_UNSET_VALUE)
    return ON_UNSET_VALUE;
  
  if (a > ON_UNSET_POSITIVE_VALUE)
    return ON_UNSET_POSITIVE_VALUE;

  return a;
}

void ON_HatchLine::SetAngleRadians( double angle_radians)
{
  angle_radians = DealWithUnsetAngles(angle_radians);
  
  if (angle_radians > ON_UNSET_VALUE && angle_radians < ON_UNSET_POSITIVE_VALUE)
  {
    const double twopi = ON_PI * 2.0;
    // clamp between [0  2pi)
    while (angle_radians < 0.0)
      angle_radians += twopi;
    while (angle_radians > twopi)
      angle_radians -= twopi;

    const double zero_angle_tol = ON_ZERO_TOLERANCE*twopi;
    if (
      fabs(angle_radians) <= zero_angle_tol 
      || fabs(angle_radians - twopi) <= zero_angle_tol 
      )
      angle_radians = 0.0;
  }
  m_angle_radians = angle_radians;
}


void ON_HatchLine::SetAngleDegrees(double angle_degrees)
{
  angle_degrees = DealWithUnsetAngles(angle_degrees);

  if (angle_degrees > ON_UNSET_VALUE && angle_degrees < ON_UNSET_POSITIVE_VALUE)
    SetAngleRadians(angle_degrees*(ON_PI/180.0));
  else
    m_angle_radians = angle_degrees;
}

ON_2dPoint ON_HatchLine::Base() const
{
  return m_base;
}

void ON_HatchLine::SetBase( const ON_2dPoint& base)
{
  m_base = base;
}

ON_2dVector ON_HatchLine::Offset() const
{
  return m_offset;
}

void ON_HatchLine::SetOffset( const ON_2dVector& offset)
{
  m_offset = offset;
}

int ON_HatchLine::DashCount() const
{
  return m_dashes.Count();
}

double ON_HatchLine::Dash( int index) const
{
  if( index >= 0 && index < m_dashes.Count())
    return m_dashes[index];
  return 0.0;
}

void ON_HatchLine::AppendDash( double dash)
{
//  if( fabs( dash) > ON_SQRT_EPSILON)
    m_dashes.Append( dash);
}

void ON_HatchLine::SetDashes( const ON_SimpleArray<double>& dashes)
{
  m_dashes = dashes;
}

const ON_SimpleArray<double>& ON_HatchLine::Dashes() const
{
  return m_dashes;
}

void ON_HatchLine::GetLineData( double& angle, 
                                ON_2dPoint& base, 
                                ON_2dVector& offset, 
                                ON_SimpleArray<double>& dashes) const
{
  angle = m_angle_radians;
  base = m_base;
  offset = m_offset;  dashes = m_dashes;
}

double ON_HatchLine::GetPatternLength() const
{
  int i;
  double length = 0.0;
  for( i = 0; i < m_dashes.Count(); i++)
    length += fabs( m_dashes[i]);

  return length;
}


//  class ON_HatchPattern
/////////////////////////////////////////////////////////////////
ON_OBJECT_IMPLEMENT( ON_HatchPattern, ON_ModelComponent, "064E7C91-35F6-4734-A446-79FF7CD659E1" );

ON_HatchPattern::HatchFillType ON_HatchPattern::HatchFillTypeFromUnsigned(
  unsigned hatch_fill_type_as_unsigned
  )
{
  switch (hatch_fill_type_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_HatchPattern::HatchFillType::Solid);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_HatchPattern::HatchFillType::Lines);
    //ON_ENUM_FROM_UNSIGNED_CASE(ON_HatchPattern::HatchFillType::Gradient);
  }
  ON_ERROR("Invalid hatch_fill_type_as_unsigned value.");
  return ON_HatchPattern::HatchFillType::Solid;
}

int ON_HatchPattern::Compare(
  const ON_HatchPattern& a,
  const ON_HatchPattern& b
  )
{
  int rc = ON_ModelComponent::CompareNameAndId(a, b);
  if (0 == rc)
    rc = CompareAppearance(a, b);
  if (0 == rc)
    rc = ON_wString::CompareOrdinal(a.m_description, b.m_description, false);
  return rc;
}

int ON_HatchPattern::CompareAppearance( 
  const ON_HatchPattern& a,
  const ON_HatchPattern& b
  )
{
  const unsigned int atype = static_cast<unsigned int>(a.FillType());
  const unsigned int btype = static_cast<unsigned int>(b.FillType());
  if (atype < btype)
    return -1;
  if (atype > btype)
    return 1;
  
  if (ON_HatchPattern::HatchFillType::Lines != a.FillType())
    return 0;

  const unsigned acount = a.m_lines.UnsignedCount();
  const unsigned bcount = b.m_lines.UnsignedCount();
  if (acount < bcount)
    return -1;
  if (acount > bcount)
    return 1;

  for (unsigned int i = 0; i < acount; i++)
  {
    int rc = ON_HatchLine::Compare(a.m_lines[i], b.m_lines[i]);
    if (0 != rc)
      return rc;
  }

  return 0;
}

const ON_HatchPattern* ON_HatchPattern::FromModelComponentRef(
  const class ON_ModelComponentReference& model_component_reference,
  const ON_HatchPattern* none_return_value
  )
{
  const ON_HatchPattern* hatch_pattern = ON_HatchPattern::Cast(model_component_reference.ModelComponent());
  return (nullptr != hatch_pattern) ? hatch_pattern : none_return_value;
}

ON_HatchPattern::ON_HatchPattern() ON_NOEXCEPT
  : ON_ModelComponent(ON_ModelComponent::Type::HatchPattern)
{}

ON_HatchPattern::ON_HatchPattern(const ON_HatchPattern& src)
  : ON_ModelComponent(ON_ModelComponent::Type::HatchPattern, src)
  , m_type(src.m_type)
  , m_description(src.m_description)
  , m_lines(src.m_lines)
{}

bool ON_HatchPattern::IsValid( ON_TextLog* text_log) const
{
  ON_HatchPattern::HatchFillType type = FillType();
  bool rc = true;
  if( type != ON_HatchPattern::HatchFillTypeFromUnsigned(static_cast<unsigned int>(type)))
  {
    if( text_log)
      text_log->Print( "Type field not set correctly.\n");
    rc = false;
  }
  if( type == ON_HatchPattern::HatchFillType::Lines)
  {
    int count = m_lines.Count();
    if( count < 1)
    {
      if( text_log)
        text_log->Print( "Line type pattern with no lines.\n");
      return false;
    }
    for( int i = 0; i < count; i++)
    {
      if( !m_lines[i].IsValid())
      {
        if( text_log)
          text_log->Print( "Line[%d] is not valid.\n", i);
        return false;
      }
    }
    return true;
  }
  return rc;
}

void ON_HatchPattern::Dump( ON_TextLog& dump) const
{
  ON_ModelComponent::Dump(dump);

  switch( m_type)
  {
  case ON_HatchPattern::HatchFillType::Solid:
    dump.Print( "fill type: Solid");
    break;
  case ON_HatchPattern::HatchFillType::Lines:
    dump.Print( "fill type: Lines");
    break;
  //case ON_HatchPattern::HatchFillType::Gradient:
  //  dump.Print( "fill type: Gradient");
  //  break;
  }
  dump.Print( "\n");

  const wchar_t* wsDescription =  static_cast< const wchar_t* >(m_description);
  if ( 0 == wsDescription )
    wsDescription = L"";
  dump.Print( "Description: %ls\n", wsDescription);

  if( m_type == ON_HatchPattern::HatchFillType::Lines)
  {
    int count = m_lines.Count();
    dump.Print( "Line count = %d\n", count);
    for( int i = 0; i < count; i++)
    {
      m_lines[i].Dump( dump);
    }
    dump.Print( "\n");
  }
}

bool ON_HatchPattern::Write(ON_BinaryArchive& archive ) const
{
  if (archive.Archive3dmVersion() < 60)
    return WriteV5(archive);

  const int major_version = 1;
  const int minor_version = 0;
  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, major_version, minor_version))
    return false;
  bool rc = false;
  for (;;)
  {
    unsigned int attributes_filter
      = ON_ModelComponent::Attributes::IdAttribute
      | ON_ModelComponent::Attributes::IndexAttribute
      | ON_ModelComponent::Attributes::NameAttribute;
    if (!WriteModelComponentAttributes(archive, attributes_filter))
      break;

    if (!archive.WriteInt(static_cast<unsigned int>(m_type)))
      break;

    if (!archive.WriteString(m_description))
      break;

    if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, 0))
      break;
    {
      const unsigned int count = (m_type == ON_HatchPattern::HatchFillType::Lines ? m_lines.UnsignedCount() : 0);
      bool lines_rc = archive.WriteInt(count);
      for (unsigned int i = 0; i < count && lines_rc; i++)
        lines_rc = m_lines[i].Write(archive);
      if (!archive.EndWrite3dmChunk())
        lines_rc = false;
      if (false == lines_rc)
        break;
    }

    rc = true;
    break;
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_HatchPattern::Read(ON_BinaryArchive& archive)
{
  if ( Internal_UseHatchReadV5(archive) )
    return ReadV5(archive);

  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version))
    return false;
  bool rc = false;
  for (;;)
  {
    if (!ReadModelComponentAttributes(archive))
      break;

    unsigned int type_as_unsigned = 0;
    if (!archive.ReadInt(&type_as_unsigned))
      break;
    m_type = ON_HatchPattern::HatchFillTypeFromUnsigned(type_as_unsigned);

    if (!archive.ReadString(m_description))
      break;

    unsigned int tcode = 0;
    ON__INT64 value = 0;
    if (!archive.BeginRead3dmBigChunk(&tcode, &value))
      break;
    {
      bool lines_rc = (TCODE_ANONYMOUS_CHUNK == tcode && value > 0);
      unsigned int count = 0;
      lines_rc = archive.ReadInt(&count);
      m_lines.Reserve(count);
      for (unsigned int i = 0; i < count && lines_rc; i++)
        lines_rc = m_lines.AppendNew().Read(archive);
      if (!archive.EndRead3dmChunk())
        lines_rc = false;
      if (false == lines_rc)
        break;
    }

    rc = true;
    break;
  }
  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;
}

bool ON_HatchPattern::WriteV5( ON_BinaryArchive& ar) const
{
  bool rc = ar.Write3dmChunkVersion(1,2);

  if (rc) rc = ar.Write3dmReferencedComponentIndex( *this );
  if (rc) rc = ar.WriteInt( static_cast<unsigned int>(m_type));
  ON_wString name = Name();
  if (name.IsEmpty() && ModelComponentStatus().IsDeleted())
    name = DeletedName();
  if (rc) rc = ar.WriteString(name );
  if (rc) rc = ar.WriteString( m_description);
  if( rc)
  {
    if( m_type == ON_HatchPattern::HatchFillType::Lines)
    {
      int i, count = m_lines.Count();
      if ( count < 0 )
        count = 0;
      rc = ar.WriteInt( count );
      for( i = 0; i < count && rc; i++)
        rc = m_lines[i].Write( ar);
    }
  }
  // version 1.2 field
  if (rc) rc = ar.WriteUuid(Id());

  return rc;
}

bool ON_HatchPattern::ReadV5( ON_BinaryArchive& ar)
{
  *this = ON_HatchPattern::Unset;

  int major_version = 0;
  int minor_version = 0;
  bool rc = ar.Read3dmChunkVersion( &major_version, &minor_version);
  if (rc && 1 != major_version)
    rc = false;
  if ( rc ) 
  {
    int hatchpattern_index = Index();
    if (rc) rc = ar.ReadInt(&hatchpattern_index);
    if (rc) SetIndex(hatchpattern_index);

    int fill_type_as_unsigned = 0;
    if( rc) rc = ar.ReadInt( &fill_type_as_unsigned);
    if( rc)  m_type = ON_HatchPattern::HatchFillTypeFromUnsigned(fill_type_as_unsigned);
    ON_wString hatchpattern_name;
    if( rc) rc = ar.ReadString( hatchpattern_name);
    if (rc) SetName(hatchpattern_name);
    if( rc) rc = ar.ReadString( m_description);
    if( rc)
    {
      if( m_type == ON_HatchPattern::HatchFillType::Lines)
      {
        m_lines.Empty();
        int count = 0;
        rc = ar.ReadInt( &count);
        if( rc && count > 0 ) 
        {
          m_lines.SetCapacity( count);
          for(int li = 0; rc && li < count; li++)
          {
            ON_HatchLine& line = m_lines.AppendNew();
            rc = line.Read( ar);
          }
        }
      }
    }
    if ( minor_version >= 2 )
    {
      ON_UUID hatchpattern_id = ON_nil_uuid;
      rc = ar.ReadUuid(hatchpattern_id);
      if (rc) SetId(hatchpattern_id);
    }
  }
  if (rc && IdIsNil())
    SetId(); // modern hatch patterns require a unique id.
  return rc;
}

ON_HatchPattern::ON_HatchPattern::HatchFillType ON_HatchPattern::FillType() const
{
  return m_type;
}

void ON_HatchPattern::SetFillType( ON_HatchPattern::HatchFillType type)
{
  if ( m_type != type && type == ON_HatchPattern::HatchFillTypeFromUnsigned(static_cast<unsigned int>(type)) )
  {
    if (ON_HatchPattern::HatchFillType::Lines != type)
      m_lines.Destroy();
    m_type = type;
    IncrementContentVersionNumber();
  }
}

void ON_HatchPattern::SetDescription( const wchar_t* pDescription)
{
  ON_wString s(pDescription);
  s.TrimLeftAndRight();
  if (s != m_description)
  {
    m_description = s;
    IncrementContentVersionNumber();
  }
}


const ON_wString& ON_HatchPattern::Description() const
{
  return m_description;
}

//  Line HatchPattern functions

int ON_HatchPattern::HatchLineCount() const
{
  return m_lines.Count();
}

int ON_HatchPattern::AddHatchLine( const ON_HatchLine& line)
{
  m_lines.Append( line);
  IncrementContentVersionNumber();
  return m_lines.Count()-1;
}

const ON_HatchLine* ON_HatchPattern::HatchLine( int index) const
{
  if( index >= 0 && index < m_lines.Count())
    return &m_lines[index];
  else
    return nullptr;
}

bool ON_HatchPattern::RemoveHatchLine( int index)
{
  if( index >= 0 && index < m_lines.Count())
  {
    m_lines.Remove( index);
    IncrementContentVersionNumber();
    return true;
  }
  return false;
}

void ON_HatchPattern::RemoveAllHatchLines()
{
  if ( m_lines.UnsignedCount() > 0 )
    IncrementContentVersionNumber();
  m_lines.Empty();
}

int ON_HatchPattern::SetHatchLines( const ON_ClassArray<ON_HatchLine>& lines)
{
  return SetHatchLines(
    lines.UnsignedCount(),
    lines.Array()
    );
}

int ON_HatchPattern::SetHatchLines(
  size_t count,
  const ON_HatchLine* lines
  )
{

  if (count > 0 && nullptr != lines )
  {
    m_lines.SetCount(0);
    m_lines.Append((int)count, lines);
    IncrementContentVersionNumber();
    SetFillType(ON_HatchPattern::HatchFillType::Lines);
  }
  else
  {
    if (0 != m_lines.UnsignedCount())
      IncrementContentVersionNumber();
    m_lines.Destroy();
    if ( ON_HatchPattern::HatchFillType::Lines == FillType())
      SetFillType(ON_HatchPattern::HatchFillType::Solid);
  }
  return m_lines.Count();
}

const ON_ClassArray<ON_HatchLine>& ON_HatchPattern::HatchLines() const
{
  return m_lines;
}


//  class ON_HatchLoop
/////////////////////////////////////////////////////////////////

#if defined(OPENNURBS_EXPORTS)

// When the Microsoft CRT(s) is/are used, this is the best
// way to prevent crashes that happen when a hatch loop is
// allocated with new in one DLL and deallocated with
// delete in another DLL.

void* ON_HatchLoop::operator new(size_t sz)
{
  // ON_HatchLoop new
  return onmalloc(sz);
}

void ON_HatchLoop::operator delete(void* p)
{
  // ON_HatchLoop delete
  onfree(p);
}

void* ON_HatchLoop::operator new[] (size_t sz)
{
  // ON_HatchLoop array new
  return onmalloc(sz);
}

void ON_HatchLoop::operator delete[] (void* p)
{
  // ON_HatchLoop array delete
  onfree(p);
}

void* ON_HatchLoop::operator new(size_t, void* p)
{
  // ON_HatchLoop placement new
  return p;
}

void ON_HatchLoop::operator delete(void*, void*)
{
  // ON_HatchLoop placement delete
  return;
}

#endif


ON_HatchLoop::ON_HatchLoop()
: m_type( ON_HatchLoop::ltOuter), m_p2dCurve( nullptr)
{
}

ON_HatchLoop::ON_HatchLoop( ON_Curve* pCurve2d, eLoopType type)
: m_type( type), m_p2dCurve( pCurve2d)
{
}

ON_HatchLoop::ON_HatchLoop( const ON_HatchLoop& src)
: m_type( src.m_type), m_p2dCurve( nullptr)
{ 
  if( src.m_p2dCurve)
    m_p2dCurve = src.m_p2dCurve->DuplicateCurve();
}

ON_HatchLoop::~ON_HatchLoop()
{
  delete m_p2dCurve;
}

ON_HatchLoop& ON_HatchLoop::operator=( const ON_HatchLoop& src)
{
  if( this != &src)
  {
    if( m_p2dCurve)
      delete m_p2dCurve;
    m_p2dCurve = src.m_p2dCurve->DuplicateCurve();

    m_type = src.m_type;
  }
  return *this;
}

bool ON_HatchLoop::IsValid( ON_TextLog* text_log) const
{
  bool rc = m_p2dCurve != nullptr;
  if( !rc)
  {
    if( text_log)
      text_log->Print( "2d loop curve is nullptr\n");
  }
  if( rc)
  {
    rc = m_p2dCurve->IsValid( text_log);
    if( !rc)
    {
      if( text_log)
        text_log->Print( "Loop curve is not valid\n");
    }
  }

  if(rc)
  {
  }

  if( rc)
  {
    ON_BoundingBox box;
    m_p2dCurve->GetBoundingBox( box);
    rc = ( box.Max().z == box.Min().z && box.Max().z == 0.0);
    if( !rc)
    {
      if( text_log)
        text_log->Print( "2d loop curve has non-zero z coordinates\n");
    }
  }

  if( rc && m_type != ltOuter && m_type != ltInner)
  {
    if( text_log)
      text_log->Print( "Loop type is invalid.\n");
    rc = false;
  }

  return rc;
}

void ON_HatchLoop::Dump( ON_TextLog& dump) const
{
  if( m_type == ltOuter)
    dump.Print( "Outer hatch loop\n");
  if( m_type == ltInner)
    dump.Print( "Inner hatch loop\n");

  if ( 0 == m_p2dCurve )
  {
    dump.Print( "2d curve: null pointer\n");
  }
  else
  {
    dump.Print( "2d curve:\n");
    m_p2dCurve->Dump(dump);
  }

}

bool ON_HatchLoop::Write( ON_BinaryArchive& ar) const
{
  bool rc = ar.Write3dmChunkVersion(1,1);
  if( rc) rc = ar.WriteInt( m_type);
  if( rc) rc = ar.WriteObject( m_p2dCurve);
  return rc;
}

bool ON_HatchLoop::Read( ON_BinaryArchive& ar)
{
  m_type = ltOuter;
  delete m_p2dCurve;
  m_p2dCurve = nullptr;
  int major_version = 0;
  int minor_version = 0;
  bool rc = ar.Read3dmChunkVersion( &major_version, &minor_version);
  if ( major_version == 1 ) 
  {
    int type = 0;
    if( rc) rc = ar.ReadInt( &type);
    if( rc) 
    {
      switch( type)
      {
      case ltOuter:  m_type = ltOuter; break;
      case ltInner:  m_type = ltInner; break;
      default: rc = false; break;
      }
    }
    if( rc)
    {
      ON_Object* pObj = nullptr;
      rc = ar.ReadObject( &pObj);
      if( pObj)
      {
        m_p2dCurve = ON_Curve::Cast( pObj);
        if( !m_p2dCurve) // read something, but it wasn't right
        {
          rc = false;
          delete pObj;
        }
      }
    }
  }
  return rc;
}

const ON_Curve* ON_HatchLoop::Curve() const
{
  return m_p2dCurve;
}

bool ON_HatchLoop::SetCurve( const ON_Curve& curve)
{
  ON_Curve* pC = curve.DuplicateCurve();
  if( pC)
  {
    if(pC->Dimension() == 3 && !pC->ChangeDimension(2))
      return false;

    if( m_p2dCurve)
      delete m_p2dCurve;
    m_p2dCurve = pC;
  }
  return true;
}
ON_HatchLoop::eLoopType ON_HatchLoop::Type() const
{
  return m_type;
}

void ON_HatchLoop::SetType( eLoopType type)
{
  m_type = type;
}

//  class ON_Hatch
/////////////////////////////////////////////////////////////////
ON_OBJECT_IMPLEMENT( ON_Hatch, ON_Geometry, "0559733B-5332-49d1-A936-0532AC76ADE5");

ON_Hatch::ON_Hatch( const ON_Hatch& src)
  : ON_Geometry(src)
{
  Internal_CopyFrom(src);
}

ON_Hatch& ON_Hatch::operator=( const ON_Hatch& src)
{
  if( this != &src)
  {
    Internal_Destroy();
    ON_Geometry::operator =(src);
    Internal_CopyFrom(src);
  }
  return *this;
}

ON_Hatch::~ON_Hatch()
{
  Internal_Destroy();
}

void ON_Hatch::Internal_Destroy()
{
  const int count = m_loops.Count();
  for ( int i = 0; i < count; i++ )
  {
    ON_HatchLoop* pL = m_loops[i];
    if ( pL )
    {
      m_loops[i] = nullptr;
      delete pL;
    }
  }
  m_loops.Destroy();
}

void ON_Hatch::Internal_CopyFrom(const ON_Hatch& src)
{
  m_plane = src.m_plane;
  m_pattern_scale = src.m_pattern_scale;
  m_pattern_rotation = src.m_pattern_rotation;
  m_basepoint = src.m_basepoint;
  const int count = src.m_loops.Count();
  m_loops.SetCount(0);
  m_loops.Reserve(count);
  for( int i = 0; i < count; i++)
  {
    ON_HatchLoop* pL = new ON_HatchLoop( *src.m_loops[i]);
    m_loops.Append( pL);
  }
  m_pattern_index = src.m_pattern_index;
}

ON_Hatch* ON_Hatch::DuplicateHatch() const
{
  return Duplicate();
}


ON_Hatch* ON_Hatch::HatchFromBrep(
  ON_Hatch* use_this_hatch,
  const ON_Brep* brep,
  int face_index,
  int pattern_index,
  double pattern_rotation_radians,
  double pattern_scale,
  ON_3dPoint basepoint)
{
  ON_Hatch* newhatch = nullptr;
  if (nullptr != use_this_hatch)
    use_this_hatch->Internal_Destroy();

  if (nullptr == brep)
    return nullptr;

  if (face_index < 0 || face_index >= brep->m_F.Count())
    face_index = 0;

  const ON_BrepFace* face = brep->Face(face_index);
  if (nullptr == face)
    return nullptr;

  ON_Plane plane;
  if (!face->IsPlanar(&plane))
    return nullptr;

  if (nullptr == use_this_hatch)
    newhatch = new ON_Hatch();
  else
  {
    newhatch = use_this_hatch;
    newhatch->Internal_Destroy();
  }

  if (0 > pattern_index)
    pattern_index = 0;

  if (pattern_scale < ON_SQRT_EPSILON)
    pattern_scale = 1.0;

  if (ON_3dPoint::UnsetPoint == basepoint)
    basepoint = ON_3dPoint::Origin;

  newhatch->SetPlane(plane);
  newhatch->SetPatternIndex(pattern_index);
  newhatch->SetPatternRotation(pattern_rotation_radians);
  newhatch->SetPatternScale(pattern_scale);
  newhatch->SetBasePoint(basepoint);

  bool rc = false;
  int loopcount = face->LoopCount();
  for (int li = 0; li < loopcount; li++)
  {
    ON_Curve* loopcurve = nullptr;
    ON_SimpleArray< ON_Curve* > edgecurves;
    ON_BrepLoop* loop = face->Loop(li);
    if (nullptr != loop)
    {
      int trimcount = loop->TrimCount();
      for (int ti = 0; ti < trimcount; ti++)
      {
        ON_BrepTrim* trim = loop->Trim(ti);
        if (nullptr != trim)
        {
          const ON_Curve* edgecurve = trim->EdgeCurveOf();
          if (nullptr != edgecurve)
          {
            ON_Curve* ec = edgecurve->Duplicate();
            if (trim->m_bRev3d)
              ec->Reverse();
            edgecurves.Append(ec);
          }
        }
      }

      int edgecount = edgecurves.Count();
      if (edgecount == 1)
      {
        loopcurve = edgecurves[0];
      }
      else if (edgecount > 1)
      {
        ON_PolyCurve* pc = new ON_PolyCurve(edgecount);
        if (nullptr != pc)
        {
          for (int ei = 0; ei < edgecount; ei++)
          {
            ON_Curve* ec = edgecurves[ei];
            if (nullptr != ec)
              pc->AppendAndMatch(ec);
          }
          loopcurve = pc;
        }
      }
      if (nullptr != loopcurve)
      {
        ON_Xform xf;
        xf.ChangeBasis(ON_xy_plane, plane);
        loopcurve->Transform(xf);
        ON_HatchLoop* hloop = new ON_HatchLoop();
        hloop->SetCurve(*loopcurve);
        if(loop->m_type == ON_BrepLoop::TYPE::outer)
        {
          hloop->SetType(ON_HatchLoop::eLoopType::ltOuter);
          rc = true;
        }
        else
          hloop->SetType(ON_HatchLoop::eLoopType::ltInner);
        newhatch->AddLoop(hloop);
      }
    }
  }
  if (!rc)
  {
    if (nullptr != newhatch)
    {
      delete newhatch;
      newhatch = nullptr;
    }
  }

  return newhatch;
}


bool ON_Hatch::IsValid( ON_TextLog* text_log) const
{
  bool rc = m_plane.IsValid();
  if( !rc)
  {
    if( text_log)
      text_log->Print( "Plane is not valid\n");
    return false;
  }
  // 18 June 2012 - Lowell - Added loop self-intersection and 
  // intersecting other loops tests
  int count = m_loops.Count();
  for(int i = 0; i < count; i++)
  {
    if(m_loops[i] == 0)
    {
      if( text_log)
        text_log->Print( "Loop[%d] is nullptr\n", i);
      return false;
    }
    if(rc)
      rc = m_loops[i]->IsValid( text_log);
    if( !rc)
    {
      if( text_log)
        text_log->Print( "Loop[%d] is not valid\n", i);
      return false;
    }
  }
  

  return true;
}

void ON_Hatch::Dump( ON_TextLog& dump) const
{
  dump.Print("Hatch: Pattern index: %d\n", PatternIndex());
  dump.Print("Pattern rotation: %g\n", PatternRotation());
  dump.Print("Pattern scale: %g\n", PatternScale());
  ON_3dPoint p = this->BasePoint();
  dump.Print("Base point: %g, %g, %g\n", p.x, p.y, p.z);
  dump.Print("2d base point: %g, %g\n", m_basepoint.x, m_basepoint.y);
  dump.Print("Plane origin: %g, %g, %g\n", m_plane.origin.x, m_plane.origin.y, m_plane.origin.z);
  dump.Print("Plane x axis: %g, %g, %g\n", m_plane.xaxis.x, m_plane.xaxis.y, m_plane.xaxis.z);
  dump.Print("Plane y axis: %g, %g, %g\n", m_plane.yaxis.x, m_plane.yaxis.y, m_plane.yaxis.z);
  dump.Print("Plane z axis: %g, %g, %g\n", m_plane.zaxis.x, m_plane.zaxis.y, m_plane.zaxis.z);
  int count = m_loops.Count();
  dump.Print("Loop count = %d\n", count);
  for( int i = 0; i < count; i++)
    m_loops[i]->Dump( dump);
}

bool ON_Hatch::Write( ON_BinaryArchive& ar) const
{
  // Added basepoint to 1.2;
  const int minor_version = (ar.Archive3dmVersion() >= 60) ? 2 : 1;
  bool rc = ar.Write3dmChunkVersion(1,minor_version);
  if (rc) rc = ar.WritePlane( m_plane);
  if (rc) rc = ar.WriteDouble( m_pattern_scale);
  if (rc) rc = ar.WriteDouble( m_pattern_rotation);
  if (rc) rc = ar.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::HatchPattern, m_pattern_index);
  if (rc)
  {
    int i, count = m_loops.Count();
    if( count < 0 )
      count = 0;
    rc = ar.WriteInt( count);
    for( i = 0; i < count && rc; i++)
      rc = m_loops[i]->Write( ar);
  }
  const ON_2dPoint basepoint = BasePoint2d();
  if (minor_version >= 2)
  {
    // m_basepoint = a 2d (x,y) point.
    if (rc) rc = ar.WritePoint(basepoint);
  }
  else if (
    basepoint.IsValid() 
    && false == basepoint.IsZero()
    && 50 == ar.Archive3dmVersion()
    )
  {
    // add temporary V5 user data cache
    ON_OBSOLETE_V5_HatchExtra* v5_ud = ON_OBSOLETE_V5_HatchExtra::HatchExtension(this);
    if( nullptr!= v5_ud)
      v5_ud->m_basepoint = basepoint;
  }
  return rc;
}

bool ON_Hatch::Read( ON_BinaryArchive& ar)
{
  m_plane.CreateFromNormal( ON_3dPoint::Origin, ON_3dVector::ZAxis);
  m_pattern_scale = 1.0;
  m_pattern_rotation = 0.0;
  m_pattern_index = -1;
  m_loops.Empty();
  int major_version = 0;
  int minor_version = 0;
  bool rc = ar.Read3dmChunkVersion( &major_version, &minor_version);
  if ( rc && major_version == 1 ) 
  {
    if( rc) rc = ar.ReadPlane( m_plane);
    if( rc) rc = ar.ReadDouble( &m_pattern_scale);
    if( rc) rc = ar.ReadDouble( &m_pattern_rotation);
    if( rc) rc = ar.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::HatchPattern,&m_pattern_index);
    if( rc)
    {
      m_loops.Empty();
      int i, count = 0;
      rc = ar.ReadInt( &count);
      if( rc && count > 0)
      {
        m_loops.SetCapacity( count );
        for( i = 0; rc && i < count; i++)
        {
          ON_HatchLoop*& pLoop = m_loops.AppendNew();
          pLoop = new ON_HatchLoop;
          if( pLoop)
            rc = pLoop->Read( ar);
          else
            rc = false;
        }
      }
    }
    if (minor_version >= 2)
    {
      ON_2dPoint basepoint = BasePoint2d();
      if (rc) rc = ar.ReadPoint(basepoint);
      if (rc)
        SetBasePoint(basepoint);
    }
  }
  return rc;
}

ON::object_type ON_Hatch::ObjectType() const
{
  return ON::hatch_object;
}

int ON_Hatch::Dimension() const
{
  return 3;
}

// Copy the 2d curve, make it 3d, and transform it 
// to the 3d plane position
ON_Curve* ON_Hatch::LoopCurve3d( int index) const
{
  int count = m_loops.Count();
  ON_Curve* pC = nullptr;

  if( index >= 0 && index < count)
  {
    if( m_loops[index]->Curve())
    {
      pC = m_loops[index]->Curve()->DuplicateCurve();
      if( pC)
      {
        pC->ChangeDimension( 3);

        ON_Xform xf;
        xf.Rotation( ON_xy_plane, m_plane);

        pC->Transform( xf);
      }
    }
  }
  return pC;
}


int ON_Hatch::PatternIndex() const
{
  return m_pattern_index;
}

void ON_Hatch::SetPatternIndex( int index)
{
  m_pattern_index = index;
}


bool ON_Hatch::GetBBox( double* bmin, double* bmax, bool bGrowBox) const
{
  int i;
  int count = m_loops.Count();
  bool rc = true;
  ON_Curve* pC;
  for( i = 0; rc && i < count; i++)
  {
    pC = LoopCurve3d( i);
    if( pC)
    {
      rc = pC->GetBBox( bmin, bmax, i?true:bGrowBox);
      delete pC;
    }
  }
  return rc;
}

bool ON_Hatch::GetTightBoundingBox( ON_BoundingBox& tight_bbox, bool bGrowBox, const ON_Xform* xform) const
{
  int i;
  int count = m_loops.Count();
  ON_CurveArray curves(count);
  for( i = 0; i < count; i++)
  {
    curves.Append( LoopCurve3d(i) );
  }
  return curves.GetTightBoundingBox(tight_bbox,bGrowBox,xform);
}

static double Angle3d(const ON_3dVector& axis, ON_3dVector& from, const ON_3dVector& to)
{
  ON_3dVector x = from, a = to;
  x.Unitize();
  a.Unitize();

  ON_3dVector y = ON_CrossProduct(axis, from);
  y.Unitize();

  double cosa = x * a;

  if(cosa > 1.0 - ON_SQRT_EPSILON)
    return 0.0;
  if(cosa < ON_SQRT_EPSILON - 1.0)
    return ON_PI;

  double sina = a * y;

  return atan2(sina, cosa);
}


#define ARBBOUND  0.015625
void arbaxis(const ON_3dVector& givenaxis, ON_3dVector& newaxis)
{
  if(fabs(givenaxis[0]) < ARBBOUND && fabs(givenaxis[1]) < ARBBOUND) // near world z
    newaxis = ON_CrossProduct(ON_3dVector::YAxis, givenaxis);
  else
    newaxis = ON_CrossProduct(ON_3dVector::ZAxis, givenaxis);

  newaxis.Unitize();
}

double arbaxisRotation(const ON_Plane& plane)
{
  // get arbaxis frame and angle of rotation from it
  ON_3dVector arbXaxis;
  arbaxis(plane.zaxis, arbXaxis);
  return Angle3d(plane.zaxis, arbXaxis, plane.xaxis);
}

// 20 June 2012 - Lowell - rr44706, 68320
// This will find A, the arbaxis direction for the hatch plane
// and rotate the hatch plane by -A and rotate the hatch boundaries
// by A and add A to the hatch rotation.
// The picture will be the same after that, but the way the
// angle is represented will match the way AutoCAD does it
// so hatches can be round-tripped with acad files.
// In addition, after several hatches are rotated by different amounts
// the hatch angles can be set to look the same by setting them all
// to the same pattern rotation
 
static void UnrotateHatch(ON_Hatch* hatch)
{
  double a = arbaxisRotation(hatch->Plane());

  ON_Plane& plane = *(ON_Plane*)(&hatch->Plane());
  if(fabs(a) > ON_ZERO_TOLERANCE)
  {
    ON_2dPoint base2 = hatch->BasePoint2d();
    plane.Rotate(-a, plane.zaxis);
    for(int i = 0; i < hatch->LoopCount(); i++)
    {
      ON_Curve* pC = (ON_Curve*)hatch->Loop(i)->Curve();
      pC->Rotate(a, ON_3dVector::ZAxis, ON_3dPoint::Origin);
    }
    base2.Rotate(a, ON_2dPoint::Origin);
    hatch->SetBasePoint(base2);

    hatch->SetPatternRotation(hatch->PatternRotation()+a);
  }
  // Project world origin to hatch plane and set hatch plane origin to the result
  // Translate hatch 2d curves to get back to the right position
  ON_3dPoint P;
  plane.ClosestPointTo(ON_3dPoint::Origin, &P.x, &P.y);

  if(fabs(P.x) > ON_ZERO_TOLERANCE ||fabs(P.y) > ON_ZERO_TOLERANCE ||fabs(P.z) > ON_ZERO_TOLERANCE)
  {
    const ON_3dVector V(-P.x, -P.y, 0.0);
    for(int i = 0; i < hatch->LoopCount(); i++)
    {
      ON_Curve* pC = (ON_Curve*)hatch->Loop(i)->Curve();
      pC->Translate(V);
    }

    ON_2dPoint base2 = hatch->BasePoint2d();
    base2 = base2 + ON_2dVector(-P.x, -P.y);
    hatch->SetBasePoint(base2);

    P = plane.PointAt(P.x, P.y);
    plane.origin = P;
  }
}
  
bool ON_Hatch::Transform( const ON_Xform& xform)
{
  if( fabs( fabs( xform.Determinant()) - 1.0) > 1.0e-4)
  {
    // xform has a scale component
    ON_Plane tmp( m_plane);
    tmp.Transform( xform);
    ON_Xform A, B, T;
    A.Rotation( ON_xy_plane, m_plane);
    B.Rotation( tmp, ON_xy_plane);
    T = B * xform * A;

    // kill translation and z-scaling
    T[0][2] = T[0][3] = 0.0;
    T[1][2] = T[1][3] = 0.0;
    T[2][0] = T[2][1] = 0.0; T[2][2] = 1.0; T[2][3] = 0.0; 
    T[3][0] = T[3][1] = T[3][2] = 0.0; T[3][3] = 1.0;

    for( int i = 0; i < LoopCount(); i++)
      m_loops[i]->m_p2dCurve->Transform( T);
  }
  
  ON_3dPoint base = m_plane.PointAt(m_basepoint.x, m_basepoint.y);
  base.Transform(xform);
  int rc = m_plane.Transform(xform);
  SetBasePoint(base);

  //ON_3dVector x = m_plane.xaxis;
  //x.Transform(xform);
  //double scale = x.Length() * PatternScale();
  //SetPatternScale(scale);

  UnrotateHatch(this);

  TransformUserData(xform);

  return rc;
}

bool ON_Hatch::ScalePattern(ON_Xform xform)
{
  ON_3dVector v = m_plane.xaxis;
  v.Transform(xform);

  double l = v.Length();
  if (v.Unitize())
  {
    m_pattern_scale *= l;
    return true;
  }
  return false;
}

ON_Brep* ON_Hatch::BrepForm(ON_Brep* brep) const
{
  if (brep)
    brep->Destroy();

  ON_Brep* newbrep = brep ? brep : ON_Brep::New();

  if (0 == newbrep)
  {
    ON_ERROR("Unable to get allocate brep.");
    return 0;
  }
  brep = newbrep;

  ON_Plane plane = Plane();
  ON_PlaneSurface* srf = new ON_PlaneSurface(plane);
  int srf_i = -1, face_i = -1;

  int loopcount = LoopCount();
  for (int i = 0; i < loopcount; i++)
  {
    const ON_HatchLoop* loop = Loop(i);
    const ON_Curve* loopcurve = loop->Curve();
    ON_Curve* edgecurve = this->LoopCurve3d(i);
    ON_SimpleArray< ON_Curve* > bounds;
    bounds.Append(edgecurve);

    if (i == 0)
    {
      ON_BoundingBox bbox;
      loopcurve->GetBBox(&bbox.m_min.x, &bbox.m_max.x, false);
      srf->SetExtents(0, ON_Interval(bbox.m_min.x - 1.0, bbox.m_max.x + 1.0), true);
      srf->SetExtents(1, ON_Interval(bbox.m_min.y - 1.0, bbox.m_max.y + 1.0), true);
      srf_i = brep->AddSurface(srf);
      ON_BrepFace& face = brep->NewFace(srf_i);
      face_i = face.m_face_index;
      brep->NewPlanarFaceLoop(face_i, ON_BrepLoop::TYPE::outer, bounds, false);
    }
    else
      brep->NewPlanarFaceLoop(face_i, ON_BrepLoop::TYPE::inner, bounds, false);
  }
  brep->SetTolerancesBoxesAndFlags();

  return brep;
}


bool ON_Hatch::Create( const ON_Plane& plane,
                       const ON_SimpleArray<const ON_Curve*> loops, 
                       int pattern_index, 
                       double pattern_rotation, 
                       double pattern_scale)
{
  if( loops.Count() < 1)
    return false;
  if( pattern_index < 0)
    return false;
  SetPlane( plane);
  for( int i = 0; i < loops.Count(); i++)
  {
    ON_HatchLoop* pLoop = new ON_HatchLoop;
    pLoop->SetCurve( *loops[i]);
    pLoop->SetType( i?ON_HatchLoop::ltInner:ON_HatchLoop::ltOuter);
    AddLoop( pLoop);
  }
  SetPatternIndex( pattern_index);
  SetPatternRotation( pattern_rotation);
  SetPatternScale( pattern_scale);
  return true;
}

const ON_Plane& ON_Hatch::Plane() const
{
  return m_plane;
}

void ON_Hatch::SetPlane( const ON_Plane& plane)
{
  m_plane = plane;
}

double ON_Hatch::PatternRotation() const
{
  return m_pattern_rotation;
}

void ON_Hatch::SetPatternRotation( double rotation)
{
  m_pattern_rotation = rotation;
}

double ON_Hatch::PatternScale() const
{
  return m_pattern_scale;
}

void ON_Hatch::SetPatternScale( double scale)
{
  if( scale > 0.001) // Changed May 13, 2009 - Lowell - rr39185
    m_pattern_scale = scale;
}

int ON_Hatch::LoopCount() const
{
  return m_loops.Count();
}

void ON_Hatch::AddLoop( ON_HatchLoop* pLoop)
{
  m_loops.Append( pLoop);
}

bool ON_Hatch::InsertLoop( int index, ON_HatchLoop* loop)
{
  if( index >= 0 && index <= m_loops.Count()) // 26 June 2012 - Lowell - Changed ndex < to ndex <= 
  {
    m_loops.Insert(index, loop);
	return true;
  }

  return false;
}

bool ON_Hatch::RemoveLoop( int index)
{
  if( index >= 0 && index < m_loops.Count())
  {
    delete m_loops[index];
    m_loops.Remove(index);
    return true;
  }
  
  return false;
}


bool ON_Hatch::ReplaceLoops(ON_SimpleArray<const ON_Curve*>& loop_curves)
{
  if(loop_curves.Count() < 1)
    return false;

  bool rc = true;
  ON_Xform xf;
  bool flat = false;
  ON_SimpleArray<ON_HatchLoop*> loops;

  for(int i = 0; i < loop_curves.Count(); i++)
  {
    if(loop_curves[i] == 0)
    {
      rc = false;
      break;
    }
    ON_Curve* p2d = loop_curves[i]->Duplicate();
    if(p2d == 0)
    {
      rc = false;
      break;
    }
    if(p2d->Dimension() == 3)
    {
      if(!flat)
      {
        ON_Xform planexf, flatxf;
        ON_Plane hplane(ON_xy_plane);
        hplane.origin = m_plane.origin;
        planexf.Rotation(m_plane, hplane);
        flatxf.PlanarProjection(hplane);
        xf = flatxf * planexf;
        flat = true;
      }
      if(!p2d->Transform(xf) ||
         !p2d->ChangeDimension(2))
      {
        delete p2d;
        rc = false;
        break;
      }
    }
    ON_HatchLoop* loop = new ON_HatchLoop(p2d,loops.Count()?ON_HatchLoop::ltInner:ON_HatchLoop::ltOuter);
    if(loop)
      loops.Append(loop);
    else
      delete p2d;
  }
  if(!rc)
  {
    for(int i = 0; i < loops.Count(); i++)
      delete loops[i];

    loops.Empty();
  }

  if(loops.Count() < 1)
    return false;

  for(int i = 0; i < m_loops.Count(); i++)
    delete m_loops[i];
  m_loops.Empty();
  for(int i = 0; i < loops.Count(); i++)
    m_loops.Append(loops[i]);
  return true;
}

const ON_HatchLoop* ON_Hatch::Loop( int index) const
{
  if( index >= 0 && index < m_loops.Count())
    return m_loops[index];  
  return nullptr;
}

// Basepoint functions added March 23, 2008 -LW
void ON_Hatch::SetBasePoint(ON_2dPoint basepoint)
{
  m_basepoint = basepoint;
}

void ON_Hatch::SetBasePoint(ON_3dPoint point)
{
  m_plane.ClosestPointTo(point, &m_basepoint.x, &m_basepoint.y);
}

ON_3dPoint ON_Hatch::BasePoint() const
{
  return m_plane.PointAt(m_basepoint.x, m_basepoint.y);
}

ON_2dPoint ON_Hatch::BasePoint2d() const
{
  return m_basepoint;
}

ON_CurveRegionBoundaryElement::ON_CurveRegionBoundaryElement()
  : m_curve_id(-1), m_bReversed(false)
{}
ON_CurveRegionBoundaryElement::ON_CurveRegionBoundaryElement(const ON_CurveRegionBoundaryElement& src)
{
  *this = src;
}

ON_CurveRegionBoundaryElement::~ON_CurveRegionBoundaryElement()
{}

ON_CurveRegionBoundaryElement& ON_CurveRegionBoundaryElement::operator=(const ON_CurveRegionBoundaryElement& src)
{
  if (this != &src){
    m_curve_id = src.m_curve_id;
    m_subdomain = src.m_subdomain;
    m_bReversed = src.m_bReversed;
  }
  return *this;
}

class ON_CLASS ON_GradientColorData : public ON_UserData
{
  ON_OBJECT_DECLARE(ON_GradientColorData);
public:
  ON_GradientColorData();
  ~ON_GradientColorData() = default;

  ON_GradientColorData(const ON_GradientColorData&) = default;
  ON_GradientColorData& operator=(const ON_GradientColorData&) = default;

  //ON_GradientColorData(const ON_GradientColorData&);
  //ON_GradientColorData& operator=(const ON_GradientColorData&);

  static ON_GradientColorData* FromObject( const ON_Object* );
  static ON_GradientColorData* FromObject(ON_Object* obj, bool createAndAttachIfMissing);

  // override virtual ON_Object::Dump function
  void Dump(ON_TextLog& text_log) const override;

  // override virtual ON_Object::SizeOf function
  unsigned int SizeOf() const override;

  // override virtual ON_Object::DataCRC function
  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const override;

  // override virtual ON_Object::Write function
  bool Write(ON_BinaryArchive& binary_archive) const override;

  // override virtual ON_Object::Read function
  bool Read(ON_BinaryArchive& binary_archive) override;

  // override virtual ON_UserData::GetDescription function
  bool GetDescription(ON_wString& description) override;

  // override virtual ON_UserData::Archive function
  bool WriteToArchive(
    const class ON_BinaryArchive& archive,
    const class ON_Object* parent_object
  ) const override;

  // override virtual ON_UserData::Transform function
  bool Transform(const ON_Xform&) override;

  ON_GradientType m_gradient_type = ON_GradientType::Linear;
  ON_3dPoint m_start = ON_3dPoint::UnsetPoint;
  ON_3dPoint m_end = ON_3dPoint::UnsetPoint;
  double m_repeat = 0;
  ON_SimpleArray<ON_ColorStop> m_colors;

//private:
  //void Internal_CopyFrom(const ON_GradientColorData&);
};

ON_OBJECT_IMPLEMENT(ON_GradientColorData, ON_UserData, "0C1AD613-4EFA-4F47-A147-4D79D77FCB0C");

ON_GradientColorData::ON_GradientColorData()
{
  m_userdata_uuid = ON_CLASS_ID(ON_GradientColorData);
  m_application_uuid = ON_opennurbs6_id;
  m_userdata_copycount = 1;
}

//void ON_GradientColorData::Internal_CopyFrom(const ON_GradientColorData & src)
//{
//  m_gradient_type = src.m_gradient_type;
//  m_start = src.m_start;
//  m_end = src.m_end;
//  m_repeat = src.m_repeat;
//  m_colors = src.m_colors;
//}
//
//ON_GradientColorData::ON_GradientColorData(const ON_GradientColorData &src)
//  : ON_UserData(src)
//{
//  Internal_CopyFrom(src);
//}

ON_GradientColorData* ON_GradientColorData::FromObject(const ON_Object* p)
{
  return p
    ? ON_GradientColorData::Cast(p->GetUserData(ON_CLASS_ID(ON_GradientColorData)))
    : nullptr;
}

//ON_GradientColorData & ON_GradientColorData::operator=(const ON_GradientColorData & src)
//{
//  if (this != &src)
//  {
//    ON_UserData::operator=(src);
//    Internal_CopyFrom(src);
//  }
//  return *this;
//}

ON_GradientColorData* ON_GradientColorData::FromObject(ON_Object* obj, bool createAndAttachIfMissing)
{
  if (nullptr == obj)
    return nullptr;
  ON_GradientColorData* rc = ON_GradientColorData::Cast(obj->GetUserData(ON_CLASS_ID(ON_GradientColorData)));
  if (nullptr == rc && createAndAttachIfMissing)
  {
    rc = new ON_GradientColorData();
    if (!obj->AttachUserData(rc))
    {
      delete rc;
      return nullptr;
    }
  }
  return rc;
}

bool ON_GradientColorData::GetDescription(ON_wString& description)
{
  description = L"Color Gradient UserData";
  return true;
}

bool ON_GradientColorData::WriteToArchive(const ON_BinaryArchive & archive, const ON_Object * parent_object) const
{
  return (archive.Archive3dmVersion() >= 60);
}

unsigned int ON_GradientColorData::SizeOf() const
{
  unsigned int sz = ON_UserData::SizeOf();
  sz += sizeof(*this) - sizeof(ON_UserData);
  sz += m_colors.SizeOfArray();
  return sz;
}

ON__UINT32 ON_GradientColorData::DataCRC(ON__UINT32 current_remainder) const
{
  current_remainder = ON_CRC32(current_remainder, sizeof(m_gradient_type), &m_gradient_type);
  current_remainder = m_start.DataCRC(current_remainder);
  current_remainder = m_end.DataCRC(current_remainder);
  current_remainder = ON_CRC32(current_remainder, sizeof(m_repeat), &m_repeat);
  current_remainder = m_colors.DataCRC(current_remainder);
  return current_remainder;
}

void ON_GradientColorData::Dump(ON_TextLog& text_log) const
{
  switch (m_gradient_type)
  {
  case ON_GradientType::None:
    text_log.Print("None gradient\n");
    break;
  case ON_GradientType::Linear:
    text_log.Print("Linear gradient\n");
    break;
  case ON_GradientType::Radial:
    text_log.Print("Radial gradient\n");
    break;
  case ON_GradientType::LinearDisabled:
    text_log.Print("Linear(disabled) gradient\n");
    break;
  case ON_GradientType::RadialDisabled:
    text_log.Print(L"Radial(disabled) gradient\n");
    break;
  default:
    break;
  }

  text_log.PushIndent();
  text_log.Print("points ");
  text_log.Print(m_start);
  text_log.Print("-");
  text_log.Print(m_end);
  text_log.Print("\nrepeat %d\n", m_repeat);
  text_log.PopIndent();
}

bool ON_GradientColorData::Write(ON_BinaryArchive& archive) const
{
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, 1, 0);
  if (!rc)
    return false;

  for (;;)
  {
    rc = archive.WriteInt((int)m_gradient_type);
    if (!rc) break;
    rc = archive.WritePoint(m_start);
    if (!rc) break;
    rc = archive.WritePoint(m_end);
    if (!rc) break;
    rc = archive.WriteDouble(m_repeat);
    if (!rc) break;

    int count = m_colors.Count();
    rc = archive.WriteInt(count);
    if (!rc) break;

    for (int i = 0; i < count && rc; i++)
    {
      rc = m_colors[i].Write(archive);
      if (!rc) break;
    }
    if (!rc) break;

    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_GradientColorData::Read(ON_BinaryArchive& archive)
{
  m_colors.SetCount(0);

  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version);
  if (!rc)
    return false;

  for (;;)
  {
    rc = (1 == major_version);
    if (!rc) break;

    int gt = (int)ON_GradientType::None;
    rc = archive.ReadInt(&gt);
    if (gt < (int)ON_GradientType::None || gt >(int)ON_GradientType::RadialDisabled)
      rc = false;
    if (!rc) break;
    m_gradient_type = (ON_GradientType)gt;

    rc = archive.ReadPoint(m_start);
    if (!rc) break;
    rc = archive.ReadPoint(m_end);
    if (!rc) break;
    rc = archive.ReadDouble(&m_repeat);
    if (!rc) break;
    int count = 0;
    rc = archive.ReadInt(&count);
    if (!rc) break;

    m_colors.Reserve(count);
    for (int i = 0; i < count && rc; i++)
    {
      ON_ColorStop cs;
      rc = cs.Read(archive);
      if (!rc) break;

      m_colors.Append(cs);
    }
    if (!rc) break;

    break;
  }

  if (!archive.EndRead3dmChunk())
    rc = false;

  return rc;
}

bool ON_GradientColorData::Transform(const ON_Xform& xform)
{
  m_start.Transform(xform);
  m_end.Transform(xform);
  return ON_UserData::Transform(xform);
}

/////////////////////////////////////////////////////////////////////////

ON_GradientType ON_Hatch::GetGradientType() const
{
  ON_GradientColorData* data = ON_GradientColorData::FromObject(this);
  if (data)
    return data->m_gradient_type;
  return ON_GradientType::None;
}

void ON_Hatch::SetGradientType(ON_GradientType gt)
{
  ON_GradientColorData* data = ON_GradientColorData::FromObject(this, true);
  if (data)
    data->m_gradient_type = gt;
}

void ON_Hatch::GetGradientColors(ON_SimpleArray<ON_ColorStop>& colors) const
{
  colors.Empty();
  ON_GradientColorData* data = ON_GradientColorData::FromObject(this);
  if (data)
    colors = data->m_colors;
}
bool ON_Hatch::SetGradientColors(const ON_SimpleArray<ON_ColorStop>& colors)
{
  ON_GradientColorData* data = ON_GradientColorData::FromObject(this, true);
  if (nullptr == data)
    return false;
  data->m_colors = colors;
  return true;
}

double ON_Hatch::GetGradientRepeat() const
{
  ON_GradientColorData* data = ON_GradientColorData::FromObject(this);
  if (data)
    return data->m_repeat;
  return 0;
}
bool ON_Hatch::SetGradientRepeat(double repeat)
{
  ON_GradientColorData* data = ON_GradientColorData::FromObject(this);
  if (nullptr == data && 0 == repeat)
    return true;

  data = ON_GradientColorData::FromObject(this, true);
  if (nullptr == data)
    return false;
  
  data->m_repeat = repeat;
  return true;
}

void ON_Hatch::GetGradientEndPoints(ON_3dPoint& startPoint, ON_3dPoint& endPoint) const
{
  ON_GradientColorData* data = ON_GradientColorData::FromObject(this);
  if (nullptr == data)
  {
    startPoint = ON_3dPoint::UnsetPoint;
    endPoint = ON_3dPoint::UnsetPoint;
    return;
  }

  startPoint = data->m_start;
  endPoint = data->m_end;
}
bool ON_Hatch::SetGradientEndPoints(ON_3dPoint startpoint, ON_3dPoint endpoint)
{
  ON_GradientColorData* data = ON_GradientColorData::FromObject(this, true);
  if (nullptr == data)
    return false;

  data->m_start = startpoint;
  data->m_end = endpoint;
  return true;
}
