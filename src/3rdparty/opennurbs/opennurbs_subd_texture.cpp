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

#include "opennurbs_subd_data.h"

unsigned char ON_SubD::ObsoleteTextureDomainTypeFromTextureCoordinateType(ON_SubDTextureCoordinateType texture_coordinate_type)
{
/*
  OBSOLETE enum class ON_SubDTextureDomainType : unsigned char
  {
    ///<summary>
    /// Texture domains are not set.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// Each face texture domain is a unique rectangle of normalized texture space.
    ///</summary>
    PerFace = 1,

    ///<summary>
    /// Each face texture domain is a unique rectangle of normalized texture space.
    /// When possible, faces are partitioned into quad groups. Adjacent members
    /// of the group are assigned adjacent rectangles in texture space.
    ///</summary>
    Packed = 2,

    ///<summary>
    /// All face texture domain values are zero.
    ///</summary>
    Zero = 3,

    ///<summary>
    /// All face texture domain values are nan.
    ///</summary>
    Nan = 4,

    ///<summary>
    /// All face texture domain is (0,1)x(0,1).
    ///</summary>
    UnitSquare = 5,

    ///<summary>
    /// Code outside of opennurbs set the values. No other information is available.
    ///</summary>
    Custom = 7,
  };
  */
  unsigned char obsolete_texture_domain_type = 0;
  switch (texture_coordinate_type)
  {
  case ON_SubDTextureCoordinateType::Unset:
    obsolete_texture_domain_type = 0; // OBSOLETE ON_SubDTextureDomainType::Unset = 0
    break;
  case ON_SubDTextureCoordinateType::Unpacked:
    obsolete_texture_domain_type = 1; // OBSOLETE ON_SubDTextureDomainType::PerFace = 1
    break;
  case ON_SubDTextureCoordinateType::Packed:
    obsolete_texture_domain_type = 2; // OBSOLETE ON_SubDTextureDomainType::Packed = 2
    break;
  case ON_SubDTextureCoordinateType::Zero:
    obsolete_texture_domain_type = 3; // OBSOLETE ON_SubDTextureDomainType::Zero = 3
    break;
  case ON_SubDTextureCoordinateType::Nan:
    obsolete_texture_domain_type = 4; // OBSOLETE ON_SubDTextureDomainType::Nan = 4
    break;
  case ON_SubDTextureCoordinateType::FromFaceTexturePoints:
    obsolete_texture_domain_type = 6; // no corresponding OBSOLETE ON_SubDTextureDomainType
    break;
  case ON_SubDTextureCoordinateType::FromMapping:
    obsolete_texture_domain_type = 7; // OBSOLETE ON_SubDTextureDomainType::Custom = 7
    break;
  default:
    obsolete_texture_domain_type = 0;
    break;
  }
  return obsolete_texture_domain_type;
}


ON_SubDTextureCoordinateType ON_SubD::TextureCoordinateTypeFromObsoleteTextureDomainType(
  unsigned int obsolete_texture_domain_type_as_unsigned
)
{
  /*
  OBSOLETE enum class ON_SubDTextureDomainType : unsigned char
  {
    ///<summary>
    /// Texture domains are not set.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// Each face texture domain is a unique rectangle of normalized texture space.
    ///</summary>
    PerFace = 1,

    ///<summary>
    /// Each face texture domain is a unique rectangle of normalized texture space.
    /// When possible, faces are partitioned into quad groups. Adjacent members
    /// of the group are assigned adjacent rectangles in texture space.
    ///</summary>
    Packed = 2,

    ///<summary>
    /// All face texture domain values are zero.
    ///</summary>
    Zero = 3,

    ///<summary>
    /// All face texture domain values are nan.
    ///</summary>
    Nan = 4,

    ///<summary>
    /// All face texture domain is (0,1)x(0,1).
    ///</summary>
    UnitSquare = 5,

    ///<summary>
    /// Code outside of opennurbs set the values. No other information is available.
    ///</summary>
    Custom = 7,
  };
  */

  switch (obsolete_texture_domain_type_as_unsigned)
  {
  case 0: // OBSOLETE ON_SubDTextureDomainType::Unset = 0
    return ON_SubDTextureCoordinateType::Unset;
    break;
  case 1: // OBSOLETE ON_SubDTextureDomainType::PerFace = 1
    return ON_SubDTextureCoordinateType::Unpacked;
    break;
  case 2: // OBSOLETE ON_SubDTextureDomainType::Packed = 2
    return ON_SubDTextureCoordinateType::Packed;
    break;
  case 3: // OBSOLETE ON_SubDTextureDomainType:: Zero = 3
    return ON_SubDTextureCoordinateType::Zero;
    break;
  case 4: // OBSOLETE ON_SubDTextureDomainType::Nan = 4
    return ON_SubDTextureCoordinateType::Nan;
    break;
  case 5: // OBSOLETE ON_SubDTextureDomainType::UnitSquare = 5
    return ON_SubDTextureCoordinateType::Unset;
    break;
  case 6: // no corresponding OBSOLETE ON_SubDTextureDomainType
    return ON_SubDTextureCoordinateType::FromFaceTexturePoints;
    break;
  case 7: // OBSOLETE ON_SubDTextureDomainType::Custom = 7
    return ON_SubDTextureCoordinateType::FromMapping;
    break;
  }
  return ON_SubDTextureCoordinateType::Unset;
}

ON_SubDTextureCoordinateType ON_SubD::TextureCoordinateTypeFromUnsigned
(
  unsigned int texture_coordinate_type_as_unsigned
)
{
  switch (texture_coordinate_type_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDTextureCoordinateType::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDTextureCoordinateType::Unpacked);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDTextureCoordinateType::Packed);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDTextureCoordinateType::Zero);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDTextureCoordinateType::Nan);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDTextureCoordinateType::FromFaceTexturePoints);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_SubDTextureCoordinateType::FromMapping);
  }
  return ON_SUBD_RETURN_ERROR(ON_SubDTextureCoordinateType::Unset);
}

const ON_wString ON_SubD::TextureCoordinateTypeToString(
  ON_SubDTextureCoordinateType texture_coordinate_type
)
{
  const wchar_t* s;
  switch (texture_coordinate_type)
  {
  case ON_SubDTextureCoordinateType::Unset:
    s = L"Unset";
    break;
  case ON_SubDTextureCoordinateType::Unpacked:
    s = L"Unpacked";
    break;
  case ON_SubDTextureCoordinateType::Packed:
    s = L"Packed";
    break;
  case ON_SubDTextureCoordinateType::Zero:
    s = L"Zero";
    break;
  case ON_SubDTextureCoordinateType::Nan:
    s = L"Nan";
    break;
  case ON_SubDTextureCoordinateType::FromFaceTexturePoints:
    s = L"FromFaceTexturePoints";
    break;
  case ON_SubDTextureCoordinateType::FromMapping:
    s = L"FromMapping";
    break;
  default:
    s = nullptr;
    break;
  }
  return (nullptr != s && 0 != s[0]) 
    ? ON_wString(s)
    : ON_wString::FormatToString(L"ON_SubDTextureCoordinateType(%u)", ((unsigned)static_cast<unsigned char>(texture_coordinate_type)));
}

//////////////////////////////////////////////////////////////////////////////
//
// ON_SubDimple - texture coordinates
// 
#if 1
#pragma region ON_SubD - texture coordinates

void ON_SubDimple::SetTextureMappingTag(const ON_MappingTag &mapping_tag) const
{
  if (0 != ON_MappingTag::CompareAll(this->m_texture_mapping_tag, mapping_tag))
  {
    this->m_texture_mapping_tag = mapping_tag;
    ChangeRenderContentSerialNumber();
  }
}

const ON_MappingTag ON_SubDimple::TextureMappingTag(bool bIgnoreTextureCoordinateType) const
{
  return
    (bIgnoreTextureCoordinateType || ON_SubDTextureCoordinateType::FromMapping == TextureCoordinateType())
    ? m_texture_mapping_tag
    : ON_MappingTag::Unset;
}

#pragma endregion
#endif

const ON_MappingTag ON_SubDimple::ColorsMappingTag() const
{
  return m_colors_mapping_tag;
}

void ON_SubDimple::SetColorsMappingTag(const ON_MappingTag& mapping_tag) const
{
  if (0 != ON_MappingTag::CompareAll(this->m_colors_mapping_tag, mapping_tag))
  {
    this->m_colors_mapping_tag = mapping_tag;
    ChangeRenderContentSerialNumber();
  }
}


//////////////////////////////////////////////////////////////////////////////
//
// ON_SubD - texture coordinates
// 
#if 1
#pragma region ON_SubD - texture coordinates

ON_SubDTextureCoordinateType ON_SubD::TextureCoordinateType() const
{
  const ON_SubDimple* subdimple = SubDimple();
  return (nullptr != subdimple) ? subdimple->TextureCoordinateType() : ON_SubDTextureCoordinateType::Unset;
}

ON_SubDTextureCoordinateType ON_SubDimple::TextureCoordinateType() const
{
  return m_texture_coordinate_type;
}


unsigned int ON_SubD::TexturePointsAreSet() const
{
  unsigned int count = 0;
  ON_SubDFaceIterator fit(*this);
  for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
  {
    if (f->TexturePointsAreSet())
      ++count;
  }
  return count;
}

unsigned int ON_SubD::ClearTexturePoints() const
{
  const bool bUpdateFragments = ON_SubDTextureCoordinateType::FromFaceTexturePoints == this->TextureCoordinateType();
  const ON_SubDimple* subdimple = SubDimple();
  const unsigned count = (nullptr != subdimple) ? subdimple->ClearTexturePoints() : 0;
  if (bUpdateFragments)
    this->Internal_SetFragmentTextureCoordinatesWithoutMapping();
  return count;
}

