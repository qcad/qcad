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

#include "opennurbs_textiterator.h"
ON_VIRTUAL_OBJECT_IMPLEMENT(ON_Annotation, ON_Geometry, "B5802E0C-5B16-43C9-BD43-A3E0AC18203B");

ON::AnnotationType ON::AnnotationTypeFromUnsigned( 
  unsigned int annotation_type_as_unsigned
)
{
  switch (annotation_type_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::Aligned);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::Angular);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::Diameter);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::Radius);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::Rotated);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::Ordinate);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::ArcLen);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::CenterMark);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::Text);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::Leader);
  ON_ENUM_FROM_UNSIGNED_CASE(ON::AnnotationType::Angular3pt);
  }
  ON_ERROR("Invalid annotation_type_as_unsigned parameter");
  return ON::AnnotationType::Unset;
}

ON_Annotation::ON_Annotation(ON::AnnotationType annotation_type)
  : ON_Geometry()
  , m_annotation_type(annotation_type)
{}

ON::AnnotationType ON_Annotation::Type() const
{
  return m_annotation_type;
}

void ON_Annotation::Internal_CopyFrom(const ON_Annotation& src)
{
  m_annotation_type = src.m_annotation_type;
  m_dimstyle_id = src.m_dimstyle_id;
  m_plane = src.m_plane;
  m_horizontal_direction = src.m_horizontal_direction;
  m_allow_text_scaling = src.m_allow_text_scaling;
  if (nullptr != src.m_text)
    m_text = new ON_TextContent(*src.m_text);
  if (nullptr != src.m_override_dimstyle)
  {
    m_override_dimstyle = new ON_DimStyle(*src.m_override_dimstyle);
  }
}

void ON_Annotation::Internal_Destroy()
{
  ClearText();
  Internal_DeleteOverrideDimstyle();
}

ON_Annotation::ON_Annotation(const ON_Annotation& src)
  : ON_Geometry(src)
{
  Internal_CopyFrom(src);
}

ON_Annotation::~ON_Annotation()
{
  Internal_Destroy();
}

ON_Annotation& ON_Annotation::operator=(const ON_Annotation& src)
{
  if (&src != this)
  {
    Internal_Destroy();
    Internal_CopyFrom(src);
  }
  return *this;
}

ON::object_type ON_Annotation::ObjectType() const
{
  return ON::annotation_object;
}

bool ON_BinaryArchive::Internal_Write3dmDimStyleOverrides(
  const ON_Annotation& annotation,
  const ON_DimStyle* dim_style_overrides
)
{
  // Chunk containing dimstyle overrides
  const int content_version = 1;
  if (false == BeginWrite3dmAnonymousChunk(content_version))
    return false;

  bool rc = false;
  for (;;)
  {
    const ON_UUID annotation_dimstyle_id = annotation.DimensionStyleId();

    const bool bHasOverrideDimStyle
      = nullptr != dim_style_overrides
      && ON_nil_uuid != annotation_dimstyle_id
      && annotation_dimstyle_id == dim_style_overrides->ParentId()
      && annotation.IsOverrideDimStyleCandidate(dim_style_overrides,true)
      && (ON_ModelComponent::Type::DimStyle == Manifest().ItemFromId(annotation_dimstyle_id).ComponentType()
        || ON_DimStyle::SystemDimstyleFromId(annotation_dimstyle_id).Id() == annotation_dimstyle_id
        )
      ;

    if (!WriteBool(bHasOverrideDimStyle))
      break;

    if (bHasOverrideDimStyle)
    {
      // use archive.WriteObject() so user data will persist.
      if (!WriteObject(dim_style_overrides))
        break;
    }

    rc = true;
    break;
  }

  if (!EndWrite3dmChunk())
    rc = false;
  return rc;
}

static bool Internal_UpdateOverrideCandidateParentId(
  const ON_BinaryArchive& archive,
  ON_DimStyle* override_candidate
)
{
  for (;;)
  {
    if (
      false == archive.CheckForRemappedIds()
      && 0 == archive.ReferenceModelSerialNumber()
      && 0 == archive.InstanceDefinitionModelSerialNumber()
      )
    {
      return false; // common situation - no change required
    }


    if (nullptr == override_candidate)
      break;
    const ON_UUID archive_parent_id = override_candidate->ParentId();
    if (ON_nil_uuid == archive_parent_id)
      break;

    // We are reading a worksession reference model or reference style linked instance definition.
    // The ids in the reference file may have had a collision with ids in the active model
    // and been changed.
    const ON_ManifestMapItem parent_id_map_item = archive.ManifestMap().MapItemFromSourceId(archive_parent_id);
    if (ON_ModelComponent::Type::DimStyle != parent_id_map_item.ComponentType())
      break;
    if (false == parent_id_map_item.SourceIsSet())
      break;
    if (false == parent_id_map_item.DestinationIsSet())
      break;
    if (parent_id_map_item.SourceId() != archive_parent_id)
      break;
    
    const ON_UUID model_parent_id = parent_id_map_item.DestinationId();
    if (model_parent_id == ON_nil_uuid)
      break;

    if (model_parent_id == archive_parent_id)
      return false; // common situation - no change reqired

    // We are reading a worksession reference model or reference style linked instance definition.
    // The ids in the reference file may have had a collision with ids in the active model
    // and been changed.
    override_candidate->SetParentId(model_parent_id);
    return true; // changed parent id
  }

  return false; // unexpected but, no changes
}

bool ON_BinaryArchive::Internal_Read3dmDimStyleOverrides(
  class ON_Annotation& annotation,
  bool bFromDimStyleTable
)
{
  if (bFromDimStyleTable)
  {
    // V5 or old V6 file where override styles were kept in the dim style table
    for (;;)
    {
      if (false == m_bLegacyOverrideDimStylesInArchive)
        break;

      const ON_UUID dim_style_id = annotation.DimensionStyleId();
      if (ON_nil_uuid == dim_style_id)
        break;

      const unsigned count = this->m_archive_dim_style_table.UnsignedCount();
      if (count <= 0)
        break;

      for (unsigned int i = 0; i < count; i++)
      {
        const ON_DimStyle* dim_style = m_archive_dim_style_table[i];
        if (nullptr == dim_style)
          continue;

        if (dim_style_id != dim_style->Id())
          continue;

        const ON_UUID parent_id = dim_style->ParentId();
        
        if (ON_nil_uuid == parent_id)
          continue;

        if (dim_style_id == parent_id)
          continue;

        if (ON_ModelComponent::Type::DimStyle != Manifest().ItemFromId(parent_id).ComponentType())
          continue;

        const ON_DimStyle* parent_ds = nullptr;
        for (unsigned int j = 0; j < count; j++)
        {
          const ON_DimStyle* archive_ds = m_archive_dim_style_table[j];
          if (nullptr == archive_ds)
            continue;
          if (parent_id != archive_ds->Id())
            continue;
          parent_ds = archive_ds;
          break;
        }

        if (nullptr == parent_ds)
          break;
        if (parent_ds->ParentIdIsNotNil())
          break;

        annotation.SetDimensionStyleId(parent_id);

        ON_DimStyle* override_candidate = new ON_DimStyle(*dim_style);
        override_candidate->ClearId();
        override_candidate->ClearIndex();
        override_candidate->ClearName();
        Internal_UpdateOverrideCandidateParentId(*this, override_candidate);
        annotation.SetOverrideDimensionStyle(override_candidate);
        if (nullptr != override_candidate)
        {
          // If this error occurs frequently, then we will comment out the call to ON_ERROR.
          ON_ERROR("Legacy override dimstyle information discarded.");
          delete override_candidate;
          break;
        }
        // update override_candidate settings.
        annotation.DimensionStyle(*parent_ds);
        break;
      }
      break;
    }

    return true;
  }

  // Read information written by ON_BinaryArchive::Internal_Write3dmDimStyleOverrides()
  int content_version = 0;
  if (false == BeginRead3dmAnonymousChunk(&content_version))
    return false;

  bool rc = false;
  for (;;)
  {
    bool bHasOverrideDimStyle = false;
    if (!ReadBool(&bHasOverrideDimStyle))
      break;

    if (bHasOverrideDimStyle)
    {
      // use archive.ReadObject() so user data will persist.
      ON_Object* ptr = nullptr;
      if (!ReadObject(&ptr))
        break;

      for (;;)
      {
        if (ON_nil_uuid == annotation.DimensionStyleId())
          break;
        ON_DimStyle* override_candidate = ON_DimStyle::Cast(ptr);
        if (nullptr == override_candidate)
          break;
        Internal_UpdateOverrideCandidateParentId(*this, override_candidate);
        if (false == annotation.IsOverrideDimStyleCandidate(override_candidate,true))
          break;
        annotation.SetOverrideDimensionStyle(override_candidate);
        ptr = override_candidate; // if annotation is managing override_candidate, then it is nullptr here.
        break;
      }
      if (nullptr != ptr)
        delete ptr;
    }

    rc = true;
    break;
  }

  if (!EndRead3dmChunk())
    rc = false;
  return rc;

}


