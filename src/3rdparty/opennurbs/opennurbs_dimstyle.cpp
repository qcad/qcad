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

/*
Changes and additions 5/01/07 LW
Adding several fields to ON_Dimstyle
Adding the concept of Parent and Child dimstyles so that individual dimension objects
can have their own copy of a dimension style to override some settings

  Adding several fields to ON_Dimstyle - This is done with ON_DimStyleExtra userdata
  class for now so the SDK doesn't break completely. When the SDK changes, the data in 
  ON_DimstyleExtra should be moved into ON_Dimstyle.

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
// Userdata class being used to extend ON_DimStyle so the v4 sdk still works
// Presumably, this will be moved into ON_DimStyle when the SDK is changed again
// Don't put this extension class in a header file or export it.
class ON_DimStyleExtra : public ON_UserData
{
  ON_OBJECT_DECLARE(ON_DimStyleExtra);
public:
  static ON_DimStyleExtra* DimStyleExtension( ON_DimStyle* pDimStyle, bool bCreate);
  static const ON_DimStyleExtra* DimStyleExtension( const ON_DimStyle* pDimStyle, bool bCreate);

  ON_DimStyleExtra();
  ~ON_DimStyleExtra();

  void SetDefaults();

  // override virtual ON_Object::Dump function
  void Dump( ON_TextLog& text_log ) const;

  // override virtual ON_Object::SizeOf function
  unsigned int SizeOf() const;

  // override virtual ON_Object::Write function
  ON_BOOL32 Write(ON_BinaryArchive& binary_archive) const;

  // override virtual ON_Object::Read function
  ON_BOOL32 Read(ON_BinaryArchive& binary_archive);

  // override virtual ON_UserData::GetDescription function
  ON_BOOL32 GetDescription( ON_wString& description );

  // override virtual ON_UserData::Archive function
  ON_BOOL32 Archive() const; 

  void SetFieldOverride( int field_id, bool bOverride);
  bool IsFieldOverride( int field_id) const;

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
};





// Added for v5 - 5/01/07 LW
ON_OBJECT_IMPLEMENT(ON_DimStyleExtra,ON_UserData,"513FDE53-7284-4065-8601-06CEA8B28D6F");


ON_DimStyleExtra* ON_DimStyleExtra::DimStyleExtension( ON_DimStyle* pDimStyle, bool bCreate)
{
  ON_DimStyleExtra* pExtra = 0;
  if( pDimStyle)
  {
    pExtra = ON_DimStyleExtra::Cast( pDimStyle->GetUserData( ON_DimStyleExtra::m_ON_DimStyleExtra_class_id.Uuid()));
    if( pExtra == 0 && bCreate)
    {
      pExtra = new ON_DimStyleExtra;
      if( pExtra)
      {
        if( !pDimStyle->AttachUserData( pExtra))
        {
          delete pExtra;
          pExtra = 0;
        }
      }
    }
  }
  return pExtra;
}

const 
ON_DimStyleExtra* ON_DimStyleExtra::DimStyleExtension( const ON_DimStyle* pDimStyle, bool bCreate)
{
  return DimStyleExtension( (ON_DimStyle*)pDimStyle, bCreate);
}

ON_DimStyleExtra::ON_DimStyleExtra()
{
  m_userdata_uuid = ON_DimStyleExtra::m_ON_DimStyleExtra_class_id.Uuid();
  m_application_uuid = ON_opennurbs5_id; // opennurbs.dll reads/writes this userdata
                                         // The id must be the version 5 id because
                                         // V6 SaveAs V5 needs to work, but SaveAs
                                         // V4 should not write this userdata.
  m_userdata_copycount = 1;
  m_valid_fields.Reserve( eFieldCount);
  m_valid_fields.SetCount( eFieldCount);
  m_parent_dimstyle = ON_nil_uuid;
  SetDefaults();
}

ON_DimStyleExtra::~ON_DimStyleExtra()
{
}

void ON_DimStyleExtra::SetDefaults()
{
  m_tolerance_style = ON_DimStyle::DefaultToleranceStyle();
  m_tolerance_resolution = ON_DimStyle::DefaultToleranceResolution();
  m_tolerance_upper_value = ON_DimStyle::DefaultToleranceUpperValue();
  m_tolerance_lower_value = ON_DimStyle::DefaultToleranceLowerValue();
  m_tolerance_height_scale = ON_DimStyle::DefaultToleranceHeightScale();
  m_baseline_spacing = ON_DimStyle::DefaultBaselineSpacing();
  m_bDrawMask = false;
  m_mask_color_source = 0;
  m_mask_color.SetRGB(255,255,255);
  m_dimscale = 1.0;
  m_dimscale_source = 0;

  for( int i = 0; i < eFieldCount; i++)
    m_valid_fields[i] = false;
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

ON_BOOL32 ON_DimStyleExtra::Write(ON_BinaryArchive& archive) const
{
//  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0); Changed to 1,1 for mask settings 12/12/09
//  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,1); Changed to 1,2 for dimscale 12/17/09
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,2);

  if(rc) rc = archive.WriteUuid( m_parent_dimstyle);
  if(rc) rc = archive.WriteArray( m_valid_fields);

  if(rc) rc = archive.WriteInt(m_tolerance_style);
  if(rc) rc = archive.WriteInt(m_tolerance_resolution);

  if(rc) rc = archive.WriteDouble(m_tolerance_upper_value);
  if(rc) rc = archive.WriteDouble(m_tolerance_lower_value);
  if(rc) rc = archive.WriteDouble(m_tolerance_height_scale);

  if(rc) rc = archive.WriteDouble(m_baseline_spacing);

  if(rc) rc = archive.WriteBool(m_bDrawMask);
  if(rc) rc = archive.WriteInt(m_mask_color_source);
  if(rc) rc = archive.WriteColor(m_mask_color);

  if(rc) rc = archive.WriteDouble(m_dimscale);
  if(rc) rc = archive.WriteInt(m_dimscale_source);

  if(!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

ON_BOOL32 ON_DimStyleExtra::Read(ON_BinaryArchive& archive)
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
    if(rc) rc = archive.ReadDouble(&m_dimscale);
    if(rc) rc = archive.ReadInt(&m_dimscale_source);

  if ( !archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

ON_BOOL32 ON_DimStyleExtra::GetDescription( ON_wString& description)
{
  description.Format( "Userdata extension of ON_DimStyle");
  return true;
}

ON_BOOL32 ON_DimStyleExtra::Archive() const
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
  m_bDrawMask = bDraw;
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


ON_OBJECT_IMPLEMENT( ON_DimStyle, ON_Object, "81BD83D5-7120-41c4-9A57-C449336FF12C" );

ON_DimStyle::ON_DimStyle()
{
  SetDefaults();
}

ON_DimStyle::~ON_DimStyle()
{
}

void ON_DimStyle::SetDefaults()
{
  // If there is already a userdata extension, reset it to the defaults,
  // but don't make one if its not there already
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if( pDE)
  {
    // reset all field override flags
    for( int i = 0; i < pDE->m_valid_fields.Count(); i++)
      pDE->m_valid_fields[i] = false;
    pDE->SetDefaults();
  }

  m_dimstyle_index = -1;
  memset(&m_dimstyle_id,0,sizeof(m_dimstyle_id));
  m_dimstyle_name = L"Default";

  m_extextension = 0.5;
  m_extoffset = 0.5;
  m_arrowsize = 1.0;
  m_centermark = 0.5;
  m_textgap = 0.25;
  m_textheight = 1.0;
  m_textalign = ON::dtAboveLine;
  m_arrowtype = 0;
  m_angularunits = 0;
  m_lengthformat = 0;
  m_angleformat = 0;
  m_lengthresolution = 2;
  m_angleresolution = 2;
  m_fontindex = -1;

  // Added at 1.3
  m_lengthfactor = 1.0;  
  m_bAlternate = false;
  m_alternate_lengthfactor = 25.4;
  m_alternate_lengthformat = 0;
  m_alternate_lengthresolution = 2;
  m_alternate_angleformat = 0;
  m_alternate_angleresolution = 2;

  m_prefix = L"";
  m_suffix = L"";
  m_alternate_prefix = L" [";
  m_alternate_suffix = L"]";
  m_valid = 0;

  m_dimextension = 0.0;

  m_leaderarrowsize = 1.0;
  m_leaderarrowtype = 0;
  m_bSuppressExtension1 = false;
  m_bSuppressExtension2 = false;
}


// copy from ON_3dmAnnotationSettings and add a couple of fields
ON_DimStyle& ON_DimStyle::operator=( const ON_3dmAnnotationSettings& src)
{
  SetDefaults();

  m_extextension = src.m_dimexe;
  m_extoffset = src.m_dimexo;
  m_arrowsize = src.m_arrowlength;
  m_textalign = src.m_textalign;
  m_centermark = src.m_centermark;
  m_textgap = src.m_dimexo / 2.0;
  m_textheight = src.m_textheight;
  m_arrowtype = src.m_arrowtype;
  m_angularunits = src.m_angularunits;
  m_lengthformat = src.m_lengthformat;
  m_angleformat = src.m_angleformat;
  m_lengthresolution = src.m_resolution;
  m_angleresolution = src.m_resolution;

  return *this;
}

//////////////////////////////////////////////////////////////////////
//
// ON_Object overrides

ON_BOOL32 ON_DimStyle::IsValid( ON_TextLog* text_log ) const
{
  return ( m_dimstyle_name.Length() > 0 && m_dimstyle_index >= 0);
}

void ON_DimStyle::Dump( ON_TextLog& dump ) const
{
  const wchar_t* name = m_dimstyle_name;
  if ( !name )
    name = L"";
  dump.Print("dimstyle index = %d\n",m_dimstyle_index);
  dump.Print("dimstyle name = \"%S\"\n",name);
}

ON_BOOL32 ON_DimStyle::Write(
       ON_BinaryArchive& file // serialize definition to binary archive
     ) const
{
  // changed to version 1.4 Dec 28, 05
  // changed to version 1.5 Mar 23, 06
  ON_BOOL32 rc = file.Write3dmChunkVersion(1,5);

  if (rc) rc = file.WriteInt(m_dimstyle_index);
  if (rc) rc = file.WriteString(m_dimstyle_name);

  if (rc) rc = file.WriteDouble(m_extextension);
  if (rc) rc = file.WriteDouble(m_extoffset);
  if (rc) rc = file.WriteDouble(m_arrowsize);
  if (rc) rc = file.WriteDouble(m_centermark);
  if (rc) rc = file.WriteDouble(m_textgap);
  
  if (rc) rc = file.WriteInt(m_textalign);
  if (rc) rc = file.WriteInt(m_arrowtype);
  if (rc) rc = file.WriteInt(m_angularunits);
  if (rc) rc = file.WriteInt(m_lengthformat);
  if (rc) rc = file.WriteInt(m_angleformat);
  if (rc) rc = file.WriteInt(m_lengthresolution);
  if (rc) rc = file.WriteInt(m_angleresolution);
  if (rc) rc = file.WriteInt(m_fontindex);

  if (rc) rc = file.WriteDouble(m_textheight);

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
  if (rc) rc = file.WriteInt(m_valid);

  // Added 24 October 2005 ver 1.3
  if (rc) rc = file.WriteUuid(m_dimstyle_id);

  // Added Dec 28, 05 ver 1.4
  if (rc) rc = file.WriteDouble(m_dimextension);

  // Added Mar 23 06 ver 1.5
  if (rc) rc = file.WriteDouble(m_leaderarrowsize);
  if (rc) rc = file.WriteInt(m_leaderarrowtype);
  if (rc) rc = file.WriteBool(m_bSuppressExtension1);
  if (rc) rc = file.WriteBool(m_bSuppressExtension2);

  return rc;
}

ON_BOOL32 ON_DimStyle::Read(
       ON_BinaryArchive& file // restore definition from binary archive
     )
{
  SetDefaults();

  int major_version = 0;
  int minor_version = 0;
  ON_BOOL32 rc = file.Read3dmChunkVersion(&major_version,&minor_version);


  if ( major_version >= 1 ) 
  {
    if ( rc) rc = file.ReadInt( &m_dimstyle_index);
    if ( rc) rc = file.ReadString( m_dimstyle_name);
    
    if ( rc) rc = file.ReadDouble( &m_extextension);
    if ( rc) rc = file.ReadDouble( &m_extoffset);
    if ( rc) rc = file.ReadDouble( &m_arrowsize);
    if ( rc) rc = file.ReadDouble( &m_centermark);
    if ( rc) rc = file.ReadDouble( &m_textgap);
    
    if ( rc) rc = file.ReadInt( &m_textalign);
    if ( rc) rc = file.ReadInt( &m_arrowtype);
    if ( rc) rc = file.ReadInt( &m_angularunits);
    if ( rc) rc = file.ReadInt( &m_lengthformat);
    if ( rc) rc = file.ReadInt( &m_angleformat);
    if ( rc) rc = file.ReadInt( &m_lengthresolution);
    if ( rc) rc = file.ReadInt( &m_angleresolution);
    if ( rc) rc = file.ReadInt( &m_fontindex);

    if( minor_version >= 1)
      if ( rc) rc = file.ReadDouble( &m_textheight);

    // added 1/13/05
    if( minor_version >= 2)
    {
      if (rc) rc = file.ReadDouble( &m_lengthfactor);
      if (rc) rc = file.ReadString( m_prefix);
      if (rc) rc = file.ReadString( m_suffix);

      if (rc) rc = file.ReadBool( &m_bAlternate);
      if (rc) rc = file.ReadDouble(&m_alternate_lengthfactor);
      if (rc) rc = file.ReadInt( &m_alternate_lengthformat);
      if (rc) rc = file.ReadInt( &m_alternate_lengthresolution);
      if (rc) rc = file.ReadInt( &m_alternate_angleformat);
      if (rc) rc = file.ReadInt( &m_alternate_angleresolution);
      if (rc) rc = file.ReadString( m_alternate_prefix);
      if (rc) rc = file.ReadString( m_alternate_suffix);
      if (rc) rc = file.ReadInt( &m_valid);

      if ( minor_version >= 3 )
      {
        if (rc) rc = file.ReadUuid(m_dimstyle_id);
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

  return rc;
}

void ON_DimStyle::EmergencyDestroy()
{
  m_prefix.EmergencyDestroy();
  m_suffix.EmergencyDestroy();
  m_alternate_prefix.EmergencyDestroy();
  m_alternate_suffix.EmergencyDestroy();
}

//////////////////////////////////////////////////////////////////////
//
// Interface
void ON_DimStyle::SetName( const wchar_t* s )
{
  m_dimstyle_name = s;
  m_dimstyle_name.TrimLeftAndRight();
}

void ON_DimStyle::SetName( const char* s )
{
  m_dimstyle_name = s;
  m_dimstyle_name.TrimLeftAndRight();
}

void ON_DimStyle::GetName( ON_wString& s ) const
{
  s = m_dimstyle_name;
}

const wchar_t* ON_DimStyle::Name() const
{
  const wchar_t* s = m_dimstyle_name;
  return s;
}

void ON_DimStyle::SetIndex(int i )
{
  m_dimstyle_index = i;
}

int ON_DimStyle::Index() const
{
  return m_dimstyle_index;
}

double ON_DimStyle::ExtExtension() const
{
  return m_extextension;
}

void ON_DimStyle::SetExtExtension( const double e)
{
  // Allow negative?
  m_extextension = e;
}

double ON_DimStyle::ExtOffset() const
{
  return m_extoffset;
}

void ON_DimStyle::SetExtOffset( const double e)
{
  m_extoffset = e;
}

double ON_DimStyle::ArrowSize() const
{
  return m_arrowsize;
}

void ON_DimStyle::SetArrowSize( const double e)
{
  m_arrowsize = e;
}

double ON_DimStyle::LeaderArrowSize() const
{
  return m_leaderarrowsize;
}

void ON_DimStyle::SetLeaderArrowSize( const double e)
{
  m_leaderarrowsize = e;
}

double ON_DimStyle::CenterMark() const
{
  return m_centermark;
}

void ON_DimStyle::SetCenterMark( const double e)
{
  m_centermark = e;
}

int ON_DimStyle::TextAlignment() const
{
  return m_textalign;
}

void ON_DimStyle::SetTextAlignment( ON::eTextDisplayMode a)
{
  m_textalign = a;
}

int ON_DimStyle::ArrowType() const
{
  return m_arrowtype;
}

void ON_DimStyle::SetArrowType( eArrowType a)
{
  m_arrowtype = a;
}

int ON_DimStyle::LeaderArrowType() const
{
  return m_leaderarrowtype;
}

void ON_DimStyle::SetLeaderArrowType( eArrowType a)
{
  m_leaderarrowtype = a;
}

int ON_DimStyle::AngularUnits() const
{
  return m_angularunits;
}

void ON_DimStyle::SetAngularUnits( int u)
{
  m_angularunits = u;
}

int ON_DimStyle::LengthFormat() const
{
  return m_lengthformat;
}

void ON_DimStyle::SetLengthFormat( int f)
{
  m_lengthformat = f;
}

int ON_DimStyle::AngleFormat() const
{
  return m_angleformat;
}

void ON_DimStyle::SetAngleFormat( int f)
{
  m_angleformat = f;
}

int ON_DimStyle::LengthResolution() const
{
  return m_lengthresolution;
}

void ON_DimStyle::SetLengthResolution( int r)
{
  if( r >= 0 && r < 16)
  {
    m_lengthresolution = r;
  }
}

int ON_DimStyle::AngleResolution() const
{
  return m_angleresolution;
}

void ON_DimStyle::SetAngleResolution( int r)
{
  if( r >= 0 && r < 16)
  {
    m_angleresolution = r;
  }
}

int ON_DimStyle::FontIndex() const
{
  return m_fontindex;
}

void ON_DimStyle::SetFontIndex( int index)
{
  m_fontindex = index;
}

double ON_DimStyle::TextGap() const
{
  return m_textgap;
}

void ON_DimStyle::SetTextGap( double gap)
{
  if( gap >= 0.0)
  {
    m_textgap = gap;
  }
}

double ON_DimStyle::TextHeight() const
{
  return m_textheight;
}

void ON_DimStyle::SetTextHeight( double height)
{
  if( ON_IsValid( height) && height > ON_SQRT_EPSILON)
  {
    m_textheight = height;
  }
}


double ON_DimStyle::LengthFactor() const
{
  return m_lengthfactor;
}
void ON_DimStyle::SetLengthactor( double factor)
{
  SetLengthFactor( factor);
}
void ON_DimStyle::SetLengthFactor( double factor)
{
  m_lengthfactor = factor;
  ValidateField( fn_lengthfactor);
}

bool ON_DimStyle::Alternate() const
{
  return m_bAlternate;
}
void ON_DimStyle::SetAlternate( bool bAlternate)
{
  m_bAlternate = bAlternate;
}

double ON_DimStyle::AlternateLengthFactor() const
{
  return m_alternate_lengthfactor;
}
void ON_DimStyle::SetAlternateLengthactor( double factor)
{
  SetAlternateLengthFactor( factor);
}
void ON_DimStyle::SetAlternateLengthFactor( double factor)
{
  m_alternate_lengthfactor = factor;
  ValidateField( fn_alternate_lengthfactor);
}

int ON_DimStyle::AlternateLengthFormat() const
{
  return m_alternate_lengthformat;
}
void ON_DimStyle::SetAlternateLengthFormat( int format)
{
  m_alternate_lengthformat = format;
}

int ON_DimStyle::AlternateLengthResolution() const
{
  return m_alternate_lengthresolution;
}
void ON_DimStyle::SetAlternateLengthResolution( int resolution)
{
  m_alternate_lengthresolution = resolution;
}

int ON_DimStyle::AlternateAngleFormat() const
{
  return m_alternate_angleformat;
}
void ON_DimStyle::SetAlternateAngleFormat( int format)
{
  m_alternate_angleformat = format;
}

int ON_DimStyle::AlternateAngleResolution() const
{
  return m_alternate_angleresolution;
}
void ON_DimStyle::SetAlternateAngleResolution( int resolution)
{
  m_alternate_angleresolution = resolution;
}

void ON_DimStyle::GetPrefix( ON_wString& prefix) const
{
  prefix = m_prefix;
}
const wchar_t* ON_DimStyle::Prefix() const
{
  return m_prefix;
}
void ON_DimStyle::SetPrefix( wchar_t* prefix)
{
  m_prefix = prefix;
}
void ON_DimStyle::SetPrefix( const wchar_t* prefix)
{
  m_prefix = prefix;
}

void ON_DimStyle::GetSuffix( ON_wString& suffix) const
{
  suffix = m_suffix;
}
const wchar_t* ON_DimStyle::Suffix() const
{
  return m_suffix;
}
void ON_DimStyle::SetSuffix( wchar_t* suffix)
{
  m_suffix = suffix;
}
void ON_DimStyle::SetSuffix( const wchar_t* suffix)
{
  m_suffix = suffix;
}

void ON_DimStyle::GetAlternatePrefix( ON_wString& prefix) const
{
  prefix = m_alternate_prefix;
}
const wchar_t* ON_DimStyle::AlternatePrefix() const
{
  return m_alternate_prefix;
}
void ON_DimStyle::SetAlternatePrefix( wchar_t* prefix)
{
  m_alternate_prefix = prefix;
}
void ON_DimStyle::SetAlternatePrefix( const wchar_t* prefix)
{
  m_alternate_prefix = prefix;
}

void ON_DimStyle::GetAlternateSuffix( ON_wString& suffix) const
{
  suffix = m_alternate_suffix;
}
const wchar_t* ON_DimStyle::AlternateSuffix() const
{
  return m_alternate_suffix;
}
void ON_DimStyle::SetAlternateSuffix( wchar_t* suffix)
{
  m_alternate_suffix = suffix;
}
void ON_DimStyle::SetAlternateSuffix( const wchar_t* suffix)
{
  m_alternate_suffix = suffix;
}

bool ON_DimStyle::SuppressExtension1() const
{
  return m_bSuppressExtension1;
}
void ON_DimStyle::SetSuppressExtension1( bool suppress)
{
  m_bSuppressExtension1 = suppress;
}
bool ON_DimStyle::SuppressExtension2() const
{
  return m_bSuppressExtension2;
}
void ON_DimStyle::SetSuppressExtension2( bool suppress)
{
  m_bSuppressExtension2 = suppress;
}

// This function deprecated 5/01/07 LW
void ON_DimStyle::Composite( const ON_DimStyle& OverRide)
{
/*
  InvalidateAllFields();

  if( OverRide.IsFieldValid( fn_name))                          { ValidateField( fn_name); m_dimstyle_name = OverRide.m_dimstyle_name; }
  if( OverRide.IsFieldValid( fn_index))                         { ValidateField( fn_index); m_dimstyle_index = OverRide.m_dimstyle_index; }
  if( OverRide.IsFieldValid( fn_extextension))                  { ValidateField( fn_extextension); m_extextension = OverRide.m_extextension; }
  if( OverRide.IsFieldValid( fn_extoffset))                     { ValidateField( fn_extoffset); m_extoffset = OverRide.m_extoffset; }
  if( OverRide.IsFieldValid( fn_arrowsize))                     { ValidateField( fn_arrowsize); m_arrowsize = OverRide.m_arrowsize; }
  if( OverRide.IsFieldValid( fn_leaderarrowsize))               { ValidateField( fn_leaderarrowsize); m_leaderarrowsize = OverRide.m_leaderarrowsize; }
  if( OverRide.IsFieldValid( fn_centermark))                    { ValidateField( fn_centermark); m_centermark = OverRide.m_centermark; }
  if( OverRide.IsFieldValid( fn_textgap))                       { ValidateField( fn_textgap); m_textgap = OverRide.m_textgap; }
  if( OverRide.IsFieldValid( fn_textheight))                    { ValidateField( fn_textheight); m_textheight = OverRide.m_textheight; }
  if( OverRide.IsFieldValid( fn_textalign))                     { ValidateField( fn_textalign); m_textalign = OverRide.m_textalign; }
  if( OverRide.IsFieldValid( fn_arrowtype))                     { ValidateField( fn_arrowtype); m_arrowtype = OverRide.m_arrowtype; }
  if( OverRide.IsFieldValid( fn_leaderarrowtype))               { ValidateField( fn_leaderarrowtype); m_leaderarrowtype = OverRide.m_leaderarrowtype; }
  if( OverRide.IsFieldValid( fn_angularunits))                  { ValidateField( fn_angularunits); m_angularunits = OverRide.m_angularunits; }
  if( OverRide.IsFieldValid( fn_lengthformat))                  { ValidateField( fn_lengthformat); m_lengthformat = OverRide.m_lengthformat; }
  if( OverRide.IsFieldValid( fn_angleformat))                   { ValidateField( fn_angleformat); m_angleformat = OverRide.m_angleformat; }
  if( OverRide.IsFieldValid( fn_angleresolution))               { ValidateField( fn_angleresolution); m_angleresolution = OverRide.m_angleresolution; }
  if( OverRide.IsFieldValid( fn_lengthresolution))              { ValidateField( fn_lengthresolution); m_lengthresolution = OverRide.m_lengthresolution; }
  if( OverRide.IsFieldValid( fn_fontindex))                     { ValidateField( fn_fontindex); m_fontindex = OverRide.m_fontindex; }
  if( OverRide.IsFieldValid( fn_lengthfactor))                  { ValidateField( fn_lengthfactor); m_lengthfactor = OverRide.m_lengthfactor; }
  if( OverRide.IsFieldValid( fn_bAlternate))                    { ValidateField( fn_bAlternate); m_bAlternate = OverRide.m_bAlternate; }
  if( OverRide.IsFieldValid( fn_alternate_lengthfactor))        { ValidateField( fn_alternate_lengthfactor); m_alternate_lengthfactor = OverRide.m_alternate_lengthfactor; }
  if( OverRide.IsFieldValid( fn_alternate_lengthformat))        { ValidateField( fn_alternate_lengthformat); m_alternate_lengthformat = OverRide.m_alternate_lengthformat; }
  if( OverRide.IsFieldValid( fn_alternate_lengthresolution))    { ValidateField( fn_alternate_lengthresolution); m_alternate_lengthresolution = OverRide.m_alternate_lengthresolution; }
  if( OverRide.IsFieldValid( fn_prefix))                        { ValidateField( fn_prefix); m_prefix = OverRide.m_prefix; }
  if( OverRide.IsFieldValid( fn_suffix))                        { ValidateField( fn_suffix); m_suffix = OverRide.m_suffix; }
  if( OverRide.IsFieldValid( fn_alternate_prefix))              { ValidateField( fn_alternate_prefix); m_alternate_prefix = OverRide.m_alternate_prefix; }
  if( OverRide.IsFieldValid( fn_alternate_suffix))              { ValidateField( fn_alternate_suffix); m_alternate_suffix = OverRide.m_alternate_suffix; }
  if( OverRide.IsFieldValid( fn_dimextension))                  { ValidateField( fn_dimextension); m_dimextension = OverRide.m_dimextension; }
  if( OverRide.IsFieldValid( fn_suppressextension1))            { ValidateField( fn_suppressextension1); m_bSuppressExtension1 = OverRide.m_bSuppressExtension1; }
  if( OverRide.IsFieldValid( fn_suppressextension2))            { ValidateField( fn_suppressextension2); m_bSuppressExtension2 = OverRide.m_bSuppressExtension2; }
*/
}

