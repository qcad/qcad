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

class ON_LayerPrivate
{
public:
  ON_LayerPrivate() = default;
  ~ON_LayerPrivate() = default;

  bool operator==(const ON_LayerPrivate&) const;
  bool operator!=(const ON_LayerPrivate&) const;

  std::shared_ptr<ON_SectionStyle> m_custom_section_style;

  bool m_visible_in_new_details = true;
};

static const ON_LayerPrivate DefaultLayerPrivate;


bool ON_LayerPrivate::operator==(const ON_LayerPrivate& other) const
{
  if (this == &other)
    return true;

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

  if (m_visible_in_new_details != other.m_visible_in_new_details)
    return false;

  return true;
}

bool ON_LayerPrivate::operator!=(const ON_LayerPrivate& other) const
{
  return !ON_LayerPrivate::operator==(other);
}


ON_OBJECT_IMPLEMENT(ON_Layer,ON_ModelComponent,"95809813-E985-11d3-BFE5-0010830122F0");

const ON_Layer* ON_Layer::FromModelComponentRef(
  const class ON_ModelComponentReference& model_component_reference,
  const ON_Layer* none_return_value
  )
{
  const ON_Layer* p = ON_Layer::Cast(model_component_reference.ModelComponent());
  return (nullptr != p) ? p : none_return_value;
}

bool ON_Layer::UpdateReferencedComponents(
  const class ON_ComponentManifest& source_manifest,
  const class ON_ComponentManifest& destination_manifest,
  const class ON_ManifestMap& manifest_map
  )
{
  bool rc = true;

  // Update render material reference
  int material_index = RenderMaterialIndex();
  if (material_index >= 0)
  {
    int destination_material_index = ON_UNSET_INT_INDEX;
    if (manifest_map.GetAndValidateDestinationIndex(
      ON_ModelComponent::Type::RenderMaterial,
      material_index,
      destination_manifest,
      &destination_material_index))
    {
      material_index = destination_material_index;
    }
    else
    {
      ON_ERROR("Unable to update render material reference.");
      rc = false;
      material_index = ON_Layer::Default.RenderMaterialIndex();
    }
    SetRenderMaterialIndex(material_index);
  }

  // Update line pattern reference
  int line_pattern_index = LinetypeIndex();
  if (line_pattern_index >= 0)
  {
    int destination_line_pattern_index = ON_UNSET_INT_INDEX;
    if (manifest_map.GetAndValidateDestinationIndex(
      ON_ModelComponent::Type::LinePattern,
      line_pattern_index,
      destination_manifest,
      &destination_line_pattern_index))
    {
      line_pattern_index = destination_line_pattern_index;
    }
    else
    {
      ON_ERROR("Unable to update line pattern reference.");
      rc = false;
      line_pattern_index = ON_Layer::Default.LinetypeIndex();
    }
    SetLinetypeIndex(line_pattern_index);
  }

  // Update parent layer reference
  ON_UUID parent_layer_id = ParentLayerId();
  if (ON_nil_uuid != parent_layer_id)
  {
    const ON_UUID manifest_item_id = destination_manifest.ItemFromId(
      ON_ModelComponent::Type::Layer,
      parent_layer_id
      ).Id();
    if ( ON_nil_uuid == manifest_item_id )
    {
      ON_ERROR("Unable to update parent layer id reference.");
      rc = false;
      parent_layer_id = ON_Layer::Default.ParentLayerId();
    }
    else
    {
      parent_layer_id = manifest_item_id;
    }
    SetParentLayerId(parent_layer_id);
  }

  return rc;
}

#define ON_BOZO_VACCINE_3E4904E6E9304fbcAA42EBD407AEFE3B
#define ON_BOZO_VACCINE_BFB63C094BC7472789BB7CC754118200

ON_Layer::ON_Layer() ON_NOEXCEPT
  : ON_ModelComponent(ON_ModelComponent::Type::Layer)
{}

ON_Layer::~ON_Layer()
{
  if (m_private)
    delete m_private;
}

ON_Layer::ON_Layer( const ON_Layer& src)
  : ON_ModelComponent(ON_ModelComponent::Type::Layer,src)
  , m_iges_level(src.m_iges_level)
  , m_material_index(src.m_material_index)
  , m_rendering_attributes(src.m_rendering_attributes)
  , m_linetype_index(src.m_linetype_index)
  , m_color(src.m_color)
  , m_display_material_id(src.m_display_material_id)
  , m_plot_color(src.m_plot_color)
  , m_plot_weight_mm(src.m_plot_weight_mm)
  , m_bExpanded(src.m_bExpanded)
  , m_extension_bits(src.m_extension_bits)
{
  if (src.m_private)
  {
    m_private = new ON_LayerPrivate();
    *m_private = *src.m_private;
  }
}

ON_Layer& ON_Layer::operator=(const ON_Layer& src)
{
  if (this != &src)
  {
    ON_ModelComponent::operator=(src);
    m_iges_level = src.m_iges_level;
    m_material_index = src.m_material_index;
    m_rendering_attributes = src.m_rendering_attributes;
    m_linetype_index = src.m_linetype_index;
    m_color = src.m_color;
    m_display_material_id = src.m_display_material_id;
    m_plot_color = src.m_plot_color;
    m_plot_weight_mm = src.m_plot_weight_mm;
    m_bExpanded = src.m_bExpanded;
    m_extension_bits = src.m_extension_bits;

    if (m_private)
      delete m_private;
    m_private = nullptr;
    if (src.m_private)
    {
      m_private = new ON_LayerPrivate();
      *m_private = *src.m_private;
    }
  }
  return *this;
}


static void SetExtensionBit( unsigned char* layer_m_extension_bits, unsigned char mask )
{
  *layer_m_extension_bits |= mask;
}

static void ClearExtensionBit(  unsigned char* layer_m_extension_bits, unsigned char mask )
{
  unsigned char notmask = ~mask;
  *layer_m_extension_bits &= notmask;
}

static bool ExtensionBit( unsigned char layer_m_extension_bits, unsigned char mask )
{
  return (0 != (layer_m_extension_bits & mask));
}

bool ON_Layer::IsValid( ON_TextLog* text_log ) const
{
  if ( NameIsEmpty() )
  {
    if ( text_log )
    {
      text_log->Print("Layer name is empty.\n");
    }
    return false;
  }
  return true;
}

// 12 Aug 2021 S. Baer
// When adding new fields written to 3dm files, always add information to this
// Dump function. Dump is used by the opennurbs file testing framework to
// perform comparisons and is useful for manual comparison in when tests fail.
void ON_Layer::Dump( ON_TextLog& dump ) const
{
  ON_ModelComponent::Dump(dump);
  dump.Print("display = %s\n",IsVisible()?"visible":"hidden");
  dump.Print("picking = %s\n",IsLocked()?"locked":"unlocked");
  dump.Print("display color rgb = "); dump.PrintRGB(m_color); dump.Print("\n");
  dump.Print("plot color rgb = "); dump.PrintRGB(m_plot_color); dump.Print("\n");
  dump.Print("default material index = %d\n",m_material_index);

  //{
  //  bool clipAll = true;
  //  bool clipNone = false;
  //  ON_UuidList cliplist;
  //  bool isSelectiveList = true;
  //  GetClipParticipation(clipAll, clipNone, cliplist, isSelectiveList);
  //  if (clipAll)
  //  {
  //    dump.Print("participates with all clipping planes\n");
  //  }
  //  else if (clipNone)
  //  {
  //    dump.Print("participates with no clipping planes\n");
  //  }
  //  else
  //  {
  //    dump.Print("participates with specific clipping planes\n");
  //  }
  //}

  const ON_SectionStyle* section_style = CustomSectionStyle();
  if (nullptr == section_style)
  {
    dump.Print("No custom section style\n");
  }
  else
  {
    dump.Print("Has custom section style\n");
  }
}

// 28 Sept. 2021
// This enum is patterned off of ON_3dmObjectAttributeTypeCode
// Layers will grow with properties at the same rate as ON_3dmObjectAttributes
// Attribute I/O changed years ago to only write non-default values into
// 3dm files so we don't end up stuffing repeated data into a 3dm that can be
// inferred when the data matches default values.
enum ON_LayerTypeCodes : unsigned char
{
  ObsoleteSelectiveClippingData = 28,
  // 18 Oct 2021 S. Baer
  // chunk version 1.11: add section hatch attributes
  SectionHatchIndex = 29,
  SectionHatchScale = 30,
  SectionHatchRotation = 31,
  // 14 June 2022 S. Baer
  // chunk version 1.12: add section fill rule
  SectionFillRule = 32,
  // 30 Nov 2022 S. Baer
  // chunk version 1.13: add custom linetype
  CustomLinetype = 33,
  // 4 Apr 2023 D. Fugier
  // chunk version 1.14: add visible in new detail
  PerViewportIsVisibleInNewDetails = 34,
  // 22 Apr 2023 S. Baer
  // chunk version 1.15: custom section style
  CustomSectionStyle = 35,
  // 11 May 2023 S. Baer
  // New selective clipping data with bool for list type
  ObsoleteSelectiveClippingListType = 36,

  LastLayerTypeCode = 36
};