bool ON_Annotation::Internal_WriteAnnotation(
  ON_BinaryArchive& archive
  ) const
{
  // content_version = 2 - added override dimstyle to ON_Annotation RH-37176
  // content_version = 3 -  added m_horizontal_direction
  // content_version = 4 -  added m_allow_text_scaling - Lowell
  const int content_version = 4;

  if (false == archive.BeginWrite3dmAnonymousChunk(content_version))
    return false;
  bool rc = false;
  for (;;)
  {
    const ON_TextContent* text_to_write = (nullptr != m_text) ? m_text : &ON_TextContent::Empty;

    if (false == text_to_write->Write(archive))
      break;

    if (!archive.WriteUuid(m_dimstyle_id))
      break;

    if (!archive.WritePlane(m_plane))
      break;

    // Added for content_version 1
    // Required to write/write linear dimensions and radial dimensions
    // because they have multiple possible values of m_annotation_type.
    unsigned int u = static_cast<unsigned char>(m_annotation_type);
    if (!archive.WriteInt(u))
      break;

    // Dale Lear 2016 Dec 12 https://mcneel.myjetbrains.com/youtrack/issue/RH-37176
    // content_version incremented to 2.
    if (!archive.Internal_Write3dmDimStyleOverrides(*this, m_override_dimstyle))
      break;

    // content_version = 3 ( 13 July, 2017 )
    if (!archive.WriteVector(m_horizontal_direction))
      break;

    // content_version = 4 ( 17 May, 2018 - Lowell)
    if (!archive.WriteBool(m_allow_text_scaling))
      break;

    rc = true;
    break;
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_Annotation::Internal_ReadAnnotation(
  ON_BinaryArchive& archive
  )
{
  Internal_Destroy();
  m_dimstyle_id = ON_nil_uuid;
  m_plane = ON_Plane::World_xy;
  // do not change the value of m_annotation_type
    
  int content_version = -1;
  if (false == archive.BeginRead3dmAnonymousChunk(&content_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (content_version < 0)
      break;
    
    ON_TextContent* text = new ON_TextContent;
    if (nullptr == text)
      break;
    if (false == text->Read(archive))
    {
      delete text;
      break;
    }
    m_text = text;

    if (!archive.Read3dmReferencedComponentId(ON_ModelComponent::Type::DimStyle, &m_dimstyle_id))
      break;

    if (!archive.ReadPlane(m_plane))
      break;

    if (content_version <= 0)
    {
      rc = true;
      break;
    }

    unsigned int u = 0;
    if (!archive.ReadInt(&u))
      break;
    const ON::AnnotationType annotation_type = ON::AnnotationTypeFromUnsigned(u);
    if (annotation_type != m_annotation_type)
    {
      const ON::AnnotationType annotation_type_pairs[3][2]
      {
        // ON_DimLinear linear dimensions can have type = Aligned or Rotated
        {ON::AnnotationType::Aligned,ON::AnnotationType::Rotated},

        // ON_DimRadial radial dimensions can have type = Diameter or Radius
        { ON::AnnotationType::Diameter,ON::AnnotationType::Radius },

        // ON_DimAngular radial dimensions can have type = Angular or Angular3pt
        { ON::AnnotationType::Angular,ON::AnnotationType::Angular3pt },
      };
      for (int pair_dex = 0; pair_dex < 3 && annotation_type != m_annotation_type; pair_dex++)
      {
        for (int k = 0; k < 2; k++)
        {
          if (
            annotation_type_pairs[pair_dex][k] == annotation_type
            && annotation_type_pairs[pair_dex][1-k] == m_annotation_type
            )
          {
            m_annotation_type = annotation_type;
            break;
          }
        }            
      }
      if (annotation_type != m_annotation_type)
      {
        ON_ERROR("Invalid annotation type.");
      }
    }

    // Dale Lear 2016 Dec 12 https://mcneel.myjetbrains.com/youtrack/issue/RH-37176
    // content_version incremented to 2.
    // optional override dimension style move from dimstyle table to annotation object
    const bool bFromDimStyleTable = content_version <= 1;
    if (!archive.Internal_Read3dmDimStyleOverrides(*this, bFromDimStyleTable))
      break;

    if (content_version <= 2)
    {
      rc = true;
      break;
    }

    // content_version = 3 ( 13 July, 2017 )
    if (!archive.ReadVector(m_horizontal_direction))
      break;

    if (content_version <= 3)
    {
      rc = true;
      break;
    }

    // content_version = 4 ( 17 May, 2018 - Lowell)
    if (!archive.ReadBool(&m_allow_text_scaling))
      break;

    rc = true;
    break;
  }
  if (!archive.EndRead3dmChunk())
    rc = false;

  return rc;
}

bool ON_Annotation::IsValid(ON_TextLog* text_log) const
{
  return (
    m_text->IsValid() 
    && m_plane.IsValid()
    );
}

bool ON_Annotation::GetTextXform(
  const ON_Xform* model_xform,
  const ON_Viewport* vp,
  const ON_DimStyle* dimstyle,
  double dimscale,
  ON_Xform& text_xform_out
) const
{
  const ON_Text* pText = ON_Text::Cast(this);
  if (nullptr != pText)
    return pText->GetTextXform(model_xform, vp, dimstyle, dimscale, text_xform_out);

  const ON_Leader* pLeader = ON_Leader::Cast(this);
  if (nullptr != pLeader)
    return pLeader->GetTextXform(model_xform, vp, dimstyle, dimscale, text_xform_out);

  const ON_DimLinear* pDimLinear = ON_DimLinear::Cast(this);
  if (nullptr != pDimLinear)
    return pDimLinear->GetTextXform(model_xform, vp, dimstyle, dimscale, text_xform_out);

  const ON_DimAngular* pDimAngular = ON_DimAngular::Cast(this);
  if (nullptr != pDimAngular)
    return pDimAngular->GetTextXform(model_xform, vp, dimstyle, dimscale, text_xform_out);

  const ON_DimRadial* pDimRadial = ON_DimRadial::Cast(this);
  if (nullptr != pDimRadial)
    return pDimRadial->GetTextXform(model_xform, vp, dimstyle, dimscale, text_xform_out);

  const ON_DimOrdinate* pDimOrdinate = ON_DimOrdinate::Cast(this);
  if (nullptr != pDimOrdinate)
    return pDimOrdinate->GetTextXform(model_xform, vp, dimstyle, dimscale, text_xform_out);

  const ON_Centermark* pCentermark = ON_Centermark::Cast(this);
  if (nullptr != pCentermark)
    return pCentermark->GetTextXform(vp, dimstyle, dimscale, text_xform_out);

  ON_ERROR("Annotation type not handled");
  return false;
}

void ON_Annotation::SetPlane(const ON_Plane& plane)
{
  m_plane = plane;
}

const ON_Plane& ON_Annotation::Plane() const
{
  return m_plane;
}

void ON_Annotation::SetHorizontalDirection(ON_2dVector horiz)
{
  if (horiz.Unitize())
    m_horizontal_direction = horiz;
}

const ON_2dVector ON_Annotation::HorizontalDirection() const
{
  return m_horizontal_direction;
}

ON_3dVector ON_Annotation::GetDefaultHorizontal(const ON_Plane& plane)
{
  double dx = plane.zaxis * ON_3dVector::XAxis;
  double dy = plane.zaxis * ON_3dVector::YAxis;
  double dz = plane.zaxis * ON_3dVector::ZAxis;

  ON_3dVector h3d = ON_3dVector::XAxis;
  if (fabs(dz) > fabs(dx) && fabs(dz) > fabs(dy))
    h3d = dz > 0.0 ? ON_3dVector::XAxis : -ON_3dVector::XAxis;
  else if (fabs(dx) > fabs(dy) && fabs(dx) > fabs(dz))
    h3d = dx > 0.0 ? ON_3dVector::YAxis : -ON_3dVector::YAxis;
  else if (fabs(dy) > fabs(dx) && fabs(dy) > fabs(dz))
    h3d = dy > 0.0 ? ON_3dVector::XAxis : -ON_3dVector::XAxis;

  ON_2dVector h2d;
  ON_3dPoint p = plane.origin + h3d;
  if (plane.ClosestPointTo(p, &h2d.x, &h2d.y) && h2d.Unitize())
  {
    p = plane.PointAt(h2d.x, h2d.y);
    h3d = p - plane.origin;
    if (h3d.Unitize())
      return h3d;
  }

  return ON_3dVector::XAxis;
}


void ON_Annotation::CalcTextFlip(
  const ON_3dVector& text_xdir, const ON_3dVector& text_ydir, const ON_3dVector& text_zdir,
  const ON_3dVector& view_xdir, const ON_3dVector& view_ydir, const ON_3dVector& view_zdir,
  const ON_Xform* model_xform,
  const double fliptol,
  bool& flip_x,
  bool& flip_y)
{

  double XoX = text_xdir * view_xdir;
  double XoY = text_xdir * view_ydir;
  double YoX = text_ydir * view_xdir;
  double YoY = text_ydir * view_ydir;
  bool from_the_back = (view_zdir * text_zdir < 0.0);
  if (nullptr != model_xform && model_xform->Determinant() < 0.0)
    from_the_back = !from_the_back;

  double upsign = 1.0;

  // This part shifts text to the correct side of the dimension line
  if (fabs(XoX) > fabs(XoY)) // more horizontal
  {
    if (YoY > 0.0)
      upsign = 1.0;
    else
      upsign = -1.0;
  }
  else  // more vertical
  {
    if (from_the_back)
    {
      if (YoX < 0.0)
      {
        if (XoX < fliptol)
          upsign = 1.0;
        else
          upsign = -1.0;
      }
      else
      {
        if (XoX > -fliptol)
          upsign = -1.0;
        else
          upsign = 1.0;
      }
    }
    else
    {
      if (YoX > 0.0)
      {
        if (XoX > fliptol)
          upsign = 1.0;
        else
          upsign = -1.0;
      }
      else
      {
        if (XoX < -fliptol)
          upsign = -1.0;
        else
          upsign = 1.0;
      }
    }
  }
  flip_x = false;
  flip_y = false;
  if (from_the_back)
    upsign = -upsign;
  flip_x = upsign < 0.0;
  if (from_the_back)
    flip_y = !flip_x;
  else
    flip_y = flip_x;
}


const ON_wString ON_Annotation::PlainText() const
{
  if (nullptr == m_text)
    return ON_wString::EmptyString;
  const ON_TextRunArray* runs = m_text->TextRuns(true);
  if (nullptr != runs && 0 == runs->Count())
    BoundingBox();  // Side effect of building text runs
  return m_text->PlainText();
}

const ON_wString ON_Annotation::PlainTextWithFields() const
{
  if (nullptr == m_text)
    return ON_wString::EmptyString;
  const ON_TextRunArray* runs = m_text->TextRuns(true);
  if (nullptr != runs && 0 == runs->Count())
    BoundingBox();
  return m_text->PlainTextWithFields();
}

const ON_wString  ON_Annotation::PlainTextWithFields(ON_SimpleArray<ON_3dex>* runmap) const
{
  if (nullptr == m_text)
    return ON_wString::EmptyString;
  const ON_TextRunArray* runs = m_text->TextRuns(true);
  if (nullptr != runs && 0 == runs->Count())
    BoundingBox();
  return m_text->PlainTextWithFields(runmap);
}


const ON_wString ON_Annotation::RichText() const
{
  return (nullptr == m_text)
    ? ON_wString::EmptyString
    : m_text->RichText();
}

ON_UUID ON_Annotation::DimensionStyleId() const
{
  return m_dimstyle_id;
}

void ON_Annotation::SetDimensionStyleId(ON_UUID dimstyle_id)
{
  const bool bKeepOverrides = false;
  SetDimensionStyleIdForExperts(dimstyle_id, bKeepOverrides);
}

void ON_Annotation::SetDimensionStyleId(
  const class ON_DimStyle& dim_style
)
{
  const ON_UUID dim_style_id
    = dim_style.ParentIdIsNil()
    ? dim_style.Id()
    : dim_style.ParentId();

  ON_DimStyle* override_dim_style
    = (ON_nil_uuid != dim_style_id
      && dim_style_id != dim_style.Id()
      && ON_Annotation::Internal_IsOverrideDimStyleCandidate(&dim_style, dim_style_id, true, false)
      )
    ? new ON_DimStyle(dim_style)
    : nullptr;

  // If dim_style parameter was the override on this class,
  // the next line will delete it.
  SetDimensionStyleId(dim_style_id);

  SetOverrideDimensionStyle(override_dim_style);
}


void ON_Annotation::SetDimensionStyleIdForExperts(
  ON_UUID dimstyle_id,
  bool bKeepOverrides
)
{
  if (bKeepOverrides)
  {
    if (ON_nil_uuid == dimstyle_id || nullptr == m_override_dimstyle)
      bKeepOverrides = false;
    else if (IsOverrideDimStyleCandidate(m_override_dimstyle,true))
      bKeepOverrides = m_override_dimstyle->SetParentId(dimstyle_id);
  }

  if (false == bKeepOverrides)
  {
    // This resets all overrides
    Internal_DeleteOverrideDimstyle();
  }

  m_dimstyle_id = dimstyle_id;
}

const ON_DimStyle& ON_Annotation::DimensionStyle(const ON_DimStyle& parent_dimstyle) const
{
  return DimensionStyle(parent_dimstyle, false);
}

const ON_DimStyle& ON_Annotation::DimensionStyle(
  const ON_DimStyle& parent_dimstyle,
  bool bForceOverrideUpdate
) const
{
  if (nullptr == m_override_dimstyle )
    return parent_dimstyle;

  if (false == m_override_dimstyle->HasOverrides())
  {
    Internal_DeleteOverrideDimstyle();
    return parent_dimstyle;
  }

  if (
    bForceOverrideUpdate
    || m_override_dimstyle->ParentId() != parent_dimstyle.Id() 
    || parent_dimstyle.ContentVersionNumber() != m_parent_dimstyle_content_version_number
    || m_override_dimstyle->ParentContentHash() != parent_dimstyle.ContentHash()
    )
  {
    // update m_override_dimstyle if parent content has changed.
    m_override_dimstyle->OverrideFields(*m_override_dimstyle, parent_dimstyle);
    if (false == m_override_dimstyle->HasOverrides())
    {
      // Updating overrides unsets all overrides that match parent values.
      // When this happens, the overrides are deleted here.
      Internal_DeleteOverrideDimstyle();
      return parent_dimstyle;
    }
    m_parent_dimstyle_content_version_number = parent_dimstyle.ContentVersionNumber();
  }

  return *m_override_dimstyle;
}

bool ON_Annotation::IsOverrideStylePointer(
  const ON_DimStyle* ptr
) const
{
  return (nullptr != ptr && ptr == m_override_dimstyle);
}

bool ON_Annotation::AllowTextScaling() const
{
  // These functions are being added to continue the V5 behavior of
  // per-object text scaling. There is no user interface
  // in V6 or V7 that shows this setting or that allows a user
  // to change this setting.
  // AllowTextScaling() = false means the effective dimstyle value 
  // of DimScale() (model space scale factor) is ignored (treated as if it were 1).
  return m_allow_text_scaling;
}

void ON_Annotation::SetAllowTextScaling(bool scale)
{
  // These functions are being added to continue the V5 behavior of
  // per-object text scaling. There is no user interface
  // in V6 or V7 that shows this setting or that allows a user
  // to change this setting.
  // AllowTextScaling() = false means the effective dimstyle value 
  // of DimScale() (model space scale factor) is ignored (treated as if it were 1).
  if (scale != m_allow_text_scaling)
  {
    m_allow_text_scaling = scale ? true : false;
    ClearBoundingBox();
  }
}

bool ON_Annotation::IsOverrideDimStyleCandidate(
  const ON_DimStyle* override_style_candidate,
  bool bRequireSetOverrides
) const
{
  const bool bIssueErrorsAndWarnings = false;
  return Internal_IsOverrideDimStyleCandidate(override_style_candidate, m_dimstyle_id, bRequireSetOverrides, bIssueErrorsAndWarnings);
}

bool ON_DimStyle::IsOverrideDimStyleCandidate(
  ON_UUID parent_id,
  bool bRequireSetOverrides,
  ON_wString* error_description
) const
{
  if (bRequireSetOverrides)
  {
    if (false == this->HasOverrides())
    {
      if (error_description)
      {
        *error_description = "this->HasOverrides() is false.";
      }
      return false;
    }
  }

  if (this->IsDeleted())
  {
    if (error_description)
    {
      *error_description = "override style parameter is marked as deleted.";
    }
    return false;
  }

  const ON_UUID candidate_parent_id = this->ParentId();
  if (ON_nil_uuid == candidate_parent_id)
  {
    if (this->ParentIdIsLocked())
    {
      if (error_description)
      {  
        *error_description = "override style parent id is nil and locked.";
      }
      return false;
    }
  }
  else if (candidate_parent_id != parent_id)
  {
    if (error_description)
    {
      *error_description = "override style parent id is incorrectly set.";
    }
    return false;
  }
  
  if ( this->IdIsNotNil() )
  {
    if (error_description)
    {
      *error_description = "override style id is not nil.";
    }
    return false;
  }

  if ( this->NameIsNotEmpty() )
  {
    if (error_description)
    {
      *error_description = "override style name is not empty.";
    }
    return false;
  }
    
  if ( ON_ModelComponent::Unset.Index() != this->Index() )
  {
    if (error_description)
    {
      *error_description = "override style index is not unset index.";
    }
    return false;
  }

  return true;  
}


bool ON_Annotation::Internal_IsOverrideDimStyleCandidate(
  const ON_DimStyle* override_style_candidate,
  ON_UUID parent_id,
  bool bRequireSetOverrides,
  bool bIssueErrorsAndWarnings
)
{
  if (nullptr == override_style_candidate)
  {
    if (bIssueErrorsAndWarnings)
    {
      ON_ERROR("override_style_candidate is nullptr.");
    }
    return false;
  }

  ON_wString error_description;
  bool rc = override_style_candidate->IsOverrideDimStyleCandidate(
    parent_id,
    bRequireSetOverrides,
    (bIssueErrorsAndWarnings ? &error_description : nullptr)
  );
  if (false == rc && bIssueErrorsAndWarnings)
  {
    error_description.TrimLeftAndRight();
    ON_String utf8_error_description = error_description;
    utf8_error_description.TrimLeftAndRight();
    if (utf8_error_description.IsEmpty())
    {
      ON_ERROR("override_style_candidate is not a valid override candidate.");
    }
    else
    {
      ON_ERROR(utf8_error_description);
    }
  }

  return true;  
}

void ON_Annotation::ClearOverrideDimensionStyle()
{
  Internal_DeleteOverrideDimstyle();
}

/*
Description:
  If this->IsOverrideDimStyleCandidate(override_style_candidate,bRequireSetOverrides)
  is true, then a managed copy of override_style_candidate is set as an override.
Returns:
  True if an override is set.
*/
bool ON_Annotation::SetOverrideDimensionStyle(
  const ON_DimStyle* override_style_candidate,
  bool bRequireSetOverrides
)
{
  bool rc;

  if (nullptr == override_style_candidate)
  {
    ClearOverrideDimensionStyle();
    rc = true;
  }
  else if ( IsOverrideDimStyleCandidate(override_style_candidate, bRequireSetOverrides) )
  {
    ON_DimStyle* managed_override_style = new ON_DimStyle(*override_style_candidate);
    rc = SetOverrideDimensionStyle(managed_override_style);
    if (managed_override_style != m_override_dimstyle)
    {
      delete managed_override_style;
      rc = false;
    }
  }
  else
  {
    // invalid override candidate
    rc = false;
  }

  return rc;
}

bool ON_Annotation::SetOverrideDimensionStyle(ON_DimStyle*& override_style) const
{
  if (nullptr != m_override_dimstyle && m_override_dimstyle == override_style)
  {
    // The caller is very confused.
    // override_style is already managed by this ON_Annotation instance.
    // Going further will cause a crash.
    // This is a serious error caused by a serious bug in the calling code.
    ON_ERROR("m_override_dimstyle = override_style");
    override_style = nullptr;
    return false;
  }
  Internal_DeleteOverrideDimstyle();

  // handle simple cases of "clearing overrides" first.
  if (nullptr == override_style)
    return true;

  if (ON_nil_uuid == m_dimstyle_id)
  {
    // ON_ERROR automatically fills in function name and new lines when needed.
    //ON_ERROR("SetOverrideDimensionStyle(): this->m_dimstyle_id must be non-nil to override a dimstyle.\n");
    ON_ERROR("this->m_dimstyle_id must be non-nil to override a dimstyle.");
    return false;
  }

  // Do not require overrides to be set. Some workflows add dimstyle with no overrides set and then
  // modify that dimstyle.

  //if (false == override_style->HasOverrides())
  //{
  //  // skip detailed validation steps that don't matter.
  //  delete override_style;
  //  return true;
  //}

  const ON_UUID candidate_parent_id
    = override_style->ParentIdIsNil()
    ? ON_nil_uuid
    : m_dimstyle_id;
  const bool bRequireSetOverrides = false;
  const bool bIssueErrorsAndWarnings = true;
  if (false == ON_Annotation::Internal_IsOverrideDimStyleCandidate(override_style, candidate_parent_id, bRequireSetOverrides, bIssueErrorsAndWarnings) )
  {
    // invalid override_style
    return false;
  }

  if (false == override_style->SetParentId(m_dimstyle_id) || m_dimstyle_id != override_style->ParentId())
  {
    ON_ERROR("override_style->SetParentId(this->m_dimstyle_id) failed.");
    return false;
  }

  // override_style's must have unset id (= nil), unset index = (ON_UNSET_INT_INDEX), unset name (empty)
  override_style->ClearId();
  override_style->LockId();

  override_style->ClearName();
  override_style->LockName();

  override_style->ClearIndex();
  override_style->LockIndex(); 

  m_override_dimstyle = override_style;
  override_style = nullptr;

  return true;
}

bool ON_Annotation::HasDimensionStyleOverrides() const
{
  return (nullptr != m_override_dimstyle && m_override_dimstyle->HasOverrides());
}

void ON_Annotation::Internal_DeleteOverrideDimstyle() const
{
  if (nullptr != m_override_dimstyle)
  {
    delete m_override_dimstyle;
    m_override_dimstyle = nullptr;
  }
  m_parent_dimstyle_content_version_number = 0;  
}

const ON_TextContent* ON_Annotation::Text() const
{
  return m_text;
}

ON_TextContent* ON_Annotation::Text()
{
  return m_text;
}

void ON_Annotation::SetText(ON_TextContent*& text) const
{
  if (text == m_text)
    return;
  ClearText();
  m_text = text;
  text = nullptr;
}

void ON_Annotation::ClearText() const
{
  if (nullptr != m_text)
  {
    delete m_text;
    m_text = nullptr;
  }
}

double ON_Annotation::TextRotationRadians() const
{
  double ang = 0.0;
  const ON_TextContent* text = Text();
  if (nullptr != text)
  {
    ang = text->TextRotationRadians();
  }
  return ang;
}

void ON_Annotation::SetTextRotationRadians(double rotation)
{
  ON_TextContent* text = Text();
  if (nullptr != text)
  {
    text->SetTextRotationRadians(rotation);
  }
}

double ON_Annotation::TextRotationDegrees() const
{
  double a = TextRotationRadians();
  return a * ON_RADIANS_TO_DEGREES;
}

void ON_Annotation::SetTextRotationDegrees(double rotation)
{
  double a = rotation * ON_DEGREES_TO_RADIANS;
  SetTextRotationRadians(a);
}

ON_SHA1_Hash ON_Annotation::DimStyleTextPositionPropertiesHash() const
{
  const ON_TextContent* text = Text();
  return
    (nullptr == text)
    ? ON_TextContent::Empty.DimStyleTextPositionPropertiesHash()
    : text->DimStyleTextPositionPropertiesHash();
}

bool ON_Annotation::EqualTextPositionProperties(
  const class ON_DimStyle* dimstyle
) const
{
  const ON_TextContent* text = Text();
  return
    (nullptr == text)
    ? (ON_DimStyle::DimStyleOrDefault(dimstyle).TextPositionPropertiesHash() == DimStyleTextPositionPropertiesHash())
    : text->EqualTextPositionProperties( Type(), dimstyle );
}

static bool DimstyleHasMask(const ON_DimStyle* dimstyle)
{
  return (nullptr == dimstyle || dimstyle->DrawTextMask() || dimstyle->MaskFrameType() != ON_TextMask::MaskFrame::NoFrame);
}

const ON_SHA1_Hash ON_Annotation::Internal_GetBBox_InputHash(
  const ON_Viewport* vp,
  const ON_DimStyle* dimstyle,
  double dimscale,
  const ON_2dPoint& text_point,
  unsigned int point_count,
  const ON_2dPoint* points
) const
{
  ON_SHA1 sha1;
  if (nullptr != vp)
    sha1.AccumulateSubHash(vp->ViewProjectionContentHash());
  if ( nullptr != dimstyle )
    sha1.AccumulateSubHash(dimstyle->ContentHash());
  sha1.AccumulateDouble(dimscale);
  
  sha1.Accumulate3dVector(m_plane.xaxis);
  sha1.Accumulate3dVector(m_plane.yaxis);
  sha1.Accumulate3dVector(m_plane.zaxis);
  sha1.AccumulateDoubleArray(4,&m_plane.plane_equation.x);

  if (nullptr != m_text)
  {
    // This return ON_TextContent.m_mbox
    // which is a cached value
    const ON_BoundingBox textbbox = m_text->BoundingBox();
    sha1.AccumulateBoundingBox(textbbox);
    if (textbbox.IsNotEmpty() && DimstyleHasMask(dimstyle))
    {
      sha1.AccumulateDouble(dimstyle->MaskBorder());
    }
  }

  sha1.Accumulate2dPoint(text_point);
  sha1.AccumulateUnsigned32(point_count);
  if (point_count > 0 && nullptr != points)
    sha1.AccumulateDoubleArray(2 * point_count, &points[0].x);

  return sha1.Hash();
}

bool ON_Annotation::Internal_GetBBox_TextGlyphBox(
  const ON_Viewport* vp,
  const ON_DimStyle* dimstyle,
  double dimscale,
  ON_BoundingBox& text_glyph_box
) const
{
  text_glyph_box = ON_BoundingBox::UnsetBoundingBox;
  if (m_text)
  {
    ON_Xform txf;
    // 20 June 2017 S. Baer (RH-39835)
    // GetTextXform can change cached information. Make sure this
    // is called before m_text->BoundingBox()
    // 23 June, 2020 - Lowell - Moved it above m_text->BoundingBox()
    bool b = GetTextXform(vp, dimstyle, dimscale, txf);

    text_glyph_box = m_text->BoundingBox();

    // if mask, grow 2d bbox
    if (text_glyph_box.IsNotEmpty() && DimstyleHasMask(dimstyle))
    {
      ON_3dPoint bmin = text_glyph_box.Min();
      ON_3dPoint bmax = text_glyph_box.Max();
      double d = dimstyle->MaskBorder();
      bmin.x -= d;
      bmin.y -= d;
      bmax.x += d;
      bmax.y += d;
      text_glyph_box.m_min = bmin;
      text_glyph_box.m_max = bmax;
    }

    if (b)
    {
      text_glyph_box.Transform(txf);
    }
  }
  return text_glyph_box.IsNotEmpty();
}

bool ON_Annotation::Internal_GetBBox_Begin(
  const ON_SHA1_Hash& hash,
  double* boxmin,
  double* boxmax,
  bool bGrow
) const
{
  ON_BoundingBox bbox = ON_BoundingBox::NanBoundingBox;
  if (nullptr != boxmin && nullptr != boxmax)
  {
    if (bGrow)
    {
      bbox.m_min = ON_3dPoint(boxmin);
      bbox.m_max = ON_3dPoint(boxmax);
      bGrow = bbox.IsNotEmpty();
    }
    if (false == bGrow)
      bbox = ON_BoundingBox::EmptyBoundingBox;
    ON_BoundingBox cached_bbox;
    const bool rc = m_bbox_cache.GetBoundingBox(hash, cached_bbox);
    if (rc)
    {
      if (bGrow)
        bbox.Union(cached_bbox);
      else
        bbox = cached_bbox;
    }
    boxmin[0] = bbox.m_min.x;
    boxmin[1] = bbox.m_min.y;
    boxmin[2] = bbox.m_min.z;
    boxmax[0] = bbox.m_max.x;
    boxmax[1] = bbox.m_max.y;
    boxmax[2] = bbox.m_max.z;
    return rc;
  }

  if (nullptr != boxmin)
  {
    boxmin[0] = boxmin[1] = boxmin[2] = ON_DBL_QNAN;
  }
  if (nullptr != boxmax)
  {
    boxmax[0] = boxmax[1] = boxmax[2] = ON_DBL_QNAN;
  }

  return false;
}

bool ON_Annotation::Internal_GetBBox_End(
    const ON_BoundingBox& bbox,
    const ON_SHA1_Hash& hash,
    double* boxmin,
    double* boxmax,
    bool bGrow
) const
{
  if (bbox.IsNotEmpty())
  {
    m_bbox_cache.AddBoundingBox(bbox, hash);
  }

  ON_BoundingBox box_out = bbox;
  if (bGrow && nullptr != boxmin && nullptr != boxmax )
  {
    ON_BoundingBox box_in;
    box_in.m_min = ON_3dPoint(boxmin);
    box_in.m_max = ON_3dPoint(boxmax);
    if (box_in.IsNotEmpty())
      box_out.Union(box_in);
  }

  if (nullptr != boxmin)
  {
    boxmin[0] = box_out.m_min.x;
    boxmin[1] = box_out.m_min.y;
    boxmin[2] = box_out.m_min.z;
  }
  if (nullptr != boxmax)
  {
    boxmax[0] = box_out.m_max.x;
    boxmax[1] = box_out.m_max.y;
    boxmax[2] = box_out.m_max.z;
  }

  return box_out.IsNotEmpty();
}

const wchar_t* ON_Annotation::RtfText() const
{
  const ON_TextContent* text = Text();
  if (nullptr == text)
    return nullptr;
  return text->RtfText();
}

bool ON_Annotation::ReplaceTextString(
  const wchar_t* RtfString,
  const ON_DimStyle* dimstyle
)
{
  ON_TextContent* text = Text();
  if (nullptr == text)
  {
    text = new ON_TextContent;
    if (nullptr == text)
      return true;
    SetText(text);
    text = Text();
    if (nullptr == text)
      return true;
  }
  ON_Dimension* dim = ON_Dimension::Cast(this);
  if (nullptr != dim)
  {
    dim->SetUserText(RtfString);
    dim->ClearText();
    return true;
  }
  else
    return text->ReplaceTextString(RtfString, Type(), dimstyle);
}


bool ON_Annotation::RunReplaceString(
  const ON_DimStyle* dimstyle,
  const wchar_t* repl_str,
  int start_run_idx,
  int start_run_pos,
  int end_run_idx,
  int end_run_pos)
{
  ON_TextContent* text_content = Text();
  if (nullptr == text_content)
    return false;
  bool rc = text_content->RunReplaceString(repl_str, start_run_idx, start_run_pos, end_run_idx, end_run_pos);

  text_content->ComposeText();
  
  text_content->RebuildRuns(Type(), dimstyle);

  
  return rc;
}


////double ON_Annotation::Height() const
////{
////  //// Delete this function ASAP
////  //// TextHeight is on ON_DimStyle
////  return ON_DimStyle::Default.TextHeight();
////  //const ON_TextContent* text = Text();
////  //if (nullptr == text)
////  //  return 1.0;
////  //return text->Height();
////}
////void ON_Annotation::SetHeight(double height)
////{
////  //// Delete this function ASAP
////  //// TextHeight is on ON_DimStyle
////  //ON_TextContent* text = Text();
////  //if (nullptr != text)
////  //  text->SetHeight(height);
////}

void ON_Annotation::GetAlignment(ON::TextHorizontalAlignment& horz, ON::TextVerticalAlignment& vert) const
{
  const ON_TextContent* text = Text();
  if (nullptr == text)
  {
    horz = ON::TextHorizontalAlignment::Left;
    vert = ON::TextVerticalAlignment::Top;
  }
  else
  {
    text->GetAlignment(horz, vert);
  }
}

void ON_Annotation::SetAlignment(ON::TextHorizontalAlignment horz, ON::TextVerticalAlignment vert)
{
  ON_TextContent* text = Text();
  if (nullptr != text)
    text->SetAlignment(horz, vert);
}

double ON_Annotation::FormattingRectangleWidth() const
{
  const ON_TextContent* text = Text();
  if (nullptr != text)
    return text->FormattingRectangleWidth();
  return 1.0e300;
}

void ON_Annotation::SetFormattingRectangleWidth(double width)
{
  ON_TextContent* text = Text();
  if (nullptr != text)
    text->SetFormattingRectangleWidth(width);
}

bool ON_Annotation::GetText3dCorners(ON_3dPoint corners[4]) const
{
  if (nullptr == corners)
    return false;
  const ON_TextContent* text_geom = Text();
  if (nullptr == text_geom)
    return false;
  return text_geom->Get3dCorners(corners);
}




//// ------------------ new overrides

bool ON_Annotation::Internal_DimStyleDoubleChanged(
  const double current_value,
  double candidate_value
)
{
  const double tol = ON_EPSILON * current_value;
  const double delta = fabs(current_value - candidate_value);
  return (delta > tol);
}


const ON_DimStyle& ON_Annotation::Internal_StyleForFieldQuery(
  const ON_DimStyle* parent_style,
  ON_DimStyle::field field_id
) const
{
  if (
    nullptr != m_override_dimstyle
    && m_override_dimstyle->IsFieldOverride(field_id)
    )
  {
    // There is an override style and this particular field value is overridden.
    return *m_override_dimstyle;
  }

  if (nullptr != parent_style)
  {
    // Even when there is an override style, it's contents may not be up to date
    // with the parent style. That's why we check m_override_dimstyle->IsFieldOverride(field_id)
    // above before returning m_override_dimstyle.
    return *parent_style;
  }

  // returning the m_override_dimstyle style here is done because 
  // there is some chance it will be up to date and its contents
  // are more applicable than the default settings.
  if (nullptr != m_override_dimstyle)
    return *m_override_dimstyle;

  // This is not a good situation. It means the developer could not get a parent
  // style from the context of the query.
  return ON_DimStyle::Default;
}


ON_DimStyle* ON_Annotation::Internal_GetOverrideStyle(bool bCreateIfNull) const
{
  if (nullptr == m_override_dimstyle && bCreateIfNull)
  {
    ON_DimStyle* style = new ON_DimStyle;
    SetOverrideDimensionStyle(style);
  }
  return m_override_dimstyle;
}

bool ON_Annotation::FieldIsOverridden(ON_DimStyle::field field) const
{
  ON_DimStyle* override_style = Internal_GetOverrideStyle(false);
  if (nullptr == override_style)
    return false;
  return override_style->IsFieldOverride(field);
}

void ON_Annotation::ClearFieldOverride(ON_DimStyle::field field)
{
  ON_DimStyle* override_style = Internal_GetOverrideStyle(false);
  if (nullptr != override_style)
  {
    override_style->SetFieldOverride(field, false);
    if (!override_style->HasOverrides())
    {
      // Delete the override style if that was the last overridden field
      ON_DimStyle* nullstyle = nullptr;
      SetOverrideDimensionStyle(nullstyle);
    }
  }
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////

double ON_Annotation::ExtensionLineExtension(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ExtensionLineExtension).ExtExtension();
}

void ON_Annotation::SetExtensionLineExtension(const ON_DimStyle* parent_style, double extension)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(extension, parent_style->ExtExtension());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetExtExtension(extension);
    override_style->SetFieldOverride(ON_DimStyle::field::ExtensionLineExtension, bCreate);
  }
}

double ON_Annotation::ExtensionLineOffset(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ExtensionLineOffset).ExtOffset();
}