// This function deprecated 5/01/07 LW
void ON_DimStyle::InvalidateField( eField field)
{
  m_valid &= ~( 1 << field);
}
// This function deprecated 5/01/07 LW
void ON_DimStyle::InvalidateAllFields()
{
  m_valid = 0;
}
// This function deprecated 5/01/07 LW
void ON_DimStyle::ValidateField( eField field)
{
  m_valid |= ( 1 << field);
}
// This function deprecated 5/01/07 LW
bool ON_DimStyle::IsFieldValid( eField field) const
{
  return ( m_valid & ( 1 << field)) ? true : false;
}


// ver 1.4, Dec 28, 05
double ON_DimStyle::DimExtension() const
{
  return m_dimextension;
}

void ON_DimStyle::SetDimExtension( const double e)
{
  // Allow negative?
  m_dimextension = e;
}

//--------------------------------------
// ON_DimStyleExtra access functions
// Added for v5 5/01/07 LW

bool ON_DimStyle::IsFieldOverride( ON_DimStyle::eField field_id) const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->IsFieldOverride( field_id);

  return false;
}

void ON_DimStyle::SetFieldOverride(  ON_DimStyle::eField field_id, bool bOverride)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
    pDE->SetFieldOverride( field_id, bOverride);
}
  
bool ON_DimStyle::HasOverrides() const 
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
  {
    for( int i = 0; i < pDE->m_valid_fields.Count(); i++)
    {
      if( pDE->m_valid_fields[i])
        return true;
    }
  }
  return false;
}