unsigned int ON_SubDimple::ClearTexturePoints() const
{
  bool bSetPacked = ON_SubDTextureCoordinateType::FromFaceTexturePoints == this->TextureCoordinateType();
  if ( bSetPacked)
    this->SetTextureCoordinateType(ON_SubDTextureCoordinateType::Unset);
  const ON_SubDLevel& level = this->ActiveLevel();
  unsigned int count = 0;
  for (const ON_SubDFace* f = level.m_face[0]; nullptr != f; f = f->m_next_face)
  {
    if (f->TexturePointsAreSet())
      ++count;
    this->ReturnFaceTexturePoints(f);
    if (bSetPacked && false == f->PackRectIsSet())
      bSetPacked = false;
  }
  if (bSetPacked)
    this->SetTextureCoordinateType(ON_SubDTextureCoordinateType::Packed);
  return count;
}

void ON_SubDimple::SetTextureCoordinateType(
  ON_SubDTextureCoordinateType texture_coordinate_type
) const
{
  if (m_texture_coordinate_type != texture_coordinate_type)
  {
    ChangeRenderContentSerialNumber();
    m_texture_coordinate_type = texture_coordinate_type;
  }
}

const ON_2udex ON_SubD::TextureDomainGridSize(
  unsigned minimum_rectangle_count,
  double image_width,
  double image_height
)
{
  if (0 == minimum_rectangle_count)
    return ON_2udex(1, 1);

  unsigned i = (unsigned)floor(sqrt((double)(minimum_rectangle_count)));
  while (i < minimum_rectangle_count && i*i < minimum_rectangle_count)
    ++i;
  unsigned int j = i;
  if (j > 1 && (j - 1)*i >= minimum_rectangle_count)
    --j;
  return (image_height > image_width) ? ON_2udex(j, i) : ON_2udex(i, j);
}

double ON_SubDFace::PackRectGapInPixels(
  double pack_rect_distance_in_pixels
)
{
  // In order to produce repeatable rendering results,
  // it is critical that TextureImageSuggestedMinimumSize be a 
  // constant and context independent value.

  // As is clearly stated in the definition of ON_SubD::TextureImageSuggestedMinimumSize,
  // this code assumes ON_SubD::TextureImageSuggestedMinimumSize is a power of 2 and
  // ON_SubD::TextureImageSuggestedMinimumSize >= 512.
  // As a result the following code assumes min_distance_in_pixels >= 8.0 and an integer value;
  const double min_distance_in_pixels = ((double)(ON_SubD::TextureImageSuggestedMinimumSize))/64.0;
  
  if (pack_rect_distance_in_pixels >= min_distance_in_pixels)
  {
    if (pack_rect_distance_in_pixels <= 2.0 * min_distance_in_pixels)
      return 1.0;
    if (pack_rect_distance_in_pixels <= 4.0 * min_distance_in_pixels)
      return 2.0;
    return 3.0;
  }
  return 0.0;
}

const ON_2udex ON_SubDFace::GetNgonSubPackRectSizeAndDelta(
  unsigned int ngon_edge_count,
  ON_2dVector ngon_face_pack_rect_size,
  ON_2dVector& ngon_sub_pack_rect_size,
  ON_2dVector& ngon_sub_pack_rect_delta
)
{
  ON_2udex grid_size(0, 0);
  ngon_sub_pack_rect_size = ON_2dVector::ZeroVector;
  ngon_sub_pack_rect_delta = ON_2dVector::ZeroVector;

  // This function determines how to partition ngon_face_pack_rect_size into
  // ngon_edge_count sub quads that the ngon will use when it is rendered.

  // Validate input parameters
  if (ngon_edge_count < 5 || ngon_edge_count > ON_SubDFace::MaximumEdgeCount)
  {
    ON_SUBD_ERROR("Invalid ngon_edge_count parameter. Value must be >= 5 and <= ON_SubDFace::MaximumEdgeCount.");
    return grid_size;
  }

  if (false == (ngon_face_pack_rect_size.x > 0.0 && ngon_face_pack_rect_size.x < ON_UNSET_POSITIVE_VALUE))
  {
    ON_SUBD_ERROR("Invalid ngon_face_pack_rect_size.x parameter. Value must be > 0.");
    return grid_size;
  }

  if (false == (ngon_face_pack_rect_size.y > 0.0 && ngon_face_pack_rect_size.y < ON_UNSET_POSITIVE_VALUE))
  {
    ON_SUBD_ERROR("Invalid ngon_face_pack_rect_size.y parameter. Value must be > 0.");
    return grid_size;
  }

  // The ngon's face pack rect will be partitioned into grid_size.i X grid_size.j sub pack rects.
  const int pack_rect_aspectdex
    = (ngon_face_pack_rect_size.x > ngon_face_pack_rect_size.y)
    ? 1
    : ((ngon_face_pack_rect_size.x < ngon_face_pack_rect_size.y) ? -1 : 0)
    ;
  grid_size = ON_SubD::TextureDomainGridSize(ngon_edge_count, 0.0, 0.0);
  if (grid_size.i * grid_size.j < ngon_edge_count)
  {
    ON_SUBD_ERROR("Failed to get a valid grid_size.");
    return ON_2udex(0, 0);
  }
  else
  {
    const int grid_aspectdex
      = (grid_size.i > grid_size.j)
      ? 1
      : ((grid_size.i < grid_size.j) ? -1 : 0)
      ;
    if (grid_aspectdex * pack_rect_aspectdex < 0)
      grid_size = ON_2udex(grid_size.j, grid_size.i);
  }

  // Estimate image pixels assigned to this ngon's pack rect.
  // In order to produce repeatable rendering results,
  // it is critical that TextureImageSuggestedMinimumSize be a 
  // constant and context independent value.
  // 
  // The portion of the image assigned to the ngon face pack rect
  // is rect_image_width X rect_image_height pixels.
  // All variables ending in "size" have pixels as units.
  const double subd_image_size = ON_SubD::TextureImageSuggestedMinimumSize;
  const double rect_image_size[2] = {
    subd_image_size * ngon_face_pack_rect_size.x,
    subd_image_size * ngon_face_pack_rect_size.y
  };
  double subrect_image_size[2] = {
    rect_image_size[0] / ((double)(grid_size.i)),
    rect_image_size[1] / ((double)(grid_size.j))
  };
  double subrect_gap_size[2] = {
    ON_SubDFace::PackRectGapInPixels(subrect_image_size[0]),
    ON_SubDFace::PackRectGapInPixels(subrect_image_size[1])
  };

  // As is clearly stated in the definition of ON_SubD::TextureImageSuggestedMinimumSize,
  // this code assumes ON_SubD::TextureImageSuggestedMinimumSize is a power of 2 and
  // ON_SubD::TextureImageSuggestedMinimumSize >= 512.
  // As a result the following code assumes min_distance_in_pixels >= 8.0 and an integer value;
  //const double min_distance_in_pixels = ((double)(ON_SubD::TextureImageSuggestedMinimumSize)) / 64.0;

  bool bApplyGap[2] = { false,false };
  for (int i = 0; i < 2; ++i)
  {
    bApplyGap[i] = (subrect_gap_size[i] >= 1.0 && 8.0 * subrect_gap_size[i] <= subrect_image_size[i]);
    if (bApplyGap[i])
      subrect_image_size[i] = floor(subrect_image_size[i]) - subrect_gap_size[i];
  }

  // Dividing by subd_image_size converts pixel values to normalized dimensionless pack subrect values.
  ngon_sub_pack_rect_size = ON_2dVector(
    bApplyGap[0] ? (subrect_image_size[0] / subd_image_size) : (1.0 - ON_EPSILON) * (ngon_face_pack_rect_size.x / ((double)(grid_size.i))),
    bApplyGap[1] ? (subrect_image_size[1] / subd_image_size) : (1.0 - ON_EPSILON) * (ngon_face_pack_rect_size.y / ((double)(grid_size.j)))
  );
  ngon_sub_pack_rect_delta = ON_2dVector(
    ngon_sub_pack_rect_size.x + (bApplyGap[0] ? (subrect_gap_size[0] / subd_image_size) : 0.0),
    ngon_sub_pack_rect_size.y + (bApplyGap[1] ? (subrect_gap_size[1] / subd_image_size) : 0.0)
  );

  return grid_size;
}

void ON_SubD::SetTextureCoordinateType(
  ON_SubDTextureCoordinateType texture_coordinate_type
) const
{
  const ON_SubDimple* subdimple = SubDimple();
  if (nullptr != subdimple)
    subdimple->SetTextureCoordinateType(texture_coordinate_type);
}

bool ON_SubD::TextureMappingRequired() const
{
  if (ON_SubDTextureCoordinateType::FromMapping == TextureCoordinateType())
  {
    const ON_MappingTag texture_mapping_tag = TextureMappingTag(false);
    if (
      ON_TextureMapping::TYPE::no_mapping != texture_mapping_tag.m_mapping_type
      && ON_TextureMapping::TYPE::srfp_mapping != texture_mapping_tag.m_mapping_type 
      && texture_mapping_tag.IsSet()
      )
      return true; // need an explicit ON_TextureMapping class to evaluate texture coordinates.
  }
  return false;
}