void ON_Annotation::SetExtensionLineOffset(const ON_DimStyle* parent_style, double offset)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(offset, parent_style->ExtOffset());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetExtOffset(offset);
    override_style->SetFieldOverride(ON_DimStyle::field::ExtensionLineOffset, bCreate);
  }
}

double ON_Annotation::ArrowSize(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::Arrowsize).ArrowSize();
}

void ON_Annotation::SetArrowSize(const ON_DimStyle* parent_style, double size)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(size, parent_style->ArrowSize());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetArrowSize(size);
    override_style->SetFieldOverride(ON_DimStyle::field::Arrowsize, bCreate);
  }
}

double ON_Annotation::LeaderArrowSize(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderArrowsize).LeaderArrowSize();
}

void ON_Annotation::SetLeaderArrowSize(const ON_DimStyle* parent_style, double size)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(size, parent_style->LeaderArrowSize());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderArrowSize(size);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderArrowsize, bCreate);
  }
}

double ON_Annotation::CenterMarkSize(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::Centermark).CenterMark();
}

void ON_Annotation::SetCenterMarkSize(const ON_DimStyle* parent_style, double size)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(size, parent_style->CenterMark());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetCenterMark(size);
    override_style->SetFieldOverride(ON_DimStyle::field::Centermark, bCreate);
  }
}