bool ON_Layer::Write(
       ON_BinaryArchive& file // serialize definition to binary archive
     ) const
{
  int i;

  // 11 May 2023 S. Baer
  // Do not write a minor chunk version greater than 15. Chunk versions are actually
  // two values packed into a single unsigned char. The use of type codes for I/O
  // with layers makes it so the minor version isn't really necessary. Just stop at
  // a minor version of 15
  bool rc = file.Write3dmChunkVersion(1,15);
  while(rc)
  {
    // Save the visibility state this layer has when its parent
    // is visible ignoring current parent visibility value.
    bool bVisible = PersistentVisibility();

    // Save the locked state this layer has when its parent
    // is unlocked ignoring current parenting locked setting.
    const bool bLocked = PersistentLocking();

    // Save OBSOLETE mode value so we don't break file format
    if ( bVisible )
      i = 0; // "normal" layer mode
    else if ( bLocked )
      i = 2; // "locked" layer mode
    else
      i = 1; // "hidden" layer mode

    rc = file.WriteInt( i );
    if (!rc) break;

    rc = file.Write3dmReferencedComponentIndex( *this );
    if (!rc) break;

    rc = file.WriteInt( m_iges_level );
    if (!rc) break;

    rc = file.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::RenderMaterial, m_material_index );
    if (!rc) break;

    // Starting with version 200312110, this value is zero.  For files written
    // with earlier versions, the number was a "model index" value that was
    // set to something >= 1, but never used.  We have to continue to 
    // read/write an integer here so that old/new versions of opennurbs can
    // read files written by new/old versions.
    i = 0;
    rc = file.WriteInt( i );
    if (!rc) break;

    rc = file.WriteColor( m_color );
    if (!rc) break;
    
    {
      // OBSOLETE LINE STYLE if ( rc ) rc = file.WriteLineStyle( LineStyle() );
      // Starting with version 200503170, this section is "officially" not used.
      // Prior to that, it was old ON_LineStyle information that has
      // never been used.
      short s = 0;
      if (rc) rc = file.WriteShort(s);    // default pattern
      if (rc) rc = file.WriteShort(s);    // default pattern index
      if (rc) rc = file.WriteDouble(0.0); // default thickness
      if (rc) rc = file.WriteDouble(1.0); // default scale
    }
    if (!rc) break;

    if (
      file.Active3dmTable() == ON_3dmArchiveTableType::layer_table
      && file.Archive3dmVersion() <= 4
      && NameIsNotEmpty()
      && ParentIdIsNotNil()
      )
    {
      ON_wString name = Name();
      // In V4 there are no parent layers and all V4 layer names must be unique.
      // Since layers can be written in any order, we cannot know if there will
      // eventually be a parent layer using the same name as this child layer.
      // So, child layer names get a hash appended to insure they are unique.
      ON_UUID parent_layer_id = ParentId();
      ON__UINT16 hash = ON_CRC16(0, sizeof(parent_layer_id), &parent_layer_id);
      ON_RandomNumberGenerator rng;
      rng.Seed(hash);
      for (int attempt_count = 0; attempt_count < 100; attempt_count++)
      {
        while ( 0 == hash )
          hash = (ON__UINT16)(rng.RandomNumber() % 0xFFFFU);
        ON_wString sublayer_name;
        sublayer_name.Format(L"%ls (%04x)", static_cast<const wchar_t*>(name),hash);
        
        // Use ON_nil_uuid ast the parent id because we need a name that is uniques
        // as a "top level" layer name for V4 files.
        const ON_NameHash sublayer_name_hash = ON_NameHash::Create(ON_nil_uuid,sublayer_name);

        if ( file.Manifest().ItemFromNameHash(ComponentType(), sublayer_name_hash).IsUnset() )
        {
          // have a unique name
          name = sublayer_name;
          const_cast< ON_ComponentManifest& >(file.Manifest()).ChangeComponentNameHash(Id(), sublayer_name_hash);
          break;
        }
        hash = (ON__UINT16)(rng.RandomNumber() % 0xFFFFU);
      }
      rc = file.WriteString( name );
    }
    else
    {
      rc = file.WriteModelComponentName(*this);
    }

    if (!rc) break;

    // 1.1 fields
    rc = file.WriteBool(bVisible);
    if (!rc) break;

    // 1.2 field
    rc = file.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::LinePattern, m_linetype_index );
    if (!rc) break;

    // 1.3 field - 23 March 2005 Dale Lear
    rc = file.WriteColor( m_plot_color);
    if (!rc) break;
    rc = file.WriteDouble( m_plot_weight_mm);
    if (!rc) break;

    // 1.4 field - 3 May 2005 Dale Lear 
    //           - locked and visible are independent settings
    rc = file.WriteBool( bLocked );
    if (!rc) break;

    // 1.5 field
    rc = file.WriteUuid( Id() );
    if (!rc) break;

    // 1.6 field
    ON_UUID parent_layer_id = ParentLayerId();
    rc = file.WriteUuid( parent_layer_id );
    if (!rc) break;

    // 1.6 field
    rc = file.WriteBool( m_bExpanded );
    if (!rc) break;

    // 1.7 field - added 6 June 2006
    rc = m_rendering_attributes.Write(file);
    if (!rc) break;

    // 1.8 field - added 19 Sep 2006
    rc = file.WriteUuid(m_display_material_id);
    if (!rc) break;

    // 1.10 field - added 29 Sep 2021
    // using ON_3dmObjectAttributes inspired technique for writing only
    // non-default values to 3dm files
    unsigned char c = 0;

    // selective clipping (1.10)
    //{
    //  bool forAllClippingPlanes = true;
    //  bool forNoClippingPlanes = false;
    //  ON_UuidList selectiveList;
    //  bool isParticipationList = true;
    //  GetClipParticipation(forAllClippingPlanes, forNoClippingPlanes, selectiveList, isParticipationList);
    //  // only write selective clipping data if it is not default
    //  if (false == forAllClippingPlanes || true == forNoClippingPlanes || selectiveList.Count() > 0)
    //  {
    //    c = ON_LayerTypeCodes::SelectiveClippingData;
    //    rc = file.WriteChar(c);
    //    if (!rc) break;
    //    rc = file.WriteBool(forNoClippingPlanes);
    //    if (!rc) break;
    //    rc = selectiveList.Write(file);
    //    if (!rc) break;
    //  }
    //}

    // 23 April 2023 S. Baer
    // Stop writing individual section attributes. All section attribute IO has been
    // moved to writing an ON_SectionStyle instance
    // section hatch (1.11)
    const ON_SectionStyle* section_style = CustomSectionStyle();
    //if (section_style)
    //{
    //  if (section_style->HatchIndex() != ON_UNSET_INT_INDEX)
    //  {
    //    c = ON_LayerTypeCodes::SectionHatchIndex;
    //    rc = file.WriteChar(c);
    //    if (!rc) break;
    //    rc = file.Write3dmReferencedComponentIndex(ON_ModelComponent::Type::HatchPattern, section_style->HatchIndex());
    //    if (!rc) break;
    //  }
    //  if (section_style->HatchScale() != 1.0)
    //  {
    //    c = ON_LayerTypeCodes::SectionHatchScale;
    //    rc = file.WriteChar(c);
    //    if (!rc) break;
    //    rc = file.WriteDouble(section_style->HatchScale());
    //    if (!rc) break;
    //  }
    //  if (section_style->HatchRotation() != 0.0)
    //  {
    //    c = ON_LayerTypeCodes::SectionHatchRotation;
    //    rc = file.WriteChar(c);
    //    if (!rc) break;
    //    rc = file.WriteDouble(section_style->HatchRotation());
    //    if (!rc) break;
    //  }

    //  // section fill (1.12)
    //  if (section_style->SectionFillRule() != ON::SectionFillRule::ClosedCurves)
    //  {
    //    c = ON_LayerTypeCodes::SectionFillRule; //32
    //    rc = file.WriteChar(c);
    //    if (!rc) break;
    //    rc = file.WriteChar((unsigned char)section_style->SectionFillRule());
    //    if (!rc) break;
    //  }
    //}

    // custom linetype (1.13)
    // 17 Feb 2023 S. Baer
    // Custom linetypes were an experiment that ended up making the UI more complicated
    // than necessary. Do not write any custom linetype data into the 3dm file.
    //{
    //  const ON_Linetype* linetype = CustomLinetype();
    //  if (linetype)
    //  {
    //    c = ON_LayerTypeCodes::CustomLinetype; // 33
    //    rc = file.WriteChar(c);
    //    if (!rc) break;
    //    rc = linetype->Write(file);
    //    if (!rc) break;
    //  }
    //}

    // visible in new detail (1.14)
    if (PerViewportIsVisibleInNewDetails() != DefaultLayerPrivate.m_visible_in_new_details)
    {
      c = ON_LayerTypeCodes::PerViewportIsVisibleInNewDetails; //34
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = file.WriteBool(PerViewportIsVisibleInNewDetails());
      if (!rc) break;
    }

    if (section_style)
    {
      c = ON_LayerTypeCodes::CustomSectionStyle; //35
      rc = file.WriteChar(c);
      if (!rc) break;
      rc = section_style->Write(file);
      if (!rc) break;
    }

    //if (m_private && false == m_private->m_clipplane_list_is_participation)
    //{
    //  c = ON_LayerTypeCodes::SelectiveClippingListType; //36
    //  rc = file.WriteChar(c);
    //  if (!rc) break;
    //  rc = file.WriteBool(m_private->m_clipplane_list_is_participation);
    //  if (!rc) break;
    //}

    // 0 indicates end of new non-default attributes
    c = 0;
    rc = file.WriteChar(c);

    break;
  }

  return rc;
}

