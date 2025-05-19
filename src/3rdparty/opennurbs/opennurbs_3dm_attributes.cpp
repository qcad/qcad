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
#include "opennurbs_internal_defines.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

class ON_3dmObjectAttributesPrivate
{
public:
  ON_3dmObjectAttributesPrivate() = delete;
  ON_3dmObjectAttributesPrivate(const ON_3dmObjectAttributes* attr);
  ~ON_3dmObjectAttributesPrivate() = default;
  ON_3dmObjectAttributesPrivate& operator=(const ON_3dmObjectAttributesPrivate&) = default;

  bool operator==(const ON_3dmObjectAttributesPrivate&) const;
  bool operator!=(const ON_3dmObjectAttributesPrivate&) const;

  ON::SectionAttributesSource m_section_attributes_source = ON::SectionAttributesSource::FromLayer;
  double m_linetype_scale = 1.0;
  ON_Color m_hatch_background_fill;
  bool m_hatch_boundary_visible = false;
  ON::SectionLabelStyle m_section_label_style = ON::SectionLabelStyle::None;

  std::shared_ptr<ON_Linetype> m_custom_linetype;
  std::shared_ptr<ON_SectionStyle> m_custom_section_style;

  ON_DecalCollection m_decals;
  ON_MeshModifiers m_mesh_modifiers;
};

ON_3dmObjectAttributesPrivate::ON_3dmObjectAttributesPrivate(const ON_3dmObjectAttributes* attr)
  :
  m_decals(const_cast<ON_3dmObjectAttributes*>(attr))
{
  m_hatch_background_fill = ON_Color::UnsetColor;
}