ON_DimStyle::centermark_style ON_Annotation::CenterMarkStyle(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::CentermarkStyle).CenterMarkStyle();
}

void ON_Annotation::SetCenterMarkStyle(const ON_DimStyle* parent_style, ON_DimStyle::centermark_style style)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (style != parent_style->CenterMarkStyle());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetCenterMarkStyle(style);
    override_style->SetFieldOverride(ON_DimStyle::field::CentermarkStyle, bCreate);
  }
}

ON_DimStyle::TextLocation ON_Annotation::DimTextLocation(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::DimTextLocation).DimTextLocation();
}

void ON_Annotation::SetDimTextLocation(const ON_DimStyle* parent_style, ON_DimStyle::TextLocation text_location)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (text_location != parent_style->DimTextLocation());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDimTextLocation(text_location);
    override_style->SetFieldOverride(ON_DimStyle::field::DimTextLocation, bCreate);
  }
}

ON_DimStyle::TextLocation ON_Annotation::DimRadialTextLocation(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::DimRadialTextLocation).DimRadialTextLocation();
}

void ON_Annotation::SetDimRadialTextLocation(const ON_DimStyle* parent_style, ON_DimStyle::TextLocation text_location)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (text_location != parent_style->DimRadialTextLocation());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDimRadialTextLocation(text_location);
    override_style->SetFieldOverride(ON_DimStyle::field::DimRadialTextLocation, bCreate);
  }
}