bool ON_Layer::Read(
       ON_BinaryArchive& file // restore definition from binary archive
     )
{
  int obsolete_value1 = 0; // see ON_Layer::Write
  int major_version=0;
  int minor_version=0;
  int mode = ON::normal_layer;
  *this = ON_Layer::Unset;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if ( rc && major_version == 1 )
  {
    // common to all 1.x formats
    if ( rc ) rc = file.ReadInt( &mode );
    if ( rc ) 
    {
      switch(mode)
      {
      case 0: // OBSOLETE ON::normal_layer
        break;
      case 1: // OBSOLETE ON::hidden_layer
        SetHiddenModelComponentState(true);
        break;
      case 2: // OBSOLETE ON::locked_layer
        SetLockedModelComponentState( true );
        break;
      default:
        break;
      }
    }
    int layer_index = Index();
    if (rc)
    {
      // this is the archive layer index - it will probably change when the
      // layer is added to the model. Since the layer has not been added to
      // the model, there is not way to automatically update it at this time.
      rc = file.ReadInt(&layer_index);
    }
    if (rc)
      SetIndex(layer_index);

    if ( rc ) rc = file.ReadInt( &m_iges_level );

    // render material index
    int render_material_index = ON_UNSET_INT_INDEX;
    if (rc) 
      rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::RenderMaterial,&render_material_index);
    if (rc && ON_UNSET_INT_INDEX != render_material_index )
      SetRenderMaterialIndex(render_material_index);

    if ( rc ) rc = file.ReadInt( &obsolete_value1 );
    if ( rc ) rc = file.ReadColor( m_color );

    // 25 Aug 2021 S. Baer (RH-65410)
    // Pre-V7 files ignored alpha on layer colors and in some cases
    // alpha was being set to completely transparent. In this case,
    // make the color opaque. Even V7 files with completely transparent
    // color is strange, but it can be intentionally set for some reason
    if (rc && m_color.Alpha() == 255 && m_color != ON_Color::UnsetColor && file.Archive3dmVersion() < 70)
    {
      m_color.SetAlpha(0);
    }

    {
      // OBSOLETE line style was never used - read and discard the next 20 bytes
      short s;
      double x;
      if (rc) file.ReadShort(&s);
      if (rc) file.ReadShort(&s);
      if (rc) file.ReadDouble(&x);
      if (rc) file.ReadDouble(&x);
    }

    ON_wString layer_name;
    if ( rc ) rc = file.ReadString( layer_name );
    if (rc)
      SetName(layer_name);

    if ( rc && minor_version >= 1 )
    {
      bool bVisible = true;
      rc = file.ReadBool(&bVisible);
      if ( rc && false == bVisible)
        SetHiddenModelComponentState(true);
      bVisible = (false == ModelComponentStatus().IsHidden());

      if ( rc && minor_version >= 2 )
      {
        // line pattern index
        int line_pattern_index = ON_UNSET_INT_INDEX;
        rc = file.Read3dmReferencedComponentIndex( ON_ModelComponent::Type::LinePattern, &line_pattern_index );
        if (rc && ON_UNSET_INT_INDEX != line_pattern_index)
          SetLinetypeIndex(line_pattern_index);

        if (rc && minor_version >= 3 )
        {
          // 23 March 2005 Dale Lear
          rc = file.ReadColor( m_plot_color);
          if (rc) rc = file.ReadDouble( &m_plot_weight_mm);

          if (rc && minor_version >= 4 )
          {
            bool bLocked = false;
            rc = file.ReadBool(&bLocked);
            if (rc && bLocked )
              SetLockedModelComponentState(bLocked);
            bLocked = ModelComponentStatus().IsLocked();

            if (rc && minor_version >= 5 )
            {
              ON_UUID layer_id = ON_nil_uuid;
              rc = file.ReadUuid(layer_id);
              if (rc)
                SetId(layer_id);
              if ( rc
                   && minor_version >= 6
                   && file.ArchiveOpenNURBSVersion() > 200505110
                 )
              {
                // Some files saved with opennurbs version 200505110 
                // do not contain correctly written m_parent_layer_id
                // and m_bExpanded values.
                // It is ok to default these values.
                ON_UUID parent_layer_id = ON_nil_uuid;
                rc = file.ReadUuid(parent_layer_id);
                if (rc)
                {
                  SetParentId(parent_layer_id);
                  if ( ON_UuidIsNotNil(parent_layer_id) )
                  {
                    //SetParentId(parent_layer_id);
                    if ( ModelComponentStatus().IsHidden() )
                      SetPersistentVisibility(false);
                    if ( ModelComponentStatus().IsLocked())
                      SetPersistentLocking(true);
                  }
                  rc = file.ReadBool(&m_bExpanded);
                }
              }

              if ( rc && minor_version >= 7 )
              {
                // 1.7 field - added 6 June 2006
                rc = m_rendering_attributes.Read(file);

                if ( rc && minor_version >= 8 )
                {
                  // 1.8 field - added 19 Sep 2006
                  rc = file.ReadUuid(m_display_material_id);

                  if (rc && minor_version == 9)
                  {
                    // 1.9 field - added 11 Aug 2021 and removed on 12 Aug 2021
                    // Note above that we are looking specifically at minor_version of 9
                    // read two chars and throw them away.
                    // minor_version >= 10 should skip this entirely
                    unsigned char style = 0;
                    rc = file.ReadChar(&style);
                    if (rc)
                    {
                      style = 0;
                      rc = file.ReadChar(&style);
                    }
                  }

                  if (rc && minor_version >= 10)
                  {
                    unsigned char itemid = 0xFF;
                    while (rc)
                    {
                      rc = file.ReadChar(&itemid);
                      if (!rc) break;
                      if (0 == itemid)
                        break;

                      if (ON_LayerTypeCodes::ObsoleteSelectiveClippingData == itemid) //28
                      {
                        bool noClippingPlanes = false;
                        ON_UuidList selectiveList;
                        rc = file.ReadBool(&noClippingPlanes);
                        if (!rc) break;
                        rc = selectiveList.Read(file);
                        if (!rc) break;
                        //if (noClippingPlanes)
                        //  SetClipParticipationForNone();
                        //else if (selectiveList.Count() > 0)
                        //  SetClipParticipationList(selectiveList.Array(), selectiveList.Count(), true);
                        //else
                        //  SetClipParticipationForAll();

                        rc = file.ReadChar(&itemid);
                        if (!rc || 0 == itemid) break;
                      }

                      if (minor_version <= 10)
                        break;

                      if (ON_LayerTypeCodes::SectionHatchIndex == itemid) // 30
                      {
                        int pattern = 0;
                        rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::HatchPattern, &pattern);
                        if (!rc) break;
                        ON_SectionStyle section_style;
                        CustomSectionStyle(&section_style);
                        section_style.SetHatchIndex(pattern);
                        SetCustomSectionStyle(section_style);
                        rc = file.ReadChar(&itemid);
                        if (!rc || 0 == itemid) break;
                      }

                      if (ON_LayerTypeCodes::SectionHatchScale == itemid) // 31
                      {
                        double scale = 1;
                        rc = file.ReadDouble(&scale);
                        if (!rc) break;
                        ON_SectionStyle section_style;
                        CustomSectionStyle(&section_style);
                        section_style.SetHatchScale(scale);
                        SetCustomSectionStyle(section_style);
                        rc = file.ReadChar(&itemid);
                        if (!rc || 0 == itemid) break;
                      }

                      if (ON_LayerTypeCodes::SectionHatchRotation == itemid) // 32
                      {
                        double rotation = 0;
                        rc = file.ReadDouble(&rotation);
                        if (!rc) break;
                        ON_SectionStyle section_style;
                        CustomSectionStyle(&section_style);
                        section_style.SetHatchRotation(rotation);
                        SetCustomSectionStyle(section_style);
                        rc = file.ReadChar(&itemid);
                        if (!rc || 0 == itemid) break;
                      }

                      if (minor_version <= 11)
                        break;

                      if (ON_LayerTypeCodes::SectionFillRule == itemid)
                      {
                        unsigned char c = 0;
                        rc = file.ReadChar(&c);
                        if (!rc) break;
                        ON_SectionStyle section_style;
                        CustomSectionStyle(&section_style);
                        section_style.SetSectionFillRule(ON::SectionFillRuleFromUnsigned(c));
                        SetCustomSectionStyle(section_style);
                        rc = file.ReadChar(&itemid);
                        if (!rc || 0 == itemid) break;
                      }

                      if (minor_version <= 12)
                        break;

                      if (ON_LayerTypeCodes::CustomLinetype == itemid)
                      {
                        ON_Linetype lt;
                        rc = lt.Read(file);
                        if (!rc) break;
                        // 17 Feb 2023 S. Baer
                        // Custom linetype per layer was a short lived experiment
                        // We still need to read a linetype out of the few 3dm files
                        // that have them, but we no longer set any sort of custom linetype
                        //SetCustomLinetype(lt);
                        rc = file.ReadChar(&itemid);
                        if (!rc || 0 == itemid) break;
                      }

                      if (minor_version <= 13)
                        break;

                      // visible in new detail (1.14)
                      if (ON_LayerTypeCodes::PerViewportIsVisibleInNewDetails == itemid)
                      {
                        bool b = true;
                        rc = file.ReadBool(&b);
                        if (!rc) break;
                        SetPerViewportIsVisibleInNewDetails(b);
                        rc = file.ReadChar(&itemid);
                        if (!rc || 0 == itemid) break;
                      }

                      if (minor_version <= 14)
                        break;

                      if (ON_LayerTypeCodes::CustomSectionStyle == itemid)
                      {
                        ON_SectionStyle section_style;
                        rc = section_style.Read(file);
                        if (!rc) break;
                        SetCustomSectionStyle(section_style);
                        rc = file.ReadChar(&itemid);
                        if (!rc || 0 == itemid) break;
                      }

                      if (ON_LayerTypeCodes::ObsoleteSelectiveClippingListType == itemid)
                      {
                        bool b = true;
                        file.ReadBool(&b);
                        if (!rc) break;
                        //if (nullptr == m_private)
                        //  m_private = new ON_LayerPrivate();
                        //m_private->m_clipplane_list_is_participation = b;

                        rc = file.ReadChar(&itemid);
                        if (!rc || 0 == itemid) break;
                      }

                      // Add new item reading above and increment the LastLayerTypeCode value
                      // in the enum. Be sure to test reading of old and new files by old and new
                      // code, before checking in your changes.
                      if (itemid > ON_LayerTypeCodes::LastLayerTypeCode)
                      {
                        // we are reading file written with code newer than this code
                        itemid = 0;
                      }

                      break;
                    }

                    if (rc && 0 != itemid)
                    {
                      ON_ERROR("Bug in ON_Layer::Read or Write");
                    }

                  }
                }
              }
            }
          }
        }
      }
    }

    if ( IdIsNil()  )
    {
      // old files didn't have layer ids and we need unique ones.
      SetId();
    }
  }
  else
  {
    ON_ERROR("ON_Layer::Read() encountered a layer written by future code.");
    rc = false;
  }

  return rc;
}