bool ON_3dmObjectAttributesPrivate::operator==(const ON_3dmObjectAttributesPrivate& other) const
{
  if (m_section_attributes_source != other.m_section_attributes_source)
    return false;

  if (m_linetype_scale != other.m_linetype_scale)
    return false;

  if (m_hatch_background_fill != other.m_hatch_background_fill)
    return false;

  if (m_hatch_boundary_visible != other.m_hatch_boundary_visible)
    return false;

  if (m_section_label_style != other.m_section_label_style)
    return false;

  {
    const ON_SectionStyle* customThis = m_custom_section_style.get();
    const ON_SectionStyle* customOther = other.m_custom_section_style.get();
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

  const ON_Linetype* customThis = m_custom_linetype.get();
  const ON_Linetype* customOther = other.m_custom_linetype.get();
  if (customThis != customOther)
    return false;

  return true;
}

bool ON_3dmObjectAttributesPrivate::operator!=(const ON_3dmObjectAttributesPrivate& other) const
{
  return !ON_3dmObjectAttributesPrivate::operator==(other);
}

static const ON_3dmObjectAttributesPrivate DefaultAttributesPrivate(nullptr);

ON_OBJECT_IMPLEMENT( ON_3dmObjectAttributes, ON_Object, "A828C015-09F5-477c-8665-F0482F5D6996" );

ON_3dmObjectAttributes::ON_3dmObjectAttributes()
  : m_color(0,0,0)
  , m_plot_color(0,0,0)
{
  // No longer need to call Default. All members are initialized in class declaration
  // Default();
}

ON_3dmObjectAttributes::~ON_3dmObjectAttributes()
{
  if (m_private)
    delete m_private;
}

void ON_3dmObjectAttributes::CopyHelper(const ON_3dmObjectAttributes& src)
{
  // private helper for the copy constructor and operator=.
  m_uuid = src.m_uuid;
  m_name = src.m_name;
  m_url  = src.m_url;
  m_layer_index = src.m_layer_index;
  m_linetype_index = src.m_linetype_index;
  m_material_index = src.m_material_index;
  m_rendering_attributes = src.m_rendering_attributes;
  m_color = src.m_color;
  m_plot_color = src.m_plot_color;
  m_display_order = src.m_display_order;
  m_plot_weight_mm = src.m_plot_weight_mm;
  m_object_decoration = src.m_object_decoration;
  m_wire_density = src.m_wire_density;
  m_viewport_id = src.m_viewport_id;
  m_space = src.m_space;
  m_bVisible = src.m_bVisible;
  m_mode = src.m_mode;
  m_color_source = src.m_color_source;
  m_plot_color_source = src.m_plot_color_source;
  m_plot_weight_source = src.m_plot_weight_source;
  m_material_source = src.m_material_source;
  m_linetype_source = src.m_linetype_source;
  m_reserved_0 = src.m_reserved_0;
  m_object_frame = src.m_object_frame;
  m_group = src.m_group;
  if (m_private)
    delete m_private;
  m_private = nullptr;
  if (src.m_private)
  {
    m_private = new ON_3dmObjectAttributesPrivate(this);
    *m_private = *src.m_private;
  }
  m_dmref = src.m_dmref;
}

ON_3dmObjectAttributes::ON_3dmObjectAttributes(const ON_3dmObjectAttributes& src) 
  : ON_Object(src)
  , m_color(0, 0, 0)
  , m_plot_color(0, 0, 0)
{
  CopyHelper(src);
}

bool ON_3dmObjectAttributes::operator==(const ON_3dmObjectAttributes& other) const
{
  if ( ON_UuidCompare( m_uuid, other.m_uuid ) )
    return false;
  if ( m_name.CompareOrdinal(other.m_name,false) )
    return false;
  if ( m_url.CompareOrdinal(other.m_url,false) )
    return false;
  if ( m_layer_index != other.m_layer_index )
    return false;
  if ( m_material_index != other.m_material_index )
    return false;
  if ( m_linetype_index != other.m_linetype_index )
    return false;
  if ( m_color != other.m_color )
    return false;
  if ( m_plot_color != other.m_plot_color )
    return false;
  if ( m_display_order != other.m_display_order )
    return false;
  if ( m_object_decoration != other.m_object_decoration )
    return false;
  if ( m_wire_density != other.m_wire_density )
    return false;
  if ( m_mode != other.m_mode )
    return false;
  if ( m_color_source != other.m_color_source )
    return false;
  if ( m_linetype_source != other.m_linetype_source )
    return false;
  if ( m_plot_color_source != other.m_plot_color_source )
    return false;
  if ( m_material_source != other.m_material_source )
    return false;
  if ( m_plot_weight_mm != other.m_plot_weight_mm )
    return false;
  if ( m_plot_weight_source != other.m_plot_weight_source )
    return false;

  int count = m_group.Count();
  if ( count != other.m_group.Count() )
    return false;
  if ( count > 0 )
  {
    const int* a = m_group.Array();
    const int* b = other.m_group.Array();
    if ( memcmp( a, b, count*sizeof(*a) ) )
      return false;
  }

  if ( m_bVisible != other.m_bVisible )
    return false;

  if ( m_rendering_attributes.Compare(other.m_rendering_attributes) )
    return false;

  if ( m_space != other.m_space)
    return false;

  if ( m_viewport_id != other.m_viewport_id )
    return false;

  if ( m_dmref != other.m_dmref )
    return false;

  if (m_object_frame != other.m_object_frame)
    return false;

  if (m_private && other.m_private)
  {
    if (*m_private != *other.m_private)
      return false;
  }
  else
  {
    if (m_private && *m_private != DefaultAttributesPrivate)
      return false;
    if (other.m_private && *other.m_private != DefaultAttributesPrivate)
      return false;
  }

  return true;
}

bool ON_3dmObjectAttributes::operator!=(const ON_3dmObjectAttributes& other) const
{
  return !ON_3dmObjectAttributes::operator==(other);
}


ON_3dmObjectAttributes& ON_3dmObjectAttributes::operator=(const ON_3dmObjectAttributes& src )
{
  if ( this != &src ) 
  {
    ON_Object::operator=(src);
    CopyHelper(src);
  }
  return *this;
}

bool ON_3dmObjectAttributes::UpdateReferencedComponents(
  const class ON_ComponentManifest& source_manifest,
  const class ON_ComponentManifest& destination_manifest,
  const class ON_ManifestMap& manifest_map
  )
{
  bool rc = true;

  // Update layer reference
  if (m_layer_index >= 0)
  {
    int destination_layer_index = ON_UNSET_INT_INDEX;
    if (manifest_map.GetAndValidateDestinationIndex(ON_ModelComponent::Type::Layer, m_layer_index, destination_manifest, &destination_layer_index))
    {
      m_layer_index = destination_layer_index;
    }
    else
    {
      ON_ERROR("Unable to update layer reference.");
      rc = false;
      m_layer_index = ON_3dmObjectAttributes::DefaultAttributes.m_layer_index;
    }
  }

  // Update render material reference
  if (m_material_index >= 0)
  {
    int destination_material_index = ON_UNSET_INT_INDEX;
    if (manifest_map.GetAndValidateDestinationIndex(ON_ModelComponent::Type::RenderMaterial, m_material_index, destination_manifest, &destination_material_index))
    {
      m_material_index = destination_material_index;
    }
    else
    {
      ON_ERROR("Unable to update render material reference.");
      rc = false;
      m_material_index = ON_3dmObjectAttributes::DefaultAttributes.m_material_index;
    }
  }

  // Update line pattern reference
  if (m_linetype_index >= 0)
  {
    int destination_line_pattern_index = ON_UNSET_INT_INDEX;
    if (manifest_map.GetAndValidateDestinationIndex(ON_ModelComponent::Type::LinePattern, m_linetype_index, destination_manifest, &destination_line_pattern_index))
    {
      m_linetype_index = destination_line_pattern_index;
    }
    else
    {
      ON_ERROR("Unable to update line pattern reference.");
      rc = false;
      m_linetype_index = ON_3dmObjectAttributes::DefaultAttributes.m_linetype_index;
    }
  }

  // Update group references
  unsigned int group_count = 0;
  for (unsigned int i = 0; i < m_group.UnsignedCount(); i++)
  {
    int group_index = m_group[i];
    int destination_group_index_index = ON_UNSET_INT_INDEX;
    if (!manifest_map.GetAndValidateDestinationIndex(ON_ModelComponent::Type::Group, group_index, destination_manifest, &destination_group_index_index))
    {
      ON_ERROR("Unable to update group reference.");
      rc = false;
      continue;
    }
    if (destination_group_index_index < 0)
    {
      ON_ERROR("Unable to update group reference.");
      rc = false;
      continue;
    }
    m_group[group_count] = destination_group_index_index;
    group_count++;
  }
  m_group.SetCount(group_count);

  return rc;
}

void ON_3dmObjectAttributes::Default()
{
  ON_3dmObjectAttributes default_attrs;
  *this = default_attrs;
  // the following is no longer necessary now that initial values are defined in
  // class declaration
  /*
  PurgeUserData();
  m_uuid = ON_nil_uuid;
  m_name.Destroy();
  m_url.Destroy();
  m_layer_index = 0;
  m_linetype_index = -1; // continuous
  m_material_index = -1; // white diffuse
  m_rendering_attributes.Default();
  m_color = ON_Color(0,0,0);
  m_plot_color = ON_Color(0,0,0); // Do not change to ON_UNSET_COLOR
  m_display_order = 0;
  m_plot_weight_mm = 0.0;
  m_object_decoration = ON::no_object_decoration;
  m_wire_density = 1;
  m_mode = ON::normal_object;
  m_bVisible = true;
  m_color_source       = ON::color_from_layer;
  m_material_source    = ON::material_from_layer;
  m_linetype_source    = ON::linetype_from_layer;
  m_plot_color_source  = ON::plot_color_from_layer;
  m_plot_weight_source = ON::plot_weight_from_layer;
  m_group.Destroy();
  m_space = ON::model_space;
  m_viewport_id = ON_nil_uuid;
  m_dmref.Destroy();

  if (m_private)
    delete m_private;
  m_private = nullptr;
  */
}


// {9BBB37E9-2131-4fb8-B9C6-5524859B98B8}
const ON_UUID ON_ObsoletePageSpaceObjectId =
{ 0x9bbb37e9, 0x2131, 0x4fb8, { 0xb9, 0xc6, 0x55, 0x24, 0x85, 0x9b, 0x98, 0xb8 } };

enum ON_3dmObjectAttributesTypeCodes : unsigned char
{
  // TODO: add older itemids to this enum in order to make the read/write
  //       code easier for a developer to parse
  ObsoleteLineCapStyleSource = 23,
  ObsoleteLineCapStyle = 24,
  ObsoleteLineJoinStyleSource = 25,
  ObsoleteLineJoinStyle = 26,
  ObsoleteClipParticipationSource = 27,
  SelectiveClippingData = 28,
  // 18 Oct 2021 S. Baer
  // file version 2.4: add section hatch attributes
  SectionAttributesSource = 29,
  SectionHatchIndex = 30,
  SectionHatchScale = 31,
  SectionHatchRotation = 32,
  // 5 Nov 2021 S. Baer
  // file version 2.5: add linetype scale
  LinetypeScale = 33,
  // 10 Jan 2022 S. Baer
  // file version 2.6: add hatch background fill, hatch boundary visible
  HatchBackgroundFill = 34,
  HatchBoundaryVisible = 35,
  // file version 2.7 was skipped
  // 26 Jan 2022 Andy Le Bihan
  // file version 2.8: object frame
  ObjectFrame = 36,
  // 15 Jun 2022 S. Baer
  // file version 2.9: SectionFillRule
  SectionFillRule = 37,
  // 30 Nov 2022 S. Baer
  // file version 2.10: custom linetype
  CustomLinetype = 38,
  // 18 Apr 2023 S. Baer
  // file version 2.11: custom section style
  CustomSectionStyle = 39,
  // 10 May 2023 S. Baer
  // file version 2.12: ClippingPlaneLabelStyle
  ClippingPlaneLabelStyle = 40,
  // 11 May 2023 S. Baer
  // file version 2.13: how the participation list for clipping planes is interpreted
  ObsoleteSelectiveClippingListType = 41,

  // add items here
  LastAttributeTypeCode = 41
};

bool ON_3dmObjectAttributes::Internal_ReadV5( ON_BinaryArchive& file )
{
  unsigned char itemid = 0xFF;
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if ( rc && 2 != major_version )
    rc = false;

  while(rc)
  {
    if (!rc) break;
    rc = file.ReadUuid(m_uuid);
    if (!rc) break;
    //rc = file.ReadInt(&m_layer_index);
    rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::Layer, &m_layer_index);
    if (!rc) break;

    // read non-default settings - skip everything else
    rc = file.ReadChar(&itemid);
    if (!rc) break;
    if ( 0 == itemid )
      break;
    
    if ( 1 == itemid )
    {
      ON_wString name;
      rc = file.ReadString(name);
      if (!rc) break;
      SetName(name,true);

      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 2 == itemid )
    {
      rc = file.ReadString(m_url);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 3 == itemid )
    {
      //rc = file.ReadInt(&m_linetype_index);
      rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::LinePattern, &m_linetype_index);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 4 == itemid )
    {
      //rc = file.ReadInt(&m_material_index);
      rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::RenderMaterial, &m_material_index);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 5 == itemid )
    {
      rc = m_rendering_attributes.Read(file);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 6 == itemid )
    {
      rc = file.ReadColor(m_color);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 7 == itemid )
    {
      rc = file.ReadColor(m_plot_color);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 8 == itemid )
    {
      rc = file.ReadDouble(&m_plot_weight_mm);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 9 == itemid )
    {
      unsigned char c = 0;
      rc = file.ReadChar(&c);
      if (!rc) break;
      m_object_decoration = ON::ObjectDecoration(c);
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 10 == itemid )
    {
      rc = file.ReadInt(&m_wire_density);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 11 == itemid )
    {
      rc = file.ReadBool(&m_bVisible);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 12 == itemid )
    {
      rc = file.ReadChar(&m_mode);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 13 == itemid )
    {
      rc = file.ReadChar(&m_color_source);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 14 == itemid )
    {
      rc = file.ReadChar(&m_plot_color_source);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 15 == itemid )
    {
      rc = file.ReadChar(&m_plot_weight_source);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 16 == itemid )
    {
      rc = file.ReadChar(&m_material_source);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 17 == itemid )
    {
      rc = file.ReadChar(&m_linetype_source);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 18 == itemid )
    {
      rc = file.Read3dmReferencedComponentIndexArray(ON_ModelComponent::Type::Group, m_group);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 19 == itemid )
    {
      unsigned char c = 0;
      rc = file.ReadChar(&c);
      if (!rc) break;
      m_space = ON::ActiveSpace(c);
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 20 == itemid )
    {
      rc = file.ReadUuid(m_viewport_id);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }
    if ( 21 == itemid )
    {
      rc = file.ReadArray(m_dmref);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }

    // items 1 - 21 are in chunk version 2.0 files
    if ( minor_version <= 0 )
      break;

    // 28 Nov. 2009 - S. Baer
    // Added m_display_order to version 2.1 files
    if ( 22 == itemid )
    {
      rc = file.ReadInt(&m_display_order);
      if (!rc) break;
      rc = file.ReadChar(&itemid);
      if ( !rc || 0 == itemid ) break;
    }

    if ( minor_version <= 1 )
      break;

    // 12 Aug 2021 S. Baer
    // Items 23, 24, 25, 26 were in a version of Rhino 8 WIP for about 24 hours.
    // They were most likely never used by anyone, but just in case let's test,
    // read, and throw away.
    if (ON_3dmObjectAttributesTypeCodes::ObsoleteLineCapStyleSource == itemid) //23
    {
      unsigned char source = 0;
      rc = file.ReadChar(&source);
      if (!rc) break;
      //SetLineCapStyleSource(ON::ObjectLineCapStyleSourceFromUnsigned(source));
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (ON_3dmObjectAttributesTypeCodes::ObsoleteLineCapStyle == itemid) //24
    {
      unsigned char style = 0;
      rc = file.ReadChar(&style);
      if (!rc) break;
      //SetLineCapStyle(ON::LineCapStyleFromUnsigned(style));
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (ON_3dmObjectAttributesTypeCodes::ObsoleteLineJoinStyleSource == itemid) //25
    {
      unsigned char source = 0;
      rc = file.ReadChar(&source);
      if (!rc) break;
      //SetLineJoinStyleSource(ON::ObjectLineJoinStyleSourceFromUnsigned(source));
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (ON_3dmObjectAttributesTypeCodes::ObsoleteLineJoinStyle == itemid) //26
    {
      unsigned char style = 0;
      rc = file.ReadChar(&style);
      if (!rc) break;
      //SetLineJoinStyle(ON::LineJoinStyleFromUnsigned(style));
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 2)
      break;

    if (ON_3dmObjectAttributesTypeCodes::ObsoleteClipParticipationSource == itemid) //27
    {
      unsigned char clip_participation_source = 0;
      rc = file.ReadChar(&clip_participation_source);
      if (!rc) break;
      //SetClipParticipationSource(ON::ClipParticipationSourceFromUnsigned(clip_participation_source));
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (ON_3dmObjectAttributesTypeCodes::SelectiveClippingData == itemid) //28
    {
      bool clipping_proof = false;
      rc = file.ReadBool(&clipping_proof);
      if (!rc) break;
      ON_UuidList selectiveClipping;
      rc = selectiveClipping.Read(file);
      if (!rc) break;
      //if (clipping_proof)
      //  SetClipParticipationForNone();
      //else
      //{
      //  if (selectiveClipping.Count() > 0)
      //  {
      //    SetClipParticipationList(selectiveClipping.Array(), selectiveClipping.Count(), true);
      //  }
      //}
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 3)
      break;

    if (ON_3dmObjectAttributesTypeCodes::SectionAttributesSource == itemid) //29
    {
      unsigned char section_attr_source = 0;
      rc = file.ReadChar(&section_attr_source);
      if (!rc) break;
      SetSectionAttributesSource(ON::SectionAttributesSourceFromUnsigned(section_attr_source));
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }
    if (ON_3dmObjectAttributesTypeCodes::SectionHatchIndex == itemid) //30
    {
      int hatch_index = 0;
      rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::HatchPattern, &hatch_index);
      if (!rc) break;
      ON_SectionStyle ss;
      CustomSectionStyle(&ss);
      ss.SetHatchIndex(hatch_index);
      SetCustomSectionStyle(ss);
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }
    if (ON_3dmObjectAttributesTypeCodes::SectionHatchScale == itemid) //31
    {
      double hatch_scale = 1;
      rc = file.ReadDouble(&hatch_scale);
      if (!rc) break;
      ON_SectionStyle ss;
      CustomSectionStyle(&ss);
      ss.SetHatchScale(hatch_scale);
      SetCustomSectionStyle(ss);
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }
    if (ON_3dmObjectAttributesTypeCodes::SectionHatchRotation == itemid) //32
    {
      double hatch_rotation = 0;
      rc = file.ReadDouble(&hatch_rotation);
      if (!rc) break;
      ON_SectionStyle ss;
      CustomSectionStyle(&ss);
      ss.SetHatchRotation(hatch_rotation);
      SetCustomSectionStyle(ss);
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 4)
      break;

    if (ON_3dmObjectAttributesTypeCodes::LinetypeScale == itemid) //33
    {
      double scale = 1.0;
      rc = file.ReadDouble(&scale);
      if (!rc) break;
      SetLinetypePatternScale(scale);
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 5)
      break;

    if (ON_3dmObjectAttributesTypeCodes::HatchBackgroundFill == itemid) // 34
    {
      ON_Color color = ON_Color::UnsetColor;
      rc = file.ReadColor(color);
      if (!rc) break;
      SetHatchBackgroundFillColor(color);
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (ON_3dmObjectAttributesTypeCodes::HatchBoundaryVisible == itemid) // 35
    {
      bool visible = false;
      rc = file.ReadBool(&visible);
      if (!rc) break;
      SetHatchBoundaryVisible(visible);
      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 6)
      break;

    // nothing added in 2.7
    if (minor_version <= 7)
      break;

    if (ON_3dmObjectAttributesTypeCodes::ObjectFrame == itemid) // 36
    {
      ON_Xform object_frame = ON_Xform::Nan;
      rc = file.ReadXform(object_frame);
      if (!rc) break;

      m_object_frame = ON_Plane::World_xy;
      m_object_frame.Transform(object_frame);

      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 8)
      break;

    if (ON_3dmObjectAttributesTypeCodes::SectionFillRule == itemid) // 37
    {
      unsigned char c = 0;
      rc = file.ReadChar(&c);
      if (!rc) break;
      ON_SectionStyle ss;
      CustomSectionStyle(&ss);
      ss.SetSectionFillRule(ON::SectionFillRuleFromUnsigned(c));

      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 9)
      break;

    if (ON_3dmObjectAttributesTypeCodes::CustomLinetype == itemid) // 38
    {
      ON_Linetype lt;
      rc = lt.Read(file);
      if (!rc) break;

      SetCustomLinetype(lt);

      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 10)
      break;

    if (ON_3dmObjectAttributesTypeCodes::CustomSectionStyle == itemid) // 39
    {
      ON_SectionStyle sectionStyle;
      rc = sectionStyle.Read(file);
      if (!rc) break;

      SetCustomSectionStyle(sectionStyle);

      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 11)
      break;

    if (ON_3dmObjectAttributesTypeCodes::ClippingPlaneLabelStyle == itemid) // 40
    {
      unsigned char c = 0;
      rc = file.ReadChar(&c);
      if (!rc) break;
      SetClippingPlaneLabelStyle(ON::SectionLabelStyleFromUnsigned(c));

      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 12)
      break;

    if (ON_3dmObjectAttributesTypeCodes::ObsoleteSelectiveClippingListType == itemid) // 41
    {
      bool b = true;
      rc = file.ReadBool(&b);
      if (!rc) break;
      //if (nullptr == m_private)
      //  m_private = new ON_3dmObjectAttributesPrivate(this);
      //m_private->m_clipplane_list_is_participation = b;

      rc = file.ReadChar(&itemid);
      if (!rc || 0 == itemid) break;
    }

    if (minor_version <= 13)
      break;

    // Add new item reading above and increment the LastAttributeTypeCode value
    // in the enum. Be sure to test reading of old and new files by old and new
    // code, before checking in your changes.
    //
    if ( itemid > ON_3dmObjectAttributesTypeCodes::LastAttributeTypeCode )
    {
      // we are reading file written with code newer
      // than this code (minor_version > 2)
      itemid = 0;
    }

    break;
  }

  if ( rc && 0 != itemid )
  {
    ON_ERROR("Bug in ON_3dmObjectAttributes::ReadV5Helper or WriteV5Helper");
  }

  return rc;
}

bool ON_3dmObjectAttributes::Read( ON_BinaryArchive& file )
{
  Default();
  if (    file.Archive3dmVersion() >= 5 
       && file.ArchiveOpenNURBSVersion() >= 200712190 )
  {
    return Internal_ReadV5(file);
  }
  int i;
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if ( rc && major_version == 1 ) 
  {
    if (rc) rc = file.ReadUuid(m_uuid);
    if (rc) rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::Layer,&m_layer_index);
    if (rc) rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::RenderMaterial,&m_material_index);
    if (rc) rc = file.ReadColor(m_color);
    
    while(rc)
    {
      // OBSOLETE if (rc) rc = file.ReadLineStyle(m_line_style); // 23 March 2005 Dale Lear
      // replaced with
      short s = 0;
      double x;
      rc = file.ReadShort(&s); 
      if (!rc) break;
      if ( file.Archive3dmVersion() < 4 || file.ArchiveOpenNURBSVersion() < 200503170 )
      {
        // ignore unused linestyle info in old files
        // This bit keeps the curve arrowheads from V3 showing up
        // in V4.
        m_object_decoration = ON::ObjectDecoration( (s & ON::both_arrowhead) );
      }
      rc = file.ReadShort(&s);
      if (!rc) break;
      rc = file.ReadDouble(&x);
      if (!rc) break;
      rc = file.ReadDouble(&x);
      break;
    }

    if (rc) rc = file.ReadInt(&m_wire_density);
    if (rc) rc = file.ReadChar(&m_mode);

    if (rc) rc = file.ReadChar(&m_color_source);
    if (rc) m_color_source = (unsigned char)ON::ObjectColorSource(m_color_source);

    if (rc) rc = file.ReadChar(&m_linetype_source);
    if (rc) m_linetype_source = (unsigned char)ON::ObjectLinetypeSource(m_linetype_source);

    if (rc) rc = file.ReadChar(&m_material_source);
    if (rc) m_material_source = (unsigned char)ON::ObjectMaterialSource(m_material_source);

    ON_wString name;
    if (rc) rc = file.ReadString(name);
    if (rc)
      SetName(name, true);

    if (rc) rc = file.ReadString(m_url);

    m_bVisible = (Mode() != ON::hidden_object);
    if ( rc && minor_version >= 1 ) 
    {
      rc = file.Read3dmReferencedComponentIndexArray(ON_ModelComponent::Type::Group, m_group);
      if ( rc && minor_version >= 2 )
      {
        rc = file.ReadBool(&m_bVisible);

        if ( rc && minor_version >= 3 )
        {
          rc = file.ReadArray(m_dmref);     

          if (rc && minor_version >= 4 )
          {
            // 23 March 2005 Dale Lear
            //    Added m_plot_color_source and m_plot_color
            i = 0;
            if (rc) rc = file.ReadInt(&i);
            if (rc) m_object_decoration = ON::ObjectDecoration(i);
            if (rc) rc = file.ReadChar(&m_plot_color_source);
            if (rc) m_plot_color_source = (unsigned char)ON::PlotColorSource(m_plot_color_source);
            if (rc) rc = file.ReadColor( m_plot_color );
            if (rc) rc = file.ReadChar(&m_plot_weight_source);
            if (rc) m_plot_weight_source = (unsigned char)ON::PlotWeightSource(m_plot_weight_source);
            if (rc) rc = file.ReadDouble(&m_plot_weight_mm);


            if (rc && minor_version >= 5 )
            {
              // version 1.5 fields 11 April 2005
              if (rc) rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::LinePattern,&m_linetype_index);

              // version 1.6 fields 2 September 2005
              if (rc && minor_version >= 6 )
              {
                unsigned char uc = 0;
                rc = file.ReadChar(&uc);
                if (rc)
                {
                  m_space = (1 == uc) ? ON::page_space : ON::model_space;
                  m_dmref.Empty();
                  int i_local, count=0;
                  rc = file.ReadInt(&count);
                  if (rc && count > 0)
                  {
                    m_dmref.SetCapacity(count);
                    for ( i_local = 0; i_local < count && rc; i_local++)
                    {
                      ON_DisplayMaterialRef& dmr = m_dmref.AppendNew();
                      rc = file.ReadUuid(dmr.m_viewport_id);
                      if (rc) rc = file.ReadUuid(dmr.m_display_material_id);
                      if ( rc )
                      {
                        // Assigning an object to a page started out as
                        // using dmrs.  The way the runtime info is saved
                        // has changed, but, at this point, I can't change
                        // the way the information is saved in the file and
                        // it doesn't matter.
                        if ( 0 == ON_UuidCompare(&ON_ObsoletePageSpaceObjectId,&dmr.m_display_material_id) )
                        {
                          m_viewport_id = dmr.m_viewport_id;
                          m_dmref.Remove();
                        }
                      }
                    }
                    if ( 0 == m_dmref.Count() )
                      m_dmref.Destroy();
                  }
                }

                if ( rc && minor_version >= 7 )
                {
                  // version 1.7 fields 6 June 2006
                  if (rc) rc = m_rendering_attributes.Read(file);
                }
              }
            }
          }
        }
      }
    }
  }
  else 
  {
    rc = false;
  }
  return rc;
}