ON_DimStyle::angle_format ON_Annotation::AngleFormat(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AngleFormat).AngleFormat();
}

void ON_Annotation::SetAngleFormat(const ON_DimStyle* parent_style, ON_DimStyle::angle_format format)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (format != parent_style->AngleFormat());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAngleFormat(format);
    override_style->SetFieldOverride(ON_DimStyle::field::AngleFormat, bCreate);
  }
}

int ON_Annotation::LengthResolution(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LengthResolution).LengthResolution();
}

void ON_Annotation::SetLengthResolution(const ON_DimStyle* parent_style, int resolution)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (resolution != parent_style->LengthResolution());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLengthResolution(resolution);
    override_style->SetFieldOverride(ON_DimStyle::field::LengthResolution, bCreate);
  }
}

int ON_Annotation::AngleResolution(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AngleResolution).AngleResolution();
}

void ON_Annotation::SetAngleResolution(const ON_DimStyle* parent_style, int resolution)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (resolution != parent_style->AngleResolution());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAngleResolution(resolution);
    override_style->SetFieldOverride(ON_DimStyle::field::AngleResolution, bCreate);
  }
}

double ON_Annotation::TextGap(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::TextGap).TextGap();
}

void ON_Annotation::SetTextGap(const ON_DimStyle* parent_style, double gap)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(gap, parent_style->TextGap());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetTextGap(gap);
    override_style->SetFieldOverride(ON_DimStyle::field::TextGap, bCreate);
  }
}

double ON_Annotation::TextHeight(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::TextHeight).TextHeight();
}

void ON_Annotation::SetTextHeight(const ON_DimStyle* parent_style, double height)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(height, parent_style->TextHeight());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetTextHeight(height);
    override_style->SetFieldOverride(ON_DimStyle::field::TextHeight, bCreate);
  }
}

double ON_Annotation::LengthFactor(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LengthFactor).LengthFactor();
}

void ON_Annotation::SetLengthFactor(const ON_DimStyle* parent_style, double factor)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(factor, parent_style->LengthFactor());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLengthFactor(factor);
    override_style->SetFieldOverride(ON_DimStyle::field::LengthFactor, bCreate);
  }
}

bool ON_Annotation::Alternate(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::Alternate).Alternate();
}

void ON_Annotation::SetAlternate(const ON_DimStyle* parent_style, bool alternate)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (alternate != parent_style->Alternate());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAlternate(alternate);
    override_style->SetFieldOverride(ON_DimStyle::field::Alternate, bCreate);
  }
}

double ON_Annotation::AlternateLengthFactor(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AlternateLengthFactor).AlternateLengthFactor();
}

void ON_Annotation::SetAlternateLengthFactor(const ON_DimStyle* parent_style, double factor)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(factor, parent_style->AlternateLengthFactor());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAlternateLengthFactor(factor);
    override_style->SetFieldOverride(ON_DimStyle::field::AlternateLengthFactor, bCreate);
  }
}

int ON_Annotation::AlternateLengthResolution(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AlternateLengthResolution).AlternateLengthResolution();
}

void ON_Annotation::SetAlternateLengthResolution(const ON_DimStyle* parent_style, int resolution)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (resolution != parent_style->AlternateLengthResolution());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAlternateLengthResolution(resolution);
    override_style->SetFieldOverride(ON_DimStyle::field::AlternateLengthResolution, bCreate);
  }
}

const wchar_t* ON_Annotation::Prefix(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::Prefix).Prefix();
}

void ON_Annotation::SetPrefix(const ON_DimStyle* parent_style, const wchar_t* prefix)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = !ON_wString::EqualOrdinal(prefix, parent_style->Prefix(), false);
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetPrefix(prefix);
    override_style->SetFieldOverride(ON_DimStyle::field::Prefix, bCreate);
  }
}

const wchar_t* ON_Annotation::Suffix(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::Suffix).Suffix();
}

void ON_Annotation::SetSuffix(const ON_DimStyle* parent_style, const wchar_t* suffix)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = !ON_wString::EqualOrdinal(suffix, parent_style->Suffix(), false);
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetSuffix(suffix);
    override_style->SetFieldOverride(ON_DimStyle::field::Suffix, bCreate);
  }
}

const wchar_t* ON_Annotation::AlternatePrefix(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AlternatePrefix).AlternatePrefix();
}

void ON_Annotation::SetAlternatePrefix(const ON_DimStyle* parent_style, const wchar_t* prefix)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = !ON_wString::EqualOrdinal(prefix, parent_style->Prefix(), false);
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAlternatePrefix(prefix);
    override_style->SetFieldOverride(ON_DimStyle::field::AlternatePrefix, bCreate);
  }
}

const wchar_t* ON_Annotation::AlternateSuffix(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AlternateSuffix).AlternateSuffix();
}

void ON_Annotation::SetAlternateSuffix(const ON_DimStyle* parent_style, const wchar_t* suffix)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = !ON_wString::EqualOrdinal(suffix, parent_style->Suffix(), false);
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAlternateSuffix(suffix);
    override_style->SetFieldOverride(ON_DimStyle::field::AlternateSuffix, bCreate);
  }
}

bool ON_Annotation::SuppressExtension1(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::SuppressExtension1).SuppressExtension1();
}

void ON_Annotation::SetSuppressExtension1(const ON_DimStyle* parent_style, bool suppress)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (suppress != parent_style->SuppressExtension1());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetSuppressExtension1(suppress);
    override_style->SetFieldOverride(ON_DimStyle::field::SuppressExtension1, bCreate);
  }
}

bool ON_Annotation::SuppressExtension2(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::SuppressExtension2).SuppressExtension2();
}

void ON_Annotation::SetSuppressExtension2(const ON_DimStyle* parent_style, bool suppress)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (suppress != parent_style->SuppressExtension2());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetSuppressExtension2(suppress);
    override_style->SetFieldOverride(ON_DimStyle::field::SuppressExtension2, bCreate);
  }
}

double ON_Annotation::DimExtension(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::DimensionLineExtension).DimExtension();
}

void ON_Annotation::SetDimExtension(const ON_DimStyle* parent_style, double extension)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(extension, parent_style->DimExtension());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDimExtension(extension);
    override_style->SetFieldOverride(ON_DimStyle::field::DimensionLineExtension, bCreate);
  }
}

ON_DimStyle::tolerance_format ON_Annotation::ToleranceFormat(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ToleranceFormat).ToleranceFormat();
}

void ON_Annotation::SetToleranceFormat(const ON_DimStyle* parent_style, ON_DimStyle::tolerance_format format)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (format != parent_style->ToleranceFormat());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetToleranceFormat(format);
    override_style->SetFieldOverride(ON_DimStyle::field::ToleranceFormat, bCreate);
  }
}

int ON_Annotation::ToleranceResolution(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ToleranceResolution).ToleranceResolution();
}

void ON_Annotation::SetToleranceResolution(const ON_DimStyle* parent_style, int resolution)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (resolution != parent_style->ToleranceResolution());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetToleranceResolution(resolution);
    override_style->SetFieldOverride(ON_DimStyle::field::ToleranceResolution, bCreate);
  }
}

double ON_Annotation::ToleranceUpperValue(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ToleranceUpperValue).ToleranceUpperValue();
}

void ON_Annotation::SetToleranceUpperValue(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->ToleranceUpperValue());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetToleranceUpperValue(value);
    override_style->SetFieldOverride(ON_DimStyle::field::ToleranceUpperValue, bCreate);
  }
}

double ON_Annotation::ToleranceLowerValue(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ToleranceLowerValue).ToleranceLowerValue();
}

void ON_Annotation::SetToleranceLowerValue(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->ToleranceLowerValue());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetToleranceLowerValue(value);
    override_style->SetFieldOverride(ON_DimStyle::field::ToleranceLowerValue, bCreate);
  }
}

double ON_Annotation::ToleranceHeightScale(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ToleranceHeightScale).ToleranceHeightScale();
}

void ON_Annotation::SetToleranceHeightScale(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->ToleranceHeightScale());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetToleranceHeightScale(value);
    override_style->SetFieldOverride(ON_DimStyle::field::ToleranceHeightScale, bCreate);
  }
}

double ON_Annotation::BaselineSpacing(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::BaselineSpacing).BaselineSpacing();
}

void ON_Annotation::SetBaselineSpacing(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->BaselineSpacing());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetBaselineSpacing(value);
    override_style->SetFieldOverride(ON_DimStyle::field::BaselineSpacing, bCreate);
  }
}

bool ON_Annotation::DrawTextMask(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::DrawMask).DrawTextMask();
}

void ON_Annotation::SetDrawTextMask(const ON_DimStyle* parent_style, bool value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->DrawTextMask());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDrawTextMask(value);
    override_style->SetFieldOverride(ON_DimStyle::field::DrawMask, bCreate);
  }
}

ON_TextMask::MaskType ON_Annotation::MaskFillType(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::MaskColorSource).MaskFillType();
}

void ON_Annotation::SetMaskFillType(const ON_DimStyle* parent_style, ON_TextMask::MaskType value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->MaskFillType());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetMaskFillType(value);
    override_style->SetFieldOverride(ON_DimStyle::field::MaskColorSource, bCreate);
  }
}

ON_TextMask::MaskFrame ON_Annotation::MaskFrameType(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::MaskFrameType).MaskFrameType();
}

void ON_Annotation::SetMaskFrameType(const ON_DimStyle* parent_style, ON_TextMask::MaskFrame value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->MaskFrameType());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetMaskFrameType(value);
    override_style->SetFieldOverride(ON_DimStyle::field::MaskFrameType, bCreate);
  }
}

ON_Color ON_Annotation::MaskColor(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::MaskColor).MaskColor();
}

void ON_Annotation::SetMaskColor(const ON_DimStyle* parent_style, ON_Color value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->MaskColor());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetMaskColor(value);
    override_style->SetFieldOverride(ON_DimStyle::field::MaskColor, bCreate);
  }
}

double ON_Annotation::MaskBorder(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::MaskBorder).MaskBorder();
}

void ON_Annotation::SetMaskBorder(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->MaskBorder());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetMaskBorder(value);
    override_style->SetFieldOverride(ON_DimStyle::field::MaskBorder, bCreate);
  }
}