ON_SubDTextureCoordinateType ON_SubD::Internal_BestChoiceTextureCoordinateType(
  const class ON_TextureMapping& available_mapping
) const
{
  ON_SubDTextureCoordinateType subd_texture_coordinate_type = TextureCoordinateType();

  if (ON_SubDTextureCoordinateType::FromMapping == subd_texture_coordinate_type)
  {
    const ON_MappingTag texture_mapping_tag = TextureMappingTag(false);
    switch (texture_mapping_tag.m_mapping_type)
    {
    case ON_TextureMapping::TYPE::no_mapping:
      subd_texture_coordinate_type = ON_SubDTextureCoordinateType::Unset;
      break;
    case ON_TextureMapping::TYPE::srfp_mapping:
      subd_texture_coordinate_type = ON_SubDTextureCoordinateType::Packed; // <- breakpoint here when debugging texture issues
      break;
    default:
      {
        const bool bMappingAvailable
          = ON_TextureMapping::TYPE::srfp_mapping != texture_mapping_tag.m_mapping_type
          && texture_mapping_tag.IsSet()
          && texture_mapping_tag.m_mapping_type == available_mapping.m_type
          && texture_mapping_tag.m_mapping_crc == available_mapping.MappingCRC()
          ;
        if (false == bMappingAvailable)
          subd_texture_coordinate_type = ON_SubDTextureCoordinateType::Unset; // <- breakpoint here when debugging texture issues
      }
      break;
    }
  }

  if (ON_SubDTextureCoordinateType::Unset == subd_texture_coordinate_type)
    subd_texture_coordinate_type = ON_SubD::DefaultTextureCoordinateType;

  return subd_texture_coordinate_type;
}

bool ON_SubD::Internal_SetFragmentTextureCoordinatesWithoutMapping() const
{

  // face_corners[] initialized to unpacked.
  ON_SubDTextureCoordinateType subd_texture_coordinate_type = Internal_BestChoiceTextureCoordinateType(ON_TextureMapping::Unset);

  bool bPacked = false;
  bool bUnpacked = false;
  bool bConstant = false;
  bool bFromFaceTexturePoints = false;
  ON_3dPoint face_corners[4];
  
  switch (subd_texture_coordinate_type)
  {
  default:
    // no break here
  case ON_SubDTextureCoordinateType::FromMapping:
    ON_SUBD_ERROR("Bug - these cases should have been eliminated in code above.");
    subd_texture_coordinate_type = ON_SubDTextureCoordinateType::Packed;
    // no break here

  case ON_SubDTextureCoordinateType::Packed:
    bPacked = true;
    // If packing information is present, these values get updated for each face.
    face_corners[0] = ON_3dPoint::NanPoint;
    face_corners[1] = ON_3dPoint::NanPoint;
    face_corners[2] = ON_3dPoint::NanPoint;
    face_corners[3] = ON_3dPoint::NanPoint;
    break;

  case ON_SubDTextureCoordinateType::Unpacked:
    bUnpacked = true;
    // fragment grid order for unit texture corners
    face_corners[0] = ON_3dPoint(0, 0, 0);
    face_corners[1] = ON_3dPoint(1, 0, 0);
    face_corners[2] = ON_3dPoint(0, 1, 0);
    face_corners[3] = ON_3dPoint(1, 1, 0);
    break;

  case ON_SubDTextureCoordinateType::Zero:
    bConstant = true;
    face_corners[0] = ON_3dPoint::Origin;
    face_corners[1] = ON_3dPoint::Origin;
    face_corners[2] = ON_3dPoint::Origin;
    face_corners[3] = ON_3dPoint::Origin;
    break;

  case ON_SubDTextureCoordinateType::Nan:
    bConstant = true;
    face_corners[0] = ON_3dPoint::NanPoint;
    face_corners[1] = ON_3dPoint::NanPoint;
    face_corners[2] = ON_3dPoint::NanPoint;
    face_corners[3] = ON_3dPoint::NanPoint;
    break;

  case ON_SubDTextureCoordinateType::FromFaceTexturePoints:
    bFromFaceTexturePoints = true;
    face_corners[0] = ON_3dPoint::NanPoint;
    face_corners[1] = ON_3dPoint::NanPoint;
    face_corners[2] = ON_3dPoint::NanPoint;
    face_corners[3] = ON_3dPoint::NanPoint;
    break;
  }

  ON_SHA1_Hash hash = ON_SHA1_Hash::EmptyContentHash;
  if (bPacked || bUnpacked || bConstant || bFromFaceTexturePoints)
  {
    ON_SubDFaceIterator fit(*this);

    // DELETE // // estimate face image size - used to add empty space around ngon-subdfragments
    // DELETE // const unsigned int face_image_size = ON_SubD::TextureImageSuggestedMinimumSize(ON_SubD::TextureDomainGridSize(fit.FaceCount(), 0, 0));

    for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      if (f->m_edge_count < 3)
        continue;
      const ON_SubDMeshFragment* fragment = f->MeshFragments();
      if (nullptr == fragment)
        continue;

      const unsigned short frag_count = (4 == f->m_edge_count) ? 1 : f->m_edge_count;
      if (bUnpacked || bConstant)
      {
        for (unsigned short frag_dex = 0; frag_dex < frag_count && nullptr != fragment; ++frag_dex, fragment = fragment->m_next_fragment)
          fragment->SetTextureCoordinateCornersForExperts(true, face_corners, true);
        continue;
      }

      if (bFromFaceTexturePoints && f->TexturePointsAreSet())
      {
        // All the code in this if clause handles setting custom texture coordinates.
        ON_3dPoint frag_texture_corners[4];
        if (1 == frag_count)
        {
          // f is a quad face and there is one fragment
          frag_texture_corners[0] = f->TexturePoint(0);
          frag_texture_corners[1] = f->TexturePoint(1);
          frag_texture_corners[2] = f->TexturePoint(2);
          frag_texture_corners[3] = f->TexturePoint(3);
          fragment->SetTextureCoordinateCornersForExperts(false, frag_texture_corners, true);
        }
        else if ( frag_count >= 3)
        {
          // f is a n-gon with n subd fragments
          const int k = 2;
          frag_texture_corners[(2 + k) % 4] = f->TextureCenterPoint();
          ON_Line L(f->TexturePoint(f->m_edge_count - 1), f->TexturePoint(0));
          frag_texture_corners[(1 + k) % 4] = L.PointAt(0.5);
          for (unsigned short frag_dex = 0; frag_dex < frag_count && nullptr != fragment; ++frag_dex, fragment = fragment->m_next_fragment)
          {
            L.from = L.to;
            L.to = f->TexturePoint((frag_dex + 1) % frag_count);
            frag_texture_corners[(3 + k) % 4] = frag_texture_corners[(1 + k) % 4];
            frag_texture_corners[(0 + k) % 4] = L.from;
            frag_texture_corners[(1 + k) % 4] = L.PointAt(0.5);
            fragment->SetTextureCoordinateCornersForExperts(false, frag_texture_corners, true);
          }
        }
        continue;
      }

      // The remaining code in this scope handles setting packed texture coordinates on face fragments.
      // We end up here when bPacked or a face is missing texture points.
      if (f->PackRectIsSet())
      {
        // even when bPacked is false, use packed coordinates as a fallback
        face_corners[0] = f->PackRectCorner(true, 0);
        face_corners[1] = f->PackRectCorner(true, 1);
        face_corners[2] = f->PackRectCorner(true, 2);
        face_corners[3] = f->PackRectCorner(true, 3);
      }
      else
      {
        face_corners[0] = ON_2dPoint::NanPoint;
        face_corners[1] = ON_2dPoint::NanPoint;
        face_corners[2] = ON_2dPoint::NanPoint;
        face_corners[3] = ON_2dPoint::NanPoint;
      }

      if (1 == frag_count || 3 == frag_count)
      {
        // A quad ON_SubDFace has a single fragment and that fragment gets the entire face_texture_domain
        // A 3-gon ON_SubDFace has 3 fragments that get a portion of the entire face_texture_domain
        for (unsigned short frag_dex = 0; frag_dex < frag_count && nullptr != fragment; ++frag_dex, fragment = fragment->m_next_fragment)
          fragment->SetQuadOr3gonFaceFragmentTextureCoordinateCorners(true, face_corners, true);
      }
      else if (frag_count >= 5)
      {
        // A n-gon ON_SubDFace (n  has n fragments that get a portion of the entire face_texture_domain

        // General case n-gon with n >= 5.
        // This face in an n-gon with n fragments that each get a portion of the 
        // texture domain assigned to the face.
        const ON_2dVector face_pack_rect_size = f->PackRectIsSet() ? f->PackRectSize() : ON_2dVector(1.0, 1.0);
        ON_2dVector ngon_sub_pack_rect_size = ON_2dVector::NanVector;
        ON_2dVector ngon_sub_pack_rect_delta = ON_2dVector::NanVector;
        const ON_2udex ngon_grid_size = ON_SubDFace::GetNgonSubPackRectSizeAndDelta(
          frag_count,
          face_pack_rect_size,
          ngon_sub_pack_rect_size,
          ngon_sub_pack_rect_delta
        );
        for (unsigned short frag_dex = 0; frag_dex < frag_count && nullptr != fragment; ++frag_dex, fragment = fragment->m_next_fragment)
          fragment->SetNgonFaceFragmentTextureCoordinateCorners(true, face_corners, face_pack_rect_size, ngon_grid_size, ngon_sub_pack_rect_size, ngon_sub_pack_rect_delta, true);
      }
    }
    hash = ON_SubD::TextureSettingsHash(subd_texture_coordinate_type, ON_MappingTag::Unset);
    ChangeRenderContentSerialNumber();
  }

  Internal_SetFragmentTextureCoordinatesTextureSettingsHash(hash);

  return true;
}

void ON_SubD::SetTextureMappingTag(const ON_MappingTag &mapping_tag) const
{
  const ON_SubDimple* subdimple = SubDimple();
  if (nullptr != subdimple)
    subdimple->SetTextureMappingTag(mapping_tag);
}

void ON_SubD::ClearFragmentTextureCoordinatesTextureSettingsHash() const
{
  Internal_SetFragmentTextureCoordinatesTextureSettingsHash(ON_SHA1_Hash::EmptyContentHash);
}