bool ON_3dmObjectAttributes::Internal_WriteV5( ON_BinaryArchive& file ) const
{
  if (m_private)
  {
    // Have the decal collection update the user data if anything has changed and there
    // is actually decal data for which a user data object is needed. Note that this is
    // not actually needed when running Rhino because the RDK decal UI directly updates
    // the user data when changes are made. This is only needed when using ONX_Model and
    // File3dm outside of Rhino, in case the programmer sets a decal property.
    const unsigned int archive_3dm_version = file.Archive3dmVersion();
    m_private->m_decals.UpdateUserData(archive_3dm_version);
  }

  unsigned char c;
  // 29 Nov. 2009 S. Baer
  // Chunk version updated to 2.1 in order to support m_display_order
  // 12 Aug 2021 S. Baer
  // The next minor chunk version should be 3. There was a 24 hour period
  // where files could contain some extra information in a 2.2 chunk
  // 29 Sept 2021 S. Baer
  // Chunk version updated to 2.3 to support ClipParticipationSource and
  // clip participation list
  // 18 Oct 2021 S. Baer
  // Chunk version = 2.4 to support section hatch attributes
  // 5 Nov 2021 S. Baer
  // Chunk version = 2.5 to support linetype scale
  // 10 Jan 2022 S. Baer
  // Chunk version = 2.6 to support hatch background fill and hatch boundary visibility
  // 26 Jan 2022 Andy Le Bihan
  // Chunk version 2.7 was skipped
  // Chunk version = 2.8 to support object frame.
  // 15 Jun 2022 S. Baer
  // Chunk version = 2.9 to support SectionFillRule
  // 30 Nov 2022 S. Baer
  // Chunk version = 2.10 to support custom linetype
  // 18 Apr 2023 S. Baer
  // Chunk version = 2.11 to support custom section style
  // 10 May 2023 S. Baer
  // Chunk version = 2.12 to support ClippingPlaneLabelStyle
  // 11 May 2023 S. Baer
  // Chunk version = 2.13 to support SelectiveClippingListType
  bool rc = file.Write3dmChunkVersion(2,13);
  while(rc)
  {
    if (!rc) break;
    rc = file.WriteUuid(m_uuid);
    if (!rc) break;
    rc = file.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::Layer, m_layer_index);
    if (!rc) break;

    // write non-default settings - skip everything else
    if ( !m_name.IsEmpty() )
    {
      c = 1;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteString(m_name);
      if (!rc) break;
    }
    if ( !m_url.IsEmpty() )
    {
      c = 2;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteString(m_url);
      if (!rc) break;
    }
    if ( -1 != m_linetype_index )
    {
      c = 3;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::LinePattern, m_linetype_index);
      if (!rc) break;
    }
    if ( -1 != m_material_index && MaterialSource() == ON::material_from_object)
    {
      c = 4;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::RenderMaterial, m_material_index);
      if (!rc) break;
    }
    if (    m_rendering_attributes.m_mappings.Count() > 0
         || m_rendering_attributes.m_materials.Count() > 0
         || true != m_rendering_attributes.m_bCastsShadows
         || true != m_rendering_attributes.m_bReceivesShadows
         || false != m_rendering_attributes.AdvancedTexturePreview()
         )
    {
      c = 5;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = m_rendering_attributes.Write(file);
      if (!rc) break;
    }
    if ( 0 != m_color )
    {
      c = 6;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteColor(m_color);
      if (!rc) break;
    }
    if ( 0 != m_plot_color )
    {
      c = 7;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteColor(m_plot_color);
      if (!rc) break;
    }
    if ( 0.0 != m_plot_weight_mm )
    {
      c = 8;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteDouble(m_plot_weight_mm);
      if (!rc) break;
    }
    if ( ON::no_object_decoration != m_object_decoration )
    {
      c = 9;
      rc = file.WriteChar(c);
      if (!rc) break;
      c = (unsigned char)m_object_decoration;
      rc = file.WriteChar(c);
      if (!rc) break;
    }
    if ( 1 != m_wire_density )
    {
      c = 10;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteInt(m_wire_density);
      if (!rc) break;
    }
    if ( true != m_bVisible )
    {
      c = 11;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteBool(m_bVisible);
      if (!rc) break;
    }
    if ( ON::normal_object != m_mode )
    {
      c = 12;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteChar(m_mode);
      if (!rc) break;
    }
    if ( ON::color_from_layer != m_color_source )
    {
      c = 13;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteChar(m_color_source);
      if (!rc) break;
    }
    if ( ON::plot_color_from_layer != m_plot_color_source )
    {
      c = 14;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteChar(m_plot_color_source);
      if (!rc) break;
    }
    if ( ON::plot_weight_from_layer != m_plot_weight_source )
    {
      c = 15;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteChar(m_plot_weight_source);
      if (!rc) break;
    }
    if ( ON::material_from_layer != m_material_source )
    {
      c = 16;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteChar(m_material_source);
      if (!rc) break;
    }
    if ( ON::linetype_from_layer != m_linetype_source )
    {
      c = 17;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteChar(m_linetype_source);
      if (!rc) break;
    }
    if ( m_group.Count() > 0 )
    {
      c = 18;
      rc = file.WriteChar(c);
      if (!rc) break;
      int count = m_group.Count();
      rc = file.WriteInt(count);
      for ( int i = 0; i < count && rc; i++)
        rc = file.Write3dmReferencedComponentIndex(ON_ModelComponent::Type::Group, m_group[i]);
      if (!rc) break;
    }
    if ( ON::model_space != m_space )
    {
      c = 19;
      rc = file.WriteChar(c);
      if (!rc) break;
      c = (unsigned char)m_space;
      rc = file.WriteChar(c);
      if (!rc) break;
    }
    if ( !ON_UuidIsNil(m_viewport_id) )
    {
      c = 20;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteUuid(m_viewport_id);
      if (!rc) break;
    }
    if ( m_dmref.Count() > 0 )
    {
      c = 21;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteArray(m_dmref);
      if (!rc) break;
    }

    // 29 Nov. 2009 - S. Baer
    // Only write m_display_order if it's value!=0
    // m_display_order is written to version 2.1 files
    if ( 0 != m_display_order )
    {
      c = 22;
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteInt(m_display_order);
      if (!rc) break;
    }

    const ON_SectionStyle* customSectionStyle = CustomSectionStyle();
    // 12 Aug 2021 S. Baer
    // Items 23, 24, 25, 26 were in a version of Rhino 8 WIP for about 24 hours.
    // They were most likely never used by anyone

    // New attribute non-default values are all held in the m_private variable.
    // If this variable is nullptr, then all of the following properties will
    // be default which means there is no need to check their state
    if (m_private)
    {
      //if (ClipParticipationSource() != ON::ClipParticipationSource::FromLayer)
      //{
      //  c = ON_3dmObjectAttributesTypeCodes::ClipParticipationSource; // 27
      //  rc = file.WriteChar(c);
      //  if (!rc) break;
      //  rc = file.WriteChar((unsigned char)ClipParticipationSource());
      //  if (!rc) break;
      //}

      //{
      //  bool forAllClippingPlanes = true;
      //  bool forNoClippingPlanes = false;
      //  ON_UuidList selectiveClipping;
      //  bool isParticipationList = true;
      //  GetClipParticipation(forAllClippingPlanes, forNoClippingPlanes, selectiveClipping, isParticipationList);
      //  if (!forAllClippingPlanes)
      //  {
      //    c = ON_3dmObjectAttributesTypeCodes::SelectiveClippingData; // 28
      //    rc = file.WriteChar(c);
      //    if (!rc) break;
      //    rc = file.WriteBool(forNoClippingPlanes);
      //    if (!rc) break;
      //    rc = selectiveClipping.Write(file);
      //    if (!rc) break;
      //  }
      //}

      if (SectionAttributesSource() != ON::SectionAttributesSource::FromLayer)
      {
        c = ON_3dmObjectAttributesTypeCodes::SectionAttributesSource; // 29
        rc = file.WriteChar(c);
        if (!rc) break;
        rc = file.WriteChar((unsigned char)SectionAttributesSource());
        if (!rc) break;
      }

      // 23 April 2023 S. Baer
      // Stop writing individual section attributes. All section attribute IO has been
      // moved to writing an ON_SectionStyle instance
      //if (customSectionStyle)
      //{
      //  if (customSectionStyle->HatchIndex() != ON_UNSET_INT_INDEX)
      //  {
      //    c = ON_3dmObjectAttributesTypeCodes::SectionHatchIndex; // 30
      //    rc = file.WriteChar(c);
      //    if (!rc) break;
      //    rc = file.Write3dmReferencedComponentIndex(ON_ModelComponent::Type::HatchPattern, customSectionStyle->HatchIndex());
      //    if (!rc) break;
      //  }

      //  if (customSectionStyle->HatchScale() != 1.0)
      //  {
      //    c = ON_3dmObjectAttributesTypeCodes::SectionHatchScale; // 31
      //    rc = file.WriteChar(c);
      //    if (!rc) break;
      //    rc = file.WriteDouble(customSectionStyle->HatchScale());
      //    if (!rc) break;
      //  }

      //  if (customSectionStyle->HatchRotation() != 0.0)
      //  {
      //    c = ON_3dmObjectAttributesTypeCodes::SectionHatchRotation; // 32
      //    rc = file.WriteChar(c);
      //    if (!rc) break;
      //    rc = file.WriteDouble(customSectionStyle->HatchRotation());
      //    if (!rc) break;
      //  }
      //}

      if (fabs(1.0 - LinetypePatternScale()) > ON_EPSILON)
      {
        c = ON_3dmObjectAttributesTypeCodes::LinetypeScale; // 33
        rc = file.WriteChar(c);
        if (!rc) break;
        rc = file.WriteDouble(LinetypePatternScale());
        if (!rc) break;
      }

      if (HatchBackgroundFillColor() != ON_Color::UnsetColor)
      {
        c = ON_3dmObjectAttributesTypeCodes::HatchBackgroundFill; // 34
        rc = file.WriteChar(c);
        if (!rc) break;
        rc = file.WriteColor(HatchBackgroundFillColor());
        if (!rc) break;
      }

      if (HatchBoundaryVisible() != false)
      {
        c = ON_3dmObjectAttributesTypeCodes::HatchBoundaryVisible; // 35
        rc = file.WriteChar(c);
        if (!rc) break;
        rc = file.WriteBool(HatchBoundaryVisible());
        if (!rc) break;
      }
    }

    // 15 Jun 2022 S. Baer
    // Do not write items if they are their default value.
    if (m_object_frame != ON_Plane::UnsetPlane)
    {
      // 26 Jan 2022 Andy Le Bihan
      // Always write the object frame - it will always be initialized.
      c = ON_3dmObjectAttributesTypeCodes::ObjectFrame;
      rc = file.WriteChar(c);
      if (!rc) break;

      ON_Xform xform;
      xform.ChangeBasis(m_object_frame, ON_Plane::World_xy);
      rc = file.WriteXform(xform);
      if (!rc) break;
    }

    // 23 April 2023 S. Baer
    // Stop writing individual section attributes. All section attribute IO has been
    // moved to writing an ON_SectionStyle instance
    //if (customSectionStyle)
    //{
    //  if (customSectionStyle->SectionFillRule() != ON::SectionFillRule::ClosedCurves)
    //  {
    //    c = ON_3dmObjectAttributesTypeCodes::SectionFillRule; // 37
    //    rc = file.WriteChar(c);
    //    if (!rc) break;
    //    rc = file.WriteChar((unsigned char)(customSectionStyle->SectionFillRule()));
    //    if (!rc) break;
    //  }
    //}

    // 30 Nov 2022 S. Baer
    // Write custom linetype
    {
      const ON_Linetype* linetype = CustomLinetype();
      if (linetype)
      {
        c = ON_3dmObjectAttributesTypeCodes::CustomLinetype; // 38
        rc = file.WriteChar(c);
        if (!rc) break;
        rc = linetype->Write(file);
        if (!rc) break;
      }
    }

    // 18 Apr 2023 S. Baer
    // Write custom section style
    if (customSectionStyle && !customSectionStyle->SectionAttributesEqual(ON_SectionStyle::Unset))
    {
      c = ON_3dmObjectAttributesTypeCodes::CustomSectionStyle; // 39
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = customSectionStyle->Write(file);
      if (!rc) break;
    }

    if (ClippingPlaneLabelStyle() != ON::SectionLabelStyle::None)
    {
      c = ON_3dmObjectAttributesTypeCodes::ClippingPlaneLabelStyle; // 40
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteChar((unsigned char)(ClippingPlaneLabelStyle()));
      if (!rc) break;
    }

    //if (m_private && false == m_private->m_clipplane_list_is_participation)
    //{
    //  c = ON_3dmObjectAttributesTypeCodes::SelectiveClippingListType; //41
    //  rc = file.WriteChar(c);
    //  if (!rc) break;
    //  rc = file.WriteBool(m_private->m_clipplane_list_is_participation);
    //  if (!rc) break;
    //}

    // 0 indicates end of attributes - this should be the last item written
    c = 0;
    rc = file.WriteChar(c);
    break;
  }
  return rc;
}