ON::object_type ON_Layer::ObjectType() const
{
  return ON::layer_object;
}

//////////////////////////////////////////////////////////////////////
//
// Interface


void ON_Layer::SetColor( ON_Color c)
{
  m_color = c;
}

void ON_Layer::SetPlotColor( ON_Color c)
{
  m_plot_color = c;
}

ON_Color ON_Layer::Color() const
{
  return m_color;
}

ON_Color ON_Layer::PlotColor() const
{
  return ((m_plot_color == ON_UNSET_COLOR) ? m_color : m_plot_color);
}

bool ON_Layer::SetLinetypeIndex( int index)
{
  if( m_linetype_index != index )
  {
    IncrementContentVersionNumber();
    m_linetype_index = index;
    return true;
  }
  return false;
}

int ON_Layer::LinetypeIndex() const
{
  return m_linetype_index;
}


ON_UUID ON_Layer::ParentLayerId() const
{
  return ParentId();
}

void ON_Layer::SetParentLayerId(
  ON_UUID parent_layer_id
  )
{
  SetParentId(parent_layer_id);
}



bool ON_Layer::IsVisible() const
{
  return IsHidden() ? false : true;
}

bool ON_Layer::IsVisible(const ON_3dmView* view) const
{
  if (nullptr == view)
    return IsVisible();

  if (view->m_view_type == ON::view_type::model_view_type)
    return ModelIsVisible();

  return PerViewportIsVisible(view->m_vp.ViewportId());
}

void ON_Layer::SetVisible( bool bVisible )
{
  SetHiddenModelComponentState( bVisible ? false : true );
  bVisible = (false == IsHidden());
  if ( ParentIdIsNil() )
    UnsetPersistentVisibility();
  else if ( bVisible )
  {
    // When a parent layer is turned off, the m_bVisible value for
    // every child layer layer is set to false. When a parent layer
    // is turned on and the visible child setting is true, the
    // child's m_bVisible value is set to true.
    //
    // This call ensures that if, at some point in the future, the
    // parent layer is turned off and then turned back on, this
    // layer will get turned back on as well.
    SetPersistentVisibility(true);
  }
}

void ON_Layer::SetLocked( bool bLocked )
{
  SetLockedModelComponentState(bLocked);
  bLocked = IsLocked();

  if ( ParentIdIsNil() )
    UnsetPersistentLocking();
  else if ( !bLocked )
  {
    // When a parent layer is locked off, the m_bLocked value for
    // every child layer layer is set to true. When a parent layer
    // is unlocked on and the locked child setting is false, the
    // child's m_bLocked value is set to false.
    //
    // This call ensures that if, at some point in the future, the
    // parent layer is locked and then unlocked, this layer will 
    // get unlocked on as well.
    SetPersistentLocking(false);
  }
}

bool ON_Layer::IsVisibleAndNotLocked() const
{
  return (false == IsHidden() && false == IsLocked());
}

bool ON_Layer::IsVisibleAndLocked() const
{
  return (false == IsHidden() && IsLocked());
}

bool ON_Layer::SetRenderMaterialIndex( int i )
{
  if ( i != m_material_index )
    IncrementContentVersionNumber();
  m_material_index = i;
  return true;
}

int ON_Layer::RenderMaterialIndex() const
{
  return m_material_index;
}

bool ON_Layer::SetIgesLevel( int level )
{
  m_iges_level = level;
  return true;
}

int ON_Layer::IgesLevel() const
{
  return m_iges_level;
}

double ON_Layer::PlotWeight() const
{
  return m_plot_weight_mm;
}

void ON_Layer::SetPlotWeight(double plot_weight_mm)
{
  m_plot_weight_mm = (ON_IsValid(plot_weight_mm) && (plot_weight_mm>0.0 || -1.0==plot_weight_mm) ) 
                   ? plot_weight_mm 
                   : 0.0;
}


////////////////////////////////////////////////////////////////
//
// BEGIN ON__LayerPerViewSettings class
//

class /*NEVER EXPORT THIS CLASS DEFINITION*/ ON__LayerPerViewSettings
{
#if !defined(ON_BOZO_VACCINE_3E4904E6E9304fbcAA42EBD407AEFE3B)
#error Never copy this class definition or put this definition in a header file!
#endif
public:
  ON__LayerPerViewSettings();
  void SetDefaultValues();
  bool Write( const ON_Layer& layer, ON_BinaryArchive& binary_archive ) const;
  bool Read( const ON_Layer& layer, ON_BinaryArchive& binary_archive);

  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  ON_UUID m_viewport_id;   // id of the viewport with custom layer settings
                           // if this id is nil, then the rest of the settings
                           // in this class are meaningless.
  ON_Color m_color;        // ON_UNSET_COLOR means use ON_Layer::m_color
  ON_Color m_plot_color;   // ON_UNSET_COLOR means use ON_Layer::m_plot_color
  double m_plot_weight_mm; // ON_UNSET_VALUE means use ON_Layer::m_plot_weight_mm

  unsigned char m_visible; // 0 means use ON_Layer::m_bVisible
                           // 1 = visible in viewport
                           // 2 = off in viewport
  unsigned char m_persistent_visibility; // 0 = unset, 1 = visible, 2 = not visible

  static
  int Compare(
      const ON__LayerPerViewSettings* a,
      const ON__LayerPerViewSettings* b 
      );

  /*
  Returns:
    A bitfield that sets the bits if a layer setting is
    per viewport for the specified for the viewport. 
    The ON_Layer::PER_VIEWPORT_SETTINGS enum values 
    which bits correspond to which settings. 
  Remarks:
    If m_viewport_id is nil, this function returns 0. 
  */
  unsigned int SettingsMask() const;

  /*
  Description:
    Copy specified settings from src to this class.
  Parameters:
    src - [in]
      settings to copy
    settings_mask - [in]
      a bitfield that specifies which settings to copy.  The bits
      are defined in the ON_Layer::PER_VIEWPORT_SETTINGS enum.
  */
  void CopySettings( 
      const ON__LayerPerViewSettings* src, 
      unsigned int settings_mask 
      );
};

ON__UINT32 ON__LayerPerViewSettings::DataCRC(ON__UINT32 current_remainder) const
{
  const unsigned int settings_mask = SettingsMask();
  if ( 0 != settings_mask )
  {
    if ( 0 != (settings_mask & ON_Layer::per_viewport_id) )
      current_remainder = ON_CRC32(current_remainder,sizeof(m_viewport_id),&m_viewport_id);
    if ( 0 != (settings_mask & ON_Layer::per_viewport_color) )
      current_remainder = ON_CRC32(current_remainder,sizeof(m_color),&m_color);
    if ( 0 != (settings_mask & ON_Layer::per_viewport_plot_color) )
      current_remainder = ON_CRC32(current_remainder,sizeof(m_plot_color),&m_plot_color);
    if ( 0 != (settings_mask & ON_Layer::per_viewport_plot_weight) )
      current_remainder = ON_CRC32(current_remainder,sizeof(m_plot_weight_mm),&m_plot_weight_mm);
    if ( 0 != (settings_mask & ON_Layer::per_viewport_visible) )
      current_remainder = ON_CRC32(current_remainder,sizeof(m_visible),&m_visible);
    if ( 0 != (settings_mask & ON_Layer::per_viewport_persistent_visibility) )
      current_remainder = ON_CRC32(current_remainder,sizeof(m_persistent_visibility),&m_persistent_visibility);
  }
  return current_remainder;
}

void ON__LayerPerViewSettings::CopySettings( const ON__LayerPerViewSettings* src, unsigned int settings_mask )
{
  if ( 0 != src && this != src && 0 != settings_mask )
  {
    if ( 0 != (settings_mask & ON_Layer::per_viewport_id) )
      m_viewport_id = src->m_viewport_id;
    if ( 0 != (settings_mask & ON_Layer::per_viewport_color) )
      m_color = src->m_color;
    if ( 0 != (settings_mask & ON_Layer::per_viewport_plot_color) )
      m_plot_color = src->m_plot_color;
    if ( 0 != (settings_mask & ON_Layer::per_viewport_plot_weight) )
      m_plot_weight_mm = src->m_plot_weight_mm;
    if ( 0 != (settings_mask & ON_Layer::per_viewport_visible) )
      m_visible = src->m_visible;
    if ( 0 != (settings_mask & ON_Layer::per_viewport_persistent_visibility) )
      m_persistent_visibility = src->m_persistent_visibility;
  }
}