static bool SetGridMeshMappingTCs(const unsigned int pointCount, const double* P, const size_t P_stride, const double* N, const size_t N_stride, double* T, const size_t T_stride, const ON_TextureMapping& mapping, const ON_Xform* P_xform, const ON_Xform* N_xform)
{
  return false;
}

bool ON_SubD::SetFragmentTextureCoordinates(
  const class ON_TextureMapping& mapping,
  bool bLazy
) const
{
  const ON_SubDTextureCoordinateType subd_texture_coordinate_type = Internal_BestChoiceTextureCoordinateType(mapping);
  const ON_MappingTag mapping_tag = this->TextureMappingTag(false);
  const ON_SHA1_Hash hash = ON_SubD::TextureSettingsHash(subd_texture_coordinate_type, mapping_tag);

  if (bLazy)
  {
    // fragment texture coordinates match what's be asked for.
    const ON_SHA1_Hash current_hash = FragmentTextureCoordinatesTextureSettingsHash();
    if (hash == current_hash)
      return true;
  }


  if (ON_SubDTextureCoordinateType::FromMapping != subd_texture_coordinate_type || false == this->TextureMappingRequired())
    return Internal_SetFragmentTextureCoordinatesWithoutMapping();

  // we have a valid and nontrivial mapping.
  const ON_Xform subd_xform(mapping_tag.Transform());
  const bool bApplySubDXform = ON_MappingTag::TransformTreatedIsIdentity(&subd_xform) ? false : true;
  ON_Xform P_xform, N_xform;
  if (bApplySubDXform)
    subd_xform.GetMappingXforms(P_xform, N_xform);

  ON_3dPoint tc;
  ON_SubDMeshFragmentIterator frit(*this);
  for (const ON_SubDMeshFragment* fragment = frit.FirstFragment(); nullptr != fragment; fragment = frit.NextFragment())
  {
    const unsigned P_count = fragment->PointCount();
    if (P_count < 4)
      continue;
    const double* P = fragment->m_P;
    const size_t P_stride = fragment->m_P_stride;
    unsigned T_count = fragment->TextureCoordinateCount();
    if (P_count != T_count)
      continue;
    double* T = fragment->m_T;
    if (nullptr == T)
      continue;
    size_t T_stride = fragment->m_T_stride;
    if (0 == T_stride)
    {
      T_stride = 3;
      T_count = 1;
    }
    const unsigned N_count = fragment->NormalCount();
    const double* N = (N_count == P_count) ? fragment->m_N : &ON_3dVector::ZeroVector.x;
    const size_t N_stride = (N_count == P_count) ? fragment->m_N_stride : 0;
    if (T_count != P_count || N_count != P_count || !SetGridMeshMappingTCs(P_count, P, P_stride, N, N_stride, T, T_stride, mapping, bApplySubDXform ? &P_xform : nullptr, bApplySubDXform ? &N_xform : nullptr))
    {
      for (double* T1 = T + T_stride * T_count; T < T1; T += T_stride, P += P_stride, N += N_stride)
      {
        const bool ok = bApplySubDXform ?
          mapping.Evaluate(ON_3dPoint(P), ON_3dVector(N), &tc, P_xform, N_xform) :
          mapping.Evaluate(ON_3dPoint(P), ON_3dVector(N), &tc);
        if (!ok)
          tc = ON_3dPoint::NanPoint;
        T[0] = tc.x;
        T[1] = tc.y;
        T[2] = tc.z;
      }
    }
  }

  Internal_SetFragmentTextureCoordinatesTextureSettingsHash(hash);

  return true;
}

void ON_SubD::Internal_SetFragmentTextureCoordinatesTextureSettingsHash(ON_SHA1_Hash hash) const
{
  const ON_SubDimple* subdimple = SubDimple();
  if (nullptr != subdimple) 
    subdimple->Internal_SetFragmentTextureCoordinatesTextureSettingsHash(hash);
}

const ON_SHA1_Hash ON_SubD::FragmentTextureCoordinatesTextureSettingsHash() const
{
  const ON_SubDimple* subdimple = SubDimple();
  return (nullptr != subdimple) ? subdimple->FragmentTextureCoordinatesTextureSettingsHash() : ON_SHA1_Hash::EmptyContentHash;
}

const ON_MappingTag ON_SubD::TextureMappingTag(bool bIgnoreTextureCoordinateType) const
{
  const ON_SubDimple* subdimple = SubDimple();
  return (nullptr != subdimple) ? subdimple->TextureMappingTag(bIgnoreTextureCoordinateType) : ON_MappingTag();
}

const ON_SHA1_Hash ON_SubD::TextureSettingsHash(ON_SubDTextureCoordinateType texture_coordinate_type, const ON_MappingTag& texture_mapping_tag)
{
  bool bHashMapping = false;
  switch (texture_coordinate_type)
  {
  case ON_SubDTextureCoordinateType::Unset:
    break;
  case ON_SubDTextureCoordinateType::Unpacked:
    break;
  case ON_SubDTextureCoordinateType::Packed:
    break;
  case ON_SubDTextureCoordinateType::Zero:
    break;
  case ON_SubDTextureCoordinateType::Nan:
    break;
  case ON_SubDTextureCoordinateType::FromFaceTexturePoints:
    break;
  case ON_SubDTextureCoordinateType::FromMapping:
    switch (texture_mapping_tag.m_mapping_type)
    {
    case ON_TextureMapping::TYPE::no_mapping:
      texture_coordinate_type = ON_SubD::DefaultTextureCoordinateType;
      break;
    case ON_TextureMapping::TYPE::srfp_mapping:
      texture_coordinate_type = ON_SubDTextureCoordinateType::Packed;
      break;
    default:
      if (texture_mapping_tag.IsSet())
        bHashMapping = true;
      else
        texture_coordinate_type = ON_SubD::DefaultTextureCoordinateType;
      break;
    }
    break;
  default:
    ON_SUBD_ERROR("Invalid texture_coordinate_type parameter");
    texture_coordinate_type = ON_SubDTextureCoordinateType::Unset;
    break;
  }

  ON_SHA1 sha1;

  sha1.AccumulateBytes(&texture_coordinate_type, sizeof(texture_coordinate_type)); // 1 byte
  if (bHashMapping)
    sha1.AccumulateSubHash(texture_mapping_tag.Hash());

  return sha1.Hash();
}

const ON_SHA1_Hash ON_SubD::TextureSettingsHash() const
{
  return ON_SubD::TextureSettingsHash(this->TextureCoordinateType(), this->TextureMappingTag(false));
}


#pragma endregion
#endif

//////////////////////////////////////////////////////////////////////////////
//
// ON_SubDFace - texture coordinates
// 
void ON_SubDFace::SetMaterialChannelIndex(int material_channel_index) const
{
  if ( material_channel_index > 0 && material_channel_index <= ON_Material::MaximumMaterialChannelIndex )
  {
    m_material_channel_index = (unsigned short)material_channel_index;
  }
  else
  {
    if (0 != material_channel_index)
    {
      ON_ERROR("Invalid material_channel_index value.");
    }
    ClearMaterialChannelIndex(); // makes it easier to detect when per face setting is cleared.
  }
}

void ON_SubDFace::ClearMaterialChannelIndex() const
{
  m_material_channel_index = 0;
}

int ON_SubDFace::MaterialChannelIndex() const
{
  return (int)m_material_channel_index;
}

void ON_SubDFace::SetPerFaceColor(
  ON_Color color
  ) const
{
  if (ON_Color::UnsetColor == color)
    ClearPerFaceColor(); // makes it easier to detect when the per face setting is cleared.
  else
    m_per_face_color = color;
}

void ON_SubDFace::ClearPerFaceColor() const
{
  m_per_face_color = ON_Color::UnsetColor;
}


const ON_Color ON_SubDFace::PerFaceColor() const
{
  return m_per_face_color;
}


unsigned int ON_SubD::ClearPerFaceMaterialChannelIndices()
{
  unsigned change_count = 0;
  ON_SubDFaceIterator fit(*this);
  for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
  {
    if (0 != f->MaterialChannelIndex())
    {
      f->ClearMaterialChannelIndex();
      ++change_count;
    }
  }

  if (change_count>0)
    ChangeRenderContentSerialNumber();

  return change_count;
}

bool ON_SubD::HasPerFaceMaterialChannelIndices() const
{
  ON_SubDFaceIterator fit(*this);
  for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
  {
    if (0 != f->MaterialChannelIndex())
      return true;
  }
  return false;
}

unsigned int ON_SubD::ClearPerFaceColors() const
{
  unsigned change_count = 0;
  ON_SubDFaceIterator fit(*this);
  for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
  {
    if (ON_Color::UnsetColor != f->PerFaceColor())
    {
      f->ClearPerFaceColor();
      ++change_count;
    }
  }
  if (change_count > 0)
    ChangeRenderContentSerialNumber();
  return change_count;
}

bool ON_SubD::HasPerFaceColors() const
{
  ON_SubDFaceIterator fit(*this);
  for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
  {
    if (ON_Color::UnsetColor != f->PerFaceColor())
      return true;
  }
  return false;
}