bool ON_3dmObjectAttributes::Write( ON_BinaryArchive& file ) const
{
  if ( file.Archive3dmVersion() >= 5 )
  {
    // added at opennurbs version 200712190
    return Internal_WriteV5(file);
  }

  bool rc = file.Write3dmChunkVersion(1,8);
  // version 1.0 fields
  if (rc) rc = file.WriteUuid(m_uuid);
  if (rc) rc = file.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::Layer, m_layer_index);
  if (rc) rc = file.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::RenderMaterial, m_material_index);
  if (rc) rc = file.WriteColor(m_color);

  if (rc)
  {
    // OBSOLETE if (rc) rc = file.WriteLineStyle(m_line_style); // 23 March 2005 Dale Lear
    short s;
    s = (short)m_object_decoration;
    if (rc) rc = file.WriteShort(s);
    s = 0;
    if (rc) rc = file.WriteShort(s);
    if (rc) rc = file.WriteDouble(0.0);
    if (rc) rc = file.WriteDouble(1.0);
  }

  if (rc) rc = file.WriteInt(m_wire_density);
  if (rc) rc = file.WriteChar(m_mode);
  if (rc) rc = file.WriteChar(m_color_source);
  if (rc) rc = file.WriteChar(m_linetype_source);
  if (rc) rc = file.WriteChar(m_material_source);
  if (rc) rc = file.WriteString(m_name);
  if (rc) rc = file.WriteString(m_url);

  // version 1.1 fields
  int count = m_group.Count();
  rc = file.WriteInt(count);
  for ( int i = 0; i < count && rc; i++)
    rc = file.Write3dmReferencedComponentIndex(ON_ModelComponent::Type::Group, m_group[i]);

  // version 1.2 fields
  if (rc) rc = file.WriteBool(m_bVisible);

  // version 1.3 fields
  if (rc) rc = file.WriteArray(m_dmref);

  // version 1.4 fields - 23 March 2005 Dale Lear
  if (rc) rc = file.WriteInt(m_object_decoration);
  if (rc) rc = file.WriteChar(m_plot_color_source);
  if (rc) rc = file.WriteColor(m_plot_color);
  if (rc) rc = file.WriteChar(m_plot_weight_source);
  if (rc) rc = file.WriteDouble(m_plot_weight_mm);

  // version 1.5 fields 11 April 2005
  if (rc) rc = file.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::LinePattern, m_linetype_index );

  // version 1.6 fields 2 September 2005
  if (rc)
  {
    unsigned char uc = 0;
    switch(m_space)
    {
    case ON::no_space:    uc = 0; break;
    case ON::model_space: uc = 0; break;
    case ON::page_space:  uc = 1; break;
    case ON::uveditor_space:
    case ON::blockeditor_space:
        {
            uc = 2;
            ON_ASSERT(false);
            break;
        }
    }
    rc = file.WriteChar(uc);
  }
  if (rc)
  {
    // 22 Sep 2006 - the way ON_3dmObjectAttributes indicates
    // that an object is put on a particular page view changed
    // from being saved in the m_dmref[] list to using the
    // m_space and m_viewport_id settings.  But the file format
    // cannot change at this point.  So, the bAddPagespaceDMR
    // is here to save the page info in the old dmr format.
    int count_local = m_dmref.Count();
    if ( count_local < 0 )
      count_local = 0;
    bool bAddPagespaceDMR = ( ON::page_space == m_space && !ON_UuidIsNil(m_viewport_id) );
    rc = file.WriteInt( bAddPagespaceDMR ? (count_local+1) : count_local );
    if ( rc && bAddPagespaceDMR )
    {
      rc = file.WriteUuid(m_viewport_id);
      if (rc) rc = file.WriteUuid(ON_ObsoletePageSpaceObjectId);
    }
    int i;
    for ( i = 0; i < count_local && rc; i++ )
    {
      const ON_DisplayMaterialRef& dmr = m_dmref[i];
      rc = file.WriteUuid(dmr.m_viewport_id);
      if (rc) rc = file.WriteUuid(dmr.m_display_material_id);
    }
  }

  // version 1.7 fields 6 June 2006
  if (rc) rc = m_rendering_attributes.Write(file);

  return rc;
}