bool ON_DimStyle::OverrideFields( const ON_DimStyle& src, const ON_DimStyle& parent)
{
  bool rc = false;
  const ON_DimStyleExtra* pDEsrc = ON_DimStyleExtra::DimStyleExtension( &src, true);
  ON_DimStyleExtra* pDE    = ON_DimStyleExtra::DimStyleExtension( this, true);
  if( pDEsrc && pDE)
  {
    for( int i = 0; i < pDEsrc->eFieldCount; i++)
    {
      pDE->m_valid_fields[i] = pDEsrc->m_valid_fields[i];
      switch( i)
      {
      case fn_extextension:
        if( pDEsrc->m_valid_fields[i])
          SetExtExtension( src.ExtExtension());
        else
          SetExtExtension( parent.ExtExtension());
        rc = true;
        break;
      case fn_extoffset:
        if( pDEsrc->m_valid_fields[i])
          SetExtOffset( src.ExtOffset());
        else
          SetExtOffset( parent.ExtOffset());
        rc = true;
        break;
      case fn_arrowsize:
        if( pDEsrc->m_valid_fields[i])
          SetArrowSize( src.ArrowSize());
        else
          SetArrowSize( parent.ArrowSize());
        rc = true;
        break;
      case fn_centermark:
        if( pDEsrc->m_valid_fields[i])
          SetCenterMark( src.CenterMark());
        else
          SetCenterMark( parent.CenterMark());
        rc = true;
        break;
      case fn_textgap:
        if( pDEsrc->m_valid_fields[i])
          SetTextGap( src.TextGap());
        else
          SetTextGap( parent.TextGap());
        rc = true;
        break;
      case fn_textheight:
        if( pDEsrc->m_valid_fields[i])
          SetTextHeight( src.TextHeight());
        else
          SetTextHeight( parent.TextHeight());
        rc = true;
        break;
      case fn_textalign:
        if( pDEsrc->m_valid_fields[i])
          SetTextAlignment( (ON::eTextDisplayMode)src.TextAlignment());
        else
          SetTextAlignment( (ON::eTextDisplayMode)parent.TextAlignment());
        rc = true;
        break;
      case fn_arrowtype:
        if( pDEsrc->m_valid_fields[i])
          SetArrowType( (eArrowType)src.ArrowType());
        else
          SetArrowType( (eArrowType)parent.ArrowType());
        rc = true;
        break;
      case fn_angularunits:
        if( pDEsrc->m_valid_fields[i])
          SetAngularUnits( (eArrowType)src.AngularUnits());
        else
          SetAngularUnits( (eArrowType)parent.AngularUnits());
        rc = true;
        break;
      case fn_lengthformat:
        if( pDEsrc->m_valid_fields[i])
          SetLengthFormat( src.LengthFormat());
        else
          SetLengthFormat( parent.LengthFormat());
        rc = true;
        break;
      case fn_angleformat:
        if( pDEsrc->m_valid_fields[i])
          SetAngleFormat( src.AngleFormat());
        else
          SetAngleFormat( parent.AngleFormat());
        rc = true;
        break;
      case fn_angleresolution:
        if( pDEsrc->m_valid_fields[i])
          SetAngleResolution( src.AngleResolution());
        else
          SetAngleResolution( parent.AngleResolution());
        rc = true;
        break;
      case fn_lengthresolution:
        if( pDEsrc->m_valid_fields[i])
          SetLengthResolution( src.LengthResolution());
        else
          SetLengthResolution( parent.LengthResolution());
        rc = true;
        break;
      case fn_fontindex:
        if( pDEsrc->m_valid_fields[i])
          SetFontIndex( src.FontIndex());
        else
          SetFontIndex( parent.FontIndex());
        rc = true;
        break;
      case fn_lengthfactor:
        if( pDEsrc->m_valid_fields[i])
          SetLengthactor( src.LengthFactor());
        else
          SetLengthactor( parent.LengthFactor());
        rc = true;
        break;
      case fn_bAlternate:
        if( pDEsrc->m_valid_fields[i])
          SetAlternate( src.Alternate());
        else
          SetAlternate( parent.Alternate());
        rc = true;
        break;
      case fn_alternate_lengthfactor:
        if( pDEsrc->m_valid_fields[i])
          SetAlternateLengthFactor( src.LengthFactor());
        else
          SetAlternateLengthFactor( parent.LengthFactor());
        rc = true;
        break;
      case fn_alternate_lengthformat:
        if( pDEsrc->m_valid_fields[i])
          SetAlternateLengthFormat( src.AlternateLengthFormat());
        else
          SetAlternateLengthFormat( parent.AlternateLengthFormat());
        rc = true;
        break;
      case fn_alternate_lengthresolution:
        if( pDEsrc->m_valid_fields[i])
          SetAlternateLengthResolution( src.AlternateLengthResolution());
        else
          SetAlternateLengthResolution( parent.AlternateLengthResolution());
        rc = true;
        break;
      case fn_alternate_angleformat:
        if( pDEsrc->m_valid_fields[i])
          SetAlternateLengthResolution( src.AlternateLengthResolution());
        else
          SetAlternateLengthResolution( parent.AlternateLengthResolution());
        rc = true;
        break;
      case fn_alternate_angleresolution:
        if( pDEsrc->m_valid_fields[i])
          SetAlternateAngleResolution( src.AlternateAngleResolution());
        else
          SetAlternateAngleResolution( parent.AlternateAngleResolution());
        rc = true;
        break;
      case fn_prefix:
        if( pDEsrc->m_valid_fields[i])
          SetPrefix( src.Prefix());
        else
          SetPrefix( parent.Prefix());
        rc = true;
        break;
      case fn_suffix:
        if( pDEsrc->m_valid_fields[i])
          SetSuffix( src.Suffix());
        else
          SetSuffix( parent.Suffix());
        rc = true;
        break;
      case fn_alternate_prefix:
        if( pDEsrc->m_valid_fields[i])
          SetAlternatePrefix( src.AlternatePrefix());
        else
          SetAlternatePrefix( parent.AlternatePrefix());
        rc = true;
        break;
      case fn_alternate_suffix:
        if( pDEsrc->m_valid_fields[i])
          SetAlternateSuffix( src.AlternateSuffix());
        else
          SetAlternateSuffix( parent.AlternateSuffix());
        rc = true;
        break;
      case fn_dimextension:
        if( pDEsrc->m_valid_fields[i])
          SetDimExtension( src.DimExtension());
        else
          SetDimExtension( parent.DimExtension());
        rc = true;
        break;
      case fn_leaderarrowsize:
        if( pDEsrc->m_valid_fields[i])
          SetLeaderArrowSize( src.LeaderArrowSize());
        else
          SetLeaderArrowSize( parent.LeaderArrowSize());
        rc = true;
        break;
      case fn_leaderarrowtype:
        if( pDEsrc->m_valid_fields[i])
          SetLeaderArrowType( (eArrowType)src.LeaderArrowType());
        else
          SetLeaderArrowType( (eArrowType)parent.LeaderArrowType());
        rc = true;
        break;
      case fn_suppressextension1:
        if( pDEsrc->m_valid_fields[i])
          SetSuppressExtension1( src.SuppressExtension1());
        else
          SetSuppressExtension1( parent.SuppressExtension1());
        rc = true;
        break;
      case fn_suppressextension2:
        if( pDEsrc->m_valid_fields[i])
          SetSuppressExtension2( src.SuppressExtension2());
        else
          SetSuppressExtension2( parent.SuppressExtension2());
        rc = true;
        break;
      case fn_tolerance_style:
        if( pDEsrc->m_valid_fields[i])
          SetToleranceStyle( src.ToleranceStyle());
        else
          SetToleranceStyle( parent.ToleranceStyle());
        rc = true;
        break;
      case fn_tolerance_resolution:
        if( pDEsrc->m_valid_fields[i])
          SetToleranceResolution( src.ToleranceResolution());
        else
          SetToleranceResolution( parent.ToleranceResolution());
        rc = true;
        break;
      case fn_tolerance_upper_value:
        if( pDEsrc->m_valid_fields[i])
          SetToleranceUpperValue( src.ToleranceUpperValue());
        else
          SetToleranceUpperValue( parent.ToleranceUpperValue());
        rc = true;
        break;
      case fn_tolerance_lower_value:
        if( pDEsrc->m_valid_fields[i])
          SetToleranceLowerValue( src.ToleranceLowerValue());
        else
          SetToleranceLowerValue( parent.ToleranceLowerValue());
        rc = true;
        break;
      case fn_tolerance_height_scale:
        if( pDEsrc->m_valid_fields[i])
          SetToleranceHeightScale( src.ToleranceHeightScale());
        else
          SetToleranceHeightScale( parent.ToleranceHeightScale());
        rc = true;
        break;
      case fn_baseline_spacing:
        if( pDEsrc->m_valid_fields[i])
          SetBaselineSpacing( src.BaselineSpacing());
        else
          SetBaselineSpacing( parent.BaselineSpacing());
          rc = true;
          break;
      case fn_draw_mask:
        if( pDEsrc->m_valid_fields[i])
          SetDrawTextMask( src.DrawTextMask());
        else
          SetDrawTextMask( parent.DrawTextMask());
          rc = true;
          break;
      case fn_mask_color_source:
        if( pDEsrc->m_valid_fields[i])
          SetMaskColorSource( src.MaskColorSource());
        else
          SetMaskColorSource( parent.MaskColorSource());
          rc = true;
          break;
      case fn_mask_color:
        if( pDEsrc->m_valid_fields[i])
          SetMaskColor( src.MaskColor());
        else
          SetMaskColor( parent.MaskColor());
          rc = true;
          break;
      case fn_dimscale:
        if( pDEsrc->m_valid_fields[i])
          SetDimScale( src.DimScale());
        else
          SetDimScale( parent.DimScale());
          rc = true;
          break;
      case fn_dimscale_source:
        if( pDEsrc->m_valid_fields[i])
          SetDimScaleSource( src.DimScaleSource());
        else
          SetDimScaleSource( parent.DimScaleSource());
          rc = true;
          break;
      }
    }
  }
  return rc;
}