int ON__LayerPerViewSettings::Compare( const ON__LayerPerViewSettings* a, const ON__LayerPerViewSettings* b )
{
  int rc = ON_UuidCompare(a->m_viewport_id,b->m_viewport_id);
  if ( 0 == rc )
  {
    unsigned int abits = a->SettingsMask();
    unsigned int bbits = b->SettingsMask();
    rc = ((int)abits) - ((int)bbits);
    if ( 0 == rc )
    {
      if ( 0 != (ON_Layer::per_viewport_visible & abits) )
      {
        rc = ((int)a->m_visible) - ((int)b->m_visible);
      }
      if ( 0 == rc && 0 != (ON_Layer::per_viewport_persistent_visibility & abits) )
      {
        rc = ((int)a->m_persistent_visibility) - ((int)b->m_persistent_visibility);
      }
      if ( 0 == rc && 0 != (ON_Layer::per_viewport_color & abits) )
      {
        rc = ((int)a->m_color) - ((int)b->m_color);
      }
      if ( 0 == rc && 0 != (ON_Layer::per_viewport_plot_color & abits) )
      {
        rc = ((int)a->m_plot_color) - ((int)b->m_plot_color);
      }
      if ( 0 == rc && 0 != (ON_Layer::per_viewport_plot_weight & abits) )
      {
        if ( a->m_plot_weight_mm < b->m_plot_weight_mm )
          rc = -1;
        else if ( a->m_plot_weight_mm > b->m_plot_weight_mm )
          rc = 1;
      }
    }
  }
  return rc;
}

unsigned int ON__LayerPerViewSettings::SettingsMask() const
{
  // It is critical that this function returns
  // zero when m_viewport_id = nil and returns
  // zero when no layer properties are overridden
  // for the specified viewport.
  unsigned int bits = 0;
  if ( !ON_UuidIsNil(m_viewport_id) )
  {
    if ( ON_UNSET_COLOR != m_color )
      bits |= ON_Layer::per_viewport_color;
    if ( ON_UNSET_COLOR != m_plot_color )
      bits |= ON_Layer::per_viewport_plot_color;
    if ( (m_plot_weight_mm >= 0.0 || -1.0 == m_plot_weight_mm) && ON_IsValid(m_plot_weight_mm) )
      bits |= ON_Layer::per_viewport_plot_weight;
    if ( 1 == m_visible || 2 == m_visible )
      bits |= ON_Layer::per_viewport_visible;
    if ( 1 == m_persistent_visibility || 2 == m_persistent_visibility )
      bits |= ON_Layer::per_viewport_persistent_visibility;
    // It is critical that bit "1" is set only if
    // some layer property is overridden.  That's 
    // why the 0 != bits test is here.
    if ( 0 != bits )
      bits |= ON_Layer::per_viewport_id;
  }

  return bits;
}

ON__LayerPerViewSettings::ON__LayerPerViewSettings()
{
  SetDefaultValues();
}

void ON__LayerPerViewSettings::SetDefaultValues()
{
  memset(this,0,sizeof(*this));
  m_color = ON_UNSET_COLOR;
  m_plot_color = ON_UNSET_COLOR;
  m_plot_weight_mm = ON_UNSET_VALUE;
}

bool ON__LayerPerViewSettings::Write(const ON_Layer& layer, ON_BinaryArchive& binary_archive) const
{
  if ( !binary_archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,2) )
    return false;

  bool rcc = false;
  for(;;)
  {
    // This complicated "bits" stuff is to minimize number of bytes
    // written in the file.  Even though long term storage space is 
    // nearly free, we have lots of customers who complain about 
    // large file size and so ...
    unsigned int bits = SettingsMask();
    if ( !binary_archive.WriteInt(1,&bits) )
      break;
    
    if ( 0 == bits )
    {
      rcc = true;
      break; // all settings are defaults or viewport_id is nil
    }

    if ( !binary_archive.WriteUuid(m_viewport_id) )
      break;

    if ( 0 != (ON_Layer::per_viewport_color & bits) )
    {
      if  ( !binary_archive.WriteColor(m_color) )
        break;
    }

    if ( 0 != (ON_Layer::per_viewport_plot_color & bits) )
    {
      if ( !binary_archive.WriteColor(m_plot_color) )
        break;
    }

    if ( 0 != (ON_Layer::per_viewport_plot_weight & bits) )
    {
      if ( !binary_archive.WriteDouble(m_plot_weight_mm) )
        break;
    }

    if ( 0 != (ON_Layer::per_viewport_visible & bits) )
    {
      if ( !binary_archive.WriteChar(m_visible) )
        break;
      // version 1.1 addition
      if ( !binary_archive.WriteChar(m_visible) ) // (makes old a file old rhinos can read)
        break;
    }

    // 1.2 addition
    if ( 0 != (ON_Layer::per_viewport_persistent_visibility & bits) )
    {
      if ( !binary_archive.WriteChar(m_persistent_visibility) )
        break;
    }

    rcc = true;
    break;
  }

  if ( !binary_archive.EndWrite3dmChunk() )
    rcc = false;

  return rcc;
}

bool ON__LayerPerViewSettings::Read(const ON_Layer& layer, ON_BinaryArchive& binary_archive)
{
  SetDefaultValues();

  int major_version = 0;
  int minor_version = 0;
  if ( !binary_archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version) )
    return false;

  bool rc = false;
  for(;;)
  {
    if (1 != major_version)
      break;

    // This complicated "bits" stuff is to minimize number of bytes
    // written in the file.  Even though long term storage space is 
    // nearly free, we have lots of customers who complain about 
    // large file size and so ...
    unsigned int bits = 0;
    if ( !binary_archive.ReadInt(1,&bits) )
      break;
    if ( 0 == bits )
    {
      rc = true;
      break;
    }

    if ( !binary_archive.ReadUuid(m_viewport_id) )
      break;

    if ( 0 != (ON_Layer::per_viewport_color & bits) )
    {
      if ( !binary_archive.ReadColor(m_color) )
        break;
    }

    if ( 0 != (ON_Layer::per_viewport_plot_color & bits) )
    {
      if ( !binary_archive.ReadColor(m_plot_color) )
        break;
    }

    if ( 0 != (ON_Layer::per_viewport_plot_weight & bits) )
    {
      if ( !binary_archive.ReadDouble(&m_plot_weight_mm) )
        break;
    }

    if ( 0 != (ON_Layer::per_viewport_visible & bits) )
    {
      if ( !binary_archive.ReadChar(&m_visible) )
        break;
      if ( minor_version >= 1 )
      {
        // for reading older Rhino files
        // Yes, writing m_visible and reading m_persistent_visibility is done on purpose.
        if ( !binary_archive.ReadChar(&m_persistent_visibility) )
          break;
      }
    }

    if ( minor_version >= 2 )
    {
      if ( 0 != (ON_Layer::per_viewport_persistent_visibility & bits) )
      {
        if ( !binary_archive.ReadChar(&m_persistent_visibility) )
          break;
      }
    }

    if ( layer.ParentIdIsNil() )
      m_persistent_visibility = 0;
    rc = true;
    break;
  }

  if ( !binary_archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}


//
//
// END ON__LayerPerViewSettings class
//
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
//
// BEGIN ON__LayerExtensions user data class
//

class /*NEVER EXPORT THIS CLASS DEFINITION*/ ON__LayerExtensions : public ON_UserData
{
#if !defined(ON_BOZO_VACCINE_3E4904E6E9304fbcAA42EBD407AEFE3B)
#error Never copy this class definition or put this definition in a header file!
#endif
  ON_OBJECT_DECLARE(ON__LayerExtensions);

public:
  ON__LayerExtensions();
  ~ON__LayerExtensions();
  // default copy constructor and operator= work fine.

public:
  // virtual ON_Object override
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  // virtual ON_Object override
  unsigned int SizeOf() const override;
  // virtual ON_Object override
  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const override;
  // virtual ON_Object override
  bool Write(ON_BinaryArchive& binary_archive) const override;
  // virtual ON_Object override
  bool Read(ON_BinaryArchive& binary_archive) override;
  // virtual ON_UserData override
  bool Archive() const override;
  // virtual ON_UserData override
  bool GetDescription( ON_wString& description ) override;

public:
  bool IsEmpty() const;

  static
  ON__LayerPerViewSettings* ViewportSettings(
      const ON_Layer& layer, const unsigned char* layer_m_extension_bits, 
      ON_UUID viewport_id, 
      bool bCreate
      );

  static
  void DeleteViewportSettings(
      const ON_Layer& layer, const unsigned char* layer_m_extension_bits, 
      const ON__LayerPerViewSettings* vp_settings_to_delete
      );

  static
  ON__LayerExtensions* LayerExtensions(
      const ON_Layer& layer, const unsigned char* layer_m_extension_bits,
      bool bCreate
      );

  // per viewport overrides of color, linetype, plot color, plot weight, and visibility
  ON_SimpleArray<ON__LayerPerViewSettings> m_vp_settings;
};

#undef ON_BOZO_VACCINE_3E4904E6E9304fbcAA42EBD407AEFE3B

ON_OBJECT_IMPLEMENT(ON__LayerExtensions,ON_UserData,"3E4904E6-E930-4fbc-AA42-EBD407AEFE3B");

ON__LayerExtensions* ON__LayerExtensions::LayerExtensions(const ON_Layer& layer, const unsigned char* layer_m_extension_bits, bool bCreate)
{
  ON__LayerExtensions* ud = ON__LayerExtensions::Cast(layer.GetUserData(ON_CLASS_ID(ON__LayerExtensions)));

  if ( 0 == ud )
  {
    if ( bCreate )
    {
      ud = new ON__LayerExtensions();
      const_cast<ON_Layer&>(layer).AttachUserData(ud);
      // Clear 0x01 bit of ON_Layer::m_extension_bits so 
      // ON_Layer visibility and color queries will check
      // for ON__LayerExtensions userdata.
      ClearExtensionBit( const_cast<unsigned char*>(layer_m_extension_bits), 0x01 );
    }
    else
    {
      // Set 0x01 bit of ON_Layer::m_extension_bits so 
      // ON_Layer visibility and color queries will not
      // perform the expensive check for ON__LayerExtensions 
      // userdata. This speeds up visibility and color queries 
      // that occur millions of times when complicated models
      // are rendered.
      SetExtensionBit( const_cast<unsigned char*>(layer_m_extension_bits), 0x01 );
    }
  }
  else
  {
    // Clear 0x01 bit of ON_Layer::m_extension_bits so 
    // ON_Layer visibility and color queries will check
    // for ON__LayerExtensions userdata.
    ClearExtensionBit( const_cast<unsigned char*>(layer_m_extension_bits), 0x01 );
  }

  return ud;
}