bool ON_3dmObjectAttributes::Transform( const ON_Xform& xform )
{
  // Please discuss any changes with Dale Lear.
  ON_Object::TransformUserData(xform);

  //https://mcneel.myjetbrains.com/youtrack/issue/RH-20531
  //m_object_frame.Transform(xform);

  return m_rendering_attributes.Transform(xform);
}

bool ON_3dmObjectAttributes::Transform(const ON_Geometry* pOriginalGeometry, const ON_Xform& xform)
{
  // Please discuss any changes with Dale Lear.
  ON_Object::TransformUserData(xform);

  //https://mcneel.myjetbrains.com/youtrack/issue/RH-20531

  //This assumes that the incoming geometry has already been transformed, so if this is initializing
  //the object frame, it doesn't need to be transformed.
  if (m_object_frame.IsValid())
  {
    m_object_frame.Transform(xform);
  }
  /*else if (pOriginalGeometry)
  {
    ON_Plane plane = ON_Plane::World_xy;
    plane.SetOrigin(pOriginalGeometry->BoundingBox().Center());

    m_object_frame.Transform(xform);
  }*/

  return m_rendering_attributes.Transform(xform);
}

bool ON_3dmObjectAttributes::IsValid( ON_TextLog* text_log ) const
{
  if ( ON_UuidIsNil(m_uuid) )
  {
    if ( text_log )
    {
      text_log->Print("Object id is nil - this is not valid.\n");
    }
    return false;
  }

  if ( !m_rendering_attributes.IsValid(text_log) )
  {
    if ( text_log )
    {
      text_log->Print("Object rendering attributes are not valid.\n");
    }
    return false;
  }

  return true;
}

