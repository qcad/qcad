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

// obsolete V5 dimension style
#include "opennurbs_internal_V5_dimstyle.h"

#pragma region DimstyleExtra

/*
Changes and additions 5/01/07 LW
Adding several fields to ON_Dimstyle
Adding the concept of Parent and Child dimstyles so that individual dimension objects
can have their own copy of a dimension style to override some settings

  Adding the concept of Parent and Child dimstyles to support per object overrides of
  dimstyle based properties.  Individual dimensions will be able to have one or more
  properties that differ from the dimension style for that dimension, but the rest of 
  their properties will be controlled by the parent dimstyle. In this implementation 
  (Rhino 5), dimstyles will only inherit one level deep.

  The first time an individual dimension has a dimstyle value overridden, a new child 
  dimstyle is made that is a copy of the dimension's dimstyle. If there is already a 
  child dimstyle for that dimension, it is used and no new dimstyle is made.
  The value being overridden is changed in the child dimstyle and a flag is set that 
  the field is being overridden.

  When a value is changed in a parent dimstyle, it should look through the other 
  dimstyles in the dimstyle table (or your application's equivalent) and change any 
  of its children appropriately.  Name and Index fields aren't propogated this way.
  If the parent's field being changed is not set in the child's m_valid_fields array,
  the child's copy of that field should be changed to match the parent's new value.
  Changing values in child dimstyles doesn't change values in their parents.

  When a value that has previously been overridden by an individual dimension
  is set to ByStyle, the corresponding field flag is unset in the valid field array. 
  If all of the flags in a child dimstyle become unset, the dimension is set to 
  reference the parent dimstyle directly.
  
*/


// Added for v5 - 5/01/07 LW
// Userdata class being used to extend ON_V5x_DimStyle so the v4 sdk still works
// Presumably, this will be moved into ON_V5x_DimStyle when the SDK is changed again
// Don't put this extension class in a header file or export it.

// April 11, 2014 - Lowell
// Moving these fields into ON_Dimstyle
// ON_DimStyleExtra class is still here for writing V5 files
class ON_DimStyleExtra : public ON_UserData
{
  ON_OBJECT_DECLARE(ON_DimStyleExtra);
public:
//  static ON_DimStyleExtra* DimStyleExtensionGet( ON_V5x_DimStyle* pDimStyle, bool bCreateIfNoneExists );
//  static const ON_DimStyleExtra* DimStyleExtensionGet( const ON_V5x_DimStyle* pDimStyle);

  ON_DimStyleExtra();
  ~ON_DimStyleExtra();

  void SetDefaults();

  /*
  Returns:
    True if this ON_DimStyleExtra has default settings.
  */
  bool IsDefault() const;

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

  bool DeleteAfterRead( 
    const class ON_BinaryArchive& archive,
    class ON_Object* parent_object
    ) const override;

  bool DeleteAfterWrite(
    const class ON_BinaryArchive& archive,
    const class ON_Object* parent_object
    ) const override;


  //void SetFieldOverride( int field_id, bool bOverride);
  //bool IsFieldOverride( int field_id) const;

  // Data access
  // Scale all of the length values
  void Scale( double scale);

  // Tolerances
  // Tolerance style
  //  0: None
  //  1: Symmetrical
  //  2: Deviation
  //  3: Limits
  //  4: Basic
  void SetToleranceStyle( int style);
  int  ToleranceStyle() const;
  
  void SetToleranceResolution( int resolution);
  int  ToleranceResolution() const;

  void SetToleranceUpperValue( double upper_value);
  double ToleranceUpperValue() const;

  void SetToleranceLowerValue( double lower_value);
  double ToleranceLowerValue() const;

  void SetToleranceHeightScale( double scale);
  double ToleranceHeightScale() const;

  void SetBaselineSpacing( double);
  double BaselineSpacing() const;

  // Determines whether or not to draw a Text Mask
  bool DrawTextMask() const;
  void SetDrawTextMask(bool bDraw);

  // Determines where to get the color to draw a Text Mask
  // 0: Use background color of the viewport.  Initially, gradient backgrounds will not be supported
  // 1: Use the ON_Color returned by MaskColor()
  int MaskColorSource() const;
  void SetMaskColorSource(int source);

  ON_Color MaskColor() const;  // Only works right if MaskColorSource returns 1.
                               // Does not return viewport background color
  void SetMaskColor(ON_Color color);

  void SetDimScale(double scale);
  double DimScale() const;
  void SetDimScaleSource(int source);
  int DimScaleSource() const;

  void SetSourceDimstyle(ON_UUID source_uuid);
  ON_UUID SourceDimstyle() const;

  bool CompareFields(const ON_DimStyleExtra* pOther) const;

  // Data storage

  ON_UUID m_parent_dimstyle;  // ON_nil_uuid if there is no parent dimstyle
  ON_SimpleArray<bool> m_valid_fields;
  enum { eFieldCount = 66 };

  int    m_tolerance_style;
  int    m_tolerance_resolution;
  double m_tolerance_upper_value;   // or both upper and lower in symmetrical style
  double m_tolerance_lower_value;
  double m_tolerance_height_scale;  // relative to the main dimension text

  double m_baseline_spacing;

  // Text mask - added Dec 12 2009
  bool     m_bDrawMask;
  int      m_mask_color_source;
  ON_Color m_mask_color;

  // Per dimstyle DimScale added Dec 16, 2009
  double   m_dimscale;
  int      m_dimscale_source;

  // 19 Oct 2010 - Added uuid of source dimstyle to restore defaults
  ON_UUID  m_source_dimstyle;
};



// Added for v5 - 5/01/07 LW
ON_OBJECT_IMPLEMENT(ON_DimStyleExtra,ON_UserData,"513FDE53-7284-4065-8601-06CEA8B28D6F");

//ON_DimStyleExtra* ON_DimStyleExtra::DimStyleExtensionGet( ON_V5x_DimStyle* pDimStyle, bool bCreateIfNoneExists )
//{
//  ON_DimStyleExtra* pExtra = 0;
//  if( pDimStyle)
//  {
//    pExtra = ON_DimStyleExtra::Cast( pDimStyle->GetUserData( ON_CLASS_ID(ON_DimStyleExtra)));
//    // 2 November 2011 Dale Lear
//    //   I added the bCreateIfNoneExists parameter and I'm using
//    //   is sparingly.  It is critical that we do not add
//    //   ON_DimStyleExtra unless it is actually being used
//    //   to override a default setting.  Otherwise, we 
//    //   end up leaking vast amounts of memory when
//    //   the default dimstyle in the Rhino dimstyle
//    //   table is used due to the way annotation
//    //   is currently drawn.
//    //   If you have questions, please ask Dale Lear for details
//    //   but please do not revert to constantly adding user
//    //   data to dimstyles.
//    if( pExtra == 0 && bCreateIfNoneExists )
//    {
//      pExtra = new ON_DimStyleExtra;
//      if( pExtra)
//      {
//        if( !pDimStyle->AttachUserData( pExtra))
//        {
//          delete pExtra;
//          pExtra = 0;
//        }
//      }
//    }
//  }
//  return pExtra;
//}
//
//const 
//ON_DimStyleExtra* ON_DimStyleExtra::DimStyleExtensionGet( const ON_V5x_DimStyle* pDimStyle)
//{
//  // Please do not changes the "false" to a "true" in the second argument.
//  return ON_DimStyleExtra::DimStyleExtensionGet( (ON_V5x_DimStyle*)pDimStyle, false );
//}

ON_DimStyleExtra::ON_DimStyleExtra()
{
  m_userdata_uuid = ON_CLASS_ID(ON_DimStyleExtra);
  m_application_uuid = ON_opennurbs5_id; // opennurbs.dll reads/writes this userdata
                                         // The id must be the version 5 id because
                                         // V6 SaveAs V5 needs to work, but SaveAs
                                         // V4 should not write this userdata.
  m_userdata_copycount = 1;
  m_valid_fields.Reserve( ON_DimStyleExtra::eFieldCount);
  m_valid_fields.SetCount( ON_DimStyleExtra::eFieldCount);
  m_parent_dimstyle = ON_nil_uuid;
  m_source_dimstyle = ON_nil_uuid;
  SetDefaults();
}

ON_DimStyleExtra::~ON_DimStyleExtra()
{
}

void ON_DimStyleExtra::SetDefaults()
{
  m_tolerance_style = ON_V5x_DimStyle::DefaultToleranceStyle();
  m_tolerance_resolution = ON_V5x_DimStyle::DefaultToleranceResolution();
  m_tolerance_upper_value = ON_V5x_DimStyle::DefaultToleranceUpperValue();
  m_tolerance_lower_value = ON_V5x_DimStyle::DefaultToleranceLowerValue();
  m_tolerance_height_scale = ON_V5x_DimStyle::DefaultToleranceHeightScale();
  m_baseline_spacing = ON_V5x_DimStyle::DefaultBaselineSpacing();
  m_bDrawMask = ON_V5x_DimStyle::DefaultDrawTextMask(); // false;
  m_mask_color_source = ON_V5x_DimStyle::DefaultMaskColorSource(); // 0;
  m_mask_color = ON_V5x_DimStyle::DefaultMaskColor(); // .SetRGB(255,255,255);
  m_dimscale = ON_V5x_DimStyle::DefaultDimScale(); // 1.0;
  m_dimscale_source = ON_V5x_DimStyle::DefaultDimScaleSource(); // 0;

  for( int i = 0; i < m_valid_fields.Count(); i++)
    m_valid_fields[i] = false;
}

bool ON_DimStyleExtra::IsDefault() const
{
  if ( m_tolerance_style != ON_V5x_DimStyle::DefaultToleranceStyle() ) return false;
  if ( m_tolerance_resolution != ON_V5x_DimStyle::DefaultToleranceResolution() ) return false;
  if ( m_tolerance_upper_value != ON_V5x_DimStyle::DefaultToleranceUpperValue() ) return false;
  if ( m_tolerance_lower_value != ON_V5x_DimStyle::DefaultToleranceLowerValue() ) return false;
  if ( m_tolerance_height_scale != ON_V5x_DimStyle::DefaultToleranceHeightScale() ) return false;
  if ( m_baseline_spacing != ON_V5x_DimStyle::DefaultBaselineSpacing() ) return false;
  if ( m_bDrawMask != ON_V5x_DimStyle::DefaultDrawTextMask() ) return false;
  if ( m_mask_color_source != ON_V5x_DimStyle::DefaultMaskColorSource() ) return false;
  if ( m_mask_color != ON_V5x_DimStyle::DefaultMaskColor() ) return false;
  if ( m_dimscale != ON_V5x_DimStyle::DefaultDimScale() ) return false;
  if ( m_dimscale_source != ON_V5x_DimStyle::DefaultDimScaleSource() ) return false;

  // The m_valid_fields[] settings only matter when
  // m_parent_dimstyle is not zero.
  if ( !(m_parent_dimstyle == ON_nil_uuid) )
  {
    for( int i = 0; i < m_valid_fields.Count() && i < ON_DimStyleExtra::eFieldCount; i++)
    {
      if ( !m_valid_fields[i] )
        return false;
    }
  }

  return true;
}

void ON_DimStyleExtra::Dump( ON_TextLog& text_log ) const
{
  // do nothing
}

unsigned int ON_DimStyleExtra::SizeOf() const
{
  unsigned int sz = ON_UserData::SizeOf();
  sz += sizeof(*this) - sizeof(ON_UserData);
  return sz;
}