void ON_Annotation::SetTextMask(const ON_DimStyle* parent_style, const ON_TextMask& mask)
{
  // In order for overrides to work correctly, each text mask property must be
  // set individually.
  const ON_TextMask local_mask(mask);
  SetDrawTextMask(parent_style, local_mask.DrawTextMask());
  SetMaskColor(parent_style, local_mask.MaskColor());
  SetMaskFillType(parent_style, local_mask.MaskFillType());
  SetMaskBorder(parent_style, local_mask.MaskBorder());
  SetMaskFrameType(parent_style, local_mask.MaskFrameType());
}

double ON_Annotation::FixedExtensionLength(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::FixedExtensionLength).FixedExtensionLen();
}

void ON_Annotation::SetFixedExtensionLength(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->FixedExtensionLen());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetFixedExtensionLen(value);
    override_style->SetFieldOverride(ON_DimStyle::field::FixedExtensionLength, bCreate);
  }
}

bool ON_Annotation::FixedExtensionLengthOn(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::FixedExtensionOn).FixedExtensionLenOn();
}

void ON_Annotation::SetFixedExtensionLengthOn(const ON_DimStyle* parent_style, bool value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->FixedExtensionLenOn());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetFixedExtensionLenOn(value);
    override_style->SetFieldOverride(ON_DimStyle::field::FixedExtensionOn, bCreate);
  }
}

int ON_Annotation::AlternateToleranceResolution(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AltToleranceResolution).AlternateToleranceResolution();
}

void ON_Annotation::SetAlternateToleranceResolution(const ON_DimStyle* parent_style, int value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->AlternateToleranceResolution());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAlternateToleranceResolution(value);
    override_style->SetFieldOverride(ON_DimStyle::field::AltToleranceResolution, bCreate);
  }
}

bool ON_Annotation::SuppressArrow1(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::SuppressArrow1).SuppressArrow1();
}

void ON_Annotation::SetSuppressArrow1(const ON_DimStyle* parent_style, bool value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->SuppressArrow1());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetSuppressArrow1(value);
    override_style->SetFieldOverride(ON_DimStyle::field::SuppressArrow1, bCreate);
  }
}

bool ON_Annotation::SuppressArrow2(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::SuppressArrow2).SuppressArrow2();
}

void ON_Annotation::SetSuppressArrow2(const ON_DimStyle* parent_style, bool value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->SuppressArrow2());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetSuppressArrow2(value);
    override_style->SetFieldOverride(ON_DimStyle::field::SuppressArrow2, bCreate);
  }
}

int ON_Annotation::TextMoveLeader(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::TextmoveLeader).TextMoveLeader();
}

void ON_Annotation::SetTextMoveLeader(const ON_DimStyle* parent_style, int value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->TextMoveLeader());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetTextMoveLeader(value);
    override_style->SetFieldOverride(ON_DimStyle::field::TextmoveLeader, bCreate);
  }
}

int ON_Annotation::ArcLengthSymbol(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ArclengthSymbol).ArcLengthSymbol();
}

void ON_Annotation::SetArcLengthSymbol(const ON_DimStyle* parent_style, int value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->ArcLengthSymbol());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetArcLengthSymbol(value);
    override_style->SetFieldOverride(ON_DimStyle::field::ArclengthSymbol, bCreate);
  }
}

ON_DimStyle::stack_format ON_Annotation::StackFractionFormat(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::StackFormat).StackFractionFormat();
}

void ON_Annotation::SetStackFractionFormat(const ON_DimStyle* parent_style, ON_DimStyle::stack_format value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->StackFractionFormat());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetStackFractionFormat(value);
    override_style->SetFieldOverride(ON_DimStyle::field::StackFormat, bCreate);
  }
}

double ON_Annotation::StackHeightScale(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::StackTextheightScale).StackHeightScale();
}

void ON_Annotation::SetStackHeightScale(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->StackHeightScale());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetStackHeightScale(value);
    override_style->SetFieldOverride(ON_DimStyle::field::StackTextheightScale, bCreate);
  }
}

double ON_Annotation::RoundOff(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::Round).RoundOff();
}

void ON_Annotation::SetRoundOff(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->RoundOff());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetRoundOff(value);
    override_style->SetFieldOverride(ON_DimStyle::field::Round, bCreate);
  }
}

double ON_Annotation::AlternateRoundOff(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AltRound).AlternateRoundOff();
}

void ON_Annotation::SetAlternateRoundOff(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->AlternateRoundOff());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAlternateRoundOff(value);
    override_style->SetFieldOverride(ON_DimStyle::field::AltRound, bCreate);
  }
}

double ON_Annotation::AngleRoundOff(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AngularRound).AngleRoundOff();
}

void ON_Annotation::SetAngleRoundOff(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->AngleRoundOff());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAngleRoundOff(value);
    override_style->SetFieldOverride(ON_DimStyle::field::AngularRound, bCreate);
  }
}

bool ON_DimStyle::ZeroSuppressMatchesLengthDisplay(
  ON_DimStyle::suppress_zero zero_suppress,
  ON_DimStyle::LengthDisplay length_display)
{
  bool rc = true;

  switch (length_display)
  {
  case ON_DimStyle::LengthDisplay::ModelUnits:
    rc = true;
    break;

  case ON_DimStyle::LengthDisplay::InchesFractional:
    if (
      ON_DimStyle::suppress_zero::None != zero_suppress
      )
    {
      rc = false;
    }
    break;

  case ON_DimStyle::LengthDisplay::FeetAndInches:
    if (
      ON_DimStyle::suppress_zero::None != zero_suppress
      && ON_DimStyle::suppress_zero::SuppressZeroFeet != zero_suppress
      && ON_DimStyle::suppress_zero::SuppressZeroInches != zero_suppress
      && ON_DimStyle::suppress_zero::SuppressZeroFeetAndZeroInches != zero_suppress
      )
    {
      rc = false;
    }
    break;

  default: // decimal format or any future format
    if (
      ON_DimStyle::suppress_zero::None != zero_suppress
      && ON_DimStyle::suppress_zero::SuppressLeading != zero_suppress
      && ON_DimStyle::suppress_zero::SuppressTrailing != zero_suppress
      && ON_DimStyle::suppress_zero::SuppressLeadingAndTrailing != zero_suppress
      )
    {
      rc = false;
    }
    break;
  }

  return rc;

}

ON_DimStyle::suppress_zero ON_Annotation::ZeroSuppress(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ZeroSuppress).ZeroSuppress();
}

 

void ON_Annotation::SetZeroSuppress(const ON_DimStyle* parent_style, ON_DimStyle::suppress_zero value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->ZeroSuppress());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    if (false == override_style->IsFieldOverride(ON_DimStyle::field::DimensionLengthDisplay))
    {
      // Make the DimensionLengthDisplay field on the override style match the parent style
      // but mark it not overridden so override_style->SetZeroSuppress(value) doesn't call an error
      ON_DimStyle::LengthDisplay x = DimensionLengthDisplay(parent_style);
      if (x != override_style->DimensionLengthDisplay())
      {
        override_style->SetDimensionLengthDisplay(x);
        override_style->SetFieldOverride(ON_DimStyle::field::DimensionLengthDisplay, false);
      }
    }

    if (ON_DimStyle::ZeroSuppressMatchesLengthDisplay(value, DimensionLengthDisplay(parent_style)))
    {
      override_style->SetZeroSuppress(value);
      override_style->SetFieldOverride(ON_DimStyle::field::ZeroSuppress, bCreate);
    }
    else
    {
      ON_ERROR("Attempting to set zero suppression to a value that doesn't match length display.");
    }
  }
}

ON_DimStyle::suppress_zero ON_Annotation::AlternateZeroSuppress(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AltZeroSuppress).AlternateZeroSuppress();
}

void ON_Annotation::SetAlternateZeroSuppress(const ON_DimStyle* parent_style, ON_DimStyle::suppress_zero value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->AlternateZeroSuppress());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    if (false == override_style->IsFieldOverride(ON_DimStyle::field::AlternateDimensionLengthDisplay))
    {
      // Make the DimensionLengthDisplay field on the override style match the parent style
      // but mark it not overridden so override_style->SetZeroSuppress(value) doesn't call an error
      ON_DimStyle::LengthDisplay x = AlternateDimensionLengthDisplay(parent_style);
      if (x != override_style->AlternateDimensionLengthDisplay())
      {
        override_style->SetAlternateDimensionLengthDisplay(x);
        override_style->SetFieldOverride(ON_DimStyle::field::AlternateDimensionLengthDisplay, false);
      }
    }

    if (ON_DimStyle::ZeroSuppressMatchesLengthDisplay(value, override_style->AlternateDimensionLengthDisplay()))
    {
      override_style->SetAlternateZeroSuppress(value);
      override_style->SetFieldOverride(ON_DimStyle::field::AltZeroSuppress, bCreate);
    }
    else
    {
      ON_ERROR("Attempting to set zero suppression to a value that doesn't match length display.");
    }
  }
}

ON_DimStyle::suppress_zero ON_Annotation::ToleranceZeroSuppress(const ON_DimStyle* parent_style) const
{
  // OBSOLETE PROPERTY
  // The ZeroSuppress() or  AlternateZeroSuppress() property
  // is used to format tolerance display.  ToleranceZeroSuppress() is ignored.
  return ON_DimStyle::suppress_zero::None;
}

void ON_Annotation::SetToleranceZeroSuppress(const ON_DimStyle* parent_style, ON_DimStyle::suppress_zero value)
{
  // OBSOLETE PROPERTY
  // The ZeroSuppress() or  AlternateZeroSuppress() property
  // is used to format tolerance display.  ToleranceZeroSuppress() is ignored.
}

ON_DimStyle::suppress_zero ON_Annotation::AngleZeroSuppress(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AngleZeroSuppress).AngleZeroSuppress();
}

void ON_Annotation::SetAngleZeroSuppress(const ON_DimStyle* parent_style, ON_DimStyle::suppress_zero value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->AngleZeroSuppress());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAngleZeroSuppress(value);
    override_style->SetFieldOverride(ON_DimStyle::field::AngleZeroSuppress, bCreate);
  }
}

bool ON_Annotation::AlternateBelow(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AltBelow).AlternateBelow();
}

void ON_Annotation::SetAlternateBelow(const ON_DimStyle* parent_style, bool value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->AlternateBelow());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAlternateBelow(value);
    override_style->SetFieldOverride(ON_DimStyle::field::AltBelow, bCreate);
  }
}

ON_Arrowhead::arrow_type ON_Annotation::ArrowType1(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ArrowType1).ArrowType1();
}

void ON_Annotation::SetArrowType1(const ON_DimStyle* parent_style, ON_Arrowhead::arrow_type value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->ArrowType1());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetArrowType1(value);
    override_style->SetFieldOverride(ON_DimStyle::field::ArrowType1, bCreate);
  }
}

ON_Arrowhead::arrow_type ON_Annotation::ArrowType2(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ArrowType2).ArrowType2();
}

void ON_Annotation::SetArrowType2(const ON_DimStyle* parent_style, ON_Arrowhead::arrow_type value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->ArrowType2());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetArrowType2(value);
    override_style->SetFieldOverride(ON_DimStyle::field::ArrowType2, bCreate);
  }
}

void ON_Annotation::SetArrowType1And2(const ON_DimStyle* parent_style, ON_Arrowhead::arrow_type value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = ((value != parent_style->ArrowType1()) ||
                  (value != parent_style->ArrowType2()));
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetArrowType1And2(value);
    override_style->SetFieldOverride(ON_DimStyle::field::ArrowType1, bCreate);
    override_style->SetFieldOverride(ON_DimStyle::field::ArrowType2, bCreate);
  }
}