unsigned int ON_3dmObjectAttributes::SizeOf() const
{
  unsigned int sz = sizeof(*this) - sizeof(ON_Object) 
                  + m_name.Length()*sizeof(wchar_t)
                  + m_url.Length()*sizeof(wchar_t)
                  + m_group.SizeOfArray()
                  + ON_Object::SizeOf();
  return sz;
}

// 12 Aug 2021 S. Baer
// When adding new fields written to 3dm files, always add information to this
// Dump function. Dump is used by the opennurbs file testing framework to
// perform comparisons and is useful for manual comparison in when tests fail.
void ON_3dmObjectAttributes::Dump( ON_TextLog& dump ) const
{
  const wchar_t* wsName = static_cast< const wchar_t* >(m_name);
  if ( !wsName )
    wsName = L"";
  dump.Print("object name = \"%ls\"\n",wsName);

  dump.Print("object uuid = ");
  dump.Print(m_uuid);
  dump.Print("\n");

  const char* sMode = "unknown";
  switch( Mode() )
  {
  case ON::normal_object:
    sMode = "normal";
    break;
  case ON::hidden_object:
    sMode = "hidden";
    break;
  case ON::locked_object:
    sMode = "locked";
    break;
  default:
    sMode = "unknown";
    break;
  }
  dump.Print("object mode = %s\n",sMode); // sSMode is const char*

  dump.Print("object layer index = %d\n",m_layer_index);

  const ON::object_material_source mat_source = MaterialSource();

  if (ON::object_material_source::material_from_object == mat_source || false == dump.IsTextHash())
  {
    // Depending on when a 3dm file was written, m_material_index may get set to an implicit -1 
    // during writing as part of an old attempt to reduce the size of attributes when saved in .3dm files.
    // When mat_source is not (ON::object_material_source::material_from_object. This causes the
    // 3dm content to vary in a way that content hashing must ignore. The sample file
    // C:\dev\github\mcneel\rhino\src4\opennurbs\example_files\V5\v5_teacup.3dm is an example.
    // It's old enough that it contains material index values >= 0 that are not saved
    // by SaveAs V5 writing code since circa 2010 or earlier.
    dump.Print("object material index = %d\n", m_material_index);
  }

  const char* sMaterialSource = "unknown";
  switch(MaterialSource()) {
  case ON::object_material_source::material_from_layer: sMaterialSource = "layer material"; break;
  case ON::object_material_source::material_from_object: sMaterialSource = "object material"; break;
  case ON::object_material_source::material_from_parent: sMaterialSource = "parent material"; break;
  }
  dump.Print("material source = %s\n",sMaterialSource); // sMaterialSource is const char*
  const int group_count = GroupCount();
  if ( group_count > 0 ) {
    const int* group = GroupList();
    dump.Print("groups: ");
    int i;
    for ( i = 0; i < group_count; i++ ) {
      if ( i )
        dump.Print(",%d",group[i]);
      else
        dump.Print("%d",group[i]);
    }
    dump.Print("\n");
  }

  const ON_Linetype* linetype = CustomLinetype();
  if (nullptr == linetype)
  {
    dump.Print("no custom linetype\n");
  }
  else
  {
    dump.Print("contains custom linetype\n");
  }
}

ON::object_mode ON_3dmObjectAttributes::Mode() const
{
  return ON::ObjectMode( m_mode%16 );
}

void ON_3dmObjectAttributes::SetMode( ON::object_mode m )
{
  int om = ON::ObjectMode(m);
  if ( om >= 16 || om < 0 )
    om = 0;
  m_mode = (unsigned char)om;

  // temporary
  m_bVisible = (om != ON::hidden_object);
}

bool ON_3dmObjectAttributes::IsInstanceDefinitionObject() const
{
  return (ON::idef_object == Mode());
}

bool ON_3dmObjectAttributes::IsVisible() const
{
  return m_bVisible;
}

void ON_3dmObjectAttributes::SetVisible( bool bVisible )
{
  if ( m_bVisible != (bVisible?true:false) )
  {
    m_bVisible = (bVisible?true:false);

    // temporary
    if ( Mode() != ON::idef_object )
      SetMode( m_bVisible ? ON::normal_object : ON::hidden_object );
  }
}

bool ON_3dmObjectAttributes::SetName(
  const wchar_t* candidate_name,
  bool bFixInvalidName

)
{
  ON_wString name(candidate_name);
  name.TrimLeftAndRight();
  bool rc = name.IsEmpty() || ON_ModelComponent::IsValidComponentName(name);
  if (false == rc && bFixInvalidName)
  {
    // Because ON_3dmObjectAttributes.m_name is public, it has been set to strings
    // that are not valid names. Some of these strings begin with a bracket that
    // is permitted to appear later in the name. Prepending a carrot makes the names
    // unique while not turning them into something that the Rhino or python parsers
    // key off of in some other way.
    // way to make these names
    ON_wString prefixed_name = '^';
    prefixed_name += name;
    rc = ON_ModelComponent::IsValidComponentName(prefixed_name);
    if (rc)
      name = prefixed_name;
  }
  m_name = rc ? name : ON_wString::EmptyString;
  return rc;
}

const ON_wString ON_3dmObjectAttributes::Name() const
{
  return m_name;
}


unsigned int ON_3dmObjectAttributes::ApplyParentalControl(
        const ON_3dmObjectAttributes& parents_attributes,
        const ON_Layer& parent_layer,
        unsigned int control_limits
        )
{
  unsigned int rc = ApplyParentalControl(parents_attributes, parent_layer, ON_nil_uuid, control_limits);
  return rc;
}