bool ON_DimStyleExtra::Write(ON_BinaryArchive& archive) const
{
//  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0); Changed to 1,1 for mask settings 12/12/09
//  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,1); Changed to 1,2 for dimscale 12/17/09
//  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,2); Changed to 1,3 for source_dimstyle 10/19/10
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,3);

  if(rc) rc = archive.WriteUuid( m_parent_dimstyle);
  if(rc) rc = archive.WriteArray( m_valid_fields);

  if(rc) rc = archive.WriteInt(m_tolerance_style);
  if(rc) rc = archive.WriteInt(m_tolerance_resolution);

  if(rc) rc = archive.WriteDouble(m_tolerance_upper_value);
  if(rc) rc = archive.WriteDouble(m_tolerance_lower_value);
  if(rc) rc = archive.WriteDouble(m_tolerance_height_scale);

  // March 22, 2010 - Global DimStyle was obsoleted and moved into DimStyles
  // So now for writing older version files, its multiplied into all distance values
  if(archive.Archive3dmVersion() < 5)
  {
    if(rc) rc = archive.WriteDouble(m_baseline_spacing * m_dimscale);
  }
  else
  {
    if(rc) rc = archive.WriteDouble(m_baseline_spacing);
  }

  if(rc) rc = archive.WriteBool(m_bDrawMask);
  if(rc) rc = archive.WriteInt(m_mask_color_source);
  if(rc) rc = archive.WriteColor(m_mask_color);

  if(archive.Archive3dmVersion() < 5)
  {
    if(rc) rc = archive.WriteDouble(1.0);
  }
  else
  {
    if(rc) rc = archive.WriteDouble(m_dimscale);
  }
  if(rc) rc = archive.WriteInt(m_dimscale_source); // Obsolete field

  if(rc) rc = archive.WriteUuid(m_source_dimstyle);  // Added 19 Oct 2010

  if(!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_DimStyleExtra::Read(ON_BinaryArchive& archive)
{
  // Changed to 1,0 for mask settings 12/12/09
  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if(major_version != 1)
    rc = false;

  if(rc) rc = archive.ReadUuid(m_parent_dimstyle);
  if(rc) rc = archive.ReadArray(m_valid_fields);

  if(rc) rc = archive.ReadInt(&m_tolerance_style);
  if(rc) rc = archive.ReadInt(&m_tolerance_resolution);

  if(rc) rc = archive.ReadDouble(&m_tolerance_upper_value);
  if(rc) rc = archive.ReadDouble(&m_tolerance_lower_value);
  if(rc) rc = archive.ReadDouble(&m_tolerance_height_scale);

  if(rc) rc = archive.ReadDouble(&m_baseline_spacing);

  if(minor_version >= 1)
  {
    if(rc) rc = archive.ReadBool(&m_bDrawMask);
    if(rc) rc = archive.ReadInt(&m_mask_color_source);
    if(rc) rc = archive.ReadColor(m_mask_color);
  }

  if(minor_version >= 2)
  {
    if(rc) rc = archive.ReadDouble(&m_dimscale);
    if(rc) rc = archive.ReadInt(&m_dimscale_source);
  }

  if(minor_version >= 3)
  {
    if(rc) rc = archive.ReadUuid(m_source_dimstyle);
  }

  if ( !archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool ON_DimStyleExtra::DeleteAfterWrite(
  const class ON_BinaryArchive& archive,
  const class ON_Object* parent_object
) const
{
  return true;
}

bool ON_DimStyleExtra::DeleteAfterRead(
  const class ON_BinaryArchive& archive,
  class ON_Object* parent_object
) const
{
  // Move settings to ON_V5x_DimStyle
  for (;;)
  {
    ON_V5x_DimStyle* dimstyle = ON_V5x_DimStyle::Cast(parent_object);
    if (nullptr == dimstyle)
      break;

    if (ON_nil_uuid == dimstyle->ParentId())
      dimstyle->SetParentId(this->m_parent_dimstyle);

    if (0 == dimstyle->m_field_override_count)
    {
      const unsigned int capacity = sizeof(dimstyle->m_field_override) / sizeof(dimstyle->m_field_override[0]);
      unsigned int count = m_valid_fields.Count();
      if ( count > static_cast<unsigned int>(ON_V5x_DimStyle::Field::FieldCount) )
        count = static_cast<unsigned int>(ON_V5x_DimStyle::Field::FieldCount);
      for (unsigned int i = 0; i < count && i < capacity; i++)
      {
        bool bOverrideParentSetting 
          = (i > static_cast<unsigned int>(ON_V5x_DimStyle::Field::fn_index) && i <= static_cast<unsigned int>(ON_V5x_DimStyle::Field::fn_dim_arrow_blockname2) && this->m_valid_fields[i])
          ? true 
          : false;
        dimstyle->m_field_override[i] = bOverrideParentSetting;
        if (bOverrideParentSetting)
          dimstyle->m_field_override_count++;
      }
      for (unsigned int i = count; i < capacity; i++)
        dimstyle->m_field_override[i] = false;
    }
    dimstyle->m_tolerance_style = this->m_tolerance_style;
    dimstyle->m_tolerance_resolution = this->m_tolerance_resolution;
    dimstyle->m_tolerance_upper_value = this->m_tolerance_upper_value;
    dimstyle->m_tolerance_lower_value = this->m_tolerance_lower_value;
    dimstyle->m_tolerance_height_scale = this->m_tolerance_height_scale;
    dimstyle->m_bDrawMask = this->m_bDrawMask;
    dimstyle->m_mask_color_source = this->m_mask_color_source;
    dimstyle->m_mask_color = this->m_mask_color;
    dimstyle->m_dimscale = this->m_dimscale;
    dimstyle->m_dimscale_source = this->m_dimscale_source;
    dimstyle->m_source_dimstyle = this->m_source_dimstyle;
   
    break;
  }

  return true;
}


bool ON_DimStyleExtra::GetDescription( ON_wString& description)
{
  description = L"Userdata extension of ON_V5x_DimStyle";
  return true;
}

bool ON_DimStyleExtra::Archive() const
{
  // true to write to file
  return true;
}

void ON_DimStyleExtra::Scale( double scale)
{
  if( ON_IsValid( scale) && scale > ON_SQRT_EPSILON)
    m_baseline_spacing *= scale;
}

// Tolerance style
void ON_DimStyleExtra::SetToleranceStyle( int style)
{
  if( style >= 0 && style <= 4)
    m_tolerance_style = style;
}

int ON_DimStyleExtra::ToleranceStyle() const
{
  return m_tolerance_style;
}

void ON_DimStyleExtra::SetToleranceResolution( int resolution)
{
  if( resolution >= 0 && resolution < 16)
    m_tolerance_resolution = resolution;
}

int ON_DimStyleExtra::ToleranceResolution() const
{
  return m_tolerance_resolution;
}

void ON_DimStyleExtra::SetToleranceUpperValue( double upper_value)
{
  if( ON_IsValid(upper_value))
    m_tolerance_upper_value = upper_value;
}

double ON_DimStyleExtra::ToleranceUpperValue() const
{
  return m_tolerance_upper_value;
}

void ON_DimStyleExtra::SetToleranceLowerValue( double lower_value)
{
  if( ON_IsValid(lower_value))
    m_tolerance_lower_value = lower_value;
}

double ON_DimStyleExtra::ToleranceLowerValue() const
{
  return m_tolerance_lower_value;
}

void ON_DimStyleExtra::SetToleranceHeightScale( double scale)
{
  if( ON_IsValid( scale) && scale > ON_SQRT_EPSILON)
    m_tolerance_height_scale = scale;
}

double ON_DimStyleExtra::ToleranceHeightScale() const
{
  return m_tolerance_height_scale;
}

void ON_DimStyleExtra::SetBaselineSpacing( double spacing)
{
  if( ON_IsValid( spacing) && spacing > ON_SQRT_EPSILON)
    m_baseline_spacing = spacing;
}

double ON_DimStyleExtra::BaselineSpacing() const
{
  return m_baseline_spacing;
}

bool ON_DimStyleExtra::DrawTextMask() const
{
  return m_bDrawMask;
}

void ON_DimStyleExtra::SetDrawTextMask(bool bDraw)
{
  m_bDrawMask = bDraw ? true : false;
}

int ON_DimStyleExtra::MaskColorSource() const
{
  return m_mask_color_source;
}

void ON_DimStyleExtra::SetMaskColorSource(int source)
{
  if(source == 1)
    m_mask_color_source = 1;
  else
    m_mask_color_source = 0;
}

ON_Color ON_DimStyleExtra::MaskColor() const
{
  return m_mask_color;
}

void ON_DimStyleExtra::SetMaskColor(ON_Color color)
{
  m_mask_color = color;
}

void ON_DimStyleExtra::SetDimScale(double scale)
{
  m_dimscale = scale;
}

double ON_DimStyleExtra::DimScale() const
{
  return m_dimscale;
}

void ON_DimStyleExtra::SetDimScaleSource(int source)
{
  m_dimscale_source = source;
}

int ON_DimStyleExtra::DimScaleSource() const
{
  return m_dimscale_source;
}

void ON_DimStyleExtra::SetSourceDimstyle(ON_UUID source_uuid)
{
  m_source_dimstyle = source_uuid;
}

ON_UUID ON_DimStyleExtra::SourceDimstyle() const
{
  return m_source_dimstyle;
}

// returns true if they are the same
bool ON_DimStyleExtra::CompareFields(const ON_DimStyleExtra* pOther) const
{
  if(pOther == 0)
    return false;

  if((m_parent_dimstyle        != pOther->m_parent_dimstyle) ||
     (m_tolerance_style        != pOther->m_tolerance_style) ||
     (m_tolerance_resolution   != pOther->m_tolerance_resolution) ||
     (m_tolerance_upper_value  != pOther->m_tolerance_upper_value) ||
     (m_tolerance_lower_value  != pOther->m_tolerance_lower_value) ||
     (m_tolerance_height_scale != pOther->m_tolerance_height_scale) ||
     (m_baseline_spacing       != pOther->m_baseline_spacing) ||
     (m_bDrawMask              != pOther->m_bDrawMask) ||
     (m_mask_color_source      != pOther->m_mask_color_source) ||
     (m_mask_color             != pOther->m_mask_color) ||
     (m_dimscale               != pOther->m_dimscale) ||
     (m_dimscale_source        != pOther->m_dimscale_source)
     )
    return false;

  for(int i = 0; i < m_valid_fields.Count(); i++)
  {
    if(m_valid_fields[i] != pOther->m_valid_fields[i])
      return false;
  }
  return true;
}
#pragma endregion DimstyleExtra


ON_OBJECT_IMPLEMENT( ON_V5x_DimStyle, ON_Object, "81BD83D5-7120-41c4-9A57-C449336FF12C" );

ON_V5x_DimStyle::ON_V5x_DimStyle()
  : ON_ModelComponent(ON_ModelComponent::Type::DimStyle)
{}

ON_V5x_DimStyle::~ON_V5x_DimStyle()
{}


// copy from ON_3dmAnnotationSettings and add a couple of fields
ON_V5x_DimStyle::ON_V5x_DimStyle( const ON_3dmAnnotationSettings& src)
  : ON_ModelComponent(ON_ModelComponent::Type::DimStyle)
{
  m_extextension       = src.m_dimexe;
  m_extoffset          = src.m_dimexo;
  m_arrowsize          = src.m_arrowlength;
  m_dimstyle_textalign = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine;
  m_centermark         = src.m_centermark;
  m_textgap            = src.m_dimexo / 2.0;
  m_textheight         = src.m_textheight;
  m_arrowtype          = src.m_arrowtype;
  m_angularunits       = src.m_angularunits;
  m_lengthformat       = src.m_lengthformat;
  m_angleformat        = src.m_angleformat;
  m_lengthresolution   = src.m_resolution;
  m_angleresolution    = src.m_resolution;
}

bool ON_V5x_DimStyle::CompareValidFields(const ON_V5x_DimStyle& style) const
{
  if ( 0 == m_field_override_count && 0 == style.m_field_override_count )
    return true;

  if ( m_field_override_count != style.m_field_override_count )
    return false;

  const unsigned int count = (unsigned int)(sizeof(m_field_override) / sizeof(m_field_override[0]));
  for (int i = 0; i < count; i++)
  {
    if ((m_field_override_count > 0 ? m_field_override[i] : false) != (style.m_field_override_count > 0 ? style.m_field_override[i] : false) )
      return false;
  }
  return true;
}


bool ON_V5x_DimStyle::CompareDimstyle(const ON_V5x_DimStyle& style) const
{
  if (
    0 == ON_ModelComponent::CompareNameExact(*this,style) &&
    m_extextension == style.m_extextension &&
    m_extoffset == style.m_extoffset &&
    m_arrowsize == style.m_arrowsize &&
    m_centermark == style.m_centermark &&
    m_textgap == style.m_textgap &&
    m_textheight == style.m_textheight &&
    m_dimstyle_textalign == style.m_dimstyle_textalign &&
    m_arrowtype == style.m_arrowtype &&
    m_angularunits == style.m_angularunits &&
    m_lengthformat == style.m_lengthformat &&
    m_angleformat == style.m_angleformat &&
    m_lengthresolution == style.m_lengthresolution &&
    m_angleresolution == style.m_angleresolution &&
    m_v5_text_style.Font().ManagedFontSerialNumber() == style.m_v5_text_style.Font().ManagedFontSerialNumber() &&
    //ON_TextStyle::EqualTextStyleFontAndName(m_text_style, style.m_text_style) &&
    m_lengthfactor == style.m_lengthfactor &&
    m_bAlternate == style.m_bAlternate &&
    m_alternate_lengthfactor == style.m_alternate_lengthfactor &&
    m_alternate_lengthformat == style.m_alternate_lengthformat &&
    m_alternate_lengthresolution == style.m_alternate_lengthresolution &&
    m_alternate_angleformat == style.m_alternate_angleformat &&
    m_alternate_angleresolution == style.m_alternate_angleresolution &&

    m_prefix == style.m_prefix &&
    m_suffix == style.m_suffix &&
    m_alternate_prefix == style.m_alternate_prefix &&
    m_alternate_suffix == style.m_alternate_suffix &&

    m_dimextension == style.m_dimextension &&

    m_leaderarrowsize == style.m_leaderarrowsize &&
    m_leaderarrowtype == style.m_leaderarrowtype &&
    m_bSuppressExtension1 == style.m_bSuppressExtension1 &&
    m_bSuppressExtension2 == style.m_bSuppressExtension2 &&

    ParentId() == style.ParentId() &&
    m_source_dimstyle == style.m_source_dimstyle &&

    m_tolerance_style == style.m_tolerance_style &&
    m_tolerance_resolution == style.m_tolerance_resolution &&
    m_tolerance_upper_value == style.m_tolerance_upper_value &&
    m_tolerance_lower_value == style.m_tolerance_lower_value &&
    m_tolerance_height_scale == style.m_tolerance_height_scale &&
    m_baseline_spacing == style.m_baseline_spacing &&
    m_bDrawMask == style.m_bDrawMask &&
    m_mask_color_source == style.m_mask_color_source &&
    m_mask_color == style.m_mask_color &&
    m_dimscale == style.m_dimscale &&
    m_dimscale_source == style.m_dimscale_source &&

    m_ext_line_color_source == style.m_ext_line_color_source &&
    m_dim_line_color_source == style.m_dim_line_color_source &&
    m_arrow_color_source == style.m_arrow_color_source &&
    m_text_color_source == style.m_text_color_source &&
    m_ext_line_color == style.m_ext_line_color &&
    m_dim_line_color == style.m_dim_line_color &&
    m_arrow_color == style.m_arrow_color &&
    m_text_color == style.m_text_color &&
    m_ext_line_plot_color_source == style.m_ext_line_plot_color_source &&
    m_dim_line_plot_color_source == style.m_dim_line_plot_color_source &&
    m_arrow_plot_color_source == style.m_arrow_plot_color_source &&
    m_text_plot_color_source == style.m_text_plot_color_source &&
    m_ext_line_plot_color == style.m_ext_line_plot_color &&
    m_dim_line_plot_color == style.m_dim_line_plot_color &&
    m_arrow_plot_color == style.m_arrow_plot_color &&
    m_text_plot_color == style.m_text_plot_color &&
    m_ext_line_plot_weight_source == style.m_ext_line_plot_weight_source &&
    m_dim_line_plot_weight_source == style.m_dim_line_plot_weight_source &&
    m_ext_line_plot_weight_mm == style.m_ext_line_plot_weight_mm &&
    m_dim_line_plot_weight_mm == style.m_dim_line_plot_weight_mm &&

    m_fixed_extension_len == style.m_fixed_extension_len &&
    m_fixed_extension_len_on == style.m_fixed_extension_len_on &&
    m_text_rotation == style.m_text_rotation &&
    m_alt_tol_resolution == style.m_alt_tol_resolution &&
    m_suppress_arrow1 == style.m_suppress_arrow1 &&
    m_suppress_arrow2 == style.m_suppress_arrow2 &&
    m_textmove_leader == style.m_textmove_leader &&
    m_arclength_sym == style.m_arclength_sym &&
    m_stack_textheight_fraction == style.m_stack_textheight_fraction &&
    m_stack_format == style.m_stack_format &&
    m_alt_round == style.m_alt_round &&
    m_round == style.m_round &&
    m_alt_zero_suppress == style.m_alt_zero_suppress &&
    m_tol_zero_suppress == style.m_tol_zero_suppress &&
    m_zero_suppress == style.m_zero_suppress &&
    m_ang_zero_suppress == style.m_ang_zero_suppress &&

    //m_arrow_type_1 == style.m_arrow_type_1 &&
    //m_arrow_type_2 == style.m_arrow_type_2 &&
    //m_dim_arrow_block1 == style.m_dim_arrow_block1 &&
    //m_dim_arrow_block2 == style.m_dim_arrow_block2 &&

    m_arrow_1 == style.m_arrow_1 &&
    m_arrow_2 == style.m_arrow_2 &&


    CompareValidFields(style)
    )
    return true;
  else
    return false;
}

//////////////////////////////////////////////////////////////////////
//
// ON_Object overrides

bool ON_V5x_DimStyle::IsValid( ON_TextLog* text_log ) const
{
  return ( Name().Length() > 0 && Index() >= 0);
}

void ON_V5x_DimStyle::Dump( ON_TextLog& dump ) const
{
  ON_ModelComponent::Dump(dump);
}


// Called to attach userdata to a dimstyle in a V6 model
// to write it to a V5 file (SaveAs V5)
bool ON_V5x_DimStyle::AttachDimstyleExtra()
{
  ON_DimStyleExtra* pExtra = 0;
  // Get or make userdata
  // Look first so it only gets put on once.
  pExtra = ON_DimStyleExtra::Cast(GetUserData(ON_CLASS_ID(ON_DimStyleExtra)));
  if (pExtra == 0)
  {
    pExtra = new ON_DimStyleExtra;
    if (pExtra)
    {
      if (!AttachUserData(pExtra))
      {
        delete pExtra;
        pExtra = 0;
      }
    }
  }

  if (0 != pExtra)
  {
    // Update all of the values even if the userdata was already there
    pExtra->m_userdata_copycount = 0;
    pExtra->m_tolerance_style = m_tolerance_style;
    pExtra->m_tolerance_resolution = m_tolerance_resolution;
    pExtra->m_tolerance_upper_value = m_tolerance_upper_value;
    pExtra->m_tolerance_lower_value = m_tolerance_lower_value;
    pExtra->m_tolerance_height_scale = m_tolerance_height_scale;
    pExtra->m_baseline_spacing = m_baseline_spacing;
    pExtra->m_bDrawMask = m_bDrawMask;
    pExtra->m_mask_color_source = m_mask_color_source;
    pExtra->m_mask_color = m_mask_color;
    pExtra->m_dimscale = m_dimscale;
    pExtra->m_dimscale_source = m_dimscale_source;
    pExtra->m_parent_dimstyle = ParentId();
    pExtra->m_source_dimstyle = m_source_dimstyle;

    const unsigned int count = (unsigned int)(sizeof(m_field_override) / sizeof(m_field_override[0]));
    if ( 0 == m_field_override_count )
      ClearAllFieldOverrides(); // insure m_field_override[] is initialized.

    pExtra->m_valid_fields.Reserve(ON_DimStyleExtra::eFieldCount);
    pExtra->m_valid_fields.SetCount(ON_DimStyleExtra::eFieldCount);
    pExtra->m_valid_fields.Zero();
    for (int i = 0; i < ON_DimStyleExtra::eFieldCount; i++)
    {
      pExtra->m_valid_fields[i] = (i < count) ? m_field_override[i] : false;
    }
    return true;
  }
  return false;
}

//void ON_V5x_DimStyle::ConsolidateDimstyleExtra()
//{
//  ON_DimStyleExtra* extra = ON_DimStyleExtra::Cast(this->GetUserData(ON_CLASS_ID(ON_DimStyleExtra)));
//  if (extra)
//  {
//    m_tolerance_style = extra->m_tolerance_style;
//    m_tolerance_resolution = extra->m_tolerance_resolution;
//    m_tolerance_upper_value = extra->m_tolerance_upper_value;
//    m_tolerance_lower_value = extra->m_tolerance_lower_value;
//    m_tolerance_height_scale = extra->m_tolerance_height_scale;
//    m_baseline_spacing = extra->m_baseline_spacing;
//    m_bDrawMask = extra->m_bDrawMask;
//    m_mask_color_source = extra->m_mask_color_source;
//    m_mask_color = extra->m_mask_color;
//    m_dimscale = extra->m_dimscale;
//    m_dimscale_source = extra->m_dimscale_source;
//    m_parent_dimstyle = extra->m_parent_dimstyle;
//    m_source_dimstyle = extra->m_source_dimstyle;
//
//    if ( 0 == m_field_override_count )
//      ClearAllFieldOverrides(); // insure m_field_override[] is initialized
//    int count = (int)(sizeof(m_field_override)/sizeof(m_field_override[0]));
//    if (count > extra->m_valid_fields.Count())
//      count = extra->m_valid_fields.Count();
//    for (int i = 0; i < count; i++)
//      m_field_override[i] = extra->m_valid_fields[i];
//
//      DetachUserData(extra);
//      delete extra;
//  }
//}

bool ON_V5x_DimStyle::Write(
  ON_BinaryArchive& file // serialize definition to binary archive
  ) const
{
  if (file.Archive3dmVersion() >= 60)
  {
    ON_ERROR("Never save V5 dimstyles in a V6 file.");
    //// Write v6 and beyond
    //return Write_v6(file);
    return false;
  }
  
  if (file.Archive3dmVersion() == 5 || file.Archive3dmVersion() == 50)
  {
    // See if we need to write some user data for the v5 file
    const_cast<ON_V5x_DimStyle*>(this)->AttachDimstyleExtra();
  }

  const bool rc = Write_v5(file) ? true : false;

  return rc;
}


bool ON_V5x_DimStyle::Read(
  ON_BinaryArchive& file // restore definition from binary archive
  )
{
  // ON_V5x_DimStyle::Default cannot be a static member
  // because we cannot control order of static initialization on Mac / Clang
  // and all public statics in opennurbs_statics.cpp need to be initialized
  // before the obsolete ON_V5x_DimStyle can be initialzed.
  // The ON_V5x_DimStyle::Default() function is called only when files are 
  // read and by that time ON_DimStyle::Default exists.
  const ON_V5x_DimStyle unset_dimstyle(ON::LengthUnitSystem::None, ON_DimStyle::Unset);
  *this = unset_dimstyle;

  if (file.Archive3dmVersion() < 60)
    return Internal_Read_v5(file);
  else
  {
    // Read v6 and beyond
    // This is a file saved by a very early version of Rhino 6 WIP
    return Internal_Read_v6(file);
  }
}

bool ON_V5x_DimStyle::Internal_Read_v6(
  ON_BinaryArchive& file // restore definition from binary archive
  )
{
  ClearModelComponentAttributes(ON_ModelComponent::Attributes::AllAttributes);

  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version, &minor_version);

  if (major_version >= 1)
  {
    int dimstyle_index = Index();
    if (rc) rc = file.ReadInt(&dimstyle_index);
    if (rc)
      SetIndex(dimstyle_index);
    ON_wString dimstyle_name;
    if (rc) rc = file.ReadString(dimstyle_name);
    if (rc) SetName(dimstyle_name);

    if (rc) rc = file.ReadDouble(&m_extextension);
    if (rc) rc = file.ReadDouble(&m_extoffset);
    if (rc) rc = file.ReadDouble(&m_arrowsize);
    if (rc) rc = file.ReadDouble(&m_centermark);
    if (rc) rc = file.ReadDouble(&m_textgap);

    unsigned int ui = 0;
    if (rc) rc = file.ReadInt(&ui);
    if (rc) m_dimstyle_textalign = (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode)ui;
    if (rc) rc = file.ReadInt(&m_arrowtype);
    if (rc) rc = file.ReadInt(&m_angularunits);
    if (rc) rc = file.ReadInt(&m_lengthformat);
    if (rc) rc = file.ReadInt(&m_angleformat);
    if (rc) rc = file.ReadInt(&m_lengthresolution);
    if (rc) rc = file.ReadInt(&m_angleresolution);
    int text_style_index = ON_UNSET_INT_INDEX;
    if (rc) rc = file.ReadInt(&text_style_index);
    if (rc)
    {
      const ON_TextStyle* text_style = file.ArchiveTextStyleFromArchiveTextStyleIndex(text_style_index);
      if (nullptr != text_style)
        SetV5TextStyle(*text_style);
    }

    if (rc && minor_version < 3 )
      SetId(); // non nil id is required

    if (minor_version >= 1)
      if (rc) rc = file.ReadDouble(&m_textheight);

    // added 1/13/05
    if (minor_version >= 2)
    {
      if (rc) rc = file.ReadDouble(&m_lengthfactor);
      // assume length factor value was junk from buggy .NET user inteface 
      m_lengthfactor = 1.0;

      if (rc) rc = file.ReadString(m_prefix);
      if (rc) rc = file.ReadString(m_suffix);

      if (rc) rc = file.ReadBool(&m_bAlternate);
      if (rc) rc = file.ReadDouble(&m_alternate_lengthfactor);
      if (rc) rc = file.ReadInt(&m_alternate_lengthformat);
      if (rc) rc = file.ReadInt(&m_alternate_lengthresolution);
      if (rc) rc = file.ReadInt(&m_alternate_angleformat);
      if (rc) rc = file.ReadInt(&m_alternate_angleresolution);
      if (rc) rc = file.ReadString(m_alternate_prefix);
      if (rc) rc = file.ReadString(m_alternate_suffix);
      unsigned int not_used = 0;
      if (rc) rc = file.ReadInt(&not_used);  // Obsolete - no longer used

      if (minor_version >= 3)
      {
        ON_UUID dimstyle_id = Id();
        if (rc) rc = file.ReadUuid(dimstyle_id);
        if (rc)
        {
          if (ON_nil_uuid == dimstyle_id)
            dimstyle_id = ON_CreateId(); // non nil id is required
          SetId(dimstyle_id);
        }
      }
    }
    // Added Dec 28, 05 ver 1.4
    if (minor_version >= 4)
      if (rc) rc = file.ReadDouble(&m_dimextension);

    // Added Mar 23 06 ver 1.5
    if (minor_version >= 5)
    {
      if (rc) rc = file.ReadDouble(&m_leaderarrowsize);
      if (rc) rc = file.ReadInt(&m_leaderarrowtype);
      if (rc) rc = file.ReadBool(&m_bSuppressExtension1);
      if (rc) rc = file.ReadBool(&m_bSuppressExtension2);
    }

    // Apr 10, 2014 - V6 - ver 1.6
    // Moved DimstyleExtra userdata fields into main class
    if (minor_version >= 6)
    {
      ON_UUID parent_dimstyle_id = ParentId();
      if (rc) rc = file.ReadUuid(parent_dimstyle_id);
      SetParentId(parent_dimstyle_id);

      ClearAllFieldOverrides();
      ON_SimpleArray<bool> valid_fields;
      if (rc) rc = file.ReadArray(valid_fields);
      unsigned int count = (unsigned int)(sizeof(m_field_override)/sizeof(m_field_override[0]));
      if ( count > valid_fields.UnsignedCount())
        count = valid_fields.UnsignedCount();
      for (unsigned int i = 0; i < count; i++)
      {
        m_field_override[i] = valid_fields[i];
        if ( m_field_override[i] )
          m_field_override_count++;
      }      

      if (rc) rc = file.ReadInt(&m_tolerance_style);
      if (rc) rc = file.ReadInt(&m_tolerance_resolution);

      if (rc) rc = file.ReadDouble(&m_tolerance_upper_value);
      if (rc) rc = file.ReadDouble(&m_tolerance_lower_value);
      if (rc) rc = file.ReadDouble(&m_tolerance_height_scale);

      if (rc) rc = file.ReadDouble(&m_baseline_spacing);

      if (rc) rc = file.ReadBool(&m_bDrawMask);
      if (rc) rc = file.ReadInt(&m_mask_color_source);
      if (rc) rc = file.ReadColor(m_mask_color);

      if (rc) rc = file.ReadDouble(&m_dimscale);
      if (rc) rc = file.ReadInt(&m_dimscale_source);
      m_source_dimstyle = ON_nil_uuid;
      if (rc)
      {
        // The m_source_dimstyle uuid got to the V6 3dm file when it still used V5 dimstyles.
        // But, it was not added correctly.
        // Checking for enough room prevents attempting to read beyond the end of the chunk
        ON_3DM_BIG_CHUNK c;
        if (file.GetCurrentChunk(c) > 0)
        {
          ON__UINT64 len = c.LengthRemaining(file.CurrentPosition());
          if ( 16 == len )
            rc = file.ReadUuid(m_source_dimstyle);
          else
          {
            char buffer[8];
            while (rc && len >= 8)
            {
              rc = file.ReadByte(8, buffer);
              len -= 8;
            }
            while (rc && len > 0)
            {
              rc = file.ReadByte(1, buffer);
              len--;
            }
          }
        }
      }
    }
  }
  else
    rc = false;

  if (rc)
    IfIdIsNilSetId();


  return rc;
}


bool ON_V5x_DimStyle::Write_v5(
       ON_BinaryArchive& file // serialize definition to binary archive
     ) const
{
  // March 22, 2010 - Global DimStyle was obsoleted and moved into DimStyles
  // So now for writing older version files, its multiplied into all distance values
  double ds = 1.0;
  if (file.Archive3dmVersion() < 5)
    ds = DimScale();

  // changed to version 1.4 Dec 28, 05
  // changed to version 1.5 Mar 23, 06
  bool rc = file.Write3dmChunkVersion(1,5);

  if (rc) rc = file.Write3dmReferencedComponentIndex(*this);
  if (rc) rc = file.WriteString(Name());

  if (rc) rc = file.WriteDouble(m_extextension * ds);
  if (rc) rc = file.WriteDouble(m_extoffset * ds);
  if (rc) rc = file.WriteDouble(m_arrowsize * ds);
  if (rc) rc = file.WriteDouble(m_centermark * ds);
  if (rc) rc = file.WriteDouble(m_textgap * ds);
  
  if (rc) rc = file.WriteInt((unsigned int)m_dimstyle_textalign);
  if (rc) rc = file.WriteInt(m_arrowtype);
  if (rc) rc = file.WriteInt(m_angularunits);
  if (rc) rc = file.WriteInt(m_lengthformat);
  if (rc) rc = file.WriteInt(m_angleformat);
  if (rc) rc = file.WriteInt(m_lengthresolution);
  if (rc) rc = file.WriteInt(m_angleresolution);

  // legacy text style index
  // for V5 archives, the text style index = dim style index.
  if (rc) rc = file.Write3dmReferencedComponentIndex(*this);

  if (rc) rc = file.WriteDouble(m_textheight * ds);

  // added 1/13/05 ver 1.2
  if (rc) rc = file.WriteDouble(m_lengthfactor);
  if (rc) rc = file.WriteString(m_prefix);
  if (rc) rc = file.WriteString(m_suffix);

  if (rc) rc = file.WriteBool(m_bAlternate);
  if (rc) rc = file.WriteDouble(m_alternate_lengthfactor);
  if (rc) rc = file.WriteInt(m_alternate_lengthformat);
  if (rc) rc = file.WriteInt(m_alternate_lengthresolution);
  if (rc) rc = file.WriteInt(m_alternate_angleformat);
  if (rc) rc = file.WriteInt(m_alternate_angleresolution);
  if (rc) rc = file.WriteString(m_alternate_prefix);
  if (rc) rc = file.WriteString(m_alternate_suffix);

  unsigned int not_used = 0;
  if (rc) rc = file.WriteInt(not_used);

  // Added 24 October 2005 ver 1.3
  if (rc) rc = file.WriteUuid(Id());

  // Added Dec 28, 05 ver 1.4
  if (rc) rc = file.WriteDouble(m_dimextension * ds);

  // Added Mar 23 06 ver 1.5
  if (rc) rc = file.WriteDouble(m_leaderarrowsize * ds);
  if (rc) rc = file.WriteInt(m_leaderarrowtype);
  if (rc) rc = file.WriteBool(m_bSuppressExtension1);
  if (rc) rc = file.WriteBool(m_bSuppressExtension2);

  return rc;
}

void ON_Internal_FixBogusDimStyleLengthFactor(
  const ON_BinaryArchive& file,
  double& dimstyle_length_factor
)
{
  if (1.0 == dimstyle_length_factor)
    return;
  if (false == ON_IsValid(dimstyle_length_factor))
  {
    dimstyle_length_factor = 1.0;
    return;
  }

  // The .NET Dimstyle interface from Jan - Jun 16 2017, was incorrectly
  // setting m_lengthfactor and making a real mess of things.
  // When correctly used, it is extremely rare for m_lengthfactor to be any value except 1.0
  const unsigned int opennurbs_version = file.ArchiveOpenNURBSVersion();
  unsigned int version_year = 0;
  unsigned int version_month = 0;
  unsigned int version_day_of_month = 0;
  if (ON_VersionNumberParse(opennurbs_version,nullptr,nullptr,&version_year,&version_month,&version_day_of_month,nullptr))
  {
    if (version_year >= 2000 && version_year < 2017)
      return; // before 2017
    if (version_year >= 2018)
      return; // after 2017
    if (version_month >= 8 && version_month <= 12)
      return; // August through December 2017
    if (version_day_of_month >= 6)
      return; // July 6, 2017 through July 31, 2017
  }
  dimstyle_length_factor = 1.0; // fix junky value written from Jan 1, 2017 throught July 5, 2017
}

bool ON_V5x_DimStyle::Internal_Read_v5(
  ON_BinaryArchive& file // restore definition from binary archive
  )
{
  ClearModelComponentAttributes(ON_ModelComponent::Attributes::AllAttributes);

  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);


  if ( major_version >= 1 ) 
  {
    int dimstyle_index = Index();
    if ( rc) rc = file.ReadInt( &dimstyle_index);
    if ( rc )
      SetIndex(dimstyle_index);

    ON_wString dimstyle_name;
    if ( rc) rc = file.ReadString( dimstyle_name);
    if (rc)
      SetName(dimstyle_name);
    
    if ( rc) rc = file.ReadDouble( &m_extextension);
    if ( rc) rc = file.ReadDouble( &m_extoffset);
    if ( rc) rc = file.ReadDouble( &m_arrowsize);
    if ( rc) rc = file.ReadDouble( &m_centermark);
    if ( rc) rc = file.ReadDouble( &m_textgap);
    
    unsigned int ui = 0;
    if (rc) rc = file.ReadInt(&ui);
    if (rc) m_dimstyle_textalign = (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode)ui;
    if ( rc) rc = file.ReadInt( &m_arrowtype);
    if ( rc) rc = file.ReadInt( &m_angularunits);
    if ( rc) rc = file.ReadInt( &m_lengthformat);
    if ( rc) rc = file.ReadInt( &m_angleformat);
    if ( rc) rc = file.ReadInt( &m_lengthresolution);
    if ( rc) rc = file.ReadInt( &m_angleresolution);
    int text_style_index = ON_UNSET_INT_INDEX;
    if ( rc) rc = file.ReadInt( &text_style_index);
    if (rc)
    {
      const ON_TextStyle* text_style = file.ArchiveTextStyleFromArchiveTextStyleIndex(text_style_index);
      if (text_style)
        m_v5_text_style = *text_style;
    }

    if ( rc && minor_version < 3 )
      SetId(); // older versions did not have an id.

    if( minor_version >= 1)
      if ( rc) rc = file.ReadDouble( &m_textheight);

    // added 1/13/05
    if( minor_version >= 2)
    {
      if (rc)
      {
        rc = file.ReadDouble(&m_lengthfactor);
        if (rc)
          ON_Internal_FixBogusDimStyleLengthFactor(file, m_lengthfactor);
      }

      if (rc) rc = file.ReadString( m_prefix);
      if (rc) rc = file.ReadString( m_suffix);

      if (rc) rc = file.ReadBool( &m_bAlternate);
      if (rc) rc = file.ReadDouble(&m_alternate_lengthfactor);
      if (rc)
        ON_Internal_FixBogusDimStyleLengthFactor(file, m_alternate_lengthfactor);

      if (rc) rc = file.ReadInt( &m_alternate_lengthformat);
      if (rc) rc = file.ReadInt( &m_alternate_lengthresolution);
      if (rc) rc = file.ReadInt( &m_alternate_angleformat);
      if (rc) rc = file.ReadInt( &m_alternate_angleresolution);
      if (rc) rc = file.ReadString( m_alternate_prefix);
      if (rc) rc = file.ReadString( m_alternate_suffix);

      unsigned int not_used = 0;
      if (rc) rc = file.ReadInt( &not_used);

      if ( minor_version >= 3 )
      {
        ON_UUID dimstyle_id = Id();
        if (rc) rc = file.ReadUuid(dimstyle_id);
        if (rc)
        {
          if (ON_nil_uuid == dimstyle_id)
            dimstyle_id = ON_CreateId();  // non-nil id is required
          SetId(dimstyle_id);
        }
      }
    }
    // Added Dec 28, 05 ver 1.4
    if( minor_version >= 4)
      if( rc) rc = file.ReadDouble( &m_dimextension);

    // Added Mar 23 06 ver 1.5
    if( minor_version >= 5)
    {
      if (rc) rc = file.ReadDouble( &m_leaderarrowsize);
      if (rc) rc = file.ReadInt( &m_leaderarrowtype);
      if (rc) rc = file.ReadBool( &m_bSuppressExtension1);
      if (rc) rc = file.ReadBool( &m_bSuppressExtension2);
    }
  }
  else
    rc = false;

  if (rc)
    IfIdIsNilSetId();

  return rc;
}

void ON_V5x_DimStyle::EmergencyDestroy()
{
  m_prefix.EmergencyDestroy();
  m_suffix.EmergencyDestroy();
  m_alternate_prefix.EmergencyDestroy();
  m_alternate_suffix.EmergencyDestroy();
}

//////////////////////////////////////////////////////////////////////
//
// Interface

double ON_V5x_DimStyle::ExtExtension() const
{
  return m_extextension;
}

void ON_V5x_DimStyle::SetExtExtension( const double e)
{
  // Allow negative?
  m_extextension = e;
}

double ON_V5x_DimStyle::ExtOffset() const
{
  return m_extoffset;
}

void ON_V5x_DimStyle::SetExtOffset( const double e)
{
  m_extoffset = e;
}

double ON_V5x_DimStyle::ArrowSize() const
{
  return m_arrowsize;
}

void ON_V5x_DimStyle::SetArrowSize( const double e)
{
  m_arrowsize = e;
}

double ON_V5x_DimStyle::LeaderArrowSize() const
{
  return m_leaderarrowsize;
}

void ON_V5x_DimStyle::SetLeaderArrowSize( const double e)
{
  m_leaderarrowsize = e;
}

double ON_V5x_DimStyle::CenterMark() const
{
  return m_centermark;
}

void ON_V5x_DimStyle::SetCenterMark( const double e)
{
  m_centermark = e;
}

ON_INTERNAL_OBSOLETE::V5_TextDisplayMode ON_V5x_DimStyle::TextAlignment() const
{
  return m_dimstyle_textalign;
}

void ON_V5x_DimStyle::SetTextAlignment( ON_INTERNAL_OBSOLETE::V5_TextDisplayMode a)
{
  m_dimstyle_textalign = a;
}

int ON_V5x_DimStyle::ArrowType() const
{
  return m_arrowtype;
}

void ON_V5x_DimStyle::SetArrowType( eArrowType a)
{
  m_arrowtype = a;
}

int ON_V5x_DimStyle::LeaderArrowType() const
{
  return m_leaderarrowtype;
}

void ON_V5x_DimStyle::SetLeaderArrowType( eArrowType a)
{
  m_leaderarrowtype = a;
}

int ON_V5x_DimStyle::AngularUnits() const
{
  return m_angularunits;
}

void ON_V5x_DimStyle::SetAngularUnits( int u)
{
  m_angularunits = u;
}

int ON_V5x_DimStyle::LengthFormat() const
{
  return m_lengthformat;
}

void ON_V5x_DimStyle::SetLengthFormat( int f)
{
  m_lengthformat = f;
}

int ON_V5x_DimStyle::AngleFormat() const
{
  return m_angleformat;
}

void ON_V5x_DimStyle::SetAngleFormat( int f)
{
  m_angleformat = f;
}

int ON_V5x_DimStyle::LengthResolution() const
{
  return m_lengthresolution;
}

void ON_V5x_DimStyle::SetLengthResolution( int r)
{
  if( r >= 0 && r < 16)
  {
    m_lengthresolution = r;
  }
}

int ON_V5x_DimStyle::AngleResolution() const
{
  return m_angleresolution;
}

void ON_V5x_DimStyle::SetAngleResolution( int r)
{
  if( r >= 0 && r < 16)
  {
    m_angleresolution = r;
  }
}

const ON_TextStyle& ON_V5x_DimStyle::V5TextStyle() const
{
  return m_v5_text_style;
}

void ON_V5x_DimStyle::SetV5TextStyle(
  const ON_TextStyle& text_style
  )
{
  m_v5_text_style = text_style;
}

double ON_V5x_DimStyle::TextGap() const
{
  return m_textgap;
}

void ON_V5x_DimStyle::SetTextGap( double gap)
{
  if( gap >= 0.0)
  {
    m_textgap = gap;
  }
}

double ON_V5x_DimStyle::TextHeight() const
{
  return m_textheight;
}

void ON_V5x_DimStyle::SetTextHeight( double height)
{
  if( ON_IsValid( height) && height > ON_SQRT_EPSILON)
  {
    m_textheight = height;
  }
}

double ON_V5x_DimStyle::LengthFactor() const
{
  return m_lengthfactor;
}

void ON_V5x_DimStyle::SetLengthFactor( double factor)
{
  m_lengthfactor = factor;
}

bool ON_V5x_DimStyle::Alternate() const
{
  return m_bAlternate;
}
void ON_V5x_DimStyle::SetAlternate( bool bAlternate)
{
  m_bAlternate = bAlternate;
}

double ON_V5x_DimStyle::AlternateLengthFactor() const
{
  return m_alternate_lengthfactor;
}

void ON_V5x_DimStyle::SetAlternateLengthFactor( double factor)
{
  m_alternate_lengthfactor = factor;
}

int ON_V5x_DimStyle::AlternateLengthFormat() const
{
  return m_alternate_lengthformat;
}
void ON_V5x_DimStyle::SetAlternateLengthFormat( int format)
{
  m_alternate_lengthformat = format;
}

int ON_V5x_DimStyle::AlternateLengthResolution() const
{
  return m_alternate_lengthresolution;
}
void ON_V5x_DimStyle::SetAlternateLengthResolution( int resolution)
{
  m_alternate_lengthresolution = resolution;
}

int ON_V5x_DimStyle::AlternateAngleFormat() const
{
  return m_alternate_angleformat;
}
void ON_V5x_DimStyle::SetAlternateAngleFormat( int format)
{
  m_alternate_angleformat = format;
}

int ON_V5x_DimStyle::AlternateAngleResolution() const
{
  return m_alternate_angleresolution;
}
void ON_V5x_DimStyle::SetAlternateAngleResolution( int resolution)
{
  m_alternate_angleresolution = resolution;
}

void ON_V5x_DimStyle::GetPrefix( ON_wString& prefix) const
{
  prefix = m_prefix;
}
const wchar_t* ON_V5x_DimStyle::Prefix() const
{
  return static_cast< const wchar_t* >(m_prefix);
}
void ON_V5x_DimStyle::SetPrefix( wchar_t* prefix)
{
  m_prefix = prefix;
}
void ON_V5x_DimStyle::SetPrefix( const wchar_t* prefix)
{
  m_prefix = prefix;
}

void ON_V5x_DimStyle::GetSuffix( ON_wString& suffix) const
{
  suffix = m_suffix;
}
const wchar_t* ON_V5x_DimStyle::Suffix() const
{
  return static_cast< const wchar_t* >(m_suffix);
}
void ON_V5x_DimStyle::SetSuffix( wchar_t* suffix)
{
  m_suffix = suffix;
}
void ON_V5x_DimStyle::SetSuffix( const wchar_t* suffix)
{
  m_suffix = suffix;
}

void ON_V5x_DimStyle::GetAlternatePrefix( ON_wString& prefix) const
{
  prefix = m_alternate_prefix;
}
const wchar_t* ON_V5x_DimStyle::AlternatePrefix() const
{
  return static_cast< const wchar_t* >(m_alternate_prefix);
}
void ON_V5x_DimStyle::SetAlternatePrefix( wchar_t* prefix)
{
  m_alternate_prefix = prefix;
}
void ON_V5x_DimStyle::SetAlternatePrefix( const wchar_t* prefix)
{
  m_alternate_prefix = prefix;
}

void ON_V5x_DimStyle::GetAlternateSuffix( ON_wString& suffix) const
{
  suffix = m_alternate_suffix;
}
const wchar_t* ON_V5x_DimStyle::AlternateSuffix() const
{
  return static_cast< const wchar_t* >(m_alternate_suffix);
}
void ON_V5x_DimStyle::SetAlternateSuffix( wchar_t* suffix)
{
  m_alternate_suffix = suffix;
}
void ON_V5x_DimStyle::SetAlternateSuffix( const wchar_t* suffix)
{
  m_alternate_suffix = suffix;
}

bool ON_V5x_DimStyle::SuppressExtension1() const
{
  return m_bSuppressExtension1;
}
void ON_V5x_DimStyle::SetSuppressExtension1( bool suppress)
{
  m_bSuppressExtension1 = suppress;
}
bool ON_V5x_DimStyle::SuppressExtension2() const
{
  return m_bSuppressExtension2;
}
void ON_V5x_DimStyle::SetSuppressExtension2( bool suppress)
{
  m_bSuppressExtension2 = suppress;
}

// ver 1.4, Dec 28, 05
double ON_V5x_DimStyle::DimExtension() const
{
  return m_dimextension;
}

void ON_V5x_DimStyle::SetDimExtension( const double e)
{
  // Allow negative?
  m_dimextension = e;
}

// ver 2.0 v6

void ON_V5x_DimStyle::SetExtensionLineColorSource(const ON::object_color_source src)
{
  m_ext_line_color_source = (unsigned char)src;
}
ON::object_color_source ON_V5x_DimStyle::ExtensionLineColorSource() const
{
  return (ON::object_color_source)m_ext_line_color_source;
}
void ON_V5x_DimStyle::SetDimensionLineColorSource(const ON::object_color_source src)
{
  m_dim_line_color_source = (unsigned char)src;
}
ON::object_color_source ON_V5x_DimStyle::DimensionLineColorSource() const
{
  return (ON::object_color_source)m_dim_line_color_source;
}
void ON_V5x_DimStyle::SetArrowColorSource(const ON::object_color_source src)
{
  m_arrow_color_source = (unsigned char)src;
}
ON::object_color_source ON_V5x_DimStyle::ArrowColorSource() const
{
  return (ON::object_color_source)m_arrow_color_source;
}
void ON_V5x_DimStyle::SetExtensionLineColor(ON_Color c)
{
  m_ext_line_color = c;
}
ON_Color ON_V5x_DimStyle::ExtensionLineColor() const
{
  return m_ext_line_color;
}
void ON_V5x_DimStyle::SetDimensionLineColor(ON_Color c)
{
  m_dim_line_color = c;
}
ON_Color ON_V5x_DimStyle::DimensionLineColor() const
{
  return m_dim_line_color;
}
void ON_V5x_DimStyle::SetArrowColor(ON_Color c)
{
  m_arrow_color = c;
}
ON_Color ON_V5x_DimStyle::ArrowColor() const
{
  return m_arrow_color;
}
void ON_V5x_DimStyle::SetTextColor(ON_Color c)
{
  m_text_color = c;
}
ON_Color ON_V5x_DimStyle::TextColor() const
{
  return m_text_color;
}

void ON_V5x_DimStyle::SetExtensionLinePlotColorSource(const ON::plot_color_source src)
{
  m_ext_line_plot_color_source = (unsigned char)src;
}
ON::plot_color_source ON_V5x_DimStyle::ExtensionLinePlotColorSource() const
{
  return (ON::plot_color_source)m_ext_line_plot_color_source;
}
void ON_V5x_DimStyle::SetDimensionLinePlotColorSource(const ON::plot_color_source src)
{
  m_dim_line_plot_color_source = (unsigned char)src;
}
ON::plot_color_source ON_V5x_DimStyle::DimensionLinePlotColorSource() const
{
  return (ON::plot_color_source)m_dim_line_plot_color_source;
}
void ON_V5x_DimStyle::SetArrowPlotColorSource(const ON::plot_color_source src)
{
  m_arrow_plot_color_source = (unsigned char)src;
}
ON::plot_color_source ON_V5x_DimStyle::ArrowPlotColorSource() const
{
  return (ON::plot_color_source)m_arrow_plot_color_source;
}
void ON_V5x_DimStyle::SetExtensionLinePlotColor(ON_Color c)
{
  m_ext_line_plot_color = c;
}
ON_Color ON_V5x_DimStyle::ExtensionLinePlotColor() const
{
  return m_ext_line_plot_color;
}
void ON_V5x_DimStyle::SetDimensionLinePlotColor(ON_Color c)
{
  m_dim_line_plot_color = c;
}
ON_Color ON_V5x_DimStyle::DimensionLinePlotColor() const
{
  return m_dim_line_plot_color;
}
void ON_V5x_DimStyle::SetArrowPlotColor(ON_Color c)
{
  m_arrow_plot_color = c;
}
ON_Color ON_V5x_DimStyle::ArrowPlotColor() const
{
  return m_arrow_plot_color;
}
void ON_V5x_DimStyle::SetTextPlotColor(ON_Color c)
{
  m_text_plot_color = c;
}
ON_Color ON_V5x_DimStyle::TextPlotColor() const
{
  return m_text_plot_color;
}

void ON_V5x_DimStyle::SetExtensionLinePlotWeightSource(const ON::plot_weight_source src)
{
  m_ext_line_plot_weight_source = (unsigned char)src;
}
ON::plot_weight_source ON_V5x_DimStyle::ExtensionLinePlotWeightSource() const
{
  return (ON::plot_weight_source)m_ext_line_plot_weight_source;
}
void ON_V5x_DimStyle::SetDimensionLinePlotWeightSource(const ON::plot_weight_source src)
{
  m_dim_line_plot_weight_source = (unsigned char)src;
}
ON::plot_weight_source ON_V5x_DimStyle::DimensionLinePlotWeightSource() const
{
  return (ON::plot_weight_source)m_dim_line_plot_weight_source;
}
void ON_V5x_DimStyle::SetExtensionLinePlotWeight(double w)
{
  m_ext_line_plot_weight_mm = w;
}
double ON_V5x_DimStyle::ExtensionLinePlotWeight() const
{
  return m_ext_line_plot_weight_mm;
}
void ON_V5x_DimStyle::SetDimensionLinePlotWeight(double w)
{
  m_dim_line_plot_weight_mm = w;
}
double ON_V5x_DimStyle::DimensionLinePlotWeight() const
{
  return m_dim_line_plot_weight_mm;
}

void ON_V5x_DimStyle::SetFixedExtensionLen(double l)
{
  m_fixed_extension_len = l;
}

double ON_V5x_DimStyle::FixedExtensionLen() const
{
  return m_fixed_extension_len;
}

void ON_V5x_DimStyle::SetFixedExtensionLenOn(bool on)
{
  m_fixed_extension_len_on = on;
}

bool ON_V5x_DimStyle::FixedExtensionLenOn() const
{
  return m_fixed_extension_len_on;
}

void ON_V5x_DimStyle::SetTextRotation(double r)
{
  m_text_rotation = r;
}
double ON_V5x_DimStyle::TextRotation() const
{
  return m_text_rotation;
}

void ON_V5x_DimStyle::SetAlternateToleranceResolution(int r)
{
  m_alt_tol_resolution = r;
}
int ON_V5x_DimStyle::AlternateToleranceResolution() const
{
  return m_alt_tol_resolution;
}

void ON_V5x_DimStyle::SetSuppressArrow1(bool s)
{
  m_suppress_arrow1 = s;
}
bool ON_V5x_DimStyle::SuppressArrow1() const
{
  return m_suppress_arrow1;
}
void ON_V5x_DimStyle::SetSuppressArrow2(bool s)
{
  m_suppress_arrow2 = s;
}
bool ON_V5x_DimStyle::SuppressArrow2() const
{
  return m_suppress_arrow2;
}
void ON_V5x_DimStyle::SetTextMoveLeader(int m)
{
  m_textmove_leader = m;
}
int ON_V5x_DimStyle::TextMoveLeader() const
{
  return m_textmove_leader;
}
void ON_V5x_DimStyle::SetArcLengthSymbol(int m)
{
  m_arclength_sym = m;
}
int ON_V5x_DimStyle::ArcLengthSymbol() const
{
  return m_arclength_sym;
}
void ON_V5x_DimStyle::SetStackFractionFormat(int f)
{
  if (0 <= f && 2 >= f)
    m_stack_format = f;
}
int ON_V5x_DimStyle::StackFractionFormat() const
{
  return m_stack_format;
}
void ON_V5x_DimStyle::SetStackHeightFraction(double f)
{
  m_stack_textheight_fraction = f;
}
double ON_V5x_DimStyle::StackHeightFraction() const
{
  return m_stack_textheight_fraction;
}
void ON_V5x_DimStyle::SetRoundOff(double r)
{
  m_round = r;
}
double ON_V5x_DimStyle::RoundOff() const
{
  return m_round;
}
void ON_V5x_DimStyle::SetAlternateRoundOff(double r)
{
  m_alt_round = r;
}
double ON_V5x_DimStyle::AlternateRoundOff() const
{
  return m_alt_round;
}
void ON_V5x_DimStyle::SetZeroSuppress(int s)
{
  m_zero_suppress = s;
}
int ON_V5x_DimStyle::ZeroSuppress() const
{
  return m_zero_suppress;
}
void ON_V5x_DimStyle::SetAlternateZeroSuppress(int s)
{
  m_alt_zero_suppress = s;
}
int ON_V5x_DimStyle::AlternateZeroSuppress() const
{
  return m_alt_zero_suppress;
}
void ON_V5x_DimStyle::SetToleranceZeroSuppress(int s)
{
  m_tol_zero_suppress = s;
}
int ON_V5x_DimStyle::ToleranceZeroSuppress() const
{
  return m_tol_zero_suppress;
}
void ON_V5x_DimStyle::SetAngleZeroSuppress(int s)
{
  m_ang_zero_suppress = s;
}
int ON_V5x_DimStyle::AngleZeroSuppress() const
{
  return m_ang_zero_suppress;
}
void ON_V5x_DimStyle::SetAlternateBelow(bool below)
{
  m_alt_below = below;
}
bool ON_V5x_DimStyle::AlternateBelow() const
{
  return m_alt_below;
}
void ON_V5x_DimStyle::SetArrowType1(ON_Arrowhead::arrow_type type)
{
  m_arrow_1.SetArrowheadType(type);
}
ON_Arrowhead::arrow_type ON_V5x_DimStyle::ArrowType1() const
{
  return m_arrow_1.ArrowheadType();
}
void ON_V5x_DimStyle::SetArrowType2(ON_Arrowhead::arrow_type type)
{
  m_arrow_2.SetArrowheadType(type);
}
ON_Arrowhead::arrow_type ON_V5x_DimStyle::ArrowType2() const
{
  return m_arrow_2.ArrowheadType();
}
void ON_V5x_DimStyle::SetArrowBlockId1(ON_UUID id)
{
  m_arrow_1.SetArrowBlockId(id);
}
ON_UUID ON_V5x_DimStyle::ArrowBlockId1() const
{
  return m_arrow_1.ArrowBlockId();
}
void ON_V5x_DimStyle::SetArrowBlockId2(ON_UUID id)
{
  m_arrow_2.SetArrowBlockId(id);
}
ON_UUID ON_V5x_DimStyle::ArrowBlockId2() const
{
  return m_arrow_2.ArrowBlockId();
}
const ON_Arrowhead& ON_V5x_DimStyle::Arrowhead1() const
{
  return m_arrow_1;
}
const ON_Arrowhead& ON_V5x_DimStyle::Arrowhead2() const
{
  return m_arrow_2;
}

//--------------------------------------
// ON_DimStyleExtra access functions
// Added for v5 5/01/07 LW


bool ON_V5x_DimStyle::IsFieldOverride(ON_V5x_DimStyle::Field field_id) const
{
  const unsigned int field_index = static_cast<unsigned int>(field_id);
  if (m_field_override_count > 0 &&
    field_index < (unsigned int)(static_cast<unsigned int>(sizeof(m_field_override) / sizeof(m_field_override[0])))
    )
  {
    return m_field_override[field_index];
  }

  return false;
}

void ON_V5x_DimStyle::SetFieldOverride(ON_V5x_DimStyle::Field field_id, bool bOverride)
{
  bOverride = bOverride ? true : false;
  if (m_field_override_count > 0 || bOverride)
  {
    if (bOverride && 0 == m_field_override_count)
    {
      // Insure m_field_override[] is initialized.
      ClearAllFieldOverrides();
    }
    if (static_cast<unsigned int>(field_id) < static_cast<unsigned int>(sizeof(m_field_override) / sizeof(m_field_override[0])))
    {
      if (m_field_override[(int)field_id] != bOverride)
      {
        if (bOverride)
          m_field_override_count++;
        else
          m_field_override_count--;
        m_field_override[(int)field_id] = bOverride;
      }
    }
  }
}


void ON_V5x_DimStyle::ClearAllFieldOverrides()
{
  m_field_override_count = 0;
  memset(m_field_override, 0, sizeof(m_field_override));
}


bool ON_V5x_DimStyle::HasOverrides() const
{
  return (m_field_override_count > 0);
}

bool ON_V5x_DimStyle::OverrideFields(const ON_V5x_DimStyle& src, const ON_V5x_DimStyle& parent)
{
  // NOTE WELL:
  //  "this" could be src or parent, so do not modify member values until they are not longer needed.

  const unsigned int count = (unsigned int)(sizeof(m_field_override)/sizeof(m_field_override[0]));

  unsigned int field_override_count = 0;

  for(unsigned int i = 0; i < count; i++)
  {
    const bool bFromSrc = (src.m_field_override_count > 0 && src.m_field_override[i]);
    m_field_override[i] = bFromSrc;
    if ( bFromSrc )
      field_override_count++;
    const ON_V5x_DimStyle* copyfrom = bFromSrc ? (&src) : (&parent);

    if ( this == copyfrom )
      continue;

    switch((Field)i)
    {
    case Field::fn_extextension:
      SetExtExtension(copyfrom->ExtExtension());
      break;
    case Field::fn_extoffset:
      SetExtOffset(copyfrom->ExtOffset());
      break;
    case Field::fn_arrowsize:
      SetArrowSize(copyfrom->ArrowSize());
      break;
    case Field::fn_centermark:
      SetCenterMark(copyfrom->CenterMark());
      break;
    case Field::fn_textgap:
      SetTextGap(copyfrom->TextGap());
      break;
    case Field::fn_textheight:
      SetTextHeight(copyfrom->TextHeight());
      break;
    case Field::fn_textalign:
      SetTextAlignment(copyfrom->TextAlignment());
      break;
    case Field::fn_arrowtype:
      SetArrowType((eArrowType)copyfrom->ArrowType());
      break;
    case Field::fn_angularunits:
      SetAngularUnits((eArrowType)copyfrom->AngularUnits());
      break;
    case Field::fn_lengthformat:
      SetLengthFormat(copyfrom->LengthFormat());
      break;
    case Field::fn_angleformat:
      SetAngleFormat(copyfrom->AngleFormat());
      break;
    case Field::fn_angleresolution:
      SetAngleResolution(copyfrom->AngleResolution());
      break;
    case Field::fn_lengthresolution:
      SetLengthResolution(copyfrom->LengthResolution());
      break;
    case Field::fn_fontindex:
      SetV5TextStyle(copyfrom->V5TextStyle());
      break;
    case Field::fn_lengthfactor:
      SetLengthFactor(copyfrom->LengthFactor());
      break;
    case Field::fn_bAlternate:
      SetAlternate(copyfrom->Alternate());
      break;
    case Field::fn_alternate_lengthfactor:
      SetAlternateLengthFactor(copyfrom->AlternateLengthFactor());
      break;
    case Field::fn_alternate_lengthformat:
      SetAlternateLengthFormat(copyfrom->AlternateLengthFormat());
      break;
    case Field::fn_alternate_lengthresolution:
      SetAlternateLengthResolution(copyfrom->AlternateLengthResolution());
      break;
    case Field::fn_alternate_angleformat:
      SetAlternateAngleFormat(copyfrom->AlternateAngleFormat());
      break;
    case Field::fn_alternate_angleresolution:
      SetAlternateAngleResolution(copyfrom->AlternateAngleResolution());
      break;
    case Field::fn_prefix:
      SetPrefix(copyfrom->Prefix());
      break;
    case Field::fn_suffix:
      SetSuffix(copyfrom->Suffix());
      break;
    case Field::fn_alternate_prefix:
      SetAlternatePrefix(copyfrom->AlternatePrefix());
      break;
    case Field::fn_alternate_suffix:
      SetAlternateSuffix(copyfrom->AlternateSuffix());
      break;
    case Field::fn_dimextension:
      SetDimExtension(copyfrom->DimExtension());
      break;
    case Field::fn_leaderarrowsize:
      SetLeaderArrowSize(copyfrom->LeaderArrowSize());
      break;
    case Field::fn_leaderarrowtype:
      SetLeaderArrowType((eArrowType)copyfrom->LeaderArrowType());
      break;
    case Field::fn_suppressextension1:
      SetSuppressExtension1(copyfrom->SuppressExtension1());
      break;
    case Field::fn_suppressextension2:
      SetSuppressExtension2(copyfrom->SuppressExtension2());
      break;
    case Field::fn_tolerance_style:
      SetToleranceStyle(copyfrom->ToleranceStyle());
      break;
    case Field::fn_tolerance_resolution:
      SetToleranceResolution(copyfrom->ToleranceResolution());
      break;
    case Field::fn_tolerance_upper_value:
      SetToleranceUpperValue(copyfrom->ToleranceUpperValue());
      break;
    case Field::fn_tolerance_lower_value:
      SetToleranceLowerValue(copyfrom->ToleranceLowerValue());
      break;
    case Field::fn_tolerance_height_scale:
      SetToleranceHeightScale(copyfrom->ToleranceHeightScale());
      break;
    case Field::fn_baseline_spacing:
      SetBaselineSpacing(copyfrom->BaselineSpacing());
      break;
    case Field::fn_draw_mask:
      SetDrawTextMask(copyfrom->DrawTextMask());
      break;
    case Field::fn_mask_color_source:
      SetMaskColorSource(copyfrom->MaskColorSource());
      break;
    case Field::fn_mask_color:
      SetMaskColor(copyfrom->MaskColor());
      break;
    case Field::fn_dimscale:
      SetDimScale(copyfrom->DimScale());
      break;
    case Field::fn_dimscale_source:
      SetDimScaleSource(copyfrom->DimScaleSource());
      break;

    case Field::fn_fixed_extension_len:
      SetFixedExtensionLen(copyfrom->FixedExtensionLen());
      break;
    case Field::fn_fixed_extension_on:
      SetFixedExtensionLenOn(copyfrom->FixedExtensionLenOn());
      break;
    case Field::fn_text_rotation:
      SetTextRotation(copyfrom->TextRotation());
      break;
    case Field::fn_tolerance_alt_resolution:
      SetAlternateToleranceResolution(copyfrom->AlternateToleranceResolution());
      break;
    case Field::fn_tolerance_textheight_fraction:
      SetToleranceHeightScale(copyfrom->ToleranceHeightScale());
      break;
    case Field::fn_suppress_arrow1:
      SetSuppressArrow1(copyfrom->SuppressArrow1());
      break;
    case Field::fn_suppress_arrow2:
      SetSuppressArrow2(copyfrom->SuppressArrow2());
      break;
    case Field::fn_textmove_leader:
      SetTextMoveLeader(copyfrom->TextMoveLeader());
      break;
    case Field::fn_arclength_sym:
      SetArcLengthSymbol(copyfrom->ArcLengthSymbol());
      break;
    case Field::fn_stack_textheight_fraction:
      SetStackHeightFraction(copyfrom->StackHeightFraction());
      break;
    case Field::fn_stack_format:
      SetStackFractionFormat(copyfrom->StackFractionFormat());
      break;
    case Field::fn_alt_round:
      SetAlternateRoundOff(copyfrom->AlternateRoundOff());
      break;
    case Field::fn_round:
      SetRoundOff(copyfrom->RoundOff());
      break;
    case Field::fn_alt_zero_suppress:
      SetAlternateZeroSuppress(copyfrom->AlternateZeroSuppress());
      break;
    case Field::fn_tol_zero_suppress:
      SetToleranceZeroSuppress(copyfrom->ToleranceZeroSuppress());
      break;
    case Field::fn_ang_zero_suppress:
      SetAngleZeroSuppress(copyfrom->AngleZeroSuppress());
      break;
    case Field::fn_zero_suppress:
      SetZeroSuppress(copyfrom->ZeroSuppress());
      break;
    case Field::fn_alt_below:
      SetAlternateBelow(copyfrom->AlternateBelow());
      break;
    case Field::fn_dim_arrow_type1:
      SetArrowType1(copyfrom->ArrowType1());
      break;
    case Field::fn_dim_arrow_type2:
      SetArrowType2(copyfrom->ArrowType2());
      break;
    case Field::fn_dim_arrow_blockname1:
      SetArrowBlockId1(copyfrom->ArrowBlockId1());
      break;
    case Field::fn_dim_arrow_blockname2:
      SetArrowBlockId2(copyfrom->ArrowBlockId2());
      break;
    default:
      break;
    }
  }

  m_field_override_count = field_override_count;

  return true;
}

bool ON_V5x_DimStyle::InheritFields(const ON_V5x_DimStyle& parent)
{
  OverrideFields(*this,parent);
  return (m_field_override_count < ON_DimStyle::FieldCount);
}

bool ON_V5x_DimStyle::IsChildDimstyle() const
{
  if(ParentId() != ON_nil_uuid)
    return true;
  else
    return false;
}

bool ON_V5x_DimStyle::IsChildOf(const ON_UUID& parent_uuid) const
{
  if(parent_uuid != ON_nil_uuid && ParentId() == parent_uuid)
    return true;
  else
    return false;
}

//void ON_V5x_DimStyle::SetParentId(ON_UUID parent_id)
//{
//  m_parent_dimstyle = parent_id;
//}
//
//ON_UUID ON_V5x_DimStyle::ParentId() const
//{
//  return m_parent_dimstyle;
//}

// Tolerances
// Tolerance style
//  0: None
//  1: Symmetrical
//  2: Deviation
//  3: Limits
//  4: Basic
int ON_V5x_DimStyle::ToleranceStyle() const
{
  return m_tolerance_style;
}

int ON_V5x_DimStyle::ToleranceResolution() const
{
  return m_tolerance_resolution;
}

double ON_V5x_DimStyle::ToleranceUpperValue() const
{
  return m_tolerance_upper_value;
}

double ON_V5x_DimStyle::ToleranceLowerValue() const
{
  return m_tolerance_lower_value;
}

double ON_V5x_DimStyle::ToleranceHeightScale() const
{
  return m_tolerance_height_scale;
}

double ON_V5x_DimStyle::BaselineSpacing() const
{
  return m_baseline_spacing;
}

//static 
int ON_V5x_DimStyle::DefaultToleranceStyle()
{
  return 0;
}

//static 
int ON_V5x_DimStyle::DefaultToleranceResolution()
{
  return 4;
}

//static 
double ON_V5x_DimStyle::DefaultToleranceUpperValue()
{
  return 0.0;
}

//static 
double ON_V5x_DimStyle::DefaultToleranceLowerValue()
{
  return 0.0;
}

//static 
double ON_V5x_DimStyle::DefaultToleranceHeightScale()
{
  return 1.0;
}

//static 
double ON_V5x_DimStyle::DefaultBaselineSpacing()
{
  return 1.0;
}

// static
bool ON_V5x_DimStyle::DefaultDrawTextMask()
{
  return false;
}

// static
int ON_V5x_DimStyle::DefaultMaskColorSource()
{
  return 0;
}

// static
ON_Color ON_V5x_DimStyle::DefaultMaskColor()
{
  return ON_Color(255, 255, 255);
}

// static
double ON_V5x_DimStyle::DefaultDimScale()
{
  return 1.0;
}

// static
int ON_V5x_DimStyle::DefaultDimScaleSource()
{
  return 0;
}


//-------------------
void ON_V5x_DimStyle::Scale(double scale)
{
  if (ON_IsValid(scale) && scale > ON_SQRT_EPSILON && 1.0 != scale)
  {
    m_extextension *= scale;
    m_extoffset *= scale;
    m_arrowsize *= scale;
    m_centermark *= scale;
    m_textgap *= scale;
    m_textheight *= scale;
    m_dimextension *= scale;
    m_leaderarrowsize *= scale;
    m_baseline_spacing *= scale;
  }
}

void ON_V5x_DimStyle::SetToleranceStyle(int style)
{
  if (style >= tsMin && style <= tsMax)
    m_tolerance_style = style;
}

void ON_V5x_DimStyle::SetToleranceResolution(int resolution)
{
  if (resolution >= 0 && resolution < 16)
    m_tolerance_resolution = resolution;
}

void ON_V5x_DimStyle::SetToleranceUpperValue(double upper_value)
{
  if (ON_IsValid(upper_value))
    m_tolerance_upper_value = upper_value;
}

void ON_V5x_DimStyle::SetToleranceLowerValue(double lower_value)
{
  if (ON_IsValid(lower_value))
    m_tolerance_lower_value = lower_value;
}

void ON_V5x_DimStyle::SetToleranceHeightScale(double scale)
{
  if (ON_IsValid(scale) && scale > ON_SQRT_EPSILON)
    m_tolerance_height_scale = scale;
}

void ON_V5x_DimStyle::SetBaselineSpacing(double spacing)
{
  if (ON_IsValid(spacing) && spacing > ON_SQRT_EPSILON)
    m_baseline_spacing = spacing;
}

bool ON_V5x_DimStyle::DrawTextMask() const
{
  return m_bDrawMask;
}

void ON_V5x_DimStyle::SetDrawTextMask(bool bDraw)
{
  m_bDrawMask = bDraw ? true : false;
}

int ON_V5x_DimStyle::MaskColorSource() const
{
  return m_mask_color_source;
}

void ON_V5x_DimStyle::SetMaskColorSource(int source)
{
  if (source == 1)
    m_mask_color_source = 1;
  else
    m_mask_color_source = 0;
}

ON_Color ON_V5x_DimStyle::MaskColor() const
{
  return m_mask_color;
}

void ON_V5x_DimStyle::SetMaskColor(ON_Color color)
{
  m_mask_color = color;
}

double ON_V5x_DimStyle::MaskOffsetFactor() const
{
  if (m_textheight != 0.0)
    return 0.5 * m_textgap / m_textheight;
  else
    return 0.0;
}

void ON_V5x_DimStyle::SetDimScale(double scale)
{
  if (ON_IsValid(scale))
    m_dimscale = scale;
}

double ON_V5x_DimStyle::DimScale() const
{
  return m_dimscale;
}

void ON_V5x_DimStyle::SetDimScaleSource(int source)
{
  m_dimscale_source = source;
}

int ON_V5x_DimStyle::DimScaleSource() const
{
  return m_dimscale_source;
}

void ON_V5x_DimStyle::SetSourceDimstyle(ON_UUID source_uuid)
{
  // Can be ON_nil_uuid
  m_source_dimstyle = source_uuid;
}

ON_UUID ON_V5x_DimStyle::SourceDimstyle() const
{
  return m_source_dimstyle;
}

// returns true if they are the same
bool ON_V5x_DimStyle::CompareFields(const ON_V5x_DimStyle& other) const
{
  if(
    (m_extextension != other.m_extextension) ||
    (m_extoffset != other.m_extoffset) ||
    (m_arrowsize != other.m_arrowsize) ||
    (m_centermark != other.m_centermark) ||
    (m_textgap != other.m_textgap) ||
    (m_textheight != other.m_textheight) ||
    (m_dimstyle_textalign != other.m_dimstyle_textalign) ||
    (m_arrowtype != other.m_arrowtype) ||
    (m_angularunits != other.m_angularunits) ||
    (m_lengthformat != other.m_lengthformat) ||
    (m_angleformat != other.m_angleformat) ||
    (m_angleresolution != other.m_angleresolution) ||
    (m_lengthresolution != other.m_lengthresolution) ||
    (m_v5_text_style.Font().ManagedFontSerialNumber() != other.m_v5_text_style.Font().ManagedFontSerialNumber()) ||
    (m_lengthfactor != other.m_lengthfactor) ||
    (m_bAlternate != other.m_bAlternate) ||
    (m_alternate_lengthfactor != other.m_alternate_lengthfactor) ||
    (m_alternate_lengthformat != other.m_alternate_lengthformat) ||
    (m_alternate_lengthresolution != other.m_alternate_lengthresolution) ||
    (m_alternate_angleformat != other.m_alternate_angleformat) ||
    (m_alternate_angleresolution != other.m_alternate_angleresolution) ||
    (m_prefix != other.m_prefix) ||
    (m_suffix != other.m_suffix) ||
    (m_alternate_prefix != other.m_alternate_prefix) ||
    (m_alternate_suffix != other.m_alternate_suffix) ||
    (m_dimextension != other.m_dimextension) ||
    (m_leaderarrowsize != other.m_leaderarrowsize) ||
    (m_leaderarrowtype != other.m_leaderarrowtype) ||
    (m_bSuppressExtension1 != other.m_bSuppressExtension1) ||
    (m_bSuppressExtension2 != other.m_bSuppressExtension2) ||
    (ParentId() != other.ParentId()) ||
    (m_tolerance_style != other.m_tolerance_style) ||
    (m_tolerance_resolution != other.m_tolerance_resolution) ||
    (m_tolerance_upper_value != other.m_tolerance_upper_value) ||
    (m_tolerance_lower_value != other.m_tolerance_lower_value) ||
    (m_tolerance_height_scale != other.m_tolerance_height_scale) ||
    (m_baseline_spacing != other.m_baseline_spacing) ||
    (m_bDrawMask != other.m_bDrawMask) ||
    (m_mask_color_source != other.m_mask_color_source) ||
    (m_mask_color != other.m_mask_color) ||
    (m_dimscale != other.m_dimscale) ||
    (m_dimscale_source != other.m_dimscale_source) 

    ||
    (m_ext_line_color_source != other.m_ext_line_color_source) ||
    (m_dim_line_color_source != other.m_dim_line_color_source) ||
    (m_arrow_color_source != other.m_arrow_color_source) ||
    (m_text_color_source != other.m_text_color_source) ||
    (m_ext_line_color != other.m_ext_line_color) ||
    (m_dim_line_color != other.m_dim_line_color) ||
    (m_arrow_color != other.m_arrow_color) ||
    (m_text_color != other.m_text_color) ||
    (m_ext_line_plot_color_source != other.m_ext_line_plot_color_source) ||
    (m_dim_line_plot_color_source != other.m_dim_line_plot_color_source) ||
    (m_arrow_plot_color_source != other.m_arrow_plot_color_source) ||
    (m_text_plot_color_source != other.m_text_plot_color_source) ||
    (m_ext_line_plot_color != other.m_ext_line_plot_color) ||
    (m_dim_line_plot_color != other.m_dim_line_plot_color) ||
    (m_arrow_plot_color != other.m_arrow_plot_color) ||
    (m_text_plot_color != other.m_text_plot_color) ||
    (m_ext_line_plot_weight_source != other.m_ext_line_plot_weight_source) ||
    (m_dim_line_plot_weight_source != other.m_dim_line_plot_weight_source) ||
    (m_ext_line_plot_weight_mm != other.m_ext_line_plot_weight_mm) ||
    (m_dim_line_plot_weight_mm != other.m_dim_line_plot_weight_mm) ||
    (m_fixed_extension_len != other.m_fixed_extension_len) ||
    (m_fixed_extension_len_on != other.m_fixed_extension_len_on) ||
    (m_text_rotation != other.m_text_rotation) ||
    (m_alt_tol_resolution != other.m_alt_tol_resolution) ||
    (m_suppress_arrow1 != other.m_suppress_arrow1) ||
    (m_suppress_arrow2 != other.m_suppress_arrow2) ||
    (m_textmove_leader != other.m_textmove_leader) ||
    (m_arclength_sym != other.m_arclength_sym) ||
    (m_stack_textheight_fraction != other.m_stack_textheight_fraction) ||
    (m_stack_format != other.m_stack_format) ||
    (m_alt_round != other.m_alt_round) ||
    (m_round != other.m_round) ||
    (m_alt_zero_suppress != other.m_alt_zero_suppress) ||
    (m_tol_zero_suppress != other.m_tol_zero_suppress) ||
    (m_zero_suppress != other.m_zero_suppress) ||
    (m_ang_zero_suppress != other.m_ang_zero_suppress) ||
    (m_arrow_1 != other.m_arrow_1) ||
    (m_arrow_2 != other.m_arrow_2)

    )
    return false;
  
  return true;
}