void ON_SubD::SetPerFaceColorsFromPackId() const
{
  if (FaceCount() <= 0)
    return;

  ON_SubDFaceIterator fit(*this);
  for (const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
  {
    const unsigned pack_id = f->PackId();
    if (0 == pack_id)
      f->ClearPerFaceColor();
    else
      f->SetPerFaceColor(ON_Color::RandomColor(pack_id));
  }
  ChangeRenderContentSerialNumber(); // face color changes.
}

bool ON_SubD::HasPerFaceColorsFromPackId() const
{
  ON_SubDFaceIterator fit(*this);
  const ON_SubDFace* f = fit.FirstFace();
  if (nullptr == f)
    return false;
  bool bHasPerFaceColorsFromPackId = false;
  for (/*empty init*/; nullptr != f; f = fit.NextFace())
  {
    const ON_Color f_color = f->PerFaceColor();
    if (((unsigned int)f_color) == ((unsigned int)ON_Color::UnsetColor))
      continue;
    const unsigned pack_id = f->PackId();
    const ON_Color pack_id_color 
      = (0 == pack_id)
      ? ON_Color::UnsetColor
      : ON_Color::RandomColor(pack_id);
    if (((unsigned int)pack_id_color) != ((unsigned int)f_color))
      return false;
    bHasPerFaceColorsFromPackId = true;
  }
  return bHasPerFaceColorsFromPackId;
}




void ON_SubD::SetComponentMarkBitsFromSymmetryMotif() const
{
  this->ClearComponentMarkBits(true, true, true);
}

void ON_SubD::SetPerFaceColorsFromSymmetryMotif() const
{
  if (FaceCount() < 1)
    return;

  this->ClearPerFaceColors();
  ChangeRenderContentSerialNumber(); // face color changes.
}

bool ON_SubD::HasPerFaceColorsFromSymmetryMotif() const
{
  return false;
}



//////////////////////////////////////////////////////////////////////////////
//
// ON_SubDMeshFragment - texture coordinates
// 
#if 1
#pragma region ON_SubDMeshFragment - texture coordinates


void ON_SubDMeshFragment::ClearTextureCoordinates() const
{
  m_vertex_count_etc &= ~ON_SubDMeshFragment::EtcTextureCoordinatesExistBit;
  const size_t count = sizeof(this->m_ctrlnetT) / sizeof(this->m_ctrlnetT[0][0]);
  double* p = &this->m_ctrlnetT[0][0];
  double* p1 = p + count;
  while (p < p1)
    *p++ = ON_DBL_QNAN;
}


bool ON_SubDMeshFragment::TextureCoordinatesExistForExperts() const
{
  return (0 != (m_vertex_count_etc & ON_SubDMeshFragment::EtcTextureCoordinatesExistBit));
}

void ON_SubDMeshFragment::SetTextureCoordinatesExistForExperts(bool bTextureCoordinatesExist) const
{
  if (bTextureCoordinatesExist)
    m_vertex_count_etc |= ON_SubDMeshFragment::EtcTextureCoordinatesExistBit;
  else
    ClearTextureCoordinates();
}


unsigned int ON_SubDMeshFragment::TextureCoordinateCount() const
{
  return (TextureCoordinatesExistForExperts() && nullptr != m_T && (0 == m_T_stride || m_T_stride  >= 3)) ? VertexCount() : 0U;
}

unsigned int ON_SubDMeshFragment::TextureCoordinateCapacity() const
{
  return (nullptr != m_T && m_T_stride >= 3) ? VertexCapacity() : 0U;
}

const double* ON_SubDMeshFragment::TextureCoordinateArray(ON_SubDComponentLocation subd_appearance)const
{
  return (ON_SubDComponentLocation::ControlNet == subd_appearance) ? &m_ctrlnetT[0][0] : m_T;
}

size_t ON_SubDMeshFragment::TextureCoordinateArrayStride(ON_SubDComponentLocation subd_appearance)const
{
  return (ON_SubDComponentLocation::ControlNet == subd_appearance) ? 3 : m_T_stride;
}

unsigned ON_SubDMeshFragment::TextureCoordinateArrayCount(ON_SubDComponentLocation subd_appearance) const
{
  if (false == TextureCoordinatesExistForExperts())
    return 0U;
  return (ON_SubDComponentLocation::ControlNet == subd_appearance) ? 4U : TextureCoordinateCount();
}

bool  ON_SubDMeshFragment::GetTextureCoordinteCorners(
  bool bGridOrder,
  ON_3dPoint texture_coordinate_corners[4]
) const
{
  // mutable double m_T_default_bbox[2][2];
  if (nullptr != texture_coordinate_corners)
  {
    int i;
    texture_coordinate_corners[0].x = m_ctrlnetT[0][0];
    texture_coordinate_corners[0].y = m_ctrlnetT[0][1];
    texture_coordinate_corners[0].z = m_ctrlnetT[0][2];

    texture_coordinate_corners[1].x = m_ctrlnetT[1][0];
    texture_coordinate_corners[1].y = m_ctrlnetT[1][1];
    texture_coordinate_corners[1].z = m_ctrlnetT[1][2];

    i = bGridOrder ? 2 : 3;
    texture_coordinate_corners[i].x = m_ctrlnetT[2][0];
    texture_coordinate_corners[i].y = m_ctrlnetT[2][1];
    texture_coordinate_corners[i].z = m_ctrlnetT[2][2];

    i = bGridOrder ? 3 : 2;
    texture_coordinate_corners[i].x = m_ctrlnetT[3][0];
    texture_coordinate_corners[i].y = m_ctrlnetT[3][1];
    texture_coordinate_corners[i].z = m_ctrlnetT[3][2];

    return true;
  }
  return false;
}

static const ON_2dPoint Internal_NgonFragmentPackRectCorner(
  bool bGridOrder,
  const ON_2dPoint face_pack_rect_corners[4],
  double s,
  double t
)
{
  // used for 3-gons and for n-gons with n >= 5
  return (1.0 - s) * (1.0 - t) * face_pack_rect_corners[0] + s * (1.0 - t) * face_pack_rect_corners[1] + (1.0 - s) * t * face_pack_rect_corners[bGridOrder ? 2 : 3] + s * t * face_pack_rect_corners[bGridOrder ? 3 : 2];
}

static const ON_3dPoint Internal_NgonFragmentTextureCoordinateCorner(
  bool bGridOrder,
  const ON_3dPoint face_texture_coordinate_corners[4],
  double s,
  double t
)
{
  // used for 3-gons and for n-gons with n >= 5
  return (1.0 - s) * (1.0 - t) * face_texture_coordinate_corners[0] + s * (1.0 - t) * face_texture_coordinate_corners[1] + (1.0 - s) * t * face_texture_coordinate_corners[bGridOrder ? 2 : 3] + s * t * face_texture_coordinate_corners[bGridOrder ? 3 : 2];
}


void ON_SubDMeshFragment::SetPackRectCornersForExperts(
  bool bGridOrder,
  const ON_2dPoint pack_rect_corners[4]
) 
{
  if (nullptr != pack_rect_corners)
  {
    // m_ctrlnetT[] is in grid order.

    // lower left
    m_pack_rect[0][0] = pack_rect_corners[0].x;
    m_pack_rect[0][1] = pack_rect_corners[0].y;

    // lower right
    m_pack_rect[1][0] = pack_rect_corners[1].x;
    m_pack_rect[1][1] = pack_rect_corners[1].y;

    // upper left
    int i = bGridOrder ? 2 : 3;
    m_pack_rect[2][0] = pack_rect_corners[i].x;
    m_pack_rect[2][1] = pack_rect_corners[i].y;

    // upper right
    i = bGridOrder ? 3 : 2;
    m_pack_rect[3][0] = pack_rect_corners[i].x;
    m_pack_rect[3][1] = pack_rect_corners[i].y;
  }
}

void ON_SubDMeshFragment::SetQuadOr3gonFaceFragmentTextureCoordinateCorners(
  bool bGridOrder,
  const ON_3dPoint face_texture_coordinate_corners[4],
  bool bSetTextureCoordinates
) const
{
  if (1 == m_face_fragment_count && 0 == m_face_fragment_index)
  {
    // A quad ON_SubDFace is rendered with one ON_SubDMeshFragments.
    SetTextureCoordinateCornersForExperts(bGridOrder, face_texture_coordinate_corners, bSetTextureCoordinates);
  }
  else 
  {
    ON_3dPoint fragment_corners[4];

    if (3 == m_face_fragment_count)
    {
      // A 3-gon ON_SubDFace is rendered with three ON_SubDMeshFragments.
      // The pack rect assigned to the face is divided into quarters and
      // 3 of those quarters are assigned to the 3-gon fragments
      // in a continuous manner.

      const int i2 = bGridOrder ? 2 : 3;
      const int i3 = bGridOrder ? 3 : 2;

      fragment_corners[0] = ON_3dPoint::Midpoint(
        ON_3dPoint::Midpoint(face_texture_coordinate_corners[0], face_texture_coordinate_corners[1]),
        ON_3dPoint::Midpoint(face_texture_coordinate_corners[i2], face_texture_coordinate_corners[i3])
      );

      switch (m_face_fragment_index)
      {
      case 0:
        // fragment_corners[] in counter-clockwise order for 3-gon's 1st fragment
        fragment_corners[1] = ON_3dPoint::Midpoint(face_texture_coordinate_corners[0], face_texture_coordinate_corners[i2]);
        fragment_corners[2] = face_texture_coordinate_corners[0];
        fragment_corners[3] = ON_3dPoint::Midpoint(face_texture_coordinate_corners[0], face_texture_coordinate_corners[1]);
        break;

      case 1:
        // fragment_corners[] in counter-clockwise order for 3-gon's 2nd fragment in
        fragment_corners[1] = ON_3dPoint::Midpoint(face_texture_coordinate_corners[0], face_texture_coordinate_corners[1]);
        fragment_corners[2] = face_texture_coordinate_corners[1];
        fragment_corners[3] = ON_3dPoint::Midpoint(face_texture_coordinate_corners[1], face_texture_coordinate_corners[i3]);
        break;

      case 2:
        // fragment_corners[] in counter-clockwise order for 3-gon's 3rd fragment
        fragment_corners[1] = ON_3dPoint::Midpoint(face_texture_coordinate_corners[1], face_texture_coordinate_corners[i3]);
        fragment_corners[2] = face_texture_coordinate_corners[i3];
        fragment_corners[3] = ON_3dPoint::Midpoint(face_texture_coordinate_corners[i2], face_texture_coordinate_corners[i3]);
        break;

      default:
        ON_SUBD_ERROR("Invalid m_face_fragment_index value");
        fragment_corners[0] = ON_3dPoint::NanPoint;
        fragment_corners[1] = ON_3dPoint::NanPoint;
        fragment_corners[2] = ON_3dPoint::NanPoint;
        fragment_corners[3] = ON_3dPoint::NanPoint;
        break;
      }
    }
    else
    {
      // n-gon with n >= 5 or initialized m_face_fragment_count.
      // If m_face_fragment_count >= 5, then you should be calling SetNgonFaceFragmentTextureCoordinateCorners().
      ON_SUBD_ERROR("Invalid m_face_fragment_count value");
      fragment_corners[0] = ON_3dPoint::NanPoint;
      fragment_corners[1] = ON_3dPoint::NanPoint;
      fragment_corners[2] = ON_3dPoint::NanPoint;
      fragment_corners[3] = ON_3dPoint::NanPoint;
    }

    SetTextureCoordinateCornersForExperts(false, fragment_corners, true);
  }
}

bool ON_SubDFace::GetMeshFragmentPackRectCorners(
  bool bGridOrder,
  unsigned int fragment_index,
  ON_2dPoint mesh_fragment_pack_rect_corners[4]
) const
{
  if (nullptr == mesh_fragment_pack_rect_corners)
    return true; // confused caller

  if (fragment_index >= ( (4 == m_edge_count) ? 1U : ((unsigned)m_edge_count) ) )
  {
    return ON_SUBD_RETURN_ERROR(false);
  }

  if (PackRectIsSet())
  {
    switch (m_edge_count)
    {
    case 0:
    case 1:
    case 2:
      mesh_fragment_pack_rect_corners[0] = ON_2dPoint::NanPoint;
      mesh_fragment_pack_rect_corners[1] = ON_2dPoint::NanPoint;
      mesh_fragment_pack_rect_corners[2] = ON_2dPoint::NanPoint;
      mesh_fragment_pack_rect_corners[3] = ON_2dPoint::NanPoint;
      return false;
      break;

    case 3: // triangle
      {
        // A 3-gon ON_SubDFace is rendered with three ON_SubDMeshFragments.
        // The pack rect assigned to the face is divided into quarters and
        // 3 of those quarters are assigned to the 3-gon fragments
        // in a continuous manner.

        const ON_2dPoint face_pack_rect_corners[4] = 
        {
          PackRectCorner(bGridOrder, 0),
          PackRectCorner(bGridOrder, 1),
          PackRectCorner(bGridOrder, 2),
          PackRectCorner(bGridOrder, 3)
        };
        const int i2 = bGridOrder ? 2 : 3;
        const int i3 = bGridOrder ? 3 : 2;

        mesh_fragment_pack_rect_corners[0] = ON_2dPoint::Midpoint(
          ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[1]),
          ON_2dPoint::Midpoint(face_pack_rect_corners[i2], face_pack_rect_corners[i3])
        );

        switch (fragment_index)
        {
        case 0:
          // mesh_fragment_pack_rect_corners[] in counter-clockwise order for 3-gon's 1st fragment
          mesh_fragment_pack_rect_corners[1] = ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[i2]);
          mesh_fragment_pack_rect_corners[i2] = face_pack_rect_corners[0];
          mesh_fragment_pack_rect_corners[i3] = ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[1]);
          break;

        case 1:
          // mesh_fragment_pack_rect_corners[] in counter-clockwise order for 3-gon's 2nd fragment in
          mesh_fragment_pack_rect_corners[1] = ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[1]);
          mesh_fragment_pack_rect_corners[i2] = face_pack_rect_corners[1];
          mesh_fragment_pack_rect_corners[i3] = ON_2dPoint::Midpoint(face_pack_rect_corners[1], face_pack_rect_corners[i3]);
          break;

        case 2:
          // mesh_fragment_pack_rect_corners[] in counter-clockwise order for 3-gon's 3rd fragment
          mesh_fragment_pack_rect_corners[1] = ON_2dPoint::Midpoint(face_pack_rect_corners[1], face_pack_rect_corners[i3]);
          mesh_fragment_pack_rect_corners[i2] = face_pack_rect_corners[i3];
          mesh_fragment_pack_rect_corners[i3] = ON_2dPoint::Midpoint(face_pack_rect_corners[i2], face_pack_rect_corners[i3]);
          break;
        }
      }
      return true;
      break;

    case 4: // quad
      return this->GetFacePackRectCorners(bGridOrder,mesh_fragment_pack_rect_corners);
      break;

    default: // n-gon with n >= 5
      {
        // An n-gon ON_SubDFace is rendered with n ON_SubDMeshFragments.
        ON_2dPoint face_pack_rect_corners[4];
        if (this->GetFacePackRectCorners(bGridOrder, face_pack_rect_corners))
        {
          const ON_2dVector face_pack_rect_size = this->PackRectSize();
          ON_2dVector ngon_sub_pack_rect_size;
          ON_2dVector ngon_sub_pack_rect_delta;
          const ON_2udex ngon_grid_size = ON_SubDFace::GetNgonSubPackRectSizeAndDelta(
            m_edge_count,
            face_pack_rect_size,
            ngon_sub_pack_rect_size,
            ngon_sub_pack_rect_delta
          );
          if (ngon_grid_size.i > 0 && ngon_grid_size.j > 0 && ON_SubDMeshFragment::GetNgonFaceFragmentPackRectCorners(
            m_edge_count,
            fragment_index,
            bGridOrder,
            face_pack_rect_corners,
            face_pack_rect_size,
            ngon_grid_size,
            ngon_sub_pack_rect_size,
            ngon_sub_pack_rect_delta,
            mesh_fragment_pack_rect_corners
          ))
          {
            return true;
          }
        }
      }
      break;
    }
  }

  mesh_fragment_pack_rect_corners[0] = ON_2dPoint::NanPoint;
  mesh_fragment_pack_rect_corners[1] = ON_2dPoint::NanPoint;
  mesh_fragment_pack_rect_corners[2] = ON_2dPoint::NanPoint;
  mesh_fragment_pack_rect_corners[3] = ON_2dPoint::NanPoint;
  return false;
}