unsigned int ON_3dmObjectAttributes::ApplyParentalControl(
  const ON_3dmObjectAttributes& parents_attributes,
  const ON_Layer& parent_layer,
  const ON_UUID& viewport_id,
  unsigned int control_limits
)
{
  unsigned int rc = 0;

  if (0 != (0x01 & control_limits))
  {
    if (m_bVisible && !parents_attributes.m_bVisible)
    {
      rc |= 0x01;
      m_bVisible = false;
    }
  }

  if (0 != (0x02 & control_limits))
  {
    if (ON::color_from_parent == m_color_source)
    {
      rc |= 0x02;
      m_color_source = parents_attributes.m_color_source;
      m_color = parents_attributes.m_color;
      // 2010 March 10 Dale Lear
      //   Changing the layer index is wrong!
      //   Color by parent means COLOR and not LAYER
      // WRONG! // m_layer_index = parents_attributes.m_layer_index;
      if (ON::color_from_layer == m_color_source && parent_layer.Index() >= 0)
      {
        // this object will use the parent layer's color
        m_color_source = ON::color_from_object;
        m_color = parent_layer.PerViewportColor(viewport_id);
      }
    }
  }

  if (0 != (0x04 & control_limits))
  {
    if (ON::material_from_parent == m_material_source)
    {
      rc |= 0x04;
      m_material_source = parents_attributes.m_material_source;
      m_material_index = parents_attributes.m_material_index;
      // 2010 March 10 Dale Lear
      //   Changing the layer index is wrong!
      //   Material by parent means MATERIAL and not LAYER
      // WRONG! // m_layer_index = parents_attributes.m_layer_index;
      if (ON::material_from_layer == m_material_source && parent_layer.Index() >= 0)
      {
        // this object will use the parent layer's material
        m_material_source = ON::material_from_object;
        m_material_index = parent_layer.m_material_index;
      }
    }
  }

  if (0 != (0x08 & control_limits))
  {
    if (ON::plot_color_from_parent == m_plot_color_source)
    {
      rc |= 0x08;
      m_plot_color_source = parents_attributes.m_plot_color_source;
      m_plot_color = parents_attributes.m_plot_color;
      if (ON::plot_color_from_layer == m_plot_color_source && parent_layer.Index() >= 0)
      {
        // this object will use the parent layer's plot color
        m_plot_color_source = ON::plot_color_from_object;
        m_plot_color = parent_layer.PerViewportPlotColor(viewport_id);
      }
    }
  }

  if (0 != (0x10 & control_limits))
  {
    if (ON::plot_weight_from_parent == m_plot_weight_source)
    {
      rc |= 0x10;
      m_plot_weight_source = parents_attributes.m_plot_weight_source;
      m_plot_weight_mm = parents_attributes.m_plot_weight_mm;
      if (ON::plot_weight_from_layer == m_plot_weight_source && parent_layer.Index() >= 0)
      {
        // this object will use the parent layer's plot weight
        m_plot_weight_source = ON::plot_weight_from_object;
        m_plot_weight_mm = parent_layer.PerViewportPlotWeight(viewport_id);
      }
    }
  }

  if (0 != (0x20 & control_limits))
  {
    if (ON::linetype_from_parent == m_linetype_source)
    {
      rc |= 0x20;
      m_linetype_source = parents_attributes.m_linetype_source;
      m_linetype_index = parents_attributes.m_linetype_index;
      if (ON::linetype_from_layer == m_linetype_source && parent_layer.Index() >= 0)
      {
        // this object will use the parent layer's line type
        m_linetype_source = ON::linetype_from_object;
        m_linetype_index = parent_layer.m_linetype_index;
      }
    }
  }

  if (0 != (0x40 & control_limits))
  {
    rc |= 0x40;
    m_display_order = parents_attributes.m_display_order;
  }

  //if (0 != (0x80 & control_limits))
  //{
  //  if (ON::ClipParticipationSource::FromParent == ClipParticipationSource())
  //  {
  //    rc |= 0x80;
  //    SetClipParticipationSource(parents_attributes.ClipParticipationSource());
  //    if (ON::ClipParticipationSource::FromLayer == ClipParticipationSource() && parent_layer.Index() >= 0)
  //    {
  //      SetClipParticipationSource(ON::ClipParticipationSource::FromObject);
  //      bool forAll = false;
  //      bool forNone = false;
  //      ON_UuidList list;
  //      bool isParticipationList = true;
  //      parent_layer.GetClipParticipation(forAll, forNone, list, isParticipationList);
  //      if (forAll)
  //        SetClipParticipationForAll();
  //      else if (forNone)
  //        SetClipParticipationForNone();
  //      else if (list.Count() > 0)
  //        SetClipParticipationList(list.Array(), list.Count(), isParticipationList);
  //    }
  //    if (ON::ClipParticipationSource::FromObject == ClipParticipationSource())
  //    {
  //      bool forAll = false;
  //      bool forNone = false;
  //      ON_UuidList list;
  //      bool isParticipationList = true;
  //      parents_attributes.GetClipParticipation(forAll, forNone, list, isParticipationList);
  //      if (forAll)
  //        SetClipParticipationForAll();
  //      else if (forNone)
  //        SetClipParticipationForNone();
  //      else if (list.Count() > 0)
  //        SetClipParticipationList(list.Array(), list.Count(), isParticipationList);
  //    }
  //  }
  //}

  if (0 != (0x100 & control_limits))
  {
    if (ON::SectionAttributesSource::FromParent == SectionAttributesSource())
    {
      rc |= 0x100;
      SetSectionAttributesSource(parents_attributes.SectionAttributesSource());
      if (ON::SectionAttributesSource::FromLayer == SectionAttributesSource() && parent_layer.Index() >= 0)
      {
        SetSectionAttributesSource(ON::SectionAttributesSource::FromObject);
        const ON_SectionStyle* sectionStyle = parent_layer.CustomSectionStyle();
        if (sectionStyle)
          SetCustomSectionStyle(*sectionStyle);
        else
          RemoveCustomSectionStyle();
      }
      else
      {
        ON_SectionStyle sectionStyle;
        parents_attributes.CustomSectionStyle(&sectionStyle);
        SetCustomSectionStyle(sectionStyle);
      }
    }
  }

  return rc;
}


ON::object_color_source ON_3dmObjectAttributes::ColorSource() const
{
  return ON::ObjectColorSource(m_color_source);
}

void ON_3dmObjectAttributes::SetColorSource( ON::object_color_source c )
{
  m_color_source = (unsigned char)ON::ObjectColorSource(c);
}

ON::object_linetype_source ON_3dmObjectAttributes::LinetypeSource() const
{
  return ON::ObjectLinetypeSource(m_linetype_source);
}

void ON_3dmObjectAttributes::SetLinetypeSource( ON::object_linetype_source c )
{
  m_linetype_source = (unsigned char)ON::ObjectLinetypeSource(c);
}

ON::object_material_source ON_3dmObjectAttributes::MaterialSource() const
{
  return ON::ObjectMaterialSource(m_material_source);
}

void ON_3dmObjectAttributes::SetMaterialSource( ON::object_material_source c )
{
  m_material_source = (unsigned char)ON::ObjectMaterialSource(c);
}


ON::plot_color_source ON_3dmObjectAttributes::PlotColorSource() const
{
  return ON::PlotColorSource(m_plot_color_source);
}

void ON_3dmObjectAttributes::SetPlotColorSource( ON::plot_color_source pcs )
{
  m_plot_color_source = (unsigned char)ON::PlotColorSource(pcs);
}

ON::plot_weight_source ON_3dmObjectAttributes::PlotWeightSource() const
{
  return ON::PlotWeightSource(m_plot_weight_source);
}

void ON_3dmObjectAttributes::SetPlotWeightSource( ON::plot_weight_source pws )
{
  m_plot_weight_source = (unsigned char)ON::PlotColorSource(pws);
}


int ON_3dmObjectAttributes::GroupCount() const
{
  return m_group.Count();
}

//////////
// returns an int array of GroupCount() zero based group indices
const int* ON_3dmObjectAttributes::GroupList() const
{
  return (m_group.Count()>0) ? m_group.Array() : 0;
}

int ON_3dmObjectAttributes::GetGroupList(ON_SimpleArray<int>& group_list) const
{
  group_list = m_group;
  return group_list.Count();
}

//////////
// returns true if object is in group with specified index
bool ON_3dmObjectAttributes::IsInGroup(
  int group_index // zero based group index
  ) const
{
  bool rc = false;
  const int count = m_group.Count();
  int i;
  for ( i = 0; i < count; i++ ) {
    if (m_group[i] == group_index) {
      rc = true;
      break;
    }
  }
  return rc;
}

bool ON_3dmObjectAttributes::IsInGroups( int group_count, const int* group_list ) const
{
  // returns true if object is in any of the groups in the list
  bool rc = false;
  if ( group_count > 0 && group_list ) {
    const int obj_group_count  = GroupCount();
    const int* obj_group_list = GroupList();
    // in practice these arrays will be very short and this search will be fast
    int i, j;
    for ( i = 0; i < obj_group_count; i++ ) for ( j = 0; j < group_count; j++ ) {
      if ( obj_group_list[i] == group_list[j] )
        return true;
    }
  }
  return rc;
}

bool ON_3dmObjectAttributes::IsInGroups( const ON_SimpleArray<int>& group_list ) const
{
  return IsInGroups( group_list.Count(), group_list.Array() );
}


//////////
// Adds object to group with specified index (If object is already in
// group, nothing is changed.)
void ON_3dmObjectAttributes::AddToGroup(
  int group_index // zero based group index
  )
{
  if ( group_index >= 0 ) {
    if ( !IsInGroup(group_index) )
      m_group.Append(group_index);
  }
}

//////////
// returns the index of the last group in the group list
// or -1 if the object is not in any groups
int ON_3dmObjectAttributes::TopGroup() const
{
  const int* top_group = m_group.Last();
  return top_group ? *top_group : -1;
}

//////////
// removes the object from the last group in the group list
void ON_3dmObjectAttributes::RemoveFromTopGroup()
{
  int c = m_group.Count();
  if ( c > 0 ) {
    c--;
    m_group.SetCount(c);
  }
}

//////////
// Removes object from group with specified index.  If object is not
// in the group, nothing is changed.
void ON_3dmObjectAttributes::RemoveFromGroup(
  int group_index // zero based group index
  )
{
  int i;
  const int count = m_group.Count();
  for ( i = 0; i < count; i++ ) {
    if (m_group[i] == group_index) {
      m_group.Remove(i);
      break;
    }
  }
}

//////////
// Removes object from all groups.
void ON_3dmObjectAttributes::RemoveFromAllGroups()
{
  m_group.Destroy();
}


bool ON_3dmObjectAttributes::FindDisplayMaterialId( 
      const ON_UUID& viewport_id, 
      ON_UUID* display_material_id
      ) const
{
  bool rc = false;
  if ( m_dmref.Count() > 0 )
  {
    ON_DisplayMaterialRef search_material, found_material;
    search_material.m_viewport_id = viewport_id;
    if ( 0 != (rc = FindDisplayMaterialRef(search_material,&found_material)) )
    {
      if ( display_material_id )
        *display_material_id = found_material.m_display_material_id;
    }
  }
  return rc;
}


bool ON_3dmObjectAttributes::FindDisplayMaterialRef(
  const ON_DisplayMaterialRef& search_material,
  ON_DisplayMaterialRef* found_material
  ) const
{
  int i = m_dmref.Count();
  if ( i > 0 )
  {
    int j = -1;
    if ( search_material.m_viewport_id != ON_nil_uuid )
    {
      if ( search_material.m_display_material_id != ON_nil_uuid )
      {
        while(i--)
        {
          if ( (m_dmref[i].m_display_material_id == search_material.m_display_material_id) &&
               (m_dmref[i].m_viewport_id == search_material.m_viewport_id) )
          {
            if(found_material)
              *found_material = m_dmref[i];
            return true;
          }
        }
      }
      else
      {
        while(i--)
        {
          const ON_UUID& vid = m_dmref[i].m_viewport_id;
          if ( vid == search_material.m_viewport_id )
          {
            if(found_material)
              *found_material = m_dmref[i];
            return true;
          }
          if ( vid == ON_nil_uuid )
          {
            j = i;
          }
        }
        if ( j >= 0 )
        {
          if(found_material)
            *found_material = m_dmref[j];
          return true;
        }
      }
    }
    else
    {
      if ( search_material.m_display_material_id != ON_nil_uuid )
      {
        while(i--)
        {
          if ( m_dmref[i].m_display_material_id == search_material.m_display_material_id )
          {
            if ( m_dmref[i].m_viewport_id == ON_nil_uuid )
            {
              if(found_material)
                *found_material = m_dmref[i];
              return true;
            }
            if ( j < 0 )
              j = i;
          }
        }
        if ( j >= 0 )
        {
          if(found_material)
            *found_material = m_dmref[j];
          return true;
        }
      }
      else
      {
        while(i--)
        {
          if ( m_dmref[i].m_viewport_id == ON_nil_uuid )
          {
            if(found_material)
              *found_material = m_dmref[i];
            return true;
          }
        }
      }
    }
  }
  return false;
}