bool ON_DimStyle::InheritFields( const ON_DimStyle& parent)
{
  bool rc = false;
  const ON_DimStyleExtra* pDE       = ON_DimStyleExtra::DimStyleExtension( this, true);
  if( pDE)
  {
    for( int i = 0; i < pDE->eFieldCount; i++)
    {
      switch( i)
      {
      case fn_extextension:
        if( !pDE->m_valid_fields[i])
        {
          SetExtExtension( parent.ExtExtension());
          rc = true;
        }
        break;
      case fn_extoffset:
        if( !pDE->m_valid_fields[i])
        {
          SetExtOffset( parent.ExtOffset());
          rc = true;
        }
        break;
      case fn_arrowsize:
        if( !pDE->m_valid_fields[i])
        {
          SetArrowSize( parent.ArrowSize());
          rc = true;
        }
        break;
      case fn_centermark:
        if( !pDE->m_valid_fields[i])
        {
          SetCenterMark( parent.CenterMark());
          rc = true;
        }
        break;
      case fn_textgap:
        if( !pDE->m_valid_fields[i])
        {
          SetTextGap( parent.TextGap());
          rc = true;
        }
        break;
      case fn_textheight:
        if( !pDE->m_valid_fields[i])
        {
          SetTextHeight( parent.TextHeight());
          rc = true;
        }
        break;
      case fn_textalign:
        if( !pDE->m_valid_fields[i])
        {
          SetTextAlignment( (ON::eTextDisplayMode)parent.TextAlignment());
          rc = true;
        }
        break;
      case fn_arrowtype:
        if( !pDE->m_valid_fields[i])
        {
          SetArrowType( (eArrowType)parent.ArrowType());
          rc = true;
        }
        break;
      case fn_angularunits:
        if( !pDE->m_valid_fields[i])
        {
          SetAngularUnits( (eArrowType)parent.AngularUnits());
          rc = true;
        }
        break;
      case fn_lengthformat:
        if( !pDE->m_valid_fields[i])
        {
          SetLengthFormat( parent.LengthFormat());
          rc = true;
        }
        break;
      case fn_angleformat:
        if( !pDE->m_valid_fields[i])
        {
          SetAngleFormat( parent.AngleFormat());
          rc = true;
        }
        break;
      case fn_angleresolution:
        if( !pDE->m_valid_fields[i])
        {
          SetAngleResolution( parent.AngleResolution());
          rc = true;
        }
        break;
      case fn_lengthresolution:
        if( !pDE->m_valid_fields[i])
        {
          SetLengthResolution( parent.LengthResolution());
          rc = true;
        }
        break;
      case fn_fontindex:
        if( !pDE->m_valid_fields[i])
        {
          SetFontIndex( parent.FontIndex());
          rc = true;
        }
        break;
      case fn_lengthfactor:
        if( !pDE->m_valid_fields[i])
        {
          SetLengthactor( parent.LengthFactor());
          rc = true;
        }
        break;
      case fn_bAlternate:
        if( !pDE->m_valid_fields[i])
        {
          SetAlternate( parent.Alternate());
          rc = true;
        }
        break;
      case fn_alternate_lengthfactor:
        if( !pDE->m_valid_fields[i])
        {
          SetAlternateLengthFactor( parent.LengthFactor());
          rc = true;
        }
        break;
      case fn_alternate_lengthformat:
        if( !pDE->m_valid_fields[i])
        {
          SetAlternateLengthFormat( parent.AlternateLengthFormat());
          rc = true;
        }
        break;
      case fn_alternate_lengthresolution:
        if( !pDE->m_valid_fields[i])
        {
          SetAlternateLengthResolution( parent.AlternateLengthResolution());
          rc = true;
        }
        break;
      case fn_alternate_angleformat:
        if( !pDE->m_valid_fields[i])
        {
          SetAlternateLengthResolution( parent.AlternateLengthResolution());
          rc = true;
        }
        break;
      case fn_alternate_angleresolution:
        if( !pDE->m_valid_fields[i])
        {
          SetAlternateAngleResolution( parent.AlternateAngleResolution());
          rc = true;
        }
        break;
      case fn_prefix:
        if( !pDE->m_valid_fields[i])
        {
          SetPrefix( parent.Prefix());
          rc = true;
        }
        break;
      case fn_suffix:
        if( !pDE->m_valid_fields[i])
        {
          SetSuffix( parent.Suffix());
          rc = true;
        }
        break;
      case fn_alternate_prefix:
        if( !pDE->m_valid_fields[i])
        {
          SetAlternatePrefix( parent.AlternatePrefix());
          rc = true;
        }
        break;
      case fn_alternate_suffix:
        if( !pDE->m_valid_fields[i])
        {
          SetAlternateSuffix( parent.AlternateSuffix());
          rc = true;
        }
        break;
      case fn_dimextension:
        if( !pDE->m_valid_fields[i])
        {
          SetDimExtension( parent.DimExtension());
          rc = true;
        }
        break;
      case fn_leaderarrowsize:
        if( !pDE->m_valid_fields[i])
        {
          SetLeaderArrowSize( parent.LeaderArrowSize());
          rc = true;
        }
        break;
      case fn_leaderarrowtype:
        if( !pDE->m_valid_fields[i])
        {
          SetLeaderArrowType( (eArrowType)parent.LeaderArrowType());
          rc = true;
        }
        break;
      case fn_suppressextension1:
        if( !pDE->m_valid_fields[i])
        {
          SetSuppressExtension1( parent.SuppressExtension1());
          rc = true;
        }
        break;
      case fn_suppressextension2:
        if( !pDE->m_valid_fields[i])
        {
          SetSuppressExtension2( parent.SuppressExtension2());
          rc = true;
        }
        break;
      case fn_tolerance_style:
        if( !pDE->m_valid_fields[i])
        {
          SetToleranceStyle( parent.ToleranceStyle());
          rc = true;
        }
        break;
      case fn_tolerance_resolution:
        if( !pDE->m_valid_fields[i])
        {
          SetToleranceResolution( parent.ToleranceResolution());
          rc = true;
        }
        break;
      case fn_tolerance_upper_value:
        if( !pDE->m_valid_fields[i])
        {
          SetToleranceUpperValue( parent.ToleranceUpperValue());
          rc = true;
        }
        break;
      case fn_tolerance_lower_value:
        if( !pDE->m_valid_fields[i])
        {
          SetToleranceLowerValue( parent.ToleranceLowerValue());
          rc = true;
        }
        break;
      case fn_tolerance_height_scale:
        if( !pDE->m_valid_fields[i])
        {
          SetToleranceHeightScale( parent.ToleranceHeightScale());
          rc = true;
        }
        break;
      case fn_baseline_spacing:
        if( !pDE->m_valid_fields[i])
        {
          SetBaselineSpacing( parent.BaselineSpacing());
            rc = true;
        }
        break;
      case fn_draw_mask:
        if( !pDE->m_valid_fields[i])
        {
          SetDrawTextMask( parent.DrawTextMask());
            rc = true;
        }
        break;
      case fn_mask_color_source:
        if( !pDE->m_valid_fields[i])
        {
          SetMaskColorSource( parent.MaskColorSource());
            rc = true;
        }
        break;
      case fn_mask_color:
        if( !pDE->m_valid_fields[i])
        {
          SetMaskColor( parent.MaskColor());
            rc = true;
        }
        break;
      case fn_dimscale:
        if( !pDE->m_valid_fields[i])
        {
          SetDimScale( parent.DimScale());
            rc = true;
        }
        break;
      case fn_dimscale_source:
        if( !pDE->m_valid_fields[i])
        {
          SetDimScaleSource( parent.DimScaleSource());
            rc = true;
        }
        break;
      }
    }
  }
  return rc;
}