ON_Arrowhead::arrow_type ON_Annotation::LeaderArrowType(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderArrowType).LeaderArrowType();
}

void ON_Annotation::SetLeaderArrowType(const ON_DimStyle* parent_style, ON_Arrowhead::arrow_type value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->LeaderArrowType());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderArrowType(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderArrowType, bCreate);
  }
}

ON_UUID ON_Annotation::ArrowBlockId1(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ArrowBlockId1).ArrowBlockId1();
}

void ON_Annotation::SetArrowBlockId1(const ON_DimStyle* parent_style, ON_UUID value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->ArrowBlockId1());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetArrowBlockId1(value);
    override_style->SetFieldOverride(ON_DimStyle::field::ArrowBlockId1, bCreate);
  }
}

ON_UUID ON_Annotation::ArrowBlockId2(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::ArrowBlockId2).ArrowBlockId2();
}

void ON_Annotation::SetArrowBlockId2(const ON_DimStyle* parent_style, ON_UUID value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->ArrowBlockId2());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetArrowBlockId2(value);
    override_style->SetFieldOverride(ON_DimStyle::field::ArrowBlockId2, bCreate);
  }
}

ON_UUID ON_Annotation::LeaderArrowBlockId(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderArrowBlock).LeaderArrowBlockId();
}

void ON_Annotation::SetLeaderArrowBlockId(const ON_DimStyle* parent_style, ON_UUID value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->LeaderArrowBlockId());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderArrowBlockId(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderArrowBlock, bCreate);
  }
}

ON::TextVerticalAlignment ON_Annotation::TextVerticalAlignment(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::TextVerticalAlignment).TextVerticalAlignment();
}

void ON_Annotation::SetTextVerticalAlignment(const ON_DimStyle* parent_style, ON::TextVerticalAlignment value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->TextVerticalAlignment());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetTextVerticalAlignment(value);
    override_style->SetFieldOverride(ON_DimStyle::field::TextVerticalAlignment, bCreate);
  }
}

ON::TextVerticalAlignment ON_Annotation::LeaderTextVerticalAlignment(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderTextVerticalAlignment).LeaderTextVerticalAlignment();
}

void ON_Annotation::SetLeaderTextVerticalAlignment(const ON_DimStyle* parent_style, ON::TextVerticalAlignment value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->LeaderTextVerticalAlignment());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderTextVerticalAlignment(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderTextVerticalAlignment, bCreate);
  }
}

ON_DimStyle::ContentAngleStyle ON_Annotation::LeaderContentAngleStyle(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderContentAngleStyle).LeaderContentAngleStyle();
}

void ON_Annotation::SetLeaderContentAngleStyle(const ON_DimStyle* parent_style, ON_DimStyle::ContentAngleStyle value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->LeaderContentAngleStyle());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderContentAngleStyle(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderContentAngleStyle, bCreate);
  }
}

ON_DimStyle::leader_curve_type ON_Annotation::LeaderCurveType(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderCurveType).LeaderCurveType();
}

void ON_Annotation::SetLeaderCurveType(const ON_DimStyle* parent_style, ON_DimStyle::leader_curve_type value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->LeaderCurveType());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderCurveType(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderCurveType, bCreate);
  }
}

bool ON_Annotation::LeaderHasLanding(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderHasLanding).LeaderHasLanding();
}

void ON_Annotation::SetLeaderHasLanding(const ON_DimStyle* parent_style, bool value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->LeaderHasLanding());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderHasLanding(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderHasLanding, bCreate);
  }
}

double ON_Annotation::LeaderLandingLength(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderLandingLength).LeaderLandingLength();
}

void ON_Annotation::SetLeaderLandingLength(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->LeaderLandingLength());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderLandingLength(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderLandingLength, bCreate);
  }
}

double ON_Annotation::LeaderContentAngleRadians(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderContentAngle).LeaderContentAngleRadians();
}

void ON_Annotation::SetLeaderContentAngleRadians(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->LeaderContentAngleRadians());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderContentAngleRadians(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderContentAngle, bCreate);
  }
}

double ON_Annotation::LeaderContentAngleDegrees(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderContentAngle).LeaderContentAngleDegrees();
}

void ON_Annotation::SetLeaderContentAngleDegrees(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->LeaderContentAngleDegrees());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderContentAngleDegrees(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderContentAngle, bCreate);
  }
}

ON::TextHorizontalAlignment ON_Annotation::TextHorizontalAlignment(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::TextHorizontalAlignment).TextHorizontalAlignment();
}

void ON_Annotation::SetTextHorizontalAlignment(const ON_DimStyle* parent_style, ON::TextHorizontalAlignment value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->TextHorizontalAlignment());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetTextHorizontalAlignment(value);
    override_style->SetFieldOverride(ON_DimStyle::field::TextHorizontalAlignment, bCreate);
  }
}

ON::TextHorizontalAlignment ON_Annotation::LeaderTextHorizontalAlignment(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::LeaderTextHorizontalAlignment).LeaderTextHorizontalAlignment();
}

void ON_Annotation::SetLeaderTextHorizontalAlignment(const ON_DimStyle* parent_style, ON::TextHorizontalAlignment value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->LeaderTextHorizontalAlignment());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderTextHorizontalAlignment(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderTextHorizontalAlignment, bCreate);
  }
}

ON_DimStyle::ContentAngleStyle ON_Annotation::DimTextAngleStyle(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::DimTextAngleStyle).DimTextAngleStyle();
}

void ON_Annotation::SetDimTextAngleStyle(const ON_DimStyle* parent_style, ON_DimStyle::ContentAngleStyle value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->DimTextAngleStyle());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDimTextAngleStyle(value);
    override_style->SetFieldOverride(ON_DimStyle::field::DimTextAngleStyle, bCreate);
  }
}

ON_DimStyle::ContentAngleStyle ON_Annotation::DimRadialTextAngleStyle(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::DimRadialTextAngleStyle).DimRadialTextAngleStyle();
}

void ON_Annotation::SetDimRadialTextAngleStyle(const ON_DimStyle* parent_style, ON_DimStyle::ContentAngleStyle value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->DimRadialTextAngleStyle());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDimRadialTextAngleStyle(value);
    override_style->SetFieldOverride(ON_DimStyle::field::DimRadialTextAngleStyle, bCreate);
  }
}

ON::TextOrientation ON_Annotation::TextOrientation(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::TextOrientation).TextOrientation();
}

void ON_Annotation::SetTextOrientation(const ON_DimStyle* parent_style, ON::TextOrientation value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->TextOrientation());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetTextOrientation(value);
    override_style->SetFieldOverride(ON_DimStyle::field::TextOrientation, bCreate);
  }
}

ON::TextOrientation ON_Annotation::LeaderTextOrientation(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::LeaderTextOrientation).LeaderTextOrientation();
}

void ON_Annotation::SetLeaderTextOrientation(const ON_DimStyle* parent_style, ON::TextOrientation value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->LeaderTextOrientation());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetLeaderTextOrientation(value);
    override_style->SetFieldOverride(ON_DimStyle::field::LeaderTextOrientation, bCreate);
  }
}

ON::TextOrientation ON_Annotation::DimTextOrientation(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::DimTextOrientation).DimTextOrientation();
}

void ON_Annotation::SetDimTextOrientation(const ON_DimStyle* parent_style, ON::TextOrientation value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->DimTextOrientation());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDimTextOrientation(value);
    override_style->SetFieldOverride(ON_DimStyle::field::DimTextOrientation, bCreate);
  }
}

ON::TextOrientation ON_Annotation::DimRadialTextOrientation(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::DimRadialTextOrientation).DimRadialTextOrientation();
}

void ON_Annotation::SetDimRadialTextOrientation(const ON_DimStyle* parent_style, ON::TextOrientation value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->DimRadialTextOrientation());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDimRadialTextOrientation(value);
    override_style->SetFieldOverride(ON_DimStyle::field::DimRadialTextOrientation, bCreate);
  }
}

bool ON_Annotation::TextUnderlined(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::TextUnderlined).TextUnderlined();
}

void ON_Annotation::SetTextUnderlined(const ON_DimStyle* parent_style, bool value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->TextUnderlined());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetTextUnderlined(value);
    override_style->SetFieldOverride(ON_DimStyle::field::TextUnderlined, bCreate);
  }
}

bool ON_Annotation::DrawForward(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::DrawForward).DrawForward();
}

void ON_Annotation::SetDrawForward(const ON_DimStyle* parent_style, bool value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->DrawForward());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDrawForward(value);
    override_style->SetFieldOverride(ON_DimStyle::field::DrawForward, bCreate);
  }
}

bool ON_Annotation::SignedOrdinate(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::SignedOrdinate).SignedOrdinate();
}

void ON_Annotation::SetSignedOrdinate(const ON_DimStyle* parent_style, bool value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (value != parent_style->SignedOrdinate());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetSignedOrdinate(value);
    override_style->SetFieldOverride(ON_DimStyle::field::SignedOrdinate, bCreate);
  }
}

double ON_Annotation::DimScale(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::DimensionScale).DimScale();
}

void ON_Annotation::SetDimScale(const ON_DimStyle* parent_style, double value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = Internal_DimStyleDoubleChanged(value, parent_style->DimScale());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDimScale(value);
    override_style->SetFieldOverride(ON_DimStyle::field::DimensionScale, bCreate);
  }
}

wchar_t ON_Annotation::DecimalSeparator(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::DecimalSeparator).DecimalSeparator();
}

void ON_Annotation::SetDecimalSeparator(const ON_DimStyle* parent_style, wchar_t separator)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (separator != parent_style->DecimalSeparator());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDecimalSeparator(separator);
    override_style->SetFieldOverride(ON_DimStyle::field::DecimalSeparator, bCreate);
  }
}

const class ON_Font& ON_Annotation::Font(const ON_DimStyle* parent_style) const
{
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::Font).Font();
}

const class ON_Font& ON_Annotation::FontCharacteristics(const ON_DimStyle* parent_style) const
{
  // FontCharacteristics() queries information that is set by calling ON_DimStyle.SetFont()
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::Font).FontCharacteristics();
}

const bool ON_Annotation::FontSubstituted(const ON_DimStyle* parent_style) const
{
  // FontSubstituted() queries information that is set by calling ON_DimStyle.SetFont()
  return Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::Font).FontSubstituted();
}

void ON_Annotation::SetFont(const ON_DimStyle* parent_style, const class ON_Font& value)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (0 != ON_Font::CompareFontCharacteristics(value, parent_style->Font()));
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetFont(value);
    override_style->SetFieldOverride(ON_DimStyle::field::Font, bCreate);
  }
}

ON_DimStyle::LengthDisplay ON_Annotation::DimensionLengthDisplay(const ON_DimStyle* parent_style) const
{
  const ON_DimStyle::LengthDisplay dim_length_display
    = Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::DimensionLengthDisplay).DimensionLengthDisplay();
  return dim_length_display;
}

ON_DimStyle::LengthDisplay ON_Annotation::AlternateDimensionLengthDisplay(const ON_DimStyle* parent_style) const
{
  const ON_DimStyle::LengthDisplay dim_length_display
    = Internal_StyleForFieldQuery(parent_style,ON_DimStyle::field::AlternateDimensionLengthDisplay).AlternateDimensionLengthDisplay();
  return dim_length_display;
}

void ON_Annotation::SetDimensionLengthDisplay(const ON_DimStyle* parent_style, ON_DimStyle::LengthDisplay length_display)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (length_display != parent_style->DimensionLengthDisplay());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetDimensionLengthDisplay(length_display);
    override_style->SetFieldOverride(ON_DimStyle::field::DimensionLengthDisplay, bCreate);
  }
}