ON__LayerExtensions::ON__LayerExtensions()
{
  m_userdata_uuid = ON_CLASS_ID(ON__LayerExtensions);
  m_application_uuid = ON_opennurbs5_id;
  m_userdata_copycount = 1;
}

ON__LayerExtensions::~ON__LayerExtensions()
{
}

// virtual ON_Object override
bool ON__LayerExtensions::IsValid( ON_TextLog* text_log ) const
{
  return true;
}

// virtual ON_Object override
unsigned int ON__LayerExtensions::SizeOf() const
{
  size_t sz = sizeof(*this) - sizeof(ON_UserData);
  sz += m_vp_settings.SizeOfArray();
  return (unsigned int)sz;
}

// virtual ON_Object override
ON__UINT32 ON__LayerExtensions::DataCRC(ON__UINT32 current_remainder) const
{
  ON__UINT32 crc = 0;
  crc = m_vp_settings.DataCRC(crc);
  return crc;
}

// virtual ON_Object override
bool ON__LayerExtensions::Write(ON_BinaryArchive& binary_archive) const
{
  bool rc = binary_archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
  if ( !rc )
    return false;

  for(;;)
  {
    const ON_Layer* layer = ON_Layer::Cast( Owner() );
    if ( 0 == layer )
      break;
    int count = m_vp_settings.Count();
    rc = binary_archive.WriteInt(count);
    if ( !rc ) break;
    for ( int i = 0; i < count && rc; i++ )
    {
      rc = m_vp_settings[i].Write( *layer, binary_archive );
    }
    if (!rc) break;

    break;
  }

  if ( !binary_archive.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

// virtual ON_Object override
bool ON__LayerExtensions::Read(ON_BinaryArchive& binary_archive)
{
  m_vp_settings.SetCount(0);

  int major_version = 0;
  int minor_version = 0;
  bool rc = binary_archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if ( !rc )
    return false;

  for(;;)
  {
    const ON_Layer* layer = ON_Layer::Cast( Owner() );
    rc = ( 0 != layer );
    if (!rc) break;

    rc = (1 == major_version);
    if (!rc) break;

    int count = 0;
    rc = binary_archive.ReadInt(&count);
    if ( !rc ) break;
    m_vp_settings.Reserve(count);
    for ( int i = 0; i < count; i++ )
    {
      rc = m_vp_settings.AppendNew().Read(*layer,binary_archive);
      if (!rc) 
      {
        m_vp_settings.Remove();
        break;
      }
      if ( 0 == m_vp_settings.Last()->SettingsMask() )
        m_vp_settings.Remove();
    }

    // to make ON_Layer::PerViewportSettingsCRC() return
    // equal values for equal settings, it is critical
    // that m_vp_settings[] be sorted.
    m_vp_settings.QuickSort(ON__LayerPerViewSettings::Compare);

    if (!rc) break;

    break;
  }

  if ( !binary_archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

// virtual ON_UserData override
bool ON__LayerExtensions::Archive() const
{
  return !IsEmpty();
}

// virtual ON_UserData override
bool ON__LayerExtensions::GetDescription( ON_wString& description )
{
  description = L"Layer Extensions";
  return true;
}

ON__LayerPerViewSettings* ON__LayerExtensions::ViewportSettings( 
  const ON_Layer& layer,
  const unsigned char* layer_m_extension_bits,
  ON_UUID viewport_id,
  bool bCreate
  )
{
  if ( !ON_UuidIsNil(viewport_id) )
  {
    ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(layer,layer_m_extension_bits,bCreate);
    if ( ud )
    {
      int i;
      const int vp_settings_count = ud->m_vp_settings.Count();
      ON__LayerPerViewSettings* vp_settings = ud->m_vp_settings.Array();
      for ( i = 0; i < vp_settings_count; i++ )
      {
        if ( 0 == memcmp(&viewport_id,&vp_settings[i].m_viewport_id,sizeof(ON_UUID)) )
          return (vp_settings+i);
      }
      if ( bCreate )
      {
        ON__LayerPerViewSettings& new_vp_settings = ud->m_vp_settings.AppendNew();
        vp_settings = ud->m_vp_settings.Array(); // appending can grow the array
        new_vp_settings.SetDefaultValues();
        new_vp_settings.m_viewport_id = viewport_id;

        // to make ON_Layer::PerViewportSettingsCRC() return
        // equal values for equal settings, it is critical
        // that m_vp_settings[] be sorted.
        ud->m_vp_settings.QuickSort(ON__LayerPerViewSettings::Compare);

        for ( i = 0; i <= vp_settings_count; i++ ) // "i <= ..." is correct because of the .AppendNew()
        {
          if ( 0 == memcmp(&viewport_id,&vp_settings[i].m_viewport_id,sizeof(ON_UUID)) )
            return (vp_settings+i);
        }
      }
    }
  }
  return 0;
}

void ON__LayerExtensions::DeleteViewportSettings( 
  const ON_Layer& layer, 
  const unsigned char* layer_m_extension_bits,
  const ON__LayerPerViewSettings* vp_settings_to_delete
  )
{
  ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(layer,layer_m_extension_bits,false);
  if ( ud )
  {
    if ( 0 == vp_settings_to_delete )
    {
      delete ud;
      // Set bit 0x01 of ON_Layer::m_extension_bits to prevent
      // ON_Layer visibility and color queries from wasting
      // time looking for userdata.
      SetExtensionBit( const_cast<unsigned char*>(layer_m_extension_bits), 0x01 );
    }
    else
    {
      const size_t vp_settings_count = ud->m_vp_settings.Count();
      if ( vp_settings_count > 0 )
      {
        const ON__LayerPerViewSettings* vp_settings0 = ud->m_vp_settings.Array();
        if ( vp_settings0 <= vp_settings_to_delete )
        {
          int i = (int)(vp_settings_to_delete-vp_settings0);
          ud->m_vp_settings.Remove(i);
        }
      }
      if ( ud->IsEmpty() )
      {
        delete ud;
        // Set bit 0x01 of ON_Layer::m_extension_bits to prevent
        // ON_Layer visibility and color queries from wasting
        // time looking for userdata.
        SetExtensionBit( const_cast<unsigned char*>(layer_m_extension_bits), 0x01 );
      }
    }
  }
}

bool ON__LayerExtensions::IsEmpty() const
{
  const int count = m_vp_settings.Count();

  for ( int i = 0; i < count; i++ )
    if ( 0 != m_vp_settings[i].SettingsMask() )
      return false;

  return true; // nothing of value in this user data
}

//
// END ON__LayerExtensions user data class
//
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
//
// BEGIN ON_Layer per viewport interface functions
//

void ON_Layer::SetPerViewportColor( ON_UUID viewport_id, ON_Color layer_color )
{
  if ( ON_UuidIsNil(viewport_id) )
  {
    DeletePerViewportColor(viewport_id);
    if ( ON_Color::UnsetColor != layer_color )
      m_color = layer_color;
  }
  else
  {
    bool bSet = ( layer_color != ON_UNSET_COLOR );
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, bSet );
    if ( vp_settings )
    {
      vp_settings->m_color = layer_color;
      if ( !bSet && 0 == vp_settings->SettingsMask() )
        ON__LayerExtensions::DeleteViewportSettings(*this, &m_extension_bits, vp_settings);
    }
  }
}

//void ON_Layer::SetColor( ON_Color layer_color, const ON_UUID& viewport_id )
//{
//  SetPerViewportColor( viewport_id, layer_color );
//}

ON_Color ON_Layer::PerViewportColor( ON_UUID viewport_id ) const
{
  if ( !ExtensionBit(m_extension_bits,0x01) )
  {
    const ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
    if ( 0 != vp_settings && ON_UNSET_COLOR != vp_settings->m_color )
      return vp_settings->m_color;
  }

  return m_color;
}

//ON_Color ON_Layer::Color( const ON_UUID& viewport_id ) const
//{
//  return PerViewportColor( viewport_id );
//}

void ON_Layer::SetPerViewportPlotColor( ON_UUID viewport_id, ON_Color plot_color )
{
  if ( ON_UuidIsNil(viewport_id) )
  {
    DeletePerViewportPlotColor(viewport_id);
    SetPlotColor(plot_color);
  }
  else
  {
    bool bSet = ( plot_color != ON_UNSET_COLOR );
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, bSet );
    if ( vp_settings )
    {
      vp_settings->m_plot_color = plot_color;
      if ( !bSet && 0 == vp_settings->SettingsMask() )
        ON__LayerExtensions::DeleteViewportSettings(*this, &m_extension_bits,vp_settings);
    }
  }
}

//void ON_Layer::SetPlotColor( ON_Color plot_color, const ON_UUID& viewport_id )
//{
//  return SetPerViewportPlotColor( viewport_id, plot_color );
//}

ON_Color ON_Layer::PerViewportPlotColor( ON_UUID viewport_id ) const
{
  if ( !ExtensionBit(m_extension_bits,0x01) )
  {
    const ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
    if ( 0 != vp_settings && vp_settings->m_plot_color != ON_UNSET_COLOR )
      return vp_settings->m_plot_color;
  }

  // no per viewport settings
  // 2-Nov-2009 Dale Fugier, modified to call default PlotColor()
  return PlotColor();
}

void ON_Layer::SetPerViewportPlotWeight( ON_UUID viewport_id, double plot_weight_mm )
{
  if ( ON_UuidIsNil(viewport_id) )
  {
    DeletePerViewportPlotWeight(viewport_id);
    SetPlotWeight(plot_weight_mm); // this call handles invalid plot weights
  }
  else
  {
    bool bSet = ( ON_IsValid(plot_weight_mm) && (plot_weight_mm>=0.0 || -1.0==plot_weight_mm) );
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, bSet );
    if ( vp_settings )
    {
      vp_settings->m_plot_weight_mm = (bSet) ? plot_weight_mm : ON_UNSET_VALUE;
      if ( !bSet && 0 == vp_settings->SettingsMask() )
        ON__LayerExtensions::DeleteViewportSettings(*this, &m_extension_bits, vp_settings);
    }
  }
}

double ON_Layer::PerViewportPlotWeight( ON_UUID viewport_id ) const
{
  if ( !ExtensionBit(m_extension_bits,0x01) )
  {
    const ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
    if ( 0 != vp_settings && (vp_settings->m_plot_weight_mm >= 0.0 || -1.0 == vp_settings->m_plot_weight_mm) )
      return vp_settings->m_plot_weight_mm;
  }
  return PlotWeight();
}

// {5CCA6037-AFC7-4204-9548-EC32CD7177D6}
static const ON_UUID ON_model_viewport_id = { 0x5cca6037, 0xafc7, 0x4204, { 0x95, 0x48, 0xec, 0x32, 0xcd, 0x71, 0x77, 0xd6 } };

bool ON_Layer::ModelIsVisible() const
{
  return PerViewportIsVisible(ON_model_viewport_id);
}

void ON_Layer::SetModelVisible(bool bVisible)
{
  SetPerViewportVisible(ON_model_viewport_id, bVisible);
}

bool ON_Layer::ModelPersistentVisibility() const
{
  return PerViewportPersistentVisibility(ON_model_viewport_id);
}

void ON_Layer::SetModelPersistentVisibility(bool bPersistentVisibility)
{
  SetPerViewportPersistentVisibility(ON_model_viewport_id, bPersistentVisibility);
}

void ON_Layer::UnsetModelPersistentVisibility()
{
  UnsetPerViewportPersistentVisibility(ON_model_viewport_id);
}

void ON_Layer::DeleteModelVisible()
{
  DeletePerViewportVisible(ON_model_viewport_id);
}

bool ON_Layer::PerViewportIsVisible( ON_UUID viewport_id ) const
{
  if ( false == ExtensionBit(m_extension_bits,0x01) && ON_nil_uuid != viewport_id )
  {
    const ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
    if (vp_settings)
    {
      if ( 1 == vp_settings->m_visible )
        return true;  // per viewport ON setting overrides layer setting
      if ( 2 == vp_settings->m_visible )
        return false; // per viewport OFF setting overrides layer setting
    }
  }

  return IsVisible(); // use layer setting
}

void ON_Layer::SetPerViewportVisible( ON_UUID viewport_id, bool bVisible )
{
  if ( ON_UuidIsNil(viewport_id) )
  {
    // remove per view visible settings
    DeletePerViewportVisible(viewport_id);

    // set general visibility setting
    SetVisible(bVisible);
  }
  else 
  {
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, true );
    if (vp_settings)
    {
      vp_settings->m_visible = (bVisible)
        ? 1  // layer is on in this viewport
        : 2; // layer is off in this viewport
      if ( ParentIdIsNil() )
        vp_settings->m_persistent_visibility = 0;
      else if ( bVisible )
        vp_settings->m_persistent_visibility = 1;
    }
  }
}