static const ON_2dPoint Internal_PackRectCenterPoint(
  const ON_2dPoint face_pack_rect_corners[4]
)
{
  // This code works for face_pack_rect_corners[] in either grid order or counter clockwise order
  // because swapping 2 and 3 does not change the result.
  return ON_2dPoint::Midpoint(
    ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[1]),
    ON_2dPoint::Midpoint(face_pack_rect_corners[2], face_pack_rect_corners[3])
  );
}

bool ON_SubDMeshFragment::Get3gonFaceFragmentPackRectCorners(
  bool bFaceGridOrder,
  const ON_2dPoint face_pack_rect_corners[4], 
  unsigned int fragment_index,
  bool bFragmentGridOrder,
  ON_2dPoint fragment_pack_rect_corners[4])
{
  fragment_pack_rect_corners[0] = Internal_PackRectCenterPoint(face_pack_rect_corners);
  // A 3-gon ON_SubDFace is rendered with three ON_SubDMeshFragments.
  // The pack rect assigned to the face is divided into quarters and
  // 3 of those quarters are assigned to the 3-gon fragments
  // in a continuous manner.

  const int i2 = bFaceGridOrder ? 2 : 3;
  const int i3 = bFaceGridOrder ? 3 : 2;

  const int j2 = bFragmentGridOrder ? 3 : 2;
  const int j3 = bFragmentGridOrder ? 2 : 3;

  fragment_pack_rect_corners[0] = Internal_PackRectCenterPoint(face_pack_rect_corners);

  bool rc = true;
  switch (fragment_index)
  {
  case 0:
    // fragment_pack_rect_corners[] in counter-clockwise order for 3-gon's 1st fragment
    fragment_pack_rect_corners[1] = ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[i2]);
    fragment_pack_rect_corners[j2] = face_pack_rect_corners[0];
    fragment_pack_rect_corners[j3] = ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[1]);
    break;

  case 1:
    // fragment_pack_rect_corners[] in counter-clockwise order for 3-gon's 2nd fragment in
    fragment_pack_rect_corners[1] = ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[1]);
    fragment_pack_rect_corners[j2] = face_pack_rect_corners[1];
    fragment_pack_rect_corners[j3] = ON_2dPoint::Midpoint(face_pack_rect_corners[1], face_pack_rect_corners[i3]);
    break;

  case 2:
    // fragment_pack_rect_corners[] in counter-clockwise order for 3-gon's 3rd fragment
    fragment_pack_rect_corners[1] = ON_2dPoint::Midpoint(face_pack_rect_corners[1], face_pack_rect_corners[i3]);
    fragment_pack_rect_corners[j2] = face_pack_rect_corners[i3];
    fragment_pack_rect_corners[j3] = ON_2dPoint::Midpoint(face_pack_rect_corners[i2], face_pack_rect_corners[i3]);
    break;

  default:
    ON_SUBD_ERROR("Invalid m_face_fragment_index value");
    fragment_pack_rect_corners[0] = ON_2dPoint::NanPoint;
    fragment_pack_rect_corners[1] = ON_2dPoint::NanPoint;
    fragment_pack_rect_corners[2] = ON_2dPoint::NanPoint;
    fragment_pack_rect_corners[3] = ON_2dPoint::NanPoint;
    rc = false;
    break;
  }
  return rc;

}