void ON_Annotation::SetAlternateDimensionLengthDisplay(const ON_DimStyle* parent_style, ON_DimStyle::LengthDisplay length_display)
{
  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  bool bCreate = (length_display != parent_style->AlternateDimensionLengthDisplay());
  ON_DimStyle* override_style = Internal_GetOverrideStyle(bCreate);
  if (nullptr != override_style)
  {
    override_style->SetAlternateDimensionLengthDisplay(length_display);
    override_style->SetFieldOverride(ON_DimStyle::field::AlternateDimensionLengthDisplay, bCreate);
  }
}

ON::LengthUnitSystem ON_Annotation::DimensionLengthDisplayUnit(
  const ON_DimStyle* parent_style,
  unsigned int model_sn
) const
{
  if (ON_UNSET_UINT_INDEX == model_sn && nullptr != parent_style)
    model_sn = parent_style->ModelSerialNumber();
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::DimensionLengthDisplay).DimensionLengthDisplayUnit(model_sn);
}

ON::LengthUnitSystem ON_Annotation::AlternateDimensionLengthDisplayUnit(
  const ON_DimStyle* parent_style,
  unsigned int model_sn
) const
{
  if (ON_UNSET_UINT_INDEX == model_sn && nullptr != parent_style)
    model_sn = parent_style->ModelSerialNumber();
  return Internal_StyleForFieldQuery(parent_style, ON_DimStyle::field::AlternateDimensionLengthDisplay).DimensionLengthDisplayUnit(model_sn);
}
//--------------------------------

bool ON_Annotation::ClearRtfFmt(const wchar_t* fmt_str_on, const wchar_t* fmt_str_off, ON_wString& rtf_in)
{
  ON_wString fmt_off = fmt_str_off;
  fmt_off += "{";
  rtf_in.Replace(fmt_off.Array(), L"{");
  fmt_off = fmt_str_off;
  fmt_off += "}";
  rtf_in.Replace(fmt_off.Array(), L"}");
  fmt_off = fmt_str_off;
  fmt_off += "\\";
  rtf_in.Replace(fmt_off.Array(), L"\\");
  fmt_off = fmt_str_off;
  fmt_off += " ";
  rtf_in.Replace(fmt_off.Array(), L"");

  ON_wString fmt_on = fmt_str_on;
  fmt_on += "{";
  rtf_in.Replace(fmt_on.Array(), L"{");
  fmt_on = fmt_str_on;
  fmt_on += "}";
  rtf_in.Replace(fmt_on.Array(), L"}");
  fmt_on = fmt_str_on;
  fmt_on += "\\";
  rtf_in.Replace(fmt_on.Array(), L"\\");
  fmt_on = fmt_str_on;
  fmt_on += " ";
  rtf_in.Replace(fmt_on.Array(), L"");


  return true;
}

int ON_Annotation::FindRtfTable(ON_wString rtf_in, int startidx, const wchar_t* tablename)
{
  int count = rtf_in.Length();
  int idx = rtf_in.Find(tablename, startidx);
  if (-1 != idx)
  {
    int open = 0;
    for (int ci = idx; ci < count; ci++)
    {
      if (L'{' == rtf_in[ci])
        open++;
      else if (L'}' == rtf_in[ci])
        open--;
      if (0 == open)
      {
        idx = ci+1;
        break;
      }
    }
  }
  return idx;
}

bool ON_Annotation::SetRtfFmt(ON_wString& rtf_in, const wchar_t* fmt_str)
{
  ON_wString rtf = rtf_in;

  int idx = rtf.Find(L"{\\rtf1");
  if (-1 == idx)
  {
    rtf_in.Format(L"{\\rtf1{%s %s}}", fmt_str, rtf.Array());
    return true;
  }
  int count = rtf.Length();
  if (-1 < idx && idx < count)
  {
    idx += 6;
    int nextidx = ON_Annotation::FindRtfTable(rtf, idx, L"{\\fonttbl");
    if (-1 != nextidx)
      idx = nextidx;

    nextidx = ON_Annotation::FindRtfTable(rtf, idx, L"{\\colortbl");
    if (-1 != nextidx)
      idx = nextidx;

    ON_wString head = rtf.Left(idx);
    ON_wString tail = rtf.Right(count - idx);
    if (rtf[idx + 1] != L'{')
    {
      rtf_in.Format(L"%s{%s{%s}}", head.Array(), fmt_str, tail.Array());
    }
    else
    {
      rtf_in.Format(L"%s{%s%s}", head.Array(), fmt_str, tail.Array());
    }
  }
  return true;
}

bool ON_Annotation::SetAnnotationTextFormat(ON_wString& rtf_in, const wchar_t* fmt_str_on, const wchar_t* fmt_str_off, bool set_on)
{
  bool rc = ON_Annotation::ClearRtfFmt(fmt_str_on, fmt_str_off, rtf_in);
  if (set_on)
    rc = ON_Annotation::SetRtfFmt(rtf_in, fmt_str_on);
  else
    rc = ON_Annotation::SetRtfFmt(rtf_in, fmt_str_off);
  return rc;
}

bool ON_Annotation::SetAnnotationBold(bool bold, const ON_DimStyle* parent_style)
{
  ON_Dimension* dim = ON_Dimension::Cast(this);
  const wchar_t* textstring;
  if (nullptr == dim)
    textstring = RichText().Array();
  else
    textstring = dim->UserText();
  ON_wString rtfstr(textstring);

  parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
  ON_wString newrtf;
  if (!bold && parent_style->Font().IsBoldInQuartet())
  {
    newrtf = ON_TextContext::FormatRtfString(rtfstr, parent_style, true, true, false, false, false, false, false, false, L"");
    newrtf.Replace(L"\\b", L"\\b0");
  }
  else
    newrtf = ON_TextContext::FormatRtfString(rtfstr, parent_style, !bold, bold, false, false, false, false, false, false, L"");
  
  if (newrtf.IsNotEmpty())
  {
    if (nullptr != dim)
    {
      dim->SetUserText(newrtf);
    }
    else
    {
      ON_TextContent* text = this->Text();
      ON::AnnotationType type = this->Type();
      text->ReplaceTextString(newrtf, type, parent_style);
      SetText(text);
    }
    return true;
  }
  return false;
}

bool ON_Annotation::SetAnnotationItalic(bool italic, const ON_DimStyle* parent_style)
{
  ON_Dimension* dim = ON_Dimension::Cast(this);
  const wchar_t* textstring;
  if (nullptr == dim)
    textstring = RichText().Array();
  else
    textstring = dim->UserText();
  ON_wString rtfstr(textstring);

  const ON_wString newrtf = ON_TextContext::FormatRtfString(rtfstr, parent_style, false, false, !italic, italic, false, false, false, false, L"");
  if (newrtf.IsNotEmpty())
  {
    if (nullptr != dim)
    {
      dim->SetUserText(newrtf);
    }
    else
    {
      ON_TextContent* text = this->Text();
      ON::AnnotationType type = this->Type();
      parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
      text->ReplaceTextString(newrtf, type, parent_style);
      SetText(text);
    }
    return true;
  }
  return false;
}

bool ON_Annotation::SetAnnotationUnderline(bool underline, const ON_DimStyle* parent_style)
{
  ON_Dimension* dim = ON_Dimension::Cast(this);
  const wchar_t* textstring;
  if (nullptr == dim)
    textstring = RichText().Array();
  else
    textstring = dim->UserText();
  ON_wString rtfstr(textstring);

  const ON_wString newrtf = ON_TextContext::FormatRtfString(rtfstr, parent_style, false, false, false, false, !underline, underline, false, false, L"");
  if (newrtf.IsNotEmpty())
  {
    if (nullptr != dim)
    {
      dim->SetUserText(newrtf);
    }
    else
    {
      ON_TextContent* text = this->Text();
      ON::AnnotationType type = this->Type();
      parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
      text->ReplaceTextString(newrtf, type, parent_style);
      SetText(text);
    }
    return true;
  }
  return false;
}


bool ON_Annotation::SetAnnotationFont(const ON_Font* font, const ON_DimStyle* parent_style)
{
  if (nullptr != font)
  {
    SetFont(parent_style, *font);

    const ON_wString fontname = font->QuartetName();  //ON_Font::RichTextFontName(font, true);
    bool bold = font->IsBoldInQuartet();
    bool italic = font->IsItalic();

    ON_Dimension* dim = ON_Dimension::Cast(this);
    const wchar_t* textstring;
    if (nullptr == dim)
      textstring = RichText().Array();
    else
      textstring = dim->UserText();
    ON_wString rtfstr(textstring);

    const ON_wString newrtf = ON_TextContext::FormatRtfString(rtfstr, parent_style, false, bold, false, italic, false, false, false, true, fontname);
    if (newrtf.IsNotEmpty())
    {
      if (nullptr != dim)
      {
        dim->SetUserText(newrtf);
      }
      else
      {
        ON_TextContent* text = this->Text();
        ON::AnnotationType type = this->Type();
        parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
        text->ReplaceTextString(newrtf, type, parent_style);
        SetText(text);
      }
      return true;
    }
  }
  return false;
}

bool ON_Annotation::SetAnnotationFacename(bool set_or_clear, const wchar_t* facename, const ON_DimStyle* parent_style)
{
  ON_Dimension* dim = ON_Dimension::Cast(this);
  const wchar_t* textstring;
  if (nullptr == dim)
    textstring = RichText().Array();
  else
    textstring = dim->UserText();
  ON_wString rtfstr(textstring);

  const ON_wString newrtf = ON_TextContext::FormatRtfString(rtfstr, parent_style, false, false, false, false, false, false, !set_or_clear, set_or_clear, facename);
  if(newrtf.IsNotEmpty())
  {
    if (nullptr != dim)
    {
      dim->SetUserText(newrtf);
    }
    else
    {
      ON_TextContent* text = this->Text();
      ON::AnnotationType type = this->Type();
      parent_style = &ON_DimStyle::DimStyleOrDefault(parent_style);
      text->ReplaceTextString(newrtf, type, parent_style);
      SetText(text);
    }
    return true;
  }
  return false;
}

bool ON_Annotation::FirstCharTextProperties(const wchar_t* rtfstr, bool& bold, bool& italic, bool& underline, ON_wString& facename)
{
  bool rc = ON_TextContext::RtfFirstCharProperties(rtfstr, bold, italic, underline, facename);
  return rc;
}

const ON_Font* ON_Annotation::FirstCharFont() const
{
  if(nullptr != Text())
    return Text()->FirstCharFont();
  return &ON_Font::Default;
}

bool ON_Annotation::IsAllBold() const
{
  return IsAllFormat(&ON_Font::IsBold);
}

bool ON_Annotation::IsAllItalic() const
{
  return IsAllFormat(&ON_Font::IsItalic);
}

bool ON_Annotation::IsAllUnderlined() const
{
  return IsAllFormat(&ON_Font::IsUnderlined);
}

bool ON_Annotation::IsAllFormat(bool (ON_Font::*func)() const) const
{
  if (nullptr == func)
    return false;
  const ON_TextContent* text = Text();
  if (nullptr == text)
    return false;

  const ON_TextRunArray* runs = text->TextRuns(true);
  if (nullptr == runs)
    return false;

  for (int i = 0; i < runs->Count(); i++)
  {
    const ON_TextRun* run = (*runs)[i];
    if (nullptr == run)
      continue;
    ON_TextRun::RunType type = run->Type();
    if (ON_TextRun::RunType::kText == type ||
      ON_TextRun::RunType::kField == type ||
      ON_TextRun::RunType::kFieldValue == type)
    {
      if (!(run->Font()->*func)())
        return false;
    }
  }
  return true;
}







































