bool ON_3dmObjectAttributes::AddDisplayMaterialRef(
  ON_DisplayMaterialRef display_material
  )
{
  bool rc = false;
  if ( !(display_material.m_display_material_id == ON_nil_uuid) )
  {
    int i = m_dmref.Count();
    while(i--)
    {
      if ( m_dmref[i].m_viewport_id == display_material.m_viewport_id )
      {
         m_dmref[i] = display_material;
         return true;
      }
    }
    m_dmref.Append(display_material);
  }
  return rc;
}

void ON_3dmObjectAttributes::RemoveAllDisplayMaterialRefs()
{
  m_dmref.Destroy();
}

bool ON_3dmObjectAttributes::RemoveDisplayMaterialRef(
  ON_UUID viewport_id,
  ON_UUID display_material_id
  )
{
  bool rc = false;
  int i = m_dmref.Count();
  if ( i > 0 )
  {
    const bool bCheckViewportId = !ON_UuidIsNil(viewport_id);
    const bool bCheckMaterialId = !ON_UuidIsNil(display_material_id);
    if ( bCheckViewportId || bCheckMaterialId )
    {
      while(i--)
      {
        if ( bCheckViewportId && m_dmref[i].m_viewport_id != viewport_id )
          continue;
        if ( bCheckMaterialId && m_dmref[i].m_display_material_id != display_material_id )
          continue;

        // remove this item
        rc = true;
        m_dmref.Remove(i);
      }
    }
    else
    {
      // 20 Sep 2006 Dale Lear - this was added so we can
      // remove all entries with non-nil viewport and nil
      // uuid.
      while(i--)
      {
        if (   !ON_UuidIsNil(m_dmref[i].m_viewport_id)
             && ON_UuidIsNil(m_dmref[i].m_display_material_id)
           )
        {
          // remove this item
          rc = true;
          m_dmref.Remove(i);
        }
      }
    }
  }
  return rc;
}

int ON_3dmObjectAttributes::DisplayMaterialRefCount() const
{
  return m_dmref.Count();
}



ON::SectionAttributesSource ON_3dmObjectAttributes::SectionAttributesSource() const
{
  return m_private ? m_private->m_section_attributes_source : DefaultAttributesPrivate.m_section_attributes_source;
}
void ON_3dmObjectAttributes::SetSectionAttributesSource(ON::SectionAttributesSource source)
{
  if (SectionAttributesSource() == source)
    return;

  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);
  m_private->m_section_attributes_source = source;
}

void ON_3dmObjectAttributes::SetCustomSectionStyle(const ON_SectionStyle& sectionStyle)
{
  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);

  m_private->m_custom_section_style.reset(new ON_SectionStyle(sectionStyle));
}
const ON_SectionStyle* ON_3dmObjectAttributes::CustomSectionStyle(ON_SectionStyle* sectionStyle) const
{
  const ON_SectionStyle* rc = nullptr;
  if (m_private)
    rc = m_private->m_custom_section_style.get();

  if (sectionStyle && rc)
  {
    *sectionStyle = *rc;
  }

  return rc;
}
void ON_3dmObjectAttributes::RemoveCustomSectionStyle()
{
  if (m_private)
    m_private->m_custom_section_style.reset();
}


double ON_3dmObjectAttributes::LinetypePatternScale() const
{
  return m_private ? m_private->m_linetype_scale : 1.0;
}
void ON_3dmObjectAttributes::SetLinetypePatternScale(double scale)
{
  if (scale < ON_EPSILON)
    return;

  if (fabs(LinetypePatternScale() - scale) < ON_EPSILON)
    return;

  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);
  m_private->m_linetype_scale = scale;
}

void ON_3dmObjectAttributes::SetCustomLinetype(const ON_Linetype& linetype)
{
  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);

  m_private->m_custom_linetype.reset(new ON_Linetype(linetype));
}
const ON_Linetype* ON_3dmObjectAttributes::CustomLinetype() const
{
  const ON_Linetype* rc = nullptr;
  if (m_private)
    rc = m_private->m_custom_linetype.get();
  return rc;
}
void ON_3dmObjectAttributes::RemoveCustomLinetype()
{
  if (m_private)
    m_private->m_custom_linetype.reset();
}


ON_Color ON_3dmObjectAttributes::HatchBackgroundFillColor() const
{
  return m_private ? m_private->m_hatch_background_fill : ON_Color::UnsetColor;
}
void ON_3dmObjectAttributes::SetHatchBackgroundFillColor(const ON_Color& color)
{
  ON_Color c = color;
  if (c.Alpha() == 255)
    c = ON_Color::UnsetColor;
  if (HatchBackgroundFillColor() == c)
    return;

  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);
  m_private->m_hatch_background_fill = c;
}
bool ON_3dmObjectAttributes::HatchBoundaryVisible() const
{
  return m_private ? m_private->m_hatch_boundary_visible : DefaultAttributesPrivate.m_hatch_boundary_visible;
}
void ON_3dmObjectAttributes::SetHatchBoundaryVisible(bool on)
{
  if (HatchBoundaryVisible() == on)
    return;

  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);
  m_private->m_hatch_boundary_visible = on;
}

ON::SectionLabelStyle ON_3dmObjectAttributes::ClippingPlaneLabelStyle() const
{
  return m_private ? m_private->m_section_label_style : DefaultAttributesPrivate.m_section_label_style;
}
void ON_3dmObjectAttributes::SetClippingPlaneLabelStyle(ON::SectionLabelStyle style)
{
  if (ClippingPlaneLabelStyle() == style)
    return;

  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);
  m_private->m_section_label_style = style;
}


//https://mcneel.myjetbrains.com/youtrack/issue/RH-20531
ON_Plane ON_3dmObjectAttributes::ObjectFrame(const ON_COMPONENT_INDEX& ci) const
{
  return m_object_frame;
}

//https://mcneel.myjetbrains.com/youtrack/issue/RH-20531
void ON_3dmObjectAttributes::SetObjectFrame(const ON_COMPONENT_INDEX&, const ON_Xform& wcs_to_ocs)
{
  m_object_frame = ON_Plane::World_xy;
  m_object_frame.Transform(wcs_to_ocs);
}

void ON_3dmObjectAttributes::SetObjectFrame(const ON_COMPONENT_INDEX& ci, const ON_Plane& plane)
{
  m_object_frame = plane;
}

ON_MeshModifiers& ON_3dmObjectAttributes::MeshModifiers(void) const
{
  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);

  return m_private->m_mesh_modifiers;
}

const ON_SimpleArray<ON_Decal*>& ON_3dmObjectAttributes::GetDecalArray(void) const
{
  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);

  return m_private->m_decals.GetDecalArray();
}

ON_Decal* ON_3dmObjectAttributes::AddDecal(void)
{
  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);

  return m_private->m_decals.AddDecal();
}

bool ON_3dmObjectAttributes::RemoveDecal(ON_Decal& decal)
{
  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);

  return m_private->m_decals.RemoveDecal(decal);
}

void ON_3dmObjectAttributes::RemoveAllDecals(void)
{
  if (nullptr == m_private)
    m_private = new ON_3dmObjectAttributesPrivate(this);

  return m_private->m_decals.RemoveAllDecals();
}

// {1403A7E4-E7AD-4a01-A2AA-41DAE6BE7ECB}
const ON_UUID ON_DisplayMaterialRef::m_invisible_in_detail_id = 
{ 0x1403a7e4, 0xe7ad, 0x4a01, { 0xa2, 0xaa, 0x41, 0xda, 0xe6, 0xbe, 0x7e, 0xcb } };

ON_DisplayMaterialRef::ON_DisplayMaterialRef()
{
  m_viewport_id = ON_nil_uuid;
  m_display_material_id = ON_nil_uuid;
}

bool ON_DisplayMaterialRef::operator==(const ON_DisplayMaterialRef& other) const
{
  return (Compare(other)==0); 
}

bool ON_DisplayMaterialRef::operator!=(const ON_DisplayMaterialRef& other) const
{
  return (Compare(other)!=0); 
}

int ON_DisplayMaterialRef::Compare(const ON_DisplayMaterialRef& other) const
{
  int i = ON_UuidCompare(m_viewport_id,other.m_viewport_id);
  if (0==i)
    i = ON_UuidCompare(m_display_material_id,other.m_display_material_id);
  return i;
}

bool ON_DisplayMaterialRef::operator<(const ON_DisplayMaterialRef& other) const
{
  return (Compare(other)<0); 
}

bool ON_DisplayMaterialRef::operator<=(const ON_DisplayMaterialRef& other) const
{
  return (Compare(other)<=0); 
}

bool ON_DisplayMaterialRef::operator>(const ON_DisplayMaterialRef& other) const
{
  return (Compare(other)>0); 
}

bool ON_DisplayMaterialRef::operator>=(const ON_DisplayMaterialRef& other) const
{
  return (Compare(other)>=0); 
}