bool ON_Layer::PerViewportPersistentVisibility( ON_UUID viewport_id ) const
{
  // added to fix bug 82587
  if ( !ExtensionBit(m_extension_bits,0x01) && ON_UuidIsNotNil(viewport_id) )
  {
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
    if ( 0 != vp_settings )
    {
      if ( 1 == vp_settings->m_visible )
        return true;
      if ( ParentIdIsNotNil() )
      {
        if ( 1 == vp_settings->m_persistent_visibility )
          return true;
        if ( 2 == vp_settings->m_persistent_visibility )
          return false;
      }
      if ( 2 == vp_settings->m_visible )
        return false;
    }
  }

  return PersistentVisibility();
}

void ON_Layer::SetPerViewportPersistentVisibility( ON_UUID viewport_id, bool bVisibleChild )
{
  // added to fix bug 82587
  if ( ON_UuidIsNotNil(viewport_id) )
  {
    bool bCreate = false; // This "false" is correct because the per viewport visibility
                          // setting needs to be in existence for this call to make any
                          // sense in the first place.
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, bCreate );
    if (vp_settings )
      vp_settings->m_persistent_visibility = bVisibleChild ? 1 : 2;
  }
}

void ON_Layer::UnsetPerViewportPersistentVisibility( ON_UUID viewport_id )
{
  // added to fix bug 82587
  if ( ON_UuidIsNil(viewport_id) )
  {
    ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions( *this, &m_extension_bits, false );
    if ( 0 != ud )
    {
      for ( int i = 0; i < ud->m_vp_settings.Count(); i++ )
      {
        ud->m_vp_settings[i].m_persistent_visibility = 0;
      }
    }
  }
  else
  {
    bool bCreate = false; // This "false" is correct because the per viewport visibility
                          // setting needs to be in existence for this call to make any
                          // sense in the first place.
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, bCreate );
    if (vp_settings )
      vp_settings->m_persistent_visibility = 0;
  }
}

void ON_Layer::DeletePerViewportColor( const ON_UUID& viewport_id )
{
  if ( ON_UuidIsNil(viewport_id) )
  {
    ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(*this,&m_extension_bits,false);
    if ( 0 != ud )
    {
      for ( int i = ud->m_vp_settings.Count(); i--; /*empty iterator*/ )
      {
        ud->m_vp_settings[i].m_color = ON_Color::UnsetColor;
        if ( 0 == ud->m_vp_settings[i].SettingsMask() )
          ud->m_vp_settings.Remove(i);
      }
      if ( ud->IsEmpty() )
      {
        ON__LayerExtensions::DeleteViewportSettings( *this, &m_extension_bits, 0 );
        ud = 0;
      }
    }
  }
  else
  {
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
    if (vp_settings) 
    {
      vp_settings->m_color = ON_Color::UnsetColor;
      if ( 0 == vp_settings->SettingsMask() )
        ON__LayerExtensions::DeleteViewportSettings(*this,&m_extension_bits,vp_settings);
    }
  }
}

void ON_Layer::DeletePerViewportPlotColor( const ON_UUID& viewport_id )
{
  if ( ON_UuidIsNil(viewport_id) )
  {
    ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(*this,&m_extension_bits,false);
    if ( 0 != ud )
    {
      for ( int i = ud->m_vp_settings.Count(); i--; /*empty iterator*/ )
      {
        ud->m_vp_settings[i].m_plot_color = ON_UNSET_COLOR;
        if ( 0 == ud->m_vp_settings[i].SettingsMask() )
          ud->m_vp_settings.Remove(i);
      }
      if ( ud->IsEmpty() )
      {
        ON__LayerExtensions::DeleteViewportSettings( *this, &m_extension_bits, 0 );
        ud = 0;
      }
    }
  }
  else
  {
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
    if (vp_settings) 
    {
      vp_settings->m_plot_color = ON_UNSET_COLOR;
      if ( 0 == vp_settings->SettingsMask() )
        ON__LayerExtensions::DeleteViewportSettings(*this,&m_extension_bits,vp_settings);
    }
  }
}

int ON_Layer::UpdateViewportIds( const ON_UuidPairList& viewport_id_map )
{
  if ( viewport_id_map.Count() <= 0 )
    return 0;
  ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(*this,&m_extension_bits,false);
  if ( 0 == ud )
    return 0;
  int rc = 0;
  ON_UUID new_id;
  for ( int i = 0; i < ud->m_vp_settings.Count(); i++ )
  {
    ON__LayerPerViewSettings& s = ud->m_vp_settings[i];
    if ( viewport_id_map.FindId1(s.m_viewport_id,&new_id) && s.m_viewport_id != new_id )
    {
      s.m_viewport_id = new_id;
      rc++;
    }
  }
  return rc;
}

void ON_Layer::DeletePerViewportPlotWeight( const ON_UUID& viewport_id )
{
  if ( ON_UuidIsNil(viewport_id) )
  {
    ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(*this,&m_extension_bits,false);
    if ( 0 != ud )
    {
      for ( int i = ud->m_vp_settings.Count(); i--; /*empty iterator*/ )
      {
        ud->m_vp_settings[i].m_plot_weight_mm = ON_UNSET_VALUE;
        if ( 0 == ud->m_vp_settings[i].SettingsMask() )
          ud->m_vp_settings.Remove(i);
      }
      if ( ud->IsEmpty() )
      {
        ON__LayerExtensions::DeleteViewportSettings( *this, &m_extension_bits, 0 );
        ud = 0;
      }
    }
  }
  else
  {
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
    if (vp_settings) 
    {
      vp_settings->m_plot_weight_mm = ON_UNSET_VALUE;
      if ( 0 == vp_settings->SettingsMask() )
        ON__LayerExtensions::DeleteViewportSettings(*this,&m_extension_bits,vp_settings);
    }
  }
}

void ON_Layer::DeletePerViewportVisible( const ON_UUID& viewport_id )
{
  if ( ON_UuidIsNil(viewport_id) )
  {
    ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(*this,&m_extension_bits,false);
    if ( 0 != ud )
    {
      for ( int i = ud->m_vp_settings.Count(); i--; /*empty iterator*/ )
      {
        ud->m_vp_settings[i].m_visible = 0;
        ud->m_vp_settings[i].m_persistent_visibility = 0;
        if ( 0 == ud->m_vp_settings[i].SettingsMask() )
          ud->m_vp_settings.Remove(i);
      }
      if ( ud->IsEmpty() )
      {
        ON__LayerExtensions::DeleteViewportSettings( *this, &m_extension_bits, 0 );
        ud = 0;
      }
    }
  }
  else
  {
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
    if (vp_settings) 
    {
      vp_settings->m_visible = 0;
      vp_settings->m_persistent_visibility = 0;
      if ( 0 == vp_settings->SettingsMask() )
        ON__LayerExtensions::DeleteViewportSettings(*this,&m_extension_bits,vp_settings);
    }
  }
}