void ON_SubDMeshFragment::SetQuadOr3gonFaceFragmentPackRectCorners(
  bool bGridOrder,
  const ON_2dPoint face_pack_rect_corners[4]
) 
{
  if (1 == m_face_fragment_count && 0 == m_face_fragment_index)
  {
    // A quad ON_SubDFace is rendered with one ON_SubDMeshFragments.
    SetPackRectCornersForExperts(bGridOrder, face_pack_rect_corners);
  }
  else
  {
    ON_2dPoint fragment_corners[4];

    if (3 == m_face_fragment_count)
    {
      // A 3-gon ON_SubDFace is rendered with three ON_SubDMeshFragments.
      // The pack rect assigned to the face is divided into quarters and
      // 3 of those quarters are assigned to the 3-gon fragments
      // in a continuous manner.

      const int i2 = bGridOrder ? 2 : 3;
      const int i3 = bGridOrder ? 3 : 2;

      fragment_corners[0] = Internal_PackRectCenterPoint(face_pack_rect_corners);

      switch (m_face_fragment_index)
      {
      case 0:
        // fragment_corners[] in counter-clockwise order for 3-gon's 1st fragment
        fragment_corners[1] = ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[i2]);
        fragment_corners[2] = face_pack_rect_corners[0];
        fragment_corners[3] = ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[1]);
        break;

      case 1:
        // fragment_corners[] in counter-clockwise order for 3-gon's 2nd fragment in
        fragment_corners[1] = ON_2dPoint::Midpoint(face_pack_rect_corners[0], face_pack_rect_corners[1]);
        fragment_corners[2] = face_pack_rect_corners[1];
        fragment_corners[3] = ON_2dPoint::Midpoint(face_pack_rect_corners[1], face_pack_rect_corners[i3]);
        break;

      case 2:
        // fragment_corners[] in counter-clockwise order for 3-gon's 3rd fragment
        fragment_corners[1] = ON_2dPoint::Midpoint(face_pack_rect_corners[1], face_pack_rect_corners[i3]);
        fragment_corners[2] = face_pack_rect_corners[i3];
        fragment_corners[3] = ON_2dPoint::Midpoint(face_pack_rect_corners[i2], face_pack_rect_corners[i3]);
        break;

      default:
        ON_SUBD_ERROR("Invalid m_face_fragment_index value");
        fragment_corners[0] = ON_2dPoint::NanPoint;
        fragment_corners[1] = ON_2dPoint::NanPoint;
        fragment_corners[2] = ON_2dPoint::NanPoint;
        fragment_corners[3] = ON_2dPoint::NanPoint;
        break;
      }
    }
    else
    {
      // n-gon with n >= 5 or initialized m_face_fragment_count.
      // If m_face_fragment_count >= 5, then you should be calling SetNgonFaceFragmentPackRectCorners().
      ON_SUBD_ERROR("Invalid m_face_fragment_count value");
      fragment_corners[0] = ON_2dPoint::NanPoint;
      fragment_corners[1] = ON_2dPoint::NanPoint;
      fragment_corners[2] = ON_2dPoint::NanPoint;
      fragment_corners[3] = ON_2dPoint::NanPoint;
    }

    SetPackRectCornersForExperts(false, fragment_corners);
  }
}

static double Internal_ClampBetweenZeroAndOne(double x)
{
  if (x < 0.0)
    return 0.0;
  if (x > 1.0)
    return 1.0;
  return x;
}

void ON_SubDMeshFragment::SetNgonFaceFragmentTextureCoordinateCorners(
  bool bGridOrder,
  const ON_3dPoint face_texture_coordinate_corners[4],
  ON_2dVector face_pack_rect_size,
  ON_2udex ngon_grid_size,
  ON_2dVector ngon_sub_pack_rect_size,
  ON_2dVector ngon_sub_pack_rect_delta,
  bool bSetTextureCoordinates
) const
{
  for (;;)
  {
    if (
      face_texture_coordinate_corners[0] == face_texture_coordinate_corners[1]
      && face_texture_coordinate_corners[0] == face_texture_coordinate_corners[2]
      && face_texture_coordinate_corners[0] == face_texture_coordinate_corners[3]
      )
    {
      // constant texture coordinates
      SetTextureCoordinateCornersForExperts(true, face_texture_coordinate_corners, bSetTextureCoordinates);
      return;
    }

    const unsigned ngon_edge_count = m_face_fragment_count;
    const unsigned ngon_fragment_index = m_face_fragment_index;
    if (ngon_edge_count < 5 || ngon_edge_count > ON_SubDFace::MaximumEdgeCount)
      break;
    if (ngon_fragment_index >= ngon_edge_count)
      break;
    if (ngon_grid_size.i * ngon_grid_size.j < ngon_edge_count)
      break;
    const ON_2udex frag_k(ngon_fragment_index % ngon_grid_size.i, ngon_fragment_index / ngon_grid_size.i);
    const double s0 = Internal_ClampBetweenZeroAndOne(frag_k.i * (ngon_sub_pack_rect_delta.x/face_pack_rect_size.x));
    const double s1 = Internal_ClampBetweenZeroAndOne(s0 + (ngon_sub_pack_rect_size.x/ face_pack_rect_size.x));
    const double t0 = Internal_ClampBetweenZeroAndOne(frag_k.j * (ngon_sub_pack_rect_delta.y/ face_pack_rect_size.y));
    const double t1 = Internal_ClampBetweenZeroAndOne(t0 + (ngon_sub_pack_rect_size.y/ face_pack_rect_size.y));
    const ON_3dPoint fragment_texture_coordinate_corners[4] = {
      Internal_NgonFragmentTextureCoordinateCorner(bGridOrder,face_texture_coordinate_corners,s0,t0),
      Internal_NgonFragmentTextureCoordinateCorner(bGridOrder,face_texture_coordinate_corners,s1,t0),
      Internal_NgonFragmentTextureCoordinateCorner(bGridOrder,face_texture_coordinate_corners,s0,t1),
      Internal_NgonFragmentTextureCoordinateCorner(bGridOrder,face_texture_coordinate_corners,s1,t1)
    };
    // fragment_texture_coordinate_corners[] is in grid order
    SetTextureCoordinateCornersForExperts(true, fragment_texture_coordinate_corners, bSetTextureCoordinates);
    return;
  }
  ON_SUBD_ERROR("Invalid input.");
  const ON_3dPoint nan_corners[4] = { ON_3dPoint ::NanPoint,ON_3dPoint::NanPoint ,ON_3dPoint::NanPoint ,ON_3dPoint::NanPoint };
  SetTextureCoordinateCornersForExperts(bGridOrder, nan_corners, bSetTextureCoordinates);
}


bool ON_SubDMeshFragment::GetNgonFaceFragmentPackRectCorners(
  unsigned int ngon_edge_count,
  unsigned int ngon_fragment_index,
  bool bGridOrder,
  const ON_2dPoint face_pack_rect_corners[4],
  ON_2dVector face_pack_rect_size,
  ON_2udex ngon_grid_size,
  ON_2dVector ngon_sub_pack_rect_size,
  ON_2dVector ngon_sub_pack_rect_delta,
  ON_2dPoint fragment_pack_rect_corners[4]
)
{
  for (;;)
  {
    if (ngon_edge_count < 5 || ngon_edge_count > ON_SubDFace::MaximumEdgeCount)
      break;
    if (ngon_fragment_index >= ngon_edge_count)
      break;
    if (ngon_grid_size.i * ngon_grid_size.j < ngon_edge_count)
      break;
    if (nullptr == fragment_pack_rect_corners)
      break;
    const ON_2udex frag_k(ngon_fragment_index % ngon_grid_size.i, ngon_fragment_index / ngon_grid_size.i);
    const double s0 = Internal_ClampBetweenZeroAndOne(frag_k.i * (ngon_sub_pack_rect_delta.x / face_pack_rect_size.x));
    const double s1 = Internal_ClampBetweenZeroAndOne(s0 + (ngon_sub_pack_rect_size.x / face_pack_rect_size.x));
    const double t0 = Internal_ClampBetweenZeroAndOne(frag_k.j * (ngon_sub_pack_rect_delta.y / face_pack_rect_size.y));
    const double t1 = Internal_ClampBetweenZeroAndOne(t0 + (ngon_sub_pack_rect_size.y / face_pack_rect_size.y));
    const int i2 = bGridOrder ? 2 : 3;
    const int i3 = bGridOrder ? 3 : 2;
    fragment_pack_rect_corners[0] = Internal_NgonFragmentPackRectCorner(bGridOrder,face_pack_rect_corners,s0,t0);
    fragment_pack_rect_corners[1] = Internal_NgonFragmentPackRectCorner(bGridOrder,face_pack_rect_corners,s1,t0);
    fragment_pack_rect_corners[i2] = Internal_NgonFragmentPackRectCorner(bGridOrder,face_pack_rect_corners,s0,t1);
    fragment_pack_rect_corners[i3] = Internal_NgonFragmentPackRectCorner(bGridOrder,face_pack_rect_corners,s1,t1);
    return true;
  }

  ON_SUBD_ERROR("Invalid input.");
  if (nullptr != fragment_pack_rect_corners)
  {
    fragment_pack_rect_corners[0] = ON_2dPoint::NanPoint;
    fragment_pack_rect_corners[1] = ON_2dPoint::NanPoint;
    fragment_pack_rect_corners[2] = ON_2dPoint::NanPoint;
    fragment_pack_rect_corners[3] = ON_2dPoint::NanPoint;
  }

  return false;
}