bool ON_DimStyle::IsChildDimstyle() const
{

  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE && pDE->m_parent_dimstyle != ON_nil_uuid)
    return true;
  else
    return false;
}

bool ON_DimStyle::IsChildOf( ON_UUID& parent_uuid) const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE && parent_uuid != ON_nil_uuid && pDE->m_parent_dimstyle == parent_uuid)
    return true;
  else
    return false;
}

void ON_DimStyle::SetParent( ON_UUID& parent_uuid)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
    pDE->m_parent_dimstyle = parent_uuid;
}

bool ON_DimStyleExtra::IsFieldOverride( int field_id) const
{
  if( field_id >= 0 && field_id < m_valid_fields.Count())
    return m_valid_fields[field_id];
  else
    return false;
}

void ON_DimStyleExtra::SetFieldOverride( int field_id, bool bOverride)
{
  if( field_id >= 0 && field_id < m_valid_fields.Count())
    m_valid_fields[field_id] = bOverride;
}

// Tolerances
// Tolerance style
//  0: None
//  1: Symmetrical
//  2: Deviation
//  3: Limits
//  4: Basic
int ON_DimStyle::ToleranceStyle() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->ToleranceStyle();
  else
    return DefaultToleranceStyle();
}
int ON_DimStyle::ToleranceResolution() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->ToleranceResolution();
  else
    return DefaultToleranceResolution();
}
double ON_DimStyle::ToleranceUpperValue() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->ToleranceUpperValue();
  else
    return DefaultToleranceUpperValue();
}
double ON_DimStyle::ToleranceLowerValue() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->ToleranceLowerValue();
  else
    return DefaultToleranceLowerValue();
}
double ON_DimStyle::ToleranceHeightScale() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->ToleranceHeightScale();
  else
    return DefaultToleranceHeightScale();
}
double ON_DimStyle::BaselineSpacing() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->BaselineSpacing();
  else
    return DefaultBaselineSpacing();
}