void ON_Layer::GetPerViewportVisibilityViewportIds(
    ON_SimpleArray<ON_UUID>& viewport_id_list
    ) const
{
  viewport_id_list.SetCount(0);
  const ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(*this,&m_extension_bits,false);
  if ( 0 != ud )
  {
    const int count = ud->m_vp_settings.Count();
    if ( count > 0 )
    {
      viewport_id_list.Reserve(count);
      for( int i = 0; i < count; i++ )
      {
        const ON__LayerPerViewSettings& s = ud->m_vp_settings[i];
        if (    0 != ( ON_Layer::per_viewport_visible & s.SettingsMask() ) 
             || 0 != ( ON_Layer::per_viewport_persistent_visibility & s.SettingsMask() ) 
           )
        {
          viewport_id_list.Append(s.m_viewport_id);
        }
      }
    }
  }
}

bool ON_Layer::HasPerViewportSettings( const ON_UUID& viewport_id ) const
{
  return HasPerViewportSettings( viewport_id, 0xFFFFFFFF );
}

bool ON_Layer::HasPerViewportSettings(
    ON_UUID viewport_id,
    unsigned int settings_mask
    ) const
{

  if ( 0 != settings_mask )
  {
    if ( ON_UuidIsNil(viewport_id) )
    {
      const ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(*this,&m_extension_bits,false);
      if ( 0 != ud )
      {
        const int count = ud->m_vp_settings.Count();
        for ( int i = 0; i < count; i++ )
        {
          const ON__LayerPerViewSettings& s = ud->m_vp_settings[i];
          if ( 0 != (settings_mask & s.SettingsMask()) )
            return true;
        }
      }
    }
    else
    {
      const ON__LayerPerViewSettings* pvs = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
      if ( 0 != pvs && 0 != (settings_mask & pvs->SettingsMask() ) )
        return true;
    }
  }

  return false;
}

bool ON_Layer::CopyPerViewportSettings(ON_UUID source_viewport_id, ON_UUID destination_viewport_id)
{
  bool rc = false;
  if (    ON_UuidIsNotNil(source_viewport_id) 
       && ON_UuidIsNotNil(destination_viewport_id) 
       && 0 != ON_UuidCompare(source_viewport_id, destination_viewport_id)
     )
  {
    const ON__LayerPerViewSettings* src = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, source_viewport_id, false );
    if( 0 != src )
    {
      // Make a local copy of the source settings because
      // the pointer to the source settings may be invalid
      // after adding storage for the destination settings.
      const ON__LayerPerViewSettings local_src(*src);
      src = 0; // never use this pointer again in this function.
      ON__LayerPerViewSettings* dst = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, destination_viewport_id, true);
      if( 0 != dst )
      {
        *dst = local_src;
        dst->m_viewport_id = destination_viewport_id;
        rc = true;
      }
    }
  }
  return rc;
}

bool ON_Layer::CopyPerViewportSettings( 
    const ON_Layer& source_layer,
    ON_UUID viewport_id,
    unsigned int settings_mask
    )
{
  bool rc = false;
  if ( 0 != settings_mask && this != &source_layer )
  {
    if ( ON_UuidIsNil(viewport_id) )
    {
      // copy per viewport settings for every viewport
      const ON__LayerExtensions* soruce_layer_ud = ON__LayerExtensions::LayerExtensions(source_layer,&source_layer.m_extension_bits,false);
      if ( 0 != soruce_layer_ud )
      {
        const int count = soruce_layer_ud->m_vp_settings.Count();
        for ( int i = 0; i < count; i++ )
        {
          const ON__LayerPerViewSettings& src = soruce_layer_ud->m_vp_settings[i];
          ON__LayerPerViewSettings* dst = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, src.m_viewport_id, true);
          if ( 0 != dst )
          {
            dst->CopySettings(&src,settings_mask);
            rc = true;
          }
        }
      }
    }
    else
    {
      // copy per viewport settings for a specified viewport.
      const ON__LayerPerViewSettings* src = ON__LayerExtensions::ViewportSettings( source_layer, &source_layer.m_extension_bits, viewport_id, false);
      if ( 0 != src )
      {
        ON__LayerPerViewSettings* dst = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, true);
        if ( 0 != dst )
        {
          dst->CopySettings(src,settings_mask);
          rc = true;
        }
      }
    }
  }
  return rc;
}


void ON_Layer::DeletePerViewportSettings( const ON_UUID& viewport_id ) const
{
  if ( ON_UuidIsNil(viewport_id) )
  {
    ON__LayerExtensions::DeleteViewportSettings(*this,&m_extension_bits,0);
  }
  else
  {
    ON__LayerPerViewSettings* vp_settings = ON__LayerExtensions::ViewportSettings( *this, &m_extension_bits, viewport_id, false );
    if ( vp_settings )
      ON__LayerExtensions::DeleteViewportSettings(*this,&m_extension_bits,vp_settings);
  }
}


void ON_Layer::CullPerViewportSettings( int viewport_id_count, const ON_UUID* viewport_id_list )
{
  ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(*this,&m_extension_bits,false);
  if ( 0 != ud )
  {
    if ( viewport_id_count <= 0 )
    {
      // delete all per viewport settings
      ON__LayerExtensions::DeleteViewportSettings( *this, &m_extension_bits, 0 );
      ud = 0;
    }
    else if ( viewport_id_count > 0 && 0 != viewport_id_list )
    {
      int i, j;
      for ( i = ud->m_vp_settings.Count(); i--; /*empty iterator*/ )
      {
        const ON_UUID vp_id = ud->m_vp_settings[i].m_viewport_id;
        for ( j = 0; j < viewport_id_count; j++ )
        {
          if ( 0 == memcmp(&viewport_id_list[i],&vp_id,sizeof(vp_id)) )
            break;
        }
        if ( j >= viewport_id_count )
        {
          // ud->m_vp_settings[i].m_viewport_id is NOT in viewport_id_list[]
          ud->m_vp_settings.Remove(i);
        }
      }
      if ( ud->IsEmpty() )
      {
        // nothing useful in ud
        ON__LayerExtensions::DeleteViewportSettings( *this, &m_extension_bits, 0 );
        ud = 0;
      }
    }
  }
}

ON__UINT32 ON_Layer::PerViewportSettingsCRC() const
{
  ON__UINT32 crc = 0;
  if ( !ExtensionBit(m_extension_bits,0x01) )
  {
    ON__LayerExtensions* ud = ON__LayerExtensions::LayerExtensions(*this,&m_extension_bits,false);
    if ( 0 != ud )
    {
      for ( int i = 0; i < ud->m_vp_settings.Count(); i++ )
        crc = ud->m_vp_settings[i].DataCRC(crc);
    }
  }
  return crc;
}

//
// END ON_Layer per viewport interface functions
//
////////////////////////////////////////////////////////////////


bool ON_Layer::PersistentVisibility() const
{
  if ( !IsVisible() && ParentIdIsNotNil() )
  {
    switch ( 0x06 & m_extension_bits )
    {
    case 0x02:
      return true;
    case 0x04:
      return false;
    }
  }

  return IsVisible();
}

void ON_Layer::SetPersistentVisibility(bool bVisibleChild)
{
  const unsigned char and_mask = 0xF9;
  const unsigned char or_bit = ParentIdIsNotNil() 
                             ? (bVisibleChild ? 0x02 : 0x04)
                             : 0x00;
  m_extension_bits &= and_mask;
  m_extension_bits |= or_bit;
}

void ON_Layer::UnsetPersistentVisibility()
{
  const unsigned char and_mask = 0xF9;
  m_extension_bits &= and_mask;
}

bool ON_Layer::PersistentLocking() const
{
  if ( IsLocked() && ParentIdIsNotNil() )
  {
    switch ( 0x18 & m_extension_bits )
    {
    case 0x08:
      return true;
    case 0x10:
      return false;
    }
  }

  return IsLocked();
}

void ON_Layer::SetPersistentLocking(bool bLockedChild)
{
  const unsigned char and_mask = 0xE7;
  const unsigned char or_bit = ParentIdIsNotNil()
                             ? (bLockedChild ? 0x08 : 0x10)
                             : 0x00;
  m_extension_bits &= and_mask;
  m_extension_bits |= or_bit;
}

void ON_Layer::UnsetPersistentLocking()
{
  // a set bit means the child will be unlocked when the parent is unlocked
  const unsigned char and_mask = 0xE7;
  m_extension_bits &= and_mask;
}

void ON_Layer::SetCustomSectionStyle(const ON_SectionStyle& sectionStyle)
{
  if (nullptr == m_private)
    m_private = new ON_LayerPrivate();

  m_private->m_custom_section_style.reset(new ON_SectionStyle(sectionStyle));
}
const ON_SectionStyle* ON_Layer::CustomSectionStyle(ON_SectionStyle* sectionStyle) const
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
void ON_Layer::RemoveCustomSectionStyle()
{
  if (m_private)
    m_private->m_custom_section_style.reset();
}

bool ON_Layer::PerViewportIsVisibleInNewDetails() const
{
  return m_private ? m_private->m_visible_in_new_details : DefaultLayerPrivate.m_visible_in_new_details;
}

void ON_Layer::SetPerViewportIsVisibleInNewDetails(bool bVisible)
{
  if (PerViewportIsVisibleInNewDetails() == bVisible)
    return;
  if (nullptr == m_private)
    m_private = new ON_LayerPrivate();
  m_private->m_visible_in_new_details = bVisible;
}