void ON_SubDMeshFragment::SetNgonFaceFragmentPackRectCorners(
  bool bGridOrder,
  const ON_2dPoint face_pack_rect_corners[4],
  ON_2dVector face_pack_rect_size,
  ON_2udex ngon_grid_size,
  ON_2dVector ngon_sub_pack_rect_size,
  ON_2dVector ngon_sub_pack_rect_delta
)
{
  ON_2dPoint fragment_pack_rect_corners[4];
  ON_SubDMeshFragment::GetNgonFaceFragmentPackRectCorners(
    m_face_fragment_count,
    m_face_fragment_index,
    bGridOrder,
    face_pack_rect_corners,
    face_pack_rect_size,
    ngon_grid_size,
    ngon_sub_pack_rect_size,
    ngon_sub_pack_rect_delta,
    fragment_pack_rect_corners
  );
  SetPackRectCornersForExperts(bGridOrder, fragment_pack_rect_corners);
}

void ON_SubDMeshFragment::SetTextureCoordinateCornersForExperts(
  bool bGridOrder,
  const ON_3dPoint fragment_texture_coordinate_corners[4],
  bool bSetTextureCoordinates
) const
{
  if (nullptr != fragment_texture_coordinate_corners)
  {
    // m_ctrlnetT[] is in grid order.

    // lower left
    m_ctrlnetT[0][0] = fragment_texture_coordinate_corners[0].x;
    m_ctrlnetT[0][1] = fragment_texture_coordinate_corners[0].y;
    m_ctrlnetT[0][2] = fragment_texture_coordinate_corners[0].z;

    // lower right
    m_ctrlnetT[1][0] = fragment_texture_coordinate_corners[1].x;
    m_ctrlnetT[1][1] = fragment_texture_coordinate_corners[1].y;
    m_ctrlnetT[1][2] = fragment_texture_coordinate_corners[1].z; 

    // upper left
    int i = bGridOrder ? 2 : 3;
    m_ctrlnetT[2][0] = fragment_texture_coordinate_corners[i].x;
    m_ctrlnetT[2][1] = fragment_texture_coordinate_corners[i].y;
    m_ctrlnetT[2][2] = fragment_texture_coordinate_corners[i].z;

    // upper right
    i = bGridOrder ? 3 : 2;
    m_ctrlnetT[3][0] = fragment_texture_coordinate_corners[i].x;
    m_ctrlnetT[3][1] = fragment_texture_coordinate_corners[i].y;
    m_ctrlnetT[3][2] = fragment_texture_coordinate_corners[i].z;

    if (bSetTextureCoordinates)
      SetTextureCoordinatesFromCorners();
  }
}

const ON_3dPoint ON_SubDMeshFragment::VertexTextureCoordinate(
  ON_2udex grid2dex
) const
{
  return VertexTextureCoordinate(m_grid.PointIndexFromGrid2dex(grid2dex.i, grid2dex.j));
}

const ON_3dPoint ON_SubDMeshFragment::VertexTextureCoordinate(
  unsigned grid2dex_i,
  unsigned grid2dex_j
) const
{
  return VertexTextureCoordinate(m_grid.PointIndexFromGrid2dex(grid2dex_i, grid2dex_j));
}

const ON_3dPoint ON_SubDMeshFragment::VertexTextureCoordinate(
  unsigned grid_point_index
) const
{
  return
    (grid_point_index >= TextureCoordinateCount())
    ? ON_3dPoint::NanPoint
    : ON_3dPoint(m_T + grid_point_index * m_T_stride);
}

const ON_3dPoint ON_SubDMeshFragment::VertexTextureCoordinateFromCorners(unsigned grid2dex_i, unsigned grid2dex_j) const
{
  const unsigned n = m_grid.SideSegmentCount();
  if (n <= 0U || grid2dex_i > n || grid2dex_j > n)
    return ON_3dPoint::NanPoint;
  const double s = ((double)grid2dex_i) / ((double)n);
  const double t = ((double)grid2dex_j) / ((double)n);
  const double c[4] = { (1.0 - s)*(1.0 - t), s*(1.0 - t), (1.0 - s)*t, s*t };
  return ON_3dPoint(
    c[0] * m_ctrlnetT[0][0] + c[1] * m_ctrlnetT[1][0] + c[2] * m_ctrlnetT[2][0] + c[3] * m_ctrlnetT[3][0],
    c[0] * m_ctrlnetT[0][1] + c[1] * m_ctrlnetT[1][1] + c[2] * m_ctrlnetT[2][1] + c[3] * m_ctrlnetT[3][1],
    c[0] * m_ctrlnetT[0][2] + c[1] * m_ctrlnetT[1][2] + c[2] * m_ctrlnetT[2][2] + c[3] * m_ctrlnetT[3][2]
  );
}

const ON_3dPoint ON_SubDMeshFragment::VertexTextureCoordinateFromCorners(ON_2udex grid2dex) const
{
  return VertexTextureCoordinateFromCorners(grid2dex.i, grid2dex.j);
}

const ON_3dPoint ON_SubDMeshFragment::VertexTextureCoordinateFromCorners(unsigned grid_point_index) const
{
  return VertexTextureCoordinateFromCorners(m_grid.Grid2dexFromPointIndex(grid_point_index));
}

void ON_SubDMeshFragment::SetTextureCoordinatesFromCorners() const
{
  Internal_SetTextureCoordinatesFromCorners(m_ctrlnetT[0], m_ctrlnetT[1], m_ctrlnetT[2], m_ctrlnetT[3], ON_DBL_QNAN, 3);
}

void ON_SubDMeshFragment::SetPackedTextureCoordinates() const
{
  Internal_SetTextureCoordinatesFromCorners(m_pack_rect[0], m_pack_rect[1], m_pack_rect[2], m_pack_rect[3], 0.0, 2);
}

void ON_SubDMeshFragment::SetUnpackedTextureCoordinates() const
{
  const double unpacked_corners[4][2] =
  {
    {0.0,0.0},
    {1.0,0.0},
    {0.0,1.0},
    {1.0,1.0},
  };
  Internal_SetTextureCoordinatesFromCorners(unpacked_corners[0], unpacked_corners[1], unpacked_corners[2], unpacked_corners[3], 0.0, 2);
}

void ON_SubDMeshFragment::Internal_SetTextureCoordinatesFromCorners(
  const double* corner0, 
  const double* corner1, 
  const double* corner2,
  const double* corner3,
  double default_coordinate_value,
  int corner_dim
) const
{
  const unsigned n = m_grid.SideSegmentCount();
  if (n <= 0U || n > ON_SubDMeshFragment::MaximumSideSegmentCount)
    return;
  // TextureCoordinateCapacity() check insures m_T_stride >= 3
  if (TextureCoordinateCapacity() < n * n) 
    return;
  if (corner_dim <= 0)
    return;
  if (corner_dim > 3)
    corner_dim = 3;
  if (nullptr == corner0 || nullptr == corner1 || nullptr == corner2 || nullptr == corner3)
    return;
    
  SetTextureCoordinatesExistForExperts(true);
  double* T = m_T;
  const double d = (double)n;
  double s, t;
  ON_3dPoint tc(default_coordinate_value, default_coordinate_value, default_coordinate_value);
  bool bConstant[3] = { corner_dim < 1, corner_dim < 2, corner_dim < 3 };
  for (int i = 0; i < corner_dim; ++i)
  {
    double c = corner0[i];
    if (c == corner1[i] && c == corner2[i] && c == corner3[i])
    {
      tc[i] = c;
      bConstant[i] = true;
    }
    else if (false == (c == c) || false == (corner1[i] == corner1[i]) || false == (corner2[i] == corner2[i]) || false == (corner3[i] == corner3[i]))
    {
      tc[i] = ON_DBL_QNAN;
      bConstant[i] = true;
    }
  }

  for (unsigned j = 0U; j <= n; ++j)
  {
    t = ((double)j) / d;
    for (unsigned i = 0U; i <= n; ++i)
    {
      s = ((double)i) / d;
      const double c[4] = { (1.0 - s) * (1.0 - t), s * (1.0 - t), (1.0 - s) * t, s * t };
      if (false == bConstant[0])
        tc.x = c[0] * corner0[0] + c[1] * corner1[0] + c[2] * corner2[0] + c[3] * corner3[0];
      if (false == bConstant[1])
        tc.y = c[0] * corner0[1] + c[1] * corner1[1] + c[2] * corner2[1] + c[3] * corner3[1];
      if (false == bConstant[2])
        tc.z = c[0] * corner0[2] + c[1] * corner1[2] + c[2] * corner2[2] + c[3] * corner3[2];
      T[0] = tc.x;
      T[1] = tc.y;
      T[2] = tc.z;
      T += m_T_stride;
    }
  }

  return;
}


bool ON_SubDMeshFragment::SetVertexTextureCoordinate(
  ON_2udex grid2dex,
  ON_3dPoint texture_coordinate
) const
{
  return SetVertexTextureCoordinate(m_grid.PointIndexFromGrid2dex(grid2dex.i, grid2dex.j), texture_coordinate);
}

bool ON_SubDMeshFragment::SetVertexTextureCoordinate(
  unsigned grid2dex_i,
  unsigned grid2dex_j,
  ON_3dPoint texture_coordinate
) const
{
  return SetVertexTextureCoordinate(m_grid.PointIndexFromGrid2dex(grid2dex_i, grid2dex_j), texture_coordinate);
}

bool ON_SubDMeshFragment::SetVertexTextureCoordinate(
  unsigned grid_point_index,
  ON_3dPoint texture_coordinate
) const
{
  if (grid_point_index >= TextureCoordinateCapacity())
    return false;
  double* T = (m_T + grid_point_index * m_T_stride);
  T[0] = texture_coordinate.x;
  T[1] = texture_coordinate.y;
  T[2] = texture_coordinate.z;
  SetTextureCoordinatesExistForExperts(true);
  return true;
}

#pragma endregion
#endif