//static 
int ON_DimStyle::DefaultToleranceStyle()
{
  return 0;
}

//static 
int ON_DimStyle::DefaultToleranceResolution()
{
  return 4;
}

//static 
double ON_DimStyle::DefaultToleranceUpperValue()
{
  return 0.0;
}

//static 
double ON_DimStyle::DefaultToleranceLowerValue()
{
  return 0.0;
}

//static 
double ON_DimStyle::DefaultToleranceHeightScale()
{
  return 1.0;
}

//static 
double ON_DimStyle::DefaultBaselineSpacing()
{
  return 1.0;
}

//-------------------
void ON_DimStyle::Scale( double scale)
{
  if( ON_IsValid( scale) && scale > ON_SQRT_EPSILON)
  {
    m_extextension    *= scale;
    m_extoffset       *= scale;
    m_arrowsize       *= scale;
    m_centermark      *= scale;
    m_textgap         *= scale;
    m_textheight      *= scale;
    m_dimextension    *= scale;
    m_leaderarrowsize *= scale;

    ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
    if(pDE)
    {
      pDE->Scale( scale);
    }
  }
}

void ON_DimStyle::SetToleranceStyle( int style)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
  {
    pDE->SetToleranceStyle( style);
  }
}
void ON_DimStyle::SetToleranceResolution( int resolution)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
  {
    pDE->SetToleranceResolution( resolution);
  }
}
void ON_DimStyle::SetToleranceUpperValue( double upper_value)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
  {
    pDE->SetToleranceUpperValue( upper_value);
  }
}
void ON_DimStyle::SetToleranceLowerValue( double lower_value)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
  {
    pDE->SetToleranceLowerValue( lower_value);
  }
}
void ON_DimStyle::SetToleranceHeightScale( double scale)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
  {
    pDE->SetToleranceHeightScale( scale);
  }
}
void ON_DimStyle::SetBaselineSpacing( double spacing)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
  {
    pDE->SetBaselineSpacing( spacing);
  }
}

bool ON_DimStyle::DrawTextMask() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->DrawTextMask();
  else
    return false;
}

void ON_DimStyle::SetDrawTextMask(bool bDraw)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
    pDE->SetDrawTextMask(bDraw);
}

int ON_DimStyle::MaskColorSource() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->MaskColorSource();
  else
    return 0;
}

void ON_DimStyle::SetMaskColorSource(int source)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
    pDE->SetMaskColorSource(source);
}

ON_Color ON_DimStyle::MaskColor() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->MaskColor();
  else
    return 0;
}

void ON_DimStyle::SetMaskColor(ON_Color color)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
    pDE->SetMaskColor(color);
}

double ON_DimStyle::MaskOffsetFactor() const
{
  if(m_textheight != 0.0)
    return 0.5 * m_textgap / m_textheight;
  else
    return 0.0;
 }

void ON_DimStyle::SetDimScale(double scale)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
    pDE->SetDimScale(scale);
}

double ON_DimStyle::DimScale() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE) // && pDE->DimScaleSource() == 1)
      return pDE->DimScale();
  else
    return 1.0;
}

void ON_DimStyle::SetDimScaleSource(int source)
{
  ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, true);
  if(pDE)
    pDE->SetDimScaleSource(source);
}

int ON_DimStyle::DimScaleSource() const
{
  const ON_DimStyleExtra* pDE = ON_DimStyleExtra::DimStyleExtension( this, false);
  if(pDE)
    return pDE->DimScaleSource();
  else
    return 0;
}

// This function is temporary and will be removed next time the SDK can be modified.
class ON_DimStyleExtra* ON_DimStyle::DimStyleExtension()
{
  ON_DimStyleExtra* pExtra = ON_DimStyleExtra::Cast( GetUserData( ON_DimStyleExtra::m_ON_DimStyleExtra_class_id.Uuid()));
  return pExtra;
}

// returns true if they are the same
bool ON_DimStyle::CompareFields(const ON_DimStyle& other) const
{
  if((m_extextension               != other.m_extextension) ||
     (m_extoffset                  != other.m_extoffset) ||
     (m_arrowsize                  != other.m_arrowsize) ||
     (m_centermark                 != other.m_centermark) ||
     (m_textgap                    != other.m_textgap) ||
     (m_textheight                 != other.m_textheight) ||
     (m_textalign                  != other.m_textalign) ||
     (m_arrowtype                  != other.m_arrowtype) ||
     (m_angularunits               != other.m_angularunits) ||
     (m_lengthformat               != other.m_lengthformat) ||
     (m_angleformat                != other.m_angleformat) ||
     (m_angleresolution            != other.m_angleresolution) ||
     (m_lengthresolution           != other.m_lengthresolution) ||
     (m_fontindex                  != other.m_fontindex) ||
     (m_lengthfactor               != other.m_lengthfactor) ||
     (m_bAlternate                 != other.m_bAlternate) ||
     (m_alternate_lengthfactor     != other.m_alternate_lengthfactor) ||
     (m_alternate_lengthformat     != other.m_alternate_lengthformat) ||
     (m_alternate_lengthresolution != other.m_alternate_lengthresolution) ||
     (m_alternate_angleformat      != other.m_alternate_angleformat) ||
     (m_alternate_angleresolution  != other.m_alternate_angleresolution) ||
     (m_prefix                     != other.m_prefix) ||
     (m_suffix                     != other.m_suffix) ||
     (m_alternate_prefix           != other.m_alternate_prefix) ||
     (m_alternate_suffix           != other.m_alternate_suffix) ||
     (m_dimextension               != other.m_dimextension) ||
     (m_leaderarrowsize            != other.m_leaderarrowsize) ||
     (m_leaderarrowtype            != other.m_leaderarrowtype) ||
     (m_bSuppressExtension1        != other.m_bSuppressExtension1) ||
     (m_bSuppressExtension2        != other.m_bSuppressExtension2))
    return false;

  const ON_DimStyleExtra* pDEo = ON_DimStyleExtra::DimStyleExtension(&other,false);
  const ON_DimStyleExtra* pDE  = ON_DimStyleExtra::DimStyleExtension(this,false);
  if((pDEo == 0 && pDE != 0) || (pDEo != 0 && pDE == 0))
    return false;
  if(pDE != 0)
    return pDE->CompareFields(pDEo);
  return true;
}
